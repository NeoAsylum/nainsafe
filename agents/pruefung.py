#!/usr/bin/env python3
"""Prueft die Konfiguration aller Rollen und zeigt ihren tatsaechlichen Verbrauch.

    python3 agents/pruefung.py

Beantwortet drei Fragen auf einmal: Ist jede Rolle vollstaendig und plausibel
konfiguriert, welches Modell benutzt sie, und was hat sie bisher tatsaechlich an
Kontext und Ausgabe gekostet.

Die Konfigurationspruefungen sind bewusst streng: Eine Rolle ohne Schreibrecht kann
nichts festhalten, eine ohne Modellangabe laeuft auf dem Standard, und eine, deren
Timeout unter ihrem bisherigen Maximum liegt, wird frueher oder spaeter mittendrin
abgeschnitten.
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import DB, ROLLEN, WURZEL, frontmatter, schreibpfade  # noqa: E402

# Grobe Einordnung: Rollen, die urteilen, brauchen das staerkere Modell; Rollen, die
# sammeln, kommen mit dem schnelleren aus.
URTEILSROLLEN = {
    "ideator", "fit-filter", "portfolio-manager", "digest-redakteur", "rechercheur",
    "advocatus-nachfrage", "advocatus-wettbewerb", "advocatus-betrieb",
    "advocatus-recht", "advocatus-vertrieb",
}


def rot(t): return f"\033[31m{t}\033[0m"
def gelb(t): return f"\033[33m{t}\033[0m"
def fett(t): return f"\033[1m{t}\033[0m"


def main() -> int:
    verbrauch = {}
    if DB.exists():
        v: sqlite3.Connection = sqlite3.connect(DB)
        for rolle, n, ein, aus, maxdauer in v.execute(
            """SELECT rolle, count(*), avg(tokens_in), avg(tokens_out),
                      max(strftime('%s', beendet) - strftime('%s', gestartet))
               FROM lauf WHERE ergebnis NOT IN ('laeuft','abgebrochen')
               GROUP BY rolle"""
        ):
            verbrauch[rolle] = (n, ein or 0, aus or 0, maxdauer or 0)
        v.close()

    print(fett("\nKonfiguration und Verbrauch"))
    print("─" * 100)
    print(f"{'Rolle':22} {'Modell':8} {'Aufwand':8} {'Timeout':>8} {'Läufe':>6} "
          f"{'Ø Eingang':>11} {'Ø Ausgabe':>10} {'längster':>9}")
    print("─" * 100)

    befunde = []
    for datei in sorted(ROLLEN.glob("*.md")):
        name = datei.stem
        kopf, rumpf = frontmatter(datei.read_text(encoding="utf-8"))
        modell = kopf.get("modell", rot("FEHLT"))
        aufwand = kopf.get("effort", rot("Standard"))
        timeout = int(kopf.get("timeout", 0) or 0)
        werkzeuge = kopf.get("tools") or []

        n, ein, aus, maxdauer = verbrauch.get(name, (0, 0, 0, 0))
        print(f"{name:22} {modell:8} {aufwand:8} {timeout:>7}s {n:>6} "
              f"{int(ein):>11,} {int(aus):>10,} {int(maxdauer):>8}s".replace(",", "."))

        # --- Pruefungen ---
        if not kopf.get("effort"):
            befunde.append((name, gelb("kein Denkaufwand gesetzt -- laeuft auf dem Standard")))
        if not kopf.get("modell"):
            befunde.append((name, rot("kein Modell gesetzt -- laeuft auf dem Standard")))
        if not schreibpfade(werkzeuge):
            befunde.append((name, rot("kein Schreibrecht -- kann nichts festhalten")))
        if not timeout:
            befunde.append((name, rot("kein Timeout -- haengt im Zweifel ewig")))
        elif maxdauer and maxdauer > timeout * 0.8:
            befunde.append((name, gelb(
                f"laengster Lauf {int(maxdauer)}s bei Timeout {timeout}s -- zu knapp")))
        if name in URTEILSROLLEN and modell == "sonnet":
            befunde.append((name, gelb("urteilt, laeuft aber auf sonnet")))
        if name not in URTEILSROLLEN and modell == "opus":
            befunde.append((name, gelb("sammelt nur, laeuft aber auf opus")))
        if f"Edit(notizen/{name}.md)" not in [w.strip() for w in werkzeuge]:
            befunde.append((name, gelb("kein eigenes Logbuch -- lernt nichts dazu")))
        if len(rumpf) < 800:
            befunde.append((name, gelb(f"Auftrag nur {len(rumpf)} Zeichen -- duenn")))

    print("\n" + fett("Befunde"))
    print("─" * 100)
    if befunde:
        for name, text in befunde:
            print(f"  {name:22} {text}")
    else:
        print("  Keine. Alle Rollen vollstaendig und plausibel konfiguriert.")

    # --- Was jeder Lauf ohnehin traegt ---
    print("\n" + fett("Grundlast je Lauf"))
    print("─" * 100)
    gesamt = 0
    for pfad in ("CLAUDE.md", "notizen/lehren.md"):
        d = WURZEL / pfad
        if d.exists():
            zeichen = len(d.read_text(encoding="utf-8"))
            gesamt += zeichen
            print(f"  {pfad:24} {zeichen:>7,} Zeichen  (~{zeichen//4:>6,} Tokens)"
                  .replace(",", "."))
    print(f"  {'zusammen':24} {gesamt:>7,} Zeichen  (~{gesamt//4:>6,} Tokens)"
          .replace(",", "."))
    print("\n  Das laedt jeder Lauf, bevor er irgendetwas tut -- CLAUDE.md automatisch,")
    print("  lehren.md laut Auftrag. Bei vielen kurzen Laeufen ist das der groesste")
    print("  Einzelposten im Kontext.")
    print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
