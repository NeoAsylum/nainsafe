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

# Ein Pauschalabschalter erreicht den Uebersetzer auf mehr Wegen als dem einen, den
# dieser Riegel bis zum 2026-09-04 gelesen hat. `COMPILE_OPTIONS` des Ziels ist **eine**
# der Eigenschaften, aus denen CMake die Uebersetzerzeile zusammensetzt. Drei weitere
# gemessen am 2026-09-04 an derselben Wegwerf-Quelle wie unten (`int f(double d){ int i =
# d; return i; }`; ohne Abschalter bricht der Bau mit `[-Werror=float-conversion]` ab):
#
#   set_target_properties(z PROPERTIES COMPILE_FLAGS "-w")
#       Riegel Code 0, Bau Code 0, 0 Diagnosen
#       CXX_FLAGS = -std=c++20 -w -Wall -Wextra -Werror ...
#   set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")
#       Riegel Code 0, Bau Code 0, 0 Diagnosen
#       # Custom flags: CMakeFiles/z.dir/z.cpp.o_FLAGS = -w
#   add_library(iface INTERFACE); target_compile_options(iface INTERFACE -w);
#   target_link_libraries(z PRIVATE iface)
#       Riegel Code 0, Bau Code 0, 0 Diagnosen
#       CXX_FLAGS = ... -fwrapv -fno-fast-math -w
#
# In allen drei Faellen meldete der Riegel wortgleich Vollzug. Das ist dieselbe
# Fehlerklasse wie beim Eintrag, der kein Schalter ist, nur eine Ebene weiter: Die
# Eigenschaft ist nicht die Schalterzeile.
#
# Gesammelt wird deshalb **jeder Eintrag mit seiner Herkunft** -- zwei Listen im
# Gleichschritt, weil eine CMake-Liste flach ist und kein Paar traegt. Die Herkunft ist
# keine Zugabe zur Meldung: Wer `-w` sucht und nur den Zielnamen bekommt, sucht im
# falschen Manifest, wenn der Schalter an einer einzelnen Quelldatei oder in der
# Schnittstelle eines gelinkten Ziels haengt.
#
# Ein Makro und keine Funktion, weil es in den Gueltigkeitsbereich des Riegels schreiben
# muss. Eine Funktion bekaeme eigene Kopien von `eintraege` und `herkuenfte`, und der
# Riegel saehe am Ende eine leere Liste -- also gruen, immer.
macro(fabrik_riegel_sammeln herkunft listenname)
  # Nicht `if(${listenname})`: Eine Eigenschaft mit dem Wert `0` waere damit still
  # verschwunden. Geprueft wird auf genau die zwei Faelle, die "nichts da" heissen --
  # die leere Zeichenkette und das `-NOTFOUND`, das `get_*_property` fuer eine ungesetzte
  # Eigenschaft liefert.
  if(NOT "${${listenname}}" STREQUAL "" AND NOT "${${listenname}}" MATCHES "-NOTFOUND$")
    foreach(fabrik_eintrag IN LISTS ${listenname})
      list(APPEND eintraege "${fabrik_eintrag}")
      list(APPEND herkuenfte "${herkunft}")
    endforeach()
  endif()
endmacro()

# Der Sollzustand wird hier festgehalten und nicht erst im Riegel gelesen: Als globale
# Eigenschaft haengt er an der Datei, die ihn setzt, und nicht am Gueltigkeitsbereich,
# in dem der Riegel spaeter laeuft. Wird diese Datei aus einem engeren Bereich
# eingebunden, findet der Riegel den Sollzustand trotzdem -- und faengt dann die Ziele
# darueber, statt selbst leer auszugehen.
set_property(GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_SATZ
             ${FABRIK_STRENGE} ${FABRIK_UEBERLAUF_SCHALTER})

