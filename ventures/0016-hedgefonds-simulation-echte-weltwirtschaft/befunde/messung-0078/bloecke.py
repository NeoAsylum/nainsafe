#!/usr/bin/env python3
# Paket 0078, Ruecklauf 1 -- listet alle Bloecke [[reihe.umrechnung]] mit ihren
# Schluesselmengen auf. Grundlage fuer den Satz in pruefweg.zaehlregel_umrechnung.
# Aufruf: python3 befunde/messung-0078/bloecke.py <datei.toml>
import sys, tomllib

pfad = sys.argv[1]
with open(pfad, "rb") as f:
    d = tomllib.load(f)

n = 0
for r in d["reihe"]:
    for u in r.get("umrechnung", []):
        n += 1
        keys = sorted(u.keys())
        print("Reihe %-3s Schritt %-3s art=%-18s faktor=%-8s | %s" % (
            r["nr"], u.get("schritt", "-"), repr(u.get("art")),
            repr(u.get("faktor", None)),
            ",".join(k for k in keys if k not in
                     ("schritt", "art", "faktor", "begruendung", "beleg", "status"))))
print("Bloecke gesamt:", n)
