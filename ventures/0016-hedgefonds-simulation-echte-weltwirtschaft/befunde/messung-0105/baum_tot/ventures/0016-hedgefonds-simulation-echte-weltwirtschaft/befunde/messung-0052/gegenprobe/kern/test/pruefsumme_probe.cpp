//! Laufende Probe fuer `kern::pruefsumme`.
//!
//! Die Zahlenwerte sind schon in `src/pruefsumme.cpp` als `static_assert` belegt und
//! damit beim Uebersetzen geprueft. Diese Probe gibt es fuer drei Dinge, die ein
//! `static_assert` nicht kann:
//!
//!   1. **Das Testprofil aus ADR 0011, Massnahme 2.** Die Probe linkt `kern_geprueft`,
//!      also dieselben Quellen mit `-fsanitize=undefined,address`. Damit die
//!      Sanitizer ueberhaupt etwas zu sehen bekommen, laufen alle Oktette hier ueber
//!      `undurchsichtig()` -- sonst faltet der Uebersetzer die `constexpr`-Aufrufe weg
//!      und misst seine eigene Konstantenrechnung statt des Programms.
//!   2. **Den Beleg, dass Laufzeit und Uebersetzungszeit dasselbe rechnen.** Das sind
//!      zwei verschiedene Rechenwerke des Uebersetzers; dass sie uebereinstimmen, ist
//!      die Vorbedingung dafuer, dass die Summe als Waehrung der Regressionstests
//!      taugt.
//!   3. **Die Zahlen im Wortlaut.** Die Probe schreibt die gerechneten Summen
//!      hexadezimal auf die Ausgabe. Wer den Testvektor in der Quelle nachschlaegt,
//!      vergleicht damit Zeichen fuer Zeichen gegen etwas, das dieses Programm
//!      wirklich ausgerechnet hat -- und nicht gegen eine Zeile Programmtext.
//!
//! Abbruchpfade gibt es hier keine zu pruefen: Dieses Modul hat keine. Der Grund
//! steht im Kopf von `pruefsumme.hpp` -- der Umbruch `mod 2**64` ist die
//! Rechenvorschrift und kein Fehlerfall, und die Zerlegung eines `i64` in acht Bytes
//! hat keine unzulaessige Eingabe.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string_view>

#include "kern/pruefsumme.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::pruefsumme::fnv1a64;
using kern::pruefsumme::fnv1a64_text;
using kern::pruefsumme::i64;
using kern::pruefsumme::nach_bytes_le;
using kern::pruefsumme::Summe;
using kern::pruefsumme::u64;

int fehlgeschlagen = 0;

/// Nimmt dem Uebersetzer die Konstantenfaltung. `volatile` zwingt ihn, den Wert
/// wirklich zu schreiben und zu lesen -- erst dadurch rechnet das Programm zur
/// Laufzeit, und erst dann sehen die Sanitizer die Rechnung.
std::uint8_t undurchsichtig(std::uint8_t oktett)
{
    volatile std::uint8_t zwischenlager = oktett;
    return zwischenlager;
}

i64 undurchsichtig_i64(i64 zahl)
{
    volatile i64 zwischenlager = zahl;
    return zwischenlager;
}

/// Eine Kopie des Feldes, Oktett fuer Oktett durch `undurchsichtig` gezogen. Das
/// Ergebnis ist dasselbe Feld, aber der Uebersetzer kennt seinen Inhalt nicht mehr --
/// die Summe darueber muss er ausrechnen lassen.
template <std::size_t N>
std::array<std::uint8_t, N> verschleiert(const std::array<std::uint8_t, N>& quelle)
{
    std::array<std::uint8_t, N> ziel{};
    for (std::size_t i = 0; i < N; ++i) {
        ziel[i] = undurchsichtig(quelle[i]);
    }
    return ziel;
}

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// Prueft eine Bytefolge gegen ihren veroeffentlichten Erwartungswert und schreibt
/// beide Zahlen hin. Die Ausgabe ist der eigentliche Zweck: Sie macht aus dem
/// Vergleich etwas, das ein Mensch gegen die Quelle halten kann.
template <std::size_t N>
void pruefe_vektor(const char* name, const std::array<std::uint8_t, N>& oktette,
                   u64 erwartet, int zeile)
{
    const std::array<std::uint8_t, N> eingabe = verschleiert(oktette);
    const u64 gerechnet = fnv1a64(eingabe);

    std::fprintf(stdout, "  %-26s -> %016llx  (erwartet %016llx)\n", name,
                 static_cast<unsigned long long>(gerechnet),
                 static_cast<unsigned long long>(erwartet));
    pruefe(gerechnet == erwartet, name, zeile);
}

/// Acht Bytes hexadezimal, damit die Zerlegung aus Abnahme 3 nicht nur behauptet,
/// sondern gezeigt ist.
template <std::size_t N>
void schreibe_bytes(const char* name, const std::array<std::uint8_t, N>& bytes)
{
    std::fprintf(stdout, "  %-26s ->", name);
    for (const std::uint8_t oktett : bytes) {
        std::fprintf(stdout, " %02x", static_cast<unsigned int>(oktett));
    }
    std::fprintf(stdout, "\n");
}

