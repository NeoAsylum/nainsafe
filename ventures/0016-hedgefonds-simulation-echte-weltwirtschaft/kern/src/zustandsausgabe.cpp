//! Die drei Zustandsebenen aus T20, ausgeschrieben.
//!
//! Der Kopf traegt die Zuordnung von Klasse und Herkunft samt ihrem
//! Uebersetzungsnachweis; hier steht, was daraus fuer einen Leser wird.
//!
//! ## Eine Quelle fuer alle drei Ebenen
//!
//! T20 verlangt es ausdruecklich, und es ist hier keine Absicht, sondern die Bauart:
//! Jede der drei Funktionen liest ueber `Zustand::lies` und benennt ueber
//! `index_zu_adresse`, `skalenklasse_von` und `herkunft_von`. Es gibt keine zweite
//! Namenstabelle und keine zweite Adressordnung in dieser Datei -- was `zustand.cpp`
//! ueber eine Adresse sagt, sagt jede Ebene hier wortgleich mit.
//!
//! ## Was hier keine Rolle spielt
//!
//! Ausrichtung, Spaltenbreiten, Tausendertrennung. Eine Zahl steht so da, wie sie im
//! Zustand steht -- die Skala nennt die Klasse daneben, geteilt wird erst in der Sicht
//! (T20). Wer aus `1700` in der Spalte Einfluss `17,00 %` machen will, braucht dafuer
//! die Klasse Anteile, und die steht auf der Detailebene bei jeder Adresse.

#include <array>
#include <cstddef>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/verlauf.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"
#include "kern/zustandsausgabe.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::zustandsausgabe {
namespace {

using zustand::Aggregat;
using zustand::FondsGroesse;
using zustand::Gebiet;
using zustand::Instrument;
using zustand::InstrumentFeld;
using zustand::MarktGroesse;
using zustand::PartieFeld;
using zustand::PolitischeGroesse;
using zustand::Sektor;

using zustand::GEBIETE;
using zustand::LAENDER;
using zustand::SEKTOREN_HANDELBAR;
using zustand::UEBERRENDITE_RUNDEN;

/// Die Kuerzel der fuenf Gebiete in der Reihenfolge aus T9.
///
/// Zweite Fassung derselben Liste -- `src/zustand.cpp` fuehrt sie fuer den Adressbau.
/// Sie steht hier trotzdem, und der Grund ist nicht Bequemlichkeit: Jene ist privat und
/// gehoert einer fremden Datei. Dass beide dieselbe Folge nennen, ist nicht behauptet,
/// sondern geprueft -- `zustandsausgabe_probe` haelt jedes Kuerzel gegen die Adresse
/// desselben Gebiets aus `index_zu_adresse` und wird rot, sobald eine der beiden Listen
/// umsortiert wird.
constexpr std::array<const char*, GEBIETE> GEBIET_KUERZEL = {"US", "CN", "DE", "BR", "RW"};

/// Die Namen der dreizehn Klassen aus T5, nach ihrer Nummer.
constexpr std::array<const char*, SKALENKLASSEN> KLASSENNAME = {
    "Fondsgeld",    "volkswirtschaftlich", "Raten",     "Anteile",
    "Nominalindex", "Wechselkurs",         "Realindex", "Personen",
    "Lobbydruck",   "Instrumentenstufe",   "Zaehler",   "Kennung",
    "Partieergebnis",
};

/// Die Einheiten derselben dreizehn Klassen, in derselben Reihenfolge.
///
/// Das ist die Spalte, wegen der die Detailebene ueberhaupt eine Klasse mitfuehrt: Ohne
/// sie ist `4200000000` eine Zahl und mit ihr ein Betrag von 42 Millionen Dollar.
constexpr std::array<const char*, SKALENKLASSEN> KLASSENEINHEIT = {
    "US-Cent",
    "Tausend USD zu konstanten Preisen 2015",
    "Basispunkte",
    "Zehntausendstel",
    "Index, Startjahr 10.000",
    "Index gegen USD, Startjahr 10.000",
    "Index, Startjahr 10.000, nie neu basiert",
    "Personen",
    "Lobbypunkte",
    "Stufe",
    "Stueck bzw. Runden",
    "Bitmuster ohne Groessenbedeutung",
    "Milli-Runden",
};

/// Die Namen der fuenf Herkunftsarten aus T45, nach ihrer Nummer.
constexpr std::array<const char*, HERKUNFTSARTEN> HERKUNFTSNAME = {
    "Datenanker", "Entwurf", "Parameter", "Manifest", "Vorgabe",
};

}  // namespace

