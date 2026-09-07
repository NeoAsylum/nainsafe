//! # Der Zahlwortriegel -- Paket 0180, um Sorte 3 erweitert in Paket 0194
//!
//! `werte.hpp` traegt Saetze, die zaehlen, was unter ihnen steht. Sie stimmen, wenn sie
//! geschrieben werden, und sie werden falsch, sobald ein Paket eine Deklaration
//! ergaenzt. Innerhalb eines Tages hat das zwei Pakete gekostet, beide auf derselben
//! Datei: `0152` zog vier Stellen von "siebzehn" auf "zweiundzwanzig" nach, `0155` zog
//! "die eine Jahrgangskonstante" auf "die zwei" nach. Beide Male hat die Zahl einen
//! Lauf ueberlebt, in dem sie schon falsch war -- `0151` legte `durchgriff` an, und der
//! Kopf zaehlte weiter eins.
//!
//! Die Zahlen sind nicht schwer zu bilden. Sie sind schwer im Blick zu behalten, und
//! genau das ist die Sorte Arbeit, die kein Agent tun sollte.
//!
//! ## Was dieses Programm prueft -- drei Behauptungen gegen drei Zaehlungen
//!
//! Gelesen wird genau eine Datei, `kern/include/kern/werte.hpp`, und in ihr werden
//! drei Sorten Satz gegen drei Zaehlungen im selben Quelltext gehalten:
//!
//!   **Sorte 1 -- das Zahlwort vor "Groessen"** gegen die Zahl der T48-Nummern, die als
//!   oeffentliche Funktionsdeklaration darunter stehen. Gezaehlt werden **Nummern und
//!   nicht Zeilen**: Nr. 11 traegt zwei Stelligkeiten unter einer Nummer.
//!
//!   **Sorte 2 -- das Zahlwort vor "Jahrgangskonstante" oder "Jahrgangskonstanten"**
//!   gegen die Zahl der Felder von `struct Konstanten`, deren Kommentar sich auf T23
//!   Punkt 5 beruft.
//!
//!   **Sorte 3 -- das Zahlwort vor "Deklarationen"** gegen die Zahl der
//!   Funktionsdeklarationen, diesmal **Zeilen und nicht Nummern** (Paket 0194).
//!
//! Sorte 1 und Sorte 3 stehen in **einem** Satz: Zeile 32 sagt "Zweiundzwanzig
//! Groessen in dreiundzwanzig Deklarationen". Bis 0194 war davon eine Zahl bewacht und
//! eine nicht -- eine weitere Stelligkeit unter einer **vorhandenen** Nummer laesst die
//! Nummernzaehlung bei 22 und macht "dreiundzwanzig" still falsch. Genau diese Sorte
//! Drift hat 0151 schon einmal einen Lauf lang ueberlebt. Zwei Zahlen in einem Satz
//! brauchen zwei Pruefungen: Ein Vergleich der ganzen Zeile wuerde rot, sagte aber
//! nicht, welche Haelfte riss.
//!
//! Die Zaehlungen kommen aus dem Quelltext und nicht aus diesem Programm. Eine feste
//! Sollzahl hier waere ein Messgeraet, das nur prueft, dass die Welt sich nicht bewegt
//! -- und der Text duerfte still falsch werden, waehrend beide Seiten sich aendern.
//!
//! ## Was als Zahlbehauptung gilt, und warum die Unterscheidung tragend ist
//!
//! Nicht jede Stelle mit dem Wort behauptet eine Zahl. Der Kopf sagt an einer Stelle
//! "weder eine Zustandsadresse noch ein Parameterschluessel noch eine
//! Jahrgangskonstante" -- das nennt eine Kategorie und keine Anzahl. Ohne diese
//! Unterscheidung waere der Riegel ein Dauerbefund, und ein Dauerbefund wird
//! abgeschaltet.
//!
//! Die Schwierigkeit sitzt in einem einzigen Wort: `eine` ist im Deutschen zugleich
//! unbestimmter Artikel und Kardinalzahl. Die Regel trennt beides an dem, was links
//! davon steht:
//!
//!   * **Kardinalzahl** unmittelbar vor dem Wort -- `zwei Jahrgangskonstanten`. Sie
//!     behauptet, wie viele es sind, und wird auf **Gleichheit** geprueft.
//!   * Ist die Kardinalzahl eine der mehrdeutigen Formen (`ein`, `eine`, `einer`,
//!     `eines`, `einem`, `einen`), zaehlt sie nur mit **bestimmtem Artikel davor**:
//!     `die eine Jahrgangskonstante` ist eine Behauptung, `noch eine Jahrgangskonstante`
//!     ist keine.
//!   * **Ordnungszahl** -- `die zweite Jahrgangskonstante`. Sie behauptet nicht, wie
//!     viele es sind, sondern dass es mindestens so viele sind; geprueft wird `<=`.
//!   * **Alles andere** ist keine Zahlbehauptung und wird gezaehlt, genannt und nicht
//!     bewertet.
//!
//! Zwischen Zahlwort und Nomen darf **genau ein Beiwort** stehen -- der Modulkopf sagt
//! "die zweiundzwanzig abgeleiteten Groessen", und ohne diesen Schritt bliebe die
//! erste Zeile der Datei ungeprueft. Ein Beiwort ist hier ein kleingeschriebenes,
//! rein alphabetisches Wort mit einer der Beugungsendungen `e`, `en`, `er`, `es`, `em`,
//! das weder Zahlwort noch Begleiter ist. Die Enge ist Absicht: `und keine Groessen`
//! kommt im Bestand vor, und ein weiteres Fenster faende dort das `vier` aus dem
//! Satzteil davor.
//!
//! ## Die Zahlwoerter werden gerechnet, nicht aufgezaehlt
//!
//! Eine Liste der gebrauchten Zahlwoerter waere dieselbe Handnachfuehrung, gegen die
//! dieses Programm antritt: Wer von zweiundzwanzig auf dreiundzwanzig geht, muesste
//! erst hier ein Wort ergaenzen, sonst faende der Riegel keine Behauptung mehr und
//! meldete gruen. Zusammengesetzte Zahlwoerter werden deshalb zerlegt
//! (`<einer>und<zehner>`), Ordnungszahlen auf ihren Kardinalstamm zurueckgefuehrt
//! (`...ste`, `...te`) und nur die unregelmaessigen Formen benannt.
//!
//! ## Die Grenzen, ausgeschrieben
//!
//!   * **Nur `werte.hpp`.** Was eine Zahl im Kommentar zaehlt, steht nirgends
//!     maschinenlesbar; ein allgemeiner Riegel muesste es raten. Diese Datei ist die,
//!     an der es zweimal weh getan hat. Wer den Riegel allgemein will, braucht zuerst
//!     eine erklaerte Zaehlmarke im Kommentar -- das ist eine Entwurfsfrage und ein
//!     anderes Paket.
//!   * **Nur der Plural "Groessen".** Der Singular kommt im Bestand in Wendungen vor,
//!     die eine Zahl nennen und sie zugleich verneinen ("ist keine dreiundzwanzigste
//!     Groesse"). Eine Verneinung maschinell zu lesen ist eine andere Aufgabe; der
//!     Plural traegt alle vier Zaehlsaetze der Datei.
//!   * **Nur der Plural "Deklarationen"**, aus demselben Grund: Der Singular steht im
//!     Bestand in "haben in diesem Kopf keine Deklaration" -- wieder eine Verneinung.
//!     Der Plural steht zweimal, einmal mit Zahl (Zeile 32) und einmal ohne ("die
//!     oeffentlichen Deklarationen dieses Kopfes"); beide Stellen stehen als Fall im
//!     Selbsttest, damit die stumme stumm bleibt.
//!   * **Nur Zahlwoerter, keine Ziffern.** `die 22 Groessen` faengt dieser Riegel
//!     nicht. Der Bestand schreibt Zaehlsaetze aus, und eine Ziffernform mitzunehmen
//!     hiesse, jede Jahreszahl und jede Vorgabenkennung erst wieder auszunehmen.
//!   * **Nur ganzzeilige Kommentare.** Ein Kommentar hinter Code auf derselben Zeile
//!     wird nicht gelesen. Die Datei hat keinen solchen; der Selbsttest haelt die
//!     Grenze fest, damit sie niemand fuer eine Deckung haelt.
//!
//! ## Der Selbsttest, der bei jedem Aufruf mitlaeuft
//!
//! Fuenf Tabellen laufen **vor** dem ersten Lesen der Datei, und ein verfehlter Fall
//! bricht den Lauf mit Code 2 ab: die Zerlegung in Woerter und Bloecke, die Erkennung
//! der Zahlbehauptung, der Schritt vom Behaupteten zum Urteil, die beiden Zaehlungen
//! und -- als fuenfte -- die **Verdrahtung**: derselbe Weg, den der Ernstfall geht,
//! aber auf Text statt auf einer Datei. Die vier ersten pruefen je einen Baustein; ohne
//! die fuenfte liesse sich das Zusammensetzen auf "immer gruen" festnageln, ohne dass
//! ein Fall risse.
//!
//! ## Die Empfindlichkeitsprobe -- der Rotnachweis laeuft mit, statt danebenzuliegen
//!
//! Ein Riegel, der nie rot wird, prueft nichts, und ob er es wuerde, weiss man nur,
//! wenn man es zeigt. Deshalb macht dieses Programm nach dem gruenen Lauf **denselben
//! Lauf ein zweites Mal auf einem Mutanten des gelesenen Textes**: Unter eine
//! **vorhandene** Nummer der Tabelle kommt eine weitere Deklaration. Damit bleibt die
//! Nummernzaehlung, wo sie war, und nur die Zahl der Deklarationen steigt um eins --
//! die Drift, gegen die Sorte 3 gebaut ist. Verlangt wird: die Zahl der Deklarationen
//! genau eins hoeher, die Nummernmenge und die Maengelliste unveraendert, an Sorte 3
//! **mehr** Abweichungen als vorher und an den Sorten 1 und 2 gleich viele. Faellt eine
//! dieser Bedingungen aus, ist der Riegel taub und meldet **2** statt gruen.
//!
//! Der Mutant wird nur im Speicher gebildet; `werte.hpp` wird gelesen und nie
//! geschrieben. Wer den roten Lauf selbst sehen will, ruft
//! `zahlwort_riegel <wurzel> --bruch=stelligkeit` -- dann laeuft der ganze Riegel auf
//! dem Mutanten, druckt seinen Nachlass und gibt **1**. Der Schalter verbiegt die
//! geholte Eingabe an genau einer Stelle und ist die einzige Stelle, an der dieses
//! Programm etwas anderes prueft als die Datei.
//!
//! ## Die drei Rueckgabewerte
//!
//!   * **2** -- der Selbsttest ist verfehlt, die Empfindlichkeitsprobe ist verfehlt,
//!     die Datei fehlt, oder der Riegel hat keinen Gegenstand (keine Deklaration, kein
//!     Feld, keine Zahlbehauptung einer der drei Sorten). Das ist kein gruener Lauf,
//!     sondern ein Messgeraet ohne Messung.
//!   * **1** -- eine Behauptung weicht von ihrer Zaehlung ab, oder eine Deklaration
//!     nennt keine Nummer der Tabelle, oder ein Feld faellt in keine der beiden Sorten.
//!   * **0** -- jede Behauptung deckt sich mit ihrer Zaehlung.

