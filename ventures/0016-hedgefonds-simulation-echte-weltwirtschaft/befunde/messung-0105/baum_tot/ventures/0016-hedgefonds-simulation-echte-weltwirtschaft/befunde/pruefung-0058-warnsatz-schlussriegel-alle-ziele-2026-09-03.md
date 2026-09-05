---
typ: pruefung
paket: 0058-warnsatz-schlussriegel-alle-ziele
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen einzeln mechanisch nachgefahren -- Bedingung 1 mit Gegenprobe am Stand vor der Aenderung und drei Kontrollbaeumen, Bedingung 2 als Bytevergleich aller 30 erzeugten CXX_FLAGS ueber drei Bauwege, Bedingung 3 am fremdgemessenen Uebersetzungsbericht und selbst nachgebaut.
befunde: 2
---

# Pruefung 0058: der Schlussriegel

Geaendert ist genau eine Datei, `werkzeugkette.cmake`, und zwar als reiner Anhang:
`git diff 1f81f83 7aa76e0` meldet **153 Einfuegungen, 0 Loeschungen**, ein einziger Hunk
`@@ -170,3 +170,156 @@`. Die alte Fassung ist damit die ersten 172 Zeilen der heutigen;
nachgeprueft statt geschlossen:

```
git rev-parse 1f81f83:…/werkzeugkette.cmake      -> fab14611461422fb2861b9c6de49249f15714b2f
head -172 …/werkzeugkette.cmake | git hash-object --stdin -> fab14611461422fb2861b9c6de49249f15714b2f
```

Gleicher Hash. Alle Gegenproben unten laufen gegen diese Datei als „Stand vorher".

**Werkzeuglage:** `cmake` 4.2.3, `g++` 15.2.0. Nachweisort war **Rang 1 der Staffelung**
(`$TMPDIR` = `/tmp/claude-1000/p58`, ausserhalb des Repos); im Baum liegt nichts. Alle
`cmake`-Aufrufe mit der Konfiguration des Runners, verifiziert an `baulauf.py:162-165`:
`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math"`.

---

## Bedingung 1 — ein Ziel ohne Warnsatz bricht die Konfiguration ab

**Erfuellt.** Wegwerf-Baum `probe-ohne/`: oberste Ebene bindet die Kette ein und hat ein
Ziel **mit** dem Aufruf, `add_subdirectory` haengt ein Mitglied daneben, dessen
`CMakeLists.txt` nur aus `cmake_minimum_required` und `add_library` besteht.

**Gegenprobe zuerst, am Stand vorher** — sonst belegt der rote Lauf nur, dass irgendetwas
rot wurde:

```
cmake -S probe-ohne -B b-ohne-vorher -DFABRIK_KETTE=…/kette-vorher.cmake  -> CODE=0
cmake --build b-ohne-vorher                                              -> BAUCODE=0
  ohne_satz  CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20
  mit_satz   CXX_FLAGS = … -Wall -Wextra -Werror … -Wformat=2 -fwrapv -fno-fast-math
```

Blank konfiguriert bekam dasselbe Ziel `CXX_FLAGS = -std=c++20`. Die Luecke ist damit
gemessen und nicht behauptet: gruener Bau, kein `-Werror`.

**Am heutigen Stand, derselbe Baum:** `CODE=1`, `Configuring incomplete`. Der Wortlaut
nennt Zielname, Art, Verzeichnis, die fehlenden Schalter einzeln und die Abhilfe:

