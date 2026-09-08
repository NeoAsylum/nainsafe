---
typ: pruefung
paket: 0196-t61-regel-5-sieht-die-ausschluesse-in-den-sollreihen-nicht
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Ruecklauf 1 — all three zurueck findings verified fixed at HEAD, conditions 1-5 replayed (~9 greps, 5 section reads, neither spec opened whole)
befunde: 0
---

# Pruefung 0196, run 2 (Ruecklauf 1) — geprueft

Run 1 is `pruefung-0196-...-2026-09-08.md` (same date, hence the `-2` suffix). All three
findings answered; no new ones.

## The blocking finding (condition 1) is fixed

The T61 preamble sentence that said the class is decided *solely* by the three
`politikpfad` series is gone. `technik.md:4016-4017` now reads: the three series "carry
**condition a of the class rule and nothing beyond it** — since package `0196` the class
is formed from two sorts of series, and rule 5 below is the only place that says which."
Rule 5 (`:4047-4062`) remains the single site: three conditions a/b/c, each with the
series sort it is measured in. `Grep -n "solely"` over technik.md: 4 hits (`:446`,
`:716`, `:1301`, `:1641`), none about the class. T61 no longer says it twice.

## Finding 2 (grep-c clause) is fixed, and the numbers reproduce

`:5115-5120` now says: `grep -c` counts **lines**, 33 at start, **48** at end; a
match-counting tool gives one more at either end, **49** today, one line carrying two.
Measured at HEAD: `Grep count 'T6[0-2]'` = **48** lines; with `-o` = **49** matches;
the double line is `:4166` (T61+T62, was `:4165` pre-fix). Reconciliation exact and
unchanged from run 1: section 27 has 9 match-lines, rule 5 has 7 (6 new + retained T60
lock `:4062`), outside both 33. The claim "all fifteen new lines lie in rule 5 (six)
and this section (nine)" holds: 33 + 15 = 48.

## Finding 3 (PM's decision) is executed

`:5105-5113`: the disclosure paragraph now names **four** clauses outside T61, the
fourth ("exactly when" → "already when" in section 26, now `:5011-5012`) with place, old
wording, cause, and the PM's 2026-09-08 weighing. Same form as the three from the
acceptance list.

## Conditions 2, 4a, 4b, 5 — spot-checked, none regressed in the rebuild

- **2:** abort bound inside rule 5 (`:4059`); divergence report names country, both
  classes, which of a/b/c, and the series measured (`:4114-4116`); probe SAU + SAMA
  stage 1 written out (`:4119-4134`), derived play-only = manifest, build runs.
- **4a:** `:4859` in past tense ("did not occur … before this package"); `partie.runde`
  before section 25 today: `:1420`, `:1428`, both in T18b.
- **4b:** `:1422-1425` — section 25 "deliberately holds open" the bounds of the other
  three, *that* not *which*.
- **5:** `:5008-5010` carries anchor + "read 2026-09-08"; quote verbatim at
  `spiel.md:3330` (T58 row) at today's HEAD — re-checked because `spiel.md` left
  `ops/reserviert.txt` on 2026-09-07; it has not moved under the quote.

## Condition 3 (nothing outside T61 moves)

Total T6x matches 49 = run-1 count; the three fixes sit in the T61 preamble, section
27's check clause, and section 27's disclosure — all inside the package's own two
sites. Document preamble intact: `:46` "The prescriptions are numbered **T1** through
**T53**", T60-as-example `:56` — 0082/0084/0181 keep their anchor. Note for the next
reviewer: a literal grep for "numbered T1 through T53" returns nothing because of the
bold markers; grep "through **T53**" or read `:46` before calling the preamble changed.

Searched, found nothing: a remaining "solely"-type class sentence anywhere; a T6x token
in the three fix sites beyond the reconciled 15; movement under the `spiel.md` quote.
