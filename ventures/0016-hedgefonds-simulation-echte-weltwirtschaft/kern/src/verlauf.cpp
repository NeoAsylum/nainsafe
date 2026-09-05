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
//! einen vollen Verlauf etwa. Geprueft wird dann von der Aussage ueber das Argument zur
//! Aussage ueber den Behaelter: erst der Wert der Rundennummer, dann ihr Verhaeltnis zur
//! Vorrunde, dann der Platz im Verlauf. Ohne festgelegte Reihenfolge haenge es an der
//! Uebersetzung, welche der Meldungen ankommt, und eine Probe auf den Wortlaut pruefte
//! dann den Zufall.

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
        meldung.text(" Runden auf, und die Runde ");
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

const Kette& Verlauf::kette_der_runde(i64 runde) const
{
    // Aufsteigend gesucht (T9), nicht ueber eine streuende Menge: Der Verlauf traegt
    // hoechstens zwanzig Runden, und eine feste Reihenfolge ist hier billiger als jede
    // Beschleunigung, die eine zweite Datenhaltung braechte.
    for (std::size_t platz = 0; platz < runden_; ++platz) {
        if (nummer_[platz] == runde) {
            return kette_[platz];
        }
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

}  // namespace kern::verlauf
