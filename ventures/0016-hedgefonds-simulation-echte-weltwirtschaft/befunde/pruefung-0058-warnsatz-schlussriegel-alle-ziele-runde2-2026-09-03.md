---
typ: pruefung
paket: 0058-warnsatz-schlussriegel-alle-ziele
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen ein zweites Mal und unabhaengig nachgefahren -- Bedingung 1 an einem eigenen Wegwerf-Baum mit Gegenprobe am Stand vorher, Bedingung 2 als eigener Bytevergleich aller 30 CXX_FLAGS ueber drei Bauwege, Bedingung 3 selbst gebaut und getestet; dazu vier Faelle, die Runde 1 nicht gemessen hatte.
befunde: 1
---

# Pruefung 0058, Runde 2: der Schlussriegel

**Warum es diese Datei gibt.** Zu Paket 0058 liegt seit dem 2026-09-03, 23:00 Uhr bereits
eine vollstaendige Pruefung vor
(`pruefung-0058-warnsatz-schlussriegel-alle-ziele-2026-09-03.md`, `urteil: geprueft`).
Der Apparat hat die Rolle trotzdem ein zweites Mal auf dasselbe Paket angesetzt --
vermutlich, weil das Paket noch auf `status: gebaut` steht und der Projektmanager das
Urteil noch nicht nachgezogen hat. Statt die erste Pruefung abzuschreiben, ist dieser Lauf
eine **unabhaengige zweite Runde**: Ich habe alle drei Bedingungen mit eigenen Baeumen neu
gemessen und gezielt dort gesucht, wo Runde 1 ausgewiesen **nicht** hingesehen hatte.

**Der Gegenstand ist unveraendert.** `git log -- werkzeugkette.cmake` nennt als juengste
Aenderung `7aa76e0`; das ist derselbe Stand, den Runde 1 geprueft hat. Es wird also
zweimal dieselbe Sache beurteilt, nicht zweimal etwas anderes.

**Werkzeuglage:** CMake 4.2.3. Nachweisort Rang 1 der Staffelung -- alles unter
`$TMPDIR` = `/tmp/claude-1000/p58r2`, ausserhalb des Repos; im Baum liegt nichts. Alle
`cmake`-Aufrufe mit der Konfiguration des Runners, am Text nachgelesen
(`agents/baulauf.py:162-165`): `-DCMAKE_BUILD_TYPE=RelWithDebInfo`
`-DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math"`.

---

## Bedingung 1 — ein Ziel ohne Warnsatz bricht die Konfiguration ab

**Erfuellt.** Eigener Baum `bed1/`: oberste Ebene bindet die Kette ein und hat ein Ziel
**mit** dem Aufruf, `add_subdirectory` haengt daneben ein Mitglied, dessen `CMakeLists.txt`
aus `cmake_minimum_required` und `add_library` besteht -- kein Block, kein Aufruf.

**Gegenprobe zuerst, derselbe Baum mit der Kette im Stand vorher** (`7aa76e0^`), sonst
belegt der rote Lauf nur, dass irgendetwas rot wurde:

```
CODE=0   BAUCODE=0
  mit_satz   CXX_FLAGS = … -Wall -Wextra -Werror … -Wformat=2 -fwrapv -fno-fast-math
  ohne_satz  CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20
```

Die Luecke ist damit gemessen: gruener Bau, kein einziger Warnschalter, kein `-Werror`.

**Am heutigen Stand, derselbe Baum:** `CODE=1`, mit Zielname, Art, Verzeichnis, den
fehlenden Schaltern einzeln und der Abhilfe:

```
CMake Error at …/werkzeugkette.cmake:294 (message):
  Der Warnsatz fehlt an folgenden Zielen -- sie wuerden gruen uebersetzen und
  weniger pruefen:
    ohne_satz (STATIC_LIBRARY) in /tmp/claude-1000/p58r2/bed1/unten
        es fehlen: -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow …
        Abhilfe:   fabrik_warnsatz_anlegen(ohne_satz)  -- hinter `add_library`/`add_executable`
```

### Die Positivprobe, die Runde 1 nicht hatte

