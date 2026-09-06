"""Blattwertbilanz zweier Fassungen von reihen.toml.

Aufruf: python3 messen.py <blob-des-bezugsstands> <pfad-der-vorliegenden-fassung>
Eigenstaendig geschrieben fuer die Pruefung des Pakets 0100; misst dasselbe,
was pruefweg.toml_geprueft behauptet, ohne das Skript des Bauagenten zu benutzen.
"""

import subprocess
import sys
import tomllib


def flach(o, pre=()):
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, pre + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, pre + (str(i),))
    else:
        yield pre, o


blob, pfad = sys.argv[1], sys.argv[2]
roh_alt = subprocess.run(["git", "cat-file", "blob", blob], capture_output=True, check=True).stdout
roh_neu = open(pfad, "rb").read()
alt = tomllib.loads(roh_alt.decode())
neu = tomllib.loads(roh_neu.decode())
A, B = dict(flach(alt)), dict(flach(neu))

print("Blattwerte alt/neu:", len(A), len(B))
print("neu :", sorted(".".join(k) for k in B.keys() - A.keys()))
print("weg :", sorted(".".join(k) for k in A.keys() - B.keys()))
geaendert = sorted(".".join(k) for k in A.keys() & B.keys() if A[k] != B[k])
print("geaendert (%d): %s" % (len(geaendert), geaendert))

print("reihe:", len(neu["reihe"]), "widerspruch:", len(neu["widerspruch"]), "wurzel:", sorted(neu.keys()))
print("sollreihen-summe:", sum(r["sollreihen"] for r in neu["reihe"]),
      "zaehlung.sollreihen_gesamt:", neu["zaehlung"]["sollreihen_gesamt"])
print("zweimal eingelesen gleich:", tomllib.loads(roh_neu.decode()) == neu)
print("zeilen alt/neu:", roh_alt.decode().count("\n"), roh_neu.decode().count("\n"))
