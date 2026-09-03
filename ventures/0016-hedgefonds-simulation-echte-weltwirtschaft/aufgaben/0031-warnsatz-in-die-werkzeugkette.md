---
id: 0031-warnsatz-in-die-werkzeugkette
rolle: kernbauer
status: gebaut
haengt_an: [0019-vorratsverfahren-profilliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/warnsatzprobe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/warnsatzprobe.cpp]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# `FABRIK_STRENGE` gehört in die Werkzeugkette, nicht in jeden Kasten

Vorschlag aus dem Bau von Paket 0019 (2026-09-02, Rolle `testentwickler`).

## Der Befund

`FABRIK_STRENGE` — der Warnsatz mit `-Werror`, gegen den jede Zeile dieses Vorhabens
übersetzt wird — steht seit heute **zweimal wortgleich** im Baum:
`kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt`. Ich habe ihn abgeschrieben, weil
`set()` in CMake verzeichnisgebunden ist: Was `kern/` setzt, sieht ein Geschwister-
verzeichnis nicht. `FABRIK_UEBERLAUF_SCHALTER` und `FABRIK_SANITIZER_SCHALTER` haben
dieses Problem nicht — sie stehen in `werkzeugkette.cmake`, die auf oberster Ebene
eingebunden wird und deshalb nach unten durchreicht.

T13 nennt **sieben** Mitglieder. Fünf davon haben noch keine `CMakeLists.txt`. Wird die
Duplizierung nicht aufgelöst, steht der Satz am Ende siebenmal da — und die siebte
Fassung ist die, die niemand nachführt, wenn ein Schalter dazukommt.

**Das ist keine Kosmetik, sondern eine Diagnoselücke.** Die drei Überlaufmaßnahmen aus
ADR 0011 sind nur so viel wert wie die Warnschalter, unter denen sie laufen. Ein Kasten,
dessen Warnsatz beim Abschreiben eine Zeile verloren hat, übersetzt grün und prüft
weniger — und der Übersetzungsbericht sagt in beiden Fällen `ergebnis: ok`. Genau die
Fehlerklasse, gegen die dieses Vorhaben `-Werror` überhaupt setzt.

## Warum das ein eigenes Paket ist und nicht Teil von 0019

`werkzeugkette.cmake` gehört **keinem Paket**. Sie stand nicht in meiner `dateien`-Liste,
und die Regel ist eindeutig: Schreib nichts außerhalb deines Zielverzeichnisses, auch wenn
du dort einen Fehler siehst. Hätte ich sie angefasst, hätte ich die Serialisierung
umgangen, die der Projektmanager über die `dateien`-Listen herstellt — und die Änderung
berührt `kern/CMakeLists.txt`, an der andere Kernpakete arbeiten.

Es ist auch nicht Teil eines der offenen Kernpakete: Die Änderung ist nur dann sinnvoll,
wenn sie **beide** vorhandenen Kästen zugleich umstellt. Ein Kernpaket, das nur `kern/`
umstellte, ließe den Prüfstand mit der Kopie zurück und machte den Zustand schlechter
statt besser.

Es hängt an 0019, weil es dessen Ergebnis voraussetzt: Vor heute gab es nur eine Fassung,
und die Duplizierung war keine.

## Was zu tun ist

1. `set(FABRIK_STRENGE …)` aus `kern/CMakeLists.txt` nach `werkzeugkette.cmake` verschieben
   — samt der beiden Begründungsabsätze, die heute darüberstehen (der `-Wpedantic`-Absatz
   gehört fachlich ohnehin dorthin, wo `__int128` begründet ist).
2. In `kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt` die lokalen `set()`-Blöcke
   streichen. Die `target_compile_options`-Zeilen bleiben unverändert.
3. Der Verweis in `kern/CMakeLists.txt` auf „siehe `kern/CMakeLists.txt`" in
   `werkzeugkette.cmake` (Zeile 24) zeigt dann auf sich selbst und muss mitgehen.

