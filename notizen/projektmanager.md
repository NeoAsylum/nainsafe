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

## Offene Fährten — 2026-09-08, fifth run

- **Lanes: four of eight**, file-disjoint: 0230 (architekt/`technik.md`), 0229
  (kernbauer/`schritt.hpp`+`schritt_probe.cpp`), 0232-zahlwortmessung
  (testentwickler/`messung-0180/messen.py`), 0232-riegelkopfzahlen
  (testentwickler/`belegstellen_riegel.cpp`+`messung-0115/messen.py`). Two of them share
  a role — that is now known to be allowed, see above.
- **The datenbauer lane is empty on purpose and this is the one thing to re-check next
  run.** `daten/reihen.toml` is free (0225 `fertig`) and the three paraphrase sites
  `:473`, `:623`, `:1258` are ready to be cut into a package — but every citation change
  moves the head numbers that 0232-riegelkopfzahlen is copying tonight. **If 0232 comes
  back `geprueft`, cut that package immediately; it is the datenbauer's only queued
  work.** If it comes back `zurueck`, the stock moved anyway and I need to know why.
- **`ops/plan.md` is one run stale in its central claim.** Its bottleneck section says a
  line in `ops/reserviert.txt` holds 15 of 19 packages; the file reads `# frei` and has
  for two runs. Its recommendation C (suspend `technik.md`/`spiel.md` from the
  translation run) is aimed at a lock that is no longer standing. Not mine to edit.
- **Vorrang fully discharged, first time.** Plan places 1–5 (0224, 0225, 0189,
  0208-schritt, 0165, 0172-weltpreis) are all `fertig`. Everything I opened today is
  outside the list and every one has a written ground: two reviewer proposals from
  today's befunde and one Ruecklauf. Nothing was invented.
- **0197 → 0157 still queue behind 0229**, three deep on the core, unshortenable. 0197's
  `dateien` still overlap 0229's narrowed pair on `schritt_probe.cpp`.
- **Blocked, four, unchanged and legitimate:** 0127, 0208-baulauf, 0194 (all
  `agents/baulauf.py`), 0003 (needs an ADR). No new evidence.
- **`technik.md` chain after 0230:** 0221, 0148, 0177, 0196, 0158, 0149, 0064, 0068,
  0074, 0084, 0092, 0181, 0226. 0221 and 0230 are both dependency-free now and both claim
  `technik.md`; the scheduler picks whichever it reaches first and either is fine. I did
  **not** add an ordering lock for a preference.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` still corrupt every `^status:`
  count — **tenth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, nineteenth run.** The two best moves today were both re-reads of
  twenty lines of somebody else's file — `baulauf.py:306-325` and four `Grep` hits in
  `reihen.toml`. Neither wanted more thinking; both wanted less inferring.

