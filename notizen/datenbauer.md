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

## 2026-09-08 — 0234, Ruecklauf 2: three counts carried a claim about five

The reviewer was right twice, and the second time was the expensive one.

**The rule: a set claim needs a count per member, not per member you happened to fetch.**
I wrote „Germany is empty in **all five** World Bank rate indicators, China carries 25 of 25
there" off `RINR`, `LEND`, `DPST` — three. `LNDP` and `RISK` were never queried. Both halves
looked safe by derivation, and one of them was: DEU empty in `LNDP`/`RISK` does follow from
`LEND` = 0 and `DPST` = 0, since both are differences of measured rates. **The China half
does not follow, and it was false.** Measured 2026-09-08, per country, 1997–2021:

| Code | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `RINR` | 25 | 0 | 25 | 25 |
| `LEND` | 25 | 0 | 25 | 25 |
| `DPST` | 0 | 0 | 25 | 25 |
| `LNDP` | 0 | 0 | 25 | 25 |
| `RISK` | 25 | 0 | **0** | 25 |

`RISK` is lending rate minus treasury-bill rate; China reports no treasury-bill rate to WDI.
Only Brazil carries all five. The headline („no single code reaches all four") held and is
only now *proven* — two of the five that could have refuted it were unmeasured.

**Where the derivation trap sits, for next time:** the tempting move is to write the
derivation as a count. It reads identically and it is a different kind of claim. If the
sentence says a number, either fetch it or say „follows from", and say from what.

**And unasked-for overreach closes cheap.** „Exactly five `FR.INR` indicators" rested on one
read of topic 7 with no pagination check. One fetch: `total: 203`, `pages: 1` — complete,
the enumeration is sound. What stays open and is now written down as a limit rather than
glossed: an indicator under a different topic or without the `FR.INR` prefix. WDI files
rates in topic 7 by convention, not by guarantee. **Checking my own load-bearing number
before a reviewer does cost one fetch; the one I did not check cost a Ruecklauf.**

**Method that worked and is worth repeating:** four single-country fetches per indicator
instead of one four-country fetch. Each response is 25 rows, so „all null" and „25 of 25"
are answers the summariser cannot get wrong — and my own logbook already says the bulk
listing lies. Eight fetches, no ambiguity, no re-measure.

## 2026-09-08 — 0241: the overreaching negative is a *class*, and I shipped six of them

The remainder of 0234, no retrieval, three conditions. The thing worth carrying: 0234's
condition 1 caught every *unnamed* negative result and let every *overreaching* one through,
three Ruecklaufe running. Those are two different defects and only one of them was being
checked.

**The test that separates them, and it is one question:** would the sentence still be true
if the query had a typo? „`FR.INR.MMKT` does not exist" survives a typo — it is a claim
about the world. „`FR.INR.MMKT` returned no rows for these four countries" does not — it is
a claim about an answer. Write the second, always; the first needs its own query against the
identifier endpoint, and if I did not run that, I may not write it.

**Six in one file, all mine** — MMKT, CHN „nothing found in any vetted source", CHN `DISR`
„the series does not exist" (derived from a wildcard, never fetched), `MFS_FMP` „no interest
rate for anyone" (one USA control), PWT „no interest-rate variable" (landing page only), and
the H1.

**The sharpest one was not overreach but self-contradiction:** the per-country table said
CHN „nothing found in any vetted source" four lines above its own matrix giving CHN 25 of 25
in four World Bank codes. My own trigger from the morning of 2026-09-08 — *a number of mine
that contradicts a number already measured is an instruction to re-fetch* — has a twin I did
not have: **a sentence of mine that contradicts a table of mine in the same file needs no
fetch at all, only reading my own file once as a stranger would.** Cheapest defect class
there is, and the one I keep shipping.

**A negative can get stronger under a sweep, not only weaker.** BACI's „no monetary
variable" was impression; its six columns (`t`, `i`, `j`, `k`, `v`, `q`) are enumerated in
`daten/einheitenbefund-pwt-baci.md`, so it became proof. PWT next to it got weaker. Two rows
of one table moved in opposite directions in the same edit — binding claims to queries is
not hedging.

**Documenting a gap can undercut a headline, and that is the correct direction.** Condition
2 told me to raise „a rate indicator outside topic 7 is not excluded" to *documented* with
`MMKT` as the instance. That makes the unqualified H1 („no single code reaches all four at
all") strictly less supportable than before. Narrowed it to „no code queried here" and
flagged it as my one departure from the package's own wording.

**Cheap and repeatable:** `Grep -c 'technik\.md|spiel\.md'` before and after every
`reihen.toml` edit. 62 both times, and the note in the package says so with the command.
Also: I avoided writing the word `ungemessen` in the corrected clause, because a case-blind
keyword probe would otherwise read the correction as the old claim.

## Open leads

- **The 61-against-62 keyword count is closed — do not reopen it.** The project manager
  ruled on 2026-09-08 (Ruecklauf 2): no line was moved, all four sites are intact, and which
  of the two counts was wrong is not separable without a diff, which no role here has.
  62 is the standing number. **R = 19 does not wobble** and gets no package of its own.
- **0234 is `blockiert`, its remainder 0241 is built. Closed by 0241:** `:623` no longer
  says `ungemessen`, and `:1258` no longer says „keine einzige Kennung". **Still open:** (a)
  the new befund file adds file names to `daten/`; if that directory is counted, the
  uebergangen head number moves by more than the one I caused in `reihen.toml`. (b) The
  three ways out named in the befund are for three different roles — nobody owns the
  decision yet, and Reihe 9 feeds `leitzins_start[l]` and T51's `aufschlag_min`.
- **`FR.INR.MMKT` is now a documented hole in the topic-7 enumeration, and nobody has
  measured how big it is.** Rate indicators outside topic 7 or without the `FR.INR` prefix
  are unenumerated; MMKT itself is empty for the four countries, so nothing hangs on it
  today. One indicator-endpoint sweep would close it. Worth a package only if the mixed-path
  decision goes to the architect.
- **The policy-rate question is no longer mine, and the World Bank side is now closed by
  enumeration** (all five `FR.INR` indicators counted per country, 2026-09-08). What remains
  is a decision (new source = gate; mixed path = architect; rule instead of series = game
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

