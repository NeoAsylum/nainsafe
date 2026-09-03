//! Paket 0029 -- die Probe zum **Vorratsverfahren und seiner Invariante** (T43).
//!
//! Vorgaben: T43 (Vorratsverfahren, Invariante fuer `k = 1` **und** `k = 3`), T30
//! Pruefung 1, T4 (kein Gleitkomma), T13 (Kasten `pruefstand`); `spiel.md`, Abschnitt
//! "Das Aktionsprofil und wie es auf Aktionen wirkt", ist der Wortlaut. ADR 0011 fuer
//! die Sprache.
//!
//! ## Was hier ausdruecklich NICHT geprueft wird
//!
//! Die Zulaessigkeitsliste aus T32. Welche der fuenf Arten in einer Runde zur Wahl
//! stehen, ist ein **Eingabewert** dieser Probe und keine Rechnung -- wer sie hier
//! erfaende, baute T32 ein zweites Mal und falsch. Ebenso wenig: die Bots, die drei
//! Masse, die Fensterlogik von Mass 3, und die Profilliste selbst (Paket 0019,
//! `vorrat_probe`). Die 126 Profile werden hier **geholt**, nicht erzeugt.
//!
//! ## Die vier Pruefungen und wie sie zusammenhaengen
//!
//!   1 **Die Invariante, fuer alle 126 Profile, `k = 1` und `k = 3` einzeln.** Bei
//!     durchgehend zulaessigen fuenf Arten steht der Vorratsvektor nach `5k` Runden
//!     wieder auf `(0,0,0,0,0)`, Art `i` hat genau `3k*ai` der `15k` Steckplaetze,
//!     und kein Steckplatz ist leer geblieben. Beide `k` einzeln, weil genau ihre
//!     Verwechslung dreimal Befund war (T43, letzter Punkt).
//!   2 **Die Probe des Referenzprofils, zeichengleich.** `(1,1,1,1,1)` vergibt in den
//!     Runden 1 bis 5 die Arten `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`. Dieser
//!     Erwartungswert steht **woertlich in `spiel.md`** (Zeile 1043 f.) und stammt
//!     damit nicht aus diesem Programm. Er steht unten zweimal -- als Zeichenkette
//!     und als Tabelle --, und die Probe prueft die beiden Abschriften zuerst
//!     gegeneinander: Ein Tippfehler in einer Abschrift faellt dann auf, bevor er
//!     zum Massstab wird.
//!   3 **Die beiden absichtlich falschen Fassungen.** Sie stehen im Kopf
//!     (`Abweichung`) und sind je eine geaenderte Zeile des Verfahrens. Der Nachweis
//!     ist **doppelt**, und beide Haelften werden gebraucht:
//!       - `GLEICHSTAND_NACH_GROESSERER_KENNUNG` **besteht** Pruefung 1 -- jede Art
//!         kommt wieder `3k*ai`-mal dran -- und wird von Pruefung 2 gefangen.
//!       - `VORRAT_BEI_NULL_ABGESCHNITTEN` **besteht** Pruefung 2 -- die fuenf Runden
//!         des Referenzprofils laufen zeichengleich -- und wird von Pruefung 1
//!         gefangen.
//!     Erst beides zusammen belegt, dass die zwei Bedingungen Verschiedenes messen.
//!     Eine einzige falsche Fassung wuerde nur zeigen, dass *irgendetwas* rot wird.
//!   4 **Der leere Steckplatz und das Gegenstueck dazu.** Steht keine Art zur Wahl,
//!     bleibt der Platz `LEER`, `leer_geblieben` zaehlt ihn, und **kein Vorrat ist
//!     verrechnet**: Der Vektor ist danach Zeichen fuer Zeichen der vom Rundenanfang,
//!     und der wird hier getrennt hingeschrieben statt von der geprueften Funktion
//!     geholt. Die Gegenprobe zu "`ai = 0` verbietet die Art nicht": eine einzige
//!     zulaessige Art mit `ai = 0` bekommt alle drei Steckplaetze, obwohl eine andere
//!     Art den weit groesseren Vorrat hat.
//!
//! ## Was die Vorfuehrung von Pruefung 4 ergeben hat, und warum sie noetig war
//!
//! Pruefung 1 und 2 fuehren sich ueber `Abweichung` selbst vor. Pruefung 4 hat keinen
//! solchen Fall im Kopf, also ist sie am 2026-09-03 von Hand vorgefuehrt worden --
//! zwei Aenderungen am Modul, gebaut, gelaufen, zurueckgenommen. Was dabei herauskam,
//! steht hier, weil es die Pruefung begruendet:
//!
//!   - Verrechnet der leere Steckplatz doch Vorrat (`vi -= 5` fuer alle statt gar
//!     nichts), faellt **allein 4a** um. Pruefung 1 und 2 merken nichts: Bei
//!     durchgehender Zulaessigkeit bleibt nie ein Platz leer, der Zweig wird nie
//!     betreten.
//!   - Macht man `ai = 0` zum harten Verbot -- der Fehler, gegen den `spiel.md` den
//!     Satz ueberhaupt geschrieben hat --, faellt **allein 4b** um, mit vier
//!     Zusicherungen. **Pruefung 1 bleibt dabei fuer alle 126 Profile und beide `k`
//!     gruen**, und das ist kein Zufall: Eine Art mit `ai = 0` soll `3k*0 = 0`
//!     Steckplaetze bekommen, und genau null bekommt sie auch, wenn man sie verbietet.
//!     Die Invariante kann diesen Fehler **prinzipiell nicht** fangen. Ohne 4b waere
//!     der Satz "`ai = 0` verbietet die Art nicht" in diesem Kasten ungeprueft.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdio>
#include <stdexcept>

