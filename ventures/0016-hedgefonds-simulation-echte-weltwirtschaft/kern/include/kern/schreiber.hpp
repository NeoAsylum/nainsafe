#pragma once
//! `kern::schreiber` -- der einzige Schreibweg und die Kette, die dabei entsteht.
//!
//! Vorgaben: T18 (ein Schreibweg, ein Ursachensatz je Schreibzugriff, Bitfeld ueber
//! alle 310 Adressen), T38 (der Modus ist Argument und bringt eine Sollmaske mit),
//! T39 (zwei Lesezugriffe, und der falsche stirbt sofort), T19 (die Kette gehoert
//! nicht in den Zustand, ihre Aufnahmekapazitaet ist fest). Dazu T9, T15, T17, T4,
//! T2. Die Sprache ist C++20 nach ADR 0011.
//!
//! **Drei Zusagen des Produkts haengen an diesem Kasten, und keine ist eine
//! Fleissaufgabe:**
//!
//!   1. Jede Groesse der Sollmaske wird je Runde **genau einmal** geschrieben (T18).
//!   2. Es gibt **acht** rundenuebergreifende Rueckkopplungskanaele und nicht neun
//!      (T18). Eine Rueckkopplung innerhalb der Runde braucht zwangslaeufig einen
//!      zweiten Schreibzugriff auf dieselbe Adresse -- der stirbt hier, statt als
//!      neunter Kanal unbemerkt zu entstehen.
//!   3. Die Reihenfolge der sechs Rundenschritte ist **zyklenfrei** (T39). Wer den
//!      Wert dieser Runde liest, bevor er geschrieben ist, bekommt keinen stillen
//!      Rueckgriff auf die Vorrunde, sondern einen Abbruch.
//!
//! Alle drei sind Eigenschaften des Codes oder gar nicht. Der stille Rueckgriff waere
//! dabei die gefaehrlichere Bequemlichkeit: Er macht das Ergebnis von der Reihenfolge
//! der sechs Schritte abhaengig, ohne dass irgendwo steht, dass es das tut.
//!
//! ## Was hier nicht steht
//!
//! Der **Rundenablauf** (`kern::schritt`): welche sechs Schritte in welcher Reihenfolge
//! laufen und wer `setze` aufruft. Gebaut ist der Weg, nicht der Gang. Ebenso wenig die
//! **abgeleiteten Groessen** (`kern::werte`) -- dieser Kasten kennt Adressen und Werte,
//! keine Bewertungsformel -- und der **Verlauf**, den nach T19 die Sitzung fuehrt.
//!
//! ## Gebaut gegen das Verzeichnis
//!
//! Die Adressen kommen aus `kern::zustand`, also aus `daten/adressen.md`. Eine Adresse
//! ist hier ihre Maschinenform, der Platz `0 ... 309`; `zustand::adresse_zu_index` ist
//! der Weg von der Textform aus T17 hierher, `zustand::index_zu_adresse` der Weg
//! zurueck. Der Grund fuer die Maschinenform: Der Schreiber wird je Runde
//! dreihundertmal gerufen, und die Textform waere dreihundert Tabellensuchen.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/zustand.hpp"

namespace kern::schreiber {

using zustand::Gebiet;
using zustand::i64;
using zustand::Index;
using zustand::Instrument;
using zustand::Sektor;
using zustand::u64;
using zustand::Zustand;
using zustand::FELDER;

// ---------------------------------------------------------------------------
// T38 -- der Modus
// ---------------------------------------------------------------------------

/// Die beiden Modi aus `spiel.md`.
///
/// Der Modus steht **nicht** im Zustand (T38): Er waere ein 311. Feld und
/// widerspraeche einer Zahl, die `spiel.md` nennt, und er beschreibt nicht die Welt,
/// sondern die Art, sie zu rechnen. Er ist deshalb Argument des Schreibers.
enum class Modus : std::uint8_t {
    Spielmodus = 0,
    Weltlauf = 1,
};

// ---------------------------------------------------------------------------
// Das Bitfeld ueber alle 310 Adressen (T18)
// ---------------------------------------------------------------------------

/// So viele 64-Bit-Woerter fassen 310 Bits.
inline constexpr std::size_t BITFELD_WOERTER = (FELDER + 63) / 64;

static_assert(BITFELD_WOERTER == 5, "310 Bits liegen in fuenf Woertern zu 64 Bit");

/// Eine Menge von Adressen als Bitfeld fester Groesse.
///
/// Die Speicherform ist die Entscheidung des Bauagenten -- `specs/` schweigt dazu.
/// Gewaehlt sind fuenf Woerter zu 64 Bit, weil damit die Kosten aus T18 ("40 Byte je
/// Runde, ein Bittest je Schreibzugriff") woertlich eingehalten sind und weil `anzahl`
/// die Maskengroesse aus T38 schon beim Uebersetzen nachrechnen kann. Die Reihenfolge
/// ist fest: Bit `n` liegt im Wort `n / 64` an der Stelle `n % 64`.
///
/// Die zehn ueberzaehligen Bits des fuenften Wortes werden nie gesetzt: Jeder Zugriff
/// prueft gegen `FELDER` und nicht gegen `BITFELD_WOERTER * 64`.
class Bitfeld {
public:
    constexpr void setze(Index platz)
    {
        pruefe_platz(platz);
        wort_[platz / 64] |= (u64{1} << (platz % 64));
    }

