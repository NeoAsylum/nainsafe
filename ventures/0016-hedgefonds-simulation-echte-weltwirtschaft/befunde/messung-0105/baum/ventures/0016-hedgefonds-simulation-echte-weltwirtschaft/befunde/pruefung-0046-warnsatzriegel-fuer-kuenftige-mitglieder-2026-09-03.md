---
typ: pruefung
paket: 0046-warnsatzriegel-fuer-kuenftige-mitglieder
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln nachgefahren -- Bedingung 1 an vier eigenen Wegwerf-Mitgliedern (ohne Block in alter und in neuer Form, mit Block, enger Gueltigkeitsbereich), Bedingung 2 als Bytevergleich zweier erzeugter flags.make und als Vollzaehlung aller 30 Ziele auf allen drei Bauwegen, Bedingung 3 durch eigenen Bau und Testlauf ausserhalb des Repos.
befunde: 0
---

# Der Riegel haelt, und er haelt aus dem Grund, aus dem er gebaut wurde

Geprueft wurden `werkzeugkette.cmake`, `kern/CMakeLists.txt` und
`pruefstand/CMakeLists.txt` im Stand vom 2026-09-03 gegen die drei Bedingungen im
Abschnitt "Abnahme" des Pakets, samt der Berichtigung des Projektmanagers zu Bedingung 1.

Nicht gelesen habe ich das Logbuch des Bauagenten. Gelesen habe ich die Aenderung als
Diff, die drei Dateien im Ganzen, `CMakeLists.txt` des Arbeitsbereichs und
`agents/baulauf.py` (fuer die Aufrufe, gegen die ich gemessen habe).

Werkzeuglage dieses Laufs: `cmake` 4.2.3, `g++` 15.2.0 -- gleich der in
`werkzeugkette.cmake` als geprueft festgenagelten `FABRIK_UEBERSETZER_GEPRUEFT 15.2.0`,
die Versionswarnung greift also nicht und verfaelscht keine Messung.

## Bedingung 1 -- ein Mitglied ohne Werkzeugkette bricht ab

Nachgefahren an vier eigenen Wegwerf-Mitgliedern. Sie liegen unter
`befunde/pruefung-0046/`; die Bauverzeichnisse lagen ausserhalb des Repos in `$TMPDIR`.
Der Ort ist Rang 2 der Staffelung aus der Berichtigung, und er ist hier ungefaehrlich:
`baulauf.py` sammelt jede `CMakeLists.txt` unter dem Vorhaben ein **ausser** denen, deren
Pfad `befunde` enthaelt (`baulauf.py:116`). Der Uebersetzungsbericht desselben Tages
belegt das mit `manifeste: 4`, obwohl `befunde/pruefung-0029/CMakeLists.txt` schon
vorher dort lag. Alle vier Mitglieder uebersetzen dieselbe Datei mit einer ungenutzten
Variablen -- der Verstoss, den der Warnsatz fangen muss und ohne den er ihn durchlaesst.

Alle vier mit den Schaltern des Runners konfiguriert
(`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`):

| Mitglied | Fassung | `cmake` | `cmake --build` | `CXX_FLAGS` |
|---|---|---|---|---|
| `vergessen-alte-form` | ohne Block, Stand **vor** 0046 | 0 | 0 -- **gruen** | `-fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=gnu++20` |
| `vergessenes-mitglied` | ohne Block, Stand **nach** 0046 | **1** | nicht erreicht | -- |
| `erinnertes-mitglied` | mit Block, Stand nach 0046 | 0 | **2** | alle 17 Schalter, `-std=c++20` |
| `enger-gueltigkeitsbereich` | Einbindung im engeren Bereich | **1** | nicht erreicht | -- |

Der Wortlaut des Abbruchs in Zeile 2 der Tabelle:

```
CMake Error at CMakeLists.txt:16 (fabrik_warnsatz_anlegen):
  Unknown CMake command "fabrik_warnsatz_anlegen".

-- Configuring incomplete, errors occurred!
```

Hinter dem Aufruf steht in dieser Datei ein `message(STATUS "PRUEFER: diese Zeile darf
nicht erscheinen")`. Sie erscheint nicht. Der Abbruch ist also hart und nicht eine
Meldung, ueber die die Konfiguration hinweglaeuft.

**Die Gegenprobe ist die wichtigere Haelfte**, und sie ist am Stand *vor* der Aenderung
gemessen: Dieselbe Datei, die den Satz in der alten Form selbst anhaengt
(`target_compile_options(x PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})`),
laeuft ohne Werkzeugkette **fehlerfrei durch und baut gruen**. Blank konfiguriert, ohne
die Schalter des Runners, bleibt von der Zeile ueberhaupt nichts uebrig:

