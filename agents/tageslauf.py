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
import inhalt  # noqa: E402
import nachtlauf  # noqa: E402
from lauf import (TAGESGRENZE_USD, WOCHENGRENZE_USD, db, jetzt,  # noqa: E402
                  wochenverbrauch as lauf_wochenverbrauch,
                  kontingent_erschoepft as lauf_kontingent_erschoepft)

GRENZE = 80.0
try:
    GRENZE = float(os.environ.get("FABRIK_TAGESZIEL", GRENZE))
except ValueError:
    pass
DURCHGAENGE = 40

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
    """Dieselbe Rechnung wie in lauf.py -- eine zweite Fassung war eine zweite Wahrheit."""
    verbindung = db()
    try:
        # Der geteilte Topf bindet: Ohne ihn laufen weder Bau noch Projektmanager, und
        # die Fable-Pruefer haetten nichts zu pruefen.
        return (lauf_wochenverbrauch(verbindung, "geteilt")
                + lauf_wochenverbrauch(verbindung, "fable"))
    finally:
        verbindung.close()


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

    # Abschnittsverzeichnis auffrischen, bevor der erste Agent laeuft. Kostet null
    # Token. Muss VOR den Durchgaengen stehen: Ein veraltetes Verzeichnis ist schlimmer
    # als keines, weil ein Agent dann an der falschen Zeile liest und es nicht merkt.
    # Der Uebersetzer verschiebt die Zeilennummern in technik.md bei jedem Abschnitt.
    try:
        inhalt.main()
    except Exception as fehlschlag:      # nie den ganzen Tageslauf daran haengen
        print(f"  Abschnittsverzeichnis nicht erneuert: {fehlschlag}")

    fehler = 0
    try:
        fehler = durchgaenge_fahren(grenze, durchgaenge)
    finally:
        sperre_geben()
    print(f"[{jetzt()}] Tageslauf beendet, {fehler} Fehler, "
          f"{verbrauch():.1f} $ verbraucht.")
    return 0 if fehler == 0 else 1


def berichtsalter_stunden() -> float:
    """Alter von ops/plan.md in Stunden; sehr gross, wenn es die Datei nicht gibt."""
    plan = Path(__file__).resolve().parent.parent / "ops" / "plan.md"
    try:
        return (time.time() - plan.stat().st_mtime) / 3600
    except OSError:
        return 1e9


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
            #
            # `rest_woche` gehoert hier genauso hin wie die Tagesgrenze. Ohne sie faellt
            # der Bericht aus, sobald die Woche und nicht der Tag anhaelt: Die Schleife
            # bricht oben bei `rest_woche <= 0` ab, und der Geschaeftsfuehrer ist nie
            # gelaufen. Am 2026-09-04 ist das passiert -- die Woche schloss um 03:00,
            # und `ops/plan.md` blieb auf dem Stand vom Vortag stehen, waehrend die
            # Fabrik in derselben Nacht 27 Pakete bewegte. Der Betreiber haette bis
            # Montag einen Bericht gelesen, der die eine Zahl noch bei 0 von 310 nennt.
            # Ein alter Bericht ist ein eigener Grund. Die Sitzungsgrenze beendet den
            # Tageslauf ueber `break`, nie ueber einen "letzten" Durchgang -- am
            # 2026-09-06 stand ops/plan.md deshalb seit zwei Tagen still, waehrend die
            # Fabrik 60 Pakete abschloss. Zwoelf Stunden sind die Grenze, weil der
            # Betreiber den Rechner in diesem Takt weckt und dann liest.
            plan_alt = berichtsalter_stunden() >= 12
            letzter = (nr == durchgaenge
                       or heute + 60 >= grenze
                       or rest_woche <= 60
                       or plan_alt)
            if plan_alt:
                print(f"  Bericht ist {berichtsalter_stunden():.0f} h alt -- "
                      "Geschaeftsfuehrer laeuft in diesem Durchgang.")
            if nachtlauf.main(False, bericht=letzter) != 0:
                fehler += 1
            # Die Sitzungsgrenze ist keine Stoerung eines Durchgangs, sondern das Ende
            # des Tages. Weitermachen erzeugt nur Fehlzeilen -- am 2026-09-05 waren es
            # tausend in drei Stunden.
            absage = lauf_kontingent_erschoepft()
            if absage:
                print(f"[{jetzt()}] Angehalten nach {nr} Durchgaengen -- {absage}")
                break
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
