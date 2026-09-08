# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 15496 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-8.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · a
satisfied `haengt_an` is inert — name the package you must **not** run beside, and
recompute a proposed one, never carry it over · a sweep is unprovable, an enumeration is
countable · **ask whether the role owns the tools its own acceptance requires** · a number
that "lands in the report" must land in a file the package writes, or a befund · never lock
past the next link, and re-decide the one link every run · an already-`offen` package is
not a vetted package · lanes are scarce, nights are not · evidence never lives in a run
summary · read the odds of a return off the *kind* of acceptance: *fix* rarely comes back,
*decide* often does · answer the tool question against `agents/lauf.py:NIE` and a precedent
package, never against the role's frontmatter · never read `werkzeugkette.cmake` or
`technik.md` whole.

---

## Ask not only "does the role own the tool" but "does the input exist" — 2026-09-08 (21st run)

`ops/plan.md` made *„Schritt 3 rechnen lassen"* Vorrang 1: a `kernbauer` package on
`kern/src/schritt.cpp`. **I did not cut it, because it cannot be built, and a builder who
took it would have failed through no fault of his own.** Step 3 in the `weltlauf` needs the
historical instrument path of round `t`. Measured, in this order and it took four greps:

- `schritt.hpp:369-370` — `schritt(const Zustand&, const Aktionsbuendel&, const Konstanten&, Modus)`.
- `werte.hpp:112` ff. — `Konstanten` is seven scalar key fields plus `leitzins_start` and
  `durchgriff`. No series.
- `Zustand` holds this round's addresses.

**No argument, no field, no address carries the path.** The spec demands the value
(T25 `:2003`, section 23 `:5020-5021`) and provides no route for it.

**The generalisation, and it is the tool question one level up.** I have been asking "does
the role own the tools its acceptance requires" for weeks and it has saved runs. The same
question has a second half I had not been asking: **does the *input* the acceptance needs
exist today?** A build package whose data has no way in is as unbuildable as one whose role
has no `Edit`. Both look fine in the frontmatter. **Check it by reading the signature and
the carrier struct, not the prose around them** — the prose said *„come from the historical
path"* and was true and useless.

## The gap was already named in `specs/`, addressed to me, and nobody picked it up

`technik.md:5482-5489`, section 28, package `0158`, `fertig` since some days:
*„**Report 2 — the route of a path value into the round is open** … Whether it travels in
that carrier … or beside it, is a signature question … It is not decided here, because this
package may not widen `schritt`."* It even pre-decides two sub-questions (the clamp sits in
the accessor; a `const` carrier needs no ADR) so the successor cannot re-open them.

**That is a package proposal written into a specification, and it has no `status` field, so
nothing in this factory ever schedules it.** The Vorschlag mechanism from 2026-09-02 covers
what an agent notices *in its own run*; it does not cover what a spec section says about
work it could not do. **Practical rule for me: when a spec section ends in a report
addressed to a role, grep it.** `Grep -n "is a package and not"|"is open"|"not decided
here"` over `technik.md` would have found this a week ago. Try that next run and write down
what it costs.

Became `0277-der-weg-eines-pfadwerts-in-die-runde`, architekt, and it takes the one
`technik.md` lane over four packages I locked behind it.

## Four locks for one lane, and why I paid it

`baulauf.py:pakete` sorts by **filename**, so among startbereit packages on one file the
lowest number wins. `0277` is the highest number in the venture; without locks the lane
would have gone to `0181` (a Vorspann tidy-up) by pure arithmetic. Locked: `0181`, `0230`,
`0236`, `0274`. `0226` follows `0181` and needed nothing.

**One of the four turned out not to be a queue lock at all.** `0236` asks which state the
quantities of a rule read, and `schritt.cpp:541-550` names the condition under which the
question even arises: *„An dem Tag, an dem Schritt 4 rechnet, fallen sie auseinander."*
`0277` is the package that opens the road to that day. **The lock is technical, and I only
saw it because I read the source comment while checking something else.** Worth the habit:
when you lock A behind B for queue reasons, read A's own subject once — sometimes the queue
lock was a dependency you had missed.

## I was wrong about `belegstellen_*` for nine runs, and the Geschäftsführer dissolved it

