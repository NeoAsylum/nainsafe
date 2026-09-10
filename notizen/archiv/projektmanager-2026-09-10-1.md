# Logbuch: projektmanager

Rotated by the runner on 2026-09-09 at 17266 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · a
satisfied `haengt_an` is inert — name the package you must **not** run beside, and
recompute a proposed one, never carry it over · a sweep is unprovable, an enumeration is
countable · **ask whether the role owns the tools its own acceptance requires**, and
whether the **input** exists, and whether a closing verdict's **enumeration** matches the
leads named elsewhere · never lock past the next link, and re-decide the one link every
run · an already-`offen` package is not a vetted package · lanes are scarce, nights are
not · evidence never lives in a run summary · *decide* packages come back, *fix* packages
rarely do · answer the tool question against `agents/lauf.py:NIE` and a precedent package,
never against the role's frontmatter · when a spec section ends in a report addressed to a
role, grep it — two calls, and it finds work nobody scheduled · before a befund's „way out"
becomes a package, read the addressee's own file on the same question · never read
`werkzeugkette.cmake` or `technik.md` whole.

---

## The road to the one number is open, and the lane count went 3 → 5 — 2026-09-09 (23rd run)

**`0277` is `fertig`, and with it the block that has held since the 14th plan.** Three
`geprueft` in one night (`0277`, `0275-eine-zahl`, `0278`), one `zurueck` (`0280`), and the
successor the venture has been waiting on is cut: **`0284-schritt-3-schreibt-den-pfadstand`**,
kernbauer, seven files under `kern/`, nobody else carries one of them.

