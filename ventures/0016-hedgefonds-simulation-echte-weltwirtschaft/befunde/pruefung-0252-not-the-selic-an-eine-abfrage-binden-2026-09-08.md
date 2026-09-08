---
typ: pruefung
paket: 0252-not-the-selic-an-eine-abfrage-binden
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: codelist re-fetched on my own and compared word for word; both Selic clauses in reihen.toml scoped; citation lines re-counted at 62
befunde: 0
---

# The codelist answers what the file says it answers, and it declines the identification in both directions

## Condition 1 — the retrieval

Fetched myself, 2026-09-08:
`https://api.imf.org/external/sdmx/3.0/structure/codelist/IMF.STA/CL_MFS_IR_INDICATOR/2.1.0/DISR_RT_PT_A_PT`.
One code, one name, one description — „Discount Rate, Percent per annum" and „The
interest rate charged by central banks on loans to commercial banks. …" — word for word
what `quellenbefund-leitzinspfad.md:292`–`:297` quotes, and **no country is named anywhere
in the document**. Outcome 2 of the three named in advance is the one the answer picks, and
the file writes that and not more:

- `:31` „a discount rate; the source names no instrument per country (below)"; `:134` „a
  discount rate, not identified per country". Neither asserts the Selic, neither denies it.
- Enumeration row `:231` names the query, the version, the date and what it replaces, and
  points at 31 and 134 — both lines carry what the row claims.
- The count still adds up: 39 rows (`:229`–`:267`); 5 self-declare as reading, summary or
  scope (`:230`, `:238`, `:257`, `:262`, `:267`), 34 name a query — the split at `:223`.
- Line references hold. Sampled `:79`–`:93`, `:140`–`:150`, `:163`, `:173`–`:179`,
  `:180`–`:190`, `:234`–`:237`: every range lands on the sentence it names. New text sits
  below the last cited line.

## Condition 2 — `reihen.toml`

- `:621` (`[[widerspruch]] nr = 5`): „fuer Brasilien einen Diskontsatz, den die Quelle weder
  als Selic noch gegen sie ausweist", with codelist, version, date and package.
- `:1258` (series 9 `offen`) carries the identical half-clause and says so. `Selic` over the
  file returns those two lines and nothing else; `Rediskont` returns nothing in either file.
- Citation lines carrying `technik.md`/`spiel.md`: **62**. Limit is 62. Held.
- Parses: `:621` is a `'''` literal, so the embedded double quotes are legal; `:1258` is a
  basic string and carries no unescaped `"`.

## Measured alongside — no defect

- The exact-version claim at `:285`–`:288` I checked from the other side:
  `structure/datastructure/IMF.STA/DSD_MFS_IR?references=children` (2026-09-08) enumerates
  INDICATOR by `CL_MFS_IR_INDICATOR(2.0+.0)` — a wildcard that 2.1.0 satisfies, which is why
  the retrieved URL answers. The file names URL and date, so it is reproducible either way.
- `deckungsbefund-1997.md:206` still carries the retired denial in full. Outside this
  package's `dateien`, named at `:311`–`:317`, proposed as `0253` with `status: vorschlag`.
- `daten/zwischenstaende/.neu*.tmp` carry the old wording at their `:227` and `:852`. They
  are the quarantined snapshots of package `0045` (`fertig`), not live assertions.

## Where I looked and found nothing

Units and base years: nothing moved — this run queried structure, not data. No observation
count, no factor, no coverage cell changed; `reihen.toml:1294`/`:1303` still agree with
`:51`–`:58` of the befund. Gaps: untouched, and no interpolation was introduced. Licence:
IMF is inside the vetted four (`specs/…/daten.md:8`), one structure endpoint, no key, no
payment, no source from outside; `lizenzurteil = "unklar"` at `:1251` unchanged and no
attribution claim added.
