//! Messstand zu Paket 0243 -- **200 Runden ohne Spieler, nachdem Schritt 5 rechnet**.
//!
//! Dieses Programm ist **kein** Bestandteil des Erzeugnisses. Es liegt unter
//! `befunde/beschraenktheit-nach-schritt/`, wird von keiner `CMakeLists.txt` eingesammelt
//! und haengt an keinem `ctest`-Eintrag. Uebersetzt wird es von `lauf.sh` daneben, gegen
//! die gebaute Kernbibliothek. Der Baum bleibt unveraendert, und die Zahl der
//! ctest-Eintraege des Arbeitsbereichs bleibt dieselbe -- `lauf.sh` zaehlt sie vor und
//! nach der Messung.
//!
//! ## Der Vorlaeufer und die drei Gruende, warum er nicht mehr genuegt
//!
//! `befunde/beschraenktheit/beschraenktheit.cpp` ist der Stand von Paket 0145, gelaufen am
//! 2026-09-06. Er misst dieselben zehn Sachen mit derselben Pruefroutine. Uebernommen ist
//! sie hier woertlich aus ihm, damit die Urteile der beiden Staende vergleichbar bleiben.
//! Drei Dinge haben sich seither bewegt, und jedes einzelne macht den alten Stand
//! unbrauchbar:
//!
//!   1. **`kern::schritt::schritt` nimmt seit Paket 0229 einen vierten Eingang**, den
//!      Parametersatz. Der alte Aufruf mit drei Argumenten uebersetzt nicht mehr.
//!   2. **Die Runde haelt seit Paket 0228 die Pruefsumme des Parametersatzes gegen
//!      `partie.parameter_pruefsumme`.** Der alte Stand setzt diese Adresse nicht, also
//!      traegt sie null; der Lauf braeche in Runde 1 an dieser Schranke ab, ehe eine
//!      Adresse geschrieben ist. Hier wird die Zahl gesetzt, und zwar aus derselben
//!      Rechnung, die die Runde selbst benutzt -- zwei Abschriften einer Summe sind zwei
//!      Stellen, die auseinanderlaufen.
//!   3. **Der alte Stand setzt keine Zustimmung** (`grep -n 'ustimmung'` auf
//!      `beschraenktheit.cpp` hat keinen Treffer), also stehen alle vier auf null, und
//!      null liegt in der Klemme. Ein Lauf auf dieser Lage druckt in jeder Runde die
//!      Aenderungszahl 1 -- auch dann, wenn Schritt 5 rechnet. Er misst „der Startzustand
//!      hat eine Zustimmung ausserhalb `0 ... 10.000`" und nicht „Schritt 5 rechnet".
//!
//! ## Was gemessen wird
//!
//!   1. **Der Lauf.** `kern::schritt::schritt` im Modus `weltlauf`, 200 Runden
//!      nacheinander, ohne Spieler. Je Runde eine Zeile.
//!   2. **Die zehn Sachen** aus `kern/test/schranken_probe.cpp` -- sieben
//!      Wertebereichsschranken, zwei Gleichheiten aus T49, die Sektoranteile. Die
//!      Pruefroutine ist aus jener Probe uebernommen und nicht neu hergeleitet.
//!   3. **Die eine Zahl:** wie viele der 310 Groessen sich ueber *eine* Runde und ueber
//!      *200* Runden gegenueber der Startbelegung unterscheiden. Feld fuer Feld gezaehlt.
//!   4. **Die vier Zustimmungen einzeln** -- Startwert, Endwert und die Schranke, auf der
//!      die Regel sie erwarten laesst. Das ist der Zusatz gegenueber 0145, und er ist der
//!      Grund dieses Standes: Eine Zaehlung unterscheidet den gerechneten Rumpf nicht vom
//!      vortragenden, eine Gegenueberstellung Wert fuer Wert schon.
//!
//! ## Die drei Ausgangslagen
//!
//! Es gibt heute keinen Jahrgang -- der Kasten `daten` aus T13 ist nicht gebaut. Das
//! Argument entscheidet:
//!
//!   `gueltig`  Die Ausgangslage aus `schranken_probe.cpp` (`gueltiger_zustand`):
//!              Wechselkurse, Nominalindizes und Produktivitaeten auf 10.000, Marktkorb
//!              auf 1.000.000, Sektoren 3:3:4. **Dazu die vier Zustimmungen auf
//!              `{10.001, -1, I64_MAX, I64_MIN}`** -- die vier Zahlen, die
//!              `probe_zustimmung_klemmt_statt_vortrag` (`schritt_probe.cpp:1329-1334`)
//!              benutzt, alle vier ausserhalb der Klemme, zwei ueber der oberen und zwei
//!              unter der unteren Schranke, darunter beide Enden des Zahlbereichs.
//!   `null`     Der frische `Zustand` -- **bis auf `partie.parameter_pruefsumme`**, ohne
//!              die keine Runde bis zu einer Rechnung kaeme. Er ist ausdruecklich kein
//!              Startzustand des Spiels; er laeuft mit, weil jede Wertschoepfung null ist
//!              und damit der Nenner der Zustimmungsregel.
//!   `decke`    Die Lage `gueltig`, aber die drei Wertschoepfungen von `land.US` auf
//!              2^62 = 4.611.686.018.427.387.904. Ihre Summe verlaesst den `i64`. Das ist
//!              die Decke der Nennerbedingung, deren Boden Paket 0237 und deren Decke
//!              Paket 0242 eine verortete Meldung gegeben hat.
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
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::festkomma::i128;
using kern::festkomma::mal_geteilt;
using kern::zustand::Adressfund;
using kern::zustand::Gebiet;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::PartieFeld;
using kern::zustand::PolitischeGroesse;
using kern::zustand::Sektor;
using kern::zustand::SektorGroesse;
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
// `kern/test/schranken_probe.cpp` (Paket 0020) ueber
// `befunde/beschraenktheit/beschraenktheit.cpp` (Paket 0145, Stand 2026-09-06).
//
// Uebernommen und nicht nachgebaut, damit die zehn Urteile dieses Standes gegen die
// Urteile von 0145 haltbar sind. Fortgelassen ist ausschliesslich der Probenrahmen
// (`PRUEFE`, `ROT`, `GRUEN`, der Zaehler `fehlgeschlagen`).
//
// Wer die Pruefung aendert, aendert sie in `schranken_probe.cpp` -- diese Abschrift
// haengt an keinem Testeintrag und faellt nicht auf, wenn sie zurueckbleibt. Sie ist der
// Messstand eines Tages und keine zweite Wahrheit.
// ===========================================================================

