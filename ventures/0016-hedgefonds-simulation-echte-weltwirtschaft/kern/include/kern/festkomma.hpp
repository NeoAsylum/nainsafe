#pragma once
//! Festkomma -- die einzige Stelle des Kerns, an der geteilt wird (T6).
//!
//! Hier steht das Rechenwerk ausgeschrieben; `src/festkomma.cpp` enthaelt den
//! Abbruch und die Zahlenproben. Die Aufteilung hat einen Grund: Alle Regeln sind
//! `constexpr`, damit die Proben schon beim Uebersetzen laufen. Ein Rundungsfehler
//! ist damit kein roter Test, sondern eine Datei, die sich nicht uebersetzen laesst.
//!
//! Drei Vorgaben, die jede Zeile hier bestimmen:
//!
//!   T6  Genau eine Rundungsregel -- auf halbe Betraege **vom Null weg** --, `/` auf
//!       Zustandsgroessen ist ausserhalb dieser Datei verboten, `nenner == 0` bricht ab.
//!   T7  Ueberlauf ist ein Absturz, kein Umlauf.
//!   ADR 0011, Massnahme 3: `__int128` fuer JEDEN Zwischenwert einer
//!       Multiplikation-Division. Nie ein nachtraeglicher Test auf Ueberlauf.
//!
//! **Warum vom Null weg und nicht wie die Maschine.** C++ schneidet seit C++11 bei
//! `/` gegen null ab (\[expr.mul\]/4) -- genau wie Rust, die Begruendung aus T6 gilt
//! unveraendert weiter. Abschneiden ist ueber dem Vorzeichen unsymmetrisch: Es zieht
//! jeden Betrag nach unten, also positive Werte nach unten und negative nach oben.
//! Ein Fonds, der nach `spiel.md` long **und** short sein koennen soll, bekaeme damit
//! eine still bevorzugte Richtung, und Mass 2 misst danach die Rundung statt das
//! Spiel. Deshalb wird das Vorzeichen abgespalten, auf dem Betrag gerundet und erst
//! am Ende wieder angesetzt.

#include <cstdint>

