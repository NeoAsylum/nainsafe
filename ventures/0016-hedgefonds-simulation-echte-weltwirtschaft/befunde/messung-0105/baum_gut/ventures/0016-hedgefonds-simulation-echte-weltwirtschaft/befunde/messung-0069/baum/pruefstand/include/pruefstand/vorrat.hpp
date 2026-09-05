#pragma once
//! Das Vorratsverfahren (T43) und die Profilliste (T36) -- der Baustein des
//! Pruefstands, der von nichts abhaengt.
//!
//! **Was hier drin ist und warum es allein steht.** Das Verfahren rechnet mit fuenf
//! Ganzzahlen und drei Steckplaetzen. Es kennt den `Zustand` nicht, es ruft `schritt`
//! nicht auf, und `spiel.md` sagt ausdruecklich: "Es wird nie gerundet und nie
//! gezogen." Also braucht es `kern::zufall` auch nicht. Dieser Kasten linkt deshalb
//! nichts -- weder `kern` noch eine Fremdabhaengigkeit.
//!
//! **Was hier ausdruecklich nicht drin ist:** die Zulaessigkeitsliste aus T32. Welche
//! der fuenf Arten in einer Runde ueberhaupt zur Wahl stehen, ist ein *Eingabewert*
//! (`Zulaessigkeit`) und keine Rechnung dieses Moduls. Wer sie hier erfaende, baute
//! T32 ein zweites Mal und falsch.
//!
//! Alles ganzzahlig (T4). Der Vorrat wird nie bei null abgeschnitten -- er darf
//! negativ werden, und genau daran haengt die Invariante aus T43.

#include <array>
#include <cstddef>
#include <cstdint>

