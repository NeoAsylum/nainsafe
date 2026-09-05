//! Zufall -- der Abbruch und die Zahlenproben.
//!
//! Das Verfahren steht in `include/kern/zufall.hpp`, weil es `constexpr` sein muss.
//! Hier steht, was nicht `constexpr` sein kann (der Abbruch) und was nicht in einen
//! Kopf gehoert (die Proben). Dieselbe Aufteilung wie bei `festkomma` und
//! `pruefsumme`.
//!
//! **Die Proben sind `static_assert`, und das ist der Punkt.** Sie laufen beim
//! Uebersetzen, nicht beim Testen. Eine verfehlte Konstante, eine vertauschte Zeile im
//! Verfahren oder eine andere Saatregel sind damit kein roter Test, den jemand lesen
//! muss, sondern eine Datei, die sich nicht uebersetzen laesst. Was ein
//! `static_assert` nicht kann -- unter den Sanitizern laufen und die Zahlen
//! ausschreiben --, steht in `test/zufall_probe.cpp`.
//!
//! ## Warum hier fremde Zahlen stehen
//!
//! **Jeder Erwartungswert des Verfahrens in dieser Datei stammt aus einer
//! Veroeffentlichung, keiner aus diesem Programm.** Ein selbst erzeugter
//! Erwartungswert pruefte nur, dass der Code heute dasselbe tut wie gestern -- er kann
//! nicht zeigen, dass hier SplitMix64 und xoshiro256** gerechnet werden und nicht
//! irgendetwas anderes, das sich reproduzierbar irrt. Dieser Unterschied wiegt in
//! diesem Modul schwerer als anderswo: Ein Zufallserzeuger sieht auch dann richtig
//! aus, wenn er falsch ist, weil seine Ausgabe in jedem Fall zufaellig aussieht.
//!
//! Die drei Konstanten des Mischers bekommen deshalb keine eigene Probe. Sie brauchen
//! auch keine: Ein einziges verkehrtes Halbbyte in einer von ihnen laesst jeden der
//! zehn veroeffentlichten Werte unten fehlschlagen.
//!
//! Nur die Ableitungseigenschaften am Ende stehen als Beziehungen zwischen selbst
//! gerechneten Zahlen da -- „gleich", „verschieden", „unabhaengig von der
//! Reihenfolge". Das ist die schwaechere Behauptung und der staerkere Nachweis: Sie
//! verlangt keinen Wert, den nur dieses Programm kennt.
//!
//! Die Quellen mit Abrufdatum stehen im Kopf von `include/kern/zufall.hpp`.

#include <array>
#include <cstddef>
#include <stdexcept>

#include "kern/zufall.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::zufall {

void abbruch(const char* grund)
{
    // `std::domain_error` und nicht das Abwuergen des Programms: siehe die
    // Begruendung an der Deklaration in `zufall.hpp`. Kurz -- ein Wurf ist zur
    // Uebersetzungszeit pruefbar und zur Laufzeit nachweisbar, ein Signal ist beides
    // nicht.
    throw std::domain_error(grund);
}

// ---------------------------------------------------------------------------
// Probe 1 -- SplitMix64 gegen veroeffentlichte Werte (Abnahme 3)
// ---------------------------------------------------------------------------
//
// [XOSHIRO-RS] fuehrt im Testblock `reference` fuenfzig Ausgaben zum Startwert
// 1477776061723855037 auf und schreibt daneben, woher sie kommen: „These values were
// produced with the reference implementation: http://xoshiro.di.unimi.it/splitmix64.c".
// Die ersten sechs stehen hier.
//
// **Was diese sechs Werte belegen und was nicht.** Sie belegen die drei Konstanten,
// die Reihenfolge der drei Mischzeilen, die drei Verschiebeweiten (30, 27, 31) und
// -- weil es sechs aufeinanderfolgende sind -- die Fortschreibung `stand +=
// SPLITMIX_SCHRITT` zwischen den Ausgaben. Sie belegen nicht die Saatregel und nicht
// xoshiro256**; dafuer steht Probe 2 daneben.