/// Ein Zustand samt dem **einen** Startwertzugang, der ihn fuellt (Paket 0027).
///
/// Ein Zugang und nicht mehrere: Der Riegel aus 0027 greift beim Binden, und
/// `partie.runde` gehoert selbst zu der Menge, die eine Startbelegung setzt. Ein zweiter
/// Zugang bindet auf einer Lage mit gesetzter Rundennummer nicht mehr.
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
/// Schluesselnamen am Zeilenanfang, nicht ueber eine Zeilennummer. Nachgesehen am
/// 2026-09-08, unveraendert gegenueber 0145:
///
///   parameter.toml, Schluessel `druck_max`:  `druck_max  = 1   # PLATZHALTER`
///   parameter.toml, Schluessel `stufen_max`: `stufen_max = 1   # PLATZHALTER`
///   parameter.toml, Schluessel `aufschlag`:  `aufschlag  = 51  # PLATZHALTER`
///
/// **Diese drei Zahlen sind der Massstab der Pruefung und nicht der Parametersatz der
/// Runde.** Den fuehrt `KONSTANTEN_DER_RUNDE` weiter unten, und er traegt auf allen
/// sieben Schluesselfeldern null. Die beiden Saetze auseinanderzuhalten ist Absicht:
/// Der Massstab bleibt der von 0145, damit die zehn Urteile vergleichbar sind; der
/// Parametersatz bleibt der voreingestellte, damit dieser Stand keine Kalibrierung
/// erfindet, die niemand beschlossen hat.
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

