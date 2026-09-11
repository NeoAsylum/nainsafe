//! Der Aktionstyp -- die Abbrueche im Wortlaut, die Namen aus den Vorgaben, die Liste
//! einer Runde und die Pruefung eines Buendels.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/aktion.hpp`. Hier steht, was nicht in
//! einen Kopf gehoert: der Weg von einer blossen Zahl zu einer Aktionsart, die Namen
//! der fuenf Arten, der drei Ordnungsschluessel und der Einwaende, die Meldungen dazu --
//! und seit Paket 0300 die beiden Funktionen aus T32, die ueber den Zustand laufen und
//! deshalb nicht in einen Kopf gehoeren, der nur ordnet.
//!
//! ## Warum die Namen hier stehen und nicht im Kopf
//!
//! Ein Name ist eine Zeichenkette, kein Rechenwert. Im Kopf braeuchte er eine
//! Zusicherung ueber seine Lebensdauer an jeder Einbindungsstelle; hier ist er eine
//! Tabelle in einer Uebersetzungseinheit, die so lange lebt wie das Programm -- dieselbe
//! Bauart, mit der der Zustand seine Adressen fuehrt.
//!
//! ## Warum es genau einen Weg von einer Zahl zu einer Art gibt
//!
//! Eine Aktion kommt nicht immer als Typ an. Nach T22 traegt ein Speicherstand die
//! Aktionsfolge als Zahlen, und nach T21 kommt sie ueber die Maschinenschnittstelle
//! ebenso. Eine Umwandlung an jeder dieser Stellen waere eine Umwandlung, die an einer
//! davon die Bereichspruefung vergisst -- und eine Aktionsart ausserhalb 1 bis 5 ist
//! keine Aktion, sondern eine Zahl, die sich als eine ausgibt. Ihre Ordnung waere
//! danach still falsch, denn der staerkste Ordnungsschluessel aus T32 ist genau diese
//! Kennung.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::aktion {

namespace {

using meldung::Meldung;

using werte::Konstanten;

using zustand::BeteiligungsFeld;
using zustand::FondsGroesse;
using zustand::Gebiet;
using zustand::LAENDER;
using zustand::Sektor;
using zustand::SEKTOREN;
using zustand::Steckplatz;
using zustand::Zustand;

/// Die drei Sektoren in der Reihenfolge aus T9, als Liste statt als Zaehlschleife.
///
/// Die Aufzaehlung der Sektoren faengt bei eins an, damit die Zahl in der Aufzaehlung
/// und die Zahl in der Adresse dieselbe ist. Eine Schleife ueber `0 ... SEKTOREN-1` mit
/// einem aufaddierten Eins waere die Sorte stiller Umrechnung, die T9 gerade vermeiden
/// will; die Liste nennt die drei und die Zusicherung darunter zaehlt sie nach.
constexpr std::array<Sektor, SEKTOREN> SEKTORLISTE = {
    Sektor::Landwirtschaft,
    Sektor::Industrie,
    Sektor::Dienstleistungen,
};

static_assert(SEKTORLISTE.size() == SEKTOREN,
              "T9: die Liste fuehrt jeden Sektor genau einmal");

/// Der Betrag einer Stufenzahl.
///
/// Gebaut aus der geprueften Subtraktion und nicht aus einer eigenen Vorzeichenregel: Der
/// kleinste `i64` hat keinen darstellbaren Betrag, und unter `-fwrapv` ergaebe die
/// naheliegende Form dort wieder dieselbe negative Zahl -- aus einem Betrag wuerde still
/// ein negativer Anteil. So bricht der Fall an derselben Stelle ab wie jeder andere
/// Ueberlauf der Strichrechnung, und diese Quelle traegt keine zweite Rechenregel.
[[nodiscard]] i64 betrag_der_stufe(i64 stufe)
{
    return stufe < 0 ? festkomma::minus(i64{0}, stufe) : stufe;
}

/// Ob zwei Aktionen **dasselbe Ziel** meinen -- gleiche Art, gleiche Zielkennung.
///
/// Die Stufe bleibt ausser Betracht, und das ist der ganze Sinn: T32 nennt drei
/// Aufstockungen desselben Steckplatzes in einer Runde, und die unterscheiden sich
/// genau in der Stufe.
[[nodiscard]] bool dasselbe_ziel(const Aktion& links, const Aktion& rechts)
{
    return links.art == rechts.art && links.ziel == rechts.ziel;
}

/// Ob die Liste dieser Runde das Ziel dieser Aktion anbietet.
[[nodiscard]] bool wird_angeboten(const Zulaessigkeitsliste& liste, const Aktion& eintrag)
{
    for (std::size_t k = 0; k < liste.anzahl; ++k) {
        if (dasselbe_ziel(liste.eintrag[k], eintrag)) {
            return true;
        }
    }
    return false;
}

}  // namespace

