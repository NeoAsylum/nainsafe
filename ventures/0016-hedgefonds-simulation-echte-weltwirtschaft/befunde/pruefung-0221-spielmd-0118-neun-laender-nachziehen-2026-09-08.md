---
typ: pruefung
paket: 0221-spielmd-0118-neun-laender-nachziehen
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "all five acceptance clauses replayed with Grep/Read only; every 16/2/31/27 hit in T37 and section 7 checked against its formula or wave sentence"
befunde: 2
---

# Pruefung 0221 — one reading of the country count

Builder chose the acceptance's second branch: `L_R = 4` stays binding, on `spiel.md`'s
own sentence, with the horizon as three named conditions (technik.md:4914–4928). Checked
clause by clause; ~12 greps, 7 small reads, neither spec opened whole.

## Clause 1 — one reading, not two: HOLDS

Section 26 (technik.md:4895–4978) names the binding reading with the dated quote
"`L = 4`, `L_R = 4` and 310 continue to hold" — verified verbatim at spiel.md:3325
(English there now; quote matches current language, read 2026-09-08). Every count in
T37 is now a formula in `L_R, S, n` with today's evaluation beside it
(technik.md:2748–2788); T59 carries the `L_R = 7` column and all evaluations reproduce:
28 = 3·7+6+1, tolerance 3 = ⌊7/2⌋, 48 = 7·7−1, 55 = 7·8−1, 112 = 8·7·2, mask
328 = 7·27+22+112+2+3 (:3830–3837). The horizon's counterexample also computes:
`L_R = 6` → 24 subjects, tolerance 3. technik.md frontmatter carries only address
geometry (310), which spiel.md:3325 expressly holds until 0116 — no second reading.

## Clause 2 — grep 16, 2, 31, 27 in T37 and section 7: HOLDS

Grep tool, `\b(16|27|31)\b` and `[Tt]oleran[cz]` over technik.md, hits filtered to
T37 (2742–2789) and section 7 (1598–2009). Every hit is either (a) a formula evaluation
with `L_R = 4` named beside it (:1646–1649, :1849–1851, :1954–1956, :2767, :2779,
:2782–2784), (b) address geometry backed by T15 and held by spiel.md:3325 (:1631,
:1643), or (c) wave-2 marked with its pointer to 0068 (:1649, :2786–2788). Section 7
has no tolerance mention at all. The wave question from the vermerk is answered in a
table (:4944–4947); wave 2 is marked, not repaired — 0068 keeps its subject.

## Clause on dated quotes: ONE MISS — finding 1

Three spiel.md quotations stand in the built text. :2764–2767 and :4907–4912 carry
"read 2026-09-08" and both verify verbatim (spiel.md:3333 and :3325). The third,
*"An expectation with a condition, not a determination"* at technik.md:4924, carries
**no read date and no anchor**. It is a real quote — spiel.md:3330, T58 row, verified
2026-09-08 — so no drift damage exists today, and the section's other quote dates the
same run. Judged not blocking because the clause's function (traceability under
translation) is met by this befund's anchor and the repair is one parenthesis, not a
build: candidate one-liner for the next technik.md package, or 0068, which already owes
wording at adjacent places. If the PM weighs his appended clause stricter, `zurueck` is
the call to make when pulling the status.

## Clause on reihen.toml: HOLDS

`daten/reihen.toml` untouched: `sollreihen_gesamt = 27` (:456), `gesamt = 16` (:504),
`toleranz = 2` (:510) all still stand; the follow-up is named at technik.md:4956–4960.

## Finding 2 — to the project manager, not the builder

The acceptance's first branch says "the Sollreihen count that follows from
`L_R(S+3) − n`". That formula gives 23/41 — the **free** series count (spiel.md's
"16 aus 23 / 28 aus 41"). Sollreihen are `L_R(S+4) − n` = 27/48 (reihen.toml:456,
T59 :3825). Dormant here because branch two was taken; if a future package exercises
branch one against this wording, it pulls the wrong count.

## Searched and not found

A second reading in technik.md's frontmatter or T59; a digit of the nine-country
reading standing as today's state (grep 28/48/55/112/328 — all sit in formulas or the
`L_R = 7` column); an invented stufe-4 rule (pre-exists: technik.md:4304, :4047,
MFS_IR route :4281); an undated edit in sections 7/19/20 (markers at :1649, :3603,
:4063 all dated 2026-09-08).
