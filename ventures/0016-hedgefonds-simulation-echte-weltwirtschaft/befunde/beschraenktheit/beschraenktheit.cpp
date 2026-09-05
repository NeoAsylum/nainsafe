//! Messstand zu Paket 0145 -- **200 Runden ohne Spieler**, T30 Pruefung 6.
//!
//! Dieses Programm ist **kein** Bestandteil des Erzeugnisses. Es liegt unter
//! `befunde/beschraenktheit/`, wird von keiner `CMakeLists.txt` eingesammelt und haengt
//! an keinem `ctest`-Eintrag. Uebersetzt wird es von `lauf.sh` daneben, gegen die
//! gebaute Kernbibliothek. Der Grund ist Abnahmebedingung 4 des Arbeitspakets: Der Baum
//! bleibt unveraendert, und die Zahl der ctest-Eintraege des Arbeitsbereichs bleibt
//! dieselbe.
//!
//! ## Was gemessen wird
//!
//!   1. **Der Lauf.** `kern::schritt::schritt` im Modus `weltlauf`, 200 Runden
//!      nacheinander, ohne Spieler (das `Aktionsbuendel` ist im `weltlauf` nach T38
//!      ohnehin folgenlos). Je Runde eine Zeile mit der Rundennummer.
//!   2. **Die sieben Wertebereichsschranken** aus der Tabelle unter T30 in
//!      `technik.md`, dazu die zwei Gleichheiten aus T49 und die Sektoranteile -- also
//!      genau die zehn Sachen, die `kern/test/schranken_probe.cpp` prueft. Die
//!      Pruefroutine unten ist aus jener Probe uebernommen und nicht neu hergeleitet;
//!      das Arbeitspaket verlangt ausdruecklich denselben Massstab und keinen zweiten.
//!   3. **Die eine Zahl:** wie viele der 310 Groessen sich ueber *eine* Runde und ueber
//!      *200* Runden gegenueber der Startbelegung unterscheiden. Gezaehlt wird Feld fuer
//!      Feld ueber `Zustand::lies`, nicht geschaetzt.
//!
//! ## Was hier ausdruecklich nicht geschieht
//!
//! **Es wird kein `Verlauf` angelegt.** Der Rumpf des Arbeitspakets begruendet das
//! nachgemessen: Die Rundenkapazitaet des Verlaufs steht bei zwanzig, ein Lauf mit
//! Verlauf endete also in Runde 21 mit einer Aussage ueber den Behaelter statt ueber das
//! Modell. `kern::schritt::schritt` gibt die Rundenkette je Runde frisch zurueck; wer
//! nur Ergebnisse zaehlt, wirft sie weg. Genau das tut dieses Programm -- die Kette wird
//! gelesen (ihre Laenge steht in der Zeile) und danach mit dem `Rundenergebnis`
//! verworfen.
//!
//! **Es wird nichts repariert.** Was ausserhalb der Schranken liegt, wird gemeldet, und
//! der Lauf laeuft weiter: Nach der Vorgabe ist eine verlassene Schranke ein Befund und
//! kein harter Fehler dieses Laufs (T30 Pruefung 6, "neunter Rueckkopplungskanal").
//!
//! ## Die zwei Ausgangslagen
//!
//! Es gibt heute keinen Jahrgang -- der Kasten `daten` aus T13 ist nicht gebaut, und ein
//! frischer `Zustand` ist durchgehend null. Gelaufen wird deshalb gegen beide Lagen, und
//! das Argument entscheidet:
//!
//!   `gueltig`  Die Ausgangslage, die `schranken_probe.cpp` selbst als gueltig baut
//!              (`gueltiger_zustand`): Wechselkurse, Nominalindizes und
//!              Produktivitaeten auf 10.000, Marktkorb auf 1.000.000, Sektoren 3:3:4.
//!              Sie reisst am Anfang keine der zehn Sachen. Das ist der Lauf, ueber den
//!              Abnahmebedingung 2 spricht.
//!   `null`     Der frische `Zustand`. Er reisst schon vor der ersten Runde mehrere
//!              Sachen und ist ausdruecklich kein Startzustand des Spiels. Er laeuft
//!              trotzdem mit, weil er die Gegenprobe ist: Bewegt sich seine Maske ueber
//!              200 Runden, dann rechnet die Runde etwas; bleibt sie stehen, traegt sie
//!              vor.
//!
//! Rueckgabe 0 heisst: Der Lauf ist ueber alle 200 Runden gekommen. Rueckgabe 2 heisst:
//! Er ist abgebrochen; Rundennummer und Meldung im Wortlaut stehen dann in der letzten
//! Zeile der Ausgabe. Ein Schrankenbefund allein aendert die Rueckgabe nicht -- er ist
//! der Gegenstand der Messung und nicht ihr Scheitern.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
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

