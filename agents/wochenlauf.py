#!/usr/bin/env python3
"""Der Vorstand: der wöchentliche Lauf.

    python agents/wochenlauf.py [--trocken]

    rechnen  ->  bewerten  ->  berichten

Rechnen ist deterministisch und kostet keine Tokens. Bewerten heißt: Angriffe auswerten,
Kandidaten töten, höchstens eine Gate-Vorlage anlegen. Berichten heißt: eine Seite,
Sonntagmorgen.

Sinnvoll sonntags früh, damit das Ergebnis beim ersten Kaffee bereitliegt.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kosten  # noqa: E402
import repo  # noqa: E402
from lauf import WURZEL, git, jetzt, lauf  # noqa: E402

KETTE = ["portfolio-manager", "digest-redakteur"]


def kostenbericht() -> None:
    """Deterministischer Vorlauf: Zahlen stehen fest, bevor ein Modell sie liest."""
    kosten.ZIEL.parent.mkdir(parents=True, exist_ok=True)
    kosten.ZIEL.write_text(kosten.bericht(7), encoding="utf-8")
    if git("status", "--porcelain", "ops/kosten.md").strip():
        git("add", "ops/kosten.md")
        subprocess.run(
            ["git", "commit", "-q", "-m", "kosten: Wochenbilanz"],
            cwd=WURZEL, capture_output=True, text=True, encoding="utf-8",
        )
    print(f"  ops/kosten.md geschrieben (0 Tokens).")


def main(trocken: bool = False) -> int:
    reif = repo.bereit_zur_bewertung()
    kandidaten = repo.ideen("kandidat")

    print(f"[{jetzt()}] Wochenlauf -- {len(kandidaten)} Kandidaten, "
          f"{len(reif)} davon vollständig geprüft")

    if trocken:
        print("  Trockenlauf, geplante Kette: kosten -> " + " -> ".join(KETTE))
        for k in reif:
            urteile = repo.angriffe(k["_id"])
            print(f"    reif: {k['_id']} ({len(urteile)} Angriffe)")
        if not reif:
            print("    Kein Kandidat vollständig geprüft -- der Portfolio-Manager")
            print("    wird diese Woche vermutlich keine Gate-Vorlage anlegen.")
        return 0

    kostenbericht()

    fehler = 0
    for rolle in KETTE:
        if lauf(rolle) != 0:
            fehler += 1
            print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

    offene_gates = sorted((WURZEL / "gates").glob("*.md"))
    if offene_gates:
        print(f"[{jetzt()}] Wochenlauf beendet. {len(offene_gates)} Gate-Vorlage(n) "
              f"warten auf dich:")
        for g in offene_gates:
            print(f"    {g.relative_to(WURZEL)}")
    else:
        print(f"[{jetzt()}] Wochenlauf beendet, {fehler} Fehler. Keine offenen Gates.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
