#!/usr/bin/env python3
"""Faehrt den Nachtlauf wiederholt, bis das Tagesbudget aufgebraucht ist.

    python3 agents/tageslauf.py [--grenze 95] [--durchgaenge 8] [--trocken]

Warum es das gibt: Der Nachtlauf macht **einen** Durchgang. Solange die Fabrik suchte,
war das richtig -- mehr Signale je Nacht haetten nur mehr Material erzeugt, das niemand
aufgreift. Seit sie an einem Vorhaben baut, ist es falsch: Ein Durchgang kostete am
2026-09-01 ganze 17 von 120 Dollar Tagesbudget, und die uebrigen hundert verfielen
ungenutzt.

Das Abo ist ein Festpreis. Ein nicht genutzter Durchgang spart nichts, er verschenkt.

Die Bremse bleibt, wo sie war: `lauf.py:TAGESGRENZE_USD` haelt jeden einzelnen Lauf an,
wenn die Tagesgrenze gerissen ist. Dieses Skript hoert schon frueher auf -- bei
`--grenze`, standardmaessig 95 --, damit der letzte Durchgang nicht mittendrin abbricht
und eine halbe Arbeit hinterlaesst.
"""

from __future__ import annotations

import os
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import nachtlauf  # noqa: E402
from lauf import TAGESGRENZE_USD, WOCHENGRENZE_USD, db, jetzt  # noqa: E402

GRENZE = 830.0
DURCHGAENGE = 12

# Nur ein Tageslauf zugleich. Am 2026-09-03 liefen vier gleichzeitig -- einer aus der
# crontab, zwei von Hand gestartete und einer aus einer Warteschleife -- und das Ergebnis
# war nicht viermal so viel Arbeit, sondern fast keine: sechs Laeufe an einem ganzen Tag,
# vier davon seit Stunden haengend. Sie konkurrieren um dieselben Arbeitspakete, um den
# Git-Index und um das Kontingent.
#
# Die Sperre ist eine Datei mit der Prozessnummer darin. Steht dort eine Nummer, die es
# nicht mehr gibt, ist sie verwaist und wird uebernommen -- ein abgestuerzter Lauf soll
# die Fabrik nicht dauerhaft blockieren.
SPERRE = Path(__file__).resolve().parent.parent / "ops" / "tageslauf.sperre"


def sperre_nehmen() -> bool:
    """True, wenn dieser Prozess laufen darf."""
    SPERRE.parent.mkdir(parents=True, exist_ok=True)
    if SPERRE.exists():
        try:
            fremd = int(SPERRE.read_text().strip())
        except (ValueError, OSError):
            fremd = None
        veraltet = time.time() - SPERRE.stat().st_mtime > 6 * 3600
        if fremd and fremd != os.getpid() and not veraltet:
            try:
                os.kill(fremd, 0)          # laeuft der noch?
            except ProcessLookupError:
                print(f"  Verwaiste Sperre von Prozess {fremd} uebernommen.")
            except PermissionError:
                return False               # fremder Prozess, aber er lebt
            else:
                print(f"[{jetzt()}] Ein Tageslauf laeuft bereits (Prozess {fremd}).")
                print("  Zwei gleichzeitig behindern sich mehr, als sie leisten.")
                return False
    SPERRE.write_text(str(os.getpid()), encoding="utf-8")
    return True


def sperre_geben() -> None:
    try:
        if SPERRE.exists() and SPERRE.read_text().strip() == str(os.getpid()):
            SPERRE.unlink()
    except OSError:
        pass


def wochenverbrauch() -> float:
    verbindung = db()
    wert = verbindung.execute(
        "SELECT coalesce(sum(kosten_eur), 0) FROM lauf "
        "WHERE gestartet > strftime('%Y-%m-%dT%H:%M:%S', 'now', '-7 days')"
    ).fetchone()[0]
    verbindung.close()
    return float(wert)


def verbrauch() -> float:
    verbindung = db()
    wert = verbindung.execute(
        "SELECT coalesce(sum(kosten_eur), 0) FROM lauf WHERE gestartet > date('now')"
    ).fetchone()[0]
    verbindung.close()
    return float(wert)


def main(grenze: float = GRENZE, durchgaenge: int = DURCHGAENGE,
         trocken: bool = False) -> int:
    print(f"[{jetzt()}] Tageslauf -- Grenze {grenze:.0f} von "
          f"{TAGESGRENZE_USD:.0f} $, hoechstens {durchgaenge} Durchgaenge")

    if not trocken and not sperre_nehmen():
        return 0

    if trocken:
        print(f"  Verbrauch bisher: {verbrauch():.1f} $")
        print("  Je Durchgang: nachtlauf.py -- also Entwurfsrunde oder Baulauf,")
        print("  je nachdem, ob der Entwurf abgenommen ist.")
        return 0

    fehler = 0
    try:
        fehler = durchgaenge_fahren(grenze, durchgaenge)
    finally:
        sperre_geben()
    print(f"[{jetzt()}] Tageslauf beendet, {fehler} Fehler, "
          f"{verbrauch():.1f} $ verbraucht.")
    return 0 if fehler == 0 else 1


def durchgaenge_fahren(grenze: float, durchgaenge: int) -> int:
    fehler = 0
    for nr in range(1, durchgaenge + 1):
        heute = verbrauch()
        rest_woche = WOCHENGRENZE_USD - wochenverbrauch()
        if rest_woche <= 0:
            print(f"[{jetzt()}] Wochengrenze erreicht -- angehalten nach {nr - 1} "
                  "Durchgaengen. Die Woche bindet, nicht der Tag.")
            break
        if heute >= grenze:
            print(f"[{jetzt()}] Budget erreicht ({heute:.1f} von {grenze:.0f} $) "
                  f"nach {nr - 1} Durchgaengen.")
            break
        print()
        print(f"=== Durchgang {nr} -- {grenze - heute:.1f} $ Spielraum " + "=" * 30)
        try:
            # Bericht nur im letzten Durchgang -- siehe baulauf.py.
            letzter = nr == durchgaenge or heute + 60 >= grenze
            if nachtlauf.main(False, bericht=letzter) != 0:
                fehler += 1
        except Exception as ausnahme:          # ein Durchgang darf den Tag nicht kippen
            fehler += 1
            print(f"  Durchgang {nr} abgebrochen: {ausnahme}")
    else:
        print(f"[{jetzt()}] {durchgaenge} Durchgaenge gefahren.")
    return fehler


if __name__ == "__main__":
    g = GRENZE
    d = DURCHGAENGE
    if "--grenze" in sys.argv:
        g = float(sys.argv[sys.argv.index("--grenze") + 1])
    if "--durchgaenge" in sys.argv:
        d = int(sys.argv[sys.argv.index("--durchgaenge") + 1])
    sys.exit(main(g, d, "--trocken" in sys.argv))
