//! Die Rechnung zu `pruefstand/vorrat.hpp` -- **das Vorratsverfahren und seine
//! Invariante** (T43, Paket 0029).
//!
//! `strategiekern` und `erzeuge_profilliste` stehen nebenan in `src/vorrat.cpp` und
//! gehoeren Paket 0019. Diese Datei legt sich daneben und faesst weder jene Quelle
//! noch die `CMakeLists.txt` an; deren Glob sammelt sie von selbst ein.
//!
//! **Der Wortlaut, gegen den gebaut ist** (`spiel.md`, "Das Aktionsprofil und wie es
//! auf Aktionen wirkt"; T43 in `technik.md`):
//!
//!   1. Am Rundenanfang `vi += 3 * ai` fuer alle fuenf Arten. Die Summe waechst je
//!      Runde um 15.
//!   2. Fuer jeden der drei Steckplaetze nacheinander: unter den Arten, die in dieser
//!      Runde noch mindestens eine zulaessige Aktion haben, die mit dem groessten
//!      `vi`; bei Gleichstand die kleinere Kennung. Aktion setzen, `vi -= 5`.
//!   3. Hat keine Art eine zulaessige Aktion, bleibt der Steckplatz leer und **kein
//!      Vorrat wird verrechnet**.
//!
//! Drei Dinge, an denen je ein Satz der Vorgabe haengt und die deshalb einzeln
//! kommentiert sind:
//!
//!   - **`ai = 0` verbietet die Art nicht.** Sie geht mit `vi += 0` in die Runde und
//!     verliert damit jeden Vergleich gegen eine besetzte Art -- aber sie steht zur
//!     Wahl. Sind die besetzten Arten unzulaessig, gewinnt sie. Ein hartes Verbot
//!     liesse Profile mit Nullen ihre Steckplaetze nicht fuellen und machte Mass 2 zu
//!     einem Vergleich zwischen drei und weniger als drei Aktionen je Runde statt
//!     zwischen Strategien. Die Zulaessigkeit entscheidet, wer zur Wahl steht, der
//!     Vorrat nur, wer gewinnt.
//!   - **`vi` wird nie bei null abgeschnitten.** Er darf negativ werden, und genau
//!     daran haengt die Invariante: Nach `5k` Runden steht der Vektor wieder auf
//!     `(0,0,0,0,0)`. Ein Abschnitt bei null verschenkt die Schuld einer Art und
//!     verschiebt die Verteilung still.
//!   - **Der leere Steckplatz verrechnet nichts.** Nicht "zieht von der zuletzt
//!     gewaehlten Art ab", nicht "zieht von allen ab" -- gar nichts.
//!
//! **Es merkt sich nichts.** Ausserhalb einer Funktion steht in dieser Datei nichts
//! Veraenderliches; der Vorrat gehoert dem Aufrufer und wird als `Vorrat&`
//! durchgereicht. Zwei Laeufe koennen deshalb nicht ueber eine Ablage aneinander-
//! geraten -- dieselbe Regel wie in `src/vorrat.cpp` und in `kern::zufall`.
//!
//! **Es erfindet keine Zulaessigkeit.** Welche Arten zur Wahl stehen, kommt als
//! `Zulaessigkeit` von aussen (T32).
//!
//! Ganzzahlig durchgehend (T4). Zur Groessenordnung, damit die fehlende
//! `__int128`-Vorsorge nach ADR 0011 Massnahme 3 eine begruendete und keine
//! vergessene ist: Die einzige Multiplikation ist `ZUWACHS * ai` mit `ai <= BUDGET`,
//! also hoechstens 15 je Runde und Art; ueber die `RUNDEN_HOECHSTENS = 90` Runden
//! bleibt `|vi| <= 1350`. Es gibt keine Division und damit auch keinen
//! Multiplikation-Divisions-Zwischenwert, fuer den Massnahme 3 geschrieben ist. Ein
//! `__int128` waere hier nicht Vorsorge, sondern Verwirrung.

#include "pruefstand/vorrat.hpp"

#include <stdexcept>

