---
typ: pruefung
paket: 0273-der-riegel-aus-t7-ist-beschrieben-und-nicht-gebaut
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all five conditions recounted against source and build report; rule 5 hand-traced on schritt.cpp:405 and on the `/` case; both red sites verified as true positives, not latch defects
befunde: 2
---

# geprueft -- and condition 5 is literally unmet

## What I checked, and how

**Numbers, recounted.** 23 `.hpp`/`.cpp` under `kern/include` and `kern/src` (`Glob`) -- the
run says 23. `constexpr u64` declarations outside `kern/test`: exactly 7 (`zufall.cpp:190,192`,
`pruefsumme.hpp:94,105`, `zufall.hpp:137,140,141`) -- the run says 7, and the function
declarations `constexpr u64 wert()`, `fnv1a64(...)` are kept out by the `(`-check in
`sammle_namen:706`. 36 lines, matching T7 `:877-884`.

**Rule 5, by hand.** `schritt.cpp:405` through `lies` -> `finde_behauptungen` ->
`linker_operand`/`rechter_operand` -> `traegt_nur_literale`: left operand `4`, right
`(12 + 9 + 1)`, left bound the opening `static_assert(`, right bound the `==`, every character
of the run inside the alphabet -> rule 5. Self-test case 11, `static_assert(4 * 3 / 2 == 6)`:
the right scan stops at `==`, and the `/` inside the run is outside the alphabet -> no match,
one finding. The sentence of `0268` is built, not guessed.

**Condition 4.** Every case the criterion names is there: rules 1-5 (cases 1-10), fifth kind
(15), `*` in string content (17) and comment text (18, 23), the `/` case (11). Expectations
written out per case; the one non-constructible case stands in the head as blind spot 3.

**Condition 2.** `PROJECT_IS_TOP_LEVEL` block, `../../werkzeugkette.cmake`, `enable_testing()`,
`fabrik_warnsatz_anlegen`, `add_test` in T7's wording; root `CMakeLists.txt:84` carries
`werkzeuge/multiplikation`. Both build paths compile green (`uebersetzung-2026-09-08.md:38,61`
and `:467`).

**Determinism.** The one place a directory order could leak in is closed: `sammle_quellen:1090`
sorts. No floating point, no time, no addresses. The name lists accumulate over the sorted
corpus and are only asked for membership; `behauptungen` is rebuilt per file. `NICHTS` is
checked at every caller, `--tiefe` cannot underflow because every bracket walker returns at
depth 0, `ist_binaeres_mal` guards both ends.

**Searched and empty.** Paren-adjacent narrow spelling (`)*x`, `x*(`) over `kern/include` and
`kern/src`: 0 matches, so restricting to T7's two spellings costs nothing today. Rule 1
excusing a real `i64 * i64` by swallowing a call argument: checked T7's own example
(`:816`, `positionswert`) -- `werte.cpp:550` runs through `mal()`, and the only ` * ` in the
file is the `static_assert` at `:298`. No excused multiplication.

## Befund 1 -- condition 5 demands `Passed`, and the test is `***Failed`

`uebersetzung-2026-09-08.md:132` and `:477`. The red is a true positive, not a defect:
`festkomma.hpp:99` `const i128 rest = az - ganz * an;` has no cast on either side, no layout
constant, no `sizeof`, no unsigned literal, no `static_assert`; `:356`
`((static_cast<i128>(n) - 1) * r` has the cast on the **left only**, and rule 4 (T7 `:846`)
says both sides. T7 `:882-884` is false at HEAD `cd46bbf`. Package `0274` already carries this
against `specs/`; I do not duplicate it.

I judge `geprueft` because `vermerk_pm` -- part of this package, addressed to the reviewer --
pre-authorises exactly this red. But **conditions 3 and 5 contradict each other in the case
that occurred**: 3 orders the red, 5 forbids it. That is a finding against the criterion, not
against the builder, and it is for the project manager. The buildable wording for the next
latch package is "green, **or** red with every divergent line named with file and line" --
not "`Passed`".

## Befund 2 -- `*=` is invisible, and it is not among the four blind spots

`ist_binaeres_mal:421-422` needs whitespace or a name character on **both** sides. `wert *= b`
has `=` on the right, is never seen, and raises neither a rule nor the line count. Three sites
exist today: `festkomma.hpp:123`, `:311`, `pruefsumme.hpp:177`. All three are `i128 *= i128`
or the deliberately wrapping `u64` checksum of T12, so measure 4.3 is not violated at HEAD --
but a latch whose point is deny-by-default lets a future `i64 wert; wert *= faktor;` through
in silence, and that is the failure mode T7 `:828-831` built the latch to avoid. No
Ruecklauf: the criterion names "binary `*`" and the two spellings of `:863`, and `*=` is
neither. Proposal `0275`.
