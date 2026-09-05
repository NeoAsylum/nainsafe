#pragma once
//! `kern::verlauf` -- der Traeger, in dem die Rundenketten gesammelt werden.
//!
//! Vorgaben: T19 (die Kette gehoert nicht in den Zustand; die Runde liefert Zustand und
//! Kette nebeneinander, und die Sitzung sammelt die Ketten in einem Verlauf; die
//! Aufnahmekapazitaet je Runde ist fest, und ihr Erreichen ist ein harter Fehler und
//! keine stille Kuerzung), T18 (der Ursachensatz und seine sieben Felder), T9 (feste
//! Reihenfolge, keine streuende Menge). Die Sprache ist C++20 nach ADR 0011.
//!
//! ## Warum es diesen Kasten gibt
//!
//! Von T19 war die eine Haelfte gebaut: `kern::schritt::schritt` gibt ein
//! `Rundenergebnis` zurueck, und darin liegt neben dem Zustand die
//! `kette_dieser_runde`. Wer die Kette einer Runde zurueckgibt und sie niemand aufheben
//! laesst, hat sie fuer die naechste Runde verloren -- und mit ihr die Unterschiedsebene
//! aus T20, die die Kette rueckwaerts bis zur ausloesenden Aktion aufloest.
//!
//! Dieser Kasten ist der Behaelter, den T19 dafuer beim Namen nennt. Er nimmt die Ketten
//! entgegen und gibt sie zeichengleich wieder heraus. Er rechnet nichts, er loest nichts
//! auf, er gibt nichts aus.
//!
//! ## Was hier nicht steht
//!
//! Die **Rueckwaertsaufloesung** ueber mehrere Runden (T20): Sie liest den Verlauf,
//! statt in ihm zu stehen. Die **Ausgabe** in den drei Ebenen
//! (`kern::zustandsausgabe`). Die **Erzeugung** der Ketten (`kern::schreiber`,
//! `kern::schritt`) -- an einem Ursachensatz wird hier nichts geaendert, er wird
//! abgelegt. Und der **Zustand**: T19 sagt gerade, dass die Kette dort nicht hingehoert,
//! und dieser Kasten bindet den Zustandskopf nur wegen des Zahlentyps und der 310.
//!
//! ## Die beiden Kapazitaeten, und warum beide hart sind
//!
//! **Je Runde.** `GLIEDER_JE_RUNDE` ist die Zahl, die T19 fest verlangt. Sie ist
//! hergeleitet und nicht geschaetzt: Nach T18 wird jede der 310 Adressen je Runde
//! hoechstens einmal geschrieben, und jeder Schreibzugriff haengt genau einen
//! Ursachensatz an. Mehr als 310 Glieder kann eine Rundenkette deshalb nicht haben.
//!
//! **Ueber die Partie.** `RUNDEN_KAPAZITAET` ist die Partielaenge R aus spiel.md, dort
//! im Kopf der Datei unter dem Schluessel takt: eine Runde ist ein Jahr, R ist 20,
//! Startzustand 2001, Endzustand 2021. Die Ketten der Runden 1 bis 20 sind damit genau
//! die einer vollen Partie; die Runde null hat keine Kette, weil vor der ersten Runde
//! nichts geschrieben wurde.
//!
//! Der lange Lauf des Bruchtesters -- 200 Runden ohne Spieler -- ist bewusst **nicht**
//! die Bezugsgroesse. Er ist der Fall, den T19 selbst als kettenfrei ausweist: Wer nur
//! Ergebnisse zaehlt, wirft die Ketten weg und braucht keinen Verlauf. Wer ihn trotzdem
//! einen fuehren laesst, bekommt in Runde 21 einen Abbruch, der die Kapazitaet nennt --
//! und nicht neunzig Prozent einer Partie, denen man das Fehlende nicht ansieht.
//!
//! **Beide Grenzen brechen hart ab.** Das ist die eine Zusage dieses Kastens, und sie
//! ist der Grund, aus dem T19 geschrieben wurde: Eine gekuerzte Kette waere eine Luege
//! gegenueber dem Kaeufer. Ein Verlauf, der die ueberzaehlige Kette wegwirft und
//! trotzdem gruen zurueckkehrt, ist von einem vollstaendigen durch keine Messung zu
//! unterscheiden.
//!
//! ## Die Groesse des Behaelters
//!
//! Ein Verlauf traegt 20 Ketten zu je 310 Ursachensaetzen und ist damit rund ein Drittel
//! Megabyte gross -- feste Groesse, keine Zuteilung, wie jeder Behaelter des Kerns. Die
//! Schranke darauf steht unten als Zusicherung ueber die Typgroesse und nicht als
//! Kommentar: Wer die Kapazitaeten hochsetzt, ohne die Folge zu bedenken, bekommt einen
//! roten Bau.

#include <array>
#include <cstddef>

#include "kern/schreiber.hpp"
#include "kern/zustand.hpp"

