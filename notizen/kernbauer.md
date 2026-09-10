# Logbuch: kernbauer

Rotated by the runner on 2026-09-10 at 13919 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 -- 0282 (two probes, one offset)

One file, `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`. Case 29 of `TABELLENFAELLE`
(`:1979`), `std::array<Tabellenfall, 28>` -> `29` (`:1678`), three key comments rewritten
(`:289-299` file head, `:988-993` `struct Listenzahl`, `:1265-1275` the dedup itself),
enumeration recounted 19/9/28 -> 19/10/29, six ones (20, 22, 24, 26, 28, 29), four zeros.
The dedup code at `:1278` is untouched -- the defect was that no case held it.

- 2026-09-10, **the lesson of the run** -- **A test for a two-term key needs the two terms
  to disagree *and* the right one to be second.** `listen` is deduped on
  `stelle && probe`; if the short list is pushed *first*, dropping the probe term swallows
  the complete one instead, `listen_knapp` is 1 either way, and the case is green before
  and after -- the exact worthlessness `lehren.md` 2026-09-06 warns about. The full list
  stands first in the case on purpose, and that sentence is in the case comment because it
  is not readable off the input text.
- 2026-09-10 -- **How to force two probes onto one mask offset, cheaply.** `stelle` is
  `fund.auf`, an index into that probe's own `maske`; `zerlege` copies ordinary characters
  1:1 and collapses each string literal to one char. So two declaration lines equal in
  length up to the `{`, with no literal before it, land on the same index. `KZ_HIER` and
  `KZ_DORT` are both seven characters -> both at 47 (hand-counted). No fixture, no
  arithmetic in the test.
- 2026-09-10 -- **The package named two comments; there were three.** Condition 2 cites
  `:953-955` and `:1179-1182` (`:982-984`/`:1256-1259` after `0275` and `0279` shifted
  them), but the file head carried the same false sentence -- *„zwei Listen koennen sich
  eine Zeile teilen, eine Stelle koennen sie nicht"*. Fixed all three. **When a package
  names N sites of a prose claim, grep the claim, not the line numbers.**
- 2026-09-10 -- **The residual the package carried was already closed by `0279`**, so I did
  not touch it: *„die geteilte Liste"* now has its anchor in the `KZ_GETEILT` case comment
  (`:1875`), which names the word and points at the enumeration. Of the counts I was told
  not to weaken, only the case total moved, and it had to: 27 -> 28 by `0279`, 28 -> 29 by
  me. 19, 8 (`ABGLEICHFAELLE`) and 16 stand unchanged and recounted.
- 2026-09-10, **what I am unsure about, for the project manager:** three things.
  **(a) I cannot compile.** The risk is low: the new row is one more aggregate in an
  existing `constexpr std::array`, nine initialisers against nine members, nothing newly
  `constexpr`-computed.
  **(b) Predicted numbers, so a divergence is visible instead of arguable.**
  `kennzeichen_riegel` green, printing `9 Faelle zur Zerlegung, 29 zum Lesen eines
  Verzeichnisses und 8 zum Abgleich`. Deleting `&& listen[l].probe == lz.probe` at `:1278`
  must give exactly one failure: `Fall 29 verfehlt ... knappe Listen: 0 erwartet 1`. If any
  *other* case moves on that deletion, distrust this line -- I claim none does, because at
  HEAD no case put two entries from different probes into `listen`, and that is the finding
  the package rests on.
  **(c)** The 47 in the case comment is hand-counted and nothing in the code depends on it;
  the equality rests on the two names being equally long, and the comment says so. A
  recount that gives 46 or 48 is a comment fix, not a broken case.
