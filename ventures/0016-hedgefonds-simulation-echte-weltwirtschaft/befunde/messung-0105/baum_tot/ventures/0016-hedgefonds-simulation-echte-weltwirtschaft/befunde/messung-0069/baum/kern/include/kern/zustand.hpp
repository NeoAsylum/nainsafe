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
//! Startwerte -- wohl aber seit Paket 0027 der **Zugang** fuer sie. Das Verzeichnis
//! fuehrt fuer die Herkuenfte `Entwurf` und `Vorgabe` eine Startwertspalte, aber die
//! Werte selbst kommen zusammen mit Jahrgang, Parametersatz und Manifest, also aus dem
//! Kasten `daten`. Ein frischer `Zustand` ist deshalb durchgehend null, und das ist
//! ausdruecklich kein Startzustand des Spiels. `Startbelegung` weiter unten ist die
//! Stelle, an der `daten` seine Zahlen spaeter einsetzt.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"

namespace kern::schreiber {

/// Der Rundenschreiber aus T18, nur angekuendigt.
///
/// Dieser Kopf holt `kern/schreiber.hpp` **nicht** herein, und das ist keine
/// Bequemlichkeit: Der Schreiber baut auf dem Zustand auf, nicht umgekehrt, und ein
/// gegenseitiges Einbinden waere die erste Abhaengigkeit im Kreis in einem Kasten, der
/// nach T2 sonst gar keine hat. Fuer eine `friend`-Nennung genuegt der Name.
class Schreiber;

}  // namespace kern::schreiber

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
/// Alle Vorgaben nennen dieselbe Folge, und die Aufzaehlung unten folgt ihr:
/// T15 ("Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil",
/// `technik.md:477`), in `daten/adressen.md` die fuenf Bezeichner `fonds.kasse`,
/// `fonds.hebelstand`, `fonds.sichtbarkeit`, `fonds.anlegerbestand` und
/// `fonds.marktanteil` in genau dieser Folge, und `spiel.md:212-213`.
///
/// **Warum hier Bezeichner stehen und kein Zeilenbereich.** Bis zum 2026-09-04 stand
/// hier einer, und der Belegstellenriegel aus Paket 0059 hat ihn tot gefunden: Er
/// nannte fuenf Zeilen, in denen inzwischen Handelszeilen stehen (`handel.CN.RW.1`
/// bis `handel.DE.CN.1`), nicht die fuenf Fondsaggregate -- von Hand nachgeschlagen
/// und bestaetigt in Paket 0070. Ein Bezeichner wandert nicht: Wer die Adresstabelle
/// umsortiert, nimmt ihn mit. Nachgezogen wird hier deshalb nie wieder; sechs Pakete
/// haben das getan, und bei 0050 war die Korrektur falsch, bevor sie jemand ausfuehren
/// konnte.
///
/// Ein Widerspruch zwischen den Vorgaben besteht hier **nicht** -- eine fruehere
/// Fassung dieses Kommentars behauptete einen und widerlegte sich in ihrem eigenen
/// Zitat, das `Sichtbarkeit` bereits vor `Anlegerbestand` fuehrte (Befund 1 der
/// Pruefung zu Paket 0008). Der Hinweis bleibt stehen, damit die Nachrecherche
/// kein zweites Mal gefuehrt wird.
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

/// Der Startwertzugang, hier nur angekuendigt -- er steht gleich unter dem Zustand.
class Startbelegung;

