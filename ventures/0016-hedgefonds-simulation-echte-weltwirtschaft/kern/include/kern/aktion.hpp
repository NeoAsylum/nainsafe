#pragma once
//! `kern::aktion` -- der Aktionstyp und die kanonische Ordnung.
//!
//! Vorgaben: T32 (die Liste der zulaessigen Aktionen hat eine kanonische Ordnung, und
//! sie ist Teil der Schnittstellenversion; sortiert wird nach Aktionsart, Zielkennung
//! und Stufe), T9 (feste Reihenfolge, eigene Indextypen statt eines blanken Zaehltyps,
//! und die Warnung vor einer Sortierung mit Gleichstaenden), T35 (Mass 1 zieht ohne
//! Zuruecklegen aus dieser Liste), T7 und ADR 0011 (Ganzzahlarithmetik, kein
//! Gleitkomma). Die fuenf Arten und ihre Kennungen 1 bis 5 stehen in `spiel.md`,
//! Abschnitt "The actions".
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
//! ## Die Liste und die Buendelpruefung, und was von den frueheren Luecken bleibt
//!
//! Zwei Saetze standen hier, solange dieser Kasten nur ordnete. Beide sind mit ihrem
//! Grund fortgefallen, und zwar nicht durch eine Meinung, sondern durch eine Vorgabe:
//!
//!   * **Der Wertebereich der Zielkennung je Aktionsart** fehlte in den Vorgaben und
//!     durfte hier nicht geraten werden. T32b fuellt die Luecke: je Art die Menge, die
//!     ihre Zielkennung durchlaeuft, und je Menge die Indexordnung aus T9, in der sie
//!     laeuft. `zielmenge` rechnet die fuenf Groessen aus den Konstanten des Zustands
//!     aus, statt sie hinzuschreiben -- ein fuenftes Land bewegt damit die Zahl und die
//!     Zusicherung darueber zugleich.
//!   * **Die Zulaessigkeit eines Buendels** gehoerte einem eigenen Paket, und dieses ist
//!     es. Den Ort nennt T32b selbst: Geprueft wird der Wertebereich dort, wo die Liste
//!     **erzeugt** wird, und erzeugt wird sie gegen den Zustand.
//!
//! **Zwei Luecken bleiben, beide gemeldet und keine geraten** -- ausgeschrieben stehen
//! sie unten bei `buendel_einwand` und bei `kassenbedarf`: die fuenfte Bedingung aus
//! T32, der die Groessenschranke der Stufenzahl als Parameterfeld fehlt, und der
//! Kassenanspruch der Arten 1, 2 und 4, den keine Vorgabe beziffert.
//!
//! **Kein Eingriff in `kern::schritt`.** Der leere Aktionsbuendeltyp dort bleibt, wo er
//! ist. Ihn durch diesen Typ zu ersetzen ist eine Entscheidung ueber die Signatur aus
//! T10, und die trifft kein Bauagent.

#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