    [[nodiscard]] constexpr bool steht(Index platz) const
    {
        pruefe_platz(platz);
        return (wort_[platz / 64] & (u64{1} << (platz % 64))) != 0;
    }

    /// Wie viele Bits stehen. Das ist die Maskengroesse aus T38, gezaehlt statt
    /// behauptet.
    [[nodiscard]] constexpr std::size_t anzahl() const noexcept
    {
        std::size_t summe = 0;
        for (const u64 wort : wort_) {
            u64 rest = wort;
            while (rest != 0) {
                if ((rest & u64{1}) != 0) {
                    ++summe;
                }
                rest >>= 1;
            }
        }
        return summe;
    }

    constexpr bool operator==(const Bitfeld&) const = default;

private:
    static constexpr void pruefe_platz(Index platz)
    {
        if (platz >= FELDER) {
            festkomma::abbruch("kern::schreiber -- Adresse ausserhalb der 310 Felder");
        }
    }

    std::array<u64, BITFELD_WOERTER> wort_{};
};

// ---------------------------------------------------------------------------
// T18 -- die Ursache, eine geschlossene Aufzaehlung mit sechs Formen
// ---------------------------------------------------------------------------

/// Die sechs Formen aus der Tabelle in T18. Es gibt keine siebte und keinen Freitext:
/// Eine Ursache, die sich nicht benennen laesst, ist eine, die niemand spaeter
/// zuordnen kann.
enum class UrsacheArt : std::uint8_t {
    Aktion = 0,          ///< `Aktion{nr}`
    Instrument = 1,      ///< `Instrument{land, instr}`
    Gegenkraft = 2,      ///< `Gegenkraft{art}`
    Marktraeumung = 3,   ///< `Marktraeumung{sektor}` -- in T18 mit Umlaut geschrieben
    Vortrag = 4,         ///< `Vortrag{adresse}`
    Jahrgang = 5,        ///< `Jahrgang`, ohne Beiwerk
};

/// Wie viele Aktionsarten es gibt (`spiel.md`, *Die Aktionen*: fuenf Arten, die
/// Kennungen 1 bis 5 sind zugleich die Gleichstandsordnung aller Masse).
inline constexpr std::size_t AKTIONSARTEN = 5;

/// Wie viele Gegenkraefte es gibt (`spiel.md`, *Die Gegenkraefte*: fuenf, von der
/// Aufsicht bis zur Gegenlobby, durchgezaehlt 1 bis 5).
inline constexpr std::size_t GEGENKRAEFTE = 5;

/// Eine Ursache aus T18 -- die Art und genau der Beiwert, den ihre Form nennt.
///
/// Gebaut als geschlossene Klasse mit benannten Erzeugern statt als offene Struktur:
/// Ein Wert dieses Typs entsteht nur ueber einen der sechs Erzeuger, und jeder prueft
/// seinen Beiwert beim Anlegen. Wer den falschen Beiwert abfragt -- das Land einer
/// `Gegenkraft` etwa --, bekommt keinen Ersatzwert, sondern einen Abbruch.
///
/// Der voreingestellte Wert ist `Jahrgang`. Das ist die einzige Form ohne Beiwert und
/// damit die einzige, die ohne Angabe vollstaendig ist; ein Behaelter fester Groesse
/// braucht einen solchen Wert, und ein siebter, ungueltiger Zustand waere schlechter
/// als eine der sechs Formen.
class Ursache {
public:
    constexpr Ursache() noexcept = default;

