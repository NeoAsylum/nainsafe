---
typ: pruefung
paket: 0060-schlussriegel-blinde-flecken
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen an eigenen Wegwerf-Baeumen je gegen den Stand vorher und nachher gefahren, dazu die drei Bauwege und der Bytevergleich aller 15 CXX_FLAGS.
befunde: 1
---

# Paket 0060 ist erfuellt; ein vierter Weg an der Sperrliste vorbei ist offen

Werkzeugkette g++ 15.2.0 / cmake 4.2.3, dieselbe wie die festgenagelte. Alle Messungen
eigene Laeufe unter `$TMPDIR/kp0060`, nichts im Repo angelegt oder veraendert.

**"vorher" und "nachher"** sind in jeder Zeile unten dieselbe Datei aus zwei Staenden:
`git show 788a917:.../werkzeugkette.cmake` gegen den Arbeitsstand. Maschinell nachgezaehlt,
dass die beiden sich genau an den drei erwarteten Stellen unterscheiden -- `MODULE_LIBRARY`
0 -> 2 Vorkommen, `pauschalmuster` 0 -> 2, `gezaehlt EQUAL 0` 0 -> 1 -- und dass in zwei
Kopien des ganzen Vorhabens **genau eine** Datei abweicht (`werkzeugkette.cmake`).

**Zum Fundort, weil er irrefuehrt:** Die Aenderung an `werkzeugkette.cmake` steht in Commit
`1a4d240` mit dem Betreff "testentwickler: 0061-kernanker-sichtbarkeit", nicht in `24aa5aa`
"kernbauer: 0060-..." -- der traegt nur den Nachweistext und drei fremde Dateien. Sechster
Fall derselben Verwechslung; geprueft habe ich die `dateien`-Liste des Pakets gegen den
Vorzustand, nicht den Commit.

## Bedingung 1 -- `MODULE_LIBRARY` ohne Warnsatz bricht ab

Baum: `add_library(x MODULE q.cpp)`, kein `fabrik_warnsatz_anlegen`, blank konfiguriert.

```
vorher    CODE=0   -- Warnsatz-Schlussriegel: 0 uebersetzende Ziele geprueft, alle mit Warnsatz.
nachher   CODE=1   x (MODULE_LIBRARY) in /tmp/claude-1000/kp0060/modul-nachher
                       es fehlen: -Wall -Wextra -Werror -Wconversion -Wsign-conversion ...
                       Abhilfe:   fabrik_warnsatz_anlegen(x)  -- hinter `add_library`
```

Die Meldung nennt `x (MODULE_LIBRARY)` im Wortlaut, wie verlangt. Gegenprobe "vorher"
gefahren: derselbe Baum kam vollstaendig durch, und die Zahl `0` stand daneben.

**Dazu die Positivrichtung, die die Bedingung nicht verlangt** -- ohne sie belegte CODE=1
nur, dass *irgendein* `MODULE_LIBRARY` rot wird, nicht dass das richtige gruen bleibt:
derselbe Baum **mit** `fabrik_warnsatz_anlegen(x)` ergibt nachher CODE=0 und
`1 uebersetzende Ziele geprueft`.

**Die Artenliste ist jetzt vollstaendig, nicht nur laenger.** `BUILDSYSTEM_TARGETS` fuehrt
weder importierte noch `ALIAS`-Ziele; was danach bleibt, sind die fuenf gelisteten Arten
plus `INTERFACE_LIBRARY` und `UTILITY`, und die beiden erzeugen keinen Uebersetzeraufruf.
Es fehlt also kein sechstes Glied mehr.

## Bedingung 2 -- Nullriegel, drei Bauwege, Bytevergleich

Baum `leer`: bindet die Kette ein, legt kein Ziel an.

