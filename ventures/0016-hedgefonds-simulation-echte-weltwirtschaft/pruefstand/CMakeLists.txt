# Der Pruefstand -- das Gestell, auf dem Mass 1 bis 3 und der Selbstspieler stehen.
#
# T13 fuehrt `pruefstand` als eigenen Kasten. Er **darf** auf `schnittstelle` zeigen;
# heute tut er es nicht, weil das einzige Modul darin (`vorrat`) mit fuenf Ganzzahlen
# und drei Steckplaetzen auskommt. T13 gibt die erlaubte Richtung an, keine Pflicht,
# sie auszunutzen -- also wird hier **nichts** gelinkt: weder `kern` noch eine
# Fremdabhaengigkeit. T3 erlaubt dem Pruefstand `rayon`; hier wird nichts parallel
# gerechnet, also kommt es nicht herein.
#
# Diese Datei wird auf **zwei** Wegen konfiguriert, und beide muessen tragen:
#
#   1. ueber den Arbeitsbereich -- `../CMakeLists.txt` nimmt `pruefstand` in
#      `FABRIK_MITGLIEDER` auf, sobald diese Datei existiert;
#   2. allein -- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf
#      jeder `cmake`, `--build` und `ctest`.
#
# Weg 2 ist der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt, und
# `ctest` meldete "No tests were found!!!" -- im Bericht nicht zu unterscheiden von
# einem Kasten, den es gar nicht gibt.

cmake_minimum_required(VERSION 3.22)

project(pruefstand LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../werkzeugkette.cmake)
  enable_testing()
endif()

# Derselbe Warnsatz wie im Kern, und er steht hier ein zweites Mal, weil `set()` in
# CMake verzeichnisgebunden ist: Was `kern/CMakeLists.txt` setzt, sieht ein
# Geschwisterverzeichnis nicht. Die Alternative waere, ihn in `werkzeugkette.cmake`
# hochzuziehen -- das ist eine Aenderung an einer Datei, die keinem Paket gehoert,
# und gehoert deshalb in einen Vorschlag statt in diesen Lauf.
#
# `-Wpedantic` fehlt aus demselben Grund wie im Kern: Es warnt vor `__int128`, und
# `__int128` ist nach ADR 0011 Massnahme 3 vorgeschrieben.
set(FABRIK_STRENGE
    -Wall -Wextra -Werror
    -Wconversion -Wsign-conversion
    -Wshadow -Wold-style-cast -Wcast-qual -Wuseless-cast
    -Wdouble-promotion -Wfloat-equal
    -Wnon-virtual-dtor -Woverloaded-virtual
    -Wnull-dereference -Wformat=2)

# Eingesammelt statt aufgezaehlt, und das ist hier eine **Zusage an Paket 0029**:
# Es legt `src/vorrat_verfahren.cpp` und `test/vorrat_verfahren_probe.cpp` daneben und
# fasst diese Datei nicht an. Zwei Bauagenten treffen sich dann nie in derselben
# Zeile. `CONFIGURE_DEPENDS` laesst CMake beim Bau nachsehen, ob eine dazugekommen ist.
file(GLOB PRUEFSTAND_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB PRUEFSTAND_KOEPFE  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/pruefstand/*.hpp)

add_library(pruefstand STATIC ${PRUEFSTAND_QUELLEN} ${PRUEFSTAND_KOEPFE})
target_include_directories(pruefstand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(pruefstand PUBLIC cxx_std_20)
target_compile_options(pruefstand PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})

# Das Testprofil (ADR 0011, Massnahme 2), wortgleich zum Kern und aus demselben
# Grund: Ein Sanitizer findet nur, was er selbst uebersetzt hat. Linkten die Proben
# die ungepruefte Bibliothek, sicherte die Massnahme den Testcode ab und den Code,
# um den es geht, nicht.
if(FABRIK_SANITIZER)
  add_library(pruefstand_geprueft STATIC ${PRUEFSTAND_QUELLEN} ${PRUEFSTAND_KOEPFE})
  target_include_directories(pruefstand_geprueft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(pruefstand_geprueft PUBLIC cxx_std_20)
  target_compile_options(pruefstand_geprueft PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
  target_compile_options(pruefstand_geprueft PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(pruefstand_geprueft    PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  set(FABRIK_PROBEN_BIBLIOTHEK pruefstand_geprueft)
else()
  set(FABRIK_PROBEN_BIBLIOTHEK pruefstand)
endif()

# Je Probendatei ein eigenes Programm und ein eigener CTest-Eintrag. Nicht Kosmetik:
# Ohne das haette Paket 0029 keinen eigenen Testnamen im Uebersetzungsbericht, und ein
# roter Test waere nicht der Datei zuzuordnen, die ihn ausloest.
file(GLOB PRUEFSTAND_PROBEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

foreach(probe IN LISTS PRUEFSTAND_PROBEN)
  get_filename_component(name ${probe} NAME_WE)
  add_executable(${name} ${probe})
  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
  target_compile_options(${name} PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
