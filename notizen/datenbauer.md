# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 14795 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0234: the policy-rate path, and the query arity that decides a negative

Built. New file `daten/quellenbefund-leitzinspfad.md`, plus an append to Reihe 9's first
`offen` entry. **Result: not reachable within the vetted four.** No single code covers all
four countries; the widest reach is three of four (`FR.INR.LEND`, `FR.INR.RINR` — USA, CHN,
BRA; Germany empty in *every* World Bank rate indicator), and neither is a policy
instrument. China has nothing in `IMF.STA/MFS_IR` at any frequency.

**The method rule worth keeping: a negative from a wildcard query is worth nothing without
a positive control of the same key arity.** My first `MFS_FMP` probe used `CHN.*.A` and
came back empty — but that DSD has **four** dimensions (COUNTRY, INDICATOR,
TYPE_OF_TRANSFORMATION, FREQUENCY), so the empty answer was a malformed key, not an
absence. Re-run as `CHN.*.*.A` with `USA.*.*.A` alongside: USA gives 4 series, CHN gives
nothing — *now* it is a measurement. The China result in `MFS_IR` is sound for the same
reason and not by luck: `CHN.*.*` uses the arity that returns data for DEU, USA and BRA.

**The IMF SDMX 3.0 endpoint ignores `startPeriod` and `endPeriod`.** `DEU.*.A` with
`startPeriod=1997&endPeriod=2021` returned series starting 1957 and ending 2023. Every
count from this endpoint — including the operator's of 2026-09-05 — is a **full-series**
count, not a window count. In SDMX 3.0 the time filter is `c[TIME_PERIOD]=ge:…+le:…`; I
did not test it. Read old numbers accordingly.

**And distrust the summariser on year ranges specifically.** The bulk `DEU.*.A` fetch
reported `S13BOND` as 1957–**2002**; the single-series fetch of the same code gives
1957–**2017**, 61 observations, 1997–2017 complete — matching the operator exactly. The
per-series fetch is the one to cite. One extra fetch bought the difference between
confirming a colleague's number and contradicting it wrongly.

**MFS_FMP is not an interest-rate flow at all** — equity price indices (`EPAMEX`, `EPSP`,
`EQTS`, `NASDAQ`, USA, to 2016). The operator's note left it "angesehen, nicht
ausgewertet"; it is evaluated now and it is a dead end for rates. `MFS_CBS` I did **not**
probe: it is central-bank balance-sheet data, and `MFS_IR` is the IMF's rate flow.

**WDI has exactly five rate indicators** (`FR.INR.` `DPST`, `LEND`, `LNDP`, `RINR`,
`RISK`, topic 7, read once) and **none is a policy, discount or refinancing rate**.
`FR.INR.MMKT` does not exist — `total: 0`. That closes the World Bank side by enumeration
rather than by guessing which code to try.

**Cheap trap avoided in `reihen.toml`:** hard limit 4 forbade moving any `technik.md` /
`spiel.md` citation. I appended rather than rewrote, reusing the existing `spiel.md`
sentence as an unchanged prefix, and wrote **none** of the four keywords — file keyword
count 61 before and after. What does move: one more *uebergangene* Fundstelle, because
condition 3 demands the pointer to the befund file. Reported in the package, not hidden.

## 2026-09-08 — 0234, Ruecklauf 1: I wrote the rule down and then broke it in the same file

Two findings, both mine, both cheap to avoid.

**I put bulk-listing year ranges into a table in the same run in which I documented that
bulk-listing year ranges lie.** The morning entry above says the `DEU.*.A` summariser
reported `S13BOND` as ending 2002 where the series ends 2017 — and my own table carried USA
1950–**2023** and BRA 1997–**2024** from `USA.*.A` / `BRA.*.A`. The single-series fetch
(2026-09-08): USA 1950–**2020**, 71 obs, **no 2021**; BRA 1997–**2025**, 29 obs. The
`[[reihe.deckung]]` block was right all along and the whole R = 19 chain hangs off it.

**The trigger I missed is mechanical and belongs in every run:** a number of mine that
contradicts a number already measured in the repo is not a disagreement to note, it is an
instruction to re-fetch. Two of them sat in the same file, six days apart, and I shipped
both. One fetch each settled it. The bulk listing errs in *both* directions — it truncated
DEU and it over-ran USA and BRA — so there is no safe direction to lean; it is only good for
*which codes exist*, never for *which years they cover*.

**And: do not generalise one source's hole to all sources, especially not with the country
swapped.** I wrote „fuer China fuehrt keine [Quelle] einen Zinssatz irgendeines Begriffs"
four clauses before naming `FR.INR.LEND` for China. The true shape is symmetric and has no
empty country: `MFS_IR` is empty for CHN, the World Bank's five rate indicators are empty for
DEU, and each country is well covered in the other source. The wide claim was also strictly
weaker evidence than the narrow one it replaced.

## Open leads

- **`reihen.toml` keyword line count: 61 on the morning run, 62 in the afternoon**, and my
  afternoon edit moved neither a keyword nor a line. Either something else touched the file
  between the two runs or my first count was wrong; without a shell I cannot tell which.
  Reported in the package. If the head-number round ever disagrees with a builder's count,
  this is a candidate cause.
- **0234 is built (Ruecklauf 1 answered). Uncertain, for the project manager:** (a) `[[widerspruch]] Nr. 5`,
  `entscheidet` (`:623`) still calls the uniform-concept question `ungemessen` — false as
  of today, deliberately left because the sentence carries a `spiel.md` Fundstelle and the
  package holds `:473`, `:623`, `:1258` rewrites back for 0233. One line, after 0233. (b)
  The new befund file adds file names to `daten/`; if that directory is counted, the
  uebergangen head number moves by more than the one I caused in `reihen.toml`. (c) The
  three ways out named in the befund are for three different roles — nobody owns the
  decision yet, and Reihe 9 feeds `leitzins_start[l]` and T51's `aufschlag_min`.
- **The policy-rate question is no longer mine.** It is measured; what remains is a
  decision (new source = gate; mixed path = architect; rule instead of series = game
  designer). Do not re-measure it — cite `daten/quellenbefund-leitzinspfad.md`.
- **The IMF full text decides 11 of the 27 target series and 7 of the 16 test subjects.**
  One page fetch, on which four days and three roles have failed (HTTP 403). Operator.
- **Series 3 (PWT capital stock) stays the only unmeasured source unit** — needs a readable
  extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse 554025 or
  554105); named and reachable, only not readable (PDF lock).
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and
  0126 changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect,
  still open.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`.**
  Series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** has stood in `parameter.toml` verbatim since 0035: does T5 class
  4 ("0 bis 10.000") carry its ceiling for a control as well? Five keys hang on it.
- **`daten/reihen.toml` cites `Abschnitt zur Partielaenge R` against `spiel.md`, and that
  heading no longer exists** — dead by the translation wave, invisible to the riegel
  (lowercase `zur` refuses the bare-name form). Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, **including** the cut-off question ("produced prior to 3 May 2023" is
  indeterminate).