    /// `Aktion{nr}` -- `nr` ist die Aktionsart 1 bis 5 aus `spiel.md`.
    [[nodiscard]] static constexpr Ursache aktion(std::size_t nr)
    {
        if (nr < 1 || nr > AKTIONSARTEN) {
            festkomma::abbruch("kern::schreiber -- es gibt fuenf Aktionsarten, 1 bis 5");
        }
        return Ursache{UrsacheArt::Aktion, static_cast<std::uint16_t>(nr), 0};
    }

    /// `Instrument{land, instr}` -- nur spielbare Laender haben Politikinstrumente
    /// (T15); die Restwelt hat keine.
    [[nodiscard]] static constexpr Ursache instrument(Gebiet gebiet, Instrument welches)
    {
        const std::size_t l = static_cast<std::size_t>(gebiet);
        const std::size_t i = static_cast<std::size_t>(welches);
        if (l >= zustand::LAENDER) {
            festkomma::abbruch(
                "kern::schreiber -- Politikinstrumente gibt es nur bei spielbaren Laendern");
        }
        if (i >= zustand::INSTRUMENTE) {
            festkomma::abbruch("kern::schreiber -- unbekanntes Politikinstrument");
        }
        return Ursache{UrsacheArt::Instrument, static_cast<std::uint16_t>(l),
                       static_cast<std::uint16_t>(i)};
    }

    /// `Gegenkraft{art}` -- `art` ist die Nummer 1 bis 5 aus `spiel.md`.
    [[nodiscard]] static constexpr Ursache gegenkraft(std::size_t art)
    {
        if (art < 1 || art > GEGENKRAEFTE) {
            festkomma::abbruch("kern::schreiber -- es gibt fuenf Gegenkraefte, 1 bis 5");
        }
        return Ursache{UrsacheArt::Gegenkraft, static_cast<std::uint16_t>(art), 0};
    }

    /// `Marktraeumung{sektor}` -- alle drei Sektoren werden geraeumt; handelbar sind
    /// nur die ersten beiden, und das ist eine Frage des Handels und nicht der
    /// Raeumung.
    [[nodiscard]] static constexpr Ursache marktraeumung(Sektor welcher)
    {
        const std::size_t versatz = zustand::sektor_index(welcher);
        return Ursache{UrsacheArt::Marktraeumung, static_cast<std::uint16_t>(versatz), 0};
    }

    /// `Vortrag{adresse}` -- die Adresse, aus der der Wert vorgetragen wurde. Bei der
    /// unveraenderten Groesse ist das ihre eigene.
    [[nodiscard]] static constexpr Ursache vortrag(Index adresse)
    {
        if (adresse >= FELDER) {
            festkomma::abbruch("kern::schreiber -- Vortrag aus einer Adresse ausserhalb der 310");
        }
        return Ursache{UrsacheArt::Vortrag, static_cast<std::uint16_t>(adresse), 0};
    }

    /// `Jahrgang` -- der Wert kommt aus den Sollreihen des Pruefjahrgangs.
    [[nodiscard]] static constexpr Ursache jahrgang() noexcept
    {
        return Ursache{UrsacheArt::Jahrgang, 0, 0};
    }

    [[nodiscard]] constexpr UrsacheArt art() const noexcept { return art_; }

    /// Die Aktionsart 1 bis 5. Bricht ab, wenn diese Ursache keine `Aktion` ist.
    [[nodiscard]] constexpr std::size_t aktionsnummer() const
    {
        verlange(UrsacheArt::Aktion, "kern::schreiber -- diese Ursache ist keine Aktion");
        return erster_;
    }

    /// Das Land eines `Instrument`. Bricht ab bei jeder anderen Form.
    [[nodiscard]] constexpr Gebiet land() const
    {
        verlange(UrsacheArt::Instrument,
                 "kern::schreiber -- ein Land hat nur die Ursache Instrument");
        return static_cast<Gebiet>(static_cast<std::uint8_t>(erster_));
    }

    /// Das Politikinstrument eines `Instrument`. Bricht ab bei jeder anderen Form.
    [[nodiscard]] constexpr Instrument politikinstrument() const
    {
        verlange(UrsacheArt::Instrument,
                 "kern::schreiber -- ein Instrument hat nur die Ursache Instrument");
        return static_cast<Instrument>(static_cast<std::uint8_t>(zweiter_));
    }

