#!/usr/bin/env python3
"""Die Wegwerf-Baeume dieser Messung wieder abraeumen.

Ein eigenes Skript und kein Loeschbefehl von Hand: Die Ablage steht an genau einer
Stelle (`aufbau.py:ABLAGE`), und ein Aufruf, der seinen Pfad selbst hinschreibt, trifft
beim naechsten Mal einen anderen. Geraeumt wird ausschliesslich diese Ablage --
Hausregel 3 gilt fuer den Bestand, nicht fuer Baeume, die `aufbau.py` zehn Minuten
vorher selbst angelegt hat.

Anlass war ein voller Datentraeger: Drei Kopien zu je 82 MB und ihre sechs Baubaeume
haben `$TMPDIR` gefuellt, und danach scheiterte jeder weitere Aufruf an ENOSPC statt an
der Sache. Seither liegt die Ablage unter `bau/` im Vorhaben; die Begruendung steht im
Kopf von `aufbau.py`.

    python3 befunde/messung-0136/raeumen.py
"""

import shutil
import sys

# `python3 <datei>` legt das Verzeichnis der Datei selbst auf `sys.path`, also findet
# dieser Import `aufbau.py` daneben. Der Pfad der Ablage steht dort und nur dort.
from aufbau import ABLAGE


def main():
    # Zwei Orte, weil `aufbau.py` an zwei Orten anlegt: die Baeume selbst und der
    # Spiegel der Vorgaben daneben, den der Belegstellenriegel jedes Wegwerf-Baums
    # sucht. Der Spiegel liegt eine Ebene hoeher und bliebe sonst stehen.
    for pfad in (ABLAGE, ABLAGE.parent / "specs"):
        vorhanden = pfad.exists()
        shutil.rmtree(pfad, ignore_errors=True)
        print(("abgeraeumt:   " if vorhanden else "war nicht da: ") + str(pfad))
    frei = shutil.disk_usage(str(ABLAGE.parent.parent))
    print("frei unter " + str(ABLAGE.parent.parent) + ": "
          + str(frei.free // (1024 * 1024)) + " MB von "
          + str(frei.total // (1024 * 1024)) + " MB")
    return 0


if __name__ == "__main__":
    sys.exit(main())
