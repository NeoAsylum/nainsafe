#!/usr/bin/env python3
# Paket 0078, Ruecklauf 1 -- Selbstmessung nach Bedingung 5.
# Vergleicht den Bezugsblob (Argument 1) gegen den Arbeitsbaum (Argument 2):
# Parserlauf, Blattwertbilanz, die sechzehn Muster der sieben Schnitte,
# und bei schnitt_1 zusaetzlich die Trefferkontexte.
# Aufruf: python3 befunde/messung-0078/messung.py <blob-sha> <pfad>
import re, subprocess, sys, tomllib

blob, pfad = sys.argv[1], sys.argv[2]
alt_roh = subprocess.run(["git", "cat-file", "blob", blob],
                         cwd="/home/adria/fabrik", capture_output=True, check=True).stdout
with open(pfad, "rb") as f:
    neu_roh = f.read()

alt = tomllib.loads(alt_roh.decode("utf-8"))
neu = tomllib.loads(neu_roh.decode("utf-8"))
neu2 = tomllib.loads(neu_roh.decode("utf-8"))
print("PARSER: gueltiges TOML, zweimal gleich:", neu == neu2)
print("PARSER: reihe", len(neu["reihe"]), "widerspruch", len(neu["widerspruch"]),
      "wurzeltabellen", len(neu), sorted(neu))
print("PARSER: summe sollreihen", sum(r["sollreihen"] for r in neu["reihe"]),
      "== zaehlung.sollreihen_gesamt", neu["zaehlung"]["sollreihen_gesamt"])


def flach(o, p=()):
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, p + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, p + (str(i),))
    else:
        yield p, o


a = dict(flach(alt))
n = dict(flach(neu))
gemeinsam = set(a) & set(n)
versch = sorted(k for k in gemeinsam if a[k] != n[k])
print("\nBLATTWERTE: alt", len(a), "neu", len(n),
      "| neu hinzu", len(set(n) - set(a)), "| weg", len(set(a) - set(n)),
      "| gemeinsam", len(gemeinsam), "davon verschieden", len(versch))
for k in sorted(set(n) - set(a)):
    print("  + ", ".".join(k))
for k in sorted(set(a) - set(n)):
    print("  - ", ".".join(k))
for k in versch:
    print("  ~ ", ".".join(k))

MUSTER = [
    ("schnitt_1", r"[=] [0-9]+\.[0-9]", "zeilen"),
    ("schnitt_2 zeilen", r"[']{3}", "zeilen"),
    ("schnitt_2 vorkommen", r"[']{3}", "vorkommen"),
    ("schnitt_2 randzeilen", r"^[']{3}|[']{3}$", "zeilen"),
    ("schnitt_3", r"^\[\[", "zeilen"),
    ("schnitt_4 exogen_ab", r"^exogen_ab = ", "zeilen"),
    ("schnitt_4 verkettet_ab", r"^verkettet_ab = ", "zeilen"),
    ("schnitt_4 lizenzurteil", r"^lizenzurteil = ", "zeilen"),
    ("schnitt_4 sammel",
     r"^(lizenzurteil|bezeichnung|dimension|modelleinheit|quelle_tabelle"
     r"|rolle_tabelle|verdacht_tabelle|quelle_eingebettet) = ", "zeilen"),
    ("schnitt_4 t37_klasse", r"^t37_klasse = ", "zeilen"),
    ("schnitt_4 nr", r"^nr = ", "zeilen"),
    ("schnitt_5 mit gleich", r"^sollreihen = ", "zeilen"),
    ("schnitt_5 ohne gleich", r"^sollreihen", "zeilen"),
    ("schnitt_7 wortlaut", r"^wortlaut = ", "zeilen"),
    ("schnitt_7 wortlaut_form", r"^wortlaut_form", "zeilen"),
]


def zaehle(roh, muster, art):
    rx = re.compile(muster, re.M)
    text = roh.decode("utf-8")
    if art == "vorkommen":
        return len(rx.findall(text))
    return sum(1 for z in text.splitlines() if rx.search(z))


print("\nSCHNITTE (alt -> neu):")
for name, m, art in MUSTER:
    print("  %-26s %4d -> %4d" % (name, zaehle(alt_roh, m, art), zaehle(neu_roh, m, art)))

print("\nschnitt_3 nach Typ (neu):")
typen = {}
for z in neu_roh.decode("utf-8").splitlines():
    t = re.match(r"^\[\[([a-z._]+)\]\]", z)
    if t:
        typen[t.group(1)] = typen.get(t.group(1), 0) + 1
print(" ", typen, "summe", sum(typen.values()))

print("\nschnitt_1 Trefferkontexte alt gegen neu:")
rx = re.compile(r"[=] [0-9]+\.[0-9]")
ka = [z for z in alt_roh.decode("utf-8").splitlines() if rx.search(z)]
kn = [z for z in neu_roh.decode("utf-8").splitlines() if rx.search(z)]
print("  zeichengleich:", ka == kn, "| Anzahl", len(ka), len(kn))
for z in kn:
    print("   ", z[:90])

print("\nWort aus Bedingung 4 (Reihe 20):")
for name, roh in (("alt", alt_roh), ("neu", neu_roh)):
    print(" ", name, roh.decode("utf-8").count("Ausfuhrpreis" + "index"))