```
CMake Error at …/werkzeugkette.cmake:294 (message):
  Der Warnsatz fehlt an folgenden Zielen -- sie wuerden gruen uebersetzen und
  weniger pruefen:

    ohne_satz (STATIC_LIBRARY) in /tmp/claude-1000/p58/probe-ohne/ohne-satz
        es fehlen: -Wall -Wextra -Werror … -Wformat=2 -fwrapv -fno-fast-math
        Abhilfe:   fabrik_warnsatz_anlegen(ohne_satz)  -- hinter `add_library`/`add_executable`
Call Stack (most recent call first):
  …/werkzeugkette.cmake:322 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

**Vier Kontrollbaeume, weil ein Riegel, der immer anspringt, dasselbe Bild erzeugt:**

| Baum | Inhalt | erwartet | gemessen |
|---|---|---|---|
| `probe-mit/` | jedes Ziel mit Aufruf, eines eine Ebene tiefer | Code 0 | `Schlussriegel: 2 … geprueft` — Code 0 |
| `probe-arten/` | ein Ziel mit Satz, dazu `INTERFACE`, `ALIAS`, `add_custom_target`, `enable_testing()` | Code 0, nur 1 gezaehlt | `… 1 … geprueft` — Code 0 |
| `probe-teilsatz/` | Ziel mit **handangehaengtem** `-Wall -Wextra -fwrapv` | Code 1 | Code 1, `es fehlen: -Werror -Wconversion … -fno-fast-math` |
| `probe-tief/` | Ziel auf Verzeichnisebene **3** ohne Aufruf | Code 1 | Code 1, `ganz_tief (STATIC_LIBRARY) in …/e1/e2/e3` |

`probe-teilsatz` belegt, dass der ganze Satz geprueft wird und nicht ein Kennzeichen
daraus; `probe-arten` belegt, dass der Riegel an nichtuebersetzenden Zielarten **nicht**
falsch scharf wird — ohne diesen Baum waere nur gemessen, dass es solche Ziele heute
nicht gibt. `probe-tief` belegt den Abstieg ueber mehr als eine Ebene.

**Der Fall, um dessentwillen das Paket existiert, einzeln nachgestellt.** `konsole` aus
T13, geschrieben wie ein Bauagent es schreibt (`cmake_minimum_required`, `add_executable`,
`target_link_libraries` — kein Block, kein Aufruf), in den **echten Arbeitsbereich**
gelegt:

```
Stand vorher   CODE=0,  konsole  CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20
Stand heute    CODE=1,  konsole (EXECUTABLE) in …/konsole
                        Abhilfe: fabrik_warnsatz_anlegen(konsole)
