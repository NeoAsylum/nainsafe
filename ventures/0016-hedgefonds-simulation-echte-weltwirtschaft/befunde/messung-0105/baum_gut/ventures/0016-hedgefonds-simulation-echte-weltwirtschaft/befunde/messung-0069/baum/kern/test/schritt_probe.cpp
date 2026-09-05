//! Laufende Probe fuer `kern::schritt` -- die acht Bedingungen des Arbeitspakets 0033,
//! **Bedingung 6 in der Fassung von Paket 0071**.
//!
//! Bedingung 6 von 0033 verlangte die *unveraenderte* Pruefsumme ueber eine Runde. Sie
//! ist widerrufen -- 0033 hatte sie als "auf Widerruf" ausgewiesen --, und an ihrer
//! Stelle steht die schaerfere Aussage: **Genau eine der 310 Groessen aendert sich,
//! naemlich `partie.runde`.** Was die alte Fassung nicht leisten konnte, ist der Grund
//! des Widerrufs: Ein Zustand, den eine vollstaendige Runde Feld fuer Feld unveraendert
//! laesst, ist von "keine Runde gelaufen" durch keinen Vergleich zu unterscheiden.
//!
//! Die Aufteilung der Sollmaske auf die sechs Schritte ist in `src/schritt.cpp` schon
//! als `static_assert` bewiesen (3 + 0 + 16 + 152 + 4 + 0 = 175). Diese Probe gibt es
//! fuer das, was ein `static_assert` nicht kann:
//!
//!   1. **Die gelaufene Runde.** Dass die Rundenendpruefung aus T38 haelt, sieht man
//!      nur, wenn eine Runde wirklich laeuft -- sie bricht hart ab, wenn eine
//!      Maskenadresse fehlt oder eine ausserhalb beruehrt wurde.
//!   2. **Die Abbrueche.** Der `spielmodus`, die negative Rundennummer und die nicht
//!      mehr zaehlbare sind Wuerfe, und ein Wurf laesst sich nur zur Laufzeit fangen.
//!      Beim `spielmodus` wird zusaetzlich der **Wortlaut** geprueft: Bedingung 7
//!      verlangt, dass die Meldung sagt, warum.
//!   3. **Der unabhaengige Erwartungswert.** Der Zustand nach der Runde wird nicht gegen
//!      eine abgeschriebene Zahl gehalten, sondern gegen eine **zweite Bauart desselben
//!      Zustands**: dieselbe Ausgangslage, ueber `zustand::Startbelegung` gebaut, nur mit
//!      der Rundennummer dieser Runde. Diese zweite Bauart weiss von `kern::schritt`
//!      nichts. Die Pruefsummen ueber die kanonische Byteform (T12) stehen daneben und
//!      werden ausgedruckt -- beide, vorher und nachher, denn der Widerruf oben ist nur
//!      dann einer, wenn die beiden Zahlen im Wortlaut dastehen.
//!   4. **Das Testprofil aus ADR 0011, Massnahme 2.** Sie linkt `kern_geprueft`, also
//!      dieselben Quellen mit den Sanitizern. Ein Sanitizer sieht nur, was wirklich
//!      laeuft.
//!   5. **Die Zahlen im Wortlaut.** Was diese Probe ausrechnet, schreibt sie hin.
//!
//! **Zu Bedingung 1 (die Signatur) und Bedingung 5 (der Schreibweg):** Beide sind
//! Mustervergleiche ueber `src/schritt.cpp` und `include/kern/schritt.hpp` und keine
//! Laufzeitfragen. Ihre Suchmuster stehen deshalb **in keiner der beiden Dateien** --
//! eine Datei, die ihr eigenes Suchmuster zitiert, laesst es nie leer ausgehen. Was die
//! Probe dazu beitragen kann, ist die Gegenrichtung: Sie ruft `schritt` mit genau drei
//! Argumenten (Zustand, Buendel, Modus) und bekommt beides zurueck, Zustand und Kette.
//! Ein viertes Argument gaebe es nicht zu uebergeben.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <span>
#include <stdexcept>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::schreiber::Bitfeld;
using kern::schreiber::Kette;
using kern::schreiber::Modus;
using kern::schreiber::UrsacheArt;
using kern::schreiber::Ursachensatz;
using kern::schreiber::sollmaske;
using kern::schreiber::sollmaskengroesse;