const char* klassenname(Skalenklasse klasse)
{
    const std::size_t nummer = static_cast<std::size_t>(klasse);
    if (nummer < 1 || nummer > SKALENKLASSEN) {
        festkomma::abbruch("kern::zustandsausgabe::klassenname -- unbekannte Skalenklasse");
    }
    return KLASSENNAME[nummer - 1];
}

const char* klasseneinheit(Skalenklasse klasse)
{
    const std::size_t nummer = static_cast<std::size_t>(klasse);
    if (nummer < 1 || nummer > SKALENKLASSEN) {
        festkomma::abbruch("kern::zustandsausgabe::klasseneinheit -- unbekannte Skalenklasse");
    }
    return KLASSENEINHEIT[nummer - 1];
}

const char* herkunftsname(Herkunftsart herkunft)
{
    const std::size_t nummer = static_cast<std::size_t>(herkunft);
    if (nummer >= HERKUNFTSARTEN) {
        festkomma::abbruch("kern::zustandsausgabe::herkunftsname -- unbekannte Herkunftsart");
    }
    return HERKUNFTSNAME[nummer];
}

bool gehoert_zum_bereich(const char* adresse, const char* bereich) noexcept
{
    if (adresse == nullptr || bereich == nullptr || bereich[0] == '\0') {
        return false;
    }
    std::size_t i = 0;
    while (bereich[i] != '\0') {
        if (adresse[i] != bereich[i]) {
            return false;
        }
        ++i;
    }
    // Die Grenzbedingung: Der Vorspann muss dort enden, wo die Adresse einen Punkt hat
    // oder aufhoert. Ohne sie waere `land.U` ein Bereich mit 44 Adressen.
    return adresse[i] == '\0' || adresse[i] == '.';
}

namespace {

/// Haengt `<beschriftung><zahl>` an. Die Beschriftung traegt ihr eigenes Leerzeichen,
/// damit an der Aufrufstelle steht, wie die Zeile aussieht.
void feld(Uebersichtsblatt& blatt, const char* beschriftung, i64 wert)
{
    blatt.text(beschriftung);
    blatt.zahl(wert);
}

/// Die Zeile eines Gebiets in der Uebersichtstabelle.
///
/// Die Restwelt hat nach T15 keine Instrumente, keine Zustimmung, keinen
/// Aufsichtszaehler und keinen Einfluss. Ihre Spalten bleiben deshalb leer, statt eine
/// Null zu zeigen: Eine Null waere hier ein Wert, und es gibt keinen.
///
/// **Der Leitzins kommt aus dem Instrumentenstand und nicht aus dem Aggregat**, und das
/// ist keine Geschmacksfrage. T49 nennt beide Adressen dieselbe Groesse und regelt, wer
/// sie schreibt: Der Stand entsteht in Schritt 3, das Aggregat uebernimmt ihn in
/// Schritt 4. Wer hier das Aggregat laese, saehe in einer halb gerechneten Runde die
/// Zahl der Vorrunde -- die Uebersicht liest deshalb den Herrn und nicht den Gast.
/// Dasselbe gilt fuer den Haushaltssaldo.
void gebietszeile(Uebersichtsblatt& blatt, const zustand::Zustand& z, std::size_t nummer)
{
    const auto gebiet   = static_cast<Gebiet>(nummer);
    const bool spielbar = nummer < LAENDER;

    blatt.text(GEBIET_KUERZEL[nummer]);
    feld(blatt, " | BIP ", werte::bip(z, gebiet));

    if (spielbar) {
        feld(blatt, " | Zins ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Leitzins,
                                                                  InstrumentFeld::Stand)));
        feld(blatt, " | Zoll ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Zoll,
                                                                  InstrumentFeld::Stand)));
        feld(blatt, " | Haushalt ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Haushalt,
                                                                     InstrumentFeld::Stand)));
        feld(blatt, " | Regulierung ",
             z.lies(zustand::stelle_instrument(gebiet, Instrument::Regulierung,
                                               InstrumentFeld::Stand)));
        feld(blatt, " | Einfluss ",
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Einfluss)));
        feld(blatt, " | Zustimmung ",
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Zustimmung)));
        feld(blatt, " | Aufsicht ",
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Aufsichtszaehler)));
    } else {
        blatt.text(" | Zins - | Zoll - | Haushalt - | Regulierung - | Einfluss - "
                   "| Zustimmung - | Aufsicht -");
    }

    feld(blatt, " | Wechselkurs ", z.lies(zustand::stelle_aggregat(gebiet, Aggregat::Wechselkurs)));
    blatt.zeilenende();
}

}  // namespace

