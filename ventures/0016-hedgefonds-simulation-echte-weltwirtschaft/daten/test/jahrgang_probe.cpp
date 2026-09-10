//! Laufende Probe fuer `daten::Jahrgang` -- Paket 0297.
//!
//! Geprueft wird an einem **von Hand gebauten** Jahrgang, nicht an einer geladenen
//! Datei: Das Jahrgangsformat schreibt `werkzeuge/aufbereitung`, und dieses Mitglied ist
//! nicht gebaut. Was hier geprueft wird, ist die Rechnung -- die Abbildung von Runde auf
//! Stuetzstelle, die Klemme am Ende der Reihe und die beiden Schranken aus T23 Punkt 5
//! und T51.
//!
//! ## Wie der Jahrgang gebaut ist, und warum so
//!
//! Jede der sechzig Zahlen ist verschieden, und die drei Ordnungen sind an drei
//! verschiedenen Stellen abzulesen: das Instrument am Tausender, das Land am Hunderter,
//! die Stuetzstelle am Zehner. Ein vertauschter Index gibt damit eine Zahl aus einem
//! anderen Bereich und nicht zufaellig dieselbe. Ein Traeger, der eine Runde lang
//! richtig ist und danach nur vortraegt, faellt an Fall (b) auf: Runde 1 und Runde 3
//! liefern nachweislich verschiedene Zahlen.
//!
//! ## Was jede Pruefung leisten soll
//!
//! Nicht "die Funktion liefert eine Zahl", sondern eine Aussage, die falsch werden kann.
//! Jeder Abbruchpfad steht deshalb mit einer **Positivkontrolle** daneben: derselbe
//! Aufruf mit einer heilen Zahl muss nachweislich gerechnet haben, sonst ist "bricht ab"
//! kein Nachweis. Und jeder gefangene Abbruch wird an einem Textstueck gehalten, das
//! seinen Riegel eindeutig macht -- eine Schranke, die doppelt gehalten wird, kann sonst
//! darunter wegfallen, ohne dass etwas rot wird.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer auf
//! der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdio>
#include <stdexcept>

#include "daten/jahrgang.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using daten::Bereichsbefund;
using daten::Jahrgang;
using daten::Wertebereich;
using daten::Wertebereiche;

using kern::werte::Konstanten;

using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Instrument;
using kern::zustand::LAENDER;
using kern::zustand::PFADINSTRUMENTE;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Teilzeichenkettensuche von Hand -- kein `<cstring>`, weil die Probe damit ohne jede
/// weitere Bindung auskommt und die Suche selbst hier nachzulesen ist.
[[nodiscard]] bool enthaelt(const char* heuhaufen, const char* nadel)
{
    if (heuhaufen == nullptr || nadel == nullptr) {
        return false;
    }
    for (std::size_t a = 0; heuhaufen[a] != '\0'; ++a) {
        std::size_t b = 0;
        while (nadel[b] != '\0' && heuhaufen[a + b] == nadel[b]) {
            ++b;
        }
        if (nadel[b] == '\0') {
            return true;
        }
    }
    return nadel[0] == '\0';
}

/// Ruft `aufruf` und meldet, ob er mit einer Meldung abgebrochen hat, in der beide
/// Textstuecke stehen. `zweites` darf `nullptr` sein.
template <typename Aufruf>
[[nodiscard]] bool bricht_ab_mit(Aufruf aufruf, const char* erstes, const char* zweites)
{
    try {
        aufruf();
    } catch (const std::domain_error& fehler) {
        const char* wortlaut = fehler.what();
        return enthaelt(wortlaut, erstes) && (zweites == nullptr
                                              || enthaelt(wortlaut, zweites));
    }
    return false;
}

// ---------------------------------------------------------------------------
// Der Jahrgang von Hand
// ---------------------------------------------------------------------------

constexpr std::size_t STUETZSTELLEN = 5;  // R = 4
constexpr i64 RUNDEN = static_cast<i64>(STUETZSTELLEN) - 1;

constexpr std::array<Gebiet, LAENDER> LAENDERORDNUNG = {Gebiet::US, Gebiet::CN,
                                                        Gebiet::DE, Gebiet::BR};

constexpr std::array<Instrument, PFADINSTRUMENTE> PFADORDNUNG = {
    Instrument::Leitzins, Instrument::Zoll, Instrument::Haushalt};

