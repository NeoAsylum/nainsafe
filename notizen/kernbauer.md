# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 13570 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- the run on 0249 (the head names a barrier that can no longer fire)

- 2026-09-08, **the lesson of the run** -- **"This entry is dead" is almost never true of
  the whole entry; find the clause that died.** The package (and the finding behind it)
  said the third bullet of the hard-error list names a dead barrier: since `0240`,
  `festkomma::plus` in step 5 cannot abort. True of the *addition* and of nothing else.
  The body of step 5 still reaches `kern::festkomma` through the elasticity line, and
  `realeinkommenshub` through `minus(0, last)` and `mal_geteilt`. So the repair was **a
  split, not a replacement**: `Drei weitere` became `Vier weitere`, the located barrier
  out of `kern::schritt` got its own entry, and the old one kept everything but the
  addition. Had I taken the package's wording as the whole finding, I would have deleted
  three live paths.
- 2026-09-08 -- **What went stale five times was one line, and it was not an entry.** The
  group head assigned places to entries by ordinal -- `die ersten beiden fuehren aus
  kern::werte heraus, der dritte aus kern::festkomma`. That breaks on *insertion* as well
  as on *movement*, and both happened. The structural fix is one moving fact, one place:
  each entry carries its own place, no group line. It also killed the `Anders als die
  beiden Eintraege davor` contrast (condition 3) without a separate repair -- **a
  cross-entry contrast is the same defect in another grammar.**
- 2026-09-08 -- **Answer a "where is this actually checked" condition by pointing, never
  by summarising.** Condition 5 offered the `Riegel` ledger of `schritt_probe.cpp`. I
  named it and said **nothing** about which entries it holds: `0248` was editing that file
  in the parallel lane, so any sentence about its contents would have been stale on
  landing. Pointing is order-independent; summarising is not. General form: **when two
  packages share a subject but not a file, the one that does not own the file may only
  point at it.**
- 2026-09-08 -- **`werte::bip` aborts twice on one quantity, and the header knew one.**
  The value-added sum leaves `i64` inside `bip` itself (`kern/src/werte.cpp`, the ceiling
  since `0242`); only after that does `realeinkommenshub` test `bip(l) > 0`. Entry 1 was
  worded to the second alone while entry 2 was a catch-all over its function. **Check
  whether neighbouring entries are written at the same width before you trust either.**
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** I deleted one clause the conditions did not name -- the old entry 1 closed with
  `die Aussage ueber die eine bewegte Groesse weiter oben ist genau so falsch geworden`.
  It is true, but the new closing paragraph makes the same argument with `0240` as the
  instance, so it went as repetition. Recorded in the package's Vermerk; a reviewer may
  fault it as an edit beside the package.
  **(b)** I cannot compile, and this run touches only a doc comment, so nothing in it can
  be red at the compiler. What could bite is `belegstellen_riegel`, which reads the whole
  tree: my text has no line word before digits (`Paket 0240`, `T7` only) and none of
  Abschnitt/Absatz/Ueberschrift near the quoted `spiel.md`. Checked by reading the riegel,
  not by running it.

## Carried forward from the predecessor

- **`belegstellen_riegel` in two sentences.** Condition 1 is a per-line match: the word
  for a line (optionally plus `n`), a space, then **at least two digits** -- or `Z.` plus
  at least two digits -- with a file name anywhere to its left in the same sentence.
  Condition 2 needs three parts in one paragraph: Abschnitt/Absatz/Ueberschrift, then a
  quoted name, then a document name to the left. Avoid those three words near a quote and
  you never have to reason about it.
- **Which riegel reads what.** `zahlwort_riegel` reads exactly one file,
  `kern/include/kern/werte.hpp`; `belegstellen_riegel` reads the whole tree. Of the five
  `belegstellen_*` ctest entries **only `belegstellen_riegel` reads your files**, the
  other four are self-tests of that tool. Read the riegel that owns your target file
  before you choose where a new declaration goes.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours. And **grep the completeness half of the `Riegel` ledger
  before you add an abort you cannot trigger** -- it demands a message per entry each run,
  so an unreachable barrier registered there turns a healthy build red.
- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Scope every code search
  to `kern/` -- the venture root drags in the frozen tree copies under `befunde/messung-*/`.
- **Changing an abort message without changing the abort set:** test the precondition on
  `i128`, then let `festkomma` do the arithmetic anyway; doing it yourself with
  `__builtin_add_overflow` is shorter and breaks T6.
