//! Die Rechnung zu `pruefstand/vorrat.hpp`.
//!
//! Drei Dinge, die dieses Modul absichtlich **nicht** tut, weil an jedem von ihnen
//! ein Befund haengt:
//!
//!   1. **Es merkt sich nichts.** Kein Modulzustand, keine gespeicherte Liste, keine
//!      Zwischenablage. Der Vorrat gehoert dem Aufrufer, die Profilliste faellt als
//!      Wert heraus. Zwei Laeufe koennen deshalb nicht ueber eine Ablage
//!      aneinandergeraten -- dieselbe Regel wie in `kern::zufall`.
//!   2. **Es schneidet den Vorrat nicht bei null ab.** `vi` darf negativ werden. Der
//!      Abschnitt saehe harmlos aus und zerstoerte die Invariante aus T43; die Probe
//!      fuehrt genau das als Abweichung vor.
//!   3. **Es erfindet keine Zulaessigkeit.** Welche Arten zur Wahl stehen, kommt von
//!      aussen (T32).
//!
//! Ganzzahlig durchgehend (T4). Die groesste hier vorkommende Zahl ist
//! `ZUWACHS * BUDGET * RUNDEN_HOECHSTENS = 1350`; ein `__int128`-Zwischenwert ist
//! deshalb nicht noetig -- es gibt keine Multiplikation-Division und keinen Wert in
//! der Naehe einer Schranke.

#include "pruefstand/vorrat.hpp"

#include <stdexcept>

namespace pruefstand::vorrat {
