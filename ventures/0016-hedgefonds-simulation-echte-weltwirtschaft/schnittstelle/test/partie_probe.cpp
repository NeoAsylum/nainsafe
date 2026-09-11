//! Laufende Probe fuer `schnittstelle::partie` -- Paket 0301.
//!
//! Geprueft wird der Schreiber an **von Hand gebauten** Speicherstaenden. Einen Leser
//! gibt es nicht; er ist das zweite Paket, und seine Prueffaelle sind die Zeilen, die
//! hier entstehen.
//!
//! ## Was jede Pruefung leisten soll
//!
//! Nicht "es kommt eine Zeile heraus", sondern eine Aussage, die falsch werden kann.
//! Der Wortlaut wird deshalb Zeichen fuer Zeichen gegen eine ausgeschriebene Zeile
//! gehalten und nicht nach Teilstuecken durchsucht: Eine Teilstueckssuche bliebe gruen,
//! wenn ein Feld doppelt, an falscher Stelle oder mit Leerraum daneben stuende.
//!
//! Die acht Feldwerte werden dafuer aus der Zeile herausgeschnitten -- an den Namen, die
//! `FELDNAME` fuehrt, und an der festen Reihenfolge. Das ist **kein** Leser: Es loest
//! keine Schachtelung auf, weist keine Fehlform ab und wird von nichts ausser dieser
//! Datei benutzt. Es ist der Weg, "zwei Zeilen unterscheiden sich in genau einem Feld"
//! zu messen, statt es an einer Zeichenposition zu erraten.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer auf
//! der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string_view>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/werte.hpp"
#include "schnittstelle/partie.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::aktion::Aktion;
using kern::aktion::Art;
using kern::aktion::zielkennung;
using kern::aktion::ZIELKENNUNG_MAX;

using kern::festkomma::I64_MIN;

using kern::schreiber::Modus;
using kern::werte::Konstanten;

