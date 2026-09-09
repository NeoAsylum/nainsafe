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

