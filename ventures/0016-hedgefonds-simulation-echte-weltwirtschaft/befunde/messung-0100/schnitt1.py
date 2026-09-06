"""Vergleicht die sechs Trefferkontexte von schnitt_1 alt gegen neu zeichengleich.

Aufruf: python3 schnitt1.py <blob> <pfad>
Eine gleiche Trefferzahl aus anderen Stellen bliebe sonst unbemerkt.
"""

import re
import subprocess
import sys

MUSTER = re.compile(r"[=] [0-9]+\.[0-9]")


def treffer(text):
    return [z[:120] for z in text.split("\n") if MUSTER.search(z)]


blob, pfad = sys.argv[1], sys.argv[2]
alt = treffer(subprocess.run(["git", "cat-file", "blob", blob], capture_output=True,
                             check=True).stdout.decode())
neu = treffer(open(pfad, "rb").read().decode())
print("Treffer alt/neu:", len(alt), len(neu), "zeichengleich:", alt == neu)
for z in neu:
    print("  ", z)
