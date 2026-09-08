//! Die Probe des Kennzeichenverzeichnisses selbst -- Paket 0264, um acht Waechter
//! erweitert in Paket 0270.
//!
//! **Warum es diese Datei gibt.** `kern/test/kennzeichen.hpp` traegt die
//! Zusicherungsmechanik von drei Proben; jede Zahl, die sie ueber Abbruchriegel nennen,
//! kommt aus `Buch`. Bis zum 2026-09-08 war `Buch` selbst von nichts geprueft -- es gab
//! keinen Eintrag, dessen Gegenstand der Kopf ist, sondern nur Proben, die seine
//! Richtigkeit voraussetzen. Paket 0259 hat die Lage zugespitzt: Es hat eine Bedingung
//! gelockert und konnte den Rotnachweis dafuer nicht fuehren, weil ein Fall, der rot
//! werden **muss**, in einer Probe, die gruen bleiben muss, nicht wohnen kann.
//!
//! Diese Probe ist der Ort, an dem er wohnt. Sie richtet Faelle her, in denen der Apparat
//! rot werden soll, laesst ihn urteilen und haelt **seinen Fehlerzaehler gegen eine
//! Sollzahl**. Ein Fall, der zu wenig zaehlt, ist ein Loch in der Mechanik; einer, der zu
//! viel zaehlt, ist eine Zusicherung, die weiter greift, als der Kopf sie ausweist.
//!
//! **Jeder Fall tritt als Paar auf.** Zu jeder gestoerten Fassung steht die heile
//! daneben, die sich in genau einer Sache von ihr unterscheidet. Erst das Paar ist der
//! Nachweis: Eine gestoerte Fassung allein zeigt, dass gezaehlt wurde, aber nicht, dass
//! die Stoerung der Grund war. Ablesbar ist der Unterschied an der Aufbautabelle weiter
//! unten -- die heile Fassung ist dort die leere Klammer, und jede gestoerte nennt genau
//! das eine Feld, in dem sie abweicht.
//!
//! **Sie baut eigene Aufzaehlungen.** Kein Riegel aus `kern::werte`, `kern::schritt` oder
//! `kern::festkomma` kommt hier vor. Gegenstand ist die Mechanik und keine Kernschranke;
//! ein geborgter Riegel machte aus dieser Datei eine zweite Stelle, die ueber den
//! Wortlaut des Kerns urteilt, und zwei Dateien wuerden rot, sobald jemand eine Meldung
//! umformuliert.
//!
//! **Die Tabelle hier heisst nicht `RIEGEL_OHNE_ZUSTAND`, und das ist keine Nachlaessigkeit.**
//! Der Kennzeichenriegel unter werkzeuge sucht Verzeichnisse dieses Namens unter
//! `kern/test` und verlangt zu jedem Kennzeichen eine Zeichenkette im Kern. Fuer die
//! erfundenen Meldungen dieser Probe gibt es die nicht und darf es sie nicht geben -- sie
//! beschreiben keinen Riegel des Kerns, sondern einen erdachten Apparat unter Pruefung.
//! `SCHEIN_OHNE_ZUSTAND` traegt deshalb einen eigenen Namen. Wer jenen Riegel spaeter auf
//! weitere Namen oder auf den Typ ausdehnt, muss diese Datei ausnehmen; die Begruendung
//! steht hier, damit sie dort nicht erfunden werden muss.
//!
//! **Die Ausgabe ist umgedreht, und ohne diesen Absatz sieht ein gruener Lauf falsch aus.**
//! Der Apparat druckt seine Fehlschlaege auf die Standardfehlerausgabe, und die von
//! dieser Probe **erwarteten** Fehlschlaege stehen dort genauso wie echte. Was diese Probe
//! selbst zu sagen hat, traegt deshalb den Kopf "0264" -- und nur diese Zeilen sind ihr
//! Urteil. Der Kopf bleibt "0264" auch fuer die Faelle aus 0270: Er benennt die Probe und
//! nicht das Paket, und wer nach ihm greppt, soll alle ihre Zeilen finden und nicht die
//! halben. Die Standardausgabe ist waehrend jedes Falles in die Datei umgelenkt, die
//! `MITSCHRIFT_DATEI` nennt, und danach zurueckgelesen: Ein Fall wird nicht nur an seinem
//! Zaehler gemessen, sondern auch an dem, was er gedruckt hat. Ohne diesen Umweg waere
//! die Zeile aus Paket 0259 -- die Ansage, dass das zweite Verzeichnis leer ist -- von
//! innen nicht pruefbar, denn sie hinterlaesst keinen Zaehlerstand.
//!
//! ## Die acht Nachzuegler -- Paket 0270
//!
//! Paket 0264 liess sieben Waechter des Apparats ohne Fall und nannte sie im Kopf, statt
//! sie zu verschweigen: den Durchlauf ohne Abbruch, einen Wurf, der nicht
//! `std::domain_error` ist, eine Aufrufstelle ohne jedes Kennzeichen, einen Eintrag ohne
//! Kennzeichen im zweiten Verzeichnis, die abgeschnittene Meldung, die volle Ablage und
//! mehr Kennzeichen als `KENNZEICHEN_MAX`. Sie fehlten aus Umfangsgruenden und nicht,
//! weil sie schwer waeren; die Faelle 7 bis 13 tragen sie nach.
//!
//! Der achte kommt aus der Pruefung zu 0264 und stand in keiner der sieben Zeilen:
//! `alle_stuecke_in` verlangt **alle** Stuecke einer Liste, und keiner der zwoelf Faelle
//! von 0264 trug eine mehrstueckige Liste, die sich mit einer fremden Meldung nur
//! **teilweise** deckt. Ein Rueckfall auf *irgendein Stueck genuegt* waere deshalb durch
//! alle zwoelf gruen gelaufen. Fall 14 ist der fehlende Nachweis, und er sitzt in der
//! **heilen** Haelfte: Sie zaehlt null, weil das zweite Stueck in der fremden Meldung
//! fehlt, und wird rot, sobald aus "alle" ein "irgendeins" wird.
//!
//! Keiner der acht brauchte die Ausnahme "laesst sich mit diesem Aufbau nicht
//! herrichten"; es steht deshalb auch keine im Kopf.
//!
//! ## Was auch jetzt nicht geprueft wird
//!
//! Zwei Stellen bleiben, und der Kopf nennt sie, statt sie offenzulassen. `anzahl_zu` --
//! die Zaehlung je Riegel -- ruft diese Probe nicht; sie steht nach dem Kopf des Apparats
//! fuer eine Probe, die eine **genaue** Zahl je Riegel verlangt statt "mindestens eine",
//! und ist kein Waechter, sondern eine Auskunft.
//! Und der Nullzeigerarm von `enthaelt` ist von aussen nicht zu erreichen:
//! `merke` faengt den leeren Wortlaut vorher ab, und ein Nullzeiger **in** einer
//! Kennzeichenliste ist kein Fall des Apparats, sondern einer der Liste, die ihn nennt.
//!
//! Rueckgabe 0 heisst bestanden, 1 ein verfehltes Soll, 2 ein Lauf ohne Messung: Die
//! Mitschrift liess sich nicht anlegen, und dann misst diese Probe nichts.

