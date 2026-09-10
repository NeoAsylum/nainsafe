//! Der Rumpf zu `daten/jahrgang.hpp`. Die Begruendungen stehen dort und werden hier
//! nicht wiederholt; was hier steht, ist die Rechnung und das, was allein am Rumpf
//! haengt.

#include <array>
#include <cstddef>

#include "daten/jahrgang.hpp"
#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace daten {

using kern::festkomma::abbruch;
using kern::meldung::Meldung;
using kern::zustand::LAENDER;
using kern::zustand::PFADINSTRUMENTE;

namespace {

// Die beiden Ordnungen, ueber die dieser Kasten laeuft, als Aufzaehlung statt als
// Rueckrechnung aus dem Index. Eine Rueckrechnung -- `static_cast<Gebiet>(l)` -- waere
// eine zweite Behauptung ueber die Nummerierung aus T9, und sie stuende an einer Stelle,
// an der niemand sie prueft. Die Zusicherungen darunter halten beide Listen an genau die
// Nummerierung, auf der auch die Feldbreite ruht.
constexpr std::array<Gebiet, LAENDER> LAENDERORDNUNG = {Gebiet::US, Gebiet::CN,
                                                        Gebiet::DE, Gebiet::BR};

constexpr std::array<Instrument, PFADINSTRUMENTE> PFADORDNUNG = {
    Instrument::Leitzins, Instrument::Zoll, Instrument::Haushalt};

static_assert(static_cast<std::size_t>(Gebiet::US) == 0);
static_assert(static_cast<std::size_t>(Gebiet::CN) == 1);
static_assert(static_cast<std::size_t>(Gebiet::DE) == 2);
static_assert(static_cast<std::size_t>(Gebiet::BR) == 3);
static_assert(static_cast<std::size_t>(Instrument::Leitzins) == 0);
static_assert(static_cast<std::size_t>(Instrument::Zoll) == 1);
static_assert(static_cast<std::size_t>(Instrument::Haushalt) == 2);

/// Die Landesschranke aus T15. Im Wortlaut anders als die des Kerns, weil sie eine
/// andere Stelle nennt -- wer sie liest, soll `daten` aufschlagen und nicht `kern`.
[[nodiscard]] std::size_t land_nummer(Gebiet land)
{
    const std::size_t nummer = static_cast<std::size_t>(land);
    if (nummer >= LAENDER) {
        abbruch("daten::Jahrgang -- einen Politikpfad haben allein die vier spielbaren "
                "Laender; die Restwelt hat keine Instrumente (T15)");
    }
    return nummer;
}

/// Die Instrumentenschranke aus T61 -- eine Bedingung fuer zwei Faelle: die Regulierung
/// als Wert drei und jede Kennung ausserhalb der Aufzaehlung. Zu beiden gibt es keine
/// Reihe des Jahrgangs.
[[nodiscard]] std::size_t instrument_nummer(Instrument instrument)
{
    const std::size_t nummer = static_cast<std::size_t>(instrument);
    if (nummer >= PFADINSTRUMENTE) {
        abbruch("daten::Jahrgang -- zu dieser Instrumentenkennung gehoert keine Reihe des "
                "Jahrgangs; die Finanzmarktregulierung hat keinen Anker (T23 Punkt 3, T61)");
    }
    return nummer;
}

}  // namespace

i64 reihe_von(Instrument instrument)
{
    switch (instrument) {
    case Instrument::Leitzins:
        return 9;
    case Instrument::Zoll:
        return 13;
    case Instrument::Haushalt:
        return 12;
    case Instrument::Regulierung:
        break;
    }
    // Der `switch` faellt hier nur fuer die Regulierung und fuer eine Kennung ausserhalb
    // der Aufzaehlung durch -- beide aus demselben Grund, und deshalb mit derselben
    // Meldung wie die Schranke oben: Sie soll die Sache nennen und nicht die
    // Grenzarithmetik.
    static_cast<void>(instrument_nummer(instrument));
    abbruch("daten::reihe_von -- keine Reihe zu dieser Instrumentenkennung (T61)");
}

