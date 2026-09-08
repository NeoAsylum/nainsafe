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
//!
//! **Und die drei Argumente sind seit dem 2026-09-07 nicht mehr die vorgeschriebenen.**
//! T10b traegt seit Paket 0208 die Form `schritt(vorrunde, aktionen, konstanten, modus)`
//! mit `konstanten` als `const kern::werte::Konstanten&`; der Kern ist ihr noch nicht
//! gefolgt, und der Traeger `kern::werte::Konstanten` fuehrt den Schluessel
//! `zustimmung_elastizitaet` bis heute nicht. Solange beides so steht, uebergibt diese
//! Probe drei Argumente, weil es kein viertes gibt -- nicht, weil drei richtig waeren.
//!
//! **Paket 0197 -- die beiden Zahlen der Zustimmung.** Die letzte Probe misst, was den
//! gerechneten Rumpf von Schritt 5 traegt: den bewegten Instrumentenschritt und die
//! Adressordnung, die ihn aus der aufsteigenden Runde heraushaelt. Beides ohne den
//! Koeffizienten, der noch keinen Weg in die Runde hat; die Begruendung steht dort.
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

/// Die Textstuecke, an denen eine Abbruchmeldung ihren Riegel zu erkennen gibt.
using Kennzeichen = std::span<const char* const>;

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
    Anzahl,
};

constexpr std::array<Riegel, 5> ALLE_RIEGEL = {Riegel::ObereRundenschranke,
                                               Riegel::RundeVorDerErsten,
                                               Riegel::StartwertSetzen,
                                               Riegel::StartwertBinden, Riegel::Spielmodus};

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
    case Riegel::Anzahl:
        break;
    }
    return "(kein Riegel)";
}

/// Was von einem Abbruch uebrig bleibt, nachdem der Fangblock zu ist.
///
/// Die Meldung wird **abgeschrieben** und nicht gemerkt: `what()` zeigt in die Ausnahme,
/// und die ist hinter der schliessenden Klammer fort. Die Kennzeichen dagegen sind
/// Zeichenkettenliterale mit statischer Lebensdauer -- von ihnen genuegen die Zeiger; nur
/// das Feld, in dem sie an der Aufrufstelle stehen, stirbt mit ihrer Funktion.
constexpr std::size_t MELDUNGEN_MAX = 16;
constexpr std::size_t MELDUNG_ZEICHEN = 512;
constexpr std::size_t KENNZEICHEN_MAX = 8;

struct Angekommen {
    Riegel riegel = Riegel::Anzahl;
    const char* was = nullptr;
    int zeile = 0;
    std::size_t anzahl = 0;
    std::array<const char*, KENNZEICHEN_MAX> kennzeichen{};
    std::array<char, MELDUNG_ZEICHEN> meldung{};
};

std::array<Angekommen, MELDUNGEN_MAX> angekommene{};
std::size_t angekommene_anzahl = 0;

/// Schreibt `quelle` nach `ziel` ab. Rueckgabe `false` heisst **abgeschnitten** -- eine
/// halbe Meldung koennte ein fremdes Kennzeichen verlieren und die Zusicherung unten
/// still schwaechen, also ist das ein Fehlschlag und keine Nebensache.
bool schreibe_ab(std::array<char, MELDUNG_ZEICHEN>& ziel, const char* quelle)
{
    std::size_t i = 0;
    while (quelle[i] != '\0' && i + 1 < ziel.size()) {
        ziel[i] = quelle[i];
        ++i;
    }
    ziel[i] = '\0';
    return quelle[i] == '\0';
}

/// Legt eine angekommene Meldung fuer die Eindeutigkeitspruefung ab.
void merke_meldung(Riegel welcher, const char* was, int zeile, Kennzeichen kennzeichen,
                   const char* angekommen)
{
    if (angekommene_anzahl >= angekommene.size()) {
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- mehr als %zu Abbruchmeldungen; die "
                     "Eindeutigkeitspruefung saehe die uebrigen nicht\n",
                     zeile, was, angekommene.size());
        ++fehlgeschlagen;
        return;
    }
    if (kennzeichen.size() > KENNZEICHEN_MAX) {
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- %zu Kennzeichen, abgelegt werden "
                     "hoechstens %zu\n",
                     zeile, was, kennzeichen.size(), KENNZEICHEN_MAX);
        ++fehlgeschlagen;
        return;
    }

    Angekommen& eintrag = angekommene[angekommene_anzahl];
    eintrag.riegel = welcher;
    eintrag.was = was;
    eintrag.zeile = zeile;
    eintrag.anzahl = kennzeichen.size();
    for (std::size_t k = 0; k < kennzeichen.size(); ++k) {
        eintrag.kennzeichen[k] = kennzeichen[k];
    }
    if (!schreibe_ab(eintrag.meldung, angekommen)) {
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- die Meldung ist laenger als %zu "
                     "Zeichen und wurde abgeschnitten\n",
                     zeile, was, MELDUNG_ZEICHEN - 1);
        ++fehlgeschlagen;
    }
    ++angekommene_anzahl;
}

