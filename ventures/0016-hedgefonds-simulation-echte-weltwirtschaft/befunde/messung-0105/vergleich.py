"""Vergleicht die Ausgabe zweier ctest-Faelle aus einem `-V`-Mitschnitt.

Warum ein Skript und keine Handarbeit: Die beiden Laeufe drucken je rund sechzig
uebergangene Fundstellen. "Die Zahlen sind gleich" sagt nichts darueber, ob dieselben
Stellen gemeint sind -- verglichen wird deshalb der **Wortlaut Zeile fuer Zeile** und
als Mehrfachmenge, nicht als Menge.

Aufruf: python3 vergleich.py <mitschnitt> <nummer-links> <nummer-rechts>
"""

import re
import sys
from collections import Counter


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
    # Verglichen wird als **Mehrfachmenge** und nicht mit `in`. Der gedruckte Wortlaut
    # einer Fundstelle ist nicht schluesselfaehig: "gesucht war: 7" steht sechzehnmal da.
    # Ein Vergleich, der ihn dedupliziert, uebersieht genau die Aenderung, um die es
    # hier geht -- eine Zeile, die von drei auf zwei Vorkommen faellt.
    fehlt = Counter(links) - Counter(rechts)
    dazu = Counter(rechts) - Counter(links)
    for z, n in sorted(fehlt.items()):
        print("  nur links  (%dx):" % n, z)
    for z, n in sorted(dazu.items()):
        print("  nur rechts (%dx):" % n, z)
    print("Zeilen nur links :", sum(fehlt.values()))
    print("Zeilen nur rechts:", sum(dazu.values()))
    return 0


if __name__ == "__main__":
    sys.exit(main())
