#!/usr/bin/env python3
"""Wartet, bis der Arbeitsbaum uebersetzbar ist, und faehrt dann `nachweis.py`.

Warum das noetig ist und nicht Bequemlichkeit: Der Baum bewegt sich waehrend des Laufs.
Am 2026-09-05 lagen um 22:23 zwei halbfertige Fremddateien darin -- eine Quelle des
Belegstellenriegels und `kern/test/aktion_probe.cpp` mit einer offenen Klammer. Beide
gehoeren nicht zu Paket 0144, und beide machen jede Messung rot, die in diesem Moment
laeuft. Ein Nachweis, der das nicht abwartet, misst den fremden Lauf.

Geprueft wird mit einer Wegwerfkopie des Kerns, damit das Warten selbst nichts anfasst.
"""

import os
import pathlib
import shutil
import subprocess
import time

WURZEL = pathlib.Path(__file__).resolve().parents[2]
TMP = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "warte-0144"
VERSUCHE = 40
PAUSE = 60


def baum_gruen():
    if TMP.exists():
        shutil.rmtree(TMP)
    TMP.mkdir(parents=True)
    shutil.copytree(WURZEL / "kern", TMP / "kern", ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WURZEL / "werkzeugkette.cmake", TMP / "werkzeugkette.cmake")
    for befehl in (["cmake", "-S", str(TMP / "kern"), "-B", str(TMP / "bau"),
                    "-DFABRIK_SANITIZER=OFF"],
                   ["cmake", "--build", str(TMP / "bau"), "-j", "4"]):
        ergebnis = subprocess.run(befehl, capture_output=True, text=True)
        if ergebnis.returncode != 0:
            fremd = [z for z in (ergebnis.stdout + ergebnis.stderr).splitlines()
                     if " error" in z or "Error " in z]
            return False, fremd[:4]
    return True, []


for versuch in range(1, VERSUCHE + 1):
    gruen, meldungen = baum_gruen()
    stempel = time.strftime("%H:%M:%S")
    if gruen:
        print("{0} Versuch {1}: Baum uebersetzt -- Nachweis laeuft".format(stempel, versuch),
              flush=True)
        raise SystemExit(subprocess.run(
            ["python3", str(pathlib.Path(__file__).resolve().parent / "nachweis.py")]).returncode)
    print("{0} Versuch {1}: Baum noch rot -- {2}".format(stempel, versuch, meldungen),
          flush=True)
    time.sleep(PAUSE)

print("Der Baum blieb ueber {0} Versuche rot.".format(VERSUCHE))
raise SystemExit(2)
