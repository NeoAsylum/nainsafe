#!/usr/bin/env python3
"""Der Herzschlag: die nächtliche Kette.

    python agents/nachtlauf.py [--trocken]

    sammeln  ->  verdichten  ->  filtern  ->  angreifen

Die ersten drei Schritte laufen immer, auch wenn der vorherige nichts fand: Es kann
unverarbeitetes Material aus früheren Nächten liegen. Die Angriffe werden erst danach
bestimmt, weil der Fit-Filter in diesem Lauf neue Kandidaten erzeugt haben kann.

Ist das WIP-Limit erreicht, bleibt nur die Sensorik. Neue Kandidaten wären dann Ballast:
Sie könnten ohnehin nicht hochgestuft werden und würden nur Angriffsläufe kosten.
"""

from __future__ import annotations

import sqlite3
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import db, jetzt, lauf  # noqa: E402

# Vier Sensoren, nicht einer. Der erste echte Lauf hat gezeigt, warum: Mit dem
# Regel-Scout als einziger Quelle stammen alle Ideen aus gesetzlichen Pflichten, und
# solche Ideen laufen fast zwangslaeufig darauf hinaus, eine Rechtsfrage zu beantworten
# -- Grenze G5. Beide Ideen des ersten Laufs starben genau daran. Erst geaeusserter
# Aerger, Marktluecken und neue Bausteine machen die Fabrik ergebnisoffen.
SENSOREN = [
    "regel-scout",
    "pain-scout",
    "markt-scout",
    "tech-scout",
    # Sucht Modelle, die anderswo nachweislich laufen. Die einzige Signalart, bei der
    # die Frage "zahlt jemand dafuer" schon beantwortet ist -- genau die Frage, an der
    # bisher jede Idee starb.
    "modell-scout",
]

# Nach den Sensoren, vor dem Ideator: Der Rechercheur graebt jedes neue Signal aus,
# damit die Ideen auf Zahlen stehen statt auf Vermutungen. Er laeuft je Signal einmal.
VERDICHTUNG = ["ideator", "fit-filter"]

KETTE = SENSOREN + VERDICHTUNG

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1

# ---------------------------------------------------------------- Skalierung
#
# Das Kontingent ist bei weitem nicht ausgelastet -- ein voller Nachtlauf lag bei rund
# einem Prozent des Fuenf-Stunden-Fensters (siehe agents/kontingent.py). Diese drei
# Zahlen sind die Stellschrauben; sie hochzudrehen kostet Tokens, nicht Lesezeit, denn
# der Betreiber sieht ohnehin hoechstens eine Gate-Vorlage pro Woche.
#
# Nach jeder Erhoehung einmal `python3 agents/kontingent.py` und `agents/stand.py`
# gegenlesen: Die Frage ist nie, ob mehr Laeufe moeglich sind, sondern ob sie noch
# Neues finden.

RECHERCHEN_MAX = 15       # Signale, die pro Nacht ausgegraben werden
ANGRIFFE_MAX_IDEEN = 10   # Kandidaten, die pro Nacht angegriffen werden (× 5 Linsen)

def wip() -> tuple[int, int]:
    verbindung: sqlite3.Connection = db()
    zeile = verbindung.execute("SELECT aktiv, im_bau FROM wip").fetchone()
    verbindung.close()
    return (zeile[0] or 0, zeile[1] or 0) if zeile else (0, 0)


def main(trocken: bool = False) -> int:
    aktiv, im_bau = wip()
    voll = aktiv >= WIP_AKTIV_MAX

    print(f"[{jetzt()}] Nachtlauf -- WIP: {aktiv}/{WIP_AKTIV_MAX} aktiv, "
          f"{im_bau}/{WIP_BAU_MAX} im Bau")

    if voll:
        print("  WIP-Limit erreicht: nur Sensorik. Ideenfindung und Angriffe entfallen,")
        print("  bis an Gate 4 etwas eingestellt wird.")

    recherchen = [] if voll else repo.offene_recherchen(RECHERCHEN_MAX)

    if trocken:
        print("  Trockenlauf, geplante Kette:")
        print("    " + " -> ".join(SENSOREN))
        if recherchen:
            print(f"    rechercheur × {len(recherchen)}:")
            for pfad in recherchen:
                print(f"      {pfad}")
        elif not voll:
            print("    rechercheur: nichts Offenes -- die Sensoren erzeugen heute Nacht welches.")
        if not voll:
            print("    " + " -> ".join(VERDICHTUNG))
        offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        if offen and not voll:
            print(f"    Angriffe nach heutigem Stand: {len(offen)} Läufe "
                  f"auf {len({i for i, _ in offen})} Kandidaten")
        elif not voll:
            print("    Keine offenen Angriffe -- der Fit-Filter kann heute Nacht welche erzeugen.")
        return 0

    fehler = 0
    for rolle in SENSOREN:
        if lauf(rolle) != 0:
            fehler += 1
            print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

    # Nach den Sensoren neu bestimmen: Sie haben gerade Signale erzeugt, die noch
    # keine Recherche haben.
    if not voll:
        recherchen = repo.offene_recherchen(RECHERCHEN_MAX)
        if recherchen:
            print(f"  {len(recherchen)} Signale werden ausgegraben")
        for pfad in recherchen:
            if lauf("rechercheur", pfad) != 0:
                fehler += 1

        for rolle in VERDICHTUNG:
            if lauf(rolle) != 0:
                fehler += 1
                print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

    # Erst jetzt bestimmen: Der Fit-Filter hat gerade neue Kandidaten erzeugt.
    if not voll:
        offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        if offen:
            print(f"  {len(offen)} Angriffe auf "
                  f"{len({i for i, _ in offen})} Kandidaten")
        for idee_id, linse in offen:
            if lauf(f"advocatus-{linse}", idee_id) != 0:
                fehler += 1

    print(f"[{jetzt()}] Nachtlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
