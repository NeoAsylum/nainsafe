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
//! ## Die fuenf Pruefungen
//!
//!   1 Bauform der Liste: 126 Eintraege, `kennung == index`, `ai` aus `0..5`,
//!     `Sum ai = 5`, und die Folge ist **echt** lexikographisch aufsteigend.
//!   2 Die beiden Anker aus T36: `(1,1,1,1,1)` traegt die Kennung **76**, und die
//!     Kennungen **0 bis 5** sind genau die sechs Profile `(0,0,0,a4,a5)` -- "genau"
//!     in beide Richtungen, also auch: kein siebtes Profil ausserhalb `0..5` hat
//!     `a1 = a2 = a3 = 0`.
//!   3 Der Strategiekern ist vierwertig: **6** Profile ohne Kern, **120**
//!     klassifiziert, und kein Profil ohne Familienaktion traegt eine Klasse.
//!   4 **Die Abweichung zu Pruefung 3.** Derselbe Zaehler laeuft ein zweites Mal
//!     ueber einen absichtlich dreiwertigen Kern -- den, gegen den Befund 8
//!     geschrieben ist. Die Probe weist nach, dass Pruefung 3 ihn **verwirft**, und
//!     nennt Kennung und Vektor des Profils, an dem es auffaellt.
//!   5 **Die Abweichung zu Pruefung 1 und 2.** Dasselbe Praedikat laeuft ueber eine
//!     Liste, die lexikographisch ueber `(a5..a1)` statt ueber `(a1..a5)` geordnet
//!     ist. Sie zeigt nicht nur, dass die Pruefung rot wird, sondern **welche
//!     Bedingung sie faengt und welche sie durchlaesst**: Die Bauform bleibt heil,
//!     Anker 1 bleibt bei 76 (das Referenzprofil ist symmetrisch), gefangen wird sie
//!     von der Ordnungspruefung und von Anker 2.
//!
//! Eine Pruefung, die nie rot wird, prueft nichts; deshalb stehen beide falschen
//! Fassungen im Testcode und nicht im Modul.
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
// Die Bauformpruefung als Praedikat
// ---------------------------------------------------------------------------
//
// Alles, was Pruefung 1 und 2 ueber eine Profilliste feststellen, steht in dieser
// einen Funktion -- aus demselben Grund wie `zaehle_kerne` weiter unten: Pruefung 5
// legt sie auf eine absichtlich falsche Liste an, und nur so ist nachweisbar,
// dass die Vorfuehrung **denselben** Massstab benutzt und nicht einen milderen.

struct Bauformbefund {
    /// `kennung == Index`, `ai` aus `0..BUDGET`, `Summe ai == BUDGET`.
    bool bauform_heil = true;
    /// Die Folge ist echt lexikographisch aufsteigend.
    bool ordnung_heil = true;
    /// Die erste Kennung, an der die Ordnung kippt. `-1` heisst: keine.
    i64 ordnungsverstoss = -1;
    /// Anker 1: welche Kennung traegt `(1,1,1,1,1)`? `-1` heisst: nicht gefunden.
    i64 referenzkennung = -1;
    /// Anker 2: genau die Kennungen `0..5` haben `a1 = a2 = a3 = 0`.
    bool anker2_heil = true;
    /// Die erste Kennung, an der Anker 2 verletzt ist. `-1` heisst: keine.
    i64 anker2_verstoss = -1;
};

Bauformbefund pruefe_bauform(const Profilliste& liste)
{
    Bauformbefund befund;
    const Profil referenz = Profil{1, 1, 1, 1, 1};

    for (std::size_t i = 0; i < PROFILE; ++i) {
        const Profileintrag& eintrag = liste[i];

        if (eintrag.kennung != static_cast<i64>(i)) {
            befund.bauform_heil = false;
        }

        i64 summe = 0;
        for (std::size_t k = 0; k < ARTEN; ++k) {
            if (eintrag.anteile[k] < 0 || eintrag.anteile[k] > BUDGET) {
                befund.bauform_heil = false;
            }
            summe += eintrag.anteile[k];
        }
        if (summe != BUDGET) {
            befund.bauform_heil = false;
        }

        if (i > 0 && !lexikographisch_kleiner(liste[i - 1].anteile, eintrag.anteile)) {
            befund.ordnung_heil = false;
            if (befund.ordnungsverstoss < 0) {
                befund.ordnungsverstoss = static_cast<i64>(i);
            }
        }

        if (eintrag.anteile == referenz) {
            befund.referenzkennung = eintrag.kennung;
        }

        // "Genau" in beide Richtungen: unter 6 muss es zutreffen, ab 6 darf es nicht.
        if (!hat_familienaktion(eintrag.anteile) != (i < 6)) {
            befund.anker2_heil = false;
            if (befund.anker2_verstoss < 0) {
                befund.anker2_verstoss = static_cast<i64>(i);
            }
        }
    }

    return befund;
}

