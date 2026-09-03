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
