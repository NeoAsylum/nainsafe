#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 6: die vier Zahlen der Riegelmeldung nachzaehlen und
die uebergangenen Fundstellen als Menge vergleichen, nicht als Zahl.

Der Bauagent behauptet: Rueckgabe 0, 40 Zitate gefunden, 40 aufgeloest,
55 Fundstellen uebergangen, davon 40 in reihen.toml, viermal dieselbe Zahl wie
vorher. Zahlen koennen gleich sein und trotzdem andere Mengen meinen -- deshalb
zusaetzlich der Textvergleich ohne Zeilennummern.

Aufruf: python3 riegel_vergleich.py   (setzt riegel.py voraus)
"""
import os
import re
import subprocess

WURZEL = "/home/adria/fabrik"
V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
S = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.join(WURZEL, V, "werkzeuge/belegstellen/bau/belegstellen_riegel")
BASIS = os.path.join(os.environ.get("TMPDIR", "/tmp/claude"), "pruefung-0170")

FUND = re.compile(r"^\s{6}(\S+?):(\d+)\s+\((.*)\)\s*$")


def lauf(stand):
    w = os.path.join(BASIS, stand)
    p = subprocess.run([EXE, os.path.join(w, V), os.path.join(w, S)],
                       capture_output=True)
    return p.returncode, p.stdout.decode()


for stand in ("vorher", "nachher"):
    rc, aus = lauf(stand)
    funde = [FUND.match(z) for z in aus.splitlines()]
    funde = [m for m in funde if m]
    in_datei = [m for m in funde if m.group(1) == "daten/reihen.toml"]
    zitate = re.search(r"jedes der\s+(\d+) Abschnittszitate", aus.replace("\n", " "))
    ohne = re.search(r"Davon ohne Anfuehrung: (\d+) Zitate", aus)
    print("== %s ==" % stand)
    print("  Rueckgabe            :", rc)
    print("  Abschnittszitate     :", zitate.group(1) if zitate else "?")
    print("  ohne Anfuehrung      :", ohne.group(1) if ohne else "?")
    print("  uebergangen gesamt   :", len(funde))
    print("  davon in reihen.toml :", len(in_datei))
    globals()["f_" + stand] = [(m.group(1), m.group(3),
                                z) for m, z in zip(funde, [None] * len(funde))]
    globals()["roh_" + stand] = aus

# Mengenvergleich: Datei + Grund + gesuchter Text, ohne Zeilennummer
def ohne_nummern(aus):
    zeilen = []
    for z in aus.splitlines():
        m = FUND.match(z)
        zeilen.append(("FUND", m.group(1), m.group(3)) if m else ("TXT", z))
    return zeilen


a, b = ohne_nummern(roh_vorher), ohne_nummern(roh_nachher)
print()
print("Ausgabe ohne Zeilennummern gleich:", a == b)
if a != b:
    for x, y in zip(a, b):
        if x != y:
            print("  alt:", x)
            print("  neu:", y)
print("Ausgabe mit Zeilennummern gleich :", roh_vorher == roh_nachher)

diff = [(x, y) for x, y in zip(roh_vorher.splitlines(), roh_nachher.splitlines())
        if x != y]
print("abweichende Ausgabezeilen:", len(diff))
for x, y in diff[:3]:
    print("   -", x.strip()[:110])
    print("   +", y.strip()[:110])
