# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 14185 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (twelfth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; every test
timeout well under the runner's 900 s; **mount red, read the numbers out of
`--output-on-failure`, write them the next run.**

---

## What works

- 2026-09-08 (0232) — **A `FEHLSCHLAG` line in the report is not by itself a defect of
  the delivered text, and I nearly inherited a wrong one.** `messung-0115` prints its
  output twice: the straight pass, then the Gegenprobe, which re-runs all three checks
  against a text where exactly one Angabe is turned by one step and where every check
  *must* report. Those reports are printed and then dropped from the tally
  (`del fehler[vorher_fehler:]`). The package cut for me quoted the Gegenprobe's Angabe-3
  line as a real defect "left over from 0189" — the head comment was right all along.
  **The arbiter is the tally line, not the FEHLSCHLAG count:** six unmet expectations,
  three for Angabe 1 and three for Angabe 2, and everything below the second `B1` block
  belongs to the Gegenprobe. Read from the `G  Gegenprobe` line upward before believing a
  failure.
- 2026-09-08 (0232) — **What I write in a work package or in a measurement stand cannot
  move the corpus numbers; what I write in the riegel can.** The citing set is source
  files (`.cpp`, `.hpp`, `.cmake`, `CMakeLists.txt`) plus `parameter.toml` and everything
  under `daten/`. `aufgaben/`, `befunde/`, `specs/` and `notizen/` are targets only, never
  citing — the riegel's head says it at *„Was auch Bedingung 2 nicht liest"*. So the
  `:NNN` line references in a package body are free, and the `-0115` stand's own comments
  are free. Inside `belegstellen_riegel.cpp` the old rule stands: no `datei.ext` followed
  by a number, no keyword before a quote.
- 2026-09-08 (0232) — **Six numbers moved by exactly one because one citation was added to
  the corpus, and every one of them had to be copied, not derived.** 0225 added a citation
  in `reihen.toml`; that moved Zitate 36→37, aufgeloest 36→37, the mutant's 47→48 and the
  sum 93→94, while 70 uebergangen and the {2, 1, 7} breakdown did not move at all. Nothing
  about which numbers follow a single citation is guessable in advance — the mutant's
  count rose by one because it counts the same site twice over, and the passed-over sites
  did not rise because the new citation resolves. Copy all of them.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 (0232) — **Twelfth run in a row with no shell**, and the second in which it
  did not matter: the nightly report carried the measurement. Nothing compiled here by
  hand.

## Open leads

- 2026-09-08 (0232) — **The next report is the whole proof.** Expect `belegstellen_kopfzahlen`
  with return 0. In order of what would hurt most: (1) `A vorher` must produce numbers —
  an abort *„Alte und neue Fassung sind zeichengleich"* or a failed `git rev-parse` means
  `VORFASSUNGSSTAND = 4d14905` was not a commit that carries the file; (2) all six
  corrected numbers silent; (3) the `Hinweis: HEAD steht auf ... aelter als der Baum` line
  will still appear, because HEAD moves past `d17b26d` with my own commit — it is a
  Hinweis and not a Fehlschlag, by design, and nobody should chase it; (4) if a number
  moves again by one, a lane added a citation to `daten/` or a source file overnight, and
  that is a fourth package, not a mistake in this one.
- 2026-09-08 (0232) — **The head comment cites its own measuring stand at three places and
  the numbers at two more; they are only ever right for one night.** Three packages so far
  (0189, 0227, 0232) have done nothing but re-copy them. The re-copy is mechanical and
  costs a full run each time. Worth its own proposal: let the stand *write* the numbers it
  measured into the comment instead of comparing them — but that is a builder's change to
  a file two other packages keep touching, so it needs the project manager, not a quiet
  edit.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build and run
  copies of the same source and one writes to it. ctest is serial today (no `-j` in
  `baulauf.py`); the day someone adds `-j`, they collide. `RESOURCE_LOCK` on all four
  would fix it, but three entries belong to other packages.

## Where I am unsure

**0232.** Two things.

*`4d14905` is HEAD at the start of my run and I claim it is the parent of my commit.* I
read it from the run's git status, not from a shell. If another lane commits first it is
an ancestor instead, which is harmless while nobody else writes `belegstellen_riegel.cpp`
— this package holds that file alone. The acceptance did not ask me to move
`VORFASSUNGSSTAND`; section C of the stand does, and leaving it would have made Teil A
measure 0189's change together with mine. I moved it and wrote why into the package body.

*The dates in the head comment.* The acceptance names the numbers and the Stand, not the
date. I moved *„Gemessen am 2026-09-07"* to 2026-09-08 at all three places, because a
measurement date that no longer matches the stand next to it is the same kind of stale
claim the whole package exists to remove. No check reads the date.

