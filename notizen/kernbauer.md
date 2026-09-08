# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 15364 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-9.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0278 (the three head numbers measure themselves)

Three files. `belegstellen_riegel.cpp`: the three corpus numbers are out of the head
comment, replaced by three *relations* between two runs; what stays absolute is marked
`Momentaufnahme vom 2026-09-08, vom Messstand nicht geprueft`. `messen.py`: `BEZUGSSTAND`
and its check gone (the last commit id the check held against), `teil_b1`/`teil_b2` split
into measure-once / judge-twice, four Rotnachweise instead of three. `CMakeLists.txt`:
the block description and the timeout derivation. **Compilations 8 -> 5** (16.26 s
measured on 2026-09-08 -> ~10 s expected); TIMEOUT 300 deliberately not lowered.

- 2026-09-08, **the lesson of the run** -- **When a transcript keeps ageing, the fix is
  not a better transcript but a claim with two measured sides.** Six finished packages
  (0115, 0166, 0189, 0227, 0232, 0233) wrote „41 Zitate, 41 aufgeloest, 53 uebergangen"
  into that head; every one was right on its day and wrong the next, because the latch
  counts a corpus containing its own source. The move that works was already in the same
  file, twenty lines higher: package 0166's table of six Fassungen states **differences to
  the unchanged version**, never base numbers, and it has not aged since. General form:
  **a document may state what two runs differ by; it may not state what one run counts.**
  The first has both sides inside the measuring call, the second borrows one side from a
  commit.
- 2026-09-08 -- **The trap the package named is real, and the way out is that the
  Gegenprobe must falsify the *code*, not the sentence.** Once the head carries no number,
  `verstellen()` -- bump the digit in the text and require red -- has nothing to bite; a
  deleted sentence only proves `gelesen()` searches for it. So two of the four proofs now
  swap an **input**: Angabe 1 runs with the shipped latch replaced by the mutant (both
  sides collapse, the „werden mehr" relation breaks), Angabe 2 runs with
  `ohne-marken-rein` in place of the mutant that moves nothing (the claimed equality
  breaks). Cost: zero extra compilations, because both re-judge measurements already
  taken. **A relation-based check needs relation-based counter-proofs; keep text-verstellen
  only where the text really carries a number** -- here the two claims about this file
  itself (Fall 6 in `ABSTANDSFAELLE`, the seventh Herkunftshinweis), which age only when
  someone edits the file, and then red is the right answer.
- 2026-09-08 -- **Not every number in a head is the same kind of number, and the sort
  order is „what makes it stale".** Corpus counts go stale with *any* foreign commit ->
  out. Counts about this file (case numbers, table names, exit code 2, the wording of a
  self-test message) go stale only when someone edits this file -> they stay checked. I
  split on that line rather than on „absolute vs. relative", and it is the line the
  package's condition 1 actually draws.
- 2026-09-08 -- **Verified before writing, and it was the real risk of the run:** Teil A
  runs the pinned old source and today's source over the same tree and requires the same
  three numbers -- so **my own edit to the head comment could redden it**. The latch only
  counts a Fundstelle at one of four keywords (`Abschnit\164`, `Ueberschrif\164`,
  `\303\234berschrif\164`, `Absa\164z`, `:1544`). Every occurrence in this file sits in
  `:21-345`; my edited ranges (`:558-590`, `:616-623`, `:1593-1620`) contain none, and I
  added no document name that was not already there. **Before editing a file that a latch
  counts itself over, work out the latch's trigger and check your diff against it -- not
  the diff's size.**
- 2026-09-08 -- **Relation 1 of Angabe 1 is written so a foreign red cannot break it.**
  The obvious form -- „extra quotes == places reported", `zahlen[0] - grund[0] ==
  stellen` -- is false the day some foreign document carries a broken quote, because
  `stellen` then counts that one too and the equality shifts by it. Written instead as
  `stellen == zahlen[0] - zahlen[1]` (both from the *same* run) plus `zahlen[1] ==
  grund[1]`, it says the same thing and survives. **When you turn a transcript into a
  relation, check which side of it a stranger can move.**
- 2026-09-08, **what I am unsure about, for the project manager:** four things.
  **(a)** I cannot compile or run. The riskiest edits are in `messen.py`, in this order:
  the three `gelesen()` patterns, which must match my new head wording after `flach()`
  collapses `//!` and newlines -- if one misses, the run is red with „Im Quelltext steht
  keine Aussage der Form"; then `gegenprobe()`, rewritten from a `zip` over three tuples
  into four explicit Nachweise with a closure (`lambda t=verstellt, p=pruefung`); then
  `messe_ohne_marken`'s `% ((code,) + zahlen + (...))`, seven placeholders against seven
  values.
  **(b) Predicted values, so a divergence is visible instead of arguable.** With the
  numbers of the 2026-09-08 report (grund 50/50/45, `ohne-marken-rein` 61/50/59, 11
  Stellen, `rechts-ohne-satzgrenze-rein` 50/50/45): all four checks green, and the four
  Rotnachweise report 1, 1, 1, 1 Meldung each. If the run prints anything else, distrust
  this line, not the run.
  **(c) `VORFASSUNGSSTAND` stays on `dbcd637` and I could not move it** -- no role has a
  shell, so I cannot read HEAD. Until today it was dragged forward with every correction;
  there are no more corrections, so I froze it explicitly and rewrote section C to say
  what a red Teil A now means (a commit in between moved the latch's *behaviour*). **It is
  the last commit anchor in the stand.** If it ever reddens for a foreign reason, the
  honest fix is to retire Teil A, not to re-pin it -- but that is a package, not a
  side-edit.
  **(d)** Condition 3 asks that a red run name „every divergent number with file and
  line". My messages name the numbers and which side of the comparison they came from,
  not file:line -- a measured corpus count has no line. Green is expected; if it is red,
  that wording is where a reviewer will bite.
- 2026-09-08, **a lead I did not act on:** `multiplikationsriegel` is red at HEAD with
  exactly the two true positives my `0273` run predicted (`festkomma.hpp:99` and `:356`,
  `uebersetzung-2026-09-08.md:137-140`), and the per-rule split printed there --
  31/0/6/2/1 plus 2 findings -- matches my hand count in that file's head to the
  occurrence. The head is not to be distrusted. That is package `0274`, not mine.
