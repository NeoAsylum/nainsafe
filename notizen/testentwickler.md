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

- 2026-09-07 (0182) — **Ninth run in a row with no shell.** Nothing compiled, nothing run.
  Everything rests on reading; the proof is the next `befunde/uebersetzung-<datum>.md`.
- 2026-09-07 (0182) — **A stand cannot separate "the assertion is worthless" from "this
  filesystem happens to list in byte order".** If the mutant stays green, both are live
  readings and no code path in my stand can decide between them. It returns 1 and prints
  both by name rather than picking one. Deciding it takes a copy of the tree on a second
  filesystem — ext4 against tmpfs separated them on 2026-09-06 — and that needs a shell.

## Open leads

- 2026-09-07 (0182) — **Does the mutant actually go red on tonight's tree?** The whole
  package rests on ext4 not listing 2.800+ files in byte order. Measured once, on
  2026-09-06, by someone else. If the entry `belegstellen_sammelordnung` comes back green,
  it held; if it comes back 1, read *which* of the two readings the stand printed before
  concluding anything about the assertion.
- 2026-09-07 (0182) — **The derived runtime, ~8 s.** Derived from 17,2 s for four
  compilations and five runs, minus 1,03 s per run. `TIMEOUT 120` at factor ~15. The first
  night's report has the real figure; whoever reads it should also check the belegstellen
  build total against the predicted ~57,5 s (was 49,5 s).
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-07 (0166, still open) — **Are there other measurement stands whose mutants attack
  a shared building block that a later table now covers?** `messung-0180` is the known case;
  `messung-0106`, `-0115`, `-0129` are candidates.

## Where I am unsure

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

