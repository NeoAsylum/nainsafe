#!/usr/bin/env python3
"""Raeumt weg, was `messung.py` ausserhalb des Repos anlegt.

Es liegt alles unter einem Ordner, und dieser Name steht in beiden Dateien gleich. Das
Skript weigert sich, etwas anderes anzufassen: Ohne diese Pruefung waere ein leeres
`TMPDIR` ein `rmtree` auf `/`.

Aufruf:  python3 aufraeumen.py
"""

import os
import pathlib
import shutil
import sys

ARBEITSNAME = "messung-0147"


def main():
    wurzel = pathlib.Path(os.environ.get("TMPDIR", "/tmp"))
    arbeit = wurzel / ARBEITSNAME
    if arbeit.name != ARBEITSNAME or arbeit.parent == arbeit:
        print("ABBRUCH: " + str(arbeit) + " ist nicht der Arbeitsordner.")
        return 1
    if not arbeit.exists():
        print("Nichts da: " + str(arbeit))
        return 0
    shutil.rmtree(arbeit)
    print("Weg: " + str(arbeit))
    return 0


if __name__ == "__main__":
    sys.exit(main())
