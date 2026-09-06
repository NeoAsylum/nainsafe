import subprocess, re, tomllib, sys

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"


def blob(rev):
    out = subprocess.run(["git", "show", rev + ":" + V + "/rueckstand.md"],
                         capture_output=True)
    return out.stdout.decode("utf-8").splitlines()


t73 = blob("73bbab8~1")
tf2 = blob("f26f20b~1")

orig = {
    "P4": " ".join(t73[204:207]),
    "P6": " ".join(t73[212:215]),
    "P9": " ".join(tf2[143:147]),
}

STERN = chr(42) + chr(42)
TICK = chr(96)


def norm(s, drop_tick=True):
    s = s.replace(STERN, "")
    s = re.sub(r"^\d+\.\s*", "", s)
    if drop_tick:
        s = s.replace(TICK, "")
    s = re.sub(r"\s+", " ", s).strip()
    return s


print("### ORIGINALE, normalisiert (Fett, Gliederungsnummer, Backticks entfernt)")
for k in sorted(orig):
    n = norm(orig[k])
    print(k, "len=", len(n))
    print("   ", n)
    codes = sorted(set(hex(ord(c)) for c in orig[k] if ord(c) > 0x2000))
    print("   sonderzeichen:", codes)
print()

# --- Zielstellen im Arbeitsbaum ---
p_toml = V + "/daten/reihen.toml"
p_md = V + "/daten/einheitenbefund-pwt-baci.md"

d = tomllib.load(open(p_toml, "rb"))
stellen = {
    "reihe.1.offen.0": d["reihe"][1]["offen"][0],
    "reihe.1.umrechnung.1.beleg": d["reihe"][1]["umrechnung"][1]["beleg"],
    "widerspruch.4.entscheidet": d["widerspruch"][4]["entscheidet"],
}

roh_toml = open(p_toml, encoding="utf-8").read()
roh_md = open(p_md, encoding="utf-8").read()

# Kopfkommentar: Zeilen, die mit '#' beginnen, ab Leseregel 1
komm = []
for line in roh_toml.splitlines():
    if line.startswith("#"):
        komm.append(line.lstrip("#").strip())
    elif komm and len(komm) > 5:
        break
stellen["kopfkommentar"] = " ".join(komm)

stellen["einheitenbefund"] = re.sub(r"\s+", " ", roh_md)

print("### ENTHALTENSEIN je Stelle")
zuordnung = {
    "kopfkommentar": "P9",
    "reihe.1.offen.0": "P9",
    "reihe.1.umrechnung.1.beleg": "P9",
    "widerspruch.4.entscheidet": "P6",
    "einheitenbefund": "P4",
}
for stelle, pkt in zuordnung.items():
    hay = norm(stellen[stelle])
    for variante, txt in (("ohne backticks", norm(orig[pkt])),
                          ("mit backticks", norm(orig[pkt], drop_tick=False))):
        print(stelle, "<-", pkt, variante, ":", hay.count(txt))
print()

print("### Gesamtzahl der Vorkommen in den ganzen Dateien")
ht = norm(roh_toml)
hm = norm(roh_md)
for pkt in sorted(orig):
    print(pkt, "reihen.toml:", ht.count(norm(orig[pkt])),
          " einheitenbefund:", hm.count(norm(orig[pkt])))
