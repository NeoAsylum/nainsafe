//! Laufende Probe fuer `kern::schritt` -- die acht Bedingungen des Arbeitspakets 0033.
//!
//! Die Aufteilung der Sollmaske auf die sechs Schritte ist in `src/schritt.cpp` schon
//! als `static_assert` bewiesen (3 + 0 + 16 + 152 + 4 + 0 = 175). Diese Probe gibt es
//! fuer das, was ein `static_assert` nicht kann:
//!
//!   1. **Die gelaufene Runde.** Dass die Rundenendpruefung aus T38 haelt, sieht man
//!      nur, wenn eine Runde wirklich laeuft -- sie bricht hart ab, wenn eine
//!      Maskenadresse fehlt oder eine ausserhalb beruehrt wurde.
//!   2. **Die Abbrueche.** Der `spielmodus`, die negative Rundennummer und die nicht
//!      mehr zaehlbare sind Wuerfe, und ein Wurf laesst sich nur zur Laufzeit fangen.
//!      Beim `spielmodus` wird zusaetzlich der **Wortlaut** geprueft: Bedingung 7
//!      verlangt, dass die Meldung sagt, warum.
//!   3. **Der unabhaengige Erwartungswert.** Die Pruefsumme ueber die kanonische
//!      Byteform (T12) ist keine Zahl aus dem eigenen Code, sondern eine Eigenschaft,
//!      die aus der Bedeutung von `vortrag` folgt: Eine Runde, die nur vortraegt, laesst
//!      jeden der 310 Werte stehen.
//!   4. **Das Testprofil aus ADR 0011, Massnahme 2.** Sie linkt `kern_geprueft`, also
//!      dieselben Quellen mit den Sanitizern. Ein Sanitizer sieht nur, was wirklich
//!      laeuft.
//!   5. **Die Zahlen im Wortlaut.** Was diese Probe ausrechnet, schreibt sie hin.
//!
//! **Zu Bedingung 1 (die Signatur) und Bedingung 5 (der Schreibweg):** Beide sind
//! Mustervergleiche ueber `src/schritt.cpp` und `include/kern/schritt.hpp` und keine
//! Laufzeitfragen. Ihre Suchmuster stehen deshalb **in keiner der beiden Dateien** --
//! eine Datei, die ihr eigenes Suchmuster zitiert, laesst es nie leer ausgehen. Was die
//! Probe dazu beitragen kann, ist die Gegenrichtung: Sie ruft `schritt` mit genau drei
//! Argumenten (Zustand, Buendel, Modus) und bekommt beides zurueck, Zustand und Kette.
//! Ein viertes Argument gaebe es nicht zu uebergeben.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <span>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::schreiber::Bitfeld;
using kern::schreiber::Kette;
using kern::schreiber::Modus;
using kern::schreiber::UrsacheArt;
using kern::schreiber::Ursachensatz;
using kern::schreiber::sollmaske;
using kern::schreiber::sollmaskengroesse;

using kern::schritt::Aktionsbuendel;
using kern::schritt::Rundenergebnis;

using kern::zustand::FELDER;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::PartieFeld;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

using u64 = std::uint64_t;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// Ob `nadel` in `heuhaufen` vorkommt -- ohne `<string>`, das nach `sperre.hpp` keine
/// Kernquelle mehr einbinden darf.
bool enthaelt(const char* heuhaufen, const char* nadel)
{
    if (heuhaufen == nullptr || nadel == nullptr) {
        return false;
    }
    for (std::size_t i = 0; heuhaufen[i] != '\0'; ++i) {
        std::size_t j = 0;
        while (nadel[j] != '\0' && heuhaufen[i + j] == nadel[j]) {
            ++j;
        }
        if (nadel[j] == '\0') {
            return true;
        }
    }
    return false;
}

/// Die Pruefsumme des Zustands ueber die kanonische Byteform (T12) -- der unabhaengige
/// Erwartungswert aus Bedingung 6.
///
/// Gerechnet wird ueber `zustand::nach_bytes` und FNV-1a-64 aus `kern::pruefsumme`, also
/// ueber zwei Kaesten, die von `kern::schritt` nichts wissen. `zustand::pruefsumme_von`
/// rechnet dieselbe Summe auf dem kuerzeren Weg; die Probe stellt beide gegeneinander,
/// damit die Aussage nicht an einer einzigen Rechnung haengt.
u64 summe_von(const Zustand& welt)
{
    std::array<std::uint8_t, kern::zustand::BYTES> bytes{};
    kern::zustand::nach_bytes(welt, bytes);
    return kern::pruefsumme::fnv1a64(bytes);
}

