//! Laufende Probe fuer `kern::meldung` -- die drei nicht trivialen Stellen des
//! Meldungsbaus.
//!
//! Die Klasse ist rund 65 Zeilen und sieht harmlos aus. Drei ihrer Stellen sind es
//! nicht, und genau diese drei prueft diese Datei:
//!
//!   1. **Der Betrag des kleinsten `int64_t`.** `-I64_MIN` ist in `i64` nicht
//!      darstellbar. Mit `-fwrapv` ergaebe `-wert` wieder `I64_MIN`, und die
//!      Ziffernschleife liefe entweder endlos oder schriebe eine falsche Zahl. Der
//!      Betrag entsteht deshalb ueber `u64`. Das ist keine Vermutung mehr, sobald diese
//!      Probe die zwanzig Zeichen `-9223372036854775808` Zeichen fuer Zeichen vergleicht.
//!   2. **Das Abschneiden am Pufferende.** Eine Diagnose, die den Stapelrahmen
//!      zerschlaegt, den sie beschreiben soll, ist schlimmer als gar keine. Geprueft wird
//!      an drei Stellen: eine Zeichenkette, die weit ueber den Puffer hinausgeht, eine
//!      Zahl, die mitten in ihren Ziffern anstoesst, und ein Anhang an einen bereits
//!      vollen Puffer.
//!   3. **Die Adressform.** Textform nach T17 plus laufende Nummer, und eine Adresse
//!      ausserhalb der 310 als eigene Textform statt als Absturz.
//!
//! Dazu die vierte Stelle, die keine Rechnung ist, aber jeden Aufrufer treffen wuerde:
//! `text(nullptr)` ist ein leerer Anhang.
//!
//! **Das Testprofil aus ADR 0011, Massnahme 2** gilt hier besonders: Diese Probe linkt
//! `kern_geprueft`, also dieselben Quellen mit `-fsanitize=undefined,address`. Ein
//! Schreibzugriff einen Platz hinter dem Puffer waere ohne den Adressen-Sanitizer eine
//! gruene Probe -- und ein Fehler, der sich beim Kaeufer zeigt.
//!
//! **Keine Grenze wird abgeschrieben.** Die Laenge kommt aus
//! `meldung::MELDUNG_ZEICHEN_MAX`; eine abgeschriebene Zahl prueft nach der ersten
//! Aenderung des Puffers nichts mehr, sondern nur noch sich selbst.
//!
//! Rueckgabe 0 heisst bestanden; jede fehlgeschlagene Pruefung steht mit Zeilennummer
//! auf der Standardfehlerausgabe.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "kern/festkomma.hpp"
#include "kern/meldung.hpp"
#include "kern/zustand.hpp"

#include "kern/sperre.hpp"  // T4: ab hier ist Gleitkomma ein Uebersetzungsfehler

