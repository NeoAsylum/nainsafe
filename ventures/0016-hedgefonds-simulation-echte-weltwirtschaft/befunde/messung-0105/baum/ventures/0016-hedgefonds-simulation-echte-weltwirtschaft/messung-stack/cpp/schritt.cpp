// Deterministischer Festkomma-Weltschritt, Stackmessung 0016.
// Uebersetzung: g++ -O2 -std=c++20 schritt.cpp
// Keine Fremdbibliothek, kein Gleitkommatyp, auch nicht in der Zeitmessung.

#include <array>
#include <chrono>
#include <cinttypes>
#include <cstdint>
#include <cstdio>

namespace {

constexpr int kBreite = 64;
constexpr int kSchritte = 1000000;
constexpr std::int64_t kUntergrenze = -1000000000000LL;
constexpr std::int64_t kObergrenze = 1000000000000LL;
constexpr std::int64_t kModul = 9223372036854775807LL;  // 2^63 - 1

// a * b / c mit 128-Bit-Zwischenwert, gerundet auf halbe Betraege von null weg.
std::int64_t mal_geteilt(std::int64_t a, std::int64_t b, std::int64_t c) {
    const __int128 zaehler = static_cast<__int128>(a) * static_cast<__int128>(b);
    const __int128 nenner = static_cast<__int128>(c);
    __int128 q = zaehler / nenner;         // schneidet gegen null ab
    const __int128 r = zaehler % nenner;   // traegt das Vorzeichen des Zaehlers
    const __int128 rest_betrag = r < 0 ? -r : r;
    const __int128 nenner_betrag = nenner < 0 ? -nenner : nenner;
    // Genau die Haelfte zaehlt noch als "weg von null", darum >= und nicht >.
    if (rest_betrag * 2 >= nenner_betrag) {
        q += ((zaehler < 0) != (nenner < 0)) ? -1 : 1;
    }
    return static_cast<std::int64_t>(q);
}

std::int64_t klemme(std::int64_t x, std::int64_t unten, std::int64_t oben) {
    if (x < unten) return unten;
    if (x > oben) return oben;
    return x;
}

// Ein Weltschritt, i aufsteigend, in-place: ab i = 47 liest der Nachbargriff
// bereits fortgeschriebene Werte desselben Schritts.
void weltschritt(std::array<std::int64_t, kBreite>& z) {
    for (int i = 0; i < kBreite; ++i) {
        const std::int64_t nachbar = z[(i + 17) % kBreite];
        const std::int64_t alt = z[i];
        const std::int64_t roh = mal_geteilt(alt, 9512 + nachbar % 977, 10000);
        z[i] = klemme(roh + nachbar / 1024 - alt / 4096, kUntergrenze, kObergrenze);
    }
}

// summe(z[i] * (i + 1)) mit Ueberlaufumbruch, danach mod 2^63 - 1.
std::int64_t pruefsumme(const std::array<std::int64_t, kBreite>& z) {
    std::uint64_t summe = 0;
    for (int i = 0; i < kBreite; ++i) {
        summe += static_cast<std::uint64_t>(z[i]) *
                 static_cast<std::uint64_t>(static_cast<std::int64_t>(i) + 1);
    }
    return static_cast<std::int64_t>(summe) % kModul;
}

}  // namespace

int main() {
    std::array<std::int64_t, kBreite> z{};
    for (int i = 0; i < kBreite; ++i) {
        z[i] = 1000000 + static_cast<std::int64_t>(i) * 37;
    }

    const auto beginn = std::chrono::steady_clock::now();
    for (int s = 0; s < kSchritte; ++s) {
        weltschritt(z);
    }
    const auto ende = std::chrono::steady_clock::now();

    const std::int64_t nanosekunden =
        std::chrono::duration_cast<std::chrono::nanoseconds>(ende - beginn).count();

    std::printf("pruefsumme=%" PRId64 "\n", pruefsumme(z));
    std::printf("nanosekunden_je_schritt=%" PRId64 "\n", nanosekunden / kSchritte);
    std::printf("zustand0=%" PRId64 "\n", z[0]);
    return 0;
}
