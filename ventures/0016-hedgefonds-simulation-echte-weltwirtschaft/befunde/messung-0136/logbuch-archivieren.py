#!/usr/bin/env python3
"""Das Logbuch des Testentwicklers ins Archiv verschieben.

Warum ein Skript und keine drei Handgriffe: Die Regel in `CLAUDE.md` lautet
*verschieben*, nicht kopieren und nicht loeschen -- und die Werkzeuge dieses Laufs
koennen Dateien schreiben, aber nicht bewegen. Ein Abschreiben von Hand haette den
alten Wortlaut durch mich hindurchgehen lassen, und genau daran gehen Zitate kaputt.
`shutil.move` laesst ihn unberuehrt.

Der Zielname wird gesucht und nicht geraten: `-<datum>-<n>` mit dem kleinsten freien
`n`. Ein bestehendes Archiv wird nie ueberschrieben (Hausregel 3).

    python3 befunde/messung-0136/logbuch-archivieren.py
"""

import shutil
import sys
from datetime import date
from pathlib import Path

from aufbau import WURZEL

LOGBUCH = WURZEL.parents[1] / "notizen" / "testentwickler.md"


def main():
    if not LOGBUCH.exists():
        raise SystemExit("Kein Logbuch unter " + str(LOGBUCH))
    archiv = LOGBUCH.parent / "archiv"
    archiv.mkdir(parents=True, exist_ok=True)
    stamm = LOGBUCH.stem + "-" + date.today().isoformat()
    n = 1
    while (archiv / (stamm + "-" + str(n) + ".md")).exists():
        n += 1
    ziel = archiv / (stamm + "-" + str(n) + ".md")
    groesse = LOGBUCH.stat().st_size
    shutil.move(str(LOGBUCH), str(ziel))
    print(str(groesse) + " Zeichen verschoben nach " + str(ziel))
    print("Das Logbuch ist jetzt fort und wird neu angelegt -- mit den Eintraegen, "
          "die noch gelten.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
