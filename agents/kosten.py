#!/usr/bin/env python3
"""Erzeugt ops/kosten.md aus dem Journal.

    python agents/kosten.py [tage]

Bewusst kein Agent: Zahlen aus einer Datenbank zu addieren ist keine Modellaufgabe.
Deterministisch ist es billiger, schneller und immer gleich richtig. Der
Digest-Redakteur liest das Ergebnis, statt selbst zu rechnen.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import db, jetzt  # noqa: E402

WURZEL = Path(__file__).resolve().parent.parent
ZIEL = WURZEL / "ops" / "kosten.md"


def bericht(tage: int = 7) -> str:
    verbindung = db()
    grenze = f"-{tage} days"

    zeilen = verbindung.execute(
        """SELECT rolle,
                  count(*)                                   AS laeufe,
                  sum(ergebnis = 'ok')                       AS ergiebig,
                  sum(ergebnis = 'leer')                     AS leer,
                  sum(ergebnis = 'fehler')                   AS fehler,
                  sum(tokens_in + tokens_out)                AS tokens,
                  sum(kosten_eur)                            AS kosten
           FROM lauf
           WHERE gestartet > date('now', ?)
           GROUP BY rolle
           ORDER BY tokens DESC""",
        (grenze,),
    ).fetchall()

    gesamt = verbindung.execute(
        """SELECT count(*), sum(tokens_in + tokens_out), sum(kosten_eur)
           FROM lauf WHERE gestartet > date('now', ?)""",
        (grenze,),
    ).fetchone()
    verbindung.close()

    aus = [
        "# Kosten und Auslastung",
        "",
        f"Zeitraum: letzte {tage} Tage. Erzeugt {jetzt()} von `agents/kosten.py`.",
        "",
    ]

    if not zeilen:
        aus += ["Keine Läufe im Zeitraum.", ""]
        return "\n".join(aus)

    aus += [
        "| Rolle | Läufe | ergiebig | leer | Fehler | Tokens | API-Kosten |",
        "|---|---:|---:|---:|---:|---:|---:|",
    ]
    for r in zeilen:
        rolle, laeufe, ok, leer, fehler, tokens, kosten = r
        aus.append(
            f"| {rolle} | {laeufe} | {ok or 0} | {leer or 0} | {fehler or 0} "
            f"| {tokens or 0:,} | {kosten or 0:.2f} $ |".replace(",", ".")
        )

    laeufe, tokens, kosten = gesamt
    aus += [
        "",
        f"**Gesamt:** {laeufe} Läufe, {(tokens or 0):,} Tokens, "
        f"{(kosten or 0):.2f} $ echte API-Kosten.".replace(",", "."),
        "",
        "Läufe über das Abo erscheinen mit 0 $ — sie kosten kein Geld, aber Kontingent.",
        "",
    ]

    auffaellig = [r for r in zeilen if r[1] >= 3 and (r[2] or 0) == 0]
    if auffaellig:
        aus += ["## Auffällig", ""]
        for r in auffaellig:
            aus.append(
                f"- **{r[0]}** lief {r[1]}× und hat nie etwas produziert. "
                "Entweder taugt der Auftrag nicht, oder die Quelle gibt nichts her."
            )
        aus.append("")

    fehlerhaft = [r for r in zeilen if (r[4] or 0) > 0]
    if fehlerhaft:
        aus += ["## Fehler", ""]
        for r in fehlerhaft:
            aus.append(f"- **{r[0]}**: {r[4]} von {r[1]} Läufen abgebrochen.")
        aus.append("")

    return "\n".join(aus)


if __name__ == "__main__":
    tage = int(sys.argv[1]) if len(sys.argv) > 1 else 7
    ZIEL.parent.mkdir(parents=True, exist_ok=True)
    ZIEL.write_text(bericht(tage), encoding="utf-8")
    print(f"{ZIEL.relative_to(WURZEL)} geschrieben.")
