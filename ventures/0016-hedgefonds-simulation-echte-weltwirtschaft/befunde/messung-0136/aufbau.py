#!/usr/bin/env python3
"""Die drei Wegwerf-Baeume der Messung zu Paket 0136.

Der Umzug des Waechters `schlussriegel_nachbau` aus `pruefstand/CMakeLists.txt` nach
`werkzeuge/schlussriegel/CMakeLists.txt` war beim Zuschnitt dieses Laufs schon im
Arbeitsbaum und schon eingecheckt (Commit `0333b81`, ein fremder Lauf hat ihn
mitgenommen). Gemessen werden muss trotzdem gegen den **Stand davor** -- und der ist
nicht `0333b81^`: In jenem Commit stecken die Ergebnisse mehrerer Pakete, unter anderem
75 geaenderte Zeilen in `werkzeugkette.cmake`. Ein Vergleich dagegen maesse drei Pakete
und nennte es eines (Logbuch des Testentwicklers, 2026-09-05).

Deshalb wird der Stand davor **gebaut** statt ausgepackt: eine Kopie des heutigen Baums,
in der genau diese eine Aenderung rueckgaengig gemacht ist. Der Rueckbau ist exakt und
nicht nachempfunden -- `git diff` zwischen dem letzten Commit vor dem Umzug und `HEAD`
zeigt fuer beide Dateien ausschliesslich diese Aenderung:

    pruefstand/CMakeLists.txt   4ee0f79 -> HEAD   nur der Waechterblock
    CMakeLists.txt              497bcbc -> HEAD   nur Kopfabsatz + FABRIK_MITGLIEDER

Beide alten Fassungen werden deshalb woertlich aus jenen Commits geholt.

Drei Baeume, alle unter `bau/messung-0136/` **im Vorhaben** und nicht unter `$TMPDIR`.
Der Grund ist gemessen und nicht Geschmack: `$TMPDIR` ist auf dieser Maschine ein
`tmpfs` von 7,8 GB, das am 2026-09-05 zu 94 Prozent belegt war -- drei Kopien zu je
82 MB und ihre sechs Baubaeume haben es gefuellt, und danach scheiterte jeder weitere
Aufruf an ENOSPC statt an der Sache. `/home/adria/fabrik` hat 952 GB frei. Unter `bau/`
stoert die Ablage niemanden: Der Ordner steht in `.gitignore` (`ventures/**/bau/`), in
`UNGELESENE_ORDNER` beider Riegel und in `AUSGENOMMEN` der Manifestsuche von
`baulauf.py`.

    vorher   Kopie mit rueckgebautem Umzug -- der Vergleichsstand
    gruen    Kopie des heutigen Baums, unveraendert -- die Gegenprobe
    stumpf   dieselbe Kopie mit **einer** stumpf gemachten Zeile in
             `fabrik_riegel_sammeln` von `werkzeugkette.cmake`

Der Arbeitsbaum wird nicht angefasst. `git status` ist vor und nach diesem Skript
zeichengleich; die Baeume liegen ausserhalb des Repos.

Aufruf aus WSL heraus:

    python3 befunde/messung-0136/aufbau.py
"""

import shutil
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
ABLAGE = WURZEL / "bau" / "messung-0136"

# Commit -> Datei, aus der die Fassung vor dem Umzug geholt wird.
VORHER_FASSUNGEN = {
    "pruefstand/CMakeLists.txt": "4ee0f79",
    "CMakeLists.txt": "497bcbc",
}

# Die eine Zeile, die den Sammler des Schlussriegels stumpf macht. Woertlich dieselbe
# Mutation wie im Nachweis zu Paket 0133 -- eine Gegenprobe, die eine andere Zeile
# trifft, belegt nicht dieselbe Regel.
ALT = 'if(NOT "${${listenname}}" STREQUAL "")'
NEU = "if(FALSE)  # STUMPF GEMACHT -- Gegenprobe zu Paket 0136, nicht eingecheckt"


def kopieren(ziel):
    """Den Vorhabensbaum kopieren, ohne die Baubaeume.

    `bau` faellt an jeder Ebene weg und nicht nur an der Wurzel: Unter `befunde/`
    liegen ausgepackte Vorhabensbaeume frueherer Messungen, die eigene tragen. Mit
    ihnen waere die Kopie ueber 700 MB gross, ohne sie unter 100.
    """
    if ziel.exists():
        shutil.rmtree(ziel)
    shutil.copytree(WURZEL, ziel,
                    ignore=shutil.ignore_patterns("bau"), symlinks=True)
    specs_spiegeln(ziel)


