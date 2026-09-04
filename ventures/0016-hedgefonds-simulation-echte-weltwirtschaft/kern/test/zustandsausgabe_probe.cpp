//! Laufende Probe fuer `kern::zustandsausgabe`.
//!
//! Der Kopf des Moduls weist beim **Uebersetzen** nach, dass jede der 310 Adressen
//! genau eine Skalenklasse und genau eine Herkunftsart hat und dass die zwoelf Zahlen
//! aus T49 und die fuenf aus T45 aufgehen. Diese Probe gibt es fuer sechs Dinge, die
//! ein `static_assert` nicht kann:
//!
//!   1. **Die Abnahmebedingung im Wortlaut.** Sie verlangt den Nachweis, dass jede der
//!      310 Adressen **in mindestens einer der drei Ausgaben vorkommt**. Das ist eine
//!      Aussage ueber Text, nicht ueber eine Tabelle, und sie laesst sich nur an
//!      erzeugtem Text pruefen.
//!   2. **Die Vorbedingung dieses Nachweises.** "Kommt vor" heisst hier: Die Adresse
//!      steht als Zeichenfolge im Blatt. Das ist nur dann ein Beleg, wenn keine Adresse
//!      in einer anderen steckt -- sonst faende die Suche nach der einen die andere.
//!      Diese Bedingung wird zuerst geprueft, ueber alle 310 mal 310 Paare. Ohne sie
//!      waere die Probe darunter ein Riegel, der Vorhandensein prueft und Wirkung
//!      behauptet.
//!   3. **Das Testprofil aus ADR 0011, Massnahme 2.** Sie linkt `kern_geprueft`, also
//!      dieselben Quellen mit `-fsanitize=undefined,address`. Ein Sanitizer sieht nur,
//!      was wirklich laeuft -- und diese Datei schreibt in Puffer von 60 kB an ihrer
//!      Grenze entlang.
//!   4. **Die Bereichsaufteilung.** Dass die zehn Bereiche die 310 Adressen
//!      vollstaendig und ueberschneidungsfrei teilen, haengt an den Adresstexten und ist
//!      deshalb keine Uebersetzungszeitfrage.
//!   5. **Die Abbrueche.** Ein Abbruch laesst sich nur zur Laufzeit fangen, und seine
//!      Meldung gehoert ins Protokoll. Geprueft werden beide Richtungen: dass die
//!      Uebersicht auf einem tragfaehigen Zustand rechnet, und dass sie auf einem
//!      Zustand abbricht, dessen Wechselkurs die Schranke aus T47 reisst.
//!   6. **Die Zahlen im Wortlaut.** Was diese Probe ausrechnet, schreibt sie hin.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <cstddef>
#include <cstdio>
#include <stdexcept>

#include "kern/werte.hpp"
#include "kern/zustand.hpp"
#include "kern/zustandsausgabe.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::I64_MAX;
using kern::festkomma::I64_MIN;
using kern::zustand::Aggregat;
using kern::zustand::FondsGroesse;
using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Instrument;
using kern::zustand::InstrumentFeld;
using kern::zustand::PartieFeld;
using kern::zustand::PolitischeGroesse;
using kern::zustand::Sektor;
using kern::zustand::SektorGroesse;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

using kern::zustand::FELDER;
using kern::zustand::GEBIETE;
using kern::zustand::LAENDER;
using kern::zustand::SEKTOREN;

using kern::zustandsausgabe::Adressblatt;
using kern::zustandsausgabe::Ausgabe;
using kern::zustandsausgabe::BEREICH_NAME;
using kern::zustandsausgabe::BEREICHE;
using kern::zustandsausgabe::detail;
using kern::zustandsausgabe::diff;
using kern::zustandsausgabe::gehoert_zum_bereich;
using kern::zustandsausgabe::herkunft_von;
using kern::zustandsausgabe::Herkunftsart;
using kern::zustandsausgabe::Skalenklasse;
using kern::zustandsausgabe::skalenklasse_von;
using kern::zustandsausgabe::uebersicht;
using kern::zustandsausgabe::UEBERSICHT_ZEILEN_MAX;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Weist nach, dass ein Aufruf abbricht -- und schreibt die Meldung mit.
///
/// Der Wortlaut gehoert ins Protokoll: Ein Fang ohne Meldung belegt nur, dass
/// *irgendwo* etwas geworfen wurde, nicht dass es die gemeinte Stelle war.
template <typename Aufruf>
void erwarte_abbruch(Aufruf aufruf, const char* text, int zeile)
{
    try {
        aufruf();
    } catch (const std::domain_error& fehler) {
        std::fprintf(stdout, "  Abbruch wie erwartet (Zeile %d): %s\n", zeile, fehler.what());
        return;
    }
    std::fprintf(stderr, "KEIN ABBRUCH Zeile %d: %s\n", zeile, text);
    ++fehlgeschlagen;
}

