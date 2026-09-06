#!/usr/bin/env python3
"""Raeumt den Arbeitsplatz von `messen.py` weg.

`messen.py` raeumt am Ende selbst auf. Bricht er vorher ab -- ein verschobener
Wortlaut, ein Mutant, der nicht uebersetzt --, bleiben die Wegwerfwurzeln und die
Mutantenbinaerprogramme liegen. Sie liegen ausserhalb des Repos und fallen deshalb
niemandem auf, bis der naechste Lauf am vollen Dateibaum scheitert.

Geloescht wird ausschliesslich das eine Verzeichnis unter `TMPDIR`, das `messen.py`
selbst angelegt hat. Hausregel 3 gilt fuer das Gedaechtnis der Fabrik; ein Wegwerfbaum
in `TMPDIR` ist keins.
"""

import os
import pathlib
import shutil

ARBEIT = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0180"

if ARBEIT.exists():
    shutil.rmtree(ARBEIT)
    print(f"weggeraeumt: {ARBEIT}")
else:
    print(f"nichts zu tun: {ARBEIT} gibt es nicht")
