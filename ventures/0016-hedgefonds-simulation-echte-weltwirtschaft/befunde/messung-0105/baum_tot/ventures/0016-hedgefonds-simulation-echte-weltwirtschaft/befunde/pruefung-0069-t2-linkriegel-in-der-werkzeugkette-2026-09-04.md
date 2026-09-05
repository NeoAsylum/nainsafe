---
typ: pruefung
paket: 0069-t2-linkriegel-in-der-werkzeugkette
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen selbst nachgemessen -- beide Rotnachweise am unveraenderten Arbeitsbaum reproduziert (Code 1), die drei Bauwege gruen mit dem gelesenen Eigenschaftswert in der Meldung, `ctest` 13 von 14 mit einem fremden Rotstand.
befunde: 1
---

# Pruefung zu Paket 0069

Werkzeugkette: cmake 4.2.3, g++ 15.2.0 (Ubuntu 15.2.0-16ubuntu1).

**Wie gemessen wurde, und warum anders als im Nachweis.** Die Rotnachweise brauchen eine
Zeile im Wurzelmanifest, und das gehoert weder in meine noch in die Dateiliste des
Pakets. Statt einer Abschrift habe ich die Angriffszeile ueber
`-DCMAKE_PROJECT_INCLUDE=<datei>` eingehaengt: CMake bindet diese Datei am Ende des
`project()`-Aufrufs im obersten Verzeichnis ein, also **vor** `add_subdirectory(kern)`.
Damit lief jeder Angriff gegen den **unveraenderten Arbeitsbaum** — keine Kopie, keine
Zeile im Manifest, kein Eintrag in `git status`. Die drei Einhaengedateien liegen unter
`befunde/pruefung-0069/`.

Das ist zugleich der Grund, warum diese Pruefung die Messung des Bauagenten nicht nur
nachliest: Sie ist auf einem anderen Weg entstanden und trifft dieselben Ergebnisse.

---

## Bedingung 1 — die Eigenschaft wird gelesen, der Baum ist gruen, der Wert steht da

Drei Bauwege, alle Code 0, alle mit dem Eigenschaftsnamen **und** dem Wert in der
Meldung:

**Arbeitsbereich** (`cmake -S <vorhaben>`):

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 18 uebersetzende Ziele geprueft, ...
-- Configuring done (0.2s)     → Code 0
```

**Alleinbau des Kerns** (`cmake -S <vorhaben>/kern`): dieselbe Zeile wortgleich, daneben
12 statt 18 uebersetzende Ziele. Code 0.

**Alleinbau des Pruefstands**: Code 0, und der Riegel sagt, dass er nichts hatte, statt
gruen ueber nichts zu melden:

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
```

Die Zahlen weichen vom Nachweis ab (18 statt 17, 12 statt 11). Das ist kein Widerspruch:
Der Baum hat seit dem Bau ein weiteres uebersetzendes Ziel bekommen
(`zustandsausgabe_probe` aus Paket 0010). Der Nullabhaengigkeitsteil der Meldung ist
Zeichen fuer Zeichen derselbe.

**Determinismus der Meldung geprueft**, weil ein Riegel ohne stabile Ausgabe keinen
Regressionstest tragen kann: zwei frische Konfigurationen in getrennte Bauverzeichnisse,
die Riegelzeile `diff`-gleich. Der Riegel laeuft ueber eine benannte Liste
(`FABRIK_NULLABHAENGIG`) und eine feste Eigenschaftsfolge, nicht ueber eine ungeordnete
Menge.

**Dass die Eigenschaft und nicht der Dateitext gelesen wird**, ist nicht am Wortlaut des
Codes abgelesen, sondern an der Wirkung: Beide Rotnachweise unten lassen `kern/CMakeLists.txt`
unberuehrt, und ein Mustervergleich darueber ginge in beiden Faellen leer aus.

---

## Bedingung 2 — beide Rotnachweise reproduziert, am unveraenderten Baum

### Variante A — Verzeichnisform eine Ebene hoeher

