//! Laufende Probe fuer `kern::schritt` -- die acht Bedingungen des Arbeitspakets 0033,
//! **Bedingung 6 in der Fassung von Paket 0071**.
//!
//! Bedingung 6 von 0033 verlangte die *unveraenderte* Pruefsumme ueber eine Runde. Sie
//! ist widerrufen -- 0033 hatte sie als "auf Widerruf" ausgewiesen --, und an ihrer
//! Stelle stand die schaerfere Aussage: genau eine der 310 Groessen aendert sich,
//! naemlich `partie.runde`. Was die alte Fassung nicht leisten konnte, ist der Grund
//! des Widerrufs: Ein Zustand, den eine vollstaendige Runde Feld fuer Feld unveraendert
//! laesst, ist von "keine Runde gelaufen" durch keinen Vergleich zu unterscheiden.
//!
//! **Auch die Zahl eins ist seit Paket 0197 gefallen, und diesmal nicht durch einen
//! Widerruf, sondern durch eine Rechnung.** Schritt 5 hat einen Rumpf; wie viele der 310
//! Groessen eine Runde bewegt, haengt jetzt am Zustand. Diese Probe zaehlt sie deshalb
//! nicht mehr gegen eine hingeschriebene Ziffer, sondern gegen einen **unabhaengig
//! gebauten Erwartungszustand** -- die Zahl wird ausgedruckt und nicht behauptet.
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
//!      Seit Paket 0085 fragt **jede** dieser Stellen nicht nur, *dass* geworfen wurde,
//!      sondern *welcher Riegel* -- an Textstuecken der Meldung, die ihn eindeutig
//!      machen. Der Grund ist die doppelt gehaltene Schranke: Faellt der Riegel in
//!      `kern/src/schritt.cpp` weg, bricht der `Schreiber` die Runde weiterhin ab, nur
//!      mit einer Meldung, die die Ursache nicht mehr nennt. Ein blosses "es hat
//!      geworfen" bliebe dabei gruen. Beim `spielmodus` kommt Bedingung 7 dazu: Die
//!      Meldung muss sagen, warum.
//!   2a. **Dass die Kennzeichen kennzeichnen** (Paket 0107). Dass ein Textstueck seinen
//!      Riegel eindeutig macht, war bis dahin eine Lesung -- ein Mensch hat es beim
//!      Hinschreiben entschieden, und nichts hat die Entscheidung nachgehalten. Wer eine
//!      Liste auf ein Allerweltsstueck verkuerzt, bekam von der Werkzeugkette gruenes
//!      Licht. Seither ist es eine Messung: Alle Abbruchstellen legen ihre angekommene
//!      Meldung nebeneinander, und jede Liste muss auf **jede** Meldung ihres eigenen
//!      Riegels passen und auf **keine** eines fremden. Beide Haelften werden gebraucht;
//!      die erste schliesst den Ausweg, einen fremden Riegel einfach zum eigenen zu
//!      erklaeren. Verglichen werden nur Dinge, die im selben Lauf entstehen -- kein
//!      Wortlaut wandert in diese Datei, die Warnung gegen den Volltextvergleich bleibt.
//!   2b. **Und die Riegel, die kein Zustand erreicht** (Paket 0248). Beide Haelften von 2a
//!      setzen eine angekommene Meldung voraus; eine Schranke, vor die kein Zustand kommt,
//!      liefert nie eine. Sie steht deshalb in einem zweiten Verzeichnis mit eigenem Typ,
//!      ist von der Vollzaehligkeit ausgenommen und behaelt die erste Haelfte -- ihre Liste
//!      darf auf keine fremde Meldung passen. Die zweite ist nicht zu haben; was das
//!      kostet, steht am Aufzaehlungstyp und wird in jedem Lauf mitgedruckt.
//!   2c. **Der Apparat gehoert seit Paket 0244 nicht mehr dieser Datei.** Er steht in
//!      `kern/test/kennzeichen.hpp` und wird von `werte_probe` mit einer eigenen
//!      Riegelaufzaehlung genauso benutzt. Was hier steht, sind die beiden Aufzaehlungen,
//!      die Namen, die Kennzeichenlisten und die Aufrufstellen -- was dort steht, ist die
//!      Mechanik und die Begruendung beider Haelften.
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
//! Probe dazu beitragen kann, ist die Gegenrichtung: Sie ruft `schritt` mit genau vier
//! Argumenten (Zustand, Buendel, Parametersatz, Modus) und bekommt beides zurueck,
//! Zustand und Kette.
//!
//! **Das vierte Argument gibt es seit Paket 0229**, in der Form aus T10b:
//! `schritt(vorrunde, aktionen, konstanten, modus)` mit `konstanten` als
//! `const kern::werte::Konstanten&`. Mit ihm kommt eine Schranke, die **jede**
//! Ausgangslage dieser Datei betrifft: Die Runde bildet die Pruefsumme ueber die
//! Schluesselfelder des Traegers und haelt sie gegen `partie.parameter_pruefsumme`.
//! Deshalb bekommt diese eine Adresse in `ausgangslage` nicht mehr ihren Musterwert,
//! sondern die Zahl, die zum Traeger dieser Probe gehoert -- ein Musterwert dort liesse
//! jede Runde dieser Datei an der Schranke sterben.
//!
//! Geprueft wird die Schranke zweiseitig: Die passende Paarung laeuft durch -- das tut
//! sie in jeder Probe dieser Datei --, die unpassende bricht ab und nennt beide Zahlen.
//! Dazu die Feldprobe, ohne die die Summe eine Zahl waere, die niemand nachrechnet:
//! Jedes der sieben Schluesselfelder bewegt sie, und die beiden Jahrgangsgroessen
//! bewegen sie nicht.
//!
//! **Und die Feldzahl selbst**, seit dem zweiten Lauf desselben Pakets. Die Feldprobe
//! faengt ein vergessenes Feld, nie ein neues; dagegen steht drueben ein
//! `static_assert` auf der Zahl der Felder des Traegers. Was er wert ist, haengt daran,
//! dass sein Zaehler wirklich zaehlt, und das ist keine Frage an den Traeger, sondern
//! an eigens gebaute Verbunde mit bekannter und verschiedener Feldzahl. Sie stehen
//! unten, jeder mit seiner ausgeschriebenen Zahl. **Seit Paket 0233 steht daneben
//! derselbe Zaehler ohne die Klammern je Stelle**: Was die Klammern verhindern, war bis
//! dahin eine Behauptung in zwei Kommentaren, und sie traf auf den Verbund nicht zu, den
//! sie nannte.
//!
//! **Paket 0197 -- die Zustimmung wird gerechnet.** Drei Stellen dieser Datei haengen
//! daran, und sie sagen Verschiedenes:
//!
//!   * Die Kettenprobe **zieht die Aussage ueber die aufsteigende Kette nach**, die
//!     `include/kern/schritt.hpp` "auf Widerruf" ausgewiesen hat. Die Kette steigt nicht
//!     mehr durchgehend auf: 171 Glieder aufsteigend und mit der Ursache `Vortrag`, dann
//!     die vier Zustimmungen mit der Ursache `Gegenkraft`, ebenfalls aufsteigend. Beide
//!     Haelften werden geprueft, und die zweite bricht ein Vortragen auf.
//!   * Eine Probe misst die zwei Zahlen, an denen die Regel haengt -- den bewegten
//!     Instrumentenschritt und die Adressordnung, die Schritt 5 aus der aufsteigenden
//!     Runde heraushaelt. Sie braucht den Koeffizienten nicht und ist deshalb auch dann
//!     falsifizierbar, wenn er auf null steht.
//!   * Eine Probe **unterscheidet den gerechneten Rumpf vom vortragenden.** Sie startet
//!     mit vier Zustimmungswerten ausserhalb des Wertebereichs der Klasse 4; ein Vortrag
//!     liesse alle vier stehen, die Regel klemmt alle vier auf ihre Schranke. Vier gegen
//!     null, je Adresse mit Start- und Endwert ausgedruckt.
//!
//! **Paket 0237 -- der Nenner der Regel, und er aendert jede Ausgangslage.** Die
//! Zustimmungsregel teilt durch das Bruttoinlandsprodukt, und `spiel.md` verlangt dafuer
//! einen Nenner ueber null. Unter der reinen Musterbelegung war er in allen vier Laendern
//! negativ; jede Runde dieser Datei hat also bis dahin auf einem Zustand gemessen, den
//! der Entwurf verbietet, und blieb nur deshalb gruen, weil der Zaehler null war. Seither
//! tragen die zwoelf Wertschoepfungsadressen einen positiven Wert -- `startwert` statt
//! `musterwert` --, und eine eigene Probe haelt die Schranke von beiden Seiten.
//!
//! **Paket 0240 -- die Klemme steht hinter der Summe, und der Verdacht bleibt einer.** Die
//! Regel addiert, ehe sie klemmt, und die Addition bricht bei Ueberlauf ab. Diese Datei
//! kann den Fall durch die Runde nicht herstellen, und das ist gemessen statt vermutet:
//! Der additive Term ist ein Produkt mit `zustimmung_elastizitaet`, und die steht in jedem
//! Traeger dieser Datei auf null -- ein Hub ungleich null aendert daran nichts. Gemessen
//! wird beides: dass der Koeffizient keine der 310 Adressen ausser der Parametersumme
//! bewegt, und was aus den vier Ausgangswerten mit einem Term ungleich null wuerde. Der
//! zweite Teil laeuft an `festkomma::plus` und nicht durch die Runde; warum, steht bei der
//! Probe.
//!
//! **Paket 0284 -- Schritt 3 schreibt den Pfadstand, und diese Datei fuehrt seither zwei
//! Traeger.** Der Schritt setzt je spielbarem Land den Stand der drei pfadgestuetzten
//! Instrumente aus `Konstanten::pfadstand`, statt ihn vorzutragen; das vierte, die
//! Regulierung, traegt er weiter vor. Der Traeger dieser Datei fuehrt auf jenen zwoelf
//! Adressen genau den Musterwert, den die Ausgangslage dort schon hat -- damit bewegt
//! keine der aelteren Proben einen Stand, und jede ihrer Zahlen bleibt die, die sie war.
//! Der Grund steht bei `pfadstand_der_probe` und ist gemessen: Ein Pfadstand von null
//! bewegte sechs Staende, und `politiklast` liefe damit in eine Zinszeile, deren
//! Schuldenquote in der Musterlage der kleinste `int64_t` ist. Dass Schritt 3 wirklich
//! **schreibt**, haengt deshalb an zwei Stellen -- an der Ursache `Jahrgang` der zwoelf
//! Kettenglieder und an `probe_pfadstand_geht_in_die_runde`, die mit einem zweiten
//! Traeger faehrt und rot wird, sobald der Rumpf wieder vortraegt.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <span>
#include <stdexcept>
#include <utility>

#include "kern/festkomma.hpp"
#include "kern/pruefsumme.hpp"
#include "kern/schreiber.hpp"
#include "kern/schritt.hpp"
#include "kern/werte.hpp"
#include "kern/zustand.hpp"

#include "kennzeichen.hpp"

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

/// Der Platz von `partie.runde` -- die Adresse, die **jede** Runde aendert, seit
/// Paket 0071 sie setzt statt sie vorzutragen. Die einzige war sie bis Paket 0197.
/// Aus der Adressrechnung geholt und nicht als 306 hingeschrieben: Verschoebe
/// ein spaeteres Paket den Partieblock, prueft diese Datei weiter das richtige Feld.
constexpr Index PLATZ_RUNDE = kern::zustand::stelle_partie(PartieFeld::Runde);

/// Der Platz der Parameterpruefsumme -- die zweite Adresse, die diese Datei beim Namen
/// kennen muss, seit die Runde sie gegen den Traeger haelt (T10b).
constexpr Index PLATZ_PARAMETERSUMME =
    kern::zustand::stelle_partie(PartieFeld::ParameterPruefsumme);

/// Die vier spielbaren Laender, in der Reihenfolge aus T15.
constexpr std::array<kern::zustand::Gebiet, kern::zustand::LAENDER> LAENDER_DER_PROBE = {
    kern::zustand::Gebiet::US, kern::zustand::Gebiet::CN, kern::zustand::Gebiet::DE,
    kern::zustand::Gebiet::BR};

/// Die vier Instrumente, in der Reihenfolge aus T15.
constexpr std::array<kern::zustand::Instrument, kern::zustand::INSTRUMENTE>
    INSTRUMENTE_DER_PROBE = {
        kern::zustand::Instrument::Leitzins, kern::zustand::Instrument::Zoll,
        kern::zustand::Instrument::Haushalt, kern::zustand::Instrument::Regulierung};

/// Die drei Sektoren, in der Reihenfolge aus T15.
constexpr std::array<kern::zustand::Sektor, kern::zustand::SEKTOREN> SEKTOREN_DER_PROBE = {
    kern::zustand::Sektor::Landwirtschaft, kern::zustand::Sektor::Industrie,
    kern::zustand::Sektor::Dienstleistungen};

/// Die zwoelf Wertschoepfungsadressen der vier spielbaren Laender -- die Summanden, aus
/// denen `kern::werte::bip` das Bruttoinlandsprodukt eines Landes bildet.
///
/// Gerechnet und nicht hingeschrieben, aus demselben Grund wie bei `PLATZ_RUNDE`: Ein
/// Paket, das den Laenderblock verschoebe, traefe hier weiter dieselben Groessen.
constexpr std::array<Index, kern::zustand::LAENDER * kern::zustand::SEKTOREN>
wertschoepfungsplaetze()
{
    std::array<Index, kern::zustand::LAENDER * kern::zustand::SEKTOREN> plaetze{};
    std::size_t n = 0;
    for (const kern::zustand::Gebiet land : LAENDER_DER_PROBE) {
        for (const kern::zustand::Sektor sektor : SEKTOREN_DER_PROBE) {
            plaetze[n] = kern::zustand::stelle_sektorgroesse(
                land, sektor, kern::zustand::SektorGroesse::Wertschoepfung);
            ++n;
        }
    }
    return plaetze;
}

constexpr std::array<Index, kern::zustand::LAENDER * kern::zustand::SEKTOREN>
    WERTSCHOEPFUNGSPLAETZE = wertschoepfungsplaetze();

/// Die vier Zustimmungsadressen, in der Laenderreihenfolge -- gerechnet und nicht
/// hingeschrieben, aus demselben Grund wie bei `PLATZ_RUNDE`.
constexpr std::array<Index, kern::zustand::LAENDER> zustimmungsplaetze()
{
    std::array<Index, kern::zustand::LAENDER> plaetze{};
    for (std::size_t n = 0; n < LAENDER_DER_PROBE.size(); ++n) {
        plaetze[n] = kern::zustand::stelle_politisch(
            LAENDER_DER_PROBE[n], kern::zustand::PolitischeGroesse::Zustimmung);
    }
    return plaetze;
}

constexpr std::array<Index, kern::zustand::LAENDER> ZUSTIMMUNGSPLAETZE = zustimmungsplaetze();

/// Die zwoelf Adressen, die Schritt 3 seit Paket 0284 **setzt** statt sie vorzutragen:
/// je spielbarem Land der Stand der drei pfadgestuetzten Instrumente.
///
/// Gerechnet aus derselben Doppelschleife, aus der `kern::schritt` sie schreibt, und
/// nicht als Zahlenliste hingeschrieben -- aus demselben Grund wie bei `PLATZ_RUNDE`:
/// Ein Paket, das den Laenderblock verschoebe, traefe hier weiter dieselben Groessen.
/// Die Regulierung steht nicht darunter; ihr Stand hat keine Reihe (T61) und wird
/// vorgetragen.
constexpr std::array<Index, kern::zustand::LAENDER * kern::zustand::PFADINSTRUMENTE>
pfadstandsplaetze()
{
    std::array<Index, kern::zustand::LAENDER * kern::zustand::PFADINSTRUMENTE> plaetze{};
    std::size_t n = 0;
    for (const kern::zustand::Gebiet land : LAENDER_DER_PROBE) {
        for (std::size_t i = 0; i < kern::zustand::PFADINSTRUMENTE; ++i) {
            plaetze[n] = kern::zustand::stelle_instrument(land, INSTRUMENTE_DER_PROBE[i],
                                                          kern::zustand::InstrumentFeld::Stand);
            ++n;
        }
    }
    return plaetze;
}

