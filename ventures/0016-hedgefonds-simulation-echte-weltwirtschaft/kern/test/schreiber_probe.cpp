//! Laufende Probe fuer `kern::schreiber`.
//!
//! Die Maskengroessen sind in `src/schreiber.cpp` schon als `static_assert` bewiesen.
//! Diese Probe gibt es fuer das, was ein `static_assert` nicht kann:
//!
//!   1. **Die Abbrueche.** Zweiter Schreibzugriff, `lies_neu` auf eine noch nicht
//!      geschriebene Adresse, fehlende Adresse der Sollmaske, Adresse ausserhalb der
//!      Sollmaske -- jeder davon ist ein Wurf, und ein Wurf laesst sich nur zur
//!      Laufzeit fangen.
//!   2. **Das Testprofil aus ADR 0011, Massnahme 2.** Sie linkt `kern_geprueft`, also
//!      dieselben Quellen mit den Sanitizern. Ein Sanitizer sieht nur, was wirklich
//!      laeuft.
//!   3. **Dass `alt` und `neu` nicht auf demselben Speicher liegen.** Das ist der
//!      Fehler, den T39 ausschliesst, und er ist von aussen nur an zwei verschiedenen
//!      Zahlen zu sehen -- deshalb stehen sie hier ausgeschrieben.
//!   4. **Die Zahlen im Wortlaut.** Was diese Probe ausrechnet, schreibt sie hin.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::schreiber::Bitfeld;
using kern::schreiber::Kette;
using kern::schreiber::Modus;
using kern::schreiber::Schreiber;
using kern::schreiber::Ursache;
using kern::schreiber::UrsacheArt;
using kern::schreiber::Ursachensatz;

using kern::schreiber::sollmaske;
using kern::schreiber::sollmaskengroesse;

using kern::schreiber::AUSSERHALB_WELTLAUF;
using kern::schreiber::KETTE_KAPAZITAET;
using kern::schreiber::MASKE_SPIELMODUS;
using kern::schreiber::MASKE_WELTLAUF;

using kern::zustand::Aggregat;
using kern::zustand::FondsGroesse;
using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Instrument;
using kern::zustand::InstrumentFeld;
using kern::zustand::MarktGroesse;
using kern::zustand::PartieFeld;
using kern::zustand::PolitischeGroesse;
using kern::zustand::Restdauerzaehler;
using kern::zustand::Sektor;
using kern::zustand::SektorGroesse;
using kern::zustand::Zustand;
using kern::zustand::FELDER;

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
    } catch (const std::domain_error& fehler) {
        // Die Meldung wird mitgeschrieben: Die Abnahme verlangt, dass die Adresse
        // ausgeschrieben darin steht, und das sieht man nur, wenn man sie liest.
        std::fprintf(stdout, "  Abbruch wie erwartet (Zeile %d): %s\n", zeile, fehler.what());
        return;
    }
    std::fprintf(stderr, "KEIN ABBRUCH Zeile %d: %s\n", zeile, text);
    ++fehlgeschlagen;
}

/// Nimmt dem Uebersetzer die Konstantenfaltung, damit die Sanitizer die Rechnung
/// wirklich zu sehen bekommen.
i64 undurchsichtig(i64 wert)
{
    volatile i64 zwischenlager = wert;
    return zwischenlager;
}