#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

/// Die eine Datei, die dieser Riegel liest. Relativ zur Wurzel des Vorhabens, die von
/// CMake kommt -- ein eingebauter Pfad liefe nur auf einem Rechner.
constexpr std::string_view PRUEFLING = "kern/include/kern/werte.hpp";

/// Der Traeger der Zahlen neben dem Zustand. Sein Rumpf traegt die Felder, gegen die
/// Sorte 2 zaehlt.
constexpr std::string_view TRAEGER = "struct Konstanten";

/// Die Berufung, an der ein Feld sich selbst als Groesse des Jahrgangs ausweist. Sie
/// steht im Kommentar des Feldes und nicht in einer Liste hier -- eine Liste waere
/// wieder die Handnachfuehrung.
constexpr std::string_view BERUFUNG_JAHRGANG = "T23 Punkt 5";

/// Woran ein Feld sich als Parameterschluessel nach T27 ausweist.
constexpr std::string_view BERUFUNG_SCHLUESSEL = "/// Schluessel ";

/// Der Vorspann, hinter dem die laufende Nummer der Tabelle aus T48 steht.
constexpr std::string_view VORSPANN_NUMMER = "T48 Nr. ";

/// Der Schalter, der den Rotnachweis von Hand fuehrt. Er steht hier neben den anderen
/// Wortlauten und nicht in `main`, damit die Meldung, die ihn nennt, und die Stelle,
/// die ihn liest, denselben Wortlaut benutzen.
constexpr std::string_view BRUCHSCHALTER = "--bruch=stelligkeit";

// ---------------------------------------------------------------------------
// Zeichenwerk
// ---------------------------------------------------------------------------

bool ist_klein(char c) {
    const unsigned char u = static_cast<unsigned char>(c);
    return u >= 'a' && u <= 'z';
}

bool ist_gross(char c) {
    const unsigned char u = static_cast<unsigned char>(c);
    return u >= 'A' && u <= 'Z';
}

bool ist_buchstabe(char c) { return ist_klein(c) || ist_gross(c); }

bool ist_ziffer(char c) {
    const unsigned char u = static_cast<unsigned char>(c);
    return u >= '0' && u <= '9';
}

bool ist_leerraum(char c) { return c == ' ' || c == '\t' || c == '\r'; }

std::string klein_geschrieben(std::string_view w) {
    std::string s;
    s.reserve(w.size());
    for (std::size_t i = 0; i < w.size(); ++i) {
        const char c = w[i];
        s.push_back(ist_gross(c) ? static_cast<char>(c - 'A' + 'a') : c);
    }
    return s;
}

std::string getrimmt(std::string_view zeile) {
    std::size_t a = 0;
    while (a < zeile.size() && ist_leerraum(zeile[a])) {
        ++a;
    }
    std::size_t e = zeile.size();
    while (e > a && ist_leerraum(zeile[e - 1])) {
        --e;
    }
    return std::string(zeile.substr(a, e - a));
}

bool beginnt_mit(std::string_view text, std::string_view anfang) {
    return text.size() >= anfang.size() && text.compare(0, anfang.size(), anfang) == 0;
}

bool endet_auf(std::string_view text, std::string_view ende) {
    return text.size() >= ende.size()
           && text.compare(text.size() - ende.size(), ende.size(), ende) == 0;
}

std::vector<std::string> zeilen_von(std::string_view text) {
    std::vector<std::string> zeilen;
    std::string laufend;
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\n') {
            zeilen.push_back(laufend);
            laufend.clear();
        } else {
            laufend.push_back(text[i]);
        }
    }
    if (!laufend.empty()) {
        zeilen.push_back(laufend);
    }
    return zeilen;
}

// ---------------------------------------------------------------------------
// Zahlwoerter -- gerechnet statt aufgezaehlt
// ---------------------------------------------------------------------------

/// Die zwanzig Grundzahlen. Sie lassen sich nicht bilden und stehen deshalb da.
constexpr std::array<std::string_view, 20> GRUNDZAHL = {
    "null",      "eins",     "zwei",     "drei",     "vier",
    "fuenf",     "sechs",    "sieben",   "acht",     "neun",
    "zehn",      "elf",      "zwoelf",   "dreizehn", "vierzehn",
    "fuenfzehn", "sechzehn", "siebzehn", "achtzehn", "neunzehn"};

/// Die vollen Zehner ab zwanzig, in Zehnerschritten.
constexpr std::array<std::string_view, 8> ZEHNER = {
    "zwanzig", "dreissig", "vierzig", "fuenfzig",
    "sechzig", "siebzig",  "achtzig", "neunzig"};

/// Die Einerform, wie sie **in einer Zusammensetzung** steht: `ein` und nicht `eins`.
constexpr std::array<std::string_view, 10> EINERFORM = {
    "", "ein", "zwei", "drei", "vier", "fuenf", "sechs", "sieben", "acht", "neun"};

/// Die Formen, in denen die Kardinalzahl eins mit dem unbestimmten Artikel
/// zusammenfaellt. Sie sind der ganze Grund fuer die Artikelregel weiter unten.
constexpr std::array<std::string_view, 6> MEHRDEUTIG = {"ein",   "eine",  "einer",
                                                        "eines", "einem", "einen"};

/// Die bestimmten Artikel. Steht einer unmittelbar vor einer mehrdeutigen Form, ist
/// die Form dort eine Zahl und kein Begleiter.
constexpr std::array<std::string_view, 6> ARTIKEL_BESTIMMT = {"die", "der", "das",
                                                              "den", "dem", "des"};

/// Begleiter, die nie ein Beiwort sind. Ohne diese Liste zaehlte `keine` als Beiwort,
/// und der Riegel spraenge im Satz "vier Zeilen und keine Groessen" ueber das `keine`
/// hinweg auf ein `vier`, das zu einem anderen Nomen gehoert.
constexpr std::array<std::string_view, 26> BEGLEITER = {
    "die",    "der",    "das",    "den",    "dem",    "des",    "ein",
    "eine",   "einer",  "eines",  "einem",  "einen",  "kein",   "keine",
    "keiner", "keines", "keinem", "keinen", "jede",   "jeder",  "jedes",
    "jedem",  "jeden",  "diese",  "dieser", "dieses"};

struct Unregelmaessig {
    std::string_view wort;
    std::size_t wert;
};

/// Die Ordnungszahlen, die sich nicht aus ihrem Kardinalstamm bilden lassen.
constexpr std::array<Unregelmaessig, 5> ORDNUNG_UNREGELMAESSIG = {
    Unregelmaessig{"erste", 1}, Unregelmaessig{"dritte", 3}, Unregelmaessig{"siebte", 7},
    Unregelmaessig{"siebente", 7}, Unregelmaessig{"achte", 8}};

bool in_liste(std::string_view wort, const std::string_view* liste, std::size_t anzahl) {
    for (std::size_t i = 0; i < anzahl; ++i) {
        if (wort == liste[i]) {
            return true;
        }
    }
    return false;
}

bool ist_mehrdeutig(std::string_view klein) {
    return in_liste(klein, MEHRDEUTIG.data(), MEHRDEUTIG.size());
}

bool ist_bestimmter_artikel(std::string_view wort) {
    return in_liste(klein_geschrieben(wort), ARTIKEL_BESTIMMT.data(),
                    ARTIKEL_BESTIMMT.size());
}

bool ist_begleiter(std::string_view klein) {
    return in_liste(klein, BEGLEITER.data(), BEGLEITER.size());
}

/// Der Wert einer Kardinalzahl, oder falsch. Gerechnet, nicht nachgeschlagen:
/// `<einer>und<zehner>` wird zerlegt, damit ein Wort, das heute noch nicht gebraucht
/// wird, morgen trotzdem erkannt ist.
bool kardinalwert(std::string_view wort, std::size_t& wert) {
    const std::string k = klein_geschrieben(wort);
    for (std::size_t i = 0; i < GRUNDZAHL.size(); ++i) {
        if (k == GRUNDZAHL[i]) {
            wert = i;
            return true;
        }
    }
    if (ist_mehrdeutig(k)) {
        wert = 1;
        return true;
    }
    for (std::size_t i = 0; i < ZEHNER.size(); ++i) {
        if (k == ZEHNER[i]) {
            wert = 20 + i * 10;
            return true;
        }
    }
    const std::size_t fuge = k.find("und");
    if (fuge == std::string::npos || fuge == 0) {
        return false;
    }
    const std::string links = k.substr(0, fuge);
    const std::string rechts = k.substr(fuge + 3);
    for (std::size_t e = 1; e < EINERFORM.size(); ++e) {
        if (links != EINERFORM[e]) {
            continue;
        }
        for (std::size_t i = 0; i < ZEHNER.size(); ++i) {
            if (rechts == ZEHNER[i]) {
                wert = 20 + i * 10 + e;
                return true;
            }
        }
    }
    return false;
}

/// Der Wert einer Ordnungszahl, oder falsch. Erst die Beugung abstreifen
/// (`zweiten` -> `zweite`), dann die Unregelmaessigen, dann die Bildungsregel:
/// `...ste` und `...te` fuehren auf den Kardinalstamm zurueck.
bool ordnungswert(std::string_view wort, std::size_t& wert) {
    std::string k = klein_geschrieben(wort);
    if (k.size() >= 3) {
        const char letzt = k[k.size() - 1];
        if (letzt == 'n' || letzt == 'r' || letzt == 's' || letzt == 'm') {
            const std::string ohne = k.substr(0, k.size() - 1);
            if (endet_auf(ohne, "e")) {
                k = ohne;
            }
        }
    }
    for (std::size_t i = 0; i < ORDNUNG_UNREGELMAESSIG.size(); ++i) {
        if (k == ORDNUNG_UNREGELMAESSIG[i].wort) {
            wert = ORDNUNG_UNREGELMAESSIG[i].wert;
            return true;
        }
    }
    if (endet_auf(k, "ste") && kardinalwert(k.substr(0, k.size() - 3), wert)) {
        return true;
    }
    if (endet_auf(k, "te") && kardinalwert(k.substr(0, k.size() - 2), wert)) {
        return true;
    }
    return false;
}