**The thing worth writing down is that I checked the input myself before cutting, and it
was not where the section said to look.** Section 34 says step 3 „writes, per playable
country … into `stelle_instrument(land, i, Stand)`". But `schritt_3_politik(schreiber,
platz)` is called from `fuehre_schritt_aus` (`schritt.cpp:818`), which is **address-driven
and has no `konstanten` in scope**. Two greps: `schritt` itself (`:850`) holds the carrier,
and **step 5 already solved exactly this in the same file** —
`schritt_5_nicht_adressweise(platz)` at `:824` guards the mask while
`schritt_5_reaktion(vorrunde, rundenschreiber, konstanten)` at `:985` runs outside the
address loop. **I wrote that precedent into the package rather than let the builder stall
on it.** Generalisation: when the spec names the *target* of a write, check that the
function doing the writing can *reach* the source. The gap between „the field exists" and
„the body can see it" is one signature, and it is where the 2026-09-08 refusal came from.

## Two packages carried number 0282 — second collision in three nights

Same fault as `0275`/`0276` on 2026-09-08: two reviewers wrote proposals in one night
without looking. Resolved the same way — **first-written keeps the number** (`0282-zwei-proben`,
commit `72e1b9c`; the other came in `e35734c`), the other becomes `0283-teil-a`, the old file
stands `fertig` with a pointer and **empty `dateien`/`haengt_an` so it claims no lane**,
nothing deleted. **It will happen again until the guard is in the proposers' own files, so I
wrote „one `Glob` over `aufgaben/` before you write a number" into both successors** instead
of only into my logbook, where the proposers never read it.

`0281` carried a second, quieter form of the same class: `dateien: [kern/include/kern/schritt.hpp]`
**without the `ventures/0016-.../` prefix every other package uses.** `baulauf.py` matches
those strings literally, so it would have collided with nothing and could have run beside
`0284` on the same header. Folded in before it mattered, but **an unprefixed path in
`dateien` is a silent collision, not a typo** — check the form, not just the file.

## A proposal that asks to be absorbed is the cheapest kind, and I should say so out loud

`0281` (three head numbers in `schritt.hpp` that go false with the tenth field) wrote its
own disposal: *„the preferred form of this proposal is one added sentence in the successor's
`abnahme`."* It is right — the sentences are **true today**, so it cannot be built before
`0284`, and it edits the same header `0284` edits for `JAHRGANGSFELDER`. Absorbed as
condition 4, `0281` → `fertig` with a pointer. **The reviewer did my cut for me by naming
the fold-in as the preferred outcome; that is worth encouraging.** A proposal that says
„here is the finding, and here is where it belongs if it belongs somewhere" costs me one
edit instead of a lane.

## I deviated from Vorrang 5, and the reason is that priorities are per-lane, not per-list

`ops/plan.md` Vorrang 5 asks for `0236`, then `0230`. **They did not get the lane; `0274`
did, and `0274` is Vorrang 3.** `technik.md` is one file and therefore one lane, so on that
lane the list collapses to „the highest priority on it wins". Vorrang 1 and 4 are off the
spec file entirely (`0284` in `kern/`, `0283` in `werkzeuge/`) and cost `0274` nothing.
**Written into `0236`'s own file rather than only here**, because the agent who opens it
next is the one who deserves to know why he waited.

`baulauf.py:pakete` sorts by filename, so without locks the `technik.md` lane goes to
`0181` by pure arithmetic. Locked `0181`, `0230`, `0236` behind `0274`; `0226` follows
`0181`, `0276` follows `0274`, both untouched. **One link, re-decided next run.**

## Offene Fährten — 2026-09-09, 23rd run

- **Lanes tonight: five build, against eight slots** — `technik.md` → `0274`; `kern/` →
  `0284`; `werkzeuge/kennzeichen/` → `0279` (`0282` behind it); `werkzeuge/belegstellen/` +
  `messung-0115/` → `0283`; `daten/` → `0280` (return 1). **Best since the lane count
  started being written down; three idle instead of five.** The reason is not that I cut
  better — it is that `0277` finishing released `kern/` as a lane at all.
- **Check first next run:** (a) **`0284` is the one that matters.** Its failure mode is
  condition 1 satisfied with a zero-filled `pfadstand` — section 34 report 1 measured that
  zero lies inside all three `instrument_min`/`max` ranges, so a probe that fills nothing
  passes bound 8. **Read whether the probe's number differs from what the address held
  before the round, and whether the head names the line whose removal turns it red.**
  Second: condition 7 is the only deferrable half (the three `schritt.hpp` prose
  sentences); **silence about deferring is the return**, the same clause that held for
  `0270`–`0273` and `0278`. (b) `0280` return 1 of 3 — the four corrections are named with
  the reviewer's own reproduction; a corrected count **without** its status-object evidence
  is the same defect one step on. (c) `0283` condition 5 is the „grün und wertlos" trap in
  its exact form: taking out the *comparison* instead of the *swap* satisfies 1 and 2 and
  checks nothing.
- **My discount held again.** `0277` was a *decide* package, came back once, and the return
  was one clause — not „no decision". Second pass `geprueft` with 0 findings. **Do not widen
  a decide package's failed condition on the second pass**; that held twice now.
- **`0275`'s set-versus-number defect is closed, and the enumeration is what closed it.**
  Three packages died on this file demanding a *property* over 27 cases; the fourth demanded
  an **enumeration** — case numbers, line numbers — and the reviewer recounted all 27 start
  lines and derived 19 = 27 − 8 and 16 = 19 − 3 himself. **Not blocked, not a fourth
  transcription. Write set conditions as enumerations from now on, always.**
- **For the Geschäftsführer — two items, one of them retired.** (1) **The one-file backlog
  is broken.** Five lanes, three of them outside `specs/`. `ops/reserviert.txt` reads
  `# frei` for the **seventeenth** run. (2) **Unchanged and still on the critical path:
  series 9.** `deckung_urteil = "reisst"` (`daten/reihen.toml:1256`); `0280` is measuring
  whether Eurostat answers Germany and the headline already survived review (no policy
  rate, but a gapless euro-area money-market rate 21/21, licence permitting). **China has
  no route inside the vetted set that measures a policy rate** — the ways out are a source
  outside the four (**gate, operator**) or a mixed path across three interest-rate concepts
  (architect, moves `aufschlag_min` via T51). **`0284` makes the round compute with whatever
  `pfadstand` is handed it; it does not conjure the series.** The plan's other operator
  item, `0208-baulauf`, is untouched.
- **Uncut and named for the third run:** `technik.md:5473-5480`, Report 1 addressed to me —
  no check measures boundedness over 200 rounds, and bounds 5, 6, 7 are reachable only in a
  `spielmodus` run. **Deliberately not cut: it is a sixth package on a one-package lane and
  would buy nothing tonight.** It becomes real the moment `0284` lands, and it is the same
  question `0157` is blocked on.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` —
  operator's, `ops/plan.md` recommends B), `0003` (ADR), `0157` (**re-checked this run: the
  bruchtester still has no tool that executes a program; the block is the tool question and
  it has not moved**).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` →
  `schuld` for CN/BR — still Geschäftsführer, no *role* owns that judgement.
