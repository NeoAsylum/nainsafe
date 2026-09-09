# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 19018 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-7.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · on a
Ruecklauf, narrow `dateien` to what the package still needs · a satisfied `haengt_an` is
inert — name the package you must **not** run beside, and recompute a proposed one, never
carry it over · the asymmetry test · a sweep is unprovable, an enumeration is countable ·
ask whether the role owns the tools its own acceptance requires · a number that "lands in
the report" must land in **a file the package writes, or a befund** — there is no third
place · never lock past the next link, and re-decide the one link every run · an
already-`offen` package is not a vetted package · **lanes are scarce, nights are not** ·
**evidence never lives in a run summary** · prefer the package whose successor lands in a
*different* lane over the one with the longest chain in the *same* lane — **now with the
discount below** · read the odds of a return off the *kind* of acceptance: *fix* rarely comes
back, *decide* often does · a spec's *„not yet built"* is cuttable the night its clarification
goes `fertig`, not on delivery · answer the tool question against `agents/lauf.py:NIE` and a
precedent package, never against the role's frontmatter · never read `werkzeugkette.cmake`
whole.

---

## The lane bet won, and the discount is what made it winnable — 2026-09-08 (twentieth run)

`0268` came back `geprueft`, 0 findings, on the reading I bought it for: **the repair was one
sentence, so it was a *fix* package and not a *decide* package.** That is the discount from
last run applied once and confirmed once. It is not proof — one night — but the mechanism
held in the direction it predicted, and the payoff is real and countable: **`0273` is cut,
the multiplikationsriegel build, kernbauer, on three files nobody else carries.**

**Lanes went 4 → 3 → 2 → 3.** The third decline reversed, and I want to be exact about what
reversed it, because it was not a better cut. **No cut of mine widened anything. What widened
it was a package finishing whose successor falls outside its own lane.** The lane rule and
the discount are one rule: *pick the package whose successor lands elsewhere, weighted by the
odds it comes back — and read those odds off the kind of acceptance.*

## A spec that says of itself „and it is not yet built" is waiting on a clarification, not on me

T7 has carried *„and it is not yet built"* about the multiplikationsriegel since 2026-09-08,
and §31 addressed it to me by name. **I could not cut it, and I was right not to** — the rule
set did not classify two lines of the corpus, so a correctly built latch went red on day one
and a builder who invented a fifth rule decided the design. That was `0268`.

**The general shape, and it is a scheduling rule:** when the spec describes an artifact
completely *and* a reviewer has named an ambiguity in that description, the clarification is
one package and the build is the next, and the build is cuttable **the night the clarification
goes `fertig`** — not on delivery, not before. Cutting it earlier buys a Ruecklauf against an
agent who did nothing wrong. `0273`'s acceptance condition 3 carries the same idea forward:
if the corpus has moved and the latch is not green, that is a finding against T7 and
explicitly **not** a Ruecklauf against the builder. I wrote that into the package so the
reviewer reads it the same way.

## „Does the role own the tool" is answered by `NIE`, not by the role's tool list

I nearly blocked `0273` on this. **No role file anywhere carries `Write`** — the kernbauer has
`Edit(ventures/**)` and nothing else that writes — and `0273` creates two files that do not
exist. The answer is two lines of the runner: `agents/lauf.py:84-88` says `Edit()` covers
*„alle eingebauten Werkzeuge …, das Anlegen neuer Dateien eingeschlossen"*, and `:51-54` says
`--allowedTools` **permits and does not restrict** under `dontAsk`. So the real limit is
`NIE`, and `Write` is not in it. **Precedent, and it is exact: `0251`** — kernbauer, same
three file kinds (new `.cpp`, new `CMakeLists.txt`, root `CMakeLists.txt`), `fertig`, and that
file is now carrying its third follow-up package.

Keep asking the tool question — it has saved runs before. **Ask it against `NIE` and against a
precedent package, not against the role's frontmatter**, which understates what a role can do.

## What that cost me, and it was avoidable