/// Der Wert, den Land `l`, Instrument `i` und Stuetzstelle `t` im Probenjahrgang tragen.
///
/// Die drei Grundwerte liegen so weit auseinander, dass sich die Bereiche nicht
/// beruehren: Leitzins 500 bis 840, Zoll 3.000 bis 3.340, Haushaltssaldo -400 bis -60.
[[nodiscard]] i64 muster(std::size_t l, std::size_t i, std::size_t t)
{
    const std::array<i64, PFADINSTRUMENTE> grund = {500, 3000, -400};
    return grund[i] + 100 * static_cast<i64>(l) + 10 * static_cast<i64>(t);
}

[[nodiscard]] Jahrgang probenjahrgang()
{
    Jahrgang jahrgang(STUETZSTELLEN);
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
            for (std::size_t t = 0; t < STUETZSTELLEN; ++t) {
                jahrgang.setze(LAENDERORDNUNG[l], PFADORDNUNG[i], t, muster(l, i, t));
            }
        }
    }
    return jahrgang;
}

/// Ein Jahrgang, dessen Leitzinspfad ueberall `sockel` traegt, ausser an einer Stelle:
/// Land DE, Stuetzstelle 2, wo `tiefpunkt` steht. Zoll und Haushalt bleiben null -- fuer
/// `aufschlag_min` zaehlt allein der Leitzins.
[[nodiscard]] Jahrgang leitzinsjahrgang(i64 sockel, i64 tiefpunkt)
{
    Jahrgang jahrgang(STUETZSTELLEN);
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t t = 0; t < STUETZSTELLEN; ++t) {
            jahrgang.setze(LAENDERORDNUNG[l], Instrument::Leitzins, t, sockel);
        }
    }
    jahrgang.setze(Gebiet::DE, Instrument::Leitzins, 2, tiefpunkt);
    return jahrgang;
}

// ---------------------------------------------------------------------------
// (a) Runde 1 gibt die erste Stuetzstelle -- gelesen ueber den Zugang des Kerns
// ---------------------------------------------------------------------------

void fall_a_erste_stuetzstelle()
{
    const Jahrgang jahrgang = probenjahrgang();
    Konstanten konstanten;
    jahrgang.fuelle_pfadstand(konstanten, 1);

    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
            const i64 gelesen =
                kern::werte::pfadstand(konstanten, LAENDERORDNUNG[l], PFADORDNUNG[i]);
            PRUEFE(gelesen == muster(l, i, 0));
        }
    }

    // Der Traeger wird ueber `kern::werte::pfadstand` gelesen und nicht ueber das Feld:
    // Das ist der eine Zugang, den der Kern dafuer vorsieht, und nur er haelt die beiden
    // Indizes gegen ihre schmaleren Bereiche.
    PRUEFE(kern::werte::pfadstand(konstanten, Gebiet::BR, Instrument::Haushalt)
           == muster(3, 2, 0));

    // T40: `R = stuetzstellen - 1`, gebildet und nicht hingeschrieben.
    PRUEFE(jahrgang.runden() == RUNDEN);
    PRUEFE(jahrgang.stuetzstellen() == STUETZSTELLEN);
}

// ---------------------------------------------------------------------------
// (b) Runde r gibt die r-te Stuetzstelle -- und sie ist eine andere Zahl
// ---------------------------------------------------------------------------

void fall_b_rte_stuetzstelle()
{
    const Jahrgang jahrgang = probenjahrgang();

    for (i64 runde = 1; runde <= RUNDEN; ++runde) {
        Konstanten konstanten;
        jahrgang.fuelle_pfadstand(konstanten, runde);
        const std::size_t t = static_cast<std::size_t>(runde) - 1;
        PRUEFE(jahrgang.stuetzstelle_zu_runde(runde) == t);
        for (std::size_t l = 0; l < LAENDER; ++l) {
            for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
                const i64 gelesen =
                    kern::werte::pfadstand(konstanten, LAENDERORDNUNG[l], PFADORDNUNG[i]);
                PRUEFE(gelesen == muster(l, i, t));
            }
        }
    }

    // Der Riegel gegen einen Traeger, der nur vortraegt: zwei Runden, zwei Zahlen. Ohne
    // diese Zeile waere ein `fuelle_pfadstand`, das den Rundenwert uebergeht, gruen.
    Konstanten eins;
    Konstanten drei;
    jahrgang.fuelle_pfadstand(eins, 1);
    jahrgang.fuelle_pfadstand(drei, 3);
    PRUEFE(kern::werte::pfadstand(eins, Gebiet::US, Instrument::Leitzins) == 500);
    PRUEFE(kern::werte::pfadstand(drei, Gebiet::US, Instrument::Leitzins) == 520);
    PRUEFE(kern::werte::pfadstand(eins, Gebiet::US, Instrument::Leitzins)
           != kern::werte::pfadstand(drei, Gebiet::US, Instrument::Leitzins));
}

