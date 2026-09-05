#!/bin/sh
# Der Messstand zu Paket 0145 -- 200 Runden ohne Spieler, in beiden Profilen.
#
# Aufruf (aus WSL, wie jede Beruehrung dieses Baums):
#   sh ventures/0016-.../befunde/beschraenktheit/lauf.sh
#
# Was das Skript tut, in der Reihenfolge:
#
#   1. Es legt je Profil ein **eigenes** Bauverzeichnis unter dieser Ablage an --
#      `bau-sanitizer-on` und `bau-sanitizer-off`. Es fasst `ventures/.../bau` nicht
#      an: Dort baut der Baulauf, und zwei Laeufe im selben Verzeichnis sind der Fall
#      aus `lehren.md` vom 2026-09-03. Beide Namen treffen `ventures/**/bau-*/` in der
#      obersten `.gitignore`, kommen also nicht in die Versionierung.
#   2. Es zaehlt **vor** der Messung die ctest-Eintraege des Arbeitsbereichs je Profil
#      (`ctest -N`). Das ist der Bezugsstand aus Abnahmebedingung 4.
#   3. Es baut den Arbeitsbereich -- gebraucht wird daraus nur `libkern.a` bzw.
#      `libkern_geprueft.a`, aber ein Teilbau saehe wie eine Abkuerzung aus, und der
#      Bau ist die Gegenprobe dafuer, dass der Baum heil ist.
#   4. Es uebersetzt `beschraenktheit.cpp` **von Hand**, mit demselben Warnsatz und
#      denselben Ueberlaufschaltern, die `werkzeugkette.cmake` an jedes Ziel des Baums
#      haengt. Von Hand, weil ein `add_executable` in einer `CMakeLists.txt` genau das
#      waere, was Abnahmebedingung 4 verbietet: ein Eingriff in den Baum und ein
#      Ziel mehr.
#   5. Es laesst beide Ausgangslagen in beiden Profilen laufen und schreibt je einen
#      Mitschnitt.
#   6. Es zaehlt **nach** der Messung noch einmal.
#
# Das Skript raeumt die Bauverzeichnisse nicht weg. Wer nachmisst, will sie haben; und
# geloescht wird hier ohnehin nichts (Hausregel 3).

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

fuer_profil() {
    profil="$1"          # ON oder OFF
    bau="$ABLAGE/bau-sanitizer-$2"
    bibliothek="$3"      # kern_geprueft oder kern
    zusatz="$4"          # Sanitizer-Schalter oder leer

    echo "=============================================================="
    echo "Profil FABRIK_SANITIZER=$profil"
    echo "=============================================================="

    cmake -S "$WURZEL" -B "$bau" -DFABRIK_SANITIZER="$profil" >"$bau.konfiguration.txt" 2>&1 \
        || { echo "cmake -S fehlgeschlagen, Code $?"; cat "$bau.konfiguration.txt"; return 1; }
    grep -E 'Sperrebindungsriegel|Schlussriegel|Nullabhaengigkeitsriegel' \
        "$bau.konfiguration.txt" || true

    echo "--- ctest -N VOR der Messung (Bezugsstand, Abnahme 4) ---"
    ctest --test-dir "$bau" -N | tail -3

    cmake --build "$bau" -j 4 >"$bau.bau.txt" 2>&1 \
        || { echo "cmake --build fehlgeschlagen, Code $?"; tail -40 "$bau.bau.txt"; return 1; }
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
        mitschnitt="$ABLAGE/lauf-sanitizer-$2-$lage.txt"
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
    echo
}

fuer_profil ON  on  kern_geprueft "$SANITIZER"
fuer_profil OFF off kern          ""

echo "=============================================================="
echo "Fertig. Mitschnitte in $ABLAGE"
echo "=============================================================="