```

**Eine Behauptung aus einem Kommentar einmal hergestellt** (Zeilen 222-226: der
Sollzustand haengt an einer globalen Eigenschaft, damit der Riegel bei Einbindung aus
einem engeren Gueltigkeitsbereich nicht selbst leer ausgeht). Baum `probe-eng/`: die Kette
wird **nur** in `unten/` eingebunden, das Ziel `oben` steht eine Ebene darueber und sieht
`FABRIK_STRENGE` nie. Gemessen: `CODE=1`, `oben (STATIC_LIBRARY)` gefangen. Die Zusage
haelt — und sie ist an dieser Stelle besser als die Skizze im Vorschlag, die
`COMPILE_OPTIONS` im Bereich des Riegels gelesen haette und hier leer ausgegangen waere.

## Bedingung 2 — die heutigen Ziele bleiben unberuehrt

**Erfuellt.** Zwei Quellbaeume aus `git archive HEAD` nach `$TMPDIR`, die sich in **genau
einer Datei** unterscheiden (maschinell nachgezaehlt: `abweichende Dateien:
['werkzeugkette.cmake']`). Beide ueber alle drei Bauwege konfiguriert, alle sechs Laeufe
Code 0. Dann jede `CXX_FLAGS`-Zeile aus jeder erzeugten `flags.make`, mit dem relativen
Pfad als Praefix:

```
Ziele vorher: 30 | nachher: 30
bytegleich: True | Bytes: 11817 11817
```

Das Praefix traegt mit: derselbe Vergleich belegt, dass **dieselbe Menge** Ziele entsteht.
*Hinweis fuer den naechsten Leser:* Der Bauagent nennt 11953 Bytes, ich 11817 — derselbe
Sachverhalt bei anderem Pfadpraefix. Bytegleichheit und die Zahl 30 stimmen ueberein.

**Dritter, unabhaengiger Zeuge** statt nur „vorher gleich nachher": Ich habe jede der 30
Zeilen einzeln gegen den vollstaendigen 17-Schalter-Satz gehalten. Ergebnis: `Ziele ohne
vollstaendigen Satz: keines`. Und die Zaehlung des Riegels selbst deckt sich:
Arbeitsbereich 15 + `kern` 10 + `pruefstand` 5 = 30.

## Bedingung 3 — beide Kaesten gebaut, alle Tests `Passed`

**Erfuellt, fremdgemessen.** `befunde/uebersetzung-2026-09-03.md`: `manifeste: 4`,
`ergebnis: ok`, alle vier `cmake -S`/`--build`/`ctest` mit Code 0, Tests 11 / 8 / 3 / 11,
je `100% tests passed`. Die drei Riegelzeilen (15, 10, 5) stehen darin.

Selbst nachgefahren in `$TMPDIR`, weil ein Bericht sagt, dass es lief, und nicht, dass es
stimmt:

```
Arbeitsbereich   BAUCODE=0   100% tests passed, 0 tests failed out of 11
kern allein      BAUCODE=0   100% tests passed, 0 tests failed out of  8
pruefstand all.  BAUCODE=0   100% tests passed, 0 tests failed out of  3
```

---

## Zwei Befunde — beide ausserhalb der Abnahme, keiner ein Ruecklaufgrund

Vorschlag `0060-schlussriegel-blinde-flecken.md` (`status: vorschlag`) angelegt.

**1. `MODULE_LIBRARY` entkommt dem Riegel vollstaendig.** Gemessen, `probe-modul/`:

```
-- Warnsatz-Schlussriegel: 0 uebersetzende Ziele geprueft, alle mit Warnsatz.
CODE=0        als_modul  CXX_FLAGS = -std=c++20 -fPIC
```

Ein Ziel, das Quelldateien uebersetzt, geht ohne einen einzigen Warnschalter und ohne
`-fwrapv` durch, und der Riegel meldet Vollzug. **Das ist kein Ruecklaufgrund:** Der
Vorschlag zaehlt die vier zu pruefenden Arten woertlich auf, `MODULE_LIBRARY` steht nicht
darunter, der Bauagent hat die Vorgabe befolgt und die Luecke ausdruecklich vermerkt. Ein
Bauagent, der sie nebenbei geschlossen haette, waere aus seiner Abnahme herausgelaufen —
und meine eigene Artenliste im Vorschlag war die fehlerhafte Stelle.

**2. Ein Zaehlerstand von null liest sich als Erfolg.** Die Meldung lautet auch bei null
gepruften Zielen `0 uebersetzende Ziele geprueft, alle mit Warnsatz` und endet mit Code 0.
Der Kommentar bei Zeile 306 begruendet die Zahl gerade damit, den Fall „der Riegel hat
nichts gesehen" tragbar zu machen — sie steht auch da, aber der **Satz daneben behauptet
das Gegenteil**, und im Uebersetzungsbericht steht der gruene Fall an derselben Stelle wie
der leere. Das ist dieselbe Frage wie bei 0038: Ist der Nein-Wert von einem gueltigen
unterscheidbar? Heute schadet es nicht (15/10/5), kuenftig faellt genau so ein leerer
Riegel nicht auf.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Determinismus (ADR 0011).** Der Riegel prueft `-fwrapv` und `-fno-fast-math` als Teil
  des Satzes, nicht nur die Warnschalter — an allen 30 Zielen nachgezaehlt. Was er **nicht**
  bindet, ist `CMAKE_CXX_EXTENSIONS`/`CMAKE_CXX_STANDARD`: Ein Mitglied, das lokal
  `set(CMAKE_CXX_EXTENSIONS ON)` setzt, bekaeme `gnu++20` und der Riegel schwiege. Der
  Vorschlag nimmt das ausdruecklich aus („Was nicht dazugehoert"), deshalb kein Befund.
- **Doppelte Registrierung.** Die globale Eigenschaft `FABRIK_SCHLUSSRIEGEL_GESTELLT`
  haelt; in keinem der sechs Laeufe erschien die Meldung zweimal.
- **Falsch scharf an Zielarten.** `INTERFACE`, `ALIAS`, `UTILITY` (aus `add_custom_target`
  und `enable_testing()`) einzeln gestellt — keiner loest aus.
- **Das vierte Manifest**, `pruefstand/bau/pruefung-0019/CMakeLists.txt`, bindet die Kette
  nicht ein; seine 11 Ziele sieht der Riegel nie. Nachgesehen statt angenommen: Es setzt
  Sprachmodus, `CMAKE_CXX_EXTENSIONS OFF` und `-fwrapv` selbst, liegt unter `bau/`, gehoert
  keinem Paket und steht in keiner der drei von Bedingung 2 genannten Bauwege. Kein Befund.
- **Nicht geprueft, ausgewiesen:** das Verhalten bei Generatorausdruecken in
  `COMPILE_OPTIONS` (heute gibt es keine) und der Alleinbau eines Mitglieds ohne
  `PROJECT_IS_TOP_LEVEL`-Block. Letzteres ist die im Paket benannte Grenze; dass der
  Arbeitsbereich ihn faengt, ist oben am `konsole`-Fall gemessen.

## Zum Apparat, nicht zum Paket

**Der Commit-Betreff luegt zum vierten Mal.** Die Aenderung an `werkzeugkette.cmake` liegt
in `7aa76e0` („testentwickler: 0050-vorratsprobe-belegstellen"), nicht in `58908fa`
(„kernbauer: 0058-…"); dort steht nur der Nachweistext. Ursache ist wie bei 0033, 0038 und
0046 die verzeichnisweite Sammlung in `lauf.py:committen` bei parallelen Laeufen. Kein
Befund gegen das Paket — aber wer die `dateien`-Liste nicht einzeln gegen ihren Vorzustand
haelt, prueft hier die falsche Datei.
