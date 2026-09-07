---
typ: pruefung
paket: 0220-reihentoml-spielmd-ohne-nachziehpflicht
pruefer: daten-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Every count of the Vorlagentabelle in the comment recounted by me against the table (five live places, three dated as history); the spielentwurf stand checked against spiel.md:95 and :21; scope held by +16 lines that are +16 comment lines, all sixteen patterns and the three Zahlwortriegel anchors re-measured myself.
befunde: 0
---

# What I counted, and against what

**The table.** `[datei.vorlagen]` 439-446 holds seven keys: reihenliste, preisbasis,
spielentwurf, deckung, lizenz_wdi, lizenz_reihen, einheiten. All seven name a Stand.

**Every count of it in the comment 156-438, not only the three the acceptance names:**

| line | says | counted |
|---|---|---|
| 156 | "Stand der **sieben** Vorlagen" | 7 keys |
| 161 | "fuehrt **sieben** Schluessel", all seven listed | 7 |
| 221-227 | "**fuenf** der **sechs** anderen … ein Datum aus einem Frontmatter"; "Der **sechste**, spielentwurf, nennt keines" | preisbasis → technik.md:5 (`fassung:` names 2026-09-04, Paket 0026); deckung/lizenz_wdi/lizenz_reihen/einheiten → `datum:`/`ueberarbeitet:` of their four Befunddateien = 5. spiel.md:1-17 carries no Fassung, its own stands in the body = the sixth. |
| 290 | "alle **sieben** einen Stand und **keiner** nennt keinen" | 7 of 7 |
| 394 | "eine andere Form als die **sechs** anderen" | 7 − 1 |

Dated as history and correct for its stand: 163-165 (fuenf/sechs), 226-227, 284-287,
376 ("der fuenf Vorlagen, die vor Paket 0099 in dieser Tabelle standen").

**The stand.** 442 names the date and the package and disclaims the rest of the file:
"Nachtragszeile unter dem Titel vom 2026-09-07 (Paket 0198-…), gegen die diese Datei
gelesen ist; ob eine juengere darunter steht, sagt dieser Eintrag nicht." No superlative
anywhere. `spiel.md:95` carries that Nachtragszeile and names 0198; it is the only one
dated 2026-09-07. `spiel.md:21` reads "*Fünfte Fassung*". Both are in the document, as
the entry claims. `.git/logs/HEAD:896/898` still gives ab2cd7f 1788789606 against
d52d3bb 1788789617.

# Scope, and what I cannot show

`^` = **2029** lines, `^#` = **491** comment lines. Before: 2013 and 475. **+16 = +16**,
so no line outside a comment was added or removed; `toml_geprueft` records the same two
pairs and matches my measurement. All **sixteen** patterns counted by me, not read off:
6; 29, 54 and 27; 114; 19, 19, 19, 152, 20, 28; 21 and 28; 20 and 2 — every one equals
the recorded value. `["]{3}` = 1, as schnitt_2 says.

Leaves the acceptance forbids: `^faktor =` 21 values, `art = "ungemessen"` exactly once
(884, Reihe 3), `basisjahr = 2015` exactly once (1689, Reihe 14), the 19 `sollreihen` on
Reihe level sum to 27 with fourteen zeros. The Zahlwortriegel (`zahlwort_reihen`,
`befunde/messung-0099/zahlwoerter.py`) has three anchors that must each occur exactly
once in a whole-line comment: "Stand der 7 Vorlagen" (156, the only "Stand der …
Vorlagen" in a comment line), "genannt wird er in 8 Blattwerten" (321), "zerfallen ohne
Rest in 2 plus 1 plus 5" (323). The marke sits in exactly 8 non-comment lines — 446,
653, 877, 886, 1668, 1680, 1824, 2013. Green.

**The boundary:** no role has a shell and I cannot read a blob, so a leaf value changed
*in place* would leave none of these counts moving. What I show is that no leaf line
exists or is missing, and that every count derived from leaf values is unchanged.
`datei.stand` stays 2026-09-06, as the acceptance requires and `toml_geprueft` says.

# Checked, not a finding, and it belongs to 0222

`reihen.toml:1870` (Reihe 17, `offen`) cites "die spiel.md unter **'Die Grenze des
Orakels'** aufzaehlt". That place no longer exists in `spiel.md`: the bold lead-in was
"**Und die Grenze des Orakels, ausdrücklich.**" (still readable in
`befunde/messung-0105/baum_tot/…/spiel.md:2147`) and today reads "**And the limit of the
oracle, explicitly.**" (`spiel.md:2830`). The only surviving German mention,
`spiel.md:1606`, points at the place from inside the same file. `technik.md:1802` carries
the same dead reference.

Not a return: 0220 moved no leaf value there, the line is older than the package, and
the vermerk names this class expressly. It is the weakness the new comment itself
records at 402-406 — the translation changed the text without writing a Nachtragszeile,
so the new nachziehpflicht does not fire on it. No new package from me: `0222-zitate-auf-
uebersetzte-technik-abschnitte-nachziehen` (`vorschlag`) already claims
`daten/reihen.toml`. Its acceptance covers "every citation of the checked form" — this
one is a paraphrase inside a leaf value and may fall outside it. That is the sentence
its builder needs.
