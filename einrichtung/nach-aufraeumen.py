#!/usr/bin/env python3
"""Prueft, ob nach dem Aufraeumen noch alles laeuft.

    python3 einrichtung/nach-aufraeumen.py

Am 2026-09-02 ist die Suchphase ins Archiv gewandert -- signals/, research/, fuenfzehn
Ideen und sieben Runner. Was davon noch jemand liest, faellt sonst erst um 03:00 auf,
und dann ist eine Nacht weg.
"""

from __future__ import annotations

import importlib
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(WURZEL / "agents"))

MODULE = ["lauf", "repo", "nachtlauf", "baulauf", "konzeptlauf", "wochenlauf",
          "tageslauf", "dashboard", "kontingent", "auslastung", "pruefung"]


def main() -> int:
    befunde: list[str] = []

    for name in MODULE:
        try:
            importlib.import_module(name)
        except Exception as fehler:
            befunde.append(f"IMPORT {name}: {type(fehler).__name__}: {fehler}")

    # Ruft die crontab etwas auf, das es nicht mehr gibt?
    try:
        zeilen = subprocess.run(["crontab", "-l"], capture_output=True, text=True,
                                timeout=20).stdout.splitlines()
    except Exception:
        zeilen = []
    for zeile in zeilen:
        if zeile.lstrip().startswith("#"):
            continue
        for teil in zeile.split():
            if teil.startswith("agents/") and teil.endswith(".py"):
                if not (WURZEL / teil).exists():
                    befunde.append(f"CRONTAB ruft {teil} -- die Datei ist archiviert")

    # Die Verzeichnisse, die es nach dem Aufraeumen noch geben muss
    for pfad in ("ideas", "specs", "ventures", "gates", "notizen", "decisions",
                 "agents/rollen", "archiv/suche"):
        if not (WURZEL / pfad).is_dir():
            befunde.append(f"FEHLT das Verzeichnis {pfad}")

    # Die aktive Idee muss da sein, die archivierten nicht
    ideen = sorted((WURZEL / "ideas").glob("*.md"))
    if len(ideen) != 1:
        befunde.append(f"ideas/ enthaelt {len(ideen)} Dateien, erwartet ist genau die aktive")

    # Die Berichtsskripte wirklich AUSFUEHREN, nicht nur importieren. Genau daran ist
    # diese Pruefung beim ersten Mal vorbeigelaufen: `dashboard` liess sich importieren
    # und scheiterte beim Lauf an `signals/`, das ins Archiv gewandert war -- alle
    # dreissig Minuten, still, eine Stunde lang.
    for skript in ("agents/dashboard.py", "agents/kontingent.py", "agents/auslastung.py"):
        f = subprocess.run([sys.executable, skript], cwd=WURZEL,
                           capture_output=True, text=True, timeout=180)
        if f.returncode != 0:
            befunde.append("LAUF " + skript + " scheitert: "
                           + (f.stderr or "")[-500:])

    # Trockenlauf der Kette, die nachts wirklich faehrt
    fertig = subprocess.run([sys.executable, "agents/nachtlauf.py", "--trocken"],
                            cwd=WURZEL, capture_output=True, text=True, timeout=120)
    if fertig.returncode != 0:
        befunde.append("nachtlauf --trocken scheitert:\n" + (fertig.stderr or "")[-800:])

    print(f"{len(MODULE)} Module, crontab und Trockenlauf geprueft.")
    for b in befunde:
        print(f"  BEFUND  {b}")
    if not befunde:
        print("  Keine Befunde -- der naechste Takt laeuft.")
    return 1 if befunde else 0


if __name__ == "__main__":
    sys.exit(main())
