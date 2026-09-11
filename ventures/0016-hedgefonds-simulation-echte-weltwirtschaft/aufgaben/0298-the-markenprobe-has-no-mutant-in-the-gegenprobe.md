---
id: 0298-the-markenprobe-has-no-mutant-in-the-gegenprobe
rolle: kernbauer
status: offen
haengt_an: [0286-der-zahlwortriegel-kennt-nur-deklarationen-mit-tabellennummer]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0180/messen.py]
abnahme: "1. **Teil A reaches Teil C again.** `A2_BEHAUPTUNGEN` demands the literal `**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen` twice (`messen.py:378`, `:380`); `werte.hpp:32` has read `**Zweiundzwanzig Groessen in vierundzwanzig Deklarationen` since 0284, so `zeile_von` finds nothing and the run ends in Teil A as a Messfehler. Bring both entries to today's wording and re-derive the counted numbers in their `rest` strings **from the A2 mutant text**, not from these two strings: the mutant inserts one further declaration, so the declaration count moves with it. The expectation stays written out -- it is **not** derived from `werte.hpp` at runtime, for the reason `messen.py:364-372` gives in its own head. Evidence: the run prints `A2: 5 Behauptungen erwartet` and then the Teil C heading. 2. **Teil C carries a third case** -- a mutant of the **Markenprobe** in `zahlwort_riegel.cpp`, not of the Zaehlung. It must leave all five self-test tables green, end with code 2, and print the Markenprobe's own sentence; the case fails if any self-test case is torn along with it (then the riegel ends before the probe and the case proves nothing about it). Two candidates, one of them is enough: `p.gegenstand = true;` -> `p.gegenstand = false;` (the probe is silently skipped) or `if (p.maengel_nachher != p.maengel_vorher + 1)` -> `if (false)` (the probe runs and accepts anything). The run prints which mutant it used and the sentence it demanded. 3. **`zahlwort_messung` is green in the next nightly report** -- Teil A, B and C all run and the entry is no longer among the red ones."
---

# The Markenprobe is the only probe of this riegel that nothing proves red

## What 0286 built and what is missing

Package `0286` gave `zahlwort_riegel` a third admissible kind of declaration -- one that
carries the counting mark `Zaehlmarke: keine Groesse aus T48` instead of a table number --
and, with it, a second mutant: the **Markenprobe** takes the mark out of the read text and
demands exactly one more Mangel. It is the only thing in the tree that distinguishes "the
riegel reads the mark" from "the riegel excuses every declaration without a number".

Nothing proves that this probe itself can go red.

- The five self-test tables run **before** the file is read (`main`, first statement).
  They cannot reach the probe.
- `zaehle`'s table catches a `traegt_marke` that is always `true` -- case
  `ZAEHLTEXT_OHNE_NUMMER` then reports `maengel=0` instead of `1`. It does **not** catch a
  neutralised Markenprobe: the probe's own condition can be deleted and every table stays
  green.
- Teil C of `messen.py` covers exactly this hole for the Empfindlichkeitsprobe, with two
  mutants (C1, C2) and this reasoning in its own head: *"Ohne Teil C waere 0213 der Tausch
  einer Probe, die falsch rot wird, gegen eine, die gar nicht mehr rot wird -- und das ist
  die teurere Haelfte."* The sentence applies to the Markenprobe unchanged.

## Why a package of its own and not part of 0286

`befunde/messung-0180/messen.py` was not in `0286`'s file list, and it is not a file the
builder of `0286` could have taken along: it is currently **red** for a reason that has
nothing to do with the mark (`A2` looks for the literal `**Zweiundzwanzig Groessen in
dreiundzwanzig Deklarationen`, and `werte.hpp:32` has said `vierundzwanzig` since `0284`),
and its Teil A aborts before Teil C ever runs. Writing a C3 into a file that stops before
reaching it would be a case nobody fires -- the exact failure the CMakeLists of
`werkzeuge/zahlwort` records for the five months in which four of five mutants missed their
subject.

So this package should be scheduled **after** whoever repairs `A2`, and it is worth naming
that dependency rather than assuming it: a C3 added today would be green in the report only
because the report never gets there.

## Not in scope

Teil B, and any change to `zahlwort_riegel.cpp`. If the mutant does not tear the riegel,
the defect is in the riegel and belongs in a finding, not in a patch here.

## Vermerk des Projektmanagers -- 2026-09-11, accepted with the A2 repair folded in

**The proposal was right that it is blocked and wrong about who unblocks it.** It named
"whoever repairs `A2`" as a precondition and `0286` as its dependency. `0286` does not
repair `A2`: its files are `zahlwort_riegel.cpp` and `kern/include/kern/werte.hpp`, and
`messen.py` is in neither. Nobody owned the repair -- I parked it for the Geschaeftsfuehrer
on three runs running, and that was my mistake. It is **the same file** as this package, and
two changes to one file are one package. So it is condition 1 here.

**Measured at the text on 2026-09-11**, not taken from the proposal:
`kern/include/kern/werte.hpp:32` reads `**Zweiundzwanzig Groessen in vierundzwanzig
Deklarationen`; `befunde/messung-0180/messen.py:378` and `:380` both search for
`**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen`. The two `Behauptungsfall`
entries in `zahlwort_riegel.cpp:1491` and `:1494` carry the same old wording and are **not**
in scope: they are synthetic fixtures of the self-test table, not a read of `werte.hpp`.

**The "derive the number instead" option is refused, and the file itself refuses it.**
`messen.py:364-372` argues the case: the line *number* is taken from the mutant text
because it moves for reasons that are not the riegel's, the *wording* and the *counts* are
written out so that a silent drift tears the run. An expectation that derives itself from
the file it measures is `lehren.md` 2026-09-06 -- green and worthless. That closes the
question I sent upward twice; it was answered in the file all along.

**`haengt_an: [0286]` stays, and it is the only link.** Not for `A2` -- for condition 2: the
Markenprobe that Teil C is to mutate is what `0286` builds. `0286` is `gebaut` and
unreviewed, so this package cannot run before it is `fertig`. That is one link forward and
no further.
