---
typ: pruefung
paket: 0208-anhaengen-pruefreihenfolge-falsche-richtung
pruefer: kern-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Both order paragraphs of the verlauf.cpp head held against the six abort branches of beginne_runde and anhaengen in reading order, plus the probe sheet and a sizeof hand-check anchoring the compiled class to the source read.
befunde: 0
---

# The head names the direction `anhaengen` checks in

## State measured

`kern/src/verlauf.cpp` is absent from `git status` at run start, so it stands at `HEAD`
(`be1a40b`). Both trees compiled it in this run, profile `FABRIK_SANITIZER=ON` with
`-fsanitize=undefined,address -fno-sanitize-recover=all`.

Anchor that the class I read is the class that was compiled: the probe sheet prints
`sizeof(Verlauf) 451784, sizeof(Kette) 17368, RUNDEN_KAPAZITAET 26`. By hand:
26 x 17368 = 451568 for `kette_`, plus 26 x 8 = 208 for `nummer_`, plus 8 for `runden_`
= 451784. Exact, no padding.

## Clause 1 — the direction is named, and named as the reverse

`beginne_runde`, branches in reading order: `runde < 1`; `runden_ > 0 && runde <=
nummer_[runden_ - 1]`; `runden_ >= RUNDEN_KAPAZITAET`. The paragraph says *"In
`beginne_runde` wird dann von der Aussage ueber das Argument zur Aussage ueber den
Behaelter geprueft"* and quotes all three conditions in that order. Match.

`anhaengen`, branches in reading order: `runden_ == 0`; `laufende.laenge() >=
GLIEDER_JE_RUNDE`; `satz.runde != nummer_[runden_ - 1]`. The paragraph says *"In
`anhaengen` ist die Reihenfolge ebenso festgelegt, laeuft aber in der Gegenrichtung"*,
container then argument, all three conditions in that order. Match. The half-sentence
*"und in derselben Richtung"* is gone.

Runtime confirmation, not only reading order: for a glied offered without a begun round
the sheet prints `es ist keine Runde begonnen`. Had the argument check stood first, the
call would have read `nummer_[runden_ - 1]` at `runden_ == 0` and died in ASan instead.

## Clause 2 — not merely the deletion

The reason stands in the head: *"Die Gegenrichtung ist dort erzwungen und nicht
gewaehlt: Die beiden spaeteren Pruefungen greifen selbst auf den Behaelter zu."*
Verified: `kette_` and `nummer_` are `std::array<..., RUNDEN_KAPAZITAET>`, `runden_` is
`std::size_t`. At `runden_ == 0` the expression `runden_ - 1` wraps to SIZE_MAX and both
subscripts leave the array. A memory-safety fact, not decoration.

## Clause 3 — read off the branches, not derived from the head

`include/kern/verlauf.hpp` lists three hard errors per function in the right order, but
names neither a direction nor a condition. The decisive detail is in neither the header
nor `specs/`: *"die mittlere Pruefung traegt ihre Bedingung an ihn mit `runden_ > 0 &&`
in sich selbst"*. That is visible only in the branch.

Beyond the criterion, the fix reaches the root. The frozen pre-0144 copy under
`befunde/messung-0144/vorher/` states the argument-to-container direction unscoped, for
the whole file — false for `anhaengen` already before 0186 added its half-sentence. It
is now scoped to `beginne_runde`.

## Clause 4 — probes green without change

21 of 21 in the workspace tree, 12 of 12 standalone, `verlauf_probe` passed. All six
abort messages print character-identical to the source. No probe source is changed
against `HEAD`.

## What I looked for and did not find

- **Code touched under cover of a comment package.** Function bodies compared against the
  frozen pre-0144 copy: identical except the T40 half-sentence in the full-Verlauf
  message and 0186's third branch, both printed in the probe sheet.
- **"erzwungen" over-stated.** Forced is only that `runden_ == 0` stands before the two
  others; capacity against mismatch is free. The head claims no more — it names exactly
  the forcing reason, and its closing rule (*"Jede Pruefung steht so frueh, wie ihre
  Operanden und ihre Meldung es zulassen"*) governs a new check instead of the direction.
- **The order stated in two files.** The header's per-function lists agree with the
  branches. No drift today.
