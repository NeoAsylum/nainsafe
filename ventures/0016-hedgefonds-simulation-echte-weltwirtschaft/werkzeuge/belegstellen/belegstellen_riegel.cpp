//! # Der Belegstellenriegel -- Paket 0059
//!
//! Sechs Pakete haben Belegstellen von Hand nachgezogen (0034, 0035, 0044, 0047,
//! 0050, 0057). Jedes war richtig; zusammen sind sie der Beleg, dass die
//! Handnachfuehrung den Fehler nur einholt und nicht abstellt. Paket 0050 hat vier
//! Belegstellen aufgezaehlt und fuer jede die richtige Zeile nachgeschlagen -- wenige
//! Stunden spaeter standen die Stellen anderswo. Die Korrektur war falsch, bevor sie
//! jemand ausfuehren konnte.
//!
//! Dieses Programm prueft zwei Bedingungen ueber die Quelldateien des Vorhabens:
//!
//!   1. **Keine Zeilennummer in eine fremde Datei.** Wo im Text ein Dateiname steht,
//!      dem eine Zeilenangabe folgt, ist der Verweis nicht haltbar. Er zeigt heute
//!      vielleicht richtig; er zeigt morgen woandershin, ohne dass jemand etwas tut.
//!
//!   2. **Jedes Abschnittszitat existiert wirklich.** Wo eine Quelldatei einen
//!      Dateinamen nennt, gefolgt von der Marke fuer einen Abschnitt und einer
//!      Ueberschrift in Anfuehrungszeichen oder Sternchen, muss in der genannten
//!      Datei eine Ueberschriftszeile mit genau dieser Ueberschrift stehen.
//!
//! **Bedingung 2 ist die wichtigere.** Alle sechs Pakete haben Zeilennummern durch
//! Ueberschriften ersetzt; ob eine dieser Ueberschriften noch existiert, hat seither
//! nichts gemessen. Eine umbenannte Ueberschrift ist genauso tot wie eine verschobene
//! Zeile -- sie faellt aber nicht einmal beim Nachschlagen auf, weil der Verweis
//! weiterhin plausibel aussieht.
//!
//! ## Was der Riegel liest, und warum genau das
//!
//! Gelesen werden die **Bauquellen** des Vorhabens: Rumpf- und Kopfdateien, die
//! Bausteuerung und jede Bauliste. Ausgenommen sind die Verzeichnisse `bau` (vom
//! Uebersetzer erzeugt) und `befunde` (Berichte -- eine Zeilennummer darin ist ein
//! *Messwert vom Tag der Messung*, kein Verweis; sie soll gerade nicht nachgefuehrt
//! werden, sonst faelschte man einen Bericht).
//!
//! Die Datendokumente unter `daten/` und die Parameterdatei sind **nicht** darunter,
//! und das ist eine benannte Grenze und keine Ausnahmeliste: Auf `reihen.toml` und
//! `einheitenbefund-pwt-baci.md` laeuft Paket 0057, auf die Parameterdatei liefen
//! 0035 und 0042. Ein Riegel, der sie heute mitnaehme, koennte erst gruen werden,
//! nachdem eine inhaltliche Aufraeumarbeit fertig ist -- genau das, was das
//! Arbeitspaket zu diesem Programm ausschliesst. Die Erweiterung ist eigene Arbeit
//! und liegt als Vorschlag 0061 daneben. Die Grenze steht hier ausgeschrieben, damit
//! niemand die Zahlen unten fuer "alles geprueft" haelt.
//!
//! ## Warum der Riegel seinen eigenen Quelltext mitliest
//!
//! Er tut es, und das ist Absicht: Nur so laesst sich der Rotnachweis fuehren, ohne
//! eine fremde Datei anzufassen. Die Marke fuer Bedingung 2 steht deshalb unten mit
//! einer Begruendung, warum sie sich nicht selbst faengt.
//!
//! ## Aufruf
//!
//!     belegstellen_riegel <wurzel-des-vorhabens> <wurzel-der-vorgaben>
//!
//! Beide Wurzeln kommen von CMake und stehen nicht im Programm. Ein fest eingebauter
//! Pfad liefe nur auf dem Rechner, auf dem er gebaut wurde.
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet),
//! ADR 0011 (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Die Marken
// ---------------------------------------------------------------------------

/// Die Marke fuer Bedingung 2.
///
/// Der Riegel liest seinen eigenen Quelltext mit, und diese Zeile steht darin. Sie
/// loest trotzdem keinen Selbstfund aus: Hinter der Marke folgt hier sofort ein
/// Anfuehrungszeichen, ein Zitat verlangt aber erst ein Leerzeichen. Nachzulesen als
/// erste Bedingung in `ueberschrift_lesen`.
constexpr std::string_view MARKE = "Abschnitt";

/// Die zugelassenen Endungen, als ein Streifen mit Trennpunkten statt als Liste.
/// Gesucht wird darin nach der Endung samt beiden Punkten, damit `md` nicht in
/// `cmd` trifft. Bewusst kurz: Was hier nicht steht, ist kein Verweisziel dieses
/// Vorhabens.
constexpr std::string_view ENDUNGEN = ".md.toml.cpp.hpp.txt.cmake.py.rs.";
