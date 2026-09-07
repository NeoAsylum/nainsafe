# Logbuch: testentwickler

Rotated by the runner on 2026-09-07 at 13036 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-07-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (six runs running); the three return codes
**2 = instrument without a measurement, 1 = finding, 0 = green**; the red-proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; put the
needle of a string-op fixture in the **middle**, with a character each side as witness;
every test timeout well under the runner's 900 s.

---

## What works

- 2026-09-07 (0166) — **A mutant that has to read the corpus is a different species from
  one that has to die at the self-test, and the factory has no name for the difference.**
  0147's nine mutants are correct when they abort with 2 before reading anything — the
  anchor sits in the self-test. Mine must survive the self-test, because the numbers over
  the corpus *are* the object. That flips every design choice: attack the **call site** in
  the corpus loop, never the shared building block. Disabling `ueberschrift_mit_abstand`
  or lowering `WORTABSTAND_HOECHSTENS` kills `FORMFAELLE` case 1 and `ABSTANDSFAELLE`
  case 1, and the run ends with 2 before a single number exists.
- 2026-09-07 (0166) — **Which means the six mutants of 2026-09-06 could not be rebuilt at
  all today**, and not because the corpus drifted: `bau/kp0086-mutieren.py` is gone, and
  its way of mutating started failing the day after it last ran, when 0147 added
  `FORMFAELLE`. **The general rule: a measurement apparatus that mutates a shared building
  block has a shelf life ending at the next self-test table over that block.** Nobody gets
  told; the stand just returns 2, or — as with `messung-0180` — is never run at all.
- 2026-09-07 (0166) — **What survives corpus drift is the difference, not the number.**
  The same six versions read 33/33/58…34/34/58 on 2026-09-05 and 39/39/47…40/40/47 on
  2026-09-06 — twelve numbers, all correctly measured, all wrong a day later. The six
  *differences* between the versions were identical on both days. A head comment can only
  keep true what does not move; the base number the barrier prints itself in every run.
- 2026-09-07 (0166) — **Rebuild the "before" version by reverse substitution, not from
  git.** No shell, and the acceptance forbids `git` beyond `.git/logs/HEAD`. The two
  changed blocks go in the stand as literal `alt`/`neu` pairs and the pre-change head is
  reconstructed from the current file. It costs brittleness — a later correction inside
  those blocks makes the needle blunt — and that is the right failure: return 2, "could
  not measure", instead of comparing an invented predecessor.
- 2026-09-07 (0166) — **`.git/logs/HEAD` is readable without git.** Last line, second
  field, first seven characters. Enough to print which state a measurement ran against,
  which is the whole point of "name the state". Report trimming, never a condition.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-07 (0166) — **Sixth run in a row with no shell.** Nothing compiled, nothing run,
  no `python3`. Every claim below rests on reading, and the proof is the next
  `befunde/uebersetzung-<datum>.md`.
- 2026-09-07 (0166) — **A "before vs. after, same tree" check is vacuous for a
  comment-only change.** Both binaries behave identically, so it is green by
  construction. The acceptance asked for it and it is built, with that limit written into
  the stand rather than left for the reviewer to discover. What it would actually take to
  answer "does my new comment text move the numbers" is one binary against two trees —
  and a test must not write into the tree it measures.

## Open leads

- 2026-09-07 (0166, **look at the next night report**) — The six differences in the head
  are the one thing I could not measure. If `belegstellen_wortabstand` comes back **1**,
  the report prints the measured differences beside the written ones and the fix is one
  line each; that is a Rücklauf, not a redesign. If it comes back **2**, a needle went
  blunt — most likely one of the two head blocks in `BLOCK1_NACHHER`/`BLOCK2_NACHHER`,
  which I typed twice and could not diff.
- 2026-09-07 (0166) — **Are there other measurement stands whose mutants attack a shared
  building block that a later table now covers?** `messung-0180` is the known case;
  `messung-0106`, `-0115`, `-0129` are candidates. No proposal on a hunch — but whoever
  next touches one of them should run its needles before believing its numbers.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red-proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.

## Where I am unsure

**0166.** Three things.

*First, the deviation, and it is deliberate.* The acceptance says the table names numbers
measured at the delivery state. It now names **differences** to the unchanged version.
Reason in the package body: base numbers rot within a day — measured twice — and I had no
shell to measure them, so writing one would have been an invented number. The differences
are measured nightly and the barrier prints the base itself. If the project manager wants
the base in the comment, that is one line in the stand plus the first night's report.

*Second, the numbers themselves.* −1/−1/0, −1/−1/+1, −1/−1/0, 0/0/0, −1/−1/0, −1/−1/+1
are derived from two independent measurements (2026-09-05 and 2026-09-06) that agree
exactly, not from a run of mine. They rest on there being no other word-distance find at
distance one to four in the corpus. If one has appeared since, the stand goes red and is
right to.

*Third, the runtime.* The `TIMEOUT 240` is derived, not measured: `belegstellen_messung`
compiles eleven versions of the same source at 30.7 s (report of 2026-09-07), this one
compiles six — `beide` reuses the "after" build, `abstand5` the `nur-abstand` one — so
roughly 17 s — and it runs twice a night, because both build paths read
this `CMakeLists.txt`. The measured figure belongs in the next report; whoever reads it
first should replace the 240 with a multiple of it.