/// Eine Ursache, die in jeder dieser Proben taugt, wo es auf die Form nicht ankommt.
Ursache irgendeine() { return Ursache::gegenkraft(3); }

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)
#define ERWARTE_ABBRUCH(anweisung)                             \
    erwarte_abbruch([&] { anweisung; }, #anweisung, __LINE__)

namespace {

// ---------------------------------------------------------------------------
// Abnahme 1 -- die sechs Formen der Ursache
// ---------------------------------------------------------------------------

void probe_ursachenformen()
{
    const Ursache a = Ursache::aktion(3);
    PRUEFE(a.art() == UrsacheArt::Aktion);
    PRUEFE(a.aktionsnummer() == 3);

    const Ursache i = Ursache::instrument(Gebiet::BR, Instrument::Zoll);
    PRUEFE(i.art() == UrsacheArt::Instrument);
    PRUEFE(i.land() == Gebiet::BR);
    PRUEFE(i.politikinstrument() == Instrument::Zoll);

    const Ursache g = Ursache::gegenkraft(5);
    PRUEFE(g.art() == UrsacheArt::Gegenkraft);
    PRUEFE(g.gegenkraftart() == 5);

    const Ursache m = Ursache::marktraeumung(Sektor::Dienstleistungen);
    PRUEFE(m.art() == UrsacheArt::Marktraeumung);
    PRUEFE(m.sektor() == Sektor::Dienstleistungen);

    const Ursache v = Ursache::vortrag(309);
    PRUEFE(v.art() == UrsacheArt::Vortrag);
    PRUEFE(v.vortragsadresse() == 309);

    const Ursache j = Ursache::jahrgang();
    PRUEFE(j.art() == UrsacheArt::Jahrgang);

    // Die Voreinstellung ist `Jahrgang`, die einzige Form ohne Beiwert.
    const Ursache leer;
    PRUEFE(leer.art() == UrsacheArt::Jahrgang);
    PRUEFE(leer == j);

    // Der falsche Beiwert gibt keinen Ersatzwert, sondern einen Abbruch.
    ERWARTE_ABBRUCH(static_cast<void>(g.land()));
    ERWARTE_ABBRUCH(static_cast<void>(a.sektor()));
    ERWARTE_ABBRUCH(static_cast<void>(j.vortragsadresse()));
    ERWARTE_ABBRUCH(static_cast<void>(v.aktionsnummer()));

    // Und die Beiwerte selbst sind geprueft: fuenf Aktionsarten, fuenf Gegenkraefte,
    // 310 Adressen, und die Restwelt hat keine Politikinstrumente.
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::aktion(0)));
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::aktion(6)));
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::gegenkraft(0)));
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::gegenkraft(6)));
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::vortrag(FELDER)));
    ERWARTE_ABBRUCH(static_cast<void>(Ursache::instrument(Gebiet::RW, Instrument::Zoll)));
}

// ---------------------------------------------------------------------------
// Abnahme 2 -- der zweite Schreibzugriff und `lies_neu` sterben sofort
// ---------------------------------------------------------------------------

void probe_zweiter_schreibzugriff()
{
    const Index ziel = kern::zustand::stelle_aggregat(Gebiet::DE, Aggregat::Leitzins);

    Zustand start;
    Schreiber schreiber(start, Modus::Spielmodus, 4);

    schreiber.setze(ziel, undurchsichtig(250), Ursache::instrument(Gebiet::DE, Instrument::Leitzins),
                    0, 1000);
    PRUEFE(schreiber.ist_geschrieben(ziel));
    PRUEFE(schreiber.kette().laenge() == 1);

    // T18: derselbe Platz ein zweites Mal in derselben Runde -- harter Fehler, und die
    // Adresse steht ausgeschrieben in der Meldung.
    ERWARTE_ABBRUCH(schreiber.setze(ziel, undurchsichtig(275), irgendeine(), 0, 1000));

    // Der Abbruch hat nichts angefasst: Wert, Bitfeld und Kette stehen wie vorher.
    PRUEFE(schreiber.lies_neu(ziel) == 250);
    PRUEFE(schreiber.kette().laenge() == 1);

    // T39: eine in dieser Runde noch nicht geschriebene Adresse hat keinen Wert dieser
    // Runde -- auch dann nicht, wenn sie in der Vorrunde einen hatte.
    const Index ungeschrieben = kern::zustand::stelle_aggregat(Gebiet::DE, Aggregat::Inflation);
    PRUEFE(!schreiber.ist_geschrieben(ungeschrieben));
    ERWARTE_ABBRUCH(static_cast<void>(schreiber.lies_neu(ungeschrieben)));

    // Ausserhalb der 310 stirbt jeder der drei Wege.
    ERWARTE_ABBRUCH(schreiber.setze(FELDER, 1, irgendeine(), 0, 1000));
    ERWARTE_ABBRUCH(static_cast<void>(schreiber.lies_neu(FELDER)));
    ERWARTE_ABBRUCH(static_cast<void>(schreiber.lies_alt(FELDER)));

    // Eine Wirkung liegt nie vor ihrer Ursache.
    const Index anderes = kern::zustand::stelle_aggregat(Gebiet::DE, Aggregat::Preisniveau);
    ERWARTE_ABBRUCH(schreiber.setze(anderes, 1, irgendeine(), -1, 1000));
    PRUEFE(!schreiber.ist_geschrieben(anderes));
}