Eingehaengt: `link_libraries(m)`, ausgefuehrt am Ende von `project()` und damit vor dem
Abstieg. Gelinkt wird eine vorhandene Bibliothek statt eines Wegwerfziels, damit nicht
der **Warnsatz**riegel zuerst anschlaegt und der Rotnachweis dem falschen Riegel gehoert.

```
CMake Error at werkzeugkette.cmake:695 (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: LINK_LIBRARIES nennt m
    kern: INTERFACE_LINK_LIBRARIES nennt m
    kern_geprueft: LINK_LIBRARIES nennt m
    kern_geprueft: INTERFACE_LINK_LIBRARIES nennt m
  ...
Call Stack (most recent call first):
  werkzeugkette.cmake:780 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
-- Configuring incomplete, errors occurred!      → Code 1
```

Die Messung, die das Paket ausdruecklich sehen wollte, faellt unabhaengig genauso aus:
**Die Verzeichnisanweisung landet in der Zieleigenschaft**, in beiden, und sie trifft
`kern_geprueft` mit. Die Ruecknahmeklausel der Bedingung 2 wird nicht gebraucht.

### Variante B — Zielform aus einem fremden Verzeichnis

Eingehaengt: `cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}" CALL target_link_libraries kern PRIVATE m)`.
Das ist dieselbe Stelle, die Bedingung 2 meint („am Ende des Wurzelverzeichnisses"), und
ausserhalb des Verzeichnisses, in dem `kern` entsteht.

```
CMake Error at werkzeugkette.cmake:695 (message):
  T2 verlangt vom Kern null Fremdabhaengigkeiten.  Diese Ziele linken etwas:

    kern: LINK_LIBRARIES nennt ::@(0x5a513cacf0a0)
    kern: LINK_LIBRARIES nennt m
    kern: LINK_LIBRARIES nennt ::@
    kern: INTERFACE_LINK_LIBRARIES nennt ::@(0x5a513cacf0a0)
    kern: INTERFACE_LINK_LIBRARIES nennt $<LINK_ONLY:m>
    kern: INTERFACE_LINK_LIBRARIES nennt ::@
                                                 → Code 1
```

Der Nachweis nennt die geklammerte Zahl eine Speicheradresse. **Nachgemessen und
bestaetigt:** derselbe Angriff zweimal hintereinander liefert `0x5a513cacf0a0` und
`0x5d50c21f1030`. Sie steht ausschliesslich auf dem Abbruchweg, kein heutiger Test
vergleicht diesen Text, und der Bauagent hat sie ausgeschrieben — deshalb keine
Beanstandung, aber eine Warnung an das naechste Testpaket: Wer diese Meldung je im
Wortlaut prueft, prueft eine Adresse mit.

### Der Arbeitsbaum ist unberuehrt — nachgesehen, nicht geglaubt

- `git status` weist **keine** Aenderung an
  `ventures/0016-…/CMakeLists.txt` aus. Der Weg dieser Pruefung konnte sie gar nicht
  erzeugen; fuer den Weg des Bauagenten gilt sie ebenfalls.
- Die Abschrift unter `befunde/messung-0069/baum/` traegt `werkzeugkette.cmake` und
  `CMakeLists.txt` **byteweise identisch** zum Arbeitsbaum (`diff -q`, beide gleich). Das
  heisst zweierlei: Die Rotnachweise sind gegen genau den Riegel gelaufen, der jetzt im
  Baum steht, und die Angriffszeilen sind wieder heraus.
- Die Praemisse des Annahmevermerks haelt: `agents/baulauf.py:116` sucht Manifeste mit
  `if "befunde" not in m.parts`. Die Abschrift kommt also nicht in den
  Uebersetzungsbericht.

---

## Bedingung 3 — die Probenziele bleiben gruen

Die beiden Zeilen, um die es geht, stehen unveraendert da — `kern/CMakeLists.txt:91` und
`pruefstand/CMakeLists.txt:88`, je `target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})` —
und der Riegel sieht sie nicht an: Er fragt die Eigenschaften **von `kern` und
`kern_geprueft`**, und in denen taucht ein Ziel, das *sie* linkt, nicht auf. Der
Blindtreffer, an dem der ausgeschriebene Mustervergleich gescheitert waere, entsteht hier
gar nicht erst.

Nachgemessen statt hergeleitet:

```
cmake --build   → Code 0
ctest           → 93% tests passed, 1 tests failed out of 14
```

Die 13 gruenen sind die Proben aus `kern/` und `pruefstand/`. Die eine rote ist
`belegstellen_riegel`, und sie gehoert nicht hierher: Ihre Beanstandungen nennen
`rueckstand.md`, `parameter.toml`, `daten/lizenzbefund-reihen.md`,
`daten/einheitenbefund-pwt-baci.md`, `kern/CMakeLists.txt:3` und
`pruefstand/test/vorrat_kernanker_probe.cpp:3` — kein einziges Mal `werkzeugkette.cmake`.
Es ist ein Zitatriegel ueber die Dokumentation, kein Ziel dieses Pakets.

---

## Befund 1 — der Durchgang ueber die Linkschalter sieht die durchgereichte Form nicht

**Ausserhalb der Abnahme, deshalb kein `zurueck`.** Die drei Bedingungen nennen die
Linkschalter nicht; `nachweis.md` fuehrt diesen Durchgang selbst als „Variante C — ueber
die Abnahme hinaus". Ich hebe ein bestandenes Kriterium nicht nachtraeglich an.

Der Abgleich in `werkzeugkette.cmake:661` greift am Anfang oder am Ende des **ganzen**
Eintrags:

```cmake
if("${eintrag}" MATCHES "^-l." OR "${eintrag}" MATCHES "\\.(a|so)$")
```

Ein durchgereichter Linkerschalter beginnt aber mit `-W` und endet auf den Namen. So
erzeugt:

```cmake
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}"
               CALL target_link_options kern INTERFACE "-Wl,-lz")
```

```
-- Nullabhaengigkeitsriegel (T2): 1 Ziel(e) gelesen -- ... kern.INTERFACE_LINK_OPTIONS=[-Wl,-lz]
-- Configuring done      → Code 0
```

Auf der Linkerzeile steht er trotzdem — derselbe Baum, `cmake --build --target festkomma_probe -v`:

```
/usr/bin/c++ -Wl,-lz -Wl,--dependency-file=… festkomma_probe.cpp.o -o festkomma_probe libkern.a
```

Hier scheitert der Bau danach an `cannot find -lz`, weil zlib auf diesem Rechner fehlt.
Das ist der Zufall der Maschine, nicht der Riegel: mit der Bibliothek waere der Bau gruen
und die Fremdabhaengigkeit haengte an jeder Probe.

`INTERFACE` statt `PRIVATE` ist die wirksame Form: `kern` ist statisch und wird selbst nie
gelinkt; ein Linkschalter an ihr wirkt allein ueber die Schnittstelle — und dann bei jedem
Verbraucher.

**Was den Befund abmildert und warum er trotzdem einer ist:** Der Riegel meldet den
gelesenen Wert (`INTERFACE_LINK_OPTIONS=[-Wl,-lz]`), der Schalter steht also im
Uebersetzungsbericht. Blind ist das System nicht. Aber Bedingung 1 verlangt einen Riegel,
der *abbricht*, und ein Messwert in einer Statuszeile bricht nichts ab. Die Datei selbst
schreibt ihre Grenzen sonst aus; diese fehlt dort.

→ Vorschlag `0094-linkschalterform-durchgereichtes-l` (`status: vorschlag`; zuerst als
`0092` geschrieben, dann gewichen, weil ein paralleler Lauf die Nummer belegt hat — unter
`0092-linkschalterform-…` steht nur noch ein Zeiger). Er benutzt
die Zerlegung, die derselbe Riegel gegen Pauschalabschalter schon hat
(`werkzeugkette.cmake:506`), und schreibt die verbleibende Endungsluecke in den Kommentar.
`werkzeugkette.cmake` ist zurzeit von `0076` (`offen`) beansprucht — die Einplanung
gehoert dem Projektmanager.

---

## Wonach ich sonst gesucht und nichts gefunden habe

- **Ein Riegel, der leer laufen und trotzdem gruen melden kann.** Drei Wege geprueft:
  leere Namensliste (`FATAL_ERROR`, Code 1 — im Code bei `:609`), Kernmanifest ohne Ziel
  dieses Namens (`FATAL_ERROR`, `:683`), kein einziges uebersetzendes Ziel
  (`FATAL_ERROR`, `:743`). Der Fall „Ziel nicht da" faellt nicht still gruen aus, sondern
  steht als eigener Satz in der Meldung — am Alleinbau des Pruefstands gesehen.
- **Zu scharf gegen die erlaubten Faelle.** Die Sanitizerschalter an `kern_geprueft`
  stehen in `LINK_OPTIONS` und werden nicht gemeldet; die Probenschleifen in `kern/` und
  `pruefstand/` bleiben unberuehrt. Beides am gruenen Lauf abgelesen.
- **`-NOTFOUND` als Bibliotheksname missverstanden.** Die Pruefung `MATCHES "-NOTFOUND$"`
  greift am Ende der ganzen Zeichenkette; eine Liste, deren letzter Eintrag so endet,
  wuerde ganz verworfen. Kein heutiger Weg erzeugt das, und `0076` arbeitet ohnehin an
  derselben Stelle im Nachbardurchgang.
- **Eine Reihenfolgeluecke im `DEFER`.** Ein `cmake_language(DEFER …)`, das **nach** dem
  des Riegels gestellt wird, laeuft nach ihm und entzieht sich. Das ist die Bauform des
  Schlussriegels seit 0058/0060 und nicht von diesem Paket eingefuehrt; genannt, damit es
  dasteht.
- **Der Zuschnitt auf `kern` und `kern_geprueft`.** T2 verlangt die Nullabhaengigkeit vom
  Kern, nicht vom Baum. Kein Befund, sondern die Vorgabe.

## Eine Beobachtung ausserhalb des Pakets, ohne Vorschlag

Die Aenderung an `werkzeugkette.cmake` liegt im Commit `dffb251`, dessen Betreff
`architekt: 0043-t48-groessen-gegenkraft-5 (40 Dateien)` lautet; der Commit mit dem
Betreff dieses Pakets (`357cb04`) fuehrt statt dessen `kern/src/zustandsausgabe.cpp` und
`kern/include/kern/zustandsausgabe.hpp` aus Paket 0010. **Am Inhalt aendert das nichts** —
der Riegel steht im Baum, ist eingecheckt und laeuft, und der Bauagent hat nur seine eine
Datei angefasst. Aber `<rolle>: <was>` traegt hier nicht mehr, was es tragen soll: Wer
diese Aenderung ueber den Commit-Betreff sucht, findet sie nicht. Das entsteht aus
gleichzeitigen Laeufen im selben Arbeitsbaum und gehoert dem Projektmanager oder dem
Verbesserer, nicht einem Bauagenten — deshalb kein Paket von mir.

## Was in `befunde/pruefung-0069/` liegt

Die drei Einhaengedateien, mit denen jeder Nachweis oben in einem Aufruf wiederholbar
ist, ohne eine Zeile im Baum zu aendern:

```
cmake -S <vorhaben> -B <bau> -DCMAKE_PROJECT_INCLUDE=<vorhaben>/befunde/pruefung-0069/angriff-a.cmake
```

| Datei | Fall | erwartet |
|---|---|---|
| `angriff-a.cmake` | `link_libraries(m)` vor dem Abstieg | Code 1 |
| `angriff-b.cmake` | `target_link_libraries(kern PRIVATE m)` von aussen | Code 1 |
| `angriff-c-linkerzeile.cmake` | `target_link_options(kern INTERFACE "-Wl,-lz")` | Code 0 — Befund 1 |
