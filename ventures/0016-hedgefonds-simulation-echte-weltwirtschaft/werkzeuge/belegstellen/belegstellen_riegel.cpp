//! # Der Belegstellenriegel -- Paket 0059
//!
//! Sechs Pakete haben Belegstellen von Hand nachgezogen (0034, 0035, 0044, 0047,
//! 0050, 0057). Jedes war richtig; zusammen sind sie der Beleg, dass die
//! Handnachfuehrung den Fehler nur einholt und nicht abstellt. Paket 0050 hat vier
//! Belegstellen aufgezaehlt und fuer jede die richtige Zeile nachgeschlagen -- wenige
//! Stunden spaeter standen die Stellen anderswo. Die Korrektur war falsch, bevor sie
//! jemand ausfuehren konnte.
//!
//! ## Was dieses Programm prueft -- und was hier nicht mehr steht
//!
//! **Eine Bedingung, nicht zwei.** Der Rumpf von 0059 nennt zwei; beim zweiten
//! Abbruch am 2026-09-04 hat der Projektmanager sie getrennt. Hier steht die erste:
//!
//!   **Keine Zeilennummer in eine fremde Datei.** Wo im Text ein Dateiname steht,
//!   dem eine Zeilenangabe folgt, ist der Verweis nicht haltbar. Er zeigt heute
//!   vielleicht richtig; er zeigt morgen woandershin, ohne dass jemand etwas tut.
//!
//! Die zweite -- **jedes Abschnittszitat existiert wirklich** -- ist Paket 0067 und
//! kommt in dieselbe Datei zurueck. Sie ist die wichtigere und die aufwendigere: Sie
//! muss Ueberschriften aus fremden Dateien lesen, waehrend die Bedingung hier ein
//! Mustertreffer in derselben Zeile ist. Was 0067 hier wieder anlegt, ist eine Marke
//! fuer das Zitat; sie stand in der Fassung vom 2026-09-04 und ist heraus, weil eine
//! ungenutzte Konstante unter `-Werror` nicht uebersetzt.
//!
//! ## Wie "fremde Datei" gemessen wird
//!
//! Ein Treffer allein ist noch kein Befund. Erst wenn **auf derselben Zeile links vom
//! Treffer** ein Wort mit einer der Endungen unten steht und dessen Basisname nicht
//! die gerade gelesene Datei ist, zeigt die Zahl nach auswaerts. Das trennt zwei
//! Sorten sauber:
//!
//!   * Ein Dateiname mit einer Zeilenangabe dahinter -- ein Verweis nach auswaerts.
//!     Befund.
//!   * `stelle_basiswechsel(Gebiet::RW) == 197);` mit einer Zeilenangabe im
//!     Zeilenendkommentar -- kein Dateiname, also keine fremde Datei. Das ist die
//!     Nummer der Zeile in der Adresstabelle, und die `static_assert` daneben rechnet
//!     sie in derselben Zeile nach. Kein Befund, und zwar nicht aus Nachsicht,
//!     sondern weil dort nichts nach auswaerts zeigt.
//!
//! **Die Grenze dieser Messung, ausgeschrieben:** Eine nackte Zeilenangabe ohne
//! Dateinamen daneben faengt der Riegel nicht -- auch dann nicht, wenn drei Zeilen
//! darueber im Fliesstext eine Datei genannt wurde. Er sieht je Zeile, nicht je
//! Absatz. Wer ihn fuer "alle Verweise geprueft" haelt, irrt; er prueft die, die ihr
//! Ziel bei sich tragen. Die Zahl unten sagt deshalb beides: wie viele Muster
//! getroffen haben und wie viele davon einen Dateinamen trugen.
//!
//! ## Was der Riegel liest, und warum genau das
//!
//! Gelesen werden die **Bauquellen** des Vorhabens: Rumpf- und Kopfdateien, die
//! Bausteuerung und jede Bauliste. Ausgenommen sind die Verzeichnisse `bau` (vom
//! Uebersetzer erzeugt) und `befunde` (Berichte -- eine Zeilennummer darin ist ein
//! *Messwert vom Tag der Messung*, kein Verweis; sie soll gerade nicht nachgefuehrt
//! werden, sonst faelschte man einen Bericht).
//!
//! Der Schnitt bei `bau` kostet etwas, und das gehoert dazugesagt: Unter
//! `pruefstand/bau/pruefung-0019/` liegen Quelldateien, die keine Erzeugnisse sind.
//! Sie fallen mit heraus. Sie dort wegzuholen ist Aufraeumarbeit an fremdem Gebiet;
//! eine Ausnahme nach Pfadnamen waere die erste Zeile einer Ausnahmeliste. Beides tut
//! dieser Riegel nicht.
//!
//! Die Datendokumente unter `daten/` und die Parameterdatei sind **nicht** darunter,
//! und das ist eine benannte Grenze und keine Ausnahmeliste: Auf `reihen.toml` und
//! `einheitenbefund-pwt-baci.md` laeuft Paket 0057, auf die Parameterdatei liefen
//! 0035 und 0042. Ein Riegel, der sie heute mitnaehme, koennte erst gruen werden,
//! nachdem eine inhaltliche Aufraeumarbeit fertig ist -- genau das, was das
//! Arbeitspaket zu diesem Programm ausschliesst. Die Erweiterung ist eigene Arbeit
//! und liegt als Vorschlag daneben. Die Grenze steht hier ausgeschrieben, damit
//! niemand die Zahlen unten fuer "alles geprueft" haelt.
//!
//! Zu lesen sind sie fuer diese Bedingung ohnehin nie noetig: Sie vergleicht den
//! Verweis mit nichts, sie verwirft ihn wegen seiner **Bauart**. Ob die Nummer heute
//! trifft, ist gleichgueltig -- sie traefe nicht aus Bauart, sondern aus Glueck.
//!
//! ## Warum der Riegel seinen eigenen Quelltext mitliest
//!
//! Er tut es, und das ist Absicht: Nur so laesst sich der Rotnachweis fuehren, ohne
//! eine fremde Datei anzufassen. Eine eingefuegte Belegstelle in diesem Kommentar
//! macht ihn rot; dieselbe Zeile wieder heraus macht ihn gruen.
//!
//! ## Wenn er nichts gesehen hat
//!
//! Dann bricht er ab, statt gruen zu melden. Ein Riegel ohne Gegenstand ist kein
//! gruener Lauf -- dieselbe Lehre wie beim Warnsatz-Schlussriegel in
//! `werkzeugkette.cmake`, der bis zum 2026-09-04 "0 uebersetzende Ziele geprueft,
//! alle mit Warnsatz" melden konnte und dabei Code 0 gab.
//!
//! ## Aufruf
//!
//!     belegstellen_riegel <wurzel-des-vorhabens>
//!
//! Die Wurzel kommt von CMake und steht nicht im Programm. Ein fest eingebauter Pfad
//! liefe nur auf dem Rechner, auf dem er gebaut wurde. Paket 0067 haengt die Wurzel
//! der Vorgaben als zweites Argument an; die braucht erst das Abschnittszitat.
//!
//! Rueckgabe: 0 kein Befund, 1 Befunde gefunden, 2 Aufruf- oder Lesefehler.
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet),
//! ADR 0011 (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Die Marken
// ---------------------------------------------------------------------------

