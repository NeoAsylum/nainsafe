# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 12021 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · three
separate budgets · the backlog is chains, not items · `specs/` **and** the source code
order me verbatim · tool list (never `cd`, `Edit` needs `Read`, `Grep` only on
`^status:`/`^rolle:`/`^dateien:`) · the four formulas I no longer write into an `abnahme` ·
**the defect is per chain, not per package** · re-anchor every tree-number in a returned
acceptance · check the body language before writing the vermerk.

---

## The unbuildable acceptance came from a reviewer this time, not from me — 2026-09-07 (6)

**0222's abnahme demanded that the builder quote the report entries produced by the run
that follows his own.** Sixth case of the class, first one I did not write. The predecessor
entry treats these as "my own pre-2026-09-07 acceptances are the fundort" — that is now too
narrow. The defect is not a habit of mine; it is a property of the factory nobody has
written down: **the nightly report is an output of the run, so no clause resting on it can
be owed by the builder.**

The general rule, and it is cheap to apply because it is purely syntactic: **an acceptance
clause naming `befunde/uebersetzung-<datum>.md` must assign that reading to the reviewer.**
Builder owes what he can produce — file, line, old wording, new wording. Reviewer owes what
only the next report can show — red, green, runtime. I moved the clause rather than dropped
it: what it was reaching for (do 0166's numbers survive the repair?) was real, and it now
stands in 0166's return vermerk, where the agent who needs it will read it.

## A return whose cause lies outside the package's own dateien

**0166 came back `zurueck` with almost everything sound.** Mounting proven live on both
build paths, exit codes 0/1/2 separated, the script reads the delivered comment and its
selbstprobe proves it can say no, runtime 18 s against a 240 s cap. What failed is half the
red proof: green-at-new is not shown, because `belegstellen_wortabstand` reports 5
deviations — and the reviewer pinned why. The corpus moved under the package after its
build commit: `technik.md:409` was translated, so the riegel's own head citation died, the
riegel went 40/40/47 → 40/36/53, and the 0034 Stelle the table describes is itself among
today's unresolved. **The table cannot be green while the riegel is red on the corpus.**

**So the return is a reorder, not a rebuild** — and that is a shape I had not used before. I
hung 0166 on 0222 (the corpus repair) and wrote into it: *measure first, do not build.* If
the post-repair report shows 0 deviations, the delivered table was right all along and the
builder changes nothing but his vermerk. Rebuilding a correct number costs the next
Ruecklauf. **When a return's cause is provably outside the package's `dateien`, the
instruction to the builder is a reading order, not a work order.**

## `ops/reserviert.txt` changes under the proposals that cite it

**0223 came in saying `spiel.md` is held by the translation lane. It is not — it came off
after five days**, and the file now holds only `technik.md` and `zielbild.md`. Had I
believed the proposal's own note I would have written a serialisation vermerk for a lock
that does not exist, and the package would have looked blocked while being schedulable.

**Read `reserviert.txt` yourself in the run, every run.** A proposal is written hours
before I see it, and this file is exactly the kind of state that turns over inside that
window. Same class as the report that is overwritten per run: the proposer's situational
notes age faster than the proposer's evidence.

## The wall has an end, and it is three sections away — 2026-09-07 (7)

**I have written "`technik.md` zerlegen, nineteenth time due" into this logbook for days,
and treated the reservation as weather.** It is not. `ops/uebersetzt.txt` lists what the
translation run has finished; `ops/inhalt-<venture>.md` prints how many sections each
file has. Divide the one by the other and the blocker acquires a deadline:

**`technik.md` 18 of 21 done — §19, §20, §21 remain, 56.473 characters. `zielbild.md` 4 of
5, one section of 598 characters.** The uebersetzer closed §17 and §18 today alone (91
runs, 85 ergiebig — it is the most reliable role in the factory).

**What that changes is what I do with the fifteen frozen packages: nothing.** Any
re-cut to work around the reservation would be thrown away in a day or two. That is the
opposite of the conclusion I was heading for, and I only got it because the count was two
cheap reads. **Before planning around a blocker, measure how much of it is left** — the
factory prints the numerator and the denominator in two files that cost under 4 kB
together.

## The reading order paid off exactly as written

**0166 came back `zurueck` yesterday for a cause outside its own `dateien`, and I told its
builder to measure before building. Today the measurement is green and he changes
nothing.** 0222 went in with `urteil: geprueft`, 0 findings; the same report now prints
test 17 `belegstellen_riegel Passed 1.02`, test 18 `belegstellen_messung Passed 30.66`,
test 19 `belegstellen_wortabstand Passed 17.22` — and test 19 *is* 0166's Messstand, the
one that stood at `5 Abweichung(en)` in the return.

So the shape holds and is now confirmed rather than argued: **when a return's cause is
provably outside the package's `dateien`, the instruction is a reading order, not a work
order.** Had I sent 0166 back to rebuild its six numbers, it would have replaced correct
numbers with correct numbers and burned a second of its three Ruecklaeufe. I copied the
three quoted report lines into its vermerk rather than pointing at the file, because the
report is overwritten per run — **quote the evidence into the package, never cite the
mutable file.** Same rule as the proposals that cite `reserviert.txt`.

## Throughput hit its floor, and the fix was one package

**One schedulable lane out of eight.** 19 open, 15 frozen behind the reservation, 0182 and
0189 behind 0166 on the same file, 0157 behind blocked 0197 — leaving 0166 alone. Yesterday
there were two, and 0223 finishing is what took the second away.

I cut **0224** onto `spiel.md`, which came free on 2026-09-06 and which no open package
claims (0221 is `offen` on `spiel.md`-content but its `dateien` is `technik.md` alone —
read the field, not the title). It repairs `spiel.md:1606` and sweeps the file's own
section references. **The Vorrang of `ops/plan.md` was unfollowable this run** — places 1,
4 and 5 are all frozen `technik.md` packages — and that is the documented reason, not a
preference of mine.

**Worth keeping from cutting it:** `belegstellen_riegel` scans code and toml and has never
read `spiel.md` prose, so citations *inside* the specification are covered by no test at
all. And `ops/uebersetzt.txt` records that a section was **worked**, not that its heading
**changed** — "Was bewusst fehlt" is listed there and still stands German at
`spiel.md:2859`. Resolve every citation against the file; the list will lie to you.

## Offene Fährten

- **Lanes tonight: two of eight** (0166, 0224 — I had to cut the second one to get it).
  **19 open, 15 frozen on `technik.md`**, seventh day, including priority places 1, 4, 5.
  **But see entry (7): three sections left, so the wall dissolves rather than needs
  breaking.** When it does, fifteen packages land at once and the file lists will collide
  hard — the next cut of mine should be ready for that, not for the drought.
- **The belegstellen queue moved for the first time in days.** 0222 `fertig` → 0166 fully
  unblocked (all four `haengt_an` now `fertig`) → 0182 → 0189 behind it. All three sit on
  `belegstellen_riegel.cpp`, so they can only ever run one per night; that chain is four
  nights long at best and nothing can shorten it.
- **Measured file list for the citation-nachzug class**, from 0222's builder:
  `{belegstellen_riegel.cpp, daten/adressen.md, daten/reihen.toml}`. The five inherited
  files were not needed — notably `kern/src/schritt.cpp`, which 0197 needs the moment its
  blockade lifts. **Inherited `dateien` lists cost lanes; make the builder report which
  ones he did not touch.** That instruction paid for itself in one run.
- **Deferred on purpose, do not forget it:** `daten/reihen.toml:1870` was repaired but
  deliberately left without a Schluesselwort, because adding one would move the base
  number 0166's Messstand prints. It is a real open decision — take it up **after** 0166
  is `fertig`, never during.
- **Third wave of citation breakage, and I am carrying the count to the Geschäftsführer.**
  0200 wave one, 0222 wave three, 0224 the prose sites the riegel never scanned. Whether
  nachzug belongs in the uebersetzer's own loop is recommendation B in `ops/plan.md` and
  has been the operator's open decision for a day. Note for that report: three sections of
  `technik.md` remain, so **wave four is the last one** — which weakens the case for a
  rule change and strengthens the case for just finishing.
- **0197 stays blocked, one package deep** — 0198 is `fertig` and off its `haengt_an`;
  only 0208-schritt remains, frozen under the same `technik.md` line. Both remaining gaps
  of `ops/plan.md` are behind the translation run, not behind an agent.
- **`Realeinkommen` is settled**: T48 quantity, 310 stays 310, 890 stays 890, T48 22 → 25.
  The architect needs that number and the core builder measures against it.
- **The daten-pruefer's own boundary is worth quoting when someone asks what green means
  here:** without a shell he cannot read a blob, so a leaf value changed *in place* moves
  none of his counts. He wrote it himself rather than letting it pass as coverage.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count —
  **fourth run in a row.** No role may delete (hard rule 3), so this only ever leaves the
  repo by the operator's hand. It belongs in the Geschäftsführer's report, not in this
  list where I have now written it four times. Subtract 2 from every `gebaut` count until
  it goes.
- **`technik.md` zerlegen**, twentieth time due — but for the first time the argument has
  changed: the file frees itself in about two days. **Split it for the next venture, not
  for this one.** Fifteen packages waiting on one file was worth a rewrite when the wait
  was open-ended; it is not worth one with three sections left.
- **`high` was enough**, thirteenth run. Two acceptances, one unblocking, one package cut.
  The one thing that needed judgement was refusing to re-plan around the reservation, and
  what settled it was arithmetic on two small files — reading, not reasoning.

