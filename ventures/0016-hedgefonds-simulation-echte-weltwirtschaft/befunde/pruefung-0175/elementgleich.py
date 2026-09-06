import re, tomllib
BT = chr(96)
with open("parameter.toml", encoding="utf-8") as f:
    t = f.read()
with open("parameter.toml", "rb") as f:
    d = tomllib.load(f)

def flach(x, p=""):
    aus = {}
    for k, v in x.items():
        if isinstance(v, dict):
            aus.update(flach(v, p + k + "."))
        else:
            aus[p + k] = v
    return aus

blatt = list(flach(d))
print("Blattschluessel:", len(blatt))

# gemessene Marken, Abkuerzungen _2/_3 aufgeloest (Zeile 441)
m = sorted(set(re.findall(BT + "([a-z_0-9]*)" + BT + "[*](?![*])", t)))
aufgeloest = set()
for n in m:
    aufgeloest.add("aufsicht_schwelle" + n if n.startswith("_") else n)
print("Marken gemessen:", len(m), "| nach Aufloesung von _2/_3:", len(aufgeloest))

# die 26 aus BEFUNDE Punkt 1
vierzehn = ["stufenweite", "stufen_max", "ausstiegsabschlag", "zwangsabschlag",
            "aufschlag", "lobbykosten", "beteiligungsrabatt", "gegenlobby_satz",
            "druck_max", "regulierung_stufen", "schwelle_v", "schwelle_e",
            "startkapital", "regulierung_last"]
zwoelf = [k for k in blatt if k.startswith("instrument.")]
print("vierzehn:", len(vierzehn), "| zwoelf:", len(zwoelf),
      "| Summe woertlich:", len(vierzehn) + len(zwoelf))

oben = [k for k in blatt if "." not in k]
print("Blattschluessel oberste Ebene:", len(oben))
komplement = sorted(set(oben) - set(vierzehn))
print("Komplement der Vierzehn:", len(komplement))
print("elementgleich mit den gemessenen Marken:", set(komplement) == aufgeloest)
print("nur im Komplement:", sorted(set(komplement) - aufgeloest))
print("nur in den Marken:", sorted(aufgeloest - set(komplement)))
print("Rechnung:", len(aufgeloest), "+", len(vierzehn) + len(zwoelf), "=",
      len(aufgeloest) + len(vierzehn) + len(zwoelf), "| tomllib:", len(blatt))
