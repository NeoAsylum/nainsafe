# Wegwerf-Mitglied des Kern-Pruefers, Paket 0046, 2026-09-03.
#
# Gebaut wie `pruefstand/CMakeLists.txt`, mit genau einem Unterschied: Der
# `PROJECT_IS_TOP_LEVEL`-Block fehlt, `werkzeugkette.cmake` wird also nie eingebunden.
# Das ist das Mitglied aus Abnahmebedingung 1. Es liegt unter `befunde/`, weil
# `baulauf.py` jede `CMakeLists.txt` unter dem Venture einsammelt AUSSER denen, deren
# Pfad `befunde` enthaelt -- hier stoert es den Uebersetzungsbericht also nicht.
cmake_minimum_required(VERSION 3.22)

project(vergessen LANGUAGES CXX)

file(GLOB VERGESSEN_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(vergessen STATIC ${VERGESSEN_QUELLEN})
target_compile_features(vergessen PUBLIC cxx_std_20)
fabrik_warnsatz_anlegen(vergessen)

message(STATUS "PRUEFER: diese Zeile darf nicht erscheinen")