static_assert(
    [] {
        u64 stand = 1477776061723855037ULL;
        std::array<u64, 6> ausgaben{};
        for (std::size_t i = 0; i < ausgaben.size(); ++i) {
            ausgaben[i] = splitmix64_naechster(stand);
        }
        return ausgaben;
    }() == std::array<u64, 6>{1985237415132408290ULL,
                              2979275885539914483ULL,
                              13511426838097143398ULL,
                              8488337342461049707ULL,
                              15141737807933549159ULL,
                              17093170987380407015ULL},
    "[XOSHIRO-RS] splitmix64.rs, Testblock `reference`, Startwert 1477776061723855037, "
    "die ersten sechs der fuenfzig aufgefuehrten Ausgaben");

// Und die Zusicherung aus dem Kopf von `zufall.hpp`, dass `einruehren` mit null
// genau dieser Schritt ist -- sonst waere die Ableitung unten an ein Verfahren
// gebunden, das keine der Proben trifft.
static_assert(
    [] {
        u64 stand = 1477776061723855037ULL;
        return splitmix64_naechster(stand);
    }() == einruehren(1477776061723855037ULL, 0ULL),
    "einruehren(stand, 0) ist genau ein Schritt des Referenzerzeugers ab stand");

// ---------------------------------------------------------------------------
// Probe 2 -- Saatregel und xoshiro256** in einem Stueck (Abnahme 3)
// ---------------------------------------------------------------------------
//
// [XOSHIRO-CPP] nennt in seiner Beschreibung den Vektor ausdruecklich: „When
// initialized with SplitMix64 seeded with 100, the generator should produce these four
// consecutive 64-bit values". Der Quelltext daneben zeigt, was „initialized with
// SplitMix64 seeded with 100" heisst -- vier aufeinanderfolgende Ausgaben von
// SplitMix64 ab dem Stand 100, in die Worte 0 bis 3.
//
// **Das ist der schaerfste Vektor, den es fuer dieses Modul gibt.** Er laeuft ueber
// beide Verfahren und ueber die Naht dazwischen: Saatregel, Wortreihenfolge, die
// Bildung der Ausgabe aus `s[1]`, beide Rotationsweiten, die Verschiebung um 17 und
// die Reihenfolge der sechs Fortschreibungszeilen. Vier aufeinanderfolgende Ausgaben
// treffen nur dann alle, wenn jedes einzelne davon stimmt.

static_assert(
    [] {
        Strom strom{strom_aus_keim(100ULL)};
        std::array<u64, 4> ausgaben{};
        for (std::size_t i = 0; i < ausgaben.size(); ++i) {
            ausgaben[i] = strom.naechster();
        }
        return ausgaben;
    }() == std::array<u64, 4>{792317387143481937ULL,
                              1418856489092323125ULL,
                              6662743737787356053ULL,
                              9823178768685107703ULL},
    "[XOSHIRO-CPP] Testvektor zum Keim 100, die vier aufeinanderfolgenden Ausgaben");

// Dieselbe Quelle nennt die vier Zahlen zweimal, dezimal und hexadezimal. Ein
// vertippter Ziffernblock in den zwanzigstelligen Dezimalzahlen oben faellt beim Lesen
// nicht auf; gegen die zweite Schreibweise derselben Veroeffentlichung gehalten,
// muesste er in beiden Formen derselbe sein.
static_assert(792317387143481937ULL == 0x0afee0773a0d8a51ULL,
              "[XOSHIRO-CPP] nennt denselben Wert als 0afee077'3a0d8a51");
static_assert(1418856489092323125ULL == 0x13b0ca759b9b1735ULL,
              "[XOSHIRO-CPP] nennt denselben Wert als 13b0ca75'9b9b1735");
static_assert(6662743737787356053ULL == 0x5c76d220f8461395ULL,
              "[XOSHIRO-CPP] nennt denselben Wert als 5c76d220'f8461395");
