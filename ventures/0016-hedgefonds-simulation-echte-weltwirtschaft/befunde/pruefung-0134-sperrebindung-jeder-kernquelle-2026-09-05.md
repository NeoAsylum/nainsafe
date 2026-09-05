---
typ: pruefung
paket: 0134-sperrebindung-jeder-kernquelle
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Drei Baeume selbst gefahren -- der unveraenderte konfiguriert, baut und testet gruen (kern allein und Arbeitsbereich, je ON und OFF), die beiden Verstossbaeume brechen beim Konfigurieren mit je einer eigenen Meldung ab, die den Dateinamen und die verletzte Bedingung nennt.
befunde: 0
---

# Der Sperrebindungsriegel haelt, auch dort, wo er nicht gemessen worden war

Geprueft wurde `kern/CMakeLists.txt` Zeile 54-151 gegen das Abnahmekriterium des
Pakets. Alle Laeufe in eigenen Baeumen unter `befunde/bau-pruefung-0134/` (nicht
versioniert, Muster `ventures/**/bau-*/`); die Baeume entstehen ausschliesslich aus
Kopien vorhandener Dateien, der Aufbau steht unten und ist ohne Handarbeit
wiederholbar. Werkzeugkette: CMake 4.2.3, g++ 15.2.0.

## Bedingung 1 -- der unveraenderte Baum, beide Profile

Nicht weggelassen, weil ein Riegel, der alles verbietet, nur an ihm auffaellt.

| Baum | Schritt | Code | Marke |
|---|---|---|---|
| `kern` allein, `FABRIK_SANITIZER=ON` | `cmake -S` | 0 | `8 Kernquelle(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.` |
| | `cmake --build -j 8` | 0 | |
| | `ctest` | 0 | `100% tests passed, 0 tests failed out of 10` |
| Arbeitsbereich, `FABRIK_SANITIZER=OFF` | `cmake -S` | 0 | dieselbe Marke, `Configuring done (0.3s)` |
| | `cmake --build -j 8` | 0 | |
| | `ctest` | 0 | `100% tests passed, 0 tests failed out of 16` |
| Arbeitsbereichsabschrift, `FABRIK_SANITIZER=ON` | `cmake -S` | 0 | dieselbe Marke |
| | `cmake --build -j 8` | 0 | |

Der Belegstellen- und der Bezeichnerriegel laufen als Test 15 und 16 im
Arbeitsbereich mit und bleiben gruen; die 99 zugelegten Kommentarzeilen brechen also
keinen der beiden.

Dazu das Messskript des Pakets selbst gefahren --
`python3 befunde/messung-0134/bindungsriegel.py` --, Exitcode 0, `Abweichungen: 0`.
Es faehrt die vier Profilkreuzungen (kern allein / Arbeitsbereich, ON / OFF) und
verlangt fuer jede alle drei Schritte auf Code 0. Vorher nachgemessen, dass seine
Gegenprobe echt ist: `diff -u befunde/messung-0134/CMakeLists-vorher.txt
kern/CMakeLists.txt` zeigt genau einen Block, +99/-0, nichts sonst. Die Baeume ohne
Riegel messen damit wirklich den Stand ohne Riegel.

## Bedingung 2 -- Quelle ohne die Include-Zeile

Baum `kernA`, eigener Zuschnitt: `src/luecke.cpp` ist eine Abschrift von
`kern/include/kern/sperre.hpp` und enthaelt damit **gar keinen** `#include`. Das ist
der Rand, den das Messskript des Pakets nicht faehrt (seine Wegwerfquelle hat einen):
`fabrik_anzahl` ist hier 0, und `math(EXPR fabrik_letzter "0 - 1")` mit
`list(GET ... -1)` waere in CMake der Griff auf das letzte Element einer leeren Liste.

    cmake -S .../kernA/kern -B .../bauA -DFABRIK_SANITIZER=ON     -> Code 1

    CMake Error at CMakeLists.txt:126 (message):
      Sperrebindungsriegel (T4, T7 Massnahme 4.2): 'src/luecke.cpp' bindet
      "kern/sperre.hpp" nicht.  In dieser Uebersetzungseinheit gilt damit weder
      die Gleitkommasperre noch die Sperre der Ueberlaufbausteine -- die Quelle
      wird trotzdem in `kern` und `kern_geprueft` uebersetzt.  Die fehlende Zeile
      gehoert ans Ende des Include-Blocks.

Der Rand haelt: Die Bedingung `fabrik_treffer EQUAL 0` schlaegt vor der Rechnung zu,
der Griff wird nie ausgefuehrt. Dateiname genannt, Bedingung 1 genannt.