#include <array>
#include <cstddef>
#include <cstdio>
#include <span>
#include <stdexcept>

#include "kennzeichen.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using probe::kennzeichen::Buch;
using probe::kennzeichen::enthaelt;
using probe::kennzeichen::Kennzeichen;
using probe::kennzeichen::KENNZEICHEN_MAX;
using probe::kennzeichen::MELDUNG_ZEICHEN;
using probe::kennzeichen::MELDUNGEN_MAX;
using probe::kennzeichen::OhneZustand;

// ---------------------------------------------------------------------------
// Die erdachten Riegel
// ---------------------------------------------------------------------------
//
// Drei und nicht zwei. Der dritte kostet nichts und macht den fuenften Fall scharf: Faellt
// die Meldung eines Riegels aus, sollen **nur** die Vollzaehligkeit anschlagen und sonst
// nichts. Bei zwei Riegeln blieben nach dem Ausfall alle Meldungen beim selben Riegel, und
// die Zaehlung der fremden Paare fiele auf null -- der Fall zaehlte dann drei statt eins,
// und welcher der drei Zaehler die Stoerung gesehen hat, waere nicht mehr ablesbar.

enum class Riegel : std::size_t {
    Untergrenze,
    Obergrenze,
    Seitenwand,
    Anzahl,
};

constexpr std::array<Riegel, 3> ALLE_RIEGEL = {
    Riegel::Untergrenze,
    Riegel::Obergrenze,
    Riegel::Seitenwand,
};

static_assert(ALLE_RIEGEL.size() == static_cast<std::size_t>(Riegel::Anzahl));

const char* riegelname(Riegel welcher)
{
    switch (welcher) {
    case Riegel::Untergrenze:
        return "Untergrenze";
    case Riegel::Obergrenze:
        return "Obergrenze";
    case Riegel::Seitenwand:
        return "Seitenwand";
    case Riegel::Anzahl:
        break;
    }
    return "(kein Riegel)";
}

enum class RiegelOhneZustand : std::size_t {
    NieErreicht,
    Anzahl,
};

// ---------------------------------------------------------------------------
// Die erdachten Meldungen und ihre Listen
// ---------------------------------------------------------------------------
//
// Die Wortlaute sind so gebaut, dass jede Liste unten genau auf die Meldungen ihres
// eigenen Riegels passt -- das ist der heile Zustand, gegen den alle sechs Stoerungen
// gemessen werden. Zwei Stellen darin sind gewollt und nicht zufaellig:
//
//   * Die beiden Meldungen der Untergrenze unterscheiden sich nur in ihrer Klammer. Sie
//     sind das Paar, an dem die Haelfte "passt auf jede eigene" ueberhaupt etwas zu
//     messen hat; ohne zwei Meldungen eines Riegels laeuft sie ueber null Paare.
//   * Die Meldung der Seitenwand sagt "beruehrt" und nicht "verletzt". Dadurch trifft die
//     zu weite Liste des dritten Falles genau eine fremde Meldung und nicht zwei -- eine
//     Sollzahl, die man an der Tabelle nachzaehlen kann, statt sie zu glauben.

constexpr const char* M_UNTEN_EINS =
    "Untergrenze verletzt: der Stand liegt unter der Sohle (Zugang eins)";
