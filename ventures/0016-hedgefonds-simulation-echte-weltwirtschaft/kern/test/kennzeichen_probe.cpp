//! Die Probe des Kennzeichenverzeichnisses selbst -- Paket 0264.
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
//! Urteil. Die Standardausgabe ist waehrend jedes Falles in die Datei umgelenkt, die
//! `MITSCHRIFT_DATEI` nennt, und danach zurueckgelesen: Ein Fall wird nicht nur an seinem
//! Zaehler gemessen, sondern auch an dem, was er gedruckt hat. Ohne diesen Umweg waere
//! die Zeile aus Paket 0259 -- die Ansage, dass das zweite Verzeichnis leer ist -- von
//! innen nicht pruefbar, denn sie hinterlaesst keinen Zaehlerstand.
//!
//! ## Was hier **nicht** geprueft wird
//!
//! Sechs Faelle, und der Kopf nennt die Luecke, statt sie offenzulassen: ungeprueft
//! bleiben der Durchlauf ohne Abbruch, ein Wurf, der nicht `std::domain_error` ist, eine
//! Aufrufstelle ohne jedes Kennzeichen, ein Eintrag ohne Kennzeichen im zweiten
//! Verzeichnis, die abgeschnittene Meldung, die volle Ablage und mehr Kennzeichen als
//! `KENNZEICHEN_MAX`. Jeder davon ist derselbe Bau wie die sechs hier -- eine Zeile in der
//! Aufbautabelle und eine Sollzahl. Sie fehlen aus Umfangsgruenden und nicht, weil sie
//! schwer waeren.
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

/// Die Liste des Eintrags ohne Zustand. Sie passt auf keine der Meldungen -- so soll es
/// sein, und daran misst der zweite Fall, dass ueberhaupt verglichen wurde.
constexpr std::array<const char*, 1> KZ_NIE_ERREICHT = {"nie erreichte Schranke"};

constexpr std::array<OhneZustand<RiegelOhneZustand>, 1> SCHEIN_OHNE_ZUSTAND = {{
    {RiegelOhneZustand::NieErreicht, "nie erreichte Schranke",
     "diese Probe legt zu ihr keine Meldung ab -- sie ist der Eintrag, an dem die "
     "Zaehlung der Paare ohne Zustand etwas zu zaehlen hat",
     KZ_NIE_ERREICHT},
}};

static_assert(SCHEIN_OHNE_ZUSTAND.size()
              == static_cast<std::size_t>(RiegelOhneZustand::Anzahl));

using Verzeichnis = Buch<Riegel, RiegelOhneZustand>;

/// Die beiden Gestalten des zweiten Verzeichnisses, zwischen denen die Faelle 1 und 2
/// umschalten. Der leere Fall ist eine leere **Spanne** und keine Tabelle mit null
/// Eintraegen -- die Begruendung steht im Kopf des Apparats und ist der Gegenstand von
/// Paket 0263.
constexpr std::span<const OhneZustand<RiegelOhneZustand>> OHNE_EINTRAG{};
constexpr std::span<const OhneZustand<RiegelOhneZustand>> MIT_EINTRAG{SCHEIN_OHNE_ZUSTAND};

// ---------------------------------------------------------------------------
// Der Aufbau eines Falles
// ---------------------------------------------------------------------------
//
// Die Vorbelegungen **sind** der heile Zustand. Eine Zeile der Falltabelle, die nichts
// nennt, ist der heile Lauf; jede gestoerte Zeile nennt genau das Feld, in dem sie
// abweicht. Damit steht die Stoerung eines Falles an einer Stelle statt in einem
// Vergleich zweier langer Zeilen.
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
    int         zaehler = 0;
    Verzeichnis verzeichnis{name, zaehler, ALLE_RIEGEL, &riegelname,
                            aufbau.tabelle_leer ? OHNE_EINTRAG : MIT_EINTRAG};

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

    verzeichnis.auswerten();
    return zaehler;
}

// ---------------------------------------------------------------------------
// Die zwoelf Faelle -- sechs Paare
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

constexpr std::array<Fall, 12> FAELLE = {{
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