```
CXX_FLAGS = -std=gnu++20
```

Damit ist der Befund, gegen den das Paket geschrieben wurde, unabhaengig bestaetigt:
Verloren sind nicht nur die 15 Warnschalter, sondern auch der Sprachmodus -- `gnu++20`
statt des von ADR 0011 vorgeschriebenen `c++20`. Die beiden Ueberlaufschalter ueberleben
nur deshalb, weil `baulauf.py` sie zusaetzlich von aussen setzt; wer nicht ueber den
Runner uebersetzt, verliert auch `-fwrapv`. Das ist die Determinismusfrage meiner Rolle,
und dieses Paket beantwortet sie zugunsten des Determinismus.

**Die Positivkontrolle** zeigt, dass der Abbruch an der fehlenden Einbindung haengt und
an nichts anderem: dieselbe Datei mit dem `PROJECT_IS_TOP_LEVEL`-Block konfiguriert
durch, traegt alle 17 Schalter -- und derselbe Quelltext wird dann rot:

```
error: unused variable 'ungenutzt' [-Werror=unused-variable]
cc1plus: all warnings being treated as errors
```

Ein gruener Bau belegt also nichts ueber das Vorhandensein der Schalter, ein roter
schon. Genau deshalb steht der Bytevergleich in Bedingung 2 und nicht "der Bau ist gruen".

**Der zweite Riegel wurde ebenfalls gemessen**, obwohl er in keiner Abnahmebedingung
steht. `werkzeugkette.cmake` behauptet in seinem Kommentar, der Aufruf allein reiche
nicht: CMake-Funktionen sind global, `set()` ist gueltigkeitsbereichsgebunden, also kann
die Funktion bekannt und der Satz trotzdem leer sein. Hergestellt mit einer Einbindung
in einem `block()` und dem Aufruf davor:

```
CMake Error at werkzeugkette.cmake:159 (message):
  fabrik_warnsatz_anlegen('enge'): `FABRIK_STRENGE` ist hier leer. Ein leerer
  Warnsatz uebersetzt gruen und prueft nichts -- das ist kein Bauzustand,
  sondern ein Fehler.
```

Die Behauptung im Kommentar ist damit keine Behauptung mehr. Der dritte Riegel
(`if(NOT TARGET ...)`) wurde im Skriptmodus ausgeloest und meldet
`kein solches Ziel`.

## Bedingung 2 -- beide Kaesten tragen unveraendert alle 15 Schalter

Zwei voneinander unabhaengige Messungen.

**Erstens die Vollzaehlung.** Drei Bauwege gegen die echten Quellen konfiguriert --
Arbeitsbereich, `kern` allein, `pruefstand` allein --, zusammen **30 Ziele**. Ueber alle
30 erzeugten `flags.make` gibt es genau **zwei** verschiedene `CXX_FLAGS`-Zeilen: die
Sanitizer-Ziele und die uebrigen. Alle 30 enthalten die Zeichenkette

```
-std=c++20 -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow
-Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
-Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2
-fwrapv -fno-fast-math
```

zusammenhaengend und in dieser Reihenfolge; die drei ausdruecklich verlangten Stellen
(`kern` allein, `pruefstand` allein, `pruefstand` im Arbeitsbereich) sind darunter. Kein
Ziel hat einen verkuerzten Satz -- das ist die Prueffrage, denn ein verkuerzter Satz ist
der Fehler, der gruen uebersetzt.

Gegengezaehlt am Ursprung, nicht am Ergebnis: `FABRIK_STRENGE` hat im Skriptmodus die
Laenge **15**, `FABRIK_UEBERLAUF_SCHALTER` die Laenge **2**.

**Zweitens der Bytevergleich alte gegen neue Fassung.** Zwei Wegwerf-Mitglieder, die
sich in genau einer Zeile unterscheiden -- einmal `fabrik_warnsatz_anlegen(erinnert)`,
einmal die alte `target_compile_options`-Zeile --, gleicher Zielname, gleiche
Quelldatei, gleiche Konfiguration:

```
$ diff bau-erinnert/CMakeFiles/erinnert.dir/flags.make \
       bau-erinnert-alt/CMakeFiles/erinnert.dir/flags.make
$ echo $?
0
```