/// Ein Beiwort in beugender Stellung -- das, was zwischen Zahlwort und Nomen stehen
/// darf. Kleingeschrieben, rein alphabetisch, mit einer der fuenf Beugungsendungen,
/// und weder Zahlwort noch Begleiter.
bool ist_beiwort(std::string_view wort) {
    if (wort.size() < 4 || !ist_klein(wort[0])) {
        return false;
    }
    for (std::size_t i = 0; i < wort.size(); ++i) {
        if (!ist_buchstabe(wort[i])) {
            return false;
        }
    }
    const std::string k = klein_geschrieben(wort);
    if (ist_begleiter(k)) {
        return false;
    }
    std::size_t egal = 0;
    if (kardinalwert(k, egal) || ordnungswert(k, egal)) {
        return false;
    }
    return endet_auf(k, "en") || endet_auf(k, "er") || endet_auf(k, "es")
           || endet_auf(k, "em") || endet_auf(k, "e");
}

// ---------------------------------------------------------------------------
// Die Zerlegung in Woerter und Bloecke
// ---------------------------------------------------------------------------

struct Wort {
    std::string text;
    std::size_t zeile;
};

/// Ein Block ist ein Lauf zusammenhaengender Kommentarzeilen, die je mindestens ein
/// Wort tragen. Eine leere Kommentarzeile, eine Strichzeile und jede Codezeile
/// trennen. Warum ueberhaupt ueber Zeilengrenzen zusammengezogen wird: Der Modulkopf
/// bricht "die abgeleiteten / Groessen" mitten in der Wortgruppe um, und eine
/// zeilenweise Suche saehe dort ein Nomen ohne alles davor.
struct Block {
    std::vector<Wort> worte;
};

/// Der Nutztext einer Kommentarzeile. Erkannt werden nur **ganzzeilige** Kommentare --
/// die drei Formen `//!`, `///` und `//`, jeweils nach beliebigem Einzug.
bool kommentartext(std::string_view zeile, std::string& nutz) {
    std::size_t a = 0;
    while (a < zeile.size() && ist_leerraum(zeile[a])) {
        ++a;
    }
    const std::string_view rest = zeile.substr(a);
    if (!beginnt_mit(rest, "//")) {
        return false;
    }
    std::size_t marke = 2;
    if (rest.size() > 2 && (rest[2] == '!' || rest[2] == '/')) {
        marke = 3;
    }
    nutz = std::string(rest.substr(marke));
    return true;
}

/// Woerter sind maximale Laeufe von Buchstaben. Alles andere trennt -- Auszeichnung,
/// Satzzeichen, Klammern, Ziffern. Damit zerfaellt eine fett ausgezeichnete Zahl in
/// ihr blosses Wort und eine Vorgabenkennung in ihren Buchstaben; beides ist gewollt,
/// denn geprueft werden Zahlwoerter und zwei feste Nomen, und keines davon steht je
/// neben einer Ziffer.
void worte_der_zeile(std::string_view nutz, std::size_t zeilennummer,
                     std::vector<Wort>& hinein) {
    std::size_t i = 0;
    while (i < nutz.size()) {
        if (!ist_buchstabe(nutz[i])) {
            ++i;
            continue;
        }
        const std::size_t anfang = i;
        while (i < nutz.size() && ist_buchstabe(nutz[i])) {
            ++i;
        }
        hinein.push_back(Wort{std::string(nutz.substr(anfang, i - anfang)), zeilennummer});
    }
}

std::vector<Block> bloecke_von(std::string_view text) {
    const std::vector<std::string> zeilen = zeilen_von(text);
    std::vector<Block> bloecke;
    Block laufend;
    for (std::size_t i = 0; i < zeilen.size(); ++i) {
        std::string nutz;
        std::vector<Wort> worte;
        if (kommentartext(zeilen[i], nutz)) {
            worte_der_zeile(nutz, i + 1, worte);
        }
        if (worte.empty()) {
            if (!laufend.worte.empty()) {
                bloecke.push_back(laufend);
                laufend.worte.clear();
            }
            continue;
        }
        for (std::size_t w = 0; w < worte.size(); ++w) {
            laufend.worte.push_back(worte[w]);
        }
    }
    if (!laufend.worte.empty()) {
        bloecke.push_back(laufend);
    }
    return bloecke;
}

// ---------------------------------------------------------------------------
// Die Zahlbehauptung an einer Fundstelle
// ---------------------------------------------------------------------------

enum class Art { Keine, Kardinal, Ordnungszahl };

struct Behauptung {
    Art art = Art::Keine;
    std::size_t zahl = 0;
    std::string wort;
};

/// Wie weit vor dem Nomen ein Zahlwort stehen darf. Zwei, und keins mehr: die Stelle
/// unmittelbar davor und die eine dahinter, wenn dazwischen ein Beiwort steht.
constexpr std::size_t FENSTER = 2;

/// Die Behauptung an der Fundstelle `i`, gelesen aus dem, was links davon im selben
/// Block steht.
Behauptung behauptung_an(const std::vector<Wort>& worte, std::size_t i) {
    Behauptung b;
    for (std::size_t abstand = 1; abstand <= FENSTER; ++abstand) {
        if (i < abstand) {
            return b;
        }
        const std::string& kandidat = worte[i - abstand].text;
        std::size_t wert = 0;
        if (ordnungswert(kandidat, wert)) {
            b.art = Art::Ordnungszahl;
            b.zahl = wert;
            b.wort = kandidat;
            return b;
        }
        if (kardinalwert(kandidat, wert)) {
            if (ist_mehrdeutig(klein_geschrieben(kandidat))) {
                // Die tragende Regel. Ohne bestimmten Artikel davor ist `eine` der
                // unbestimmte Artikel und keine Zahl -- und genau diese Stelle steht
                // im Modulkopf, wo eine Kategorie aufgezaehlt wird.
                if (i < abstand + 1
                    || !ist_bestimmter_artikel(worte[i - abstand - 1].text)) {
                    return b;
                }
            }
            b.art = Art::Kardinal;
            b.zahl = wert;
            b.wort = kandidat;
            return b;
        }
        if (abstand < FENSTER && ist_beiwort(kandidat)) {
            continue;
        }
        return b;
    }
    return b;
}

// ---------------------------------------------------------------------------
// Der Schritt vom Behaupteten zum Urteil
// ---------------------------------------------------------------------------

enum class Urteil { Unbeteiligt, Gruen, Rot };

/// Eigener Aufruf und nicht eine Zeile mitten in der Schleife: Bis eine Rolle diesen
/// Schritt herausgezogen hat, liess er sich in zwei verwandten Riegeln dieser Fabrik
/// auf "immer gruen" festnageln, ohne dass ein Fall einer Bausteintabelle riss.
Urteil urteil(const Behauptung& b, std::size_t gezaehlt) {
    if (b.art == Art::Keine) {
        return Urteil::Unbeteiligt;
    }
    if (b.art == Art::Kardinal) {
        return b.zahl == gezaehlt ? Urteil::Gruen : Urteil::Rot;
    }
    // Eine Ordnungszahl sagt nicht, wie viele es sind, sondern dass es mindestens so
    // viele sind.
    return b.zahl <= gezaehlt ? Urteil::Gruen : Urteil::Rot;
}

// ---------------------------------------------------------------------------
// Die beiden Zaehlungen
// ---------------------------------------------------------------------------

struct Feld {
    std::string name;
    std::size_t zeile = 0;
};

struct Zaehlung {
    /// Die verschiedenen Nummern der Tabelle an oeffentlichen Funktionsdeklarationen.
    /// Ein Mengentyp, weil Nr. 11 zweimal vorkommt und einmal zaehlt.
    std::set<std::size_t> nummern;
    std::size_t deklarationen = 0;
    std::vector<Feld> felder;
    std::vector<Feld> jahrgang;
    std::vector<Feld> schluessel;
    /// Was der Zaehlung selbst im Weg steht -- eine Deklaration ohne Nummer, ein Feld
    /// ohne Sorte. Beides ist ein Befund und keine stille Null.
    std::vector<std::string> maengel;
    bool brauchbar = true;
    std::string warum;
};

int klammersaldo(std::string_view zeile) {
    int saldo = 0;
    for (std::size_t i = 0; i < zeile.size(); ++i) {
        if (zeile[i] == '{') {
            ++saldo;
        } else if (zeile[i] == '}') {
            --saldo;
        }
    }
    return saldo;
}

bool ist_kommentarzeile(std::string_view getrimmte) {
    return beginnt_mit(getrimmte, "//");
}

/// Der letzte Bezeichner eines Codestueckes. Rueckwaerts gelesen, weil vorn der Typ
/// steht und der beliebig lang sein darf. Ein reiner Ziffernlauf -- die Null aus
/// `= 0;` -- ist kein Bezeichner und wird uebersprungen.
std::string letzter_bezeichner(std::string_view code) {
    std::size_t i = code.size();
    while (i > 0) {
        while (i > 0 && !ist_buchstabe(code[i - 1]) && code[i - 1] != '_'
               && !ist_ziffer(code[i - 1])) {
            --i;
        }
        if (i == 0) {
            return std::string();
        }
        const std::size_t ende = i;
        while (i > 0
               && (ist_buchstabe(code[i - 1]) || code[i - 1] == '_'
                   || ist_ziffer(code[i - 1]))) {
            --i;
        }
        const std::string_view kandidat = code.substr(i, ende - i);
        if (!kandidat.empty() && !ist_ziffer(kandidat[0])) {
            return std::string(kandidat);
        }
    }
    return std::string();
}

/// Alle Nummern der Tabelle aus einem Kommentarblock in die Menge legen.
void nummern_aus(std::string_view dok, std::set<std::size_t>& hinein,
                 std::size_t& gefunden) {
    std::size_t i = 0;
    while (true) {
        const std::size_t treffer = dok.find(VORSPANN_NUMMER, i);
        if (treffer == std::string_view::npos) {
            return;
        }
        std::size_t j = treffer + VORSPANN_NUMMER.size();
        std::size_t wert = 0;
        std::size_t stellen = 0;
        while (j < dok.size() && ist_ziffer(dok[j])) {
            wert = wert * 10 + static_cast<std::size_t>(dok[j] - '0');
            ++j;
            ++stellen;
        }
        if (stellen > 0) {
            hinein.insert(wert);
            ++gefunden;
        }
        i = j > treffer ? j : treffer + 1;
    }
}

struct Zeilenstueck {
    std::size_t nr;
    std::string text;
};

