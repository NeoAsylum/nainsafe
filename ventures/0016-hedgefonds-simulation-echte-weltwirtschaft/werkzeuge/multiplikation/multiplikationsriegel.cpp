// Der Multiplikationsriegel -- Paket 0273.
//
// Was er durchsetzt: Massnahme 4.3 aus T7. Jede blanke Multiplikation zweier `i64` mit
// Groessenbedeutung (T5) soll durch `mal()` und den `__int128`-Waechter laufen. Ein
// Schloss, das der Uebersetzer haelt, gibt es dafuer nicht -- `#pragma GCC poison` nimmt
// **Bezeichner**, und `*` ist ein Operator (T7 `:909-911`). Bleibt ein Riegel ueber den
// Text.
//
// ---------------------------------------------------------------------------
// Was gelesen wird, ehe eine Regel gilt (T7 `:870-880`)
// ---------------------------------------------------------------------------
//
// Bestand: jede `.hpp` und `.cpp` unter `kern/include` und `kern/src` der uebergebenen
// Wurzel. Aus jeder Zeile faellt der Kommentartext -- und **der Inhalt** jeder
// Zeichenkette und Zeichenkonstante. Die Grenzzeichen bleiben stehen: aus
// `"a*b sprengt i64"` wird `""`, aus `'*'` wird `''`. Damit ist die Operandenstruktur der
// Zeile unveraendert, und genau darauf beruht Regel 5: T7 `:5851` rechnet ausdruecklich
// damit, dass hinter der Lesung noch `== 152, ""` in der Zeile steht.
//
// Das einfache Anfuehrungszeichen ist zweideutig -- es begrenzt eine Zeichenkonstante und
// trennt Ziffergruppen (`1'000'000`). Unterschieden wird wie im Bezeichnerriegel: Steht
// links davon ein Wort, das mit einer Ziffer anfaengt, ist es ein Trenner.
//
// Rohe Zeichenketten (`R"(...)"`) kann diese Lesung nicht, und deshalb bricht sie laut ab,
// statt still daran vorbeizulesen. Im Kern steht heute keine.
//
// ---------------------------------------------------------------------------
// Welcher `*` ueberhaupt geprueft wird
// ---------------------------------------------------------------------------
//
// **Beide Schreibweisen** (T7 `:868`), und nur diese beiden:
//
//   weit -- Leerraum links **und** rechts:      `a * b`
//   eng  -- Namenszeichen links **und** rechts: `a*b`
//
// Das ist keine Verlegenheit, sondern die Grenze, die den Operator vom Zeiger trennt:
// `const char* s`, `*p`, `char** argv` erfuellen keine der beiden Bedingungen und sind
// damit gar nicht erst Gegenstand. Die Gegenprobe steht als Fall in `REGELFAELLE`.
//
// ---------------------------------------------------------------------------
// Die fuenf benannten Regeln, erste Uebereinstimmung gewinnt (T7 `:842-860`)
// ---------------------------------------------------------------------------
//
//   1. Ein Operand ist eine **Layoutkonstante** -- `constexpr` und vom Typ `Index` oder
//      `std::size_t`. Die Namensliste dazu baut der Riegel aus den Deklarationen des
//      Bestands, er traegt sie nicht bei sich.
//   2. `sizeof(...)` auf einer der beiden Seiten.
//   3. Ein vorzeichenloses Literal (`5ULL`, `8u`) oder eine benannte `u64`-Konstante --
//      dieselbe Namensliste, aus `constexpr u64`-Deklarationen gebaut.
//   4. `static_cast<i128>` am **Kopf** wenigstens eines der beiden Operandenlaeufe, und
//      dieser Lauf traegt kein `?` -- die Rechenstelle aus T6. **Eine** Seite genuegt:
//      Traegt ein Operand den Typ `i128`, wandeln die ueblichen arithmetischen
//      Umwandlungen den anderen vor der Multiplikation ebenfalls dorthin, und dann steht
//      auf der Zeile gar keine `i64`-Multiplikation mehr -- genau der Fall, gegen den
//      Massnahme 4.3 geschrieben ist. Warum am Kopf und warum ohne `?`, steht gleich
//      darunter.
//   5. Beide Operanden sind ganzzahlige Literale **und** der `*` steht in der Bedingung
//      eines `static_assert`. Das Alphabet des Operandenbereichs: Ziffern, der Trenner
//      `'`, Leerraum, Klammern und `+ - *`. Der Bereich reicht vom `*` bis zur naechsten
//      **Grenze** -- `==`, `!=` oder das Komma auf oberster Ebene vor der Meldung --, sonst
//      bis zur Klammer des `static_assert`. **Nur diese drei enden den Bereich** (T7
//      `:857-858`); jedes andere Zeichen ausserhalb des Alphabets *innerhalb* des
//      Bereichs, `/` zum Beispiel, ist ein **Befund** und keine Grenze.
//
// Alles andere ist ein Befund -- die fuenfte Sorte, zwei `i64` mit Groessenbedeutung.
// Ablehnung im Zweifel ist der ganze Zweck.
//
// ---------------------------------------------------------------------------
// Wie Regel 4 den Kopf eines Laufs liest -- Abschnitt 35 leitet beides her
// ---------------------------------------------------------------------------
//
// Der Operandenlauf neben dem `*` wird leerraumbefreit; dann fallen umschliessende
// Klammern, solange die oeffnende **keine** Argumentliste ist -- ein `(`, dem unmittelbar
// ein Namenszeichen vorangeht, gehoert zu einem Aufruf. Was uebrig bleibt, muss mit
// `static_cast<i128>` anfangen.
//
// **Warum am Kopf und nicht irgendwo im Lauf.** In einem Operandenlauf stehen Aufrufe --
// `festkomma.hpp:356` traegt selbst einen. `f(static_cast<i128>(a)) * b` traegt den Text,
// aber ueber den Typ entscheidet der **Rueckgabetyp** von `f`, und die Multiplikation
// kann trotz des Textes `i64 * i64` sein.
//
// **Warum kein `?` im Lauf.** Ein Bedingungsausdruck nimmt seinen Typ aus den beiden
// Zweigen und nicht aus seinem Kopf; `static_cast<i128>(a) > 0 ? x : y` bestuende die
// Kopfprobe und bewiese nichts. Die Bedingung kostet heute keine Zeile: die einzige Zeile
// des Bestands, die `?` und `*` traegt, ist `zustand.hpp:777`, und dort steht das `?`
// ausserhalb beider Laeufe (gemessen zu Paket `0274` am 2026-09-09).
//
// ---------------------------------------------------------------------------
// Die Messung am HEAD des 2026-09-08, und die eine Zeile, die uebrig bleibt
// ---------------------------------------------------------------------------
//
// Die Zahl steht nicht hier fest, sondern wird bei jedem Lauf neu gerechnet und
// ausgegeben. Von Hand nachgezaehlt wurde sie trotzdem, weil eine Zahl ohne Gegenprobe
// nichts belegt: **36 Zeilen, 42 Vorkommen, in 14 Dateien** -- die 92 Zeilen der
// Zuordnungstabelle in T7 `:927-945` minus die 56, die laufender Text in einem Kommentar
// sind; die beiden engen Treffer (`festkomma.cpp:91` als Zeichenkette,
// `meldung.hpp:54` als Kommentar) fallen mit derselben Lesung heraus. Die Zeilenzahl
// stimmt mit T7 `:882-888` ueberein.
//
// **Der Riegel ist rot, und zwar an einer Zeile:**
//
//   `kern/include/kern/festkomma.hpp:99`
//       const i128 rest = az - ganz * an;
//       Beide Operanden sind blanke `const i128`-Ortsgroessen. Kein `Index`, kein
//       `std::size_t` (1), kein `sizeof` (2), kein vorzeichenloses Literal und keine
//       `u64`-Konstante (3), auf **keiner** Seite ein `static_cast<i128>` (4), kein
//       `static_assert` (5). Textlich ist die Zeile `name * name` -- die Gestalt der
//       fuenften Sorte. Keine Textregel erreicht sie, ohne `stufen * stufenwert`
//       mitzunehmen, und T7 `:890-894` sagt das inzwischen selbst. Aufgeloest wird sie
//       an der Quelle: mit `ganz = az / an` eine Zeile darueber **ist** `az - ganz * an`
//       gleich `az % an`. Das ist ein Paket unter `kern/` und nicht dieses.
//
// Die zweite rote Zeile war `kern/include/kern/festkomma.hpp:356` --
// `((static_cast<i128>(n) - 1) * r`. Der Cast steht am Kopf des linken Laufs, die
// umschliessende Klammer ist keine Argumentliste, rechts steht das blanke `r`: seit der
// Weitung von Regel 4 (Paket `0274`) faellt sie unter eine benannte Regel. Der Riegel
// senkt dabei keine Latte und erfindet keine sechste Regel -- er folgt T7 und nicht
// umgekehrt.
//
// Die von Hand nachgezaehlte Verteilung, zur Gegenprobe gegen die Ausgabe des Laufs:
// Regel 1 -- 31 Vorkommen in 26 Zeilen; Regel 2 -- keines; Regel 3 -- 6 in 5 Zeilen;
// Regel 4 -- 3 in 3 Zeilen (`festkomma.hpp:161,292,356`); Regel 5 -- 1
// (`schritt.cpp:405`); Befund -- 1 in 1 Zeile. Dass Regel 2 auf nichts trifft, ist kein
// Fehler: `zustand.hpp:496` und `verlauf.hpp:377,379` tragen zwar `sizeof`, aber Regel 1
// greift davor.
//
// ---------------------------------------------------------------------------
// Die blinden Flecken, ausgeschrieben
// ---------------------------------------------------------------------------
//
// 1. **Die Namensliste ist eine Liste, kein Geltungsbereich.** Sie wird ueber den ganzen
//    Bestand gebaut, wie T7 es vorschreibt. Heisst irgendwo eine `constexpr
//    std::size_t`-Konstante `n`, dann faellt jede Multiplikation mit einem Operanden `n`
//    unter Regel 1 -- auch in einer anderen Datei und auch, wenn dort ein `i64` gemeint
//    ist. Enger ginge es nur mit einem Geltungsbereich, und den hat ein Textriegel nicht.
//    Gemildert ist es dadurch, dass nur `constexpr`-Deklarationen zaehlen: Zaehlschleifen
//    (`for (std::size_t i = ...)`) kommen so gar nicht erst in die Liste, und genau
//    deshalb faellt `pruefsumme.hpp:138` (`8u * i`) unter Regel 3 und nicht unter Regel 1.
//
// 2. **Der Operandenbereich ist gelaufen, nicht geparst.** Rueckwaerts wie vorwaerts wird
//    ueber Namen, Klammergruppen und `<...>` vor einer Klammer gelaufen. Ein `>` gilt nur
//    unmittelbar hinter einer Klammergruppe als Ende einer Argumentliste
//    (`static_cast<i128>(a)`, `linksrotieren<7>(...)`) -- sonst ist es ein Vergleich. Wo
//    dieser Lauf zu kurz greift, faellt eine Regel aus und es entsteht ein **Befund**,
//    also ein lautes Ergebnis. Die andere Richtung, ein zu langer Lauf, koennte eine Regel
//    faelschlich greifen lassen; dagegen steht, dass der Lauf nur an Zeichen weitergeht,
//    die zum Operanden gehoeren koennen.
//
// 3. **Der Selbsttest prueft eine Datei je Fall.** Regel 1 loest im echten Lauf auch dann
//    aus, wenn die Konstante in einer **anderen** Datei des Bestands deklariert ist; ein
//    Fall dieser Form laesst sich mit der Konstruktion hier nicht bauen, weil ein
//    `Regelfall` genau einen Text traegt. Die Faelle 1 und 2 deklarieren die Konstante
//    deshalb im selben Text. Das ist die einzige Bedingung des Pakets, die als Fall nicht
//    darstellbar ist -- sie steht hier statt als Schweigen.
//
// 4. **`static_assert` wird an seiner Klammer erkannt, nicht am `;`.** T7 `:5845`
//    beschreibt den Zustand als „opens at `static_assert(` and closes at the next `;`".
//    Hier schliesst er an der zugehoerigen Klammer. Fuer wohlgeformten Text ist das
//    dasselbe, und es ist genau die Grenze, die Regel 5 als „its closing `)`" benennt.
//
// ---------------------------------------------------------------------------
// Bau
// ---------------------------------------------------------------------------
//
// Nichts ausser der Standardbibliothek, wie bei den vier Riegeln daneben. Der
// Bezeichnerriegel ist das **Vorbild** fuer die Lesung (`:228-233`, `:253-271`) und
// ausdruecklich keine Abhaengigkeit: Ein gemeinsamer Kopf waere ein zweites Paket und eine
// zweite Datei in zwei Anspruchslisten.

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Zeichenklassen
// ---------------------------------------------------------------------------