/// Pruefung 1 und 2 als ein Urteil. Bestanden heisst: Bauform heil, Ordnung echt
/// aufsteigend, `(1,1,1,1,1)` bei Kennung 76, und genau `0..5` ohne Familienaktion.
bool besteht_bauformpruefung(const Bauformbefund& befund)
{
    return befund.bauform_heil && befund.ordnung_heil
           && befund.referenzkennung == 76 && befund.anker2_heil;
}

// ---------------------------------------------------------------------------
// Die erste Abweichung: die Liste in umgekehrter Stellenordnung
// ---------------------------------------------------------------------------
//
// Wortgleich zu `erzeuge_profilliste`, mit **einer** Vertauschung: die aeusserste
// Schleife laeuft ueber `a5` statt ueber `a1`, die Ordnung also lexikographisch
// ueber `(a5..a1)` statt ueber `(a1..a5)`. Die Menge der 126 Vektoren bleibt
// dieselbe, Summe und Wertebereich bleiben heil -- nur die Reihenfolge kippt.
//
// Sie steht hier, weil Pruefung 1 und 2 sich sonst nicht selbst vorfuehren: Der
// dreiwertige Kern weiter unten ist die falsche Fassung fuer Pruefung 3, die beiden
// anderen haetten keine, und ein Test, der nie rot wird, prueft nichts.

Profilliste erzeuge_profilliste_umgekehrt()
{
    Profilliste liste{};
    std::size_t naechste = 0;

    for (i64 a5 = 0; a5 <= BUDGET; ++a5) {
        for (i64 a4 = 0; a4 <= BUDGET - a5; ++a4) {
            for (i64 a3 = 0; a3 <= BUDGET - a5 - a4; ++a3) {
                for (i64 a2 = 0; a2 <= BUDGET - a5 - a4 - a3; ++a2) {
                    const i64 a1 = BUDGET - a5 - a4 - a3 - a2;

                    // Indexpruefung an der Grenze -- dieselbe Vorsicht wie im Modul.
                    // Testcode, der hinter das Feldende schreibt, faelscht das
                    // Urteil, statt es zu faellen.
                    if (naechste >= PROFILE) {
                        return liste;
                    }

                    Profileintrag& eintrag = liste[naechste];
                    eintrag.kennung = static_cast<i64>(naechste);
                    eintrag.anteile = Profil{a1, a2, a3, a4, a5};
                    eintrag.kern = pruefstand::vorrat::strategiekern(eintrag.anteile);

                    ++naechste;
                }
            }
        }
    }

    return liste;
}

