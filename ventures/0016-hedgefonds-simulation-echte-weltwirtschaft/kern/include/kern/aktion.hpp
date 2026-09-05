#pragma once
//! `kern::aktion` -- der Aktionstyp und die kanonische Ordnung.
//!
//! Vorgaben: T32 (die Liste der zulaessigen Aktionen hat eine kanonische Ordnung, und
//! sie ist Teil der Schnittstellenversion; sortiert wird nach Aktionsart, Zielkennung
//! und Stufe), T9 (feste Reihenfolge, eigene Indextypen statt eines blanken Zaehltyps,
//! und die Warnung vor einer Sortierung mit Gleichstaenden), T35 (Mass 1 zieht ohne
//! Zuruecklegen aus dieser Liste), T7 und ADR 0011 (Ganzzahlarithmetik, kein
//! Gleitkomma). Die fuenf Arten und ihre Kennungen 1 bis 5 stehen in `spiel.md`,
//! Abschnitt "Die Aktionen".
//!
//! Gelesene Fassung von T32: Stand `1f763e9`.
//!
//! ## Warum die Ordnung eine benannte Eigenschaft ist und keine Nebenwirkung
//!
//! T32 nennt den Grund selbst: Mass 1 zieht Aktionen ohne Zuruecklegen aus der Liste
//! der in dieser Runde zulaessigen Aktionen. Waere ihre Reihenfolge das Ergebnis der
//! Schleife, die sie erzeugt, haenge die gemessene Entscheidungsdichte an einer
//! Reihenfolge, die niemand aufgeschrieben hat -- ein spaeterer Umbau der
//! Erzeugungsschleife aenderte dann eine Messgroesse, ohne eine Regel zu aendern. Die
//! Ordnung zu aendern entwertet den Regressionsbestand und braucht nach T32 einen ADR;
//! das gilt nur fuer eine Ordnung, die man ueberhaupt benennen kann.
//!
//! Gebaut ist sie deshalb dreifach benannt und an keiner Stelle beilaeufig:
//!
//!   1. `Schluessel` zaehlt die drei Ordnungsschluessel aus T32 auf, und der Wert eines
//!      Eintrags **ist** sein Rang: 0 ist der staerkste, 2 der schwaechste.
//!   2. `schluesselwert` gibt den Wert eines benannten Schluessels heraus. Wer ordnet,
//!      nennt also den Schluessel und nicht ein Feld.
//!   3. `ordnungsvergleich` laeuft ueber die Raenge 0, 1, 2 und vergleicht nichts
//!      anderes. Es ist die einzige Stelle des Kastens, die zwei Aktionen ordnet;
//!      `operator<=>` und `operator==` laufen ueber sie und nicht daneben.
//!
//! Damit laesst sich die Rangfolge pruefen, statt sie zu glauben: Die Zusicherungen
//! weiter unten zeigen beim Uebersetzen, dass ein Unterschied im staerkeren Schluessel
//! jeden gegenlaeufigen Unterschied in den schwaecheren ueberwiegt -- gerechnet an den
//! Raendern des Wertebereichs und nicht an Beispielzahlen.
//!
//! Die Feldreihenfolge im Verbund `Aktion` ist dieselbe. Sie ist die Lesehilfe und
//! **nicht** der Traeger der Ordnung: Ein vorgegebener Vergleich ueber die
//! Feldreihenfolge stuende und fiele mit der Reihenfolge der Zeilen, und genau das ist
//! die Nebenwirkung, gegen die T32 geschrieben ist.
//!
//! ## Was hier nicht steht -- und eine Luecke, die gemeldet und nicht geraten ist
//!
//! **Die Zulaessigkeit eines Buendels gehoert nicht hierher.** Derselbe Steckplatz
//! zweimal, Kasse ueberzogen, mehr als drei Aktionen, dazu die beiden Bedingungen aus
//! der Anteilsskala -- das ist die zweite Haelfte von T32 und ein eigenes Paket auf
//! denselben drei Dateien. Dieser Kasten ordnet; er entscheidet nicht, was in die Liste
//! hineingehoert.
//!
//! **Der Wertebereich der Zielkennung je Aktionsart fehlt in den Vorgaben, und er wird
//! hier nicht nachgeliefert.** T32 sagt, wonach sortiert wird, und dass die Zielkennung
//! die feste Indexordnung aus T9 ist. Welche Menge sie je Art durchlaeuft, sagt weder
//! T32 noch T9 noch der gebaute Kern -- fuer die Arten 4 und 5 fuehrt der Zustand
//! ueberhaupt kein Ziel, sondern je eine einzelne Fondsgroesse. Eine hier
//! hingeschriebene Zuordnung waere geraten, und eine geratene Ordnung bindet den
//! Regressionsbestand, ohne dass jemand sie beschlossen haette. `Zielkennung` ist
//! deshalb der Platz in einer T9-Ordnung und sonst nichts; welche Ordnung das je Art
//! ist, gehoert in die Vorgabe und danach in ein Paket. Der Bericht zu diesem Lauf
//! meldet die Luecke.
//!
//! **Kein Eingriff in `kern::schritt`.** Der leere Aktionsbuendeltyp dort bleibt, wo er
//! ist. Ihn durch diesen Typ zu ersetzen ist eine Entscheidung ueber die Signatur aus
//! T10, und die trifft kein Bauagent.

