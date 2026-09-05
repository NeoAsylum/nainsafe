---
id: 0046-warnsatzriegel-fuer-kuenftige-mitglieder
rolle: kernbauer
status: fertig
haengt_an: [0031-warnsatz-in-die-werkzeugkette]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Ein Mitglied ohne Werkzeugkette muss abbrechen, nicht still ohne Warnschalter bauen

Vorschlag aus der Pruefung von Paket 0031 (2026-09-03, Rolle `kern-pruefer`).
Befund und Messungen stehen in
`befunde/pruefung-0031-warnsatz-in-die-werkzeugkette-2026-09-03.md`.

## Der Befund

Paket 0031 hat `FABRIK_STRENGE` richtig nach `werkzeugkette.cmake` verschoben. Damit
erreicht der Warnsatz ein Mitglied nur noch auf zwei Wegen: ueber die
Verzeichnisvererbung beim Arbeitsbereichsbau, oder ueber den eigenen
`PROJECT_IS_TOP_LEVEL`-Block beim Alleinbau.

Fehlt dieser Block -- oder steht `target_compile_options` versehentlich davor --, dann
steht dort `target_compile_options(x PRIVATE )` mit null Schaltern. Gemessen:

- Eine undefinierte `FABRIK_STRENGE` expandiert in CMake zu einer Liste der Laenge 0 und
  zu einer leeren Zeichenkette. Kein Fehler, keine Warnung, die Konfiguration laeuft durch.
- Eine Uebersetzungseinheit mit einer ungenutzten Variablen uebersetzt mit dem Rest
  (Sprachstand und Ueberlaufschalter) mit Code 0 -- gruen.

Das ist Zeichen fuer Zeichen die Signatur, gegen die Paket 0031 geschrieben wurde: Der
Kasten uebersetzt gruen, prueft weniger, und der Uebersetzungsbericht sagt `ergebnis: ok`.

## Warum der Umzug das verschaerft hat

Vor dem Umzug trug jedes Mitglied eine eigene `set()`-Fassung. Ein vergessener
Einbindungsblock kostete dann die Werkzeugkette und `enable_testing()` -- und der zweite
Verlust ist **laut**: `ctest` meldet "No tests were found!!!", genau wie
`pruefstand/CMakeLists.txt` in den Zeilen 17 bis 20 beschreibt. Der Warnsatz blieb.

Jetzt faellt er mit. Ein Mitglied **ohne eigene Proben** hat den lauten Teil gar nicht --
`konsole` und `oberflaeche` aus T13 sind Binaerprogramme. Es verliert alle 15 Schalter
lautlos.

T13 nennt sieben Mitglieder, fuenf davon existieren noch nicht. Das ist dasselbe
Mengenargument, mit dem Paket 0031 selbst begruendet wurde -- nur eine Ebene tiefer: Nicht
mehr "der siebte abgeschriebene Satz verliert eine Zeile", sondern "das siebte Mitglied
vergisst die Einbindung und verliert alle".

## Warum das ein eigenes Paket ist und nicht Teil von 0031

Es ist **keine der vier Abnahmebedingungen von 0031**, und keine davon ist verletzt --
das Paket ist geprueft. Die Aenderung faellt ausserdem unter genau das, was der Abschnitt
"Was nicht dazugehoert" dem Bauagenten von 0031 verbietet: eine eigene Entscheidung mit
eigener Begruendung. Ein Bauagent, der sie nebenbei mitgemacht haette, haette die Abnahme
verlassen.

Es ist auch kein offenes Kernpaket: Die Aenderung ist nur sinnvoll, wenn sie
`werkzeugkette.cmake` **und beide** vorhandenen Mitglieder zugleich umstellt, damit die
neue Form ueberhaupt einen Nachweis hat.

Es haengt an 0031, weil es dessen Ergebnis voraussetzt: Vor dem Umzug gab es die Luecke
in dieser Form nicht.

## Was zu tun ist

Die Bauform steht dem Bauagenten frei; die Abnahme prueft die Wirkung, nicht den Weg.
Ein Weg, der nachweislich traegt: `werkzeugkette.cmake` stellt eine Funktion bereit --
etwa `fabrik_warnsatz_anlegen(<ziel>)` --, die den Warnsatz und die Ueberlaufschalter an
ein Ziel haengt, und die beiden vorhandenen `CMakeLists.txt` rufen sie statt der heutigen
`target_compile_options`-Zeilen auf.

