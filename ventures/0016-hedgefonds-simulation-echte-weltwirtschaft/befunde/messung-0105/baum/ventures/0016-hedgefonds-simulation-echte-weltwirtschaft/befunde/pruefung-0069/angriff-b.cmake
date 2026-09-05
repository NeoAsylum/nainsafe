# Pruefung 0069, Angriff B -- die Zielform aus einem fremden Verzeichnis.
#
# `target_link_libraries(kern ...)` braucht das Ziel, und das entsteht erst beim
# Abstieg. Deshalb aufgeschoben auf das Ende des obersten Verzeichnisses -- dieselbe
# Stelle, an die Bedingung 2 Variante B die Zeile setzt ("am Ende des
# Wurzelverzeichnisses"), und ausserhalb des Verzeichnisses, in dem `kern` entsteht.
#
# Die Reihenfolge ist der Punkt: Dieses DEFER wird waehrend `project()` gestellt, das
# des Schlussriegels erst in `include(werkzeugkette.cmake)` danach. CMake fuehrt
# aufgeschobene Aufrufe in der Reihenfolge ihrer Stellung aus, der Angriff steht also
# vor dem Riegel.
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}"
               CALL target_link_libraries kern PRIVATE m)
