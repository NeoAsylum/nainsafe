#pragma once
//! `kern::zustandsausgabe` -- die drei Zustandsebenen aus G8 und T20: Uebersicht,
//! Detail, Unterschied.
//!
//! Vorgaben: T20 (drei Abfragen, eine Quelle), T49 (jede der 310 Adressen traegt genau
//! eine Skalenklasse), T45 und T46 (jede traegt genau einen Herkunftseintrag aus fuenf
//! Arten), T5 (was eine Klasse bedeutet), T13 (der Kern kennt weder Bildschirm noch
//! Datei noch Uhr), T2 (keine eigene Speicherverwaltung).
//!
//! ## Warum das hier keine Zugabe ist
//!
//! Das ist die Schnittstelle, ueber die diese Fabrik ihr eigenes Erzeugnis ueberhaupt
//! kennt. Selbstspieler, Rueckvergleicher, Bruchtester und jeder Pruefer lesen nichts
//! anderes; eine Groesse, die in keiner der drei Ausgaben vorkommt, ist fuer sie nicht
//! vorhanden. Deshalb ist die Deckung aller 310 Adressen eine nachgewiesene Eigenschaft
//! und keine Absicht -- `zustandsausgabe_probe` weist sie ueber die oeffentliche
//! Schnittstelle nach, und die Zuordnungstabelle unten weist beim **Uebersetzen** nach,
//! dass jede Adresse genau eine Klasse und genau eine Herkunft hat.
//!
//! ## Wie T13 eingehalten ist, obwohl hier Text entsteht
//!
//! Keine Stromausgabe, kein Dateizugriff, keine Zeitquelle. Die drei Aufrufe **geben
//! eine Zeichenkette zurueck**; wohin sie geht, entscheidet der Aufrufer. Der Puffer ist
//! ein `std::array` fester Groesse im Rueckgabewert, es gibt keine Zuteilung und keinen
//! wachsenden Behaelter -- dieselbe Bauart wie `kern::meldung`, nur groesser.
//!
//! Der Preis steht ausgeschrieben, damit ihn niemand suchen muss: Ein `Adressblatt` ist
//! rund 60 kB und lebt auf dem Stapel des Aufrufers. Das ist die Kehrseite von "keine
//! eigene Speicherverwaltung" und war die Wahl zwischen dieser Zahl und einem Behaelter,
//! den T2 ausschliesst.
//!
//! ## Was hier ausdruecklich NICHT steht
//!
//! **Die Ursachenkette.** T20 verlangt zum Unterschied zweier Zeitpunkte auch die Kette
//! aus T18, rueckwaerts aufgeloest. Sie steht nicht im Zustand, sondern nach T19 neben
//! ihm, und ein Verlauf ueber mehrere Runden ist noch nicht gebaut. Der Unterschied
//! sagt *was*; das *warum* kommt dazu, sobald es einen Traeger dafuer gibt. Das
//! Arbeitspaket verlangt fuer diesen Lauf die drei Zahlen -- alter Wert, neuer Wert,
//! Differenz --, und mehr ist hier nicht gebaut.
//!
//! **Farben, Rahmen, Ausrichtung.** Das ist die Sicht und nicht das Modell.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