// ---------------------------------------------------------------------------
// (c) Eine Runde jenseits von R bekommt die letzte Stuetzstelle
// ---------------------------------------------------------------------------

void fall_c_klemme()
{
    const Jahrgang jahrgang = probenjahrgang();
    const std::size_t letzte = STUETZSTELLEN - 1;

    PRUEFE(!jahrgang.ueber_fenster(RUNDEN));
    PRUEFE(jahrgang.ueber_fenster(RUNDEN + 1));

    // Die Klemme, an drei Runden jenseits des Fensters: die erste dahinter, eine weit
    // dahinter und eine, die ohne Klemme weit hinter das Feld laese.
    PRUEFE(jahrgang.stuetzstelle_zu_runde(RUNDEN + 1) == letzte);
    PRUEFE(jahrgang.stuetzstelle_zu_runde(RUNDEN + 5) == letzte);
    PRUEFE(jahrgang.stuetzstelle_zu_runde(1'000'000) == letzte);

    Konstanten konstanten;
    jahrgang.fuelle_pfadstand(konstanten, 1'000'000);
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
            const i64 gelesen =
                kern::werte::pfadstand(konstanten, LAENDERORDNUNG[l], PFADORDNUNG[i]);
            PRUEFE(gelesen == muster(l, i, letzte));
        }
    }

    // Positivkontrolle zur Schranke darunter: Runde 1 rechnet.
    PRUEFE(jahrgang.stuetzstelle_zu_runde(1) == 0);
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() { static_cast<void>(jahrgang.stuetzstelle_zu_runde(0)); },
        "die Runden beginnen bei eins", "T40"));
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() { static_cast<void>(jahrgang.stuetzstelle_zu_runde(-7)); },
        "die Runden beginnen bei eins", "T40"));
}

// ---------------------------------------------------------------------------
// (d) Eine Stuetzstelle ausserhalb des Bereichs wird gemeldet, nicht gekappt
// ---------------------------------------------------------------------------

void fall_d_wertebereich()
{
    const Jahrgang jahrgang = probenjahrgang();

    // Der Wertebereich kommt als Argument herein. `instrument_min` und `instrument_max`
    // sind Schluessel von `parameter.toml` und keine Felder von `kern::werte::Konstanten`
    // -- gelesen wird hier nichts aus einer Datei.
    Wertebereiche weit{};
    weit[0] = Wertebereich{-500, 5000};   // Leitzins
    weit[1] = Wertebereich{0, 4000};      // Zollniveau
    weit[2] = Wertebereich{-1000, 1000};  // Haushaltssaldo

    // Positivkontrolle: derselbe Jahrgang, ein Bereich, den er haelt.
    const Bereichsbefund sauber = jahrgang.pruefe_wertebereich(weit);
    PRUEFE(sauber.sauber());
    PRUEFE(sauber.verletzungen == 0);

    // Und jetzt eine Obergrenze, die genau die fuenf Zollstuetzstellen von BR nicht mehr
    // deckt: BR traegt 3.300 bis 3.340, die drei anderen Laender hoechstens 3.240.
    Wertebereiche eng = weit;
    eng[1] = Wertebereich{0, 3299};

    const Bereichsbefund befund = jahrgang.pruefe_wertebereich(eng);
    PRUEFE(!befund.sauber());
    PRUEFE(befund.verletzungen == STUETZSTELLEN);

    const char* wortlaut = befund.erste.fertig();
    PRUEFE(enthaelt(wortlaut, "BR"));        // das Land, namentlich
    PRUEFE(enthaelt(wortlaut, "Reihe 13"));  // die Reihe, namentlich
    PRUEFE(enthaelt(wortlaut, "3300"));
    PRUEFE(!befund.erste.abgeschnitten());

    // **Gemeldet und nicht gekappt** (T51). Der Pfad steht nach der Pruefung unveraendert
    // da; ein stilles Kappen erfuellte die Schranke und toetete den Befund.
    PRUEFE(jahrgang.stelle(Gebiet::BR, Instrument::Zoll, 0) == 3300);
    PRUEFE(jahrgang.stelle(Gebiet::BR, Instrument::Zoll, 4) == 3340);

    Konstanten konstanten;
    jahrgang.fuelle_pfadstand(konstanten, 1);
    PRUEFE(kern::werte::pfadstand(konstanten, Gebiet::BR, Instrument::Zoll) == 3300);

    // Eine Untergrenze fasst dieselbe Stelle von der anderen Seite an, und der erste
    // Befund ist dann ein anderes Land und eine andere Reihe -- der Beleg, dass die
    // Meldung ihre drei Ordnungen wirklich liest und nicht einen festen Text traegt.
    Wertebereiche unten = weit;
    unten[2] = Wertebereich{-350, 1000};  // Haushaltssaldo: US traegt -400 bei t = 0
    const Bereichsbefund von_unten = jahrgang.pruefe_wertebereich(unten);
    PRUEFE(von_unten.verletzungen > 0);
    PRUEFE(enthaelt(von_unten.erste.fertig(), "US"));
    PRUEFE(enthaelt(von_unten.erste.fertig(), "Reihe 12"));
}

