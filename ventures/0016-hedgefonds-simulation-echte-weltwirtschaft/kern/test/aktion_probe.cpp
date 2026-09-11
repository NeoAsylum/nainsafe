//! Laufende Probe fuer `kern::aktion` -- die vier Bedingungen des Arbeitspakets 0146
//! und die fuenf des Arbeitspakets 0300.
//!
//! ## Die fuenf aus 0300, in einem Satz je Stueck
//!
//!   5. **Die Liste einer Runde.** Neunzehn plus dreissig Angebote auf fuenfzig
//!      Plaetzen, in der kanonischen Ordnung, jedes mit offener Stufe. Dazu die
//!      Gegenprobe -- dieselbe Menge umgedreht steht **nicht** in der Ordnung -- und
//!      der heutige Stand der beiden Argumente: Zwei verschiedene Zustaende ergeben
//!      dieselbe Liste.
//!   6. **Die fuenf Zielmengen aus T32b**, jede zweimal: einmal als heutige Zahl und
//!      einmal aus den Konstanten des Zustands gerechnet. Ein fuenftes Land bewegt
//!      beide Seiten zugleich; hielte man nur eine, waere die Probe entweder
//!      handnachzufuehren oder eine Formel gegen sich selbst.
//!   7. **Zwanzig Plaetze, neunzehn Angebote.** Aufgezaehlt und nicht gefegt: Jeder der
//!      zwanzig Steckplaetze wird einzeln gefragt. Eine blosse Zaehlung bestuende auch
//!      gegen eine Liste, die einen Platz doppelt und einen gar nicht anbietet.
//!   8. **Die vier gebauten Bedingungen des Buendels**, jede mit ihrer Positivkontrolle
//!      am Rand, der noch zulaessig ist -- und dazu die gemeldete Luecke als Fall statt
//!      als Satz: Die Arten 1, 2 und 4 ziehen heute keine Kasse.
//!   9. **Der Satz, mit dem T32 die Pruefung auf das Buendel legt** -- drei
//!      Aufstockungen desselben Steckplatzes, jede fuer sich zulaessig. Und derselbe
//!      Satz ohne das doppelte Ziel, damit die Anteilsskala ihn allein traegt.
//!
//! Die tragende ist Bedingung 2, und das Paket sagt auch, warum: Eine Ordnung, die
//! sich als Nebenwirkung der Erzeugungsschleife ergibt, ist nicht dasselbe wie eine
//! benannte Eigenschaft des Typs -- auch dann nicht, wenn die Probe gruen ist. Geprueft
//! wird deshalb beides, und zwar getrennt:
//!
//!   1. **Die drei Schluessel und ihre Rangfolge, benannt.** Es sind drei, sie tragen
//!      die Namen aus T32, ihr Wert ist ihr Rang, und der staerkere ueberwiegt jeden
//!      gegenlaeufigen Unterschied in den schwaecheren. Der Nachweis laeuft ueber die
//!      Raenge und nicht ueber drei hingeschriebene Beispiele: Wer die Rangfolge
//!      vertauscht, wird an jedem Rang rot.
//!   2. **Zwei verschieden vorsortierte Eingaben ergeben dieselbe Ausgabe.** Dieselbe
//!      Menge von zwoelf Aktionen, einmal genau rueckwaerts und einmal nach einer
//!      **falschen** Rangfolge vorsortiert -- Stufe zuerst, Aktionsart zuletzt. Das ist
//!      der Fall, den das Arbeitspaket meint: eine Reihenfolge, die von aussen kommt.
//!      Beide muessen auf dieselbe Ausgabe laufen, und beide auf die von Hand
//!      hingeschriebene Sollfolge.
//!   3. **Die Ordnung ist streng, vollstaendig und uebertragbar.** Ueber alle Paare und
//!      alle Tripel der zwoelf: genau eine der drei Lagen, Gegenlaeufigkeit,
//!      Uebertragbarkeit, und Gleichheit genau bei Gleichheit in allen drei Schluesseln.
//!      Dazu, dass die beiden Vergleichsoperatoren nichts anderes sagen als
//!      `ordnungsvergleich`.
//!   4. **Griffe daneben.** Eine Kennung ausserhalb 1 bis 5, ein Rang ausserhalb 0 bis
//!      2, eine Zielkennung jenseits ihres Wertebereichs, eine Laengenangabe groesser
//!      als die Liste. Jeder mit seiner Meldung, und daneben die Gegenprobe, dass die
//!      Nachbarwerte innerhalb der Grenze **nicht** abbrechen.
//!
//! ## Warum Bedingung 2 eine Gegenprobe braucht
//!
//! "Beide Eingaben ergeben dieselbe Ausgabe" ist wohlfeil, wenn die beiden Eingaben
//! schon gleich waren. Die Probe zeigt deshalb zuerst, dass die drei Folgen vor dem
//! Ordnen paarweise verschieden sind, und druckt alle drei ab. Ohne das bestuende sie
//! auch gegen eine Sortierung, die gar nichts tut.
//!
//! ## Keine Zahl steht hier abgeschrieben, bis auf eine
//!
//! Die Sollfolge steht von Hand da, und das ist Absicht: Sie ist der einzige Teil der
//! Probe, der die Ordnung **nicht** aus dem Kasten bezieht. Eine Sollfolge, die der
//! Kasten selbst erzeugt hat, prueft die Sortierung gegen sich selbst. Alles andere --
//! die Zahl der Schluessel, ihre Raender, die Namen -- kommt aus dem Kopf.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::meldung::Meldung;

using kern::aktion::Aktion;
using kern::aktion::ART_KENNUNG_ERSTE;
using kern::aktion::ART_KENNUNG_LETZTE;
using kern::aktion::ARTEN;
using kern::aktion::Art;
using kern::aktion::art_bekannt;
using kern::aktion::art_der_kennung;
using kern::aktion::art_kennung;
using kern::aktion::art_name;
using kern::aktion::i64;
using kern::aktion::in_kanonischer_ordnung;
using kern::aktion::ordne;
using kern::aktion::ordnungsvergleich;
using kern::aktion::SCHLUESSEL;
using kern::aktion::Schluessel;
using kern::aktion::schluessel_des_ranges;
using kern::aktion::schluessel_name;
using kern::aktion::schluesselwert;
using kern::aktion::ZIELKENNUNG_MAX;
using kern::aktion::Zielkennung;
using kern::aktion::zielkennung;