// ---------------------------------------------------------------------------
// Abnahme 3 -- `lies_alt` bleibt alt, mit zwei ausgeschriebenen Zahlen
// ---------------------------------------------------------------------------

void probe_alt_bleibt_alt()
{
    const Index ziel = kern::zustand::stelle_sektorgroesse(Gebiet::US, Sektor::Industrie,
                                                           SektorGroesse::Preis);

    Zustand vorrunde;
    vorrunde.schreibe(ziel, 4711);

    Schreiber schreiber(vorrunde, Modus::Spielmodus, 12);
    PRUEFE(schreiber.lies_alt(ziel) == 4711);

    schreiber.setze(ziel, undurchsichtig(815), Ursache::marktraeumung(Sektor::Industrie), 0, 1000);

    // Die beiden Zahlen sind der ganze Nachweis: Laegen `alt` und `neu` auf demselben
    // Speicher, stuende hier zweimal 815.
    PRUEFE(schreiber.lies_alt(ziel) == 4711);
    PRUEFE(schreiber.lies_neu(ziel) == 815);
    std::printf("  lies_alt = %lld, lies_neu = %lld (erwartet 4711 und 815)\n",
                static_cast<long long>(schreiber.lies_alt(ziel)),
                static_cast<long long>(schreiber.lies_neu(ziel)));

    // Und der Ursachensatz traegt beide Zahlen, nicht nur die neue.
    const Ursachensatz& satz = schreiber.kette().eintrag(0);
    PRUEFE(satz.runde == 12);
    PRUEFE(satz.ziel == ziel);
    PRUEFE(satz.alt == 4711);
    PRUEFE(satz.neu == 815);
    PRUEFE(satz.ursache.art() == UrsacheArt::Marktraeumung);
    PRUEFE(satz.verzoegerung == 0);
    PRUEFE(satz.beitrag == 1000);

    ERWARTE_ABBRUCH(static_cast<void>(schreiber.kette().eintrag(1)));
}

// ---------------------------------------------------------------------------
// Abnahme 4 -- die Sollmasken und die zweiseitige Pruefung
// ---------------------------------------------------------------------------

