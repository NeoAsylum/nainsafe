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

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    return 0;
}
