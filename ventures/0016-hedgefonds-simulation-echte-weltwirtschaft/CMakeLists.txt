# Arbeitsbereich des Vorhabens 0016 -- die Werkstatt, in die alle Pakete schreiben.
#
# Das ist die C++-Entsprechung des Arbeitsbereichs, den Paket 0004 als `Cargo.toml`
# beschreibt; die Sprache ist seit ADR 0011 (2026-09-01) C++20 mit CMake.
#
# Die Mitglieder sind die aus T13, in der Richtung, die T13 vorgibt:
#
#   kern            (keine Abhaengigkeit)  Zustand, Regeln, Kette, Festkomma, Zufall, Pruefsumme
#     ^
#   daten           -> kern                Jahrgang laden, Sollreihen, Parameterdatei
#     ^
#   schnittstelle   -> kern, daten         Protokoll, drei Zustandsebenen, Partieformat
#     ^          ^
#   konsole      pruefstand                Binaerprogramme: Text und Protokoll / Bots und Masse
#     ^
#   oberflaeche  -> schnittstelle          Binaerprogramm (vertagt, ADR 0010)
#   werkzeuge/aufbereitung -> daten        einmal je Jahrgang: Rohdaten -> Jahrgang
#
# Vier Mitglieder stehen zusaetzlich hier und stammen nicht aus T13:
# `werkzeuge/belegstellen` seit Paket 0059, `werkzeuge/mutation` seit Paket 0110,
# `werkzeuge/bezeichner` seit Paket 0129 und `werkzeuge/schlussriegel` seit Paket 0136.
# Alle vier haengen an nichts und werden von nichts gelinkt. Sie sind Riegel ueber den
# Baum selbst, keine Bausteine des Erzeugnisses. Sie stehen trotzdem in der Liste und
# nicht daneben, weil die Liste die einzige Stelle ist, an der ein Verzeichnis
# eingehaengt wird -- ohne Eintrag liefe ein solcher Riegel nur beim Alleinbau und
# fehlte genau im Arbeitsbereichslauf, den der Uebersetzungsbericht oben fuehrt.
#
# Der Unterschied zwischen ihnen ist der Aufrufort. Belegstellen-, Bezeichner- und
# Schlussriegelwaechter haengen als `add_test` in `ctest` und laufen damit bei jeder
# Abnahme mit; sie lesen den Baum und kosten unter einer Sekunde, der Schlussriegel-
# waechter 4,2 Sekunden. Der Mutationslauf tut das ausdruecklich nicht: Ein Fall kostet
# Uebersetzen, Binden und einen Probenlauf, und ein Katalog ueber alle Module waechst
# schnell auf Minuten. Er ist ein eigenes Ziel, das gerufen wird, wenn jemand es braucht
# -- entschieden vom Projektmanager am 2026-09-05 im Rumpf des Pakets 0110. Sein Eintrag
# hier hebt deshalb die Zahl der konfigurierten Ziele, nicht die Zahl der Proben.
#
# `werkzeuge/schlussriegel` ist der einzige der vier ohne uebersetzendes Ziel -- er
# traegt nur eine Bahn zu einem Skript. Er bindet deshalb als einziges Mitglied des Baums
# die `werkzeugkette.cmake` beim Alleinbau **nicht** ein; die Begruendung steht in seiner
# eigenen Datei und nicht hier, weil sie den Schlussriegel jener Datei betrifft.
#
# In diesem Paket bekommt nur `kern` ein Verzeichnis. Die uebrigen legt jeweils ihr
# eigenes Paket an -- deshalb wird jedes Mitglied hier nur dann eingebunden, wenn es
# schon existiert. Das ist keine Bequemlichkeit, sondern derselbe Kollisionsschutz
# wie die Platzhalterdateien im Kern: So muss kein spaeteres Paket diese Datei
# anfassen, und zwei Bauagenten treffen sich nie darin.

cmake_minimum_required(VERSION 3.22)

project(hedgefonds
        VERSION 0.1.0
        DESCRIPTION "Hedgefonds-Simulation auf einer echten Weltwirtschaft -- Arbeitsbereich"
        LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/werkzeugkette.cmake)

enable_testing()

set(FABRIK_MITGLIEDER
    kern
    daten
    schnittstelle
    konsole
    pruefstand
    oberflaeche
    werkzeuge/aufbereitung
    werkzeuge/belegstellen
    werkzeuge/mutation
    werkzeuge/bezeichner
    werkzeuge/schlussriegel)

foreach(mitglied IN LISTS FABRIK_MITGLIEDER)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${mitglied}/CMakeLists.txt)
    add_subdirectory(${mitglied})
  else()
    message(STATUS "Mitglied '${mitglied}' ist noch nicht gebaut -- uebersprungen.")
  endif()
endforeach()
