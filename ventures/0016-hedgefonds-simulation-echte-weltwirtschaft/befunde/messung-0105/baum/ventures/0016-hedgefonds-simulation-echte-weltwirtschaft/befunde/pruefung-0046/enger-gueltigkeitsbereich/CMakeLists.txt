# Wegwerf-Mitglied des Kern-Pruefers, Paket 0046, 2026-09-03 -- die ZWEITE LUECKE.
#
# `werkzeugkette.cmake` behauptet in seinem Kommentar: Wird die Datei aus einem engeren
# Gueltigkeitsbereich eingebunden als dem, aus dem gerufen wird, ist die FUNKTION bekannt
# (CMake-Funktionen sind global) und der SATZ trotzdem leer (`set()` ist scope-gebunden).
# Genau dagegen steht der zweite Riegel in der Funktion. Diese Datei stellt den Fall her.
#
# `block()` gibt es ab CMake 3.25; das ist hoeher als die 3.22 des Vorhabens, stoert hier
# aber nicht: Diese Datei wird nie vom Baulauf angefasst (Pfad enthaelt `befunde`).
cmake_minimum_required(VERSION 3.25)

project(enge LANGUAGES CXX)

block()
  include(${CMAKE_CURRENT_LIST_DIR}/../../../werkzeugkette.cmake)
endblock()

add_library(enge STATIC ${CMAKE_CURRENT_LIST_DIR}/../vergessenes-mitglied/src/etwas.cpp)
target_compile_features(enge PUBLIC cxx_std_20)
fabrik_warnsatz_anlegen(enge)

message(STATUS "PRUEFER: diese Zeile darf nicht erscheinen")