Uebersichtsblatt uebersicht(const zustand::Zustand& z, const werte::Konstanten& konstanten)
{
    Uebersichtsblatt blatt;

    blatt.text("Uebersicht (Ebene 1 von 3, T20) -- jede Zahl in der Skala ihrer Klasse, "
               "ungeteilt");
    blatt.zeilenende();

    feld(blatt, "Partie | Runde ", z.lies(zustand::stelle_partie(PartieFeld::Runde)));
    feld(blatt, " | Jahrgang ", z.lies(zustand::stelle_partie(PartieFeld::JahrgangId)));
    feld(blatt, " | Parametersatz ",
         z.lies(zustand::stelle_partie(PartieFeld::ParameterPruefsumme)));
    feld(blatt, " | Mandatsstand ", z.lies(zustand::stelle_partie(PartieFeld::Mandatsstand)));
    blatt.zeilenende();

    // Die einzige gerechnete Groesse der Uebersicht -- und damit die einzige Stelle, an
    // der diese Ebene abbrechen kann. Die Begruendung steht am Kopf der Funktion.
    feld(blatt, "Fonds | Vermoegen (US-Cent) ", werte::fondsvermoegen(z, konstanten));
    feld(blatt, " | Kasse ", z.lies(zustand::stelle_fonds(FondsGroesse::Kasse)));
    feld(blatt, " | Hebelstand ", z.lies(zustand::stelle_fonds(FondsGroesse::Hebelstand)));
    feld(blatt, " | Anlegerbestand ",
         z.lies(zustand::stelle_fonds(FondsGroesse::Anlegerbestand)));
    blatt.zeilenende();

    feld(blatt, "Fonds | Sichtbarkeit ", z.lies(zustand::stelle_fonds(FondsGroesse::Sichtbarkeit)));
    feld(blatt, " | Marktanteil ", z.lies(zustand::stelle_fonds(FondsGroesse::Marktanteil)));
    blatt.text(" (Zehntausendstel) | Ueberrendite (bp)");
    for (std::size_t n = 1; n <= UEBERRENDITE_RUNDEN; ++n) {
        feld(blatt, n == 1 ? " " : " / ", z.lies(zustand::stelle_ueberrendite(n)));
    }
    blatt.zeilenende();

    feld(blatt, "Markt | Korbwert ", z.lies(zustand::stelle_markt(MarktGroesse::Wert)));
    feld(blatt, " | Rendite (bp) ", z.lies(zustand::stelle_markt(MarktGroesse::Rendite)));
    for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
        blatt.text(" | Weltpreis Sektor ");
        blatt.zahl(static_cast<i64>(s));
        blatt.text(" ");
        blatt.zahl(z.lies(zustand::stelle_weltpreis(static_cast<Sektor>(s))));
    }
    blatt.zeilenende();

    blatt.text("Gebiet | BIP (Tausend USD) | die vier Instrumentenstaende | Einfluss, "
               "Zustimmung (Zehntausendstel) | Aufsicht | Wechselkurs");
    blatt.zeilenende();
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        gebietszeile(blatt, z, g);
    }

    blatt.text("Mandat | zweiteilig nach spiel.md: Fondsvermoegen ueber einer Schwelle UND "
               "Einfluss ueber einer");
    blatt.zeilenende();
    blatt.text("       | Schwelle in mindestens zwei Laendern. Beide Schwellen stehen nach T27 "
               "in parameter.toml");
    blatt.zeilenende();
    blatt.text("       | und nicht im Zustand -- diese Ebene zeigt beide Haelften und faellt "
               "kein Urteil.");
    blatt.zeilenende();

    // Die Grenze aus dem Arbeitspaket, als Abbruch und nicht als Absicht. Sie steht
    // hinter dem Schreiben und nicht davor: Wer eine Zeile ergaenzt, findet sie hier,
    // und was vergessen werden kann, gehoert in etwas, dessen Fehlen abbricht.
    //
    // Ein Abschneiden traegt sie nicht mit -- eine gekuerzte Ausgabe hat weniger Zeilen,
    // nicht mehr --, deshalb steht die zweite Bedingung daneben.
    if (blatt.zeilen() > UEBERSICHT_ZEILEN_MAX) {
        festkomma::abbruch("kern::zustandsausgabe::uebersicht -- mehr als 40 Zeilen");
    }
    if (blatt.abgeschnitten()) {
        festkomma::abbruch("kern::zustandsausgabe::uebersicht -- der Puffer hat nicht gereicht");
    }
    return blatt;
}

