#pragma once
//! Der Kern -- Sammelkopf und Modulliste.
//!
//! Das ist die Datei, die Paket 0004 als `kern/src/lib.rs` beschreibt: die Stelle,
//! an der die sieben Module des Kerns aufgezaehlt sind und an der die Regeln stehen,
//! die fuer alle gelten. Seit ADR 0011 (2026-09-01) ist die Sprache C++20; die
//! Kastenattribute von Rust haben hier je eine mechanische Entsprechung.
//!
//! ## Die sieben Module
//!
//!   festkomma    die Rechenregeln -- Rundung, Multiplikation-Division, Potenz, Wurzel
//!   zustand      die 310 Felder             (Paket 0008-kern-zustand-310-felder)
//!   werte        die abgeleiteten Groessen  (Paket 0002-fondsbewertung-definieren)
//!   schreiber    der Schreibzugriff mit Herkunftseintrag
//!   zufall       der eine Zufallsstrom mit ausdruecklichem Startwert
//!   pruefsumme   die kanonische Byteform und ihre Summe
//!   schritt      der Weltschritt
//!
//! Sechs davon sind Platzhalter mit genau einer Zeile. Das ist der Auftrag und kein
//! Versaeumnis: Nur so besitzt jedes spaetere Paket genau eine Datei, und keine zwei
//! Bauagenten treffen sich in dieser hier. Wer ein Modul baut, ersetzt seine
//! Kopfdatei und legt seine `src/<modul>.cpp` daneben -- diese Datei bleibt, wie sie
//! ist, und `kern/CMakeLists.txt` auch.
//!
//! ## Was fuer den ganzen Kern gilt
//!
//! **T2 -- null Fremdabhaengigkeiten.** Nur die Standardbibliothek, und von der so
//! wenig wie moeglich. Der Nachweis steht in `kern/CMakeLists.txt`.
//!
//! **T4 -- keine Gleitkommazahl.** Durchgesetzt durch `include/kern/sperre.hpp`:
//! Jede Quelldatei des Kerns schliesst ihren Include-Block mit
//! `#include "kern/sperre.hpp"` ab, und ab dieser Zeile ist `float`, `double`,
//! `sqrt`, `pow` und `log` ein Uebersetzungsfehler. Dieser Sammelkopf bindet die
//! Sperre **nicht** ein -- er wird von aussen eingebunden, und dort folgen noch
//! Standardkoepfe, die an einer Vergiftung zerbrechen wuerden.
//!
//! **T7 und ADR 0011 -- Ueberlauf.** `-fwrapv` in jedem Profil macht den Umbruch
//! definiert, die Sanitizer machen im Testprofil laut, was unbeabsichtigt ist, und
//! jeder Zwischenwert einer Multiplikation-Division laeuft ueber `__int128`. Wo ein
//! Ergebnis nicht mehr in `i64` passt, bricht der Kern ab, statt umzulaufen.
//!
//! **T9 -- feste Reihenfolge.** Laender, Sektoren, Instrumente und Handelspaare sind
//! dichte Indexlisten. `std::unordered_map` und `std::unordered_set` sind im Kern
//! verboten; gebraucht wird eine Zuordnung, ist es `std::map`. Der Grund ist nicht
//! Geschmack: Eine streuende Reihenfolge macht denselben Startwert zu zwei Partien.
//!
//! **T13 -- der Kern kennt weder Bildschirm noch Datei noch Uhr.** Kein `<iostream>`,
//! kein `<fstream>`, kein `<chrono>`. Das Modell fragt die Sicht nie etwas.
//!
//! **Kein `unsafe`.** C++ hat dafuer kein Wort, deshalb steht die Regel hier und der
//! Nachweis in `kern/CMakeLists.txt`: keine Zeigerarithmetik, keine eigene
//! Speicherverwaltung, `std::array` fester Groesse statt roher Felder,
//! Indexpruefung an jeder Grenze.

#include "kern/festkomma.hpp"
#include "kern/zustand.hpp"
#include "kern/werte.hpp"
#include "kern/schreiber.hpp"
#include "kern/zufall.hpp"
#include "kern/pruefsumme.hpp"
#include "kern/schritt.hpp"
