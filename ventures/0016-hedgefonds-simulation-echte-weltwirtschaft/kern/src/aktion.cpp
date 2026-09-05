//! Der Aktionstyp -- die Abbrueche im Wortlaut und die Namen aus den Vorgaben.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/aktion.hpp`. Hier steht, was nicht in
//! einen Kopf gehoert: der Weg von einer blossen Zahl zu einer Aktionsart, die Namen
//! der fuenf Arten und der drei Ordnungsschluessel, und die Meldungen dazu.
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

#include <cstdint>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::aktion {

namespace {

using meldung::Meldung;

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

}  // namespace kern::aktion
