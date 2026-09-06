import re, subprocess, tomllib
W = "/home/adria/fabrik"
P = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml"
BT = chr(96)

def blob(c):
    return subprocess.run(["git", "show", c + ":" + P], cwd=W,
                          capture_output=True, text=True, check=True).stdout

def flach(x, p=""):
    aus = {}
    for k, v in x.items():
        if isinstance(v, dict):
            aus.update(flach(v, p + k + "."))
        else:
            aus[p + k] = v
    return aus

neu = blob("84c324b")
alt = blob("bfe7e13")
with open(W + "/" + P, encoding="utf-8") as f:
    baum = f.read()
print("Paketstand gleich Arbeitsbaum:", neu == baum)

d = tomllib.loads(neu)
fn = flach(d)
print("Blattschluessel laut tomllib:", len(fn))
namen = [k.rsplit(".", 1)[-1] for k in fn]
print("verschiedene Endnamen:", len(set(namen)))
print("Tabellen:", sorted(k for k, v in d.items() if isinstance(v, dict)))
print("Listen als Blatt:", sorted(k for k, v in fn.items() if isinstance(v, list)))

m = re.findall(BT + "([a-z_0-9]*)" + BT + "[*](?![*])", neu)
g = set(m)
print("Marke-Fundstellen:", len(m), "verschiedene Namen:", len(g))
print("markiert, aber kein Blattschluessel:", sorted(g - set(namen)))
rest = sorted(set(namen) - g)
print("woertlich belegt (Rest):", len(rest))
print("Summe:", len(g) + len(rest))
print("REST:", rest)

fa = flach(tomllib.loads(alt))
print("Blattwerte vorher:", len(fa), "nachher:", len(fn))
print("neu:", sorted(set(fn) - set(fa)))
print("weg:", sorted(set(fa) - set(fn)))
print("geaendert:", sorted(k for k in set(fa) & set(fn) if fa[k] != fn[k]))

def marken(t):
    aus = {}
    for z in t.splitlines():
        mm = re.match("^([a-z_0-9]+) *=.*?#(.*)$", z)
        if mm:
            aus[mm.group(1)] = mm.group(2).strip()
    return aus

ma, mn = marken(alt), marken(neu)
print("Zeilen mit Marke vorher:", len(ma), "nachher:", len(mn))
print("Marken-Unterschiede:", [(k, ma.get(k), mn.get(k))
      for k in sorted(set(ma) | set(mn)) if ma.get(k) != mn.get(k)])

z = [x for x in neu.splitlines() if "grep -o" in x]
print("Fundstellen des Ausdrucks:", len(z))
for x in z:
    print("  >", x.strip())
print("beide zeichengleich:", len(set(x.strip().lstrip("#").strip() for x in z)) == 1)
