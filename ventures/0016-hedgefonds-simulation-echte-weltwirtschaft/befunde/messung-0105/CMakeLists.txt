# Der Messstand zu Paket 0105 -- er gehoert nicht zum Erzeugnis.
#
# Er liegt unter `befunde/` und damit in einem mit Absicht ungelesenen Ordner: Der
# Riegel des Arbeitsbereichs liest hier keine Datei, und dieser Stand kann seine
# eigenen Zahlen nicht faelschen.
#
# Warum ein eigenes Projekt und kein `add_test` daneben: Die `CMakeLists.txt` des
# Riegels gehoert Paket 0059 und steht nicht in der Dateiliste von 0105. Gemessen
# werden ausserdem Aufrufe, die es dort nicht gibt -- derselbe Riegel gegen drei
# verschiedene Baeume, einmal in der ausgelieferten und einmal in der neuen Fassung.
#
#   riegel_vorher   Quelle aus `baum/` -- der Stand aus dem Commit in `bezugsstand.txt`
#   riegel_nachher  Quelle aus dem Arbeitsbaum -- die Fassung dieses Pakets
#
# Beide werden **gleich** uebersetzt, sonst misst der Vergleich den Schalter und nicht
# die Aenderung.

cmake_minimum_required(VERSION 3.22)

project(messung_0105 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

get_filename_component(MESS_WURZEL ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
get_filename_component(MESS_ARBEITSBAUM ${MESS_WURZEL}/../.. ABSOLUTE)

add_executable(riegel_vorher
  ${MESS_WURZEL}/baum/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp)
add_executable(riegel_nachher
  ${MESS_ARBEITSBAUM}/werkzeuge/belegstellen/belegstellen_riegel.cpp)

foreach(ziel riegel_vorher riegel_nachher)
  target_compile_options(${ziel} PRIVATE -Wall -Wextra -fwrapv)
endforeach()

# Die drei Baeume. `baum` ist der unveraenderte Stand des Bezugscommits; die beiden
# anderen sind seine Kopie mit **einer** angehaengten Belegstelle in `rueckstand.md`,
# die ueber den Zeilenumbruch laeuft -- einmal mit einer Ueberschrift, die es gibt,
# einmal mit einer, die es nicht gibt.
set(MESS_BAEUME baum baum_gut baum_tot)

foreach(baum ${MESS_BAEUME})
  foreach(ziel riegel_vorher riegel_nachher)
    add_test(NAME ${ziel}_auf_${baum}
             COMMAND ${ziel}
                     ${MESS_WURZEL}/${baum}/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
                     ${MESS_WURZEL}/${baum}/specs/0016-hedgefonds-simulation-echte-weltwirtschaft)
  endforeach()
endforeach()

# Was rot sein **soll**. Ohne diese Zeilen liefe der Nachweis auf "irgendetwas ist rot"
# hinaus; mit ihnen sagt `ctest` selbst, welche Richtung erwartet war.
set_tests_properties(riegel_vorher_auf_baum_gut PROPERTIES WILL_FAIL TRUE)
set_tests_properties(riegel_vorher_auf_baum_tot PROPERTIES WILL_FAIL TRUE)
set_tests_properties(riegel_nachher_auf_baum_tot PROPERTIES WILL_FAIL TRUE)

# Die Rueckgabewerte im Wortlaut. `WILL_FAIL` oben beweist nur "ungleich 0", und der
# Riegel unterscheidet 1 (Befund am Bestand) von 2 (gerissener Selbsttest). Ohne diesen
# Eintrag koennte ein kaputtes Programm als gefangener Fehler durchgehen.
add_test(NAME rueckgabewerte
         COMMAND sh ${MESS_WURZEL}/rueckgabewerte.sh
                 $<TARGET_FILE:riegel_vorher> $<TARGET_FILE:riegel_nachher>
                 ${MESS_WURZEL})

# Der Arbeitsbaum von heute -- der "dann geltende Korpus" aus der Abnahme. Die drei
# Baeume oben sind der eingefrorene Stand aus `bezugsstand.txt`; hier laufen beide
# Fassungen **im selben Aufruf** ueber den Baum, den der Baulauf sieht. Nur so ist der
# Vergleich gegen einen Bestand haltbar, an dem fremde Laeufe gleichzeitig schreiben.
foreach(ziel riegel_vorher riegel_nachher)
  add_test(NAME ${ziel}_auf_arbeitsbaum
           COMMAND ${ziel}
                   ${MESS_ARBEITSBAUM}
                   ${MESS_ARBEITSBAUM}/../../specs/0016-hedgefonds-simulation-echte-weltwirtschaft)
endforeach()
