//! Laufende Probe fuer `kern::festkomma`.
//!
//! Die Rechenwerte sind schon in `src/festkomma.cpp` als `static_assert` belegt und
//! damit beim Uebersetzen geprueft. Diese Probe gibt es fuer drei Dinge, die ein
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
//!   3. **Welcher Riegel geworfen hat** (Paket 0257). Alle neun Abbruchstellen von
//!      `festkomma.hpp` werfen dieselbe Klasse; ein Nachweis, der nur nach dem Wurf
//!      fragt, bliebe gruen, wenn zwei von ihnen in denselben Zweig zusammenfielen.
//!      Das Verzeichnis dazu steht in `kern/test/kennzeichen.hpp`, die Riegel dieser
//!      Probe stehen unten.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdio>

#include "kern/festkomma.hpp"

#include "kennzeichen.hpp"

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

// ---------------------------------------------------------------------------
// Die Riegel dieser Probe -- Paket 0257
// ---------------------------------------------------------------------------
//
// Bis zu diesem Paket standen hier zwei eigene Fassungen derselben Sache: elf Aufrufe
// von `ERWARTE_ABBRUCH`, die allein pruefen, *dass* geworfen wurde, und sieben eines
// probeneigenen Makros, das den Wortlaut von Hand nach einer einzelnen Nadel
// durchsuchte. Der Apparat steht seit Paket 0244 in `kern/test/kennzeichen.hpp` und
// wird von `schritt_probe` und `werte_probe` benutzt; die Begruendung beider Haelften
// der Eindeutigkeit steht dort und wird hier nicht wiederholt.
//
// **Neun Abbruchstellen, zehn Riegel und einer ohne Zustand.** Gezaehlt am 2026-09-08
// auf dem Stand von `kern/include/kern/festkomma.hpp`; die Zeilennummern altern, die
// Zuordnung nicht:
//
//   :84   `intern::nach_i64`   -> drei Riegel, siehe den Absatz darunter
//   :121  `intern::potenz_i128` -> `RIEGEL_OHNE_ZUSTAND`, siehe dort
//   :138  `teile_gerundet`     -> `TeileGerundetNennerNull`
//   :158  `mal_geteilt`        -> `MalGeteiltNennerNull`
//   :203  `plus`               -> `PlusSumme`
//   :219  `minus`              -> `MinusDifferenz`
//   :313  `potenz`             -> `PotenzErgebnis`
//   :345  `wurzel`             -> `WurzelGrad`
//   :348  `wurzel`             -> `WurzelRadikand`
//
// **Warum eine Stelle drei Riegel ist.** `intern::nach_i64` bricht mit dem Text ab,
// den ihr Aufrufer hereinreicht, und das sind drei verschiedene: `teile_gerundet`,
// `mal_geteilt` und `mal` nennen jeweils sich selbst. Ein Riegel ist der Wortlaut und
// nicht der Waechter, der ihn baut -- zoege man die drei zu einem zusammen, muesste
// ihre Kennzeichenliste auf den gemeinsamen Rest schrumpfen, und der ist
// "Ergebnis ausserhalb von i64 (T7)", also genau der Teil, der nichts unterscheidet.
// Dieselbe Entscheidung hat `werte_probe` fuer `pruefe_handelssektor` getroffen
// (Paket 0255).
enum class Riegel : std::size_t {
    TeileGerundetNennerNull,  ///< `teile_gerundet`: Nenner null (T6)
    TeileGerundetErgebnis,    ///< `nach_i64` unter dem Namen `teile_gerundet` (T7)
    MalGeteiltNennerNull,     ///< `mal_geteilt`: Nenner null (T6)
    MalGeteiltErgebnis,       ///< `nach_i64` unter dem Namen `mal_geteilt` (T7)
    MalErgebnis,              ///< `nach_i64` unter dem Namen `mal` (T7)
    PlusSumme,                ///< `plus`: der Ueberlaufbaustein meldet (T7)
    MinusDifferenz,           ///< `minus`: derselbe Baustein, andere Rechenart (T7)
    PotenzErgebnis,           ///< `potenz`: der Zwischenwert verlaesst i64 (T7)
    WurzelGrad,               ///< `wurzel`: Grad ausserhalb von 1..WURZEL_GRAD_MAX (T29)
    WurzelRadikand,           ///< `wurzel`: negativer Radikand (T29)
    Anzahl,
};