constexpr const char* M_UNTEN_ZWEI =
    "Untergrenze verletzt: der Stand liegt unter der Sohle (Zugang zwei)";
constexpr const char* M_OBEN = "Obergrenze verletzt: der Stand liegt ueber der Decke";
constexpr const char* M_SEITE = "Seitenwand beruehrt: der Stand liegt neben der Bahn";
constexpr const char* M_SEITE_NACHTRAG_EINS =
    "Seitenwand beruehrt: der Stand liegt neben der Bahn (Nachtrag eins)";
constexpr const char* M_SEITE_NACHTRAG_ZWEI =
    "Seitenwand beruehrt: der Stand liegt neben der Bahn (Nachtrag zwei)";

/// Die drei Listen des heilen Zustands: jede passt auf ihre eigenen Meldungen und auf
/// keine fremde.
constexpr std::array<const char*, 2> KZ_UNTERGRENZE = {"Untergrenze", "Sohle"};
constexpr std::array<const char*, 2> KZ_OBERGRENZE  = {"Obergrenze", "Decke"};
constexpr std::array<const char*, 2> KZ_SEITENWAND  = {"Seitenwand", "Bahn"};

/// Zu weit: steht in beiden Meldungen der Untergrenze und in der der Obergrenze. Das ist
/// die Verkuerzung auf ein Allerweltsstueck, gegen die die erste Haelfte der
/// Eindeutigkeit geschrieben ist.
constexpr std::array<const char*, 1> KZ_ZU_WEIT = {"verletzt"};

/// Zu eng: steht in der ersten Meldung der Untergrenze und nicht in der zweiten. Die
/// Aufrufstelle bliebe fuer sich betrachtet heil -- ihre eigene Meldung traegt das Stueck
/// --, und trotzdem sind es dann zwei Riegel und nicht einer.
constexpr std::array<const char*, 1> KZ_NUR_ZUGANG_EINS = {"Zugang eins"};

/// Beide Stuecke stehen in der Meldung der Obergrenze -- und in den eigenen. Die
/// gestoerte Haelfte des vierzehnten Falles: Sie passt auf eine fremde Meldung, weil
/// **alle** ihre Stuecke darin vorkommen.
constexpr std::array<const char*, 2> KZ_BEIDE_FREMD = {"verletzt", "der Stand liegt"};

/// Nur das zweite Stueck steht in der Meldung der Obergrenze, das erste nicht. Die heile
/// Haelfte desselben Falles -- und die einzige Stelle dieser Probe, an der
/// `alle_stuecke_in` etwas anderes entscheidet als eine Suche nach irgendeinem Stueck.
/// Sie zaehlt null, solange "alle" gilt, und wird rot, sobald "irgendeins" genuegt.
constexpr std::array<const char*, 2> KZ_TEILWEISE = {"Untergrenze", "verletzt"};

/// Gar kein Stueck. Die Kuerze steht im Wert und nicht in einem erklaerten, aber
/// ungefuellten Feld: Ein Nullzeiger darin waere ein zweiter Fehlschlag neben dem
/// gemeinten.
constexpr Kennzeichen KZ_KEINES{};

/// Ein Stueck mehr, als `merke_meldung` ablegen kann. Die Laenge kommt aus
/// `KENNZEICHEN_MAX` selbst; eine ausgeschriebene Neun waere ein Schnappschuss und hoerte
/// auf zu messen, sobald jemand die Grenze verschiebt. Jedes Feld traegt dasselbe Stueck,
/// und dieses steht in der Meldung, an der die Liste haengt -- so bleibt der Fall bei
/// seinem einen Waechter und schlaegt nicht nebenbei als "falscher Riegel" an.
constexpr std::array<const char*, KENNZEICHEN_MAX + 1> zu_viele_stuecke()
{
    std::array<const char*, KENNZEICHEN_MAX + 1> stuecke{};
    for (const char*& stueck : stuecke) {
        stueck = "Untergrenze";
    }
    return stuecke;
}

constexpr std::array<const char*, KENNZEICHEN_MAX + 1> KZ_ZU_VIELE = zu_viele_stuecke();

/// Die Liste des Eintrags ohne Zustand. Sie passt auf keine der Meldungen -- so soll es
/// sein, und daran misst der zweite Fall, dass ueberhaupt verglichen wurde.
constexpr std::array<const char*, 1> KZ_NIE_ERREICHT = {"nie erreichte Schranke"};

// ---------------------------------------------------------------------------
// Die ueberlange Meldung
// ---------------------------------------------------------------------------
//
// Ein Zeichen mehr, als `schreibe_ab` abzuschreiben vermag, und die Laenge kommt aus
// `MELDUNG_ZEICHEN` selbst. Der Kopf traegt beide Stuecke der Seitenwandliste und steht
// vorn: Die abgeschnittene Fassung, die im Verzeichnis liegt, muss ihrer eigenen Liste
// weiterhin genuegen -- gemessen werden soll das Abschneiden und nicht ein Riegel, der
// dadurch unkenntlich wird. Kein Stueck einer fremden Liste kommt darin vor.

constexpr std::size_t UEBERLANG_ZEICHEN = MELDUNG_ZEICHEN + 1;

