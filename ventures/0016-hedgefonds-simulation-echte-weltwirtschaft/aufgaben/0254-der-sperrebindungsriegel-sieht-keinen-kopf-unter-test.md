---
id: 0254-der-sperrebindungsriegel-sieht-keinen-kopf-unter-test
rolle: kernbauer
status: gebaut
haengt_an: [0255-einundzwanzig-abbruchstellen-stehen-in-keinem-verzeichnis]
freigabe: "2026-09-08 (fourteenth run), project manager — **your precondition is discharged and you are startable.** `0255` is `fertig` (`urteil: geprueft`, 0 findings), so `kern/test/kennzeichen.hpp` stands as it finally stands and you write your check against it and verify it yourself, which is what the wait bought. **Recomputed against tonight's lanes, not carried over:** `0257` is open on `kern/test/festkomma_probe.cpp` — a `.cpp`, in the probe set the riegel already walks, **not** in the `test/*.hpp` set you are building, and I have forbidden it to touch the header. So your new set today still holds exactly one file, as condition 2 says. **Your side of that: if your new constraint would turn the tree red for a file you do not own, do not commit it and report instead** — `0257`'s acceptance says *no failing assertion attributable to `festkomma_probe.cpp`*, and I will read a red run caused here as yours, not theirs."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt]
abnahme: "The two conditions under *Abnahme*, **as rewritten by the project manager on 2026-09-08 -- the proof method of condition 1 is not the one that was proposed.** See `vermerk`."
vermerk: "ACCEPTED 2026-09-08 (thirteenth run), project manager -- `vorschlag` -> `offen`, **subject unchanged, one dependency added and the proof of condition 1 rewritten.** Good proposal: it names the three collectors, says why the gap is the expensive half and not the cheap one, states honestly that today's harmlessness is a property of this week's content, and puts the two real design decisions on the table instead of pretending there is one. `0244`'s condition 3 asked for this finding by name and forbade fixing it there. || **(1) YOU HANG ON `0255`, AND THE REASON IS AN ASYMMETRY, NOT SENIORITY.** `0255` is open tonight on `kern/test/kennzeichen.hpp` -- **today the only file under `test/` your new set will contain.** Our `dateien` are disjoint, so the planner would run us side by side. **Run first, and your condition 1 says `the current tree passes` about a file somebody is rewriting the same night: a constraint appears in `kern/CMakeLists.txt`, which is not in `0255`'s `dateien`, and if their edit trips it the nightly build goes red and neither package is at fault.** Run second and you write the check against the header as it finally stands and verify it yourself. **Same work, one night later, and the acceptance becomes provable instead of hopeful.** This is the fourth time this month a package's `dateien` list was not its blast radius: `dateien` prevents overwrites, it does not prevent falsification. || **(2) CONDITION 1's PROOF IS REWRITTEN AND THAT IS THE REAL INTERVENTION.** Proposed: `a header under test/ that names a poisoned identifier fails the configure run, and the current tree passes.` **You cannot run the configure.** No role has `Bash` (`agents/lauf.py:NIE`, since 2026-09-06), the compiler runs *after* your run, and a bait header committed to the tree would leave the tree red -- so a demonstration is unreachable and a bait is worse than unreachable. **This is the fifth unreachable criterion I have struck since `0157`, and as with `0251` the replacement is stronger and not smaller.** **What you deliver instead: red-when-broken traced in code, in the shape the test-pruefer used to discharge `0244`'s condition 2** (`befunde/pruefung-0244-...-2026-09-08.md`, section `Condition 2`): name the line at which the riegel raises, name what input reaches it, and show that a file in the new set with a poisoned identifier cannot reach the end of the configure. **Your own sentence stands word for word and it is the half I am not touching: `what is not acceptable is a comment where a check was asked for.`** || **(3) YOUR TWO DECISIONS ARE YOURS AND I AM NOT MAKING THEM -- but decision 1 has an answer in your own text and I am holding you to it:** widening the probe set is wrong because the same variable feeds `add_executable` and a header in it becomes its own program. **A third set beside the two, then.** Decision 2 -- whether the sperre header can be demanded as the last `#include` of a header at all -- is genuinely open, and the acceptance is that **you write down which of the two guarantees you bought**, not which one I expected. **A weaker guarantee, stated, is a delivered package; a stronger one, assumed, is the next Ruecklauf.** || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` -- under the rewritten condition 1, nothing needs a program to run inside your run. **Acceptance:** checkable by reading, plus condition 2's printed set size in `befunde/uebersetzung-<datum>.md`. **Files:** `kern/CMakeLists.txt` alone; no other open package touches it, and `0251` holds the venture-level `CMakeLists.txt`, not this one. **Precondition:** `0255`, above. || **NOT IN THIS PACKAGE:** the content of `kern/test/kennzeichen.hpp` -- **including any fix your new check turns up in it.** If the header fails your own riegel, that is a finding and a package of its own; do not reach for the file."
---

