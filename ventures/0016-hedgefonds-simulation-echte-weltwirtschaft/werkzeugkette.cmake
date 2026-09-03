# Die Werkzeugkette, festgenagelt.
#
# Das ist die C++-Entsprechung von `rust-toolchain.toml`, das Paket 0004 verlangt.
# Rust nagelt eine Toolchain-Version fest; CMake kann das nicht von sich aus, also
# steht die Bedingung hier ausgeschrieben und bricht den Lauf ab, wenn sie verletzt
# ist. Eingebunden wird die Datei vom Arbeitsbereich (`CMakeLists.txt` daneben) und
# von jedem Mitglied, das allein gebaut wird.
#
# Warum eine Version ueberhaupt festgenagelt wird, obwohl der Kern nur ganzzahlig
# rechnet: Das Ergebnis haengt nicht am Uebersetzer -- Ganzzahlarithmetik mit
# `-fwrapv` ist ueber Versionen hinweg dieselbe Rechnung. Festgenagelt wird die
# *Diagnose*: Warnschalter, `__int128` und die Sanitizer verhalten sich zwischen
# Versionen unterschiedlich, und ein Bauagent ohne Shell sieht nur das Urteil des
# Runners. Ein Urteil, das auf einer anderen Werkzeugkette entstanden ist als die
# naechste Pruefung, ist kein Urteil.

# ADR 0011: C++20, uebersetzt mit g++. Keine Compiler-Erweiterungen im Sprachmodus
# (`-std=c++20`, nicht `gnu++20`) -- derselbe Schalter, den `baulauf.py` fuer blanke
# Quelldateien setzt. `__int128` bleibt trotzdem verfuegbar; es ist eine Erweiterung
# des Typsystems, nicht des Sprachmodus, und `-Wpedantic` ist deshalb aus (begruendet
# beim Warnsatz am Ende dieser Datei).
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FABRIK_UEBERSETZER            "GNU"    CACHE STRING "Der einzige zugelassene Uebersetzer (ADR 0011).")
set(FABRIK_UEBERSETZER_MINDESTENS "12.0"   CACHE STRING "Aeltere g++ koennen C++20 nicht vollstaendig.")
set(FABRIK_UEBERSETZER_GEPRUEFT   "15.2.0" CACHE STRING "Version, gegen die dieses Vorhaben gebaut und geprueft wurde.")

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL FABRIK_UEBERSETZER)
  message(FATAL_ERROR
    "Uebersetzer ist '${CMAKE_CXX_COMPILER_ID}', vorgeschrieben ist '${FABRIK_UEBERSETZER}' (ADR 0011).\n"
    "Ein anderer Uebersetzer ist kein Bauproblem, sondern eine Stackaenderung: Er braucht einen ADR.")
endif()

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS FABRIK_UEBERSETZER_MINDESTENS)
  message(FATAL_ERROR
    "g++ ${CMAKE_CXX_COMPILER_VERSION} ist aelter als ${FABRIK_UEBERSETZER_MINDESTENS} "
    "und beherrscht C++20 nicht vollstaendig.")
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL FABRIK_UEBERSETZER_GEPRUEFT)
  message(WARNING
    "g++ ${CMAKE_CXX_COMPILER_VERSION} statt der geprueften ${FABRIK_UEBERSETZER_GEPRUEFT}. "
    "Die Rechnung aendert das nicht, die Warnungen und die Sanitizer-Meldungen koennen sich "
    "unterscheiden.")
endif()

# ADR 0011, Massnahme 1: `-fwrapv` in JEDEM Profil, nicht nur im Testprofil.
# Damit ist vorzeichenbehafteter Ganzzahlueberlauf als Umbruch im Zweierkomplement
# definiert. Die Gefahr ist nicht der Ueberlauf, sondern was ein Optimierer aus
# seiner angeblichen Unmoeglichkeit folgert.
#
# `baulauf.py` setzt denselben Schalter von aussen. Er steht hier trotzdem: Der
# Runner ist nicht die einzige Stelle, an der dieses Vorhaben uebersetzt wird, und
# ein Determinismusschalter, der nur im Nachtlauf gilt, ist keiner.
set(FABRIK_UEBERLAUF_SCHALTER -fwrapv -fno-fast-math)

# ADR 0011, Massnahme 2: Sanitizer im Testprofil, und der Pruefstand laeuft darueber.
# `-fno-sanitize-recover=all` macht daraus einen Abbruch statt einer Meldung -- sonst
# laeuft ein Test trotz gemeldeter UB gruen durch, und die Massnahme prueft nichts.
option(FABRIK_SANITIZER "Sanitizer im Testprofil (ADR 0011, Massnahme 2)." ON)
set(FABRIK_SANITIZER_SCHALTER -fsanitize=undefined,address -fno-sanitize-recover=all)

