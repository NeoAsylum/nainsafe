//! # Der Mutationslauf -- Paket 0110
//!
//! Dreimal hat diese Fabrik einen Mutationslauf gebaut, einmal benutzt und weggeworfen:
//! die Pruefung zu Paket 0010 (50 Mutationen, 20 Ueberlebende), Paket 0088 (vier
//! Mutationen, unter denen keine vorhandene Probe rot wurde) und Paket 0097 (19
//! Mutationen, alle rot). Jedes Mal war das Werkzeug ein Wegwerfskript unter `bau/`,
//! und `bau/` steht in `.gitignore`. Das Ergebnis ueberlebte als Satz in einem Bericht,
//! nicht als Riegel.
//!
//! Ein Satz in einem Bericht laesst sich nicht wiederholen. Aendert ein spaeteres Paket
//! die Stelle, faellt eine dieser Mutationen stillschweigend auf gruen zurueck, und die
//! Probe bleibt bestanden -- genau die Lage, aus der Paket 0097 entstanden ist, eine
//! Ebene hoeher.
//!
//! ## Was dieses Programm tut
//!
//! Es liest einen Katalog von Faellen. Jeder Fall nennt eine Quelldatei, einen gesuchten
//! Text, seinen Ersatz und das Urteil, das dabei herauskommen muss. Das Programm setzt
//! jeden Fall einzeln, uebersetzt, laesst die zugehoerige Probe laufen und vergleicht
//! das Urteil mit der Erwartung. Null gibt es genau dann zurueck, wenn **jeder** Fall
//! sein erwartetes Urteil erreicht und der Baum vorher wie nachher gruen ist.
//!
//! ## Drei Eigenschaften, die keine Bequemlichkeit sind
//!
//! **Keine Quelldatei wird angefasst.** Der mutierte Text geht in eine Wegwerfdatei im
//! Baubaum; der Uebersetzer schreibt daraus die Objektdatei, die im Baubaum ohnehin
//! entsteht. `git status` fuehrt nach dem Lauf nichts ausser dem Baubaum, und der ist
//! ignoriert. Der Weg ueber eine Kopie im Quellbaum waere kuerzer und hinterliesse bei
//! jedem Abbruch eine unversionierte Datei neben der echten.
//!
//! **Der Vorlauf ist Pflicht.** Vor der ersten Mutation muss jede beteiligte Probe am
//! unveraenderten Baum gruen sein. Ohne diesen Riegel wuerde ein aus fremdem Grund
//! roter Baum jeden Fall als `rot` melden -- und der Lauf gaebe Null zurueck, waehrend
//! er nichts geprueft hat. Das ist die teuerste Art, ein Messgeraet falsch zu bauen:
//! Es zeigt genau dann Erfolg, wenn es blind ist.
//!
//! **Ein Muster, das nicht genau einmal vorkommt, ist ein Fehlschlag.** Nicht ein
//! uebersprungener Fall. Ein Fall, dessen Text sich im Quelltext nicht mehr findet,
//! misst nichts mehr, und ein Werkzeug, das darueber hinwegsieht, verliert seine Faelle
//! einen nach dem anderen, ohne je rot zu werden.
//!
//! ## Der Aufruf
//!
//! ```text
//! mutationstreiber <vorhaben-wurzel> <baubaum> <katalogdatei> [kennung ...]
//! ```
//!
//! Ohne Kennungen laufen alle Faelle. Mit Kennungen nur die genannten -- das ist der
//! Weg, mit dem ein Bauagent einen einzelnen Fall nachstellt, ohne die anderen achtzehn
//! zu bezahlen.

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Urteile
// ---------------------------------------------------------------------------

/// Was bei einem Fall herauskommen kann.
///
/// `Bau` ist ein eigenes Urteil und nicht ein Unterfall von `Rot`, und der Unterschied
/// ist gemessen: Die Pruefung zu Paket 0010 hat zwei Mutationen gefangen, bevor der
/// Uebersetzer fertig war -- die `static_assert`-Kette im Kopf des Moduls zaehlt
/// Adressen ab. Das ist ein starker Riegel, aber ein anderer als eine rote Probe. Wer
/// beides zusammenwirft, kann nicht mehr sagen, welcher der beiden gehalten hat, und
/// merkt nicht, wenn einer davon ausfaellt.
enum class Urteil { Gruen, Rot, Bau, Keines };

std::string_view urteilsname(Urteil urteil)
{
    switch (urteil) {
    case Urteil::Gruen:  return "gruen";
    case Urteil::Rot:    return "rot";
    case Urteil::Bau:    return "bau";
    case Urteil::Keines: break;
    }
    return "(keines)";
}

std::optional<Urteil> urteil_lesen(std::string_view wort)
{
    if (wort == "gruen") return Urteil::Gruen;
    if (wort == "rot")   return Urteil::Rot;
    if (wort == "bau")   return Urteil::Bau;
    return std::nullopt;
}

// ---------------------------------------------------------------------------
// Der Katalog und sein Leser
// ---------------------------------------------------------------------------

/// Die Fehlerarten des Lesers, mit Zaehlmarke am Ende.
///
/// Die Marke ist kein Schmuck: Der Selbsttest weiter unten prueft, dass **jede** Art
/// von mindestens einem Fall ausgeloest wird. Ohne sie waechst die Liste, und niemand
/// merkt, dass die neue Art nie gemessen wurde -- eine Fehlermeldung, die nie
/// erschienen ist, ist eine Vermutung ueber den eigenen Code.
enum class Fehlerart {
    FeldFehlt,
    FeldUnbekannt,
    FeldDoppelt,
    UrteilUnbekannt,
    KennungDoppelt,
    BlockOffen,
    BlockOhneFall,
    BlockDoppelt,
    KatalogLeer,
    Anzahl
};

