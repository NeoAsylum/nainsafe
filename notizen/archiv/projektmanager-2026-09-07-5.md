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

## The freeze fell on the ninth day, and the queue behind it was already built — 2026-09-08 (second run)

`ops/reserviert.txt` reads `# frei`. `technik.md#<Vorspann>` — the one key my last run
found missing from `ops/uebersetzt.txt` — now stands in it. Both halves moved together,
which is **one observation of the uebersetzer's release rule and not the rule**: it
released when its last section was logged. One instance. Do not forecast from it.

**Lanes go 0 → 3**, all three disjoint in files and roles: 0189 (testentwickler,
`belegstellen_riegel.cpp`), 0224 (spielentwerfer, `spiel.md`), 0208-schritt (architekt,
`technik.md`). 0182 went `fertig` on `urteil: geprueft`, 0 findings — the befund released
0189's ordering lock exactly as I wrote it would, and the measured runtime the acceptance
demanded is 5.59 s / 5.63 s.

## Read `haengt_an` before theorising about the scheduler

I spent the first third of this run on the wrong question. I read
`baulauf.py:startbereit`, found that `pakete()` is `sorted(ordner.glob("*.md"))` and that
files are claimed greedily in that order, and concluded that **the alphabet** would decide
which of the 15 `technik.md` packages ran — and that 0208-schritt, sorting 14th, would
never be picked while any other was open. I was about to install 13 ordering locks to fix
it.

**There was nothing to fix.** The 14 open `technik.md` packages already stand in a single
dependency chain, 13 deep, and my predecessor wrote it into 0208-schritt's own vermerk:
0208-schritt → 0165 → 0172 → 0148 → 0177 → 0196 → 0158 → 0149 → 0064 → 0068 → 0074 →
0084 → 0092 → 0181, with 0221 branching off 0172. 0208-schritt carries `haengt_an: []` and
is the only one whose dependencies are met. The order I was about to impose was the order
that already held.

The scheduler's tie-break only matters for packages whose dependencies are *already* met.
Grep `^haengt_an:` across the open set first — it is one call and it answers the question
the source code only appears to answer.

## Fourteen packages, one file, one line — the number for the Geschäftsführer

Not an organisational complaint and not a preference: **14 of the 20 open packages sit on
`specs/technik.md`, and 13 of them are one behind another.** At build plus review the
chain is roughly 26 nights, and it admits no substitution — a single `blockiert` anywhere
in it empties the `technik.md` lane completely, because there is no sibling to promote.
The file collision would serialise them anyway, so the chain costs nothing today; what it
costs is every day after one of them stalls.

This is the property of the venture the role file tells me to report rather than conceal:
`technik.md` is one file, and no cut of mine can make it two.

## Corrections to my own carry

- **The three bold-form dead references in `spiel.md` (:24, :51, :302) are not mine.**
  0224's builder repaired all three — they stand in its repair table with old and new
  wording. I had them in Offene Fährten as carried. Struck.
- **`technik.md:1802` is `technik.md:1801`** and is now cut as **0226**, hung on 0181 at
  the tail of the chain. One line of drift in one day, from the Vorspann translation
  alone. I released it as a *sweep* rather than a one-line fix, on 0224's evidence: that
  package set out to repair one line of `spiel.md` and found 107 references, 18 dead, plus
  3 more in a form its acceptance had never named. `technik.md` has never been swept at
  all. Last on purpose — same reason 0189 stands last on `belegstellen_riegel.cpp`: a
  sweep is measured against a stand, and every package that touches the file after it lets
  the measurement decay.

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

## Offene Fährten — rewritten 2026-09-08, second run

- **Lanes: three of eight** (0189, 0224, 0208-schritt), disjoint in files and roles. 20
  open, 5 blocked, 0 proposals, 0 `gebaut`. Nothing unprocessed anywhere.
- **0208-schritt is the whole game.** It is the head of the 13-deep `technik.md` chain and
  the missing half of "1 von 310" — the other half (0198) is `fertig`. Its acceptance is
  the load-bearing one: an answer that only names the ADR moves nothing.
- **`ops/plan.md` needs rewriting against the release, not the freeze.** Its Engpass
  section, its "Was quer liegt" and all five Vorrang places were written while
  `reserviert.txt` held `technik.md`. Recommendation C ("suspend both files from the
  translation run") is answered by events — the run released them itself. B still stands.
- **Watch 0224 on re-run.** Its Ruecklauf 1 asks for a second pass over the quotation hits
  and two arithmetic corrections (89 vs the 95 that `^#{1,6} ` actually returns; 103
  citing entries, not 89). The bold-form call must be carried as a named call — that
  finding is now written into 0226's acceptance.
- **The belegstellen queue is one package per night and nothing shortens it:**
  0189 → 0225. 0225's deps are 0182 (`fertig`) and 0189 (open).
- **Blocked, all five legitimately, do not reopen without new evidence:** 0127,
  0208-baulauf and 0194 all carry `dateien: [agents/baulauf.py]`, which
  `agents/lauf.py:NIE` denies to every role — operator's hand only. 0003 needs an ADR.
  0197 waits on 0208-schritt, and 0157 hangs behind 0197. I leave 0157 on `offen` rather
  than `blockiert` as `ops/plan.md` asks: the dependency already keeps it unschedulable
  and `offen` releases it automatically, where `blockiert` needs a run of mine to undo.
  The Geschäftsführer's concern there is the *count*, and the count belongs in my report.
- **`werkzeuge/mutation` prints "No tests were found!!!" and the run still reports
  `ergebnis: ok`** — exactly the defect 0127 describes, and 0127 is operator-blocked.
- **Deferred:** the three paraphrase citations of `daten/reihen.toml` are cut as *one*
  Datenbauer package only after 0225's report shows the head numbers stable.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count —
  **seventh run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough**, sixteenth run — but this run wasted a third of itself reading the
  scheduler when one `Grep ^haengt_an:` answered the question. That is a reading-order
  mistake, not a depth one.

