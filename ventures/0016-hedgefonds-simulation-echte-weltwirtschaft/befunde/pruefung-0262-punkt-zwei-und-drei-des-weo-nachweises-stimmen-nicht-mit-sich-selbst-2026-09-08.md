---
typ: pruefung
paket: 0262-punkt-zwei-und-drei-des-weo-nachweises-stimmen-nicht-mit-sich-selbst
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: three named sites read in the current file, nine values compared digit for digit against the pre-edit copy, and the newly named GGXCNL query re-fetched
befunde: 0
---

# 0262, first round: all three conditions hold, and the new query answers

Line numbers below are the file as it stands now; the acceptance names them as they stood
before the edit (the passage grew, everything at `:283`+ shifted down by up to 11 lines).

## Condition 1 — the count word matches the list

`daten/deckungsbefund-1997.md:289`–`:290` lists **seven** values: USA 2020 = 132,55 and
2021 = 125,05; DEU 2010 = 81,03 and 2020 = 68,04; CHN 2020 = 70,13; BRA 2020 = 96,01 and
2021 = 88,93. The file's own count word is now „sieben", at `:300`.

`Grep -in 'sechs|sieben'` over the file gives exactly three lines, and „sechs" survives on
two of them only inside the retracted sentence — `:294` quotes it, `:296`–`:297` says it
„stand schon in der zurückgezogenen Fassung falsch da und ist hier nur zitiert". That is
true: the pre-edit copy `befunde/messung-0069/baum/daten/deckungsbefund-1997.md:284` reads
„Alle sechs sind". Nothing in the file asserts six in its own voice.

## Condition 2 — the lead-in names the point it means

`:283`–`:284`: „Punkt 1 und Punkt 3 tragen gegen den Auslesefehler; Punkt 2 hält die
Einheit fest und mehr nicht." Point 2 (`:289`, `:292`–`:293`) is the unit point („Was sie
zeigen, ist die **Einheit** … Mehr ist ihnen nicht zu entnehmen"). Point 3 still ends „Der
Punkt trägt über Startjahr und Wertezahl, nicht über die Werte" (`:312`–`:313`, the old
`:304`–`:305`), and Startjahr and Wertezahl are read-out checks. No contradiction remains.

## Condition 3 — the query is named *and* the sentence is scoped

Both halves of the disjunction were done. `:304` retires the original provenance („Welche
Abfrage sie am 2026-09-01 geliefert hat, hält dieser Befund nicht fest."), and `:305`–`:308`
names a re-read dated 2026-09-08.

I fetched that URL myself:
`api.imf.org/external/sdmx/3.0/data/dataflow/IMF.RES/WEO/9.0.0/USA.GGXCNL_NGDP.A?format=sdmx-csv`,
retrieved 2026-09-08 — 2001–2031, 31 values, **2009 = −13.176825, 2020 = −14.126658**,
which round to the −13,18 and −14,13 the file has carried since 2026-09-01. `:309` calls it
„ein zweiter Abruf derselben Quelle, keine zweite Referenz"; that is the correct grade.

**A warning about how this fetch is read.** The first retrieval, prompted for 2009 and 2020
only, came back with 2020 = −11.460685. That is the **2021** value; the summarising step
slipped one year. Narrowing the same call with `startPeriod`/`endPeriod` and asking for the
rows verbatim gave the full 31-row column and settled it. A single-year read-off of an SDMX
answer is exactly the off-by-one this passage exists to guard against — do not grade a value
on one.

## The values, and the lines other files cite

All nine values (the seven above, plus −13,18 / −14,13 at `:302`–`:303`) are digit-identical
with the pre-edit copy in `befunde/messung-0069/baum/`, including their year pairing. Nothing
moved.

The three line-numbered citations into this file still land: `quellenbefund-leitzinspfad.md`
`:55` → `:167` (USA `letztes_jahr` 2020, 24 support points), `:60`/`:236` → `:174`
(`DEU.DISR_RT_PT_A_PT.A` (leer)), `:70` → `:10` (`Reihe 9 USA (endet 2020)`). The edit stayed
below `:214` as the vermerk asked. The only mention of `quellenbefund-leitzinspfad.md` in the
file is the pre-existing one at `:208`.

## Where I looked and found nothing

`Grep 'GGXCNL'` over `daten/` — two hits in this file (`:302`, `:306`, prose plus the new
query) and the `reihen.toml` codes at `:1515`/`:1543`, untouched. No second unnamed retrieval
crept in. Outside the acceptance I did find the frontmatter field `ueberarbeitet:` frozen at
2026-09-02 while four packages have rewritten the body since; that is not this package's and
is proposed as `0266`.
