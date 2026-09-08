---
typ: quellenbefund
gegenstand: Reihe 9 (Leitzins) -- source for the policy-rate path, USA / DEU / CHN / BRA
paket: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
datum: 2026-09-08
ergebnis: not reachable within the vetted sources
---

# No vetted source carries a policy rate for all four countries, and no code queried here reaches all four at all

Measured 2026-09-08 against the four sources vetted in `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md`, line 8. Every endpoint
below is freely retrievable: no account, no key, no payment.

IMF endpoint, same for every key: `https://api.imf.org/external/sdmx/3.0/data/dataflow/IMF.STA/<FLOW>/<VERSION>/<KEY>`
World Bank endpoint, in the form every cell below was counted from — **one country per
fetch**, 25 rows, `total: 25`:
`https://api.worldbank.org/v2/country/<ISO3>/indicator/<CODE>?format=json&date=1997:2021&per_page=50`
The four-country form `country/USA;DEU;CHN;BRA/...` returns 100 rows and silently truncates
to 50 at the default `per_page`. It is not the form the counts rest on.

**How to read a negative here.** Every „empty", „absent" and „0" below is the answer of the
named query, not a statement that the quantity does not exist. Where a stronger claim is
made — that an identifier or a series does not exist — the query against the identifier
endpoint itself is named alongside it.

## Per country: the nearest candidate found

| Country | Source | Flow | Code | Years | What it measures | Policy rate? |
|---|---|---|---|---|---|---|
| USA | IMF | `MFS_IR` 9.0.0 | `DISR_RT_PT_A_PT` | 1950–2020, 71 obs | Fed discount-window rate | administered, not the target rate |
| BRA | IMF | `MFS_IR` 9.0.0 | `DISR_RT_PT_A_PT` | 1997–2025, 29 obs | rediscount rate, **not the Selic** | administered, not the target rate |
| DEU | IMF | `MFS_IR` 9.0.0 | `S13BOND_RT_PT_A_PT` | 1957–**2017**, 61 obs | government bond yield | **no** — a market price |
| CHN | World Bank | WDI | `FR.INR.LEND` | 1997–2021, 25 of 25 | administered PBoC benchmark lending rate | **no** — a bank lending rate, not the policy instrument |

The CHN row is the nearest candidate, not a find: no query in this run returned a policy
rate for China, and `IMF.STA/MFS_IR` returns no observations for CHN at any frequency
(below). Everything China does carry sits on the World Bank side.

The German window shortfall is exact: 1997–2017 all carry a value, 2018–2021 carry none
(`DEU.S13BOND_RT_PT_A_PT.A`, retrieved 2026-09-08). This confirms the operator's count of
2026-09-05 (`daten/nachmessung-zinsreihen-2026-09-05.md`) against the series itself.

## `DISR_RT_PT_A_PT` coverage: which reading holds

Two readings of this code stood six days apart. The **single-series fetch decides**, and it
confirms the `[[reihe.deckung]]` block of `daten/reihen.toml` (`:1290`–`:1313`) in every
figure. The wider years an earlier draft of the table above carried came from the bulk
`USA.*.A` / `BRA.*.A` listing, whose year ranges are unreliable — the same listing reported
DEU `S13BOND` as ending 2002 where the series ends 2017.

- **USA — 1950–2020 holds.** 71 observations, **no 2021 row**, so 1997–2021 carries 24 of 25
  years. Read off `USA.DISR_RT_PT_A_PT.A?format=sdmx-csv`, retrieved 2026-09-08; last three
  rows 2018 = 3, 2019 = 2.25, 2020 = 0.25. `reihen.toml:1294` (`letztes_jahr = 2020`),
  `:1295` (`luecken_1997_2021 = 1`), `:1296` (24 support points) and
  `deckungsbefund-1997.md:167` stand unchanged.
- **BRA — 1997–2025 holds.** 29 observations, no gap inside the window, 25 support points.
  Read off `BRA.DISR_RT_PT_A_PT.A?format=sdmx-csv`, retrieved 2026-09-08; 2024 = 18.4762,
  2025 = 21.794. `reihen.toml:1303` (`letztes_jahr = 2025`) stands unchanged.
