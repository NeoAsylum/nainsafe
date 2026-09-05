//! Laufende Probe fuer `kern::festkomma`.
//!
//! Die Rechenwerte sind schon in `src/festkomma.cpp` als `static_assert` belegt und
//! damit beim Uebersetzen geprueft. Diese Probe gibt es fuer zwei Dinge, die ein
//! `static_assert` nicht kann:
//!
//!   1. **Die Abbruchpfade.** `teile_gerundet(1, 0)` laesst sich zur
//!      Uebersetzungszeit nur dadurch pruefen, dass die Datei nicht uebersetzt --
//!      und eine Datei, die nicht uebersetzt, ist kein Nachweis, sondern ein roter
//!      Baulauf. Hier wird der Wurf gefangen und gezaehlt.
//!   2. **Das Testprofil aus ADR 0011, Massnahme 2.** Die Probe linkt
//!      `kern_geprueft`, also dieselben Quellen mit `-fsanitize=undefined,address`.
//!      Damit die Sanitizer ueberhaupt etwas zu sehen bekommen, laufen alle
//!      Rechnungen hier ueber `undurchsichtig()` -- sonst faltet der Uebersetzer die
//!      `constexpr`-Aufrufe weg und misst seine eigene Konstantenrechnung.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <cstdio>
#include <stdexcept>
#include <string_view>

#include "kern/festkomma.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::i64;
using kern::festkomma::I64_MAX;
using kern::festkomma::I64_MIN;
using kern::festkomma::mal;
using kern::festkomma::mal_geteilt;
using kern::festkomma::minus;
using kern::festkomma::plus;
using kern::festkomma::potenz;
using kern::festkomma::teile_gerundet;
using kern::festkomma::wurzel;

/// Die beiden Wertepaare, an denen Paket 0052 den Waechter von `mal` misst -- als
/// benannte Groessen, weil eine abgeschriebene Grenze nach der ersten Aenderung nur
/// noch sich selbst prueft.
///
/// `MAL_FAKTOR_PASST` ist die abgerundete Quadratwurzel von `I64_MAX`; sein Quadrat
/// ist damit das groesste Produkt zweier gleicher Faktoren, das noch in `i64` passt.
/// Das sind 9.223.372.030.926.249.001 gegen `I64_MAX` mit
/// 9.223.372.036.854.775.807. Einen Schritt darueber liegt
/// `MAL_FAKTOR_BRICHT_AB`, dessen Quadrat 9.223.372.037.000.250.000 betraegt und
/// `I64_MAX` um 145.474.193 ueberschreitet.
constexpr i64 MAL_FAKTOR_PASST     = wurzel(I64_MAX, 2);
constexpr i64 MAL_FAKTOR_BRICHT_AB = MAL_FAKTOR_PASST + 1;
constexpr i64 MAL_PRODUKT_PASST    = mal_geteilt(MAL_FAKTOR_PASST, MAL_FAKTOR_PASST, 1);

// Der zweite Weg ist zugleich der Pruefstand: `MAL_PRODUKT_PASST` entsteht ueber
// `mal_geteilt` mit Nenner 1, also ueber die Regel, die `src/festkomma.cpp` schon
// an eigenen Zahlen festnagelt. Stimmt `mal` damit ueberein, stimmen beide Wege.
//
// Sie stehen ausnahmsweise hier statt in `src/festkomma.cpp`, wo die uebrigen
// Zahlenproben liegen: Paket 0052 nennt in seiner Dateiliste den Kopf und diese
// Probe, und eine Datei ausserhalb der Liste gehoert einem anderen Paket.
static_assert(MAL_PRODUKT_PASST <= I64_MAX, "das groesste passende Produkt passt noch");
static_assert(mal(MAL_FAKTOR_PASST, MAL_FAKTOR_PASST) == MAL_PRODUKT_PASST,
              "beide Wege liefern dasselbe -- schon beim Uebersetzen");
static_assert(mal(-MAL_FAKTOR_PASST, MAL_FAKTOR_PASST) == -MAL_PRODUKT_PASST,
              "und mit umgekehrtem Vorzeichen zeichengleich zurueck");

