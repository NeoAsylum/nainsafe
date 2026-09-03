# Wegwerf-Probe des Kern-Pruefers, Paket 0046, 2026-09-03 -- MACHBARKEIT des in
# Paket 0058 vorgeschlagenen Schluss-Riegels.
#
# Sie baut nichts. Sie beantwortet eine einzige Frage: Kann eine nachgestellte Pruefung
# am Ende der Konfiguration alle Ziele aufzaehlen und an jedem ablesen, ob der Warnsatz
# daran haengt? Wenn nein, waere der Vorschlag Prosa.
#
# `mit_satz` bekommt ihn ueber `fabrik_warnsatz_anlegen()`, `ohne_satz` gar nicht -- das
# ist das Mitglied, das die Form nie benutzt und das der Riegel aus 0046 nicht faengt.
cmake_minimum_required(VERSION 3.22)

project(machbarkeit LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../../werkzeugkette.cmake)

add_library(mit_satz  STATIC ${CMAKE_CURRENT_LIST_DIR}/../erinnertes-mitglied/src/etwas.cpp)
add_library(ohne_satz STATIC ${CMAKE_CURRENT_LIST_DIR}/../erinnertes-mitglied/src/etwas.cpp)
fabrik_warnsatz_anlegen(mit_satz)

# Das dritte Ziel liegt ein Verzeichnis tiefer -- so wie `kern` und `pruefstand` im
# Arbeitsbereich. Damit misst die Probe auch, ob die Aufzaehlung ueber
# `add_subdirectory` hinwegreicht; ein Riegel, der nur die oberste Ebene sieht, faende
# im Arbeitsbereich gar nichts.
add_subdirectory(mitglied-ohne-satz)

function(pruefer_schlussriegel verzeichnis)
  get_property(ziele DIRECTORY ${verzeichnis} PROPERTY BUILDSYSTEM_TARGETS)
  foreach(ziel IN LISTS ziele)
    get_target_property(art ${ziel} TYPE)
    get_target_property(schalter ${ziel} COMPILE_OPTIONS)
    if("${schalter}" MATCHES "-Werror")
      message(STATUS "PRUEFER-RIEGEL: ${ziel} (${art}) -- Warnsatz vorhanden")
    else()
      message(STATUS "PRUEFER-RIEGEL: ${ziel} (${art}) -- OHNE WARNSATZ, hier stuende FATAL_ERROR")
    endif()
  endforeach()
  get_property(unter DIRECTORY ${verzeichnis} PROPERTY SUBDIRECTORIES)
  foreach(u IN LISTS unter)
    pruefer_schlussriegel(${u})
  endforeach()
endfunction()

cmake_language(DEFER CALL pruefer_schlussriegel ${CMAKE_CURRENT_SOURCE_DIR})
