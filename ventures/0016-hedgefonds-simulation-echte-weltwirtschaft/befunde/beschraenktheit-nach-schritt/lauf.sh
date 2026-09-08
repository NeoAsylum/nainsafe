#!/bin/sh
# Der Messstand zu Paket 0243 -- 200 Runden ohne Spieler, drei Ausgangslagen, zwei
# Profile. Er loest den Stand von 0145 ab
# (`befunde/beschraenktheit/lauf.sh`); dessen Messprogramm uebersetzt seit Paket 0229
# nicht mehr und wuerde seit 0228 in Runde 1 abbrechen. Der Grund steht ausfuehrlich im
# Kopf von `beschraenktheit-nach-schritt.cpp` daneben.
#
# Aufruf (aus WSL, wie jede Beruehrung dieses Baums), eine Zeile:
#   sh ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit-nach-schritt/lauf.sh
#
# Es braucht kein Argument und keine Umgebungsvariable. Es liegt nichts an dem
# Verzeichnis, aus dem es gerufen wird -- der Baum wird aus dem Pfad des Skripts
# hergeleitet.
#
# Was das Skript tut, in der Reihenfolge:
#
#   1. Es legt je Profil ein **eigenes** Bauverzeichnis unter dieser Ablage an --
#      `bau-sanitizer-on` und `bau-sanitizer-off`. Es fasst `ventures/.../bau` nicht
#      an: Dort baut der Baulauf, und zwei Laeufe im selben Verzeichnis sind der Fall
#      aus `lehren.md` vom 2026-09-03. Beide Namen treffen `ventures/**/bau-*/` in der
#      obersten `.gitignore` (Zeile 246), kommen also nicht in die Versionierung.
#   2. Es zaehlt **vor** der Messung die ctest-Eintraege des Arbeitsbereichs je Profil
#      (`ctest -N`) und legt die volle Liste als Datei ab. Das ist der Bezugsstand.
#   3. Es baut den Arbeitsbereich -- gebraucht wird daraus nur `libkern.a` bzw.
#      `libkern_geprueft.a`, aber ein Teilbau saehe wie eine Abkuerzung aus, und der
#      Bau ist die Gegenprobe dafuer, dass der Baum heil ist.
#   4. Es uebersetzt `beschraenktheit-nach-schritt.cpp` **von Hand**, mit demselben
#      Warnsatz und denselben Ueberlaufschaltern, die `werkzeugkette.cmake` an jedes Ziel
#      des Baums haengt. Von Hand, weil ein `add_executable` in einer `CMakeLists.txt`
#      ein Eingriff in den Baum und ein ctest-Ziel mehr waere.
#   5. Es laesst alle drei Ausgangslagen in beiden Profilen laufen und schreibt je einen
#      **benannten** Mitschnitt: `lauf-sanitizer-<on|off>-<lage>.txt`, sechs Dateien.
#   6. Es zaehlt **nach** der Messung noch einmal und legt die Liste ein zweites Mal ab.
#
# Das Skript raeumt die Bauverzeichnisse nicht weg. Wer nachmisst, will sie haben; und
# geloescht wird hier ohnehin nichts (Hausregel 3).
#
# Erwartete Rueckgabewerte des Messprogramms -- was sie bedeuten, steht in
# `bruch-2026-09-08-2.md` unter "Was jede der sechs Dateien enthalten wird". Ein von
# null verschiedener Rueckgabewert ist hier **kein** Fehler des Standes: Zwei der drei
# Lagen brechen vorhergesagt ab. Deshalb faengt die Schleife den Wert ab, statt an ihm
# zu sterben.

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
# Der Arbeitsbereich gehoert in den Mitschnitt: "gemessen an <Kennung>" liest sich sonst
# wie "an einem sauberen Baum". Die Zahl ist die der geaenderten und unverfolgten Dateien
# im ganzen Repo.
echo "Arbeitsbereich: $(cd "$WURZEL/../.." && git status --porcelain | wc -l) Datei(en) \
geaendert oder unverfolgt"
echo