/// Der ganze Weltzustand als Wert fester Groesse (T15).
///
/// Kein wachsender Behaelter, kein Text, keine streuende Zuordnung, keine eigene
/// Speicherverwaltung. Kopieren ist damit ein Speicherumzug von 2,5 kB und keine
/// Zuteilung -- die Voraussetzung dafuer, dass der Pruefstand Millionen Nachspiele
/// aus Zwischenstaenden startet.
///
/// **Zum Schreibzugriff (T18): von aussen ist dieser Typ nur lesbar.** Die 310
/// Groessen und der rohe Schreibzugriff darauf liegen im privaten Teil. Geschrieben
/// wird ein Zustand auf genau zwei Wegen, und beide stehen unten als `friend`:
///
///   1. `schreiber::Schreiber::setze` -- der Weg **innerhalb** einer Runde. Er haengt
///      an jeden Schreibzugriff einen Ursachensatz, fuehrt das Bitfeld ueber alle 310
///      Adressen und prueft am Rundenende gegen die Sollmaske aus T38.
///   2. `Startbelegung` -- der Weg **vor** der ersten Runde. Warum das kein zweiter
///      Schreibweg im Sinne von T18 ist, steht in einem Satz an der Klasse selbst.
///
/// Eine dritte Stelle gibt es nicht, und das ist keine Verabredung, sondern eine
/// Eigenschaft des Codes: Wer eine vierte Uebersetzungseinheit schreibt, die diesen
/// Kopf einbindet und einen Wert in ein Feld legen will, bekommt einen
/// Uebersetzungsfehler. Vorher stand hier ein `struct` mit oeffentlichem Feld, und die
/// beiden Zusagen des Schreibers -- "genau einmal je Runde" und "acht Kanaele, nicht
/// neun" -- galten nur fuer den, der sich daran hielt.
///
/// C++ kennt keine Sichtbarkeit "innerhalb des Kastens"; `friend` ueber zwei
/// namentlich genannte Klassen ist die naechste Entsprechung. Gewaehlt ist sie und
/// nicht ein Zugriffsschluessel, weil ein Schluessel dieselbe Wirkung mit einem
/// zusaetzlichen Typ und einem zusaetzlichen Argument je Aufruf erkauft -- und die
/// Liste der Berechtigten dann nicht mehr am Zustand steht, sondern am Schluessel.
class Zustand {
public:
    /// Lesen mit Indexpruefung. Ein Index ausserhalb `0 ... 309` bricht ab.
    [[nodiscard]] constexpr i64 lies(Index index) const
    {
        if (index >= FELDER) {
            festkomma::abbruch("kern::zustand::lies -- Index ausserhalb der 310 Felder");
        }
        return feld[index];
    }

    /// Feldweiser Vergleich -- die Grundlage der Diff-Ebene und des Rueckvergleichs:
    /// Zwei Zustaende sind gleich, wenn alle 310 Zahlen gleich sind.
    constexpr bool operator==(const Zustand&) const = default;

private:
    /// Die 310 Groessen in der Reihenfolge aus `daten/adressen.md`.
    std::array<i64, FELDER> feld{};

    /// Der rohe Schreibzugriff mit Indexpruefung -- die eine Stelle im ganzen
    /// Programm, an der ein Feld des Zustands seinen Wert bekommt.
    ///
    /// **Er heisst nicht mehr `schreibe`, und der Name ist die halbe Massnahme.** Die
    /// Sichtbarkeit allein schuetzt den naechsten Bauagenten nicht davor, den alten
    /// Aufruf hinzuschreiben und erst am Uebersetzer zu merken, dass es ihn nicht mehr
    /// gibt; mit dem Namenswechsel ist der alte Aufruf zusaetzlich **suchbar** tot.
    /// Damit wird aus T18 eine Regel derselben Machart wie die Gleitkommasperre aus
    /// T4: Ein Mustervergleich ueber `kern/` findet weder den alten Schreibzugriff noch
    /// einen indizierten Feldzugriff -- nirgends, auch nicht in dieser Datei.
    constexpr void lege_ab(Index index, i64 wert)
    {
        if (index >= FELDER) {
            festkomma::abbruch("kern::zustand::lege_ab -- Index ausserhalb der 310 Felder");
        }
        feld[index] = wert;
    }

    friend class kern::schreiber::Schreiber;
    friend class Startbelegung;
};

/// Die Abnahmebedingung des Arbeitspakets, mechanisch: Die Feldzahl wird aus
/// `sizeof(Zustand)` zurueckgerechnet und muss 310 ergeben, die Groesse selbst
/// 2.480 Byte. Stimmt eine der beiden Zahlen nicht, ist der Bau rot -- und nicht eine
/// Zeile in einem Bericht, die jemand liest oder auch nicht.
static_assert(sizeof(Zustand) == 2480, "T15: der Zustand ist 2.480 Byte gross");
static_assert(sizeof(Zustand) / sizeof(i64) == FELDER, "T15: 310 Felder");
static_assert(std::is_trivially_copyable_v<Zustand>,
              "T15: Kopieren ist ein Speicherumzug, keine Zuteilung");

