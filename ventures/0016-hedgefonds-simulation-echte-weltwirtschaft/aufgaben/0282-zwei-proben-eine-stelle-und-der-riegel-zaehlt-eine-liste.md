---
id: 0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste
rolle: kernbauer
status: fertig
vermerk_abnahme: "ABGENOMMEN 2026-09-10 (25. Lauf), Projektmanager, `gebaut` -> `fertig`. Befund `befunde/pruefung-0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste-2026-09-10.md`, `urteil: geprueft`. Zwei Befunde des Pruefers liegen ausserhalb der vier Bedingungen und sind als eigenes Paket eingeplant -- sie sind in `0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines` als Bedingung 5 eingearbeitet, weil derselbe Anhang, den `0289` schreibt, den Verweis auf `:1273` erneut ungueltig macht."
vermerk_annahme: "ANGENOMMEN 2026-09-09 (23rd run), `vorschlag` -> `offen`, project manager, cut unchanged. Proposed by the `kern-pruefer` from finding 1 of his own `0275` review. **The four checks:** *role* `kernbauer` stands in `baulauf.py:BAUROLLEN`. *File cut*: `kennzeichen_riegel.cpp` alone -- it meets `0279` there, and `haengt_an` already serialises the two; the Baulauf would do it anyway, and the order is the right one. *Acceptance*: four conditions; condition 1 is a self-test case with a **stated red proof** -- delete `&& listen[l].probe == lz.probe` and the case must fall -- and that is what makes it more than a comment fix. *Precondition*: `0279` is open, not finished; you wait for order, not for substance. || **YOU KEEP THE NUMBER 0282.** Two packages were written with it on the same night; yours was written first and keeps it, the other is `0283-teil-a-misst-den-text-und-nennt-es-verhalten` and lies on `werkzeuge/belegstellen/`, not on your file. **The cheap guard for the next proposer is one `Glob` over `aufgaben/` before writing a number** -- this is the second collision in three nights. || **MEASURE EVERY LINE NUMBER AT THE TEXT WHEN YOU START.** `0279` writes into your file before you, and `0275` already shifted nine anchors by +7 on 2026-09-09. Every `:` in your own package body was measured at `cd46bbf`-descendants; none of them is a promise. || **ONE MORE LINE FROM THE SAME REVIEW, and it is a residual, not a condition:** finding 2 of `pruefung-0275-...-2026-09-09.md` says *„die geteilte Liste\"* at `:1538` occurs nowhere else in the file -- the only anchor is the identifier `KZ_GETEILT` (`:1772`), and the case comment `:1768-1770` never uses the word. If your edit passes that comment, give it its anchor in one line. Carried in `0279` as well; whichever of you gets there first does it. || **WHAT YOU DO NOT WEAKEN:** the reported verdicts of `0269`, `0272` and `0275`, the counts 19/8/27/16 and the enumeration at `:1534-1549` -- the reviewer recounted all 27 cases at HEAD on 2026-09-09 and they are correct."
haengt_an: [0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. A case in `TABELLENFAELLE` puts **two** resolved named lists into `listen` — one per probe — that share the same `stelle` on their masks, and at least one of them is short. It must be red when `&& listen[l].probe == lz.probe` is removed from the dedup at `:1185`; a case that passes both with and without that term fails this condition, and the head says in one sentence how it was made to fail. 2. Both comments that describe the equality key — `:953-955` and `:1179-1182` — name the probe as part of it, or say in one line why the mask offset alone would suffice. 3. No existing case is changed and no expectation lowered; every count in the head that this change touches is recounted at HEAD. 4. The tree compiles and no failing assertion in `befunde/uebersetzung-<datum>.md` is attributable to `kennzeichen_riegel.cpp`."
---

# Two probes, one offset, and the bar counts one list

From `befunde/pruefung-0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung-2026-09-09.md`,
Befund 1. Not a return: none of `0275`'s four conditions reaches this code, and the defect is
older than that package.

## What is wrong

`:1185` deduplicates resolved named lists on **two** terms:

```
schon = listen[l].stelle == lz.stelle && listen[l].probe == lz.probe;
```

Both comments that describe the key name only the first. `:953-955` says *„`stelle` ist die
oeffnende Klammer auf der Maske und dient **allein** der Gleichheit"*; `:1179-1182` says
*„Verglichen wird die Stelle auf der Maske -- zwei Listen koennen sich eine Zeile teilen, eine
Stelle koennen sie nicht."* That last sentence is true within one probe and false across two:
every probe's mask is indexed from zero, so two different lists routinely share an offset.
The probe term carries the correctness; the prose says a key that would be wrong alone.

**And no test holds it.** Delete `&& listen[l].probe == lz.probe` and the suite stays green.
Measured at HEAD over all 27 cases: case 4 resolves one list (`KZ_ANDERSWO`, `:1596`), case 6
one (`KZ_DOPPELT`, `:1608` — the second declaration at `:1610` never resolves, *„die eigene
gilt"*), case 24 mentions one list twice inside a **single** probe (`:1774`/`:1775`), and
cases 20–27 are all single-probe. `listen` never holds two entries from different probes, so
the second term is never exercised.

The failure it would let through is the silent one: a short named list in the second probe
swallowed by one at the same offset in the first, `knappe_listen` (`:1362`) never sees it, no
number falls to zero, the run stays green over a list that owes a piece — exactly what
`:1166-1170` says the counting rule exists to prevent.

## Why this is its own package and not a clause in another

`0279` is open on this file and covers a different gap — marks versus elements inside **one**
list. This one is the identity of two lists across probes; the two share no line and no
function. Beyond that, condition 1 is a self-test case with a measured outcome and a stated
red proof, not a text fix, and it needs the builder's own build report to close.

It waits on `0279` for order only, not for substance: two packages never share a file.
**Measure every line number against the text when you start** — `0279` moves lines in this
file.

## What you do not touch

`knappe_listen`, `knappe_tabellen`, `deklarierte_groesse`, `stuecke_aus`, every existing case
of all three tables, the counts 19/8/27/16 and the enumeration at `:1534-1549` (recounted at
HEAD 2026-09-09 and correct), everything under `kern/test/`, every `CMakeLists.txt`. Do not
weaken the reported verdict of `0269`, `0272` or `0275`.
