---
typ: pruefung
paket: 0068-technikmd-reihe-9-ohne-sollrolle
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all four conditions verified in place — file-wide greps in both languages, every count recomputed from the L_R formulas, §29 reconciled line-for-line against the 0064 review
befunde: 0
---

# Review 0068 — all four conditions met

Line numbers are today's, after the 0068 build. New section 30 (:5400-5477) documents the change.

## Condition 1 (as corrected 2026-09-04) — no place leads series 9 as target, counts recounted

- **Place 1, series list row 9 (:1945):** role column reads `start + policy path`. No `Soll`/target in the row.
- **Place 2, class table T37 (:2836-2843):** exactly two rows, `frei` and `abgeleitet`; the sentence below says the row is "gone, not set to zero".
- **Place 3, preamble (:2805-2826):** the old by-construction observation stands, followed by what replaces the class (see condition 3).
- **Recounted, not taken over:** at `L_R = 4, S = 3, n = 1`: frei `L_R(S+3)−n` = 23 (19 independent = `L_R(S+2)−n`), abgeleitet `L_R` = 4, sum `L_R(S+4)−n` = 27; check-subject table 4+4+4+3+1 = 16; reported `L_R(S+5)−n` = 31 = 4+12+4+4+3+4 (:1958-1959). **No difference** to the package's or 0065's numbers, so no difference statement was owed.
- **File-wide:** `Grep gesetzt` gives, outside section 30, six lines at five places (:2811, :2843, :2878, :2880, :4286+:4291) — exactly the five that section 30's own check clause (:5470-5474) enumerates, and each says the class fell. No table row carries `gesetzt` with the policy rate except the marked "before" column of section 30's change record (:5411-5412), which records the defect and does not carry the role. Also swept in English ("policy rate", "target"): row 9's line and section 21's data table (:4371) are clean. The four second-wave corrections check out in place: content list point 2 (:1648-1654, filename reason included), sentence below the series list (:1957-1963, names the invariant), section 17's row-20 sentence (:3499, now "31 **reported** series ... rows 1, 2, 8, 9, 10 and 11" — true, matches :1958), T59 label (:3969, "target + policy rate", formula unchanged).
- Stale-but-disclosed records in sections 19/20 (:3714, :4291 — present-tense "untouched") are other packages' records, named in section 30 report 3; they give row 9 no role. No finding.

## Condition 2 — 16 and tolerance 2 untouched, with the why

Both stand as the formulas 0117/0221 left: `3·L_R+(L_R−n)+1` and `⌊L_R/2⌋` with evaluations 16 and 2 (:2847-2852, :2866-2867) — the state found at start, per the 2026-09-05 vermerk. The why-sentence stands at :2875-2884: series 9 never entered a check subject because it carried `gesetzt` and was error-free by construction; the `spiel.md` quote beside it is genuine (spiel.md :2819, wraps across lines — a plain grep misses it).

## Condition 3 — the preamble says what takes the class's place

:2811-2826: invariant instead of error measure — "checked **harder**, not less", any deviation at a support point is a hard error, not a 300-bp measure; still reported; costs no check subject, enters no tolerance; enforcer named (backtester, check 8) and the enforcement gap reported, not hidden (section 30 report 1). Quote verified at spiel.md :2763. Wording is the builder's own.

## Condition 4 — §29's check clause

The phrase sits inside the line: :5395 "in this file outside this section". No new line: the clause paragraph is still four lines (:5395-5398); §29's body shifted uniformly +36 (heading :5273→:5309, clause :5359→:5395) from 0068's insertions above it, and the one extra line in the section span is the blank separator before the new section 30 heading. Groups A-D, the five reports and the S-collision note (:5340-5391) match my 0064 review verbatim — no number, no enumeration line touched. The amended claim is now true: `18.024`/`87.864` hit only :5349, :5350, :5395, all inside :5309-5399. The second clause's analogous defect (`1.464`/`9.024` "only in group A") was reported to the PM (section 30 report 4), not fixed — exactly the vermerk's boundary; it mirrors my 0064 caveat and needs the same one-phrase repair.

## What I searched and did not find

A remaining target role for series 9 (greps on `gesetzt`, `Leitzins|policy rate`, `Soll`, row-9 table lines, both number-word languages), a touched 16/2, an undisclosed edit in §29. Nothing.
