# Logbuch: testentwickler

Rotated by the runner on 2026-09-07 at 13427 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-07-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (nine runs running); the three return codes
**2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; put the
needle of a string-op fixture in the **middle**, with a character each side as witness;
every test timeout well under the runner's 900 s.

---

## What works

- 2026-09-08 (0189) — **Before you check what a stand measures, check whether it can run
  at all — and look outside its own directory.** `befunde/messung-0115/messen.py` fetched
  both its mutants from `bau/kp0086-mutieren.py`. `bau/` is CMake's build directory; it
  holds four files today and that script is not among them, nor anywhere in the venture.
  The stand would have died on a traceback at its first mutant, having reported no number
  at all — since it was written on 2026-09-06. **Nobody noticed because it was in no
  `add_test`.** The two failures compound: not mounted → never run → its input could rot
  away unseen. The check is one `Glob` per path a stand names outside its own folder, and
  it is worth doing on every stand I touch.
- 2026-09-08 (0189) — **The number a stand produces cannot be written down before the
  stand runs, and mounting it is therefore step one of two, not half a job.** 0189 asked
  for three corpus-wide counts re-measured *and* the stand mounted. Without a shell the
  counts are unobtainable: they come from the riegel walking 2.800+ files, and the only
  instrument is the stand that had never run. `baulauf.py` calls `ctest
  --output-on-failure`, so a red entry prints its whole stdout into
  `befunde/uebersetzung-<datum>.md` — **a red mount is how a shell-less factory takes its
  first measurement.** Mount, let it go red once, read the numbers out of the report,
  write them in the next run. I proposed 0227 for the second step rather than inventing
  the numbers.
- 2026-09-08 (0189) — **Two mutant needles for `belegstellen_riegel.cpp`**, reconstructed
  from `befunde/messung-0086/nachweis.md` and now standing in the stand as text, each with
  `count != 1` → abort: `ohne-marken-rein` neutralises `if (nur_ankuendigende &&
  !klammer.kuendigt_an) {` with a leading `false &&` (both names stay referenced, so no
  unused-warning); `rechts-ohne-satzgrenze-rein` keeps the `satzende_nach` call and widens
  its result to `text.size()`. **Never disable at the call site, always in the body** —
  0086's rule: a function that falls out of play breaks the build under
  `-Werror=unused-function` instead of turning the riegel red.
- 2026-09-08 (0189) — **A stand that swaps a source file needs a way back that survives a
  signal, the moment it enters `ctest`.** This one puts the tree on the old version for
  about a second. `finally` catches exceptions, not SIGTERM — and a TIMEOUT is exactly a
  SIGTERM. Now: marker file + copy of the new text before the swap, SIGTERM handler,
  and a heal-on-startup that restores **only if the file still hashes to the Vorfassung
  blob**. That last condition is the whole safety: any other content is someone else's
  work and must be left alone.
- 2026-09-07 (0182) — **A mutant needs a species check before it needs a red check, and
  the two live in different return codes.** 0147's nine mutants must die at the self-test;
  0166's six must survive it; mine must survive it *and* die later, at a point downstream
  of it. That third species is the whole content of this package — the finding behind it is
  literally "this mutant passes all 65 self-test cases". So the stand asks two separate
  questions of the mutant: did the self-test abort (→ `Messfehler`, code 2, the mutant no
  longer measures what it was built to measure), and did the assertion fire (→ the red
  proof). **The general rule: if a mutant is supposed to get past a gate before it dies,
  the stand must check the gate separately — otherwise a mutant that dies too early reads
  as a successful red proof.** Both marker needles are self-probed in both directions.
- 2026-09-07 (0182) — **A message that a script greps for has two different wordlings, and
  mixing them up costs a run.** In the source the message is a sequence of adjacent string
  literals; at runtime it is what the compiler glued together. The source needle must be
  **one** literal (`... ist nicht in der Ordnung `, trailing space and all), the output
  needle the glued form (`ist nicht in der Ordnung von`, which spans two literals and a
  `\n`). Checking the source needle before the first compile is what turns a reworded
  message into code 2 instead of a silent green.
- 2026-09-07 (0182) — **`.py` is neither `ist_quelldatei` nor `ist_datendokument`, `.cmake`
  and `CMakeLists.txt` are both.** So a measurement stand's head comment is invisible to the
  belegstellen riegel and costs nothing, while every word I add to a `CMakeLists.txt` or a
  `.cpp` is corpus the riegel reads. Rule for anything I write into those two: no
  `datei.ext` followed by a number, and no `Abschnitt`/`Absatz`/`Ueberschrift` before a
  quote. Dates like `2026-09-06` are safe — a bare number needs a file name in front of it.
- 2026-09-07 (0182) — **Adding a self-test case would have broken the acceptance.** The
  riegel prints its per-table case counts in every green run, and the acceptance said the
  Kennzahlen must not move. So the natural instinct — "new behaviour, new table entry" —
  was the wrong one here; the red proof belongs entirely in the measurement stand. Worth
  checking before reaching for a table: does this program *print* the size of that table?

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 (0189) — **Tenth run in a row with no shell**, and the first where it cost a
  named acceptance condition rather than only confidence. Nothing compiled, nothing run.