Art art_der_kennung(i64 kennung)
{
    if (kennung < static_cast<i64>(ART_KENNUNG_ERSTE)
        || kennung > static_cast<i64>(ART_KENNUNG_LETZTE)) {
        Meldung meldung;
        meldung.text("kern::aktion -- die Kennung ");
        meldung.zahl(kennung);
        meldung.text(" ist keine Aktionsart; es gibt die Kennungen ");
        meldung.zahl(static_cast<i64>(ART_KENNUNG_ERSTE));
        meldung.text(" bis ");
        meldung.zahl(static_cast<i64>(ART_KENNUNG_LETZTE));
        meldung.text(". Ein Ersatzwert gaebe es nicht -- die Kennung ist der staerkste "
                     "Ordnungsschluessel aus T32.");
        festkomma::abbruch(meldung.fertig());
    }
    return static_cast<Art>(static_cast<std::uint8_t>(kennung));
}

const char* art_name(Art art)
{
    switch (art) {
    case Art::Position:
        return "Position";
    case Art::Beteiligung:
        return "Beteiligung";
    case Art::Lobbybudget:
        return "Lobbybudget";
    case Art::Hebel:
        return "Hebel";
    case Art::Sichtbarkeit:
        return "Sichtbarkeit";
    }

    Meldung meldung;
    meldung.text("kern::aktion -- zur Kennung ");
    meldung.zahl(static_cast<i64>(static_cast<std::uint8_t>(art)));
    meldung.text(" gibt es keine Aktionsart. Ein Fragezeichen an ihrer Stelle saehe in "
                 "einer Ausgabe aus wie eine Art, die es gibt.");
    festkomma::abbruch(meldung.fertig());
}

const char* schluessel_name(Schluessel schluessel)
{
    switch (schluessel) {
    case Schluessel::Aktionsart:
        return "Aktionsart";
    case Schluessel::Zielkennung:
        return "Zielkennung";
    case Schluessel::Stufe:
        return "Stufe";
    }

    Meldung meldung;
    meldung.text("kern::aktion -- zum Rang ");
    meldung.zahl(static_cast<i64>(static_cast<std::uint8_t>(schluessel)));
    meldung.text(" gibt es keinen Ordnungsschluessel; T32 kennt drei.");
    festkomma::abbruch(meldung.fertig());
}

const char* einwand_name(Einwand einwand)
{
    switch (einwand) {
    case Einwand::Keiner:
        return "zulaessig";
    case Einwand::ZuVieleAktionen:
        return "mehr als drei Aktionen";
    case Einwand::NichtAngeboten:
        return "in dieser Runde nicht angeboten";
    case Einwand::ZielDoppelt:
        return "dasselbe Ziel zweimal";
    case Einwand::KasseUeberzogen:
        return "Kasse ueberzogen";
    case Einwand::AnteilUeberDerSkala:
        return "Fondsanteil ueber der Anteilsskala";
    }

    Meldung meldung;
    meldung.text("kern::aktion -- zur Kennung ");
    meldung.zahl(static_cast<i64>(static_cast<std::uint8_t>(einwand)));
    meldung.text(" gibt es keinen Einwand. Ein Fragezeichen an seiner Stelle saehe in "
                 "einer Zurueckweisung nach T21 aus wie ein Grund, den es gibt.");
    festkomma::abbruch(meldung.fertig());
}

// ---------------------------------------------------------------------------
// T32 -- die Liste einer Runde
// ---------------------------------------------------------------------------