// Paket 0300 -- die Liste einer Runde und die Pruefung des Buendels
using kern::aktion::ANGEBOTE_HOECHSTENS;
using kern::aktion::ANTEIL_HOECHSTENS;
using kern::aktion::Buendel;
using kern::aktion::buendel_einwand;
using kern::aktion::buendel_zulaessig;
using kern::aktion::BUENDEL_AKTIONEN_HOECHSTENS;
using kern::aktion::BUENDEL_FASST;
using kern::aktion::Einwand;
using kern::aktion::EINWAENDE;
using kern::aktion::einwand_name;
using kern::aktion::kassenbedarf;
using kern::aktion::STUFE_OFFEN;
using kern::aktion::zielmenge;
using kern::aktion::zulaessige_aktionen;
using kern::aktion::Zulaessigkeitsliste;

using kern::werte::fondsanteil;
using kern::werte::Konstanten;

using kern::zustand::BeteiligungsFeld;
using kern::zustand::FondsGroesse;
using kern::zustand::Gebiet;
using kern::zustand::Index;
using kern::zustand::INSTRUMENTE;
using kern::zustand::LAENDER;
using kern::zustand::Sektor;
using kern::zustand::SEKTOREN;
using kern::zustand::Startbelegung;
using kern::zustand::Steckplatz;
using kern::zustand::STECKPLAETZE;
using kern::zustand::STECKPLAETZE_SPIELBAR;
using kern::zustand::stelle_beteiligung;
using kern::zustand::stelle_fonds;
using kern::zustand::stelle_position;
using kern::zustand::Zustand;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Ob `nadel` in `heuhaufen` vorkommt -- ohne den Standardkopf fuer Zeichenketten, den
/// nach der Sperre keine Kernquelle mehr einbinden darf.
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

/// Zeichengleichheit zweier nullterminierter Texte.
bool gleich(const char* links, const char* rechts)
{
    std::size_t i = 0;
    while (links[i] != '\0' && links[i] == rechts[i]) {
        ++i;
    }
    return links[i] == rechts[i];
}

/// Der Wortlaut des zuletzt gefangenen Abbruchs. Er wird abgeschrieben, weil der Text
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

/// Fuehrt `tun` aus und sagt, ob es mit einem Abbruch des Kerns geendet hat. Eine
/// Ausnahme anderer Art gilt **nicht** als Abbruch: Der Kern wirft nach T7 genau einen
/// Typ, und eine Stelle, die etwas anderes wirft, soll auffallen statt durchzugehen.
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
/// Kasten selbst benutzt. Damit kann die Erwartung von der Ausgabe nicht abweichen.
Meldung als_text(i64 wert)
{
    Meldung text;
    text.zahl(wert);
    return text;
}

// ---------------------------------------------------------------------------
// Die zwoelf Aktionen, in der Sollfolge von Hand
// ---------------------------------------------------------------------------
//
// Sie decken, was die Ordnung unterscheiden muss: alle fuenf Arten; zweimal dieselbe
// Art und dasselbe Ziel bei verschiedener Stufe (Plaetze 0/1 und 6/7); dieselbe Art bei
// verschiedenem Ziel; negative und positive Stufen, damit ein Vergleich auf den Betrag
// statt auf den Wert auffiele.

inline constexpr std::size_t ANZAHL = 12;

using Liste = std::array<Aktion, ANZAHL>;

constexpr Liste SOLLFOLGE = {{
    {Art::Position, Zielkennung{0}, -3},
    {Art::Position, Zielkennung{0}, 1},
    {Art::Position, Zielkennung{4}, -1},
    {Art::Position, Zielkennung{19}, 2},
    {Art::Beteiligung, Zielkennung{0}, 5},
    {Art::Beteiligung, Zielkennung{11}, -5},
    {Art::Lobbybudget, Zielkennung{3}, -7},
    {Art::Lobbybudget, Zielkennung{3}, 7},
    {Art::Lobbybudget, Zielkennung{15}, 1},
    {Art::Hebel, Zielkennung{0}, 9},
    {Art::Sichtbarkeit, Zielkennung{0}, -1},
    {Art::Sichtbarkeit, Zielkennung{2}, 1},
}};

void drucke(const char* titel, const Liste& liste)
{
    std::printf("  %s\n", titel);
    for (std::size_t k = 0; k < ANZAHL; ++k) {
        std::printf("    %2zu  %-13s ziel %5u  stufe %5lld\n", k, art_name(liste[k].art),
                    static_cast<unsigned>(liste[k].ziel.wert),
                    static_cast<long long>(liste[k].stufe));
    }
}