/// Ein Musterwert je Adresse -- "beliebige Feldwerte" im Sinne von Bedingung 3.
///
/// Die acht Muster decken null, beide Vorzeichen, die Skala 10.000 aus `spiel.md` und
/// **beide Enden des `int64_t`** ab. Die Enden stehen bewusst drin: Eine Runde, die nur
/// vortraegt, darf an ihnen nichts rechnen, und der Sanitizer aus ADR 0011 Massnahme 2
/// saehe es, wenn doch.
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

/// Baut eine Ausgangslage mit Musterwerten auf allen 310 Adressen und `partie.runde` auf
/// `rundennummer`.
///
/// **Ein einziger Startwertzugang fuer alle 310 Adressen**, und `partie.runde` zuletzt:
/// Der Riegel aus Paket 0027 greift beim Binden und nicht bei jedem `setze` -- genau
/// deshalb, weil `partie.runde` selbst zu der Menge gehoert, die eine Startbelegung
/// setzt. Ein Zugang je Aufruf haette sich nach der ersten gesetzten Rundennummer selbst
/// die Tuer zugemacht.
Zustand ausgangslage(i64 rundennummer)
{
    Zustand welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, musterwert(platz));
    }
    zugang.setze(kern::zustand::stelle_partie(PartieFeld::Runde), rundennummer);
    return welt;
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)

namespace {

// ---------------------------------------------------------------------------
// Bedingung 2 -- die Maskengroesse stimmt aus unabhaengiger Quelle
// ---------------------------------------------------------------------------
//
// Die beiden Zahlen stehen ausgeschrieben in der Tabelle von T38 samt Nachrechnung
// (108 + 22 + 40 + 2 + 3 = 175), nicht in diesem Paket. Gefragt wird `kern::schreiber`,
// also der Kasten, der die Maske fuehrt -- nicht `kern::schritt`.

void probe_maskengroesse()
{
    PRUEFE(sollmaskengroesse(Modus::Weltlauf) == 175);
    PRUEFE(sollmaskengroesse(Modus::Spielmodus) == 310);
    PRUEFE(108 + 22 + 40 + 2 + 3 == 175);
    std::printf("  Sollmaske weltlauf = %zu, spielmodus = %zu (erwartet 175 und 310)\n",
                sollmaskengroesse(Modus::Weltlauf), sollmaskengroesse(Modus::Spielmodus));
}

// ---------------------------------------------------------------------------
// Bedingung 4 -- die Kette hat 175 Glieder, und jedes ist ein Vortrag
// ---------------------------------------------------------------------------

/// Geht alle Glieder durch. Statt je Glied eine eigene Meldung zu setzen -- das waeren
/// im Fehlerfall 175 -- merkt sich die Probe **das erste** verletzte Glied je Aussage
/// und schreibt es hin. Eine Nummer ist ein Hinweis, ein Wall aus 175 Zeilen keiner.
void probe_kette(const Kette& kette, i64 erwartete_runde)
{
    PRUEFE(kette.laenge() == 175);

    constexpr std::size_t KEINS = 1000;  // liegt ausserhalb jeder moeglichen Gliednummer
    std::size_t erste_falsche_art = KEINS;
    std::size_t erste_falsche_quelle = KEINS;
    std::size_t erste_falsche_runde = KEINS;
    std::size_t erste_falsche_verzoegerung = KEINS;
    std::size_t erster_falscher_beitrag = KEINS;
    std::size_t erste_wertaenderung = KEINS;
    std::size_t erste_nicht_aufsteigende = KEINS;
    std::size_t erste_ausserhalb_maske = KEINS;

    const Bitfeld& maske = sollmaske(Modus::Weltlauf);
    bool voriges_gibt_es = false;
    Index voriges_ziel = 0;

    for (std::size_t n = 0; n < kette.laenge(); ++n) {
        const Ursachensatz& satz = kette.eintrag(n);

        if (satz.ursache.art() != UrsacheArt::Vortrag && erste_falsche_art == KEINS) {
            erste_falsche_art = n;
        }
        // Ein Vortrag traegt aus der eigenen Adresse vor -- die Aussage "unveraendert".
        if (satz.ursache.art() == UrsacheArt::Vortrag
            && satz.ursache.vortragsadresse() != satz.ziel && erste_falsche_quelle == KEINS) {
            erste_falsche_quelle = n;
        }
        if (satz.runde != erwartete_runde && erste_falsche_runde == KEINS) {
            erste_falsche_runde = n;
        }
        if (satz.verzoegerung != 0 && erste_falsche_verzoegerung == KEINS) {
            erste_falsche_verzoegerung = n;
        }
        if (satz.beitrag != 1000 && erster_falscher_beitrag == KEINS) {
            erster_falscher_beitrag = n;
        }
        if (satz.alt != satz.neu && erste_wertaenderung == KEINS) {
            erste_wertaenderung = n;
        }
        if (voriges_gibt_es && satz.ziel <= voriges_ziel && erste_nicht_aufsteigende == KEINS) {
            // "aufsteigend" schliesst "paarweise verschieden" ein: `<=` faengt beides.
            erste_nicht_aufsteigende = n;
        }
        if (!maske.steht(satz.ziel) && erste_ausserhalb_maske == KEINS) {
            erste_ausserhalb_maske = n;
        }

        voriges_ziel = satz.ziel;
        voriges_gibt_es = true;
    }

    PRUEFE(erste_falsche_art == KEINS);
    PRUEFE(erste_falsche_quelle == KEINS);
    PRUEFE(erste_falsche_runde == KEINS);
    PRUEFE(erste_falsche_verzoegerung == KEINS);
    PRUEFE(erster_falscher_beitrag == KEINS);
    PRUEFE(erste_wertaenderung == KEINS);
    PRUEFE(erste_nicht_aufsteigende == KEINS);
    PRUEFE(erste_ausserhalb_maske == KEINS);

    // Und die Gegenrichtung: Jede Adresse der Maske kommt in der Kette vor. Zusammen mit
    // "aufsteigend, paarweise verschieden" und der Laenge 175 ist die Kette damit genau
    // die Maske -- nicht 175 beliebige Adressen, die zufaellig in ihr liegen.
    std::size_t fehlende = 0;
    std::size_t erste_fehlende = FELDER;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (!maske.steht(platz)) {
            continue;
        }
        bool gefunden = false;
        for (std::size_t n = 0; n < kette.laenge() && !gefunden; ++n) {
            gefunden = kette.eintrag(n).ziel == platz;
        }
        if (!gefunden) {
            ++fehlende;
            if (erste_fehlende == FELDER) {
                erste_fehlende = platz;
            }
        }
    }
    PRUEFE(fehlende == 0);
    if (fehlende != 0) {
        std::fprintf(stderr, "  erste fehlende Maskenadresse: %zu (%s)\n", erste_fehlende,
                     kern::zustand::index_zu_adresse(erste_fehlende));
    }
}

