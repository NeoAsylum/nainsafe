#pragma once
//! `kern::zustand` -- die 310 Adressen als Wert fester Groesse.
//!
//! Vorgaben: T15 (310 Felder, 2.480 Byte, keine Speicheranforderung), T16 (Positionen
//! sind Steckplaetze), T17 (jede Groesse hat eine stabile Adresse), T9 (feste
//! Reihenfolge, keine streuenden Behaelter), T12 (kanonische Byteform).
//!
//! **Gebaut ist gegen `daten/adressen.md`, nicht gegen die Prosa von T15.** Das
//! Verzeichnis zaehlt die 310 Adressen einzeln auf; hier steht dieselbe Menge ein
//! zweites Mal, einmal als Rechenvorschrift (die `stelle_*`-Funktionen unten) und
//! einmal als Zeichentabelle in `src/zustand.cpp`. Dass beide Fassungen dieselbe
//! Menge in derselben Reihenfolge ergeben, ist kein Versprechen, sondern eine
//! `static_assert`-Schleife ueber alle 310 Zeilen.
//!
//! ## Der Aufbau in einem Bild
//!
//! Die Reihenfolge ist die laufende Nummer aus `daten/adressen.md`, minus eins:
//!
//!        0 ... 175   vier spielbare Laender, je 44 Felder (US, CN, DE, BR)
//!      176 ... 197   die Restwelt, 22 Felder
//!      198 ... 237   Handel, 5 Gebiete x 4 Gegenueber x 2 handelbare Sektoren
//!      238 ... 239   Weltpreise, je handelbarem Sektor
//!      240 ... 251   Nachahmerzaehler, 4 Laender x 3 Sektoren
//!      252 ... 253   Marktkorb: Wert, Rendite
//!      254 ... 258   Fondsaggregate
//!      259 ... 261   Ueberrenditen der letzten drei Runden
//!      262 ... 281   20 Positionssteckplaetze
//!      282 ... 305   12 Beteiligungen x (Anteil, Restdauer)
//!      306 ... 309   Partie
//!
//! Ein Gebietsblock ist in den ersten 21 Feldern fuer alle fuenf Gebiete gleich
//! gebaut (12 Sektorfelder, 9 Aggregate). Danach trennen sie sich: Die Restwelt hat
//! als 22. Feld sofort ihren `basiswechsel`, ein spielbares Land hat davor noch die
//! drei politischen Groessen, 16 Instrumentenfelder und drei Restdauerzaehler.
//! Deshalb nehmen `stelle_sektorgroesse` und `stelle_aggregat` alle fuenf Gebiete,
//! `stelle_politisch` und die drei folgenden nur die vier spielbaren.
//!
//! ## Warum ein flaches Feld und keine verschachtelten Untertypen
//!
//! Das Arbeitspaket stellt die Aufteilung ausdruecklich frei. Gewaehlt ist die
//! flache Fassung, weil daran drei Dinge ohne Zwischenschritt haengen: `sizeof` ist
//! ohne Auffuellbytes genau `310 * 8`, die kanonische Byteform aus T12 ist die
//! Zaehlschleife ueber denselben Index, und die Adressabbildung aus T17 liefert eine
//! Zahl statt eines Zeigers auf ein Element. Die Lesbarkeit, die ein Untertyp
//! gebracht haette, tragen stattdessen die `stelle_*`-Funktionen: Sie rechnen aus
//! benannten Aufzaehlungen, nie aus einer nackten Zahl.
//!
//! ## Was hier nicht steht
//!
//! Startwerte. Das Verzeichnis fuehrt fuer die Herkuenfte `Entwurf` und `Vorgabe`
//! eine Startwertspalte, aber die Werte kommen zusammen mit Jahrgang, Parametersatz
//! und Manifest -- also aus dem Kasten `daten` und nicht aus diesem Paket. Ein
//! frischer `Zustand` ist deshalb durchgehend null, und das ist ausdruecklich kein
//! Startzustand des Spiels.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"

