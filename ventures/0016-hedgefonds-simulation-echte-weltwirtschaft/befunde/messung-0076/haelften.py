#!/usr/bin/env python3
"""Beide Haelften des neuen Musters einzeln stumpf gemacht -- Paket 0076.

Gruen uebersetzen ist kein Nachweis fuer einen Waechter. Nachgewiesen wird hier,
dass **jede** Haelfte des Musters `^(.*-)?NOTFOUND$` traegt: Wer eine davon
wegnimmt, sieht den Nichtwert wieder in `eintraege` stehen.

Vier Faelle an einem Wegwerf-Baum mit einem Ziel, einer Quelle, keiner
Quelleigenschaft. Instrumentiert wie in `notfound.py` -- ein `message()` vor
`set(pauschal "")`, sonst unveraendert.

    python3 befunde/messung-0076/haelften.py
"""

import os
import subprocess
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
QUELLE = "int f(double d){ int i = d; return i; }" + chr(10)
ANKER = chr(34) + "^(.*-)?NOTFOUND$" + chr(34)
ANKER = "MATCHES " + ANKER
MESS = ("  message(STATUS " + chr(34) + "MESS ${ziel}: eintraege=[${eintraege}]"
        + chr(34) + ")" + chr(10)
        + "  message(STATUS " + chr(34) + "MESS ${ziel}: herkuenfte=[${herkuenfte}]"
        + chr(34) + ")" + chr(10))

# Name -> (Muster statt des Ankers, was erwartet wird)
FAELLE = [
    ("kontrolle-neu", ANKER,
     "Kontrolle: das gebaute Muster, kein Nichtwert"),
    ("stumpf-nur-blank", "MATCHES " + chr(34) + "^NOTFOUND$" + chr(34),
     "nur die blanke Form -- die Zielabfragen muessen durchkommen"),
    ("stumpf-nur-bindestrich", "MATCHES " + chr(34) + "-NOTFOUND$" + chr(34),
     "der Stand vor 0076 -- die Quellabfragen muessen durchkommen"),
    ("stumpf-unverankert", "MATCHES " + chr(34) + "NOTFOUND" + chr(34),
     "ohne Anker -- faengt zwar beides, aber auch echte Werte mit dem Wort darin"),
]


def main():
    roh = (WURZEL / "werkzeugkette.cmake").read_text()
    if roh.count(ANKER) != 1:
        raise SystemExit("Anker kommt " + str(roh.count(ANKER)) + "-mal vor, erwartet 1-mal.")
    roh = roh.replace("  set(pauschal " + chr(34) + chr(34) + ")",
                      MESS + "  set(pauschal " + chr(34) + chr(34) + ")", 1)
    tmp = Path(os.environ.get("TMPDIR", "/tmp")) / "haelften0076"
    for name, muster, was in FAELLE:
        d = tmp / name
        d.mkdir(parents=True, exist_ok=True)
        kette = d / "werkzeugkette.cmake"
        kette.write_text(roh.replace(ANKER, muster, 1))
        (d / "z.cpp").write_text(QUELLE)
        (d / "CMakeLists.txt").write_text(
            "cmake_minimum_required(VERSION 3.22)" + chr(10)
            + "project(z LANGUAGES CXX)" + chr(10)
            + "include(" + str(kette) + ")" + chr(10)
            + "add_library(z STATIC z.cpp)" + chr(10)
            + "fabrik_warnsatz_anlegen(z)" + chr(10))
        r = subprocess.run(["cmake", "-S", str(d), "-B", str(d / "build")],
                           capture_output=True, text=True)
        txt = r.stdout + r.stderr
        (d / "konfig.log").write_text(txt)
        ez = [t for t in txt.splitlines() if "eintraege=[" in t]
        hz = [t for t in txt.splitlines() if "herkuenfte=[" in t]
        print(name.ljust(24) + " " + muster)
        print("     " + was)
        if not ez:
            print("     code=" + str(r.returncode) + "  KEINE MESSZEILE")
            continue
        teile = [t for t in ez[0].split("eintraege=[", 1)[1].rsplit("]", 1)[0].split(";") if t]
        hteile = [t for t in hz[0].split("herkuenfte=[", 1)[1].rsplit("]", 1)[0].split(";") if t]
        nw = [t for t in teile if t == "NOTFOUND" or t.endswith("-NOTFOUND")]
        print("     code=" + str(r.returncode) + "  " + str(len(teile))
              + " Eintraege, Nichtwerte: " + (str(nw) if nw else "keine"))
        if len(teile) != len(hteile):
            print("     !! Gleichschritt verletzt: " + str(len(teile)) + " zu " + str(len(hteile)))
        herkunft_nw = [hteile[i] for i, t in enumerate(teile) if t in nw]
        if herkunft_nw:
            print("     Herkunft der Nichtwerte: " + str(herkunft_nw))
    print(chr(10) + "Ablage: " + str(tmp))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())