namespace {

/// Haengt `[K<nummer> <name>, <einheit>]` an -- die Skalenangabe, wegen der ein Leser
/// nicht raten muss, ob eine Zahl Cent, Basispunkte oder Personen sind.
///
/// Ueber die Puffergroesse gebunden und nicht ueber `Adressblatt`: Die dritte und die
/// vierte Ebene schreiben dieselbe Angabe in verschieden grosse Blaetter. Zwei Fassungen
/// koennten auseinanderlaufen, und dann naennte die eine Ebene eine andere Klasse als die
/// andere -- auf derselben Adresse.
template <std::size_t N>
void klassenangabe(Ausgabe<N>& blatt, Index platz)
{
    const Skalenklasse klasse = skalenklasse_von(platz);
    blatt.text("  [K");
    blatt.zahl(static_cast<i64>(klasse));
    blatt.text(" ");
    blatt.text(klassenname(klasse));
    blatt.text(", ");
    blatt.text(klasseneinheit(klasse));
    blatt.text("]");
}

/// Was an der Stelle der Differenz steht, wo T5 keine zulaesst.
///
/// Ein Strich, **dahinter ein Leerzeichen**, dann der Grund. Das Leerzeichen ist der
/// ganze Unterschied zu einem Minuszeichen: Hinter dem steht eine Ziffer, hinter diesem
/// nicht, und die Ebene liest nach T20 auch eine Maschine. Der Grund steht in der Zeile
/// und nicht in einem Dokument -- wer die Ausgabe liest, hat dort nichts nachzuschlagen.
///
/// Die Klassenangabe am Zeilenende nennt gleich danach `[K12 Kennung, Bitmuster ohne
/// Groessenbedeutung]`; beides zusammen sagt, was fehlt und warum.
constexpr const char* STRICH_STATT_DIFFERENZ = "-  (T5: auf einer Kennung nur Gleichheit)";

/// Haengt die Schlusszeile `<gezaehlt> von 310 Adressen <was>.` an.
///
/// Sie steht unter jedem Adressblatt, auch unter einem leeren, und das ist der ganze
/// Zweck: Eine Ausgabe ohne Zeilen und eine, in der nichts zu berichten war, sind sonst
/// dasselbe Zeichen fuer zwei verschiedene Lagen -- und die zweite ist ein Befund.
template <std::size_t N>
void schlusszeile(Ausgabe<N>& blatt, std::size_t gezaehlt, const char* was)
{
    blatt.zahl(static_cast<i64>(gezaehlt));
    blatt.text(" von ");
    blatt.zahl(static_cast<i64>(FELDER));
    blatt.text(" Adressen ");
    blatt.text(was);
    blatt.text(".");
    blatt.zeilenende();
}

/// Die Zeile einer geaenderten Adresse: alter Wert, neuer Wert, Differenz, Klasse.
///
/// **Die dritte Ebene und die vierte schreiben sie aus dieser einen Funktion**, und das
/// ist der Punkt: Die vierte ist die dritte mit einer zweiten Zeile darunter, nicht mit
/// einer anderen ersten. Zwei Fassungen dieser Zeile waeren zwei Antworten auf dieselbe
/// Frage, und die Probe auf die eine liesse die andere in Ruhe.
template <std::size_t N>
void unterschiedszeile(Ausgabe<N>& blatt, Index platz, i64 alt, i64 neu)
{
    blatt.text(zustand::index_zu_adresse(platz));
    blatt.text("  alt ");
    blatt.zahl(alt);
    blatt.text("  neu ");
    blatt.zahl(neu);
    blatt.text("  Differenz ");
    if (differenz_hat_bedeutung(skalenklasse_von(platz))) {
        // Auf `i128`, weil der Abstand zweier `i64` keine `i64` ist (ADR 0011,
        // Massnahme 3). Unter `-fwrapv` waere der Umlauf definiert und die Zahl
        // wohlgeformt falsch -- die Sorte Wert, die keine Pruefung bemerkt.
        blatt.zahl(static_cast<i128>(neu) - static_cast<i128>(alt));
    } else {
        // T5, Klasse 12: Hier ist die Subtraktion selbst der Fehler, nicht ihr
        // Ergebnisbereich. Die Ausnahme haengt an der Klasse und nicht an einer
        // Adressliste in dieser Datei -- eine zweite Liste waere die, die niemand
        // nachfuehrt.
        blatt.text(STRICH_STATT_DIFFERENZ);
    }
    klassenangabe(blatt, platz);
    blatt.zeilenende();
}

}  // namespace