/// Ob **alle** Stuecke des Eintrags in `text` vorkommen -- dieselbe Frage, die
/// `bricht_ab_mit` an der eigenen Meldung stellt, hier an einer fremden.
///
/// Eine leere Liste passt auf jeden Text. Das ist gewollt und harmlos: Der leere Fall
/// faellt schon an der Aufrufstelle auf, und ihn hier zusaetzlich durchzulassen ergaebe
/// nur eine zweite Meldung ueber dieselbe Sache.
bool liste_passt(const Angekommen& eintrag, const char* text)
{
    for (std::size_t k = 0; k < eintrag.anzahl; ++k) {
        if (!enthaelt(text, eintrag.kennzeichen[k])) {
            return false;
        }
    }
    return true;
}

/// Fuehrt `tun` aus und sichert zu, dass **dieser** Riegel abgebrochen hat -- nicht
/// irgendeiner (Paket 0085).
///
/// Der Unterschied zu einem blossen `PRUEFE(geworfen)` ist der Grund des Pakets: Die
/// Schranke gegen die nicht mehr zaehlbare Runde wird doppelt gehalten. Der aeussere
/// Riegel in `kern/src/schritt.cpp` nennt die Ursache; der innere im
/// `Schreiber`-Konstruktor sieht nur noch die negative Rundennummer, die der Umbruch
/// unter `-fwrapv` hinterlassen hat. Streicht jemand den aeusseren, wirft der innere
/// weiter -- eine Probe, die nur nach dem Wurf fragt, bleibt gruen, und der Riegel ist
/// unbemerkt weg. Dieselbe Falle steht bei `Startbelegung`, wo Binden und Setzen zwei
/// verschiedene Riegel sind, die beide `kern::zustand::Startbelegung` im Namen tragen.
///
/// **Nicht der ganze Wortlaut, sondern Stuecke.** Ein Volltextvergleich ginge bei jeder
/// Umformulierung rot und erzoege dazu, die erwartete Zeichenkette nachzuziehen statt
/// hinzusehen. Verlangt wird, was den Riegel eindeutig macht und eine Umformulierung des
/// Restes ueberlebt.
///
/// Der Fehlerfall druckt **beide** Zeichenketten, die erwartete und die angekommene:
/// Ein "falsche Meldung" ohne Wortlaut kostet den naechsten Lauf einen eigenen Bau, nur
/// um zu sehen, was denn nun ankam.
/// **Die Kennung des Riegels ist ein eigenes Argument** und nicht aus den Kennzeichen
/// erschlossen. Sie zu erschliessen ginge im Kreis: Ob zwei Stellen denselben Riegel
/// meinen, waere dann eine Aussage ueber genau die Textstuecke, deren Trennschaerfe die
/// Zusicherung erst nachweisen soll.
template <typename Aufgabe>
void bricht_ab_mit(const char* was, Riegel welcher, Kennzeichen kennzeichen, int zeile,
                   Aufgabe tun)
{
    // Ohne Kennzeichen prueft der Aufruf wieder nur, *dass* geworfen wurde -- also genau
    // das, was dieses Paket abschafft. Er faellt lieber auf, als still zu verwaessern.
    if (kennzeichen.empty()) {
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- kein Kennzeichen genannt; so prueft "
                     "die Stelle nur, dass ueberhaupt geworfen wurde\n",
                     zeile, was);
        ++fehlgeschlagen;
    }

    // Alles am Wortlaut geschieht **innerhalb** des Fangblocks: `what()` zeigt in die
    // Ausnahme, und die ist hinter der schliessenden Klammer fort.
    try {
        tun();
    } catch (const std::domain_error& fehler) {
        const char* const angekommen = fehler.what();

        // Abschreiben, bevor irgendetwas urteilt: Auch eine Stelle, die gleich als
        // "falscher Riegel" rot wird, liefert eine Meldung, gegen die die anderen Listen
        // gehalten werden. Die Zusicherung soll nicht davon abhaengen, ob der Rest dieser
        // Stelle gerade in Ordnung ist.
        merke_meldung(welcher, was, zeile, kennzeichen, angekommen);

        const char* fehlendes = nullptr;
        for (const char* const stueck : kennzeichen) {
            if (!enthaelt(angekommen, stueck)) {
                fehlendes = stueck;
                break;
            }
        }
        if (fehlendes == nullptr) {
            std::printf("  Abbruch wie erwartet (%s): %s\n", was, angekommen);
            return;
        }
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- es hat abgebrochen, aber der falsche "
                     "Riegel.\n  erwartetes Textstueck: \"%s\"\n  angekommene Meldung:   "
                     "\"%s\"\n",
                     zeile, was, fehlendes, angekommen);
        ++fehlgeschlagen;
        return;
    } catch (...) {
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- abgebrochen, aber nicht mit "
                     "std::domain_error; zu einem Wortlaut kommt die Probe so nicht\n",
                     zeile, was);
        ++fehlgeschlagen;
        return;
    }

    std::fprintf(stderr,
                 "FEHLGESCHLAGEN Zeile %d: %s -- kein Abbruch.\n  erwartet war eine "
                 "Meldung mit: \"%s\"\n  angekommen ist:         (nichts, der Aufruf kam "
                 "durch)\n",
                 zeile, was, kennzeichen.empty() ? "(keins genannt)" : kennzeichen[0]);
    ++fehlgeschlagen;
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

