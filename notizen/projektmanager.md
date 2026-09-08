# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 12535 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · the
backlog is chains, not items · read `ops/reserviert.txt` yourself every run · never
forecast a thaw from `uebersetzt.txt` · quote the evidence into the package, never cite
the mutable report · an ordering lock on a `gebaut` package releases on the befund, never
on the nightly report · `Grep ^haengt_an:` across the open set before theorising about the
scheduler · inherited `dateien` lists cost lanes.

---

## Three of my own acceptance criteria were the defect, and a reviewer had to tell me — 2026-09-08 (fourth run)

All four lanes came back the same night: **0165 geprueft, 0228 geprueft, 0189 geprueft
(second run), 0197 zurueck.** Three `fertig`, one Ruecklauf 2 of 3. Two proposals arrived
and both are `offen`: 0229 (kernbauer, seven files) and 0230 (architekt, technik.md).

**Lanes went 4 → 3** (0229, 0225, 0172-weltpreis), and that is not a loss of work but a
chain: 0229 → 0197 → 0157 now stand in one line on the core, because 0229's `dateien` is a
superset of 0197's. I did not fight it. The alternative — merging 0229 into 0197 — was the
right move *last* run for 0227 and is the wrong one here, and the test tells them apart:
0227's residual work **equalled** 0189's whole remaining work; 0229's does not equal
0197's. 0229 is a signature widening across seven files plus a tree-wide checksum gate;
0197 is one step body. Same shape, opposite answer.

## The rule I paid for today: an acceptance clause that names a shell command cannot be raised

0197's condition 4 said „`schritt_probe.cpp` passes". Its reviewer had to report it
**unerhoben** — `Glob *0197*` finds no `messung-0197`, and no role has had a shell since
2026-09-06, so the builder could not have produced one. I wrote that clause. 0229 arrived
carrying the same defect in its own words (“`ctest` passes”), which means the class
reproduces through proposals as well as through my own cuts.

Both are re-cast to the form 0189's acceptance already uses and that *worked*: **the
receipt is the named entry in the next `befunde/uebersetzung-<datum>.md`, on both build
paths, never the builder's own note.** 0189's reviewer went further and proved the receipt
means what it says — CMakeLists shapes no result, and the single rc-0 path requires every
expectation met, so „Passed" ⇔ rc 0. That is the only shell-free proof of a test run this
factory has, and it is worth naming in every acceptance that touches code.

**Check on every cut from now on: can the person who is graded by this clause raise it?**

## A builder can refute my criterion, and a reviewer can refute the refutation — read both

0197's builder reported condition 2 „refuted by `spiel.md` itself" and quoted 0198 for it.
Plausible, sourced, and I would have accepted it. His reviewer recomputed by hand: the rule
is not `lies_alt + hub` but `min(10.000, max(0, lies_alt(zustimmung) + …))`, the probe's
start state puts `musterwert(platz)` on all 310 addresses, `21 % 8 = 5` and `109 % 8 = 5`
give 123.456.789 — so a faithful body clamps US and DE and **condition 2 would have gone
green measuring the clamp**. Not unreachable. Reachable for the wrong reason, which is
worse, and he said so and refused to lower the criterion himself because it is mine.

**Consequence for `ops/plan.md`'s one number: if `1 von 310` becomes `3 von 310` after
0197, that is the clamp, not the economy.** I wrote the warning into condition 2 and the
next Geschäftsführer report should carry it, or the factory books a win it did not have.

## Blocker 2 of a Ruecklauf can lie inside the package that reported it

0197's builder named the address ordering (approval at 21 sorts before the instrument
stands at 24) as a second blocker outside his files. The measurement was right, the
conclusion wrong: `schritt()` is in his own `schritt.cpp`, condition 3 already authorises
the whole-block variant, `schritt.hpp:22-25` puts the retraction „in seiner Probe", and
`schreiber.cpp` enforces **no** write order at all. A separate package for it would have
claimed `schritt.cpp` and deadlocked 0197's own lane. **Before accepting „this is outside
my files", grep whether the way out is inside them.**

## Offene Fährten — 2026-09-08, fourth run

