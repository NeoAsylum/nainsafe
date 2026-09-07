//! Der Verlauf -- die Rundenketten und die beiden harten Schranken darauf.
//!
//! Die Erklaerungen stehen im Kopf `include/kern/verlauf.hpp`. Hier steht, was nicht in
//! einen Kopf gehoert: die Abbrueche im Wortlaut und die Reihenfolge, in der sie
//! geprueft werden.
//!
//! ## Warum die Schranke je Runde hier noch einmal steht
//!
//! `kern::schreiber::Kette` traegt dieselbe Grenze und bricht ebenfalls hart ab. Die
//! Pruefung hier ist trotzdem keine Verdopplung ohne Gewinn, sondern eine doppelt
//! gehaltene Schranke mit einem Unterschied im Wortlaut: Die Kette kennt ihre
//! Rundennummer nicht -- sie ist ein Behaelter und keine Runde --, und ihre Meldung
//! kann deshalb nur sagen, dass **eine** Kette voll war. Der Verlauf weiss, welche.
//!
//! Fuer den Aufrufer ist das der Unterschied zwischen einer Meldung, mit der er die
//! Stelle findet, und einer, mit der er von vorn suchen muss. Die aeussere Pruefung
//! liegt deshalb vor der Weitergabe an die Kette; die innere bleibt als Auffanglinie
//! stehen, und welche von beiden zugeschlagen hat, unterscheidet die Probe am Wortlaut.
//!
//! ## Die Reihenfolge der Pruefungen ist festgelegt und nicht beliebig
//!
//! Ein Aufruf kann mehrere Bedingungen auf einmal verletzen -- eine Runde null auf
//! einen vollen Verlauf etwa. In `beginne_runde` wird dann von der Aussage ueber das
//! Argument zur Aussage ueber den Behaelter geprueft: erst der Wert der Rundennummer
//! (`runde < 1`), dann ihr Verhaeltnis zur Vorrunde
//! (`runde <= nummer_[runden_ - 1]`), dann der Platz im Verlauf
//! (`runden_ >= RUNDEN_KAPAZITAET`). Ohne festgelegte Reihenfolge haenge es an der
//! Uebersetzung, welche der Meldungen ankommt, und eine Probe auf den Wortlaut pruefte
//! dann den Zufall.
//!
//! In `anhaengen` ist die Reihenfolge ebenso festgelegt, laeuft aber in der
//! **Gegenrichtung**: erst die Aussage ueber den Behaelter -- ist eine Runde begonnen
//! (`runden_ == 0`), ist in ihrer Kette noch Platz
//! (`laufende.laenge() >= GLIEDER_JE_RUNDE`) --, dann die ueber das Argument
//! (`satz.runde != nummer_[runden_ - 1]`).
//!
//! Die Gegenrichtung ist dort erzwungen und nicht gewaehlt: Die beiden spaeteren
//! Pruefungen greifen selbst auf den Behaelter zu. `kette_[runden_ - 1]` und
//! `nummer_[runden_ - 1]` sind ohne begonnene Runde kein Wert, und die letzte Meldung
//! nennt die Rundennummer des Verlaufs obendrein im Wortlaut. In `beginne_runde` zwingt
//! nichts: `runde < 1` braucht vom Behaelter nichts, und die mittlere Pruefung traegt
//! ihre Bedingung an ihn mit `runden_ > 0 &&` in sich selbst, statt sie sich vorziehen
//! zu lassen.
//!
//! Die Regel hinter beiden Richtungen heisst deshalb nicht Argument vor Behaelter,
//! sondern: Jede Pruefung steht so frueh, wie ihre Operanden und ihre Meldung es
//! zulassen. Wer in `anhaengen` eine Pruefung ergaenzt, ordnet sie danach ein -- nicht
//! nach der Richtung, die hier fuer `beginne_runde` steht.

#include <cstddef>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/schreiber.hpp"
#include "kern/verlauf.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace kern::verlauf {