// ---------------------------------------------------------------------------
// (e) `aufschlag_min` aus dem Minimum des Leitzinspfads (T23 Punkt 5)
// ---------------------------------------------------------------------------

void fall_e_aufschlag_min()
{
    // Der Einlagesatz der EZB: -50 Basispunkte, also `aufschlag_min = 1 - (-50) = 51`.
    const Jahrgang einlage = leitzinsjahrgang(400, -50);
    PRUEFE(einlage.aufschlag_min() == 51);
    PRUEFE(!einlage.aufschlag_zulaessig(50));
    PRUEFE(einlage.aufschlag_zulaessig(51));
    PRUEFE(einlage.aufschlag_zulaessig(200));

    // Der Hauptrefinanzierungssatz: 0,00 Prozent ab 2016, also `aufschlag_min = 1`.
    const Jahrgang haupt = leitzinsjahrgang(400, 0);
    PRUEFE(haupt.aufschlag_min() == 1);
    PRUEFE(!haupt.aufschlag_zulaessig(0));
    PRUEFE(haupt.aufschlag_zulaessig(1));

    // Die verworfene Alternative als Zahl: Waere `aufschlag_min` aus `leitzins_start`
    // statt aus dem Minimum ueber **alle** Stuetzstellen gebildet, stuende hier -399.
    // Der Tiefpunkt liegt an Stuetzstelle 2 und nicht an der ersten.
    PRUEFE(einlage.leitzins_start(Gebiet::DE) == 400);
    PRUEFE(einlage.aufschlag_min() != 1 - einlage.leitzins_start(Gebiet::DE));
}

// ---------------------------------------------------------------------------
// `leitzins_start` ist die erste Stuetzstelle und kein zweites Feld (T23 Punkt 5)
// ---------------------------------------------------------------------------

void fall_leitzins_start()
{
    const Jahrgang jahrgang = probenjahrgang();
    Konstanten konstanten;
    jahrgang.fuelle_leitzins_start(konstanten);

    for (std::size_t l = 0; l < LAENDER; ++l) {
        PRUEFE(jahrgang.leitzins_start(LAENDERORDNUNG[l]) == muster(l, 0, 0));
        PRUEFE(konstanten.leitzins_start[l] == muster(l, 0, 0));
        PRUEFE(jahrgang.leitzins_start(LAENDERORDNUNG[l])
               == jahrgang.stelle(LAENDERORDNUNG[l], Instrument::Leitzins, 0));
    }

    // Der Traeger fuehrt keinen zweiten Leitzinsstart: Was `fuelle_pfadstand` in Runde 1
    // schreibt, ist dieselbe Zahl -- und in Runde 3 nicht mehr, waehrend
    // `leitzins_start` steht. Genau das ist der Unterschied zwischen den beiden Feldern.
    Konstanten runde_drei;
    jahrgang.fuelle_pfadstand(runde_drei, 3);
    jahrgang.fuelle_leitzins_start(runde_drei);
    PRUEFE(runde_drei.leitzins_start[0] == 500);
    PRUEFE(kern::werte::pfadstand(runde_drei, Gebiet::US, Instrument::Leitzins) == 520);
}