constexpr std::array<char, UEBERLANG_ZEICHEN + 1> baue_ueberlange_meldung()
{
    const char* kopf =
        "Seitenwand beruehrt: der Stand liegt neben der Bahn, und dann noch ";

    std::array<char, UEBERLANG_ZEICHEN + 1> text{};
    std::size_t                            i = 0;
    while (kopf[i] != '\0') {
        text[i] = kopf[i];
        ++i;
    }
    while (i < UEBERLANG_ZEICHEN) {
        text[i] = '.';
        ++i;
    }
    text[i] = '\0';
    return text;
}

constexpr std::array<char, UEBERLANG_ZEICHEN + 1> UEBERLANGE_MELDUNG =
    baue_ueberlange_meldung();

constexpr std::array<OhneZustand<RiegelOhneZustand>, 1> SCHEIN_OHNE_ZUSTAND = {{
    {RiegelOhneZustand::NieErreicht, "nie erreichte Schranke",
     "diese Probe legt zu ihr keine Meldung ab -- sie ist der Eintrag, an dem die "
     "Zaehlung der Paare ohne Zustand etwas zu zaehlen hat",
     KZ_NIE_ERREICHT},
}};

static_assert(SCHEIN_OHNE_ZUSTAND.size()
              == static_cast<std::size_t>(RiegelOhneZustand::Anzahl));

/// Derselbe Eintrag ohne seine Liste -- die gestoerte Fassung der Tabelle fuer den
/// zehnten Fall. Bei einem Riegel mit Zustand faengt `bricht_ab_mit` die leere Liste ab;
/// hier gibt es keine Aufrufstelle, die es taete, und `auswerten` ist die einzige Stelle,
/// die es noch merken kann.
constexpr std::array<OhneZustand<RiegelOhneZustand>, 1> SCHEIN_OHNE_KENNZEICHEN = {{
    {RiegelOhneZustand::NieErreicht, "nie erreichte Schranke, ohne Kennzeichen",
     "dieser Eintrag ist der gestoerte Zwilling des Eintrags darueber: dieselbe Schranke, "
     "aber ohne ein einziges Kennzeichen -- seine Liste passte damit auf jede Meldung",
     KZ_KEINES},
}};

using Verzeichnis = Buch<Riegel, RiegelOhneZustand>;

/// Die beiden Gestalten des zweiten Verzeichnisses, zwischen denen die Faelle 1 und 2
/// umschalten. Der leere Fall ist eine leere **Spanne** und keine Tabelle mit null
/// Eintraegen -- die Begruendung steht im Kopf des Apparats und ist der Gegenstand von
/// Paket 0263.
constexpr std::span<const OhneZustand<RiegelOhneZustand>> OHNE_EINTRAG{};
constexpr std::span<const OhneZustand<RiegelOhneZustand>> MIT_EINTRAG{SCHEIN_OHNE_ZUSTAND};

/// Die dritte Gestalt: ein Eintrag, dem die Liste fehlt. Sie kam mit Paket 0270 hinzu und
/// steht neben den beiden statt an ihrer Stelle -- ein bestehender Fall soll sich durch
/// sie nicht bewegen.
constexpr std::span<const OhneZustand<RiegelOhneZustand>> EINTRAG_OHNE_KENNZEICHEN{
    SCHEIN_OHNE_KENNZEICHEN};

// ---------------------------------------------------------------------------
// Der Aufbau eines Falles
// ---------------------------------------------------------------------------
//
// Die Vorbelegungen **sind** der heile Zustand. Eine Zeile der Falltabelle, die nichts
// nennt, ist der heile Lauf; jede gestoerte Zeile nennt genau das Feld, in dem sie
// abweicht. Damit steht die Stoerung eines Falles an einer Stelle statt in einem
// Vergleich zweier langer Zeilen.

/// Was die zusaetzliche Aufrufstelle der Faelle 7 und 8 tut. Die drei Werte sind die drei
/// Wege durch `bricht_ab_mit`: der Fangblock, der Sammelfang und der Durchlauf ohne
/// Abbruch. Der Wortlaut ist in allen dreien derselbe, damit sich die beiden gestoerten
/// Fassungen von der heilen in genau diesem Feld unterscheiden und in keinem zweiten.
enum class Wurf {
    Sachbereich,
    Fremd,
    Keiner,
};

/// Wie viele Meldungen der heile Lauf ablegt -- der Bezugspunkt der beiden Fuellfaelle.
/// Die Zahl wird von ihnen zugleich **gemessen** und nicht nur benutzt: Stimmte sie
/// nicht, verfehlte der volle Fall seine Null und der uebervolle seine Eins.
constexpr std::size_t HEILE_MELDUNGEN = 4;

/// Die beiden Fuellmengen. Beide kommen aus `MELDUNGEN_MAX` und nie aus der Zahl, die es
/// heute traegt.
constexpr std::size_t FUELLEN_BIS_VOLL   = MELDUNGEN_MAX - HEILE_MELDUNGEN;
constexpr std::size_t FUELLEN_UEBER_VOLL = FUELLEN_BIS_VOLL + 1;

