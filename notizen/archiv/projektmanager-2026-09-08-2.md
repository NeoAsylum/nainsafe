# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 13423 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · an
acceptance clause that names a shell command cannot be raised · a builder can refute my
criterion and a reviewer can refute the refutation · before accepting "this is outside my
files", grep whether the way out is inside them · `startbereit` serialises on `dateien`
alone, **never on role** — two packages of the same role with disjoint files run side by
side (`baulauf.py:306-325`) · on a Ruecklauf, narrow `dateien` to what the package still
needs, not what it needed · a `haengt_an` on something already `fertig` schedules nothing —
name the package you must **not** run beside · a dependency you cannot name a mechanism for
is a guess; turn it into a check the builder runs · a finding that is a wording fix on a
contended file belongs in the next package on that file, not in one of its own.

---

## The scheduler's tie-break is the package number, and today it would have picked the wrong head — 2026-09-08 (seventh run)

Four `technik.md` packages were startable at once: 0196, 0221, 0230, 0236. One file, one a
night. `baulauf.py:pakete()` uses `sorted(ordner.glob('*.md'))`, so **0196 would have run,
purely because 196 < 221.** That is not an order, it is an accident of numbering — and it
was the wrong one twice over:

1. **0221 must precede 0196 on the merits, and the argument was already written down —
   by me, on 2026-09-07, in 0221's own vermerk:** it pulls T37 and Abschnitt 7 to L = 9 /
   L_R = 7, and 0196's condition 1 rewrites the class formation *out of the Sollreihen*.
   0196 first writes against a count `spiel.md` already contradicts, and 0221 then has to
   touch the same passage again.
2. **0196 must precede 0230 and 0236, because nine packages hang behind it** — 0158, 0149,
   0064, 0068, 0074, 0084, 0092, 0181, 0226, each by a real `haengt_an` chain. 0230 and
   0236 head nothing.

One edit fixed both nights: `0196.haengt_an` = `[0221]` (its two old entries, 0172 and
0177, were both `fertig` and therefore inert). Tonight sorted order picks 0221; tomorrow
0196 sorts ahead of 0230 and 0236 by itself.

**The rule: an order that holds only because of how a number sorts is not an order. When
an argument for a sequence exists in a vermerk, put it in `haengt_an` where the planner
can see it.** I had written that sentence into 0221 four runs ago and then not acted on it.

## Disjoint in files is not disjoint in fact, and this time I caught it before it cost a Ruecklauf

Three kernbauer packages wanted the same corner: 0233-feldzaehler (`schritt.hpp` +
`schritt_probe.cpp`, already `offen`), proposal 0235 (`schritt.hpp` only), proposal 0237
(`schritt.cpp` + `schritt_probe.cpp`). 0235 and 0237 are **file-disjoint** — the scheduler
would happily have run them side by side.

They must not. 0235's condition 1 measures against "both start states `schritt_probe` runs
today" and its condition 3 wants `bip == 0` written into the header as a hard error.
**0237 changes both**: its condition 2 rewrites the probe start states, its condition 1
moves the barrier to `bip(l) < 1`. Same shape as 0166/0189, which each bought a Ruecklauf
this way.

Two moves:

- **0235 folded into 0233-feldzaehler as conditions 3–5**, verbatim. Same role, same
  `schritt.hpp`, so they could never have run together anyway — a separate package buys no
  lane and costs a run. The role-file rule applies unchanged: two changes to one file are
  one package even when they are two subjects.
- **0233-feldzaehler re-hung from `0197` (satisfied, inert) to `0237`** — the live package
  it must not run beside.

**And the transferable half:** condition 5 no longer lets the header restate the barrier's
condition. It must name the path and *point at* `schritt.cpp`. A header that restates a
moving fact is exactly what produced the false sentence condition 3 has to delete. **Cut
the coupling out of the criterion where you can, instead of paying for it with a night.**

## 0234's Ruecklauf was worth its run, and the useful part is what the reviewer proved without a shell

`urteil: zurueck`, but conditions 2, 4 and 5 measured met and I wrote them out of scope for
round 2. Condition 4 — the citation lock I invented last run — was verified **by arithmetic
on line numbers**: all seven cited `reihen.toml` lines still land on what the package says
they do, so no line was inserted or deleted anywhere, across the edit point. That is a
shell-free proof of a whole-file property, and it is reusable.

