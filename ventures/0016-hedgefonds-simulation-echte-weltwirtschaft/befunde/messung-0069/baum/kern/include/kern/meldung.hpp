#pragma once
//! Der Meldungsbau des Kerns -- eine Fehlermeldung, die eine Adresse und eine Zahl im
//! Wortlaut nennt.
//!
//! `festkomma::abbruch` nimmt **einen** `const char*`. Wer in einer Fehlermeldung eine
//! Adresse, eine Rundennummer oder einen Wert nennen will, muss den Text selbst
//! zusammensetzen -- und weil der Kern keine eigene Speicherverwaltung hat (T2b), heisst
//! das: Puffer fester Groesse auf dem Stapel, Laengenpruefung bei jedem Zeichen,
//! Zahlenumwandlung von Hand.
//!
//! Genau das stand seit Paket 0016 in `src/schreiber.cpp` in einem anonymen Namensraum.
//! Es steht seit Paket 0038 hier, weil die sechs Schrittpakete der Runde dieselbe Klasse
//! einzeln brauchen -- und ein Bauagent, der eine Fehlermeldungsklasse abschreibt, hat
//! sie beim naechsten Mal in zwei Fassungen, die auseinanderlaufen.
//!
//! ## Die vier nicht trivialen Stellen
//!
//! 1. **Der Betrag des kleinsten `int64_t`.** `-I64_MIN` ist in `i64` nicht darstellbar;
//!    mit `-fwrapv` ergaebe es wieder `I64_MIN` und damit eine Endlosschleife oder eine
//!    falsche Ziffernfolge. Der Betrag entsteht deshalb ueber `u64`, wo er passt.
//! 2. **Das Abschneiden statt Ueberlaufen am Pufferende.** Ist der Puffer voll, hoert
//!    `text` auf -- es gibt keinen Weg, ueber `puffer_` hinauszuschreiben, und keinen
//!    Fall, in dem die Meldung selbst zum Fehler wird. Eine abgeschnittene Diagnose ist
//!    schlechter als eine vollstaendige und unendlich viel besser als ein zerstoerter
//!    Stapelrahmen. Sie sagt seit Paket 0056 auch, **dass** sie abgeschnitten ist --
//!    das ist die vierte Stelle.
//! 3. **Die Adressform.** `adresse` schreibt die Textform nach T17 *und* die laufende
//!    Nummer aus `daten/adressen.md` -- die Textform fuer den Menschen, die Nummer fuer
//!    den, der im Verzeichnis nachschlaegt. Eine Adresse ausserhalb der 310 ist kein
//!    Absturz, sondern eine eigene Textform: Wer eine kaputte Adresse meldet, will
//!    gerade **die** Zahl sehen.
//! 4. **Die Sichtbarkeit des Abschneidens.** Eine abgeschnittene Meldung endet mitten im
//!    Wort und sieht aus wie eine vollstaendige; `laenge()` liefert dieselbe Zahl wie bei
//!    einer, die zufaellig genau `MELDUNG_ZEICHEN_MAX` misst. Teuer wird das bei `zahl`:
//!    Aus `-9223372036854775808` wuerde am Rand `-92233` -- eine **kuerzere, aber
//!    wohlgeformte** Zahl, an der nichts stutzig macht. Es gibt deshalb zwei Anzeigen,
//!    eine je Leser: `abgeschnitten()` fuer den Aufrufer, die Marke `MARKE` am Textende
//!    fuer den Menschen im Protokoll, der die Abfrage nicht kennt. Die Marke
//!    **ueberschreibt** die letzten Zeichen, statt den Puffer zu verlaengern -- ein
//!    Puffer, der beim Markieren waechst, haette dasselbe Problem nur um eine Stelle
//!    weiter hinten.
//!
//! ## Was sich gegenueber der Fassung in `src/schreiber.cpp` geaendert hat
//!
//! Genau eine Zahl: der Puffer fasst 512 statt 256 Zeichen. Die Abbrueche in
//! `src/schritt.cpp` tragen zu ihrer Prosa zusaetzlich eine Adresse (bis 47 Zeichen),
//! ihre laufende Nummer und eine Schrittnummer; bei 256 waeren die laengsten von ihnen
//! abgeschnitten worden -- also ausgerechnet die, die zwei auseinandergelaufene
//! Abschriften derselben Tabelle erklaeren sollen. Alles andere ist wortgleich
//! uebernommen; dass sich am Verhalten nichts geaendert hat, weist `schreiber_probe`
//! nach, das die Abbruchmeldungen im Wortlaut ins Protokoll schreibt.
//!
//! **Kein `sperre.hpp` hier.** Die Gleitkommasperre ist die letzte Zeile jeder
//! Kern*quelle*, nie einer `.hpp` -- ein Standardkopf, der danach eingebunden wird,
//! zerbricht daran.

#include <array>
#include <cstddef>

#include "kern/zustand.hpp"