namespace kern::zustandsausgabe {

using festkomma::i128;
using zustand::FELDER;
using zustand::i64;
using zustand::Index;

// ---------------------------------------------------------------------------
// T5 und T49 -- die dreizehn Skalenklassen
// ---------------------------------------------------------------------------

/// Die dreizehn Groessenklassen aus T5. Die Nummern sind die aus der Vorgabe und
/// stehen ausgeschrieben, nicht vom Uebersetzer vergeben: Sie erscheinen in der
/// Ausgabe und in `daten/adressen.md` als Zahl, und eine verschobene Nummer waere dort
/// eine falsche Angabe statt eines Uebersetzungsfehlers.
///
/// **Zwoelf davon tragen Zustandsadressen, die dreizehnte nicht.** `Partieergebnis` ist
/// das Ergebnis einer Partie nach T34 und liegt nicht im Zustand. Sie steht hier
/// trotzdem, weil T49 dreizehn Klassen kennt -- und weil die Zaehlung unten dann
/// nachweisen kann, dass genau diese eine leer bleibt, statt sie stillschweigend
/// wegzulassen.
enum class Skalenklasse : std::uint8_t {
    Fondsgeld           = 1,
    Volkswirtschaftlich = 2,
    Raten               = 3,
    Anteile             = 4,
    Nominalindex        = 5,
    Wechselkurs         = 6,
    Realindex           = 7,
    Personen            = 8,
    Lobbydruck          = 9,
    Instrumentenstufe   = 10,
    Zaehler             = 11,
    Kennung             = 12,
    Partieergebnis      = 13,
};

inline constexpr std::size_t SKALENKLASSEN              = 13;
inline constexpr std::size_t SKALENKLASSEN_MIT_ADRESSEN = 12;

static_assert(SKALENKLASSEN_MIT_ADRESSEN + 1 == SKALENKLASSEN,
              "T49: genau eine der dreizehn Klassen traegt keine Zustandsadresse");

/// Die fuenf Herkunftsarten aus T45. Ihre Bedeutung in je einem Satz:
///
///   `Datenanker`  der Startwert kommt aus einer Reihe der Reihenliste;
///   `Entwurf`     `spiel.md` schreibt in seiner Tabelle der Groessen ohne Datenanker
///                 einen Zahlenwert hin;
///   `Parameter`   der Wert steht nach T27 in `parameter.toml`;
///   `Manifest`    der Jahrgangsbau rechnet ihn und weist ihn im Manifest aus;
///   `Vorgabe`     `technik.md` selbst bestimmt ihn, abschliessend aufgezaehlt in T46.
///
/// **Der Eintrag ist die Stelle, die den Wert bestimmt, nicht die, die ihn erwaehnt**
/// (T45). Wo die Entwurfstabelle auf `parameter.toml` oder auf das Manifest
/// weiterverweist, lautet der Eintrag `Parameter` beziehungsweise `Manifest`; ein
/// Verweis ist kein zweiter Eintrag. Genau daran haengt, dass die Summe der fuenf
/// Zahlen unten 310 ergibt.
enum class Herkunftsart : std::uint8_t {
    Datenanker = 0,
    Entwurf    = 1,
    Parameter  = 2,
    Manifest   = 3,
    Vorgabe    = 4,
};

inline constexpr std::size_t HERKUNFTSARTEN = 5;

// ---------------------------------------------------------------------------
// Die Zuordnung, gerechnet statt abgeschrieben
// ---------------------------------------------------------------------------
//
// `daten/adressen.md` fuehrt Klasse und Herkunft je Adresse als Spalte. Hier steht
// **nicht** diese Spalte, sondern die Regel, aus der sie entsteht -- ausgedrueckt in
// denselben benannten Aufzaehlungen, aus denen `zustand.hpp` die Plaetze rechnet. Eine
// abgeschriebene Tabelle prueft sich nur selbst; eine gerechnete laesst sich gegen die
// Abzaehlungen aus T49 und T45 halten, und genau das tun die `static_assert` unten.
//
// Der Nachweis hat zwei Haelften, und beide sind noetig:
//
//   1. **Jede Adresse genau einmal.** Die Belegung zaehlt ihre Setzungen und ihre
//      Doppelbelegungen. 310 Setzungen ohne eine einzige Doppelbelegung heisst: 310
//      verschiedene Plaetze, also alle. Das ist wortgleich die Bedingung, an der der
//      Jahrgangsbau nach T45 abbricht -- eine Luecke und ein zweiter Eintrag.
//   2. **Die Mengen stimmen.** Zwoelf Klassenzahlen aus T49 und fuenf Herkunftszahlen
//      aus T45, jede einzeln. Ohne sie liesse sich dieselbe Menge falsch verteilen, und
//      Haelfte 1 bemerkte es nicht.

/// Das Ergebnis der Zuordnung: je Platz eine Klasse und eine Herkunft, dazu die beiden
/// Zaehler, aus denen der Deckungsnachweis entsteht.
///
/// Die Null heisst in beiden Feldern "noch nicht belegt". Bei der Klasse ist sie dafuer
/// frei, weil T5 ab eins zaehlt; bei der Herkunft zaehlt T45 ab null, deshalb liegt dort
/// die Aufzaehlung um eins verschoben. Ein Fehlerwert innerhalb des gueltigen Bereichs
/// waere von einem Wert nicht zu unterscheiden -- derselbe Grund, aus dem `KEIN_PLATZ`
/// ausserhalb der 310 liegt.
struct Zuordnung {
    std::array<std::uint8_t, FELDER> klasse{};
    std::array<std::uint8_t, FELDER> herkunft{};
    std::size_t                      setzungen = 0;
    std::size_t                      doppelt   = 0;
};

/// Baut die Zuordnung aus den Regeln von T49, T45 und T46.
///
/// Die Reihenfolge der Bloecke ist die von `daten/adressen.md`; die Plaetze kommen
/// ausschliesslich aus den `stelle_*`-Funktionen, nie aus einer Zahl. Damit verschiebt
/// eine Aenderung an der Feldordnung diese Tabelle mit, statt sie falsch werden zu
/// lassen.
[[nodiscard]] constexpr Zuordnung zuordnung_bauen()
{
    using namespace zustand;

    Zuordnung z{};

    const auto setze = [&z](Index platz, Skalenklasse klasse, Herkunftsart herkunft) {
        if (platz >= FELDER) {
            festkomma::abbruch("kern::zustandsausgabe -- Platz ausserhalb der 310 Felder");
        }
        if (z.klasse[platz] != 0) {
            ++z.doppelt;
        }
        z.klasse[platz]   = static_cast<std::uint8_t>(klasse);
        z.herkunft[platz] = static_cast<std::uint8_t>(static_cast<unsigned>(herkunft) + 1U);
        ++z.setzungen;
    };

    // --- die fuenf Gebietsbloecke -------------------------------------------
    //
    // Die ersten 21 Felder sind fuer alle fuenf gleich gebaut, und ihre Klassen sind es
    // auch. Die Herkunft trennt sich frueher als die Klasse: Vier Aggregate der
    // Restwelt liest nach T46 keine Modellregel, ihr Wechselkurs ist bedeutungslos, und
    // der Wechselkurs der USA ist der Numeraire.
    for (std::size_t g = 0; g < GEBIETE; ++g) {
        const auto gebiet    = static_cast<Gebiet>(g);
        const bool spielbar  = g < LAENDER;
        const auto ungelesen = spielbar ? Herkunftsart::Datenanker : Herkunftsart::Vorgabe;

        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            const auto sektor = static_cast<Sektor>(s);
            setze(stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Wertschoepfung),
                  Skalenklasse::Volkswirtschaftlich, Herkunftsart::Datenanker);
            setze(stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Kapitalstock),
                  Skalenklasse::Volkswirtschaftlich, Herkunftsart::Datenanker);
            setze(stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Beschaeftigung),
                  Skalenklasse::Personen, Herkunftsart::Datenanker);
            setze(stelle_sektorgroesse(gebiet, sektor, SektorGroesse::Preis),
                  Skalenklasse::Nominalindex, Herkunftsart::Entwurf);
        }

        setze(stelle_aggregat(gebiet, Aggregat::Bevoelkerung), Skalenklasse::Personen,
              Herkunftsart::Datenanker);
        setze(stelle_aggregat(gebiet, Aggregat::Erwerbstaetige), Skalenklasse::Personen,
              Herkunftsart::Datenanker);
        setze(stelle_aggregat(gebiet, Aggregat::Produktivitaet), Skalenklasse::Realindex,
              Herkunftsart::Datenanker);
        setze(stelle_aggregat(gebiet, Aggregat::Preisniveau), Skalenklasse::Nominalindex,
              Herkunftsart::Datenanker);
        setze(stelle_aggregat(gebiet, Aggregat::Inflation), Skalenklasse::Raten, ungelesen);
        setze(stelle_aggregat(gebiet, Aggregat::Leitzins), Skalenklasse::Raten, ungelesen);
        setze(stelle_aggregat(gebiet, Aggregat::Staatsschuld), Skalenklasse::Raten, ungelesen);
        setze(stelle_aggregat(gebiet, Aggregat::Haushaltssaldo), Skalenklasse::Raten, ungelesen);
        setze(stelle_aggregat(gebiet, Aggregat::Wechselkurs), Skalenklasse::Wechselkurs,
              (spielbar && gebiet != Gebiet::US) ? Herkunftsart::Datenanker
                                                 : Herkunftsart::Vorgabe);
        setze(stelle_basiswechsel(gebiet), Skalenklasse::Zaehler, Herkunftsart::Vorgabe);

        if (!spielbar) {
            continue;  // Die Restwelt hat weder Politik noch Instrumente noch Restdauern.
        }

        setze(stelle_politisch(gebiet, PolitischeGroesse::Zustimmung), Skalenklasse::Anteile,
              Herkunftsart::Parameter);
        setze(stelle_politisch(gebiet, PolitischeGroesse::Aufsichtszaehler),
              Skalenklasse::Zaehler, Herkunftsart::Entwurf);
        setze(stelle_politisch(gebiet, PolitischeGroesse::Einfluss), Skalenklasse::Anteile,
              Herkunftsart::Entwurf);

        for (std::size_t i = 0; i < INSTRUMENTE; ++i) {
            const auto instrument = static_cast<Instrument>(i);
            // Drei Instrumentenstaende sind Basispunkte mit historischem Politikpfad;
            // die Finanzmarktregulierung hat nach T5 keinen Anker und eine Stufenskala,
            // ihr Startwert kommt deshalb aus `parameter.toml`.
            const bool stufig = instrument == Instrument::Regulierung;
            setze(stelle_instrument(gebiet, instrument, InstrumentFeld::Stand),
                  stufig ? Skalenklasse::Instrumentenstufe : Skalenklasse::Raten,
                  stufig ? Herkunftsart::Parameter : Herkunftsart::Datenanker);
            setze(stelle_instrument(gebiet, instrument, InstrumentFeld::Druck),
                  Skalenklasse::Lobbydruck, Herkunftsart::Entwurf);
            setze(stelle_instrument(gebiet, instrument, InstrumentFeld::Gegendruck),
                  Skalenklasse::Lobbydruck, Herkunftsart::Entwurf);
            setze(stelle_instrument(gebiet, instrument, InstrumentFeld::Restverzoegerung),
                  Skalenklasse::Zaehler, Herkunftsart::Entwurf);
        }

        for (std::size_t r = 0; r < RESTDAUERZAEHLER; ++r) {
            setze(stelle_restdauer(gebiet, static_cast<Restdauerzaehler>(r)),
                  Skalenklasse::Zaehler, Herkunftsart::Entwurf);
        }
    }

    // --- Handel, Weltpreise, Nachahmer --------------------------------------
    for (std::size_t v = 0; v < GEBIETE; ++v) {
        for (std::size_t n = 0; n < GEBIETE; ++n) {
            if (v == n) {
                continue;  // Ein Gebiet handelt nicht mit sich selbst.
            }
            for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
                setze(stelle_handel(static_cast<Gebiet>(v), static_cast<Gebiet>(n),
                                    static_cast<Sektor>(s)),
                      Skalenklasse::Volkswirtschaftlich, Herkunftsart::Datenanker);
            }
        }
    }

    for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
        setze(stelle_weltpreis(static_cast<Sektor>(s)), Skalenklasse::Nominalindex,
              Herkunftsart::Entwurf);
    }

    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            setze(stelle_nachahmer(static_cast<Gebiet>(l), static_cast<Sektor>(s)),
                  Skalenklasse::Zaehler, Herkunftsart::Entwurf);
        }
    }

    // --- Marktkorb ----------------------------------------------------------
    //
    // `markt.wert` ist der einzige volkswirtschaftliche Betrag mit Herkunft `Manifest`:
    // Der Jahrgangsbau rechnet den Startkorb zu Startpreisen und weist ihn aus (T33).
    setze(stelle_markt(MarktGroesse::Wert), Skalenklasse::Volkswirtschaftlich,
          Herkunftsart::Manifest);
    setze(stelle_markt(MarktGroesse::Rendite), Skalenklasse::Raten, Herkunftsart::Entwurf);

    // --- Fondsaggregate und Ueberrenditen -----------------------------------
    setze(stelle_fonds(FondsGroesse::Kasse), Skalenklasse::Fondsgeld, Herkunftsart::Parameter);
    setze(stelle_fonds(FondsGroesse::Hebelstand), Skalenklasse::Fondsgeld,
          Herkunftsart::Entwurf);
    setze(stelle_fonds(FondsGroesse::Sichtbarkeit), Skalenklasse::Anteile,
          Herkunftsart::Entwurf);
    setze(stelle_fonds(FondsGroesse::Anlegerbestand), Skalenklasse::Fondsgeld,
          Herkunftsart::Parameter);
    setze(stelle_fonds(FondsGroesse::Marktanteil), Skalenklasse::Anteile,
          Herkunftsart::Entwurf);

    for (std::size_t n = 1; n <= UEBERRENDITE_RUNDEN; ++n) {
        setze(stelle_ueberrendite(n), Skalenklasse::Raten, Herkunftsart::Entwurf);
    }

    // --- die zwanzig Steckplaetze -------------------------------------------
    //
    // Alle zwanzig, auch der dauerhaft leere Waehrungsplatz der USA: Er ist eine
    // Adresse und traegt deshalb Klasse und Herkunft wie jede andere (T16). Was er
    // nicht ist, ist eine Moeglichkeit -- das entscheidet `steckplatz_spielbar` und
    // nicht diese Tabelle.
    for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
        setze(stelle_position(static_cast<Steckplatz>(p)), Skalenklasse::Zaehler,
              Herkunftsart::Entwurf);
    }

    // --- Beteiligungen ------------------------------------------------------
    for (std::size_t l = 0; l < LAENDER; ++l) {
        for (std::size_t s = 1; s <= SEKTOREN; ++s) {
            const auto land   = static_cast<Gebiet>(l);
            const auto sektor = static_cast<Sektor>(s);
            setze(stelle_beteiligung(land, sektor, BeteiligungsFeld::Anteil),
                  Skalenklasse::Anteile, Herkunftsart::Entwurf);
            setze(stelle_beteiligung(land, sektor, BeteiligungsFeld::Restdauer),
                  Skalenklasse::Zaehler, Herkunftsart::Entwurf);
        }
    }

    // --- Partie -------------------------------------------------------------
    //
    // Die beiden Kennungen sind die einzigen Adressen, auf denen nach T5 jede
    // Arithmetik ausser der Gleichheit ein Fehler ist. Sie stehen hier mit ihrer Klasse,
    // damit das in der Ausgabe abzulesen ist, statt in einem Dokument zu stehen.
    setze(stelle_partie(PartieFeld::Runde), Skalenklasse::Zaehler, Herkunftsart::Entwurf);
    setze(stelle_partie(PartieFeld::JahrgangId), Skalenklasse::Kennung,
          Herkunftsart::Manifest);
    setze(stelle_partie(PartieFeld::ParameterPruefsumme), Skalenklasse::Kennung,
          Herkunftsart::Parameter);
    setze(stelle_partie(PartieFeld::Mandatsstand), Skalenklasse::Zaehler,
          Herkunftsart::Entwurf);

    return z;
}