/// Reicht die Zeile der **Aufrufstelle** an `bricht_ab_mit` durch -- sonst naennte jede
/// Fehlermeldung die eine Zeile in der Vorlage. Variadisch, damit das Komma in einem
/// mehrzeiligen Lambda den Praeprozessor nicht in zwei Argumente teilt.
#define BRICHT_AB_MIT(was, riegel, kennzeichen, ...) \
    bricht_ab_mit((was), (riegel), (kennzeichen), __LINE__, __VA_ARGS__)

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

    // Und **welcher** Riegel (Paket 0085): "groesste int64_t" steht nur in dem, der die
    // naechste Runde vorher verweigert. Der Fangnetzriegel im `Schreiber` spraeche
    // stattdessen von einer Runde vor der ersten -- er saehe nur die Zahl, die der
    // Umbruch hinterlassen hat, und nicht ihren Grund.
    const std::array<const char*, 2> nach_der_letzten = {{"kern::schritt", "groesste int64_t"}};
    BRICHT_AB_MIT("Runde nach der letzten zaehlbaren", Riegel::ObereRundenschranke,
                  nach_der_letzten, [&] {
        static_cast<void>(kern::schritt::schritt(am_ende, {}, Modus::Weltlauf));
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

    // Die drei hinteren Stuecke sind Bedingung 7 und standen hier schon: alle 310
    // Adressen, der Modus beim Namen, die zwei Schritte ohne Paket. Vorn steht seit
    // Paket 0085 der Kasten, der geworfen hat -- er kennzeichnet den Riegel, waehrend die
    // drei anderen sagen, dass die Meldung ihren Grund nennt.
    const std::array<const char*, 4> kennzeichen = {
        {"kern::schritt", "spielmodus", "310", "kein Paket"}};
    BRICHT_AB_MIT("Modus spielmodus", Riegel::Spielmodus, kennzeichen, [&] {
        static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Spielmodus));
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
            static_cast<void>(kern::schritt::schritt(welt, {}, Modus::Weltlauf));
        });
    }
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
// und darueber `realeinkommenshub(l)` und die Zustimmung. Der Entwurf nennt den
// Grenzfall selbst die Abnahme: Bewegt sich kein Instrumentenstand, ist jedes `sgn`
// null, also `politiklast` null, also der Hub **genau** null -- fuer jeden Preis, jedes
// Handelsvolumen und jede Schuldenquote.
//
// Diese Probe misst die beiden Zahlen, an denen der gerechnete Rumpf haengt, und sie
// misst sie **ohne** ihn: den Koeffizienten `zustimmung_elastizitaet` braucht keine der
// beiden Aussagen. Was hier steht, ist deshalb heute schon falsifizierbar und bleibt es,
// wenn Schritt 3 und Schritt 5 rechnen.

/// Die vier spielbaren Laender, in der Reihenfolge aus T15.
constexpr std::array<kern::zustand::Gebiet, kern::zustand::LAENDER> LAENDER_DER_PROBE = {
    kern::zustand::Gebiet::US, kern::zustand::Gebiet::CN, kern::zustand::Gebiet::DE,
    kern::zustand::Gebiet::BR};