// ---------------------------------------------------------------------------
// Die Schranken des Traegers -- jede mit Positivkontrolle davor
// ---------------------------------------------------------------------------

void fall_schranken()
{
    Jahrgang jahrgang = probenjahrgang();

    // T15: die Restwelt hat keine Instrumente.
    PRUEFE(jahrgang.stelle(Gebiet::BR, Instrument::Leitzins, 0) == 800);
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() {
            static_cast<void>(jahrgang.stelle(Gebiet::RW, Instrument::Leitzins, 0));
        },
        "spielbaren Laender", "T15"));
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() { jahrgang.setze(Gebiet::RW, Instrument::Leitzins, 0, 1); },
        "spielbaren Laender", "T15"));
    PRUEFE(bricht_ab_mit([]() { static_cast<void>(daten::land_kuerzel(Gebiet::RW)); },
                         "Restwelt", "T15"));

    // T61: die Finanzmarktregulierung hat keine Reihe.
    PRUEFE(jahrgang.stelle(Gebiet::US, Instrument::Haushalt, 0) == -400);
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() {
            static_cast<void>(jahrgang.stelle(Gebiet::US, Instrument::Regulierung, 0));
        },
        "keine Reihe", "T61"));
    PRUEFE(bricht_ab_mit(
        []() { static_cast<void>(daten::reihe_von(Instrument::Regulierung)); },
        "keine Reihe", "T61"));
    PRUEFE(bricht_ab_mit(
        []() { static_cast<void>(daten::instrument_name(Instrument::Regulierung)); },
        "keine Reihe", "T61"));

    // Die Stuetzstelle wird gegen die **belegten** geprueft und nicht gegen die
    // Feldbreite: Was dahinter liegt, ist die Vorbelegung mit null und saehe wie ein
    // Datum aus.
    PRUEFE(jahrgang.stelle(Gebiet::US, Instrument::Leitzins, STUETZSTELLEN - 1) == 540);
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() {
            static_cast<void>(
                jahrgang.stelle(Gebiet::US, Instrument::Leitzins, STUETZSTELLEN));
        },
        "Stuetzstelle", "jenseits"));
    PRUEFE(bricht_ab_mit(
        [&jahrgang]() {
            jahrgang.setze(Gebiet::US, Instrument::Leitzins, STUETZSTELLEN, 1);
        },
        "Stuetzstelle", "jenseits"));

    // Die Wand aus T40, in beide Richtungen. Der Aufruf hinter dem Erbauer wird nie
    // erreicht -- er steht da, damit kein unbenutztes Ergebnis herumliegt.
    PRUEFE(Jahrgang(daten::STUETZSTELLEN_HOECHSTENS).runden()
           == daten::RUNDEN_HOECHSTENS);
    PRUEFE(bricht_ab_mit(
        []() {
            static_cast<void>(
                Jahrgang(daten::STUETZSTELLEN_HOECHSTENS + 1).stuetzstellen());
        },
        "Wand aus T40", nullptr));
    PRUEFE(Jahrgang(daten::STUETZSTELLEN_MINDESTENS).runden() == 1);
    PRUEFE(bricht_ab_mit(
        []() {
            static_cast<void>(
                Jahrgang(daten::STUETZSTELLEN_MINDESTENS - 1).stuetzstellen());
        },
        "weniger als zwei Stuetzstellen", "T40"));

    // Die Reihennummern, an denen die Meldung haengt (`daten/reihen.toml`).
    PRUEFE(daten::reihe_von(Instrument::Leitzins) == 9);
    PRUEFE(daten::reihe_von(Instrument::Zoll) == 13);
    PRUEFE(daten::reihe_von(Instrument::Haushalt) == 12);
}

}  // namespace

int main()
{
    fall_a_erste_stuetzstelle();
    fall_b_rte_stuetzstelle();
    fall_c_klemme();
    fall_d_wertebereich();
    fall_e_aufschlag_min();
    fall_leitzins_start();
    fall_schranken();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "jahrgang_probe: %d Pruefung(en) fehlgeschlagen\n",
                     fehlgeschlagen);
        return 1;
    }
    std::fprintf(stdout,
                 "jahrgang_probe: alle Pruefungen bestanden -- ein Jahrgang mit %zu "
                 "Stuetzstellen (R = %lld), vier Laender, drei Reihen.\n",
                 STUETZSTELLEN, static_cast<long long>(RUNDEN));
    return 0;
}