// ---------------------------------------------------------------------------
// Bedingungen 3, 4 und 6 -- eine Runde laeuft durch, und die Welt steht still
// ---------------------------------------------------------------------------

void probe_eine_runde(i64 vorrundennummer)
{
    const Zustand vorher = ausgangslage(vorrundennummer);
    const u64 summe_vorher = summe_von(vorher);

    // Bedingung 3: kehrt zurueck, ohne abzubrechen. Der Aufruf selbst ist der Nachweis,
    // dass die Rundenendpruefung aus T38 gehalten hat.
    const Rundenergebnis ergebnis = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);

    // Bedingung 6: die Pruefsumme aendert sich nicht. Zwei Wege zur selben Zahl.
    const u64 summe_nachher = summe_von(ergebnis.neuer_zustand);
    PRUEFE(summe_vorher == summe_nachher);
    PRUEFE(summe_vorher == kern::zustand::pruefsumme_von(vorher));
    PRUEFE(summe_nachher == kern::zustand::pruefsumme_von(ergebnis.neuer_zustand));

    // Und dieselbe Aussage feldweise, damit ein Summenzusammenstoss sie nicht traegt.
    PRUEFE(ergebnis.neuer_zustand == vorher);

    std::printf("  Vorrunde %lld -> Runde %lld: Pruefsumme %016llx vorher, %016llx nachher\n",
                static_cast<long long>(vorrundennummer),
                static_cast<long long>(vorrundennummer + 1),
                static_cast<unsigned long long>(summe_vorher),
                static_cast<unsigned long long>(summe_nachher));

    probe_kette(ergebnis.kette_dieser_runde, vorrundennummer + 1);
    std::printf("  Kette: %zu Glieder (erwartet 175), Runde %lld an jedem Glied\n",
                ergebnis.kette_dieser_runde.laenge(),
                static_cast<long long>(vorrundennummer + 1));
}

