---
typ: pruefung
paket: 0213-empfindlichkeitsprobe-saettigt-bei-einer-fundstelle
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Both halves verified against the sources and against today's executed ctest run (zahlwort_messung Passed on a freshly recompiled riegel), plus hand-simulation of A2 and both Teil-C mutants against the new probe code.
befunde: 0
---

# Pruefung 0213 — geprueft

## Half 1: A2 expects code 1 with five named findings

`messen.py:311-323` now expects code 1 and exactly the five wordings — four at
Groessen ("gezaehlt sind 23", Zeilennummer 2, 16, 32, 157) and one at
Deklarationen ("nennt 23, gezaehlt sind 24", Zeilennummer 32). Grep of today's
`werte.hpp` confirms these are the only Groessen/Deklarationen claim sites
(lines 6, 25, 474 carry the noun without a number claim and stay silent).

The riegel change that makes this possible: the probe compares **per
fundstelle** (`zahlwort_riegel.cpp:1133-1191`). Every kardinal sorte-3
fundstelle must count exactly +1 ("gefolgt", line 1162), and at least one must
show it in its urteil, where **red-after counts even if red-before** (line
1169). Hand-simulated on the A2 stand: line 32-D is red at 23 vs 24; the
probe's own mutant moves it to 23 vs 25, still red → gefolgt=1, gezeigt=1,
sorte-1/2 rot counts and maengel unchanged → probe passes → 5 befunde, exit 1.
Pre-0213 this saturated (`rot_nachher <= rot_vorher` over one fundstelle) and
exited 2 before the first printed finding.

## Half 2: red proof of the probe, in the same medium as Teil B

Teil C (`messen.py:446-477`) compiles two mutants of the **riegel**, exactly
like Teil B's five: C1 rebinds `SORTE_DER_PROBE` to Groessen (the sorte-3
comparison disabled) — the Groessen count does not follow the extra
declaration, probe fails "...ist der weiteren Deklaration nicht gefolgt". C2
freezes the fundstelle urteil to Gruen — gezeigt=0, probe fails "keine
Fundstelle der Sorte 3 zeigt...". Each case demands code 2 **and** the probe's
own wording in the output **and** no ripped selbsttest table, so the 2
provably comes from the probe. Both target strings occur exactly once in the
riegel (lines 1022, 1047), enforced again at runtime by `einmal_ersetzen`.

## Executed, not only read

Today's baulauf report (`befunde/uebersetzung-2026-09-07.md`) recompiled the
riegel in this run ("Building CXX ... zahlwort_riegel.cpp.o") and ran
`zahlwort_messung` **Passed** — 23/23 workspace, 3/3 standalone, 18.6–18.7 s
against 13.5 s pre-0213, matching the two extra mutant compilations (6→8). A
pass is only possible with the matched pair: the new messen.py fails on the
old riegel (A2 code, missing C targets), the old one fails on the new riegel.

## Weakening check

All pre-0213 probe guards are retained (riegel 1108–1131: nummern set,
dekl +1, maengel, sorte-1/2 rot counts). A0 still demands the probe sentence;
the clean-tree Gegenprobe (code 0) stays. A2's change 2→1 is a strengthening
(five pinned wordings) and is the abnahme itself.

## What I looked for and did not find

A way to pass the probe with the sorte-3 comparison disabled (C1/C2 cover
both halves; only `deklarationen` moves +1 under the mutant, so "gefolgt" pins
the binding — the wiring itself is pinned by M5); a format/order mismatch
between the riegel's stderr befunde and messen.py's line filter; a stray noun
in either inserted mutant comment that would add a fundstelle.

## Outside the package

`befunde/messung-0180/lauf.txt` records the pre-0194 state ("zwei Nomen", A2
with 4 findings) and today contradicts exactly the case 0213 changed. Not in
0213's `dateien`, so no finding against it — proposal written as
`aufgaben/0214-lauf-txt-traegt-den-stand-vor-0194.md`.
