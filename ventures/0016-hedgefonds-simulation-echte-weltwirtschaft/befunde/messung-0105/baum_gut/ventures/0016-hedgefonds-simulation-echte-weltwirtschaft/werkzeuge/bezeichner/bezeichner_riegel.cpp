//! # Der Bezeichnerriegel -- Paket 0129
//!
//! Der dritte Fall der Familie, deren erste beiden der Belegstellenriegel haelt: ein
//! Verweis, der beim Lesen richtig aussieht und ins Leere zeigt. Dort sind es eine
//! Zeilenangabe in eine fremde Datei und ein zitierter Ueberschriftentext; hier ist es
//! **der Bezeichner in Rueckwaerts-Anfuehrung**. Ein Kommentar nennt eine Funktion,
//! eine Klasse oder eine Konstante, die Sache wird umbenannt, und der Kommentar bleibt
//! stehen. Er ist dann teurer als gar keiner: Wer ihn liest, hat die Frage gestellt,
//! eine Antwort bekommen und hoert auf zu suchen.
//!
//! Belegt ist der Fall zweimal, beide Male von Hand nachgezogen -- Paket 0101 (der
//! Kommentar am Fehlerwert der Adresssuche berief sich auf eine Zustandsfunktion, die
//! es seit der Umbenennung durch Paket 0027 nicht mehr gab) und Paket 0123. Zwei
//! Handnachfuehrungen sind dasselbe Argument, mit dem der Belegstellenriegel selbst
//! begruendet wurde: Handnachfuehrung holt den Fehler ein, statt ihn abzustellen.
//!
//! ## Was dieses Programm liest
//!
//! Die Koepfe, die Quellen und die Proben des Kerns -- alles unter `kern/` mit der
//! Endung fuer einen Kopf oder eine Quelle, ohne den Baubaum und ohne versteckte
//! Ordner. **Nicht** den Pruefstand, **nicht** die Werkzeuge: Die Regel steht erst im
//! Kern, und wer die uebrigen Baeume gleich mitnimmt, verhandelt drei Sorten Ausnahme
//! mehr in einem Lauf.
//!
//! Jede Zeile wird in einen Codeteil und einen Kommentarteil zerlegt -- Zeichenketten
//! und Zeichenkonstanten werden dabei uebersprungen, damit ein Schraegstrichpaar in
//! einer Netzadresse keinen Kommentar erfindet. Aus dem Codeteil entsteht die
//! **Deklarationsmenge**, aus dem Kommentarteil die **Kandidaten**.
//!
//! ## Was als Kandidat zaehlt
//!
//! Ein Textstueck zwischen zwei Rueckwaerts-Anfuehrungszeichen, dessen **ganzer**
//! Inhalt ein Bezeichner ist -- ein einzelner oder ein qualifizierter, mit einem
//! wahlfreien leeren Klammerpaar am Ende. Ein Ausdruck, eine Zahl, ein Pfad oder eine
//! Wortgruppe ist keiner. Geprueft wird der **letzte** Namensteil eines
//! qualifizierten Namens; der Vorspann entscheidet spaeter ueber eine der Regeln.
//!
//! Diese enge Fassung ist Absicht. Ein Bezeichner mitten in einem eingeklammerten
//! Ausdruck waere ein zweiter Eingang mit eigenen Fehlerquellen, und der Gewinn ist
//! klein: Wer einen Namen nennt, setzt ihn allein in Anfuehrung.
//!
//! ## Die tragende Regel: eine negative Zusicherung ist keine Deklaration
//!
//! Der Kern haelt an einer Stelle Zusagen ueber **Sichtbarkeit** fest, und zwar beim
//! Uebersetzen statt zur Laufzeit: Eine Anforderung der Form `requires { &X::name; }`
//! wird gebaut, um mit `static_assert` nachzuweisen, dass sie **nicht** erfuellt ist.
//! Der Name steht dort also gerade deshalb, weil es ihn nicht gibt.
//!
//! Eine Pruefung ueber blosse Mengenzugehoerigkeit haelt so eine Zusicherung fuer eine
//! Deklaration -- und geht damit an genau dem Fall vorbei, der dieses Werkzeug
//! veranlasst hat. Der tote Name aus Paket 0101 kommt im Kern in einer einzigen
//! Codezeile vor, und das ist eine solche Zusicherung.
//!
//! **Die Regel lautet deshalb:** Ein Name, der im Kern ausschliesslich innerhalb einer
//! Anforderung dieser Form vorkommt, gilt als **nicht** deklariert. Kommt er sonstwo
//! im Code auch nur einmal vor, gilt er als deklariert. Gemessen wird das ohne
//! Sonderfall: Beim Aufbau der Deklarationsmenge wird der Mitgliedsname innerhalb
//! einer solchen Anforderung uebersprungen, alles andere nicht.
//!
//! Der Nachweis, dass die Regel etwas leistet, steht nicht hier, sondern in der
//! Abnahme des Pakets: derselbe Baum mit dem Wortlaut vor Paket 0101, einmal ohne und
//! einmal mit der Regel. Ohne sie bleibt der Riegel gruen, mit ihr wird er rot.
//!
//! ## Die Ausnahmen sind Regeln, keine Namensliste
//!
//! Ein Kommentar nennt in Rueckwaerts-Anfuehrung vieles, was zu Recht kein Bezeichner
//! des Kerns ist. Jeder solche Fall faellt unter eine **benannte Regel**; eine Liste
//! einzelner geduldeter Namen gaebe es nicht, denn sie waere genau die
//! Handnachfuehrung, gegen die dieses Werkzeug antritt. Geprueft wird in dieser
//! Reihenfolge, und die erste zutreffende Regel gewinnt:
//!
//!   1. `kennung` -- ein bis zwei Grossbuchstaben und ein bis drei Ziffern. Das sind
//!      die Kennungen der Vorgaben und der Mutationskataloge.
//!   2. `commitkennung` -- sieben bis vierzig Zeichen aus den Hexziffern, mit
//!      mindestens einer Ziffer und mindestens einem Buchstaben.
//!   3. `reserviert` -- ein der Umsetzung vorbehaltener Name: zwei fuehrende
//!      Unterstriche, oder einer vor einem Grossbuchstaben. Das ist keine Erfindung
//!      dieses Werkzeugs, sondern die Namensregel der Sprache.
//!   4. `schluesselwort` -- ein Schluesselwort von C++20.
//!   5. `vergiftet` -- ein Name, den der Kern selbst verbietet. Die Liste wird nicht
//!      abgeschrieben, sondern aus den Vergiftungszeilen des Kerns gelesen.
//!   6. `parameterschluessel` -- ein Schluessel oder Tabellenname aus der
//!      Kalibrierdatei des Vorhabens.
//!   7. `bauziel` -- ein Ziel oder ein Mitglied aus den Bauskripten des Vorhabens.
//!   8. `dateiname` -- der Name oder der Stamm einer Datei oder eines Ordners des
//!      Vorhabens.
//!   9. `namensvorsilbe` -- endet auf einem Unterstrich und ist echter Anfang eines
//!      deklarierten Namens. So wird eine Namensfamilie genannt, nicht ein Name.
//!  10. `namensteil` -- echter Anfang eines deklarierten Namens, und dieser volle Name
//!      steht im selben Kommentarblock ebenfalls in Rueckwaerts-Anfuehrung. Das ist
//!      die Form "das Ding heisst X und nicht Y".
//!  11. `abgelegter_name` -- unmittelbar links vor der Anfuehrung steht eine Wendung,
//!      die den Namen als abwesend kennzeichnet. **Unmittelbar** heisst: das letzte
//!      Wort davor, hoechstens zu zweit. Ein Satz weiter links zaehlt nicht, und das
//!      ist der ganze Zuschnitt dieser Regel -- der Kommentar aus Paket 0101 traegt in
//!      seinem eigenen Satz gleich zwei Verneinungen, und eine satzweite Fassung haette
//!      ihn durchgelassen. Gemessen: mit der engen Fassung wird er rot.
//!  12. `fremder_behaelter` -- ein qualifizierter Name, dessen erster Namensteil kein
//!      Namensraum und kein Verbund des Kerns ist. Ob es in einer fremden Bibliothek
//!      einen Namen gibt, entscheidet nicht dieses Vorhaben.
//!  13. `quellenangabe` -- der Kommentarblock nennt eine Netzadresse oder ein
//!      Quellenkuerzel in eckigen Klammern. Die dort genannten Namen gehoeren einem
//!      fremden Werk.
//!  14. `fremdwort` -- ohne Unterstrich, ohne Namensraum, und die Zeichenfolge kommt im
//!      **ganzen Codetext** des Kerns nicht ein einziges Mal vor, auch nicht als Teil
//!      eines laengeren Namens. Ein deutsches Wort ist von einem Namen nicht zu
//!      trennen; dass keine Spur davon im Code steht, ist das staerkste mechanische
//!      Anzeichen, dass es keiner ist.
//!
//! ## Der ausgeschriebene blinde Fleck
//!
//! Die letzte Regel ist die schwaechste, und sie ist es mit Ansage: Ein einteiliger,
//! ohne jede Spur aus dem Code verschwundener Name bleibt ungefangen. Genau diese
//! Sorte faengt Regel 12 der Deklarationsmenge -- der Name aus Paket 0101 ist nur
//! deshalb sichtbar, weil die negative Zusicherung ihn im Code stehen laesst. Wer
//! diesem Riegel "alle toten Namen geprueft" unterstellt, irrt; er prueft die, die
//! eine Spur hinterlassen haben.
//!
//! Die Regeln 10 und 11 haben denselben Charakter und die kleinere Reichweite. Alle
//! drei drucken jede ihrer Fundstellen mit Namen und Ort aus, damit der Nachlass
//! sichtbar bleibt statt gezaehlt zu werden.
//!
//! ## Der Selbsttest, der bei jedem Aufruf mitlaeuft
//!
//! Vier Falltabellen im Programm, zusammen mit ihren Gegenproben. Sie laufen vor dem
//! ersten Lesen des Bestands; ein verfehlter Fall bricht mit Code 2 ab, ehe eine Zahl
//! entsteht. Der Grund ist derselbe wie beim Belegstellenriegel: Stimmt die Zerlegung
//! nicht, ist jede Zahl weiter unten wertlos -- auch und gerade eine gruene.
//!
//! Die Tabellen tragen Faelle, die der Baum nicht hergibt, und zu jedem faengt einer
//! den Gegenfall: was die Regel treffen **und** was sie durchlassen muss. Der wichtigste
//! ist der erste der Regeltabelle -- der Wortlaut aus Paket 0101, der ein Befund sein
//! muss, direkt neben dem Wortlaut am rohen Schreibzugriff, der keiner sein darf.
//! Beide nennen denselben Namen.
//!
//! ## Aufruf und Rueckgabe
//!
//! Ein Argument: die Wurzel des Vorhabens. Sie kommt von CMake und nicht aus dem
//! Programm -- ein eingebauter Pfad liefe nur auf einem Rechner.
//!
//! Rueckgabe: 0 kein Befund, 1 Befunde gefunden, 2 der Riegel selbst taugt nicht --
//! Aufruf- oder Lesefehler, ein verfehlter Fall des Selbsttests, keine gelesene Datei,
//! kein einziger Kandidat oder keine einzige negative Zusicherung im Kern. Die letzte
//! Bedingung ist die Vorsorge gegen den stillen Ausfall: Verschwindet die tragende
//! Regel aus dem Bestand, ist der Lauf nicht gruen, sondern gegenstandslos.
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet),
//! ADR 0011 (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Kleine Pruefzeichen
// ---------------------------------------------------------------------------

