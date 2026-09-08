---
typ: pruefung
paket: 0233-riegelkopfzahlen-nach-0148-0229-nachziehen
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "Each transcribed number read at its site and matched against two independent records of the 2f2f79f measurement; proof clause met by the green belegstellen_kopfzahlen entry in the working-tree report, both paths."
befunde: 0
---

# Pruefung 0233 — geprueft, 0 findings

## The proof clause has already executed

The abnahme names its own proof: "the next report: the same entry with return code 0."
The working-tree `befunde/uebersetzung-2026-09-08.md` now holds a post-commit run
(`ergebnis: ok`, 26/26 tests): `belegstellen_kopfzahlen` **Passed** 15.95 s root
(`:123-124`) and 16.04 s standalone (`:290-291`). rc 0 has exactly one path in
`messung-0115/messen.py:771-775` — empty `fehler` after teil_a, teil_b1-b3, Gegenprobe,
staende and source-restore checks. A foreign HEAD is a printed Hinweis, not a melde
(`messen.py:749-762`), so green at a later HEAD is a valid pass, exactly as the vermerk
priced in.

## Every number, at its site, against the measurement

`belegstellen_riegel.cpp`: `:563` 52 statt 41 Zitate / weiterhin nur 41 aufgeloest / 66
statt 53 Fundstellen; `:562-565` elf zu Unrecht, zehn eigene, zwei Kopfkommentar / eine
SATZFAELLE / sieben ZITATFAELLE (same breakdown in words at `:1573-1578` above
`Klammer::kuendigt_an`); `:603-605` Angabe 2 = 41/41/53, Summe 94; `:1016` "Der siebte
Herkunftshinweis". Date 2026-09-08 and Stand `2f2f79f` at all three `gegen den Stand`
sites (`:560`, `:602`, `:1586`); `messen.py:755-758` requires that set to equal
`{BEZUGSSTAND}`, and the run is green. `BEZUGSSTAND = "2f2f79f"` (`messen.py:108`);
`VORFASSUNGSSTAND` 4d14905 → `"dbcd637"` (`:99`), the exact parent of build commit
dfc5251 — teil_a therefore measures this Berichtigung, not later foreign code.

## The cited report lines are gone — the values hold anyway

The runner replaced the dated report's content; the red entry (`:118-157`) the package
body cites is no longer readable (second sighting after 0232). The values are
corroborated twice, independently: (1) `befunde/pruefung-0232-riegelkopfzahlen-nach-
0225-nachziehen-2026-09-08.md:45` records the corpus move 37/37/57 → 41/41/53, sum
still 94, `:29` the breakdown 11/10/{Kopf 2, SATZFAELLE 1, ZITATFAELLE 7}, `:28` the
ordinal — written before this build; (2) the green run re-measured the corpus against
the comment. "Copied, not carried forward" is attested by execution, not by the rotted
line numbers.

## Can it go red? It did, and its Gegenprobe still rips

The same entry was red on exactly these numbers in the run this package cites (7
Erwartungen at HEAD 2f2f79f) — that red is why 0233 exists. Red → green across dfc5251
alone. In addition, every run's Gegenprobe turns one Angabe by one and demands each of
the three checks report (`messen.py:713-718`, 0 Meldungen → melde) — a blunted check
makes the run red by itself.

## The extra condition from the vermerk

All four `daten/reihen.toml` citation sites resolve at the current tree exactly where
the body says: `:440` Abschnitt 7, `:441` Vorgabe T53 (in Abschnitt 2), `:655` Vorgabe
T53 (Abschnitt 2), `:1667` Abschnitt 17 — 0234 (1b6cab7) did not move them.

## Looked for, not found

Weakened assertions in `messen.py` (main sequence `:721-775` intact, matches the
apparatus reviewed in pruefung 0232 the same day; only the two stand constants moved,
each with an accurate fresh comment); a VORFASSUNGSSTAND pin that would blunt teil_a
(exact parent — stronger than the ancestor pins accepted in 0189/0232); carried-forward
numbers (the predecessor values 48/37/37/70/57 appear nowhere). For the PM: the vermerk
accepted a likely re-red within days from the `technik.md` chain; tonight's 0177
(e6900ed) has landed and the entry is still green — the price is not yet due.