```
vorher    CODE=0   -- Warnsatz-Schlussriegel: 0 uebersetzende Ziele geprueft, alle mit Warnsatz.
nachher   CODE=1   fabrik_schlussriegel: kein einziges uebersetzendes Ziel unter
                   '.../leer-nachher' gesehen.
```

Zweiter Baum, den die Bedingung nicht verlangt: nur `add_library(i INTERFACE)` und
`add_custom_target(u)`, also Ziele, die der Riegel absichtlich uebergeht. Vorher CODE=0,
nachher CODE=1 -- der Nullriegel greift auch dort, wo Ziele **da** sind, aber keines
uebersetzt. Das ist die im Paket ausdruecklich benannte Grenze ("nur dort, wo ueberhaupt
ein Ziel erwartet wird"), kein Widerspruch zur Abnahme; im Repo gibt es heute keinen
solchen Baum, der die Kette einbindet.

**Die drei Zahlen, selbst gemessen** -- mit den Schaltern des Runners
(`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`, am Text von
`baulauf.py:162-164` nachgelesen), je vorher und nachher, alle sechs mit Code 0:

```
Arbeitsbereich  15        kern allein  10        pruefstand allein  5        15 = 10 + 5
```

Dritter, fremder Zeuge ohne meine Laeufe: `befunde/uebersetzung-2026-09-04.md` nennt
dieselben 15 / 10 / 5 und zaehlt im Bauabschnitt 15 gebaute Ziele auf.

**Bytevergleich aller `CXX_FLAGS` des Arbeitsbereichs, vorher gegen nachher:** je **15**
`flags.make`, mit dem Pfad innerhalb des Bauverzeichnisses als Praefix sortiert,
`vorher == nachher` -> **True**. Verglichen wurde erst, nachdem die beiden Baumwurzeln
textlich normalisiert waren; ohne das vergleicht man Pfade statt Schalter. Zusaetzlich,
und nur zusaetzlich: `cmake --build --parallel` Code 0, `ctest` 11/11 `Passed`.

**Die zwei uebrigen Manifeste des Runners nachgesehen statt angenommen** --
`baulauf.py:116` baut jede `CMakeLists.txt` ausser unter `befunde/`, und das sind fuenf,
nicht drei. `pruefstand/bau/pruefung-0019/CMakeLists.txt` und
`werkzeuge/belegstellen/CMakeLists.txt` binden `werkzeugkette.cmake` beide **nicht** ein
(gegrept, beide ohne Fundstelle) und laufen deshalb nicht in den Nullriegel -- obwohl die
zweite gar kein Ziel anlegt und mit Einbindung genau der Fehlalarm waere, den das Paket
beschreibt. Der Bericht von heute bestaetigt es: beide Code 0, beide ohne Riegelzeile.

## Bedingung 3 -- Warnsatz plus Pauschalabschalter bricht ab

Viermal dieselbe Quelle `int f(double d){ int i = d; return i; }`, je ein eigener Baum:

| Baum | Zusatz am Ziel | vorher | nachher |
|---|---|---|---|
| `nurwarnsatz` | (nichts) | CODE=0, BAUCODE=2 `[-Werror=float-conversion]` | CODE=0, BAUCODE=2 |
| `pauschal` | `-Wno-error -w` | CODE=0, `1 ... alle mit Warnsatz`, **BAUCODE=0, keine Diagnose** | **CODE=1** |
| `klassenweise` | `-Wno-error=float-conversion` | CODE=0, BAUCODE=0, nur noch `[-Wfloat-conversion]` | **CODE=1** |
| `einzeln` | `-Wno-conversion` | CODE=0 | CODE=0 |

Meldung im Fall `pauschal`, nachher: `z (STATIC_LIBRARY) in ... / hebt den Satz wieder auf:
-Wno-error -w` -- sie nennt den Schalter. Im Fall `klassenweise` entsprechend
`-Wno-error=float-conversion`.

Die Zeile `nurwarnsatz` traegt den Rest: Ohne sie belegte der gruene Bau von `pauschal`
nichts, weil die Quelle vielleicht gar nicht verstiesse. Die Zeile `einzeln` traegt die
Gegenrichtung -- eine benannte Unterdrueckung bleibt zugelassen.

**Zwei weitere Formen gemessen, die die Bedingung nicht nennt:** `-w` allein am Ziel wird
gefangen (CODE=1), und `add_compile_options(-w)` **verzeichnisweit** vor dem `add_library`
ebenfalls (CODE=1) -- CMake fuellt die Zielsicht daraus vor, der Riegel sieht es also. Die
zweite ist die realistischste Form ueberhaupt und war offen geblieben; sie haelt.

Falschalarm ausgeschlossen: Die 15 Warnschalter und die Sanitizerschalter der
`_geprueft`-Ziele treffen die Sperrliste nicht -- die drei Bauwege oben laufen mit vollem
Satz durch.

## Was ich sonst gesucht und **nicht** gefunden habe

- **Haengt ein Skript oder eine Probe am alten Wortlaut?** Die Erfolgsmeldung heisst jetzt
  "... alle mit Warnsatz **und ohne Pauschalabschalter**". Ueber `*.py`, `*.cpp`, `*.hpp`,
  `*.cmake`, `*.txt`, `*.sh`, `*.toml` gegrept: einzige Fundstelle ist die `message`-Zeile
  selbst. Kein Befund.
- **Bricht der Riegel ueber-scharf ab?** Fuer jeden Negativnachweis oben steht ein
  Positivnachweis daneben (Modul mit Satz, `-Wno-conversion`, drei Bauwege, 11/11 Tests).
  Kein Befund.
- **Ist der Zaehler noch der alte?** 15 / 10 / 5 vorher wie nachher, und 15 = 10 + 5.
  Kein Befund.

## Befund 1 (ausserhalb der Abnahme): `SHELL:` fuehrt an der Sperrliste vorbei

Der Riegel vergleicht jeden Eintrag von `COMPILE_OPTIONS` **als ganze Zeichenkette** gegen
`^-w$` und `^-Wno-error(=.+)?$`. CMakes `SHELL:`-Praefix ist genau der dokumentierte Weg,
mehrere Schalter in **einem** Eintrag zu uebergeben -- der Eintrag heisst dann
`SHELL:-Wno-error -w` und trifft kein Muster, waehrend der Uebersetzer beide Schalter
bekommt. Gemessen am Arbeitsstand, dieselbe Quelle wie oben:

```
target_compile_options(z PRIVATE "SHELL:-Wno-error -w")
   -> Riegel: CODE=0, "1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne
      Pauschalabschalter."   BAUCODE=0, keine einzige Diagnose
```

Das ist wortgleich die Signatur aus Befund 3 des Pakets, nur eine Schreibweise weiter.
**Der Generatorausdruck ebenso** (`$<1:-w>` und `$<$<CONFIG:Release>:-w>`, beide gemessen:
Riegel gruen, Bau gruen, keine Diagnose) -- der ist in Paket 0060 unter "Nicht abgedeckt"
ausdruecklich ausgewiesen, `SHELL:` nicht. Zur Vollstaendigkeit: `"-Wno-error -w"` als
**eine** Zeichenkette ohne `SHELL:` ist kein Loch, dort bricht der Bau (BAUCODE=2).

**Warum das kein `zurueck` ist:** Abnahmebedingung 3 nennt den Nachweis woertlich --
`target_compile_options(z PRIVATE -Wno-error -w)` -- und der ist erbracht. Ein Bauagent,
der `SHELL:` dazugenommen haette, waere aus seiner Abnahme herausgelaufen. Der Befund wird
Vorschlag `0062-sperrliste-je-wort-statt-je-eintrag`; dort steht der Weg, den ich dafuer
gebaut und an den drei Bauwegen auf Falschalarm gemessen habe.
