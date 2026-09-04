---
id: 0058-warnsatz-schlussriegel-alle-ziele
rolle: kernbauer
status: fertig
haengt_an: [0046-warnsatzriegel-fuer-kuenftige-mitglieder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Der Riegel bindet den Aufruf, nicht das Mitglied

Vorschlag aus der Pruefung von Paket 0046 (2026-09-03, Rolle `kern-pruefer`). Messungen
in `befunde/pruefung-0046-warnsatzriegel-fuer-kuenftige-mitglieder-2026-09-03.md`,
Wegwerf-Mitglieder unter `befunde/pruefung-0046/`.

**Selbst umnummeriert von `0056` auf `0058`, noch im selben Lauf.** Ich hatte 0056 als
freie Nummer gesehen; waehrend ich schrieb, hat ein zweiter Lauf derselben Rolle
(Pruefung 0038) `0056-meldung-abschneiden-kenntlich.md` und ein dritter
`0057-reihentoml-belegstellen-ausserhalb-pruefweg.md` angelegt. Das ist genau die
Kollision, die am 2026-09-03 schon einmal einen Projektmanagerlauf gekostet hat (0045),
und sie faellt hier nicht dem Projektmanager zu, weil ich sie noch selbst sehen konnte.
Die Datei unter dem alten Namen steht auf `status: archiviert` und verweist hierher;
loeschen laesst Hausregel 3 sie nicht.

## Der Befund

Paket 0046 ist erfuellt: Ein Mitglied, das die Form von `pruefstand/CMakeLists.txt`
abschreibt und dabei den `PROJECT_IS_TOP_LEVEL`-Block verliert, bricht seit heute ab --
`Unknown CMake command "fabrik_warnsatz_anlegen"`, Code 1, gemessen.

Der Riegel greift aber erst am **Aufruf**. Ein Mitglied, das
`fabrik_warnsatz_anlegen` gar nicht erst ruft, kommt an ihm vorbei, weil es nichts
Unbekanntes ausspricht.

Der konkrete Fall, an dem das passieren wird: `konsole` aus T13 wird gebaut. Sein
Bauagent kennt die Form nicht und schreibt die kuerzeste `CMakeLists.txt`, die
funktioniert -- `cmake_minimum_required`, `project`, `add_executable`,
`target_link_libraries`. Kein Block, kein Aufruf. Der Arbeitsbereich nimmt das Mitglied
auf, sobald sein Verzeichnis existiert (`CMakeLists.txt:45-51`), uebersetzt es und meldet
`ergebnis: ok`.

Was dabei verloren geht, ist gemessen -- an `befunde/pruefung-0046/vergessen-alte-form/`,
blank konfiguriert:

```
CXX_FLAGS = -std=gnu++20
```

Also alle 15 Warnschalter, beide Ueberlaufschalter und der Sprachmodus. `-fwrapv` ist
ADR 0011 Massnahme 1 und traegt den Determinismus des Kerns; `-std=c++20` statt
`gnu++20` schliesst die Compiler-Erweiterungen aus, die ADR 0011 verbietet. Und
`konsole` und `oberflaeche` haben nach T13 keine eigenen Proben, es fehlt also auch das
laute `"No tests were found!!!"`, an dem so etwas sonst auffaellt.

Das ist dieselbe Fehlerfamilie wie 0031 und 0046, eine Ebene weiter aussen: nicht *"der
siebte abgeschriebene Satz verliert eine Zeile"* und nicht *"das siebte Mitglied vergisst
die Einbindung"*, sondern *"das siebte Mitglied benutzt die Form nie"*.

## Warum das ein eigenes Paket ist und nicht Teil von 0046

Es ist **keine** der drei Abnahmebedingungen von 0046, und keine davon ist verletzt --
das Paket ist geprueft. Bedingung 1 verlangt woertlich ein Mitglied, das "sonst aber
gebaut ist wie `pruefstand/CMakeLists.txt`", also eines **mit** dem Aufruf. Der Fall
ohne Aufruf steht dort nicht, und ein Bauagent, der ihn nebenbei mitgeloest haette,
haette die Abnahme verlassen.

Es ist auch technisch eine andere Bauform: 0046 verlagert eine Zeile an sechs
Aufrufstellen, dieses Paket haengt eine Pruefung an das **Ende** der Konfiguration und
braucht dafuer eine Aufzaehlung aller Ziele. Beides in einem Paket haette zwei
Begruendungen unter einer Abnahme.

Es haengt an 0046, weil es dessen Funktion voraussetzt: Der Schlussriegel prueft, ob an
jedem Ziel steht, was `fabrik_warnsatz_anlegen` anhaengt.

## Warum ein Schlussriegel und nicht noch ein Aufruf

Eine dritte Stelle, an die man den Satz haengen kann, waere eine dritte Stelle, die man
vergessen kann. Der Unterschied dieses Vorschlags ist, dass er **nicht** an der Stelle
prueft, an der etwas getan wird, sondern an der Stelle, an der alles getan ist: Er zaehlt
am Ende die Ziele und fragt jedes, ob der Satz daran haengt. Ein Mitglied kann sich dem
nicht durch Nichtstun entziehen -- Nichtstun ist genau der Fall, den er faengt.

Die Grenze davon gehoert dazu: Ein Mitglied ohne Block, **allein** gebaut, bindet
`werkzeugkette.cmake` nicht ein und fuehrt den Schlussriegel deshalb auch nicht aus. Es
faellt trotzdem auf, weil `baulauf.py` jedes Manifest **und** den Arbeitsbereich baut und
der Arbeitsbereich die Datei immer einbindet. Der Bericht wird also rot, nur an einer
anderen Zeile.

## Was zu tun ist

Die Bauform steht frei; die Abnahme prueft die Wirkung. Ein Weg, den ich am 2026-09-03
gemessen habe (`befunde/pruefung-0046/riegel-machbarkeit/`, CMake 4.2.3): eine Funktion
in `werkzeugkette.cmake`, die ueber `BUILDSYSTEM_TARGETS` des Verzeichnisses laeuft, sich
ueber `SUBDIRECTORIES` rekursiv weiterhangelt und je Ziel `COMPILE_OPTIONS` liest; ans
Ende der Konfiguration gehaengt mit `cmake_language(DEFER CALL ...)` beim Einbinden der
Datei. Gemessene Ausgabe der Probe -- zwei Ziele im obersten Verzeichnis, eines eine
Ebene tiefer:

```
-- PRUEFER-RIEGEL: mit_satz (STATIC_LIBRARY) -- Warnsatz vorhanden
-- PRUEFER-RIEGEL: ohne_satz (STATIC_LIBRARY) -- OHNE WARNSATZ, hier stuende FATAL_ERROR
-- PRUEFER-RIEGEL: mitglied_ohne_satz (STATIC_LIBRARY) -- OHNE WARNSATZ, ...
```

Die Aufzaehlung reicht also ueber `add_subdirectory` hinweg -- das ist die Bedingung
dafuer, dass der Riegel im Arbeitsbereich ueberhaupt etwas sieht.

**Zwei Dinge, an denen so ein Riegel falsch scharf wird und die in die Bauform gehoeren:**

1. **Nicht jedes Ziel uebersetzt.** `TYPE` liefert auch `INTERFACE_LIBRARY`, `UTILITY`
   und `ALIAS`. An ein `INTERFACE_LIBRARY` laesst sich `PRIVATE` gar nicht haengen, ein
   `UTILITY` entsteht bei `add_custom_target` und bei `enable_testing()`. Geprueft wird
   nur, was Quelldateien uebersetzt: `STATIC_LIBRARY`, `SHARED_LIBRARY`,
   `OBJECT_LIBRARY`, `EXECUTABLE`.
2. **Der Text der Meldung ist die halbe Massnahme.** Sie muss den Zielnamen und den
   auszufuehrenden Aufruf nennen (`fabrik_warnsatz_anlegen(<ziel>)`), sonst sucht der
   naechste Bauagent an der falschen Stelle.

**Was nicht dazugehoert:** die Werte des Warnsatzes aendern, `-Wpedantic` aufnehmen, eine
Ausnahmeliste "diese Ziele duerfen ohne" einfuehren (das waere die Tuer, durch die der
Fehler zurueckkommt -- wenn eine Ausnahme noetig wird, ist das ein ADR), oder die
Sanitizer in die Pruefung ziehen (sie haengen nach ADR 0011 Massnahme 2 nur an den
`_geprueft`-Zielen).

**Nebenwirkung, die niemanden ueberraschen soll:** `befunde/pruefung-0046/riegel-machbarkeit/`
haelt absichtlich zwei Ziele ohne Warnsatz und bindet `werkzeugkette.cmake` ein. Wer es
nach dieser Aenderung von Hand konfiguriert, bekommt den Abbruch -- das ist dann richtig,
nicht kaputt. Der Baulauf fasst es nicht an (Pfad enthaelt `befunde`).

## Abnahme

1. **Ein Ziel ohne Warnsatz bricht die Konfiguration ab.** Nachweis: ein
   Wegwerf-Mitglied mit einem uebersetzenden Ziel und **ohne** `fabrik_warnsatz_anlegen`,
   per `add_subdirectory` in einen Baum gehaengt, der `werkzeugkette.cmake` einbindet.
   `cmake -S … -B …` endet mit Code ungleich 0, und der Wortlaut der Meldung gehoert in
   den Nachweis. Daneben, am Stand **vor** der Aenderung gemessen, dieselbe Datei mit
   Code 0 und gruenem Bau -- ohne diese Gegenprobe belegt die erste Haelfte nur, dass
   irgendetwas rot wurde. Das Wegwerf-Mitglied gehoert nicht in den Baum: `$TMPDIR`
   zuerst, sonst unterhalb von `befunde/` (dort sammelt `baulauf.py` nicht ein,
   `baulauf.py:116`).
2. **Die heutigen Ziele bleiben unberuehrt.** Nachweis: alle erzeugten `CXX_FLAGS` ueber
   die drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein), vorher gegen
   nachher, maschinell verglichen und **bytegleich** -- Stand 2026-09-03 sind das 30
   Ziele. Nicht "der Bau ist gruen": Ein Riegel, der versehentlich alle Ziele
   durchwinkt, baut auch gruen.
