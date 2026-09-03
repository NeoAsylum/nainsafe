# Der Kern -- die einzige Bibliothek des Vorhabens ohne jede Abhaengigkeit.
#
# T2: **null Fremdabhaengigkeiten.** In Rust stuende hier ein leerer Abschnitt
# `[dependencies]`. C++ hat keinen solchen Abschnitt; die Entsprechung ist, dass der
# Kern nichts hereinholt und nichts dazulinkt.
#
#   Mechanischer Nachweis (T2), zwei Mustervergleiche ueber diese Datei: Der erste
#   sucht jede Anweisung, die fremden Code hereinholt oder ein weiteres Verzeichnis
#   dazunimmt, der zweite jede Bibliothek, die an den Kern gelinkt wird. Beide muessen
#   leer ausgehen. Ihr Wortlaut steht in der Abnahme von Paket 0004, Bedingung 3, und
#   absichtlich nicht hier: Eine Datei, die ihre eigenen Suchmuster zitiert, laesst sie
#   nie leer ausgehen, und die Ausnahme davon gehoerte dann ins Kriterium statt in die
#   geprueften Zeilen.
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

# Der Warnsatz `FABRIK_STRENGE` -- das, was hier an die Stelle von Rusts
# `#![forbid(unsafe_code)]` tritt -- stand bis zum 2026-09-02 an dieser Stelle und
# steht seit Paket 0031 in `werkzeugkette.cmake`, samt seiner vollstaendigen
# Begruendung und den beiden kernlokalen Massnahmen daneben (Gleitkommasperre,
# Grep-Regel). Der Grund fuer den Umzug: `set()` ist verzeichnisgebunden, der
# Pruefstand musste den Satz deshalb abschreiben, und ein abgeschriebener Warnsatz mit
# einer verlorenen Zeile uebersetzt gruen und prueft weniger.
#
# Unten benutzbar ist er trotzdem: Beim Bau ueber den Arbeitsbereich hat
# `../CMakeLists.txt` die Werkzeugkette schon eingebunden, beim Alleinbau tut es der
# `PROJECT_IS_TOP_LEVEL`-Block oben -- in beiden Faellen vor dieser Zeile.

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
