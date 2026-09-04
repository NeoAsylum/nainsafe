---
typ: nachweis
paket: 0069-t2-linkriegel-in-der-werkzeugkette
rolle: kernbauer
datum: 2026-09-04
---

# Nachweis zu Paket 0069

Werkzeugkette: g++ 15.2.0, cmake 4.2.3. Gemessen wurde in beiden Profilen -- blank
konfiguriert und mit der Zeile des Runners
(`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`).

**Nachweisort.** Die Rotnachweise brauchen eine Zeile im Wurzelmanifest. Diese Datei
steht nicht in der Dateiliste dieses Pakets und ist von einem anderen offenen Paket
beansprucht; der Annahmevermerk des Projektmanagers weist die Messung deshalb an eine
Abschrift des Baums unter `befunde/messung-0069/baum/`. Genau dort ist sie gelaufen.
Der Arbeitsbaum ist unberuehrt geblieben -- der letzte Abschnitt zeigt es nach.

Die Angriffszeile wurde je Fall eingebaut, konfiguriert und wieder zurueckgenommen.
Die Abschrift steht am Ende dieses Laufs wieder Zeichen fuer Zeichen so da wie der
Arbeitsbaum; die Wegwerfquelle `fremd.cpp`, die die Faelle brauchen, liegt absichtlich
**neben** der Abschrift und nicht darin, damit sie niemand fuer einen Bestandteil des
Vorhabens haelt.

## Was gebaut wurde

Ein zweiter Gegenstand am bestehenden Schlussriegel in `werkzeugkette.cmake`, kein
zweiter Apparat. Er liest je Ziel aus `FABRIK_NULLABHAENGIG` vier Eigenschaften:

    LINK_LIBRARIES              INTERFACE_LINK_LIBRARIES
    LINK_OPTIONS                INTERFACE_LINK_OPTIONS

Die ersten beiden muessen leer sein -- jeder Eintrag ist ein Befund. In den letzten
beiden faellt nur auf, was die Form einer Bibliothek hat (ein Wort, das mit `-l`
beginnt, oder eines, das auf eine Bibliotheksendung endet); die Sanitizerschalter des
geprueften Kerns stehen dort erlaubterweise.

Dazu zwei Riegel gegen den Riegel selbst: eine leere Namensliste bricht ab, und ein
Kernmanifest unter der Wurzel ohne ein Ziel dieses Namens bricht ebenfalls ab.

## Bedingung 1 -- gruen auf dem heutigen Baum, mit dem gelesenen Wert daneben

Drei Bauwege, alle Code 0. Die Meldung nennt die Eigenschaft und ihren Wert, nicht
"keine Auffaelligkeiten":

**Arbeitsbereich** (blank und im Profil des Runners wortgleich):

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 17 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done
```

**Alleinbau des Kerns** -- dieselbe Zeile, daneben 11 statt 17 uebersetzende Ziele.

**Alleinbau des Pruefstands** -- dort gibt es den Kern nicht, und der Riegel sagt das,
statt gruen ueber nichts zu melden:

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, ...
```

Der Bau des Arbeitsbereichs laeuft durch (Code 0), 12 der 13 Proben sind gruen. Die
dreizehnte ist ein fremder Rotstand und steht weiter unten.

## Bedingung 2 -- die zwei Rotnachweise

Beide Varianten fallen rot aus. Positivkontrolle: dieselbe Abschrift ohne
Angriffszeile, unmittelbar danach konfiguriert, Code 0 mit der Meldung aus Bedingung 1.

### Variante A -- die Verzeichnisform eine Ebene hoeher

Eingebaut im Wurzelmanifest der Abschrift, vor der Schleife ueber die Mitglieder:

```cmake
add_library(fremd STATIC fremd.cpp)
fabrik_warnsatz_anlegen(fremd)
link_libraries(fremd)
```

Der Warnsatz haengt am Wegwerfziel, damit der **andere** Riegel nicht zuerst
anschlaegt und der Rotnachweis dem gehoert, um den es geht. Ergebnis, Code 1:

