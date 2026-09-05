#pragma once
//! Die beiden Rechensperren des Kerns (T4 und T7) -- als Uebersetzungsfehler, nicht
//! als Vorsatz.
//!
//! Der obere Block sperrt das Gleitkomma, der untere die Strichrechnung. Beide haben
//! dieselbe Bauform und beide leben von derselben Einbauregel; die zweite ist unter
//! ihrer eigenen Ueberschrift weiter unten begruendet.
//!
//! In Rust stuende dafuer `#![deny(clippy::float_arithmetic)]` in `lib.rs`. C++ hat
//! kein solches Attribut; die Entsprechung ist `#pragma GCC poison`. Ein vergifteter
//! Bezeichner ist ab dieser Zeile ein harter Fehler des Vorverarbeiters -- nicht eine
//! Warnung, nicht eine Regel, die jemand liest. Wer im Kern `double` schreibt, bekommt
//! keinen Zahlenfehler in Runde 400, sondern einen roten Uebersetzungslauf.
//!
//! **Die Einbauregel, und sie ist der ganze Trick:** Diese Datei ist die *letzte*
//! Zeile des Include-Blocks jeder Kernquelle. Die Vergiftung gilt ab der Stelle, an
//! der sie steht, bis zum Ende der Uebersetzungseinheit -- ein Standardkopf, der
//! danach eingebunden wird, zerbricht daran (`<string>` deklariert `std::to_string`
//! fuer `double`). Deshalb steht sie in keiner `.hpp` des Kerns, sondern nur unten in
//! den `.cpp`, wo nichts mehr folgt.
//!
//!   Mechanischer Nachweis, dass die Regel eingehalten ist:
//!   grep -c 'include "kern/sperre.hpp"' kern/src/*.cpp   -> jede Quelle genau 1
//!   grep -rn 'f32\|f64\|float\|double' kern/              -> nur diese Datei
//!
//! `long double` braucht keinen eigenen Eintrag: Es sind zwei Token, und `double`
//! ist vergiftet.
//!
//! ## Dieselbe Sperre fuer die Strichrechnung (T7, Massnahme 4, Punkt 2)
//!
//! `__builtin_add_overflow` und `__builtin_sub_overflow` sind die vorgeschriebene und
//! einzige erlaubte Bauart fuer Addition und Subtraktion auf `i64`. Die Vergiftung
//! unten verbietet sie deshalb nicht -- sie ist das Gegenteil eines Verbots: die
//! Zusicherung, dass es bei der einen Stelle bleibt, die sie benutzt, naemlich
//! `festkomma::plus` und `festkomma::minus`.
//!
//! **Warum sie hier steht und nicht in `festkomma.hpp`** -- wegen der Einbauregel
//! oben, und nur wegen ihr. Der Kopf mit den beiden Funktionen gehoert in den
//! Include-Block ueber dieser Datei und ist vollstaendig gelesen, bevor die Vergiftung
//! ueberhaupt gilt; danach folgt in einer Kernquelle nichts mehr. Es braucht deshalb
//! **keine** Ausnahme fuer die eine erlaubte Stelle -- die Reihenfolge ist die
//! Ausnahme. In `festkomma.hpp` selbst waere dieselbe Zeile ein Widerspruch: Sie
//! vergiftete die Bausteine vor ihrem eigenen Gebrauch.
//!
//! **Und warum es den Riegel ueberhaupt braucht.** Ohne ihn ist die Vorgabe aus T6 --
//! der Festkommakopf ist die einzige Rechenstelle des Kerns -- fuer die Strichrechnung
//! ein Satz, den ein Mensch lesen muss. Eine zweite Fassung von `plus` im anonymen
//! Namensraum irgendeiner Quelle uebersetzt und laeuft gruen, und keine Messung
//! unterscheidet sie von der richtigen. Bei einer Ueberlaufpruefung heisst
//! Auseinanderlaufen dann: ein Modul bricht ab, das andere bricht unter `-fwrapv`
//! **still** um -- der Unterschied zwischen einem roten Lauf und einem falschen
//! Ergebnis in Runde 400.
//!
//!   Mechanischer Nachweis, dass es bei der einen Stelle geblieben ist:
//!   grep -rln '__builtin_add_overflow\|__builtin_sub_overflow' kern/ pruefstand/
//!       -> nur festkomma.hpp und diese Datei
//!
//! Nicht mitvergiftet sind `*`, `+` und `-` als Operator. Ob `a * b` zwei Groessen
//! multipliziert oder eine Adresse rechnet, traegt die Zeile nicht bei sich; das ist
//! die Frage von Massnahme 4.3, sie liegt bei Paket 0074 und wird hier nicht
//! mitentschieden. Der Unterschied zu der Zeile unten ist, dass die
//! Ueberlaufbausteine Bezeichner sind und keine Operatoren -- keine Typfrage, kein
//! Doppelleben als Adressrechnung, kein Grenzfall.

#pragma GCC poison float double
#pragma GCC poison sqrt sqrtf sqrtl pow powf powl log logf logl exp expf expl
#pragma GCC poison atof strtod strtof strtold

#pragma GCC poison __builtin_add_overflow __builtin_sub_overflow
