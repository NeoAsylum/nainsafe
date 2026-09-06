import subprocess, tomllib

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"


def roh(blob):
    return subprocess.run(["git", "cat-file", "blob", blob], capture_output=True).stdout


# ---- 1. Byte-Nachweis des Anfuehrungszeichens ----
AUF = "„"
ZU = "“"
ASCII = '"'

quelle = subprocess.run(
    ["git", "show", "f26f20b~1:" + V + "/rueckstand.md"], capture_output=True).stdout
ist_toml = open(V + "/daten/reihen.toml", "rb").read()

for name, b in (("rueckstand.md@f26f20b~1", quelle), ("reihen.toml (Arbeitsbaum)", ist_toml)):
    print(name)
    print("   Bytes von 'Spalte " + AUF + "Rolle" + ZU + "':",
          b.count(("Spalte " + AUF + "Rolle" + ZU).encode()))
    print("   Bytes von 'Spalte " + AUF + "Rolle" + ASCII + "':",
          b.count(("Spalte " + AUF + "Rolle" + ASCII).encode()))

# technik.md als Vorgabe
t = open("specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md", "rb").read()
print("technik.md: mit " + ZU + ":", t.count((AUF + "Rolle" + ZU).encode()),
      " mit ASCII:", t.count((AUF + "Rolle" + ASCII).encode()))


# ---- 2. Folge des Nachtrags: Zaehlung der Blattwerte mit 'einheitenbefund-pwt-baci.md' ----
def flach(o, p=()):
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, p + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, p + (str(i),))
    else:
        yield p, o


NADEL = "einheitenbefund-pwt-baci.md"
for name, blob in (("VOR 67b925e", "67b925e584277fd9e95a8e1686a27d7ce4009c95"),
                   ("NACH 8903184 d18ca19", "d18ca197812364ac65dba58dd67a7851339ddfe7")):
    d = tomllib.loads(roh(blob).decode("utf-8"))
    treffer = [".".join(p) for p, v in flach(d) if isinstance(v, str) and NADEL in v]
    print(name, ": Blattwerte mit", NADEL, "=", len(treffer))
    for t2 in treffer:
        print("     ", t2)