bool ist_ziffer(char c) { return c >= '0' && c <= '9'; }

bool ist_klein(char c) { return c >= 'a' && c <= 'z'; }

bool ist_gross(char c) { return c >= 'A' && c <= 'Z'; }

bool ist_buchstabe(char c) { return ist_klein(c) || ist_gross(c); }

bool ist_namenszeichen(char c) { return ist_buchstabe(c) || ist_ziffer(c) || c == '_'; }

bool ist_namensanfang(char c) { return ist_buchstabe(c) || c == '_'; }

bool ist_leerraum(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

/// Der Nichtwert fuer einen Index. Ausgeschrieben, weil `0` ein gueltiger Index ist.
constexpr std::size_t NICHTS = static_cast<std::size_t>(-1);

// ---------------------------------------------------------------------------
// Die Lesung: Kommentartext faellt, Literalinhalt faellt, die Grenzen bleiben
// ---------------------------------------------------------------------------

/// Der gelesene Text einer Datei. `zeile` laeuft zeichenweise neben `maske` her; ohne das
/// kann kein Befund sagen, wo er steht.
struct Gelesen {
    std::string              maske;
    std::vector<std::size_t> zeile;
    bool                     rohe_zeichenkette = false;
    std::size_t              rohe_zeile = 0;
};

/// Ob an `i` eine rohe Zeichenkette beginnt -- `R` unmittelbar vor einem
/// Anfuehrungszeichen, und `R` nicht selbst Teil eines Namens.
bool beginnt_rohe_zeichenkette(std::string_view text, std::size_t i)
{
    if (text[i] != 'R' || i + 1 >= text.size() || text[i + 1] != '"') {
        return false;
    }
    return i == 0 || !ist_namenszeichen(text[i - 1]);
}

/// Ob das Anfuehrungszeichen an `i` Ziffergruppen trennt (`1'000'000`) statt eine
/// Zeichenkonstante zu eroeffnen. Zurueckgelaufen wird bis zum Anfang des Wortes davor;
/// faengt es mit einer Ziffer an, ist es eine Zahl. Das trifft auch `0x1F'00`.
bool ist_ziffertrenner(std::string_view text, std::size_t i)
{
    if (i == 0 || !ist_namenszeichen(text[i - 1])) {
        return false;
    }
    std::size_t anfang = i - 1;
    while (anfang > 0 && ist_namenszeichen(text[anfang - 1])) {
        --anfang;
    }
    return ist_ziffer(text[anfang]);
}

Gelesen lies(std::string_view text)
{
    Gelesen           g;
    const std::size_t n = text.size();
    std::size_t       i = 0;
    std::size_t       zl = 1;

    // Immer ueber diese Stelle anhaengen, damit Maske und Zeilenzahl nie auseinanderlaufen.
    const auto anhaengen = [&g](char zeichen, std::size_t nr) {
        g.maske.push_back(zeichen);
        g.zeile.push_back(nr);
    };

    while (i < n) {
        const char c = text[i];

        if (c == '\n') {
            anhaengen('\n', zl);
            ++zl;
            ++i;
            continue;
        }

        // Zeilenkommentar: nichts ausgeben, den Zeilenumbruch stehen lassen.
        if (c == '/' && i + 1 < n && text[i + 1] == '/') {
            while (i < n && text[i] != '\n') {
                ++i;
            }
            continue;
        }

        // Blockkommentar: ein Leerzeichen, damit nichts zusammenwaechst, was getrennt
        // geschrieben war -- und je Umbruch darin einer, damit die Zeilenzahl stimmt.
        if (c == '/' && i + 1 < n && text[i + 1] == '*') {
            anhaengen(' ', zl);
            i += 2;
            while (i < n && !(text[i] == '*' && i + 1 < n && text[i + 1] == '/')) {
                if (text[i] == '\n') {
                    anhaengen('\n', zl);
                    ++zl;
                }
                ++i;
            }
            i = (i < n) ? i + 2 : n;
            continue;
        }

        // Rohe Zeichenkette: nicht behandelt, und deshalb laut. Weitergelesen wird
        // trotzdem, damit die Meldung die erste Fundstelle nennen kann.
        if (beginnt_rohe_zeichenkette(text, i)) {
            if (!g.rohe_zeichenkette) {
                g.rohe_zeichenkette = true;
                g.rohe_zeile = zl;
            }
            anhaengen(' ', zl);
            i += 2;
            continue;
        }

        // Zeichenkonstante -- die beiden Grenzen bleiben, der Inhalt faellt.
        if (c == '\'' && !ist_ziffertrenner(text, i)) {
            anhaengen('\'', zl);
            ++i;
            while (i < n && text[i] != '\'') {
                if (text[i] == '\\' && i + 1 < n) {
                    ++i;
                }
                if (text[i] == '\n') {
                    ++zl;
                }
                ++i;
            }
            anhaengen('\'', zl);
            i = (i < n) ? i + 1 : n;
            continue;
        }

        // Zeichenkette -- ebenso. Benachbarte Teile bleiben getrennte Paare; die Sprache
        // setzt sie zusammen, aber fuer die Operandenstruktur der Zeile aendert das nichts.
        if (c == '"') {
            anhaengen('"', zl);
            ++i;
            while (i < n && text[i] != '"') {
                if (text[i] == '\\' && i + 1 < n) {
                    ++i;
                }
                if (text[i] == '\n') {
                    ++zl;
                }
                ++i;
            }
            anhaengen('"', zl);
            i = (i < n) ? i + 1 : n;
            continue;
        }

        anhaengen(c, zl);
        ++i;
    }
    return g;
}

// ---------------------------------------------------------------------------
// Klammern, vorwaerts und rueckwaerts
// ---------------------------------------------------------------------------

std::size_t rueck_klammer(const std::string& m, std::size_t zu)
{
    const char  schliess = m[zu];
    const char  oeffne = (schliess == ')') ? '(' : '[';
    std::size_t tiefe = 0;
    std::size_t j = zu + 1;
    while (j > 0) {
        --j;
        if (m[j] == schliess) {
            ++tiefe;
        } else if (m[j] == oeffne) {
            --tiefe;
            if (tiefe == 0) {
                return j;
            }
        }
    }
    return NICHTS;
}

std::size_t vor_klammer(const std::string& m, std::size_t auf)
{
    const char  oeffne = m[auf];
    const char  schliess = (oeffne == '(') ? ')' : ']';
    std::size_t tiefe = 0;
    for (std::size_t j = auf; j < m.size(); ++j) {
        if (m[j] == oeffne) {
            ++tiefe;
        } else if (m[j] == schliess) {
            --tiefe;
            if (tiefe == 0) {
                return j;
            }
        }
    }
    return NICHTS;
}

/// Das `<` zum `>` an `zu`. Ein `;` oder eine geschweifte Klammer dazwischen heisst: Das
/// war kein Argumentklammerpaar, sondern ein Vergleich.
std::size_t rueck_winkel(const std::string& m, std::size_t zu)
{
    std::size_t tiefe = 0;
    std::size_t j = zu + 1;
    while (j > 0) {
        --j;
        if (m[j] == '>') {
            ++tiefe;
        } else if (m[j] == '<') {
            --tiefe;
            if (tiefe == 0) {
                return j;
            }
        } else if (m[j] == ';' || m[j] == '{' || m[j] == '}') {
            return NICHTS;
        }
    }
    return NICHTS;
}

std::size_t vor_winkel(const std::string& m, std::size_t auf)
{
    std::size_t tiefe = 0;
    for (std::size_t j = auf; j < m.size(); ++j) {
        if (m[j] == '<') {
            ++tiefe;
        } else if (m[j] == '>') {
            --tiefe;
            if (tiefe == 0) {
                return j;
            }
        } else if (m[j] == ';' || m[j] == '{' || m[j] == '}') {
            return NICHTS;
        }
    }
    return NICHTS;
}

// ---------------------------------------------------------------------------
// Welcher `*` gehoert dem Riegel
// ---------------------------------------------------------------------------

/// Beide Schreibweisen aus T7 `:868` und keine dritte. Ein `*`, der links ein
/// Namenszeichen und rechts Leerraum hat, ist ein Zeiger und kein Operator.
bool ist_binaeres_mal(const std::string& m, std::size_t i)
{
    if (m[i] != '*' || i == 0 || i + 1 >= m.size()) {
        return false;
    }
    const bool weit = ist_leerraum(m[i - 1]) && ist_leerraum(m[i + 1]);
    const bool eng = ist_namenszeichen(m[i - 1]) && ist_namenszeichen(m[i + 1]);
    return weit || eng;
}

// ---------------------------------------------------------------------------
// Die beiden Operandenbereiche
// ---------------------------------------------------------------------------

struct Bereich {
    std::size_t auf = 0;
    std::size_t zu = 0;  // ausschliesslich
};

/// Ob `m[j]` zu einem Wort gehoert -- Namenszeichen, oder der Ziffertrenner zwischen zwei
/// Ziffern.
bool gehoert_zum_wort(const std::string& m, std::size_t j)
{
    if (ist_namenszeichen(m[j])) {
        return true;
    }
    return m[j] == '\'' && j > 0 && ist_ziffer(m[j - 1]) && j + 1 < m.size()
           && ist_ziffer(m[j + 1]);
}

Bereich linker_operand(const std::string& m, std::size_t stern)
{
    std::size_t j = stern;
    while (j > 0 && ist_leerraum(m[j - 1])) {
        --j;
    }
    const std::size_t ende = j;
    bool              gruppe = false;
    while (j > 0) {
        const char c = m[j - 1];
        if (c == ')' || c == ']') {
            const std::size_t auf = rueck_klammer(m, j - 1);
            if (auf == NICHTS) {
                break;
            }
            j = auf;
            gruppe = true;
            continue;
        }
        if (c == '>' && gruppe) {
            const std::size_t auf = rueck_winkel(m, j - 1);
            if (auf == NICHTS) {
                break;
            }
            j = auf;
            gruppe = false;
            continue;
        }
        if (gehoert_zum_wort(m, j - 1)) {
            while (j > 0 && gehoert_zum_wort(m, j - 1)) {
                --j;
            }
            gruppe = false;
            if (j >= 2 && m[j - 1] == ':' && m[j - 2] == ':') {
                j -= 2;
                continue;
            }
            break;
        }
        break;
    }
    return Bereich{j, ende};
}

Bereich rechter_operand(const std::string& m, std::size_t stern)
{
    const std::size_t n = m.size();
    std::size_t       j = stern + 1;
    while (j < n && ist_leerraum(m[j])) {
        ++j;
    }
    while (j < n && (m[j] == '-' || m[j] == '+')) {
        ++j;
        while (j < n && ist_leerraum(m[j])) {
            ++j;
        }
    }
    const std::size_t anfang = j;
    bool              weiter = true;
    while (weiter && j < n) {
        weiter = false;
        const char c = m[j];
        if (c == '(' || c == '[') {
            const std::size_t zu = vor_klammer(m, j);
            if (zu == NICHTS) {
                break;
            }
            j = zu + 1;
            weiter = true;
            continue;
        }
        if (gehoert_zum_wort(m, j)) {
            while (j < n && gehoert_zum_wort(m, j)) {
                ++j;
            }
            if (j + 1 < n && m[j] == ':' && m[j + 1] == ':') {
                j += 2;
                weiter = true;
                continue;
            }
            if (j < n && m[j] == '<') {
                const std::size_t zu = vor_winkel(m, j);
                if (zu != NICHTS && zu + 1 < n && m[zu + 1] == '(') {
                    j = zu + 1;
                    weiter = true;
                    continue;
                }
            }
            if (j < n && (m[j] == '(' || m[j] == '[')) {
                weiter = true;
            }
            continue;
        }
    }
    return Bereich{anfang, j};
}

std::string_view ausschnitt(const std::string& m, const Bereich& b)
{
    return std::string_view(m.data() + b.auf, b.zu - b.auf);
}

// ---------------------------------------------------------------------------
// Die Proben, die eine Regel stellt
// ---------------------------------------------------------------------------

/// Ob in `b` ein Wort steht, das in `tabelle` gefuehrt wird.
bool traegt_namen(std::string_view b, const std::vector<std::string>& tabelle)
{
    std::size_t i = 0;
    while (i < b.size()) {
        if (!ist_namensanfang(b[i]) || (i > 0 && ist_namenszeichen(b[i - 1]))) {
            ++i;
            continue;
        }
        const std::size_t auf = i;
        while (i < b.size() && ist_namenszeichen(b[i])) {
            ++i;
        }
        const std::string_view wort = b.substr(auf, i - auf);
        for (std::size_t k = 0; k < tabelle.size(); ++k) {
            if (std::string_view(tabelle[k]) == wort) {
                return true;
            }
        }
    }
    return false;
}

bool traegt_wort(std::string_view b, std::string_view gesucht)
{
    std::size_t i = 0;
    while (i < b.size()) {
        if (!ist_namensanfang(b[i]) || (i > 0 && ist_namenszeichen(b[i - 1]))) {
            ++i;
            continue;
        }
        const std::size_t auf = i;
        while (i < b.size() && ist_namenszeichen(b[i])) {
            ++i;
        }
        if (b.substr(auf, i - auf) == gesucht) {
            return true;
        }
    }
    return false;
}

/// Ein Zahlwort mit vorzeichenlosem Anhang -- `8u`, `5ULL`, `0xFFu`. Hexziffern tragen
/// kein `u`, deshalb reicht die Suche nach dem Buchstaben im ganzen Wort.
bool traegt_vorzeichenlose_zahl(std::string_view b)
{
    std::size_t i = 0;
    while (i < b.size()) {
        if (!ist_ziffer(b[i]) || (i > 0 && (ist_namenszeichen(b[i - 1]) || b[i - 1] == '\''))) {
            ++i;
            continue;
        }
        const std::size_t auf = i;
        while (i < b.size() && (ist_namenszeichen(b[i]) || b[i] == '\'')) {
            ++i;
        }
        for (std::size_t k = auf; k < i; ++k) {
            if (b[k] == 'u' || b[k] == 'U') {
                return true;
            }
        }
    }
    return false;
}

/// Regel 4 nach T7 `:847-851`: `static_cast<i128>` am **Kopf** dieses Laufs, und der Lauf
/// traegt kein `?`. Erst faellt der Leerraum -- diese Stelle gab es schon, und sie ist die
/// richtige --, dann fallen umschliessende Klammern, solange die oeffnende **keine**
/// Argumentliste ist: Ein `(`, dem unmittelbar ein Namenszeichen vorangeht, gehoert zu
/// einem Aufruf, und ueber den Typ entscheidet dann dessen Rueckgabetyp und nicht der Text
/// darin (`f(static_cast<i128>(a)) * b`). Am **ersten** Zeichen des Laufs kann so ein `(`
/// nicht stehen, weil der Ruecklauf den Namen mit in den Lauf nimmt (`linker_operand`);
/// die Probe traegt ab der zweiten Klammer, und sie steht ausgeschrieben da, weil T7 sie
/// nennt und nicht ihre Folgerung.
bool kopf_ist_i128_umdeutung(std::string_view b)
{
    static constexpr std::string_view UMDEUTUNG = "static_cast<i128>";

    std::string eng;
    eng.reserve(b.size());
    for (std::size_t i = 0; i < b.size(); ++i) {
        if (!ist_leerraum(b[i])) {
            eng.push_back(b[i]);
        }
    }
    if (eng.find('?') != std::string::npos) {
        return false;
    }
    std::size_t auf = 0;
    std::size_t zu = eng.size();
    while (auf + 1 < zu && eng[auf] == '(' && !(auf > 0 && ist_namenszeichen(eng[auf - 1]))
           && vor_klammer(eng, auf) == zu - 1) {
        ++auf;
        --zu;
    }
    return std::string_view(eng).substr(auf, zu - auf).starts_with(UMDEUTUNG);
}

// ---------------------------------------------------------------------------
// Die Namensliste aus den Deklarationen des Bestands
// ---------------------------------------------------------------------------

/// Liest ab `j` das naechste Wort; `std::size_t` kommt als **ein** Wort zurueck.
bool naechstes_wort(const std::string& m, std::size_t& j, std::string& wort)
{
    const std::size_t n = m.size();
    while (j < n && ist_leerraum(m[j])) {
        ++j;
    }
    if (j >= n || !ist_namensanfang(m[j])) {
        return false;
    }
    wort.clear();
    while (true) {
        const std::size_t auf = j;
        while (j < n && ist_namenszeichen(m[j])) {
            ++j;
        }
        wort.append(m, auf, j - auf);
        if (j + 1 < n && m[j] == ':' && m[j + 1] == ':') {
            wort.append("::");
            j += 2;
            continue;
        }
        break;
    }
    return true;
}

/// Baut die beiden Namenslisten. **Nur `constexpr`**: Regel 1 spricht von einer
/// *Layoutkonstante*, nicht von jeder Groesse dieses Typs, und eine Zaehlschleife
/// `for (std::size_t i = ...)` darf den Namen `i` nicht in die Liste bringen. Ein Name,
/// hinter dem unmittelbar `(` steht, ist eine Funktion und keine Konstante.
void sammle_namen(const std::string& m, std::vector<std::string>& layout,
                  std::vector<std::string>& vorzeichenlos)
{
    const std::size_t n = m.size();
    std::size_t       i = 0;
    while (i < n) {
        if (!ist_namensanfang(m[i]) || (i > 0 && ist_namenszeichen(m[i - 1]))) {
            ++i;
            continue;
        }
        const std::size_t auf = i;
        while (i < n && ist_namenszeichen(m[i])) {
            ++i;
        }
        if (std::string_view(m.data() + auf, i - auf) != "constexpr") {
            continue;
        }

        std::size_t j = i;
        std::string wort;
        bool        gelesen = naechstes_wort(m, j, wort);
        while (gelesen && (wort == "const" || wort == "inline" || wort == "static")) {
            gelesen = naechstes_wort(m, j, wort);
        }
        if (!gelesen) {
            continue;
        }
        const bool ist_layout = (wort == "Index" || wort == "std::size_t" || wort == "size_t");
        const bool ist_u64 =
            (wort == "u64" || wort == "std::uint64_t" || wort == "uint64_t");
        if (!ist_layout && !ist_u64) {
            continue;
        }

        std::string name;
        if (!naechstes_wort(m, j, name)) {
            continue;
        }
        std::size_t k = j;
        while (k < n && ist_leerraum(m[k])) {
            ++k;
        }
        if (k < n && m[k] == '(') {
            continue;
        }
        if (ist_layout) {
            layout.push_back(name);
        } else {
            vorzeichenlos.push_back(name);
        }
    }
}

// ---------------------------------------------------------------------------
// Regel 5: der Bereich mit seinen drei Grenzen
// ---------------------------------------------------------------------------

/// Die Klammern eines `static_assert`.
struct Behauptung {
    std::size_t auf = 0;  // die oeffnende Klammer
    std::size_t zu = 0;   // die zugehoerige schliessende
};

std::vector<Behauptung> finde_behauptungen(const std::string& m)
{
    std::vector<Behauptung> raus;
    const std::string_view  marke = "static_assert";
    std::size_t             i = m.find(marke);
    while (i != std::string::npos) {
        const bool  frei = (i == 0) || !ist_namenszeichen(m[i - 1]);
        std::size_t j = i + marke.size();
        while (j < m.size() && ist_leerraum(m[j])) {
            ++j;
        }
        if (frei && j < m.size() && m[j] == '(') {
            const std::size_t zu = vor_klammer(m, j);
            if (zu != NICHTS) {
                raus.push_back(Behauptung{j, zu});
            }
        }
        i = m.find(marke, i + marke.size());
    }
    return raus;
}

const Behauptung* umgebende_behauptung(const std::vector<Behauptung>& alle, std::size_t stern)
{
    const Behauptung* treffer = nullptr;
    for (std::size_t i = 0; i < alle.size(); ++i) {
        if (alle[i].auf < stern && stern < alle[i].zu) {
            treffer = &alle[i];
        }
    }
    return treffer;
}

/// Das Alphabet des Operandenbereichs aus T7 `:847-848`.
bool im_alphabet(char c)
{
    return ist_ziffer(c) || c == '\'' || ist_leerraum(c) || c == '(' || c == ')' || c == '+'
           || c == '-' || c == '*';
}

/// Regel 5. Die Grenzen sind `==`, `!=` und das Komma auf oberster Ebene -- **nur diese
/// drei**. Ein `/` im Bereich ist deshalb kein Ende, sondern ein Zeichen ausserhalb des
/// Alphabets, und damit faellt `static_assert(4 * 3 / 2 == 6)` durch.
bool traegt_nur_literale(const std::string& m, std::size_t stern, const Behauptung& b)
{
    std::size_t links = b.auf + 1;
    std::size_t tiefe = 0;
    for (std::size_t j = b.auf + 1; j < stern; ++j) {
        const char c = m[j];
        if (c == '(' || c == '[') {
            ++tiefe;
        } else if (c == ')' || c == ']') {
            if (tiefe > 0) {
                --tiefe;
            }
        } else if (tiefe == 0) {
            if ((c == '=' || c == '!') && j + 1 < m.size() && m[j + 1] == '=') {
                links = j + 2;
            } else if (c == ',') {
                links = j + 1;
            }
        }
    }

    std::size_t rechts = b.zu;
    tiefe = 0;
    for (std::size_t j = stern + 1; j < b.zu; ++j) {
        const char c = m[j];
        if (c == '(' || c == '[') {
            ++tiefe;
        } else if (c == ')' || c == ']') {
            if (tiefe > 0) {
                --tiefe;
            }
        } else if (tiefe == 0) {
            if (((c == '=' || c == '!') && j + 1 < m.size() && m[j + 1] == '=') || c == ',') {
                rechts = j;
                break;
            }
        }
    }

    for (std::size_t j = links; j < rechts; ++j) {
        if (!im_alphabet(m[j])) {
            return false;
        }
    }
    return links < rechts;
}

// ---------------------------------------------------------------------------
// Die Einordnung
// ---------------------------------------------------------------------------

enum class Regel : std::size_t {
    Layout,
    Sizeof,
    Vorzeichenlos,
    I128,
    Literal,
    Keine,
    Anzahl
};

constexpr std::size_t REGELN = 6;

/// Die Namensliste haengt an der Aufzaehlung und nicht neben ihr: Wer eine sechste Sorte
/// einfuegt, bricht hier ab, statt sie stumm ohne Namen auszugeben.
static_assert(static_cast<std::size_t>(Regel::Anzahl) == REGELN,
              "REGELN zaehlt die fuenf Regeln und den Befund");

constexpr std::array<std::string_view, REGELN> REGELNAMEN = {
    "Regel 1  Layoutkonstante (Index, std::size_t)",
    "Regel 2  sizeof",
    "Regel 3  vorzeichenlos (Literal oder u64-Konstante)",
    "Regel 4  static_cast<i128> am Kopf einer Seite, kein ?",
    "Regel 5  Literale in der Bedingung eines static_assert",
    "BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)",
};

struct Lage {
    std::vector<std::string> layout;
    std::vector<std::string> vorzeichenlos;
    std::vector<Behauptung>  behauptungen;
};

Regel ordne_ein(const std::string& m, std::size_t stern, const Lage& lage)
{
    const std::string_view links = ausschnitt(m, linker_operand(m, stern));
    const std::string_view rechts = ausschnitt(m, rechter_operand(m, stern));

    if (traegt_namen(links, lage.layout) || traegt_namen(rechts, lage.layout)) {
        return Regel::Layout;
    }
    if (traegt_wort(links, "sizeof") || traegt_wort(rechts, "sizeof")) {
        return Regel::Sizeof;
    }
    if (traegt_vorzeichenlose_zahl(links) || traegt_vorzeichenlose_zahl(rechts)
        || traegt_namen(links, lage.vorzeichenlos) || traegt_namen(rechts, lage.vorzeichenlos)) {
        return Regel::Vorzeichenlos;
    }
    if (kopf_ist_i128_umdeutung(links) || kopf_ist_i128_umdeutung(rechts)) {
        return Regel::I128;
    }
    const Behauptung* b = umgebende_behauptung(lage.behauptungen, stern);
    if (b != nullptr && traegt_nur_literale(m, stern, *b)) {
        return Regel::Literal;
    }
    return Regel::Keine;
}

struct Stelle {
    std::size_t datei = 0;
    std::size_t zeile = 0;
    Regel       regel = Regel::Keine;
};

void ordne_datei_ein(const Gelesen& g, const Lage& lage, std::size_t datei,
                     std::vector<Stelle>& raus)
{
    for (std::size_t i = 0; i < g.maske.size(); ++i) {
        if (!ist_binaeres_mal(g.maske, i)) {
            continue;
        }
        Stelle s;
        s.datei = datei;
        s.zeile = g.zeile[i];
        s.regel = ordne_ein(g.maske, i, lage);
        raus.push_back(s);
    }
}

// ---------------------------------------------------------------------------
// Selbsttest 1: die Lesung
// ---------------------------------------------------------------------------

struct Lesefall {
    std::string_view text;
    std::string_view maske;
};

/// Neun Faelle, und die Haelfte davon ist die Gegenprobe: was **nicht** verschwinden darf.
/// Der Ziffertrenner und die beiden benachbarten Zeichenketten sind keine erfundenen
/// Faelle -- beide stehen im Kern.
constexpr std::array<Lesefall, 9> LESEFAELLE = {{
    {"int x = 1;  // 3 * 4\n", "int x = 1;  \n"},
    {"//! Kern*quelle*\nint y = 2;\n", "\nint y = 2;\n"},
    {"const char* m = \"a*b\";\n", "const char* m = \"\";\n"},
    {"char c = '*';\n", "char c = '';\n"},
    {"i64 g = 1'000'000;\n", "i64 g = 1'000'000;\n"},
    {"i64 x = /* 3 * 4 */ 5;\n", "i64 x =   5;\n"},
    {"a\n/* x\n * y */\nb\n", "a\n \n\nb\n"},
    {"f(\"a*b\" \"c*d\");\n", "f(\"\" \"\");\n"},
    {"f(\"a\\\"b*c\");\n", "f(\"\");\n"},
}};

std::size_t selbsttest_lesung()
{
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < LESEFAELLE.size(); ++i) {
        const Gelesen g = lies(LESEFAELLE[i].text);
        if (g.maske != LESEFAELLE[i].maske || g.zeile.size() != g.maske.size()
            || g.rohe_zeichenkette) {
            std::fprintf(stderr,
                         "  Lesefall %zu: erwartet <%s>, bekommen <%s>\n",
                         i + 1, std::string(LESEFAELLE[i].maske).c_str(), g.maske.c_str());
            ++verfehlt;
        }
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Selbsttest 2: die Regeln
// ---------------------------------------------------------------------------

struct Regelfall {
    std::string_view text;
    std::size_t      sterne;   // wie viele binaere `*` die Lesung uebrig laesst
    Regel            erste;    // die Regel des ersten; `Keine`, wenn es keinen gibt
    std::size_t      befunde;  // wie viele unter gar keine Regel fallen
};

/// Siebenundzwanzig Faelle. Was jeder einzelne belegen soll, steht in T7 oder in Abschnitt
/// 33 und nicht in einer Erfindung dieses Riegels:
///
///   1,2   Regel 1, einmal am Namen und einmal in einer Klammergruppe (`zustand.hpp:874`).
///   3     Regel 2 -- im Bestand trifft sie auf nichts, weil Regel 1 davor greift.
///   4,5   Regel 3, beide Haelften: vorzeichenloses Literal und benannte `u64`-Konstante.
///   6     Regel 4 mit dem Cast auf beiden Seiten -- die Form aus `festkomma.hpp:161,292`.
///   7     Regel 4 mit dem Cast auf **einer** Seite. Bis zur Weitung von Regel 4 war das
///         ein Befund; seither genuegt eine Seite, und der Fall haelt die Weitung fest.
///   8     Regel 5, `schritt.cpp:405` im Wortlaut.
///   9     Regel 5 ueber zwei Zeilen, mit `a*b` in der Meldung (`festkomma.cpp:90-91`).
///   10    Regel 5 hinter der Grenze `!=`.
///   11    `static_assert(4 * 3 / 2 == 6)` -- **kein** Treffer. Der `/` ist ein Befund
///         **im** Bereich und keine Grenze (T7 `:852-853`, Abschnitt 33 `:5858-5861`).
///   12    Literale ohne `static_assert` -- die Haelfte, die T7 `:5836` ausdruecklich
///         nicht zulassen will.
///   13    `static_assert` ohne das Literalalphabet -- die andere Haelfte (`:5839`).
///   14    `<` ist keine Grenze (Abschnitt 33 `:5862-5864`), also ein Befund.
///   15    Die fuenfte Sorte, wie sie im Kern aussaehe.
///   16    Die enge Schreibweise `a*b`.
///   17,18 Ein `*` im Inhalt einer Zeichenkette und einer im Kommentartext -- **kein**
///         Fall darf daraus entstehen (`festkomma.cpp:91`, `meldung.hpp:54`).
///   19    Zeiger in drei Formen: keiner ist ein binaerer `*`.
///   20    Zwei `*` in einer Zeile -- der Unterschied zwischen 36 Zeilen und 42 Vorkommen.
///   21    Ein `*` als Zeichenkonstante.
///   22    Der Ziffertrenner eroeffnet keine Zeichenkonstante, und der `*` dahinter bleibt
///         sichtbar.
///   23    Ein `*` im Blockkommentar.
///   24    Die Gestalt von `festkomma.hpp:356`: der Cast am Kopf des linken Laufs, davor
///         eine umschliessende Klammer, die **keine** Argumentliste ist -- sie faellt ab,
///         und der Kopf ist der Cast. Regel 4.
///   25    Derselbe Cast in der Argumentliste eines Aufrufs -- **Befund**. Der Kopf des
///         Laufs ist `f`, und ueber den Typ entscheidet dessen Rueckgabetyp.
///   26    Der Cast am Kopf, aber ein `?` im Lauf -- **Befund**. Ein Bedingungsausdruck
///         nimmt seinen Typ aus den Zweigen; ohne diese Probe faende die Kopfprobe hier
///         nach dem Abstreifen der Klammer einen Treffer.
///   27    Der Cast an einem **anderen** Glied desselben Ausdrucks -- **Befund**. Die
///         beiden Laeufe neben dem `*` sind `b` und `c` und tragen ihn nicht.
constexpr std::array<Regelfall, 27> REGELFAELLE = {{
    {"inline constexpr Index LAND_FELDER = 44;\nIndex a = nummer * LAND_FELDER;\n",
     1, Regel::Layout, 0},
    {"inline constexpr std::size_t GEBIETE = 5;\nstd::size_t b = v * (GEBIETE - 1);\n",
     1, Regel::Layout, 0},
    {"i64 b = sizeof(Kette) * 3;\n", 1, Regel::Sizeof, 0},
    {"u64 s = 8192u * 1024u;\n", 1, Regel::Vorzeichenlos, 0},
    {"inline constexpr u64 SPLITMIX_FAKTOR_1 = 1;\nu64 z = mix * SPLITMIX_FAKTOR_1;\n",
     1, Regel::Vorzeichenlos, 0},
    {"const i128 p = static_cast<i128>(a) * static_cast<i128>(b);\n", 1, Regel::I128, 0},
    {"const i128 q = static_cast<i128>(n) * r;\n", 1, Regel::I128, 0},
    {"static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, \"T38\");\n", 1, Regel::Literal, 0},
    {"static_assert(2 * 3 == 6,\n              \"a*b\");\n", 1, Regel::Literal, 0},
    {"static_assert(7 != 2 * 4, \"z\");\n", 1, Regel::Literal, 0},
    {"static_assert(4 * 3 / 2 == 6, \"x\");\n", 1, Regel::Keine, 1},
    {"i64 x = 100'000 * 100'000;\n", 1, Regel::Keine, 1},
    {"static_assert(a * b == c, \"m\");\n", 1, Regel::Keine, 1},
    {"static_assert(1 < 4 * 3, \"y\");\n", 1, Regel::Keine, 1},
    {"i64 w = stufen * stufenwert;\n", 1, Regel::Keine, 1},
    {"i64 c = a*b;\n", 1, Regel::Keine, 1},
    {"const char* m = \"a*b sprengt i64\";\n", 0, Regel::Keine, 0},
    {"// 21.000.000.000 * 20 / 10.000 = 42\ni64 x = 1;\n", 0, Regel::Keine, 0},
    {"const char* p = q;\ni64* r = *p;\nchar** argv = nullptr;\n", 0, Regel::Keine, 0},
    {"inline constexpr std::size_t S = 3;\nstd::size_t t = (v * (S - 1) + w) * S;\n",
     2, Regel::Layout, 0},
    {"char c = '*';\ni64 y = 2;\n", 0, Regel::Keine, 0},
    {"i64 g = 1'000 * 2;\n", 1, Regel::Keine, 1},
    {"i64 x = /* 3 * 4 */ 5;\n", 0, Regel::Keine, 0},
    {"const i128 s = ((static_cast<i128>(n) - 1) * r + z);\n", 1, Regel::I128, 0},
    {"const i128 t = f(static_cast<i128>(a)) * b;\n", 1, Regel::Keine, 1},
    {"const i128 u = (static_cast<i128>(a) > 0 ? x : y) * b;\n", 1, Regel::Keine, 1},
    {"const i128 v = static_cast<i128>(a) - b * c;\n", 1, Regel::Keine, 1},
}};

std::size_t selbsttest_regeln()
{
    std::size_t verfehlt = 0;
    for (std::size_t i = 0; i < REGELFAELLE.size(); ++i) {
        const Regelfall& fall = REGELFAELLE[i];
        const Gelesen    g = lies(fall.text);

        Lage lage;
        sammle_namen(g.maske, lage.layout, lage.vorzeichenlos);
        lage.behauptungen = finde_behauptungen(g.maske);

        std::vector<Stelle> stellen;
        ordne_datei_ein(g, lage, 0, stellen);

        std::size_t befunde = 0;
        for (std::size_t k = 0; k < stellen.size(); ++k) {
            if (stellen[k].regel == Regel::Keine) {
                ++befunde;
            }
        }
        const Regel erste = stellen.empty() ? Regel::Keine : stellen[0].regel;

        if (stellen.size() != fall.sterne || erste != fall.erste || befunde != fall.befunde) {
            std::fprintf(stderr,
                         "  Regelfall %zu: erwartet %zu Sterne / %s / %zu Befunde,"
                         " bekommen %zu / %s / %zu\n",
                         i + 1, fall.sterne,
                         std::string(REGELNAMEN[static_cast<std::size_t>(fall.erste)]).c_str(),
                         fall.befunde, stellen.size(),
                         std::string(REGELNAMEN[static_cast<std::size_t>(erste)]).c_str(),
                         befunde);
            ++verfehlt;
        }
    }
    return verfehlt;
}

// ---------------------------------------------------------------------------
// Der Baum
// ---------------------------------------------------------------------------

bool ist_maschinerie(std::string_view name) { return !name.empty() && name.front() == '.'; }

bool ist_quelle(const fs::path& pfad)
{
    const std::string endung = pfad.extension().string();
    return endung == ".cpp" || endung == ".hpp";
}

/// Alle Quellen unter `wurzel`, absteigend. **Sortiert**, weil die Reihenfolge eines
/// Verzeichnisses nicht festgelegt ist und ein Riegel, dessen Ausgabe zwischen zwei
/// Laeufen wandert, nicht vergleichbar ist.
std::vector<fs::path> sammle_quellen(const fs::path& wurzel, std::error_code& fehler)
{
    std::vector<fs::path> gefunden;
    std::vector<fs::path> offen;
    offen.push_back(wurzel);
    while (!offen.empty()) {
        const fs::path ordner = offen.back();
        offen.pop_back();
        fs::directory_iterator it(ordner, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path    eintrag = it->path();
            const std::string name = eintrag.filename().string();
            std::error_code   art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_maschinerie(name)) {
                    offen.push_back(eintrag);
                }
            } else if (fs::is_regular_file(eintrag, art) && ist_quelle(eintrag)) {
                gefunden.push_back(eintrag);
            }
            it.increment(fehler);
            if (fehler) {
                return gefunden;
            }
        }
    }
    std::sort(gefunden.begin(), gefunden.end());
    return gefunden;
}