static_assert(9823178768685107703ULL == 0x8852f10b70a289f7ULL,
              "[XOSHIRO-CPP] nennt denselben Wert als 8852f10b'70a289f7");

// ---------------------------------------------------------------------------
// Probe 3 -- die zweite Stelle wird nie ueber eine Zahl geschrieben (Abnahme 2)
// ---------------------------------------------------------------------------
//
// T11: die `zweck_id` „wird nie ueber eine Zahl geschrieben". Das ist hier keine
// Konvention und keine Bitte an den naechsten Bauagenten, sondern eine Regel des
// Uebersetzers -- und die folgenden zwei Zeilen sind ihr Nachweis. Sie fragen, ob ein
// Aufruf ueberhaupt zustande kaeme: mit dem Namen ja, mit einer nackten Zahl an
// derselben Stelle nicht.
//
// Der Nachweis steht hier und nicht in der laufenden Probe, weil eine laufende Probe
// ihn gar nicht fuehren koennte: Was nicht uebersetzt, laesst sich nicht ausfuehren.
//
// Die Frage muss ueber einen Typparameter laufen. Ein `requires`, das den verbotenen
// Aufruf ausgeschrieben enthaelt, waere selbst der Uebersetzungsfehler, den es
// nachweisen will -- fuer einen Ausdruck, in dem nichts von einem Parameter abhaengt,
// urteilt der Uebersetzer sofort und nicht erst beim Einsetzen. Mit dem Parameter
// wird aus dem Fehler eine Antwort: „dieser Typ passt an die vierte Stelle, jener
// nicht."

template <typename ZweckTyp>
constexpr bool ableitung_nimmt = requires(ZweckTyp zweck) {
    splitmix64(0ULL, 0, 0ULL, zweck, 0, 0);
};

static_assert(ableitung_nimmt<Zweck>,
              "der Aufruf mit dem Namen muss zustande kommen -- sonst pruefen die "
              "Zeilen darunter nichts");

static_assert(!ableitung_nimmt<int>,
              "Abnahme 2: eine nackte Zahl als zweck_id findet die Ableitung nicht");
static_assert(!ableitung_nimmt<u64>,
              "Abnahme 2: auch nicht als vorzeichenlose 64-Bit-Zahl");
static_assert(!ableitung_nimmt<i64>,
              "Abnahme 2: auch nicht als vorzeichenbehaftete 64-Bit-Zahl");

// ---------------------------------------------------------------------------
// Probe 4 -- abgeleitet, nicht fortgeschrieben (Abnahme 4)
// ---------------------------------------------------------------------------
//
// Die drei Eigenschaften aus der Abnahme, hier als Beziehungen zwischen Zahlen. Die
// Zahlen selbst schreibt `test/zufall_probe.cpp` aus; sie stehen nicht hier, weil kein
// Wert, den dieses Programm erzeugt hat, als Erwartungswert taugt.
//
// Die Vergleichsgroesse ist der **ganze Strom** -- alle vier Worte --, nicht nur seine
// erste Ausgabe. Zwei Stroeme mit gleicher erster Ausgabe und verschiedenem Rest waeren
// verschiedene Stroeme, und der schwaechere Vergleich haette es nicht gemerkt.

// Der Bezugsaufruf. Sechs Zahlen, die nichts miteinander zu tun haben, damit ein
// Vertauschen zweier Argumente auffiele.
constexpr u64 WURZEL = 0x0123456789abcdefULL;
constexpr i64 JAHRGANG = 1997;
constexpr u64 PARAMETERSUMME = 0xcbf29ce484222325ULL;
constexpr i64 RUNDE = 12;

/// Eigenschaft 1: Gleiche sechs Zahlen, gleicher Strom -- und zwar ohne dass irgendwo
/// ein Aufruf dazwischen etwas verschoben haette.
static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() ==
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte(),
              "Abnahme 4: gleiche sechs Zahlen -> gleicher Strom");

