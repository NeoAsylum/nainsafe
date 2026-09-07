//! Laufende Probe fuer `kern::verlauf` -- die vier Bedingungen des Arbeitspakets 0140.
//!
//! Die tragende ist Bedingung 2, und sie ist es, weil ein einseitiger Nachweis von dem
//! Fehler, gegen den T19 geschrieben ist, nicht zu unterscheiden waere: Ein Verlauf, der
//! die ueberzaehlige Kette still wegwirft und mit Code 0 zurueckkehrt, besteht jede
//! Pruefung, die nur die durchgelaufene Haelfte ansieht. Geprueft werden deshalb beide
//! Seiten derselben Grenze, und beide Laeufe drucken ihr Ergebnis ab.
//!
//!   1. **Der Verlauf gibt heraus, was er aufgenommen hat.** Eine Partie ueber vier
//!      Runden ueber `kern::schritt::schritt`; je Runde wird die Kette aufgenommen und
//!      danach mit der verglichen, die die Runde geliefert hat -- Glied fuer Glied und
//!      Feld fuer Feld.
//!   2. **Die Aufnahmekapazitaet je Runde.** Genau an der Grenze laeuft es durch, eines
//!      darueber bricht ab, und die Meldung nennt die Runde und die Kapazitaet.
//!   3. **Die Kapazitaet ueber die Partie.** Dieselbe Zweiseitigkeit fuer die zweite
//!      Schranke: die letzte zulaessige Runde laeuft durch, die naechste bricht ab. Die
//!      Schranke ist seit Paket 0144 die Wand aus T40 und nicht mehr die Partielaenge --
//!      Bedingung 1 laeuft deshalb ueber eine volle Partie der laengsten nach T40
//!      zulaessigen Laenge, und nicht mehr ueber vier Runden.
//!   4. **Die Ordnung und die Griffe daneben.** Rundennummern unter eins, nicht
//!      aufsteigende Runden, ein Glied ohne begonnene Runde, ein Platz ausserhalb, eine
//!      Runde, die der Verlauf nicht traegt.
//!   5. **Die Rueckwaertsaufloesung aus T20** (Paket 0091). Eine Partie ueber drei
//!      Runden, in der eine Aktion aus Runde 1 eine Groesse in Runde 3 aendert -- einmal
//!      unmittelbar und einmal ueber ein Zwischenglied. Dazu die Gegenprobe auf die
//!      Verzoegerung, die fuenf Enden einer Kette und die Griffe daneben.
//!   6. **Ein Glied traegt die Runde, unter der es abgelegt wird** (Paket 0186).
//!      Zweiseitig an derselben Lage: Das uebereinstimmende Glied laeuft durch, das
//!      abweichende bricht ab -- nach oben und nach unten --, die Meldung nennt beide
//!      Rundennummern, und der Verlauf steht danach unveraendert da.
//!
//! ## Keine Zahl steht hier abgeschrieben
//!
//! Die beiden Kapazitaeten kommen aus dem Kopf des Kastens, die Rundennummern aus dem
//! Zustand, den die Runde zurueckgibt, und die erwarteten Textstuecke der Abbrueche
//! werden mit demselben Meldungsbau erzeugt, den der Kasten benutzt. Eine
//! abgeschriebene 310 prueft nach der ersten Aenderung nichts mehr als sich selbst.
//!
//! Die Ausnahme ist der Namensraum in den Abbruchpruefungen. Er steht ausgeschrieben,
//! und zwar zweimal: einmal als Bedingung -- die Meldung nennt `kern::verlauf` -- und
//! einmal als Verbot -- sie nennt `kern::schreiber` nicht. Das zweite ist der Grund fuer
//! das erste: Die Kette traegt dieselbe Grenze und bricht ebenfalls ab, nur ohne die
//! Rundennummer. Ohne die Gegenprobe bliebe die Stelle gruen, wenn die aeussere Pruefung
//! des Verlaufs wegfiele und die innere der Kette an ihre Stelle traete.
//!
//! **Das Testprofil aus ADR 0011, Massnahme 2** gilt hier besonders: Ein Verlauf traegt
//! `RUNDEN_KAPAZITAET` Ketten zu je 310 Ursachensaetzen, und jeder Griff daneben waere
//! ohne den Adressen-Sanitizer eine gruene Probe.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/verlauf.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::meldung::Meldung;

using kern::schreiber::Kette;
using kern::schreiber::Modus;
using kern::schreiber::Schreiber;
using kern::schreiber::Ursache;
using kern::schreiber::UrsacheArt;
using kern::schreiber::Ursachensatz;
using kern::schreiber::sollmaskengroesse;

using kern::schritt::Rundenergebnis;

using kern::verlauf::Aufloesung;
using kern::verlauf::Ende;
using kern::verlauf::GLIEDER_JE_RUNDE;
using kern::verlauf::KEIN_RUNDENPLATZ;
using kern::verlauf::PARTIELAENGE_HOECHSTENS;
using kern::verlauf::RUNDEN_KAPAZITAET;
using kern::verlauf::Verlauf;

using kern::zustand::FELDER;
using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Instrument;
using kern::zustand::InstrumentFeld;
using kern::zustand::PartieFeld;
using kern::zustand::Sektor;
using kern::zustand::SektorGroesse;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

/// Der Platz von `partie.runde` -- aus der Adressrechnung geholt und nicht als Zahl
/// hingeschrieben.
constexpr Index PLATZ_RUNDE = kern::zustand::stelle_partie(PartieFeld::Runde);

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Ob `nadel` in `heuhaufen` vorkommt -- ohne `<cstring>`, das nach der Sperre keine
/// Kernquelle mehr einbinden darf.
bool enthaelt(const char* heuhaufen, const char* nadel)
{
    for (std::size_t i = 0; heuhaufen[i] != '\0'; ++i) {
        std::size_t j = 0;
        while (nadel[j] != '\0' && heuhaufen[i + j] == nadel[j]) {
            ++j;
        }
        if (nadel[j] == '\0') {
            return true;
        }
    }
    return nadel[0] == '\0';
}

/// Der Wortlaut des zuletzt gefangenen Abbruchs. Er wird abgeschrieben, weil `what()`
/// in die Ausnahme zeigt und die hinter dem Fangblock fort ist.
std::array<char, kern::meldung::PUFFER_ZEICHEN> letzte_meldung{};

void schreibe_ab(const char* quelle)
{
    std::size_t n = 0;
    while (quelle[n] != '\0' && n + 1 < letzte_meldung.size()) {
        letzte_meldung[n] = quelle[n];
        ++n;
    }
    letzte_meldung[n] = '\0';
}

