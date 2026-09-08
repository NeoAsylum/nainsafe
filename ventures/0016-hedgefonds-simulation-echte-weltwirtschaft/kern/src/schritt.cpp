//! Die Runde -- die sechs Schritte, die Zuordnungstafel und der Rundeninhalt.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/schritt.hpp`. Hier steht, was nicht in
//! einen Kopf gehoert: die Aufteilung der Sollmaske aus T38 auf die sechs Schritte aus
//! `spiel.md`, samt der Nachrechnung ihrer Groessen, und die Abbrueche im Wortlaut.
//!
//! ## Die Aufteilung ist eine zweite Abschrift derselben Tabelle -- mit Absicht
//!
//! `src/schreiber.cpp` schreibt die Blocktabelle aus T38 **nach Bloecken** ab und zaehlt
//! 175. Diese Datei schreibt dieselbe Tabelle **nach Schritten** ab und zaehlt
//! `3 + 0 + 16 + 152 + 4 + 0`. Beide Abschriften entstehen aus denselben
//! `zustand::stelle_*`-Funktionen, aber ueber verschiedene Schleifen -- und die Runde
//! unten legt sie zur Laufzeit zweiseitig gegeneinander: Eine Adresse in der Sollmaske
//! ohne Schritt bricht ab, ein Schritt mit einer Adresse ausserhalb der Sollmaske
//! ebenfalls. Eine abgetippte Tabelle ist sonst ein Tippfehler mit Verzoegerung.
//!
//! ## Warum die Runde ueber die Adressen laeuft und nicht ueber die Schritte
//!
//! Die sechs Schritte sind zyklenfrei, aber ihre Adressbloecke liegen ineinander: Der
//! Instrumentenstand aus Schritt 3 liegt im selben 44er-Block wie die Sektoren aus
//! Schritt 4 und **vor** ihnen nicht, sondern dazwischen. Wer die sechs Schritte
//! nacheinander ihre Bloecke schreiben laesst, bekommt eine Kette, die nicht aufsteigt --
//! und die aufsteigende Kette ist genau das, was diesen Rahmen von einer gerechneten
//! Runde unterscheidbar macht (Bedingung 4 des Arbeitspakets 0033).
//!
//! Deshalb ist die aeussere Schleife die aufsteigende Adressrunde (T9, keine streuende
//! Menge), und jede Adresse geht an den Schritt, dem sie gehoert. Die feste Reihenfolge
//! der sechs Schritte steht daneben als benannte Liste (`SCHRITTFOLGE`, T9), damit ein
//! Umstellen sichtbar wird.
//!
//! **Und das ist eine Eigenschaft des Rahmens, nicht der Architektur -- seit dem
//! 2026-09-08 ist sie widerrufen.** Paket 0197 hat Schritt 5 den ersten rechnenden Rumpf
//! gegeben, und der nimmt seinen Block als Ganzes: Die Zustimmung eines Landes liest den
//! **neuen** Stand seiner vier Instrumente, und in der aufsteigenden Adressrunde kommt
//! sie vor ihnen an. Die vier Zustimmungsadressen laufen deshalb nach der Adressrunde.
//! Damit steigt die Kette nicht mehr durchgehend auf: 171 Glieder aufsteigend, danach die
//! vier der Gegenkraft. `test/schritt_probe.cpp` zieht die Aussage nach und misst die
//! neue Gestalt, statt sie abzuschreiben -- der Kopf `include/kern/schritt.hpp` hat den
//! Widerruf ausdruecklich dorthin gelegt.
//!
//! Was der Widerruf **nicht** ist: eine Erlaubnis fuer Schritt 4. Dessen Marktraeumung
//! wird denselben Weg gehen, wenn sie gebaut wird; heute traegt sie vor.
//!
//! Die zweite Aussage derselben Art -- die unveraenderte Pruefsumme -- ist seit Paket
//! 0071 widerrufen: Schritt 1 **setzt** `partie.runde` auf die Nummer dieser Runde, statt
//! sie vorzutragen. Der Grund steht an `schritt_1_ansicht` weiter unten und in einem Satz
//! hier: Ein Zustand, den eine vollstaendige Runde Feld fuer Feld unveraendert laesst,
//! ist von "keine Runde gelaufen" durch keinen Vergleich zu unterscheiden.
//!
//! **Die Zahl, die 0071 daneben schrieb -- "genau eine der 310 Groessen" --, gilt seit
//! dem 2026-09-08 nicht mehr.** Schritt 5 rechnet, und die Zustimmung eines Landes kann
//! sich mitbewegen; wie viele Groessen eine Runde bewegt, haengt jetzt am Zustand und ist
//! keine Konstante des Rahmens mehr. Der Kopf `include/kern/schritt.hpp` fuehrt die alte
//! Zahl noch. Er steht nicht in der Dateiliste dieses Pakets und ist als eigener
//! Vorschlag gemeldet (0235).

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::schritt {

namespace {

/// Der Meldungsbau (Paket 0038). Jeder Abbruch dieser Datei nennt damit die Adresse, um
/// die es geht -- in ihrer Textform nach T17 und mit ihrer laufenden Nummer. Wer eine
/// auseinandergelaufene Zuordnung sucht, will die Adresse lesen und nicht den Dateinamen
/// der Tafel, in der sie steht.
using meldung::Meldung;

using zustand::Aggregat;
using zustand::FELDER;
using zustand::Gebiet;
using zustand::i64;
using zustand::Index;
using zustand::Instrument;
using zustand::InstrumentFeld;
using zustand::PartieFeld;
using zustand::PolitischeGroesse;
using zustand::Sektor;
using zustand::SektorGroesse;

using schreiber::Bitfeld;
using schreiber::Schreiber;
using schreiber::Ursache;

/// Der Platz von `partie.runde` -- aus der Adressrechnung und nicht als Zahl.
///
/// Er kommt an vier Stellen dieser Datei vor: in der Zuordnungstafel, zweimal in den
/// beiden Randfallabbruechen der Rundennummer und in Schritt 1, der ihn seit Paket 0071
/// **setzt**. Vier Abschriften desselben Aufrufs waeren vier Stellen, an denen ein
/// verschobener Partieblock nur drei davon erwischt.
constexpr Index PLATZ_RUNDE = zustand::stelle_partie(PartieFeld::Runde);

/// Der Platz von `partie.parameter_pruefsumme` -- aus derselben Adressrechnung und aus
/// demselben Grund wie `PLATZ_RUNDE`: Er kommt zweimal vor, in der Zuordnungstafel und
/// in der Bindung des Parametersatzes an den Zustand (T10b).
constexpr Index PLATZ_PARAMETERSUMME =
    zustand::stelle_partie(PartieFeld::ParameterPruefsumme);

// ---------------------------------------------------------------------------
// Die festen Reihenfolgen, ueber die iteriert wird (T9)
// ---------------------------------------------------------------------------
//
// Ausgeschrieben statt aus Zahlen gerechnet, dieselbe Begruendung wie in
// `src/schreiber.cpp`: Wer eine Aufzaehlung erweitert, muss die Zeile hier anfassen und
// sieht dabei, was er tut.

constexpr std::array<Gebiet, zustand::GEBIETE> GEBIETE_ALLE = {
    Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::BR, Gebiet::RW};

constexpr std::array<Gebiet, zustand::LAENDER> LAENDER_ALLE = {Gebiet::US, Gebiet::CN,
                                                               Gebiet::DE, Gebiet::BR};

constexpr std::array<Sektor, zustand::SEKTOREN> SEKTOREN_ALLE = {
    Sektor::Landwirtschaft, Sektor::Industrie, Sektor::Dienstleistungen};

constexpr std::array<Sektor, zustand::SEKTOREN_HANDELBAR> SEKTOREN_HANDELBAR_ALLE = {
    Sektor::Landwirtschaft, Sektor::Industrie};

constexpr std::array<SektorGroesse, zustand::SEKTORGROESSEN> SEKTORGROESSEN_ALLE = {
    SektorGroesse::Wertschoepfung, SektorGroesse::Kapitalstock, SektorGroesse::Beschaeftigung,
    SektorGroesse::Preis};

constexpr std::array<Aggregat, zustand::AGGREGATE> AGGREGATE_ALLE = {
    Aggregat::Bevoelkerung, Aggregat::Erwerbstaetige, Aggregat::Produktivitaet,
    Aggregat::Preisniveau,  Aggregat::Inflation,      Aggregat::Leitzins,
    Aggregat::Wechselkurs,  Aggregat::Staatsschuld,   Aggregat::Haushaltssaldo};

constexpr std::array<Instrument, zustand::INSTRUMENTE> INSTRUMENTE_ALLE = {
    Instrument::Leitzins, Instrument::Zoll, Instrument::Haushalt, Instrument::Regulierung};

// ---------------------------------------------------------------------------
// Die sechs Schritte aus `spiel.md`, Abschnitt "The loop"
// ---------------------------------------------------------------------------

/// Die sechs Schritte der Runde, mit ausgeschriebenen Nummern.
///
/// `Keiner` ist die siebte Marke und **kein** siebter Schritt: Sie sagt "diese Adresse
/// gehoert im Modus `weltlauf` keinem Schritt", und das trifft nach T38 auf genau 135
/// der 310 Adressen zu. Sie steht auf der Null, damit eine frisch angelegte
/// Zuordnungstafel durchgehend "noch nicht zugeteilt" bedeutet.
enum class Rundenschritt : std::uint8_t {
    Keiner = 0,
    Ansicht = 1,
    Aktionen = 2,
    Politik = 3,
    Wirtschaft = 4,
    Reaktion = 5,
    Abrechnung = 6,
};

inline constexpr std::size_t SCHRITTE = 6;

/// T9: "Die sechs Schritte der Runde laufen in der Reihenfolge aus `spiel.md`, und diese
/// Reihenfolge steht als benannte Konstantenliste im Code, damit ein Umstellen sichtbar
/// wird." Das ist diese Liste.
constexpr std::array<Rundenschritt, SCHRITTE> SCHRITTFOLGE = {
    Rundenschritt::Ansicht,    Rundenschritt::Aktionen, Rundenschritt::Politik,
    Rundenschritt::Wirtschaft, Rundenschritt::Reaktion, Rundenschritt::Abrechnung};

/// Die Nummer eines Schritts, `1` bis `6` -- dieselbe Zahl wie in `spiel.md`.
constexpr std::size_t schrittnummer(Rundenschritt welcher)
{
    return static_cast<std::size_t>(welcher);
}

/// Der Name eines Schritts fuer die Abbrueche unten.
///
/// Die Nummer allein zwingt den Leser einer Fehlermeldung, in `spiel.md` nachzuschlagen,
/// welcher Schritt die `3` ist. Kein `default`: Ohne ihn meldet `-Wswitch` einen
/// fehlenden Fall, und mit `-Werror` ist ein siebter Schritt damit ein Bauabbruch statt
/// einer Meldung, die "Keiner" sagt, wo sie einen Namen nennen sollte.
constexpr const char* schrittname(Rundenschritt welcher)
{
    switch (welcher) {
        case Rundenschritt::Keiner:
            return "keiner";
        case Rundenschritt::Ansicht:
            return "Ansicht";
        case Rundenschritt::Aktionen:
            return "Aktionen";
        case Rundenschritt::Politik:
            return "Politik";
        case Rundenschritt::Wirtschaft:
            return "Wirtschaft";
        case Rundenschritt::Reaktion:
            return "Reaktion";
        case Rundenschritt::Abrechnung:
            return "Abrechnung";
    }
    return "unbekannt";
}

/// Haengt einen Schritt als "Nr. Name" an eine Meldung -- die Zahl aus `spiel.md` und
/// der Name daneben, damit beide Enden derselben Auskunft in derselben Zeile stehen.
void nenne_schritt(Meldung& meldung, Rundenschritt welcher)
{
    meldung.text("Schritt ");
    meldung.zahl(static_cast<i64>(schrittnummer(welcher)));
    meldung.text(" (");
    meldung.text(schrittname(welcher));
    meldung.text(")");
}

/// Ob die Liste vollstaendig ist und in der Reihenfolge aus `spiel.md` steht.
///
/// Gebaut als Nachrechnung statt als Sichtpruefung: Wer zwei Eintraege vertauscht, hat
/// keine andere Reihenfolge, sondern eine Datei, die sich nicht uebersetzen laesst.
constexpr bool schrittfolge_stimmt()
{
    for (std::size_t n = 0; n < SCHRITTE; ++n) {
        if (schrittnummer(SCHRITTFOLGE[n]) != n + 1) {
            return false;
        }
    }
    return true;
}

static_assert(schrittfolge_stimmt(),
              "T9: die sechs Schritte stehen in der Reihenfolge aus spiel.md");

// ---------------------------------------------------------------------------
// T38 -- die Sollmaske `weltlauf`, ein zweites Mal abgeschrieben, nach Schritten
// ---------------------------------------------------------------------------
//
// Die Zuordnung folgt der Tabelle in T38 und dem Satz darunter: "Der Modus wirkt an
// genau vier Stellen -- Schritt 2 und 6 der Runde entfallen, aus Schritt 5 laufen nur
// Zustimmung und Regierungswechsel, und die Politikinstrumente kommen in Schritt 3 aus
// dem Jahrgang statt aus dem Lobbydruck."
//
//   Schritt 1  Ansicht      Partie: Runde, Jahrgangskennung, Parameterpruefsumme    3
//   Schritt 2  Aktionen     -- entfaellt im weltlauf (T38)                          0
//   Schritt 3  Politik      je Land der Instrumentenstand (4)                      16
//   Schritt 4  Wirtschaft   je Land Sektoren (12), Aggregate (9), basiswechsel (1)  88
//                           Restwelt 22, Handel 40, Weltpreise 2                   64
//   Schritt 5  Reaktion     je Land Zustimmung (1)                                  4
//   Schritt 6  Abrechnung   -- entfaellt im weltlauf (T38)                          0
//                                                                          zusammen 175
//
// **Die drei Partiefelder sind die eine Zuordnung, die T38 nicht nennt**, und deshalb
// steht ihre Begruendung hier statt in einer Fussnote: Sie stehen in der Tabelle als
// eigene Zeile, ohne einen der sechs Schritte. Sie gehen an Schritt 1, weil die Runde
// mit der Feststellung beginnt, *welche* Runde aus *welchem* Jahrgang mit *welchem*
// Parametersatz gerechnet wird -- jeder spaetere Schritt liest das, keiner setzt es.
// Der `Mandatsstand` bleibt davon getrennt und liegt bei Schritt 6, wie es die Tabelle
// tut; er ist im `weltlauf` ohnehin ausserhalb der Maske.
//
// Ausserhalb der Maske `weltlauf` wird **nichts** zugeteilt. Wer die 135 Adressen des
// `spielmodus` verteilt, entscheidet ueber Kaesten, die `specs/` noch nicht beauftragt
// hat; hier bleiben sie `Keiner`, und die Zahl 135 ist die Gegenprobe unten.

using Zuordnung = std::array<Rundenschritt, FELDER>;

/// Teilt eine Adresse einem Schritt zu. Zwei harte Fehler, beide beim Uebersetzen:
/// Adresse ausserhalb der 310, und eine Adresse, die schon einem Schritt gehoert.
///
/// Die zweite Pruefung ist die wichtige: Sie faengt die Ueberschneidung zweier
/// Blockschleifen ab, die sich sonst als zu kleine Gesamtzahl verstecken wuerde -- und
/// eine zu kleine Gesamtzahl haette in der Runde unten die Sollmaske verfehlt und
/// dieselbe Adresse zweimal geschrieben.
///
/// Beide Meldungen nennen die Adresse und die Zahl, die nicht aufging. Dass diese Datei
/// die Zuordnung zur *Uebersetzungszeit* baut, heisst nicht, dass die Meldungen
/// ueberfluessig waeren: `teile_zu` ist keine `consteval` Funktion, und der Rumpf steht
/// als Vorlage fuer den Tag, an dem ein Schrittpaket eine Adresse zur Laufzeit zuteilt.
constexpr void teile_zu(Zuordnung& tafel, Index platz, Rundenschritt welcher)
{
    if (platz >= FELDER) {
        Meldung meldung;
        meldung.text("kern::schritt -- Zuordnung: Adresse ausserhalb der 310 Felder, Platz ");
        meldung.zahl(static_cast<i64>(platz));
        meldung.text(" soll an ");
        nenne_schritt(meldung, welcher);
        festkomma::abbruch(meldung.fertig());
    }
    if (tafel[platz] != Rundenschritt::Keiner) {
        Meldung meldung;
        meldung.text("kern::schritt -- Zuordnung: ");
        meldung.adresse(platz);
        meldung.text(" gehoert schon ");
        nenne_schritt(meldung, tafel[platz]);
        meldung.text(" und soll zusaetzlich an ");
        nenne_schritt(meldung, welcher);
        festkomma::abbruch(meldung.fertig());
    }
    tafel[platz] = welcher;
}

constexpr Zuordnung baue_zuordnung()
{
    Zuordnung tafel{};  // durchgehend `Keiner`

    // Schritt 1 -- Ansicht: die drei Partiefelder der Maske.
    teile_zu(tafel, PLATZ_RUNDE, Rundenschritt::Ansicht);
    teile_zu(tafel, zustand::stelle_partie(PartieFeld::JahrgangId), Rundenschritt::Ansicht);
    teile_zu(tafel, PLATZ_PARAMETERSUMME, Rundenschritt::Ansicht);

    // Schritt 2 -- Aktionen: kein Eintrag. Entfaellt im `weltlauf` (T38).

    // Schritt 3 -- Politik: je spielbarem Land der Instrumentenstand, zusammen 16.
    // Druck, Gegendruck und Restverzoegerung liegen ausserhalb der Maske.
    for (const Gebiet land : LAENDER_ALLE) {
        for (const Instrument welches : INSTRUMENTE_ALLE) {
            teile_zu(tafel, zustand::stelle_instrument(land, welches, InstrumentFeld::Stand),
                     Rundenschritt::Politik);
        }
    }

    // Schritt 4 -- Wirtschaft: Produktion, Handel, Preise. Je spielbarem Land die zwoelf
    // Sektorgroessen, die neun Aggregate und der `basiswechsel` (27 x 4 = 88 minus die
    // vier Zustimmungen, die Schritt 5 hat -- gezaehlt wird unten), dazu die ganze
    // Restwelt, der Handelsblock und die beiden Weltpreise.
    for (const Gebiet land : LAENDER_ALLE) {
        for (const Sektor sektor : SEKTOREN_ALLE) {
            for (const SektorGroesse groesse : SEKTORGROESSEN_ALLE) {
                teile_zu(tafel, zustand::stelle_sektorgroesse(land, sektor, groesse),
                         Rundenschritt::Wirtschaft);
            }
        }
        for (const Aggregat aggregat : AGGREGATE_ALLE) {
            teile_zu(tafel, zustand::stelle_aggregat(land, aggregat), Rundenschritt::Wirtschaft);
        }
        teile_zu(tafel, zustand::stelle_basiswechsel(land), Rundenschritt::Wirtschaft);
    }

    // Die Restwelt, alle 22: Sie hat weder politische Groessen noch Instrumente noch
    // Restdauern (T15), ihr Block gehoert deshalb vollstaendig der Wirtschaft.
    for (const Sektor sektor : SEKTOREN_ALLE) {
        for (const SektorGroesse groesse : SEKTORGROESSEN_ALLE) {
            teile_zu(tafel, zustand::stelle_sektorgroesse(Gebiet::RW, sektor, groesse),
                     Rundenschritt::Wirtschaft);
        }
    }
    for (const Aggregat aggregat : AGGREGATE_ALLE) {
        teile_zu(tafel, zustand::stelle_aggregat(Gebiet::RW, aggregat), Rundenschritt::Wirtschaft);
    }
    teile_zu(tafel, zustand::stelle_basiswechsel(Gebiet::RW), Rundenschritt::Wirtschaft);

    // Der Handel, alle 40: fuenf Gebiete mal vier Gegenueber mal zwei handelbare
    // Sektoren.
    for (const Gebiet von : GEBIETE_ALLE) {
        for (const Gebiet nach : GEBIETE_ALLE) {
            if (von == nach) {
                continue;  // ein Gebiet handelt nicht mit sich selbst
            }
            for (const Sektor sektor : SEKTOREN_HANDELBAR_ALLE) {
                teile_zu(tafel, zustand::stelle_handel(von, nach, sektor),
                         Rundenschritt::Wirtschaft);
            }
        }
    }

    // Die beiden Weltpreise.
    for (const Sektor sektor : SEKTOREN_HANDELBAR_ALLE) {
        teile_zu(tafel, zustand::stelle_weltpreis(sektor), Rundenschritt::Wirtschaft);
    }

    // Schritt 5 -- Reaktion: im `weltlauf` laufen nur Zustimmung und Regierungswechsel
    // (T38), und der Regierungswechsel wird gerechnet und ausgewiesen, schreibt aber
    // nichts. Bleibt je spielbarem Land die Zustimmung.
    for (const Gebiet land : LAENDER_ALLE) {
        teile_zu(tafel, zustand::stelle_politisch(land, PolitischeGroesse::Zustimmung),
                 Rundenschritt::Reaktion);
    }

    // Schritt 6 -- Abrechnung: kein Eintrag. Entfaellt im `weltlauf` (T38).

    return tafel;
}

constexpr Zuordnung ZUORDNUNG = baue_zuordnung();

/// Wie viele der 310 Adressen diesem Schritt gehoeren.
constexpr std::size_t zaehle(Rundenschritt welcher)
{
    std::size_t summe = 0;
    for (const Rundenschritt eintrag : ZUORDNUNG) {
        if (eintrag == welcher) {
            ++summe;
        }
    }
    return summe;
}

// Die Nachrechnung, die aus der Abschrift eine Pruefung macht -- Schritt fuer Schritt
// gegen die Tabelle in T38.
static_assert(zaehle(Rundenschritt::Ansicht) == 3, "T38: Runde, Jahrgangskennung, Pruefsumme");
static_assert(zaehle(Rundenschritt::Aktionen) == 0, "T38: Schritt 2 entfaellt im weltlauf");
static_assert(zaehle(Rundenschritt::Politik) == 16, "T38: vier Laender mal vier Instrumentenstaende");
static_assert(zaehle(Rundenschritt::Wirtschaft) == 152,
              "T38: 4x(12+9+1) + 22 + 40 + 2 = 88 + 64");
static_assert(zaehle(Rundenschritt::Reaktion) == 4, "T38: je spielbarem Land die Zustimmung");
static_assert(zaehle(Rundenschritt::Abrechnung) == 0, "T38: Schritt 6 entfaellt im weltlauf");

static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, "T38: der Block von Schritt 4, nachgerechnet");

// Und die Summe gegen die Zahl, die `schreiber.hpp` aus der anderen Richtung fuehrt.
// Beide Abschriften derselben Tabelle muessen dieselbe Menge ergeben; dass sie es
// adressgenau tun, prueft die Runde unten zur Laufzeit zweiseitig.
static_assert(3 + 0 + 16 + 152 + 4 + 0 == schreiber::MASKE_WELTLAUF,
              "T38: die Maske weltlauf, nach den sechs Schritten geordnet, ergibt 175");
static_assert(zaehle(Rundenschritt::Keiner) == schreiber::AUSSERHALB_WELTLAUF,
              "T38: 135 Adressen gehoeren im weltlauf keinem Schritt");

// ---------------------------------------------------------------------------
// Die sechs Schritte als sechs benannte Funktionen
// ---------------------------------------------------------------------------
//
// **Das ist der Anschlussort fuer die Folgepakete.** Wer Schritt 4 baut, ersetzt den
// Rumpf von `schritt_4_wirtschaft` und fasst nichts anderes an. Jede der sechs traegt
// ihren Adressblock aus T38 im Kommentar.
//
// **Vier von ihnen bekommen eine Adresse, zwei nicht mehr.** Die Schritte 1, 3, 4 und 6
// nehmen `(Schreiber&, Index)` und werden aus der Adressrunde gerufen; sie tragen ihre
// Adresse vor -- mit einer Ausnahme, `partie.runde` in Schritt 1, die seit Paket 0071
// gesetzt wird statt vorgetragen. Schritt 5 nimmt seit Paket 0197 seinen ganzen Block
// und laeuft nach der Adressrunde, weil er den neuen Stand von Adressen liest, die hinter
// seinen eigenen liegen. Schritt 2 hat im `weltlauf` keine Adresse.
//
// `vortrag` ist fuer die vier da: "Eine Adresse, die sich nicht aendert, wird trotzdem
// geschrieben -- *unveraendert* ist eine Aussage und keine Luecke." Verzoegerung null,
// Beitrag 1.000 Promille und `alt == neu` folgen daraus und stehen im `Schreiber`, nicht
// hier.

/// **Schritt 1 -- Ansicht.** Nach `spiel.md`: "Der Zustand, und daneben die Kette der
/// Vorrunde." Der Schritt zeigt; geschrieben wird an ihm nur die Buchfuehrung der Runde.
///
/// T38-Block: `Partie: Runde, Jahrgangskennung, Parametersatz-Pruefsumme` -- 3 Adressen,
/// in der Maske `weltlauf`.
///
/// **Zwei der drei Adressen werden vorgetragen, eine wird gesetzt** (Paket 0071):
/// `partie.runde` bekommt die Nummer *dieser* Runde, Jahrgangskennung und
/// Parameterpruefsumme behalten ihre. Bis zum 2026-09-04 wurde auch die Rundennummer
/// vorgetragen -- der Zuschnitt von Paket 0033, das die unveraenderte Pruefsumme
/// ausdruecklich "auf Widerruf" ausgewiesen hat. Dies ist der Widerruf, und der Grund
/// ist kein aesthetischer: Der Startwertriegel aus Paket 0027 erkennt eine gelaufene
/// Runde daran, dass sich die Zahl auf diesem Platz **geaendert** hat. Solange die Runde
/// sie vortrug, war ein vollstaendig gerechneter Weltlauf von "keine Runde gelaufen"
/// durch keinen Vergleich am Zustand zu unterscheiden, und der Riegel schlug gegen die
/// Runde des Kerns nie an.
///
/// **Die Zahl kommt aus dem Schreiber und nicht aus einem zweiten Rechenweg.** Er hat sie
/// im Konstruktor bekommen und traegt sie ohnehin an jedes der 175 Kettenglieder; sie
/// hier ein zweites Mal aus der Vorrunde zu rechnen hiesse, dieselbe Zahl an zwei Stellen
/// zu fuehren -- und zwei Stellen laufen auseinander.
///
/// **Warum die Ursache `Vortrag` heisst, obwohl der Wert sich aendert.** Die sechs Formen
/// aus T18 sind abschliessend, und keine von ihnen heisst "Rundenzaehler"; eine siebte
/// waere eine Abweichung von `specs/` und braeuchte einen ADR. `Vortrag{adresse}` ist die
/// einzige der sechs, die eine **Herkunftsadresse** nennt, und die Herkunft stimmt genau:
/// Die neue Nummer entsteht aus dem alten Wert dieser Adresse und aus nichts sonst. Was
/// die Form *nicht* aussagt, ist "unveraendert" -- das sagt `Schreiber::vortrag`, die
/// Abkuerzung, die `alt` als neuen Wert einsetzt. Deshalb steht hier der ausgeschriebene
/// `setze`-Aufruf und nicht sie. Verzoegerung null und Beitrag 1.000 Promille wie beim
/// Vortrag: Ursache und Wirkung liegen in derselben Runde, und diese eine Ursache
/// erklaert die Aenderung vollstaendig.
void schritt_1_ansicht(Schreiber& schreiber, Index platz)
{
    if (platz == PLATZ_RUNDE) {
        schreiber.setze(platz, schreiber.runde(), Ursache::vortrag(platz), 0, 1000);
        return;
    }
    schreiber.vortrag(platz);
}

/// **Schritt 2 -- Aktionen.** Nach `spiel.md`: "Der Spieler stellt bis zu drei
/// Aktionen."
///
/// T38-Block: **keiner.** Der Schritt entfaellt im Modus `weltlauf` -- es gibt dort
/// keinen Spieler. Er steht hier, weil die Reihenfolge der sechs Schritte vollstaendig
/// sein muss und weil der `spielmodus` ihn braucht; sein Aktionstyp haengt an T32 und
/// ist unbeauftragt.
///
/// Der Rumpf ist ein Abbruch und kein leerer Block: Eine Adresse, die hier ankommt,
/// bedeutet, dass Zuordnungstafel und Sollmaske auseinanderlaufen -- und ein leerer
/// Rumpf haette diese Adresse verschluckt, bis die Rundenendpruefung sie viel spaeter
/// als "in der Sollmaske, aber nicht geschrieben" gemeldet haette.
void schritt_2_aktionen(Schreiber& schreiber, const Aktionsbuendel& aktionen, Index platz)
{
    static_cast<void>(schreiber);
    static_cast<void>(aktionen);
    Meldung meldung;
    meldung.text(
        "kern::schritt -- Schritt 2 (Aktionen) entfaellt im Modus weltlauf (T38) und hat dort "
        "keine Adresse; wer hierher kommt, hat Zuordnungstafel und Sollmaske verschoben. "
        "Angekommen ist ");
    meldung.adresse(platz);
    festkomma::abbruch(meldung.fertig());
}

/// **Schritt 3 -- Politik.** Nach `spiel.md`: "Anliegender Lobbydruck und Gegenlobby
/// werden je Instrument gegeneinander verrechnet, faellige Verzoegerungen aus frueheren
/// Runden greifen, Instrumente bewegen sich um hoechstens einen Schritt je Runde."
///
/// T38-Block: `je spielbarem Land: Instrumentenstand (4)` -- 16 Adressen, in der Maske
/// `weltlauf`. Druck, Gegendruck und Restverzoegerung (12 je Land) liegen ausserhalb:
/// Im `weltlauf` kommen die Politikinstrumente aus dem Jahrgang statt aus dem
/// Lobbydruck (T38), es gibt also keinen Druck zu fuehren.
void schritt_3_politik(Schreiber& schreiber, Index platz) { schreiber.vortrag(platz); }

/// **Schritt 4 -- Wirtschaft.** Nach `spiel.md`: "Produktion aus Kapitalstock und
/// Produktivitaet, Handel zwischen den vier Laendern und der Restwelt, Preise,
/// Realeinkommen, Zins, Wechselkurs, Staatsfinanzen."
///
/// T38-Block: `je spielbarem Land: Sektoren (12), Aggregate (9), basiswechsel (1)`,
/// dazu `Restwelt (22)`, `Handel (40)` und `Weltpreise (2)` -- 152 Adressen, alle in der
/// Maske `weltlauf`. Das ist der groesste der sechs Bloecke und der einzige, in dem nach
/// `spiel.md` eine Schleife steht: die Marktraeumung, mit fester Iterationszahl.
void schritt_4_wirtschaft(Schreiber& schreiber, Index platz) { schreiber.vortrag(platz); }

// ---------------------------------------------------------------------------
// Gegenkraft 2 -- die Zustimmung, als Rechenvorschrift (Paket 0197)
// ---------------------------------------------------------------------------
//
// Die Regel steht in `spiel.md` ausgeschrieben, seit Paket 0198 sie gefuellt hat. Ihre
// drei Zeilen stehen hier im Wortlaut, damit die Rumpfe darunter sich an ihnen messen
// lassen und niemand sie aus dem Programmtext zurueckuebersetzen muss:
//
//     politiklast(l) = Summe ueber die vier Instrumente i:
//                        sgn( lies_neu(land.<l>.instrument.<i>.stand)
//                           - lies_alt(land.<l>.instrument.<i>.stand) ) * schaden(l, i)
//
//     realeinkommenshub(l) = mal_geteilt( -politiklast(l), 10.000, bip(l) )
//
//     zustimmung_neu(l) = min( 10.000,
//                              max( 0,
//                                   lies_alt(land.<l>.zustimmung)
//                                   + mal_geteilt( zustimmung_elastizitaet,
//                                                  realeinkommenshub(l), 10.000 ) ) )
//
// **Woher die Mengen kommen, und die eine Stelle, an der diese Datei zwei Vorgaben
// nebeneinander findet.** `spiel.md` sagt zur Regel: alles ausser dem Ausgangswert der
// Zustimmung wird mit `lies_neu` gelesen. `werte::schaden` und `werte::bip` nehmen nach
// T48 dagegen einen `Zustand`, und der einzige, den ein Rumpf hier hat, ist der am Ende
// der Vorrunde -- der `Schreiber` gibt seinen erst nach der Maskenpruefung des
// Rundenendes heraus, und da ist die Zustimmung noch nicht geschrieben. Heute fallen
// beide Lesarten zusammen: `schritt_4_wirtschaft` traegt alle 152 Wirtschaftsadressen
// unveraendert vor, also ist `lies_neu` dort Zahl fuer Zahl `lies_alt`. An dem Tag, an
// dem Schritt 4 rechnet, fallen sie auseinander, und dann ist es keine Frage, die ein
// Rumpf entscheiden darf. Sie ist als eigener Vorschlag gemeldet (0236).

/// Die Skala der Anteile aus T5 Klasse 4 -- Zehntausendstel. Sie kommt in der Regel oben
/// dreimal vor: als obere Schranke, als Faktor des Hubs und als Nenner der
/// Elastizitaetszeile.
constexpr i64 ZEHNTAUSENDSTEL = 10'000;

/// Das Vorzeichen der Regel: die Richtung, in die sich ein Instrumentenstand ueber diese
/// Runde bewegt hat -- minus eins, null oder plus eins.
///
/// **Verglichen und nicht subtrahiert.** Die Differenz zweier Staende kann nach T7 aus
/// dem `i64` laufen; `festkomma::minus` braeche dann ab, und zwar an einer Stelle, an der
/// die Regel nur das Vorzeichen wissen will. Der Vergleich gibt fuer jedes Paar dasselbe
/// Vorzeichen, auch fuer die beiden Enden des Zahlbereichs.
i64 schrittrichtung(const Schreiber& schreiber, Gebiet land, Instrument welches)
{
    const Index stand = zustand::stelle_instrument(land, welches, InstrumentFeld::Stand);
    const i64 neu = schreiber.lies_neu(stand);
    const i64 alt = schreiber.lies_alt(stand);
    if (neu == alt) {
        return 0;
    }
    return neu > alt ? 1 : -1;
}

/// `politiklast(l)` -- die vier Zeilen aus `spiel.md`, jede mit ihrem Vorzeichen.
///
/// **Ein Instrument, das sich nicht bewegt hat, traegt nichts bei, und sein `schaden`
/// wird nicht gerechnet.** Das ist keine Abkuerzung der Regel, sondern ihre woertliche
/// Lesart: Die Summe laeuft ueber Produkte, und ein Faktor null legt das Produkt fest,
/// welchen Wert der andere auch haette. Gerechnet wuerde sonst der Preis eines
/// Politikschritts, den niemand getan hat -- ueber `handelsvolumen`, `schuld` und
/// `preishub_zoll`, die dafuer nicht gestellt sind.
///
/// Die Reihenfolge der vier Zeilen ist `INSTRUMENTE_ALLE` (T9) und nicht die Laufrichtung
/// eines Feldes: Eine Summe haengt nicht von ihr ab, ein Abbruch in ihr schon.
i64 politiklast(const Zustand& rundengrenze, const Schreiber& schreiber,
                const Konstanten& konstanten, Gebiet land)
{
    i64 last = 0;
    for (const Instrument welches : INSTRUMENTE_ALLE) {
        const i64 richtung = schrittrichtung(schreiber, land, welches);
        if (richtung == 0) {
            continue;
        }
        const i64 zeile = werte::schaden(rundengrenze, schreiber, konstanten, land, welches);
        last = festkomma::plus(last, festkomma::mal(richtung, zeile));
    }
    return last;
}

/// `realeinkommenshub(l)` -- die Aenderung des Realeinkommens in Zehntausendsteln.
///
/// **Der Bezug ist nicht die Vorrunde, sondern dieselbe Runde ohne Politikbewegung.**
/// `bip(l)` ist dieser Gegenzustand: Es steht nach T5 in Klasse 2 und ist damit blind
/// fuer die Preise, die die Politik setzt. Deshalb steht es im Nenner, und deshalb kostet
/// die Gegenkraft weder eine zweite Marktraeumung noch eine 311. Adresse.
///
/// **Die Bedingung an den Nenner steht vor der Rechnung und nicht in ihr** (Paket 0237).
/// `spiel.md` nennt sie an der Regel selbst: "bip(l) > 0 is the denominator condition".
/// `mal_geteilt` faengt davon allein die Null. Der Rest ist derselbe Fall, den
/// `kern::werte::wert` am Wechselkurs schon aufgeschrieben hat -- dort steht der Grund im
/// Wortlaut: "der **negative** Nenner ist der gefaehrlichere Fall, weil er das Vorzeichen
/// jeder Bewertung drehte, ohne dass irgendetwas abbraeche". An dieser Regel hiesse das,
/// dass eine Politiklast die Zustimmung **hebt**: Die Gegenkraft liefe verkehrt herum,
/// und keine Zeile im Kern sagte es.
///
/// Kein Ersatzwert (T6). Ein Land ohne Wertschoepfung hat kein Realeinkommen, an dem sich
/// eine Aenderung messen liesse; eine erfundene Null waere eine Zahl, die keine Pruefung
/// bemerkt.
///
/// Die Schranke steht **vor** `politiklast`, weil sie eine Voraussetzung der Regel ist
/// und keine Folge ihrer Summe: Auf einem Zustand, den `spiel.md` verbietet, soll der
/// Abbruch die verbotene Groesse nennen und nicht irgendeine Zwischenrechnung, die auf
/// dem Weg dorthin zuerst umfaellt.
i64 realeinkommenshub(const Zustand& rundengrenze, const Schreiber& schreiber,
                      const Konstanten& konstanten, Gebiet land)
{
    const i64 inlandsprodukt = werte::bip(rundengrenze, land);
    if (inlandsprodukt < 1) {
        Meldung meldung;
        meldung.text(
            "kern::schritt -- Zustimmungsregel: bip(l) > 0 ist die Nennerbedingung aus "
            "spiel.md, und hier ist bip(l) kleiner als 1. Der negative Nenner ist der "
            "gefaehrlichere Fall, weil er das Vorzeichen jeder Bewertung drehte, ohne dass "
            "irgendetwas abbraeche: Eine Politiklast hoebe die Zustimmung, statt sie zu "
            "senken. Betroffen ist ");
        meldung.adresse(zustand::stelle_politisch(land, PolitischeGroesse::Zustimmung));
        meldung.text(", das Bruttoinlandsprodukt seines Landes ist ");
        meldung.zahl(inlandsprodukt);
        festkomma::abbruch(meldung.fertig());
    }

    const i64 last = politiklast(rundengrenze, schreiber, konstanten, land);
    return festkomma::mal_geteilt(festkomma::minus(0, last), ZEHNTAUSENDSTEL, inlandsprodukt);
}

/// **Schritt 5 -- Reaktion.** Nach `spiel.md`: "Zustimmung, Regierungswechsel,
/// Aufsichtszaehler, Nachahmerzaehler, Anlegerbestand -- die fuenf Gegenkraefte rechnen
/// ab."
///
/// T38-Block im `weltlauf`: `je spielbarem Land: Zustimmung (1)` -- 4 Adressen. Aus
/// diesem Schritt laufen im `weltlauf` nur Zustimmung und Regierungswechsel (T38), und
/// der Regierungswechsel wird gerechnet und ausgewiesen, **schreibt aber nichts**; dass
/// das Orakel an dieser Stelle blind ist, gehoert nach `spiel.md` in jeden Befund.
/// Aufsichtszaehler, Einfluss, Restdauern, Nachahmerzaehler und Anlegerbestand liegen
/// ausserhalb der Maske.
///
/// **Dieser Rumpf rechnet, und er ist der erste der sechs, der es tut** (Paket 0197).
/// Er nimmt seinen Block als Ganzes und laeuft nach der Adressrunde; die anderen fuenf
/// bekommen weiter Adresse fuer Adresse. Der Grund ist die Adressordnung und keine
/// Vorliebe: Die Regel liest `lies_neu` der vier Instrumentenstaende eines Landes, nach
/// T39 ist `lies_neu` auf eine in dieser Runde noch nicht geschriebene Adresse ein harter
/// Fehler, und in der aufsteigenden Runde kommt die Zustimmung eines Landes **vor**
/// seinen Instrumentenstaenden an. `test/schritt_probe.cpp` misst diese Ordnung, statt
/// sie aus T15 abzuschreiben, und zieht dort zugleich die Aussage ueber die aufsteigende
/// Kette nach.
///
/// **Die Ursache ist `Gegenkraft{2}` und bleibt es auch, wenn die Zahl stehen bleibt.**
/// Ein `Vortrag` waere die falsche Auskunft: Der Wert kommt aus der Regel und nicht aus
/// seiner eigenen Adresse, auch dann, wenn die Regel ihn auf sich selbst abbildet.
/// Verzoegerung null und Beitrag 1.000 Promille, weil Ursache und Wirkung in derselben
/// Runde liegen und diese eine Ursache die Groesse vollstaendig erklaert.
///
/// **Die beiden Schranken sind der Wertebereich der Klasse 4 und kein Verband ueber eine
/// Luecke** -- `spiel.md` sagt es an der Regel selbst: null und hundert Prozent
/// Zustimmung sind erreichbare Zustaende. Sie stehen deshalb hier und nicht in einer
/// Ausnahmebehandlung.
void schritt_5_reaktion(const Zustand& rundengrenze, Schreiber& schreiber,
                        const Konstanten& konstanten)
{
    for (const Gebiet land : LAENDER_ALLE) {
        const Index platz = zustand::stelle_politisch(land, PolitischeGroesse::Zustimmung);

        const i64 hub = realeinkommenshub(rundengrenze, schreiber, konstanten, land);
        const i64 wirkung =
            festkomma::mal_geteilt(konstanten.zustimmung_elastizitaet, hub, ZEHNTAUSENDSTEL);
        const i64 ungeklemmt = festkomma::plus(schreiber.lies_alt(platz), wirkung);

        // `min(10.000, max(0, ...))`, in der Schachtelung der Vorgabe: erst die untere
        // Schranke, dann die obere.
        const i64 nicht_unter_null = ungeklemmt < 0 ? 0 : ungeklemmt;
        const i64 zustimmung_neu =
            nicht_unter_null > ZEHNTAUSENDSTEL ? ZEHNTAUSENDSTEL : nicht_unter_null;

        schreiber.setze(platz, zustimmung_neu, Ursache::gegenkraft(2), 0, 1000);
    }
}

/// Der Weg, den Schritt 5 seit Paket 0197 **nicht** mehr nimmt: die Weiche der
/// Adressrunde.
///
/// Der Rumpf ist ein Abbruch und kein leerer Block, aus demselben Grund wie bei den
/// Schritten 2 und 6: Eine Adresse, die hier ankommt, bedeutet, dass jemand die
/// Auslassung in der Adressrunde entfernt hat -- und die Zustimmung wuerde dann zweimal
/// geschrieben, einmal hier und einmal im Block. Der zweite Schreibzugriff waere nach T18
/// ohnehin ein harter Fehler, nur naennte seine Meldung die Adresse und nicht den Grund.
void schritt_5_nicht_adressweise(Index platz)
{
    Meldung meldung;
    meldung.text(
        "kern::schritt -- Schritt 5 (Reaktion) rechnet seinen Block als Ganzes nach der "
        "Adressrunde und nimmt keine einzelne Adresse entgegen; wer hierher kommt, hat die "
        "Auslassung in der Adressrunde entfernt. Angekommen ist ");
    meldung.adresse(platz);
    festkomma::abbruch(meldung.fertig());
}

/// **Schritt 6 -- Abrechnung.** Nach `spiel.md`: "Positionen bewertet, Hebel gegen den
/// Innerjahresausschlag geprueft, Mandat geprueft, Kette als Diff gespeichert."
///
/// T38-Block: **keiner.** Der Schritt entfaellt im Modus `weltlauf` -- das
/// Fondsteilsystem laeuft dort nicht, weder Marktkorb noch Fondsaggregate noch
/// Steckplaetze noch Beteiligungen noch Mandatsstand stehen in der Maske. Er braucht
/// `kern::werte`, und Paket 0002 ist blockiert.
///
/// Zum Abbruch im Rumpf gilt dieselbe Begruendung wie bei Schritt 2.
void schritt_6_abrechnung(Schreiber& schreiber, Index platz)
{
    static_cast<void>(schreiber);
    Meldung meldung;
    meldung.text(
        "kern::schritt -- Schritt 6 (Abrechnung) entfaellt im Modus weltlauf (T38) und hat dort "
        "keine Adresse; wer hierher kommt, hat Zuordnungstafel und Sollmaske verschoben. "
        "Angekommen ist ");
    meldung.adresse(platz);
    festkomma::abbruch(meldung.fertig());
}

/// Gibt eine Adresse an den Schritt, dem sie gehoert.
///
/// Die sechs Faelle stehen in der Reihenfolge aus `SCHRITTFOLGE`. Kein `default`: Ohne
/// ihn meldet `-Wswitch` einen fehlenden Fall, und mit `-Werror` ist ein siebter Schritt
/// damit ein Bauabbruch statt einer stillen Auslassung.
void fuehre_schritt_aus(Rundenschritt welcher, Schreiber& schreiber,
                        const Aktionsbuendel& aktionen, Index platz)
{
    switch (welcher) {
        case Rundenschritt::Ansicht:
            schritt_1_ansicht(schreiber, platz);
            return;
        case Rundenschritt::Aktionen:
            schritt_2_aktionen(schreiber, aktionen, platz);
            return;
        case Rundenschritt::Politik:
            schritt_3_politik(schreiber, platz);
            return;
        case Rundenschritt::Wirtschaft:
            schritt_4_wirtschaft(schreiber, platz);
            return;
        case Rundenschritt::Reaktion:
            schritt_5_nicht_adressweise(platz);
            return;
        case Rundenschritt::Abrechnung:
            schritt_6_abrechnung(schreiber, platz);
            return;
        case Rundenschritt::Keiner:
            break;
    }
    Meldung meldung;
    meldung.text("kern::schritt -- ");
    meldung.adresse(platz);
    meldung.text(" steht in der Sollmaske aus T38, gehoert aber ");
    nenne_schritt(meldung, welcher);
    meldung.text(
        ": die Zuordnungstafel in kern/src/schritt.cpp und die Maske in kern/src/schreiber.cpp "
        "sind zwei Abschriften derselben Tabelle und laufen auseinander");
    festkomma::abbruch(meldung.fertig());
}

}  // namespace