# ---------------------------------------------------------------------------
# Die Nullabhaengigkeit aus T2 -- an der Eigenschaft gelesen, nicht am Dateitext
# ---------------------------------------------------------------------------
#
# T2 verlangt vom Kern null Fremdabhaengigkeiten und nennt als mechanischen Nachweis
# drei Mustervergleiche. Zwei laufen ueber das Manifest des Kerns und stehen in der
# Abnahme von Paket 0004. Der dritte sollte ueber alle uebrigen Manifeste laufen und
# dort zwei Schreibweisen suchen -- er stand bis zum 2026-09-04 in keinem Riegel und
# war damit eine Regel, die niemand ausfuehrt.
#
# Er wird hier nicht nachgetragen, sondern ersetzt, und dafuer gibt es zwei Gruende.
#
# Der erste ist gemessen: Wer ihn woertlich ausschreibt, baut einen Vergleich, der nie
# leer ausgehen kann. Seine Nadel fuer die Verzeichnisform steckt als Teilzeichenkette
# in der Zielform, und beide Probenschleifen -- die im Kern und die im Pruefstand --
# benutzen die Zielform erlaubterweise. Ein Vergleich mit bekannten Blindtreffern ist
# kein Ablesen mehr, sondern ein Durchsehen, und der echte Treffer stuende dann zwischen
# denen, die man gewohnt ist zu ueberspringen.
#
# Der zweite ist der wichtigere: Ein Mustervergleich ueber Dateitext raet, welche
# Schreibweise jemand benutzt hat. Die Zieleigenschaft nennt das Ergebnis. Gemessen am
# 2026-09-04 an einem Wegwerfbaum, dessen oberstes Verzeichnis die Verzeichnisform vor
# dem Abstieg ausspricht und dessen Ziel eine Ebene tiefer entsteht:
#
#   LINK_LIBRARIES           des Ziels = [fremd]
#   INTERFACE_LINK_LIBRARIES des Ziels = [fremd]
#
# Die Verzeichnisanweisung landet also in der **Ziel**eigenschaft. Ein Riegel, der sie
# liest, sieht beide Angriffsformen aus der Pruefung von Paket 0011 -- die aus einem
# fremden Verzeichnis, seit CMake 3.13 erlaubt und ohne eine Zeile im Manifest des
# Kerns, und die eine Ebene hoeher. Und er sieht Schreibweisen, die es heute noch nicht
# gibt, denn er fragt nicht nach der Anweisung, sondern nach ihrer Wirkung.
#
# Leer ist dabei der Sollzustand, nicht "nichts Fremdes". Die Standardbibliothek steht
# in keiner dieser Eigenschaften -- sie kommt mit dem Uebersetzer, den diese Datei
# festnagelt, und der Uebersetzungstreiber haengt sie von sich aus an. Eine
# Ausnahmeliste "diese Bibliothek darf" gibt es deshalb nicht; sie waere die Tuer, durch
# die die erste Fremdabhaengigkeit hereinkaeme, und sie waere zugleich unnoetig.
#
# Die Namen stehen in einer benannten Liste und nicht verstreut in der Bedingung: Wer
# den Kern umbenennt oder ihn teilt, hat dann eine Stelle zu aendern -- und der Riegel
# unten haelt ihn dazu an, statt still leer auszugehen.
set(FABRIK_NULLABHAENGIG kern kern_geprueft)
set_property(GLOBAL PROPERTY FABRIK_NULLABHAENGIGE_ZIELE ${FABRIK_NULLABHAENGIG})