namespace kern::aktion {

using i64 = std::int64_t;

// ---------------------------------------------------------------------------
// Die fuenf Arten
// ---------------------------------------------------------------------------

/// Die fuenf Aktionsarten mit ihren Kennungen aus `spiel.md`, Abschnitt
/// "The actions": dort sind die Kennungen 1 bis 5 zugleich die Gleichstandsordnung
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

/// Der Name einer Art, wie ihn `spiel.md`, Abschnitt "The actions" fuehrt. Ein Wert
/// ausserhalb 1 bis 5 bricht ab.
[[nodiscard]] const char* art_name(Art art);

/// Der Name eines Ordnungsschluessels, wie ihn T32 fuehrt. Ein Wert daneben bricht ab.
[[nodiscard]] const char* schluessel_name(Schluessel schluessel);

// ---------------------------------------------------------------------------
// T32b -- die fuenf Zielmengen, aus den Konstanten gerechnet
// ---------------------------------------------------------------------------

/// Wie viele Plaetze die Zielkennung der Art `art` durchlaeuft (T32b).
///
/// **Keine der fuenf Zahlen steht hier.** T32b nennt je Art eine Formel und daneben
/// ihren heutigen Wert; gebaut ist die Formel. Der Grund steht in T32b selbst: Bei fuenf
/// Laendern werden aus 20, 12 und 16 die Zahlen 25, 15 und 20, und eine hingeschriebene
/// Zahl bliebe daneben stehen, ohne dass etwas abbraeche.
///
/// Die Arten 4 und 5 fuehren im Zustand kein Ziel, sondern je eine einzelne
/// Fondsgroesse. Ihre Menge hat deshalb genau ein Element, und der Platz dieses
/// Elements ist 0 -- nicht "ein beliebiger Wert". T32b sagt auch, warum: Jede Aktion
/// wandert nach T22 in den Speicherstand und damit in die Pruefsumme, und ein
/// ungelesenes Feld mit zwei moeglichen Werten machte aus einer Partie zwei Dateien.
[[nodiscard]] constexpr std::size_t zielmenge(Art art)
{
    switch (art) {
    case Art::Position:
        // Die Positionssteckplaetze aus T16: Sektoren, Waehrungen, Anleihen.
        return zustand::LAENDER * (zustand::SEKTOREN + 2);
    case Art::Beteiligung:
        return zustand::LAENDER * zustand::SEKTOREN;
    case Art::Lobbybudget:
        return zustand::LAENDER * zustand::INSTRUMENTE;
    case Art::Hebel:
    case Art::Sichtbarkeit:
        return 1;
    }
    festkomma::abbruch("kern::aktion::zielmenge -- unbekannte Aktionsart; T32b nennt "
                       "fuenf Zielmengen");
}

// Die Formel der Art 1 und die Steckplatzzahl aus T16 sind dieselbe Groesse, an zwei
// Stellen hergeleitet. Der Zustand rechnet sie ueber die Blockanfaenge nach; hier steht
// sie als Produkt. Laufen die beiden auseinander, uebersetzt dieser Kopf nicht mehr --
// und das ist der Zweck, denn die Ordnung der Art 1 **ist** die Steckplatzordnung.
static_assert(zielmenge(Art::Position) == zustand::STECKPLAETZE,
              "T32b, erste der fuenf Arten: die Zielmenge der Position ist die "
              "Steckplatzmenge aus T16");

/// Wie viele Angebote die Liste einer Runde hoechstens traegt -- die Summe der fuenf
/// Zielmengen.
///
/// **Das ist die Zahl der Plaetze und nicht die der Moeglichkeiten** (T32b). Der
/// dauerhaft leere Waehrungsplatz der USA zaehlt hier mit und wird nie angeboten; die
/// Liste einer Runde ist deshalb um genau eins kuerzer als diese Schranke. Beide Zahlen
/// nebeneinander stehen zu lassen ist Absicht: Der Unterschied ist die Aussage.
inline constexpr std::size_t ANGEBOTE_HOECHSTENS =
    zielmenge(Art::Position) + zielmenge(Art::Beteiligung) + zielmenge(Art::Lobbybudget)
    + zielmenge(Art::Hebel) + zielmenge(Art::Sichtbarkeit);

/// Die Stufe, die ein Eintrag der Liste traegt.
///
/// **Die Liste zaehlt Ziele auf, keine Stufen.** T32 sagt, dass Mass 1 ohne
/// Zuruecklegen aus der Liste der in dieser Runde zulaessigen Aktionen zieht, und dass
/// nach Art, Zielkennung und Stufe sortiert wird -- es sagt nicht, welche Stufen die
/// Liste anbietet. Aufzaehlen liesse sich das auch nicht: Der Wertebereich einer Stufe
/// der Art 1 ist `-stufen_max ... +stufen_max`, und `stufen_max` fehlt im Kern (siehe
/// `buendel_einwand`). Ein Eintrag ist deshalb das **Angebot** -- Art und Ziel -- und
/// traegt an der Stelle der Stufe die Null. Wer aus einem Angebot eine Aktion macht,
/// setzt die Stufe ein; `buendel_zulaessig` prueft danach das Buendel.
inline constexpr i64 STUFE_OFFEN = 0;

/// Die Liste der in einer Runde zulaessigen Angebote, in der kanonischen Ordnung.
///
/// Behaelter fester Groesse ohne Zuteilung, wie jeder Behaelter des Kerns. `anzahl` ist
/// die Laenge, die Groesse des Feldes darueber die Kapazitaet; die beiden sind hier
/// verschieden, und der Unterschied ist der leere Waehrungsplatz.
struct Zulaessigkeitsliste {
    std::array<Aktion, ANGEBOTE_HOECHSTENS> eintrag{};
    std::size_t                             anzahl = 0;
};

/// Die in dieser Runde zulaessigen Angebote, gegen den Zustand zu Rundenbeginn gebaut.
///
/// **Einmal je Runde, nicht nach jeder gesetzten Aktion** (T32): Keine Aktion hat nach
/// `spiel.md` einen Zeitpunkt innerhalb der Runde, und eine Liste, die sich zwischen
/// zwei Steckplaetzen aenderte, fuehrte genau diesen Zeitpunkt ein.
///
/// **Die Ordnung ist gesetzt und nicht gelaufen.** Die Erzeugungsschleife laeuft zwar
/// schon in der Rangfolge aus T32, aber die Ausgabe geht trotzdem durch `ordne`. Das ist
/// der Unterschied, gegen den der ganze Kopf oben geschrieben ist: Waere die Ordnung
/// das Ergebnis der Schleife, verschoebe ein Umbau der Schleife eine Messgroesse, ohne
/// eine Regel zu aendern.
///
/// **Was die beiden Argumente heute tun, gemessen und nicht behauptet: nichts.** T32
/// legt fest, wogegen die Liste gebaut wird, und T32b nennt die fuenf Zielmengen -- und
/// keine der fuenf haengt an einer Zahl des Zustands oder an einem Parameter. Die
/// einzige Ausnahme, die T16 macht, ist der leere Waehrungsplatz, und der ist eine
/// Eigenschaft der Adressordnung und keines Standes. Die beiden Argumente stehen
/// deshalb in der Signatur, weil T32 sie dort verlangt, und sie werden gelesen, sobald
/// eine Vorgabe etwas nennt, das von ihnen abhaengt. Eine Probe haelt diesen Stand
/// fest: Zwei verschiedene Zustaende ergeben heute dieselbe Liste.
[[nodiscard]] Zulaessigkeitsliste zulaessige_aktionen(const zustand::Zustand& z,
                                                      const werte::Konstanten& konst);

// ---------------------------------------------------------------------------
// T32 -- die Pruefung des Buendels
// ---------------------------------------------------------------------------

/// Wie viele Aktionen ein Buendel nach T32 hoechstens tragen darf.
inline constexpr std::size_t BUENDEL_AKTIONEN_HOECHSTENS = 3;

/// Wie viele ein Buendel **fasst** -- eine mehr, als es tragen darf.
///
/// Die beiden Zahlen auseinanderzuhalten ist kein Luxus: Waere die Kapazitaet die
/// Regel, koennte ein zu grosses Buendel gar nicht erst entstehen, und die Bedingung
/// "mehr als drei Aktionen" waere eine Zusage, die keine Eingabe je verletzt -- also
/// eine Pruefung, die nicht rot werden kann. Die eine Reserve reicht, weil die Frage
/// "mehr als drei?" mit dem vierten Eintrag beantwortet ist.
inline constexpr std::size_t BUENDEL_FASST = BUENDEL_AKTIONEN_HOECHSTENS + 1;

/// Die Aktionen einer Runde, als Wert fester Groesse.
struct Buendel {
    std::array<Aktion, BUENDEL_FASST> eintrag{};
    std::size_t                       anzahl = 0;
};

/// Die Obergrenze der Anteilsskala aus T5 Klasse 4 -- Zehntausendstel.
///
/// T32: Eine Aktion 1 oder 2, nach der der Fondsanteil darueber laege, ist unzulaessig.
/// Ein Anteil ueber hundert Prozent ist kein Anteil, und Gegenkraft 1 und der Preisstoss
/// lesen genau diese Zahl.
inline constexpr i64 ANTEIL_HOECHSTENS = 10'000;

/// Warum ein Buendel unzulaessig ist -- oder dass es zulaessig ist.
///
/// Die Zahlen sind ausgeschrieben und werden nicht vom Uebersetzer vergeben, aus
/// demselben Grund wie bei den Aktionsarten: Nach T21 weist die Maschinenschnittstelle
/// einen Befehl mit einem Grund zurueck, und ein Grund, dessen Nummer sich beim
/// Einschieben eines Eintrags verschiebt, ist in einer aufgezeichneten Sitzung ein
/// anderer Grund als gestern.
enum class Einwand : std::uint8_t {
    Keiner              = 0,
    ZuVieleAktionen     = 1,
    NichtAngeboten      = 2,
    ZielDoppelt         = 3,
    KasseUeberzogen     = 4,
    AnteilUeberDerSkala = 5,
};

/// Wie viele Einwaende es gibt, den leeren mitgezaehlt.
inline constexpr std::size_t EINWAENDE = 6;

static_assert(static_cast<std::size_t>(Einwand::AnteilUeberDerSkala) + 1 == EINWAENDE,
              "die Kennungen der Einwaende sind luecklos, und EINWAENDE zaehlt sie");

/// Der Kassenanspruch einer einzelnen Aktion, in Fondsgeld (T5 Klasse 1, US-Cent).
///
/// **Genau eine der fuenf Arten hat einen bezifferten Anspruch, und das ist der Stand
/// der Vorgaben, nicht der des Baus:**
///
///   * **Art 3** -- die Stufe **ist** der Geldbetrag. T50 nennt den Uebergang von
///     Fondsgeld in Lobbydruck mit Namen und sagt, dass er genau an dieser Aktion
///     steht; was er hereinnimmt, sind Cent. Die Richtung ist nach T32b das Vorzeichen
///     der Stufe und kein zweites Ziel, also kostet sie in beide Richtungen dasselbe,
///     und der Anspruch ist der Betrag.
///   * **Art 5** -- keine Vorgabe nennt bei ihr Geld. Anspruch null.
///   * **Arten 1, 2 und 4** -- **die Luecke.** Was eine Positionsstufe, ein
///     Beteiligungsanteil oder ein Hebelschritt an Kasse zieht, steht in keiner Vorgabe:
///     T47 und T48 bewerten, was der Fonds **hat**, nicht was ein Schritt **kostet**,
///     und die Beschreibung der drei Arten nennt keinen Betrag. Geraten wird hier
///     nichts; ihr Anspruch ist heute null, und das ist die gemeldete Luecke und kein
///     Ergebnis. Sie faellt in die nachgiebige Richtung -- eine ungebaute Schranke
///     laesst durch, sie weist nicht ab.
[[nodiscard]] i64 kassenbedarf(const Aktion& eintrag);

/// Der Einwand gegen das Buendel `buendel`, gegen den Zustand zu Rundenbeginn.
///
/// **Die Reihenfolge der Pruefungen ist festgelegt und keine Nebenwirkung**, denn ein
/// Buendel mit zwei Maengeln bekommt genau einen Grund genannt. Geprueft wird von der
/// groebsten Form zur feinsten Rechnung: Zahl der Aktionen, dann ob jede ueberhaupt
/// angeboten ist, dann dasselbe Ziel zweimal, dann die Kasse, zuletzt die Anteilsskala.
///
/// **Dasselbe Ziel zweimal heisst: dieselbe Art und dieselbe Zielkennung**, und die
/// Stufe bleibt dabei ausser Betracht. Genau das ist der Fall, den T32 nennt -- drei
/// Aufstockungen desselben Steckplatzes in einer Runde --, und er waere nicht zu fassen,
/// wenn die Stufe mitzaehlte: Drei verschiedene Stufen sind drei verschiedene Aktionen.
///
/// **Die fuenfte Bedingung aus T32 ist nicht gebaut.** T32 nennt neben dem Fondsanteil
/// eine zweite Bedingung aus der Anteilsskala: unzulaessig ist auch eine Aktion, nach
/// der der Betrag der Stufenzahl eines Steckplatzes ueber `stufen_max` laege. Diese
/// Groesse gibt es im Kern nicht -- `Konstanten` fuehrt sie nicht, und kein Kopf unter
/// den Vorgaben des Kerns nennt sie. Sie steht in der Parameterdatei als Platzhalter und
/// in den Vorgaben mit Klasse und Bedeutung; welchen Weg sie in den Kern nimmt, ist eine
/// Entscheidung ueber `Konstanten` und damit ueber einen anderen Kasten. Ein hier
/// hingeschriebener Wert waere eine Kalibrierung, die niemand beschlossen hat. Das
/// Arbeitspaket zu diesem Lauf nennt die Fundstellen.
[[nodiscard]] Einwand buendel_einwand(const zustand::Zustand& z,
                                      const werte::Konstanten& konst,
                                      const Buendel& buendel);

/// Ob das Buendel zulaessig ist -- dieselbe Pruefung, ohne den Grund.
///
/// Sie laeuft ueber `buendel_einwand` und nicht daneben, aus demselben Grund, aus dem
/// die Vergleichsoperatoren ueber `ordnungsvergleich` laufen: Zwei Fassungen derselben
/// Entscheidung laufen auseinander, und die zweite ist die, der niemand zusieht.
[[nodiscard]] bool buendel_zulaessig(const zustand::Zustand& z,
                                     const werte::Konstanten& konst,
                                     const Buendel& buendel);

/// Der Name eines Einwands. Ein Wert daneben bricht ab.
[[nodiscard]] const char* einwand_name(Einwand einwand);

}  // namespace kern::aktion
