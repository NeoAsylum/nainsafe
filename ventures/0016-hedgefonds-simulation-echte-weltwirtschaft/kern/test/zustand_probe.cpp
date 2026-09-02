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
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

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
    // und reicht `index` an `schreibe` weiter. Frueher war das ein stiller
    // Schreibzugriff auf Platz 0 -- `land.US.sektor.1.wertschoepfung`, eine getragene
    // Groesse des Modells. Jetzt ist es ein Abbruch, und die Meldung steht im
    // Protokoll.
    {
        Zustand zustand;
        const Index platz_null = stelle_sektorgroesse(Gebiet::US, Sektor::Landwirtschaft,
                                                      SektorGroesse::Wertschoepfung);
        PRUEFE(platz_null == 0);

        // Ein Wert, den man wiedererkennt: Er steht vor und nach dem Fehlversuch da.
        zustand.schreibe(platz_null, undurchsichtig(4711));
        PRUEFE(zustand.lies(platz_null) == 4711);

        // Schritt 1 und 2 -- die Adresse mit Tippfehler, die Antwort der Suche.
        const Adressfund fund = adresse_zu_index("land.US.sektor.1.wertschoepfun");
        PRUEFE(!fund.gefunden);
        PRUEFE(fund.index == KEIN_PLATZ);
        PRUEFE(fund.index >= FELDER);

        // Schritt 3 und 4 -- `.index` ohne `.gefunden` weitergereicht. Alle drei
        // Zugriffe des Zustands muessen ihn abweisen, nicht nur der eine aus dem
        // Arbeitspaket.
        ERWARTE_ABBRUCH(zustand.schreibe(undurchsichtig_index(fund.index),
                                         undurchsichtig(-1)));
        ERWARTE_ABBRUCH((void)zustand.lies(undurchsichtig_index(fund.index)));
        ERWARTE_ABBRUCH((void)index_zu_adresse(undurchsichtig_index(fund.index)));

        // Nachher wie vorher -- und zwar in keinem der 310 Felder etwas anderes.
        PRUEFE(zustand.lies(platz_null) == 4711);
        Zustand vergleich;
        vergleich.schreibe(platz_null, undurchsichtig(4711));
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
        zustand.schreibe(echt.index, undurchsichtig(-4711));
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
        zustand.schreibe(platz, undurchsichtig(-7));
        PRUEFE(zustand.lies(platz) == -7);
        zustand.schreibe(platz, undurchsichtig(11));
        PRUEFE(zustand.lies(platz) == 11);
        zustand.schreibe(platz, 0);
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
            zustand.schreibe(undurchsichtig_index(FELDER), 1);
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
        zustand.schreibe(stelle_partie(PartieFeld::Mandatsstand), undurchsichtig(-1));

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
            einer.schreibe(i, undurchsichtig(1));
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
    {
        Zustand zaehlend;
        for (Index i = 0; i < FELDER; ++i) {
            zaehlend.schreibe(i, static_cast<i64>(i));
        }
        std::array<std::uint8_t, BYTES> bytes{};
        nach_bytes(zaehlend, bytes);

        const u64 summe = pruefsumme_von(zaehlend);
        std::fprintf(stdout, "Zaehlzustand (Feld i = i): %016llx\n",
                     static_cast<unsigned long long>(summe));
        PRUEFE(summe == kern::pruefsumme::fnv1a64(bytes));
        PRUEFE(summe == 0x25e8b19071bea26cULL);

        // Und die Gegenprobe zur Reihenfolge: dieselben Werte, zwei davon getauscht.
        Zustand getauscht = zaehlend;
        getauscht.schreibe(0, static_cast<i64>(FELDER - 1));
        getauscht.schreibe(FELDER - 1, 0);
        PRUEFE(pruefsumme_von(getauscht) != summe);
    }

    // --- Kopieren ist ein Speicherumzug, und der Vergleich ist feldweise ---------
    {
        Zustand a;
        a.schreibe(stelle_fonds(FondsGroesse::Kasse), undurchsichtig(1'000'000));
        const Zustand b = a;
        PRUEFE(a == b);
        PRUEFE(pruefsumme_von(a) == pruefsumme_von(b));

        Zustand c = a;
        c.schreibe(stelle_fonds(FondsGroesse::Marktanteil), undurchsichtig(1));
        PRUEFE(!(a == c));
        PRUEFE(pruefsumme_von(a) != pruefsumme_von(c));
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "kern::zustand -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "kern::zustand -- %d Probe(n) fehlgeschlagen.\n", fehlgeschlagen);
    return 1;
}
