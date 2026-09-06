#!/usr/bin/env python3
"""Uebersetzt den bleibenden Bestand der Fabrik ins Englische, Datei fuer Datei.

    python3 agents/uebersetzungslauf.py [--trocken] [--stueck N]

Warum es das gibt: Die Fabrik schreibt seit dem 2026-09-06 englisch, der Bestand ist
deutsch. Ein Repo in zwei Sprachen kostet jeden Agenten in jedem Lauf einen
Uebersetzungsschritt. Uebersetzt wird deshalb, was **bleibt** -- Rollendateien, das
Regelwerk, die Spezifikationen, die ADRs.

**Was ausdruecklich nicht uebersetzt wird**, weil es sich von selbst dreht: Logbuecher
(rotieren bei 12.000 Zeichen, neue Eintraege sind englisch), Arbeitspakete und Befunde
(neue entstehen englisch, alte werden fertig und nicht mehr gelesen). Sie zu uebersetzen
waere Arbeit an etwas, das ohnehin verschwindet.

Die Reihenfolge ist nach Lesehaeufigkeit sortiert: Rollendateien werden in jedem Lauf
gelesen, ADRs fast nie.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(WURZEL / "agents"))
from lauf import jetzt, lauf  # noqa: E402

FOKUS = "0016-hedgefonds-simulation-echte-weltwirtschaft"

# Ein Abschnitt je Lauf, wenn die Datei groesser ist als das. Gemessen: spiel.md hat
# 15 Abschnitte auf zweiter Ebene, technik.md 21 -- rund 14.000 Zeichen je Stueck.
STUECK_MAX = 20_000

# Reihenfolge = Lesehaeufigkeit. Was in jedem Lauf gelesen wird, zuerst.
def bestand() -> list[Path]:
    aktiv = {"projektmanager", "geschaeftsfuehrer", "kernbauer", "datenbauer",
             "oberflaechenbauer", "auslieferer", "testentwickler", "architekt",
             "spielentwerfer", "kern-pruefer", "daten-pruefer", "test-pruefer",
             "entwurf-pruefer", "oberflaechen-pruefer", "auslieferungs-pruefer",
             "selbstspieler", "rueckvergleicher", "bruchtester", "verbesserer",
             "portfolio-manager", "digest-redakteur", "chronist", "uebersetzer"}
    liste = [WURZEL / "agents" / "rollen" / f"{r}.md" for r in sorted(aktiv)]
    liste += [WURZEL / "grenzen.md", WURZEL / "agentenbau.md"]
    liste += sorted((WURZEL / "specs" / FOKUS).glob("*.md"))
    liste += sorted((WURZEL / "decisions").glob("*.md"))
    return [p for p in liste if p.exists()]


def deutsch(text: str) -> bool:
    """Grobe, aber ausreichende Probe: deutsche Funktionswoerter und Umlaute."""
    probe = text[:4000].lower()
    treffer = sum(probe.count(w) for w in
                  (" der ", " die ", " das ", " und ", " nicht ", " ist ", " ein ",
                   " wird ", " sich ", " auch ", "ae", "oe", "ue", "ä", "ö", "ü", "ß"))
    return treffer >= 12


def offen() -> list[tuple[Path, str | None]]:
    """(Datei, Abschnitt) fuer alles, was noch deutsch ist."""
    aufgaben = []
    for p in bestand():
        try:
            t = p.read_text(encoding="utf-8")
        except OSError:
            continue
        if not deutsch(t):
            continue
        if len(t) <= STUECK_MAX:
            aufgaben.append((p, None))
            continue
        # Grosse Dateien abschnittsweise, erster noch deutscher Abschnitt zuerst.
        for m in re.finditer(r"(?m)^## (.+)$", t):
            anfang = m.start()
            naechste = re.search(r"(?m)^## ", t[anfang + 3:])
            ende = anfang + 3 + naechste.start() if naechste else len(t)
            if deutsch(t[anfang:ende]):
                aufgaben.append((p, m.group(1).strip()))
                break
    return aufgaben


def main() -> int:
    trocken = "--trocken" in sys.argv
    stueck = 1
    if "--stueck" in sys.argv:
        stueck = int(sys.argv[sys.argv.index("--stueck") + 1])

    warten = offen()
    gesamt = sum(len(p.read_text(encoding="utf-8")) for p, _ in warten)
    print(f"[{jetzt()}] Uebersetzung: {len(warten)} Dateien offen, "
          f"{gesamt:,} Zeichen deutsch")

    if not warten:
        print("  Der bleibende Bestand ist englisch.")
        return 0

    for p, abschnitt in warten[:stueck if not trocken else 8]:
        rel = p.relative_to(WURZEL)
        wo = f"{rel}#{abschnitt}" if abschnitt else str(rel)
        gr = len(p.read_text(encoding="utf-8"))
        if trocken:
            print(f"  wuerde uebersetzen: {wo}  ({gr:,} Zeichen)")
            continue
        print(f"[{jetzt()}] {wo}  ({gr:,} Zeichen)")
        if lauf("uebersetzer", wo) != 0:
            print("  Lauf fehlgeschlagen -- angehalten.")
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
