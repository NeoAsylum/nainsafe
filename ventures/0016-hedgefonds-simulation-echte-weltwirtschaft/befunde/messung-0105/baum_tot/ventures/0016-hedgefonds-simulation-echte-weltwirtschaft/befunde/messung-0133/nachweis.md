---
typ: messung
paket: 0133-schlussriegel-nachbau-laeuft-nirgends
rolle: testentwickler
datum: 2026-09-05
bezugsstand: 8a2c381
---

# Nachweis zu Paket 0133 -- der Schlussriegel bekommt einen Waechter

Gemessen am 2026-09-05, alle Baeume unter `$TMPDIR` (`/tmp/claude-1000`), also
ausserhalb des Repos -- erste Stufe der Staffelung aus der Abnahme. Werkzeuge:
CMake 4.2.3, g++ 15.2.0, Python 3.

## Was gebaut wurde

Zwei Dateien, beide aus der `dateien`-Liste des Pakets:

1. `pruefstand/CMakeLists.txt` -- `befunde/pruefung-0066/nachbau.py` haengt als Probe
   `schlussriegel_nachbau` in `ctest` und laeuft damit bei jeder Abnahme mit. Dazu zwei
   Riegel gegen das stille Verschwinden der Bahn selbst: Fehlt das Skript, bricht die
   Konfiguration ab (`FATAL_ERROR`); fehlt ein Python-Deuter, wird `python3` aus dem
   Suchpfad eingetragen und die Probe rot, statt aus der Liste zu fallen.
2. `befunde/pruefung-0066/nachbau.py` -- zwei Aenderungen, keine an den 22 Faellen:
   `NACHBAU_ABLAGE` verlegt die Wegwerf-Baeume in den Baubaum (der Vorgabepfad haengt
   allein am Stand, nicht am Baum -- zwei Baeume nacheinander liefen einander in die
   Ablage), und die Positivkontrolle `p_positiv` zaehlt in den Rueckgabewert. Der Aufruf
   von Hand ist unveraendert; Pfad, Ausgabeformat und Rueckgabewert am heutigen Baum
   sind dieselben wie vorher.

Der Nachbau ist **nicht** umgezogen (Vermerk 3 des Pakets). `bauwege.py` ist nicht
angefasst (das ist 0135), `werkzeugkette.cmake` nicht, die `CMakeLists.txt` des
Vorhabens nicht, der Riegel selbst nicht.

## Bedingung 1 -- ein stumpfer Schlussriegel wird ohne Zutun rot

Drei Wegwerf-Baeume unter `$TMPDIR/nachweis0133/`, jeder aus
`werkzeugkette.cmake` + `pruefstand/` + `befunde/pruefung-0066/nachbau.py` des
Arbeitsbaums. Keine dieser Fassungen ist eingecheckt -- sie sind die Messung.

### 1a. Der unveraenderte Baum -- die Gegenprobe

Ohne sie belegt das Rot unten nur, dass irgendetwas rot ist.

```
$ cmake -S $TMPDIR/nachweis0133/unveraendert/pruefstand \
        -B $TMPDIR/nachweis0133/unveraendert/bau -DFABRIK_SANITIZER=ON
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne
   Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/claude-1000/nachweis0133/unveraendert/bau

$ cmake --build $TMPDIR/nachweis0133/unveraendert/bau -j 4
[100%] Built target vorrat_verfahren_probe

$ ctest --test-dir $TMPDIR/nachweis0133/unveraendert/bau --output-on-failure \
        -R schlussriegel_nachbau --no-tests=error
Test project /tmp/claude-1000/nachweis0133/unveraendert/bau
    Start 4: schlussriegel_nachbau
1/1 Test #4: schlussriegel_nachbau ............   Passed    4.18 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   4.19 sec
```

### 1b. Derselbe Baum mit einer stumpf gemachten Zeile in `fabrik_riegel_sammeln`