# ---------------------------------------------------------------------------
# Der Warnsatz -- fuer jeden Kasten derselbe
# ---------------------------------------------------------------------------
#
# Er stand bis zum 2026-09-02 in `kern/CMakeLists.txt` und, wortgleich abgeschrieben,
# ein zweites Mal im Pruefstand. `set()` ist in CMake verzeichnisgebunden: Was ein
# Verzeichnis setzt, sieht ein Geschwisterverzeichnis nicht, also musste der Satz
# abgeschrieben werden. Bei den sieben Mitgliedern aus T13 stuende er am Ende siebenmal
# da, und die siebte Fassung ist die, die niemand nachfuehrt.
#
# Das ist keine Kosmetik, sondern eine Diagnoseluecke: Ein Kasten, dessen abgeschriebener
# Warnsatz eine Zeile verloren hat, uebersetzt gruen und prueft weniger -- und der
# Uebersetzungsbericht sagt in beiden Faellen `ergebnis: ok`. Genau die Fehlerklasse,
# gegen die `-Werror` hier ueberhaupt gesetzt ist. Hier steht der Satz einmal und reicht
# nach unten durch: beim Bau ueber den Arbeitsbereich ueber `add_subdirectory`, beim
# Alleinbau eines Mitglieds ueber dessen `PROJECT_IS_TOP_LEVEL`-Block, der diese Datei
# vor der ersten Benutzung einbindet.
#
# Die folgende Begruendung ist aus `kern/CMakeLists.txt` unveraendert uebernommen. Punkt 1
# gilt seither fuer jeden Kasten. Punkt 2 und 3 nennen Pfade unter `kern/` und gelten
# weiter nur dort; sie stehen mit hier, weil sie sagen, was der Warnsatz *ersetzt* -- und
# der Ersatz ist nur zu dritt vollstaendig.

# Was in Rust `#![forbid(unsafe_code)]` waere.
#
# C++ kennt kein solches Attribut, und das ist der Preis der Entscheidung aus
# ADR 0011: Speichersicherheit ist hier eine Pruefregel statt einer Spracheigenschaft.
# An ihre Stelle treten drei Dinge, alle mechanisch:
#
#   1. Dieser Warnsatz mit `-Werror`. Was der Uebersetzer als zweifelhaft erkennt,
#      ist damit ein Bauabbruch und keine Zeile, die im Protokoll untergeht.
#   2. `#pragma GCC poison` in `include/kern/sperre.hpp` -- die Gleitkommasperre aus
#      T4 als Uebersetzungsfehler statt als Vorsatz.
#   3. Die Grep-Regel des Pruefers:
#      grep -rnE 'reinterpret_cast|const_cast|\bnew\b|\bdelete\b|\basm\b' kern/
#      -> liefert nichts. Der Kern kommt ohne Zeiger und ohne eigene Speicher-
#      verwaltung aus; feste Groessen und `std::array` statt roher Felder.
#
# `-Wpedantic` steht bewusst NICHT dabei: Es warnt vor `__int128`, und `__int128` ist
# nach ADR 0011 Massnahme 3 verpflichtend fuer jeden Zwischenwert. Ein Warnschalter,
# der eine Vorschrift anmeckert, wuerde entweder abgeschaltet oder ignoriert -- beides
# schlechter, als ihn gar nicht zu setzen.
set(FABRIK_STRENGE
    -Wall -Wextra -Werror
    -Wconversion -Wsign-conversion
    -Wshadow -Wold-style-cast -Wcast-qual -Wuseless-cast
    -Wdouble-promotion -Wfloat-equal
    -Wnon-virtual-dtor -Woverloaded-virtual
    -Wnull-dereference -Wformat=2)