/// Die vier Instrumente, in der Reihenfolge aus T15.
constexpr std::array<kern::zustand::Instrument, kern::zustand::INSTRUMENTE>
    INSTRUMENTE_DER_PROBE = {
        kern::zustand::Instrument::Leitzins, kern::zustand::Instrument::Zoll,
        kern::zustand::Instrument::Haushalt, kern::zustand::Instrument::Regulierung};

void probe_zustimmung_ohne_instrumentenschritt()
{
    const Zustand vorher = ausgangslage(11);
    const Rundenergebnis ergebnis = kern::schritt::schritt(vorher, {}, Modus::Weltlauf);
    const Zustand& nachher = ergebnis.neuer_zustand;

    // Erste Zahl: wie viele der 16 Instrumentenstaende sich ueber die Runde bewegt haben.
    // Heute null, weil `schritt_3_politik` vortraegt; die Zahl wird ungleich null an dem
    // Tag, an dem Schritt 3 einen rechnenden Rumpf bekommt.
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

    // Zweite Zahl: wie viele der vier Zustimmungsadressen sich bewegt haben.
    std::size_t bewegte_zustimmungen = 0;
    for (const kern::zustand::Gebiet land : LAENDER_DER_PROBE) {
        const Index platz = kern::zustand::stelle_politisch(
            land, kern::zustand::PolitischeGroesse::Zustimmung);
        if (vorher.lies(platz) != nachher.lies(platz)) {
            ++bewegte_zustimmungen;
        }
    }

    // **Die Aussage aus `spiel.md`, als Bedingung und nicht als Behauptung ueber heute.**
    // Ohne Instrumentenschritt kann sich keine Zustimmung bewegen. Umgekehrt sagt die
    // Zeile nichts: Bewegt sich ein Instrument, darf sich Zustimmung bewegen und muss
    // nicht -- der Hub kann nach der Rundungsregel aus T6 auf null fallen. Deshalb eine
    // Implikation; eine Gleichsetzung waere an dem Tag falsch, an dem Schritt 3 rechnet.
    PRUEFE(bewegte_instrumente != 0 || bewegte_zustimmungen == 0);

    // **Die Ordnungsaussage, und sie ist der Grund, warum Schritt 5 nicht in der
    // aufsteigenden Adressrunde stehen bleiben kann.** Die Regel liest `lies_neu` der
    // Instrumentenstaende; `lies_neu` auf eine in dieser Runde noch nicht geschriebene
    // Adresse ist nach T39 ein harter Fehler. Liegt die Zustimmung eines Landes **vor**
    // seinen Instrumentenstaenden, kommt sie in der aufsteigenden Runde als erste an und
    // findet den neuen Stand noch nicht vor.
    //
    // Gemessen und nicht aus T15 abgeschrieben. Faellt die Zeile eines Tages, ist das
    // keine Verschlechterung, sondern die Nachricht, dass das Hindernis weg ist -- dann
    // gehoert dieser Kommentar gestrichen und nicht die Adressordnung zurueckgedreht.
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
                "bewegt; %zu von 16 Paaren haben die Zustimmung vor ihrem Instrumentenstand\n",
                bewegte_instrumente, bewegte_zustimmungen, zustimmung_vor_instrument);
}

// ---------------------------------------------------------------------------
// Paket 0107 -- die Kennzeichen kennzeichnen wirklich
// ---------------------------------------------------------------------------
//
// Diese Probe laeuft **zuletzt** und nicht in `bricht_ab_mit`. Der Grund ist keine
// Vorliebe: Sie vergleicht jede Liste gegen jede Meldung, also kann sie erst anfangen,
// wenn alle Meldungen da sind. Waere sie in der Vorlage, saehe die erste Stelle nur sich
// selbst und die letzte alles -- eine Zusicherung, deren Schaerfe von der Reihenfolge
// abhaengt, ist keine.
//
// Die Aussage in einem Satz: **Die Liste einer Stelle passt genau auf die Meldungen ihres
// eigenen Riegels.** Zwei Haelften, und beide werden gebraucht.
//
//   *Passt auf keine fremde.* Das ist die Haelfte, um die es dem Paket geht. Verkuerzt
//   jemand eine Liste auf ein Allerweltsstueck, passt sie sofort auch auf fremde
//   Meldungen und die Zeile wird rot, ohne dass an der Quelle etwas geaendert wurde.
//
//   *Passt auf jede eigene.* Ohne sie gaebe es einen bequemen Ausweg: Wer die verkuerzte
//   Liste behalten will, erklaert ihren Riegel kurzerhand zu dem, mit dem sie
//   kollidiert -- und die erste Haelfte schweigt, weil nur noch fremde Paare geprueft
//   werden. Diese Haelfte macht daraus einen Tausch statt eines Auswegs: Die Liste muesste
//   dann auch die Meldung des angeeigneten Riegels treffen, und genau das tut ein
//   Allerweltsstueck aus einem anderen Kasten nicht.
//
// Der naheliegende Riegel waere "mindestens zwei Textstuecke je Liste" gewesen. Er taugt
// nichts: Zwei nichtssagende Stuecke bestehen ihn.