bool ist_ziffer(char c) { return c >= '0' && c <= '9'; }

bool ist_klein(char c) { return c >= 'a' && c <= 'z'; }

bool ist_gross(char c) { return c >= 'A' && c <= 'Z'; }

bool ist_buchstabe(char c) { return ist_klein(c) || ist_gross(c); }

bool ist_namenszeichen(char c) { return ist_buchstabe(c) || ist_ziffer(c) || c == '_'; }

bool ist_namensanfang(char c) { return ist_buchstabe(c) || c == '_'; }

bool ist_leerraum(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

char klein(char c) { return ist_gross(c) ? static_cast<char>(c - 'A' + 'a') : c; }

/// Vergleich ohne Ruecksicht auf Gross- und Kleinschreibung -- nur fuer die
/// Wendungen der Regel `abgelegter_name` gebraucht, wo dasselbe Wort am Satzanfang
/// gross und mitten im Satz klein steht.
bool gleich_ohne_fall(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (klein(a[i]) != klein(b[i])) {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Die Zerlegung einer Zeile in Code und Kommentar
// ---------------------------------------------------------------------------

/// Was von einer Zeile uebrig bleibt, getrennt nach den beiden Verwendungen.
struct Zerlegung {
    std::string code;
    std::string kommentar;
    bool im_block = false;
};

/// Zerlegt eine Zeile. `im_block` sagt, ob die Zeile in einem offenen Blockkommentar
/// beginnt, und die Rueckgabe sagt, ob sie in einem endet.
///
/// Zeichenketten und Zeichenkonstanten wandern **ungelesen** in den Codeteil. Ohne das
/// erfaende eine Netzadresse in einer Zeichenkette einen Kommentar, und der Kern haelt
/// mehrere. Das einfache Anfuehrungszeichen ist in C++ zweideutig: Es begrenzt eine
/// Zeichenkonstante und trennt zugleich Ziffergruppen in einer Zahl. Steht links davon
/// ein Namenszeichen, ist es ein Trenner -- eine Zeichenkonstante faengt nie
/// unmittelbar hinter einem Namen oder einer Ziffer an.
Zerlegung zerlege(std::string_view zeile, bool im_block) {
    Zerlegung aus;
    aus.im_block = im_block;
    std::size_t i = 0;
    while (i < zeile.size()) {
        if (aus.im_block) {
            const std::size_t schluss = zeile.find("*/", i);
            if (schluss == std::string_view::npos) {
                aus.kommentar.append(zeile.substr(i));
                i = zeile.size();
            } else {
                aus.kommentar.append(zeile.substr(i, schluss - i));
                i = schluss + 2;
                aus.im_block = false;
            }
            continue;
        }
        const char c = zeile[i];
        const bool trenner_links = !aus.code.empty() && ist_namenszeichen(aus.code.back());
        if (c == '"' || (c == '\'' && !trenner_links)) {
            const char schlusszeichen = c;
            aus.code.push_back(c);
            ++i;
            while (i < zeile.size()) {
                if (zeile[i] == '\\' && i + 1 < zeile.size()) {
                    aus.code.push_back(zeile[i]);
                    aus.code.push_back(zeile[i + 1]);
                    i += 2;
                    continue;
                }
                const char d = zeile[i];
                aus.code.push_back(d);
                ++i;
                if (d == schlusszeichen) {
                    break;
                }
            }
            continue;
        }
        if (c == '/' && i + 1 < zeile.size() && zeile[i + 1] == '/') {
            aus.kommentar.append(zeile.substr(i + 2));
            i = zeile.size();
            continue;
        }
        if (c == '/' && i + 1 < zeile.size() && zeile[i + 1] == '*') {
            i += 2;
            aus.im_block = true;
            continue;
        }
        aus.code.push_back(c);
        ++i;
    }
    return aus;
}

struct Zerlegefall {
    std::string_view zeile;
    bool im_block_vorher;
    std::string_view code;
    std::string_view kommentar;
    bool im_block_nachher;
};

/// Neun Faelle, und die Haelfte davon ist die Gegenprobe: was **nicht** als Kommentar
/// zaehlen darf. Die Netzadresse und der Schraegstrich in der Zeichenkonstante sind
/// keine erfundenen Faelle -- beide stehen im Kern.
constexpr std::array<Zerlegefall, 9> ZERLEGEFAELLE = {{
    {"int x = 1;  // ein `name`", false, "int x = 1;  ", " ein `name`", false},
    {"/// ein `name`", false, "", "/ ein `name`", false},
    {"//! ein `name`", false, "", "! ein `name`", false},
    {"const char* s = \"http://x/y\";", false, "const char* s = \"http://x/y\";", "",
     false},
    {"if (c == '/') { return 1; }", false, "if (c == '/') { return 1; }", "", false},
    {"a = 1'000'000;  // gross", false, "a = 1'000'000;  ", " gross", false},
    {"/* `name` */ int y;", false, " int y;", " `name` ", false},
    {"noch im Block `name`", true, "", "noch im Block `name`", true},
    {"Rest */ int z;", true, " int z;", "Rest ", false},
}};

std::size_t selbsttest_zerlegung() {
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < ZERLEGEFAELLE.size(); ++i) {
        const Zerlegefall& fall = ZERLEGEFAELLE[i];
        const Zerlegung z = zerlege(fall.zeile, fall.im_block_vorher);
        if (z.code != fall.code || z.kommentar != fall.kommentar
            || z.im_block != fall.im_block_nachher) {
            std::fprintf(stderr,
                         "Selbsttest Zerlegung, Fall %zu verfehlt.\n  Eingabe:   %s\n"
                         "  Code:      '%s' erwartet '%s'\n"
                         "  Kommentar: '%s' erwartet '%s'\n  im Block:  %d erwartet %d\n",
                         i + 1, std::string(fall.zeile).c_str(), z.code.c_str(),
                         std::string(fall.code).c_str(), z.kommentar.c_str(),
                         std::string(fall.kommentar).c_str(), z.im_block ? 1 : 0,
                         fall.im_block_nachher ? 1 : 0);
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Die negative Sichtbarkeitszusicherung
// ---------------------------------------------------------------------------

/// Wo in einer Codezeile ein Mitgliedsname einer negativen Zusicherung steht.
struct Zusicherung {
    std::size_t anfang = 0;
    std::size_t ende = 0;
};

std::size_t hinter_leerraum(std::string_view text, std::size_t i) {
    while (i < text.size() && ist_leerraum(text[i])) {
        ++i;
    }
    return i;
}

std::size_t hinter_namen(std::string_view text, std::size_t i) {
    if (i >= text.size() || !ist_namensanfang(text[i])) {
        return i;
    }
    while (i < text.size() && ist_namenszeichen(text[i])) {
        ++i;
    }
    return i;
}

/// Sucht in einer Codezeile alle Anforderungen der Form `requires { &X::name; }` und
/// gibt die Lage des **letzten** Namensteils zurueck -- also des Mitglieds, dessen
/// Abwesenheit zugesichert wird. Der Vorspann (`X` und alles davor) bleibt unberuehrt:
/// Er ist eine gewoehnliche Nennung und soll als Deklaration zaehlen.
///
/// Verlangt wird mindestens ein Namensraumdoppelpunkt. Ohne ihn gaebe es keinen
/// Mitgliedsnamen, und die Form waere eine andere.
std::vector<Zusicherung> zusicherungen(std::string_view code) {
    std::vector<Zusicherung> gefunden;
    const std::string_view wort = "requires";
    std::size_t i = 0;
    while (i < code.size()) {
        const std::size_t treffer = code.find(wort, i);
        if (treffer == std::string_view::npos) {
            break;
        }
        i = treffer + wort.size();
        const bool wortanfang =
            treffer == 0 || !ist_namenszeichen(code[treffer - 1]);
        if (!wortanfang || (i < code.size() && ist_namenszeichen(code[i]))) {
            continue;
        }
        std::size_t j = hinter_leerraum(code, i);
        if (j >= code.size() || code[j] != '{') {
            continue;
        }
        j = hinter_leerraum(code, j + 1);
        if (j >= code.size() || code[j] != '&') {
            continue;
        }
        j = hinter_leerraum(code, j + 1);
        const std::size_t erster = j;
        j = hinter_namen(code, j);
        if (j == erster) {
            continue;
        }
        std::size_t teile = 0;
        std::size_t letzter_anfang = erster;
        std::size_t letztes_ende = j;
        for (;;) {
            const std::size_t k = hinter_leerraum(code, j);
            if (k + 1 >= code.size() || code[k] != ':' || code[k + 1] != ':') {
                break;
            }
            const std::size_t m = hinter_leerraum(code, k + 2);
            const std::size_t n = hinter_namen(code, m);
            if (n == m) {
                break;
            }
            letzter_anfang = m;
            letztes_ende = n;
            j = n;
            ++teile;
        }
        if (teile == 0) {
            continue;
        }
        j = hinter_leerraum(code, j);
        if (j >= code.size() || code[j] != ';') {
            continue;
        }
        j = hinter_leerraum(code, j + 1);
        if (j >= code.size() || code[j] != '}') {
            continue;
        }
        gefunden.push_back(Zusicherung{letzter_anfang, letztes_ende});
        i = j + 1;
    }
    return gefunden;
}

struct Zusicherungsfall {
    std::string_view code;
    std::string_view name;  // leer: keine Zusicherung in dieser Zeile
};

/// Sechs Faelle, davon drei Gegenproben. Der vierte ist die Form, die im Kern
/// tatsaechlich steht und die keine Zusicherung dieser Art ist: eine Anforderung mit
/// Parameterliste ueber einen Ausdruck. Wer sie mitfaenge, striche einen Namen aus der
/// Deklarationsmenge, den es sehr wohl gibt.
constexpr std::array<Zusicherungsfall, 6> ZUSICHERUNGSFAELLE = {{
    {"constexpr bool hat = requires { &Z::schreibe; };", "schreibe"},
    {"constexpr bool hat = requires{&Z::lege_ab;};", "lege_ab"},
    {"constexpr bool hat = requires { &kern::zustand::Zustand::lies; };", "lies"},
    {"constexpr bool nimmt = requires(ZweckTyp zweck) { ableitung(zweck); };", ""},
    {"constexpr bool hat = requires { &Z::schreibe };", ""},
    {"constexpr bool hat = requires { &schreibe; };", ""},
}};

std::size_t selbsttest_zusicherung() {
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < ZUSICHERUNGSFAELLE.size(); ++i) {
        const Zusicherungsfall& fall = ZUSICHERUNGSFAELLE[i];
        const std::vector<Zusicherung> gefunden = zusicherungen(fall.code);
        std::string name;
        if (gefunden.size() == 1) {
            name = std::string(
                fall.code.substr(gefunden[0].anfang, gefunden[0].ende - gefunden[0].anfang));
        } else if (gefunden.size() > 1) {
            name = "<mehrfach>";
        }
        if (name != fall.name) {
            std::fprintf(stderr,
                         "Selbsttest Zusicherung, Fall %zu verfehlt.\n  Eingabe: %s\n"
                         "  gelesen: '%s' erwartet '%s'\n",
                         i + 1, std::string(fall.code).c_str(), name.c_str(),
                         std::string(fall.name).c_str());
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Die Form eines Kandidaten
// ---------------------------------------------------------------------------

/// Ein in Rueckwaerts-Anfuehrung genannter Bezeichner samt allem, was die Regeln von
/// ihm brauchen.
struct Kandidat {
    std::string voll;      ///< wie der Kommentar ihn nennt, samt Vorspann
    std::string letzt;     ///< der letzte Namensteil -- der geprueft wird
    std::string vorspann;  ///< der erste Namensteil, leer bei einem einfachen Namen
    std::string block;     ///< der ganze Kommentarblock, fuer die Regeln 10 und 13
    std::string links;     ///< der Text links davon, fuer Regel 11
    std::string datei;
    std::size_t zeilennummer = 0;
};

/// Ist der ganze Inhalt einer Anfuehrung ein Bezeichner? Dann werden `voll`, `letzt`
/// und `vorspann` gefuellt. Ein leeres Klammerpaar am Ende ist zugelassen -- eine
/// Funktion wird oft so genannt -- und gehoert nicht zum Namen.
bool ist_bezeichner(std::string_view roh, std::string& voll, std::string& letzt,
                    std::string& vorspann) {
    std::size_t ende = roh.size();
    while (ende > 0 && ist_leerraum(roh[ende - 1])) {
        --ende;
    }
    std::size_t anfang = 0;
    while (anfang < ende && ist_leerraum(roh[anfang])) {
        ++anfang;
    }
    std::string_view text = roh.substr(anfang, ende - anfang);
    if (text.size() >= 2 && text.substr(text.size() - 2) == "()") {
        text = text.substr(0, text.size() - 2);
    }
    if (text.empty() || !ist_namensanfang(text[0])) {
        return false;
    }
    std::vector<std::string> teile;
    std::size_t i = 0;
    for (;;) {
        const std::size_t j = hinter_namen(text, i);
        if (j == i) {
            return false;
        }
        teile.push_back(std::string(text.substr(i, j - i)));
        if (j == text.size()) {
            break;
        }
        if (j + 1 >= text.size() || text[j] != ':' || text[j + 1] != ':') {
            return false;
        }
        i = j + 2;
    }
    voll = std::string(text);
    letzt = teile.back();
    vorspann = teile.size() > 1 ? teile.front() : std::string();
    return true;
}

struct Formfall {
    std::string_view roh;
    bool bezeichner;
    std::string_view letzt;
    std::string_view vorspann;
};

/// Zehn Faelle, sechs davon Gegenproben. Alle zehn stammen der Form nach aus dem Kern:
/// Ausdruecke, Zahlenbereiche, Tabellennamen und Pfade stehen dort ebenso in
/// Anfuehrung wie Namen.
constexpr std::array<Formfall, 10> FORMFAELLE = {{
    {"lies", true, "lies", ""},
    {"kern::werte", true, "werte", "kern"},
    {"lege_ab()", true, "lege_ab", ""},
    {"std::string_view", true, "string_view", "std"},
    {"MAL_", true, "MAL_", ""},
    {"index >= FELDER", false, "", ""},
    {"0 ... 309", false, "", ""},
    {"kern/sperre.hpp", false, "", ""},
    {"[instrument.leitzins]", false, "", ""},
    {"kern::", false, "", ""},
}};

std::size_t selbsttest_form() {
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < FORMFAELLE.size(); ++i) {
        const Formfall& fall = FORMFAELLE[i];
        std::string voll;
        std::string letzt;
        std::string vorspann;
        const bool ja = ist_bezeichner(fall.roh, voll, letzt, vorspann);
        if (ja != fall.bezeichner || (ja && (letzt != fall.letzt || vorspann != fall.vorspann))) {
            std::fprintf(stderr,
                         "Selbsttest Form, Fall %zu verfehlt.\n  Eingabe: '%s'\n"
                         "  Bezeichner %d erwartet %d; letzt '%s' erwartet '%s'; "
                         "Vorspann '%s' erwartet '%s'\n",
                         i + 1, std::string(fall.roh).c_str(), ja ? 1 : 0,
                         fall.bezeichner ? 1 : 0, letzt.c_str(),
                         std::string(fall.letzt).c_str(), vorspann.c_str(),
                         std::string(fall.vorspann).c_str());
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Die Bestaende, gegen die geprueft wird
// ---------------------------------------------------------------------------

using Namensmenge = std::set<std::string>;

struct Bestand {
    Namensmenge deklariert;   ///< aus dem Codeteil des Kerns, ohne die Zusicherungen
    Namensmenge parameter;    ///< Schluessel der Kalibrierdatei
    Namensmenge bauziele;     ///< Ziele und Mitglieder aus den Bauskripten
    Namensmenge dateinamen;   ///< Namen und Staemme der Dateien und Ordner
    Namensmenge vergiftet;    ///< aus den Vergiftungszeilen des Kerns
    Namensmenge behaelter;    ///< Namensraeume und Verbunde des Kerns
    std::string codetext;     ///< der ganze Codeteil, fuer die letzte Regel
};

/// Die Schluesselwoerter von C++20, wie die Sprache sie fuehrt. Eine geschlossene,
/// fremdbestimmte Liste -- keine Sammlung geduldeter Namen dieses Vorhabens.
constexpr std::array<std::string_view, 96> SCHLUESSELWOERTER = {
    {"alignas",  "alignof",      "and",        "and_eq",       "asm",
     "auto",     "bitand",       "bitor",      "bool",         "break",
     "case",     "catch",        "char",       "char8_t",      "char16_t",
     "char32_t", "class",        "compl",      "concept",      "const",
     "consteval", "constexpr",   "constinit",  "const_cast",   "continue",
     "co_await", "co_return",    "co_yield",   "decltype",     "default",
     "delete",   "do",           "double",     "dynamic_cast", "else",
     "enum",     "explicit",     "export",     "extern",       "false",
     "float",    "for",          "friend",     "goto",         "if",
     "inline",   "int",          "long",       "mutable",      "namespace",
     "new",      "noexcept",     "not",        "not_eq",       "nullptr",
     "operator", "or",           "or_eq",      "private",      "protected",
     "public",   "register",     "reinterpret_cast", "requires", "return",
     "short",    "signed",       "sizeof",     "static",       "static_assert",
     "static_cast", "struct",    "switch",     "template",     "this",
     "thread_local", "throw",    "true",       "try",          "typedef",
     "typeid",   "typename",     "union",      "unsigned",     "using",
     "virtual",  "void",         "volatile",   "wchar_t",      "while",
     "xor",      "xor_eq",       "if_consteval", "atomic_cancel", "atomic_commit",
     "atomic_noexcept"}};

bool ist_schluesselwort(const std::string& name) {
    for (std::size_t i = 0; i < SCHLUESSELWOERTER.size(); ++i) {
        if (name == SCHLUESSELWOERTER[i]) {
            return true;
        }
    }
    return false;
}

/// Die Wendungen der Regel `abgelegter_name`, jeweils als **letztes Wort** vor der
/// Anfuehrung. Zwei Woerter lang ist nur die erste; sie steht deshalb getrennt.
constexpr std::array<std::string_view, 11> WENDUNGEN = {
    {"statt", "kein", "keine", "keinen", "keiner", "nicht", "ohne", "gegen", "hiess",
     "hiessen", "frueher"}};

constexpr std::string_view WENDUNG_ZWEITEILIG_LETZT = "mehr";
constexpr std::string_view WENDUNG_ZWEITEILIG_ERST = "nicht";

/// Die letzten beiden Woerter eines Textes, ohne alles, was kein Buchstabe ist. Die
/// Auszeichnung des Fliesstextes -- Sternchen, Anfuehrung, Doppelpunkt -- faellt damit
/// von selbst weg.
void letzte_woerter(std::string_view text, std::string& letztes, std::string& vorletztes) {
    letztes.clear();
    vorletztes.clear();
    std::size_t i = text.size();
    for (std::size_t gefunden = 0; gefunden < 2 && i > 0;) {
        while (i > 0 && !ist_buchstabe(text[i - 1])) {
            --i;
        }
        if (i == 0) {
            break;
        }
        const std::size_t ende = i;
        while (i > 0 && ist_buchstabe(text[i - 1])) {
            --i;
        }
        const std::string wort(text.substr(i, ende - i));
        if (gefunden == 0) {
            letztes = wort;
        } else {
            vorletztes = wort;
        }
        ++gefunden;
    }
}

bool wendung_links(std::string_view links) {
    std::string letztes;
    std::string vorletztes;
    letzte_woerter(links, letztes, vorletztes);
    if (letztes.empty()) {
        return false;
    }
    if (gleich_ohne_fall(letztes, WENDUNG_ZWEITEILIG_LETZT)
        && gleich_ohne_fall(vorletztes, WENDUNG_ZWEITEILIG_ERST)) {
        return true;
    }
    for (std::size_t i = 0; i < WENDUNGEN.size(); ++i) {
        if (gleich_ohne_fall(letztes, WENDUNGEN[i])) {
            return true;
        }
    }
    return false;
}

/// Nennt der Block eine Netzadresse oder ein Quellenkuerzel in eckigen Klammern?
/// Ein Kuerzel besteht aus mindestens drei Grossbuchstaben oder Ziffern, beginnend mit
/// einem Grossbuchstaben; danach darf noch etwas folgen.
bool nennt_quelle(std::string_view block) {
    if (block.find("http://") != std::string_view::npos
        || block.find("https://") != std::string_view::npos) {
        return true;
    }
    for (std::size_t i = 0; i + 1 < block.size(); ++i) {
        if (block[i] != '[' || !ist_gross(block[i + 1])) {
            continue;
        }
        std::size_t j = i + 1;
        std::size_t gross = 0;
        while (j < block.size() && (ist_gross(block[j]) || ist_ziffer(block[j]))) {
            ++gross;
            ++j;
        }
        if (gross < 3) {
            continue;
        }
        const std::size_t schluss = block.find(']', j);
        if (schluss != std::string_view::npos) {
            return true;
        }
    }
    return false;
}

bool ist_kennung(const std::string& name) {
    std::size_t i = 0;
    while (i < name.size() && ist_gross(name[i])) {
        ++i;
    }
    if (i == 0 || i > 2) {
        return false;
    }
    const std::size_t ziffern = name.size() - i;
    if (ziffern == 0 || ziffern > 3) {
        return false;
    }
    for (std::size_t j = i; j < name.size(); ++j) {
        if (!ist_ziffer(name[j])) {
            return false;
        }
    }
    return true;
}

bool ist_commitkennung(const std::string& name) {
    if (name.size() < 7 || name.size() > 40) {
        return false;
    }
    bool ziffer = false;
    bool buchstabe = false;
    for (std::size_t i = 0; i < name.size(); ++i) {
        const char c = name[i];
        if (ist_ziffer(c)) {
            ziffer = true;
        } else if (c >= 'a' && c <= 'f') {
            buchstabe = true;
        } else {
            return false;
        }
    }
    return ziffer && buchstabe;
}

bool ist_reserviert(const std::string& name) {
    if (name.size() >= 2 && name[0] == '_' && name[1] == '_') {
        return true;
    }
    return name.size() >= 2 && name[0] == '_' && ist_gross(name[1]);
}

/// Gibt es einen deklarierten Namen, der mit `name` anfaengt und laenger ist?
bool ist_anfang_eines_namens(const Namensmenge& deklariert, const std::string& name) {
    Namensmenge::const_iterator it = deklariert.lower_bound(name);
    for (; it != deklariert.end(); ++it) {
        if (it->size() <= name.size() || it->compare(0, name.size(), name) != 0) {
            return it->compare(0, name.size(), name) == 0;
        }
        return true;
    }
    return false;
}

/// Steht im selben Block ein laengerer deklarierter Name, der mit `name` anfaengt, und
/// zwar seinerseits in Rueckwaerts-Anfuehrung?
bool voller_name_im_block(const Namensmenge& deklariert, const std::string& name,
                          std::string_view block) {
    Namensmenge::const_iterator it = deklariert.lower_bound(name);
    for (; it != deklariert.end(); ++it) {
        if (it->compare(0, name.size(), name) != 0) {
            break;
        }
        if (it->size() == name.size()) {
            continue;
        }
        const std::string gesucht = "`" + *it + "`";
        if (block.find(gesucht) != std::string_view::npos) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// Die Regeln
// ---------------------------------------------------------------------------

/// Welche Regel einen nicht aufloesenden Kandidaten durchgehen laesst -- oder eine
/// leere Sicht, wenn keine es tut. Dann ist er ein Befund.
///
/// Die Reihenfolge ist die aus dem Kopf und sie ist bedeutsam: Die spezifischen Regeln
/// stehen vor den allgemeinen, damit der Bericht den treffenden Grund nennt und nicht
/// den zuerst zufaellig passenden.
std::string_view regel(const Kandidat& k, const Bestand& b) {
    if (ist_kennung(k.letzt)) {
        return "kennung";
    }
    if (ist_commitkennung(k.letzt)) {
        return "commitkennung";
    }
    if (ist_reserviert(k.letzt)) {
        return "reserviert";
    }
    if (ist_schluesselwort(k.letzt)) {
        return "schluesselwort";
    }
    if (b.vergiftet.count(k.letzt) > 0) {
        return "vergiftet";
    }
    if (b.parameter.count(k.letzt) > 0) {
        return "parameterschluessel";
    }
    if (b.bauziele.count(k.letzt) > 0) {
        return "bauziel";
    }
    if (b.dateinamen.count(k.letzt) > 0) {
        return "dateiname";
    }
    if (!k.letzt.empty() && k.letzt.back() == '_'
        && ist_anfang_eines_namens(b.deklariert, k.letzt)) {
        return "namensvorsilbe";
    }
    if (voller_name_im_block(b.deklariert, k.letzt, k.block)) {
        return "namensteil";
    }
    if (wendung_links(k.links)) {
        return "abgelegter_name";
    }
    if (!k.vorspann.empty() && b.behaelter.count(k.vorspann) == 0) {
        return "fremder_behaelter";
    }
    if (nennt_quelle(k.block)) {
        return "quellenangabe";
    }
    if (k.vorspann.empty() && k.letzt.find('_') == std::string::npos
        && b.codetext.find(k.letzt) == std::string::npos) {
        return "fremdwort";
    }
    return "";
}

struct Regelfall {
    std::string_view voll;
    std::string_view block;
    std::string_view links;
    std::string_view erwartet;  // leer: Befund
};

/// Die Falltabelle der Regeln. Sie traegt zu jeder Regel einen Fall, den sie treffen
/// muss, und zu den drei weichsten je einen, den sie durchlassen muss.
///
/// **Fall 1 und Fall 2 sind der Kern dieses Pakets.** Beide nennen denselben Namen,
/// beide stehen im Kern, und der eine muss ein Befund sein und der andere nicht. Fall 1
/// ist der Wortlaut vor Paket 0101 -- der Satz nennt drei Namen als heutige, und einer
/// davon war seit einer Umbenennung tot. Er traegt in sich zwei Verneinungen; eine
/// satzweite Fassung von Regel 11 haette ihn durchgelassen, die enge nicht. Fall 2 ist
/// der Wortlaut am rohen Schreibzugriff, der denselben toten Namen ausdruecklich als
/// abgelegt bezeichnet -- ein richtiger Satz, der gruen bleiben muss.
constexpr std::array<Regelfall, 18> REGELFAELLE = {{
    {"schreibe",
     "Er liegt ausserhalb `0 ... 309` und ist damit **kein** Feld des Zustands. Das ist "
     "der ganze Zweck: `lies`, `schreibe` und `index_zu_adresse` pruefen `index >= "
     "FELDER` ohnehin, also wird aus einer nicht ausgewerteten Fehlanzeige ein Abbruch "
     "statt eines Zugriffs auf ein fremdes Feld.",
     "Er liegt ausserhalb `0 ... 309` und ist damit **kein** Feld des Zustands. Das ist "
     "der ganze Zweck: `lies`, ",
     ""},
    {"schreibe", "**Er heisst nicht mehr `schreibe`, und der Name ist die halbe Massnahme.**",
     "**Er heisst nicht mehr ", "abgelegter_name"},
    {"T17", "die Adressabbildung nach `T17`", "die Adressabbildung nach ", "kennung"},
    {"f6731fe", "gemessen auf dem Stand `f6731fe`", "gemessen auf dem Stand ",
     "commitkennung"},
    {"__builtin_mul_overflow", "die Wahl dieser Form ist begruendet",
     "die Wahl dieser Form ist begruendet ", "reserviert"},
    {"consteval", "`teile_zu` ist keine `consteval` Funktion", "`teile_zu` ist keine ",
     "schluesselwort"},
    // `sqrt` und nicht `double`: Der Kern vergiftet beide, aber `double` ist zugleich
    // ein Schluesselwort und faellt schon dort heraus. Ein Fall, der zwei Regeln
    // zugleich trifft, weist keine von beiden nach.
    {"sqrt", "wer im Kern `sqrt` schreibt", "wer im Kern ", "vergiftet"},
    {"instrument_min", "die vier Tabellen wiederholen `instrument_min`",
     "die vier Tabellen wiederholen ", "parameterschluessel"},
    {"kern_geprueft", "die Probe linkt `kern_geprueft`", "die Probe linkt ", "bauziel"},
    {"festkomma_probe", "`festkomma_probe` nagelt sie fest", "", "dateiname"},
    {"MAL_", "aus demselben Grund wie bei den `MAL_`-Groessen darueber",
     "aus demselben Grund wie bei den ", "namensvorsilbe"},
    {"Rest", "Das letzte heisst `Restverzoegerung` und nicht `Rest`.",
     "Das letzte heisst `Restverzoegerung` und nicht ", "namensteil"},
    {"std::bit_width", "handgeschrieben, weil `std::bit_width` nur ueber Standardtypen geht",
     "handgeschrieben, weil ", "fremder_behaelter"},
    {"fnv1a_64_test_vector", "Aus [TESTVEK], Tabelle `fnv1a_64_test_vector`, gelesen",
     "Aus [TESTVEK], Tabelle ", "quellenangabe"},
    {"grep", "der Pruefer weist die Abwesenheit mit einem `grep` nach",
     "der Pruefer weist die Abwesenheit mit einem ", "fremdwort"},
    // Die drei Gegenproben zu den weichsten Regeln.
    {"Rest", "Das letzte Feld traegt einen anderen Namen als `Rest`.",
     "Das letzte Feld traegt einen anderen Namen als ", ""},
    {"zustand::gibtsnicht", "der Aufruf `zustand::gibtsnicht` steht hier",
     "der Aufruf ", ""},
    {"mal", "der Waechter von `mal` haelt die Grenze", "der Waechter von ", ""},
}};

/// Der Bestand, gegen den die Falltabelle laeuft. Er ist klein und im Programm
/// festgelegt, damit die Faelle auch dann noch gelten, wenn der Baum sich aendert --
/// ein Selbsttest, der am Korpus haengt, misst den Korpus und nicht das Programm.
Bestand pruefbestand() {
    Bestand b;
    b.deklariert.insert("lies");
    b.deklariert.insert("index_zu_adresse");
    b.deklariert.insert("MAL_MAX");
    b.deklariert.insert("MAL_MIN");
    b.deklariert.insert("Restverzoegerung");
    b.deklariert.insert("teile_zu");
    b.parameter.insert("instrument_min");
    b.bauziele.insert("kern_geprueft");
    b.dateinamen.insert("festkomma_probe");
    b.vergiftet.insert("sqrt");
    b.behaelter.insert("kern");
    b.behaelter.insert("zustand");
    // Der Codetext des Pruefbestands: Er traegt `schreibe` (aus der negativen
    // Zusicherung, die ihn im Code stehen laesst), `Restverzoegerung` und `malnehmen`.
    // Der letzte ist der Grund, warum Fall 18 kein `fremdwort` ist -- `mal` steckt
    // darin, und die Regel sucht die Zeichenfolge und nicht das Wort.
    b.codetext = "&Z::schreibe; Restverzoegerung malnehmen teile_zu index_zu_adresse";
    return b;
}

std::size_t selbsttest_regeln() {
    const Bestand b = pruefbestand();
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < REGELFAELLE.size(); ++i) {
        const Regelfall& fall = REGELFAELLE[i];
        Kandidat k;
        if (!ist_bezeichner(fall.voll, k.voll, k.letzt, k.vorspann)) {
            std::fprintf(stderr,
                         "Selbsttest Regeln, Fall %zu: '%s' ist gar kein Bezeichner.\n",
                         i + 1, std::string(fall.voll).c_str());
            ++falsch;
            continue;
        }
        k.block = std::string(fall.block);
        k.links = std::string(fall.links);
        const std::string_view gefunden = regel(k, b);
        if (gefunden != fall.erwartet) {
            std::fprintf(stderr,
                         "Selbsttest Regeln, Fall %zu verfehlt.\n  Kandidat: %s\n"
                         "  Regel '%s', erwartet '%s'\n",
                         i + 1, std::string(fall.voll).c_str(),
                         std::string(gefunden).c_str(),
                         std::string(fall.erwartet).c_str());
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Baum
// ---------------------------------------------------------------------------

/// Ordner, die gar nicht erst betreten werden -- dieselben zwei wie beim
/// Belegstellenriegel und aus einem verschaerften Grund. `bau` traegt erzeugte Kopien
/// der Quellen; ein Riegel, der seinen eigenen Baubaum mitliest, misst sich doppelt.
/// `befunde` traegt Berichte **und Messbaeume**: unter ihm liegen ueber siebzig
/// weggeworfene Bauskripte frueherer Messungen. Ihre Zielnamen sind keine Ziele dieses
/// Vorhabens, und sie in die Regel `bauziel` zu lassen hiesse, einen toten Bezeichner
/// mit dem Namen eines Wegwerfziels zu entschuldigen. Gesammelt wird deshalb weder ihr
/// Inhalt noch ihr Name -- nur der des Ordners selbst.
constexpr std::array<std::string_view, 2> UNGELESENE_ORDNER = {"bau", "befunde"};

bool ist_ungelesener_ordner(std::string_view name) {
    for (std::size_t i = 0; i < UNGELESENE_ORDNER.size(); ++i) {
        if (name == UNGELESENE_ORDNER[i]) {
            return true;
        }
    }
    return false;
}

bool ist_maschinerie(std::string_view name) { return !name.empty() && name.front() == '.'; }

/// Alle Dateien unter `wurzel`, absteigend, ohne die ungelesenen Ordner und ohne
/// versteckte. Mit eigener Arbeitsliste statt eines absteigenden Iterators: Ein Ordner
/// voller Maschinerie soll gar nicht erst geoeffnet werden.
///
/// `ordnernamen` und `dateinamen` sammeln nebenher, was die Regel `dateiname` braucht.
/// Zwei Durchgaenge ueber denselben Baum waeren zwei Ordnerlisten, die auseinander
/// laufen koennen.
std::vector<fs::path> sammle(const fs::path& wurzel, Namensmenge& namen,
                             std::error_code& fehler) {
    std::vector<fs::path> gefunden;
    std::vector<fs::path> offen;
    offen.push_back(wurzel);
    while (!offen.empty()) {
        const fs::path ordner = offen.back();
        offen.pop_back();
        fs::directory_iterator it(ordner, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path eintrag = it->path();
            const std::string name = eintrag.filename().string();
            std::error_code art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_maschinerie(name)) {
                    namen.insert(name);
                    if (!ist_ungelesener_ordner(name)) {
                        offen.push_back(eintrag);
                    }
                }
            } else if (fs::is_regular_file(eintrag, art)) {
                namen.insert(name);
                namen.insert(eintrag.stem().string());
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

bool ist_kernquelle(const fs::path& pfad) {
    const std::string endung = pfad.extension().string();
    return endung == ".cpp" || endung == ".hpp";
}

std::string kurzname(const fs::path& pfad, const std::string& wurzeltext) {
    std::string name = pfad.string();
    if (name.size() > wurzeltext.size() && name.compare(0, wurzeltext.size(), wurzeltext) == 0) {
        name.erase(0, wurzeltext.size() + 1);
    }
    return name;
}

// ---------------------------------------------------------------------------
// Das Einlesen
// ---------------------------------------------------------------------------

struct Zaehlwerk {
    std::size_t dateien = 0;
    std::size_t zeilen = 0;
    std::size_t kommentarzeilen = 0;
    std::size_t bloecke = 0;
    std::size_t kandidaten = 0;
    std::size_t zusicherungen = 0;
};

bool hat_inhalt(const std::string& text) {
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (!ist_leerraum(text[i])) {
            return true;
        }
    }
    return false;
}

/// Liest eine Kernquelle: fuellt die Deklarationsmenge, den Codetext und die
/// Kandidatenliste.
///
/// Ein **Block** ist ein Lauf aufeinanderfolgender Zeilen mit nicht leerem
/// Kommentarteil. Eine Trennzeile ohne Text beendet ihn. Das ist dieselbe Einheit, in
/// der ein Kommentar geschrieben wird, und sie ist der Bezug der Regeln 10 und 13.
void lies_datei(const fs::path& pfad, const std::string& anzeigename, Bestand& bestand,
                std::vector<Kandidat>& kandidaten, Zaehlwerk& z) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    ++z.dateien;

    std::vector<std::string> blockzeilen;
    std::vector<std::size_t> blocknummern;

    std::string zeile;
    std::size_t nummer = 0;
    bool im_block = false;

    // Ein Block wird erst ausgewertet, wenn er zu Ende ist -- vorher steht sein Text
    // nicht vollstaendig fest, und die Regeln 10 und 13 brauchen ihn ganz.
    const auto blockschluss = [&]() {
        if (blockzeilen.empty()) {
            return;
        }
        ++z.bloecke;
        std::string ganzer;
        for (std::size_t i = 0; i < blockzeilen.size(); ++i) {
            ganzer.append(blockzeilen[i]);
            ganzer.push_back(' ');
        }
        std::string vorlauf;
        for (std::size_t i = 0; i < blockzeilen.size(); ++i) {
            const std::string& text = blockzeilen[i];
            std::size_t j = 0;
            while (j < text.size()) {
                if (text[j] != '`') {
                    ++j;
                    continue;
                }
                const std::size_t schluss = text.find('`', j + 1);
                if (schluss == std::string::npos) {
                    break;
                }
                Kandidat k;
                if (ist_bezeichner(std::string_view(text).substr(j + 1, schluss - j - 1),
                                   k.voll, k.letzt, k.vorspann)) {
                    k.block = ganzer;
                    k.links = vorlauf + text.substr(0, j);
                    k.datei = anzeigename;
                    k.zeilennummer = blocknummern[i];
                    kandidaten.push_back(k);
                    ++z.kandidaten;
                }
                j = schluss + 1;
            }
            vorlauf.append(text);
            vorlauf.push_back(' ');
        }
        blockzeilen.clear();
        blocknummern.clear();
    };

    while (std::getline(strom, zeile)) {
        ++nummer;
        ++z.zeilen;
        if (!zeile.empty() && zeile.back() == '\r') {
            zeile.pop_back();
        }
        const Zerlegung teil = zerlege(zeile, im_block);
        im_block = teil.im_block;

        bestand.codetext.append(teil.code);
        bestand.codetext.push_back('\n');

        // Die Deklarationsmenge: jeder Name des Codeteils **ausser** dem Mitgliedsnamen
        // einer negativen Sichtbarkeitszusicherung. Das ist Bedingung 2 des Pakets, und
        // sie steht hier als einzige Stelle im Programm.
        const std::vector<Zusicherung> zus = zusicherungen(teil.code);
        z.zusicherungen += zus.size();
        std::size_t i = 0;
        while (i < teil.code.size()) {
            if (!ist_namensanfang(teil.code[i])) {
                ++i;
                continue;
            }
            const std::size_t ende = hinter_namen(teil.code, i);
            bool zugesichert = false;
            for (std::size_t k = 0; k < zus.size(); ++k) {
                if (zus[k].anfang == i && zus[k].ende == ende) {
                    zugesichert = true;
                }
            }
            if (!zugesichert) {
                bestand.deklariert.insert(teil.code.substr(i, ende - i));
            }
            i = ende;
        }

        if (hat_inhalt(teil.kommentar)) {
            ++z.kommentarzeilen;
            blockzeilen.push_back(teil.kommentar);
            blocknummern.push_back(nummer);
        } else {
            blockschluss();
        }
    }
    blockschluss();
}

/// Namensraeume und Verbunde des Kerns -- der Bestand der Regel `fremder_behaelter`.
/// Gelesen wird der Codeteil, damit ein Wort aus einem Kommentar nicht zum Namensraum
/// wird.
void sammle_behaelter(std::string_view code, Namensmenge& ziel) {
    constexpr std::array<std::string_view, 5> WOERTER = {
        {"namespace", "class", "struct", "union", "enum"}};
    for (std::size_t i = 0; i < WOERTER.size(); ++i) {
        const std::string_view wort = WOERTER[i];
        std::size_t j = 0;
        while (j < code.size()) {
            const std::size_t treffer = code.find(wort, j);
            if (treffer == std::string_view::npos) {
                break;
            }
            j = treffer + wort.size();
            const bool wortanfang = treffer == 0 || !ist_namenszeichen(code[treffer - 1]);
            if (!wortanfang || (j < code.size() && ist_namenszeichen(code[j]))) {
                continue;
            }
            std::size_t k = hinter_leerraum(code, j);
            // `enum class X` und `enum struct X` -- das Wort dazwischen ueberspringen.
            if (wort == "enum") {
                const std::size_t nach = hinter_namen(code, k);
                const std::string_view naechstes = code.substr(k, nach - k);
                if (naechstes == "class" || naechstes == "struct") {
                    k = hinter_leerraum(code, nach);
                }
            }
            const std::size_t ende = hinter_namen(code, k);
            if (ende > k) {
                ziel.insert(std::string(code.substr(k, ende - k)));
            }
        }
    }
}

/// Die Namen aus den Vergiftungszeilen des Kerns. Sie werden gelesen und nicht
/// abgeschrieben: Eine zweite Fassung derselben Liste ist die, die niemand nachfuehrt.
void sammle_vergiftete(const fs::path& pfad, Namensmenge& ziel) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    const std::string marke = "pragma GCC poison";
    std::string zeile;
    while (std::getline(strom, zeile)) {
        const std::size_t treffer = zeile.find(marke);
        if (treffer == std::string::npos) {
            continue;
        }
        std::size_t i = treffer + marke.size();
        while (i < zeile.size()) {
            if (!ist_namensanfang(zeile[i])) {
                ++i;
                continue;
            }
            const std::size_t ende = hinter_namen(zeile, i);
            ziel.insert(zeile.substr(i, ende - i));
            i = ende;
        }
    }
}

/// Schluessel und Tabellennamen der Kalibrierdatei.
void sammle_parameter(const fs::path& pfad, Namensmenge& ziel) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    std::string zeile;
    while (std::getline(strom, zeile)) {
        std::size_t i = 0;
        while (i < zeile.size() && ist_leerraum(zeile[i])) {
            ++i;
        }
        if (i >= zeile.size()) {
            continue;
        }
        if (zeile[i] == '[') {
            while (i < zeile.size() && zeile[i] == '[') {
                ++i;
            }
            while (i < zeile.size() && zeile[i] != ']') {
                if (!ist_namensanfang(zeile[i])) {
                    ++i;
                    continue;
                }
                const std::size_t ende = hinter_namen(zeile, i);
                ziel.insert(zeile.substr(i, ende - i));
                i = ende;
            }
            continue;
        }
        if (!ist_namensanfang(zeile[i])) {
            continue;
        }
        const std::size_t ende = hinter_namen(zeile, i);
        std::size_t nach = ende;
        while (nach < zeile.size() && ist_leerraum(zeile[nach])) {
            ++nach;
        }
        if (nach < zeile.size() && zeile[nach] == '=') {
            ziel.insert(zeile.substr(i, ende - i));
        }
    }
}

/// Ziele und Mitglieder aus einem Bauskript. Gelesen werden die vier Anweisungen, die
/// ein Ziel anlegen, der Name einer Probe und die Mitgliederliste des Arbeitsbereichs.
void sammle_bauziele(const fs::path& pfad, Namensmenge& ziel) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    constexpr std::array<std::string_view, 4> ANWEISUNGEN = {
        {"add_executable", "add_library", "add_custom_target", "add_test"}};
    std::string ganzes;
    std::string zeile;
    while (std::getline(strom, zeile)) {
        ganzes.append(zeile);
        ganzes.push_back('\n');
    }
    for (std::size_t a = 0; a < ANWEISUNGEN.size(); ++a) {
        const std::string_view wort = ANWEISUNGEN[a];
        std::size_t j = 0;
        while (j < ganzes.size()) {
            const std::size_t treffer = ganzes.find(wort, j);
            if (treffer == std::string::npos) {
                break;
            }
            j = treffer + wort.size();
            std::size_t k = hinter_leerraum(ganzes, j);
            if (k >= ganzes.size() || ganzes[k] != '(') {
                continue;
            }
            k = hinter_leerraum(ganzes, k + 1);
            if (wort == "add_test") {
                const std::size_t nach = hinter_namen(ganzes, k);
                if (ganzes.compare(k, nach - k, "NAME") != 0) {
                    continue;
                }
                k = hinter_leerraum(ganzes, nach);
            }
            const std::size_t ende = hinter_namen(ganzes, k);
            if (ende > k) {
                ziel.insert(ganzes.substr(k, ende - k));
            }
        }
    }
    // Die Mitgliederliste: Ihre Eintraege sind Pfade, und jeder Pfadteil zaehlt --
    // `pruefstand` steht als Baustein in einem Kommentar des Kerns.
    const std::string marke = "FABRIK_MITGLIEDER";
    std::size_t stelle = ganzes.find(marke);
    while (stelle != std::string::npos) {
        std::size_t i = stelle + marke.size();
        while (i < ganzes.size() && ganzes[i] != ')') {
            if (!ist_namensanfang(ganzes[i])) {
                ++i;
                continue;
            }
            const std::size_t ende = hinter_namen(ganzes, i);
            ziel.insert(ganzes.substr(i, ende - i));
            i = ende;
        }
        stelle = ganzes.find(marke, i);
    }
}

bool ist_bauskript(const fs::path& pfad) {
    return pfad.filename().string() == "CMakeLists.txt" || pfad.extension().string() == ".cmake";
}

struct Uebergangen {
    std::string name;
    std::string grund;
    std::string datei;
    std::size_t zeilennummer = 0;
};

struct Befund {
    std::string name;
    std::string voll;
    std::string datei;
    std::size_t zeilennummer = 0;
};

}  // namespace

int main(int argc, char** argv) {
    // Der Selbsttest laeuft vor allem anderen und braucht kein Argument. Stimmt die
    // Zerlegung oder eine der Regeln nicht, ist jede Zahl weiter unten wertlos.
    const std::size_t fehlgeschlagen = selbsttest_zerlegung() + selbsttest_zusicherung()
                                       + selbsttest_form() + selbsttest_regeln();
    const std::size_t faelle = ZERLEGEFAELLE.size() + ZUSICHERUNGSFAELLE.size()
                               + FORMFAELLE.size() + REGELFAELLE.size();
    if (fehlgeschlagen > 0) {
        std::fprintf(stderr,
                     "\nbezeichner_riegel: %zu von %zu Faellen des Selbsttests sind nicht "
                     "wie erwartet\nausgegangen. Der Riegel hat den Bestand gar nicht erst "
                     "gelesen -- ein Messgeraet,\ndas seine eigenen Faelle verfehlt, misst "
                     "auch fremde nicht.\n",
                     fehlgeschlagen, faelle);
        return 2;
    }
    std::fprintf(stdout,
                 "bezeichner_riegel, Selbsttest: %zu Faelle zur Zerlegung, %zu zur "
                 "negativen\nZusicherung, %zu zur Form eines Kandidaten und %zu zu den "
                 "Regeln, alle wie erwartet.\n",
                 ZERLEGEFAELLE.size(), ZUSICHERUNGSFAELLE.size(), FORMFAELLE.size(),
                 REGELFAELLE.size());

    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() != 2) {
        std::fprintf(stderr,
                     "Aufruf: bezeichner_riegel <wurzel-des-vorhabens>\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf einem "
                     "Rechner.\n");
        return 2;
    }

    std::error_code fehler;
    const fs::path wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "bezeichner_riegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }
    const fs::path kernwurzel = wurzel / "kern";
    if (!fs::is_directory(kernwurzel, fehler)) {
        std::fprintf(stderr,
                     "bezeichner_riegel: unter '%s' liegt kein Kern. Dieser Riegel prueft "
                     "den Kern\nund nichts sonst; ohne ihn hat er keinen Gegenstand.\n",
                     wurzel.string().c_str());
        return 2;
    }

    Bestand bestand;
    Namensmenge namen;
    std::error_code lesefehler;
    const std::vector<fs::path> alle = sammle(wurzel, namen, lesefehler);
    if (lesefehler) {
        std::fprintf(stderr, "bezeichner_riegel: Lesefehler unter '%s': %s\n",
                     wurzel.string().c_str(), lesefehler.message().c_str());
        return 2;
    }
    bestand.dateinamen = namen;

    const std::string wurzeltext = wurzel.string();
    const std::string kerntext = kernwurzel.string();

    std::vector<fs::path> kernquellen;
    std::vector<std::string> kernnamen;
    std::size_t bauskripte = 0;
    for (std::size_t i = 0; i < alle.size(); ++i) {
        const std::string pfad = alle[i].string();
        const bool im_kern = pfad.size() > kerntext.size()
                             && pfad.compare(0, kerntext.size(), kerntext) == 0;
        if (im_kern && ist_kernquelle(alle[i])) {
            kernquellen.push_back(alle[i]);
            kernnamen.push_back(kurzname(alle[i], wurzeltext));
        }
        if (ist_bauskript(alle[i])) {
            sammle_bauziele(alle[i], bestand.bauziele);
            ++bauskripte;
        }
        if (alle[i].filename().string() == "parameter.toml") {
            sammle_parameter(alle[i], bestand.parameter);
        }
    }

    std::vector<Kandidat> kandidaten;
    Zaehlwerk zaehlwerk;
    for (std::size_t i = 0; i < kernquellen.size(); ++i) {
        lies_datei(kernquellen[i], kernnamen[i], bestand, kandidaten, zaehlwerk);
        sammle_vergiftete(kernquellen[i], bestand.vergiftet);
    }
    sammle_behaelter(bestand.codetext, bestand.behaelter);

    // ------------------------------------------------------------------
    // Die Vorsorge gegen den stillen Ausfall
    // ------------------------------------------------------------------
    if (kernquellen.empty()) {
        std::fprintf(stderr,
                     "bezeichner_riegel: keine einzige Kernquelle unter '%s' gefunden. Das "
                     "ist kein\ngruener Lauf, sondern ein Riegel ohne Gegenstand.\n",
                     kernwurzel.string().c_str());
        return 2;
    }
    if (zaehlwerk.kandidaten == 0) {
        std::fprintf(stderr,
                     "bezeichner_riegel: kein einziger Bezeichner in Rueckwaerts-Anfuehrung "
                     "gefunden.\nDas ist ein Befund gegen die Kandidatensuche und keine "
                     "bestandene Bedingung.\n");
        return 2;
    }
    if (zaehlwerk.zusicherungen == 0) {
        std::fprintf(stderr,
                     "bezeichner_riegel: keine einzige negative Sichtbarkeitszusicherung im "
                     "Kern.\nSie ist die tragende Regel dieses Riegels -- ohne sie ist der "
                     "Lauf nicht gruen,\nsondern gegenstandslos. Entweder liest der "
                     "Mustervergleich sie nicht mehr, dann\nist das die Ursache, oder der "
                     "Kern fuehrt sie nicht mehr. Nur im zweiten Fall\nwird diese Schranke "
                     "geaendert, und zwar mit Begruendung an ihrer Stelle.\n");
        return 2;
    }

    // ------------------------------------------------------------------
    // Die Pruefung
    // ------------------------------------------------------------------
    std::vector<Befund> befunde;
    std::vector<Uebergangen> uebergangen;
    std::map<std::string, std::size_t> je_grund;
    std::size_t aufgeloest = 0;
    for (std::size_t i = 0; i < kandidaten.size(); ++i) {
        const Kandidat& k = kandidaten[i];
        if (bestand.deklariert.count(k.letzt) > 0) {
            ++aufgeloest;
            continue;
        }
        const std::string_view grund = regel(k, bestand);
        if (grund.empty()) {
            befunde.push_back(Befund{k.letzt, k.voll, k.datei, k.zeilennummer});
        } else {
            uebergangen.push_back(
                Uebergangen{k.letzt, std::string(grund), k.datei, k.zeilennummer});
            ++je_grund[std::string(grund)];
        }
    }

    std::fprintf(stdout,
                 "bezeichner_riegel: %zu Kernquellen mit %zu Zeilen gelesen, davon %zu "
                 "Kommentarzeilen\nin %zu Bloecken; %zu Bezeichner in Rueckwaerts-"
                 "Anfuehrung geprueft, %zu davon\naufgeloest, %zu Fundstellen uebergangen. "
                 "%zu Namen im Kern deklariert, %zu negative\nSichtbarkeitszusicherungen "
                 "abgezogen. Nebenbestaende: %zu Schluessel der Kalibrierdatei,\n%zu "
                 "Bauziele aus %zu Bauskripten, %zu Datei- und Ordnernamen, %zu vergiftete "
                 "Namen,\n%zu eigene Behaelter.\n",
                 zaehlwerk.dateien, zaehlwerk.zeilen, zaehlwerk.kommentarzeilen,
                 zaehlwerk.bloecke, zaehlwerk.kandidaten, aufgeloest, uebergangen.size(),
                 bestand.deklariert.size(), zaehlwerk.zusicherungen,
                 bestand.parameter.size(), bestand.bauziele.size(), bauskripte,
                 bestand.dateinamen.size(), bestand.vergiftet.size(),
                 bestand.behaelter.size());

    if (!uebergangen.empty()) {
        std::fprintf(stdout,
                     "\nUebergangen -- der ausgeschriebene Nachlass dieses Riegels. Jede "
                     "Fundstelle mit\nder Regel, die sie durchgelassen hat. Gezaehlt und "
                     "genannt, aber nicht bewertet:\n\n");
        for (std::size_t i = 0; i < uebergangen.size(); ++i) {
            const Uebergangen& u = uebergangen[i];
            std::fprintf(stdout, "  %-24s %-20s %s (Zeile %zu)\n", u.name.c_str(),
                         u.grund.c_str(), u.datei.c_str(), u.zeilennummer);
        }
        std::fprintf(stdout, "\n  je Regel:");
        for (std::map<std::string, std::size_t>::const_iterator it = je_grund.begin();
             it != je_grund.end(); ++it) {
            std::fprintf(stdout, " %s %zu;", it->first.c_str(), it->second);
        }
        std::fprintf(stdout, "\n");
    }

    if (befunde.empty()) {
        std::fprintf(stdout,
                     "\nKein Bezeichner in einem Kommentar des Kerns zeigt ins Leere: Alle "
                     "%zu genannten\nNamen loesen auf, und die uebrigen %zu Fundstellen "
                     "fallen unter eine benannte Regel.\n",
                     aufgeloest, uebergangen.size());
        return 0;
    }

    std::fprintf(stderr,
                 "\n%zu Bezeichner in Kommentaren des Kerns loesen nicht auf:\n\n",
                 befunde.size());
    for (std::size_t i = 0; i < befunde.size(); ++i) {
        const Befund& b = befunde[i];
        std::fprintf(stderr, "  %s (Zeile %zu)\n      genannt: %s\n      gesucht: %s\n",
                     b.datei.c_str(), b.zeilennummer, b.voll.c_str(), b.name.c_str());
    }
    std::fprintf(stderr,
                 "\nEntweder ist der Name umbenannt worden -- dann wird der Kommentar "
                 "nachgezogen --,\noder er hiess nie so. Beides wird berichtigt und nicht "
                 "ausgenommen. Ist der Name\nzu Recht keiner des Kerns, gehoert er unter "
                 "eine der benannten Regeln, und die\nRegel wird begruendet, wo sie "
                 "steht -- nicht der einzelne Name geduldet.\n");
    return 1;
}