Zulaessigkeitsliste zulaessige_aktionen([[maybe_unused]] const Zustand& z,
                                        [[maybe_unused]] const Konstanten& konst)
{
    Zulaessigkeitsliste liste{};

    // Die aeussere Schleife laeuft ueber die Kennungen 1 bis 5 und nicht ueber eine
    // hingeschriebene Artenliste: Die Kennung ist der staerkste Ordnungsschluessel aus
    // T32, und `art_der_kennung` ist der eine erlaubte Weg von einer Zahl zu einer Art.
    for (std::size_t k = 0; k < ARTEN; ++k) {
        const Art art =
            art_der_kennung(static_cast<i64>(ART_KENNUNG_ERSTE) + static_cast<i64>(k));
        const std::size_t ziele = zielmenge(art);

        for (std::size_t platz = 0; platz < ziele; ++platz) {
            // T16, die eine Ausnahme: Der Waehrungsplatz der USA behaelt seinen Platz
            // in der Ordnung und wird nie angeboten. Gefragt wird die eine Stelle, die
            // diese Ausnahme fuehrt -- sie steht bei den Steckplaetzen und nicht hier,
            // und eine zweite Fassung davon waere die, die jemand vergisst, wenn die
            // erste sich aendert. Eine Zahl des Zustands liest das nicht.
            if (art == Art::Position
                && !zustand::steckplatz_spielbar(
                    static_cast<Steckplatz>(static_cast<std::uint8_t>(platz)))) {
                continue;
            }

            if (liste.anzahl >= liste.eintrag.size()) {
                festkomma::abbruch("kern::aktion::zulaessige_aktionen -- mehr Angebote, "
                                   "als die Liste fasst; ihre Kapazitaet ist die Summe "
                                   "der fuenf Zielmengen aus T32b");
            }

            liste.eintrag[liste.anzahl] = Aktion{art, zielkennung(platz), STUFE_OFFEN};
            ++liste.anzahl;
        }
    }

    // Die Ordnung wird gesetzt und nicht ueberliefert. Die Schleife oben laeuft schon in
    // der Rangfolge aus T32; genau deshalb steht dieser Aufruf hier und nicht als
    // Bemerkung darueber. Kostet auf einer bereits geordneten Folge einen Durchlauf.
    ordne(liste.eintrag, liste.anzahl);
    return liste;
}

// ---------------------------------------------------------------------------
// T32 -- die Pruefung des Buendels
// ---------------------------------------------------------------------------

i64 kassenbedarf(const Aktion& eintrag)
{
    switch (eintrag.art) {
    case Art::Lobbybudget:
        // T50, Uebergang 2: Was diese Aktion in Lobbydruck umrechnet, sind Cent -- also
        // ist die Stufe der Geldbetrag. Die Richtung ist nach T32b das Vorzeichen und
        // kein zweites Ziel; bezahlt wird sie in beide Richtungen.
        return betrag_der_stufe(eintrag.stufe);
    case Art::Position:
    case Art::Beteiligung:
    case Art::Hebel:
    case Art::Sichtbarkeit:
        // Null, und der Grund steht am Kopf dieser Funktion: Fuer die Art 5 nennt keine
        // Vorgabe Geld, fuer die Arten 1, 2 und 4 nennt keine Vorgabe einen Betrag. Die
        // zweite Null ist die gemeldete Luecke und kein Ergebnis.
        return 0;
    }

    Meldung meldung;
    meldung.text("kern::aktion::kassenbedarf -- zur Kennung ");
    meldung.zahl(static_cast<i64>(static_cast<std::uint8_t>(eintrag.art)));
    meldung.text(" gibt es keine Aktionsart; T32 kennt die Kennungen 1 bis 5.");
    festkomma::abbruch(meldung.fertig());
}