Adressblatt detail(const zustand::Zustand& z, const char* bereich)
{
    Adressblatt blatt;

    blatt.text("Detail (Ebene 2 von 3, T20) -- Bereich ");
    blatt.text(bereich == nullptr ? "(ohne Namen)" : bereich);
    blatt.zeilenende();

    std::size_t gezaehlt = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        const char* adresse = zustand::index_zu_adresse(platz);
        if (!gehoert_zum_bereich(adresse, bereich)) {
            continue;
        }
        ++gezaehlt;
        blatt.text(adresse);
        blatt.text("  =  ");
        blatt.zahl(z.lies(platz));
        klassenangabe(blatt, platz);
        blatt.text("  Herkunft ");
        blatt.text(herkunftsname(herkunft_von(platz)));
        blatt.zeilenende();
    }

    if (gezaehlt == 0) {
        // Kein Fehler, sondern eine Antwort: Ein unbekannter Vorspann kommt aus
        // Protokoll, Testvorlage oder Oberflaeche und darf dort beantwortet werden --
        // dieselbe Haltung, die `adresse_zu_index` gegenueber einer unbekannten Adresse
        // einnimmt.
        blatt.text("Kein Vorspann dieses Namens -- ein Bereich ist ein Adressanfang nach T17, "
                   "der an einem Punkt endet.");
        blatt.zeilenende();
    }
    schlusszeile(blatt, gezaehlt, "in diesem Bereich");
    return blatt;
}

