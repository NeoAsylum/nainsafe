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

# ---------------------------------------------------------------------------
# Der Waechter des Warnsatz-Schlussriegels -- Paket 0133
# ---------------------------------------------------------------------------
#
# Der Schlussriegel aus `werkzeugkette.cmake` laeuft bei **jeder** Konfiguration mit,
# und trotzdem hatte er bis zum 2026-09-05 keinen Regressionsnachweis. Der Grund steht
# im Kopf des Skripts unten: Im echten Baum steht nirgends ein `-w`. Ein Riegel, der
# nur ueber fehlerfreie Baeume faehrt, kann Fehlalarm zeigen und sonst nichts -- seine
# eigene Stumpfheit sieht er nie. Wer die Pruefung im Riegel abschaltet, bekommt einen
# gruenen Baum und keine Meldung.
#
# `befunde/pruefung-0066/nachbau.py` schliesst diese Luecke: 22 Wegwerf-Baeume unter
# einer eigenen Ablage, jeder mit einem anderen Weg, den Warnsatz auszuhebeln, dazu
# die Positivkontrolle `p_positiv`, die ohne Abschalter rot bauen **muss**. Er hing
# aber in keinem `add_test`, in keinem Ziel und in keinem Baulauf. Gelaufen ist er nur,
# weil einzelne Abnahmen ihn namentlich nannten -- ein Waechter, dessen Aufruf in
# fremder Prosa steht, ist beim uebernaechsten Paket fort.
#
# **Warum die Bahn hier liegt und nicht unter `werkzeuge/`.** Sachlich gehoerte sie
# dorthin: Der Nachbau misst den **Baum**, nicht das Erzeugnis, und der
# Belegstellenriegel loest dieselbe Frage seit Paket 0059 ueber ein eigenes Mitglied.
# Ein eigenes Mitglied muss aber in `FABRIK_MITGLIEDER` der `CMakeLists.txt` des
# Vorhabens eingetragen werden, und die haelt am 2026-09-05 ein anderes offenes Paket.
# Die Wahl ist damit eine Kollisionsentscheidung (Paket 0133, Vermerk 2) und keine
# Aussage darueber, dass der Nachbau zum Pruefstand gehoerte. Sie kostet nichts als
# den Ort: Die Probe haengt an keinem Ziel dieses Kastens, linkt nichts und wird von
# nichts gelinkt. Zieht sie spaeter jemand nach `werkzeuge/`, bleibt der Aufruf
# derselbe.
#
# **Der Preis, gemessen statt geschaetzt:** 4,5 Sekunden kalt fuer alle 22 Baeume
# (2026-09-05). Damit liegt der Nachbau auf der billigen Seite der Grenze, die der
# Projektmanager im Rumpf von Paket 0110 gezogen und im Kopf der `CMakeLists.txt` des
# Vorhabens festgehalten hat: Der Belegstellenriegel haengt als `add_test` in `ctest`
# und laeuft bei jeder Abnahme mit, der Mutationslauf ausdruecklich nicht, weil ein
# einziger Fall dort Uebersetzen, Binden und einen Probenlauf kostet.
get_filename_component(FABRIK_VORHABEN ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(FABRIK_NACHBAU ${FABRIK_VORHABEN}/befunde/pruefung-0066/nachbau.py)

# Kein `if(EXISTS ... ) add_test() endif()`. Genau diese Bauform ist der Fehler, gegen
# den dieses Paket geschrieben ist: Sie laesst den Waechter still verschwinden, sobald
# jemand die Datei verschiebt, und meldet danach eine gruene Abnahme ueber einen Baum
# ohne Waechter. Fehlt die Datei, bricht die Konfiguration ab und sagt, was zu tun ist.
if(NOT EXISTS ${FABRIK_NACHBAU})
  message(FATAL_ERROR
          "Der Regressionsnachweis des Schlussriegels fehlt: ${FABRIK_NACHBAU}\n"
          "Er ist der einzige Nachweis, dass der Riegel in `werkzeugkette.cmake` noch "
          "prueft, statt nur zu laufen. Ist er absichtlich umgezogen, gehoert der neue "
          "Pfad hierher -- nicht diese Bedingung entfernt.")
endif()

# Derselbe Gedanke einen Schritt weiter: Wird kein Deuter gefunden, wird `python3`
# trotzdem eingetragen. Dann meldet `ctest` die Probe rot ("Unable to find executable"),
# statt dass sie lautlos aus der Liste faellt. Ein uebersprungener Waechter sieht im
# Bericht aus wie ein bestandener.
find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
  set(FABRIK_PYTHON ${Python3_EXECUTABLE})
else()
  set(FABRIK_PYTHON python3)
  message(WARNING "Kein Python3 gefunden -- die Probe `schlussriegel_nachbau` faellt "
                  "auf `python3` aus dem Suchpfad zurueck und wird rot, wenn es das "
                  "nicht gibt.")
endif()

add_test(NAME schlussriegel_nachbau COMMAND ${FABRIK_PYTHON} ${FABRIK_NACHBAU})

# `NACHBAU_ABLAGE` zeigt in den Baubaum und nicht nach `$TMPDIR`. Der Vorgabepfad des
# Skripts haengt allein am Stand (`nachbau0066-HEAD`), also am selben Ort fuer jeden
# Baum -- zwei Baeume nacheinander, wie sie jede Gegenprobe fahrt, liefen einander in
# die Ablage. Unter dem Baubaum ist sie je Baum und je Profil eine eigene und
# verschwindet mit ihm. `bau/` ist in `.gitignore` und in `UNGELESENE_ORDNER` des
# Belegstellenriegels, die 22 Wegwerf-Manifeste stoeren dort also niemanden.
#
# Die Zeitgrenze ist keine Schaetzung nach oben, sondern das Vielfache des gemessenen
# Werts: 4,5 Sekunden kalt, 600 Sekunden Grenze. Sie soll nicht knapp sein, sie soll
# verhindern, dass ein haengendes `cmake` den Nachtlauf blockiert.
set_tests_properties(schlussriegel_nachbau PROPERTIES
                     TIMEOUT 600
                     ENVIRONMENT "NACHBAU_ABLAGE=${CMAKE_CURRENT_BINARY_DIR}/nachbau0066")