std::string_view fehlerartname(Fehlerart art)
{
    switch (art) {
    case Fehlerart::FeldFehlt:       return "FeldFehlt";
    case Fehlerart::FeldUnbekannt:   return "FeldUnbekannt";
    case Fehlerart::FeldDoppelt:     return "FeldDoppelt";
    case Fehlerart::UrteilUnbekannt: return "UrteilUnbekannt";
    case Fehlerart::KennungDoppelt:  return "KennungDoppelt";
    case Fehlerart::BlockOffen:      return "BlockOffen";
    case Fehlerart::BlockOhneFall:   return "BlockOhneFall";
    case Fehlerart::BlockDoppelt:    return "BlockDoppelt";
    case Fehlerart::KatalogLeer:     return "KatalogLeer";
    case Fehlerart::Anzahl:          break;
    }
    return "(keine)";
}

struct Fehler {
    Fehlerart   art;
    std::size_t zeile;
    std::string text;
};

struct Fall {
    std::string kennung;
    std::string beschreibung;
    std::string quelle;   ///< Pfad der Quelldatei, relativ zur Vorhabenwurzel.
    std::string objekt;   ///< Pfad der Objektdatei, relativ zum Baubaum.
    std::string ziel;     ///< Name des CMake-Ziels, das neu gebunden wird.
    std::string probe;    ///< Name des ctest-Falls; ohne Angabe derselbe wie `ziel`.
    Urteil      erwartet = Urteil::Keines;
    std::string suche;
    std::string ersatz;
    bool        hat_suche  = false;
    bool        hat_ersatz = false;
    std::size_t zeile      = 0;
};

struct Katalog {
    std::vector<Fall>   faelle;
    std::vector<Fehler> fehler;
};

/// Die Marken des Katalogformats.
///
/// Der Zaun aus Tilden statt aus Gegenstrichen ist keine Geschmacksfrage: Der Katalog
/// zitiert Quelltext, und Quelltextbeispiele in Markdown stehen ueblicherweise zwischen
/// Gegenstrichen. Ein Zaun, der im Inhalt vorkommen kann, ist kein Zaun.
///
/// Der Fallkopf traegt aus demselben Grund ein eigenes Wort und nicht bloss zwei
/// Rautenzeichen: Der Katalog ist auch ein Dokument und hat Gliederung. Beim ersten
/// Lauf wurden zwei Prosaueberschriften als Faelle gelesen, mit den Kennungen `Das` und
/// `Woher` -- laut und harmlos, aber ein Format, in dem jede Gliederung ein Fall ist,
/// zwingt dazu, das Dokument um den Leser herum zu schreiben.
constexpr std::string_view FALLKOPF     = "## Fall ";
constexpr std::string_view BLOCK_SUCHE  = "~~~suche";
constexpr std::string_view BLOCK_ERSATZ = "~~~ersatz";
constexpr std::string_view BLOCKENDE    = "~~~";
constexpr std::string_view FELDRAND     = "    ";

std::string_view kappen(std::string_view text)
{
    std::size_t vorne = 0;
    while (vorne < text.size() && (text[vorne] == ' ' || text[vorne] == '\t')) ++vorne;
    std::size_t hinten = text.size();
    while (hinten > vorne
           && (text[hinten - 1] == ' ' || text[hinten - 1] == '\t'
               || text[hinten - 1] == '\r')) {
        --hinten;
    }
    return text.substr(vorne, hinten - vorne);
}

std::vector<std::string> zeilen_zerlegen(const std::string& text)
{
    std::vector<std::string> zeilen;
    std::string              laufend;
    for (const char zeichen : text) {
        if (zeichen == '\n') {
            if (!laufend.empty() && laufend.back() == '\r') laufend.pop_back();
            zeilen.push_back(laufend);
            laufend.clear();
        } else {
            laufend.push_back(zeichen);
        }
    }
    if (!laufend.empty()) {
        if (laufend.back() == '\r') laufend.pop_back();
        zeilen.push_back(laufend);
    }
    return zeilen;
}

/// Wie viele Male `nadel` in `heu` steckt -- ohne Ueberlappung.
std::size_t vorkommen(const std::string& heu, const std::string& nadel)
{
    if (nadel.empty()) return 0;
    std::size_t gezaehlt = 0;
    std::size_t stelle   = heu.find(nadel);
    while (stelle != std::string::npos) {
        ++gezaehlt;
        stelle = heu.find(nadel, stelle + nadel.size());
    }
    return gezaehlt;
}

