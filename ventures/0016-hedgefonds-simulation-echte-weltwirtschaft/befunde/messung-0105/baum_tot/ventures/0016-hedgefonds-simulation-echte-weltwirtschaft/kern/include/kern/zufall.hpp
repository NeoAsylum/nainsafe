#pragma once
//! Zufall -- jeder Strom wird **abgeleitet**, keiner fortgeschrieben (T11).
//!
//! **Der Satz, der zuerst kommen muss, weil er sonst niemandem auffaellt:** Im Modus
//! `weltlauf` wird kein einziger Strom gezogen (T38) -- keine Bots, keine Stichproben,
//! keine Jahrgangsstreuung, und der Rueckvergleich ist damit nicht nur wiederholbar,
//! sondern startwertfrei. Das ist eine Eigenschaft der **Aufrufer** und steht deshalb
//! nicht als Pruefung in diesem Modul: `schritt` und der Pruefstand entscheiden, ob
//! gezogen wird, dieses Modul nur, was dabei herauskommt. Wer hier eine Modusabfrage
//! einbaut, verlegt die Regel an die Stelle, an der sie niemand mehr findet.
//!
//! ## Ableiten statt Fortschreiben -- die eigentliche Vorgabe
//!
//! T11 schreibt beides vor, und der zweite Satz ist der teurere:
//!
//!     strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme,
//!                        zweck_id, runde, index)
//!
//! Ein **fortlaufender** Strom -- einer, der irgendwo im Programm liegt und bei jedem
//! Zugriff weiterrueckt -- haette die Eigenschaft, dass eine einzige zusaetzliche
//! Ziehung an einer beliebigen Stelle alle spaeteren Ziehungen verschiebt. Der ganze
//! Regressionsbestand wuerde rot, ohne dass sich inhaltlich etwas geaendert haette,
//! und niemand koennte mehr unterscheiden, ob eine Aenderung das Modell **verbessert**
//! oder es nur **veraendert** hat. Deshalb ist die Ableitung hier eine reine Funktion
//! von sechs Zahlen: Gleiche sechs Zahlen, gleicher Strom -- unabhaengig davon, was
//! vorher gezogen wurde, wie oft, und in welcher Reihenfolge.
//!
//! Fortgeschrieben wird nur **innerhalb** eines einzelnen Stroms (`Strom::naechster`),
//! und ein `Strom` gehoert dem, der ihn abgeleitet hat. Genau so verlangt es T35 fuer
//! die Buendelziehung: „`s` wird als xoshiro-Zustand fortgeschrieben, und zwar nur
//! innerhalb dieser einen Ziehung."
//!
//! **Ausserhalb einer Funktion liegt in diesem Modul nichts, was sich aendern kann.**
//! Alles, was ein Aufruf braucht, kommt ueber seine Argumente herein und geht ueber
//! seinen Rueckgabewert hinaus. Ein Modul mit einem gemerkten Zustandswort waere nicht
//! eine andere Umsetzung derselben Sache, sondern die falsche Sache.
//!
//! ## Warum das Verfahren selbst geschrieben ist (T2)
//!
//! Kein fremder Kasten. Ein Versionssprung eines fremden Zufallserzeugers wuerde jede
//! gespeicherte Partie entwerten -- die Speicherstaende der Kaeufer eingeschlossen --,
//! und zwar aus einem Grund, der mit dem Spiel nichts zu tun hat. Die zwanzig Zeilen
//! stehen deshalb im Repo und aendern sich nur ueber einen ADR.
//!
//! Aus demselben Grund sind die vier Werte von `Zweck` festgeschriebene Zahlen: Sie
//! gehen in die Ableitung ein. Wer sie umnummeriert, aendert jeden Strom des Spiels.
//!
//! ## Ganzzahlig, auch beim Bereich (T4)
//!
//! Der Erzeuger liefert 64 Bit. Wer eine Zahl in einem Bereich braucht, nimmt
//! `in_bereich` -- ganzzahlige Restrechnung. Der uebliche Umweg ueber einen
//! Bruchwert in `[0,1)` ist genau der Weg, den T4 sperrt und den `sperre.hpp` zum
//! Uebersetzungsfehler macht.
//!
//! ## Quellen des Verfahrens und der Erwartungswerte
//!
//!   [SPLITMIX]    Vigna, S., „splitmix64.c" (2015), Referenzimplementierung,
//!                 gemeinfrei. Liefert die drei Konstanten und die Schrittfolge.
//!                 https://prng.di.unimi.it/splitmix64.c
//!                 -- abgerufen am 2026-09-02.
//!   [XOSHIRO]     Blackman, D., Vigna, S., „xoshiro256starstar.c" (2018),
//!                 Referenzimplementierung, gemeinfrei.
//!                 https://prng.di.unimi.it/xoshiro256starstar.c
//!                 -- abgerufen am 2026-09-02.
//!   [XOSHIRO-CPP] O'Dwyer, A., „Xoshiro256ss" -- eine wortgetreue C++-Fassung von
//!                 [XOSHIRO] samt der Saatregel „vier aufeinanderfolgende Ausgaben von
//!                 SplitMix64" und einem veroeffentlichten Testvektor zum Startwert 100.
//!                 https://raw.githubusercontent.com/Quuxplusone/Xoshiro256ss/master/xoshiro256ss.h
//!                 https://raw.githubusercontent.com/Quuxplusone/Xoshiro256ss/master/README.md
//!                 -- beide abgerufen am 2026-09-02.
//!   [XOSHIRO-RS]  rust-random/rngs, `rand_xoshiro/src/splitmix64.rs`, Testblock
//!                 `reference`: 50 Ausgaben zum Startwert 1477776061723855037, laut
//!                 Quellkommentar „produced with the reference implementation".
//!                 https://raw.githubusercontent.com/rust-random/rngs/master/rand_xoshiro/src/splitmix64.rs
//!                 -- abgerufen am 2026-09-02.
//!
//! Die Zahlenproben gegen diese Quellen stehen in `src/zufall.cpp` als `static_assert`;
//! was ein `static_assert` nicht kann -- unter den Sanitizern laufen und die Werte
//! ausschreiben --, steht in `test/zufall_probe.cpp`.

