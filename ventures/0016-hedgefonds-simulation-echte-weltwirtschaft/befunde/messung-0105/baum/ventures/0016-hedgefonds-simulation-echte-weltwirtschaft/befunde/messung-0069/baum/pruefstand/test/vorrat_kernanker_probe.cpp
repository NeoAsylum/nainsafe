//! Paket 0040 -- der **Kernanker**: welche Klasse ein Profil traegt (T36).
//!
//! Vorgaben: T36, Absatz "Strategiekern, vierwertig" -- "Aktionsart mit dem groessten
//! Anteil unter `{1 Position, 2 Beteiligung, 3 Lobby}`, Gleichstand nach kleinerer
//! Kennung; Hebel und Sichtbarkeit gehen nicht ein." Dazu T4 (kein Gleitkomma) und
//! T13 (Kasten `pruefstand`). ADR 0011 fuer die Sprache.
//!
//! ## Warum es diese Probe gibt
//!
//! `vorrat_probe.cpp` (Paket 0019) prueft **wie viele** Profile eine Klasse tragen --
//! 6 ohne, 120 klassifiziert -- und an genau einer Stelle, **welche**. Diese eine
//! Stelle vergleicht das Modul gegen `strategiekern_dreiwertig`, eine wortgleiche
//! Kopie desselben Verfahrens im selben Kopf. Zwei Mutationen des Moduls sterben
//! deshalb an nur einer einzigen Zusicherung, und stuende der Gleichstandsbrecher in
//! Modul *und* Kopie gleich falsch, liefe die Probe gruen.
//!
//! Diese Probe ist der fehlende **unabhaengige Massstab**: vier von Hand
//! nachgerechnete Profile mit hingeschriebener Klasse. Kein Vergleich gegen eine
//! zweite Rechnung, sondern gegen T36 im Wortlaut.
//!
//! ## Was hier ausdruecklich NICHT geprueft wird
//!
//! Die Bauform der Liste, ihre Ordnung und die Zaehlung 6/120 -- das ist Paket 0019
//! und steht in `vorrat_probe.cpp`. `runde`, `spiele` und `Abweichung` -- das
//! Vorratsverfahren aus T43 -- sind Paket 0029 und werden hier nicht angefasst.
//! Diese Probe ruft aus dem Modul genau zwei Dinge: `erzeuge_profilliste` und
//! `strategiekern`.
//!
//! ## Die drei Pruefungen
//!
//!   1 **Die vier Anker gegen den abgelegten Kern.** Je Anker beides: dass
//!     `liste[k].anteile` der von Hand abgezaehlte Vektor ist und dass
//!     `liste[k].kern` die von Hand nachgerechnete Klasse ist. Ohne die erste Haelfte
//!     pruefte man die Klasse eines Profils, das man nicht identifiziert hat.
//!   2 **Dieselben vier Anker gegen den frisch gerechneten Kern.** T36 verlangt, dass
//!     der Kern einmal je Profil gerechnet und mit der Liste abgelegt wird; hier
//!     steht, dass "abgelegt" und "gerechnet" dieselbe Klasse nennen -- und beide die
//!     hingeschriebene.
//!   3 **Die Abweichung.** Eine benannte, testeigene Zuteilung gibt den Gleichstand
//!     an die *groessere* Kennung. Dieselbe Ankerpruefung urteilt ueber sie und
//!     **verwirft** sie, mit Kennung und Vektor des ersten Ankers, an dem es
//!     auffaellt. Und die andere Haelfte des Nachweises, die genauso hierher gehoert:
//!     **zwei der vier Anker fangen sie nicht**, und das steht in der Ausgabe.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdio>

#include "pruefstand/vorrat.hpp"