Der Grund, warum eine Funktion und nicht ein `if(NOT DEFINED …)`-Riegel in jedem
Mitglied: Ein Riegel kann vom siebten Mitglied genauso vergessen werden wie die
Einbindung -- das waere derselbe Fehler eine Ebene hoeher. Ein Aufruf, den CMake nicht
kennt, ist dagegen ein harter Konfigurationsfehler. Gemessen: `Unknown CMake command`,
Code 1, die naechste Zeile wird nicht mehr erreicht.

**Was nicht dazugehoert:** die Werte des Warnsatzes aendern, `-Wpedantic` aufnehmen, ein
zweites Bauprofil einfuehren, oder `FABRIK_SANITIZER_SCHALTER` in dieselbe Funktion
ziehen -- die Sanitizer haengen nach ADR 0011 Massnahme 2 nur an den `_geprueft`-Zielen
und haben eine andere Sichtbarkeit (`PUBLIC` statt `PRIVATE`).

## Abnahme

1. **Ein Mitglied ohne Werkzeugkette bricht ab.** Nachweis: ein Wegwerf-Verzeichnis
   ausserhalb des Repos mit einer `CMakeLists.txt`, die den
   `PROJECT_IS_TOP_LEVEL`-Block **nicht** hat, sonst aber gebaut ist wie
   `pruefstand/CMakeLists.txt`. `cmake -S … -B …` endet mit Code ungleich 0. In den
   Nachweis gehoert der Wortlaut der Fehlermeldung. Heute endet derselbe Fall mit Code 0
   und baut gruen -- das ist die Gegenprobe, und sie gehoert daneben, gemessen am Stand
   **vor** der Aenderung.
2. **Beide vorhandenen Kaesten tragen unveraendert alle 15 Schalter.** Nachweis: die
   Zeile `CXX_FLAGS` aus der von CMake erzeugten `flags.make`, an drei Stellen --
   `kern` im Alleinbau, `pruefstand` im Alleinbau, `pruefstand` im Arbeitsbereichsbau.
   Alle drei bytegleich zu der von heute. Nicht "der Bau ist gruen": Ein leerer Satz
   baut auch gruen, das ist der ganze Punkt dieses Pakets.
3. **Der Uebersetzungsbericht des Tages zeigt beide Kaesten gebaut und alle Tests
   `Passed`**, ueber den Alleinbau-Weg von `baulauf.py` und ueber den Arbeitsbereich.

Bedingung 1 ist der eigentliche Nachweis, und sie kommt ohne eine Datei im Baum aus --
das Wegwerf-Verzeichnis liegt ausserhalb des Repos. Die Falle aus der Warnung an 0031
(eine liegengebliebene Probedatei vergiftet die Bibliothek fuer jeden nachfolgenden Lauf)
gibt es hier deshalb nicht.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

**Umnummeriert von `0045` auf `0046`.** Die Kennung 0045 war doppelt vergeben: Zwei Prüfer
haben am 2026-09-03 im Abstand von einer Minute je einen Vorschlag angelegt und konnten
die Nummer des anderen nicht sehen (19:33 `daten-pruefer`, 19:34 `kern-pruefer`). Der
frühere behält die Nummer, dieser weicht — nicht wegen des Alters, sondern weil beide
gleich oft zitiert werden, nämlich null mal. Kein `haengt_an` und kein Bericht verwies auf
den alten Namen; nachgeprüft mit `grep` über alle Pakete und `ops/plan.md`. Alter Name für
die Suche: `0045-warnsatzriegel-fuer-kuenftige-mitglieder`.

Die vier Prüfungen meiner Rolle:

- **Rolle:** `kernbauer` existiert und wird eingeplant. ✓
- **Abhängigkeit:** `0031` ist mit diesem Lauf `fertig`. Die Sperre fällt. ✓
- **Dateischnitt:** `werkzeugkette.cmake`, `kern/CMakeLists.txt` und
  `pruefstand/CMakeLists.txt` stehen in keiner anderen `dateien`-Liste — weder unter
  `offen` noch unter `gebaut`. Die vier Pakete, die diese Dateien im Fliesstext erwähnen
  (0004, 0008, 0019, 0020), sind alle `fertig` und beanspruchen sie nicht. ✓
- **Abnahme:** prüfbar, aber Bedingung 1 war für den Bauagenten nicht durchführbar. Siehe
  unten.

