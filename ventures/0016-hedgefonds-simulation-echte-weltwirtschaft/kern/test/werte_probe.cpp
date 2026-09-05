//! Laufende Probe fuer `kern::werte` -- Paket 0002-fondsbewertung-definieren.
//!
//! Geprueft wird, was ein `static_assert` in `src/werte.cpp` nicht kann: alles, was
//! einen `Zustand` braucht (er ist kein literaler Typ), und jeder Abbruchpfad.
//!
//! ## Die Zahlenprobe aus T47, mit ausgeschriebenem Erwartungswert
//!
//! Ein Korb von 21.000.000.000 Tausend USD, ein Beteiligungsanteil von 20
//! Zehntausendsteln und ein Ausstiegsabschlag von null ergeben innen 42.000.000
//! Tausend USD und nach der Skalengrenze 4.200.000.000.000 US-Cent. Das ist
//! Abnahmebedingung 4 des Pakets, und beide Zahlen stehen unten ausgeschrieben, damit
//! der Pruefer sie von Hand nachrechnen kann.
//!
//! ## Was jede Pruefung leisten soll
//!
//! Nicht "die Funktion liefert eine Zahl", sondern eine Aussage, die falsch werden
//! kann. Drei Bauarten kommen dafuer vor:
//!
//!   * **Der zweite Rechenweg.** `fondsvermoegen` wird gegen die Summe der einzeln
//!     aufgerufenen Positions- und Beteiligungswerte gehalten. Der eine Weg liest die
//!     zwoelf Korbwerte aus einem Feld, der andere rechnet jeden neu -- dass beide
//!     dasselbe ergeben, ist die Zusage "eine Bewertung, nicht zwei".
//!   * **Der Abbruch mit Positivkontrolle davor.** "Der Aufruf bricht ab" ist erst ein
//!     Nachweis, wenn derselbe Aufruf mit einer heilen Zahl nachweislich gerechnet hat.
//!   * **Die verworfene Alternative als Zahl.** Wo eine Vorgabe zwischen zwei Formen
//!     entscheidet, steht die andere Form daneben und liefert eine **andere** Zahl.
//!     Sonst prueft die Zeile die Entscheidung nicht, sondern nur die Rechnung.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdio>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::mal_geteilt;

using kern::schreiber::Modus;
using kern::schreiber::Schreiber;
using kern::schreiber::Ursache;

using kern::zustand::Aggregat;
using kern::zustand::BeteiligungsFeld;
using kern::zustand::FondsGroesse;
using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Sektor;
using kern::zustand::SektorGroesse;
using kern::zustand::Startbelegung;
using kern::zustand::Steckplatz;
using kern::zustand::Zustand;

using kern::zustand::GEBIETE;
using kern::zustand::LAENDER;
using kern::zustand::SEKTOREN;
using kern::zustand::STECKPLAETZE;

using kern::zustand::stelle_aggregat;
using kern::zustand::stelle_beteiligung;
using kern::zustand::stelle_fonds;
using kern::zustand::stelle_handel;
using kern::zustand::stelle_position;
using kern::zustand::stelle_sektorgroesse;
using kern::zustand::steckplatz_anleihe;
using kern::zustand::steckplatz_sektor;
using kern::zustand::steckplatz_waehrung;

using kern::werte::Konstanten;

int fehlgeschlagen = 0;

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
        return;  // genau das war die Erwartung
    }
    std::fprintf(stderr, "KEIN ABBRUCH Zeile %d: %s\n", zeile, text);
    ++fehlgeschlagen;
}

/// Die drei Sektoren als Liste, damit die Grundbelegung ueber sie laufen kann.
constexpr std::array<Sektor, SEKTOREN> SEKTORLISTE{
    Sektor::Landwirtschaft,
    Sektor::Industrie,
    Sektor::Dienstleistungen,
};