namespace kern::festkomma {

using i64 = std::int64_t;

/// Der Zwischenwerttyp aus ADR 0011, Massnahme 3. GCC-Erweiterung, in
/// `werkzeugkette.cmake` begruendet; deshalb ist `-Wpedantic` dort abgeschaltet.
using i128 = __int128;

inline constexpr i64  I64_MAX  = 9'223'372'036'854'775'807;
inline constexpr i64  I64_MIN  = -I64_MAX - 1;
inline constexpr i128 I128_MAX = static_cast<i128>(~static_cast<unsigned __int128>(0) >> 1);

/// Der harte Fehler aus T6 und T7. Kehrt nie zurueck.
///
/// **Warum ein Abbruch und kein Ersatzwert** -- die Stelle, an der Paket 0004 eine
/// Begruendung verlangt: Ein stiller Ersatzwert waere eine Zahl, die keine Pruefung
/// bemerkt. Befund 2 der zweiten Pruefung entstand genau so: Ein Rueckvergleich mit
/// einem Fonds ohne Vermoegen brauchte dieses Vermoegen als Nenner. Haette
/// `teile_gerundet` dort still null geliefert, waere aus einem Fehler eine falsche
/// Zahl geworden -- und eine falsche Zahl wandert in den Regressionsbestand, wird
/// dort zum Sollwert und macht jede spaetere Behebung rot. Ein Abbruch kostet einen
/// Lauf, ein Ersatzwert kostet den Bestand.
///
/// **Warum eine Ausnahme und kein `std::abort`.** Zwei mechanische Gruende, beide
/// wiegen mehr als der Unterschied in der Haerte:
///   1. Bei der Auswertung zur Uebersetzungszeit ist ein `throw` kein Laufzeitereignis,
///      sondern macht den Ausdruck zu keiner Konstante -- ein `static_assert`, das den
///      Abbruchpfad trifft, ist damit ein Uebersetzungsfehler. Mit `abort` waere er
///      unpruefbar.
///   2. Ein Signal laesst sich von CTest nicht als erwartetes Ergebnis verbuchen; eine
///      Ausnahme faengt die Probe und weist sie nach. Was nicht nachweisbar ist, ist
///      in dieser Fabrik nicht gebaut.
/// Still ist die Ausnahme dadurch nicht: Sie hat keinen Rueckgabewert, den jemand
/// versehentlich weiterrechnet, und `[[noreturn]]` sagt das dem Uebersetzer.
[[noreturn]] void abbruch(const char* grund);

namespace intern {

/// Betrag auf `i128`. Ueberlaeuft nie, auch nicht bei `I64_MIN`: Der Betrag
/// 9.223.372.036.854.775.808 passt in `i128` und laege ausserhalb von `i64`.
constexpr i128 betrag(i128 wert) { return wert < 0 ? -wert : wert; }

/// Bitlaenge eines nichtnegativen Werts; 0 hat die Laenge 0.
/// Handgeschrieben, weil `std::bit_width` nur ueber Standard-Ganzzahltypen geht und
/// `__int128` keiner ist.
constexpr unsigned bitlaenge(i128 wert)
{
    unsigned n = 0;
    while (wert > 0) { wert >>= 1; ++n; }
    return n;
}

/// Der Ueberlaufwaechter aus T7: Was nicht in `i64` passt, ist ein Abbruch.
constexpr i64 nach_i64(i128 wert, const char* stelle)
{
    if (wert > static_cast<i128>(I64_MAX) || wert < static_cast<i128>(I64_MIN)) {
        abbruch(stelle);
    }
    return static_cast<i64>(wert);
}

/// Die eine Rundungsregel, auf `i128` und mit abgespaltenem Vorzeichen.
/// Vorbedingung: `nenner != 0` -- die Pruefung steht bei den Aufrufern, damit die
/// Fehlermeldung sagt, welche Rechnung gestolpert ist.
constexpr i128 runde_von_null_weg(i128 zaehler, i128 nenner)
{
    const int  vorzeichen = ((zaehler < 0) != (nenner < 0)) ? -1 : 1;
    const i128 az = betrag(zaehler);
    const i128 an = betrag(nenner);

    const i128 ganz = az / an;
    const i128 rest = az - ganz * an;          // 0 <= rest < an, weil beide >= 0 sind

    // Aufgerundet wird genau dann, wenn der Rest mindestens die Haelfte des Nenners
    // ist -- also bei `2 * rest >= an`. Ausgeschrieben steht hier die Form
    // `rest >= an - rest`. Sie ist dieselbe Bedingung und rechnet nur mit Werten,
    // die kleiner als `an` sind: Wegen `0 <= rest < an` kann `an - rest` nicht
    // ueberlaufen, die Verdopplung `2 * rest` bei einem Nenner nahe der
    // `i128`-Grenze aber sehr wohl. Das ist kein hypothetischer Fall -- `mal_geteilt`
    // reicht ein Produkt zweier `i64` als Zaehler herein, und das steht mit bis zu
    // 8,5e37 in derselben Groessenordnung wie die `i128`-Grenze 1,7e38.
    const i128 abs_ergebnis = (rest >= an - rest) ? ganz + 1 : ganz;

    return vorzeichen < 0 ? -abs_ergebnis : abs_ergebnis;
}

/// Ganzzahlige Potenz auf `i128` fuer nichtnegative Basen, mit hartem Abbruch bei
/// Ueberlauf. Nur `wurzel` braucht sie; oeffentlich ist `potenz` auf `i64`.
constexpr i128 potenz_i128(i128 basis, unsigned exponent)
{
    i128 wert = 1;
    for (unsigned i = 0; i < exponent; ++i) {
        if (basis != 0 && wert > I128_MAX / basis) {
            abbruch("potenz_i128: Zwischenwert ueberschreitet i128");
        }
        wert *= basis;
    }
    return wert;
}

}  // namespace intern

/// `zaehler / nenner`, gerundet auf halbe Betraege vom Null weg (T6).
///
/// Beispiele, die zugleich in `src/festkomma.cpp` als Probe stehen:
/// `teile_gerundet(7, 2) == 4`, `teile_gerundet(-7, 2) == -4`,
/// `teile_gerundet(5, 2) == 3`, `teile_gerundet(-5, 2) == -3`.
constexpr i64 teile_gerundet(i64 zaehler, i64 nenner)
{
    if (nenner == 0) {
        abbruch("teile_gerundet: Nenner null -- ein stiller Ersatzwert waere eine Zahl, "
                "die keine Pruefung bemerkt (T6)");
    }
    return intern::nach_i64(
        intern::runde_von_null_weg(static_cast<i128>(zaehler), static_cast<i128>(nenner)),
        "teile_gerundet: Ergebnis ausserhalb von i64 (T7)");
}

/// `a * b / c` ueber einen `i128`-Zwischenwert, dieselbe Rundungsregel (T6, T47).
///
/// **Warum der Zwischenwert Pflicht ist und kein Optimierungsdetail.** Die Skalen aus
/// T5 stossen bei jeder Bewertung zusammen: Betraege in Cent mal Anteilen in
/// Zehntausendsteln. `mal_geteilt(21'000'000'000, 20, 10'000)` -- die Zahlenprobe aus
/// T47 -- hat das Produkt 420.000.000.000, das passt noch; ein Korb in der
/// volkswirtschaftlichen Skala mal einem Kurs in Basispunkten passt nicht mehr. Ein
/// nachtraeglicher Ueberlauftest kaeme dafuer zu spaet: Das Produkt waere dann schon
/// gebildet, und mit `-fwrapv` waere es still umgebrochen statt falsch zu sein.
constexpr i64 mal_geteilt(i64 a, i64 b, i64 c)
{
    if (c == 0) {
        abbruch("mal_geteilt: Nenner null -- ein stiller Ersatzwert waere eine Zahl, "
                "die keine Pruefung bemerkt (T6)");
    }
    const i128 produkt = static_cast<i128>(a) * static_cast<i128>(b);
    return intern::nach_i64(intern::runde_von_null_weg(produkt, static_cast<i128>(c)),
                            "mal_geteilt: Ergebnis ausserhalb von i64 (T7)");
}

/// `a + b` auf `i64` ueber den Ueberlaufbaustein des Uebersetzers
/// (T7, Massnahme 4, Punkt 2). Ueberlauf ist ein Abbruch, kein Umbruch.
///
/// **Die Vorgabe im Wortlaut**, aus `technik.md`, Anforderung **T7**, Massnahme 4,
/// Punkt 2. Zitiert statt zusammengefasst, weil dort zugleich steht, warum Massnahme 1
/// diesen Baustein nicht entwertet:
///
/// > „Was nicht über `__int128` läuft -- Additionen und Subtraktionen auf `i64` --,
/// > benutzt `__builtin_add_overflow` und `__builtin_sub_overflow`. Sie rechnen in
/// > unendlicher Genauigkeit und melden, ob das Ergebnis in den Zieltyp passt;
/// > `-fwrapv` berührt sie nicht, weil sie kein undefiniertes Verhalten auslösen,
/// > sondern eines abfragen.“
///
/// **Warum nicht `nach_i64(i128(a) + i128(b))`.** Der Weg waere richtig und faenge
/// dieselben Faelle. T7 schneidet die geprueften Rechenarten aber nach der Rechenart
/// und nennt fuer die Strichrechnung ausdruecklich diese beiden Bausteine; eine
/// zweite Bauart fuer dieselbe Vorgabe braeuchte einen ADR und keinen besseren Grund.
///
/// **Warum die Strichrechnung hier steht und nicht bei ihrem ersten Aufrufer.**
/// Denselben Grund fuehrt T7 schon fuer `mal`: Diese Datei ist nach T6 die einzige
/// Rechenstelle des Kerns. Eine gepruefte Addition ausserhalb macht daraus einen Satz
/// mit einer Ausnahme, die nur der Bauagent des betroffenen Moduls kennt -- und das
/// naechste Modul schreibt dann seine eigene Fassung. Bei einer Ueberlaufpruefung
/// heisst das: Ein Modul bricht ab, das andere bricht um. Dazu kommt der Nachweis:
/// Eine Fassung im anonymen Namensraum einer Quelle hat keinen Aufrufer ausserhalb
/// ihrer Datei, und damit sind ihre beiden Abbruchpfade unpruefbar. `festkomma_probe`
/// nagelt sie hier mit derselben Bauart fest, mit der sie den Waechter von `mal`
/// schon festnagelt.
///
/// **Warum die Ausgabegroesse ein Ausgabeargument des Bausteins ist und kein
/// Rueckgabewert.** `__builtin_add_overflow` liefert den Ueberlaufbefund zurueck und
/// legt die Summe ab; der abgelegte Wert ist im Ueberlauffall der umgebrochene, und
/// genau ihn gibt diese Funktion nie heraus. Der Abbruch steht davor.
constexpr i64 plus(i64 a, i64 b)
{
    i64 ergebnis = 0;
    if (__builtin_add_overflow(a, b, &ergebnis)) {
        abbruch("plus: Summe ausserhalb von i64 (T7)");
    }
    return ergebnis;
}

/// `a - b` auf `i64`, derselbe Baustein und derselbe Abbruch wie bei `plus`
/// (T7, Massnahme 4, Punkt 2).
///
/// Eigenstaendig und nicht als `plus(a, -b)` gebaut, und das ist kein Geschmack:
/// `-b` ist fuer `b == I64_MIN` selbst der Ueberlauf, den diese Funktion faengt.
/// Die Umschreibung braeche also genau dort ab, wo `minus(0, I64_MIN)` abbrechen
/// soll, aber auch dort, wo `minus(-1, I64_MIN)` ein gueltiges Ergebnis hat.
constexpr i64 minus(i64 a, i64 b)
{
    i64 ergebnis = 0;
    if (__builtin_sub_overflow(a, b, &ergebnis)) {
        abbruch("minus: Differenz ausserhalb von i64 (T7)");
    }
    return ergebnis;
}

/// `a * b` ohne folgende Division -- derselbe Zwischentyp, derselbe Waechter
/// (T7, Massnahme 4, Punkt 3).
///
/// **Die Vorgabe im Wortlaut**, aus `technik.md`, Anforderung **T7**, Massnahme 4,
/// Punkt 3. Zitiert statt zusammengefasst, weil dort zugleich die Wahl dieser Form
/// gegen `__builtin_mul_overflow` begruendet ist:
///
/// > „Auch eine Multiplikation ohne nachfolgende Division läuft über `__int128` und
/// > den Wächter aus 4.1, nämlich über `mal(a, b)` in
/// > `kern/include/kern/festkomma.hpp`, gebaut wie `mal_geteilt`: Produkt als
/// > `i128`, Rückkehr durch `intern::nach_i64`. Der Zwischenwert kann dabei nicht
/// > selbst überlaufen, weil `|a·b| ≤ 2^126`, also rund `8,5·10^37`, unter der
/// > `i128`-Grenze `1,7·10^38` bleibt -- dasselbe Argument, das `potenz` in
/// > derselben Datei schon führt.“
///
/// **Warum die blanke Multiplikation eine eigene Massnahme braucht.** Sie lag
/// zwischen den anderen: Massnahme 3 deckt die Multiplikation *mit* nachfolgender
/// Division, 4.1 die Verengung eines 128-Bit-Werts, 4.2 die Strichrechnung auf
/// `i64` -- und Massnahme 1 (`-fwrapv`) macht ihren Ueberlauf gerade **definiert**,
/// also still. `tsd_in_cent` (T50) vervielfacht blank mit 100.000 und hat weder
/// Division noch 128-Bit-Zwischenwert noch Addition; sein Ergebnis geht nach T47
/// unmittelbar ins Fondsvermoegen. Ohne diese Funktion waere das ein stiller
/// Umbruch statt eines Abbruchs -- und T7 sagt in seiner Ueberschrift das
/// Gegenteil zu.
///
/// **Der Zwischenwert kann nicht selbst ueberlaufen**, das Argument steht im Zitat
/// und ist dasselbe, das `potenz` und `mal_geteilt` schon fuehren: Beide Faktoren
/// liegen dem Betrag nach unter 2^63, das Produkt also unter 2^126. Abbrechen kann
/// allein die Verengung am Ende -- und sie bricht ab, statt zu kappen.
///
/// **Heute mit fuenf Aufrufern, und alle fuenf stehen in `kern::werte`.** Selbst
/// gemessen am 2026-09-05 auf dem Stand `f6731fe`, mit einem Mustervergleich ueber
/// `kern/`, `pruefstand/` und `werkzeuge/` ausserhalb von `bau/` und `befunde/`. In
/// `pruefstand/` und `werkzeuge/` steht kein Aufruf; die Aufrufe in `festkomma_probe`
/// sind nicht mitgezaehlt, weil sie diese Funktion pruefen, statt sie zu benutzen.
///
/// Welche Rechenarten dort ueber sie laufen: `tsd_in_cent` vervielfacht blank mit der
/// Skalenzahl aus T5 -- der Fall, den die Begruendung oben schon nennt;
/// `lobbypunkte_aus_geld` bildet aus `lobbykosten` und `rabatt` den Nenner eines
/// `mal_geteilt`; `positionswert_aus` vervielfacht die Stufenzahl mit dem Stufenwert;
/// `korbbestand` und `fondsanteil` vervielfachen den Betrag der Stufenzahl mit
/// `stufenweite`. Die letzten drei sind die fuenfte Rechenart aus T7 in Reinform --
/// zwei `i64` mit Groessenbedeutung nach T5 --, die ersten beiden zeigen, dass 4.3
/// auch dort greift, wo ein Faktor eine Skalen- oder Kalibrierzahl ist.
///
/// **Dass die Funktion hier steht und nicht bei ihrem ersten Aufrufer, haengt nicht
/// an dieser Zahl.** Der Grund ist T6 und derselbe, den die Strichrechnung oben
/// ausfuehrt: Diese Datei ist die einzige Rechenstelle des Kerns. Waere die Zahl
/// wieder null, stuende die Funktion aus demselben Grund weiter hier.
constexpr i64 mal(i64 a, i64 b)
{
    const i128 produkt = static_cast<i128>(a) * static_cast<i128>(b);
    return intern::nach_i64(produkt, "mal: Ergebnis ausserhalb von i64 (T7)");
}

/// `basis ^ exponent` als Ganzzahl (T29). Ueberlauf ist ein Abbruch.
///
/// Geschrieben als einfache Schleife statt als schnelle Potenzierung, und das ist
/// Absicht: T29 beschraenkt die Exponenten auf kleine ganze Zahlen, die Schleife ist
/// beim Lesen gegen die Vorgabe pruefbar, und ihre Ueberlaufsicherheit hat ein
/// Argument in einem Satz. Naemlich: Vor jeder Multiplikation gilt
/// `|wert| <= I64_MAX`, weil die Pruefung der vorigen Runde das erzwungen hat; das
/// Produkt zweier solcher Werte bleibt unter 8,6e37 und damit unter der
/// `i128`-Grenze 1,7e38. Es kann also kein Zwischenwert ueberlaufen, bevor der
/// Waechter ihn sieht.
constexpr i64 potenz(i64 basis, unsigned exponent)
{
    i128 wert = 1;
    const i128 b = static_cast<i128>(basis);
    for (unsigned i = 0; i < exponent; ++i) {
        wert *= b;
        if (wert > static_cast<i128>(I64_MAX) || wert < static_cast<i128>(I64_MIN)) {
            abbruch("potenz: Ergebnis ausserhalb von i64 (T7)");
        }
    }
    return static_cast<i64>(wert);
}

/// Feste Schrittzahl fuer `wurzel` (T29). Die Schranke ist grosszuegig: Newton
/// verdoppelt die gueltigen Stellen je Schritt, 63 Bit sind nach ein bis zwei
/// Dutzend Schritten erschoepft. Sie steht trotzdem da, damit die Laufzeit einer
/// Wurzel eine Obergrenze hat und nicht von den Daten abhaengt.
inline constexpr unsigned WURZEL_SCHRITTE = 128;

/// Groesster zugelassener Wurzelgrad. Ueber 32 hinaus ist die Wurzel eines `i64`
/// hoechstens 1 -- und die Schranke haelt zugleich das Ueberlaufargument unten
/// zusammen.
inline constexpr unsigned WURZEL_GRAD_MAX = 32;

/// Abgerundete `n`-te Wurzel von `x` ueber Newton auf `i128` (T29).
///
/// Nachbedingung, und sie ist der Grund, warum das Ergebnis nicht von der Schrittzahl
/// abhaengt: `wurzel(x, n)^n <= x < (wurzel(x, n) + 1)^n`. Newton laeuft mit fester
/// Schranke, die beiden Berichtigungsschleifen danach stellen die Nachbedingung
/// exakt her. Damit ist `WURZEL_SCHRITTE` eine Kostengrenze und keine Genauigkeit --
/// wer sie aendert, aendert das Ergebnis nicht.
///
/// Ueberlauf: Der Startwert ist `2^ceil(bitlaenge(x)/n)`, also die kleinste
/// Zweierpotenz oberhalb der Wurzel. Mit `bitlaenge(x) <= 63` und
/// `n <= WURZEL_GRAD_MAX` bleibt `start^(n-1)` unter `2^95`, und `r` wird nur
/// kleiner. Kein Zwischenwert kommt der `i128`-Grenze nahe.
constexpr i64 wurzel(i64 x, unsigned n)
{
    if (n == 0 || n > WURZEL_GRAD_MAX) {
        abbruch("wurzel: Grad muss zwischen 1 und WURZEL_GRAD_MAX liegen (T29)");
    }
    if (x < 0) {
        abbruch("wurzel: negativer Radikand -- die Produktionsfunktion hat keinen (T29)");
    }
    if (n == 1 || x < 2) { return x; }   // 0 und 1 sind ihre eigene Wurzel

    const i128 ziel = static_cast<i128>(x);
    i128 r = static_cast<i128>(1) << ((intern::bitlaenge(ziel) + n - 1) / n);

    for (unsigned schritt = 0; schritt < WURZEL_SCHRITTE; ++schritt) {
        const i128 naechst = ((static_cast<i128>(n) - 1) * r + ziel / intern::potenz_i128(r, n - 1))
                             / static_cast<i128>(n);
        if (naechst >= r) { break; }     // Newton faellt monoton; Stillstand ist das Ende
        r = naechst;
    }

    while (r > 0 && intern::potenz_i128(r, n) > ziel)      { --r; }
    while (intern::potenz_i128(r + 1, n) <= ziel)          { ++r; }

    return static_cast<i64>(r);
}

}  // namespace kern::festkomma