#define ERWARTE_ABBRUCH(ausdruck) erwarte_abbruch([&] { ausdruck; }, #ausdruck, __LINE__)

/// Legt einen Startwert. Der Zugang aus Paket 0027 ist der einzige Schreibweg vor der
/// ersten Runde; einen anderen gibt es von aussen nicht.
void startwert(Zustand& ziel, Index platz, i64 wert) { Startbelegung{ziel}.setze(platz, wert); }

// ---------------------------------------------------------------------------
// Textwerkzeug -- so wenig, wie fuer die Nachweise noetig ist
// ---------------------------------------------------------------------------

/// Steht `nadel` irgendwo in `heuhaufen`? Die leere Nadel steht ueberall.
[[nodiscard]] bool enthaelt(const char* heuhaufen, const char* nadel) noexcept
{
    for (std::size_t start = 0; heuhaufen[start] != '\0' || nadel[0] == '\0'; ++start) {
        std::size_t i = 0;
        while (nadel[i] != '\0' && heuhaufen[start + i] == nadel[i]) {
            ++i;
        }
        if (nadel[i] == '\0') {
            return true;
        }
        if (heuhaufen[start] == '\0') {
            return false;
        }
    }
    return false;
}

/// Der Anfang der ersten Zeile, die mit `vorspann` beginnt -- sonst `nullptr`.
[[nodiscard]] const char* zeile_ab(const char* text, const char* vorspann) noexcept
{
    std::size_t start = 0;
    while (true) {
        std::size_t i = 0;
        while (vorspann[i] != '\0' && text[start + i] == vorspann[i]) {
            ++i;
        }
        if (vorspann[i] == '\0') {
            return text + start;
        }
        while (text[start] != '\0' && text[start] != '\n') {
            ++start;
        }
        if (text[start] == '\0') {
            return nullptr;
        }
        ++start;  // ueber die Zeilenschaltung hinweg
    }
}

/// Steht `nadel` in **dieser** Zeile -- also vor der naechsten Zeilenschaltung?
///
/// Die Trennung von `enthaelt` ist der Punkt: Eine Zahl irgendwo im Blatt belegt nicht,
/// dass sie in der Zeile dieses Gebiets steht, und genau das soll unten geprueft werden.
[[nodiscard]] bool zeile_enthaelt(const char* zeilenanfang, const char* nadel) noexcept
{
    if (zeilenanfang == nullptr) {
        return false;
    }
    for (std::size_t start = 0; zeilenanfang[start] != '\n' && zeilenanfang[start] != '\0';
         ++start) {
        std::size_t i = 0;
        while (nadel[i] != '\0' && zeilenanfang[start + i] == nadel[i]) {
            ++i;
        }
        if (nadel[i] == '\0') {
            return true;
        }
    }
    return false;
}

/// Eine Zahl als Text -- ueber dieselbe Zahlenumwandlung, die die drei Ebenen benutzen.
///
/// Keine zweite Umwandlung in dieser Datei: Wer die Zahl anders formatierte als das
/// Modul, vergliche zwei Schreibweisen statt zweier Werte.
using Zahltext = Ausgabe<64>;

[[nodiscard]] Zahltext als_text(kern::festkomma::i128 wert)
{
    Zahltext text;
    text.zahl(wert);
    return text;
}

}  // namespace

