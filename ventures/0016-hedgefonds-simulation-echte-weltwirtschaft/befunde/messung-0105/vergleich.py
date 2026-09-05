"""Vergleicht die Ausgabe zweier ctest-Faelle aus einem `-V`-Mitschnitt.

Warum ein Skript und keine Handarbeit: Die beiden Laeufe drucken je rund sechzig
uebergangene Fundstellen. "Die Zahlen sind gleich" sagt nichts darueber, ob dieselben
Stellen gemeint sind -- verglichen wird deshalb der **Wortlaut Zeile fuer Zeile** und
als Mehrfachmenge, nicht als Menge.

Aufruf: python3 vergleich.py <mitschnitt> <nummer-links> <nummer-rechts>
"""

import re
import sys


def teile(pfad):
    links, rechts = [], []
    a, b = sys.argv[2], sys.argv[3]
    with open(pfad, encoding="utf-8", errors="replace") as strom:
        for zeile in strom.read().splitlines():
            treffer = re.match(r"^(\d+): (.*)$", zeile)
            if not treffer:
                continue
            if treffer.group(1) == a:
                links.append(treffer.group(2))
            elif treffer.group(1) == b:
                rechts.append(treffer.group(2))
    return links, rechts


def main():
    links, rechts = teile(sys.argv[1])
    print("links  Zeilen:", len(links))
    print("rechts Zeilen:", len(rechts))
    gleich = links == rechts
    print("zeichengleich:", gleich)
    if gleich:
        return 0
    # Die Selbsttestzeile darf abweichen: Sie zaehlt die Faelle im Programm, und dieses
    # Paket legt welche dazu. Alles andere ist eine Abweichung am Gegenstand.
    nur_links = [z for z in links if z not in rechts]
    nur_rechts = [z for z in rechts if z not in links]
    for z in nur_links:
        print("  nur links :", z)
    for z in nur_rechts:
        print("  nur rechts:", z)
    return 0


if __name__ == "__main__":
    sys.exit(main())
