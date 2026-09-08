---
typ: pruefung
paket: 0256-die-richtigen-zahlen-fuer-weo-an-eine-abfrage-binden
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: both „richtigen Zahlen" claims read as retracted-and-scoped at `:293`–`:299` and `:302`–`:307`, all eight values matched digit for digit against the pre-edit copy in `messung-0069/baum/`
befunde: 3
---

# 0256 — both claims retired, values intact; three defects outside the acceptance

## What the acceptance says and how I checked it

**Claim 1** (was `:289`–`:291`, „Alle sechs sind die richtigen WEO-Werte. Eine um ein Jahr
verschobene Zuordnung hätte sie verfehlt."). Now `deckungsbefund-1997.md:293`–`:296`:
retracted with its date („Bis 2026-09-08 stand hier …"), and scoped — the values carry
only „die **Einheit**", „Mehr ist ihnen nicht zu entnehmen." Both acceptance routes are
in fact satisfied: `:291` binds them to „des oben genannten Einzelabrufs, abgerufen
2026-09-01", and that Einzelabruf exists at `:260`–`:261`
(`api.imf.org/external/sdmx/3.0/data/dataflow/IMF.RES/WEO/9.0.0/<Land>.GGXWDG_NGDP.A?format=sdmx-csv`).

**Claim 2** (was `:293`–`:294`, „— die richtigen Zahlen"). Now `:302`–`:303`: „**nicht
gegen eine Referenz geprüft** (der Satz … ist aus demselben Grund zurückgezogen)", scoped
to the sign convention.

**Every value unchanged.** Compared against the pre-edit copy
`befunde/messung-0069/baum/daten/deckungsbefund-1997.md:280`–`:288`: 132,55 / 125,05 /
81,03 / 68,04 / 70,13 / 96,01 / 88,93 and −13,18 / −14,13 identical, „ebenfalls 2001",
„31 Werte" identical, and point 1 (`:286`–`:288`) byte-for-byte the old `:280`–`:282`.

**Also checked:** the retired argument has no residue — `verschoben|Zuordnung|bekannte
Zahlen` over `daten/` hits only `:295`, inside the retraction itself. Nothing is asserted
about `quellenbefund-leitzinspfad.md`: the only mention in the whole file is `:208`, in
the `DISR` section, pre-existing. No reference broke: every line citation into this file
(`:10`, `:79`, `:167`–`:174`, `:203`–`:214`) sits above the edited region. „Die einzige
weitere Schuldenreihe hier ist die Weltbankreihe weiter unten" holds — `GGXWDG_NGDP` and
`GC.DOD.TOTL.GD.ZS` (`:316`–`:318`) are the only two, and `GGXCNL_NGDP` is a balance.

## Three defects, none of them the acceptance criterion

1. **`:299` says „die sechs Werte"; `:289`–`:290` lists seven.** USA 2020, USA 2021, DEU
   2010, DEU 2020, CHN 2020, BRA 2020, BRA 2021. The miscount is inherited (old `:284`,
   and the package's own table calls them „six WEO values"), but `:299` is a *new*
   sentence and repeats it. `:294` is exempt — there „sechs" is inside a faithful quote.
2. **`:283`–`:284` mis-maps its own list.** „Zwei davon tragen gegen den Auslesefehler;
   das dritte hält die Einheit fest" — the unit point is number **2**. A reader following
   „das dritte" lands on `:304`–`:305`, which says the opposite of itself: „Der Punkt
   trägt über Startjahr und Wertezahl, nicht über die Werte."
3. **Point 3 now rests its weight on an unnamed retrieval.** The new `:304`–`:306` moves
   point 3 onto „Startjahr und Wertezahl", and no `GGXCNL_NGDP` query is named anywhere
   in the file (grep `GGXCNL` over `daten/`: one hit, `:300`, the prose). The passage that
   was bound got bound; the load moved to a sentence that never was.

Reproduce 1 and 3 by reading `:289`–`:290` and grepping `GGXCNL` over `daten/`.
All three are one edit in one passage; proposed as `0262`.