// ---------------------------------------------------------------------------
// Die zweite Abweichung: der dreiwertige Strategiekern
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

    const Bauformbefund bauform = pruefe_bauform(liste);
    pruefe(bauform.bauform_heil, "jeder Eintrag: kennung == Index, ai aus 0..5, Summe 5",
           __LINE__);
    pruefe(bauform.ordnung_heil, "die Folge ist echt lexikographisch aufsteigend", __LINE__);
    std::fprintf(stdout, "  kennung == Index          %s\n",
                 bauform.bauform_heil ? "ja" : "NEIN");
    std::fprintf(stdout, "  lexikographisch aufwaerts %s\n",
                 bauform.ordnung_heil ? "ja" : "NEIN");

    // -----------------------------------------------------------------------
    // Pruefung 2 -- die beiden Anker aus T36
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nAnker 1: das Referenzprofil (1,1,1,1,1)\n");

    const Profil referenz = Profil{1, 1, 1, 1, 1};
    if (bauform.referenzkennung >= 0) {
        const Profileintrag& treffer =
            liste[static_cast<std::size_t>(bauform.referenzkennung)];
        schreibe_profil("gefunden bei", treffer.kennung, treffer.anteile, treffer.kern);
    }
    std::fprintf(stdout, "  Kennung %lld (erwartet 76)\n",
                 static_cast<long long>(bauform.referenzkennung));
    pruefe(bauform.referenzkennung == 76, "(1,1,1,1,1) traegt die Kennung 76", __LINE__);
    pruefe(liste[76].anteile == referenz, "liste[76] ist (1,1,1,1,1)", __LINE__);

    std::fprintf(stdout, "\nAnker 2: die Kennungen 0 bis 5 sind genau die (0,0,0,a4,a5)\n");
    for (std::size_t i = 0; i < 6; ++i) {
        schreibe_profil("", liste[i].kennung, liste[i].anteile, liste[i].kern);
    }
    if (bauform.anker2_verstoss >= 0) {
        const Profileintrag& verstoss =
            liste[static_cast<std::size_t>(bauform.anker2_verstoss)];
        schreibe_profil("VERSTOSS", verstoss.kennung, verstoss.anteile, verstoss.kern);
    }
    pruefe(bauform.anker2_heil, "genau die Kennungen 0..5 haben a1 = a2 = a3 = 0", __LINE__);

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
    // Pruefung 5 -- die umgekehrte Stellenordnung wird verworfen
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nAbweichung: Ordnung ueber (a5..a1) statt (a1..a5)\n");

    const Profilliste umgekehrt = erzeuge_profilliste_umgekehrt();
    const Bauformbefund falsch = pruefe_bauform(umgekehrt);

    // Dieselbe Funktion, anderes Urteil -- das ist der ganze Nachweis.
    pruefe(besteht_bauformpruefung(bauform),
           "die echte Liste besteht die Bauformpruefung", __LINE__);
    pruefe(!besteht_bauformpruefung(falsch),
           "die Bauformpruefung VERWIRFT die umgekehrte Ordnung", __LINE__);

    std::fprintf(stdout, "  Bauform heil              %s (die echte Fassung: ja)\n",
                 falsch.bauform_heil ? "ja" : "NEIN");
    std::fprintf(stdout, "  lexikographisch aufwaerts %s (die echte Fassung: ja)\n",
                 falsch.ordnung_heil ? "ja" : "NEIN");
    pruefe(falsch.ordnungsverstoss >= 0,
           "die Ordnung kippt an einer benannten Kennung", __LINE__);
    if (falsch.ordnungsverstoss >= 0) {
        const Profileintrag& kipp =
            umgekehrt[static_cast<std::size_t>(falsch.ordnungsverstoss)];
        schreibe_profil("kippt bei", kipp.kennung, kipp.anteile, kipp.kern);
    }
    if (falsch.anker2_verstoss >= 0) {
        const Profileintrag& verstoss =
            umgekehrt[static_cast<std::size_t>(falsch.anker2_verstoss)];
        schreibe_profil("Anker 2 bricht", verstoss.kennung, verstoss.anteile, verstoss.kern);
    }

    // **Und was diese Abweichung ausdruecklich NICHT ausloest**, weil ein Test auch
    // sagen muss, was er durchlaesst: Die Bauform bleibt heil -- es sind dieselben
    // 126 Vektoren, nur anders sortiert. Und Anker 1 bleibt bei 76, weil
    // `(1,1,1,1,1)` sein eigenes Spiegelbild ist: Eine Umkehrung der Stellenordnung
    // kann ein symmetrisches Profil nicht verschieben. Anker 1 allein wuerde diesen
    // Fehler also **nicht** fangen -- genau dafuer gibt es Anker 2 und die
    // Ordnungspruefung daneben.
    pruefe(falsch.bauform_heil,
           "die Umkehrung laesst die Bauform heil -- sie trifft nur die Ordnung", __LINE__);
    pruefe(falsch.referenzkennung == 76,
           "Anker 1 bleibt bei 76: (1,1,1,1,1) ist symmetrisch", __LINE__);
    pruefe(!falsch.ordnung_heil, "gefangen wird sie von der Ordnungspruefung", __LINE__);
    pruefe(!falsch.anker2_heil, "und von Anker 2", __LINE__);

    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\n%s -- %d Pruefung(en) fehlgeschlagen\n",
                 fehlgeschlagen == 0 ? "bestanden" : "GESCHEITERT", fehlgeschlagen);
    return fehlgeschlagen == 0 ? 0 : 1;
}
