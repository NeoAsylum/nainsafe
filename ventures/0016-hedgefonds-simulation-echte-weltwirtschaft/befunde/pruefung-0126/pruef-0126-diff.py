import subprocess, re, tomllib, difflib

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
STERN = chr(42) + chr(42)
TICK = chr(96)


def blob(rev, pfad):
    out = subprocess.run(["git", "show", rev + ":" + V + "/" + pfad],
                         capture_output=True)
    return out.stdout.decode("utf-8")


def norm(s):
    s = s.replace(STERN, "").replace(TICK, "")
    s = re.sub(r"^\d+\.\s*", "", s)
    return re.sub(r"\s+", " ", s).strip()


tf2 = blob("f26f20b~1", "rueckstand.md").splitlines()
t73 = blob("73bbab8~1", "rueckstand.md").splitlines()
P9 = norm(" ".join(tf2[143:147]))
P6 = norm(" ".join(t73[212:215]))
P4 = norm(" ".join(t73[204:207]))

roh_toml = open(V + "/daten/reihen.toml", encoding="utf-8").read()
roh_md = open(V + "/daten/einheitenbefund-pwt-baci.md", encoding="utf-8").read()
d = tomllib.loads(roh_toml)

# Kopfkommentar-Block von Leseregel 1: Zeilen 33..56 (1-basiert) suchen wir am Text
zeilen = roh_toml.splitlines()
start = next(i for i, l in enumerate(zeilen) if l.startswith("# 1. "))
ende = next(i for i, l in enumerate(zeilen) if l.startswith("# 2. "))
kopf = " ".join(l.lstrip("#").strip() for l in zeilen[start:ende])

STELLEN = [
    ("kopfkommentar Leseregel 1", kopf, P9),
    ("reihe.1.offen.0", d["reihe"][1]["offen"][0], P9),
    ("reihe.1.umrechnung.1.beleg", d["reihe"][1]["umrechnung"][1]["beleg"], P9),
    ("widerspruch.4.entscheidet", d["widerspruch"][4]["entscheidet"], P6),
    ("einheitenbefund-pwt-baci.md", roh_md, P4),
]

# tolerante Fassung: alle doppelten Anfuehrungszeichen vereinheitlichen
def lose(s):
    for c in [chr(0x201e), chr(0x201c), chr(0x201d), chr(0x22)]:
        s = s.replace(c, "|")
    return s


for name, ist, soll in STELLEN:
    h = norm(ist)
    exakt = h.count(soll)
    tolerant = lose(h).count(lose(soll))
    print("---", name)
    print("   exakt:", exakt, "  anfuehrungszeichen-tolerant:", tolerant)
    if exakt == 0 and tolerant >= 1:
        # genaue Abweichung zeigen
        i = lose(h).find(lose(soll))
        kand = h[i:i + len(soll)]
        sm = difflib.SequenceMatcher(None, soll, kand, autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                continue
            print("   ", tag, "soll", repr(soll[i1:i2]),
                  [hex(ord(c)) for c in soll[i1:i2]],
                  "ist", repr(kand[j1:j2]), [hex(ord(c)) for c in kand[j1:j2]])
