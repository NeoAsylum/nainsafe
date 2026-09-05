# Pruefung 0069, Angriff A -- die Verzeichnisform eine Ebene hoeher.
#
# Eingehaengt ueber `-DCMAKE_PROJECT_INCLUDE=...`, damit der **Arbeitsbaum
# unveraendert** bleibt: CMake bindet diese Datei am Ende des `project()`-Aufrufs
# im obersten Verzeichnis ein, also vor `add_subdirectory(kern)`. Genau die Stelle,
# die Bedingung 2 Variante A meint -- nur ohne eine Zeile im Wurzelmanifest.
#
# Gelinkt wird `m` (libm) und kein Wegwerfziel: Ein selbst angelegtes Ziel ohne
# Warnsatz wuerde den *anderen* Riegel derselben Datei zuerst ausloesen, und der
# Rotnachweis gehoerte dann dem falschen Riegel.
link_libraries(m)
