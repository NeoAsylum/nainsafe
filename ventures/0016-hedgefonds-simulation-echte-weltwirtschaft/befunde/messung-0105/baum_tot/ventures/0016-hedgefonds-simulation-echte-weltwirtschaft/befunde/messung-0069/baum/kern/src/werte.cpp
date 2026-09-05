//! `kern::werte` -- die Rechnung hinter den siebzehn Groessen aus T48.
//!
//! Der Kopf `kern/werte.hpp` sagt, **was** dieses Modul anbietet und warum die Menge
//! abgeschlossen ist. Hier steht, **wie** gerechnet wird, und drei Dinge, die nur hier
//! stehen koennen:
//!
//!   1. **Die drei Skalenuebergaenge aus T50**, privat und ohne Deklaration im Kopf.
//!   2. **Die beiden benannten Tabellen** -- die Steckplatzarten aus T16 und die
//!      Gegenueber je Gebiet aus T9. T48 verlangt fuer die zweite ausdruecklich eine
//!      Tabelle statt einer Rechnung auf Indizes.
//!   3. **Die geprueften Rechenarten aus T7 Massnahme 4**, soweit sie hier entstehen:
//!      Strichrechnung ueber die Ueberlaufbausteine des Uebersetzers (4.2) und jede
//!      blanke Multiplikation ueber `festkomma::mal` (4.3).
//!
//! ## Warum hier ueberhaupt Strichrechnung steht
//!
//! T7 Massnahme 4.2 verlangt fuer Additionen und Subtraktionen auf `i64` die
//! Ueberlaufbausteine des Uebersetzers. Der Kern hatte bis zu diesem Paket keine
//! Strichrechnung auf Groessen nach T5 -- `fondsvermoegen` ist die erste, und mit ihr
//! `bip`, `handelsvolumen`, `fondsanteil`, `korbbestand` und `marktkorb`. `plus` und
//! `minus` stehen deshalb hier und nicht in `festkomma.hpp`: Jene Datei gehoert nicht
//! zur Dateiliste dieses Pakets, und ein Bauagent, der ausserhalb seines Pakets
//! schreibt, kollidiert mit dem, der gerade daran arbeitet. Dass sie dorthin gehoeren,
//! sobald ein zweites Modul sie braucht, steht als eigener Vorschlag unter
//! `aufgaben/` -- gesucht wird er ueber den Bezeichner `plus` neben `festkomma`, nicht
//! ueber eine Nummer.
//!
//! ## Die Zahlenproben stehen als `static_assert`
//!
//! Dieselbe Bauart wie in `src/festkomma.cpp`: Was zur Uebersetzungszeit auswertbar
//! ist, wird dort geprueft. Ein Rundungsfehler ist damit kein roter Test, sondern eine
//! Datei, die sich nicht uebersetzen laesst. Die drei privaten Skalenuebergaenge haben
//! heute keinen anderen Aufrufer als diese Proben -- ihre Aufruforte nach T50 (Aktion 3
//! in Schritt 2, Gegenkraft 5 in Schritt 5) sind noch nicht gebaut --, und eine private
//! Funktion ohne jeden Aufrufer waere unter dem Warnsatz ein Bauabbruch.

