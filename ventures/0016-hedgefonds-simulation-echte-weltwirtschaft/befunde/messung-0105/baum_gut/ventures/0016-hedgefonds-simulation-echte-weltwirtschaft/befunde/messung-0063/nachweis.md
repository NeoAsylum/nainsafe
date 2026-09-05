---
typ: nachweis
paket: 0063-sperrliste-je-wort-statt-je-eintrag
rolle: kernbauer
datum: 2026-09-04
---

# Nachweis zu Paket 0063

Werkzeugkette: g++ 15.2.0, cmake 4.2.3. Konfiguriert wurde durchgehend mit der Zeile
des Runners (`agents/baulauf.py:162-164`), also
`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`.

**Nachweisort:** Rang 2 der Staffelung. Rang 1 (`$TMPDIR`) hat in diesem Lauf nicht
getragen -- ein `mkdir` nach `/tmp/claude-1000` lief, jeder Dateischreibzugriff dorthin
wurde verweigert. Gemessen wird deshalb unterhalb von `befunde/`, das `baulauf.py:116`
von der Manifestsuche ausnimmt.

## Was geaendert wurde

Genau eine Stelle: der **zweite** Durchgang von `fabrik_schlussriegel` in
`werkzeugkette.cmake`. Er hielt jeden Eintrag von `COMPILE_OPTIONS` als ganze
Zeichenkette gegen die Sperrliste; jetzt zerlegt er den Eintrag zuvor in Woerter
(Trenner `SHELL:` und die Zeichen `$ < > : ,`) und haelt jedes Wort gegen dieselbe,
unveraenderte Sperrliste. Der erste Durchgang (`luecke`) ist unberuehrt.

Dazu eine Zeile im Meldungstext: Weil jetzt ein **Wort** genannt wird, steht der
Eintrag daneben, aus dem es stammt -- aber nur, wenn er sich vom Wort unterscheidet.
Fuer die Form aus 0060 (`-Wno-error -w` als zwei Eintraege) ist die Meldung damit
unveraendert; fuer `SHELL:` und die Generatorausdruecke nennt sie zusaetzlich die
Zeile, die im Manifest zu suchen ist.

## Wie gemessen wurde

`fahre.py` faehrt sechs Wegwerf-Baeume, jeder mit eigener `CMakeLists.txt`, gegen
**eine** Fassung der Kette (`-DFABRIK_KETTE=...`). Jeder Baum: `add_library(z STATIC
../z.cpp)`, `fabrik_warnsatz_anlegen(z)`, danach die eine zu pruefende Zeile. `z.cpp`
ist die Quelle aus Befund 3 von 0060, `int f(double d){ int i = d; return i; }` --
eine Verengung, die `-Werror=float-conversion` ausloest, solange der Satz wirkt.

Die `vorher`-Reihe lief gegen `kette-vorher.cmake`, einen Schnappschuss der Datei vor
der Aenderung (md5 `f8eb2437bef9cc8189923836b29d070b`, gegen den damaligen Repo-Stand
abgeglichen). Die `endstand`-Reihe lief gegen die Datei auf der Platte nach der letzten
Aenderung. Die Zwischenreihe `nachher` steht mit dabei; sie unterscheidet sich vom
Endstand nur um eine Leerzeile im Kommentar und ist in jedem Ergebnis gleich.

`bauwege.py` faehrt die drei echten Bauwege -- dort wird die Kette **nicht**
untergeschoben, sondern von den Baeumen selbst eingebunden, weil genau dieser Weg
gemessen werden soll.

## Bedingung 1 -- `SHELL:` wird gefangen

`target_compile_options(z PRIVATE "SHELL:-Wno-error -w")`

| | `cmake -S` | `cmake --build` |
|---|---|---|
| **vorher** | CODE=0, `-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.` | CODE=0, Ausgabe nur `[100%] Built target z` -- keine Diagnose |
| **endstand** | **CODE=1** | kein Bau, die Konfiguration bricht ab |

Der Meldungstext im Endstand, im Wortlaut aus `protokoll-faelle-endstand.md:18-23`:

```
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in .../befunde/messung-0063/a_shell
        hebt den Satz wieder auf: -Wno-error -w
        im Eintrag:               SHELL:-Wno-error -w
```

Die Gegenprobe traegt die Aussage: Vorher meldete der Riegel wortgleich Vollzug **und**
der Bau lief still durch -- der Abschalter war also wirklich beim Uebersetzer
angekommen und nicht bloss unbemerkt geblieben.

## Bedingung 2 -- der Generatorausdruck ebenso

| Eintrag | vorher | endstand | gemeldetes Wort / gemeldeter Eintrag |
|---|---|---|---|
| `"$<1:-w>"` | CODE=0 | **CODE=1** | `-w` / `$<1:-w>` |
| `"$<$<CONFIG:Release>:-w>"` | CODE=0 | **CODE=1** | `-w` / `$<$<CONFIG:Release>:-w>` |

`$<1:-w>` ist in jeder Konfiguration wirksam: vorher `cmake --build` CODE=0, Ausgabe
nur `[100%] Built target z`, keine Diagnose.

