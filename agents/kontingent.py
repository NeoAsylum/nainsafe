#!/usr/bin/env python3
"""Wie viel vom Kontingent nutzt die Fabrik wirklich?

    python3 agents/kontingent.py

Vergleicht den gemessenen Verbrauch mit dem, was ein Max-20x-Abo hergibt. Die
Grenzwerte sind Naeherungen -- Anthropic nennt Prompts, keine Tokens, und die
tatsaechliche Grenze haengt am Modell. Als Groessenordnung reicht es, um die eine
Frage zu beantworten: Laufen wir am Limit oder im Leerlauf?
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import DB  # noqa: E402

# Grobe Hausnummern fuer Max 20x. Bewusst konservativ: Wenn wir selbst gegen die
# vorsichtige Schaetzung im Leerlauf laufen, ist die Antwort eindeutig.
FENSTER_STUNDEN = 5
FENSTER_TOKENS = 3_000_000      # konservativ angesetzt je 5-Stunden-Fenster
WOCHE_TOKENS = 60_000_000       # konservativ angesetzt je Woche


def balken(anteil: float, breite: int = 40) -> str:
    voll = max(0, min(breite, round(anteil * breite)))
    return "█" * voll + "·" * (breite - voll)


def main() -> int:
    if not DB.exists():
        print("Kein Journal vorhanden.")
        return 1
    v: sqlite3.Connection = sqlite3.connect(DB)

    print("\n\033[1mVerbrauch je Rolle\033[0m")
    print("─" * 66)
    print(f"{'Rolle':22} {'Laeufe':>6} {'Tokens':>12} {'je Lauf':>10}")
    for rolle, n, tok in v.execute(
        """SELECT rolle, count(*), sum(tokens_in + tokens_out)
           FROM lauf WHERE ergebnis != 'laeuft'
           GROUP BY rolle ORDER BY sum(tokens_in + tokens_out) DESC"""
    ):
        tok = tok or 0
        print(f"{rolle:22} {n:>6} {tok:>12,} {tok // max(n,1):>10,}".replace(",", "."))

    # Der schwerste Tag im Zeitraum statt eines festen Datums -- ein hartcodierter
    # Zeitstempel meldet ab dem naechsten Tag stillschweigend veraltete Zahlen.
    nacht = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out)
           FROM lauf WHERE gestartet > datetime('now', '-7 days')
           GROUP BY date(gestartet)
           ORDER BY sum(tokens_in + tokens_out) DESC LIMIT 1"""
    ).fetchone()

    fenster = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out) FROM lauf
           WHERE gestartet > datetime('now', ?)""",
        (f"-{FENSTER_STUNDEN} hours",),
    ).fetchone()

    woche = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out) FROM lauf
           WHERE gestartet > datetime('now', '-7 days')"""
    ).fetchone()
    v.close()

    print("\n\033[1mAuslastung\033[0m")
    print("─" * 66)

    f_tok = fenster[1] or 0
    f_anteil = f_tok / FENSTER_TOKENS
    print(f"  Laufendes {FENSTER_STUNDEN}-Stunden-Fenster")
    print(f"    {balken(f_anteil)}  {f_anteil*100:5.2f} %")
    print(f"    {f_tok:,} von grob {FENSTER_TOKENS:,} Tokens".replace(",", "."))

    # Ein Nachtlauf ist der eigentliche Massstab: Er faellt in genau ein Fenster.
    if nacht and nacht[1]:
        n_anteil = nacht[1] / FENSTER_TOKENS
        print(f"\n  Schwerster Tag ({nacht[0]} Laeufe)")
        print(f"    {balken(n_anteil)}  {n_anteil*100:5.2f} %")
        print(f"    {nacht[1]:,} Tokens".replace(",", "."))

    w_tok = woche[1] or 0
    # Hochrechnen: Bisher lief die Fabrik erst zwei Tage.
    hoch = (nacht[1] or 0) * 7 if nacht and nacht[1] else w_tok
    w_anteil = hoch / WOCHE_TOKENS
    print(f"\n  Sieben Naechte, hochgerechnet")
    print(f"    {balken(w_anteil)}  {w_anteil*100:5.2f} %")
    print(f"    {hoch:,} von grob {WOCHE_TOKENS:,} Tokens je Woche".replace(",", "."))

    print("\n\033[1mBefund\033[0m")
    print("─" * 66)
    if w_anteil < 0.05:
        faktor = int(0.5 / max(w_anteil, 0.001))
        print(f"  Die Fabrik nutzt ihr Kontingent praktisch nicht. Sie koennte grob")
        print(f"  das {faktor}-Fache leisten, bevor die Haelfte erreicht waere.")
        print()
        print("  Das ist kein Fehler, sondern der Stand des Ausbaus: Es laufen sechs")
        print("  Rollen einmal taeglich. Die Frage ist nicht, wie man mehr Tokens")
        print("  verbraucht, sondern welche zusaetzliche Arbeit die eine Entscheidung")
        print("  am Sonntag besser macht.")
    elif w_anteil < 0.5:
        print("  Solide Auslastung mit Luft nach oben.")
    else:
        print("  Nahe am Limit. Vor jedem Ausbau pruefen, was dafuer wegfaellt.")
    print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
