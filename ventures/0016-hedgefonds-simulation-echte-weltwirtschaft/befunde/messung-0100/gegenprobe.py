"""Gegenprobe zur neuen Regel in namensnennung.vollstaendigkeit, zweite Richtung:
Steht jede Reihe unter jeder Quelle, aus der ihre ausgelieferten Werte entstehen?

Zeigt je Reihe die Quelle, die zugeordneten Namensnennungen und alle Felder der
Umrechnungsbloecke, die eine fremde Bezugsgroesse nennen koennten.

Aufruf: python3 gegenprobe.py <pfad>
"""

import sys
import tomllib

d = tomllib.load(open(sys.argv[1], "rb"))
n = d["namensnennung"]
zuord = {}
for q, v in n.items():
    if isinstance(v, dict):
        for r in v["gilt_fuer_reihen"]:
            zuord.setdefault(r, []).append(q)

INTERESSANT = ("quelle_deflator", "bezugsgroesse", "teiler", "quelle_eingebettet",
               "rundungsstelle", "umrechnungskurs_dem_je_eur_mal_100000")

for i, r in enumerate(d["reihe"], start=1):
    print("=" * 70)
    print("Reihe %2d  %s" % (i, r["bezeichnung"][:60]))
    print("  quelle_tabelle : %s" % r.get("quelle_tabelle"))
    print("  namensnennung  : %s" % (zuord.get(i) or "-- keine --"))
    print("  quelle_eingeb. : %s" % r.get("quelle_eingebettet", "")[:300])
    for j, u in enumerate(r.get("umrechnung", []), start=1):
        print("  umrechnung %d: art=%s" % (j, u.get("art")))
        for k in INTERESSANT:
            if k in u:
                print("     %s = %s" % (k, str(u[k])[:300]))
