//! Der Schreiber -- die Sollmasken, die Schreib- und Lesewege, die Rundenendpruefung.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/schreiber.hpp`. Hier steht, was nicht
//! in einen Kopf gehoert: die beiden Sollmasken aus T38 samt der Nachrechnung ihrer
//! Groesse.
//!
//! **Der Meldungsbau stand bis Paket 0038 ebenfalls hier** und steht seit dem in
//! `include/kern/meldung.hpp`. Der Grund fuer den Umzug: Die sechs Schrittpakete der
//! Runde brauchen dieselbe Klasse, jedes einzeln, und eine abgeschriebene
//! Fehlermeldungsklasse liegt beim zweiten Mal in zwei Fassungen vor, die auseinander-
//! laufen. Am Verhalten der Abbrueche unten hat der Umzug nichts geaendert; dass er es
//! nicht getan hat, weist `schreiber_probe` nach, das sie im Wortlaut ins Protokoll
//! schreibt.
//!
//! **Die Maskengroessen sind `static_assert` und keine Behauptung.** Sie laufen beim
//! Uebersetzen: Ergibt die abgeschriebene Blocktabelle aus T38 nicht 175 Adressen, ist
//! das kein roter Test, den jemand lesen muss, sondern eine Datei, die sich nicht
//! uebersetzen laesst.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::schreiber {

namespace {

/// Der Meldungsbau steht seit Paket 0038 in `include/kern/meldung.hpp` -- die Abbrueche
/// unten nennen ihre Adresse damit, und die sechs Schrittpakete der Runde benutzen
/// dieselbe Klasse statt einer eigenen Abschrift.
using meldung::Meldung;

using zustand::Aggregat;
using zustand::InstrumentFeld;
using zustand::PartieFeld;
using zustand::PolitischeGroesse;
using zustand::SektorGroesse;

// ---------------------------------------------------------------------------
// Die festen Reihenfolgen, ueber die iteriert wird (T9)
// ---------------------------------------------------------------------------
//
// Ausgeschrieben statt aus Zahlen gerechnet: Wer eine Aufzaehlung erweitert, muss die
// Zeile hier anfassen und sieht dabei, was er tut. Eine Zaehlschleife ueber
// `static_cast<Gebiet>(n)` haette den Zuwachs stillschweigend mitgenommen.

constexpr std::array<Gebiet, zustand::GEBIETE> GEBIETE_ALLE = {
    Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::BR, Gebiet::RW};

constexpr std::array<Gebiet, zustand::LAENDER> LAENDER_ALLE = {
    Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::BR};

constexpr std::array<Sektor, zustand::SEKTOREN> SEKTOREN_ALLE = {
    Sektor::Landwirtschaft, Sektor::Industrie, Sektor::Dienstleistungen};

constexpr std::array<Sektor, zustand::SEKTOREN_HANDELBAR> SEKTOREN_HANDELBAR_ALLE = {
    Sektor::Landwirtschaft, Sektor::Industrie};

constexpr std::array<SektorGroesse, zustand::SEKTORGROESSEN> SEKTORGROESSEN_ALLE = {
    SektorGroesse::Wertschoepfung, SektorGroesse::Kapitalstock, SektorGroesse::Beschaeftigung,
    SektorGroesse::Preis};

constexpr std::array<Aggregat, zustand::AGGREGATE> AGGREGATE_ALLE = {
    Aggregat::Bevoelkerung, Aggregat::Erwerbstaetige, Aggregat::Produktivitaet,
    Aggregat::Preisniveau,  Aggregat::Inflation,      Aggregat::Leitzins,
    Aggregat::Wechselkurs,  Aggregat::Staatsschuld,   Aggregat::Haushaltssaldo};

constexpr std::array<Instrument, zustand::INSTRUMENTE> INSTRUMENTE_ALLE = {
    Instrument::Leitzins, Instrument::Zoll, Instrument::Haushalt, Instrument::Regulierung};

// ---------------------------------------------------------------------------
// T38 -- die Maske `weltlauf`, Block fuer Block aus der Tabelle abgeschrieben
// ---------------------------------------------------------------------------

constexpr Bitfeld baue_maske_weltlauf()
{
    Bitfeld menge;

    // Block 1 -- je spielbarem Land 27 Adressen, zusammen 108.
    // Sektoren (12), Aggregate (9), Zustimmung (1), Instrumentenstand (4),
    // basiswechsel (1). Alles andere eines Landes steht in Block 2 und bleibt draussen.
    for (const Gebiet land : LAENDER_ALLE) {
        for (const Sektor sektor : SEKTOREN_ALLE) {
            for (const SektorGroesse groesse : SEKTORGROESSEN_ALLE) {
                menge.setze(zustand::stelle_sektorgroesse(land, sektor, groesse));
            }
        }
        for (const Aggregat aggregat : AGGREGATE_ALLE) {
            menge.setze(zustand::stelle_aggregat(land, aggregat));
        }
        menge.setze(zustand::stelle_politisch(land, PolitischeGroesse::Zustimmung));
        for (const Instrument welches : INSTRUMENTE_ALLE) {
            menge.setze(zustand::stelle_instrument(land, welches, InstrumentFeld::Stand));
        }
        menge.setze(zustand::stelle_basiswechsel(land));
    }

    // Block 3 -- die Restwelt, alle 22. Sie hat weder politische Groessen noch
    // Instrumente noch Restdauern (T15); ihr Block ist damit vollstaendig in der Maske.
    for (const Sektor sektor : SEKTOREN_ALLE) {
        for (const SektorGroesse groesse : SEKTORGROESSEN_ALLE) {
            menge.setze(zustand::stelle_sektorgroesse(Gebiet::RW, sektor, groesse));
        }
    }
    for (const Aggregat aggregat : AGGREGATE_ALLE) {
        menge.setze(zustand::stelle_aggregat(Gebiet::RW, aggregat));
    }
    menge.setze(zustand::stelle_basiswechsel(Gebiet::RW));

    // Block 4 -- der Handel, alle 40: fuenf Gebiete mal vier Gegenueber mal zwei
    // handelbare Sektoren.
    for (const Gebiet von : GEBIETE_ALLE) {
        for (const Gebiet nach : GEBIETE_ALLE) {
            if (von == nach) {
                continue;  // ein Gebiet handelt nicht mit sich selbst
            }
            for (const Sektor sektor : SEKTOREN_HANDELBAR_ALLE) {
                menge.setze(zustand::stelle_handel(von, nach, sektor));
            }
        }
    }

    // Block 5 -- die beiden Weltpreise.
    for (const Sektor sektor : SEKTOREN_HANDELBAR_ALLE) {
        menge.setze(zustand::stelle_weltpreis(sektor));
    }

    // Block 9 -- drei der vier Partiefelder. Der Mandatsstand gehoert zum
    // Fondsteilsystem und laeuft im Weltlauf nicht.
    menge.setze(zustand::stelle_partie(PartieFeld::Runde));
    menge.setze(zustand::stelle_partie(PartieFeld::JahrgangId));
    menge.setze(zustand::stelle_partie(PartieFeld::ParameterPruefsumme));

    return menge;
}

constexpr Bitfeld baue_maske_spielmodus()
{
    Bitfeld menge;
    for (Index platz = 0; platz < FELDER; ++platz) {
        menge.setze(platz);
    }
    return menge;
}

constexpr Bitfeld MASKE_WELTLAUF_MENGE = baue_maske_weltlauf();
constexpr Bitfeld MASKE_SPIELMODUS_MENGE = baue_maske_spielmodus();

// Die Nachrechnung, die das Arbeitspaket verlangt -- Blocktabelle gegen gezaehlte
// Bits. Setzte eine der Blockschleifen dieselbe Adresse zweimal, kaeme hier eine zu
// kleine Zahl heraus; eine Ueberschneidung zwischen zwei Bloecken faellt damit auf,
// statt sich als stille Doppelung zu verstecken.
static_assert(MASKE_WELTLAUF_MENGE.anzahl() == MASKE_WELTLAUF,
              "T38: die Blocktabelle des Weltlaufs ergibt 175 Adressen");
static_assert(MASKE_SPIELMODUS_MENGE.anzahl() == MASKE_SPIELMODUS,
              "T38: im Spielmodus stehen alle 310 Adressen in der Maske");

// Und die Gegenprobe von der anderen Seite: Genau 135 Adressen liegen ausserhalb.
constexpr std::size_t ausserhalb_gezaehlt()
{
    std::size_t summe = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (!MASKE_WELTLAUF_MENGE.steht(platz)) {
            ++summe;
        }
    }
    return summe;
}