- **DEU — no reading to reconcile.** `DEU.DISR_RT_PT_A_PT.A` is empty (2026-09-01,
  `deckungsbefund-1997.md:174`); `reihen.toml:1308`–`:1313` stands. The German row of the
  table above is `S13BOND_RT_PT_A_PT`, a different code.
- **CHN — no reading to reconcile.** No `DISR` observations to read, and this follows from
  the wildcard rather than from a fetch of its own: `CHN.*.*` over the whole flow returns
  no observations at any frequency (2026-09-08), which covers `DISR_RT_PT_A_PT`. The
  single-code key `CHN.DISR_RT_PT_A_PT.A` was not fetched separately. Measured is the empty
  answer at the arity that returns data for the other three countries — not that the code
  is undefined for CHN in the DSD, which is a question of the structure endpoint and was
  not put to it.

Nothing this run measured moves the R chain: `deckungsbefund-1997.md:10` names „Reihe 9 USA
(endet 2020)" as one of the two series that force **R = 19**, and 2020 is now confirmed
against the observations. The chain itself is not re-traced here — it is outside this
package.

## What was tried, and what each answered

| Query | Answer, retrieved 2026-09-08 |
|---|---|
| `MFS_IR/9.0.0/USA.*.A` | 9 annual series: `DISR`, `GSTBILY`, `GSTBILY_S3M`, `MFS134`, `MFS162`, `MFS166`, `MMRT`, `S13BONDS_SMT`, `S13BOND` (all `_RT_PT_A_PT`) |
| `MFS_IR/9.0.0/BRA.*.A` | 7 annual series: `DISR`, `GSTBILY`, `MFS135` (1982–1993), `MFS162`, `MFS166`, `MFS174` (1982–1993), `MMRT` (1964–1981) |
| `MFS_IR/9.0.0/DEU.*.A` | 11 annual series: ten MFI bank rates (`HEANBLCCO…`, `HENBD_LT2…`, `HENBD_STO1…`, `HENBL_NB_CFR…`, `HENBL_OY5…`, `HENBL_STO1…`, `HEOADAM_LT2…` 2008–2020, `HERLOBO1EUR…`, `MFS151…`, `MFS2123…`; the other nine 2003–2023) plus `S13BOND` |
| `MFS_IR/9.0.0/CHN.*.*` | **no observations, at any frequency.** Same key arity that returns data for the three other countries, so the empty answer is a measurement and not a malformed key. Measured is that the flow returns nothing for CHN — not that CHN is undefined in the DSD, which was not queried |
| `MFS_FMP/3.0.0/CHN.*.*.A` | empty. Positive control `USA.*.*.A` returns 4 series — `EPAMEX`, `EPSP`, `EQTS`, `NASDAQ`, equity price indices, 1950/1971/1972–2016. Those four are what the control returned, and none is an interest rate; the flow was not enumerated for other countries |
| `structure/dataflow/IMF.STA` | 62 dataflow **names** returned; none of the 62 is named for a policy or central-bank rate. This screens names, not contents, and the list was read once without a pagination check — see Limits |
| WDI `FR.INR.RINR` (Real interest rate, %) | USA 25, CHN 25, BRA 25 of the years 1997–2021; **DEU 0** |
| WDI `FR.INR.LEND` (Lending interest rate, %) | USA 25, CHN 25, BRA 25; **DEU 0** |
| WDI `FR.INR.DPST` (Deposit interest rate, %) | CHN 25, BRA 25; **USA 0, DEU 0** |
| WDI `FR.INR.LNDP` (Interest rate spread, lending rate minus deposit rate, %) | CHN 25, BRA 25; **USA 0, DEU 0**. Four single-country fetches, `total: 25` each, all 25 rows null for USA and DEU |
| WDI `FR.INR.RISK` (Risk premium on lending, lending rate minus treasury bill rate, %) | USA 25, BRA 25; **CHN 0, DEU 0**. Four single-country fetches, `total: 25` each, all 25 rows null for CHN and DEU |
| WDI `FR.INR.MMKT` (Money market rate, %), four countries over 1997–2021 | `total: 0, page: 0, pages: 0` — **no row for these four countries in the window.** The identifier itself exists and was queried separately: `/v2/indicator/FR.INR.MMKT` gives `total: 1`, source **Africa Development Indicators** and not WDI, and `/v2/country/all/indicator/FR.INR.MMKT` gives **3,180** country-year rows. Those two fetches are the daten-pruefer's, 2026-09-08, `befunde/pruefung-0234-leitzinspfad-quelle-fuer-deu-und-chn-messen-2026-09-08-3.md`. So: the code exists, it is filed outside topic 7, and it carries nothing for USA, DEU, CHN, BRA |
| WDI topic 7 (Financial Sector), `https://api.worldbank.org/v2/topic/7/indicator?format=json&per_page=500` | `total: 203`, `pages: 1` — the list is complete in one page, so the enumeration is not truncated. **In topic 7** exactly five `FR.INR` indicators: `DPST`, `LEND`, `LNDP`, `RINR`, `RISK`; by their WDI titles none is a policy, discount or refinancing rate. The count is over topic 7 and not over WDI — `FR.INR.MMKT` carries the same prefix from outside it (row above) |
| PWT 11.0, `https://www.rug.nl/ggdc/productivity/pwt/` | the landing page describes national-accounts and productivity variables and names no interest rate. **Read off the page description, not off the variable list** — that list exists only in `pwt110_user_guide_to_data_files.pdf` (Dataverse 554025) and `pwt110.xlsx` (554105), both unreadable with this role's tools (`daten/einheitenbefund-pwt-baci.md`, section 3). Not an enumeration |
| CEPII BACI, `https://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37` | the dataset carries six columns — `t`, `i`, `j`, `k`, `v`, `q` — read in full from the source page (`daten/einheitenbefund-pwt-baci.md`, section 1). Trade value and quantity by product; **no interest rate, by enumeration of the columns** |

