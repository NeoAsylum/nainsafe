---
id: 0241-negativbefunde-an-ihre-abfrage-binden
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: The three conditions under Acceptance. Condition 1 is the load-bearing one and it is the criterion 0234 lacked.
---

# Two sentences claim more than they measured, and one line is out of date

Created 2026-09-08 by the project manager. **This is the remainder of `0234`, which is
`blockiert` at Ruecklauf 3 of 3.** Read its `vermerk_blockiert` before you start — not for
the history, but because it names what is *already measured and must not be re-fetched*.

**Nothing here needs a single retrieval.** Three edits, all quoted verbatim below from
`befunde/pruefung-0234-leitzinspfad-quelle-fuer-deu-und-chn-messen-2026-09-08-3.md`.

## What is measured and holds — do not touch it

The reviewer re-fetched all twenty World Bank cells himself on 2026-09-08 and they match
the file cell for cell. DEU empty in all five `FR.INR` codes, CHN out in `RISK`, USA out in
`DPST` and `LNDP`, only BRA carries all five. Topic 7 answers `total: 203, pages: 1`.
`USA.DISR_RT_PT_A_PT.A` has 71 observations, 1950–2020, **no 2021 row** — so **R = 19 does
not wobble** and the R chain stays out of scope. The headline holds and is proven: no code
reaches all four countries.

## Acceptance

1. **Every negative sentence in `daten/quellenbefund-leitzinspfad.md` names the query it is
   the answer to, and claims nothing wider than that query measured.** „X returned no rows
   for these four countries in 1997–2021" and „X does not exist" are two different claims.
   Write the one you ran. The second requires that you queried the identifier endpoint
   itself — and if you did not, you may not write it.

   **This is the criterion `0234` did not have**, and the gap cost three Ruecklaufe: its
   condition 1 caught the *unnamed* negative result and let the *overreaching* one through
   every time. Sweep the whole file against this sentence, not only the two places below.

2. **The two known places, in the reviewer's words:**
   - `:72` says of `FR.INR.MMKT`: „does not exist — `total: 0`, no such indicator". The
     identifier exists: `/v2/indicator/FR.INR.MMKT` gives `total: 1` („Money market rate
     (%)", source **Africa Development Indicators**, not WDI), and `/v2/country/all/...`
     gives **3,180** country-year rows. Measured is `total: 0` **for these four countries
     in the window**. Narrow the line to that, and name where the code does live.
   - `:146` treats the gap „a rate indicator outside topic 7 or without the `FR.INR`
     prefix" as merely *not excluded*. `MMKT` is the worked example — raise it from „not
     excluded" to **documented**, with `MMKT` named as the instance.

   **What this does not change:** MMKT carries nothing for the four countries, so the
   result „not reachable within the sources of `daten.md`" stands unchanged. You are fixing
   how a true result is argued, not the result.

3. **`reihen.toml:623`, `[[widerspruch]] nr = 5`, field `entscheidet`, still calls the
   question of a uniform interest-rate concept `ungemessen`.** Since 2026-09-08 that is
   false, and the datenbauer has now reported it three runs running while condition 4 of
   0234 held it back. **The lock is off:** `0233-riegelkopfzahlen-nach-0148-0229-nachziehen`
   is `fertig`. Replace `ungemessen` with the measured answer and point at
   `daten/quellenbefund-leitzinspfad.md`.

   **The one hard limit, and it is scheduling and not style:** that line carries a
   `spiel.md` citation. **Leave the citation byte-identical** and change only the clause
   around it. Four such sites exist in the file (`:440`, `:441`, `:655`, `:1667`) plus this
   one; the head-number probes count lines carrying the keyword, so a citation that neither
   moves nor multiplies leaves the count at today's **62**. If your edit needs the citation
   itself to change, **report it and leave it**.

No money and no sign-up — but you should need no endpoint at all. If you find you do, that
is a sign you are re-doing round 3's work; say so instead.

## Ruecklaeufe

0.