static_assert(ausserhalb_gezaehlt() == AUSSERHALB_WELTLAUF,
              "T38: 135 Adressen behalten im Weltlauf ihren Startwert");

}  // namespace

// ---------------------------------------------------------------------------
// Die Sollmasken nach aussen
// ---------------------------------------------------------------------------

const Bitfeld& sollmaske(Modus modus)
{
    switch (modus) {
        case Modus::Spielmodus:
            return MASKE_SPIELMODUS_MENGE;
        case Modus::Weltlauf:
            return MASKE_WELTLAUF_MENGE;
    }
    festkomma::abbruch("kern::schreiber -- unbekannter Modus");
}

std::size_t sollmaskengroesse(Modus modus) { return sollmaske(modus).anzahl(); }

// ---------------------------------------------------------------------------
// Der Schreiber
// ---------------------------------------------------------------------------

Schreiber::Schreiber(const Zustand& vorrunde, Modus welcher_modus, i64 welche_runde)
    : alt_(vorrunde), neu_(vorrunde), modus_(welcher_modus), runde_(welche_runde)
{
    if (welche_runde < 0) {
        festkomma::abbruch("kern::schreiber -- eine Runde vor der ersten gibt es nicht");
    }
    // Der Aufruf prueft den Modus; ein unbekannter stirbt hier und nicht erst am
    // Rundenende, wenn schon dreihundert Werte darauf gebaut haben.
    static_cast<void>(sollmaske(welcher_modus));
}

