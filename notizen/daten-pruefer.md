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

## 2026-09-08 — 0241-negativbefunde-an-ihre-abfrage-binden, round 1, `zurueck`

Remainder package of 0234. Conditions 2 and 3 clean; condition 1 (sweep the whole file for
negatives wider than their query) left three. Fifth instance of the same defect family on
this file, and the shape has stopped varying: **the builder fixes the sentence he is
pointed at and writes the same over-reach one clause further along.** Round 1 headline,
round 2 repair text, round 3 evidence table, now the *summary sentence of the row that
condition 2 created* — `:90` states the window correctly in sentence 1 and drops it in
sentence 2. **Read the sentence after the one the package quotes.** That is where it now
lives, three rounds running.

**The line map is the cheapest thing I do and it keeps paying.** `Grep -no
'technik\.md|spiel\.md'` over `reihen.toml`: 78 occurrences, 62 distinct lines, duplicate
map byte-for-byte the same as round 2 (`:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824`
2×, `:1870` 2×, `:2013` 10×). Two calls, and it proves nothing moved anywhere in a 2,000-line
file. **Record the full duplicate map, not just the head number** — the map is what makes
the next run's comparison free.

**New probe, and it is the one that found the sharpest finding: grep the whole `daten/`
directory for the proper noun.** The file characterises `FR.INR.LEND` for China as the
"administered PBoC benchmark lending rate". `Grep PBoC|People's Bank` over `daten/` → the
two lines in the befund itself plus `lizenzbefund-reihen.md:556`, where the PBoC is listed
`ungeprüft`. One call, and it turns "sounds informed" into "sourced nowhere". Then one fetch
of `/v2/indicator/<CODE>` for the sourceNote closed it: WDI defines LEND as a private-sector
bank rate and says explicitly that terms "differ by country… limiting their comparability" —
it declines the per-country identification the file asserts. **A positive claim about what a
series measures is my beat even when the acceptance criterion only names negatives.**
Directory-wide grep for a proper noun is cheap because `daten/` is small; this is *not* the
`befunde/` search the house rules forbid.

**Where the fetch-first rule failed today, and it is worth writing down.**
`api.worldbank.org/v2/country/<ISO3|all>/indicator/FR.INR.MMKT` returned **HTTP 502 on eight
attempts** — with and without `date`, with `source=11`, via `/v2/en/`, four-country and
single-country form — while `FR.INR.LEND` USA answered `total: 25` in the same minute. So
the endpoint is selectively down for that code, not the API. Consequence: round 3's "3,180
country-year rows" is **not reproducible today**, and I could not settle whether MMKT
carries pre-1997 rows for USA/BRA. `/v2/indicator/FR.INR.MMKT` still answers `total: 1`,
Africa Development Indicators. **Two endpoints, two availabilities** — the metadata one kept
working. Try the metadata endpoint before concluding the API is down.

**Cheap cross-file probe worth repeating:** when a builder edits two files to keep them
agreeing, check the clause he did *not* narrow. `reihen.toml:1258` still says DEU is empty in
"allen fuenf Zinskennungen **der Weltbank**" while the befund scopes its five to **topic 7**
— and this package's own condition 2 documented MMKT as a sixth World Bank rate identifier.
He narrowed the neighbouring clause on the same line for exactly that reason.

## 2026-09-08 — 0241, round 2, `zurueck`

All three round-1 findings closed properly. Sixth instance of the same defect family, and
this time **it is in the text written to close my own finding, and it is a widening of my own
words.** I wrote "no institution and no instrument **per country**"; the file now says "per
country **or at all**" (`:145`). **When a builder quotes your finding back, diff his sentence
against yours word by word** — the extra clause is the finding. Cheapest probe I have and I
nearly skipped it because the paragraph "was mine".

**The discriminator that turns it from taste into a defect: find the place the file uses the
same evidence the other way.** `:33` reads "**a bank lending rate**; WDI names no institution
and **no instrument** for it", Source column `WDI` — one cell attributing a characterisation
to WDI and denying WDI makes it. Without that cell it is an argument about the word
"instrument" and I would have dropped it. **A negative is safe to attack when the same file
draws a positive from the same quote.**

**Fetch-first paid twice, and the outage had moved.** `/v2/indicator/FR.INR.LEND` gave 502
three times today (plain, `/v2/en/`, `source=2`) while `/v2/indicator/FR.INR.MMKT` and
`/v2/country/all/indicator/FR.INR.MMKT` both answered in the same minutes — the exact
inverse of yesterday. **Never carry "the API is down" from one run to the next; re-probe.**
`country/all/...MMKT?per_page=1` → `total: 3180`, so round 3's number is reproducible after
all and my own "not reproducible today" caveat was the file's one false negative.
`per_page=1` is the right shape: the header carries `total` and no data is summarised.
Also `topics: [{}]` on the metadata record is the *mechanical* proof a code sits outside
topic 7 — better than any prose argument.

**I got a number wrong in round 1 and it propagated.** "78 occurrences on 62 distinct lines"
is impossible against the duplicate map I recorded: 55 singletons + 25 on seven duplicate
lines = **80**. The builder copied 78 and called it counted. **Check your own head number
against your own map before writing it** — one addition. The 62 and the map were right and
they are what the limit actually constrains.

**Enumeration instead of sweep: it works and it is cheap to check.** 39 rows, each with a
line range; I checked all 39 references land on the sentence they name and recounted 33/6.
Then the only place left to hunt is *outside* the rows — seven uncovered sentences, all of
which fell outside the enumeration's own scope sentence. **An enumeration converts an
unprovable sweep into a finite complement.** Ask for it whenever a criterion says "sweep".