One fetch failed and is recorded rather than retried into the ground: `FR.INR.LEND` with
`per_page=200` exceeded 60 s; the same query with `per_page=120` answered.

## Is a uniform interest-rate concept reachable?

**No — and the gap is worse than non-uniformity: of the codes queried above, none reaches
all four countries at all.** The widest reach of any one of them is three of four
(`FR.INR.LEND`, `FR.INR.RINR`: USA, CHN, BRA, Germany empty), and neither is a policy
instrument. On the World Bank side that set is an enumeration and not a sample (next
paragraph); on the IMF side it is the whole `MFS_IR` flow per country by wildcard.

Within topic 7 this is an enumeration and not a sample: the topic carries exactly five
`FR.INR` indicators, and all five are now queried per country over 1997–2021 (retrieved
2026-09-08). It is an enumeration of topic 7 and of nothing wider — `FR.INR.MMKT` is a
sixth indicator with the same prefix, filed outside the topic, and it carries no row for
these four countries. Non-null window years:

| Code | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `FR.INR.RINR` | 25 | **0** | 25 | 25 |
| `FR.INR.LEND` | 25 | **0** | 25 | 25 |
| `FR.INR.DPST` | **0** | **0** | 25 | 25 |
| `FR.INR.LNDP` | **0** | **0** | 25 | 25 |
| `FR.INR.RISK` | 25 | **0** | **0** | 25 |

Germany is empty in all five — counted per indicator, not derived from `LEND` and `DPST`.
China is **not** the mirror image: it carries four of the five in full and is empty in
`FR.INR.RISK` alone (lending rate less treasury-bill rate). Only Brazil carries all five.
Neither newcomer is a rate level in any case — `LNDP` and `RISK` are differences of two
rates, so neither is a policy-path candidate even where it is covered. On the IMF side the
wildcard `CHN.*.*` over `MFS_IR` returns no observations at any frequency, at the arity
that returns data for the three other countries.

What each candidate measures, per country. **„absent" means the query for that country and
code returned no observations** — the rows above name it — and not that the country has no
such rate:

