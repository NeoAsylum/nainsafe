// Gegenprobe zu Abnahmebedingung 3c: dieselbe Frage mit der echten Runde des Kerns.
//
// `schreiber_probe.cpp` fuehrt 3c mit einer von Hand gebauten Runde vor -- der Helfer
// `weltlauf_runde` schreibt auf jede Maskenadresse `platz * 10`, auf `partie.runde`
// also 3060. Hier laeuft stattdessen `kern::schritt::schritt(...)`, bei sonst gleichem
// Ablauf: binden, Runde laufen lassen, Rundenende zurueckschreiben, alten Zugang
// benutzen. Rueckgabewert 0 heisst: beide Wege sind zu.
#include "kern/schritt.hpp"
#include "kern/zustand.hpp"

#include <cstdio>
#include <stdexcept>

int main()
{
    using kern::zustand::FondsGroesse;
    using kern::zustand::PartieFeld;
    using kern::zustand::Startbelegung;
    using kern::zustand::Zustand;

    const auto kasse       = kern::zustand::stelle_fonds(FondsGroesse::Kasse);
    const auto platz_runde = kern::zustand::stelle_partie(PartieFeld::Runde);

    Zustand       partie;
    Startbelegung zugang{partie};
    zugang.setze(kasse, 1000000);

    const auto ergebnis = kern::schritt::schritt(partie, {}, kern::schritt::Modus::Weltlauf);
    partie              = ergebnis.neuer_zustand;

    std::printf("nach einer echten Runde: partie.runde = %lld, Kette %zu Glieder, "
                "vor_der_ersten_runde = %s\n",
                static_cast<long long>(partie.lies(platz_runde)),
                ergebnis.kette_dieser_runde.laenge(),
                kern::zustand::vor_der_ersten_runde(partie) ? "ja" : "nein");

    int durchgekommen = 0;

    try {
        zugang.setze(kasse, 4711);
        std::printf("KEIN ABBRUCH: der Zugang von vor Runde 1 hat nach der Runde "
                    "geschrieben -- fonds.kasse = %lld\n",
                    static_cast<long long>(partie.lies(kasse)));
        ++durchgekommen;
    } catch (const std::domain_error& fehler) {
        std::printf("Abbruch wie erwartet (alter Zugang): %s\n", fehler.what());
    }

    try {
        Startbelegung zweiter{partie};
        zweiter.setze(kasse, 815);
        std::printf("KEIN ABBRUCH: ein neuer Zugang bindet nach der Runde -- "
                    "fonds.kasse = %lld\n",
                    static_cast<long long>(partie.lies(kasse)));
        ++durchgekommen;
    } catch (const std::domain_error& fehler) {
        std::printf("Abbruch wie erwartet (neuer Zugang): %s\n", fehler.what());
    }

    if (durchgekommen != 0) {
        std::fprintf(stderr, "%d von 2 Schreibwegen sind nach einer echten Runde offen.\n",
                     durchgekommen);
        return 1;
    }
    std::printf("beide Wege zu.\n");
    return 0;
}