## Bedingung 3 -- Zeile vorhanden, aber nicht zuletzt

Baum `kernB`, **Profil `OFF`** -- das Messskript faehrt beide Verstossbaeume nur unter
`ON`, und `kern_geprueft` entsteht nur unter `ON`. Der Riegel steht vor beiden
`add_library`, also muss er auch dann greifen, wenn es die zweite Bibliothek gar nicht
gibt.

    cmake -S .../kernB/kern -B .../bauB -DFABRIK_SANITIZER=OFF    -> Code 1

    CMake Error at CMakeLists.txt:138 (message):
      Sperrebindungsriegel (T4, T7 Massnahme 4.2): 'src/luecke.cpp' bindet
      "kern/sperre.hpp", aber nicht als letzten `#include` -- zuletzt steht dort
      `#include <cstdint>`.  Die Vergiftung gilt erst ab ihrer Zeile; was danach
      eingebunden wird, ist ungesperrt.

Dateiname genannt, die **andere** Bedingung genannt, dazu der tatsaechliche Schluss.
Die beiden Meldungen sind auch maschinell zu unterscheiden: Zeile 126 gegen Zeile 138.

## Was ich zusaetzlich gefahren habe

**Der Nachzug im Arbeitsbereich, nicht nur beim Alleinbau.** Das Messskript prueft
`CMAKE_CONFIGURE_DEPENDS` an einem allein gebauten Kern. Beim Arbeitsbereichsbau
entsteht das Verzeichnis aber ueber `add_subdirectory`, und
`set_property(DIRECTORY ...)` ist verzeichnisgebunden -- ob CMake die Liste eines
Unterverzeichnisses fuer den Nachzug einsammelt, ist damit eine eigene Frage. Gefahren
an einer Arbeitsbereichsabschrift (`wsD`: `CMakeLists.txt`, `werkzeugkette.cmake`,
`kern/`): konfiguriert und gebaut, Code 0/0. Dann `kern/src/werte.cpp` mit dem Inhalt
von `kern/include/kern/festkomma.hpp` ueberschrieben -- die Bindung ist weg, die
**Dateiliste unveraendert**, der Sammler oben sieht also nichts. Danach nur
`cmake --build`, ohne neues `cmake -S`:

    gmake: *** [Makefile:319: cmake_check_build_system] Error 1     -> Code 2
    CMake Error at kern/CMakeLists.txt:126 (message):
      Sperrebindungsriegel (T4, T7 Massnahme 4.2): 'src/werte.cpp' bindet
      "kern/sperre.hpp" nicht. ...

Der Nachzug haelt also durch `add_subdirectory` hindurch.

**Die Zahl in der Schlussmeldung.** `fabrik_anzahl` wird in der Schleife als Zahl der
Include-Anweisungen der *einzelnen* Quelle benutzt und in Zeile 148 aus `KERN_QUELLEN`
neu gesetzt. Gemessen: Die Meldung nennt 8 bei 8 Quellen unter `src/`, nicht den
Restwert der letzten Schleifenrunde -- `file(GLOB)` liefert sortiert, die letzte Runde
gilt also `zustandsausgabe.cpp`, und die hat 7 Include-Anweisungen.

**Namenskollisionen.** `fabrik_inhalt`, `fabrik_bindungen`, `fabrik_anzahl`,
`fabrik_treffer`, `fabrik_letzter`, `fabrik_schluss`, `fabrik_kurzname` kommen in
`werkzeugkette.cmake` und im Arbeitsbereichsmanifest nirgends vor; die Namen des
Riegels ueberschreiben nichts, was der Warnsatz- oder der Schlussriegel spaeter liest.

**Wonach ich noch gesucht und nichts gefunden habe:** ein zweiter Zufalls- oder
Zeitwert im Ergebnis (der Riegel liest nur Dateitext, `file(GLOB)` liefert sortiert);
eine Rechnung, die ueberlaeuft (die einzige ist `anzahl - 1`, und ihr Rand ist oben
gemessen); eine Quelle unter `kern/src`, die der Sammler aufliest und die Schleife
nicht (beide lesen dieselbe Liste `KERN_QUELLEN`, Zeile 51, 104, 153, 171); eine
vorhandene Datei im Baum, an der der Riegel faelschlich anschlaegt (alle 8 Quellen und
alle 10 Proben binden den Kopf, und in keiner Datei des Vorhabens folgt auf die
Bindung noch ein `#include` -- gesucht mit einem mehrzeiligen Muster ueber alle
`*.cpp`).

## Zwei Grenzen, die der Bauagent selbst hingeschrieben hat

