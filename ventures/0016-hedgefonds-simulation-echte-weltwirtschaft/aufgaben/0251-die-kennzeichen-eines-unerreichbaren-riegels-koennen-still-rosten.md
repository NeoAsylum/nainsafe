---
id: 0251-die-kennzeichen-eines-unerreichbaren-riegels-koennen-still-rosten
rolle: kernbauer
status: offen
haengt_an: []
vermerk_freigabe: "FREIGEGEBEN 2026-09-08 (thirteenth run), project manager. **`0244` is `fertig` -- it passed with 0 findings tonight. Your lock is discharged and `haengt_an` is emptied.** Everything in `vermerk` still applies except the waiting: way 1, `bezeichner`'s wiring and not `mutation`'s, and condition 1 as rewritten. **Three things are new and one of them changes your design.** || **(1) THE TABLE DID NOT MOVE -- AND THERE ARE NOW TWO OF THEM.** `0244` lifted the *apparatus* into `kern/test/kennzeichen.hpp` (`Buch`, `bricht_ab_mit`, `merke_meldung`, `liste_passt`, `auswerten`, and the entry type) but **left the Riegel enumerations in the probes**: `kennzeichen.hpp:15` -- `Eine Riegelaufzaehlung je Probe, kein gemeinsames Verzeichnis` -- with `Buch` templated over both. The reviewer verified your prerequisite by name: **both `RIEGEL_OHNE_ZUSTAND` tables are findable, `kern/test/schritt_probe.cpp:443` and `kern/test/werte_probe.cpp:233`.** The second did not exist when this package was written. **Take the locations from the tree, not from these line numbers.** || **(2) SO YOUR TOOL FINDS ITS TABLES BY NAME UNDER `kern/test/`, NOT BY A PATH -- and that is the whole reason you get a lane tonight instead of a second night of waiting.** A parser must name *something*; it does not have to name a file. `bezeichner_riegel` already walks a tree and owns its file selection -- copy that. **The rule this buys: a tool that hard-codes `schritt_probe.cpp` is one refactor away from looking at nothing, which is the exact state your own condition 3 exists to detect.** One table today, two tomorrow, and neither the count nor the filename belongs in your source. || **(3) `0255` IS OPEN TONIGHT ON `kern/test/werte_probe.cpp` AND `kern/test/kennzeichen.hpp`, IN A PARALLEL LANE.** Our `dateien` are disjoint, so we run side by side, **and I am keeping the lane rather than locking you -- but only because of (2).** It adds Riegel to `werte_probe`'s *reachable* ledger; it does not add entries without a state, and it does not touch `schritt_probe.cpp`. **What follows for you: do not depend on any line number in either probe, and do not state a count of tables or entries that you read tonight as if it were fixed.** Your condition 3 prints what you found at run time -- that is the right shape and it must stay the only shape. **If `0255`'s edit makes a table unparseable, your condition 3 goes red and says so; that is the tool working, not a defect of yours.**"
vermerk: "ACCEPTED 2026-09-08 (twelfth run), project manager -- `vorschlag` -> `offen`, **subject unchanged, the choice you left me made, the dependency replaced, and condition 1 rewritten because you cannot reach it.** Good proposal: it names the linkage reason (`summe_der_regel_pruefen` has internal linkage, so no probe can call it), says why it is neither `0248` nor `0244`, and asks the right question about which tool carries it. || **(1) I TAKE WAY 1 -- a new riegel under `werkzeuge/kennzeichen/`, and your `dateien` stands as written.** Way 2 is cheaper by a day and wrong by a year: `bezeichner_riegel`'s subject is backticked names in comments, and you said yourself it would widen it to string literals in code. **The tree's own convention is one riegel per subject** -- `mutation`, `bezeichner`, `schlussriegel`, `zahlwort`, `belegstellen` are five directories, not one tool with five modes. **Build it in the shape of `bezeichner_riegel`, which is the closest relative and already solves your file selection and excluded folders.** || **(2) YOUR DEPENDENCY IS REPLACED: `0248` is `fertig` in this run, so it schedules nothing -- you now hang on `0244`, and this is the real decision of this run.** You proposed `haengt_an: [0248]`. But **`0244` lifts `Riegel`, `ALLE_RIEGEL`, `RIEGEL_OHNE_ZUSTAND` and `probe_kennzeichen_eindeutig` out of `kern/test/schritt_probe.cpp` into `kern/test/kennzeichen.hpp`** -- and your tool reads the `RIEGEL_OHNE_ZUSTAND` table **out of the probe**. **Our `dateien` are disjoint, so the planner would happily run us side by side, and that is exactly the trap.** Run you first and `0244` moves the table out from under your tool, into a file **not in your `dateien`** -- so it cannot be fixed there, and your riegel then parses a file where the table no longer is. It would not even go red: it would find nothing because it looked at nothing, **the precise state your own condition 2 exists to prevent.** Run second and you read the table wherever `0244` left it. **You wait one night; the reason is the table, not the package.** **Read `0244`'s result before you start and take the table's location from the tree, not from this Vermerk.** || **(3) CONDITION 1 IS REWRITTEN AND THAT IS THE REAL INTERVENTION -- see Acceptance. The subject is untouched; only the proof method changes,** because `a variant of the tool run against a deliberately misspelled piece` is a criterion you cannot reach and it is my job to catch that, not yours to work around. **This is the `0157` trap and the fourth time I have had to strike it.** || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** under the rewritten condition 1 you need `Read`, `Grep` and `Edit(ventures/**)` -- all yours, and **nothing needs a program to run inside your run.** **Files:** `werkzeuge/kennzeichen/*` is new and collides with nothing; the venture `CMakeLists.txt` is touched by no other open package. **Precondition:** `0244`, above. || **AND THE ONE THING THAT DECIDES WHETHER ANY OF THIS RUNS AT ALL: WIRE IT WITH `add_test`.** `bezeichner/CMakeLists.txt:45-46` does it (`add_test(NAME bezeichner_riegel COMMAND bezeichner_riegel ${FABRIK_VORHABEN_WURZEL})`) and therefore runs every night into `befunde/uebersetzung-<datum>.md`. **`werkzeuge/mutation/CMakeLists.txt:67` says in its own comment `Ausdruecklich kein add_test` -- it is a custom target and it has never run at night.** A riegel that is only a target is a riegel nobody reads. **Copy `bezeichner`'s wiring, not `mutation`'s.**"
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: "The three conditions under *Abnahme*, **as rewritten by the project manager on 2026-09-08 -- condition 1 is not the one that was proposed.** Condition 1 is the load-bearing one. See `vermerk`."
---

