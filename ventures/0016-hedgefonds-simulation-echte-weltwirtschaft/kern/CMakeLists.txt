# Der Kern -- die einzige Bibliothek des Vorhabens ohne jede Abhaengigkeit.
#
# T2: **null Fremdabhaengigkeiten.** In Rust stuende hier ein leerer Abschnitt
# `[dependencies]`. C++ hat keinen solchen Abschnitt; die Entsprechung ist, dass der
# Kern nichts hereinholt und nichts dazulinkt.
#
#   Mechanischer Nachweis (T2), zwei Mustervergleiche ueber diese Datei: Der erste
#   sucht jede Anweisung, die fremden Code hereinholt oder ein weiteres Verzeichnis
#   dazunimmt, der zweite jede Bibliothek, die an den Kern gelinkt wird. Beide muessen
#   leer ausgehen. Ihr Wortlaut steht in der Abnahme von Paket 0004, Bedingung 3, und
#   absichtlich nicht hier: Eine Datei, die ihre eigenen Suchmuster zitiert, laesst sie
#   nie leer ausgehen, und die Ausnahme davon gehoerte dann ins Kriterium statt in die
#   geprueften Zeilen.
#
# Ein Kasten ohne Abhaengigkeiten kann durch kein fremdes Versionsupdate sein
# Ergebnis aendern. Die Standardbibliothek ist keine Fremdabhaengigkeit: Sie kommt
# mit dem Uebersetzer, den `werkzeugkette.cmake` festnagelt.

cmake_minimum_required(VERSION 3.22)

project(kern LANGUAGES CXX)

# Wird dieses Verzeichnis allein gebaut -- `baulauf.py` tut genau das, es sucht jede
# CMakeLists.txt einzeln --, dann gilt die Werkzeugkette des Arbeitsbereichs
# trotzdem. Beim Bau ueber den Arbeitsbereich ist sie schon eingebunden.
if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../werkzeugkette.cmake)
  enable_testing()
endif()

# Der Warnsatz `FABRIK_STRENGE` -- das, was hier an die Stelle von Rusts
# `#![forbid(unsafe_code)]` tritt -- stand bis zum 2026-09-02 an dieser Stelle und
# steht seit Paket 0031 in `werkzeugkette.cmake`, samt seiner vollstaendigen
# Begruendung und den beiden kernlokalen Massnahmen daneben (Gleitkommasperre,
# Grep-Regel). Der Grund fuer den Umzug: `set()` ist verzeichnisgebunden, der
# Pruefstand musste den Satz deshalb abschreiben, und ein abgeschriebener Warnsatz mit
# einer verlorenen Zeile uebersetzt gruen und prueft weniger.
#
# Angehaengt wird er seit Paket 0046 nicht mehr hier, sondern von
# `fabrik_warnsatz_anlegen(<ziel>)` aus derselben Datei. Der Grund steht dort: Haengt ein
# Mitglied den Satz selbst an und fehlt ihm der `PROJECT_IS_TOP_LEVEL`-Block, dann haengt
# es eine leere Liste an -- eine undefinierte Variable ist in CMake kein Fehler, sondern
# nichts. Der Kasten uebersetzt gruen und prueft weniger. Ein Aufruf, den CMake nicht
# kennt, bricht dagegen ab. Die Funktion gibt es nur, wenn die Werkzeugkette eingebunden
# ist; damit ist der Block oben nicht mehr vergessbar, sondern erzwungen.