function(fabrik_schlussriegel wurzelverzeichnis)
  get_property(erwartet GLOBAL PROPERTY FABRIK_SCHLUSSRIEGEL_SATZ)
  if(NOT erwartet)
    message(FATAL_ERROR
      "fabrik_schlussriegel: der Sollzustand ist leer. Ein Riegel ohne Sollzustand "
      "winkt jedes Ziel durch und baut gruen -- das ist schlimmer als kein Riegel.")
  endif()

  # Nicht jedes Ziel uebersetzt Quelldateien. `UTILITY` entsteht bei
  # `add_custom_target`, `ALIAS` ist nur ein zweiter Name. **Den Warnsatz** verlangt
  # dieser Riegel nur von den Arten hier; an allem anderen waere sein Fehlen kein
  # Befund, sondern die Bauart.
  #
  # `INTERFACE_LIBRARY` steht bewusst nicht in der Liste und wird trotzdem angesehen --
  # der Unterschied steht unten an der Verzweigung. Es kann `PRIVATE` ueberhaupt keine
  # Schalter tragen, ihm den Satz abzuverlangen machte jedes Schnittstellenziel unbaubar;
  # sein `INTERFACE_COMPILE_OPTIONS` erreicht aber jeden, der es linkt. Anwesenheit und
  # Abwesenheit brauchen hier verschiedene Schaerfe.
  #
  # `MODULE_LIBRARY` steht seit dem 2026-09-04 mit dabei und fehlte vorher. Es
  # uebersetzt Quelldateien wie die anderen vier, kam aber vollstaendig vorbei --
  # gemessen an einem Baum mit genau einem solchen Ziel und ohne Warnsatz: Der Riegel
  # meldete `0 uebersetzende Ziele geprueft` und Code 0, das Ziel bekam
  # `CXX_FLAGS = -std=c++20 -fPIC`, also keinen Warnschalter, kein `-Werror` und blank
  # konfiguriert auch kein `-fwrapv`. Dieselbe Fehlerklasse, gegen die dieser Riegel
  # geschrieben ist, nur eine Zielart weiter.
  set(arten STATIC_LIBRARY SHARED_LIBRARY MODULE_LIBRARY OBJECT_LIBRARY EXECUTABLE)

  # Die Sperrliste gegen Pauschalabschalter, als benannte Groesse statt verstreut in
  # der Bedingung weiter unten. Sie ist **keine** Ausnahmeliste im Sinne des Absatzes
  # ueber dieser Funktion: Sie erlaubt nichts, sie verbietet zusaetzlich.
  #
  # Muster statt fester Werte, weil `-Wno-error` mit und ohne angehaengte Warnklasse
  # vorkommt. `^-w$` trifft nur den Schalter selbst, nicht die vielen anderen, die mit
  # `-w` beginnen.
  set(pauschalmuster "^-w$" "^-Wno-error(=.+)?$")

  # Iterativ statt rekursiv, mit einer Arbeitsliste: Die Ziele stehen je Verzeichnis,
  # und `add_subdirectory` schachtelt beliebig tief. Ohne den Abstieg saehe der Riegel
  # im Arbeitsbereich gar nichts -- dort liegt jedes Ziel eine Ebene tiefer.
  set(offen "${wurzelverzeichnis}")
  set(fehlt "")
  set(abgeschaltet "")
  set(gezaehlt 0)
  set(schnittstellen 0)
  while(offen)
    list(POP_FRONT offen verzeichnis)

    get_property(ziele DIRECTORY "${verzeichnis}" PROPERTY BUILDSYSTEM_TARGETS)
    foreach(ziel IN LISTS ziele)
      get_target_property(art ${ziel} TYPE)
      set(uebersetzt TRUE)
      if(NOT "${art}" IN_LIST arten)
        # Der dritte gemessene Fall kam genau hier vorbei: Das `-w` stand an einem
        # `INTERFACE_LIBRARY`, und das bog an dieser Zeile ab. Es bleibt vom Warnsatz
        # befreit -- `uebersetzt` ist fuer es falsch --, aber seine Schnittstelle wird
        # gelesen. Zum Vergleich gemessen: Haengt dasselbe `-w` per
        # `target_compile_options(lib PUBLIC -w)` an einer `STATIC`-Bibliothek, wurde
        # `lib` schon vorher gefangen. Der Weg entzog sich allein ueber die Zielart.
        if(NOT "${art}" STREQUAL "INTERFACE_LIBRARY")
          continue()
        endif()
        set(uebersetzt FALSE)
      endif()

      get_target_property(schalter ${ziel} COMPILE_OPTIONS)
      if(NOT schalter)
        set(schalter "")  # `NOTFOUND` ist hier kein Fehler, sondern die leere Menge.
      endif()

      # Geprueft wird der ganze Satz, nicht ein Kennzeichen daraus: Ein Ziel, an dem
      # jemand `-Wall` von Hand anhaengt, hat den Satz nicht -- und ein Riegel, der
      # sich mit einem Schalter zufriedengibt, wuerde genau das durchwinken.
      #
      # Nur fuer uebersetzende Ziele, und `COMPILE_FLAGS` bleibt hier absichtlich
      # draussen: Der Satz wird von `fabrik_warnsatz_anlegen` in `COMPILE_OPTIONS`
      # gelegt und nirgendwo sonst. Wer diesen Durchgang auf weitere Eigenschaften
      # ausdehnte, erlaubte damit einen zweiten Ort, an dem der Satz stehen darf --
      # also genau die dritte Stelle, die der Absatz ueber dieser Funktion ausschliesst.
      set(luecke "")
      if(uebersetzt)
        foreach(schalterwert IN LISTS erwartet)
          if(NOT "${schalterwert}" IN_LIST schalter)
            list(APPEND luecke "${schalterwert}")
          endif()
        endforeach()
      endif()

      # Zweiter Durchgang, andere Frage: Der Satz kann dastehen und trotzdem nicht
      # wirken. Wer ihn ordentlich anlegt und danach `-Wno-error` oder `-w` anhaengt,
      # hat jeden erwarteten Schalter in `COMPILE_OPTIONS` -- die Luecke oben bleibt
      # leer -- und uebersetzt ohne eine einzige Diagnose. Gemessen am 2026-09-04 an
      # zweimal derselben Quelle mit einer Verengung von `double` auf `int`: mit dem
      # Satz allein Bauabbruch, `[-Werror=float-conversion]` im Wortlaut; mit dem Satz
      # plus `-Wno-error -w` gruener Bau und keine Diagnose. Der Riegel sagte in beiden
      # Faellen wortgleich dasselbe.
      #
      # Der zweite Fall ist der wahrscheinliche: Ein Pauschalabschalter ist der
      # billigste Ausweg aus einer Warnung, die gerade nicht loesbar scheint, und er
      # sieht harmlos aus, **weil** der Riegel danach Vollzug meldet.
      #
      # Einzeln unterdruecken bleibt ausdruecklich erlaubt: `-Wno-conversion` an genau
      # einem Ziel benennt, was nachgesehen wird, und laesst den Rest des Satzes scharf.
      # Ein Pauschalabschalter benennt nichts.

      # Zerlegt wird vor dem Abgleich, weil ein Eintrag nicht dasselbe ist wie ein
      # Schalter. `SHELL:-Wno-error -w` ist CMakes dokumentierter Weg, mehrere Schalter
      # in **einem** Eintrag zu uebergeben, und ein Generatorausdruck -- `$<1:-w>`,
      # `$<$<CONFIG:Release>:-w>` -- traegt den Schalter im Inneren. Der Uebersetzer
      # bekommt in allen drei Faellen `-w`; ein Abgleich gegen die ganze Zeichenkette
      # sieht dagegen einen Eintrag, der auf `S` oder `$` beginnt, findet kein Muster
      # und meldet Vollzug. Gemessen am 2026-09-04 an derselben Quelle wie oben: alle
      # drei kamen am Riegel vorbei und uebersetzten ohne eine einzige Diagnose.
      #
      # Getrennt wird an `SHELL:` und an den Zeichen `$ < > : ,`. Das Ergebnis dient
      # allein dem Abgleich und wird nie weitergereicht -- was die Zerlegung an einem
      # ungewoehnlichen Eintrag zerschlaegt, kostet hoechstens einen Fehlalarm, und der
      # waere laut statt still. Die Schalter, die hier wirklich vorkommen, erzeugen
      # keinen: weder `-Wall` noch `-Wno-conversion` noch `-fsanitize=undefined,address`
      # noch `-fno-sanitize-recover=all` liefert ein Wort, das `^-w$` oder
      # `^-Wno-error(=.+)?$` trifft.
      #
      # Der erste Durchgang bleibt absichtlich beim ganzen Eintrag. Er prueft
      # **Anwesenheit**, und dort zeigt dieselbe Zerlegung in die andere Richtung: Wer
      # den Satz je in einem `SHELL:`-Eintrag anlegt, wird vom ersten Durchgang
      # vermisst und bricht ab. Das ist die harmlose Haelfte des Fehlers -- hier geht
      # es um Abwesenheit, und die schweigt von selbst.

      # Eingesammelt wird, was der Uebersetzer wirklich bekommt, und nicht die eine
      # Eigenschaft, die am naechsten liegt: `COMPILE_OPTIONS` und `COMPILE_FLAGS` des
      # Ziels, dieselben beiden an jeder seiner Quelldateien, dazu
      # `INTERFACE_COMPILE_OPTIONS`. Fuenf statt einer -- die drei gemessenen Umgehungen
      # stehen im Absatz vor `fabrik_riegel_sammeln`. Jeder Eintrag kommt mit seiner
      # Herkunft, damit die Meldung unten nicht nur den Schalter nennt, sondern die
      # Zeile, die umzuschreiben ist.
      set(eintraege "")
      set(herkuenfte "")
      if(uebersetzt)
        fabrik_riegel_sammeln("COMPILE_OPTIONS an ${ziel}" schalter)
        get_target_property(zielflags ${ziel} COMPILE_FLAGS)
        fabrik_riegel_sammeln("COMPILE_FLAGS an ${ziel}" zielflags)

        get_target_property(quellverzeichnis ${ziel} SOURCE_DIR)
        get_target_property(quellen ${ziel} SOURCES)
        if(NOT quellen)
          set(quellen "")  # wie oben: `NOTFOUND` ist die leere Menge, kein Dateiname.
        endif()
        foreach(quelle IN LISTS quellen)
          # Ein Generatorausdruck in `SOURCES` -- `$<TARGET_OBJECTS:x>` -- ist kein
          # Dateiname, den man nach Eigenschaften fragen kann. Uebergangen statt geraten;
          # was drinsteckt, wird an seinem eigenen Ziel gefangen.
          if("${quelle}" MATCHES "[$]<")
            continue()
          endif()
          if(NOT IS_ABSOLUTE "${quelle}")
            set(quelle "${quellverzeichnis}/${quelle}")
          endif()
          # `TARGET_DIRECTORY` ist Pflicht und keine Feinheit: Eigenschaften von
          # Quelldateien sind verzeichnisgebunden, und dieser Riegel laeuft per `DEFER`
          # im obersten Verzeichnis. Ohne die Angabe fragte er seinen eigenen Bereich,
          # bekaeme fuer jede Datei die leere Menge und meldete gruen -- immer.
          get_source_file_property(quellopt "${quelle}"
                                   TARGET_DIRECTORY ${ziel} COMPILE_OPTIONS)
          fabrik_riegel_sammeln("COMPILE_OPTIONS an ${quelle}" quellopt)
          get_source_file_property(quellflags "${quelle}"
                                   TARGET_DIRECTORY ${ziel} COMPILE_FLAGS)
          fabrik_riegel_sammeln("COMPILE_FLAGS an ${quelle}" quellflags)
        endforeach()
      endif()

      # Die Schnittstelle gilt fuer beide Zielarten. Gefangen wird der Schalter hier, an
      # dem Ziel, an dem er geschrieben steht -- nicht bei seinen Verbrauchern. Sonst
      # meldete derselbe Verstoss so oft, wie ihn jemand linkt, und die Zahl der Befunde
      # saegte an der Stelle, an der niemand etwas geschrieben hat.
      get_target_property(schnittstellenschalter ${ziel} INTERFACE_COMPILE_OPTIONS)
      fabrik_riegel_sammeln("INTERFACE_COMPILE_OPTIONS an ${ziel}" schnittstellenschalter)

      set(pauschal "")
      set(pauschalquelle "")
      # Ueber den Index statt mit `foreach`, weil zu jedem Eintrag seine Herkunft
      # gehoert und CMake keine Paare kennt. Beide Listen wachsen nur in
      # `fabrik_riegel_sammeln` und dort im Gleichschritt.
      list(LENGTH eintraege eintragszahl)
      set(lfd 0)
      while(lfd LESS eintragszahl)
        list(GET eintraege ${lfd} schalterwert)
        list(GET herkuenfte ${lfd} herkunft)
        math(EXPR lfd "${lfd} + 1")
        string(REPLACE "SHELL:" " " zerlegt "${schalterwert}")
        string(REGEX REPLACE "[$<>:,]" " " zerlegt "${zerlegt}")
        separate_arguments(worte UNIX_COMMAND "${zerlegt}")
        foreach(wort IN LISTS worte)
          foreach(muster IN LISTS pauschalmuster)
            if("${wort}" MATCHES "${muster}")
              list(APPEND pauschal "${wort}")
              list(APPEND pauschalquelle "${herkunft}:  ${schalterwert}")
            endif()
          endforeach()
        endforeach()
      endwhile()

      # Zwei Zaehler, weil zwei verschiedene Dinge gezaehlt werden. Ein
      # Schnittstellenziel unter die "uebersetzenden Ziele" zu mischen machte den Satz
      # daneben unwahr und die Zahl unvergleichbar mit jeder frueheren Messung.
      if(uebersetzt)
        math(EXPR gezaehlt "${gezaehlt} + 1")
      else()
        math(EXPR schnittstellen "${schnittstellen} + 1")
      endif()
      if(pauschal)
        list(REMOVE_DUPLICATES pauschal)
        list(REMOVE_DUPLICATES pauschalquelle)
        list(JOIN pauschal " " pauschaltext)
        list(APPEND abgeschaltet
             "  ${ziel} (${art}) in ${verzeichnis}\n"
             "      hebt den Satz wieder auf: ${pauschaltext}\n")
        # Je Fundstelle eine Zeile, und jede nennt zuerst die Eigenschaft. Zwei Gruende,
        # beide gemessen: Seit die Zerlegung Woerter meldet, ist der genannte Schalter
        # nicht mehr notwendig die Zeile im Manifest -- wer `-w` sucht, findet
        # `$<$<CONFIG:Release>:-w>` nicht. Und seit hier fuenf Eigenschaften einlaufen,
        # ist auch der Zielname nicht mehr der Ort: `-w` an einer einzelnen Quelldatei
        # oder in der Schnittstelle eines gelinkten Ziels steht in einer anderen Zeile
        # als `add_library(${ziel} ...)`.
        foreach(fundstelle IN LISTS pauschalquelle)
          list(APPEND abgeschaltet
               "      gefunden in:              ${fundstelle}\n")
        endforeach()
      endif()
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

  if(abgeschaltet)
    list(JOIN abgeschaltet "" abgeschaltettext)
    message(FATAL_ERROR
      "Diese Ziele heben den Warnsatz mit einem Pauschalabschalter wieder auf:\n"
      "${abgeschaltettext}"
      "`-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus. Das "
      "Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder erwartete "
      "Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine Pruefung weiter "
      "oben sieht deshalb nichts.\n"
      "Die Zeile `gefunden in` nennt die Eigenschaft und nicht nur das Ziel, denn der "
      "Abschalter muss dort gar nicht stehen: Er kann an einer einzelnen Quelldatei "
      "haengen (`set_source_files_properties`), in der aelteren Form `COMPILE_FLAGS` "
      "oder in `INTERFACE_COMPILE_OPTIONS` eines Ziels, das hier gelinkt wird. Ein "
      "`INTERFACE_LIBRARY` steht deshalb auch dann in dieser Liste, wenn es selbst "
      "nichts uebersetzt -- gefangen wird der Schalter, wo er geschrieben steht, und "
      "nicht bei jedem, der ihn erbt.\n"
      "Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und "
      "benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz "
      "daneben, warum. Das bleibt zugelassen. Pauschal abgeschaltet wird nichts.")
  endif()

  # ---------------------------------------------------------------------
  # Zweiter Gegenstand desselben Riegels: die Nullabhaengigkeit aus T2
  # ---------------------------------------------------------------------
  #
  # Nicht in der Schleife oben, sondern daneben, und der Grund ist der Zuschnitt: Die
  # Schleife fragt jedes Ziel des Baumes nach dem Warnsatz und braucht dafuer den
  # Abstieg ueber die Verzeichnisse. Hier geht es um eine Handvoll benannter Ziele,
  # und die Frage nach einem Ziel dieses Namens ist global statt verzeichnisgebunden.
  # Ein zweiter Durchlauf durch den Baum brauchte es dafuer nicht -- und ein Riegel,
  # der auf den Abstieg angewiesen waere, ginge leer aus, sobald das Ziel woanders
  # entsteht als dort, wo man es sucht. Genau das ist die Luecke, die hier zu
  # schliessen ist.
  get_property(nullabhaengig GLOBAL PROPERTY FABRIK_NULLABHAENGIGE_ZIELE)
  if(NOT nullabhaengig)
    message(FATAL_ERROR
      "fabrik_schlussriegel: die Liste der nullabhaengigen Ziele ist leer. Dasselbe "
      "gilt wie fuer den Sollzustand oben -- ein Riegel ohne Gegenstand winkt jedes "
      "Ziel durch und baut gruen.")
  endif()

  set(fremdlink "")
  set(nullgelesen "")
  set(nullziele "")
  foreach(nullziel IN LISTS nullabhaengig)
    if(NOT TARGET ${nullziel})
      continue()
    endif()
    list(APPEND nullziele "${nullziel}")

    # Zwei Eigenschaften und nicht eine: Dieselbe Anweisung legt ihre Angabe je nach
    # Sichtbarkeit an verschiedenen Stellen ab -- privat nur in der ersten, als
    # Schnittstelle nur in der zweiten, oeffentlich in beiden. Wer nur die erste liest,
    # uebersieht die dritte Form vollstaendig. Das ist die Lehre aus Paket 0066 auf der
    # Linkseite: Die Frage ist nicht, welche Eigenschaft am naechsten liegt, sondern aus
    # wie vielen das Werkzeug zusammensetzt, was geprueft werden soll.
    foreach(eigenschaft LINK_LIBRARIES INTERFACE_LINK_LIBRARIES)
      get_target_property(nullwert ${nullziel} ${eigenschaft})
      # Wie beim Sammeln oben: `-NOTFOUND` heisst ungesetzt und ist die leere Menge,
      # nicht der Name einer Bibliothek.
      if("${nullwert}" MATCHES "-NOTFOUND$")
        set(nullwert "")
      endif()
      list(APPEND nullgelesen "${nullziel}.${eigenschaft}=[${nullwert}]")
      foreach(eintrag IN LISTS nullwert)
        list(APPEND fremdlink "  ${nullziel}: ${eigenschaft} nennt ${eintrag}\n")
      endforeach()
    endforeach()

    # Die dritte Stelle, an der eine Bibliothek an den Kern kommt, ohne in den beiden
    # oben aufzutauchen: die Linkerzeile. Fuer CMake ist ein `-l`-Schalter dort keine
    # Abhaengigkeit, sondern ein Wort; der Uebersetzungstreiber macht trotzdem eine
    # daraus. Geprueft wird deshalb nicht auf Anwesenheit, sondern auf die Form -- ein
    # Wort, das mit `-l` beginnt, oder eines, das auf eine Bibliotheksendung endet.
    #
    # Die Schalter, die hier heute wirklich stehen, sind die beiden Sanitizerschalter am
    # geprueften Kern. Beide beginnen mit `-f` und enden auf ein Wort ohne Punkt, treffen
    # also keines der zwei Muster. Der Nachweis dafuer ist die Zeile in der Meldung
    # unten: Sie nennt den gelesenen Wert und nicht nur das Urteil.
    foreach(eigenschaft LINK_OPTIONS INTERFACE_LINK_OPTIONS)
      get_target_property(nullwert ${nullziel} ${eigenschaft})
      if("${nullwert}" MATCHES "-NOTFOUND$")
        set(nullwert "")
      endif()
      list(APPEND nullgelesen "${nullziel}.${eigenschaft}=[${nullwert}]")
      foreach(eintrag IN LISTS nullwert)
        if("${eintrag}" MATCHES "^-l." OR "${eintrag}" MATCHES "\\.(a|so)$")
          list(APPEND fremdlink "  ${nullziel}: ${eigenschaft} nennt ${eintrag}\n")
        endif()
      endforeach()
    endforeach()
  endforeach()

  # Der Riegel darf nicht deshalb gruen sein, weil er sein Ziel nicht gefunden hat. Wird
  # der Kern umbenannt oder aufgeteilt, meldet ein Riegel ueber eine Namensliste, die
  # niemand nachgefuehrt hat, genau dasselbe wie einer ueber einen sauberen Baum.
  #
  # Gebunden wird das an eine Datei statt an eine Zusage: Liegt unter der Wurzel ein
  # Kernverzeichnis mit eigenem Manifest, muss danach auch ein Ziel dieses Namens
  # dastehen. Beim Alleinbau des Kerns ist die Wurzel das Kernverzeichnis selbst, die
  # Bedingung trifft also nicht -- dort steht das Ziel ohnehin, und die Zahl unten sagt
  # es.
  #
  # Der gepruefte Kern bekommt bewusst keine solche Bindung: Er entsteht nur unter
  # `FABRIK_SANITIZER`, und ein Riegel, der ihn unbedingt verlangte, machte jeden Bau
  # ohne Sanitizer unmoeglich -- er waere zu scharf und damit ein Befund gegen sich
  # selbst. Seine An- oder Abwesenheit steht statt dessen in der Meldung, wo sie
  # auffaellt, wenn sie sich aendert.
  if(EXISTS "${wurzelverzeichnis}/kern/CMakeLists.txt" AND NOT TARGET kern)
    message(FATAL_ERROR
      "fabrik_schlussriegel: unter '${wurzelverzeichnis}' liegt ein Kernmanifest, aber "
      "es gibt kein Ziel dieses Namens. Der Nullabhaengigkeitsriegel haette nichts "
      "gelesen und trotzdem gruen gemeldet -- das ist kein gruener Bau, sondern ein "
      "Riegel ohne Gegenstand.\n"
      "Wurde das Ziel umbenannt oder geteilt, gehoert der neue Name in "
      "`FABRIK_NULLABHAENGIG` in dieser Datei, und zwar in derselben Aenderung.")
  endif()

  if(fremdlink)
    list(JOIN fremdlink "" fremdlinktext)
    message(FATAL_ERROR
      "T2 verlangt vom Kern null Fremdabhaengigkeiten. Diese Ziele linken etwas:\n"
      "${fremdlinktext}"
      "Gelesen wurde die Eigenschaft des Ziels und nicht der Text eines Manifests, und "
      "das ist der Kern der Sache: Eine Abhaengigkeit muss im Manifest des Kerns gar "
      "nicht stehen, um an ihm zu haengen. Sie kann eine Ebene hoeher als "
      "Verzeichnisanweisung stehen und auf jedes danach angelegte Ziel durchschlagen, "
      "und sie darf seit CMake 3.13 aus einem beliebigen anderen Verzeichnis an den "
      "Kern gehaengt werden. In beiden Faellen bleibt sein eigenes Manifest unberuehrt "
      "und ein Mustervergleich darueber leer.\n"
      "Der Sollzustand ist die leere Eigenschaft. Die Standardbibliothek steht in keiner "
      "von ihnen -- sie kommt mit dem Uebersetzer, den diese Datei festnagelt.\n"
      "Braucht der Kern wirklich eine Abhaengigkeit, ist das eine Aenderung an T2 und "
      "damit ein ADR, keine Zeile hier.")
  endif()

  # Die Meldung nennt die Eigenschaft und ihren Wert, nicht "keine Auffaelligkeiten".
  # Zwei Gruende, beide aus frueheren Riegeln dieser Datei: Eine Zahl, die von zwei auf
  # eins faellt, faellt auf; ein Urteil ohne Messwert tut das nicht. Und ein Riegel, der
  # nur sein Ergebnis meldet, laesst sich nicht mehr von einem unterscheiden, der seinen
  # Gegenstand verloren hat.
  if(nullziele)
    list(LENGTH nullziele nullzahl)
    list(JOIN nullgelesen "; " nullgelesentext)
    message(STATUS
      "Nullabhaengigkeitsriegel (T2): ${nullzahl} Ziel(e) gelesen -- ${nullgelesentext}")
  else()
    message(STATUS
      "Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG "
      "(${nullabhaengig}) liegt in diesem Baum -- nichts gelesen.")
  endif()

  # Ein Riegel, der nichts gesehen hat, hat nichts geprueft. Bis zum 2026-09-04 meldete
  # er in dem Fall `0 uebersetzende Ziele geprueft, alle mit Warnsatz` und endete mit
  # Code 0: Die Zahl trug den Unterschied, der Satz daneben behauptete das Gegenteil,
  # und im Uebersetzungsbericht steht die leere Zeile an derselben Stelle wie die
  # gruene. An keinem heutigen Bauweg laeuft er leer; er tut es an dem Tag, an dem eine
  # Umbenennung, ein verschobener `include` oder ein `DEFER`, das nicht mehr greift,
  # ihm den Baum entzieht -- also genau dann, wenn niemand hinsieht.
  #
  # Die Grenze gehoert dazu: Er darf nur greifen, wo ueberhaupt ein Ziel erwartet wird.
  # Ein reines Datenverzeichnis ohne `add_library` waere ein Fehlalarm. Heute bindet nur
  # ein Baum mit Zielen diese Datei ein; wird das je anders, gehoert die Ausnahme
  # begruendet und nicht stillschweigend eingebaut.
  #
  # Gezaehlt wird hier allein `gezaehlt`, nicht `schnittstellen`: Ein Baum aus lauter
  # Schnittstellenzielen uebersetzt keine einzige Zeile, und ein Riegel, den ein solcher
  # Baum saettigt, waere wieder einer ohne Gegenstand.
  if(gezaehlt EQUAL 0)
    message(FATAL_ERROR
      "fabrik_schlussriegel: kein einziges uebersetzendes Ziel unter "
      "'${wurzelverzeichnis}' gesehen. Der Riegel hat damit nichts geprueft -- das ist "
      "kein gruener Bau, sondern ein Riegel ohne Gegenstand.\n"
      "Naheliegende Ursachen: Der Baum legt gar kein uebersetzendes Ziel an; das `DEFER` "
      "haengt an einem anderen Verzeichnis als dem, unter dem die Ziele stehen; oder "
      "diese Datei wird aus einem Bereich eingebunden, unter dem nichts liegt.")
  endif()

  # Die Zahl steht da, damit der Uebersetzungsbericht den Unterschied zwischen "der
  # Riegel hat geprueft" und "der Riegel hat nichts gefunden, weil er nichts gesehen
  # hat" traegt. Sie bleibt, obwohl der Nullfall darueber jetzt selbst abbricht: Ein
  # Riegel, der aus einem anderen Grund die Haelfte der Ziele durchwinkt, baut ebenfalls
  # gruen, und eine Zahl, die von 15 auf 3 faellt, faellt genau dort auf.
  #
  # Die zweite Zahl steht getrennt daneben und wird nicht dazugerechnet. Sonst waere die
  # erste nicht mehr mit der von gestern vergleichbar, und genau darauf beruht ihr
  # Nutzen: Am 2026-09-04 waren es 16 im Arbeitsbereich, 10 im Kern und 5 im Pruefstand;
  # die Differenz von einem traegt `werkzeuge/belegstellen` aus `FABRIK_MITGLIEDER`, das
  # zu keinem der beiden Alleinbauten gehoert.
  message(STATUS
    "Warnsatz-Schlussriegel: ${gezaehlt} uebersetzende Ziele geprueft, "
    "alle mit Warnsatz und ohne Pauschalabschalter; dazu ${schnittstellen} "
    "Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.")
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
