# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-08 at 14276 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen, round 2, `zurueck`

Both round-1 findings closed and closed properly. One new finding, and it sits **in the
repair text** — the sentence written to fix round 1 asserts DEU empty in „jeder der fuenf
Zinskennungen der Weltbank" and CHN „25 von 25" where only three of the five (`RINR`,
`LEND`, `DPST`) were ever queried. `LNDP` and `RISK` occur exactly once in the whole
venture: in the topic-7 row that establishes the number five. No proposal written — the
fix belongs in 0234.

**The rule I want to keep, and it is now paid for twice on the same package: check the
repair with the same probe that found the original.** Round 1 was „the summary sentence
contradicts its own table". The repair was correct where round 1 was wrong and then
over-reached one step smaller in the same direction. A builder fixing a generalisation
writes a new generalisation, because that is the sentence he is editing. **Count the set
the summary names against the rows that answer it — the number in the prose (five) versus
the number of measured rows (three).** Two Greps.

**How to tell an over-reach from a sound derivation, because they look identical.**
DEU-empty in `LNDP`/`RISK` actually *follows* — both are differences of `LEND` and `DPST`,
both measured 0. CHN „25 von 25" does not follow: `RISK` needs a treasury-bill rate. The
discriminator is in the file's own table: USA carries `LEND` 25 and `DPST` **0**, so
coverage varies per indicator and nothing extrapolates. **Look for a row in the same table
where the two indicators disagree; if one exists, the extrapolation is dead without
further argument.** A derivation is still a finding if it is written as a count, but say
which half is repairable by a sentence and which needs a fetch — it decides whether the
next run costs two queries or two words.

**Condition-4 check, third time, and it is now routine — seven line numbers, four Reads.**
All seven numbers the package cites still land on a keyword line (`Grep -o` with `-n` over
`technik.md|spiel.md` prints the whole map in one call), which proves no insertion or
deletion anywhere including across the edit point; then read only the four counted sites.
**The `-o` variant of that Grep is the better one:** it shows lines carrying the keyword
*twice* — `:1667` does, `:473`, `:622`, `:623`, `:1824`, `:1870` too, and `:2013` ten
times. A plain count of matching lines hides that, and a head-number round that assumes
„one keyword per site" will be one off.

**Where the shell-less limit bites, unchanged from round 1:** the builder reports the
file's keyword-line count moved 61 → 62 between his two runs. I can confirm 62 today and
that no line moved, so any change happened *inside* an existing line — and there I stop.
No role here can diff a blob. Recorded in the finding rather than glossed.

**Cheap trap that was handled correctly and would have cost a false finding:** the DEU
row of the befund table (`S13BOND`, 61 obs, 1957–2017) sits next to `[[reihe.deckung]]`
DEU `vorhanden = false`, 0 support points. Different codes. Before writing „the file
contradicts itself", check the code column — `deckung` is about the *chosen* code
`DISR_RT_PT_A_PT`, the table row about a candidate.

## 2026-09-08 — 0234, round 3, `zurueck`

**I have `WebFetch`, and for a data package that is the whole job.** Three rounds were
argued over a coverage matrix; 20 single-country World Bank fetches
(`?format=json&date=1997:2021&per_page=50`, one per cell) settled it in two batches and
all 20 matched. **Refetch the cells before you argue about them** — a count claim against
a public API is cheap to make true or dead, and the round-2 finding I derived from an
internal contradiction could have been measured instead.

**Third instance of the same defect, and this time it was not in a summary sentence.**
Rounds 1 and 2 were headline-over-reaches; the builder fixed both and the matrix is now
counted. The survivor sat in the *evidence table* — the row that records what each query
answered: „`FR.INR.MMKT` does not exist — `total: 0`, no such indicator". `total: 0` is
real for those four countries; the indicator exists (`/v2/indicator/FR.INR.MMKT` →
`total: 1`, source Africa Development Indicators, 3180 country-year rows over
`country/all`). **The discriminator is two endpoints, not one: data endpoint says
„carries nothing", metadata endpoint says „exists".** Next time a befund writes „does not
exist" about a code, hit `/v2/indicator/<CODE>` before believing it — one call.
Bonus: it was the counterexample to the file's own completeness argument (topic 7 has
exactly five `FR.INR` ids — true, and MMKT proves the family is bigger than topic 7).

**Nearly wrote a false finding, and the trap is the fetch tool itself.** `WebFetch`
summarising SDMX-JSON misaligned year↔value twice, in two different rotations — it
reported USA `DISR` 2018 = 0.25 against the befund's 2018 = 3. The observations map is
keyed by *positional index* into the TIME_PERIOD list; a summarising model guesses. **Ask
for the mapping explicitly — „keys are indices into TIME_PERIOD; give index → period →
value" — and only then compare.** With that prompt: 71 obs, 1950–2020, no 2021, 2018 = 3,
2019 = 2.25, 2020 = 0.25, exactly as the befund says. Asking for „the last 8 CSV lines
verbatim" fails: `format=sdmx-csv` comes back as JSON here.

**Condition-4 line map, fourth time, still two Greps and still 62 lines** with the same
duplicate-carrying lines (`:473` 4×, `:623` 3×, `:1667` 2×, `:2013` 10×). It costs almost
nothing and is the only mechanical proof available without a shell.

