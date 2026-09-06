#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 1: die drei geaenderten Blattwerte im Wortlaut,
dazu die beiden Felder, mit denen die Berichtigung uebereinstimmen muss.
Grosse Felder gehen in Dateien, kleine auf die Ausgabe.

Aufruf: python3 felder.py
"""
import os
import subprocess
import textwrap
import tomllib

WURZEL = "/home/adria/fabrik"
PFAD = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"
HIER = os.path.dirname(os.path.abspath(__file__))
ALT = "885449e~1"
NEU = "885449e"


def laden(commit):
    roh = subprocess.run(["git", "show", commit + ":" + PFAD],
                         cwd=WURZEL, capture_output=True, check=True).stdout
    return roh, tomllib.loads(roh.decode("utf-8"))


def ablegen(name, text):
    with open(os.path.join(HIER, name), "w", encoding="utf-8") as f:
        f.write(textwrap.fill(text, 100, replace_whitespace=False) + "\n")
    print("  -> %s (%d Zeichen)" % (name, len(text)))


alt_roh, alt = laden(ALT)
neu_roh, neu = laden(NEU)

for name, d in (("alt", alt), ("neu", neu)):
    ablegen("vollstaendigkeit-%s.txt" % name, d["namensnennung"]["vollstaendigkeit"])
    ablegen("tomlgeprueft-%s.txt" % name, d["pruefweg"]["toml_geprueft"])

ablegen("zaehlregel_lizenz-neu.txt", neu["pruefweg"]["zaehlregel_lizenz"])
ablegen("schnitt_7-neu.txt", neu["pruefweg"]["schnitt_7"])

print()
print("zaehlregel_lizenz alt==neu:",
      alt["pruefweg"]["zaehlregel_lizenz"] == neu["pruefweg"]["zaehlregel_lizenz"])
print("schnitt_7 alt==neu:",
      alt["pruefweg"]["schnitt_7"] == neu["pruefweg"]["schnitt_7"])
print("vollstaendigkeit alt==neu:",
      alt["namensnennung"]["vollstaendigkeit"] == neu["namensnennung"]["vollstaendigkeit"])
print("toml_geprueft alt==neu:",
      alt["pruefweg"]["toml_geprueft"] == neu["pruefweg"]["toml_geprueft"])