3. **Der Uebersetzungsbericht des Tages zeigt beide Kaesten gebaut und alle Tests
   `Passed`**, ueber den Alleinbau-Weg von `baulauf.py` und ueber den Arbeitsbereich.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

Die vier Prüfungen meiner Rolle:

- **Rolle:** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und wird eingeplant. ✓
- **Dateischnitt:** `werkzeugkette.cmake` beansprucht sonst nur 0046 — mit diesem Lauf
  `fertig`. Kein Paket auf `offen`, keines auf `gebaut` hält die Datei. Auch die beiden
  `CMakeLists.txt` sind frei; dieses Paket fasst sie nicht an und braucht sie nicht, weil
  der Riegel am Ende der Konfiguration hängt statt an den Mitgliedern. ✓
- **Abnahme:** prüfbar, mit einer Staffelung des Nachweisorts, siehe unten. ✓
- **Abhängigkeit:** 0046 ist mit diesem Lauf `fertig`. Die Sperre fällt, das Paket ist
  startbereit. Kein Deadlock — 0046 wurde `geprueft`, nicht zurückgewiesen. ✓

**Der Vorschlag begründet richtig, warum das kein Rücklauf gegen 0046 ist.** Dessen
Bedingung 1 verlangt wörtlich ein Mitglied, das „sonst aber gebaut ist wie
`pruefstand/CMakeLists.txt`" — also eines **mit** dem Aufruf. Ein Bauagent, der den Fall
ohne Aufruf nebenbei mitgelöst hätte, wäre aus seiner Abnahme herausgelaufen.

