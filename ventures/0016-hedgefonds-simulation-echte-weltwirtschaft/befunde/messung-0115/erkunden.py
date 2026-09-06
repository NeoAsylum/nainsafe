#!/usr/bin/env python3
"""Erkundungslauf zu Paket 0115 -- baut Mutanten und druckt ihre drei Zahlen.

Kein Riegel, sondern das Werkzeug, mit dem die Zahlen fuer den Kopfkommentar
ueberhaupt erst entstehen. Gebaut wird in $TMPDIR, der Quellbaum wird nicht
angefasst.
"""
import os
import re
import subprocess
import sys

W = ("/home/adria/fabrik/ventures/"
     "0016-hedgefonds-simulation-echte-weltwirtschaft")
MUTIEREN = W + "/bau/kp0086-mutieren.py"
TMP = os.environ.get("TMPDIR", "/tmp") + "/k0115"

# Der Filter aus dem Rumpf von 0115: er nimmt jedem Selbsttest die Abbruch-
# wirkung, nicht die Meldung. Ohne ihn bricht ein Mutant, der eine Falltabelle
# reissen laesst, mit Code 2 ab, ehe der Bestand gelesen ist.
ZAEHLZEILE = "            ++falsch;\n"

SCHALTER = ["-fwrapv", "-O1", "-std=c++20", "-Wno-everything"]

ZAHLEN = re.compile(
    r"(\d+) Zitate der geprueften Form gefunden, (\d+) davon aufgeloest "
    r"\(Untergrenze \d+\), (\d+) Fundstellen uebergangen")


def quelle(art):
    if art == "beide-unveraendert":
        return open(W + "/werkzeuge/belegstellen/belegstellen_riegel.cpp",
                    encoding="utf-8").read()
    return subprocess.run([sys.executable, MUTIEREN, art], check=True,
                          capture_output=True, text=True).stdout


def bauen(art, entschaerfen):
    text = quelle(art)
    if entschaerfen:
        n = text.count(ZAEHLZEILE)
        assert n > 0, "keine Zaehlzeile gefunden -- der Filter greift nicht"
        text = text.replace(ZAEHLZEILE, "")
    pfad = TMP + "/riegel_" + art.replace("-", "_")
    if entschaerfen:
        pfad += "_frei"
    p = subprocess.run(["/usr/bin/c++", "-x", "c++", "-", "-fwrapv", "-O1",
                        "-std=c++20", "-o", pfad],
                       input=text, text=True, capture_output=True)
    if p.returncode != 0:
        print(p.stderr[-3000:])
        raise SystemExit("Bau von " + art + " fehlgeschlagen")
    return pfad


def laufen(pfad):
    p = subprocess.run([pfad, W], capture_output=True, text=True)
    return p.returncode, p.stdout + p.stderr


def main():
    os.makedirs(TMP, exist_ok=True)
    arten = sys.argv[1:] or ["beide-unveraendert"]
    for art in arten:
        pfad = bauen(art, True)
        code, aus = laufen(pfad)
        t = ZAHLEN.search(aus)
        print("=== %-28s code=%d  Zitate=%s aufgeloest=%s uebergangen=%s"
              % (art, code, t.group(1) if t else "?",
                 t.group(2) if t else "?", t.group(3) if t else "?"))
        with open(TMP + "/aus_" + art.replace("-", "_") + ".txt", "w",
                  encoding="utf-8") as f:
            f.write(aus)


main()