#include <array>
#include <cstddef>
#include <cstdint>

namespace kern::zufall {

using u64 = std::uint64_t;
using i64 = std::int64_t;

/// Der harte Fehler dieses Moduls. Kehrt nie zurueck.
///
/// **Warum ein Abbruch und kein Ersatzwert.** Er trifft genau einen Fall: eine
/// Bereichsgrenze von null, also eine Ziehung aus einer leeren Menge. Wuerde die
/// stillschweigend null liefern, waere aus einem Fehler des Aufrufers eine Zahl
/// geworden, die keine Pruefung bemerkt -- und eine falsche Zahl wandert in den
/// Regressionsbestand, wird dort zum Sollwert und macht jede spaetere Behebung rot.
///
/// **Warum eine Ausnahme und kein Signal.** Bei der Auswertung zur Uebersetzungszeit
/// ist ein Wurf kein Laufzeitereignis, sondern macht den Ausdruck zu keiner Konstante;
/// ein `static_assert`, das den Abbruchpfad trifft, ist damit ein Uebersetzungsfehler.
/// Und zur Laufzeit faengt die Probe ihn und weist ihn nach -- ein Signal koennte sie
/// nicht verbuchen. Was nicht nachweisbar ist, ist in dieser Fabrik nicht gebaut.
///
/// **Warum eigen und nicht der Abbruch des Rechenwerks.** Dieses Modul haengt an
/// nichts: Es kennt den Zustand nicht, die abgeleiteten Groessen nicht und das
/// Rechenwerk nicht, sondern nur sechs Zahlen. Diese Unabhaengigkeit ist der Grund,
/// warum es zuerst gebaut werden konnte, und sie ist mehr wert als die vier Zeilen,
/// die eine gemeinsame Abbruchstelle sparen wuerde. Der Preis steht hier, damit ihn
/// niemand suchen muss: zwei Wuerfe im Kern statt einem.
[[noreturn]] void abbruch(const char* grund);

// ---------------------------------------------------------------------------
// Die vier Zwecke aus T11
// ---------------------------------------------------------------------------

/// `zweck_id` -- „wird nie ueber eine Zahl geschrieben" (T11).
///
/// Als `enum class` ist das keine Abmachung, sondern eine Regel des Uebersetzers: Eine
/// nackte Zahl an dieser Stelle hat keine Umwandlung hierher und findet die Ableitung
/// gar nicht erst. `src/zufall.cpp` weist das mechanisch nach.
///
/// **Die Zahlen sind Teil der Ableitung und damit unveraenderlich.** Sie gehen in den
/// Keim ein; eine Umnummerierung erzeugt andere Stroeme und entwertet jede gespeicherte
/// Partie. Die Reihenfolge ist die aus T11, die Zaehlung beginnt bei eins.
enum class Zweck : u64 {
    JAHRGANGSSTREUUNG = 1,
    ZUFALLSBOT = 2,
    BUENDELZIEHUNG = 3,
    SUCHBOT_KANDIDATEN = 4,
};

// ---------------------------------------------------------------------------
// SplitMix64 -- die Ableitung
// ---------------------------------------------------------------------------

/// Der Schrittabstand von [SPLITMIX] („x += 0x9e3779b97f4a7c15").
inline constexpr u64 SPLITMIX_SCHRITT = 0x9e3779b97f4a7c15ULL;

/// Die beiden Faktoren der Mischung von [SPLITMIX], in der Reihenfolge der Quelle.
inline constexpr u64 SPLITMIX_FAKTOR_1 = 0xbf58476d1ce4e5b9ULL;
inline constexpr u64 SPLITMIX_FAKTOR_2 = 0x94d049bb133111ebULL;

/// Die Mischung aus [SPLITMIX] -- die drei Zeilen hinter dem `+=`.
///
/// ```
/// z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
/// z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
/// return z ^ (z >> 31);
/// ```
///
/// **Sie ist umkehrbar eindeutig**, und das ist keine Nebensaechlichkeit, sondern die
/// Eigenschaft, an der die ganze Ableitung haengt: Jeder der drei Schritte ist es
/// einzeln -- `z ^ (z >> k)` mit `k >= 1` laesst sich Bit fuer Bit von oben her
/// zurueckrechnen, und eine Multiplikation mit einer ungeraden Zahl ist `mod 2**64`
/// umkehrbar (beide Faktoren enden auf `9` beziehungsweise `b`, sind also ungerade).
/// Aus zwei verschiedenen Eingaben werden damit zwei verschiedene Ausgaben --
/// **garantiert**, nicht nur mit hoher Wahrscheinlichkeit. Darauf beruht unten, dass
/// ein um eins erhoehter `index` wirklich einen anderen Strom liefert.
///
/// Der Umbruch `mod 2**64` ist die Rechenvorschrift und kein Fehlerfall. Er laeuft auf
/// `std::uint64_t`, wo der Standard ihn festlegt -- nicht `-fwrapv` und keine Annahme
/// ueber den Uebersetzer. Vorzeichenbehaftete Arithmetik kommt in diesem Modul nicht
/// vor; die drei Massnahmen aus ADR 0011 sichern sie ab, und hier ist keine.
[[nodiscard]] constexpr u64 mische(u64 z) noexcept
{
    z = (z ^ (z >> 30)) * SPLITMIX_FAKTOR_1;
    z = (z ^ (z >> 27)) * SPLITMIX_FAKTOR_2;
    return z ^ (z >> 31);
}

/// Ein Schritt von [SPLITMIX], wortgleich mit der Referenzimplementierung:
///
/// ```
/// uint64_t next() {
///     uint64_t z = (x += 0x9e3779b97f4a7c15);
///     ...
/// }
/// ```
///
/// `stand` ist das, was dort die Ablage `x` ist -- nur liegt es hier beim Aufrufer und
/// nicht im Modul. Das ist der einzige Unterschied zur Quelle, und er ist der Punkt
/// des ganzen Pakets.
///
/// Gebraucht wird die Funktion an zwei Stellen: um aus einem Keim die vier Worte eines
/// Stroms zu ziehen, und um in `src/zufall.cpp` gegen die veroeffentlichten Werte von
/// [XOSHIRO-RS] zu stehen -- diese Fassung ist es, die dort geprueft wird.
[[nodiscard]] constexpr u64 splitmix64_naechster(u64& stand) noexcept
{
    stand += SPLITMIX_SCHRITT;
    return mische(stand);
}

/// Eine Zahl in einen Zwischenstand einruehren.
///
/// Es ist derselbe Schritt wie oben, nur wird zusaetzlich `wert` addiert: Mit
/// `wert == 0` ist `einruehren(stand, 0)` genau ein Schritt des Referenzerzeugers ab
/// `stand`. `src/zufall.cpp` haelt beides gegeneinander, damit die Gleichheit nicht
/// nur hier behauptet ist.
///
/// **Warum sie umkehrbar eindeutig in beiden Argumenten ist.** Bei festem `stand` ist
/// `wert -> stand + SPLITMIX_SCHRITT + wert` eine Verschiebung `mod 2**64` und damit
/// umkehrbar; danach folgt `mische`, ebenfalls umkehrbar. Zwei verschiedene Werte
/// ergeben deshalb zwei verschiedene Zwischenstaende -- ohne Ausnahme und ohne
/// Kollisionswahrscheinlichkeit.
[[nodiscard]] constexpr u64 einruehren(u64 stand, u64 wert) noexcept
{
    return mische(stand + SPLITMIX_SCHRITT + wert);
}

// ---------------------------------------------------------------------------
// xoshiro256** -- die Erzeugung
// ---------------------------------------------------------------------------

/// Ein Strom besteht aus so vielen Worten. Die Zahl steht als Name da, weil die
/// Schrittregel unten mit festen Indizes darauf zugreift.
inline constexpr std::size_t STROM_WORTE = 4;

/// Linksrotation um eine **feste** Weite.
///
/// Die Weite ist ein Vorlagenwert und keine Laufzeitgroesse, und das hat einen Grund:
/// `x >> (64 - K)` waere bei `K == 0` eine Verschiebung um 64 Stellen und damit
/// undefiniert. Als Vorlagenwert ist die Bedingung `0 < K < 64` beim Uebersetzen
/// geprueft statt beim Ausfuehren gehofft; die beiden einzigen Weiten des Verfahrens
/// (7 und 45) stehen als Literale in der Schrittregel.
template <unsigned K>
[[nodiscard]] constexpr u64 linksrotieren(u64 x) noexcept
{
    static_assert(K > 0 && K < 64,
                  "eine Rotation um 0 oder 64 waere eine undefinierte Verschiebung");
    return (x << K) | (x >> (64u - K));
}

/// Ein abgeleiteter Strom: vier Worte Zustand und die Schrittregel darauf.
///
/// **Der Zustand liegt im Objekt, nicht im Modul.** Wer einen Strom ableitet, bekommt
/// sein eigenes Stueck Zustand in die Hand; zwei Stroeme wissen nichts voneinander,
/// und kein Aufruf irgendwo sonst im Programm kann diesen hier verschieben. Genau das
/// ist der Unterschied zwischen „abgeleitet" und „fortgeschrieben": Fortgeschrieben
/// wird innerhalb einer Ziehung, abgeleitet wird zwischen den Ziehungen.
class Strom {
public:
    /// Aus vier Worten. Oeffentlich, weil eine gespeicherte Partie den Zustand eines
    /// Stroms mitten in einer Ziehung wiederherstellen koennen muss.
    constexpr explicit Strom(std::array<u64, STROM_WORTE> worte) noexcept : s_(worte) {}