/// Der Leser.
///
/// Er ist absichtlich streng: Eine eingerueckte Zeile innerhalb eines Falls, die kein
/// bekanntes Feld nennt, ist ein Fehler und keine Prosa. Der weiche Weg -- Unbekanntes
/// still uebergehen -- laesst einen Tippfehler im Feldnamen zu einem fehlenden Feld
/// werden, und die Meldung zeigt dann auf die falsche Ursache.
Katalog katalog_lesen(const std::string& text)
{
    Katalog     ergebnis;
    const auto  zeilen = zeilen_zerlegen(text);
    Fall        laufend;
    bool        offen       = false;  ///< steht gerade ein Fall in Arbeit?
    int         blockart    = 0;      ///< 0 keiner, 1 suche, 2 ersatz
    std::size_t blockbeginn = 0;
    std::string blockinhalt;
    bool        blockerste = true;

    auto pflichtfeld = [&ergebnis](const Fall& fall, const std::string& wert,
                                   std::string_view name) {
        if (wert.empty()) {
            ergebnis.fehler.push_back(
                {Fehlerart::FeldFehlt, fall.zeile,
                 "Fall " + fall.kennung + ": das Feld " + std::string(name) + " fehlt."});
        }
    };

    auto abschliessen = [&]() {
        if (!offen) return;
        pflichtfeld(laufend, laufend.quelle, "quelle");
        pflichtfeld(laufend, laufend.objekt, "objekt");
        pflichtfeld(laufend, laufend.ziel, "ziel");
        if (laufend.erwartet == Urteil::Keines) {
            ergebnis.fehler.push_back(
                {Fehlerart::FeldFehlt, laufend.zeile,
                 "Fall " + laufend.kennung + ": das Feld urteil fehlt."});
        }
        if (!laufend.hat_suche) {
            ergebnis.fehler.push_back({Fehlerart::FeldFehlt, laufend.zeile,
                                       "Fall " + laufend.kennung + ": kein Suchblock."});
        }
        if (!laufend.hat_ersatz) {
            ergebnis.fehler.push_back({Fehlerart::FeldFehlt, laufend.zeile,
                                       "Fall " + laufend.kennung + ": kein Ersatzblock."});
        }
        if (laufend.probe.empty()) laufend.probe = laufend.ziel;
        for (const Fall& frueher : ergebnis.faelle) {
            if (frueher.kennung == laufend.kennung) {
                ergebnis.fehler.push_back(
                    {Fehlerart::KennungDoppelt, laufend.zeile,
                     "Die Kennung " + laufend.kennung + " kommt zweimal vor."});
                break;
            }
        }
        ergebnis.faelle.push_back(laufend);
        offen = false;
    };

    for (std::size_t lfd = 0; lfd < zeilen.size(); ++lfd) {
        const std::string& zeile   = zeilen[lfd];
        const std::size_t  nummer  = lfd + 1;
        const auto         gekappt = kappen(zeile);

        if (blockart != 0) {
            if (gekappt == BLOCKENDE) {
                if (blockart == 1) {
                    laufend.suche     = blockinhalt;
                    laufend.hat_suche = true;
                } else {
                    laufend.ersatz     = blockinhalt;
                    laufend.hat_ersatz = true;
                }
                blockart = 0;
                blockinhalt.clear();
            } else {
                // Der Inhalt wird **roh** genommen, ohne Kappen: Die Einrueckung ist
                // bei einem Quelltextmuster bedeutungstragend, und ein Muster mit
                // weggeputzten Leerzeichen findet sich im Quelltext nicht wieder.
                if (!blockerste) blockinhalt.push_back('\n');
                blockinhalt += zeile;
                blockerste = false;
            }
            continue;
        }

        if (zeile.rfind(FALLKOPF, 0) == 0) {
            abschliessen();
            laufend       = Fall{};
            offen         = true;
            laufend.zeile = nummer;
            const std::string rest(
                kappen(std::string_view(zeile).substr(FALLKOPF.size())));
            const std::size_t luecke = rest.find(' ');
            laufend.kennung          = rest.substr(0, luecke);
            laufend.beschreibung     = (luecke == std::string::npos)
                                           ? std::string()
                                           : std::string(kappen(rest.substr(luecke)));
            continue;
        }

        if (gekappt == BLOCK_SUCHE || gekappt == BLOCK_ERSATZ) {
            if (!offen) {
                ergebnis.fehler.push_back({Fehlerart::BlockOhneFall, nummer,
                                           "Ein Textblock steht vor dem ersten Fallkopf."});
                continue;
            }
            const bool ist_suche = (gekappt == BLOCK_SUCHE);
            if ((ist_suche && laufend.hat_suche) || (!ist_suche && laufend.hat_ersatz)) {
                ergebnis.fehler.push_back({Fehlerart::BlockDoppelt, nummer,
                                           "Fall " + laufend.kennung + ": "
                                               + std::string(gekappt) + " steht zweimal."});
                continue;
            }
            blockart    = ist_suche ? 1 : 2;
            blockbeginn = nummer;
            blockinhalt.clear();
            blockerste = true;
            continue;
        }

        if (offen && zeile.rfind(FELDRAND, 0) == 0 && !gekappt.empty()) {
            const std::string feldzeile(gekappt);
            const std::size_t punkt = feldzeile.find(':');
            const std::string name =
                (punkt == std::string::npos)
                    ? feldzeile
                    : std::string(kappen(feldzeile.substr(0, punkt)));
            const std::string wert =
                (punkt == std::string::npos)
                    ? std::string()
                    : std::string(kappen(feldzeile.substr(punkt + 1)));

            std::string* ablage = nullptr;
            if (name == "quelle") {
                ablage = &laufend.quelle;
            } else if (name == "objekt") {
                ablage = &laufend.objekt;
            } else if (name == "ziel") {
                ablage = &laufend.ziel;
            } else if (name == "probe") {
                ablage = &laufend.probe;
            }

            if (ablage != nullptr) {
                if (!ablage->empty()) {
                    ergebnis.fehler.push_back({Fehlerart::FeldDoppelt, nummer,
                                               "Fall " + laufend.kennung + ": das Feld "
                                                   + name + " steht zweimal."});
                } else {
                    *ablage = wert;
                }
            } else if (name == "urteil") {
                if (laufend.erwartet != Urteil::Keines) {
                    ergebnis.fehler.push_back(
                        {Fehlerart::FeldDoppelt, nummer,
                         "Fall " + laufend.kennung + ": das Feld urteil steht zweimal."});
                } else if (const auto gelesen = urteil_lesen(wert)) {
                    laufend.erwartet = *gelesen;
                } else {
                    ergebnis.fehler.push_back(
                        {Fehlerart::UrteilUnbekannt, nummer,
                         "Fall " + laufend.kennung + ": urteil " + wert
                             + " gibt es nicht -- zugelassen sind gruen, rot und bau."});
                }
            } else {
                ergebnis.fehler.push_back({Fehlerart::FeldUnbekannt, nummer,
                                           "Fall " + laufend.kennung + ": das Feld " + name
                                               + " kennt niemand."});
            }
            continue;
        }
    }

    if (blockart != 0) {
        ergebnis.fehler.push_back({Fehlerart::BlockOffen, blockbeginn,
                                   "Ein Textblock ist nie geschlossen worden."});
    }
    abschliessen();

    if (ergebnis.faelle.empty()) {
        ergebnis.fehler.push_back(
            {Fehlerart::KatalogLeer, 0,
             "Der Katalog nennt keinen einzigen Fall. Ein leerer Lauf ist kein gruener."});
    }
    return ergebnis;
}

