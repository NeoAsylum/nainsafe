# Die sechzehn Muster der sieben Schnitte aus `pruefweg`, einzeln nachgezaehlt.
# Kein Eingriff, nur Zaehlung. Aufruf ohne Argument misst den Arbeitsbaum; mit
# einer Blobkennung misst es zusaetzlich denselben Satz gegen jenen Blob und
# stellt beide Spalten nebeneinander.

import re
import subprocess
import sys

PFAD = ("/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
        "/daten/reihen.toml")

MUSTER = [
    ("schnitt_1  dezimalpunkt", r"[=] [0-9]+\.[0-9]", "zeilen"),
    ("schnitt_2  ''' zeilen", r"[']{3}", "zeilen"),
    ("schnitt_2  ''' vorkommen", r"[']{3}", "vorkommen"),
    ("schnitt_2  ''' am rand", r"^[']{3}|[']{3}$", "zeilen"),
    ("schnitt_3  tabellenkoepfe", r"^\[\[", "zeilen"),
    ("schnitt_4  exogen_ab", r"^exogen_ab = ", "zeilen"),
    ("schnitt_4  verkettet_ab", r"^verkettet_ab = ", "zeilen"),
    ("schnitt_4  lizenzurteil", r"^lizenzurteil = ", "zeilen"),
    ("schnitt_4  sammelmuster",
     r"^(lizenzurteil|bezeichnung|dimension|modelleinheit|quelle_tabelle"
     r"|rolle_tabelle|verdacht_tabelle|quelle_eingebettet) = ", "zeilen"),
    ("schnitt_4  t37_klasse", r"^t37_klasse = ", "zeilen"),
    ("schnitt_4  nr", r"^nr = ", "zeilen"),
    ("schnitt_5  sollreihen mit =", r"^sollreihen = ", "zeilen"),
    ("schnitt_5  sollreihen ohne =", r"^sollreihen", "zeilen"),
    ("schnitt_7  wortlaut", r"^wortlaut = ", "zeilen"),
    ("schnitt_7  wortlaut_form", r"^wortlaut_form", "zeilen"),
]

TYPEN = ["reihe", "widerspruch", "reihe.umrechnung", "reihe.lizenzbeleg",
         "reihe.deckung", "reihe.konkordanz", "reihe.bruch"]


def zaehle(text):
    zeilen = text.splitlines()
    aus = {}
    for name, muster, art in MUSTER:
        r = re.compile(muster)
        if art == "zeilen":
            aus[name] = sum(1 for z in zeilen if r.search(z))
        else:
            aus[name] = sum(len(r.findall(z)) for z in zeilen)
    for t in TYPEN:
        aus["schnitt_3  [[" + t + "]]"] = sum(1 for z in zeilen
                                              if z.startswith("[[" + t + "]]"))
    aus["schnitt_1  trefferkontexte"] = "\n".join(
        z.strip()[:60] for z in zeilen if re.search(MUSTER[0][1], z))
    return aus


neu = zaehle(open(PFAD, encoding="utf-8").read())
alt = None
if len(sys.argv) > 1:
    roh = subprocess.run(["git", "-C", "/home/adria/fabrik", "cat-file", "blob",
                          sys.argv[1]], capture_output=True, check=True).stdout
    alt = zaehle(roh.decode("utf-8"))

for schluessel in neu:
    if schluessel == "schnitt_1  trefferkontexte":
        continue
    zeile = "  %-32s neu %4s" % (schluessel, neu[schluessel])
    if alt is not None:
        gleich = "gleich" if alt[schluessel] == neu[schluessel] else "ABWEICHUNG"
        zeile += "   alt %4s   %s" % (alt[schluessel], gleich)
    print(zeile)

if alt is not None:
    k = "schnitt_1  trefferkontexte"
    print("  schnitt_1, sechs Trefferkontexte alt gegen neu zeichengleich:",
          alt[k] == neu[k])
