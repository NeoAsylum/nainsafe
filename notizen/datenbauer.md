# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 14358 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 — 0280, Eurostat for the policy-rate path

**Result: no policy rate in Eurostat, but `irt_st_a` / geo=EA / `IRT_DTD` carries 21 of 21
window years 2001–2021, gapless.** It is EONIA, a money-market rate — quoted from
`irt_st_esms.htm`, not inferred. `irt_lt_mcby_a` carries 21/21 for **DE** and closes the
IMF `S13BOND` 2018–2021 shortfall, but is a bond yield. File:
`daten/quellenbefund-leitzinspfad-eurostat.md`.

**The one thing worth carrying forward: how to enumerate a Eurostat catalogue.** Three
routes failed, one worked, and the failure mode is not obvious.

- `catalogue/toc/txt?lang=en` and `sdmx/2.1/dataflow/ESTAT/all/latest?detail=allstubs` both
  return 200 and both get **truncated by the fetch tool** — the TOC stopped after ~1,839
  lines and never reached the `irt` branch; the dataflow list died mid-element at
  `LFSQ_EWHAN2`. A truncated 200 reads exactly like a complete answer if you only look at
  the summary. **Always make the fetch state whether the document was truncated.**
- `&node=irt` on the TOC is **silently ignored** — you get the same truncated whole file
  back and could easily mistake it for a scoped answer.
- What works: **`api/dissemination/files?dir=data&sort=1&start=<prefix>`.** Machine-generated
  bulk-file index, prefix-filterable, small, complete. 27 entries for `irt`. This is the
  enumeration endpoint to reach for first next time.
- `web/interest-rates/database` is 404; the live node is
  `web/exchange-and-interest-rates/database` and it is JS-rendered, so it yields nothing to
  a fetch. Same for `databrowser/product/page/<CODE>` — the DOI and citation string are not
  in the served HTML.

**How to verify a Eurostat DOI without the product page:** request
`https://doi.org/10.2908/<CODE>` and read the redirect. `10.2908/IRT_ST_A` → 302 →
the databrowser product page. That is a verification by request, not an assumption, and it
is the only cheap one I found.

**Query shape that pays.** `statistics/1.0/data/<code>?format=JSON&geo=<GEO>&sinceTimePeriod=&untilTimePeriod=`
honours the window (unlike the IMF endpoint, which ignores `startPeriod` —
`quellenbefund-leitzinspfad.md:173`). Read the count off the returned `time` index and the
`status` fields, **never off the catalogue's advertised coverage**: `irt_h_ddmr_a` and
`irt_h_mr3_a` both advertise through 2014 and carry `m` for 2013–2014.

**A 200 with an empty `geo` index is an answer, not an error.** `irt_st_a` with `geo=DE`
comes back 200 with no `geo` category at all — Germany is not a reporting unit for money
market rates, because after 1999 there is no German money market distinct from the euro
area's. Same for `irt_lt_gby10_a`. I recorded these as 0 window years with the reason, not
as failed requests.

**Unsure about, for the project manager:**
1. I did **not** resolve `10.2908/IRT_LT_MCBY_A` by request — only `IRT_ST_A`. Said so in
   §4. If a follow-up uses the bond-yield series, that DOI still needs a request.
2. „No policy rate in Eurostat" is measured over 27 enumerated `irt` datasets plus
   `ei_mfir_m`. It is **not** a whole-catalogue statement, and I could not make it one
   because of the truncation above. This is the same shape of gap that `FR.INR.MMKT` was
   for topic 7 — I flagged it in §5 rather than let the verdict read wider than the
   measurement.
3. The euro-area value standing in for Germany is my interpretation; the dataset does not
   say it. §5 says so.
4. Seven of the 21 values are **negative** (min -0.483). `T51` derives `aufschlag_min` from
   the path minimum, so whoever carries this in inherits a signed path. Named, not decided —
   it is the architect's, way 2.

