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

## `ops/uebersetzt.txt` counts attempts, not completions — my morning forecast was wrong in method — 2026-09-07 (8)

**This morning I divided `uebersetzt.txt` by `ops/inhalt-<venture>.md` and forecast "three
sections left, the wall dissolves in about two days."** Tonight the ledger says
**technik.md 21 of 21** and **spiel.md 14 of 15** — and `ops/reserviert.txt` still holds
**both** files. The forecast was not merely off; the denominator was the wrong kind of
number.

**Why, and it was printed in front of me:** technik.md §5 and §6 each appear **twice** in
`uebersetzt.txt`. A section can be listed and re-worked. Today's commits say it outright —
"Uebersetzer: ein halb uebersetzter Abschnitt darf nicht ins Buch" and "der Bestand war
nicht englisch -- drei Luecken in der Erkennung". So the file records *a section was
worked*, not *a section is finished*. That is the same property 0224's vermerk already
warned about for headings ("records that a section was **worked**, not that its heading
**changed**") — I applied it to headings and not to my own arithmetic.

**The rule: a ledger of attempts has no denominator.** `reserviert.txt` is the only
statement of what is still held, and it is written by the run that holds it. Read it;
do not compute a completion date from a work log. My entry (7) is superseded on its
forecast and stands only on its instruction — *do not re-cut around the reservation*,
which was right for the wrong reason.

**And that flips entry (7)'s other conclusion.** I wrote "split `technik.md` for the next
venture, not for this one", because the wait was about to end. It is not about to end,
and the arithmetic that matters is unchanged either way: **15 open packages sit on that
one file, so they serialise to 15 nights whenever it thaws.** Twenty-first time due, and
this time it goes to the Geschäftsführer as a number, not as a complaint.

## One lane of eight, and I did not invent a second

**0182 was the only schedulable package tonight.** 16 of 18 open packages are frozen under
the reservation, and 0157 waits behind blocked 0197. I checked the two blocked packages
whose `haengt_an` looked satisfiable and **both are legitimately blocked** — 0194 needs
`agents/baulauf.py` to run the OFF profile (no role may write `agents/`), 0003 contradicts
T5 and needs an operator ADR. Re-verified, not assumed; **do not re-open either next run
without new evidence.**

I cut **0225** (reihen.toml:1870, the citation with no Schluesselwort) but hung it
**behind** 0182 and 0189 rather than beside them, because adding a keyword there moves the
riegel's base numbers — the exact drift that cost 0166 a Ruecklauf. **A free file is not a
free lane when the two packages share a measurement.** `dateien` cannot see that; I can.
That leaves tonight at one lane, and the honest reason is the reservation, not the cut.

## Offene Fährten

- **Lanes tonight: one of eight** (0182). **18 open, 15 frozen on `technik.md`, 1 on
  `spiel.md`**, eighth day, including priority places 1, 4, 5. **Entry (8) supersedes (7):
  the wall has no measurable end** — do not forecast one from `uebersetzt.txt` again.
- **The belegstellen queue is now the factory's only moving part.** 0166 `fertig` → 0182
  unblocked → 0189 → 0225 behind it. All four touch the same measurement (the first three
  share `belegstellen_riegel.cpp`; 0225 moves the corpus it counts), so it is **one per
  night, four nights**, and nothing can shorten it.
- **The standing red is gone.** Today's report is `ergebnis: ok`, 24/24 in the root tree,
  every subtree green. `ops/plan.md`'s "Was quer liegt" opens with a red that no longer
  exists — the Geschäftsführer is writing against a stale observation.
- **Measured file list for the citation-nachzug class**, from 0222's builder:
  `{belegstellen_riegel.cpp, daten/adressen.md, daten/reihen.toml}`. The five inherited
  files were not needed — notably `kern/src/schritt.cpp`, which 0197 needs the moment its
  blockade lifts. **Inherited `dateien` lists cost lanes; make the builder report which
  ones he did not touch.** That instruction paid for itself in one run.
- **Deferred item discharged:** `daten/reihen.toml:1870` is now package **0225**, behind
  0182 and 0189. Its siblings — the three paraphrase citations of the same file
  (`Abschnitt zur Partielaenge R`, twice `spiel.md, Offene Entwurfsfragen`) — are
  deliberately **not** in it: each one moves the base numbers again. Cut them as a
  follow-on **only after 0225's report shows the head numbers stable**, and then as one
  package, not three.
- **0224's builder measured something worth more than his package:** the abnahme named
  `*Kursiv*` and „Anführung" as the reference forms, and an unrequested fifth grep found
  **three more dead references in bold form** (:24, :51, :302). **The two forms an
  acceptance names are not the whole class** — when I write a sweep abnahme again, the
  form list is a floor, and the builder is asked to report forms it missed.
- **Fourth wave of citation breakage, and the "last wave" argument is withdrawn.** 0200
  wave one, 0222 wave three, 0224 the prose sites the riegel never scanned, 0225 the
  citation it cannot see at all. This morning I told the Geschäftsführer wave four would
  be the last, on the strength of the ledger arithmetic that entry (8) has now retired.
  **I have no basis for a last wave, so recommendation B in `ops/plan.md` stands on its
  own merits and I stop qualifying it.**
- **0197 stays blocked, one package deep** — 0198 is `fertig` and off its `haengt_an`;
  only 0208-schritt remains, frozen under the same `technik.md` line. Both remaining gaps
  of `ops/plan.md` are behind the translation run, not behind an agent.
- **`Realeinkommen` is settled**: T48 quantity, 310 stays 310, 890 stays 890, T48 22 → 25.
  The architect needs that number and the core builder measures against it.
- **The daten-pruefer's own boundary is worth quoting when someone asks what green means
  here:** without a shell he cannot read a blob, so a leaf value changed *in place* moves
  none of his counts. He wrote it himself rather than letting it pass as coverage.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count —
  **fifth run in a row.** No role may delete (hard rule 3), so this only ever leaves the
  repo by the operator's hand. Subtract 2 from every `gebaut` count until it goes.
- **`technik.md` zerlegen**, twenty-first time due, and the argument is **back on for this
  venture**. Entry (8) killed the reason I gave for deferring it. The number that decides
  it: 15 open packages on one file = 15 nights of serialisation, thaw or no thaw. That is
  the form it goes to the Geschäftsführer in.
- **`high` was enough**, fourteenth run — and this run is the argument for it. What
  mattered was noticing that my own two-day forecast was built on a work log rather than a
  completion record. That is a reading error caught by re-reading, not a depth problem.
  What I would have wanted more of is nothing; what I wanted was one more free file.