**Der Vorschlag begründet richtig, warum das kein Teil von 0031 ist:** Es ist keine seiner
vier Bedingungen, keine davon ist verletzt, und die Änderung fiele unter genau das, was
0031 seinem Bauagenten als eigene Entscheidung verbietet. Auch die Wahl Funktion statt
Riegel ist mit einer Messung begründet, nicht mit Geschmack.

### Berichtigung zu Bedingung 1 — der Nachweisort, nicht der Nachweis

**Bedingung 1 verlangt ein Wegwerf-Verzeichnis „ausserhalb des Repos". Das kann in dieser
Umgebung fehlschlagen, und dann steht der Bauagent vor einem Kriterium, das er nicht
erfüllen kann.** Am selben Tag gemessen, in zwei Richtungen: Der Prüfer von 0011 notiert,
`Write` und jeder `Bash`-Aufruf, der eine Datei ausserhalb des Repos anlegt, sei mit
*„Permission to use … has been denied"* geendet — er konnte deshalb keine
Übersetzungsprobe schreiben. Der Prüfer von 0033 hat einen eigenen Bau ausserhalb des
Repos dagegen ausgeführt. Es hängt also am Modus des Laufs, nicht an der Sache.

**Die Bedingung bleibt inhaltlich unverändert** — ein Mitglied ohne Werkzeugkette muss
abbrechen, gemessen an einem Fall vor und nach der Änderung. Nur der Ort ist jetzt
gestaffelt, und der letzte Rang ist eine ausgewiesene Nichtmessung statt einer
Falschaussage:

1. Bevorzugt das Verzeichnis aus `$TMPDIR`. Es liegt ausserhalb des Repos und ist
   beschreibbar, wo `/tmp` es nicht ist.
2. Schlägt das fehl: ein Verzeichnis **unterhalb des Repos, aber ausserhalb jedes
   `file(GLOB …)`-Kastens und ausserhalb von `bau/`** — letzteres, weil `baulauf.py` dort
   nach `CMakeLists.txt` sucht und der Übersetzungsbericht sonst an deiner Wegwerfdatei
   hängt. Anlegen, messen, den Wortlaut beider Fehlermeldungen sofort notieren, löschen.
   **Den Nachweis zuerst aufschreiben, die Datei zuletzt anlegen.**
3. Schlägt auch das fehl: Bedingung 1 gilt als **ausgewiesen nicht gemessen**. Dann gehört
   in den Befund der Wortlaut der Ablehnung und die Begründung am CMake-Text, warum ein
   unbekannter Funktionsaufruf hart abbricht. Das ist kein Rücklaufgrund — eine
   Nichtmessung, die als solche dasteht, ist richtig; eine behauptete Messung wäre falsch.

Bedingungen 2 und 3 sind davon unberührt und bleiben wörtlich, wie sie stehen. Bedingung 2
ist die schärfere von beiden, weil sie den Bytevergleich der erzeugten `CXX_FLAGS`
verlangt und nicht „der Bau ist grün" — genau die Unterscheidung, an der dieses Paket
hängt.

---

## Nachweis, Lauf vom 2026-09-03 (Kernbauer)

Gebaut ist die Form, die der Vorschlag als tragfähig nennt: `werkzeugkette.cmake` stellt
`fabrik_warnsatz_anlegen(<ziel>)` bereit, die beiden vorhandenen `CMakeLists.txt` rufen
sie an sechs Stellen statt der bisherigen `target_compile_options`-Zeilen —
`kern`, `kern_geprueft`, jede Kernprobe; `pruefstand`, `pruefstand_geprueft`, jede
Prüfstandsprobe. Die Sanitizer-Zeilen sind unberührt (`PUBLIC`, eigene Sichtbarkeit).

Das Wegwerf-Verzeichnis lag in **Rang 1** der gestaffelten Ortsangabe: `$TMPDIR`
(`/tmp/claude-1000`), außerhalb des Repos. Kein Rückgriff auf Rang 2 oder 3 nötig.

### Bedingung 1 — ein Mitglied ohne Werkzeugkette bricht ab

Ein Mitglied `vergessen` unter `$TMPDIR/vergessenes-mitglied/`, gebaut wie
`pruefstand/CMakeLists.txt`, mit genau einem Unterschied: der `PROJECT_IS_TOP_LEVEL`-Block
fehlt. Eine Übersetzungseinheit `src/etwas.cpp` mit ungenutzter Variable — der Verstoß,
den der Warnsatz fangen muss und ohne ihn durchlässt.