namespace {

/// Der Wechselkurs des Gebiets `g` in der tragfaehigen Belegung.
///
/// **Je Gebiet ein anderer Wert, und das ist der Kern der Ordnungsprobe.** Waeren alle
/// fuenf gleich, liefe die Pruefung unten gruen, auch wenn die Uebersicht die Zeilen
/// vertauschte -- zwei Quellen sind nur unterscheidbar, wenn sie verschiedene Werte
/// tragen. Alle fuenf liegen ueber der Schranke aus T47.
[[nodiscard]] i64 kurs_von(std::size_t g) { return 10000 + static_cast<i64>(g) * 137; }

/// Eine Belegung, auf der `werte::fondsvermoegen` durchrechnet.
///
/// Sie ist kein Startzustand des Spiels und will keiner sein -- die Startwerte kommen
/// nach T45 aus Jahrgang, `parameter.toml` und Manifest, und der Kasten `daten` ist
/// nicht gebaut. Sie ist die Ausgangslage, an der sich die Ebenen messen lassen.
void belege_tragfaehig(Zustand& z)
{
    using namespace kern::zustand;

    for (std::size_t g = 0; g < GEBIETE; ++g) {
        const auto gebiet = static_cast<Gebiet>(g);
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            const auto sektor = static_cast<Sektor>(s);
            startwert(z, stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Wertschoepfung),
                      1000000);
            startwert(z, stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Kapitalstock),
                      2000000);
            startwert(z, stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Beschaeftigung),
                      500000);
            startwert(z, stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Preis), 10000);
        }
        startwert(z, stelle_aggregat(gebiet, Aggregat::Bevoelkerung), 80000000);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Erwerbstaetige), 40000000);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Produktivitaet), 10000);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Preisniveau), 10000);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Inflation), 200);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Leitzins), 250);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Wechselkurs), kurs_von(g));
        startwert(z, stelle_aggregat(gebiet, Aggregat::Staatsschuld), 6000);
        startwert(z, stelle_aggregat(gebiet, Aggregat::Haushaltssaldo), -200);

        for (std::size_t n = 0; n < GEBIETE; ++n) {
            if (n == g) {
                continue;
            }
            for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
                startwert(z, stelle_handel(gebiet, static_cast<Gebiet>(n),
                                           static_cast<Sektor>(s)),
                          100000);
            }
        }

        if (g >= LAENDER) {
            continue;
        }
        startwert(z, stelle_politisch(gebiet, PolitischeGroesse::Zustimmung), 5000);
        startwert(z, stelle_politisch(gebiet, PolitischeGroesse::Einfluss), 1000);
        startwert(z, stelle_instrument(gebiet, Instrument::Leitzins, InstrumentFeld::Stand), 250);
        startwert(z, stelle_instrument(gebiet, Instrument::Zoll, InstrumentFeld::Stand), 380);
        startwert(z, stelle_instrument(gebiet, Instrument::Haushalt, InstrumentFeld::Stand), -200);
        startwert(z, stelle_instrument(gebiet, Instrument::Regulierung, InstrumentFeld::Stand), 3);
    }

    for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
        startwert(z, stelle_weltpreis(static_cast<Sektor>(s)), 10000);
    }
    startwert(z, stelle_markt(MarktGroesse::Wert), 1000000);
    startwert(z, stelle_markt(MarktGroesse::Rendite), 300);

    startwert(z, stelle_fonds(FondsGroesse::Kasse), 4200000000);
    startwert(z, stelle_fonds(FondsGroesse::Sichtbarkeit), 1500);
    startwert(z, stelle_fonds(FondsGroesse::Anlegerbestand), 1000000000);
    startwert(z, stelle_fonds(FondsGroesse::Marktanteil), 420);
    startwert(z, stelle_ueberrendite(1), 100);
    startwert(z, stelle_ueberrendite(2), 200);
    startwert(z, stelle_ueberrendite(3), -50);

    startwert(z, stelle_partie(PartieFeld::JahrgangId), 2001);
    startwert(z, stelle_partie(PartieFeld::ParameterPruefsumme), 12345);
}

/// Ein Parametersatz, mit dem die Bewertung durchrechnet.
[[nodiscard]] kern::werte::Konstanten tragfaehige_konstanten()
{
    kern::werte::Konstanten konst;
    konst.stufenweite       = 100;
    konst.ausstiegsabschlag = 500;
    konst.aufschlag         = 50;
    konst.lobbykosten       = 1;
    konst.gegenlobby_satz   = 1;
    for (std::size_t l = 0; l < LAENDER; ++l) {
        konst.leitzins_start[l] = 250;
    }
    return konst;
}

}  // namespace
