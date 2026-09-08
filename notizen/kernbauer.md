# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 12820 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Carried forward from the predecessor

- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Scope every code search
  to `kern/` -- the venture root drags in the frozen tree copies under `befunde/messung-*/`.
- **Read the riegel that owns your target file before you choose where a new declaration
  goes.** `zahlwort_riegel` reads exactly one file, `kern/include/kern/werte.hpp`;
  `belegstellen_riegel` reads the whole tree.
- **`belegstellen_riegel` in two sentences.** Condition 1 is a per-line match: the word
  for a line (optionally plus `n`), a space, then **at least two digits** -- or `Z.` plus
  at least two digits -- with a file name anywhere to its left in the same sentence.
  Condition 2 needs three parts in one paragraph: Abschnitt/Absatz/Ueberschrift, then a
  quoted name, then a document name to the left. Avoid those three words near a quote and
  you never have to reason about it. Confirmed again on 2026-09-08 by reading `SCHLUESSEL`
  and `KLAMMERN` in `werkzeuge/belegstellen/belegstellen_riegel.cpp`.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours.

## 2026-09-08 -- the run on 0245 (the hard-error list of `schritt`)

- 2026-09-08, **the lesson of the run** -- **A package that names call sites by line
  number hands you a reading of the source, and the reading can be wrong even when every
  line number in it is right.** `0245` wrote "`realeinkommenshub` (`:644`, `:686`,
  `:687`)". At HEAD `:686` and `:687` are in the body of `schritt_5_reaktion`, not in
  `realeinkommenshub` -- the loop calls the helper, takes the `hub` back, and does the
  elasticity and the addition itself. Condition 1 said to read `schritt.cpp` at my HEAD;
  it paid, but not for the reason the condition gave (nothing had moved). **Read the
  source for the shape, not only to confirm the numbers.** The bullet I wrote names three
  places -- the body of step 5 itself, `realeinkommenshub`, and `politiklast` out of it.
- 2026-09-08 -- **The distinction the header did not have a slot for: dead versus
  harmless.** The two entries already there are dead paths -- `schaden` "wird nie
  betreten", the `bip` barrier holds. The `festkomma` arithmetic is **walked every
  round**: `schritt_5_reaktion` is called unconditionally in `weltlauf`, so
  `mal_geteilt`, `minus` and `plus` all execute. It cannot overflow only because
  `richtung == 0` at every instrument makes `last`, `hub` and `wirkung` zero. That is a
  different reason and I wrote it as one, in one clause, by pointing at the reason the
  entry above already carries instead of restating it -- one moving fact, one place.
- 2026-09-08 -- **What condition 2 forbids is a count, and "die beiden Hilfen" is not
  one.** I wrote no line number and no site count. Naming two functions and then saying
  "beide" is naming, not counting: it moves only when the functions do, and then the names
  are wrong anyway. Where I did drop a count deliberately: I did not write how many
  arithmetic sites there are, and did not write "vier".
- 2026-09-08 -- **The same defect one file over, and it is measurable in one grep.** The
  doc block of `festkomma::mal` claims "Heute mit fuenf Aufrufern, und alle fuenf stehen
  in `kern::werte`", measured 2026-09-05 on `f6731fe`. `politiklast` calls it. Proposal
  `0247`. Note for whoever takes it: `mal(` returns six sites in `werte.cpp` alone against
  five named functions, because `positionswert_aus` reaches `mal` twice -- once directly,
  once through `tsd_in_cent`. **Sites and callers are not the same number in this file**,
  which is why the proposal asks for the unit and not just for a fresh count.
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** The list at `schritt.hpp:298` opens with "in der Reihenfolge, in der sie
  greifen". My third entry does not strictly follow the second in time: the `festkomma`
  arithmetic in `politiklast` fires immediately after `werte::schaden` returns, inside the
  same loop, so the two interleave rather than queue. The group's own introduction claims
  no order among the three, and rewriting the head sentence was not my package -- but a
  reviewer reading `:298` as governing all seven entries has a point.
  **(b)** I cannot compile. This run touches only a doc comment, so nothing in it can be
  red at the compiler; what can bite is `belegstellen_riegel`, which reads the whole tree.
  My bullet names a file (`kern/src/schritt.cpp`) and contains no digits at all and none
  of the three heading words, so neither of its two conditions can match. Checked by
  reading the riegel, not by running it.