// Die drei Zahlen oben haengen daran, dass der private Teil nichts enthaelt ausser den
// 310 Groessen: kein Merker, kein Zeiger, kein Bit "Partie laeuft schon". Genau
// deshalb liest der Startwertzugang unten seine Schranke aus dem Zustand selbst.
static_assert(sizeof(Zustand) == FELDER * sizeof(i64),
              "T15: der Zustand traegt die 310 Groessen und sonst nichts");

// ---------------------------------------------------------------------------
// Der Startwertzugang -- der zweite benannte Weg, und warum er keiner ist
// ---------------------------------------------------------------------------

/// Legt die **Startwerte** in einen Zustand, bevor die erste Runde laeuft.
///
/// Gebraucht wird er, weil die 310 Groessen irgendwo herkommen muessen: Der Kasten
/// `daten` setzt Jahrgangskennung, Parameterpruefsumme und die Startwertspalte aus
/// `daten/adressen.md` ein, und die Proben dieses Kastens bauen sich Ausgangslagen,
/// gegen die sie rechnen. Ohne ihn bliebe ein frischer Zustand fuer immer durchgehend
/// null -- und das ist ausdruecklich kein Startzustand des Spiels.
///
/// **Warum er kein zweiter Schreibweg im Sinne von T18 ist, in einem Satz:** T18
/// regelt, was *in einer Runde* geschieht -- ein Schreibzugriff je Adresse, ein
/// Ursachensatz je Schreibzugriff, eine Sollmaske je Modus --, und vor der ersten
/// Runde gibt es weder Runde noch Ursache noch Maske, weshalb dieser Zugang genau dort
/// und nur dort arbeitet.
///
/// **Die Grenze ist mechanisch und nicht verabredet.** Der Zugang laesst sich nur an
/// einen Zustand binden, der `partie.runde == 0` traegt -- den Wert, den
/// `daten/adressen.md` fuer dieses Feld als Startwert fuehrt (Nr. 307). Traegt das Feld
/// eine andere Zahl, ist ein Startwertzugang darauf ein harter Fehler mit
/// ausgeschriebener Meldung. Der Riegel liegt damit **im Zustand selbst** und nicht in
/// einem Merker daneben: Ein Zustand ist 2.480 Byte, und ein 311. Feld haette T15
/// gerissen.
///
/// **Was der Riegel voraussetzt -- und dass der Kern es tut.** Er greift genau dann
/// gegen eine gelaufene Runde, wenn diese `partie.runde` auf ihre eigene Nummer
/// **setzt**. Der Kern tut das, und die Herleitung laeuft ueber drei Stellen, die sich
/// einzeln nachlesen lassen: In `kern/src/schritt.cpp` liest die Rundenfunktion
/// `schritt` die Nummer der Vorrunde vom Platz von `partie.runde`, zaehlt eins dazu und
/// gibt das Ergebnis dem `Schreiber` mit; `schritt_1_ansicht` reicht genau diesen einen
/// Platz **nicht** an `vortrag` weiter, sondern an `setze`, mit `schreiber.runde()` als
/// Wert. In `kern/src/schreiber.cpp` legt `Schreiber::setze` den Wert ueber `lege_ab` in
/// den Zustand. Nach einer vollstaendigen Runde traegt der Platz also eine um genau eins
/// groessere Zahl als davor, und der Riegel unten schlaegt gegen einen Zugang an, an dem
/// sie vorbeigelaufen ist.
///
/// **Nachgeprueft wird das an Schritt 1 und nicht an der Sollmaske**, und dieser Satz
/// ist der teuerste dieses Kopfes: **In einer Sollmaske zu stehen heisst geschrieben zu
/// werden, nicht veraendert zu werden.** `partie.runde` stand auch dann in beiden Masken
/// aus T38, als jede Runde denselben Wert zurueckschrieb; die Maske hat sich nicht
/// geaendert, `schritt_1_ansicht` hat es. Wer die Aussage oben pruefen will, sieht
/// deshalb dort nach, ob `setze` steht oder `vortrag`.
///
/// **Warum dieser Absatz so ausfuehrlich ist:** Bis zum 2026-09-04 trug die Runde den
/// Wert der Vorrunde vor, und der Riegel unten schlug gegen sie nie an -- ein
/// vollstaendig gerechneter Weltlauf war von "keine Runde gelaufen" durch keinen
/// Vergleich am Zustand zu unterscheiden. Paket `0071-rundennummer-in-den-zustand` hat
/// das geaendert und ist abgenommen; damit ist die Regel unten eine Eigenschaft des
/// gebauten Systems und keine Zusage auf Widerruf mehr. Der Verweis steht hier als
/// **Grund** der heutigen Fassung, nicht als offene Heilung.
///
/// **Und er wird bei jedem `setze` gefragt, nicht nur beim Binden.** Die Regel in einem
/// Satz: *Ein Zugang schreibt, solange `partie.runde` genau die Zahl traegt, die er
/// dort selbst hinterlassen hat* -- beim Binden ist das die geforderte Null, danach die
/// Zahl, die er zuletzt auf den Platz von `partie.runde` gelegt hat. Steht dort etwas
/// anderes, hat jemand anders geschrieben, und das ist genau der Fall "an diesem Zugang
/// ist eine Runde vorbeigelaufen".
///
/// **Warum die Regel nicht schlicht `partie.runde == 0` lautet.** Unter den 310
/// Groessen ist `partie.runde` selbst, und eine Startbelegung setzt sie mit. Eine
/// Pruefung, die stumpf die Null verlangt, liesse dieselbe Belegung je nach Reihenfolge
/// ihrer Aufrufe mal zu und braeche mal ab -- die Belegung zoege sich beim eigenen
/// Schreibzugriff auf diesen Platz die Tuer vor der Nase zu. Mit der Regel oben traegt
/// sie weiter, und nur ein **fremder** Schreibzugriff schliesst.
///
/// **Wogegen der Riegel nichts ausrichtet, damit es niemand suchen muss:** Er
/// vergleicht eine Zahl und keine Herkunft. Ein fremder Schreibzugriff, der auf
/// `partie.runde` genau die Zahl zuruecklaesst, die schon dort stand, bleibt ihm
/// verborgen. Die Runde des Kerns ist keiner davon -- sie erhoeht die Zahl um eins
/// (Herleitung oben) --, aber das ist eine Eigenschaft von `schritt_1_ansicht` und
/// keine des Riegels. Wer dort spaeter wieder einen Vortrag hinschreibt, macht den
/// Riegel gegen die Runde stumm, ohne eine Zeile dieser Datei anzufassen. Genau deshalb
/// steht die Herleitung oben ausgeschrieben statt in einem Nebensatz.
///
/// **Dieser Absatz war binnen zweier Tage in beide Richtungen falsch**, und das ist die
/// Lehre, die ihn traegt: Erst erklaerte er den Fall ausdruecklich fuer ausgeschlossen,
/// dann -- nach dem Pruefbefund vom 2026-09-04, der ihn mit einer ausgefuehrten Runde
/// statt mit einer von Hand gesetzten Rundennummer widerlegte -- fuer offen, und
/// inzwischen ist er geschlossen. **Ein Kommentar, der einen Randfall fuer erledigt oder
/// fuer offen erklaert, ist teurer als gar keiner, wenn er sich irrt:** Wer ihn liest,
/// hat die Frage gestellt, eine Antwort bekommen und hoert auf zu suchen. Wer diese
/// Datei aendert, ohne den Kern zu lesen, schreibt hier die dritte falsche Fassung.
///
/// **Warum das mehr ist als Ordnungsliebe.** Der Schreiber nimmt den Vorrundenzustand
/// unveraenderlich entgegen und rechnet auf zwei eigenen Abschriften; das Ergebnis holt
/// der Aufrufer aus `rundenende()` zurueck. Eine Rundenschleife bindet den
/// Startwertzugang also vor der Schleife und schreibt jede Runde in denselben Zustand
/// zurueck -- danach stuende der Zugang immer noch da. Seine naechste Setzung waere
/// eine Aenderung ohne Ursachensatz, ohne Kettenglied und ohne Maskenpruefung, und die
/// Diff-Ebene aus T20 zeigte sie als Aenderung ohne Ursache. Genau die **soll** die
/// Regel oben verhindern, und genau die verhindert sie: Die Runde erhoeht `partie.runde`
/// um eins, die Merkzahl des Zugangs stimmt danach nicht mehr, und seine naechste
/// Setzung bricht ab -- statt still zu landen.
class Startbelegung {
public:
    /// Bindet den Zugang an einen Zustand vor seiner ersten Runde.
    ///
    /// **Harter Fehler, wenn `partie.runde` nicht null ist** -- siehe oben. Nach einer
    /// gerechneten Runde ist das der Fall: Sie traegt dort ihre eigene Nummer ein, also
    /// mindestens die Eins, und ein Zugang bindet auf diesen Zustand nicht mehr. Die
    /// Bedingung bleibt trotzdem die schwaechere von beiden -- sie fragt nach der Null
    /// und nicht danach, ob gerechnet wurde; ein Zustand, auf dem nie eine Runde lief,
    /// dessen Startbelegung aber eine andere Nummer gesetzt hat, wird ebenso abgewiesen.
    /// `explicit`, damit aus einem Zustand nirgends beilaeufig ein Schreibrecht wird:
    /// Wer schreibt, nennt diesen Typ und damit seine Absicht.
    explicit Startbelegung(Zustand& ziel);

