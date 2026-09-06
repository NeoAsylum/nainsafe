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
//! ## Die vierte Abfrage: der Unterschied mit seiner Ursachenkette
//!
//! T20 verlangt zum Unterschied zweier Zeitpunkte nicht nur alt, neu und Differenz,
//! sondern die Kette aus T18, **rueckwaerts aufgeloest bis zur ausloesenden Aktion oder
//! Gegenkraft, mit Verzoegerung und Beitrag je Glied**. Derselbe Absatz nennt die
//! Rangfolge: Der Unterschied sagt *was*, die Kette sagt *warum*, und massgeblich ist
//! die Kette.
//!
//! Sie steht nicht im Zustand, sondern nach T19 neben ihm -- `diff` sieht zwei Zustaende
//! und sonst nichts und kann sie deshalb nicht kennen, wie man es auch schriebe. Seit
//! Paket 0091 gibt es `diff_mit_kette`: dieselbe Ebene mit der Quelle, die ihr fehlte.
//! Die Aufloesung selbst steht in `kern::verlauf` und nicht hier; diese Datei nimmt sie
//! entgegen und schreibt sie hin.
//!
//! **`diff` bleibt daneben stehen, und das ist keine Doppelung.** Nicht jeder Aufrufer
//! hat einen Verlauf: Der Rueckvergleich zweier Speicherstaende hat zwei Zustaende und
//! keine Ketten, und der Pruefstand wirft sie nach T19 ausdruecklich weg, wenn er nur
//! Ergebnisse zaehlt. Wer dort trotzdem einen verlangte, bekaeme einen leeren -- und ein
//! leerer Verlauf sieht aus wie eine Partie, in der nichts eine Ursache hatte.
//!
//! ## Was hier ausdruecklich NICHT steht
//!
//! **Die Erzeugung der Glieder und ihre Sammlung.** Ein Ursachensatz entsteht in
//! `kern::schreiber`, gesammelt und rueckwaerts aufgeloest wird er in `kern::verlauf`.
//! An keinem Glied wird hier gerechnet.
//!
//! **Farben, Rahmen, Ausrichtung.** Das ist die Sicht und nicht das Modell.
//!
//! ## Auf zwei der 310 Adressen ist die Differenz keine Zahl
//!
//! Dort steht ein Strich mit seinem Grund: T5 erklaert auf den Kennungen jede Arithmetik
//! ausser der Gleichheit zum Fehler. Die Herleitung steht bei `differenz_hat_bedeutung`.

#include <array>
#include <cstddef>
#include <cstdint>

#include "kern/festkomma.hpp"
#include "kern/verlauf.hpp"
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
    //
    // Abgelesen wird es an genau einer Stelle: `diff` fragt `differenz_hat_bedeutung`
    // und setzt auf diesen beiden Adressen einen Strich mit Grund an die Stelle der
    // Differenz. Wer hier eine dritte Adresse auf `Kennung` legt, bekommt die Ausnahme
    // damit mit -- und wer eine dieser beiden umtraegt, verliert sie.
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

// ---------------------------------------------------------------------------
// T5, Klasse 12 -- wo eine Differenz keine ist
// ---------------------------------------------------------------------------
//
// Auf den Kennungen ist nach T5 jede Arithmetik ausser der Gleichheit ein Fehler, und
// der Grund steht in der Vorgabe daneben: Eine Pruefsumme, die versehentlich in eine
// Summe geraet, erzeugt eine Zahl, die keine Pruefung bemerkt, weil sie in keinem
// Wertebereich liegt. Die Unterschiedsebene subtrahiert -- auf genau diesen zwei der
// 310 Adressen darf sie es also nicht.
//
// **Was sie stattdessen tut, ist nicht Weglassen.** Alter und neuer Wert stehen wie
// ueberall sonst; nur an der Stelle der Differenz steht ein Strich mit seinem Grund.
// Die beiden verworfenen Wege, damit niemand sie fuer ungeprueft haelt: Eine
// weggelassene Zeile waere fuer den Selbstspieler dasselbe Zeichen wie -- hat sich
// nicht geaendert --, und eine ausgerechnete Zahl waere ein Ausschlag, der keiner ist.
// `4611686018427387904` minus `-6917529027641081856` ergibt `11529215046068469760`;
// die Zahl ist wohlgeformt, gross und bedeutet nichts.

/// Ob eine Differenz auf dieser Klasse ueberhaupt etwas bedeutet.
///
/// Die Frage steht hier und nicht als `if` an der Aufrufstelle, damit sie beim
/// Uebersetzen abzaehlbar ist: Kommt eine vierzehnte Klasse dazu, muss jemand
/// entscheiden, auf welcher Seite sie steht, statt sie stillschweigend rechnen zu
/// lassen. Die Zusicherung darunter zaehlt nach, dass es bei einer Ausnahme bleibt.
[[nodiscard]] constexpr bool differenz_hat_bedeutung(Skalenklasse klasse) noexcept
{
    return klasse != Skalenklasse::Kennung;
}