/// Die eine Zuordnung. Sie entsteht beim Uebersetzen; zur Laufzeit wird nur noch
/// nachgeschlagen.
inline constexpr Zuordnung ZUORDNUNG = zuordnung_bauen();

/// Wie viele Adressen eine Klasse traegt -- die Gegenrechnung zur Zerlegung aus T49.
[[nodiscard]] constexpr std::size_t adressen_der_klasse(Skalenklasse klasse) noexcept
{
    std::size_t anzahl = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (ZUORDNUNG.klasse[platz] == static_cast<std::uint8_t>(klasse)) {
            ++anzahl;
        }
    }
    return anzahl;
}

/// Wie viele Adressen eine Herkunftsart traegt -- die Gegenrechnung zu T45.
[[nodiscard]] constexpr std::size_t adressen_der_herkunft(Herkunftsart herkunft) noexcept
{
    std::size_t anzahl = 0;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (ZUORDNUNG.herkunft[platz]
            == static_cast<std::uint8_t>(static_cast<unsigned>(herkunft) + 1U)) {
            ++anzahl;
        }
    }
    return anzahl;
}

// Haelfte 1: keine Luecke, kein zweiter Eintrag -- die Bedingung, an der der
// Jahrgangsbau nach T45 abbricht, hier eine Ebene frueher und beim Uebersetzen.
static_assert(ZUORDNUNG.setzungen == FELDER,
              "T45/T49: jede der 310 Adressen bekommt genau eine Setzung");
