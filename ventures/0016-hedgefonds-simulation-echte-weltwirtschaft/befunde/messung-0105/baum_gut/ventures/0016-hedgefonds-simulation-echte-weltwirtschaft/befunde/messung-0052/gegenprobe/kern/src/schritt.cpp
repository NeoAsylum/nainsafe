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
//! **Und das ist eine Eigenschaft des Rahmens, nicht der Architektur.** Wer Schritt 4
//! baut, ersetzt den Rumpf von `schritt_4_wirtschaft` durch die Rechnung; die nimmt ihren
//! Block als Ganzes, weil sie Eingangsgroessen braucht, und dann steigt die Kette nicht
//! mehr auf. Genau dann soll sie es nicht mehr -- dasselbe gilt fuer die unveraenderte
//! Pruefsumme. Das Folgepaket zieht beide Aussagen nach.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
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
// Die sechs Schritte aus `spiel.md`, Abschnitt "Die Schleife"
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
    teile_zu(tafel, zustand::stelle_partie(PartieFeld::Runde), Rundenschritt::Ansicht);
    teile_zu(tafel, zustand::stelle_partie(PartieFeld::JahrgangId), Rundenschritt::Ansicht);
    teile_zu(tafel, zustand::stelle_partie(PartieFeld::ParameterPruefsumme),
             Rundenschritt::Ansicht);

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
// ihren Adressblock aus T38 im Kommentar; jede bekommt heute eine Adresse ihres Blocks
// und traegt sie unveraendert vor.
//
// `vortrag` ist genau dafuer da: "Eine Adresse, die sich nicht aendert, wird trotzdem
// geschrieben -- *unveraendert* ist eine Aussage und keine Luecke." Verzoegerung null,
// Beitrag 1.000 Promille und `alt == neu` folgen daraus und stehen im `Schreiber`, nicht
// hier.

/// **Schritt 1 -- Ansicht.** Nach `spiel.md`: "Der Zustand, und daneben die Kette der
/// Vorrunde." Der Schritt zeigt; geschrieben wird an ihm nur die Buchfuehrung der Runde.
///
/// T38-Block: `Partie: Runde, Jahrgangskennung, Parametersatz-Pruefsumme` -- 3 Adressen,
/// in der Maske `weltlauf`.
///
/// **Was hier noch nicht steht:** Der Rahmen traegt `partie.runde` unveraendert vor,
/// statt sie hochzuzaehlen. Das ist der Zuschnitt von Paket 0033 -- eine Runde, die
/// weiterzaehlt, aendert die Pruefsumme, und die Unveraendertheit der Pruefsumme ist die
/// Aussage, an der dieser Rahmen gemessen wird. Die Nummer *dieser* Runde steht
/// trotzdem an jedem der 175 Ursachensaetze; wer diesen Schritt baut, schreibt sie
/// zusaetzlich in das Feld.
void schritt_1_ansicht(Schreiber& schreiber, Index platz) { schreiber.vortrag(platz); }

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
void schritt_5_reaktion(Schreiber& schreiber, Index platz) { schreiber.vortrag(platz); }

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
            schritt_5_reaktion(schreiber, platz);
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

Rundenergebnis schritt(const Zustand& vorrunde, const Aktionsbuendel& aktionen, Modus modus)
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
    // geschrieben wird; ein Merker daneben waere ein 311. Feld gewesen (T15).
    const i64 vorrundennummer = vorrunde.lies(zustand::stelle_partie(PartieFeld::Runde));
    if (vorrundennummer < 0) {
        Meldung meldung;
        meldung.text("kern::schritt -- partie.runde der Vorrunde ist ");
        meldung.zahl(vorrundennummer);
        meldung.text(" und damit negativ: eine Runde vor der ersten gibt es nicht. Gelesen aus ");
        meldung.adresse(zustand::stelle_partie(PartieFeld::Runde));
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
        meldung.adresse(zustand::stelle_partie(PartieFeld::Runde));
        festkomma::abbruch(meldung.fertig());
    }
    const i64 diese_runde = vorrundennummer + 1;

    Schreiber rundenschreiber(vorrunde, modus, diese_runde);
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

        fuehre_schritt_aus(eigner, rundenschreiber, aktionen, platz);
    }

    // Die zweiseitige Rundenendpruefung aus T38 gehoert dem `Schreiber` und wird hier
    // nicht nachgebaut -- nur gerufen. Sie bricht hart ab, wenn eine Maskenadresse fehlt
    // oder eine ausserhalb beruehrt wurde.
    Rundenergebnis ergebnis;
    ergebnis.neuer_zustand = rundenschreiber.rundenende();
    ergebnis.kette_dieser_runde = rundenschreiber.kette();
    return ergebnis;
}

}  // namespace kern::schritt
