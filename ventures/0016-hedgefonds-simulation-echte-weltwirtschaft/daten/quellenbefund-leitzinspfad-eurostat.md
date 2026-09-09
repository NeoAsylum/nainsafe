---
typ: quellenbefund
gegenstand: Reihe 9 (Leitzins) -- Eurostat for the DEU / euro-area side, window 2001-2021
paket: 0280-eurostat-fuer-den-deutschen-leitzinspfad-messen
datum: 2026-09-09
ergebnis: kein Leitzins, aber ein lueckenloser Geldmarktzins fuer den Euroraum ueber 21/21 Fensterjahre
---

# Eurostat carries no policy rate — and a gapless money-market rate for 2001–2021

Measured 2026-09-09 against Eurostat, source no. 7 of
`specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md:193`. Window **2001–2021**,
annual, 21 support points (package `0054`). Every endpoint below is free: no account, no key.

Data endpoint, identical in form for every row:
`https://ec.europa.eu/eurostat/api/dissemination/statistics/1.0/data/<code>?format=JSON&lang=en&geo=<GEO>&sinceTimePeriod=2001&untilTimePeriod=2021`

**This package closes at most the German side.** `daten.md:203-208` excludes non-EU/EFTA
countries from commercial reuse, so Eurostat cannot answer CHN by construction. China's
route inside the vetted sources stays way 2 of `daten/quellenbefund-leitzinspfad.md:163-166`
and is an architect's decision, not this file's.

## 1. How the codes were enumerated

Not from memory. Four catalogue routes were tried; **one returned a complete listing.**

| # | Request | Status | Result |
|---|---|---|---|
| 1 | `.../api/dissemination/files?dir=data&sort=1&start=irt` | 200 | **complete, 27 entries** — the `irt` family, machine-generated bulk-file index |
| 2 | `.../api/dissemination/catalogue/toc/txt?lang=en` | 200 | truncated by the fetch tool at ~1,839 lines, never reaching the `irt` branch — **not usable as an enumeration** |
| 3 | `.../api/dissemination/sdmx/2.1/dataflow/ESTAT/all/latest?detail=allstubs` | 200 | truncated mid-element at `LFSQ_EWHAN2` — **not usable** |
| 4 | `.../eurostat/web/interest-rates/database` | **404** | — |
| 5 | `.../eurostat/cache/metadata/en/irt_esms.htm` | **404** | — |

Row 1 is the enumeration this file rests on. Its 27 entries hold **8 annual datasets**
(`_a`); all 8 are queried below. The monthly, quarterly and daily variants are not queried —
the window needs annual values. `irt_h_eurcoe_d` is daily-only and has no annual variant.
Outside the `irt` family, `ei_mfir_m` was probed for its indicator list (row 11).

## 2. Every request made

Retrieval date **2026-09-09** on every row. „Window years" = distinct years in 2001–2021
carrying a non-null value.

| # | Dataset code | Catalogue title | geo | Status | Window years | Reason where short |
|---|---|---|---|---|---|---|
| 1 | `irt_st_a` | Money market interest rates - annual data | DE | 200 | **0** | `geo` dimension comes back with no category — Germany is not a reporting unit here |
| 2 | `irt_st_a` | Money market interest rates - annual data | EA | 200 | **21 / 21** | — gapless, per each of the 5 `int_rt` categories |
| 3 | `irt_lt_mcby_a` | EMU convergence criterion series - annual data | DE | 200 | **21 / 21** | — gapless, but a bond yield (§3) |
| 4 | `irt_lt_gby10_a` | Government bond yields, 10 years' maturity - annual data | DE | 200 | **0** | `geo` not indexed for DE |
| 5 | `irt_euryld_a` | Euro yield curves - annual data | EA | 200 | **18** | series starts 2004; 2001–2003 absent |
| 6 | `irt_h_ddmr_a` | Day-to-day rates for euro area countries - annual data | DE | 200 | **12** | series ends 2014; 2013 and 2014 carry status `m` |
| 7 | `irt_h_mr3_a` | 3-month rates for euro area countries - annual data | DE | 200 | **12** | series ends 2014; 2013 and 2014 carry status `m` |
| 8 | `irt_h_cgby_a` | Central government bond yields - annual data | DE | 200 | **0** | series runs 1973–1998, entirely before the window |
| 9 | `irt_h_euryld_a` | Euro yield curves - annual data | EA | 200 | **4** | time index ends 2004 |
| 10 | `ei_mfir_m` | Interest rates - monthly data | DE | 200 | n/a | probed `2020-01`–`2020-03` for its `indic` labels only (§3) |

Rows 1 and 4 are answers, not absences of the quantity: the query returned 200 with an empty
`geo` index. Row 8's series exists and carries 421 observations; **none** of them fall in the
window.

## 3. What the found series measures — quoted, not inferred

**No dataset reached above is a central-bank policy rate.** The ECB's deposit facility and
main refinancing operation appear in none of the `irt` datasets, and `ei_mfir_m` (row 10)
carries exactly six indicators, all market rates:

