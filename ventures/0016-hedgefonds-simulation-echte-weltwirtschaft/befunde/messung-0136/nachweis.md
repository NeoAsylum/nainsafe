---
typ: nachweis
paket: 0136-schlussriegel-nachbau-in-eigenes-mitglied
rolle: testentwickler
datum: 2026-09-05
stand: 74e1464
ergebnis: beide Bedingungen erfuellt, 0 Abweichungen
---

# Der Waechter des Schlussriegels laeuft nach dem Umzug an denselben Stellen und beisst dort

Gemessen am 2026-09-05 auf dem Stand `74e1464`. Die Skripte dieser Messung liegen
daneben (`aufbau.py`, `messen.py`, `rotnachweis.py`, `raeumen.py`); jede Zahl unten ist
mit ihnen wiederholbar.

## Der Zustand beim Zuschnitt dieses Laufs -- und was daraus fuer die Messung folgt

Der Umzug selbst lag beim Beginn dieses Laufs **schon im Arbeitsbaum und schon
eingecheckt**: `werkzeuge/schlussriegel/CMakeLists.txt` traegt den Zeitstempel 16:09,
und Commit `0333b81` (`projektmanager: … (18 Dateien)`, 19:01) hat ihn mitgenommen. Das
Arbeitspaket stand trotzdem auf `status: offen` -- genau der Fall, den die Rollendatei
des Testentwicklers beschreibt: Der Runner kennt nur das Frontmatter und plant dasselbe
Paket erneut ein. Was fehlte, war nicht der Umzug, sondern **sein Nachweis**: Unter
`befunde/` lag zu diesem Paket keine einzige Datei.

Daraus folgt die einzige Entscheidung dieser Messung, die eine Begruendung braucht:
**Der Stand davor wird gebaut, nicht ausgepackt.** `0333b81^` waere der falsche
Vergleich -- in jenem Commit stecken die Ergebnisse mehrerer Pakete, unter anderem 75
geaenderte Zeilen in `werkzeugkette.cmake`, also genau der Datei, deren Riegel hier
gemessen wird. Ein Vergleich dagegen maesse drei Pakete und nennte es eines.

Stattdessen: eine Kopie des heutigen Baums, in der **nur** dieser Umzug rueckgaengig
gemacht ist. Der Rueckbau ist exakt und nicht nachempfunden, denn `git diff` zwischen dem
jeweils letzten Commit vor dem Umzug und `HEAD` zeigt fuer beide Dateien ausschliesslich
diese Aenderung:

    pruefstand/CMakeLists.txt   4ee0f79 -> HEAD   nur der Waechterblock
    CMakeLists.txt              497bcbc -> HEAD   nur Kopfabsatz + FABRIK_MITGLIEDER

Beide alten Fassungen sind woertlich aus jenen Commits geholt. Dass der Rueckbau der
Rueckbau ist und **nicht mehr**, steht als Messwert da und nicht als Zusicherung:

```
$ diff -rq --exclude=bau <arbeitsbaum> <ablage>/vorher
Files .../CMakeLists.txt and .../vorher/CMakeLists.txt differ
Files .../pruefstand/CMakeLists.txt and .../vorher/pruefstand/CMakeLists.txt differ
Only in .../werkzeuge: schlussriegel
```

Drei Unterschiede, und es sind die drei des Pakets.

## Bedingung 1 -- dieselben Stellen, dasselbe Urteil, eine Probe weniger im Pruefstand

Gemessen mit `befunde/messung-0076/bauwege.py` (Paket 0135) und nicht mit einem zweiten
Messgeraet daneben: Es faehrt beide Profile ueber alle drei Bauwege und vergleicht gegen
den **eigenen Stand davor** statt gegen eine hingeschriebene Sollzahl. `messen.py` fuegt
dreierlei hinzu und aendert an jener Datei nichts -- sie gehoert Paket 0135.

**Alle sechs Bauwege des Arbeitsbaums: Konfiguration, Bau und `ctest` mit Code 0, null
Abweichungen gegen den Stand davor.**

```
$ python3 befunde/messung-0076/bauwege.py nachher136 --gegen-datei <ablage>/bauwege0076-vorher136/stand.json
Stand davor: Arbeitsbaum <ablage>/vorher am 2026-09-05 auf 74e1464
   FABRIK_SANITIZER=OFF   arbeitsbereich=18  kern=11  pruefstand=4
   FABRIK_SANITIZER=ON    arbeitsbereich=20  kern=12  pruefstand=5

=== Profil sanitizer-an (FABRIK_SANITIZER=ON) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=20 (Stand davor 20)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=12 (Stand davor 12)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=5 (Stand davor 5)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 3
=== Profil sanitizer-aus (FABRIK_SANITIZER=OFF) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=18 (Stand davor 18)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=11 (Stand davor 11)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=4 (Stand davor 4)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 3

0 Abweichung(en).
rueckgabe=0
```