namespace kern::zustand {

using i64 = std::int64_t;
using u64 = std::uint64_t;

/// Der Platz einer Groesse im Zustand, `0` bis `309`. Die laufende Nummer in
/// `daten/adressen.md` ist `index + 1`; das Verzeichnis zaehlt ab eins, der Kern ab
/// null, und die Umrechnung steht genau hier und nirgends sonst.
using Index = std::size_t;

/// T15: 310 Felder. Die Zahl steht an dieser einen Stelle.
inline constexpr Index FELDER = 310;

/// T12: die Laenge der kanonischen Byteform, `310 * 8`.
inline constexpr std::size_t BYTES = FELDER * pruefsumme::BYTES_JE_I64;

static_assert(BYTES == 2480, "T12: 310 Felder zu je acht Bytes sind 2.480 Byte");

// ---------------------------------------------------------------------------
// T9 -- die festen Reihenfolgen, als Aufzaehlung mit ausgeschriebenen Nummern
// ---------------------------------------------------------------------------
//
// Die Nummern stehen bei jedem Eintrag, statt vom Uebersetzer vergeben zu werden.
// Der Grund ist T17: Diese Reihenfolgen bestimmen ueber die `stelle_*`-Funktionen
// jeden der 310 Plaetze und damit die kanonische Byteform und jede je gerechnete
// Pruefsumme. Wer einen Eintrag einschiebt, verschiebt bei vergebenen Nummern
// stillschweigend alles dahinter; bei ausgeschriebenen sieht man es in der Zeile.

/// Die fuenf Gebiete in der Reihenfolge aus T9: `US, CN, DE, BR, RW`.
///
/// `RW` ist die Restwelt. Sie ist ein Gebiet und kein Land: Sie hat Sektoren und
/// Aggregate, aber keine Instrumente, keine Zustimmung, keinen Aufsichtszaehler,
/// keinen Einfluss und keine Restdauern (T15).
enum class Gebiet : std::uint8_t {
    US = 0,
    CN = 1,
    DE = 2,
    BR = 3,
    RW = 4,
};

inline constexpr std::size_t GEBIETE = 5;

/// Die vier spielbaren Laender sind die ersten vier Gebiete. Wer ueber Laender
/// laeuft, laeuft ueber `0 ... LAENDER-1` und trifft die Restwelt nie.
inline constexpr std::size_t LAENDER = 4;

/// Die drei Sektoren, nummeriert wie in der Adresse (`land.US.sektor.2.preis`).
///
/// Die Nummerierung beginnt bei eins und nicht bei null, damit die Zahl in der
/// Aufzaehlung und die Zahl in der Adresse dieselbe ist. Wer den Sektor als
/// Feldversatz braucht, nimmt `sektor_index`.
enum class Sektor : std::uint8_t {
    Landwirtschaft = 1,
    Industrie = 2,
    Dienstleistungen = 3,
};

inline constexpr std::size_t SEKTOREN = 3;

/// Handelszeilen gibt es nur fuer die Sektoren 1 und 2 (T15, Zeile "Handel").
inline constexpr std::size_t SEKTOREN_HANDELBAR = 2;

/// Die vier Politikinstrumente in der Reihenfolge aus T9.
enum class Instrument : std::uint8_t {
    Leitzins = 0,
    Zoll = 1,
    Haushalt = 2,
    Regulierung = 3,
};

inline constexpr std::size_t INSTRUMENTE = 4;

/// Die vier Groessen je Sektor, in der Reihenfolge aus T15.
enum class SektorGroesse : std::uint8_t {
    Wertschoepfung = 0,
    Kapitalstock = 1,
    Beschaeftigung = 2,
    Preis = 3,
};

inline constexpr std::size_t SEKTORGROESSEN = 4;

/// Die neun Aggregate je Gebiet, in der Reihenfolge aus T15.
///
/// Vier davon liest bei der Restwelt keine Modellregel (`Leitzins`, `Wechselkurs`,
/// `Staatsschuld`, `Haushaltssaldo`). Sie stehen trotzdem da, weil der Aggregatblock
/// fuer alle fuenf Gebiete gleich gebaut ist -- gleichfoermige Adressierung nach T17,
/// dieselbe Begruendung wie der dauerhaft leere Steckplatz aus T16.
enum class Aggregat : std::uint8_t {
    Bevoelkerung = 0,
    Erwerbstaetige = 1,
    Produktivitaet = 2,
    Preisniveau = 3,
    Inflation = 4,
    Leitzins = 5,
    Wechselkurs = 6,
    Staatsschuld = 7,
    Haushaltssaldo = 8,
};

inline constexpr std::size_t AGGREGATE = 9;

/// Die drei politischen Groessen je spielbarem Land.
enum class PolitischeGroesse : std::uint8_t {
    Zustimmung = 0,
    Aufsichtszaehler = 1,
    Einfluss = 2,
};

inline constexpr std::size_t POLITISCHE_GROESSEN = 3;

/// Die vier Felder je Instrument, in der Reihenfolge aus T15.
///
/// Das letzte heisst `Restverzoegerung` und nicht `Rest`. Das ist der Name aus T15,
/// T38 und T45; T23 Punkt 1 schreibt an einer Stelle `rest`, und dieser Widerspruch
/// steht als Befund 1 in `daten/adressen.md`. Gebaut ist gegen das Verzeichnis.
enum class InstrumentFeld : std::uint8_t {
    Stand = 0,
    Druck = 1,
    Gegendruck = 2,
    Restverzoegerung = 3,
};

inline constexpr std::size_t INSTRUMENTFELDER = 4;

/// Die drei Restdauerzaehler je spielbarem Land (T15, Gegenkraft 1 und 2).
enum class Restdauerzaehler : std::uint8_t {
    Marktverbot = 0,
    Lobbykosten = 1,
    Regierungsdruck = 2,
};

inline constexpr std::size_t RESTDAUERZAEHLER = 3;

/// Die beiden Groessen des Marktkorbs (T15, Zeile "Marktkorb").
enum class MarktGroesse : std::uint8_t {
    Wert = 0,
    Rendite = 1,
};

inline constexpr std::size_t MARKTGROESSEN = 2;

/// Die fuenf Fondsaggregate, in der Reihenfolge aus `daten/adressen.md`.
///
/// Die Reihenfolge weicht von der Aufzaehlung in T15 ab: Dort steht "Kasse,
/// Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil" als Fliesstext, das
/// Verzeichnis fuehrt `sichtbarkeit` vor `anlegerbestand`. Beide Fassungen nennen
/// dieselben fuenf Groessen; massgeblich ist nach dem Arbeitspaket das Verzeichnis.
enum class FondsGroesse : std::uint8_t {
    Kasse = 0,
    Hebelstand = 1,
    Sichtbarkeit = 2,
    Anlegerbestand = 3,
    Marktanteil = 4,
};

inline constexpr std::size_t FONDSGROESSEN = 5;

/// Die beiden Felder je Beteiligung (T15, Aktion 2).
enum class BeteiligungsFeld : std::uint8_t {
    Anteil = 0,
    Restdauer = 1,
};

inline constexpr std::size_t BETEILIGUNGSFELDER = 2;

/// Wie viele Runden Ueberrendite der Zustand mitfuehrt (T15: die letzten drei).
inline constexpr std::size_t UEBERRENDITE_RUNDEN = 3;

/// Die vier Felder der Partie.
enum class PartieFeld : std::uint8_t {
    Runde = 0,
    JahrgangId = 1,
    ParameterPruefsumme = 2,
    Mandatsstand = 3,
};

inline constexpr std::size_t PARTIEFELDER = 4;

// ---------------------------------------------------------------------------
// T16 -- die zwanzig Steckplaetze
// ---------------------------------------------------------------------------
//
// Eine Position ist eine vorzeichenbehaftete Stufenzahl auf einem festen Platz;
// null heisst "keine". Damit entfaellt jede Frage nach Hoechstzahl, Reihenfolge und
// Zusammenlegung, und der Zustand bleibt vergleichbar (T12). Es gibt keine Liste, in
// die etwas aufgenommen oder aus der etwas entfernt wuerde -- die zwanzig Plaetze
// stehen von der ersten bis zur letzten Runde da und tragen nur eine andere Zahl.

/// Die zwanzig Positionssteckplaetze: 12 Land x Sektor, 4 Waehrung, 4 Anleihe.
enum class Steckplatz : std::uint8_t {
    Sektor_US_1 = 0,
    Sektor_US_2 = 1,
    Sektor_US_3 = 2,
    Sektor_CN_1 = 3,
    Sektor_CN_2 = 4,
    Sektor_CN_3 = 5,
    Sektor_DE_1 = 6,
    Sektor_DE_2 = 7,
    Sektor_DE_3 = 8,
    Sektor_BR_1 = 9,
    Sektor_BR_2 = 10,
    Sektor_BR_3 = 11,
    Waehrung_US = 12,
    Waehrung_CN = 13,
    Waehrung_DE = 14,
    Waehrung_BR = 15,
    Anleihe_US = 16,
    Anleihe_CN = 17,
    Anleihe_DE = 18,
    Anleihe_BR = 19,
};

inline constexpr std::size_t STECKPLAETZE = 20;

/// Der erste Waehrungssteckplatz; davor liegen die zwoelf Sektorplaetze.
inline constexpr std::size_t STECKPLATZ_WAEHRUNG_ERSTER = 12;

/// Der erste Anleihensteckplatz.
inline constexpr std::size_t STECKPLATZ_ANLEIHE_ERSTER = 16;

/// **Ein Steckplatz ist dauerhaft leer: die Waehrung USA** (T16). Der US-Dollar ist
/// der Numeraire, eine Position darauf waere gegen sich selbst gerichtet. Der Platz
/// bleibt fuer die gleichfoermige Adressierung nach T17 stehen; die
/// Zulaessigkeitspruefung nach T32 bietet ihn nie an.
///
/// Diese Funktion ist die eine Stelle, an der das steht. T32 gehoert einem spaeteren
/// Paket, und wenn es die Ausnahme selbst noch einmal formulierte, gaebe es zwei
/// Fassungen derselben Regel -- und die zweite waere die, die jemand vergisst.
[[nodiscard]] constexpr bool steckplatz_spielbar(Steckplatz platz) noexcept
{
    return platz != Steckplatz::Waehrung_US;
}

/// Spielbar sind 19 der 20 Plaetze; wer 20 zaehlt, zaehlt Adressen, nicht
/// Moeglichkeiten (T16).
inline constexpr std::size_t STECKPLAETZE_SPIELBAR = 19;

// ---------------------------------------------------------------------------
// Die Bloecke und ihre Anfangsplaetze
// ---------------------------------------------------------------------------

/// Felder je spielbarem Land (T15: `12 + 9 + 3 + 16 + 3 + 1`).
inline constexpr Index LAND_FELDER = 44;

/// Felder der Restwelt (T15: `12 + 9 + 1`).
inline constexpr Index RESTWELT_FELDER = 22;

/// Die ersten 21 Felder eines Gebietsblocks sind fuer alle fuenf Gebiete gleich
/// gebaut. Ab hier laufen Land und Restwelt auseinander.
inline constexpr Index GEBIET_SEKTOREN_AB = 0;
inline constexpr Index GEBIET_AGGREGATE_AB = 12;

/// Nur spielbare Laender, gezaehlt ab dem Anfang ihres 44er-Blocks.
inline constexpr Index LAND_POLITISCH_AB = 21;
inline constexpr Index LAND_INSTRUMENTE_AB = 24;
inline constexpr Index LAND_RESTDAUERN_AB = 40;
inline constexpr Index LAND_BASISWECHSEL = 43;

/// Die Restwelt hat ihren `basiswechsel` sofort nach dem Aggregatblock.
inline constexpr Index RESTWELT_BASISWECHSEL = 21;

inline constexpr Index BASIS_RESTWELT = LAENDER * LAND_FELDER;           // 176
inline constexpr Index BASIS_HANDEL = BASIS_RESTWELT + RESTWELT_FELDER;  // 198
inline constexpr Index BASIS_WELTPREIS = 238;
inline constexpr Index BASIS_NACHAHMER = 240;
inline constexpr Index BASIS_MARKT = 252;
inline constexpr Index BASIS_FONDS = 254;
inline constexpr Index BASIS_UEBERRENDITE = 259;
inline constexpr Index BASIS_POSITION = 262;
inline constexpr Index BASIS_BETEILIGUNG = 282;
inline constexpr Index BASIS_PARTIE = 306;

// Die Bloecke gehen lueckenlos ineinander ueber und enden genau auf 310. Das ist die
// Gegenrechnung zur Gruppentabelle aus T15 (`198 + 56 + 52 + 4`) -- nicht Summe gegen
// Summe, sondern Blockgrenze gegen Blockgrenze.
static_assert(BASIS_RESTWELT == 176);
static_assert(BASIS_HANDEL == 198);
static_assert(BASIS_HANDEL + GEBIETE * (GEBIETE - 1) * SEKTOREN_HANDELBAR == BASIS_WELTPREIS);
static_assert(BASIS_WELTPREIS + SEKTOREN_HANDELBAR == BASIS_NACHAHMER);
static_assert(BASIS_NACHAHMER + LAENDER * SEKTOREN == BASIS_MARKT);
static_assert(BASIS_MARKT + MARKTGROESSEN == BASIS_FONDS);
static_assert(BASIS_FONDS + FONDSGROESSEN == BASIS_UEBERRENDITE);
static_assert(BASIS_UEBERRENDITE + UEBERRENDITE_RUNDEN == BASIS_POSITION);
static_assert(BASIS_POSITION + STECKPLAETZE == BASIS_BETEILIGUNG);
static_assert(BASIS_BETEILIGUNG + LAENDER * SEKTOREN * BETEILIGUNGSFELDER == BASIS_PARTIE);
static_assert(BASIS_PARTIE + PARTIEFELDER == FELDER);

// Und dieselbe Rechnung noch einmal von innen: die 44 eines Landes und die 22 der
// Restwelt aus ihren Gruppen.
static_assert(SEKTOREN * SEKTORGROESSEN + AGGREGATE + POLITISCHE_GROESSEN
                      + INSTRUMENTE * INSTRUMENTFELDER + RESTDAUERZAEHLER + 1
                  == LAND_FELDER);
static_assert(SEKTOREN * SEKTORGROESSEN + AGGREGATE + 1 == RESTWELT_FELDER);
static_assert(LAND_POLITISCH_AB == GEBIET_AGGREGATE_AB + AGGREGATE);
static_assert(RESTWELT_BASISWECHSEL == GEBIET_AGGREGATE_AB + AGGREGATE);
static_assert(LAND_INSTRUMENTE_AB == LAND_POLITISCH_AB + POLITISCHE_GROESSEN);
static_assert(LAND_RESTDAUERN_AB == LAND_INSTRUMENTE_AB + INSTRUMENTE * INSTRUMENTFELDER);
static_assert(LAND_BASISWECHSEL == LAND_RESTDAUERN_AB + RESTDAUERZAEHLER);
static_assert(STECKPLATZ_WAEHRUNG_ERSTER == LAENDER * SEKTOREN);
static_assert(STECKPLATZ_ANLEIHE_ERSTER == STECKPLATZ_WAEHRUNG_ERSTER + LAENDER);
static_assert(STECKPLATZ_ANLEIHE_ERSTER + LAENDER == STECKPLAETZE);
static_assert(STECKPLAETZE_SPIELBAR + 1 == STECKPLAETZE, "T16: genau ein Platz bleibt leer");

// ---------------------------------------------------------------------------
// Der Zustand
// ---------------------------------------------------------------------------

/// Der ganze Weltzustand als Wert fester Groesse (T15).
///
/// Kein wachsender Behaelter, kein Text, keine streuende Zuordnung, keine eigene
/// Speicherverwaltung. Kopieren ist damit ein Speicherumzug von 2,5 kB und keine
/// Zuteilung -- die Voraussetzung dafuer, dass der Pruefstand Millionen Nachspiele
/// aus Zwischenstaenden startet.
///
/// **Zum Schreibzugriff:** T18 will, dass innerhalb des Kerns niemand direkt
/// schreibt, sondern ueber `Schreiber::setze(adresse, wert, ursache, ...)`, und dass
/// die Felder ausserhalb des Kerns gar nicht schreibbar sind. C++ kennt keine
/// Sichtbarkeit "innerhalb des Kastens"; die Durchsetzung gehoert deshalb dem Paket,
/// das den Schreiber baut. `schreibe` ist der Zugriff, den er benutzt -- und die
/// Stelle, an der ausser ihm niemand stehen sollte.
struct Zustand {
    /// Die 310 Groessen in der Reihenfolge aus `daten/adressen.md`.
    std::array<i64, FELDER> feld{};

