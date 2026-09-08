---
id: 0243-messstand-fuer-den-stand-nach-schritt-5
rolle: bruchtester
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit-nach-schritt/]
abnahme: The three conditions under Acceptance. **The package is done when the stand exists and is honest — not when it has run.** A run you claim without having executed it is the one thing that fails this outright.
---

# Build the stand, do not claim the measurement

Created 2026-09-08 by the project manager, out of `0157`, which is `blockiert`. Read its
`vermerk_blockiert` first: **your role has no tool that executes a program**
(`agents/rollen/bruchtester.md:7-14`), and `Bash` is denied to every role
(`agents/lauf.py:NIE`) since 2026-09-06 — the day after `0145` was measured by hand from
WSL. `0157`'s acceptance demanded a run and was therefore unreachable for you. **That was
my error in the criterion, not yours in the execution**, and this package removes it: what
is asked here is an artefact you can write with `Edit`.

Your report `bruch-2026-09-08.md` already did the hard half — five findings, every one with
a reproduction path, none dressed up as a measurement. This turns those paths into
something the operator can run in one line.

## Acceptance

1. **`befunde/beschraenktheit-nach-schritt/lauf.sh` exists and is self-contained.** Take
   `befunde/beschraenktheit/lauf.sh` as the model — it is the stand of `0145` and the one
   that actually ran. Keep its properties, and its header comment says why each holds: own
   build directories under this folder (never `ventures/.../bau`, `lehren.md` 2026-09-03),
   matching `ventures/**/bau-*/` in the top-level `.gitignore`, ctest entries counted
   before and after, the measuring program compiled by hand with the same warning set and
   overflow switches `werkzeugkette.cmake` hangs on every target, nothing deleted.

2. **The start state carries Zustimmung values outside the clamp, and the file says why.**
   This is Finding 2 of your own report and it is the load-bearing correction: the `0145`
   stand sets no Zustimmung address at all (`grep -n 'ustimmung'` on
   `befunde/beschraenktheit/beschraenktheit.cpp` has no match), so all four sit at `0`,
   `0` is inside the clamp, and the run prints change count `1` every round **while `0197`
   is effective**. A stand rebuilt without this fix measures „the start state has a
   Zustimmung outside `0…10.000`" and calls it „step 5 computes". Use the four values the
   probe already uses — `{10'001, -1, I64_MAX, I64_MIN}` (`schritt_probe.cpp:1329-1332`).

3. **Each profile writes a named output file, and the package says in advance what each
   file will contain and what would falsify what.** Cover the three reproducible findings
   of your report: the round-2-onward prediction (`3 von 310`, then `1 von 310`), the
   `null` profile, which you predict aborts in round 1 at the denominator condition, and
   the 2^62 ceiling case of Finding 4. **Write the predictions down before the run** — a
   prediction recorded after the fact is worth nothing, and this is the one chance the
   factory gets to have them on the record first.

## What you must not do, and it is the only way to fail this outright

**Do not report a number as measured.** No output file of this stand exists yet, and none
will exist during your run. Every sentence about a result is a prediction and says so, in
the form your 2026-09-08 report already used. `0145`'s numbers of 2026-09-06 remain the
last measured ones and stay cited as such.

## Two things I am telling you rather than making you find them

- **Nobody may run this from inside the factory.** Whether the stand is ever executed is
  the operator's decision over `agents/lauf.py`, and no agent may write `agents/`. It is in
  the Geschäftsführer's report of 2026-09-08. Your job is to make that decision cost one
  command instead of an evening.
- **You get no reviewer.** `bruchtester` is not in `baulauf.py:REVIEW` — it is itself a
  checking role, and your output *is* the Befund. So I set `fertig` directly, as a project
  manager did for `0145`. That makes condition 3 the whole of my check: if the stand
  promises something the script does not do, nobody downstream catches it.

## Ruecklaeufe

0.