/// Ob zwei Folgen Platz fuer Platz dieselben Aktionen tragen.
bool folgen_gleich(const Liste& links, const Liste& rechts)
{
    for (std::size_t k = 0; k < ANZAHL; ++k) {
        if (ordnungsvergleich(links[k], rechts[k]) != 0) {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Die Raender der drei Schluessel und der Weg, einen einzeln zu setzen
// ---------------------------------------------------------------------------

i64 rand_klein(Schluessel schluessel)
{
    switch (schluessel) {
    case Schluessel::Aktionsart:
        return static_cast<i64>(ART_KENNUNG_ERSTE);
    case Schluessel::Zielkennung:
        return 0;
    case Schluessel::Stufe:
        return kern::festkomma::I64_MIN;
    }
    return 0;
}

i64 rand_gross(Schluessel schluessel)
{
    switch (schluessel) {
    case Schluessel::Aktionsart:
        return static_cast<i64>(ART_KENNUNG_LETZTE);
    case Schluessel::Zielkennung:
        return static_cast<i64>(ZIELKENNUNG_MAX);
    case Schluessel::Stufe:
        return kern::festkomma::I64_MAX;
    }
    return 0;
}

void setze(Aktion& eintrag, Schluessel schluessel, i64 wert)
{
    switch (schluessel) {
    case Schluessel::Aktionsart:
        eintrag.art = art_der_kennung(wert);
        return;
    case Schluessel::Zielkennung:
        eintrag.ziel = zielkennung(static_cast<std::size_t>(wert));
        return;
    case Schluessel::Stufe:
        eintrag.stufe = wert;
        return;
    }
}

// ---------------------------------------------------------------------------
// Bedingung 1 -- die drei Schluessel und ihre Rangfolge
// ---------------------------------------------------------------------------

void probe_schluessel()
{
    // Es sind drei, und ihr Wert ist ihr Rang.
    PRUEFE(SCHLUESSEL == 3);
    for (std::size_t rang = 0; rang < SCHLUESSEL; ++rang) {
        const Schluessel schluessel = schluessel_des_ranges(rang);
        PRUEFE(static_cast<std::size_t>(static_cast<std::uint8_t>(schluessel)) == rang);
        std::printf("    Rang %zu: %s\n", rang, schluessel_name(schluessel));
    }

    // Die Namen sind die aus T32, in der Rangfolge aus T32.
    PRUEFE(gleich(schluessel_name(schluessel_des_ranges(0)), "Aktionsart"));
    PRUEFE(gleich(schluessel_name(schluessel_des_ranges(1)), "Zielkennung"));
    PRUEFE(gleich(schluessel_name(schluessel_des_ranges(2)), "Stufe"));

    // Der Wert eines Schluessels ist der, den die Aktion traegt.
    const Aktion muster{Art::Lobbybudget, Zielkennung{13}, -4};
    PRUEFE(schluesselwert(muster, Schluessel::Aktionsart) == art_kennung(Art::Lobbybudget));
    PRUEFE(schluesselwert(muster, Schluessel::Aktionsart) == 3);
    PRUEFE(schluesselwert(muster, Schluessel::Zielkennung) == 13);
    PRUEFE(schluesselwert(muster, Schluessel::Stufe) == -4);

    // Die fuenf Arten tragen die Kennungen 1 bis 5, luecklos und in dieser Folge.
    for (std::size_t k = 0; k < ARTEN; ++k) {
        const i64 kennung = static_cast<i64>(ART_KENNUNG_ERSTE) + static_cast<i64>(k);
        const Art art = art_der_kennung(kennung);
        PRUEFE(art_bekannt(art));
        PRUEFE(art_kennung(art) == kennung);
        std::printf("    Kennung %lld: %s\n", static_cast<long long>(kennung),
                    art_name(art));
    }

    // Der Nachweis der Rangfolge, ueber die Raenge und nicht ueber Beispiele: Der
    // staerkere Schluessel zeigt in die eine Richtung, **alle** schwaecheren zeigen mit
    // ihrem groesstmoeglichen Unterschied in die andere. Gewinnen muss der staerkere.
    for (std::size_t rang = 0; rang + 1 < SCHLUESSEL; ++rang) {
        Aktion links{};
        Aktion rechts{};
        for (std::size_t andere = 0; andere < SCHLUESSEL; ++andere) {
            const Schluessel schluessel = schluessel_des_ranges(andere);
            if (andere < rang) {
                setze(links, schluessel, rand_klein(schluessel));
                setze(rechts, schluessel, rand_klein(schluessel));
            } else if (andere == rang) {
                setze(links, schluessel, rand_klein(schluessel));
                setze(rechts, schluessel, rand_gross(schluessel));
            } else {
                setze(links, schluessel, rand_gross(schluessel));
                setze(rechts, schluessel, rand_klein(schluessel));
            }
        }
        pruefe(ordnungsvergleich(links, rechts) < 0,
               "der staerkere Schluessel ueberwiegt alle schwaecheren zusammen",
               __LINE__);
        pruefe(ordnungsvergleich(rechts, links) > 0, "und in der Gegenrichtung ebenso",
               __LINE__);
        std::printf("    Rang %zu (%s) ueberwiegt jeden Unterschied darunter\n", rang,
                    schluessel_name(schluessel_des_ranges(rang)));
    }
}

// ---------------------------------------------------------------------------
// Bedingung 2 -- zwei verschieden vorsortierte Eingaben, dieselbe Ausgabe
// ---------------------------------------------------------------------------

/// Die Rangfolge, die T32 **nicht** meint: die Stufe zuerst, die Aktionsart zuletzt.
///
/// Sie ist nicht hingeschrieben, sondern umgedreht -- der Rang `k` dieser Ordnung ist
/// der Rang `SCHLUESSEL - 1 - k` der kanonischen. Damit bleibt sie die Gegenordnung,
/// auch wenn die kanonische einmal vier Schluessel haette, und sie kann nicht
/// versehentlich mit ihr zusammenfallen.
int falscher_vergleich(const Aktion& links, const Aktion& rechts)
{
    for (std::size_t rang = 0; rang < SCHLUESSEL; ++rang) {
        const Schluessel schluessel = schluessel_des_ranges(SCHLUESSEL - 1 - rang);
        const i64 hier = schluesselwert(links, schluessel);
        const i64 dort = schluesselwert(rechts, schluessel);
        if (hier < dort) {
            return -1;
        }
        if (dort < hier) {
            return 1;
        }
    }
    return 0;
}

void ordne_falsch(Liste& liste)
{
    for (std::size_t k = 1; k < ANZAHL; ++k) {
        const Aktion eintrag = liste[k];
        std::size_t platz = k;
        while (platz > 0 && falscher_vergleich(liste[platz - 1], eintrag) > 0) {
            liste[platz] = liste[platz - 1];
            --platz;
        }
        liste[platz] = eintrag;
    }
}

Liste rueckwaerts(const Liste& liste)
{
    Liste gedreht{};
    for (std::size_t k = 0; k < ANZAHL; ++k) {
        gedreht[k] = liste[ANZAHL - 1 - k];
    }
    return gedreht;
}

void probe_ordnung_der_liste()
{
    // Die Sollfolge steht von Hand da und ist die kanonische -- das ist die eine
    // Aussage dieser Probe, die nicht aus dem Kasten kommt.
    PRUEFE(in_kanonischer_ordnung(SOLLFOLGE, ANZAHL));

    Liste rueckwaerts_eingabe = rueckwaerts(SOLLFOLGE);
    Liste falsch_vorsortiert = SOLLFOLGE;
    ordne_falsch(falsch_vorsortiert);

    drucke("Eingabe A -- genau rueckwaerts:", rueckwaerts_eingabe);
    drucke("Eingabe B -- nach der falschen Rangfolge (Stufe zuerst):", falsch_vorsortiert);

    // Die Gegenprobe: Waeren die beiden Eingaben schon gleich oder schon geordnet,
    // bestuende diese Bedingung auch gegen eine Sortierung, die nichts tut.
    PRUEFE(!folgen_gleich(rueckwaerts_eingabe, falsch_vorsortiert));
    PRUEFE(!folgen_gleich(rueckwaerts_eingabe, SOLLFOLGE));
    PRUEFE(!folgen_gleich(falsch_vorsortiert, SOLLFOLGE));
    PRUEFE(!in_kanonischer_ordnung(rueckwaerts_eingabe, ANZAHL));
    PRUEFE(!in_kanonischer_ordnung(falsch_vorsortiert, ANZAHL));

    ordne(rueckwaerts_eingabe, ANZAHL);
    ordne(falsch_vorsortiert, ANZAHL);

    drucke("Ausgabe A:", rueckwaerts_eingabe);
    drucke("Ausgabe B:", falsch_vorsortiert);

    PRUEFE(in_kanonischer_ordnung(rueckwaerts_eingabe, ANZAHL));
    PRUEFE(in_kanonischer_ordnung(falsch_vorsortiert, ANZAHL));
    PRUEFE(folgen_gleich(rueckwaerts_eingabe, falsch_vorsortiert));
    PRUEFE(folgen_gleich(rueckwaerts_eingabe, SOLLFOLGE));
    PRUEFE(folgen_gleich(falsch_vorsortiert, SOLLFOLGE));

    // Eine schon geordnete Folge bleibt, wie sie ist.
    Liste schon_geordnet = SOLLFOLGE;
    ordne(schon_geordnet, ANZAHL);
    PRUEFE(folgen_gleich(schon_geordnet, SOLLFOLGE));

    // Eine Laengenangabe unter der Kapazitaet ordnet nur den Anfang und laesst den Rest
    // liegen -- die Kapazitaet ist die des Behaelters, die Laenge die der Liste.
    Liste teil = rueckwaerts(SOLLFOLGE);
    ordne(teil, 4);
    for (std::size_t k = 1; k < 4; ++k) {
        PRUEFE(ordnungsvergleich(teil[k - 1], teil[k]) <= 0);
    }
    for (std::size_t k = 4; k < ANZAHL; ++k) {
        PRUEFE(ordnungsvergleich(teil[k], SOLLFOLGE[ANZAHL - 1 - k]) == 0);
    }
}

// ---------------------------------------------------------------------------
// Bedingung 3 -- streng, vollstaendig, uebertragbar
// ---------------------------------------------------------------------------

void probe_ordnungsgesetze()
{
    for (std::size_t a = 0; a < ANZAHL; ++a) {
        for (std::size_t b = 0; b < ANZAHL; ++b) {
            const int hin = ordnungsvergleich(SOLLFOLGE[a], SOLLFOLGE[b]);
            const int zurueck = ordnungsvergleich(SOLLFOLGE[b], SOLLFOLGE[a]);

            // Genau eine der drei Lagen, und sie ist gegenlaeufig.
            PRUEFE(hin == -1 || hin == 0 || hin == 1);
            PRUEFE(hin == -zurueck);

            // Gleichheit genau bei Gleichheit in allen drei Schluesseln -- und die
            // Sollfolge traegt keine zwei gleichen, also genau auf der Diagonale.
            PRUEFE((hin == 0) == (a == b));

            // Die beiden Operatoren sagen nichts anderes.
            PRUEFE((SOLLFOLGE[a] == SOLLFOLGE[b]) == (hin == 0));
            PRUEFE((SOLLFOLGE[a] < SOLLFOLGE[b]) == (hin < 0));
            PRUEFE((SOLLFOLGE[a] > SOLLFOLGE[b]) == (hin > 0));

            // Und die Ordnung ist die der Sollfolge selbst.
            PRUEFE((a < b) == (hin < 0));
        }
    }

    std::size_t tripel = 0;
    for (std::size_t a = 0; a < ANZAHL; ++a) {
        for (std::size_t b = 0; b < ANZAHL; ++b) {
            for (std::size_t c = 0; c < ANZAHL; ++c) {
                const bool ab = ordnungsvergleich(SOLLFOLGE[a], SOLLFOLGE[b]) <= 0;
                const bool bc = ordnungsvergleich(SOLLFOLGE[b], SOLLFOLGE[c]) <= 0;
                const bool ac = ordnungsvergleich(SOLLFOLGE[a], SOLLFOLGE[c]) <= 0;
                if (ab && bc) {
                    PRUEFE(ac);
                }
                ++tripel;
            }
        }
    }
    std::printf("    %zu Paare und %zu Tripel geprueft\n", ANZAHL * ANZAHL, tripel);
}

// ---------------------------------------------------------------------------
// Bedingung 4 -- die Griffe daneben
// ---------------------------------------------------------------------------

void probe_griffe_daneben()
{
    // Eine Kennung ausserhalb 1 bis 5. Die Meldung nennt die Zahl, und der erwartete
    // Wortlaut wird mit demselben Meldungsbau erzeugt, den der Kasten benutzt.
    for (const i64 daneben : {i64{0}, i64{6}, kern::festkomma::I64_MIN,
                             kern::festkomma::I64_MAX}) {
        const bool geworfen =
            hat_abgebrochen([daneben]() { static_cast<void>(art_der_kennung(daneben)); });
        pruefe(geworfen, "eine Kennung ausserhalb 1 bis 5 ist keine Aktionsart",
               __LINE__);
        PRUEFE(enthaelt(letzte_meldung.data(), "kern::aktion"));
        PRUEFE(enthaelt(letzte_meldung.data(), als_text(daneben).fertig()));
        std::printf("    Kennung %lld: %s\n", static_cast<long long>(daneben),
                    letzte_meldung.data());
    }

    // Die Gegenprobe: die beiden Nachbarn innerhalb der Grenze brechen nicht ab.
    for (const i64 gueltig : {static_cast<i64>(ART_KENNUNG_ERSTE),
                              static_cast<i64>(ART_KENNUNG_LETZTE)}) {
        PRUEFE(!hat_abgebrochen(
            [gueltig]() { static_cast<void>(art_der_kennung(gueltig)); }));
    }

    // Eine Aktionsart, die keine ist, faellt am Ordnungsschluessel auf und nicht erst
    // an der Ausgabe: Sie ist der staerkste Schluessel aus T32.
    const Aktion erfunden{static_cast<Art>(std::uint8_t{7}), Zielkennung{0}, 0};
    PRUEFE(!art_bekannt(erfunden.art));
    PRUEFE(hat_abgebrochen([&erfunden]() {
        static_cast<void>(schluesselwert(erfunden, Schluessel::Aktionsart));
    }));
    PRUEFE(enthaelt(letzte_meldung.data(), "Aktionsart"));
    PRUEFE(hat_abgebrochen(
        [&erfunden]() { static_cast<void>(ordnungsvergleich(erfunden, SOLLFOLGE[0])); }));
    PRUEFE(hat_abgebrochen([&erfunden]() { static_cast<void>(art_name(erfunden.art)); }));
    std::printf("    erfundene Art: %s\n", letzte_meldung.data());

    // Ein Rang jenseits der drei.
    PRUEFE(hat_abgebrochen(
        []() { static_cast<void>(schluessel_des_ranges(SCHLUESSEL)); }));
    PRUEFE(enthaelt(letzte_meldung.data(), "T32"));
    PRUEFE(hat_abgebrochen([]() {
        static_cast<void>(schluessel_name(static_cast<Schluessel>(std::uint8_t{9})));
    }));
    std::printf("    Rang daneben: %s\n", letzte_meldung.data());

    // Eine Zielkennung jenseits ihres Wertebereichs -- und der Rand selbst noch nicht.
    PRUEFE(!hat_abgebrochen(
        []() { static_cast<void>(zielkennung(ZIELKENNUNG_MAX)); }));
    PRUEFE(hat_abgebrochen([]() {
        static_cast<void>(zielkennung(static_cast<std::size_t>(ZIELKENNUNG_MAX) + 1));
    }));
    PRUEFE(enthaelt(letzte_meldung.data(), "Zielkennung"));
    std::printf("    Zielkennung daneben: %s\n", letzte_meldung.data());

    // Eine Laengenangabe groesser als der Behaelter -- an beiden Wegen, die eine
    // Laenge entgegennehmen, und am Rand selbst noch nicht.
    Liste liste = SOLLFOLGE;
    PRUEFE(!hat_abgebrochen([&liste]() { ordne(liste, ANZAHL); }));
    PRUEFE(hat_abgebrochen([&liste]() { ordne(liste, ANZAHL + 1); }));
    PRUEFE(enthaelt(letzte_meldung.data(), "kern::aktion::ordne"));
    std::printf("    Laenge daneben: %s\n", letzte_meldung.data());
    PRUEFE(hat_abgebrochen(
        [&liste]() { static_cast<void>(in_kanonischer_ordnung(liste, ANZAHL + 1)); }));
    PRUEFE(enthaelt(letzte_meldung.data(), "kern::aktion::in_kanonischer_ordnung"));
    std::printf("    Laenge daneben: %s\n", letzte_meldung.data());
}

// ---------------------------------------------------------------------------
// Paket 0300 -- der Zustand, den diese Proben brauchen
// ---------------------------------------------------------------------------

/// Ein Zustand samt dem einen Startwertzugang, der ihn fuellt -- dieselbe Bauart wie in
/// der Werteprobe, und aus demselben Grund: Ein Zugang laesst sich an einen Zustand mit
/// gelaufener Runde nicht mehr binden, also leben beide gemeinsam.
///
/// **Ohne Grundbelegung.** Die Werteprobe setzt Wechselkurse und Sektorpreise, weil ihre
/// Formeln sonst an einer Bereichspruefung abbraechen. Die Pruefungen hier lesen genau
/// drei Adressarten -- Kasse, Positionsstufe, Beteiligungsanteil -- und keine davon
/// braucht einen Kurs. Ein voreingestellter Wert waere hier also nicht Vorsorge, sondern
/// eine Zahl, die in keiner Rechnung vorkommt.
class Rohling {
public:
    void lege(Index platz, i64 wert) { zugang_.setze(platz, wert); }

    operator const Zustand&() const { return zustand_; }

private:
    Zustand       zustand_;
    Startbelegung zugang_{zustand_};
};

/// Die Ordnungszahl eines Steckplatzes als Zielkennung der Art 1 (T32b, Art 1).
[[nodiscard]] std::size_t platz_als_ziel(Steckplatz platz)
{
    return static_cast<std::size_t>(platz);
}

/// Haengt eine Aktion an ein Buendel. Passt sie nicht mehr hinein, ist das ein Fehler
/// der Probe und nicht des Kerns -- er wird gemeldet und nicht verschwiegen.
void lege_dazu(Buendel& buendel, Art art, std::size_t ziel, i64 stufe)
{
    if (buendel.anzahl >= buendel.eintrag.size()) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: das Buendel fasst nicht mehr\n",
                     __LINE__);
        ++fehlgeschlagen;
        return;
    }
    buendel.eintrag[buendel.anzahl] = Aktion{art, zielkennung(ziel), stufe};
    ++buendel.anzahl;
}

/// Wie oft die Liste ein Angebot der Art `art` mit der Zielkennung `ziel` traegt.
[[nodiscard]] std::size_t wie_oft_angeboten(const Zulaessigkeitsliste& liste, Art art,
                                            std::size_t ziel)
{
    std::size_t treffer = 0;
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        if (liste.eintrag[k].art == art
            && static_cast<std::size_t>(liste.eintrag[k].ziel.wert) == ziel) {
            ++treffer;
        }
    }
    return treffer;
}