Genau eine Zeile, und das Skript der Messung bricht ab, wenn sie nicht genau einmal
vorkommt (`assert txt.count(alt) == 1`):

```
if(NOT "${${listenname}}" STREQUAL "")
  ->  if(FALSE)  # STUMPF GEMACHT -- Gegenprobe zu Paket 0133, nicht eingecheckt
```

Das ist der Sammler des Riegels: Was er nicht in `eintraege` legt, sieht der Riegel
nicht. Bemerkenswert und der ganze Grund fuer dieses Paket -- **die Konfiguration des
stumpfen Baums meldet weiter gruen und im Wortlaut dasselbe wie oben**:

```
$ cmake -S $TMPDIR/nachweis0133/stumpf/pruefstand \
        -B $TMPDIR/nachweis0133/stumpf/bau -DFABRIK_SANITIZER=ON
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne
   Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.3s)

$ cmake --build $TMPDIR/nachweis0133/stumpf/bau -j 4
[100%] Built target vorrat_verfahren_probe
```

Der neue automatische Lauf faengt es:

```
$ ctest --test-dir $TMPDIR/nachweis0133/stumpf/bau --output-on-failure \
        -R schlussriegel_nachbau --no-tests=error
Test project /tmp/claude-1000/nachweis0133/stumpf/bau
    Start 4: schlussriegel_nachbau
1/1 Test #4: schlussriegel_nachbau ............***Failed    4.27 sec
Stand: HEAD   Kette: /tmp/claude-1000/nachweis0133/stumpf/bau/nachbau0066/werkzeugkette.cmake   (55175 Bytes)

!! a1_zielflags             code=0 (soll 1 an HEAD)
!! b1_quellflags            code=0 (soll 1 an HEAD)
!! b1b_quellopt             code=0 (soll 1 an HEAD)
!! b2_iface                 code=0 (soll 1 an HEAD)
   c1_wnoconv               code=0 (soll 0 an HEAD)
   c2_leereiface            code=0 (soll 0 an HEAD)
!! e10_genexquelle          code=0 (soll 1 an HEAD)
!! e1_addcompileopt         code=0 (soll 1 an HEAD)
!! e2_dirprop               code=0 (soll 1 an HEAD)
!! e4_zweiworte             code=0 (soll 1 an HEAD)
!! e5_zweitequelle          code=0 (soll 1 an HEAD)
   e6_targetobjects         code=0 (soll 0 an HEAD)
   e7_ifacegut              code=0 (soll 0 an HEAD)
!! e8_wnoerrorquelle        code=0 (soll 1 an HEAD)
   p_positiv                code=0 (soll 0 an HEAD)
   r1_ohnesatz              code=1 (soll 1 an HEAD)
        es fehlen: -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow ...
!! r2_privatw               code=0 (soll 1 an HEAD)
!! r3_shellform             code=0 (soll 1 an HEAD)
!! r4_staticpublic          code=0 (soll 1 an HEAD)
   r5_nurschnittstelle      code=1 (soll 1 an HEAD)
        fabrik_schlussriegel: kein einziges uebersetzendes Ziel unter
!! f1_targetdir             code=0 (soll 1 an HEAD)
!! x_unterbaum              code=0 (soll 1 an HEAD)

Positivkontrolle p_positiv: bau code=2, 1 Fehler
        .../p_positiv/z.cpp:1:26: error: conversion from 'double' to 'int' may change value [-Werror=float-conversion]

15 Abweichung(en) vom Soll.

0% tests passed, 1 tests failed out of 1

The following tests FAILED:
	  4 - schlussriegel_nachbau (Failed)
Errors while running CTest
```