/// Wie viele der dreizehn Klassen keine Differenz tragen -- gezaehlt statt behauptet.
[[nodiscard]] constexpr std::size_t klassen_ohne_differenz() noexcept
{
    std::size_t anzahl = 0;
    for (std::size_t nummer = 1; nummer <= SKALENKLASSEN; ++nummer) {
        if (!differenz_hat_bedeutung(static_cast<Skalenklasse>(nummer))) {
            ++anzahl;
        }
    }
    return anzahl;
}

static_assert(klassen_ohne_differenz() == 1,
              "T5: allein Klasse 12 traegt Bitmuster ohne Groessenbedeutung");
static_assert(!differenz_hat_bedeutung(Skalenklasse::Kennung),
              "T5 Klasse 12: die Ausnahme gilt fuer die Kennungen");
static_assert(differenz_hat_bedeutung(Skalenklasse::Zaehler),
              "T5 Klasse 11: die Runde ist eine Zahl und ihre Differenz auch");

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

/// Wie viele Kettenzeilen die vierte Abfrage je geaenderter Adresse traegt.
///
/// **Hergeleitet und nicht gegriffen.** Eine rueckwaerts aufgeloeste Kette, die je Glied
/// mindestens eine Runde zurueckgeht, hat hoechstens so viele Glieder, wie der Verlauf
/// Runden aufnimmt; dazu kommt die Zeile, die das Ende der Kette nennt. Genau so lang ist
/// jede Kette, deren Ursachen in frueheren Runden liegen -- und das ist der Fall, den T20
/// beschreibt.
///
/// Laenger wird sie allein durch Glieder **innerhalb** einer Runde, also durch eine
/// Ursache, die auf eine in derselben Runde frueher geschriebene Adresse zeigt. Wie viele
/// davon hintereinander stehen koennen, sagt `specs/` nicht, und eine erfundene Zahl waere
/// eine Vorgabe, die dort nicht steht. Der Puffer traegt deshalb keinen Vorrat auf
/// Verdacht: Reicht er nicht, **bricht die Ebene ab** und nennt die Adresse. Eine
/// gekuerzte Kette waere genau die Luege, gegen die T19 geschrieben ist.
inline constexpr std::size_t KETTENZEILEN_JE_ADRESSE = verlauf::RUNDEN_KAPAZITAET + 1;

/// Der Puffer der vierten Abfrage: je Adresse ihre Wertzeile und ihre Kettenzeilen, dazu
/// Kopf und Schluss.
inline constexpr std::size_t KETTENBLATT_ZEICHEN =
    (FELDER * (1 + KETTENZEILEN_JE_ADRESSE) + 4) * ZEILE_ZEICHEN + 1;

using Kettenblatt = Ausgabe<KETTENBLATT_ZEICHEN>;

// Ein Kettenblatt ist gross, und die Zahl gehoert hingeschrieben statt gesucht: Sie liegt
// bei 1.667.360 Byte und damit bei knapp einem Fuenftel dessen, was ein Faden ueberhaupt
// an Stapel hat -- gemessen, `zustandsausgabe_probe` druckt beide Zahlen ab. Das ist die Kehrseite von T2 -- kein wachsender Behaelter, keine Zuteilung -- und
// dieselbe Rechnung, die `kern::verlauf` fuer seinen eigenen Kasten aufmacht. Die
// Zusicherung faengt beide Regler, die die linke Seite bewegen: die Zeilen je Adresse und
// die Zeichen je Zeile. Ihre rechte Seite ist gemessen und waechst mit keinem von beiden.
static_assert(sizeof(Kettenblatt) < verlauf::STAPEL_JE_FADEN,
              "T2: ein Kettenblatt lebt auf dem Stapel des Aufrufers und passt dort nicht "
              "mehr hinein -- die Zeilen je Adresse oder die Zeichen je Zeile wurden "
              "heraufgesetzt");

// ---------------------------------------------------------------------------
// Die Bereiche
// ---------------------------------------------------------------------------

