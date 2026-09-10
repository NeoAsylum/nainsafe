# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 14358 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 — 0297, the `daten` member: the standalone build is the trap, not the code

**First C++ package of this role, and the one thing worth carrying forward is a build
fact, not a code fact.** `baulauf.py` rglobs **every** `CMakeLists.txt` and configures each
one alone (`agents/baulauf.py`, the `befehle()` branch for `cmake`). `daten` is the first
member of T13 that depends on `kern`, and in its own tree the target `kern` does not
exist. Without a fix that build is red no matter how good the source is. What I did:
`add_subdirectory(../kern ${CMAKE_CURRENT_BINARY_DIR}/kern)` inside the
`PROJECT_IS_TOP_LEVEL` block, after including `werkzeugkette.cmake`. **The next member
that hangs off another one — `schnittstelle`, `konsole`, `oberflaeche`,
`werkzeuge/aufbereitung` — hits exactly this and can copy the four lines.**

**Its price, named because a reviewer will see it:** the standalone `daten` tree also
registers all 14 `kern` tests plus `wandschranke`, so they run twice per night (0.67 s +
0.43 s). I did not see a way around it without editing `kern/CMakeLists.txt`, which is not
my file.

**The three riegel that read the tree and what they cost a new source file.**
`multiplikationsriegel` and `bezeichner_riegel` read `kern/` only — a new file under
`daten/` is invisible to both. `belegstellen_riegel` reads the **whole** tree; two things
in a comment make it red, and I avoided both: a file name followed by a line number, and
the three keywords for a section quote. That is why nothing I wrote cites `technik.md` by
line — only by T-number. `zahlwort_riegel` reads exactly one file (`werte.hpp` in the core), so number words in my
own prose are unchecked.

**Unsure about, for the project manager (the reviewer does not see this):**
1. **I cannot compile.** No role has `Bash`; the acceptance hangs on
   `befunde/uebersetzung-<datum>.md`, which does not exist yet for this run. Everything
   below is a reading of the warn set (`-Wconversion -Wsign-conversion -Wold-style-cast
   -Wuseless-cast -Werror`), not a measurement. The likeliest way I am wrong is a
   discarded `[[nodiscard]]` inside one of the abort lambdas in `jahrgang_probe.cpp` — I
   wrapped nine of them in `static_cast<void>(…)`; if I missed one, that file is red.
2. **`fuelle_leitzins_start` is one function more than the acceptance names.** Condition 3
   only demands that `leitzins_start` be derived and not stored twice. I added the one
   place that writes it into `Konstanten` so the next package does not derive it a second
   time. If that reads as scope creep, it is two lines and deletable.
3. **`ueber_fenster` likewise.** T40's `ueber_fenster` row assigns the mark to the data
   builder and derives it as `runde > R`; it is the same comparison the clamp already
   makes. Named, not smuggled.
4. **The clamp reading.** I took "a round beyond R gives the last support point" as
   `index = min(runde − 1, stuetzstellen − 1)`. Rounds 1…R therefore read support points
   0…R−1, and index R — the closing year — is reached only from round R+1 on. If the
   intended reading is that round R already reads the last point, the mapping is off by
   one and `fall_b` is the test that would have to change.
5. **The message caps at the first violation** and carries the count beside it. A
   `Meldung` has a fixed 512-char buffer, so "all violations in the words of one message"
   is not available. The count is the honest half of it.

## 2026-09-09 — 0280, return 1 of 3: I counted missing-value flags as values

**The defect, and it is a rule, not a slip.** In Eurostat JSON-stat, a year can appear in
`dimension.time.category.index` three ways: with an entry in `value`; with an entry in
`status` and none in `value`; or listed in `extension.positions-with-no-data.time`. Only the
first is data. I read the `status` object as coverage and reported **12** window years for
`irt_h_ddmr_a` and `irt_h_mr3_a` where the answer is **0** — both series' `value` stops at
index 8 = 1998, and indices 9–22 carry `m`. Eurostat's own codelist
(`api/dissemination/sdmx/2.1/codelist/ESTAT/OBS_FLAG`) says `m` = „missing value; data cannot
exist". **Count off `value`. `status` tells you why a year is absent, never that it is
present.** That endpoint is also the cheap way to make a flag claim quotable.

Worse than the count: it contradicted my own §5, which says Germany has no separate money
market after 1999 — which is precisely why those two series stop in 1998. **A table that
disagrees with the prose in the same file is the prose being right.** I had the reason
written down and still filled the cell from the wrong object.

The other three, all mine, all the same shape — a number carried without re-reading its
source: (a) I rounded the 21 `irt_st_a` values 5→3 decimals unmarked, so the minimum handed
on became `-0.483` instead of `-0.48270` — now carried at full source precision;
(b) „421 observations" for `irt_h_cgby_a` is the dataset-wide total, `geo=DE` returns **26**;
(c) I truncated the EONIA quote without an ellipsis, and the dropped clause („initiated
within the euro area by the contributing panel banks") was the part that supported my own
`geo=EA`-is-not-Germany caveat. **A quote cut short can delete your own evidence.**

All four re-requested by hand before editing, not taken from the reviewer's word. The
headline result was untouched by all of this and stands.

**Still unsure, for the project manager:** points 1–3 of the previous entry are unchanged
(`10.2908/IRT_LT_MCBY_A` still unresolved by request; „no policy rate in Eurostat" is measured
over 28 datasets, not the catalogue; the EA-for-DE substitution is my interpretation). Point 4
now reads with a five-decimal minimum of **-0.48270**.

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

