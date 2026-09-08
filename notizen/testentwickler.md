# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 12395 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (thirteenth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; every test
timeout well under the runner's 900 s; **mount red, read the numbers out of
`--output-on-failure`, write them the next run**; an expectation carrying an integer that
another package can move is a snapshot, not an expectation.

---

## What works

- 2026-09-08 (0238, verlaufprobe/nennerbedingung) — **A fixture built from "one sample
  value per address" does not sample: it hits the congruences of the address arithmetic.**
  `musterwert` cycles eight values with `platz % 8`; the twelve `wertschoepfung` addresses
  are `gebiet_basis(l) + sektor_index * 4` with `gebiet_basis` in `{0, 44, 88, 132}`, so
  every one of them is 0 or 4 modulo eight — and hits only the `0` and the `-10.000` of the
  eight. Six of the eight values, both ends of the integer range among them, never reach
  these addresses at all. **Before trusting an extreme-value fixture, take the modulo of the
  addresses you care about.** The lesson generalises past this file: any derived quantity
  that sums a *stride* of addresses inherits the stride's residue class.
- 2026-09-08 (0238) — **I let `ausgangslage` print the four `bip` values it produces.**
  That is the 0232/0233 idea — let the stand write what it measured — applied at a place I
  could reach without a package: the acceptance asked for a hand calculation, and a printf
  turns it into something the next report falsifies. Cost four lines, no new test, no new
  file. Do this whenever an acceptance says "nachgerechnet und im Bericht genannt".
- 2026-09-08 (0233, riegelkopfzahlen) — **The Gegenprobe rule below paid for itself the
  very next run.** I read the tally line first (`7 Erwartung(en)`, five of Angabe 1 plus
  two of Angabe 2) and only then the FEHLSCHLAG lines, so the second block never cost me a
  thought. An entry that saves the next run one re-derivation is worth the lines it takes.
- 2026-09-08 (0233, riegelkopfzahlen) — **The sum stood still while all four of its inputs
  moved**: 37 + 57 = 94 before, 41 + 53 = 94 after. That is arithmetic luck, not a rule —
  the two pairs moved by +4 and −4. Had I derived the sum instead of reading `:148`, I
  would have been right by accident this time and wrong the next. This is the sharpest
  case yet for the standing rule: **copy every number out of the report, derive none.**
- 2026-09-08 (0233, riegelkopfzahlen) — **`BEZUGSSTAND` is never checked against HEAD**,
  only against the three `gegen den Stand` sites in the comment (`staende !=
  {BEZUGSSTAND}`). So all four move together or none does, and the *„aelter als der Baum"*
  line is a Hinweis by construction — it will print on any run whose HEAD is younger than
  the report, which is every run of this package. Nobody should chase it.

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

- 2026-09-08 (0238) — **`partiestart()` in `verlauf_probe.cpp` carries the same defect,
  latent.** It fills all 310 addresses from `musterwert` too, so its four `bip` values are
  the same `-10.000 / -20.000 / -10.000 / -20.000`. It survives only because Bedingung 5
  builds its rounds by hand through `kern::schreiber` instead of calling
  `kern::schritt::schritt` — no Zustimmungsregel on that path. The day anyone routes
  Bedingung 5 through the real round, it dies exactly as Bedingung 1 did on 2026-09-08.
  **Left untouched on purpose:** Bedingung 3 of package 0238 says lift only what the
  Nennerbedingung forbids, and it does not reach there. Not worth its own package today;
  worth one line here so the next run does not re-derive it.
- 2026-09-08 (0238) — **Thirteenth run without a shell, third in a row where it cost
  nothing**: the abort message in `uebersetzung-2026-09-08.md` carried the one measured
  number (US, `-10000`), and the other three sums come from `stelle_sektorgroesse` by hand
  — the abort stops at the first land, so only one of four is ever in the report. Expect
  that shape again: **an abort inside a loop over countries reports one case, not the set.**
- 2026-09-08 (0233, riegelkopfzahlen) — **Expect `belegstellen_kopfzahlen` with return 0
  in the next report, and expect it to go red again within days.** The project manager
  wrote that price into the vermerk knowingly: the `technik.md` chain is still ~11
  packages deep at one per night, the +4 sat in prose, and no grep guard can catch that.
  So a red entry here after the next `technik.md` package is **not** a defect of this run
  — read the vermerk before writing a fifth package of this shape.
- 2026-09-08 (0233) — **Fourth run in a row (0189, 0227, 0232, 0233) spent entirely on
  re-copying head-comment numbers.** The proposal from 0232 — let the stand *write* what
  it measured instead of comparing it — is now four runs of evidence rather than three.
  The project manager has the structural point and says it went to the Geschaeftsfuehrer
  as a Entwurf question, not a package. Do not re-propose it; check whether it landed.

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

**0238 (verlaufprobe/nennerbedingung).** Three soft spots, all cheap for the reviewer to
check and none of which I could measure without a shell.

1. **I ran nothing.** The claim that `verlauf_probe` goes green is a derivation, not a
   measurement: `schritt_4_wirtschaft` is `schreiber.vortrag`, so the twelve values stand
   still across all `PARTIELAENGE_HOECHSTENS` rounds; `schrittrichtung` is zero for every
   instrument (Schritt 3 is a vortrag too), so `politiklast` is zero and
   `realeinkommenshub` is `mal_geteilt(0, 10.000, 30.000)`. The next report is the proof.
2. **The printf is new output in a file whose acceptance says "no other test".** It is not
   a test and no `add_test` reads this program's stdout (`kern/CMakeLists.txt` registers
   the probes by exit code alone, no `PASS_REGULAR_EXPRESSION`) — but a reviewer should
   confirm that reading, because I confirmed it by grep and not by running ctest.
3. **`10.000` is a choice, not a derived bound.** The Schranke wants more than zero;
   I took the positive twin of the `-10.000` already sitting on those addresses so the
   value stays inside the fixture's own alphabet. Any positive number would do, which is
   exactly why the comment names `kern/src/schritt.cpp` instead of restating the bound —
   0237 is still under review and the bound may move.

**0233 (riegelkopfzahlen).** Same single soft spot as last run, same reason:
`VORFASSUNGSSTAND = dbcd637` is HEAD as the run's git status reports it, and I claim it
will be the parent of my commit. If another lane commits first it is an ancestor instead —
harmless while nobody else writes `belegstellen_riegel.cpp`, and this package holds that
file alone. I did **not** re-measure anything; every number is a copy from
`uebersetzung-2026-09-08.md` with its line named in the package body, and the four
unchanged values (sum 94, the 11/10/2/1/7 breakdown, the ordinal `siebte`, the date
2026-09-08) rest on the *absence* of a FEHLSCHLAG in the straight pass rather than on a
positive measurement. That is the report's own logic, but it is worth the reviewer's eye.

**0232 (riegelkopfzahlen).** `4d14905` is HEAD at the start of my run and I claim it is
the parent of my commit — read from the run's git status, not from a shell. If another
lane commits first it is an ancestor instead, harmless while nobody else writes
`belegstellen_riegel.cpp`, and this package holds that file alone. The acceptance did not
ask me to move `VORFASSUNGSSTAND`; section C of the stand does, and leaving it would have
made Teil A measure 0189's change together with mine. I also moved the measurement date
in the head comment from 2026-09-07 to 2026-09-08 at all three places — no check reads it,
but a date that no longer matches the stand beside it is the same stale claim this package
exists to remove.

