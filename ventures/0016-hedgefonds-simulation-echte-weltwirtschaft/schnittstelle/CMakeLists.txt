# `schnittstelle` -- das Mitglied aus T13, das an `kern` und `daten` haengt und nie
# umgekehrt. Angelegt von Paket 0301 mit dem Schreiber des Partieformats (T22); Protokoll
# (T21) und die drei Zustandsebenen (G8) kommen als eigene Pakete daneben.
#
# Diese Datei wird auf **zwei** Wegen konfiguriert, und beide muessen tragen -- wortgleich
# zum Vorgehen in `daten/CMakeLists.txt` und aus demselben Grund:
#
#   1. ueber den Arbeitsbereich -- `../CMakeLists.txt` nimmt `schnittstelle` in
#      `FABRIK_MITGLIEDER` auf, sobald diese Datei existiert. Dort stehen `kern` und
#      `daten` in jener Liste davor und sind deshalb schon eingehaengt;
#   2. allein -- `baulauf.py` sucht **jede** `CMakeLists.txt` einzeln und ruft auf jeder
#      `cmake`, `--build` und `ctest`. In diesem Baum gibt es weder `kern` noch `daten`,
#      und deshalb haengt der Block unten beide selbst ein, in dieser Reihenfolge: `daten`
#      erwartet das Ziel `kern` und sucht es nicht.
#
# Weg 2 ist auch der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt, und
# `fabrik_warnsatz_anlegen` gaebe es nicht -- ein harter Konfigurationsfehler statt eines
# stillen Verlusts der siebzehn Schalter.
#
# **Warum `daten` schon jetzt gelinkt wird, obwohl der Schreiber nichts daraus liest.**
# T13 zieht die Kante, und dieses Verzeichnis wird genau einmal angelegt. Stuende hier nur
# `kern`, muesste das erste Paket, das den Jahrgang braucht -- das Laden nach T22, der
# Befehl `neu` nach T21 --, diese gemeinsame Datei anfassen, und genau das ist der
# Kollisionsfall, gegen den die Sammler unten gebaut sind.
#
# Die `../CMakeLists.txt` wird **nicht** angefasst: Sie haengt jedes Mitglied ein, dessen
# eigene `CMakeLists.txt` existiert.

cmake_minimum_required(VERSION 3.22)

project(schnittstelle LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../werkzeugkette.cmake)
  enable_testing()

  # Eingehaengt und nicht gesucht: Eine `find_package`-Bauart braeuchte eine installierte
  # Fassung, und die gibt es in diesem Vorhaben nicht. Die Bauverzeichnisse liegen unter
  # dem eigenen, damit der Alleinbau des Kerns, der der Datenschicht und dieser hier sich
  # nicht in dieselben Dateien schreiben.
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../kern  ${CMAKE_CURRENT_BINARY_DIR}/kern)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../daten ${CMAKE_CURRENT_BINARY_DIR}/daten)
endif()

# Eingesammelt statt aufgezaehlt, wie im Kern und in der Datenschicht und aus demselben
# Grund: Jedes spaetere Paket dieses Mitglieds legt seine Datei daneben und fasst diese
# hier nicht an. Zwei Bauagenten treffen sich dann nie in derselben Zeile.
# `CONFIGURE_DEPENDS` laesst CMake beim Bau nachsehen, ob eine dazugekommen ist.
file(GLOB SCHNITTSTELLE_QUELLEN CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB SCHNITTSTELLE_KOEPFE  CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/schnittstelle/*.hpp)
file(GLOB SCHNITTSTELLE_PROBEN  CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_library(schnittstelle STATIC ${SCHNITTSTELLE_QUELLEN} ${SCHNITTSTELLE_KOEPFE})
target_include_directories(schnittstelle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(schnittstelle PUBLIC cxx_std_20)
target_link_libraries(schnittstelle PUBLIC daten)
fabrik_warnsatz_anlegen(schnittstelle)

# Das Testprofil (ADR 0011, Massnahme 2), wortgleich zum Kern und zur Datenschicht und aus
# demselben Grund: Ein Sanitizer findet nur, was er selbst uebersetzt hat. Linkte die Probe
# die ungepruefte Bibliothek, sicherte die Massnahme den Testcode ab und den Code, um den
# es geht, nicht. Gelinkt wird dann auch `daten_geprueft` und nicht `daten` -- und darueber
# `kern_geprueft`, weil jenes Manifest dieselbe Verzweigung fuehrt.
if(FABRIK_SANITIZER)
  add_library(schnittstelle_geprueft STATIC
              ${SCHNITTSTELLE_QUELLEN} ${SCHNITTSTELLE_KOEPFE})
  target_include_directories(schnittstelle_geprueft PUBLIC
                             ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(schnittstelle_geprueft PUBLIC cxx_std_20)
  target_link_libraries(schnittstelle_geprueft PUBLIC daten_geprueft)
  fabrik_warnsatz_anlegen(schnittstelle_geprueft)
  target_compile_options(schnittstelle_geprueft PUBLIC ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(schnittstelle_geprueft    PUBLIC ${FABRIK_SANITIZER_SCHALTER})
  set(FABRIK_PROBEN_BIBLIOTHEK schnittstelle_geprueft)
else()
  set(FABRIK_PROBEN_BIBLIOTHEK schnittstelle)
endif()

# Je Probendatei ein eigenes Programm und ein eigener CTest-Eintrag -- derselbe
# Kollisionsschutz wie bei den Quellen, und im Uebersetzungsbericht ist ein roter Test
# damit der Datei zuzuordnen, die ihn ausloest.
foreach(probe IN LISTS SCHNITTSTELLE_PROBEN)
  get_filename_component(name ${probe} NAME_WE)
  add_executable(${name} ${probe})
  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
  fabrik_warnsatz_anlegen(${name})
  add_test(NAME ${name} COMMAND ${name})
endforeach()
