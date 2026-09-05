//! Paket 0020 -- die sieben Wertebereichsschranken, die zwei Gleichheiten und die
//! Sektoranteile aus **T30 Pruefung 2**, je Runde und als harter Fehler.
//!
//! Vorgaben: T30 Pruefung 2 samt der Untertabelle "Die sieben Wertebereichsschranken",
//! dazu T5 (Skalenklassen), T49 (Klasse je Adresse, die zwei Adresspaare), T51
//! (Wertebereich am Instrument), T2 (kein Dateizugriff, keine Fremdabhaengigkeit) und
//! T4 (kein Gleitkomma). Eingabe ist der `Zustand` aus Paket 0008; die Adressmengen
//! kommen aus dem Adressverzeichnis (Paket 0007) und nicht aus dieser Datei.
//!
//! ## Die zehn geprueften Sachen
//!
//!   1 `wechselkurs[g] >= 1`                                            5 Adressen
//!   2 Nominalindizes `> 0`                                            22 Adressen
//!   3 `produktivitaet[g] > 0`                                          5 Adressen
//!   4 `leitzins[l] + aufschlag >= 1`                                   4 Adressen
//!   5 `0 < markt.wert < 9,2e13`                                        1 Adresse
//!   6 `0 <= druck, gegendruck <= druck_max`                           32 Adressen
//!   7 `0 <= fondsanteil(l,s) <= 10.000`, `|stufen(p)| <= stufen_max`  12 + 20
//!   8 `land.<L>.leitzins = land.<L>.instrument.leitzins.stand`         4 Paare
//!   9 `land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`   4 Paare
//!  10 drei Sektoranteile je Gebiet auf 10.000, keiner ausserhalb 0...10.000  5 Gebiete
//!
//! ## Warum die Adressmengen erlaufen und nicht aufgezaehlt werden
//!
//! Die Zahlen oben stehen im Arbeitspaket und in der Klassenzaehlung von
//! `daten/adressen.md`. Eine zweite Aufzaehlung in dieser Datei waere eine zweite
//! Fassung derselben Menge -- und die zweite ist die, die niemand nachfuehrt. Die
//! Probe laeuft deshalb ueber alle 310 Plaetze, fragt `index_zu_adresse` nach dem
//! Namen und entscheidet an ihm. Weicht der Kern vom Verzeichnis ab, kommt eine
//! andere Anzahl heraus, und genau das ist der Befund, den Abnahmebedingung 2 sucht.
//! Die beiden Adresspaare und die Sektordreiergruppen entstehen auf demselben Weg:
//! aus dem gefundenen Namen wird der Geschwistername gebildet und nachgeschlagen.
//!
//! ## Was hier ausdruecklich NICHT geprueft wird
//!
//! T30 Pruefung 2 nennt vier weitere Sachen -- Summe aller Handelsbilanzen, die
//! Fortschreibung der Staatsschuld, das Fondsvermoegen nach T47 und die drei
//! Ergebnisbaender nach T34. Alle vier brauchen etwas, das es noch nicht gibt: einen
//! gerechneten Weltschritt, `fondsvermoegen()` aus dem blockierten Paket 0002, eine
//! gespielte Partie. Ein Platzhalter dafuer wuerde die Annahme messen statt das
//! Modell; sie kommen als eigenes Paket, sobald ihre Voraussetzung steht.
//!
//! ## Die drei Grenzen aus `parameter.toml` sind Argumente, kein Dateizugriff
//!
//! Der Kern liest keine Datei (T2). `druck_max`, `stufen_max` und `aufschlag` stehen
//! deshalb in `Grenzen` und werden von aussen eingesetzt. Die Werte, die die Probe
//! einsetzt, sind die des Bauzeitpunkts; Schluesselname und Zeile stehen bei jedem.
//! Alle drei tragen dort heute `# PLATZHALTER` -- der Grund, warum die Zahl nicht in
//! den Code eingebrannt werden darf.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "kern/festkomma.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::i128;
using kern::festkomma::mal_geteilt;
using kern::zustand::Adressfund;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

using kern::zustand::adresse_zu_index;
using kern::zustand::index_zu_adresse;

using kern::zustand::ADRESSE_PUFFER;
using kern::zustand::FELDER;
using kern::zustand::GEBIETE;
using kern::zustand::KEIN_PLATZ;
using kern::zustand::LAENDER;
using kern::zustand::SEKTOREN;

/// Ein Zustand, den diese Probe gerade baut, samt dem **einen** Startwertzugang, der
/// ihn fuellt.
///
/// **Nachgezogen von Paket 0027, mechanisch und ohne Bedeutungsaenderung.** Bis dahin
/// stand an jeder dieser Stellen ein Schreibzugriff auf den Zustand selbst; den gibt es
/// nicht mehr, seit T18 auch im Code durchgesetzt ist. Diese Probe spielt keine Runde,
/// sie baut Ausgangslagen und laesst die Wertebereichspruefung darauf laufen -- also
/// genau der Fall, fuer den es den Startwertzugang gibt.
///
/// **Warum ein Typ und keine Hilfsfunktion, die je Aufruf einen Zugang bindet.** Genau
/// so stand es hier, und es ging nur so lange gut, wie keine der Stellen unten
/// `partie.runde` anfasst: Ein Zugang laesst sich an einen Zustand mit gelaufener Runde
/// nicht mehr binden. Die erste Schranke, die einen Randfall auf einem solchen Zustand
/// braucht, waere an einer Meldung gestorben, die von einem echten Fehler nicht zu
/// unterscheiden ist. Ein Zustand und ein Zugang, gemeinsam gebaut und gemeinsam
/// lebend, haben das Problem nicht -- der Zugang traegt weiter, auch ueber die
/// Rundennummer hinweg, weil sie dann von ihm selbst stammt.
///
/// Der Zugang ist weder kopierbar noch verschiebbar, also ist ein `Rohling` es auch
/// nicht. Das ist hier kein Verlust: Jeder steht in dem Block, in dem er gebraucht
/// wird. Die Umwandlung nach `const Zustand&` steht da, damit `GRUEN` und `ROT`
/// unveraendert einen Zustand bekommen und diese Umstellung nichts anderes anfasst.
class Rohling {
public:
    Rohling() = default;
    explicit Rohling(const Zustand& vorlage) : zustand_(vorlage) {}

