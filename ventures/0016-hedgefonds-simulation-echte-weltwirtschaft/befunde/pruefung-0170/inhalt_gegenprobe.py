#!/usr/bin/env python3
"""Pruefung 0170 -- Schritt 3: eigene Gegenprobe zu Abnahme 1.

Zaehlt unabhaengig vom Bauagenten gegen alle 19 Reihenbloecke:
  * wie viele Reihen einen leeren reihe.lizenzbeleg fuehren (Zaehlregel aus
    pruefweg.zaehlregel_lizenz: wortlaut, url und abrufdatum saemtlich leer),
    und zwar in drei Lesarten, damit die Zahl nicht an der Lesart haengt,
  * bei welchen Reihen quelle_tabelle das Wort "keine" fuehrt,
  * die Vereinigung der vier Listen gilt_fuer_reihen.

Aufruf: python3 inhalt_gegenprobe.py
"""
import subprocess
import tomllib

WURZEL = "/home/adria/fabrik"
PFAD = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml"

roh = subprocess.run(["git", "show", "885449e:" + PFAD],
                     cwd=WURZEL, capture_output=True, check=True).stdout
d = tomllib.loads(roh.decode("utf-8"))
reihen = d["reihe"]
print("Reihenbloecke:", len(reihen))

alle_leer, ein_leer, ohne_block, felderzahl = [], [], [], {}
for i, r in enumerate(reihen, start=1):
    belege = r.get("lizenzbeleg", [])
    felderzahl[i] = len(belege)
    if not belege:
        ohne_block.append(i)
        continue

    def leer(b):
        return not b.get("wortlaut") and not b.get("url") and not b.get("abrufdatum")
    if all(leer(b) for b in belege):
        alle_leer.append(i)
    if any(leer(b) for b in belege):
        ein_leer.append(i)

print("Lesart 'alle Bloecke der Reihe leer':", alle_leer, "->", len(alle_leer))
print("Lesart 'mindestens ein Block leer' :", ein_leer, "->", len(ein_leer))
print("Reihen ganz ohne Block            :", ohne_block)
print("Bloecke je Reihe                  :", felderzahl,
      "| Summe", sum(felderzahl.values()))

keine = [i for i, r in enumerate(reihen, start=1)
         if "keine" in r.get("quelle_tabelle", "").lower()]
genau_keine = [i for i, r in enumerate(reihen, start=1)
               if r.get("quelle_tabelle", "").strip().lower() == "keine"]
print()
print("quelle_tabelle enthaelt 'keine':", keine)
print("quelle_tabelle ist genau 'keine':", genau_keine)
print("quelle_tabelle-Werte der vier Kandidaten:",
      {i: reihen[i - 1].get("quelle_tabelle") for i in sorted(set(keine) | {16})})

listen = {k: v["gilt_fuer_reihen"] for k, v in d["namensnennung"].items()
          if isinstance(v, dict)}
union = sorted(set().union(*listen.values()))
print()
print("gilt_fuer_reihen je Quelle:", listen)
print("Vereinigung:", union)
print("fehlend aus 1..19:", sorted(set(range(1, 20)) - set(union)))

print()
print("PROBE der Aussage im Feld:")
print("  drei fehlende == quelle_tabelle-keine-Menge :",
      sorted(set(range(1, 20)) - set(union)) == genau_keine == [17, 18, 19])
print("  leere Lizenzbelege sind vier, naemlich 16..19:", alle_leer == [16, 17, 18, 19])
print("  die drei sind Teilmenge der vier            :",
      set(genau_keine) <= set(alle_leer))

txt = d["namensnennung"]["vollstaendigkeit"]
print()
print("Wortprobe im Feld:")
for w in ("dieselben drei", "vier", "16, 17, 18 und 19", "nicht allein",
          "zaehlregel_lizenz", "schnitt_7", "widerlegt"):
    print("  %-22r %s" % (w, w in txt))
