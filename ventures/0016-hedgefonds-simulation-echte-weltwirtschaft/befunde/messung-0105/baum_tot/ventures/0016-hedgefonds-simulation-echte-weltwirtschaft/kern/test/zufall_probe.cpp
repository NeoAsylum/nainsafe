//! Laufende Probe fuer `kern::zufall`.
//!
//! Die Zahlenwerte sind schon in `src/zufall.cpp` als `static_assert` belegt und damit
//! beim Uebersetzen geprueft. Diese Probe gibt es fuer vier Dinge, die ein
//! `static_assert` nicht kann:
//!
//!   1. **Das Testprofil aus ADR 0011, Massnahme 2.** Die Probe linkt `kern_geprueft`,
//!      also dieselben Quellen mit `-fsanitize=undefined,address`. Damit die Sanitizer
//!      ueberhaupt etwas zu sehen bekommen, laufen alle Eingaben hier ueber
//!      `undurchsichtig()` -- sonst faltet der Uebersetzer die `constexpr`-Aufrufe weg
//!      und misst seine eigene Konstantenrechnung statt des Programms. Fuer diesen
//!      Kern zaehlt das doppelt: Er ist voller Verschiebungen und Umbrueche, also
//!      genau der Sorte Rechnung, bei der ein Sanitizer anschlaegt, wenn eine Weite
//!      oder ein Typ danebenliegt.
//!   2. **Den Beleg, dass Laufzeit und Uebersetzungszeit dasselbe rechnen.** Das sind
//!      zwei verschiedene Rechenwerke des Uebersetzers; dass sie uebereinstimmen, ist
//!      die Vorbedingung dafuer, dass eine gespeicherte Partie beim Laden dieselben
//!      Zahlen ergibt wie beim Spielen.
//!   3. **Die Zahlen im Wortlaut** (Abnahme 4). Die Ableitungseigenschaften sind in
//!      `src/zufall.cpp` als Beziehungen geprueft -- gleich, verschieden, unabhaengig.
//!      Hier stehen die Stroeme, um die es dabei geht, mit allen vier Worten
//!      hexadezimal auf der Ausgabe. Wer wissen will, ob der Strom zu `index = 7`
//!      wirklich derselbe ist, liest zwei Zeilen und vergleicht sie, statt einer
//!      Zusicherung zu glauben.
//!   4. **Den Abbruchpfad.** `in_bereich` mit der Grenze null wirft; ein
//!      `static_assert` koennte das nur als „ist keine Konstante" bemerken, eine
//!      laufende Probe faengt den Wurf und weist ihn nach.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

#include "kern/zufall.hpp"

#include "kern/sperre.hpp"   // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::zufall::einruehren;
using kern::zufall::i64;
using kern::zufall::in_bereich;
using kern::zufall::splitmix64;
using kern::zufall::splitmix64_naechster;
using kern::zufall::Strom;
using kern::zufall::strom_aus_keim;
using kern::zufall::STROM_WORTE;
using kern::zufall::u64;
using kern::zufall::Zweck;

int fehlgeschlagen = 0;

/// Nimmt dem Uebersetzer die Konstantenfaltung. `volatile` zwingt ihn, den Wert
/// wirklich zu schreiben und zu lesen -- erst dadurch rechnet das Programm zur
/// Laufzeit, und erst dann sehen die Sanitizer die Rechnung.
u64 undurchsichtig(u64 wert)
{
    volatile u64 zwischenlager = wert;
    return zwischenlager;
}

i64 undurchsichtig_i64(i64 wert)
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

/// Eine Zahl hexadezimal, sechzehn Stellen.
void schreibe_wert(const char* name, u64 wert)
{
    std::fprintf(stdout, "  %-34s -> %016llx\n", name, static_cast<unsigned long long>(wert));
}

/// Eine gerechnete Zahl neben ihrem veroeffentlichten Erwartungswert. Die Ausgabe ist
/// der eigentliche Zweck: Sie macht aus dem Vergleich etwas, das ein Mensch gegen die
/// Quelle halten kann.
void schreibe_gegen_quelle(const char* name, u64 gerechnet, u64 erwartet)
{
    std::fprintf(stdout, "  %-34s -> %016llx  (erwartet %016llx)\n", name,
                 static_cast<unsigned long long>(gerechnet),
                 static_cast<unsigned long long>(erwartet));
}

/// Alle vier Worte eines Stroms. Der Vergleich zweier Stroeme laeuft ueber den ganzen
/// Zustand und nicht ueber die naechste Ausgabe -- also muss auch die Ausgabe ihn
/// ganz zeigen.
void schreibe_strom(const char* name, const Strom& strom)
{
    const std::array<u64, STROM_WORTE> worte = strom.worte();
    std::fprintf(stdout, "  %-34s ->", name);
    for (const u64 wort : worte) {
        std::fprintf(stdout, " %016llx", static_cast<unsigned long long>(wort));
    }
    std::fprintf(stdout, "\n");
}

