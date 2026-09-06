"""Vergleicht die Kommentarzeilen zweier Fassungen zeichengleich.

Aufruf: python3 kommentare.py <blob> <pfad>
"""

import subprocess
import sys

blob, pfad = sys.argv[1], sys.argv[2]
alt = [z for z in subprocess.run(["git", "cat-file", "blob", blob], capture_output=True,
                                 check=True).stdout.decode().split("\n") if z.lstrip().startswith("#")]
neu = [z for z in open(pfad, "rb").read().decode().split("\n") if z.lstrip().startswith("#")]
print("Kommentarzeilen alt/neu:", len(alt), len(neu))
print("zeichengleich:", alt == neu)
if alt != neu:
    for a, b in zip(alt, neu):
        if a != b:
            print("ALT:", a)
            print("NEU:", b)