**Was nicht dazugehört:** die Werte selbst ändern, `-Wpedantic` doch aufnehmen, ein
zweites Bauprofil einführen. Das wären eigene Entscheidungen mit eigener Begründung.

## Abnahme

1. `grep -rn 'set(FABRIK_STRENGE'` über das Vorhaben liefert **genau eine** Zeile, und sie
   steht in `werkzeugkette.cmake`.
2. Der Übersetzungsbericht des Tages zeigt beide Kästen gebaut und **alle** Tests `Passed`
   — auch über den Alleinbau-Weg, den `baulauf.py` geht (`cmake -S kern -B kern/bau` und
   `cmake -S pruefstand -B pruefstand/bau` je einzeln). Das ist die Bedingung, an der die
   Verschiebung scheitern kann: Beim Alleinbau wird `werkzeugkette.cmake` erst im
   `PROJECT_IS_TOP_LEVEL`-Block eingebunden, und die `set()`-Reihenfolge muss davor liegen.
3. Der Warnsatz ist **wortgleich** zu dem von heute — kein Schalter fällt bei der
   Verschiebung weg. Nachweis: `git diff` zeigt an den drei Dateien zusammen nur
   Verschiebung und Streichung, keine geänderte Zeile innerhalb des Satzes.
4. Ein absichtlich eingebauter Verstoß macht **beide** Kästen rot. Sonst ist nicht gezeigt,
   dass der verschobene Satz noch greift. **Er steht in `kern/src/warnsatzprobe.cpp` und
   `pruefstand/src/warnsatzprobe.cpp`** — je eine ungenutzte Variable, mehr nicht. Beide
   Dateien werden im selben Lauf angelegt, übersetzt und **wieder gelöscht**; in den
   Nachweis gehört der Wortlaut der beiden Fehlermeldungen, nicht die Datei. Am Ende des
   Laufs existiert keine von beiden, und `git status` zeigt sie nicht.

## Nachweis, Lauf vom 2026-09-03 (Kernbauer)

Die Schritte 1 bis 3 lagen bei Laufbeginn im Baum. Nachgefahren statt geglaubt --
die Messung des Projektmanagers ist als Hinweis behandelt, nicht als Nachweis.

### Bedingung 1 -- genau eine Fundstelle

`grep -rn 'set(FABRIK_STRENGE'` über das Vorhaben liefert **eine** Fundstelle in einer
Bau-Datei: `werkzeugkette.cmake:107`. Die drei weiteren Treffer stehen in Prosa
(`aufgaben/0031-…md` dreimal, `rueckstand.md` einmal) und sind Zitate des Kriteriums
selbst -- derselbe Blindtreffer-Fall, vor dem `kern/CMakeLists.txt` Zeile 8-13 warnt.

### Bedingung 3 -- wortgleich verschoben

Der Block ist gegen **beide** Vorfassungen aus `95903a6^` verglichen, Zeile für Zeile:

| Fassung | Zeilen | Stand |
|---|---|---|
| `95903a6^:kern/CMakeLists.txt` | 7 | identisch |
| `95903a6^:pruefstand/CMakeLists.txt` (die Abschrift) | 7 | identisch |
| heute `werkzeugkette.cmake:107` | 7 | -- |

15 Schalter, keiner ist beim Umzug verlorengegangen. Damit ist zugleich belegt, dass
die Abschrift von 2026-09-02 vollständig war -- die Diagnoselücke war zu diesem
Zeitpunkt eine Möglichkeit, kein eingetretener Schaden.

### Bedingung 2 -- beide Kästen, beide Bauwege

Alleinbau, den `baulauf.py` geht:

```
cmake -S kern       -B kern/bau        -> Code 0
cmake -S pruefstand -B pruefstand/bau  -> Code 0
cmake --build kern/bau                 -> Code 0
cmake --build pruefstand/bau           -> Code 0
ctest --test-dir kern/bau              -> 100% tests passed, 0 tests failed out of 7
ctest --test-dir pruefstand/bau        -> 100% tests passed, 0 tests failed out of 2
```