void probe_maskengroessen()
{
    PRUEFE(sollmaskengroesse(Modus::Weltlauf) == 175);
    PRUEFE(sollmaskengroesse(Modus::Spielmodus) == 310);
    PRUEFE(MASKE_WELTLAUF + AUSSERHALB_WELTLAUF == 310);
    std::printf("  Sollmaske weltlauf = %zu, spielmodus = %zu, Kettenkapazitaet = %zu\n",
                sollmaskengroesse(Modus::Weltlauf), sollmaskengroesse(Modus::Spielmodus),
                KETTE_KAPAZITAET);

    // Stichproben gegen die Blocktabelle in T38, je eine aus jeder Zeile. Sie belegen
    // nicht nur die Zahl 175, sondern dass die richtigen 175 drinstehen.
    const Bitfeld& maske = sollmaske(Modus::Weltlauf);

    // in der Maske
    PRUEFE(maske.steht(kern::zustand::stelle_sektorgroesse(Gebiet::CN, Sektor::Landwirtschaft,
                                                           SektorGroesse::Wertschoepfung)));
    PRUEFE(maske.steht(kern::zustand::stelle_aggregat(Gebiet::CN, Aggregat::Preisniveau)));
    PRUEFE(maske.steht(kern::zustand::stelle_politisch(Gebiet::CN, PolitischeGroesse::Zustimmung)));
    PRUEFE(maske.steht(
        kern::zustand::stelle_instrument(Gebiet::CN, Instrument::Zoll, InstrumentFeld::Stand)));
    PRUEFE(maske.steht(kern::zustand::stelle_basiswechsel(Gebiet::CN)));
    PRUEFE(maske.steht(kern::zustand::stelle_aggregat(Gebiet::RW, Aggregat::Leitzins)));
    PRUEFE(maske.steht(kern::zustand::stelle_basiswechsel(Gebiet::RW)));
    PRUEFE(maske.steht(kern::zustand::stelle_handel(Gebiet::DE, Gebiet::CN, Sektor::Industrie)));
    PRUEFE(maske.steht(kern::zustand::stelle_weltpreis(Sektor::Landwirtschaft)));
    PRUEFE(maske.steht(kern::zustand::stelle_partie(PartieFeld::Runde)));
    PRUEFE(maske.steht(kern::zustand::stelle_partie(PartieFeld::JahrgangId)));
    PRUEFE(maske.steht(kern::zustand::stelle_partie(PartieFeld::ParameterPruefsumme)));

    // ausserhalb der Maske
    PRUEFE(!maske.steht(
        kern::zustand::stelle_politisch(Gebiet::CN, PolitischeGroesse::Aufsichtszaehler)));
    PRUEFE(!maske.steht(kern::zustand::stelle_politisch(Gebiet::CN, PolitischeGroesse::Einfluss)));
    PRUEFE(!maske.steht(
        kern::zustand::stelle_instrument(Gebiet::CN, Instrument::Zoll, InstrumentFeld::Druck)));
    PRUEFE(!maske.steht(kern::zustand::stelle_restdauer(Gebiet::CN, Restdauerzaehler::Marktverbot)));
    PRUEFE(!maske.steht(kern::zustand::stelle_nachahmer(Gebiet::CN, Sektor::Industrie)));
    PRUEFE(!maske.steht(kern::zustand::stelle_markt(MarktGroesse::Rendite)));
    PRUEFE(!maske.steht(kern::zustand::stelle_fonds(FondsGroesse::Kasse)));
    PRUEFE(!maske.steht(kern::zustand::stelle_ueberrendite(1)));
    PRUEFE(!maske.steht(kern::zustand::stelle_position(kern::zustand::Steckplatz::Anleihe_BR)));
    PRUEFE(!maske.steht(kern::zustand::stelle_beteiligung(Gebiet::CN, Sektor::Industrie,
                                                          kern::zustand::BeteiligungsFeld::Anteil)));
    PRUEFE(!maske.steht(kern::zustand::stelle_partie(PartieFeld::Mandatsstand)));

    // Im Spielmodus steht jede der 310 Adressen in der Maske.
    const Bitfeld& alle = sollmaske(Modus::Spielmodus);
    std::size_t gezaehlt = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (alle.steht(platz)) {
            ++gezaehlt;
        }
    }
    PRUEFE(gezaehlt == 310);
}

/// Schreibt die Sollmaske des Weltlaufs, laesst dabei `auslassen` aus und schreibt
/// `zusaetzlich` obendrein. `FELDER` heisst "nichts auslassen" bzw. "nichts dazu".
void weltlauf_runde(Schreiber& schreiber, Index auslassen, Index zusaetzlich)
{
    const Bitfeld& maske = sollmaske(Modus::Weltlauf);
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (maske.steht(platz) && platz != auslassen) {
            schreiber.setze(platz, undurchsichtig(static_cast<i64>(platz) * 10),
                            Ursache::jahrgang(), 0, 1000);
        }
    }
    if (zusaetzlich < FELDER) {
        schreiber.setze(zusaetzlich, undurchsichtig(1), irgendeine(), 0, 1000);
    }
}