/// Fuehrt `tun` aus und sagt, ob es mit einem Abbruch des Kerns geendet hat. Der
/// Wortlaut steht danach in `letzte_meldung` und wird an der Aufrufstelle geprueft.
///
/// Eine Ausnahme anderer Art gilt **nicht** als Abbruch: Der Kern wirft nach T7 genau
/// einen Typ, und eine Stelle, die etwas anderes wirft, soll auffallen statt
/// durchzugehen.
template <typename Aufgabe>
bool hat_abgebrochen(Aufgabe tun)
{
    letzte_meldung[0] = '\0';
    try {
        tun();
    } catch (const std::domain_error& fehler) {
        schreibe_ab(fehler.what());
        return true;
    } catch (...) {
        schreibe_ab("(abgebrochen, aber nicht mit std::domain_error)");
        return false;
    }
    return false;
}

/// Das erwartete Textstueck einer Zahl -- mit demselben Meldungsbau erzeugt, den der
/// Kasten selbst benutzt. Damit kann die Erwartung nicht von der Ausgabe abweichen.
Meldung als_text(i64 wert)
{
    Meldung text;
    text.zahl(wert);
    return text;
}

/// Ob zwei Ketten zeichengleich sind: gleiche Laenge, und jedes Glied in allen sieben
/// Feldern aus T18 gleich. Der Feldvergleich kommt aus dem Ursachensatz selbst.
bool ketten_gleich(const Kette& links, const Kette& rechts)
{
    if (links.laenge() != rechts.laenge()) {
        return false;
    }
    for (std::size_t glied = 0; glied < links.laenge(); ++glied) {
        if (!(links.eintrag(glied) == rechts.eintrag(glied))) {
            return false;
        }
    }
    return true;
}

/// Ein Musterwert je Adresse -- null, beide Vorzeichen, die Skala aus spiel.md und
/// beide Enden des Ganzzahlbereichs.
i64 musterwert(Index platz)
{
    constexpr std::array<i64, 8> muster = {0,
                                           1,
                                           -1,
                                           10'000,
                                           -10'000,
                                           123'456'789,
                                           kern::festkomma::I64_MAX,
                                           kern::festkomma::I64_MIN};
    return muster[platz % muster.size()];
}

/// Ein Ursachensatz, der sich von jedem anderen dieser Probe unterscheidet.
///
/// Er wird gebaut und nicht gerechnet: Diese Probe prueft, ob der Verlauf ablegt und
/// herausgibt, was er bekommen hat, nicht ob eine Runde richtig rechnet. Genau deshalb
/// muessen sich die Saetze unterscheiden -- ein Vergleich ueber lauter gleiche Glieder
/// bestuende auch bei vertauschter Reihenfolge.
Ursachensatz muster_satz(i64 runde, std::size_t lauf)
{
    Ursachensatz satz;
    satz.runde = runde;
    satz.ziel = lauf % FELDER;
    satz.alt = musterwert(satz.ziel);
    satz.neu = static_cast<i64>(lauf);
    satz.ursache = Ursache::vortrag(satz.ziel);
    satz.verzoegerung = 0;
    satz.beitrag = 1'000;
    return satz;
}

/// Eine Ausgangslage mit Musterwerten auf allen 310 Adressen und `partie.runde` auf
/// `rundennummer` -- ein einziger Startwertzugang, die Rundennummer zuletzt.
Zustand ausgangslage(i64 rundennummer)
{
    Zustand welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, musterwert(platz));
    }
    zugang.setze(PLATZ_RUNDE, rundennummer);
    return welt;
}

// ---------------------------------------------------------------------------
// Bedingung 1 -- der Verlauf gibt heraus, was er aufgenommen hat
// ---------------------------------------------------------------------------

/// Wie viele Runden die Partie dieser Probe laeuft: die laengste Partielaenge, die T40
/// zulaesst.
///
/// **Das ist der tragende Teil der Abnahme von Paket 0144.** Vier Runden liefen auch
/// gruen, als der Verlauf bei zwanzig abbrach -- ein Nachweis, der nur bis zwanzig
/// zaehlt, ist von einem, der die Wand erreicht, nicht zu unterscheiden. Die Zahl kommt
/// aus dem Kopf des Kastens und steht hier nicht abgeschrieben: Verschiebt T40 seine
/// Wand, laeuft diese Probe von selbst bis dorthin mit.
constexpr std::size_t PARTIERUNDEN = PARTIELAENGE_HOECHSTENS;

void probe_partie()
{
    Verlauf verlauf;
    std::array<Kette, PARTIERUNDEN> geliefert{};
    std::array<i64, PARTIERUNDEN> nummern{};

    Zustand welt = ausgangslage(0);
    for (std::size_t n = 0; n < PARTIERUNDEN; ++n) {
        const Rundenergebnis ergebnis = kern::schritt::schritt(welt, {}, Modus::Weltlauf);

        // Die Rundennummer kommt aus dem Zustand, den die Runde zurueckgibt, und nicht
        // aus der Zaehlschleife: So ist es die Nummer, die der Kern vergeben hat.
        nummern[n] = ergebnis.neuer_zustand.lies(PLATZ_RUNDE);
        geliefert[n] = ergebnis.kette_dieser_runde;

        verlauf.aufnehmen(nummern[n], ergebnis.kette_dieser_runde);
        welt = ergebnis.neuer_zustand;
    }

    PRUEFE(verlauf.runden() == PARTIERUNDEN);

    std::size_t glieder_zusammen = 0;
    for (std::size_t n = 0; n < PARTIERUNDEN; ++n) {
        const i64 runde = nummern[n];
        const Kette& aus_verlauf = verlauf.kette(n);
        const Kette& gesucht = verlauf.kette_der_runde(runde);

        const bool zeichengleich = ketten_gleich(aus_verlauf, geliefert[n]);
        pruefe(zeichengleich, "die Kette aus dem Verlauf ist die der Runde", __LINE__);
        pruefe(verlauf.rundennummer(n) == runde, "und sie steht unter ihrer Rundennummer",
               __LINE__);
        pruefe(&gesucht == &aus_verlauf, "die Suche nach der Rundennummer findet dieselbe",
               __LINE__);
        pruefe(aus_verlauf.laenge() == sollmaskengroesse(Modus::Weltlauf),
               "eine Runde im weltlauf schreibt jede Adresse ihrer Sollmaske", __LINE__);

        // Der Zuordnungsnachweis, und er kommt aus dem Glied selbst: Jeder Ursachensatz
        // traegt nach T18 die Runde, in der er geschrieben wurde. Ein Verlauf, der die
        // Ketten um eine Runde versetzt ablegte, faellt hier auf, ohne dass die Probe
        // eine eigene Buchhaltung dagegenhalten muesste.
        std::size_t fremde = 0;
        for (std::size_t glied = 0; glied < aus_verlauf.laenge(); ++glied) {
            if (aus_verlauf.eintrag(glied).runde != runde) {
                ++fremde;
            }
        }
        pruefe(fremde == 0, "jedes Glied traegt die Runde, unter der es steht", __LINE__);

        glieder_zusammen += aus_verlauf.laenge();
        std::printf("  Runde %lld: %zu Glieder, zeichengleich %s, fremde Glieder %zu\n",
                    static_cast<long long>(runde), aus_verlauf.laenge(),
                    zeichengleich ? "ja" : "NEIN", fremde);
    }

    PRUEFE(verlauf.glieder() == glieder_zusammen);

    // Die Gegenprobe zur Zuordnung: Die Ketten zweier Runden sind **nicht** gleich.
    // Ohne sie waere "zeichengleich" oben von jeder beliebigen Zuordnung erfuellt, denn
    // vier gleiche Ketten sind auch vertauscht noch gleich.
    for (std::size_t n = 1; n < PARTIERUNDEN; ++n) {
        pruefe(!ketten_gleich(verlauf.kette(n), geliefert[n - 1]),
               "die Kette einer Runde unterscheidet sich von der der Vorrunde", __LINE__);
        pruefe(verlauf.rundennummer(n) == verlauf.rundennummer(n - 1) + 1,
               "die Runden stehen luecken- und sprungfrei hintereinander", __LINE__);
    }

    // Und der Zustand am Ende der Partie: Die Pruefsumme steht hier, damit der Nachweis
    // zu Bedingung 3 sie ohne einen zweiten Bau ablesen kann.
    std::printf("  nach %zu Runden: %zu Glieder im Verlauf, Zustandspruefsumme %016llx\n",
                verlauf.runden(), verlauf.glieder(),
                static_cast<unsigned long long>(kern::zustand::pruefsumme_von(welt)));
}