/// Wie viele Runden gerechnet werden -- die Zahl aus T30 Pruefung 6.
constexpr i64 RUNDEN = 200;

// ===========================================================================
// Ab hier bis zum Ende von `fuelle_gueltig` ist der Massstab uebernommen aus
// `kern/test/schranken_probe.cpp` (Paket 0020, Stand Commit 5d04c39).
//
// Uebernommen und nicht nachgebaut, weil das Arbeitspaket es so verlangt: "Sie ist
// bereits als Probe gebaut (`kern/test/schranken_probe.cpp`); nimm sie als Massstab,
// statt einen zweiten zu erfinden." Fortgelassen ist ausschliesslich der Probenrahmen
// (`PRUEFE`, `ROT`, `GRUEN`, der Zaehler `fehlgeschlagen`) -- er ist der Weg, die
// Pruefroutine an einzelnen Randfaellen rot zu zeigen; hier laeuft sie ueber einen Lauf
// statt ueber Randfaelle. Die Pruefung selbst ist unangetastet.
//
// Wer die Pruefung aendert, aendert sie in `schranken_probe.cpp` -- diese Abschrift
// haengt an keinem Testeintrag und faellt nicht auf, wenn sie zurueckbleibt. Sie ist der
// Messstand eines Tages und keine zweite Wahrheit.
// ===========================================================================

/// Ein Zustand samt dem **einen** Startwertzugang, der ihn fuellt (Paket 0027).
class Rohling {
public:
    Rohling() = default;

    void lege(Index platz, i64 wert) { zugang_.setze(platz, wert); }

    operator const Zustand&() const { return zustand_; }

private:
    Zustand       zustand_;
    Startbelegung zugang_{zustand_};
};

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

inline constexpr std::size_t MENGE_MAX = 64;
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

        if (endet_auf(a, ".wechselkurs")) {
            v.wechselkurs.nimm(i);
        }

        if (endet_auf(a, ".preis") || endet_auf(a, ".preisniveau")
            || beginnt_mit(a, "welt.preis.")) {
            v.nominalindex.nimm(i);
        }

        if (endet_auf(a, ".produktivitaet")) {
            v.produktivitaet.nimm(i);
        }

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

        if (endet_auf(a, ".druck") || endet_auf(a, ".gegendruck")) {
            v.lobbydruck.nimm(i);
        }

        if (beginnt_mit(a, "fonds.beteiligung.") && endet_auf(a, ".anteil")) {
            v.beteiligungsanteil.nimm(i);
        }

        if (beginnt_mit(a, "fonds.position.")) {
            v.positionsstufe.nimm(i);
        }

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

struct Grenzen {
    i64 druck_max = 0;   // Schluessel `druck_max`
    i64 stufen_max = 0;  // Schluessel `stufen_max`
    i64 aufschlag = 0;   // Schluessel `aufschlag`
};

/// Derselbe Stand von `parameter.toml` wie in `schranken_probe.cpp`, und aus demselben
/// Grund als Argument statt als eingebrannte Zahl (T2: der Kern liest keine Datei).
/// Alle drei Zeilen tragen dort `# PLATZHALTER`; wiederzufinden sind sie ueber den
/// Schluesselnamen am Zeilenanfang, nicht ueber eine Zeilennummer.
///
///   parameter.toml, Schluessel `druck_max`:  `druck_max  = 1   # PLATZHALTER`
///   parameter.toml, Schluessel `stufen_max`: `stufen_max = 1   # PLATZHALTER`
///   parameter.toml, Schluessel `aufschlag`:  `aufschlag  = 51  # PLATZHALTER`
inline constexpr Grenzen GRENZEN_BAUZEITPUNKT{1, 1, 51};

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

inline constexpr i64 ANTEIL_GANZ = 10'000;
inline constexpr i64 ANTEIL_SCHLUPF = 1;

struct Anteile {
    bool bildbar = false;
    std::array<i64, SEKTOREN> anteil{};
    i64 summe = 0;
};

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

/// Die Ueberlaufschranke von `tsd_in_cent` (T47), als Zahl: 9,2 * 10^13.
inline constexpr i64 MARKT_WERT_MAX = 92'000'000'000'000;