**Welche Zeilen reissen, ist mitgemessen und nicht nur die Zahl.** Rot sind die 15
Faelle, in denen ein Abschalter *durchgereicht* wird -- der Sammler bekommt sie nicht
mehr in die Liste. Gruen bleiben die vier Faelle, die gruen bleiben **muessen**
(`c1_wnoconv`, `c2_leereiface`, `e6_targetobjects`, `e7_ifacegut`), dazu `p_positiv`,
das schon im Soll gruen konfiguriert und rot **baut**, und die zwei, die
auf einem anderen Weg als ueber den Sammler urteilen: `r1_ohnesatz` (der Satz **fehlt**,
das misst die Gegenrichtung) und `r5_nurschnittstelle` (kein uebersetzendes Ziel).
Genau die zwei sind der Beleg, dass das Rot aus der stumpf gemachten Zeile kommt und
nicht daraus, dass der Baum insgesamt nicht mehr laeuft.

### 1c. Der zweite Rotnachweis -- die Positivkontrolle allein

Die Positivkontrolle zaehlt seit diesem Paket in den Rueckgabewert. Ein Test, der nie
rot wird, prueft nichts, also ist auch dieser Teil einmal rot gemacht -- und zwar so,
dass **kein einziges** der 22 Urteile kippt. Dritter Baum, aus `FABRIK_STRENGE`
verschwindet allein `-Werror`:

```
    -Wall -Wextra -Werror   ->   -Wall -Wextra
```

Der Riegel prueft danach gegen seinen eigenen, kuerzeren Sollsatz und urteilt ueber
alle 22 Baeume unveraendert. Der Warnsatz greift trotzdem nicht mehr: Was der
Uebersetzer als zweifelhaft erkennt, ist wieder nur eine Warnung.

```
$ ctest --test-dir $TMPDIR/nachweis0133/ohne_werror/bau --output-on-failure \
        -R schlussriegel_nachbau --no-tests=error
1/1 Test #4: schlussriegel_nachbau ............***Failed    4.25 sec
...
   x_unterbaum              code=1 (soll 1 an HEAD)

Positivkontrolle p_positiv: bau code=0, 0 Fehler   !! erwartet war ein roter Bau -- der Warnsatz greift nicht mehr

0 Abweichung(en) vom Soll.

0% tests passed, 1 tests failed out of 1
```

**Null Abweichungen und trotzdem rot** -- das ist die Luecke, um die es geht. Die
Gegenprobe dazu ist der Stand von `nachbau.py` aus `HEAD` (`8a2c381`), auf **demselben**
Baum gefahren:

```
$ git show HEAD:.../befunde/pruefung-0066/nachbau.py  > .../nachbau_alt.py
$ python3 .../nachbau_alt.py
Positivkontrolle p_positiv: bau code=0, 0 Fehler

0 Abweichung(en) vom Soll.
Rueckgabewert: 0
```

Der alte Stand gibt **0** zurueck ueber einen Baum, dessen Warnsatz nichts mehr
erzwingt. Als Aufruf von Hand war das vertretbar -- wer die Ausgabe liest, sieht
`bau code=0` sofort. Als Probe nicht: `ctest` liest nur den Rueckgabewert.

### 1d. Der dritte Rotnachweis -- die Bahn selbst

`FATAL_ERROR` statt `if(EXISTS ...)`: Verschwindet das Skript, bricht die Konfiguration
ab, statt die Probe still zu ueberspringen. Vierter Baum, `befunde/pruefung-0066/`
weggelassen:

```
Konfigurationscode: 1
-- Configuring incomplete, errors occurred!
CMake Error at CMakeLists.txt:136 (message):
  Der Regressionsnachweis des Schlussriegels fehlt:
  /tmp/claude-1000/nachweis0133/ohne_skript/befunde/pruefung-0066/nachbau.py

  Er ist der einzige Nachweis, dass der Riegel in `werkzeugkette.cmake` noch
  prueft, statt nur zu laufen.  Ist er absichtlich umgezogen, gehoert der
  neue Pfad hierher -- nicht diese Bedingung entfernt.
```

## Bedingung 2 -- kein Urteil aendert sich

### 2a. `nachbau.py` von Hand, am Arbeitsbaum