namespace {

using kern::meldung::Meldung;
using kern::meldung::MELDUNG_ZEICHEN_MAX;
using kern::meldung::PUFFER_ZEICHEN;

using kern::zustand::FELDER;
using kern::zustand::i64;
using kern::zustand::Index;
using kern::zustand::KEIN_PLATZ;

int fehlgeschlagen = 0;

void pruefe(bool bedingung, const char* text, int zeile)
{
    if (!bedingung) {
        std::fprintf(stderr, "FEHLGESCHLAGEN Zeile %d: %s\n", zeile, text);
        ++fehlgeschlagen;
    }
}

#define PRUEFE(bedingung) pruefe((bedingung), #bedingung, __LINE__)

/// Die Laenge einer Zeichenkette -- ohne `<cstring>`, das nach `sperre.hpp` keine
/// Kernquelle mehr einbinden darf.
std::size_t laenge_von(const char* zeichenkette)
{
    std::size_t n = 0;
    while (zeichenkette[n] != '\0') {
        ++n;
    }
    return n;
}

/// Ob zwei Zeichenketten Zeichen fuer Zeichen gleich sind.
bool gleich(const char* links, const char* rechts)
{
    std::size_t i = 0;
    while (links[i] != '\0' && links[i] == rechts[i]) {
        ++i;
    }
    return links[i] == rechts[i];
}

/// Ob `nadel` in `heuhaufen` vorkommt.
bool enthaelt(const char* heuhaufen, const char* nadel)
{
    for (std::size_t i = 0; heuhaufen[i] != '\0'; ++i) {
        std::size_t j = 0;
        while (nadel[j] != '\0' && heuhaufen[i + j] == nadel[j]) {
            ++j;
        }
        if (nadel[j] == '\0') {
            return true;
        }
    }
    return nadel[0] == '\0';
}

// ---------------------------------------------------------------------------
// Stelle 1 -- der Betrag des kleinsten int64_t
// ---------------------------------------------------------------------------

void probe_zahlen()
{
    struct Fall {
        i64 wert;
        const char* erwartet;
    };

    // `I64_MIN` steht ausgeschrieben und nicht als `-9223372036854775808` gerechnet:
    // Letzteres ist im Quelltext gar kein negatives Literal, sondern ein unaeres Minus
    // auf einem zu grossen positiven -- genau die Falle, um die es hier geht.
    const std::array<Fall, 9> faelle = {
        Fall{0, "0"},
        Fall{1, "1"},
        Fall{-1, "-1"},
        Fall{9, "9"},
        Fall{-10, "-10"},
        Fall{1000, "1000"},
        Fall{kern::festkomma::I64_MAX, "9223372036854775807"},
        Fall{kern::festkomma::I64_MIN + 1, "-9223372036854775807"},
        Fall{kern::festkomma::I64_MIN, "-9223372036854775808"},
    };

    for (const Fall& fall : faelle) {
        Meldung meldung;
        meldung.zahl(fall.wert);
        const bool stimmt = gleich(meldung.fertig(), fall.erwartet);
        std::fprintf(stdout, "  zahl(%lld) = \"%s\" (erwartet \"%s\")%s\n",
                     static_cast<long long>(fall.wert), meldung.fertig(), fall.erwartet,
                     stimmt ? "" : "  <-- FALSCH");
        pruefe(stimmt, "zahl() schreibt die erwartete Ziffernfolge", __LINE__);
        pruefe(meldung.laenge() == laenge_von(fall.erwartet), "zahl() zaehlt richtig mit",
               __LINE__);
    }

    // Die Gegenprobe zur Vorzeichenfalle: Betrag von `I64_MIN` und Betrag von `I64_MAX`
    // unterscheiden sich um genau eine Endziffer. Waere der Betrag ueber `i64` gebildet,
    // stuende hier zweimal dasselbe.
    Meldung klein;
    klein.zahl(kern::festkomma::I64_MIN);
    Meldung gross;
    gross.zahl(kern::festkomma::I64_MAX);
    PRUEFE(!gleich(klein.fertig() + 1, gross.fertig()));
}

// ---------------------------------------------------------------------------
// Stelle 2 -- das Abschneiden statt Ueberlaufen am Pufferende
// ---------------------------------------------------------------------------

void probe_abschneiden()
{
    // (a) Eine Zeichenkette, die weit ueber den Puffer hinausgeht.
    //
    // Angeboten werden 1.000 Zeichen des Musters "0123456789". Der Puffer nimmt
    // `MELDUNG_ZEICHEN_MAX` davon und hoert dann auf -- nicht bei einem Vielfachen von
    // zehn, sondern mitten im Brocken, weil `text` je Zeichen prueft und nicht je Aufruf.
    Meldung lang;
    for (int n = 0; n < 100; ++n) {
        lang.text("0123456789");
    }
    PRUEFE(lang.laenge() == MELDUNG_ZEICHEN_MAX);
    PRUEFE(laenge_von(lang.fertig()) == MELDUNG_ZEICHEN_MAX);
    PRUEFE(MELDUNG_ZEICHEN_MAX + 1 == PUFFER_ZEICHEN);

    bool muster_stimmt = true;
    for (std::size_t i = 0; i < MELDUNG_ZEICHEN_MAX; ++i) {
        if (lang.fertig()[i] != static_cast<char>('0' + static_cast<int>(i % 10))) {
            muster_stimmt = false;
        }
    }
    PRUEFE(muster_stimmt);
    std::fprintf(stdout, "  abgeschnitten bei %zu von 1000 angebotenen Zeichen, letztes '%c'\n",
                 lang.laenge(), lang.fertig()[MELDUNG_ZEICHEN_MAX - 1]);

    // (b) Ein Anhang an den bereits vollen Puffer aendert nichts mehr -- weder Laenge
    //     noch Inhalt, und schon gar nicht das Byte dahinter (dafuer laeuft ASan mit).
    const char letztes = lang.fertig()[MELDUNG_ZEICHEN_MAX - 1];
    lang.text("noch etwas");
    lang.zahl(kern::festkomma::I64_MIN);
    lang.adresse(0);
    lang.text(nullptr);
    PRUEFE(lang.laenge() == MELDUNG_ZEICHEN_MAX);
    PRUEFE(lang.fertig()[MELDUNG_ZEICHEN_MAX - 1] == letztes);

    // (c) Eine Zahl, die mitten in ihren Ziffern anstoesst.
    //
    // Der Puffer wird auf `MELDUNG_ZEICHEN_MAX - 6` gefuellt, dann kommt `I64_MIN` mit
    // seinen 20 Zeichen. Sechs davon passen: `-92233`. Das ist der Fall, der `zahl`
    // vom Rest unterscheidet -- sie ruft `text` je Zeichen einzeln, und nur deshalb
    // bricht sie sauber statt am Stueck.
    Meldung knapp;
    while (knapp.laenge() < MELDUNG_ZEICHEN_MAX - 6) {
        knapp.text("x");
    }
    PRUEFE(knapp.laenge() == MELDUNG_ZEICHEN_MAX - 6);
    knapp.zahl(kern::festkomma::I64_MIN);
    PRUEFE(knapp.laenge() == MELDUNG_ZEICHEN_MAX);
    PRUEFE(gleich(knapp.fertig() + (MELDUNG_ZEICHEN_MAX - 6), "-92233"));
    std::fprintf(stdout, "  Zahl am Pufferende abgeschnitten zu \"%s\"\n",
                 knapp.fertig() + (MELDUNG_ZEICHEN_MAX - 6));

    // (d) `text(nullptr)` ist ein leerer Anhang und kein Absturz.
    Meldung leer;
    leer.text(nullptr);
    PRUEFE(leer.laenge() == 0);
    PRUEFE(gleich(leer.fertig(), ""));
}

// ---------------------------------------------------------------------------
// Stelle 3 -- die Adressform, drinnen wie draussen
// ---------------------------------------------------------------------------

void probe_adressen()
{
    // Innerhalb der 310: Textform nach T17, dann die laufende Nummer. Die Nummer ist
    // einsbasiert, der Platz nullbasiert -- die haeufigste Verwechslung an dieser
    // Stelle, und deshalb stehen beide Enden hier ausgeschrieben.
    Meldung erste;
    erste.adresse(0);
    Meldung letzte;
    letzte.adresse(FELDER - 1);
    std::fprintf(stdout, "  adresse(0)   = \"%s\"\n", erste.fertig());
    std::fprintf(stdout, "  adresse(309) = \"%s\"\n", letzte.fertig());
    PRUEFE(enthaelt(erste.fertig(), "(Nr. 1)"));
    PRUEFE(enthaelt(letzte.fertig(), "(Nr. 310)"));
    PRUEFE(gleich(erste.fertig(), "land.US.sektor.1.wertschoepfung (Nr. 1)"));

    // Ausserhalb der 310: eine eigene Textform, die genau die Zahl nennt, um die es
    // geht. Drei Faelle -- die erste unerlaubte Adresse, eine weit dahinter, und
    // `KEIN_PLATZ`, den `zustand.hpp` bewusst auf `FELDER` legt, damit eine nicht
    // ausgewertete Fehlanzeige hier landet statt im Zahlenraum.
    const std::array<Index, 3> draussen = {FELDER, FELDER + 7, KEIN_PLATZ};
    const std::array<const char*, 3> nummern = {"Platz 310", "Platz 317", "Platz 310"};

    for (std::size_t n = 0; n < draussen.size(); ++n) {
        Meldung meldung;
        meldung.adresse(draussen[n]);
        std::fprintf(stdout, "  adresse(%zu) = \"%s\"\n", draussen[n], meldung.fertig());
        pruefe(enthaelt(meldung.fertig(), "ausserhalb der 310 Felder"),
               "eine Adresse ausserhalb der 310 sagt das", __LINE__);
        pruefe(enthaelt(meldung.fertig(), nummern[n]), "und nennt die Zahl, um die es geht",
               __LINE__);
        pruefe(!enthaelt(meldung.fertig(), "(Nr. "), "ohne eine laufende Nummer zu erfinden",
               __LINE__);
    }

    // Der Grund, warum die Textform ueberhaupt in die Meldung gehoert: Ein Aufrufer
    // setzt Prosa und Adresse zusammen, und beides muss in einer Zeile lesbar bleiben.
    Meldung satz;
    satz.text("kern::probe -- zweiter Schreibzugriff in Runde ");
    satz.zahl(4);
    satz.text(" auf ");
    satz.adresse(105);
    std::fprintf(stdout, "  zusammengesetzt: \"%s\"\n", satz.fertig());
    PRUEFE(enthaelt(satz.fertig(), "Runde 4"));
    PRUEFE(enthaelt(satz.fertig(), "(Nr. 106)"));
}

}  // namespace

int main()
{
    probe_zahlen();
    probe_abschneiden();
    probe_adressen();

    if (fehlgeschlagen != 0) {
        std::fprintf(stderr, "%d Pruefung(en) fehlgeschlagen\n", fehlgeschlagen);
        return 1;
    }
    std::fprintf(stdout, "meldung_probe: alle Pruefungen bestanden\n");
    return 0;
}