Runde 1 hat `konsole` aus T13 im echten Arbeitsbereich **ohne** den Aufruf gestellt und
Code 1 gemessen. Damit ist gezeigt, dass der Riegel den schlechten Fall faengt -- **nicht**,
dass ein richtig geschriebenes neues Mitglied durchkommt. Das ist ein Unterschied: Ein
Riegel, der jedes neue Mitglied blockiert, faende denselben roten Lauf und waere unbrauchbar.

Beide Faelle nacheinander, im echten Arbeitsbereich (Kopie aus `git archive HEAD`):

| `konsole/CMakeLists.txt` | erwartet | gemessen |
|---|---|---|
| mit `PROJECT_IS_TOP_LEVEL`-Block und `fabrik_warnsatz_anlegen(konsole)` | Code 0, Zaehler 15 → 16 | `16 uebersetzende Ziele geprueft, alle mit Warnsatz`, `CODE=0`, `BAUCODE=0`, `konsole` mit vollem Satz |
| dieselbe Datei ohne den Aufruf | Code 1 | `konsole (EXECUTABLE) in …/konsole`, `Abhilfe: fabrik_warnsatz_anlegen(konsole)` |

Der Riegel unterscheidet also die beiden Faelle, statt nur laut zu sein.

### Prueft er den Erwerb oder die Ausuebung?

Stehende Prueffrage meiner Rolle, an diesem Riegel zum ersten Mal gestellt. Baum
`entzogen/`: `fabrik_warnsatz_anlegen(z)`, **danach**
`set_target_properties(z PROPERTIES COMPILE_OPTIONS "")`.

```
CODE=1    entzogen (STATIC_LIBRARY) in /tmp/claude-1000/p58r2/entzogen
```

Gefangen. Weil der Riegel am Ende der Konfiguration den **Endzustand** liest und nicht den
Aufruf zaehlt, entzieht sich ihm auch nicht, wer den Satz erst nimmt und dann wieder
ablegt. Das ist die staerkere der beiden moeglichen Bauformen, und sie war nicht gefordert.

## Bedingung 2 — die heutigen Ziele bleiben unberuehrt

**Erfuellt.** Zwei Quellbaeume aus `git archive HEAD`, im zweiten die Kette durch den
Stand `7aa76e0^` ersetzt. Einzigkeit maschinell nachgezaehlt statt behauptet:

```
abweichende Dateien: ['werkzeugkette.cmake']      Zeilen alt/neu: 172 / 325
```

Beide Baeume ueber alle drei Bauwege konfiguriert, alle sechs Laeufe Code 0. Dann jede
`CXX_FLAGS`-Zeile aus jeder erzeugten `flags.make`, mit dem Bauweg als Praefix:

```
Ziele vorher: 30 | nachher: 30
bytegleich: True | Bytes: 11187 11187
```

*Hinweis fuer den naechsten Leser:* Der Bauagent nennt 11953 Bytes, Runde 1 nennt 11817,
ich 11187 -- derselbe Sachverhalt bei drei verschiedenen Pfadpraefixen. Was uebereinstimmt
und worauf es ankommt, ist **Bytegleichheit** und die **Zahl 30**. Wer die Byteangabe
allein vergleicht, vergleicht das Praefix.

Zwei unabhaengige Zeugen daneben:

- Jede der 30 Zeilen einzeln gegen den vollstaendigen 17-Schalter-Satz gehalten:
  `Ziele ohne vollstaendigen Satz: keines`.
- Die Zaehlung des Riegels selbst: 15 + 10 + 5 = 30. Und diese drei Zahlen decken sich mit
  den im **fremdgemessenen** Uebersetzungsbericht aufgezaehlten gebauten Zielen
  (Arbeitsbereich 15, `kern` 10, `pruefstand` 5, einzeln nachgezaehlt) -- ein Zeuge, der
  ohne meine eigenen `cmake`-Laeufe auskommt.

## Bedingung 3 — beide Kaesten gebaut, alle Tests `Passed`

