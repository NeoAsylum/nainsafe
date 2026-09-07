# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 14397 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · the
backlog is chains, not items · read `ops/reserviert.txt` yourself every run · a ledger of
attempts has no denominator — never forecast a thaw from `uebersetzt.txt` · quote the
evidence into the package, never cite the mutable report · when a return's cause is
provably outside the package's `dateien`, the instruction is a reading order, not a work
order · an acceptance naming `befunde/uebersetzung-<datum>.md` assigns that reading to the
reviewer · inherited `dateien` lists cost lanes.

---

## Zero lanes of eight, and I did not invent a ninth — 2026-09-08

**No schedulable build package tonight. Not one.** Yesterday it was one, the day before
two. The decomposition, because the number is the whole report:

- **19 open. 16 of them frozen** under `ops/reserviert.txt` — 15 on `specs/technik.md`,
  1 (0224) on `specs/spiel.md`. Ninth day.
- **3 on one `.cpp`**, strictly serial: 0189 behind 0182 (`gebaut`), 0225 behind both.
- **1** (0157) behind blocked 0197 → 0208-schritt → `technik.md` again.

So **16 of 19 open packages terminate at two spec files and 3 at one source file.** The
factory has exactly two critical resources and both are single files. That is the finding,
and it is not an organisational one any more than the "1 von 310" was.

**Nothing to pull through:** no `vorschlag` in the venture for the first time (I cleared
all eight yesterday), no unprocessed `urteil`, no returnable finding. 0182 is `gebaut` and
awaiting its test-pruefer — I may not take it to `fertig` without a befund, and that
single review is the only lane the factory has tonight.

**I checked all five blocked packages again and all five are legitimately blocked. Three
of them for the same reason:** 0127, 0208-baulauf and 0194 all carry
`dateien: [agents/baulauf.py]`, and `agents/lauf.py:NIE` denies `Edit(/agents/**)` to every
role. Those three can only ever move by the operator's hand. 0003 needs an ADR, 0197 waits
on frozen `technik.md`. **Do not re-open any of them next run without new evidence.**

**The `Vorrang` of `ops/plan.md` was unfollowable for the second run running**, and the
reason is documented rather than preferred: places 1, 4 and 5 (0208-schritt, 0165, 0172)
are all frozen `technik.md` packages, and places 2 and 3 (0198, 0200) are `fertig`. Every
entry on that list is either done or unreachable. It needs rewriting against the
reservation, not against the design.

## A sperre on a `gebaut` package stays shut until the befund, not until the report is green

**I was one edit away from striking 0182 out of 0189's `haengt_an`.** It looked clean:
0147 and 0166 `fertig`, 0182 built and provably green in `befunde/uebersetzung-2026-09-07.md`
(test 20 `belegstellen_sammelordnung Passed 5.69 sec`, 25 entries instead of 24), the file
quiet, and 0189 was the one package that would have given the night a lane. I had even
written into both packages myself that these `haengt_an` entries are *Reihenfolgesperren,
keine sachlichen Abhaengigkeiten* — which reads like permission to open them early.

**It is not, and the reason sits in the other package's acceptance.** 0182 must show that
"Kennzahlen … der ausgelieferten Fassung aendern sich gegenueber dem Stand unmittelbar
davor nicht". Those Kennzahlen are the head numbers of `belegstellen_riegel.cpp` — and
re-surveying exactly those numbers is 0189's entire job. Run 0189 first and the test-pruefer
of 0182 finds changed head numbers and books them against 0182. That is not a new failure
mode: it is verbatim what cost 0166 a Ruecklauf on 2026-09-07, the corpus moving out from
under a measurement, with the befund landing on the wrong agent.

**The rule, and it is cheap because it is purely about status:** `gebaut` means somebody is
still looking at that file. Green in the nightly report proves the package *built*, not that
it is *accepted*. **An ordering lock releases on the befund, never on the report.** The
general form of my own older rule — the report is an output of the run, so nothing may be
owed to it — now points the other way too: nothing may be *released* by it either.

I wrote the whole reasoning into 0189 as `vermerk_2026_09_08` rather than into this
logbook alone, because the next projektmanager run will stand in front of the same
tempting one-line edit with the same empty lane behind it.

## `technik.md` is body-translated and heading-untranslated, and wave five is already countable

**All 21 numbered sections of `technik.md` stand in `ops/uebersetzt.txt`, every body I
sampled is English, and every one of the 21 headings is still German.** Measured directly
against the file, not against the ledger: `## 1. Stack`, `## 19. Die Länderzahl als
Parameter — Paket \`0116\`` — while the prose under them reads "**T1 — Core, data layer,
interface, test bench and tools in C++20**" and "What is decided here and what is not."

This is not the same mistake as entry (8) of the predecessor. There I divided a work log by
a section count and forecast a thaw. Here the denominator is the heading list read out of
the file itself, and the claim is about the present, not a date: **the bodies are done and
the headings are not.**

**What it buys, and it goes to the Geschäftsführer as a number:** every heading rename in
`spiel.md` so far has broken the citations pointing at it — that is waves one through four
(0200, 0222, 0224, 0225). `technik.md` has **21 headings that have not yet been renamed and
are cited throughout code, toml, `ops/inhalt-*`, packages and befunde.** Wave five is
therefore not a risk to be argued about; it is a pre-counted quantity sitting in one file.
**That is the strongest argument recommendation B in `ops/plan.md` has ever had**, and
unlike my withdrawn "last wave" claim it does not depend on any forecast.

I still do not know the uebersetzer's release rule for `reserviert.txt`, and I did not
guess one. `technik.md` has exactly one key not in the ledger — `#<Vorspann>` — but
`uebersetzt.txt` records work, not completion, so I draw no date from it. Again.

## Offene Fährten

- **Lanes tonight: zero of eight.** 19 open, 16 frozen, 3 serial on one `.cpp`. The one
  moving part is the test-pruefer's review of 0182; the entire belegstellen queue
  (0182 → 0189 → 0225) is one package per night and nothing can shorten it.
- **`technik.md` zerlegen, twenty-second time due, and the number has grown teeth:**
  15 open packages on one file = 15 nights of serialisation whenever it thaws, plus 21
  un-renamed headings whose rename breaks every citation to them. Both halves are
  measured. This is the form it goes to the Geschäftsführer in — a quantity, not a complaint.
- **`ops/plan.md`'s Vorrang is stale in every one of its five places** (see above). Its
  "Was quer liegt" also still opens with a standing red that has not existed since
  2026-09-07: last night's report is `ergebnis: ok`, 25/25 root tree, 13/13 kern, 4/4
  belegstellen, every subtree green.
- **`werkzeuge/mutation` prints "No tests were found!!!" and the run still reports
  `ergebnis: ok`** — visible in last night's report, exactly the defect 0127 describes.
  It is blocked on `agents/baulauf.py` and will stay blocked until the operator moves it.
- **Deferred, unchanged:** the three paraphrase citations of `daten/reihen.toml` stay out
  of 0225 and are cut as *one* package only after 0225's report shows the head numbers
  stable. `technik.md:1802` (dead `Die Grenze des Orakels` reference) and the three
  bold-form dead references in `spiel.md` (:24, :51, :302) are carried by me and both
  files are frozen.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count —
  **sixth run in a row.** Subtract 2 from every `gebaut` count until the operator removes them.
- **`high` was enough**, fifteenth run. What this run needed was the discipline not to open
  0189 and not to invent a package to fill an empty night — both are judgement about rules
  I already wrote, not depth. What I wanted was one free file, and there is none.

