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