namespace kern::meldung {

using zustand::FELDER;
using zustand::i64;
using zustand::Index;
using zustand::u64;

/// Wie viele Zeichen der Puffer fasst, Abschlussnull eingerechnet.
///
/// Oeffentlich, damit eine Probe das Abschneiden pruefen kann, ohne die Zahl
/// abzuschreiben -- eine abgeschriebene Grenze prueft nach der ersten Aenderung nichts
/// mehr.
inline constexpr std::size_t PUFFER_ZEICHEN = 512;

/// Die laengste Meldung, die vollstaendig hineinpasst.
inline constexpr std::size_t MELDUNG_ZEICHEN_MAX = PUFFER_ZEICHEN - 1;

/// Worauf eine abgeschnittene Meldung endet.
///
/// Die Marke ist fuer den Menschen im Protokoll da, `Meldung::abgeschnitten()` fuer den
/// Aufrufer. Ohne sie ist eine am Rand gekuerzte Zahl von einer echten nicht zu
/// unterscheiden -- `-92233` ist eine tadellose Zahl, auch wenn vierzehn Ziffern fehlen.
///
/// Warum eckige Klammern und nicht drei Punkte allein: Die Meldungen des Kerns sind Prosa
/// mit Zahlen und Adressen darin. Drei Punkte koennten ein Satzzeichen sein, `[...]` kann
/// keines sein.
///
/// Oeffentlich aus demselben Grund wie `PUFFER_ZEICHEN`: damit eine Probe das Ende einer
/// abgeschnittenen Meldung vergleichen kann, ohne die Marke abzuschreiben.
inline constexpr char MARKE[] = "[...]";

/// Wie viele Zeichen die Marke belegt, Abschlussnull nicht gerechnet.
///
/// Hergeleitet statt abgeschrieben: Wer `MARKE` aendert, aendert diese Zahl mit.
inline constexpr std::size_t MARKE_ZEICHEN = sizeof(MARKE) - 1;

// Die Marke ueberschreibt das Ende einer vollen Meldung. Passte sie dort nicht hinein,
// waere jedes Abschneiden ein Schreibzugriff ausserhalb des Puffers -- deshalb steht das
// hier als Zusicherung und nicht als Kommentar.
static_assert(MARKE_ZEICHEN > 0, "eine leere Marke markiert nichts");
static_assert(MARKE_ZEICHEN <= MELDUNG_ZEICHEN_MAX,
              "die Marke muss in eine volle Meldung passen");

/// Baut eine Fehlermeldung aus Textstuecken, Zahlen und Adressen zusammen.
///
/// `festkomma::abbruch` wirft den Text als Ausnahme, und die Ausnahme legt sich eine
/// eigene Abschrift an -- ein Puffer auf dem Stapel reicht also. Die uebliche Verwendung:
///
/// ```
/// Meldung meldung;
/// meldung.text("kern::schreiber::setze -- zweiter Schreibzugriff in Runde ");
/// meldung.zahl(runde_);
/// meldung.text(" auf ");
/// meldung.adresse(adresse);
/// festkomma::abbruch(meldung.fertig());
/// ```
///
/// Die Klasse bleibt ein Literaltyp: drei Felder mit fester Groesse -- `std::array`,
/// `std::size_t`, `bool` --, jedes im Kopf vorbelegt, kein eigener Destruktor, keine
/// Speicherverwaltung. Damit darf sie auch in einer `constexpr` Funktion stehen, deren
/// Abbruchzweig zur Uebersetzungszeit nie gelaufen ist.
class Meldung {
public:
    /// Haengt eine Zeichenkette an. `nullptr` ist ein leerer Anhang und kein Absturz --
    /// eine Diagnose, die selbst abstuerzt, hilft niemandem.
    constexpr void text(const char* zeichenkette)
    {
        if (zeichenkette == nullptr) {
            return;
        }
        for (std::size_t i = 0; zeichenkette[i] != '\0'; ++i) {
            if (laenge_ + 1 >= puffer_.size()) {
                // Abgeschnitten statt uebergelaufen -- und kenntlich statt still.
                abgeschnitten_ = true;
                marke_setzen();
                return;
            }
            puffer_[laenge_] = zeichenkette[i];
            ++laenge_;
            puffer_[laenge_] = '\0';
        }
    }

    /// Haengt eine Ganzzahl in Zehnerschreibweise an, `I64_MIN` eingeschlossen.
    constexpr void zahl(i64 wert)
    {
        std::array<char, 24> ziffern{};
        std::size_t stellen = 0;
        const bool negativ = wert < 0;
        // Der Betrag ueber vorzeichenlose Zahlen, damit auch der kleinste i64 geht.
        u64 rest = negativ ? (u64{0} - static_cast<u64>(wert)) : static_cast<u64>(wert);
        if (rest == 0) {
            ziffern[0] = '0';
            stellen = 1;
        }
        while (rest != 0 && stellen < ziffern.size()) {
            ziffern[stellen] = static_cast<char>('0' + static_cast<int>(rest % 10));
            ++stellen;
            rest /= 10;
        }
        // Kein eigener Merker fuer `zahl`: Vorzeichen und Ziffern gehen einzeln durch
        // `text`, und dort schlaegt der Rand zu. Genau deshalb bricht eine Zahl mitten in
        // den Ziffern statt am Stueck ab -- und genau deshalb war ihr Abschneiden bis
        // Paket 0056 die unauffaelligste Art, eine Meldung zu verlieren.
        if (negativ) {
            const char minus[2] = {'-', '\0'};
            text(minus);
        }
        while (stellen > 0) {
            --stellen;
            const char eine[2] = {ziffern[stellen], '\0'};
            text(eine);
        }
    }

