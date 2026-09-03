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
//! ## Die drei nicht trivialen Stellen
//!
//! 1. **Der Betrag des kleinsten `int64_t`.** `-I64_MIN` ist in `i64` nicht darstellbar;
//!    mit `-fwrapv` ergaebe es wieder `I64_MIN` und damit eine Endlosschleife oder eine
//!    falsche Ziffernfolge. Der Betrag entsteht deshalb ueber `u64`, wo er passt.
//! 2. **Das Abschneiden statt Ueberlaufen am Pufferende.** Ist der Puffer voll, hoert
//!    `text` auf -- es gibt keinen Weg, ueber `puffer_` hinauszuschreiben, und keinen
//!    Fall, in dem die Meldung selbst zum Fehler wird. Eine abgeschnittene Diagnose ist
//!    schlechter als eine vollstaendige und unendlich viel besser als ein zerstoerter
//!    Stapelrahmen.
//! 3. **Die Adressform.** `adresse` schreibt die Textform nach T17 *und* die laufende
//!    Nummer aus `daten/adressen.md` -- die Textform fuer den Menschen, die Nummer fuer
//!    den, der im Verzeichnis nachschlaegt. Eine Adresse ausserhalb der 310 ist kein
//!    Absturz, sondern eine eigene Textform: Wer eine kaputte Adresse meldet, will
//!    gerade **die** Zahl sehen.
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
/// Die Klasse ist ein Literaltyp: `std::array` als einziges Feld, kein eigener
/// Destruktor, keine Speicherverwaltung. Damit darf sie auch in einer `constexpr`
/// Funktion stehen, deren Abbruchzweig zur Uebersetzungszeit nie gelaufen ist.
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
                return;  // abgeschnitten statt uebergelaufen
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
    [[nodiscard]] constexpr std::size_t laenge() const noexcept { return laenge_; }

private:
    std::array<char, PUFFER_ZEICHEN> puffer_{};
    std::size_t laenge_ = 0;
};

}  // namespace kern::meldung
