import subprocess, tomllib, sys

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"


def bytes_of(blob):
    return subprocess.run(["git", "cat-file", "blob", blob], capture_output=True).stdout


def blaetter(d, pfad=""):
    aus = {}
    if isinstance(d, dict):
        for k, v in d.items():
            aus.update(blaetter(v, pfad + ("." if pfad else "") + str(k)))
    elif isinstance(d, list):
        for i, v in enumerate(d):
            aus.update(blaetter(v, pfad + "." + str(i)))
    else:
        aus[pfad] = d
    return aus


VOR = "67b925e584277fd9e95a8e1686a27d7ce4009c95"
NACH = "d18ca197812364ac65dba58dd67a7851339ddfe7"
HEUTE = open(V + "/daten/reihen.toml", "rb").read()

roh = {"VOR": bytes_of(VOR), "NACH": bytes_of(NACH), "HEUTE": HEUTE}
bl = {}
for k, b in roh.items():
    d1 = tomllib.loads(b.decode("utf-8"))
    d2 = tomllib.loads(b.decode("utf-8"))
    bl[k] = blaetter(d1)
    print(k, "Zeilen:", len(b.decode("utf-8").splitlines()),
          " Blattwerte:", len(bl[k]),
          " zweimal gleich:", d1 == d2,
          " Reihen:", len(d1.get("reihe", [])),
          " Widersprueche:", len(d1.get("widerspruch", [])),
          " Wurzeltabellen:", len(d1))
    floats = [p for p, v in bl[k].items() if isinstance(v, float)]
    print("   Gleitkomma-Blattwerte:", floats)
    soll = [v for p, v in bl[k].items() if p.endswith("sollreihen")]
    print("   Summe sollreihen:", sum(x for x in soll if isinstance(x, int)),
          " zaehlung.sollreihen_gesamt:", d1.get("zaehlung", {}).get("sollreihen_gesamt"))

print()
v, n = bl["VOR"], bl["NACH"]
print("neu   :", sorted(set(n) - set(v)))
print("weg   :", sorted(set(v) - set(n)))
geaendert = sorted(k for k in set(v) & set(n) if v[k] != n[k])
print("geaendert:", geaendert)
