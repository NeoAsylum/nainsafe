#!/usr/bin/env python3
"""Arbeitet mehrere Marktsegmente auf einmal ab.

    python3 agents/marktlauf.py [anzahl] [--trocken]

Der Markt-Analyst ist die einzige Rolle mit unerschoepftem Vorrat: Er wartet nicht
auf Ereignisse, sondern arbeitet eine feste Segmentliste ab. Waehrend die uebrigen
Sensoren leer laufen, weil in der Welt gerade nichts passiert ist, hat er noch
Segmente offen.

Jeder Lauf bekommt sein Segment ausdruecklich zugewiesen. Ohne das wuerden mehrere
gleichzeitig laufende Analysten dieselbe Liste lesen, dasselbe erste unbearbeitete
Segment sehen und dieselbe Arbeit doppelt machen.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import jetzt  # noqa: E402
from nachtlauf import phase  # noqa: E402


def main(anzahl: int = 5, trocken: bool = False) -> int:
    offen = repo.offene_segmente()
    print(f"[{jetzt()}] Marktlauf -- {len(offen)} von "
          f"{len(repo.segmentliste())} Segmenten unbearbeitet")

    if not offen:
        print("  Die Liste ist abgearbeitet. Neue Segmente traegt der Betreiber")
        print("  in quellen.yml ein -- der Analyst darf sie nicht selbst erweitern.")
        return 0

    dran = offen[:anzahl]
    if trocken:
        for s in dran:
            print(f"    markt-analyst -> {s}")
        print(f"  ({len(offen) - len(dran)} bleiben danach offen)")
        return 0

    fehler = phase("Marktanalyse", [("markt-analyst", s) for s in dran])
    uebrig = len(repo.offene_segmente())
    print(f"[{jetzt()}] Marktlauf beendet, {fehler} Fehler. {uebrig} Segmente offen.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    sys.exit(main(int(args[0]) if args else 5, "--trocken" in sys.argv))