using kern::schritt::Aktionsbuendel;
using kern::schritt::Rundenergebnis;

using kern::zustand::FELDER;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::PartieFeld;
using kern::zustand::Startbelegung;
using kern::zustand::Zustand;

using u64 = std::uint64_t;

/// Der Platz von `partie.runde` -- die eine Adresse, die eine Runde seit Paket 0071
/// aendert. Aus der Adressrechnung geholt und nicht als 306 hingeschrieben: Verschoebe
/// ein spaeteres Paket den Partieblock, prueft diese Datei weiter das richtige Feld.
constexpr Index PLATZ_RUNDE = kern::zustand::stelle_partie(PartieFeld::Runde);

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// Ob `nadel` in `heuhaufen` vorkommt -- ohne `<string>`, das nach `sperre.hpp` keine
/// Kernquelle mehr einbinden darf.
bool enthaelt(const char* heuhaufen, const char* nadel)
{
    if (heuhaufen == nullptr || nadel == nullptr) {
        return false;
    }
    for (std::size_t i = 0; heuhaufen[i] != '\0'; ++i) {
        std::size_t j = 0;
        while (nadel[j] != '\0' && heuhaufen[i + j] == nadel[j]) {
            ++j;
        }
        if (nadel[j] == '\0') {
            return true;
        }
    }
    return false;
}

/// Die Pruefsumme des Zustands ueber die kanonische Byteform (T12) -- der unabhaengige
/// Erwartungswert aus Bedingung 6.
///
/// Gerechnet wird ueber `zustand::nach_bytes` und FNV-1a-64 aus `kern::pruefsumme`, also
/// ueber zwei Kaesten, die von `kern::schritt` nichts wissen. `zustand::pruefsumme_von`
/// rechnet dieselbe Summe auf dem kuerzeren Weg; die Probe stellt beide gegeneinander,
/// damit die Aussage nicht an einer einzigen Rechnung haengt.
u64 summe_von(const Zustand& welt)
{
    std::array<std::uint8_t, kern::zustand::BYTES> bytes{};
    kern::zustand::nach_bytes(welt, bytes);
    return kern::pruefsumme::fnv1a64(bytes);
}

/// Ein Musterwert je Adresse -- "beliebige Feldwerte" im Sinne von Bedingung 3.
///
/// Die acht Muster decken null, beide Vorzeichen, die Skala 10.000 aus `spiel.md` und
/// **beide Enden des `int64_t`** ab. Die Enden stehen bewusst drin: Eine Runde, die nur
/// vortraegt, darf an ihnen nichts rechnen, und der Sanitizer aus ADR 0011 Massnahme 2
/// saehe es, wenn doch.
i64 musterwert(Index platz)
{
    constexpr std::array<i64, 8> muster = {0,
                                           1,
                                           -1,
                                           10'000,
                                           -10'000,
                                           123'456'789,
                                           kern::festkomma::I64_MAX,
                                           kern::festkomma::I64_MIN};
    return muster[platz % muster.size()];
}

/// Baut eine Ausgangslage mit Musterwerten auf allen 310 Adressen und `partie.runde` auf
/// `rundennummer`.
///
/// **Ein einziger Startwertzugang fuer alle 310 Adressen**, und `partie.runde` zuletzt:
/// Der Riegel aus Paket 0027 greift beim Binden und nicht bei jedem `setze` -- genau
/// deshalb, weil `partie.runde` selbst zu der Menge gehoert, die eine Startbelegung
/// setzt. Ein Zugang je Aufruf haette sich nach der ersten gesetzten Rundennummer selbst
/// die Tuer zugemacht.
Zustand ausgangslage(i64 rundennummer)
{
    Zustand welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, musterwert(platz));
    }
    zugang.setze(kern::zustand::stelle_partie(PartieFeld::Runde), rundennummer);
    return welt;
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)