    /// Die Nummer der Gegenkraft, 1 bis 5. Bricht ab bei jeder anderen Form.
    [[nodiscard]] constexpr std::size_t gegenkraftart() const
    {
        verlange(UrsacheArt::Gegenkraft,
                 "kern::schreiber -- diese Ursache ist keine Gegenkraft");
        return erster_;
    }

    /// Der Sektor einer `Marktraeumung`. Bricht ab bei jeder anderen Form.
    [[nodiscard]] constexpr Sektor sektor() const
    {
        verlange(UrsacheArt::Marktraeumung,
                 "kern::schreiber -- einen Sektor hat nur die Ursache Marktraeumung");
        // Der Versatz zaehlt ab null, die Aufzaehlung wie die Adresse ab eins.
        return static_cast<Sektor>(static_cast<std::uint8_t>(erster_ + 1));
    }

    /// Die Adresse, aus der vorgetragen wurde. Bricht ab bei jeder anderen Form.
    [[nodiscard]] constexpr Index vortragsadresse() const
    {
        verlange(UrsacheArt::Vortrag, "kern::schreiber -- diese Ursache ist kein Vortrag");
        return erster_;
    }

    constexpr bool operator==(const Ursache&) const = default;

private:
    constexpr Ursache(UrsacheArt art, std::uint16_t erster, std::uint16_t zweiter) noexcept
        : art_(art), erster_(erster), zweiter_(zweiter)
    {
    }

    constexpr void verlange(UrsacheArt erwartet, const char* grund) const
    {
        if (art_ != erwartet) {
            festkomma::abbruch(grund);
        }
    }

    UrsacheArt art_ = UrsacheArt::Jahrgang;
    std::uint16_t erster_ = 0;
    std::uint16_t zweiter_ = 0;
};

// ---------------------------------------------------------------------------
// T18 -- der Ursachensatz, genau die sieben Felder der Tabelle
// ---------------------------------------------------------------------------

/// Ein Glied der Kette: was in dieser Runde an dieser Adresse geschah und warum.
///
/// Die sieben Felder stehen unter den Namen aus der Tabelle in T18 und in ihrer
/// Reihenfolge. Ein achtes gibt es nicht, auch kein nuetzliches: Wer die Tabelle
/// danebenlegt und abzaehlt, muss auf dieselbe Menge kommen.
struct Ursachensatz {
    /// In welcher Runde geschrieben.
    i64 runde = 0;
    /// Adresse nach T17, in ihrer Maschinenform `0 ... 309`.
    Index ziel = 0;
    /// Der Wert am Ende der Vorrunde, in der Skala der Groesse.
    i64 alt = 0;
    /// Der Wert dieser Runde, in derselben Skala.
    i64 neu = 0;
    /// Welche der sechs Formen aus T18 die Aenderung ausgeloest hat.
    Ursache ursache{};
    /// Wie viele Runden zwischen Ursache und Wirkung lagen.
    i64 verzoegerung = 0;
    /// Anteil dieser Ursache an der Aenderung, in Promille.
    i64 beitrag = 0;

    constexpr bool operator==(const Ursachensatz&) const = default;
};

// ---------------------------------------------------------------------------
// T19 -- die Kette der Runde
// ---------------------------------------------------------------------------

/// Die Aufnahmekapazitaet der Kette je Runde.
///
/// **Die Zahl ist hergeleitet und nicht geschaetzt:** Nach T18 wird jede Adresse je
/// Runde hoechstens einmal geschrieben, und jeder Schreibzugriff haengt genau einen
/// Ursachensatz an; bei 310 Adressen kann eine Rundenkette deshalb nie mehr als 310
/// Glieder haben. Die Kapazitaetspruefung liegt damit hinter dem Bitfeld -- sie ist
/// die zweite Sperre und nicht die erste.
inline constexpr std::size_t KETTE_KAPAZITAET = FELDER;

/// Die Ursachensaetze einer Runde, in der Reihenfolge ihres Entstehens.
///
/// Behaelter fester Groesse mit fester Reihenfolge (T9): Was hier hineinkommt, kommt
/// in der Reihenfolge der Schreibzugriffe wieder heraus, in jedem Lauf gleich. Die
/// Kette gehoert nach T19 **nicht** in den Zustand -- der bleibt bei 310 Feldern und
/// 2.480 Byte; die Sitzung sammelt die Ketten in einem `Verlauf`, und der ist nicht
/// in diesem Kasten.
class Kette {
public:
    [[nodiscard]] constexpr std::size_t laenge() const noexcept { return laenge_; }