static_assert(ZUORDNUNG.doppelt == 0,
              "T45: eine Adresse mit zwei Eintraegen haette zwei Herren ueber eine Zahl");

// Haelfte 2, erste Zerlegung: die zwoelf Klassenzahlen aus T49, einzeln.
static_assert(adressen_der_klasse(Skalenklasse::Fondsgeld) == 3);
static_assert(adressen_der_klasse(Skalenklasse::Volkswirtschaftlich) == 71);
static_assert(adressen_der_klasse(Skalenklasse::Raten) == 36);
static_assert(adressen_der_klasse(Skalenklasse::Anteile) == 22);
static_assert(adressen_der_klasse(Skalenklasse::Nominalindex) == 22);
static_assert(adressen_der_klasse(Skalenklasse::Wechselkurs) == 5);
static_assert(adressen_der_klasse(Skalenklasse::Realindex) == 5);
static_assert(adressen_der_klasse(Skalenklasse::Personen) == 25);
static_assert(adressen_der_klasse(Skalenklasse::Lobbydruck) == 32);
static_assert(adressen_der_klasse(Skalenklasse::Instrumentenstufe) == 4);
static_assert(adressen_der_klasse(Skalenklasse::Zaehler) == 83);
static_assert(adressen_der_klasse(Skalenklasse::Kennung) == 2);
static_assert(adressen_der_klasse(Skalenklasse::Partieergebnis) == 0,
              "T49: die dreizehnte Klasse ist das Partieergebnis und liegt nicht im Zustand");