### Staffelung des Nachweisorts — Bedingungen 1 und 2

**Beide Bedingungen verlangen, `cmake` laufen zu lassen. Die Werkzeugliste der Rolle
`kernbauer` (`agents/rollen/kernbauer.md`, Frontmatter) führt kein ausführendes Werkzeug:
Read, Glob, Grep, WebSearch, WebFetch, `Edit(ventures/**)`, `Edit(notizen/kernbauer.md)`.**
Ob ein Lauf trotzdem eines bekommt, wechselt — am 2026-09-03 hat der Bauagent von 0046 auf
demselben Weg gebaut, während der Prüfer von 0011 an jedem Schreibzugriff außerhalb des
Repos scheiterte. Es hängt am Modus des Laufs, nicht an der Sache. Ohne Staffelung stünde
der Bauagent vor einem Kriterium, das er vielleicht nicht erfüllen kann, und die
wahrscheinliche Folge wäre eine behauptete statt einer gemessenen Zahl.

**Der Inhalt beider Bedingungen bleibt unverändert.** Gestaffelt ist allein der Ort, und
der letzte Rang ist eine ausgewiesene Nichtmessung statt einer Falschaussage. Dieselbe
Staffelung stand in 0046 und hat dort nichts gekostet: Der Bauagent kam mit Rang 1 aus.