namespace {

using pruefstand::vorrat::ARTEN;
using pruefstand::vorrat::i64;
using pruefstand::vorrat::Profil;
using pruefstand::vorrat::Profileintrag;
using pruefstand::vorrat::PROFILE;
using pruefstand::vorrat::Profilliste;
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

// ---------------------------------------------------------------------------
// Die vier Anker -- von Hand abgezaehlt, von Hand nachgerechnet
// ---------------------------------------------------------------------------
//
// Die Kennung ist der Index in der lexikographisch aufsteigenden Liste (T36), die
// Klasse folgt aus dem Satz aus T36 und aus nichts sonst. Beides steht hier als
// Festwert und wird nicht gerechnet -- **das ist der ganze Zweck dieser Datei**. Eine
// erwartete Klasse, die aus einer zweiten Fassung von `strategiekern` faellt, misst
// nur, ob zwei Abschriften desselben Gedankens uebereinstimmen.
//
// Das Abzaehlen der Kennungen zum Nachvollziehen: `a1` laeuft aussen und wechselt am
// langsamsten. Der Block `a1 = 0, a2 = 0` umfasst die Kennungen 0..20 mit den
// Teillaengen 6,5,4,3,2,1 fuer `a3 = 0..5` -- die letzte davon ist 20 = (0,0,5,0,0).
// `a1 = 0` endet bei 55 (C(8,3) = 56 Vektoren), also faengt `a1 = 1` bei 56 an:
// (1,0,0,0,4)..(1,0,0,4,0) sind 56..60. Und 76 ist das Referenzprofil (1,1,1,1,1),
// dieselbe Zahl, die Paket 0019 an zwei Stellen festnagelt.

struct Anker {
    /// Der Index in der Profilliste (T36), nullbasiert.
    i64 kennung;
    /// Der Vektor `(a1..a5)`, von Hand abgezaehlt.
    Profil anteile;
    /// Die Klasse nach T36, von Hand nachgerechnet. Ein Festwert, kein Ergebnis.
    Strategiekern kern;
    /// Die Klasse, die der Gleichstand an die **groessere** Kennung ergaebe --
    /// ebenfalls von Hand. Sie macht Pruefung 3 nachpruefbar: Ohne sie zeigte die
    /// Vorfuehrung nur, dass die Abweichung *irgendetwas anderes* liefert.
    Strategiekern kern_bei_abweichung;
    /// Was dieser Anker festnagelt -- der Grund, warum gerade er in der Liste steht.
    const char* nagelt_fest;
};

inline constexpr std::size_t ANKERZAHL = 4;

constexpr std::array<Anker, ANKERZAHL> ANKER = {{
    {20, Profil{0, 0, 5, 0, 0}, Strategiekern::LOBBY, Strategiekern::LOBBY,
     "Zuteilung ohne Gleichstand: Index 2 -> Kennung 3"},
    {44, Profil{0, 2, 2, 1, 0}, Strategiekern::BETEILIGUNG, Strategiekern::LOBBY,
     "Gleichstand Beteiligung(2) gegen Lobby(3) -> die kleinere"},
    {60, Profil{1, 0, 0, 4, 0}, Strategiekern::POSITION, Strategiekern::POSITION,
     "Hebel ist mit 4 der groesste Anteil und geht NICHT ein"},
    {76, Profil{1, 1, 1, 1, 1}, Strategiekern::POSITION, Strategiekern::LOBBY,
     "Dreifachgleichstand -> die kleinste Kennung"},
}};

/// Die Indexpruefung an der Grenze (ADR 0011), hier als Beweis statt als Abfrage:
/// Die vier Kennungen sind Festwerte, also laesst sich zur Uebersetzungszeit
/// entscheiden, ob sie in die Liste zeigen. Ein Zugriff, den der Uebersetzer schon
/// abgelehnt haette, kann zur Laufzeit nicht danebengreifen.
constexpr bool anker_kennungen_im_bereich()
{
    for (const Anker& anker : ANKER) {
        if (anker.kennung < 0 || anker.kennung >= static_cast<i64>(PROFILE)) {
            return false;
        }
    }
    return true;
}

static_assert(anker_kennungen_im_bereich(),
              "Eine Ankerkennung zeigt nicht in die Profilliste.");

/// Kennung, Vektor, gefundene und erwartete Klasse in einer Zeile -- das Format, das
/// die Abnahme fuer jeden Anker verlangt.
void schreibe_anker(const char* rand, const Anker& anker,
                    Strategiekern gefunden, Strategiekern erwartet)
{
    std::fprintf(stdout, "  %-14s Kennung %3lld  (", rand,
                 static_cast<long long>(anker.kennung));
    for (std::size_t i = 0; i < ARTEN; ++i) {
        std::fprintf(stdout, "%s%lld", i == 0 ? "" : ",",
                     static_cast<long long>(anker.anteile[i]));
    }
    std::fprintf(stdout, ")  gefunden %-11s  erwartet %-11s  %s\n",
                 kernname(gefunden), kernname(erwartet), anker.nagelt_fest);
}

// ---------------------------------------------------------------------------
// Die Ankerpruefung als Praedikat
// ---------------------------------------------------------------------------
//
// Alles, was ueber eine Klassenzuteilung festgestellt wird, steht in dieser einen
// Funktion. Der Grund ist derselbe wie bei `zaehle_kerne` in `vorrat_probe.cpp`:
// Pruefung 3 legt sie auf eine absichtlich falsche Zuteilung an, und nur so ist
// nachweisbar, dass die Vorfuehrung **denselben** Massstab benutzt und nicht einen
// milderen.

/// Die vier an den Ankern gefundenen Klassen, in der Reihenfolge der Ankertabelle.
using Klassenfund = std::array<Strategiekern, ANKERZAHL>;

struct Ankerbefund {
    /// `liste[k]` traegt die Kennung `k` und den von Hand abgezaehlten Vektor.
    bool vektoren_heil = true;
    /// Die erste Kennung, an der der Vektor nicht stimmt. `-1` heisst: keine.
    i64 vektorverstoss = -1;
    /// Alle vier Klassen sind die von Hand nachgerechneten.
    bool klassen_heil = true;
    /// Die erste Kennung, an der die Klasse abweicht. `-1` heisst: keine.
    i64 erster_klassenverstoss = -1;
    /// Je Anker: weicht seine Klasse ab? Damit die Ausgabe auch sagen kann, welche
    /// Anker eine Abweichung **durchlassen**.
    std::array<bool, ANKERZAHL> weicht_ab{};
    int abweichende = 0;
};

Ankerbefund pruefe_anker(const Profilliste& liste, const Klassenfund& gefunden)
{
    Ankerbefund befund;

    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Anker& anker = ANKER[i];
        const Profileintrag& eintrag = liste[static_cast<std::size_t>(anker.kennung)];

        // Die erste Haelfte: Ist das ueberhaupt das Profil, das ich meine? Verglichen
        // wird der ganze Vektor gegen den hingeschriebenen, nicht eine Stelle gegen
        // eine andere.
        if (eintrag.kennung != anker.kennung || !(eintrag.anteile == anker.anteile)) {
            befund.vektoren_heil = false;
            if (befund.vektorverstoss < 0) {
                befund.vektorverstoss = anker.kennung;
            }
        }

        // Die zweite Haelfte, und sie ist die neue: Traegt es die Klasse aus T36?
        if (gefunden[i] != anker.kern) {
            befund.klassen_heil = false;
            befund.weicht_ab[i] = true;
            ++befund.abweichende;
            if (befund.erster_klassenverstoss < 0) {
                befund.erster_klassenverstoss = anker.kennung;
            }
        }
    }