namespace {

using meldung::Meldung;

using schreiber::Ursache;
using schreiber::UrsacheArt;

/// Die Antwort auf "diese Kette traegt zu dieser Adresse keinen Schreibzugriff".
///
/// Sie liegt ausserhalb der Plaetze, die eine Kette vergibt -- derselbe Grund wie bei
/// `KEIN_RUNDENPLATZ` und `zustand::KEIN_PLATZ`.
constexpr std::size_t KEIN_GLIEDPLATZ = GLIEDER_JE_RUNDE;

/// Der Platz des Schreibzugriffs auf `ziel` in dieser Kette, oder `KEIN_GLIEDPLATZ`.
///
/// Der erste Treffer genuegt und ist zugleich der einzige: Nach T18 wird jede Adresse je
/// Runde hoechstens einmal geschrieben, und der zweite Schreibzugriff stirbt im
/// Schreiber, bevor ein zweites Glied entstehen kann.
std::size_t gliedplatz_von(const Kette& kette, Index ziel)
{
    for (std::size_t glied = 0; glied < kette.laenge(); ++glied) {
        if (kette.eintrag(glied).ziel == ziel) {
            return glied;
        }
    }
    return KEIN_GLIEDPLATZ;
}

/// Wohin eine Ursache zeigt: auf eine Adresse -- oder auf ein Ende.
struct Ursachenziel {
    /// Die Adresse, aus der der Wert stammt, oder `zustand::KEIN_PLATZ`, wenn die Form
    /// keine nennt.
    Index adresse = zustand::KEIN_PLATZ;
    /// Das Ende der Kette. Gilt **nur**, wenn `adresse` auf `zustand::KEIN_PLATZ` steht.
    Ende ende = Ende::Ausloeser;
};

/// Die Zuordnung der sechs Formen aus T18 auf die eine Frage, die die Aufloesung stellt:
/// Nennt diese Ursache eine Adresse, und wenn nicht -- warum endet die Kette hier?
Ursachenziel ziel_der_ursache(const Ursache& ursache)
{
    switch (ursache.art()) {
        case UrsacheArt::Vortrag:
            return {ursache.vortragsadresse(), Ende::Ausloeser};
        case UrsacheArt::Instrument:
            // Der Stand ist die Groesse, die das Instrument im Zustand fuehrt; Druck,
            // Gegendruck und Restverzoegerung sind seine Eingaben und nicht sein Wert.
            return {zustand::stelle_instrument(ursache.land(), ursache.politikinstrument(),
                                               zustand::InstrumentFeld::Stand),
                    Ende::Ausloeser};
        case UrsacheArt::Aktion:
        case UrsacheArt::Gegenkraft:
            // Das Ende, das T20 beim Namen nennt.
            return {zustand::KEIN_PLATZ, Ende::Ausloeser};
        case UrsacheArt::Jahrgang:
            return {zustand::KEIN_PLATZ, Ende::Jahrgang};
        case UrsacheArt::Marktraeumung:
            return {zustand::KEIN_PLATZ, Ende::OhneAdresse};
    }
    // Erreichbar nur ueber einen Wert ausserhalb der sechs Formen. Er kann nur aus einer
    // Umwandlung stammen, die den Erzeugern des Ursachentyps ausweicht -- und dann ist
    // ein Abbruch die richtige Antwort und kein Ersatzende.
    festkomma::abbruch("kern::verlauf -- unbekannte Ursachenform: T18 kennt sechs");
}

/// Setzt den Platz auf den Schreibzugriff **unmittelbar vor** dem uebergebenen: erst
/// innerhalb der Kette, dann in die zuletzt aufgenommene fruehere Runde, die Glieder
/// traegt. `false` heisst, dass es keinen frueheren gibt.
///
/// Das ist die Stelle, an der die Aufloesung ihr Ende beweist: Jeder Aufruf geht echt
/// zurueck, und die Zahl der Plaetze ist endlich.
bool schritt_zurueck(const Verlauf& verlauf, std::size_t& rundenplatz, std::size_t& gliedplatz)
{
    if (gliedplatz > 0) {
        --gliedplatz;
        return true;
    }
    while (rundenplatz > 0) {
        --rundenplatz;
        const std::size_t laenge = verlauf.kette(rundenplatz).laenge();
        if (laenge > 0) {
            gliedplatz = laenge - 1;
            return true;
        }
    }
    return false;
}

}  // namespace

void Verlauf::beginne_runde(i64 runde)
{
    if (runde < 1) {
        Meldung meldung;
        meldung.text("kern::verlauf -- eine Runde vor der ersten gibt es nicht; angeboten "
                     "war die Runde ");
        meldung.zahl(runde);
        meldung.text(". Rundennummern beginnen bei eins.");
        festkomma::abbruch(meldung.fertig());
    }

    if (runden_ > 0 && runde <= nummer_[runden_ - 1]) {
        Meldung meldung;
        meldung.text("kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); "
                     "angeboten war die Runde ");
        meldung.zahl(runde);
        meldung.text(", zuletzt begonnen ist die Runde ");
        meldung.zahl(nummer_[runden_ - 1]);
        meldung.text(". Eine Runde, die nicht groesser ist, koennte nur auf Kosten "
                     "einer schon aufgenommenen Kette dazukommen.");
        festkomma::abbruch(meldung.fertig());
    }

    if (runden_ >= RUNDEN_KAPAZITAET) {
        Meldung meldung;
        meldung.text("kern::verlauf -- der Verlauf ist voll: er nimmt ");
        meldung.zahl(static_cast<i64>(RUNDEN_KAPAZITAET));
        meldung.text(" Runden auf -- so viele, wie die laengste nach T40 zulaessige "
                     "Partie hat --, und die Runde ");
        meldung.zahl(runde);
        meldung.text(" waere die naechste. Eine stille Kuerzung gibt es nicht (T19).");
        festkomma::abbruch(meldung.fertig());
    }

    // Die frische Kette an den Platz: Sie beginnt leer, unabhaengig davon, was der
    // Platz vorher getragen hat.
    kette_[runden_] = Kette{};
    nummer_[runden_] = runde;
    ++runden_;
}