#include "kern/werte.hpp"

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::werte {

using festkomma::mal;
using festkomma::mal_geteilt;

using zustand::Aggregat;
using zustand::BeteiligungsFeld;
using zustand::FondsGroesse;
using zustand::Gebiet;
using zustand::i64;
using zustand::Sektor;
using zustand::SektorGroesse;
using zustand::Steckplatz;
using zustand::Zustand;

using zustand::GEBIETE;
using zustand::LAENDER;
using zustand::SEKTOREN;
using zustand::SEKTOREN_HANDELBAR;
using zustand::STECKPLAETZE;

namespace {

// ---------------------------------------------------------------------------
// T7 Massnahme 4.2 -- Strichrechnung, die nicht still umbricht
// ---------------------------------------------------------------------------

/// `a + b` auf `i64`, Ueberlauf ist ein Abbruch (T7 Massnahme 4.2).
///
/// `__builtin_add_overflow` rechnet in unendlicher Genauigkeit und meldet, ob das
/// Ergebnis in den Zieltyp passt. `-fwrapv` beruehrt den Baustein nicht: Er loest kein
/// undefiniertes Verhalten aus, sondern fragt eines ab. Genau deshalb ist er hier
/// noetig -- Massnahme 1 macht den Umbruch **definiert** und damit still.
constexpr i64 plus(i64 a, i64 b)
{
    i64 ergebnis = 0;
    if (__builtin_add_overflow(a, b, &ergebnis)) {
        festkomma::abbruch("kern::werte::plus -- Summe ausserhalb von i64 (T7)");
    }
    return ergebnis;
}

/// `a - b` auf `i64`, Ueberlauf ist ein Abbruch (T7 Massnahme 4.2).
constexpr i64 minus(i64 a, i64 b)
{
    i64 ergebnis = 0;
    if (__builtin_sub_overflow(a, b, &ergebnis)) {
        festkomma::abbruch("kern::werte::minus -- Differenz ausserhalb von i64 (T7)");
    }
    return ergebnis;
}

/// Der Betrag einer `i64`.
///
/// Der kleinste `i64` hat keinen darstellbaren Betrag; mit `-fwrapv` ergaebe `-x`
/// wieder denselben negativen Wert, und aus einem Betrag wuerde still eine negative
/// Zahl. `fondsanteil` und `korbbestand` reichen ihr Ergebnis unmittelbar als Anteil
/// in Zehntausendsteln weiter -- ein negativer Anteil dort waere ein Vorzeichenfehler,
/// den keine Pruefung bemerkt.
constexpr i64 betrag(i64 zahl)
{
    if (zahl == festkomma::I64_MIN) {
        festkomma::abbruch("kern::werte::betrag -- der Betrag von I64_MIN passt nicht in i64 (T7)");
    }
    return zahl < 0 ? -zahl : zahl;
}

static_assert(plus(3, 4) == 7 && minus(3, 4) == -1);
static_assert(betrag(-7) == 7 && betrag(7) == 7 && betrag(0) == 0);

// ---------------------------------------------------------------------------
// T50 -- die drei Skalenuebergaenge, privat
// ---------------------------------------------------------------------------
//
// T50 zaehlt sie abschliessend auf und bindet jeden an genau einen Aufrufort. Sie
// stehen hier und nicht im Kopf, weil ein Uebergang, den jeder aufrufen kann, nach
// zwei Paketen an drei Stellen steht -- und dann ist "je Bewertung einmal" wieder ein
// Satz statt einer Eigenschaft. Der Nachweis ist ein Mustervergleich ueber `kern/`:
// Ihre Namen kommen nur in dieser Datei vor.

/// **T50 Uebergang 1** -- volkswirtschaftlich (Klasse 2) nach Fondsgeld (Klasse 1):
/// ein Tausend USD sind 100.000 US-Cent (T5).
///
/// **Zweite der beiden Wertebereichsschranken aus T47:** Das ist die einzige Stelle,
/// an der ein `i64` ueberlaufen kann -- der Faktor 100.000 verlaesst den Bereich ab
/// einem Betrag von rund 9,2e13 Tausend USD. Die Multiplikation laeuft deshalb ueber
/// `festkomma::mal` (T7 Massnahme 4.3): Produkt als 128-Bit-Zwischenwert, Rueckkehr
/// durch den Waechter, Ueberlauf ist ein Abbruch und kein Umbruch. Der Jahrgangsbau
/// und der Invariantentest halten den Marktkorb zusaetzlich unter derselben Schranke;
/// beides zusammen macht den Ueberlauf nicht bloss unwahrscheinlich, sondern
/// ausgeschlossen und geprueft.
constexpr i64 tsd_in_cent(i64 tausend_usd) { return mal(tausend_usd, 100'000); }

/// **T50 Uebergang 2** -- Fondsgeld (Klasse 1) nach Lobbydruck (Klasse 9). Einziger
/// Aufrufort nach T50: die dritte Aktion in Schritt 2.
///
/// `rabatt` steht in Zehntausendsteln und ist 10.000 ohne und `beteiligungsrabatt` mit
/// Beteiligung im betroffenen Sektor. **Der Rabatt sitzt am Preis eines Lobbypunkts,
/// nicht an der Punktzahl** -- sonst waere der Einfluss, nach `spiel.md` der Anteil des
/// Fonds am gesamten Lobbydruck, ueber Laender hinweg nicht mehr vergleichbar. Ein
/// kleinerer Rabattwert heisst mehr Punkte fuer dasselbe Geld.
///
/// Der Nenner ist ein Produkt zweier Groessen und laeuft deshalb ueber
/// `festkomma::mal` (T7 Massnahme 4.3). Waere er null -- `lobbykosten` ist nach T50
/// mindestens 1, `rabatt` mindestens 1 --, braeche `mal_geteilt` nach T6 ab.
///
/// Der Konstantensatz steht vorn und nicht in der Signatur aus T50, weil der Kern
/// keine Datei liest (T2): `lobbykosten` kommt von aussen herein wie jeder andere
/// Kalibrierwert.
constexpr i64 lobbypunkte_aus_geld(const Konstanten& konst, i64 cent, i64 rabatt)
{
    return mal_geteilt(cent, 10'000, mal(konst.lobbykosten, rabatt));
}

/// **T50 Uebergang 3** -- volkswirtschaftlich (Klasse 2) nach Lobbydruck (Klasse 9).
/// Einziger Aufrufort nach T50: die fuenfte Gegenkraft in Schritt 5.
///
/// `gegenlobby_satz` sind Lobbypunkte je 10.000 Tausend USD Schaden. *Wie hoch* der
/// Schaden eines Sektors ist, bleibt Sache von `spiel.md` und des Bauagenten, der jene
/// Gegenkraft baut; T50 legt allein fest, in welcher Einheit er ankommt.
constexpr i64 lobbypunkte_aus_schaden(const Konstanten& konst, i64 tsd)
{
    return mal_geteilt(tsd, konst.gegenlobby_satz, 10'000);
}

// --- Die Zahlenproben der drei Uebergaenge, beim Uebersetzen ---------------
//
// Sie sind zugleich der einzige Aufrufer, den die beiden Lobbyumrechnungen heute
// haben: Ihre Aufruforte nach T50 sind nicht gebaut. Ohne sie waere eine private
// Funktion ohne Aufrufer ein Bauabbruch unter dem Warnsatz -- und ein Uebergang, der
// erst mit seinem ersten Aufrufer entstuende, waere genau der Fall, den T50
// ausschliesst.

/// Der innere Wert der Zahlenprobe aus T47, in Tausend USD.
constexpr i64 PROBE_INNEN_TSD = 42'000'000;

// Die Probe rechnet die Skalengrenze nach, nicht die Multiplikation: 42 Mio Tausend
// USD sind 4,2 Bio US-Cent.
static_assert(tsd_in_cent(PROBE_INNEN_TSD) == 4'200'000'000'000,
              "T47/T50: der aeusserste Aufruf traegt den Faktor 100.000");
static_assert(tsd_in_cent(-PROBE_INNEN_TSD) == -4'200'000'000'000,
              "und zeichengleich zurueck -- der Fonds darf short sein");

/// Ein Satz Konstanten allein fuer die drei Proben. Die Zahlen sind gewaehlt, nicht
/// gemessen: `parameter.toml` traegt fuer diese Schluessel durchweg einen als solchen
/// gekennzeichneten Platzhalter, und eine Probe, die ihn abschriebe, wuerde bei der
/// ersten Kalibrierung rot, ohne dass etwas kaputt waere.
constexpr Konstanten PROBE_KONSTANTEN{
    /* stufenweite       */ 1,
    /* ausstiegsabschlag */ 0,
    /* aufschlag         */ 51,
    /* lobbykosten       */ 100,
    /* gegenlobby_satz   */ 3,
    /* leitzins_start    */ {{0, 0, 0, 0}},
};

// 1.000.000 Cent zu 100 Cent je Punkt sind 10.000 Punkte -- und mit halbiertem Preis
// (`rabatt` 5.000 statt 10.000) doppelt so viele. Das ist der Bruchteil, den
// `spiel.md` der dritten Aktion mit Beteiligung zusagt, als Zahl.
static_assert(lobbypunkte_aus_geld(PROBE_KONSTANTEN, 1'000'000, 10'000) == 10'000,
              "T50 Uebergang 2: ohne Rabatt kostet ein Punkt volle lobbykosten");
static_assert(lobbypunkte_aus_geld(PROBE_KONSTANTEN, 1'000'000, 5'000) == 20'000,
              "T50 Uebergang 2: halber Preis, doppelte Punktzahl");

// 50.000 Tausend USD Schaden mal 3 Punkten je 10.000 Tausend USD sind 15 Punkte.
static_assert(lobbypunkte_aus_schaden(PROBE_KONSTANTEN, 50'000) == 15,
              "T50 Uebergang 3: der Satz zaehlt je 10.000 Tausend USD");

// ---------------------------------------------------------------------------
// Die erste benannte Tabelle -- die zwanzig Steckplaetze und ihre Art (T16)
// ---------------------------------------------------------------------------
//
// `markt(p)` ist nach T48 eine Fallunterscheidung ueber die drei Steckplatzarten. Der
// Zustand kennt den Weg **hin** -- aus Land und Sektor wird ein Steckplatz --, nicht
// den Weg zurueck. Er steht hier als Tabelle und nicht als Rechnung auf der
// Platznummer, aus demselben Grund, aus dem T48 die Gegenuebertabelle weiter unten
// verlangt: Wer einen Steckplatz einschoebe, verschoebe bei einer Rechnung
// stillschweigend jede Art dahinter; in der Tabelle sieht man es in der Zeile.

enum class Steckplatzart : std::uint8_t {
    Korb = 0,
    Waehrung = 1,
    Anleihe = 2,
};

/// Der Sektor eines Steckplatzes, der keinen hat.
///
/// Die Sektoren sind nach der Adressform ab eins nummeriert; die Null ist deshalb
/// frei, und sie liegt **ausserhalb** des gueltigen Bereichs. Wer diesen Wert
/// versehentlich weiterreicht, bricht in `sektor_index` ab, statt still den ersten
/// Sektor zu treffen -- derselbe Gedanke wie beim Fehlerwert der Adresssuche.
constexpr Sektor KEIN_SEKTOR = static_cast<Sektor>(0);

struct Platzbeschreibung {
    Steckplatzart art;
    Gebiet        land;
    /// Nur bei der Art Korb bedeutsam; sonst `KEIN_SEKTOR`.
    Sektor        sektor;
};

constexpr std::array<Platzbeschreibung, STECKPLAETZE> PLAETZE{{
    {Steckplatzart::Korb, Gebiet::US, Sektor::Landwirtschaft},
    {Steckplatzart::Korb, Gebiet::US, Sektor::Industrie},
    {Steckplatzart::Korb, Gebiet::US, Sektor::Dienstleistungen},
    {Steckplatzart::Korb, Gebiet::CN, Sektor::Landwirtschaft},
    {Steckplatzart::Korb, Gebiet::CN, Sektor::Industrie},
    {Steckplatzart::Korb, Gebiet::CN, Sektor::Dienstleistungen},
    {Steckplatzart::Korb, Gebiet::DE, Sektor::Landwirtschaft},
    {Steckplatzart::Korb, Gebiet::DE, Sektor::Industrie},
    {Steckplatzart::Korb, Gebiet::DE, Sektor::Dienstleistungen},
    {Steckplatzart::Korb, Gebiet::BR, Sektor::Landwirtschaft},
    {Steckplatzart::Korb, Gebiet::BR, Sektor::Industrie},
    {Steckplatzart::Korb, Gebiet::BR, Sektor::Dienstleistungen},
    {Steckplatzart::Waehrung, Gebiet::US, KEIN_SEKTOR},
    {Steckplatzart::Waehrung, Gebiet::CN, KEIN_SEKTOR},
    {Steckplatzart::Waehrung, Gebiet::DE, KEIN_SEKTOR},
    {Steckplatzart::Waehrung, Gebiet::BR, KEIN_SEKTOR},
    {Steckplatzart::Anleihe, Gebiet::US, KEIN_SEKTOR},
    {Steckplatzart::Anleihe, Gebiet::CN, KEIN_SEKTOR},
    {Steckplatzart::Anleihe, Gebiet::DE, KEIN_SEKTOR},
    {Steckplatzart::Anleihe, Gebiet::BR, KEIN_SEKTOR},
}};

/// Die zwoelf Korbplaetze sind die ersten der zwanzig. Die Zahl wird hergeleitet und
/// nicht abgeschrieben: Sie ist genau der Platz, an dem die Waehrungen beginnen.
constexpr std::size_t KOERBE = zustand::STECKPLATZ_WAEHRUNG_ERSTER;

/// Der zweite Weg zu derselben Tabelle, und damit ihr Pruefstand.
///
/// Der Zustand rechnet aus Land und Sektor einen Steckplatz; diese Schleife rechnet
/// aus jeder Zeile der Tabelle denselben Steckplatz zurueck und vergleicht ihn mit der
/// Zeilennummer. Stimmt eine Zeile nicht, uebersetzt die Datei nicht. Eine
/// abgeschriebene Tabelle ohne diesen Gegenweg pruefte sich nur selbst.
constexpr bool plaetze_stimmen()
{
    for (std::size_t i = 0; i < STECKPLAETZE; ++i) {
        const Platzbeschreibung& b = PLAETZE[i];
        const Steckplatz erwartet = static_cast<Steckplatz>(i);
        if (i < KOERBE) {
            if (b.art != Steckplatzart::Korb) { return false; }
            if (zustand::steckplatz_sektor(b.land, b.sektor) != erwartet) { return false; }
        } else if (i < zustand::STECKPLATZ_ANLEIHE_ERSTER) {
            if (b.art != Steckplatzart::Waehrung) { return false; }
            if (b.sektor != KEIN_SEKTOR) { return false; }
            if (zustand::steckplatz_waehrung(b.land) != erwartet) { return false; }
        } else {
            if (b.art != Steckplatzart::Anleihe) { return false; }
            if (b.sektor != KEIN_SEKTOR) { return false; }
            if (zustand::steckplatz_anleihe(b.land) != erwartet) { return false; }
        }
    }
    return true;
}

static_assert(plaetze_stimmen(),
              "T16: jede Zeile der Platztabelle rechnet auf ihre eigene Platznummer zurueck");
static_assert(KOERBE == LAENDER * SEKTOREN, "T16: zwoelf Land-mal-Sektor-Plaetze");

// ---------------------------------------------------------------------------
// Die zweite benannte Tabelle -- die vier Gegenueber je Gebiet (T9, T48)
// ---------------------------------------------------------------------------
//
// T48 verlangt sie ausdruecklich: "die Zuordnung des dichten Gegenueber-Index zum
// Gebietsindex steht im Code als benannte Tabelle, nicht als Rechnung auf Indizes".
// `handelsvolumen` braucht die Gegenrichtung -- fuer jedes Gebiet die vier anderen in
// der Reihenfolge aus T9 --, und die ist keine Ableitung aus der eigenen Nummer.

constexpr std::size_t GEGENUEBER_JE_GEBIET = GEBIETE - 1;

constexpr std::array<std::array<Gebiet, GEGENUEBER_JE_GEBIET>, GEBIETE> GEGENUEBER{{
    {{Gebiet::CN, Gebiet::DE, Gebiet::BR, Gebiet::RW}},  // US
    {{Gebiet::US, Gebiet::DE, Gebiet::BR, Gebiet::RW}},  // CN
    {{Gebiet::US, Gebiet::CN, Gebiet::BR, Gebiet::RW}},  // DE
    {{Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::RW}},  // BR
    {{Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::BR}},  // RW
}};

/// Der Pruefstand der Tabelle: Jede Zeile traegt vier Gebiete, keines davon sich
/// selbst, alle streng aufsteigend in der Reihenfolge aus T9. Damit ist jede Zeile
/// genau die Menge der vier anderen -- vier verschiedene aus fuenf, ohne das eigene.
constexpr bool gegenueber_stimmt()
{
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        std::size_t vorheriges = 0;
        for (std::size_t j = 0; j < GEGENUEBER_JE_GEBIET; ++j) {
            const std::size_t n = static_cast<std::size_t>(GEGENUEBER[g][j]);
            if (n >= GEBIETE) { return false; }
            if (n == g) { return false; }
            if (j > 0 && n <= vorheriges) { return false; }
            vorheriges = n;
        }
    }
    return true;
}

static_assert(gegenueber_stimmt(),
              "T9: jede Zeile sind die vier anderen Gebiete, aufsteigend und ohne das eigene");

// ---------------------------------------------------------------------------
// Die beiden Sektorlisten (T9, T15)
// ---------------------------------------------------------------------------

constexpr std::array<Sektor, SEKTOREN> SEKTORLISTE{
    Sektor::Landwirtschaft,
    Sektor::Industrie,
    Sektor::Dienstleistungen,
};

/// Handelszeilen gibt es nur fuer die ersten beiden Sektoren (T15).
constexpr std::array<Sektor, SEKTOREN_HANDELBAR> SEKTORLISTE_HANDELBAR{
    Sektor::Landwirtschaft,
    Sektor::Industrie,
};

constexpr bool sektorlisten_stimmen()
{
    for (std::size_t i = 0; i < SEKTOREN; ++i) {
        if (zustand::sektor_index(SEKTORLISTE[i]) != i) { return false; }
    }
    for (std::size_t i = 0; i < SEKTOREN_HANDELBAR; ++i) {
        if (SEKTORLISTE_HANDELBAR[i] != SEKTORLISTE[i]) { return false; }
        if (!zustand::sektor_handelbar(SEKTORLISTE_HANDELBAR[i])) { return false; }
    }
    return zustand::sektor_handelbar(SEKTORLISTE[SEKTOREN - 1]) == false;
}

static_assert(sektorlisten_stimmen(),
              "T15: drei Sektoren in Adressreihenfolge, davon die ersten zwei handelbar");

// ---------------------------------------------------------------------------
// Innere Fassungen -- ein Rechenweg, zwei Eingaenge
// ---------------------------------------------------------------------------

/// Die Nummer eines spielbaren Landes, mit Bereichspruefung.
///
/// Gebraucht von `anleihekurs`, weil dessen `leitzins_start` vier Eintraege hat und
/// die Restwelt keinen Politikpfad. Ueberall sonst bringen die `stelle_*`-Funktionen
/// des Zustands ihre eigene Pruefung mit.
std::size_t land_nummer(Gebiet land)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        festkomma::abbruch(
            "kern::werte -- diese Groesse gibt es nur bei spielbaren Laendern");
    }
    return nummer;
}

const Platzbeschreibung& platzbeschreibung(Steckplatz platz)
{
    const std::size_t p = static_cast<std::size_t>(platz);
    if (p >= STECKPLAETZE) {
        festkomma::abbruch("kern::werte -- unbekannter Steckplatz");
    }
    return PLAETZE[p];
}

/// Die zwoelf Korbwerte eines Aufrufs von `fondsvermoegen` -- oder die Anzeige, dass
/// noch keiner gerechnet ist.
///
/// **Warum es diesen Typ gibt und nicht zwei Fassungen jeder Formel.** T47 verlangt,
/// dass `korbwert(l, s)` je Aufruf von `fondsvermoegen` **einmal** gerechnet und von
/// Steckplatz und Beteiligung daraus gelesen wird -- nicht um Zeit zu sparen, sondern
/// damit "eine Bewertung, nicht zwei" eine Eigenschaft des Codes ist. Zugleich muessen
/// `markt`, `stufenwert`, `positionswert` und `beteiligung_wert` einzeln aufrufbar
/// bleiben. Beides zusammen geht nur, wenn der Vorrat ein Argument ist: Ein leerer
/// laesst jede Formel ihren einen Korbwert selbst rechnen, ein gefuellter reicht allen
/// dieselbe Zahl. Zwei Fassungen derselben Formel waeren die Sorte Verdopplung, die
/// nach zwei Paketen auseinanderlaeuft.
///
/// Der Platz eines Korbwerts im Feld ist die Nummer seines Steckplatzes -- das duerfen
/// beide Leser annehmen, weil `plaetze_stimmen` es beim Uebersetzen nachrechnet.
struct Korbvorrat {
    bool gefuellt = false;
    std::array<i64, KOERBE> korb{};
};

i64 markt_aus(const Zustand& z, const Konstanten& konst, Steckplatz platz,
              const Korbvorrat& vorrat)
{
    const std::size_t p = static_cast<std::size_t>(platz);
    const Platzbeschreibung& b = platzbeschreibung(platz);
    switch (b.art) {
    case Steckplatzart::Korb:
        return vorrat.gefuellt ? vorrat.korb[p] : korbwert(z, b.land, b.sektor);
    case Steckplatzart::Waehrung:
        return waehrungswert(z, b.land);
    case Steckplatzart::Anleihe:
        return anleihewert(z, konst, b.land);
    }
    festkomma::abbruch("kern::werte::markt -- unbekannte Steckplatzart");
}

i64 stufenwert_aus(const Zustand& z, const Konstanten& konst, Steckplatz platz,
                   const Korbvorrat& vorrat)
{
    // T48 Nr. 6, Zeichen fuer Zeichen: mal_geteilt(markt(p), stufenweite, 10.000).
    // Die 10.000 ist die Anteilsskala aus T5 Klasse 4.
    return mal_geteilt(markt_aus(z, konst, platz, vorrat), konst.stufenweite, 10'000);
}

i64 positionswert_aus(const Zustand& z, const Konstanten& konst, Steckplatz platz,
                      const Korbvorrat& vorrat)
{
    const i64 stufen = z.lies(zustand::stelle_position(platz));

    // T47 woertlich: der Abbruch bei stufen = 0 liegt **vor** markt(p). Das ist keine
    // Beschleunigung, die man auch weglassen koennte -- ein leerer Steckplatz darf an
    // einer Bewertung nicht scheitern, die ihn nichts angeht.
    if (stufen == 0) { return 0; }

    // Die verbindliche Reihenfolge der Rundungen (T47): erst der Stufenwert, dann die
    // Vervielfachung. Die genauere Form mit einem einzigen mal_geteilt braeuchte einen
    // ADR, keinen besseren Grund.
    const i64 je_stufe = stufenwert_aus(z, konst, platz, vorrat);
    return tsd_in_cent(mal(stufen, je_stufe));
}

i64 beteiligung_wert_aus(const Zustand& z, const Konstanten& konst, Gebiet land,
                         Sektor sektor, const Korbvorrat& vorrat)
{
    const std::size_t p = static_cast<std::size_t>(zustand::steckplatz_sektor(land, sektor));
    const i64 korb = vorrat.gefuellt ? vorrat.korb[p] : korbwert(z, land, sektor);
    const i64 anteil = z.lies(zustand::stelle_beteiligung(land, sektor, BeteiligungsFeld::Anteil));

    // T47: innen der Korbanteil in Zehntausendsteln, darum der Abschlag, und erst um
    // den **aeussersten** Aufruf die Skalengrenze.
    const i64 innen = mal_geteilt(korb, anteil, 10'000);
    const i64 nach_abschlag = mal_geteilt(innen, minus(10'000, konst.ausstiegsabschlag), 10'000);
    return tsd_in_cent(nach_abschlag);
}

/// `korbwert` mit getrennten Quellen fuer Menge und Kurs (T33 Punkt 3).
i64 korbwert_zwei(const Zustand& mengen, const Zustand& kurse, Gebiet land, Sektor sektor)
{
    return wert(kurse,
                mengen.lies(zustand::stelle_sektorgroesse(land, sektor, SektorGroesse::Kapitalstock)),
                kurse.lies(zustand::stelle_sektorgroesse(land, sektor, SektorGroesse::Preis)),
                land);
}

/// `anleihewert` mit getrennten Quellen. Die Schuld ist eine Menge und kommt aus
/// `mengen`, der Anleihekurs ein Kurs und kommt aus `kurse` -- ebenso der Wechselkurs,
/// den `wert` selbst nachschlaegt.
i64 anleihewert_zwei(const Zustand& mengen, const Zustand& kurse, const Konstanten& konst,
                     Gebiet land)
{
    return wert(kurse, schuld(mengen, land), anleihekurs(kurse, konst, land), land);
}

}  // namespace

// ---------------------------------------------------------------------------
// Die siebzehn Groessen aus T48
// ---------------------------------------------------------------------------

// --- Nr. 1 ---------------------------------------------------------------
i64 wert(const Zustand& z, i64 menge, i64 kurs, Gebiet gebiet)
{
    const i64 wechselkurs = z.lies(zustand::stelle_aggregat(gebiet, Aggregat::Wechselkurs));

    // Die erste Wertebereichsschranke aus T47. `mal_geteilt` faengt den Nenner null
    // nach T6 von selbst; der **negative** Nenner ist der gefaehrlichere Fall, weil er
    // das Vorzeichen jeder Bewertung drehte, ohne dass irgendetwas abbraeche. Der
    // Invariantentest prueft dieselbe Schranke je Runde ueber alle fuenf Gebiete; die
    // beiden ersetzen einander nicht -- er sieht das Rundenende, diese Zeile jeden
    // einzelnen Aufruf, auch den auf einem selbst gebauten Zwischenzustand.
    if (wechselkurs < 1) {
        festkomma::abbruch(
            "kern::werte::wert -- wechselkurs unter 1: ein negativer Nenner drehte das "
            "Vorzeichen jeder Bewertung (T47, T5 Klasse 6)");
    }

    return mal_geteilt(menge, kurs, wechselkurs);
}

// --- Nr. 2 ---------------------------------------------------------------
i64 korbwert(const Zustand& z, Gebiet land, Sektor sektor)
{
    return korbwert_zwei(z, z, land, sektor);
}

// --- Nr. 3 ---------------------------------------------------------------
i64 anleihewert(const Zustand& z, const Konstanten& konst, Gebiet land)
{
    return anleihewert_zwei(z, z, konst, land);
}

// --- Nr. 4 ---------------------------------------------------------------
i64 waehrungswert(const Zustand& z, Gebiet land)
{
    // Der Kurs ist fest 10.000 -- ein Index mit Startwert 10.000 nach T5 Klasse 5, der
    // sich nie bewegt. Eine Waehrung traegt keinen eigenen Kurs neben dem Wechselkurs;
    // ihre Bewegung steckt genau dort, und `wert` teilt durch ihn.
    return wert(z, handelsvolumen(z, land), 10'000, land);
}

// --- Nr. 5 ---------------------------------------------------------------
i64 markt(const Zustand& z, const Konstanten& konst, Steckplatz platz)
{
    return markt_aus(z, konst, platz, Korbvorrat{});
}

// --- Nr. 6 ---------------------------------------------------------------
i64 stufenwert(const Zustand& z, const Konstanten& konst, Steckplatz platz)
{
    return stufenwert_aus(z, konst, platz, Korbvorrat{});
}

// --- Nr. 7 ---------------------------------------------------------------
i64 marktkorb(const Zustand& mengen, const Zustand& kurse, const Konstanten& konst)
{
    i64 summe = 0;

    // Die zwoelf Koerbe in der Indexordnung aus T9 -- dieselbe Reihenfolge wie die
    // ersten zwoelf Steckplaetze, und deshalb aus derselben Tabelle gelesen.
    for (std::size_t i = 0; i < KOERBE; ++i) {
        summe = plus(summe, korbwert_zwei(mengen, kurse, PLAETZE[i].land, PLAETZE[i].sektor));
    }

    // Die vier Staatsanleihen. Waehrungen gehen nicht ein (T33 Punkt 1).
    for (std::size_t l = 0; l < LAENDER; ++l) {
        summe = plus(summe, anleihewert_zwei(mengen, kurse, konst, static_cast<Gebiet>(l)));
    }

    return summe;
}

// --- Nr. 8 ---------------------------------------------------------------
i64 korbbestand(const Zustand& z, const Konstanten& konst)
{
    i64 summe = 0;

    for (std::size_t i = 0; i < KOERBE; ++i) {
        const Gebiet land = PLAETZE[i].land;
        const Sektor sektor = PLAETZE[i].sektor;
        summe = plus(summe, mal_geteilt(korbwert(z, land, sektor),
                                        fondsanteil(z, konst, land, sektor), 10'000));
    }

    for (std::size_t l = 0; l < LAENDER; ++l) {
        const Gebiet land = static_cast<Gebiet>(l);
        const Steckplatz platz = zustand::steckplatz_anleihe(land);
        const i64 stufen = z.lies(zustand::stelle_position(platz));

        // Eine Anleihe traegt keinen Beteiligungsanteil -- Beteiligungen gibt es nach
        // T15 nur an den zwoelf Land-mal-Sektor-Koerben. Hier steht deshalb allein die
        // Positionshaelfte des Anteils.
        summe = plus(summe, mal_geteilt(anleihewert(z, konst, land),
                                        mal(betrag(stufen), konst.stufenweite), 10'000));
    }

    return summe;
}

// --- Nr. 9 ---------------------------------------------------------------
i64 bip(const Zustand& z, Gebiet land)
{
    i64 summe = 0;
    for (const Sektor sektor : SEKTORLISTE) {
        summe = plus(summe,
                     z.lies(zustand::stelle_sektorgroesse(land, sektor,
                                                          SektorGroesse::Wertschoepfung)));
    }
    return summe;
}

// --- Nr. 10 --------------------------------------------------------------
i64 schuld(const Zustand& z, Gebiet land)
{
    // `staatsschuld` ist die Quote in Basispunkten (T5 Klasse 3); 10.000 Basispunkte
    // sind 100 Prozent des Bruttoinlandsprodukts.
    return mal_geteilt(bip(z, land), z.lies(zustand::stelle_aggregat(land, Aggregat::Staatsschuld)),
                       10'000);
}

// --- Nr. 11 --------------------------------------------------------------
i64 handelsvolumen(const Zustand& z, Gebiet land)
{
    const std::size_t g = static_cast<std::size_t>(land);
    if (g >= GEBIETE) {
        festkomma::abbruch("kern::werte::handelsvolumen -- unbekanntes Gebiet");
    }

    i64 summe = 0;
    for (const Gebiet gegenueber : GEGENUEBER[g]) {
        for (const Sektor sektor : SEKTORLISTE_HANDELBAR) {
            // Beide Richtungen je Paar: Ausfuhr und Einfuhr. Wer nur eine zaehlte,
            // haette die halbe Tiefe des Waehrungsmarktes und ein Handelsvolumen, das
            // sich bei einem Zoll in die falsche Richtung bewegte.
            summe = plus(summe, z.lies(zustand::stelle_handel(land, gegenueber, sektor)));
            summe = plus(summe, z.lies(zustand::stelle_handel(gegenueber, land, sektor)));
        }
    }
    return summe;
}

// --- Nr. 12 --------------------------------------------------------------
i64 anleihekurs(const Zustand& z, const Konstanten& konst, Gebiet land)
{
    const i64 start = konst.leitzins_start[land_nummer(land)];
    const i64 zaehlerzins = plus(start, konst.aufschlag);
    const i64 nenner = plus(z.lies(zustand::stelle_aggregat(land, Aggregat::Leitzins)),
                            konst.aufschlag);

    // T48 schreibt `teile_gerundet(10.000 * (leitzins_start + aufschlag), leitzins +
    // aufschlag)`. Gebaut ist die 128-Bit-Form derselben Rechnung, und zwar aus dem
    // Grund, den T48 fuer den Marktanteil selbst nennt: Es ist dieselbe Zahl, aber die
    // naive Form bildet das Produkt zuerst auf i64 -- eine blanke Multiplikation
    // zweier Groessen, die nach T7 Massnahme 4.3 ohnehin ueber den 128-Bit-Weg
    // laufen muss. Der Nenner ist nach T51 nie null und nie negativ; ist er es doch,
    // bricht `mal_geteilt` nach T6 ab, statt eine Zahl zu liefern.
    return mal_geteilt(10'000, zaehlerzins, nenner);
}

// --- Nr. 13 --------------------------------------------------------------
i64 landespreis(const schreiber::Schreiber& rundenschreiber, Gebiet gebiet, Sektor sektor)
{
    // T39: der Wert am Ende der Vorrunde, nicht der dieser Runde. Der Zugriff steht
    // hier und nirgends sonst -- das ist der ganze Zweck dieser Funktion.
    return rundenschreiber.lies_alt(
        zustand::stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Preis));
}

// --- Nr. 14 --------------------------------------------------------------
i64 fondsanteil(const Zustand& z, const Konstanten& konst, Gebiet land, Sektor sektor)
{
    const i64 stufen = z.lies(zustand::stelle_position(zustand::steckplatz_sektor(land, sektor)));
    const i64 anteil = z.lies(zustand::stelle_beteiligung(land, sektor, BeteiligungsFeld::Anteil));

    // Betrag der Stufenzahl, nicht ihr Vorzeichen: Ein grosser Short bewegt einen
    // Markt so stark wie ein grosser Long.
    return plus(mal(betrag(stufen), konst.stufenweite), anteil);
}

// --- Nr. 15 --------------------------------------------------------------
i64 positionswert(const Zustand& z, const Konstanten& konst, Steckplatz platz)
{
    return positionswert_aus(z, konst, platz, Korbvorrat{});
}

// --- Nr. 16 --------------------------------------------------------------
i64 beteiligung_wert(const Zustand& z, const Konstanten& konst, Gebiet land, Sektor sektor)
{
    return beteiligung_wert_aus(z, konst, land, sektor, Korbvorrat{});
}

// --- Nr. 17 --------------------------------------------------------------
i64 fondsvermoegen(const Zustand& z, const Konstanten& konst)
{
    // Die zwoelf Korbwerte, einmal je Aufruf (T47). Ab hier liest jeder Leser aus
    // diesem Feld, und damit sehen Steckplatz und Beteiligung nachweislich dieselbe
    // Bewertung -- nicht, weil es so verabredet ist, sondern weil es keinen zweiten
    // Rechenweg gibt, den sie nehmen koennten.
    Korbvorrat vorrat;
    for (std::size_t i = 0; i < KOERBE; ++i) {
        vorrat.korb[i] = korbwert(z, PLAETZE[i].land, PLAETZE[i].sektor);
    }
    vorrat.gefuellt = true;

    i64 summe = z.lies(zustand::stelle_fonds(FondsGroesse::Kasse));

    // Beide Summen laufen ueber die Indexordnung aus T9, nie ueber eine Menge (T47).
    for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
        summe = plus(summe, positionswert_aus(z, konst, static_cast<Steckplatz>(p), vorrat));
    }
    for (std::size_t i = 0; i < KOERBE; ++i) {
        summe = plus(summe,
                     beteiligung_wert_aus(z, konst, PLAETZE[i].land, PLAETZE[i].sektor, vorrat));
    }

    return minus(summe, z.lies(zustand::stelle_fonds(FondsGroesse::Hebelstand)));
}

}  // namespace kern::werte
