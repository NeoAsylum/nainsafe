# Der Belegstellenriegel -- Paket 0059.
#
# Diese Datei wird auf zwei Wegen konfiguriert, und beide muessen tragen:
#
#   1. ueber den Arbeitsbereich -- `../../CMakeLists.txt` fuehrt `werkzeuge/belegstellen`
#      seit Paket 0059 in `FABRIK_MITGLIEDER`;
#   2. allein -- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder
#      `cmake`, `--build` und `ctest`.
#
# Weg 2 ist der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt. Genau das
# stand hier bis zum 2026-09-04 -- der Uebersetzungsbericht jenes Tages fuehrt dieses
# Verzeichnis mit `No project() command is present` und `No tests were found!!!` und
# meldete trotzdem `ergebnis: ok`. Ein gruener Bericht ueber nichts.

cmake_minimum_required(VERSION 3.22)

project(belegstellen LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../werkzeugkette.cmake)
  enable_testing()
endif()

# Die Quelle wird **einzeln genannt und nicht eingesammelt**. Ein `file(GLOB *.cpp)`
# zoege hier `probe.tmp` und alles weitere Liegengebliebene mit in die Uebersetzung und
# machte den ganzen Kasten rot statt nur dieses Paket. Anders als bei `kern` und
# `pruefstand` ist das kein Verzicht: Dieses Verzeichnis traegt genau ein Programm, und
# Paket 0067 legt keine zweite Datei daneben, sondern schreibt in dieselbe.
add_executable(belegstellen_riegel belegstellen_riegel.cpp)
fabrik_warnsatz_anlegen(belegstellen_riegel)

# ADR 0011, Massnahme 2. Der Riegel rechnet nichts, aber er indiziert Zeichenketten
# rueckwaerts -- genau die Fehlerklasse, die C++ nicht selbst abfaengt und die sich
# sonst erst beim Kaeufer zeigt.
if(FABRIK_SANITIZER)
  target_compile_options(belegstellen_riegel PRIVATE ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(belegstellen_riegel    PRIVATE ${FABRIK_SANITIZER_SCHALTER})
endif()

# Die Wurzel kommt von CMake, nicht aus dem Programm -- Abnahmebedingung 1. Sie zeigt
# auf das Vorhaben, nicht auf dieses Verzeichnis, und ist auf beiden Bauwegen dieselbe:
# `CMAKE_CURRENT_SOURCE_DIR` ist in beiden Faellen dieses Verzeichnis.
get_filename_component(FABRIK_VORHABEN_WURZEL
                       ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

add_test(NAME belegstellen_riegel
         COMMAND belegstellen_riegel ${FABRIK_VORHABEN_WURZEL})

# ---------------------------------------------------------------------------
# Die Gegenprobe des Riegels -- Paket 0147
#
# `befunde/messung-0147/messung.py` beantwortet die Frage, die der Selbsttest ueber sich
# selbst nicht beantworten kann: ob seine Faelle etwas **messen** oder nur laufen. Neun
# Mutanten von `belegstellen_riegel.cpp` gegen die Tabellen `ORTSFAELLE` und
# `FORMFAELLE`, dazu die Fassung vor dem Paket und die danach im selben Aufruf ueber
# denselben Arbeitsbaum.
#
# **Warum sie hier steht und nicht nur in `befunde/`:** `agents/baulauf.py` sucht jede
# `CMakeLists.txt` und ruft `cmake`, `--build` und `ctest` -- ein Skript, das in keinem
# dieser drei vorkommt, laeuft in dieser Fabrik nirgends. Genau daran ist dieses Paket am
# 2026-09-07 einmal zurueckgelaufen: Der Quelltext war vollstaendig, die Messung war nie
# ausgefuehrt. Bei `befunde/messung-0180/messen.py` blieb derselbe Zustand ein halbes Jahr
# unbemerkt, und vier ihrer fuenf Mutanten trafen laengst ins Leere. Eine Probe, die
# niemand faehrt, verfaellt still.
#
# Kein `if(EXISTS ...) add_test() endif()`: Genau diese Bauform laesst eine Probe
# verschwinden, sobald jemand die Datei verschiebt, und meldet danach eine gruene Abnahme
# ueber einen Baum ohne sie. Fehlt die Datei, bricht die Konfiguration ab und sagt, wo sie
# erwartet wird.
get_filename_component(FABRIK_MESSUNG_0147
                       ${FABRIK_VORHABEN_WURZEL}/befunde/messung-0147/messung.py
                       ABSOLUTE)

if(NOT EXISTS ${FABRIK_MESSUNG_0147})
  message(FATAL_ERROR
          "Die Gegenprobe des Belegstellenriegels fehlt: ${FABRIK_MESSUNG_0147}\n"
          "Sie ist der einzige Nachweis, dass die Selbsttesttabellen ORTSFAELLE und "
          "FORMFAELLE von belegstellen_riegel.cpp etwas messen. Ist sie absichtlich "
          "umgezogen, gehoert der neue Pfad hierher -- nicht diese Bedingung entfernt.")
endif()

# Wird kein Deuter gefunden, wird `python3` trotzdem eingetragen. Dann meldet `ctest` die
# Probe rot ("Unable to find executable"), statt dass sie lautlos aus der Liste faellt.
# Eine uebersprungene Probe sieht im Bericht aus wie eine bestandene.
find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
  set(FABRIK_BELEGSTELLEN_PYTHON ${Python3_EXECUTABLE})
else()
  set(FABRIK_BELEGSTELLEN_PYTHON python3)
  message(WARNING "Kein Python3 gefunden -- die Probe `belegstellen_messung` faellt auf "
                  "`python3` aus dem Suchpfad zurueck und wird rot, wenn es das nicht "
                  "gibt.")
endif()

# Der Uebersetzer kommt von CMake und steht nicht im Skript. Das Skript baut elf Fassungen
# unmittelbar, ohne CMake -- ein fest eingebautes `g++` waere dabei ein zweiter
# Uebersetzer neben dem, gegen den dieser Kasten gebaut wird, und ein Unterschied zwischen
# beiden faende sich nirgends wieder. Dieselbe Begruendung wie bei `zahlwort_messung`.
add_test(NAME belegstellen_messung
         COMMAND ${FABRIK_BELEGSTELLEN_PYTHON} ${FABRIK_MESSUNG_0147}
                 --vorhaben ${FABRIK_VORHABEN_WURZEL}
                 --uebersetzer ${CMAKE_CXX_COMPILER})

# 600 und nicht 900: `agents/baulauf.py` bricht **den ganzen `ctest`-Aufruf** nach 900 s
# ab. Eine Probe mit derselben Grenze koennte das Kontingent allein aufbrauchen, und der
# Bericht wuerde dann nicht sie nennen, sondern nur einen abgeschnittenen Lauf. Mit 600
# meldet `ctest` die haengende Probe beim Namen und die uebrigen laufen noch.
#
# Die Zahl ist eine Schranke und keine gemessene Zeit -- der Lauf, der sie gesetzt hat,
# hatte keine Schale. Der Kostenpunkt sind elf Uebersetzungen von rund 4.050 Zeilen bei
# `-O2`; zum Vergleich steht `zahlwort_messung` mit sechs Uebersetzungen von rund 1.800
# Zeilen bei 13,5 s im Bericht vom 2026-09-07. Wer den ersten Nachtlauf im Bericht sieht,
# ersetzt die 600 durch das Vielfache der dort gemessenen Zeit.
set_tests_properties(belegstellen_messung PROPERTIES TIMEOUT 600)