/// Die beiden Raender der Strichrechnung (T7, Massnahme 4, Punkt 2) -- hergeleitet
/// aus `I64_MAX` und `I64_MIN` und nicht abgeschrieben, aus demselben Grund wie bei
/// den `MAL_`-Groessen darueber.
///
/// `SUMMAND_PASST_OBEN` ist der groesste Wert, zu dem sich 1 noch addieren laesst:
/// Das Ergebnis ist genau `I64_MAX`. Einen Schritt darueber liegt `I64_MAX` selbst,
/// und `plus(I64_MAX, 1)` ist damit der erste Aufruf, der abbrechen muss. Nach unten
/// dieselbe Bauart: `SUMMAND_PASST_UNTEN` ist der kleinste Wert, von dem sich 1 noch
/// abziehen laesst, und `minus(I64_MIN, 1)` der erste Aufruf darunter.
constexpr i64 SUMMAND_PASST_OBEN  = I64_MAX - 1;
constexpr i64 SUMMAND_PASST_UNTEN = I64_MIN + 1;

// Die Positivkontrollen, schon beim Uebersetzen: An beiden Raendern kommt der
// groesste noch passende Wert heraus, und zwar ueber jede der beiden Rechenarten.
// Damit ist ein Waechter ausgeschlossen, der aus lauter Vorsicht schon vor der
// Grenze abbricht -- die haeufigere Sorte Fehler als die um eins zu spaete.
static_assert(plus(SUMMAND_PASST_OBEN, 1) == I64_MAX,
              "der groesste noch passende Summand fuehrt genau auf I64_MAX");
static_assert(plus(SUMMAND_PASST_UNTEN, -1) == I64_MIN,
              "und nach unten genau auf I64_MIN");
static_assert(minus(SUMMAND_PASST_OBEN, -1) == I64_MAX,
              "dieselben beiden Raender ueber die Subtraktion");
static_assert(minus(SUMMAND_PASST_UNTEN, 1) == I64_MIN,
              "und auch hier nach unten");

// Der zweite Weg als Pruefstand, wie bei `mal` und `mal_geteilt`: Wo `-b` selbst
// darstellbar ist, muessen `plus(a, b)` und `minus(a, -b)` uebereinstimmen.
static_assert(plus(SUMMAND_PASST_OBEN, 1) == minus(SUMMAND_PASST_OBEN, -1),
              "beide Wege liefern denselben Rand");

// Und der eine Fall, in dem sie es nicht muessen: `-I64_MIN` ist selbst der
// Ueberlauf. `minus(-1, I64_MIN)` hat trotzdem ein gueltiges Ergebnis, naemlich
// I64_MAX -- eine Subtraktion, die als `plus(a, -b)` gebaut waere, braeche hier ab.
static_assert(minus(-1, I64_MIN) == I64_MAX,
              "die Subtraktion ist eigenstaendig gebaut, nicht als plus(a, -b)");

int fehlgeschlagen = 0;

/// Nimmt dem Uebersetzer die Konstantenfaltung. `volatile` zwingt ihn, den Wert
/// wirklich zu schreiben und zu lesen -- erst dadurch rechnet das Programm zur
/// Laufzeit, und erst dann sehen die Sanitizer die Rechnung.
i64 undurchsichtig(i64 wert)
{
    volatile i64 zwischenlager = wert;
    return zwischenlager;
}

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

template <typename Aufruf>
void erwarte_abbruch(Aufruf aufruf, const char* text, int zeile)
{
    try {
        aufruf();
    } catch (const std::domain_error&) {
        return;                        // genau das war die Erwartung
    }
    std::fprintf(stderr, "KEIN ABBRUCH Zeile %d: %s\n", zeile, text);
    ++fehlgeschlagen;
}