void probe_maskenpruefung_zweiseitig()
{
    const Zustand start;

    // Seite 1: eine Adresse der Maske bleibt ungeschrieben.
    {
        const Index fehlt = kern::zustand::stelle_weltpreis(Sektor::Industrie);
        Schreiber schreiber(start, Modus::Weltlauf, 1);
        weltlauf_runde(schreiber, fehlt, FELDER);
        PRUEFE(schreiber.geschriebene() == 174);
        ERWARTE_ABBRUCH(static_cast<void>(schreiber.rundenende()));
    }

    // Seite 2: eine Adresse ausserhalb der Maske wird beruehrt. Die Maske ist dabei
    // vollstaendig geschrieben -- sonst schluege schon Seite 1 an, und die Probe
    // beliefe nicht, was sie belegen soll.
    {
        const Index zuviel = kern::zustand::stelle_fonds(FondsGroesse::Hebelstand);
        Schreiber schreiber(start, Modus::Weltlauf, 1);
        weltlauf_runde(schreiber, FELDER, zuviel);
        PRUEFE(schreiber.geschriebene() == 176);
        ERWARTE_ABBRUCH(static_cast<void>(schreiber.rundenende()));
    }

    // Und die Maske genau getroffen: die Pruefung besteht, die Kette hat 175 Glieder.
    {
        Schreiber schreiber(start, Modus::Weltlauf, 1);
        weltlauf_runde(schreiber, FELDER, FELDER);
        PRUEFE(schreiber.geschriebene() == 175);
        const Zustand& fertig = schreiber.rundenende();
        PRUEFE(schreiber.kette().laenge() == 175);
        // Was ausserhalb der Maske liegt, behaelt seinen Startwert (T38).
        PRUEFE(fertig.lies(kern::zustand::stelle_fonds(FondsGroesse::Kasse)) == 0);
        // Und was drin liegt, traegt den geschriebenen Wert.
        const Index preis = kern::zustand::stelle_weltpreis(Sektor::Industrie);
        PRUEFE(fertig.lies(preis) == static_cast<i64>(preis) * 10);
        std::printf("  Weltlauf: %zu Adressen geschrieben, Kette %zu Glieder (erwartet 175)\n",
                    schreiber.geschriebene(), schreiber.kette().laenge());
    }
}

// ---------------------------------------------------------------------------
// Abnahme 5 -- die volle Runde im Spielmodus geht auf
// ---------------------------------------------------------------------------

void probe_volle_runde()
{
    Zustand vorrunde;
    vorrunde.schreibe(7, 123'456);
    vorrunde.schreibe(300, -987);

    Schreiber schreiber(vorrunde, Modus::Spielmodus, 40);

    for (Index platz = 0; platz < FELDER; ++platz) {
        if (platz == 7 || platz == 300) {
            // Eine Adresse, die sich nicht aendert, wird trotzdem geschrieben (T18):
            // "unveraendert" ist eine Aussage und keine Luecke.
            schreiber.vortrag(platz);
        } else {
            schreiber.setze(platz, undurchsichtig(static_cast<i64>(platz) + 1),
                            Ursache::aktion(1), 2, 1000);
        }
    }

    const Zustand& fertig = schreiber.rundenende();

    // Ausgeschrieben als Erwartungswert, nicht als Zaehlschleife ueber den eigenen
    // Behaelter: 310 Adressen, 310 Kettenglieder.
    PRUEFE(schreiber.geschriebene() == 310);
    PRUEFE(schreiber.kette().laenge() == 310);
    std::printf("  Spielmodus: %zu Adressen geschrieben, Kette %zu Glieder (erwartet 310)\n",
                schreiber.geschriebene(), schreiber.kette().laenge());

    // Die beiden Vortraege stehen als solche in der Kette und haben den Wert gehalten.
    const Ursachensatz& sieben = schreiber.kette().eintrag(7);
    PRUEFE(sieben.ziel == 7);
    PRUEFE(sieben.ursache.art() == UrsacheArt::Vortrag);
    PRUEFE(sieben.ursache.vortragsadresse() == 7);
    PRUEFE(sieben.alt == 123'456);
    PRUEFE(sieben.neu == 123'456);
    PRUEFE(fertig.lies(7) == 123'456);
    PRUEFE(fertig.lies(300) == -987);

    // Die Kette liegt in der Reihenfolge der Schreibzugriffe -- hier also nach Adresse.
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (schreiber.kette().eintrag(platz).ziel != platz) {
            PRUEFE(schreiber.kette().eintrag(platz).ziel == platz);
            break;
        }
    }

    // Und der 311. Schreibzugriff kann es nicht geben: Jede Adresse ist vergeben, und
    // jede weitere ist der zweite Schreibzugriff auf eine schon vergebene.
    ERWARTE_ABBRUCH(schreiber.setze(0, 1, irgendeine(), 0, 1000));
    PRUEFE(schreiber.kette().laenge() == KETTE_KAPAZITAET);
}

}  // namespace

int main()
{
    probe_ursachenformen();
    probe_zweiter_schreibzugriff();
    probe_alt_bleibt_alt();
    probe_maskengroessen();
    probe_maskenpruefung_zweiseitig();
    probe_volle_runde();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("schreiber_probe: alle Pruefungen bestanden\n");
    return 0;
}
