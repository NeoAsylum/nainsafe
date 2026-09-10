# `daten` -- die Datenschicht aus T13. Sie haengt an `kern`, und nie umgekehrt.
#
# Diese Datei wird auf **zwei** Wegen konfiguriert, und beide muessen tragen:
#
#   1. ueber den Arbeitsbereich -- `../CMakeLists.txt` nimmt `daten` in
#      `FABRIK_MITGLIEDER` auf, sobald diese Datei existiert. Dort ist `kern` schon
#      eingehaengt, weil es in jener Liste davor steht;
#   2. allein -- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder
#      `cmake`, `--build` und `ctest`. In diesem Baum gibt es das Ziel `kern` nicht, und
#      deshalb haengt der Block unten es selbst ein.
#
# Weg 2 ist auch der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt, und
# `ctest` meldete "No tests were found!!!" -- im Bericht nicht zu unterscheiden von einem
# Kasten, den es gar nicht gibt. Ohne die Werkzeugkette fehlt zusaetzlich
# `fabrik_warnsatz_anlegen`; das ist ein harter Konfigurationsfehler und kein stiller
# Verlust der siebzehn Schalter, und genau dafuer ist die Funktion eine Funktion.

cmake_minimum_required(VERSION 3.22)

project(daten LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../werkzeugkette.cmake)
  enable_testing()

  # `kern` wird eingehaengt und nicht gesucht: Eine `find_package`-Bauart braeuchte eine
  # installierte Fassung, und die gibt es in diesem Vorhaben nicht. Das Bauverzeichnis
  # liegt unter dem eigenen, damit der Alleinbau des Kerns und dieser hier sich nicht in
  # dieselben Dateien schreiben. Beim Bau ueber den Arbeitsbereich passiert das hier
  # nicht -- dort ist `kern` bereits ein Ziel, und ein zweites `add_subdirectory` waere
  # ein Namenskonflikt.
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../kern ${CMAKE_CURRENT_BINARY_DIR}/kern)
endif()

# Eingesammelt statt aufgezaehlt, wie im Kern und im Pruefstand und aus demselben Grund:
# Jedes spaetere Paket der Datenschicht legt seine Datei daneben und fasst diese hier
# nicht an. Zwei Bauagenten treffen sich dann nie in derselben Zeile. `CONFIGURE_DEPENDS`
# laesst CMake beim Bau nachsehen, ob eine dazugekommen ist.
file(GLOB DATEN_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB DATEN_KOEPFE  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/daten/*.hpp)
file(GLOB DATEN_PROBEN  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_library(daten STATIC ${DATEN_QUELLEN} ${DATEN_KOEPFE})
target_include_directories(daten PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(daten PUBLIC cxx_std_20)
target_link_libraries(daten PUBLIC kern)
fabrik_warnsatz_anlegen(daten)

# Das Testprofil (ADR 0011, Massnahme 2), wortgleich zum Kern und aus demselben Grund:
# Ein Sanitizer findet nur, was er selbst uebersetzt hat. Linkte die Probe die
# ungepruefte Bibliothek, sicherte die Massnahme den Testcode ab und den Code, um den es
# geht, nicht. Gelinkt wird dann auch `kern_geprueft` und nicht `kern` -- eine Probe, die
# den ungeprueften Kern mitnimmt, laesst den halben Aufrufweg ungesehen.
if(FABRIK_SANITIZER)
  add_library(daten_geprueft STATIC ${DATEN_QUELLEN} ${DATEN_KOEPFE})
  target_include_directories(daten_geprueft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(daten_geprueft PUBLIC cxx_std_20)
  target_link_libraries(daten_geprueft PUBLIC kern_geprueft)
  fabrik_warnsatz_anlegen(daten_geprueft)
  target_compile_options(daten_geprueft PUBLIC ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(daten_geprueft    PUBLIC ${FABRIK_SANITIZER_SCHALTER})
  set(FABRIK_PROBEN_BIBLIOTHEK daten_geprueft)
else()
  set(FABRIK_PROBEN_BIBLIOTHEK daten)
endif()

# Je Probendatei ein eigenes Programm und ein eigener CTest-Eintrag -- derselbe
# Kollisionsschutz wie bei den Quellen, und im Uebersetzungsbericht ist ein roter Test
# damit der Datei zuzuordnen, die ihn ausloest.
foreach(probe IN LISTS DATEN_PROBEN)
  get_filename_component(name ${probe} NAME_WE)
  add_executable(${name} ${probe})
  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
  fabrik_warnsatz_anlegen(${name})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