// ---------------------------------------------------------------------------
// Bedingung 2 -- die Aufnahmekapazitaet je Runde, zweiseitig
// ---------------------------------------------------------------------------

/// Die Rundennummer, unter der die volle Kette steht. Sie ist absichtlich keine Eins:
/// Die Abbruchmeldung soll die Runde nennen, und eine Eins kommt in einer Meldung mit
/// einer Kapazitaet von 310 an mehreren Stellen vor.
constexpr i64 RUNDE_MIT_VOLLER_KETTE = 7;

void probe_kapazitaet_je_runde()
{
    Verlauf verlauf;
    verlauf.beginne_runde(RUNDE_MIT_VOLLER_KETTE);

    // (a) Genau an der Grenze -- das muss durchlaufen.
    for (std::size_t lauf = 0; lauf < GLIEDER_JE_RUNDE; ++lauf) {
        verlauf.anhaengen(muster_satz(RUNDE_MIT_VOLLER_KETTE, lauf));
    }
    PRUEFE(verlauf.kette(0).laenge() == GLIEDER_JE_RUNDE);
    PRUEFE(verlauf.glieder() == GLIEDER_JE_RUNDE);

    // und alle 310 stehen unveraendert da, in der Reihenfolge ihres Eingangs
    std::size_t abweichende = 0;
    for (std::size_t lauf = 0; lauf < GLIEDER_JE_RUNDE; ++lauf) {
        if (!(verlauf.kette(0).eintrag(lauf) == muster_satz(RUNDE_MIT_VOLLER_KETTE, lauf))) {
            ++abweichende;
        }
    }
    PRUEFE(abweichende == 0);
    std::printf("  an der Grenze: Runde %lld mit %zu Gliedern aufgenommen, %zu "
                "abweichend, kein Abbruch\n",
                static_cast<long long>(RUNDE_MIT_VOLLER_KETTE), verlauf.kette(0).laenge(),
                abweichende);

    // (b) Eines darueber -- das muss abbrechen, und zwar mit Runde und Kapazitaet.
    const bool geworfen = hat_abgebrochen([&verlauf]() {
        verlauf.anhaengen(muster_satz(RUNDE_MIT_VOLLER_KETTE, GLIEDER_JE_RUNDE));
    });
    PRUEFE(geworfen);

    Meldung erwartete_runde;
    erwartete_runde.text("Runde ");
    erwartete_runde.zahl(RUNDE_MIT_VOLLER_KETTE);
    const Meldung erwartete_kapazitaet = als_text(static_cast<i64>(GLIEDER_JE_RUNDE));

    PRUEFE(enthaelt(letzte_meldung.data(), erwartete_runde.fertig()));
    PRUEFE(enthaelt(letzte_meldung.data(), erwartete_kapazitaet.fertig()));
    PRUEFE(enthaelt(letzte_meldung.data(), "kern::verlauf"));

    // Die Gegenprobe: Es war die aeussere Pruefung und nicht die der Kette. Die Kette
    // traegt dieselbe Grenze, kennt aber ihre Rundennummer nicht -- faellt die aeussere
    // weg, bricht es weiter ab, nur ohne die Angabe, die den Befund brauchbar macht.
    PRUEFE(!enthaelt(letzte_meldung.data(), "kern::schreiber"));

    // Und nichts ist dazugekommen: Der Abbruch ist keine halbe Aufnahme.
    PRUEFE(verlauf.kette(0).laenge() == GLIEDER_JE_RUNDE);
    PRUEFE(verlauf.glieder() == GLIEDER_JE_RUNDE);
    std::printf("  eines darueber: Abbruch mit \"%s\"\n", letzte_meldung.data());
    std::printf("  danach unveraendert: %zu Glieder in Runde %lld\n",
                verlauf.kette(0).laenge(), static_cast<long long>(verlauf.rundennummer(0)));
}

// ---------------------------------------------------------------------------
// Bedingung 3 -- die Kapazitaet ueber die Partie, ebenfalls zweiseitig
// ---------------------------------------------------------------------------

void probe_rundenkapazitaet()
{
    Verlauf verlauf;
    for (std::size_t n = 0; n < RUNDEN_KAPAZITAET; ++n) {
        const i64 runde = static_cast<i64>(n) + 1;
        verlauf.beginne_runde(runde);
        verlauf.anhaengen(muster_satz(runde, n));
    }
    PRUEFE(verlauf.runden() == RUNDEN_KAPAZITAET);
    PRUEFE(verlauf.glieder() == RUNDEN_KAPAZITAET);
    PRUEFE(verlauf.rundennummer(RUNDEN_KAPAZITAET - 1) == static_cast<i64>(RUNDEN_KAPAZITAET));
    std::printf("  an der Grenze: %zu Runden aufgenommen, kein Abbruch\n", verlauf.runden());

    const i64 eine_zuviel = static_cast<i64>(RUNDEN_KAPAZITAET) + 1;
    const bool geworfen =
        hat_abgebrochen([&verlauf, eine_zuviel]() { verlauf.beginne_runde(eine_zuviel); });
    PRUEFE(geworfen);

    const Meldung erwartete_kapazitaet = als_text(static_cast<i64>(RUNDEN_KAPAZITAET));
    PRUEFE(enthaelt(letzte_meldung.data(), erwartete_kapazitaet.fertig()));
    PRUEFE(enthaelt(letzte_meldung.data(), "kern::verlauf"));
    PRUEFE(verlauf.runden() == RUNDEN_KAPAZITAET);
    std::printf("  eine darueber: Abbruch mit \"%s\"\n", letzte_meldung.data());
}