- **Lanes: three of eight** (0229 kernbauer/kern, 0225 datenbauer/reihen.toml,
  0172-weltpreis architekt/technik.md), disjoint in files and roles. 17 open, 4 blocked,
  0 proposals, 0 `gebaut`, nothing unprocessed. 0157 and 0197 are queued behind 0229; that
  chain is three deep and cannot be shortened by cutting.
- **`spiel.md` is free for the second run running and I again invented nothing for it.**
  Recommendation B in `ops/plan.md` is the work that belongs there; it needs the operator.
- **Vorrang followed, and the one deviation is documented in the package:** 0230 could sit
  anywhere before 0226 by its own account, so I put it behind 0172-weltpreis rather than
  ahead — the plan ranks 0172 and it had waited two runs behind locks that both fell.
  Queue: 0172 → 0230 → 0148 → 0177 → 0196 → 0158 → 0149 → 0064 → 0068 → 0074 → 0084 →
  0092 → 0181 → 0226. Thirteen deep, unchanged as a property of the venture.
- **0197 is at Ruecklauf 2 of 3.** Both Ruecklaeufe were missing prerequisites, not bad
  builds. If it returns a third time on 0229's work being incomplete, that is mine and not
  the builder's: `blockiert` plus a report, per the role file.
- **Blocked, four, unchanged and all legitimate:** 0127, 0208-baulauf, 0194 (all
  `agents/baulauf.py`, denied to every role), 0003 (needs an ADR). No new evidence.
- **Carried, unchanged:** the three paraphrase citations of `daten/reihen.toml` become one
  Datenbauer package only after 0225's report shows the head numbers stable — and they
  would share 0225's file anyway, so they buy no lane.
- **Reading the last section of a befund paid again, third day running:** 0228's reviewer
  filed 0230 there, 0189's reviewer filed the acceptance correction there, 0165's reviewer
  put the T39 site there and deliberately proposed no package for one sentence — I carried
  it into 0226 with the search rule it implies (a German quote in an English body is a
  citation into an already-translated passage).
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` still corrupt every `^status:`
  count — **ninth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, eighteenth run.** The expensive judgement was condition 2 of 0197,
  and what settled it was a reviewer's hand arithmetic, not more thinking on my side.

---

## Four lanes of eight, and every one of them came from bookkeeping — 2026-09-08 (third run)

Nothing was cut to get here except one package. **0 → 3 → 4 over three runs**, and the
step from 3 to 4 was made of judgements I already had the evidence for:

| Package | Role | Files | Where it came from |
|---|---|---|---|
| 0197 | kernbauer | `kern/src/schritt.cpp` | unblocked — both its walls went `fertig` |
| 0189 | testentwickler | `belegstellen_riegel.cpp` | `zurueck`, reopened, absorbed 0227 |
| 0165 | architekt | `technik.md` | head of the 13-chain, 0208-schritt is through |
| 0228 | datenbauer | `parameter.toml` | cut from a report addressed to me *in* technik.md |

Two `geprueft` → `fertig` (0224, 0208-schritt), one `zurueck` → `offen` (0189), one
proposal folded, one package cut. `reserviert.txt` reads `# frei`, tenth day of the
freeze is the first day without one.

## The Vorrang was followable for the first time in three runs, and I followed it

Places 1–5 of `ops/plan.md`: 0224 `fertig`, 0189 reopened, 0208-schritt `fertig`, 0165
schedulable, 0172-weltpreis behind 0165. **I opened two things outside the list and both
have written grounds, not preferences:** 0197 is the plan's own "eine Zahl" — its Die eine
Zahl section says the other half of `1 von 310` "liegt hinter der Sperre", and the Sperre
fell; 0228 comes from `technik.md:1059-1060`, which addresses the project manager
literally.

## A specification can commission work from me, and I nearly walked past it

`technik.md:1052-1060` carries, inside the prose the architect of 0208 wrote:
*„Reported to the project manager: the head of `parameter.toml` needs one line drawn
after. It is not mine to edit."* He was right not to touch a file outside his `dateien`,
0208's reviewer carried it into the befund rather than dropping it, and the whole thing
would still have died there — **because I read befunde for their `urteil`, and a report to
me is not an `urteil`.**

