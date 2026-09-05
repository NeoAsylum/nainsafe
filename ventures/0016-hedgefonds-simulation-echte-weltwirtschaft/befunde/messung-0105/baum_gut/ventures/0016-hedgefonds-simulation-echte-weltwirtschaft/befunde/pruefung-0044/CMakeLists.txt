# Rotnachweis zu Paket 0044 -- Test-Pruefer, 2026-09-04.
#
# Zweck: zeigen, dass das Gruen des Belegstellenriegels ueber
# `kern/test/schranken_probe.cpp` gemessen und nicht blind ist. Dazu laeuft **derselbe,
# unveraenderte Riegel** ueber zwei winzige Wurzeln: `alt/` traegt den Kommentarblock im
# Wortlaut von **vor** 0044, `neu/` den von **nach** 0044.
#
#   riegel_alt  soll FEHLSCHLAGEN  (drei Verweise auf parameter.toml mit Zeilennummer)
#   riegel_neu  soll BESTEHEN      (kein Verweis mehr)
#
# Der Riegel wird per absolutem Pfad uebersetzt und nicht abgeschrieben: Eine Abschrift
# wuerde messen, was hier steht, und nicht, was im Vorhaben laeuft.
#
# Diese Probe liegt unter `befunde/` und ist damit fuer den echten Riegellauf unsichtbar
# -- `GESPERRTE_ORDNER = {"bau", "befunde"}` in `belegstellen_riegel.cpp`. Die Wurzel
# eines Laufs wird nicht gegen diese Liste geprueft, nur betretene Unterordner; deshalb
# traegt sie hier trotzdem.

cmake_minimum_required(VERSION 3.22)
project(pruefung_0044_rotnachweis LANGUAGES CXX)
enable_testing()

add_executable(riegel
  ${CMAKE_CURRENT_SOURCE_DIR}/../../werkzeuge/belegstellen/belegstellen_riegel.cpp)
target_compile_features(riegel PRIVATE cxx_std_20)

add_test(NAME riegel_alt COMMAND riegel ${CMAKE_CURRENT_SOURCE_DIR}/alt)
add_test(NAME riegel_neu COMMAND riegel ${CMAKE_CURRENT_SOURCE_DIR}/neu)

set_tests_properties(riegel_alt PROPERTIES WILL_FAIL TRUE)
