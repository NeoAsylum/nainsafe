---
typ: pruefung
paket: 0257-die-dritte-fassung-der-kennzeichenpruefung-steht-in-festkomma-probe
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "Both Ruecklauf findings verified fixed against the fresh runner report (bezeichner_riegel green, belegstellen 41/41 resolved); structure and counts from the first pruefung reconfirmed at HEAD."
befunde: 0
---

# Pruefung 0257, Ruecklauf 1: geprueft

Second review after my `zurueck` of 2026-09-08 (`pruefung-0257-…-2026-09-08.md`). The
PM's Ruecklauf ordered exactly two comment fixes in `kern/test/festkomma_probe.cpp` and
forbade rebuilding the rest. Both are fixed; the rest is unchanged.

## Finding 1 (dangling `ABBRUCH_MELDET` at :136) — fixed

`Grep ABBRUCH_MELDET` over the file returns one line: `:501`, inside the
`!ABBRUCH_MELDET(...)` history comment the riegel had never flagged. The former `:136`
passage now reads „sieben eines probeneigenen Makros" (today `:135-136`) — the macro is
described, not named. `bezeichner_riegel` is green twice in
`uebersetzung-2026-09-08.md`: root lane test 22/27 (`:147`, Passed) and the standalone
tool lane (`:416`, Passed). Leaving `:501` follows the PM's instruction word for word
(„leave whichever the riegel does not name").

## Finding 2 (unresolvable citation at :259) — fixed

The parenthesis *(„Absatz \"Ueberlauf\" ueber `wurzel`")* is gone; the comment (today
`:257-264`) states the unreachability argument inline instead of citing a heading. The
PM allowed „cite a heading that is actually there, **or drop the parenthesis**".
Belegstellen A-phase now measures **41 Zitate, 41 aufgeloest** before and after
(`uebersetzung-2026-09-08.md:116-117`) — tonight's earlier 42/41 with one unresolved is
gone, and every remaining citation resolves.

## Acceptance criterion as a whole, reconfirmed at HEAD

- Structure intact and untouched by the fix: `ALLE_RIEGEL` `:189`, `RIEGEL_OHNE_ZUSTAND`
  `:285-292` with its `warum` (three call sites, all in `wurzel`, intermediate below
  2^95), forget-nets `:296` and `:336`, `Buch` instantiation `:340`, printed line „vor
  Paket 0257 stand hier keine" `:375`. 17 `BRICHT_AB_MIT` calls recounted by grep —
  same number as the first pruefung, so no assertion was lost in the fix.
- No compile error, no failing assertion attributable to `festkomma_probe.cpp`: kern
  lane 13/13 green including `festkomma_probe` (report `:212`), root build compiles and
  links it (`:44`, `:59-60`).
- The two remaining red tests — `belegstellen_wortabstand` (19) and
  `belegstellen_kopfzahlen` (21) — name only the tool's own head comment against its
  measurement: Messstand 0166 (`:106`), „Bezugsstand im Kommentar: 2f2f79f; HEAD zu
  Beginn: 6f2ec03" (`:115`, `:142`), NAMENSFAELLE head naming the wrong case (`:139`).
  No failure line names `festkomma_probe.cpp`. This is exactly the moved-HEAD drift the
  PM pre-adjudicated as not this package's Ruecklauf; the Grundzahl (41, 41, 54) vs the
  head's (41, 41, 53) stays uncharged here as in the first pruefung.

## What I looked for and did not find

A third comment carrying the dead macro name (grep: only `:501`), a citation-shaped
parenthesis left elsewhere (grep `Absatz|Ueberlauf`: only prose, no citation form), a
changed assertion count hiding behind the comment fix (17 = 17), and a
`festkomma_probe` line inside either belegstellen failure block (none).