    /// Lesen mit Indexpruefung. Ein Index ausserhalb `0 ... 309` bricht ab.
    [[nodiscard]] constexpr i64 lies(Index index) const
    {
        if (index >= FELDER) {
            festkomma::abbruch("kern::zustand::lies -- Index ausserhalb der 310 Felder");
        }
        return feld[index];
    }

    /// Schreiben mit Indexpruefung. Siehe die Bemerkung zu T18 oben.
    constexpr void schreibe(Index index, i64 wert)
    {
        if (index >= FELDER) {
            festkomma::abbruch("kern::zustand::schreibe -- Index ausserhalb der 310 Felder");
        }
        feld[index] = wert;
    }

    /// Feldweiser Vergleich -- die Grundlage der Diff-Ebene und des Rueckvergleichs:
    /// Zwei Zustaende sind gleich, wenn alle 310 Zahlen gleich sind.
    constexpr bool operator==(const Zustand&) const = default;
};

/// Die Abnahmebedingung des Arbeitspakets, mechanisch: Die Feldzahl wird aus
/// `sizeof(Zustand)` zurueckgerechnet und muss 310 ergeben, die Groesse selbst
/// 2.480 Byte. Stimmt eine der beiden Zahlen nicht, ist der Bau rot -- und nicht eine
/// Zeile in einem Bericht, die jemand liest oder auch nicht.
static_assert(sizeof(Zustand) == 2480, "T15: der Zustand ist 2.480 Byte gross");
static_assert(sizeof(Zustand) / sizeof(i64) == FELDER, "T15: 310 Felder");
static_assert(std::is_trivially_copyable_v<Zustand>,
              "T15: Kopieren ist ein Speicherumzug, keine Zuteilung");

// ---------------------------------------------------------------------------
// T17 -- die Adressabbildung, beide Richtungen
// ---------------------------------------------------------------------------

/// Das Ergebnis einer Adresssuche.
///
/// Ein Ergebnistyp mit einem Ja-Nein-Feld statt eines Behaelters aus der
/// Standardbibliothek, der "vielleicht ein Wert" bedeutet: T15 schliesst solche
/// Behaelter im Zustand aus, und ein zweiter Weg, dasselbe zu sagen, waere genau die
/// Sorte Ausnahme, deren Begruendung spaeter niemand mehr findet.
struct Adressfund {
    bool gefunden = false;
    Index index = 0;
};

/// Adresse nach T17 -> Platz im Zustand.
///
/// `adresse` ist ein nullbyte-begrenzter Text. Steht sie nicht in
/// `daten/adressen.md`, kommt `{false, 0}` zurueck -- eine unbekannte Adresse ist
/// eine Frage und kein Fehler: Sie kommt aus Protokoll, Testvorlage oder Oberflaeche
/// und darf dort beantwortet werden. Ein Nullzeiger gilt als unbekannte Adresse.
[[nodiscard]] Adressfund adresse_zu_index(const char* adresse) noexcept;

/// Platz im Zustand -> Adresse nach T17.
///
/// Der Rueckgabewert zeigt auf einen Eintrag der Adresstabelle in `src/zustand.cpp`
/// und lebt so lange wie das Programm. Ein Index ausserhalb `0 ... 309` bricht ab --
/// anders als bei der Gegenrichtung gibt es hier keine offene Frage, sondern nur
/// einen Rechenfehler des Aufrufers.
[[nodiscard]] const char* index_zu_adresse(Index index);

/// Die laengste Adresse ist `land.US.instrument.regulierung.restverzoegerung` mit 47
/// Zeichen. Der Puffer traegt sie samt Nullbyte und hat Luft; dass keine Adresse
/// laenger ist, prueft `src/zustand.cpp` beim Uebersetzen ueber die ganze Tabelle.
inline constexpr std::size_t ADRESSE_PUFFER = 64;

// ---------------------------------------------------------------------------
// Die Plaetze, aus benannten Aufzaehlungen gerechnet
// ---------------------------------------------------------------------------
//
// Jede dieser Funktionen ist die Umkehrung einer Zeilengruppe aus
// `daten/adressen.md`. Sie sind `constexpr`: Ein Platz, der aus festen
// Aufzaehlungswerten kommt, ist damit eine Zahl im uebersetzten Programm und keine
// Rechnung zur Laufzeit -- und ein falsches Argument, das schon beim Uebersetzen
// feststeht, ist ein Uebersetzungsfehler statt eines Abbruchs in Runde 400.

/// Der Sektor als Feldversatz `0 ... 2`. Die Aufzaehlung zaehlt ab eins (wie die
/// Adresse), der Block ab null.
[[nodiscard]] constexpr std::size_t sektor_index(Sektor sektor)
{
    const std::size_t nummer = static_cast<std::size_t>(sektor);
    if (nummer < 1 || nummer > SEKTOREN) {
        festkomma::abbruch("kern::zustand -- unbekannter Sektor");
    }
    return nummer - 1;
}

/// Handelszeilen gibt es nur fuer die Sektoren 1 und 2.
[[nodiscard]] constexpr bool sektor_handelbar(Sektor sektor)
{
    return sektor_index(sektor) < SEKTOREN_HANDELBAR;
}

/// Der Anfang des Gebietsblocks. Die vier Laender liegen zu je 44 Feldern
/// hintereinander, die Restwelt danach mit ihren 22.
[[nodiscard]] constexpr Index gebiet_basis(Gebiet gebiet)
{
    const std::size_t nummer = static_cast<std::size_t>(gebiet);
    if (nummer >= GEBIETE) {
        festkomma::abbruch("kern::zustand -- unbekanntes Gebiet");
    }
    return nummer < LAENDER ? nummer * LAND_FELDER : BASIS_RESTWELT;
}

/// Wie `gebiet_basis`, aber nur fuer die vier spielbaren Laender. Die Restwelt hat
/// keine Instrumente, keine Zustimmung, keinen Aufsichtszaehler, keinen Einfluss und
/// keine Restdauern (T15); ein Aufruf mit `RW` ist deshalb ein Programmfehler und
/// kein Sonderfall, der stillschweigend etwas anderes zurueckgibt.
[[nodiscard]] constexpr Index land_basis(Gebiet land)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- diese Groesse gibt es nur bei spielbaren Laendern");
    }
    return nummer * LAND_FELDER;
}

