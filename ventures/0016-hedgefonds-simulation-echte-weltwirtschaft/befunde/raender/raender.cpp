//! Messstand zu Paket 0160: **die drei harten Fehler der Runde, vorgefuehrt**.
//!
//! `kern/include/kern/schritt.hpp` nennt unter "Harte Fehler, alle ohne Ersatzwert" drei
//! Faelle, und `kern/src/schritt.cpp` schreibt fuer jeden eine ausformulierte Meldung:
//!
//!   1. der Modus ist der Spielmodus -- in diesem Rahmen nicht gebaut,
//!   2. `partie.runde` der Vorrunde ist negativ -- eine Runde vor der ersten gibt es nicht,
//!   3. `partie.runde` der Vorrunde ist der groesste `int64_t` -- die naechste Runde
//!      liesse sich nicht mehr zaehlen.
//!
//! Alle drei waren bis zum 2026-09-06 **behauptet** und nie ausgeloest. Ein Riegel, der
//! nie ausgeloest hat, ist von einem fehlenden nicht zu unterscheiden. Dieses Programm
//! stellt die Lage her, ruft die Runde und laesst sehen, was herauskommt.
//!
//! **Kopf und Hilfsklasse sind aus `befunde/beschraenktheit/raender.cpp` uebernommen**,
//! dem angefangenen Messstand aus Paket 0145. Kopiert, nicht verschoben: Er gehoert zur
//! Ablage von 0145, und ein Paket benennt nicht um, was es nicht selbst angelegt hat.
//!
//! ## Wie die Vorrundennummer an den Rand kommt
//!
//! Ueber `zustand::Startbelegung` und nicht erlaufen: Bis zum groessten `int64_t` zu
//! zaehlen sind 9,2 Trillionen Runden. Der Zugang darf das -- er arbeitet vor der ersten
//! Runde, und seine Merkzahl wandert mit (Paket 0027, `kern/src/zustand.cpp`,
//! `Startbelegung::setze`). Genau deshalb ist dies ein **zweiter Messstand** und keine
//! weitere Zeile im ersten: 0145 hat die Beschraenktheit ueber die Laenge eines Laufs
//! gemessen, dies misst sie am Rand des Zahlenbereichs.
//!
//! ## Sechs Lagen, sechs Aufrufe, ein Aufruf je Programmlauf
//!
//! Die Abnahme verlangt "jeder mit einem eigenen Aufruf". Das Programm nimmt deshalb die
//! **Nummer** einer Lage als einziges Argument und fuehrt genau **einen** Aufruf von
//! `kern::schritt::schritt` aus. Drei Lagen sind die der Abnahme, drei stehen daneben und
//! messen, ob die Riegel an der richtigen Stelle sitzen:
//!
//!   1. Modus spielmodus, Vorrundennummer 0        -- harter Fehler 1
//!   2. Vorrundennummer -1                         -- harter Fehler 2
//!   3. Vorrundennummer = groesster int64_t        -- harter Fehler 3
//!   4. Vorrundennummer = kleinster int64_t        -- derselbe Riegel wie 2, am Ende
//!   5. Vorrundennummer = groesster int64_t - 1    -- die letzte zaehlbare Vorrunde
//!   6. Vorrundennummer 0, Modus weltlauf          -- der Vergleichsfall
//!
//! Lage 5 und 6 tragen den Beweis, dass die drei Abbrueche **eng** sind: Ein Riegel, der
//! jede Runde abwiese, saehe in den Lagen 1 bis 4 genauso aus.
//!
//! ## Das Programm druckt Zahlen, das Skript druckt Worte
//!
//! Auf der Standardausgabe stehen ohne Abbruch vier Zahlen, je eine Zeile, in dieser
//! Reihenfolge:
//!
//!   1. `partie.runde` **vor** dem Aufruf, gelesen aus dem Zustand (die Gegenprobe auf
//!      den Aufbau -- ohne sie waere ein abgewiesener Startwert von einem wirksamen
//!      nicht zu unterscheiden),
//!   2. `partie.runde` **nach** dem Aufruf,
//!   3. die Laenge der Rundenkette,
//!   4. wie viele der 310 Groessen sich geaendert haben.
//!
//! Kommt es zum Abbruch, steht Zahl 1 auf der Standardausgabe, der **Wortlaut der
//! Meldung** auf der Fehlerausgabe, und der Rueckgabewert ist 3 (`std::domain_error`)
//! oder 4 (eine andere Ausnahme). Ohne Abbruch ist er 0, bei einem Bedienfehler 1.
//!
//! Der Wortlaut kommt aus `what()` und geht unveraendert durch `std::fputs`; das Programm
//! setzt an ihm kein Zeichen. Die Beschriftung des Mitschnitts macht `lauf.sh`, und dort
//! steht auch, welche Lage welche Nummer hat. **Der Grund fuer diese Trennung ist nicht
//! Geschmack, sondern eine Werkzeugsperre im Lauf vom 2026-09-06** -- der Befund
//! `bruch-2026-09-06.md` nennt sie beim Namen. Sie hat dem Messstand nichts genommen: Der
//! Wortlaut, um den es geht, ist gerade der, den dieses Programm nicht selbst schreibt.

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

