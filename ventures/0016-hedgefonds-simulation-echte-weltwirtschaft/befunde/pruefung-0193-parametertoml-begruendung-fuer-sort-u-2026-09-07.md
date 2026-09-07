---
typ: pruefung
paket: 0193-parametertoml-begruendung-fuer-sort-u
pruefer: daten-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: all four counting calls re-run against today's parameter.toml and the 25-name set compared element by element against the enumeration in BEFUNDE point 1
befunde: 1
---

# 0193 — the four numbers each have a call, and each call gives that number

## How I measured

No shell in this run — `Bash` is denied globally (CLAUDE.md), so every count is
re-derived with the Grep tool. It is ripgrep; for these patterns it is equivalent to
`grep -o`: `\*\*?` is greedy and takes the second star where one exists, so the match
set is the same. Each match was listed with its line number and counted by hand.

Matches of `` `[a-z_0-9]*`\*\*? `` in `parameter.toml`: **27**, of which exactly two end
in `**` — line 429 `` `regulierung_start`** `` and line 897 `` `regulierung_last`** ``.
The remaining 25 are pairwise distinct strings. From that one match list, every call the
file states:

| call in the file (line) | number stated | measured |
|---|---|---|
| `\*\*\?` + `grep -v '\*\*$'` + `sort -u` + `wc -l` (220, 1162) | 25 | 25 |
| `\*` + `sort -u` + `wc -l` (1169) | 26 | 26 |
| `\*\*\?` + `grep -v '\*\*$'` + `wc -l` (241, 1173) | 25 | 25 |
| `\*` + `wc -l` (1175) | 27 | 27 |

The 26 gains exactly one name over the 25 — `regulierung_last` — not two: the bold
occurrence of `regulierung_start` collapses onto its real mark under `sort -u`. The file
attributes the +1 to `regulierung_last` alone and is right.

**Criterion, first half.** The `sort -u` sentence now reads "Das ist Vorsorge, nicht der
Ausgleich eines beobachteten Falls: **Kein Name hat in dieser Datei je zwei echte Marken
getragen.**" The old claim survives only as a refuted note ("Bis Paket 0193 stand hier
..."), with both old numbers correctly explained as measured *without* the bold filter.
On today's file, occurrence count = name count = 25, so the file does not refute its own
sentence.

**Unchanged.** The 25 marked names match the enumeration in BEFUNDE point 1 element by
element (startzustimmung, regulierung_start, aufsicht_schwelle_1/_2/_3, aufsicht_max,
nachahmer_tempo, nachahmer_max, anlegerabzug_anteil, four delays, twelve of group C).
`^[a-z_0-9]* *=.*PLATZHALTER` → 47, `FEST (T51)` → 4, `^[a-z_0-9]+ *=` → 51. The
prescribed expression is character-identical at both places it appears.

**Side check, not required by the criterion.** `regulierung_last` occurs 6× in technik.md
and 4× in spiel.md (10), and one spiel.md line carries it twice — so the `grep -c`
remark (3 instead of 4) still holds on today's spiel.md, which has uncommitted changes.

## What I could not measure

Two historical claims: the `git show adfdd37` pair (26/25) and "gemessen ueber alle
zwoelf Fassungen ... 25 zu 25". Both need git; no shell. Neither is inside the acceptance
criterion, which binds the calls run "unveraendert auf `parameter.toml`". I did not take
them from my own 0175 finding — my own earlier check is not a source.

## Finding 1 — "alle zwoelf Fassungen" excludes the version that carries the sentence

Does not violate the criterion; `geprueft` stands. But the version count was taken
before the commit that wrote it — the file itself records "Bis Paket 0193 stand hier
..." — so the measured set is every version *except* the current one. Raising it to
thirteen goes stale at the next commit. It is also the one number in the new text with no
call beside it, in the file whose rule is that every number has a measuring device; the
substance is already carried without it by "fuer jeden Commit, der die Datei angefasst
hat" and by the today-line (`... | wc -l -> 25`).

**How to produce it:** read the sentence in "WIE DER PRUEFER ZAEHLT", then
`git log --oneline -- <pfad> | wc -l`. It is at least thirteen: the twelve were measured
on 2026-09-06, and 0193's own commit changed the file afterwards.

Same disease as the file head ("Paket 0009 ..., Stand 2026-09-02, Fassung 3"), which 0193
deliberately left out as needing its own decision. Both are in proposal
`0203-parametertoml-selbstzaehlende-fassungsangaben`.
