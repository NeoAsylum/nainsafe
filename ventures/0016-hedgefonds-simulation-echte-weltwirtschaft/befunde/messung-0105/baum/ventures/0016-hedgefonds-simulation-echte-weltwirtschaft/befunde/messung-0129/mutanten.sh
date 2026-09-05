#!/bin/sh
# Legt die fuenf Mutanten der ausgelieferten Quelle in einem Arbeitsordner ab.
#
# Aufruf: mutanten.sh <wurzel-des-vorhabens> <arbeitsordner>
#
# Der Arbeitsordner ist der, in dem auch `nachweis-CMakeLists.txt` erwartet wird; im
# Lauf vom 2026-09-05 war das `bau/kp0129`.
set -e
wurzel=$1
arbeit=$2
hier=$(dirname "$0")
for fall in bedingung2 zerlegung form zusicherung regeln; do
  python3 "$hier/mutant.py" \
    "$wurzel/werkzeuge/bezeichner/bezeichner_riegel.cpp" \
    "$arbeit/mutant_$fall.cpp" "$fall"
done