// ---------------------------------------------------------------------------
// Bedingung 4 -- die Ordnung und die Griffe daneben
// ---------------------------------------------------------------------------

void probe_ordnung()
{
    // Ein Glied ohne begonnene Runde.
    {
        Verlauf frisch;
        PRUEFE(frisch.runden() == 0);
        PRUEFE(frisch.glieder() == 0);
        const bool geworfen =
            hat_abgebrochen([&frisch]() { frisch.anhaengen(muster_satz(1, 0)); });
        PRUEFE(geworfen);
        PRUEFE(enthaelt(letzte_meldung.data(), "keine Runde begonnen"));
        std::printf("  Glied ohne Runde: %s\n", letzte_meldung.data());
    }

    // Rundennummern unter eins -- die Null und eine negative.
    for (const i64 zu_klein : {i64{0}, i64{-1}}) {
        Verlauf frisch;
        const bool geworfen =
            hat_abgebrochen([&frisch, zu_klein]() { frisch.beginne_runde(zu_klein); });
        pruefe(geworfen, "eine Runde vor der ersten gibt es nicht", __LINE__);
        pruefe(enthaelt(letzte_meldung.data(), "kern::verlauf"), "und der Kasten nennt sich",
               __LINE__);
        pruefe(frisch.runden() == 0, "und nimmt sie nicht doch auf", __LINE__);
        std::printf("  Runde %lld: %s\n", static_cast<long long>(zu_klein),
                    letzte_meldung.data());
    }

    // Nicht aufsteigende Runden -- dieselbe noch einmal und eine kleinere. Davor der
    // Gegenfall, der durchlaufen muss: die naechstgroessere.
    {
        Verlauf verlauf;
        verlauf.beginne_runde(5);
        verlauf.beginne_runde(6);
        PRUEFE(verlauf.runden() == 2);

        for (const i64 zurueck : {i64{6}, i64{5}, i64{1}}) {
            const bool geworfen =
                hat_abgebrochen([&verlauf, zurueck]() { verlauf.beginne_runde(zurueck); });
            pruefe(geworfen, "die Runden steigen streng an", __LINE__);
            pruefe(verlauf.runden() == 2, "und der Verlauf bleibt, wie er war", __LINE__);
            std::printf("  nach Runde 6 noch Runde %lld: %s\n",
                        static_cast<long long>(zurueck), letzte_meldung.data());
        }

        // Ein Sprung nach vorn ist dagegen erlaubt: Der Verlauf verlangt Ordnung, nicht
        // Lueckenlosigkeit -- eine Sitzung, die aus einer geladenen Partie fortsetzt,
        // faengt nicht bei eins an.
        verlauf.beginne_runde(9);
        PRUEFE(verlauf.runden() == 3);
        PRUEFE(verlauf.rundennummer(2) == 9);
    }

    // Ein Platz ausserhalb und eine Runde, die der Verlauf nicht traegt.
    {
        Verlauf verlauf;
        verlauf.beginne_runde(3);
        verlauf.anhaengen(muster_satz(3, 0));

        PRUEFE(hat_abgebrochen(
            [&verlauf]() { static_cast<void>(verlauf.rundennummer(verlauf.runden())); }));
        PRUEFE(enthaelt(letzte_meldung.data(), "ausserhalb"));
        PRUEFE(hat_abgebrochen(
            [&verlauf]() { static_cast<void>(verlauf.kette(verlauf.runden())); }));
        PRUEFE(enthaelt(letzte_meldung.data(), "ausserhalb"));

        for (const i64 unbekannt : {i64{2}, i64{4}}) {
            const bool geworfen = hat_abgebrochen([&verlauf, unbekannt]() {
                static_cast<void>(verlauf.kette_der_runde(unbekannt));
            });
            pruefe(geworfen, "zu einer nicht aufgenommenen Runde gibt es keine Kette",
                   __LINE__);
            std::printf("  Kette der Runde %lld: %s\n", static_cast<long long>(unbekannt),
                        letzte_meldung.data());
        }

        // Der Gegenfall: die Runde, die er traegt, findet er.
        PRUEFE(verlauf.kette_der_runde(3).laenge() == 1);
        PRUEFE(verlauf.kette_der_runde(3).eintrag(0) == muster_satz(3, 0));
    }
}

// ---------------------------------------------------------------------------
// Bedingung 5 -- die Rueckwaertsaufloesung aus T20 (Paket 0091)
// ---------------------------------------------------------------------------

/// Das Land, an dem die Partie dieser Probe ihre Ursachenkette baut.
constexpr Gebiet LAND = Gebiet::DE;

constexpr Index PLATZ_ZOLLSTAND =
    kern::zustand::stelle_instrument(LAND, Instrument::Zoll, InstrumentFeld::Stand);
constexpr Index PLATZ_ZOLLDRUCK =
    kern::zustand::stelle_instrument(LAND, Instrument::Zoll, InstrumentFeld::Druck);
constexpr Index PLATZ_PREIS =
    kern::zustand::stelle_sektorgroesse(LAND, Sektor::Industrie, SektorGroesse::Preis);
constexpr Index PLATZ_KAPITAL =
    kern::zustand::stelle_sektorgroesse(LAND, Sektor::Industrie, SektorGroesse::Kapitalstock);

/// Die Aktionsart, die die Partie in Runde 1 setzt.
///
/// Absichtlich keine Eins: In einer Kettenzeile stehen Rundennummern, Verzoegerungen und
/// Beitraege daneben, und eine Eins darunter waere von jeder anderen Eins nicht zu
/// unterscheiden.
constexpr std::size_t AKTIONSART = 2;

/// Was eine Runde dieser Partie ausser dem Vortrag schreibt.
struct Setzung {
    Index   ziel = 0;
    i64     wert = 0;
    Ursache ursache{};
    i64     verzoegerung = 0;
    i64     beitrag      = 0;
};

