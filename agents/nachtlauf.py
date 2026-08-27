#!/usr/bin/env python3
"""Der Herzschlag: die nächtliche Kette.

    python agents/nachtlauf.py [--trocken]

    sammeln  ->  verdichten  ->  filtern  ->  angreifen

Die ersten drei Schritte laufen immer, auch wenn der vorherige nichts fand: Es kann
unverarbeitetes Material aus früheren Nächten liegen. Die Angriffe werden erst danach
bestimmt, weil der Fit-Filter in diesem Lauf neue Kandidaten erzeugt haben kann.

Ist das WIP-Limit erreicht, bleibt nur die Sensorik. Neue Kandidaten wären dann Ballast:
Sie könnten ohnehin nicht hochgestuft werden und würden nur Angriffsläufe kosten.
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import db, jetzt, lauf  # noqa: E402

KETTE = ["regel-scout", "ideator", "fit-filter"]

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1

# Höchstens so viele Ideen pro Nacht angreifen. Drei Linsen je Idee -- ohne Deckel
# wäre eine ergiebige Nacht schnell ein zweistelliger Lauf.
ANGRIFFE_MAX_IDEEN = 2


def wip() -> tuple[int, int]:
    verbindung: sqlite3.Connection = db()
    zeile = verbindung.execute("SELECT aktiv, im_bau FROM wip").fetchone()
    verbindung.close()
    return (zeile[0] or 0, zeile[1] or 0) if zeile else (0, 0)


def main(trocken: bool = False) -> int:
    aktiv, im_bau = wip()
    voll = aktiv >= WIP_AKTIV_MAX
    kette = ["regel-scout"] if voll else list(KETTE)

    print(f"[{jetzt()}] Nachtlauf -- WIP: {aktiv}/{WIP_AKTIV_MAX} aktiv, "
          f"{im_bau}/{WIP_BAU_MAX} im Bau")

    if voll:
        print("  WIP-Limit erreicht: nur Sensorik. Ideenfindung und Angriffe entfallen,")
        print("  bis an Gate 4 etwas eingestellt wird.")

    if trocken:
        print("  Trockenlauf, geplante Kette:", " -> ".join(kette))
        offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        if offen and not voll:
            print(f"  Angriffe nach heutigem Stand: {len(offen)} Läufe")
            for idee_id, linse in offen:
                print(f"    advocatus-{linse} -> {idee_id}")
        elif not voll:
            print("  Keine offenen Angriffe -- der Fit-Filter kann heute Nacht welche erzeugen.")
        return 0

    fehler = 0
    for rolle in kette:
        if lauf(rolle) != 0:
            fehler += 1
            print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

    # Erst jetzt bestimmen: Der Fit-Filter hat gerade neue Kandidaten erzeugt.
    if not voll:
        offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        if offen:
            print(f"  {len(offen)} Angriffe auf "
                  f"{len({i for i, _ in offen})} Kandidaten")
        for idee_id, linse in offen:
            if lauf(f"advocatus-{linse}", idee_id) != 0:
                fehler += 1

    print(f"[{jetzt()}] Nachtlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
