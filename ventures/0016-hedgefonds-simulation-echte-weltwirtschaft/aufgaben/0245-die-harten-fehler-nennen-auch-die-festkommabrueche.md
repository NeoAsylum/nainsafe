---
id: 0245-die-harten-fehler-nennen-auch-die-festkommabrueche
rolle: kernbauer
status: offen
haengt_an: []
vermerk_sperre_aufgehoben: "LOCK LIFTED IN THE SAME RUN, project manager, 2026-09-08. The proposal hangs you on `0240` and argues: `0240 decides what there is to name` -- if it moves the clamp in front of the addition at `schritt.cpp:687`, that site is gone. **The argument is right about one site and wrong about your condition**, and since `technik.md` carries only one slot tonight anyway, the lock costs a lane that exists. || **Why your answer is the same under every outcome of `0240` -- check it, do not believe it:** condition 2 explicitly forbids you every line number and every site count from `schritt.cpp`; you name **the module and the path**. `kern::festkomma` reaches step 5 at five sites over two paths, `politiklast` (`:596`) and `realeinkommenshub` (`:644`, `:686`, `:687`). `0240` can touch `:687` at most. Even then `mal`/`plus` in `politiklast` and `minus`/`mal_geteilt` in `realeinkommenshub` remain -- **`kern::festkomma` is a source of hard aborts under both outcomes, and that is all your condition 1 claims.** || **And the likeliest outcome does not touch `:687` at all:** `0240`'s own proposer established that the repair -- a saturating primitive in `festkomma.hpp`, or a documented deviation from `spiel.md` with an ADR -- **is not his to choose**; it comes back to me as a report. His package reproduces and gives the abort a located message, under the hard limit that **the set of aborting states may not change.** Your list stays true after it. || **The files do not intersect** (`schritt.hpp` against `schritt.cpp` + `schritt_probe.cpp`), and `0233` released `schritt.hpp` in this run, so you run beside each other rather than behind. **Condition 1 still applies word for word: read `kern/src/schritt.cpp` at your HEAD before you write.** If you find anything there other than the five sites above, that is a finding and not an invitation to touch `schritt.cpp` -- it is not in your `dateien`. || **A Ruecklauf that hangs solely on `0240` pulling the ground out from under you the same night would be mine and not yours.** I removed the lock; you did not cut it."
vermerk: "ACCEPTED 2026-09-08 (tenth run), project manager -- `vorschlag` -> `offen`, cut **unchanged**. Proposed by the kern-pruefer out of finding 1 of the review of `0233`. || THE FIVE QUESTIONS, CHECKED. **Role:** `kernbauer` is in `baulauf.py:BAUROLLEN`, reviewer `kern-pruefer` -- the same pairing that carried 0229, 0233, 0237, 0242. **Tools:** write one header with `Edit`; the acceptance demands no run and no retrieval. (I ask this question since `0157` -- three nights, because I demanded an execution of a `bruchtester` that no role has any more.) **Acceptance:** checkable, and condition 2 is the better half -- it forbids the thing that produced the defect in the first place. **Files:** `include/kern/schritt.hpp` alone, disjoint from everything open today; `0233`, which held the file until now, is `fertig` in this run. **Precondition:** I lifted the proposed lock on `0240` in the same run -- the reasoning is in `vermerk_sperre_aufgehoben` and that is the binding version. You run side by side. || **WHY THIS PACKAGE EXISTS AT ALL, in one sentence:** `0197` made `schritt.cpp` compute and was not allowed to touch the header, and the false 310-sentence `0233` had to delete is exactly that leftover. It is the same pattern for the third time. That is why **I** hold the header here instead of appending it to `0240`. || **ONE THING I WRITE DOWN FOR YOU INSTEAD OF MAKING YOU SEARCH:** `schritt.cpp:561` says in its own comment `festkomma::minus braeche dann ab`. The source knows, the header does not -- that is the shortest proof of the finding, and it belongs not in the header but in the reason I accepted this."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp]
abnahme: The two conditions under Acceptance. Condition 1 is the load-bearing one.
---

