# Wegwerf-Mitglied des Kern-Pruefers, Paket 0046, 2026-09-03 -- die GEGENPROBE.
#
# Wortgleich zu `../vergessenes-mitglied/CMakeLists.txt`, nur haengt es den Warnsatz in
# der Form an, die vor Paket 0046 in `kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt`
# stand. Das ist der Stand VOR der Aenderung, und er muss gruen durchlaufen -- sonst
# waere die Luecke, gegen die dieses Paket geschrieben ist, gar nicht da.
cmake_minimum_required(VERSION 3.22)

project(vergessen_alt LANGUAGES CXX)

file(GLOB VERGESSEN_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(vergessen_alt STATIC ${VERGESSEN_QUELLEN})
target_compile_features(vergessen_alt PUBLIC cxx_std_20)
target_compile_options(vergessen_alt PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})

message(STATUS "PRUEFER: diese Zeile WIRD erreicht -- das ist der Befund")