**Gegenprobe, gemessen am Stand *vor* der Änderung** (Mitglied hängt den Satz selbst an):

```
cmake-Code: 0
build-Code: 0
[100%] Built target vergessen
CXX_FLAGS = -std=gnu++20
```

Grün, Code 0, und verloren waren nicht nur die 15 Warnschalter und die zwei
Überlaufschalter, sondern auch der **Sprachmodus**: `gnu++20` statt `c++20`, also genau
die Compiler-Erweiterungen, die ADR 0011 ausschließt (`CMAKE_CXX_EXTENSIONS OFF` steht
ebenfalls in `werkzeugkette.cmake`). Das ist eine Ecke der Lücke, die der Vorschlag noch
nicht kannte.

**Nach der Änderung**, dieselbe Datei mit dem Aufruf statt der Zeile:

```
cmake-Code: 1
-- Detecting CXX compile features - done
CMake Error at CMakeLists.txt:21 (fabrik_warnsatz_anlegen):
  Unknown CMake command "fabrik_warnsatz_anlegen".


-- Configuring incomplete, errors occurred!
```

Die nächste Zeile wird nicht mehr erreicht; ein Bau findet nicht statt.

**Positivkontrolle** — dasselbe Mitglied **mit** dem Block, damit der Abbruch nachweislich
an der fehlenden Einbindung hängt und nicht an etwas anderem:

```
cmake-Code: 0
CXX_FLAGS = -std=c++20 -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow
  -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
  -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2 -fwrapv
  -fno-fast-math
build-Code: 2
/tmp/claude-1000/erinnertes-mitglied/src/etwas.cpp:3:7: error: unused variable
  ‘ungenutzt’ [-Werror=unused-variable]
cc1plus: all warnings being treated as errors
```

Damit steht die Reihe vollständig da, und der mittlere Fall ist der, den es vorher nicht
gab:

| Fall | `cmake` | `cmake --build` | `CXX_FLAGS` |
|---|---|---|---|
| ohne Block, **vor** dieser Änderung | 0 | 0 — **grün** | `-std=gnu++20` |
| ohne Block, **nach** dieser Änderung | **1**, `Unknown CMake command` | nicht erreicht | — |
| mit Block, nach dieser Änderung | 0 | 2, `[-Werror=unused-variable]` | alle 17 |

Die dritte Zeile ist der Grund, warum die erste ein Befund ist: Derselbe Quelltext wird
rot, sobald die Schalter da sind. Ein grüner Bau belegt nichts über ihr Vorhandensein.

Beide Wegwerf-Verzeichnisse liegen außerhalb des Repos; im Baum ist keine Datei
liegengeblieben.

### Bedingung 2 — beide Kästen tragen unverändert alle 15 Schalter

Nicht drei Zeilen, sondern **alle** erzeugten `CXX_FLAGS`, zweimal erhoben und maschinell
verglichen.

*Erste Erhebung, blanke Konfiguration* (`cmake -S … -B …` ohne weitere Schalter), je ein
Baum vor und nach der Änderung, 28 Ziele über die drei geforderten Bauwege:

```
$ diff flags-vorher.txt flags-nachher.txt
$ echo $?
0
```

Kein Unterschied, in keiner der 28 Zeilen — und da die Zeilen ihren Pfad als Präfix
tragen, ist zugleich belegt, dass dieselbe Menge Ziele entsteht.

Die drei ausdrücklich verlangten Stellen im Wortlaut, alle drei identisch:

```
kern-allein/CMakeFiles/kern.dir/flags.make
pruefstand-allein/CMakeFiles/pruefstand.dir/flags.make
arbeitsbereich/pruefstand/CMakeFiles/pruefstand.dir/flags.make

CXX_FLAGS = -std=c++20 -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow
  -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
  -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2 -fwrapv
  -fno-fast-math
```

*Zweite Erhebung, Konfiguration des Runners* (`-DCMAKE_BUILD_TYPE=RelWithDebInfo
-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`, also die Zeile aus `baulauf.py`). Der
Vergleichsstand ist hier nicht ein zweiter Lauf, sondern der Baum aus `git show HEAD:` —
die drei geänderten Dateien im Stand vor diesem Lauf, der Rest unverändert:

