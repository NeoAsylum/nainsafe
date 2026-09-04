//! Laufende Probe fuer `kern::zustand`.
//!
//! Die Deckung der 310 Adressen ist in `src/zustand.cpp` schon als `static_assert`
//! bewiesen und damit beim Uebersetzen geprueft. Diese Probe gibt es fuer vier Dinge,
//! die ein `static_assert` nicht kann:
//!
//!   1. **Das Testprofil aus ADR 0011, Massnahme 2.** Sie linkt `kern_geprueft`, also
//!      dieselben Quellen mit `-fsanitize=undefined,address`. Ein Sanitizer sieht nur,
//!      was wirklich laeuft; deshalb wird hier alles noch einmal zur Laufzeit
//!      durchgezaehlt, statt sich auf die Uebersetzungsrechnung zu verlassen.
//!   2. **Den Nachweis ueber die oeffentliche Schnittstelle.** Der Deckungslauf in
//!      `src/zustand.cpp` sieht die Adresstabelle von innen. Diese Probe kennt sie
//!      nicht -- sie geht ausschliesslich ueber `index_zu_adresse`,
//!      `adresse_zu_index` und die `stelle_*`-Funktionen. Was hier durchgeht, geht
//!      auch fuer Protokoll, Kette, Testvorlagen und Oberflaeche durch.
//!   3. **Zwei Wege zu derselben Zahl.** `pruefsumme_von` rechnet ueber die Kette
//!      Feld fuer Feld, `fnv1a64(nach_bytes(...))` ueber die fertige Bytefolge.
//!      Stimmen beide ueberein, ist die Byteform belegt und nicht behauptet. Fuer den
//!      Nullzustand kommt ein dritter Weg dazu: die geschlossene Form
//!      `Anfangswert * Primzahl^2480`, gerechnet mit modularem Potenzieren -- eine
//!      Zahl, die in keinem der beiden anderen Wege vorkommt.
//!   4. **Die Zahlen im Wortlaut.** Was diese Probe ausrechnet, schreibt sie hin.
//!   5. **Den Startwertzugang und seinen Riegel** (Paket 0027). Dass der Zustand von
//!      aussen nicht mehr schreibbar ist, steht als `static_assert` weiter unten und
//!      ist damit Sache des Uebersetzers. Dass der eine erlaubte Zugang vor der ersten
//!      Runde traegt und danach abbricht, ist es nicht -- ein Abbruch laesst sich nur
//!      zur Laufzeit fangen, und seine Meldung gehoert ins Protokoll.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <type_traits>

#include "kern/pruefsumme.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::zustand::Adressfund;
using kern::zustand::Aggregat;
using kern::zustand::BeteiligungsFeld;
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
using kern::zustand::Startbelegung;
using kern::zustand::Steckplatz;
using kern::zustand::u64;
using kern::zustand::Zustand;

using kern::zustand::adresse_zu_index;
using kern::zustand::index_zu_adresse;
using kern::zustand::nach_bytes;
using kern::zustand::pruefsumme_von;
using kern::zustand::steckplatz_anleihe;
using kern::zustand::steckplatz_sektor;
using kern::zustand::steckplatz_spielbar;
using kern::zustand::steckplatz_waehrung;
using kern::zustand::stelle_aggregat;
using kern::zustand::stelle_basiswechsel;
using kern::zustand::stelle_beteiligung;
using kern::zustand::stelle_fonds;
using kern::zustand::stelle_handel;
using kern::zustand::stelle_instrument;
using kern::zustand::stelle_markt;
using kern::zustand::stelle_nachahmer;
using kern::zustand::stelle_partie;
using kern::zustand::stelle_politisch;
using kern::zustand::stelle_position;
using kern::zustand::stelle_restdauer;
using kern::zustand::stelle_sektorgroesse;
using kern::zustand::stelle_ueberrendite;
using kern::zustand::stelle_weltpreis;

using kern::zustand::AGGREGATE;
using kern::zustand::BETEILIGUNGSFELDER;
using kern::zustand::BYTES;
using kern::zustand::FELDER;
using kern::zustand::FONDSGROESSEN;
using kern::zustand::GEBIETE;
using kern::zustand::INSTRUMENTE;
using kern::zustand::INSTRUMENTFELDER;
using kern::zustand::KEIN_PLATZ;
using kern::zustand::LAENDER;
using kern::zustand::MARKTGROESSEN;
using kern::zustand::PARTIEFELDER;
using kern::zustand::POLITISCHE_GROESSEN;
using kern::zustand::RESTDAUERZAEHLER;
using kern::zustand::SEKTOREN;
using kern::zustand::SEKTOREN_HANDELBAR;
using kern::zustand::SEKTORGROESSEN;
using kern::zustand::STECKPLAETZE;
using kern::zustand::STECKPLAETZE_SPIELBAR;
using kern::zustand::UEBERRENDITE_RUNDEN;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// Weist nach, dass ein Aufruf abbricht -- und schreibt die Meldung mit.
///
/// Der Wortlaut gehoert ins Protokoll: Ein `catch (...)` belegt nur, dass *irgendwo*
/// etwas geworfen wurde. Erst die Meldung zeigt, dass es die Indexpruefung war, die
/// abgebrochen hat, und nicht ein anderer Fehler auf demselben Weg.
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