| Candidate | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `DISR_RT_PT_A_PT` | Fed discount-window rate | absent | absent | rediscount rate, not the Selic |
| `S13BOND_RT_PT_A_PT` | govt bond yield | govt bond yield, ends 2017 | absent | absent |
| `MMRT_RT_PT_A_PT` | money market rate | absent | absent | 1964–1981 only |
| `FR.INR.LEND` | bank lending rate | absent | administered PBoC benchmark lending rate | bank lending rate |
| `FR.INR.RINR` | lending rate less GDP deflator | absent | same, deflated | same, deflated |

The known asymmetry the package named as the anchor to beat is not beaten: `DISR` remains
two concepts across two countries, and every alternative reached by the queries above
either drops a country or drops the policy character.

## What a decision would need

Not decided here — this file measures. Three ways out, and each belongs to someone else:

1. **A source outside the vetted four** — BIS central bank policy rates, the ECB data
   portal, or national central banks. This is a new source and therefore a gate: it needs
   the licence check that made the vetted four vetted. Data curator plus operator.
2. **Accept a mixed path and say so in the product** — e.g. USA and BRA `DISR`, DEU
   `S13BOND` (four years short of the window), CHN from `FR.INR.LEND`. Four countries,
   three concepts, two sources, and one country on a market price. Architect: T51 computes
   `aufschlag_min` from the minimum of this path, so the choice moves a parameter bound.
3. **Take the path out of the data** — T23 point 5 already makes its first support point
   the vintage constant `leitzins_start[l]`, four values; the rest could be a rule of the
   world run rather than an embedded series. Game designer.

## Limits of this measurement

- **The IMF endpoint ignores `startPeriod` and `endPeriod`.** `DEU.*.A` with
  `startPeriod=1997&endPeriod=2021` returned series beginning 1957 and ending 2023. Counts
  from this endpoint are therefore full-series counts, not window counts, and the coverage
  years above are read off the observations themselves.
- **Licence, not measured here and unchanged:** everything IMF-side inherits
  `lizenzurteil = unklar` — the licence text is unread after five attempts with HTTP 403
  (`daten/reihen.toml`, series 9, block `[[reihe.lizenzbeleg]]`). Not retried in this run.
- **The World Bank enumeration is over topic 7, not over all of WDI — and rate indicators
  outside topic 7 demonstrably exist.** Topic 7 (Financial Sector) is complete and
  unpaginated (`total: 203`, `pages: 1`), so „exactly five `FR.INR` indicators **in topic
  7**" is counted, not sampled. But `FR.INR.MMKT` (Money market rate, %) carries the same
  prefix, is filed under Africa Development Indicators rather than WDI, and answers
  `total: 1` at `/v2/indicator/` with 3,180 country-year rows worldwide. It is not a
  possibility the enumeration failed to exclude; it is a worked instance of the gap, and a
  money market rate is the closest thing to a policy path among all candidates named here.
  It carries nothing for these four countries in the window, so the result stands — but the
  enumeration argument reaches only as far as topic 7, and how many further rate
  indicators sit outside it is unmeasured.
- **PWT was screened by page description, not by variable list.** The variable list is
  PDF-locked for this role (see the query table). „No interest-rate variable in PWT" is
  therefore the weakest claim in this file.
- **Not checked:** IMF flows other than `MFS_IR` and `MFS_FMP` — including `MFS_CBS`, which
  was not probed — and whether China reports monetary statistics to the IMF at all outside
  interest rates. The dataflow list was read once, screened by name only, and may be
  paginated.

## Revision 2026-09-08, package 0241

**No figure changed and no query was re-run.** What changed is what the sentences claim:
every negative is now bound to the query it answers. Four substantive corrections —
`FR.INR.MMKT` from „does not exist" to „no row for these four countries, identifier filed
outside WDI and carrying 3,180 rows worldwide"; the topic-7 count stated as an enumeration
of topic 7 with `MMKT` as the documented instance outside it; the CHN row of the
per-country table now names `FR.INR.LEND`, which the file's own coverage matrix carries,
instead of „nothing found in any vetted source"; PWT marked as screened by page
description rather than by variable list. The result is unchanged: **not reachable within
the vetted sources.**
