---
typ: messung
paket: 0132-riegelmeldung-nennt-gesammelte-eintraege
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-06
rolle: kernbauer
---

# Die Meldung des Schlussriegels nennt, was sie eingesammelt hat

Geaendert ist eine Datei -- `werkzeugkette.cmake` --, und in ihr allein die Funktion
`fabrik_schlussriegel`: ein dritter Zaehler `eingesammelt` und die drei Meldungen, die
ihn nennen. Die gruene Statusmeldung nennt ihn, und beide Abbrueche nennen ihn auch, denn
ein Abbruch erreicht die Statusmeldung nie.

Gezaehlt wird die Laenge der Liste, die `fabrik_riegel_sammeln` je Ziel fuellt -- also
ausserhalb des Makros. Im Makro selbst waere der Zaehler wertlos: Eine stumpf gemachte
Fassung naehme ihren eigenen Zaehler mit, und die Zahl bezeugte dann nur noch sich
selbst. Der Wert ist heute im Arbeitsbereich 388 bei 22 uebersetzenden Zielen; das sind
17 Schalter des Warnsatzes je Ziel und 14 Sanitizer-Eintraege an den sieben
`_geprueft`-Zielen. Die Zahl waechst mit dem Baum und gehoert deshalb ausgeschrieben in
keine `abnahme` -- dieselbe Regel, die fuer die Zahl der Ziele gilt.

## Abnahme 1 -- ein stumpfer Riegel faellt an einer Zahl auf

Skript `zaehler.py`, Lauf in `lauf.txt`, gefahren am 2026-09-06 mit CMake 4.2.3. Zwei
Wegwerf-Baeume mit je einem Ziel und einer Quelldatei ohne eigene Schalter; welche
Fassung der Kette ein Lauf einbindet, entscheidet allein `-DFABRIK_KETTE=`. A und B
fahren damit denselben Quellbaum, Byte fuer Byte. Stumpf gemacht ist die Bedingung in
`fabrik_riegel_sammeln` -- `if(NOT "${${listenname}}" STREQUAL "")` wird `if(FALSE)` --,
und der Suchtext dazu kommt in der Kette nachweislich genau einmal vor.

| Lauf | Baum | Fassung | Code | Zaehler |
|---|---|---|---|---|
| A | ohne `-w` | unveraendert | 0 | **17** |
| B | ohne `-w` | stumpf | 0 | **0** |
| C | mit `-w` am Ziel | unveraendert | 1 | -- (Abbruch) |
| D | mit `-w` am Ziel | stumpf | 0 | **0** |

A und B melden beide Code 0 und beide `alle mit Warnsatz und ohne Pauschalabschalter`;
die Riegelzeile ohne den neuen Satzteil ist zeichengleich dieselbe. Was sie unterscheidet,
ist allein die neue Zahl: 17 gegen 0.

C und D stehen dabei, weil "stumpf" sonst eine Behauptung ueber die Mutation waere und
keine Messung. C zeigt, dass die unveraenderte Fassung an diesem `-w` wirklich abbricht;
D, dass die mutierte dasselbe `-w` gruen durchlaesst. D ist der eigentliche Fall des
Pakets: Seine Meldung ist ausser dem Zaehler zeichengleich die von A -- ein Baum, in dem
`-w` auf der Uebersetzerzeile steht, und eine Meldung, die aussieht wie die eines sauberen.
Die 0 ist das Einzige, was ihn noch verraet.

## Abnahme 2 -- kein Urteil aendert sich

### Die 22 Wegwerf-Baeume

`befunde/pruefung-0066/nachbau.py`, zweimal gefahren: einmal gegen die Kette dieses
Arbeitsbaums (`nachbau-lauf.txt`), einmal gegen die des Standes `ca60f8a`, also die
Fassung vor dieser Aenderung (`nachbau-lauf-vorher.txt`). Beide Laeufe: `0 Abweichung(en)
vom Soll`, Rueckgabewert 0, Positivkontrolle rot gebaut (Code 2, eine Diagnose).