/// Eigenschaft 2: Ein um eins erhoehter `index` ist ein anderer Strom. Das gilt hier
/// nicht nur an diesem Beispiel -- die Herleitung im Kopf von `zufall.hpp` zeigt es
/// fuer jedes Paar --, aber ein Beispiel, das beim Uebersetzen mitlaeuft, faengt einen
/// Umbau ab, der die Herleitung ungueltig macht.
static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 8).worte(),
              "Abnahme 4: index + 1 -> anderer Strom");

/// Eigenschaft 3, der eigentliche Punkt des Pakets: Der Strom zu `index = 7` ist
/// derselbe, ob vorher zu `index = 1 … 6` gezogen wurde oder nicht -- und auch dann,
/// wenn dabei kraeftig gezogen wurde.
///
/// **Wogegen diese Probe steht.** Ein Modul mit einer gemerkten Ablage bestuende die
/// Eigenschaften 1 und 2 muehelos und faellt allein hier durch. Deshalb zieht die
/// Schleife nicht nur einen Wert je Strom, sondern unterschiedlich viele: Bei einer
/// fortgeschriebenen Ablage haenge das Ergebnis dann an der **Summe** der Ziehungen,
/// und die ist mit 21 Ziehungen keine, die man versehentlich trifft.
static_assert(
    [] {
        Strom vorher{splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::BUENDELZIEHUNG,
                                RUNDE, 7)};

        for (i64 lauf = 1; lauf <= 6; ++lauf) {
            Strom dazwischen{
                splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::BUENDELZIEHUNG, RUNDE, lauf)};
            for (i64 zug = 0; zug < lauf; ++zug) {
                (void)dazwischen.naechster();
            }
        }

        Strom nachher{splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::BUENDELZIEHUNG,
                                 RUNDE, 7)};
        return vorher.worte() == nachher.worte();
    }(),
    "Abnahme 4: der Strom zu index = 7 haengt nicht daran, ob und wie viel zu "
    "index = 1 … 6 gezogen wurde");

/// Und die Gegenprobe zur Reihenfolge: Der Strom zu `index = 7` ist derselbe, ob er
/// vor oder nach den anderen abgeleitet wird. „Zwei Aufrufe mit denselben sechs Zahlen
/// liefern denselben Strom, auch in umgekehrter Reihenfolge aufgerufen."
static_assert(
    [] {
        Strom zuerst{splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::SUCHBOT_KANDIDATEN,
                                RUNDE, 7)};
        Strom danach{splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::SUCHBOT_KANDIDATEN,
                                RUNDE, 1)};
        (void)danach.naechster();

        Strom wieder{splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::SUCHBOT_KANDIDATEN,
                                RUNDE, 7)};
        return zuerst.worte() == wieder.worte();
    }(),
    "Abnahme 4: die Ableitungsreihenfolge aendert den abgeleiteten Strom nicht");

// ---------------------------------------------------------------------------
// Probe 5 -- jede der sechs Zahlen kommt wirklich an (Abnahme 1)
// ---------------------------------------------------------------------------
//
// Sechs Argumente, sechs Aenderungen um genau eine Stelle, sechsmal ein anderer Strom.
// Ohne diese Probe koennte ein Argument stillschweigend unbenutzt sein -- die
// Ableitung saehe genauso zufaellig aus, und alle anderen Proben blieben gruen.

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL + 1, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7)
                      .worte(),
              "der Wurzelstartwert geht in die Ableitung ein");

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG + 1, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7)
                      .worte(),
              "der Jahrgang geht in die Ableitung ein");

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME + 1, Zweck::ZUFALLSBOT, RUNDE, 7)
                      .worte(),
              "die Pruefsumme des Parametersatzes geht in die Ableitung ein");

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::BUENDELZIEHUNG, RUNDE, 7)
                      .worte(),
              "der Zweck geht in die Ableitung ein");

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE + 1, 7)
                      .worte(),
              "die Runde geht in die Ableitung ein");

static_assert(splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte() !=
                  splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 6).worte(),
              "der Index geht in die Ableitung ein");

