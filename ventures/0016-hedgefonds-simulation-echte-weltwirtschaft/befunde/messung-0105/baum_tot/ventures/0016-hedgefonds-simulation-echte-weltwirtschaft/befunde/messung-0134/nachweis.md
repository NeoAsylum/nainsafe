---
typ: messung
paket: 0134-sperrebindung-jeder-kernquelle
rolle: kernbauer
datum: 2026-09-05
bezugsstand: 4ee0f79 (letzter Commit vor dem Lauf)
---

# Nachweis zu 0134: der Sperrebindungsriegel

Alles hier ist gemessen. `bindungsriegel.py` faehrt die Baeume und laesst sich
wiederholen; `lauf-2026-09-05.txt` ist seine Ausgabe im Wortlaut, Exitcode **0**,
**0 Abweichungen**. `CMakeLists-vorher.txt` ist die Fassung vor der Aenderung, als
Kopie und nicht als Git-Verweis -- ein Fremdlauf verschiebt HEAD, die Kopie nicht.
(Genau das ist eingetreten: Commit `3840367` hat diese Aenderung unter fremdem
Betreff mitgenommen.)

## Die Abnahme, Bedingung fuer Bedingung

| Abnahme verlangt | Baum | gemessen |
|---|---|---|
| unveraenderter Baum konfiguriert und laeuft in beiden Profilen gruen | 1 | vier Laeufe -- `kern` allein und Arbeitsbereich, je `FABRIK_SANITIZER=ON` und `OFF`. Alle drei Schritte Code 0, 10 bzw. 15 Proben bestanden. |
| Quelle ohne die Include-Zeile bricht beim Konfigurieren ab | 3 | `cmake -S` Code 1, Meldung nennt `'src/luecke.cpp'` und die verletzte Bedingung ("bindet \"kern/sperre.hpp\" nicht"). |
| Quelle mit der Zeile, aber nicht an letzter Stelle, bricht ebenso ab | 5 | `cmake -S` Code 1, Meldung nennt `'src/luecke.cpp'`, die andere Bedingung ("nicht als letzten `#include`") und den tatsaechlichen Schluss `#include <cstdint>`. |

## Was daneben gemessen ist, weil es sonst nichts beweist

**Der Riegel faengt nicht einfach alles.** Zu jedem Baum, der neu rot wird, gehoert
einer, der es nicht darf. Baum **2** und **4** sind dieselben Verstoesse auf der
Fassung **ohne** Riegel: beide Code 0 durch `cmake -S`, `--build` und `ctest`.

Baum 2 ist zugleich die Luecke selbst, gemessen statt zitiert: `src/luecke.cpp`
rechnet auf `double` (gegen T4) und fuehrt eine eigene Fassung der Strichrechnung mit
`__builtin_add_overflow` (gegen T7 Massnahme 4.2). Sie wird in `kern` **und** in
`kern_geprueft` uebersetzt und besteht jede Probe.

Baum 4 ist absichtlich so zugeschnitten, dass der Uebersetzer den Verstoss **nicht**
sehen kann: Der nachgestellte Kopf ist ein bereits gebundener, seine Einbindesperre
macht die Zeile folgenlos. Der erste Versuch nahm `<cstddef>`, und der Baum ohne
Riegel wurde rot -- `max_align_t` nennt `long double`. Damit haette der Nachweis nur
gezeigt, dass die Vergiftung wirkt, nicht dass der Riegel etwas faengt.

**Der Riegel greift auch bei einer Aenderung an einer vorhandenen Quelle.**
`CONFIGURE_DEPENDS` am Quellensammler bemerkt nur neue und verschwundene Dateien; wer
die Include-Zeile aus einer bestehenden Quelle entfernt, aendert die Dateiliste nicht.
Baum **6** und **7** messen das Paar: `src/werte.cpp` verliert die Zeile, danach nur
`cmake --build` ohne neues `cmake -S`. Ohne `CMAKE_CONFIGURE_DEPENDS` (Baum 6) Code 0
-- der Bau laeuft still weiter. Mit ihm (Baum 7) Code 2, und der Abbruch nennt
`'src/werte.cpp'`.

## Grenzen, die der Riegel hat

Er liest Zeilen, er verarbeitet nicht vor. Eine `#include`-Zeile in einem `/* */`-Block
oder hinter `#if 0` zaehlt er mit. Er deckt `kern/src`, nicht `kern/test`. Ein zweites
Vorkommen des Kopfes weiter oben faengt er nicht ab -- `#pragma once` macht es
folgenlos, und die Reihenfolgebedingung haelt trotzdem. Alle drei stehen so auch im
Kommentar neben dem Riegel.

## Die Aenderung selbst

`kern/CMakeLists.txt`, 94 -> 193 Zeilen: **99 hinzugefuegt, 0 entfernt**. Die alte
Datei ist Zeile fuer Zeile in der neuen enthalten; verglichen wurde gegen die Kopie
oben, nicht gegen `HEAD`.
