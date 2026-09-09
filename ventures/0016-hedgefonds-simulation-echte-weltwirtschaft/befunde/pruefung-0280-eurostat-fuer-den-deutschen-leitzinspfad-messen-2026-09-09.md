---
typ: pruefung
paket: 0280-eurostat-fuer-den-deutschen-leitzinspfad-messen
pruefer: daten-pruefer
datum: 2026-09-09
urteil: zurueck
kriterium_geprueft: every row of §1 and §2 re-requested against the live Eurostat API and counted off the raw JSON-stat `value`/`status` objects, not off a summary; quotes, licence and DOI re-retrieved separately
befunde: 4
---

# Two rows count missing-value flags as values

Condition 1 names „the **count of window years actually returned**". Rows 6 and 7 report
**12**; the answer is **0**. Both are German money-market series that end in 1998.

## 1. Rows 6 and 7 — the count is inverted (fails condition 1)

Reproduce, 2026-09-09:

1. GET `…/1.0/data/irt_h_ddmr_a?format=JSON&lang=en&geo=DE&sinceTimePeriod=1990&untilTimePeriod=2021`
2. `time` index: `{"1990":0,…,"2014":24}`
3. `value`: **9 entries, indices 0–8** → 1990–1998. Last German value 1998 = `3.41321`.
4. `status`: `{"8":"d","9":"m","10":"m",…,"22":"m"}` → indices 9–22 = **1999–2012**, `m` = missing.
5. `extension.positions-with-no-data.time`: `[23,24]` → 2013, 2014.
6. Window 2001–2021 is indices 11–22. Every one carries `m` and no value → **0 window years.**

`irt_h_mr3_a`, same call: structure byte-identical, last value 1998 = `3.51907`, `status`
9–22 `m`, no-data `[23,24]` → **0**.

The 12 is the count of `m`-flagged in-window positions (2001–2012). `m` marks the absence
of a value. The stated reason is inverted too: 2013/2014 carry **no** status entry — they
are the `positions-with-no-data` — and the `m` flags sit on 1999–2012. „Series ends 2014"
is the time index; the data ends 1998.

These are the only two rows where a series stops before the window and Eurostat pads the
index with `m`; rows 5 and 9 also start late or stop early, carry no `m`, and are correct.

**It contradicts the file's own §5**, which says Germany „has no separate money market"
from 1999 — exactly why these two series stop in 1998. The table denies it, and the table
is the countable part a follow-up package reads.

## 2. Outside the acceptance, same file, worth fixing while it is open

- **§3, the 21 values are rounded 5→3 decimals, unmarked.** Source `irt_st_a` EA `IRT_DTD`:
  `2001 = 4.38720 … 2021 = -0.48270`. All 21 match the file to 3 decimals, but the minimum
  handed to the follow-up is **-0.4827**, not `-0.483`. §5 does not name the rounding.
- **§2 row 8: „carries 421 observations"** is the dataset-wide total. `irt_h_cgby_a` for
  `geo=DE` returns **26** (1973–1998). „None fall in the window" is correct.
- **§3 the EONIA quote is truncated without an ellipsis.** The sentence continues
  „…in the interbank market**, initiated within the euro area by the contributing panel
  banks**". The omitted clause supports §5's `geo=EA`-is-not-Germany caveat.

## 3. What I checked and what holds

Everything else reproduced. Rows 1 (`irt_st_a` DE: empty `geo` index, empty `value`), 2
(105 values = 5 `int_rt` × 21 years, gapless; `IRT_DTD` = „Day-to-day rate"), 3
(`irt_lt_mcby_a` DE: 21 values, no gap), 4 (empty `geo`), 5 (index starts 2004 → 18), 8,
9 (index 1999–2004 → 4 in window), 10 (`ei_mfir_m`: exactly 6 indicators, labels verbatim).

§1 row 1 reproduced exactly: **27 entries**, of which **8** are `_a`, and all 8 are queried.
`irt_h_eurcoe_d` is daily-only as stated — and is „Euro yields - coefficients", not a policy
rate, so §3's „deposit facility and MRO appear in no `irt` dataset" holds.

Condition 2: the `irt_st_esms.htm` quotes are verbatim and the document calls the series a
policy rate nowhere. Condition 3: `daten.md:195-198` and `:203-208` quoted exactly, the live
notice's exception list matches, `https://doi.org/10.2908/IRT_ST_A` → **302** →
`…/databrowser/product/page/IRT_ST_A`. Condition 5: `[Ee]urostat` over
`daten/quellenbefund-leitzinspfad.md` = zero hits, and the occurrence map in
`daten/reihen.toml` matches the pre-edit copy in `befunde/messung-0069/baum/` under a
uniform line shift — nothing written there.

**The headline result survives**: no policy rate in Eurostat, a gapless euro-area
money-market rate 21/21, licence permitting, attribution nameable. Only the two counts and
their reason cells are wrong.