    /// Haengt eine Adresse in ihrer Textform nach T17 an, dazu ihre laufende Nummer aus
    /// `daten/adressen.md` -- die Textform fuer den Menschen, die Nummer fuer den, der
    /// im Verzeichnis nachschlaegt.
    ///
    /// Nicht `constexpr`: `zustand::index_zu_adresse` ist es nicht, und der Kopf, der
    /// die 310 Textformen fuehrt, soll deshalb keine Umkehr erzwingen.
    void adresse(Index platz)
    {
        if (platz >= FELDER) {
            text("(Adresse ausserhalb der 310 Felder, Platz ");
            zahl(static_cast<i64>(platz));
            text(")");
            return;
        }
        text(zustand::index_zu_adresse(platz));
        text(" (Nr. ");
        zahl(static_cast<i64>(platz) + 1);
        text(")");
    }

    /// Der fertige Text, nullterminiert. Gueltig, solange die `Meldung` lebt.
    [[nodiscard]] constexpr const char* fertig() const { return puffer_.data(); }

    /// Wie viele Zeichen bisher darinstehen, ohne die Abschlussnull.
    ///
    /// Allein sagt diese Zahl nichts ueber Vollstaendigkeit: Eine Meldung, die genau
    /// `MELDUNG_ZEICHEN_MAX` misst, und eine, von der ein Drittel fehlt, liefern
    /// dieselbe. Dafuer ist `abgeschnitten()` da.
    [[nodiscard]] constexpr std::size_t laenge() const noexcept { return laenge_; }

    /// Ob unterwegs etwas nicht mehr in den Puffer passte.
    ///
    /// `false` heisst: Alles, was angehaengt wurde, steht auch drin. `true` heisst, dass
    /// mindestens ein Zeichen verlorenging -- und dann endet der Text auf `MARKE`.
    ///
    /// Ein Feld und kein Rueckgabewert von `text`: Die Aufrufstellen im Kern sind Ketten
    /// aus fuenf bis sieben Anhaengen. Ein Rueckgabewert je Anhang waere an jeder von
    /// ihnen zu pruefen und an keiner zu sehen.
    [[nodiscard]] constexpr bool abgeschnitten() const noexcept { return abgeschnitten_; }

private:
    /// Schreibt `MARKE` ueber die letzten Zeichen der Meldung.
    ///
    /// Ueberschreiben statt anhaengen: Gerufen wird nur aus dem Abschneidezweig von
    /// `text`, und dort ist der Puffer voll -- es ist kein Platz mehr da, an den sich
    /// etwas haengen liesse. Die Marke kostet also die letzten `MARKE_ZEICHEN` Zeichen
    /// des Textes. Das ist der Preis dafuer, dass man das Abschneiden sieht, und er ist
    /// billiger als das, was ohne sie verlorengeht: die Gewissheit, eine vollstaendige
    /// Meldung zu lesen.
    ///
    /// Mehrfach zu rufen ist folgenlos. Nach dem ersten Abschneiden kann `laenge_` nicht
    /// mehr wachsen -- der Schreibzweig verlangt Platz, den es nicht mehr gibt --, die
    /// Marke landet also jedes Mal an derselben Stelle mit denselben Zeichen.
    ///
    /// Die Laengenpruefung greift an dieser Aufrufstelle nie: `laenge_` ist hier immer
    /// `MELDUNG_ZEICHEN_MAX`, und `MARKE_ZEICHEN` ist per Zusicherung oben nicht groesser.
    /// Sie steht trotzdem da, weil ein zweiter Aufrufer sie braeuchte und niemand sie
    /// dann vermisste -- und weil ein Index in C++ ohne Pruefung nur so lange stimmt, wie
    /// die Begruendung daneben stimmt.
    constexpr void marke_setzen()
    {
        if (laenge_ < MARKE_ZEICHEN) {
            return;  // zu kurz zum Markieren -- dann lieber der volle Reststext
        }
        const std::size_t beginn = laenge_ - MARKE_ZEICHEN;
        for (std::size_t i = 0; i < MARKE_ZEICHEN; ++i) {
            if (beginn + i >= laenge_) {
                return;
            }
            puffer_[beginn + i] = MARKE[i];
        }
    }

    std::array<char, PUFFER_ZEICHEN> puffer_{};
    std::size_t laenge_ = 0;
    bool abgeschnitten_ = false;
};

}  // namespace kern::meldung