// Haelfte 2, zweite Zerlegung: die fuenf Herkunftszahlen aus T45, einzeln.
static_assert(adressen_der_herkunft(Herkunftsart::Datenanker) == 136);
static_assert(adressen_der_herkunft(Herkunftsart::Entwurf) == 150);
static_assert(adressen_der_herkunft(Herkunftsart::Parameter) == 11);
static_assert(adressen_der_herkunft(Herkunftsart::Manifest) == 2);
static_assert(adressen_der_herkunft(Herkunftsart::Vorgabe) == 11,
              "T46 zaehlt seine elf Adressen abschliessend auf");

// Und beide Zerlegungen noch einmal als Summe. Sie ist nicht ueberfluessig neben den
// Einzelzahlen: Sie faengt den Fall, in dem eine Klasse dazukommt, deren Zeile hier
// niemand ergaenzt -- die siebzehn Zeilen darueber blieben dann gruen.
static_assert(adressen_der_klasse(Skalenklasse::Fondsgeld)
                      + adressen_der_klasse(Skalenklasse::Volkswirtschaftlich)
                      + adressen_der_klasse(Skalenklasse::Raten)
                      + adressen_der_klasse(Skalenklasse::Anteile)
                      + adressen_der_klasse(Skalenklasse::Nominalindex)
                      + adressen_der_klasse(Skalenklasse::Wechselkurs)
                      + adressen_der_klasse(Skalenklasse::Realindex)
                      + adressen_der_klasse(Skalenklasse::Personen)
                      + adressen_der_klasse(Skalenklasse::Lobbydruck)
                      + adressen_der_klasse(Skalenklasse::Instrumentenstufe)
                      + adressen_der_klasse(Skalenklasse::Zaehler)
                      + adressen_der_klasse(Skalenklasse::Kennung)
                      + adressen_der_klasse(Skalenklasse::Partieergebnis)
                  == FELDER,
              "T49: die dreizehn Klassen decken die 310 Adressen");