    void lege(Index platz, i64 wert) { zugang_.setze(platz, wert); }

    operator const Zustand&() const { return zustand_; }

private:
    Zustand       zustand_;
    Startbelegung zugang_{zustand_};
};

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

// ---------------------------------------------------------------------------
// Zeichenkettenarbeit auf Indizes statt auf Zeigern
// ---------------------------------------------------------------------------
//
// Feste Groessen, Indexpruefung an jeder Grenze, kein Standardkopf ausserhalb der
// vier oben -- die Vorsichtsregel aus ADR 0011 fuer eine Sprache ohne
// Speichersicherheit.

std::size_t laenge(const char* text)
{
    std::size_t n = 0;
    while (text[n] != '\0') {
        ++n;
    }
    return n;
}

bool endet_auf(const char* text, const char* schwanz)
{
    const std::size_t lt = laenge(text);
    const std::size_t ls = laenge(schwanz);
    if (ls > lt) {
        return false;
    }
    for (std::size_t i = 0; i < ls; ++i) {
        if (text[lt - ls + i] != schwanz[i]) {
            return false;
        }
    }
    return true;
}

bool beginnt_mit(const char* text, const char* kopf)
{
    for (std::size_t i = 0; kopf[i] != '\0'; ++i) {
        if (text[i] != kopf[i]) {
            return false;
        }
    }
    return true;
}

bool ist_gleich(const char* a, const char* b)
{
    std::size_t i = 0;
    while (a[i] != '\0' && a[i] == b[i]) {
        ++i;
    }
    return a[i] == b[i];
}

/// `text` ohne den Schwanz `schwanz`, dafuer mit `anhang` -- der Weg vom gefundenen
/// Namen zum Geschwisternamen. Passt das Ergebnis nicht in den Puffer aus T17, ist
/// das `false` und keine abgeschnittene Adresse.
bool geschwistername(const char* text, const char* schwanz, const char* anhang,
                     std::array<char, ADRESSE_PUFFER>& ziel)
{
    const std::size_t lt = laenge(text);
    const std::size_t ls = laenge(schwanz);
    const std::size_t la = laenge(anhang);
    if (ls > lt || lt - ls + la + 1 > ziel.size()) {
        return false;
    }
    const std::size_t kopf = lt - ls;
    for (std::size_t i = 0; i < kopf; ++i) {
        ziel[i] = text[i];
    }
    for (std::size_t i = 0; i < la; ++i) {
        ziel[kopf + i] = anhang[i];
    }
    ziel[kopf + la] = '\0';
    return true;
}

// ---------------------------------------------------------------------------
// Die Adressmengen, aus dem Verzeichnis erlaufen
// ---------------------------------------------------------------------------

/// Reichlich Luft ueber der groessten erwarteten Menge (32, Klasse 9). Laeuft sie
/// ueber, ist das ein Befund gegen das Verzeichnis und kein Grund zum Abschneiden.
inline constexpr std::size_t MENGE_MAX = 64;

/// Reichlich Luft ueber der groessten erwarteten Gruppenzahl (5 Gebiete).
inline constexpr std::size_t GRUPPE_MAX = 16;

struct Menge {
    std::array<Index, MENGE_MAX> platz{};
    std::size_t anzahl = 0;
    bool uebergelaufen = false;

    void nimm(Index stelle)
    {
        if (anzahl >= platz.size()) {
            uebergelaufen = true;
            return;
        }
        platz[anzahl] = stelle;
        ++anzahl;
    }
};

/// Zwei Adressen, die nach T49 denselben Wert tragen muessen.
struct Paar {
    Index aggregat = KEIN_PLATZ;
    Index stand = KEIN_PLATZ;
};

struct Paarmenge {
    std::array<Paar, GRUPPE_MAX> paar{};
    std::size_t anzahl = 0;
    bool uebergelaufen = false;

    void nimm(Paar neu)
    {
        if (anzahl >= paar.size()) {
            uebergelaufen = true;
            return;
        }
        paar[anzahl] = neu;
        ++anzahl;
    }
};

/// Die drei Sektorwertschoepfungen eines Gebiets -- aus ihnen entstehen die drei
/// Sektoranteile. Der Anteil selbst hat nach T49 keine eigene Adresse.
struct Dreier {
    std::array<Index, SEKTOREN> platz{};
};

struct Dreiermenge {
    std::array<Dreier, GRUPPE_MAX> gruppe{};
    std::size_t anzahl = 0;
    bool uebergelaufen = false;

    void nimm(const Dreier& neu)
    {
        if (anzahl >= gruppe.size()) {
            uebergelaufen = true;
            return;
        }
        gruppe[anzahl] = neu;
        ++anzahl;
    }
};

struct Verzeichnis {
    Menge wechselkurs;          // Schranke 1
    Menge nominalindex;         // Schranke 2
    Menge produktivitaet;       // Schranke 3
    Menge leitzinsstand;        // Schranke 4
    Menge marktwert;            // Schranke 5
    Menge lobbydruck;           // Schranke 6
    Menge beteiligungsanteil;   // Schranke 7, erster Teil
    Menge positionsstufe;       // Schranke 7, zweiter Teil
    Paarmenge gleich_leitzins;  // Gleichheit 1 (T49)
    Paarmenge gleich_haushalt;  // Gleichheit 2 (T49)
    Dreiermenge sektoren;       // Sektoranteile je Gebiet
    bool vollstaendig = true;
};

/// Schlaegt eine abgeleitete Adresse nach. Eine Fehlanzeige ist hier ein Fehler und
/// keine offene Frage: Der Name wurde aus einem Namen gebildet, den das Verzeichnis
/// selbst gerade geliefert hat.
Index nachschlagen(const std::array<char, ADRESSE_PUFFER>& name, bool& heil)
{
    const Adressfund fund = adresse_zu_index(name.data());
    if (!fund.gefunden) {
        heil = false;
        return KEIN_PLATZ;
    }
    return fund.index;
}