# Die Quellen werden eingesammelt statt aufgezaehlt, und der Grund ist derselbe wie
# beim Arbeitsbereich: Jedes spaetere Kernpaket bringt genau seine eigene Datei mit
# und muss diese hier nicht anfassen. `CONFIGURE_DEPENDS` laesst CMake beim Bau
# nachsehen, ob eine dazugekommen ist.
file(GLOB KERN_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB KERN_KOEPFE  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/kern/*.hpp)

# Die Proben werden seit Paket 0139 hier eingesammelt und nicht erst unten bei den
# Testzielen: Der Sperrebindungsriegel darunter prueft sie mit denselben zwei
# Bedingungen wie die Bibliotheksquellen, und er steht vor den `add_library`-Aufrufen.
# Es bleibt bei **einem** Sammler fuer die Proben -- zwei Aufrufe auf dasselbe Muster
# koennten auseinanderlaufen, und dann pruefte der Riegel eine andere Menge, als
# gebaut wird.
file(GLOB KERN_PROBEN  CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

# Die Koepfe unter `test/` -- ein **dritter** Sammler und nicht der Probensammler
# erweitert (Paket 0254). Der Grund steht weiter unten in der Schleife ueber
# `KERN_PROBEN`: Dieselbe Liste speist `add_executable`, ein Kopf darin wuerde sein
# eigenes Programm. Diese Menge wird geprueft und nicht gebaut, und sie ist deshalb
# eine eigene.
file(GLOB KERN_PROBENKOEPFE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp)

# ---------------------------------------------------------------------------
# Der Sperrebindungsriegel (Paket 0134)
# ---------------------------------------------------------------------------
#
# `include/kern/sperre.hpp` vergiftet das Gleitkomma (T4) und die beiden
# Ueberlaufbausteine (T7, Massnahme 4, Punkt 2). Ein `#pragma GCC poison` wirkt ab der
# Zeile, an der es steht, bis zum Ende der Uebersetzungseinheit -- beide Sperren gelten
# also genau fuer die Quellen, die den Kopf binden, und dort erst ab seiner Zeile.
# Daraus die Einbauregel, die im Kopf selbst begruendet ist: Er ist der **letzte**
# `#include` jeder Kernquelle. Sie ist der Grund, warum die Sperre ohne Ausnahmeliste
# auskommt -- `festkomma.hpp` darf die vergifteten Bausteine benutzen, weil es fertig
# gelesen ist, bevor die Vergiftung gilt.
#
# Gehalten wurde diese Regel bis zum 2026-09-05 von nichts. Im Kopf steht ein `grep`
# als Nachweis, und ein `grep` in einem Kommentar laeuft nur, wenn ihn jemand liest und
# tippt.
#
# Der Riegel gehoert genau hierhin, weil die Sammler darueber die Luecke aufmachen:
# Sie lesen Quellen und Proben ein, statt sie aufzuzaehlen. Das ist gewollt
# -- jedes spaetere Kernpaket bringt seine Datei mit und muss keine Bauliste anfassen.
# Der Preis ist, dass eine Quelle **ohne** die Sperre ebenso ohne jeden Eingriff in
# beide Bibliotheken kommt. Gemessen im Vorschlag zu diesem Paket: eine zugelegte
# `src/luecke.cpp` mit einer Rechnung auf `double` und einer eigenen Fassung der
# Strichrechnung wird in `kern` **und** in `kern_geprueft` uebersetzt und laeuft gruen
# durch jede Probe.
#
# Warum beim Konfigurieren und nicht im Belegstellenriegel: Die Pruefung braucht keine
# Uebersetzung und kein eigenes Binaerprogramm, und sie schlaegt zu, **bevor** gebaut
# wird, statt danach.
#
# Zwei Bedingungen, und genau die halten die beiden Abbruchmeldungen auseinander: Der
# Kopf ist gebunden, und er ist als letzter gebunden. Ein zweites Vorkommen weiter oben
# faengt der Riegel nicht ab -- `#pragma once` macht es folgenlos, und die zweite
# Bedingung haelt die Reihenfolge trotzdem.
#
# **Was er nicht sieht**, damit es niemand fuer geprueft haelt: Er liest Zeilen, er
# verarbeitet nicht vor. Eine `#include`-Zeile innerhalb eines `/* */`-Blocks oder
# hinter einem `#if 0` zaehlt er mit.
#
# Seit Paket 0139 deckt er **beide** Mengen, `src/*.cpp` und `test/*.cpp`, mit
# denselben zwei Bedingungen und derselben Meldung. Unterschieden werden die beiden
# nur am Namen: Die Meldung nennt den Pfad ab `kern/`, also `src/...` oder `test/...`.
#
# Warum die Proben dazugehoeren, obwohl sie keine Uebersetzungseinheit der beiden
# Bibliotheken sind: Sie sind die teurere Haelfte, nicht die billigere. Was eine
# Bibliotheksquelle falsch rechnet, faellt an einer Probe auf. Was eine **Probe**
# falsch rechnet, faellt an nichts auf -- sie ist die Stelle, die den Sollwert nennt.
# Eine Probe, die ihren Erwartungswert auf `double` ausrechnet oder eine eigene
# Fassung der Strichrechnung mitbringt, uebersetzt gruen und deckt von da an genau die
# Abweichung zu, gegen die sie geschrieben wurde.
set(KERN_SPERRKOPF "kern/sperre.hpp")
string(REPLACE "." "\\." KERN_SPERRKOPF_MUSTER "${KERN_SPERRKOPF}")
set(KERN_SPERRKOPF_MUSTER "[\"<]${KERN_SPERRKOPF_MUSTER}[\">]")

# Der Pfad zum Sperrkopf wird aus seinem Include-Namen gebildet und nicht ein zweites
# Mal hingeschrieben: Die Vergiftungspruefung unten liest die Datei, und zwei Fassungen
# desselben Pfades koennten auf zwei verschiedene Dateien zeigen.
set(KERN_SPERRKOPF_DATEI "${CMAKE_CURRENT_SOURCE_DIR}/include/${KERN_SPERRKOPF}")

# `CONFIGURE_DEPENDS` am Sammler oben bemerkt nur neue und verschwundene Dateien. Wer
# die Include-Zeile aus einer **vorhandenen** Quelle entfernt, aendert die Dateiliste
# nicht; ohne die folgende Zeile liefe der naechste Bau ohne neuen Konfigurationslauf
# und damit ohne diesen Riegel. Sie gilt fuer alle drei Mengen.
#
# Der Sperrkopf steht seit Paket 0254 mit darin, und zwar als **Inhalt** und nicht als
# Vorhandensein: Aus ihm kommt die Liste der vergifteten Bezeichner. Ein zugelegter
# Eintrag dort muss den naechsten Konfigurationslauf ausloesen, sonst wird gegen die
# Liste von gestern geprueft.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
             ${KERN_QUELLEN} ${KERN_PROBEN} ${KERN_PROBENKOEPFE}
             ${KERN_SPERRKOPF_DATEI})

