"""Die sechzehn Muster der sieben Schnitte, einzeln gezaehlt -- alt gegen neu.

Aufruf: python3 muster.py <blob-des-bezugsstands> <pfad-der-vorliegenden-fassung>
Die fuenfzehn Zaehlmuster stehen in pruefweg.schnitt_1 bis schnitt_7; als
sechzehntes zaehlt die Typaufzaehlung hinter schnitt_3. Zeilenweise gezaehlt wie
Grep, ausser wo "Vorkommen" dabeisteht -- das entspricht Grep mit -o.
"""

import re
import subprocess
import sys

ZEILE = [
    ("schnitt_1 dezimalpunkt", r"[=] [0-9]+\.[0-9]"),
    ("schnitt_2 zeilen", r"[']{3}"),
    ("schnitt_2 randzeilen", r"^[']{3}|[']{3}$"),
    ("schnitt_3 tabellenkoepfe", r"^\[\["),
    ("schnitt_4 exogen_ab", r"^exogen_ab = "),
    ("schnitt_4 verkettet_ab", r"^verkettet_ab = "),
    ("schnitt_4 lizenzurteil", r"^lizenzurteil = "),
    ("schnitt_4 sammelmuster",
     r"^(lizenzurteil|bezeichnung|dimension|modelleinheit|quelle_tabelle|rolle_tabelle|verdacht_tabelle|quelle_eingebettet) = "),
    ("schnitt_4 t37_klasse", r"^t37_klasse = "),
    ("schnitt_4 nr", r"^nr = "),
    ("schnitt_5 sollreihen mit =", r"^sollreihen = "),
    ("schnitt_5 sollreihen ohne =", r"^sollreihen"),
    ("schnitt_7 wortlaut", r"^wortlaut = "),
    ("schnitt_7 wortlaut_form", r"^wortlaut_form"),
]
VORKOMMEN = [("schnitt_2 vorkommen", r"[']{3}")]
TYPEN = ["reihe", "widerspruch", "reihe.umrechnung", "reihe.lizenzbeleg",
         "reihe.deckung", "reihe.konkordanz", "reihe.bruch"]


def messen(text):
    zeilen = text.split("\n")
    out = {}
    for name, muster in ZEILE:
        rx = re.compile(muster)
        out[name] = sum(1 for z in zeilen if rx.search(z))
    for name, muster in VORKOMMEN:
        out[name] = len(re.findall(muster, text))
    koepfe = [z for z in zeilen if z.startswith("[[")]
    typ = {t: sum(1 for z in koepfe if z.strip() == "[[%s]]" % t) for t in TYPEN}
    out["schnitt_3 typaufzaehlung"] = (typ, sum(typ.values()), len(koepfe))
    return out


blob, pfad = sys.argv[1], sys.argv[2]
alt = messen(subprocess.run(["git", "cat-file", "blob", blob], capture_output=True, check=True).stdout.decode())
neu = messen(open(pfad, "rb").read().decode())
for k in neu:
    gleich = "gleich" if alt[k] == neu[k] else "VERSCHIEDEN"
    print("%-30s alt=%s neu=%s  %s" % (k, alt[k], neu[k], gleich))
