# Wegwerf-Mitglied des Kern-Pruefers, Paket 0046, 2026-09-03 -- die POSITIVKONTROLLE.
#
# Wortgleich zu `../vergessenes-mitglied/CMakeLists.txt`, nur MIT dem
# `PROJECT_IS_TOP_LEVEL`-Block. Sie belegt zweierlei: Der Abbruch der Negativprobe haengt
# an der fehlenden Einbindung und nicht an etwas anderem -- und die Schalter, die dann
# ankommen, beissen wirklich (derselbe Quelltext wird an `-Werror=unused-variable` rot).
cmake_minimum_required(VERSION 3.22)

project(erinnert LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  include(${CMAKE_CURRENT_LIST_DIR}/../../../werkzeugkette.cmake)
  enable_testing()
endif()

file(GLOB ERINNERT_QUELLEN CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(erinnert STATIC ${ERINNERT_QUELLEN})
target_compile_features(erinnert PUBLIC cxx_std_20)
fabrik_warnsatz_anlegen(erinnert)

message(STATUS "PRUEFER: diese Zeile WIRD erreicht -- die Konfiguration traegt")