[[nodiscard]] constexpr Index stelle_sektorgroesse(Gebiet gebiet, Sektor sektor,
                                                   SektorGroesse groesse)
{
    const std::size_t g = static_cast<std::size_t>(groesse);
    if (g >= SEKTORGROESSEN) {
        festkomma::abbruch("kern::zustand -- unbekannte Sektorgroesse");
    }
    return gebiet_basis(gebiet) + GEBIET_SEKTOREN_AB + sektor_index(sektor) * SEKTORGROESSEN + g;
}

[[nodiscard]] constexpr Index stelle_aggregat(Gebiet gebiet, Aggregat groesse)
{
    const std::size_t a = static_cast<std::size_t>(groesse);
    if (a >= AGGREGATE) {
        festkomma::abbruch("kern::zustand -- unbekanntes Aggregat");
    }
    return gebiet_basis(gebiet) + GEBIET_AGGREGATE_AB + a;
}

/// `basiswechsel` haben alle fuenf Gebiete -- aber an verschiedener Stelle im Block,
/// weil die Restwelt die zweiundzwanzig Felder dazwischen nicht hat.
[[nodiscard]] constexpr Index stelle_basiswechsel(Gebiet gebiet)
{
    const std::size_t nummer = static_cast<std::size_t>(gebiet);
    if (nummer >= GEBIETE) {
        festkomma::abbruch("kern::zustand -- unbekanntes Gebiet");
    }
    return nummer < LAENDER ? land_basis(gebiet) + LAND_BASISWECHSEL
                            : BASIS_RESTWELT + RESTWELT_BASISWECHSEL;
}

