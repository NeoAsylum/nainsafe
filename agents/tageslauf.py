#!/usr/bin/env python3
"""Faehrt den Nachtlauf wiederholt, bis das Tagesbudget aufgebraucht ist.

    python3 agents/tageslauf.py [--grenze 95] [--durchgaenge 8] [--trocken]

Warum es das gibt: Der Nachtlauf macht **einen** Durchgang. Solange die Fabrik suchte,
war das richtig -- mehr Signale je Nacht haetten nur mehr Material erzeugt, das niemand
aufgreift. Seit sie an einem Vorhaben baut, ist es falsch: Ein Durchgang kostete am
2026-09-01 ganze 17 von 120 Dollar Tagesbudget, und die uebrigen hundert verfielen
ungenutzt.

Das Abo ist ein Festpreis. Ein nicht genutzter Durchgang spart nichts, er verschenkt.

Die Bremse bleibt, wo sie war: `lauf.py:TAGESGRENZE_USD` haelt jeden einzelnen Lauf an,
wenn die Tagesgrenze gerissen ist. Dieses Skript hoert schon frueher auf -- bei
`--grenze`, standardmaessig 95 --, damit der letzte Durchgang nicht mittendrin abbricht
und eine halbe Arbeit hinterlaesst.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import nachtlauf  # noqa: E402
from lauf import TAGESGRENZE_USD, db, jetzt  # noqa: E402

GRENZE = 700.0
DURCHGAENGE = 12


def verbrauch() -> float:
    verbindung = db()
    wert = verbindung.execute(
        "SELECT coalesce(sum(kosten_eur), 0) FROM lauf WHERE gestartet > date('now')"
    ).fetchone()[0]
    verbindung.close()
    return float(wert)


def main(grenze: float = GRENZE, durchgaenge: int = DURCHGAENGE,
         trocken: bool = False) -> int:
    print(f"[{jetzt()}] Tageslauf -- Grenze {grenze:.0f} von "
          f"{TAGESGRENZE_USD:.0f} $, hoechstens {durchgaenge} Durchgaenge")

    if trocken:
        print(f"  Verbrauch bisher: {verbrauch():.1f} $")
        print("  Je Durchgang: nachtlauf.py -- also Entwurfsrunde oder Baulauf,")
        print("  je nachdem, ob der Entwurf abgenommen ist.")
        return 0

    fehler = 0
    for nr in range(1, durchgaenge + 1):
        heute = verbrauch()
        if heute >= grenze:
            print(f"[{jetzt()}] Budget erreicht ({heute:.1f} von {grenze:.0f} $) "
                  f"nach {nr - 1} Durchgaengen.")
            break
        print()
        print(f"=== Durchgang {nr} -- {grenze - heute:.1f} $ Spielraum " + "=" * 30)
        try:
            if nachtlauf.main(False) != 0:
                fehler += 1
        except Exception as ausnahme:          # ein Durchgang darf den Tag nicht kippen
            fehler += 1
            print(f"  Durchgang {nr} abgebrochen: {ausnahme}")
    else:
        print(f"[{jetzt()}] {durchgaenge} Durchgaenge gefahren.")

    print(f"[{jetzt()}] Tageslauf beendet, {fehler} Fehler, "
          f"{verbrauch():.1f} $ verbraucht.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    g = GRENZE
    d = DURCHGAENGE
    if "--grenze" in sys.argv:
        g = float(sys.argv[sys.argv.index("--grenze") + 1])
    if "--durchgaenge" in sys.argv:
        d = int(sys.argv[sys.argv.index("--durchgaenge") + 1])
    sys.exit(main(g, d, "--trocken" in sys.argv))