/// Der Parametersatz dieser Proben. **Eine einzige Zahl steht darin**, und sie ist so
/// gewaehlt, dass sich die Anteilsskala von Hand nachrechnen laesst: Bei einer
/// Stufenweite von 2.500 Zehntausendsteln sind vier Positionsstufen genau die ganze
/// Skala. Der Wert ist kein Vorschlag zur Kalibrierung -- der steht in der
/// Parameterdatei und ist dort als Platzhalter gekennzeichnet.
[[nodiscard]] Konstanten probe_konstanten()
{
    Konstanten konst{};
    konst.stufenweite = 2'500;
    return konst;
}

// ---------------------------------------------------------------------------
// Bedingung 5 -- die Liste einer Runde, ihre Laenge und ihre Ordnung
// ---------------------------------------------------------------------------

void probe_liste()
{
    const Konstanten konst = probe_konstanten();
    Rohling          roh;

    const Zulaessigkeitsliste liste = zulaessige_aktionen(roh, konst);

    // Die Kapazitaet zaehlt Plaetze, die Laenge Moeglichkeiten (T32b): genau einer.
    PRUEFE(liste.eintrag.size() == ANGEBOTE_HOECHSTENS);
    PRUEFE(liste.anzahl + 1 == ANGEBOTE_HOECHSTENS);
    std::printf("    %zu Angebote auf %zu Plaetzen\n", liste.anzahl, ANGEBOTE_HOECHSTENS);

    PRUEFE(in_kanonischer_ordnung(liste.eintrag, liste.anzahl));

    // Jeder Eintrag ist ein Angebot und keine Aktion: Art und Ziel, die Stufe offen.
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        PRUEFE(liste.eintrag[k].stufe == STUFE_OFFEN);
    }

    // Die Gegenprobe, die Bedingung 1 des Pakets verlangt: Dieselbe Menge in einer
    // anderen Reihenfolge ist **nicht** in der kanonischen Ordnung. Ohne sie bestuende
    // die Zusage oben auch gegen ein `in_kanonischer_ordnung`, das immer wahr sagt.
    Zulaessigkeitsliste gedreht = liste;
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        gedreht.eintrag[k] = liste.eintrag[liste.anzahl - 1 - k];
    }
    PRUEFE(!in_kanonischer_ordnung(gedreht.eintrag, gedreht.anzahl));

    // Und geordnet ist sie wieder dieselbe Folge -- Platz fuer Platz.
    ordne(gedreht.eintrag, gedreht.anzahl);
    PRUEFE(in_kanonischer_ordnung(gedreht.eintrag, gedreht.anzahl));
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        PRUEFE(gedreht.eintrag[k] == liste.eintrag[k]);
    }

    // **Der heutige Stand der beiden Argumente, festgehalten statt behauptet.** Keine
    // Vorgabe laesst die Liste an einer Zahl des Zustands oder an einem Parameter
    // haengen; der Kopf sagt das, und dieser Fall misst es. Wird die Liste eines Tages
    // von einer Vorgabe her zustandsabhaengig, wird er rot -- und das ist der Zweck.
    Rohling anders;
    anders.lege(stelle_fonds(FondsGroesse::Kasse), 12'345);
    anders.lege(stelle_position(Steckplatz::Sektor_CN_2), -7);
    anders.lege(stelle_beteiligung(Gebiet::BR, Sektor::Industrie, BeteiligungsFeld::Anteil),
                9'000);

    Konstanten andere_konstanten{};
    andere_konstanten.stufenweite = 9'999;

    const Zulaessigkeitsliste zweite = zulaessige_aktionen(anders, andere_konstanten);
    PRUEFE(zweite.anzahl == liste.anzahl);
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        PRUEFE(zweite.eintrag[k] == liste.eintrag[k]);
    }
}