/// Die zugelassenen Endungen, als ein Streifen mit Trennpunkten statt als Liste.
/// Gesucht wird darin nach der Endung samt beiden Punkten, damit `md` nicht in
/// `cmd` trifft. Bewusst kurz: Was hier nicht steht, ist kein Verweisziel dieses
/// Vorhabens.
constexpr std::string_view ENDUNGEN = ".md.toml.cpp.hpp.txt.cmake.py.rs.";

/// Verzeichnisnamen, die nicht betreten werden. Begruendung im Kopf.
constexpr std::array<std::string_view, 2> GESPERRTE_ORDNER = {"bau", "befunde"};

/// Die Zeichen, aus denen ein Dateiname bestehen darf. Absichtlich ohne Akzent- und
/// Anfuehrungszeichen: Ein Verweis steht regelmaessig zwischen Akzenten, und die
/// sollen den Namen begrenzen statt Teil von ihm zu werden.
bool ist_pfadzeichen(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
           || c == '.' || c == '_' || c == '-' || c == '/';
}

bool ist_ziffer(char c) { return c >= '0' && c <= '9'; }

// ---------------------------------------------------------------------------
// Die zwei Muster
// ---------------------------------------------------------------------------
//
// Aus dem Arbeitspaket, dort in der Schreibweise der Textsuche -- hier absichtlich
// nicht abgeschrieben, sondern beschrieben, weil eine abgeschriebene Musterzeile in
// diesem Kommentar sich selbst faengt:
//
//   * das Wort fuer eine Zeile, ein `n` darf folgen, dann ein Leerzeichen, dann
//     mindestens zwei Ziffern;
//   * der Buchstabe `Z` mit Punkt, ein Leerzeichen darf folgen, dann mindestens zwei
//     Ziffern.
//
// Von Hand gebaut statt mit `<regex>`: zwei Muster dieser Groesse sind zwanzig Zeilen,
// und `<regex>` zoege eine Maschine herein, deren Verhalten niemand hier nachliest.
// Die Vorgabe aus dem Rollenauftrag -- feste Groessen, Indexpruefung an jeder Grenze --
// laesst sich so ausserdem einhalten.
//
// Die Obergrenze von vier Ziffern aus der Suchschreibweise ist keine: Ein Muster ohne
// Anker trifft in einer fuenfstelligen Zahl ebenso. Geprueft wird deshalb **mindestens
// zwei Ziffern**, und die Laenge laeuft bis zum Ende des Ziffernlaufs -- sonst stuende
// in der Meldung eine abgeschnittene Zahl.

