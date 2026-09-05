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
using kern::schreiber::Ursache;
using kern::schreiber::Ursachensatz;
using kern::schreiber::sollmaskengroesse;

using kern::schritt::Rundenergebnis;

using kern::verlauf::GLIEDER_JE_RUNDE;
using kern::verlauf::PARTIELAENGE_HOECHSTENS;
using kern::verlauf::RUNDEN_KAPAZITAET;
using kern::verlauf::Verlauf;

using kern::zustand::FELDER;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::PartieFeld;
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

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("verlauf_probe: alle Pruefungen bestanden\n");
    return 0;
}
