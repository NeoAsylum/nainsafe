"""Raeumt weg, was `messen.py` angelegt hat -- und nur das.

Der erste Anlauf am 2026-09-06 legte zwei Kopien mit je 126.339 leeren Dateien in
den tmpfs; auf tmpfs kostet auch eine leere Datei eine Seite, und der Dateibaum
lief voll. Seither legt `messen.py` nur **eine** Kopie dorthin. Dieses Skript ist
der Griff fuer den Fall, dass ein Lauf mittendrin abbricht.

Geloescht werden ausschliesslich die vier Namen unten. Sie liegen ausserhalb des
Repositoriums oder tragen einen Punkt am Anfang; keiner von ihnen ist Bestand.
"""
import os
import shutil

TMP = os.environ.get("TMPDIR") or "/tmp"
NAMEN = [
    os.path.join(TMP, "messung-0130"),
    os.path.join(TMP, "messung-0130-tmpfs-auf"),
    os.path.join(TMP, "messung-0130-tmpfs-ab"),
    "/home/adria/fabrik/.messung-0130-ext4",
    "/home/adria/fabrik/.messung-0130-ext4-ab",
]

DATEIEN = ["/home/adria/fabrik/.messung-0130-lauf.txt"]

for name in NAMEN:
    if os.path.isdir(name):
        shutil.rmtree(name)
for name in DATEIEN:
    if os.path.isfile(name):
        os.remove(name)
