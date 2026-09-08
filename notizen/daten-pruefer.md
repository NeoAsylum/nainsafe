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