constexpr std::size_t ZIFFERN_MINDESTENS = 2;

/// Wie viele Ziffern ab `i` stehen.
std::size_t ziffernlauf(std::string_view zeile, std::size_t i) {
    std::size_t d = 0;
    while (i + d < zeile.size() && ist_ziffer(zeile[i + d])) {
        ++d;
    }
    return d;
}

/// Laenge des Treffers, der bei `i` **beginnt** -- oder 0, wenn dort keiner beginnt.
std::size_t musterlaenge(std::string_view zeile, std::size_t i) {
    // Zusammengesetzt statt als Literal, damit diese Uebersetzungseinheit das Muster
    // nicht selbst als Text traegt.
    constexpr std::string_view WORT = "Zeil\145";

    if (zeile.size() - i >= WORT.size() && zeile.substr(i, WORT.size()) == WORT) {
        std::size_t j = i + WORT.size();
        if (j < zeile.size() && zeile[j] == 'n') {
            ++j;
        }
        if (j < zeile.size() && zeile[j] == ' ') {
            ++j;
            const std::size_t d = ziffernlauf(zeile, j);
            if (d >= ZIFFERN_MINDESTENS) {
                return (j + d) - i;
            }
        }
        return 0;
    }

    if (zeile[i] == 'Z' && i + 1 < zeile.size() && zeile[i + 1] == '.') {
        std::size_t j = i + 2;
        if (j < zeile.size() && zeile[j] == ' ') {
            ++j;
        }
        const std::size_t d = ziffernlauf(zeile, j);
        if (d >= ZIFFERN_MINDESTENS) {
            return (j + d) - i;
        }
    }

    return 0;
}

// ---------------------------------------------------------------------------
// Der Dateiname links vom Treffer
// ---------------------------------------------------------------------------

/// Der letzte Punkt trennt die Endung -- aber nur, wenn danach kein Schraegstrich
/// mehr kommt. `a.b/c` hat keine Endung, `daten/adressen.md` hat `.md`.
bool endung_zugelassen(std::string_view wort) {
    const std::size_t punkt = wort.rfind('.');
    if (punkt == std::string_view::npos) {
        return false;
    }
    const std::string_view endung = wort.substr(punkt);
    if (endung.find('/') != std::string_view::npos) {
        return false;
    }
    const std::string gesucht = std::string(endung) + ".";
    return ENDUNGEN.find(gesucht) != std::string_view::npos;
}

