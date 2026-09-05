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

# Der Warnsatz `FABRIK_STRENGE` stand hier am 2026-09-02 einen Tag lang als Abschrift
# des Satzes aus dem Kern -- `set()` ist in CMake verzeichnisgebunden, ein
# Geschwisterverzeichnis sieht den Satz des anderen nicht. Seit Paket 0031 steht er
# einmal in `werkzeugkette.cmake` und reicht von dort nach unten durch; die Abschrift
# ist weg. Was sie gekostet haette, steht dort: Eine Zeile, die beim Abschreiben
# verlorengeht, macht den Kasten nicht rot, sondern still nachlaessiger.
#
# Angehaengt wird er seit Paket 0046 nicht mehr hier, sondern von
# `fabrik_warnsatz_anlegen(<ziel>)` aus derselben Datei. Der Grund steht dort: Haengt ein
# Mitglied den Satz selbst an und fehlt ihm der `PROJECT_IS_TOP_LEVEL`-Block, dann haengt
# es eine leere Liste an -- eine undefinierte Variable ist in CMake kein Fehler, sondern
# nichts. Der Kasten uebersetzt gruen und prueft weniger. Ein Aufruf, den CMake nicht
# kennt, bricht dagegen ab. Die Funktion gibt es nur, wenn die Werkzeugkette eingebunden
# ist; damit ist der Block oben nicht mehr vergessbar, sondern erzwungen.
#
# Fuer diesen Kasten war der vergessene Block bisher wenigstens laut -- ohne ihn faellt
# `enable_testing()` mit, und `ctest` meldet "No tests were found!!!". Fuer `konsole` und
# `oberflaeche` aus T13, die keine eigenen Proben haben, gilt das nicht: Sie haetten den
# Verlust lautlos. Der Riegel steht deshalb nicht wegen dieser Datei da, sondern wegen
# der fuenf Mitglieder, die es noch nicht gibt.

# Eingesammelt statt aufgezaehlt, und das ist hier eine **Zusage an Paket 0029**:
# Es legt `src/vorrat_verfahren.cpp` und `test/vorrat_verfahren_probe.cpp` daneben und
# fasst diese Datei nicht an. Zwei Bauagenten treffen sich dann nie in derselben
# Zeile. `CONFIGURE_DEPENDS` laesst CMake beim Bau nachsehen, ob eine dazugekommen ist.
file(GLOB PRUEFSTAND_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB PRUEFSTAND_KOEPFE  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/pruefstand/*.hpp)

add_library(pruefstand STATIC ${PRUEFSTAND_QUELLEN} ${PRUEFSTAND_KOEPFE})
target_include_directories(pruefstand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(pruefstand PUBLIC cxx_std_20)
fabrik_warnsatz_anlegen(pruefstand)

# Das Testprofil (ADR 0011, Massnahme 2), wortgleich zum Kern und aus demselben
# Grund: Ein Sanitizer findet nur, was er selbst uebersetzt hat. Linkten die Proben
# die ungepruefte Bibliothek, sicherte die Massnahme den Testcode ab und den Code,
# um den es geht, nicht.
if(FABRIK_SANITIZER)
  add_library(pruefstand_geprueft STATIC ${PRUEFSTAND_QUELLEN} ${PRUEFSTAND_KOEPFE})
  target_include_directories(pruefstand_geprueft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(pruefstand_geprueft PUBLIC cxx_std_20)
  fabrik_warnsatz_anlegen(pruefstand_geprueft)
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
  fabrik_warnsatz_anlegen(${name})
  add_test(NAME ${name} COMMAND ${name})
endforeach()

# Hier stand vom 2026-09-05 an einen Lauf lang der Waechter des Warnsatz-Schlussriegels
# aus Paket 0133 -- die `ctest`-Probe `schlussriegel_nachbau` auf
# `befunde/pruefung-0066/nachbau.py`. Paket 0136 hat sie nach
# `werkzeuge/schlussriegel/CMakeLists.txt` gezogen, und der Grund steht dort
# ausgeschrieben. In einem Satz: Sie misst den **Baum** und nicht das Erzeugnis, dieser
# Kasten ist nach T13 das Gestell fuer Mass 1 bis 3 und den Selbstspieler, und der Ort
# war von Anfang an als Kollisionsentscheidung des Projektmanagers gekennzeichnet und
# nicht als Entwurfsentscheidung.
#
# Der Hinweis bleibt stehen, weil er sonst nur noch aus einem Commit-Betreff hervorginge:
# Wer den Waechter hier sucht -- drei Abnahmen aus dem 0133er Umfeld nennen ihn --,
# findet an dieser Stelle, wohin er gegangen ist. Das Skript selbst ist nicht umgezogen.
