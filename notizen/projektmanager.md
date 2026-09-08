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

