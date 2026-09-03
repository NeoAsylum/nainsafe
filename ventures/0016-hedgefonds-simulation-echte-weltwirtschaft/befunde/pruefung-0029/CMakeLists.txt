# Der Mutationsstand zu Paket 0029 -- Werkzeug des `test-pruefer`, kein Teil des Kastens.
#
# **Warum er unter `befunde/` liegt und nirgends sonst.** `agents/baulauf.py:116` sucht
# jede `CMakeLists.txt` unter `ventures/<venture>/` und filtert genau einen
# Verzeichnisnamen heraus: `befunde`. Ein Mutationsstand an jeder anderen Stelle wuerde
# zum weiteren Manifest des offiziellen Uebersetzungsberichts -- am 2026-09-03 ist das
# unter `pruefstand/bau/pruefung-0019/` genau so passiert.
#
# **Was er tut.** Er uebersetzt je Mutant die **unveraenderte** Probe des Pakets gegen
# ein absichtlich kaputtes `vorrat_verfahren.cpp` und erwartet, dass sie rot wird
# (`WILL_FAIL TRUE`). Damit wird aus "ctest gruen" die Aussage:
#
#   Die Kontrollfassung besteht, und **jeder** Mutant wird von der Probe gefangen.
#
# Er fasst keine Datei des Pakets an: `file(READ)` liest, `string(REPLACE)` aendert die
# Kopie im Arbeitsspeicher, `file(WRITE)` legt sie im Bauverzeichnis ab.

cmake_minimum_required(VERSION 3.22)
project(pruefung_0029 LANGUAGES CXX)
enable_testing()

set(PS ${CMAKE_CURRENT_LIST_DIR}/../../pruefstand)
set(VERFAHREN ${PS}/src/vorrat_verfahren.cpp)   # Paket 0029 -- die Datei, die mutiert wird
set(NACHBAR   ${PS}/src/vorrat.cpp)             # Paket 0019 -- unveraendert, liefert die 126 Profile
set(PROBE     ${PS}/test/vorrat_verfahren_probe.cpp)  # Paket 0029 -- unveraendert, das Pruefmittel

file(READ ${VERFAHREN} URSCHRIFT)

# `erwartung` ist `faellt` oder `besteht`. `besteht` gibt es fuer den Kontrolllauf mit
# wirkungsloser Aenderung: Ohne ihn belegte "alle Mutanten sterben" auch, dass schon mein
# Eingriff selbst alles kaputtmacht.
function(mutant name erwartung suchen ersetzen)
  string(REPLACE "${suchen}" "${ersetzen}" MUT "${URSCHRIFT}")
  # Die Fehlerbremse. Ohne sie erzeugt ein Tippfehler im Suchmuster eine unveraenderte
  # Datei, die brav besteht -- und ich zaehlte ihr Bestehen als Empfindlichkeit der Probe.
  if("${MUT}" STREQUAL "${URSCHRIFT}")
    message(FATAL_ERROR "Mutant ${name}: das Suchmuster trifft nichts, die Datei ist unveraendert.")
  endif()
  set(ziel ${CMAKE_CURRENT_BINARY_DIR}/mutanten/${name}.cpp)
  file(WRITE ${ziel} "${MUT}")
  add_executable(${name} ${ziel} ${NACHBAR} ${PROBE})
  target_include_directories(${name} PRIVATE ${PS}/include)
  target_compile_features(${name} PRIVATE cxx_std_20)
  add_test(NAME ${name} COMMAND ${name})
  if(erwartung STREQUAL "faellt")
    set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
  endif()
endfunction()

# --- Die Kontrollfassung: die Urschrift, muss bestehen -------------------------------
add_executable(kontrolle_unveraendert ${VERFAHREN} ${NACHBAR} ${PROBE})
target_include_directories(kontrolle_unveraendert PRIVATE ${PS}/include)
target_compile_features(kontrolle_unveraendert PRIVATE cxx_std_20)
add_test(NAME kontrolle_unveraendert COMMAND kontrolle_unveraendert)

# --- Der Kontrolllauf mit wirkungsloser Aenderung: muss ebenfalls bestehen -----------
mutant(kontrolle_wirkungslos besteht
  "// Schritt 1: der Rundenanfang."
  "// Schritt 1 (Kontrolle, wirkungslos): der Rundenanfang.")