namespace {

// ---------------------------------------------------------------------------
// Bedingung 2 -- die Maskengroesse stimmt aus unabhaengiger Quelle
// ---------------------------------------------------------------------------
//
// Die beiden Zahlen stehen ausgeschrieben in der Tabelle von T38 samt Nachrechnung
// (108 + 22 + 40 + 2 + 3 = 175), nicht in diesem Paket. Gefragt wird `kern::schreiber`,
// also der Kasten, der die Maske fuehrt -- nicht `kern::schritt`.

void probe_maskengroesse()
{
    PRUEFE(sollmaskengroesse(Modus::Weltlauf) == 175);
    PRUEFE(sollmaskengroesse(Modus::Spielmodus) == 310);
    PRUEFE(108 + 22 + 40 + 2 + 3 == 175);
    std::printf("  Sollmaske weltlauf = %zu, spielmodus = %zu (erwartet 175 und 310)\n",
                sollmaskengroesse(Modus::Weltlauf), sollmaskengroesse(Modus::Spielmodus));
}

// ---------------------------------------------------------------------------
// Bedingung 4 -- die Kette hat 175 Glieder, und jedes ist ein Vortrag
// ---------------------------------------------------------------------------

/// Geht alle Glieder durch. Statt je Glied eine eigene Meldung zu setzen -- das waeren
/// im Fehlerfall 175 -- merkt sich die Probe **das erste** verletzte Glied je Aussage
/// und schreibt es hin. Eine Nummer ist ein Hinweis, ein Wall aus 175 Zeilen keiner.
void probe_kette(const Kette& kette, i64 erwartete_runde)
{
    PRUEFE(kette.laenge() == 175);

    constexpr std::size_t KEINS = 1000;  // liegt ausserhalb jeder moeglichen Gliednummer
    std::size_t erste_falsche_art = KEINS;
    std::size_t erste_falsche_quelle = KEINS;
    std::size_t erste_falsche_runde = KEINS;
    std::size_t erste_falsche_verzoegerung = KEINS;
    std::size_t erster_falscher_beitrag = KEINS;
    std::size_t erste_wertaenderung = KEINS;
    std::size_t erste_nicht_aufsteigende = KEINS;
    std::size_t erste_ausserhalb_maske = KEINS;

    // Das eine Glied, das seit Paket 0071 einen anderen Wert traegt als vorher. Beides
    // wird geprueft: dass es da ist, und dass es die richtigen beiden Zahlen nennt.
    bool rundenglied_gesehen = false;
    bool rundenglied_zaehlt_hoch = false;

    const Bitfeld& maske = sollmaske(Modus::Weltlauf);
    bool voriges_gibt_es = false;
    Index voriges_ziel = 0;

    for (std::size_t n = 0; n < kette.laenge(); ++n) {
        const Ursachensatz& satz = kette.eintrag(n);

        if (satz.ursache.art() != UrsacheArt::Vortrag && erste_falsche_art == KEINS) {
            erste_falsche_art = n;
        }
        // Alle 175 Glieder nennen ihre **eigene** Adresse als Herkunft. Bei den 174
        // vorgetragenen ist das die Aussage "unveraendert"; beim Glied von
        // `partie.runde` ist es die Aussage "aus dem alten Wert dieser Adresse und aus
        // nichts sonst" -- die Ursachenform nennt die Herkunft, nicht die Gleichheit.
        if (satz.ursache.art() == UrsacheArt::Vortrag
            && satz.ursache.vortragsadresse() != satz.ziel && erste_falsche_quelle == KEINS) {
            erste_falsche_quelle = n;
        }
        if (satz.runde != erwartete_runde && erste_falsche_runde == KEINS) {
            erste_falsche_runde = n;
        }
        if (satz.verzoegerung != 0 && erste_falsche_verzoegerung == KEINS) {
            erste_falsche_verzoegerung = n;
        }
        if (satz.beitrag != 1000 && erster_falscher_beitrag == KEINS) {
            erster_falscher_beitrag = n;
        }
        if (satz.ziel == PLATZ_RUNDE) {
            // Das Glied von Schritt 1: `alt` ist die Vorrundennummer, `neu` die dieser
            // Runde. Die Subtraktion ist hier gefahrlos -- `erwartete_runde` ist
            // mindestens eins, weil `schritt` eine Rundennummer kleiner eins gar nicht
            // erst erzeugt.
            rundenglied_gesehen = true;
            rundenglied_zaehlt_hoch =
                satz.alt == erwartete_runde - 1 && satz.neu == erwartete_runde;
        } else if (satz.alt != satz.neu && erste_wertaenderung == KEINS) {
            // Alle uebrigen 174 Glieder tragen vor, und ein Vortrag aendert nichts.
            erste_wertaenderung = n;
        }
        if (voriges_gibt_es && satz.ziel <= voriges_ziel && erste_nicht_aufsteigende == KEINS) {
            // "aufsteigend" schliesst "paarweise verschieden" ein: `<=` faengt beides.
            erste_nicht_aufsteigende = n;
        }
        if (!maske.steht(satz.ziel) && erste_ausserhalb_maske == KEINS) {
            erste_ausserhalb_maske = n;
        }

        voriges_ziel = satz.ziel;
        voriges_gibt_es = true;
    }

    PRUEFE(erste_falsche_art == KEINS);
    PRUEFE(erste_falsche_quelle == KEINS);
    PRUEFE(erste_falsche_runde == KEINS);
    PRUEFE(erste_falsche_verzoegerung == KEINS);
    PRUEFE(erster_falscher_beitrag == KEINS);
    PRUEFE(erste_wertaenderung == KEINS);
    PRUEFE(erste_nicht_aufsteigende == KEINS);
    PRUEFE(erste_ausserhalb_maske == KEINS);
    PRUEFE(rundenglied_gesehen);
    PRUEFE(rundenglied_zaehlt_hoch);

    // Und die Gegenrichtung: Jede Adresse der Maske kommt in der Kette vor. Zusammen mit
    // "aufsteigend, paarweise verschieden" und der Laenge 175 ist die Kette damit genau
    // die Maske -- nicht 175 beliebige Adressen, die zufaellig in ihr liegen.
    std::size_t fehlende = 0;
    std::size_t erste_fehlende = FELDER;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (!maske.steht(platz)) {
            continue;
        }
        bool gefunden = false;
        for (std::size_t n = 0; n < kette.laenge() && !gefunden; ++n) {
            gefunden = kette.eintrag(n).ziel == platz;
        }
        if (!gefunden) {
            ++fehlende;
            if (erste_fehlende == FELDER) {
                erste_fehlende = platz;
            }
        }
    }
    PRUEFE(fehlende == 0);
    if (fehlende != 0) {
        std::fprintf(stderr, "  erste fehlende Maskenadresse: %zu (%s)\n", erste_fehlende,
                     kern::zustand::index_zu_adresse(erste_fehlende));
    }
}