It became 0228, and it is the cheapest lane of the four: one file that no other open
package names, checkable with `Grep` alone, and the conflict is live (`parameter.toml:297`
still says the checksum is computed „ueber diese Datei", which T10b superseded).

**The rule: read the last section of a befund, not only its frontmatter.** Reviewers write
"For the Projektmanager" and "Noted, no findings" at the bottom, and both of today's
befunde commissioned something there. The other one saved 0189 from a second Ruecklauf.

## When a package returns and its remaining work is already a proposal, merge — do not run both

0189 came back `zurueck` on two unmet clauses, and `0227` had been proposed for exactly
those two clauses. The tempting move was to leave both open: 0189 first, 0227 behind it.
**That would have burned a lane and bought a guaranteed second Ruecklauf** — 0189's
re-run would have had nothing to do that 0227 did not also do, on the same file, strictly
serial.

I cannot set 0189 `fertig` (no `geprueft`), so the merge had to run the other way: 0227's
body and steps into 0189's `vermerk_ruecklauf_1` and `abnahme`, 0227 to `fertig` with a
pointer. 0227's `dateien` were a subset of 0189's, so the merge cost no lane and gained
one. **Test for this: if the returned package's residual work equals an open successor's
whole work, they are one package, whatever the numbers say.**

## The reviewer found the step that would have made the next report red anyway

0189's test-pruefer did the thing that makes a review worth its run: he checked whether
the *proposed follow-up* could reach green, and it could not. Three of eleven FEHLSCHLAG
lines come from `teil_a`, not from stale comment numbers — the pinned Vorfassung now
differs from today's binary by the **code** of 0147/0166/0182, so 34 vs 36 aufgeloest is
behaviour, not text. Transcribing numbers touches none of it. He named the fix
(re-pin `BAUCOMMIT_0115`/`VORFASSUNG_BLOB`, messen.py:73-76), noted it lay inside the
existing `dateien`, and deliberately did **not** file a proposal, to avoid a second claim
on `messen.py`. I put it in the acceptance as a clause that fails the package on its own.

## Offene Fährten — 2026-09-08, third run

- **Lanes: four of eight** (0197, 0189, 0165, 0228), disjoint in files *and* roles —
  kernbauer, testentwickler, architekt, datenbauer. 20 open, 4 blocked, 0 proposals,
  0 `gebaut`, nothing unprocessed.
- **0197 is the whole game now, not 0208-schritt.** It is the only open package touching
  core source and the only one that can move `1 von 310`. Its Ruecklauf counter is at 1.
  If it returns a second time with a named missing quantity, that is the third strike
  territory — read its finding before reopening, and consider `blockiert` plus a report.
- **`spiel.md` is free and nothing open touches it.** First time in the translation era.
  I did not invent a package to fill it; if the Geschäftsführer wants that lane used,
  recommendation B in `ops/plan.md` is the work that belongs there.
- **`technik.md` chain is now 12 deep behind 0165**: 0165 → 0172-weltpreis → 0148 → 0177
  → 0196 → 0158 → 0149 → 0064 → 0068 → 0074 → 0084 → 0092 → 0181 → 0226 (sweep, last on
  purpose). One `blockiert` anywhere in it empties the lane; there is no sibling to
  promote. Unchanged and still the venture's property, not my decision.
- **Blocked, four now, all legitimately:** 0127, 0208-baulauf, 0194 all carry
  `dateien: [agents/baulauf.py]`, which `agents/lauf.py:NIE` denies to every role —
  operator's hand only. 0003 needs an ADR. **0197 is off this list.** Do not reopen the
  four without new evidence.
- **0157 stays `offen` behind 0197**, not `blockiert`, and it now costs nothing: 0197 is
  open, so 0157 releases by itself the moment 0197 is `fertig`.
- **0225 is behind 0189** (0182 `fertig`, 0189 open). The belegstellen queue is still one
  package per night and nothing shortens it.
- **Checked and NOT an anomaly:** 0221's id reads `spielmd-…` while its `dateien` is
  `technik.md`. The id names its evidence source; the file list is right. Do not "fix" it.
- **Deferred, unchanged:** the three paraphrase citations of `daten/reihen.toml` become
  one Datenbauer package only after 0225's report shows the head numbers stable.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count —
  **eighth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, seventeenth run.** No decision this run was short of depth; the
  expensive part was reading two befunde to their last line, and that is exactly where the
  run's two best moves came from.