Verzeichnis lies_verzeichnis()
{
    Verzeichnis v;

    for (Index i = 0; i < FELDER; ++i) {
        const char* a = index_zu_adresse(i);
        if (a == nullptr) {
            v.vollstaendig = false;
            continue;
        }

        // Klasse 6 (T49): `land.<L>.wechselkurs` und `restwelt.wechselkurs`.
        if (endet_auf(a, ".wechselkurs")) {
            v.wechselkurs.nimm(i);
        }

        // Klasse 5 (T49): Sektorpreise, Preisniveaus, die zwei Weltpreise.
        if (endet_auf(a, ".preis") || endet_auf(a, ".preisniveau")
            || beginnt_mit(a, "welt.preis.")) {
            v.nominalindex.nimm(i);
        }

        // Klasse 7 (T49): die Produktivitaet, real und nie neu basiert.
        if (endet_auf(a, ".produktivitaet")) {
            v.produktivitaet.nimm(i);
        }

        // T51: die Schranke des Leitzinses sitzt am Instrument, nicht am Aggregat.
        if (endet_auf(a, ".instrument.leitzins.stand")) {
            v.leitzinsstand.nimm(i);

            std::array<char, ADRESSE_PUFFER> name{};
            bool heil = true;
            if (!geschwistername(a, ".instrument.leitzins.stand", ".leitzins", name)) {
                heil = false;
            }
            const Index aggregat = heil ? nachschlagen(name, heil) : KEIN_PLATZ;
            if (heil) {
                v.gleich_leitzins.nimm(Paar{aggregat, i});
            } else {
                v.vollstaendig = false;
            }
        }

        if (endet_auf(a, ".instrument.haushalt.stand")) {
            std::array<char, ADRESSE_PUFFER> name{};
            bool heil = true;
            if (!geschwistername(a, ".instrument.haushalt.stand", ".haushaltssaldo", name)) {
                heil = false;
            }
            const Index aggregat = heil ? nachschlagen(name, heil) : KEIN_PLATZ;
            if (heil) {
                v.gleich_haushalt.nimm(Paar{aggregat, i});
            } else {
                v.vollstaendig = false;
            }
        }

        if (ist_gleich(a, "markt.wert")) {
            v.marktwert.nimm(i);
        }

        // Klasse 9 (T49): 16 anliegende Druecke, 16 Gegendruecke. `.gegendruck` endet
        // nicht auf `.druck` -- vor `druck` steht dort ein `n`, kein Punkt.
        if (endet_auf(a, ".druck") || endet_auf(a, ".gegendruck")) {
            v.lobbydruck.nimm(i);
        }

        if (beginnt_mit(a, "fonds.beteiligung.") && endet_auf(a, ".anteil")) {
            v.beteiligungsanteil.nimm(i);
        }

        if (beginnt_mit(a, "fonds.position.")) {
            v.positionsstufe.nimm(i);
        }

        // Die drei Wertschoepfungen eines Gebiets, am ersten Sektor aufgesammelt.
        if (endet_auf(a, ".sektor.1.wertschoepfung")) {
            Dreier gruppe;
            gruppe.platz[0] = i;
            bool heil = true;
            std::array<char, ADRESSE_PUFFER> name{};
            if (geschwistername(a, ".sektor.1.wertschoepfung", ".sektor.2.wertschoepfung",
                                name)) {
                gruppe.platz[1] = nachschlagen(name, heil);
            } else {
                heil = false;
            }
            if (heil
                && geschwistername(a, ".sektor.1.wertschoepfung", ".sektor.3.wertschoepfung",
                                   name)) {
                gruppe.platz[2] = nachschlagen(name, heil);
            } else {
                heil = false;
            }
            if (heil) {
                v.sektoren.nimm(gruppe);
            } else {
                v.vollstaendig = false;
            }
        }
    }

    return v;
}

// ---------------------------------------------------------------------------
// Die Grenzen aus `parameter.toml` -- Argumente, nie ein Dateizugriff (T2)
// ---------------------------------------------------------------------------

struct Grenzen {
    i64 druck_max = 0;   // Schluessel `druck_max`
    i64 stufen_max = 0;  // Schluessel `stufen_max`
    i64 aufschlag = 0;   // Schluessel `aufschlag`
};

/// Der Stand von `parameter.toml` zum Bauzeitpunkt (2026-09-02). Alle drei Zeilen
/// tragen dort `# PLATZHALTER`; sie werden kalibriert und nicht entworfen, deshalb
/// steht die Zahl hier als Argument und nicht in der Pruefung.
///
///   parameter.toml Zeile 304: `druck_max  = 1   # PLATZHALTER`   (T5 Klasse 9)
///   parameter.toml Zeile 205: `stufen_max = 1   # PLATZHALTER`   (T5 Klasse 11, T16)
///   parameter.toml Zeile 250: `aufschlag  = 51  # PLATZHALTER`   (T5 Klasse 3, T51)
inline constexpr Grenzen GRENZEN_BAUZEITPUNKT{1, 1, 51};

// ---------------------------------------------------------------------------
// Der Befund
// ---------------------------------------------------------------------------

enum class Sache : std::size_t {
    Schranke1Wechselkurs = 0,
    Schranke2Nominalindizes = 1,
    Schranke3Produktivitaet = 2,
    Schranke4Leitzinsuntergrenze = 3,
    Schranke5Marktkorb = 4,
    Schranke6Lobbydruck = 5,
    Schranke7AnteilUndStufe = 6,
    Gleichheit1Leitzins = 7,
    Gleichheit2Haushaltssaldo = 8,
    Sektoranteile = 9,
};

inline constexpr std::size_t SACHEN = 10;

const char* name_der_sache(Sache sache)
{
    switch (sache) {
    case Sache::Schranke1Wechselkurs: return "Schranke 1  wechselkurs >= 1";
    case Sache::Schranke2Nominalindizes: return "Schranke 2  Nominalindex > 0";
    case Sache::Schranke3Produktivitaet: return "Schranke 3  produktivitaet > 0";
    case Sache::Schranke4Leitzinsuntergrenze: return "Schranke 4  leitzins + aufschlag >= 1";
    case Sache::Schranke5Marktkorb: return "Schranke 5  0 < markt.wert < 9,2e13";
    case Sache::Schranke6Lobbydruck: return "Schranke 6  0 <= druck <= druck_max";
    case Sache::Schranke7AnteilUndStufe: return "Schranke 7  Anteil 0..10.000, |Stufe| <= max";
    case Sache::Gleichheit1Leitzins: return "Gleichheit 1  leitzins = instrument.stand";
    case Sache::Gleichheit2Haushaltssaldo: return "Gleichheit 2  saldo = instrument.stand";
    case Sache::Sektoranteile: return "Sektoranteile  Summe 10.000, keiner ausserhalb";
    }
    return "unbekannt";
}

