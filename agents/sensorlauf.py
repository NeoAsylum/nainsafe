#!/usr/bin/env python3
"""Nur sammeln und ausgraben. Laeuft mehrmals taeglich.

    python3 agents/sensorlauf.py [--trocken]

Die vier Sensoren plus der Rechercheur, ohne Ideator, Fit-Filter und Angriffe.

Warum getrennt vom Nachtlauf: Signale duerfen liegen bleiben, Kandidaten nicht.
Mehr Signale kosten nichts -- sie warten, bis die Vollkette sie nachts abholt. Mehr
Kandidaten dagegen waeren wertlos, weil der Betreiber am Sonntag ohnehin hoechstens
eine Vorlage sieht. Deshalb laeuft die Sensorik oft und die Verdichtung einmal.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import jetzt, lauf  # noqa: E402
from nachtlauf import RECHERCHEN_MAX, SENSOREN  # noqa: E402


def main(trocken: bool = False) -> int:
    offen = repo.offene_recherchen(RECHERCHEN_MAX)
    print(f"[{jetzt()}] Sensorlauf -- {len(offen)} Signale ohne Recherche")

    if trocken:
        print("  Trockenlauf:", " -> ".join(SENSOREN))
        for pfad in offen:
            print(f"    rechercheur -> {pfad}")
        return 0

    fehler = 0
    for rolle in SENSOREN:
        if lauf(rolle) != 0:
            fehler += 1

    # Nach den Sensoren neu bestimmen -- sie haben gerade Signale erzeugt.
    for pfad in repo.offene_recherchen(RECHERCHEN_MAX):
        if lauf("rechercheur", pfad) != 0:
            fehler += 1

    print(f"[{jetzt()}] Sensorlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