static_assert(adressen_der_herkunft(Herkunftsart::Datenanker)
                      + adressen_der_herkunft(Herkunftsart::Entwurf)
                      + adressen_der_herkunft(Herkunftsart::Parameter)
                      + adressen_der_herkunft(Herkunftsart::Manifest)
                      + adressen_der_herkunft(Herkunftsart::Vorgabe)
                  == FELDER,
              "T45: die fuenf Herkunftsarten decken die 310 Adressen");

/// Die Skalenklasse einer Adresse. Ein Platz ausserhalb `0 ... 309` bricht ab -- wie bei
/// `index_zu_adresse` ist das ein Rechenfehler des Aufrufers und keine offene Frage.
[[nodiscard]] constexpr Skalenklasse skalenklasse_von(Index platz)
{
    if (platz >= FELDER) {
        festkomma::abbruch("kern::zustandsausgabe::skalenklasse_von -- Platz ausserhalb der 310");
    }
    return static_cast<Skalenklasse>(ZUORDNUNG.klasse[platz]);
}

/// Die Herkunftsart einer Adresse. Bricht ab wie `skalenklasse_von`.
[[nodiscard]] constexpr Herkunftsart herkunft_von(Index platz)
{
    if (platz >= FELDER) {
        festkomma::abbruch("kern::zustandsausgabe::herkunft_von -- Platz ausserhalb der 310");
    }
    return static_cast<Herkunftsart>(ZUORDNUNG.herkunft[platz] - 1U);
}

