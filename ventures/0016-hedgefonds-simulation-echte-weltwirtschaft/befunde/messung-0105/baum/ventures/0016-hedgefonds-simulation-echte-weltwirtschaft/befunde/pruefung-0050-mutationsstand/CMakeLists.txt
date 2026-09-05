# Mutationsstand zur Pruefung von Paket 0050 -- test-pruefer, 2026-09-04.
#
# Zweck: Bedingung 2 der Abnahme sagt, `REFERENZFOLGE`, `REFERENZTABELLE` und
# `REFERENZPROFIL` behielten "Zeichen fuer Zeichen ihren Wert". Dass sie es taten,
# zeigt der Diff. Dass es **etwas bedeutet**, zeigt der Diff nicht: Waeren die drei
# nur Zierat, waere ihre Unversehrtheit ein Kriterium ueber nichts. Dieser Stand
# uebersetzt die **unveraenderte** Probe des Pakets je einmal gegen eine geaenderte
# Fassung genau dieser drei Werte und dreht das Urteil um: `ctest` gruen heisst
# *Kontrollfassung besteht, und jede Mutation wird gefangen*.
#
# Der Stand fasst keine Datei des Pakets an. Die Mutanten entstehen im Bauverzeichnis.
#
#   cmake -S <dieses Verzeichnis> -B $TMPDIR/mut0050 && cmake --build $TMPDIR/mut0050
#   cd $TMPDIR/mut0050 && ctest

cmake_minimum_required(VERSION 3.22)
project(mutationsstand_0050 LANGUAGES CXX)
enable_testing()

set(PS "${CMAKE_CURRENT_LIST_DIR}/../../pruefstand")
set(QUELLE "${PS}/test/vorrat_verfahren_probe.cpp")

# Das gepruefte Modul unveraendert -- mutiert wird ausschliesslich die Probe.
add_library(ps STATIC ${PS}/src/vorrat.cpp ${PS}/src/vorrat_verfahren.cpp)
target_include_directories(ps PUBLIC ${PS}/include)
target_compile_features(ps PUBLIC cxx_std_20)

# `original` leer heisst: Kontrollfassung, unveraendert uebersetzt.
# Die Fehlerbremse ist Absicht: Ein Tippfehler im Suchmuster erzeugte sonst eine
# unveraenderte Datei, die brav besteht -- und ich zaehlte ihr Bestehen als
# Empfindlichkeit der Probe. Das waere genau der Fehler, den ich suchen soll.
function(mutant name original ersatz sollrot)
  file(READ ${QUELLE} inhalt)
  if(NOT original STREQUAL "")
    string(FIND "${inhalt}" "${original}" pos)
    if(pos LESS 0)
      message(FATAL_ERROR "Mutant ${name}: Suchmuster nicht gefunden.")
    endif()
    string(REPLACE "${original}" "${ersatz}" inhalt "${inhalt}")
  endif()
  set(ziel ${CMAKE_BINARY_DIR}/${name}.cpp)
  file(WRITE ${ziel} "${inhalt}")
  add_executable(${name} ${ziel})
  target_link_libraries(${name} PRIVATE ps)
  add_test(NAME ${name} COMMAND ${name})
  if(sollrot)
    set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
  endif()
endfunction()

# M0 -- Kontrolle. Muss gruen sein, sonst misst der Stand meinen eigenen Eingriff.
mutant(m0_kontrolle "" "" FALSE)

# M1..M3 -- die drei Werte aus Bedingung 2, je eine Ziffer verstellt.
mutant(m1_referenzfolge
  "REFERENZFOLGE = \"1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5\""
  "REFERENZFOLGE = \"1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,4\""
  TRUE)

mutant(m2_referenztabelle
  "Rundenfolge{2, 3, 4},"
  "Rundenfolge{2, 3, 5},"
  TRUE)

mutant(m3_referenzprofil
  "REFERENZPROFIL = Profil{1, 1, 1, 1, 1}"
  "REFERENZPROFIL = Profil{2, 1, 1, 1, 0}"
  TRUE)

# M4 -- die neue Belegstelle selbst. Erwartung ausdruecklich **gruen**: Sie wird
# gedruckt, nicht geprueft. Der Mutant misst diese Luecke, statt sie zu behaupten.
mutant(m4_belegstelle
  "BELEGSTELLE =\n    \"spiel.md, Abschnitt"
  "BELEGSTELLE =\n    \"GIBT-ES-NICHT.md, Abschnitt"
  FALSE)
