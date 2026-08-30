#!/usr/bin/env python3
"""Arbeitet mehrere Vorgaenge auf einmal ab.

    python3 agents/prozesslauf.py [anzahl] [--trocken]

Das Gegenstueck zu marktlauf.py auf der zweiten Achse (ADR 0005): Der Markt-Analyst
schneidet nach Branche, der Prozess-Analyst nach Vorgang. Beide haben einen
unerschoepften Vorrat -- sie warten nicht auf Ereignisse, sondern arbeiten eine Liste
ab -- und beide brauchen deshalb einen Weg, mehr als einen Auftrag je Nacht zu
erledigen, wenn Kontingent uebrig ist.

Jeder Lauf bekommt seinen Vorgang ausdruecklich zugewiesen. Ohne das wuerden mehrere
gleichzeitig laufende Analysten dieselbe Liste lesen, denselben ersten unbearbeiteten
Vorgang sehen und dieselbe Arbeit doppelt machen.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import jetzt  # noqa: E402
from nachtlauf import phase  # noqa: E402


def main(anzahl: int = 3, trocken: bool = False) -> int:
    offen = repo.offene_prozesse()
    print(f"[{jetzt()}] Prozesslauf -- {len(offen)} von "
          f"{len(repo.vorgangsliste())} Vorgaengen unbearbeitet")

    if not offen:
        print("  Die Liste ist abgearbeitet. Neue Vorgaenge traegt der Betreiber")
        print("  in quellen.yml ein -- der Analyst darf sie nicht selbst erweitern.")
        return 0

    dran = offen[:anzahl]
    if trocken:
        for v in dran:
            print(f"    prozess-analyst -> {v}")
        print(f"  ({len(offen) - len(dran)} bleiben danach offen)")
        return 0

    fehler = phase("Prozessanalyse", [("prozess-analyst", v) for v in dran])
    uebrig = len(repo.offene_prozesse())
    print(f"[{jetzt()}] Prozesslauf beendet, {fehler} Fehler. {uebrig} Vorgaenge offen.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    sys.exit(main(int(args[0]) if args else 3, "--trocken" in sys.argv))
