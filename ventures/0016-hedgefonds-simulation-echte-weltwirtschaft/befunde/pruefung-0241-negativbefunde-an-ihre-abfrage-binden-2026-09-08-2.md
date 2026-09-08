---
typ: pruefung
paket: 0241-negativbefunde-an-ihre-abfrage-binden
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: all 39 enumeration rows checked against the sentences they name, plus 5 retrievals; conditions 2 and 3 re-measured mechanically and both hold
befunde: 2
---

# The new WDI paragraph claims wider than the sourceNote it quotes

## Discharged — do not touch

- **Ruecklauf-1 finding 1 (MMKT window).** `:90` „no row for these four countries in the
  window… it returned no row in 1997–2021 — the window of the query in the left column.
  Years outside that window were not queried"; `:109`–`:110` „no row for these four
  countries in 1997–2021, the only window queried". Both bound.
- **Ruecklauf-1 finding 2 (PBoC).** `Grep PBoC|PBOC|People's Bank` over all of `daten/`
  now returns two lines: `lizenzbefund-reihen.md:556` and `quellenbefund-leitzinspfad.md:148`,
  the sentence that disowns the identification. `:33` and `:137` clean.
- **Ruecklauf-1 finding 3 (`reihen.toml:1258`).** Scoped to „allen fuenf Zinskennungen der
  Weltbank **aus Thema 7**", names `FR.INR.MMKT` as the sixth and windows it („im Fenster
  1997 bis 2021 allerdings leer"). `spiel.md` citation byte-identical.
- **Condition 3.** `:623` carries the measured answer and points at the befund; `Grep
  ungemessen` over `reihen.toml` returns `:64`, `:69`, `:80`, `:653`–`:655`, `:691`, `:877`,
  `:884`, `:885`, `:1666`, `:2028` — **not `:623`**.
- **The hard limit holds.** 62 distinct lines carrying `technik.md|spiel.md`, duplicate map
  unchanged: `:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824` 2×, `:1870` 2×, `:2013` 10×.
  Every other line number in the map is unchanged, so nothing was inserted or deleted.
  **Correction to my own round-1 record:** the occurrence total is **80**, not 78 — 55
  singleton lines + 25 on the seven duplicate lines. My 78 was wrong and was copied into the
  note; the 62 and the map are right and they are what condition 3 limits.
- **The enumeration.** 39 rows, 6 marked non-query (`:230`, `:231`, `:238`, `:257`, `:262`,
  `:267`), remainder 33 — the arithmetic holds. All 39 line references land on the sentence
  they name; I checked each.

## Finding 1 — `:145`–`:146` „per country **or at all**", and `:33` contradicts it in the same cell

`:145`–`:146`: „**It names no institution and no instrument, per country or at all**".
The quoted sourceNote at `:142`–`:144` does describe an instrument: „Lending rate is the bank
rate that usually meets the short- and medium-term financing needs of the private sector".

**How to produce it:** read `:33` alone. One cell says „**a bank lending rate**; WDI names
no institution and **no instrument** for it (below)", and the row's Source column is `World
Bank | WDI`. The cell attributes the characterisation to WDI and denies WDI makes it. `:137`
does not have the defect — it says only „no institution named by the source", which is true.

**per country is right; or at all is the over-reach**, and it is mine no longer: my
round-1 finding read „no institution and no instrument **per country**". The enumeration
certifies the wider version as a query answer (`:261`). One clause.

**Not re-fetchable today, so I checked the transcription instead:**
`/v2/indicator/FR.INR.LEND` answered **HTTP 502 three times** (plain, `/v2/en/`,
`source=2`), while `/v2/indicator/FR.INR.MMKT` answered normally in the same minutes — the
outage moved from MMKT to LEND since yesterday. The quote at `:142`–`:145` matches my
2026-09-08 retrieval word for word, ellipsis included.

## Finding 2 — `:272`–`:273` says the 3,180 is „not reproducible today". It is. Not the builder's error

`https://api.worldbank.org/v2/country/all/indicator/FR.INR.MMKT?format=json&per_page=1`,
retrieved 2026-09-08 by me: `page: 1, pages: 3180, per_page: 1, **total: 3180**`. The
endpoint that answered 502 eight times yesterday answers today. The file's own caveat is now
the one false negative in it, dated the same day it is false.

This came from my round-1 report and the builder was told not to fetch, so it is a
correction and not a failure of his. Replace the caveat with the retrieval above.

**Bonus, unasked and it strengthens `:187`:** `/v2/indicator/FR.INR.MMKT` gives
`total: 1`, `sourceNote: "Money market interest rate, IFS line 60b (%)."`,
`source: {id: 11, "Africa Development Indicators"}`, `topics: [{}]` — empty topics, which is
the mechanical proof that MMKT is filed outside topic 7, and IFS line 60b confirmed from the
source rather than asserted.

## What I searched and did not find

Every sentence outside an enumeration row, for an unbound absence: `:11`–`:12` („no account,
no key, no payment"), `:18`–`:19`, `:46`–`:49`, `:158`, `:162`, `:201`, `:211`. All fall
outside the enumeration's own scope sentence (`:221`–`:222`: absence „of a row, a series, an
identifier, a variable, or of policy character") and none asserts one of those five. The
coverage matrix `:114`–`:118` was recounted against `:85`–`:89` and the three prose counts
that read it (`:102` widest reach three, `:120`–`:122`, `reihen.toml:1258` USA three of five
/ CHN four of five) all follow from it.