/// Das Wort unmittelbar links von `bis`, ohne schliessende Satzzeichen.
///
/// Leer, wenn dort keines steht oder es keine zugelassene Endung traegt. Der
/// Rueckwaertsgang laeuft ueber zwei Laeufe: erst ueber alles, was kein Pfadzeichen
/// ist (Leerzeichen, Akzent, Doppelpunkt), dann ueber das Wort selbst.
std::string dateiname_davor(std::string_view zeile, std::size_t bis) {
    std::size_t ende = bis;
    while (ende > 0 && !ist_pfadzeichen(zeile[ende - 1])) {
        --ende;
    }
    std::size_t anfang = ende;
    while (anfang > 0 && ist_pfadzeichen(zeile[anfang - 1])) {
        --anfang;
    }
    if (anfang == ende) {
        return {};
    }

    std::string_view wort = zeile.substr(anfang, ende - anfang);

    // Ein Satzpunkt am Ende gehoert nicht zum Namen: `siehe technik.md.` traegt die
    // Endung `.md`, nicht `.md.`. Dasselbe fuer den Schraegstrich eines Verzeichnisses.
    while (!wort.empty() && (wort.back() == '.' || wort.back() == '/')) {
        wort.remove_suffix(1);
    }
    if (!endung_zugelassen(wort)) {
        return {};
    }
    return std::string(wort);
}

std::string_view basisname(std::string_view pfad) {
    const std::size_t strich = pfad.rfind('/');
    if (strich == std::string_view::npos) {
        return pfad;
    }
    return pfad.substr(strich + 1);
}

// ---------------------------------------------------------------------------
// Die Dateiauswahl
// ---------------------------------------------------------------------------

bool ist_quelldatei(const fs::path& pfad) {
    if (pfad.filename().string() == "CMakeLists.txt") {
        return true;
    }
    const std::string endung = pfad.extension().string();
    return endung == ".cpp" || endung == ".hpp" || endung == ".cmake";
}

bool ist_gesperrt(std::string_view ordner) {
    for (std::size_t i = 0; i < GESPERRTE_ORDNER.size(); ++i) {
        if (ordner == GESPERRTE_ORDNER[i]) {
            return true;
        }
    }
    // Versteckte Ordner (`.git`, `.claude`) sind keine Bauquellen.
    return !ordner.empty() && ordner.front() == '.';
}

/// Absteigend, mit eigener Arbeitsliste statt `recursive_directory_iterator`: Dessen
/// `disable_recursion_pending` haengt am Zustand des Iterators, und ein gesperrter
/// Ordner soll gar nicht erst geoeffnet werden.
std::vector<fs::path> sammle_dateien(const fs::path& wurzel, std::error_code& fehler) {
    std::vector<fs::path> gefunden;
    std::vector<fs::path> offen;
    offen.push_back(wurzel);

    while (!offen.empty()) {
        const fs::path verzeichnis = offen.back();
        offen.pop_back();

        fs::directory_iterator it(verzeichnis, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path eintrag = it->path();
            std::error_code art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_gesperrt(eintrag.filename().string())) {
                    offen.push_back(eintrag);
                }
            } else if (fs::is_regular_file(eintrag, art) && ist_quelldatei(eintrag)) {
                gefunden.push_back(eintrag);
            }
            it.increment(fehler);
            if (fehler) {
                return gefunden;
            }
        }
    }
    return gefunden;
}

// ---------------------------------------------------------------------------
// Die Pruefung
// ---------------------------------------------------------------------------

struct Befund {
    std::string datei;
    std::size_t zeilennummer = 0;
    std::string ziel;
    std::string stelle;
};

struct Zaehlwerk {
    std::size_t treffer = 0;
    std::size_t mit_dateinamen = 0;
};

/// Der Ausschnitt um den Treffer, damit die Meldung zeigt, was gemeint ist.
std::string ausschnitt(std::string_view zeile, std::size_t anfang, std::size_t laenge) {
    constexpr std::size_t VORLAUF = 28;
    const std::size_t von = anfang > VORLAUF ? anfang - VORLAUF : 0;
    return std::string(zeile.substr(von, (anfang + laenge) - von));
}

