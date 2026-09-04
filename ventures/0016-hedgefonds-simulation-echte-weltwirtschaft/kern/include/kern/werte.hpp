#pragma once
//! `kern::werte` -- die siebzehn abgeleiteten Groessen aus T48 und die drei
//! Skalenuebergaenge aus T50.
//!
//! Vorgaben: T47 (das Fondsvermoegen ist genau eine Funktion), T48 (die abgeleiteten
//! Groessen abschliessend aufgezaehlt), T50 (genau drei Skalenuebergaenge, jeder mit
//! benannter Funktion und genau einem Aufrufort), T5 (Skalenklassen), T9 (feste
//! Indexordnung), T13 (Modulschnitt), T33 (Marktkorb), T39 (der Landespreis liest die
//! Vorrunde), T6/T6b/T7 (Rechenwerk und Ueberlauf), T4 (kein Gleitkomma), T2 (keine
//! Fremdabhaengigkeit).
//!
//! ## Wozu es dieses Modul gibt
//!
//! T48 sagt den Zweck in einem Satz: Ein Name in einer Formel der Vorgaben, der weder
//! eine Zustandsadresse noch ein Parameterschluessel noch eine Jahrgangskonstante noch
//! eine der siebzehn Groessen hier ist, **ist ein Befund und keine Bauentscheidung**.
//! Waehlt der Bauagent, misst Mass 2 seine Wahl. Genau das war Befund 1 der sechsten
//! Entwurfspruefung: `korbwert` und `positionswert` standen in einer Formel und wurden
//! nirgends gebildet -- und der Abzaehlschritt aus T45 konnte die Luecke nicht finden,
//! weil er **Adressen** zaehlt und `korbwert` nie eine der 310 war.
//!
//! ## Der mechanische Nachweis, und was er zaehlt
//!
//! T48 sieht ihn ausdruecklich fuer dieses Modul vor: die oeffentlichen Deklarationen
//! dieses Kopfes gegen die Tabelle aus T48 gelegt. Gezaehlt werden **Funktionen** --
//! in Rust waere es ein Mustervergleich auf die oeffentlichen Funktionen, in C++ ist
//! es der Kopf, weil dort und nur dort steht, was das Modul nach aussen anbietet.
//! Unten stehen siebzehn, in der Reihenfolge der Tabelle aus T48 und mit deren
//! laufender Nummer davor.
//!
//! `Konstanten` ist keine achtzehnte Groesse, sondern der Traeger der Zahlen, die die
//! Formeln aus T47 und T48 **neben** dem Zustand nennen. Ohne ihn muesste jede der
//! siebzehn Funktionen sie einzeln durchreichen, und `fondsvermoegen` haette sechs
//! gleichartige Zahlenargumente in einer Reihe, in der eine Verwechslung nicht
//! auffiele.
//!
//! ## Was hier ausdruecklich NICHT steht
//!
//! Die drei Skalenuebergaenge aus T50. Sie sind **privat**: Sie stehen allein in
//! `src/werte.cpp` und haben in diesem Kopf keine Deklaration. Der Nachweis dafuer ist
//! ein Mustervergleich derselben Bauart wie der Gleitkommanachweis aus T4 -- eine
//! Suche nach ihren Namen ueber `kern/` trifft nur jene eine Datei.
//!
//! Die Umkehrung des ersten Uebergangs gibt es nicht (T50). Der Fonds wirkt auf die
//! Welt ausschliesslich ueber Anteile in Zehntausendsteln, nie ueber einen Geldbetrag;
//! eine Umrechnung ohne Aufrufer waere eine stehende Einladung, sie irgendwo zu
//! benutzen, wo sie nicht hingehoert.
//!
//! `B(z)`, `v(z)` und `e(z)` aus T44 stehen ebenfalls nicht hier: Sie sind
//! Pruefstandsgroessen, gehoeren dem Baustein `pruefstand` und verlassen die Partie
//! nie.

#include <array>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

namespace kern::werte {

// ---------------------------------------------------------------------------
// Die Zahlen neben dem Zustand
// ---------------------------------------------------------------------------

/// Die Kalibrierwerte und die eine Jahrgangskonstante, die in den Formeln aus T47 und
/// T48 neben den Zustandsadressen vorkommen.
///
/// **Warum sie als Argument hereinkommen und nicht aus einer Datei.** Der Kern liest
/// keine Datei (T2) und haengt an keinem Kasten -- `daten` haengt an `kern` und nicht
/// umgekehrt (T13). T27 schreibt vor, dass der Parametersatz beim Laden in eine
/// Struktur mit benannten Feldern faellt, nie ueber eine Schleife ueber Schluessel;
/// diese Struktur ist der Ausschnitt daraus, den die Bewertung braucht. Damit bleibt
/// Kalibrieren eine Datenaenderung, die kein Uebersetzen braucht.
///
/// Jedes Feld traegt seinen Schluesselnamen und seine Skalenklasse nach T5. Ein
/// Parameterschluessel ohne Klasse ist nach T27 derselbe Fehler wie eine Adresse ohne
/// Klasse.
///
/// **Alle Felder sind mit null vorbelegt, und das ist kein brauchbarer Parametersatz.**
/// Ein voreingestelltes `Konstanten` laesst `anleihekurs` an seinem Nenner abbrechen
/// und macht jeden Stufen- und Beteiligungswert null. Das ist gewollt: Ein plausibel
/// aussehender Vorgabewert waere eine Kalibrierung, die niemand beschlossen hat.
struct Konstanten {
    /// Schluessel `stufenweite` -- T5 Klasse 4 (Anteile, Zehntausendstel). Anteil des
    /// Marktes je Positionsstufe, **kein Geldbetrag**.
    zustand::i64 stufenweite = 0;

    /// Schluessel `ausstiegsabschlag` -- T5 Klasse 4. Abschlag auf den
    /// Beteiligungswert, im Wertansatz und damit beim Aufbau bezahlt (T47 Punkt 1).
    zustand::i64 ausstiegsabschlag = 0;

    /// Schluessel `aufschlag` -- T5 Klasse 3 (Raten, Basispunkte). Abstand zwischen
    /// Leitzins und Anleiherendite.
    zustand::i64 aufschlag = 0;

    /// Schluessel `lobbykosten` -- T5 Klasse 1 (Fondsgeld, US-Cent je Lobbypunkt,
    /// mindestens 1). Gelesen allein vom zweiten Skalenuebergang aus T50.
    zustand::i64 lobbykosten = 0;

    /// Schluessel `gegenlobby_satz` -- T5 Klasse 9 (Lobbypunkte je 10.000 Tausend USD
    /// Schaden). Gelesen allein vom dritten Skalenuebergang aus T50.
    zustand::i64 gegenlobby_satz = 0;

    /// Der Leitzins des Startjahrs je spielbarem Land -- T5 Klasse 3.
    ///
    /// **Keine Kalibriergroesse, sondern eine Messung**, und deshalb steht sie nach
    /// T27 nicht in `parameter.toml`, sondern im Jahrgang: Es ist die erste
    /// Stuetzstelle des Politikpfads, die der Jahrgang ohnehin traegt (T23 Punkt 5).
    /// Nur die vier spielbaren Laender haben einen Politikpfad; die Restwelt hat
    /// keinen und bekommt deshalb auch keinen Anleihekurs.
    std::array<zustand::i64, zustand::LAENDER> leitzins_start{};
};