[[nodiscard]] constexpr Index stelle_politisch(Gebiet land, PolitischeGroesse groesse)
{
    const std::size_t p = static_cast<std::size_t>(groesse);
    if (p >= POLITISCHE_GROESSEN) {
        festkomma::abbruch("kern::zustand -- unbekannte politische Groesse");
    }
    return land_basis(land) + LAND_POLITISCH_AB + p;
}

[[nodiscard]] constexpr Index stelle_instrument(Gebiet land, Instrument instrument,
                                                InstrumentFeld feld)
{
    const std::size_t i = static_cast<std::size_t>(instrument);
    const std::size_t f = static_cast<std::size_t>(feld);
    if (i >= INSTRUMENTE || f >= INSTRUMENTFELDER) {
        festkomma::abbruch("kern::zustand -- unbekanntes Instrument oder Instrumentenfeld");
    }
    return land_basis(land) + LAND_INSTRUMENTE_AB + i * INSTRUMENTFELDER + f;
}

[[nodiscard]] constexpr Index stelle_restdauer(Gebiet land, Restdauerzaehler zaehler)
{
    const std::size_t r = static_cast<std::size_t>(zaehler);
    if (r >= RESTDAUERZAEHLER) {
        festkomma::abbruch("kern::zustand -- unbekannter Restdauerzaehler");
    }
    return land_basis(land) + LAND_RESTDAUERN_AB + r;
}