/// Alle Riegel der Reihe nach -- erzeugt und nicht abgeschrieben, aus demselben Grund
/// wie in `werte_probe` seit Paket 0255: Eine Namensliste neben der Aufzaehlung
/// derselben Namen ist eine Verdopplung, die vergessen werden kann.
constexpr std::array<Riegel, static_cast<std::size_t>(Riegel::Anzahl)> riegelliste()
{
    std::array<Riegel, static_cast<std::size_t>(Riegel::Anzahl)> liste{};
    for (std::size_t n = 0; n < liste.size(); ++n) {
        liste[n] = static_cast<Riegel>(n);
    }
    return liste;
}

constexpr auto ALLE_RIEGEL = riegelliste();

const char* riegelname(Riegel welcher)
{
    switch (welcher) {
    case Riegel::TeileGerundetNennerNull:
        return "Nenner null in teile_gerundet";
    case Riegel::TeileGerundetErgebnis:
        return "Ergebnis ausserhalb von i64 (teile_gerundet)";
    case Riegel::MalGeteiltNennerNull:
        return "Nenner null in mal_geteilt";
    case Riegel::MalGeteiltErgebnis:
        return "Ergebnis ausserhalb von i64 (mal_geteilt)";
    case Riegel::MalErgebnis:
        return "Ergebnis ausserhalb von i64 (mal)";
    case Riegel::PlusSumme:
        return "Summe ausserhalb von i64 (plus)";
    case Riegel::MinusDifferenz:
        return "Differenz ausserhalb von i64 (minus)";
    case Riegel::PotenzErgebnis:
        return "Ergebnis ausserhalb von i64 (potenz)";
    case Riegel::WurzelGrad:
        return "Wurzelgrad ausserhalb von 1 bis WURZEL_GRAD_MAX";
    case Riegel::WurzelRadikand:
        return "negativer Radikand in wurzel";
    case Riegel::Anzahl:
        break;
    }
    return "(kein Riegel)";
}

// Die Kennzeichenlisten. Jede besteht aus Stuecken **ihrer eigenen** Meldung; was sie
// leisten, misst die Auswertung am Ende des Laufs.
//
// **Die Aufteilung ist hier ueberall dieselbe, weil die Gefahr ueberall dieselbe ist.**
// Acht der zehn Meldungen enden auf "ausserhalb von i64 (T7)" -- das gemeinsame Ende
// traegt nichts. Das **erste** Stueck nennt deshalb den Namen der Rechnung **samt
// Doppelpunkt**, und daran haengt die ganze Trennschaerfe: `"mal: Ergebnis"` steht
// nicht in `"mal_geteilt: Ergebnis ausserhalb von i64 (T7)"`, weil dort auf `mal` ein
// Unterstrich folgt. Wer eines dieser Stuecke auf den blossen Funktionsnamen kuerzt,
// bekommt im selben Lauf die Zeile "kennzeichnet nicht" -- `mal` steht in `mal_geteilt`
// und `potenz` in `potenz_i128`. Das **zweite** Stueck ist der Satzteil, der eine
// Umformulierung der Meldung auffallen liesse.
constexpr std::array<const char*, 2> KZ_TEILE_NENNER = {
    "teile_gerundet: Nenner null", "keine Pruefung bemerkt (T6)"};
