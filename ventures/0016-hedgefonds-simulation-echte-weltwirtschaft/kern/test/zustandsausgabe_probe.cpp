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

#include <array>
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

/// Schreibt **genau eine** Zeile eines Blattes ins Protokoll.
///
/// Ein Zeiger auf einen Zeilenanfang zeigt zugleich auf den ganzen Rest des Blattes;
/// wer ihn ungekuerzt ausgibt, schreibt hundert Zeilen, wo eine gemeint war. Die Laenge
/// bis zur naechsten Zeilenschaltung steht deshalb im Formatwort.
void schreibe_zeile(const char* beschriftung, const char* zeilenanfang)
{
    if (zeilenanfang == nullptr) {
        std::fprintf(stdout, "%s: (nicht gefunden)\n", beschriftung);
        return;
    }
    int laenge = 0;
    while (zeilenanfang[laenge] != '\0' && zeilenanfang[laenge] != '\n') {
        ++laenge;
    }
    std::fprintf(stdout, "%s:\n  %.*s\n", beschriftung, laenge, zeilenanfang);
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

int main()
{
    // -----------------------------------------------------------------------
    // 1. Die Vorbedingung des Deckungsnachweises
    // -----------------------------------------------------------------------
    //
    // Der Nachweis unten sucht jede Adresse als Zeichenfolge in den Blaettern. Das ist
    // nur dann ein Beleg, wenn keine Adresse in einer anderen steckt: Steckte sie, faende
    // die Suche nach der einen die andere, und die Deckung waere gruen, ohne dass die
    // gesuchte Adresse je ausgegeben wurde. Geprueft werden alle 310 mal 310 Paare.
    {
        std::size_t verschachtelt = 0;
        for (Index a = 0; a < FELDER; ++a) {
            for (Index b = 0; b < FELDER; ++b) {
                if (a == b) {
                    continue;
                }
                if (enthaelt(kern::zustand::index_zu_adresse(b),
                             kern::zustand::index_zu_adresse(a))) {
                    ++verschachtelt;
                    std::fprintf(stderr, "verschachtelt: %s steckt in %s\n",
                                 kern::zustand::index_zu_adresse(a),
                                 kern::zustand::index_zu_adresse(b));
                }
            }
        }
        PRUEFE(verschachtelt == 0);
        std::fprintf(stdout, "Vorbedingung: keine der 310 Adressen steckt in einer anderen.\n");

        // Die Gegenprobe, ohne die die Zeile darueber nur besagte, dass `enthaelt`
        // immer falsch liefert.
        PRUEFE(enthaelt("land.US.sektor.1.preis", "sektor.1"));
        PRUEFE(!enthaelt("land.US.sektor.1.preis", "sektor.2"));
    }

    // -----------------------------------------------------------------------
    // 2. Die zehn Bereiche teilen die 310 Adressen genau auf
    // -----------------------------------------------------------------------
    //
    // Genau einer, nicht mindestens einer: Ein Bereich, der einen anderen ueberdeckte,
    // liesse die Deckungsprobe darunter trotzdem gruen laufen und die Summe unten
    // trotzdem stimmen -- gezaehlt wird deshalb je Adresse, nicht je Bereich.
    {
        std::size_t ohne_bereich  = 0;
        std::size_t mehrfach      = 0;
        std::size_t zusammen      = 0;
        for (Index platz = 0; platz < FELDER; ++platz) {
            const char* adresse = kern::zustand::index_zu_adresse(platz);
            std::size_t treffer = 0;
            for (std::size_t b = 0; b < BEREICHE; ++b) {
                if (gehoert_zum_bereich(adresse, BEREICH_NAME[b])) {
                    ++treffer;
                }
            }
            zusammen += treffer;
            if (treffer == 0) {
                ++ohne_bereich;
                std::fprintf(stderr, "ohne Bereich: %s\n", adresse);
            }
            if (treffer > 1) {
                ++mehrfach;
                std::fprintf(stderr, "in mehreren Bereichen: %s\n", adresse);
            }
        }
        PRUEFE(ohne_bereich == 0);
        PRUEFE(mehrfach == 0);
        PRUEFE(zusammen == FELDER);
        std::fprintf(stdout, "Bereiche: %zu Namen teilen die %zu Adressen lueckenlos.\n",
                     BEREICHE, FELDER);
    }

    Zustand tragfaehig;
    belege_tragfaehig(tragfaehig);
    const kern::werte::Konstanten konst = tragfaehige_konstanten();

    // -----------------------------------------------------------------------
    // 3. Die Abnahmebedingung: jede der 310 Adressen kommt in einer Ausgabe vor
    // -----------------------------------------------------------------------
    //
    // Gepruefte Menge ist die Vereinigung der drei Ebenen, so wie die Bedingung sie
    // nennt. Die Blaetter entstehen einzeln und nicht als ein grosser Text: Ein
    // `Adressblatt` misst rund 60 kB, und zehn davon nebeneinander waeren eine halbe
    // Million Bytes auf dem Stapel, ohne dass der Nachweis dadurch staerker wuerde.
    //
    // Der Unterschied laeuft gegen einen zweiten Zustand, in dem **jedes** Feld einen
    // anderen Wert traegt -- sonst haette er nichts zu berichten und truege zur Deckung
    // nichts bei. Er ist damit zugleich die Probe darauf, dass die Unterschiedsebene
    // alle 310 nennen kann und nicht nur die ersten paar.
    Zustand vollstaendig_anders;
    {
        Startbelegung zugang{vollstaendig_anders};
        for (Index platz = 0; platz < FELDER; ++platz) {
            zugang.setze(platz, static_cast<i64>(platz) + 1);
        }
    }

    {
        std::array<bool, FELDER> gesehen{};

        const auto vermerke = [&gesehen](const char* blatt) {
            for (Index platz = 0; platz < FELDER; ++platz) {
                if (!gesehen[platz] && enthaelt(blatt, kern::zustand::index_zu_adresse(platz))) {
                    gesehen[platz] = true;
                }
            }
        };

        {
            const auto blatt = uebersicht(tragfaehig, konst);
            vermerke(blatt.fertig());
        }
        for (std::size_t b = 0; b < BEREICHE; ++b) {
            const auto blatt = detail(tragfaehig, BEREICH_NAME[b]);
            vermerke(blatt.fertig());
        }
        {
            const auto blatt = diff(tragfaehig, vollstaendig_anders);
            vermerke(blatt.fertig());
        }

        std::size_t fehlend = 0;
        for (Index platz = 0; platz < FELDER; ++platz) {
            if (!gesehen[platz]) {
                ++fehlend;
                std::fprintf(stderr, "in keiner Ausgabe: %s\n",
                             kern::zustand::index_zu_adresse(platz));
            }
        }
        PRUEFE(fehlend == 0);
        std::fprintf(stdout,
                     "Deckung: alle %zu Adressen kommen in mindestens einer der drei "
                     "Ausgaben vor.\n",
                     FELDER);
    }

    // -----------------------------------------------------------------------
    // 3b. Dieselbe Deckung je Ebene statt nur in der Vereinigung
    // -----------------------------------------------------------------------
    //
    // Der Nachweis oben erfuellt die Abnahme im Wortlaut -- "in mindestens einer der
    // drei Ausgaben" --, und genau darin liegt seine Schwaeche: Der Unterschied gegen
    // einen durchweg anderen Zustand nennt schon allein alle 310. Eine Detailebene, die
    // eine Adresse ueberspringt, bliebe darunter unsichtbar, weil eine andere Ebene sie
    // mitbringt. Hier steht deshalb die schaerfere Aussage, je Bereich: Sein Blatt nennt
    // **genau** die Adressen, die ihm nach `gehoert_zum_bereich` gehoeren -- keine
    // weniger und keine mehr -- und seine Schlusszahl ist dieselbe Zahl.
    {
        std::size_t abweichungen = 0;
        std::size_t zusammen     = 0;
        for (std::size_t b = 0; b < BEREICHE; ++b) {
            const auto  blatt      = detail(tragfaehig, BEREICH_NAME[b]);
            std::size_t im_bereich = 0;
            for (Index platz = 0; platz < FELDER; ++platz) {
                const char* adresse = kern::zustand::index_zu_adresse(platz);
                const bool  soll    = gehoert_zum_bereich(adresse, BEREICH_NAME[b]);
                const bool  ist     = enthaelt(blatt.fertig(), adresse);
                if (soll != ist) {
                    ++abweichungen;
                    std::fprintf(stderr, "Bereich %s: %s soll %d, ist %d\n", BEREICH_NAME[b],
                                 adresse, static_cast<int>(soll), static_cast<int>(ist));
                }
                if (soll) {
                    ++im_bereich;
                }
            }
            zusammen += im_bereich;

            Ausgabe<96> nadel;
            nadel.zahl(static_cast<i64>(im_bereich));
            nadel.text(" von ");
            nadel.zahl(static_cast<i64>(FELDER));
            nadel.text(" Adressen in diesem Bereich.");
            PRUEFE(enthaelt(blatt.fertig(), nadel.fertig()));
            PRUEFE(!blatt.abgeschnitten());
        }
        PRUEFE(abweichungen == 0);
        PRUEFE(zusammen == FELDER);
        std::fprintf(stdout,
                     "Detailebene allein: die zehn Bereiche nennen zusammen genau die %zu "
                     "Adressen.\n",
                     FELDER);
    }

    // -----------------------------------------------------------------------
    // 4. Klasse und Herkunft an den Stellen, an denen die Regel nicht gleichfoermig ist
    // -----------------------------------------------------------------------
    //
    // Die Mengen stimmen schon beim Uebersetzen. Was eine Abzaehlung nicht zeigt, ist,
    // ob die richtige Adresse die richtige Ausnahme traegt: Eine vertauschte Zuordnung
    // zwischen zwei Adressen derselben Klasse laesst jede Zahl unveraendert. Geprueft
    // wird deshalb dort, wo T45 und T46 von der Regel abweichen -- und daneben jeweils
    // die Geschwisteradresse, die es nicht tut.
    {
        const auto erwarte = [](const char* adresse, Skalenklasse klasse,
                                Herkunftsart herkunft, int zeile) {
            const auto fund = kern::zustand::adresse_zu_index(adresse);
            pruefe(fund.gefunden, adresse, zeile);
            if (!fund.gefunden) {
                return;
            }
            pruefe(skalenklasse_von(fund.index) == klasse, adresse, zeile);
            pruefe(herkunft_von(fund.index) == herkunft, adresse, zeile);
        };

        // Der Numeraire und sein Geschwister: dieselbe Klasse, verschiedene Herkunft.
        erwarte("land.US.wechselkurs", Skalenklasse::Wechselkurs, Herkunftsart::Vorgabe,
                __LINE__);
        erwarte("land.CN.wechselkurs", Skalenklasse::Wechselkurs, Herkunftsart::Datenanker,
                __LINE__);
        erwarte("restwelt.wechselkurs", Skalenklasse::Wechselkurs, Herkunftsart::Vorgabe,
                __LINE__);

        // Die vier Restweltaggregate, die keine Modellregel liest -- und dieselbe
        // Groesse bei einem spielbaren Land.
        erwarte("restwelt.leitzins", Skalenklasse::Raten, Herkunftsart::Vorgabe, __LINE__);
        erwarte("restwelt.staatsschuld", Skalenklasse::Raten, Herkunftsart::Vorgabe, __LINE__);
        erwarte("restwelt.haushaltssaldo", Skalenklasse::Raten, Herkunftsart::Vorgabe, __LINE__);
        erwarte("restwelt.inflation", Skalenklasse::Raten, Herkunftsart::Vorgabe, __LINE__);
        erwarte("land.DE.leitzins", Skalenklasse::Raten, Herkunftsart::Datenanker, __LINE__);
        erwarte("restwelt.basiswechsel", Skalenklasse::Zaehler, Herkunftsart::Vorgabe, __LINE__);
        erwarte("land.DE.basiswechsel", Skalenklasse::Zaehler, Herkunftsart::Vorgabe, __LINE__);

        // Das eine Instrument mit Stufenskala und ohne Datenanker, daneben eines mit.
        erwarte("land.BR.instrument.regulierung.stand", Skalenklasse::Instrumentenstufe,
                Herkunftsart::Parameter, __LINE__);
        erwarte("land.BR.instrument.zoll.stand", Skalenklasse::Raten, Herkunftsart::Datenanker,
                __LINE__);
        erwarte("land.BR.instrument.zoll.druck", Skalenklasse::Lobbydruck, Herkunftsart::Entwurf,
                __LINE__);
        erwarte("land.BR.instrument.zoll.restverzoegerung", Skalenklasse::Zaehler,
                Herkunftsart::Entwurf, __LINE__);

        // Die beiden Manifestadressen -- die einzigen zwei im ganzen Zustand.
        erwarte("markt.wert", Skalenklasse::Volkswirtschaftlich, Herkunftsart::Manifest,
                __LINE__);
        erwarte("partie.jahrgang_id", Skalenklasse::Kennung, Herkunftsart::Manifest, __LINE__);
        erwarte("markt.rendite", Skalenklasse::Raten, Herkunftsart::Entwurf, __LINE__);
        erwarte("partie.parameter_pruefsumme", Skalenklasse::Kennung, Herkunftsart::Parameter,
                __LINE__);

        // Fondsgeld: zwei aus `parameter.toml`, eines aus der Entwurfstabelle.
        erwarte("fonds.kasse", Skalenklasse::Fondsgeld, Herkunftsart::Parameter, __LINE__);
        erwarte("fonds.anlegerbestand", Skalenklasse::Fondsgeld, Herkunftsart::Parameter,
                __LINE__);
        erwarte("fonds.hebelstand", Skalenklasse::Fondsgeld, Herkunftsart::Entwurf, __LINE__);
        erwarte("land.US.zustimmung", Skalenklasse::Anteile, Herkunftsart::Parameter, __LINE__);

        // Der dauerhaft leere Steckplatz ist eine Adresse wie jede andere (T16).
        erwarte("fonds.position.waehrung.US", Skalenklasse::Zaehler, Herkunftsart::Entwurf,
                __LINE__);

        ERWARTE_ABBRUCH((void)skalenklasse_von(FELDER));
        ERWARTE_ABBRUCH((void)herkunft_von(FELDER));
    }

    // -----------------------------------------------------------------------
    // 5. Die Grenzbedingung des Bereichsnamens
    // -----------------------------------------------------------------------
    //
    // Ohne sie waere jeder abgeschnittene Name ein Bereich, und `detail("land.U")`
    // lieferte 44 Zeilen unter einer Ueberschrift, die es nicht gibt.
    {
        PRUEFE(gehoert_zum_bereich("land.US.sektor.1.preis", "land.US"));
        PRUEFE(gehoert_zum_bereich("land.US.sektor.1.preis", "land.US.sektor.1"));
        PRUEFE(gehoert_zum_bereich("markt.wert", "markt"));
        PRUEFE(gehoert_zum_bereich("markt.wert", "markt.wert"));   // ganze Adresse
        PRUEFE(!gehoert_zum_bereich("land.US.sektor.1.preis", "land.U"));
        PRUEFE(!gehoert_zum_bereich("land.US.sektor.1.preis", "land.US.sektor.11"));
        PRUEFE(!gehoert_zum_bereich("markt.wert", "markt.werte"));  // laenger als die Adresse
        PRUEFE(!gehoert_zum_bereich("markt.wert", ""));
        PRUEFE(!gehoert_zum_bereich("markt.wert", nullptr));
        PRUEFE(!gehoert_zum_bereich(nullptr, "markt"));

        // Und dieselbe Grenze am erzeugten Blatt: Der abgeschnittene Name findet nichts.
        const auto leer = detail(tragfaehig, "land.U");
        PRUEFE(enthaelt(leer.fertig(), "Kein Vorspann dieses Namens"));
        PRUEFE(enthaelt(leer.fertig(), "0 von 310 Adressen in diesem Bereich."));
        PRUEFE(!leer.abgeschnitten());

        // Positivkontrolle daneben: Derselbe Aufruf mit dem vollstaendigen Namen liefert
        // die 44 Adressen des Landes. Ohne sie belegte die Zeile darueber nur, dass
        // `detail` etwas nicht findet.
        const auto voll = detail(tragfaehig, "land.US");
        PRUEFE(enthaelt(voll.fertig(), "44 von 310 Adressen in diesem Bereich."));
        PRUEFE(enthaelt(voll.fertig(), "land.US.instrument.regulierung.restverzoegerung"));
        PRUEFE(!enthaelt(voll.fertig(), "land.CN."));
        PRUEFE(!voll.abgeschnitten());

        // Die Detailzeile traegt Wert, Klasse mit Einheit und Herkunft -- die drei
        // Angaben, wegen deren die Ebene ueberhaupt existiert.
        PRUEFE(enthaelt(voll.fertig(),
                        "land.US.wechselkurs  =  10000  [K6 Wechselkurs, "
                        "Index gegen USD, Startjahr 10.000]  Herkunft Vorgabe"));
        schreibe_zeile("Detailzeile im Wortlaut", zeile_ab(voll.fertig(), "land.US.wechselkurs"));
    }

    // -----------------------------------------------------------------------
    // 6. Die Uebersicht -- Umfang, Ordnung und die eine Rechnung darin
    // -----------------------------------------------------------------------
    {
        const auto blatt = uebersicht(tragfaehig, konst);
        PRUEFE(blatt.zeilen() <= UEBERSICHT_ZEILEN_MAX);
        PRUEFE(!blatt.abgeschnitten());
        std::fprintf(stdout, "Uebersicht: %zu Zeilen (Grenze %zu), %zu Zeichen.\n",
                     blatt.zeilen(), UEBERSICHT_ZEILEN_MAX, blatt.laenge());

        // Das Fondsvermoegen steht als Zahl da -- verglichen wird gegen dieselbe
        // Rechnung, nicht gegen eine abgeschriebene Zahl: Die Uebersicht soll den Wert
        // **zeigen**, und was er ist, entscheidet `werte` und nicht diese Probe.
        auto vermoegen = als_text(kern::werte::fondsvermoegen(tragfaehig, konst));
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "Fonds | Vermoegen"),
                              vermoegen.fertig()));

        // Die Ordnung der fuenf Gebietszeilen, und zwar gegen `index_zu_adresse` statt
        // gegen eine abgeschriebene Liste: Das Kuerzel eines Gebiets steht in seiner
        // eigenen Handelsadresse (`handel.<von>.<nach>.<sektor>`), und von dort wird es
        // gelesen. Wer die Kuerzel im Modul umsortiert, macht diese Probe rot.
        for (std::size_t g = 0; g < GEBIETE; ++g) {
            const std::size_t von     = (g == 0) ? 1 : 0;
            const char*       handel  = kern::zustand::index_zu_adresse(
                kern::zustand::stelle_handel(static_cast<Gebiet>(von), static_cast<Gebiet>(g),
                                             Sektor::Landwirtschaft));
            const char kuerzel[3] = {handel[10], handel[11], '\0'};

            const char* zeile = zeile_ab(blatt.fertig(), kuerzel);
            PRUEFE(zeile != nullptr);

            Ausgabe<64> nadel;
            nadel.text("Wechselkurs ");
            nadel.zahl(kurs_von(g));
            PRUEFE(zeile_enthaelt(zeile, nadel.fertig()));
        }
        std::fprintf(stdout,
                     "Uebersicht: fuenf Gebietszeilen in der Ordnung aus T9, jede mit "
                     "ihrem eigenen Wechselkurs.\n");

        // Die Restwelt hat keine Instrumente und keinen Einfluss -- ihre Spalten bleiben
        // leer statt null. Daneben die Gegenprobe an einem spielbaren Land.
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "RW"), "Zins - "));
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "US"), "Zins 250 "));
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "US"), "Einfluss 1000 "));

        // Runde und Mandatsstand -- die beiden Groessen, die das Arbeitspaket unter
        // "Stand gegenueber der Siegbedingung" nennt, soweit sie im Zustand stehen.
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "Partie"), "Runde 0"));
        PRUEFE(zeile_enthaelt(zeile_ab(blatt.fertig(), "Partie"), "Mandatsstand 0"));

        std::fprintf(stdout, "--- Uebersicht im Wortlaut ---\n%s------------------------\n",
                     blatt.fertig());
    }

    // -----------------------------------------------------------------------
    // 7. Und die Gegenprobe zur Zeile darueber: die Uebersicht rechnet wirklich
    // -----------------------------------------------------------------------
    //
    // Die Positivkontrolle steht oben -- derselbe Aufruf auf demselben Zustand ist
    // gelaufen. Hier reisst ein einziger Wert die Schranke aus T47, und die Ebene bricht
    // ab, statt eine Zahl zu zeigen, die niemand gerechnet hat. Ohne diese Haelfte
    // belegte die obere nur, dass irgendetwas herauskam.
    {
        Zustand kaputt = tragfaehig;
        startwert(kaputt, kern::zustand::stelle_aggregat(Gebiet::CN, Aggregat::Wechselkurs), 0);
        ERWARTE_ABBRUCH((void)uebersicht(kaputt, konst));

        // Detail und Unterschied rechnen nichts und tragen denselben Zustand.
        const auto blatt = detail(kaputt, "land.CN");
        PRUEFE(enthaelt(blatt.fertig(), "land.CN.wechselkurs  =  0"));
        const auto unterschied = diff(tragfaehig, kaputt);
        PRUEFE(enthaelt(unterschied.fertig(), "1 von 310 Adressen geaendert."));
    }

    // -----------------------------------------------------------------------
    // 8. Der Unterschied -- und die Differenz, die keine `i64` ist
    // -----------------------------------------------------------------------
    {
        // Gleich heisst: nichts zu berichten, und das steht ausdruecklich da. Eine leere
        // Ausgabe und eine ohne Befund waeren sonst dasselbe Zeichen.
        const auto gleich = diff(tragfaehig, tragfaehig);
        PRUEFE(enthaelt(gleich.fertig(), "Kein Feld unterscheidet sich"));
        PRUEFE(enthaelt(gleich.fertig(), "0 von 310 Adressen geaendert."));

        // Eine einzelne Aenderung mit allen drei Zahlen.
        Zustand nachher = tragfaehig;
        startwert(nachher, kern::zustand::stelle_fonds(FondsGroesse::Marktanteil), 500);
        const auto eine = diff(tragfaehig, nachher);
        PRUEFE(enthaelt(eine.fertig(),
                        "fonds.marktanteil  alt 420  neu 500  Differenz 80  "
                        "[K4 Anteile, Zehntausendstel]"));
        PRUEFE(enthaelt(eine.fertig(), "1 von 310 Adressen geaendert."));

        // **Die Stelle, an der die Entscheidung fuer `i128` gemessen wird.** Der Abstand
        // zwischen dem kleinsten und dem groessten `i64` ist 18.446.744.073.709.551.615
        // und passt in keine `i64`. Waere die Differenz dort gerechnet worden, stuende
        // unter `-fwrapv` die verworfene Zahl **-1** da -- wohlgeformt, unauffaellig und
        // falsch. Beide Zahlen stehen hier, weil die Zeile sonst die Rechnung pruefte
        // und nicht die Entscheidung.
        Zustand klein;
        Zustand gross;
        startwert(klein, kern::zustand::stelle_fonds(FondsGroesse::Kasse), I64_MIN);
        startwert(gross, kern::zustand::stelle_fonds(FondsGroesse::Kasse), I64_MAX);
        const auto weit = diff(klein, gross);
        PRUEFE(enthaelt(weit.fertig(), "Differenz 18446744073709551615"));
        PRUEFE(!enthaelt(weit.fertig(), "Differenz -1 "));
        PRUEFE(enthaelt(weit.fertig(), "1 von 310 Adressen geaendert."));
        schreibe_zeile("Weite Differenz", zeile_ab(weit.fertig(), "fonds.kasse"));

        // Und die Gegenrichtung, damit das Vorzeichen nicht ungeprueft bleibt.
        const auto rueckwaerts = diff(gross, klein);
        PRUEFE(enthaelt(rueckwaerts.fertig(), "Differenz -18446744073709551615"));

        // Alle 310 auf einmal: Die Ebene kuerzt nicht, und sie laeuft nicht ueber.
        const auto alles = diff(tragfaehig, vollstaendig_anders);
        PRUEFE(enthaelt(alles.fertig(), "310 von 310 Adressen geaendert."));
        PRUEFE(!alles.abgeschnitten());
        PRUEFE(alles.zeilen() == FELDER + 2);  // Kopfzeile, 310 Zeilen, Schlusszeile
        std::fprintf(stdout, "Unterschied ueber alle 310: %zu Zeilen, %zu Zeichen, "
                             "Puffer %zu.\n",
                     alles.zeilen(), alles.laenge(),
                     kern::zustandsausgabe::ADRESSBLATT_ZEICHEN);
    }

    // -----------------------------------------------------------------------
    // 9. Der Puffer am Rand: abgeschnitten statt uebergelaufen, und kenntlich
    // -----------------------------------------------------------------------
    //
    // Der Adressen-Sanitizer sieht nur, was laeuft; deshalb laeuft der Rand hier
    // wirklich an. Geprueft wird an einem kleinen Puffer, weil der Fall an einem
    // 60-kB-Puffer nur mit 60 kB Nutzlast zu erreichen waere -- und die Bauart ist
    // dieselbe.
    {
        Ausgabe<12> eng;
        eng.text("12345678901234567890");
        PRUEFE(eng.abgeschnitten());
        PRUEFE(eng.laenge() == 11);
        PRUEFE(enthaelt(eng.fertig(), Ausgabe<12>::MARKE));
        std::fprintf(stdout, "Abschneiden: \"%s\" (%zu Zeichen, Marke am Ende).\n",
                     eng.fertig(), eng.laenge());

        // Der Zeilenzaehler waechst nicht mehr, wenn nichts mehr hineinpasst -- eine
        // gekuerzte Ausgabe hat weniger Zeilen und nie mehr. Genau deshalb steht in
        // `uebersicht` neben der Zeilengrenze auch die Frage nach dem Abschneiden.
        const std::size_t zeilen_vorher = eng.zeilen();
        eng.zeilenende();
        PRUEFE(eng.zeilen() == zeilen_vorher);

        // Die Gegenprobe: derselbe Puffer, eine Nutzlast, die hineinpasst.
        Ausgabe<12> passt;
        passt.text("1234567890");
        PRUEFE(!passt.abgeschnitten());
        PRUEFE(!enthaelt(passt.fertig(), Ausgabe<12>::MARKE));
        passt.zeilenende();
        PRUEFE(passt.zeilen() == 1);

        // Die Zahlenumwandlung an ihren Raendern, beide Vorzeichen und die Null.
        PRUEFE(enthaelt(als_text(0).fertig(), "0"));
        PRUEFE(enthaelt(als_text(I64_MIN).fertig(), "-9223372036854775808"));
        PRUEFE(enthaelt(als_text(I64_MAX).fertig(), "9223372036854775807"));

        // Ein Nullzeiger ist ein leerer Anhang und kein Absturz.
        Ausgabe<12> nichts;
        nichts.text(nullptr);
        PRUEFE(nichts.laenge() == 0);
        PRUEFE(!nichts.abgeschnitten());
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::zustandsausgabe -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::zustandsausgabe -- %d Probe(n) fehlgeschlagen.\n",
                 fehlgeschlagen);
    return 1;
}
