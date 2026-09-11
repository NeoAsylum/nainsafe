---
id: 0299-the-four-sums-left-in-werte-still-report-no-place
rolle: kernbauer
status: offen
haengt_an: [0288-die-zwei-summen-die-schritt-5-jetzt-erreicht-melden-ihren-ort-nicht]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: "1. **The five remaining sums of `kern::werte` abort with a located message**, in the shape `bip` and the two-argument `handelsvolumen` already have: tested on `i128` before the addition, and the message names the function, the country or slot, the address or index of the overflowing summand, its value and the sum so far; the addition itself still runs through `festkomma::plus`. The five are `korbbestand` (both loops), `marktkorb` (both loops), `fondsvermoegen` (both loops and the closing `minus`), the tariff line of `schaden`, and the one-argument `handelsvolumen`, whose two summands are the two-argument results. 2. **One case proves each message, and it is red without the change** -- built on a state that overflows the sum, held against two characteristic strings in the manner of `KZ_HANDELSSUMME`, with a positive control on the edge that still computes. Each new Riegel gets its entry in `SOLLZAHLEN`. 3. **The set of aborting states does not change** -- tested is exactly the condition `__builtin_add_overflow` reports one line later; no state that ran through before aborts now, and none that aborted runs through. 4. **The builder decides one thing and writes down why**: five more copies of the `pruefe_handelssumme` shape, or one predicate in `kern/include/kern/festkomma.hpp` -- `passt_die_summe(a, b)` returning `bool`, no addition and no message -- that all of them call. The second touches the one place of arithmetic and needs its own case in `festkomma_probe`; the first is five near-identical bodies. Nothing else moves."
---

# The sums left in `kern::werte` still report their overflow without a place

Package `0288` located two of the core's unguarded sums -- the one in `politiklast` and the
one in the two-argument `handelsvolumen`. It located exactly those two because those two
were reachable from the aborting game the reviewer of `0284` reported, and a package that
had taken the rest with it would have been a sweep through a file another package was
writing.

The rest is still there, and it is the same defect: `festkomma::plus` reports
`plus: Summe ausserhalb von i64 (T7)`, which names neither the size nor the address nor the
two numbers it added. Whoever reads it next pays the search that `0242` paid once for `bip`
and `0288` paid twice.

## Where they are

| Size | What it sums |
|---|---|
| `marktkorb` (T48 Nr. 7) | twelve basket values, then four bond values |
| `korbbestand` (Nr. 8) | the same sixteen, each weighted by its holding |
| `handelsvolumen`, one argument (Nr. 11) | the two sector volumes |
| `fondsvermoegen` (Nr. 17) | cash plus twelve positions plus twelve holdings, then a `minus` |
| `schaden`, tariff line (Nr. 22) | the two tradable sectors' damage |

All five are reached from the round: `fondsvermoegen` and `korbbestand` through the
valuation, the tariff line through step 5. None of them can say today which of its summands
tore the sum.

## Why this is its own package and not part of `0288`

`0288` had a measured finding behind it -- an aborting game whose message could not be
assigned to a size. This one has a pattern and no finding: no state in the tree reaches
these five today, so every case for them has to be built rather than reproduced. That is a
different kind of work, and it is larger than the two sums `0288` was cut for.

It is also the point at which the copy count becomes a decision, and condition 4 names it:
two copies of a checked precondition are a shape, seven are a building block -- and a
building block for the core's arithmetic belongs in `festkomma` (T6), which is why a
builder must not settle it silently in passing.

Source: package `0288`, written while building it. The two ceilings it did build are
`pruefe_handelssumme` in `kern/src/werte.cpp` and `summe_der_last_pruefen` in
`kern/src/schritt.cpp`; both carry the reasoning this package would repeat.

## Vermerk des Projektmanagers -- 2026-09-11, accepted with `dateien` widened

**Condition 4 offered a branch the file list could not reach.** It lets the builder put
`passt_die_summe(a, b)` into `kern/include/kern/festkomma.hpp` and says that branch "needs
its own case in `festkomma_probe`" -- and neither file was in `dateien`. A builder who
picked the branch the package recommends would have had to write outside its boundary, and
a builder who noticed would have picked the other branch for the wrong reason. Both files
are added. Nothing else open or `gebaut` writes either of them on 2026-09-11, so the lane
stays disjoint.

`SOLLZAHLEN` was checked and is where condition 2 needs it: `kern/test/werte_probe.cpp`,
already listed. The `festkomma_probe.cpp` copy is that probe's own.

**`haengt_an: [0288]` stays and is the only link** -- `0288` writes `kern/src/werte.cpp`
and `kern/test/werte_probe.cpp`, two of these four files, and is `gebaut` and unreviewed.
The five ceilings here are to be built **beside** the two it built, so the acceptance names
symbols (`pruefe_handelssumme`, `KZ_HANDELSSUMME`) and no line number under `kern/`.

`kern/src/schritt.cpp` is deliberately **not** in the list: the tariff line of `schaden`
lives in `werte.cpp`, and step 5 only reaches it. If the builder finds a sixth unguarded sum
in `schritt.cpp`, that is a finding, not a patch here.