/// Legt einen Startwert -- der Zugang aus Paket 0027, als Einzeiler.
///
/// Diese Probe kennt den Schreiber nicht und spielt keine Runde; sie baut
/// Ausgangslagen. Genau dafuer gibt es `Startbelegung`, und genau deshalb steht sie
/// hier statt eines Schreibzugriffs auf den Zustand: Den gibt es von aussen nicht
/// mehr, und die Probe unten weist das auch nach.
void startwert(Zustand& ziel, Index platz, i64 wert) { Startbelegung{ziel}.setze(platz, wert); }

// ---------------------------------------------------------------------------
// Der Nachweis, dass der alte Weg zu ist -- beim Uebersetzen statt zur Laufzeit
// ---------------------------------------------------------------------------
//
// Eine Zusage ueber Sichtbarkeit ist eine Eigenschaft des Codes oder keine, also
// gehoert ihr Nachweis in den Uebersetzungslauf und nicht in eine gefangene Ausnahme.
// Die Frage laeuft ueber einen Typparameter und nicht ueber den Typ selbst: Ein
// `requires` mit einem nicht abhaengigen Ausdruck ist ein harter Uebersetzungsfehler
// statt `false` -- dann waere die Probe selbst der Fehler, den sie belegen soll.
//
// Gefragt wird nach der Adresse des Elements und nicht nach einem geschriebenen
// Zugriff. Der Grund ist die Grep-Regel aus der Abnahme: Ein Suchmuster, das in der
// Datei steht, die es pruefen soll, geht nie leer aus.

template <typename Z>
constexpr bool hat_offenes_feld = requires { &Z::feld; };

template <typename Z>
constexpr bool hat_offenen_schreibzugriff = requires { &Z::schreibe; };

template <typename Z>
constexpr bool hat_rohen_schreibzugriff = requires { &Z::lege_ab; };

template <typename Z>
constexpr bool hat_lesezugriff = requires { &Z::lies; };

static_assert(!hat_offenes_feld<Zustand>, "T18: die 310 Groessen sind von aussen nicht erreichbar");
static_assert(!hat_offenen_schreibzugriff<Zustand>,
              "T18: den frueheren oeffentlichen Schreibzugriff gibt es nicht mehr");
static_assert(!hat_rohen_schreibzugriff<Zustand>,
              "T18: auch der neue rohe Schreibzugriff ist von aussen nicht erreichbar");

// Die Gegenprobe, an der eine zu grobe Fassung dieser Frage auffliegt: Waere hier
// alles unerreichbar, sagten die drei Zeilen oben nichts ueber Sichtbarkeit aus,
// sondern nur darueber, dass `requires` immer `false` liefert.
static_assert(hat_lesezugriff<Zustand>, "lesen bleibt jedem erlaubt -- sonst prueft das hier nichts");

// ---------------------------------------------------------------------------
// Und dieselbe Art Nachweis fuer den Startwertzugang selbst
// ---------------------------------------------------------------------------
//
// Zwei Fragen des Ruecklaufs 1 zu Paket 0027 sind hier beantwortet statt beschrieben:
// ob eine Kopie das Schreibrecht mitnimmt, und ob sich ein Zugang an einen Zustand
// binden laesst, den er nicht ueberlebt. Beide Antworten sind "nein", und beide gelten
// beim Uebersetzen -- die Begruendungen stehen an der Klasse in `zustand.hpp`.

static_assert(!std::is_copy_constructible_v<Startbelegung>,
              "eine Kopie nimmt das Schreibrecht nicht mit, weil keine entstehen kann");
static_assert(!std::is_move_constructible_v<Startbelegung>,
              "auch verschieben gibt es nicht -- sonst liesse sich ein Zugang wegspeichern");
static_assert(!std::is_copy_assignable_v<Startbelegung>, "ein Zugang wird nicht umgehaengt");
static_assert(!std::is_move_assignable_v<Startbelegung>, "ein Zugang wird nicht umgehaengt");
static_assert(!std::is_constructible_v<Startbelegung, Zustand&&>,
              "kein Zugang auf einen Zustand ohne Namen -- er wuerde ihn nicht ueberleben");

// Die Gegenprobe, ohne die die fuenf Zeilen oben nur belegten, dass diese Frage immer
// `false` liefert: An einen benannten Zustand laesst sich sehr wohl einer binden.
static_assert(std::is_constructible_v<Startbelegung, Zustand&>,
              "an einen benannten Zustand bindet der Zugang -- sonst prueft das hier nichts");