using kern::schreiber::Modus;

constexpr Index PLATZ_RUNDE =
    kern::zustand::stelle_partie(kern::zustand::PartieFeld::Runde);

constexpr i64 OBERGRENZE  = kern::festkomma::I64_MAX;
constexpr i64 UNTERGRENZE = kern::festkomma::I64_MIN;

/// Ein Zustand samt seinem einen Startwertzugang -- wie in `schranken_probe.cpp`.
class Rohling {
public:
    Rohling() = default;

    void lege(Index platz, i64 wert) { zugang_.setze(platz, wert); }

    operator const Zustand&() const { return zustand_; }

private:
    Zustand       zustand_;
    Startbelegung zugang_{zustand_};
};

/// Wie viele der 310 Groessen sich unterscheiden -- Feld fuer Feld ueber `lies`, keine
/// Pruefsumme, keine Stichprobe.
std::size_t zaehle_unterschiede(const Zustand& vorher, const Zustand& nachher)
{
    std::size_t summe = 0;
    for (Index platz = 0; platz < kern::zustand::FELDER; ++platz) {
        if (vorher.lies(platz) != nachher.lies(platz)) {
            ++summe;
        }
    }
    return summe;
}

}  // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        return 1;
    }
    const int lage = std::atoi(argv[1]);

    // Die sechs Lagen aus dem Kopf. Ausgeschrieben und nicht gerechnet: Wer eine aendert,
    // fasst ihre Zeile an und sieht dabei, was er tut.
    Modus modus  = Modus::Weltlauf;
    i64   nummer = 0;
    if (lage == 1) {
        modus = Modus::Spielmodus;
    } else if (lage == 2) {
        nummer = -1;
    } else if (lage == 3) {
        nummer = OBERGRENZE;
    } else if (lage == 4) {
        nummer = UNTERGRENZE;
    } else if (lage == 5) {
        nummer = OBERGRENZE - 1;
    } else if (lage != 6) {
        return 1;
    }

    Rohling rohling;
    rohling.lege(PLATZ_RUNDE, nummer);
    const Zustand& vorrunde = rohling;

    // Zahl 1: die Gegenprobe auf den Aufbau, vor dem Aufruf gelesen.
    std::cout << vorrunde.lies(PLATZ_RUNDE) << std::endl;

    const kern::schritt::Aktionsbuendel buendel{};
    try {
        const kern::schritt::Rundenergebnis ergebnis =
            kern::schritt::schritt(vorrunde, buendel, modus);
        std::cout << ergebnis.neuer_zustand.lies(PLATZ_RUNDE) << std::endl;
        std::cout << ergebnis.kette_dieser_runde.laenge() << std::endl;
        std::cout << zaehle_unterschiede(vorrunde, ergebnis.neuer_zustand) << std::endl;
        return 0;
    } catch (const std::domain_error& fehler) {
        std::cout << std::flush;
        std::fputs(fehler.what(), stderr);
        std::fputc(10, stderr);
        return 3;
    } catch (const std::exception& fehler) {
        std::cout << std::flush;
        std::fputs(fehler.what(), stderr);
        std::fputc(10, stderr);
        return 4;
    }
}
