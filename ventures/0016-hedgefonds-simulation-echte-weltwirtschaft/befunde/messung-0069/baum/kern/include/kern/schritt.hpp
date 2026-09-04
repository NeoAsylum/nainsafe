#pragma once
//! `kern::schritt` -- die Runde als Geruest, im Modus `weltlauf`.
//!
//! Vorgaben: T10 (der Weltschritt zieht nicht), T19 (die Kette gehoert nicht in den
//! Zustand), T38 (der Modus ist Argument und bringt eine Sollmaske mit), T39 (zwei
//! Lesezugriffe), T18 (der Schreiber ist der einzige Schreibweg), T9 (feste
//! Reihenfolge); `spiel.md`, Abschnitt *Die Schleife* (die sechs Schritte).
//!
//! ## Was dieser Kasten ist -- und was er ausdruecklich nicht ist
//!
//! Er ist der **Rahmen** der Runde: Signatur, Rueckgabewert, die feste Reihenfolge der
//! sechs Schritte, die Rundenendpruefung. Er ist **keine gerechnete Welt**. Eine Runde
//! im `weltlauf` traegt heute jede der 175 Adressen ihrer Sollmaske unveraendert vor;
//! danach steht dieselbe Welt noch einmal da, mit 175 Ursachensaetzen, die genau das
//! aussagen. Das ist der Zuschnitt des Arbeitspakets 0033 und keine Unfertigkeit: Die
//! sechs Schritte der Runde sind sechs eigene Pakete, und dies ist die Buehne, auf der
//! sie einzeln aufgestellt werden.
//!
//! Zwei Eigenschaften dieses Rahmens sind deshalb **auf Widerruf**, und beide sind es
//! mit Absicht:
//!
//!   * Die Pruefsumme des Zustands aendert sich ueber eine Runde **nicht**. Sie faellt,
//!     sobald der erste Schritt anfaengt zu rechnen -- und genau dann soll sie fallen.
//!   * Die Kette liegt in **aufsteigender** Adressfolge. Auch das faellt, sobald ein
//!     Schritt seinen Block als Ganzes rechnet statt Adresse fuer Adresse.
//!
//! Wer den ersten rechnenden Schritt baut, zieht beide Aussagen in seiner Probe nach.
//!
//! ## Der Modus
//!
//! Gebaut ist **`Modus::Weltlauf`** und nur der. Er ist der einzige, der heute
//! vollstaendig baubar ist: Nach T38 entfallen in ihm Schritt 2 (Aktionen) und Schritt 6
//! (Abrechnung), also braucht der Rahmen weder einen Aktionstyp (T32, unbeauftragt) noch
//! `kern::werte` (Paket 0002, blockiert). **`Modus::Spielmodus` bricht ab**, und die
//! Meldung nennt den Grund -- ein stilles Vortragen aller 310 Adressen saehe aus wie eine
//! gerechnete Spielrunde und waere keine.
//!
//! ## Was hier nicht steht
//!
//! Die **Regeln** der sechs Schritte (`spiel.md`), die **abgeleiteten Groessen**
//! (`kern::werte`), der **Verlauf** ueber mehrere Runden (nach T19 fuehrt ihn die
//! Sitzung, nicht der Kern) und die **Datenschicht** (T13): `parameter.toml` wird hier
//! nicht gelesen, der Rahmen braucht keinen Parameter.

#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

namespace kern::schritt {

using schreiber::Kette;
using schreiber::Modus;
using zustand::Zustand;

/// Die Aktionen einer Runde -- **heute ein leerer Typ**.
///
/// Er steht in der Signatur, weil T10 ihn nennt (`schritt(zustand, aktionen, modus)`),
/// und er ist leer, weil es den Aktionstyp im Kern noch nicht gibt: **T32 ist
/// unbeauftragt.** Ihn wegzulassen waere eine Signatur, die ein spaeteres Paket aendern
/// muss; ihn auszufuellen waere Arbeit an einem Kasten, den `specs/` noch nicht
/// beauftragt hat. Im Modus `weltlauf` entfaellt Schritt 2 ohnehin (T38), das Buendel
/// ist dort also nicht nur leer, sondern folgenlos.
struct Aktionsbuendel {
};

/// Was eine Runde liefert: **beides** (T19).
///
/// Die Feldnamen sind die aus T19 (`(neuer_zustand, kette_dieser_runde)`). Die Kette
/// geht **nicht** in den Zustand -- der bleibt bei 310 Feldern und 2.480 Byte; ein
/// Ergebnistyp daneben ist die Bauart, die T19 verlangt, und der Pruefstand kann die
/// Kette wegwerfen, wenn er nur Ergebnisse zaehlt.
struct Rundenergebnis {
    /// Der Zustand am Ende dieser Runde, wie ihn `Schreiber::rundenende` herausgibt --
    /// also erst nach der zweiseitigen Maskenpruefung aus T38.
    Zustand neuer_zustand;
    /// Die Ursachensaetze dieser Runde, in der Reihenfolge der Schreibzugriffe.
    Kette kette_dieser_runde;
};

/// Eine Runde: aus dem Zustand am Ende der Vorrunde wird der dieser Runde.
///
/// **Eine reine Funktion ohne gezogene Zahlen** (T10). Sie hat kein Argument dafuer und
/// zieht keine: Nach `spiel.md` ist jede Regel eine Schwelle, ein Zaehler oder eine
/// Rechnung, und im `weltlauf` wird nach T38 ohnehin kein einziger Strom angefasst.
/// Derselbe Zustand, dasselbe Buendel und derselbe Modus ergeben deshalb in jedem Lauf
/// dasselbe Ergebnis -- das ist Anforderung 1 des Vorhabens, und sie kostet hier nichts.
///
/// `vorrunde` ist der Zustand am Ende der Vorrunde; in Runde 1 der Startzustand des
/// Jahrgangs. Die Nummer dieser Runde ist `partie.runde` der Vorrunde **plus eins** --
/// die Nummer der letzten abgeschlossenen Runde steht nach T38 in beiden Sollmasken und
/// wird jede Runde geschrieben.
///
/// **Harte Fehler, alle ohne Ersatzwert:**
///   * `modus == Modus::Spielmodus` -- in diesem Rahmen nicht gebaut, siehe oben.
///   * `partie.runde` der Vorrunde ist negativ oder der groesste `int64_t`. Eine Runde
///     vor der ersten gibt es nicht, und eine nach der letzten zaehlbaren auch nicht.
///   * jeder Abbruch aus `Schreiber` -- zweiter Schreibzugriff, Lesezugriff auf eine
///     noch ungeschriebene Adresse, verfehlte Sollmaske am Rundenende.
[[nodiscard]] Rundenergebnis schritt(const Zustand& vorrunde, const Aktionsbuendel& aktionen,
                                     Modus modus);

}  // namespace kern::schritt