# ---------------------------------------------------------------------------
# Der Riegel: wer den Warnsatz anhaengt, muss diese Datei haben
# ---------------------------------------------------------------------------
#
# Seit der Satz nur noch hier steht, erreicht er ein Mitglied auf zwei Wegen: ueber
# `add_subdirectory` beim Arbeitsbereichsbau, oder ueber den eigenen
# `PROJECT_IS_TOP_LEVEL`-Block beim Alleinbau. Fehlt dieser Block, dann stuende in dem
# Mitglied `target_compile_options(x PRIVATE )` mit null Schaltern -- eine undefinierte
# Variable expandiert in CMake zu einer leeren Liste, nicht zu einem Fehler.
#
# Gemessen am 2026-09-03 an einem Mitglied ohne den Block: `cmake` Code 0,
# `cmake --build` Code 0, `CXX_FLAGS = -std=gnu++20`. Verloren waren nicht nur die 15
# Warnschalter und die zwei Ueberlaufschalter, sondern auch der Sprachmodus -- `gnu++20`
# statt `c++20`, also genau die Compiler-Erweiterungen, die ADR 0011 ausschliesst. Eine
# Uebersetzungseinheit mit ungenutzter Variable ging gruen durch.
#
# Der Umzug hat diese Luecke verschaerft, statt sie zu schaffen: Vorher kostete ein
# vergessener Einbindungsblock auch `enable_testing()`, und dieser Verlust ist **laut**
# ("No tests were found!!!"). Ein Mitglied ohne eigene Proben -- `konsole` und
# `oberflaeche` aus T13 sind Binaerprogramme -- hat den lauten Teil gar nicht.
#
# Deshalb haengt kein Mitglied den Satz mehr selbst an, sondern ruft diese Funktion.
# Warum eine Funktion und nicht ein `if(NOT DEFINED …)`-Riegel in jedem Mitglied: Einen
# Riegel kann das siebte Mitglied genauso vergessen wie die Einbindung, das waere
# derselbe Fehler eine Ebene hoeher. Ein Aufruf dagegen, den CMake nicht kennt, ist ein
# harter Konfigurationsfehler -- `Unknown CMake command`, Code 1, die naechste Zeile
# wird nicht mehr erreicht. Der Fehler faellt damit dorthin, wo er hingehoert: in den
# Konfigurationslauf, statt in einen gruenen Bau, der weniger prueft.
#
# Die Sanitizer bleiben ausdruecklich draussen (ADR 0011, Massnahme 2): Sie haengen nur
# an den `_geprueft`-Zielen und haben eine andere Sichtbarkeit (`PUBLIC` statt
# `PRIVATE`), weil sie an die Proben durchreichen muessen.
function(fabrik_warnsatz_anlegen ziel)
  if(NOT TARGET ${ziel})
    message(FATAL_ERROR
      "fabrik_warnsatz_anlegen('${ziel}'): kein solches Ziel. Der Aufruf gehoert hinter "
      "`add_library`/`add_executable`.")
  endif()

  # Der Aufruf allein reicht nicht: Wird diese Datei aus einem engeren Gueltigkeitsbereich
  # eingebunden als dem, aus dem gerufen wird, ist die Funktion bekannt und der Satz
  # trotzdem leer. Das waere genau die Signatur, gegen die dieses Paket geschrieben ist,
  # nur eine Ebene weiter -- also wird sie hier zum Abbruch statt zum stillen Nichts.
  if(NOT DEFINED FABRIK_STRENGE OR "${FABRIK_STRENGE}" STREQUAL "")
    message(FATAL_ERROR
      "fabrik_warnsatz_anlegen('${ziel}'): `FABRIK_STRENGE` ist hier leer. Ein leerer "
      "Warnsatz uebersetzt gruen und prueft nichts -- das ist kein Bauzustand, sondern "
      "ein Fehler.")
  endif()
  if(NOT DEFINED FABRIK_UEBERLAUF_SCHALTER OR "${FABRIK_UEBERLAUF_SCHALTER}" STREQUAL "")
    message(FATAL_ERROR
      "fabrik_warnsatz_anlegen('${ziel}'): `FABRIK_UEBERLAUF_SCHALTER` ist hier leer. "
      "Ohne `-fwrapv` ist vorzeichenbehafteter Ganzzahlueberlauf undefiniert (ADR 0011, "
      "Massnahme 1), und der Kern rechnet in Festkomma.")
  endif()

  target_compile_options(${ziel} PRIVATE ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})
endfunction()