Der Bauweg `werkzeuge/schlussriegel` **allein** steht im Abschnitt darunter zweimal --
gruen und stumpf; sein Alleinbau ist damit an derselben Stelle belegt wie der
Rotnachweis und nicht doppelt gefahren.

**Die Zahl der Proben, vorher gegen nachher.** `bauwege.py` zaehlt uebersetzende Ziele;
die Abnahme dieses Pakets fragt nach Proben, und der Waechter ist eine Probe **ohne**
Ziel. Deshalb liest `messen.py` die Bilanzzeile aus den `ctest`-Protokollen, die
`bauwege.py` selbst abgelegt hat, und stellt sie gegenueber:

```
   sanitizer-an  arbeitsbereich  Proben 16 -> 16 (+0, erwartet +0)   verfehlt vorher=0 nachher=0
   sanitizer-an  kern            Proben 10 -> 10 (+0, erwartet +0)   verfehlt vorher=0 nachher=0
   sanitizer-an  pruefstand      Proben  4 ->  3 (-1, erwartet -1)   verfehlt vorher=0 nachher=0
   sanitizer-aus arbeitsbereich  Proben 16 -> 16 (+0, erwartet +0)   verfehlt vorher=0 nachher=0
   sanitizer-aus kern            Proben 10 -> 10 (+0, erwartet +0)   verfehlt vorher=0 nachher=0
   sanitizer-aus pruefstand      Proben  4 ->  3 (-1, erwartet -1)   verfehlt vorher=0 nachher=0

0 Abweichung(en).
```

Das ist die Abnahme Wort fuer Wort: Der Arbeitsbereich haelt seine Zahl -- die Probe
wechselt den Kasten, sie kommt nicht hinzu --, und der Bauweg `pruefstand` faellt um
genau eins. `kern` hat sie nie gehabt und aendert sich nicht; er steht hier, weil ein
Mass, das nur die zwei betroffenen Wege ansieht, den Fall nicht faende, in dem sich
nebenher etwas Drittes bewegt.

**Die eine Abweichung des Vorlaufs ist eine Eigenschaft des Messaufbaus und keine des
Baums.** `bauwege.py` holt seinen Vergleichsstand mit `git archive HEAD <pfad>`; der
Vergleichsbaum liegt unter einem in `.gitignore` gefuehrten Ordner, also gibt es ihn in
`HEAD` nicht:

```
!! Vergleichsstand nicht zu bekommen: `git archive HEAD` gab Code 128:
   fatal: pathspec '.../bau/messung-0136/vorher' did not match any files
1 Abweichung(en).   rueckgabe=1
```

Das ist die Bauart von 0135 und richtig so: Ein ausgefallenes Mass meldet rot statt
gruen. Fuer diese Messung wird der Vorlauf nicht als Urteil gebraucht, sondern als
**Stand** -- seine sechs Zahlen sind der Vergleich, gegen den der Hauptlauf oben faehrt.
Alle sechs `ctest`-Laeufe des Vorlaufs sind selbst Code 0.

**Ein Fund am Rande, der den Vorlauf erst brauchbar gemacht hat.** Beim ersten Versuch
war der Vergleichsbaum auf dem Bauweg `arbeitsbereich` in **beiden** Profilen rot:

```
15/16 Test #15: belegstellen_riegel ..............***Failed    0.02 sec
belegstellen_riegel: '.../bau/specs/vorher' ist kein Verzeichnis.
```

Der Belegstellenriegel schlaegt die Vorgaben ueber den Ort des Vorhabens nach
(`<vorhaben>/../../specs/<name>`) und bricht ab, wenn dort nichts liegt -- richtig so,
denn ohne die Vorgaben liefe jedes Zitat in sie als "Ziel ausserhalb des Bestands"
durch. Ein **kopierter** Baum steht aber an einem Ort, an dem er nichts findet. Ein
Vorlauf, der aus fremdem Grund rot ist, meldet jede Aenderung als gefangen; deshalb legt
`aufbau.py` die Vorgaben jetzt dorthin, wo der Riegel des Wegwerf-Baums sucht. Danach
ist der Vorlauf in beiden Profilen und auf allen drei Wegen gruen -- und damit ein
fairer Pruefstand und nicht bloss eine Kopie.

