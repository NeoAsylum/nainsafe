---
typ: pruefung
paket: 0185-standschwaeche-paketkennung-je-commit
pruefer: daten-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Both remaining conditions of the re-cast `abnahme` measured one by one -- (3) by the grep the order names, (4) at the citation, at its target in spiel.md, at the riegel's two deciding rules, and at the runner's own ctest output.
befunde: 1
---

# Both conditions met; one gap outside the order

Binding is the `abnahme` field (re-cast 2026-09-07), conditions 3 and 4. Conditions 1
and 2 were declared done and untouchable; I did not re-measure them, but line 249-262
still carries the corrected half-sentence and the line count did not move.

## Condition 3 -- the pointer to the vanished counting

Grep `zaehlen beide|Mengen` over `daten/reihen.toml`, as the order prescribes: 194, 475,
922, 1923, 1946. Line 194 now reads

    # zaehlen diese beiden Mengen nicht mehr auf; der Grund steht dort.

The other four are elsewhere and belong to other subjects: 475 and both hits at 1946 are
0170's lizenzbeleg sets ("Reihe 16 ist der Fall, der die beiden Mengen trennt"), 922 is
"Source nennt eine Menge, keine Zuordnung", 1923 is "Mengenkorb". **Below line 194 no
paragraph enumerates either set.** The promised reason stands at 232-243 ("Geschichte
mit Datum, weil hier bis zum 2026-09-07 eine Zaehlung ueber alle Commits an technik.md
stand: Sie ist ersatzlos weggefallen"). One sentence changed, nothing else.

## Condition 4 -- the two policy-rate citations

Both still sit at 406 and 556 (line count unmoved) and both read
`(spiel.md, ... Absatz The policy rate has not been a target series since 2026-09-03)`.

Resolution checked at the target and at the mechanism, not assumed:

* `specs/.../spiel.md:2447` begins `**The policy rate has not been a target series
  since 2026-09-03.**` -- a bold-lead line, the riegel's second kind of heading. After
  its normalisation (markup off, trailing period off) the cited name is
  character-identical to the heading.
* `ist_namensende` (`belegstellen_riegel.cpp:2638`) counts `)`, so the name ends before
  the closing bracket; 61 characters against `UEBERSCHRIFT_HOECHSTENS = 200` (:1563).
  The nearest file name left of the keyword inside the sentence is `spiel.md`, in the
  same bracket.
* The run itself: `befunde/uebersetzung-2026-09-07.md`, `ergebnis: ok`, ctest #17
  `belegstellen_riegel ... Passed` in the venture tree and `1/2 ... Passed` in
  `werkzeuge/belegstellen`.

**The limit of that last piece, named:** I cannot run ctest, and the report carries no
clock time. It postdates the delivery by elimination -- the vermerk records that before
this run *every* baulauf reported `ergebnis: fehler` with "2 Abschnittszitat(e) finden
ihre Ueberschrift nicht" in both trees; `spiel.md` and the riegel source are unchanged
since then, so the only edit that can turn that green is the one in `reihen.toml`. No
third, newly translated citation fell.

## The side numbers the field carries, recounted

1962 lines and 426 comment lines (`^\s*#`) -- the field says "unveraendert" for both,
and both are right. The three keywords stand 102 times, as claimed.
`datei.nachgezogen_durch` carries `0185` as its sixteenth entry, which is the one new
leaf behind "unveraendert 1238".

## Finding 1 -- `spiel.md` has no nachziehpflicht in this file

`datei.vorlagen` names six templates, and the head's "Quellen dieser Datei" (112-122)
names technik.md, daten.md and four `daten/*.md`. **Neither names `spiel.md`** -- yet
five live places do (406 twice, 556 twice, 1191), and 406 takes the 27-Sollreihen cut
from it. Only the two with a keyword are visible to the belegstellen riegel; the
paraphrases ("Abschnitt zur Partielaenge R", "spiel.md, Offene Entwurfsfragen") are
not. That is why today's translation hit this file with a red riegel and no warning,
cost 0214 its own run and blocked 0147 twice.

Not fixable under this order: a seventh template is a new leaf value, and the vermerk
forbade every leaf but two. Proposal `0220-reihentoml-spielmd-ohne-nachziehpflicht`.
