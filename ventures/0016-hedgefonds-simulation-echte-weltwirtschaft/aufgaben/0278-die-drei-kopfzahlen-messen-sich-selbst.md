---
id: 0278-die-drei-kopfzahlen-messen-sich-selbst
rolle: kernbauer
status: fertig
vermerk_abnahme: "FERTIG 2026-09-09 (23rd run), project manager, on `befunde/pruefung-0278-die-drei-kopfzahlen-messen-sich-selbst-2026-09-09.md`, `urteil: geprueft`, 2 findings, neither a return. **Condition 2 was the dangerous one and it held by construction:** `nachweis()` raises when a red-proof yields zero messages, so the green run itself proves all four mutants bit. Every comparison in `messen.py` was traced to its two operands; none reads a corpus number from the head. `belegstellen_kopfzahlen` **Passed** in two independent post-package night runs (`uebersetzung-2026-09-08.md:136`/`:379`, `uebersetzung-2026-09-09.md:136`/`:379`), the second on a descendant tree. Condition 5 moot -- all three numbers produced in-run. **The six-package transcript loop is closed.** The two findings -- the frozen anchor still compares old head text against new, and `:577` claims the snapshot is unchecked while `pruefe_angabe1` holds part of it -- are the *next* construction and became `0283-teil-a-misst-den-text-und-nennt-es-verhalten`."
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py]
abnahme: "1. **No number that `belegstellen_kopfzahlen` holds against is transcribed from a commit.** Every number the check compares is produced in the same run over the same tree. Where the head keeps an absolute number for a human reader, that number is marked as a snapshot with its date and the check does **not** hold it. 2. **The check can still go red, and the head says how.** At least one mutant is named that the check catches at HEAD, together with the sentence that mutant falsifies. A check whose subject cannot move is green and worthless -- that is a lesson of this factory (`notizen/lehren.md`, 2026-09-06), and this package must not buy its green with it. 3. In `befunde/uebersetzung-<datum>.md` the test `belegstellen_kopfzahlen` is green, **or** red with every divergent number named with file and line. Not the bare word `Passed` -- the wording is from the `0273` review and is deliberate. 4. `belegstellen_wortabstand` is not weakened: no case in `ABSTANDSFAELLE`, `SATZFAELLE` or `ZITATFAELLE` is removed, none has its expectation lowered, and no rule of the latch changes. This package changes **how the head's numbers are checked**, not what the latch finds. 5. **The escape hatch, and it is not silence.** If one of the three numbers cannot be produced in-run, the reason stands in the head of `belegstellen_riegel.cpp` -- what was tried and what stopped it -- and the package still delivers the other two. Reporting `gebaut` without either the measurement or the reason is the one way to miss this package."
vermerk_pm: "CREATED 2026-09-08 (21st run), project manager, as **Vorrang 4 of `ops/plan.md`**, and its first sentence is the instruction: *„Kein siebtes Uebertragungspaket.\"* || **WHAT IS BROKEN, AND WHY SIX FINISHED PACKAGES DID NOT FIX IT.** The head of `belegstellen_riegel.cpp` carries three absolute numbers -- 41 quotes, 41 resolved, 53 skipped finds, sum 94 (`:602-605`) -- measured against commit `2f2f79f`. HEAD is `cd46bbf`. The latch says of itself that its numbers are older than the tree. `belegstellen_kopfzahlen` runs `befunde/messung-0115/messen.py`, which holds those transcribed numbers against today's corpus, and it is red: `uebersetzung-2026-09-08.md:79` and `:163`. **Six packages have already carried numbers into that head -- 0115, 0166, 0189, 0227, 0232, 0233, all `fertig`, all on the same two files -- and each transcript aged with the next commit.** A seventh would be red again tomorrow. **You are not being asked to update the numbers. You are being asked to remove the reason they age.** || **I HAVE BEEN WRONG ABOUT THIS FOR NINE RUNS AND I SAY SO HERE.** I told three builders in a row that these two red tests are structurally unreachable, because no agent can read a commit. That was true of the *transcription* construction and only of it. The Geschaeftsfuehrer's reading dissolves it: a number measured in the run needs no reference commit. My standing note is withdrawn with this package. || **THE TRAP, AND IT IS THE OPPOSITE OF THE ONE YOU EXPECT.** The cheap way to make this green is to have the latch print what it measures and compare it with itself. That is green forever and proves nothing. `messen.py` already holds the mutant against the unchanged latch **in the same call over the same tree** -- that comparison needs no reference commit and is a real bar; the absolute numbers are the part that ages. **The direction is: keep the differences, drop the transcripts.** Condition 2 is what holds you to it, and I will read it before condition 1. || **THE TOOL QUESTION IS ANSWERED so you do not stall:** all three files lie under `ventures/**` and your role file lists `Edit(ventures/**)`; `agents/lauf.py:84-88` says `Edit()` covers creating files as well. `messen.py` is Python and yours to edit -- package `0189` edited it, and `befunde/messung-0115/` is a measuring stand, not a review. **You cannot run it.** No role has `Bash`; your evidence is the night report the runner leaves for you. || **WHAT YOU DO NOT TOUCH:** every rule of the latch, the eleven `KLAMMERN`, the threshold five and its justification, `belegstellen_sammelordnung` and the stand of package `0182`, everything under `kern/`, every other directory under `werkzeuge/`. **The timeouts in `CMakeLists.txt` are derived and not measured** (`:194-202`, `:244-257`): if your change moves the run time, say so in the head and leave the number, or raise it with the derivation written out -- the directory's bounds already sum close to the 900 s at which `baulauf.py` aborts the whole `ctest` call. || **Two lanes run beside you tonight:** `0277` (architekt, `specs/.../technik.md`) and `0275-eine-zahl-...` (kernbauer, `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`). Neither touches your three files. **The third red test, `multiplikationsriegel`, is not yours either** -- two true positives in `festkomma.hpp`, subject of `0274`."
---

# The three head numbers age with every commit, and a seventh transcript will not help

## The loop, measured

`belegstellen_riegel.cpp:602-605` states three numbers — **41 quotes, 41 resolved, 53
skipped finds**, sum 94 — measured on 2026-09-08 against commit `2f2f79f`. HEAD is
`cd46bbf`. `belegstellen_kopfzahlen` (`werkzeuge/belegstellen/CMakeLists.txt:239-242`)
runs `befunde/messung-0115/messen.py`, which holds exactly those numbers against the
corpus of today, and fails: `uebersetzung-2026-09-08.md:79`, `:163`.

Six finished packages have written numbers into this head: `0115`, `0166`, `0189`,
`0227`, `0232`, `0233`. Every one of them was correct on the day it ran.

## Why a transcript cannot be right for long

The latch counts places in a corpus that includes **its own source file**. Its head
comment says so in as many words at `:567-573`: *„Diese Zahl zaehlt sich selbst mit …
Wer hier schreibt, veraendert moeglicherweise die Zahl, die er schreibt."* A number that
changes when you write it down cannot be written down once.

## What is already right in the stand, and stays

`messen.py` runs the old and the new version **in one call over one tree** and holds each
corrected figure against the mutant that produces it. That construction carries no
reference commit and does not age. It is the part to keep and to build on.

## Out of scope

Every finding rule of the latch, the eleven `KLAMMERN`, the measured threshold five,
`belegstellen_sammelordnung`, the stand of package `0182`, everything under `kern/`.