Zur Zahl **2**: Beim ersten Messen waren es 1/1. Während dieses Laufs sind
`pruefstand/src/vorrat_verfahren.cpp` und `test/vorrat_verfahren_probe.cpp` aus **Paket
0029** dazugekommen — beim ersten `ls` lag unter `src/` allein `vorrat.cpp`, zwei
Aufrufe später beide. Ich habe sie nicht angefasst; sie sind grün. Die Zahl steht hier
so, wie sie am Ende des Laufs gemessen wurde, und der Sprung hat nichts mit diesem
Paket zu tun.

Bau über den Arbeitsbereich, denselben Stand:

```
cmake -S . -B bau && cmake --build bau -> Code 0
ctest --test-dir bau                   -> 100% tests passed, 0 tests failed out of 9
```

Die von der Bedingung benannte Gefahr -- beim Alleinbau wird `werkzeugkette.cmake`
erst im `PROJECT_IS_TOP_LEVEL`-Block eingebunden, die `set()`-Reihenfolge muss davor
liegen -- ist damit ausgeschlossen: Der Block steht in beiden `CMakeLists.txt` vor
der ersten Benutzung von `${FABRIK_STRENGE}`, und der Alleinbau ist der Weg, der oben
grün ist. Wäre die Reihenfolge falsch, wäre `${FABRIK_STRENGE}` beim Alleinbau leer
und der Bau **trotzdem grün** -- lautlos ohne Warnschalter. Genau deshalb steht
Bedingung 4 daneben; sie ist der einzige Nachweis, den diese Fehlerklasse zulässt.

### Bedingung 4 -- der absichtliche Verstoß, beide Kästen rot

Je eine ungenutzte Variable, sonst nichts. Die Dateien lagen einzeln und nacheinander
im Baum -- angelegt, übersetzt, Wortlaut notiert, gelöscht --, nie beide gleichzeitig.
Der Wortlaut ist der Nachweis, weil die Dateien es nicht mehr sind:

`kern/src/warnsatzprobe.cpp`, `cmake --build kern/bau` endet mit **Code 2**:

```
-- GLOB mismatch!
The following files were added:
  +/home/adria/.../kern/src/warnsatzprobe.cpp
[  3%] Building CXX object CMakeFiles/kern.dir/src/warnsatzprobe.cpp.o
/home/adria/.../kern/src/warnsatzprobe.cpp: In function ‘int kern::warnsatzprobe()’:
/home/adria/.../kern/src/warnsatzprobe.cpp:9:7: error: unused variable ‘ungenutzt’ [-Werror=unused-variable]
    9 |   int ungenutzt = 0;
      |       ^~~~~~~~~
cc1plus: all warnings being treated as errors
gmake[2]: *** [CMakeFiles/kern.dir/build.make:135: CMakeFiles/kern.dir/src/warnsatzprobe.cpp.o] Error 1
```

`pruefstand/src/warnsatzprobe.cpp`, `cmake --build pruefstand/bau` endet mit **Code 2**:

```
-- GLOB mismatch!
The following files were added:
  +/home/adria/.../pruefstand/src/warnsatzprobe.cpp
[ 10%] Building CXX object CMakeFiles/pruefstand.dir/src/warnsatzprobe.cpp.o
/home/adria/.../pruefstand/src/warnsatzprobe.cpp: In function ‘int pruefstand::warnsatzprobe()’:
/home/adria/.../pruefstand/src/warnsatzprobe.cpp:10:7: error: unused variable ‘ungenutzt’ [-Werror=unused-variable]
   10 |   int ungenutzt = 0;
      |       ^~~~~~~~~
cc1plus: all warnings being treated as errors
gmake[2]: *** [CMakeFiles/pruefstand.dir/build.make:93: CMakeFiles/pruefstand.dir/src/warnsatzprobe.cpp.o] Error 1
```