/// Der Handelsstrom von `von` nach `nach` im Sektor `sektor`.
///
/// Der Block laeuft ueber alle fuenf Gebiete; jedes hat vier Gegenueber, naemlich die
/// vier anderen in der Reihenfolge aus T9. Der Platz des Gegenuebers in dieser
/// Viererliste ist seine Gebietsnummer, vermindert um eins, sobald sie hinter der
/// eigenen liegt -- das ist die feste Abbildung aus T9, ausgerechnet statt
/// nachgeschlagen.
[[nodiscard]] constexpr Index stelle_handel(Gebiet von, Gebiet nach, Sektor sektor)
{
    const std::size_t v = static_cast<std::size_t>(von);
    const std::size_t n = static_cast<std::size_t>(nach);
    if (v >= GEBIETE || n >= GEBIETE) {
        festkomma::abbruch("kern::zustand -- unbekanntes Gebiet im Handel");
    }
    if (v == n) {
        festkomma::abbruch("kern::zustand -- ein Gebiet handelt nicht mit sich selbst");
    }
    if (!sektor_handelbar(sektor)) {
        festkomma::abbruch("kern::zustand -- dieser Sektor hat keine Handelszeile");
    }
    const std::size_t gegenueber = n < v ? n : n - 1;
    return BASIS_HANDEL + (v * (GEBIETE - 1) + gegenueber) * SEKTOREN_HANDELBAR
           + sektor_index(sektor);
}

