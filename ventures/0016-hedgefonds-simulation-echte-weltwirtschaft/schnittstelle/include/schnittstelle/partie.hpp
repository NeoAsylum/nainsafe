#pragma once
//! `schnittstelle::partie` -- der Speicherstand nach T22 und der Schreiber dafuer.
//!
//! Vorgaben: T22 (ein Speicherstand ist Jahrgang, Modus, Startwert, Aktionsfolge und
//! Pruefsumme -- **nicht** der Zustand), T32 (die drei Ordnungsschluessel einer Aktion
//! und ihre kanonische Reihenfolge), T21 (jede Antwort traegt `schema_version`), T13
//! (dieses Mitglied haengt an `kern` und `daten`, nie umgekehrt), ADR 0011
//! (Ganzzahlarithmetik, kein Gleitkomma).
//!
//! ## Was dieser Kasten baut und was er ausdruecklich nicht baut
//!
//! **Er schreibt. Er liest nicht.** Das Gegenstueck aus T22 -- beim Laden wird die
//! Partie nachgerechnet und die Pruefsumme verglichen -- ist ein eigenes Paket: Ein
//! Schreiber fuer acht feste Felder ist begrenzt, ein Leser, der Fehlformen abweisen
//! muss, ist es nicht. Andersherum liesse sich der Schnitt nicht legen, denn ein Leser
//! ohne Eingabe ist nicht pruefbar; die Ausgabe dieses Schreibers ist der Prueffall des
//! Lesers.
//!
//! **Vier der acht Felder werden getragen, nicht gerechnet.** `jahrgang_id`, `modus`,
//! `daten_pruefsumme` und `startwert` kommen fertig herein. Sie zu fuellen ist Sache des
//! Jahrgangs und des Befehls `neu` aus T21; das Format befoerdert sie. Genau deshalb
//! haengt dieser Kasten an keinem von beiden.
//!
//! ## Warum der Traeger kein neunter Platz hat
//!
//! T22 nennt acht Felder. Die Zahl der Zuege steht deshalb **in** `Aktionsfolge` und
//! nicht als neuntes Feld daneben: Ein Traeger mit einem Feld, das die Vorgabe nicht
//! kennt, schriebe entweder ein Feld zu viel oder fuehrte eine Zahl mit, die in keiner
//! Zeile ankommt. Die Zusicherung weiter unten haelt das beim Uebersetzen -- gezaehlt
//! wird ueber `kern::schritt::feldzahl`, also an der Aufbauliste und nicht an `sizeof`.
//!
//! ## Warum der Puffer aus `kern::zustandsausgabe` kommt
//!
//! `Ausgabe` ist ein Puffer fester Groesse, an den nur angehaengt wird, mit einer
//! Zahlenumwandlung auf `i128` und einer Marke fuer den abgeschnittenen Fall. Eine
//! zweite Fassung davon in diesem Mitglied waere eine zweite Zahlenumwandlung -- und zwei
//! Zahlenumwandlungen sind der Anfang zweier Wahrheiten ueber dieselbe Zahl.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/verlauf.hpp"
#include "kern/zustandsausgabe.hpp"