unsigned nur(Sache sache)
{
    return 1U << static_cast<unsigned>(sache);
}

constexpr std::array<Index, SACHEN> keine_stellen()
{
    std::array<Index, SACHEN> stellen{};
    for (std::size_t i = 0; i < SACHEN; ++i) {
        stellen[i] = KEIN_PLATZ;
    }
    return stellen;
}

/// Wie die Pruefung ihr Ergebnis meldet, stellt das Arbeitspaket frei. Gewaehlt ist
/// eine Maske ueber die zehn Sachen plus die erste betroffene Adresse je Sache: Damit
/// sagt ein Befund, *welche* Sache gerissen ist, und der Nachweis aus Abnahme 3 --
/// genau diese eine und keine andere -- ist ein Zahlenvergleich statt einer Lesung.
struct Befund {
    unsigned verletzt = 0;
    std::array<Index, SACHEN> erste_stelle = keine_stellen();
    std::array<std::size_t, SACHEN> adressen{};

    void besucht(Sache sache) { ++adressen[static_cast<std::size_t>(sache)]; }

    void melde(Sache sache, Index stelle)
    {
        const std::size_t nummer = static_cast<std::size_t>(sache);
        verletzt |= nur(sache);
        if (erste_stelle[nummer] == KEIN_PLATZ) {
            erste_stelle[nummer] = stelle;
        }
    }
};

// ---------------------------------------------------------------------------
// Die Sektoranteile
// ---------------------------------------------------------------------------

/// Ein voller Anteil in Zehntausendsteln (T5 Klasse 4).
inline constexpr i64 ANTEIL_GANZ = 10'000;

/// **Der Rundungsschlupf, und er ist eine ausgerechnete Schranke und keine gesenkte.**
/// Die drei Anteile entstehen als drei Quotienten, jeder nach T6 auf halbe Betraege
/// vom Null weg gerundet. Jeder weicht damit um weniger als 1/2 vom genauen Wert ab,
/// alle drei zusammen um weniger als 3/2 -- in ganzen Zahlen also um hoechstens 1.
/// Eine Summe von 9.999 oder 10.001 kann aus der Rundung kommen; 9.998 oder 10.002
/// kann es nicht und ist ein Rechenfehler. Wer hier 0 einsetzt, macht die Pruefung
/// rot fuer Gebiete mit drei gleich grossen Sektoren (10.000/3 = 3.333 dreimal ergibt
/// 9.999) -- das waere kein schaerferer Test, sondern ein falscher.
inline constexpr i64 ANTEIL_SCHLUPF = 1;

struct Anteile {
    bool bildbar = false;
    std::array<i64, SEKTOREN> anteil{};
    i64 summe = 0;
};

/// Die drei Anteile eines Gebiets aus den drei Sektorwertschoepfungen. Nach T49 hat
/// der Anteil keine eigene Adresse; er entsteht wie im Jahrgangsbau (T23 Punkt 1)
/// durch Normierung auf 10.000.
///
/// `bildbar == false` heisst: Es gibt keine drei Anteile. Das ist der Fall bei einer
/// Summe von null oder darunter -- die Normierung haette dort keinen Nenner -- und
/// bei einer Summe ausserhalb `i64`. Beides gehoert zur selben Sache: Wo kein Anteil
/// bildbar ist, summiert auch keiner auf 10.000. Die Pruefung bricht darueber nicht
/// ab, sondern meldet; ein Testwerkzeug, das am kaputten Zustand stirbt, sagt nichts.
Anteile anteile_aus_zustand(const Zustand& zustand, const Dreier& gruppe)
{
    Anteile ergebnis;
    std::array<i64, SEKTOREN> wert{};
    i128 summe = 0;
    for (std::size_t s = 0; s < SEKTOREN; ++s) {
        wert[s] = zustand.lies(gruppe.platz[s]);
        summe += static_cast<i128>(wert[s]);
    }
    if (summe <= 0 || summe > static_cast<i128>(kern::festkomma::I64_MAX)) {
        return ergebnis;
    }

    const i64 nenner = static_cast<i64>(summe);
    for (std::size_t s = 0; s < SEKTOREN; ++s) {
        ergebnis.anteil[s] = mal_geteilt(wert[s], ANTEIL_GANZ, nenner);
    }
    ergebnis.summe = ergebnis.anteil[0] + ergebnis.anteil[1] + ergebnis.anteil[2];
    ergebnis.bildbar = true;
    return ergebnis;
}

/// Die Aussage aus T30 Pruefung 2 als reine Rechnung auf drei Zahlen -- getrennt von
/// ihrer Herkunft, damit sie sich einzeln rot zeigen laesst. Aus einem Zustand allein
/// ist die Summenbedingung naemlich nicht zu reissen, solange die Anteile nach der
/// Regel oben entstehen; erst eine *andere* Bildungsregel reisst sie, und genau davor
/// bewacht sie.
bool anteile_ok(const Anteile& anteile)
{
    if (!anteile.bildbar) {
        return false;
    }
    for (std::size_t s = 0; s < SEKTOREN; ++s) {
        if (anteile.anteil[s] < 0 || anteile.anteil[s] > ANTEIL_GANZ) {
            return false;
        }
    }
    const i64 abweichung = anteile.summe - ANTEIL_GANZ;
    return abweichung <= ANTEIL_SCHLUPF && abweichung >= -ANTEIL_SCHLUPF;
}

// ---------------------------------------------------------------------------
// Die Pruefung
// ---------------------------------------------------------------------------

/// Die Ueberlaufschranke von `tsd_in_cent` (T47), als Zahl: 9,2 * 10^13.
inline constexpr i64 MARKT_WERT_MAX = 92'000'000'000'000;

