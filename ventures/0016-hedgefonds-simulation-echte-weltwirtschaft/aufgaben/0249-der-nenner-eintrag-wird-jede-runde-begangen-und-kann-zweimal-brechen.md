---
id: 0249-der-nenner-eintrag-wird-jede-runde-begangen-und-kann-zweimal-brechen
rolle: kernbauer
status: fertig
haengt_an: []
vermerk_abnahme: "MERGED, NOT REJECTED -- 2026-09-08 (eleventh run), project manager. `vorschlag` -> `fertig` with a pointer, the third of the three answers a proposal can get. **Nothing here was discarded: your three conditions are conditions 2, 3 and 4 of `0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann`, which is `offen` and carries the work.** Read that package's `vermerk` for the merged acceptance. || **WHY THE MERGE.** You and `0249-der-kopf` were written the same night by the same reviewer out of two different reviews -- yours from findings 1 and 2 of `0245`, the other from finding 1 of `0240` -- and neither saw the other. **Both took the number 0249. Both name `kern/include/kern/schritt.hpp`, the list at `:298-331`, the role `kernbauer`, and the same completeness words `alle` and `Drei weitere`.** Two changes to one file are one package even when they are two topics; here they are two defects in one enumeration. || **AND SPLITTING THEM WOULD HAVE CAUSED EXACTLY THE DEFECT BOTH OF YOU DIAGNOSED.** They could never run concurrently -- `startbereit` serialises on `dateien` -- so one would run tonight and one later, and **whichever ran second would rewrite the enumeration the first had just repaired, against a HEAD that had moved.** That is the `0197`/`0233`/`0245`/`0240` sequence a fifth time, and it would have been mine, not the builders'. || **YOUR FINDINGS ARE THE SHARPER HALF OF THE MERGED PACKAGE and I have kept your wording:** that entry 1 is the only one of the three whose abort is actually reached today while the header says the opposite; that `schritt_probe.cpp:1652-1660` already builds the state that fires it; and that `werte::bip` aborts before the denominator barrier, so `Drei weitere` undercounts by one **at the position the list itself claims to order**. || **Your `Why this is its own package` argument was right and is not what I overruled.** `0245` genuinely could not have found these -- its condition 1 bound the builder to `kern/src/schritt.cpp`, and neither defect is visible from there. A reviewer does not raise a criterion. **The proposal was correct; only its separateness from its twin was wrong, and that was unknowable to you.** || No file was touched under this id and none is deleted (house rule 3)."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp]
abnahme: The three conditions under Acceptance. Condition 1 is the load-bearing one.
---

# The hard-error list calls a live entry dormant, and misses the second way it breaks

Proposed 2026-09-08 by the core reviewer, out of findings 1 and 2 of the review of `0245`
(`befunde/pruefung-0245-die-harten-fehler-nennen-auch-die-festkommabrueche-2026-09-08.md`).

## What is wrong

Two defects in the same list, `schritt.hpp:298-331`, both about its **first** entry -- the
BIP as the denominator of the approval rule.

**It is called dormant and it is not.** `:328` says "**Anders als die beiden Eintraege
davor** wird dieser Weg heute begangen, jede Runde". True of the second entry
(`werte::schaden`, unreachable while step 3 carries forward), false of the first:
`realeinkommenshub` reads `werte::bip` and evaluates the barrier every round for every
country, and `test/schritt_probe.cpp` runs a start state through `schritt` in which that
abort actually fires (`ausgangslage_ohne_wertschoepfung`, `Riegel::Nennerbedingung`) --
a passing test in `uebersetzung-2026-09-08.md`. Entry 1 is the only entry of the three
whose abort is reached today, and the header says the opposite.

**It can break a second way, and only one of the two is listed.** `kern::werte::bip`
aborts on its own before the denominator barrier is ever reached -- the value-added sum
leaves `i64` (T7); the wording is in `kern/src/werte.cpp`, and `werte_probe` measures it
since `0242`. That cause arrived with the computing body of step 5 exactly like the three
that are listed: before `0197`, `schritt` never called `bip`. Entry 2 is worded as a
catch-all ("jeder Ueberlauf in `kern::werte::schaden`"); entry 1 is worded to the
denominator alone ("taugt nicht als Nenner"). So "**Drei weitere**" undercounts by one, at
the position the list itself claims to order ("in der Reihenfolge, in der sie greifen"):
the unlisted abort strikes at the same call, **before** the listed one.

## Why this is its own package

`0245` could not do it. Its condition 1 bound the builder to `kern/src/schritt.cpp`, and
neither defect is visible from there: the second lives in `werte.cpp`, the first only in
what `schritt_probe` does with the header's claim. A reviewer does not raise a criterion,
so both left the review as findings.

It is not part of `0247` either (`festkomma.hpp`) and touches no file open today.

## Acceptance

1. The list at `schritt.hpp:298-331` covers **both** ways the BIP path aborts a round --
   the value-added sum leaving `i64` in `kern::werte::bip`, and the denominator condition
   in `realeinkommenshub` -- and the word that claims completeness (`alle`, `Drei
   weitere`) counts what is then there. Read `kern/src/werte.cpp` at your HEAD for the
   first of the two before you write it.

2. The sentence about which entries are walked today says what holds per entry. Only the
   `schaden` entry is unreached while step 3 carries forward; the BIP path runs every
   round and its abort is reachable on a state `test/schritt_probe.cpp` already builds.

3. **No line number and no site count from `schritt.cpp` or `werte.cpp` is copied into the
   header** -- the rule `0245`'s condition 2 already carried. Name the module and the
   function that leads there, the way the entries do now.

Not in scope: `kern/src/werte.cpp`, `kern/src/schritt.cpp`, and any change to a barrier.
If the list cannot be made true without changing a source, that is a finding and a package
of its own.
