# Der Mutationslauf -- Paket 0110.
#
# Gebaut wie `werkzeuge/belegstellen` daneben, und aus demselben Grund: Das hier ist ein
# Riegel ueber den Baum, kein Baustein des Erzeugnisses. Es haengt an nichts und wird
# von nichts gelinkt.
#
# Diese Datei wird auf zwei Wegen konfiguriert, und beide muessen tragen:
#
#   1. ueber den Arbeitsbereich -- `../../CMakeLists.txt` fuehrt `werkzeuge/mutation`
#      in `FABRIK_MITGLIEDER`;
#   2. allein -- `baulauf.py` sucht **jede** Manifestdatei einzeln und ruft auf jeder
#      `cmake`, `--build` und `ctest`.
#
# Weg 2 ist der Grund fuer den `PROJECT_IS_TOP_LEVEL`-Block: ohne ihn faenden die
# Werkzeugkette (ADR 0011) und `enable_testing()` beim Alleinbau nicht statt. Der
# Belegstellenriegel nebenan stand bis zum 2026-09-04 ohne diesen Block da, und der
# Uebersetzungsbericht jenes Tages fuehrte sein Verzeichnis mit `No project() command is
# present` -- und meldete trotzdem `ergebnis: ok`.

cmake_minimum_required(VERSION 3.22)

project(mutation LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../werkzeugkette.cmake)
  enable_testing()
endif()

# Der Treiber heisst nicht wie das Ziel, das ihn ruft. `mutationslauf` ist der Name, den
# ein Mensch aufruft; `mutationstreiber` ist das Programm dahinter. Zwei Namen, weil
# CMake fuer beides denselben Namensraum benutzt und ein `add_custom_target` mit dem
# Namen eines vorhandenen Programms ein harter Konfigurationsfehler waere.
add_executable(mutationstreiber mutationslauf.cpp)
fabrik_warnsatz_anlegen(mutationstreiber)

# ADR 0011, Massnahme 2. Der Treiber rechnet nichts, aber er indiziert Zeichenketten und
# setzt Teilstuecke von Hand zusammen -- genau die Fehlerklasse, die C++ nicht selbst
# abfaengt und die sich sonst erst beim Kaeufer zeigt. Derselbe Block wie beim
# Belegstellenriegel.
if(FABRIK_SANITIZER)
  target_compile_options(mutationstreiber PRIVATE ${FABRIK_SANITIZER_SCHALTER})
  target_link_options(mutationstreiber    PRIVATE ${FABRIK_SANITIZER_SCHALTER})
endif()

# Die Wurzel kommt von CMake, nicht aus dem Programm -- dieselbe Bauart wie beim
# Belegstellenriegel. Sie zeigt auf das Vorhaben, nicht auf dieses Verzeichnis, und ist
# auf beiden Bauwegen dieselbe.
get_filename_component(FABRIK_VORHABEN_WURZEL
                       ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)

# Der Baubaum, in dem die Objektdateien der Faelle liegen.
#
# Beim Bau ueber den Arbeitsbereich ist `CMAKE_BINARY_DIR` genau dieser Baum -- dort
# stehen `kern`, `pruefstand` und alles weitere. Beim Alleinbau zeigt dieselbe Variable
# in dieses Verzeichnis, und dort steht keine einzige Objektdatei des Kerns; genommen
# wird dann der Baubaum, den `baulauf.py` fuer den Arbeitsbereich anlegt.
#
# Der Unterschied ist keine Feinheit: Ein Lauf gegen den falschen Baubaum findet die
# Schalterdatei nicht und meldet jeden Fall als Fehlschlag -- laut, immerhin, aber am
# falschen Gegenstand.
if(PROJECT_IS_TOP_LEVEL)
  set(FABRIK_MUTATION_BAUBAUM ${FABRIK_VORHABEN_WURZEL}/bau)
else()
  set(FABRIK_MUTATION_BAUBAUM ${CMAKE_BINARY_DIR})
endif()

# Ausdruecklich **kein** `add_test`. Der Aufrufort ist die Entscheidung, um die der
# Vorschlag zu Paket 0110 gebeten hat, und der Projektmanager hat sie am 2026-09-05
# getroffen: `ctest` bleibt frei davon.
#
# Der Grund ist nicht Bequemlichkeit. Ein Fall kostet Uebersetzen, Binden und einen
# Probenlauf -- gemessen im Bereich von Sekunden, nicht von Millisekunden --, und ein
# Katalog ueber alle Module waechst schnell auf Minuten. In dieser Fabrik ist die
# Zeile "alle Proben gruen in beiden Bauprofilen" der Standardnachweis von fast jedem
# Paket und von jedem Pruefer. Minuten dort hinzuzufuegen verteuert jede Abnahme im
# ganzen Vorhaben und nicht nur diese.
#
# Das Ziel ist deshalb ein Ziel, das gerufen wird, wenn jemand es braucht:
#
#   cmake --build <baubaum> --target mutationslauf
#
# `USES_TERMINAL` gibt ihm die Ausgabe ungepuffert -- ein Lauf ueber Minuten, dessen
# Zwischenstand erst am Ende erscheint, sieht bis dahin wie ein Haenger aus.
#
# Was diese Entscheidung kostet, gemessen und nicht befuerchtet: Beim Alleinbau meldet
# `ctest` hier `No tests were found!!!` und gibt trotzdem Code 0 zurueck; der
# Uebersetzungsbericht fuehrt dieses Verzeichnis damit als `ok`. Das ist dieselbe Zeile,
# an der der Belegstellenriegel am 2026-09-04 einen echten Fehler verdeckt hat -- dort
# fehlte der `PROJECT_IS_TOP_LEVEL`-Block, hier ist die Testlosigkeit gewollt. Der
# Unterschied steht deshalb hier ausgeschrieben, damit ein Pruefer die gleiche Zeile
# nicht fuer denselben Fehler haelt: Dieses Verzeichnis hat einen Riegel, er heisst
# `mutationslauf`, und er wird gerufen und nicht angemeldet.
add_custom_target(mutationslauf
  COMMAND mutationstreiber
          ${FABRIK_VORHABEN_WURZEL}
          ${FABRIK_MUTATION_BAUBAUM}
          ${CMAKE_CURRENT_SOURCE_DIR}/katalog.md
  DEPENDS mutationstreiber
  WORKING_DIRECTORY ${FABRIK_VORHABEN_WURZEL}
  COMMENT "Mutationslauf gegen den Katalog"
  USES_TERMINAL
  VERBATIM)