/// Der Name einer Klasse, so wie T5 sie nennt.
[[nodiscard]] const char* klassenname(Skalenklasse klasse);

/// Die Einheit einer Klasse nach T5 -- die Angabe, wegen der niemand raten muss, ob
/// eine Zahl Cent, Basispunkte oder Personen sind.
[[nodiscard]] const char* klasseneinheit(Skalenklasse klasse);

/// Der Name einer Herkunftsart.
[[nodiscard]] const char* herkunftsname(Herkunftsart herkunft);

// ---------------------------------------------------------------------------
// Der Textpuffer
// ---------------------------------------------------------------------------

/// Zeichen je Zeile, grosszuegig: die laengste Adresse misst 47, dazu drei Zahlen zu je
/// hoechstens 40 Stellen und die Angaben zu Klasse und Herkunft.
inline constexpr std::size_t ZEILE_ZEICHEN = 192;

/// Die Grenze aus dem Arbeitspaket: die Uebersicht fasst hoechstens 40 Zeilen.
inline constexpr std::size_t UEBERSICHT_ZEILEN_MAX = 40;

/// Ein Puffer fester Groesse, an den nur angehaengt wird -- dieselbe Bauart und
/// dieselbe Begruendung wie `kern::meldung::Meldung`, nur mit `N` als Groesse und mit
/// einem Zeilenzaehler.
///
/// **Warum nicht `Meldung` selbst.** Sie fasst 512 Zeichen und haengt an jede Adresse
/// ihre laufende Nummer -- beides richtig fuer eine Abbruchmeldung und falsch fuer eine
/// Zustandsausgabe ueber 310 Zeilen. Sie zu einer Vorlage umzubauen hiesse, eine fremde
/// Datei zu aendern, an der die Abbruchstellen des halben Kerns haengen.
///
/// **Abgeschnitten statt uebergelaufen, und kenntlich statt still.** Ist der Puffer
/// voll, hoert das Anhaengen auf, `abgeschnitten()` sagt es dem Aufrufer, und der Text
/// endet auf `MARKE` fuer den Menschen im Protokoll. Ohne die Marke waere eine am Rand
/// gekuerzte Zahl von einer echten nicht zu unterscheiden.
template <std::size_t N>
class Ausgabe {
public:
    /// Worauf ein abgeschnittener Text endet. Eckige Klammern, weil sie -- anders als
    /// drei Punkte -- kein Satzzeichen sein koennen.
    static constexpr char MARKE[] = "[...]";

    /// Zeichen der Marke, ohne Abschlussnull. Hergeleitet, nicht abgeschrieben.
    static constexpr std::size_t MARKE_ZEICHEN = sizeof(MARKE) - 1;

    static_assert(N > MARKE_ZEICHEN + 1,
                  "ein Puffer, in den nicht einmal die Marke passt, markiert nichts");

    /// Haengt eine Zeichenkette an. `nullptr` ist ein leerer Anhang und kein Absturz --
    /// eine Ausgabe, die selbst abstuerzt, hilft niemandem.
    constexpr void text(const char* zeichenkette)
    {
        if (zeichenkette == nullptr) {
            return;
        }
        for (std::size_t i = 0; zeichenkette[i] != '\0'; ++i) {
            if (laenge_ + 1 >= puffer_.size()) {
                abgeschnitten_ = true;
                marke_setzen();
                return;
            }
            puffer_[laenge_] = zeichenkette[i];
            ++laenge_;
            puffer_[laenge_] = '\0';
        }
    }