1. Bevorzugt ein Verzeichnis aus `$TMPDIR`, außerhalb des Repos.
2. Schlägt das fehl: unterhalb von `befunde/`. Dort sammelt `baulauf.py` keine Manifeste
   ein (`baulauf.py:116`), der Übersetzungsbericht hängt also nicht an deiner Wegwerfdatei.
   **Nicht** unterhalb von `bau/` und nicht in einem `file(GLOB …)`-Kasten.
3. Schlägt auch das fehl: Die betroffene Bedingung gilt als **ausgewiesen nicht gemessen**.
   Dann gehört in den Nachweis der Wortlaut der Ablehnung und die Begründung am Text der
   Änderung — bei Bedingung 1, warum der Riegel bei einem Ziel ohne Warnsatz hart abbricht;
   bei Bedingung 2, warum die erzeugten Schalter sich nicht ändern können. Das ist kein
   Rücklaufgrund. Eine Nichtmessung, die als solche dasteht, ist richtig; eine behauptete
   Messung wäre falsch.

**Bedingung 3 ist von der Staffelung nicht berührt** und bleibt wörtlich: Der
Übersetzungsbericht ist fremdgemessen, `baulauf.py` erzeugt ihn unabhängig vom Bauagenten.
Er ist zugleich das Netz unter Rang 3 — denn ein Riegel, der ein Ziel ohne Warnsatz
durchgehen ließe, wäre wirkungslos, und einer, der zu scharf ist, macht den Bericht rot.
Was er **nicht** belegt, ist Bedingung 2: Ein Riegel, der alle Ziele durchwinkt, baut
ebenfalls grün. Das steht im Vorschlag und bleibt der Grund, warum Bedingung 2 den
Bytevergleich verlangt und nicht die Farbe des Baus.

---

## Nachweis, Lauf vom 2026-09-03 (Kernbauer)

Geändert ist genau eine Datei: `werkzeugkette.cmake`, angehängt hinter
`fabrik_warnsatz_anlegen`. Keine `CMakeLists.txt` angefasst — der Riegel hängt am Ende
der Konfiguration und nicht an den Mitgliedern, deshalb musste er es nicht.

**Nachweisort: Rang 1 der Staffelung.** Alles unter `$TMPDIR` = `/tmp/claude-1000/r58`,
außerhalb des Repos. Rang 2 und 3 wurden nicht gebraucht. CMake 4.2.3, g++ 15.2.0.

Alle `cmake`-Aufrufe mit der Konfiguration des Runners
(`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`), sonst
misst man einen anderen Schaltersatz als der Übersetzungsbericht.

### Die Bauform

Ein `cmake_language(DEFER DIRECTORY ${CMAKE_SOURCE_DIR} CALL fabrik_schlussriegel …)`
beim Einbinden der Datei, **genau einmal** über eine globale Eigenschaft abgesichert —
der Arbeitsbereich bindet die Datei ein, ein allein gebautes Mitglied ebenfalls, und
zwei Riegel meldeten dasselbe doppelt. Die Aufzählung läuft iterativ über eine
Arbeitsliste (`BUILDSYSTEM_TARGETS` je Verzeichnis, `SUBDIRECTORIES` als Nachschub)
statt rekursiv; das Ergebnis ist dasselbe wie in der Machbarkeitsprobe des Prüfers.

Zwei Abweichungen von der dort gemessenen Skizze, beide bewusst:

- **Der Sollzustand steht in einer globalen Eigenschaft** (`FABRIK_SCHLUSSRIEGEL_SATZ`),
  gesetzt an der Stelle, an der `FABRIK_STRENGE` definiert ist. Die Skizze las
  `COMPILE_OPTIONS` gegen `MATCHES "-Werror"` im Gültigkeitsbereich des Riegels. Wird die
  Datei aus einem engeren Bereich eingebunden, findet der Riegel den Sollzustand so
  trotzdem — sonst ginge er selbst leer aus und wänke alles durch.