    return befund;
}

/// Die Ankerpruefung als ein Urteil. Bestanden heisst: alle vier Profile sind die,
/// die sie sein sollen, und alle vier tragen die Klasse aus T36.
bool besteht_ankerpruefung(const Ankerbefund& befund)
{
    return befund.vektoren_heil && befund.klassen_heil;
}

/// Die Klassen, die die Liste **mitbringt** -- nach T36 einmal je Profil gerechnet
/// und abgelegt.
Klassenfund fund_abgelegt(const Profilliste& liste)
{
    Klassenfund fund{};
    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        fund[i] = liste[static_cast<std::size_t>(ANKER[i].kennung)].kern;
    }
    return fund;
}

/// Die Klassen aus einem frischen Aufruf von `strategiekern`.
Klassenfund fund_gerechnet(const Profilliste& liste)
{
    Klassenfund fund{};
    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Profileintrag& eintrag =
            liste[static_cast<std::size_t>(ANKER[i].kennung)];
        fund[i] = pruefstand::vorrat::strategiekern(eintrag.anteile);
    }
    return fund;
}

// ---------------------------------------------------------------------------
// Die Abweichung: Gleichstand an die groessere Kennung
// ---------------------------------------------------------------------------
//
// **Hergeleitet, nicht nachgebaut.** Ein zweites `strategiekern` im Testcode waere
// genau der Befund, gegen den dieses Paket geschrieben ist -- also entsteht die
// falsche Zuteilung hier durch eine Spiegelung des Profils und nicht durch eine
// zweite Fassung des Verfahrens.
//
// Warum das dieselbe Sache ist, in einem Satz: Das Modul waehlt den **kleinsten**
// Index unter den drei Familienstellen mit dem groessten Anteil. Vertauscht man
// `(a1,a2,a3)` zu `(a3,a2,a1)`, wird aus dem kleinsten Index der groesste -- Index `j`
// der gespiegelten Stellen ist Index `2-j` der urspruenglichen --, und die Klasse
// spiegelt sich mit: Position und Lobby tauschen, Beteiligung bleibt in der Mitte,
// und `ohne` bleibt `ohne`, weil eine Spiegelung drei Nullen nicht veraendert.
// Hebel und Sichtbarkeit bleiben stehen, wo sie sind; sie gehen nach T36 ohnehin
// nicht ein, und so bleibt der gespiegelte Vektor ein gueltiges Profil mit Summe 5.
//
// In dieser Funktion wird kein Anteil gegen einen anderen verglichen. Sie liest fuenf
// Stellen und schreibt sie in anderer Ordnung hin -- den Gleichstandsbrecher selbst
// gibt es hier nirgends.