```
CMake Error at werkzeugkette.cmake (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: LINK_LIBRARIES nennt fremd
    kern: INTERFACE_LINK_LIBRARIES nennt fremd
    kern_geprueft: LINK_LIBRARIES nennt fremd
    kern_geprueft: INTERFACE_LINK_LIBRARIES nennt fremd
```

Die Ruecknahme in der Abnahme -- faellt Variante A nicht rot aus, gehoert in das Paket,
in welcher Eigenschaft sie stattdessen landet -- wird nicht gebraucht: Die
Verzeichnisanweisung landet in der **Ziel**eigenschaft, und zwar in beiden. Sie trifft
ausserdem den geprueften Kern mit, weil sie fuer jedes danach angelegte Ziel gilt.

### Variante B -- die Zielform aus einem fremden Verzeichnis

Eingebaut am Ende desselben Manifests, also ausserhalb des Verzeichnisses, in dem der
Kern entsteht:

```cmake
add_library(fremd STATIC fremd.cpp)
fabrik_warnsatz_anlegen(fremd)
target_link_libraries(kern PRIVATE fremd)
```

Ergebnis, Code 1:

```
CMake Error at werkzeugkette.cmake (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: LINK_LIBRARIES nennt ::@(0x5cc1689589d0)
    kern: LINK_LIBRARIES nennt fremd
    kern: LINK_LIBRARIES nennt ::@
    kern: INTERFACE_LINK_LIBRARIES nennt ::@(0x5cc1689589d0)
    kern: INTERFACE_LINK_LIBRARIES nennt $<LINK_ONLY:fremd>
    kern: INTERFACE_LINK_LIBRARIES nennt ::@
```

**Der Nebenbefund ist hier der wertvollere Teil, und er traegt die Bauform des ganzen
Pakets.** Wer aus einem fremden Verzeichnis linkt, hinterlaesst nicht den Namen der
Bibliothek, sondern eine geklammerte Kennung des Verzeichnisses davor und dahinter --
und auf der Schnittstellenseite steckt der Name zusaetzlich in einem
Generatorausdruck. Ein Riegel, der auf einen **Namen** abgliche, muesste beide Formen
kennen und veraltete mit der naechsten. Ein Riegel, dem **leer** der Sollzustand ist,
sieht sie, ohne sie zu kennen.

Zwei Sachen stehen nicht in der Meldung und gehoeren trotzdem gewusst: Die Klammerzahl
ist eine Speicheradresse und damit von Lauf zu Lauf verschieden -- wer diesen Wortlaut
je vergleicht, vergleicht sie mit. Und der gepruefte Kern bleibt hier sauber, anders
als bei Variante A: Die Zielform trifft genau das genannte Ziel.

### Variante C -- die Linkerzeile (ueber die Abnahme hinaus)

Weder in der Abnahme noch in der Vorgabe, aber dieselbe Frage: Ein `-l`-Schalter ist
fuer CMake keine Abhaengigkeit, sondern ein Wort, und steht in keiner der beiden
Eigenschaften oben. Eingebaut als `target_link_options(kern PRIVATE -lfremd)` am Ende
des Wurzelmanifests, Code 1:

```
    kern: LINK_OPTIONS nennt -lfremd
```

Genau eine Zeile: Die beiden Sanitizerschalter am geprueften Kern stehen in derselben
Eigenschaft und werden nicht mitgemeldet. Das ist zugleich die Gegenprobe darauf, dass
der vierte Durchgang nicht zu scharf ist.

### Variante D -- der Riegel ohne Gegenstand

Der Riegel darf nicht deshalb gruen sein, weil er sein Ziel nicht gefunden hat. In der
Abschrift wurde das Kernziel umbenannt, das Kernmanifest liegt weiter da. Code 1:

```
CMake Error at werkzeugkette.cmake (message):
  fabrik_schlussriegel: unter '.../befunde/messung-0069/baum' liegt ein
  Kernmanifest, aber es gibt kein Ziel dieses Namens.  Der
  Nullabhaengigkeitsriegel haette nichts gelesen und trotzdem gruen gemeldet
  -- das ist kein gruener Bau, sondern ein Riegel ohne Gegenstand.
```

### Variante E -- die leere Namensliste

`set(FABRIK_NULLABHAENGIG)` in der Abschrift. Code 1:

