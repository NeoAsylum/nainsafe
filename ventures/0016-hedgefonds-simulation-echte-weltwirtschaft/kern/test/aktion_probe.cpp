//! Laufende Probe fuer `kern::aktion` -- die vier Bedingungen des Arbeitspakets 0146.
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

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("aktion_probe: alle Pruefungen bestanden\n");
    return 0;
}