void probe_kennzeichen_eindeutig()
{
    // Zuerst die Vollzaehligkeit. Ohne sie hoehlt jede geloeschte Abbruchstelle die
    // Zusicherung still aus -- eine Meldung, die nicht ankommt, widerspricht keiner Liste,
    // und die Probe bliebe gruen und saegte weniger.
    for (const Riegel welcher : ALLE_RIEGEL) {
        bool gesehen = false;
        for (std::size_t i = 0; i < angekommene_anzahl && !gesehen; ++i) {
            gesehen = angekommene[i].riegel == welcher;
        }
        if (!gesehen) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN: zum Riegel \"%s\" ist in diesem Lauf keine "
                         "Meldung angekommen; seine Eindeutigkeit ist ungeprueft\n",
                         riegelname(welcher));
            ++fehlgeschlagen;
        }
    }

    std::size_t fremde_paare = 0;
    std::size_t eigene_paare = 0;
    std::size_t verletzungen = 0;

    for (std::size_t i = 0; i < angekommene_anzahl; ++i) {
        const Angekommen& liste = angekommene[i];
        for (std::size_t j = 0; j < angekommene_anzahl; ++j) {
            if (i == j) {
                continue;
            }
            const Angekommen& andere = angekommene[j];
            const bool derselbe_riegel = liste.riegel == andere.riegel;
            const bool passt = liste_passt(liste, andere.meldung.data());

            if (derselbe_riegel) {
                ++eigene_paare;
                if (!passt) {
                    std::fprintf(stderr,
                                 "FEHLGESCHLAGEN Zeile %d: %s -- diese Stelle und \"%s\" "
                                 "nennen beide den Riegel \"%s\", aber die Liste der ersten "
                                 "passt nicht auf die Meldung der zweiten. Entweder sind es "
                                 "zwei Riegel und nicht einer, oder die Liste greift zu eng."
                                 "\n  fremde Meldung: \"%s\"\n",
                                 liste.zeile, liste.was, andere.was, riegelname(liste.riegel),
                                 andere.meldung.data());
                    ++fehlgeschlagen;
                    ++verletzungen;
                }
                continue;
            }

            ++fremde_paare;
            if (passt) {
                std::fprintf(stderr,
                             "FEHLGESCHLAGEN Zeile %d: %s -- die Kennzeichenliste dieser "
                             "Stelle kennzeichnet nicht: Sie passt auch auf die Meldung des "
                             "Riegels \"%s\" (Stelle \"%s\").\n  fremde Meldung: \"%s\"\n",
                             liste.zeile, liste.was, riegelname(andere.riegel), andere.was,
                             andere.meldung.data());
                ++fehlgeschlagen;
                ++verletzungen;
            }
        }
    }

    // Zwei Zaehlungen, die nicht null sein duerfen. Eine Schleife ueber null Paare laeuft
    // gruen durch und misst nichts; das ist genau der Zustand, den dieses Paket abschafft,
    // und er darf nicht durch eine spaetere Umstellung zurueckkommen.
    PRUEFE(fremde_paare > 0);
    PRUEFE(eigene_paare > 0);
    PRUEFE(verletzungen == 0);

    std::printf("  Kennzeichen: %zu Meldungen aus %zu Riegeln, %zu fremde und %zu eigene "
                "Paare geprueft, %zu Verletzung(en)\n",
                angekommene_anzahl, ALLE_RIEGEL.size(), fremde_paare, eigene_paare,
                verletzungen);
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
    probe_zustimmung_ohne_instrumentenschritt();

    // Zuletzt, denn sie liest ein, was die fuenf Aufrufstellen oben hinterlassen haben.
    probe_kennzeichen_eindeutig();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::printf("schritt_probe: alle Pruefungen bestanden\n");
    return 0;
}
