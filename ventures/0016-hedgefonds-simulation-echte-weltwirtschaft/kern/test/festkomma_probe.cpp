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

#include "kern/festkomma.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::i64;
using kern::festkomma::I64_MAX;
using kern::festkomma::I64_MIN;
using kern::festkomma::mal_geteilt;
using kern::festkomma::potenz;
using kern::festkomma::teile_gerundet;
using kern::festkomma::wurzel;

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

}  // namespace

#define PRUEFE(ausdruck)     pruefe((ausdruck), #ausdruck, __LINE__)
#define ERWARTE_ABBRUCH(ausdruck) \
    erwarte_abbruch([] { static_cast<void>(ausdruck); }, #ausdruck, __LINE__)

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

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::festkomma -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::festkomma -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
