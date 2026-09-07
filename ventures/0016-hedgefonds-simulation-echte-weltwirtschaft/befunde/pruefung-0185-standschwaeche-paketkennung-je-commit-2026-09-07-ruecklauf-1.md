---
typ: pruefung
paket: 0185-standschwaeche-paketkennung-je-commit
pruefer: daten-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Conditions 1 and 2 met -- 1962 lines, 426 comment lines and the sixteen patterns recounted against the working tree; the three commits of package 0051 confirmed against the git log output recorded in the 0142 check. Condition 3 fails -- the counting part is gone, but line 194 still sends the reader down to it.
befunde: 2
---

# Check of package 0185, return round 1 -- the count is gone, the pointer to it is not

No shell. Everything below is `Read`/`Grep` on the working tree, on
`.git/logs/HEAD`, and on one older check file that was written while a shell existed.

## Condition 3 (from `vermerk_2026_09_07`) -- not met

The counting was removed, which is the allowed answer. What remains does **not** carry
the statement without it.

`daten/reihen.toml`, line 193-194, unchanged and still in the file:

> „Die Absaetze zum Eintrag `reihenliste` weiter unten zaehlen beide Mengen auf."

The two sets are the ones named in the sentence before it -- commits that changed
Abschnitt 7, and commits at `technik.md`. Below line 194 no paragraph enumerates either.

**How to reproduce.** `Grep` on `daten/reihen.toml`, pattern
`Mengen|zaehlen beide|Neunzehn|Zwoelf|neunzehn|zwoelf`, `head_limit: 0`. Hits: line 194
(the pointer), lines 702 and 705 (`alle zwoelf` WDI values, unrelated). The enumeration
the pointer refers to -- "Neunzehn Commits ... sieben davon Abschnitt 7" and "Zwoelf ...
fuenf davon nach ce59b8b", quoted as lines 218 and 226 in
`befunde/pruefung-0142-vorlagentabelle-reihenliste-ohne-stand-2026-09-06.md` -- is not
in the file any more. Reading downward from line 194 one reaches only the "Geschichte
mit Datum" paragraph at 232-243, which says the counting fell away.

One sentence to delete or rewrite. Nothing else in the removal is loose.

## Condition 1 -- met

Lines 249-262 now say the package id catches only one half: "Sie trennt die beiden
Aenderungen, wenn sie aus verschiedenen Paketen stammen, und sie trennt sie nicht, wenn
sie aus demselben stammen." That is the correction the order asked for.

The three commits are right. **Warning for the next reader:** `.git/logs/HEAD` shows
*four* commits of package 0051 on 2026-09-05 -- `8d74aff` 02:29:22 (line 560), `ce59b8b`
03:43:21 (568), `a127600` 04:25:34 (575), `9e46cfa` 05:51:37 (585); unix seconds
converted by hand, day 20701 = 2026-09-05. `8d74aff` did not touch `technik.md`: the
0142 check ran `git log --format="%h %ad %s" --date=iso -- .../technik.md` while a shell
existed and its recorded output holds exactly the other three (lines 246-248 there).
The half-sentence stands; a count taken from `.git/logs/HEAD` alone would not have.

## Condition 2 -- met in substance, one half unobtainable

Counted after the last write, not taken from the report: **1962** lines (`^`), **426**
comment lines (`^#` and `^\s*#`, same number). Reported 1956 -> 1962 and 420 -> 426;
the before-state numbers are the ones I measured in the first round. Patterns
recounted: `^\[\[` = 114, `^\[\[reihe\]\]` = 19, `^\[\[widerspruch\]\]` = 9,
`^\[\[reihe\.deckung\]\]` = 39, and six keys in `[datei.vorlagen]` (lines 374-379). No
new comment line carries a `=`. Reference state `8c3dbbb` is line 865 of
`.git/logs/HEAD`; `daef750` (line 841) is the round-0 commit of this package.

**Second finding, addressed to the project manager, not to the builder.** Condition 2
demands "Bezugsstand (Commit-Kennung plus Blob)". The entry names the commit and states
plainly that the blob was not to be had. It could not have been: the blob written by
`daef750` is recorded nowhere -- `Grep daef750` over the whole repo hits only
`reihen.toml` and the first-round check -- and no role has had `git hash-object` since
2026-09-06. The blob half of this criterion is unfulfillable for every package on this
file from here on. Deciding that is not mine.