Adressblatt diff(const zustand::Zustand& vorher, const zustand::Zustand& nachher)
{
    Adressblatt blatt;

    blatt.text("Unterschied (Ebene 3 von 3, T20) -- alter Wert, neuer Wert, Differenz");
    blatt.zeilenende();

    std::size_t gezaehlt = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        const i64 alt = vorher.lies(platz);
        const i64 neu = nachher.lies(platz);
        if (alt == neu) {
            continue;
        }
        ++gezaehlt;
        unterschiedszeile(blatt, platz, alt, neu);
    }

    if (gezaehlt == 0) {
        blatt.text("Kein Feld unterscheidet sich -- die beiden Zustaende sind gleich.");
        blatt.zeilenende();
    }
    schlusszeile(blatt, gezaehlt, "geaendert");
    return blatt;
}

// ---------------------------------------------------------------------------
// Ebene 3 mit der Ursachenkette (T20) -- die vierte Abfrage
// ---------------------------------------------------------------------------

namespace {

using kern::verlauf::Aufloesung;
using kern::verlauf::Ende;
using kern::verlauf::KEIN_RUNDENPLATZ;
using kern::verlauf::Verlauf;

using schreiber::Ursache;
using schreiber::UrsacheArt;

/// Die Beschriftung der fuenf Enden aus `kern::verlauf`, nach ihrer Nummer.
///
/// Die Reihenfolge ist die der Aufzaehlung, und die Zusicherung darunter zaehlt nach,
/// dass keine Zeile fehlt: Kommt ein sechstes Ende dazu, ohne dass jemand hier eine Zeile
/// ergaenzt, ist der Bau rot statt die Ausgabe still falsch.
constexpr std::array<const char*, kern::verlauf::ENDEN> ENDENAME = {
    "ausloesende Aktion oder Gegenkraft (T20)",
    "Sollreihe des Jahrgangs -- im Modell ohne Vorgaenger",
    "Marktraeumung -- die Form nennt einen Sektor und keine Adresse",
    "kein frueherer Schreibzugriff im Verlauf -- davor steht der Startwert",
    "der Verlauf traegt zu dieser Adresse in dieser Runde keinen Schreibzugriff",
};

static_assert(ENDENAME.size() == kern::verlauf::ENDEN,
              "jedes Ende einer Ursachenkette traegt genau eine Beschriftung");

const char* endename(Ende ende)
{
    const std::size_t nummer = static_cast<std::size_t>(ende);
    if (nummer >= kern::verlauf::ENDEN) {
        festkomma::abbruch("kern::zustandsausgabe -- unbekanntes Ende einer Ursachenkette");
    }
    return ENDENAME[nummer];
}

/// Haengt die Ursache in der Form an, die T18 fuer sie nennt -- mit ihrem Beiwert und,
/// wo die Form eine Adresse nennt, mit deren Text nach T17.
///
/// Die Adresse steht ausgeschrieben und nicht als Platz: Wer die Kette liest, soll die
/// Ursache derselben Adresse zuordnen koennen, die die Zeile darueber nennt, ohne eine
/// Nummer nachzuschlagen.
template <std::size_t N>
void ursachenangabe(Ausgabe<N>& blatt, const Ursache& ursache)
{
    switch (ursache.art()) {
        case UrsacheArt::Aktion:
            blatt.text("Aktion ");
            blatt.zahl(static_cast<i64>(ursache.aktionsnummer()));
            return;
        case UrsacheArt::Instrument:
            // Der Stand ist die Groesse, die das Instrument im Zustand fuehrt -- Druck,
            // Gegendruck und Restverzoegerung sind seine Eingaben und nicht sein Wert.
            blatt.text("Instrument ");
            blatt.text(zustand::index_zu_adresse(zustand::stelle_instrument(
                ursache.land(), ursache.politikinstrument(), zustand::InstrumentFeld::Stand)));
            return;
        case UrsacheArt::Gegenkraft:
            blatt.text("Gegenkraft ");
            blatt.zahl(static_cast<i64>(ursache.gegenkraftart()));
            return;
        case UrsacheArt::Marktraeumung:
            blatt.text("Marktraeumung Sektor ");
            blatt.zahl(static_cast<i64>(zustand::sektor_index(ursache.sektor()) + 1U));
            return;
        case UrsacheArt::Vortrag:
            blatt.text("Vortrag ");
            blatt.text(zustand::index_zu_adresse(ursache.vortragsadresse()));
            return;
        case UrsacheArt::Jahrgang:
            blatt.text("Jahrgang");
            return;
    }
    festkomma::abbruch("kern::zustandsausgabe -- unbekannte Ursachenform: T18 kennt sechs");
}

/// Schreibt die Kette einer Adresse, Glied fuer Glied, und darunter ihr Ende.
///
/// Rueckgabe: ob die Adresse ueberhaupt einen Ursachensatz hatte. Die Schlusszeile des
/// Blattes zaehlt damit, was die Abnahme dieses Pakets ausschliessen will -- eine
/// geaenderte Adresse ohne Ursache.
bool kettenzeilen(Kettenblatt& blatt, const Verlauf& ketten, i64 bis, Index platz)
{
    Aufloesung kette{ketten, bis, platz};

    if (kette.leer()) {
        blatt.text("    ohne Ursachensatz in Runde ");
        blatt.zahl(bis);
        blatt.text(" -- ");
        blatt.text(endename(kette.ende()));
        blatt.zeilenende();
        return false;
    }

    // Erst schreiben, dann weitergehen: Das erste Glied steht schon nach dem Anlegen,
    // ein `while` davor ueberspraenge es.
    do {
        const schreiber::Ursachensatz& satz = kette.glied();
        blatt.text("    Glied ");
        blatt.zahl(static_cast<i64>(kette.glieder()));
        blatt.text("  Runde ");
        blatt.zahl(satz.runde);
        blatt.text("  ");
        ursachenangabe(blatt, satz.ursache);
        blatt.text("  Verzoegerung ");
        blatt.zahl(satz.verzoegerung);
        blatt.text("  Beitrag ");
        blatt.zahl(satz.beitrag);
        blatt.text(" Promille");
        blatt.zeilenende();
    } while (kette.weiter());

    // Die Runde des letzten Gliedes ist die der Ursache; `bis` ist die der Wirkung. Der
    // Abstand steht hier ausgerechnet, weil er die Frage beantwortet, wegen der T20 die
    // Kette ueberhaupt verlangt: wie lange die Ursache gebraucht hat. Auf `i128`, weil die
    // Differenz zweier `i64` keine `i64` ist.
    const i64 ursachenrunde = kette.glied().runde;
    blatt.text("    Ende nach ");
    blatt.zahl(static_cast<i64>(kette.glieder()));
    blatt.text(" Glied(ern): ");
    blatt.text(endename(kette.ende()));
    blatt.text(", Runde ");
    blatt.zahl(ursachenrunde);
    blatt.text(", ");
    blatt.zahl(static_cast<i128>(bis) - static_cast<i128>(ursachenrunde));
    blatt.text(" Runde(n) vor der Wirkung");
    blatt.zeilenende();
    return true;
}

}  // namespace