// ---------------------------------------------------------------------------
// Bedingung 6 -- die fuenf Zielmengen aus T32b
// ---------------------------------------------------------------------------

void probe_zielmengen()
{
    // Die heutigen Werte, und daneben dieselben Zahlen aus den Konstanten des Zustands.
    // Beide Seiten stehen da, damit ein fuenftes Land sie **zugleich** bewegt: Wer nur
    // die linke Seite hielte, muesste sie von Hand nachziehen, und wer nur die rechte
    // hielte, pruefte eine Formel gegen sich selbst.
    PRUEFE(zielmenge(Art::Position) == 20);
    PRUEFE(zielmenge(Art::Beteiligung) == 12);
    PRUEFE(zielmenge(Art::Lobbybudget) == 16);
    PRUEFE(zielmenge(Art::Hebel) == 1);
    PRUEFE(zielmenge(Art::Sichtbarkeit) == 1);

    PRUEFE(zielmenge(Art::Position) == LAENDER * (SEKTOREN + 2));
    PRUEFE(zielmenge(Art::Beteiligung) == LAENDER * SEKTOREN);
    PRUEFE(zielmenge(Art::Lobbybudget) == LAENDER * INSTRUMENTE);

    // Die Zielmenge der Art 1 ist die Steckplatzmenge aus T16 -- dieselbe Groesse, an
    // zwei Stellen hergeleitet.
    PRUEFE(zielmenge(Art::Position) == STECKPLAETZE);
    PRUEFE(ANTEIL_HOECHSTENS == 10'000);

    const Konstanten konst = probe_konstanten();
    Rohling          roh;

    const Zulaessigkeitsliste liste = zulaessige_aktionen(roh, konst);

    // Je Art so viele Angebote wie Plaetze -- ausser bei der Art 1, der T16 einen Platz
    // nimmt.
    for (std::size_t k = 0; k < ARTEN; ++k) {
        const Art art =
            art_der_kennung(static_cast<i64>(ART_KENNUNG_ERSTE) + static_cast<i64>(k));

        std::size_t gezaehlt = 0;
        for (std::size_t e = 0; e < liste.anzahl; ++e) {
            if (liste.eintrag[e].art == art) {
                ++gezaehlt;
            }
        }

        const std::size_t erwartet =
            art == Art::Position ? zielmenge(art) - 1 : zielmenge(art);
        pruefe(gezaehlt == erwartet, "je Art so viele Angebote wie T32b Plaetze nennt",
               __LINE__);
        std::printf("    %-13s %2zu Plaetze, %2zu Angebote\n", art_name(art),
                    zielmenge(art), gezaehlt);
    }

    // Und eine Art, die keine ist, bekommt keine Zielmenge untergeschoben.
    PRUEFE(hat_abgebrochen(
        []() { static_cast<void>(zielmenge(static_cast<Art>(std::uint8_t{7}))); }));
    PRUEFE(enthaelt(letzte_meldung.data(), "T32b"));
}

// ---------------------------------------------------------------------------
// Bedingung 7 -- zwanzig Plaetze, neunzehn Angebote
// ---------------------------------------------------------------------------

void probe_der_leere_platz()
{
    const Konstanten konst = probe_konstanten();
    Rohling          roh;

    const Zulaessigkeitsliste liste = zulaessige_aktionen(roh, konst);

    // Der dauerhaft leere Platz, bei seiner Ordnungszahl genannt und nicht bei einer
    // Zahl: T16 haelt ihn am Namen fest, und der Name traegt die Zahl.
    const std::size_t leer = platz_als_ziel(Steckplatz::Waehrung_US);

    PRUEFE(STECKPLAETZE_SPIELBAR + 1 == STECKPLAETZE);

    // Aufgezaehlt und nicht gefegt: Jeder der zwanzig Plaetze wird einzeln gefragt, und
    // von neunzehn wird genau ein Angebot verlangt. Eine blosse Zaehlung der Art-1-
    // Eintraege bestuende auch gegen eine Liste, die einen Platz doppelt und einen gar
    // nicht anbietet.
    for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
        const std::size_t gezaehlt = wie_oft_angeboten(liste, Art::Position, p);
        const std::size_t erwartet = p == leer ? 0 : 1;
        pruefe(gezaehlt == erwartet,
               "jeder Steckplatz ausser dem leeren steht genau einmal in der Liste",
               __LINE__);
    }

    std::printf("    Steckplatz %zu (Waehrung USA) wird nicht angeboten, die uebrigen "
                "%zu je einmal\n",
                leer, STECKPLAETZE_SPIELBAR);
}