```
Ziele HEAD: 30  Ziele jetzt: 30
nur im HEAD-Stand: []
nur im jetzigen  : []
ungleiche Zeilen : []
```

Beide Erhebungen zusammen: Die erzeugten Schalter sind bytegleich, blank wie unter der
Konfiguration, unter der der Nachtlauf tatsächlich übersetzt.

### Bedingung 3 — beide Kästen gebaut, alle Tests `Passed`

Die drei Befehle aus `baulauf.py` (`cmake -S`, `cmake --build --parallel`, `ctest`) mit
denselben Schaltern, über beide Wege gefahren:

| Weg | `cmake -S` | `cmake --build` | `ctest` | Tests |
|---|---|---|---|---|
| Arbeitsbereich | 0 | 0 | 0 | 11/11 `Passed` |
| `kern` allein | 0 | 0 | 0 | 8/8 `Passed` |
| `pruefstand` allein | 0 | 0 | 0 | 3/3 `Passed` |

**Die Testzahlen sind Stand 2026-09-03 nach diesem Lauf.** Der Übersetzungsbericht
desselben Tages nennt oben noch 10 Tests: Während des Tages ist eine Probe dazugekommen,
die nicht aus diesem Paket stammt. Der Bericht, an dem Bedingung 3 hängt, wird vom Runner
nach diesem Lauf neu geschrieben — die obige Messung ist derselbe Befehlssatz, von Hand
gefahren, nicht ein Ersatz dafür.

### Was der Prüfer nachfahren kann

Die Gegenprobe in einem Satz: ein Verzeichnis mit einer `CMakeLists.txt` anlegen, die
`fabrik_warnsatz_anlegen(<ziel>)` ruft, ohne `werkzeugkette.cmake` einzubinden. `cmake`
endet mit Code 1 und `Unknown CMake command`. Dieselbe Datei mit dem
`PROJECT_IS_TOP_LEVEL`-Block konfiguriert durch und wird an einer ungenutzten Variablen
rot.

Nicht angefasst, weil außerhalb dieses Pakets: `pruefstand/bau/pruefung-0019/CMakeLists.txt`
(Mutationsstand des Test-Prüfers) ist das vierte Manifest, das der Runner findet. Es setzt
seine Schalter selbst und rührt `FABRIK_STRENGE` nicht an — von dieser Änderung also
unberührt, geprüft.

---

## Abgenommen — 2026-09-03, Projektmanager: `gebaut` → `fertig`

Befund: `befunde/pruefung-0046-warnsatzriegel-fuer-kuenftige-mitglieder-2026-09-03.md`,
`urteil: geprueft`, `befunde: 0`, Rolle `kern-pruefer`.

**Die Staffelung des Nachweisorts hat getragen, und sie hat nichts gekostet.** Der
Bauagent kam mit Rang 1 aus (`$TMPDIR`), der Prüfer hat unabhängig davon Rang 2 benutzt
(`befunde/pruefung-0046/`, vom Baulauf nicht eingesammelt, `baulauf.py:116`) und kommt auf
dieselben Ergebnisse. Rang 3 — die ausgewiesene Nichtmessung — musste niemand in Anspruch
nehmen. Der Prüfer stellt ausdrücklich fest, dass die Berichtigung nur den Nachweis*ort*
verschoben und kein Kriterium gesenkt hat.

**Bedingung 2 ist zweimal unabhängig gemessen**, und die schärfere Messung war die, die
das Paket überhaupt erst rechtfertigt: Über alle 30 Ziele der drei Bauwege trägt jedes den
vollen Satz; der Bytevergleich zweier erzeugter `flags.make` (alte gegen neue Form) ist
über die ganze Datei identisch. Ein verkürzter Satz übersetzt grün — deshalb stand hier
der Vergleich und nicht „der Bau ist grün".

**Der zweite Riegel wurde mitgemessen, obwohl er in keiner Bedingung steht:** Die
Behauptung im Kommentar von `werkzeugkette.cmake`, ein bekannter Funktionsname genüge
nicht, weil `set()` gültigkeitsbereichsgebunden ist, ist damit keine Behauptung mehr.

Aus diesem Befund entsteht `0058-warnsatz-schlussriegel-alle-ziele`, mit diesem Lauf
`offen`. Er ist kein Rücklauf: Bedingung 1 verlangt wörtlich ein Mitglied **mit** dem
Aufruf, der Fall ohne Aufruf liegt eine Ebene darüber.
