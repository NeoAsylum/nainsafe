#!/usr/bin/env python3
"""Nur die Angriffsphase: alle offenen Linsen auf alle Kandidaten, gleichzeitig.

    python3 agents/angriffslauf.py [--trocken]

Nützlich, wenn der Fit-Filter ausserhalb der Nachtkette gelaufen ist und frische
Kandidaten ungeprüft liegen -- statt eine volle Kette zu fahren, nur um die Angriffe
nachzuholen.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import jetzt  # noqa: E402
from nachtlauf import ANGRIFFE_MAX_IDEEN, phase  # noqa: E402


def main(trocken: bool = False) -> int:
    offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
    ideen = {i for i, _ in offen}
    print(f"[{jetzt()}] Angriffslauf -- {len(offen)} Läufe auf {len(ideen)} Kandidaten")

    if trocken:
        for idee, linse in offen:
            print(f"    advocatus-{linse} -> {idee}")
        return 0

    fehler = phase("Angriffe", [(f"advocatus-{l}", i) for i, l in offen])
    fehler += phase("Verteidigung",
                    [("anwalt", i) for i in repo.offene_anwaelte(ANGRIFFE_MAX_IDEEN)])
    print(f"[{jetzt()}] Angriffslauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