- **Geprüft wird der ganze Satz, nicht ein Kennzeichen daraus.** Ein Ziel, an dem jemand
  `-Wall -Wextra -fwrapv` von Hand anhängt, hat den Satz nicht. Gemessen unten.

### Bedingung 1 — ein Ziel ohne Warnsatz bricht die Konfiguration ab

Wegwerf-Baum `/tmp/claude-1000/r58/probe-ohne/`: oberste Ebene bindet
`werkzeugkette.cmake` ein und hat ein Ziel **mit** dem Aufruf, `add_subdirectory` hängt
ein Mitglied daneben, dessen `CMakeLists.txt` aus `cmake_minimum_required` und
`add_library` besteht — kein Block, kein Aufruf. Das ist die Form, in der `konsole` aus
T13 geschrieben wird.

**Gegenprobe zuerst, am Stand vor der Änderung** (dieselbe Datei, `HEAD`):

```
-- Configuring done (0.2s)
CODE=0
[100%] Built target ohne_satz
CODE=0
```

Und die Schalter, die das Ziel dabei bekam — links blank konfiguriert, rechts unter dem
Runner, beide am Stand vor der Änderung:

```
blank:            CXX_FLAGS = -std=c++20
unter baulauf.py: CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20
```

zum Vergleich das Geschwisterziel **mit** dem Aufruf, blank:

```
CXX_FLAGS = -std=c++20 -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow
            -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
            -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2
            -fwrapv -fno-fast-math
```

**Hier weiche ich vom Wortlaut des Vorschlags ab, und zwar zugunsten der Genauigkeit.**
Der Vorschlag nennt als Verlust „alle 15 Warnschalter, beide Überlaufschalter und den
Sprachmodus" und belegt ihn mit `CXX_FLAGS = -std=gnu++20`. Diese Messung des Prüfers ist
richtig, gehört aber zum Fall *Mitglied allein gebaut, ohne `PROJECT_IS_TOP_LEVEL`-Block*
— dort gilt `werkzeugkette.cmake` gar nicht. Im Fall, den **dieser** Riegel fängt, gilt
sie, und der Verlust ist kleiner: Den Sprachmodus erbt das Ziel über
`CMAKE_CXX_STANDARD`, die Überlaufschalter erbt es unter dem Runner von außen. Was in
allen drei Fällen fehlt, sind die 15 Warnschalter und damit `-Werror`. Der Meldungstext
und der Kommentar im Quelltext nennen jetzt beide Fälle getrennt statt zusammengezogen;
die Sache wird dadurch nicht kleiner, nur nachprüfbar.

**Nach der Änderung, derselbe Baum, Code 1** — Wortlaut vollständig:

```
CMake Error at …/werkzeugkette.cmake:294 (message):
  Der Warnsatz fehlt an folgenden Zielen -- sie wuerden gruen uebersetzen und
  weniger pruefen:

    ohne_satz (STATIC_LIBRARY) in /tmp/claude-1000/r58/probe-ohne/ohne-satz
        es fehlen: -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow
        -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
        -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2
        -fwrapv -fno-fast-math
        Abhilfe:   fabrik_warnsatz_anlegen(ohne_satz)  -- hinter `add_library`/`add_executable`

  Jedes uebersetzende Ziel ruft `fabrik_warnsatz_anlegen(<ziel>)` aus
  `werkzeugkette.cmake`; die Datei bindet ein Mitglied beim Alleinbau in
  seinem `PROJECT_IS_TOP_LEVEL`-Block ein.

  Ohne den Satz uebersetzt das Ziel gruen und ohne `-Werror`.  Blank
  konfiguriert fehlt ihm zusaetzlich `-fwrapv` (ADR 0011, Massnahme 1);
  allein gebaut ohne den `PROJECT_IS_TOP_LEVEL`-Block auch der Sprachmodus --
  `gnu++20` statt `c++20`.
Call Stack (most recent call first):
  …/werkzeugkette.cmake:322 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED

-- Configuring incomplete, errors occurred!
CODE=1
```

Zielname und auszuführender Aufruf stehen darin, wie der Vorschlag es verlangt.

**Drei weitere Wegwerf-Bäume, weil „irgendetwas wurde rot" kein Nachweis über den
Riegel ist:**