```
$ python3 befunde/pruefung-0066/nachbau.py
...
   x_unterbaum              code=1 (soll 1 an HEAD)
        gefunden in: COMPILE_FLAGS an /tmp/claude-1000/nachbau0066-HEAD/x_unterbaum/mitglied/src/z.cpp:  -w

Positivkontrolle p_positiv: bau code=2, 1 Fehler
        /tmp/claude-1000/nachbau0066-HEAD/p_positiv/z.cpp:1:26: error: conversion from
        'double' to 'int' may change value [-Werror=float-conversion]

0 Abweichung(en) vom Soll.
```

Rueckgabewert 0. Die Ablage ist unveraendert `/tmp/claude-1000/nachbau0066-HEAD` --
ohne `NACHBAU_ABLAGE` verhaelt sich der Aufruf wie vorher, und die beiden Abnahmen, die
ihn namentlich nennen (0103 abgenommen, 0108 offen), sehen keinen Unterschied.

### 2b. Die drei Bauwege in beiden Profilen

**Gemessen an einem ausgepackten Baum, nicht am Arbeitsbereich, und das ist hier
noetig statt sauber:** Waehrend meines Laufs haben Nachbarpakete
`werkzeuge/belegstellen/belegstellen_riegel.cpp` und `werkzeugkette.cmake` im
Arbeitsbaum in einem halbfertigen Zustand stehen (`git status`, beide **nicht** in
meiner `dateien`-Liste). Der Arbeitsbereich uebersetzt damit zeitweise nicht -- eine
Messung dort haette den Bruch eines anderen als meinen ausgewiesen. Beide Baeume
kommen deshalb aus `git archive HEAD` (`8a2c381`); in **rein-nachher** liegen darueber
genau meine zwei Dateien und sonst nichts:

```
$ diff -rq $TMPDIR/nachweis0133/rein-vorher $TMPDIR/nachweis0133/rein-nachher
Files .../rein-vorher/befunde/pruefung-0066/nachbau.py and .../rein-nachher/... differ
Files .../rein-vorher/pruefstand/CMakeLists.txt     and .../rein-nachher/... differ
```

Beide Zahlen sind selbst gemessen; keine ist uebernommen. Je Weg
`cmake -S/-B -DFABRIK_SANITIZER=<Profil>`, `cmake --build -j 4`,
`ctest --output-on-failure --no-tests=error`.

**Vorher** (`rein-vorher`, reiner Stand `8a2c381`):

```
=== rein-vorher, FABRIK_SANITIZER=ON ===
  arbeitsbereich   konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 14
  kern             konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 10
  pruefstand       konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 3
=== rein-vorher, FABRIK_SANITIZER=OFF ===
  arbeitsbereich   konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 14
  kern             konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 10
  pruefstand       konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 3
```

**Nachher** (`rein-nachher`, derselbe Stand plus meine zwei Dateien):

```
=== rein-nachher, FABRIK_SANITIZER=ON ===
  arbeitsbereich   konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 15
        14/15 Test #14: schlussriegel_nachbau ............   Passed    4.17 sec
  kern             konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 10
  pruefstand       konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 4
        4/4 Test #4: schlussriegel_nachbau ............   Passed    4.18 sec
=== rein-nachher, FABRIK_SANITIZER=OFF ===
  arbeitsbereich   konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 15
        14/15 Test #14: schlussriegel_nachbau ............   Passed    4.23 sec
  kern             konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 10
  pruefstand       konfig=0 bau=0 ctest=0   100% tests passed, 0 tests failed out of 4
        4/4 Test #4: schlussriegel_nachbau ............   Passed    4.34 sec
```

| Weg | Profil | Proben vorher | Proben nachher |
|---|---|---|---|
| arbeitsbereich | ON  | 14 | 15 |
| kern           | ON  | 10 | 10 |
| pruefstand     | ON  |  3 |  4 |
| arbeitsbereich | OFF | 14 | 15 |
| kern           | OFF | 10 | 10 |
| pruefstand     | OFF |  3 |  4 |