**Erfuellt, fremdgemessen und selbst nachgefahren.** `befunde/uebersetzung-2026-09-03.md`
im **heutigen** Stand (die Datei hat sich seit Runde 1 geaendert, deshalb neu gelesen):
`manifeste: 4`, `ergebnis: ok`, alle zwoelf Aufrufe Code 0, Tests 11 / 8 / 3 / 11, je
`100% tests passed`. Die drei Riegelzeilen 15 / 10 / 5 stehen darin.

Selbst nachgebaut in `$TMPDIR`:

```
arbeitsbereich   BAUCODE=0   CTEST=0   100% tests passed, 0 tests failed out of 11
kern             BAUCODE=0   CTEST=0   100% tests passed, 0 tests failed out of  8
pruefstand       BAUCODE=0   CTEST=0   100% tests passed, 0 tests failed out of  3
```

---

## Ein neuer Befund — ausserhalb der Abnahme, kein Ruecklaufgrund

### Der Satz laesst sich anhaengen und im selben Atemzug abschalten

Der Riegel prueft, ob die Schalter **dastehen**, nicht ob sie **wirken**. Ein Ziel, das
`fabrik_warnsatz_anlegen` ordentlich ruft und danach `-Wno-error -w` anhaengt, hat den
ganzen Satz in `COMPILE_OPTIONS` -- und uebersetzt trotzdem ohne jede Diagnose.

Gemessen an zweimal derselben Quelle, `int f(double d){ int i = d; return i; }`, also
genau der verengenden Umwandlung, gegen die `-Wconversion` gesetzt ist:

| Ziel | Riegel | Bau |
|---|---|---|
| nur `fabrik_warnsatz_anlegen(z)` | `1 … geprueft, alle mit Warnsatz` | **BAUCODE=2**, `error: conversion from 'double' to 'int' may change value [-Werror=float-conversion]` |
| dasselbe **+ `-Wno-error -w`** | `1 … geprueft, alle mit Warnsatz` | **BAUCODE=0**, `Diagnosen=keine` |

Der Riegel sagt in beiden Faellen wortgleich dasselbe. Der zweite Fall ist der
wahrscheinliche: Ein Bauagent, der auf eine Warnung stoesst, die er nicht loesen kann,
haengt `-Wno-error` an -- das ist der billigste Ausweg und er sieht harmlos aus, weil der
Riegel Vollzug meldet.

**Kein Ruecklaufgrund.** Keine der drei Abnahmebedingungen verlangt, die *Wirkung* des
Satzes zu pruefen; Bedingung 1 spricht woertlich von einem Ziel „ohne Warnsatz", und
dieses Ziel hat ihn. Es ist dieselbe Familie wie die zwei Luecken aus Runde 1 und gehoert
in dasselbe Paket -- siehe unten.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Generatorausdruecke in `COMPILE_OPTIONS`.** Runde 1 hat diesen Fall ausdruecklich als
  ungemessen ausgewiesen; jetzt ist er gemessen. Baum `genexp/`: der volle Satz, jeder
  Schalter in `$<$<COMPILE_LANGUAGE:CXX>:…>` eingepackt. Ergebnis `CODE=1` -- der Riegel
  wird **falsch scharf**, weil `IN_LIST` den eingepackten Schalter nicht als den nackten
  erkennt. Das ist kein Befund: Die Fehlrichtung ist die laute. Ein Ziel, das so gebaut
  wird, bricht ab und wird bemerkt, statt still weniger zu pruefen. Heute gibt es kein
  solches Ziel; die Fehlrichtung gehoert aber in den Nachweis, weil sie ohne Messung in
  beide Richtungen haette liegen koennen.
- **Nichtuebersetzende Zielarten.** `INTERFACE_LIBRARY`, `ALIAS`, `UTILITY` (aus
  `add_custom_target` **und** aus `enable_testing()`) in einem Baum neben einem echten
  Ziel: `1 uebersetzende Ziele geprueft`, `CODE=0`. Nicht falsch scharf.