Kein Unterschied, nicht nur in der `CXX_FLAGS`-Zeile, sondern in der ganzen Datei. Damit
ist "unveraendert" gemessen und nicht aus dem Diff geschlossen.

Dazu passt der Diff selbst, den ich getrennt gelesen habe: `werkzeugkette.cmake` ist
**rein additiv** (59 Zeilen angehaengt, keine bestehende Zeile geaendert oder entfernt),
`FABRIK_STRENGE` und `FABRIK_UEBERLAUF_SCHALTER` sind unberuehrt, und die sechs Stellen
in den beiden `CMakeLists.txt` sind eins zu eins ersetzt --
`target_compile_options(<ziel> PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})`
wird zu `fabrik_warnsatz_anlegen(<ziel>)`, und die letzte Zeile der Funktion ist
zeichenweise die ersetzte Zeile mit `${ziel}` an der Stelle des Namens. Die
Sanitizer-Zeilen (`PUBLIC`) sind nicht angefasst, das Bauprofil ist nicht angefasst,
`-Wpedantic` ist nicht dazugekommen. Das ist genau der Zuschnitt, den der Abschnitt
"Was nicht dazugehoert" verlangt.

## Bedingung 3 -- beide Kaesten gebaut, alle Tests `Passed`

`befunde/uebersetzung-2026-09-03.md` steht auf `ergebnis: ok` und zeigt beide Wege:
Arbeitsbereich 11/11 `Passed`, `kern` allein 8/8, `pruefstand` allein 3/3, dazu das
vierte Manifest des Test-Pruefers mit 11/11. Der Bericht ist um 22:04:51 geschrieben,
die Aenderung liegt bei 21:07 -- er misst also den Stand nach diesem Lauf und nicht
davor.

Weil ein fremdgemessener Bericht kein Ersatz fuer eine eigene Messung ist, habe ich den
Arbeitsbereich selbst gebaut, ausserhalb des Repos, mit denselben drei Aufrufen:
`cmake -S` Code 0, `cmake --build --parallel` Code 0, `ctest` **11/11 Passed**.

## Die vier Fragen meiner Rolle an diesem Paket

Dieses Paket enthaelt keine Zustandsfortschreibung, keine Rueckkopplung und keine
Rechnung -- es ist Bauwerkzeug. Zwei der vier Fragen sind hier deshalb gegenstandslos,
und das schreibe ich hin, statt sie mit einem Satz abzuhaken:

1. **Determinismus** -- betroffen, und das ist der Punkt des Pakets. Determinismus haengt
   in diesem Kern an drei Schaltern, die still verschwinden koennen: `-fwrapv`
   (ADR 0011, Massnahme 1), `-fno-fast-math` und `-std=c++20` ohne GNU-Erweiterungen.
   Gemessen: alle drei erreichen alle 30 Ziele auf allen drei Bauwegen; ein Mitglied, das
   die Form abschreibt und die Einbindung verliert, bekommt sie seit dieser Aenderung
   nicht mehr lautlos aberkannt, sondern bricht ab. Kein Gleitkomma, keine ungeordnete
   Menge, kein Zufallsstrom in der Aenderung -- sie fuegt CMake-Code hinzu und keine
   Zeile C++.
2. **Rueckkopplungen** -- gegenstandslos.
3. **Zustandsausgabe** -- gegenstandslos fuer die Simulation. Die Ausgabe, um die es hier
   geht, ist der Uebersetzungsbericht, und die Aenderung macht ihn schaerfer: Der Fall
   "gebaut, aber ohne Pruefung" kann fuer ein Mitglied, das die Form benutzt, nicht mehr
   als `ergebnis: ok` erscheinen.
4. **Raender** -- keine Arithmetik. Gepruefte Randfaelle stattdessen an der Funktion:
   Ziel existiert nicht (Abbruch, gemessen), `FABRIK_STRENGE` im Bereich nicht sichtbar
   (Abbruch, gemessen), Funktion nicht bekannt (Abbruch, gemessen).

## Wonach ich gesucht und nichts gefunden habe

- **Ein Ziel ohne den vollen Satz.** Alle 30 gezaehlt, zwei verschiedene Zeilen, beide
  vollstaendig. Nicht gefunden.
- **Eine Reihenfolgeaenderung bei den Sanitizer-Zielen.** `fabrik_warnsatz_anlegen`
  steht vor der `PUBLIC`-Zeile, so wie die ersetzte Zeile davor stand; die erzeugte
  Reihenfolge ist `... -Wformat=2 -fwrapv -fno-fast-math -fsanitize=... `. Unveraendert.