/// Ein Bereich ist ein **Adressvorspann** nach T17, kein eigener Begriff daneben.
///
/// Damit beantwortet dieselbe Regel beide Fragen: die des Arbeitspakets (ein Bereich
/// vollstaendig) und die von T20, das `land.US`, `fonds`, `land.BR.instrument.zoll`,
/// `land.CN.sektor.1` und `markt` als adressierbare Einheiten nennt. Eine zweite,
/// engere Liste von Bereichen daneben waere die Stelle gewesen, an der T20 und dieses
/// Modul auseinanderlaufen.
///
/// Gehoerig ist eine Adresse, wenn der Vorspann zeichengleich vorn steht **und** dort
/// endet, wo die Adresse einen Punkt hat oder aufhoert. Ohne diese Bedingung waere
/// `land.U` ein Bereich; mit ihr ist es keiner. Ein leerer Vorspann gehoert zu nichts:
/// Ein Bereich ohne Namen ist keiner, und "alles" heisst hier nicht "nichts angegeben".
/// Ein Nullzeiger zaehlt wie der leere Vorspann.
[[nodiscard]] bool gehoert_zum_bereich(const char* adresse, const char* bereich) noexcept;

/// Wie viele Bereiche die 310 Adressen vollstaendig und ueberschneidungsfrei aufteilen.
inline constexpr std::size_t BEREICHE = 10;

/// Die zehn Bereiche selbst.
///
/// Sie sind **keine** Aufzaehlung zulaessiger Argumente -- `detail` nimmt jeden
/// Vorspann. Sie sind die Liste, an der sich die Deckung nachweisen laesst: Laeuft ein
/// Aufrufer sie ab, hat er jede der 310 Adressen genau einmal gesehen. Der Nachweis
/// steht in `zustandsausgabe_probe` und nicht hier, weil er die Adresstexte braucht und
/// `index_zu_adresse` keine Uebersetzungszeitfunktion ist.
///
/// `fonds` ist der einzige Bereich, dessen Adressen im Zustand nicht zusammenhaengen:
/// Die zwoelf Nachahmerzaehler liegen vor dem Marktkorb, die fuenf Fondsaggregate
/// dahinter. Genau deshalb schneidet diese Liste nach dem Namen und nicht nach dem
/// Platz -- eine Liste aus Indexbereichen haette `fonds` zerreissen muessen und damit
/// eine zweite Bereichsordnung neben der von T20 eingefuehrt.
inline constexpr std::array<const char*, BEREICHE> BEREICH_NAME = {
    "land.US", "land.CN",    "land.DE", "land.BR", "restwelt",
    "handel",  "welt.preis", "markt",   "fonds",   "partie",
};

// ---------------------------------------------------------------------------
// Die drei Ebenen
// ---------------------------------------------------------------------------

/// **Ebene 1 -- der Gesamtzustand in einem Blick**, hoechstens 40 Zeilen.
///
/// Enthaelt, was das Arbeitspaket verlangt: Fondsvermoegen, Einfluss je Land, die vier
/// Politikinstrumente je Land, die Runde und den Stand gegenueber der Siegbedingung.
/// Die Grenze von 40 Zeilen ist keine Absicht, sondern gerechnet und geprueft: Der
/// Puffer traegt genau so viele, und die Funktion bricht ab, wenn sie mehr geschrieben
/// haette.
///
/// **Zum Mandat, damit die Zeile nicht mehr verspricht, als sie halten kann.** Die
/// Siegbedingung nach `spiel.md` ist zweiteilig -- Fondsvermoegen ueber einer Schwelle
/// **und** Einfluss ueber einer Schwelle in mindestens zwei Laendern. Beide Schwellen
/// stehen nach T27 in `parameter.toml` und liegen dem Kern an dieser Stelle nicht vor.
/// Die Uebersicht zeigt deshalb die beiden gemessenen Haelften und den Mandatsstand aus
/// dem Zustand, und sie faellt kein Urteil.
///
/// **Sie erbt die Wertebereichsschranken aus T47, und das ist Absicht.** Das
/// Fondsvermoegen entsteht ueber `werte::fondsvermoegen`; auf einem Zustand, dessen
/// Wechselkurs kleiner als eins ist, bricht diese Rechnung ab, und dieser Aufruf mit
/// ihr. Hier steht **keine zweite Fassung** jener Schranke daneben -- eine Regel mit
/// zwei Herren laeuft auseinander, und die zweite Fassung waere die, die niemand
/// nachfuehrt. Wer eine Ausgabe ueber einen kaputten Zustand braucht, nimmt `detail`
/// und `diff`: Beide lesen nur ab und rechnen nichts.
[[nodiscard]] Uebersichtsblatt uebersicht(const zustand::Zustand&  z,
                                          const werte::Konstanten& konstanten);

/// **Ebene 2 -- ein Bereich vollstaendig.**
///
/// Je Adresse des Bereichs eine Zeile mit Wert, Skalenklasse samt Einheit und
/// Herkunftsart. Wer hier liest, muss nicht raten, ob eine Zahl Cent oder Tausend ist.
///
/// Kein Treffer ist kein Fehler: Ein unbekannter Vorspann kommt aus Protokoll,
/// Testvorlage oder Oberflaeche und bekommt eine Zeile, die genau das sagt -- dieselbe
/// Haltung wie `adresse_zu_index` gegenueber einer unbekannten Adresse.
///
/// Diese Ebene rechnet nichts und bricht deshalb auf keinem Zustand ab.
[[nodiscard]] Adressblatt detail(const zustand::Zustand& z, const char* bereich);

