"""Legt unter bau/kp0129/vorstand eine Kopie des Vorhabens ohne das Bauskript des
neuen Mitglieds an -- der unmittelbar vorhergehende Stand desselben Baums, gegen den
Bedingung 4 die Zahl der ctest-Eintraege zaehlt. Wegwerfskript, nicht ausgeliefert."""
import os, shutil, sys

QUELLE = sys.argv[1]
ZIEL = os.path.join(QUELLE, "bau", "kp0129", "vorstand")


def ohne_bau(ordner, eintraege):
    return [n for n in eintraege if n == "bau" or n.startswith(".")]


if os.path.isdir(ZIEL):
    shutil.rmtree(ZIEL)
os.makedirs(ZIEL)
for n in sorted(os.listdir(QUELLE)):
    if n == "bau" or n.startswith("."):
        continue
    q = os.path.join(QUELLE, n)
    z = os.path.join(ZIEL, n)
    if os.path.isdir(q):
        shutil.copytree(q, z, ignore=ohne_bau)
    else:
        shutil.copy2(q, z)

WEG = os.path.join(ZIEL, "werkzeuge", "bezeichner")
if not os.path.isdir(WEG):
    raise SystemExit("das neue Mitglied fehlt in der Kopie -- nichts zu entfernen")
shutil.rmtree(WEG)
print("vorstand angelegt, Mitglied 'werkzeuge/bezeichner' entfernt:", ZIEL)
