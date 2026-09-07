---
typ: pruefung
paket: 0203-parametertoml-selbstzaehlende-fassungsangaben
pruefer: daten-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: four counting calls re-run with Grep, 47/4/51 recounted, all 51 leaf lines compared against the frozen tree in befunde/messung-0105, and both self-counting places read against the file's own history
befunde: 1
---

# 0203 — the version count is gone, and the head got a new register of the file's history

## How I measured

No shell (CLAUDE.md denies `Bash`). Every count is re-derived with the Grep tool on
`parameter.toml`; ripgrep matches `\*\*?` greedily, so the match set equals `grep -o`.

**(c) Nothing else moved.** The 27 matches of `` `[a-z_0-9]*`\* `` were listed with line
numbers and counted by hand; exactly two end in `**` (451 `` `regulierung_start` ``,
919 `` `regulierung_last` ``), the remaining 25 are pairwise distinct.

| call in the file (line) | stated | measured |
|---|---|---|
| `\*\*\?` + `grep -v '\*\*$'` + `sort -u` (229, 1184) | 25 | 25 |
| `\*` + `sort -u` (1191) | 26 | 26 |
| `\*\*\?` + `grep -v '\*\*$'` (263, 1195) | 25 | 25 |
| `\*` (1197) | 27 | 27 |

`^[a-z_0-9]* *=.*PLATZHALTER` → 47, `FEST (T51)` → 4, `^[a-z_0-9]* *=` → 51. All 51 leaf
lines, in order, key, value and mark, are character-identical to the frozen tree
`befunde/messung-0105/baum/.../parameter.toml`, which has the same 50 plus nothing —
today's file adds only `regulierung_last = 0` (996, group D, from 0150/0153). No leaf
value has moved since 0105, a fortiori not in this run. The prescribed expression is
character-identical at both places it appears.

**(a) met.** The `sort -u` justification names no version count: "Gemessen am 2026-09-06
ueber jeden Commit, der die Datei bis dahin angefasst hatte". "zwoelf Fassungen" survives
only as a retired quote with the reason ("einen Commit spaeter ueberholt"), and the
`git log --oneline -- <pfad> | wc -l` call is given for whoever needs the number, outside
the file.

**(b) met in the letter.** Line 4: "**Dieser Kopf haelt die Entstehung der Datei fest und
wird nicht fortgeschrieben.**"

## Finding 1 — the head declares itself frozen and then carries a list that ages

Lines 8–9, new in this run: "Was spaetere Pakete geaendert haben, steht da, wo sie es
geaendert haben, mit eigener Nummer und eigenem Datum: 0150 und 0153 bei der Gruppe D,
0175 und 0193 bei den Zaehlaufrufen."

That is a statement about which packages changed this file, written into the head that
the sentence above it declares not carried forward — and the file's own history
contradicts it in both readings.

**How to produce it, no git needed.** Read as an exhaustive list: line 38 of the same
comment block names `0035` — "An dieser Stelle stand bis Paket 0035 statt der Frage ein
Verweis auf `rueckstand.md`" — and lines 52–66 are a whole paragraph 0035 added. A later
package that changed the file, missing from the list 30 lines above it. Read as a rule
with examples: `0200` changed this file one commit before yours (`aufgaben/0200-...`,
`dateien:` holds `parameter.toml`, `status: fertig`, accepted 2026-09-07) at line 809,
"spiel.md, Abschnitt \"The actions\"" — that place carries neither a number nor a date.
"mit eigenem Datum" is false for 0035 (line 38), 0175 (226) and 0193 (264) too: each
names its number, none a date.

Both readings fail, so the finding does not depend on which is meant. And it is the
disease this package exists to remove: the list must be extended by every future package
touching the file, no call in the file produces it, and it was already stale on the day
it was written. Criterion (b) asks for **one sentence**; the sentence is right, the
apparatus under it is a new counter of the file's own history in the one place declared
free of them.

**What a rerun should do:** keep line 4 and the reason (lines 10–11), drop the
enumeration in 8–9 or reduce it to the rule without the roll-call —
"was spaetere Pakete geaendert haben, steht da, wo sie es geaendert haben".