/// Die Felder des Traegers aus dem Rumpf seiner Anweisung. Ein Feld ist sein
/// Kommentar plus die Zeilen bis zum abschliessenden Strichpunkt; die Sorte liest der
/// Riegel aus dem Kommentar des Feldes und nicht aus einer Liste.
void felder_aus_traeger(const std::vector<Zeilenstueck>& anweisung, Zaehlung& z) {
    std::vector<std::string> puffer;
    std::size_t erste_zeile = 0;
    int tiefe = 0;
    for (std::size_t k = 1; k + 1 < anweisung.size(); ++k) {
        const std::string t = getrimmt(anweisung[k].text);
        if (puffer.empty() && t.empty()) {
            continue;
        }
        if (puffer.empty()) {
            erste_zeile = anweisung[k].nr;
        }
        puffer.push_back(t);
        if (ist_kommentarzeile(t) || t.empty()) {
            continue;
        }
        tiefe += klammersaldo(t);
        if (tiefe > 0 || !endet_auf(t, ";")) {
            continue;
        }
        std::string ganz;
        std::string code;
        for (std::size_t p = 0; p < puffer.size(); ++p) {
            ganz += puffer[p];
            ganz += "\n";
            if (!ist_kommentarzeile(puffer[p])) {
                code += puffer[p];
                code += " ";
            }
        }
        Feld feld;
        feld.name = letzter_bezeichner(code);
        feld.zeile = erste_zeile;
        z.felder.push_back(feld);
        const bool ist_jahrgang = ganz.find(BERUFUNG_JAHRGANG) != std::string::npos;
        const bool ist_schluessel = ganz.find(BERUFUNG_SCHLUESSEL) != std::string::npos;
        if (ist_jahrgang) {
            z.jahrgang.push_back(feld);
        }
        if (ist_schluessel) {
            z.schluessel.push_back(feld);
        }
        // Die zwei Sorten teilen die Felder restlos und ueberschneidungsfrei. Ohne das
        // waere die Zahl unten die einer Teilmenge und nicht die des Traegers -- ein
        // neues Feld ohne Kennzeichnung liesse den Riegel still gruen.
        if (ist_jahrgang == ist_schluessel) {
            std::ostringstream m;
            m << "Feld '" << feld.name << "' ab Zeilennummer " << feld.zeile << " faellt in "
              << (ist_jahrgang ? "beide" : "keine")
              << " der zwei Sorten (Groesse des Jahrgangs nach " << BERUFUNG_JAHRGANG
              << ", Parameterschluessel nach T27)";
            z.maengel.push_back(m.str());
        }
        puffer.clear();
        tiefe = 0;
    }
}

Zaehlung zaehle(std::string_view text) {
    Zaehlung z;
    const std::vector<std::string> zeilen = zeilen_von(text);

    std::size_t start = zeilen.size();
    for (std::size_t i = 0; i < zeilen.size(); ++i) {
        if (beginnt_mit(getrimmt(zeilen[i]), "namespace kern::werte")) {
            start = i;
            break;
        }
    }
    if (start == zeilen.size()) {
        z.brauchbar = false;
        z.warum = "kein Namensraum 'kern::werte' im Pruefling";
        return z;
    }

    std::string dok;
    std::vector<Zeilenstueck> anweisung;
    int tiefe = 0;
    for (std::size_t i = start + 1; i < zeilen.size(); ++i) {
        const std::string t = getrimmt(zeilen[i]);
        if (anweisung.empty()) {
            if (beginnt_mit(t, "///")) {
                dok += t;
                dok += "\n";
                continue;
            }
            if (t.empty() || ist_kommentarzeile(t)) {
                // Ein gewoehnlicher Kommentar und eine Leerzeile beenden den
                // Dokumentationsblock. Was danach kommt, hat ihn nicht mehr.
                dok.clear();
                continue;
            }
            if (beginnt_mit(t, "}") && t.find("namespace") != std::string::npos) {
                break;
            }
        }
        anweisung.push_back(Zeilenstueck{i + 1, zeilen[i]});
        if (ist_kommentarzeile(t) || t.empty()) {
            continue;
        }
        tiefe += klammersaldo(t);
        if (tiefe > 0 || !endet_auf(t, ";")) {
            continue;
        }

        std::string code;
        std::size_t codezeile = 0;
        for (std::size_t k = 0; k < anweisung.size(); ++k) {
            const std::string tk = getrimmt(anweisung[k].text);
            if (ist_kommentarzeile(tk) || tk.empty()) {
                continue;
            }
            if (codezeile == 0) {
                codezeile = anweisung[k].nr;
            }
            code += tk;
            code += " ";
        }

        if (beginnt_mit(code, "struct ")) {
            if (beginnt_mit(code, std::string(TRAEGER) + " ")
                || beginnt_mit(code, std::string(TRAEGER) + "{")) {
                felder_aus_traeger(anweisung, z);
            }
        } else if (code.find('(') != std::string::npos
                   && code.find('{') == std::string::npos) {
            ++z.deklarationen;
            std::size_t gefunden = 0;
            nummern_aus(dok, z.nummern, gefunden);
            if (gefunden == 0) {
                const std::string kopf = code.substr(0, code.find('('));
                std::ostringstream m;
                m << "Funktionsdeklaration '" << letzter_bezeichner(kopf)
                  << "' ab Zeilennummer " << codezeile
                  << " nennt keine Nummer der Tabelle -- sie faellt damit aus der Zaehlung";
                z.maengel.push_back(m.str());
            }
        }

        anweisung.clear();
        dok.clear();
        tiefe = 0;
    }
    return z;
}

// ---------------------------------------------------------------------------
// Die Pruefung -- die Verdrahtung der vier Bausteine
// ---------------------------------------------------------------------------

enum class Sorte { Groessen, Jahrgang, Deklarationen };

std::string_view sortenname(Sorte s) {
    if (s == Sorte::Groessen) {
        return std::string_view("Groessen");
    }
    if (s == Sorte::Jahrgang) {
        return std::string_view("Jahrgangskonstante[n]");
    }
    return std::string_view("Deklarationen");
}

/// Welche der drei Zaehlungen zu einer Sorte gehoert. Ein eigener Aufruf und keine
/// Bedingung mitten in der Schleife: Sorte 1 und Sorte 3 zaehlen **dieselben**
/// Deklarationen, die eine nach Nummern und die andere nach Zeilen. Wer die zwei
/// vertauscht, faellt an keinem Baustein auf -- der Fall dagegen steht in der
/// Verdrahtungstabelle, auf einem Kopf, in dem die beiden Zahlen verschieden sind.
std::size_t zaehlung_zur_sorte(const Zaehlung& z, Sorte s) {
    if (s == Sorte::Groessen) {
        return z.nummern.size();
    }
    if (s == Sorte::Jahrgang) {
        return z.jahrgang.size();
    }
    return z.deklarationen;
}

struct Fundstelle {
    Sorte sorte = Sorte::Groessen;
    std::size_t zeile = 0;
    Behauptung behauptung;
    std::size_t gezaehlt = 0;
    Urteil ergebnis = Urteil::Unbeteiligt;
};

struct Ergebnis {
    Zaehlung zaehlung;
    std::vector<Fundstelle> funde;
    std::vector<std::string> befunde;
    std::size_t behauptungen_groessen = 0;
    std::size_t behauptungen_jahrgang = 0;
    std::size_t behauptungen_deklarationen = 0;
};

bool ist_nomen(std::string_view wort, Sorte& sorte) {
    if (wort == "Groessen") {
        sorte = Sorte::Groessen;
        return true;
    }
    if (wort == "Jahrgangskonstante" || wort == "Jahrgangskonstanten") {
        sorte = Sorte::Jahrgang;
        return true;
    }
    if (wort == "Deklarationen") {
        sorte = Sorte::Deklarationen;
        return true;
    }
    return false;
}

Ergebnis pruefe(std::string_view text) {
    Ergebnis e;
    e.zaehlung = zaehle(text);
    if (!e.zaehlung.brauchbar) {
        return e;
    }
    const std::vector<Block> bloecke = bloecke_von(text);
    for (std::size_t b = 0; b < bloecke.size(); ++b) {
        const std::vector<Wort>& worte = bloecke[b].worte;
        for (std::size_t i = 0; i < worte.size(); ++i) {
            Sorte sorte = Sorte::Groessen;
            if (!ist_nomen(worte[i].text, sorte)) {
                continue;
            }
            Fundstelle f;
            f.sorte = sorte;
            f.zeile = worte[i].zeile;
            f.behauptung = behauptung_an(worte, i);
            f.gezaehlt = zaehlung_zur_sorte(e.zaehlung, sorte);
            f.ergebnis = urteil(f.behauptung, f.gezaehlt);
            if (f.behauptung.art != Art::Keine) {
                if (sorte == Sorte::Groessen) {
                    ++e.behauptungen_groessen;
                } else if (sorte == Sorte::Jahrgang) {
                    ++e.behauptungen_jahrgang;
                } else {
                    ++e.behauptungen_deklarationen;
                }
            }
            if (f.ergebnis == Urteil::Rot) {
                std::ostringstream m;
                m << "Zeilennummer " << f.zeile << ": '" << f.behauptung.wort << " "
                  << sortenname(sorte) << "' nennt " << f.behauptung.zahl
                  << ", gezaehlt sind " << f.gezaehlt;
                e.befunde.push_back(m.str());
            }
            e.funde.push_back(f);
        }
    }
    for (std::size_t m = 0; m < e.zaehlung.maengel.size(); ++m) {
        e.befunde.push_back(e.zaehlung.maengel[m]);
    }
    return e;
}

// ---------------------------------------------------------------------------
// Der Mutant und die Empfindlichkeitsprobe
// ---------------------------------------------------------------------------

/// Der eine Mutant dieses Riegels: **eine weitere Deklaration unter einer vorhandenen
/// Nummer**, eingesetzt unmittelbar vor dem Ende des Namensraums.
///
/// Die Nummer kommt als Argument und steht nicht hier: Eine eingebaute Nummer waere
/// wieder die Handnachfuehrung, gegen die dieses Programm antritt, und eine fremde
/// Nummer bewegte die falsche Zaehlung -- der Mutant soll die Nummernmenge gerade
/// **nicht** vergroessern. Der eingesetzte Kommentar traegt keines der drei Nomen;
/// sonst brachte der Mutant eine Fundstelle mit, die er selbst gestellt hat.
///
/// Gebildet wird nur eine Zeichenkette. `werte.hpp` wird von diesem Programm gelesen
/// und nie geschrieben.
bool mit_weiterer_stelligkeit(std::string_view text, std::size_t nummer,
                              std::string& hinein, std::string& warum) {
    const std::vector<std::string> zeilen = zeilen_von(text);
    std::size_t start = zeilen.size();
    for (std::size_t i = 0; i < zeilen.size(); ++i) {
        if (beginnt_mit(getrimmt(zeilen[i]), "namespace kern::werte")) {
            start = i;
            break;
        }
    }
    if (start == zeilen.size()) {
        warum = "kein Namensraum 'kern::werte' -- der Mutant hat keine Stelle";
        return false;
    }
    std::size_t schluss = zeilen.size();
    for (std::size_t i = start + 1; i < zeilen.size(); ++i) {
        const std::string t = getrimmt(zeilen[i]);
        if (beginnt_mit(t, "}") && t.find("namespace") != std::string::npos) {
            schluss = i;
            break;
        }
    }
    if (schluss == zeilen.size()) {
        warum = "der Namensraum 'kern::werte' wird nicht geschlossen";
        return false;
    }
    std::ostringstream aus;
    for (std::size_t i = 0; i < zeilen.size(); ++i) {
        if (i == schluss) {
            aus << "\n/// **" << VORSPANN_NUMMER << nummer
                << ", weitere Fassung** -- eingesetzt vom Riegel selbst.\n"
                << "[[nodiscard]] int weitere_fassung(int wert);\n\n";
        }
        aus << zeilen[i] << "\n";
    }
    hinein = aus.str();
    return true;
}