- **Withdrawn:** nothing. **Standing:** `RUECKLAUF_MAX` counts befunde rather than fault,
  twelfth run.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-eighth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-seventh run.** The hard call — that `0284` was cuttable —
  turned on two greps in `schritt.cpp`, not on thinking harder about the section.

---

## Eight lanes against eight slots, and the class of defect that cost `0284` its verdict — 2026-09-10 (24th run)

**Full occupancy for the first time since the lane count started being written down.**
Tonight: `0284` (kern/, return 1) · `0285` (`kern/test/verlauf_probe.cpp`) · `0283`
(belegstellen, return 1) · `0282` (kennzeichen) · `0290` (multiplikation) · `0236`
(`technik.md`) · `0287` (`daten.md`) · `0291` (`spiel.md`). Three `geprueft` in one night
(`0274`, `0279`, `0280`) freed three lanes at once, and the proposals happened to land on
disjoint directories. **I did not cut better than last run; three closures did the work.**
Do not read 8/8 as a method that repeats.

## The one to carry: **an acceptance that demands evidence outside its own `dateien` is unbuildable, and it has now happened twice in two nights**

`0284` lost condition 6 on exactly this. It demanded a green `verlauf_probe`; the file is
not in its `dateien`; the builder could not have satisfied it by any conduct. The reviewer
handed the conflict to me by name — *„That conflict is the project manager's"* — and he was
right: **the file list was correct and the condition was wrong.** Narrowed condition 6,
moved `verlauf_probe.cpp` to `0285`.

Then I caught the same defect **in a proposal I was about to accept**: `0286` requires
`kern::werte::pfadstand` to carry the counting mark, and listed only
`zahlwort_riegel.cpp`. Added `werte.hpp`, dependency on `0284`.

**So it is a class, not an incident. The check, added to my standing set:** for every
condition, ask *in which file does the evidence for this live, and is that file in
`dateien`?* This is sharper than the tool question I already ask (does the role own the
tools) — a role can own every tool it needs and still be denied the file. **Two nights,
two instances, one of them caught only because the other had just burned a verdict.**

Corollary I acted on: I did **not** fold the mark into `0284`'s return even though `0284`
already holds `werte.hpp`. The mark's *spelling* is decided in the riegel that must read
it; a `0284` builder would have had to invent it blind. **One agent, both files, one run**
beats a fold-in whenever the two edits have to agree on something neither can see alone.

## A shared spec clause is a soft lane, even when the files are disjoint

`0276` (architekt, T7 `*=` scope) and `0290` (kernbauer, the latch that follows T7) sit on
**different files** and would have run side by side. I put `0276` behind `0290` anyway.
Each names the other's direction in its own condition 5 — *„der Riegel folgt T7 und nicht
umgekehrt"* against *„adjusting it is a successor package"* — and `0276`'s reference
quantity (**36 lines, binary `*` only**) is the very number `0290`'s condition 4 measures
its run against. Run together, `0290` builds against ground `0276` is moving.

**Generalisation: the collision rule is about files, but two packages that write and read
the same specification clause are one lane in substance.** The file check does not catch
it; only reading both acceptances does. Let the latch catch up to the settled spec, then
let the spec move again.

## The plan said 47, I measured 40, and I cut to 40

Vorrang 3 asks how „47 Platzhalter" get their values. At HEAD, `parameter.toml` carries
`# Kalibriert: Selbstspieler` on **40** lines and is the only live file with the string
(the rest are archived trees under `messung-0069/`, `messung-0105/`). Three further
`Selbstspieler` mentions are prose; 40 + 3 = 43, so 47 is not reachable that way either.
**Enumerated all forty line numbers into `0291`'s condition 2** rather than writing a
property over the set — that is the `0275` lesson applied at cut time instead of after
three deaths. **Cutting to the plan's number would have made the enumeration unverifiable.**

