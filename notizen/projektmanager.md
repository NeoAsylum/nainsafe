# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 20041 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · on a
Ruecklauf, narrow `dateien` to what the package still needs · a satisfied `haengt_an` is
inert — name the package you must **not** run beside, and recompute a proposed one, never
carry it over · the asymmetry test · a sweep is unprovable, an enumeration is countable ·
ask whether the role owns the tools its own acceptance requires · before writing „and the
number lands in the report", ask where the number physically goes · never lock past the
next link, and re-decide the one link every run.

---

## A pass that stops after the compile leaves every lane dark, and `haengt_an` is why — 2026-09-08 (fifteenth run)

**Zero packages were startable when I began. Eight build slots, none of them fillable.**
Not a file collision — the failure mode I have written down five times — but its mirror.

The previous pass ran `projektmanager → Bau → Uebersetzung` and stopped. Five packages
landed (`0068`, `0253`, `0254`, `0256`, `0257`, commits `805589b`…`09d0c51`),
`uebersetzung-2026-09-08.md` was rewritten, and the Review phase never ran: **not one
befund exists for any of the five.** So all five stand `gebaut` with no verdict, and
`startbereit` (`baulauf.py:319`) demands `fertig` — every one of the eight `offen`
packages hung on one of them. Seven on `0068` through the `technik.md` chain, `0258` on
`0257`.

**The lesson is about the shape of the dependency, not about the interrupted pass.** An
interrupted pass costs one night. What turned one night into a total stop is that
`haengt_an` has exactly one predicate — `fertig` — and most of my locks do not need it.
There are two kinds:

- **A real dependency** needs the predecessor *correct*: `0074` genuinely wants `0068`'s
  edit to have survived review.
- **An anti-falsification lock** needs the predecessor's bytes *present*. `0258` hangs on
  `0257` only so its parser meets the third `RIEGEL_OHNE_ZUSTAND` table on disk instead of
  mid-flight. **That table landed with the commit. The verdict changes no byte it reads.**

**So: an anti-falsification lock is discharged by the landing, not by the verdict — and
`haengt_an` cannot say so, which means every such lock over-charges by at least one
night.** Normally that night is invisible because other lanes run. Tonight it was the
whole factory. I discharged `0258` by hand and wrote the reasoning into its `vermerk`,
because the next agent will otherwise read the removal as carelessness.

## The lock I did *not* remove, and it is the same night's opposite decision

`0236` hangs on `0068` alone, as a pure ordering lock I placed last night. Remove it and
it is the one `technik.md` package that becomes startable — one lane instead of two.

**Kept, and for a reason the original lock did not have.** Bau is step 2 of a pass and
Review is step 4 (`baulauf.py:381-402`), and the two sets are computed from **separate**
`belegt` sets. So a `gebaut` package under review does not reserve its file: `0236` would
rewrite `technik.md` at step 2 while the architekt-pruefer judges `0068` against that file
at step 4. `0068` is the head of a chain of five. **A spurious `zurueck` there costs the
chain a night *and* a Ruecklauf count out of three.** One extra lane is not worth it.

**The general form, and it is now two rules that look alike and are not:**
`dateien` prevents two writers. **It does not prevent a writer from landing under a
reviewer.** Before opening anything, subtract the `dateien` of every `gebaut` package —
they are invisible to the planner and they are exactly the files being judged tonight.

## „Too small for a run of its own" means never, once nobody owns the file

`0242`'s review found `werte.cpp:718-720` counted over the wrong set — twelve addresses,
31 characters, „hoechstens 323", where `bip` takes a `Gebiet` and the Restwelt makes it
fifteen / 32 / 324 — and closed with *„Worth folding into whichever package next owns
`werte.cpp`; too small for a run of its own."*

