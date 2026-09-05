# Das Mitglied, das der Riegel aus Paket 0046 NICHT faengt: Es ruft
# `fabrik_warnsatz_anlegen` gar nicht erst und hat auch keinen
# `PROJECT_IS_TOP_LEVEL`-Block. Genau so wird `konsole` aus T13 geschrieben, wenn sein
# Bauagent die Form nicht kennt. Kein unbekannter Aufruf, also kein Abbruch.
cmake_minimum_required(VERSION 3.22)

add_library(mitglied_ohne_satz STATIC ${CMAKE_CURRENT_LIST_DIR}/../../erinnertes-mitglied/src/etwas.cpp)