Befund pruefe_wertebereiche(const Zustand& zustand, const Verzeichnis& v, const Grenzen& g)
{
    Befund befund;

    for (std::size_t k = 0; k < v.wechselkurs.anzahl; ++k) {
        const Index stelle = v.wechselkurs.platz[k];
        befund.besucht(Sache::Schranke1Wechselkurs);
        if (zustand.lies(stelle) < 1) {
            befund.melde(Sache::Schranke1Wechselkurs, stelle);
        }
    }

    for (std::size_t k = 0; k < v.nominalindex.anzahl; ++k) {
        const Index stelle = v.nominalindex.platz[k];
        befund.besucht(Sache::Schranke2Nominalindizes);
        if (zustand.lies(stelle) <= 0) {
            befund.melde(Sache::Schranke2Nominalindizes, stelle);
        }
    }

    for (std::size_t k = 0; k < v.produktivitaet.anzahl; ++k) {
        const Index stelle = v.produktivitaet.platz[k];
        befund.besucht(Sache::Schranke3Produktivitaet);
        if (zustand.lies(stelle) <= 0) {
            befund.melde(Sache::Schranke3Produktivitaet, stelle);
        }
    }

    for (std::size_t k = 0; k < v.leitzinsstand.anzahl; ++k) {
        const Index stelle = v.leitzinsstand.platz[k];
        befund.besucht(Sache::Schranke4Leitzinsuntergrenze);
        const i128 summe = static_cast<i128>(zustand.lies(stelle)) + static_cast<i128>(g.aufschlag);
        if (summe < 1) {
            befund.melde(Sache::Schranke4Leitzinsuntergrenze, stelle);
        }
    }

    for (std::size_t k = 0; k < v.marktwert.anzahl; ++k) {
        const Index stelle = v.marktwert.platz[k];
        befund.besucht(Sache::Schranke5Marktkorb);
        const i64 wert = zustand.lies(stelle);
        if (wert <= 0 || wert >= MARKT_WERT_MAX) {
            befund.melde(Sache::Schranke5Marktkorb, stelle);
        }
    }

    for (std::size_t k = 0; k < v.lobbydruck.anzahl; ++k) {
        const Index stelle = v.lobbydruck.platz[k];
        befund.besucht(Sache::Schranke6Lobbydruck);
        const i64 wert = zustand.lies(stelle);
        if (wert < 0 || wert > g.druck_max) {
            befund.melde(Sache::Schranke6Lobbydruck, stelle);
        }
    }

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

    for (std::size_t k = 0; k < v.sektoren.anzahl; ++k) {
        const Dreier& gruppe = v.sektoren.gruppe[k];
        befund.besucht(Sache::Sektoranteile);
        if (!anteile_ok(anteile_aus_zustand(zustand, gruppe))) {
            befund.melde(Sache::Sektoranteile, gruppe.platz[0]);
        }
    }

    return befund;
}

