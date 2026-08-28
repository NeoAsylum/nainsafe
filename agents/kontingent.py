#!/usr/bin/env python3
"""Wie viel zieht die Fabrik aus dem Abo, und ist sie je am Limit gescheitert?

    python3 agents/kontingent.py

Rohtokens taugen NICHT als Maß fürs Kontingent, und zwar in beide Richtungen. Ein
einzelner Rechercheur-Lauf meldete sieben Millionen Tokens und lief trotzdem durch --
davon war fast alles Cache-Lesen, das anders zählt als frischer Kontext. Umgekehrt
meldete ein Markt-Scout 1,15 Millionen Rohtokens bei 0,87 $ Gegenwert, während ein
Rechercheur mit 39.000 Rohtokens 4,82 $ kostete.

Der Gegenwert aus `total_cost_usd` gewichtet richtig: Cache-Lesen fällt dort mit einem
Bruchteil ins Gewicht. Er ist deshalb die Leitgröße dieser Seite. Rohtokens stehen als
Nebenzahl daneben, ausdrücklich als das, was sie sind.

Was hier bewusst NICHT steht: eine Tokengrenze für das Fünf-Stunden-Fenster. Anthropic
nennt Prompts, keine Tokens; jede solche Zahl wäre geraten. Belastbar ist stattdessen,
ob je ein Lauf am Kontingent gescheitert ist -- das steht im Journal.
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import DB  # noqa: E402

FENSTER_STUNDEN = 5

# Bezugsgroesse fuer den Gegenwert, keine Kontingentgrenze.
ABO_MONAT_USD = 200


def balken(anteil: float, breite: int = 40) -> str:
    voll = max(0, min(breite, round(anteil * breite)))
    return "█" * voll + "·" * (breite - voll)


def tsd(n) -> str:
    return f"{n or 0:,}".replace(",", ".")


def main() -> int:
    if not DB.exists():
        print("Kein Journal vorhanden.")
        return 1
    v: sqlite3.Connection = sqlite3.connect(DB)

    print("\n\033[1mVerbrauch je Rolle\033[0m")
    print("─" * 72)
    print(f"{'Rolle':22} {'Läufe':>6} {'Gegenwert':>11} {'je Lauf':>9} {'Rohtokens':>14}")
    for rolle, n, wert, tok in v.execute(
        """SELECT rolle, count(*), sum(kosten_eur), sum(tokens_in + tokens_out)
           FROM lauf WHERE ergebnis != 'laeuft'
           GROUP BY rolle ORDER BY sum(kosten_eur) DESC"""
    ):
        wert = wert or 0
        print(f"{rolle:22} {n:>6} {wert:>10.2f}$ {wert/max(n,1):>8.2f}$ {tsd(tok):>14}")

    fenster = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out), sum(kosten_eur) FROM lauf
           WHERE gestartet > datetime('now', ?)""",
        (f"-{FENSTER_STUNDEN} hours",),
    ).fetchone()

    tag = v.execute(
        """SELECT count(*), sum(kosten_eur) FROM lauf
           WHERE gestartet > datetime('now', '-7 days')
           GROUP BY date(gestartet) ORDER BY sum(kosten_eur) DESC LIMIT 1"""
    ).fetchone()

    woche = v.execute(
        """SELECT count(*), sum(kosten_eur) FROM lauf
           WHERE gestartet > datetime('now', '-7 days')"""
    ).fetchone()

    gescheitert = v.execute(
        "SELECT count(*) FROM lauf WHERE ergebnis IN ('fehler','abgebrochen')"
    ).fetchone()[0]
    v.close()

    print("\n\033[1mAuslastung\033[0m")
    print("─" * 72)
    print(f"  Laufendes {FENSTER_STUNDEN}-Stunden-Fenster")
    print(f"    {fenster[0] or 0} Läufe, {fenster[2] or 0:.2f} $ Gegenwert")
    print(f"    ({tsd(fenster[1])} Rohtokens — überwiegend Cache, siehe Kopf der Datei)")

    if tag and tag[1]:
        print(f"\n  Schwerster Tag: {tag[0]} Läufe, {tag[1]:.2f} $ Gegenwert")

    hoch = (tag[1] * 30) if (tag and tag[1]) else ((woche[1] or 0) * 4)
    faktor = hoch / ABO_MONAT_USD
    print(f"\n  Hochgerechnet auf einen Monat bei diesem Tempo")
    print(f"    {balken(min(faktor / 10, 1.0))}  {hoch:.0f} $ Gegenwert")
    print(f"    Das Abo kostet {ABO_MONAT_USD} $ — Faktor {faktor:.1f}.")

    print("\n\033[1mBefund\033[0m")
    print("─" * 72)
    if gescheitert:
        print(f"  {gescheitert} Läufe sind gescheitert. Sind Abbrüche wegen Kontingent")
        print("  darunter, ist das Limit erreicht — die Notizen dieser Läufe sagen es:")
        print("  sqlite3 state.db \"SELECT rolle, notiz FROM lauf WHERE ergebnis='fehler';\"")
    else:
        print("  Kein Lauf ist bisher am Kontingent gescheitert. Solange das so bleibt,")
        print("  ist die Auslastung nicht die Grenze — die Frage ist dann, ob zusätzliche")
        print("  Läufe noch Neues finden, nicht ob sie möglich sind.")
    print()
    print(f"  Der Faktor {faktor:.1f} sagt, was die Fabrik aus dem Abo zieht. Er ist keine")
    print("  Rechnung: Über das Abo wird nichts davon abgerechnet.")
    print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
