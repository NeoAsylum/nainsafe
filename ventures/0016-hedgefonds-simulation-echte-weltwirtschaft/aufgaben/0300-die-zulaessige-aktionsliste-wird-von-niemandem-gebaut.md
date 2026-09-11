---
id: 0300-die-zulaessige-aktionsliste-wird-von-niemandem-gebaut
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/aktion.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/aktion.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/aktion_probe.cpp]
abnahme: "1. **`zulaessige_aktionen(zustand, konstanten)` exists and returns this round's admissible list**, built once against the round-start state and in canonical order: `in_kanonischer_ordnung` returns `true` on the result, and one case shuffles the result and shows the same predicate returns `false`. 2. **The five target-id sets are the ones T32b's table names, and their sizes are computed from the constants, never written out**: kind 1 over `LAENDER*(SEKTOREN+2)` places, kind 2 over `LAENDER*SEKTOREN`, kind 3 over `LAENDER*INSTRUMENTE`, kinds 4 and 5 over one place each whose id is `0`. A case asserts today's values 20 / 12 / 16 / 1 / 1 against the computed sizes, so a fifth country moves both sides at once. 3. **Kind 1 has twenty places and nineteen offers.** The permanently empty currency slot of the USA keeps its place in the order and is never offered (T16). Enumerated, not swept: the case names that place by its `Steckplatz` ordinal, and asserts each of the other nineteen appears exactly once in the list. 4. **`buendel_zulaessig(zustand, konstanten, buendel)` checks the bundle as a whole against the same round-start state**, and four conditions each get their own case with a positive control on the edge that is still admissible: the same slot twice, cash overdrawn, more than three actions, and `fondsanteil(l, s) > 10000` after an action of kind 1 or 2. 5. **One case is the sentence T32 gives for why the check sits on the bundle**: three top-ups of the same slot, each individually admissible, the bundle inadmissible. 6. **The fifth condition of T32 is not built and the builder writes down why.** `|stufen(p)| > stufen_max` needs a constant `stufen_max`; greped on 2026-09-11, no such name exists under `kern/include/`. The builder does not invent a value -- they record in the package which constant is missing and at which line `spiel.md` or `technik.md` names it, and `buendel_zulaessig` carries a comment saying the condition is outstanding. 7. **Nothing outside the three files moves.** `fondsanteil`, `stufen` and `Konstanten` are called, not changed; no T21 command, no JSON, no stdin."
---

# The admissible-action list is specified in two places and built in none

`kern/include/kern/aktion.hpp` already carries the **order**: `zielkennung`,
`ordnungsvergleich` over the T32 key ranks, `in_kanonischer_ordnung`, `operator<=>`. What
it does not carry is the **list** -- nothing in the tree generates the actions admissible
in a round, and nothing checks a bundle.

That matters beyond the interface. Per `spiel.md`, Maß 1 draws actions *without replacement
from the list of actions admissible in this round* (T35). The measure that scores a game
reads a list that no code produces.

## Where the specification is

`technik.md` section 6, `## 6. Maschinenschnittstelle und Partieformat` -- **T32** (the list
is built once per round against the round-start state; `buendel_zulaessig` is the
bundle-wide check; two further conditions arrive with `spiel.md` version 5) and **T32b**
(the table of five kinds with the set each Zielkennung runs over, and the three
consequences). `Grep -n "^## 6\. Maschinenschnittstelle"` for today's line; the section is
about 5.2 kB and is the only one to read.

## Why this is cuttable today, and why it is not `schnittstelle`

Every input exists and is green. `Zustand` and its 310 addresses, `LAENDER`, `SEKTOREN`,
`INSTRUMENTE`, `Steckplatz` and its ordinal, `kern::werte::fondsanteil` and `stufen`, and
the T32 order itself. One constant is missing and condition 6 names it rather than
inventing it.

It belongs in `kern` and not in the unbuilt `schnittstelle` member because T32b says so in
its own third consequence: the domain is checked *where the list is built*, and the list is
built against `Zustand`. `schnittstelle` is the member that will **call** this; see `0301`,
which opens that member on the other half of section 6.

## Not in scope

T21 -- no command loop, no JSON, no standard input. The `setze` and load paths that T32b's
third consequence also names check the same domain at the edge and are `schnittstelle`'s
work, not this package's.

## Vermerk des Projektmanagers -- 2026-09-11

**Lane:** `kern/aktion.*` is touched by nothing else that is `offen` or `gebaut` today --
`0288` and `0299` sit on `werte.cpp`/`schritt.cpp` and their probes, `0286` on `werte.hpp`,
`0296` on `verlauf_probe.cpp`. No `haengt_an`; this is one of two packages that can run
tonight.

`0286` shifts the lines of `werte.hpp` and is unreviewed, so every condition above names
**symbols** and no line number under `kern/`. The evidence for conditions 1 to 6 lives in
`kern/test/aktion_probe.cpp`, which is in `dateien`.