foreach(datei IN LISTS KERN_QUELLEN KERN_PROBEN)
  file(READ "${datei}" fabrik_inhalt)

  # Der Kurzname wird gegen `kern/` gebildet und traegt damit sein Verzeichnis:
  # `src/festkomma.cpp` gegen `test/festkomma_probe.cpp`. Das ist der einzige
  # Unterschied, den die Meldungen zwischen den beiden Mengen machen -- und er
  # genuegt, weil die Bedingung fuer beide dieselbe ist.
  file(RELATIVE_PATH fabrik_kurzname "${CMAKE_CURRENT_SOURCE_DIR}" "${datei}")

  # Gesucht wird die Include-**Anweisung**, nicht die Zeile: vom Zeilenanfang bis zur
  # schliessenden Klammer des Kopfnamens. Ein Zeilenkommentar dahinter -- jede
  # Kernquelle hat einen -- bleibt damit draussen, und mit ihm jedes Semikolon, das
  # sonst die CMake-Liste unter dem Ergebnis zerteilen wuerde. Die vorangestellte
  # Zeilenschaltung faengt den Fall, dass schon die erste Zeile der Datei ein
  # `#include` ist.
  string(REGEX MATCHALL "\n[ \t]*#[ \t]*include[ \t]*[\"<][^\"<>\n]*[\">]"
         fabrik_bindungen "\n${fabrik_inhalt}")

  list(LENGTH fabrik_bindungen fabrik_anzahl)
  set(fabrik_treffer 0)
  foreach(bindung IN LISTS fabrik_bindungen)
    if("${bindung}" MATCHES "${KERN_SPERRKOPF_MUSTER}")
      math(EXPR fabrik_treffer "${fabrik_treffer} + 1")
    endif()
  endforeach()

  if(fabrik_treffer EQUAL 0)
    message(FATAL_ERROR
      "Sperrebindungsriegel (T4, T7 Massnahme 4.2): '${fabrik_kurzname}' bindet "
      "\"${KERN_SPERRKOPF}\" nicht. In dieser Uebersetzungseinheit gilt damit weder "
      "die Gleitkommasperre noch die Sperre der Ueberlaufbausteine -- die Datei wird "
      "trotzdem gebaut: unter `src/` in `kern` und `kern_geprueft`, unter `test/` als "
      "eigenes Programm auf denselben Werten. Die fehlende Zeile gehoert ans Ende des "
      "Include-Blocks.")
  endif()

  math(EXPR fabrik_letzter "${fabrik_anzahl} - 1")
  list(GET fabrik_bindungen ${fabrik_letzter} fabrik_schluss)
  string(STRIP "${fabrik_schluss}" fabrik_schluss)
  if(NOT "${fabrik_schluss}" MATCHES "${KERN_SPERRKOPF_MUSTER}")
    message(FATAL_ERROR
      "Sperrebindungsriegel (T4, T7 Massnahme 4.2): '${fabrik_kurzname}' bindet "
      "\"${KERN_SPERRKOPF}\", aber nicht als letzten `#include` -- zuletzt steht "
      "dort `${fabrik_schluss}`. Die Vergiftung gilt erst ab ihrer Zeile; was danach "
      "eingebunden wird, ist ungesperrt.")
  endif()