constexpr std::array<Index, kern::zustand::LAENDER * kern::zustand::PFADINSTRUMENTE>
    PFADSTANDSPLAETZE = pfadstandsplaetze();

static_assert(PFADSTANDSPLAETZE.size() == 12,
              "vier spielbare Laender mal drei pfadgestuetzten Instrumenten");

/// Ob `platz` einer der zwoelf ist.
constexpr bool ist_pfadstand(Index platz)
{
    for (const Index eine : PFADSTANDSPLAETZE) {
        if (eine == platz) {
            return true;
        }
    }
    return false;
}

/// Ob `platz` eine der vier Zustimmungsadressen ist -- gebraucht, wo eine Zaehlung ueber
/// alle 310 die Adressen ausnehmen muss, die Schritt 5 schreibt.
constexpr bool ist_zustimmung(Index platz)
{
    for (const Index eine : ZUSTIMMUNGSPLAETZE) {
        if (eine == platz) {
            return true;
        }
    }
    return false;
}

// Die Regulierung gehoert nicht dazu, und das steht als Zusicherung da und nicht als
// Absicht: Faende ein spaeteres Paket sie hier, waere die Halbseite von `probe_kette`
// -- der vierte Stand traegt vor -- still leer.
static_assert(!ist_pfadstand(kern::zustand::stelle_instrument(
                  kern::zustand::Gebiet::US, kern::zustand::Instrument::Regulierung,
                  kern::zustand::InstrumentFeld::Stand)),
              "der vierte Instrumentenstand hat keine Reihe des Jahrgangs (T61)");

/// Dass die vier untereinander aufsteigen, traegt die Kettenprobe weiter unten: Sie
/// verlangt die vier Schlussglieder in genau dieser Reihenfolge. Gerechnet statt
/// angenommen, damit ein verschobener Laenderblock hier auffaellt und nicht dort.
constexpr bool zustimmungsplaetze_steigen()
{
    for (std::size_t n = 1; n < ZUSTIMMUNGSPLAETZE.size(); ++n) {
        if (ZUSTIMMUNGSPLAETZE[n] <= ZUSTIMMUNGSPLAETZE[n - 1]) {
            return false;
        }
    }
    return true;
}

static_assert(zustimmungsplaetze_steigen(),
              "T15: die vier Laenderbloecke liegen aufsteigend, also auch ihre Zustimmungen");

/// Die obere Schranke der Zustimmungsregel -- T5 Klasse 4, hundert Prozent.
constexpr i64 ZUSTIMMUNG_OBEN = 10'000;