/// Faengt den Abbruch eines Aufrufs und sagt, ob seine Meldung `nadel` enthaelt.
///
/// **Warum nicht `erwarte_abbruch` genuegt.** Jener Waechter belegt, **dass**
/// geworfen wurde, nicht **welcher** Riegel geworfen hat. `plus` und `minus` liegen
/// im selben Kopf und werfen dieselbe Klasse; ein Nachweis, der sie nicht
/// auseinanderhaelt, bliebe gruen, wenn beide Abbruchpfade in denselben Zweig
/// zusammenfielen.
///
/// Bleibt der Abbruch aus, ist die Antwort `false` -- ein ausbleibender Abbruch darf
/// keine Pruefung erfuellen, die einen erwartet.
template <typename Aufruf>
bool abbruchmeldung_enthaelt(Aufruf aufruf, std::string_view nadel)
{
    try {
        aufruf();
    } catch (const std::domain_error& fehler) {
        return std::string_view{fehler.what()}.find(nadel) != std::string_view::npos;
    }
    return false;
}

}  // namespace

#define PRUEFE(ausdruck)     pruefe((ausdruck), #ausdruck, __LINE__)
#define ERWARTE_ABBRUCH(ausdruck) \
    erwarte_abbruch([] { static_cast<void>(ausdruck); }, #ausdruck, __LINE__)
#define ABBRUCH_MELDET(ausdruck, nadel) \
    abbruchmeldung_enthaelt([] { static_cast<void>(ausdruck); }, (nadel))

int main()
{
    // --- Die Rundungsregel, zur Laufzeit und unter den Sanitizern (T6) ---------
    PRUEFE(teile_gerundet(undurchsichtig( 7), undurchsichtig( 2)) ==  4);
    PRUEFE(teile_gerundet(undurchsichtig(-7), undurchsichtig( 2)) == -4);
    PRUEFE(teile_gerundet(undurchsichtig( 7), undurchsichtig(-2)) == -4);
    PRUEFE(teile_gerundet(undurchsichtig(-7), undurchsichtig(-2)) ==  4);
    PRUEFE(teile_gerundet(undurchsichtig( 5), undurchsichtig( 2)) ==  3);
    PRUEFE(teile_gerundet(undurchsichtig(-5), undurchsichtig( 2)) == -3);
    PRUEFE(teile_gerundet(undurchsichtig( 5), undurchsichtig(-2)) == -3);
    PRUEFE(teile_gerundet(undurchsichtig(-5), undurchsichtig(-2)) ==  3);

    // Die Raender von i64, die ein Sanitizer am ehesten aufdeckt.
    PRUEFE(teile_gerundet(undurchsichtig(I64_MIN), undurchsichtig(1)) == I64_MIN);
    PRUEFE(teile_gerundet(undurchsichtig(I64_MAX), undurchsichtig(1)) == I64_MAX);
    PRUEFE(teile_gerundet(undurchsichtig(I64_MIN), undurchsichtig(2)) == -4'611'686'018'427'387'904);

    // --- Multiplikation-Division ueber i128 (T47, ADR 0011 Massnahme 3) --------
    PRUEFE(mal_geteilt(undurchsichtig(21'000'000'000), undurchsichtig(20),
                       undurchsichtig(10'000)) == 42'000'000);
    PRUEFE(mal_geteilt(undurchsichtig(9'000'000'000'000'000'000), undurchsichtig(4),
                       undurchsichtig(8)) == 4'500'000'000'000'000'000);
    PRUEFE(mal_geteilt(undurchsichtig(I64_MAX), undurchsichtig(I64_MAX),
                       undurchsichtig(I64_MAX)) == I64_MAX);
    PRUEFE(mal_geteilt(undurchsichtig(I64_MIN), undurchsichtig(I64_MIN),
                       undurchsichtig(I64_MIN)) == I64_MIN);

    // --- Potenz und Wurzel (T29) ----------------------------------------------
    PRUEFE(potenz(undurchsichtig(2), 10) == 1024);
    PRUEFE(potenz(undurchsichtig(-3), 3) == -27);
    PRUEFE(wurzel(undurchsichtig(1'000'000), 2) == 1000);
    PRUEFE(wurzel(undurchsichtig(999), 3) == 9);
    PRUEFE(wurzel(undurchsichtig(I64_MAX), 2) == 3'037'000'499);

    // Die Nachbedingung, an tausend Werten statt an einem: Ist sie fuer alle
    // erfuellt, haengt das Ergebnis nicht an WURZEL_SCHRITTE.
    for (i64 x = 0; x < 1000; ++x) {
        const i64 w = wurzel(undurchsichtig(x), 3);
        PRUEFE(potenz(w, 3) <= x && potenz(w + 1, 3) > x);
    }

    // --- Die Abbruchpfade (T6, T7) --------------------------------------------
    //
    // Nenner null bricht ab und wird nie still zu null -- der Fall, an dem Befund 2
    // der zweiten Pruefung haengt.
    ERWARTE_ABBRUCH(teile_gerundet(undurchsichtig(1), undurchsichtig(0)));
    ERWARTE_ABBRUCH(teile_gerundet(undurchsichtig(0), undurchsichtig(0)));
    ERWARTE_ABBRUCH(mal_geteilt(undurchsichtig(1), undurchsichtig(2), undurchsichtig(0)));

    // Ueberlauf ist ein Absturz, kein Umlauf (T7). `I64_MIN / -1` ist der eine Fall,
    // in dem eine gueltige Division ein Ergebnis ausserhalb von i64 hat.
    ERWARTE_ABBRUCH(teile_gerundet(undurchsichtig(I64_MIN), undurchsichtig(-1)));
    ERWARTE_ABBRUCH(mal_geteilt(undurchsichtig(I64_MAX), undurchsichtig(2), undurchsichtig(1)));
    ERWARTE_ABBRUCH(potenz(undurchsichtig(I64_MAX), 2));
    ERWARTE_ABBRUCH(potenz(undurchsichtig(10), 19));

    // Wurzel: Grad und Radikand haben Grenzen, und sie sind Abbrueche.
    ERWARTE_ABBRUCH(wurzel(undurchsichtig(-1), 2));
    ERWARTE_ABBRUCH(wurzel(undurchsichtig(4), 0));
    ERWARTE_ABBRUCH(wurzel(undurchsichtig(4), 33));

    // --- Blanke Multiplikation ueber i128 (T7, Massnahme 4, Punkt 3) -----------
    //
    // Das groesste noch passende Produkt kommt zeichengleich zurueck, in beide
    // Richtungen -- ein Waechter, der nur die obere Grenze kennt, waere die Haelfte.
    PRUEFE(mal(undurchsichtig( MAL_FAKTOR_PASST), undurchsichtig(MAL_FAKTOR_PASST))
           ==  MAL_PRODUKT_PASST);
    PRUEFE(mal(undurchsichtig(-MAL_FAKTOR_PASST), undurchsichtig(MAL_FAKTOR_PASST))
           == -MAL_PRODUKT_PASST);
    PRUEFE(mal(undurchsichtig(I64_MAX), undurchsichtig(1)) == I64_MAX);
    PRUEFE(mal(undurchsichtig(I64_MIN), undurchsichtig(1)) == I64_MIN);
    PRUEFE(mal(undurchsichtig(0), undurchsichtig(I64_MIN)) == 0);

    // Zwei Wege fuer dieselbe Rechnung, diesmal zur Laufzeit und unter den
    // Sanitizern: `mal(a, b)` und `mal_geteilt(a, b, 1)` muessen uebereinstimmen.
    PRUEFE(mal(undurchsichtig(MAL_FAKTOR_PASST), undurchsichtig(MAL_FAKTOR_PASST))
           == mal_geteilt(undurchsichtig(MAL_FAKTOR_PASST),
                          undurchsichtig(MAL_FAKTOR_PASST), undurchsichtig(1)));

    // Der Abbruchfall: Einen Schritt ueber der Grenze ist das Quadrat
    // 9.223.372.037.000.250.000, und es nimmt denselben Weg wie Massnahme 4.1 --
    // `intern::nach_i64` wirft `std::domain_error`. Kein gekappter Wert, kein
    // stiller Umbruch unter `-fwrapv`.
    ERWARTE_ABBRUCH(mal(undurchsichtig(MAL_FAKTOR_BRICHT_AB),
                        undurchsichtig(MAL_FAKTOR_BRICHT_AB)));
    ERWARTE_ABBRUCH(mal(undurchsichtig(-MAL_FAKTOR_BRICHT_AB),
                        undurchsichtig(MAL_FAKTOR_BRICHT_AB)));
    ERWARTE_ABBRUCH(mal(undurchsichtig(I64_MIN), undurchsichtig(-1)));

    // --- Strichrechnung ueber die Ueberlaufbausteine (T7, Massnahme 4, Punkt 2) ---
    //
    // Erst die Positivkontrollen, dann die Abbrueche -- in dieser Reihenfolge, weil
    // ein Abbruchnachweis ohne Kontrolle davor auch von einer Funktion erfuellt
    // wuerde, die immer abbricht.
    PRUEFE(plus(undurchsichtig(3), undurchsichtig(4)) == 7);
    PRUEFE(minus(undurchsichtig(3), undurchsichtig(4)) == -1);

    // Die groessten noch passenden Werte, beide Raender, beide Rechenarten. Zur
    // Laufzeit und damit unter den Sanitizern -- der `static_assert` oben prueft
    // dieselben vier Werte beim Uebersetzen, wo kein Sanitizer mitliest.
    PRUEFE(plus(undurchsichtig(SUMMAND_PASST_OBEN),  undurchsichtig( 1)) == I64_MAX);
    PRUEFE(plus(undurchsichtig(SUMMAND_PASST_UNTEN), undurchsichtig(-1)) == I64_MIN);
    PRUEFE(minus(undurchsichtig(SUMMAND_PASST_OBEN),  undurchsichtig(-1)) == I64_MAX);
    PRUEFE(minus(undurchsichtig(SUMMAND_PASST_UNTEN), undurchsichtig( 1)) == I64_MIN);

    // Die ganze Spanne in einem Schritt, ohne dass etwas hinausfaellt.
    PRUEFE(plus(undurchsichtig(I64_MAX), undurchsichtig(I64_MIN)) == -1);
    PRUEFE(minus(undurchsichtig(-1), undurchsichtig(I64_MIN)) == I64_MAX);

    // Die beiden Abbruchpfade, je einen Schritt ueber den Kontrollen darueber. Die
    // Nadel nennt den Riegel, nicht bloss die Klasse des Wurfs: "plus: Summe" und
    // "minus: Differenz" enthalten einander nicht, also unterscheidet die Suche die
    // beiden wirklich.
    PRUEFE(ABBRUCH_MELDET(plus(undurchsichtig(I64_MAX), undurchsichtig(1)),
                          "plus: Summe"));
    PRUEFE(ABBRUCH_MELDET(plus(undurchsichtig(I64_MIN), undurchsichtig(-1)),
                          "plus: Summe"));
    PRUEFE(ABBRUCH_MELDET(minus(undurchsichtig(I64_MAX), undurchsichtig(-1)),
                          "minus: Differenz"));
    PRUEFE(ABBRUCH_MELDET(minus(undurchsichtig(I64_MIN), undurchsichtig(1)),
                          "minus: Differenz"));

    // Negativkontrolle auf die Textsuche selbst, sonst waere sie ein Ritual: Der
    // Waechter von `mal` bricht nachweislich ab -- drei Zeilen weiter oben steht es
    // --, seine Meldung nennt aber weder den einen noch den anderen Riegel. Eine
    // wirkungslose Suche liesse beide Zeilen hier durchgehen.
    PRUEFE(!ABBRUCH_MELDET(mal(undurchsichtig(MAL_FAKTOR_BRICHT_AB),
                               undurchsichtig(MAL_FAKTOR_BRICHT_AB)),
                           "plus: Summe"));
    PRUEFE(!ABBRUCH_MELDET(mal(undurchsichtig(MAL_FAKTOR_BRICHT_AB),
                               undurchsichtig(MAL_FAKTOR_BRICHT_AB)),
                           "minus: Differenz"));

    // Und die zweite Haelfte derselben Kontrolle: Bleibt der Abbruch ganz aus, ist
    // die Antwort `false` und nicht etwa `true`, weil nichts widersprochen hat.
    PRUEFE(!ABBRUCH_MELDET(plus(undurchsichtig(SUMMAND_PASST_OBEN), undurchsichtig(1)),
                           "plus: Summe"));

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::festkomma -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::festkomma -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
