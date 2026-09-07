---
typ: pruefung
paket: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen
pruefer: test-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Driven red/green proof read from the nightly report the abnahme names as sole Beleg; it shows belegstellen_wortabstand red at the NEW head (5 deviations) on both build paths.
befunde: 1
---

# Pruefung 0166 -- zurueck: the abnahme's own Beleg says red

## The finding

The abnahme: "Der Rotnachweis wird nicht behauptet, sondern gefahren: an der
Fassung vor dieser Aenderung rot, an der neuen gruen, und der Beleg ist der
Eintrag im naechsten `befunde/uebersetzung-<datum>.md`". That entry exists
(2026-09-07, Arbeitsbaum 82fa870) and shows, on BOTH build paths (workspace
test 19/24, standalone 3/3) -- quoted on sight, the report file is overwritten
daily:

> 19/24 Test #19: belegstellen_wortabstand .........***Failed   18.02 sec
> ROT die Zeile 'keine von beiden' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
> [same for 'nur der Wortabstand', 'nur die Suche nach rechts', 'Schwelle vier', 'Schwelle fuenf'; only 'beide' matches]
> OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich 6 Beanstandung(en)
> Messstand 0166: 5 Abweichung(en).

Red-at-old holds; green-at-new does not. The first abnahme sentence -- the
table "nennen Zahlen, die am Auslieferungsstand gemessen sind" -- is refuted by
the same measurement: the middle column (aufgeloest) is wrong in 5 of 6 rows.

## Mechanism (evidence, not blame)

At 82fa870 the riegel itself is red: 40/36/53 (four citations found but
unresolved; earlier today the corpus stood 40/40/47, see pruefung-0147's
quotes). Disabling both loosenings moves Zitate -1 but aufgeloest +-0 -- so the
Paket-0034 Stelle the table describes is itself among today's unresolved. The
head's "-1 aufgeloest" holds only while that Stelle resolves, i.e. only while
the riegel is green on the corpus. The base moved AFTER the build commit
6c34479: technik.md sections were translated (798f425, 37cc63d; §5-§8 in
`ops/uebersetzt.txt`). Verified concretely: `technik.md:409` now reads "Two
address pairs carry the same value...", so the riegel's own head citation
(belegstellen_riegel.cpp:39, Absatz "Zwei Adresspaare tragen denselben Wert...")
no longer resolves. Same failure class 0200 repaired for the previous wave;
tests 17 (riegel) and 18 (messung-0147, 2 Abweichungen) are red from the same
churn. Repair proposed as 0222 (vorschlag).

## What I verified and found sound (the re-run is cheap)

- Mounting per abnahme: own `add_test belegstellen_wortabstand`, no
  `if(EXISTS)` (FATAL_ERROR, CMakeLists.txt:134), TIMEOUT 240 < 900 -- proven
  live on both build paths.
- Exit codes 0/1/2 separated (messen.py:685-698); the 1-path proven by the red
  run, the 2-path guarded by the needle pre-check ("alle Nadeln treffen genau
  einmal" at 82fa870 per report).
- The script reads the table from the delivered comment (`lies_tabelle`), not
  from constants; its selbstprobe proves it complains at a wrong number and a
  missing row -- it can say no.
- Teil 1: vorher/nachher same three numbers (40, 36, 53), one call, one tree --
  that abnahme condition holds.
- Teil 4 re-derives the Absatz's Aussage from measured numbers: all four
  sentences OK at 82fa870. The claim survives; only the table's middle column
  is stale.
- Zahlenzeile read from stdout (riegel prints it at :4149) -- absence gives
  Messfehler/2, not silent green.
- Runtime 18.02 s / 17.50 s, cap 240 s -- proportionate.

The apparatus did exactly what it was built for: it got loud the day the base
moved. What fails the abnahme is the head's numbers at the delivery state, not
the measuring rig.

## Path for the PM

0166 cannot go green while the riegel is red on the corpus; the four stale
citations are outside 0166's dateien. Sequence 0222 (or equivalent corpus
repair) before a redo; if the report after that repair still shows
wortabstand red, only then does the table need re-measuring by the builder.