    /// **Kein Zugang auf einen Zustand ohne Namen.** Ein Zugang zeigt auf einen
    /// Zustand, den er nicht besitzt; an einen Zwischenwert gebunden waere er von der
    /// naechsten Anweisung an ein Zeiger ins Leere. Diese eine Form der zu kurzen
    /// Lebensdauer schliesst der Uebersetzer hier aus. Der andere Fall -- ein benannter
    /// Zustand, der vor seinem Zugang endet -- ist in C++ nicht mechanisch
    /// auszuschliessen; er steht hier, damit ihn niemand fuer ausgeschlossen haelt, und
    /// die geloeschten Zeilen darunter halten den Zugang wenigstens in dem Block, in
    /// dem er steht.
    Startbelegung(Zustand&&) = delete;

    /// **Eine Kopie nimmt das Schreibrecht nicht mit, weil keine entstehen kann.**
    /// Zwei Zugaenge auf denselben Zustand traegen zwei verschiedene Merkzahlen; nach
    /// der Regel oben duerfte dann der eine schreiben, waehrend der andere abbricht --
    /// und welcher, haenge an der Reihenfolge der Aufrufe. Eine Berechtigung, die davon
    /// abhaengt, ist keine. Ohne Kopie und ohne Verschiebung laesst sich ein Zugang
    /// ausserdem nicht in einem Behaelter ablegen, nicht zurueckgeben und nicht
    /// wegspeichern.
    Startbelegung(const Startbelegung&)            = delete;
    Startbelegung& operator=(const Startbelegung&) = delete;