/// Der Parametersatz, mit dem jede Runde dieses Standes faehrt -- alle Felder auf ihrer
/// Vorbelegung, genau wie `KONSTANTEN_DER_PROBE` in `kern/test/schritt_probe.cpp:271`.
///
/// **Ein voreingestellter Satz ist hier richtig.** Was dieser Stand misst, ist die
/// Bindung von Satz und Zustand und die Gestalt der Zustimmungsregel, nicht ihre
/// Kalibrierung. Ein erfundener Satz mit plausiblen Zahlen saehe wie eine Kalibrierung
/// aus, die niemand beschlossen hat -- und `zustimmung_elastizitaet` steht in
/// `parameter.toml:746` ohnehin auf `0  # PLATZHALTER`, der Satz waere also nicht einmal
/// naeher an der Datei.
///
/// Fuer Schritt 5 heisst das etwas Bestimmtes: Der additive Term der Regel ist null, und
/// was gemessen wird, sind ihre beiden Schranken.
constexpr kern::werte::Konstanten KONSTANTEN_DER_RUNDE{};

/// Die vier spielbaren Laender in der Reihenfolge, in der `schritt_5_reaktion` sie nimmt.
constexpr std::array<Gebiet, LAENDER> LAENDER_DER_LAGE = {
    {Gebiet::US, Gebiet::CN, Gebiet::DE, Gebiet::BR}};

/// Die drei Sektoren in der Reihenfolge, in der `kern::werte::bip` sie summiert.
constexpr std::array<Sektor, SEKTOREN> SEKTOREN_DER_LAGE = {
    {Sektor::Landwirtschaft, Sektor::Industrie, Sektor::Dienstleistungen}};

/// Die vier Zustimmungsadressen, gerechnet und nicht hingeschrieben.
constexpr std::array<Index, LAENDER> zustimmungsplaetze()
{
    std::array<Index, LAENDER> plaetze{};
    for (std::size_t n = 0; n < LAENDER; ++n) {
        plaetze[n] =
            kern::zustand::stelle_politisch(LAENDER_DER_LAGE[n], PolitischeGroesse::Zustimmung);
    }
    return plaetze;
}

constexpr std::array<Index, LAENDER> ZUSTIMMUNGSPLAETZE = zustimmungsplaetze();

