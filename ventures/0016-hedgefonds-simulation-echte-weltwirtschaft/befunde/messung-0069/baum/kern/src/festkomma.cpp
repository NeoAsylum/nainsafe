//! Festkomma -- der Abbruch und die Zahlenproben.
//!
//! Die Rechenregeln stehen in `include/kern/festkomma.hpp`, weil sie `constexpr`
//! sein muessen. Hier steht, was nicht `constexpr` sein kann (der Abbruch) und was
//! nicht in einen Kopf gehoert (die Proben).
//!
//! **Die Proben sind `static_assert`, und das ist der Punkt.** Sie laufen beim
//! Uebersetzen, nicht beim Testen. Eine verfehlte Rundung ist damit kein roter Test,
//! den jemand lesen muss, sondern eine Datei, die sich nicht uebersetzen laesst --
//! und `baulauf.py` legt das Urteil des Uebersetzers ungefiltert als Befund ab. Was
//! sich hier nicht nachweisen laesst, weil es einen Abbruch ausloest, steht als
//! laufende Probe in `test/festkomma_probe.cpp`.

#include <stdexcept>

#include "kern/festkomma.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::festkomma {

void abbruch(const char* grund)
{
    // `std::domain_error` und nicht `std::abort`: siehe die Begruendung an der
    // Deklaration in `festkomma.hpp`. Kurz -- ein Wurf ist zur Uebersetzungszeit
    // pruefbar und zur Laufzeit nachweisbar, ein Signal ist beides nicht.
    throw std::domain_error(grund);
}

// ---------------------------------------------------------------------------
// Probe 1 -- die Rundungsregel, alle vier Vorzeichenkombinationen (T6)
// ---------------------------------------------------------------------------
//
// Erwartungswerte ausgeschrieben und von Hand nachrechenbar. 7/2 ist 3,5 und liegt
// genau zwischen zwei Ganzzahlen; "vom Null weg" heisst, dass der Betrag aufgerundet
// wird -- also 4, und mit umgekehrtem Vorzeichen -4. Genau hier unterscheidet sich
// die Regel vom Abschneiden der Maschine, das 3 und -3 liefern wuerde.

static_assert(teile_gerundet( 7,  2) ==  4, "7/2 = 3,5 -> Betrag aufgerundet");
static_assert(teile_gerundet(-7,  2) == -4, "-7/2 = -3,5 -> Betrag aufgerundet");
static_assert(teile_gerundet( 7, -2) == -4, "7/-2 = -3,5 -> Betrag aufgerundet");
static_assert(teile_gerundet(-7, -2) ==  4, "-7/-2 = 3,5 -> Betrag aufgerundet");

static_assert(teile_gerundet( 5,  2) ==  3, "5/2 = 2,5 -> Betrag aufgerundet");
static_assert(teile_gerundet(-5,  2) == -3, "-5/2 = -2,5 -> Betrag aufgerundet");
static_assert(teile_gerundet( 5, -2) == -3, "5/-2 = -2,5 -> Betrag aufgerundet");
static_assert(teile_gerundet(-5, -2) ==  3, "-5/-2 = 2,5 -> Betrag aufgerundet");

// Die Symmetrie ist die eigentliche Forderung aus T6: Jeder Betrag wird gleich
// gerundet, egal in welche Richtung der Fonds steht.
static_assert(teile_gerundet( 1,  2) ==  1, "0,5 -> 1");
static_assert(teile_gerundet(-1,  2) == -1, "-0,5 -> -1");
static_assert(teile_gerundet( 3,  2) ==  2, "1,5 -> 2");
static_assert(teile_gerundet(-3,  2) == -2, "-1,5 -> -2");

// Ungerader Nenner: Hier gibt es keinen Wert genau in der Mitte, und die Regel muss
// trotzdem in beide Richtungen dasselbe tun.
static_assert(teile_gerundet( 2,  3) ==  1, "0,667 -> 1");
static_assert(teile_gerundet(-2,  3) == -1, "-0,667 -> -1");
static_assert(teile_gerundet( 1,  3) ==  0, "0,333 -> 0");
static_assert(teile_gerundet(-1,  3) ==  0, "-0,333 -> 0");
static_assert(teile_gerundet( 5,  3) ==  2, "1,667 -> 2");
static_assert(teile_gerundet( 4,  3) ==  1, "1,333 -> 1");

static_assert(teile_gerundet( 0,  7) ==  0, "null bleibt null");
static_assert(teile_gerundet(10,  5) ==  2, "glatt bleibt glatt");

// Die Raender von i64 gehen glatt durch, solange nichts hinausfaellt.
static_assert(teile_gerundet(I64_MAX, 1) == I64_MAX, "groesster Wert, Nenner 1");
static_assert(teile_gerundet(I64_MIN, 1) == I64_MIN, "kleinster Wert, Nenner 1");

