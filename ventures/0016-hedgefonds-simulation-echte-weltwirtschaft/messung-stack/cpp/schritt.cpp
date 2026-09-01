// Deterministischer Festkomma-Weltschritt, C++-Fassung der Stack-Messung.
// Uebersetzt mit: g++ -O2 -std=c++20 schritt.cpp -o schritt
// Kein Gleitkommatyp, keine Fremdbibliothek, keine Eingabe, keine Argumente.

#include <chrono>
#include <cstdint>
#include <cstdio>

namespace {

constexpr int FELDER = 64;
constexpr int SCHRITTE = 1000000;
constexpr std::int64_t OBERGRENZE = 1000000000000LL;
constexpr std::int64_t UNTERGRENZE = 0;

// a * b / c mit 128 Bit im Zwischenergebnis, gerundet auf halbe Betraege von null weg.
inline std::int64_t mal_geteilt(std::int64_t a, std::int64_t b, std::int64_t c) {
    __int128 zaehler = static_cast<__int128>(a) * static_cast<__int128>(b);
    __int128 nenner = static_cast<__int128>(c);
    bool negativ = (zaehler < 0) != (nenner < 0);
    __int128 betrag_zaehler = zaehler < 0 ? -zaehler : zaehler;
    __int128 betrag_nenner = nenner < 0 ? -nenner : nenner;
    __int128 quotient = betrag_zaehler / betrag_nenner;
    __int128 rest = betrag_zaehler % betrag_nenner;
    if (rest * 2 >= betrag_nenner) {
        quotient += 1;
    }
    return static_cast<std::int64_t>(negativ ? -quotient : quotient);
}

inline std::int64_t klemme(std::int64_t x, std::int64_t unten, std::int64_t oben) {
    if (x < unten) return unten;
    if (x > oben) return oben;
    return x;
}

} // namespace

int main() {
    std::int64_t z[FELDER];
    for (int i = 0; i < FELDER; ++i) {
        z[i] = 1000000LL + static_cast<std::int64_t>(i) * 37LL;
    }

    auto beginn = std::chrono::steady_clock::now();
    for (int schritt = 0; schritt < SCHRITTE; ++schritt) {
        for (int i = 0; i < FELDER; ++i) {
            std::int64_t nachbar = z[(i + 17) % FELDER];
            std::int64_t roh = mal_geteilt(z[i], 10000LL + (nachbar % 977LL), 10000LL);
            z[i] = klemme(roh + (nachbar / 1024LL) - (z[i] / 4096LL), UNTERGRENZE, OBERGRENZE);
        }
    }
    auto ende = std::chrono::steady_clock::now();

    // Summe mit Ueberlaufumbruch, danach modulo 2^63 - 1.
    std::uint64_t summe = 0;
    for (int i = 0; i < FELDER; ++i) {
        summe += static_cast<std::uint64_t>(z[i]) * static_cast<std::uint64_t>(i + 1);
    }
    std::uint64_t pruefsumme = summe % ((1ULL << 63) - 1ULL);

    std::int64_t nanosekunden =
        std::chrono::duration_cast<std::chrono::nanoseconds>(ende - beginn).count();
    std::int64_t je_schritt = nanosekunden / SCHRITTE;

    std::printf("pruefsumme=%llu\n", static_cast<unsigned long long>(pruefsumme));
    std::printf("nanosekunden_je_schritt=%lld\n", static_cast<long long>(je_schritt));
    std::printf("zustand0=%lld\n", static_cast<long long>(z[0]));
    return 0;
}