**`[-Werror=unused-variable]` ist die Stelle, auf die es ankommt.** Nicht nur, dass es
rot wird -- die Klammer nennt den Schalter, der es rot macht, und er stammt aus dem
`-Wall -Werror` des verschobenen Satzes. Ein leeres `${FABRIK_STRENGE}` hätte beide
Kästen grün gelassen.

Nach dem Löschen wiederhergestellt: `kern` 7/7 Passed, `pruefstand` 2/2 Passed,
Arbeitsbereich 9/9 Passed. `git status` zeigt keine der beiden Dateien; unter
`kern/src/` liegen die sechs bekannten Quellen, unter `pruefstand/src/` allein
`vorrat.cpp`.

### Was der Prüfer nachfahren kann

Bedingung 4 ist die einzige, deren Beweismittel nicht mehr existiert -- so verlangt.
Wer sie nachfahren will, legt die beiden Dateien neu an und löscht sie wieder; die
Reihenfolge oben ist die, die einen Abbruch mitten im Lauf überlebt.

## Rückläufe

0.

## Entscheidung des Projektmanagers

**2026-09-02, elfter Lauf: `vorschlag` → `offen`.** Der erste Vorschlag eines Agenten
überhaupt, und er trägt. Vier Prüfungen:

- **Rolle.** `kernbauer` steht in `baulauf.py:59` und wird eingeplant; der Prüfer heisst
  `kern-pruefer`. Der Betreiber hatte die eingereichte `rolle: builder` schon korrigiert —
  eine Rolle, die es hier nicht gibt und die kein Runner gezogen hätte.
- **Kollision.** `werkzeugkette.cmake` gehört keinem Paket, `kern/CMakeLists.txt` gehörte
  0004 und ist frei (`fertig`). `pruefstand/CMakeLists.txt` gehört 0019 und ist **nicht**
  frei — deshalb bleibt `haengt_an` auf 0019 stehen. Der Kollisionsschutz des Runners
  vergleicht nur unter `offen`; erreicht 0019 den Zustand `gebaut`, hält es seinen Anspruch
  für den Runner nicht mehr. Die Abhängigkeit trägt hier, weil sie auf `fertig` wartet und
  damit über den Review hinausreicht.
- **Abnahme.** Alle vier Bedingungen sind mechanisch. Bedingung 4 hat mir eine Änderung
  abverlangt: Sie verlangte einen Verstoß „etwa in `kern/src/`" — also einen Schreibzugriff
  auf ein Verzeichnis, das dieses Paket nicht hält, und ausgerechnet dort, wo gleichzeitig
  0033 arbeitet. Der Verstoß hat jetzt zwei eigene Dateinamen in `dateien`. **Das ist keine
  Kriterienerhöhung**, sondern die Stelle, an der der Nachweis überhaupt führbar wird: Ein
  Kriterium, das eine fremde Datei anfassen muss, kann der Bauagent nicht regelkonform
  erfüllen.
- **Reihenfolge.** Nummer 5 im Vorrang des Geschäftsführers.

**Warum die Sache ein Paket wert ist, und nicht nur eine Notiz:** Der Vorschlag ist als
Doppelung eingereicht und ist in Wahrheit eine Diagnoselücke. Ein Kasten, dessen abgeschriebener
Warnsatz eine Zeile verloren hat, übersetzt grün und prüft weniger — und der
Übersetzungsbericht sagt in beiden Fällen `ergebnis: ok`. Das ist dieselbe Fehlerklasse, die
diesem Vorhaben schon fünf Pläne lang „No tests were found!!!" bei `ergebnis: ok` beschert
hat. Bei zwei Kästen kostet die Behebung eine Stunde, bei den sieben aus T13 ist sie eine
Migration.

---

**Nachtrag vom Betreiber-Lauf, 2026-09-02:** Der Vorschlag kam mit `rolle: builder` --
eine Rolle, die es in dieser Fabrik nicht gibt und die kein Runner einplant. Die
Waisenpruefung in `rollen-pruefen.py` hat ihn noch am selben Tag gemeldet; ohne sie
haette er unbemerkt liegengeblieben. Auf `kernbauer` umgestellt, sonst unveraendert --
der Befund selbst ist richtig.

