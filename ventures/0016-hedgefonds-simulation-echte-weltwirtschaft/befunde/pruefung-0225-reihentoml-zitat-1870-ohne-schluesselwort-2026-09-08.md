---
typ: pruefung
paket: 0225-reihentoml-zitat-1870-ohne-schluesselwort
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "three named ctest entries quoted from both build paths of uebersetzung-2026-09-08.md; keyword, Anfuehrung and wortgleich resolution read off the riegel's delta 36/36/57 -> 37/37/57 and the four code sites it runs through"
befunde: 0
---

# The line resolves, and the three named probes are green in both paths

## 1. The condition the acceptance puts on me

`befunde/uebersetzung-2026-09-08.md`, path **werkzeuge/belegstellen** (`:328-333`):

```
1/5 Test #1: belegstellen_riegel ..............   Passed    1.03 sec
2/5 Test #2: belegstellen_messung .............   Passed   31.15 sec
3/5 Test #3: belegstellen_wortabstand .........   Passed   17.43 sec
```

Path **whole tree** (26 entries): the per-test lines are **not in the report**, and that is
mechanical — `agents/baulauf.py:206` keeps `text[-6000:]`, so entries 1–21 are cut off in
front (`:89` starts mid-sentence). What it carries verbatim (`:170-176`):

```
92% tests passed, 2 tests failed out of 26
The following tests FAILED:
	 21 - belegstellen_kopfzahlen (Failed)
	 26 - zahlwort_messung (Failed)
```

All three are outside that list, hence green here too. `zahlwort_messung` is red on
`kern/include/kern/werte.hpp` line numbers (`:135`) and belongs to `d17b26d`.

**Green in both paths — abnahmefaehig by the acceptance's own wording.**

## 2. The Fundstelle resolves — two independent checks

`reihen.toml:1870` today: `... aufgezaehlt in spiel.md, Absatz 'And the limit of the
oracle, explicitly'. ...` — file, comma, keyword, Anfuehrung at distance zero.

*Code.* `Absa\164z` is entry 4 of `SCHLUESSEL` (`belegstellen_riegel.cpp:1544-1545`).
`{"'", "'", false}` is entry 5 of `KLAMMERN` (`:1605`): `kuendigt_an == false`, so the
straight single quote is an Anfuehrung **only** with a keyword directly before it — that is
what makes the keyword load-bearing and confirms the old line was invisible. `spiel.md:2851`
reads `**And the limit of the oracle, explicitly.** Without a target series are: ...`;
`ueberschrift_aus_zeile` (`:1727-1732`) takes the bold lead-in, `normiere` (`:1701-1705`)
drops the trailing `.` on both sides — wortgleich.

*Measurement, the stronger of the two.* 2026-09-07 report `:286/:296`: `36 Zitate, 36
aufgeloest, 57 uebergangen`. 2026-09-08 `:342-343`: `37 Zitate, 37 aufgeloest, 57
uebergangen`. **+1 citation, +1 resolved, ±0 passed over, none unresolved.** A site with
keyword and Anfuehrung is either a citation or passed over; the passed-over count did not
move, so this line is the new citation and it resolves.

## 3. Nothing else moved

- 2029 lines, 491 comment lines (`Grep "^"`, `Grep "^\s*#"`), measured by me after the run
  — identical to what I recorded for 0220 on 2026-09-07 and to the vermerk.
- The delta in 2. is a **whole-tree** statement: no other citation changed status.
- The excluded sites still carry their old form: `:473` `spiel.md, Abschnitt zur
  Partielaenge R`, `:623` and `:1258` `spiel.md, Offene Entwurfsfragen`.
- `zahlwort_reihen` and `belegstellen_sammelordnung` green in both paths — the head
  comment's word-sequence anchors and the collection order are untouched.
- `specs/` is outside the builder's `Edit` scope, so that condition is enforced, not
  promised.
- Vermerk carries old line, new line and the Grep; I reran it and got the same two hits,
  `:1622` and `:2851`.

## 4. Checked, not a finding

The acceptance renders the head form as `<datei>, <Schluesselwort> "<Name>"` and cites
`belegstellen_riegel.cpp:346`. That line describes the form **without** Anfuehrung, four
times, from package 0047. The builder used the quoted form, the stricter one: with
Anfuehrung `beurteile_zitat` demands wortgleich instead of reading to the next punctuation
mark. He met the acceptance as written.

`reihen.toml:409-410` calls the remaining `spiel.md` mentions "Umschreibungen". Line 1870
is no longer among "the remaining", so it stays true — and it was already imprecise before
this run (`:473`, `:623` carry keywords).

## 5. Report to the project manager — not a Ruecklauf

`belegstellen_kopfzahlen` is red in both paths. It was **already red on 2026-09-07** (11
unmet expectations), so no green probe was turned red — but this package changed *which*
numbers are wrong, one day after 0189 entered them. Package proposed:
`aufgaben/0232-riegelkopfzahlen-nach-0225-nachziehen.md`.
