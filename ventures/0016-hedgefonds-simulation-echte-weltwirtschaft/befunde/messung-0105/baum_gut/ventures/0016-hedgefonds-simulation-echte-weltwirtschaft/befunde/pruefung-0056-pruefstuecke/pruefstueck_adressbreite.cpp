// Pruefstueck des Kern-Pruefers zu Paket 0056 -- Messung, kein Bestandteil des Pakets.
//
// Beantwortet die eine Zahl, die man fuer die Randrechnung des Meldungspuffers braucht:
// Wie lang wird die laengste Adressform mit ihrer laufenden Nummer, und wie lang die
// Form fuer eine Adresse ausserhalb der 310?
//
// Gemessen am 2026-09-04:
//   laengste Adressform mit Nummer: 57 Zeichen, Platz 127
//     -> "land.DE.instrument.regulierung.restverzoegerung (Nr. 128)"
//   Form ausserhalb: 46 Zeichen -> "(Adresse ausserhalb der 310 Felder, Platz 310)"
//   MELDUNG_ZEICHEN_MAX = 511
//
// Die Aussenform waechst mit der Zahl: 46 - 3 Ziffern = 43 feste Zeichen, schlimmstenfalls
// also 43 + 20 = 63. Das ist der Wert, mit dem die Tabelle im Befund rechnet.
//
// Bauen: die Datei nach `kern/test/` legen, `cmake -S kern -B <bau ausserhalb des Repos>`,
// dann `cmake --build <bau> --target pruefstueck_adressbreite`. Der Baulauf sammelt unter
// `befunde/` nicht ein (`baulauf.py:116`), hier liegt sie also niemandem im Weg.

#include <cstdio>
#include <cstddef>

#include "kern/meldung.hpp"
#include "kern/zustand.hpp"

int main()
{
    std::size_t laengste = 0;
    kern::zustand::Index wo = 0;
    for (kern::zustand::Index i = 0; i < kern::zustand::FELDER; ++i) {
        kern::meldung::Meldung m;
        m.adresse(i);
        if (m.laenge() > laengste) {
            laengste = m.laenge();
            wo = i;
        }
    }
    kern::meldung::Meldung l;
    l.adresse(wo);
    std::printf("laengste Adressform mit Nummer: %zu Zeichen, Platz %zu -> \"%s\"\n",
                laengste, static_cast<std::size_t>(wo), l.fertig());

    kern::meldung::Meldung d;
    d.adresse(kern::zustand::FELDER);
    std::printf("Form ausserhalb: %zu Zeichen -> \"%s\"\n", d.laenge(), d.fertig());
    std::printf("MELDUNG_ZEICHEN_MAX = %zu\n", kern::meldung::MELDUNG_ZEICHEN_MAX);
    return 0;
}
