# Pruefung 0069, Angriff C -- die Linkerzeile in ihrer durchgereichten Form.
#
# Ueber die Abnahme hinaus, aber dieselbe Frage wie Variante C des Nachweises. Der
# vierte Durchgang des Riegels liest `LINK_OPTIONS` und `INTERFACE_LINK_OPTIONS` und
# meldet ein Wort, das mit `-l` beginnt oder auf `.a`/`.so` endet. Hier steht dasselbe
# `-l` in der Form, in der `g++` es an den Linker durchreicht.
#
# `INTERFACE` und nicht `PRIVATE`: `kern` ist eine statische Bibliothek, sie wird nie
# gelinkt. Wirksam wird ein Linkschalter an ihr allein ueber die Schnittstelle -- er
# landet dann auf der Linkerzeile jeder Probe, die `kern` linkt.
#
# `z` (zlib) und nicht `m`: libm gehoert zur C-Laufzeit und waere als "etwas anderes
# als die Standardbibliothek" streitbar. zlib ist es nicht.
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}"
               CALL target_link_options kern INTERFACE "-Wl,-lz")