// ---------------------------------------------------------------------------
// Bedingung 8 -- die vier gebauten Bedingungen des Buendels
// ---------------------------------------------------------------------------

void probe_buendel()
{
    const Konstanten konst = probe_konstanten();

    Rohling roh;
    roh.lege(stelle_fonds(FondsGroesse::Kasse), 1'000);

    // --- mehr als drei Aktionen, und drei als Positivkontrolle am Rand -------------
    {
        Buendel drei;
        lege_dazu(drei, Art::Lobbybudget, 0, 10);
        lege_dazu(drei, Art::Lobbybudget, 1, 10);
        lege_dazu(drei, Art::Lobbybudget, 2, 10);
        PRUEFE(drei.anzahl == BUENDEL_AKTIONEN_HOECHSTENS);
        PRUEFE(buendel_einwand(roh, konst, drei) == Einwand::Keiner);

        Buendel vier = drei;
        lege_dazu(vier, Art::Lobbybudget, 3, 10);
        PRUEFE(vier.anzahl == BUENDEL_FASST);
        PRUEFE(buendel_einwand(roh, konst, vier) == Einwand::ZuVieleAktionen);
    }

    // --- dasselbe Ziel zweimal -----------------------------------------------------
    {
        Buendel doppelt;
        lege_dazu(doppelt, Art::Lobbybudget, 5, 10);
        lege_dazu(doppelt, Art::Lobbybudget, 5, -20);
        PRUEFE(buendel_einwand(roh, konst, doppelt) == Einwand::ZielDoppelt);

        // Positivkontrolle: dieselbe **Zahl** bei verschiedener Art ist ein anderes
        // Ziel. Eine Zielkennung ist der Platz in der Ordnung ihrer eigenen Art (T32b),
        // und eine Pruefung, die nur die Zahl vergliche, verboete hier grundlos.
        Buendel gemischt;
        lege_dazu(gemischt, Art::Position, 5, 1);
        lege_dazu(gemischt, Art::Lobbybudget, 5, 10);
        PRUEFE(buendel_einwand(roh, konst, gemischt) == Einwand::Keiner);
    }

    // --- Kasse ueberzogen, und der Rand selbst noch nicht --------------------------
    {
        Buendel am_rand;
        lege_dazu(am_rand, Art::Lobbybudget, 0, 1'000);
        PRUEFE(kassenbedarf(am_rand.eintrag[0]) == 1'000);
        PRUEFE(buendel_einwand(roh, konst, am_rand) == Einwand::Keiner);

        Buendel einen_darueber;
        lege_dazu(einen_darueber, Art::Lobbybudget, 0, 1'001);
        PRUEFE(buendel_einwand(roh, konst, einen_darueber) == Einwand::KasseUeberzogen);

        // Das Vorzeichen der Stufe ist nach T32b die Richtung und kein Rabatt.
        Buendel gegenrichtung;
        lege_dazu(gegenrichtung, Art::Lobbybudget, 0, -1'001);
        PRUEFE(kassenbedarf(gegenrichtung.eintrag[0]) == 1'001);
        PRUEFE(buendel_einwand(roh, konst, gegenrichtung) == Einwand::KasseUeberzogen);

        // Zwei, die je einzeln durchgehen und zusammen nicht -- die Pruefung sitzt auf
        // dem Buendel und nicht auf der Aktion.
        Buendel eine_haelfte;
        lege_dazu(eine_haelfte, Art::Lobbybudget, 0, 600);
        PRUEFE(buendel_zulaessig(roh, konst, eine_haelfte));

        Buendel beide_haelften;
        lege_dazu(beide_haelften, Art::Lobbybudget, 0, 600);
        lege_dazu(beide_haelften, Art::Lobbybudget, 1, 600);
        PRUEFE(buendel_einwand(roh, konst, beide_haelften) == Einwand::KasseUeberzogen);

        // **Die gemeldete Luecke, als Fall und nicht als Satz.** Die Arten 1, 2 und 4
        // ziehen heute keine Kasse, weil keine Vorgabe einen Betrag nennt. Wer den
        // Anspruch baut, macht diesen Fall rot -- und genau daran soll er auffallen.
        Buendel ohne_anspruch;
        lege_dazu(ohne_anspruch, Art::Hebel, 0, kern::festkomma::I64_MAX);
        PRUEFE(kassenbedarf(ohne_anspruch.eintrag[0]) == 0);
        PRUEFE(buendel_einwand(roh, konst, ohne_anspruch) == Einwand::Keiner);
    }

    // --- der Fondsanteil ueber der Anteilsskala ------------------------------------
    {
        // Bei einer Stufenweite von 2.500 sind vier Stufen genau die ganze Skala.
        Buendel am_rand;
        lege_dazu(am_rand, Art::Position, platz_als_ziel(Steckplatz::Sektor_US_1), 4);
        PRUEFE(buendel_einwand(roh, konst, am_rand) == Einwand::Keiner);

        Buendel einen_darueber;
        lege_dazu(einen_darueber, Art::Position, platz_als_ziel(Steckplatz::Sektor_US_1),
                  5);
        PRUEFE(buendel_einwand(roh, konst, einen_darueber)
               == Einwand::AnteilUeberDerSkala);

        // Der Betrag zaehlt, nicht das Vorzeichen (T48 Nr. 14): Ein grosser Short bewegt
        // den Markt so stark wie ein grosser Long.
        Buendel kurze_seite;
        lege_dazu(kurze_seite, Art::Position, platz_als_ziel(Steckplatz::Sektor_US_1), -5);
        PRUEFE(buendel_einwand(roh, konst, kurze_seite) == Einwand::AnteilUeberDerSkala);

        // Eine Position auf einem Waehrungsplatz traegt keinen Korbanteil und faellt
        // deshalb in keine der zwoelf Rechnungen.
        Buendel auf_waehrung;
        lege_dazu(auf_waehrung, Art::Position, platz_als_ziel(Steckplatz::Waehrung_CN),
                  1'000'000);
        PRUEFE(buendel_einwand(roh, konst, auf_waehrung) == Einwand::Keiner);
    }

    // --- angeboten oder nicht: der leere Platz und eine Zahl jenseits ihrer Menge ---
    {
        Buendel auf_den_leeren;
        lege_dazu(auf_den_leeren, Art::Position, platz_als_ziel(Steckplatz::Waehrung_US),
                  1);
        PRUEFE(buendel_einwand(roh, konst, auf_den_leeren) == Einwand::NichtAngeboten);

        Buendel der_nachbar;
        lege_dazu(der_nachbar, Art::Position, platz_als_ziel(Steckplatz::Waehrung_CN), 1);
        PRUEFE(buendel_einwand(roh, konst, der_nachbar) == Einwand::Keiner);

        // Die Arten 4 und 5 haben genau einen Platz, und der traegt die Null.
        Buendel jenseits;
        lege_dazu(jenseits, Art::Hebel, 1, 1);
        PRUEFE(buendel_einwand(roh, konst, jenseits) == Einwand::NichtAngeboten);

        Buendel der_eine_platz;
        lege_dazu(der_eine_platz, Art::Sichtbarkeit, 0, 1);
        PRUEFE(buendel_einwand(roh, konst, der_eine_platz) == Einwand::Keiner);
    }

    // --- die Laengenangabe jenseits der Kapazitaet ---------------------------------
    {
        Buendel zu_lang;
        zu_lang.anzahl = BUENDEL_FASST + 1;
        PRUEFE(hat_abgebrochen([&roh, &konst, &zu_lang]() {
            static_cast<void>(buendel_einwand(roh, konst, zu_lang));
        }));
        PRUEFE(enthaelt(letzte_meldung.data(), "kern::aktion::buendel_einwand"));
        std::printf("    Laenge daneben: %s\n", letzte_meldung.data());
    }

    // --- die Namen der Einwaende ---------------------------------------------------
    for (std::size_t e = 0; e < EINWAENDE; ++e) {
        const Einwand einwand = static_cast<Einwand>(static_cast<std::uint8_t>(e));
        std::printf("    Einwand %zu: %s\n", e, einwand_name(einwand));
    }
    PRUEFE(hat_abgebrochen([]() {
        static_cast<void>(einwand_name(static_cast<Einwand>(std::uint8_t{9})));
    }));
    PRUEFE(enthaelt(letzte_meldung.data(), "kern::aktion"));
}

// ---------------------------------------------------------------------------
// Bedingung 9 -- der Satz, mit dem T32 die Pruefung auf das Buendel legt
// ---------------------------------------------------------------------------

void probe_der_satz_aus_t32()
{
    const Konstanten konst = probe_konstanten();
    Rohling          roh;
    roh.lege(stelle_fonds(FondsGroesse::Kasse), 1'000);

    const std::size_t us_1 = platz_als_ziel(Steckplatz::Sektor_US_1);

    // Drei Aufstockungen desselben Steckplatzes: jede fuer sich zulaessig ...
    Buendel einzeln;
    lege_dazu(einzeln, Art::Beteiligung, us_1, 4'000);
    PRUEFE(buendel_zulaessig(roh, konst, einzeln));

    // ... das Buendel nicht.
    Buendel dreimal;
    lege_dazu(dreimal, Art::Beteiligung, us_1, 4'000);
    lege_dazu(dreimal, Art::Beteiligung, us_1, 4'000);
    lege_dazu(dreimal, Art::Beteiligung, us_1, 4'000);
    PRUEFE(!buendel_zulaessig(roh, konst, dreimal));

    // Genannt wird der erste Einwand der festgelegten Reihenfolge, und das ist hier das
    // doppelte Ziel. Die 12.000 laegen ebenso ueber der Skala; ein Buendel mit zwei
    // Maengeln bekommt einen Grund genannt und nicht zwei.
    PRUEFE(buendel_einwand(roh, konst, dreimal) == Einwand::ZielDoppelt);
    std::printf("    drei Aufstockungen desselben Steckplatzes: %s\n",
                einwand_name(buendel_einwand(roh, konst, dreimal)));

    // **Derselbe Satz ohne das doppelte Ziel**, damit die Anteilsskala ihn allein traegt:
    // Position und Beteiligung sind zwei verschiedene Ziele und derselbe Korb (T48
    // Nr. 14). Jede der beiden allein ist zulaessig, zusammen sind sie es nicht.
    Buendel nur_position;
    lege_dazu(nur_position, Art::Position, us_1, 2);
    PRUEFE(buendel_zulaessig(roh, konst, nur_position));

    Buendel nur_beteiligung;
    lege_dazu(nur_beteiligung, Art::Beteiligung, us_1, 5'001);
    PRUEFE(buendel_zulaessig(roh, konst, nur_beteiligung));

    Buendel beide;
    lege_dazu(beide, Art::Position, us_1, 2);
    lege_dazu(beide, Art::Beteiligung, us_1, 5'001);
    PRUEFE(buendel_einwand(roh, konst, beide) == Einwand::AnteilUeberDerSkala);

    // Und der Rand: 5.000 statt 5.001 gehen zusammen gerade noch durch.
    Buendel beide_am_rand;
    lege_dazu(beide_am_rand, Art::Position, us_1, 2);
    lege_dazu(beide_am_rand, Art::Beteiligung, us_1, 5'000);
    PRUEFE(buendel_einwand(roh, konst, beide_am_rand) == Einwand::Keiner);

    // --- dieselbe Formel, gegen die Funktion des Kerns gehalten --------------------
    //
    // Die Skalenpruefung rechnet T48 Nr. 14 mit den Zahlen **nach** dem Buendel. Damit
    // das keine zweite Fassung derselben Formel wird, steht hier ein Zustand, dessen
    // Fondsanteil die Funktion des Kerns selbst nennt -- und daneben die beiden
    // Buendel, die von dort aus nach oben und nach unten fuehren.
    Rohling besetzt;
    besetzt.lege(stelle_position(Steckplatz::Sektor_DE_2), -3);
    besetzt.lege(
        stelle_beteiligung(Gebiet::DE, Sektor::Industrie, BeteiligungsFeld::Anteil), 1'500);
    PRUEFE(fondsanteil(besetzt, konst, Gebiet::DE, Sektor::Industrie) == 9'000);

    const std::size_t de_2 = platz_als_ziel(Steckplatz::Sektor_DE_2);

    // Eine Stufe **tiefer** in den Short: der Betrag waechst auf 4, der Anteil auf
    // 11.500. Der Betrag liegt aussen, und eine Fortschreibung ueber die Summe der
    // Betraege saehe das nicht.
    Buendel tiefer;
    lege_dazu(tiefer, Art::Position, de_2, -1);
    PRUEFE(buendel_einwand(besetzt, konst, tiefer) == Einwand::AnteilUeberDerSkala);

    // Eine Stufe zurueck: der Betrag faellt auf 2, der Anteil auf 6.500.
    Buendel zurueck;
    lege_dazu(zurueck, Art::Position, de_2, 1);
    PRUEFE(buendel_einwand(besetzt, konst, zurueck) == Einwand::Keiner);

    std::printf("    Fondsanteil DE Industrie vor dem Buendel: %lld\n",
                static_cast<long long>(
                    fondsanteil(besetzt, konst, Gebiet::DE, Sektor::Industrie)));
    std::printf("    Die fuenfte Bedingung aus T32 ist nicht gebaut: der Groesse fuer "
                "die Schranke der Stufenzahl fehlt das Feld im Parametersatz.\n");
}

}  // namespace

int main()
{
    std::printf("Bedingung 1 -- die drei Schluessel und ihre Rangfolge:\n");
    probe_schluessel();
    std::printf("Bedingung 2 -- zwei Eingaben, eine Ausgabe:\n");
    probe_ordnung_der_liste();
    std::printf("Bedingung 3 -- streng, vollstaendig, uebertragbar:\n");
    probe_ordnungsgesetze();
    std::printf("Bedingung 4 -- die Griffe daneben:\n");
    probe_griffe_daneben();
    std::printf("Bedingung 5 -- die Liste einer Runde und ihre Ordnung:\n");
    probe_liste();
    std::printf("Bedingung 6 -- die fuenf Zielmengen aus T32b:\n");
    probe_zielmengen();
    std::printf("Bedingung 7 -- zwanzig Plaetze, neunzehn Angebote:\n");
    probe_der_leere_platz();
    std::printf("Bedingung 8 -- die vier Bedingungen des Buendels:\n");
    probe_buendel();
    std::printf("Bedingung 9 -- der Satz, mit dem T32 die Pruefung auf das Buendel "
                "legt:\n");
    probe_der_satz_aus_t32();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("aktion_probe: alle Pruefungen bestanden\n");
    return 0;
}
