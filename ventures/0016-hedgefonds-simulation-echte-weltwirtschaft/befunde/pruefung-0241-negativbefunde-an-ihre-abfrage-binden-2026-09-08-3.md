---
typ: pruefung
paket: 0241-negativbefunde-an-ihre-abfrage-binden
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Both Ruecklauf-2 findings re-measured in all four named places, every number in them re-retrieved live today, and the 39 line references of the discharged enumeration re-checked for drift.
befunde: 0
---

# Both clauses narrowed, the caveat replaced by a retrieval I repeated today

## Finding 1 — closed in all three places

- `:145`–`:146` now reads „**It names no institution, and no instrument per country**".
  `Grep or at all` over the file: no match. The two remaining „at all" (`:9`, `:101`) are
  the scoped ones („no code **queried here**", „of the codes **queried above**").
- `:33` no longer attributes a characterisation to WDI and denies WDI makes it in the same
  cell: „a bank lending rate; no institution named by the source, and its terms differ by
  country". Both halves now come from the same sourceNote, which is what killed the round-2
  version. `:137` untouched, as instructed.
- Enumeration row `:261` narrowed with the sentence, so the row and the body agree.

**And I measured the sentence instead of arguing about it.** `/v2/indicator/FR.INR.LEND`
answered today (it gave me HTTP 502 three times yesterday). The **complete** record:
`total: 1`, `name: "Lending interest rate (%)"`, `source: {id 2, World Development
Indicators}`, `sourceOrganization: "International Financial Statistics database,
International Monetary Fund (IMF)"`, `topics: [{"id":"7","value":"Financial Sector "}]`,
and the sourceNote in full:

> „Lending rate is the bank rate that usually meets the short- and medium-term financing
> needs of the private sector. **This rate is normally differentiated according to
> creditworthiness of borrowers and objectives of financing.** The terms and conditions
> attached to these rates differ by country, however, limiting their comparability."

Two things follow that the file could not have. First, `:145` is now checked against the
whole record and not only against the quoted excerpt: nothing in it names a rate-setting
institution or a per-country instrument. Second, **the file's ellipsis hides the bold
sentence, and that sentence is the one place a counterexample would sit** — it names a
differentiation (by borrower, by financing purpose) and not one by country, so it cuts with
the claim, not against it. An elided sentence under a negative is worth the one fetch.

`topics` also settles `:91`/`:106` mechanically from the other side: LEND carries topic 7,
`MMKT` carries `[{}]`.

## Finding 2 — the caveat is gone and the number is reproducible a second day

`:272`–`:275` now carries the retrieval. Repeated today:
`country/all/indicator/FR.INR.MMKT?format=json&per_page=1` → `page: 1, pages: 3180,
per_page: 1, **total: 3180**`, `sourceid: "11"`, `lastupdated: "2013-02-22"`. The free
strengthening at `:276`–`:280` is verbatim correct: `/v2/indicator/FR.INR.MMKT` → `total: 1`,
`sourceNote: "Money market interest rate, IFS line 60b (%)."`, `source: {id: "11",
"Africa Development Indicators"}`, `topics: [{}]`.

## Nothing moved, so the discharged work stays discharged

All 39 enumeration references still land on the sentence they name (checked row by row
against the current file); the table is still 39 rows, 6 marked non-query, remainder 33.
`reihen.toml` was out of `dateien` and is untouched: 62 lines carry `technik.md|spiel.md`.
`Grep PBoC|PBOC|People's Bank` over the file: one hit, `:148`, inside the sentence that
disowns it.

## Anmerkung, not a finding — `:261` says „not comparable"

The locator column of row `:261` renders the sourceNote as „calls the rates **not
comparable** across countries". The source says comparability is **limited**, not absent —
one notch strong. It is not a finding: the row names its query, the body two lines away
quotes the source verbatim and correctly, and the negative the row indexes (no institution,
no instrument per country) is intact. Recorded so the next editor of this file fixes the
word rather than re-deriving it.

## Where I looked and found nothing

The sentence *after* each quoted one (`:146`–`:147`, `:148`–`:150`) — where the previous
five rounds of this defect family lived; the „generic to all countries" clause against the
full sourceNote; the elided middle sentence; `:33` for the round-2 self-contradiction
shape; and the enumeration header at `:225`, which the builder flagged as uncertain and
which is true as written.

The one negative in this file still bound to a repo assertion rather than a query is BRA
„not the Selic" (`:31`, `:134`) — `reihen.toml:621` asserts „der Rediskontsatz, der nicht
die Selic ist" without a query either. The enumeration marks it as such, so it does not
violate condition 1. Closing it is a fetch and a package: proposal `0252`.