// --- Die veroeffentlichten Vektoren, wortgleich mit `src/pruefsumme.cpp` -----------
//
// Quellen und die Unterscheidung der beiden Makrosorten `TEST` / `TEST0` stehen dort
// im Kopf. Hier stehen die Oktette, weil diese Probe ueber Bytes geht.

constexpr std::array<std::uint8_t, 0> LEER = {};
constexpr std::array<std::uint8_t, 1> A_ALLEIN = {0x61};
constexpr std::array<std::uint8_t, 1> NUL_ALLEIN = {0x00};
constexpr std::array<std::uint8_t, 2> A_DANN_NUL = {0x61, 0x00};
constexpr std::array<std::uint8_t, 2> NUL_DANN_A = {0x00, 0x61};
constexpr std::array<std::uint8_t, 6> FOOBAR = {0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72};

constexpr std::array<std::uint8_t, 8> NULLSUMME_VORWAERTS =
    {0xd5, 0x6b, 0xb9, 0x53, 0x42, 0x87, 0x08, 0x36};
constexpr std::array<std::uint8_t, 8> NULLSUMME_RUECKWAERTS =
    {0x36, 0x08, 0x87, 0x42, 0x53, 0xb9, 0x6b, 0xd5};

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)
#define PRUEFE_VEKTOR(name, oktette, erwartet) \
    pruefe_vektor((name), (oktette), (erwartet), __LINE__)

