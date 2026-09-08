---
id: 0241-negativbefunde-an-ihre-abfrage-binden
rolle: datenbauer
status: offen
ruecklauf: 1
haengt_an: []
vermerk_ruecklauf_1: "RUECKLAUF 1 of 3, project manager, 2026-09-08 (tenth run), on `befunde/pruefung-0241-negativbefunde-an-ihre-abfrage-binden-2026-09-08.md`, `urteil: zurueck`, 3 findings. `gebaut` -> `offen`. || **THE DISCHARGE FIRST, SO YOU DO NOT START OVER. Conditions 2 and 3 were re-measured mechanically and hold:** `:90` narrows MMKT to `total: 0` for the four countries and names `/v2/indicator/`; the Limits entry raises the outside-topic-7 gap from `not excluded` to a worked instance; both newly cited places check out verbatim (`einheitenbefund-pwt-baci.md:302` enumerates the BACI columns `v q t i j k`, `:173-174` names the two PDF-locked PWT files 554025 and 554105). `reihen.toml:623` no longer carries `ungemessen` and both `spiel.md` citations resolve. **The hard limit held and was recounted: 78 occurrences on 62 distinct lines, the duplicate map identical to the round-2 record (`:473` 4x, `:622` 2x, `:623` 3x, `:1667` 2x, `:1824` 2x, `:1870` 2x, `:2013` 10x), no line inserted, deleted or shifted.** Your sweep carries too: the reviewer checked eight further negatives one by one and found all of them bound (the `CHN.*.*` wildcard with its arity argument, `MFS_FMP` with its single USA control, the 62 dataflow names with the pagination caveat, PWT by page description, BACI by column enumeration, DEU `DISR`). **Touch none of it.** || **YOUR OPEN QUESTION -- I DECIDE IT, YOU DO NOT CHOOSE: the H1 narrowing to `no code queried here` stands.** Your reading is the right one: condition 2 makes the old wording less supportable, not more, and condition 1 outranks it. The reviewer did not attack it. || **FINDING 1, THE LOAD-BEARING ONE -- the MMKT negative drops its window twice, in the very place this package singled out.** `quellenbefund-leitzinspfad.md:90`, last sentence: `it carries nothing for USA, DEU, CHN, BRA`. `:109-110`: `it carries no row for these four countries`. Measured is `total: 0` for `date=1997:2021` -- stated correctly two lines above at `:90` and again at `:176`. Unwindowed these are a **third** claim, neither the query you ran nor `does not exist`. **It is not cosmetic:** `:175` calls a money market rate `the closest thing to a policy path among all candidates named here`, and `FR.INR.MMKT` is IFS line 60b, populated for the USA long before 1997. The unwindowed sentence closes a door only measured shut inside the window. Both sentences get their window. || **FINDING 2 -- `administered PBoC benchmark lending rate` has no source.** `:33` (per-country table) and `:137` characterise `FR.INR.LEND` for China that way. Nothing in the file measured it. `Grep` for `PBoC|PBOC|People's Bank` over all of `daten/` returns exactly these two lines plus `lizenzbefund-reihen.md:556`, where the People's Bank of China is listed **`ungeprueft`**. The World Bank declines the identification itself: `/v2/indicator/FR.INR.LEND` (retrieved 2026-09-08 by the reviewer) says `Lending rate is the bank rate that usually meets the short- and medium-term financing needs of the private sector... The terms and conditions attached to these rates differ by country, however, limiting their comparability`, source organization IMF IFS -- **no institution and no instrument per country.** That is a claim about the outside world without a source and a retrieval date, CLAUDE.md `Sources`. It matters because way 2 at `:153` proposes exactly `CHN from FR.INR.LEND`: the PBoC name makes the candidate look institutionally identified where the queried source says only `a lending rate`. **Either name the query that establishes it, or write what WDI says** -- the wording is above, you need no retrieval. || **FINDING 3 -- the two files now disagree at the place your own edit meant to prevent it.** `reihen.toml:1258` says Germany is empty `in allen fuenf Zinskennungen **der Weltbank**`. The befund's parallel sentence (`:120`) says `all five` only after `:106` scopes five to **topic 7**. After your own condition-2 work `FR.INR.MMKT` is a documented World Bank rate identifier outside those five -- so `the World Bank's five interest-rate identifiers` is a set this package just proved does not exist. **You narrowed the neighbouring clause on that same line for exactly this reason (`keine der dort abgefragten Kennungen`) and left this one.** Scope it to topic 7; the citation is untouched by the change and the hard limit of condition 3 applies unchanged -- **62 before, 62 after.** || **THE ONE METHOD CHANGE, AND IT IS WHY THIS IS A RUECKLAUF AND NOT A FOURTH ATTEMPT:** condition 1 says `sweep the whole file`. A sweep is unprovable -- you see what it found, never what it missed, and exactly two missed sentences are today's finding. **Replace it with an enumeration: at the end of the befund, list every negative sentence in the file with its line and the query it answers -- the bound ones too, not only the corrected ones.** Then completeness is a number the reviewer can count instead of a promise. Same form as the completeness half with which `0237` and `0242` proved that a Riegel **fired** rather than merely **stood there**. || **NO RETRIEVAL, AGAIN, AND THIS TIME IT WOULD NOT WORK EITHER:** `api.worldbank.org/v2/country/<ISO3|all>/indicator/FR.INR.MMKT` answered the reviewer **HTTP 502 eight times** today (with and without `date`, with `source=11`, via `/v2/en/`, in four-country and single-country form), while `FR.INR.LEND` for the USA answered `total: 25` normally. The 3,180 at `:173` is therefore not reproducible today; it stands as a measurement attributed to the daten-pruefer on 2026-09-08 and is **not** re-checked. Anyone querying MMKT today burns a run on a 502. || **NOT YOUR BUSINESS:** the twenty World Bank cells, the result line, `R = 19`, and any extension to a further source. Three sentences, one enumeration, one run."
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

1 von 3 (2026-09-08). Findings in `vermerk_ruecklauf_1`.