    [[nodiscard]] constexpr const Ursachensatz& eintrag(std::size_t nummer) const
    {
        if (nummer >= laenge_) {
            festkomma::abbruch("kern::schreiber -- Kettenglied ausserhalb der Kette");
        }
        return satz_[nummer];
    }

    /// Haengt ein Glied an. **Ist die Kapazitaet erreicht, ist das ein harter Fehler
    /// und keine stille Kuerzung** (T19) -- eine gekuerzte Kette waere eine Luege
    /// gegenueber dem Kaeufer.
    constexpr void anhaengen(const Ursachensatz& satz)
    {
        if (laenge_ >= KETTE_KAPAZITAET) {
            festkomma::abbruch("kern::schreiber -- die Kette dieser Runde ist voll");
        }
        satz_[laenge_] = satz;
        ++laenge_;
    }

private:
    std::array<Ursachensatz, KETTE_KAPAZITAET> satz_{};
    std::size_t laenge_ = 0;
};

// ---------------------------------------------------------------------------
// T38 -- die Sollmasken
// ---------------------------------------------------------------------------
//
// Die Blocktabelle aus T38, abgeschrieben statt gebildet:
//
//   je spielbarem Land: Sektoren 12, Aggregate 9, Zustimmung 1,
//                       Instrumentenstand 4, basiswechsel 1     -> 27 x 4 = 108   ja
//   je spielbarem Land: Aufsichtszaehler 1, Einfluss 1,
//                       Instrumente ohne Stand 12, Restdauern 3 -> 17 x 4 =  68   nein
//   Restwelt                                                                22    ja
//   Handel                                                                  40    ja
//   Weltpreise                                                               2    ja
//   Nachahmerzaehler                                                        12    nein
//   Marktkorb                                                                2    nein
//   Fonds (Aggregat 5, Ueberrendite 3, Steckplaetze 20, Beteiligungen 24)   52    nein
//   Partie: Runde, Jahrgangskennung, Parametersatz-Pruefsumme                3    ja
//   Partie: Mandatsstand                                                     1    nein

/// Die Maske `weltlauf` umfasst 175 Adressen (`108 + 22 + 40 + 2 + 3`).
inline constexpr std::size_t MASKE_WELTLAUF = 175;

/// Ausserhalb der Maske `weltlauf` liegen 135 Adressen (`68 + 12 + 2 + 52 + 1`).
/// Was ausserhalb liegt, behaelt seinen Startwert -- so verlangt es `spiel.md`.
inline constexpr std::size_t AUSSERHALB_WELTLAUF = 135;

/// Die Maske `spielmodus` umfasst alle 310 Adressen.
inline constexpr std::size_t MASKE_SPIELMODUS = 310;

static_assert(MASKE_WELTLAUF + AUSSERHALB_WELTLAUF == 310,
              "T38: 175 in der Maske, 135 ausserhalb, zusammen die 310 des Zustands");
static_assert(MASKE_SPIELMODUS == FELDER, "T38: im Spielmodus wird jede Adresse geschrieben");
static_assert(108 + 22 + 40 + 2 + 3 == MASKE_WELTLAUF, "T38: die fuenf Bloecke der Maske");
static_assert(68 + 12 + 2 + 52 + 1 == AUSSERHALB_WELTLAUF, "T38: die fuenf Bloecke ausserhalb");

/// Die Sollmaske des Modus: die Menge der Adressen, die in diesem Modus je Runde
/// geschrieben werden (T38).
[[nodiscard]] const Bitfeld& sollmaske(Modus modus);

/// Wie viele Adressen die Sollmaske dieses Modus umfasst.
[[nodiscard]] std::size_t sollmaskengroesse(Modus modus);

// ---------------------------------------------------------------------------
// Der Schreiber
// ---------------------------------------------------------------------------

/// Der einzige Schreibweg in den Zustand (T18).
///
/// Ein Schreiber gehoert **einer** Runde. Er bekommt den Zustand am Ende der Vorrunde,
/// haelt ihn unveraendert als `alt` und den entstehenden als `neu`, und gibt am
/// Rundenende beides heraus: den fertigen Zustand und die Kette dieser Runde. Fuer die
/// naechste Runde entsteht ein neuer Schreiber -- ein Zuruecksetzen gibt es nicht, weil
/// ein halb zurueckgesetzter Schreiber genau der Zustand waere, in dem die Zusagen
/// dieses Kastens nicht mehr gelten.
///
/// `neu` beginnt als Abschrift von `alt`. Das ist die Bauweise, die T38 verlangt: Was
/// ausserhalb der Sollmaske liegt, behaelt seinen Startwert. Auf das Leserecht wirkt
/// die Abschrift nicht -- `lies_neu` entscheidet am Bitfeld und nicht am Wert.
class Schreiber {
public:
    /// `vorrunde` ist der Zustand am Ende der Vorrunde, in Runde 1 der Startzustand
    /// des Jahrgangs.
    Schreiber(const Zustand& vorrunde, Modus welcher_modus, i64 welche_runde);

