#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 5: der Belegstellenriegel vor und nach dem Eingriff,
je an einem ausgepackten Stand ausserhalb des Arbeitsbaums, und zweimal je Stand
(Wiederholbarkeit, Ausgaben bitgleich).

Aufruf: python3 riegel.py
"""
import os
import shutil
import subprocess
import sys
import tarfile

WURZEL = "/home/adria/fabrik"
V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
S = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.join(WURZEL, V, "werkzeuge/belegstellen/bau/belegstellen_riegel")
TMP = os.environ.get("TMPDIR", "/tmp/claude")
BASIS = os.path.join(TMP, "pruefung-0170")


def auspacken(commit, ziel):
    os.makedirs(ziel, exist_ok=True)
    for pfad in (V, S):
        tar = os.path.join(ziel, "x.tar")
        with open(tar, "wb") as f:
            subprocess.run(["git", "archive", commit, pfad], cwd=WURZEL,
                           stdout=f, check=True)
        with tarfile.open(tar) as t:
            t.extractall(ziel)
        os.remove(tar)
    return ziel


def lauf(wurzel):
    p = subprocess.run([EXE, os.path.join(wurzel, V), os.path.join(wurzel, S)],
                       capture_output=True)
    return p.returncode, p.stdout.decode(), p.stderr.decode()


ergebnis = {}
for name, commit in (("vorher", "885449e~1"), ("nachher", "885449e")):
    ziel = os.path.join(BASIS, name)
    if os.path.isdir(ziel):
        shutil.rmtree(ziel)
    auspacken(commit, ziel)
    a = lauf(ziel)
    b = lauf(ziel)
    print("== %s (%s) ==" % (name, commit))
    print("  Rueckgabe:", a[0], "| zweiter Lauf bitgleich:",
          a[1] == b[1] and a[2] == b[2] and a[0] == b[0])
    for zeile in (a[1] + a[2]).splitlines():
        print("   ", zeile[:160])
    ergebnis[name] = a

print()
print("stdout vorher == nachher:", ergebnis["vorher"][1] == ergebnis["nachher"][1])
print("stderr vorher == nachher:", ergebnis["vorher"][2] == ergebnis["nachher"][2])
sys.stdout.flush()