void Verlauf::anhaengen(const Ursachensatz& satz)
{
    if (runden_ == 0) {
        festkomma::abbruch("kern::verlauf -- es ist keine Runde begonnen; ein Glied ohne "
                           "Runde gehoert in keine Kette");
    }

    Kette& laufende = kette_[runden_ - 1];
    if (laufende.laenge() >= GLIEDER_JE_RUNDE) {
        Meldung meldung;
        meldung.text("kern::verlauf -- die Kette der Runde ");
        meldung.zahl(nummer_[runden_ - 1]);
        meldung.text(" ist voll: die Aufnahmekapazitaet je Runde betraegt ");
        meldung.zahl(static_cast<i64>(GLIEDER_JE_RUNDE));
        meldung.text(" Glieder (T19). Ein weiteres Glied waere eine stille Kuerzung.");
        festkomma::abbruch(meldung.fertig());
    }

    if (satz.runde != nummer_[runden_ - 1]) {
        Meldung meldung;
        meldung.text("kern::verlauf -- das Glied traegt die Runde ");
        meldung.zahl(satz.runde);
        meldung.text(", aufgenommen wird es unter der Runde ");
        meldung.zahl(nummer_[runden_ - 1]);
        meldung.text(". Beide Zahlen sagen dasselbe (T18), und dieser Kasten ist die "
                     "einzige Stelle, an der sie nebeneinander stehen. Laufen sie "
                     "auseinander, haelt die Rueckwaertsaufloesung aus T20 die "
                     "Ursachenrunde gegen eine fremde Rundennummer -- und tut es lautlos.");
        festkomma::abbruch(meldung.fertig());
    }

    laufende.anhaengen(satz);
}

void Verlauf::aufnehmen(i64 runde, const Kette& rundenkette)
{
    beginne_runde(runde);
    for (std::size_t glied = 0; glied < rundenkette.laenge(); ++glied) {
        anhaengen(rundenkette.eintrag(glied));
    }
}

i64 Verlauf::rundennummer(std::size_t nummer) const
{
    if (nummer >= runden_) {
        Meldung meldung;
        meldung.text("kern::verlauf -- Platz ");
        meldung.zahl(static_cast<i64>(nummer));
        meldung.text(" ausserhalb des Verlaufs; er traegt ");
        meldung.zahl(static_cast<i64>(runden_));
        meldung.text(" Runde(n).");
        festkomma::abbruch(meldung.fertig());
    }
    return nummer_[nummer];
}

const Kette& Verlauf::kette(std::size_t nummer) const
{
    if (nummer >= runden_) {
        Meldung meldung;
        meldung.text("kern::verlauf -- Platz ");
        meldung.zahl(static_cast<i64>(nummer));
        meldung.text(" ausserhalb des Verlaufs; er traegt ");
        meldung.zahl(static_cast<i64>(runden_));
        meldung.text(" Runde(n).");
        festkomma::abbruch(meldung.fertig());
    }
    return kette_[nummer];
}

std::size_t Verlauf::platz_der_runde(i64 runde) const noexcept
{
    // Aufsteigend gesucht (T9), nicht ueber eine streuende Menge: Der Verlauf traegt
    // hoechstens `RUNDEN_KAPAZITAET` Runden, und eine feste Reihenfolge ist hier
    // billiger als jede Beschleunigung, die eine zweite Datenhaltung braechte.
    for (std::size_t platz = 0; platz < runden_; ++platz) {
        if (nummer_[platz] == runde) {
            return platz;
        }
    }
    return KEIN_RUNDENPLATZ;
}

const Kette& Verlauf::kette_der_runde(i64 runde) const
{
    // Gesucht wird nur einmal, naemlich oben. Die beiden Griffe unterscheiden sich in
    // dem, was sie mit dem Fehlschlag tun, und nicht darin, wie sie suchen -- zwei
    // Schleifen koennten auseinanderlaufen, und dann faende die eine Runden, die die
    // andere nicht findet.
    const std::size_t platz = platz_der_runde(runde);
    if (platz != KEIN_RUNDENPLATZ) {
        return kette_[platz];
    }

    Meldung meldung;
    meldung.text("kern::verlauf -- zur Runde ");
    meldung.zahl(runde);
    meldung.text(" traegt der Verlauf keine Kette. Eine leere Kette an ihrer Stelle "
                 "saehe aus wie eine Runde ohne Schreibzugriffe.");
    festkomma::abbruch(meldung.fertig());
}

