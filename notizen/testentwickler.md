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

- 2026-09-07 (0166, Beleglauf) — **The number I could not measure came back green, and the
  cheap thing that made that legible was the return-code split.** `belegstellen_wortabstand`
  stood at `5 Abweichung(en)` in the Rücklauf and reads `Passed 17.22 sec` today. Because
  1 and 2 are separate, the green is a real statement: had a needle gone blunt after 0222
  touched `belegstellen_riegel.cpp:39`, the stand would have said 2, and a 2 is not a green.
  **The general rule: a stand whose failure modes are one code cannot be believed when it
  passes.** The whole diagnosis of this Rücklauf — "the numbers were right, the corpus moved
  under them" — was only checkable because the instrument could say which of the two it was.
- 2026-09-07 (0166, Beleglauf) — **A standing red proof inside the program is worth more
  than a red run in a report, because it re-proves itself nightly.** Teil 3 runs the same
  comparison against the reverse-substituted pre-0166 head and counts a Befund if it finds
  nothing. Return 0 therefore *contains* the red proof: I never had to run anything to show
  the check can fail. Compare the Rücklauf's red — that was corpus drift, not a built proof,
  and it is worth naming the difference rather than banking the accident as evidence.
- 2026-09-07 (0166, Beleglauf) — **The nightly report prints no output for a passing test.**
  So the riegel's base numbers (Zitate/aufgeloest/uebergangen) are unobtainable from a green
  report — only a red one shows them. That is a second, independent reason the head carries
  differences and not base numbers: even with the report in hand I could not have written a
  base number without inventing it. Worth remembering before promising anyone a figure that
  only exists inside a passing test's stdout.
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

- 2026-09-07 (0222) — **The riegel's own head citation is the cheapest possible red proof,
  and it worked exactly once as designed.** The head cites `technik.md` on purpose ("wer
  den Wortlaut hier oder dort aendert, macht den Riegel rot"). The uebersetzer changed the
  wording there; the riegel went red at its own line 39. No mutant, no stand, no shell —
  the nightly report was the measurement. **The general rule: a checker that cites the
  thing it checks needs no separate red proof for that path.**
- 2026-09-07 (0222) — **The report's three numbers locate the sites without running
  anything.** 40 Zitate / 36 aufgeloest said "four dead", and exactly four turned up:
  three quotes of the T49 Absatz (`belegstellen_riegel.cpp:39`, `daten/adressen.md:29`,
  `:556`) and one of the T46 table heading (`daten/adressen.md:540`). **The count is the
  stopping criterion** — without it I could not have told a complete sweep from a partial
  one, because the corpus has no other way to enumerate its own citations.
- 2026-09-07 (0222) — **The cheap way to find them: never grep the corpus for keywords,
  grep it for the two target file names.** `Abschnitt|Absatz|Ueberschrift` over the
  venture gives 11,120 hits in 1,641 files. `technik\.md|spiel\.md` restricted to `kern/`,
  `pruefstand/`, `werkzeuge/`, `daten/`, `parameter.toml` gives about 150 lines, and only
  a translated document can have broken a citation. Then `(Abschnitt|Absatz|Ueberschrift)
  \s+(\\?["„»"'`*])` per directory for the quote form, plus the same keyword anchored at
  `$` for the quote that sits on the next line. Both passes are needed: two of the four
  sites had the quote on the following line.
- 2026-09-07 (0222) — **`ops/inhalt-<venture>.md` answers "is this heading still there"
  for `##` headings and lies about everything below.** The uebersetzer keeps the numbered
  `##` titles German ("5. Die drei Zustandsebenen (G8)" is listed as translated and is
  still German) and translates the bold lead-ins underneath — and the bold lead-in is
  exactly what the riegel accepts as a heading. So the index is the wrong instrument
  here; `Grep` on the quoted wording in the target file is the right one.

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

- 2026-09-07 (0166, Beleglauf) — **Eighth run in a row with no shell** — but for the first
  time that cost nothing, because the run's job was to read a measurement the runner had
  already taken. **A Beleglauf is the shape of run a shell-less agent is actually good at.**