fuer_profil() {
    profil="$1"          # ON oder OFF
    kurz="$2"            # on oder off
    bau="$ABLAGE/bau-sanitizer-$kurz"
    bibliothek="$3"      # kern_geprueft oder kern
    zusatz="$4"          # Sanitizer-Schalter oder leer

    echo "=============================================================="
    echo "Profil FABRIK_SANITIZER=$profil"
    echo "=============================================================="

    cmake -S "$WURZEL" -B "$bau" -DFABRIK_SANITIZER="$profil" >"$bau.konfiguration.txt" 2>&1 \
        || { echo "cmake -S fehlgeschlagen, Code $?"; cat "$bau.konfiguration.txt"; return 1; }
    grep -E 'Sperrebindungsriegel|Schlussriegel|Nullabhaengigkeitsriegel' \
        "$bau.konfiguration.txt" || true

    echo "--- ctest -N VOR der Messung (Bezugsstand) ---"
    ctest --test-dir "$bau" -N >"$ABLAGE/ctest-liste-$kurz-vor.txt" 2>&1
    tail -3 "$ABLAGE/ctest-liste-$kurz-vor.txt"

    cmake --build "$bau" -j 4 >"$bau.bau.txt" 2>&1 \
        || { echo "cmake --build fehlgeschlagen, Code $?"; tail -40 "$bau.bau.txt"; return 1; }
    echo "--- Bau: ok"

    echo "--- Uebersetzung des Messstands (von Hand, kein Eingriff in den Baum) ---"
    # shellcheck disable=SC2086
    g++ -std=c++20 -O2 -g $STRENGE $UEBERLAUF $zusatz \
        -I "$WURZEL/kern/include" \
        -o "$bau/beschraenktheit-nach-schritt" \
        "$ABLAGE/beschraenktheit-nach-schritt.cpp" \
        "$bau/kern/lib$bibliothek.a"
    echo "    g++ Code 0, gebunden gegen lib$bibliothek.a"

    for lage in gueltig null decke; do
        mitschnitt="$ABLAGE/lauf-sanitizer-$kurz-$lage.txt"
        echo "--- Lauf: Ausgangslage '$lage' -> $(basename "$mitschnitt")"
        set +e
        "$bau/beschraenktheit-nach-schritt" "$lage" >"$mitschnitt" 2>&1
        code=$?
        set -e
        echo "    Rueckgabewert $code, $(wc -l <"$mitschnitt") Zeilen Mitschnitt"
        tail -16 "$mitschnitt" | sed 's/^/    | /'
    done

    echo "--- ctest -N NACH der Messung ---"
    ctest --test-dir "$bau" -N >"$ABLAGE/ctest-liste-$kurz-nach.txt" 2>&1
    tail -3 "$ABLAGE/ctest-liste-$kurz-nach.txt"

    echo "--- Bezugsstand gehalten? diff der beiden ctest-Listen ---"
    if diff "$ABLAGE/ctest-liste-$kurz-vor.txt" "$ABLAGE/ctest-liste-$kurz-nach.txt" >/dev/null
    then
        echo "    gleich -- der Baum hat weder ein Ziel gewonnen noch eines verloren."
    else
        echo "    UNTERSCHIEDLICH -- das ist ein Befund gegen diesen Stand, nicht gegen den Baum."
        diff "$ABLAGE/ctest-liste-$kurz-vor.txt" "$ABLAGE/ctest-liste-$kurz-nach.txt" || true
    fi
    echo
}

fuer_profil ON  on  kern_geprueft "$SANITIZER"
fuer_profil OFF off kern          ""

echo "=============================================================="
echo "Fertig. Sechs Mitschnitte und vier ctest-Listen in $ABLAGE"
echo "Die Vorhersagen zu jeder der sechs Dateien stehen in bruch-2026-09-08-2.md."
echo "=============================================================="
