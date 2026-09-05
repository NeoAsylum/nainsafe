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
//! im `weltlauf` traegt heute 174 der 175 Adressen ihrer Sollmaske unveraendert vor; die
//! 175. ist `partie.runde`, und die zaehlt hoch. Danach steht dieselbe Welt noch einmal
//! da, eine Runde weiter, mit 175 Ursachensaetzen, die genau das aussagen. Das ist der
//! Zuschnitt des Arbeitspakets 0033 und keine Unfertigkeit: Die sechs Schritte der Runde
//! sind sechs eigene Pakete, und dies ist die Buehne, auf der sie einzeln aufgestellt
//! werden.
//!
//! Eine Eigenschaft dieses Rahmens ist **auf Widerruf**, und sie ist es mit Absicht:
//!
//!   * Die Kette liegt in **aufsteigender** Adressfolge. Das faellt, sobald ein Schritt
//!     seinen Block als Ganzes rechnet statt Adresse fuer Adresse.
//!
//! Wer den ersten rechnenden Schritt baut, zieht diese Aussage in seiner Probe nach.
//!
//! **Die zweite ist am 2026-09-04 widerrufen worden, und das gehoert hierher, weil an
//! ihrer Stelle etwas anderes steht.** Bis dahin hiess es: Die Pruefsumme des Zustands
//! aendert sich ueber eine Runde nicht. Seit Paket `0071-rundennummer-in-den-zustand`
//! aendert sie sich, und die Aussage an ihrer Stelle ist schaerfer als die alte: **Genau
//! eine der 310 Groessen wird ueber eine Runde im `weltlauf` anders, naemlich
//! `partie.runde`.** Der Widerruf ist keine Nachbesserung an 0033, sondern der Fall, fuer
//! den es dort "auf Widerruf" hiess: Ein Zustand, den eine vollstaendige Runde Feld fuer
//! Feld unveraendert laesst, ist von "keine Runde gelaufen" durch keinen Vergleich zu
//! unterscheiden -- und genau diese Unterscheidung braucht der Startwertriegel aus Paket
//! 0027, der sonst gegen die Runde des Kerns nie anschlaegt.
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
/// Jahrgangs. Die Nummer dieser Runde ist `partie.runde` der Vorrunde **plus eins**, und
/// sie steht danach im zurueckgegebenen Zustand: Schritt 1 **setzt** das Feld, statt es
/// vorzutragen (Paket 0071). Nach T38 liegt es in beiden Sollmasken und wird damit jede
/// Runde geschrieben; seit 0071 wird es auch jede Runde veraendert. `partie.runde` traegt
/// also die Nummer der letzten abgeschlossenen Runde -- vor der ersten die Null.
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