endforeach()

# ---------------------------------------------------------------------------
# Die Vergiftungspruefung der Probenkoepfe (Paket 0254)
# ---------------------------------------------------------------------------
#
# **Was der Riegel darueber nicht sieht.** Seine beiden Sammler nehmen die Endung einer
# Quelle, der dritte daneben nimmt allein die Koepfe unter `include/kern/` und wird von
# ihm gar nicht gelesen. Ein Kopf unter `test/` stand damit in keiner Menge. Gemessen am
# ersten seiner Art, dem Kennzeichenverzeichnis der Proben: Er bindet den Sperrkopf
# nicht, nichts verlangte es, und nichts bemerkte es. Warum ein Kopf unter `test/` die
# teurere Haelfte ist und nicht die billigere, steht in der Begruendung des Riegels
# darueber und wird hier nicht wiederholt -- er nennt den Sollwert fuer jede Probe, die
# ihn teilt.
#
# **Welche Zusicherung dieses Paket gekauft hat -- und welche nicht.** Nicht die des
# Riegels darueber. Sie ist fuer einen Kopf unter `test/` nicht zu haben, und zwar aus
# zwei Gruenden, die beide nicht an dieser Datei liegen: Die Vergiftung gilt ab ihrer
# Stelle bis zum Ende der Uebersetzungseinheit, ein Kopf, den eine Probe vor den Koepfen
# des Kerns einbindet, vergiftete diese also mit. Und ob der Sperrkopf zuletzt gebunden
# ist, ist eine Eigenschaft des Einbindenden und nicht des Eingebundenen.
#
# Gekauft ist stattdessen die **Wirkung ohne den Mechanismus**: Ein Kopf unter `test/`
# nennt keinen der Bezeichner, die der Sperrkopf vergiftet. Das ist dasselbe, was der
# Vorverarbeiter einer Quelle zusichert, die ihn bindet -- nur am Text nachgewiesen
# statt an der Uebersetzung.
#
# **Der Unterschied zwischen beidem, in beide Richtungen genannt, damit ihn niemand fuer
# keinen haelt:**
#
#   * *Strenger als die Vergiftung.* Hier wird gelesen und nicht vorverarbeitet. Ein
#     vergifteter Name in einem Kommentar oder hinter einem `#if 0` zaehlt mit. Das ist
#     dieselbe Grobheit, die der Riegel darueber fuer sich schon erklaert, und sie faellt
#     in die sichere Richtung: Sie meldet zu viel, nie zu wenig.
#   * *Schwaecher als die Vergiftung.* Ein vergifteter Name, der erst aus einer
#     Makroersetzung entsteht, steht nirgends im Text und kommt durch. Der Vorverarbeiter
#     faenge ihn. Wer diese Luecke schliessen will, braucht eine Uebersetzung und damit
#     ein anderes Verfahren als ein Konfigurationslauf.
#
# **Die Liste wird gelesen und nicht abgeschrieben.** Sie steht im Sperrkopf und dort
# allein; eine zweite Fassung an dieser Stelle liefe mit dem naechsten Eintrag
# auseinander und pruefte danach weniger -- gruen, wie jede abgeschriebene Liste. Gesucht
# werden die Anweisungen selbst, am Zeilenanfang: Der Kopfkommentar derselben Datei nennt
# dieselben drei Woerter, und ohne die Verankerung zaehlte er mit.
#
# **Findet die Suche keinen Bezeichner, bricht der Lauf ab.** Eine leere Liste liesse die
# Schleife darunter ueber nichts laufen, und jeder Kopf kaeme durch: eine Zusicherung,
# die auf keine Eingabe rot werden kann, ist keine. Aus demselben Grund steht in der
# Meldung am Ende die **Zahl** der geprueften Paare und nicht der Satz, es sei geprueft
# worden.
#
# **Rot, wenn gebrochen -- der Weg durch den Code, weil sich der Konfigurationslauf aus
# keiner Rolle heraus starten laesst.** Der Sammler weiter oben legt jeden Kopf unter
# `test/` in `KERN_PROBENKOEPFE`. Die Schleife darunter liest jeden davon und haelt ihn
# gegen jeden Namen aus `KERN_VERGIFTET`. Trifft das Muster, ruft sie `message` mit
# `FATAL_ERROR`, und damit endet der Konfigurationslauf sofort: Es entsteht kein
# Bauverzeichnis, die `add_library`-Aufrufe darunter werden nie erreicht, `cmake --build`
# und `ctest` laufen nicht an. Ein Kopf unter `test/`, der einen vergifteten Bezeichner
# nennt, kommt also nicht bis zum Ende des Laufs -- und die Meldung mit den Zahlen, an
# der ein gruener Lauf zu erkennen ist, steht hinter ihm.