# --- Regel: bei Gleichstand die kleinere Kennung -------------------------------------
mutant(mut01_gleichstand_groessere faellt
  "if (vorrat[i] > vorrat[bester]) {"
  "if (vorrat[i] >= vorrat[bester]) {")

# --- Regel: `vi` wird nie bei null abgeschnitten -------------------------------------
mutant(mut02_vorrat_abgeschnitten faellt
  "abweichung == Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN"
  "true || abweichung == Abweichung::VORRAT_BEI_NULL_ABGESCHNITTEN")

# --- Regel: der Rundenanfang trifft **alle fuenf** Arten, auch die unzulaessigen -----
mutant(mut03_zuwachs_nur_zulaessig faellt
  "vorrat[i] += ZUWACHS * anteile[i];"
  "if (zulaessig[i]) vorrat[i] += ZUWACHS * anteile[i];")

# --- Regel: der leere Steckplatz verrechnet **nichts** -------------------------------
mutant(mut04_leerer_platz_verrechnet faellt
  "// ist eine Folgerung ueber die Eingabe und keine Regel des Verfahrens."
  "for (std::size_t j = 0; j < ARTEN; ++j) { vorrat[j] -= KOSTEN; }")

# --- Regel: `ai = 0` verbietet die Art nicht ----------------------------------------
mutant(mut05_ai_null_verboten faellt
  "const std::size_t gewaehlt = waehle(vorrat, zulaessig, abweichung);"
  "Zulaessigkeit hart = zulaessig; for (std::size_t h = 0; h < ARTEN; ++h) { if (anteile[h] == 0) hart[h] = false; } const std::size_t gewaehlt = waehle(vorrat, hart, abweichung);")

# --- Regel: die Folge traegt die Kennung `1..5`, nicht den Index `0..4` --------------
mutant(mut06_kennung_nullbasiert faellt
  "folge[platz] = static_cast<i64>(gewaehlt) + 1;"
  "folge[platz] = static_cast<i64>(gewaehlt);")

# --- Regel: drei Steckplaetze je Runde ------------------------------------------------
mutant(mut07_zwei_steckplaetze faellt
  "for (std::size_t platz = 0; platz < STECKPLAETZE; ++platz) {"
  "for (std::size_t platz = 0; platz + 1 < STECKPLAETZE; ++platz) {")

# --- Regel: `vi -= 5` je gesetzter Aktion ---------------------------------------------
mutant(mut08_kosten_sechs faellt
  "vorrat[gewaehlt] -= KOSTEN;"
  "vorrat[gewaehlt] -= KOSTEN + 1;")

# --- Regel: `vi += 3 * ai` am Rundenanfang -------------------------------------------
mutant(mut09_zuwachs_vier faellt
  "vorrat[i] += ZUWACHS * anteile[i];"
  "vorrat[i] += (ZUWACHS + 1) * anteile[i];")

# --- Regel: `leer_geblieben` zaehlt die leeren Plaetze --------------------------------
mutant(mut10_leer_nicht_gezaehlt faellt
  "++ergebnis.leer_geblieben;"
  "(void)0;")

# --- Zusage des Kopfes: die Schranke von `spiele` schliesst die Grenze ein ------------
mutant(mut11_schranke_ausschliessend faellt
  "runden > static_cast<i64>(RUNDEN_HOECHSTENS)"
  "runden >= static_cast<i64>(RUNDEN_HOECHSTENS)")

# --- Der Mutant, der die Abnahmebedingung 1 auf `k = 3` auf die Probe stellt ----------
#
# Er kappt den Lauf nach fuenf Runden. `k = 1` merkt davon **nichts** -- der Fall hat
# genau fuenf Runden. Nur die Zusicherung fuer `k = 3` faengt ihn. Stirbt er, ist
# belegt, dass die zweite Haelfte von Bedingung 1 traegt und nicht bloss dasteht.
mutant(mut12_nur_fuenf_runden faellt
  "for (i64 t = 0; t < runden; ++t) {"
  "for (i64 t = 0; t < runden && t < 5; ++t) {")