/// Vier Ausgangswerte der Zustimmung, alle ausserhalb von null bis 10.000, und die
/// Schranke daneben, auf der die Regel jeden von ihnen abliefert.
///
/// **Ausgeschrieben statt gerechnet:** Eine Erwartung, die aus derselben Klemme entsteht
/// wie das Gepruefte, prueft nichts.
///
/// Sie stehen seit Paket 0240 hier statt in einer Probe, weil zwei sie brauchen: Paket
/// 0197 misst an ihnen den gerechneten Rumpf gegen den vortragenden, Paket 0240 misst an
/// denselben vier Zahlen, was aus ihnen wuerde, wenn der additive Term nicht null waere.
/// Zwei Abschriften waeren zwei Stellen, die auseinanderlaufen -- und die Aussage des
/// zweiten Pakets haengt daran, dass es dieselben vier Werte sind.
constexpr std::array<i64, kern::zustand::LAENDER> ZUSTIMMUNG_AUSSERHALB = {
    {10'001, i64{-1}, kern::festkomma::I64_MAX, kern::festkomma::I64_MIN}};
constexpr std::array<i64, kern::zustand::LAENDER> ZUSTIMMUNG_SCHRANKE = {
    {10'000, i64{0}, 10'000, i64{0}}};

/// `min(10.000, max(0, wert))` -- die beiden Schranken der Regel, hier ein zweites Mal
/// und ohne den Kern.
///
/// **Sie sind nicht die ganze Regel, sondern ihr Rest, wenn der additive Term null ist.**
/// Das ist er in jeder Runde dieser Datei, und zwar aus zwei Gruenden, die beide in
/// `spiel.md` stehen: Bewegt sich kein Instrumentenstand, ist jedes Vorzeichen der
/// Politiklast null, also die Last null, also der Realeinkommenshub null; und
/// `zustimmung_elastizitaet` steht im Traeger dieser Probe ohnehin auf null. Wo diese
/// Voraussetzung gilt, ist die Klemme der vollstaendige Erwartungswert.
///
/// **Der erste der beiden Gruende hat sich mit Paket 0284 verschoben, der zweite nicht.**
/// Bis dahin bewegte sich kein Instrumentenstand, weil `schritt_3_politik` vortrug; seither
/// bewegt er sich nicht, weil der Traeger dieser Probe auf jeder der zwoelf pfadgestuetzten
/// Adressen genau den Wert fuehrt, den die Ausgangslage dort schon hat
/// (`pfadstand_der_probe`). Der zweite Grund -- der Koeffizient auf null -- traegt die
/// Aussage ohnehin allein, und deshalb gilt sie auch in `probe_pfadstand_geht_in_die_runde`,
/// wo ein Stand sich sehr wohl bewegt.
i64 geklemmt(i64 wert)
{
    if (wert < 0) {
        return 0;
    }
    return wert > ZUSTIMMUNG_OBEN ? ZUSTIMMUNG_OBEN : wert;
}

/// Ein Musterwert je Adresse -- "beliebige Feldwerte" im Sinne von Bedingung 3.
///
/// Die acht Muster decken null, beide Vorzeichen, die Skala 10.000 aus `spiel.md` und
/// **beide Enden des `int64_t`** ab. Die Enden stehen bewusst drin: Eine Runde, die nur
/// vortraegt, darf an ihnen nichts rechnen, und der Sanitizer aus ADR 0011 Massnahme 2
/// saehe es, wenn doch.
///
/// Was davon wirklich in einer Ausgangslage steht, sagt `startwert` weiter unten: Seit
/// Paket 0237 tragen zwoelf der 310 Adressen einen anderen Wert.
///
/// **Sie steht seit Paket 0284 hier oben und ist `constexpr`**, weil der Parametersatz
/// unter ihr sie braucht: Sein Pfadstand ist genau der Musterwert der Adressen, die
/// Schritt 3 damit beschreibt, und eine zweite Abschrift der acht Muster waeren zwei
/// Stellen, die auseinanderlaufen.
constexpr i64 musterwert(Index platz)
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

/// Der Pfadstand des Parametersatzes unten: je spielbarem Land und je pfadgestuetztem
/// Instrument **genau der Musterwert, den die Ausgangslage auf dieselbe Adresse legt**.
///
/// **Das ist die tragende Wahl dieser Datei zu Paket 0284, und sie ist eine Entscheidung
/// gegen den bequemeren Weg.** Seit Schritt 3 den Pfadstand schreibt, setzt er in jeder
/// Runde zwoelf Adressen auf den Wert aus dem Traeger. Ein voreingestellter Traeger legte
/// dort null -- und weil die Musterlage auf sechs dieser zwoelf Adressen `-10.000` traegt,
/// bewegten sich sechs Instrumentenstaende in **jeder** Runde dieser Datei. Was daran
/// haengt, ist nicht die Kette, sondern Schritt 5: `politiklast` ruft fuer jedes bewegte
/// Instrument `kern::werte::schaden`, und dessen Zinszeile rechnet `schuld(l)` --
/// `mal_geteilt(bip(l), staatsschuld(l), 10.000)` -- auf einer Lage, deren
/// Staatsschuldquote bei zwei der vier Laender der kleinste `int64_t` ist. Das bricht ab,
/// und zwar in `kern::festkomma` und nicht an einer Schranke, die diese Datei prueft.
///
/// **Der Pfadstand aus dem Musterwert loest das, ohne eine Messung aufzugeben.** Er
/// bewegt keine Adresse, also bleibt jede Zaehlung dieser Datei die, die sie war, und die
/// Aussage "ohne Instrumentenschritt ist die Zustimmung die Klemme ihres Ausgangswertes"
/// wird weiter an einer Runde gemessen, in der wirklich kein Stand springt. Dass Schritt
/// 3 den Wert **setzt** statt ihn vorzutragen, sieht man ihm trotzdem an: an der Ursache
/// jedes der zwoelf Kettenglieder, die `probe_kette` einzeln festnagelt. Und der Fall, in
/// dem der Traeger etwas anderes fuehrt als die Adresse, steht als eigene Probe da --
/// `probe_pfadstand_geht_in_die_runde` mit ihrem eigenen Traeger.
constexpr std::array<std::array<i64, kern::zustand::PFADINSTRUMENTE>, kern::zustand::LAENDER>
pfadstand_der_probe()
{
    std::array<std::array<i64, kern::zustand::PFADINSTRUMENTE>, kern::zustand::LAENDER> stand{};
    for (std::size_t l = 0; l < LAENDER_DER_PROBE.size(); ++l) {
        for (std::size_t i = 0; i < kern::zustand::PFADINSTRUMENTE; ++i) {
            stand[l][i] = musterwert(kern::zustand::stelle_instrument(
                LAENDER_DER_PROBE[l], INSTRUMENTE_DER_PROBE[i],
                kern::zustand::InstrumentFeld::Stand));
        }
    }
    return stand;
}

/// Der Parametersatz, mit dem diese Probe jede Runde faehrt -- alle Schluesselfelder und
/// beide bestaendigen Jahrgangsgroessen auf ihrer Vorbelegung, der Pfadstand aus dem
/// Musterwert.
///
/// **Ein voreingestellter Satz ist hier richtig und waere anderswo falsch.** Er rechnet
/// nach T10b eine tote Welt, und genau die will diese Datei: Was sie prueft, ist die
/// **Bindung** von Satz und Zustand und die Gestalt der Regel, nicht ihre Kalibrierung.
/// Ein erfundener Satz mit plausiblen Zahlen saehe an dieser Stelle wie eine
/// Kalibrierung aus, die niemand beschlossen hat.
///
/// **Der Pfadstand ist die eine Ausnahme, und er ist keine Kalibrierung**, sondern die
/// Abschrift der Ausgangslage: Er traegt Adresse fuer Adresse den Wert, den die Lage dort
/// ohnehin hat. Die Begruendung steht bei `pfadstand_der_probe`. Auf die Pruefsumme wirkt
/// er nicht -- sie laeuft nach T10b ueber die sieben Schluesselfelder --, also bleibt
/// jede Ausgangslage dieser Datei an denselben Traeger gebunden wie vorher.
///
/// **Fuer Schritt 5 heisst das etwas Bestimmtes** (Paket 0197): `zustimmung_elastizitaet`
/// steht auf null, also ist der additive Term der Zustimmungsregel null, und was von ihr
/// gemessen wird, sind ihre beiden Schranken. Das ist die Haelfte, die ohne eine
/// beschlossene Kalibrierung ueberhaupt pruefbar ist -- die andere Haelfte braucht Zahlen,
/// die noch niemand gesetzt hat, und eine Probe, die sie sich ausdenkt, misst die
/// Erfindung.
constexpr kern::werte::Konstanten konstanten_der_probe()
{
    kern::werte::Konstanten satz{};
    satz.pfadstand = pfadstand_der_probe();
    return satz;
}

constexpr kern::werte::Konstanten KONSTANTEN_DER_PROBE = konstanten_der_probe();

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

/// Ein Eintrag des zweiten Verzeichnisses -- die Kategorie fuer einen Riegel, den kein
/// Zustand erreicht.
///
/// Der Apparat dahinter -- das Ablegen der Meldungen, der Vergleich jeder Liste gegen
/// jede Meldung, die Vollzaehligkeit -- steht seit Paket 0244 in
/// `kern/test/kennzeichen.hpp` und wird von `werte_probe` genauso benutzt. Was hier
/// bleibt, ist das, was dieser Probe eigen ist: die beiden Aufzaehlungen, die Namen, die
/// Kennzeichenlisten und die Aufrufstellen.
using probe::kennzeichen::OhneZustand;

/// Die Riegel, gegen die diese Probe abbricht -- einer je Schranke, nicht einer je
/// Aufrufstelle.
///
/// Der Unterschied traegt die Eindeutigkeitszusicherung weiter unten. Zwei Stellen
/// koennen denselben Riegel meinen: Die Runde nach der letzten zaehlbaren und der dritte
/// Fall der Rundennummernprobe schlagen beide an der oberen Schranke an und bekommen
/// zeichengleiche Meldungen; die beiden negativen Rundennummern unterscheiden sich nur in
/// der Zahl. Ohne eine Kennung je Riegel meldete die Zusicherung genau diese Paare sofort
/// als Verletzung -- ein falscher Fund am ersten Tag.
enum class Riegel : std::size_t {
    ObereRundenschranke,  ///< in `kern::schritt`: die Vorrunde traegt den groessten int64_t
    RundeVorDerErsten,    ///< in `kern::schritt`: die Vorrundennummer ist negativ
    StartwertSetzen,      ///< in `kern::zustand`: an diesem Zugang lief eine Runde vorbei
    StartwertBinden,      ///< in `kern::zustand`: die Partie laeuft schon
    Spielmodus,           ///< in `kern::schritt`: der Modus ist in diesem Rahmen nicht gebaut
    Parametersatz,        ///< in `kern::schritt`: der Traeger gehoert nicht zu diesem Zustand
    Nennerbedingung,      ///< in `kern::schritt`: der Nenner der Zustimmungsregel ist nicht positiv
    Anzahl,
};

constexpr std::array<Riegel, 7> ALLE_RIEGEL = {
    Riegel::ObereRundenschranke, Riegel::RundeVorDerErsten, Riegel::StartwertSetzen,
    Riegel::StartwertBinden,     Riegel::Spielmodus,        Riegel::Parametersatz,
    Riegel::Nennerbedingung};

// Kommt ein Riegel dazu und niemand traegt ihn hier nach, faellt es beim Uebersetzen auf
// und nicht erst daran, dass die Vollzaehligkeitspruefung unten ihn nie sucht.
static_assert(ALLE_RIEGEL.size() == static_cast<std::size_t>(Riegel::Anzahl));

const char* riegelname(Riegel welcher)
{
    switch (welcher) {
    case Riegel::ObereRundenschranke:
        return "obere Rundenschranke";
    case Riegel::RundeVorDerErsten:
        return "Runde vor der ersten";
    case Riegel::StartwertSetzen:
        return "Startwert setzen nach der Runde";
    case Riegel::StartwertBinden:
        return "Startwertzugang binden nach der Runde";
    case Riegel::Spielmodus:
        return "Modus spielmodus nicht gebaut";
    case Riegel::Parametersatz:
        return "Parametersatz gehoert nicht zum Zustand";
    case Riegel::Nennerbedingung:
        return "Nenner der Zustimmungsregel nicht positiv";
    case Riegel::Anzahl:
        break;
    }
    return "(kein Riegel)";
}

// ---------------------------------------------------------------------------
// Paket 0248 -- die zweite Art Eintrag: ein Riegel, den kein Zustand erreicht
// ---------------------------------------------------------------------------
//
// Die Vollzaehligkeitshaelfte weiter unten verlangt zu jedem Eintrag von `ALLE_RIEGEL` in
// **jedem** Lauf eine angekommene Meldung. Fuer eine Schranke, vor die kein Zustand kommt,
// ist das nicht erfuellbar, und beide naheliegenden Auswege sind falsch: Sie in
// `ALLE_RIEGEL` einzutragen faerbt einen heilen Baum rot; sie ganz wegzulassen versteckt
// sie vor genau der Pruefung, die es gibt, damit keine Schranke unbemerkt verschwindet.
//
// Deshalb ein zweites Verzeichnis mit **eigenem Aufzaehlungstyp**. Der eigene Typ ist die
// Sperre gegen den bequemen Ausweg: Wer einen erreichbaren Riegel hierher schoebe, um die
// Vollzaehligkeit zu umgehen, muesste zugleich seine Abbruchstelle umschreiben --
// `bricht_ab_mit` nimmt `Riegel` entgegen und nicht diesen Typ, und eine Stelle, die
// abbricht, kann ihre Meldung nicht ablegen, ohne einen `Riegel` zu nennen.
//
// **Was von der Eindeutigkeitszusicherung bleibt, ist eine Haelfte von zweien, und die
// andere ist nicht erreichbar. Das ist gemessen und nicht geschaetzt:**
//
//   *Passt auf keine fremde* -- **bleibt, vollstaendig.** Diese Haelfte braucht nur die
//   Liste des Eintrags und die Meldungen der anderen. Beides ist da. Verkuerzt jemand die
//   Liste eines unerreichbaren Riegels auf ein Allerweltsstueck, passt sie sofort auf
//   fremde Meldungen und der Lauf wird rot -- genau wie bei einem erreichbaren.
//
//   *Passt auf jede eigene* -- **faellt weg, und nicht aus Bequemlichkeit.** Sie braucht
//   die eigene Meldung. Die entsteht in `summe_der_regel_pruefen`, und diese Funktion
//   steht in `src/schritt.cpp` im namenlosen Namensbereich, hat also innere Bindung. Es
//   fehlt nicht ein Zustand, der sie erreichte -- es fehlt jede Moeglichkeit, sie von hier
//   aus zu nennen. Auch eine Probe, die die Argumente kennt, kann sie nicht rufen.
//
// **Der Preis, ausgeschrieben, weil ihn sonst niemand sieht:** Ohne die zweite Haelfte
// faellt zweierlei nicht mehr auf. Erstens koennte eine **fremde** Liste so weit sein,
// dass sie auch auf die Meldung des unerreichbaren Riegels passte; kein Paar prueft das,
// weil es die Meldung nicht gibt. Zweitens rosten die Kennzeichen unten still: Formuliert
// jemand die Meldung in `src/schritt.cpp` um, stimmt die Liste hier nicht mehr mit ihr
// ueberein, und nichts wird rot. Beides endet an dem Tag, an dem der Riegel erreichbar
// wird -- dann wandert er nach `ALLE_RIEGEL` und bekommt beide Haelften.
//
// **Dieser Tag ist mit Paket 0284 naeher gerueckt und nicht gekommen** (2026-09-09).
// Schritt 3 rechnet seither, ein Instrumentenstand kann sich bewegen, und damit ist der
// Realeinkommenshub nicht mehr von sich aus null -- der erste der beiden Gruende, aus
// denen der additive Term verschwand, ist fort. Der zweite traegt weiter allein:
// `zustimmung_elastizitaet` steht in jedem Traeger dieser Datei auf null, also ist das
// Produkt null, welchen Hub die Runde auch rechnet. Erreichbar wuerde der Riegel erst
// mit einem Traeger, der beides zugleich fuehrt -- einen Koeffizienten ungleich null und
// einen Pfadstand, der die Adressen bewegt --, und dazu gehoerte ein Ausgangswert der
// Zustimmung nahe an einem Ende des Zahlbereichs. Das ist ein Zuschnitt und kein Rumpf.
//
// **Der Ausweg, den es nicht gibt, damit ihn niemand zweimal sucht:** Die Meldung hier
// nachzubauen -- denselben Wortlaut ein zweites Mal hinschreiben und die fremden Listen
// dagegen halten -- ist genau der Volltextvergleich, gegen den `bricht_ab_mit` warnt, nur
// in seiner schlechteren Form. Die Abschrift ist durch nichts an das Original gebunden;
// sie truege eine Zusicherung ueber einen Text, den der Kern gar nicht wirft.
enum class RiegelOhneZustand : std::size_t {
    /// in `kern::schritt`: die Summe der Zustimmungsregel liegt ausserhalb von `i64`
    SummeDerZustimmungsregel,
    Anzahl,
};

/// Die Textstuecke, an denen die Meldung dieses Riegels zu erkennen **waere**.
///
/// **Dass die verbleibende Haelfte hier wirklich beisst, ist kein Zutrauen, sondern an
/// diesem Eintrag ablesbar:** Das erste Stueck steht auch in der Meldung der
/// `Nennerbedingung` -- beide Riegel sitzen an der Zustimmungsregel. Allein truege es
/// nicht, und der Lauf wuerde rot. Erst die drei zusammen trennen die beiden. Wer die
/// Liste kuerzt, sieht das sofort, und genau dafuer gibt es die Pruefung.
constexpr std::array<const char*, 3> KENNZEICHEN_SUMME_DER_REGEL = {
    "Zustimmungsregel", "klemmt erst hinter der Summe", "der additive Term"};

constexpr std::array<OhneZustand<RiegelOhneZustand>, 1> RIEGEL_OHNE_ZUSTAND = {{
    {RiegelOhneZustand::SummeDerZustimmungsregel,
     "Summe der Zustimmungsregel ausserhalb von i64",
     "der additive Term ist ein Produkt mit zustimmung_elastizitaet, und die steht in "
     "jedem Traeger dieser Datei auf null",
     KENNZEICHEN_SUMME_DER_REGEL},
}};

// Dasselbe Netz wie bei `ALLE_RIEGEL`: Kommt ein Eintrag dazu und niemand traegt ihn nach,
// faellt es beim Uebersetzen auf und nicht daran, dass ihn nie jemand prueft.
static_assert(RIEGEL_OHNE_ZUSTAND.size()
              == static_cast<std::size_t>(RiegelOhneZustand::Anzahl));

/// Ob der Eintrag an der n-ten Stelle auch den n-ten Riegel nennt.
///
/// Die Groessenpruefung darueber allein liesse zwei Eintraege desselben Riegels durch --
/// die Zahl staende dann richtig da und ein Riegel fehlte trotzdem. Hier haengt die
/// Zuordnung an der Stelle im Feld, und beides zusammen macht aus der Zahl eine Deckung.
constexpr bool riegel_ohne_zustand_geordnet()
{
    for (std::size_t n = 0; n < RIEGEL_OHNE_ZUSTAND.size(); ++n) {
        if (RIEGEL_OHNE_ZUSTAND[n].riegel != static_cast<RiegelOhneZustand>(n)) {
            return false;
        }
    }
    return true;
}

static_assert(riegel_ohne_zustand_geordnet());

/// Das Verzeichnis dieser Probe.
///
/// Es haelt die angekommenen Meldungen, die beiden Aufzaehlungen oben und den
/// Fehlerzaehler dieser Datei. Alles daran ist geteilt; eigen sind allein die Werte, die
/// hier hineingehen -- deshalb steht der Aufruf und nicht die Mechanik in dieser Datei.
probe::kennzeichen::Buch<Riegel, RiegelOhneZustand> buch{"schritt", fehlgeschlagen,
                                                        ALLE_RIEGEL, &riegelname,
                                                        RIEGEL_OHNE_ZUSTAND};

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

/// Was auf den zwoelf Wertschoepfungsadressen steht -- die Wahl, um die es in Paket 0237
/// geht.
///
/// `Muster` ist die Belegung, mit der jede Runde dieser Datei bis zum 2026-09-08 lief:
/// `musterwert` legt auf die zwoelf Adressen nur `0` und `-10.000`, also ist das
/// Bruttoinlandsprodukt aller vier Laender negativ. `Positiv` ist die Belegung, die
/// `spiel.md` an der Zustimmungsregel verlangt. `Muster` bleibt, aber nur noch als der
/// Fall, an dem die Schranke anschlaegt.
enum class Wertschoepfung {
    Positiv,
    Muster,
};

/// Der Wert, den eine Wertschoepfungsadresse in der positiven Belegung traegt.
///
/// **Positiv, und je Adresse verschieden.** Positiv, weil die Zustimmungsregel durch das
/// Bruttoinlandsprodukt teilt und `spiel.md` dafuer einen Nenner ueber null verlangt;
/// verschieden, weil vier gleiche Landessummen einen vertauschten Laenderblock nicht mehr
/// zeigten. Die Groessenordnung ist die der Klasse 2 aus T5 und **keine Kalibrierung** --
/// gemessen wird das Vorzeichen des Nenners und nicht seine Hoehe.
i64 wertschoepfung_der_probe(Index platz)
{
    return 1'000'000 + static_cast<i64>(platz);
}

/// Ob `platz` eine der zwoelf Wertschoepfungsadressen ist.
bool ist_wertschoepfung(Index platz)
{
    for (const Index eine : WERTSCHOEPFUNGSPLAETZE) {
        if (eine == platz) {
            return true;
        }
    }
    return false;
}

/// Der Startwert einer Adresse -- `musterwert`, ausser auf den zwoelf
/// Wertschoepfungsadressen in der positiven Belegung.
///
/// **Eine Stelle und nicht zwei.** Zwei Bauarten derselben Ausgangslage waeren zwei
/// Stellen, die auseinanderlaufen; die Handlage in
/// `probe_zwei_runden_und_startwertriegel` fuellt ihre 310 Adressen deshalb aus derselben
/// Funktion wie `ausgangslage`.
i64 startwert(Index platz, Wertschoepfung wie)
{
    if (wie == Wertschoepfung::Positiv && ist_wertschoepfung(platz)) {
        return wertschoepfung_der_probe(platz);
    }
    return musterwert(platz);
}

/// Baut eine Ausgangslage mit Startwerten auf allen 310 Adressen, `partie.runde` auf
/// `rundennummer`, die Parameterpruefsumme passend zum Traeger dieser Probe und die vier
/// Zustimmungen auf die uebergebenen Werte.
///
/// **Ein einziger Startwertzugang fuer alle 310 Adressen**, und die beiden Partiefelder
/// zuletzt: Der Riegel aus Paket 0027 greift beim Binden und nicht bei jedem `setze` --
/// genau deshalb, weil `partie.runde` selbst zu der Menge gehoert, die eine
/// Startbelegung setzt. Ein Zugang je Aufruf haette sich nach der ersten gesetzten
/// Rundennummer selbst die Tuer zugemacht.
///
/// **Die zweite Nachsetzung ist neu (Paket 0229) und keine Bequemlichkeit.** Auf
/// `PLATZ_PARAMETERSUMME` stuende sonst `musterwert(PLATZ_PARAMETERSUMME)` -- eine Zahl
/// aus acht Mustern, die den Traeger nicht kennt. Seit die Runde beide gegeneinander
/// haelt, stuerbe jede Runde dieser Datei an der Schranke, ehe sie eine Adresse
/// schreibt. Die Zahl wird nicht abgeschrieben, sondern von der Rechnung geholt, die die
/// Runde selbst benutzt: Zwei Abschriften derselben Summe waeren zwei Stellen, die
/// auseinanderlaufen. Dass die Rechnung damit nicht sich selbst prueft, ist der Grund
/// fuer `probe_parametersatz` weiter unten -- dort steht die Gegenseite.
///
/// **Die dritte Nachsetzung ist neu (Paket 0197) und traegt eine ganze Probe.** Seit
/// Schritt 5 rechnet, ist der Startwert der vier Zustimmungen kein gleichgueltiger
/// Musterwert mehr, sondern der Eingang der Regel. Ein Aufrufer, der sie frei setzen
/// kann, unterscheidet den gerechneten Rumpf vom vortragenden -- und dafuer braucht er
/// **einen** Startwertzugang, denn ein zweiter bindet auf einer Lage mit gesetzter
/// Rundennummer nicht mehr.
///
/// **Die vierte Belegung ist neu (Paket 0237) und betrifft jede Runde dieser Datei.** Die
/// zwoelf Wertschoepfungsadressen tragen ihren Musterwert nur noch, wenn der Aufrufer es
/// ausdruecklich verlangt. Der Grund steht an `Wertschoepfung`: Unter der Musterbelegung
/// ist das Bruttoinlandsprodukt aller vier Laender negativ, und eine Probe der
/// Zustimmungsregel auf einem Zustand, den `spiel.md` verbietet, misst nichts.
///
/// **Der Parametersatz ist seit Paket 0240 ein Argument mit Vorbelegung.** Die Runde haelt
/// ihre Summe gegen `partie.parameter_pruefsumme`; wer mit einem anderen Traeger fahren
/// will, braucht deshalb eine Lage, die zu ihm gehoert -- sonst stirbt die Runde an der
/// Bindung statt an dem, was gemessen werden soll. Die Vorbelegung haelt jede aeltere
/// Aufrufstelle unveraendert.
Zustand ausgangslage_voll(i64 rundennummer,
                          const std::array<i64, kern::zustand::LAENDER>& zustimmung,
                          Wertschoepfung wie,
                          const kern::werte::Konstanten& satz = KONSTANTEN_DER_PROBE)
{
    Zustand welt;
    Startbelegung zugang{welt};
    for (Index platz = 0; platz < FELDER; ++platz) {
        zugang.setze(platz, startwert(platz, wie));
    }
    for (std::size_t n = 0; n < ZUSTIMMUNGSPLAETZE.size(); ++n) {
        zugang.setze(ZUSTIMMUNGSPLAETZE[n], zustimmung[n]);
    }
    zugang.setze(kern::zustand::stelle_partie(PartieFeld::Runde), rundennummer);
    zugang.setze(PLATZ_PARAMETERSUMME, kern::schritt::parameter_pruefsumme(satz));
    return welt;
}

/// Die Startwerte der vier Zustimmungsadressen -- die Belegung, die `ausgangslage`
/// hatte, ehe sie frei setzbar wurde. Keine der vier ist eine Wertschoepfungsadresse,
/// also sind es dieselben vier Zahlen wie vor Paket 0237.
std::array<i64, kern::zustand::LAENDER> zustimmung_aus_mustern()
{
    std::array<i64, kern::zustand::LAENDER> werte{};
    for (std::size_t n = 0; n < ZUSTIMMUNGSPLAETZE.size(); ++n) {
        werte[n] = startwert(ZUSTIMMUNGSPLAETZE[n], Wertschoepfung::Positiv);
    }
    return werte;
}

Zustand ausgangslage_mit_zustimmung(i64 rundennummer,
                                    const std::array<i64, kern::zustand::LAENDER>& zustimmung,
                                    const kern::werte::Konstanten& satz = KONSTANTEN_DER_PROBE)
{
    return ausgangslage_voll(rundennummer, zustimmung, Wertschoepfung::Positiv, satz);
}

Zustand ausgangslage(i64 rundennummer)
{
    return ausgangslage_mit_zustimmung(rundennummer, zustimmung_aus_mustern());
}

/// Die Ausgangslage, die diese Datei vor Paket 0237 hatte: dieselbe Lage, aber mit dem
/// Musterwert auf den zwoelf Wertschoepfungsadressen und damit mit einem negativen
/// Bruttoinlandsprodukt in jedem der vier Laender. Sie hat genau einen Zweck -- die
/// Gegenseite der neuen Schranke.
Zustand ausgangslage_ohne_wertschoepfung(i64 rundennummer)
{
    return ausgangslage_voll(rundennummer, zustimmung_aus_mustern(), Wertschoepfung::Muster);
}

}  // namespace

#define PRUEFE(ausdruck) pruefe((ausdruck), #ausdruck, __LINE__)

/// Reicht die Zeile der **Aufrufstelle** an `Buch::bricht_ab_mit` durch -- sonst naennte
/// jede Fehlermeldung die eine Zeile in der Vorlage. Variadisch, damit das Komma in einem
/// mehrzeiligen Lambda den Praeprozessor nicht in zwei Argumente teilt.
#define BRICHT_AB_MIT(was, riegel, kennzeichen, ...) \
    buch.bricht_ab_mit((was), (riegel), (kennzeichen), __LINE__, __VA_ARGS__)

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
// Bedingung 4 -- die Kette hat 175 Glieder: 159 Vortraege, zwoelf aus dem Jahrgang
// und vier aus Gegenkraft 2
// ---------------------------------------------------------------------------

/// Geht alle Glieder durch. Statt je Glied eine eigene Meldung zu setzen -- das waeren
/// im Fehlerfall 175 -- merkt sich die Probe **das erste** verletzte Glied je Aussage
/// und schreibt es hin. Eine Nummer ist ein Hinweis, ein Wall aus 175 Zeilen keiner.
///
/// **Hier steht der Widerruf, den `include/kern/schritt.hpp` angekuendigt hat** (Paket
/// 0197). Bis dahin galt: Die Kette liegt in aufsteigender Adressfolge, und der Kopf hat
/// dazugeschrieben, dass die Aussage faellt, sobald ein Schritt seinen Block als Ganzes
/// rechnet -- nachzuziehen "in seiner Probe". Schritt 5 rechnet, und dies ist die Probe.
///
/// **Die Aussage wird nicht gestrichen, sondern geteilt**, und die neue ist die
/// schaerfere von beiden: Die Kette zerfaellt in zwei Stuecke, und beide sind vollstaendig
/// beschrieben.
///
///   * **Die ersten 171 Glieder** kommen aus der Adressrunde: aufsteigend, paarweise
///     verschieden, jedes auf seine eigene Adresse.
///   * **Die letzten vier** kommen aus dem Block von Schritt 5: die vier Zustimmungen in
///     der Laenderreihenfolge, jede mit der Ursache `Gegenkraft` und der Nummer 2 aus
///     `spiel.md`.
///
/// Eine blosse Streichung waere hier das Schlechtere gewesen. "Nicht mehr durchgehend
/// aufsteigend" ist von "in beliebiger Reihenfolge" durch keine Messung zu unterscheiden,
/// und genau der Unterschied macht den Rahmen von einer gerechneten Runde unterscheidbar.
///
/// **Und dieselbe Teilung noch einmal, eine Ebene tiefer** (Paket 0284): Die 171 Glieder
/// der Adressrunde tragen nicht mehr alle dieselbe Ursache. Zwoelf von ihnen -- je
/// spielbarem Land der Stand der drei pfadgestuetzten Instrumente -- kommen aus dem
/// Traeger und nennen deshalb nach T18 den `Jahrgang` als Herkunft; die uebrigen 159
/// nennen `Vortrag` auf ihre eigene Adresse.
///
/// **Gepruefte Adressen und keine gezaehlte Menge.** Die Probe rechnet die zwoelf
/// Adressen aus derselben Doppelschleife aus, aus der `kern::schritt` sie schreibt, und
/// verlangt fuer jedes Glied die Ursache, die zu **seiner** Adresse gehoert. Eine blosse
/// Zaehlung "zwoelfmal Jahrgang" waere von einer Runde, die den Pfadstand auf die
/// Restdauern schriebe, nicht zu unterscheiden -- und die Restdauern liegen im selben
/// Landesblock.
///
/// **Der vierte Instrumentenstand steht ausdruecklich nicht darunter.** Die
/// Finanzmarktregulierung hat keine Reihe des Jahrgangs (T61); ihr Glied traegt `Vortrag`
/// wie die anderen 158, und das ist die Halbseite, an der ein Rumpf auffiele, der einfach
/// alle sechzehn Staende setzte.
void probe_kette(const Kette& kette, i64 erwartete_runde)
{
    PRUEFE(kette.laenge() == 175);

    // Wo der Block von Schritt 5 anfaengt: hinter allem, was die Adressrunde geschrieben
    // hat. Gerechnet aus der Laenderzahl und nicht als 171 hingeschrieben.
    constexpr std::size_t VOR_DER_GEGENKRAFT = 175 - kern::zustand::LAENDER;

    constexpr std::size_t KEINS = 1000;  // liegt ausserhalb jeder moeglichen Gliednummer
    std::size_t erstes_falsches_schlussglied = KEINS;
    std::size_t erste_falsche_art = KEINS;
    std::size_t erste_falsche_quelle = KEINS;
    std::size_t erste_falsche_runde = KEINS;
    std::size_t erste_falsche_verzoegerung = KEINS;
    std::size_t erster_falscher_beitrag = KEINS;
    std::size_t erste_wertaenderung = KEINS;
    std::size_t erste_nicht_aufsteigende = KEINS;
    std::size_t erste_ausserhalb_maske = KEINS;

    // Wie viele Glieder der Adressrunde auf einer der zwoelf pfadgestuetzten Adressen
    // liegen. Die Zahl kommt **nicht** an die Stelle der Adresspruefung darueber, sondern
    // neben sie: Jene sagt, dass jedes Glied die richtige Ursache traegt, diese, dass es
    // die zwoelf Glieder ueberhaupt gibt. Ohne die zweite waere eine Kette, in der
    // Schritt 3 gar nichts schreibt, an der ersten nicht zu erkennen -- sie prueft nur
    // vorhandene Glieder.
    std::size_t glieder_aus_dem_pfad = 0;

    // Das Glied, das seit Paket 0071 einen anderen Wert traegt als vorher -- das einzige
    // der Adressrunde, das es darf. Beides wird geprueft: dass es da ist, und dass es die
    // richtigen beiden Zahlen nennt.
    bool rundenglied_gesehen = false;
    bool rundenglied_zaehlt_hoch = false;

    const Bitfeld& maske = sollmaske(Modus::Weltlauf);
    bool voriges_gibt_es = false;
    Index voriges_ziel = 0;

    for (std::size_t n = 0; n < kette.laenge(); ++n) {
        const Ursachensatz& satz = kette.eintrag(n);
        const bool aus_schritt_5 = n >= VOR_DER_GEGENKRAFT;

        if (aus_schritt_5) {
            // Die vier Schlussglieder, jedes vollstaendig festgelegt: Ursache
            // `Gegenkraft` mit der Nummer 2 aus `spiel.md`, auf genau der
            // Zustimmungsadresse des Landes, das an dieser Stelle der Reihe steht.
            // Zusammen mit der Laenge 175 sagt das zugleich, dass es diese vier Glieder
            // ueberhaupt gibt -- eine Kette ohne sie waere zu kurz.
            const std::size_t rang = n - VOR_DER_GEGENKRAFT;
            const bool stimmt = satz.ursache.art() == UrsacheArt::Gegenkraft
                                && satz.ursache.gegenkraftart() == 2
                                && satz.ziel == ZUSTIMMUNGSPLAETZE[rang];
            if (!stimmt && erstes_falsches_schlussglied == KEINS) {
                erstes_falsches_schlussglied = n;
            }
        } else {
            // Die Ursache, die zu **dieser** Adresse gehoert: `Jahrgang` fuer die zwoelf
            // pfadgestuetzten Instrumentenstaende, `Vortrag` fuer jede andere Adresse der
            // Adressrunde. Die Menge kommt aus derselben Doppelschleife wie im Kern und
            // nicht aus einer Zahl.
            const bool aus_dem_pfad = ist_pfadstand(satz.ziel);
            const UrsacheArt gefordert =
                aus_dem_pfad ? UrsacheArt::Jahrgang : UrsacheArt::Vortrag;
            if (satz.ursache.art() != gefordert && erste_falsche_art == KEINS) {
                erste_falsche_art = n;
            }
            if (aus_dem_pfad) {
                ++glieder_aus_dem_pfad;
            }
            // Die vorgetragenen Glieder der Adressrunde nennen ihre **eigene** Adresse als
            // Herkunft. Bei den unveraenderten ist das die Aussage "unveraendert";
            // beim Glied von `partie.runde` ist es die Aussage "aus dem alten Wert dieser
            // Adresse und aus nichts sonst" -- die Ursachenform nennt die Herkunft, nicht
            // die Gleichheit.
            if (satz.ursache.art() == UrsacheArt::Vortrag
                && satz.ursache.vortragsadresse() != satz.ziel
                && erste_falsche_quelle == KEINS) {
                erste_falsche_quelle = n;
            }
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
        } else if (!aus_schritt_5 && satz.alt != satz.neu && erste_wertaenderung == KEINS) {
            // Die uebrigen 170 Glieder der Adressrunde bewegen ihren Wert nicht, und die
            // zwoelf aus dem Pfad tun es aus einem anderen Grund als die 158 daneben:
            // Jene tragen vor, diese **setzen** einen Wert, der in dieser Datei zufaellig
            // derselbe ist -- der Traeger holt ihn aus `musterwert`, wie die Ausgangslage
            // (`pfadstand_der_probe`). Die Zeile prueft damit hier keine Eigenschaft von
            // Schritt 3, sondern die Bindung zwischen Traeger und Lage; dass Schritt 3
            // einen **anderen** Wert wirklich hineinschreibt, misst
            // `probe_pfadstand_geht_in_die_runde`.
            //
            // Fuer die vier aus Schritt 5 gilt das ausdruecklich nicht: Sie tragen den
            // Wert, den die Regel gerechnet hat, gleich ob er sich bewegt hat oder nicht.
            erste_wertaenderung = n;
        }
        if (!maske.steht(satz.ziel) && erste_ausserhalb_maske == KEINS) {
            erste_ausserhalb_maske = n;
        }

        if (!aus_schritt_5) {
            if (voriges_gibt_es && satz.ziel <= voriges_ziel
                && erste_nicht_aufsteigende == KEINS) {
                // "aufsteigend" schliesst "paarweise verschieden" ein: `<=` faengt beides.
                erste_nicht_aufsteigende = n;
            }
            voriges_ziel = satz.ziel;
            voriges_gibt_es = true;
        }
    }

    PRUEFE(erstes_falsches_schlussglied == KEINS);
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
    PRUEFE(glieder_aus_dem_pfad == PFADSTANDSPLAETZE.size());

    // Und die Gegenrichtung: Jede Adresse der Maske kommt in der Kette vor. Zusammen mit
    // der Laenge 175 ist die Kette damit genau die Maske -- nicht 175 beliebige Adressen,
    // die zufaellig in ihr liegen. Diese Zeile traegt seit Paket 0197 mehr als vorher:
    // Sie ist es, die eine Doppelnennung zwischen den 171 aufsteigenden und den vier
    // festgenagelten faengt, denn die beiden Stuecke werden getrennt geprueft.
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
// Bedingungen 3, 4 und 6 -- eine Runde laeuft durch, und der Zustand danach stimmt
// ---------------------------------------------------------------------------

/// Laesst eine Runde laufen und gibt den entstandenen Zustand zurueck.
Zustand probe_eine_runde(i64 vorrundennummer)
{
    const Zustand vorher = ausgangslage(vorrundennummer);
    const u64 summe_vorher = summe_von(vorher);
    const i64 diese_runde = vorrundennummer + 1;

    // Bedingung 3: kehrt zurueck, ohne abzubrechen. Der Aufruf selbst ist der Nachweis,
    // dass die Rundenendpruefung aus T38 gehalten hat.
    const Rundenergebnis ergebnis =
        kern::schritt::schritt(vorher, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    // Der unabhaengige Erwartungswert: dieselbe Ausgangslage, nur mit der Rundennummer
    // dieser Runde **und den vier Zustimmungen auf ihrer Klemme**. Sie entsteht ueber
    // `zustand::Startbelegung` und weiss von `kern::schritt` nichts -- damit haengt die
    // Aussage nicht an derselben Rechnung, die sie pruefen soll.
    //
    // Bis Paket 0197 stand hier `ausgangslage(diese_runde)` unveraendert, denn eine Runde
    // bewegte genau eine der 310 Groessen. Seit Schritt 5 rechnet, gehoert die Klemme in
    // den Erwartungswert; warum sie hier die **ganze** Regel ist, steht an `geklemmt`.
    std::array<i64, kern::zustand::LAENDER> erwartete_zustimmung = zustimmung_aus_mustern();
    for (i64& wert : erwartete_zustimmung) {
        wert = geklemmt(wert);
    }
    const Zustand erwartet = ausgangslage_mit_zustimmung(diese_runde, erwartete_zustimmung);
    PRUEFE(nachher == erwartet);

    // Wie viele der 310 Groessen sich bewegt haben. Gezaehlt wird ueber alle 310, nicht
    // an den erwarteten Stellen nachgesehen -- sonst pruefte die Zeile, was sie annimmt.
    //
    // **Die Zahl wird nicht hingeschrieben, sondern gegen den Erwartungszustand
    // gehalten.** Eine feste Ziffer haette den Rumpf nur bis zur naechsten Belegung von
    // `musterwert` geprueft und danach den Musterwert gemessen statt die Regel.
    std::size_t geaenderte = 0;
    std::size_t erwartete_aenderungen = 0;
    Index erste_geaenderte = FELDER;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (vorher.lies(platz) != nachher.lies(platz)) {
            ++geaenderte;
            if (erste_geaenderte == FELDER) {
                erste_geaenderte = platz;
            }
        }
        if (vorher.lies(platz) != erwartet.lies(platz)) {
            ++erwartete_aenderungen;
        }
    }
    PRUEFE(geaenderte == erwartete_aenderungen);
    PRUEFE(vorher.lies(PLATZ_RUNDE) == vorrundennummer);
    PRUEFE(nachher.lies(PLATZ_RUNDE) == diese_runde);
    if (geaenderte != erwartete_aenderungen) {
        std::fprintf(stderr, "  %zu Groessen geaendert statt %zu, erste: %zu (%s)\n", geaenderte,
                     erwartete_aenderungen, erste_geaenderte,
                     erste_geaenderte < FELDER ? kern::zustand::index_zu_adresse(erste_geaenderte)
                                               : "keine");
    }

    // Die Pruefsumme faellt jetzt, und das ist die widerrufene Bedingung 6 von 0033.
    // Beide Zahlen stehen darunter im Wortlaut; ohne sie waere der Widerruf ein stiller.
    const u64 summe_nachher = summe_von(nachher);
    PRUEFE(summe_vorher != summe_nachher);
    PRUEFE(summe_nachher == summe_von(erwartet));
    // Zwei Wege zu jeder der beiden Zahlen, damit keine an einer einzigen Rechnung haengt.
    PRUEFE(summe_vorher == kern::zustand::pruefsumme_von(vorher));
    PRUEFE(summe_nachher == kern::zustand::pruefsumme_von(nachher));

    std::printf("  Vorrunde %lld -> Runde %lld: Pruefsumme %016llx vorher, %016llx nachher; "
                "%zu von 310 Groessen geaendert, erste %s\n",
                static_cast<long long>(vorrundennummer), static_cast<long long>(diese_runde),
                static_cast<unsigned long long>(summe_vorher),
                static_cast<unsigned long long>(summe_nachher), geaenderte,
                erste_geaenderte < FELDER ? kern::zustand::index_zu_adresse(erste_geaenderte)
                                          : "keine");

    probe_kette(ergebnis.kette_dieser_runde, diese_runde);
    std::printf("  Kette: %zu Glieder (erwartet 175), Runde %lld an jedem Glied; "
                "171 aufsteigend aus der Adressrunde -- davon %zu mit der Ursache "
                "Jahrgang --, danach 4 aus Gegenkraft 2\n",
                ergebnis.kette_dieser_runde.laenge(), static_cast<long long>(diese_runde),
                PFADSTANDSPLAETZE.size());

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

    // Und **welcher** Riegel (Paket 0085): "groesste int64_t" steht nur in dem, der die
    // naechste Runde vorher verweigert. Der Fangnetzriegel im `Schreiber` spraeche
    // stattdessen von einer Runde vor der ersten -- er saehe nur die Zahl, die der
    // Umbruch hinterlassen hat, und nicht ihren Grund.
    const std::array<const char*, 2> nach_der_letzten = {{"kern::schritt", "groesste int64_t"}};
    BRICHT_AB_MIT("Runde nach der letzten zaehlbaren", Riegel::ObereRundenschranke,
                  nach_der_letzten, [&] {
        static_cast<void>(
            kern::schritt::schritt(am_ende, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf));
    });
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
        zugang.setze(platz, startwert(platz, Wertschoepfung::Positiv));
    }
    zugang.setze(PLATZ_RUNDE, 0);
    // Diese Lage wird von Hand gebaut und nicht ueber `ausgangslage`, weil der Zugang
    // hier ueber die beiden Runden hinaus offen bleiben muss -- er ist der Gegenstand
    // der zweiten Haelfte. Die Parameterpruefsumme braucht sie trotzdem, und aus
    // demselben Grund. Die Feldwerte kommen aus `startwert` und nicht aus `musterwert`,
    // damit sie die Nennerbedingung der Zustimmungsregel erfuellt wie jede andere Lage
    // dieser Datei (Paket 0237); von Hand gebaut heisst nicht zweimal belegt.
    zugang.setze(PLATZ_PARAMETERSUMME,
                 kern::schritt::parameter_pruefsumme(KONSTANTEN_DER_PROBE));

    // Die Positivkontrolle, und sie steht vor den beiden Abbruechen unten: Der Zugang
    // **hat** geschrieben. Ohne sie zeigten die Abbrueche auch dann dasselbe Bild, wenn
    // er von Anfang an wirkungslos gewesen waere.
    PRUEFE(welt.lies(PLATZ_RUNDE) == 0);
    PRUEFE(welt.lies(0) == startwert(0, Wertschoepfung::Positiv));
    PRUEFE(welt.lies(FELDER - 1) == startwert(FELDER - 1, Wertschoepfung::Positiv));
    PRUEFE(kern::zustand::vor_der_ersten_runde(welt));

    const Rundenergebnis erste =
        kern::schritt::schritt(welt, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    welt = erste.neuer_zustand;
    PRUEFE(welt.lies(PLATZ_RUNDE) == 1);

    const Rundenergebnis zweite =
        kern::schritt::schritt(welt, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
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
    //
    // Beide Haelften kommen aus `Startbelegung`, und der Klassenname allein unterschiede
    // sie nicht -- er steht in beiden Meldungen. Das zweite Textstueck trennt sie: Hier
    // ist eine Runde **vorbeigelaufen**, unten laeuft die Partie **schon**. Ohne die
    // Trennung sagte ein gruener Lauf nur, dass irgendwo in `Startbelegung` etwas flog.
    const i64 vorher_an_null = welt.lies(0);
    const std::array<const char*, 2> alter_zugang = {
        {"kern::zustand::Startbelegung::setze", "eine Runde vorbeigelaufen"}};
    BRICHT_AB_MIT("Zugang von vor Runde 1", Riegel::StartwertSetzen, alter_zugang,
                  [&] { zugang.setze(0, 4711); });
    // Ein Abbruch, der vorher noch schreibt, waere keiner.
    PRUEFE(welt.lies(0) == vorher_an_null);

    // Haelfte 2: ein neuer Zugang bindet nicht mehr.
    const std::array<const char*, 2> neuer_zugang = {
        {"kern::zustand::Startbelegung", "die Partie laeuft schon"}};
    BRICHT_AB_MIT("neuer Zugang nach der Runde", Riegel::StartwertBinden, neuer_zugang, [&] {
        Startbelegung neuer{welt};
        static_cast<void>(neuer);
    });
}

// ---------------------------------------------------------------------------
// T10 -- gleiches Ergebnis bei jedem Lauf
// ---------------------------------------------------------------------------
//
// `schritt` ist eine reine Funktion ohne gezogene Zahlen. Zwei Aufrufe auf derselben
// Ausgangslage muessen deshalb bis auf das letzte Kettenglied dasselbe liefern. Bis zum
// 2026-09-08 war das billig zu haben, weil kein Schritt rechnete; die Probe stand hier
// fuer den Tag, an dem einer es tut. Der Tag ist da: Schritt 5 rechnet, und diese Zeilen
// laufen jetzt ueber eine Rechnung statt ueber 175 Vortraege.

void probe_zweimal_dasselbe()
{
    const Zustand vorher = ausgangslage(7);

    const Rundenergebnis erster =
        kern::schritt::schritt(vorher, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    const Rundenergebnis zweiter =
        kern::schritt::schritt(vorher, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);

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

    // Die drei hinteren Stuecke sind Bedingung 7 und standen hier schon: alle 310
    // Adressen, der Modus beim Namen, die zwei Schritte ohne Paket. Vorn steht seit
    // Paket 0085 der Kasten, der geworfen hat -- er kennzeichnet den Riegel, waehrend die
    // drei anderen sagen, dass die Meldung ihren Grund nennt.
    const std::array<const char*, 4> kennzeichen = {
        {"kern::schritt", "spielmodus", "310", "kein Paket"}};
    BRICHT_AB_MIT("Modus spielmodus", Riegel::Spielmodus, kennzeichen, [&] {
        static_cast<void>(
            kern::schritt::schritt(welt, {}, KONSTANTEN_DER_PROBE, Modus::Spielmodus));
    });
}

// ---------------------------------------------------------------------------
// Die Rundennummer -- die beiden Enden sterben, statt still weiterzuzaehlen
// ---------------------------------------------------------------------------
//
// Die Nummer dieser Runde ist `partie.runde` der Vorrunde plus eins. Beide Enden sind
// harte Fehler: Eine Runde vor der ersten gibt es nicht, und `I64_MAX + 1` waere mit
// `-fwrapv` ein Umbruch ins Negative -- also eine Rundennummer, die der `Schreiber`
// abwiese, mit einer Meldung, die die Ursache nicht mehr nennt.

/// Eine Rundennummer und der Riegel, der an ihr anschlagen muss.
///
/// Die Erwartung haengt am Fall und nicht an der Schleife, weil die drei Nummern **nicht**
/// an derselben Schranke sterben: Die beiden negativen faengt der Riegel gegen die Runde
/// vor der ersten, `I64_MAX` der gegen die nicht mehr zaehlbare. Eine Schleife mit einer
/// gemeinsamen Erwartung koennte den Unterschied nicht sehen -- und genau ihn will das
/// Paket festhalten.
/// Der Riegel steht am Fall und nicht an der Schleife, aus demselben Grund wie die
/// Kennzeichen: Die ersten beiden Faelle sterben an einer anderen Schranke als der dritte.
/// Der dritte teilt sich seine Schranke mit der Probe der Runde nach der letzten
/// zaehlbaren -- deshalb tragen beide dieselbe Kennung, und die Eindeutigkeitspruefung
/// haelt sie auseinander, ohne sie gegeneinander zu stellen.
struct Rundenfall {
    i64 nummer;
    const char* was;
    Riegel riegel;
    std::array<const char*, 2> kennzeichen;
};

void probe_rundennummer()
{
    const std::array<Rundenfall, 3> faelle = {{
        {i64{-1}, "partie.runde = -1", Riegel::RundeVorDerErsten,
         {{"kern::schritt", "damit negativ"}}},
        {kern::festkomma::I64_MIN, "partie.runde = kleinster int64_t",
         Riegel::RundeVorDerErsten, {{"kern::schritt", "damit negativ"}}},
        {kern::festkomma::I64_MAX, "partie.runde = groesster int64_t",
         Riegel::ObereRundenschranke, {{"kern::schritt", "groesste int64_t"}}},
    }};

    for (const Rundenfall& fall : faelle) {
        const Zustand welt = ausgangslage(fall.nummer);
        BRICHT_AB_MIT(fall.was, fall.riegel, fall.kennzeichen, [&] {
            static_cast<void>(
                kern::schritt::schritt(welt, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf));
        });
    }
}

// ---------------------------------------------------------------------------
// Paket 0284 -- eine Zahl geht in den Traeger hinein und kommt aus der Adresse heraus
// ---------------------------------------------------------------------------
//
// **Die eine Probe, die stirbt, wenn `schritt_3_politik` wieder `{ schreiber.vortrag
// (platz); }` heisst.** Sie faehrt eine Runde mit einem Traeger, dessen Pfadstand fuer
// ein Land eine **andere** Zahl fuehrt als die Adresse vor der Runde, und liest die
// Adresse danach: Steht dort die Zahl aus dem Traeger, hat Schritt 3 sie geschrieben;
// traegt er vor, steht dort der alte Musterwert, und `PRUEFE(nachher == PFADWERT)` ist
// rot. Es ist die einzige Zeile dieser Datei, die von einem vortragenden Rumpf nicht
// erfuellt werden kann.
//
// **Warum ein zweiter Traeger und nicht der von oben.** Der Traeger dieser Datei fuehrt
// auf allen zwoelf pfadgestuetzten Adressen genau den Musterwert, den die Lage dort schon
// hat -- absichtlich, die Begruendung steht bei `pfadstand_der_probe`. Eine Runde damit
// ist von einer vortragenden am Zustand nicht zu unterscheiden; unterscheidbar wird sie
// erst an der Ursache in der Kette, und die prueft `probe_kette`. Hier geht es um die
// Zahl, also braucht es einen Traeger, der eine andere fuehrt.
//
// **Warum gerade die Vereinigten Staaten und der Leitzins.** Sobald sich ein Stand
// bewegt, rechnet Schritt 5 `politiklast` und dafuer `kern::werte::schaden` -- fuer den
// Leitzins ueber `schuld(l) = mal_geteilt(bip(l), staatsschuld(l), 10.000)`. Auf der
// Musterlage traegt die Staatsschuldquote bei zwei der vier Laender den kleinsten
// `int64_t`, und dort braeche jene Zeile in `kern::festkomma` ab -- an einer Schranke, die
// diese Datei weder meint noch fuehrt. Die Vereinigten Staaten tragen dort `10.000`, also
// hundert Prozent des Bruttoinlandsprodukts, und die Zeile rechnet durch. **Das ist kein
// ausgesuchter Sonderfall, sondern die Grenze dieser Ausgangslage**, und sie ist hier
// aufgeschrieben, damit der naechste sie nicht noch einmal messen muss.
//
// **Der additive Term bleibt trotzdem null**, denn `zustimmung_elastizitaet` steht in
// diesem Traeger wie im anderen auf null. Die Zustimmung liegt deshalb auch hier auf der
// Klemme ihres Ausgangswertes, und das prueft die Probe mit, weil es sonst so aussaehe,
// als haette der bewegte Stand sie bewegt.

/// Der Pfadwert, den diese Probe in den Traeger legt.
///
/// **Ausgesucht und nicht gerechnet**, damit sie im Fehlerfall wiedererkennbar ist: Sie
/// gehoert keinem der acht Muster an, ist positiv und liegt in der Groessenordnung eines
/// Leitzinses in Basispunkten (T5 Klasse 3). Was die Probe wirklich braucht, ist weniger
/// als das und steht als Zusicherung unten statt als Annahme hier: dass sie vom Musterwert
/// **der Zieladresse** verschieden ist.
constexpr i64 PFADWERT_DER_PROBE = 275;

void probe_pfadstand_geht_in_die_runde()
{
    constexpr kern::zustand::Gebiet LAND = kern::zustand::Gebiet::US;
    constexpr Index ZIEL = kern::zustand::stelle_instrument(
        LAND, kern::zustand::Instrument::Leitzins, kern::zustand::InstrumentFeld::Stand);
    constexpr Index VIERTES = kern::zustand::stelle_instrument(
        LAND, kern::zustand::Instrument::Regulierung, kern::zustand::InstrumentFeld::Stand);

    // Die Vorbedingung der ganzen Probe, als Zusicherung und nicht als Annahme: Waere der
    // Pfadwert der Musterwert der Zieladresse, liefen ein setzender und ein vortragender
    // Rumpf auf dieselbe Zahl hinaus, und die Zeile unten waere gruen, ohne etwas zu
    // sagen. Beim Uebersetzen geprueft, weil beide Zahlen beim Uebersetzen feststehen.
    static_assert(musterwert(ZIEL) != PFADWERT_DER_PROBE,
                  "sonst ist ein setzender Rumpf von einem vortragenden nicht zu "
                  "unterscheiden");
    static_assert(ist_pfadstand(ZIEL), "der Leitzins hat eine Reihe des Jahrgangs (T61)");
    static_assert(!ist_pfadstand(VIERTES), "die Regulierung hat keine (T61)");

    kern::werte::Konstanten mit_pfad = KONSTANTEN_DER_PROBE;
    mit_pfad.pfadstand[static_cast<std::size_t>(LAND)]
                      [static_cast<std::size_t>(kern::zustand::Instrument::Leitzins)] =
        PFADWERT_DER_PROBE;

    // Die Lage gehoert zu diesem Traeger, ohne dass sie neu gebaut werden muesste: Der
    // Pfadstand liegt nach T10b ausserhalb der Pruefsumme, also ist sie dieselbe Zahl wie
    // beim Traeger dieser Datei. Das steht als Pruefung da, denn faellt es, stirbt die
    // Runde unten an der Bindung statt an dem, was gemessen werden soll.
    PRUEFE(kern::schritt::parameter_pruefsumme(mit_pfad)
           == kern::schritt::parameter_pruefsumme(KONSTANTEN_DER_PROBE));

    constexpr i64 VORRUNDE = 17;
    const Zustand vorher = ausgangslage(VORRUNDE);
    PRUEFE(vorher.lies(ZIEL) == musterwert(ZIEL));

    const Rundenergebnis ergebnis =
        kern::schritt::schritt(vorher, {}, mit_pfad, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    // **Bedingung 1.** Die Zahl aus dem Traeger steht in der Adresse. Ein vortragender
    // Rumpf laesst hier `musterwert(ZIEL)` stehen und wird rot.
    PRUEFE(nachher.lies(ZIEL) == PFADWERT_DER_PROBE);

    // **Bedingung 2.** Das vierte Instrument traegt vor -- vor der Runde wie danach
    // derselbe Wert, und der ist der aus der Lage und nicht der aus dem Traeger.
    PRUEFE(nachher.lies(VIERTES) == vorher.lies(VIERTES));

    // Und die Gegenprobe zur Auswahl: **Genau eine** Adresse hat sich bewegt, und es ist
    // die Zieladresse. Ohne sie saehe ein Rumpf, der den Pfadwert auf alle sechzehn
    // Staende schriebe, hier genauso aus.
    //
    // Zwei Sorten Adresse bleiben ausgenommen, und beide bewegen sich aus einem Grund,
    // den ein anderer Rumpf verantwortet: `partie.runde` zaehlt Schritt 1 hoch, und von
    // den vier Zustimmungen holt Schritt 5 zwei auf ihre Schranke -- ihre Musterwerte
    // liegen ausserhalb des Wertebereichs der Klasse 4. Beide stehen darunter mit ihrer
    // eigenen Zusicherung, statt hier mitgezaehlt zu werden.
    std::size_t bewegte = 0;
    Index erste_bewegte = FELDER;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (platz == PLATZ_RUNDE || ist_zustimmung(platz)
            || vorher.lies(platz) == nachher.lies(platz)) {
            continue;
        }
        ++bewegte;
        if (erste_bewegte == FELDER) {
            erste_bewegte = platz;
        }
    }
    PRUEFE(bewegte == 1);
    PRUEFE(erste_bewegte == ZIEL);
    PRUEFE(nachher.lies(PLATZ_RUNDE) == VORRUNDE + 1);

    // Die Zustimmung liegt auf der Klemme ihres Ausgangswertes, obwohl ein Stand sich
    // bewegt hat: Der additive Term ist ein Produkt mit `zustimmung_elastizitaet`, und
    // die steht in diesem Traeger auf null. Das ist die Zusicherung fuer die eben
    // ausgenommenen vier -- ohne sie bliebe offen, ob der bewegte Leitzins ueber
    // `politiklast` doch eine Zustimmung verschoben hat.
    std::size_t auf_der_klemme = 0;
    for (const Index platz : ZUSTIMMUNGSPLAETZE) {
        if (nachher.lies(platz) == geklemmt(vorher.lies(platz))) {
            ++auf_der_klemme;
        }
    }
    PRUEFE(auf_der_klemme == kern::zustand::LAENDER);

    std::printf("  Pfadstand: %s traegt vor der Runde %lld, der Traeger %lld, nach der "
                "Runde %lld; %s bleibt bei %lld; %zu Adresse(n) bewegt ausser "
                "partie.runde und den vier Zustimmungen, %zu von 4 Zustimmungen auf der "
                "Klemme\n",
                kern::zustand::index_zu_adresse(ZIEL),
                static_cast<long long>(vorher.lies(ZIEL)),
                static_cast<long long>(PFADWERT_DER_PROBE),
                static_cast<long long>(nachher.lies(ZIEL)),
                kern::zustand::index_zu_adresse(VIERTES),
                static_cast<long long>(nachher.lies(VIERTES)), bewegte, auf_der_klemme);
}

// ---------------------------------------------------------------------------
// Paket 0197 -- was die Zustimmung im weltlauf bewegen koennte, und was nicht
// ---------------------------------------------------------------------------
//
// `spiel.md` traegt die Zustimmungsregel seit Paket 0198 ausgeschrieben. Sie haengt
// nicht am Zustand der Vorrunde, sondern am **Instrumentenschritt dieser Runde**:
//
//     politiklast(l) = Summe ueber die vier Instrumente i:
//                        sgn( lies_neu(land.<l>.instrument.<i>.stand)
//                           - lies_alt(land.<l>.instrument.<i>.stand) ) * schaden(l, i)
//
// und darueber der Realeinkommenshub und die Zustimmung. Der Entwurf nennt den
// Grenzfall selbst die Abnahme: Bewegt sich kein Instrumentenstand, ist jedes
// Vorzeichen null, also `politiklast` null, also der Hub **genau** null -- fuer jeden
// Preis, jedes Handelsvolumen und jede Schuldenquote.
//
// Diese Probe misst die beiden Zahlen, an denen der gerechnete Rumpf haengt, und sie
// braucht den Koeffizienten `zustimmung_elastizitaet` fuer keine ihrer Aussagen. Sie war
// deshalb schon falsifizierbar, als es den Rumpf noch nicht gab, und bleibt es, wenn
// Schritt 3 rechnet.
//
// **Was sie seit Paket 0197 nicht mehr sagt: dass sich ohne Instrumentenschritt keine
// Zustimmung bewegt.** Der Satz war falsch, und der Rumpf hat es gezeigt: Die Regel
// klemmt ihren Ausgangswert auf den Wertebereich der Klasse 4, und ein Startwert
// ausserhalb bewegt sich dabei ohne jeden Instrumentenschritt. Was an seiner Stelle
// steht, ist die schaerfere Aussage -- ohne Instrumentenschritt ist die Zustimmung
// **genau** die Klemme ihres Ausgangswertes, Land fuer Land, und nicht bloss "unbewegt".

void probe_zustimmung_ohne_instrumentenschritt()
{
    const Zustand vorher = ausgangslage(11);
    const Rundenergebnis ergebnis =
        kern::schritt::schritt(vorher, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    // Erste Zahl: wie viele der 16 Instrumentenstaende sich ueber die Runde bewegt haben.
    // Heute null -- nicht mehr, weil Schritt 3 vortruege (seit Paket 0284 tut er es
    // nicht), sondern weil der Traeger dieser Probe auf den zwoelf pfadgestuetzten
    // Adressen denselben Wert fuehrt, den die Lage dort schon hat. Die Zahl wird ungleich
    // null, sobald ein Traeger etwas anderes fuehrt; `probe_pfadstand_geht_in_die_runde`
    // ist der Fall.
    std::size_t bewegte_instrumente = 0;
    for (const kern::zustand::Gebiet land : LAENDER_DER_PROBE) {
        for (const kern::zustand::Instrument welches : INSTRUMENTE_DER_PROBE) {
            const Index platz = kern::zustand::stelle_instrument(
                land, welches, kern::zustand::InstrumentFeld::Stand);
            if (vorher.lies(platz) != nachher.lies(platz)) {
                ++bewegte_instrumente;
            }
        }
    }

    // Zweite Zahl: wie viele der vier Zustimmungen auf der Klemme ihres Ausgangswertes
    // stehen -- und daneben, wie viele sich ueberhaupt bewegt haben. Die zweite Zahl wird
    // ausgedruckt und nicht geprueft; sie ist die Groesse, die vor diesem Paket die
    // Aussage trug, und sie steht hier, damit der Unterschied ablesbar bleibt.
    std::size_t bewegte_zustimmungen = 0;
    std::size_t auf_der_klemme = 0;
    for (std::size_t n = 0; n < ZUSTIMMUNGSPLAETZE.size(); ++n) {
        const Index platz = ZUSTIMMUNGSPLAETZE[n];
        if (vorher.lies(platz) != nachher.lies(platz)) {
            ++bewegte_zustimmungen;
        }
        if (nachher.lies(platz) == geklemmt(vorher.lies(platz))) {
            ++auf_der_klemme;
        }
    }

    // **Die Aussage aus `spiel.md`, als Bedingung und nicht als Behauptung ueber heute.**
    // Ohne Instrumentenschritt ist jeder additive Term null -- jedes Vorzeichen der
    // Politiklast null, damit die Last null, damit der Hub null --, und uebrig bleibt die
    // Klemme des Ausgangswertes. Umgekehrt sagt die Zeile nichts: Bewegt sich ein
    // Instrument, darf die Zustimmung anders ausfallen und muss nicht -- der Hub kann nach
    // der Rundungsregel aus T6 auf null fallen. Deshalb eine Implikation; eine
    // Gleichsetzung waere an dem Tag falsch, an dem Schritt 3 rechnet.
    PRUEFE(bewegte_instrumente != 0 || auf_der_klemme == kern::zustand::LAENDER);

    // **Die Ordnungsaussage, und sie ist der Grund, warum Schritt 5 seit Paket 0197 nicht
    // mehr in der aufsteigenden Adressrunde steht.** Die Regel liest `lies_neu` der
    // Instrumentenstaende; `lies_neu` auf eine in dieser Runde noch nicht geschriebene
    // Adresse ist nach T39 ein harter Fehler. Liegt die Zustimmung eines Landes **vor**
    // seinen Instrumentenstaenden, kaeme sie in der aufsteigenden Runde als erste an und
    // faende den neuen Stand noch nicht vor. Alle 16 Paare liegen so.
    //
    // Gemessen und nicht aus T15 abgeschrieben. Faellt die Zeile eines Tages, ist das
    // keine Verschlechterung, sondern die Nachricht, dass ein spaeteres Paket den
    // Laenderblock umgestellt hat -- dann steht der Grund fuer die Blockfassung neu zur
    // Frage, und nicht die Adressordnung zur Rueckdrehung.
    std::size_t zustimmung_vor_instrument = 0;
    for (const kern::zustand::Gebiet land : LAENDER_DER_PROBE) {
        const Index zustimmung = kern::zustand::stelle_politisch(
            land, kern::zustand::PolitischeGroesse::Zustimmung);
        for (const kern::zustand::Instrument welches : INSTRUMENTE_DER_PROBE) {
            const Index stand = kern::zustand::stelle_instrument(
                land, welches, kern::zustand::InstrumentFeld::Stand);
            if (zustimmung < stand) {
                ++zustimmung_vor_instrument;
            }
        }
    }
    PRUEFE(zustimmung_vor_instrument == 16);

    std::printf("  Instrumentenschritt: %zu von 16 Staenden bewegt, %zu von 4 Zustimmungen "
                "bewegt, %zu von 4 auf der Klemme ihres Ausgangswertes; %zu von 16 Paaren "
                "haben die Zustimmung vor ihrem Instrumentenstand\n",
                bewegte_instrumente, bewegte_zustimmungen, auf_der_klemme,
                zustimmung_vor_instrument);
}

// ---------------------------------------------------------------------------
// Paket 0197 -- der gerechnete Rumpf, unterscheidbar vom vortragenden
// ---------------------------------------------------------------------------
//
// **Diese Probe ist die tragende des Pakets, und sie ist es, weil sie den einen Fall
// baut, in dem sich die beiden Rumpfe nicht gleich verhalten koennen.** Eine Zaehlung
// bewegter Groessen leistet das nicht: Der Startzustand der uebrigen Proben legt auf zwei
// der vier Zustimmungsadressen die Zahl 1, und die liegt im Wertebereich -- eine Klemme
// laesst sie stehen, ein Vortrag ebenso.
//
// Hier liegen deshalb **alle vier** Ausgangswerte ausserhalb, zwei ueber der oberen und
// zwei unter der unteren Schranke, darunter beide Enden des Zahlbereichs. Ein Vortrag
// liesse alle vier stehen; die Regel bringt alle vier auf die Schranke, die `spiel.md`
// nennt. Vier gegen null, und dazwischen liegt keine Auslegung.
//
// **Warum jeder additive Term in dieser Runde null ist**, mit den Worten des Entwurfs:
// Bewegt sich kein Instrumentenstand, ist jedes Vorzeichen der Politiklast null, also die
// Last null, also der Realeinkommenshub null -- "fuer jeden Preis, jedes Handelsvolumen
// und jede Schuldenquote". Der Traeger dieser Probe fuehrt auf jeder pfadgestuetzten
// Adresse den Wert, den die Lage dort schon hat, also bewegt Schritt 3 keinen. Dazu
// steht `zustimmung_elastizitaet` im Traeger dieser Probe auf null, was denselben Term
// ein zweites Mal loescht. Wer die vier Zahlen unten fuer die Wirtschaft haelt, liest die
// Klemme; sie ist die ganze Bewegung dieser Runde.

void probe_zustimmung_klemmt_statt_vortrag()
{
    // Die vier Ausgangswerte und die erwartete Schranke je Land standen bis Paket 0240
    // hier und stehen seither oben bei `ZUSTIMMUNG_AUSSERHALB` -- die Probe jenes Pakets
    // braucht dieselben vier Zahlen, und ihre Aussage haengt daran, dass es dieselben
    // sind. Ausgeschrieben sind sie dort wie hier.
    constexpr i64 VORRUNDE = 5;
    const Zustand vorher = ausgangslage_mit_zustimmung(VORRUNDE, ZUSTIMMUNG_AUSSERHALB);
    const Rundenergebnis ergebnis =
        kern::schritt::schritt(vorher, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    std::size_t auf_der_schranke = 0;
    std::size_t stehen_geblieben = 0;
    for (std::size_t n = 0; n < ZUSTIMMUNGSPLAETZE.size(); ++n) {
        const Index platz = ZUSTIMMUNGSPLAETZE[n];
        const i64 start = vorher.lies(platz);
        const i64 ende = nachher.lies(platz);
        if (ende == ZUSTIMMUNG_SCHRANKE[n]) {
            ++auf_der_schranke;
        }
        if (ende == start) {
            ++stehen_geblieben;
        }
        std::printf("  %s: Start %lld -> nach der Runde %lld (Schranke der Regel %lld)\n",
                    kern::zustand::index_zu_adresse(platz), static_cast<long long>(start),
                    static_cast<long long>(ende),
                    static_cast<long long>(ZUSTIMMUNG_SCHRANKE[n]));
    }

    // Die beiden Haelften der Unterscheidung. Die erste sagt, was die Regel rechnet; die
    // zweite, dass ein Vortrag es nicht gewesen sein kann.
    PRUEFE(auf_der_schranke == kern::zustand::LAENDER);
    PRUEFE(stehen_geblieben == 0);

    // Und die Kette sagt dasselbe aus der anderen Richtung: vier Schlussglieder mit der
    // Ursache `Gegenkraft` und der Nummer 2, keines davon ein `Vortrag`.
    probe_kette(ergebnis.kette_dieser_runde, VORRUNDE + 1);

    std::printf("  Zustimmung: %zu von 4 auf der Schranke der Regel, %zu von 4 stehen "
                "geblieben -- ein Vortrag haette alle vier stehen lassen\n",
                auf_der_schranke, stehen_geblieben);
}

// ---------------------------------------------------------------------------
// Paket 0240 -- die Klemme steht hinter einer Addition, die abbricht
// ---------------------------------------------------------------------------
//
// `spiel.md` schreibt die Regel als
// `min(10.000, max(0, lies_alt(...) + mal_geteilt(...)))`. Ueber den ganzen Zahlen ist die
// innere Summe total; ueber `i64` ist sie es nicht, und `festkomma::plus` bricht nach T7
// ab -- **vor** der Klemme, die genau solche Werte auf ihre Schranke zurueckholt. Gemeldet
// hat es der Bruchtester als Befund 5 in
// `befunde/beschraenktheit-nach-schritt/bruch-2026-09-08.md`.
//
// **Verlangt war, den Verdacht zu einem reproduzierten Befund zu machen: ein additiver
// Term ungleich null auf einem Ausgangswert ausserhalb von null bis 10.000, gebaut ohne
// auf `schritt_3_politik` zu warten. Das geht nicht, und warum es nicht geht, ist die
// erste Haelfte dieser Probe.**
//
// Der vorgeschlagene Weg war, der Probe ihr eigenes `zustimmung_elastizitaet` mitzugeben
// -- seit Paket 0229 ist der Parametersatz ein Eingang der Runde. Er traegt nicht, und der
// Grund ist keine Kalibrierung, sondern Arithmetik: Der additive Term ist
// `mal_geteilt(zustimmung_elastizitaet, realeinkommenshub(l), 10.000)`, und der Hub ist
// null, solange sich kein Instrumentenstand bewegt. Ein Produkt mit dem Faktor null bleibt
// null, welchen Koeffizienten jemand auch einsetzt. **Die zwei Bedingungen des Verdachts
// sind also nicht zwei, sondern eine** -- der bewegte Instrumentenstand --, und sie ist
// die, die dieses Paket nicht anfassen darf.
//
// Haelfte 1 misst das, statt es zu behaupten: dieselbe Ausgangslage, zweimal gefahren,
// einmal mit dem Koeffizienten null und einmal mit dem groessten `int64_t`. Von den 310
// Adressen unterscheidet sich danach genau eine, und es ist `partie.parameter_pruefsumme`
// -- die Adresse, die den Koeffizienten selbst traegt. Die vier Zustimmungen stehen
// gleich, obwohl ihre Ausgangswerte beide Enden des Zahlbereichs einschliessen.
//
// Haelfte 2 baut den Fall, den die Runde nicht hergibt, an der Stelle, an der er entsteht:
// an der Addition selbst. Fuer jeden der vier Ausgangswerte und drei additive Terme steht
// da, ob `festkomma::plus` abbricht und was die Regel ueber den ganzen Zahlen gaebe. Zwei
// der zwoelf Faelle brechen ab, und in beiden ist der Wert, den die Regel verlangt, genau
// die Schranke, die die Klemme hinter der Addition geliefert haette -- 10.000 und 0. Der
// Abbruch kostet also einen Wert, der nach der Regel nie ausserhalb des Wertebereichs lag.
//
// **Wie die Kennzeichenprobe diesen Abbruch fuehrt.** Der Abbruch, den Haelfte 2 unten
// ausloest, kommt aus `festkomma::plus` und ist gar kein Riegel von `kern::schritt`. Der
// verortete Abbruch dagegen, den `src/schritt.cpp` seit diesem Paket vor die Addition
// stellt, ist einer -- nur aus keinem Zustand erreichbar, genau das misst Haelfte 1. Bis
// Paket 0248 stand er in keinem der Verzeichnisse, weil die Vollzaehligkeitshaelfte zu
// jedem Eintrag eine angekommene Meldung verlangt und er nie eine liefert. Seither steht er
// als erster Eintrag in `RIEGEL_OHNE_ZUSTAND`, dem zweiten Verzeichnis: ausgenommen von der
// Vollzaehligkeit, geprueft gegen jede fremde Meldung. Er wandert nach `ALLE_RIEGEL` an dem
// Tag, an dem Schritt 3 rechnet.

/// Ein Ausgangswert, ein additiver Term und was aus beiden wird -- ausgeschrieben und
/// nicht gerechnet, aus demselben Grund wie bei `ZUSTIMMUNG_SCHRANKE`.
struct Summenfall {
    i64 ausgangswert;
    i64 wirkung;
    /// Ob `festkomma::plus` auf diesem Paar abbricht.
    bool bricht_ab;
    /// Was `min(10.000, max(0, ausgangswert + wirkung))` ueber den ganzen Zahlen gibt --
    /// auch dort, wo die Addition auf `i64` vorher abbricht.
    i64 nach_der_regel;
};

/// Die vier Ausgangswerte aus `ZUSTIMMUNG_AUSSERHALB`, jeder mit drei additiven Termen:
/// dem einzigen, den die Runde heute hergibt, und den beiden kleinsten, die sie nicht
/// hergibt. Groessere Terme braucht es nicht -- an beiden Enden des Zahlbereichs reicht
/// eins, und in der Mitte aendert eine groessere Zahl nichts an der Aussage.
constexpr std::array<Summenfall, 12> SUMMENFAELLE = {{
    {10'001, i64{0}, false, 10'000},
    {10'001, i64{1}, false, 10'000},
    {10'001, i64{-1}, false, 10'000},
    {i64{-1}, i64{0}, false, i64{0}},
    {i64{-1}, i64{1}, false, i64{0}},
    {i64{-1}, i64{-1}, false, i64{0}},
    {kern::festkomma::I64_MAX, i64{0}, false, 10'000},
    {kern::festkomma::I64_MAX, i64{1}, true, 10'000},
    {kern::festkomma::I64_MAX, i64{-1}, false, 10'000},
    {kern::festkomma::I64_MIN, i64{0}, false, i64{0}},
    {kern::festkomma::I64_MIN, i64{1}, false, i64{0}},
    {kern::festkomma::I64_MIN, i64{-1}, true, i64{0}},
}};

void probe_klemme_hinter_der_summe()
{
    // -----------------------------------------------------------------------
    // Haelfte 1: der Koeffizient ist kein zweiter Weg zum additiven Term.
    // -----------------------------------------------------------------------
    kern::werte::Konstanten grosser_koeffizient = KONSTANTEN_DER_PROBE;
    grosser_koeffizient.zustimmung_elastizitaet = kern::festkomma::I64_MAX;

    // Die Vorbedingung der Zaehlung unten, und sie steht als Pruefung da statt als
    // Annahme: Fielen die beiden Summen zusammen, waeren die beiden Lagen Feld fuer Feld
    // gleich, die Zaehlung ergaebe null -- und die Zeile darunter meldete den falschen
    // Grund.
    PRUEFE(kern::schritt::parameter_pruefsumme(grosser_koeffizient)
           != kern::schritt::parameter_pruefsumme(KONSTANTEN_DER_PROBE));

    constexpr i64 VORRUNDE = 7;
    const Zustand mit_null = ausgangslage_mit_zustimmung(VORRUNDE, ZUSTIMMUNG_AUSSERHALB);
    const Zustand mit_gross =
        ausgangslage_mit_zustimmung(VORRUNDE, ZUSTIMMUNG_AUSSERHALB, grosser_koeffizient);

    const Zustand nach_null =
        kern::schritt::schritt(mit_null, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf)
            .neuer_zustand;
    const Zustand nach_gross =
        kern::schritt::schritt(mit_gross, {}, grosser_koeffizient, Modus::Weltlauf)
            .neuer_zustand;

    std::size_t verschiedene = 0;
    bool nur_die_parametersumme = true;
    for (Index platz = 0; platz < FELDER; ++platz) {
        if (nach_null.lies(platz) == nach_gross.lies(platz)) {
            continue;
        }
        ++verschiedene;
        if (platz != PLATZ_PARAMETERSUMME) {
            nur_die_parametersumme = false;
            std::fprintf(stderr, "  der Koeffizient bewegt %s\n",
                         kern::zustand::index_zu_adresse(platz));
        }
    }
    PRUEFE(verschiedene == 1);
    PRUEFE(nur_die_parametersumme);

    // Und dieselbe Aussage an den vier Adressen, um die es geht -- ohne sie truege die
    // Zaehlung oben allein, und eine Zaehlung sagt nicht, *welche* Adresse gleich blieb.
    std::size_t gleiche_zustimmungen = 0;
    for (const Index platz : ZUSTIMMUNGSPLAETZE) {
        if (nach_null.lies(platz) == nach_gross.lies(platz)) {
            ++gleiche_zustimmungen;
        }
    }
    PRUEFE(gleiche_zustimmungen == kern::zustand::LAENDER);

    std::printf("  Koeffizient 0 gegen %lld: %zu von %zu Adressen verschieden -- die "
                "Parametersumme, die ihn selbst traegt; %zu von 4 Zustimmungen gleich\n",
                static_cast<long long>(grosser_koeffizient.zustimmung_elastizitaet),
                verschiedene, static_cast<std::size_t>(FELDER), gleiche_zustimmungen);

    // -----------------------------------------------------------------------
    // Haelfte 2: was aus den vier Ausgangswerten wuerde, wenn der Term nicht null waere.
    // -----------------------------------------------------------------------
    std::size_t abgebrochene = 0;
    std::size_t geklemmte = 0;
    for (const Summenfall& fall : SUMMENFAELLE) {
        bool hat_abgebrochen = false;
        i64 nach_der_klemme = 0;
        try {
            nach_der_klemme =
                geklemmt(kern::festkomma::plus(fall.ausgangswert, fall.wirkung));
        } catch (const std::domain_error&) {
            hat_abgebrochen = true;
        }

        PRUEFE(hat_abgebrochen == fall.bricht_ab);
        if (hat_abgebrochen) {
            ++abgebrochene;
            std::printf("  Ausgangswert %lld, additiver Term %lld: die Addition bricht ab; "
                        "die Regel ueber den ganzen Zahlen verlangt %lld\n",
                        static_cast<long long>(fall.ausgangswert),
                        static_cast<long long>(fall.wirkung),
                        static_cast<long long>(fall.nach_der_regel));
            continue;
        }

        ++geklemmte;
        PRUEFE(nach_der_klemme == fall.nach_der_regel);
        std::printf("  Ausgangswert %lld, additiver Term %lld: die Regel gibt %lld "
                    "(erwartet %lld)\n",
                    static_cast<long long>(fall.ausgangswert),
                    static_cast<long long>(fall.wirkung),
                    static_cast<long long>(nach_der_klemme),
                    static_cast<long long>(fall.nach_der_regel));
    }

    // Zwei von zwoelf, und beide an einem Ende des Zahlbereichs. Die Zahl steht als
    // Bedingung da und nicht nur im Ausdruck: Faellt sie, hat sich das Abbruchverhalten
    // von `festkomma::plus` bewegt.
    //
    // **Sie sagt nichts darueber, ob die Menge der abbrechenden Zustaende gleich blieb**,
    // und das stand hier bis Paket 0248 falsch. Die Schleife darueber ruft `plus`
    // unmittelbar; sie laeuft gar nicht durch `kern::schritt`. Wer den verorteten Riegel
    // enger zieht, laesst die Menge der abbrechenden Zustaende wachsen, ohne dass diese
    // Zahl sich ruehrt. Getragen wird jene Aussage von Haelfte 1 oben und von
    // `probe_zustimmung_klemmt_statt_vortrag`: Beide fahren Ausgangswerte an beiden Enden
    // des Zahlbereichs durch `schritt` und verlangen, dass die Runde sie auf die Schranke
    // bringt statt abzubrechen. Wird der Riegel enger, werden **die** rot.
    PRUEFE(abgebrochene == 2);
    PRUEFE(geklemmte == SUMMENFAELLE.size() - 2);

    std::printf("  Summe der Zustimmungsregel: %zu von %zu Faellen brechen ab, %zu kommen "
                "bis zur Klemme; die beiden Abbrueche verlangten nach der Regel 10000 und "
                "0, also Werte auf der Schranke\n",
                abgebrochene, SUMMENFAELLE.size(), geklemmte);
}

// ---------------------------------------------------------------------------
// Paket 0237 -- der Nenner der Zustimmungsregel, von beiden Seiten gemessen
// ---------------------------------------------------------------------------
//
// `spiel.md` stellt an den Nenner der Zustimmungsregel eine Bedingung:
// "bip(l) > 0 is the denominator condition". Bis zum 2026-09-08 hat sie in dieser Datei
// keine einzige Runde erfuellt -- `musterwert` legt auf die zwoelf
// Wertschoepfungsadressen nur `0` und `-10.000`, also war das Bruttoinlandsprodukt jedes
// der vier Laender negativ. Gruen blieb es, weil `schritt_3_politik` damals vortrug und
// der Zaehler damit null war: eine Division, deren Vorzeichen niemand sehen konnte. Eine
// Probe einer Regel auf einem Zustand, den der Entwurf verbietet, misst nichts.
//
// Diese Probe misst die Schranke von beiden Seiten, und beide Male stehen die vier Zahlen
// im Wortlaut da:
//
//   * Die Belegung, auf der jede andere Runde dieser Datei laeuft, erfuellt die Bedingung,
//     und die Runde darauf laeuft durch.
//   * Die alte Belegung verletzt sie, und die Runde bricht ab, statt still das Vorzeichen
//     der Gegenkraft zu drehen. Ihre vier Zahlen sind zugleich der Beleg, dass der Fall
//     wirklich vorlag und nicht bloss vorliegen konnte.
//
// **Die multiplizierende Haelfte der Regel wird seit Paket 0284 betreten, und wie weit,
// steht hier.** `politiklast` ueberspringt `kern::werte::schaden`, solange sich kein
// Instrumentenstand bewegt. Bis zum 2026-09-09 konnte ihn aus dieser Datei heraus niemand
// bewegen, und zwar unabhaengig von der Ausgangslage: Der Stand kam aus
// `schritt_3_politik`, der vortrug, also war `lies_neu` an jeder der 16 Adressen genau
// `lies_alt`. Seither entscheidet der **Traeger** darueber, und
// `probe_pfadstand_geht_in_die_runde` bewegt einen Stand: Fuer jenes eine Paar aus Land
// und Instrument wird `schaden` gerechnet und die Zinszeile aus T48 Nr. 22 durchlaufen.
//
// **Was weiterhin ungemessen bleibt, und warum es kein Versaeumnis ist:** die Zeilen der
// drei anderen Instrumente und jede Wirkung der Last auf die Zustimmung. Die erste braucht
// eine Ausgangslage, auf der `handelsvolumen` und `preishub_zoll` rechnen, statt an einem
// Musterwert abzubrechen; die zweite braucht einen Koeffizienten, den niemand kalibriert
// hat. Beides sind Zuschnitte und keine Zeilen -- und eine Probe, die sich die Zahlen
// ausdenkt, misst die Erfindung.

/// Druckt die vier Bruttoinlandsprodukte einer Lage und gibt zurueck, wie viele davon
/// die Nennerbedingung erfuellen. Gedruckt wird die erste der drei Adressen, aus denen
/// `kern::werte::bip` die Summe eines Landes bildet -- sie nennt das Land und die
/// Groesse, um die es geht.
std::size_t bip_der_lage(const Zustand& welt, const char* welche)
{
    std::size_t positive = 0;
    for (std::size_t n = 0; n < LAENDER_DER_PROBE.size(); ++n) {
        const i64 inlandsprodukt = kern::werte::bip(welt, LAENDER_DER_PROBE[n]);
        if (inlandsprodukt > 0) {
            ++positive;
        }
        std::printf("  %s -- Summe ab %s: bip = %lld\n", welche,
                    kern::zustand::index_zu_adresse(
                        WERTSCHOEPFUNGSPLAETZE[n * kern::zustand::SEKTOREN]),
                    static_cast<long long>(inlandsprodukt));
    }
    return positive;
}

void probe_nenner_der_zustimmungsregel()
{
    // Seite 1: die Belegung, auf der jede andere Probe dieser Datei laeuft.
    const Zustand mit = ausgangslage(13);
    PRUEFE(bip_der_lage(mit, "Ausgangslage") == kern::zustand::LAENDER);

    // Und die Runde darauf laeuft durch. Diese Zeile steht **vor** dem Abbruch unten und
    // nicht hinter ihm: Eine Schranke, die auch auf der erlaubten Lage anschluege, waere
    // von der geprueften durch keinen Wurf zu unterscheiden.
    const Rundenergebnis ergebnis =
        kern::schritt::schritt(mit, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf);
    PRUEFE(ergebnis.neuer_zustand.lies(PLATZ_RUNDE) == 14);

    // Seite 2: dieselbe Lage mit dem Musterwert auf den zwoelf Adressen.
    const Zustand ohne = ausgangslage_ohne_wertschoepfung(13);
    PRUEFE(bip_der_lage(ohne, "Musterbelegung") == 0);

    // Der Riegel nennt die Regel und das betroffene Land, nicht nur den Nenner: Ein
    // Abbruch aus `mal_geteilt` sagte "Nenner null" und liesse offen, welche der drei
    // Zeilen der Regel ihn ausgeloest hat -- und den negativen Nenner faenge er gar nicht.
    const std::array<const char*, 2> kennzeichen = {
        {"kern::schritt", "bip(l) > 0 ist die Nennerbedingung"}};
    BRICHT_AB_MIT("Bruttoinlandsprodukt nicht positiv", Riegel::Nennerbedingung, kennzeichen,
                  [&] {
        static_cast<void>(
            kern::schritt::schritt(ohne, {}, KONSTANTEN_DER_PROBE, Modus::Weltlauf));
    });
}

// ---------------------------------------------------------------------------
// Paket 0229 -- der Parametersatz gehoert zum Zustand, und die Summe sagt es
// ---------------------------------------------------------------------------
//
// T10b bindet den Traeger an den Zustand: Die Runde bildet die Pruefsumme ueber die
// Schluesselfelder von `kern::werte::Konstanten` und haelt sie gegen
// `partie.parameter_pruefsumme`. Drei Aussagen, und keine ist ohne die anderen etwas
// wert:
//
//   1. **Jedes der sieben Schluesselfelder geht ein.** Ohne diese Aussage waere eine
//      Summe ueber drei Felder von einer ueber sieben nicht zu unterscheiden -- sie
//      passte zu ihrem Zustand genauso gut und liesse vier Regler unbewacht.
//   2. **Die beiden Jahrgangsgroessen gehen nicht ein.** Das ist der Fehler, den der
//      Pruefer von Paket 0208 hier erwartet hat, und er wird nicht gruen, sondern rot:
//      Der Zustand fuehrt vom Jahrgang nur `partie.jahrgang_id` und keine Summe ueber
//      seinen Inhalt, also gaebe es zu ihnen nichts zu vergleichen.
//   3. **Die unpassende Paarung bricht ab.** Die passende laeuft in jeder anderen Probe
//      dieser Datei durch; ohne die Gegenseite waere das keine Schranke, sondern eine
//      Rechnung, die niemand widerlegen kann.
//
// Was diese Probe **nicht** faengt: ein Feld, das erst morgen zum Traeger kommt. Die
// Liste unten und die Aufrufe in `parameter_pruefsumme` sind zwei Abschriften derselben
// Reihe, und zwei Abschriften fangen eine Auslassung in einer von beiden -- nicht eine
// Erweiterung, die in keiner steht.

/// Ein Schluesselfeld des Traegers, mit seinem Namen fuer die Fehlermeldung.
struct Schluesselfeld {
    const char* name;
    i64 kern::werte::Konstanten::*wo;
};

/// Die sieben Felder aus T10b, in der Reihenfolge, in der die Summe sie nimmt.
constexpr std::array<Schluesselfeld, 7> SCHLUESSELFELDER = {{
    {"stufenweite", &kern::werte::Konstanten::stufenweite},
    {"ausstiegsabschlag", &kern::werte::Konstanten::ausstiegsabschlag},
    {"aufschlag", &kern::werte::Konstanten::aufschlag},
    {"lobbykosten", &kern::werte::Konstanten::lobbykosten},
    {"gegenlobby_satz", &kern::werte::Konstanten::gegenlobby_satz},
    {"regulierung_last", &kern::werte::Konstanten::regulierung_last},
    {"zustimmung_elastizitaet", &kern::werte::Konstanten::zustimmung_elastizitaet},
}};

void probe_parametersatz()
{
    const i64 grundsumme = kern::schritt::parameter_pruefsumme(KONSTANTEN_DER_PROBE);

    // Die Positivkontrolle: Die Ausgangslage traegt wirklich diese Zahl. Ohne sie saehe
    // eine Ausgangslage, in der die Nachsetzung wirkungslos waere, genauso aus wie eine,
    // in der sie greift -- die Runden liefen beide durch, wenn der Riegel selbst fehlte.
    const Zustand welt = ausgangslage(4);
    PRUEFE(welt.lies(PLATZ_PARAMETERSUMME) == grundsumme);

    // Haelfte 1: jedes der sieben Schluesselfelder bewegt die Summe.
    std::size_t bewegende_felder = 0;
    const char* erstes_stummes = nullptr;
    for (const Schluesselfeld& feld : SCHLUESSELFELDER) {
        kern::werte::Konstanten geaendert = KONSTANTEN_DER_PROBE;
        geaendert.*(feld.wo) = 4711;
        if (kern::schritt::parameter_pruefsumme(geaendert) != grundsumme) {
            ++bewegende_felder;
        } else if (erstes_stummes == nullptr) {
            erstes_stummes = feld.name;
        }
    }
    PRUEFE(bewegende_felder == SCHLUESSELFELDER.size());
    if (erstes_stummes != nullptr) {
        std::fprintf(stderr, "  erstes Schluesselfeld ohne Wirkung auf die Summe: %s\n",
                     erstes_stummes);
    }

    // Haelfte 2: die Groessen des Jahrgangs bewegen sie nicht. Seit Paket 0284 sind es
    // drei; `pfadstand` steht mit dabei, und gerade er traegt die Aussage: Er ist der
    // einzige der drei, der in **jeder** Runde eine andere Zahl fuehren darf, und die
    // Summe wird in jeder Runde gegen dieselbe Zustandsadresse gehalten. Ginge er ein,
    // riesse die Bindung in der zweiten Runde einer jeden Partie.
    kern::werte::Konstanten anderer_jahrgang = KONSTANTEN_DER_PROBE;
    anderer_jahrgang.leitzins_start[0] = 300;
    anderer_jahrgang.durchgriff[0][0] = 2'500;
    anderer_jahrgang.pfadstand[0][0] = 4'711;
    PRUEFE(kern::schritt::parameter_pruefsumme(anderer_jahrgang) == grundsumme);

    std::printf("  Parametersumme %lld; %zu von %zu Schluesselfeldern bewegen sie, die "
                "drei Jahrgangsgroessen nicht\n",
                static_cast<long long>(grundsumme), bewegende_felder,
                SCHLUESSELFELDER.size());

    // Haelfte 3: die unpassende Paarung bricht ab -- ein Feld anders, alles andere
    // gleich, und die Ausgangslage ist dieselbe, die oben durchlaeuft.
    kern::werte::Konstanten fremder = KONSTANTEN_DER_PROBE;
    fremder.zustimmung_elastizitaet = 1;
    PRUEFE(kern::schritt::parameter_pruefsumme(fremder) != grundsumme);

    const std::array<const char*, 2> kennzeichen = {
        {"kern::schritt", "Pruefsumme des Parametersatzes"}};
    BRICHT_AB_MIT("fremder Parametersatz", Riegel::Parametersatz, kennzeichen, [&] {
        static_cast<void>(kern::schritt::schritt(welt, {}, fremder, Modus::Weltlauf));
    });
}

// ---------------------------------------------------------------------------
// Paket 0229 -- der Feldzaehler zaehlt Felder und nicht Zahlen
// ---------------------------------------------------------------------------
//
// Die Probe darueber laesst eine Luecke ausdruecklich offen: ein Feld, das erst morgen
// zum Traeger kommt und in keiner der beiden Abschriften steht. Seit diesem Paket steht
// in `kern/include/kern/schritt.hpp` ein `static_assert` dagegen -- er haelt die
// Feldzahl von `kern::werte::Konstanten` gegen `SUMMIERTE_FELDER` plus
// `JAHRGANGSFELDER`. Kommt ein elftes Feld dazu, uebersetzt der Kern nicht mehr.
//
// **Ein Zaehler, der immer dieselbe Zahl sagt, faengt nichts und sieht dabei genauso
// aus.** Deshalb steht `feldzahl` hier gegen Verbunde, deren Feldzahl bekannt und
// untereinander verschieden ist, und jede erwartete Zahl steht ausgeschrieben daneben:
//
//   * `KeinFeld` -- 0. Ein Zaehler, der immer mindestens eins sagt, faellt hier.
//   * `EinFeld` -- 1. Ein Zaehler, der immer null sagt, faellt hier.
//   * `ZweiFelder` -- 2.
//   * `ZahlUndReihe` -- 2. Eine Reihe ist ein Feld und nicht so viele Felder, wie sie
//     Zahlen fuehrt.
//   * `ZahlUndRohreihe` -- 2, und **dieser Fall traegt die Aussage ueber die Klammern
//     je Stelle** (Paket 0233). Bis dahin stand sie an `ZahlUndReihe`, und dort war sie
//     falsch: `Platzhalter` wandelt sich in jeden Typ um, auch in eine `std::array`,
//     also nimmt jene Reihe eine einzige Stelle -- mit Klammern wie ohne. Eine **rohe**
//     Reihe ist kein Umwandlungsziel, denn eine Umwandlungsfunktion kann kein Feld
//     zurueckgeben; nur bei ihr kann die Klammerauslassung ueberhaupt einsetzen.
//   * `NeunFelder` -- 9, die Gestalt, die der Traeger bis Paket 0284 hatte.
//   * `ZehnFelder` -- 10, dieselbe Gestalt mit einem Feld mehr, und seit Paket 0284 die
//     Gestalt des Traegers selbst. Bis dahin war sie der Fall, um dessentwillen es den
//     Riegel gibt -- der Traeger von morgen, an dem er zuschlaegt. Dieses Morgen war der
//     2026-09-09: `pfadstand` ist das zehnte Feld, und der Riegel drueben haelt es nur,
//     weil `JAHRGANGSFELDER` im selben Lauf von zwei auf drei ging. Die beiden Verbunde
//     bleiben stehen, messen aber seither beide nur noch den **Zaehler** und nicht mehr
//     den Sprung, den er faengt; der naechste, der diese Rolle traegt, hiesse
//     `ElfFelder`.
//
// Sie stehen als `static_assert` da und nicht nur als Laufzeitvergleich -- ein Zaehler,
// der erst beim Laufen zaehlt, koennte den Riegel drueben gar nicht tragen. Gedruckt
// werden sie trotzdem, wie jede andere Zahl dieser Datei.
//
// **Was ein Zaehler ohne die Klammern je Stelle saehe, ist keine Aussage, solange sie
// niemand rechnet -- also steht er daneben** (Paket 0233). `ohne_klammern` baut
// dieselbe Aufbauliste als `Verbund{P...}` statt als `Verbund{{P}...}` und ist sonst
// Zeichen fuer Zeichen der Zaehler des Kerns, bis hin zu seinem `Platzhalter`. Drei
// weitere `static_assert` messen damit den Unterschied:
//
//   * `ZahlUndRohreihe` -- 5 statt 2. Die rohe Reihe zerfaellt in ihre vier Zahlen.
//     Das ist die Auslassung, und sie ist der ganze Grund fuer die Klammern.
//   * `ZahlUndReihe` -- 2, also unveraendert.
//   * `kern::werte::Konstanten` -- 10, also ebenfalls unveraendert. Der Traeger fuehrt
//     seit Paket 0284 drei Reihen, alle drei `std::array`; die Zahl dreiunddreissig, die
//     ein Zaehler saehe, der sie aufloeste, kommt an keinem Zaehler dieses Baums heraus.
//
// **Die Klammern bleiben trotzdem, und jetzt aus einem gemessenen Grund:** Der Traeger
// hat heute keine rohe Reihe. Bekommt er eine, zaehlte ein Zaehler ohne die Klammern
// sie als vier Felder, und der Riegel drueben wuerde an einem richtigen Traeger rot.
//
// Was diese Probe **nicht** ist: ein Baum, in dem der Riegel wirklich zuschlaegt. Den
// gibt es nicht, weil der Baulauf einen Baum uebersetzt und keine Abwandlung davon;
// das Paket sagt es, und das Arbeitspaket 0208 steht dafuer seit seinem Zuschnitt auf
// blockiert. Hier ist der Zaehler gemessen und drueben seine Anwendung sichtbar --
// zwei Nachweise statt eines, jeder fuer sich lesbar.

/// Kein Feld.
struct KeinFeld {
};

/// Ein Feld.
struct EinFeld {
    i64 eins = 0;
};

/// Zwei Felder.
struct ZweiFelder {
    i64 eins = 0;
    i64 zwei = 0;
};

/// Zwei Felder, von denen das zweite eine Reihe aus vier Zahlen ist.
struct ZahlUndReihe {
    i64 eins = 0;
    std::array<i64, 4> zwei{};
};

/// Dieselbe Gestalt mit einer **rohen** Reihe -- der Fall, an dem die Klammern je Stelle
/// haengen (Paket 0233).
///
/// **Eine rohe Reihe steht hier gegen die Hausregel, und sie ist der Gegenstand der
/// Messung und keine Bequemlichkeit.** Gemessen wird nicht die Reihe, sondern wie eine
/// Aufbauliste sie behandelt: In eine `std::array` wandelt sich `Platzhalter` um, in eine
/// rohe Reihe nicht. Ein Verbund dieser Gestalt ist deshalb der einzige der sieben, an
/// dem sich die Klammerauslassung zeigen kann. Der Kern selbst fuehrt keine rohe Reihe;
/// dass er morgen eine fuehren koennte, ist der Grund, warum sie hier steht.
struct ZahlUndRohreihe {
    i64 eins = 0;
    i64 zwei[4] = {};
};

/// Die Gestalt, die der Traeger bis Paket 0284 hatte: sieben Zahlen, eine Reihe, eine
/// Reihe von Reihen. **Kein Abbild** von `kern::werte::Konstanten` -- die Namen hier
/// tragen keine Bedeutung, gemessen wird allein die Gestalt.
struct NeunFelder {
    i64 eins = 0;
    i64 zwei = 0;
    i64 drei = 0;
    i64 vier = 0;
    i64 fuenf = 0;
    i64 sechs = 0;
    i64 sieben = 0;
    std::array<i64, 4> acht{};
    std::array<std::array<i64, 2>, 5> neun{};
};

/// Dieselbe Gestalt mit einem Feld mehr -- seit Paket 0284 die Gestalt des Traegers
/// selbst und nicht mehr die von morgen. **Kein Abbild** von `kern::werte::Konstanten`,
/// aus demselben Grund wie darueber: Die Namen tragen keine Bedeutung, und die dritte
/// Reihe des Traegers hat andere Masse als die hier.
struct ZehnFelder {
    i64 eins = 0;
    i64 zwei = 0;
    i64 drei = 0;
    i64 vier = 0;
    i64 fuenf = 0;
    i64 sechs = 0;
    i64 sieben = 0;
    i64 acht = 0;
    std::array<i64, 4> neun{};
    std::array<std::array<i64, 2>, 5> zehn{};
};

static_assert(kern::schritt::feldzahl<KeinFeld> == 0, "kein Feld sind null Felder");
static_assert(kern::schritt::feldzahl<EinFeld> == 1, "ein Feld ist ein Feld");
static_assert(kern::schritt::feldzahl<ZweiFelder> == 2, "zwei Felder sind zwei Felder");
static_assert(kern::schritt::feldzahl<ZahlUndReihe> == 2,
              "eine Reihe ist ein Feld und nicht so viele Felder, wie sie Zahlen fuehrt");
static_assert(kern::schritt::feldzahl<ZahlUndRohreihe> == 2,
              "auch eine rohe Reihe ist ein Feld, solange die Aufbauliste je Stelle "
              "eigene Klammern setzt");
static_assert(kern::schritt::feldzahl<NeunFelder> == 9, "neun Felder sind neun Felder");
static_assert(kern::schritt::feldzahl<ZehnFelder> == 10, "zehn Felder sind zehn Felder");

/// Der Zaehler des Kerns ohne die Klammern je Stelle -- die Gegenprobe zur Sperre.
///
/// Er steht in dieser Datei und nicht drueben: Gebraucht wird er allein, um zu messen,
/// was die Klammern verhindern. Er benutzt denselben `Platzhalter` und dasselbe
/// `FELDSUCHE_ENDE` wie das Vorbild -- zwei Abschriften waeren zwei Stellen, die
/// auseinanderlaufen, und der Unterschied, den er zeigen soll, waere dann nicht mehr
/// allein der der Klammern.
namespace ohne_klammern {

using kern::schritt::feldzahl_intern::FELDSUCHE_ENDE;
using kern::schritt::feldzahl_intern::PlatzhalterAn;

template <typename Verbund, std::size_t... Stelle>
[[nodiscard]] consteval bool nimmt_stellen(std::index_sequence<Stelle...>) noexcept
{
    return requires { Verbund{PlatzhalterAn<Stelle>{}...}; };
}

template <typename Verbund, std::size_t Bisher = 0>
[[nodiscard]] consteval std::size_t zaehle_felder() noexcept
{
    if constexpr (Bisher < FELDSUCHE_ENDE
                  && nimmt_stellen<Verbund>(std::make_index_sequence<Bisher + 1>{})) {
        return zaehle_felder<Verbund, Bisher + 1>();
    } else {
        return Bisher;
    }
}

template <typename Verbund>
inline constexpr std::size_t feldzahl = zaehle_felder<Verbund>();

}  // namespace ohne_klammern

static_assert(ohne_klammern::feldzahl<ZahlUndRohreihe> == 5,
              "ohne die Klammern je Stelle zerfaellt die rohe Reihe in ihre vier Zahlen "
              "-- das ist die Klammerauslassung, gegen die die Klammern stehen");
static_assert(ohne_klammern::feldzahl<ZahlUndReihe> == 2,
              "eine Reihe, in die sich der Platzhalter umwandelt, nimmt eine einzige "
              "Stelle -- mit Klammern wie ohne");
static_assert(ohne_klammern::feldzahl<kern::werte::Konstanten> == 10,
              "der Traeger fuehrt drei Reihen, alle drei std::array, und zaehlt deshalb "
              "auch ohne die Klammern zehn Felder und nicht dreiunddreissig");

/// Ein Verbund mit seiner ausgeschriebenen Feldzahl, fuer die gedruckte Fassung.
struct Feldzahlfall {
    const char* was;
    std::size_t erwartet;
    std::size_t gezaehlt;
};

constexpr std::array<Feldzahlfall, 7> FELDZAHLFAELLE = {{
    {"KeinFeld", 0, kern::schritt::feldzahl<KeinFeld>},
    {"EinFeld", 1, kern::schritt::feldzahl<EinFeld>},
    {"ZweiFelder", 2, kern::schritt::feldzahl<ZweiFelder>},
    {"ZahlUndReihe", 2, kern::schritt::feldzahl<ZahlUndReihe>},
    {"ZahlUndRohreihe", 2, kern::schritt::feldzahl<ZahlUndRohreihe>},
    {"NeunFelder", 9, kern::schritt::feldzahl<NeunFelder>},
    {"ZehnFelder", 10, kern::schritt::feldzahl<ZehnFelder>},
}};

void probe_feldzahl()
{
    std::size_t stimmende = 0;
    for (const Feldzahlfall& fall : FELDZAHLFAELLE) {
        if (fall.gezaehlt == fall.erwartet) {
            ++stimmende;
        } else {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN: %s traegt %zu Felder, der Zaehler sagt %zu\n",
                         fall.was, fall.erwartet, fall.gezaehlt);
            ++fehlgeschlagen;
        }
    }
    PRUEFE(stimmende == FELDZAHLFAELLE.size());

    // Und die Anwendung: der Traeger selbst, gegen die beiden Zahlen des Riegels und
    // gegen die Liste oben in dieser Datei. Damit haengt die vierte Abschrift der
    // sieben Felder an derselben Reihe wie die dritte -- wer eine der beiden
    // hochzaehlt und die andere vergisst, wird hier rot statt drueben still.
    PRUEFE(kern::schritt::feldzahl<kern::werte::Konstanten> == 10);
    PRUEFE(kern::schritt::feldzahl<kern::werte::Konstanten>
           == kern::schritt::SUMMIERTE_FELDER + kern::schritt::JAHRGANGSFELDER);
    PRUEFE(SCHLUESSELFELDER.size() == kern::schritt::SUMMIERTE_FELDER);

    std::printf("  Feldzahl: %zu von %zu Verbunden mit bekannter Feldzahl richtig "
                "gezaehlt; der Traeger hat %zu Felder, %zu summierte und %zu des "
                "Jahrgangs\n",
                stimmende, FELDZAHLFAELLE.size(),
                kern::schritt::feldzahl<kern::werte::Konstanten>,
                kern::schritt::SUMMIERTE_FELDER, kern::schritt::JAHRGANGSFELDER);

    // Der Unterschied, den die Klammern je Stelle machen. Er steht oben als
    // `static_assert`; hier steht er, weil diese Datei ausdruckt, was sie ausrechnet.
    std::printf("  Klammern je Stelle: ohne sie zaehlt ZahlUndRohreihe %zu statt %zu; "
                "ZahlUndReihe bleibt bei %zu und der Traeger bei %zu\n",
                ohne_klammern::feldzahl<ZahlUndRohreihe>,
                kern::schritt::feldzahl<ZahlUndRohreihe>,
                ohne_klammern::feldzahl<ZahlUndReihe>,
                ohne_klammern::feldzahl<kern::werte::Konstanten>);
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
    probe_pfadstand_geht_in_die_runde();
    probe_zustimmung_ohne_instrumentenschritt();
    probe_zustimmung_klemmt_statt_vortrag();
    probe_klemme_hinter_der_summe();
    probe_nenner_der_zustimmungsregel();
    probe_parametersatz();
    probe_feldzahl();

    // Zuletzt, denn sie liest ein, was die Aufrufstellen oben hinterlassen haben: die
    // Vollzaehligkeit ueber beide Verzeichnisse und den Vergleich jeder Liste gegen jede
    // Meldung (Paket 0107, zweite Kategorie aus Paket 0248). Der Apparat steht seit
    // Paket 0244 in `kern/test/kennzeichen.hpp`; die Begruendung beider Haelften auch.
    buch.auswerten();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("schritt_probe: alle Pruefungen bestanden\n");
    return 0;
}