[[nodiscard]] constexpr Index stelle_weltpreis(Sektor sektor)
{
    if (!sektor_handelbar(sektor)) {
        festkomma::abbruch("kern::zustand -- einen Weltpreis gibt es nur je handelbarem Sektor");
    }
    return BASIS_WELTPREIS + sektor_index(sektor);
}

[[nodiscard]] constexpr Index stelle_nachahmer(Gebiet land, Sektor sektor)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- Nachahmer gibt es nur bei spielbaren Laendern");
    }
    return BASIS_NACHAHMER + nummer * SEKTOREN + sektor_index(sektor);
}

[[nodiscard]] constexpr Index stelle_markt(MarktGroesse groesse)
{
    const std::size_t m = static_cast<std::size_t>(groesse);
    if (m >= MARKTGROESSEN) {
        festkomma::abbruch("kern::zustand -- unbekannte Marktgroesse");
    }
    return BASIS_MARKT + m;
}

[[nodiscard]] constexpr Index stelle_fonds(FondsGroesse groesse)
{
    const std::size_t f = static_cast<std::size_t>(groesse);
    if (f >= FONDSGROESSEN) {
        festkomma::abbruch("kern::zustand -- unbekannte Fondsgroesse");
    }
    return BASIS_FONDS + f;
}