- **Eine liegengebliebene Datei des Bauagenten.** `git status` ueber das Vorhaben nennt
  ausser dem Uebersetzungsbericht des Runners nichts; unter dem Vorhaben ist seit 20:00
  keine `CMakeLists.txt` dazugekommen ausser den beiden geaenderten.
- **Ein gesenktes Abnahmekriterium.** Die Berichtigung des Projektmanagers verschiebt nur
  den Nachweis*ort* von Bedingung 1 und laesst Bedingung 2 und 3 woertlich stehen. Der
  Bauagent hat Rang 1 der Staffelung benutzt und musste die Lockerung nicht in Anspruch
  nehmen; ich habe Rang 2 benutzt und komme auf dieselben Ergebnisse.
- **Eine Abweichung von der `dateien`-Liste.** Geaendert sind genau die drei genannten
  Dateien plus die Paketdatei selbst. Keine vierte.

## Anmerkungen (kein Ruecklaufgrund)

**Der Commit-Betreff nennt wieder ein anderes Paket.** Die drei Dateien dieses Pakets
liegen in `f68e8fb` mit dem Betreff *"datenbauer: 0042-parameterdatei-indexbegruendung
(22 Dateien)"*; der Nachweisabschnitt der Paketdatei kam in `0149679` *"testentwickler:
0040-kernanker-klassenzuteilung"*. Der Commit `63d3a81` *"kernbauer:
0046-warnsatzriegel-fuer-kuenftige-mitglieder"* enthaelt **eine** Datei, und das ist das
Logbuch des Bauagenten. Das ist keine Nachlaessigkeit des Bauagenten, sondern die
bekannte Mechanik des Runners (Lehren, 2026-09-03: es werden ganze Verzeichnisse
committet, der Betreff kommt aus dem Lauf). Wer diese Aenderung spaeter sucht, findet
sie ueber den Betreff nicht -- deshalb steht der Hash hier.

**Der Riegel bindet den Aufruf, nicht das Mitglied.** Er faengt das Mitglied, das die
Form abschreibt und den Einbindungsblock verliert -- das ist Bedingung 1, und sie ist
erfuellt. Er faengt **nicht** das Mitglied, das `fabrik_warnsatz_anlegen` gar nicht erst
ruft. Das ist keine Verletzung der Abnahme, sondern eine Ebene darueber; dafuer liegt ein
eigener Vorschlag als `aufgaben/0058-warnsatz-schlussriegel-alle-ziele.md` bei. Seine
Bauform habe ich einmal gebaut und laufen lassen, damit der Projektmanager nicht raten
muss, ob sie traegt.

**Zur Nummer:** Ich hatte den Vorschlag zuerst als 0056 angelegt und noch im selben Lauf
auf 0058 umnummeriert -- waehrend ich schrieb, haben zwei gleichzeitige Laeufe 0056 und
0057 belegt. Die Datei unter dem alten Namen steht auf `status: archiviert` und verweist
auf die neue; loeschen laesst Hausregel 3 sie nicht.

## Die Wegwerf-Mitglieder

Sie liegen unter `befunde/pruefung-0046/` und werden vom Baulauf nicht angefasst. Sie
bleiben liegen, weil Hausregel 3 nichts loeschen laesst -- und weil jede Zeile dieser
Pruefung damit ohne Zusatzarbeit nachgefahren werden kann:

- `vergessenes-mitglied/` -- ohne Block, neue Form. Erwartet: `cmake` Code 1.
- `vergessen-alte-form/` -- ohne Block, alte Form. Erwartet: Code 0 und gruener Bau.
- `erinnertes-mitglied/` -- mit Block, neue Form. Erwartet: Code 0, Bau rot an `-Werror`.
- `erinnert-alte-form/` -- mit Block, alte Form. Gegenstueck fuer den Bytevergleich.
- `enger-gueltigkeitsbereich/` -- Einbindung im `block()`. Erwartet: Code 1 am zweiten
  Riegel. Verlangt CMake 3.25 statt der 3.22 des Vorhabens.
- `riegel-machbarkeit/` -- gehoert nicht zu dieser Abnahme, sondern belegt, dass der
  Vorschlag 0058 baubar ist.
- `enger-gueltigkeitsbereich-CMakeLists.txt` -- ein Fehlgriff von mir, ein Dateiname,
  unter dem `cmake -S` nichts findet. Steht als Hinweis auf das richtige Verzeichnis da.

Die Bauverzeichnisse lagen in `$TMPDIR/kp0046/` und damit ausserhalb des Repos.
