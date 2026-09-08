---
typ: pruefung
paket: 0084-reihenliste-zeile-20-und-t53-selbstmessung
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all four conditions reproduced in place, including a third independent retrieval of both World Bank series and exact recomputation of all 25 derived terms
befunde: 0
---

# Pruefung 0084 — geprueft, 0 findings

**Condition 1 — row 20 and the `frei` decision.** Row 20 stands in the section-7 list
(`technik.md:2043`), verbatim identical to the handed-over row in section 17 (`:3636`).
The sentences under the table still say the same: reported series rows 1, 2, 8, 9, 10, 11,
4+12+4+4+3+4 = 31 (recounted); trade block row 14 its own block; four quantities without
data anchor rows 17, 18, 19 + financial-market regulation (`:2046-2054`). The `frei`
question is decided, not parked (`:2063-2070`): Role-column `frei` = T37 class, licence
verdict lives in T62 / `lizenzurteil` only. Its six-row check is exact against T62
(`:4502-4516`): rows 8, 10, 14 carry `frei` in both columns; 3, 4, 15 in T62 only and are
`start` in section 7. `lizenzurteil` exists in `daten/reihen.toml` (24 hits).

**Condition 2 — the 25 index values, from the source.** I retrieved both Data360 endpoints
myself on 2026-09-08 (v2 host not tried, per §32 report 1). 2018: CD 25.213.271.645.387,152
/ KD 23.890.905.014.631,023 — digit-identical to `:5690`; 10.000·CD/KD = 10.553,5021, above
the half, rounds to 10.554 per T6; the table carries 10,554 (`:522`). Recomputed from my
retrieval: 1997 → 7.417,42 → 7.417; 2015 → 10.000; 2021 → 11.548,76 → 11.549 — all match.
Changed values: one, named individually (2018), in §17 (`:3578-3581`) and §32.

**Condition 3 — derived numbers.** Recomputed all 25 terms `10.000·|7.417−Index(t)|/Index(t)`
exactly from the table integers: every 2-dp term in §32's table reproduces; unrounded sum
55.075,1978 → 55.075,20; display sum 55.075,21; mean 2.203,008 → 2.203; old-table sum
55.074,53 (confirms §32 report 4 against run 3's 55.074,54). Right edge 3.577,80 → 3.578,
r(2021) = 11.549/7.417 = 1,5571, start factor 1,34825 recomputed; durchgriff 7.837 / 6.189
expressly declared unchanged with reason (`:3588-3592`).

**Condition 4 — self-measurement.** The old sentence is quoted as struck (`:3572`) and
replaced by two precise statements (`:3594-3598`): derived numbers in two independent runs,
25 index values in two independent retrievals (2026-09-04 / 2026-09-08). §32 `:5697-5703`
names why the second path could not find the error (it consumes the table it checks).

**Vermerk-5 duty (six numbers).** §32 `:5727-5734` states none moved, with remeasured 27
and 31; T55 verified verbatim: target series `L·(S+4) − 1` = 27 (`:3815`), position slots
`L·(S+2)` = 20 (`:3808`). No formula in section 19 touched.

**§32's own self-check reproduced:** grep `10[.,]55[34]` file-wide = 8 hits; the old value
appears only inside correction sentences of §17/§32 (`:3579`, `:3584`, `:5690-5691`,
`:5770-5771`), never in a table cell.

**Sampling limits.** No git diff available: untouched-ness of T47/T48/T50/T5/preamble rests
on targeted greps (no `10,55x` or row-20 hits there; preamble `:46` unchanged) and §32's
scope statement, not on a line-by-line diff. Of the 25 index values I re-derived 4 from my
own retrieval (1997, 2015, 2018, 2021 — the corrected one and the two the derived numbers
hang on); the other 21 rest on the builder's two documented retrievals plus the exact
closure of all 25 derived terms.
