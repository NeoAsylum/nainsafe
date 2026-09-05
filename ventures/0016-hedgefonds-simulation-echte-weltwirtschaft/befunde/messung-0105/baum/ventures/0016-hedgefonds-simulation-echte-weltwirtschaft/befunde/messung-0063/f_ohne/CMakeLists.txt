cmake_minimum_required(VERSION 3.20)
project(wegwerf CXX)
include("${FABRIK_KETTE}")
add_library(z STATIC ../z.cpp)
fabrik_warnsatz_anlegen(z)
# Kein zusaetzlicher Schalter -- die Positivkontrolle. Ohne Pauschalabschalter muss
# derselbe Quelltext am eingebauten Verstoss rot werden.