std::string kurzname(const fs::path& pfad, const std::string& wurzeltext)
{
    const std::string ganz = pfad.string();
    if (ganz.size() > wurzeltext.size() + 1
        && ganz.compare(0, wurzeltext.size(), wurzeltext) == 0) {
        return ganz.substr(wurzeltext.size() + 1);
    }
    return ganz;
}

bool lies_ganz(const fs::path& pfad, std::string& inhalt)
{
    std::ifstream strom(pfad, std::ios::binary);
    if (!strom) {
        return false;
    }
    std::ostringstream puffer;
    puffer << strom.rdbuf();
    inhalt = puffer.str();
    return true;
}

struct Quelle {
    std::string name;
    std::string text;
};

/// Liest einen Baum vollstaendig ein. `false` heisst: eine Datei war nicht lesbar -- ein
/// uebersprungener Text waere ein stiller Teilbestand und damit eine unwahre Zahl.
bool lies_baum(const fs::path& wurzel, const std::string& wurzeltext,
               std::vector<Quelle>& raus, std::string& klage)
{
    std::error_code             fehler;
    const std::vector<fs::path> pfade = sammle_quellen(wurzel, fehler);
    if (fehler) {
        klage = "Lesefehler unter '" + wurzel.string() + "': " + fehler.message();
        return false;
    }
    for (std::size_t i = 0; i < pfade.size(); ++i) {
        Quelle q;
        q.name = kurzname(pfade[i], wurzeltext);
        if (!lies_ganz(pfade[i], q.text)) {
            klage = "'" + pfade[i].string() + "' laesst sich nicht lesen.";
            return false;
        }
        raus.push_back(q);
    }
    return true;
}

