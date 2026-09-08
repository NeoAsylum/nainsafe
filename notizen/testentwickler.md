# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 12395 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (twelfth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; every test
timeout well under the runner's 900 s; **mount red, read the numbers out of
`--output-on-failure`, write them the next run**; an expectation carrying an integer that
another package can move is a snapshot, not an expectation.

---

## What works

- 2026-09-08 (0232, riegelkopfzahlen) — **A `FEHLSCHLAG` line in the report is not by
  itself a defect of the delivered text.** `messung-0115` prints its output twice: the
  straight pass, then the Gegenprobe, which re-runs all three checks against a text where
  one Angabe is turned by a step and where every check *must* report — those reports are
  printed and then dropped from the tally. The package cut for me quoted a Gegenprobe line
  as a real defect; the head comment was right all along. **The arbiter is the tally line,
  not the FEHLSCHLAG count.** Read upward from the `G  Gegenprobe` line before believing a
  failure. Full account: `notizen/archiv/testentwickler-2026-09-08-2.md`.
- 2026-09-08 (0232, riegelkopfzahlen) — **What I write in a work package or a measurement
  stand cannot move the corpus numbers; what I write in the riegel can.** The citing set is
  `.cpp`, `.hpp`, `.cmake`, `CMakeLists.txt` plus `parameter.toml` and everything under
  `daten/`. `aufgaben/`, `befunde/`, `specs/`, `notizen/` are targets only, never citing.
  So `:NNN` references in a package body are free; inside the riegel the old rule holds —
  no `datei.ext` followed by a number, no keyword before a quote.
- 2026-09-08 (0232, riegelkopfzahlen) — **One added citation moved six numbers by one and
  left three untouched**, and which is which is not guessable: Zitate 36→37, aufgeloest
  36→37, the mutant's 47→48, the sum 93→94, while 70 uebergangen and the {2, 1, 7}
  breakdown stood still. Copy every one out of the report; derive none.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Twelfth run in a row with no shell**, and the second in which it did not
  matter: the nightly report carried the measurement.
- 2026-09-08 — **Two lanes wrote this logbook in the same hour and the runner rotated it
  between my read and my write.** Both entries survived in the archive, but a run that
  reads only the live file after a rotation sees an empty one. Write the entry, then check
  what is actually in the file.

## Open leads

- 2026-09-08 (0232, riegelkopfzahlen) — **The next report is the whole proof.** Expect
  `belegstellen_kopfzahlen` with return 0. An abort *„Alte und neue Fassung sind
  zeichengleich"* or a failed `git rev-parse` means `VORFASSUNGSSTAND = 4d14905` was not a
  commit carrying the file. The `Hinweis: ... aelter als der Baum` line will still appear
  — HEAD moves past `d17b26d` with my own commit; it is a Hinweis by design, nobody should
  chase it. A number that moves by one again means a lane added a citation overnight.
- 2026-09-08 (0232, riegelkopfzahlen) — **Three packages so far (0189, 0227, 0232) have
  done nothing but re-copy the same head-comment numbers, one full run each.** Worth its
  own proposal: let the stand *write* what it measured instead of comparing it. It touches
  a file two other packages keep, so it needs the project manager, not a quiet edit.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of
  the same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`);
  the day someone adds `-j`, they collide.

## Where I am unsure

**0232 (riegelkopfzahlen).** `4d14905` is HEAD at the start of my run and I claim it is
the parent of my commit — read from the run's git status, not from a shell. If another
lane commits first it is an ancestor instead, harmless while nobody else writes
`belegstellen_riegel.cpp`, and this package holds that file alone. The acceptance did not
ask me to move `VORFASSUNGSSTAND`; section C of the stand does, and leaving it would have
made Teil A measure 0189's change together with mine. I also moved the measurement date
in the head comment from 2026-09-07 to 2026-09-08 at all three places — no check reads it,
but a date that no longer matches the stand beside it is the same stale claim this package
exists to remove.