Befund pruefe_wertebereiche(const Zustand& zustand, const Verzeichnis& v, const Grenzen& g)
{
    Befund befund;

    // --- Schranke 1: `wechselkurs[g] >= 1`, 5 Adressen -------------------------
    //
    // Der Wechselkurs ist nach T47 der Nenner jeder Bewertung: null bricht die
    // Division ab, ein negativer Kurs bricht nichts und dreht dafuer bei jeder
    // Bewertung still das Vorzeichen -- aus jedem Gewinn wird ein Verlust, und die
    // Partie rechnet zu Ende, als waere nichts. Deshalb ist das hier eine Schranke
    // und keine Kosmetik: Sie ist eine der beiden aus T30, die ohne Test still
    // falsch wuerden statt laut.
    for (std::size_t k = 0; k < v.wechselkurs.anzahl; ++k) {
        const Index stelle = v.wechselkurs.platz[k];
        befund.besucht(Sache::Schranke1Wechselkurs);
        if (zustand.lies(stelle) < 1) {
            befund.melde(Sache::Schranke1Wechselkurs, stelle);
        }
    }

    // --- Schranke 2: Nominalindizes `> 0`, 22 Adressen -------------------------
    for (std::size_t k = 0; k < v.nominalindex.anzahl; ++k) {
        const Index stelle = v.nominalindex.platz[k];
        befund.besucht(Sache::Schranke2Nominalindizes);
        if (zustand.lies(stelle) <= 0) {
            befund.melde(Sache::Schranke2Nominalindizes, stelle);
        }
    }

    // --- Schranke 3: `produktivitaet[g] > 0`, 5 Adressen -----------------------
    for (std::size_t k = 0; k < v.produktivitaet.anzahl; ++k) {
        const Index stelle = v.produktivitaet.platz[k];
        befund.besucht(Sache::Schranke3Produktivitaet);
        if (zustand.lies(stelle) <= 0) {
            befund.melde(Sache::Schranke3Produktivitaet, stelle);
        }
    }

    // --- Schranke 4: `leitzins[l] + aufschlag >= 1`, 4 Adressen ----------------
    //
    // Die Summe laeuft ueber `i128`: Beide Summanden sind `i64`, und ein Zustand,
    // der geprueft werden soll, ist gerade der, dem man nichts glaubt.
    for (std::size_t k = 0; k < v.leitzinsstand.anzahl; ++k) {
        const Index stelle = v.leitzinsstand.platz[k];
        befund.besucht(Sache::Schranke4Leitzinsuntergrenze);
        const i128 summe = static_cast<i128>(zustand.lies(stelle)) + static_cast<i128>(g.aufschlag);
        if (summe < 1) {
            befund.melde(Sache::Schranke4Leitzinsuntergrenze, stelle);
        }
    }

    // --- Schranke 5: `0 < markt.wert < 9,2e13`, 1 Adresse ----------------------
    //
    // Die zweite der beiden aus T30, die ohne Test still falsch wuerden. Der
    // Marktkorb ist Nenner von `markt.rendite` und `marktanteil`; jenseits der
    // Ueberlaufschranke stuerzt er nach T7 zwar ab, aber erst tief drinnen in
    // `tsd_in_cent` -- an einer Stelle, an der niemand die Ursache sucht. Hier
    // gemeldet, steht die Ursache im Befund statt im Kellerabzug.
    for (std::size_t k = 0; k < v.marktwert.anzahl; ++k) {
        const Index stelle = v.marktwert.platz[k];
        befund.besucht(Sache::Schranke5Marktkorb);
        const i64 wert = zustand.lies(stelle);
        if (wert <= 0 || wert >= MARKT_WERT_MAX) {
            befund.melde(Sache::Schranke5Marktkorb, stelle);
        }
    }

    // --- Schranke 6: `0 <= druck, gegendruck <= druck_max`, 32 Adressen --------
    for (std::size_t k = 0; k < v.lobbydruck.anzahl; ++k) {
        const Index stelle = v.lobbydruck.platz[k];
        befund.besucht(Sache::Schranke6Lobbydruck);
        const i64 wert = zustand.lies(stelle);
        if (wert < 0 || wert > g.druck_max) {
            befund.melde(Sache::Schranke6Lobbydruck, stelle);
        }
    }

    // --- Schranke 7: Beteiligungsanteil 0...10.000 (12), |Stufe| <= max (20) ---
    for (std::size_t k = 0; k < v.beteiligungsanteil.anzahl; ++k) {
        const Index stelle = v.beteiligungsanteil.platz[k];
        befund.besucht(Sache::Schranke7AnteilUndStufe);
        const i64 wert = zustand.lies(stelle);
        if (wert < 0 || wert > ANTEIL_GANZ) {
            befund.melde(Sache::Schranke7AnteilUndStufe, stelle);
        }
    }
    for (std::size_t k = 0; k < v.positionsstufe.anzahl; ++k) {
        const Index stelle = v.positionsstufe.platz[k];
        befund.besucht(Sache::Schranke7AnteilUndStufe);
        // Betrag auf `i128`, damit `-I64_MIN` nicht selbst der Ueberlauf ist.
        const i128 wert = static_cast<i128>(zustand.lies(stelle));
        const i128 betrag = wert < 0 ? -wert : wert;
        if (betrag > static_cast<i128>(g.stufen_max)) {
            befund.melde(Sache::Schranke7AnteilUndStufe, stelle);
        }
    }

    // --- Gleichheit 1 und 2 (T49), je Land ------------------------------------
    for (std::size_t k = 0; k < v.gleich_leitzins.anzahl; ++k) {
        const Paar paar = v.gleich_leitzins.paar[k];
        befund.besucht(Sache::Gleichheit1Leitzins);
        if (zustand.lies(paar.aggregat) != zustand.lies(paar.stand)) {
            befund.melde(Sache::Gleichheit1Leitzins, paar.aggregat);
        }
    }
    for (std::size_t k = 0; k < v.gleich_haushalt.anzahl; ++k) {
        const Paar paar = v.gleich_haushalt.paar[k];
        befund.besucht(Sache::Gleichheit2Haushaltssaldo);
        if (zustand.lies(paar.aggregat) != zustand.lies(paar.stand)) {
            befund.melde(Sache::Gleichheit2Haushaltssaldo, paar.aggregat);
        }
    }

    // --- Die drei Sektoranteile je Gebiet --------------------------------------
    for (std::size_t k = 0; k < v.sektoren.anzahl; ++k) {
        const Dreier& gruppe = v.sektoren.gruppe[k];
        befund.besucht(Sache::Sektoranteile);
        if (!anteile_ok(anteile_aus_zustand(zustand, gruppe))) {
            befund.melde(Sache::Sektoranteile, gruppe.platz[0]);
        }
    }

    return befund;
}