/// Die Ueberrendite der `runden_zurueck`-letzten Runde, `1` bis `3` -- dieselbe Zahl
/// wie in der Adresse `fonds.ueberrendite.<n>`.
[[nodiscard]] constexpr Index stelle_ueberrendite(std::size_t runden_zurueck)
{
    if (runden_zurueck < 1 || runden_zurueck > UEBERRENDITE_RUNDEN) {
        festkomma::abbruch("kern::zustand -- es gibt genau drei Ueberrenditerunden");
    }
    return BASIS_UEBERRENDITE + runden_zurueck - 1;
}

[[nodiscard]] constexpr Index stelle_position(Steckplatz platz)
{
    const std::size_t p = static_cast<std::size_t>(platz);
    if (p >= STECKPLAETZE) {
        festkomma::abbruch("kern::zustand -- unbekannter Steckplatz");
    }
    return BASIS_POSITION + p;
}

[[nodiscard]] constexpr Index stelle_beteiligung(Gebiet land, Sektor sektor,
                                                 BeteiligungsFeld feld)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    const std::size_t f = static_cast<std::size_t>(feld);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- Beteiligungen gibt es nur an spielbaren Laendern");
    }
    if (f >= BETEILIGUNGSFELDER) {
        festkomma::abbruch("kern::zustand -- unbekanntes Beteiligungsfeld");
    }
    return BASIS_BETEILIGUNG + (nummer * SEKTOREN + sektor_index(sektor)) * BETEILIGUNGSFELDER
           + f;
}

[[nodiscard]] constexpr Index stelle_partie(PartieFeld feld)
{
    const std::size_t p = static_cast<std::size_t>(feld);
    if (p >= PARTIEFELDER) {
        festkomma::abbruch("kern::zustand -- unbekanntes Partiefeld");
    }
    return BASIS_PARTIE + p;
}

// ---------------------------------------------------------------------------
// Die Steckplaetze und ihre drei Arten
// ---------------------------------------------------------------------------

[[nodiscard]] constexpr Steckplatz steckplatz_sektor(Gebiet land, Sektor sektor)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- Positionen gibt es nur auf spielbaren Laendern");
    }
    return static_cast<Steckplatz>(nummer * SEKTOREN + sektor_index(sektor));
}

[[nodiscard]] constexpr Steckplatz steckplatz_waehrung(Gebiet land)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- Waehrungsplaetze gibt es nur bei spielbaren Laendern");
    }
    return static_cast<Steckplatz>(STECKPLATZ_WAEHRUNG_ERSTER + nummer);
}

[[nodiscard]] constexpr Steckplatz steckplatz_anleihe(Gebiet land)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch("kern::zustand -- Anleihenplaetze gibt es nur bei spielbaren Laendern");
    }
    return static_cast<Steckplatz>(STECKPLATZ_ANLEIHE_ERSTER + nummer);
}

// ---------------------------------------------------------------------------
// T12 -- die kanonische Byteform
// ---------------------------------------------------------------------------

/// Der Zustand als 2.480 Bytes: 310 Felder in der festen Reihenfolge dieses Moduls,
/// jedes als `int64_t` in Little-Endian.
///
/// **Nie ueber die Speicheranordnung der Struktur.** Die Funktion laeuft ueber den
/// Index und ruft je Feld die Zerlegung aus `kern::pruefsumme` auf; sie liest kein
/// Byte des Zustands als Byte. Der Unterschied ist nicht theoretisch: Eine Byteform
/// aus dem Speicherbild waere an Auffuellbytes, Anordnung und Bytereihenfolge der
/// Maschine gebunden, und jede gespeicherte Partie waere damit an den Uebersetzer
/// gebunden, der sie geschrieben hat.
void nach_bytes(const Zustand& zustand, std::array<std::uint8_t, BYTES>& ziel) noexcept;

/// FNV-1a-64 ueber die kanonische Byteform -- die Waehrung aller Regressionstests.
///
/// Gerechnet wird ueber die Kette aus Paket 0013, Feld fuer Feld. Es gibt hier keinen
/// zweiten Summenalgorithmus und keinen Zwischenspeicher ueber alle 2.480 Bytes: Die
/// Reihenfolge der Aufrufe **ist** die feste Feldreihenfolge aus T12, und sie steht
/// als Schleife ueber den Index da statt in einem Puffer.
[[nodiscard]] u64 pruefsumme_von(const Zustand& zustand) noexcept;

}  // namespace kern::zustand