#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"

namespace kern::aktion {

using i64 = std::int64_t;

// ---------------------------------------------------------------------------
// Die fuenf Arten
// ---------------------------------------------------------------------------

/// Die fuenf Aktionsarten mit ihren Kennungen aus `spiel.md`, Abschnitt
/// "Die Aktionen": dort sind die Kennungen 1 bis 5 zugleich die Gleichstandsordnung
/// aller Masse, und genau diese Zahlen sind der staerkste Ordnungsschluessel aus T32.
///
/// Die Nummern stehen ausgeschrieben und werden nicht vom Uebersetzer vergeben. Der
/// Grund ist derselbe wie bei den Reihenfolgen im Zustand: Wer einen Eintrag
/// einschiebt, verschiebt bei vergebenen Nummern stillschweigend alles dahinter -- und
/// hier verschoebe er eine Ordnung, die Teil der Schnittstellenversion ist.
///
/// Es faengt bei eins an und nicht bei null, weil die Kennung in der Vorgabe bei eins
/// anfaengt. Wer die Art als Feldversatz braucht, rechnet ihn aus der Kennung.
enum class Art : std::uint8_t {
    Position = 1,
    Beteiligung = 2,
    Lobbybudget = 3,
    Hebel = 4,
    Sichtbarkeit = 5,
};

/// Wie viele Arten es gibt. T32 nennt sie als Bereich 1 bis 5.
inline constexpr std::size_t ARTEN = 5;

inline constexpr std::uint8_t ART_KENNUNG_ERSTE = 1;
inline constexpr std::uint8_t ART_KENNUNG_LETZTE = 5;

static_assert(ART_KENNUNG_LETZTE - ART_KENNUNG_ERSTE + 1 == ARTEN,
              "T32: die Kennungen 1 bis 5 sind luecklos");

/// Ob `art` eine der fuenf ist. Ein Wert daneben entsteht nur durch eine Umwandlung
/// aus einer Zahl, und die hat genau eine erlaubte Stelle: `art_der_kennung`.
[[nodiscard]] constexpr bool art_bekannt(Art art) noexcept
{
    const std::uint8_t kennung = static_cast<std::uint8_t>(art);
    return kennung >= ART_KENNUNG_ERSTE && kennung <= ART_KENNUNG_LETZTE;
}

/// Die Kennung 1 bis 5 einer Art -- die Zahl, die T22 in einem Speicherstand ablegt
/// und die T32 als staerksten Ordnungsschluessel nimmt.
[[nodiscard]] constexpr i64 art_kennung(Art art)
{
    if (!art_bekannt(art)) {
        festkomma::abbruch("kern::aktion -- unbekannte Aktionsart; T32 kennt die "
                           "Kennungen 1 bis 5");
    }
    return static_cast<i64>(static_cast<std::uint8_t>(art));
}

// ---------------------------------------------------------------------------
// Die Zielkennung -- der Platz des Ziels in einer T9-Ordnung
// ---------------------------------------------------------------------------

/// Der zweitstaerkste Ordnungsschluessel aus T32.
///
/// Ein Huellentyp und kein blanker Zaehltyp, weil T9 genau das verlangt: Zwei
/// Indexarten sollen sich nicht stillschweigend vermischen. Eine Zielkennung ist keine
/// Stufe und kein Feldplatz im Zustand, und der Uebersetzer haelt das auseinander,
/// statt es einem Kommentar zu ueberlassen.
///
/// **Was der Typ zusagt und was nicht.** Er sagt zu, dass sein Wert der Platz in einer
/// festen Indexordnung nach T9 ist und dass aufsteigende Werte aufsteigende Plaetze
/// sind -- mehr braucht T32 fuer die Ordnung nicht. Er sagt **nicht** zu, welche
/// Ordnung das je Aktionsart ist; das steht in keiner Vorgabe (siehe den Kopf oben).
struct Zielkennung {
    std::uint16_t wert = 0;