/// Ein Zustand samt dem einen Startwertzugang, der ihn fuellt -- dieselbe Bauart wie
/// in der Schrankenprobe, und aus demselben Grund: Ein Zugang laesst sich an einen
/// Zustand mit gelaufener Runde nicht mehr binden, also leben beide gemeinsam.
///
/// Die **Grundbelegung** setzt genau die Werte, ohne die jede Bewertung an einer
/// Bereichspruefung abbraeche statt zu rechnen: Wechselkurs und Sektorpreise stehen
/// auf 10.000, dem Indexstartwert aus T5. Alles andere ist null, und das ist
/// ausdruecklich kein Startzustand des Spiels -- jede Pruefung unten setzt selbst, was
/// sie messen will.
class Rohling {
public:
    Rohling()
    {
        for (std::size_t g = 0; g < GEBIETE; ++g) {
            const Gebiet gebiet = static_cast<Gebiet>(g);
            lege(stelle_aggregat(gebiet, Aggregat::Wechselkurs), 10'000);
            for (const Sektor sektor : SEKTORLISTE) {
                lege(stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Preis), 10'000);
            }
        }
    }

    void lege(Index platz, i64 wert) { zugang_.setze(platz, wert); }

    operator const Zustand&() const { return zustand_; }

private:
    Zustand       zustand_;
    Startbelegung zugang_{zustand_};
};

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)
#define ERWARTE_ABBRUCH(ausdruck) \
    erwarte_abbruch([&] { static_cast<void>(ausdruck); }, #ausdruck, __LINE__)

namespace {

using kern::werte::anleihekurs;
using kern::werte::anleihewert;
using kern::werte::beteiligung_wert;
using kern::werte::bip;
using kern::werte::fondsanteil;
using kern::werte::fondsvermoegen;
using kern::werte::handelsvolumen;
using kern::werte::korbbestand;
using kern::werte::korbwert;
using kern::werte::landespreis;
using kern::werte::markt;
using kern::werte::marktkorb;
using kern::werte::positionswert;
using kern::werte::schuld;
using kern::werte::stufenwert;
using kern::werte::waehrungswert;
using kern::werte::wert;

/// Ein brauchbarer Konstantensatz fuer die Proben. Die Zahlen sind gewaehlt und nicht
/// aus `parameter.toml` abgeschrieben: Jeder dortige Wert traegt heute einen als
/// solchen gekennzeichneten Platzhalter, und eine Probe, die ihn uebernaehme, wuerde
/// bei der ersten Kalibrierung rot, ohne dass etwas kaputt waere.
constexpr Konstanten K_GRUND{
    /* stufenweite       */ 1,
    /* ausstiegsabschlag */ 0,
    /* aufschlag         */ 51,
    /* lobbykosten       */ 100,
    /* gegenlobby_satz   */ 3,
    /* leitzins_start    */ {{0, 0, 0, 0}},
};

// ---------------------------------------------------------------------------
// Abnahmebedingung 4 -- die Zahlenprobe aus T47
// ---------------------------------------------------------------------------

void probe_zahlenprobe_t47()
{
    Rohling r;

    // Ein Korb von 21.000.000.000 Tausend USD: Menge mal Kurs durch Wechselkurs, und
    // beide Indizes stehen auf ihrem Startwert 10.000.
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Industrie, SektorGroesse::Kapitalstock),
           21'000'000'000);
    r.lege(stelle_beteiligung(Gebiet::US, Sektor::Industrie, BeteiligungsFeld::Anteil), 20);

    const Zustand& z = r;

    PRUEFE(korbwert(z, Gebiet::US, Sektor::Industrie) == 21'000'000'000);

    // Der innere Wert, ueber den zweiten Weg gebildet: die Anteilsrechnung aus dem
    // Festkommawerk, nicht aus diesem Modul.
    PRUEFE(mal_geteilt(21'000'000'000, 20, 10'000) == 42'000'000);

    // Und derselbe Betrag nach der Skalengrenze, ausgeschrieben.
    PRUEFE(beteiligung_wert(z, K_GRUND, Gebiet::US, Sektor::Industrie) == 4'200'000'000'000);

    // Gegenprobe zum Abschlag: ein Ausstiegsabschlag von 2.500 Zehntausendsteln laesst
    // drei Viertel stehen.
    Konstanten mit_abschlag = K_GRUND;
    mit_abschlag.ausstiegsabschlag = 2'500;
    PRUEFE(beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie)
           == 3'150'000'000'000);
}

// ---------------------------------------------------------------------------
// Die erste Wertebereichsschranke aus T47 -- Positivkontrolle vor dem Abbruch
// ---------------------------------------------------------------------------

void probe_wechselkursschranke()
{
    Rohling heil;
    heil.lege(stelle_sektorgroesse(Gebiet::DE, Sektor::Industrie, SektorGroesse::Kapitalstock), 3);
    heil.lege(stelle_aggregat(Gebiet::DE, Aggregat::Wechselkurs), 1);

    // Positivkontrolle **vor** dem Abbruch: Bei einem Wechselkurs von genau 1 -- der
    // Untergrenze aus T5 Klasse 6 -- rechnet dieselbe Bewertung nachweislich.
    PRUEFE(korbwert(heil, Gebiet::DE, Sektor::Industrie) == 30'000);

    Rohling null;
    null.lege(stelle_aggregat(Gebiet::DE, Aggregat::Wechselkurs), 0);
    ERWARTE_ABBRUCH(korbwert(null, Gebiet::DE, Sektor::Industrie));

    Rohling negativ;
    negativ.lege(stelle_aggregat(Gebiet::DE, Aggregat::Wechselkurs), -10'000);
    negativ.lege(stelle_sektorgroesse(Gebiet::DE, Sektor::Industrie, SektorGroesse::Kapitalstock),
                 3);
    // Der eigentliche Fall: Ohne die Schranke braeche hier **nichts** ab, und der Korb
    // haette ein umgedrehtes Vorzeichen.
    ERWARTE_ABBRUCH(korbwert(negativ, Gebiet::DE, Sektor::Industrie));
    ERWARTE_ABBRUCH(wert(negativ, 3, 10'000, Gebiet::DE));
}

// ---------------------------------------------------------------------------
// T47 -- der Abbruch bei stufen = 0 liegt VOR markt(p)
// ---------------------------------------------------------------------------

void probe_leerer_steckplatz_rechnet_nicht()
{
    Rohling r;
    // Ein Wechselkurs von null macht jede Bewertung dieses Gebiets zum Abbruch. Damit
    // ist "markt(p) wurde gerechnet" von "markt(p) wurde nicht gerechnet"
    // unterscheidbar -- ohne diesen Kunstgriff lieferten beide Reihenfolgen dieselbe
    // Null und die Vorgabe waere ungeprueft.
    r.lege(stelle_aggregat(Gebiet::CN, Aggregat::Wechselkurs), 0);

    const Steckplatz platz = steckplatz_sektor(Gebiet::CN, Sektor::Landwirtschaft);

    // Positivkontrolle: markt(p) wuerde auf diesem Zustand abbrechen.
    ERWARTE_ABBRUCH(markt(r, K_GRUND, platz));
    ERWARTE_ABBRUCH(stufenwert(r, K_GRUND, platz));

    // Die Aussage: Bei stufen = 0 kommt trotzdem eine Null zurueck.
    PRUEFE(positionswert(r, K_GRUND, platz) == 0);

    // Und die Gegenprobe, damit die Null oben nicht bloss Zufall ist: Mit einer Stufe
    // darauf bricht derselbe Aufruf ab.
    Rohling belegt;
    belegt.lege(stelle_aggregat(Gebiet::CN, Aggregat::Wechselkurs), 0);
    belegt.lege(stelle_position(platz), 1);
    ERWARTE_ABBRUCH(positionswert(belegt, K_GRUND, platz));
}

}  // namespace

namespace {

// ---------------------------------------------------------------------------
// T47 -- die verbindliche Reihenfolge der Rundungen
// ---------------------------------------------------------------------------

void probe_rundungsreihenfolge()
{
    // Gewaehlt sind Zahlen, bei denen sich die beiden Formen **unterscheiden**. Sonst
    // pruefte die Zeile die Rechnung und nicht die Entscheidung: Bei glatten Werten
    // liefern beide dasselbe, und die Vorgabe waere unbelegt.
    Rohling r;
    r.lege(stelle_sektorgroesse(Gebiet::BR, Sektor::Industrie, SektorGroesse::Kapitalstock),
           14'999);
    const Steckplatz platz = steckplatz_sektor(Gebiet::BR, Sektor::Industrie);
    r.lege(stelle_position(platz), 3);

    const Zustand& z = r;

    PRUEFE(markt(z, K_GRUND, platz) == 14'999);

    // Verbindlich (T47): erst runden, dann vervielfachen.
    //   stufenwert = 14.999 * 1 / 10.000 -> 1 (aufgerundet von 1,4999 waere 1)
    //   3 * 1 = 3 Tausend USD -> 300.000 US-Cent
    PRUEFE(stufenwert(z, K_GRUND, platz) == 1);
    PRUEFE(positionswert(z, K_GRUND, platz) == 300'000);

    // Die genauere Form, die einen ADR braeuchte, ergibt hier eine **andere** Zahl:
    //   3 * 14.999 / 10.000 = 4,4997 -> 4 Tausend USD -> 400.000 US-Cent
    PRUEFE(mal_geteilt(14'999, 3, 10'000) == 4);
    PRUEFE(positionswert(z, K_GRUND, platz) != 400'000);
}

// ---------------------------------------------------------------------------
// T47 -- eine Bewertung, nicht zwei: der zweite Rechenweg zum Fondsvermoegen
// ---------------------------------------------------------------------------

void probe_fondsvermoegen_zweiter_weg()
{
    Rohling r;

    // Eine Ausgangslage, in der jeder Summand ungleich null ist -- sonst prueft die
    // Gleichheit unten nur, dass zwei Nullen gleich sind.
    r.lege(stelle_fonds(FondsGroesse::Kasse), 500'000'000);
    r.lege(stelle_fonds(FondsGroesse::Hebelstand), 120'000'000);

    for (std::size_t l = 0; l < LAENDER; ++l) {
        const Gebiet land = static_cast<Gebiet>(l);
        i64 stufe = 1;
        for (const Sektor sektor : SEKTORLISTE) {
            r.lege(stelle_sektorgroesse(land, sektor, SektorGroesse::Kapitalstock),
                   1'000'000 + static_cast<i64>(l) * 7'000 + stufe * 13);
            r.lege(stelle_position(steckplatz_sektor(land, sektor)), stufe - 2);
            r.lege(stelle_beteiligung(land, sektor, BeteiligungsFeld::Anteil), 30 * stufe);
            ++stufe;
        }
        // Anleihen: Schuld ueber das Bruttoinlandsprodukt, Kurs ueber den Leitzins.
        r.lege(stelle_sektorgroesse(land, Sektor::Dienstleistungen,
                                    SektorGroesse::Wertschoepfung), 400'000);
        r.lege(stelle_aggregat(land, Aggregat::Staatsschuld), 6'000);
        r.lege(stelle_aggregat(land, Aggregat::Leitzins), 200);
        r.lege(stelle_position(steckplatz_anleihe(land)), 4);
        // Waehrungen: Handelsstroeme in beide Richtungen.
        r.lege(stelle_position(steckplatz_waehrung(land)), l == 0 ? 0 : 2);
    }
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        for (std::size_t n = 0; n < GEBIETE; ++n) {
            if (g == n) { continue; }
            r.lege(stelle_handel(static_cast<Gebiet>(g), static_cast<Gebiet>(n),
                                 Sektor::Landwirtschaft),
                   1'000 + static_cast<i64>(g) * 10 + static_cast<i64>(n));
            r.lege(stelle_handel(static_cast<Gebiet>(g), static_cast<Gebiet>(n),
                                 Sektor::Industrie),
                   5'000 + static_cast<i64>(g) * 10 + static_cast<i64>(n));
        }
    }

    Konstanten konst = K_GRUND;
    konst.stufenweite = 250;
    konst.ausstiegsabschlag = 400;
    konst.leitzins_start = {{200, 150, 100, 900}};

    const Zustand& z = r;

    // Der zweite Weg: jede der zwanzig Positionen und jede der zwoelf Beteiligungen
    // einzeln aufgerufen. Diese Aufrufe kennen den Korbvorrat nicht und rechnen jeden
    // Korbwert selbst -- kommt dieselbe Zahl heraus wie beim gebuendelten Weg, dann
    // sind es nachweislich dieselben Bewertungen.
    i64 erwartet = z.lies(stelle_fonds(FondsGroesse::Kasse));
    for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
        erwartet += positionswert(z, konst, static_cast<Steckplatz>(p));
    }
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (const Sektor sektor : SEKTORLISTE) {
            erwartet += beteiligung_wert(z, konst, static_cast<Gebiet>(l), sektor);
        }
    }
    erwartet -= z.lies(stelle_fonds(FondsGroesse::Hebelstand));

    PRUEFE(fondsvermoegen(z, konst) == erwartet);
    PRUEFE(erwartet != 0);

    // Dass die Kasse als Summand und der Hebel als Abzug eingeht, und beide in
    // derselben Skala: Um denselben Betrag erhoeht, heben sie einander auf.
    r.lege(stelle_fonds(FondsGroesse::Kasse), 500'000'000 + 1'000);
    PRUEFE(fondsvermoegen(z, konst) == erwartet + 1'000);
    r.lege(stelle_fonds(FondsGroesse::Hebelstand), 120'000'000 + 1'000);
    PRUEFE(fondsvermoegen(z, konst) == erwartet);
}

}  // namespace

namespace {

// ---------------------------------------------------------------------------
// T33 -- der Marktkorb liest Mengen und Kurse aus verschiedenen Zustaenden
// ---------------------------------------------------------------------------

void probe_marktkorb_zwei_quellen()
{
    Rohling mengen;
    Rohling kurse;

    // Die Menge steht allein im ersten Zustand, der Kurs allein im zweiten. Damit
    // liefern die drei moeglichen Kombinationen drei verschiedene Zahlen, und jede
    // Verwechslung der beiden Quellen faellt auf.
    mengen.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                     SektorGroesse::Kapitalstock), 100);
    kurse.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft, SektorGroesse::Preis),
               20'000);

    // Der Wechselkurs ist ebenfalls ein Kurs und muss deshalb aus `k` kommen. Ohne
    // diese Zeile stuende er in beiden Zustaenden auf 10.000, und die Zuordnung waere
    // ungeprueft -- eine Vertauschung der Quellen lieferte dieselbe Zahl.
    kurse.lege(stelle_aggregat(Gebiet::US, Aggregat::Wechselkurs), 5'000);

    // Die vier Anleihen tragen nichts bei: ohne Wertschoepfung keine Schuld. Der
    // Anleihekurs braucht trotzdem einen tragfaehigen Nenner, sonst braeche er ab.
    for (std::size_t l = 0; l < LAENDER; ++l) {
        const Gebiet land = static_cast<Gebiet>(l);
        mengen.lege(stelle_aggregat(land, Aggregat::Leitzins), 0);
        kurse.lege(stelle_aggregat(land, Aggregat::Leitzins), 0);
    }

    const Zustand& m = mengen;
    const Zustand& k = kurse;

    // Menge aus `m`, Sektorpreis und Wechselkurs aus `k`: 100 * 20.000 / 5.000 = 400.
    PRUEFE(marktkorb(m, k, K_GRUND) == 400);

    // Beide aus `m`: Kurs und Wechselkurs stehen dort auf ihrem Startwert 10.000 -> 100.
    PRUEFE(marktkorb(m, m, K_GRUND) == 100);

    // Beide aus `k`: dort gibt es die Menge nicht -> 0.
    PRUEFE(marktkorb(k, k, K_GRUND) == 0);

    // Und die verworfene Zuordnung als Zahl: Kaeme der Wechselkurs aus den Mengen,
    // stuenden hier 200 statt 400.
    PRUEFE(mal_geteilt(100, 20'000, 10'000) == 200);
    PRUEFE(marktkorb(m, k, K_GRUND) != 200);

    // Und die Anleihen tragen wirklich nichts bei -- sonst waeren die drei Zahlen oben
    // nicht die des Korbteils.
    PRUEFE(anleihewert(m, K_GRUND, Gebiet::US) == 0);
    PRUEFE(schuld(m, Gebiet::US) == 0);
}

// ---------------------------------------------------------------------------
// T48 Nr. 11 -- das Handelsvolumen liest beide Richtungen
// ---------------------------------------------------------------------------

void probe_handelsvolumen_beide_richtungen()
{
    Rohling einzeln;
    einzeln.lege(stelle_handel(Gebiet::US, Gebiet::CN, Sektor::Landwirtschaft), 7);
    einzeln.lege(stelle_handel(Gebiet::CN, Gebiet::US, Sektor::Landwirtschaft), 5);

    // Aus- plus Einfuhr, und aus Sicht beider Seiten dieselbe Zahl.
    PRUEFE(handelsvolumen(einzeln, Gebiet::US) == 12);
    PRUEFE(handelsvolumen(einzeln, Gebiet::CN) == 12);
    // Ein unbeteiligtes Gebiet sieht davon nichts.
    PRUEFE(handelsvolumen(einzeln, Gebiet::BR) == 0);

    // Die Abzaehlung: 4 Gegenueber mal 2 handelbare Sektoren mal 2 Richtungen sind 16
    // gelesene Adressen je Gebiet. Steht ueberall eine Eins, muss 16 herauskommen --
    // und zwar fuer alle fuenf Gebiete, auch fuer die Restwelt.
    Rohling alle;
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        for (std::size_t n = 0; n < GEBIETE; ++n) {
            if (g == n) { continue; }
            alle.lege(stelle_handel(static_cast<Gebiet>(g), static_cast<Gebiet>(n),
                                    Sektor::Landwirtschaft), 1);
            alle.lege(stelle_handel(static_cast<Gebiet>(g), static_cast<Gebiet>(n),
                                    Sektor::Industrie), 1);
        }
    }
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        PRUEFE(handelsvolumen(alle, static_cast<Gebiet>(g)) == 16);
    }

    // Der Waehrungswert ist das Handelsvolumen zum festen Kurs 10.000.
    PRUEFE(waehrungswert(alle, Gebiet::DE) == 16);
}

// ---------------------------------------------------------------------------
// T48 Nr. 9, 10, 12 -- Bruttoinlandsprodukt, Schuld und Anleihekurs
// ---------------------------------------------------------------------------

void probe_bip_schuld_anleihekurs()
{
    Rohling r;
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                SektorGroesse::Wertschoepfung), 100);
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Industrie,
                                SektorGroesse::Wertschoepfung), 200);
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Dienstleistungen,
                                SektorGroesse::Wertschoepfung), 300);
    r.lege(stelle_aggregat(Gebiet::US, Aggregat::Staatsschuld), 5'000);
    r.lege(stelle_aggregat(Gebiet::US, Aggregat::Leitzins), 200);

    const Zustand& z = r;

    PRUEFE(bip(z, Gebiet::US) == 600);
    // Die Staatsschuld ist eine Quote in Basispunkten: 5.000 sind die Haelfte.
    PRUEFE(schuld(z, Gebiet::US) == 300);

    Konstanten konst = K_GRUND;
    konst.leitzins_start = {{200, 0, 0, 0}};

    // Im Startjahr per Konstruktion genau 10.000 -- der Zaehler ist der Nenner.
    PRUEFE(anleihekurs(z, konst, Gebiet::US) == 10'000);

    // Streng fallend im Zins: der doppelte Abstand halbiert den Kurs.
    r.lege(stelle_aggregat(Gebiet::US, Aggregat::Leitzins), 451);
    PRUEFE(anleihekurs(z, konst, Gebiet::US) == 5'000);

    // Die Schranke sitzt am Instrument, nicht am Kurs -- reisst der Politikpfad sie
    // trotzdem, ist der Nenner null und der Kurs ein Abbruch statt einer Zahl.
    r.lege(stelle_aggregat(Gebiet::US, Aggregat::Leitzins), -51);
    ERWARTE_ABBRUCH(anleihekurs(z, konst, Gebiet::US));

    // Die Restwelt hat keinen Politikpfad und deshalb keinen Anleihekurs.
    ERWARTE_ABBRUCH(anleihekurs(z, konst, Gebiet::RW));
    ERWARTE_ABBRUCH(anleihewert(z, konst, Gebiet::RW));
}

}  // namespace

namespace {

// ---------------------------------------------------------------------------
// T48 Nr. 14 und Nr. 8 -- Fondsanteil und Korbbestand
// ---------------------------------------------------------------------------

void probe_fondsanteil_und_korbbestand()
{
    Rohling r;
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                SektorGroesse::Kapitalstock), 1'000'000);
    r.lege(stelle_position(steckplatz_sektor(Gebiet::US, Sektor::Landwirtschaft)), -2);
    r.lege(stelle_beteiligung(Gebiet::US, Sektor::Landwirtschaft, BeteiligungsFeld::Anteil), 50);

    Konstanten konst = K_GRUND;
    konst.stufenweite = 100;

    const Zustand& z = r;

    // Der Betrag der Stufenzahl geht ein, nicht ihr Vorzeichen: 2 mal 100 plus 50.
    PRUEFE(fondsanteil(z, konst, Gebiet::US, Sektor::Landwirtschaft) == 250);
    PRUEFE(korbwert(z, Gebiet::US, Sektor::Landwirtschaft) == 1'000'000);

    // Der Korbbestand: 1.000.000 mal 250 Zehntausendstel sind 25.000.
    PRUEFE(korbbestand(z, konst) == 25'000);

    // Waehrungen tragen keine Kapitalisierung (T33 Punkt 1). Eine Waehrungsposition mit
    // nachweislich positivem Marktwert darf den Korbbestand nicht bewegen.
    r.lege(stelle_handel(Gebiet::CN, Gebiet::DE, Sektor::Industrie), 900'000);
    r.lege(stelle_position(steckplatz_waehrung(Gebiet::CN)), 5);
    PRUEFE(waehrungswert(z, Gebiet::CN) == 900'000);
    PRUEFE(positionswert(z, konst, steckplatz_waehrung(Gebiet::CN)) != 0);
    PRUEFE(korbbestand(z, konst) == 25'000);

    // Eine Anleiheposition dagegen geht ein -- und ohne Beteiligungsanteil, weil es
    // Beteiligungen nach T15 nur an den zwoelf Land-mal-Sektor-Koerben gibt.
    r.lege(stelle_sektorgroesse(Gebiet::DE, Sektor::Industrie, SektorGroesse::Wertschoepfung),
           2'000'000);
    r.lege(stelle_aggregat(Gebiet::DE, Aggregat::Staatsschuld), 10'000);
    r.lege(stelle_position(steckplatz_anleihe(Gebiet::DE)), 3);
    PRUEFE(anleihewert(z, konst, Gebiet::DE) == 2'000'000);
    // 2.000.000 mal (3 mal 100) Zehntausendstel sind 60.000, dazu die 25.000 von oben.
    PRUEFE(korbbestand(z, konst) == 85'000);
}

// ---------------------------------------------------------------------------
// T39 -- der Landespreis ist der Wert am Ende der Vorrunde
// ---------------------------------------------------------------------------

void probe_landespreis_liest_die_vorrunde()
{
    Rohling r;
    const Index platz = stelle_sektorgroesse(Gebiet::DE, Sektor::Industrie, SektorGroesse::Preis);
    r.lege(platz, 12'500);

    const Zustand& z = r;
    Schreiber schreiber{z, Modus::Spielmodus, 1};

    PRUEFE(landespreis(schreiber, Gebiet::DE, Sektor::Industrie) == 12'500);

    // Jetzt schreibt die Runde einen neuen Preis auf dieselbe Adresse.
    schreiber.setze(platz, 20'000, Ursache::marktraeumung(Sektor::Industrie), 0, 0);

    // Positivkontrolle: Der neue Wert steht wirklich im entstehenden Zustand.
    PRUEFE(schreiber.lies_neu(platz) == 20'000);

    // Und die eigentliche Aussage: Der Landespreis bleibt der alte. Waere es anders,
    // haenge das Ergebnis der Marktraeumung an der Reihenfolge der sechs Schritte,
    // ohne dass irgendwo stuende, dass es das tut.
    PRUEFE(landespreis(schreiber, Gebiet::DE, Sektor::Industrie) == 12'500);
}

// ---------------------------------------------------------------------------
// T47 -- die einzige Stelle, an der ein i64 ueberlaufen kann
// ---------------------------------------------------------------------------

void probe_ueberlauf_an_der_skalengrenze()
{
    // Positivkontrolle: Ein Korb von 9 Billionen Tausend USD geht glatt durch.
    Rohling heil;
    heil.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Industrie, SektorGroesse::Kapitalstock),
              9'000'000'000'000);
    heil.lege(stelle_beteiligung(Gebiet::US, Sektor::Industrie, BeteiligungsFeld::Anteil),
              10'000);
    PRUEFE(beteiligung_wert(heil, K_GRUND, Gebiet::US, Sektor::Industrie)
           == 900'000'000'000'000'000);

    // Und der Abbruch: 93 Billionen Tausend USD liegen oberhalb der Schranke von rund
    // 9,2e13, ab der der Faktor 100.000 den Bereich von i64 verlaesst. Ohne den
    // Waechter aus T7 waere das ein stiller Umbruch mitten im Fondsvermoegen.
    Rohling zu_gross;
    zu_gross.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Industrie,
                                       SektorGroesse::Kapitalstock),
                  93'000'000'000'000);
    zu_gross.lege(stelle_beteiligung(Gebiet::US, Sektor::Industrie, BeteiligungsFeld::Anteil),
                  10'000);
    ERWARTE_ABBRUCH(beteiligung_wert(zu_gross, K_GRUND, Gebiet::US, Sektor::Industrie));
}

// ---------------------------------------------------------------------------
// Die Randfaelle der Steckplatztabelle
// ---------------------------------------------------------------------------

void probe_steckplatzraender()
{
    Rohling r;
    const Zustand& z = r;

    // Der dauerhaft leere Steckplatz aus T16 traegt keine Stufen und ist deshalb null
    // wert -- die Formel ist dort ohne Wirkung, nicht ausgenommen.
    PRUEFE(positionswert(z, K_GRUND, steckplatz_waehrung(Gebiet::US)) == 0);

    // Ein Platz ausserhalb der zwanzig ist ein Rechenfehler des Aufrufers.
    ERWARTE_ABBRUCH(markt(z, K_GRUND, static_cast<Steckplatz>(STECKPLAETZE)));
    ERWARTE_ABBRUCH(positionswert(z, K_GRUND, static_cast<Steckplatz>(STECKPLAETZE + 7)));

    // Beteiligungen gibt es nur an spielbaren Laendern.
    ERWARTE_ABBRUCH(beteiligung_wert(z, K_GRUND, Gebiet::RW, Sektor::Industrie));
    ERWARTE_ABBRUCH(fondsanteil(z, K_GRUND, Gebiet::RW, Sektor::Industrie));

    // Der Korbwert dagegen besteht fuer alle fuenf Gebiete: Kapitalstock und
    // Sektorpreis hat auch die Restwelt.
    PRUEFE(korbwert(z, Gebiet::RW, Sektor::Industrie) == 0);
}

}  // namespace

namespace {

// ---------------------------------------------------------------------------
// Paket 0088 -- vier Vorgaben, die sich bis hierher verletzen liessen
// ---------------------------------------------------------------------------
//
// Der `kern-pruefer` hat am 2026-09-04 dreiundzwanzig Mutationen an `src/werte.cpp`
// einzeln gegen alle zwoelf Proben des Kerns gefahren. Neunzehn wurden rot; vier
// **Verletzungen einer schriftlichen Vorgabe** blieben gruen. Die vier stehen hier,
// jede mit der Mutation, gegen die sie gerichtet ist, im Kopfkommentar.
//
// Alle vier sind vom selben Bautyp, den dieser Datei ihr Kopf vorgibt: die verworfene
// Form daneben und als **andere Zahl** ausgeschrieben. Eine Zusage, deren Gegenzahl
// nicht dasteht, prueft die Rechnung und nicht die Entscheidung -- und genau daran sind
// die vier bisher durchgerutscht.

// ---------------------------------------------------------------------------
// 1. T47, T50 -- die Skalengrenze sitzt am AEUSSERSTEN Aufruf
// ---------------------------------------------------------------------------
//
// Mutation, gegen die diese Pruefung gerichtet ist: in `beteiligung_wert_aus` die
// Umrechnung nach innen ziehen -- `mal_geteilt(tsd_in_cent(korb), anteil, 10'000)`,
// danach der Abschlag, und kein `tsd_in_cent` mehr aussen.
//
// Die Zahlenprobe aus T47 (`probe_zahlenprobe_t47`) faengt das nicht: Dort geht
// 21.000.000.000 * 20 / 10.000 restlos auf, und wo nichts gerundet wird, liefern beide
// Stellen dieselbe Zahl. Gebraucht werden deshalb Zahlen **mit Rest** -- dieselbe
// Bauart, die `probe_rundungsreihenfolge` fuer die Rundungsreihenfolge schon anwendet.

void probe_skalengrenze_am_aeussersten_aufruf()
{
    Rohling r;
    // Korb 3 Tausend USD: Kapitalstock 3, Sektorpreis und Wechselkurs auf ihrem
    // Startwert 10.000.
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Industrie, SektorGroesse::Kapitalstock), 3);
    r.lege(stelle_beteiligung(Gebiet::US, Sektor::Industrie, BeteiligungsFeld::Anteil), 3'333);

    const Zustand& z = r;

    // Positivkontrolle: der Korb ist wirklich 3, sonst misst unten nichts.
    PRUEFE(korbwert(z, Gebiet::US, Sektor::Industrie) == 3);

    // Verbindlich (T47): innen der Korbanteil in Zehntausendsteln, aussen die Skala.
    //   innen = runde(3 * 3.333 / 10.000) = runde(0,9999) = 1 Tausend USD
    //   -> 1 * 100.000 = 100.000 US-Cent
    PRUEFE(beteiligung_wert(z, K_GRUND, Gebiet::US, Sektor::Industrie) == 100'000);

    // Die verworfene Form als Zahl -- Umrechnung ganz innen:
    //   runde(300.000 * 3.333 / 10.000) = 99.990 US-Cent.
    PRUEFE(mal_geteilt(300'000, 3'333, 10'000) == 99'990);
    PRUEFE(beteiligung_wert(z, K_GRUND, Gebiet::US, Sektor::Industrie) != 99'990);

    // Und dieselbe Aussage noch einmal mit einem Abschlag, der selbst rundet. Sie
    // trifft die zweite denkbare Fehlstelle: eine Umrechnung **zwischen** Korbanteil
    // und Abschlag. Mit Abschlag null waere jene von der richtigen Form nicht zu
    // unterscheiden, weil der Abschlag dann mit 10.000/10.000 multipliziert.
    Konstanten mit_abschlag = K_GRUND;
    mit_abschlag.ausstiegsabschlag = 3'333;  // es bleiben 6.667 Zehntausendstel

    //   verbindlich: runde(1 * 6.667 / 10.000) = 1 -> 100.000 US-Cent, also unveraendert
    PRUEFE(beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie) == 100'000);

    // Umrechnung zwischen Anteil und Abschlag: runde(100.000 * 6.667 / 10.000) = 66.670
    PRUEFE(mal_geteilt(100'000, 6'667, 10'000) == 66'670);
    PRUEFE(beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie) != 66'670);

    // Umrechnung ganz innen: runde(99.990 * 6.667 / 10.000) = 66.663
    PRUEFE(mal_geteilt(99'990, 6'667, 10'000) == 66'663);
    PRUEFE(beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie) != 66'663);
}

// ---------------------------------------------------------------------------
// 2. T48 Nr. 15 -- der Positionswert traegt das VORZEICHEN der Stufenzahl
// ---------------------------------------------------------------------------
//
// Mutation, gegen die diese Pruefung gerichtet ist: in `positionswert_aus`
// `mal(betrag(stufen), je_stufe)` statt `mal(stufen, je_stufe)`.
//
// T48 schreibt fuer Nr. 14 (`fondsanteil`) ausdruecklich `|stufen|` und fuer Nr. 15
// (`positionswert`) ausdruecklich `stufen`. Der Unterschied ist eine Entscheidung des
// Entwurfs, keine Schreibweise: Ein grosser Short bewegt einen Markt wie ein grosser
// Long (deshalb der Betrag), ist aber **negatives Vermoegen** (deshalb das Vorzeichen).
//
// `probe_fondsvermoegen_zweiter_weg` belegt zwar Steckplaetze mit negativen
// Stufenzahlen, haelt aber den gebuendelten Weg gegen den einzelnen -- **beide rufen
// dieselbe Funktion**, also aendern sich beide Seiten gemeinsam. Ein zweiter Rechenweg,
// der die gepruefte Funktion enthaelt, prueft alles ausser ihr selbst. Gebraucht wird
// eine Zusage mit ausgeschriebener **negativer** Zahl.

void probe_positionswert_traegt_das_vorzeichen()
{
    Rohling r;
    const Steckplatz platz = steckplatz_sektor(Gebiet::BR, Sektor::Dienstleistungen);
    r.lege(stelle_sektorgroesse(Gebiet::BR, Sektor::Dienstleistungen,
                                SektorGroesse::Kapitalstock), 1'000'000);
    r.lege(stelle_position(platz), -4);

    Konstanten konst = K_GRUND;
    konst.stufenweite = 250;

    const Zustand& z = r;

    // Positivkontrolle: Markt und Stufenwert sind vom Vorzeichen unberuehrt.
    PRUEFE(markt(z, konst, platz) == 1'000'000);
    PRUEFE(stufenwert(z, konst, platz) == 25'000);

    // Die Aussage, ausgeschrieben: vier Stufen short sind -10^10 US-Cent.
    //   -4 * 25.000 = -100.000 Tausend USD -> -10.000.000.000 US-Cent
    PRUEFE(positionswert(z, konst, platz) == -10'000'000'000);

    // Und die verworfene Form als Zahl: mit dem Betrag stuende hier dasselbe positiv.
    PRUEFE(positionswert(z, konst, platz) != 10'000'000'000);

    // Die Gegenprobe zur Zahl selbst: vier Stufen long sind derselbe Betrag mit dem
    // anderen Vorzeichen. Ohne sie koennte die Zeile oben auch eine zufaellig negative
    // Zwischenrechnung treffen.
    r.lege(stelle_position(platz), 4);
    PRUEFE(positionswert(z, konst, platz) == 10'000'000'000);

    // Warum es zaehlt: Todesart 1 nach `spiel.md` ist `fondsvermoegen <= 0`. Faellt das
    // Vorzeichen weg, ruiniert sich kein Fonds mehr mit Shorts. Kasse und Hebelstand
    // sind null, jeder Beteiligungsanteil ebenfalls -- das Fondsvermoegen ist damit
    // genau dieser eine Positionswert.
    r.lege(stelle_position(platz), -4);
    PRUEFE(fondsvermoegen(z, konst) == -10'000'000'000);
    PRUEFE(fondsvermoegen(z, konst) < 0);
}

// ---------------------------------------------------------------------------
// 3. T33 Punkt 1, T48 Nr. 7 -- der Marktkorb enthaelt KEINE Waehrungen
// ---------------------------------------------------------------------------
//
// Mutation, gegen die diese Pruefung gerichtet ist: in `marktkorb` neben
// `anleihewert_zwei` auch `waehrungswert` je Land aufaddieren.
//
// `probe_marktkorb_zwei_quellen` laesst alle Handelsstroeme auf null; damit ist jeder
// Waehrungswert null und der zusaetzliche Summand unsichtbar. Diese Probe braucht einen
// Zustand mit **nachweislich positivem** Waehrungswert -- so, wie
// `probe_fondsanteil_und_korbbestand` es fuer den Korbbestand schon vormacht.
//
// Wirkung, falls verletzt: Der Marktkorb waere dauerhaft zu gross, und mit ihm sind
// `markt.rendite`, `markt.wert` und `fonds.marktanteil` falsch -- Mass 1 und Mass 3.

void probe_marktkorb_ohne_waehrungen()
{
    Rohling r;

    // Der Korbteil: ein einziger Korb mit 700, alle uebrigen elf auf null.
    r.lege(stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                SektorGroesse::Kapitalstock), 700);

    // Der Anleiheteil: allein Deutschland traegt bei -- Wertschoepfung 2.000.000 bei
    // einer Schuldenquote von 10.000 Basispunkten, also 100 Prozent.
    r.lege(stelle_sektorgroesse(Gebiet::DE, Sektor::Industrie,
                                SektorGroesse::Wertschoepfung), 2'000'000);
    r.lege(stelle_aggregat(Gebiet::DE, Aggregat::Staatsschuld), 10'000);

    // Der Waehrungsteil, der **nicht** eingehen darf: ein Handelsstrom zwischen CN und
    // DE macht zwei der vier Waehrungen nachweislich wertvoll.
    r.lege(stelle_handel(Gebiet::CN, Gebiet::DE, Sektor::Industrie), 900'000);

    const Zustand& z = r;

    // Positivkontrollen: die drei Bestandteile einzeln, jeder ungleich null.
    PRUEFE(korbwert(z, Gebiet::US, Sektor::Landwirtschaft) == 700);
    PRUEFE(anleihewert(z, K_GRUND, Gebiet::DE) == 2'000'000);
    PRUEFE(waehrungswert(z, Gebiet::CN) == 900'000);
    PRUEFE(waehrungswert(z, Gebiet::DE) == 900'000);
    PRUEFE(waehrungswert(z, Gebiet::US) == 0);
    PRUEFE(waehrungswert(z, Gebiet::BR) == 0);

    // Die Aussage: zwoelf Koerbe plus vier Anleihen, sonst nichts.
    PRUEFE(marktkorb(z, z, K_GRUND) == 2'000'700);

    // Und die verworfene Form als Zahl: mit den vier Waehrungen kaemen 1.800.000 dazu.
    PRUEFE(marktkorb(z, z, K_GRUND) != 3'800'700);
}

// ---------------------------------------------------------------------------
// 4. T48 Nr. 4 -- der Waehrungswert nimmt den festen Kurs 10.000
// ---------------------------------------------------------------------------
//
// Mutation, gegen die diese Pruefung gerichtet ist: in `waehrungswert` statt des
// Literals 10.000 den Wechselkurs des Gebiets als Kurs einsetzen.
//
// Dann kuerzt sich der Wechselkurs gegen sich selbst weg, und der Waehrungsmarkt haengt
// nicht mehr an der einen Groesse, die eine Waehrung ueberhaupt bewegt. Unsichtbar
// bleibt es, weil die Grundbelegung jeden Wechselkurs auf seinem Startwert 10.000
// stehen laesst -- genau dort sind beide Formen gleich. Diese Probe braucht deshalb
// Wechselkurse **ungleich** 10.000, und zwar in beide Richtungen.

void probe_waehrungswert_fester_kurs()
{
    Rohling r;
    r.lege(stelle_handel(Gebiet::US, Gebiet::CN, Sektor::Landwirtschaft), 600'000);
    r.lege(stelle_handel(Gebiet::DE, Gebiet::BR, Sektor::Industrie), 400'000);

    // Eine schwache und eine starke Waehrung, beide abseits des Startwerts.
    r.lege(stelle_aggregat(Gebiet::US, Aggregat::Wechselkurs), 5'000);
    r.lege(stelle_aggregat(Gebiet::CN, Aggregat::Wechselkurs), 20'000);

    const Zustand& z = r;

    // Positivkontrolle: das Handelsvolumen ist dasselbe, nur der Wechselkurs trennt die
    // beiden Faelle. Ohne diese Zeile koennte der Unterschied unten auch am Volumen
    // liegen.
    PRUEFE(handelsvolumen(z, Gebiet::US) == 600'000);
    PRUEFE(handelsvolumen(z, Gebiet::CN) == 600'000);

    // Die Aussage: Menge mal festem Kurs 10.000, geteilt durch den Wechselkurs.
    //   US: 600.000 * 10.000 / 5.000  = 1.200.000
    //   CN: 600.000 * 10.000 / 20.000 =   300.000
    PRUEFE(waehrungswert(z, Gebiet::US) == 1'200'000);
    PRUEFE(waehrungswert(z, Gebiet::CN) == 300'000);

    // Die verworfene Form als Zahl: mit dem Wechselkurs als Kurs kuerzte er sich weg und
    // beide stuenden auf ihrem Handelsvolumen -- dieselbe Zahl fuer zwei Waehrungen, die
    // sich um den Faktor vier unterscheiden.
    PRUEFE(waehrungswert(z, Gebiet::US) != 600'000);
    PRUEFE(waehrungswert(z, Gebiet::CN) != 600'000);

    // Und warum die Grundbelegung es nicht sieht: Steht der Wechselkurs auf seinem
    // Startwert 10.000, sind beide Formen dieselbe Rechnung. Deutschland ist unberuehrt
    // geblieben und zeigt genau das.
    PRUEFE(handelsvolumen(z, Gebiet::DE) == 400'000);
    PRUEFE(waehrungswert(z, Gebiet::DE) == 400'000);
}

}  // namespace

int main()
{
    probe_zahlenprobe_t47();
    probe_wechselkursschranke();
    probe_leerer_steckplatz_rechnet_nicht();
    probe_rundungsreihenfolge();
    probe_fondsvermoegen_zweiter_weg();
    probe_marktkorb_zwei_quellen();
    probe_handelsvolumen_beide_richtungen();
    probe_bip_schuld_anleihekurs();
    probe_fondsanteil_und_korbbestand();
    probe_landespreis_liest_die_vorrunde();
    probe_ueberlauf_an_der_skalengrenze();
    probe_steckplatzraender();

    // Paket 0088 -- die vier Vorgaben, die bis dahin unbelegt waren.
    probe_skalengrenze_am_aeussersten_aufruf();
    probe_positionswert_traegt_das_vorzeichen();
    probe_marktkorb_ohne_waehrungen();
    probe_waehrungswert_fester_kurs();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    return 0;
}