## Bedingung 2 -- der Rotnachweis am neuen Ort

Ein gruener Lauf allein belegt nichts: Ein `add_test`, das am neuen Ort ins Leere zeigt,
meldet ebenfalls gruen. Deshalb dieselbe Gegenprobe wie in Paket 0133, an derselben
Zeile, nur an der neuen Bahn. Genau eine Zeile, und `aufbau.py` bricht ab, wenn der
Wortlaut nicht **genau einmal** in `werkzeugkette.cmake` vorkommt:

```
if(NOT "${${listenname}}" STREQUAL "")
  ->  if(FALSE)  # STUMPF GEMACHT -- Gegenprobe zu Paket 0136, nicht eingecheckt
```

Gebaut wird fuer diesen Nachweis nichts. Die Probe ist ein Skriptaufruf und haengt an
keinem Ziel; `cmake -S` allein reicht, damit `ctest` sie kennt.

### Der Weg, den der Nachtlauf faehrt -- `arbeitsbereich`

```
$ cmake -S <ablage>/gruen -B <ablage>/gruen/bau-rot-arbeitsbereich -DFABRIK_SANITIZER=ON
   code=0   -- Warnsatz-Schlussriegel: 20 uebersetzende Ziele geprueft, alle mit Warnsatz
              und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ...
$ ctest --test-dir <ablage>/gruen/bau-rot-arbeitsbereich --output-on-failure \
        -R schlussriegel_nachbau --no-tests=error
   code=0
        1/1 Test #16: schlussriegel_nachbau ............   Passed    4.51 sec
        100% tests passed, 0 tests failed out of 1

$ cmake -S <ablage>/stumpf -B <ablage>/stumpf/bau-rot-arbeitsbereich -DFABRIK_SANITIZER=ON
   code=0   -- Warnsatz-Schlussriegel: 20 uebersetzende Ziele geprueft, alle mit Warnsatz
              und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ...
$ ctest --test-dir <ablage>/stumpf/bau-rot-arbeitsbereich --output-on-failure \
        -R schlussriegel_nachbau --no-tests=error
   code=8
        1/1 Test #16: schlussriegel_nachbau ............***Failed    4.63 sec
        0% tests passed, 1 tests failed out of 1
        15 von 22 Faellen gekippt: a1_zielflags, b1_quellflags, b1b_quellopt, b2_iface,
        e10_genexquelle, e1_addcompileopt, e2_dirprop, e4_zweiworte, e5_zweitequelle,
        e8_wnoerrorquelle, r2_privatw, r3_shellform, r4_staticpublic, f1_targetdir, x_unterbaum
```

**Die Konfigurationsmeldung ist in beiden Baeumen dieselbe, Wort fuer Wort.** Das ist
nicht nebensaechlich, sondern der ganze Grund, warum es diesen Waechter gibt: Der
stumpfe Baum meldet `alle mit Warnsatz und ohne Pauschalabschalter` und konfiguriert mit
Code 0. Wer nur auf den Riegel selbst sieht, sieht nichts. Gefangen wird er allein von
der Probe.

### Der Alleinbau des neuen Kastens -- `werkzeuge/schlussriegel`

```
$ cmake -S <ablage>/gruen/werkzeuge/schlussriegel -B <ablage>/gruen/bau-rot-werkzeuge-schlussriegel \
        -DFABRIK_SANITIZER=ON
   code=0   (keine Riegelmeldung -- dieser Kasten bindet die Werkzeugkette nicht ein)
$ ctest ... -R schlussriegel_nachbau --no-tests=error
   code=0
        1/1 Test #1: schlussriegel_nachbau ............   Passed    4.53 sec

$ cmake -S <ablage>/stumpf/werkzeuge/schlussriegel -B <ablage>/stumpf/bau-rot-werkzeuge-schlussriegel \
        -DFABRIK_SANITIZER=ON
   code=0
$ ctest ... -R schlussriegel_nachbau --no-tests=error
   code=8
        1/1 Test #1: schlussriegel_nachbau ............***Failed    4.69 sec
        15 von 22 Faellen gekippt: (dieselben fuenfzehn)
```