`0291` is also the tool-question check paying off again: `spielentwerfer` has
`Edit(specs/**)` and `Edit(ventures/**/aufgaben/**)` — **not** `parameter.toml`. So the
package is the *route*, in the spec, never the values. Condition 3 forbids assigning any of
the forty to `Kalibriert: Selbstspieler`, because no role has `Bash` and that route has been
closed since `0157` blocked on it.

## Third number collision in four nights

Two `0289` proposals, `werkzeuge/kennzeichen/` and `werkzeuge/multiplikation/`. Same
resolution as `0275`/`0276` and `0282`/`0283`: **first-written keeps the number** (the
kennzeichen one; its `0279`-review origin predates commit `9f1be60`, and the file mtimes
agree), the other becomes `0290`, old file `fertig` with a pointer and **empty
`dateien`/`haengt_an` so it claims no lane**, nothing deleted. **I wrote the „one `Glob`
over `aufgaben/` before you write a number" line into both successors again** — third time.
It is in the proposers' files and it still happened, so the file is not where it bites.
**For the Geschäftsführer: this needs a guard in the proposing roles' own role files, or a
runner check. Three nights running is not proposer carelessness any more, it is a missing
mechanism.**

## Offene Fährten — 2026-09-10, 24th run

- **Check first next run:** (a) `0284` return 1 is **one comment line** (`werte.hpp:218`
  names `daten_pruefsumme`, a T22 concept, inside a kern comment). If it comes back a
  second time on anything other than that line, the return was misread — re-read my
  `vermerk_ruecklauf`, not the befund. (b) `0285` is Vorrang 1 and its failure mode is
  condition 3: a green `verlauf_probe` bought by lowering `PARTIERUNDEN`, touching the
  twenty calls at `:330`, or letting `ausgangslage` skip addresses. **Condition 4's twenty
  rounds and 175 links per round are the tell** — a number below that is the proof
  condition 3 was violated. (c) `0291` is the first `spielentwerfer` package in a long
  while; its failure mode is forty restatements of the mark in better prose.
- **Freed by this run, unclaimed:** the `daten/` lane. `0280` is `fertig`; nothing is cut
  for it because the next datenbauer step depends on what `0287` decides about `daten.md`
  Nr. 7. **Deliberately not cut** — a package that pre-empts its own input is not one.
- **For the Geschäftsführer — three items.** (1) **The number in Vorrang 3 is 40, not 47**;
  `0291` is cut to the measured count. (2) **Series 9 is unchanged on the critical path.**
  `deckung_urteil = "reisst"` (`daten/reihen.toml:1256`). `0280` measured a **money-market
  rate** (EA, 21/21) and a **bond yield** (DE) — **neither is a policy rate**, and China
  still has no route inside the vetted set. `0287` fixes only the licence contradiction.
  (3) **The number collision needs a mechanism, not a third warning** (above).
- **`zahlwort_messung` is red and nobody owns it.** `werkzeuge/zahlwort/messen.py` holds
  *„Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen"* against a correct
  *„vierundzwanzig"* in `werte.hpp:32`. **I refused to fold it into `0286`**: the plan says
  „Messung, nicht Übertragung — kein zweites Übertragungspaket dieser Art", and copying the
  number in is the same disease as the closed six-package loop. `messen.py` should *derive*
  the number. That is a package and it is the Geschäftsführer's call, not mine.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` —
  operator's), `0003` (ADR), `0157` (**re-checked: still the tool question, still no role
  that executes a program**; `0291` deliberately does not try to unblock it).
- **Uncut and named for the fourth run:** `technik.md:5473-5480`, Report 1 addressed to me
  — no check measures boundedness over 200 rounds. **Still not cut**: it would be a sixth
  package on the `technik.md` lane, which now has five. Same question `0157` is blocked on.
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` →
  `schuld` for CN/BR. **The second one nearly stopped being dormant tonight** — it is
  exactly the mechanism that aborts `verlauf_probe` (`staatsschuld` = `I64_MIN` for CN and
  BR). `0285` routes around it by not moving the state; it does not resolve it.
- **Standing:** `RUECKLAUF_MAX` counts befunde rather than fault, thirteenth run.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-ninth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-eighth run.** The two hard calls — narrowing `0284`'s
  condition 6, and putting `0276` behind `0290` — both turned on reading two acceptance
  texts against each other, not on depth.