#include "pruefstand/vorrat.hpp"

namespace {

using pruefstand::vorrat::ARTEN;
using pruefstand::vorrat::Abweichung;
using pruefstand::vorrat::i64;
using pruefstand::vorrat::KOSTEN;
using pruefstand::vorrat::Laufergebnis;
using pruefstand::vorrat::LEER;
using pruefstand::vorrat::Profil;
using pruefstand::vorrat::Profileintrag;
using pruefstand::vorrat::Profilliste;
using pruefstand::vorrat::PROFILE;
using pruefstand::vorrat::Rundenfolge;
using pruefstand::vorrat::RUNDEN_HOECHSTENS;
using pruefstand::vorrat::STECKPLAETZE;
using pruefstand::vorrat::Vorrat;
using pruefstand::vorrat::Zulaessigkeit;
using pruefstand::vorrat::ZUWACHS;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// `long long` fuer die Formatausgabe -- `i64` ist auf dieser Plattform `long`, und
/// `-Wformat=2` will den Typ genau. Eine Stelle statt dreissig Umwandlungen im Text.
long long z(i64 wert)
{
    return static_cast<long long>(wert);
}

void schreibe_vektor(const char* rand, const std::array<i64, ARTEN>& werte)
{
    std::fprintf(stdout, "  %-26s (", rand);
    for (std::size_t i = 0; i < ARTEN; ++i) {
        std::fprintf(stdout, "%s%lld", i == 0 ? "" : ",", z(werte[i]));
    }
    std::fprintf(stdout, ")\n");
}

// ---------------------------------------------------------------------------
// Der Wortlaut aus `spiel.md`, zweimal abgeschrieben
// ---------------------------------------------------------------------------
//
// `spiel.md`, Zeile 1043 f.: "Zur Probe das Referenzprofil: Runden 1 bis 5 vergeben
// die Arten 1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5 und stehen danach wieder auf
// (0,0,0,0,0)".
//
// Zweimal, weil die beiden Abschriften einander pruefen. Die Zeichenkette ist der
// Massstab fuer "zeichengleich", die Tabelle sagt zusaetzlich, in **welcher** Runde
// eine Abweichung zuerst auffaellt -- und eine Probe, die eine Runde benennen soll,
// braucht die Zerlegung. Waere nur eine da, waere ein Tippfehler darin ein stiller
// falscher Massstab; so faellt er in Pruefung 2a auf.

constexpr const char* REFERENZFOLGE = "1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5";

constexpr std::size_t REFERENZRUNDEN = 5;

constexpr std::array<Rundenfolge, REFERENZRUNDEN> REFERENZTABELLE = {
    Rundenfolge{1, 2, 3},
    Rundenfolge{4, 5, 1},
    Rundenfolge{2, 3, 4},
    Rundenfolge{5, 1, 2},
    Rundenfolge{3, 4, 5},
};

/// Das Referenzprofil `(1,1,1,1,1)` -- `spiel.md`, Zeile 1015.
constexpr Profil REFERENZPROFIL = Profil{1, 1, 1, 1, 1};

// ---------------------------------------------------------------------------
// Pruefung 1 als Praedikat -- die Invariante ueber alle 126 Profile
// ---------------------------------------------------------------------------
//
// Als Praedikat und nicht als Folge von Zusicherungen, aus demselben Grund wie in
// `vorrat_probe`: Pruefung 3 legt **dieselbe** Funktion auf die falschen Fassungen an.
// Nur so ist nachweisbar, dass die Vorfuehrung denselben Massstab benutzt und nicht
// einen milderen.

struct Invariantenbefund {
    i64 k = 0;
    /// Wie viele der 126 Profile die Invariante erfuellen.
    i64 erfuellt = 0;
    /// Kennung des ersten Profils, an dem sie kippt. `-1` heisst: keines.
    i64 erstes_profil = -1;
    Profil erster_vektor{};
    Vorrat erster_endvorrat{};
    std::array<i64, ARTEN> erste_verteilung{};
    std::array<i64, ARTEN> erste_erwartung{};
};

Invariantenbefund pruefe_invariante(const Profilliste& liste, i64 k, Abweichung abweichung)
{
    Invariantenbefund befund;
    befund.k = k;

    const Zulaessigkeit alle = Zulaessigkeit{true, true, true, true, true};
    const i64 runden = 5 * k;

    for (const Profileintrag& eintrag : liste) {
        const Laufergebnis lauf =
            pruefstand::vorrat::spiele(eintrag.anteile, alle, runden, abweichung);

        // Die Erwartung wird hier hingeschrieben und nicht von der geprueften
        // Funktion geholt: `3k*ai` Steckplaetze je Art, Endvorrat null, nichts leer.
        std::array<i64, ARTEN> erwartung{};
        bool heil = (lauf.leer_geblieben == 0);
        for (std::size_t i = 0; i < ARTEN; ++i) {
            erwartung[i] = 3 * k * eintrag.anteile[i];
            if (lauf.gezaehlt[i] != erwartung[i] || lauf.vorrat[i] != 0) {
                heil = false;
            }
        }

        if (heil) {
            ++befund.erfuellt;
        } else if (befund.erstes_profil < 0) {
            befund.erstes_profil = eintrag.kennung;
            befund.erster_vektor = eintrag.anteile;
            befund.erster_endvorrat = lauf.vorrat;
            befund.erste_verteilung = lauf.gezaehlt;
            befund.erste_erwartung = erwartung;
        }
    }

    return befund;
}

/// Bestanden heisst: alle 126 Profile erfuellen die Invariante.
bool besteht_invariante(const Invariantenbefund& befund)
{
    return befund.erfuellt == static_cast<i64>(PROFILE) && befund.erstes_profil < 0;
}

// ---------------------------------------------------------------------------
// Pruefung 2 als Praedikat -- die Probe des Referenzprofils
// ---------------------------------------------------------------------------

struct Folgenbefund {
    /// Die gelaufene Folge in der Form aus `spiel.md`.
    std::array<char, 64> text{};
    /// Die erste Runde `1..5`, in der sie von `REFERENZTABELLE` abweicht. `-1`: keine.
    i64 erste_abweichende_runde = -1;
    /// Der Endvorrat nach den fuenf Runden.
    Vorrat endvorrat{};
    /// Steht er auf `(0,0,0,0,0)`?
    bool endvorrat_null = true;
};

/// Setzt die Folge in die Form `1,2,3 | 4,5,1 | ...` zusammen. Feste Puffergroesse
/// und Indexpruefung an jeder Grenze -- Testcode, der hinter das Feldende schreibt,
/// faelscht das Urteil, statt es zu faellen.
void setze_text(std::array<char, 64>& puffer, const Laufergebnis& lauf, i64 runden)
{
    std::size_t pos = 0;
    puffer[0] = '\0';

    for (i64 t = 0; t < runden; ++t) {
        const Rundenfolge& f = lauf.folge[static_cast<std::size_t>(t)];
        if (pos >= puffer.size()) {
            return;
        }
        const int geschrieben =
            std::snprintf(puffer.data() + pos, puffer.size() - pos, "%s%lld,%lld,%lld",
                          t == 0 ? "" : " | ", z(f[0]), z(f[1]), z(f[2]));
        if (geschrieben < 0) {
            return;
        }
        pos += static_cast<std::size_t>(geschrieben);
    }
}

Folgenbefund pruefe_referenzfolge(Abweichung abweichung)
{
    Folgenbefund befund;

    const Zulaessigkeit alle = Zulaessigkeit{true, true, true, true, true};
    const Laufergebnis lauf = pruefstand::vorrat::spiele(
        REFERENZPROFIL, alle, static_cast<i64>(REFERENZRUNDEN), abweichung);

    setze_text(befund.text, lauf, static_cast<i64>(REFERENZRUNDEN));

    for (std::size_t t = 0; t < REFERENZRUNDEN; ++t) {
        if (lauf.folge[t] != REFERENZTABELLE[t] && befund.erste_abweichende_runde < 0) {
            befund.erste_abweichende_runde = static_cast<i64>(t) + 1;
        }
    }

    befund.endvorrat = lauf.vorrat;
    for (std::size_t i = 0; i < ARTEN; ++i) {
        if (lauf.vorrat[i] != 0) {
            befund.endvorrat_null = false;
        }
    }

    return befund;
}

/// Zeichenvergleich gegen den Wortlaut. Kein `std::strcmp`, damit der Puffer auch
/// dann nicht ueberlaufen wird, wenn die Abschluss-Null einmal fehlt.
bool gleicher_text(const std::array<char, 64>& puffer, const char* soll)
{
    for (std::size_t i = 0; i < puffer.size(); ++i) {
        if (puffer[i] != soll[i]) {
            return false;
        }
        if (puffer[i] == '\0') {
            return true;
        }
    }
    return false;
}

/// Bestanden heisst: die Folge ist zeichengleich zum Wortlaut aus `spiel.md`.
/// **Der Endvorrat geht hier absichtlich nicht ein** -- er ist Gegenstand von
/// Pruefung 1. Waere er Teil dieses Praedikats, faenge Pruefung 2 auch den
/// abgeschnittenen Vorrat, und Pruefung 3 koennte nicht mehr zeigen, dass die beiden
/// Bedingungen Verschiedenes messen.
bool besteht_referenzfolge(const Folgenbefund& befund)
{
    return gleicher_text(befund.text, REFERENZFOLGE) && befund.erste_abweichende_runde < 0;
}

/// Die erste Runde `1..runden`, in der der Vorratsvektor der abweichenden Fassung von
/// dem der echten abweicht. `-1`, wenn keine. Sie beantwortet die Frage "an welcher
/// Runde faellt es auf" fuer die Faelle, in denen die **Artenfolge** gleich bleibt.
i64 erste_vorratsabweichung(const Profil& anteile, i64 runden, Abweichung abweichung)
{
    const Zulaessigkeit alle = Zulaessigkeit{true, true, true, true, true};
    for (i64 t = 1; t <= runden; ++t) {
        const Laufergebnis echt =
            pruefstand::vorrat::spiele(anteile, alle, t, Abweichung::KEINE);
        const Laufergebnis anders = pruefstand::vorrat::spiele(anteile, alle, t, abweichung);
        if (echt.vorrat != anders.vorrat) {
            return t;
        }
    }
    return -1;
}

/// Die Vorfuehrung einer falschen Fassung in einem Block: beide Praedikate, beide
/// Urteile, und die Stelle, an der es auffaellt.
void fuehre_abweichung_vor(const char* name, const Profilliste& liste, Abweichung abweichung,
                           bool invariante_soll, bool folge_soll)
{
    std::fprintf(stdout, "\nAbweichung: %s\n", name);

    const Invariantenbefund inv1 = pruefe_invariante(liste, 1, abweichung);
    const Invariantenbefund inv3 = pruefe_invariante(liste, 3, abweichung);
    const Folgenbefund folge = pruefe_referenzfolge(abweichung);

    std::fprintf(stdout, "  Bedingung 1, k=1           %s (%lld von 126 Profilen heil)\n",
                 besteht_invariante(inv1) ? "besteht" : "GEFANGEN", z(inv1.erfuellt));
    std::fprintf(stdout, "  Bedingung 1, k=3           %s (%lld von 126 Profilen heil)\n",
                 besteht_invariante(inv3) ? "besteht" : "GEFANGEN", z(inv3.erfuellt));
    std::fprintf(stdout, "  Bedingung 2 (Referenz)     %s\n",
                 besteht_referenzfolge(folge) ? "besteht" : "GEFANGEN");
    std::fprintf(stdout, "  gelaufene Folge            %s\n", folge.text.data());
    std::fprintf(stdout, "  der Wortlaut aus spiel.md  %s\n", REFERENZFOLGE);

    // Die Stelle, an der es auffaellt -- Profil und Runde, wie die Abnahme sie
    // verlangt.
    if (!besteht_invariante(inv1)) {
        const Profileintrag& kipp = liste[static_cast<std::size_t>(inv1.erstes_profil)];
        std::fprintf(stdout, "  Bedingung 1 kippt zuerst bei Kennung %lld, k=1:\n",
                     z(inv1.erstes_profil));
        schreibe_vektor("Profil (a1..a5)", kipp.anteile);
        schreibe_vektor("Endvorrat, soll (0,..)", inv1.erster_endvorrat);
        schreibe_vektor("Steckplaetze, ist", inv1.erste_verteilung);
        schreibe_vektor("Steckplaetze, soll 3k*ai", inv1.erste_erwartung);
        const i64 runde_auf = erste_vorratsabweichung(kipp.anteile, 5, abweichung);
        std::fprintf(stdout, "  ihr Vorrat weicht ab ab Runde %lld\n", z(runde_auf));
    }
    if (!besteht_referenzfolge(folge)) {
        std::fprintf(stdout, "  Bedingung 2 faengt sie in Runde %lld\n",
                     z(folge.erste_abweichende_runde));
    }

    // **Der eigentliche Nachweis: dieselben zwei Praedikate, verschiedene Urteile.**
    // `invariante_soll` und `folge_soll` stehen im Aufruf und sagen, welche Bedingung
    // diese Fassung faengt **und welche sie durchlaesst**. Beides wird zugesichert --
    // nur zusammen belegt es, dass die zwei Bedingungen Verschiedenes messen.
    pruefe(besteht_invariante(inv1) == invariante_soll,
           "Bedingung 1 (k=1) urteilt ueber diese Fassung wie angekuendigt", __LINE__);
    pruefe(besteht_invariante(inv3) == invariante_soll,
           "Bedingung 1 (k=3) urteilt ueber diese Fassung wie angekuendigt", __LINE__);
    pruefe(besteht_referenzfolge(folge) == folge_soll,
           "Bedingung 2 urteilt ueber diese Fassung wie angekuendigt", __LINE__);
    pruefe(!invariante_soll || !folge_soll,
           "die Fassung wird von mindestens einer der beiden Bedingungen gefangen",
           __LINE__);
}

}  // namespace

