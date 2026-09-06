"""Inhaltliche Gegenproben zu den Behauptungen der Felder namensnennung.*

Aufruf: python3 inhalt.py <pfad-der-vorliegenden-fassung>
"""

import sys
import tomllib

d = tomllib.load(open(sys.argv[1], "rb"))
n = d["namensnennung"]

listen = {k: v["gilt_fuer_reihen"] for k, v in n.items() if isinstance(v, dict)}
union = sorted(set().union(*listen.values()))
print("listen:", listen)
print("vereinigung:", union)
print("fehlend von 1..19:", sorted(set(range(1, 20)) - set(union)))

for i, r in enumerate(d["reihe"], start=1):
    qt = r.get("quelle_tabelle", "")
    belege = r.get("lizenzbeleg", [])
    leer = all(not b.get("wortlaut") and not b.get("url") and not b.get("abrufdatum") for b in belege)
    if i in (14, 16, 17, 18, 19) or "keine" in qt.lower():
        print("Reihe %2d  quelle_tabelle=%r  lizenzbelege=%d leer=%s" % (i, qt, len(belege), leer))

r14 = d["reihe"][13]
print("\nReihe 14 bezeichnung:", r14["bezeichnung"])
print("umrechnungsbloecke:", len(r14["umrechnung"]))
print("umrechnung[1].art:", r14["umrechnung"][1]["art"])
print("quelle_deflator:", r14["umrechnung"][1]["quelle_deflator"])
r16 = d["reihe"][15]
print("\nReihe 16 bezeichnung:", r16["bezeichnung"])
print("quelle_tabelle:", r16["quelle_tabelle"])
print("quelle_eingebettet:", r16["quelle_eingebettet"])

zitate = [
    "Das ist Quelle Nr. 1 aus daten.md -- dieselbe Lizenz, dieselbe Zitierpflicht",
    "N stammt also aus zwei Reihen, und Reihe 1 ist eine davon",
]
h = n["weltbank"]["hinweis"]
for z in zitate:
    print("\nZitat im hinweis:", z in h,
          "| im quelle_deflator:", z in r14["umrechnung"][1]["quelle_deflator"],
          "| im quelle_eingebettet:", z in r16["quelle_eingebettet"])
