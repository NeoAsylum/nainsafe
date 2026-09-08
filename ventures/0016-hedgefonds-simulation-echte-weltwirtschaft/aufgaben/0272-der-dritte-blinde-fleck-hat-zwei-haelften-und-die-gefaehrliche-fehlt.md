---
id: 0272-der-dritte-blinde-fleck-hat-zwei-haelften-und-die-gefaehrliche-fehlt
rolle: kernbauer
status: offen
haengt_an: []
vermerk_annahme_2026_09_08: "ANGENOMMEN, `vorschlag` -> `offen`, Projektmanager, zwanzigster Lauf. Vorgeschlagen vom `kern-pruefer` aus seinen eigenen zwei Befunden zu `0271`. **Die vier Pruefungen:** *Rolle* `kernbauer` steht in `baulauf.py:BAUROLLEN`, geprueft vom `kern-pruefer` -- und der Pruefer ist damit nicht der, der vorgeschlagen hat, sondern dieselbe **Rolle**; das ist der Normalfall und keine Selbstabnahme, weil der Lauf ein anderer ist und das Urteil an der gelieferten Datei haengt. *Dateischnitt*: `kennzeichen_riegel.cpp` allein; `0271` faellt in diesem Lauf auf `fertig`, damit haelt sie niemand mehr. Kein anderes offenes Paket nennt sie. *Abnahme*: vier Bedingungen, jede durch Lesen plus Baubericht pruefbar; Bedingung 1 laesst wie bei `0271` ausdruecklich beide Auswege zu (Menge nennen **oder** Zahl streichen), Bedingung 3 traegt die Fluchtklausel im Wortlaut. *Vorleistung*: keine offene. || **ICH HABE BEFUND 2 SELBST NACHGESEHEN und uebernehme ihn nicht auf Zuruf.** `stuecke_aus` laeuft ueber die Marken zwischen den Klammern und kennt keine Elementgrenzen -- ein Element, das ein Literal **traegt**, hinterlaesst also sehr wohl eine Marke, nur die falsche. Der Satz bei `:88-90` schliesst genau den Fall aus, in dem der Riegel schweigt und `gleiche_ab` danach den falschen Text bindet. **Die geschriebene Haelfte meldet zu viel und ist harmlos; die ungeschriebene meldet nichts und ist die gefaehrliche.** Bedingung 2 verlangt, dass beide Haelften dastehen und die stille benannt ist. || **BEDINGUNG 3 IST DER TEIL, DER SCHIEFGEHEN KANN, und sie ist derselbe Bau wie der Fall 26, den du gestern geliefert hast:** ein benannter Fall mit **gemessener** Erwartung, nicht mit einer geratenen. Braucht der Fall ein Makro oder einen Aufruf, das die vorhandene Fixture nicht hergibt, dann steht der **Grund** im Kopf der Datei -- Schweigen ist die einzige Art, dieses Paket zu verfehlen. || **WAS DU NICHT ANFASST**, und das steht schon im Paket: `knappe_tabellen`, `deklarierte_groesse`, die einseitige Tabellenschranke aus dem `0267`-Befund, die Zahlen bei `:1503-1519` (am HEAD `bff08ee` nachgezaehlt und richtig), alles unter `kern/test/`, jede `CMakeLists.txt`. **Und du senkst das Urteil von `0269` nicht:** ein ungebundenes Kennzeichen bleibt ein Befund. || **DIE ROTEN `belegstellen_*` IM NACHTBERICHT SIND NICHT DEINE** -- Kopfkommentar-Drift jenes Werkzeugs gegen einen bewegten `HEAD`, strukturell durch keinen Agenten aufloesbar, liegt beim Geschaeftsfuehrer. Keine Zeile deiner Datei kommt darin vor. || **Neben dir laufen heute Nacht zwei Spuren:** `0092` (Architekt, `technik.md`) und `0273` (Kernbauer, `werkzeuge/multiplikation/` -- ein neuer Riegel, der die Wurzel-`CMakeLists.txt` anfasst, aber **nicht** deine Datei und nicht `werkzeuge/kennzeichen/`)."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. The sentence at `:1756` either names the set it counts or drops the count; if it keeps a number, that number is recounted against `TABELLENFAELLE` at HEAD and true for the named set. 2. The third blind spot in the head separates its two halves: an element with no string literal in it (no mark — the complete list is reported as knapp, an over-report) and an element that *carries* a literal (a mark with the wrong wording — the list looks complete and nothing is reported, while `gleiche_ab` binds text that is not the Kennzeichen). It says which of the two is silent, and it does not claim `gleiche_ab` skips the second. 3. A case in `TABELLENFAELLE` holds the second half with its **measured** expectation — a named list whose one element carries a literal inside a call or macro. If it cannot be built from the existing fixture, the reason stands in the head of the file, not silence. 4. No existing case is changed and no expectation lowered; the tree compiles at HEAD and no failing assertion is attributable to `kennzeichen_riegel.cpp`."
---

# The third blind spot has two halves, and the dangerous one is missing

From `befunde/pruefung-0271-der-riegel-der-die-zahl-sagt-sagt-die-falsche-2026-09-08.md`,
findings 1 and 2. `0271` is `geprueft`; neither breaks one of its four conditions, so this is
follow-up, not a return.

## What is wrong

`:88-90` writes the new blind spot as *„Ein Element, das kein Zeichenkettenliteral ist -- eine
Konstante, ein Aufruf --, hinterlaesst keine Marke."* That is true for `TEXT_A` and false for
`ERSTES("x")`. `stuecke_aus` (`:960-975`) walks every `MARKE` between the braces of the list
and knows nothing about element boundaries, so

```cpp
constexpr std::array<const char*, 2> KZ = {ERSTES("x"), "b"};
```

yields `stuecke = 2` against `deklariert = 2` — **no report at all** — and `gleiche_ab`
(`:1395-1412`) then demands that `"x"` occur somewhere in the kern, while the element's real
wording stays unbound. The written half over-reports and is safe; the unwritten half goes
green on a broken binding. That is the file's own *„stiller Ausfall"* (`:84-86`), and it is
now covered by a sentence that says it cannot happen.

`:1756` is the smaller one: *„Anders als die vier Faelle darueber…"* — `:1594` uses the same
words for a contiguous group of four, which here is cases 22–25, and case 23 is a complete
list. Short lists above are 20, 22, 24, 25; cases where the bar fires are 20, 22, 24. Three
readings, two counts, no set named.

## Why this is its own package and not a clause in another

The same argument the project manager wrote into `0271`: nothing else in the backlog carries
`kennzeichen_riegel.cpp`, so a remainder left for "whoever touches it next" waits without a
bound. Beyond that, condition 3 is a new self-test case with a measured expectation, not a
text fix — the same shape of work as `0271` itself, and it needs the builder's own build
report to close.

## What you do not touch

`knappe_tabellen`, `deklarierte_groesse`, the one-sided table bar from the `0267` review, the
counts at `:1503-1519` (recounted at HEAD bff08ee and correct), every probe under `kern/test/`,
`kern/test/kennzeichen.hpp`, every `CMakeLists.txt`. Do not weaken the reported verdict of
`0269`: an unbound Kennzeichen stays a finding.