    /// Setzt den Startwert einer Adresse. Zwei harte Fehler, beide ohne Ersatzwert:
    /// ein Index ausserhalb `0 ... 309`, und ein Zugang, an dem ein fremder
    /// Schreibzugriff die Zahl auf dem Platz von `partie.runde` geaendert hat -- der
    /// Fall, den die Meldung "an diesem Zugang ist eine Runde vorbeigelaufen" nennt und
    /// den eine Runde des Kerns ausloest (Herleitung oben). Sie nennt beide
    /// Rundennummern ausgeschrieben -- die im Zustand und die des Zugangs --, denn der
    /// Ort allein sagt nicht, ob der Zugang zu alt ist oder der Zustand fremd
    /// beschrieben wurde.
    ///
    /// Es entsteht **kein** Ursachensatz, und das Bitfeld einer Runde sieht diesen Wert
    /// nie. Beides ist gewollt: Ein Startwert hat keine Ursache im Modell -- er ist der
    /// Anfang, auf den sich jede spaetere Ursache bezieht. Zweimal dieselbe Adresse zu
    /// setzen ist hier ebenfalls erlaubt; die Regel "genau einmal" aus T18 gilt je
    /// Runde, und eine Runde ist das hier nicht.
    void setze(Index adresse, i64 wert);

private:
    Zustand* ziel_;

    /// Die Zahl, die dieser Zugang zuletzt auf dem Platz von `partie.runde`
    /// hinterlassen hat. Beim Binden ist es die Null, die der Konstruktor dort
    /// vorgefunden hat -- die Merkzahl stimmt also von der ersten Anweisung an und
    /// nicht erst nach dem ersten Schreibzugriff.
    i64 hinterlassene_runde_ = 0;
};