// ---------------------------------------------------------------------------
// Bedingungen 3, 4 und 6 -- eine Runde laeuft durch, und genau ein Feld bewegt sich
// ---------------------------------------------------------------------------

/// Laesst eine Runde laufen und gibt den entstandenen Zustand zurueck.
Zustand probe_eine_runde(i64 vorrundennummer)
{
    const Zustand vorher = ausgangslage(vorrundennummer);
    const u64 summe_vorher = summe_von(vorher);
    const i64 diese_runde = vorrundennummer + 1;

    // Bedingung 3: kehrt zurueck, ohne abzubrechen. Der Aufruf selbst ist der Nachweis,
    // dass die Rundenendpruefung aus T38 gehalten hat.
    const Rundenergebnis ergebnis = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    // Bedingung 6 in der Fassung von Paket 0071: **genau eine** der 310 Groessen aendert
    // sich, und es ist `partie.runde`. Gezaehlt wird ueber alle 310, nicht an der einen
    // erwarteten Stelle nachgesehen -- sonst pruefte die Zeile, was sie annimmt.
    std::size_t geaenderte = 0;
    Index erste_geaenderte = FELDER;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (vorher.lies(platz) != nachher.lies(platz)) {
            ++geaenderte;
            if (erste_geaenderte == FELDER) {
                erste_geaenderte = platz;
            }
        }
    }
    PRUEFE(geaenderte == 1);
    PRUEFE(erste_geaenderte == PLATZ_RUNDE);
    PRUEFE(vorher.lies(PLATZ_RUNDE) == vorrundennummer);
    PRUEFE(nachher.lies(PLATZ_RUNDE) == diese_runde);
    if (geaenderte != 1) {
        std::fprintf(stderr, "  %zu Groessen geaendert, erste: %zu (%s)\n", geaenderte,
                     erste_geaenderte,
                     erste_geaenderte < FELDER ? kern::zustand::index_zu_adresse(erste_geaenderte)
                                               : "keine");
    }

    // Der unabhaengige Erwartungswert: dieselbe Ausgangslage, nur mit der Rundennummer
    // dieser Runde. Sie entsteht ueber `zustand::Startbelegung` und weiss von
    // `kern::schritt` nichts -- damit haengt die Aussage nicht an derselben Rechnung,
    // die sie pruefen soll.
    const Zustand erwartet = ausgangslage(diese_runde);
    PRUEFE(nachher == erwartet);

    // Die Pruefsumme faellt jetzt, und das ist die widerrufene Bedingung 6 von 0033.
    // Beide Zahlen stehen darunter im Wortlaut; ohne sie waere der Widerruf ein stiller.
    const u64 summe_nachher = summe_von(nachher);
    PRUEFE(summe_vorher != summe_nachher);
    PRUEFE(summe_nachher == summe_von(erwartet));
    // Zwei Wege zu jeder der beiden Zahlen, damit keine an einer einzigen Rechnung haengt.
    PRUEFE(summe_vorher == kern::zustand::pruefsumme_von(vorher));
    PRUEFE(summe_nachher == kern::zustand::pruefsumme_von(nachher));

    std::printf("  Vorrunde %lld -> Runde %lld: Pruefsumme %016llx vorher, %016llx nachher; "
                "%zu von 310 Groessen geaendert (%s)\n",
                static_cast<long long>(vorrundennummer), static_cast<long long>(diese_runde),
                static_cast<unsigned long long>(summe_vorher),
                static_cast<unsigned long long>(summe_nachher), geaenderte,
                kern::zustand::index_zu_adresse(PLATZ_RUNDE));

    probe_kette(ergebnis.kette_dieser_runde, diese_runde);
    std::printf("  Kette: %zu Glieder (erwartet 175), Runde %lld an jedem Glied\n",
                ergebnis.kette_dieser_runde.laenge(), static_cast<long long>(diese_runde));

    return nachher;
}

