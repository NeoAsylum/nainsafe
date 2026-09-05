# Der Waechter des Warnsatz-Schlussriegels -- Paket 0133, hierher umgezogen von Paket 0136.
#
# Gebaut wie `werkzeuge/belegstellen` und `werkzeuge/mutation` daneben, und aus demselben
# Grund: Das hier ist ein Riegel ueber den **Baum**, kein Baustein des Erzeugnisses. Es
# haengt an nichts und wird von nichts gelinkt.
#
# **Was der Waechter bewacht.** Der Schlussriegel aus `werkzeugkette.cmake` laeuft bei
# jeder Konfiguration mit und hatte bis zum 2026-09-05 keinen Regressionsnachweis. Der
# Grund steht im Kopf des Skripts unten: Im echten Baum steht nirgends ein
# Pauschalabschalter. Ein Riegel, der nur ueber fehlerfreie Baeume faehrt, kann Fehlalarm
# zeigen und sonst nichts -- seine eigene Stumpfheit sieht er nie. Wer die Pruefung im
# Riegel abschaltet, bekommt einen gruenen Baum und keine Meldung.
#
# `befunde/pruefung-0066/nachbau.py` schliesst diese Luecke: 22 Wegwerf-Baeume unter einer
# eigenen Ablage, jeder mit einem anderen Weg, den Warnsatz auszuhebeln, dazu die
# Positivkontrolle `p_positiv`, die ohne Abschalter rot bauen **muss**.
#
# **Warum der Waechter hier steht und nicht mehr im Pruefstand.** Paket 0133 hat ihn in
# `pruefstand/CMakeLists.txt` eingehaengt, und das war eine Kollisionsentscheidung des
# Projektmanagers, keine Entwurfsentscheidung: Ein eigenes Mitglied braucht einen Eintrag
# in `FABRIK_MITGLIEDER` der `CMakeLists.txt` des Vorhabens, und die hielt am 2026-09-05
# ein anderes offenes Paket. Der Pruefstand ist nach T13 das Gestell fuer Mass 1 bis 3 und
# den Selbstspieler; der Nachbau misst nichts davon, er misst den Baum. Zwei Folgen hatte
# der Fehlplatz, und beide fallen mit dem Umzug weg: Wer den Pruefstand allein baute,
# bezahlte eine Messung mit, die mit ihm nichts zu tun hat, und ein aufgeloester oder
# umgehaengter Pruefstand haette den Waechter mitgenommen.
#
# Das Skript selbst bleibt, wo es liegt (Paket 0133, Vermerk 3: drei Abnahmen nennen den
# Pfad namentlich). Der Umzug betrifft die Bahn, nicht das Skript.
#
# **Der Preis, gemessen statt geschaetzt:** 4,2 Sekunden kalt fuer alle 22 Baeume
# (2026-09-05). Damit liegt der Nachbau auf der billigen Seite der Grenze, die der
# Projektmanager im Rumpf von Paket 0110 gezogen und im Kopf der `CMakeLists.txt` des
# Vorhabens festgehalten hat: Der Belegstellenriegel haengt als `add_test` in `ctest` und
# laeuft bei jeder Abnahme mit, der Mutationslauf ausdruecklich nicht, weil ein einziger
# Fall dort Uebersetzen, Binden und einen Probenlauf kostet.

cmake_minimum_required(VERSION 3.22)

# `LANGUAGES CXX`, obwohl dieser Kasten keine einzige Quelldatei traegt -- und das ist
# gemessen und nicht Gewohnheit. `LANGUAGES NONE` waere die ehrlichere Beschreibung und
# spart die Uebersetzerpruefung, aber `baulauf.py` ruft **jede** Manifestdatei mit
# `-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`. Ein Projekt ohne Sprache benutzt die
# Variable nicht, und CMake schreibt dann in jeden Nachtbericht
# "Manually-specified variables were not used by the project: CMAKE_CXX_FLAGS"
# (gemessen am 2026-09-05, Alleinbau, Code 0 mit Warnung). Der Rueckgabewert bliebe 0 --
# es waere also eine Warnung, die niemanden aufweckt und die jeder kuenftige Leser dieses
# Berichts einmal nachschlagen muss. Mit `CXX` ist der Bericht sauber, und der Preis ist
# ein Uebersetzerlauf von unter einer Sekunde beim Alleinbau.
project(schlussriegel LANGUAGES CXX)

