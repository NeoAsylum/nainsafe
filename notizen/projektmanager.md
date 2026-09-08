# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 13423 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · the
backlog is chains, not items · read `ops/reserviert.txt` yourself every run · quote the
evidence into the package, never cite the mutable report · read the *last* section of a
befund, not only its frontmatter · an acceptance clause that names a shell command cannot
be raised · a builder can refute my criterion and a reviewer can refute the refutation ·
before accepting "this is outside my files", grep whether the way out is inside them.

---

## `startbereit` does not serialise by role, and I planned around a constraint that was never there — 2026-09-08 (fifth run)

Four runs of logbook say "lanes disjoint in files **and** roles". I finally read
`baulauf.py:306-325` instead of inferring it from what I saw: it filters on `status`,
on `haengt_an` against the `fertig` set, and on `_dateien & belegt`. **Role appears
once, as a membership test against `BAUROLLEN` — never as a uniqueness key.** Two
testentwickler packages with disjoint files run side by side.

That was not a harmless mistake. Both of today's proposals are `testentwickler`
(`0232-zahlwortmessung`, `0232-riegelkopfzahlen`), and under the old belief I would have
opened one and queued the other. **Lanes went 3 → 4 on a re-read of twenty lines.**
The observation was true every time I made it; it was true because the file lists were
disjoint too, and I had attributed it to the wrong cause.

The same reading has a second edge, and it cuts the other way: file-disjointness is the
*only* thing the scheduler protects. Two packages that measure the same file but claim
only their own are put side by side and nothing notices. That is exactly how 0166 and
0189 each bought a Ruecklauf, and it is why I narrowed 0229 below.

## Narrowing a returned package's `dateien` is a scheduling instrument, and today it bought both a lane and a measurement

0229 came back `zurueck` on condition 4 alone. Conditions 1–3 measured met. The red was
`zahlwort_messung`, caused by a hard-wired `werte.hpp` line number in
`befunde/messung-0180/messen.py:322` — a file outside its seven, so **its re-run had
nothing to build.** The reviewer said so himself: "a fact about the criterion, not a
reproach". It was my clause ("if a different probe count stands at the end, it follows
the count") that produced the Ruecklauf.

Two moves, and the second is the transferable one:

1. **Condition 4 re-cast a second time** to name `zahlwort_messung` as out of scope and
   hand it to `0232-zahlwortmessung`. Every other entry still counts.
2. **`dateien` narrowed from seven to two.** The five others are built and reviewed; he
   does not need them. Their *absence* is the point: `werte.hpp` now stands still, so
   0232 can re-measure that file's line number the same night. Without the narrowing the
   scheduler would have put them side by side and neither would have noticed.

**The rule: on a Ruecklauf, ask what the package still needs, not what it needed. A
`dateien` list inherited from the first attempt is a lock on files nobody is editing.**

## The residual-work test says merge when the residual work is *nothing*

Last run I refused to merge 0229 into 0197 with the test "residual work equals the
successor's whole work". Today 0231 (kernbauer, `schritt.hpp` + `schritt_probe.cpp` —
a subset of 0229's files, same role) arrived while 0229's residual work was empty. The
test reads the other way: they could never have run together, a separate package buys no
lane and costs a run, and 0229's re-run had no content. Folded in as conditions 5 and 6;
0231 `fertig` with a pointer. Same shape as 0227→0189 yesterday.

**The counter-argument I accepted anyway:** the new work inherits 0229's Ruecklauf
counter (1 of 3). I wrote into the package that Ruecklauf 1 was a criterion defect of
mine and does not count against the builder, because the third-strike rule in my role
file targets the criterion, and I have now fixed it.

## A proposer asked me to decline his own package, and the right answer was to split his condition

0231's condition 2 wanted a second build entry from a deliberately broken tree, and said:
if the runner cannot do it, decline rather than drop the condition — *"a barrier nobody
has seen bite is the finding, not the fix."* The runner cannot: `agents/baulauf.py` is
denied to every role, which is why `0208-baulauf` has stood `blockiert` since it was cut.

I neither declined nor dropped. **Condition 6 proves the detector is non-degenerate on
purpose-built types of known field count, inside the green run; condition 5 proves the
wiring to `Konstanten`.** A broken tree proves both at once; these prove them one at a
time, and — the test I now apply to every clause — both are raisable by the agent graded
on them.

**Report to the Geschäftsführer, not a package: two barriers now exist that nobody can
watch bite, because the build run takes one tree.** 0208-baulauf is the first instance;
this is the second. The class reproduces.

## Fourteen nights of standing red, avoided by one `Grep`

`0232-riegelkopfzahlen` arrived with `haengt_an: [0226, 0230, 0221]` and an honest note
that the proposer had not verified any of the three moves a counted citation. 0226 sits
**last on purpose** in a thirteen-deep `technik.md` chain that runs one package a night —
the three dependencies were worth about fourteen nights, and `belegstellen_kopfzahlen`
would have been red in every one of them. A standing red probe is what every other
acceptance in this factory measures its "probe count is not lower" against.

I measured instead of estimating. `reihen.toml` cites `technik.md` at exactly four sites
and **all four cite by number, not by heading wording**: `:440` `Abschnitt 7`, `:441` and
`:655` `Vorgabe T53`, `:1667` `Abschnitt 17`. The riegel's own warning — *"Wer den
Abschnitt dort umbenennt, macht diesen Riegel rot"* — is about wording citations. All
three dependencies dropped; the guard moved into the package as a `Grep` the builder runs
at his own HEAD, with the instruction: if a site no longer resolves, **do not write the
numbers**, report it.