Einwand buendel_einwand(const Zustand& z, const Konstanten& konst, const Buendel& buendel)
{
    if (buendel.anzahl > buendel.eintrag.size()) {
        festkomma::abbruch("kern::aktion::buendel_einwand -- mehr Aktionen angesagt, "
                           "als das Buendel fasst");
    }

    // 1. Die Zahl. T32 nennt drei als Obergrenze; der vierte Platz besteht nur, damit
    //    diese Bedingung ueberhaupt eine Eingabe hat, an der sie rot wird.
    if (buendel.anzahl > BUENDEL_AKTIONEN_HOECHSTENS) {
        return Einwand::ZuVieleAktionen;
    }

    // Die Liste wird hier erzeugt und nicht hereingereicht. Ein Argument waere billiger
    // -- fuenfzig Eintraege und ein Einfuegedurchlauf je Aufruf --, und es waere die
    // Stelle, an der ein Aufrufer die Liste einer **anderen** Runde gegen dieses Buendel
    // haelt. Genau das ist der Fall, gegen den T32 die Liste an den Zustand zu
    // Rundenbeginn bindet; die Erzeugung ist deterministisch und kostet nichts, was der
    // Vergleich wert waere.
    const Zulaessigkeitsliste liste = zulaessige_aktionen(z, konst);

    // 2. Der Wertebereich, und zwar gegen die erzeugte Liste statt gegen eine zweite
    //    Fassung der fuenf Zeilen aus T32b. Das faengt beides: eine Zielkennung jenseits
    //    ihrer Menge und den einen Platz, den T16 nie anbietet.
    for (std::size_t k = 0; k < buendel.anzahl; ++k) {
        if (!wird_angeboten(liste, buendel.eintrag[k])) {
            return Einwand::NichtAngeboten;
        }
    }

    // 3. Dasselbe Ziel zweimal.
    for (std::size_t k = 1; k < buendel.anzahl; ++k) {
        for (std::size_t j = 0; j < k; ++j) {
            if (dasselbe_ziel(buendel.eintrag[j], buendel.eintrag[k])) {
                return Einwand::ZielDoppelt;
            }
        }
    }

    // 4. Die Kasse -- die Summe der Ansprueche gegen den Stand zu Rundenbeginn.
    i64 bedarf = 0;
    for (std::size_t k = 0; k < buendel.anzahl; ++k) {
        bedarf = festkomma::plus(bedarf, kassenbedarf(buendel.eintrag[k]));
    }
    if (bedarf > z.lies(zustand::stelle_fonds(FondsGroesse::Kasse))) {
        return Einwand::KasseUeberzogen;
    }

    // 5. Die Anteilsskala, je Land und Sektor. Gerechnet wird T48 Nr. 14 -- Betrag der
    //    Stufenzahl mal Stufenweite plus Beteiligungsanteil --, nur mit den Zahlen,
    //    **nach** denen das Buendel steht. Der Betrag liegt dabei aussen: Ein Buendel,
    //    das eine Stufenzahl von -4 auf -6 traegt, vergroessert den Anteil, und eine
    //    Fortschreibung ueber die Summe der Betraege saehe das nicht.
    //
    //    Ungeruehrte Paare bleiben aussen vor. T32 nennt eine Aktion 1 oder 2, **nach
    //    der** der Anteil darueber laege; ein Paar, das schon vorher darueber stuende,
    //    ist kein Einwand gegen dieses Buendel.
    for (std::size_t l = 0; l < LAENDER; ++l) {
        const Gebiet land = static_cast<Gebiet>(static_cast<std::uint8_t>(l));

        for (const Sektor sektor : SEKTORLISTE) {
            const Steckplatz  platz = zustand::steckplatz_sektor(land, sektor);
            const Zielkennung ziel  = zielkennung(static_cast<std::size_t>(platz));

            i64  stufen_zu = 0;
            i64  anteil_zu = 0;
            bool beruehrt  = false;

            for (std::size_t k = 0; k < buendel.anzahl; ++k) {
                const Aktion& tat = buendel.eintrag[k];
                if (tat.ziel != ziel) {
                    continue;
                }
                if (tat.art == Art::Position) {
                    stufen_zu = festkomma::plus(stufen_zu, tat.stufe);
                    beruehrt  = true;
                } else if (tat.art == Art::Beteiligung) {
                    anteil_zu = festkomma::plus(anteil_zu, tat.stufe);
                    beruehrt  = true;
                }
            }

            if (!beruehrt) {
                continue;
            }

            const i64 stufen =
                festkomma::plus(z.lies(zustand::stelle_position(platz)), stufen_zu);
            const i64 anteil = festkomma::plus(
                z.lies(zustand::stelle_beteiligung(land, sektor, BeteiligungsFeld::Anteil)),
                anteil_zu);
            const i64 zusammen = festkomma::plus(
                festkomma::mal(betrag_der_stufe(stufen), konst.stufenweite), anteil);

            if (zusammen > ANTEIL_HOECHSTENS) {
                return Einwand::AnteilUeberDerSkala;
            }
        }
    }

    return Einwand::Keiner;
}

bool buendel_zulaessig(const Zustand& z, const Konstanten& konst, const Buendel& buendel)
{
    return buendel_einwand(z, konst, buendel) == Einwand::Keiner;
}

}  // namespace kern::aktion
