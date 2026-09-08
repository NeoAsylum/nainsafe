---
typ: pruefung
paket: 0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: every one of the ten places recomputed from R = 20 with the document's own formulas, the second-pass list reproduced by grep in both number formats, the protocol marking read in place
befunde: 0
---

# Review 0064 — all three conditions met

All line numbers are today's (`technik.md`, after the 0064 build).

## Condition 1 — the ten places, each recomputed from R = 20

1. **Frontmatter `nachtlauf` (:21).** From the document's own formulas: Maß 1 per seed
   `30·R(R+1)/2 + R` (:900) = 6.320, ×50 = 316.000; Maß 2 = 126×20×(R×61) = 3.074.400;
   Maß 3 twice that; +200.000 +200 +20 +20.000 = **9.759.420**. ×10 µs = 1,63 min,
   ×50 µs = 8,13 min. Matches.
2. **T22 (:1598-1599).** R world steps × 10 µs = **0,20 ms**, written as formula. ✓
3. **T37 — disputed, stays 31, and rightly.** Verified against :1956-1959: `L_R = 4`,
   `S = 3`, `n = 1`, reported = `L_R(S+5)−n` = **31**, target = `L_R(S+4)−n` = **27**,
   both named side by side (:2843-2846, :1852-1854). Neither is formed from R; the
   proposal's row 3 (mine, 2026-09-04) predates 0221's clarification and was wrong. The
   builder named the correct value with grounds, exactly as the package's acceptance note
   prescribes.
4. **T44 third line (:2656-2658).** Formula `(R+1) × 1.000`, at R = 20 **21.000**. ✓
5. **T44 band (:2691-2703).** `21.000 ≤ B ≤ 24.000`, mandate band to `R × 1.000` =
   20.000, death band 31.000 R-independent, gap edges 23.001 → 24.001; the added claim
   "disjoint up to R ≤ 26" checks out ((R+1)·1000+3000 < 31.000 ⇔ R < 27).
6. **T44 cost note (:2753-2758).** `R×61` = 1.220; `60·210+20` = **12.620** with
   Σ(R+1−t) = 210; 12.620/1.220 = 10,34 → "around ten times". "Zwölffache" gone. ✓
7. **T35 bullet (:2770-2771).** `R × 61`, at R = 20 **1.220**. ✓
8. **Section 10, eight cores (:2995-2999).** 9.759.420×10 µs/8 = 12,2 s; ×50 µs/8 =
   61,0 s ≈ 1,0 min. The table above stays R = 24 and says so, with pointer to §29. ✓
9. **Section 10, Python counter-calculation (:3017-3023).** ×0,75 ms = 2,03 h,
   ×3 ms = 8,13 h → **2,0 to 8,1 h**; the conclusion (factor decides) preserved. ✓
10. **Section 12, depth 2 (:3073-3078).** `R×(1+60×61)` = 20×3.661 = **73.220**;
    3×126×20×73.220 = 553.543.200 ≈ 554 M; 5.535 s = 1,5 h; /8 = 11,5 → "around 12 min";
    ×5/8 = 57,7 → "around 58 min". The two values the proposal did not name are correct.

Formula-in-R clause: places 2, 4, 5, 6, 7, 10 carry the formula with an "at R = 20"
example; 1, 8, 9 are labeled "at R = 20". T40's example column stays "at R = 24" — it is
a row of the `spiel.md` catch-up table (group A), not this package.

## Condition 2 — second pass evidenced (§29, :5273-5362)

Reproduced by grep in **both** number formats (dots and commas): `18.024`/`87.864` have
zero governing occurrences; `1.464`/`9.024` hit only frontmatter `partie` (:13), T40's
example column (:899-900) and section 10's table+recount (:2973-2988) — exactly group A;
`11.519.040`/`11.783.264` only in section 10 + calibration loop (:3008), section 13
(:3174-3175), §15/§16 (:3298-3299) — groups A/B. Every `R = 24` hit falls into a named
group or one of the five reports (:892, :2518, :2549, :2552, :2967, :4317, :4388). 1997
spot-checked: two hits (:535, :1693) are covered categorially by the T24/window reason
(group A, report 4) rather than named individually — the reason holds, so no finding.

**One caveat, no Befund:** §29's check clause (:5359) "`Grep` for `18.024` and `87.864`
in this file gives zero hits" is falsified by its own enumeration — 3 lines inside §29
itself contain both values. Whoever reproduces it literally gets those hits. One phrase
("outside this section") would make it exact.

## Condition 3 — protocol marking (:3170-3182)

Rule line, one statement of which state holds below (R = 24, window 1997–2021,
11.519.040/11.783.264), dated and signed "package 0064, condition 3". §14-16 content
untouched — old numbers verified in place (:3298-3299). ✓

Scope discipline confirmed: the report-1/2/3 places (:2518, :2549-2552, :4317 ff.) still
carry R = 24 — reported, not reached for, as the release note demanded.