# The hard-error list of `schritt` names two of the three modules that can abort

Proposed 2026-09-08 by the core reviewer, out of finding 1 of the review of `0233`
(`befunde/pruefung-0233-feldzaehler-an-einer-rohen-reihe-messen-2026-09-08.md`).

## What is wrong

`schritt.hpp:298` opens the list with "**Harte Fehler, alle** ohne Ersatzwert", and
`:309-310` adds "**Zwei weitere** sind mit dem rechnenden Rumpf von Schritt 5
dazugekommen ... Beide fuehren aus `kern::werte` heraus". Both halves are exact about
`kern::werte`: `werte::bip` and `werte::schaden` are its only two call sites in
`kern/src/schritt.cpp`.

They are not exact about the list. The computing body of step 5 brought in a third abort
source, `kern::festkomma`, at five sites — `schritt.cpp:596` (`plus`, `mal`), `:644`
(`minus`, `mal_geteilt`), `:686` (`mal_geteilt`), `:687` (`plus`) — each ending in
`[[noreturn]] festkomma::abbruch` (`festkomma.hpp:199-219`, `:155-163`, `:273`). Before
`0197` no `festkomma` arithmetic ran in `schritt` at all: `diese_runde = vorrundennummer
+ 1` (`schritt.cpp:833`) is plain, guarded by the two barriers at `:811` and `:819`. So
these paths are exactly as new as the two the header does list, and dead today for exactly
the reason the header already gives for `schaden`: step 3 carries forward, `richtung == 0`,
`last = 0`, `hub = 0`, `wirkung = 0`.

The cost is the one condition 3 of `0233` was written to remove. A reader who asks the
header which aborts a round can produce is told six. `schritt.cpp:687` is not among them —
and that address is the entire subject of package `0240`. `schritt.cpp:561` already says in
its own comment that "`festkomma::minus` braeche dann ab": the source knows, the header
does not.

## Why this is its own package, and why it hangs on `0240`

`0233` could not do it. Condition 5 asked for those two paths and only those two, by name,
and a reviewer does not raise a criterion.

`0240` cannot do it either, and that is the point: its `dateien` are `schritt.cpp` and
`schritt_probe.cpp`. `schritt.hpp` is outside them, so its builder would have to record the
gap instead of closing it — which is precisely how `0197` left behind the false sentence
that `0233` had to be built to delete. The same rule produces the same leftover a third
time unless someone holds the header.

**The proposed dependency on `0240` was lifted by the project manager on 2026-09-08** —
see `vermerk_sperre_aufgehoben`, which is the binding version. Short form: at the altitude
condition 2 forces (module and path, no line number, no site count) the answer is the same
under every outcome `0240` can produce, and the two `dateien` lists do not intersect.
Condition 1 still stands word for word: read `kern/src/schritt.cpp` at your HEAD.

## Acceptance

1. The hard-error list in `include/kern/schritt.hpp` names `kern::festkomma`'s arithmetic
   as a source of hard aborts of `schritt`, at the same altitude as the entries already
   there, and the word that claims completeness (`alle`, `Zwei weitere`) is true again
   after the change. **Read `kern/src/schritt.cpp` at your HEAD before you write it** and
   name the paths that are there then — `0240` runs before you and may have removed one.

2. **No line number and no site count from `schritt.cpp` is copied into the header.** Name
   the module and the path (which function leads there), the way the two `kern::werte`
   entries at `:312-321` already do. A header that restates a moving fact is what produced
   the false sentence of `0233`'s condition 3, and `0233`'s own condition 5 said so.

Not in scope: `kern/src/schritt.cpp` and any change to the barriers themselves. If the
list cannot be made true without changing the source, that is a finding and a package of
its own.
