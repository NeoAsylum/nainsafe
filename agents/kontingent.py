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

# Die einzige echte Ausgabe. Fix: Ob die Fabrik siebzig Laeufe macht oder keinen,
# kostet dasselbe. Damit ist ungenutzte Kapazitaet verschenktes Geld -- es gibt keinen
# Sparzwang, nur die Frage, ob zusaetzliche Laeufe noch Neues finden.
ABO_MONAT_EUR = 200
TAGE_IM_MONAT = 30


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

    print("\n\033[1mWas es kostet\033[0m")
    print("─" * 72)
    pro_tag = ABO_MONAT_EUR / TAGE_IM_MONAT
    print(f"  Abo:           {ABO_MONAT_EUR} € im Monat, fix")
    print(f"  Anteilig:      {pro_tag:.2f} € am Tag — unabhängig von der Zahl der Läufe")
    print(f"  Für die EÜR:   {ABO_MONAT_EUR * 12} € im Jahr als Betriebsausgabe")
    print()
    print("  Das ist die einzige Zahl, die tatsächlich abfließt. Weil sie fix ist,")
    print("  kostet ein zusätzlicher Lauf nichts und ein unterlassener spart nichts.")

    hoch = (tag[1] * TAGE_IM_MONAT) if (tag and tag[1]) else ((woche[1] or 0) * 4)
    faktor = hoch / ABO_MONAT_EUR
    print("\n\033[1mZum Vergleich: was dieselbe Arbeit über die API gekostet hätte\033[0m")
    print("─" * 72)
    print(f"    {balken(min(faktor / 10, 1.0))}  {hoch:.0f} $ bei diesem Tempo im Monat")
    print(f"    Faktor {faktor:.1f} gegenüber dem Abopreis.")
    print()
    print("  Diese Zahl ist KEINE Ausgabe und KEINE Ersparnis — sie lässt sich weder")
    print("  verbuchen noch geltend machen. Sie sagt nur, wie intensiv das Abo genutzt")
    print("  wird. Für die Stückkosten eines Produkts ist sie unbrauchbar: Dort zählen")
    print("  die echten API-Preise, weil Kundenlast nicht über das Abo laufen darf.")

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
    return 0


if __name__ == "__main__":
    sys.exit(main())