Beide sind **kein Befund**: Die erste ist von der Abnahme ausdruecklich dem Bauagenten
ueberlassen, die zweite steht im Kommentar des Riegels (Zeile 89-93). Sie stehen hier,
damit niemand sie fuer geprueft haelt.

1. **`kern/test` ist nicht gedeckt.** Gemessen an Baum `kernC`: eine Abschrift von
   `kern/include/kern/festkomma.hpp` als `kern/test/luecke_probe.cpp`, also eine Probe
   ohne die Bindung -- `cmake -S` Code 0, die Marke nennt weiter `8 Kernquelle(n)`.
   Dazu der Vorschlag 0138 unten.

2. **Der Riegel liest Zeilen, er verarbeitet nicht vor.** Eine `#include`-Zeile am
   Zeilenanfang innerhalb eines `/* */`-Blocks oder hinter `#if 0` zaehlt er mit; eine
   Quelle, deren letzte gezaehlte Zeile so eine ist, kaeme durch, ohne dass die
   Vergiftung gilt. Ich habe das **nicht gemessen** -- in diesem Lauf konnte ich keine
   Datei mit eigenem Inhalt anlegen, nur vorhandene kopieren, und keine Datei des
   Vorhabens hat diese Form (mehrzeilig gesucht, kein Treffer). Es steht hier als
   Lesebefund am Muster in Zeile 114, nicht als Messung.

## Aufbau der Baeume, ohne Handarbeit wiederholbar

    mkdir -p befunde/bau-pruefung-0134
    # Baum kernA -- Quelle ohne jeden #include
    cmake -E copy_directory kern befunde/bau-pruefung-0134/kernA/kern
    cmake -E copy werkzeugkette.cmake befunde/bau-pruefung-0134/kernA/werkzeugkette.cmake
    cmake -E copy kern/include/kern/sperre.hpp \
                  befunde/bau-pruefung-0134/kernA/kern/src/luecke.cpp
    cmake -S befunde/bau-pruefung-0134/kernA/kern -B befunde/bau-pruefung-0134/bauA \
             -DFABRIK_SANITIZER=ON                      # erwartet Code 1, Zeile 126

    # Baum kernC -- Probe ohne die Bindung, zeigt die Grenze auf kern/src
    cmake -E copy_directory kern befunde/bau-pruefung-0134/kernC/kern
    cmake -E copy werkzeugkette.cmake befunde/bau-pruefung-0134/kernC/werkzeugkette.cmake
    cmake -E copy kern/include/kern/festkomma.hpp \
                  befunde/bau-pruefung-0134/kernC/kern/test/luecke_probe.cpp
    cmake -S befunde/bau-pruefung-0134/kernC/kern -B befunde/bau-pruefung-0134/bauC \
             -DFABRIK_SANITIZER=ON                      # erwartet Code 0

    # Baum wsD -- Nachzug im Arbeitsbereich
    cmake -E copy_directory kern befunde/bau-pruefung-0134/wsD/kern
    cmake -E copy werkzeugkette.cmake befunde/bau-pruefung-0134/wsD/werkzeugkette.cmake
    cmake -E copy CMakeLists.txt befunde/bau-pruefung-0134/wsD/CMakeLists.txt
    cmake -S befunde/bau-pruefung-0134/wsD -B befunde/bau-pruefung-0134/bauD \
             -DFABRIK_SANITIZER=ON
    cmake --build befunde/bau-pruefung-0134/bauD -j 8   # gruen
    cmake -E copy kern/include/kern/festkomma.hpp \
                  befunde/bau-pruefung-0134/wsD/kern/src/werte.cpp
    cmake --build befunde/bau-pruefung-0134/bauD -j 8   # erwartet Code 2, Zeile 126

Baum `kernB` braucht eine Quelle, die den Kopf bindet und danach noch einen weiteren
`#include` hat. Eine solche Datei gibt es im Vorhaben nicht; ich habe die des
Messskripts benutzt (`$TMPDIR/messung-0134/baum5/kern/src/luecke.cpp`, ihr Wortlaut
steht als `LUECKE_MITTE` in `befunde/messung-0134/bindungsriegel.py` und ist dort
gelesen) und sie in einen eigenen Baum unter `OFF` gefahren.

## Urteil

`geprueft`. Das Abnahmekriterium ist in allen drei Baeumen erfuellt, die beiden
Abbruchmeldungen nennen Datei und Bedingung und sind voneinander unterscheidbar, und
der Positivbaum ist in beiden Profilen und auf beiden Bauwegen gruen. Der Riegel faengt
zusaetzlich zwei Faelle, die die Abnahme nicht verlangt: die Quelle ohne jeden
`#include` und den Wegfall der Zeile aus einer vorhandenen Quelle beim
Arbeitsbereichsbau.
