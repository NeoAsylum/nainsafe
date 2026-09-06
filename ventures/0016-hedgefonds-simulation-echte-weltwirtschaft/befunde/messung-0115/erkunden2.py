#!/usr/bin/env python3
"""Erkundung 2 zu Paket 0115 -- Mutanten **ohne** den entschaerfenden Filter.

Zeigt, welche Falltabelle einen Mutanten faengt. Der Filter aus dem Rumpf von
0115 nimmt den Selbsttests die Abbruchwirkung; wer wissen will, ob eine Regel
ueberhaupt noch gemessen wird, muss ihn weglassen.
"""
import os
import re
import subprocess
import sys

W = ("/home/adria/fabrik/ventures/"
     "0016-hedgefonds-simulation-echte-weltwirtschaft")
MUTIEREN = W + "/bau/kp0086-mutieren.py"
TMP = os.environ.get("TMPDIR", "/tmp") + "/k0115"

ZAHLEN = re.compile(
    r"(\d+) Zitate der geprueften Form gefunden, (\d+) davon aufgeloest "
    r"\(Untergrenze \d+\), (\d+) Fundstellen uebergangen")


def main():
    os.makedirs(TMP, exist_ok=True)
    for art in sys.argv[1:]:
        text = subprocess.run([sys.executable, MUTIEREN, art], check=True,
                              capture_output=True, text=True).stdout
        pfad = TMP + "/roh_" + art.replace("-", "_")
        p = subprocess.run(["/usr/bin/c++", "-x", "c++", "-", "-fwrapv", "-O1",
                            "-std=c++20", "-o", pfad],
                           input=text, text=True, capture_output=True)
        if p.returncode != 0:
            print(p.stderr[-2000:])
            raise SystemExit("Bau von " + art + " fehlgeschlagen")
        r = subprocess.run([pfad, W], capture_output=True, text=True)
        t = ZAHLEN.search(r.stdout)
        print("=== %-30s code=%d  %s" % (art, r.returncode,
              t.group(0) if t else "(Bestand nicht gelesen)"))
        for zeile in r.stderr.splitlines():
            if zeile.startswith("Selbsttest"):
                print("      " + zeile)


main()