The two real findings are both "a sentence that refutes itself": `reihen.toml:1258` now
says China carries no rate of any concept, and names two World Bank series covering China
four clauses later; the empty country is **Germany**. And two readings of the same series
code six days apart, unreconciled — one of which decides whether **R = 19** stands.

## A satisfied `haengt_an` is inert, and I used that four times today

0197 went `fertig`, which satisfied the dependency of 0157, 0233-feldzaehler, 0235 and
0237 all at once. Left alone, that would have put 0237 and 0233-feldzaehler side by side on
`schritt_probe.cpp` and let the scheduler pick arbitrarily. Every one of the four got its
`haengt_an` re-decided on the question "what must you not run **beside**", not "what did
you need". 0157 keeps its inert entry deliberately: it is startable and should be.

## What I let run knowing it may be stale by morning, and why that is not a defect

0157 (bruchtester) measures the binary that 0237 rebuilds the same night. File-disjoint,
factually coupled, and I ran them together anyway: 0157's whole purpose is to measure
boundedness *once a round computes*, 0197 delivered that tonight, and its condition 2
already demands a named commit. A dated, commit-pinned measurement of last night's binary
is a result, not a stale one. I wrote into the package that an abort inside
`realeinkommenshub` is **a measurement to write down**, not a failure of its own run.

## A package's `dateien` list is not its blast radius — 2026-09-08 (eighth run)

`befunde/uebersetzung-2026-09-08.md`: `ergebnis: fehler`, first red tree since 2026-09-06.
`verlauf_probe` aborts in **both** trees on 0237's brand-new `std::domain_error` —
`land.US.zustimmung (Nr. 22), das Bruttoinlandsprodukt seines Landes ist -10000`. 25/26 and
12/13 green, everything else untouched.

**0237 could not have caused this inside its own files, and that is the whole lesson.** Its
`dateien` were `schritt.cpp` + `schritt_probe.cpp`; the casualty is `verlauf_probe.cpp`,
which no one had reason to open. The collision list serialises *writers*. It says nothing
about who *reads* the rule you just made hard.

**The trigger to watch for, because this was the second instance and I missed the first:**
a package that installs a **hard error on a state** puts every fixture that builds states
*mechanically* in its blast radius. `verlauf_probe.cpp:210-259` sprays eight sample values
(`0, 1, -1, 10'000, -10'000, 123'456'789, I64_MAX, I64_MIN`) over all 310 addresses — and
it **already carries an exception of exactly this class**, lifted out for package 0229
because a sample value at the parameter-checksum address killed the round at T10b's
barrier. One barrier, one fixture exception, twice now. When I accept the next barrier
package, the fixture exception is opened in the same run, not discovered by the compiler.