Strategiekern spiegele_klasse(Strategiekern kern)
{
    switch (kern) {
        case Strategiekern::OHNE:        return Strategiekern::OHNE;
        case Strategiekern::POSITION:    return Strategiekern::LOBBY;
        case Strategiekern::BETEILIGUNG: return Strategiekern::BETEILIGUNG;
        case Strategiekern::LOBBY:       return Strategiekern::POSITION;
    }
    return Strategiekern::OHNE;
}

Strategiekern kern_gleichstand_an_groessere(const Profil& anteile)
{
    const Profil gespiegelt =
        Profil{anteile[2], anteile[1], anteile[0], anteile[3], anteile[4]};
    return spiegele_klasse(pruefstand::vorrat::strategiekern(gespiegelt));
}

Klassenfund fund_abweichend(const Profilliste& liste)
{
    Klassenfund fund{};
    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Profileintrag& eintrag =
            liste[static_cast<std::size_t>(ANKER[i].kennung)];
        fund[i] = kern_gleichstand_an_groessere(eintrag.anteile);
    }
    return fund;
}

}  // namespace

int main()
{
    const Profilliste liste = pruefstand::vorrat::erzeuge_profilliste();

    // -----------------------------------------------------------------------
    // Pruefung 1 -- die vier Anker gegen den abgelegten Kern
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "Kernanker (T36) -- welche Klasse ein Profil traegt\n");
    std::fprintf(stdout, "  vier Anker, Kennung und Klasse von Hand nachgerechnet\n\n");

    std::fprintf(stdout, "Pruefung 1: der abgelegte Kern (liste[k].kern)\n");

    const Klassenfund abgelegt = fund_abgelegt(liste);
    const Ankerbefund befund_abgelegt = pruefe_anker(liste, abgelegt);

    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Anker& anker = ANKER[i];
        const Profileintrag& eintrag =
            liste[static_cast<std::size_t>(anker.kennung)];

        schreibe_anker(befund_abgelegt.weicht_ab[i] ? "VERSTOSS" : "", anker,
                       abgelegt[i], anker.kern);

        char text[192];

        std::snprintf(text, sizeof(text),
                      "Kennung %lld traegt den von Hand abgezaehlten Vektor",
                      static_cast<long long>(anker.kennung));
        pruefe(eintrag.anteile == anker.anteile, text, __LINE__);

        std::snprintf(text, sizeof(text),
                      "Kennung %lld traegt abgelegt die Klasse %s (gefunden: %s)",
                      static_cast<long long>(anker.kennung), kernname(anker.kern),
                      kernname(abgelegt[i]));
        pruefe(abgelegt[i] == anker.kern, text, __LINE__);
    }

    pruefe(befund_abgelegt.vektoren_heil,
           "alle vier Anker zeigen auf das Profil, das sie meinen", __LINE__);
    pruefe(besteht_ankerpruefung(befund_abgelegt),
           "der abgelegte Kern besteht die Ankerpruefung", __LINE__);

    // -----------------------------------------------------------------------
    // Pruefung 2 -- dieselben Anker gegen den frisch gerechneten Kern
    // -----------------------------------------------------------------------
    //
    // T36 legt den Kern **einmal je Profil** ab. Hier steht, dass die Ablage und ein
    // frischer Aufruf dieselbe Klasse nennen -- und zwar beide die hingeschriebene.
    // Zwei Abschriften, die uebereinstimmen, waeren kein Nachweis; drei Werte, von
    // denen einer von Hand kommt, schon.
    std::fprintf(stdout, "\nPruefung 2: der frisch gerechnete Kern (strategiekern)\n");

    const Klassenfund gerechnet = fund_gerechnet(liste);
    const Ankerbefund befund_gerechnet = pruefe_anker(liste, gerechnet);

    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Anker& anker = ANKER[i];

        schreibe_anker(befund_gerechnet.weicht_ab[i] ? "VERSTOSS" : "", anker,
                       gerechnet[i], anker.kern);

        char text[192];
        std::snprintf(text, sizeof(text),
                      "Kennung %lld rechnet die Klasse %s (gefunden: %s)",
                      static_cast<long long>(anker.kennung), kernname(anker.kern),
                      kernname(gerechnet[i]));
        pruefe(gerechnet[i] == anker.kern, text, __LINE__);

        std::snprintf(text, sizeof(text),
                      "Kennung %lld: abgelegt und gerechnet nennen dieselbe Klasse",
                      static_cast<long long>(anker.kennung));
        pruefe(gerechnet[i] == abgelegt[i], text, __LINE__);
    }

    pruefe(besteht_ankerpruefung(befund_gerechnet),
           "der gerechnete Kern besteht die Ankerpruefung", __LINE__);

    // -----------------------------------------------------------------------
    // Pruefung 3 -- die Abweichung wird verworfen
    // -----------------------------------------------------------------------
    std::fprintf(stdout,
                 "\nPruefung 3: Abweichung -- Gleichstand an die GROESSERE Kennung\n");

    const Klassenfund abweichend = fund_abweichend(liste);
    const Ankerbefund befund_abweichend = pruefe_anker(liste, abweichend);

    // Erst der Nachweis, dass die Abweichung wirklich die benannte ist und nicht
    // irgendeine andere: Ihre vier Klassen sind die von Hand nachgerechneten der
    // Regel "Gleichstand an die groessere Kennung".
    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        const Anker& anker = ANKER[i];

        schreibe_anker(befund_abweichend.weicht_ab[i] ? "gefangen" : "durchgelassen",
                       anker, abweichend[i], anker.kern);

        char text[192];
        std::snprintf(text, sizeof(text),
                      "die Abweichung liefert bei Kennung %lld %s, wie von Hand "
                      "gerechnet (gefunden: %s)",
                      static_cast<long long>(anker.kennung),
                      kernname(anker.kern_bei_abweichung), kernname(abweichend[i]));
        pruefe(abweichend[i] == anker.kern_bei_abweichung, text, __LINE__);
    }

    // Und dann der eigentliche Nachweis: dieselbe Pruefung, anderes Urteil.
    pruefe(!besteht_ankerpruefung(befund_abweichend),
           "die Ankerpruefung VERWIRFT den Gleichstand an die groessere Kennung",
           __LINE__);

    std::fprintf(stdout, "\n  Urteil echter Kern      %s\n",
                 besteht_ankerpruefung(befund_abgelegt) ? "bestanden" : "VERWORFEN");
    std::fprintf(stdout, "  Urteil Abweichung       %s\n",
                 besteht_ankerpruefung(befund_abweichend) ? "bestanden" : "VERWORFEN");

    // Die Abweichung ruehrt die Vektoren nicht an -- sie ist eine andere Zuteilung
    // auf denselben Profilen. Faellt die Vektorhaelfte hier aus, ist der Nachweis
    // ungueltig, weil dann nicht die Klasse den Ausschlag gaebe.
    pruefe(befund_abweichend.vektoren_heil,
           "die Abweichung laesst die Vektoren heil -- sie trifft nur die Klasse",
           __LINE__);
    pruefe(!befund_abweichend.klassen_heil,
           "gefangen wird sie von der Klassenhaelfte der Ankerpruefung", __LINE__);

    // Kennung und Vektor des ersten Ankers, an dem es auffaellt.
    pruefe(befund_abweichend.erster_klassenverstoss == 44,
           "sie faellt zuerst an Kennung 44 auf, dem Gleichstand 2 gegen 2", __LINE__);
    if (befund_abweichend.erster_klassenverstoss >= 0) {
        for (std::size_t i = 0; i < ANKERZAHL; ++i) {
            if (ANKER[i].kennung == befund_abweichend.erster_klassenverstoss) {
                std::fprintf(stdout, "\n  zuerst gefangen an:\n");
                schreibe_anker("faellt auf bei", ANKER[i], abweichend[i], ANKER[i].kern);
            }
        }
    }

    // **Und was diese Abweichung ausdruecklich NICHT ausloest**, weil ein Test auch
    // sagen muss, was er durchlaesst: Zwei der vier Anker haben gar keinen
    // Gleichstand unter den Familienstellen -- 20 hat mit `a3 = 5` einen eindeutig
    // groessten, 60 mit `a1 = 1` ebenso. Ein Gleichstandsbrecher kommt dort nie zum
    // Zug. Waeren nur diese beiden in der Liste, liefe die Abweichung gruen durch;
    // gefangen wird sie allein von 44 und 76.
    std::fprintf(stdout, "\n  von 4 Ankern fangen die Abweichung: %d\n",
                 befund_abweichend.abweichende);
    std::fprintf(stdout, "  durchgelassen (kein Gleichstand im Profil):\n");
    for (std::size_t i = 0; i < ANKERZAHL; ++i) {
        if (!befund_abweichend.weicht_ab[i]) {
            schreibe_anker("durchgelassen", ANKER[i], abweichend[i], ANKER[i].kern);
        }
    }

    pruefe(befund_abweichend.abweichende == 2,
           "genau 2 der 4 Anker fangen die Abweichung", __LINE__);
    pruefe(befund_abweichend.weicht_ab[1] && befund_abweichend.weicht_ab[3],
           "gefangen wird sie von Kennung 44 und Kennung 76", __LINE__);
    pruefe(!befund_abweichend.weicht_ab[0] && !befund_abweichend.weicht_ab[2],
           "Kennung 20 und Kennung 60 lassen sie durch -- sie haben keinen Gleichstand",
           __LINE__);

    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\n%s -- %d Pruefung(en) fehlgeschlagen\n",
                 fehlgeschlagen == 0 ? "bestanden" : "GESCHEITERT", fehlgeschlagen);
    return fehlgeschlagen == 0 ? 0 : 1;
}
