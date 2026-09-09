---
typ: pruefung
paket: 0280-eurostat-fuer-den-deutschen-leitzinspfad-messen
pruefer: daten-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: "Every count in §2 re-requested from Eurostat and compared digit by digit against the transcribed `value`/`status` objects; conditions 2-5 re-read against the sources they cite"
befunde: 1
---

# 0280, return 1 re-checked: the four are fixed, and the counts reproduce

Requests made by me on 2026-09-09 against the endpoints the file itself names, asking for
`value`/`status` transcribed mechanically rather than summarised.

## The four defects of return 1

**1. Rows 6/7, the inverted count.** `irt_h_ddmr_a?geo=DE&sinceTimePeriod=1990&untilTimePeriod=2021`:
`value` has **9 keys, 0–8**, highest key 8, index 8 = 1998 = `3.41321`; `status` =
`{"8":"d","9":"m",…,"22":"m"}`; `positions-with-no-data.time` = `[23,24]`; time index ends 2014.
Window 2001–2021 = indices 11–24: 11–22 `m` and valueless, 23–24 no-data, 2015–2021 unindexed.
**Count 0**, as §2 now says, and the status object stands in the file as the evidence the
vermerk demanded. Row 7 not re-fetched this round — verified in round 1 (last value 1998 =
`3.51907`). The new flag quote is accurate: codelist `OBS_FLAG` gives `m` = „missing value; data
cannot exist" and `d` = „definition differs (see metadata)", both verbatim as quoted.

**2. The rounding.** `irt_st_a?geo=EA&sinceTimePeriod=2001&untilTimePeriod=2021`: `size`
`[1,5,1,21]`, `id` `["freq","int_rt","geo","time"]`, `int_rt` index `IRT_DTD:0` — so keys 0–20 are
the day-to-day rate. **All 21 values in §3 are digit-exact**, minimum `-0.48270` (2021), seven
negative (2015–2021). `status` ABSENT, `positions-with-no-data` all empty, so §3's gapless-without-flag
claim holds; row 2's „21/21 per each of the 5 categories" holds too — 105 keys, none missing.

**3. Row 8, the 421.** `irt_h_cgby_a?geo=DE`: **26 keys**, time index 1973–1998, first `9.34`,
last `4.40`, no status. Matches §2 exactly; none in the window.

**4. The truncated quote.** The EONIA sentence is now quoted to its full stop including
„…, initiated within the euro area by the contributing panel banks", and the supplier sentence
verbatim. §3's „does not call it a policy rate anywhere" also checks out: the same metadata file
has no sentence containing policy rate, key rate, deposit facility or main refinancing.

## Also re-measured, so the pass is not resting on round 1

- Row 3, `irt_lt_mcby_a?geo=DE`, window: 21 keys, no `status`, no no-data → **21/21** ✓.
- Condition 3: §4's two quotes are verbatim `daten.md:195-198` and `:203-208`; the attribution
  form matches `:200-201`.
- Condition 5: `daten/quellenbefund-leitzinspfad.md` still has **zero** `eurostat` hits;
  `reihen.toml`'s four are at `:756/:989/:1004/:1009`, the pre-existing WDI value-added and
  population entries, not series 9. The `.neu*.tmp` files in `daten/zwischenstaende/` are older
  by mtime than `nachmessung-zinsreihen-2026-09-05.md` — not from this package.

## One residual, and why it is not an acceptance failure

**§5 bullet 2 still describes the defect as the method:** „Window years are read off the returned
`time` index and `status` fields". After the correction, that is the counting rule that produced
the 12. §2's own definition („distinct years … carrying a non-null value") and the correction both
count off `value`. A follow-up that reads §5 as method guidance repeats the inversion in the next
file. Replacement wording: *read off the returned `value` object, not off the `time` index, the
`status` flags, or the catalogue's advertised coverage.*

Condition 1 asks for correct, evidenced counts, not for a method note, and the counts are correct
and evidenced — so this does not fail the acceptance and is not a second return. Fix it if the
file is opened again for anything else.

Proposal `0287` written: `daten.md` Nr. 7 permits DEU/EA by licence (§4, confirmed) while its own
verdict at `:210-214` says „**Do not plan it in**", on a ground package `0234` disproved for DEU.
That is not a defect of 0280 — but it is what the follow-up carrying this number into series 9
walks into.