struct Aufbau {
    /// Die Liste an der ersten Meldung der Untergrenze.
    Kennzeichen liste_eins = KZ_UNTERGRENZE;
    /// Die Liste an der zweiten.
    Kennzeichen liste_zwei = KZ_UNTERGRENZE;
    /// Ob die Meldung der Obergrenze ankommt. Falsch heisst: ein eingetragener Riegel
    /// ohne Meldung.
    bool mit_obergrenze = true;
    /// Ob ueberhaupt eine Meldung abgelegt wird.
    bool mit_meldungen = true;
    /// Ob die beiden Nachtraege an `merke` gehen.
    bool mit_nachtraegen = false;
    const char* nachtrag_eins = nullptr;
    const char* nachtrag_zwei = nullptr;
    /// Ob das zweite Verzeichnis leer bleibt.
    bool tabelle_leer = true;

    // Ab hier Paket 0270. Die Felder stehen **hinten** und nicht bei ihresgleichen: Die
    // Reihenfolge der benannten Anfangswerte muss der Reihenfolge der Felder folgen, und
    // ein Feld dazwischen haette jede bestehende Zeile der Falltabelle umgeschrieben.

    /// Ob der Eintrag des zweiten Verzeichnisses seine Kennzeichenliste verliert. Wirkt
    /// nur, solange die Tabelle nicht ohnehin leer ist.
    bool eintrag_ohne_kennzeichen = false;
    /// Ob die zusaetzliche Aufrufstelle ueberhaupt gerufen wird.
    bool mit_durchlaeufer = false;
    /// Was sie dann tut.
    Wurf durchlaeufer = Wurf::Sachbereich;
    /// Wie viele gleichlautende Meldungen zusaetzlich abgelegt werden.
    std::size_t fuellstellen = 0;
};

struct Fall {
    const char* name;
    Aufbau      aufbau;
    /// Der Stand des Fehlerzaehlers, den dieser Aufbau erzeugen muss -- die Zahl und
    /// nicht "groesser null". Eine Stoerung, die zwei Zusicherungen zugleich ausloest,
    /// waere sonst von der gemeinten nicht zu unterscheiden.
    int soll;
};

/// Wirft, was der Kern an einer Schranke wuerfe. Der Apparat faengt ausschliesslich
/// `std::domain_error`; jede andere Klasse nimmt in ihm einen anderen Weg.
void wirf(const char* wortlaut)
{
    throw std::domain_error(wortlaut);
}

/// Richtet einen Fall her, laesst den Apparat urteilen und gibt seinen Fehlerzaehler
/// zurueck.
///
/// Beide Eingaenge werden benutzt und nicht nur einer: `bricht_ab_mit` mit seinem
/// Fangblock und `merke` fuer die Stelle, die selbst gefangen hat. Sie fuehren im Apparat
/// auf dieselbe Ablage, und eine Probe, die nur einen von beiden befuellt, liesse offen,
/// ob das noch stimmt.
int lauf(const Aufbau& aufbau, const char* name)
{
    int zaehler = 0;

    const auto tabelle = aufbau.tabelle_leer ? OHNE_EINTRAG
                         : aufbau.eintrag_ohne_kennzeichen ? EINTRAG_OHNE_KENNZEICHEN
                                                           : MIT_EINTRAG;

    Verzeichnis verzeichnis{name, zaehler, ALLE_RIEGEL, &riegelname, tabelle};

    if (aufbau.mit_meldungen) {
        verzeichnis.bricht_ab_mit("Untergrenze, Zugang eins", Riegel::Untergrenze,
                                  aufbau.liste_eins, __LINE__,
                                  [] { wirf(M_UNTEN_EINS); });
        verzeichnis.merke(Riegel::Untergrenze, "Untergrenze, Zugang zwei", __LINE__,
                          aufbau.liste_zwei, M_UNTEN_ZWEI);
        if (aufbau.mit_obergrenze) {
            verzeichnis.bricht_ab_mit("Obergrenze", Riegel::Obergrenze, KZ_OBERGRENZE,
                                      __LINE__, [] { wirf(M_OBEN); });
        }
        verzeichnis.merke(Riegel::Seitenwand, "Seitenwand", __LINE__, KZ_SEITENWAND,
                          M_SEITE);
    }

    if (aufbau.mit_nachtraegen) {
        verzeichnis.merke(Riegel::Seitenwand, "Nachtrag eins", __LINE__, KZ_SEITENWAND,
                          aufbau.nachtrag_eins);
        verzeichnis.merke(Riegel::Seitenwand, "Nachtrag zwei", __LINE__, KZ_SEITENWAND,
                          aufbau.nachtrag_zwei);
    }

    // Die zusaetzliche Stelle der Faelle 7 und 8. Sie kommt **zu** den vier Meldungen
    // hinzu und nimmt keiner ihren Platz: Ersetzte sie eine, fiele mit ihr entweder die
    // Vollzaehligkeit oder die Zaehlung der eigenen Paare aus, und der Fall zaehlte zwei
    // statt eins -- gemessen werden soll der eine Weg durch `bricht_ab_mit` und nicht,
    // was sein Ausfall nebenbei umwirft.
    if (aufbau.mit_durchlaeufer) {
        verzeichnis.bricht_ab_mit(
            "Seitenwand, zusaetzliche Stelle", Riegel::Seitenwand, KZ_SEITENWAND,
            __LINE__, [&aufbau] {
                if (aufbau.durchlaeufer == Wurf::Sachbereich) {
                    wirf(M_SEITE_NACHTRAG_ZWEI);
                } else if (aufbau.durchlaeufer == Wurf::Fremd) {
                    // Mit Absicht die Oberklasse von std::domain_error: Wer den Fangblock
                    // auf sie erweiterte, finge diesen Wurf und legte ihn ab -- der Fall
                    // zaehlte dann null statt eins und wird rot.
                    throw std::logic_error(M_SEITE_NACHTRAG_ZWEI);
                }
            });
    }

    // Die Fuellstellen des zwoelften Falles. Alle tragen denselben Wortlaut und dieselbe
    // Liste; gemessen wird allein, wie viele die Ablage aufnimmt.
    for (std::size_t i = 0; i < aufbau.fuellstellen; ++i) {
        verzeichnis.merke(Riegel::Seitenwand, "Fuellstelle", __LINE__, KZ_SEITENWAND,
                          M_SEITE);
    }

    verzeichnis.auswerten();
    return zaehler;
}