// **Und dieselben sechs Aenderungen paarweise gegeneinander -- die Probe, die einen
// echten Fehler gefunden hat.** Die sechs Zeilen oben halten jede Aenderung nur gegen
// den Bezugsaufruf. Das ist zu wenig: In der ersten Fassung dieses Moduls stand der
// Wurzelstartwert mit dem Jahrgang in derselben Summe, und damit ergaben
// „Wurzelstartwert + 1" und „Jahrgang + 1" **denselben** Strom. Beide waren vom
// Bezugsaufruf verschieden, also blieben alle sechs Zeilen oben gruen; aufgefallen ist
// es erst an den ausgeschriebenen Zahlen der laufenden Probe. Was zwei Argumente
// ununterscheidbar macht, faengt nur ein Vergleich der Aenderungen untereinander.
static_assert(
    [] {
        const std::array<std::array<u64, STROM_WORTE>, 7> stroeme = {
            splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte(),
            splitmix64(WURZEL + 1, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte(),
            splitmix64(WURZEL, JAHRGANG + 1, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 7).worte(),
            splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME + 1, Zweck::ZUFALLSBOT, RUNDE, 7).worte(),
            splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::BUENDELZIEHUNG, RUNDE, 7).worte(),
            splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE + 1, 7).worte(),
            splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, Zweck::ZUFALLSBOT, RUNDE, 8).worte()};

        for (std::size_t a = 0; a < stroeme.size(); ++a) {
            for (std::size_t b = a + 1; b < stroeme.size(); ++b) {
                if (stroeme[a] == stroeme[b]) {
                    return false;
                }
            }
        }
        return true;
    }(),
    "sechs Aenderungen um je eine Stelle ergeben sieben paarweise verschiedene Stroeme "
    "-- keine zwei Argumente laufen in dieselbe Rechnung");

// Und die vier Zwecke sind vier Stroeme, nicht zwei Namen fuer denselben. Sonst waere
// die Aufzaehlung eine Beschriftung ohne Wirkung.
static_assert(
    [] {
        const std::array<Zweck, 4> zwecke{Zweck::JAHRGANGSSTREUUNG, Zweck::ZUFALLSBOT,
                                          Zweck::BUENDELZIEHUNG, Zweck::SUCHBOT_KANDIDATEN};
        for (std::size_t a = 0; a < zwecke.size(); ++a) {
            for (std::size_t b = a + 1; b < zwecke.size(); ++b) {
                if (splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, zwecke[a], RUNDE, 7).worte() ==
                    splitmix64(WURZEL, JAHRGANG, PARAMETERSUMME, zwecke[b], RUNDE, 7).worte()) {
                    return false;
                }
            }
        }
        return true;
    }(),
    "die vier Zwecke ergeben vier paarweise verschiedene Stroeme");

// ---------------------------------------------------------------------------
// Probe 6 -- der Nullzustand entsteht nicht (siehe `strom_aus_keim`)
// ---------------------------------------------------------------------------
//
// xoshiro256** hat in vier Nullworten einen Fixpunkt: Er gibt von dort an nur Nullen
// aus. Die Herleitung im Kopf von `zufall.hpp` schliesst ihn aus -- die vier Worte
// eines Keims sind paarweise verschieden, und von vier paarweise verschiedenen Worten
// kann hoechstens eines null sein. Hier steht der Fall, der die Herleitung am ehesten
// widerlegen wuerde, wenn sie falsch waere: der Keim null.

static_assert(
    [] {
        const std::array<u64, STROM_WORTE> worte = strom_aus_keim(0ULL).worte();
        for (std::size_t a = 0; a < worte.size(); ++a) {
            for (std::size_t b = a + 1; b < worte.size(); ++b) {
                if (worte[a] == worte[b]) {
                    return false;
                }
            }
        }
        return true;
    }(),
    "die vier Worte eines Stroms sind paarweise verschieden, auch beim Keim null");

}  // namespace kern::zufall
