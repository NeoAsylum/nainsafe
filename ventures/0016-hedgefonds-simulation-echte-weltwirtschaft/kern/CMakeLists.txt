# Der Kern -- die einzige Bibliothek des Vorhabens ohne jede Abhaengigkeit.
#
# T2: **null Fremdabhaengigkeiten.** In Rust stuende hier ein leerer Abschnitt
# `[dependencies]`. C++ hat keinen solchen Abschnitt; die Entsprechung ist, dass der
# Kern nichts hereinholt und nichts dazulinkt.
#
#   Mechanischer Nachweis (T2), zwei Aufrufe:
#   grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory' kern/CMakeLists.txt
#   grep -n  'target_link_libraries(kern '                                kern/CMakeLists.txt
#   -> beide liefern nichts ausser diesen Kommentarzeilen.
#
# Ein Kasten ohne Abhaengigkeiten kann durch kein fremdes Versionsupdate sein
# Ergebnis aendern. Die Standardbibliothek ist keine Fremdabhaengigkeit: Sie kommt
# mit dem Uebersetzer, den `werkzeugkette.cmake` festnagelt.

cmake_minimum_required(VERSION 3.22)

project(kern LANGUAGES CXX)

# Wird dieses Verzeichnis allein gebaut -- `baulauf.py` tut genau das, es sucht jede
# CMakeLists.txt einzeln --, dann gilt die Werkzeugkette des Arbeitsbereichs
# trotzdem. Beim Bau ueber den Arbeitsbereich ist sie schon eingebunden.
if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../werkzeugkette.cmake)
  enable_testing()
endif()

# Was in Rust `#![forbid(unsafe_code)]` waere.
#
# C++ kennt kein solches Attribut, und das ist der Preis der Entscheidung aus
# ADR 0011: Speichersicherheit ist hier eine Pruefregel statt einer Spracheigenschaft.
# An ihre Stelle treten drei Dinge, alle mechanisch:
#
#   1. Dieser Warnsatz mit `-Werror`. Was der Uebersetzer als zweifelhaft erkennt,
#      ist damit ein Bauabbruch und keine Zeile, die im Protokoll untergeht.
#   2. `#pragma GCC poison` in `include/kern/sperre.hpp` -- die Gleitkommasperre aus
#      T4 als Uebersetzungsfehler statt als Vorsatz.
#   3. Die Grep-Regel des Pruefers:
#      grep -rnE 'reinterpret_cast|const_cast|\bnew\b|\bdelete\b|\basm\b' kern/
#      -> liefert nichts. Der Kern kommt ohne Zeiger und ohne eigene Speicher-
#      verwaltung aus; feste Groessen und `std::array` statt roher Felder.
#
# `-Wpedantic` steht bewusst NICHT dabei: Es warnt vor `__int128`, und `__int128` ist
# nach ADR 0011 Massnahme 3 verpflichtend fuer jeden Zwischenwert. Ein Warnschalter,
# der eine Vorschrift anmeckert, wuerde entweder abgeschaltet oder ignoriert -- beides
# schlechter, als ihn gar nicht zu setzen.
set(FABRIK_STRENGE
    -Wall -Wextra -Werror
    -Wconversion -Wsign-conversion
    -Wshadow -Wold-style-cast -Wcast-qual -Wuseless-cast
    -Wdouble-promotion -Wfloat-equal
    -Wnon-virtual-dtor -Woverloaded-virtual
    -Wnull-dereference -Wformat=2)

# Die Quellen werden eingesammelt statt aufgezaehlt, und der Grund ist derselbe wie
# beim Arbeitsbereich: Jedes spaetere Kernpaket bringt genau seine eigene Datei mit
# und muss diese hier nicht anfassen. `CONFIGURE_DEPENDS` laesst CMake beim Bau
# nachsehen, ob eine dazugekommen ist.
file(GLOB KERN_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB KERN_KOEPFE  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/kern/*.hpp)

add_library(kern STATIC ${KERN_QUELLEN} ${KERN_KOEPFE})
target_include_directories(kern PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(kern PUBLIC cxx_std_20)
target_compile_options(kern PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})

# ---------------------------------------------------------------------------
# Das Testprofil (ADR 0011, Massnahme 2)
# ---------------------------------------------------------------------------
#
# `baulauf.py` konfiguriert genau einmal, es gibt also kein zweites Bauprofil, in das
# man die Sanitizer legen koennte. Deshalb steht hier eine zweite Uebersetzung
# derselben Quellen: `kern_geprueft`. Sie ist wortgleich mit `kern`, nur mit
# `-fsanitize=undefined,address` gebaut, und **nur** die Proben linken sie.
#
# Der Umweg ist noetig, weil ein Sanitizer nur findet, was er selbst uebersetzt hat.
# Haetten die Proben die ungepruefte `kern` gelinkt, waere die Massnahme eine
# Behauptung: Sie wuerde den Testcode absichern und den Code, um den es geht, nicht.
if(FABRIK_SANITIZER)
  add_library(kern_geprueft STATIC ${KERN_QUELLEN} ${KERN_KOEPFE})
  target_include_directories(kern_geprueft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(kern_geprueft PUBLIC cxx_std_20)
  target_compile_options(kern_geprueft PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
  target_compile_options(kern_geprueft PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(kern_geprueft    PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  set(FABRIK_PROBEN_BIBLIOTHEK kern_geprueft)
else()
  set(FABRIK_PROBEN_BIBLIOTHEK kern)
endif()

# Jede Datei unter `test/` wird ein eigenes Programm und ein eigener CTest-Eintrag --
# wieder aus Kollisionsgruenden: Ein spaeteres Paket legt seine Probe daneben, statt
# eine gemeinsame Datei zu erweitern.
file(GLOB KERN_PROBEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

foreach(probe IN LISTS KERN_PROBEN)
  get_filename_component(name ${probe} NAME_WE)
  add_executable(${name} ${probe})
  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
  target_compile_options(${name} PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
