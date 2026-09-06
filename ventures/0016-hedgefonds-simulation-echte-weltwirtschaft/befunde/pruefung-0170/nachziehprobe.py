#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 4: Haette ausser den drei geaenderten Blattwerten
noch etwas nachgezogen werden muessen?

Der neue Listeneintrag hebt die Laenge von datei.nachgezogen_durch von 14 auf 15.
Gesucht wird deshalb jede Stelle -- Blattwert wie Kommentarzeile --, die diese
Liste oder ihre Laenge beziffert, sowie jede Zahlwortnennung im Umfeld.
Zusaetzlich: der 16. Zaehler (Typaufzaehlung hinter schnitt_3) alt gegen neu,
den messung.py nur fuer die neue Fassung ausgibt.

Aufruf: python3 nachziehprobe.py
"""
import re
import subprocess
import tomllib

WURZEL = "/home/adria/fabrik"
PFAD = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"


def roh(commit):
    return subprocess.run(["git", "show", commit + ":" + PFAD],
                          cwd=WURZEL, capture_output=True, check=True).stdout.decode("utf-8")


alt_t, neu_t = roh("885449e~1"), roh("885449e")
alt, neu = tomllib.loads(alt_t), tomllib.loads(neu_t)

print("nachgezogen_durch: alt", len(alt["datei"]["nachgezogen_durch"]),
      "neu", len(neu["datei"]["nachgezogen_durch"]))
print("datei.stand:", alt["datei"]["stand"], "->", neu["datei"]["stand"])
print()
print("== paket_bedeutung (unveraendert:",
      alt["datei"]["paket_bedeutung"] == neu["datei"]["paket_bedeutung"], ") ==")
print(neu["datei"]["paket_bedeutung"])
print()

ZAHLWORT = (r"\b(null|ein|eine|einen|zwei|drei|vier|fuenf|sechs|sieben|acht|neun|zehn|elf|"
            r"zwoelf|dreizehn|vierzehn|fuenfzehn|sechzehn|siebzehn|achtzehn|neunzehn|zwanzig)\b")

print("== Zeilen, die nachgezogen_durch nennen ==")
for i, z in enumerate(neu_t.splitlines(), 1):
    if "nachgezogen_durch" in z:
        print("  %4d %s" % (i, z.strip()[:200]))

print()
print("== Blattwerte, die 'nachgezogen' nennen, mit Zahlwoertern darin ==")


def flach(o, p=()):
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, p + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, p + (str(i),))
    else:
        yield p, o


for k, v in flach(neu):
    if isinstance(v, str) and "nachgezogen_durch" in v:
        for s in re.split(r"(?<=[.;:])\s+", v):
            if "nachgezogen_durch" in s or re.search(r"vorangegangen", s):
                print("  %s: %s" % (".".join(k), s[:300]))

print()
print("== Kommentarzeilen mit Zahlwort, die eine Paketmenge zaehlen koennten ==")
for i, z in enumerate(neu_t.splitlines(), 1):
    if z.lstrip().startswith("#") and re.search(ZAHLWORT, z, re.I) and \
       re.search(r"Paket|Eintrag|Kennung", z):
        print("  %4d %s" % (i, z.strip()[:180]))

print()
print("== 16. Zaehler: schnitt_3 nach Typ, alt gegen neu ==")


def typen(t):
    d = {}
    for z in t.splitlines():
        m = re.match(r"^\[\[([a-z._]+)\]\]", z)
        if m:
            d[m.group(1)] = d.get(m.group(1), 0) + 1
    return d


ta, tn = typen(alt_t), typen(neu_t)
print("  alt", ta, "summe", sum(ta.values()))
print("  neu", tn, "summe", sum(tn.values()))
print("  gleich:", ta == tn)

print()
print("== Kommentarzeilen alt gegen neu ==")
ka = [z for z in alt_t.splitlines() if z.lstrip().startswith("#")]
kn = [z for z in neu_t.splitlines() if z.lstrip().startswith("#")]
print("  Anzahl", len(ka), len(kn), "| zeichengleich:", ka == kn)