**Still valid from the predecessors:** no shell (twelve runs running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as
a standing fixture inside the program; a script in no `add_test` runs nowhere; put the
needle of a string-op fixture in the **middle**, with a character each side as witness;
every test timeout well under the runner's 900 s; **mount red, read the numbers out of
`--output-on-failure`, write them the next run**.

---

## What works

- 2026-09-08 (0232) — **A hard-coded number that names a position in a file you do not
  own is a measurement of its writing day.** Same shape as the case numbers 0194 broke and
  as 0189's Vorfassung pin, one level down: A2's fifth expectation said `Zeilennummer 157`,
  0229 inserted above it, and the stand went red with nothing wrong at the riegel. The fix
  that generalises: **hang the expectation on the wording, derive the position.** The rule
  I would apply next time without being asked — if an expectation contains an integer that
  some *other* package can move, it is not an expectation, it is a snapshot.
- 2026-09-08 (0232) — **A derived expectation is only allowed if it can still go red, and
  that takes three separate properties, not one.** The package warned that a derivation
  matching whatever it finds is worse than a stale number. What makes this one safe:
  (1) the needle must occur **exactly once** or the run aborts, (2) the number is derived
  from the **input** text and never from the program's own output — otherwise it is a
  tautology, (3) the comparison stays over the **whole list**, so a dropped finding is
  still red. Property 2 is the one that is easy to get wrong and impossible to see
  afterwards.
- 2026-09-08 (0232) — **Fix the class, not the instance, when the instance is one of
  five.** Only entry five had moved; entries 2, 16, 32 were equally coupled and equally
  one insertion away. Deriving all five costs four more lines and removes the whole trap.
  It also made the ordering question visible: the riegel prints in file order, so the
  derived list is `sorted` by line — **stable**, so the two claims sharing line 32 keep
  their order. Sorting is not a weakening here; it is a faithful model of what the riegel
  does.
- 2026-09-08 (0232) — **Print the derived number even in a green run.** `A2: 5
  Behauptungen erwartet, ihre Zeilen ... erhoben: [2, 16, 32, 32, 185]` costs one line and
  turns the nightly report into the place where the next agent reads the current numbers
  off. A derivation that only shows itself on failure is invisible exactly when it is
  right.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 (0232) — **Twelfth run in a row with no shell.** Nothing compiled, nothing
  run. Needle uniqueness checked with four `Grep -c` calls, which count *lines* and not
  occurrences; `str.count` is stricter, so a second occurrence on the same line would show
  up as a red `Messfehler` and not as a silent pass. Acceptable, but it is not the same
  check.

## Open leads

- 2026-09-08 (0232) — **The next report is the proof.** Expect `zahlwort_messung` green on
  both build paths, `Selbstprobe: 5 Faelle zu zeile_von`, the new `A2: ... erhoben: [2, 16,
  32, 32, 185]` line, `A2 ... Code 1 (erwartet 1), 5 Befunde`, `Fehlschlaege: 0`. A
  `Messfehler` from `A2` means one of the four needles is not unique after all — the one
  thing `Grep -c` could not tell me.
- 2026-09-08 (0189, second run), **answered by `uebersetzung-2026-09-08.md`** — the
  rewritten Gegenprobe holds: `:99` `Angabe 1: 2 Meldung(en), Angabe 2: 2, Angabe 3: 1`.
  No zero, no abort, so all three needles bite and none went blunt. The stand is red for
  a different reason — the corpus moved from 36 to 37 between `7ebc1a9` and `d17b26d`,
  and the report says so itself (`:101`). Written-out corpus counts go stale **within one
  day**; that is the same lesson as 0232, one stand over, and it is already in hand: the
  other `0232-riegelkopfzahlen-nach-0225-nachziehen` is `gebaut` and carries the six new
  numbers. No proposal from me needed.
- 2026-09-08 — **My package number collided.** A parallel lane of my own role took
  `0232` the same night (`0232-riegelkopfzahlen-nach-0225-nachziehen`). The `dateien` do
  not intersect — that one holds `messung-0115/messen.py` and `belegstellen_riegel.cpp`,
  mine holds `messung-0180/messen.py` — so nothing collided but the name. The project
  manager renumbers; worth knowing that "choose freely above the highest" collides when
  two lanes read the directory at the same time.
- 2026-09-08 (0189) — **Four probes in `werkzeuge/belegstellen/` build and run copies of
  the same source, and one writes to it.** ctest is serial today (no `-j` in
  `baulauf.py`); the day someone adds `-j`, they collide. `RESOURCE_LOCK` on all four
  would fix it, but three entries belong to 0147, 0166 and 0182 — its own package.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-07 (0166, still open) — **Are there other measurement stands whose mutants attack
  a shared building block that a later table now covers?** `messung-0180` is now clean on
  this point; `messung-0106`, `-0115`, `-0129` remain candidates.

## Where I am unsure

**0232.** Three things, in falling order of what they would cost.

*That the riegel prints its findings in ascending line order.* I model it that way and
sort. Today the two orders coincide (2, 16, 32, 32, 185 is both file order and sort
order), so condition 1 is not at risk — but if the riegel groups by Sorte and only looks
line-ordered because the corpus happens to be arranged that way, my sort would produce a
false red the day someone reorders the head of `werte.hpp`. Deciding it means reading
`zahlwort_riegel.cpp`'s collection loop, which is outside my `dateien`.

*Needle uniqueness, checked with `Grep -c`.* It counts matching lines. Two occurrences of
a 40-character wording on one line is implausible, but I did not measure it.

*Whether the reviewer wants only the fifth entry re-erected.* The package's prose speaks
of "the entry" in the singular; I derived all five. If the literal reading is wanted, the
other four are three lines of hard-coded strings away — but then the same finding comes
back the next time anyone inserts at the top of that file.

