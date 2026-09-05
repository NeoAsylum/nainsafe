# Der Bezeichnerriegel -- Paket 0129.
#
# Gebaut wie der Belegstellenriegel daneben, und aus denselben zwei Gruenden:
#
#   1. ueber den Arbeitsbereich -- `../../CMakeLists.txt` fuehrt `werkzeuge/bezeichner`
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

project(bezeichner LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../werkzeugkette.cmake)
  enable_testing()
endif()

# Die Quelle wird einzeln genannt und nicht eingesammelt. Ein `file(GLOB *.cpp)` zoege
# jede liegengebliebene Datei mit in die Uebersetzung und machte den ganzen Kasten rot
# statt nur dieses Paket.
add_executable(bezeichner_riegel bezeichner_riegel.cpp)
fabrik_warnsatz_anlegen(bezeichner_riegel)

# ADR 0011, Massnahme 2. Der Riegel rechnet nichts, aber er indiziert Zeichenketten
# vorwaerts und rueckwaerts -- genau die Fehlerklasse, die C++ nicht selbst abfaengt
# und die sich sonst erst beim Kaeufer zeigt.
if(FABRIK_SANITIZER)
  target_compile_options(bezeichner_riegel PRIVATE ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(bezeichner_riegel    PRIVATE ${FABRIK_SANITIZER_SCHALTER})
endif()

# Die Wurzel kommt von CMake, nicht aus dem Programm. Sie zeigt auf das Vorhaben, nicht
# auf dieses Verzeichnis, und ist auf beiden Bauwegen dieselbe:
# `CMAKE_CURRENT_SOURCE_DIR` ist in beiden Faellen dieses Verzeichnis.
get_filename_component(FABRIK_VORHABEN_WURZEL
                       ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

add_test(NAME bezeichner_riegel
         COMMAND bezeichner_riegel ${FABRIK_VORHABEN_WURZEL})
