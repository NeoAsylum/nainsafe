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
# des Typsystems, nicht des Sprachmodus, und `-Wpedantic` ist deshalb aus (siehe
# `kern/CMakeLists.txt`).
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
