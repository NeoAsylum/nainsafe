#!/usr/bin/env python3
"""Bedingung 1 von Paket 0076 -- misst, ob ein Nichtwert in `eintraege` landet.

Aufbau: eine Kopie von `werkzeugkette.cmake` mit genau einer zusaetzlichen Zeile --
ein `message()` unmittelbar vor `set(pauschal "")`, das `eintraege` je Ziel ausgibt.
Sonst unveraendert. Der Wegwerf-Baum hat genau ein Ziel, eine Quelle und **keine**
Quelleigenschaft; das ist der Normalfall jeder Uebersetzungseinheit im Arbeitsbaum.

Aufruf aus WSL heraus:

    python3 befunde/messung-0076/notfound.py            # gegen den Arbeitsbaum
    python3 befunde/messung-0076/notfound.py dffb251    # gegen einen Commit

Ausgegeben wird die Zeile `MESS` je Ziel und daneben, wie oft `NOTFOUND` als
**eigener Listeneintrag** darin steht. Gezaehlt wird nach dem Zerlegen an `;`, nicht
per Textsuche: `-fwrapv` enthaelt kein `NOTFOUND`, aber ein Herkunftstext koennte es.
"""

import os
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
KETTE = WURZEL / "werkzeugkette.cmake"
QUELLE = "int f(double d){ int i = d; return i; }\n"
ANKER = 'set(pauschal "")'
MESSZEILE = ('  message(STATUS "MESS ${ziel}: eintraege=[${eintraege}]")\n'
             '  message(STATUS "MESS ${ziel}: herkuenfte=[${herkuenfte}]")\n')


def kette_holen(stand, ablage):
    """Die zu messende Fassung als eigene Datei -- nie die im Baum einbinden."""
    if stand == "ARBEITSBAUM":
        roh = KETTE.read_text()
    else:
        rel = KETTE.relative_to(WURZEL.parents[1])
        roh = subprocess.run(["git", "-C", str(WURZEL.parents[1]), "show", f"{stand}:{rel}"],
                             capture_output=True, check=True, text=True).stdout
    if roh.count(ANKER) != 1:
        raise SystemExit(f"Anker {ANKER!r} kommt {roh.count(ANKER)}x vor, erwartet 1x. "
                         "Die Instrumentierung waere nicht mehr die gemeinte Stelle.")
    zeile = [z for z in roh.splitlines() if ANKER in z][0]
    einzug = zeile[: len(zeile) - len(zeile.lstrip())]
    instrumentiert = roh.replace(zeile, MESSZEILE.replace("  ", einzug, 1)
                                 .replace("\n  ", "\n" + einzug) + zeile, 1)
    ziel = ablage / "werkzeugkette.cmake"
    ziel.write_text(instrumentiert)
    return ziel


def main():
    stand = sys.argv[1] if len(sys.argv) > 1 else "ARBEITSBAUM"
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / f"messung0076-{stand}"
    ablage.mkdir(parents=True, exist_ok=True)
    kette = kette_holen(stand, ablage)

    baum = ablage / "baum"
    baum.mkdir(parents=True, exist_ok=True)
    (baum / "z.cpp").write_text(QUELLE)
    (baum / "CMakeLists.txt").write_text(
        "cmake_minimum_required(VERSION 3.22)\nproject(z LANGUAGES CXX)\n"
        f"include({kette})\n"
        "add_library(z STATIC z.cpp)\nfabrik_warnsatz_anlegen(z)\n")

    r = subprocess.run(["cmake", "-S", str(baum), "-B", str(baum / "build")],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    (ablage / "konfig.log").write_text(txt)

    print(f"Stand: {stand}   Kette: {kette}   Konfigurationscode: {r.returncode}\n")
    gesamt = 0
    for z in txt.splitlines():
        z = z.strip()
        if "MESS " not in z:
            continue
        print(z)
        if "eintraege=[" in z:
            inhalt = z.split("eintraege=[", 1)[1].rsplit("]", 1)[0]
            teile = [t for t in inhalt.split(";") if t != ""]
            treffer = [t for t in teile if t == "NOTFOUND" or t.endswith("-NOTFOUND")]
            gesamt += len(treffer)
            print(f"        {len(teile)} Eintraege, davon Nichtwert: {len(treffer)} {treffer}")
            print(f"        letzter Eintrag: {teile[-1] if teile else '(keiner)'}")
    print(f"\nNichtwerte in `eintraege` insgesamt: {gesamt}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