if(NOT EXISTS "${KERN_SPERRKOPF_DATEI}")
  message(FATAL_ERROR
    "Vergiftungspruefung der Probenkoepfe (T4, T7 Massnahme 4.2): der Sperrkopf fehlt, "
    "gesucht wurde er unter ${KERN_SPERRKOPF_DATEI}. Aus ihm kommt die Liste der "
    "vergifteten Bezeichner; ohne ihn pruefte die Schleife darunter gegen nichts und "
    "liesse jeden Kopf unter test/ durch. Ist er umgezogen, gehoert der neue Pfad "
    "hierher -- nicht diese Bedingung entfernt.")
endif()

file(READ "${KERN_SPERRKOPF_DATEI}" fabrik_sperrtext)

# Die vorangestellte Zeilenschaltung faengt den Fall, dass die Anweisung schon in der
# ersten Zeile steht -- derselbe Griff wie beim Riegel darueber.
string(REGEX MATCHALL "\n[ \t]*#[ \t]*pragma[ \t]+GCC[ \t]+poison[ \t][^\n]*"
       fabrik_vergiftungen "\n${fabrik_sperrtext}")

set(KERN_VERGIFTET "")
foreach(anweisung IN LISTS fabrik_vergiftungen)
  # Geschrieben wird auf eine eigene Veraenderliche und nicht auf die der Schleife: Was
  # eine Schleifenveraenderliche nach einer Zuweisung im Rumpf ist, gehoert zu den
  # Dingen, die man nachschlagen muss, und hier steht nichts darauf.
  set(fabrik_namensteil "${anweisung}")

  # Ein Kommentar hinter der Anweisung traegt Woerter, die wie Bezeichner aussehen und
  # keine sind. Er wird abgeschnitten, bevor gesammelt wird.
  string(REGEX REPLACE "//.*$"   "" fabrik_namensteil "${fabrik_namensteil}")
  string(REGEX REPLACE "/\\*.*$" "" fabrik_namensteil "${fabrik_namensteil}")
  string(REGEX REPLACE "^[ \t\n]*#[ \t]*pragma[ \t]+GCC[ \t]+poison[ \t]+" ""
         fabrik_namensteil "${fabrik_namensteil}")
  string(REGEX MATCHALL "[A-Za-z_][A-Za-z0-9_]*" fabrik_namen "${fabrik_namensteil}")
  list(APPEND KERN_VERGIFTET ${fabrik_namen})
endforeach()

list(LENGTH KERN_VERGIFTET fabrik_anzahl_vergiftet)
if(fabrik_anzahl_vergiftet EQUAL 0)
  message(FATAL_ERROR
    "Vergiftungspruefung der Probenkoepfe (T4, T7 Massnahme 4.2): in "
    "${KERN_SPERRKOPF_DATEI} steht keine einzige Vergiftungsanweisung, die sich lesen "
    "laesst. Entweder ist die Sperre fort -- dann ist das der Fund --, oder die "
    "Anweisungen sind umgeschrieben und dieser Lesevorgang zieht nach. Weitergelaufen "
    "wird nicht: Eine Pruefung ueber eine leere Namensliste laesst jeden Kopf unter "
    "test/ durch und meldet dabei gruen.")