Dass der Alleinbau **keine** Riegelmeldung druckt, ist der beabsichtigte Zustand und in
`werkzeuge/schlussriegel/CMakeLists.txt` begruendet: Der Kasten traegt kein
uebersetzendes Ziel, und der Schlussriegel bricht seit dem 2026-09-04 ab, wenn er keines
sieht. Er bindet die Werkzeugkette beim Alleinbau deshalb als einziges Mitglied des
Baums nicht ein. Der Waechter beisst dort trotzdem -- er misst die Kette als **Datei**
und nicht als eingebundenes Modul.

### Der alte Ort -- `pruefstand`

```
$ ctest --test-dir <ablage>/gruen/bau-rot-pruefstand ... -R schlussriegel_nachbau --no-tests=error
   code=8   No tests were found!!!
$ ctest --test-dir <ablage>/stumpf/bau-rot-pruefstand ... -R schlussriegel_nachbau --no-tests=error
   code=8   No tests were found!!!
```

Beide rot, und das ist hier die richtige Antwort: Die Probe ist aus diesem Kasten fort.
`--no-tests=error` ist die Zeile, die daraus eine Aussage macht -- ohne sie gaebe `ctest`
fuer "kein Treffer" den Code 0 zurueck und der Beleg waere von einem gruenen Lauf nicht
zu unterscheiden.

**Dass die fuenfzehn gekippten Faelle dieselben sind wie im Nachweis zu Paket 0133**,
ist die Gegenprobe zur Gegenprobe: Der Umzug hat die Bahn verschoben und am Urteil nichts
geaendert. Gruen bleiben dieselben sieben -- die vier, die gruen bleiben **muessen**
(`c1_wnoconv`, `c2_leereiface`, `e6_targetobjects`, `e7_ifacegut`), die Positivkontrolle
`p_positiv`, die gruen konfiguriert und rot **baut**, und die zwei, die auf einem anderen
Weg als ueber den Sammler urteilen (`r1_ohnesatz`, `r5_nurschnittstelle`). Genau die
letzten zwei belegen, dass das Rot aus der stumpf gemachten Zeile kommt und nicht daraus,
dass der Baum insgesamt nicht mehr laeuft.

## Was ich nicht angefasst habe

`werkzeugkette.cmake` im Arbeitsbaum (Vorgabe des Projektmanagers -- sie fuehrt am
2026-09-05 die laengste Kette offener Pakete), `befunde/pruefung-0066/nachbau.py`,
`befunde/messung-0076/bauwege.py` (Paket 0135), die 22 Faelle und der Riegel selbst. Die
Mutation lebt ausschliesslich in einer Kopie unter `bau/`, und `bau/` steht in
`.gitignore`.

## Worauf ich unsicher bin

**Der Ort ist meiner Meinung nach richtig, aber ich habe ihn nicht gewaehlt.** Der
Projektmanager hat vorgegeben zu melden, falls der Waechter sachlich woandershin gehoert
als unter `werkzeuge/schlussriegel`. Mir ist beim Umzug nichts aufgefallen, was dagegen
spricht: Er misst den Baum, er haengt an nichts, er wird von nichts gelinkt -- dieselbe
Gattung wie `werkzeuge/belegstellen` und `werkzeuge/bezeichner`, und die
`CMakeLists.txt` des Vorhabens beschreibt sie im Kopf bereits als eigene Gattung.

**Eine Eigenheit bleibt und ist im Kasten begruendet, nicht versteckt:**
`werkzeuge/schlussriegel` ist das einzige Mitglied, das `werkzeugkette.cmake` beim
Alleinbau nicht einbindet, und das einzige mit `LANGUAGES CXX` ohne eine einzige
Quelldatei. Beides sind Ausnahmen mit Messwert dahinter; wer sie fuer falsch haelt,
findet die Rechnung in `werkzeuge/schlussriegel/CMakeLists.txt` und muss sie nicht aus
dem Verhalten erschliessen.

**Der Korpus driftete waehrend dieses Laufs**, wie an jedem Tag dieser Woche: Zwischen
dem Zuschnitt und dem Ende sind `HEAD` von `0333b81` auf `74e1464` gewandert und
mindestens drei fremde Pakete (0105, 0108, 0139) haben im Arbeitsbaum geschrieben. Der
Vergleichsbaum ist deshalb eine Kopie **eines Augenblicks**; Vorlauf und Hauptlauf liegen
rund vier Minuten auseinander. Dass in diesem Fenster nichts Drittes gewandert ist,
belegt die Zeile `kern 10 -> 10` und die durchweg gleichen Zielzahlen -- nicht meine
Annahme.