Sechs von sechs Konfigurations-, Bau- und `ctest`-Codes sind null, vorher wie nachher.
Die Zahl der Proben steigt um die neue und sonst um nichts: plus eins auf den zwei
Wegen, die `pruefstand` enthalten, unveraendert auf `kern`. Der Zuwachs an Laufzeit
ist 4,2 Sekunden je `ctest`-Lauf, in dem der Pruefstand steckt.

**Eine Anmerkung zum Messaufbau, die kein Befund ist:** Der Belegstellenriegel erwartet
die Vorgaben unter `<Baum>/../../specs/<Name des Baums>`. Im ausgepackten Baum lief das
zunaechst ins Leere und der Riegel meldete rot -- laut und mit dem Pfad im Wortlaut,
also genau richtig. Nach einem Verweis `$TMPDIR/specs/rein-{vorher,nachher}` auf
`specs/0016-...` sind alle 14 bzw. 15 Proben gruen. Das betrifft beide Baeume gleich
und keine der Zahlen oben.

**Zu `bauwege.py`:** Es meldet auf einem fehlerfreien Baum weiter Exitcode 1 (feste
Sollzahlen 18/16, gemessen 19/17). Das ist der Gegenstand von 0135 und nach der Abnahme
dieses Pakets ausdruecklich kein Kriterium; angefasst habe ich es nicht.

## Was offen bleibt

- **Der Ort der Bahn ist eine Kollisionsentscheidung, keine Entwurfsentscheidung.**
  Sachlich gehoerte der Nachbau nach `werkzeuge/`, wo der Belegstellenriegel steht: Er
  misst den Baum, nicht das Erzeugnis. Ein eigenes Mitglied braucht aber einen Eintrag
  in `FABRIK_MITGLIEDER` der `CMakeLists.txt` des Vorhabens, und die hielt heute Paket
  0129. Der Ort ist im Kopf der Bahn begruendet; der Umzug kostet spaeter zwei Zeilen.
  Vorschlag `0136` liegt dazu bei.
- **Meine zwei Dateien liegen in einem fremden Commit.** Waehrend meines Laufs hat ein
  paralleler Lauf sie mit eingesammelt: `4ee0f79 datenbauer:
  0078-reihentoml-preisbasis-nach-t53-nachziehen (8 Dateien)` enthaelt
  `pruefstand/CMakeLists.txt` und `befunde/pruefung-0066/nachbau.py` im Wortlaut dieses
  Nachweises (`git diff HEAD` fuer beide leer). Inhaltlich ist nichts verloren, aber
  `git log -S` fuehrt die Arbeit dieses Pakets unter dem Betreff eines anderen -- und
  im selben Commit steckt `belegstellen_riegel.cpp` in einem halbfertigen Zustand, der
  zu diesem Zeitpunkt nicht uebersetzte. Das ist der Gegenstand von Paket `0131`
  (`baulauf-commit-nur-paketdateien`); ich melde es nur, weil dieser Nachweis sonst
  einen Bezugsstand nennt, den man im Log nicht wiederfindet. Bezugsstand meiner
  Messungen ist und bleibt `8a2c381` -- der Stand **vor** diesem Commit.
- **Eine Ungenauigkeit im Paketrumpf, gemeldet und nicht behoben:** Der Rumpf nennt als
  Praezedenzfall „`pruefstand/CMakeLists.txt`, die `add_test`-Zeile in der Schleife
  ueber die Proben". Die Schleife dort legt die Proben **des Pruefstands** an; der
  `add_test`-Eintrag des Belegstellenriegels steht in
  `werkzeuge/belegstellen/CMakeLists.txt`. Am Ergebnis aendert das nichts -- die
  Entscheidung des Projektmanagers traegt aus dem Kollisionsgrund, nicht aus dem
  Praezedenzfall.