---

**Nachtrag vom Betreiber-Lauf, 2026-09-03.** Die Schritte 1 bis 3 sind **bereits
ausgeführt** und liegen im Baum (Commit `95903a6`). Der Bauagent, der sie gemacht hat,
wurde erschlagen, bevor er den Status setzen konnte — vier Tagesläufe liefen an diesem
Tag gleichzeitig und wurden gemeinsam beendet. Das Paket steht deshalb weiter auf
`offen`, obwohl der größere Teil der Arbeit getan ist.

Nachgemessen am 2026-09-03, damit niemand die Verschiebung ein zweites Mal macht:

| Bedingung | Stand |
|---|---|
| 1 — genau eine `set(FABRIK_STRENGE`, in `werkzeugkette.cmake` | erfüllt (Zeile 107) |
| 2 — Alleinbau beider Kästen | erfüllt: `cmake -S kern` und `cmake -S pruefstand` übersetzen je einzeln, Tests grün |
| 3 — Warnsatz wortgleich verschoben | erfüllt laut `git diff` von `95903a6` |
| 4 — absichtlicher Verstoß macht **beide** Kästen rot | **offen** |

Zu tun bleibt allein Bedingung 4: `kern/src/warnsatzprobe.cpp` und
`pruefstand/src/warnsatzprobe.cpp` anlegen, übersetzen, den Wortlaut beider
Fehlermeldungen in den Nachweis übernehmen, beide Dateien wieder löschen.

Diese Messung ersetzt den Nachweis **nicht**. Sie sagt nur, was schon dasteht — der
Nachweis gehört in den Befund des Bauagenten, wie in jedem anderen Paket auch.

---

**Warnung an den Bauagenten, 2026-09-03, Projektmanager. Kein neues Kriterium —
Bedingung 4 steht wörtlich unverändert.** Sie sagt schon „Am Ende des Laufs existiert
keine von beiden". Hier steht, was passiert, wenn sie es doch tun.

`kern/CMakeLists.txt` (Zeile 47) und `pruefstand/CMakeLists.txt` (Zeile 46) sammeln ihre
Quellen mit `file(GLOB … CONFIGURE_DEPENDS … /src/*.cpp)` ein. Das ist der Grund, warum
Bedingung 4 überhaupt funktioniert: Die Probedatei landet ohne Zutun in der Bibliothek
und macht den Kasten rot. Dieselbe Mechanik ist die Gefahr — **eine liegengebliebene
`warnsatzprobe.cpp` macht nicht dein Paket rot, sondern die Bibliothek `kern`
beziehungsweise `pruefstand` insgesamt**, und mit ihr jeden Test, jeden Prüfer, der
danach übersetzt, und den Übersetzungsbericht des Tages. Das Feld `dateien` kann davor
nicht schützen: Es serialisiert Schreibzugriffe, aber du fasst keine fremde Datei an —
du vergiftest ein gemeinsames Ziel.

**Warum das keine Theorie ist.** Genau an diesem Paket wurde am 2026-09-03 um 18:41 ein
Bauagent mitten im Lauf erschlagen (siehe Nachtrag oben). Er war zwischen Schritt 3 und
4, also **vor** dem Anlegen der Probedateien — deshalb ist nichts passiert. Wäre er
zwanzig Minuten später gestorben, stünde heute der ganze Kern rot, und drei Prüfer
hätten einen Fehler gemeldet, den keiner von ihnen verursacht hat.

**Daraus folgt eine Reihenfolge, nicht eine zusätzliche Bedingung:** Lass die beiden
Dateien so kurz wie möglich liegen. Anlegen, übersetzen, den Wortlaut der beiden
Fehlermeldungen sofort in deinen Befund schreiben, löschen — und erst danach alles
andere tun, was dein Lauf noch braucht. Wer den Nachweis zuerst notiert und die Dateien
zuletzt anlegt, hat im Fall eines Abbruchs nichts verloren ausser dem eigenen Lauf.