endif()
list(REMOVE_DUPLICATES KERN_VERGIFTET)
list(LENGTH KERN_VERGIFTET fabrik_anzahl_vergiftet)

set(fabrik_probenkopf_paare 0)
foreach(datei IN LISTS KERN_PROBENKOEPFE)
  file(READ "${datei}" fabrik_inhalt)
  file(RELATIVE_PATH fabrik_kurzname "${CMAKE_CURRENT_SOURCE_DIR}" "${datei}")

  # Gesucht wird der **Name** und nicht die Zeichenfolge: Links und rechts von ihm muss
  # ein Zeichen stehen, das kein Namenszeichen ist, damit `exp` nicht in `export` und
  # `pow` nicht in `power` trifft. Gepolstert wird an beiden Enden, weil diesem Zeichen
  # sonst ein Name in der ersten und in der letzten Zeile entginge.
  set(fabrik_gepolstert "\n${fabrik_inhalt}\n")

  foreach(name IN LISTS KERN_VERGIFTET)
    math(EXPR fabrik_probenkopf_paare "${fabrik_probenkopf_paare} + 1")
    if("${fabrik_gepolstert}" MATCHES "[^A-Za-z0-9_]${name}[^A-Za-z0-9_]")
      message(FATAL_ERROR
        "Vergiftungspruefung der Probenkoepfe (T4, T7 Massnahme 4.2): "
        "'${fabrik_kurzname}' nennt `${name}` -- einen Bezeichner, den "
        "\"${KERN_SPERRKOPF}\" vergiftet. Ein Kopf unter test/ kann den Sperrkopf nicht "
        "binden: Er wird vor den Koepfen des Kerns eingebunden und vergiftete sie mit. "
        "An die Stelle der Vergiftung tritt fuer ihn diese Pruefung, und sie verlangt "
        "dasselbe. Was gerechnet werden muss, gehoert in den Kern und nicht in einen "
        "Kopf, der den Sollwert der Proben nennt.")
    endif()
  endforeach()
endforeach()

# Die beiden Zahlen stehen in der Meldung und in keiner Abnahme: Sie sind eine Messung
# mit Verfallsdatum, die mit jeder neuen Kernquelle und jeder neuen Probe steigt.
#
# **Getrennt** genannt, und das ist keine Kosmetik: Eine Summe verschweigt, wenn eine
# der Mengen leer bleibt. Ein Riegel, dem der zweite Sammler abhanden kaeme, meldete dann
# weiter eine plausible Zahl und saehe aus wie einer, der beides prueft.
#
# Seit Paket 0254 stehen zwei Zahlen mehr da, und beide aus diesem Grund: die Zahl der
# Koepfe unter `test/` und die der geprueften Paare aus Kopf und vergiftetem Bezeichner.
# Ein leerer Sammler und eine leere Namensliste sehen im Ergebnis gleich aus -- gruen --,
# und genau daran ist das eine vom anderen zu unterscheiden. Die Paarzahl ist dabei die
# einzige, die beides zugleich beantwortet: Sie ist null, sobald eine der beiden Mengen
# leer ist. Kein Satz steht dort, der behauptet, es sei nichts gefunden worden -- der
# Abbruch darueber hat das schon entschieden, und ein Satz, der es wiederholt, waere die
# eine Aussage, die derselbe Lauf widerlegen koennte.
list(LENGTH KERN_QUELLEN      fabrik_anzahl_quellen)
list(LENGTH KERN_PROBEN       fabrik_anzahl_proben)
list(LENGTH KERN_PROBENKOEPFE fabrik_anzahl_probenkoepfe)
message(STATUS
  "Sperrebindungsriegel (T4, T7 Massnahme 4.2): ${fabrik_anzahl_quellen} Kernquelle(n) "
  "und ${fabrik_anzahl_proben} Probe(n) geprueft, jede bindet "
  "\"${KERN_SPERRKOPF}\" als letzten #include. Dazu "
  "${fabrik_anzahl_probenkoepfe} Kopf/Koepfe unter test/, die ihn nicht binden koennen, "
  "gegen die ${fabrik_anzahl_vergiftet} dort vergifteten Bezeichner gehalten: "
  "${fabrik_probenkopf_paare} Paar(e) geprueft.")

