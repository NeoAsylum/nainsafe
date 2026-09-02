//! Die Rechnung zu `pruefstand/vorrat.hpp` -- **Profilliste und Strategiekern**
//! (T36, Paket 0019).
//!
//! `runde` und `spiele` sind im Kopf deklariert und stehen hier **nicht**. Das ist der
//! Schnitt zu Paket 0029 (Vorratsverfahren T43 samt Invariante) und ausdruecklich so
//! gewollt: Eine deklarierte Funktion, die niemand ruft, bricht weder die Uebersetzung
//! noch das Binden. Wer sie hier vermisst, sucht im falschen Paket; wer sie aus einer
//! Probe aufruft, macht den Kasten rot, bis 0029 gelaufen ist.
//!
//! Zwei Dinge, die dieses Modul absichtlich **nicht** tut, weil an jedem ein Befund
//! haengt:
//!
//!   1. **Es merkt sich nichts.** Kein Modulzustand, keine gespeicherte Liste, keine
//!      Zwischenablage. Die Profilliste faellt als Wert heraus und gehoert dem
//!      Aufrufer. Zwei Laeufe koennen deshalb nicht ueber eine Ablage aneinander-
//!      geraten -- dieselbe Regel wie in `kern::zufall`. Ausserhalb einer Funktion
//!      steht in dieser Datei nichts Veraenderliches.
//!   2. **Es erfindet keine Zulaessigkeit.** Welche Arten zur Wahl stehen, kommt von
//!      aussen (T32). Die Profilliste ist reine Kombinatorik ueber fuenf Ganzzahlen
//!      und kennt den `Zustand` nicht.
//!
//! Ganzzahlig durchgehend (T4). Die groesste hier vorkommende Zahl ist `BUDGET = 5`;
//! es gibt keine Multiplikation, keine Division und keinen Wert in der Naehe einer
//! Schranke -- ein `__int128`-Zwischenwert waere hier nicht Vorsorge, sondern
//! Verwirrung.

#include "pruefstand/vorrat.hpp"

#include <stdexcept>

namespace pruefstand::vorrat {

namespace {

/// Die drei Arten, aus denen der Strategiekern gebildet wird: `{1 Position,
/// 2 Beteiligung, 3 Lobby}`. Hebel (4) und Sichtbarkeit (5) gehen nach T36 **nicht**
/// ein -- sie stehen im Profil, aber nicht in der Klassifikation.
constexpr std::size_t FAMILIEN = 3;

}  // namespace

Strategiekern strategiekern(const Profil& anteile)
{
    // Der Gleichstandsbrecher steckt in dem einen Zeichen `>`: Nur ein *echt*
    // groesserer Anteil verdraengt den bisher besten, also gewinnt bei Gleichstand
    // die kleinere Kennung. Mit `>=` waere es die groessere -- eine Zeile, ein
    // anderes Verfahren.
    std::size_t bester = 0;
    for (std::size_t i = 1; i < FAMILIEN; ++i) {
        if (anteile[i] > anteile[bester]) {
            bester = i;
        }
    }

    // Befund 8, und er laesst sich nur an dieser Stelle beheben: Ist keine der drei
    // Familienarten besetzt, hat das Profil **keinen** Kern. Ein dreiwertiger Kern
    // liefe hier weiter und behauptete eine Positionsstrategie, in der keine Position
    // vorkommt.
    if (anteile[bester] == 0) {
        return Strategiekern::OHNE;
    }

    // Index 0..2 -> Kennung 1..3. Die Aufzaehlungswerte sind genau so gelegt.
    return static_cast<Strategiekern>(static_cast<int>(bester) + 1);
}

Profilliste erzeuge_profilliste()
{
    Profilliste liste{};
    std::size_t naechste = 0;

    // Vier verschachtelte Schleifen, jede aufsteigend, die fuenfte Stelle ergibt sich
    // als Rest. Genau das ist die lexikographisch aufsteigende Ordnung von
    // `(a1..a5)`: Die erste Stelle wechselt am langsamsten, und innerhalb jedes
    // Praefixes laeuft die naechste Stelle von klein nach gross. Eine Sortierung
    // hinterher waere dieselbe Reihenfolge -- und eine zweite Stelle, an der sie
    // falsch sein koennte.
    for (i64 a1 = 0; a1 <= BUDGET; ++a1) {
        for (i64 a2 = 0; a2 <= BUDGET - a1; ++a2) {
            for (i64 a3 = 0; a3 <= BUDGET - a1 - a2; ++a3) {
                for (i64 a4 = 0; a4 <= BUDGET - a1 - a2 - a3; ++a4) {
                    const i64 a5 = BUDGET - a1 - a2 - a3 - a4;

                    // Indexpruefung an der Grenze (ADR 0011). `C(9,4) = 126` ist
                    // durchgerechnet und die Schleifen erzeugen nicht mehr -- aber
                    // ein stiller Schreibzugriff hinter das Feldende ist genau die
                    // Fehlerklasse, die C++ dem Vorhaben mitbringt.
                    if (naechste >= PROFILE) {
                        throw std::logic_error(
                            "erzeuge_profilliste: mehr als PROFILE Vektoren erzeugt");
                    }

                    Profileintrag& eintrag = liste[naechste];
                    eintrag.kennung = static_cast<i64>(naechste);
                    eintrag.anteile = Profil{a1, a2, a3, a4, a5};

                    // Einmal je Profil gerechnet und mit der Liste abgelegt, nicht je
                    // Lauf neu (T36).
                    eintrag.kern = strategiekern(eintrag.anteile);

                    ++naechste;
                }
            }
        }
    }

    // Die Gegenrichtung derselben Pruefung: zu wenige waeren ebenso falsch und
    // liessen den Rest der Liste auf Nullvektoren stehen.
    if (naechste != PROFILE) {
        throw std::logic_error("erzeuge_profilliste: weniger als PROFILE Vektoren erzeugt");
    }

    return liste;
}

}  // namespace pruefstand::vorrat