// ---------------------------------------------------------------------------
// Die achtundzwanzig Faelle -- vierzehn Paare
// ---------------------------------------------------------------------------
//
// Die Sollzahlen sind nachzaehlbar und keine abgelesenen Messwerte. Der heile Lauf legt
// vier Meldungen ab: zwei zur Untergrenze, je eine zur Obergrenze und zur Seitenwand.
// Daraus zwoelf geordnete Paare, davon zwei eigene und zehn fremde, und keine Liste passt
// auf eine fremde Meldung -- Zaehlerstand null.
//
//   Fall 1  Der leere Fall wird genannt. Beide Fassungen zaehlen null; gemessen wird
//           allein, ob die Zeile "keiner eingetragen" in der Mitschrift steht. Sie muss
//           genau dann dastehen, wenn das zweite Verzeichnis leer ist -- das ist die
//           Ansage, die Paket 0259 an die Stelle der aufgegebenen Zaehlung gesetzt hat,
//           und die einzige Zusicherung dieser Probe, die keinen Zaehlerstand hinterlaesst.
//
//   Fall 2  Die Zaehlung der Paare ohne Zustand. Ohne jede Meldung schlagen vier
//           Zusicherungen an: die Vollzaehligkeit dreimal, die fremden Paare und die
//           eigenen je einmal -- macht fuenf. Mit einem Eintrag im zweiten Verzeichnis
//           kommt die Zaehlung der Paare ohne Zustand hinzu: sechs. **Der Unterschied von
//           genau eins ist der Nachweis**, dass es diese Zaehlung war und keine andere,
//           und er ist zugleich der Rotnachweis fuer die Lockerung aus Paket 0259.
//
//   Fall 3  Eine Liste, die auf eine fremde Meldung passt. "verletzt" steht in beiden
//           Meldungen der Untergrenze und in der der Obergrenze; beide Untergrenzstellen
//           schlagen also gegen dieselbe fremde Meldung an -- zwei Verletzungen, dazu die
//           Zusicherung ueber ihre Zahl: drei.
//
//   Fall 4  Eine Liste, die nicht auf eine eigene Meldung passt. "Zugang eins" steht in
//           der ersten Meldung der Untergrenze und nicht in der zweiten -- eine
//           Verletzung, dazu die Zusicherung ueber ihre Zahl: zwei. Die Stelle ist fuer
//           sich betrachtet heil, und genau das ist der Grund, warum es diese Haelfte
//           gibt.
//
//   Fall 5  Ein eingetragener Riegel ohne angekommene Meldung. Die Vollzaehligkeit
//           schlaegt einmal an und sonst nichts -- die uebrigen beiden Riegel tragen
//           weiterhin eigene und fremde Paare.
//
//   Fall 6  Leerer Wortlaut an `merke`. Zwei Nachtraege, einer mit leerer Zeichenkette
//           und einer ohne jeden Zeiger: beide Wege durch dieselbe Wache, beide gezaehlt,
//           keiner abgelegt. Die heile Fassung legt dieselben zwei Nachtraege mit
//           Wortlaut ab -- der Riegel Seitenwand traegt dann drei Meldungen, und die
//           Zaehlung bleibt bei null.
//
// Ab hier Paket 0270. Alle acht haengen an der zusaetzlichen Stelle, an einer Liste oder
// an der Tabelle -- keiner ruehrt an den sechs oben, und keine ihrer Sollzahlen sinkt.
//
//   Fall 7  Der Aufruf, der nicht abbricht. Die zusaetzliche Stelle wirft nicht; die vier
//           Meldungen kommen unveraendert an, und `bricht_ab_mit` zaehlt hinter seinem
//           Fangblock einmal: eins. Faellt dieser Zweig weg, zaehlt der Fall null.
//
//   Fall 8  Der Wurf, den der Fangblock nicht kennt. Dieselbe Stelle wirft
//           `std::logic_error` -- die Oberklasse dessen, was der Apparat faengt --, also
//           greift der Sammelfang: eins, und nichts wird abgelegt. Der Wortlaut ist
//           derselbe, mit dem die heile Fassung wirft. Das ist der Kern des Falles: Wer
//           den Fangblock auf die Oberklasse erweiterte, legte diesen Wurf sauber ab und
//           zaehlte null.
//
//   Fall 9  Die Aufrufstelle ohne jedes Kennzeichen. Drei Zusicherungen zugleich, und
//           alle drei gehoeren zur Sache: eins fuer die fehlende Liste; zwei fuer die
//           fremden Meldungen der Obergrenze und der Seitenwand, auf die die leere Liste
//           **passt** -- eine leere Liste passt auf jeden Text --; und eins fuer die
//           Zaehlung der Verletzungen. Macht vier. Der Kopf von `alle_stuecke_in` nennt
//           den leeren Fall harmlos, weil er vorher auffalle; er faellt vorher auf und
//           danach noch zweimal.
//
//   Fall 10 Der Eintrag des zweiten Verzeichnisses ohne Kennzeichen. `auswerten`
//           ueberspringt ihn nach der Meldung, also zaehlt keine seiner Paarungen: eins
//           fuer die fehlende Liste, eins fuer die Zaehlung der Paare ohne Zustand, die
//           damit auf null faellt, eins fuer die Zaehlung der Verletzungen. Drei.
//
//   Fall 11 Die Meldung, die laenger ist, als `schreibe_ab` abschreiben kann. Sie geht
//           als erster Nachtrag ein; abgelegt wird die abgeschnittene Fassung, gezaehlt
//           wird einmal. Ihr Kopf traegt beide Stuecke der Seitenwandliste, damit die
//           abgeschnittene Fassung ihrem eigenen Riegel weiterhin genuegt und der Fall
//           bei seiner Eins bleibt.
//
//   Fall 12 Die volle Ablage. Die heile Haelfte fuellt sie **genau** bis an den Rand und
//           zaehlt null, die gestoerte legt eine Meldung mehr auf und zaehlt eins. Das
//           Paar misst dabei mehr als seinen Waechter: Waere der Bezugspunkt der vier
//           Meldungen des heilen Laufs falsch, verfehlten beide Haelften ihr Soll.
//
//   Fall 13 Ein Kennzeichen mehr, als abgelegt werden kann. `merke_meldung` weist die
//           Meldung ab -- eins --, und mit ihr faellt die einzige zweite Meldung der
//           Untergrenze weg, so dass die Zaehlung der eigenen Paare auf null geht: eins.
//           Zwei. Beide gehoeren zum selben Vorgang, und der Kopf sagt es hier, damit die
//           Zwei nicht als Rundungsfehler gelesen wird.
//
//   Fall 14 Der achte Waechter: `alle_stuecke_in` verlangt **alle** Stuecke. Die gestoerte
//           Liste traegt zwei Stuecke, die **beide** in der Meldung der Obergrenze stehen
//           -- eine Verletzung, dazu ihre Zaehlung: zwei. Die heile traegt zwei, von denen
//           nur eines darin steht: null. Die Aussage steckt in der **heilen** Haelfte.
//           Genuegte irgendein Stueck, passte sie auf die fremde Meldung und zaehlte
//           statt null ebenfalls zwei.