/// Die Baeume, aus denen der Bestand kommt. Als benannte Liste und nicht verstreut in der
/// Bedingung: Wer den Kern umbaut, hat dann eine Stelle zu aendern.
constexpr std::array<std::string_view, 2> BESTANDSBAEUME = {"include", "src"};

/// Die Zeile `nr` im Urtext, ohne fuehrenden Leerraum -- fuer die Meldung eines Befunds.
/// Der Urtext und nicht die Maske: Wer nachsieht, soll finden, was dort steht.
std::string zeilentext(const std::string& text, std::size_t nr)
{
    std::size_t zl = 1;
    std::size_t i = 0;
    while (i < text.size() && zl < nr) {
        if (text[i] == '\n') {
            ++zl;
        }
        ++i;
    }
    while (i < text.size() && (text[i] == ' ' || text[i] == '\t')) {
        ++i;
    }
    std::string raus;
    while (i < text.size() && text[i] != '\n') {
        if (text[i] != '\r') {
            raus.push_back(text[i]);
        }
        ++i;
    }
    return raus;
}

/// Wie viele verschiedene Zeilen die Stellen belegen; `nur` schraenkt auf eine Regel ein,
/// `Regel::Anzahl` heisst „alle". Quadratisch, und das ist hier richtig: Es geht um
/// Dutzende Stellen, und ein Satz waere ein Behaelter mehr fuer nichts.
std::size_t zeilen_zusammen(const std::vector<Stelle>& stellen, Regel nur)
{
    std::size_t zusammen = 0;
    for (std::size_t i = 0; i < stellen.size(); ++i) {
        if (nur != Regel::Anzahl && stellen[i].regel != nur) {
            continue;
        }
        bool schon = false;
        for (std::size_t k = 0; k < i && !schon; ++k) {
            if (nur != Regel::Anzahl && stellen[k].regel != nur) {
                continue;
            }
            schon = (stellen[k].datei == stellen[i].datei && stellen[k].zeile == stellen[i].zeile);
        }
        if (!schon) {
            ++zusammen;
        }
    }
    return zusammen;
}

