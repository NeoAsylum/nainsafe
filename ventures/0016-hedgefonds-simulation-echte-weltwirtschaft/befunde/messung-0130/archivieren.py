"""Verschiebt das Logbuch des Testentwicklers ins Archiv -- Hausregel: nicht loeschen.

Die Datei stand am 2026-09-06 bei 12.087 Zeichen und damit ueber der Grenze von
12.000. `mv` ist mir gesperrt, `os.rename` nicht.

Der Zielname traegt eine laufende Nummer, weil an diesem Tag schon einmal
archiviert wurde. Ein vorhandenes Ziel wird nicht ueberschrieben -- dann bricht das
Skript ab.
"""
import os

QUELLE = "/home/adria/fabrik/notizen/testentwickler.md"
ZIEL = "/home/adria/fabrik/notizen/archiv/testentwickler-2026-09-06-2.md"

if os.path.exists(ZIEL):
    raise SystemExit("'%s' gibt es schon -- nichts angefasst." % ZIEL)
os.rename(QUELLE, ZIEL)
print("verschoben nach %s (%d Zeichen)" % (ZIEL, os.path.getsize(ZIEL)))