constexpr std::array<Fall, 28> FAELLE = {{
    {"1a leeres Verzeichnis, heil", {}, 0},
    {"1b ein Eintrag, heil", {.tabelle_leer = false}, 0},

    {"2a ein Eintrag, keine Meldung", {.mit_meldungen = false, .tabelle_leer = false}, 6},
    {"2b leer, keine Meldung", {.mit_meldungen = false}, 5},

    {"3a Liste passt auf eine fremde",
     {.liste_eins = KZ_ZU_WEIT, .liste_zwei = KZ_ZU_WEIT},
     3},
    {"3b Liste passt auf keine fremde", {}, 0},

    {"4a Liste passt nicht auf eigene", {.liste_eins = KZ_NUR_ZUGANG_EINS}, 2},
    {"4b Liste passt auf jede eigene", {}, 0},

    {"5a Riegel ohne Meldung", {.mit_obergrenze = false}, 1},
    {"5b jeder Riegel mit Meldung", {}, 0},

    {"6a leerer Wortlaut an merke",
     {.mit_nachtraegen = true, .nachtrag_eins = "", .nachtrag_zwei = nullptr},
     2},
    {"6b Wortlaut an merke",
     {.mit_nachtraegen = true,
      .nachtrag_eins  = M_SEITE_NACHTRAG_EINS,
      .nachtrag_zwei  = M_SEITE_NACHTRAG_ZWEI},
     0},

    {"7a Durchlauf ohne Abbruch",
     {.mit_durchlaeufer = true, .durchlaeufer = Wurf::Keiner},
     1},
    {"7b Abbruch wie erwartet", {.mit_durchlaeufer = true}, 0},

    {"8a Wurf, den der Fang nicht kennt",
     {.mit_durchlaeufer = true, .durchlaeufer = Wurf::Fremd},
     1},
    {"8b Wurf, den der Fang kennt", {.mit_durchlaeufer = true}, 0},

    {"9a Stelle ohne Kennzeichen", {.liste_eins = KZ_KEINES}, 4},
    {"9b Stelle mit Kennzeichen", {}, 0},

    {"10a Eintrag ohne Kennzeichen",
     {.tabelle_leer = false, .eintrag_ohne_kennzeichen = true},
     3},
    {"10b Eintrag mit Kennzeichen", {.tabelle_leer = false}, 0},

    {"11a Meldung zu lang",
     {.mit_nachtraegen = true,
      .nachtrag_eins  = UEBERLANGE_MELDUNG.data(),
      .nachtrag_zwei  = M_SEITE_NACHTRAG_ZWEI},
     1},
    {"11b Meldung passt",
     {.mit_nachtraegen = true,
      .nachtrag_eins  = M_SEITE_NACHTRAG_EINS,
      .nachtrag_zwei  = M_SEITE_NACHTRAG_ZWEI},
     0},

    {"12a eine Meldung zu viel", {.fuellstellen = FUELLEN_UEBER_VOLL}, 1},
    {"12b Ablage genau voll", {.fuellstellen = FUELLEN_BIS_VOLL}, 0},

    {"13a ein Kennzeichen zu viel", {.liste_eins = KZ_ZU_VIELE}, 2},
    {"13b Kennzeichen passen", {}, 0},

    {"14a beide Stuecke in der fremden", {.liste_eins = KZ_BEIDE_FREMD}, 2},
    {"14b nur ein Stueck in der fremden", {.liste_eins = KZ_TEILWEISE}, 0},
}};