constexpr std::array<const char*, 2> KZ_TEILE_ERGEBNIS = {
    "teile_gerundet: Ergebnis", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_MALGETEILT_NENNER = {
    "mal_geteilt: Nenner null", "keine Pruefung bemerkt (T6)"};
constexpr std::array<const char*, 2> KZ_MALGETEILT_ERGEBNIS = {
    "mal_geteilt: Ergebnis", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_MAL_ERGEBNIS = {
    "mal: Ergebnis", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_PLUS_SUMME = {
    "plus: Summe", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_MINUS_DIFFERENZ = {
    "minus: Differenz", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_POTENZ_ERGEBNIS = {
    "potenz: Ergebnis", "ausserhalb von i64 (T7)"};
constexpr std::array<const char*, 2> KZ_WURZEL_GRAD = {
    "wurzel: Grad muss zwischen", "WURZEL_GRAD_MAX liegen (T29)"};
constexpr std::array<const char*, 2> KZ_WURZEL_RADIKAND = {
    "wurzel: negativer Radikand", "Produktionsfunktion hat keinen (T29)"};

// ---------------------------------------------------------------------------
// Der Riegel, den kein Zustand erreicht -- die zweite Kategorie aus Paket 0248
// ---------------------------------------------------------------------------
//
// `intern::potenz_i128` bricht ab, wenn ihr Zwischenwert die `i128`-Grenze
// ueberschreitet. Erreichbar ist die Stelle nicht, und der Grund steht im Kopf von
// `wurzel` selbst: Die Funktion hat genau drei Aufrufstellen, alle drei in `wurzel`,
// und dort ist der Startwert die kleinste Zweierpotenz oberhalb der Wurzel. Mit
// `bitlaenge(x) <= 63` und `n <= WURZEL_GRAD_MAX` bleibt `start^(n-1)` unter 2^95, und
// `r` wird nur kleiner -- die Grenze 2^127 kommt nicht in Reichweite. Ausserhalb von
// `wurzel` ruft niemand sie (gemessen am 2026-09-08 ueber `kern/`, `pruefstand/` und
// `werkzeuge/`).
//
// Sie in `ALLE_RIEGEL` einzutragen faerbte einen heilen Baum rot; sie wegzulassen
// versteckte sie vor der Pruefung, die es gibt, damit keine Schranke unbemerkt
// verschwindet. Also die zweite Kategorie: ausgenommen von der Vollzaehligkeit,
// geprueft gegen jede fremde Meldung.
enum class RiegelOhneZustand : std::size_t {
    /// in `kern::festkomma::intern::potenz_i128`: der Zwischenwert verlaesst i128
    ZwischenwertInPotenzI128,
    Anzahl,
};

/// Die Textstuecke, an denen die Meldung dieses Riegels zu erkennen **waere**.
///
/// Dass die verbleibende Haelfte hier beisst, ist an diesem Eintrag ablesbar: Kuerzt
/// jemand die Liste auf `"potenz"` allein, passt sie sofort auf die Meldung des Riegels
/// `PotenzErgebnis`, die in jedem Lauf zweimal ankommt. Der Unterstrich ist die ganze
/// Trennung zwischen der oeffentlichen Potenz und der internen.
constexpr std::array<const char*, 2> KZ_POTENZ_I128 = {
    "potenz_i128: Zwischenwert", "ueberschreitet i128"};

constexpr std::array<probe::kennzeichen::OhneZustand<RiegelOhneZustand>, 1>
    RIEGEL_OHNE_ZUSTAND = {{
        {RiegelOhneZustand::ZwischenwertInPotenzI128,
         "Zwischenwert ausserhalb von i128 in potenz_i128",
         "die Funktion hat drei Aufrufstellen, alle drei in wurzel, und dort bleibt "
         "jeder Zwischenwert unter 2^95 -- die i128-Grenze liegt bei 2^127",
         KZ_POTENZ_I128},
    }};

// Dasselbe Netz wie bei `ALLE_RIEGEL`: Kommt ein Eintrag dazu und niemand traegt ihn
// nach, faellt es beim Uebersetzen auf und nicht daran, dass ihn nie jemand prueft.
static_assert(RIEGEL_OHNE_ZUSTAND.size()
              == static_cast<std::size_t>(RiegelOhneZustand::Anzahl));

/// Wie viele Meldungen zu einem Riegel in einem heilen Lauf ankommen muessen -- die
/// Zahl und nicht "mindestens eine".
///
/// Der Unterschied ist der Zweck: Die Vollzaehligkeitshaelfte des Verzeichnisses sieht
/// nur, ob ein Riegel **ueberhaupt** gefeuert hat. Von den drei Stellen am Waechter von
/// `mal` duerfte man damit zwei streichen, ohne dass etwas rot wird.
struct Sollzahl {
    Riegel      riegel;
    std::size_t meldungen;
};

constexpr std::array<Sollzahl, static_cast<std::size_t>(Riegel::Anzahl)> SOLLZAHLEN = {{
    {Riegel::TeileGerundetNennerNull, 2},  // 1/0 und 0/0
    {Riegel::TeileGerundetErgebnis, 1},    // I64_MIN / -1
    {Riegel::MalGeteiltNennerNull, 1},
    {Riegel::MalGeteiltErgebnis, 1},
    {Riegel::MalErgebnis, 3},              // beide Vorzeichen und I64_MIN * -1
    {Riegel::PlusSumme, 2},                // ueber I64_MAX und unter I64_MIN
    {Riegel::MinusDifferenz, 2},           // dieselben beiden Raender
    {Riegel::PotenzErgebnis, 2},           // I64_MAX^2 und 10^19
    {Riegel::WurzelGrad, 2},               // Grad 0 und Grad 33
    {Riegel::WurzelRadikand, 1},
}};

/// Ob der Eintrag an der n-ten Stelle auch den n-ten Riegel nennt. Die
/// Groessenpruefung darunter allein liesse zwei Eintraege desselben Riegels durch --
/// die Zahl staende dann richtig da und ein Riegel fehlte trotzdem.
constexpr bool sollzahlen_geordnet()
{
    for (std::size_t n = 0; n < SOLLZAHLEN.size(); ++n) {
        if (SOLLZAHLEN[n].riegel != static_cast<Riegel>(n)) {
            return false;
        }
    }
    return true;
}

static_assert(SOLLZAHLEN.size() == static_cast<std::size_t>(Riegel::Anzahl));
static_assert(sollzahlen_geordnet());

/// Das Verzeichnis dieser Probe. Die Mechanik ist geteilt, die Werte sind es nicht.
probe::kennzeichen::Buch<Riegel, RiegelOhneZustand> buch{"festkomma", fehlgeschlagen,
                                                        ALLE_RIEGEL, &riegelname,
                                                        RIEGEL_OHNE_ZUSTAND};

}  // namespace

#define PRUEFE(ausdruck)     pruefe((ausdruck), #ausdruck, __LINE__)

/// Der Aufruf bricht ab, und zwar an **diesem** Riegel.
///
/// Reicht die Zeile der Aufrufstelle durch -- sonst naennte jede Fehlermeldung die eine
/// Zeile in der Vorlage. Der Ausdruck steht zugleich als Text da: Er benennt die Stelle
/// in jeder Meldung des Verzeichnisses, und niemand muss ihn ein zweites Mal
/// hinschreiben.
#define BRICHT_AB_MIT(riegel, kennzeichen, ausdruck)                    \
    buch.bricht_ab_mit(#ausdruck, (riegel), (kennzeichen), __LINE__,    \
                       [&] { static_cast<void>(ausdruck); })

namespace {

// ---------------------------------------------------------------------------
// Paket 0257 -- die Vollzaehligkeit je Riegel, als Zahl
// ---------------------------------------------------------------------------
//
// Gedruckt wird je Riegel, was gezaehlt wurde, und daneben, was erwartet war. Eine
// Zusicherung ohne ihre Zahl kostet den naechsten Lauf einen eigenen Bau.
void probe_riegel_vollzaehlig()
{
    for (const Sollzahl& soll : SOLLZAHLEN) {
        const std::size_t gezaehlt = buch.anzahl_zu(soll.riegel);
        std::printf("  Riegel \"%s\": %zu Meldung(en), erwartet %zu\n",
                    riegelname(soll.riegel), gezaehlt, soll.meldungen);
        PRUEFE(gezaehlt == soll.meldungen);
    }
    std::printf("  Riegel mit Zustand (festkomma): %zu Meldungen aus %zu Riegeln, jede "
                "Zahl einzeln geprueft; vor Paket 0257 stand hier keine\n",
                buch.anzahl(), SOLLZAHLEN.size());
}

}  // namespace

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
    // Jede Stelle nennt ab Paket 0257 ihren Riegel. Der Unterschied zum blossen
    // "es hat geworfen", das hier bis dahin stand: Faellt ein Waechter weg und
    // wirft ein zweiter weiter, bleibt der alte Aufruf gruen -- die Kennzeichenliste
    // dagegen wird rot, weil die angekommene Meldung ihren Riegel nicht mehr nennt.
    //
    // Nenner null bricht ab und wird nie still zu null -- der Fall, an dem Befund 2
    // der zweiten Pruefung haengt.
    BRICHT_AB_MIT(Riegel::TeileGerundetNennerNull, KZ_TEILE_NENNER,
                  teile_gerundet(undurchsichtig(1), undurchsichtig(0)));
    BRICHT_AB_MIT(Riegel::TeileGerundetNennerNull, KZ_TEILE_NENNER,
                  teile_gerundet(undurchsichtig(0), undurchsichtig(0)));
    BRICHT_AB_MIT(Riegel::MalGeteiltNennerNull, KZ_MALGETEILT_NENNER,
                  mal_geteilt(undurchsichtig(1), undurchsichtig(2), undurchsichtig(0)));

    // Ueberlauf ist ein Absturz, kein Umlauf (T7). `I64_MIN / -1` ist der eine Fall,
    // in dem eine gueltige Division ein Ergebnis ausserhalb von i64 hat. Die beiden
    // naechsten Zeilen sterben an derselben Stelle -- `intern::nach_i64` --, nennen
    // aber verschiedene Rechnungen, und genau das halten die Listen auseinander.
    BRICHT_AB_MIT(Riegel::TeileGerundetErgebnis, KZ_TEILE_ERGEBNIS,
                  teile_gerundet(undurchsichtig(I64_MIN), undurchsichtig(-1)));
    BRICHT_AB_MIT(Riegel::MalGeteiltErgebnis, KZ_MALGETEILT_ERGEBNIS,
                  mal_geteilt(undurchsichtig(I64_MAX), undurchsichtig(2),
                              undurchsichtig(1)));
    BRICHT_AB_MIT(Riegel::PotenzErgebnis, KZ_POTENZ_ERGEBNIS,
                  potenz(undurchsichtig(I64_MAX), 2));
    BRICHT_AB_MIT(Riegel::PotenzErgebnis, KZ_POTENZ_ERGEBNIS,
                  potenz(undurchsichtig(10), 19));

    // Wurzel: Grad und Radikand haben Grenzen, und sie sind Abbrueche.
    BRICHT_AB_MIT(Riegel::WurzelRadikand, KZ_WURZEL_RADIKAND,
                  wurzel(undurchsichtig(-1), 2));
    BRICHT_AB_MIT(Riegel::WurzelGrad, KZ_WURZEL_GRAD, wurzel(undurchsichtig(4), 0));
    BRICHT_AB_MIT(Riegel::WurzelGrad, KZ_WURZEL_GRAD, wurzel(undurchsichtig(4), 33));

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
    BRICHT_AB_MIT(Riegel::MalErgebnis, KZ_MAL_ERGEBNIS,
                  mal(undurchsichtig(MAL_FAKTOR_BRICHT_AB),
                      undurchsichtig(MAL_FAKTOR_BRICHT_AB)));
    BRICHT_AB_MIT(Riegel::MalErgebnis, KZ_MAL_ERGEBNIS,
                  mal(undurchsichtig(-MAL_FAKTOR_BRICHT_AB),
                      undurchsichtig(MAL_FAKTOR_BRICHT_AB)));
    BRICHT_AB_MIT(Riegel::MalErgebnis, KZ_MAL_ERGEBNIS,
                  mal(undurchsichtig(I64_MIN), undurchsichtig(-1)));

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
    //
    // Sie sind zugleich die Kontrolle, die frueher `!ABBRUCH_MELDET(...)` an einem
    // durchkommenden Aufruf fuehrte: Was hier einen Wert liefert, hat nicht geworfen.
    PRUEFE(plus(undurchsichtig(SUMMAND_PASST_OBEN),  undurchsichtig( 1)) == I64_MAX);
    PRUEFE(plus(undurchsichtig(SUMMAND_PASST_UNTEN), undurchsichtig(-1)) == I64_MIN);
    PRUEFE(minus(undurchsichtig(SUMMAND_PASST_OBEN),  undurchsichtig(-1)) == I64_MAX);
    PRUEFE(minus(undurchsichtig(SUMMAND_PASST_UNTEN), undurchsichtig( 1)) == I64_MIN);

    // Die ganze Spanne in einem Schritt, ohne dass etwas hinausfaellt.
    PRUEFE(plus(undurchsichtig(I64_MAX), undurchsichtig(I64_MIN)) == -1);
    PRUEFE(minus(undurchsichtig(-1), undurchsichtig(I64_MIN)) == I64_MAX);

    // Die beiden Abbruchpfade, je einen Schritt ueber den Kontrollen darueber.
    //
    // Bis Paket 0257 stand hier eine Negativkontrolle von Hand: zwei Zeilen, die
    // nachwiesen, dass die Meldung von `mal` weder "plus: Summe" noch
    // "minus: Differenz" enthaelt. Sie fallen nicht weg, sondern werden allgemeiner --
    // die Auswertung des Verzeichnisses haelt am Ende des Laufs **jede** der zehn
    // Listen gegen **jede** fremde Meldung, also auch diese beiden gegen die drei
    // Meldungen von `mal`. Zwei Nadeln in einer Meldung waren der Sonderfall davon.
    BRICHT_AB_MIT(Riegel::PlusSumme, KZ_PLUS_SUMME,
                  plus(undurchsichtig(I64_MAX), undurchsichtig(1)));
    BRICHT_AB_MIT(Riegel::PlusSumme, KZ_PLUS_SUMME,
                  plus(undurchsichtig(I64_MIN), undurchsichtig(-1)));
    BRICHT_AB_MIT(Riegel::MinusDifferenz, KZ_MINUS_DIFFERENZ,
                  minus(undurchsichtig(I64_MAX), undurchsichtig(-1)));
    BRICHT_AB_MIT(Riegel::MinusDifferenz, KZ_MINUS_DIFFERENZ,
                  minus(undurchsichtig(I64_MIN), undurchsichtig(1)));

    // Zuletzt, denn beide lesen das Verzeichnis, das die Aufrufstellen oben gefuellt
    // haben: `probe_riegel_vollzaehlig` haelt die Zahl je Riegel, `buch.auswerten`
    // die Eindeutigkeit der Kennzeichen und den Riegel ohne Zustand.
    probe_riegel_vollzaehlig();
    buch.auswerten();

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::festkomma -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::festkomma -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