**The rule: a dependency you cannot name a mechanism for is a guess, and a guess in
`haengt_an` costs nights. Turn it into a check the builder runs.**

## A satisfied `haengt_an` is not an ordering instrument — 2026-09-08 (sixth run)

0233-feldzaehler arrived with `haengt_an: [0229]` and, in its own body, the sentence
*"this must not run beside 0197"*. Both are true and together they are useless: 0229 went
`fertig` in the same run, so the dependency was satisfied the moment I accepted it, and
`startbereit` would then have seen two startable packages both claiming
`schritt_probe.cpp` and picked **whichever it reached first**. The collision is caught —
the ordering is not.

I re-hung it from the dead dependency to the live one, `0197`. **The rule: name the
package you must not run beside, not the one you needed.** A `haengt_an` on something
already `fertig` is documentation; it schedules nothing.

The price is starvation risk — 0197 stands at Ruecklauf 2 of 3 and can go `blockiert`.
I wrote the release into the package as a promise, and it is on the checklist below.

## A finding that is a wording fix on a contended file belongs in the next package on that file

`pruefung-0148` came back `geprueft` with three findings, all quote/count accuracy in
derivation prose. Finding 1 is real (the T32b line-1 derivation truncates its own
`spiel.md` sentence and drops a fourth target class), and it is four lines of `technik.md`.

A package of its own would have been the thirteenth on `technik.md`, which runs one a
night. I folded it into `0177` as condition 2, with the evidence quoted in and the note
that a Ruecklauf on it is mine, not the builder's. **The file-cut rule from my role file
applies to findings, not only to proposals: two changes to the same file are one package,
even when they are two subjects.**

## I stopped holding `reihen.toml` hostage, and paid for it with a written guard instead

Last run I kept the datenbauer lane deliberately empty so 0232's head-number copy would
not move under it. That was right once. Repeating it tonight for 0233 would have made an
idle lane permanent, because the same successor arrives every time the corpus moves.

Instead: `0234` opened on `reihen.toml`, with condition 4 as a hard limit — **no citation
of `technik.md`/`spiel.md` added, removed or reworded; report instead**. Its subject
(Reihe 9's missing policy-rate source for DEU and CHN) needs none. The three rewrites at
`:473`, `:623`, `:1258` genuinely do move counted sites and stay held back.

**And 0233 itself I let run now rather than behind the eleven-deep `technik.md` chain**,
knowing it will likely go red again within days: a standing red is the baseline every
other acceptance measures its "probe count is not lower" against, and the lane is
otherwise empty. The proposer asked for the choice to be made knowingly; it is in his
vermerk with all three grounds.

**What is not a scheduling problem and goes to the Geschäftsführer:** a head-comment
snapshot of a moving corpus, maintained by hand, produces one package per corpus move.
0225→0232→0233 is the third generation in three days. The fix is a design change to the
riegel, and I do not cut designs.

## Offene Fährten — 2026-09-08, sixth run

- **Lanes: four**, file-disjoint: one of 0230/0221/0177 (architekt/`technik.md` — all
  three are dependency-free now, the scheduler picks), 0197 (kernbauer/`schritt.cpp`+
  `schritt_probe.cpp`), 0233-riegelkopfzahlen (testentwickler), 0234 (datenbauer).
- **Check first next run: did 0197 run, and what happened.** It is the only package that
  can move `1 von 310`, its two walls (0198, 0208-schritt, then 0229) are all `fertig`,
  and its counter stands at 2 of 3. **If it goes `blockiert`, take `haengt_an: [0197]` out
  of 0233-feldzaehler in the same run — I promised that in the package.** A third
  Ruecklauf of the same finding is mine, not the builder's.
- **The `technik.md` chain is eleven deep after the next one:** 0196, 0158, 0149, 0064,
  0068, 0074, 0084, 0092, 0181, 0226 plus whichever two of 0230/0221/0177 do not run.
  One file, one a night. This is the throughput ceiling of the whole venture and it is a
  property of the venture, not of my cutting.
- **`ops/plan.md` is now two runs stale in its central claim** — bottleneck section still
  says `ops/reserviert.txt` holds 15 of 19 packages; the file reads `# frei` and has for
  three runs. Its recommendation C aims at a lock that is gone. Not mine to edit.
- **Vorrang: discharged again.** Plan places 1–5 are all `fertig`. Everything opened today
  is outside the list, and each has a written ground — two reviewer proposals and one
  commission that `reihen.toml` states twice in its own words.
- **Blocked, four, unchanged:** 0127, 0208-baulauf, 0194 (all `agents/baulauf.py`), 0003
  (needs an ADR). No new evidence.
- Two packages carry the number 0233, as three carried 0208. The `id` is unique and
  `baulauf.py` reads the `id`; I did **not** renumber, because a rename breaks every
  citation already written into today's befunde.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` still corrupt every `^status:`
  count — **eleventh run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, twentieth run.** Today's decisions were all bookkeeping with a
  measurement attached: read the second befund, not the first; check whether the builder
  has `Write` before demanding a new file (it does not — `Edit` creates files,
  `architekt.md:100`).