// ---------------------------------------------------------------------------
// Die Mitschrift
// ---------------------------------------------------------------------------
//
// Der Apparat druckt seine Ansagen auf die Standardausgabe. Um sie zu pruefen statt sie
// nur zu erzeugen, laeuft jeder Fall mit einer Standardausgabe, die in eine Datei zeigt;
// danach wird dieselbe Datei zurueckgelesen. Die Datei bleibt liegen und wird von jedem
// Fall neu abgeschnitten -- was am Ende darin steht, ist die Mitschrift des letzten
// Falles.
//
// Schlaegt das Umlenken fehl, ist die Standardausgabe geschlossen und jeder weitere Druck
// des Apparats ginge ins Leere. Der Lauf bricht dann mit Rueckgabe 2 ab, statt gruen
// weiterzuzaehlen: Eine Probe, die ihr Messgeraet verloren hat, hat kein Ergebnis.

constexpr const char* MITSCHRIFT_DATEI = "kennzeichen_probe.mitschrift";
constexpr std::size_t MITSCHRIFT_ZEICHEN = 16384;

/// Die Zeile, die der Apparat seit Paket 0259 bei leerem zweitem Verzeichnis druckt.
constexpr const char* LEERZEILE = "keiner eingetragen";

std::array<char, MITSCHRIFT_ZEICHEN> mitschrift{};

}  // namespace

int main()
{
    std::fprintf(stderr,
                 "0264: Diese Probe erzeugt absichtlich Fehlschlaege des Apparats aus "
                 "kern/test/kennzeichen.hpp.\n0264: Jede Zeile ohne den Kopf \"0264\" "
                 "stammt aus einem hergerichteten Fall und ist gewollt; das Urteil steht "
                 "in den Zeilen mit dem Kopf.\n");

    int fehlgeschlagen = 0;

    for (const Fall& fall : FAELLE) {
        if (std::freopen(MITSCHRIFT_DATEI, "w+", stdout) == nullptr) {
            std::fprintf(stderr,
                         "0264: die Mitschrift %s liess sich nicht anlegen. Ohne sie ist "
                         "die Ansage bei leerem Verzeichnis nicht pruefbar, und ein Lauf "
                         "ohne Messung ist kein gruener Lauf.\n",
                         MITSCHRIFT_DATEI);
            return 2;
        }

        const int gemessen = lauf(fall.aufbau, fall.name);

        std::fflush(stdout);
        std::rewind(stdout);
        const std::size_t gelesen =
            std::fread(mitschrift.data(), 1, mitschrift.size() - 1, stdout);
        mitschrift[gelesen] = '\0';

        const bool vollstaendig  = gelesen < mitschrift.size() - 1;
        const bool zeile_steht   = enthaelt(mitschrift.data(), LEERZEILE);
        const bool zaehler_passt = gemessen == fall.soll;
        const bool zeile_passt   = zeile_steht == fall.aufbau.tabelle_leer;

        if (zaehler_passt && zeile_passt && vollstaendig) {
            std::fprintf(stderr, "0264 ok  %-34s Zaehler %d, Ansage %s\n", fall.name,
                         gemessen, zeile_steht ? "gedruckt" : "nicht gedruckt");
            continue;
        }

        ++fehlgeschlagen;
        std::fprintf(stderr,
                     "0264 FEHLGESCHLAGEN %s\n"
                     "  Fehlerzaehler:    erwartet %d, gemessen %d\n"
                     "  Ansage \"%s\": erwartet %s, gefunden %s\n"
                     "  Mitschrift (%s):\n%s",
                     fall.name, fall.soll, gemessen, LEERZEILE,
                     fall.aufbau.tabelle_leer ? "gedruckt" : "nicht gedruckt",
                     zeile_steht ? "gedruckt" : "nicht gedruckt",
                     vollstaendig ? "vollstaendig" : "ABGESCHNITTEN, sie fasst zu wenig",
                     mitschrift.data());
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stderr,
                     "0264: alle %zu Faelle bestanden -- der Apparat zaehlt in jedem "
                     "hergerichteten Fall genau so oft, wie sein Kopf es ausweist, und "
                     "die heile Fassung daneben zaehlt nicht mit.\n",
                     FAELLE.size());
        return 0;
    }

    std::fprintf(stderr, "0264: %d von %zu Faellen verfehlt.\n", fehlgeschlagen,
                 FAELLE.size());
    return 1;
}
