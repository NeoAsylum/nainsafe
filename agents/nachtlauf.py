#!/usr/bin/env python3
"""Der Herzschlag: eine Kette von Agentenlaeufen, einmal pro Nacht.

    python agents/nachtlauf.py [--trocken]

Die Kette ist bewusst kurz: sammeln, verdichten, filtern. Jeder Schritt laeuft auch
dann, wenn der vorherige nichts gefunden hat -- es kann noch unverarbeitetes Material
aus frueheren Naechten liegen.

Vor dem Lauf wird das WIP-Limit geprueft. Ist es erreicht, entfaellt die Ideenfindung:
Neue Kandidaten waeren dann nur Ballast, weil ohnehin nichts hochgestuft werden kann.
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import db, jetzt, lauf  # noqa: E402

KETTE = ["regel-scout", "ideator", "fit-filter"]

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1


def wip() -> tuple[int, int]:
    verbindung: sqlite3.Connection = db()
    zeile = verbindung.execute("SELECT aktiv, im_bau FROM wip").fetchone()
    verbindung.close()
    return (zeile[0] or 0, zeile[1] or 0) if zeile else (0, 0)


def main(trocken: bool = False) -> int:
    aktiv, im_bau = wip()
    kette = list(KETTE)

    print(f"[{jetzt()}] Nachtlauf -- WIP: {aktiv}/{WIP_AKTIV_MAX} aktiv, "
          f"{im_bau}/{WIP_BAU_MAX} im Bau")

    if aktiv >= WIP_AKTIV_MAX:
        kette = ["regel-scout"]
        print("  WIP-Limit erreicht: nur Sensorik. Ideenfindung entfaellt,")
        print("  bis am Gate 4 etwas eingestellt wird. Signale sammeln laeuft weiter.")

    if trocken:
        print("  Trockenlauf, geplante Kette:", " -> ".join(kette))
        return 0

    fehler = 0
    for rolle in kette:
        code = lauf(rolle)
        if code != 0:
            fehler += 1
            print(f"  {rolle} fehlgeschlagen -- Kette laeuft weiter.")

    print(f"[{jetzt()}] Nachtlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
