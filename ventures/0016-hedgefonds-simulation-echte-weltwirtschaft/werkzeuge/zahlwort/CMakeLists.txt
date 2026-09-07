# Der Zahlwortriegel -- Paket 0180.
#
# Gebaut wie der Belegstellen- und der Bezeichnerriegel daneben, und aus denselben zwei
# Gruenden:
#
#   1. ueber den Arbeitsbereich -- `../../CMakeLists.txt` fuehrt `werkzeuge/zahlwort`
#      in `FABRIK_MITGLIEDER`;
#   2. allein -- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder
#      `cmake`, `--build` und `ctest`.
#
# Weg 2 ist der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt, und der
# Uebersetzungsbericht meldete `No tests were found` und trotzdem `ergebnis: ok` -- ein
# gruener Bericht ueber nichts. Genau das ist diesem Vorhaben am 2026-09-04 einmal
# passiert; die Begruendung steht ausgeschrieben im Bauskript des Belegstellenriegels.

cmake_minimum_required(VERSION 3.22)

project(zahlwort LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../werkzeugkette.cmake)
  enable_testing()
endif()

# Die Quelle wird einzeln genannt und nicht eingesammelt. Ein `file(GLOB *.cpp)` zoege
# jede liegengebliebene Datei mit in die Uebersetzung und machte den ganzen Kasten rot
# statt nur dieses Paket.
add_executable(zahlwort_riegel zahlwort_riegel.cpp)
fabrik_warnsatz_anlegen(zahlwort_riegel)

# ADR 0011, Massnahme 2. Der Riegel rechnet nichts, aber er indiziert Zeichenketten
# rueckwaerts -- die Suche nach links vom Nomen und die Suche nach dem letzten
# Bezeichner eines Feldes. Genau die Fehlerklasse, die C++ nicht selbst abfaengt und
# die sich sonst erst beim Kaeufer zeigt.
if(FABRIK_SANITIZER)
  target_compile_options(zahlwort_riegel PRIVATE ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(zahlwort_riegel    PRIVATE ${FABRIK_SANITIZER_SCHALTER})
endif()

# Die Wurzel kommt von CMake, nicht aus dem Programm. Sie zeigt auf das Vorhaben, nicht
# auf dieses Verzeichnis, und ist auf beiden Bauwegen dieselbe:
# `CMAKE_CURRENT_SOURCE_DIR` ist in beiden Faellen dieses Verzeichnis.
get_filename_component(FABRIK_VORHABEN_WURZEL
                       ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

add_test(NAME zahlwort_riegel
         COMMAND zahlwort_riegel ${FABRIK_VORHABEN_WURZEL})

# ---------------------------------------------------------------------------
# Die zweite Probe desselben Kastens -- Paket 0188
#
# Dieselbe Krankheit eine Datei weiter: Der Kopf von `daten/reihen.toml` traegt drei
# Zahlwoerter, die zaehlen, was in derselben Datei steht. Binnen zweier Tage sind sie
# zweimal falsch geworden, beide Male ohne dass jemand die Zaehlung angefasst haette,
# und beide Male hat ein zufaellig danebenstehender Lauf es gefunden.
#
# **Kein C++, und das ist gemessen und nicht bequem.** Die Zaehlung liest TOML. Einen
# TOML-Leser hat dieses Vorhaben nicht, und einen fuer eine Probe unter einer Sekunde zu
# schreiben, waere der teuerste Weg zum billigsten Ergebnis. Die Zaehlung selbst liegt
# seit Paket 0099 im Baum, ist gegen zwei historische Staende bestaetigt und wird
# deshalb nicht neu geschrieben, sondern angehaengt.
#
# Die Bauart darunter ist die von `werkzeuge/schlussriegel` -- ein Python-Skript aus
# `befunde/` per `add_test` in `ctest`, ohne uebersetzendes Ziel. Sie steht hier und
# nicht in einem eigenen Mitglied, damit nicht ein zweites Mitglied fuer dieselbe Sorte
# Probe entsteht; der Kasten heisst `zahlwort` und traegt jetzt zwei Zahlwortproben.

get_filename_component(FABRIK_ZAHLWORT_SKRIPT
                       ${FABRIK_VORHABEN_WURZEL}/befunde/messung-0099/zahlwoerter.py
                       ABSOLUTE)

# Kein `if(EXISTS ...) add_test() endif()`. Genau diese Bauform laesst eine Probe still
# verschwinden, sobald jemand die Datei verschiebt, und meldet danach eine gruene Abnahme
# ueber einen Baum ohne sie. Fehlt die Datei, bricht die Konfiguration ab und sagt, wo
# sie erwartet wird.
if(NOT EXISTS ${FABRIK_ZAHLWORT_SKRIPT})
  message(FATAL_ERROR
          "Der Zahlwortriegel fuer die Reihenliste fehlt: ${FABRIK_ZAHLWORT_SKRIPT}\n"
          "Er ist der einzige Nachweis, dass die drei Zahlwoerter im Kopf von "
          "daten/reihen.toml noch gezaehlt und nicht fortgeschrieben werden. Ist er "
          "absichtlich umgezogen, gehoert der neue Pfad hierher -- nicht diese "
          "Bedingung entfernt.")
endif()

# Wird kein Deuter gefunden, wird `python3` trotzdem eingetragen. Dann meldet `ctest` die
# Probe rot ("Unable to find executable"), statt dass sie lautlos aus der Liste faellt.
# Eine uebersprungene Probe sieht im Bericht aus wie eine bestandene.
find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
  set(FABRIK_ZAHLWORT_PYTHON ${Python3_EXECUTABLE})
else()
  set(FABRIK_ZAHLWORT_PYTHON python3)
  message(WARNING "Kein Python3 gefunden -- die Probe `zahlwort_reihen` faellt auf "
                  "`python3` aus dem Suchpfad zurueck und wird rot, wenn es das nicht "
                  "gibt.")
endif()

add_test(NAME zahlwort_reihen
         COMMAND ${FABRIK_ZAHLWORT_PYTHON} ${FABRIK_ZAHLWORT_SKRIPT}
                 --riegel ${FABRIK_VORHABEN_WURZEL})

# Die Zeitgrenze ist **nicht** das Vielfache eines gemessenen Werts, und das gehoert
# dazugesagt: Der Lauf, der diese Probe gebaut hat, hatte keine Schale und konnte sie
# nicht laufen lassen. Sie ist als Hemmschuh gegen ein haengendes `git cat-file`
# gewaehlt, nicht als Schaetzung nach oben. Wer den ersten Nachtlauf im Bericht sieht,
# soll sie durch das Vielfache der gemessenen Zeit ersetzen.
set_tests_properties(zahlwort_reihen PROPERTIES TIMEOUT 300)