`$<$<CONFIG:Release>:-w>` wirkt nur unter `Release`. Unter der Zeile des Runners
(`RelWithDebInfo`) bekommt der Uebersetzer den Schalter gar nicht -- der Riegel sah ihn
vorher trotzdem nicht, weil er die Zeichenkette prueft und nicht die Wirkung. Der
stille Bau ist deshalb getrennt unter `-DCMAKE_BUILD_TYPE=Release` gemessen: vorher
`cmake -S` CODE=0 und `cmake --build` CODE=0 ohne Diagnose, im Endstand `cmake -S`
CODE=1. Beide Profile stehen in den Protokollen als Fall 3 und Fall 4.

## Bedingung 3 -- nichts wird ueber-scharf

**Die Form aus 0060** (`-Wno-error -w` als zwei Eintraege): vorher CODE=1, im Endstand
CODE=1, und die Meldung ist unveraendert `hebt den Satz wieder auf: -Wno-error -w`
**ohne** die Zeile `im Eintrag:` -- Wort und Eintrag sind hier dasselbe.

**`-Wno-conversion`** an einem Ziel mit Satz: vorher `cmake -S` CODE=0 und
`cmake --build` CODE=0, im Endstand ebenso CODE=0 / CODE=0. Einzeln unterdruecken
bleibt zugelassen.

**Positivkontrolle** (`f_ohne`, gar kein zusaetzlicher Schalter): vorher wie im
Endstand `cmake -S` CODE=0 und `cmake --build` **CODE=2** mit
`error: conversion from 'double' to 'int' may change value [-Werror=float-conversion]`
im Wortlaut. Ohne diese Zeile belegten die stillen Bauten oben nur, dass irgendetwas
nicht gewarnt hat.

**Die drei Bauwege**, je `cmake -S`, `cmake --build --parallel`, `ctest`:

| Bauweg | vorher | endstand | Riegelzahl |
|---|---|---|---|
| Arbeitsbereich | 0 / 0 / 0 | 0 / 0 / 0 | **15** |
| `kern` allein | 0 / 0 / 0 | 0 / 0 / 0 | **10** |
| `pruefstand` allein | 0 / 0 / 0 | 0 / 0 / 0 | **5** |

15 / 10 / 5, unveraendert gegen den Stand vom 2026-09-04. Die Zahl des Arbeitsbereichs
ist hier **genau** die Summe der beiden anderen, die Differenz ist null: Von den sieben
Namen in `FABRIK_MITGLIEDER` (`CMakeLists.txt:36-43`) existieren nur `kern` und
`pruefstand`; die fuenf uebrigen -- `daten`, `schnittstelle`, `konsole`, `oberflaeche`,
`werkzeuge/aufbereitung` -- meldet der Arbeitsbereich als `noch nicht gebaut --
uebersprungen`. Es gibt also kein Mitglied, das eine Differenz truege.

`ctest` lief in allen drei Wegen gruen: 11 von 11, 8 von 8, 3 von 3 bestanden, kein
Ausfall. Die Wortlaute stehen in `protokoll-bauwege-endstand.md`.

**Bytevergleich der `CXX_FLAGS`.** Jede `CXX_FLAGS`-Zeile jeder erzeugten `flags.make`
des Arbeitsbereichs, mit dem relativen Pfad als Praefix, sortiert, Bauwurzel textlich
auf `<BAU>` normalisiert:

```
cxxflags-vorher.txt    5849 Bytes, 15 Zeilen, sha256 5aab4974ebc99d641fba2281233ce037c169ebc994419c0b941fd7c62401f2a4
cxxflags-nachher.txt   5849 Bytes, 15 Zeilen, sha256 5aab4974...2401f2a4
cxxflags-endstand.txt  5849 Bytes, 15 Zeilen, sha256 5aab4974...2401f2a4
```

Bytegleich. 15 Zeilen auf beiden Seiten -- derselbe Vergleich belegt damit zugleich
dieselbe Menge uebersetzender Ziele und deckt sich mit der Riegelzahl 15.

## Was hier nicht gemessen ist

- **`werkzeuge/belegstellen`**, das fuenfte Manifest im Uebersetzungsbericht vom
  2026-09-04, bindet `werkzeugkette.cmake` nicht ein (`grep` auf beide Manifeste) und
  hat kein uebersetzendes Ziel. Die Aenderung kann es nicht erreichen. Es gehoert zu
  Paket 0059 und wurde nicht angefasst.
- **`CMAKE_CXX_FLAGS` von aussen** und **die Kommandozeile** als Weg fuer einen
  Pauschalabschalter. Beide stehen im Paket ausdruecklich ausserhalb des Umfangs; sie
  bleiben offene Grenzen des Riegels.
- **Der erste Durchgang (`luecke`)** gegen Generatorausdruecke. Ebenfalls ausserhalb des
  Umfangs, mit Begruendung im Quelltext an der Stelle selbst.

## Wie ein Pruefer das nachfaehrt

```
python3 befunde/messung-0063/fahre.py befunde/messung-0063/kette-vorher.cmake vorher
python3 befunde/messung-0063/fahre.py werkzeugkette.cmake endstand
python3 befunde/messung-0063/bauwege.py endstand
```

Die Bauverzeichnisse, die dabei entstehen, sind nach der Messung entfernt (70 MB); die
Protokolle, die Manifeste der sechs Faelle, `z.cpp`, der Schnappschuss der alten Kette
und die beiden Treiber liegen hier.
