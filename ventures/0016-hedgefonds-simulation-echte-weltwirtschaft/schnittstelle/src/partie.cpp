//! Der Schreiber des Partieformats aus T22 -- Paket 0301.
//!
//! Die Begruendung des Formats steht im Kopf von `include/schnittstelle/partie.hpp` und
//! wird hier nicht wiederholt. Was hier steht, ist der Weg vom Traeger zur Zeile.

#include <cstddef>
#include <cstdint>

#include "kern/aktion.hpp"
#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "schnittstelle/partie.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace schnittstelle::partie {

namespace {

using kern::festkomma::i128;

/// Haengt `"name":` an -- der Name kommt aus `FELDNAME` und wird nirgends ein zweites
/// Mal hingeschrieben.
void schluessel_schreiben(Partiezeile& zeile, Feld feld)
{
    zeile.text("\"");
    zeile.text(FELDNAME[static_cast<std::size_t>(feld)]);
    zeile.text("\":");
}

/// Haengt die Aktionsfolge an: eine Reihe von Reihen, je Zug vier Zahlen.
///
/// Die vier sind die Runde und danach die drei Ordnungsschluessel aus T32 in ihrer
/// Rangfolge -- Aktionsart, Zielkennung, Stufe. Die Art steht als ihre Kennung 1 bis 5,
/// gelesen ueber `kern::aktion::art_kennung`: Das ist der eine Weg von der Art zur Zahl,
/// und er bricht bei einem Wert daneben ab, statt eine Zahl zu schreiben, die kein Leser
/// zurueckverwandeln kann.
///
/// Eine leere Folge gibt `[]` -- der Speicherstand einer Partie vor der ersten Runde.
/// Genau dieser Fall waere bei einem Format mit vorangestellter Laenge der erste, den
/// niemand ausprobiert.
void folge_schreiben(Partiezeile& zeile, const Aktionsfolge& folge)
{
    zeile.text("[");
    for (std::size_t k = 0; k < folge.anzahl; ++k) {
        if (k > 0) {
            zeile.text(",");
        }
        const Zug& zug = folge.eintraege[k];
        zeile.text("[");
        zeile.zahl(static_cast<i128>(zug.runde));
        zeile.text(",");
        zeile.zahl(static_cast<i128>(kern::aktion::art_kennung(zug.aktion.art)));
        zeile.text(",");
        zeile.zahl(static_cast<i128>(zug.aktion.ziel.wert));
        zeile.text(",");
        zeile.zahl(static_cast<i128>(zug.aktion.stufe));
        zeile.text("]");
    }
    zeile.text("]");
}

/// Haengt den Wert eines Feldes an.
///
/// Eine Verzweigung ueber alle acht und **kein** Zweig fuer den Rest: Ein zugelegtes Feld
/// ist damit eine Warnung, und die ist unter `-Werror` ein roter Bau. Der Abbruch am Ende
/// faengt den einen Fall, den die Verzweigung nicht faengt -- eine Zahl, die als `Feld`
/// hereinkommt und keines ist.
void wert_schreiben(Partiezeile& zeile, const Partie& stand, Feld feld)
{
    switch (feld) {
    case Feld::SchemaVersion:
        zeile.zahl(static_cast<i128>(stand.schema_version));
        return;
    case Feld::JahrgangId:
        zeile.zahl(static_cast<i128>(stand.jahrgang_id));
        return;
    case Feld::Modus:
        zeile.zahl(static_cast<i128>(static_cast<std::uint8_t>(stand.modus)));
        return;
    case Feld::DatenPruefsumme:
        zeile.zahl(static_cast<i128>(stand.daten_pruefsumme));
        return;
    case Feld::ParameterPruefsumme:
        zeile.zahl(static_cast<i128>(stand.parameter_pruefsumme));
        return;
    case Feld::Startwert:
        zeile.zahl(static_cast<i128>(stand.startwert));
        return;
    case Feld::Aktionen:
        folge_schreiben(zeile, stand.aktionen);
        return;
    case Feld::EndPruefsumme:
        zeile.zahl(static_cast<i128>(stand.end_pruefsumme));
        return;
    }
    kern::festkomma::abbruch("schnittstelle::partie -- unbekanntes Feld; T22 kennt acht");
}

}  // namespace

Partiezeile schreibe(const Partie& stand)
{
    // Zuerst die Kapazitaet, und zwar hart. Eine Folge, die laenger angesagt ist, als der
    // Behaelter fasst, wuerde unterhalb dieser Zeile ueber das Feld hinaus gelesen.
    if (stand.aktionen.anzahl > ZUEGE_HOECHSTENS) {
        kern::festkomma::abbruch("schnittstelle::partie::schreibe -- mehr Zuege angesagt, "
                                 "als die Folge fasst; die Wand steht in T22 ueber T40");
    }

    Partiezeile zeile;
    zeile.text("{");
    for (std::size_t platz = 0; platz < FELDER; ++platz) {
        if (platz > 0) {
            zeile.text(",");
        }
        const Feld feld = feld_des_platzes(platz);
        schluessel_schreiben(zeile, feld);
        wert_schreiben(zeile, stand, feld);
    }
    zeile.text("}");

    // Der Puffer ist aus der Kapazitaet oben gebildet und kann bei einer zulaessigen Folge
    // nicht volllaufen -- `test/partie_probe.cpp` misst das an der laengsten Zeile, die
    // ueberhaupt entstehen kann. Die Schranke steht trotzdem: Sie ist die Stelle, an der
    // eine verschobene Wand laut wird, statt eine halbe Zeile herauszugeben, die aussieht
    // wie eine ganze.
    if (zeile.abgeschnitten()) {
        kern::festkomma::abbruch("schnittstelle::partie::schreibe -- die Zeile passt nicht "
                                 "in den Puffer; ein abgeschnittener Speicherstand laedt "
                                 "als eine andere Partie");
    }
    return zeile;
}

}  // namespace schnittstelle::partie