# **Hier fehlt der `include(werkzeugkette.cmake)`, den `werkzeuge/belegstellen` und
# `werkzeuge/mutation` an dieser Stelle tragen -- und zwar mit Absicht.**
#
# Der Schlussriegel in jener Datei bricht seit dem 2026-09-04 ab, wenn er kein einziges
# uebersetzendes Ziel gesehen hat: "kein einziges uebersetzendes Ziel unter '...' gesehen
# ... das ist kein gruener Bau, sondern ein Riegel ohne Gegenstand." Die Regel ist
# richtig, und dieser Kasten ist genau der Fall, den ihr eigener Kommentar vorwegnimmt --
# "Heute bindet nur ein Baum mit Zielen diese Datei ein; wird das je anders, gehoert die
# Ausnahme begruendet und nicht stillschweigend eingebaut." Das ist die Begruendung.
#
# Sie kostet nichts: Die Werkzeugkette wird eingebunden, damit `fabrik_warnsatz_anlegen`
# da ist und der Warnsatz an Zielen haengt -- dieser Kasten hat kein Ziel, an das etwas zu
# haengen waere, und kein `-fwrapv` kann an einer Zeile fehlen, die niemand uebersetzt.
# Was er vom Alleinbau braucht, ist allein `enable_testing()`; ohne das meldete `ctest`
# hier "No tests were found!!!".
#
# Ueber den Arbeitsbereich gebaut ist der Block aus: Dort hat `../../CMakeLists.txt` die
# Werkzeugkette schon eingebunden und `enable_testing()` schon gerufen, und der
# Schlussriegel sieht die uebersetzenden Ziele des ganzen Baums.
if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
endif()

# Die Wurzel kommt von CMake, nicht aus dem Programm -- dieselbe Bauart wie beim
# Belegstellenriegel. Sie zeigt auf das Vorhaben, nicht auf dieses Verzeichnis, und ist
# auf beiden Bauwegen dieselbe: `CMAKE_CURRENT_SOURCE_DIR` ist in beiden Faellen dieses
# Verzeichnis.
get_filename_component(FABRIK_VORHABEN ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)
set(FABRIK_NACHBAU ${FABRIK_VORHABEN}/befunde/pruefung-0066/nachbau.py)

# Kein `if(EXISTS ... ) add_test() endif()`. Genau diese Bauform ist der Fehler, gegen den
# Paket 0133 geschrieben war: Sie laesst den Waechter still verschwinden, sobald jemand
# die Datei verschiebt, und meldet danach eine gruene Abnahme ueber einen Baum ohne
# Waechter. Fehlt die Datei, bricht die Konfiguration ab und sagt, was zu tun ist.
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
# Skripts haengt allein am Stand (`nachbau0066-HEAD`), also am selben Ort fuer jeden Baum
# -- zwei Baeume nacheinander, wie sie jede Gegenprobe fahrt, liefen einander in die
# Ablage. Unter dem Baubaum ist sie je Baum und je Profil eine eigene und verschwindet mit
# ihm. Beide Bauwege legen ihren Baubaum unter einem Ordner namens `bau` an; der steht in
# `.gitignore` (`ventures/**/bau/`) und in `UNGELESENE_ORDNER` des Belegstellenriegels,
# die 22 Wegwerf-Manifeste stoeren dort also niemanden.
#
# Die Zeitgrenze ist keine Schaetzung nach oben, sondern das Vielfache des gemessenen
# Werts: 4,2 Sekunden kalt, 600 Sekunden Grenze. Sie soll nicht knapp sein, sie soll
# verhindern, dass ein haengendes `cmake` den Nachtlauf blockiert.
set_tests_properties(schlussriegel_nachbau PROPERTIES
                     TIMEOUT 600
                     ENVIRONMENT "NACHBAU_ABLAGE=${CMAKE_CURRENT_BINARY_DIR}/nachbau0066")