/// Die vier Startwerte der Zustimmung und die Schranke, auf der die Regel sie erwarten
/// laesst -- beide aus `kern/test/schritt_probe.cpp:1333-1336` uebernommen, damit dieser
/// Stand und jene Probe denselben Fall bauen.
///
/// **Alle vier liegen ausserhalb der Klemme**, zwei ueber der oberen und zwei unter der
/// unteren Schranke, darunter beide Enden des Zahlbereichs. Das ist die eine Lage, auf
/// der sich der gerechnete Rumpf vom vortragenden unterscheiden *kann*: Ein Vortrag
/// liesse alle vier stehen, die Regel bringt alle vier auf ihre Schranke.
constexpr std::array<i64, LAENDER> ZUSTIMMUNG_AUSSERHALB = {
    {10'001, i64{-1}, kern::festkomma::I64_MAX, kern::festkomma::I64_MIN}};

constexpr std::array<i64, LAENDER> ZUSTIMMUNG_SCHRANKE = {{10'000, i64{0}, 10'000, i64{0}}};

/// 2^62. Zwei davon summiert verlassen den `i64` um genau eins -- die kleinste Lage, die
/// die Decke der Nennerbedingung reisst, ohne schon eine einzelne Adresse zu sprengen.
inline constexpr i64 DECKE_WERT = 4'611'686'018'427'387'904;

enum class Lage : std::size_t {
    Gueltig = 0,
    Null = 1,
    Decke = 2,
};

const char* name_der_lage(Lage lage)
{
    switch (lage) {
    case Lage::Gueltig: return "gueltig (wie schranken_probe.cpp, plus vier Zustimmungen "
                               "ausserhalb der Klemme)";
    case Lage::Null: return "null (frischer Zustand, nur die Parameterpruefsumme gesetzt)";
    case Lage::Decke: return "decke (wie gueltig, plus land.US.sektor.1..3.wertschoepfung "
                             "auf 2^62)";
    }
    return "unbekannt";
}

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

int lauf(Lage lage)
{
    const Verzeichnis v = lies_verzeichnis();
    const Grenzen g = GRENZEN_BAUZEITPUNKT;
    const i64 parametersumme = kern::schritt::parameter_pruefsumme(KONSTANTEN_DER_RUNDE);

    std::fprintf(stdout, "Ausgangslage: %s\n", name_der_lage(lage));
    std::fprintf(stdout, "Runden:       %lld, Modus weltlauf, ohne Spieler\n",
                 static_cast<long long>(RUNDEN));
    std::fprintf(stdout,
                 "Grenzen der PRUEFUNG aus parameter.toml (Argumente, kein Dateizugriff, T2): "
                 "druck_max=%lld stufen_max=%lld aufschlag=%lld\n",
                 static_cast<long long>(g.druck_max), static_cast<long long>(g.stufen_max),
                 static_cast<long long>(g.aufschlag));
    std::fprintf(stdout,
                 "Parametersatz der RUNDE: alle sieben Schluesselfelder null (wie "
                 "KONSTANTEN_DER_PROBE); partie.parameter_pruefsumme = %lld\n",
                 static_cast<long long>(parametersumme));

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
    if (lage != Lage::Null) {
        fuelle_gueltig(rohling, v);
        for (std::size_t n = 0; n < LAENDER; ++n) {
            rohling.lege(ZUSTIMMUNGSPLAETZE[n], ZUSTIMMUNG_AUSSERHALB[n]);
        }
    }
    if (lage == Lage::Decke) {
        for (std::size_t s = 0; s < SEKTOREN; ++s) {
            rohling.lege(kern::zustand::stelle_sektorgroesse(Gebiet::US, SEKTOREN_DER_LAGE[s],
                                                             SektorGroesse::Wertschoepfung),
                         DECKE_WERT);
        }
    }
    // Zuletzt, weil der Riegel aus Paket 0027 beim Binden greift und `partie` selbst zu
    // der Menge gehoert, die eine Startbelegung setzt.
    rohling.lege(kern::zustand::stelle_partie(PartieFeld::ParameterPruefsumme), parametersumme);

    const Zustand start = rohling;

    std::fprintf(stdout, "Die vier Zustimmungen zu Beginn:\n");
    for (std::size_t n = 0; n < LAENDER; ++n) {
        const Index platz = ZUSTIMMUNGSPLAETZE[n];
        std::fprintf(stdout, "  %-24s Platz %3zu  Start %21lld  Schranke der Regel %6lld\n",
                     index_zu_adresse(platz), platz, static_cast<long long>(start.lies(platz)),
                     static_cast<long long>(ZUSTIMMUNG_SCHRANKE[n]));
    }
    std::fprintf(stdout, "\n");

    const Befund vor_dem_anfang = pruefe_wertebereiche(start, v, g);
    std::fprintf(stdout, "Runde   0: Startbelegung                                          "
                         "                     Maske %4u  Pruefsumme %016llx\n",
                 vor_dem_anfang.verletzt,
                 static_cast<unsigned long long>(kern::zustand::pruefsumme_von(start)));
    drucke_maske("START ", 0, vor_dem_anfang, start);

    std::array<Schrankenlage, SACHEN> schranke{};
    for (std::size_t i = 0; i < SACHEN; ++i) {
        if ((vor_dem_anfang.verletzt & nur(static_cast<Sache>(i))) != 0) {
            const Index stelle = vor_dem_anfang.erste_stelle[i];
            schranke[i] =
                Schrankenlage{true, 0, stelle, stelle < FELDER ? start.lies(stelle) : 0};
        }
    }

    Zustand zustand = start;
    std::size_t nach_einer_runde = 0;
    i64 erreichte_runde = 0;

    try {
        for (i64 runde = 1; runde <= RUNDEN; ++runde) {
            const kern::schritt::Aktionsbuendel ohne_spieler{};
            const kern::schritt::Rundenergebnis ergebnis = kern::schritt::schritt(
                zustand, ohne_spieler, KONSTANTEN_DER_RUNDE, kern::schreiber::Modus::Weltlauf);

            const std::size_t seit_vorrunde = abweichende_felder(zustand, ergebnis.neuer_zustand);
            const std::size_t seit_start = abweichende_felder(start, ergebnis.neuer_zustand);
            if (runde == 1) {
                nach_einer_runde = seit_start;
            }

            const Befund befund = pruefe_wertebereiche(ergebnis.neuer_zustand, v, g);
            for (std::size_t i = 0; i < SACHEN; ++i) {
                if ((befund.verletzt & nur(static_cast<Sache>(i))) == 0 || schranke[i].gerissen) {
                    continue;
                }
                const Index stelle = befund.erste_stelle[i];
                schranke[i] =
                    Schrankenlage{true, runde, stelle,
                                  stelle < FELDER ? ergebnis.neuer_zustand.lies(stelle) : 0};
            }

            std::fprintf(stdout,
                         "Runde %3lld: partie.runde=%3lld  Kette %3zu  geaendert ggue. Vorrunde "
                         "%3zu  ggue. Start %3zu  Maske %4u  Pruefsumme %016llx\n",
                         static_cast<long long>(runde),
                         static_cast<long long>(ergebnis.neuer_zustand.lies(
                             kern::zustand::stelle_partie(PartieFeld::Runde))),
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

    // --- Die vier Zustimmungen, Wert gegen Wert -----------------------------------
    // Der Zusatz gegenueber 0145 und der Grund dieses Standes. Eine Zaehlung
    // unterscheidet den gerechneten Rumpf nicht vom vortragenden; diese vier Zeilen tun
    // es, solange die Startwerte ausserhalb der Klemme liegen.
    std::fprintf(stdout, "\nDie vier Zustimmungen nach %lld Runden:\n",
                 static_cast<long long>(RUNDEN));
    std::size_t auf_der_schranke = 0;
    std::size_t stehen_geblieben = 0;
    for (std::size_t n = 0; n < LAENDER; ++n) {
        const Index platz = ZUSTIMMUNGSPLAETZE[n];
        const i64 anfang = start.lies(platz);
        const i64 ende = zustand.lies(platz);
        if (ende == ZUSTIMMUNG_SCHRANKE[n]) {
            ++auf_der_schranke;
        }
        if (ende == anfang) {
            ++stehen_geblieben;
        }
        std::fprintf(stdout, "  %-24s Start %21lld  Ende %21lld  Schranke %6lld  %s\n",
                     index_zu_adresse(platz), static_cast<long long>(anfang),
                     static_cast<long long>(ende),
                     static_cast<long long>(ZUSTIMMUNG_SCHRANKE[n]),
                     ende == ZUSTIMMUNG_SCHRANKE[n] ? "auf der Schranke"
                                                    : (ende == anfang ? "STEHEN GEBLIEBEN"
                                                                      : "weder noch"));
    }
    std::fprintf(stdout,
                 "  %zu von %zu auf der Schranke, %zu von %zu stehen geblieben.\n"
                 "  Vier auf der Schranke und null stehen geblieben heisst: Schritt 5 "
                 "rechnet.\n"
                 "  Null auf der Schranke und vier stehen geblieben heisst: er traegt vor.\n",
                 auf_der_schranke, LAENDER, stehen_geblieben, LAENDER);

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

    // --- Je Schranke eine Aussage ------------------------------------------------
    std::fprintf(stdout, "\nJe Sache eine Aussage ueber den ganzen Lauf:\n");
    for (std::size_t i = 0; i < SACHEN; ++i) {
        const Sache sache = static_cast<Sache>(i);
        if (!schranke[i].gerissen) {
            std::fprintf(stdout, "  GEHALTEN   %s\n", name_der_sache(sache));
            continue;
        }
        const Index stelle = schranke[i].erste_stelle;
        std::fprintf(stdout,
                     "  GERISSEN   %s -- zuerst in Runde %lld, %s (Platz %zu), Wert %lld\n",
                     name_der_sache(sache), static_cast<long long>(schranke[i].erste_runde),
                     stelle < FELDER ? index_zu_adresse(stelle) : "(keine)", stelle,
                     static_cast<long long>(schranke[i].erster_wert));
    }

    std::fprintf(stdout, "\nLauf ueber %lld Runden vollstaendig. Rueckgabewert 0.\n",
                 static_cast<long long>(RUNDEN));
    return 0;
}

}  // namespace

int main(int argc, char** argv)
{
    Lage lage = Lage::Gueltig;
    if (argc > 1) {
        if (std::strcmp(argv[1], "null") == 0) {
            lage = Lage::Null;
        } else if (std::strcmp(argv[1], "decke") == 0) {
            lage = Lage::Decke;
        } else if (std::strcmp(argv[1], "gueltig") != 0) {
            std::fprintf(stderr, "Aufruf: %s [gueltig|null|decke]\n", argv[0]);
            return 1;
        }
    }
    return lauf(lage);
}
