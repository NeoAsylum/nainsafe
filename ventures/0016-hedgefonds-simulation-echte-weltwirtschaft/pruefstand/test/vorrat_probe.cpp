//! Paket 0019 -- die Probe zu **Profilliste und Strategiekern** (T36).
//!
//! Vorgaben: T36 (Profilliste, Profilkennung, vierwertiger Strategiekern), T4 (kein
//! Gleitkomma), T13 (Kasten `pruefstand`); `spiel.md`, Abschnitt "Das Aktionsprofil
//! und wie es auf Aktionen wirkt", ist der Wortlaut. ADR 0011 fuer die Sprache.
//!
//! ## Was hier ausdruecklich NICHT geprueft wird
//!
//! `runde` und `spiele` -- das Vorratsverfahren aus T43 -- sind **Paket 0029**. Sie
//! sind im Kopf deklariert und nirgends definiert; das ist der Schnitt zwischen den
//! beiden Paketen und kein Fehler. Diese Probe ruft sie deshalb nicht auf, und sie
//! ruehrt `Abweichung` nicht an: Ein Aufruf machte den Kasten rot, bis 0029 gelaufen
//! ist. Ebenso wenig geprueft: die Zulaessigkeitsliste aus T32, die Bots, die drei
//! Masse, die Fensterlogik von Mass 3.
//!
//! ## Die vier Pruefungen
//!
//!   1 Bauform der Liste: 126 Eintraege, `kennung == index`, `ai` aus `0..5`,
//!     `Sum ai = 5`, und die Folge ist **echt** lexikographisch aufsteigend.
//!   2 Die beiden Anker aus T36: `(1,1,1,1,1)` traegt die Kennung **76**, und die
//!     Kennungen **0 bis 5** sind genau die sechs Profile `(0,0,0,a4,a5)` -- "genau"
//!     in beide Richtungen, also auch: kein siebtes Profil ausserhalb `0..5` hat
//!     `a1 = a2 = a3 = 0`.
//!   3 Der Strategiekern ist vierwertig: **6** Profile ohne Kern, **120**
//!     klassifiziert, und kein Profil ohne Familienaktion traegt eine Klasse.
//!   4 **Die Abweichung.** Derselbe Zaehler laeuft ein zweites Mal ueber einen
//!     absichtlich dreiwertigen Kern -- den, gegen den Befund 8 geschrieben ist. Die
//!     Probe weist nach, dass Pruefung 3 ihn **verwirft**, und nennt Kennung und
//!     Vektor des Profils, an dem es auffaellt. Eine Pruefung, die nie rot wird,
//!     prueft nichts; deshalb steht die falsche Fassung im Testcode und nicht im
//!     Modul.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <cstddef>
#include <cstdio>

#include "pruefstand/vorrat.hpp"