std::size_t Verlauf::glieder() const noexcept
{
    std::size_t summe = 0;
    for (std::size_t platz = 0; platz < runden_; ++platz) {
        summe += kette_[platz].laenge();
    }
    return summe;
}

// ---------------------------------------------------------------------------
// T20 -- die Rueckwaertsaufloesung
// ---------------------------------------------------------------------------

Aufloesung::Aufloesung(const Verlauf& verlauf, i64 runde, Index ziel) : verlauf_(verlauf)
{
    if (ziel >= zustand::FELDER) {
        // Eine Adresse ausserhalb der 310 ist ein Rechenfehler des Aufrufers und keine
        // Frage nach einer Ursache -- dieselbe Haltung wie `zustand::lies`.
        festkomma::abbruch("kern::verlauf::Aufloesung -- Adresse ausserhalb der 310 Felder");
    }

    const std::size_t rundenplatz = verlauf.platz_der_runde(runde);
    if (rundenplatz == KEIN_RUNDENPLATZ) {
        return;  // leer, beendet, `OhneEintrag` -- so stehen die Felder schon
    }

    const std::size_t gliedplatz = gliedplatz_von(verlauf.kette(rundenplatz), ziel);
    if (gliedplatz == KEIN_GLIEDPLATZ) {
        return;
    }

    rundenplatz_ = rundenplatz;
    gliedplatz_  = gliedplatz;
    glieder_     = 1;
    leer_        = false;
    beendet_     = false;
}

const Ursachensatz& Aufloesung::glied() const
{
    if (leer_) {
        festkomma::abbruch("kern::verlauf::Aufloesung -- zu diesem Anfangspunkt traegt der "
                           "Verlauf keinen Ursachensatz; die Aufloesung ist leer");
    }
    return verlauf_.kette(rundenplatz_).eintrag(gliedplatz_);
}

Ende Aufloesung::ende() const
{
    if (!beendet_) {
        festkomma::abbruch("kern::verlauf::Aufloesung -- die Kette ist noch nicht zu Ende; "
                           "ein Ende, das noch nicht feststeht, waere eine Auskunft, die "
                           "beim naechsten Schritt anders ausfaellt");
    }
    return ende_;
}

bool Aufloesung::weiter()
{
    if (beendet_) {
        return false;
    }

    // Eine Abschrift, kein Verweis: Der Platz wandert gleich weiter, und die Bezugnahme
    // zeigte dann auf das falsche Glied.
    const Ursachensatz satz = glied();

    const Ursachenziel ursprung = ziel_der_ursache(satz.ursache);
    if (ursprung.adresse == zustand::KEIN_PLATZ) {
        ende_    = ursprung.ende;
        beendet_ = true;
        return false;
    }

    // Die spaeteste Runde, in der die Ursache stehen darf. Auf `i128` gerechnet, weil
    // die Differenz zweier `i64` keine `i64` ist (ADR 0011, Massnahme 3) -- unter
    // `-fwrapv` waere der Umlauf definiert und die Schranke wohlgeformt falsch. Die
    // Vergleiche unten laufen deshalb ebenfalls auf `i128`.
    const festkomma::i128 spaetestens = static_cast<festkomma::i128>(satz.runde)
                                        - static_cast<festkomma::i128>(satz.verzoegerung);

    std::size_t rundenplatz = rundenplatz_;
    std::size_t gliedplatz  = gliedplatz_;
    while (schritt_zurueck(verlauf_, rundenplatz, gliedplatz)) {
        if (static_cast<festkomma::i128>(verlauf_.rundennummer(rundenplatz)) > spaetestens) {
            continue;  // noch innerhalb der Verzoegerung -- diese Runde zaehlt nicht
        }
        if (verlauf_.kette(rundenplatz).eintrag(gliedplatz).ziel == ursprung.adresse) {
            rundenplatz_ = rundenplatz;
            gliedplatz_  = gliedplatz;
            ++glieder_;
            return true;
        }
    }

    // Vor der ersten aufgenommenen Runde steht der Startwert, und der hat nach T18
    // ausdruecklich keinen Ursachensatz. Das ist kein Fehler, sondern der Anfang.
    ende_    = Ende::OhneVorgaenger;
    beendet_ = true;
    return false;
}

}  // namespace kern::verlauf