void probe_runden()
{
    // Runde 1 auf einem Startzustand des Jahrgangs.
    static_cast<void>(probe_eine_runde(0));

    // Und am oberen Ende des Zaehlbaren: die letzte Runde, die sich noch zaehlen laesst.
    const Zustand am_ende = probe_eine_runde(kern::festkomma::I64_MAX - 1);

    // Der Randfall, den Paket 0071 aus dem Vortrag geerbt hat. Solange die Runde die
    // Nummer vortrug, lief dieser Zustand beliebig oft weiter -- er trug nach der Runde
    // dieselbe Zahl wie davor. Jetzt traegt er `I64_MAX`, und die naechste Runde bricht
    // am vorhandenen Riegel ab. Das ist der Unterschied, um den es dem Paket geht: Der
    // Abbruch kommt **aus dem Zustand**, nicht aus einer Zahl, die die Probe von Hand
    // hineingeschrieben hat.
    PRUEFE(am_ende.lies(PLATZ_RUNDE) == kern::festkomma::I64_MAX);
    bool geworfen = false;
    try {
        static_cast<void>(kern::schritt::schritt(am_ende, {}, Modus::Weltlauf));
    } catch (const std::domain_error& fehler) {
        geworfen = true;
        std::printf("  Abbruch wie erwartet (Runde nach der letzten zaehlbaren): %s\n",
                    fehler.what());
    }
    PRUEFE(geworfen);
}