// ---------------------------------------------------------------------------
// Probe 2 -- `mal_geteilt` rechnet ueber i128 (T47, ADR 0011 Massnahme 3)
// ---------------------------------------------------------------------------
//
// Die Zahlenprobe des Pruefers aus T47, unveraendert uebernommen: ein Korb von
// 21.000.000.000 Tausend USD, ein Beteiligungsanteil von 20 Zehntausendsteln, also
// 0,2 Prozent. 21.000.000.000 * 20 / 10.000 = 42.000.000 Tausend USD = 42 Mrd USD,
// und das sind genau 0,2 Prozent von 21 Bio USD. Das Produkt 420.000.000.000 passt
// hier noch in i64 -- die Probe belegt die Rechenvorschrift, nicht den Zwischentyp.
static_assert(mal_geteilt(21'000'000'000, 20, 10'000) == 42'000'000,
              "T47: Korb 21 Bio USD, Anteil 0,2 % -> 42 Mrd USD");

// Den Zwischentyp belegt diese Probe: 9.000.000.000.000.000.000 * 4 ist
// 36.000.000.000.000.000.000 und damit rund viermal so gross wie i64 fasst
// (9.223.372.036.854.775.807). Geteilt durch 8 bleibt
// 4.500.000.000.000.000.000 -- ein Wert, der wieder hineinpasst. Ohne den
// i128-Zwischenwert waere das Produkt unter `-fwrapv` still umgebrochen und das
// Ergebnis eine plausible falsche Zahl.
static_assert(mal_geteilt(9'000'000'000'000'000'000, 4, 8) == 4'500'000'000'000'000'000,
              "a*b sprengt i64 um das Vierfache, das Ergebnis passt wieder");

// Dieselbe Sache noch einmal mit zwei Faktoren, die einzeln harmlos aussehen:
// 4.000.000.000 * 4.000.000.000 = 16.000.000.000.000.000.000 > i64.
static_assert(mal_geteilt(4'000'000'000, 4'000'000'000, 1'000'000'000) == 16'000'000'000,
              "zwei harmlose Faktoren, ein Produkt ausserhalb von i64");

// Und die Rundung gilt in `mal_geteilt` genauso wie in `teile_gerundet`.
static_assert(mal_geteilt( 5, 1, 2) ==  3, "2,5 -> 3");
static_assert(mal_geteilt(-5, 1, 2) == -3, "-2,5 -> -3");
static_assert(mal_geteilt( 1, 1, 3) ==  0, "0,333 -> 0");

// ---------------------------------------------------------------------------
// Probe 3 -- Potenz und Wurzel (T29)
// ---------------------------------------------------------------------------

static_assert(potenz(2, 10) == 1024,   "2^10");
static_assert(potenz(-3, 3) == -27,    "ungerader Exponent behaelt das Vorzeichen");
static_assert(potenz(-3, 2) == 9,      "gerader Exponent nicht");
static_assert(potenz(7, 0)  == 1,      "Exponent null");
static_assert(potenz(10, 18) == 1'000'000'000'000'000'000, "10^18 passt noch in i64");

static_assert(wurzel(0, 2) == 0,       "Wurzel aus null");
static_assert(wurzel(1, 2) == 1,       "Wurzel aus eins");
static_assert(wurzel(2, 2) == 1,       "abgerundet: 1,41 -> 1");
static_assert(wurzel(4, 2) == 2,       "glatte Quadratwurzel");
static_assert(wurzel(1'000'000, 2) == 1000, "1000^2");
static_assert(wurzel(999'999, 2) == 999,    "eins darunter faellt auf 999");

// Die dritte Wurzel ist der Fall, den T29 ausdruecklich nennt: der Exponent 1/3 der
// Produktionsfunktion.
static_assert(wurzel(1000, 3) == 10,   "10^3");
static_assert(wurzel(999, 3)  == 9,    "eins darunter faellt auf 9");
static_assert(wurzel(1001, 3) == 10,   "eins darueber bleibt 10");
static_assert(wurzel(8, 3)    == 2,    "2^3");
static_assert(wurzel(7, 3)    == 1,    "abgerundet: 1,91 -> 1");

// Der groesste Fall, den es gibt: Er belegt zugleich, dass der Startwert der
// Newton-Iteration nicht ueberlaeuft. 3.037.000.499^2 = 9.223.372.030.926.249.001
// liegt unter i64_MAX, 3.037.000.500^2 = 9.223.372.037.000.250.000 darueber.
static_assert(wurzel(I64_MAX, 2) == 3'037'000'499, "abgerundete Wurzel des groessten i64");
static_assert(wurzel(I64_MAX, 32) == 3, "3^32 = 1.853.020.188.851.841 <= i64_MAX < 4^32");

static_assert(wurzel(12'345, 1) == 12'345, "Grad 1 gibt den Wert zurueck");

// Nachbedingung, an einem Wert nachgerechnet statt behauptet:
// wurzel(x,n)^n <= x < (wurzel(x,n)+1)^n.
static_assert(potenz(wurzel(999'999, 2), 2) <= 999'999, "Nachbedingung, untere Haelfte");
static_assert(potenz(wurzel(999'999, 2) + 1, 2) > 999'999, "Nachbedingung, obere Haelfte");

}  // namespace kern::festkomma