namespace schnittstelle::partie {

using i64 = std::int64_t;
using u64 = std::uint64_t;

// ---------------------------------------------------------------------------
// Die acht Felder aus T22
// ---------------------------------------------------------------------------

/// Die Fassung des Formats. Sie steht in jedem Speicherstand und nach T21 in jeder
/// Antwort der Maschinenschnittstelle; ein Leser, der sie nicht kennt, weist ab, statt
/// zu raten.
inline constexpr i64 SCHEMA_VERSION = 1;

/// Die acht Felder, und ihr Wert ist ihr Platz in der Zeile.
///
/// Dieselbe Bauform wie bei den Ordnungsschluesseln aus T32: Die Reihenfolge ist eine
/// benannte Eigenschaft und keine Nebenwirkung der Schreibschleife. Wer sie aendert,
/// entwertet jeden gespeicherten Stand -- das gehoert in einen ADR und nicht in eine
/// umgestellte Zeile.
enum class Feld : std::size_t {
    SchemaVersion = 0,
    JahrgangId = 1,
    Modus = 2,
    DatenPruefsumme = 3,
    ParameterPruefsumme = 4,
    Startwert = 5,
    Aktionen = 6,
    EndPruefsumme = 7,
};

/// Wie viele Felder ein Speicherstand traegt. T22 nennt acht.
inline constexpr std::size_t FELDER = 8;

/// Die Namen der acht Felder, in der Reihenfolge ihrer Plaetze. Das ist die einzige
/// Stelle, an der sie stehen -- der Schreiber liest sie hier und schreibt sie nicht ein
/// zweites Mal hin.
inline constexpr std::array<const char*, FELDER> FELDNAME = {
    "schema_version",
    "jahrgang_id",
    "modus",
    "daten_pruefsumme",
    "parameter_pruefsumme",
    "startwert",
    "aktionen",
    "end_pruefsumme"};

/// Das Feld auf Platz `platz`. Ein Platz daneben bricht ab.
[[nodiscard]] constexpr Feld feld_des_platzes(std::size_t platz)
{
    if (platz >= FELDER) {
        kern::festkomma::abbruch("schnittstelle::partie -- Platz ausserhalb der acht "
                                 "Felder aus T22");
    }
    return static_cast<Feld>(platz);
}

// ---------------------------------------------------------------------------
// Der Traeger
// ---------------------------------------------------------------------------

/// Eine Aktion mit der Runde, in der sie gesetzt wurde -- das Paar, das T22 in
/// `aktionen` ablegt.
struct Zug {
    /// Die Runde. Sie zaehlt nach T40 ab eins; geprueft wird das dort, wo eine Aktion
    /// ankommt, und nicht hier -- dieser Kasten befoerdert, was ihm gegeben wird.
    i64 runde = 0;
    /// Die Aktion mit ihren drei Ordnungsschluesseln aus T32.
    kern::aktion::Aktion aktion{};
};

/// Wie viele Aktionen eine Runde nach T32 hoechstens traegt: mehr als drei in einem
/// Buendel ist unzulaessig. Die Zahl steht hier, weil der Kern sie nicht fuehrt -- die
/// Buendelzulaessigkeit ist dort ein offenes Paket.
inline constexpr std::size_t AKTIONEN_JE_RUNDE = 3;

/// Wie viele Zuege ein Speicherstand fasst.
///
/// Gebildet aus der Wand, die T40 ueber die Partielaenge zieht, mal der Zahl je Runde --
/// nicht aus einem Jahrgang. Ein Behaelter, dessen Kapazitaet an der Partielaenge eines
/// bestimmten Jahrgangs haenge, braeuchte fuer jeden anderen eine andere Uebersetzung;
/// dieselbe Begruendung traegt `kern::verlauf::RUNDEN_KAPAZITAET`.
inline constexpr std::size_t ZUEGE_HOECHSTENS =
    kern::verlauf::PARTIELAENGE_HOECHSTENS * AKTIONEN_JE_RUNDE;

/// Die Aktionsfolge: der Behaelter und die Zahl der belegten Plaetze, **ein** Feld.
///
/// Warum die Zahl hierher gehoert und nicht neben den Behaelter, steht im Kopf dieser
/// Datei: T22 kennt acht Felder, und der Riegel darunter haelt es bei acht.
struct Aktionsfolge {
    std::array<Zug, ZUEGE_HOECHSTENS> eintraege{};
    std::size_t anzahl = 0;
};

/// Ein Speicherstand nach T22 -- Jahrgang, Modus, Startwert, Aktionsfolge und
/// Pruefsummen. **Nicht der Zustand.** Die 310 Adressen entstehen beim Laden neu; genau
/// das ist der Grund, aus dem eine Datei unter zwei Kilobyte bleibt und aus dem ein
/// Determinismusfehler beim Kaeufer als erstes auffaellt.
struct Partie {
    /// Platz 0 -- die Fassung des Formats.
    i64 schema_version = SCHEMA_VERSION;
    /// Platz 1 -- der Jahrgang, aus dem der Startzustand gebaut wird. Getragen.
    i64 jahrgang_id = 0;
    /// Platz 2 -- der Modus aus T38. Getragen.
    kern::schreiber::Modus modus = kern::schreiber::Modus::Weltlauf;
    /// Platz 3 -- die Pruefsumme ueber den Jahrgang. Getragen.
    u64 daten_pruefsumme = 0;
    /// Platz 4 -- die Pruefsumme ueber die Schluesselfelder des Parametersatzes. Sie
    /// kommt aus `kern::schritt::parameter_pruefsumme` und nirgendwo sonst her; ein
    /// zweiter Rechenweg saehe aus wie ein fremder Parametersatz.
    i64 parameter_pruefsumme = 0;
    /// Platz 5 -- der Wurzelstartwert der Partie. Getragen.
    u64 startwert = 0;
    /// Platz 6 -- die Zuege in der Reihenfolge, in der sie gesetzt wurden.
    Aktionsfolge aktionen{};
    /// Platz 7 -- die Pruefsumme des Endzustands, aus `kern::zustand::pruefsumme_von`.
    u64 end_pruefsumme = 0;
};

// Der Riegel gegen das neunte Feld. Gezaehlt wird, wie viele Stellen eine Aufbauliste
// des Verbunds annimmt -- ohne `sizeof`, ohne Fuellbytes, ohne die Anordnung im
// Speicher. Wer ein Feld zulegt, ohne es in `Feld` und `FELDNAME` aufzunehmen, uebersetzt
// dieses Mitglied nicht mehr.
static_assert(kern::schritt::feldzahl<Partie> == FELDER,
              "T22: ein Speicherstand traegt acht Felder. Wer eines zulegt, nimmt es in "
              "`Feld`, in `FELDNAME` und in die Schreibschleife auf -- ein Feld, das in "
              "keiner der drei Stellen steht, wird getragen und nie geschrieben.");

static_assert(FELDNAME.size() == FELDER,
              "T22: zu jedem Feld gehoert genau ein Name in der Zeile");

// Die Zahl der Zuege sitzt in `Aktionsfolge` und nicht in `Partie`. Waere sie
// herausgezogen, zaehlte der Riegel darueber neun -- und die Zusicherung hier ist die
// Gegenprobe dazu, dass der Behaelter beides wirklich fuehrt.
static_assert(kern::schritt::feldzahl<Aktionsfolge> == 2,
              "die Aktionsfolge traegt den Behaelter und die Zahl der belegten Plaetze");

// ---------------------------------------------------------------------------
// Die Zeile
// ---------------------------------------------------------------------------

/// Zeichen, die ein Zug hoechstens belegt.
///
/// Nachgerechnet und nicht geschaetzt: `[runde,art,ziel,stufe]` sind zwei Klammern, drei
/// Trennzeichen und vier Zahlen -- die Runde und die Stufe je hoechstens 20 Zeichen (der
/// kleinste `i64` traegt sein Vorzeichen mit), die Art eines, die Zielkennung fuenf.
/// Macht 50, dazu das Trennzeichen zum naechsten Zug. Aufgerundet auf 64; was der Puffer
/// wirklich fasst, misst `test/partie_probe.cpp` an einer vollen Folge.
inline constexpr std::size_t ZEICHEN_JE_ZUG = 64;

/// Zeichen, die die uebrigen sieben Felder hoechstens belegen: 97 fuer die acht Namen,
/// 24 fuer Anfuehrung und Doppelpunkt, sieben Trennzeichen, zwei geschweifte Klammern und
/// hoechstens 123 fuer die sieben Zahlen -- zusammen 253. Aufgerundet auf 320.
inline constexpr std::size_t KOPF_ZEICHEN = 320;

/// Die Groesse des Zeilenpuffers, aus den beiden Zahlen darueber gebildet.
inline constexpr std::size_t PARTIE_ZEICHEN =
    KOPF_ZEICHEN + ZUEGE_HOECHSTENS * ZEICHEN_JE_ZUG + 1;

/// Eine Zeile JSON -- derselbe Puffer, den die drei Zustandsebenen benutzen.
using Partiezeile = kern::zustandsausgabe::Ausgabe<PARTIE_ZEICHEN>;

/// Schreibt den Speicherstand als **eine** Zeile JSON.
///
/// Die Feldreihenfolge ist die von `Feld`, ausserhalb von Zeichenketten steht kein
/// Leerraum, und jede Zahl steht in Zehnerschreibweise ohne Tausendertrennung -- eine
/// Zeile, die eine Maschine liest, und nach T21 eine Zeile je Antwort.
///
/// `modus` und die Aktionsart stehen als Zahl und nicht als Name: Ein Speicherstand geht
/// in die Pruefsumme ein, und ein Feld mit zwei Schreibweisen desselben Wertes machte aus
/// einer Partie zwei Dateien.
///
/// Harter Fehler ohne Ersatzwert: `aktionen.anzahl` liegt oberhalb der Kapazitaet. Eine
/// stillschweigend gekuerzte Folge waere ein Speicherstand, der sich laden laesst und
/// eine andere Partie rechnet.
[[nodiscard]] Partiezeile schreibe(const Partie& stand);

}  // namespace schnittstelle::partie