const char* instrument_name(Instrument instrument)
{
    switch (instrument) {
    case Instrument::Leitzins:
        return "Leitzins";
    case Instrument::Zoll:
        return "Zollniveau";
    case Instrument::Haushalt:
        return "Haushaltssaldo";
    case Instrument::Regulierung:
        break;
    }
    static_cast<void>(instrument_nummer(instrument));
    abbruch("daten::instrument_name -- keine Reihe zu dieser Instrumentenkennung (T61)");
}

const char* land_kuerzel(Gebiet land)
{
    switch (land) {
    case Gebiet::US:
        return "US";
    case Gebiet::CN:
        return "CN";
    case Gebiet::DE:
        return "DE";
    case Gebiet::BR:
        return "BR";
    case Gebiet::RW:
        break;
    }
    static_cast<void>(land_nummer(land));
    abbruch("daten::land_kuerzel -- die Restwelt ist kein spielbares Land (T15)");
}

Jahrgang::Jahrgang(std::size_t stuetzstellen)
{
    if (stuetzstellen < STUETZSTELLEN_MINDESTENS) {
        abbruch("daten::Jahrgang -- ein Jahrgang mit weniger als zwei Stuetzstellen hat "
                "R = 0 und damit keine Runde (T40)");
    }
    if (stuetzstellen > STUETZSTELLEN_HOECHSTENS) {
        abbruch("daten::Jahrgang -- mehr Stuetzstellen als die Wand aus T40 zulaesst: bei "
                "R > 26 traegt ein Wert der Ergebnisskala zwei Bedeutungen");
    }
    stuetzstellen_ = stuetzstellen;
}

i64 Jahrgang::runden() const noexcept
{
    // `R = stuetzstellen - 1` (T40). Die Subtraktion ist hier ohne Schranke sicher: Der
    // Erbauer laesst nur Werte ab `STUETZSTELLEN_MINDESTENS` durch.
    return static_cast<i64>(stuetzstellen_) - 1;
}

bool Jahrgang::ueber_fenster(i64 runde) const noexcept { return runde > runden(); }

void Jahrgang::setze(Gebiet land, Instrument instrument, std::size_t stuetzstelle,
                     i64 wert)
{
    const std::size_t l = land_nummer(land);
    const std::size_t i = instrument_nummer(instrument);
    if (stuetzstelle >= stuetzstellen_) {
        Meldung text;
        text.text("daten::Jahrgang::setze -- Stuetzstelle ");
        text.zahl(static_cast<i64>(stuetzstelle));
        text.text(" liegt jenseits der ");
        text.zahl(static_cast<i64>(stuetzstellen_));
        text.text(" Stuetzstellen dieses Jahrgangs");
        abbruch(text.fertig());
    }
    pfad_[l][i][stuetzstelle] = wert;
}

i64 Jahrgang::stelle(Gebiet land, Instrument instrument, std::size_t stuetzstelle) const
{
    const std::size_t l = land_nummer(land);
    const std::size_t i = instrument_nummer(instrument);
    // Geprueft wird gegen die belegten Stuetzstellen und nicht gegen die Feldbreite: Was
    // dahinter liegt, ist die Vorbelegung mit null und saehe wie ein Datum aus.
    if (stuetzstelle >= stuetzstellen_) {
        Meldung text;
        text.text("daten::Jahrgang::stelle -- Stuetzstelle ");
        text.zahl(static_cast<i64>(stuetzstelle));
        text.text(" liegt jenseits der ");
        text.zahl(static_cast<i64>(stuetzstellen_));
        text.text(" Stuetzstellen dieses Jahrgangs");
        abbruch(text.fertig());
    }
    return pfad_[l][i][stuetzstelle];
}

