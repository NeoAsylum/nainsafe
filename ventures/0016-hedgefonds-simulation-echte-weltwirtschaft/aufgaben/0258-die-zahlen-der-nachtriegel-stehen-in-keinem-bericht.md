---
id: 0258-die-zahlen-der-nachtriegel-stehen-in-keinem-bericht
rolle: kernbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "`kennzeichen_riegel` exits non-zero when a probe under `kern/test/` mentions `RIEGEL_OHNE_ZUSTAND` outside a comment and the tool parses no table out of it. The check finds its probes by symbol and directory, not by a hard-coded file name, and carries no hard-coded expected count. Red-when-broken is traced in code: name the line at which the tool raises and name what input reaches it. The count of parsed tables is printed on the failing path — not routed into the nightly report, see `vermerk`. **`At HEAD the tree passes` was narrowed by the project manager on 2026-09-08 (fifteenth run) to: no compile error and no failing assertion attributable to `kennzeichen_riegel.cpp`.** It was a whole-tree claim, and the three `RIEGEL_OHNE_ZUSTAND` tables you sweep sit in files under review tonight; a red caused in one of them is not your Ruecklauf."
vermerk: "**UNLOCKED 2026-09-08 (fifteenth run), project manager — `haengt_an: [0257]` removed, and the reason is that the lock was discharged by the landing, not by the verdict.** The lock below exists so you write your parser against `festkomma_probe.cpp`'s third `RIEGEL_OHNE_ZUSTAND` table instead of meeting it mid-flight. **That table is in the tree: `0257` was built and committed in the previous pass (`805589b`).** It stands `gebaut` and unreviewed, but a verdict changes no byte you read — `haengt_an` can only say `fertig`, so it was over-locking you by at least one night, and tonight that night is the whole factory: every other `offen` package hangs on unreviewed work and no build lane would run at all. **Read all three tables at HEAD before you start; if `festkomma_probe.cpp`'s is reshaped later, your parser must survive it anyway — that is what `by symbol, never by file name, no hard-coded count` is for, and it is unchanged below.** || ACCEPTED 2026-09-08 (fourteenth run), project manager — `vorschlag` → `offen`. **Renumbered from `0257` (two roles proposed a package the same night and both took that number); the original file is a pointer, in the shape `0092-linkschalterform-durchgereichtes-l.md` set. Way 2 accepted, way 1 not opened, one dependency added.** Proposed by the kern-pruefer out of the review of `0251`. || **WAY 1 IS NOT OPENED AND THE REASON IS NOT COST.** Making the numbers visible would put them in `befunde/uebersetzung-<datum>.md`, which is read by an operator with **two hours a week** (`CLAUDE.md`) and by reviewers looking for one fact. **A number in a report nobody diffs is not a guard — it is the same silence with more characters.** Way 1's real value was that it would make a written acceptance clause true, and that clause was mine: `0251`'s condition 1 demanded the wiring *so the numbers land in the report*. **The cheaper fix for a false criterion is to stop writing it, and that is recorded at `0251`'s `abgenommen` field and in my logbook. `ctest` swallows a passing test's stdout; no future condition gets to assume otherwise.** Way 1 stays available and unbuilt, with the proposer's own numbers so nobody re-measures them: run the riegel a second time at configure time via `execute_process` and `message(STATUS)`, in the shape `kern/CMakeLists.txt` already uses; it costs one extra execution per riegel — **0,13 s for `kennzeichen_riegel`, 31 s for `belegstellen_messung`, so it is the cheap riegel only** — and it is a package on the `werkzeuge/*/CMakeLists.txt` files, not this one. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` — nothing here needs a program to run inside your run, which is why the acceptance asks for red-when-broken **traced**, not demonstrated. **Acceptance:** checkable by reading, and **only** by reading — I am not asking for the count to appear in `befunde/uebersetzung-<datum>.md`, because that is the false clause this package exists because of. The tool prints its parsed count **on the path where it exits non-zero**, where `--output-on-failure` makes it visible; on a green night it prints where the reviewer reads it off the source. **Do not build a second mechanism to surface it.** **Files:** `kennzeichen_riegel.cpp` alone, free since `0251` went `fertig` tonight. **Precondition:** `0257`, below. || **YOU HANG ON `0257`, AND THE REASON IS THE ASYMMETRY, NOT SENIORITY.** `0257` is open on `kern/test/festkomma_probe.cpp` and gives that probe **a third** `RIEGEL_OHNE_ZUSTAND` table — exactly the set your new check sweeps. Our `dateien` are disjoint, so the planner would run us side by side. **Run first and a table you have never seen appears in your set the same night: if its shape does not match your parser the tree goes red and neither package is at fault.** Run second and you write the parser against three tables instead of two and verify it yourself. **Same work, one night later, and the acceptance becomes provable instead of hopeful.** This is the fifth time this month a package's `dateien` list was not its blast radius: `dateien` prevents overwrites, it does not prevent falsification. || **FIND THE TABLES BY SYMBOL, NEVER BY FILE NAME, AND THIS IS ACCEPTANCE AND NOT ADVICE.** `bezeichner_riegel` already walks a tree and owns its file selection — copy that shape. A tool that hard-codes `schritt_probe.cpp` would be one refactor away from looking at nothing, **which is the precise state `0251` exists to detect**: `0244` lifted the mechanism into `kennzeichen.hpp` and deliberately left one enumeration per probe (`kennzeichen.hpp:15-20`), there are two tables today and `0257` makes three, and `werte_probe`'s moved from line 233 to line 361 on 2026-09-08 alone. **It survived that move only because the tool carries no line numbers. The next move may not be a move.** || **NO HARD-CODED COUNT.** `0251`'s Vermerk forbids it and the ban stands: a floor written as a number is a second place to update and it will rot. The floor is the cross-check — every probe that names the symbol must yield a parsed table. || **NOT IN THIS PACKAGE:** the content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`, and `agents/baulauf.py` — **no agent may write `agents/`.** If capturing a passing test's stdout is what you conclude is needed, that is a decision for the operator and a line in your summary, not an edit."
---