    /// Haengt eine Ganzzahl in Zehnerschreibweise an -- **auf `i128`**, und das ist der
    /// Grund, warum es hier ueberhaupt eine eigene Zahlenumwandlung gibt.
    ///
    /// Die Differenz zweier `i64` ist keine `i64`: Der Abstand zwischen dem groessten
    /// und dem kleinsten liegt um eins ausserhalb. Unter `-fwrapv` waere das ein
    /// definierter Umlauf und damit eine wohlgeformte falsche Zahl -- genau die Sorte
    /// Wert, die keine Pruefung bemerkt. Die Unterschiedsebene rechnet deshalb auf
    /// `i128` (ADR 0011, Massnahme 3), und dann muss dieser Typ auch schreibbar sein.
    ///
    /// Der Betrag entsteht ueber `unsigned __int128`, wo auch der kleinste `i128`
    /// passt; sein Negatives waere nicht darstellbar. Vierundvierzig Ziffernplaetze
    /// tragen die laengste `i128` (39 Stellen) mit Luft.
    constexpr void zahl(i128 wert)
    {
        std::array<char, 44> ziffern{};
        std::size_t          stellen = 0;
        const bool           negativ = wert < 0;

        auto rest = negativ
                        ? (static_cast<unsigned __int128>(0)
                           - static_cast<unsigned __int128>(wert))
                        : static_cast<unsigned __int128>(wert);
        if (rest == 0) {
            ziffern[0] = '0';
            stellen    = 1;
        }
        while (rest != 0 && stellen < ziffern.size()) {
            ziffern[stellen] = static_cast<char>('0' + static_cast<int>(rest % 10));
            ++stellen;
            rest /= 10;
        }
        if (negativ) {
            const char minus[2] = {'-', '\0'};
            text(minus);
        }
        while (stellen > 0) {
            --stellen;
            const char eine[2] = {ziffern[stellen], '\0'};
            text(eine);
        }
    }

    /// Schliesst eine Zeile ab und zaehlt sie mit.
    ///
    /// Gezaehlt wird nur, was auch geschrieben wurde: Ist der Puffer voll, waechst
    /// weder Text noch Zaehler. Eine abgeschnittene Ausgabe hat deshalb **weniger**
    /// Zeilen als die vollstaendige und nie mehr -- wer die Zeilenzahl gegen eine
    /// Obergrenze prueft, prueft dann eine Zahl, die zu klein ist. Genau dafuer gibt es
    /// `abgeschnitten()` daneben.
    constexpr void zeilenende()
    {
        const std::size_t vorher = laenge_;
        text("\n");
        if (laenge_ > vorher) {
            ++zeilen_;
        }
    }

    [[nodiscard]] constexpr const char* fertig() const noexcept { return puffer_.data(); }
    [[nodiscard]] constexpr std::size_t laenge() const noexcept { return laenge_; }
    [[nodiscard]] constexpr std::size_t zeilen() const noexcept { return zeilen_; }
    [[nodiscard]] constexpr bool abgeschnitten() const noexcept { return abgeschnitten_; }

private:
    /// Schreibt `MARKE` ueber die letzten Zeichen. Ueberschreiben statt anhaengen: An
    /// dieser Aufrufstelle ist der Puffer voll, es ist kein Platz mehr da. Die
    /// Zusicherung oben haelt `beginn` innerhalb des Feldes.
    constexpr void marke_setzen()
    {
        if (laenge_ < MARKE_ZEICHEN) {
            return;  // zu kurz zum Markieren -- dann lieber der volle Reststext
        }
        const std::size_t beginn = laenge_ - MARKE_ZEICHEN;
        for (std::size_t i = 0; i < MARKE_ZEICHEN; ++i) {
            puffer_[beginn + i] = MARKE[i];
        }
    }

    std::array<char, N> puffer_{};
    std::size_t         laenge_        = 0;
    std::size_t         zeilen_        = 0;
    bool                abgeschnitten_ = false;
};

/// Die Uebersicht: hoechstens 40 Zeilen, also hoechstens so viele Zeichen.
inline constexpr std::size_t UEBERSICHT_ZEICHEN = UEBERSICHT_ZEILEN_MAX * ZEILE_ZEICHEN + 1;

/// Detail und Unterschied haben dieselbe Gestalt: eine Kopfzeile, hoechstens eine Zeile
/// je Adresse, eine Schlusszeile. Der Puffer traegt deshalb **alle** 310, auch wenn ein
/// einzelner Bereich hoechstens 64 hat -- eine Ebene, die bei der unguenstigen Anfrage
/// abschneidet, waere an der Stelle blind, an der man sie am dringendsten liest.
inline constexpr std::size_t ADRESSBLATT_ZEICHEN = (FELDER + 4) * ZEILE_ZEICHEN + 1;

using Uebersichtsblatt = Ausgabe<UEBERSICHT_ZEICHEN>;
using Adressblatt      = Ausgabe<ADRESSBLATT_ZEICHEN>;