add_library(kern STATIC ${KERN_QUELLEN} ${KERN_KOEPFE})
target_include_directories(kern PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(kern PUBLIC cxx_std_20)
fabrik_warnsatz_anlegen(kern)

# ---------------------------------------------------------------------------
# Das Testprofil (ADR 0011, Massnahme 2)
# ---------------------------------------------------------------------------
#
# `baulauf.py` konfiguriert genau einmal, es gibt also kein zweites Bauprofil, in das
# man die Sanitizer legen koennte. Deshalb steht hier eine zweite Uebersetzung
# derselben Quellen: `kern_geprueft`. Sie ist wortgleich mit `kern`, nur mit
# `-fsanitize=undefined,address` gebaut, und **nur** die Proben linken sie.
#
# Der Umweg ist noetig, weil ein Sanitizer nur findet, was er selbst uebersetzt hat.
# Haetten die Proben die ungepruefte `kern` gelinkt, waere die Massnahme eine
# Behauptung: Sie wuerde den Testcode absichern und den Code, um den es geht, nicht.
if(FABRIK_SANITIZER)
  add_library(kern_geprueft STATIC ${KERN_QUELLEN} ${KERN_KOEPFE})
  target_include_directories(kern_geprueft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  target_compile_features(kern_geprueft PUBLIC cxx_std_20)
  fabrik_warnsatz_anlegen(kern_geprueft)
  target_compile_options(kern_geprueft PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(kern_geprueft    PUBLIC  ${FABRIK_SANITIZER_SCHALTER})
  set(FABRIK_PROBEN_BIBLIOTHEK kern_geprueft)
else()
  set(FABRIK_PROBEN_BIBLIOTHEK kern)
endif()

# Jede Datei unter `test/` wird ein eigenes Programm und ein eigener CTest-Eintrag --
# wieder aus Kollisionsgruenden: Ein spaeteres Paket legt seine Probe daneben, statt
# eine gemeinsame Datei zu erweitern. `KERN_PROBEN` steht seit Paket 0139 weiter oben,
# beim Sammler der Quellen: Der Sperrebindungsriegel braucht die Liste vor den
# Bibliotheken, und gebaut wird genau die Menge, die er geprueft hat.

foreach(probe IN LISTS KERN_PROBEN)
  get_filename_component(name ${probe} NAME_WE)
  add_executable(${name} ${probe})
  target_link_libraries(${name} PRIVATE ${FABRIK_PROBEN_BIBLIOTHEK})
  fabrik_warnsatz_anlegen(${name})
  add_test(NAME ${name} COMMAND ${name})
endforeach()

# ---------------------------------------------------------------------------
# Die Wandschranke -- Paket 0212
# ---------------------------------------------------------------------------
#
# `PARTIELAENGE_HOECHSTENS` in `include/kern/verlauf.hpp` ist die Wand, die T40 ueber die
# Laenge einer Partie zieht. Vier Zusicherungen bewegen sich mit ihr. Drei stehen in
# demselben Kopf; die **bindende** nicht -- sie gehoert `kern::zustandsausgabe` und haelt
# das Kettenblatt gegen `STAPEL_JE_FADEN`.
#
# Wo sie reisst, war bis heute hergeleitet: ein Groessengesetz, gelegt durch die drei
# Waende, die ueberhaupt je jemand uebersetzt hat (26, 482, 483). Der Kopf schreibt
# selbst hin, dass mit den Waenden 138 und 139 nichts uebersetzt worden ist -- und keine
# Rolle dieser Fabrik hat eine Schale, mit der sie es haette nachholen koennen. Paket
# 0195 ist an genau dieser Luecke zurueckgekommen.
#
# Der Eintrag unten schliesst sie: Er uebersetzt beide Waende, jede Nacht, und macht aus
# einer einmaligen Messung eine stehende Regression. Wandert die Grenze -- und Paket 0091
# hat einen vierten Behaelter an dieselbe Wand gehaengt, ohne dass es jemand bemerkte --,
# wird er rot und druckt die **gemessene** Grenze aus, statt sie nur zu bestreiten.
#
# **Was er kostet.** Drei Uebersetzungen **einer** Uebersetzungseinheit mit
# `-fsyntax-only`. Alle vier Zusicherungen stehen in Koepfen, ein einziges `#include`
# erreicht also jede von ihnen; es entsteht keine Objektdatei, keine Bibliothek und keine
# Probe. Das ist noetig und nicht sparsam: Dieser Kasten wird von **beiden** Baeumen
# gelesen -- dem Arbeitsbereich und dem Alleinbau des Kerns --, der Eintrag laeuft also
# zweimal je Nacht, genau wie `zahlwort_reihen`.
#
# Kein `if(EXISTS ...) add_test() endif()`. Genau diese Bauform laesst eine Probe still
# verschwinden, sobald jemand die Datei verschiebt, und meldet danach eine gruene Abnahme
# ueber einen Baum ohne sie. Ausgeschrieben steht die Begruendung im Bauskript des
# Zahlwortriegels.

get_filename_component(FABRIK_WANDSCHRANKE
                       ${CMAKE_CURRENT_SOURCE_DIR}/messung/wandschranke.py ABSOLUTE)

if(NOT EXISTS ${FABRIK_WANDSCHRANKE})
  message(FATAL_ERROR
          "Die Wandschranke fehlt: ${FABRIK_WANDSCHRANKE}\n"
          "Sie ist der einzige Nachweis, dass die bindende Schranke der Wand aus T40 "
          "dort liegt, wo `include/kern/verlauf.hpp` sie ausweist -- und die einzige "
          "Stelle im ganzen Vorhaben, an der eine veraenderte Wand ueberhaupt "
          "uebersetzt wird. Ist sie absichtlich umgezogen, gehoert der neue Pfad "
          "hierher -- nicht diese Bedingung entfernt.")
endif()

# Wird kein Deuter gefunden, wird `python3` trotzdem eingetragen. Dann meldet `ctest` die
# Probe rot ("Unable to find executable"), statt dass sie lautlos aus der Liste faellt.
# Eine uebersprungene Probe sieht im Bericht aus wie eine bestandene.
find_package(Python3 QUIET COMPONENTS Interpreter)
if(Python3_Interpreter_FOUND)
  set(FABRIK_WANDSCHRANKE_PYTHON ${Python3_EXECUTABLE})
else()
  set(FABRIK_WANDSCHRANKE_PYTHON python3)
  message(WARNING "Kein Python3 gefunden -- die Probe `wandschranke` faellt auf "
                  "`python3` aus dem Suchpfad zurueck und wird rot, wenn es das nicht "
                  "gibt.")
endif()

# Der Uebersetzer kommt von CMake und steht nicht im Skript. Das Skript uebersetzt
# unmittelbar, ohne CMake -- ein fest eingebautes `g++` waere ein zweiter Uebersetzer
# neben dem, gegen den dieser Kasten gebaut wird, und ein Unterschied zwischen beiden
# faende sich nirgends wieder.
add_test(NAME wandschranke
         COMMAND ${FABRIK_WANDSCHRANKE_PYTHON} ${FABRIK_WANDSCHRANKE}
                 --uebersetzer ${CMAKE_CXX_COMPILER}
                 --koepfe ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 300 und nicht 900: `agents/baulauf.py` bricht **den ganzen `ctest`-Aufruf** nach 900 s
# ab. Eine Probe mit derselben Grenze koennte das Kontingent allein aufbrauchen, und der
# Bericht nennte dann nicht sie, sondern nur einen abgeschnittenen Lauf.
#
# Die Zahl ist ein Hemmschuh und keine gemessene Zeit -- der Lauf, der sie gesetzt hat,
# hatte keine Schale. Der Kostenpunkt sind drei Uebersetzungen ohne Erzeugnis, im roten
# Fall bis zu vierzehn. Wer den ersten Nachtlauf im Bericht sieht, ersetzt sie durch das
# Vielfache der gemessenen Zeit; ueber zwei Minuten je Lauf gehoert ein Befund dazu.
set_tests_properties(wandschranke PROPERTIES TIMEOUT 300)
