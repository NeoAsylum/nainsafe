//! Messstand zu Paket 0145, zweiter Teil: **die Raender des Rundenzaehlers**.
//!
//! Beschraenktheit heisst nicht nur "keine Groesse laeuft weg", sondern auch "der Lauf
//! selbst hoert an einer benannten Stelle auf". `kern/include/kern/schritt.hpp` nennt
//! drei harte Fehler der Runde -- Modus `spielmodus`, negative Vorrundennummer und die
//! Vorrundennummer `I64_MAX`. Alle drei sind bisher **behauptet** und nie vorgefuehrt
//! worden; ein Riegel, der nie ausgeloest hat, ist von einem fehlenden nicht zu
//! unterscheiden.
//!
//! Dieses Programm loest sie aus und druckt die Meldung im Wortlaut. Es aendert nichts,
//! haengt an keinem ctest-Eintrag und liegt wie sein Geschwister unter
//! `befunde/beschraenktheit/`.
//!
//! Die Vorrundennummer wird ueber den Startwertzugang gesetzt und nicht erlaufen: Bis
//! `I64_MAX` zu zaehlen sind 9,2 Trillionen Runden. Der Zugang darf das -- er arbeitet
//! vor der ersten Runde, und seine Merkzahl wandert mit (Paket 0027).

#include <cstdio>
#include <exception>
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

constexpr Index PLATZ_RUNDE =
    kern::zustand::stelle_partie(kern::zustand::PartieFeld::Runde);

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

}  // namespace

// UNVOLLSTAENDIG -- angefangen am 2026-09-06, nicht fertiggestellt.
// Was fehlt: die drei Randproben und `main`. Der Rest steht in bruch-2026-09-06.md,
// Abschnitt "Was ich nicht gemessen habe", und als Vorschlag 0160.
