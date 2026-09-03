---
id: 0045-warnsatzriegel-fuer-kuenftige-mitglieder
rolle: kernbauer
status: vorschlag
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