/// Ob `partie.runde` dieses Zustands null ist -- die Frage, die `Startbelegung` beim
/// Binden stellt.
///
/// **Der Name trifft die Funktion in der einen Richtung und nicht in der anderen, und
/// das gehoert hierher.** Nach einer vollstaendig gerechneten Runde antwortet sie
/// `false` -- die Runde setzt dieses Feld auf ihre eigene Nummer (Herleitung oben), und
/// so weit deckt der Name. Umgekehrt deckt er nicht: `false` heisst nicht "es wurde
/// gerechnet", sondern nur "hier steht nicht null", und diese Zahl kann auch eine
/// Startbelegung hinterlassen haben. Sie ist damit genau die Auskunft, die der
/// Konstruktor von `Startbelegung` verlangt -- nicht mehr.
///
/// Sie steht hier, damit ein Aufrufer sie stellen kann, statt sie am Abbruch zu
/// erfahren. Erlaubt ist die Frage; nur die Antwort "dann schreibe ich eben trotzdem"
/// ist es nicht -- es gibt von aussen keinen Weg, sie zu geben.
[[nodiscard]] bool vor_der_ersten_runde(const Zustand& zustand);

// ---------------------------------------------------------------------------
// T17 -- die Adressabbildung, beide Richtungen
// ---------------------------------------------------------------------------

/// Der Platz, den es nicht gibt -- der Fehlerwert jeder Adresssuche.
///
/// Er liegt ausserhalb `0 ... 309` und ist damit **kein** Feld des Zustands. Das ist
/// der ganze Zweck: `lies`, `schreibe` und `index_zu_adresse` pruefen `index >=
/// FELDER` ohnehin, also wird aus einer nicht ausgewerteten Fehlanzeige ein Abbruch
/// statt eines Zugriffs auf ein fremdes Feld.
inline constexpr Index KEIN_PLATZ = FELDER;

static_assert(KEIN_PLATZ >= FELDER,
              "der Fehlerwert darf kein gueltiger Platz sein, sonst schreibt er still");

/// Das Ergebnis einer Adresssuche.
///
/// Ein Ergebnistyp mit einem Ja-Nein-Feld statt eines Behaelters aus der
/// Standardbibliothek, der "vielleicht ein Wert" bedeutet: T15 schliesst solche
/// Behaelter im Zustand aus, und ein zweiter Weg, dasselbe zu sagen, waere genau die
/// Sorte Ausnahme, deren Begruendung spaeter niemand mehr findet.
///
/// **Warum die Vorbelegung `KEIN_PLATZ` ist und nicht `0`.** Der Aufrufer *soll*
/// `gefunden` auswerten, aber ein Ergebnistyp, der beim Vergessen still das falsche
/// Feld trifft, verlaesst sich darauf. Platz 0 ist
/// `land.US.sektor.1.wertschoepfung`, eine getragene Groesse des Modells: Eine
/// Adresse mit Tippfehler haette ihren Wert ueberschrieben, ohne dass irgendetwas
/// abbricht. Das ist derselbe stille Ersatzwert, gegen den `festkomma.hpp` an seiner
/// Abbruchstelle ausdruecklich entschieden hat -- nur als Index statt als Zahl, und
/// eine falsche Zahl wandert in den Regressionsbestand und wird dort zum Sollwert.
/// Der Fehlerwert liegt deshalb ausserhalb der 310 (Befund 3 der Pruefung zu Paket
/// 0008). Der gueltige Platz 0 ist davon unberuehrt: Er kommt nur mit
/// `gefunden == true` zurueck.
struct Adressfund {
    bool gefunden = false;
    Index index = KEIN_PLATZ;
};

static_assert(!Adressfund{}.gefunden && Adressfund{}.index == KEIN_PLATZ,
              "die Fehlanzeige zeigt auf keinen Platz");

/// Adresse nach T17 -> Platz im Zustand.
///
/// `adresse` ist ein nullbyte-begrenzter Text. Steht sie nicht in
/// `daten/adressen.md`, kommt `{false, KEIN_PLATZ}` zurueck -- eine unbekannte
/// Adresse ist eine Frage und kein Fehler: Sie kommt aus Protokoll, Testvorlage oder
/// Oberflaeche und darf dort beantwortet werden. Wer die Antwort trotzdem nicht
/// liest und `index` weiterreicht, bekommt einen Abbruch und keinen falschen Wert.
/// Ein Nullzeiger gilt als unbekannte Adresse.
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