namespace {

using pruefstand::vorrat::ARTEN;
using pruefstand::vorrat::BUDGET;
using pruefstand::vorrat::i64;
using pruefstand::vorrat::Profil;
using pruefstand::vorrat::Profileintrag;
using pruefstand::vorrat::Profilliste;
using pruefstand::vorrat::PROFILE;
using pruefstand::vorrat::Strategiekern;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

const char* kernname(Strategiekern kern)
{
    switch (kern) {
        case Strategiekern::OHNE:        return "ohne";
        case Strategiekern::POSITION:    return "Position";
        case Strategiekern::BETEILIGUNG: return "Beteiligung";
        case Strategiekern::LOBBY:       return "Lobby";
    }
    return "?";
}

/// Kennung und Vektor in einer Zeile -- das Format, in dem die Anker und die
/// kernlosen Profile in der Ausgabe stehen muessen.
void schreibe_profil(const char* rand, i64 kennung, const Profil& anteile,
                     Strategiekern kern)
{
    std::fprintf(stdout, "  %-14s Kennung %3lld  (", rand,
                 static_cast<long long>(kennung));
    for (std::size_t i = 0; i < ARTEN; ++i) {
        std::fprintf(stdout, "%s%lld", i == 0 ? "" : ",",
                     static_cast<long long>(anteile[i]));
    }
    std::fprintf(stdout, ")  Kern %s\n", kernname(kern));
}

/// Echtes lexikographisches Kleiner ueber `(a1..a5)`. Nicht `<=`: Die Ordnung aus T36
/// ist streng, zwei gleiche Vektoren waeren ein Doppeleintrag.
bool lexikographisch_kleiner(const Profil& links, const Profil& rechts)
{
    for (std::size_t i = 0; i < ARTEN; ++i) {
        if (links[i] != rechts[i]) {
            return links[i] < rechts[i];
        }
    }
    return false;
}

/// Hat das Profil ueberhaupt eine Aktion aus `{1 Position, 2 Beteiligung, 3 Lobby}`?
/// Genau diese Profile duerfen einen Kern tragen -- und nur sie.
bool hat_familienaktion(const Profil& anteile)
{
    return anteile[0] > 0 || anteile[1] > 0 || anteile[2] > 0;
}

// ---------------------------------------------------------------------------
// Die Abweichung: der dreiwertige Strategiekern
// ---------------------------------------------------------------------------
//
// Wortgleich zu `pruefstand::vorrat::strategiekern`, **ohne** die Abfrage auf den
// leeren Kern. Genau das ist die Fassung, gegen die Befund 8 geschrieben ist: Sie
// zwingt den Gleichstandsbrecher, fuer `(0,0,0,a4,a5)` eine Positionsstrategie zu
// behaupten, in der keine Position vorkommt. Sie steht hier und nicht im Modul, weil
// eine falsche Fassung in den Testcode gehoert.

Strategiekern strategiekern_dreiwertig(const Profil& anteile)
{
    std::size_t bester = 0;
    for (std::size_t i = 1; i < 3; ++i) {
        if (anteile[i] > anteile[bester]) {
            bester = i;
        }
    }
    // Hier fehlt sie: `if (anteile[bester] == 0) return Strategiekern::OHNE;`
    return static_cast<Strategiekern>(static_cast<int>(bester) + 1);
}

using Kernfunktion = Strategiekern (*)(const Profil&);

/// Das Ergebnis einer Zaehlung ueber die Liste mit einer *beliebigen* Kernfunktion.
/// Weil dieselbe Zaehlung beide Fassungen misst, ist Pruefung 4 wirklich derselbe
/// Massstab und nicht ein zweiter, milderer.
struct Kernbefund {
    i64 ohne = 0;
    i64 klassifiziert = 0;
    /// Ein Profil ohne jede Familienaktion, dem trotzdem eine Klasse zugeteilt wurde.
    /// `kennung < 0` heisst: kein solches gefunden.
    i64 auffaellige_kennung = -1;
    Profil auffaelliger_vektor{};
    Strategiekern auffaelliger_kern = Strategiekern::OHNE;
};

Kernbefund zaehle_kerne(const Profilliste& liste, Kernfunktion kern)
{
    Kernbefund befund;
    for (const Profileintrag& eintrag : liste) {
        const Strategiekern gefunden = kern(eintrag.anteile);
        if (gefunden == Strategiekern::OHNE) {
            ++befund.ohne;
        } else {
            ++befund.klassifiziert;
            if (!hat_familienaktion(eintrag.anteile) && befund.auffaellige_kennung < 0) {
                befund.auffaellige_kennung = eintrag.kennung;
                befund.auffaelliger_vektor = eintrag.anteile;
                befund.auffaelliger_kern = gefunden;
            }
        }
    }
    return befund;
}

/// Pruefung 3 als Praedikat, damit Pruefung 4 sie auf die falsche Fassung anwenden
/// kann. Bestanden heisst: 6 ohne, 120 klassifiziert, kein kernloses Profil
/// klassifiziert.
bool besteht_kernpruefung(const Kernbefund& befund)
{
    return befund.ohne == 6 && befund.klassifiziert == 120
           && befund.auffaellige_kennung < 0;
}

}  // namespace