> Day-to-day money market interest rates (average); 3-month interest rates (average); Euro
> yields - 1 year (average); Euro yields - 5 years (average); Euro yields - 10 years
> (average); Long term government bond yields - Maastricht definition (average)

**The one gapless candidate is row 2, `irt_st_a`, category `IRT_DTD` („Day-to-day rate").
Eurostat's own metadata (`cache/metadata/en/irt_st_esms.htm`, retrieved 2026-09-09) says
what it is:**

> „The rate is the EONIA (Euro OverNight Index Average), the effective overnight reference
> rate for the euro, computed as a weighted average of all overnight unsecured lending
> transactions in the interbank market"

and on the supplier:

> „Figures for the EU Member States, United States and Japan are collected by the European
> Central Bank and transmitted to Eurostat by electronic means."

So the concept is a **money-market rate**, the third of the four the package named — an
interbank market price computed by the ECB, not set by it. The same file does not call it a
policy rate anywhere. The 21 values, euro area, `IRT_DTD`, annual:

`2001: 4.387 · 2002: 3.287 · 2003: 2.318 · 2004: 2.049 · 2005: 2.088 · 2006: 2.834 ·
2007: 3.866 · 2008: 3.870 · 2009: 0.708 · 2010: 0.438 · 2011: 0.871 · 2012: 0.229 ·
2013: 0.089 · 2014: 0.094 · 2015: -0.108 · 2016: -0.320 · 2017: -0.355 · 2018: -0.363 ·
2019: -0.392 · 2020: -0.462 · 2021: -0.483`

**Seven of the 21 are negative.** Whoever carries this into series 9 carries a signed path;
`T51` computes `aufschlag_min` from the minimum of the path
(`daten/quellenbefund-leitzinspfad.md:165-166`), and that minimum is **-0.483**, not a
positive number. Not decided here.

Row 3, `irt_lt_mcby_a`, is also gapless for **Germany** over the window, and it is the same
concept as the IMF's `S13BOND_RT_PT_A_PT` — a long-term government bond yield, a market
price. Its value is that it closes the IMF series' 2018–2021 shortfall
(`daten/quellenbefund-leitzinspfad.md:39-41`) with a German series, 21/21. Also a market
price, and also not decided here.

## 4. Licence: permitted, and the attribution is nameable

`daten.md:195-198` in its wording:

> „Reuse of statistical data, metadata, publications, and other dissemination tools published
> on this website for commercial or non-commercial purposes is authorised provided the source
> is acknowledged."

The exception that kills Eurostat for this product elsewhere — „data for non-EU/EFTA
countries (the page names the USA, Japan and China as examples)", `daten.md:203-208` — **does
not reach the euro area or Germany.** Both are EU. Re-read against the live notice
(`ec.europa.eu/eurostat/en/help/copyright-notice`, retrieved 2026-09-09): the excluded classes
are non-EU/EFTA/non-candidate countries, third-party copyrighted material, Liechtenstein and
Switzerland trade data as declaring countries, Austrian trade data at 8-digit CN, and
co-publications. None applies to `irt_st_a` or `irt_lt_mcby_a`.

**Attribution form, from the same notice: `Source: [DOI number], [access date]`.** The DOI
exists and was verified by request, not assumed:
`https://doi.org/10.2908/IRT_ST_A` → **302** → `ec.europa.eu/eurostat/databrowser/product/page/IRT_ST_A`
(2026-09-09). So the product line is nameable exactly:

> Source: 10.2908/IRT_ST_A, 2026-09-09

and for row 3 correspondingly `10.2908/IRT_LT_MCBY_A` — **that one was not resolved by
request in this run** and must be before it is used.

## 5. Limits of this measurement

- **The enumeration reaches the `irt` family and `ei_mfir_m`, not all of Eurostat.** Two of
  the three catalogue-wide routes were truncated by the fetch tool (§1 rows 2 and 3), so „no
  policy rate in Eurostat" is measured over 27 enumerated datasets plus one, not over the
  whole catalogue. A rate dataset filed under a different prefix would be missed the way
  `FR.INR.MMKT` was missed by topic 7 in `daten/quellenbefund-leitzinspfad.md:180-189`.
- **Window years are read off the returned `time` index and `status` fields**, not off the
  catalogue's advertised coverage. Rows 6 and 7 advertise more than they carry.
- **`geo=EA` is the euro-area aggregate**, not Germany. Row 2 is a euro-area value that
  applies to Germany from 1999 on because Germany has no separate money market; that is an
  interpretation, and the dataset does not state it.
- **EONIA was discontinued after 2021.** The window ends 2021, so this does not bite here —
  but a later window would need €STR, which is a different series and was not queried.

## 6. Follow-up

Carrying either number into `daten/reihen.toml` series 9 is **not** this package. It needs
its own, and it must decide the concept mix first, because `irt_st_a` (money market, euro
area) and `irt_lt_mcby_a` (bond yield, Germany) are two different answers to the German side.
Nothing outside this file was written.