# ---------------------------------------------------------------------------
# Der Schlussriegel: am Ende zaehlen, an welchem Ziel der Satz fehlt
# ---------------------------------------------------------------------------
#
# Der Riegel eine Ebene weiter oben bindet den **Aufruf**: Wer die Form abschreibt und
# dabei die Einbindung verliert, spricht etwas Unbekanntes aus und bricht ab. Ein
# Mitglied, das die Form nie benutzt, spricht nichts Unbekanntes aus und kommt daran
# vorbei -- es schreibt die kuerzeste `CMakeLists.txt`, die uebersetzt
# (`cmake_minimum_required`, `add_library`, fertig), der Arbeitsbereich nimmt es auf,
# sobald sein Verzeichnis existiert, und der Bericht meldet `ergebnis: ok`.
#
# Gemessen am 2026-09-03 an genau so einem Mitglied, per `add_subdirectory` in einen
# Baum gehaengt, der diese Datei einbindet: `cmake` Code 0, `cmake --build` Code 0.
# Was das Ziel bekommt, haengt daran, wer konfiguriert -- und beide Faelle sind schlecht:
#
#   blank konfiguriert        CXX_FLAGS = -std=c++20
#   unter `baulauf.py`        CXX_FLAGS = -fwrapv -fno-fast-math -O2 -g -DNDEBUG -std=c++20
#
# Den Sprachmodus erbt es, weil `CMAKE_CXX_STANDARD` weiter oben in dieser Datei
# gesetzt wird und Verzeichnisvariablen nach unten durchreichen; die Ueberlaufschalter
# erbt es nur unter dem Runner, weil der sie von aussen an `CMAKE_CXX_FLAGS` haengt.
# Was in **beiden** Faellen fehlt, sind die 15 Warnschalter -- und damit `-Werror`,
# also der ganze Grund, warum der Satz existiert.
#
# Baut derselbe Bauagent sein Mitglied allein, ist der Verlust noch groesser: Ohne den
# `PROJECT_IS_TOP_LEVEL`-Block gilt diese Datei gar nicht, und der Pruefer von Paket
# 0046 hat dort `CXX_FLAGS = -std=gnu++20` gemessen -- auch der Sprachmodus weg, also
# genau die Compiler-Erweiterungen, die ADR 0011 ausschliesst.
#
# Und `konsole` und `oberflaeche` aus T13 haben keine eigenen Proben, es fehlt also
# auch das laute "No tests were found!!!", an dem so etwas sonst auffaellt.
#
# Warum nicht einfach eine dritte Stelle, an der man den Satz anhaengen kann: Das waere
# eine dritte Stelle, die man vergessen kann. Dieser Riegel prueft nicht dort, wo etwas
# getan wird, sondern dort, wo alles getan ist -- er zaehlt am Ende der Konfiguration
# die Ziele und fragt jedes, ob der Satz daran haengt. Durch Nichtstun entzieht sich ihm
# niemand, denn Nichtstun ist genau der Fall, den er faengt.
#
# Seine Grenze gehoert dazu: Ein Mitglied ohne den `PROJECT_IS_TOP_LEVEL`-Block bindet
# diese Datei beim **Alleinbau** nicht ein und fuehrt den Riegel deshalb auch nicht aus.
# Es faellt trotzdem auf, weil `baulauf.py` jedes Manifest **und** den Arbeitsbereich
# baut und der Arbeitsbereich diese Datei immer einbindet -- der Bericht wird rot, nur
# an einer anderen Zeile.
#
# Was der Riegel absichtlich NICHT hat: eine Ausnahmeliste "diese Ziele duerfen ohne".
# Das waere die Tuer, durch die der Fehler zurueckkommt. Wird eine Ausnahme noetig, ist
# das ein ADR und keine Zeile hier.

# Der Sollzustand wird hier festgehalten und nicht erst im Riegel gelesen: Als globale
# Eigenschaft haengt er an der Datei, die ihn setzt, und nicht am Gueltigkeitsbereich,
# in dem der Riegel spaeter laeuft. Wird diese Datei aus einem engeren Bereich
# eingebunden, findet der Riegel den Sollzustand trotzdem -- und faengt dann die Ziele
# darueber, statt selbst leer auszugehen.
set_property(GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_SATZ
             ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})