// ---------------------------------------------------------------------------
// Der gueltige Ausgangszustand
// ---------------------------------------------------------------------------
//
// Ein frischer `Zustand` ist durchgehend null und reisst damit fuenf der zehn Sachen
// -- er ist ausdruecklich kein Startzustand des Spiels (Paket 0008). Die Rotproben
// brauchen aber einen Zustand, der *nur* an der einen Stelle falsch ist. Er wird
// deshalb aus denselben Adressmengen gefuellt, die die Pruefung liest: Kaeme eine
// Adresse dazu, waere sie hier gesetzt und dort geprueft.

Zustand gueltiger_zustand(const Verzeichnis& v)
{
    Rohling z;
    for (std::size_t k = 0; k < v.wechselkurs.anzahl; ++k) {
        z.lege(v.wechselkurs.platz[k], 10'000);
    }
    for (std::size_t k = 0; k < v.nominalindex.anzahl; ++k) {
        z.lege(v.nominalindex.platz[k], 10'000);
    }
    for (std::size_t k = 0; k < v.produktivitaet.anzahl; ++k) {
        z.lege(v.produktivitaet.platz[k], 10'000);
    }
    for (std::size_t k = 0; k < v.marktwert.anzahl; ++k) {
        z.lege(v.marktwert.platz[k], 1'000'000);
    }
    // Leitzinsstand, Druecke, Anteile und Stufen bleiben null -- null liegt in jedem
    // dieser Bereiche, und `0 + aufschlag = 51 >= 1` haelt Schranke 4.
    for (std::size_t k = 0; k < v.sektoren.anzahl; ++k) {
        const Dreier& gruppe = v.sektoren.gruppe[k];
        z.lege(gruppe.platz[0], 3'000);
        z.lege(gruppe.platz[1], 3'000);
        z.lege(gruppe.platz[2], 4'000);
    }
    return z;
}

/// Die Adresse eines Namens, mit Nachweis, dass es sie gibt.
Index stelle_von(const char* adresse, int zeile)
{
    const Adressfund fund = adresse_zu_index(adresse);
    pruefe(fund.gefunden, adresse, zeile);
    return fund.gefunden ? fund.index : Index{0};
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)
#define STELLE(adresse) stelle_von((adresse), __LINE__)

namespace {

const Verzeichnis* verzeichnis = nullptr;
const Grenzen* grenzen = nullptr;

/// Abnahme 3: **genau diese eine** Sache und keine andere mit.
void rot(const char* was, const Zustand& z, Sache erwartet, int zeile)
{
    const Befund befund = pruefe_wertebereiche(z, *verzeichnis, *grenzen);
    const unsigned soll = nur(erwartet);
    pruefe(befund.verletzt == soll, was, zeile);
    std::fprintf(stdout, "  rot   %-38s Maske %4u, erwartet %4u  [%s]\n", was,
                 befund.verletzt, soll,
                 name_der_sache(erwartet));
}

/// Der Gegenbeweis zur Rotprobe: der Rand, der noch besteht.
void gruen(const char* was, const Zustand& z, int zeile)
{
    const Befund befund = pruefe_wertebereiche(z, *verzeichnis, *grenzen);
    pruefe(befund.verletzt == 0, was, zeile);
    std::fprintf(stdout, "  gruen %-38s Maske %4u\n", was, befund.verletzt);
}

}  // namespace

#define ROT(was, zustand, sache) rot((was), (zustand), (sache), __LINE__)
#define GRUEN(was, zustand) gruen((was), (zustand), __LINE__)

int main()
{
    const Verzeichnis v = lies_verzeichnis();
    const Grenzen g = GRENZEN_BAUZEITPUNKT;
    verzeichnis = &v;
    grenzen = &g;

    std::fprintf(stdout, "Grenzen aus parameter.toml (Argumente, kein Dateizugriff, T2):\n");
    std::fprintf(stdout, "  Zeile 304  druck_max  = %lld  # PLATZHALTER\n",
                 static_cast<long long>(g.druck_max));
    std::fprintf(stdout, "  Zeile 205  stufen_max = %lld  # PLATZHALTER\n",
                 static_cast<long long>(g.stufen_max));
    std::fprintf(stdout, "  Zeile 250  aufschlag  = %lld  # PLATZHALTER\n\n",
                 static_cast<long long>(g.aufschlag));

    // --- Abnahme 2: die Adresszahlen, aus dem Verzeichnis gezaehlt ---------------
    {
        PRUEFE(v.vollstaendig);
        PRUEFE(!v.wechselkurs.uebergelaufen);
        PRUEFE(!v.nominalindex.uebergelaufen);
        PRUEFE(!v.produktivitaet.uebergelaufen);
        PRUEFE(!v.leitzinsstand.uebergelaufen);
        PRUEFE(!v.marktwert.uebergelaufen);
        PRUEFE(!v.lobbydruck.uebergelaufen);
        PRUEFE(!v.beteiligungsanteil.uebergelaufen);
        PRUEFE(!v.positionsstufe.uebergelaufen);
        PRUEFE(!v.gleich_leitzins.uebergelaufen);
        PRUEFE(!v.gleich_haushalt.uebergelaufen);
        PRUEFE(!v.sektoren.uebergelaufen);

        PRUEFE(v.wechselkurs.anzahl == 5);
        PRUEFE(v.nominalindex.anzahl == 22);
        PRUEFE(v.produktivitaet.anzahl == 5);
        PRUEFE(v.leitzinsstand.anzahl == 4);
        PRUEFE(v.marktwert.anzahl == 1);
        PRUEFE(v.lobbydruck.anzahl == 32);
        PRUEFE(v.beteiligungsanteil.anzahl == 12);
        PRUEFE(v.positionsstufe.anzahl == 20);
        PRUEFE(v.gleich_leitzins.anzahl == LAENDER);
        PRUEFE(v.gleich_haushalt.anzahl == LAENDER);
        PRUEFE(v.sektoren.anzahl == GEBIETE);
    }

    const Zustand gut = gueltiger_zustand(v);

    // --- Abnahme 2: und dieselben Zahlen noch einmal, aus dem Lauf selbst --------
    //
    // Nicht aus dem Verzeichnis abgeschrieben, sondern gezaehlt, waehrend die
    // Pruefung laeuft: "ueber wie viele Adressen sie tatsaechlich laeuft".
    {
        const Befund lauf = pruefe_wertebereiche(gut, v, g);
        PRUEFE(lauf.verletzt == 0);

        static constexpr std::array<std::size_t, SACHEN> SOLL{5, 22, 5, 4, 1, 32, 32, 4, 4, 5};
        for (std::size_t i = 0; i < SACHEN; ++i) {
            const Sache sache = static_cast<Sache>(i);
            std::fprintf(stdout, "%-46s %3zu Adressen (Soll %3zu)%s\n", name_der_sache(sache),
                         lauf.adressen[i], SOLL[i],
                         lauf.adressen[i] == SOLL[i] ? "" : "   ABWEICHUNG");
            PRUEFE(lauf.adressen[i] == SOLL[i]);
        }
        std::fprintf(stdout,
                     "  Schranke 7 sind 12 Beteiligungsanteile + 20 Positionsstufen;\n"
                     "  Gleichheit 1 und 2 zaehlen Paare (je 2 Adressen),\n"
                     "  Sektoranteile zaehlen Gebiete (je 3 Adressen).\n\n");
    }

    // --- Der Nullzustand ist kein Startzustand ----------------------------------
    {
        const Zustand leer{};
        const Befund befund = pruefe_wertebereiche(leer, v, g);
        std::fprintf(stdout, "Nullzustand: Maske %u -- er ist kein Startzustand.\n\n",
                     befund.verletzt);
        PRUEFE(befund.verletzt != 0);
    }

    // --- Die Fussangel aus Ruecklauf 1 zu Paket 0027, ausgeraeumt ----------------
    //
    // Der Vorgaenger von `Rohling` band je Aufruf einen neuen Startwertzugang. Ein
    // Randfall auf einem Zustand mit gelaufener Runde waere damit am Binden gestorben,
    // mit einer Meldung, die von einem echten Fehler nicht zu unterscheiden ist. Hier
    // laeuft genau dieser Fall: erst die Rundennummer setzen, danach weiter belegen.
    //
    // Die Maske bleibt dabei null, denn `partie.runde` gehoert zu keiner der zehn
    // Sachen. Die Aussage dieser Zeilen ist deshalb nicht die Maske, sondern dass die
    // Belegung ueberhaupt bis zum Ende durchlaeuft.
    {
        Rohling nach_dem_anpfiff{gut};
        nach_dem_anpfiff.lege(STELLE("partie.runde"), 12);
        nach_dem_anpfiff.lege(STELLE("markt.wert"), 1'000'000);
        GRUEN("Belegung traegt auch bei partie.runde = 12", nach_dem_anpfiff);
        std::fprintf(stdout, "\n");
    }

    std::fprintf(stdout, "Abnahme 3 -- jede Sache einmal rot, und die Raender:\n");

    // --- Schranke 1 --------------------------------------------------------------
    {
        const Index us = STELLE("land.US.wechselkurs");
        const Index rw = STELLE("restwelt.wechselkurs");

        Rohling randfall{gut};
        randfall.lege(us, 1);
        GRUEN("wechselkurs = 1 besteht", randfall);

        Rohling kaputt{gut};
        kaputt.lege(us, 0);
        ROT("wechselkurs = 0", kaputt, Sache::Schranke1Wechselkurs);

        Rohling negativ{gut};
        negativ.lege(rw, -1);
        ROT("restwelt.wechselkurs = -1", negativ, Sache::Schranke1Wechselkurs);
    }

    // --- Schranke 2 --------------------------------------------------------------
    {
        Rohling randfall{gut};
        randfall.lege(STELLE("land.US.sektor.1.preis"), 1);
        GRUEN("Nominalindex = 1 besteht", randfall);

        Rohling kaputt{gut};
        kaputt.lege(STELLE("land.US.sektor.1.preis"), 0);
        ROT("land.US.sektor.1.preis = 0", kaputt, Sache::Schranke2Nominalindizes);

        Rohling welt{gut};
        welt.lege(STELLE("welt.preis.2"), -1);
        ROT("welt.preis.2 = -1", welt, Sache::Schranke2Nominalindizes);

        Rohling niveau{gut};
        niveau.lege(STELLE("restwelt.preisniveau"), 0);
        ROT("restwelt.preisniveau = 0", niveau, Sache::Schranke2Nominalindizes);
    }

    // --- Schranke 3 --------------------------------------------------------------
    {
        Rohling randfall{gut};
        randfall.lege(STELLE("land.BR.produktivitaet"), 1);
        GRUEN("produktivitaet = 1 besteht", randfall);

        Rohling kaputt{gut};
        kaputt.lege(STELLE("land.BR.produktivitaet"), 0);
        ROT("land.BR.produktivitaet = 0", kaputt, Sache::Schranke3Produktivitaet);
    }

    // --- Schranke 4 (aufschlag = 51) ---------------------------------------------
    //
    // Der Instrumentenstand und das gleichnamige Aggregat werden zusammen gesetzt --
    // sonst risse dieselbe Aenderung zugleich Gleichheit 1, und die Rotprobe wuerde
    // nicht mehr sagen, welche der beiden Sachen sie gefunden hat.
    {
        const Index stand = STELLE("land.US.instrument.leitzins.stand");
        const Index aggregat = STELLE("land.US.leitzins");

        Rohling randfall{gut};
        randfall.lege(stand, -50);
        randfall.lege(aggregat, -50);
        GRUEN("leitzins = -50, also -50 + 51 = 1", randfall);

        Rohling kaputt{gut};
        kaputt.lege(stand, -51);
        kaputt.lege(aggregat, -51);
        ROT("leitzins = -51, also -51 + 51 = 0", kaputt, Sache::Schranke4Leitzinsuntergrenze);
    }

    // --- Schranke 5 --------------------------------------------------------------
    {
        const Index wert = STELLE("markt.wert");

        Rohling unten{gut};
        unten.lege(wert, 1);
        GRUEN("markt.wert = 1 besteht", unten);

        Rohling oben{gut};
        oben.lege(wert, MARKT_WERT_MAX - 1);
        GRUEN("markt.wert = 9,2e13 - 1 besteht", oben);

        Rohling null{gut};
        null.lege(wert, 0);
        ROT("markt.wert = 0", null, Sache::Schranke5Marktkorb);

        Rohling negativ{gut};
        negativ.lege(wert, -1);
        ROT("markt.wert = -1", negativ, Sache::Schranke5Marktkorb);

        Rohling schranke{gut};
        schranke.lege(wert, MARKT_WERT_MAX);
        ROT("markt.wert = 9,2e13 (echt kleiner)", schranke, Sache::Schranke5Marktkorb);
    }

    // --- Schranke 6 (druck_max = 1) ----------------------------------------------
    {
        const Index druck = STELLE("land.US.instrument.zoll.druck");
        const Index gegen = STELLE("land.DE.instrument.regulierung.gegendruck");

        Rohling randfall{gut};
        randfall.lege(druck, g.druck_max);
        GRUEN("druck = druck_max besteht", randfall);

        Rohling zuviel{gut};
        zuviel.lege(druck, g.druck_max + 1);
        ROT("druck = druck_max + 1", zuviel, Sache::Schranke6Lobbydruck);

        Rohling negativ{gut};
        negativ.lege(gegen, -1);
        ROT("gegendruck = -1", negativ, Sache::Schranke6Lobbydruck);
    }

    // --- Schranke 7 (stufen_max = 1) ---------------------------------------------
    {
        const Index anteil = STELLE("fonds.beteiligung.CN.2.anteil");
        const Index stufe = STELLE("fonds.position.US.1");
        const Index anleihe = STELLE("fonds.position.anleihe.BR");

        Rohling randfall{gut};
        randfall.lege(anteil, 10'000);
        GRUEN("fondsanteil = 10.000 besteht", randfall);

        Rohling zuviel{gut};
        zuviel.lege(anteil, 10'001);
        ROT("fondsanteil = 10.001", zuviel, Sache::Schranke7AnteilUndStufe);

        Rohling negativ{gut};
        negativ.lege(anteil, -1);
        ROT("fondsanteil = -1", negativ, Sache::Schranke7AnteilUndStufe);

        Rohling randfall_kurz{gut};
        randfall_kurz.lege(stufe, -g.stufen_max);
        GRUEN("stufe = -stufen_max besteht", randfall_kurz);

        Rohling zu_lang{gut};
        zu_lang.lege(stufe, g.stufen_max + 1);
        ROT("stufe = stufen_max + 1", zu_lang, Sache::Schranke7AnteilUndStufe);

        Rohling zu_kurz{gut};
        zu_kurz.lege(anleihe, -g.stufen_max - 1);
        ROT("stufe = -stufen_max - 1", zu_kurz, Sache::Schranke7AnteilUndStufe);
    }

    // --- Gleichheit 1 und 2 (T49) -------------------------------------------------
    {
        Rohling kaputt{gut};
        kaputt.lege(STELLE("land.US.leitzins"), 7);
        ROT("land.US.leitzins != instrument.stand", kaputt, Sache::Gleichheit1Leitzins);

        Rohling saldo{gut};
        saldo.lege(STELLE("land.BR.haushaltssaldo"), -3);
        ROT("land.BR.haushaltssaldo != instrument", saldo, Sache::Gleichheit2Haushaltssaldo);
    }

    // --- Die Sektoranteile --------------------------------------------------------
    {
        const Index eins = STELLE("land.US.sektor.1.wertschoepfung");
        const Index zwei = STELLE("land.US.sektor.2.wertschoepfung");
        const Index drei = STELLE("land.US.sektor.3.wertschoepfung");

        // Drei gleich grosse Sektoren: 10.000/3 = 3.333 dreimal ergibt 9.999. Das ist
        // der Rundungsschlupf und kein Fehler -- der Grund, warum ANTEIL_SCHLUPF 1 ist.
        Rohling gedrittelt{gut};
        gedrittelt.lege(eins, 1);
        gedrittelt.lege(zwei, 1);
        gedrittelt.lege(drei, 1);
        GRUEN("Sektoren 1:1:1, Anteilssumme 9.999", gedrittelt);

        Rohling negativ{gut};
        negativ.lege(eins, -100);
        ROT("wertschoepfung < 0, Anteil < 0", negativ, Sache::Sektoranteile);

        Rohling leer{gut};
        leer.lege(eins, 0);
        leer.lege(zwei, 0);
        leer.lege(drei, 0);
        ROT("Summe 0, kein Anteil bildbar", leer, Sache::Sektoranteile);
    }

    // --- Die Summenbedingung, an der reinen Rechnung rot gezeigt -------------------
    //
    // Aus einem Zustand allein ist sie nicht zu reissen: Die Bildungsregel oben haelt
    // die Abweichung bei hoechstens 1. Sie bewacht deshalb die *Regel*, und genau so
    // wird sie hier rot -- mit drei Anteilen, wie eine abschneidende statt rundende
    // Bildung sie liefert: 1/7, 1/7, 5/7 ergibt abgeschnitten 1.428 + 1.428 + 7.142
    // = 9.998, also zwei daneben. Was hier gruen bliebe, pruefte nichts.
    {
        Anteile rund;
        rund.bildbar = true;
        rund.anteil = {1'429, 1'429, 7'143};
        rund.summe = 10'001;
        PRUEFE(anteile_ok(rund));

        Anteile abgeschnitten;
        abgeschnitten.bildbar = true;
        abgeschnitten.anteil = {1'428, 1'428, 7'142};
        abgeschnitten.summe = 9'998;
        PRUEFE(!anteile_ok(abgeschnitten));

        Anteile zu_gross;
        zu_gross.bildbar = true;
        zu_gross.anteil = {10'001, 0, 0};
        zu_gross.summe = 10'001;
        PRUEFE(!anteile_ok(zu_gross));

        Anteile unbildbar;
        PRUEFE(!anteile_ok(unbildbar));

        std::fprintf(stdout,
                     "  rot   %-38s Anteile 1.428+1.428+7.142 = 9.998\n",
                     "Anteilssumme, abschneidend gebildet");
    }

    if (fehlgeschlagen == 0) {
        std::fprintf(stdout, "\nSchranken (T30 Pruefung 2) -- alle Proben bestanden.\n");
        return 0;
    }
    std::fprintf(stderr, "\nSchranken (T30 Pruefung 2) -- %d Probe(n) fehlgeschlagen.\n",
                 fehlgeschlagen);
    return 1;
}