int main()
{
    // Die 126 Profile kommen aus Paket 0019 und werden hier nicht ein zweites Mal
    // erzeugt. Was an der Liste selbst zu pruefen ist, prueft `vorrat_probe`.
    const Profilliste liste = pruefstand::vorrat::erzeuge_profilliste();
    const Zulaessigkeit alle = Zulaessigkeit{true, true, true, true, true};

    // -----------------------------------------------------------------------
    // Pruefung 2a -- die beiden Abschriften aus `spiel.md` gegeneinander
    // -----------------------------------------------------------------------
    //
    // Zuerst, weil sie den Massstab prueft und nicht das Programm. Ein Tippfehler in
    // einer der beiden Abschriften waere sonst ein stiller falscher Massstab -- und
    // ein falscher Massstab, gegen den alles gruen laeuft, ist schlimmer als ein
    // roter Test.
    std::fprintf(stdout, "Der Wortlaut aus spiel.md, zweimal abgeschrieben\n");
    {
        Laufergebnis abschrift;
        abschrift.runden = static_cast<i64>(REFERENZRUNDEN);
        for (std::size_t t = 0; t < REFERENZRUNDEN; ++t) {
            abschrift.folge[t] = REFERENZTABELLE[t];
        }
        std::array<char, 64> aus_tabelle{};
        setze_text(aus_tabelle, abschrift, static_cast<i64>(REFERENZRUNDEN));

        std::fprintf(stdout, "  als Zeichenkette           %s\n", REFERENZFOLGE);
        std::fprintf(stdout, "  aus der Tabelle gesetzt    %s\n", aus_tabelle.data());
        pruefe(gleicher_text(aus_tabelle, REFERENZFOLGE),
               "die beiden Abschriften aus spiel.md stimmen ueberein", __LINE__);
    }

    // -----------------------------------------------------------------------
    // Pruefung 1 -- die Invariante, k = 1 und k = 3 einzeln
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nBedingung 1: die Invariante aus T43, alle 126 Profile\n");

    const Invariantenbefund k1 = pruefe_invariante(liste, 1, Abweichung::KEINE);
    const Invariantenbefund k3 = pruefe_invariante(liste, 3, Abweichung::KEINE);

    std::fprintf(stdout,
                 "  k=1:  5 Runden, 15 Steckplaetze, je Art 3*ai   %lld von 126 heil\n",
                 z(k1.erfuellt));
    std::fprintf(stdout,
                 "  k=3: 15 Runden, 45 Steckplaetze, je Art 9*ai   %lld von 126 heil\n",
                 z(k3.erfuellt));

    if (k1.erstes_profil >= 0) {
        schreibe_vektor("k=1 kippt bei Profil", k1.erster_vektor);
        schreibe_vektor("Endvorrat", k1.erster_endvorrat);
        schreibe_vektor("Steckplaetze, ist", k1.erste_verteilung);
        schreibe_vektor("Steckplaetze, soll", k1.erste_erwartung);
    }
    if (k3.erstes_profil >= 0) {
        schreibe_vektor("k=3 kippt bei Profil", k3.erster_vektor);
        schreibe_vektor("Endvorrat", k3.erster_endvorrat);
        schreibe_vektor("Steckplaetze, ist", k3.erste_verteilung);
        schreibe_vektor("Steckplaetze, soll", k3.erste_erwartung);
    }

    pruefe(besteht_invariante(k1), "die Invariante gilt fuer alle 126 Profile, k = 1",
           __LINE__);
    pruefe(besteht_invariante(k3), "die Invariante gilt fuer alle 126 Profile, k = 3",
           __LINE__);

    // Die Buchhaltung daneben, damit "15k Steckplaetze" nicht nur aus der Summe der
    // Erwartungen folgt: Ein Lauf ohne leeren Platz vergibt genau `3 * runden`
    // Steckplaetze, und die Summe der `3k*ai` ist `15k`, weil `Sum ai = 5` ist.
    {
        const Laufergebnis ref = pruefstand::vorrat::spiele(REFERENZPROFIL, alle, 15);
        i64 summe = 0;
        for (std::size_t i = 0; i < ARTEN; ++i) {
            summe += ref.gezaehlt[i];
        }
        std::fprintf(stdout, "  k=3 am Referenzprofil: %lld Steckplaetze, %lld leer\n",
                     z(summe), z(ref.leer_geblieben));
        pruefe(summe == 45, "k = 3 vergibt 45 Steckplaetze (15k)", __LINE__);
        pruefe(ref.leer_geblieben == 0, "bei durchgehender Zulaessigkeit bleibt keiner leer",
               __LINE__);
    }

    // -----------------------------------------------------------------------
    // Pruefung 2 -- die Probe des Referenzprofils, zeichengleich
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nBedingung 2: die Probe des Referenzprofils (1,1,1,1,1)\n");

    const Folgenbefund echt = pruefe_referenzfolge(Abweichung::KEINE);
    std::fprintf(stdout, "  gelaufen                   %s\n", echt.text.data());
    std::fprintf(stdout, "  spiel.md, Zeile 1043 f.    %s\n", REFERENZFOLGE);
    schreibe_vektor("Endvorrat nach 5 Runden", echt.endvorrat);

    pruefe(besteht_referenzfolge(echt),
           "die Folge ist zeichengleich zum Wortlaut aus spiel.md", __LINE__);
    pruefe(echt.endvorrat_null, "und der Vorrat steht danach wieder auf (0,0,0,0,0)",
           __LINE__);

    // -----------------------------------------------------------------------
    // Pruefung 3 -- die beiden absichtlich falschen Fassungen
    // -----------------------------------------------------------------------
    //
    // Je Fassung wird **beides** zugesichert: welche Bedingung sie faengt und welche
    // sie durchlaesst. Die Erwartung steht im Aufruf, nicht im Ergebnis.
    //
    //   Gleichstand nach groesserer Kennung: besteht 1, gefangen von 2. Sie dreht nur
    //   die Reihenfolge innerhalb eines Gleichstands -- jede Art kommt weiterhin
    //   `3k*ai`-mal dran, die Invariante merkt davon nichts.
    //
    //   Vorrat bei null abgeschnitten: gefangen von 1, besteht 2. Sie verschenkt die
    //   Schuld einer belasteten Art; ueber fuenf Runden des Referenzprofils faellt
    //   das an der **Artenfolge** nicht auf, wohl aber am Endvorrat.
    fuehre_abweichung_vor("Gleichstand nach GROESSERER Kennung", liste,
                          Abweichung::GLEICHSTAND_NACH_GROESSERER_KENNUNG,
                          /*invariante_soll=*/true, /*folge_soll=*/false);

    fuehre_abweichung_vor("Vorrat bei null ABGESCHNITTEN", liste,
                          Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN,
                          /*invariante_soll=*/false, /*folge_soll=*/true);

    // Und der Satz, um dessentwillen es zwei Fassungen sind und nicht eine: Jede der
    // beiden Bedingungen faengt genau eine der beiden -- also faengt keine von beiden
    // allein alles, und keine ist ueberfluessig.
    {
        const bool inv_faengt_nur_abschnitt =
            besteht_invariante(
                pruefe_invariante(liste, 1, Abweichung::GLEICHSTAND_NACH_GROESSERER_KENNUNG))
            && !besteht_invariante(
                pruefe_invariante(liste, 1, Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN));
        const bool folge_faengt_nur_gleichstand =
            !besteht_referenzfolge(
                pruefe_referenzfolge(Abweichung::GLEICHSTAND_NACH_GROESSERER_KENNUNG))
            && besteht_referenzfolge(
                pruefe_referenzfolge(Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN));

        std::fprintf(stdout, "\nDie zwei Bedingungen messen Verschiedenes\n");
        std::fprintf(stdout, "  Bedingung 1 faengt genau den Abschnitt        %s\n",
                     inv_faengt_nur_abschnitt ? "ja" : "NEIN");
        std::fprintf(stdout, "  Bedingung 2 faengt genau den Gleichstand      %s\n",
                     folge_faengt_nur_gleichstand ? "ja" : "NEIN");
        pruefe(inv_faengt_nur_abschnitt,
               "Bedingung 1 faengt den Abschnitt und laesst den Gleichstand durch",
               __LINE__);
        pruefe(folge_faengt_nur_gleichstand,
               "Bedingung 2 faengt den Gleichstand und laesst den Abschnitt durch",
               __LINE__);
    }

    // -----------------------------------------------------------------------
    // Pruefung 4 -- der leere Steckplatz und die Gegenprobe zu `ai = 0`
    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\nBedingung 4a: keine Art zur Wahl -- der Steckplatz bleibt leer\n");
    {
        // Ein Vorrat, der **nicht** bei null anfaengt, und ein Profil mit Nullen und
        // Nicht-Nullen: So ist "Zeichen fuer Zeichen der vom Rundenanfang" eine
        // Aussage ueber fuenf verschiedene Zahlen und nicht ueber fuenf Nullen.
        const Vorrat vorher = Vorrat{7, -2, 0, 4, -9};
        const Profil profil = Profil{2, 0, 1, 0, 2};
        const Zulaessigkeit keine = Zulaessigkeit{false, false, false, false, false};

        // Die Erwartung getrennt hingeschrieben -- nicht von `runde` geholt.
        std::array<i64, ARTEN> erwartet{};
        for (std::size_t i = 0; i < ARTEN; ++i) {
            erwartet[i] = vorher[i] + ZUWACHS * profil[i];
        }

        Vorrat vorrat = vorher;
        const Rundenfolge folge = pruefstand::vorrat::runde(vorrat, profil, keine);

        schreibe_vektor("Vorrat vor der Runde", vorher);
        schreibe_vektor("nach dem Rundenanfang", erwartet);
        schreibe_vektor("Vorrat nach der Runde", vorrat);
        std::fprintf(stdout, "  Steckplaetze               %lld,%lld,%lld (LEER ist %lld)\n",
                     z(folge[0]), z(folge[1]), z(folge[2]), z(LEER));

        bool alle_leer = true;
        for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
            if (folge[p] != LEER) {
                alle_leer = false;
            }
        }
        pruefe(alle_leer, "steht keine Art zur Wahl, bleibt jeder Steckplatz LEER", __LINE__);
        pruefe(vorrat == erwartet,
               "und kein Vorrat ist verrechnet: der Vektor ist der vom Rundenanfang",
               __LINE__);

        // Ueber `spiele`: `leer_geblieben` zaehlt sie, und zwar alle drei je Runde.
        const Laufergebnis lauf = pruefstand::vorrat::spiele(profil, keine, 4);
        std::fprintf(stdout, "  4 Runden ohne Zulaessigkeit: %lld leer (erwartet 12)\n",
                     z(lauf.leer_geblieben));
        pruefe(lauf.leer_geblieben == 12, "leer_geblieben zaehlt 3 Plaetze je Runde",
               __LINE__);
        i64 vergeben = 0;
        for (std::size_t i = 0; i < ARTEN; ++i) {
            vergeben += lauf.gezaehlt[i];
        }
        pruefe(vergeben == 0, "und keine Art hat einen Steckplatz bekommen", __LINE__);
    }

    std::fprintf(stdout,
                 "\nBedingung 4b: eine einzige zulaessige Art mit ai = 0 bekommt alle drei\n");
    {
        // Die Gegenprobe zu "`ai = 0` verbietet die Art nicht". Art 2 hat `a2 = 0`,
        // also Vorrat 0; Art 1 hat `a1 = 5`, also Vorrat 15 -- den weit groesseren.
        // Zulaessig ist nur Art 2. Ein hartes Verbot liesse hier alle drei
        // Steckplaetze leer; die Vorgabe verlangt, dass Art 2 alle drei bekommt.
        const Profil profil = Profil{5, 0, 0, 0, 0};
        const Zulaessigkeit nur_zwei = Zulaessigkeit{false, true, false, false, false};

        const Laufergebnis lauf = pruefstand::vorrat::spiele(profil, nur_zwei, 1);

        std::fprintf(stdout, "  Profil (5,0,0,0,0), zulaessig nur Art 2 (a2 = 0)\n");
        std::fprintf(stdout, "  Steckplaetze               %lld,%lld,%lld\n",
                     z(lauf.folge[0][0]), z(lauf.folge[0][1]), z(lauf.folge[0][2]));
        schreibe_vektor("Vorrat nach der Runde", lauf.vorrat);

        pruefe(lauf.folge[0] == Rundenfolge{2, 2, 2},
               "ai = 0 verbietet nicht: Art 2 bekommt alle drei Steckplaetze", __LINE__);
        pruefe(lauf.gezaehlt[1] == 3, "gezaehlt zaehlt sie der Art 2 zu", __LINE__);
        pruefe(lauf.leer_geblieben == 0, "und kein Steckplatz bleibt leer", __LINE__);
        pruefe(lauf.vorrat[1] == -3 * KOSTEN,
               "ihr Vorrat wird negativ (0 - 3*5) und nicht abgeschnitten", __LINE__);
        pruefe(lauf.vorrat[0] == ZUWACHS * 5,
               "der Vorrat der unzulaessigen Art 1 waechst trotzdem", __LINE__);
    }

    // -----------------------------------------------------------------------
    // Die Schranke von `spiele` -- Indexschutz, keine Spielregel
    // -----------------------------------------------------------------------
    //
    // Steht nicht in der Abnahme von Paket 0029; sie ist eine Zusage des Kopfes
    // ("Wirft `std::domain_error`, wenn `runden` ausserhalb 0 .. RUNDEN_HOECHSTENS
    // liegt") und schuetzt den Schreibzugriff auf `Laufergebnis::folge`. Eine
    // Schranke ohne Test ist eine Behauptung, und die Fehlerklasse dahinter ist
    // genau die, die C++ diesem Vorhaben mitbringt.
    std::fprintf(stdout, "\nDie Schranke von spiele (Indexschutz)\n");
    {
        const Zulaessigkeit keine = Zulaessigkeit{false, false, false, false, false};
        bool wirft_zu_gross = false;
        bool wirft_negativ = false;
        bool nimmt_grenze = false;

        try {
            (void)pruefstand::vorrat::spiele(
                REFERENZPROFIL, keine, static_cast<i64>(RUNDEN_HOECHSTENS) + 1);
        } catch (const std::domain_error&) {
            wirft_zu_gross = true;
        }
        try {
            (void)pruefstand::vorrat::spiele(REFERENZPROFIL, keine, -1);
        } catch (const std::domain_error&) {
            wirft_negativ = true;
        }
        // Die Grenze selbst gehoert **hinein**, nicht hinaus: ein Abweisen bei
        // genau `RUNDEN_HOECHSTENS` waere der Zaunpfahlfehler in die andere Richtung.
        try {
            const Laufergebnis grenze = pruefstand::vorrat::spiele(
                REFERENZPROFIL, keine, static_cast<i64>(RUNDEN_HOECHSTENS));
            nimmt_grenze = (grenze.runden == static_cast<i64>(RUNDEN_HOECHSTENS));
        } catch (const std::domain_error&) {
            nimmt_grenze = false;
        }

        std::fprintf(stdout, "  runden = %zu + 1 wirft      %s\n", RUNDEN_HOECHSTENS,
                     wirft_zu_gross ? "ja" : "NEIN");
        std::fprintf(stdout, "  runden = -1 wirft          %s\n",
                     wirft_negativ ? "ja" : "NEIN");
        std::fprintf(stdout, "  runden = %zu laeuft         %s\n", RUNDEN_HOECHSTENS,
                     nimmt_grenze ? "ja" : "NEIN");

        pruefe(wirft_zu_gross, "spiele wirft ueber RUNDEN_HOECHSTENS", __LINE__);
        pruefe(wirft_negativ, "spiele wirft bei negativer Rundenzahl", __LINE__);
        pruefe(nimmt_grenze, "und laeuft bei genau RUNDEN_HOECHSTENS noch", __LINE__);
    }

    // -----------------------------------------------------------------------
    std::fprintf(stdout, "\n%s -- %d Pruefung(en) fehlgeschlagen\n",
                 fehlgeschlagen == 0 ? "bestanden" : "GESCHEITERT", fehlgeschlagen);
    return fehlgeschlagen == 0 ? 0 : 1;
}
