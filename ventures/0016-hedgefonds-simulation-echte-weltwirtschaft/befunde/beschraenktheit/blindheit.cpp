//! Messstand 2 zu Paket 0145 -- was der `weltlauf` ueber 200 Runden NICHT anfasst.
//!
//! Der erste Messstand (`beschraenktheit.cpp`) laesst 200 Runden gegen zwei
//! kalibrierte Ausgangslagen laufen und meldet je Schranke ein Urteil. Sein Befund
//! war, dass alle sieben Schranken halten -- und dass dieses Gruen nichts wert ist,
//! weil sich ueber eine Runde genau eine der 310 Groessen aendert.
//!
//! Diese Aussage stuetzte sich auf zwei Quellen, die beide **gelesen** und nicht
//! gemessen waren: die Blocktabelle in `kern/include/kern/schreiber.hpp` und die
//! Rumpfform von `schritt_3` bis `schritt_5` in `kern/src/schritt.cpp`. Aus ihnen
//! wurde geschlossen, 65 der 101 Schrankenadressen laegen ausserhalb der Sollmaske
//! `weltlauf` und trugen deshalb in Runde 200 zwangslaeufig ihren Startwert.
//!
//! Ein geschlossener Satz ist keine Messung. Dieser Messstand misst ihn:
//!
//!   1. Er belegt alle 310 Plaetze mit einer **Marke** statt mit Startwerten und
//!      laesst 200 Runden laufen. Danach steht je Platz da, ob er sich geaendert hat
//!      und ob er in der Sollmaske liegt. Traegt ein Platz ausserhalb der Maske nach
//!      200 Runden noch seine Marke, ist der Satz gemessen statt gelesen.
//!   2. Er wiederholt das mit `I64_MAX` und `I64_MIN` auf allen Plaetzen. Das ist der
//!      Rand, den die Rollendatei des Bruchtesters verlangt: Ueberlauf, nicht
//!      Kalibrierung. Ein Abbruch ist hier **das Ergebnis** und kein Scheitern -- er
//!      wird gefangen, mit Rundennummer und Meldung im Wortlaut abgedruckt.
//!
//! `partie.runde` (Platz 306) bleibt in jeder Lage auf null. Der Startwertzugang
//! laesst sich nur an einen Zustand mit `partie.runde == 0` binden, und die Runde
//! setzt genau diesen Platz -- er ist die eine Groesse, die sich legitim bewegt.
//!
//! Kein Eingriff in den Baum: Die Datei liegt unter `befunde/`, wird von keinem
//! `file(GLOB ...)` eingesammelt und von Hand uebersetzt (siehe `lauf-3.sh`).

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::zustand::FELDER;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

/// Platz von `partie.runde` -- die eine Groesse, die die Runde setzt statt vortraegt.
constexpr Index PLATZ_RUNDE = 306;

/// Wie viele Runden. Die Zahl steht in T30, Pruefung 6.
constexpr long long RUNDEN = 200;

/// Ein Zustand samt dem einen Startwertzugang, der ihn fuellt (Paket 0027).
struct Rohling {
    Zustand       zustand{};
    Startbelegung zugang{zustand};

    void lege(Index platz, i64 wert) { zugang.setze(platz, wert); }
};

// Die drei Ausgangslagen, als Zahl statt als Aufzaehlung -- 0 Marke, 1 Obergrenze,
// 2 Untergrenze. Die Marke traegt den Platz in sich, damit im Mitschnitt sichtbar
// ist, ob ein Wert verschoben oder bloss ueberschrieben wurde.
i64 startwert(int lage, Index platz)
{
    if (lage == 0) {
        return 1000000 + static_cast<i64>(platz);
    }
    if (lage == 1) {
        return INT64_MAX;
    }
    return INT64_MIN;
}