function(fabrik_schlussriegel wurzelverzeichnis)
  get_property(erwartet GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_SATZ)
  if(NOT erwartet)
    message(FATAL_ERROR
      "fabrik_schlussriegel: der Sollzustand ist leer. Ein Riegel ohne Sollzustand "
      "winkt jedes Ziel durch und baut gruen -- das ist schlimmer als kein Riegel.")
  endif()

  # Nicht jedes Ziel uebersetzt Quelldateien. `INTERFACE_LIBRARY` kann `PRIVATE`
  # ueberhaupt keine Schalter tragen, `UTILITY` entsteht bei `add_custom_target`,
  # `ALIAS` ist nur ein zweiter Name. Geprueft wird, was einen Uebersetzeraufruf
  # erzeugt; an allem anderen waere ein fehlender Warnsatz kein Befund, sondern die
  # Bauart.
  set(arten STATIC_LIBRARY SHARED_LIBRARY OBJECT_LIBRARY EXECUTABLE)

  # Iterativ statt rekursiv, mit einer Arbeitsliste: Die Ziele stehen je Verzeichnis,
  # und `add_subdirectory` schachtelt beliebig tief. Ohne den Abstieg saehe der Riegel
  # im Arbeitsbereich gar nichts -- dort liegt jedes Ziel eine Ebene tiefer.
  set(offen "${wurzelverzeichnis}")
  set(fehlt "")
  set(gezaehlt 0)
  while(offen)
    list(POP_FRONT offen verzeichnis)

    get_property(ziele DIRECTORY "${verzeichnis}" PROPERTY BUILDSYSTEM_TARGETS)
    foreach(ziel IN LISTS ziele)
      get_target_property(art ${ziel} TYPE)
      if(NOT "${art}" IN_LIST arten)
        continue()
      endif()

      get_target_property(schalter ${ziel} COMPILE_OPTIONS)
      if(NOT schalter)
        set(schalter "")  # `NOTFOUND` ist hier kein Fehler, sondern die leere Menge.
      endif()

      # Geprueft wird der ganze Satz, nicht ein Kennzeichen daraus: Ein Ziel, an dem
      # jemand `-Wall` von Hand anhaengt, hat den Satz nicht -- und ein Riegel, der
      # sich mit einem Schalter zufriedengibt, wuerde genau das durchwinken.
      set(luecke "")
      foreach(schalterwert IN LISTS erwartet)
        if(NOT "${schalterwert}" IN_LIST schalter)
          list(APPEND luecke "${schalterwert}")
        endif()
      endforeach()

      math(EXPR gezaehlt "${gezaehlt} + 1")
      if(luecke)
        list(JOIN luecke " " luecketext)
        # Der Text ist die halbe Massnahme: Ohne Zielnamen und ohne den
        # auszufuehrenden Aufruf sucht der naechste Bauagent an der falschen Stelle.
        list(APPEND fehlt
             "  ${ziel} (${art}) in ${verzeichnis}\n"
             "      es fehlen: ${luecketext}\n"
             "      Abhilfe:   fabrik_warnsatz_anlegen(${ziel})  -- hinter `add_library`/`add_executable`\n")
      endif()
    endforeach()

    get_property(unter DIRECTORY "${verzeichnis}" PROPERTY SUBDIRECTORIES)
    list(APPEND offen ${unter})
  endwhile()

  if(fehlt)
    list(JOIN fehlt "" fehlttext)
    message(FATAL_ERROR
      "Der Warnsatz fehlt an folgenden Zielen -- sie wuerden gruen uebersetzen "
      "und weniger pruefen:\n"
      "${fehlttext}"
      "Jedes uebersetzende Ziel ruft `fabrik_warnsatz_anlegen(<ziel>)` aus "
      "`werkzeugkette.cmake`; die Datei bindet ein Mitglied beim Alleinbau in seinem "
      "`PROJECT_IS_TOP_LEVEL`-Block ein.\n"
      "Ohne den Satz uebersetzt das Ziel gruen und ohne `-Werror`. Blank konfiguriert "
      "fehlt ihm zusaetzlich `-fwrapv` (ADR 0011, Massnahme 1); allein gebaut ohne den "
      "`PROJECT_IS_TOP_LEVEL`-Block auch der Sprachmodus -- `gnu++20` statt `c++20`.")
  endif()

  # Die Zahl steht da, damit der Uebersetzungsbericht den Unterschied zwischen "der
  # Riegel hat geprueft" und "der Riegel hat nichts gefunden, weil er nichts gesehen
  # hat" traegt. Ein Riegel, der versehentlich alle Ziele durchwinkt, baut auch gruen.
  message(STATUS "Warnsatz-Schlussriegel: ${gezaehlt} uebersetzende Ziele geprueft, alle mit Warnsatz.")
endfunction()

# Ans Ende der Konfiguration gehaengt, nicht an diese Stelle: Hier ist noch kein
# einziges Ziel angelegt. `DEFER` laeuft, wenn das Verzeichnis fertig ist -- beim
# obersten Verzeichnis also nach allen `add_subdirectory`.
#
# Gestellt wird er genau einmal, auch wenn diese Datei mehrfach eingebunden wird (der
# Arbeitsbereich tut es, und ein allein gebautes Mitglied tut es ebenfalls). Ein
# zweiter Riegel faende dasselbe und meldete es doppelt.
get_property(fabrik_riegel_steht GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_GESTELLT)
if(NOT fabrik_riegel_steht)
  set_property(GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_GESTELLT ON)
  cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}"
                 CALL fabrik_schlussriegel "${CMAKE_SOURCE_DIR}")
endif()
unset(fabrik_riegel_steht)