using schnittstelle::partie::Aktionsfolge;
using schnittstelle::partie::Feld;
using schnittstelle::partie::FELDER;
using schnittstelle::partie::FELDNAME;
using schnittstelle::partie::Partie;
using schnittstelle::partie::PARTIE_ZEICHEN;
using schnittstelle::partie::Partiezeile;
using schnittstelle::partie::schreibe;
using schnittstelle::partie::SCHEMA_VERSION;
using schnittstelle::partie::Zug;
using schnittstelle::partie::ZUEGE_HOECHSTENS;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Ruft `aufruf` und meldet, ob er mit einer Meldung abgebrochen hat, in der beide
/// Textstuecke stehen.
template <typename Aufruf>
[[nodiscard]] bool bricht_ab_mit(Aufruf aufruf, std::string_view erstes,
                                 std::string_view zweites)
{
    try {
        aufruf();
    } catch (const std::domain_error& fehler) {
        const std::string_view wortlaut = fehler.what();
        return wortlaut.find(erstes) != std::string_view::npos
               && wortlaut.find(zweites) != std::string_view::npos;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Der Musterstand und der Schnitt an den Feldnamen
// ---------------------------------------------------------------------------

/// Der Stand, dessen Zeile weiter unten ausgeschrieben dasteht.
///
/// Die Zahlen sind so gewaehlt, dass sie etwas beweisen und nicht bloss passen:
/// `parameter_pruefsumme` ist negativ (das Vorzeichen muss mitreisen), `startwert` ist
/// der groesste `u64` und `end_pruefsumme` liegt oberhalb des groessten `i64` -- beide
/// faenden einen Schreiber, der eine vorzeichenlose Zahl als vorzeichenbehaftete
/// hinausgibt. Die zwei Zuege tragen zwei verschiedene Arten, damit die Kennung 1 bis 5
/// wirklich gelesen wird, und eine negative Stufe.
[[nodiscard]] Partie musterstand()
{
    Partie stand;
    stand.schema_version = SCHEMA_VERSION;
    stand.jahrgang_id = 1997;
    stand.modus = Modus::Weltlauf;
    stand.daten_pruefsumme = 42;
    stand.parameter_pruefsumme = -7;
    stand.startwert = 18446744073709551615ULL;
    stand.end_pruefsumme = 9223372036854775808ULL;
    stand.aktionen.anzahl = 2;
    stand.aktionen.eintraege[0] = Zug{1, Aktion{Art::Position, zielkennung(7), -3}};
    stand.aktionen.eintraege[1] = Zug{2, Aktion{Art::Sichtbarkeit, zielkennung(0), 12}};
    return stand;
}

constexpr const char* ERWARTETE_ZEILE =
    "{\"schema_version\":1"
    ",\"jahrgang_id\":1997"
    ",\"modus\":1"
    ",\"daten_pruefsumme\":42"
    ",\"parameter_pruefsumme\":-7"
    ",\"startwert\":18446744073709551615"
    ",\"aktionen\":[[1,1,7,-3],[2,5,0,12]]"
    ",\"end_pruefsumme\":9223372036854775808}";

/// Der Wert des Feldes auf Platz `platz`, aus der Zeile herausgeschnitten.
///
/// Geschnitten wird zwischen dem Doppelpunkt hinter dem eigenen Namen und dem
/// Trennzeichen vor dem naechsten; beim letzten Feld vor der schliessenden Klammer.
/// Leer heisst: nicht gefunden -- und darauf wird unten eigens geprueft, damit zwei
/// Fehlschlaege nicht als Gleichheit durchgehen.
[[nodiscard]] std::string_view wert_von(std::string_view zeile, std::size_t platz)
{
    if (platz >= FELDER) {
        return {};
    }
    const std::string_view name = FELDNAME[platz];
    const std::size_t treffer = zeile.find(name);
    if (treffer == std::string_view::npos) {
        return {};
    }
    const std::size_t beginn = treffer + name.size() + 2;  // das `":` hinter dem Namen
    std::size_t ende = 0;
    if (platz + 1 < FELDER) {
        const std::string_view naechster = FELDNAME[platz + 1];
        const std::size_t stelle = zeile.find(naechster);
        if (stelle == std::string_view::npos || stelle < beginn + 2) {
            return {};
        }
        ende = stelle - 2;  // das `,"` vor dem naechsten Namen
    } else {
        if (zeile.empty() || zeile.back() != '}') {
            return {};
        }
        ende = zeile.size() - 1;
    }
    if (ende <= beginn) {
        return {};
    }
    return zeile.substr(beginn, ende - beginn);
}

/// Derselbe Stand, aber in genau einem Feld veraendert.
[[nodiscard]] Partie veraendert(const Partie& grund, Feld feld)
{
    Partie stand = grund;
    switch (feld) {
    case Feld::SchemaVersion:
        stand.schema_version = grund.schema_version + 1;
        return stand;
    case Feld::JahrgangId:
        stand.jahrgang_id = grund.jahrgang_id + 1;
        return stand;
    case Feld::Modus:
        stand.modus = Modus::Spielmodus;
        return stand;
    case Feld::DatenPruefsumme:
        stand.daten_pruefsumme = grund.daten_pruefsumme + 1;
        return stand;
    case Feld::ParameterPruefsumme:
        stand.parameter_pruefsumme = grund.parameter_pruefsumme - 1;
        return stand;
    case Feld::Startwert:
        stand.startwert = grund.startwert - 1;
        return stand;
    case Feld::Aktionen:
        stand.aktionen.eintraege[0].aktion.stufe =
            grund.aktionen.eintraege[0].aktion.stufe - 1;
        return stand;
    case Feld::EndPruefsumme:
        stand.end_pruefsumme = grund.end_pruefsumme + 1;
        return stand;
    }
    kern::festkomma::abbruch("partie_probe -- unbekanntes Feld");
}

// ---------------------------------------------------------------------------
// (1) Acht Felder, acht Namen, und keiner fehlt
// ---------------------------------------------------------------------------

void fall_acht_felder()
{
    // Die Aufzaehlung der acht. Sie steht hier ein zweites Mal und absichtlich
    // ausgeschrieben: Wer ein Feld zulegt, ohne diese Liste anzufassen, wird hier rot --
    // und wer es zulegt, ohne `FELDNAME` anzufassen, schon beim Uebersetzen.
    const std::array<const char*, FELDER> erwartet = {
        "schema_version",
        "jahrgang_id",
        "modus",
        "daten_pruefsumme",
        "parameter_pruefsumme",
        "startwert",
        "aktionen",
        "end_pruefsumme"};

    PRUEFE(kern::schritt::feldzahl<Partie> == FELDER);
    PRUEFE(kern::schritt::feldzahl<Aktionsfolge> == std::size_t{2});
    PRUEFE(FELDNAME.size() == FELDER);
    PRUEFE(FELDER == std::size_t{8});

    for (std::size_t platz = 0; platz < FELDER; ++platz) {
        PRUEFE(std::string_view(FELDNAME[platz]) == std::string_view(erwartet[platz]));
        PRUEFE(schnittstelle::partie::feld_des_platzes(platz)
               == static_cast<Feld>(platz));
    }

    // Die Namen stehen in der Zeile in genau dieser Reihenfolge und jeder genau einmal.
    const Partiezeile zeile = schreibe(musterstand());
    const std::string_view text = zeile.fertig();
    std::size_t bisher = 0;
    for (std::size_t platz = 0; platz < FELDER; ++platz) {
        const std::string_view name = FELDNAME[platz];
        const std::size_t treffer = text.find(name);
        PRUEFE(treffer != std::string_view::npos);
        PRUEFE(treffer > bisher);
        PRUEFE(text.find(name, treffer + 1) == std::string_view::npos);
        bisher = treffer;

        // Und jeder Wert laesst sich schneiden -- sonst misst der Fall (3) unten zwei
        // leere Zeichenketten gegeneinander und findet sie gleich.
        PRUEFE(!wert_von(text, platz).empty());
    }

    // Ein Platz jenseits der acht ist ein harter Fehler und kein Ersatzwert.
    PRUEFE(bricht_ab_mit(
        []() { static_cast<void>(schnittstelle::partie::feld_des_platzes(FELDER)); },
        "ausserhalb der acht", "T22"));
}

// ---------------------------------------------------------------------------
// (2) Der Wortlaut, Zeichen fuer Zeichen
// ---------------------------------------------------------------------------

void fall_wortlaut()
{
    const Partiezeile zeile = schreibe(musterstand());
    const std::string_view text = zeile.fertig();
    const std::string_view soll = ERWARTETE_ZEILE;

    PRUEFE(text == soll);
    PRUEFE(zeile.laenge() == soll.size());
    PRUEFE(!zeile.abgeschnitten());

    // Eine Zeile, kein Zeilenumbruch darin und kein Leerraum ausserhalb von
    // Zeichenketten. Geprueft wird am Text und nicht am Zeilenzaehler des Puffers: Der
    // zaehlt nur, was `zeilenende` anhaengt, und das ruft dieser Schreiber nie.
    PRUEFE(zeile.zeilen() == 0);
    PRUEFE(text.find(' ') == std::string_view::npos);
    PRUEFE(text.find('\n') == std::string_view::npos);
    PRUEFE(text.find('\t') == std::string_view::npos);

    // Keine Tausendertrennung: Weder ein Punkt noch ein Hochkomma steht in der Zeile.
    PRUEFE(text.find('.') == std::string_view::npos);
    PRUEFE(text.find('\'') == std::string_view::npos);

    // Die beiden Zahlen, die einen vorzeichenbehafteten Schreiber verraten wuerden.
    PRUEFE(wert_von(text, static_cast<std::size_t>(Feld::Startwert))
           == "18446744073709551615");
    PRUEFE(wert_von(text, static_cast<std::size_t>(Feld::EndPruefsumme))
           == "9223372036854775808");
    PRUEFE(wert_von(text, static_cast<std::size_t>(Feld::ParameterPruefsumme)) == "-7");
    PRUEFE(wert_von(text, static_cast<std::size_t>(Feld::Aktionen))
           == "[[1,1,7,-3],[2,5,0,12]]");
}

// ---------------------------------------------------------------------------
// (3) Zweimal dasselbe gibt dieselben Bytes -- und ein Feld bewegt ein Feld
// ---------------------------------------------------------------------------

void fall_wiederholbar()
{
    const Partie grund = musterstand();
    const Partiezeile erste = schreibe(grund);
    const Partiezeile zweite = schreibe(grund);
    PRUEFE(std::string_view(erste.fertig()) == std::string_view(zweite.fertig()));

    // Und dazwischen ein anderer Stand: Ein Schreiber, der etwas zwischen zwei Aufrufen
    // behaelt, faellt hier auf und an der Zeile darueber nicht.
    static_cast<void>(schreibe(veraendert(grund, Feld::JahrgangId)));
    const Partiezeile dritte = schreibe(grund);
    PRUEFE(std::string_view(erste.fertig()) == std::string_view(dritte.fertig()));
}

void fall_ein_feld_ein_unterschied()
{
    const Partie grund = musterstand();
    const Partiezeile grundzeile = schreibe(grund);
    const std::string_view links = grundzeile.fertig();

    for (std::size_t platz = 0; platz < FELDER; ++platz) {
        const Feld feld = schnittstelle::partie::feld_des_platzes(platz);
        const Partiezeile andere = schreibe(veraendert(grund, feld));
        const std::string_view rechts = andere.fertig();

        PRUEFE(links != rechts);

        std::size_t abweichungen = 0;
        std::size_t wo = FELDER;
        for (std::size_t p = 0; p < FELDER; ++p) {
            const std::string_view hier = wert_von(links, p);
            const std::string_view dort = wert_von(rechts, p);
            PRUEFE(!hier.empty());
            PRUEFE(!dort.empty());
            if (hier != dort) {
                ++abweichungen;
                wo = p;
            }
        }
        PRUEFE(abweichungen == std::size_t{1});
        PRUEFE(wo == platz);
    }
}

// ---------------------------------------------------------------------------
// (4) `parameter_pruefsumme` ist die des Kerns und keine Zahl daneben
// ---------------------------------------------------------------------------

void fall_parameterpruefsumme()
{
    Konstanten konstanten;
    konstanten.stufenweite = 100;
    konstanten.ausstiegsabschlag = 25;
    konstanten.aufschlag = 150;
    konstanten.lobbykosten = 4000;
    konstanten.gegenlobby_satz = 30;
    konstanten.regulierung_last = 12;
    konstanten.zustimmung_elastizitaet = 7;

    const std::int64_t summe = kern::schritt::parameter_pruefsumme(konstanten);

    Partie stand = musterstand();
    stand.parameter_pruefsumme = summe;
    const Partiezeile zeile = schreibe(stand);

    // Verglichen wird gegen dieselbe Zahl, durch dieselbe Zahlenumwandlung geschickt --
    // nicht gegen ein hingeschriebenes Literal. Ein Literal waere die vierte Abschrift
    // einer Summe, die sich mit jedem zugelegten Schluesselfeld bewegt.
    Partiezeile gerechnet;
    gerechnet.zahl(static_cast<kern::festkomma::i128>(summe));
    PRUEFE(wert_von(zeile.fertig(), static_cast<std::size_t>(Feld::ParameterPruefsumme))
           == std::string_view(gerechnet.fertig()));

    // Positivkontrolle: Die Summe ist nicht null, und ein anderer Parametersatz gibt eine
    // andere Zahl. Ohne diese zwei Zeilen bliebe der Vergleich oben auch dann gruen, wenn
    // das Feld mit einer festen Zahl gefuellt waere.
    PRUEFE(summe != 0);

    Konstanten andere = konstanten;
    andere.lobbykosten = konstanten.lobbykosten + 1;
    const std::int64_t zweite = kern::schritt::parameter_pruefsumme(andere);
    PRUEFE(zweite != summe);

    Partie zweiter = musterstand();
    zweiter.parameter_pruefsumme = zweite;
    PRUEFE(std::string_view(schreibe(zweiter).fertig())
           != std::string_view(zeile.fertig()));
}

// ---------------------------------------------------------------------------
// (5) Die leere Folge -- der Speicherstand vor der ersten Runde
// ---------------------------------------------------------------------------

void fall_leere_folge()
{
    Partie stand = musterstand();
    stand.aktionen = Aktionsfolge{};
    PRUEFE(stand.aktionen.anzahl == 0);

    const Partiezeile zeile = schreibe(stand);
    const std::string_view text = zeile.fertig();

    PRUEFE(text.find("\"aktionen\":[]") != std::string_view::npos);
    PRUEFE(wert_von(text, static_cast<std::size_t>(Feld::Aktionen)) == "[]");
    PRUEFE(!zeile.abgeschnitten());

    // Die uebrigen sieben Felder stehen unveraendert da -- eine leere Folge ist ein
    // gueltiger Stand und kein halber.
    const Partiezeile voll = schreibe(musterstand());
    for (std::size_t platz = 0; platz < FELDER; ++platz) {
        if (platz == static_cast<std::size_t>(Feld::Aktionen)) {
            continue;
        }
        PRUEFE(wert_von(text, platz) == wert_von(voll.fertig(), platz));
    }

    // Ein Behaelter voller Zuege, dessen Zahl auf null steht, schreibt trotzdem `[]`:
    // Geschrieben wird die Zahl der belegten Plaetze und nicht der Behaelter.
    Partie getarnt = musterstand();
    getarnt.aktionen.anzahl = 0;
    PRUEFE(wert_von(schreibe(getarnt).fertig(),
                    static_cast<std::size_t>(Feld::Aktionen))
           == "[]");
}

// ---------------------------------------------------------------------------
// (6) Die Kapazitaet, gemessen statt behauptet
// ---------------------------------------------------------------------------

void fall_kapazitaet()
{
    // Die laengste Zeile, die ueberhaupt entstehen kann: jedes Feld an seinem Rand, die
    // Folge voll, und jeder Zug mit der breitesten Zahl in jeder seiner vier Stellen.
    Partie voll;
    voll.schema_version = I64_MIN;
    voll.jahrgang_id = I64_MIN;
    voll.modus = Modus::Weltlauf;
    voll.daten_pruefsumme = 18446744073709551615ULL;
    voll.parameter_pruefsumme = I64_MIN;
    voll.startwert = 18446744073709551615ULL;
    voll.end_pruefsumme = 18446744073709551615ULL;
    voll.aktionen.anzahl = ZUEGE_HOECHSTENS;
    const Aktion breiteste{Art::Sichtbarkeit, zielkennung(ZIELKENNUNG_MAX), I64_MIN};
    for (std::size_t k = 0; k < ZUEGE_HOECHSTENS; ++k) {
        voll.aktionen.eintraege[k] = Zug{I64_MIN, breiteste};
    }

    const Partiezeile zeile = schreibe(voll);
    PRUEFE(!zeile.abgeschnitten());
    PRUEFE(zeile.laenge() < PARTIE_ZEICHEN);

    // Eine untere Schranke, damit ein Schreiber, der die Folge stillschweigend
    // weglaesst, nicht als "passt bequem" durchgeht. 4.000 ist keine Messung, sondern
    // eine Zahl deutlich unterhalb der gerechneten Laenge und deutlich oberhalb jeder
    // Zeile ohne Folge.
    PRUEFE(zeile.laenge() > 4000);

    // Positivkontrolle zur Schranke darunter: die volle Folge ist zulaessig und wurde
    // eben geschrieben. Ein Zug mehr, als der Behaelter fasst, bricht ab.
    Partie zuviel = voll;
    zuviel.aktionen.anzahl = ZUEGE_HOECHSTENS + 1;
    PRUEFE(bricht_ab_mit([&zuviel]() { static_cast<void>(schreibe(zuviel)); },
                         "mehr Zuege angesagt", "T40"));

    std::fprintf(stdout,
                 "partie_probe: die laengste Zeile misst %zu Zeichen bei %zu Zuegen; "
                 "der Puffer fasst %zu.\n",
                 zeile.laenge(), ZUEGE_HOECHSTENS, PARTIE_ZEICHEN);
}

}  // namespace

int main()
{
    fall_acht_felder();
    fall_wortlaut();
    fall_wiederholbar();
    fall_ein_feld_ein_unterschied();
    fall_parameterpruefsumme();
    fall_leere_folge();
    fall_kapazitaet();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "partie_probe: %d Pruefung(en) fehlgeschlagen\n",
                     fehlgeschlagen);
        return 1;
    }
    std::fprintf(stdout,
                 "partie_probe: alle Pruefungen bestanden -- acht Felder nach T22, "
                 "hoechstens %zu Zuege.\n",
                 ZUEGE_HOECHSTENS);
    return 0;
}