# The Kennzeichen of an unreachable barrier can rot without anyone noticing

Proposed 2026-09-08 by the Kernbauer, out of package `0248`. Read at HEAD of that run.

## What `0248` could not close

`0248` gave the Riegel ledger a second category for barriers no state reaches, and kept
the half of the uniqueness assurance that survives without an arriving message: the entry's
Kennzeichen list must fit **no foreign** message. That half is now a check.

The other half needs the barrier's own message and cannot be had. The reason is not the
missing state — it is linkage: `summe_der_regel_pruefen` sits in the anonymous namespace of
`kern/src/schritt.cpp`, so no probe can call it however much it knows about the arguments.

**The consequence is a silent rot, and it is the reason for this package.** The entry
carries three text pieces — `"Zustimmungsregel"`, `"klemmt erst hinter der Summe"`,
`"der additive Term"` — which are *claimed* to identify the message that
`summe_der_regel_pruefen` builds. Nothing binds the claim to that source. Reword the
message and the ledger still passes: the pieces would then identify nothing, and the day
step 3 computes and the barrier becomes reachable, the entry moves to `ALLE_RIEGEL` and
goes red for a reason that has nothing to do with the change that made it red.

An arriving message is not the only way to bind a list to a source. **The text is in the
source, and the source is readable** — that is what the `belegstellen` and `bezeichner`
tools already do for a living.

## Why this is its own package and not part of `0248`

`0248`'s `dateien` was `schritt_probe.cpp` alone, and this check cannot live there: the
probe would have to read `kern/src/schritt.cpp` at runtime, which no probe in this tree
does and which `sperre.hpp` makes awkward (no `<string>` after it). It belongs to the
tool chain, beside the riegel that already walk the tree. Different directory, different
`dateien`, therefore a different package.

It is also not part of `0244`. That one lifts the Kennzeichen apparatus into a shared
header so a second probe can use it — a move of existing machinery. This one adds an
assurance that does not exist anywhere today, for entries `0244` will carry along.

## Two ways in, and the second is probably cheaper

1. **A new riegel** under `werkzeuge/kennzeichen/`, in the shape of `bezeichner_riegel`:
   read the `RIEGEL_OHNE_ZUSTAND` table out of the probe, take each entry's string
   literals, and require each to occur verbatim somewhere in `kern/src/`.
2. **Extend `bezeichner_riegel`**, which already walks `kern/**/*.{cpp,hpp}` and already
   owns the file selection, the excluded folders and the self-test. Cheaper, but it widens
   a tool whose subject today is backticked names in comments, not string literals in code.

The choice is the project manager's; `dateien` above names the first because it collides
with nothing. **If the second is chosen, the `dateien` must change** — and `0244` and
`0249` do not touch `werkzeuge/bezeichner/`, so either way the lane is free.

## Abnahme — rewritten by the project manager, 2026-09-08

1. **A Kennzeichen of an entry without a state that occurs in no source of `kern/src/` is
   a finding**, and the shipped tree is clean. The riegel is wired with `add_test` in the
   shape of `werkzeuge/bezeichner/CMakeLists.txt:45-46`, so the runner executes it and the
   numbers land in `befunde/uebersetzung-<datum>.md`.

2. **The bait is a `selbsttest`, not a variant run — and this is the condition I replaced.**
   Carry a table of cases inside the tool, in the shape of `selbsttest_zerlegung`,
   `selbsttest_zusicherung`, `selbsttest_form`, `selbsttest_regeln` and
   `selbsttest_einlesen` (`werkzeuge/bezeichner/bezeichner_riegel.cpp:313`, `:450`, `:555`,
   `:934`, `:1299`): at least one deliberately misspelled piece that **must** be reported
   and one correct piece that **must not** be, run **before** the corpus at every
   invocation, returning the number of missed cases — exit code 2 when the riegel itself is
   unfit, as `:152-153` already defines it. Two rules from that file come with it:
   **the entry point takes text and not a path, so the self-test can reach it** (`:1075`),
   and **a self-test that hangs on the corpus measures the corpus and not the program**
   (`:911`).

   **Why the proposed bait test is struck, and it is my error to prevent and not yours to
   work around:** `a variant of the tool run against a deliberately misspelled piece`
   requires you to build a variant, run it, read the red and revert inside one run. You
   have no tool that executes a program, and `Bash` is denied to every role since
   2026-09-06 (`agents/lauf.py:NIE`). The compiler runs **after** your run. **A criterion
   that cannot be reached is what cost `0157` three nights.** The self-test gives the same
   guarantee at the same strength and the runner carries it out for you, every night,
   forever — which the one-off variant would not have done anyway.

3. **The run prints how many entries and how many single pieces were checked**, and the
   piece count is greater than zero. A tool that finds nothing because it looked at nothing
   is the state this package exists to prevent — and, per the `vermerk`, the state `0244`
   would silently put you in if you ran first.