// --- Der Bezugsaufruf, wortgleich mit `src/zufall.cpp` -----------------------------

constexpr u64 WURZEL = 0x0123456789abcdefULL;
constexpr i64 JAHRGANG = 1997;
constexpr u64 PARAMETERSUMME = 0xcbf29ce484222325ULL;
constexpr i64 RUNDE = 12;

/// Der Bezugsaufruf mit undurchsichtigen Argumenten -- damit die Ableitung wirklich
/// zur Laufzeit gerechnet wird und nicht der Uebersetzer sie schon erledigt hat.
Strom leite_ab(Zweck zweck, i64 index)
{
    return splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(JAHRGANG),
                      undurchsichtig(PARAMETERSUMME), zweck, undurchsichtig_i64(RUNDE),
                      undurchsichtig_i64(index));
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)

int main()
{
    // --- Die veroeffentlichten Vektoren, zur Laufzeit ------------------------------
    //
    // [XOSHIRO-RS], Testblock `reference`: die ersten sechs Ausgaben zum Startwert
    // 1477776061723855037. Sie belegen SplitMix64 fuer sich.
    std::fprintf(stdout, "SplitMix64 gegen [XOSHIRO-RS], Startwert 1477776061723855037:\n");
    {
        const std::array<u64, 6> erwartet = {1985237415132408290ULL,
                                             2979275885539914483ULL,
                                             13511426838097143398ULL,
                                             8488337342461049707ULL,
                                             15141737807933549159ULL,
                                             17093170987380407015ULL};

        u64 stand = undurchsichtig(1477776061723855037ULL);
        for (std::size_t i = 0; i < erwartet.size(); ++i) {
            const u64 gerechnet = splitmix64_naechster(stand);
            schreibe_gegen_quelle("Ausgabe", gerechnet, erwartet[i]);
            pruefe(gerechnet == erwartet[i], "[XOSHIRO-RS] Referenzwert", __LINE__);
        }
    }

    // [XOSHIRO-CPP]: Saatregel und Schrittregel in einem Stueck.
    std::fprintf(stdout, "xoshiro256** gegen [XOSHIRO-CPP], Keim 100:\n");
    {
        const std::array<u64, 4> erwartet = {792317387143481937ULL,
                                             1418856489092323125ULL,
                                             6662743737787356053ULL,
                                             9823178768685107703ULL};

        Strom strom{strom_aus_keim(undurchsichtig(100ULL))};
        schreibe_strom("Zustand nach der Saat", strom);
        for (std::size_t i = 0; i < erwartet.size(); ++i) {
            const u64 gerechnet = strom.naechster();
            schreibe_gegen_quelle("Ausgabe", gerechnet, erwartet[i]);
            pruefe(gerechnet == erwartet[i], "[XOSHIRO-CPP] Referenzwert", __LINE__);
        }
    }

    // Laufzeit und Uebersetzungszeit rechnen dasselbe: links ein Wert, den der
    // Uebersetzer ausgerechnet hat, rechts einer, den das Programm ausgerechnet hat.
    {
        constexpr Strom beim_uebersetzen = strom_aus_keim(100ULL);
        const Strom zur_laufzeit = strom_aus_keim(undurchsichtig(100ULL));
        PRUEFE(beim_uebersetzen.worte() == zur_laufzeit.worte());
    }

    // `einruehren(stand, 0)` ist genau ein Schritt des Referenzerzeugers -- die Naht
    // zwischen dem geprueften Verfahren und der Ableitung.
    {
        u64 stand = undurchsichtig(1477776061723855037ULL);
        const u64 ueber_schritt = splitmix64_naechster(stand);
        const u64 ueber_einruehren = einruehren(undurchsichtig(1477776061723855037ULL), 0ULL);
        schreibe_wert("ein Schritt", ueber_schritt);
        schreibe_wert("einruehren(stand, 0)", ueber_einruehren);
        PRUEFE(ueber_schritt == ueber_einruehren);
    }

    // --- Abgeleitet, nicht fortgeschrieben (Abnahme 4) ----------------------------
    //
    // Ab hier stehen die Zahlen im Wortlaut. Erwartungswerte sind es nicht -- sie
    // stammen aus diesem Programm --, sondern die Werte, zwischen denen die drei
    // Beziehungen behauptet werden. Wer sie vergleicht, prueft die Behauptung selbst.

    std::fprintf(stdout, "gleiche sechs Zahlen -> gleicher Strom (Abnahme 4):\n");
    {
        const Strom einmal = leite_ab(Zweck::ZUFALLSBOT, 7);
        const Strom nochmal = leite_ab(Zweck::ZUFALLSBOT, 7);
        schreibe_strom("index = 7, erster Aufruf", einmal);
        schreibe_strom("index = 7, zweiter Aufruf", nochmal);
        PRUEFE(einmal.worte() == nochmal.worte());
    }

    std::fprintf(stdout, "index + 1 -> anderer Strom (Abnahme 4):\n");
    {
        const Strom sieben = leite_ab(Zweck::ZUFALLSBOT, 7);
        const Strom acht = leite_ab(Zweck::ZUFALLSBOT, 8);
        schreibe_strom("index = 7", sieben);
        schreibe_strom("index = 8", acht);
        PRUEFE(sieben.worte() != acht.worte());
    }

    // Der eigentliche Punkt: Zwischen den beiden Ableitungen zu `index = 7` wird zu
    // `index = 1 … 6` gezogen, und zwar unterschiedlich oft -- 21 Ziehungen. Ein Modul
    // mit einer gemerkten Ablage stuende hier mit zwei verschiedenen Zeilen da.
    std::fprintf(stdout, "index = 7 vor und nach 21 Ziehungen zu index = 1 … 6 (Abnahme 4):\n");
    {
        const Strom vorher = leite_ab(Zweck::BUENDELZIEHUNG, 7);
        schreibe_strom("index = 7, vorher", vorher);

        u64 verbraucht = 0;
        for (i64 lauf = 1; lauf <= 6; ++lauf) {
            Strom dazwischen = leite_ab(Zweck::BUENDELZIEHUNG, lauf);
            for (i64 zug = 0; zug < lauf; ++zug) {
                (void)dazwischen.naechster();
                ++verbraucht;
            }
        }
        std::fprintf(stdout, "  %-34s -> %llu\n", "Ziehungen dazwischen",
                     static_cast<unsigned long long>(verbraucht));

        const Strom nachher = leite_ab(Zweck::BUENDELZIEHUNG, 7);
        schreibe_strom("index = 7, nachher", nachher);
        PRUEFE(verbraucht == 21);
        PRUEFE(vorher.worte() == nachher.worte());
    }

    // Und dieselbe Sache von der anderen Seite: die Ableitungsreihenfolge umgedreht.
    std::fprintf(stdout, "umgekehrte Ableitungsreihenfolge (Abnahme 4):\n");
    {
        const Strom zuerst = leite_ab(Zweck::SUCHBOT_KANDIDATEN, 7);
        Strom danach = leite_ab(Zweck::SUCHBOT_KANDIDATEN, 1);
        (void)danach.naechster();
        const Strom wieder = leite_ab(Zweck::SUCHBOT_KANDIDATEN, 7);
        schreibe_strom("index = 7, zuerst abgeleitet", zuerst);
        schreibe_strom("index = 7, zuletzt abgeleitet", wieder);
        PRUEFE(zuerst.worte() == wieder.worte());
    }

    // --- Jede der sechs Zahlen kommt an -------------------------------------------
    std::fprintf(stdout, "jede der sechs Zahlen aendert den Strom:\n");
    {
        const Strom bezug = leite_ab(Zweck::ZUFALLSBOT, 7);
        schreibe_strom("Bezugsaufruf", bezug);

        const Strom andere_wurzel =
            splitmix64(undurchsichtig(WURZEL + 1), undurchsichtig_i64(JAHRGANG),
                       undurchsichtig(PARAMETERSUMME), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(RUNDE), undurchsichtig_i64(7));
        const Strom anderer_jahrgang =
            splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(JAHRGANG + 1),
                       undurchsichtig(PARAMETERSUMME), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(RUNDE), undurchsichtig_i64(7));
        const Strom andere_summe =
            splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(JAHRGANG),
                       undurchsichtig(PARAMETERSUMME + 1), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(RUNDE), undurchsichtig_i64(7));
        const Strom anderer_zweck = leite_ab(Zweck::BUENDELZIEHUNG, 7);
        const Strom andere_runde =
            splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(JAHRGANG),
                       undurchsichtig(PARAMETERSUMME), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(RUNDE + 1), undurchsichtig_i64(7));
        const Strom anderer_index = leite_ab(Zweck::ZUFALLSBOT, 6);

        schreibe_strom("wurzelstartwert + 1", andere_wurzel);
        schreibe_strom("jahrgang_id + 1", anderer_jahrgang);
        schreibe_strom("parameter_pruefsumme + 1", andere_summe);
        schreibe_strom("zweck_id = BUENDELZIEHUNG", anderer_zweck);
        schreibe_strom("runde + 1", andere_runde);
        schreibe_strom("index - 1", anderer_index);

        // **Paarweise, nicht nur gegen den Bezugsaufruf.** An dieser Stelle stand in
        // der ersten Fassung ein echter Fehler: „wurzelstartwert + 1" und
        // „jahrgang_id + 1" waren Wort fuer Wort derselbe Strom, weil beide Zahlen in
        // dieselbe Summe liefen. Vom Bezugsaufruf waren beide verschieden -- der
        // Vergleich gegen den Bezugsaufruf allein haette den Fehler durchgelassen.
        const std::array<std::array<u64, STROM_WORTE>, 7> stroeme = {
            bezug.worte(),      andere_wurzel.worte(), anderer_jahrgang.worte(),
            andere_summe.worte(), anderer_zweck.worte(), andere_runde.worte(),
            anderer_index.worte()};

        for (std::size_t a = 0; a < stroeme.size(); ++a) {
            for (std::size_t b = a + 1; b < stroeme.size(); ++b) {
                pruefe(stroeme[a] != stroeme[b], "sieben paarweise verschiedene Stroeme",
                       __LINE__);
            }
        }
    }

    // Negative Jahrgangs-, Runden- und Indexwerte gehoeren nicht zum Spiel, sind aber
    // der Rand des Wertebereichs -- und die Stelle, an der eine Umdeutung nach `u64`
    // schiefgehen koennte. Der Sanitizer sieht hier zu.
    {
        const Strom minus_eins =
            splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(-1),
                       undurchsichtig(PARAMETERSUMME), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(-1), undurchsichtig_i64(-1));
        const Strom rand =
            splitmix64(undurchsichtig(WURZEL), undurchsichtig_i64(-9'223'372'036'854'775'807 - 1),
                       undurchsichtig(PARAMETERSUMME), Zweck::ZUFALLSBOT,
                       undurchsichtig_i64(9'223'372'036'854'775'807), undurchsichtig_i64(0));
        schreibe_strom("jahrgang/runde/index = -1", minus_eins);
        schreibe_strom("i64-Raender", rand);
        PRUEFE(minus_eins.worte() != rand.worte());
    }

    // --- Eine Zahl in einem Bereich, ganzzahlig -----------------------------------
    std::fprintf(stdout, "in_bereich (T4, T35):\n");
    {
        Strom strom = leite_ab(Zweck::BUENDELZIEHUNG, 1);

        // T35 zieht die Buendelgroesse als `naechster(s) mod 4`. Tausend Ziehungen,
        // und keine darf aus dem Bereich fallen; nebenbei muessen alle vier Werte
        // wirklich vorkommen -- eine Restrechnung, die immer null liefert, waere im
        // Bereich und trotzdem falsch.
        std::array<int, 4> gezaehlt{};
        bool im_bereich = true;
        for (int zug = 0; zug < 1000; ++zug) {
            const u64 wert = in_bereich(strom, undurchsichtig(4ULL));
            if (wert >= 4) {
                im_bereich = false;
            } else {
                ++gezaehlt[static_cast<std::size_t>(wert)];
            }
        }
        std::fprintf(stdout, "  %-34s -> %d %d %d %d\n", "mod 4, 1000 Ziehungen",
                     gezaehlt[0], gezaehlt[1], gezaehlt[2], gezaehlt[3]);
        PRUEFE(im_bereich);
        PRUEFE(gezaehlt[0] > 0 && gezaehlt[1] > 0 && gezaehlt[2] > 0 && gezaehlt[3] > 0);

        // Die Grenze eins hat genau ein Element, und das ist die null.
        PRUEFE(in_bereich(strom, undurchsichtig(1ULL)) == 0);
    }

    // --- Der Abbruchpfad ----------------------------------------------------------
    //
    // Die Grenze null ist eine Ziehung aus einer leeren Menge. Sie muss werfen und
    // darf keinen Ersatzwert liefern -- ein Ersatzwert waere eine Zahl, die keine
    // Pruefung bemerkt.
    {
        Strom strom = leite_ab(Zweck::BUENDELZIEHUNG, 2);
        bool geworfen = false;
        try {
            (void)in_bereich(strom, undurchsichtig(0ULL));
        } catch (const std::domain_error&) {
            geworfen = true;
        }
        std::fprintf(stdout, "  %-34s -> %s\n", "in_bereich(strom, 0)",
                     geworfen ? "Abbruch, wie verlangt" : "KEIN Abbruch");
        PRUEFE(geworfen);
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::zufall -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::zufall -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