My standing note said: `belegstellen_wortabstand` / `belegstellen_kopfzahlen` are red on the
tool's own head comment measured against a moved `HEAD`, **no agent can read a commit**,
structurally unreachable, not a package. I told three builders that.

**True of the transcription construction, and only of it.** The plan's Vorrang 4 changes the
construction instead of the number: let the latch measure its three figures **in the run**,
and no reference commit is needed. Six finished packages (`0115`, `0166`, `0189`, `0227`,
`0232`, `0233`) had all carried numbers into that head, each correct on its day.

**What made my error survive nine runs: I described a limitation of the current design as a
property of the world.** The test is one question — *is the thing unreachable, or is the
construction that needs it wrong?* Became `0278`, kernbauer, three files nobody else carries.
**Its dangerous condition is 2, not 1:** the cheap green here is a latch that compares its
output with itself, and that is the "grün und wertlos" lesson exactly. I wrote condition 2
to be read first and said so in the package.

## Offene Fährten — 2026-09-08, 21st run

- **Three to `fertig`** — `0092`, `0272`, `0273`, **all `geprueft` on the first attempt, all
  with the reviewer re-deriving every number.** `0272` built its risky condition 3 instead of
  using the escape hatch. **`0273`'s condition 5 is literally unmet and I accepted anyway:
  conditions 3 and 5 contradicted each other in the case that occurred** — 3 orders the red,
  5 demands `Passed`. My fault, in my own criterion. **The wording for every future latch
  package, now written into `0273`: "green, *or* red with every divergent line named with
  file and line" — never `Passed`.** Used it already in `0278` condition 3.
- **Two proposals accepted** (`0274`, `0275-eine-zahl`), **one accepted and renumbered**
  (`0276`, was the second `0275`), **two cut** (`0277`, `0278`). **Review is empty going in;
  tonight is Bau only.**
- **Lanes tonight: three, against eight slots.** `technik.md` → `0277`;
  `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` → `0275-eine-zahl`;
  `werkzeuge/belegstellen/` (3 files) → `0278`. **Five slots idle, and I looked for a
  fourth: there is none.** Everything else open is `technik.md` (`0181`, `0226`, `0230`,
  `0236`, `0274`, `0276` — six packages, one lane by construction) or waits on a T7
  decision.
- **The number collision was real and is fixed.** The `kern-pruefer` wrote two proposals in
  one night and called both `0275`. The first-written keeps the number; the other is `0276`,
  and the old file stands at `status: fertig` with a pointer and empty `dateien`/`haengt_an`
  so it claims no lane. **Nothing deleted.** If this repeats, the cheap guard is one glob
  before writing a number.
- **Check first next run:** (a) `0277` is a *decide* package and by my own discount those
  come back — **if it returns, read whether the befund says "no decision" or "wrong
  decision"**. No decision means the acceptance let him survey; then condition 1 becomes
  "one route written out" and nothing else. (b) `0278` condition 5 is an escape hatch; if it
  is used, the reason must be in the file's head — **silence there is the Ruecklauf**, same
  clause that held for `0270`, `0271`, `0272`. (c) `0275-eine-zahl` condition 3: does the
  existing case at `:2012` already cover it? Either answer is fine, **silence about which is
  not**.
- **For the Geschäftsführer — and this is the one item.** *„Die Fabrik baut den Prüfapparat
  einer Simulation, die noch nicht rechnet"* now has a named cause and a named package.
  **Vorrang 1 was cut for the wrong role: it is an architekt decision on `technik.md`, not a
  kernbauer build, because the input does not exist.** I followed the priority and changed
  its role; `0277` carries the reasoning. The ask is unchanged and now specific: **the
  backlog is still six of eight packages on one file**, and it needs work outside `specs/`
  or a decision about that file. `ops/reserviert.txt` reads `# frei`, **fifteenth run.**
- **Withdrawn:** the `belegstellen_*` "structurally unreachable" note, ninth run, see above.
  **Standing:** `RUECKLAUF_MAX` counts befunde rather than fault, tenth run.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` —
  no role may write there, it is the operator's, and `ops/plan.md` recommends B), `0003`
  (ADR), `0157` (no execution tool).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` →
  `schuld` for CN/BR — still Geschäftsführer, no *role* owns that judgement.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-sixth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-fifth run.** The hard call — that Vorrang 1 was uncuttable as
  written — turned on reading four signatures, not on thinking harder about them.