namespace kern::verlauf {

using schreiber::Kette;
using schreiber::Ursachensatz;
using zustand::i64;

// ---------------------------------------------------------------------------
// Die beiden festen Kapazitaeten (T19)
// ---------------------------------------------------------------------------

/// Wie viele Runden ein Verlauf aufnimmt -- die Partielaenge R aus spiel.md.
inline constexpr std::size_t RUNDEN_KAPAZITAET = 20;

/// Wie viele Glieder die Kette **einer** Runde im Verlauf aufnimmt.
///
/// Abgeleitet und nicht abgeschrieben: Es ist dieselbe Zahl, die `kern::schreiber` fuer
/// die Kette einer Runde fuehrt. Zwei Zahlen fuer dieselbe Schranke koennten
/// auseinanderlaufen, und dann pruefte die eine Stelle etwas anderes als die andere.
inline constexpr std::size_t GLIEDER_JE_RUNDE = schreiber::KETTE_KAPAZITAET;

static_assert(GLIEDER_JE_RUNDE == zustand::FELDER,
              "T18: hoechstens ein Schreibzugriff je Adresse, also hoechstens 310 Glieder");

// ---------------------------------------------------------------------------
// Der Verlauf
// ---------------------------------------------------------------------------

/// Die Ketten einer Partie, Runde fuer Runde, in aufsteigender Rundenfolge.
///
/// **Zwei Wege hinein, eine Schranke.** `aufnehmen` nimmt eine ganze Rundenkette
/// entgegen -- das ist der Weg, den eine Sitzung mit dem `Rundenergebnis` in der Hand
/// nimmt. `beginne_runde` und `anhaengen` sind derselbe Weg in Einzelschritten, fuer
/// einen Aufrufer, der die Glieder erzeugt, waehrend die Runde laeuft. `aufnehmen`
/// laeuft ueber die beiden anderen und nicht daneben: Die Kapazitaetspruefung liegt
/// damit an genau einer Stelle, und kein Weg kommt an ihr vorbei.
///
/// **Die Runden steigen streng an** (T9). Eine Runde, die nicht groesser ist als die
/// zuletzt aufgenommene, ist ein harter Fehler und kein Ueberschreiben: Zweimal
/// dieselbe Runde aufzunehmen hiesse, eine der beiden Ketten zu verlieren, und genau
/// dagegen ist T19 geschrieben. Rundennummern beginnen bei eins -- vor der ersten Runde
/// wurde nichts geschrieben, es gibt dort also keine Kette.
///
/// **Die zuletzt begonnene Runde bleibt offen.** Nach `aufnehmen` haengt ein weiteres
/// `anhaengen` an dieselbe Runde an; geschlossen wird eine Runde erst dadurch, dass die
/// naechste beginnt. Das ist gewollt: Dieser Kasten kennt kein Rundenende, das er
/// pruefen koennte -- die zweiseitige Maskenpruefung dazu gehoert `kern::schreiber`.
///
/// **Es gibt keinen Weg heraus ausser dem Lesen.** Kein Loeschen, kein Zuruecksetzen,
/// kein Ueberschreiben. Ein Verlauf, dessen Inhalt sich nachtraeglich aendern liesse,
/// waere als Nachweis wertlos.
class Verlauf {
public:
    /// Beginnt die Kette der Runde `runde`.
    ///
    /// Drei harte Fehler, in dieser Reihenfolge geprueft und jeder mit eigener Meldung:
    ///   * `runde` ist kleiner als eins -- eine Runde vor der ersten gibt es nicht.
    ///   * `runde` ist nicht groesser als die zuletzt begonnene.
    ///   * der Verlauf traegt bereits `RUNDEN_KAPAZITAET` Runden.
    void beginne_runde(i64 runde);

    /// Haengt ein Glied an die zuletzt begonnene Runde.
    ///
    /// Zwei harte Fehler:
    ///   * es ist noch keine Runde begonnen;
    ///   * die Runde traegt bereits `GLIEDER_JE_RUNDE` Glieder. Die Meldung nennt die
    ///     Rundennummer und die Kapazitaet, denn ohne beides sagt sie dem Aufrufer
    ///     nicht, welche Kette wie weit gefuellt war.
    void anhaengen(const Ursachensatz& satz);

    /// Nimmt die Kette einer ganzen Runde auf -- `beginne_runde` und danach jedes Glied
    /// in der Reihenfolge, in der es in der Kette steht.
    void aufnehmen(i64 runde, const Kette& kette);

    /// Wie viele Runden der Verlauf traegt.
    [[nodiscard]] std::size_t runden() const noexcept { return runden_; }

    /// Die Rundennummer der `nummer`-ten aufgenommenen Runde, ab null gezaehlt.
    /// Ein Platz ausserhalb bricht ab.
    [[nodiscard]] i64 rundennummer(std::size_t nummer) const;

    /// Die Kette der `nummer`-ten aufgenommenen Runde, ab null gezaehlt.
    /// Ein Platz ausserhalb bricht ab.
    [[nodiscard]] const Kette& kette(std::size_t nummer) const;

    /// Die Kette der Runde `runde`, nach ihrer Rundennummer gesucht.
    ///
    /// Eine Runde, die der Verlauf nicht traegt, bricht ab -- kein Ersatzwert und keine
    /// leere Kette, die wie eine Runde ohne Schreibzugriffe aussaehe.
    [[nodiscard]] const Kette& kette_der_runde(i64 runde) const;

    /// Wie viele Glieder der Verlauf ueber alle Runden traegt.
    [[nodiscard]] std::size_t glieder() const noexcept;

private:
    std::array<Kette, RUNDEN_KAPAZITAET> kette_{};
    std::array<i64, RUNDEN_KAPAZITAET> nummer_{};
    std::size_t runden_ = 0;
};

// Die Groesse ist eine Folge der beiden Kapazitaeten und keine eigene Entscheidung --
// sie steht hier, damit ein Heraufsetzen nicht unbemerkt ein Vielfaches daraus macht.
// Ein Verlauf gehoert damit nicht beilaeufig auf einen Stapelrahmen.
static_assert(sizeof(Verlauf) >= RUNDEN_KAPAZITAET * sizeof(Kette),
              "der Verlauf traegt seine Ketten selbst und nicht hinter einem Zeiger");
static_assert(sizeof(Verlauf) < std::size_t{512} * 1024,
              "ein Verlauf bleibt unter einem halben Megabyte");

}  // namespace kern::verlauf
