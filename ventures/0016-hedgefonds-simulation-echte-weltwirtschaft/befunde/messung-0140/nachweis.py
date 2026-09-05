#!/usr/bin/env python3
"""Nachweis zu Paket 0140 -- der Verlauf sammelt die Rundenketten.

Faehrt vier Baeume in einem Aufruf und endet mit einer Zahl:

  vorher/nachher  x  FABRIK_SANITIZER=ON/OFF

Der Baum *vorher* ist derselbe Arbeitsbaum ohne die drei Dateien dieses Pakets --
nicht ein Git-Stand: Ein Fremdlauf, der mitten im Lauf committet, verschiebt HEAD, die
Kopie nicht. Kopiert wird nur `kern/` und `werkzeugkette.cmake`, ohne den Bauordner;
`kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein.

Geprueft wird:

  1. Konfigurieren, Bauen und ctest je Code 0 -- in allen vier Baeumen.
  2. Die Zahl der ctest-Eintraege steigt von *vorher* nach *nachher* um genau eins,
     je Profil gegen denselben Baum und dasselbe Profil.
  3. Die Ausgabe der drei Proben, die den Zustand rechnen, ist zwischen *vorher* und
     *nachher* zeichengleich -- darin stehen die Pruefsummen der Partie.
"""

import os
import pathlib
import shutil
import subprocess

WURZEL = pathlib.Path(__file__).resolve().parents[2]
NEUE_DATEIEN = [
    "kern/include/kern/verlauf.hpp",
    "kern/src/verlauf.cpp",
    "kern/test/verlauf_probe.cpp",
]
ZUSTANDSPROBEN = ["schritt_probe", "zustand_probe", "zustandsausgabe_probe"]
TMP = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0140"


def baum_anlegen(name, mit_neuen):
    """Legt einen Wegwerfbaum unter TMPDIR an -- nur `kern/` und die Werkzeugkette."""
    ziel = TMP / name
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.mkdir(parents=True)
    shutil.copytree(WURZEL / "kern", ziel / "kern",
                    ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WURZEL / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")
    if not mit_neuen:
        for datei in NEUE_DATEIEN:
            (ziel / datei).unlink()
    return ziel


def lauf(befehl):
    ergebnis = subprocess.run(befehl, capture_output=True, text=True)
    return ergebnis.returncode, ergebnis.stdout + ergebnis.stderr


def ctest_eintraege(bau):
    code, aus = lauf(["ctest", "--test-dir", str(bau), "-N"])
    zahl = sum(1 for zeile in aus.splitlines() if zeile.strip().startswith("Test  #")
               or zeile.strip().startswith("Test #"))
    return code, zahl, aus

