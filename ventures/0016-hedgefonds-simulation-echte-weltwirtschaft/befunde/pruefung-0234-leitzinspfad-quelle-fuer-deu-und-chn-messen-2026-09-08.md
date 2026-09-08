---
typ: pruefung
paket: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Conditions 1-5 read against the two built files, the cited reihen.toml line numbers and the standing deckungsbefund; 2, 4 and 5 hold, 1 and 3 do not.
befunde: 2
---

# China is not empty, and `reihen.toml` now says it is

## Befund 1 — condition 3: the sentence written into `reihen.toml` is false and refutes itself four clauses later

`daten/reihen.toml:1258` now reads: „Keine von ihnen fuehrt einen Leitzins fuer alle vier
Laender, **und fuer China fuehrt keine einen Zinssatz irgendeines Begriffs**".

Reproduce, without running anything:

1. Read `:1258` on to its next-but-one clause: „Der weiteste Griff einer einzigen Kennung
   reicht ueber drei der vier Laender (**FR.INR.LEND und FR.INR.RINR: USA, CHN, BRA**)".
   China carries values in both. One sentence, both claims.
2. Read the befund the sentence points at, `daten/quellenbefund-leitzinspfad.md:40-42`:
   `FR.INR.RINR` „USA 25, CHN 25, BRA 25 of the years 1997–2021"; `FR.INR.LEND` the same;
   `FR.INR.DPST` „CHN 25, BRA 25". The World Bank is one of the four vetted sources
   (`specs/…/daten.md:8`). China has 25 of 25 window years in three of its indicators.
3. `:65` of that befund calls China's `FR.INR.LEND` value „administered PBoC benchmark
   lending rate" — not merely a rate of some concept, an administered one — and `:83`
   proposes exactly it as China's leg of the mixed path.

The evidence the clause offers carries only the narrower claim: `MFS_IR` gives CHN nothing.
The country empty in every World Bank rate indicator is **Germany** (`:40-42`, DEU 0 three
times). The sentence generalises one source's hole onto all four and swaps the country.
The befund's own H1 (`:9`) carries the same false half.

Condition 3 asks the entry to state the result. It states a wrong one, in the file that
decides which input the world run gets.

## Befund 2 — condition 1: the years for USA and BRA contradict this file's standing measurement, unflagged

Same code `DISR_RT_PT_A_PT`, two numbers, six days apart, nothing reconciling them:

| | quellenbefund `:21-22` (2026-09-08) | `reihen.toml [[reihe.deckung]]` |
|---|---|---|
| USA | 1950–**2023** | `letztes_jahr = 2020` (`:1294`) |
| BRA | 1997–**2024** | `letztes_jahr = 2025` (`:1303`) |

USA is load-bearing: `:1297` judges „verkuerzt -- 2021 fehlt", `luecken_1997_2021 = 1`, and
`deckungsbefund-1997.md:10` names „Reihe 9 USA (endet 2020)" as one of the two series that
force **R = 19**. If the reading to 2023 holds, USA covers the window whole and that number
moves; if it does not, the per-country table is wrong. BRA moves the other way — it shrinks
by a year, which no data update explains.

Condition 1 asks for the years covered. Years that contradict the file's own record without
a word are not a measurement. Round 2 needs one sentence per country: which reading holds,
and read off what. Whether the R chain then needs its own package depends on that answer,
so no proposal is written yet.

## Checked, and not a finding

- **Condition 4 held, and provable without a diff.** All seven line numbers the package
  cites for `reihen.toml` (`:440`, `:441`, `:473`, `:623`, `:655`, `:1258`, `:1667`) still
  land on exactly what it says they do — so no line was inserted or deleted anywhere in the
  file, across the edit point at `:1258`. I read the four citation sites `:440`, `:441`,
  `:655`, `:1667`: each still carries its quotation intact. `:473` and `:623` untouched, as
  the package demands. What I cannot do without a shell is diff the edited value itself;
  the `spiel.md` at `:1258` is an uebergangene Fundstelle, not one of the four citations.
- **Condition 2 held.** One sentence at `:53-56` plus the per-candidate-per-country table
  `:60-66`. The `DISR` asymmetry named as the anchor is addressed and not beaten.
- **Condition 5 held.** Only `api.imf.org`, `api.worldbank.org` and two description pages;
  no key, no account, no payment. The one timeout is written down (`:48-49`), not retried.
- **Internal counts consistent:** the 9, 7 and 11 series names listed for USA, BRA and DEU
  match the counts claimed there and repeated in `:1258`; DEU 1957–2017 is 61 obs.
- **Units not at risk yet**, because nothing was chosen: every candidate is percent per
  year, the basis the existing `[[reihe.umrechnung]]` factor 100 to bp assumes (`:1267`).