# The night riegel's numbers stand in no report

Proposed 2026-09-08 by the kern-pruefer, out of the review of `0251`. Accepted as **way 2
only**; way 1 is recorded in the `vermerk` as considered and not opened.

## The measurement

`agents/baulauf.py:186` runs `ctest --test-dir <bau> --output-on-failure`. A **passing**
test's stdout goes nowhere. Tonight's report shows it for every riegel in the tree:
`belegstellen_riegel` (`uebersetzung-2026-09-08.md:121`), `bezeichner_riegel` (`:328`),
`zahlwort_riegel` (`:135`), `kennzeichen_riegel` (`:364`) — each one line, `Passed`, no
number. The numbers that *do* land come from `message(STATUS)` at configure time: the
Sperrebindungsriegel's `10 Kernquelle(n) und 12 Probe(n)` (`:19`), the
Nullabhaengigkeitsriegel (`:25`), the Warnsatz-Schlussriegel (`:26`), all from
`kern/CMakeLists.txt`.

## The concrete loss, and it is the half-blind run

These riegel all guard against *zero* and none against *half*. `kennzeichen_riegel`
returns 2 when it finds no table, no entry or no piece (`kennzeichen_riegel.cpp:1397-1423`)
— but if one of the **two** `RIEGEL_OHNE_ZUSTAND` tables stopped matching, its count drops
2 → 1, the run stays green, and the only thing that would show it is a number nobody can
see.

**This is not hypothetical:** `werte_probe`'s table moved from line 233 to line 361 on
2026-09-08. It survived because the tool carries no line numbers.

## What is built

Give the tool a floor that is not a number: **every probe under `kern/test/` that mentions
`RIEGEL_OHNE_ZUSTAND` outside a comment must yield a parsed table, else exit 2.** The probe
set is found by symbol and directory — the shape `bezeichner_riegel` already uses — so a
probe that is added, renamed or moved joins the set by itself.

## Why it is not part of `0251` and not part of `0255`

`0251` is `fertig` and met its three conditions; this is a defect of the criterion's
mechanism, not of that build. `0255` worked inside `werte_probe.cpp` and `kennzeichen.hpp`
on the *content* of the ledgers, not on whether a missing ledger is noticed.
