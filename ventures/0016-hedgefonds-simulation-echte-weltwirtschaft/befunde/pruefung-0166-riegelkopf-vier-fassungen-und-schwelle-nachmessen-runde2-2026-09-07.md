---
typ: pruefung
paket: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Green proof read in today's report on both build paths and quoted here; the exit-0-implies-all-parts chain re-verified in source, including the per-invocation red proof (Teil 3) and the needle pre-check.
befunde: 0
---

# Pruefung 0166, Runde 2 — the missing half of the red proof is now in the report

Round 1 (`pruefung-0166-...-2026-09-07.md`) found exactly one defect: green-at-new was
not in the report, and the table's middle column was stale because the corpus had
drifted under it (translation wave, dead citations). 0222 repaired the citations. This
round verifies the green proof and that nothing was weakened to get it.

## The green proof, quoted on sight (the report file mutates daily)

`befunde/uebersetzung-2026-09-07.md`, `ergebnis: ok`, as it stands now:

- Root build: `19/24 Test #19: belegstellen_wortabstand .........   Passed   17.17 sec`,
  within `100% tests passed, 0 tests failed out of 24`.
- Second path (`werkzeuge/belegstellen/bau`): `3/3 Test #3: belegstellen_wortabstand
  .........   Passed   17.34 sec`, within `0 tests failed out of 3`.

The builder's vermerk quotes 17.22/17.23 s — the report has been regenerated since
their run (test 17 now 1.03 s, was 1.02). Both wordings are green; runtime is named in
the vermerk as the abnahme demands, and 17 s against `TIMEOUT 240` (CMakeLists.txt:155,
< 900) is proportionate either way. The overwrite-per-run property is already flagged
to the PM (pruefung-0214); not a defect of this package.

## Why Passed proves the whole abnahme — verified in source, not adopted

`CMakeLists.txt` carries no `PASS_REGULAR_EXPRESSION`, `SKIP_RETURN_CODE`, `WILL_FAIL`
or `DISABLED` (grep over the file: zero hits), so Passed ⇔ exit 0. Exit 0 is only
reachable if every part held, because in `messung-0166/messen.py`:

- The comparison reads the **delivered** comment, no constants: `quelldatei.read_text`
  (:512) → `vergleiche_kommentar(nachher_text, unterschiede)` (:621); exact tuple
  equality (:151). The only numeric constants are the self-probe's `PROBE_*` (:349).
- **Teil 3 runs the red proof on every invocation**: the same comparison against the
  pre-0166 head rebuilt by back-substitution; finding nothing there counts a befund →
  exit 1 (:640-643). `BLOCK1/2_VORHER` carry the genuine historical head (base numbers
  33/33/58…34/34/58 of 2026-09-05, matching the package body's "Kopf sagt" column) —
  not a strawman.
- Bedingung 2 (same three numbers vorher/nachher, one call, one tree) is Teil 1
  (:559-563); Teil 4 re-derives the four threshold statements from measured values,
  not from the head (:650-665). Any failure → exit 1.
- Every needle is pre-checked before the first compile; a blunt needle → `Messfehler`
  → exit 2, never silent green (:531-548). Exit 0 therefore also proves 0222's edit at
  `belegstellen_riegel.cpp:39` did not blunt the back-substitution blocks.
- The self-probe must reject a wrong number and a missing line, and tests
  `einmal_ersetzen` on fehlt/zweimal/genau-einmal (:365-444). The evaluator can say no.

## Wird-es-rot — proven by history, not simulation

This exact test stood at `Messstand 0166: 5 Abweichung(en)` in round 1, on both paths,
purely from corpus drift. It went green only after 0222's citation repair, with zero
edits to the three package files: none of the three `dateien` is modified in today's
working tree, and the delivered head still carries the identical difference table
(`belegstellen_riegel.cpp:533-538`, rows (-1,-1,·)). No threshold moved, no assertion
removed, no number rewritten.

## What I searched for and did not find

Weakened comparisons (exact equality intact), raised TIMEOUT (still 240), ctest
result-shaping (none), a fabricated "vorher" (matches the recorded 2026-09-05 head),
edits to the six numbers between the zurueck and today (none).