def specs_spiegeln(baum):
    """Die Vorgaben dorthin legen, wo der Belegstellenriegel des Wegwerf-Baums sucht.

    Der Riegel schlaegt die Vorgaben ueber den Ort des Vorhabens nach --
    `<vorhaben>/../../specs/<name des vorhabens>` -- und **bricht ab**, wenn dort kein
    Verzeichnis liegt. Das ist richtig so: Ohne die Vorgaben liefe jedes Zitat in sie
    als "Ziel ausserhalb des Bestands" durch, und der Riegel meldete gruen ueber nichts.

    Fuer einen kopierten Baum heisst es aber, dass er an einem Ort steht, an dem der
    Riegel nichts findet. Gemessen am 2026-09-05 ohne diesen Spiegel: Der Bauweg
    `arbeitsbereich` des Vergleichsbaums meldete `ctest code=8`, eine verfehlte Probe
    (`belegstellen_riegel`), Wortlaut
    `'.../bau/specs/vorher' ist kein Verzeichnis` -- ein roter Vergleichsstand aus einem
    Grund, der mit dem gemessenen Unterschied nichts zu tun hat. Ein Vorlauf, der aus
    fremdem Grund rot ist, meldet jede Aenderung als gefangen (Logbuch des
    Testentwicklers, 2026-09-05).
    """
    quelle = WURZEL.parents[1] / "specs" / WURZEL.name
    ziel = baum.parents[1] / "specs" / baum.name
    if not quelle.is_dir():
        raise SystemExit("Die Vorgaben des Vorhabens fehlen: " + str(quelle))
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.parent.mkdir(parents=True, exist_ok=True)
    shutil.copytree(quelle, ziel, symlinks=True)


def git_fassung(commit, datei):
    r = subprocess.run(["git", "show", commit + ":ventures/"
                        + WURZEL.name + "/" + datei],
                       cwd=str(WURZEL), capture_output=True, text=True)
    if r.returncode != 0:
        raise SystemExit("`git show " + commit + ":" + datei + "` gab Code "
                         + str(r.returncode) + ": " + r.stderr.strip())
    return r.stdout


def groesse(pfad):
    r = subprocess.run(["du", "-sh", str(pfad)], capture_output=True, text=True)
    return r.stdout.split()[0] if r.returncode == 0 else "?"


def main():
    ABLAGE.mkdir(parents=True, exist_ok=True)

    # --- der Stand davor -------------------------------------------------
    vorher = ABLAGE / "vorher"
    kopieren(vorher)
    for datei, commit in VORHER_FASSUNGEN.items():
        (vorher / datei).write_text(git_fassung(commit, datei))
        print("vorher: " + datei + " zurueckgeholt aus " + commit)
    kasten = vorher / "werkzeuge" / "schlussriegel"
    if not kasten.exists():
        raise SystemExit("Im kopierten Baum fehlt " + str(kasten)
                         + " -- dann ist der Umzug nicht der gemessene Unterschied.")
    shutil.rmtree(kasten)
    print("vorher: werkzeuge/schlussriegel entfernt")

    # Nachweis, dass der Rueckbau wirklich der Rueckbau ist und nicht mehr: Der Baum
    # `vorher` darf sich vom Arbeitsbaum in genau diesen drei Dingen unterscheiden.
    r = subprocess.run(["diff", "-rq", "--exclude=bau", str(WURZEL), str(vorher)],
                       capture_output=True, text=True)
    print("")
    print("$ diff -rq --exclude=bau <arbeitsbaum> " + str(vorher))
    print(r.stdout.strip() or "(keine Unterschiede -- dann stimmt etwas nicht)")
    print("")

    # --- die Gegenprobe und der stumpfe Baum ------------------------------
    gruen = ABLAGE / "gruen"
    kopieren(gruen)
    print("gruen:  unveraenderte Kopie des heutigen Baums")

    stumpf = ABLAGE / "stumpf"
    kopieren(stumpf)
    kette = stumpf / "werkzeugkette.cmake"
    txt = kette.read_text()
    # Bricht ab, wenn der Wortlaut nicht **genau einmal** vorkommt. Eine Mutation, die
    # zwei Stellen trifft oder keine, belegt nichts.
    if txt.count(ALT) != 1:
        raise SystemExit("Der Wortlaut kommt " + str(txt.count(ALT))
                         + "-mal in werkzeugkette.cmake vor, erwartet genau einmal: "
                         + ALT)
    kette.write_text(txt.replace(ALT, NEU))
    print("stumpf: eine Zeile in fabrik_riegel_sammeln ersetzt")
    print("        " + ALT)
    print("    ->  " + NEU)

    print("")
    for name in ("vorher", "gruen", "stumpf"):
        print(name.ljust(8) + groesse(ABLAGE / name).rjust(6) + "  "
              + str(ABLAGE / name))
    return 0


if __name__ == "__main__":
    sys.exit(main())