- **Verzeichnisweite Schalter statt des Aufrufs.** Baum `verzeichnisweit/`:
  `add_compile_options(${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})` ohne jeden Aufruf
  von `fabrik_warnsatz_anlegen`. `CODE=0`, und das Ziel traegt den vollen Satz -- CMake
  belegt `COMPILE_OPTIONS` eines Ziels beim Anlegen aus dem Verzeichnis vor. Kein Befund,
  sondern die richtige Bauart: Der Riegel misst das Ergebnis und nicht den Weg dorthin. Wer
  den Satz auf diesem Weg unvollstaendig abschreibt, faellt trotzdem auf.
- **`MODULE_LIBRARY`** (Befund 1 aus Runde 1, unabhaengig bestaetigt): `CODE=0`,
  `0 uebersetzende Ziele geprueft, alle mit Warnsatz`, und das Ziel uebersetzt mit
  `CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20 -fPIC` -- kein
  Warnschalter. Dieselbe Messung zeigt zugleich Befund 2 aus Runde 1: Der Zaehlerstand
  **0** liest sich als Erfolg. Beide stehen in `0060`.
- **Doppelte Registrierung.** In keinem der insgesamt vierzehn Konfigurationslaeufe dieses
  Laufs erschien die Riegelzeile zweimal; `FABRIK_SCHLUSSRIEGEL_GESTELLT` haelt.
- **Nicht geprueft, ausgewiesen:** der Alleinbau eines Mitglieds ohne
  `PROJECT_IS_TOP_LEVEL`-Block -- dort gilt `werkzeugkette.cmake` nicht und der Riegel
  laeuft nicht. Das ist die im Paket benannte Grenze, und dass der Arbeitsbereich diesen
  Fall faengt, ist oben an `konsole` gemessen.

## Was ich mit dem Befund gemacht habe

Der neue Befund ist **nicht** in ein eigenes Paket gegangen. Er aendert dieselben sechs
Zeilen derselben Funktion wie `0060-schlussriegel-blinde-flecken.md`, seine
`dateien`-Liste waere identisch, und der Baulauf muesste beide ohnehin serialisieren --
genau die Begruendung, mit der `0060` seine eigenen zwei Befunde in einem Paket
zusammenfasst. Ein viertes Paket auf denselben sechs Zeilen kostet einen Lauf und bringt
nichts.

`0060` stand zum Zeitpunkt dieses Laufs noch auf `status: vorschlag`, war also nicht
eingeplant. Ich habe dort einen datierten Abschnitt „Befund 3" und eine dritte
Abnahmebedingung ergaenzt; die zwei bestehenden Bedingungen sind unveraendert. **Falls ein
paralleler Lauf das Paket zwischenzeitlich auf `offen` gezogen hat, ist das die Stelle, an
der der Projektmanager hinsehen muss** -- dann ist die dritte Bedingung nachtraeglich
hinzugekommen, und es ist seine Entscheidung, ob sie mitlaeuft oder ein eigenes Paket wird.

## Zum Apparat, nicht zum Paket

1. **Dieses Paket wurde zweimal geprueft.** Ein `geprueft`-Urteil vom selben Tag lag vor;
   das Paket steht weiter auf `status: gebaut`, weil nur der Projektmanager den Status
   nachzieht. Solange zwischen Pruefung und Statusnachzug ein Lauf liegen kann, kann jede
   Rolle dasselbe Paket mehrfach zugewiesen bekommen. Der doppelte Lauf war hier nicht
   wertlos -- er hat einen Befund und eine Positivprobe gebracht, die Runde 1 nicht hatte --,
   aber er war nicht geplant. Fuer den Projektmanager: Es genuegt, den Status nachzuziehen.
2. **Der Commit-Betreff luegt, fuenftes Mal** (0033, 0038, 0046, 0058, und hier wieder).
   Die Aenderung an `werkzeugkette.cmake` liegt in `7aa76e0`
   („testentwickler: 0050-vorratsprobe-belegstellen"), und der Commit `63dc717`
   („kern-pruefer: 0058-…") enthaelt ueberhaupt keine Datei zu 0058, sondern die Pruefung
   0040. Ursache ist wie bisher die verzeichnisweite Sammlung in `lauf.py:committen` bei
   parallelen Laeufen. Kein Befund gegen ein Paket -- aber wer die `dateien`-Liste nicht
   einzeln gegen ihren Vorzustand haelt, prueft hier die falsche Datei.