/// Eine Runde im Spielmodus von Hand: `partie.runde`, dann die benannten Setzungen, dann
/// jede noch nicht geschriebene Adresse unveraendert vorgetragen.
///
/// **Der Weg geht durch `kern::schreiber` und nicht daneben.** Die Ursachensaetze, die
/// hier entstehen, sind die des Kerns -- mit seiner Rundennummer, seinem Altwert und
/// seinem Neuwert --, und die zweiseitige Maskenpruefung aus T38 laeuft mit: Eine Runde,
/// die eine der 310 Adressen vergisst oder eine zweimal schreibt, kommt hier nicht heraus.
/// Von Hand ist an ihr nur, **welche** Ursache an welcher Adresse steht; das ist genau
/// der Teil, den `kern::schritt` heute noch nicht rechnet.
template <std::size_t N>
Rundenergebnis handrunde(const Zustand& vorrunde, i64 runde,
                         const std::array<Setzung, N>& setzungen)
{
    Schreiber schreiber{vorrunde, Modus::Spielmodus, runde};

    // Dieselbe Ursache wie im Rundengeruest des Kerns: Vortrag auf sich selbst,
    // Verzoegerung null, Beitrag 1.000 Promille.
    schreiber.setze(PLATZ_RUNDE, runde, Ursache::vortrag(PLATZ_RUNDE), 0, 1000);

    for (const Setzung& setzung : setzungen) {
        schreiber.setze(setzung.ziel, setzung.wert, setzung.ursache, setzung.verzoegerung,
                        setzung.beitrag);
    }
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (!schreiber.ist_geschrieben(platz)) {
            schreiber.vortrag(platz);
        }
    }
    return Rundenergebnis{schreiber.rundenende(), schreiber.kette()};
}

/// Der Startzustand der Partie -- Musterwerte, und darueber die vier benannten Adressen.
Zustand partiestart()
{
    Zustand       welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, musterwert(platz));
    }
    zugang.setze(PLATZ_ZOLLSTAND, 380);
    zugang.setze(PLATZ_ZOLLDRUCK, 0);
    zugang.setze(PLATZ_PREIS, 10'000);
    zugang.setze(PLATZ_KAPITAL, 4'200'000);
    zugang.setze(PLATZ_RUNDE, 0);
    return welt;
}