/// Die Zahl aus T7 `:882-888`, gegen die der Lauf sich stellt. Sie steht hier als
/// **Vergleichswert** und nicht als Erwartung: Gemessen wird bei jedem Lauf neu.
constexpr std::size_t T7_ZEILEN = 36;

}  // namespace

int main(int argc, char** argv)
{
    // Der Selbsttest laeuft vor allem anderen und braucht kein Argument. Stimmt die Lesung
    // oder die Einordnung nicht, ist jede Zahl weiter unten wertlos -- auch eine gruene.
    const std::size_t verfehlt = selbsttest_lesung() + selbsttest_regeln();
    const std::size_t faelle = LESEFAELLE.size() + REGELFAELLE.size();
    if (verfehlt > 0) {
        std::fprintf(stderr,
                     "\nmultiplikationsriegel: %zu von %zu Faellen des Selbsttests sind nicht "
                     "wie erwartet\nausgegangen. Der Bestand wurde gar nicht erst gelesen -- "
                     "ein Messgeraet, das seine\neigenen Faelle verfehlt, misst auch fremde "
                     "nicht.\n",
                     verfehlt, faelle);
        return 2;
    }
    std::fprintf(stdout,
                 "multiplikationsriegel, Selbsttest: %zu Faelle zur Lesung und %zu zu den "
                 "Regeln,\nalle wie erwartet.\n",
                 LESEFAELLE.size(), REGELFAELLE.size());

    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() != 2) {
        std::fprintf(stderr,
                     "Aufruf: multiplikationsriegel <wurzel-des-vorhabens>\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf einem "
                     "Rechner.\n");
        return 2;
    }

    std::error_code fehler;
    const fs::path  wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "multiplikationsriegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }
    const std::string wurzeltext = wurzel.string();
    const fs::path    kernwurzel = wurzel / "kern";

    std::vector<Quelle> quellen;
    std::string         klage;
    for (std::size_t i = 0; i < BESTANDSBAEUME.size(); ++i) {
        const fs::path baum = kernwurzel / std::string(BESTANDSBAEUME[i]);
        if (!fs::is_directory(baum, fehler)) {
            std::fprintf(stderr,
                         "multiplikationsriegel: '%s' ist kein Verzeichnis. Dieser Riegel "
                         "prueft den Kern\nund nichts sonst; ohne ihn hat er keinen "
                         "Gegenstand.\n",
                         baum.string().c_str());
            return 2;
        }
        if (!lies_baum(baum, wurzeltext, quellen, klage)) {
            std::fprintf(stderr, "multiplikationsriegel: %s\n", klage.c_str());
            return 2;
        }
    }
    if (quellen.empty()) {
        std::fprintf(stderr,
                     "multiplikationsriegel: keine einzige Quelle unter '%s'. Das ist kein "
                     "gruener\nLauf, sondern ein Riegel ohne Gegenstand.\n",
                     kernwurzel.string().c_str());
        return 2;
    }

    // Erst lesen, dann die Namensliste ueber den **ganzen** Bestand bauen, dann einordnen.
    // Die Reihenfolge ist der Grund, warum Regel 1 eine Konstante auch dann erkennt, wenn
    // sie in einer anderen Datei steht als ihre Verwendung.
    std::vector<Gelesen> gelesen;
    gelesen.reserve(quellen.size());
    Lage lage;
    for (std::size_t i = 0; i < quellen.size(); ++i) {
        gelesen.push_back(lies(quellen[i].text));
        if (gelesen.back().rohe_zeichenkette) {
            std::fprintf(stderr,
                         "multiplikationsriegel: rohe Zeichenkette in %s, Zeile %zu -- diese "
                         "Lesung kann\nsie nicht, und still daran vorbeizulesen waere "
                         "schlimmer als abzubrechen.\n",
                         quellen[i].name.c_str(), gelesen.back().rohe_zeile);
            return 2;
        }
        sammle_namen(gelesen.back().maske, lage.layout, lage.vorzeichenlos);
    }

    std::vector<Stelle> stellen;
    for (std::size_t i = 0; i < quellen.size(); ++i) {
        lage.behauptungen = finde_behauptungen(gelesen[i].maske);
        ordne_datei_ein(gelesen[i], lage, i, stellen);
    }

    const std::size_t zeilen = zeilen_zusammen(stellen, Regel::Anzahl);
    std::fprintf(stdout,
                 "multiplikationsriegel: %zu Dateien gelesen, %zu Namen in der Liste der "
                 "Layout-\nkonstanten, %zu in der der u64-Konstanten. Binaere `*` nach der "
                 "Lesung:\n%zu Vorkommen in %zu Zeilen.\n",
                 quellen.size(), lage.layout.size(), lage.vorzeichenlos.size(), stellen.size(),
                 zeilen);

    for (std::size_t r = 0; r < REGELN; ++r) {
        const Regel       regel = static_cast<Regel>(r);
        std::size_t       vorkommen = 0;
        for (std::size_t i = 0; i < stellen.size(); ++i) {
            if (stellen[i].regel == regel) {
                ++vorkommen;
            }
        }
        std::fprintf(stdout, "  %-58s %3zu Vorkommen in %3zu Zeilen\n",
                     std::string(REGELNAMEN[r]).c_str(), vorkommen,
                     zeilen_zusammen(stellen, regel));
    }

    if (zeilen != T7_ZEILEN) {
        std::fprintf(stdout,
                     "\nT7 `:882-888` nennt %zu Zeilen, gemessen sind es %zu. Die Abweichung "
                     "ist eine\nMeldung ueber T7 und keine ueber diesen Riegel; die Stellen "
                     "stehen unten.\n",
                     T7_ZEILEN, zeilen);
    }

    std::size_t befunde = 0;
    for (std::size_t i = 0; i < stellen.size(); ++i) {
        if (stellen[i].regel != Regel::Keine) {
            continue;
        }
        if (befunde == 0) {
            std::fprintf(stderr,
                         "\nmultiplikationsriegel: blanke Multiplikation ohne benannte Regel. "
                         "Massnahme 4.3\naus T7 verlangt `mal(a, b)` und den `__int128`-"
                         "Waechter:\n\n");
        }
        ++befunde;
        std::fprintf(stderr, "  %s:%zu\n      %s\n", quellen[stellen[i].datei].name.c_str(),
                     stellen[i].zeile,
                     zeilentext(quellen[stellen[i].datei].text, stellen[i].zeile).c_str());
    }

    if (befunde > 0) {
        std::fprintf(stderr,
                     "\n%zu Stelle(n). Wer eine davon fuer richtig haelt, aendert nicht diesen "
                     "Riegel,\nsondern den Regelsatz in T7 -- und dann faellt sie unter eine "
                     "**benannte** Regel.\n",
                     befunde);
        return 1;
    }

    std::fprintf(stdout, "\nJedes Vorkommen faellt unter eine benannte Regel.\n");
    return 0;
}
