#!/usr/bin/env python3
"""Was der Bau kostet und was dabei herauskommt.

    python3 einrichtung/bauleistung.py [ab-datum]

`kontingent.py` zeigt den Verbrauch der ganzen Fabrik ueber ihre Lebenszeit. Diese
Auswertung sieht nur auf die Bauphase und stellt eine andere Frage: **Welche Laeufe
tragen etwas bei, und welche laufen mit?**

Zwei Zahlen entscheiden das:

- **Leerlaufquote** je Rolle. Ein leerer Lauf ist nicht immer Verschwendung -- ein
  Pruefer, der nichts findet, hat gearbeitet. Ein Bauagent, der nichts hinterlaesst,
  meist schon.
- **Wiederholte Urteile** je Paket. Das dritte Urteil ueber dasselbe Paket sagt selten
  etwas Neues; es ist der Preis dafuer, dass ein Abnahmekriterium nicht traegt.
"""

from __future__ import annotations

import sqlite3
import sys
from collections import Counter
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(WURZEL / "agents"))
from lauf import DB, frontmatter  # noqa: E402

AB = sys.argv[1] if len(sys.argv) > 1 else "2026-09-01T15:00"


def main() -> int:
    db = sqlite3.connect(DB)

    print(f"Bauphase ab {AB}\n")
    kopf = ("Rolle", "Laeufe", "leer", "$ ges", "$/Lauf")
    print(f"  {kopf[0]:22}{kopf[1]:>7}{kopf[2]:>6}{kopf[3]:>9}{kopf[4]:>9}")
    print("  " + "-" * 53)

    zeilen = db.execute(
        "SELECT rolle, count(*), sum(ergebnis='leer'), round(sum(kosten_eur), 1) "
        "FROM lauf WHERE gestartet > ? GROUP BY 1 ORDER BY 4 DESC", (AB,)).fetchall()
    for rolle, n, leer, kosten in zeilen:
        print(f"  {rolle:22}{n:>7}{leer or 0:>6}{kosten:>9}{kosten / max(n, 1):>9.1f}")

    n, leer, kosten = db.execute(
        "SELECT count(*), sum(ergebnis='leer'), round(sum(kosten_eur), 1) "
        "FROM lauf WHERE gestartet > ?", (AB,)).fetchone()
    print("  " + "-" * 53)
    print(f"  {'GESAMT':22}{n:>7}{leer or 0:>6}{kosten:>9}")

    # --- Was die Steuerung kostet, gemessen an dem, was sie steuert ---
    steuerung = {"projektmanager", "geschaeftsfuehrer"}
    bau = {"kernbauer", "datenbauer", "oberflaechenbauer", "auslieferer",
           "testentwickler", "architekt", "spielentwerfer"}
    pruef = {r for r, *_ in zeilen if r.endswith("-pruefer")}

    def summe(menge: set[str]) -> tuple[int, float]:
        aus = [(n, k) for r, n, _, k in zeilen if r in menge]
        return sum(a for a, _ in aus), sum(b for _, b in aus)

    print("\n  Wohin das Geld geht")
    print("  " + "-" * 53)
    for name, menge in (("Bau", bau), ("Pruefung", pruef), ("Steuerung", steuerung)):
        anzahl, geld = summe(menge)
        anteil = 100 * geld / max(kosten, 1)
        print(f"  {name:22}{anzahl:>7}{'':>6}{geld:>9.1f}{anteil:>8.0f}%")

    # --- Wiederholte Urteile: der Preis untragfaehiger Abnahmekriterien ---
    print("\n  Urteile je Paket (nur mehr als eines)")
    print("  " + "-" * 53)
    for ordner in sorted((WURZEL / "ventures").glob("*/befunde")):
        zaehler: Counter = Counter()
        for datei in ordner.glob("pruefung-*.md"):
            kopf_, _ = frontmatter(datei.read_text(encoding="utf-8"))
            paket = str(kopf_.get("paket", "?")).split(" ")[0]
            zaehler[paket] += 1
        mehrfach = [(p, c) for p, c in zaehler.most_common() if c > 1]
        for paket, c in mehrfach:
            print(f"  {paket:40}{c:>4} Urteile")
        gesamt = sum(zaehler.values())
        doppelt = sum(c - 1 for _, c in mehrfach)
        if gesamt:
            print(f"\n  {gesamt} Urteile insgesamt, davon {doppelt} Wiederholungen "
                  f"({100 * doppelt / gesamt:.0f} %)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