std::size_t rot_der_sorte(const Ergebnis& e, Sorte s) {
    std::size_t rot = 0;
    for (std::size_t i = 0; i < e.funde.size(); ++i) {
        if (e.funde[i].sorte == s && e.funde[i].ergebnis == Urteil::Rot) {
            ++rot;
        }
    }
    return rot;
}

struct Probe {
    bool bestanden = false;
    std::string warum;
    std::size_t deklarationen_vorher = 0;
    std::size_t deklarationen_nachher = 0;
    std::size_t rot_vorher = 0;
    std::size_t rot_nachher = 0;
};

/// Zeigen, dass der Riegel rot werden **kann**, und zwar an der Sorte, um die es geht.
/// Jede Bedingung sagt einzeln, was sie ausschliesst -- "der Mutant war rot" allein
/// hiesse noch nicht, dass er aus dem gemeinten Grund rot war. Der Mutant darf genau
/// eine Zahl bewegen und muss genau eine Sorte reissen.
Probe empfindlichkeitsprobe(std::string_view text, const Ergebnis& bestand) {
    Probe p;
    p.deklarationen_vorher = bestand.zaehlung.deklarationen;
    p.rot_vorher = rot_der_sorte(bestand, Sorte::Deklarationen);
    if (bestand.zaehlung.nummern.empty()) {
        p.warum = "keine Nummer der Tabelle, unter die der Mutant eine Deklaration "
                  "setzen koennte";
        return p;
    }
    const std::size_t nummer = *bestand.zaehlung.nummern.begin();
    std::string mutant;
    if (!mit_weiterer_stelligkeit(text, nummer, mutant, p.warum)) {
        return p;
    }
    const Ergebnis nach = pruefe(mutant);
    p.deklarationen_nachher = nach.zaehlung.deklarationen;
    p.rot_nachher = rot_der_sorte(nach, Sorte::Deklarationen);
    if (!nach.zaehlung.brauchbar) {
        p.warum = "der Mutant ist unbrauchbar: " + nach.zaehlung.warum;
        return p;
    }
    if (nach.zaehlung.nummern.size() != bestand.zaehlung.nummern.size()) {
        p.warum = "der Mutant hat die Nummernmenge veraendert -- dann misst er nicht die "
                  "Drift, gegen die Sorte 3 gebaut ist";
        return p;
    }
    if (p.deklarationen_nachher != p.deklarationen_vorher + 1) {
        p.warum = "der Mutant zaehlt nicht genau eine Deklaration mehr -- die eingesetzte "
                  "Zeile wird nicht als Deklaration gelesen";
        return p;
    }
    if (nach.zaehlung.maengel.size() != bestand.zaehlung.maengel.size()) {
        p.warum = "der Mutant bringt einen eigenen Mangel mit -- dann steht der Befund "
                  "unten fuer ihn und nicht fuer die Zahl";
        return p;
    }
    if (rot_der_sorte(nach, Sorte::Groessen) != rot_der_sorte(bestand, Sorte::Groessen)
        || rot_der_sorte(nach, Sorte::Jahrgang) != rot_der_sorte(bestand, Sorte::Jahrgang)) {
        p.warum = "der Mutant bewegt auch Sorte 1 oder Sorte 2 -- dann trennt der Riegel "
                  "die Zahlen eines Satzes nicht";
        return p;
    }
    if (p.rot_nachher <= p.rot_vorher) {
        p.warum = "der Mutant bleibt an Sorte 3 gruen -- der Riegel liest das Zahlwort "
                  "vor 'Deklarationen' nicht oder haelt es gegen die falsche Zaehlung";
        return p;
    }
    p.bestanden = true;
    return p;
}

// ---------------------------------------------------------------------------
// Selbsttest, Tabelle 1: die Zerlegung in Woerter und Bloecke
// ---------------------------------------------------------------------------

struct Blockfall {
    std::string_view text;
    std::string_view erwartet;
    std::string_view was;
};

/// Bloecke durch einen senkrechten Strich getrennt, Woerter durch Leerzeichen, jedes
/// Wort mit seiner Zeilennummer hinter einem `@`. Die Zeilennummer gehoert in die
/// erwartete Zeichenkette und nicht daneben: Sie ist das, was in jeder Meldung landet.
std::string blockbild(std::string_view text) {
    const std::vector<Block> bloecke = bloecke_von(text);
    std::ostringstream aus;
    for (std::size_t b = 0; b < bloecke.size(); ++b) {
        if (b > 0) {
            aus << " | ";
        }
        for (std::size_t i = 0; i < bloecke[b].worte.size(); ++i) {
            if (i > 0) {
                aus << " ";
            }
            aus << bloecke[b].worte[i].text << "@" << bloecke[b].worte[i].zeile;
        }
    }
    return aus.str();
}

constexpr std::array<Blockfall, 9> BLOCKFAELLE = {
    Blockfall{"//! die zwei X\n", "die@1 zwei@1 X@1", "die einfachste Kommentarform"},
    Blockfall{"//! die zwei\n//! X\n", "die@1 zwei@1 X@2",
              "ueber den Zeilenumbruch hinweg zusammengezogen"},
    Blockfall{"//! die zwei\n//!\n//! X\n", "die@1 zwei@1 | X@3",
              "die leere Kommentarzeile trennt zwei Bloecke"},
    Blockfall{"//! die zwei\nint f();\n//! X\n", "die@1 zwei@1 | X@3",
              "eine Codezeile trennt zwei Bloecke"},
    Blockfall{"/// **die** `zwei` X\n", "die@1 zwei@1 X@1", "Auszeichnung faellt weg"},
    Blockfall{"// ---------\n// X\n", "X@2", "eine Strichzeile traegt kein Wort"},
    Blockfall{"    /// eingerueckt X\n", "eingerueckt@1 X@1", "Einzug vor der Marke"},
    Blockfall{"//! T48 Nr. 22 X\n", "T@1 Nr@1 X@1",
              "Ziffern trennen wie jedes Satzzeichen"},
    Blockfall{"int i = 0;  // die zwei X\n", "",
              "die benannte Grenze: ein Kommentar hinter Code wird nicht gelesen"}};