// ---------------------------------------------------------------------------
// Die Runde
// ---------------------------------------------------------------------------

Rundenergebnis schritt(const Zustand& vorrunde, const Aktionsbuendel& aktionen,
                       const Konstanten& konstanten, Modus modus)
{
    static_assert(FELDER == 310, "die Meldung unten nennt die Zahl im Wortlaut");

    switch (modus) {
        case Modus::Spielmodus:
            // Bedingung 7 des Arbeitspakets 0033, und der Grund steht in der Meldung
            // selbst: Ein stilles Vortragen aller 310 Adressen saehe aus wie eine
            // gerechnete Spielrunde und waere keine.
            festkomma::abbruch(
                "kern::schritt -- der Modus spielmodus ist in diesem Rahmen nicht gebaut: seine "
                "Sollmaske umfasst alle 310 Adressen, und die Schritte 2 (Aktionen) und 6 "
                "(Abrechnung) haben noch kein Paket. Ein stilles Vortragen aller 310 waere eine "
                "Falschaussage -- es saehe aus wie eine gerechnete Spielrunde und waere keine");
        case Modus::Weltlauf:
            break;
    }

    // Die Nummer dieser Runde: die der letzten abgeschlossenen plus eins. Sie steht in
    // `partie.runde`, weil dieses Feld nach T38 in beiden Sollmasken liegt und jede Runde
    // geschrieben wird; ein Merker daneben waere ein 311. Feld gewesen (T15). Geschrieben
    // wird sie von Schritt 1, und seit Paket 0071 als Setzung statt als Vortrag -- die
    // Begruendung steht dort.
    const i64 vorrundennummer = vorrunde.lies(PLATZ_RUNDE);
    if (vorrundennummer < 0) {
        Meldung meldung;
        meldung.text("kern::schritt -- partie.runde der Vorrunde ist ");
        meldung.zahl(vorrundennummer);
        meldung.text(" und damit negativ: eine Runde vor der ersten gibt es nicht. Gelesen aus ");
        meldung.adresse(PLATZ_RUNDE);
        festkomma::abbruch(meldung.fertig());
    }
    if (vorrundennummer == festkomma::I64_MAX) {
        // Der Ueberlauf wird verhindert, nicht nachtraeglich erkannt. Mit `-fwrapv`
        // waere `+ 1` hier ein Umbruch ins Negative und damit eine Rundennummer, die der
        // Schreiber als "vor der ersten" abweisen wuerde -- mit einer Meldung, die die
        // Ursache nicht mehr nennt.
        Meldung meldung;
        meldung.text("kern::schritt -- partie.runde der Vorrunde ist ");
        meldung.zahl(vorrundennummer);
        meldung.text(
            " und damit der groesste int64_t: eine naechste Runde laesst sich nicht mehr zaehlen. "
            "Gelesen aus ");
        meldung.adresse(PLATZ_RUNDE);
        festkomma::abbruch(meldung.fertig());
    }
    const i64 diese_runde = vorrundennummer + 1;

    Schreiber rundenschreiber(vorrunde, modus, diese_runde);

    // T10b: Der Parametersatz gehoert zu diesem Zustand, oder die Runde laeuft nicht.
    //
    // **Die Pruefung steht hier und nicht beim ersten Leser eines Feldes**, und der
    // Grund ist derselbe wie beim `spielmodus` weiter oben: Heute liest kein Schritt ein
    // Feld des Traegers, also faende eine Pruefung am Leseort heute nirgends statt --
    // und der Tag, an dem der erste Schritt rechnet, ist genau der Tag, an dem niemand
    // mehr daran denkt. Ein voreingestellter Traeger rechnet nach T10b eine tote Welt,
    // die von einer gerechneten am Ergebnis nicht zu unterscheiden waere.
    //
    // Gelesen wird ueber `lies_alt` und nicht am `Zustand` vorbei: Nach T39 ist das der
    // Zugang, der den Wert am Ende der Vorrunde immer hat, und er sagt zugleich, dass
    // diese Zahl nichts ist, was die Runde erst herstellt.
    const i64 gerechnete_summe = parameter_pruefsumme(konstanten);
    const i64 summe_im_zustand = rundenschreiber.lies_alt(PLATZ_PARAMETERSUMME);
    if (gerechnete_summe != summe_im_zustand) {
        Meldung meldung;
        meldung.text(
            "kern::schritt -- die Pruefsumme des Parametersatzes passt nicht zum Zustand "
            "(T10b): der Traeger ergibt ");
        meldung.zahl(gerechnete_summe);
        meldung.text(", ");
        meldung.adresse(PLATZ_PARAMETERSUMME);
        meldung.text(" traegt ");
        meldung.zahl(summe_im_zustand);
        meldung.text(
            ". Gerechnet wird ueber die sieben Schluesselfelder des Traegers und nicht ueber "
            "die Datei. Ein Ersatzwert wird nicht gebildet");
        festkomma::abbruch(meldung.fertig());
    }

    const Bitfeld& maske = schreiber::sollmaske(modus);

    // Die aufsteigende Adressrunde (T9, keine streuende Menge). Jede gesetzte Adresse
    // geht an ihren Schritt, jede genau einmal -- der zweite Schreibzugriff waere nach
    // T18 ohnehin ein harter Fehler.
    for (Index platz = 0; platz < FELDER; ++platz) {
        const bool in_maske = maske.steht(platz);
        const Rundenschritt eigner = ZUORDNUNG[platz];

        // Die zweiseitige Probe zwischen den beiden Abschriften der Tabelle aus T38.
        // Seite 2 steht hier und nicht am Rundenende, weil sie dort gar nicht mehr
        // auffiele: Ein Schritt mit einer Adresse ausserhalb der Maske haette sie
        // geschrieben, und `Schreiber::rundenende` haette dann zwar abgebrochen, aber
        // ueber die Adresse geklagt statt ueber die Tafel.
        if (in_maske && eigner == Rundenschritt::Keiner) {
            Meldung meldung;
            meldung.text("kern::schritt -- ");
            meldung.adresse(platz);
            meldung.text(" steht in der Sollmaske, gehoert aber ");
            nenne_schritt(meldung, eigner);
            meldung.text(
                ": die Zuordnungstafel in kern/src/schritt.cpp und die Maske in "
                "kern/src/schreiber.cpp laufen auseinander");
            festkomma::abbruch(meldung.fertig());
        }
        if (!in_maske && eigner != Rundenschritt::Keiner) {
            Meldung meldung;
            meldung.text("kern::schritt -- ");
            nenne_schritt(meldung, eigner);
            meldung.text(" hat ");
            meldung.adresse(platz);
            meldung.text(
                ", und die liegt ausserhalb der Sollmaske: die Zuordnungstafel in "
                "kern/src/schritt.cpp und die Maske in kern/src/schreiber.cpp laufen auseinander");
            festkomma::abbruch(meldung.fertig());
        }
        if (!in_maske) {
            continue;  // T38: was ausserhalb liegt, behaelt seinen Startwert
        }
        if (eigner == Rundenschritt::Reaktion) {
            // Seit Paket 0197 laeuft Schritt 5 nicht mehr hier durch. Er liest den
            // **neuen** Stand der Instrumente eines Landes, und die stehen in der
            // aufsteigenden Ordnung hinter der Zustimmung -- ein Rumpf an dieser Stelle
            // braeche nach T39 an seiner ersten Adresse ab. Seine vier Adressen bleiben
            // deshalb hier liegen und werden unten geschrieben; dass keine liegen bleibt,
            // haelt die Rundenendpruefung aus T38 fest und nicht diese Auslassung.
            continue;
        }

        fuehre_schritt_aus(eigner, rundenschreiber, aktionen, platz);
    }

    // Schritt 5 -- Reaktion, als Block und nach der Adressrunde. Zu diesem Zeitpunkt sind
    // die 171 uebrigen Adressen der Sollmaske geschrieben, also auch die 16
    // Instrumentenstaende, die die Regel mit `lies_neu` liest.
    schritt_5_reaktion(vorrunde, rundenschreiber, konstanten);

    // Die zweiseitige Rundenendpruefung aus T38 gehoert dem `Schreiber` und wird hier
    // nicht nachgebaut -- nur gerufen. Sie bricht hart ab, wenn eine Maskenadresse fehlt
    // oder eine ausserhalb beruehrt wurde.
    Rundenergebnis ergebnis;
    ergebnis.neuer_zustand = rundenschreiber.rundenende();
    ergebnis.kette_dieser_runde = rundenschreiber.kette();
    return ergebnis;
}

}  // namespace kern::schritt