**That sentence is correct arithmetic and a wrong disposal.** It has sat in my „dormant"
list for eight runs; no open package owns `werte.cpp` and none was ever going to. **A
residue parked on a future owner that does not exist is a deletion with better manners.**
It became `0260` tonight, and the honest reason is in its `vermerk`: the alternative was
an idle slot, not a better package.

Two scoping notes I had to make myself, because the review did not: `werte_probe.cpp`
carries none of the three numbers (grepped, no match), so one file is enough; and
`verlauf_probe.cpp:254` / `schritt_probe.cpp:522,1584` carry the same phrase „zwoelf
Adressen" and are **not** presumed wrong — those probes set only country addresses, where
twelve may be right. **A measured finding must not be widened into an unmeasured sweep by
the person who plans it.**

## Offene Fährten — 2026-09-08, fifteenth run

- **Nothing to `fertig`, nothing back. No befunde to act on at all** — a first. Five
  packages await their first verdict; `0253` awaits its second (Ruecklauf 1).
- **Lanes tonight: two, both created by this run.** `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`
  → `0258` (unlocked); `kern/src/werte.cpp` → `0260` (new). **Six slots idle, and I could
  not honestly fill them:** everything else `offen` is on `technik.md` behind `0068`, and
  `0259` is deliberately held behind `0254`. Review has five, so seven agents run.
- **One proposal, accepted, lock retargeted.** `0259` (testentwickler, out of `0257`) hung
  itself on `0257` while its own closing paragraph named `0254` as the contested one. It
  was right about the contest and wrong about the package: `0254`'s collector runs over
  `kern/test/*.hpp`, whose set today is exactly `0259`'s single file, and its acceptance
  is *the current tree passes*. Retargeted to `0254`, discharge condition written in.
- **Two whole-tree clauses narrowed, same wording as `0257` got last night:** `0258`'s
  *„At HEAD the tree passes"* and `0259`'s *„laufen unveraendert gruen"* both become *no
  failure attributable to your own file*. **This is now the fourth package in three runs
  needing it. It is not a builder habit — it is what a proposer writes when they cannot
  see the other lanes.** Consider making it the default reading rather than a per-package
  edit; that is a `CLAUDE.md` question and not mine.
- **Check first next run:** (a) all five verdicts, and whether the Review phase ran at all
  — if a second pass ends after `Uebersetzung`, the stall is structural and belongs to the
  Geschäftsführer, not to my planning. (b) `0068` `fertig` → free `0230` and `0236`,
  re-decide, do not renew down the chain. (c) `0254` `fertig` → `0259` is inert. (d) Did
  `0260` stay in comment lines only, and what did it report about line 722's claim that
  `werte_probe` re-measures the length?
- **For the Geschäftsführer, and it is new tonight and bigger than `RUECKLAUF_MAX`:** an
  interrupted pass does not degrade throughput, it **zeroes** it, because `haengt_an` only
  reads `fertig`. Five builds, no reviews, and the next pass had nothing to schedule until
  I hand-discharged a lock. `RUECKLAUF_MAX` counting befunde rather than fault stands, fifth
  run running.
- **`ops/plan.md`, ninth run:** Vorrang (0224, 0225, 0189, 0208-schritt, 0165,
  0172-weltpreis) fully discharged; „Der Engpass" still rests on `ops/reserviert.txt`,
  which reads `# frei` and has for nine runs. **The bottleneck is seven packages on
  `technik.md` behind one unreviewed head.** Not mine to edit. Reported.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` —
  no agent may write `agents/`), `0003` (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md` → ADR → Geschäftsführer.
  `werte::schaden` → `schuld` for CN/BR in `0237`'s `vermerk_abnahme`. **The `werte.cpp`
  entry is gone from this list — it became `0260`.**
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twentieth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-ninth run.** The run turned on one distinction — that a lock
  wanting *bytes present* is discharged by a commit while a lock wanting *correctness* is
  not — and on noticing that Bau and Review use separate `belegt` sets. Both came out of
  reading `baulauf.py`, not out of thinking harder about it.