// ---------------------------------------------------------------------------
// Der Selbsttest des Kataloglesers
// ---------------------------------------------------------------------------
//
// Warum ueberhaupt einer: Der Katalog im Baum nennt heute neunzehn gueltige Faelle und
// keinen einzigen ungueltigen. Die Haelfte des Lesers -- alles, was einen Fehler meldet
// -- liefe damit nie. Ein Fall, den der Bestand nicht hergibt, gehoert in eine Tabelle
// im Programm; das ist dieselbe Bauart wie im Belegstellenriegel nebenan.

struct Selbsttestfall {
    std::string_view name;
    std::string_view text;
    std::size_t      erwartete_faelle;
    Fehlerart        erwarteter_fehler;  ///< `Anzahl` heisst: kein Fehler erwartet.
};

constexpr std::string_view GUT =
    "## Fall M01 -- ein Fall, wie er sein soll\n"
    "\n"
    "    quelle:  kern/src/a.cpp\n"
    "    objekt:  kern/CMakeFiles/k.dir/src/a.cpp.o\n"
    "    ziel:    a_probe\n"
    "    urteil:  rot\n"
    "\n"
    "~~~suche\n"
    "    \"eins\",\n"
    "~~~\n"
    "\n"
    "~~~ersatz\n"
    "    \"zwei\",\n"
    "~~~\n";