void pruefe_datei(const fs::path& pfad, const std::string& anzeigename,
                  std::vector<Befund>& befunde, Zaehlwerk& zaehlwerk) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    const std::string eigener_name = pfad.filename().string();

    std::string zeile;
    std::size_t nummer = 0;
    while (std::getline(strom, zeile)) {
        ++nummer;
        if (!zeile.empty() && zeile.back() == '\r') {
            zeile.pop_back();
        }
        for (std::size_t i = 0; i < zeile.size();) {
            const std::size_t laenge = musterlaenge(zeile, i);
            if (laenge == 0) {
                ++i;
                continue;
            }
            ++zaehlwerk.treffer;

            const std::string ziel = dateiname_davor(zeile, i);
            if (!ziel.empty()) {
                ++zaehlwerk.mit_dateinamen;
                if (basisname(ziel) != eigener_name) {
                    befunde.push_back(
                        Befund{anzeigename, nummer, ziel, ausschnitt(zeile, i, laenge)});
                }
            }
            i += laenge;
        }
    }
}

}  // namespace

int main(int argc, char** argv) {
    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() != 2) {
        std::fprintf(stderr,
                     "Aufruf: belegstellen_riegel <wurzel-des-vorhabens>\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf "
                     "einem Rechner.\n");
        return 2;
    }

    std::error_code fehler;
    const fs::path wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "belegstellen_riegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }

    std::error_code lesefehler;
    const std::vector<fs::path> dateien = sammle_dateien(wurzel, lesefehler);
    if (lesefehler) {
        std::fprintf(stderr, "belegstellen_riegel: Lesefehler unter '%s': %s\n",
                     wurzel.string().c_str(), lesefehler.message().c_str());
        return 2;
    }

    // Ein Riegel, der nichts gesehen hat, hat nichts geprueft. Begruendung im Kopf.
    if (dateien.empty()) {
        std::fprintf(stderr,
                     "belegstellen_riegel: keine einzige Bauquelle unter '%s' gefunden. "
                     "Der Riegel hat damit nichts geprueft -- das ist kein gruener Lauf, "
                     "sondern ein Riegel ohne Gegenstand.\n",
                     wurzel.string().c_str());
        return 2;
    }

    const std::string wurzeltext = wurzel.string();
    std::vector<Befund> befunde;
    Zaehlwerk zaehlwerk;
    for (std::size_t i = 0; i < dateien.size(); ++i) {
        std::string anzeigename = dateien[i].string();
        if (anzeigename.size() > wurzeltext.size()
            && anzeigename.compare(0, wurzeltext.size(), wurzeltext) == 0) {
            anzeigename.erase(0, wurzeltext.size() + 1);
        }
        pruefe_datei(dateien[i], anzeigename, befunde, zaehlwerk);
    }

    std::fprintf(stdout,
                 "belegstellen_riegel: %zu Bauquellen gelesen, %zu Zeilenverweise "
                 "getroffen, davon %zu mit Dateinamen daneben.\n",
                 dateien.size(), zaehlwerk.treffer, zaehlwerk.mit_dateinamen);

    if (befunde.empty()) {
        std::fprintf(stdout,
                     "Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei.\n");
        return 0;
    }

    std::fprintf(stderr,
                 "\n%zu Verweis(e) zeigen mit einer Zeilennummer in eine fremde "
                 "Datei:\n\n",
                 befunde.size());
    for (std::size_t i = 0; i < befunde.size(); ++i) {
        const Befund& b = befunde[i];
        std::fprintf(stderr, "  %s:%zu  -> %s\n      %s\n", b.datei.c_str(),
                     b.zeilennummer, b.ziel.c_str(), b.stelle.c_str());
    }
    std::fprintf(stderr,
                 "\nEine Zeilennummer in eine fremde Datei wandert, ohne dass jemand "
                 "etwas tut.\nSie wird ersetzt -- durch einen Bezeichner, eine "
                 "Abschnittsueberschrift oder eine\nSchluesselzeile im Wortlaut --, "
                 "nicht ausgenommen und nicht nachgezogen.\n");
    return 1;
}