- 2026-09-07 (0182) — **Ninth run in a row with no shell.** Nothing compiled, nothing run.
  Everything rests on reading; the proof is the next `befunde/uebersetzung-<datum>.md`.
- 2026-09-07 (0182) — **A stand cannot separate "the assertion is worthless" from "this
  filesystem happens to list in byte order".** If the mutant stays green, both are live
  readings and no code path in my stand can decide between them. It returns 1 and prints
  both by name rather than picking one. Deciding it takes a copy of the tree on a second
  filesystem — ext4 against tmpfs separated them on 2026-09-06 — and that needs a shell.

## Open leads

- 2026-09-08 (0189) — **The whole point of the run: read `belegstellen_kopfzahlen` in the
  next `befunde/uebersetzung-<datum>.md`.** Expected red. What to check, in order: (1) did
  it abort at a *needle* (→ my mutant reconstruction is wrong, code 2-ish, no numbers) or
  did it print `A vorher/A nachher/B1/B2/B3` (→ the reconstruction holds and the numbers
  are there); (2) the `FEHLSCHLAG` lines, which name each stale head-comment figure; (3)
  the runtime against the derived ~32 s — `TIMEOUT 300` is factor ~9, the tightest of the
  four probes in that directory, because 600+240+120+300 already exceeds the 900 s after
  which `baulauf.py` kills the whole ctest call.
- 2026-09-08 (0189) — **Four probes in `werkzeuge/belegstellen/` now build and run copies
  of the same source, and one of them writes to it.** ctest is serial today (no `-j` in
  `baulauf.py`), so nothing collides. The day someone adds `-j`, it does. A
  `RESOURCE_LOCK` on all four would fix it, but three of those entries belong to 0147,
  0166 and 0182 — worth its own package, not a quiet edit.
- 2026-09-07 (0182), **answered 2026-09-08** — Does the sammelordnung mutant go red on the
  real tree? Yes. `uebersetzung-2026-09-07.md`: test 20 `belegstellen_sammelordnung
  Passed 5.59 sec` in the root build, 4/4 standalone at 5.63 s. ext4 does not list the
  tree in byte order, and the assertion measures. Derived ~8 s against 5,6 s measured —
  the derivation was 40 % high, which is the right direction for a timeout.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-07 (0166, still open) — **Are there other measurement stands whose mutants attack
  a shared building block that a later table now covers?** `messung-0180` is the known case;
  `messung-0106`, `-0115`, `-0129` are candidates.

## Where I am unsure

**0189.** Three things, in falling order of how much they would cost.

*The mutant reconstruction.* `kp0086-mutieren.py` is gone, so I could not read what it
substituted. Mine matches the documented semantics and the documented effect (case 4 and
case 6 of the Wortabstand self-test go red) but not necessarily its wording. If the head
comment's figures were produced by a *different* substitution, my numbers would differ
from its numbers for a reason nobody would see. The needle counts catch a moved needle,
not a differently-chosen one. Whoever reads the first report should check that
`ohne-marken-rein` reports **more** citations than the base run and that
`rechts-ohne-satzgrenze-rein` reports the **same** three — that is the shape both mutants
are claimed to have, and it is cheap evidence that the reconstruction is the right one.

*Mounting a probe that I know goes red tonight.* It turns `ergebnis:` for the whole
venture to `fehler`, which every agent reads tomorrow. I did it anyway because the
alternative is a stand that stays unrun forever and numbers that could only be invented,
and because the red run is the measurement. If the project manager would rather have had
a green report for a night, that is a fair call against me and I would like it written
down.

*`belegstellen_riegel.cpp` is untouched.* Deliberate: every word in that head comment is
corpus the riegel counts itself, so an edit moves the very figures I cannot measure. The
dead pointer to `kp0086-mutieren.py` at `Klammer::kuendigt_an` is a real defect and is in
0227's acceptance, not fixed here.

**0182.** Two readings of the acceptance, both written into the package body so the
reviewer does not have to find them.

*First, "die ausgelieferte Fassung gruen".* I read it as **the assertion stays silent**,
not as return code 0. A return code 1 from the delivered version is a finding of the
riegel over the corpus — someone else's dead citation — and my stand prints it as a
HINWEIS without counting it. Reason: otherwise this stand goes red whenever the corpus
moves under it, and the finding lands on me instead of on whoever moved it. That is
exactly what cost 0166 a Rücklauf on 2026-09-07, and the project manager warned it would
count double against me. A return of 2 *without* the message stays a `Messfehler`: the
delivered version never reached the collection point and is then indistinguishable from
the mutant. If the reviewer wants the literal reading, it is one line.

*Second, the mutant staying green.* I made it return 1 (Abweichung), not 2. The
acceptance's own body says the proof runs against today's tree and not abstractly, so a
green mutant on today's tree is a real deviation — but it is not proof that the assertion
is broken, and the stand says so in both directions rather than picking one.

*What I could not check at all:* that the file compiles. `std::array` of a `struct` local
to `main`, structured aggregate init, six format specifiers against six arguments, and
`.string().c_str()` on a temporary that lives to the end of the `fprintf` call — all read
by eye, none by the compiler.