/// Nimmt dem Uebersetzer die Konstantenfaltung, damit die Sanitizer die Rechnung
/// wirklich zu sehen bekommen.
i64 undurchsichtig(i64 wert)
{
    volatile i64 zwischenlager = wert;
    return zwischenlager;
}

std::size_t undurchsichtig_index(std::size_t wert)
{
    volatile std::size_t zwischenlager = wert;
    return zwischenlager;
}

/// Zaehlt, wie oft jeder der 310 Plaetze getroffen wurde.
struct Strichliste {
    std::array<int, FELDER> treffer{};

    void vermerke(Index platz, int zeile)
    {
        pruefe(platz < FELDER, "Stelle innerhalb der 310 Felder", zeile);
        if (platz < FELDER) {
            ++treffer[platz];
        }
    }
};

/// `x^n mod 2^64`, mit vorzeichenlosen Zahlen -- der Umbruch ist die Rechenvorschrift
/// und kein Fehlerfall. Der dritte Weg zur Summe des Nullzustands: Ueber 2.480
/// Nullbytes ist FNV-1a-64 genau `Anfangswert * Primzahl^2480`, weil das Verodern mit
/// null nichts aendert und nur die Multiplikation uebrig bleibt.
u64 potenz_mod_2hoch64(u64 basis, std::size_t exponent)
{
    u64 ergebnis = 1;
    u64 faktor = basis;
    std::size_t rest = exponent;
    while (rest > 0) {
        if ((rest & 1u) != 0u) {
            ergebnis *= faktor;
        }
        faktor *= faktor;
        rest >>= 1u;
    }
    return ergebnis;
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)
#define VERMERKE(liste, stelle) (liste).vermerke((stelle), __LINE__)
#define ERWARTE_ABBRUCH(ausdruck) \
    erwarte_abbruch([&] { ausdruck; }, #ausdruck, __LINE__)

int main()
{
    // --- Die feste Groesse (T15, Abnahme 1) --------------------------------------
    {
        PRUEFE(sizeof(Zustand) == 2480);
        PRUEFE(sizeof(Zustand) / sizeof(i64) == FELDER);
        PRUEFE(FELDER == 310);
        PRUEFE(BYTES == 2480);
        std::fprintf(stdout, "sizeof(Zustand) = %zu Byte, %zu Felder\n", sizeof(Zustand),
                     sizeof(Zustand) / sizeof(i64));
    }

    // --- Beide Richtungen der Adressabbildung, ueber alle 310 (T17, Abnahme 3) ----
    //
    // Vorwaerts: jeder Platz hat eine Adresse. Rueckwaerts: diese Adresse fuehrt
    // genau auf denselben Platz zurueck. Beides ueber die oeffentliche
    // Schnittstelle, ohne die Tabelle zu kennen.
    {
        Strichliste rundlauf;
        for (Index i = 0; i < FELDER; ++i) {
            const char* adresse = index_zu_adresse(undurchsichtig_index(i));
            PRUEFE(adresse != nullptr);
            const Adressfund fund = adresse_zu_index(adresse);
            PRUEFE(fund.gefunden);
            PRUEFE(fund.index == i);
            if (fund.gefunden) {
                VERMERKE(rundlauf, fund.index);
            }
        }
        int genau_einmal = 0;
        for (Index i = 0; i < FELDER; ++i) {
            if (rundlauf.treffer[i] == 1) {
                ++genau_einmal;
            }
        }
        PRUEFE(genau_einmal == 310);
        std::fprintf(stdout, "Rundlauf Adresse <-> Platz: %d von 310 genau einmal\n",
                     genau_einmal);
    }

    // --- Was nicht im Verzeichnis steht, wird nicht gefunden ----------------------
    {
        PRUEFE(!adresse_zu_index("land.US.sektor.4.preis").gefunden);
        PRUEFE(!adresse_zu_index("land.RW.leitzins").gefunden);
        PRUEFE(!adresse_zu_index("land.US.instrument.leitzins.rest").gefunden);
        PRUEFE(!adresse_zu_index("handel.US.US.1").gefunden);
        PRUEFE(!adresse_zu_index("fonds.position.waehrung.RW").gefunden);
        PRUEFE(!adresse_zu_index("").gefunden);
        PRUEFE(!adresse_zu_index(nullptr).gefunden);

        // Ein echtes Praefix und eine echte Verlaengerung sind beide keine Adresse.
        PRUEFE(!adresse_zu_index("land.US.sektor.1.preis.").gefunden);
        PRUEFE(!adresse_zu_index("land.US.sektor.1.prei").gefunden);
        PRUEFE(adresse_zu_index("land.US.sektor.1.preis").gefunden);

        // Und die Gegenprobe zu Befund 1 des Verzeichnisses: geschrieben wird
        // `restverzoegerung`, nicht `rest`.
        PRUEFE(adresse_zu_index("land.BR.instrument.zoll.restverzoegerung").gefunden);
    }

    // --- Der Fehlerwert zeigt auf keinen Platz (Paket 0023) ----------------------
    //
    // Der vierstufige Weg aus dem Arbeitspaket, ausgefahren statt beschrieben: Ein
    // Aufrufer bildet eine Adresse mit Tippfehler, wertet `gefunden` **nicht** aus
    // und reicht `index` an einen Schreibzugriff weiter. Frueher war das ein stiller
    // Schreibzugriff auf Platz 0 -- `land.US.sektor.1.wertschoepfung`, eine getragene
    // Groesse des Modells. Jetzt ist es ein Abbruch, und die Meldung steht im
    // Protokoll.
    {
        Zustand zustand;
        const Index platz_null = stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                                      SektorGroesse::Wertschoepfung);
        PRUEFE(platz_null == 0);

        // Ein Wert, den man wiedererkennt: Er steht vor und nach dem Fehlversuch da.
        startwert(zustand, platz_null, undurchsichtig(4711));
        PRUEFE(zustand.lies(platz_null) == 4711);

        // Schritt 1 und 2 -- die Adresse mit Tippfehler, die Antwort der Suche.
        const Adressfund fund = adresse_zu_index("land.US.sektor.1.wertschoepfun");
        PRUEFE(!fund.gefunden);
        PRUEFE(fund.index == KEIN_PLATZ);
        PRUEFE(fund.index >= FELDER);

        // Schritt 3 und 4 -- `.index` ohne `.gefunden` weitergereicht. Alle drei
        // Zugriffe des Zustands muessen ihn abweisen, nicht nur der eine aus dem
        // Arbeitspaket. Der schreibende geht seit Paket 0027 ueber den
        // Startwertzugang; die Indexpruefung dahinter ist dieselbe.
        ERWARTE_ABBRUCH(startwert(zustand, undurchsichtig_index(fund.index),
                                  undurchsichtig(-1)));
        ERWARTE_ABBRUCH((void)zustand.lies(undurchsichtig_index(fund.index)));
        ERWARTE_ABBRUCH((void)index_zu_adresse(undurchsichtig_index(fund.index)));

        // Nachher wie vorher -- und zwar in keinem der 310 Felder etwas anderes.
        PRUEFE(zustand.lies(platz_null) == 4711);
        Zustand vergleich;
        startwert(vergleich, platz_null, undurchsichtig(4711));
        PRUEFE(zustand == vergleich);

        // Jede Fehlanzeige traegt denselben Wert, nicht nur diese eine.
        PRUEFE(adresse_zu_index(nullptr).index == KEIN_PLATZ);
        PRUEFE(adresse_zu_index("").index == KEIN_PLATZ);
        PRUEFE(adresse_zu_index("land.US.sektor.1.preis.").index == KEIN_PLATZ);
        PRUEFE(adresse_zu_index("land.US.sektor.1.prei").index == KEIN_PLATZ);
        PRUEFE(adresse_zu_index("handel.US.US.1").index == KEIN_PLATZ);
        PRUEFE(adresse_zu_index("fonds.position.waehrung.RW").index == KEIN_PLATZ);

        // Die Gegenprobe, an der eine zu grobe Reparatur scheitert: Platz 0 ist
        // weiterhin ein gueltiger Platz und ueber seine Adresse erreichbar.
        const Adressfund echt = adresse_zu_index("land.US.sektor.1.wertschoepfung");
        PRUEFE(echt.gefunden);
        PRUEFE(echt.index == 0);
        startwert(zustand, echt.index, undurchsichtig(-4711));
        PRUEFE(zustand.lies(platz_null) == -4711);

        std::fprintf(stdout,
                     "Fehlerwert der Adresssuche: %zu -- gueltige Plaetze 0 ... %zu\n",
                     KEIN_PLATZ, FELDER - 1);
    }

    // --- Jede Gruppe ueber ihre `stelle_*`-Funktion, jeder Platz genau einmal -----
    //
    // Dieselbe Zaehlung wie im Deckungslauf, aber zur Laufzeit und ohne Blick in die
    // Tabelle. Sie belegt die zweite Haelfte der Abnahmebedingung: Die Abbildung
    // kennt keine Adresse ausserhalb der 310, sonst ginge die Strichliste nicht auf.
    {
        Strichliste liste;

        for (std::size_t g = 0; g < GEBIETE; ++g) {
            const Gebiet gebiet = static_cast<Gebiet>(g);
            for (std::size_t s = 1; s <= SEKTOREN; ++s) {
                for (std::size_t k = 0; k < SEKTORGROESSEN; ++k) {
                    VERMERKE(liste, stelle_sektorgroesse(gebiet, static_cast<Sektor>(s),
                                                         static_cast<SektorGroesse>(k)));
                }
            }
            for (std::size_t a = 0; a < AGGREGATE; ++a) {
                VERMERKE(liste, stelle_aggregat(gebiet, static_cast<Aggregat>(a)));
            }
            VERMERKE(liste, stelle_basiswechsel(gebiet));
        }

        for (std::size_t l = 0; l < LAENDER; ++l) {
            const Gebiet land = static_cast<Gebiet>(l);
            for (std::size_t p = 0; p < POLITISCHE_GROESSEN; ++p) {
                VERMERKE(liste, stelle_politisch(land, static_cast<PolitischeGroesse>(p)));
            }
            for (std::size_t i = 0; i < INSTRUMENTE; ++i) {
                for (std::size_t f = 0; f < INSTRUMENTFELDER; ++f) {
                    VERMERKE(liste, stelle_instrument(land, static_cast<Instrument>(i),
                                                      static_cast<InstrumentFeld>(f)));
                }
            }
            for (std::size_t r = 0; r < RESTDAUERZAEHLER; ++r) {
                VERMERKE(liste, stelle_restdauer(land, static_cast<Restdauerzaehler>(r)));
            }
        }

        for (std::size_t v = 0; v < GEBIETE; ++v) {
            for (std::size_t n = 0; n < GEBIETE; ++n) {
                if (v == n) {
                    continue;
                }
                for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
                    VERMERKE(liste, stelle_handel(static_cast<Gebiet>(v), static_cast<Gebiet>(n),
                                                  static_cast<Sektor>(s)));
                }
            }
        }

        for (std::size_t s = 1; s <= SEKTOREN_HANDELBAR; ++s) {
            VERMERKE(liste, stelle_weltpreis(static_cast<Sektor>(s)));
        }

        for (std::size_t l = 0; l < LAENDER; ++l) {
            for (std::size_t s = 1; s <= SEKTOREN; ++s) {
                VERMERKE(liste,
                         stelle_nachahmer(static_cast<Gebiet>(l), static_cast<Sektor>(s)));
            }
        }

        for (std::size_t m = 0; m < MARKTGROESSEN; ++m) {
            VERMERKE(liste, stelle_markt(static_cast<MarktGroesse>(m)));
        }
        for (std::size_t f = 0; f < FONDSGROESSEN; ++f) {
            VERMERKE(liste, stelle_fonds(static_cast<FondsGroesse>(f)));
        }
        for (std::size_t r = 1; r <= UEBERRENDITE_RUNDEN; ++r) {
            VERMERKE(liste, stelle_ueberrendite(r));
        }
        for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
            VERMERKE(liste, stelle_position(static_cast<Steckplatz>(p)));
        }
        for (std::size_t l = 0; l < LAENDER; ++l) {
            for (std::size_t s = 1; s <= SEKTOREN; ++s) {
                for (std::size_t f = 0; f < BETEILIGUNGSFELDER; ++f) {
                    VERMERKE(liste, stelle_beteiligung(static_cast<Gebiet>(l),
                                                       static_cast<Sektor>(s),
                                                       static_cast<BeteiligungsFeld>(f)));
                }
            }
        }
        for (std::size_t p = 0; p < PARTIEFELDER; ++p) {
            VERMERKE(liste, stelle_partie(static_cast<PartieFeld>(p)));
        }

        int genau_einmal = 0;
        for (Index i = 0; i < FELDER; ++i) {
            if (liste.treffer[i] != 1) {
                std::fprintf(stderr, "Platz %zu wurde %d mal getroffen (%s)\n", i,
                             liste.treffer[i], index_zu_adresse(i));
            } else {
                ++genau_einmal;
            }
        }
        PRUEFE(genau_einmal == 310);
        std::fprintf(stdout, "Adressfunktionen decken %d von 310 Plaetzen genau einmal\n",
                     genau_einmal);
    }

    // --- Die drei Steckplatzarten treffen dieselben Plaetze wie die Aufzaehlung ---
    {
        PRUEFE(steckplatz_sektor(Gebiet::US, Sektor::Landwirtschaft) == Steckplatz::Sektor_US_1);
        PRUEFE(steckplatz_sektor(Gebiet::BR, Sektor::Dienstleistungen) == Steckplatz::Sektor_BR_3);
        PRUEFE(steckplatz_waehrung(Gebiet::US) == Steckplatz::Waehrung_US);
        PRUEFE(steckplatz_waehrung(Gebiet::BR) == Steckplatz::Waehrung_BR);
        PRUEFE(steckplatz_anleihe(Gebiet::US) == Steckplatz::Anleihe_US);
        PRUEFE(steckplatz_anleihe(Gebiet::BR) == Steckplatz::Anleihe_BR);
    }

    // --- T16: zwanzig Plaetze, neunzehn spielbar, einer dauerhaft leer -----------
    {
        int spielbar = 0;
        for (std::size_t p = 0; p < STECKPLAETZE; ++p) {
            if (steckplatz_spielbar(static_cast<Steckplatz>(p))) {
                ++spielbar;
            }
        }
        PRUEFE(spielbar == 19);
        PRUEFE(static_cast<std::size_t>(spielbar) == STECKPLAETZE_SPIELBAR);
        PRUEFE(!steckplatz_spielbar(Steckplatz::Waehrung_US));
        PRUEFE(steckplatz_spielbar(steckplatz_waehrung(Gebiet::CN)));

        // Der leere Platz hat trotzdem eine Adresse -- das ist der ganze Grund,
        // warum er stehen bleibt (gleichfoermige Adressierung nach T17).
        PRUEFE(adresse_zu_index("fonds.position.waehrung.US").gefunden);
        PRUEFE(adresse_zu_index("fonds.position.waehrung.US").index
               == stelle_position(Steckplatz::Waehrung_US));
        std::fprintf(stdout, "Steckplaetze: %zu Adressen, %d spielbar\n", STECKPLAETZE, spielbar);
    }

    // --- Eine Position ist eine vorzeichenbehaftete Stufenzahl, null heisst keine -
    {
        Zustand zustand;
        const Index platz = stelle_position(steckplatz_sektor(Gebiet::DE, Sektor::Industrie));
        PRUEFE(zustand.lies(platz) == 0);
        startwert(zustand, platz, undurchsichtig(-7));
        PRUEFE(zustand.lies(platz) == -7);
        startwert(zustand, platz, undurchsichtig(11));
        PRUEFE(zustand.lies(platz) == 11);
        startwert(zustand, platz, 0);
        PRUEFE(zustand.lies(platz) == 0);
        PRUEFE(zustand == Zustand{});
    }

    // --- Indexpruefung an jeder Grenze -------------------------------------------
    {
        Zustand zustand;
        bool abgebrochen = false;
        try {
            (void)zustand.lies(undurchsichtig_index(FELDER));
        } catch (...) {
            abgebrochen = true;
        }
        PRUEFE(abgebrochen);

        abgebrochen = false;
        try {
            startwert(zustand, undurchsichtig_index(FELDER), 1);
        } catch (...) {
            abgebrochen = true;
        }
        PRUEFE(abgebrochen);

        abgebrochen = false;
        try {
            (void)index_zu_adresse(undurchsichtig_index(FELDER));
        } catch (...) {
            abgebrochen = true;
        }
        PRUEFE(abgebrochen);

        // Der letzte gueltige Platz bricht nicht ab.
        PRUEFE(zustand.lies(undurchsichtig_index(FELDER - 1)) == 0);
    }

    // --- T12: die kanonische Byteform, drei Wege zu derselben Zahl ---------------
    {
        Zustand zustand;
        std::array<std::uint8_t, BYTES> bytes{};

        nach_bytes(zustand, bytes);
        const u64 ueber_kette = pruefsumme_von(zustand);
        const u64 ueber_bytes = kern::pruefsumme::fnv1a64(bytes);
        const u64 geschlossen =
            kern::pruefsumme::FNV_OFFSET_BASIS_64
            * potenz_mod_2hoch64(kern::pruefsumme::FNV_PRIME_64, BYTES);

        std::fprintf(stdout, "Nullzustand: Kette %016llx, Bytefolge %016llx, Potenz %016llx\n",
                     static_cast<unsigned long long>(ueber_kette),
                     static_cast<unsigned long long>(ueber_bytes),
                     static_cast<unsigned long long>(geschlossen));

        PRUEFE(ueber_kette == ueber_bytes);
        PRUEFE(ueber_kette == geschlossen);
        PRUEFE(ueber_kette == 0x01d663224c4054e5ULL);

        // Alle 2.480 Bytes sind null, und es sind genau 2.480.
        PRUEFE(bytes.size() == 2480);
        std::size_t nullbytes = 0;
        for (const std::uint8_t oktett : bytes) {
            if (oktett == 0) {
                ++nullbytes;
            }
        }
        PRUEFE(nullbytes == 2480);
    }

    // --- Die Byteform ist Little-Endian und feldweise, nicht das Speicherbild ----
    {
        Zustand zustand;
        startwert(zustand, stelle_partie(PartieFeld::Mandatsstand), undurchsichtig(-1));

        std::array<std::uint8_t, BYTES> bytes{};
        nach_bytes(zustand, bytes);

        // Das letzte Feld sind die letzten acht Bytes, und -1 sind acht mal FF.
        bool letzte_acht_voll = true;
        for (std::size_t b = BYTES - 8; b < BYTES; ++b) {
            if (bytes[b] != 0xFF) {
                letzte_acht_voll = false;
            }
        }
        PRUEFE(letzte_acht_voll);
        PRUEFE(bytes[0] == 0x00);

        const u64 summe = pruefsumme_von(zustand);
        std::fprintf(stdout, "letztes Feld = -1: %016llx\n",
                     static_cast<unsigned long long>(summe));
        PRUEFE(summe == kern::pruefsumme::fnv1a64(bytes));
        PRUEFE(summe == 0xa491e70cc3f70d5dULL);
    }

    // --- Jedes einzelne Feld geht in die Summe ein -------------------------------
    //
    // 310 Durchlaeufe: Wer ein Feld aus der Byteform vergaesse, faende hier zwei
    // verschiedene Zustaende mit derselben Summe.
    {
        const Zustand leer;
        const u64 grundsumme = pruefsumme_von(leer);
        int verschieden = 0;
        for (Index i = 0; i < FELDER; ++i) {
            Zustand einer;
            startwert(einer, i, undurchsichtig(1));
            if (pruefsumme_von(einer) != grundsumme) {
                ++verschieden;
            }
        }
        PRUEFE(verschieden == 310);
        std::fprintf(stdout, "Felder, die die Summe aendern: %d von 310\n", verschieden);
    }

    // --- Zaehlzustand: ein Wert je Platz, gegen eine ausserhalb gerechnete Zahl ---
    //
    // Der Erwartungswert stammt aus einer zweiten, unabhaengigen Rechnung in
    // beliebig genauer Ganzzahlarithmetik ausserhalb dieses Programms. Er belegt die
    // Feldreihenfolge: Zwei vertauschte Felder ergeben eine andere Zahl.
    //
    // Beide Zustaende dieses Blocks bekommen **eine** Startbelegung fuer alle 310
    // Werte, keine je Feld. Der Grund steht an der Klasse: Unter den 310 ist
    // `partie.runde` selbst, und ein Zugang, der sich je Aufruf neu bindet, haette sich
    // beim Platz 306 die Tuer vor der eigenen Nase zugezogen.
    //
    // Dass die Schleifen ueber Platz 306 hinaus durchlaufen, ist zugleich die
    // Gegenprobe zum Riegel aus dem Ruecklauf 1: Er fragt bei jedem Schreibzugriff, und
    // er laesst den Zugang trotzdem weiterschreiben, weil die Rundennummer, die dort
    // steht, von ihm selbst stammt. Ein stumpfes `partie.runde == 0` je Aufruf haette
    // beide Schleifen bei Platz 307 rot gemacht -- und die Pruefsumme unten waere eine
    // andere, weil die Plaetze 307 bis 309 dann Nullen truegen.
    {
        Zustand zaehlend;
        {
            Startbelegung belegung{zaehlend};
            for (Index i = 0; i < FELDER; ++i) {
                belegung.setze(i, static_cast<i64>(i));
            }
        }
        std::array<std::uint8_t, BYTES> bytes{};
        nach_bytes(zaehlend, bytes);

        const u64 summe = pruefsumme_von(zaehlend);
        std::fprintf(stdout, "Zaehlzustand (Feld i = i): %016llx\n",
                     static_cast<unsigned long long>(summe));
        PRUEFE(summe == kern::pruefsumme::fnv1a64(bytes));
        PRUEFE(summe == 0x25e8b19071bea26cULL);

        // Und die Gegenprobe zur Reihenfolge: dieselben Werte, zwei davon getauscht.
        // Frisch gebaut statt aus `zaehlend` abgeschrieben und nachgebessert -- dessen
        // Platz 306 traegt jetzt die 306, und an einen solchen Zustand laesst sich kein
        // *neuer* Startwertzugang mehr binden. Umgangen wird dabei nichts: Der Riegel
        // greift hier gar nicht, weil dieser zweite Zugang eine eigene Merkzahl hat und
        // sie an einem frischen Zustand erwirbt.
        Zustand getauscht;
        {
            Startbelegung belegung{getauscht};
            for (Index i = 0; i < FELDER; ++i) {
                belegung.setze(i, static_cast<i64>(i));
            }
            belegung.setze(0, static_cast<i64>(FELDER - 1));
            belegung.setze(FELDER - 1, 0);
        }
        PRUEFE(pruefsumme_von(getauscht) != summe);
    }

    // --- Kopieren ist ein Speicherumzug, und der Vergleich ist feldweise ---------
    {
        Zustand a;
        startwert(a, stelle_fonds(FondsGroesse::Kasse), undurchsichtig(1'000'000));
        const Zustand b = a;
        PRUEFE(a == b);
        PRUEFE(pruefsumme_von(a) == pruefsumme_von(b));

        Zustand c = a;
        startwert(c, stelle_fonds(FondsGroesse::Marktanteil), undurchsichtig(1));
        PRUEFE(!(a == c));
        PRUEFE(pruefsumme_von(a) != pruefsumme_von(c));
    }

    // --- Der Startwertzugang und sein Riegel (Paket 0027) ------------------------
    //
    // Die Sichtbarkeit ist oben beim Uebersetzen belegt; hier laeuft, was ein
    // `static_assert` nicht kann: dass der Zugang vor der ersten Runde traegt, dass er
    // danach abbricht, und mit welcher Meldung er das tut. Der Zustand mit gelaufener
    // Runde entsteht hier ohne den Schreiber -- diese Probe kennt ihn nicht; es genuegt,
    // dass `partie.runde` eine Rundennummer traegt, denn das ist der Riegel selbst.
    {
        const Index runde = stelle_partie(PartieFeld::Runde);
        const Index kasse = stelle_fonds(FondsGroesse::Kasse);

        // Vor der ersten Runde: offen, und der Wert steht danach da.
        Zustand vor_dem_anpfiff;
        PRUEFE(kern::zustand::vor_der_ersten_runde(vor_dem_anpfiff));
        PRUEFE(vor_dem_anpfiff.lies(runde) == 0);
        startwert(vor_dem_anpfiff, kasse, undurchsichtig(1'000'000));
        PRUEFE(vor_dem_anpfiff.lies(kasse) == 1'000'000);

        // Eine Partie in Runde 12. Gebaut ueber denselben Zugang, solange er offen ist
        // -- danach ist er es nicht mehr, und genau das ist die Aussage.
        Zustand in_der_partie;
        {
            Startbelegung belegung{in_der_partie};
            belegung.setze(kasse, undurchsichtig(1'000'000));
            belegung.setze(runde, undurchsichtig(12));
        }
        PRUEFE(in_der_partie.lies(runde) == 12);
        PRUEFE(!kern::zustand::vor_der_ersten_runde(in_der_partie));

        // Und der Abbruch, im Wortlaut ins Protokoll.
        ERWARTE_ABBRUCH(startwert(in_der_partie, kasse, undurchsichtig(0)));
        ERWARTE_ABBRUCH((void)Startbelegung{in_der_partie});

        // Der Versuch hat nichts hinterlassen -- kein halber Schreibzugriff.
        PRUEFE(in_der_partie.lies(kasse) == 1'000'000);

        std::fprintf(stdout,
                     "Startwertzugang: vor Runde 1 offen, in Runde %lld verriegelt\n",
                     static_cast<long long>(in_der_partie.lies(runde)));
    }

    // --- Der Riegel greift beim Schreiben, nicht beim Binden (Ruecklauf 1) -------
    //
    // Der Fall, an dem die erste Fassung gerissen ist: Ein Zugang wird gebunden,
    // *danach* setzt jemand anders die Rundennummer, und der alte Zugang schreibt
    // trotzdem weiter. Er darf es nicht, und er tut es nicht mehr -- der Nachweis
    // laeuft, statt in einem Kommentar zu stehen.
    //
    // Der fremde Schreibzugriff kommt hier von einem *zweiten* Startwertzugang und
    // nicht vom Schreiber: Diese Probe kennt den Schreiber nicht. Fuer den Riegel ist
    // das dasselbe -- er fragt, ob die Zahl auf `partie.runde` von ihm selbst stammt,
    // und nicht, wer sie sonst hingeschrieben hat. Die Fassung mit einer echten Runde
    // steht in `schreiber_probe.cpp`.
    {
        const Index runde = stelle_partie(PartieFeld::Runde);
        const Index kasse = stelle_fonds(FondsGroesse::Kasse);

        Zustand       gemeinsam;
        Startbelegung frueher{gemeinsam};
        frueher.setze(kasse, undurchsichtig(1'000'000));
        PRUEFE(gemeinsam.lies(kasse) == 1'000'000);

        // Der zweite Zugang bindet noch -- die Partie steht ja weiter vor Runde 1 --
        // und setzt dann die Rundennummer. Ab hier ist `frueher` veraltet.
        {
            Startbelegung spaeter{gemeinsam};
            spaeter.setze(runde, undurchsichtig(7));
            // Und *er* schreibt weiter: Die 7 stammt von ihm selbst.
            spaeter.setze(kasse, undurchsichtig(2'000'000));
        }
        PRUEFE(gemeinsam.lies(runde) == 7);
        PRUEFE(gemeinsam.lies(kasse) == 2'000'000);

        // Der alte Zugang dagegen bricht ab -- beim Schreiben, nicht beim Binden, denn
        // gebunden ist er laengst. Die Meldung nennt beide Rundennummern.
        ERWARTE_ABBRUCH(frueher.setze(kasse, undurchsichtig(3'000'000)));
        PRUEFE(gemeinsam.lies(kasse) == 2'000'000);

        // Auch eine Adresse, die mit der Runde nichts zu tun hat, bleibt zu: Der Riegel
        // haengt am Zugang und nicht an der Adresse.
        ERWARTE_ABBRUCH(frueher.setze(runde, undurchsichtig(0)));
        PRUEFE(gemeinsam.lies(runde) == 7);

        std::fprintf(stdout,
                     "Riegel je Schreibzugriff: Zugang mit Merkzahl 0 gegen "
                     "partie.runde %lld -- zu\n",
                     static_cast<long long>(gemeinsam.lies(runde)));
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::zustand -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::zustand -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
