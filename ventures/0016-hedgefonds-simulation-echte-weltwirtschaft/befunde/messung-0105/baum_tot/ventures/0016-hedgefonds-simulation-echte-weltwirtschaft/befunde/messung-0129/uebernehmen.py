"""Kopiert die Wegwerfstuecke des Nachweises aus dem Arbeitsordner unter `bau/` hierher.

`bau/` ist von der Versionsverwaltung ausgenommen; ohne diesen Schritt waere der
Nachweis nach dem naechsten Aufraeumen nicht mehr nachzufahren.

Aufruf: uebernehmen.py <arbeitsordner> <zielordner>
"""
import os, shutil, sys

ARBEIT, ZIEL = sys.argv[1], sys.argv[2]

STUECKE = [
    ("entwurf.py", "entwurf.py"),
    ("altbaum.py", "altbaum.py"),
    ("vorstand.py", "vorstand.py"),
    ("mutant.py", "mutant.py"),
    ("nachweis/CMakeLists.txt", "nachweis-CMakeLists.txt"),
]

for quelle, name in STUECKE:
    q = os.path.join(ARBEIT, quelle)
    if not os.path.isfile(q):
        raise SystemExit("fehlt: " + q)
    shutil.copy2(q, os.path.join(ZIEL, name))
    print("uebernommen:", name)