Die beiden Ausgaben sind **zeichengleich**, nachdem allein der Ablagepfad vereinheitlicht
ist -- 0 Unterschiede ueber alle 22 Baeume. Damit sind die Zeilen `gefunden in` und
`es fehlen` im Wortlaut unveraendert, und zwar nicht behauptet, sondern verglichen.

### Die drei Bauwege in beiden Profilen

Gemessen wurde **nicht** im Arbeitsbaum, sondern an zwei ausgepackten Kopien des Standes
`ca60f8a`, die sich durch nichts als diese eine Datei unterscheiden. Der Grund steht
unten unter "Was diese Messung nicht ist". Ablage `bauwege0076-rein2-*`, gefahren am
2026-09-06.

Alle sechs Wege melden Konfigurations-, Bau- und `ctest`-Code 0, und jede Zielzahl ist
dieselbe wie am Stand davor. `0 Abweichung(en)`, Rueckgabewert 0.

| Profil | Bauweg | Ziele (davor) | Zaehler | bau | ctest |
|---|---|---|---|---|---|
| ON | Arbeitsbereich | 22 (22) | 388 | 0 | 0 (18/18) |
| ON | `kern` allein | 14 (14) | 242 | 0 | 0 (12/12) |
| ON | `pruefstand` allein | 5 (5) | 89 | 0 | 0 (3/3) |
| OFF | Arbeitsbereich | 20 (20) | 340 | 0 | 0 (18/18) |
| OFF | `kern` allein | 13 (13) | 221 | 0 | 0 (12/12) |
| OFF | `pruefstand` allein | 4 (4) | 68 | 0 | 0 (3/3) |

Die Zaehlerspalte ist ein Messwert vom 2026-09-06 am Stand `ca60f8a` und keine Vorgabe.
Im Profil OFF ist sie genau das 17-fache der Zielzahl; die Differenz im Profil ON sind
die zwei Sanitizer-Eintraege an den Zielen, die es nur dort gibt.

## Was diese Messung nicht ist

**Der Arbeitsbaum war waehrend dieses Laufs rot, und zwar ausserhalb dieses Pakets.** Ein
gleichzeitig laufendes Paket schrieb an `kern/include/kern/werte.hpp`; `kern/src/werte.cpp`
uebersetzte in diesem Zustand nicht (`too many braces around scalar initializer`, dreimal
`non-constant condition for static assert`). Der erste Lauf der drei Bauwege im
Arbeitsbaum meldete deshalb 8 Abweichungen, alle aus Bau und `ctest` der Kernquellen --
und alle sechs Zielzahlen trotzdem gleich dem Stand davor. Er liegt als
`bauwege-lauf.txt` daneben und ist als das zu lesen, was er ist: eine Messung an
einem Baum, der aus fremdem Grund rot war. Es zaehlt der Lauf an den ausgepackten
Kopien, in dem sich vorher und nachher durch nichts als diese eine Datei
unterscheiden.

**Der Zaehler misst nicht, ob der Riegel richtig einsammelt, sondern ob er einsammelt.**
Wer eine der fuenf Eigenschaften stumm stellte, druecke die Zahl, ohne sie auf 0 zu
bringen. Dagegen hilft dieselbe Regel wie bei der Zahl der Ziele: gelesen wird sie im
Vergleich zum vorhergehenden Stand desselben Baums und desselben Profils, nicht gegen
einen Sollwert.

**Die Nullmeldung ist unveraendert.** Bricht der Riegel ab, weil er kein einziges
uebersetzendes Ziel gesehen hat, nennt er den Zaehler nicht -- dort ist die Frage schon
beantwortet, und ein Baum aus lauter Schnittstellenzielen kann Eintraege tragen, ohne
etwas zu uebersetzen. Eine Zahl an dieser Stelle laedt zu genau dieser Verwechslung ein.