/// **Ebene 3 -- was sich zwischen zwei Zeitpunkten geaendert hat.**
///
/// Je geaenderter Adresse alter Wert, neuer Wert und Differenz, dazu die Skalenklasse,
/// ohne die die Differenz keine Bedeutung hat. Das ist die Ebene, an der ein Agent
/// erkennt, **ob eine Aenderung gewirkt hat und wie**.
///
/// Die Differenz ist der neue Wert minus dem alten, gerechnet auf `i128`: Sie passt
/// nicht immer in `i64`, und ein Umlauf waere hier eine wohlgeformte falsche Zahl.
///
/// **Auf den beiden Kennungen steht dort keine Zahl**, sondern
/// `Differenz -  (T5: auf einer Kennung nur Gleichheit)`. Der Strich traegt ein
/// Leerzeichen hinter sich und ist damit von einem Minuszeichen zu unterscheiden, hinter
/// dem eine Ziffer steht -- die Ebene liest nach T20 auch eine Maschine. Alter und neuer
/// Wert stehen unveraendert daneben, und jede Adresse der zwoelf uebrigen Klassen behaelt
/// ihre gerechnete Differenz. Warum das so ist, steht bei `differenz_hat_bedeutung`.
///
/// Sind beide Zustaende gleich, sagt das Blatt das ausdruecklich in einer Zeile. Eine
/// leere Ausgabe und eine, in der nichts zu berichten war, waeren sonst dasselbe
/// Zeichen fuer zwei verschiedene Lagen.
///
/// Diese Ebene rechnet keine Modellgroesse und bricht deshalb auf keinem Zustand ab.
[[nodiscard]] Adressblatt diff(const zustand::Zustand& vorher, const zustand::Zustand& nachher);

/// **Ebene 3 mit der Ursachenkette aus T18 -- die vierte Abfrage.**
///
/// Je geaenderter Adresse dieselbe Zeile wie bei `diff` -- zeichengleich, aus derselben
/// Funktion -- und darunter je ein Glied der Kette: Runde, Ursache, Verzoegerung und
/// Beitrag. Die Kette laeuft rueckwaerts, vom Schreibzugriff der letzten Runde bis zu der
/// Aktion oder Gegenkraft, die ihn ausgeloest hat; eine Schlusszeile nennt das Ende und
/// wie viele Runden zwischen Ursache und Wirkung liegen.
///
/// **Die beiden Zeitpunkte stehen in den Zustaenden und nicht in Argumenten daneben.**
/// `partie.runde` traegt die Nummer der letzten abgeschlossenen Runde; daraus kommt die
/// Spanne. Zwei Argumente daneben liessen sich falsch besetzen, und die Kette nennte dann
/// Runden einer anderen Spanne als die Zahlen darueber -- ein Widerspruch innerhalb
/// desselben Blattes, den niemand sieht.
///
/// **Harte Fehler, alle ohne Ersatzwert:**
///   * die Runde des zweiten Zustands ist nicht groesser als die des ersten. Eine Spanne
///     braucht zwei Zeitpunkte; fuer einen einzelnen gibt es `diff`;
///   * eine der beiden Rundennummern ist negativ -- eine Runde vor der ersten gibt es
///     nicht;
///   * der Verlauf traegt die Runde des zweiten Zustands nicht. Ohne sie haette keine
///     einzige Adresse einen Anfangspunkt, und das Blatt zeigte 310 Aenderungen ohne
///     Ursache -- ein Bild, das aussieht wie ein Befund und keiner ist;
///   * der Puffer reicht nicht. Die Meldung nennt die Adresse, an der er ausging.
///
/// **Eine geaenderte Adresse ohne Ursachensatz bricht dagegen nicht ab**, sondern bekommt
/// eine Zeile, die genau das sagt, und die Schlusszeile zaehlt sie mit. Der Unterschied
/// ist Absicht: Das eine ist ein Fehler des Aufrufers, das andere ein Befund ueber die
/// Partie -- und ein Befund, der den Lauf beendet, wird nicht gelesen, sondern umgangen.
///
/// Diese Ebene rechnet keine Modellgroesse und bricht deshalb auf keinem Zustand ab,
/// dessen Werte ausserhalb ihrer Wertebereiche liegen.
[[nodiscard]] Kettenblatt diff_mit_kette(const zustand::Zustand&   vorher,
                                         const zustand::Zustand&   nachher,
                                         const verlauf::Verlauf&   ketten);

}  // namespace kern::zustandsausgabe