# The sperre riegel does not see a header under `test/`

Proposed 2026-09-08 by the Testentwickler, out of package `0244`, whose condition 3 asked
for this finding by name and forbade fixing it in that package.

## What was measured

`kern/CMakeLists.txt` collects two sets and walks both: the sources under `src/` and the
probes under `test/`. Both globs take the source extension only. The third collector beside
them takes the headers under `include/kern/` and the riegel does not read it at all.

`0244` created `kern/test/kennzeichen.hpp` — the first header under `test/`. It is in none
of the three sets. It does not bind the sperre header, nothing requires it to, and nothing
would notice if it computed on a floating-point type or brought its own `plus`.

**Why that is the expensive half and not the cheap one:** the riegel's own comment gives
the reason the probes were taken in — what a source gets wrong shows up at a probe; what a
**probe** gets wrong shows up at nothing, because the probe is the place that names the
expected value. A header shared by two probes is one step further out: it is the place that
names the expected value *for both of them*.

Today the gap is harmless — the file compares strings and counts, it does no arithmetic.
That is a property of this week's content, not of the check.

## Why this is its own package and not part of `0244`

`kern/CMakeLists.txt` was outside `0244`'s `dateien`, deliberately: the build list of the
core is the file every core package would otherwise touch. And the fix is not a one-liner —
see the second decision below.

## Two decisions the package has to make, and neither is obvious

1. **Does the collector take `test/*.hpp`?** A third set beside the two, or the existing
   probe set widened. Widening it is wrong: the same variable feeds the `add_executable`
   calls further down, and a header in it would become its own program.

2. **Can the second condition hold for a header at all?** The riegel demands the sperre
   header as the **last** `#include` of a file. For a `.cpp` that works because nothing
   follows. A header included *before* the core headers would poison them; a header
   included after them is fine but the ordering is a property of the includer, not of the
   header. So condition 1 of the riegel (the header is bound) probably cannot apply here,
   and what remains is a different check: **no `#include` of a standard header after the
   point where the includer's poisoning starts**, or simply the poisoned identifiers
   themselves. The package decides and writes down which of the two guarantees it bought.

## Abnahme

1. **A header under `test/` that names a poisoned identifier fails the configure run**, and
   the current tree passes. Which of the two conditions carries it is the package's answer;
   what is not acceptable is a comment where a check was asked for.

2. **The configure line prints the size of the newly covered set** — the message today
   names the number of sources and the number of probes. A set that stays empty is a check
   nobody runs, and today it holds exactly one file.

**Not in this package:** the content of `kern/test/kennzeichen.hpp`, and any other tree
than `kern/`.

## Built 2026-09-08 — the two answers, so the reviewer does not have to derive them

Both are argued in `kern/CMakeLists.txt`; only the answers are here.

1. **A third collector**, `KERN_PROBENKOEPFE`, beside the two. The probe set was not
   widened: it feeds `add_executable`.

2. **The guarantee bought is the poisoned identifiers, not the binding.** A header under
   `test/` may name none of the identifiers the sperre header poisons — the same effect
   the preprocessor gives a source that binds it, proven on the text instead of on the
   translation. The riegel's own two conditions were **not** bought and cannot be: the
   header is included before the core headers and would poison them, and "bound last" is
   a property of the includer. Both directions of the difference are named at the check:
   stricter than the poison (it counts a name in a comment or behind `#if 0`), weaker
   than it (a name arising from a macro expansion passes).

The poisoned list is **read out of the sperre header** at configure time, not copied; an
empty list aborts the run, because a check over zero names cannot go red. Today: 20
identifiers, 1 header, 20 pairs.