/// Die gueltige Ausgangslage, aus `schranken_probe.cpp` uebernommen. Leitzinsstaende,
/// Druecke, Anteile und Stufen bleiben null -- null liegt in jedem dieser Bereiche, und
/// `0 + aufschlag = 51 >= 1` haelt Schranke 4.
void fuelle_gueltig(Rohling& z, const Verzeichnis& v)
{
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
    for (std::size_t k = 0; k < v.sektoren.anzahl; ++k) {
        const Dreier& gruppe = v.sektoren.gruppe[k];
        z.lege(gruppe.platz[0], 3'000);
        z.lege(gruppe.platz[1], 3'000);
        z.lege(gruppe.platz[2], 4'000);
    }
}

// ===========================================================================
// Ende der Uebernahme. Ab hier steht, was dieses Paket misst.
// ===========================================================================

/// Wie viele der 310 Groessen zwischen zwei Zustaenden verschieden sind.
std::size_t abweichende_felder(const Zustand& a, const Zustand& b)
{
    std::size_t zahl = 0;
    for (Index i = 0; i < FELDER; ++i) {
        if (a.lies(i) != b.lies(i)) {
            ++zahl;
        }
    }
    return zahl;
}

/// Was ueber den ganzen Lauf hinweg von jeder der zehn Sachen bekannt ist.
struct Schrankenlage {
    bool gerissen = false;
    i64 erste_runde = 0;
    Index erste_stelle = KEIN_PLATZ;
    i64 erster_wert = 0;
};

void drucke_maske(const char* was, i64 runde, const Befund& befund, const Zustand& z)
{
    if (befund.verletzt == 0) {
        return;
    }
    for (std::size_t i = 0; i < SACHEN; ++i) {
        if ((befund.verletzt & nur(static_cast<Sache>(i))) == 0) {
            continue;
        }
        const Index stelle = befund.erste_stelle[i];
        std::fprintf(stdout, "   %s Runde %lld: %s -- erste Adresse %s (Platz %zu), Wert %lld\n",
                     was, static_cast<long long>(runde), name_der_sache(static_cast<Sache>(i)),
                     stelle < FELDER ? index_zu_adresse(stelle) : "(keine)", stelle,
                     stelle < FELDER ? static_cast<long long>(z.lies(stelle)) : 0LL);
    }
}

int lauf(bool gueltige_lage)
{
    const Verzeichnis v = lies_verzeichnis();
    const Grenzen g = GRENZEN_BAUZEITPUNKT;

    std::fprintf(stdout, "Ausgangslage: %s\n",
                 gueltige_lage ? "gueltig (wie schranken_probe.cpp)" : "null (frischer Zustand)");
    std::fprintf(stdout, "Runden:       %lld, Modus weltlauf, ohne Spieler\n",
                 static_cast<long long>(RUNDEN));
    std::fprintf(stdout,
                 "Grenzen aus parameter.toml (Argumente, kein Dateizugriff, T2): "
                 "druck_max=%lld stufen_max=%lld aufschlag=%lld\n",
                 static_cast<long long>(g.druck_max), static_cast<long long>(g.stufen_max),
                 static_cast<long long>(g.aufschlag));

    // Das Verzeichnis ist der Massstab; laeuft es anders aus als in der Probe, misst
    // dieser Lauf etwas anderes als T30 Pruefung 2. Deshalb stehen die Zahlen hier --
    // gezaehlt, nicht abgeschrieben.
    std::fprintf(stdout,
                 "Adressmengen  ist:  wechselkurs=%zu nominalindex=%zu produktivitaet=%zu "
                 "leitzinsstand=%zu marktwert=%zu druck=%zu anteil=%zu stufe=%zu "
                 "paar_leitzins=%zu paar_haushalt=%zu sektorgruppen=%zu vollstaendig=%d\n",
                 v.wechselkurs.anzahl, v.nominalindex.anzahl, v.produktivitaet.anzahl,
                 v.leitzinsstand.anzahl, v.marktwert.anzahl, v.lobbydruck.anzahl,
                 v.beteiligungsanteil.anzahl, v.positionsstufe.anzahl, v.gleich_leitzins.anzahl,
                 v.gleich_haushalt.anzahl, v.sektoren.anzahl, v.vollstaendig ? 1 : 0);
    std::fprintf(stdout,
                 "Adressmengen soll:  wechselkurs=5 nominalindex=22 produktivitaet=5 "
                 "leitzinsstand=4 marktwert=1 druck=32 anteil=12 stufe=20 "
                 "paar_leitzins=%zu paar_haushalt=%zu sektorgruppen=%zu vollstaendig=1\n\n",
                 LAENDER, LAENDER, GEBIETE);

    Rohling rohling;
    if (gueltige_lage) {
        fuelle_gueltig(rohling, v);
    }
    const Zustand start = rohling;

    const Befund vor_dem_anfang = pruefe_wertebereiche(start, v, g);
    std::fprintf(stdout, "Runde   0: Startbelegung                                          "
                         "                     Maske %4u  Pruefsumme %016llx\n",
                 vor_dem_anfang.verletzt,
                 static_cast<unsigned long long>(kern::zustand::pruefsumme_von(start)));
    drucke_maske("START ", 0, vor_dem_anfang, start);

    std::array<Schrankenlage, SACHEN> lage{};
    for (std::size_t i = 0; i < SACHEN; ++i) {
        if ((vor_dem_anfang.verletzt & nur(static_cast<Sache>(i))) != 0) {
            const Index stelle = vor_dem_anfang.erste_stelle[i];
            lage[i] = Schrankenlage{true, 0, stelle, stelle < FELDER ? start.lies(stelle) : 0};
        }
    }

    Zustand zustand = start;
    std::size_t nach_einer_runde = 0;
    i64 erreichte_runde = 0;

    try {
        for (i64 runde = 1; runde <= RUNDEN; ++runde) {
            const kern::schritt::Aktionsbuendel ohne_spieler{};
            const kern::schritt::Rundenergebnis ergebnis =
                kern::schritt::schritt(zustand, ohne_spieler, kern::schreiber::Modus::Weltlauf);

            const std::size_t seit_vorrunde = abweichende_felder(zustand, ergebnis.neuer_zustand);
            const std::size_t seit_start = abweichende_felder(start, ergebnis.neuer_zustand);
            if (runde == 1) {
                nach_einer_runde = seit_start;
            }

            const Befund befund = pruefe_wertebereiche(ergebnis.neuer_zustand, v, g);
            for (std::size_t i = 0; i < SACHEN; ++i) {
                if ((befund.verletzt & nur(static_cast<Sache>(i))) == 0 || lage[i].gerissen) {
                    continue;
                }
                const Index stelle = befund.erste_stelle[i];
                lage[i] = Schrankenlage{true, runde, stelle,
                                        stelle < FELDER ? ergebnis.neuer_zustand.lies(stelle) : 0};
            }

            std::fprintf(stdout,
                         "Runde %3lld: partie.runde=%3lld  Kette %3zu  geaendert ggue. Vorrunde "
                         "%3zu  ggue. Start %3zu  Maske %4u  Pruefsumme %016llx\n",
                         static_cast<long long>(runde),
                         static_cast<long long>(ergebnis.neuer_zustand.lies(
                             kern::zustand::stelle_partie(kern::zustand::PartieFeld::Runde))),
                         ergebnis.kette_dieser_runde.laenge(), seit_vorrunde, seit_start,
                         befund.verletzt,
                         static_cast<unsigned long long>(
                             kern::zustand::pruefsumme_von(ergebnis.neuer_zustand)));
            drucke_maske("BEFUND", runde, befund, ergebnis.neuer_zustand);

            zustand = ergebnis.neuer_zustand;
            erreichte_runde = runde;
        }
    } catch (const std::exception& fehler) {
        std::fprintf(stdout,
                     "\nABBRUCH in Runde %lld (die letzte vollstaendige war %lld).\n"
                     "Meldung im Wortlaut: %s\n"
                     "Rueckgabewert dieses Laufs: 2\n",
                     static_cast<long long>(erreichte_runde + 1),
                     static_cast<long long>(erreichte_runde), fehler.what());
        return 2;
    }

    // --- Die eine Zahl, gemessen ------------------------------------------------
    const std::size_t nach_allen = abweichende_felder(start, zustand);
    std::fprintf(stdout,
                 "\nDie eine Zahl, Feld fuer Feld gezaehlt (Zustand::lies ueber alle %zu Plaetze):\n"
                 "  ueber EINE Runde   gegenueber der Startbelegung: %zu von %zu\n"
                 "  ueber %lld Runden  gegenueber der Startbelegung: %zu von %zu\n",
                 FELDER, nach_einer_runde, FELDER, static_cast<long long>(RUNDEN), nach_allen,
                 FELDER);

    std::fprintf(stdout, "\nWelche Adressen sich unterscheiden (Start -> Ende):\n");
    if (nach_allen == 0) {
        std::fprintf(stdout, "  keine.\n");
    }
    for (Index i = 0; i < FELDER; ++i) {
        if (start.lies(i) == zustand.lies(i)) {
            continue;
        }
        std::fprintf(stdout, "  Platz %3zu  %-50s  %lld -> %lld\n", i, index_zu_adresse(i),
                     static_cast<long long>(start.lies(i)),
                     static_cast<long long>(zustand.lies(i)));
    }

    // --- Je Schranke eine Aussage (Abnahmebedingung 2) ---------------------------
    std::fprintf(stdout, "\nJe Sache eine Aussage ueber den ganzen Lauf:\n");
    for (std::size_t i = 0; i < SACHEN; ++i) {
        const Sache sache = static_cast<Sache>(i);
        if (!lage[i].gerissen) {
            std::fprintf(stdout, "  GEHALTEN   %s\n", name_der_sache(sache));
            continue;
        }
        const Index stelle = lage[i].erste_stelle;
        std::fprintf(stdout,
                     "  GERISSEN   %s -- zuerst in Runde %lld, %s (Platz %zu), Wert %lld\n",
                     name_der_sache(sache), static_cast<long long>(lage[i].erste_runde),
                     stelle < FELDER ? index_zu_adresse(stelle) : "(keine)", stelle,
                     static_cast<long long>(lage[i].erster_wert));
    }

    std::fprintf(stdout, "\nLauf ueber %lld Runden vollstaendig. Rueckgabewert 0.\n",
                 static_cast<long long>(RUNDEN));
    return 0;
}

}  // namespace

int main(int argc, char** argv)
{
    bool gueltige_lage = true;
    if (argc > 1) {
        if (std::strcmp(argv[1], "null") == 0) {
            gueltige_lage = false;
        } else if (std::strcmp(argv[1], "gueltig") != 0) {
            std::fprintf(stderr, "Aufruf: %s [gueltig|null]\n", argv[0]);
            return 1;
        }
    }
    return lauf(gueltige_lage);
}