std::size_t Jahrgang::stuetzstelle_zu_runde(i64 runde) const
{
    if (runde < 1) {
        abbruch("daten::Jahrgang -- die Runden beginnen bei eins; eine Runde davor ist ein "
                "Programmfehler und kein Sonderfall mit eigenem Wert (T40)");
    }
    const i64 versatz = runde - 1;
    const i64 letzte = runden();
    return static_cast<std::size_t>(versatz < letzte ? versatz : letzte);
}

void Jahrgang::fuelle_pfadstand(kern::werte::Konstanten& konstanten, i64 runde) const
{
    const std::size_t t = stuetzstelle_zu_runde(runde);
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
            konstanten.pfadstand[l][i] = pfad_[l][i][t];
        }
    }
}

i64 Jahrgang::leitzins_start(Gebiet land) const
{
    return stelle(land, Instrument::Leitzins, 0);
}

void Jahrgang::fuelle_leitzins_start(kern::werte::Konstanten& konstanten) const
{
    const std::size_t leitzins = static_cast<std::size_t>(Instrument::Leitzins);
    for (std::size_t l = 0; l < LAENDER; ++l) {
        konstanten.leitzins_start[l] = pfad_[l][leitzins][0];
    }
}

i64 Jahrgang::aufschlag_min() const
{
    const std::size_t leitzins = static_cast<std::size_t>(Instrument::Leitzins);
    i64 kleinster = pfad_[0][leitzins][0];
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t t = 0; t < stuetzstellen_; ++t) {
            const i64 wert = pfad_[l][leitzins][t];
            if (wert < kleinster) {
                kleinster = wert;
            }
        }
    }
    // `festkomma::minus` und nicht `1 - kleinster`: Beim kleinsten `i64` waere die
    // Differenz ausserhalb des Typs, und mit `-fwrapv` liefe sie still um.
    return kern::festkomma::minus(i64{1}, kleinster);
}

bool Jahrgang::aufschlag_zulaessig(i64 aufschlag) const
{
    return aufschlag >= aufschlag_min();
}

Bereichsbefund Jahrgang::pruefe_wertebereich(const Wertebereiche& bereiche) const
{
    Bereichsbefund befund;
    // Geordnete Iteration ueber alle drei Ordnungen: Derselbe Jahrgang meldet damit
    // dieselbe erste Verletzung, und die Meldung ist reproduzierbar statt von der
    // Reihenfolge abhaengig.
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t i = 0; i < PFADINSTRUMENTE; ++i) {
            const Wertebereich& bereich = bereiche[i];
            for (std::size_t t = 0; t < stuetzstellen_; ++t) {
                const i64 wert = pfad_[l][i][t];
                if (wert >= bereich.min && wert <= bereich.max) {
                    continue;
                }
                ++befund.verletzungen;
                if (befund.verletzungen > 1) {
                    continue;
                }
                befund.erste.text("daten::Jahrgang -- der Politikpfad verlaesst den "
                                  "Wertebereich. Land ");
                befund.erste.text(land_kuerzel(LAENDERORDNUNG[l]));
                befund.erste.text(", ");
                befund.erste.text(instrument_name(PFADORDNUNG[i]));
                befund.erste.text(" (Reihe ");
                befund.erste.zahl(reihe_von(PFADORDNUNG[i]));
                befund.erste.text("), Stuetzstelle ");
                befund.erste.zahl(static_cast<i64>(t));
                befund.erste.text(": Wert ");
                befund.erste.zahl(wert);
                befund.erste.text(" bp, zugelassen ");
                befund.erste.zahl(bereich.min);
                befund.erste.text(" bis ");
                befund.erste.zahl(bereich.max);
                befund.erste.text(" bp. Im weltlauf gilt die Schrittweite nicht, der "
                                  "Wertebereich schon (T51) -- das hier ist ein Befund "
                                  "des Jahrgangsbaus und kein stilles Kappen.");
            }
        }
    }
    return befund;
}

}  // namespace daten