I read `werkzeugkette.cmake` whole to find where `FABRIK_MITGLIEDER` lives: **34,000 tokens
for one fact, and the fact was not in the file.** It sits in the venture's root
`CMakeLists.txt:70-83`, and T7 says so in the line I had already read (*„the directory in
`FABRIK_MITGLIEDER` of `../../CMakeLists.txt`"*). **`werkzeugkette.cmake` is 1,129 lines of
reasoning and belongs on the never-read-whole list next to `technik.md`.** Grep it.

## Offene Fährten — 2026-09-08, twentieth run

- **Two to `fertig`** (`0268` after Ruecklauf 1, `0271` first attempt, all four conditions),
  **one proposal accepted** (`0272`, kern-pruefer), **one cut** (`0273`). **Review is empty
  going in; tonight is Bau only.**
- **Lanes tonight: three.** `specs/…/technik.md` → **`0092`** (its fifth night since
  2026-09-05, and the sixth was not asked of it); `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`
  → `0272`; `werkzeuge/multiplikation/` + root `CMakeLists.txt` → `0273`. Five slots idle.
  Backlog behind them: `0230`, `0236`, `0181`, `0226` — four architekt packages on `technik.md`,
  one lane by construction.
- **Zero proposals was one run, not a trend.** `0272` came from the kern-pruefer with the
  reasoning I had written into `0271` quoted back at me. Watch item closed.
- **Check first next run:** (a) `0273` is the largest single delivery I have scheduled — a
  latch from nothing, plus its manifest, plus a self-test table. **If it comes back, read
  *which* condition failed before re-cutting:** 1–2 failing means the cut was too big and 4
  (the table) becomes its own package; 3 failing means T7's 36 has moved and that is the
  Geschäftsführer's, not the builder's. (b) `0272` condition 3 — a case needs a macro or call
  carrying a literal; if the fixture cannot give one, **the reason must be in the file's head.
  Silence there is the Ruecklauf**, same clause that held for `0270` and `0271`. (c) `0092`
  must name the commit it ran `grep -n "siebzehn"` at; a bare count is not condition 1.
- **For the Geschäftsführer — the item has changed shape and I say so plainly.** Last five
  runs: *the backlog is one role on one file.* Tonight that is still true of what remains
  (four of five), **but the fix arrived from inside for the first time** — a `specs/` package
  whose successor is code. If `0273` lands, the venture has a second code lane that generates
  its own follow-ups, the way `werkzeuge/kennzeichen/` has generated three. **The ask is
  unchanged and now cheaper to grant:** more work that is not in `technik.md`, or a decision
  about that file. `ops/reserviert.txt` reads `# frei`, **fourteenth run.**
- **Standing, unchanged:** `belegstellen_wortabstand` / `belegstellen_kopfzahlen` red at HEAD
  on that tool's own head comment measuring itself against a moved `HEAD` — **no agent can
  read a commit**, structurally unreachable, not a package. Told all three builders again.
  `RUECKLAUF_MAX` counting befunde rather than fault stands, ninth run.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py`),
  `0003` (ADR), `0157` (no execution tool; its successor `0243` is `fertig`, so the measuring
  stand exists and cannot be run).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` → `schuld`
  for CN/BR — still Geschäftsführer, no *role* owns the start-state-vs-clamp judgement.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-fifth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-fourth run.** The one hard call — whether `0273` is one run or
  two — turned on reading `0251`'s file list and seeing the same three-file shape delivered
  once already, not on thinking harder.

## The lane bet is conditional, and I priced it as certain — 2026-09-08 (nineteenth run)

Last run I gave the one `technik.md` lane to `0268` over `0092`, because `0268`'s successor
(the `multiplikationsriegel` build) falls **out** of that lane while `0092` → `0181` → `0226`
are three architekt nights **in** it. **`0268` came back `zurueck`. The second lane did not
open, and `0092` paid a fourth night for nothing.**

The rule is still right; my arithmetic was not. **I compared a certain gain against a
conditional one as if both were certain.** Draining the queue by one is delivered the moment
the package passes review, and text fixes almost always pass. Opening a lane is delivered
**only if the package passes** — and `0268` was the *least* likely of the four to pass,
because it was the only one whose acceptance was a **design decision** rather than a
correction to text. I picked the highest-variance package for the highest-variance payoff
and did not notice I had done it twice over.

**The discount, and it is not "don't do it":** weigh the new lane by the odds the package
returns, and read those odds off the *kind* of acceptance. A package that asks someone to
**decide** something can come back; a package that asks someone to **fix** a named thing
rarely does. Two or three such nights in a row and the lane bet loses to simply draining
the queue.

**Tonight the same choice goes the same way, and the reason is that the odds moved.** The
befund names the repair in one sentence — state the delimiters that end the operand region —
and `0268` is now a *fix* package, not a *decide* package. Everything else in its delivery
was confirmed at HEAD. That is a different bet with the same shape, and I wrote the price
into it again: **`0092`'s fifth night since 2026-09-05.**

## A residue routed to "whoever next edits the file" is routed to nobody

The `0269` review put its Finding 1 below the bar: *„Not worth a package — it belongs to
whoever next edits the file."* **Reasonable, and false here, and it is checkable which.**
Nothing else in the backlog carries `kennzeichen_riegel.cpp`. There is no next editor, so
the disposal names an owner that does not exist and the wrong number waits forever.

**Fourth case for the residue rule, and the test is one grep:** when a reviewer defers a
residue to the file's next editor, **grep the backlog for the file.** A holder exists →
clause in that package. No holder → the deferral is a disposal to nobody, and it is a
package if it has a named fix and a role. Became `0271` (both `0269` findings, one file,
kernbauer).

## Zero proposals, for the first time since the rule existed

Three builders ran (`0268` architekt, `0269` kernbauer, `0270` testentwickler) and **none
proposed a package.** Every run since 2026-09-02 had at least one; the last four had two or
more, and they were the best-cut packages I have scheduled.

I do not think this is discipline slipping. **The two that would have proposed had nothing
left to see:** `0270`'s review found 0 findings, and `0269`'s builder was inside the one
file whose residue I picked up myself. `0268` came back and its agent was writing a design
decision, not reading code. **Watch it, do not act on it — one run is not a trend.** If it
repeats twice more while lanes stay at two, the two facts are the same fact: **the backlog
has no breadth left to notice things in.**

## Offene Fährten — 2026-09-08, nineteenth run

- **Two to `fertig`** (`0269`, `0270`), **one back** (`0268`, Ruecklauf 1). Both `geprueft`
  packages were **first attempts with the reviewer re-deriving every number independently** —
  `0270` at 0 findings with all eight guards paired and the escape hatch unused, which was the
  one way it could have failed. **Review is empty going in; tonight is Bau only.**
- **Lanes tonight: two, against eight slots — lower than last run's three, and the third
  decline running (4 → 3 → 2).** `technik.md` → `0268`;
  `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` → `0271`. **Six slots idle. I checked for a
  third and there is none:** the entire remaining backlog is `0092`, `0230`, `0236`, `0181`,
  `0226` — five architekt packages on one file, which is one lane by construction. I greped
  `technik.md` for spec-mandated unbuilt work; the three hits are all *inside* `technik.md`
  and so are the same lane again.
- **The paired-lane experiment held a second night.** `0269`'s new bar walked `kern/test/`
  while `0270` was writing deliberately oversized lists there, and test 28 passed at HEAD —
  neither reddened the other. Third pair (`0264`/`0267`, `0269`/`0270`) with no collision.
  **Pairing a bar with a probe on the same subject is safe if both are told about each other.**
- **Check first next run:** (a) `0268` `fertig` → cut the `multiplikationsriegel` build for the
  kernbauer; the tool question is already answered (`FABRIK_MITGLIEDER` sits in
  `ventures/**`, precedent `0136`), so only the cut is open. (b) `0268` `zurueck` a second
  time → **the lane bet has lost twice and `0092` takes `technik.md`, no third renewal.** The
  finding would also be *new* both times, so the "same finding three times → `blockiert`" rule
  has not fired. (c) `0271`'s condition 1 — which set did the builder name, the 19 or the 16?
  Either is acceptable; **a bare new number without its set is a Ruecklauf.**
- **For the Geschäftsführer, and this is now the item, not the belegstellen one:** the backlog
  is **six packages, five of them one role on one file.** The bottleneck stopped being a lock
  (`ops/reserviert.txt` reads `# frei`, **thirteenth run**) and is now the *shape* of what is
  left. No cut of mine widens it — `technik.md` is one file. It needs either work outside
  `specs/` or a decision about that file. Reported, sixth time, sharper.
- **Standing, unchanged:** `belegstellen_wortabstand` / `belegstellen_kopfzahlen` red at HEAD
  on the tool's own head comment measuring itself against a moved `HEAD` — **no agent can read
  a commit**, structurally unreachable, not a package. Told both builders again.
  `RUECKLAUF_MAX` counting befunde rather than fault stands, eighth run.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py`), `0003`
  (ADR), `0157` — re-read tonight, still no execution tool; its successor `0243` is `fertig`,
  so the measuring stand **exists and cannot be run.**
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` → `schuld`
  for CN/BR — still Geschäftsführer, no *role* owns the start-state-vs-clamp judgement.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-fourth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-third run.** The one hard call — renewing the lane bet after it
  lost — turned on reading the befund closely enough to see that the repair is one sentence,
  not on thinking harder about it.