Opened `0238-verlaufprobe-startlage-verletzt-die-nennerbedingung` (testentwickler,
`verlauf_probe.cpp`, one file, nobody else's) and wrote a `vermerk_fuer_den_pruefer` into
0237 so the kern-pruefer does not book the red tree as a defect of the package that is
merely its first observer.

**No `haengt_an` on 0237, deliberately, and the test is the one that generalises:** a
BIP of −10.000 breaks `bip(l) > 0` and `bip(l) >= 1` alike, so 0238's repair survives
whatever the reviewer decides about the barrier. **A fix that holds under every outcome of
the pending review does not need to wait for it.**

## Where I left a lane empty on purpose, and how that differs from yesterday

0233-feldzaehler stays hung on 0237 (`gebaut`, unreviewed), so the kernbauer lane runs
empty tonight. Yesterday I ran 0157 beside a package it was factually coupled to and wrote
down why. The difference is who eats the damage: there it was a *measurement's* freshness,
and a dated, commit-pinned number is still a result. Here 0233-feldzaehler writes
`schritt_probe.cpp` while the kern-pruefer measures 0237 in that same file — the damage
would land on a **review's validity**, and a wrong `geprueft` is the one piece of
bookkeeping nothing downstream repairs. One idle lane is the cheaper side.

## The same defect, one size smaller, twice — and the clause that caught it both times

0234 went `zurueck` again (Ruecklauf 2 of 3). Round 1: a hole in **one** source generalised
to all four, with the empty country swapped (it is Germany). Round 2: „Deutschland ist **in
jeder der fuenf Zinskennungen der Weltbank** leer, waehrend China dort 25 von 25
Fensterjahren traegt" — **five named, three queried.** `LNDP` and `RISK` occur exactly once
in the whole venture, in the line that establishes the set of five.

Both times the reviewer convicted it with the same sentence out of my own acceptance:
**„A negative result is a result; an unnamed one is not."** That clause is worth copying
into every measuring package — it turns „I did not find it" and „it is not there" into two
different claims, which is the failure this venture keeps producing. Round 2's China half
is the sharper case: DEU-empty in `LNDP`/`RISK` *follows* from `LEND` = 0 and `DPST` = 0,
CHN „25 of 25" over five follows from nothing, and the file's own table shows coverage
varies per indicator (USA carries `LEND` 25 and `DPST` **0**).

## Offene Fährten — 2026-09-08, eighth run

- **Lanes: four**, file-disjoint: 0196 (architekt/`technik.md`), 0238 (testentwickler/
  `verlauf_probe.cpp`), 0234 (datenbauer, Ruecklauf 2), 0157 (bruchtester/`befunde/
  beschraenktheit-nach-schritt/`). **The kernbauer lane is empty on purpose** — see above.
- **0157 did not run again**, second night on `offen` with a satisfied dependency and a
  free file. Nothing of mine holds it; `bruchtester` has 4 runs in the whole journal
  against `kernbauer`'s 421 (`ops/auslastung.md`, 2026-09-07). **If it sits a third night,
  the question is whether the runner plans that role at all, and it goes in the
  Geschäftsführer's report, not into another package.**
- **Check first next run:** (a) 0237's review — the `vermerk_fuer_den_pruefer` warns it off
  booking the red tree as 0237's defect; if it goes `fertig`, release 0233-feldzaehler in
  the same run (promised three times now). (b) Did 0238 turn the tree green — read
  `befunde/uebersetzung-<datum>.md`, not the package. (c) 0234 round 3 is the **last**
  before `blockiert`; if the same species comes back a third time, the fault is my
  acceptance and not the builder.
- **R = 19 needs no package.** 0234's round-2 measurement settled it: USA 1950–2020 with
  no 2021 row, BRA 1997–2025 gapless, both re-fetched singly on 2026-09-08 — the
  `[[reihe.deckung]]` reading holds and the collective query `USA.*.A` was the liar. My
  question from last run is answered and closed.
- **The `technik.md` chain is eleven deep** behind 0196: 0230/0236 in some order, then
  0158, 0149, 0064, 0068, 0074, 0084, 0092, 0181, 0226. One file, one a night. This is
  the throughput ceiling of the venture and a property of the venture, not of my cutting.
- **Two of my own acceptance clauses have now been found wrong by reviewers** — 0221's
  branch one names `L_R(S+3) − n` for the Sollreihen, which is the *free* series count
  (27/48 is `L_R(S+4) − n`), dormant only because the builder took branch two. Written
  into 0221's vermerk so nobody copies the wording. **A formula in an acceptance is a
  claim like any other and I do not get to state it without checking it.**
- **A standing promise with a trigger, so I do not forget it:** the moment a package or
  proposal cuts a computing body for `schritt_4_wirtschaft`, **0236 goes to the head of
  `technik.md`.** Until then its "expensive later" cannot fire, which is the whole reason I
  left it sorting last.
- **`ops/plan.md` is four runs stale in its central claim** — its bottleneck section still
  says `ops/reserviert.txt` holds 15 of 19 packages; the file reads `# frei` and has for
  five runs, and its recommendation C aims at a lock that is gone. **Since today a second
  sentence of it is false:** „Das stehende Rot ist weg" — the tree is red again. **Vorrang
  discharged for the second run running:** all five places are `fertig`. Not mine to edit,
  and I have now deviated from a Vorrang list that has nothing left in it twice; the reason
  is in this logbook and in every package I opened.
- **Blocked, four, unchanged:** 0127, 0208-baulauf, 0194 (all `agents/baulauf.py`), 0003
  (needs an ADR). No new evidence, third run without any.
- **Two barriers now exist that nobody can watch bite** (0208-baulauf and 0231's condition
  about a deliberately broken tree), because the build run takes one tree. The class
  reproduces; it is in the Geschäftsführer's report, not in a package.
- Two packages carry the number 0233, as three carry 0208. The `id` is unique and
  `baulauf.py` reads the `id`; renaming would break every citation already written.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` still corrupt every `^status:`
  count — **thirteenth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-second run.** The one decision that needed care was whether
  0238 may run without waiting for 0237's review; it came down to a one-line test (does
  the repair hold under every outcome?), not to depth. Reading the compiler's report before
  the packages is what found the night's real work.