void probe_runden()
{
    // Runde 1 auf einem Startzustand des Jahrgangs.
    probe_eine_runde(0);
    // Und am oberen Ende des Zaehlbaren: die letzte Runde, die sich noch zaehlen laesst.
    probe_eine_runde(kern::festkomma::I64_MAX - 1);
}

// ---------------------------------------------------------------------------
// T10 -- gleiches Ergebnis bei jedem Lauf
// ---------------------------------------------------------------------------
//
// `schritt` ist eine reine Funktion ohne gezogene Zahlen. Zwei Aufrufe auf derselben
// Ausgangslage muessen deshalb bis auf das letzte Kettenglied dasselbe liefern. Das ist
// heute billig zu haben und wird teuer, sobald ein Schritt rechnet -- die Probe steht
// hier, damit sie dann schon da ist.

void probe_zweimal_dasselbe()
{
    const Zustand vorher = ausgangslage(7);

    const Rundenergebnis erster = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);
    const Rundenergebnis zweiter = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);

    PRUEFE(erster.neuer_zustand == zweiter.neuer_zustand);
    PRUEFE(erster.kette_dieser_runde.laenge() == zweiter.kette_dieser_runde.laenge());

    std::size_t erstes_abweichendes = 1000;
    for (std::size_t n = 0; n < erster.kette_dieser_runde.laenge(); ++n) {
        if (!(erster.kette_dieser_runde.eintrag(n) == zweiter.kette_dieser_runde.eintrag(n))
            && erstes_abweichendes == 1000) {
            erstes_abweichendes = n;
        }
    }
    PRUEFE(erstes_abweichendes == 1000);
}

// ---------------------------------------------------------------------------
// Bedingung 7 -- der spielmodus bricht ab, und die Meldung sagt warum
// ---------------------------------------------------------------------------

void probe_spielmodus_bricht_ab()
{
    const Zustand welt = ausgangslage(3);

    bool geworfen = false;
    bool nennt_alle_310 = false;
    bool nennt_den_modus = false;
    bool nennt_die_fehlenden_pakete = false;

    try {
        static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Spielmodus));
    } catch (const std::domain_error& fehler) {
        geworfen = true;
        std::fprintf(stdout, "  Abbruch wie erwartet: %s\n", fehler.what());
        nennt_alle_310 = enthaelt(fehler.what(), "310");
        nennt_den_modus = enthaelt(fehler.what(), "spielmodus");
        nennt_die_fehlenden_pakete = enthaelt(fehler.what(), "kein Paket");
    }

    PRUEFE(geworfen);
    PRUEFE(nennt_alle_310);
    PRUEFE(nennt_den_modus);
    PRUEFE(nennt_die_fehlenden_pakete);
}

// ---------------------------------------------------------------------------
// Die Rundennummer -- die beiden Enden sterben, statt still weiterzuzaehlen
// ---------------------------------------------------------------------------
//
// Die Nummer dieser Runde ist `partie.runde` der Vorrunde plus eins. Beide Enden sind
// harte Fehler: Eine Runde vor der ersten gibt es nicht, und `I64_MAX + 1` waere mit
// `-fwrapv` ein Umbruch ins Negative -- also eine Rundennummer, die der `Schreiber`
// abwiese, mit einer Meldung, die die Ursache nicht mehr nennt.

void probe_rundennummer()
{
    for (const i64 nummer : {i64{-1}, kern::festkomma::I64_MIN, kern::festkomma::I64_MAX}) {
        const Zustand welt = ausgangslage(nummer);
        bool geworfen = false;
        try {
            static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Weltlauf));
        } catch (const std::domain_error& fehler) {
            geworfen = true;
            std::fprintf(stdout, "  Abbruch wie erwartet (partie.runde = %lld): %s\n",
                         static_cast<long long>(nummer), fehler.what());
        }
        pruefe(geworfen, "partie.runde ausserhalb des Zaehlbaren bricht ab", __LINE__);
    }
}

}  // namespace

int main()
{
    probe_maskengroesse();
    probe_runden();
    probe_zweimal_dasselbe();
    probe_spielmodus_bricht_ab();
    probe_rundennummer();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("schritt_probe: alle Pruefungen bestanden\n");
    return 0;
}