int main()
{
    const Profilliste liste = pruefstand::vorrat::erzeuge_profilliste();

    // -----------------------------------------------------------------------
    // Pruefung 1 -- Bauform und Ordnung
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "Profilliste (T36)\n");
    std::fprintf(stdout, "  Eintraege                 %zu (erwartet 126)\n", PROFILE);
    pruefe(PROFILE == 126, "PROFILE ist 126 = C(9,4)", __LINE__);

    bool bauform_heil = true;
    bool ordnung_heil = true;
    for (std::size_t i = 0; i < PROFILE; ++i) {
        const Profileintrag& eintrag = liste[i];

        if (eintrag.kennung != static_cast<i64>(i)) {
            bauform_heil = false;
        }

        i64 summe = 0;
        for (std::size_t k = 0; k < ARTEN; ++k) {
            if (eintrag.anteile[k] < 0 || eintrag.anteile[k] > BUDGET) {
                bauform_heil = false;
            }
            summe += eintrag.anteile[k];
        }
        if (summe != BUDGET) {
            bauform_heil = false;
        }

        if (i > 0 && !lexikographisch_kleiner(liste[i - 1].anteile, eintrag.anteile)) {
            ordnung_heil = false;
        }
    }
    pruefe(bauform_heil, "jeder Eintrag: kennung == Index, ai aus 0..5, Summe 5", __LINE__);
    pruefe(ordnung_heil, "die Folge ist echt lexikographisch aufsteigend", __LINE__);
    std::fprintf(stdout, "  kennung == Index          %s\n", bauform_heil ? "ja" : "NEIN");
    std::fprintf(stdout, "  lexikographisch aufwaerts %s\n", ordnung_heil ? "ja" : "NEIN");

    // -----------------------------------------------------------------------
    // Pruefung 2 -- die beiden Anker aus T36
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nAnker 1: das Referenzprofil (1,1,1,1,1)\n");

    const Profil referenz = Profil{1, 1, 1, 1, 1};
    i64 referenzkennung = -1;
    for (const Profileintrag& eintrag : liste) {
        if (eintrag.anteile == referenz) {
            referenzkennung = eintrag.kennung;
            schreibe_profil("gefunden bei", eintrag.kennung, eintrag.anteile, eintrag.kern);
        }
    }
    std::fprintf(stdout, "  Kennung %lld (erwartet 76)\n",
                 static_cast<long long>(referenzkennung));
    pruefe(referenzkennung == 76, "(1,1,1,1,1) traegt die Kennung 76", __LINE__);
    pruefe(liste[76].anteile == referenz, "liste[76] ist (1,1,1,1,1)", __LINE__);

    std::fprintf(stdout, "\nAnker 2: die Kennungen 0 bis 5 sind genau die (0,0,0,a4,a5)\n");
    bool anker2_heil = true;
    for (std::size_t i = 0; i < PROFILE; ++i) {
        const bool ohne_familie = !hat_familienaktion(liste[i].anteile);
        // "Genau" in beide Richtungen: unter 6 muss es zutreffen, ab 6 darf es nicht.
        if (ohne_familie != (i < 6)) {
            anker2_heil = false;
            schreibe_profil("VERSTOSS", liste[i].kennung, liste[i].anteile, liste[i].kern);
        }
        if (i < 6) {
            schreibe_profil("", liste[i].kennung, liste[i].anteile, liste[i].kern);
        }
    }
    pruefe(anker2_heil, "genau die Kennungen 0..5 haben a1 = a2 = a3 = 0", __LINE__);

    // -----------------------------------------------------------------------
    // Pruefung 3 -- der Strategiekern ist vierwertig
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nStrategiekern, vierwertig (T36)\n");

    // Der Kern, den die Liste **mitbringt**: nach T36 einmal je Profil gerechnet und
    // abgelegt. Dass er mit einem frischen Aufruf uebereinstimmt, ist die Pruefung,
    // ob "abgelegt" und "gerechnet" dasselbe sagen.
    bool abgelegt_heil = true;
    i64 ohne_abgelegt = 0;
    for (const Profileintrag& eintrag : liste) {
        if (eintrag.kern != pruefstand::vorrat::strategiekern(eintrag.anteile)) {
            abgelegt_heil = false;
        }
        if (eintrag.kern == Strategiekern::OHNE) {
            ++ohne_abgelegt;
        }
    }
    pruefe(abgelegt_heil, "der abgelegte Kern ist der gerechnete", __LINE__);

    const Kernbefund echt = zaehle_kerne(liste, &pruefstand::vorrat::strategiekern);
    std::fprintf(stdout, "  ohne Kern                 %lld (erwartet 6)\n",
                 static_cast<long long>(echt.ohne));
    std::fprintf(stdout, "  klassifiziert             %lld (erwartet 120)\n",
                 static_cast<long long>(echt.klassifiziert));
    pruefe(echt.ohne == 6, "genau 6 Profile tragen den Kern ohne", __LINE__);
    pruefe(echt.klassifiziert == 120, "genau 120 Profile sind klassifiziert", __LINE__);
    pruefe(ohne_abgelegt == 6, "auch abgelegt sind es 6 kernlose Profile", __LINE__);
    pruefe(besteht_kernpruefung(echt), "die echte Fassung besteht die Kernpruefung", __LINE__);

    std::fprintf(stdout, "  die sechs kernlosen Profile:\n");
    for (const Profileintrag& eintrag : liste) {
        if (eintrag.kern == Strategiekern::OHNE) {
            schreibe_profil("", eintrag.kennung, eintrag.anteile, eintrag.kern);
        }
    }

    // -----------------------------------------------------------------------
    // Pruefung 4 -- die Abweichung wird verworfen
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nAbweichung: dreiwertiger Strategiekern (Befund 8)\n");

    const Kernbefund dreiwertig = zaehle_kerne(liste, &strategiekern_dreiwertig);
    std::fprintf(stdout, "  ohne Kern                 %lld (die echte Fassung: 6)\n",
                 static_cast<long long>(dreiwertig.ohne));
    std::fprintf(stdout, "  klassifiziert             %lld (die echte Fassung: 120)\n",
                 static_cast<long long>(dreiwertig.klassifiziert));

    // Der eigentliche Nachweis: dieselbe Pruefung, anderes Urteil.
    pruefe(!besteht_kernpruefung(dreiwertig),
           "die Kernpruefung VERWIRFT den dreiwertigen Kern", __LINE__);

    pruefe(dreiwertig.auffaellige_kennung >= 0,
           "die Abweichung faellt an einem benannten Profil auf", __LINE__);

    if (dreiwertig.auffaellige_kennung >= 0) {
        schreibe_profil("verworfen an", dreiwertig.auffaellige_kennung,
                        dreiwertig.auffaelliger_vektor, dreiwertig.auffaelliger_kern);
        // Sie faellt am ersten kernlosen Profil auf, und die Klasse, die sie dort
        // behauptet, ist Position -- der Gleichstandsbrecher auf drei Nullen.
        pruefe(dreiwertig.auffaellige_kennung == 0,
               "sie faellt an Kennung 0 auf, dem ersten kernlosen Profil", __LINE__);
        pruefe(dreiwertig.auffaelliger_kern == Strategiekern::POSITION,
               "sie behauptet dort Position -- ohne jede Position im Profil", __LINE__);
    }

    // Und die Gegenprobe zur Gegenprobe: Auf den 120 klassifizierten Profilen sind
    // beide Fassungen einig. Die Abweichung ist genau die sechs -- nicht ein anderes
    // Verfahren, das zufaellig auch scheitert.
    bool einig_auf_120 = true;
    for (const Profileintrag& eintrag : liste) {
        if (hat_familienaktion(eintrag.anteile)
            && strategiekern_dreiwertig(eintrag.anteile) != eintrag.kern) {
            einig_auf_120 = false;
        }
    }
    pruefe(einig_auf_120,
           "auf den 120 klassifizierten Profilen sind beide Fassungen einig", __LINE__);
    std::fprintf(stdout, "  Unterschied genau auf den 6 kernlosen: %s\n",
                 einig_auf_120 ? "ja" : "NEIN");

    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\n%s -- %d Pruefung(en) fehlgeschlagen\n",
                 fehlgeschlagen == 0 ? "bestanden" : "GESCHEITERT", fehlgeschlagen);
    return fehlgeschlagen == 0 ? 0 : 1;
}