    /// Der einzige Schreibzugriff (T18). Haengt einen Ursachensatz an die Kette.
    ///
    /// Zwei harte Fehler, beide ohne Ersatzwert:
    ///   * Die Adresse liegt ausserhalb `0 ... 309`.
    ///   * Die Adresse wurde in dieser Runde **schon** geschrieben. Der Abbruch nennt
    ///     sie im Wortlaut, damit der Befund die Stelle traegt und nicht nur die Zahl.
    ///
    /// `verzoegerung` ist die Zahl der Runden zwischen Ursache und Wirkung und deshalb
    /// nie negativ; eine Wirkung vor ihrer Ursache ist kein Sonderfall, sondern ein
    /// Rechenfehler des Aufrufers. `beitrag` ist der Anteil dieser Ursache an der
    /// Aenderung in Promille und bleibt ungeprueft: T18 nennt dafuer keine Schranke,
    /// und eine erfundene waere eine Vorgabe, die nicht in `specs/` steht.
    void setze(Index adresse, i64 wert, Ursache ursache, i64 verzoegerung, i64 beitrag);

    /// Schreibt die Groesse unveraendert fort, mit der Ursache `Vortrag` auf sich
    /// selbst (T18).
    ///
    /// Eine Adresse, die sich nicht aendert, wird trotzdem geschrieben --
    /// "unveraendert" ist eine Aussage und keine Luecke. Verzoegerung null und Beitrag
    /// 1.000 Promille, weil der Vortrag die Groesse in dieser Runde vollstaendig
    /// erklaert. Das ist eine Abkuerzung ueber `setze` und keine siebte Ursachenform.
    void vortrag(Index adresse);

    /// Der Wert am Ende der Vorrunde. Immer verfuegbar (T39).
    [[nodiscard]] i64 lies_alt(Index adresse) const;

    /// Der Wert dieser Runde. **Ist die Adresse in dieser Runde noch nicht geschrieben,
    /// ist das ein harter Fehler** (T39), kein stiller Rueckgriff auf `alt`.
    [[nodiscard]] i64 lies_neu(Index adresse) const;

    /// Ob diese Adresse in dieser Runde schon geschrieben wurde. Die Frage ist erlaubt;
    /// nur die Antwort "dann eben `alt`" ist es nicht.
    [[nodiscard]] bool ist_geschrieben(Index adresse) const;

    [[nodiscard]] Modus modus() const noexcept { return modus_; }
    [[nodiscard]] i64 runde() const noexcept { return runde_; }

    /// Die Kette dieser Runde, in der Reihenfolge der Schreibzugriffe (T19).
    [[nodiscard]] const Kette& kette() const noexcept { return kette_; }

    /// Wie viele Adressen in dieser Runde bisher geschrieben wurden.
    [[nodiscard]] std::size_t geschriebene() const noexcept;

    /// Die zweiseitige Rundenendpruefung aus T38, danach der entstandene Zustand.
    ///
    /// Geprueft wird beides, und beides ist ein harter Fehler und kein Bericht:
    ///   1. Jede Adresse der Sollmaske ist genau einmal geschrieben.
    ///   2. Keine Adresse ausserhalb der Sollmaske ist beruehrt.
    /// Die erste fehlende und die erste ueberzaehlige Adresse stehen im Wortlaut in der
    /// Fehlermeldung.
    [[nodiscard]] const Zustand& rundenende() const;

private:
    Zustand alt_;
    Zustand neu_;
    Bitfeld geschrieben_;
    Kette kette_;
    Modus modus_;
    i64 runde_;
};

}  // namespace kern::schreiber