std::size_t selbsttest_bloecke() {
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < BLOCKFAELLE.size(); ++i) {
        const std::string ist = blockbild(BLOCKFAELLE[i].text);
        if (ist == BLOCKFAELLE[i].erwartet) {
            continue;
        }
        ++verfehlt;
        std::fprintf(stderr,
                     "Selbsttest Bloecke, Fall %zu (%s):\n  erwartet [%s]\n  gefunden [%s]\n",
                     i + 1, std::string(BLOCKFAELLE[i].was).c_str(),
                     std::string(BLOCKFAELLE[i].erwartet).c_str(), ist.c_str());
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Selbsttest, Tabelle 2: was eine Zahlbehauptung ist
// ---------------------------------------------------------------------------

struct Behauptungsfall {
    std::string_view satz;
    /// An welchem der Nomen gelesen wird. Die Sorte steht seit 0194 im Fall und nicht
    /// mehr in der Suche: Ein Satz kann zwei Nomen tragen -- "Zweiundzwanzig Groessen
    /// in dreiundzwanzig Deklarationen" ist der Bestandsfall --, und dann ist "das
    /// letzte Nomen" keine Angabe, sondern ein Zufall der Wortstellung.
    Sorte an;
    std::string_view erwartet;
    std::string_view was;
};

std::string behauptungsbild(std::string_view satz, Sorte an) {
    std::vector<Wort> worte;
    worte_der_zeile(satz, 1, worte);
    std::size_t stelle = worte.size();
    for (std::size_t i = 0; i < worte.size(); ++i) {
        Sorte gefunden = Sorte::Groessen;
        if (ist_nomen(worte[i].text, gefunden) && gefunden == an) {
            stelle = i;
        }
    }
    if (stelle == worte.size()) {
        return std::string("kein Nomen der Sorte ") + std::string(sortenname(an));
    }
    const Behauptung b = behauptung_an(worte, stelle);
    std::ostringstream aus;
    if (b.art == Art::Keine) {
        aus << "keine";
    } else if (b.art == Art::Kardinal) {
        aus << "kardinal " << b.zahl;
    } else {
        aus << "ordnung " << b.zahl;
    }
    return aus.str();
}

constexpr std::array<Behauptungsfall, 20> BEHAUPTUNGSFAELLE = {
    Behauptungsfall{"die zwei Jahrgangskonstanten", Sorte::Jahrgang, "kardinal 2",
                    "der heutige Wortlaut des Traegerkopfes"},
    Behauptungsfall{"die eine Jahrgangskonstante", Sorte::Jahrgang, "kardinal 1",
                    "der Wortlaut vor 0155 -- der Artikel macht aus dem Begleiter eine Zahl"},
    Behauptungsfall{"noch eine Jahrgangskonstante noch", Sorte::Jahrgang, "keine",
                    "die Kategorienzeile des Modulkopfes: unbestimmter Artikel, keine Zahl"},
    Behauptungsfall{"Die zweite Jahrgangskonstante dieses Traegers", Sorte::Jahrgang,
                    "ordnung 2",
                    "eine Ordnungszahl sagt nicht wie viele, sondern mindestens wie viele"},
    Behauptungsfall{"die dritte Jahrgangskonstante", Sorte::Jahrgang, "ordnung 3",
                    "Ordnungszahl, unregelmaessig gebildet"},
    Behauptungsfall{"die letzte Jahrgangskonstante", Sorte::Jahrgang, "keine",
                    "was auf -te endet, ist nicht schon eine Ordnungszahl"},
    Behauptungsfall{"die zweiundzwanzig abgeleiteten Groessen", Sorte::Groessen,
                    "kardinal 22",
                    "die erste Zeile der Datei -- ein Beiwort steht dazwischen"},
    Behauptungsfall{"die abgeleiteten Groessen", Sorte::Groessen, "keine",
                    "Beiwort ohne Zahlwort dahinter"},
    Behauptungsfall{"vier Zeilen und keine Groessen", Sorte::Groessen, "keine",
                    "der Bestandsfall, an dem ein weiteres Fenster falsch griffe"},
    Behauptungsfall{"eine der zweiundzwanzig Groessen hier", Sorte::Groessen, "kardinal 22",
                    "Zahlwort unmittelbar davor, Begleiter weiter links"},
    Behauptungsfall{"Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen",
                    Sorte::Groessen, "kardinal 22",
                    "am Blockanfang steht kein Wort davor, und das ist keine Ausrede"},
    Behauptungsfall{"Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen",
                    Sorte::Deklarationen, "kardinal 23",
                    "dieselbe Zeile 32, die andere Haelfte -- die Zahl, die bis 0194 "
                    "niemand hielt"},
    Behauptungsfall{"die oeffentlichen Deklarationen dieses Kopfes", Sorte::Deklarationen,
                    "keine",
                    "die zweite Bestandsstelle (Zeile 25): Beiwort, aber kein Zahlwort "
                    "davor -- sie muss stumm bleiben, sonst ist Sorte 3 ein Dauerbefund"},
    Behauptungsfall{"Groessen", Sorte::Groessen, "keine", "nichts davor"},
    Behauptungsfall{"die zwei und Groessen", Sorte::Groessen, "keine",
                    "was kein Beiwort ist, wird nicht uebersprungen"},
    Behauptungsfall{"der zweiundzwanzigsten Groessen", Sorte::Groessen, "ordnung 22",
                    "gebeugte Ordnungszahl, aus dem Kardinalstamm gerechnet"},
    Behauptungsfall{"die dreiundzwanzig Groessen", Sorte::Groessen, "kardinal 23",
                    "das naechste Zahlwort steht in keiner Liste und wird trotzdem erkannt"},
    Behauptungsfall{"die siebenundvierzig Groessen", Sorte::Groessen, "kardinal 47",
                    "und das uebernaechste auch"},
    Behauptungsfall{"eine abgeleitete Groessen", Sorte::Groessen, "keine",
                    "mehrdeutige Form ueber ein Beiwort hinweg, ohne Artikel davor"},
    Behauptungsfall{"die eine abgeleitete Groessen", Sorte::Groessen, "kardinal 1",
                    "dieselbe Stelle mit Artikel"}};

std::size_t selbsttest_behauptung() {
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < BEHAUPTUNGSFAELLE.size(); ++i) {
        const std::string ist =
            behauptungsbild(BEHAUPTUNGSFAELLE[i].satz, BEHAUPTUNGSFAELLE[i].an);
        if (ist == BEHAUPTUNGSFAELLE[i].erwartet) {
            continue;
        }
        ++verfehlt;
        // Die Sorte gehoert in die Meldung: Zwei Faelle tragen denselben Satz und lesen
        // ihn an verschiedenen Nomen. Ohne sie waere nicht zu sehen, welcher riss.
        std::fprintf(stderr,
                     "Selbsttest Behauptung, Fall %zu (%s):\n  Satz     [%s]\n"
                     "  gelesen an [%s]\n  erwartet [%s]\n  gefunden [%s]\n",
                     i + 1, std::string(BEHAUPTUNGSFAELLE[i].was).c_str(),
                     std::string(BEHAUPTUNGSFAELLE[i].satz).c_str(),
                     std::string(sortenname(BEHAUPTUNGSFAELLE[i].an)).c_str(),
                     std::string(BEHAUPTUNGSFAELLE[i].erwartet).c_str(), ist.c_str());
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Selbsttest, Tabelle 3: der Schritt zum Urteil
// ---------------------------------------------------------------------------

struct Urteilsfall {
    Art art;
    std::size_t genannt;
    std::size_t gezaehlt;
    Urteil erwartet;
    std::string_view was;
};

constexpr std::array<Urteilsfall, 8> URTEILSFAELLE = {
    Urteilsfall{Art::Kardinal, 2, 2, Urteil::Gruen, "Kardinalzahl trifft"},
    Urteilsfall{Art::Kardinal, 1, 2, Urteil::Rot, "der Stand vor 0155"},
    Urteilsfall{Art::Kardinal, 3, 2, Urteil::Rot, "Kardinalzahl zu gross"},
    Urteilsfall{Art::Kardinal, 22, 22, Urteil::Gruen, "der heutige Stand von Sorte 1"},
    Urteilsfall{Art::Ordnungszahl, 2, 2, Urteil::Gruen, "Ordnungszahl genau am Rand"},
    Urteilsfall{Art::Ordnungszahl, 1, 2, Urteil::Gruen, "Ordnungszahl darunter"},
    Urteilsfall{Art::Ordnungszahl, 3, 2, Urteil::Rot, "Ordnungszahl jenseits der Zaehlung"},
    Urteilsfall{Art::Keine, 0, 2, Urteil::Unbeteiligt, "keine Behauptung, kein Urteil"}};

std::size_t selbsttest_urteil() {
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < URTEILSFAELLE.size(); ++i) {
        Behauptung b;
        b.art = URTEILSFAELLE[i].art;
        b.zahl = URTEILSFAELLE[i].genannt;
        const Urteil ist = urteil(b, URTEILSFAELLE[i].gezaehlt);
        if (ist == URTEILSFAELLE[i].erwartet) {
            continue;
        }
        ++verfehlt;
        std::fprintf(stderr, "Selbsttest Urteil, Fall %zu (%s): genannt %zu, gezaehlt %zu\n",
                     i + 1, std::string(URTEILSFAELLE[i].was).c_str(),
                     URTEILSFAELLE[i].genannt, URTEILSFAELLE[i].gezaehlt);
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Selbsttest, Tabelle 4: die beiden Zaehlungen
// ---------------------------------------------------------------------------

struct Zaehlfall {
    std::string_view text;
    std::string_view erwartet;
    std::string_view was;
};

std::string zaehlbild(std::string_view text) {
    const Zaehlung z = zaehle(text);
    if (!z.brauchbar) {
        return std::string("unbrauchbar: ") + z.warum;
    }
    std::ostringstream aus;
    aus << "nummern=" << z.nummern.size() << " dekl=" << z.deklarationen
        << " felder=" << z.felder.size() << " jahrgang=" << z.jahrgang.size()
        << " schluessel=" << z.schluessel.size() << " maengel=" << z.maengel.size();
    return aus.str();
}

constexpr std::string_view ZAEHLTEXT_EINFACH =
    "namespace kern::werte {\n"
    "struct Konstanten {\n"
    "    /// Schluessel `stufenweite` -- T5 Klasse 4.\n"
    "    i64 stufenweite = 0;\n"
    "\n"
    "    /// Eine Groesse des Jahrgangs nach T23 Punkt 5.\n"
    "    i64 leitzins_start = 0;\n"
    "};\n"
    "\n"
    "/// **T48 Nr. 1** -- die erste.\n"
    "[[nodiscard]] i64 wert(const Zustand& z);\n"
    "\n"
    "/// **T48 Nr. 2** -- die zweite.\n"
    "[[nodiscard]] i64 korbwert(const Zustand& z);\n"
    "\n"
    "}  // namespace kern::werte\n";

constexpr std::string_view ZAEHLTEXT_ZWEI_STELLIGKEITEN =
    "namespace kern::werte {\n"
    "/// **T48 Nr. 11, zweistellig** -- die eine.\n"
    "[[nodiscard]] i64 handelsvolumen(const Zustand& z, Sektor s);\n"
    "\n"
    "/// **T48 Nr. 11, einstellig** -- die andere.\n"
    "[[nodiscard]] i64 handelsvolumen(const Zustand& z);\n"
    "}  // namespace kern::werte\n";

constexpr std::string_view ZAEHLTEXT_OHNE_NUMMER =
    "namespace kern::werte {\n"
    "/// Eine Deklaration, deren Kommentar keine Nummer nennt.\n"
    "[[nodiscard]] i64 wert(const Zustand& z);\n"
    "}  // namespace kern::werte\n";

constexpr std::string_view ZAEHLTEXT_FELD_OHNE_SORTE =
    "namespace kern::werte {\n"
    "struct Konstanten {\n"
    "    /// Ein Feld, das sich auf gar nichts beruft.\n"
    "    i64 neuling = 0;\n"
    "};\n"
    "/// **T48 Nr. 1** -- damit die Nummernzaehlung nicht leer bleibt.\n"
    "[[nodiscard]] i64 wert(const Zustand& z);\n"
    "}  // namespace kern::werte\n";

constexpr std::string_view ZAEHLTEXT_MEHRZEILIG =
    "namespace kern::werte {\n"
    "struct Konstanten {\n"
    "    /// Der Preisdurchgriff -- nach T23 Punkt 5 eine Groesse des Jahrgangs.\n"
    "    std::array<std::array<i64, SEKTOREN_HANDELBAR>, GEBIETE>\n"
    "        durchgriff{};\n"
    "};\n"
    "\n"
    "/// **T48 Nr. 22** -- die Schadensvorschrift.\n"
    "[[nodiscard]] i64 schaden(const Zustand& z,\n"
    "                          const Schreiber& rundenschreiber,\n"
    "                          Gebiet land);\n"
    "}  // namespace kern::werte\n";

constexpr std::string_view ZAEHLTEXT_NUMMER_IM_FELD =
    "namespace kern::werte {\n"
    "struct Konstanten {\n"
    "    /// Schluessel `regulierung_last` -- gelesen von T48 Nr. 22.\n"
    "    i64 regulierung_last = 0;\n"
    "};\n"
    "\n"
    "/// **T48 Nr. 1** -- die einzige Deklaration.\n"
    "[[nodiscard]] i64 wert(const Zustand& z);\n"
    "}  // namespace kern::werte\n";

constexpr std::array<Zaehlfall, 7> ZAEHLFAELLE = {
    Zaehlfall{ZAEHLTEXT_EINFACH,
              "nummern=2 dekl=2 felder=2 jahrgang=1 schluessel=1 maengel=0",
              "zwei Nummern, zwei Felder, jede Sorte einmal"},
    Zaehlfall{ZAEHLTEXT_ZWEI_STELLIGKEITEN,
              "nummern=1 dekl=2 felder=0 jahrgang=0 schluessel=0 maengel=0",
              "gezaehlt werden Nummern und nicht Zeilen -- Nr. 11 traegt zwei Stelligkeiten"},
    Zaehlfall{ZAEHLTEXT_OHNE_NUMMER,
              "nummern=0 dekl=1 felder=0 jahrgang=0 schluessel=0 maengel=1",
              "eine Deklaration ohne Nummer faellt aus der Zaehlung und ist deshalb ein Mangel"},
    Zaehlfall{ZAEHLTEXT_FELD_OHNE_SORTE,
              "nummern=1 dekl=1 felder=1 jahrgang=0 schluessel=0 maengel=1",
              "ein Feld ohne Berufung faellt aus der Zaehlung und ist deshalb ein Mangel"},
    Zaehlfall{ZAEHLTEXT_MEHRZEILIG,
              "nummern=1 dekl=1 felder=1 jahrgang=1 schluessel=0 maengel=0",
              "ein Feld und eine Deklaration ueber mehrere Zeilen"},
    Zaehlfall{ZAEHLTEXT_NUMMER_IM_FELD,
              "nummern=1 dekl=1 felder=1 jahrgang=0 schluessel=1 maengel=0",
              "eine Nummer im Feldkommentar hebt die Nummernzaehlung nicht"},
    Zaehlfall{"struct Konstanten {\n};\n",
              "unbrauchbar: kein Namensraum 'kern::werte' im Pruefling",
              "ohne Namensraum hat der Riegel keinen Gegenstand"}};

std::size_t selbsttest_zaehlung() {
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < ZAEHLFAELLE.size(); ++i) {
        const std::string ist = zaehlbild(ZAEHLFAELLE[i].text);
        if (ist == ZAEHLFAELLE[i].erwartet) {
            continue;
        }
        ++verfehlt;
        std::fprintf(stderr,
                     "Selbsttest Zaehlung, Fall %zu (%s):\n  erwartet [%s]\n  gefunden [%s]\n",
                     i + 1, std::string(ZAEHLFAELLE[i].was).c_str(),
                     std::string(ZAEHLFAELLE[i].erwartet).c_str(), ist.c_str());
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Selbsttest, Tabelle 5: die Verdrahtung
// ---------------------------------------------------------------------------
//
// Die vier Tabellen darueber rufen je einen Baustein unmittelbar auf. Keine von ihnen
// kommt an den Schritt heran, der die Zaehlung an die Fundstelle bindet -- und genau
// dort sass in zwei verwandten Riegeln dieser Fabrik die Luecke, die sich auf "immer
// gruen" festnageln liess, ohne dass ein Fall riss. Diese Tabelle geht denselben Weg
// wie der Ernstfall, nur auf Text statt auf einer Datei.

/// Die zwei Koepfe, in die sich der zu pruefende Satz einsetzen laesst.
///
///   * `Schlicht` -- 2 Nummern in 2 Deklarationen, 1 Groesse des Jahrgangs.
///   * `ZweiStelligkeiten` -- 2 Nummern in **3** Deklarationen, 1 Groesse des
///     Jahrgangs. Dieser Kopf ist der Bestand im Kleinen: Nr. 2 traegt zwei
///     Stelligkeiten. Er gehoert hierher, weil im schlichten Kopf die Zaehlung der
///     Nummern und die der Deklarationen **dieselbe Zahl** ergeben -- ein Riegel, der
///     Sorte 3 an die Nummern haengt, bliebe dort gruen.
enum class Kopf { Schlicht, ZweiStelligkeiten };

std::string mit_kopf(std::string_view satz, Kopf art) {
    std::string t = "//! ";
    t += satz;
    t += "\n\n";
    t +=
        "namespace kern::werte {\n"
        "struct Konstanten {\n"
        "    /// Schluessel `stufenweite` -- T5 Klasse 4.\n"
        "    i64 stufenweite = 0;\n"
        "\n"
        "    /// Eine Groesse des Jahrgangs nach T23 Punkt 5.\n"
        "    i64 leitzins_start = 0;\n"
        "};\n"
        "\n"
        "/// **T48 Nr. 1** -- die erste.\n"
        "[[nodiscard]] i64 wert(const Zustand& z);\n"
        "\n";
    if (art == Kopf::Schlicht) {
        t +=
            "/// **T48 Nr. 2** -- die zweite.\n"
            "[[nodiscard]] i64 korbwert(const Zustand& z);\n"
            "\n";
    } else {
        t +=
            "/// **T48 Nr. 2, zweistellig** -- die zweite.\n"
            "[[nodiscard]] i64 korbwert(const Zustand& z, Sektor s);\n"
            "\n"
            "/// **T48 Nr. 2, einstellig** -- ihre Summe, unter derselben Nummer.\n"
            "[[nodiscard]] i64 korbwert(const Zustand& z);\n"
            "\n";
    }
    t += "}  // namespace kern::werte\n";
    return t;
}

std::string pruefbild(std::string_view satz, Kopf art) {
    const Ergebnis e = pruefe(mit_kopf(satz, art));
    std::ostringstream aus;
    aus << "befunde=" << e.befunde.size();
    for (std::size_t i = 0; i < e.befunde.size(); ++i) {
        aus << " [" << e.befunde[i] << "]";
    }
    return aus.str();
}

struct Verdrahtungsfall {
    std::string_view satz;
    Kopf kopf;
    std::string_view erwartet;
    std::string_view was;
};

constexpr std::array<Verdrahtungsfall, 9> VERDRAHTUNGSFAELLE = {
    Verdrahtungsfall{"die zwei Groessen und die eine Jahrgangskonstante", Kopf::Schlicht,
                     "befunde=0", "beide Behauptungen treffen"},
    Verdrahtungsfall{"die drei Groessen", Kopf::Schlicht,
                     "befunde=1 [Zeilennummer 1: 'drei Groessen' nennt 3, gezaehlt sind 2]",
                     "Sorte 1 weicht ab -- die Meldung nennt beide Zahlen und die Zeile"},
    Verdrahtungsfall{
        "die zwei Groessen und die zwei Jahrgangskonstanten", Kopf::Schlicht,
        "befunde=1 [Zeilennummer 1: 'zwei Jahrgangskonstante[n]' nennt 2, gezaehlt sind 1]",
        "Sorte 2 weicht ab, Sorte 1 daneben nicht"},
    Verdrahtungsfall{
        "weder ein Schluessel noch eine Jahrgangskonstante noch eine der zwei Groessen",
        Kopf::Schlicht, "befunde=0",
        "die Kategorienzeile bleibt stumm, die Zahlbehauptung daneben wird geprueft"},
    Verdrahtungsfall{
        "die zwei Groessen und die dritte Jahrgangskonstante", Kopf::Schlicht,
        "befunde=1 [Zeilennummer 1: 'dritte Jahrgangskonstante[n]' nennt 3, gezaehlt sind 1]",
        "eine Ordnungszahl jenseits der Zaehlung ist ein Befund"},
    Verdrahtungsfall{"die zwei Groessen und die erste Jahrgangskonstante", Kopf::Schlicht,
                     "befunde=0", "eine Ordnungszahl innerhalb der Zaehlung ist keiner"},
    // Die drei Faelle von 0194. Sie laufen alle auf dem Kopf mit den zwei
    // Stelligkeiten, weil dort 2 Nummern in 3 Deklarationen stehen -- erst dann sind
    // die beiden Zaehlungen unterscheidbar.
    Verdrahtungsfall{"die zwei Groessen in drei Deklarationen", Kopf::ZweiStelligkeiten,
                     "befunde=0",
                     "der Bestandssatz im Kleinen: zwei Zahlen in einem Satz, beide "
                     "richtig und beide verschieden"},
    Verdrahtungsfall{
        "die drei Groessen in drei Deklarationen", Kopf::ZweiStelligkeiten,
        "befunde=1 [Zeilennummer 1: 'drei Groessen' nennt 3, gezaehlt sind 2]",
        "Sorte 1 zaehlt Nummern und nicht Deklarationen -- wer sie an die Deklarationen "
        "haengt, macht diesen Fall gruen"},
    Verdrahtungsfall{
        "die zwei Groessen in zwei Deklarationen", Kopf::ZweiStelligkeiten,
        "befunde=1 [Zeilennummer 1: 'zwei Deklarationen' nennt 2, gezaehlt sind 3]",
        "und Sorte 3 zaehlt Deklarationen und nicht Nummern -- der Fall, den es vor "
        "0194 nicht gab"}};

std::size_t selbsttest_verdrahtung() {
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < VERDRAHTUNGSFAELLE.size(); ++i) {
        const std::string ist =
            pruefbild(VERDRAHTUNGSFAELLE[i].satz, VERDRAHTUNGSFAELLE[i].kopf);
        if (ist == VERDRAHTUNGSFAELLE[i].erwartet) {
            continue;
        }
        ++verfehlt;
        std::fprintf(stderr,
                     "Selbsttest Verdrahtung, Fall %zu (%s):\n  Satz     [%s]\n"
                     "  im Kopf  [%s]\n  erwartet [%s]\n  gefunden [%s]\n",
                     i + 1, std::string(VERDRAHTUNGSFAELLE[i].was).c_str(),
                     std::string(VERDRAHTUNGSFAELLE[i].satz).c_str(),
                     VERDRAHTUNGSFAELLE[i].kopf == Kopf::Schlicht
                         ? "2 Nummern in 2 Deklarationen"
                         : "2 Nummern in 3 Deklarationen",
                     std::string(VERDRAHTUNGSFAELLE[i].erwartet).c_str(), ist.c_str());
    }
    return verfehlt;
}

}  // namespace

int main(int argc, char** argv) {
    // Der Selbsttest laeuft vor allem anderen und braucht kein Argument. Stimmt eine
    // der fuenf Tabellen nicht, ist jede Zahl weiter unten wertlos.
    const std::size_t verfehlt = selbsttest_bloecke() + selbsttest_behauptung()
                                 + selbsttest_urteil() + selbsttest_zaehlung()
                                 + selbsttest_verdrahtung();
    const std::size_t faelle = BLOCKFAELLE.size() + BEHAUPTUNGSFAELLE.size()
                               + URTEILSFAELLE.size() + ZAEHLFAELLE.size()
                               + VERDRAHTUNGSFAELLE.size();
    if (verfehlt > 0) {
        std::fprintf(stderr,
                     "\nzahlwort_riegel: %zu von %zu Faellen des Selbsttests sind nicht wie "
                     "erwartet\nausgegangen. Der Riegel hat den Pruefling gar nicht erst "
                     "gelesen -- ein Messgeraet,\ndas seine eigenen Faelle verfehlt, misst "
                     "auch fremde nicht.\n",
                     verfehlt, faelle);
        return 2;
    }
    std::fprintf(stdout,
                 "zahlwort_riegel, Selbsttest: %zu Faelle zur Zerlegung, %zu zur "
                 "Zahlbehauptung,\n%zu zum Urteil, %zu zu den Zaehlungen und %zu zur "
                 "Verdrahtung, alle wie erwartet.\n",
                 BLOCKFAELLE.size(), BEHAUPTUNGSFAELLE.size(), URTEILSFAELLE.size(),
                 ZAEHLFAELLE.size(), VERDRAHTUNGSFAELLE.size());

    const std::vector<std::string> argumente(argv, argv + argc);
    const bool bruch =
        argumente.size() == 3 && argumente[2] == std::string(BRUCHSCHALTER);
    if (argumente.size() != 2 && !bruch) {
        std::fprintf(stderr,
                     "Aufruf: zahlwort_riegel <wurzel-des-vorhabens> [%s]\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf einem "
                     "Rechner.\nDer Schalter setzt eine weitere Deklaration unter eine "
                     "vorhandene Nummer der\nTabelle und laesst den Riegel darauf laufen -- "
                     "der Rotnachweis von Hand. Er\nveraendert nur den gelesenen Text im "
                     "Speicher, nie die Datei.\n",
                     std::string(BRUCHSCHALTER).c_str());
        return 2;
    }

    std::error_code fehler;
    const fs::path wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "zahlwort_riegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }
    const fs::path pfad = wurzel / fs::path(std::string(PRUEFLING));
    if (!fs::is_regular_file(pfad, fehler)) {
        std::fprintf(stderr,
                     "zahlwort_riegel: '%s' gibt es nicht. Dieser Riegel prueft genau diese "
                     "eine\nDatei; ohne sie hat er keinen Gegenstand und keinen gruenen "
                     "Lauf.\n",
                     pfad.string().c_str());
        return 2;
    }

    std::ifstream quelle(pfad, std::ios::binary);
    if (!quelle) {
        std::fprintf(stderr, "zahlwort_riegel: '%s' liess sich nicht oeffnen.\n",
                     pfad.string().c_str());
        return 2;
    }
    std::ostringstream aufnahme;
    aufnahme << quelle.rdbuf();
    const std::string text = aufnahme.str();
    if (text.empty()) {
        std::fprintf(stderr, "zahlwort_riegel: '%s' ist leer.\n", pfad.string().c_str());
        return 2;
    }

    // Der Schalter verbiegt die geholte Eingabe an genau dieser einen Stelle. Alles
    // darunter weiss nicht, ob es den Bestand oder den Mutanten liest -- sonst waere
    // der Rotnachweis ein anderer Weg als der Ernstfall und bewiese nichts ueber ihn.
    std::string gelesen(text);
    if (bruch) {
        const Zaehlung vorlauf = zaehle(text);
        if (!vorlauf.brauchbar || vorlauf.nummern.empty()) {
            std::fprintf(stderr,
                         "zahlwort_riegel: der Bestand gibt keine Nummer der Tabelle her, "
                         "unter die der\nSchalter eine Deklaration setzen koennte.\n");
            return 2;
        }
        const std::size_t nummer = *vorlauf.nummern.begin();
        std::string mutant;
        std::string warum;
        if (!mit_weiterer_stelligkeit(text, nummer, mutant, warum)) {
            std::fprintf(stderr, "zahlwort_riegel: %s.\n", warum.c_str());
            return 2;
        }
        gelesen = mutant;
        std::fprintf(stdout,
                     "\n%s: unter %s%zu steht eine weitere Deklaration. Die Nummernzaehlung\n"
                     "bleibt, wo sie war; die Zahl der Deklarationen steigt um eins. Was "
                     "unten steht,\ngilt fuer diesen Mutanten und nicht fuer die Datei.\n",
                     std::string(BRUCHSCHALTER).c_str(),
                     std::string(VORSPANN_NUMMER).c_str(), nummer);
    }

    const Ergebnis e = pruefe(gelesen);
    if (!e.zaehlung.brauchbar) {
        std::fprintf(stderr, "zahlwort_riegel: %s.\n", e.zaehlung.warum.c_str());
        return 2;
    }

    // ------------------------------------------------------------------
    // Die Vorsorge gegen den stillen Ausfall
    // ------------------------------------------------------------------
    if (e.zaehlung.nummern.empty()) {
        std::fprintf(stderr,
                     "zahlwort_riegel: keine einzige Nummer der Tabelle an einer "
                     "Funktionsdeklaration\ngefunden. Das ist ein Befund gegen die Zaehlung "
                     "und keine bestandene Bedingung.\n");
        return 2;
    }
    if (e.zaehlung.felder.empty()) {
        std::fprintf(stderr,
                     "zahlwort_riegel: '%s' traegt keine Felder. Ohne sie ist die zweite "
                     "Zaehlung\nleer, und ein Vergleich gegen null waere kein Vergleich.\n",
                     std::string(TRAEGER).c_str());
        return 2;
    }
    if (e.behauptungen_groessen == 0 || e.behauptungen_jahrgang == 0
        || e.behauptungen_deklarationen == 0) {
        std::fprintf(stderr,
                     "zahlwort_riegel: keine Zahlbehauptung der Sorte %s gefunden. Der "
                     "Riegel haette\ndann nichts zu pruefen und meldete gruen -- das ist "
                     "gegenstandslos und nicht\nbestanden. Entweder liest die Erkennung den "
                     "Wortlaut nicht mehr, dann ist das die\nUrsache, oder der Kopf zaehlt "
                     "nicht mehr. Nur im zweiten Fall wird diese Schranke\ngeaendert, und "
                     "zwar mit Begruendung an ihrer Stelle.\n",
                     e.behauptungen_groessen == 0      ? "Groessen"
                     : e.behauptungen_jahrgang == 0    ? "Jahrgangskonstante[n]"
                                                       : "Deklarationen");
        return 2;
    }

    // ------------------------------------------------------------------
    // Die Empfindlichkeitsprobe
    // ------------------------------------------------------------------
    // Sie laeuft nur am Bestand: Unter dem Schalter ist der gelesene Text schon der
    // Mutant, und ein Mutant des Mutanten bewiese ueber den Bestand nichts.
    if (!bruch) {
        // `gelesen` und nicht `text`: Der Vergleich geht gegen `e`, und `e` ist aus
        // `gelesen` gebildet. Ohne Schalter sind beide dasselbe -- die Probe soll aber
        // auch dann noch stimmen, wenn zwischen Lesen und Pruefen einmal mehr steht.
        const Probe p = empfindlichkeitsprobe(gelesen, e);
        if (!p.bestanden) {
            std::fprintf(stderr,
                         "zahlwort_riegel: die Empfindlichkeitsprobe ist verfehlt -- %s.\n\n"
                         "Der Riegel hat den Bestand gelesen, aber er zeigt nicht mehr, dass "
                         "er rot werden\nkann. Ein Riegel, der nie rot wird, prueft nichts; "
                         "sein gruener Lauf ist deshalb\nhier nichts wert. Gezaehlt wurden "
                         "%zu Deklarationen am Bestand und %zu am\nMutanten, rot an Sorte 3 "
                         "waren %zu und %zu.\n",
                         p.warum.c_str(), p.deklarationen_vorher, p.deklarationen_nachher,
                         p.rot_vorher, p.rot_nachher);
            return 2;
        }
        std::fprintf(stdout,
                     "zahlwort_riegel, Empfindlichkeitsprobe: mit einer weiteren "
                     "Deklaration unter einer\nvorhandenen Nummer zaehlt der Riegel %zu statt "
                     "%zu Deklarationen und meldet %zu statt\n%zu Abweichungen der Sorte "
                     "'Deklarationen' -- die Sorten 1 und 2 bleiben, wie sie\nwaren. Der "
                     "rote Lauf im Wortlaut: %s %s.\n",
                     p.deklarationen_nachher, p.deklarationen_vorher, p.rot_nachher,
                     p.rot_vorher, argumente[1].c_str(),
                     std::string(BRUCHSCHALTER).c_str());
    }

    // ------------------------------------------------------------------
    // Die Ausgabe
    // ------------------------------------------------------------------
    std::fprintf(stdout,
                 "zahlwort_riegel: %s gelesen. %zu Nummern der Tabelle in %zu "
                 "Funktionsdeklarationen;\n%zu Felder in %s, davon %zu Groessen des "
                 "Jahrgangs und %zu Parameterschluessel.\n%zu Fundstellen der drei Nomen, "
                 "davon %zu mit Zahlbehauptung (%zu zu den Groessen,\n%zu zu den "
                 "Jahrgangskonstanten, %zu zu den Deklarationen).\n",
                 std::string(PRUEFLING).c_str(), e.zaehlung.nummern.size(),
                 e.zaehlung.deklarationen, e.zaehlung.felder.size(),
                 std::string(TRAEGER).c_str(), e.zaehlung.jahrgang.size(),
                 e.zaehlung.schluessel.size(), e.funde.size(),
                 e.behauptungen_groessen + e.behauptungen_jahrgang
                     + e.behauptungen_deklarationen,
                 e.behauptungen_groessen, e.behauptungen_jahrgang,
                 e.behauptungen_deklarationen);

    std::fprintf(stdout, "\n  Groessen des Jahrgangs: ");
    for (std::size_t i = 0; i < e.zaehlung.jahrgang.size(); ++i) {
        std::fprintf(stdout, " %s", e.zaehlung.jahrgang[i].name.c_str());
    }
    std::fprintf(stdout, "\n  Parameterschluessel:    ");
    for (std::size_t i = 0; i < e.zaehlung.schluessel.size(); ++i) {
        std::fprintf(stdout, " %s", e.zaehlung.schluessel[i].name.c_str());
    }
    std::fprintf(stdout, "\n");

    std::fprintf(stdout,
                 "\nJede Fundstelle mit ihrem Urteil -- der ausgeschriebene Nachlass dieses "
                 "Riegels.\nGenannt wird auch, was keine Zahl behauptet:\n\n");
    for (std::size_t i = 0; i < e.funde.size(); ++i) {
        const Fundstelle& f = e.funde[i];
        if (f.behauptung.art == Art::Keine) {
            std::fprintf(stdout, "  %5zu  %-22s keine Zahlbehauptung\n", f.zeile,
                         std::string(sortenname(f.sorte)).c_str());
        } else {
            std::fprintf(stdout, "  %5zu  %-22s %s: '%s' nennt %zu, gezaehlt %zu%s\n", f.zeile,
                         std::string(sortenname(f.sorte)).c_str(),
                         f.behauptung.art == Art::Kardinal ? "Kardinalzahl" : "Ordnungszahl",
                         f.behauptung.wort.c_str(), f.behauptung.zahl, f.gezaehlt,
                         f.ergebnis == Urteil::Rot ? "  -- ABWEICHUNG" : "");
        }
    }

    if (e.befunde.empty()) {
        std::fprintf(stdout,
                     "\nKeine Zahl im Kommentar dieser Datei widerspricht dem, was unter ihr "
                     "steht.\n");
        return 0;
    }

    std::fprintf(stderr, "\n%zu Befunde:\n\n", e.befunde.size());
    for (std::size_t i = 0; i < e.befunde.size(); ++i) {
        std::fprintf(stderr, "  %s\n", e.befunde[i].c_str());
    }
    std::fprintf(stderr,
                 "\nEntweder ist unter dem Satz etwas dazugekommen -- dann wird das Zahlwort "
                 "nachgezogen --,\noder der Satz hat nie gestimmt. Beides wird berichtigt und "
                 "nicht ausgenommen. Die\nZahl kommt aus dem Quelltext und nicht aus diesem "
                 "Programm; eine Schwelle, an der\nsich etwas drehen liesse, gibt es hier "
                 "nicht.\n");
    return 1;
}
