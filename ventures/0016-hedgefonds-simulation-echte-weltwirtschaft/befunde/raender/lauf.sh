#!/bin/sh
# Der Messstand zu Paket 0160 -- die drei harten Fehler der Runde, in beiden Profilen.
#
# Aufruf (aus WSL, wie jede Beruehrung dieses Baums):
#   sh ventures/0016-.../befunde/raender/lauf.sh
#
# Aufbau wie `befunde/beschraenktheit/lauf.sh` aus Paket 0145, und aus denselben
# Gruenden: eigenes Bauverzeichnis je Profil unter dieser Ablage (nicht
# `ventures/.../bau`, dort baut der Baulauf), `ctest -N` vor und nach der Messung als
# Bezugsstand fuer Abnahmebedingung 2, und die Uebersetzung des Messstands von Hand statt
# ueber ein `add_executable` -- ein Ziel mehr im Baum waere genau das, was die Abnahme
# ausschliesst.
#
# Der Unterschied zu 0145: Es laufen **sechs** Aufrufe je Profil, jeder ein eigener
# Programmlauf mit genau einem Aufruf von `kern::schritt::schritt`. Die Beschriftung
# steht hier, die Zahlen kommen aus dem Programm, der Wortlaut der Abbruchmeldung aus
# dessen Fehlerausgabe.

set -eu

ABLAGE=$(cd "$(dirname "$0")" && pwd)
WURZEL=$(cd "$ABLAGE/../.." && pwd)

# Der Warnsatz aus `werkzeugkette.cmake`, `FABRIK_STRENGE`, Zeile fuer Zeile derselbe.
STRENGE="-Wall -Wextra -Werror \
 -Wconversion -Wsign-conversion \
 -Wshadow -Wold-style-cast -Wcast-qual -Wuseless-cast \
 -Wdouble-promotion -Wfloat-equal \
 -Wnon-virtual-dtor -Woverloaded-virtual \
 -Wnull-dereference -Wformat=2"

# `FABRIK_UEBERLAUF_SCHALTER` -- ADR 0011, Massnahme 1, in JEDEM Profil.
UEBERLAUF="-fwrapv -fno-fast-math"

# `FABRIK_SANITIZER_SCHALTER` -- ADR 0011, Massnahme 2.
SANITIZER="-fsanitize=undefined,address -fno-sanitize-recover=all"

echo "=============================================================="
echo "Werkzeugkette"
echo "=============================================================="
g++ --version | head -1
cmake --version | head -1
echo "Baum:  $WURZEL"
echo "Stand: $(cd "$WURZEL" && git rev-parse --short HEAD)"
echo
for kurz in on off; do
    if [ "$kurz" = on ]; then
        profil=ON
        bibliothek=kern_geprueft
        zusatz="$SANITIZER"
    else
        profil=OFF
        bibliothek=kern
        zusatz=""
    fi
    bau="$ABLAGE/bau-sanitizer-$kurz"
    mitschnitt="$ABLAGE/lauf-sanitizer-$kurz.txt"

    echo "=============================================================="
    echo "Profil FABRIK_SANITIZER=$profil"
    echo "=============================================================="

    cmake -S "$WURZEL" -B "$bau" -DFABRIK_SANITIZER="$profil" >"$bau.konfiguration.txt" 2>&1
    grep -E 'Sperrebindungsriegel|Schlussriegel|Nullabhaengigkeitsriegel' \
        "$bau.konfiguration.txt" || true

    echo "--- ctest -N VOR der Messung (Bezugsstand, Abnahme 2) ---"
    ctest --test-dir "$bau" -N | tail -3

    cmake --build "$bau" -j 4 >"$bau.bau.txt" 2>&1
    echo "--- Bau: ok"

    echo "--- Uebersetzung des Messstands (von Hand, kein Eingriff in den Baum) ---"
    # shellcheck disable=SC2086
    g++ -std=c++20 -O2 -g $STRENGE $UEBERLAUF $zusatz \
        -I "$WURZEL/kern/include" \
        -o "$bau/raender" \
        "$ABLAGE/raender.cpp" \
        "$bau/kern/lib$bibliothek.a"
    echo "    g++ Code 0, gebunden gegen lib$bibliothek.a"

    : >"$mitschnitt"
    lage=1
    while [ "$lage" -le 6 ]; do
        echo "==============================================================" >>"$mitschnitt"
        echo "Lage $lage: $(head -n "$lage" "$ABLAGE/lagen.txt" | tail -n 1)" >>"$mitschnitt"
        echo "Aufruf: raender $lage  (genau ein Aufruf von kern::schritt::schritt)" >>"$mitschnitt"
        echo "--- Standardausgabe und Fehlerausgabe, im Wortlaut ---" >>"$mitschnitt"
        set +e
        "$bau/raender" "$lage" >>"$mitschnitt" 2>>"$mitschnitt"
        code=$?
        set -e
        echo "--- Rueckgabewert: $code" >>"$mitschnitt"
        echo >>"$mitschnitt"
        lage=$((lage + 1))
    done
    echo "--- sechs Laeufe -> $(basename "$mitschnitt")"

    echo "--- ctest -N NACH der Messung (Abnahme 2) ---"
    ctest --test-dir "$bau" -N | tail -3
    echo
done

echo "=============================================================="
echo "Fertig. Mitschnitte in $ABLAGE"
echo "=============================================================="
