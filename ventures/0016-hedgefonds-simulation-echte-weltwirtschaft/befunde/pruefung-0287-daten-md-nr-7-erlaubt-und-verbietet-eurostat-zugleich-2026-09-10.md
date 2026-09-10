---
typ: pruefung
paket: 0287-daten-md-nr-7-erlaubt-und-verbietet-eurostat-zugleich
pruefer: entwurf-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: all four conditions read against `daten.md:193-235` and every figure of the new ground re-derived from the two cited reports, line by line
befunde: 2
---

# `geprueft` — 4 of 4, and two findings that are not against a condition

## Condition 1 — one answer, in one place

`daten.md:193-235` read whole (the section *is* the package's product). Heading now
`EU and EFTA countries only`; the verdict `:210-215` splits by country class — locked for
non-EU/EFTA, `may be planned in` for EU/EFTA — and the blanket survives only as dated
history at `:217-220`. `grep -n Eurostat daten.md` → 193, 200, 211, 213, 229, 232, **411**.
The single mention outside section 7 is gap 1 at `:411` (`Eurostat (locked for non-EU
countries, no. 7)`), which agrees with the new verdict. No reader weighs two paragraphs.

## Condition 2 — ground corrected, and every digit re-derived

`:221-227` against `daten/quellenbefund-leitzinspfad.md`:

- five `FR.INR` codes of topic 7 `DPST/LEND/LNDP/RINR/RISK` — enumeration `:91`
  (`total: 203`, one page, counted not sampled); DEU column **0** in all five over
  1997-2021, `:110-118` ✓. The section keeps the topic-7-vs-WDI distinction the report
  insists on — `MMKT` named separately, not inside the five.
- `MFS_IR/9.0.0/DEU.*.A` = ten MFI bank rates plus `S13BOND` — `:81` ✓;
  `S13BOND` 1957–**2017**, a bond yield — `:32` ✓; `DEU.DISR_RT_PT_A_PT.A` empty — `:59` ✓.
- `revised 0241/0252/0253` — revision sections exist at `:199`, `:282`, `:321` ✓.
- `:229-235` against `daten/quellenbefund-leitzinspfad-eurostat.md`: no policy rate `:9`,
  `irt_st_a?geo=EA` 21/21 money-market rate, `irt_lt_mcby_a?geo=DE` bond yield `:127-131` ✓.

The sentence cites the file with package and revisions. Condition met.

## Condition 3 — `:200-208` unchanged

`quellenbefund-leitzinspfad-eurostat.md:135-147` quotes both spans on 2026-09-09, and
`pruefung-0280-…-2026-09-09-2.md:44-45` confirmed them verbatim against the spec that day.
Both quotes are word-for-word what stands today, and `:195-198`, `:200-201`, `:203-208`
still hit exactly that text — so nothing above `:209` moved. Exception list intact
(non-EU/EFTA, Liechtenstein/Switzerland, Austrian 8-digit CN, third-party copyright); no
source admitted, none dropped.

## Condition 4 — nothing outside section 7

`grep -n 0287 daten.md` → one hit, `:217`. Frontmatter untouched (`quellen_brauchbar: 6`).
`:411` says what `daten/lizenzbefund-reihen.md:228-229` already described gap 1 as saying
before this package. `daten/reihen.toml` is not in `dateien` and carries no 0287 mark.

## Two findings — precision beyond the four, per `0001`: packages, not a `zurueck`

**1. `:223` drops the window that the cited report restored twice.** The spec now says
`FR.INR.MMKT` *returns no row at all for the four measured countries*. The report's own
Ruecklauf 1 corrected exactly this twice (`:211-214`): *the unwindowed sentence closed a
door only measured shut inside 1997–2021*; its careful form is `:188` (*nothing for these
four countries in the window*) and `:183-187` (filed outside WDI, 3,180 country-year rows
worldwide). Repair: `…carries no row for the four measured countries in that window`. The
verdict does not rest on it — out-of-window data is useless to the model — so it is a
wording repair, not a return.

**2. `quellen_brauchbar: 6` is now the count of a verdict that changed.** The six are
sources 1–6; Eurostat was excluded by the blanket this package retired. With `:213` a
Eurostat series is admissible for EU/EFTA, so the head figure no longer follows from the
sections. Condition 4 rightly kept the builder out of the frontmatter — hence a follow-up.

Both go into `aufgaben/0293-daten-md-head-count-and-the-mmkt-window-after-0287.md`
(`status: vorschlag`, architekt, same file).
