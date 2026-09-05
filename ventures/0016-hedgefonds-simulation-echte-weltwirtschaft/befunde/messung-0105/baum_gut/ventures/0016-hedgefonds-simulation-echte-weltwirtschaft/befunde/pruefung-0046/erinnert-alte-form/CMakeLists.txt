# Wegwerf-Mitglied des Kern-Pruefers, Paket 0046, 2026-09-03 -- die GLEICHHEITSPROBE
# fuer Abnahmebedingung 2.
#
# Zeichenweise gleich zu `../erinnertes-mitglied/CMakeLists.txt`, mit genau einer
# Abweichung: Der Warnsatz wird in der Form von VOR Paket 0046 angehaengt
# (`target_compile_options(... PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})`)
# statt ueber `fabrik_warnsatz_anlegen()`. Beide Baeume unter denselben Schaltern
# konfiguriert, dann `CXX_FLAGS` gegen `CXX_FLAGS` -- damit ist "unveraendert" gemessen
# und nicht aus dem Diff geschlossen.
#
# Der Zielname ist derselbe (`erinnert`), damit sich die erzeugten Pfade und damit die
# Zeilen der `flags.make` nicht schon durch den Namen unterscheiden.
cmake_minimum_required(VERSION 3.22)

project(erinnert LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../../werkzeugkette.cmake)
  enable_testing()
endif()

add_library(erinnert STATIC ${CMAKE_CURRENT_LIST_DIR}/../erinnertes-mitglied/src/etwas.cpp)
target_compile_features(erinnert PUBLIC cxx_std_20)
target_compile_options(erinnert PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