/// Die Partie der Abnahme: drei Runden, und eine Aktion in Runde 1 aendert eine Groesse
/// in Runde 3.
///
///   Runde 1: die Aktion setzt den Zollstand.
///   Runde 2: der Lobbydruck am Zoll entsteht aus dem Zollstand (Ursache `Instrument`,
///            Verzoegerung eins).
///   Runde 3: der Sektorpreis kommt aus jenem Druck (Verzoegerung eins) -- drei Glieder;
///            der Kapitalstock kommt unmittelbar aus dem Zollstand der Runde 1
///            (Verzoegerung zwei) -- zwei Glieder ueber zwei Runden.
///
/// Der zweite Weg ist der, den die Abnahme woertlich verlangt. Der erste steht daneben,
/// weil eine Kette aus zwei Gliedern noch nicht zeigt, dass die Aufloesung ueber ein
/// Zwischenglied hinweg findet.
Zustand partie_bauen(Verlauf& verlauf)
{
    Zustand welt = partiestart();

    const std::array<Setzung, 1> runde1 = {
        Setzung{PLATZ_ZOLLSTAND, 500, Ursache::aktion(AKTIONSART), 0, 1000}};
    const std::array<Setzung, 1> runde2 = {
        Setzung{PLATZ_ZOLLDRUCK, 4'200, Ursache::instrument(LAND, Instrument::Zoll), 1, 1000}};
    const std::array<Setzung, 2> runde3 = {
        Setzung{PLATZ_PREIS, 10'420, Ursache::vortrag(PLATZ_ZOLLDRUCK), 1, 700},
        Setzung{PLATZ_KAPITAL, 4'260'000, Ursache::vortrag(PLATZ_ZOLLSTAND), 2, 300}};

    const Rundenergebnis erste = handrunde(welt, 1, runde1);
    verlauf.aufnehmen(1, erste.kette_dieser_runde);
    welt = erste.neuer_zustand;

    const Rundenergebnis zweite = handrunde(welt, 2, runde2);
    verlauf.aufnehmen(2, zweite.kette_dieser_runde);
    welt = zweite.neuer_zustand;

    const Rundenergebnis dritte = handrunde(welt, 3, runde3);
    verlauf.aufnehmen(3, dritte.kette_dieser_runde);
    return dritte.neuer_zustand;
}

/// So viele Glieder legt diese Probe von einer Kette ab. Die laengste Kette der Partie
/// hat drei; die Grenze steht darueber, damit ein zu langes Ergebnis auffaellt, statt in
/// die Ablage zu passen.
constexpr std::size_t KETTE_PROBE_MAX = 8;

/// Eine aufgeloeste Kette als Liste -- damit die Pruefungen darunter sie an einem Stueck
/// ansehen koennen, statt den Schrittzaehler mitzufuehren.
struct Kettenprobe {
    std::array<Ursachensatz, KETTE_PROBE_MAX> glied{};
    std::size_t                               laenge = 0;
    Ende                                      ende   = Ende::OhneEintrag;
    bool                                      leer   = true;
};

Kettenprobe aufgeloest(const Verlauf& verlauf, i64 runde, Index ziel)
{
    Kettenprobe ergebnis;
    Aufloesung  kette{verlauf, runde, ziel};

    ergebnis.leer = kette.leer();
    if (!kette.leer()) {
        do {
            if (ergebnis.laenge < KETTE_PROBE_MAX) {
                ergebnis.glied[ergebnis.laenge] = kette.glied();
            }
            ++ergebnis.laenge;
        } while (kette.weiter());
        // Der Kasten zaehlt selbst mit; stimmten die beiden Zahlen nicht ueberein, waere
        // eine der beiden Zaehlungen falsch und die Liste unten nichts wert.
        pruefe(kette.glieder() == ergebnis.laenge, "die Aufloesung zaehlt ihre Glieder mit",
               __LINE__);
    }
    ergebnis.ende = kette.ende();
    return ergebnis;
}

/// Ein Glied von Hand -- fuer die Gegenproben, in denen sich genau eine Zahl unterscheidet.
Ursachensatz satz_mit(i64 runde, Index ziel, Ursache ursache, i64 verzoegerung)
{
    Ursachensatz satz;
    satz.runde        = runde;
    satz.ziel         = ziel;
    satz.alt          = 0;
    satz.neu          = 1;
    satz.ursache      = ursache;
    satz.verzoegerung = verzoegerung;
    satz.beitrag      = 1'000;
    return satz;
}

void schreibe_kette(const char* was, const Kettenprobe& kette)
{
    std::printf("  %s: %zu Glied(er), Ende %d, Runden", was, kette.laenge,
                static_cast<int>(kette.ende));
    for (std::size_t n = 0; n < kette.laenge && n < KETTE_PROBE_MAX; ++n) {
        std::printf(" %lld", static_cast<long long>(kette.glied[n].runde));
    }
    std::printf("\n");
}

void probe_partie_mit_ursachenkette()
{
    Verlauf       verlauf;
    const Zustand nach_runde_3 = partie_bauen(verlauf);

    PRUEFE(verlauf.runden() == 3);
    PRUEFE(nach_runde_3.lies(PLATZ_RUNDE) == 3);
    PRUEFE(verlauf.platz_der_runde(3) == 2);
    PRUEFE(verlauf.platz_der_runde(4) == KEIN_RUNDENPLATZ);

    // (a) Die Kette, die die Abnahme woertlich verlangt: die Aktion aus Runde 1 und die
    //     Groesse aus Runde 3, mit der Verzoegerung dazwischen.
    {
        const Kettenprobe kette = aufgeloest(verlauf, 3, PLATZ_KAPITAL);
        schreibe_kette("Kapitalstock aus der Aktion (zwei Runden)", kette);
        PRUEFE(!kette.leer);
        PRUEFE(kette.laenge == 2);
        PRUEFE(kette.glied[0].runde == 3);
        PRUEFE(kette.glied[0].ziel == PLATZ_KAPITAL);
        PRUEFE(kette.glied[0].verzoegerung == 2);
        PRUEFE(kette.glied[0].beitrag == 300);
        PRUEFE(kette.glied[0].ursache.art() == UrsacheArt::Vortrag);
        PRUEFE(kette.glied[0].ursache.vortragsadresse() == PLATZ_ZOLLSTAND);
        PRUEFE(kette.glied[1].runde == 1);
        PRUEFE(kette.glied[1].ziel == PLATZ_ZOLLSTAND);
        PRUEFE(kette.glied[1].ursache.art() == UrsacheArt::Aktion);
        PRUEFE(kette.glied[1].ursache.aktionsnummer() == AKTIONSART);
        PRUEFE(kette.glied[1].alt == 380 && kette.glied[1].neu == 500);
        PRUEFE(kette.ende == Ende::Ausloeser);

        // Die Verzoegerung dazwischen, aus den beiden Gliedern gerechnet statt behauptet.
        PRUEFE(kette.glied[0].runde - kette.glied[1].runde == 2);
    }

    // (b) Derselbe Ausloeser ueber ein Zwischenglied -- drei Glieder, drei Runden.
    {
        const Kettenprobe kette = aufgeloest(verlauf, 3, PLATZ_PREIS);
        schreibe_kette("Sektorpreis ueber den Lobbydruck (drei Glieder)", kette);
        PRUEFE(kette.laenge == 3);
        PRUEFE(kette.glied[0].runde == 3 && kette.glied[0].ziel == PLATZ_PREIS);
        PRUEFE(kette.glied[1].runde == 2 && kette.glied[1].ziel == PLATZ_ZOLLDRUCK);
        PRUEFE(kette.glied[1].ursache.art() == UrsacheArt::Instrument);
        PRUEFE(kette.glied[2].runde == 1 && kette.glied[2].ziel == PLATZ_ZOLLSTAND);
        PRUEFE(kette.glied[2].ursache.art() == UrsacheArt::Aktion);
        PRUEFE(kette.ende == Ende::Ausloeser);
    }

    // (c) Der Vortrag auf sich selbst. Er traegt nach T18 die Verzoegerung null, und
    //     genau hier entscheidet sich, ob die Aufloesung ueber Runden hinweg findet:
    //     Wer die Ursachenrunde aus Runde minus Verzoegerung ausrechnet, landet auf
    //     demselben Glied und steht still. Das zweite Glied steht deshalb in Runde 2 und
    //     nicht in Runde 3.
    {
        const Kettenprobe kette = aufgeloest(verlauf, 3, PLATZ_RUNDE);
        schreibe_kette("partie.runde, dreimal vorgetragen", kette);
        PRUEFE(kette.laenge == 3);
        PRUEFE(kette.glied[0].runde == 3);
        PRUEFE(kette.glied[1].runde == 2);
        PRUEFE(kette.glied[2].runde == 1);
        PRUEFE(kette.glied[1].ziel == PLATZ_RUNDE);
        // Vor der ersten aufgenommenen Runde steht der Startwert, und der hat nach T18
        // keinen Ursachensatz.
        PRUEFE(kette.ende == Ende::OhneVorgaenger);
    }

    // (d) Keine der 310 Adressen bleibt ohne Ursache: In einer Runde im Spielmodus wird
    //     jede geschrieben, also findet jede ihren Anfangspunkt.
    {
        std::size_t ohne = 0;
        for (Index platz = 0; platz < FELDER; ++platz) {
            if (Aufloesung{verlauf, 3, platz}.leer()) {
                ++ohne;
            }
        }
        PRUEFE(ohne == 0);
        std::printf("  Adressen ohne Ursachensatz in Runde 3: %zu von %zu\n", ohne, FELDER);
    }
}

/// Die Verzoegerung grenzt die Suche ein -- zweiseitig an derselben Lage.
///
/// Ohne den Gegenfall belegte die Partie oben nur, dass eine Kette herauskommt, nicht
/// dass die Verzoegerung sie steuert: Eine Aufloesung, die das Feld gar nicht liest,
/// faende dieselbe Runde 1, sobald in Runde 2 kein Schreibzugriff auf die Ursachenadresse
/// stuende. In dieser Lage steht einer, und nur die Verzoegerung unterscheidet die beiden
/// Laeufe.
void probe_verzoegerung_grenzt_ein()
{
    for (const i64 verzoegerung : {i64{0}, i64{2}}) {
        Verlauf verlauf;
        verlauf.beginne_runde(1);
        verlauf.anhaengen(satz_mit(1, PLATZ_ZOLLSTAND, Ursache::aktion(AKTIONSART), 0));
        verlauf.beginne_runde(2);
        verlauf.anhaengen(satz_mit(2, PLATZ_ZOLLSTAND, Ursache::vortrag(PLATZ_ZOLLSTAND), 0));
        verlauf.beginne_runde(3);
        verlauf.anhaengen(
            satz_mit(3, PLATZ_KAPITAL, Ursache::vortrag(PLATZ_ZOLLSTAND), verzoegerung));

        const Kettenprobe kette = aufgeloest(verlauf, 3, PLATZ_KAPITAL);
        schreibe_kette(verzoegerung == 0 ? "Verzoegerung null" : "Verzoegerung zwei", kette);

        if (verzoegerung == 0) {
            pruefe(kette.laenge == 3, "ohne Verzoegerung fuehrt der Weg ueber die Runde 2",
                   __LINE__);
            pruefe(kette.glied[1].runde == 2, "und das zweite Glied steht dort", __LINE__);
        } else {
            pruefe(kette.laenge == 2, "mit Verzoegerung zwei ueberspringt er die Runde 2",
                   __LINE__);
            pruefe(kette.glied[1].runde == 1, "und das zweite Glied steht in Runde 1",
                   __LINE__);
        }
        pruefe(kette.ende == Ende::Ausloeser, "beide enden bei derselben Aktion", __LINE__);
    }
}

/// Die fuenf Enden, jedes an seiner eigenen Lage.
void probe_enden()
{
    struct Fall {
        const char* name;
        Ursache     ursache;
        Ende        erwartet;
    };

    const std::array<Fall, 4> faelle = {
        Fall{"Aktion", Ursache::aktion(AKTIONSART), Ende::Ausloeser},
        Fall{"Gegenkraft", Ursache::gegenkraft(3), Ende::Ausloeser},
        Fall{"Jahrgang", Ursache::jahrgang(), Ende::Jahrgang},
        Fall{"Marktraeumung", Ursache::marktraeumung(Sektor::Industrie), Ende::OhneAdresse},
    };

    for (const Fall& fall : faelle) {
        Verlauf verlauf;
        verlauf.beginne_runde(1);
        verlauf.anhaengen(satz_mit(1, PLATZ_KAPITAL, fall.ursache, 0));

        const Kettenprobe kette = aufgeloest(verlauf, 1, PLATZ_KAPITAL);
        pruefe(kette.laenge == 1, "eine Ursache ohne Adresse ist das letzte Glied", __LINE__);
        pruefe(kette.ende == fall.erwartet, fall.name, __LINE__);
        std::printf("  Ende bei %s: %d\n", fall.name, static_cast<int>(kette.ende));
    }

    // Ein Vortrag ohne frueheren Schreibzugriff -- der Anfang des Verlaufs.
    {
        Verlauf verlauf;
        verlauf.beginne_runde(1);
        verlauf.anhaengen(satz_mit(1, PLATZ_KAPITAL, Ursache::vortrag(PLATZ_KAPITAL), 0));

        const Kettenprobe kette = aufgeloest(verlauf, 1, PLATZ_KAPITAL);
        PRUEFE(kette.laenge == 1);
        PRUEFE(kette.ende == Ende::OhneVorgaenger);

        // Zwei Lagen ohne Anfangspunkt: eine Runde, die der Verlauf nicht traegt, und
        // eine Adresse, die in ihr nicht geschrieben wurde. Beide sind leer und keine
        // bricht ab -- die Unterschiedsebene muss sie benennen koennen.
        const Kettenprobe fremde_runde = aufgeloest(verlauf, 2, PLATZ_KAPITAL);
        PRUEFE(fremde_runde.leer);
        PRUEFE(fremde_runde.laenge == 0);
        PRUEFE(fremde_runde.ende == Ende::OhneEintrag);

        const Kettenprobe fremde_adresse = aufgeloest(verlauf, 1, PLATZ_PREIS);
        PRUEFE(fremde_adresse.leer);
        PRUEFE(fremde_adresse.ende == Ende::OhneEintrag);
        std::printf("  ohne Anfangspunkt: fremde Runde und fremde Adresse, beide leer\n");
    }
}

/// Die Griffe daneben: was abbricht und was nicht.
void probe_aufloesung_grenzen()
{
    Verlauf verlauf;
    verlauf.beginne_runde(1);
    verlauf.anhaengen(satz_mit(1, PLATZ_ZOLLSTAND, Ursache::aktion(AKTIONSART), 0));
    verlauf.beginne_runde(2);
    verlauf.anhaengen(satz_mit(2, PLATZ_KAPITAL, Ursache::vortrag(PLATZ_ZOLLSTAND), 0));

    // Eine Adresse ausserhalb der 310 ist ein Rechenfehler des Aufrufers.
    {
        const bool geworfen = hat_abgebrochen(
            [&verlauf]() { static_cast<void>(Aufloesung{verlauf, 1, FELDER}.leer()); });
        PRUEFE(geworfen);
        PRUEFE(enthaelt(letzte_meldung.data(), "ausserhalb der 310"));
        std::printf("  Adresse ausserhalb: %s\n", letzte_meldung.data());
    }

    // Das Glied einer leeren Aufloesung gibt es nicht.
    {
        const bool geworfen = hat_abgebrochen([&verlauf]() {
            Aufloesung leere{verlauf, 9, PLATZ_KAPITAL};
            static_cast<void>(leere.glied());
        });
        PRUEFE(geworfen);
        PRUEFE(enthaelt(letzte_meldung.data(), "leer"));
        std::printf("  Glied einer leeren Aufloesung: %s\n", letzte_meldung.data());
    }

    // Ein Ende, das noch nicht feststeht, ist keine Auskunft.
    {
        const bool geworfen = hat_abgebrochen([&verlauf]() {
            Aufloesung laufende{verlauf, 2, PLATZ_KAPITAL};
            static_cast<void>(laufende.ende());
        });
        PRUEFE(geworfen);
        PRUEFE(enthaelt(letzte_meldung.data(), "noch nicht zu Ende"));
        std::printf("  Ende vor dem Ende: %s\n", letzte_meldung.data());

        // Der Gegenfall: dieselbe Aufloesung, zu Ende gegangen, antwortet.
        Aufloesung laufende{verlauf, 2, PLATZ_KAPITAL};
        PRUEFE(!laufende.beendet());
        while (laufende.weiter()) {
        }
        PRUEFE(laufende.beendet());
        PRUEFE(laufende.ende() == Ende::Ausloeser);
        PRUEFE(laufende.glieder() == 2);

        // Ein weiterer Schritt nach dem Ende bleibt bei false und aendert nichts.
        PRUEFE(!laufende.weiter());
        PRUEFE(laufende.glieder() == 2);
    }
}

// ---------------------------------------------------------------------------
// Bedingung 6 -- ein Glied traegt die Runde, unter der es abgelegt wird (Paket 0186)
// ---------------------------------------------------------------------------

/// Die Rundennummer, unter der die Glieder dieser Probe abgelegt werden.
///
/// Absichtlich keine Eins: In der Abbruchmeldung stehen zwei Rundennummern nebeneinander,
/// und die Probe unterscheidet sie am Wortlaut.
constexpr i64 RUNDE_DER_ABLAGE = 4;

/// Zwei fremde Rundennummern, eine oberhalb und eine unterhalb der offenen Runde.
///
/// Beide Richtungen, weil eine Schranke, die nur nach oben oder nur nach unten prueft, an
/// der jeweils anderen Vertauschung gruen bliebe -- und vertauscht waren die
/// Rundennummern in der Messung, aus der dieses Paket entstanden ist.
constexpr std::array<i64, 2> FREMDE_RUNDEN = {RUNDE_DER_ABLAGE + 2, RUNDE_DER_ABLAGE - 2};

void probe_glied_gehoert_in_seine_runde()
{
    // (a) Der uebereinstimmende Fall laeuft durch, und zwar auf beiden Wegen hinein:
    //     einzeln ueber `anhaengen` und als ganze Kette ueber `aufnehmen`.
    Verlauf verlauf;
    verlauf.beginne_runde(RUNDE_DER_ABLAGE);
    verlauf.anhaengen(muster_satz(RUNDE_DER_ABLAGE, 0));
    verlauf.anhaengen(muster_satz(RUNDE_DER_ABLAGE, 1));

    Kette gleiche;
    gleiche.anhaengen(muster_satz(RUNDE_DER_ABLAGE + 1, 2));
    gleiche.anhaengen(muster_satz(RUNDE_DER_ABLAGE + 1, 3));
    verlauf.aufnehmen(RUNDE_DER_ABLAGE + 1, gleiche);

    PRUEFE(verlauf.runden() == 2);
    PRUEFE(verlauf.glieder() == 4);
    std::printf("  uebereinstimmend: %zu Runden, %zu Glieder, kein Abbruch\n",
                verlauf.runden(), verlauf.glieder());

    // (b) Das abweichende Glied bricht ab, und der Verlauf steht danach unveraendert da.
    const i64 offene_runde = verlauf.rundennummer(verlauf.runden() - 1);
    for (const i64 fremd : FREMDE_RUNDEN) {
        const bool geworfen =
            hat_abgebrochen([&verlauf, fremd]() { verlauf.anhaengen(muster_satz(fremd, 4)); });
        pruefe(geworfen, "ein Glied mit fremder Rundennummer ist ein harter Fehler",
               __LINE__);

        // Die Meldung nennt beide Zahlen. Beide Erwartungen entstehen mit demselben
        // Meldungsbau, den der Kasten benutzt; abgeschrieben koennten sie von der Ausgabe
        // abweichen. Dass es wirklich zwei verschiedene sind, haelt die Pruefung darunter
        // fest -- sonst bestuende dieser Vergleich auch bei einer Meldung, die dieselbe
        // Zahl zweimal nennt.
        Meldung erwartetes_glied;
        erwartetes_glied.text("Runde ");
        erwartetes_glied.zahl(fremd);
        Meldung erwartete_ablage;
        erwartete_ablage.text("Runde ");
        erwartete_ablage.zahl(offene_runde);
        pruefe(fremd != offene_runde, "die beiden Erwartungen sind verschieden", __LINE__);
        pruefe(enthaelt(letzte_meldung.data(), erwartetes_glied.fertig()),
               "die Meldung nennt die Runde des Gliedes", __LINE__);
        pruefe(enthaelt(letzte_meldung.data(), erwartete_ablage.fertig()),
               "und die Runde, unter der es abgelegt wird", __LINE__);
        pruefe(enthaelt(letzte_meldung.data(), "kern::verlauf"), "und den Kasten", __LINE__);

        // Dieselbe Gegenprobe wie bei Bedingung 2: Es war die Pruefung des Verlaufs. Die
        // Kette traegt keine Rundennummer und koennte diesen Fehler gar nicht sehen --
        // eine Meldung aus `kern::schreiber` hiesse also, dass hier etwas anderes
        // zugeschlagen hat als die neue Schranke.
        pruefe(!enthaelt(letzte_meldung.data(), "kern::schreiber"),
               "und nicht die der Kette", __LINE__);

        pruefe(verlauf.runden() == 2, "der Verlauf traegt danach dieselben Runden", __LINE__);
        pruefe(verlauf.glieder() == 4, "und dieselben Glieder", __LINE__);
        pruefe(verlauf.rundennummer(1) == offene_runde, "unter derselben Rundennummer",
               __LINE__);
        std::printf("  Glied aus Runde %lld unter Runde %lld: %s\n",
                    static_cast<long long>(fremd), static_cast<long long>(offene_runde),
                    letzte_meldung.data());
    }

    // Und die Gegenprobe zum Riegel selbst: Dieselbe Stelle nimmt danach ein
    // uebereinstimmendes Glied weiterhin an. Ein Riegel, der nach dem ersten Abbruch alles
    // abwiese, waere an den beiden Abbruechen oben von diesem nicht zu unterscheiden.
    verlauf.anhaengen(muster_satz(offene_runde, 5));
    PRUEFE(verlauf.glieder() == 5);
    std::printf("  danach wieder uebereinstimmend: %zu Glieder\n", verlauf.glieder());

    // (c) Derselbe Riegel auf dem Weg ueber `aufnehmen`. Die Runde ist dort bereits
    //     begonnen, wenn das erste Glied abgewiesen wird -- `aufnehmen` laeuft ueber
    //     `beginne_runde` und `anhaengen` und nicht daneben. Der Verlauf traegt danach
    //     also eine Runde und kein Glied, und genau das steht hier statt eines
    //     ungepruefen "unveraendert".
    {
        Verlauf zweiter;
        Kette   fremde;
        fremde.anhaengen(muster_satz(FREMDE_RUNDEN[0], 6));

        const bool geworfen = hat_abgebrochen(
            [&zweiter, &fremde]() { zweiter.aufnehmen(RUNDE_DER_ABLAGE, fremde); });
        PRUEFE(geworfen);
        PRUEFE(zweiter.runden() == 1);
        PRUEFE(zweiter.glieder() == 0);
        PRUEFE(zweiter.rundennummer(0) == RUNDE_DER_ABLAGE);
        std::printf("  ueber aufnehmen: %zu Runde(n), %zu Glieder, Abbruch mit \"%s\"\n",
                    zweiter.runden(), zweiter.glieder(), letzte_meldung.data());
    }
}

}  // namespace

int main()
{
    // Die gemessenen Groessen zuerst -- der Nachweis zu Bedingung 3 liest sie hier ab,
    // statt sie in einem zweiten Bau zu ermitteln.
    std::printf("Groessen: sizeof(Verlauf) %zu, sizeof(Kette) %zu, RUNDEN_KAPAZITAET %zu, "
                "PARTIELAENGE_HOECHSTENS %zu\n",
                sizeof(Verlauf), sizeof(Kette), RUNDEN_KAPAZITAET,
                PARTIELAENGE_HOECHSTENS);
    std::printf("Bedingung 1 -- die Partie und ihre Ketten:\n");
    probe_partie();
    std::printf("Bedingung 2 -- die Aufnahmekapazitaet je Runde:\n");
    probe_kapazitaet_je_runde();
    std::printf("Bedingung 3 -- die Kapazitaet ueber die Partie:\n");
    probe_rundenkapazitaet();
    std::printf("Bedingung 4 -- Ordnung und Griffe daneben:\n");
    probe_ordnung();
    std::printf("Bedingung 5 -- die Rueckwaertsaufloesung aus T20:\n");
    probe_partie_mit_ursachenkette();
    probe_verzoegerung_grenzt_ein();
    probe_enden();
    probe_aufloesung_grenzen();
    std::printf("Bedingung 6 -- ein Glied traegt die Runde, unter der es steht:\n");
    probe_glied_gehoert_in_seine_runde();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("verlauf_probe: alle Pruefungen bestanden\n");
    return 0;
}