// ---------------------------------------------------------------------------
// Paket 0071 -- zwei aufeinanderfolgende Runden, und der Startwertzugang schliesst
// ---------------------------------------------------------------------------
//
// Zwei Aussagen in einer Probe, weil sie an derselben Zahl haengen:
//
//   1. `partie.runde` zaehlt ueber zwei Runden 0 auf 1 auf 2 -- nicht nur einmal um eins.
//   2. Bedingung 3 des Arbeitspakets 0027, zurueckgeholt: Ein Zugang, der vor der ersten
//      Runde gebunden wurde, bricht danach beim naechsten Schreibzugriff ab, und ein
//      neuer laesst sich gar nicht mehr binden. Bis zu diesem Paket galt beides nur
//      gegen eine von Hand gesetzte Rundennummer und nicht gegen die Runde des Kerns.
//
// Der Zustand wird zwischen den Runden **in dieselbe Veraenderliche** zurueckgeschrieben.
// Genau so wuerde eine Rundenschleife es tun, und genau darauf zielt der Riegel: Der
// Zugang zeigt weiter auf diesen Zustand, seine naechste Setzung waere eine Aenderung
// ohne Ursachensatz.

void probe_zwei_runden_und_startwertriegel()
{
    Zustand welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, musterwert(platz));
    }
    zugang.setze(PLATZ_RUNDE, 0);

    // Die Positivkontrolle, und sie steht vor den beiden Abbruechen unten: Der Zugang
    // **hat** geschrieben. Ohne sie zeigten die Abbrueche auch dann dasselbe Bild, wenn
    // er von Anfang an wirkungslos gewesen waere.
    PRUEFE(welt.lies(PLATZ_RUNDE) == 0);
    PRUEFE(welt.lies(0) == musterwert(0));
    PRUEFE(welt.lies(FELDER - 1) == musterwert(FELDER - 1));
    PRUEFE(kern::zustand::vor_der_ersten_runde(welt));

    const Rundenergebnis erste = kern::schritt::schritt(welt, {}, Modus::Weltlauf);
    welt = erste.neuer_zustand;
    PRUEFE(welt.lies(PLATZ_RUNDE) == 1);

    const Rundenergebnis zweite = kern::schritt::schritt(welt, {}, Modus::Weltlauf);
    welt = zweite.neuer_zustand;
    PRUEFE(welt.lies(PLATZ_RUNDE) == 2);

    // Und die Kette sagt dasselbe von der anderen Seite.
    probe_kette(erste.kette_dieser_runde, 1);
    probe_kette(zweite.kette_dieser_runde, 2);

    std::printf("  partie.runde ueber zwei Runden: 0 -> %lld -> %lld\n",
                static_cast<long long>(erste.neuer_zustand.lies(PLATZ_RUNDE)),
                static_cast<long long>(welt.lies(PLATZ_RUNDE)));

    PRUEFE(!kern::zustand::vor_der_ersten_runde(welt));

    // Haelfte 1: der alte Zugang bricht beim naechsten Schreibzugriff ab.
    const i64 vorher_an_null = welt.lies(0);
    bool alter_zugang_bricht_ab = false;
    try {
        zugang.setze(0, 4711);
    } catch (const std::domain_error& fehler) {
        alter_zugang_bricht_ab = true;
        std::printf("  Abbruch wie erwartet (Zugang von vor Runde 1): %s\n", fehler.what());
    }
    PRUEFE(alter_zugang_bricht_ab);
    // Ein Abbruch, der vorher noch schreibt, waere keiner.
    PRUEFE(welt.lies(0) == vorher_an_null);

    // Haelfte 2: ein neuer Zugang bindet nicht mehr.
    bool neuer_zugang_bindet_nicht = false;
    try {
        Startbelegung neuer{welt};
        static_cast<void>(neuer);
    } catch (const std::domain_error& fehler) {
        neuer_zugang_bindet_nicht = true;
        std::printf("  Abbruch wie erwartet (neuer Zugang nach der Runde): %s\n", fehler.what());
    }
    PRUEFE(neuer_zugang_bindet_nicht);
}

