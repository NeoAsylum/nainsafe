#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 2: was der Bauagent an pruefweg.toml_geprueft
angehaengt oder geaendert hat, satzweise als Unterschied.

Aufruf: python3 geprueft_diff.py
"""
import difflib
import os
import re
import subprocess
import textwrap
import tomllib

WURZEL = "/home/adria/fabrik"
PFAD = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"
HIER = os.path.dirname(os.path.abspath(__file__))


def feld(commit, tab, key):
    roh = subprocess.run(["git", "show", commit + ":" + PFAD],
                         cwd=WURZEL, capture_output=True, check=True).stdout
    return tomllib.loads(roh.decode("utf-8"))[tab][key]


def saetze(t):
    return [s.strip() for s in re.split(r"(?<=[.:!?])\s+", t) if s.strip()]


a = saetze(feld("885449e~1", "pruefweg", "toml_geprueft"))
b = saetze(feld("885449e", "pruefweg", "toml_geprueft"))

zeilen = []
for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b).get_opcodes():
    if tag == "equal":
        continue
    for s in a[i1:i2]:
        zeilen.append("--- " + textwrap.fill(s, 96, subsequent_indent="    "))
    for s in b[j1:j2]:
        zeilen.append("+++ " + textwrap.fill(s, 96, subsequent_indent="    "))

with open(os.path.join(HIER, "tomlgeprueft-diff.txt"), "w", encoding="utf-8") as f:
    f.write("\n".join(zeilen) + "\n")
print("Saetze alt", len(a), "neu", len(b), "| Diffzeilen", len(zeilen))
