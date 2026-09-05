---
typ: messung
paket: 0104-zielzahlen-je-profil-statt-tripel
rolle: kernbauer
datum: 2026-09-05
bezugsstand: 8a2c381
---

# Bedingung 2 von Paket 0104 -- die sechs Zahlen, nachgemessen

**Bezugsstand.** `8a2c381` (`projektmanager: 0016-... (14 Dateien)`).
`werkzeugkette.cmake` war zu Beginn unveraendert gegenueber diesem Commit
(`git status --short` leer) und wurde vor der ersten Aenderung nach
`$TMPDIR/kette-vorher.cmake` kopiert; jede Vorher-Zahl unten ist gegen diese Kopie
gemessen und nicht gegen `HEAD`, weil ein Fremdlauf `HEAD` mitten im Lauf verschieben
kann.

**Nicht abgeschrieben.** Das Paket nennt fuer den 2026-09-05 die Zahlen 18 / 12 / 5 und
16 / 11 / 4. Gemessen sind an meinem Bezugsstand **19 / 12 / 5** und **17 / 11 / 4** --
der Arbeitsbereich hat seither ein uebersetzendes Ziel dazubekommen
(`werkzeuge/mutation` mit `mutationstreiber`). Das ist keine Abweichung, sondern der
Sachverhalt, um dessentwillen das Paket existiert.

## Die sechs Zahlen

Je Bauweg ein `cmake -S` in einen Wegwerf-Baum unter `$TMPDIR`, mit den Schaltern des
Runners (`-DCMAKE_BUILD_TYPE=RelWithDebInfo`, `-DCMAKE_CXX_FLAGS=-fwrapv
-fno-fast-math`). Gelesen ist die Zahl aus der Meldung des Warnsatz-Schlussriegels.

| Bauweg | `FABRIK_SANITIZER=ON` | `=OFF` |
|---|---|---|
| Arbeitsbereich | 19 | 17 |
| `kern` allein | 12 | 11 |
| `pruefstand` allein | 5 | 4 |

Alle sechs Konfigurationen Code 0, **vorher wie nachher dieselbe Zahl**. Die Schalter
des Runners aendern die Zahl nicht: ein erster Lauf ohne sie ergab dieselben sechs Werte.

**Zweite, unabhaengige Messung.** `befunde/messung-0076/bauwege.py` meldet dieselben
sechs Zahlen und dazu Bau und `ctest` je Baum gruen: Arbeitsbereich 14/14 Tests, `kern`
10/10, `pruefstand` 3/3, in beiden Profilen. Seine Schlusszeile lautet
`2 Abweichung(en)`, und zwar gegen seine **eigene** fest eingetragene Sollspalte
(18 / 16 im Arbeitsbereich). Das Skript gehoert nicht zu diesem Paket und ist nicht
angefasst; seine zwei Abweichungen sind wortwoertlich der Fehler, den die Entscheidung
oben kuenftig ausschliesst -- eine ausgeschriebene Zahl, die mit dem naechsten neuen
Ziel von selbst falsch wird.

## Kein Satz im Kommentar widerspricht einer Messung

Der Kommentar steht jetzt bei `message(STATUS ...)` in `werkzeugkette.cmake`. Was er
behauptet, und woran es haengt:

| Behauptung im Kommentar | Nachweis |
|---|---|
| ON: 19 / 12 / 5, OFF: 17 / 11 / 4, am 2026-09-05 an `8a2c381` | die sechs Konfigurationen oben, zweimal unabhaengig |
| `kern_geprueft` und `pruefstand_geprueft` gibt es nur unter `ON` | Zielliste des Arbeitsbereichs: 26 Ziele unter `ON`, 24 unter `OFF`; genau diese beiden fehlen unter `OFF` |
| Differenz Arbeitsbereich zur Summe der Alleinbauten ist 2, getragen von `werkzeuge/belegstellen` und `werkzeuge/mutation` | 19 - (12+5) = 2 und 17 - (11+4) = 2; von den neun Namen in `FABRIK_MITGLIEDER` tragen nur `kern`, `pruefstand`, `werkzeuge/belegstellen` und `werkzeuge/mutation` eine `CMakeLists.txt`, die uebrigen fuenf meldet die Konfiguration als uebersprungen |
| am 2026-09-04 war die Differenz noch 1 | so stand es im ersetzten Kommentar; `werkzeuge/mutation` ist seither dazugekommen |

Die Zahlen 15 und 3 im ersten Absatz sind als erfundenes Beispiel gekennzeichnet und
keine Messung -- sie tragen deshalb kein Profil und kein Datum.

## Die Aenderung ist ausschliesslich Kommentar

47 geaenderte Zeilen, **keine davon ausserhalb eines `#`**. Gegenprobe ueber die
gefrorene Kopie: die 325 Zeilen der Datei, die weder leer noch Kommentar sind, sind
vorher und nachher byteweise dieselben. Ein Bau kann sich dadurch nicht aendern -- und
tut es auch nicht: Arbeitsbereich `--build` und `ctest` in beiden Profilen Code 0,
14 von 14 Tests, darunter `belegstellen_riegel`, der den neuen Kommentartext mitliest.

## Kontrolle am Ende des Laufs

Waehrend dieses Laufs haben Fremdlaeufe im selben Baum gearbeitet -- `git status` zeigt
zum Schluss unter anderem `pruefstand/CMakeLists.txt`,
`werkzeuge/belegstellen/belegstellen_riegel.cpp` und `befunde/pruefung-0066/nachbau.py`
als geaendert. Genau dagegen war die gefrorene Kopie da.

Eine Kontrollmessung zum Schluss ergibt trotzdem dieselben sechs Zahlen: **19 / 12 / 5**
unter `ON`, **17 / 11 / 4** unter `OFF`. Der Kommentartext steht unveraendert im Baum,
die ersetzte Zeile `Am 2026-09-04 waren es 16 im Arbeitsbereich ...` kommt in der Datei
nicht mehr vor.

Und falls diese Zahlen morgen andere sind: Der Kommentar behauptet sie ausdruecklich
**fuer den Stand `8a2c381` am 2026-09-05** und fuer kein anderes. Eine spaetere Messung
widerlegt ihn dadurch nicht -- das ist der ganze Unterschied zwischen einer Messung und
einem Sollwert, und der Grund fuer dieses Paket.