Kettenblatt diff_mit_kette(const zustand::Zustand& vorher, const zustand::Zustand& nachher,
                           const Verlauf& ketten)
{
    const i64 von = vorher.lies(zustand::stelle_partie(PartieFeld::Runde));
    const i64 bis = nachher.lies(zustand::stelle_partie(PartieFeld::Runde));

    if (von < 0 || bis < 0) {
        festkomma::abbruch("kern::zustandsausgabe::diff_mit_kette -- eine Runde vor der "
                           "ersten gibt es nicht");
    }
    if (bis <= von) {
        meldung::Meldung meldung;
        meldung.text("kern::zustandsausgabe::diff_mit_kette -- eine Spanne braucht zwei "
                     "Zeitpunkte: der zweite Zustand steht in Runde ");
        meldung.zahl(bis);
        meldung.text(", der erste in Runde ");
        meldung.zahl(von);
        meldung.text(". Fuer einen einzelnen Zeitpunkt gibt es die Unterschiedsebene "
                     "ohne Kette.");
        festkomma::abbruch(meldung.fertig());
    }
    if (ketten.platz_der_runde(bis) == KEIN_RUNDENPLATZ) {
        meldung::Meldung meldung;
        meldung.text("kern::zustandsausgabe::diff_mit_kette -- der Verlauf traegt die "
                     "Runde ");
        meldung.zahl(bis);
        meldung.text(" nicht; er traegt ");
        meldung.zahl(static_cast<i64>(ketten.runden()));
        meldung.text(" Runde(n). Ohne sie haette keine Adresse einen Anfangspunkt, und "
                     "das Blatt zeigte lauter Aenderungen ohne Ursache.");
        festkomma::abbruch(meldung.fertig());
    }

    Kettenblatt blatt;

    blatt.text("Unterschied mit Ursachenkette (Ebene 3 von 3, T20) -- alt, neu, Differenz "
               "und die Kette aus T18, rueckwaerts");
    blatt.zeilenende();
    blatt.text("Runde ");
    blatt.zahl(von);
    blatt.text(" bis Runde ");
    blatt.zahl(bis);
    blatt.text("; der Verlauf traegt ");
    blatt.zahl(static_cast<i64>(ketten.runden()));
    blatt.text(" Runde(n) mit ");
    blatt.zahl(static_cast<i64>(ketten.glieder()));
    blatt.text(" Glied(ern).");
    blatt.zeilenende();

    std::size_t gezaehlt      = 0;
    std::size_t mit_kette     = 0;
    std::size_t ohne_ursache  = 0;

    for (Index platz = 0; platz < FELDER; ++platz) {
        const i64 alt = vorher.lies(platz);
        const i64 neu = nachher.lies(platz);
        if (alt == neu) {
            continue;
        }
        ++gezaehlt;
        unterschiedszeile(blatt, platz, alt, neu);
        if (kettenzeilen(blatt, ketten, bis, platz)) {
            ++mit_kette;
        } else {
            ++ohne_ursache;
        }

        // Geprueft wird je Adresse und nicht am Schluss: Nur hier ist noch bekannt, an
        // welcher der Puffer ausging. Eine Marke am Ende des Textes sagt **dass**
        // gekuerzt wurde, diese Meldung sagt **wo** -- und ohne das Wo muss der naechste
        // Leser 310 Adressen absuchen.
        if (blatt.abgeschnitten()) {
            meldung::Meldung meldung;
            meldung.text("kern::zustandsausgabe::diff_mit_kette -- der Puffer hat nicht "
                         "gereicht; ausgegangen ist er bei ");
            meldung.adresse(platz);
            meldung.text(". Eine gekuerzte Kette waere eine Luege gegenueber dem Kaeufer "
                         "(T19).");
            festkomma::abbruch(meldung.fertig());
        }
    }

    if (gezaehlt == 0) {
        blatt.text("Kein Feld unterscheidet sich -- die beiden Zustaende sind gleich.");
        blatt.zeilenende();
    }
    schlusszeile(blatt, gezaehlt, "geaendert");

    // Die zweite Schlusszeile ist die Abnahmebedingung dieses Pakets in Zahlen: Sie sagt,
    // wie viele der geaenderten Adressen eine Ursache tragen und wie viele nicht. Eine
    // Ausgabe, die das nur zeigt, statt es zu zaehlen, laesst den Leser zaehlen.
    blatt.zahl(static_cast<i64>(mit_kette));
    blatt.text(" davon mit Ursachenkette, ");
    blatt.zahl(static_cast<i64>(ohne_ursache));
    blatt.text(" ohne.");
    blatt.zeilenende();

    return blatt;
}

}  // namespace kern::zustandsausgabe