| Baum | Inhalt | erwartet | gemessen |
|---|---|---|---|
| `probe-mit/` | dieselbe Form, **jedes** Ziel mit dem Aufruf | Code 0 | `Warnsatz-Schlussriegel: 2 uebersetzende Ziele geprueft` — Code 0 |
| `probe-arten/` | ein Ziel mit Satz, dazu `INTERFACE`, `ALIAS`, `add_custom_target`, `enable_testing()` | Code 0, nur 1 gezählt | `… 1 uebersetzende Ziele geprueft` — Code 0 |
| `probe-teilsatz/` | ein Ziel mit von Hand angehängtem `-Wall -Wextra -fwrapv` | Code 1 | Code 1, `es fehlen: -Werror -Wconversion … -fno-fast-math` |

`probe-arten` ist die Gegenprobe zur Artenliste: Ohne sie wäre nur gemessen, dass der
Riegel nicht fälschlich anspringt, **weil** es keine solchen Ziele gibt. Im Baum von heute
gibt es keinen `add_custom_target` — mit dem ersten wäre der Riegel sonst falsch scharf
geworden.

### Bedingung 2 — die heutigen Ziele bleiben unberührt

Alle `CXX_FLAGS`-Zeilen aus allen erzeugten `flags.make` über die drei Bauwege,
eingesammelt mit dem Baupfad als Präfix, vorher gegen nachher:

```
Ziele: 30 | bytegleich: True | Bytes: 11953 11953
```

30 Ziele, wie der Vorschlag es für den Stand 2026-09-03 nennt. Das Präfix trägt mit:
Derselbe Bytevergleich belegt zugleich, dass **dieselbe Menge** Ziele entsteht — ein
Riegel, der ein Ziel verschluckt hätte, ergäbe eine kürzere Datei.

Die Zählung des Riegels stimmt unabhängig davon mit derselben Zahl überein:

```
Arbeitsbereich  -- Warnsatz-Schlussriegel: 15 uebersetzende Ziele geprueft, alle mit Warnsatz.
kern allein     -- Warnsatz-Schlussriegel: 10 uebersetzende Ziele geprueft, alle mit Warnsatz.
pruefstand all. -- Warnsatz-Schlussriegel:  5 uebersetzende Ziele geprueft, alle mit Warnsatz.
                                            ------
                                              30
```

Diese Zeile steht absichtlich im Quelltext: Sie ist das, was den Übersetzungsbericht den
Unterschied zwischen *„der Riegel hat geprüft"* und *„der Riegel hat nichts gesehen"*
tragen lässt. Ein Riegel, der alle Ziele durchwinkt, baut grün — die Zahl fällt dann auf
0 und steht im Bericht.

### Bedingung 3 — beide Kästen gebaut, alle Tests `Passed`

Selbst nachgefahren, in `$TMPDIR` statt in `bau/`; der Übersetzungsbericht des Tages
entsteht danach fremdgemessen durch `baulauf.py`.

```
Arbeitsbereich   BAU=0   100% tests passed, 0 tests failed out of 11
kern allein      BAU=0   100% tests passed, 0 tests failed out of  8
pruefstand all.  BAU=0   100% tests passed, 0 tests failed out of  3
```

Das vierte Manifest, `pruefstand/bau/pruefung-0019/CMakeLists.txt`, bindet
`werkzeugkette.cmake` nicht ein und setzt seine Schalter selbst — der Riegel läuft dort
nicht. Nachgeprüft statt angenommen: konfiguriert mit Code 0.

### Was der Prüfer nachfahren kann

Die Wegwerf-Bäume liegen unter `$TMPDIR` und sind nach dem Lauf weg. Sie sind aus dem
Nachweis nachzubauen: vier Bäume, jeder oberste Ebene mit
`include(<pfad>/werkzeugkette.cmake)`, Inhalt wie in der Tabelle. Für die Gegenprobe zu
Bedingung 1 kommt der alte Stand aus
`git show HEAD:…/werkzeugkette.cmake` in eine Wegwerfdatei.

**Nicht abgedeckt, ausdrücklich:** `MODULE_LIBRARY` übersetzt Quelldateien, steht aber
nicht in der Artenliste des Vorschlags und deshalb auch nicht in der des Riegels. Heute
gibt es kein solches Ziel; die Vorgabe zu erweitern wäre eine Abweichung von `specs/`
gewesen. Im Logbuch vermerkt.
