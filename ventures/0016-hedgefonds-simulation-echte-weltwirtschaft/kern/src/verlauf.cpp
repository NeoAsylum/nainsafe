//! Der Verlauf -- die Rundenketten und die beiden harten Schranken darauf.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/verlauf.hpp`. Hier steht, was nicht in
//! einen Kopf gehoert: die Abbrueche im Wortlaut und die Reihenfolge, in der sie
//! geprueft werden.
//!
//! ## Warum die Schranke je Runde hier noch einmal steht
//!
//! `kern::schreiber::Kette` traegt dieselbe Grenze und bricht ebenfalls hart ab. Die
//! Pruefung hier ist trotzdem keine Verdopplung ohne Gewinn, sondern eine doppelt
//! gehaltene Schranke mit einem Unterschied im Wortlaut: Die Kette kennt ihre
//! Rundennummer nicht -- sie ist ein Behaelter und keine Runde --, und ihre Meldung
//! kann deshalb nur sagen, dass **eine** Kette voll war. Der Verlauf weiss, welche.
//!
//! Fuer den Aufrufer ist das der Unterschied zwischen einer Meldung, mit der er die
//! Stelle findet, und einer, mit der er von vorn suchen muss. Die aeussere Pruefung
//! liegt deshalb vor der Weitergabe an die Kette; die innere bleibt als Auffanglinie
//! stehen, und welche von beiden zugeschlagen hat, unterscheidet die Probe am Wortlaut.
//!
//! ## Die Reihenfolge der Pruefungen ist festgelegt und nicht beliebig
//!
//! Ein Aufruf kann mehrere Bedingungen auf einmal verletzen -- eine Runde null auf
//! einen vollen Verlauf etwa. Geprueft wird dann von der Aussage ueber das Argument zur
//! Aussage ueber den Behaelter: erst der Wert der Rundennummer, dann ihr Verhaeltnis zur
//! Vorrunde, dann der Platz im Verlauf. Ohne festgelegte Reihenfolge haenge es an der
//! Uebersetzung, welche der Meldungen ankommt, und eine Probe auf den Wortlaut pruefte
//! dann den Zufall.

#include <cstddef>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/verlauf.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::verlauf {

namespace {

using meldung::Meldung;

