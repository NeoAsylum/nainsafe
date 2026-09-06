#!/bin/sh
# Zweiter Messlauf zu Paket 0145 -- derselbe Messstand, neuer Baumstand.
#
# Warum es ihn gibt: Der erste Lauf (Baumstand 5d04c39, Mitschnitte ohne Marke)
# ist gelaufen, bevor vier Baupakete den Kern angefasst haben -- 0132, 0152,
# 0153, 0156. Ein Befund, dessen Baumstand vier Commits alt ist, sagt nichts
# ueber den Baum, den der naechste liest.
#
# Der Ablauf ist Zeile fuer Zeile der aus `lauf.sh`. Der einzige Unterschied
# sind die Dateinamen: alles traegt die Marke `-2`, damit die Mitschnitte des
# ersten Laufs unangetastet bleiben. Geloescht und ueberschrieben wird nichts
# (Hausregel 3) -- der Vergleich der beiden Staende IST das Ergebnis.
#
# Aufruf, aus WSL, Wurzel des Repos:
#   sh ventures/0016-.../befunde/beschraenktheit/lauf-2.sh

set -eu

ABLAGE=$(cd "$(dirname "$0")" && pwd)
WURZEL=$(cd "$ABLAGE/../.." && pwd)

# Der Warnsatz aus `werkzeugkette.cmake`, `FABRIK_STRENGE`.
STRENGE="-Wall -Wextra -Werror \
 -Wconversion -Wsign-conversion \
 -Wshadow -Wold-style-cast -Wcast-qual -Wuseless-cast \
 -Wdouble-promotion -Wfloat-equal \
 -Wnon-virtual-dtor -Woverloaded-virtual \
 -Wnull-dereference -Wformat=2"

UEBERLAUF="-fwrapv -fno-fast-math"
SANITIZER="-fsanitize=undefined,address -fno-sanitize-recover=all"

echo "=============================================================="
echo "Werkzeugkette"
echo "=============================================================="
g++ --version | head -1
cmake --version | head -1
echo "Baum:  $WURZEL"
echo "Stand: $(cd "$WURZEL" && git rev-parse --short HEAD)"
echo
profil="$1"
marke="$2"
bau="$ABLAGE/bau2-sanitizer-$marke"
bibliothek="$3"
zusatz="${4:-}"

echo "=============================================================="
echo "Profil FABRIK_SANITIZER=$profil"
echo "=============================================================="

cmake -S "$WURZEL" -B "$bau" -DFABRIK_SANITIZER="$profil" >"$bau.konfiguration.txt" 2>&1
grep -E 'Sperrebindungsriegel|Schlussriegel|Nullabhaengigkeitsriegel' "$bau.konfiguration.txt" || true

echo "--- ctest -N VOR der Messung (Bezugsstand, Abnahme 4) ---"
ctest --test-dir "$bau" -N >"$ABLAGE/ctest-liste-2-sanitizer-$marke.txt" 2>&1
tail -3 "$ABLAGE/ctest-liste-2-sanitizer-$marke.txt"

cmake --build "$bau" -j 4 >"$bau.bau.txt" 2>&1
echo "--- Bau: ok"

echo "--- Uebersetzung des Messstands (von Hand, kein Eingriff in den Baum) ---"
# shellcheck disable=SC2086
g++ -std=c++20 -O2 -g $STRENGE $UEBERLAUF $zusatz \
    -I "$WURZEL/kern/include" \
    -o "$bau/beschraenktheit" \
    "$ABLAGE/beschraenktheit.cpp" \
    "$bau/kern/lib$bibliothek.a"
echo "    g++ Code 0, gebunden gegen lib$bibliothek.a"

for lage in gueltig null; do
    mitschnitt="$ABLAGE/lauf-2-sanitizer-$marke-$lage.txt"
    echo "--- Lauf: Ausgangslage '$lage' -> $(basename "$mitschnitt")"
    set +e
    "$bau/beschraenktheit" "$lage" >"$mitschnitt" 2>&1
    code=$?
    set -e
    echo "    Rueckgabewert $code, $(wc -l <"$mitschnitt") Zeilen Mitschnitt"
    tail -14 "$mitschnitt" | sed 's/^/    | /'
done

echo "--- ctest -N NACH der Messung (Abnahme 4) ---"
ctest --test-dir "$bau" -N | tail -3