namespace pruefstand::vorrat {

using i64 = std::int64_t;

/// Die fuenf Aktionsarten aus `spiel.md`. Die Kennungen 1 bis 5 sind zugleich die
/// Gleichstandsordnung.
inline constexpr std::size_t ARTEN = 5;

/// Rundenbudget in Fuenftelrasterung: Summe der `ai` ist 5.
inline constexpr i64 BUDGET = 5;

/// `C(9,4)` -- so viele Vektoren `(a1..a5)` mit `ai` aus `{0..5}` und Summe 5.
inline constexpr std::size_t PROFILE = 126;

/// Drei Steckplaetze je Runde (`spiel.md`).
inline constexpr std::size_t STECKPLAETZE = 3;

/// Am Rundenanfang gilt `vi += ZUWACHS * ai`. Die Summe waechst je Runde um 15.
inline constexpr i64 ZUWACHS = 3;

/// Je gesetzter Aktion gilt `vi -= KOSTEN`.
inline constexpr i64 KOSTEN = 5;

/// Ein Steckplatz, der leer geblieben ist. Kein Vorrat wurde dafuer verrechnet.
inline constexpr i64 LEER = 0;

/// Obergrenze fuer `spiele`. Die Partie hat 24 Runden, die Invariante braucht 15;
/// die Schranke ist der Indexschutz, nicht eine Spielregel.
inline constexpr std::size_t RUNDEN_HOECHSTENS = 90;

/// Ein Aktionsprofil `(a1..a5)`.
using Profil = std::array<i64, ARTEN>;

/// Der Vorratsvektor `(v1..v5)`, zu Partiebeginn null.
using Vorrat = std::array<i64, ARTEN>;

/// Welche der fuenf Arten in dieser Runde mindestens eine zulaessige Aktion haben.
/// Der Wert kommt von aussen (T32) und gilt fuer alle drei Steckplaetze der Runde.
using Zulaessigkeit = std::array<bool, ARTEN>;

/// Die Arten der drei Steckplaetze einer Runde, je Eintrag `1..5` oder `LEER`.
using Rundenfolge = std::array<i64, STECKPLAETZE>;

/// Der Strategiekern eines Profils (T36), **vierwertig**.
///
/// `OHNE` ist kein Ersatzwert, sondern der Befund: Ein Profil ohne jede Familien-
/// aktion hat keinen Kern. Ein dreiwertiger Kern zwingt den Gleichstandsbrecher,
/// eine Positionsstrategie zu behaupten, in der keine Position vorkommt.
enum class Strategiekern : int {
    OHNE = 0,
    POSITION = 1,
    BETEILIGUNG = 2,
    LOBBY = 3,
};

/// Ein Eintrag der Profilliste. Der Kern wird **einmal je Profil** berechnet und mit
/// der Liste abgelegt, nicht je Lauf neu (T36).
struct Profileintrag {
    i64 kennung = 0;
    Profil anteile{};
    Strategiekern kern = Strategiekern::OHNE;
};

using Profilliste = std::array<Profileintrag, PROFILE>;

/// **Absichtliche Fehler, und sie stehen hier, damit die Probe zeigen kann, dass ihre
/// Pruefungen etwas messen.**
///
/// Ein Test, der nie rot wird, prueft nichts. Beide Werte veraendern genau eine
/// Zeile des Verfahrens; die Probe fuehrt sie vor und weist nach, welche Bedingung
/// sie jeweils faengt -- und welche sie durchlaesst. Zwei sind es, weil eine nicht
/// genuegt: Der Gleichstandsbrecher nach groesserer Kennung besteht die Invariante,
/// ein bei null abgeschnittener Vorrat besteht die Referenzfolge.
///
/// Fuer jeden gewoehnlichen Aufruf gilt `KEINE`; das ist der Vorgabewert.
enum class Abweichung : int {
    /// Das Verfahren nach `spiel.md`.
    KEINE = 0,
    /// Gleichstand geht an die **groessere** Kennung statt an die kleinere.
    GLEICHSTAND_NACH_GROESSERER_KENNUNG = 1,
    /// `vi` wird nach dem Abzug bei null abgeschnitten statt negativ zu werden.
    VORRAT_BEI_NULL_ABGESCHNITTEN = 2,
};

/// Der Strategiekern eines Profils: die Art mit dem groessten Anteil unter
/// `{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die kleinere Kennung.
/// Hebel und Sichtbarkeit gehen nicht ein. Sind alle drei null, ist der Kern `OHNE`.
Strategiekern strategiekern(const Profil& anteile);

/// Die 126 Profile in **lexikographisch aufsteigender** Ordnung von `(a1..a5)`,
/// **nullbasiert** durchnummeriert. Der Index ist die Profilkennung (T36).
///
/// Die Liste wird als Wert zurueckgegeben und nicht gemerkt: Dieses Modul haelt
/// zwischen zwei Aufrufen nichts fest, damit zwei Laeufe nicht ueber eine Ablage
/// aneinandergeraten koennen.
Profilliste erzeuge_profilliste();

/// Ein Rundenschritt des Vorratsverfahrens (T43), woertlich nach `spiel.md`:
///
///   1. `vi += 3 * ai` fuer alle fuenf Arten.
///   2. Fuer jeden der drei Steckplaetze nacheinander: unter den zulaessigen Arten
///      die mit dem groessten `vi`, bei Gleichstand die kleinere Kennung; Aktion
///      setzen und `vi -= 5`.
///   3. Hat keine Art eine zulaessige Aktion, bleibt der Steckplatz leer und **kein
///      Vorrat wird verrechnet**.
///
/// `ai = 0` verbietet die Art nicht, sondern schiebt sie ans Ende: Die Zulaessigkeit
/// entscheidet, wer zur Wahl steht, der Vorrat nur, wer gewinnt.
///
/// `vorrat` wird an Ort und Stelle fortgeschrieben -- er gehoert dem Aufrufer.
Rundenfolge runde(Vorrat& vorrat,
                  const Profil& anteile,
                  const Zulaessigkeit& zulaessig,
                  Abweichung abweichung = Abweichung::KEINE);

/// Das Ergebnis eines mehrrundigen Laufs.
struct Laufergebnis {
    /// Der Vorratsvektor nach der letzten Runde.
    Vorrat vorrat{};
    /// Wie oft Art `i` einen Steckplatz bekommen hat, Index `i-1`.
    std::array<i64, ARTEN> gezaehlt{};
    /// Wie viele Steckplaetze leer geblieben sind.
    i64 leer_geblieben = 0;
    /// Die Artenfolge je Runde, Index `runde-1`.
    std::array<Rundenfolge, RUNDEN_HOECHSTENS> folge{};
    /// Wie viele Runden gespielt wurden.
    i64 runden = 0;
};

/// Spielt `runden` Runden mit einem Vorrat, der bei null anfaengt. `zulaessig` gilt
/// in jeder Runde gleich -- die Verengung ueber die drei Steckplaetze hinweg gehoert
/// nach T32 und nicht hierher.
///
/// Wirft `std::domain_error`, wenn `runden` ausserhalb `0 .. RUNDEN_HOECHSTENS` liegt.
Laufergebnis spiele(const Profil& anteile,
                    const Zulaessigkeit& zulaessig,
                    i64 runden,
                    Abweichung abweichung = Abweichung::KEINE);

}  // namespace pruefstand::vorrat