```
CMake Error at werkzeugkette.cmake (message):
  fabrik_schlussriegel: die Liste der nullabhaengigen Ziele ist leer.
  Dasselbe gilt wie fuer den Sollzustand oben -- ein Riegel ohne Gegenstand
  winkt jedes Ziel durch und baut gruen.
```

## Bedingung 3 -- die Probenziele bleiben gruen

Der Kern und der Pruefstand haengen je eine Probenbibliothek an ihre eigenen Ziele.
Diese Zeilen sind der Blindtreffer, an dem der ausgeschriebene Mustervergleich
gescheitert waere; der Riegel sieht sie gar nicht an, weil er nach den Eigenschaften
**des Kerns** fragt und nicht nach dem Text irgendeines Manifests.

Nachgewiesen an den Zahlen des Warnsatzriegels, die sich durch dieses Paket nicht
bewegt haben -- 17 im Arbeitsbereich, 11 im Kern, 5 im Pruefstand -- und daran, dass
der Bau des Arbeitsbereichs durchlaeuft und die Proben laufen.

## Was der Riegel nicht sieht

Ausgeschrieben, weil ein Riegel, dessen Grenze niemand kennt, die naechste Sache ist,
die aussieht, als pruefe sie etwas:

* **Die Kommandozeile und die Umgebung.** Ein `-lfremd` in `CMAKE_CXX_FLAGS` oder in
  den Linkerschaltern von aussen steht in keiner Zieleigenschaft. Dieselbe Grenze hat
  der Warnsatzriegel daneben, und sie ist dieselbe Sorte: Was von aussen kommt, gehoert
  dem, der baut.
* **Ein Mitglied ohne den Block fuer den Alleinbau** bindet die Werkzeugkette beim
  Alleinbau nicht ein und fuehrt keinen der beiden Riegel aus. Es faellt trotzdem auf,
  weil der Runner zusaetzlich den Arbeitsbereich baut.
* **Ein Pfad auf eine Bibliotheksdatei in den Linkschaltern** wird nur erkannt, wenn er
  auf eine der beiden Endungen endet. Eine dritte Endung kaeme durch. Bei den beiden
  Bibliothekseigenschaften gibt es diese Luecke nicht -- dort ist jeder Eintrag ein
  Befund, unabhaengig von seiner Form.

## Fremder Rotstand, nicht dieses Paket

`ctest` meldet eine rote Probe von dreizehn: der Belegstellenriegel, Bedingung 2, fuenf
nicht aufloesbare Abschnittszitate aus `daten/reihen.toml` und
`daten/einheitenbefund-pwt-baci.md` auf eine Ueberschrift in `rueckstand.md`, die es
dort nicht (mehr) gibt.

Zugeordnet statt vermutet: Derselbe Riegel, gegen eine Abschrift des letzten Commits
laufen gelassen -- also **ohne** die Aenderung dieses Pakets --, meldet dieselben fuenf
Zitate und dieselben Zahlen (39 Bauquellen, 24 Zitate gefunden, 19 aufgeloest). Der
Rotstand liegt am Stand des Baums, nicht an dieser Aenderung, und die betroffenen
Dateien gehoeren nicht zu diesem Paket. Nicht angefasst.

## Der Arbeitsbaum ist unberuehrt

Nach dem Lauf weist `git status` unter dem Vorhaben genau die Eintraege aus, die diesem
Paket gehoeren, und das Wurzelmanifest ist keiner davon:

    M  werkzeugkette.cmake                    <- die eine Datei dieses Pakets
    ?? befunde/messung-0069/fremd.cpp         <- Wegwerfquelle der Rotnachweise
       befunde/messung-0069/nachweis.md       <- diese Datei
       befunde/messung-0069/baum/             <- die Abschrift, aufgefrischt

Zwei weitere Eintraege stehen daneben und stammen aus fremden, gleichzeitig laufenden
Paketen (eines unter `aufgaben/`, eines unter `werkzeuge/belegstellen/`). Sie sind
nicht angefasst worden. Die Abschrift traegt sie in ihrem damaligen Zwischenstand mit,
weil sie zum Zeitpunkt der Auffrischung so im Baum standen.