    [[nodiscard]] constexpr auto operator<=>(const Zielkennung&) const noexcept = default;
};

/// Der groesste Platz, den eine Zielkennung tragen kann.
///
/// Er ist die Grenze des Traegertyps und **keine** Aussage ueber die Groesse einer
/// Zielmenge -- die kennt dieser Kasten nicht. Zwei Bytes reichen mit weitem Abstand:
/// Die groesste heute im Kern gefuehrte Indexordnung hat 310 Eintraege.
inline constexpr std::uint16_t ZIELKENNUNG_MAX = 65535;

/// Bildet eine Zielkennung aus einem Platz. Ein Platz jenseits des Wertebereichs
/// bricht ab, statt oben umzulaufen -- ein umgelaufener Platz waere ein gueltiger, und
/// eine Ordnung darueber waere still falsch.
[[nodiscard]] constexpr Zielkennung zielkennung(std::size_t platz)
{
    if (platz > ZIELKENNUNG_MAX) {
        festkomma::abbruch("kern::aktion -- Zielkennung ausserhalb ihres Wertebereichs");
    }
    return Zielkennung{static_cast<std::uint16_t>(platz)};
}

// ---------------------------------------------------------------------------
// Die drei Ordnungsschluessel aus T32 und die Aktion
// ---------------------------------------------------------------------------

/// Die drei Ordnungsschluessel, und ihr Wert ist ihr Rang.
///
/// `Aktionsart` ist Rang 0 und damit der staerkste, `Stufe` ist Rang 2 und der
/// schwaechste. Die Namen sind die aus T32.
enum class Schluessel : std::uint8_t {
    Aktionsart = 0,
    Zielkennung = 1,
    Stufe = 2,
};

/// Wie viele Ordnungsschluessel es gibt. T32 nennt drei.
inline constexpr std::size_t SCHLUESSEL = 3;

/// Eine einzelne Aktion: Art, Ziel und Stufe.
///
/// Die drei Felder stehen in der Rangfolge aus T32, und das ist die Lesehilfe. Der
/// Traeger der Ordnung ist `ordnungsvergleich` (siehe den Kopf oben).
///
/// **Zwei Aktionen sind genau dann gleich, wenn alle drei Schluessel gleich sind**, und
/// der Verbund traegt nichts ausser diesen dreien. Gleichheit und Wesensgleichheit
/// fallen damit zusammen, und das ist die Antwort auf die Warnung aus T9 vor einer
/// Sortierung mit Gleichstaenden: Ein Gleichstand in dieser Ordnung ist kein Paar
/// unterscheidbarer Eintraege, deren Reihenfolge der Uebersetzer waehlt, sondern
/// zweimal derselbe Eintrag.
struct Aktion {
    /// Rang 0 -- die Aktionsart mit ihrer Kennung 1 bis 5.
    Art art = Art::Position;
    /// Rang 1 -- der Platz des Ziels in seiner T9-Ordnung.
    Zielkennung ziel{};
    /// Rang 2 -- die Stufe, vorzeichenbehaftet.
    i64 stufe = 0;
};

// Der Verbund traegt die drei Schluessel und sonst nichts. Daran haengt die Aussage
// ueber die Gleichheit oben: Kaeme ein viertes Feld dazu, waeren zwei in allen drei
// Schluesseln gleiche Aktionen unterscheidbar, und ihre Reihenfolge haenge wieder am
// Sortierverfahren statt an T32.
static_assert(sizeof(Aktion) <= 16,
              "T32: eine Aktion traegt die drei Ordnungsschluessel und sonst nichts");

/// Der Wert des Schluessels `schluessel` dieser Aktion.
///
/// Alle drei passen in `i64`: die Kennung ist 1 bis 5, die Zielkennung ist ein
/// vorzeichenloser Zwei-Byte-Platz, und die Stufe ist selbst ein `i64`. Damit vergleicht
/// `ordnungsvergleich` drei Zahlen desselben Typs und braucht keine Fallunterscheidung.
///
/// Zwei harte Fehler, beide ohne Ersatzwert: eine Aktionsart ausserhalb 1 bis 5 und ein
/// Schluessel, den T32 nicht kennt.
[[nodiscard]] constexpr i64 schluesselwert(const Aktion& eintrag, Schluessel schluessel)
{
    switch (schluessel) {
    case Schluessel::Aktionsart:
        return art_kennung(eintrag.art);
    case Schluessel::Zielkennung:
        return static_cast<i64>(eintrag.ziel.wert);
    case Schluessel::Stufe:
        return eintrag.stufe;
    }
    festkomma::abbruch("kern::aktion -- unbekannter Ordnungsschluessel; T32 kennt drei: "
                       "Aktionsart, Zielkennung, Stufe");
}

/// Der Schluessel des Ranges `rang`, 0 bis 2. Ein Rang daneben bricht ab.
[[nodiscard]] constexpr Schluessel schluessel_des_ranges(std::size_t rang)
{
    if (rang >= SCHLUESSEL) {
        festkomma::abbruch("kern::aktion -- Rang ausserhalb der drei Ordnungsschluessel "
                           "aus T32");
    }
    return static_cast<Schluessel>(static_cast<std::uint8_t>(rang));
}

/// Der kanonische Vergleich aus T32: negativ, null oder positiv.
///
/// Die einzige Stelle des Kastens, die zwei Aktionen ordnet. Sie laeuft ueber die
/// Raenge 0, 1, 2 und liest je Rang den benannten Schluessel -- nicht ein Feld, nicht
/// eine Zeile, nicht eine Reihenfolge, die sich beim Umbau des Verbundes mitverschiebt.
[[nodiscard]] constexpr int ordnungsvergleich(const Aktion& links, const Aktion& rechts)
{
    for (std::size_t rang = 0; rang < SCHLUESSEL; ++rang) {
        const Schluessel schluessel = schluessel_des_ranges(rang);
        const i64 hier = schluesselwert(links, schluessel);
        const i64 dort = schluesselwert(rechts, schluessel);
        if (hier < dort) {
            return -1;
        }
        if (dort < hier) {
            return 1;
        }
    }
    return 0;
}

/// Die Ordnung als Operator -- und zwar ueber `ordnungsvergleich`, damit es bei einer
/// Stelle bleibt. Sie ist streng und vollstaendig: Von zwei Aktionen ist genau eine
/// kleiner, groesser oder gleich der anderen.
[[nodiscard]] constexpr std::strong_ordering operator<=>(const Aktion& links,
                                                         const Aktion& rechts)
{
    const int urteil = ordnungsvergleich(links, rechts);
    if (urteil < 0) {
        return std::strong_ordering::less;
    }
    if (urteil > 0) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

[[nodiscard]] constexpr bool operator==(const Aktion& links, const Aktion& rechts)
{
    return ordnungsvergleich(links, rechts) == 0;
}

// ---------------------------------------------------------------------------
// Die Rangfolge, beim Uebersetzen nachgewiesen
// ---------------------------------------------------------------------------
//
// Die vier Zusicherungen unten sind der mechanische Nachweis fuer die Rangfolge aus
// T32. Gerechnet wird an den Raendern des Wertebereichs und nicht an bequemen
// Beispielzahlen: Der staerkere Schluessel gewinnt gegen den denkbar groessten
// gegenlaeufigen Unterschied in den schwaecheren, nicht nur gegen einen kleinen.
//
// Sie sind der Grund, aus dem eine vertauschte Rangfolge hier nicht gruen uebersetzt.
// Eine Probe faende sie auch, aber erst beim Laufen -- und eine Ordnung, die Teil der
// Schnittstellenversion ist, soll am Uebersetzer haengen und nicht am Testlauf.

static_assert(ordnungsvergleich(Aktion{Art::Position, Zielkennung{ZIELKENNUNG_MAX},
                                       festkomma::I64_MAX},
                                Aktion{Art::Beteiligung, Zielkennung{0},
                                       festkomma::I64_MIN})
                  < 0,
              "T32 Rang 0: die Aktionsart ueberwiegt Zielkennung und Stufe zusammen");

static_assert(ordnungsvergleich(Aktion{Art::Sichtbarkeit, Zielkennung{0},
                                       festkomma::I64_MIN},
                                Aktion{Art::Hebel, Zielkennung{ZIELKENNUNG_MAX},
                                       festkomma::I64_MAX})
                  > 0,
              "T32 Rang 0: und in der Gegenrichtung ebenso");

static_assert(ordnungsvergleich(Aktion{Art::Position, Zielkennung{0}, festkomma::I64_MAX},
                                Aktion{Art::Position, Zielkennung{1}, festkomma::I64_MIN})
                  < 0,
              "T32 Rang 1: die Zielkennung ueberwiegt die Stufe");

static_assert(ordnungsvergleich(Aktion{Art::Position, Zielkennung{7}, i64{-1}},
                                Aktion{Art::Position, Zielkennung{7}, i64{-1}})
                  == 0,
              "T32: gleich in allen drei Schluesseln heisst gleich");

// Und die Gegenprobe zur Feldreihenfolge: Waere die Ordnung die des schwaechsten
// Schluessels zuerst -- der Fall, den eine unbedachte Erzeugungsschleife hinterlaesst
// --, dann stuende das Paar unten andersherum.
static_assert(ordnungsvergleich(Aktion{Art::Sichtbarkeit, Zielkennung{0}, i64{-9}},
                                Aktion{Art::Position, Zielkennung{0}, i64{9}})
                  > 0,
              "T32: nach der Stufe zuerst zu ordnen ist genau die Nebenwirkung, gegen "
              "die die Vorgabe geschrieben ist");

// ---------------------------------------------------------------------------
// Eine Folge von Aktionen in die kanonische Ordnung bringen
// ---------------------------------------------------------------------------

/// Bringt die ersten `anzahl` Eintraege von `liste` in die kanonische Ordnung.
///
/// **Ein Behaelter fester Groesse ohne Zuteilung**, wie jeder Behaelter des Kerns; die
/// Kapazitaet bringt der Aufrufer mit, weil dieser Kasten die Laenge einer
/// Zulaessigkeitsliste nicht kennt und sie nicht raten soll.
///
/// **Das Verfahren ist Einfuegen und nicht die Sortierung der Standardbibliothek.**
/// T9 warnt ausdruecklich: Eine nicht stabile Sortierung mit Gleichstaenden ist eine
/// Reihenfolge, die der Uebersetzer waehlt. Einfuegen ist stabil, kommt ohne Zuteilung
/// aus und braucht keinen fremden Kopf. Ein Gleichstand ist hier ohnehin zweimal
/// derselbe Eintrag (siehe `Aktion`) -- die Stabilitaet ist der Guertel zum Hosentraeger,
/// und sie kostet nichts.
///
/// Harter Fehler: `anzahl` groesser als die Kapazitaet. Danach ist jeder Zugriff der
/// Schleife innerhalb der Grenze, und zwar nachrechenbar und nicht nur beabsichtigt.
template <std::size_t N>
constexpr void ordne(std::array<Aktion, N>& liste, std::size_t anzahl)
{
    if (anzahl > N) {
        festkomma::abbruch("kern::aktion::ordne -- mehr Eintraege angesagt, als die "
                           "Liste fasst");
    }
    for (std::size_t k = 1; k < anzahl; ++k) {
        const Aktion eintrag = liste[k];
        std::size_t platz = k;
        while (platz > 0 && ordnungsvergleich(liste[platz - 1], eintrag) > 0) {
            liste[platz] = liste[platz - 1];
            --platz;
        }
        liste[platz] = eintrag;
    }
}

/// Ob die ersten `anzahl` Eintraege in der kanonischen Ordnung stehen.
///
/// Die Frage, die eine Probe stellt und die ein Aufrufer stellen darf, statt sie am
/// Ergebnis zu erraten. Harter Fehler wie bei `ordne`: `anzahl` groesser als die
/// Kapazitaet.
template <std::size_t N>
[[nodiscard]] constexpr bool in_kanonischer_ordnung(const std::array<Aktion, N>& liste,
                                                    std::size_t anzahl)
{
    if (anzahl > N) {
        festkomma::abbruch("kern::aktion::in_kanonischer_ordnung -- mehr Eintraege "
                           "angesagt, als die Liste fasst");
    }
    for (std::size_t k = 1; k < anzahl; ++k) {
        if (ordnungsvergleich(liste[k - 1], liste[k]) > 0) {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Die Namen und der Weg von der Zahl zur Art
// ---------------------------------------------------------------------------

/// Die Art zu einer Kennung 1 bis 5 -- der eine erlaubte Weg von einer Zahl zu einer
/// `Art`. Eine Zahl daneben bricht ab, und die Meldung nennt sie.
///
/// Gebraucht wird er ueberall dort, wo eine Aktion als Zahl ankommt statt als Typ: in
/// einem Speicherstand nach T22 und in der Maschinenschnittstelle nach T21.
[[nodiscard]] Art art_der_kennung(i64 kennung);

/// Der Name einer Art, wie ihn `spiel.md`, Abschnitt "Die Aktionen" fuehrt. Ein Wert
/// ausserhalb 1 bis 5 bricht ab.
[[nodiscard]] const char* art_name(Art art);

/// Der Name eines Ordnungsschluessels, wie ihn T32 fuehrt. Ein Wert daneben bricht ab.
[[nodiscard]] const char* schluessel_name(Schluessel schluessel);

}  // namespace kern::aktion