- 2026-09-07 (0222) — **Seventh run in a row with no shell.** Nothing compiled, nothing
  run. Everything below rests on reading; the proof is the next
  `befunde/uebersetzung-<datum>.md`.
- 2026-09-07 (0222) — **A citation repair cannot be verified by the repairer.** I can show
  that each new wording exists in the target file today, and that the riegel's
  normalisation (umlauts, em dash, bold markers, trailing period) maps both sides onto the
  same string. I cannot show that no *fifth* citation broke between the report's tree
  (82fa870, §5–§8) and mine (§9, §10, §11 translated since). The count 40/36 covers the
  first three sections only.

## Open leads

- ~~2026-09-07 (0166) — the six differences in the head, unmeasured.~~ **Closed
  2026-09-07: `Passed 17.22 s` / `17.23 s`, both build paths.** Neither branch of the
  guess was needed — not 1 (no difference wrong) and not 2 (no blunt needle, though 0222
  moved `belegstellen_riegel.cpp:39` between the two runs). The two head blocks I typed
  twice and could not diff were correct.
- ~~2026-09-07 (0222) — does `belegstellen_riegel` come back with `Zitate == aufgeloest`?~~
  **Closed 2026-09-07: `Test #17 belegstellen_riegel ... Passed 1.02 sec`.** No fifth
  citation broke in §9–§11. The four sites were the whole set.
- 2026-09-07 (0166) — **Are there other measurement stands whose mutants attack a shared
  building block that a later table now covers?** `messung-0180` is the known case;
  `messung-0106`, `-0115`, `-0129` are candidates. No proposal on a hunch — but whoever
  next touches one of them should run its needles before believing its numbers.
- 2026-09-07 (0222) — **Fourth wave of the same breakage** (0200, 0214, this one). Each
  translated section can kill citations elsewhere, and each wave costs a package. The
  operator's decision on whether citation-nachzug belongs in the uebersetzer's own loop is
  open in `ops/plan.md` (recommendation B); the project manager is carrying the count to
  the Geschaeftsfuehrer. Nothing for me to do but note that the count is now four.
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

*Third, the runtime.* ~~Derived, not measured.~~ **Measured 2026-09-07: 17,22 s / 17,23 s.**
The estimate "roughly 17 s" was right to two significant figures, and the reasoning behind
it — eleven versions at 30,7 s, mine compiles four distinct ones of the six — is therefore
worth reusing for the next stand. I left the `TIMEOUT 240` alone at factor 14: a cap that
tears on a load spike costs more than the wait it saves. Whoever wants it tighter now has
the figure.

**0166, Beleglauf 2026-09-07.** One thing, and it is a gap in what I can *show*, not a
doubt about the result. The report prints no stdout for a passing test, so I cannot quote
the riegel's base numbers from it — only that all three entries passed. Everything I claim
about *why* the stand is green (Teil 3's red proof fired, the needles still hit) is
inferred from the return code being 0 rather than 1 or 2, which is exactly what the
three-way split was built for, but it is inference from one number and not a printed trace.
If the reviewer wants the trace, it takes a deliberately red run.

**0222.** Two things.

*First, `daten/reihen.toml`, Reihe 17.* I updated the wording and deliberately did **not**
give it a Schluesselwort. As it stands ("die spiel.md unter 'And the limit of the oracle,
explicitly' aufzaehlt") it is not one of the 40 and never was; adding "Abschnitt" would
make it counted and would move the base number the riegel prints, which 0166's Messstand
and its reviewer read. Repairing a citation and changing what is measured are two
different packages. The project manager may disagree — it is one word.

*Second, the ABSTANDSFAELLE fixture, Fall 1.* Its `herkunft` names `daten/adressen.md` and
its literal still carries the German T46 heading, which the corpus no longer has. I left
it alone: the fixture measures the five-word distance and the right-hand name, not the
corpus; its keyword is masked, so the riegel never reads it as a citation; and
`messung-0166/messen.py` substitutes that exact line as `FALL1_ALT`. Touching it would
blunt a live needle to tidy a comment.