    /// Die vier Worte, so wie sie stehen. Fuer die Zustandsausgabe und dafuer, dass
    /// eine Probe zwei Stroeme vollstaendig vergleichen kann und nicht nur ihre
    /// naechsten Ausgaben.
    [[nodiscard]] constexpr std::array<u64, STROM_WORTE> worte() const noexcept
    {
        return s_;
    }

    /// Die Schrittregel von xoshiro256**, wortgleich mit [XOSHIRO] in der Fassung
    /// [XOSHIRO-CPP]:
    ///
    /// ```
    /// u64 result = rotl(s[1] * 5, 7) * 9;
    /// u64 t = s[1] << 17;
    /// s[2] ^= s[0];  s[3] ^= s[1];  s[1] ^= s[2];  s[0] ^= s[3];
    /// s[2] ^= t;     s[3] = rotl(s[3], 45);
    /// return result;
    /// ```
    ///
    /// **Die Ausgabe wird vor der Fortschreibung gebildet** -- sie haengt allein an
    /// `s[1]`, wie es dasteht. Wer die beiden Bloecke tauscht, bekommt kein kaputtes
    /// Programm, sondern einen anderen, aehnlich aussehenden Erzeuger mit anderen
    /// Zahlen; der Nachweis liegt deshalb nicht im Lesen dieser Zeilen, sondern in dem
    /// veroeffentlichten Testvektor in `src/zufall.cpp`.
    ///
    /// Die Indizes sind Literale unter `STROM_WORTE`; das `static_assert` daneben
    /// haelt die beiden Dinge zusammen, falls jemand die Wortzahl anfasst.
    constexpr u64 naechster() noexcept
    {
        static_assert(STROM_WORTE == 4, "die Indizes unten sind auf vier Worte geschrieben");

        const u64 ergebnis = linksrotieren<7>(s_[1] * 5ULL) * 9ULL;
        const u64 zwischen = s_[1] << 17;

        s_[2] ^= s_[0];
        s_[3] ^= s_[1];
        s_[1] ^= s_[2];
        s_[0] ^= s_[3];
        s_[2] ^= zwischen;
        s_[3] = linksrotieren<45>(s_[3]);

        return ergebnis;
    }

private:
    std::array<u64, STROM_WORTE> s_{};
};

/// Dieselbe Ziehung als freie Funktion, damit `naechster(s)` aus T35 wortgleich
/// hingeschrieben werden kann.
[[nodiscard]] constexpr u64 naechster(Strom& strom) noexcept
{
    return strom.naechster();
}

/// Aus einem Keim ein Strom: vier aufeinanderfolgende Ausgaben von SplitMix64.
///
/// **Das ist die veroeffentlichte Saatregel, keine eigene Erfindung.** [XOSHIRO]
/// empfiehlt SplitMix64 zum Saeen, und [XOSHIRO-CPP] schreibt genau diese vier Zeilen
/// aus; der Testvektor zum Keim 100 in `src/zufall.cpp` prueft die Saatregel und die
/// Schrittregel in einem Stueck. Eine abweichende Saat waere nicht falsch, aber sie
/// waere durch nichts belegt -- und dann stuenden die Erwartungswerte des Kerns auf
/// dem Kern selbst.
///
/// **Der Nullzustand kann dabei nicht entstehen**, und das muss er auch nicht per
/// Zufall vermeiden: xoshiro256** hat in vier Nullworten einen Fixpunkt, der nur
/// Nullen ausgibt. Die vier Worte sind hier `mische` an vier Stellen, die sich um
/// `SPLITMIX_SCHRITT`, `2·SPLITMIX_SCHRITT` und `3·SPLITMIX_SCHRITT` unterscheiden;
/// `SPLITMIX_SCHRITT` ist ungerade, also sind die vier Stellen `mod 2**64`
/// verschieden, und weil `mische` umkehrbar eindeutig ist, sind es auch die vier
/// Worte. Von vier paarweise verschiedenen Worten kann hoechstens eines null sein.
[[nodiscard]] constexpr Strom strom_aus_keim(u64 keim) noexcept
{
    std::array<u64, STROM_WORTE> worte{};
    for (std::size_t i = 0; i < STROM_WORTE; ++i) {
        worte[i] = splitmix64_naechster(keim);
    }
    return Strom{worte};
}

// ---------------------------------------------------------------------------
// Die Ableitung aus T11 -- sechs Zahlen, ein Strom
// ---------------------------------------------------------------------------

/// `strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme, zweck_id,
///                     runde, index)` -- die Signatur aus T11, Argument fuer Argument.
///
/// | Argument | Bedeutung |
/// |---|---|
/// | `wurzelstartwert` | der eine Startwert der Partie; alles andere haengt an ihm |
/// | `jahrgang_id` | welcher Startjahrgang gespielt wird |
/// | `parameter_pruefsumme` | die Summe des Parametersatzes: ein anderer Satz, andere Stroeme |
/// | `zweck_id` | wofuer gezogen wird, als Name und nie als Zahl |
/// | `runde` | der Zeitpunkt in der Partie |
/// | `index` | die wievielte Ziehung dieses Zwecks in dieser Runde |
///
/// **Wie die sechs zusammenkommen.** Der Wurzelstartwert geht zuerst allein durch
/// einen vollen Mischschritt; danach werden die fuenf uebrigen Zahlen in fester
/// Reihenfolge nacheinander eingeruehrt, jede wieder mit einem vollen Mischschritt.
/// Weil `einruehren` in beiden Argumenten umkehrbar eindeutig ist, folgt daraus mehr
/// als eine Wahrscheinlichkeitsaussage:
///
///   * Zwei Aufrufe, die sich in **genau einer** der sechs Zahlen unterscheiden,
///     liefern **verschiedene** Keime -- fuer jede der sechs Stellen, ohne Ausnahme.
///     Ein um eins erhoehter `index` ist damit garantiert ein anderer Strom und nicht
///     nur fast sicher einer.
///   * Verschiedene Keime liefern verschiedene Stroeme: `strom_aus_keim` bildet den
///     Keim umkehrbar eindeutig auf sein erstes Wort ab.
///
/// **Warum eingeruehrt und nicht verodert oder addiert.** Ein blosses XOR oder eine
/// Summe der sechs Zahlen waere von der Reihenfolge unabhaengig -- Runde 3 mit
/// Index 5 und Runde 5 mit Index 3 bekaemen denselben Strom, und die Ziehungen zweier
/// Runden waeren aneinander gekoppelt, ohne dass es jemandem auffiele. Der
/// Mischschritt zwischen den Zahlen ist genau das, was diese Kopplung ausschliesst.
///
/// **Warum der Wurzelstartwert einen eigenen Schritt vorweg bekommt.** Ohne ihn
/// stuenden er und der Jahrgang in derselben Summe -- `wurzelstartwert +
/// SPLITMIX_SCHRITT + jahrgang_id` --, und dann haetten Wurzelstartwert 4 mit Jahrgang
/// 1997 und Wurzelstartwert 5 mit Jahrgang 1996 exakt dieselben Stroeme. Zwei Partien,
/// die einen Startwert auseinanderliegen, waeren fuer benachbarte Jahrgaenge
/// ununterscheidbar. Die laufende Probe hat genau das gezeigt, bevor dieser Schritt
/// hier stand: Die Zeilen „wurzelstartwert + 1" und „jahrgang_id + 1" waren Wort fuer
/// Wort dieselben. Der Fall ist als Probe festgehalten -- `src/zufall.cpp` haelt jetzt
/// alle sechs Einzelaenderungen **paarweise** gegeneinander und nicht mehr nur jede
/// gegen den Bezugsaufruf.
///
/// Ganz ohne Zusammenstoesse geht es nicht: Sechs mal 64 Bit gehen nicht kollisionsfrei
/// in 64 Bit. Was hier ausgeschlossen wird, ist der Zusammenstoss, den jemand
/// **versehentlich trifft** -- benachbarte Werte, vertauschte Argumente, verschobene
/// Zaehlungen.
///
/// **Die Umdeutung nach `u64` ist eine Wertumrechnung**, keine Speicherdeutung: Der
/// Standard schreibt seit C++20 `wert mod 2**64` vor, und weil vorzeichenbehaftete
/// Zahlen seit C++20 Zweierkomplement sind, ist das genau das erwartete Bitmuster.
/// Sie ist auf ganz `i64` umkehrbar eindeutig, die Aussagen oben gelten also auch fuer
/// negative Jahrgangs-, Runden- und Indexwerte.
///
/// Der Name der Funktion ist der aus T11 und T35, damit `s = splitmix64(...)` dort
/// wortgleich hingeschrieben werden kann.
[[nodiscard]] constexpr Strom splitmix64(u64 wurzelstartwert,
                                         i64 jahrgang_id,
                                         u64 parameter_pruefsumme,
                                         Zweck zweck_id,
                                         i64 runde,
                                         i64 index) noexcept
{
    u64 keim = einruehren(wurzelstartwert, 0ULL);

    keim = einruehren(keim, static_cast<u64>(jahrgang_id));
    keim = einruehren(keim, parameter_pruefsumme);
    keim = einruehren(keim, static_cast<u64>(zweck_id));
    keim = einruehren(keim, static_cast<u64>(runde));
    keim = einruehren(keim, static_cast<u64>(index));

    return strom_aus_keim(keim);
}

// ---------------------------------------------------------------------------
// Eine Zahl in einem Bereich (T4)
// ---------------------------------------------------------------------------

/// Die naechste Zahl aus `strom`, kleiner als `grenze`. Ganzzahlige Restrechnung.
///
/// Der Weg, den es hier ausdruecklich **nicht** gibt, ist der uebliche: eine Zahl in
/// `[0,1)` bilden und mit der Grenze multiplizieren. Er braeuchte einen Bruchtyp, und
/// der ist im Kern gesperrt (T4).
///
/// **Die Verzerrung wird benannt, nicht behoben.** `rest von 2**64 durch grenze` ist
/// nicht null, sobald `grenze` keine Zweierpotenz ist; die ersten
/// `2**64 mod grenze` Werte kommen deshalb um ein Vielfaches von `2**-64`
/// haeufiger vor. T35 rechnet das aus: Bei `grenze <= 2**32` liegt der Unterschied
/// unter `2**-32` und damit unter jeder Wirkung, die die Masse des Pruefstands messen.
/// Ein Verwerfungsverfahren waere gleichmaessiger, wuerde aber die **Zahl der
/// Ziehungen** von den gezogenen Werten abhaengig machen -- und dann haette ein
/// spaeterer Eingriff genau die Verschiebung zur Folge, gegen die dieses ganze Modul
/// gebaut ist.
///
/// `grenze == 0` ist eine Ziehung aus einer leeren Menge und damit ein Fehler des
/// Aufrufers, kein Randfall: siehe die Begruendung bei `abbruch`.
[[nodiscard]] constexpr u64 in_bereich(Strom& strom, u64 grenze)
{
    if (grenze == 0) {
        abbruch("in_bereich: Grenze null -- eine Ziehung aus einer leeren Menge. Ein "
                "stiller Ersatzwert waere eine Zahl, die keine Pruefung bemerkt.");
    }
    return strom.naechster() % grenze;
}

}  // namespace kern::zufall