// ---------------------------------------------------------------------------
// T10 -- gleiches Ergebnis bei jedem Lauf
// ---------------------------------------------------------------------------
//
// `schritt` ist eine reine Funktion ohne gezogene Zahlen. Zwei Aufrufe auf derselben
// Ausgangslage muessen deshalb bis auf das letzte Kettenglied dasselbe liefern. Das ist
// heute billig zu haben und wird teuer, sobald ein Schritt rechnet -- die Probe steht
// hier, damit sie dann schon da ist.

void probe_zweimal_dasselbe()
{
    const Zustand vorher = ausgangslage(7);

    const Rundenergebnis erster = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);
    const Rundenergebnis zweiter = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);

    PRUEFE(erster.neuer_zustand == zweiter.neuer_zustand);
    PRUEFE(erster.kette_dieser_runde.laenge() == zweiter.kette_dieser_runde.laenge());

    std::size_t erstes_abweichendes = 1000;
    for (std::size_t n = 0; n < erster.kette_dieser_runde.laenge(); ++n) {
        if (!(erster.kette_dieser_runde.eintrag(n) == zweiter.kette_dieser_runde.eintrag(n))
            && erstes_abweichendes == 1000) {
            erstes_abweichendes = n;
        }
    }
    PRUEFE(erstes_abweichendes == 1000);
}

// ---------------------------------------------------------------------------
// Bedingung 7 -- der spielmodus bricht ab, und die Meldung sagt warum
// ---------------------------------------------------------------------------

void probe_spielmodus_bricht_ab()
{
    const Zustand welt = ausgangslage(3);

    bool geworfen = false;
    bool nennt_alle_310 = false;
    bool nennt_den_modus = false;
    bool nennt_die_fehlenden_pakete = false;

    try {
        static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Spielmodus));
    } catch (const std::domain_error& fehler) {
        geworfen = true;
        std::fprintf(stdout, "  Abbruch wie erwartet: %s\n", fehler.what());
        nennt_alle_310 = enthaelt(fehler.what(), "310");
        nennt_den_modus = enthaelt(fehler.what(), "spielmodus");
        nennt_die_fehlenden_pakete = enthaelt(fehler.what(), "kein Paket");
    }

    PRUEFE(geworfen);
    PRUEFE(nennt_alle_310);
    PRUEFE(nennt_den_modus);
    PRUEFE(nennt_die_fehlenden_pakete);
}

// ---------------------------------------------------------------------------
// Die Rundennummer -- die beiden Enden sterben, statt still weiterzuzaehlen
// ---------------------------------------------------------------------------
//
// Die Nummer dieser Runde ist `partie.runde` der Vorrunde plus eins. Beide Enden sind
// harte Fehler: Eine Runde vor der ersten gibt es nicht, und `I64_MAX + 1` waere mit
// `-fwrapv` ein Umbruch ins Negative -- also eine Rundennummer, die der `Schreiber`
// abwiese, mit einer Meldung, die die Ursache nicht mehr nennt.

void probe_rundennummer()
{
    for (const i64 nummer : {i64{-1}, kern::festkomma::I64_MIN, kern::festkomma::I64_MAX}) {
        const Zustand welt = ausgangslage(nummer);
        bool geworfen = false;
        try {
            static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Weltlauf));
        } catch (const std::domain_error& fehler) {
            geworfen = true;
            std::fprintf(stdout, "  Abbruch wie erwartet (partie.runde = %lld): %s\n",
                         static_cast<long long>(nummer), fehler.what());
        }
        pruefe(geworfen, "partie.runde ausserhalb des Zaehlbaren bricht ab", __LINE__);
    }
}

}  // namespace

int main()
{
    probe_maskengroesse();
    probe_runden();
    probe_zwei_runden_und_startwertriegel();
    probe_zweimal_dasselbe();
    probe_spielmodus_bricht_ab();
    probe_rundennummer();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("schritt_probe: alle Pruefungen bestanden\n");
    return 0;
}
