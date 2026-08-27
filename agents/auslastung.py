#!/usr/bin/env python3
"""Erzeugt ops/auslastung.md aus dem Journal.

    python agents/auslastung.py [tage]

Die Fabrik laeuft ueber ein Abo, ihre Laeufe kosten also kein Geld. Knapp ist etwas
anderes: das Kontingent. Max rechnet in rollierenden Fuenf-Stunden-Fenstern und
zusaetzlichen Wochenkontingenten -- wer eines davon reisst, dessen Nachtlauf bricht
mittendrin ab. Deshalb misst dieser Bericht Tokens und Ergiebigkeit, nicht Euro.

Euro erscheinen erst, wenn tatsaechlich welche anfallen: sobald Kundenlast ueber die
API laeuft, traegt das Journal echte Betraege, und die Zeile taucht von selbst auf.

Bewusst kein Agent: Zahlen aus einer Datenbank zu addieren ist keine Modellaufgabe.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import db, jetzt  # noqa: E402

WURZEL = Path(__file__).resolve().parent.parent
ZIEL = WURZEL / "ops" / "auslastung.md"

# Das rollierende Fenster, in dem Max sein Kontingent rechnet.
FENSTER_STUNDEN = 5


def _tsd(n) -> str:
    return f"{n or 0:,}".replace(",", ".")


def bericht(tage: int = 7) -> str:
    verbindung = db()
    grenze = f"-{tage} days"

    zeilen = verbindung.execute(
        """SELECT rolle,
                  count(*)                    AS laeufe,
                  sum(ergebnis = 'ok')        AS ergiebig,
                  sum(ergebnis = 'leer')      AS leer,
                  sum(ergebnis IN ('fehler','abgebrochen')) AS fehler,
                  sum(tokens_in + tokens_out) AS tokens,
                  sum(kosten_eur)             AS kosten
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

    fenster = verbindung.execute(
        """SELECT count(*), sum(tokens_in + tokens_out)
           FROM lauf WHERE gestartet > datetime('now', ?)""",
        (f"-{FENSTER_STUNDEN} hours",),
    ).fetchone()

    schwerste_nacht = verbindung.execute(
        """SELECT date(gestartet) AS tag, sum(tokens_in + tokens_out) AS tok
           FROM lauf WHERE gestartet > date('now', ?)
           GROUP BY tag ORDER BY tok DESC LIMIT 1""",
        (grenze,),
    ).fetchone()
    verbindung.close()

    aus = [
        "# Auslastung",
        "",
        f"Zeitraum: letzte {tage} Tage. Erzeugt {jetzt()} von `agents/auslastung.py`.",
        "",
        "Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber",
        "Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.",
        "",
    ]

    if not zeilen:
        aus += ["Keine Laeufe im Zeitraum.", ""]
        return "\n".join(aus)

    aus += [
        "| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |",
        "|---|---:|---:|---:|---:|---:|",
    ]
    for rolle, laeufe, ok, leer, fehler, tokens, _kosten in zeilen:
        aus.append(
            f"| {rolle} | {laeufe} | {ok or 0} | {leer or 0} | {fehler or 0} "
            f"| {_tsd(tokens)} |"
        )

    laeufe, tokens, kosten = gesamt
    aus += ["", f"**Gesamt:** {laeufe} Laeufe, {_tsd(tokens)} Tokens.", ""]

    # Euro nur zeigen, wenn welche angefallen sind. Eine Spalte, die immer null
    # anzeigt, trainiert einen darauf, den Bericht nicht mehr zu lesen.
    if (kosten or 0) > 0:
        aus += [
            f"**Echte API-Kosten:** {kosten:.2f} $ — es laeuft also Last ueber die "
            "API, nicht nur ueber das Abo.",
            "",
        ]

    aus += ["## Kontingent", ""]
    f_laeufe, f_tokens = fenster
    aus.append(
        f"Im laufenden {FENSTER_STUNDEN}-Stunden-Fenster: {f_laeufe or 0} Laeufe, "
        f"{_tsd(f_tokens)} Tokens."
    )
    if schwerste_nacht:
        aus.append(
            f"Schwerster Tag im Zeitraum: {schwerste_nacht[0]} mit "
            f"{_tsd(schwerste_nacht[1])} Tokens."
        )
    aus += [
        "",
        "Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab "
        "und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette "
        "entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.",
        "",
    ]

    unergiebig = [z for z in zeilen if z[1] >= 3 and (z[2] or 0) == 0]
    fehlerhaft = [z for z in zeilen if (z[4] or 0) > 0]

    if unergiebig or fehlerhaft:
        aus += ["## Auffaellig", ""]
        for z in unergiebig:
            aus.append(
                f"- **{z[0]}** lief {z[1]}x und hat nie etwas produziert. "
                f"Dabei sind {_tsd(z[5])} Tokens ins Leere gegangen — entweder taugt "
                "der Auftrag nicht, oder die Quelle gibt nichts her."
            )
        for z in fehlerhaft:
            aus.append(f"- **{z[0]}**: {z[4]} von {z[1]} Laeufen abgebrochen.")
        aus.append("")

    return "\n".join(aus)


if __name__ == "__main__":
    tage = int(sys.argv[1]) if len(sys.argv) > 1 else 7
    ZIEL.parent.mkdir(parents=True, exist_ok=True)
    ZIEL.write_text(bericht(tage), encoding="utf-8")
    print(f"{ZIEL.relative_to(WURZEL)} geschrieben.")
