#pragma once
//! Die Gleitkommasperre des Kerns (T4) -- als Uebersetzungsfehler, nicht als Vorsatz.
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

#pragma GCC poison float double
#pragma GCC poison sqrt sqrtf sqrtl pow powf powl log logf logl exp expf expl
#pragma GCC poison atof strtod strtof strtold