namespace pruefstand::vorrat {

namespace {

/// Rueckgabewert von `waehle`, wenn keine Art zur Wahl steht. Kein gueltiger Index --
/// deshalb genau `ARTEN` und nicht `-1`: Der Wert ist derselbe Typ wie ein Index und
/// faellt trotzdem bei jeder Indexpruefung durch.
///
/// **Die einzige Deklaration auf Dateiebene in dieser Quelle, und sie ist
/// `constexpr`** -- also unveraenderlich und nach der Abnahme von Paket 0029
/// ausdruecklich zugelassen. Der Hinweis steht hier, weil der dort vorgeschriebene
/// Mustervergleich sie **nicht** findet: Sein `[a-z_][a-z0-9_]*` verlangt einen
/// kleingeschriebenen Namen, `KEINE_ART` ist gross. Ein Mustervergleich, der nichts
/// findet, ist kein Nachweis, dass nichts da ist -- die Stelle, die von Hand
/// nachzusehen ist, ist diese.
constexpr std::size_t KEINE_ART = ARTEN;

/// Die Art mit dem groessten `vi` unter den zulaessigen; bei Gleichstand die kleinere
/// Kennung. `KEINE_ART`, wenn keine zulaessig ist.
///
/// Der Gleichstandsbrecher steckt in dem einen Zeichen `>`: Die Schleife laeuft
/// aufsteigend, also verdraengt nur ein *echt* groesserer Vorrat den bisher besten,
/// und bei Gleichstand bleibt der frueher gesehene -- die kleinere Kennung. Mit `>=`
/// waere es die groessere; genau das ist die Abweichung
/// `GLEICHSTAND_NACH_GROESSERER_KENNUNG`, und sie ist deshalb eine einzige Zeile.
std::size_t waehle(const Vorrat& vorrat,
                   const Zulaessigkeit& zulaessig,
                   Abweichung abweichung)
{
    std::size_t bester = KEINE_ART;

    for (std::size_t i = 0; i < ARTEN; ++i) {
        if (!zulaessig[i]) {
            continue;
        }
        if (bester == KEINE_ART) {
            bester = i;
            continue;
        }
        if (vorrat[i] > vorrat[bester]) {
            bester = i;
        } else if (abweichung == Abweichung::GLEICHSTAND_NACH_GROESSERER_KENNUNG
                   && vorrat[i] == vorrat[bester]) {
            bester = i;
        }
    }

    return bester;
}

}  // namespace

Rundenfolge runde(Vorrat& vorrat,
                  const Profil& anteile,
                  const Zulaessigkeit& zulaessig,
                  Abweichung abweichung)
{
    Rundenfolge folge{};
    folge.fill(LEER);

    // Schritt 1: der Rundenanfang. Alle fuenf Arten, auch die unzulaessigen -- der
    // Vorrat einer Art, die in dieser Runde nicht zur Wahl steht, waechst trotzdem.
    // Sonst bekaeme eine zeitweise gesperrte Art ihre Steckplaetze nie nach, und die
    // Invariante haette eine Ausnahme, die in `spiel.md` nicht steht.
    for (std::size_t i = 0; i < ARTEN; ++i) {
        vorrat[i] += ZUWACHS * anteile[i];
    }

    // Schritt 2 und 3: die drei Steckplaetze nacheinander. `zulaessig` gilt fuer alle
    // drei gleich -- die Verengung ueber das schon gewaehlte Buendel hinweg gehoert
    // nach T32 und nicht hierher.
    for (std::size_t platz = 0; platz < STECKPLAETZE; ++platz) {
        const std::size_t gewaehlt = waehle(vorrat, zulaessig, abweichung);

        if (gewaehlt == KEINE_ART) {
            // Schritt 3. Der Steckplatz bleibt `LEER`, und es wird **nichts**
            // verrechnet. Kein `break`: Die Zulaessigkeit aendert sich innerhalb der
            // Runde nicht, also bleiben auch die restlichen Plaetze leer -- aber das
            // ist eine Folgerung ueber die Eingabe und keine Regel des Verfahrens.
            continue;
        }

        // Indexpruefung an der Grenze (ADR 0011). `waehle` liefert nur `0..ARTEN-1`
        // oder `KEINE_ART`; die Pruefung kostet einen Vergleich und faengt den Fall,
        // in dem das einmal nicht mehr stimmt -- statt hinter das Feldende zu
        // schreiben.
        if (gewaehlt >= ARTEN) {
            throw std::logic_error("runde: waehle lieferte einen ungueltigen Index");
        }

        // Kennung `1..5`, nicht der Index `0..4`. `LEER` ist 0 und damit von jeder
        // Kennung unterscheidbar.
        folge[platz] = static_cast<i64>(gewaehlt) + 1;

        vorrat[gewaehlt] -= KOSTEN;

        // Die zweite Abweichung, ebenfalls eine Zeile: der Abschnitt bei null. Sie
        // trifft nur die eben belastete Art -- "nach dem Abzug abgeschnitten".
        if (abweichung == Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN
            && vorrat[gewaehlt] < 0) {
            vorrat[gewaehlt] = 0;
        }
    }

    return folge;
}

Laufergebnis spiele(const Profil& anteile,
                    const Zulaessigkeit& zulaessig,
                    i64 runden,
                    Abweichung abweichung)
{
    // `RUNDEN_HOECHSTENS` ist der Indexschutz fuer `Laufergebnis::folge` und keine
    // Spielregel. Ein Aufruf darueber ist ein Programmierfehler des Aufrufers, kein
    // gekuerzter Lauf -- deshalb ein Wurf und keine stille Deckelung.
    if (runden < 0 || runden > static_cast<i64>(RUNDEN_HOECHSTENS)) {
        throw std::domain_error("spiele: runden liegt ausserhalb 0 .. RUNDEN_HOECHSTENS");
    }

    Laufergebnis ergebnis;
    ergebnis.runden = runden;

    // Der Vorrat faengt bei null an (`spiel.md`: "zu Partiebeginn null"); `Vorrat{}`
    // im Kopf tut das schon, die Schleife hier macht es sichtbar statt vorausgesetzt.
    for (std::size_t i = 0; i < ARTEN; ++i) {
        ergebnis.vorrat[i] = 0;
        ergebnis.gezaehlt[i] = 0;
    }
    for (Rundenfolge& leerzeile : ergebnis.folge) {
        leerzeile.fill(LEER);
    }

    for (i64 t = 0; t < runden; ++t) {
        const Rundenfolge folge =
            runde(ergebnis.vorrat, anteile, zulaessig, abweichung);

        ergebnis.folge[static_cast<std::size_t>(t)] = folge;

        for (const i64 art : folge) {
            if (art == LEER) {
                ++ergebnis.leer_geblieben;
                continue;
            }
            // Zweite Indexpruefung, an der zweiten Grenze. `runde` hat die Kennung
            // eben erst gebildet; sie hier noch einmal zu pruefen kostet nichts und
            // haelt den Schreibzugriff auf `gezaehlt` innerhalb des Feldes.
            if (art < 1 || art > static_cast<i64>(ARTEN)) {
                throw std::logic_error("spiele: runde lieferte eine ungueltige Kennung");
            }
            ++ergebnis.gezaehlt[static_cast<std::size_t>(art - 1)];
        }
    }

    return ergebnis;
}

}  // namespace pruefstand::vorrat