constexpr std::array<Selbsttestfall, 11> SELBSTTESTFAELLE = {{
    {"gueltig", GUT, 1, Fehlerart::Anzahl},

    {"zwei Faelle nacheinander",
     "## Fall M01 -- eins\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n"
     "\n"
     "## Fall M02 -- zwei\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  gruen\n"
     "\n"
     "~~~suche\n"
     "C\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "D\n"
     "~~~\n",
     2, Fehlerart::Anzahl},

    {"Feld ziel fehlt",
     "## Fall M01 -- ohne Ziel\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::FeldFehlt},

    {"Feldname vertippt",
     "## Fall M01 -- Tippfehler\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    zeil:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::FeldUnbekannt},

    {"Feld zweimal",
     "## Fall M01 -- doppelt\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    quelle:  b.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::FeldDoppelt},

    {"urteil unbekannt",
     "## Fall M01 -- falsches Urteil\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  vielleicht\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::UrteilUnbekannt},

    {"Kennung zweimal",
     "## Fall M01 -- eins\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n"
     "\n"
     "## Fall M01 -- nochmal\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "C\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "D\n"
     "~~~\n",
     2, Fehlerart::KennungDoppelt},

    {"Block nie geschlossen",
     "## Fall M01 -- offen\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n",
     1, Fehlerart::BlockOffen},

    {"Block vor dem ersten Fall",
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "## Fall M01 -- danach\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::BlockOhneFall},

    {"Suchblock zweimal",
     "## Fall M01 -- zweimal gesucht\n"
     "\n"
     "    quelle:  a.cpp\n"
     "    objekt:  o.o\n"
     "    ziel:    p\n"
     "    urteil:  rot\n"
     "\n"
     "~~~suche\n"
     "A\n"
     "~~~\n"
     "\n"
     "~~~suche\n"
     "C\n"
     "~~~\n"
     "\n"
     "~~~ersatz\n"
     "B\n"
     "~~~\n",
     1, Fehlerart::BlockDoppelt},

    {"leerer Katalog", "Nur Prosa und kein Fall.\n", 0, Fehlerart::KatalogLeer},
}};

/// Der Selbsttest, und was er ueber die Tabelle daneben hinaus prueft.
///
/// Drei Dinge, und das dritte ist das eigentliche:
///
///   1. jeder Fall der Tabelle liefert die erwartete Zahl von Katalogfaellen;
///   2. er loest genau den erwarteten Fehler aus -- und ein Fall ohne erwarteten
///      Fehler loest **keinen** aus. Ohne die zweite Haelfte wuerde ein Leser, der
///      grundsaetzlich meckert, jeden Fehlerfall bestehen;
///   3. **jede** Fehlerart kommt in der Tabelle vor. Das ist die Zusicherung, die die
///      Tabelle selbst nicht geben kann: Wer eine Art ergaenzt und den Fall vergisst,
///      hat eine Meldung gebaut, die nie erschienen ist.
///
/// Dazu die Zahl der geprueften Faelle im Klartext. Eine leere Tabelle liefe sonst
/// gruen durch -- der billigste Weg, einen Riegel abzuschalten, ist, ihm nichts zu
/// geben.
bool selbsttest(std::ostream& aus)
{
    bool                                                          heil = true;
    std::array<bool, static_cast<std::size_t>(Fehlerart::Anzahl)> gemessen{};
    std::size_t                                                   geprueft = 0;

    for (const Selbsttestfall& fall : SELBSTTESTFAELLE) {
        ++geprueft;
        const Katalog gelesen = katalog_lesen(std::string(fall.text));

        if (gelesen.faelle.size() != fall.erwartete_faelle) {
            aus << "  Selbsttest " << fall.name << ": " << gelesen.faelle.size()
                << " Faelle statt " << fall.erwartete_faelle << ".\n";
            heil = false;
        }

        if (fall.erwarteter_fehler == Fehlerart::Anzahl) {
            if (!gelesen.fehler.empty()) {
                aus << "  Selbsttest " << fall.name << ": unerwarteter Fehler "
                    << fehlerartname(gelesen.fehler.front().art) << " -- "
                    << gelesen.fehler.front().text << "\n";
                heil = false;
            }
            continue;
        }

        gemessen[static_cast<std::size_t>(fall.erwarteter_fehler)] = true;
        const bool getroffen = std::any_of(
            gelesen.fehler.begin(), gelesen.fehler.end(),
            [&fall](const Fehler& gemeldet) { return gemeldet.art == fall.erwarteter_fehler; });
        if (!getroffen) {
            aus << "  Selbsttest " << fall.name << ": "
                << fehlerartname(fall.erwarteter_fehler) << " wurde nicht gemeldet ("
                << gelesen.fehler.size() << " Fehler insgesamt).\n";
            heil = false;
        }
    }

    // Der Inhalt der Textbloecke, roh genommen. Der erste Fall der Tabelle traegt vier
    // fuehrende Leerzeichen im Suchmuster -- verloeren sie sich, faende sich kein
    // Muster dieses Katalogs im Quelltext wieder, und **jeder** Fall meldete
    // stattdessen die Musterzahl null. Das ist der Fehler, der am teuersten waere,
    // weil er nach einem Befund ueber den Kern aussaehe.
    const Katalog roh = katalog_lesen(std::string(GUT));
    if (roh.faelle.size() == 1) {
        if (roh.faelle[0].suche != "    \"eins\",") {
            aus << "  Selbsttest Rohtext: der Suchblock kam als [" << roh.faelle[0].suche
                << "] an.\n";
            heil = false;
        }
        if (roh.faelle[0].probe != "a_probe") {
            aus << "  Selbsttest Rohtext: probe steht auf [" << roh.faelle[0].probe
                << "] statt auf dem Ziel.\n";
            heil = false;
        }
        if (roh.faelle[0].beschreibung != "-- ein Fall, wie er sein soll") {
            aus << "  Selbsttest Rohtext: die Beschreibung kam als ["
                << roh.faelle[0].beschreibung << "] an.\n";
            heil = false;
        }
    }

    for (std::size_t art = 0; art < gemessen.size(); ++art) {
        if (!gemessen[art]) {
            aus << "  Selbsttest: die Fehlerart "
                << fehlerartname(static_cast<Fehlerart>(art))
                << " kommt in keinem Fall der Tabelle vor.\n";
            heil = false;
        }
    }

    if (geprueft == 0) {
        aus << "  Selbsttest: null Faelle geprueft.\n";
        heil = false;
    }

    aus << "mutationslauf, Selbsttest des Kataloglesers: " << geprueft << " Faelle, "
        << gemessen.size() << " Fehlerarten, alle vertreten -- "
        << (heil ? "wie erwartet." : "FEHLGESCHLAGEN.") << "\n";
    return heil;
}

// ---------------------------------------------------------------------------
// Dateien und Unterprozesse
// ---------------------------------------------------------------------------

std::optional<std::string> datei_lesen(const fs::path& pfad)
{
    std::ifstream strom(pfad, std::ios::binary);
    if (!strom) return std::nullopt;
    std::ostringstream sammler;
    sammler << strom.rdbuf();
    return sammler.str();
}

bool datei_schreiben(const fs::path& pfad, const std::string& inhalt)
{
    std::ofstream strom(pfad, std::ios::binary | std::ios::trunc);
    if (!strom) return false;
    strom.write(inhalt.data(), static_cast<std::streamsize>(inhalt.size()));
    return strom.good();
}

/// Ein Wort so einpacken, dass die Schale es unveraendert weitergibt.
std::string schutz(const std::string& wort)
{
    std::string gepackt = "'";
    for (const char zeichen : wort) {
        if (zeichen == '\'') {
            gepackt += "'\\''";
        } else {
            gepackt.push_back(zeichen);
        }
    }
    gepackt.push_back('\'');
    return gepackt;
}

/// Der Austrittscode aus dem Rohstatus, ohne die Makros aus der POSIX-Wartekoepfung.
///
/// Die Makros sind POSIX und nicht C++; der Sprachmodus dieses Vorhabens ist `c++20`
/// und nicht `gnu++20` (ADR 0011). Die Rechnung hier ist dieselbe und haengt an nichts.
int austrittscode(int rohstatus)
{
    if (rohstatus == -1) return -1;
    const int signalnummer = rohstatus & 0x7f;
    if (signalnummer != 0) return 128 + signalnummer;
    return (rohstatus >> 8) & 0xff;
}

int schalenlauf(const std::string& befehl, const fs::path& protokoll)
{
    const std::string ganz = befehl + " > " + schutz(protokoll.string()) + " 2>&1";
    return austrittscode(std::system(ganz.c_str()));
}

// ---------------------------------------------------------------------------
// Die Uebersetzerschalter, aus dem Baubaum gelesen statt geraten
// ---------------------------------------------------------------------------
//
// CMake legt je Ziel eine Datei mit den Schaltern an, mit denen es uebersetzt. Sie wird
// hier gelesen und nicht abgeschrieben, und das ist der Unterschied zwischen einem
// Werkzeug, das nach der naechsten Schalteraenderung noch misst, und einem, das dann
// still das Falsche uebersetzt. Der Wegwerftreiber von Paket 0097 trug die Schalter als
// Literal; nach einer Aenderung an der Werkzeugkette waere er lautlos falsch geworden.

struct Werkzeug {
    std::string uebersetzer;
    std::string defines;
    std::string includes;
    std::string flags;
};

constexpr std::string_view SCHALTERDATEI    = "flags.make";
constexpr std::string_view UEBERSETZERMARKE = "# compile CXX with ";
constexpr std::string_view MARKE_DEFINES    = "CXX_DEFINES = ";
constexpr std::string_view MARKE_INCLUDES   = "CXX_INCLUDES = ";
constexpr std::string_view MARKE_FLAGS      = "CXX_FLAGS = ";

std::optional<Werkzeug> werkzeug_lesen(const fs::path& schalterdatei, std::string& warum)
{
    const auto text = datei_lesen(schalterdatei);
    if (!text) {
        warum = "nicht lesbar: " + schalterdatei.string();
        return std::nullopt;
    }
    Werkzeug werkzeug;
    for (const std::string& zeile : zeilen_zerlegen(*text)) {
        const std::string_view sicht(zeile);
        if (zeile.rfind(UEBERSETZERMARKE, 0) == 0) {
            werkzeug.uebersetzer = std::string(kappen(sicht.substr(UEBERSETZERMARKE.size())));
        } else if (zeile.rfind(MARKE_DEFINES, 0) == 0) {
            werkzeug.defines = std::string(kappen(sicht.substr(MARKE_DEFINES.size())));
        } else if (zeile.rfind(MARKE_INCLUDES, 0) == 0) {
            werkzeug.includes = std::string(kappen(sicht.substr(MARKE_INCLUDES.size())));
        } else if (zeile.rfind(MARKE_FLAGS, 0) == 0) {
            werkzeug.flags = std::string(kappen(sicht.substr(MARKE_FLAGS.size())));
        }
    }
    if (werkzeug.uebersetzer.empty()) {
        warum = "kein Uebersetzer genannt in " + schalterdatei.string();
        return std::nullopt;
    }
    if (werkzeug.flags.empty()) {
        // Leer heisst hier nicht "keine Schalter", sondern "falsch gelesen". Ein
        // uebersetzendes Ziel dieses Vorhabens traegt immer den Warnsatz.
        warum = "keine Schalter genannt in " + schalterdatei.string();
        return std::nullopt;
    }
    return werkzeug;
}

/// Aus dem Objektpfad den Ort der Schalterdatei bilden.
///
/// CMake legt beides in dasselbe Verzeichnis, dessen Name auf `.dir` endet. Gesucht
/// wird das **letzte** Vorkommen: Der Endteil des Objektpfads ist der Pfad der
/// Quelldatei unterhalb des Zielverzeichnisses und kann den Namensteil noch einmal
/// tragen.
std::optional<fs::path> schalterdatei_zu(const fs::path& baubaum, const std::string& objekt)
{
    constexpr std::string_view MARKE  = ".dir/";
    const std::size_t          stelle = objekt.rfind(MARKE);
    if (stelle == std::string::npos) return std::nullopt;
    return baubaum / objekt.substr(0, stelle + MARKE.size() - 1) / SCHALTERDATEI;
}

// ---------------------------------------------------------------------------
// Der Lauf
// ---------------------------------------------------------------------------

struct Bericht {
    std::string kennung;
    Urteil      erreicht = Urteil::Keines;
    Urteil      erwartet = Urteil::Keines;
    bool        gelungen = false;
    std::string bemerkung;
};

/// Die Marken, an denen eine Probe dieser Fabrik ihren Abbruch meldet.
///
/// Sie stehen hier, damit die Zeile in der Zusammenfassung die **gemeinte** ist. Mein
/// Logbuch nennt den Fall dreimal: Ein Mutant scheitert gern aus einem anderen Grund
/// als dem gesuchten, und die Probe sieht trotzdem rot aus. Wer nur das Urteil liest,
/// merkt das nie.
constexpr std::array<std::string_view, 2> ABBRUCHMARKEN = {"FEHLGESCHLAGEN", "KEIN ABBRUCH"};

std::string erste_rote_zeile(const fs::path& protokoll)
{
    const auto text = datei_lesen(protokoll);
    if (!text) return {};
    std::string letzte;
    for (const std::string& zeile : zeilen_zerlegen(*text)) {
        for (const std::string_view marke : ABBRUCHMARKEN) {
            const std::size_t stelle = zeile.find(marke);
            // Ab der Marke und nicht ab dem Zeilenanfang: Die Probe schreibt ihren
            // Fortschritt nach `stdout` und ihre Abbruchmeldung nach `stderr`, und
            // beides landet in derselben Datei. Wo der Fortschritt ohne Zeilenumbruch
            // endet, klebt ein Reststueck davor -- gemessen an M20 und Z02 beim ersten
            // gruenen Lauf.
            if (stelle != std::string::npos) return zeile.substr(stelle);
        }
        if (!kappen(zeile).empty()) letzte = zeile;
    }
    return letzte;
}

struct Umgebung {
    fs::path wurzel;
    fs::path baubaum;
    fs::path werkstatt;  ///< Wegwerfdateien, im Baubaum
};

int bauen(const Umgebung& umgebung, const std::string& ziel, const fs::path& protokoll)
{
    return schalenlauf("cmake --build " + schutz(umgebung.baubaum.string()) + " --target "
                           + schutz(ziel),
                       protokoll);
}

/// Die Probe fahren -- ueber `ctest` und nicht ueber den Pfad des Binaerprogramms.
///
/// Der Grund: Das Programm liegt je nach Mitglied woanders, und seine Aufrufzeile steht
/// in der Testanmeldung. Wer den Pfad raet, raet auch die Argumente.
///
/// `--no-tests=error` ist der wichtigere Teil dieser Zeile und wurde beim Bau
/// **gemessen**, nicht vermutet. Ohne den Schalter gibt `ctest` mit einem Muster, auf
/// das kein Fall passt, Code 0 zurueck -- ein vertippter Probenname liefe damit als
/// gruen durch, und zwar zuerst im Vorlauf, der genau das ausschliessen soll. Ein
/// gruener Bericht ueber nichts ist die gefaehrlichste Rueckmeldung, die dieses
/// Vorhaben kennt; sie steht in `notizen/lehren.md` dreimal.
int pruefen(const Umgebung& umgebung, const std::string& probe, const fs::path& protokoll)
{
    return schalenlauf("ctest --test-dir " + schutz(umgebung.baubaum.string()) + " -R "
                           + schutz("^" + probe + "$")
                           + " --no-tests=error --output-on-failure",
                       protokoll);
}

/// Die Quelldatei anfassen und das Ziel neu bauen -- der Weg zurueck.
///
/// Angefasst wird nur der Zeitstempel; der Inhalt bleibt Byte fuer Byte derselbe, also
/// sieht `git status` nichts. Ohne das Anfassen haelt das Bauwerkzeug die von uns
/// geschriebene Objektdatei fuer aktuell und baut den Mutanten nie wieder weg.
///
/// Zurueckgesetzt wird nach **jedem** Fall und nicht erst am Ende. Das kostet je Fall
/// eine Uebersetzung und kauft dafuer die Eigenschaft, auf die es ankommt: Kein Fall
/// laeuft auf dem Mutanten eines anderen. Sobald ein Katalog zwei Quelldateien nennt,
/// ist das nicht mehr Sorgfalt, sondern Bedingung.
bool zuruecksetzen(const Umgebung& umgebung, const Fall& fall, const fs::path& protokoll,
                   std::string& warum)
{
    std::error_code fehlerkode;
    fs::last_write_time(umgebung.wurzel / fall.quelle, fs::file_time_type::clock::now(),
                        fehlerkode);
    if (fehlerkode) {
        warum = "Zeitstempel nicht setzbar: " + fehlerkode.message();
        return false;
    }
    const int code = bauen(umgebung, fall.ziel, protokoll);
    if (code != 0) {
        warum = "Rueckbau von " + fall.ziel + " endete mit Code " + std::to_string(code);
        return false;
    }
    return true;
}

Bericht fall_fahren(const Umgebung& umgebung, const Fall& fall, const std::string& urtext)
{
    Bericht bericht;
    bericht.kennung  = fall.kennung;
    bericht.erwartet = fall.erwartet;

    const std::size_t treffer = vorkommen(urtext, fall.suche);
    if (treffer != 1) {
        bericht.bemerkung = "das Suchmuster kommt " + std::to_string(treffer)
                            + "-mal vor, nicht genau einmal";
        return bericht;
    }

    const std::size_t stelle  = urtext.find(fall.suche);
    std::string       mutiert = urtext;
    mutiert.replace(stelle, fall.suche.size(), fall.ersatz);

    const fs::path wegwerf   = umgebung.werkstatt / (fall.kennung + ".cpp");
    const fs::path protokoll = umgebung.werkstatt / (fall.kennung + ".log");
    if (!datei_schreiben(wegwerf, mutiert)) {
        bericht.bemerkung = "die Wegwerfdatei liess sich nicht schreiben";
        return bericht;
    }

    const fs::path quelldatei    = umgebung.wurzel / fall.quelle;
    const auto     schalterdatei = schalterdatei_zu(umgebung.baubaum, fall.objekt);
    if (!schalterdatei) {
        bericht.bemerkung = "aus dem Objektpfad laesst sich kein Zielverzeichnis lesen";
        return bericht;
    }
    std::string warum;
    const auto  werkzeug = werkzeug_lesen(*schalterdatei, warum);
    if (!werkzeug) {
        bericht.bemerkung = warum;
        return bericht;
    }

    // `-iquote` zeigt auf das Verzeichnis der echten Quelldatei. Der Uebersetzer sucht
    // eine in Anfuehrung eingebundene Datei zuerst neben der einbindenden -- und die
    // einbindende liegt hier im Baubaum. Ohne den Schalter faende ein Modul seinen
    // eigenen Nachbarn nicht mehr, und der Fall meldete `bau` statt seines Urteils.
    const std::string uebersetzung = schutz(werkzeug->uebersetzer) + " -x c++ "
                                     + schutz(wegwerf.string()) + " -c -o "
                                     + schutz((umgebung.baubaum / fall.objekt).string())
                                     + " -iquote " + schutz(quelldatei.parent_path().string())
                                     + " " + werkzeug->defines + " " + werkzeug->includes
                                     + " " + werkzeug->flags;

    if (schalenlauf(uebersetzung, protokoll) != 0) {
        bericht.erreicht  = Urteil::Bau;
        bericht.bemerkung = "der Uebersetzer nimmt den Mutanten nicht an";
    } else if (bauen(umgebung, fall.ziel, protokoll) != 0) {
        bericht.erreicht  = Urteil::Bau;
        bericht.bemerkung = "das Ziel " + fall.ziel + " liess sich nicht binden";
    } else if (pruefen(umgebung, fall.probe, protokoll) == 0) {
        bericht.erreicht  = Urteil::Gruen;
        bericht.bemerkung = "die Probe bleibt bestanden";
    } else {
        bericht.erreicht  = Urteil::Rot;
        bericht.bemerkung = erste_rote_zeile(protokoll);
    }

    bericht.gelungen = (bericht.erreicht == fall.erwartet);
    return bericht;
}

/// Vorlauf und Nachlauf -- dieselbe Messung, zweimal gefahren.
bool baum_ist_gruen(const Umgebung& umgebung, const std::vector<Fall>& faelle,
                    std::string_view wann, std::ostream& aus)
{
    std::vector<std::string> gesehen;
    bool                     heil = true;
    for (const Fall& fall : faelle) {
        const std::string marke = fall.ziel + "\n" + fall.probe;
        if (std::find(gesehen.begin(), gesehen.end(), marke) != gesehen.end()) continue;
        gesehen.push_back(marke);

        const fs::path protokoll = umgebung.werkstatt / (std::string(wann) + ".log");
        const int      baucode   = bauen(umgebung, fall.ziel, protokoll);
        if (baucode != 0) {
            aus << "  " << wann << ": das Ziel " << fall.ziel << " baut nicht (Code "
                << baucode << ").\n      " << erste_rote_zeile(protokoll) << "\n";
            heil = false;
            continue;
        }
        const int probencode = pruefen(umgebung, fall.probe, protokoll);
        if (probencode != 0) {
            aus << "  " << wann << ": die Probe " << fall.probe << " ist rot (Code "
                << probencode << ").\n      " << erste_rote_zeile(protokoll) << "\n";
            heil = false;
        }
    }
    aus << "mutationslauf, " << wann << ": " << gesehen.size()
        << " Probe(n) am unveraenderten Baum -- " << (heil ? "gruen." : "NICHT GRUEN.")
        << "\n";
    return heil;
}

}  // namespace

int main(int argc, char** argv)
{
    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() < 4) {
        std::cerr << "Aufruf: mutationstreiber <wurzel> <baubaum> <katalog> [kennung ...]\n";
        return 2;
    }

    if (!selbsttest(std::cerr)) return 2;

    Umgebung umgebung;
    umgebung.wurzel    = fs::path(argumente[1]);
    umgebung.baubaum   = fs::path(argumente[2]);
    umgebung.werkstatt = umgebung.baubaum / "mutationslauf";
    const fs::path katalogdatei(argumente[3]);

    std::error_code fehlerkode;
    fs::create_directories(umgebung.werkstatt, fehlerkode);
    if (fehlerkode) {
        std::cerr << "Die Werkstatt " << umgebung.werkstatt
                  << " liess sich nicht anlegen: " << fehlerkode.message() << "\n";
        return 2;
    }

    const auto katalogtext = datei_lesen(katalogdatei);
    if (!katalogtext) {
        std::cerr << "Der Katalog " << katalogdatei << " ist nicht lesbar.\n";
        return 2;
    }

    const Katalog katalog = katalog_lesen(*katalogtext);
    if (!katalog.fehler.empty()) {
        std::cerr << "Der Katalog " << katalogdatei << " ist nicht in Ordnung:\n";
        for (const Fehler& fehler : katalog.fehler) {
            std::cerr << "  Zeile " << fehler.zeile << " -- " << fehlerartname(fehler.art)
                      << ": " << fehler.text << "\n";
        }
        return 2;
    }

    std::vector<Fall> gewaehlt;
    if (argumente.size() > 4) {
        for (std::size_t lfd = 4; lfd < argumente.size(); ++lfd) {
            const auto gefunden = std::find_if(
                katalog.faelle.begin(), katalog.faelle.end(),
                [&argumente, lfd](const Fall& fall) { return fall.kennung == argumente[lfd]; });
            if (gefunden == katalog.faelle.end()) {
                std::cerr << "Der Katalog kennt die Kennung " << argumente[lfd] << " nicht.\n";
                return 2;
            }
            gewaehlt.push_back(*gefunden);
        }
    } else {
        gewaehlt = katalog.faelle;
    }

    std::cout << "mutationslauf: " << katalog.faelle.size() << " Fall/Faelle im Katalog, "
              << gewaehlt.size() << " gewaehlt.\n";
    if (gewaehlt.empty()) {
        std::cerr << "Kein einziger Fall gewaehlt -- das ist kein gruener Lauf.\n";
        return 2;
    }

    if (!baum_ist_gruen(umgebung, gewaehlt, "Vorlauf", std::cout)) {
        std::cerr << "Der Vorlauf ist nicht gruen. Ohne ihn misst kein Fall etwas: Ein "
                     "aus fremdem Grund roter Baum meldet jede Mutation als gefangen.\n";
        return 1;
    }

    std::vector<Bericht> berichte;
    bool                 zurueckgesetzt = true;
    for (const Fall& fall : gewaehlt) {
        const auto urtext = datei_lesen(umgebung.wurzel / fall.quelle);
        if (!urtext) {
            Bericht bericht;
            bericht.kennung   = fall.kennung;
            bericht.erwartet  = fall.erwartet;
            bericht.bemerkung = "die Quelldatei " + fall.quelle + " ist nicht lesbar";
            berichte.push_back(bericht);
            continue;
        }

        berichte.push_back(fall_fahren(umgebung, fall, *urtext));

        std::string    warum;
        const fs::path protokoll = umgebung.werkstatt / (fall.kennung + "-zurueck.log");
        if (!zuruecksetzen(umgebung, fall, protokoll, warum)) {
            std::cerr << "Der Rueckweg nach " << fall.kennung << " ist gescheitert: " << warum
                      << "\n";
            zurueckgesetzt = false;
            break;
        }
    }

    std::cout << "\n";
    std::size_t gelungen = 0;
    for (const Bericht& bericht : berichte) {
        if (bericht.gelungen) ++gelungen;
        std::cout << (bericht.gelungen ? "  ok      " : "  FEHLER  ") << bericht.kennung
                  << "  erreicht " << urteilsname(bericht.erreicht) << ", erwartet "
                  << urteilsname(bericht.erwartet) << "\n";
        if (!bericht.bemerkung.empty()) {
            std::cout << "            " << bericht.bemerkung << "\n";
        }
    }

    const bool nachlauf =
        zurueckgesetzt && baum_ist_gruen(umgebung, gewaehlt, "Nachlauf", std::cout);

    std::cout << "mutationslauf: " << gelungen << " von " << berichte.size()
              << " Faellen wie erwartet.\n";

    const bool heil = zurueckgesetzt && nachlauf && gelungen == berichte.size()
                      && berichte.size() == gewaehlt.size();
    if (!heil) {
        std::cerr << "Der Mutationslauf ist rot. Ein Fall, der sein Urteil nicht erreicht, "
                     "ist entweder eine Luecke in der Probe oder ein Katalog, der der "
                     "Wirklichkeit nachhinkt -- beides wird berichtigt und nicht "
                     "ausgenommen.\n";
    }
    return heil ? 0 : 1;
}
