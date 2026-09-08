---
typ: quellenbefund
gegenstand: Reihe 9 (Leitzins) -- source for the policy-rate path, USA / DEU / CHN / BRA
paket: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
datum: 2026-09-08
ergebnis: not reachable within the vetted sources
---

# No vetted source carries a policy rate for all four countries, and none carries a rate of any concept for China

Measured 2026-09-08 against the four sources vetted in `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md`, line 8. Every endpoint
below is freely retrievable: no account, no key, no payment.

IMF endpoint, same for every key: `https://api.imf.org/external/sdmx/3.0/data/dataflow/IMF.STA/<FLOW>/<VERSION>/<KEY>`
World Bank endpoint: `https://api.worldbank.org/v2/country/USA;DEU;CHN;BRA/indicator/<CODE>?format=json&date=1997:2021`

## Per country: the nearest candidate found

| Country | Source | Flow | Code | Years | What it measures | Policy rate? |
|---|---|---|---|---|---|---|
| USA | IMF | `MFS_IR` 9.0.0 | `DISR_RT_PT_A_PT` | 1950–2023 | Fed discount-window rate | administered, not the target rate |
| BRA | IMF | `MFS_IR` 9.0.0 | `DISR_RT_PT_A_PT` | 1997–2024 | rediscount rate, **not the Selic** | administered, not the target rate |
| DEU | IMF | `MFS_IR` 9.0.0 | `S13BOND_RT_PT_A_PT` | 1957–**2017**, 61 obs | government bond yield | **no** — a market price |
| CHN | — | — | — | — | — | **nothing found in any vetted source** |

The German window shortfall is exact: 1997–2017 all carry a value, 2018–2021 carry none
(`DEU.S13BOND_RT_PT_A_PT.A`, retrieved 2026-09-08). This confirms the operator's count of
2026-09-05 (`daten/nachmessung-zinsreihen-2026-09-05.md`) against the series itself.

## What was tried, and what each answered

| Query | Answer, retrieved 2026-09-08 |
|---|---|
| `MFS_IR/9.0.0/USA.*.A` | 9 annual series: `DISR`, `GSTBILY`, `GSTBILY_S3M`, `MFS134`, `MFS162`, `MFS166`, `MMRT`, `S13BONDS_SMT`, `S13BOND` (all `_RT_PT_A_PT`) |
| `MFS_IR/9.0.0/BRA.*.A` | 7 annual series: `DISR`, `GSTBILY`, `MFS135` (1982–1993), `MFS162`, `MFS166`, `MFS174` (1982–1993), `MMRT` (1964–1981) |
| `MFS_IR/9.0.0/DEU.*.A` | 11 annual series: ten MFI bank rates (`HEANBLCCO…`, `HENBD_LT2…`, `HENBD_STO1…`, `HENBL_NB_CFR…`, `HENBL_OY5…`, `HENBL_STO1…`, `HEOADAM_LT2…` 2008–2020, `HERLOBO1EUR…`, `MFS151…`, `MFS2123…`; the other nine 2003–2023) plus `S13BOND` |
| `MFS_IR/9.0.0/CHN.*.*` | **no observations, at any frequency.** Same key arity that returns data for the three other countries, so this is a real absence, not a malformed query |
| `MFS_FMP/3.0.0/CHN.*.*.A` | empty. Positive control `USA.*.*.A` returns 4 series — `EPAMEX`, `EPSP`, `EQTS`, `NASDAQ`, equity price indices, 1950/1971/1972–2016. This flow carries no interest rate for anyone |
| `structure/dataflow/IMF.STA` | 62 dataflows read; none named for policy or central-bank rates. `MFS_IR` is the IMF's interest-rate flow |
| WDI `FR.INR.RINR` (Real interest rate, %) | USA 25, CHN 25, BRA 25 of the years 1997–2021; **DEU 0** |
| WDI `FR.INR.LEND` (Lending interest rate, %) | USA 25, CHN 25, BRA 25; **DEU 0** |
| WDI `FR.INR.DPST` (Deposit interest rate, %) | CHN 25, BRA 25; **USA 0, DEU 0** |
| WDI `FR.INR.MMKT` | does not exist — `total: 0`, no such indicator |
| WDI topic 7 (Financial Sector), `https://api.worldbank.org/v2/topic/7/indicator?format=json&per_page=500` | exactly five `FR.INR` indicators: `DPST`, `LEND`, `LNDP`, `RINR`, `RISK`. **None is a policy, discount or refinancing rate** |
| PWT 11.0, `https://www.rug.nl/ggdc/productivity/pwt/` | no interest-rate, policy-rate or central-bank-rate variable |
| CEPII BACI, `https://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37` | bilateral trade flows by product only; no monetary variable |

One fetch failed and is recorded rather than retried into the ground: `FR.INR.LEND` with
`per_page=200` exceeded 60 s; the same query with `per_page=120` answered.

## Is a uniform interest-rate concept reachable?

**No — and the gap is worse than non-uniformity: no single code reaches all four countries
at all.** The widest reach of any one code is three of four (`FR.INR.LEND`, `FR.INR.RINR`:
USA, CHN, BRA, Germany empty), and neither is a policy instrument. Germany is empty in
every World Bank rate indicator; China is absent from the IMF's entire interest-rate flow.

What each candidate measures, per country:

| Candidate | USA | DEU | CHN | BRA |
|---|---|---|---|---|
| `DISR_RT_PT_A_PT` | Fed discount-window rate | absent | absent | rediscount rate, not the Selic |
| `S13BOND_RT_PT_A_PT` | govt bond yield | govt bond yield, ends 2017 | absent | absent |
| `MMRT_RT_PT_A_PT` | money market rate | absent | absent | 1964–1981 only |
| `FR.INR.LEND` | bank lending rate | absent | administered PBoC benchmark lending rate | bank lending rate |
| `FR.INR.RINR` | lending rate less GDP deflator | absent | same, deflated | same, deflated |

The known asymmetry the package named as the anchor to beat is not beaten: `DISR` remains
two concepts across two countries, and every alternative either drops a country or drops
the policy character.

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
- **Not checked:** IMF flows other than `MFS_IR` and `MFS_FMP`, and whether China reports
  monetary statistics to the IMF at all outside interest rates. The dataflow list was read
  once and may be paginated.