int main()
{
    // --- Die veroeffentlichten Testvektoren, zur Laufzeit (Abnahme 1) -------------
    std::fprintf(stdout, "veroeffentlichte Testvektoren [TESTVEK], [FNV]:\n");

    PRUEFE_VEKTOR("leere Eingabe", LEER, 0xcbf29ce484222325ULL);
    PRUEFE_VEKTOR("61 ('a')", A_ALLEIN, 0xaf63dc4c8601ec8cULL);
    PRUEFE_VEKTOR("00", NUL_ALLEIN, 0xaf63bd4c8601b7dfULL);
    PRUEFE_VEKTOR("61 00", A_DANN_NUL, 0x089be207b544f1e4ULL);
    PRUEFE_VEKTOR("66 6f 6f 62 61 72", FOOBAR, 0x85944171f73967e8ULL);
    PRUEFE_VEKTOR("d5 6b b9 53 42 87 08 36", NULLSUMME_VORWAERTS, 0ULL);

    // Der Textweg daneben, damit auch er zur Laufzeit gegen die Quelle steht. Die
    // Praefixkette f -> fo -> foo -> foob -> fooba -> foobar belegt den Uebergang von
    // einem Stand zum naechsten und trifft nur, wenn erst verodert und dann
    // multipliziert wird ([RFC 9923] Abschnitt 2).
    //
    // Der Text wird aus verschleierten Oktetten aufgebaut statt aus einer
    // Zeichenkette im Programmtext -- sonst rechnete der Uebersetzer die sechs Werte
    // aus und die Probe belegte nichts, was `src/pruefsumme.cpp` nicht schon belegt.
    {
        const std::array<std::uint8_t, 6> oktette = verschleiert(FOOBAR);
        std::array<char, 6> puffer{};
        for (std::size_t i = 0; i < puffer.size(); ++i) {
            puffer[i] = static_cast<char>(oktette[i]);
        }
        const std::string_view ganz(puffer.data(), puffer.size());

        PRUEFE(fnv1a64_text(ganz.substr(0, 1)) == 0xaf63db4c8601ead9ULL);
        PRUEFE(fnv1a64_text(ganz.substr(0, 2)) == 0x08985907b541d342ULL);
        PRUEFE(fnv1a64_text(ganz.substr(0, 3)) == 0xdcb27518fed9d577ULL);
        PRUEFE(fnv1a64_text(ganz.substr(0, 4)) == 0xdd120e790c2512afULL);
        PRUEFE(fnv1a64_text(ganz.substr(0, 5)) == 0xcac165afa2fef40aULL);
        PRUEFE(fnv1a64_text(ganz.substr(0, 6)) == 0x85944171f73967e8ULL);

        // Text- und Byteweg sind dieselbe Rechnung, nicht zwei.
        PRUEFE(fnv1a64_text(ganz) == fnv1a64(oktette));
    }

    // --- Die Summe haengt an der Reihenfolge (Abnahme 4) --------------------------
    //
    // Dieselben Oktette, andere Reihenfolge, andere Summe -- und die zweite Zahl
    // steht jetzt ausgeschrieben auf der Ausgabe, obwohl sie nirgends veroeffentlicht
    // ist. Genau deshalb steht sie hier und nicht als `static_assert`: Ein Wert, den
    // dieses Programm selbst erzeugt hat, darf gezeigt, aber nicht als Nachweis
    // verlangt werden.
    std::fprintf(stdout, "Reihenfolge (Abnahme 4):\n");
    {
        const std::array<std::uint8_t, 2> vorwaerts = verschleiert(A_DANN_NUL);
        const std::array<std::uint8_t, 2> rueckwaerts = verschleiert(NUL_DANN_A);
        const u64 summe_vor = fnv1a64(vorwaerts);
        const u64 summe_rueck = fnv1a64(rueckwaerts);

        std::fprintf(stdout, "  %-26s -> %016llx\n  %-26s -> %016llx\n",
                     "61 00", static_cast<unsigned long long>(summe_vor),
                     "00 61", static_cast<unsigned long long>(summe_rueck));
        PRUEFE(summe_vor == 0x089be207b544f1e4ULL);
        PRUEFE(summe_vor != summe_rueck);
    }
    {
        const std::array<std::uint8_t, 8> vorwaerts = verschleiert(NULLSUMME_VORWAERTS);
        const std::array<std::uint8_t, 8> rueckwaerts = verschleiert(NULLSUMME_RUECKWAERTS);
        const u64 summe_vor = fnv1a64(vorwaerts);
        const u64 summe_rueck = fnv1a64(rueckwaerts);

        std::fprintf(stdout, "  %-26s -> %016llx\n  %-26s -> %016llx\n",
                     "d5 6b b9 53 42 87 08 36",
                     static_cast<unsigned long long>(summe_vor),
                     "36 08 87 42 53 b9 6b d5",
                     static_cast<unsigned long long>(summe_rueck));
        PRUEFE(summe_vor == 0ULL);
        PRUEFE(summe_rueck != 0ULL);
        PRUEFE(summe_vor != summe_rueck);
    }

    // Und dasselbe auf der Ebene, die Paket 0008 benutzt: zwei Felder, getauscht.
    // Ohne diese Eigenschaft waere die feste Feldreihenfolge aus T12 eine
    // Verabredung ohne Wirkung.
    {
        Summe eins;
        eins.nimm_i64(undurchsichtig_i64(1));
        eins.nimm_i64(undurchsichtig_i64(2));

        Summe zwei;
        zwei.nimm_i64(undurchsichtig_i64(2));
        zwei.nimm_i64(undurchsichtig_i64(1));

        PRUEFE(eins.wert() != zwei.wert());
    }

    // --- Little-Endian ohne Speicherzugriff (Abnahme 3) ---------------------------
    std::fprintf(stdout, "Zerlegung in acht Bytes (Abnahme 3):\n");
    {
        const std::array<std::uint8_t, 8> eins = nach_bytes_le(undurchsichtig_i64(1));
        const std::array<std::uint8_t, 8> minus_eins = nach_bytes_le(undurchsichtig_i64(-1));
        const std::array<std::uint8_t, 8> gemischt =
            nach_bytes_le(undurchsichtig_i64(0x0102030405060708));

        schreibe_bytes("1", eins);
        schreibe_bytes("-1", minus_eins);
        schreibe_bytes("0x0102030405060708", gemischt);

        PRUEFE(eins == (std::array<std::uint8_t, 8>{0x01, 0, 0, 0, 0, 0, 0, 0}));
        PRUEFE(minus_eins == (std::array<std::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF,
                                                          0xFF, 0xFF, 0xFF, 0xFF}));
        PRUEFE(gemischt == (std::array<std::uint8_t, 8>{0x08, 0x07, 0x06, 0x05,
                                                        0x04, 0x03, 0x02, 0x01}));
    }

    // Die Raender von i64 -- die Stelle, an der ein Sanitizer am ehesten anschlaegt.
    {
        constexpr i64 I64_MAX = 9'223'372'036'854'775'807;
        constexpr i64 I64_MIN = -I64_MAX - 1;

        const std::array<std::uint8_t, 8> gross = nach_bytes_le(undurchsichtig_i64(I64_MAX));
        const std::array<std::uint8_t, 8> klein = nach_bytes_le(undurchsichtig_i64(I64_MIN));

        schreibe_bytes("I64_MAX", gross);
        schreibe_bytes("I64_MIN", klein);

        PRUEFE(gross == (std::array<std::uint8_t, 8>{0xFF, 0xFF, 0xFF, 0xFF,
                                                     0xFF, 0xFF, 0xFF, 0x7F}));
        PRUEFE(klein == (std::array<std::uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0x80}));
    }

    // --- Laufzeit und Uebersetzungszeit rechnen dasselbe --------------------------
    //
    // Links steht ein Wert, den der Uebersetzer ausgerechnet hat, rechts einer, den
    // das Programm ausgerechnet hat.
    {
        constexpr u64 beim_uebersetzen = fnv1a64(FOOBAR);
        const std::array<std::uint8_t, 6> zur_laufzeit = verschleiert(FOOBAR);
        PRUEFE(beim_uebersetzen == fnv1a64(zur_laufzeit));
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::pruefsumme -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::pruefsumme -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
