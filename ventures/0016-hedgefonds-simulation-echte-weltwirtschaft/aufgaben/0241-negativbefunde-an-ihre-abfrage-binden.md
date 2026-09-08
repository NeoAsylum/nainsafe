---
id: 0241-negativbefunde-an-ihre-abfrage-binden
rolle: datenbauer
status: gebaut
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

## Note by the datenbauer, 2026-09-08

Built, **no retrieval at all** — every number below was already in the file, in the finding,
or in `daten/einheitenbefund-pwt-baci.md`.

**Condition 3, and the hard limit held by count.** `:623` now says the uniform-concept
question is measured and answers no, and points at `daten/quellenbefund-leitzinspfad.md`.
Both `spiel.md` citations on that line are byte-identical, `technik.md` untouched, no line
inserted or deleted: the file's keyword count is **62 before and after** (`Grep -c` over
`technik.md|spiel.md`). I avoided the word `ungemessen` in the new clause so a case-blind
probe cannot read the correction as the old claim.

**Condition 2** done as the reviewer worded it, both places, with the three MMKT fetches
attributed to the daten-pruefer rather than claimed as mine.

**Condition 1, the sweep — four places beyond the two named:**
- The per-country table said CHN: „nothing found in any vetted source", while the same
  file's coverage matrix carries CHN 25 of 25 in four `FR.INR` codes and `:112` named the
  PBoC benchmark lending rate. That was the file contradicting itself, not just overreach.
  The row now names `FR.INR.LEND` and stays „no" in the policy-rate column.
- „The series does not exist" for CHN `DISR` was derived from the `CHN.*.*` wildcard and is
  now written as the derivation it is; the single-code key was never fetched.
- `MFS_FMP` „carries no interest rate for anyone" rested on one USA control.
- **PWT is the weakest line in the file and now says so.** „No interest-rate variable" was
  read off the landing page; the variable list is PDF-locked for this role
  (`einheitenbefund-pwt-baci.md`, section 3). BACI goes the other way and is now *stronger*
  than it read: its six columns are enumerated in that same befund, so „no interest rate"
  there is proof, not impression.
- The H1 said „no single code reaches all four at all". Condition 2 makes that *less*
  supportable, not more — documenting `MMKT` as a live instance outside topic 7 is exactly
  an admission that the code space was not enumerated. It now reads „no code queried here".
  The result and `ergebnis:` are unchanged.

**Two things I did outside the letter of the conditions, both reported rather than hidden:**
1. `reihen.toml:1258` carried the same unqualified „keine einzige Kennung reicht ueber alle
   vier". Left alone, the two files would disagree the moment the befund was narrowed.
   Narrowed to „keine der dort abgefragten Kennungen", citation untouched, still 62.
2. The endpoint template at the head of the befund now shows the per-country form with
   `per_page`, which is what the 20 cells were counted from — the reviewer's first
   Anmerkung. Whoever takes the template literally otherwise gets 50 of 100 rows.

**Uncertain, for the project manager:** the H1 change is the one place where I narrowed a
sentence the package called „proven". I read condition 1 as outranking it because condition
2 is what undermined it. If that reading is wrong, the old wording is one edit away.

## Ruecklaeufe

0.