void Schreiber::setze(Index adresse, i64 wert, Ursache ursache, i64 verzoegerung, i64 beitrag)
{
    if (adresse >= FELDER) {
        festkomma::abbruch("kern::schreiber::setze -- Adresse ausserhalb der 310 Felder");
    }
    if (verzoegerung < 0) {
        Meldung meldung;
        meldung.text("kern::schreiber::setze -- negative Verzoegerung an ");
        meldung.adresse(adresse);
        meldung.text(": eine Wirkung liegt nie vor ihrer Ursache");
        festkomma::abbruch(meldung.fertig());
    }
    if (geschrieben_.steht(adresse)) {
        // T18: der zweite Schreibzugriff ist ein harter Fehler und kein
        // ueberschreibender Wert. Hier stirbt jede Rueckkopplung innerhalb der Runde,
        // statt als neunter Kanal unbemerkt zu entstehen.
        Meldung meldung;
        meldung.text("kern::schreiber::setze -- zweiter Schreibzugriff in Runde ");
        meldung.zahl(runde_);
        meldung.text(" auf ");
        meldung.adresse(adresse);
        festkomma::abbruch(meldung.fertig());
    }

    const i64 vorher = alt_.lies(adresse);
    // Der rohe Schreibzugriff des Zustands ist privat (T18, Paket 0027); dass er hier
    // erreichbar ist, steht als `friend`-Zeile in `zustand.hpp` und nirgends sonst.
    // Diese eine Zeile ist der ganze Schreibweg des Modells innerhalb einer Runde.
    neu_.lege_ab(adresse, wert);
    geschrieben_.setze(adresse);

    Ursachensatz satz;
    satz.runde = runde_;
    satz.ziel = adresse;
    satz.alt = vorher;
    satz.neu = wert;
    satz.ursache = ursache;
    satz.verzoegerung = verzoegerung;
    satz.beitrag = beitrag;
    kette_.anhaengen(satz);
}

void Schreiber::vortrag(Index adresse)
{
    if (adresse >= FELDER) {
        festkomma::abbruch("kern::schreiber::vortrag -- Adresse ausserhalb der 310 Felder");
    }
    setze(adresse, alt_.lies(adresse), Ursache::vortrag(adresse), 0, 1000);
}

i64 Schreiber::lies_alt(Index adresse) const
{
    // Immer verfuegbar (T39) -- der Zustand der Vorrunde ist vollstaendig und
    // unveraenderlich. Die Indexpruefung macht `Zustand::lies`.
    return alt_.lies(adresse);
}

i64 Schreiber::lies_neu(Index adresse) const
{
    if (adresse >= FELDER) {
        festkomma::abbruch("kern::schreiber::lies_neu -- Adresse ausserhalb der 310 Felder");
    }
    if (!geschrieben_.steht(adresse)) {
        // T39: kein stiller Rueckgriff auf `alt`. Genau dieser Abbruch macht die
        // Zyklenfreiheit der sechs Rundenschritte zu einer Eigenschaft, die jeder Lauf
        // nachweist -- auch der beim Kaeufer.
        Meldung meldung;
        meldung.text("kern::schreiber::lies_neu -- in Runde ");
        meldung.zahl(runde_);
        meldung.text(" noch nicht geschrieben: ");
        meldung.adresse(adresse);
        festkomma::abbruch(meldung.fertig());
    }
    return neu_.lies(adresse);
}

bool Schreiber::ist_geschrieben(Index adresse) const { return geschrieben_.steht(adresse); }

std::size_t Schreiber::geschriebene() const noexcept { return geschrieben_.anzahl(); }

const Zustand& Schreiber::rundenende() const
{
    const Bitfeld& maske = sollmaske(modus_);

    // Seite 1: jede Adresse der Maske genau einmal geschrieben. "Genau einmal" ist
    // hier "mindestens einmal" -- ein zweites Mal hat `setze` schon verhindert.
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (maske.steht(platz) && !geschrieben_.steht(platz)) {
            Meldung meldung;
            meldung.text("kern::schreiber -- Rundenende Runde ");
            meldung.zahl(runde_);
            meldung.text(": in der Sollmaske, aber nicht geschrieben: ");
            meldung.adresse(platz);
            festkomma::abbruch(meldung.fertig());
        }
    }

    // Seite 2: keine Adresse ausserhalb der Maske beruehrt. Was ausserhalb liegt,
    // behaelt seinen Startwert (T38); ein Schreibzugriff darauf ist keine falsche
    // Zahl, sondern ein Modell, das im falschen Modus rechnet.
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (!maske.steht(platz) && geschrieben_.steht(platz)) {
            Meldung meldung;
            meldung.text("kern::schreiber -- Rundenende Runde ");
            meldung.zahl(runde_);
            meldung.text(": ausserhalb der Sollmaske geschrieben: ");
            meldung.adresse(platz);
            festkomma::abbruch(meldung.fertig());
        }
    }

    return neu_;
}

}  // namespace kern::schreiber
