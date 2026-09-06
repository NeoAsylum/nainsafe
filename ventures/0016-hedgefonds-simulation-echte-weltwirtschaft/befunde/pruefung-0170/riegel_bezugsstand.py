#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 7: Der Nachtrag behauptet, der Riegellauf nach dem
Eingriff gebe dieselben Zahlen wie der davor, obwohl zwei fremde Commits
dazwischenliegen -- einer davon an technik.md, einer an einer Kernquelle.
Geprueft wird das am genannten Bezugsstand 45fc32f selbst.

Aufruf: python3 riegel_bezugsstand.py
"""
import os
import re
import shutil
import subprocess
import tarfile

WURZEL = "/home/adria/fabrik"
V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
S = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.join(WURZEL, V, "werkzeuge/belegstellen/bau/belegstellen_riegel")
BASIS = os.path.join(os.environ.get("TMPDIR", "/tmp/claude"), "pruefung-0170")

print("Vorfahren von 885449e:")
for n in range(4):
    k = subprocess.run(["git", "log", "--oneline", "-1", "885449e~%d" % n],
                       cwd=WURZEL, capture_output=True, check=True).stdout.decode().strip()
    print("  ~%d  %s" % (n, k[:100]))

ziel = os.path.join(BASIS, "bezugsstand")
if os.path.isdir(ziel):
    shutil.rmtree(ziel)
os.makedirs(ziel)
for pfad in (V, S):
    tar = os.path.join(ziel, "x.tar")
    with open(tar, "wb") as f:
        subprocess.run(["git", "archive", "45fc32f", pfad], cwd=WURZEL,
                       stdout=f, check=True)
    with tarfile.open(tar) as t:
        t.extractall(ziel)
    os.remove(tar)

ZAHLEN = [
    (r"(\d+) Bauquellen gelesen, (\d+) Zeilenverweise getroffen, davon (\d+)", "Bedingung 1"),
    (r"(\d+) Bauquellen und (\d+) Datendokumente gelesen, (\d+) Dateien im Zielbestand,"
     r" (\d+) Pfade", "Bedingung 2"),
    (r"Davon ohne Anfuehrung: (\d+) Zitate; weitere (\d+) Fundstellen", "ohne Anfuehrung"),
    (r"jedes der\s+(\d+) Abschnittszitate", "Abschnittszitate"),
]


def messe(name, wurzel):
    p = subprocess.run([EXE, os.path.join(wurzel, V), os.path.join(wurzel, S)],
                       capture_output=True)
    aus = p.stdout.decode()
    flach = " ".join(aus.split())
    print("== %s == Rueckgabe %d" % (name, p.returncode))
    for rx, bez in ZAHLEN:
        m = re.search(rx, flach)
        print("   %-18s %s" % (bez, m.groups() if m else "nicht gefunden"))
    funde = [z.strip() for z in aus.splitlines()
             if re.match(r"^\s+\S+\.(md|toml|cpp|txt):\d+\s+\(", z)]
    ohne_nr = sorted(re.sub(r":\d+\s", ":N ", z) for z in funde)
    print("   uebergangen gesamt %d | davon reihen.toml %d"
          % (len(funde), sum(1 for z in funde if z.startswith("daten/reihen.toml"))))
    return ohne_nr


a = messe("Bezugsstand 45fc32f", ziel)
b = messe("vorher 885449e~1", os.path.join(BASIS, "vorher"))
c = messe("nachher 885449e", os.path.join(BASIS, "nachher"))
print()
print("uebergangene Fundstellen (ohne Zeilennummer) Bezugsstand == vorher:", a == b)
print("uebergangene Fundstellen (ohne Zeilennummer) vorher == nachher    :", b == c)
