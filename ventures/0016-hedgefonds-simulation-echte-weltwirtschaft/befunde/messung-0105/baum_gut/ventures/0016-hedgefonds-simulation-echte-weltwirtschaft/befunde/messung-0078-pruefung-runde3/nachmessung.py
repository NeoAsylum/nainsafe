#!/usr/bin/env python3
# Nachmessung des Daten-Pruefers zu Paket 0078, Runde 3, 2026-09-05.
# Unabhaengig vom Messskript des Bauagenten geschrieben; liest beide Fassungen
# selbst aus git und misst gegen den im Baubericht genannten Bezugsstand.
# Aufruf aus der Repowurzel: python3 <dieser Pfad>
#
# ALT = Blob der Fassung im Commit fabbf2f (Bezugsstand des Bauberichts)
# NEU = Blob im Arbeitsbaum, gleich 8a2c381 und f6731fe

import re
import subprocess
from collections import Counter
import tomllib

PFAD = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"
ALT = "cf492e2cd8ff865067173e1c63af0115d5f1cd5a"
NEU = "736610e78931b608652f38320c252d8fba8516be"


def blob(h):
    return subprocess.run(["git", "cat-file", "blob", h],
                          capture_output=True, check=True).stdout


def flach(o, pre=()):
    """Blattwerte als Pfadtupel; Listen elementweise, wie der Baubericht zaehlt."""
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, pre + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, pre + (str(i),))
    else:
        yield pre, o


ba, bn = blob(ALT), blob(NEU)
print("Arbeitsbaum zeichengleich mit NEU:", open(PFAD, "rb").read() == bn)

a = tomllib.loads(ba.decode())
n = tomllib.loads(bn.decode())

print("TOML zweimal eingelesen gleich:", tomllib.loads(bn.decode()) == n)
print("Wurzeltabellen:", sorted(n.keys()))
print("reihe:", len(n["reihe"]), "widerspruch:", len(n["widerspruch"]))
print("Summe sollreihen:", sum(r.get("sollreihen", 0) for r in n["reihe"]),
      "| zaehlung.sollreihen_gesamt:", n["zaehlung"]["sollreihen_gesamt"])

fa, fn = dict(flach(a)), dict(flach(n))
print("Blattwerte alt/neu:", len(fa), len(fn))
print("neu:", sorted(set(fn) - set(fa)), "| weg:", sorted(set(fa) - set(fn)))
versch = [k for k in fa if k in fn and fa[k] != fn[k]]
print("verschieden:", [".".join(k) for k in versch])

# --- Zeichengenaue Differenz des Gegenstandsfeldes -----------------------
va = a["pruefweg"]["zaehlregel_umrechnung"]
vn = n["pruefweg"]["zaehlregel_umrechnung"]
i = 0
while i < min(len(va), len(vn)) and va[i] == vn[i]:
    i += 1
j = 0
while j < min(len(va), len(vn)) - i and va[len(va) - 1 - j] == vn[len(vn) - 1 - j]:
    j += 1
print("Feldlaenge alt/neu:", len(va), len(vn))
print("entfernt:", repr(va[i:len(va) - j]))
print("eingefuegt:", repr(vn[i:len(vn) - j]))

# --- Alle 23 Umrechnungsbloecke, nach Rechenrolle gruppiert --------------
bloecke = []
for r in n["reihe"]:
    for s, b in enumerate(r.get("umrechnung", []), 1):
        bloecke.append((r["nr"], s, b))
print("Bloecke gesamt:", len(bloecke))
print("Reihen ohne Umrechnungsblock:",
      [r["nr"] for r in n["reihe"] if not r.get("umrechnung")])
ohne_faktor = [(nr, s) for nr, s, b in bloecke if "faktor" not in b]
ungemessen = [(nr, s) for nr, s, b in bloecke if b.get("art") == "ungemessen"]
nebenfeld = [(nr, s) for nr, s, b in bloecke
             if set(b) & {"rundungsstelle", "bezugsgroesse", "teiler"}]
basierung = [(nr, s) for nr, s, b in bloecke if b.get("art") == "basierung"]
g1 = set(nebenfeld) | set(basierung)
print("ohne faktor:", ohne_faktor)
print("art=ungemessen:", ungemessen)
print("Gruppe 1, faktor plus Nebenfeld oder basierung:", sorted(g1), len(g1))
print("Gruppe 2, gar kein faktor:", ohne_faktor, len(ohne_faktor))
print("Gruppe 3, Rest:", len(bloecke) - len(g1) - len(ohne_faktor))
print("Schnitt Gruppe1 mit Gruppe2 leer:", not g1 & set(ohne_faktor))
for nr, s, b in bloecke:
    print("   Reihe", nr, "S%d" % s, b.get("art"), b.get("faktor"), sorted(b))

# --- Die sechzehn Muster, einzeln ---------------------------------------
A, N = ba.decode().splitlines(), bn.decode().splitlines()
Q = chr(39) * 3
MUSTER = [
    ("schnitt_1", "[=] [0-9]+[.][0-9]"),
    ("schnitt_3", "^[[][[]"),
    ("schnitt_4 exogen_ab", "^exogen_ab = "),
    ("schnitt_4 verkettet_ab", "^verkettet_ab = "),
    ("schnitt_4 lizenzurteil", "^lizenzurteil = "),
    ("schnitt_4 Sammelmuster",
     "^(lizenzurteil|bezeichnung|dimension|modelleinheit|quelle_tabelle"
     "|rolle_tabelle|verdacht_tabelle|quelle_eingebettet) = "),
    ("schnitt_4 t37_klasse", "^t37_klasse = "),
    ("schnitt_4 nr", "^nr = "),
    ("schnitt_5 mit Gleichheitszeichen", "^sollreihen = "),
    ("schnitt_5 ohne", "^sollreihen"),
    ("schnitt_7 wortlaut", "^wortlaut = "),
    ("schnitt_7 wortlaut_form", "^wortlaut_form"),
]
for name, muster in MUSTER:
    rx = re.compile(muster)
    print(name, sum(1 for l in A if rx.search(l)), sum(1 for l in N if rx.search(l)))
print("schnitt_2 Zeilen", sum(1 for l in A if Q in l), sum(1 for l in N if Q in l))
print("schnitt_2 Vorkommen", sum(l.count(Q) for l in A), sum(l.count(Q) for l in N))
rand = re.compile("^" + Q + "|" + Q + "$")
print("schnitt_2 Randzeilen",
      sum(1 for l in A if rand.search(l)), sum(1 for l in N if rand.search(l)))

kopf = re.compile("^[[][[]([^]]+)[]][]]")
for name, L in (("Typaufzaehlung alt", A), ("Typaufzaehlung neu", N)):
    c = Counter(m.group(1) for m in (kopf.match(l) for l in L) if m)
    print(name, dict(c), "Summe", sum(c.values()))

r1 = re.compile("[=] [0-9]+[.][0-9]")
ka = [l for l in A if r1.search(l)]
kn = [l for l in N if r1.search(l)]
print("schnitt_1 Trefferkontexte zeichengleich:", ka == kn)
for l in kn:
    print("   ", l[:100])

# --- Bedingung 4 --------------------------------------------------------
wort = "Ausfuhr" + "preisindex"   # zusammengesetzt, damit dieses Skript nicht mitzaehlt
print("Bedingung 4, Wort alt/neu:", ba.decode().count(wort), bn.decode().count(wort))
