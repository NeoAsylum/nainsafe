import subprocess, tomllib, re

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
VOR_T = "67b925e584277fd9e95a8e1686a27d7ce4009c95"
NACH_T = "d18ca197812364ac65dba58dd67a7851339ddfe7"
VOR_M = "09b0e93e9757bb5308c3aec16fc41e682db31cc1"
NACH_M = "9017fde3f4cd9eedd1789910a4ebb3c372c1a5f0"


def txt(blob):
    return subprocess.run(["git", "cat-file", "blob", blob],
                          capture_output=True).stdout.decode("utf-8")


# --- sollreihen genau ---
d = tomllib.loads(txt(NACH_T))
s = [r.get("sollreihen") for r in d["reihe"] if "sollreihen" in r]
print("reihe.*.sollreihen:", s, "Summe:", sum(s),
      "gegen zaehlung.sollreihen_gesamt:", d["zaehlung"]["sollreihen_gesamt"])

# --- numstat ---
for a, b, name in ((VOR_T, NACH_T, "reihen.toml"), (VOR_M, NACH_M, "einheitenbefund")):
    r = subprocess.run(["git", "diff", "--numstat", a, b], capture_output=True).stdout.decode()
    va, vb = txt(a).splitlines(), txt(b).splitlines()
    print(name, "numstat:", r.strip(), " Zeilen:", len(va), "->", len(vb))

# --- Kommentarblock Leseregel 1: Umfang ---
for blob, name in ((VOR_T, "VOR"), (NACH_T, "NACH")):
    z = txt(blob).splitlines()
    start = next(i for i, l in enumerate(z) if l.startswith("# 1. "))
    ende = next(i for i, l in enumerate(z) if l.startswith("# 2. "))
    print(name, "Leseregel 1:", ende - start, "Zeilen")

# --- alle Kommentarzeilen ausser Leseregel 1 zeichengleich? ---
def komm(blob):
    z = txt(blob).splitlines()
    start = next(i for i, l in enumerate(z) if l.startswith("# 1. "))
    ende = next(i for i, l in enumerate(z) if l.startswith("# 2. "))
    return [l for i, l in enumerate(z) if l.lstrip().startswith("#") and not (start <= i < ende)]


kv, kn = komm(VOR_T), komm(NACH_T)
print("Kommentarzeilen ausserhalb Leseregel 1:", len(kv), "->", len(kn),
      " zeichengleich:", kv == kn)

# --- Nachtrag im Bilanzfeld ---
print()
print("=== pruefweg.toml_geprueft, Differenz ===")
dv = tomllib.loads(txt(VOR_T))["pruefweg"]["toml_geprueft"]
dn = tomllib.loads(txt(NACH_T))["pruefweg"]["toml_geprueft"]
i = 0
while i < min(len(dv), len(dn)) and dv[i] == dn[i]:
    i += 1
print("gemeinsamer Anfang bis", i)
print("NEU:", dn[i - 60:])
