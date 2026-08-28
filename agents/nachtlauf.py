#!/usr/bin/env python3
"""Der Herzschlag: die nächtliche Kette.

    python agents/nachtlauf.py [--trocken]

    sammeln  ->  ausgraben  ->  verdichten  ->  filtern  ->  angreifen

Die Kette läuft in Phasen. Innerhalb einer Phase laufen die Agenten **gleichzeitig**,
zwischen den Phasen wird gewartet: Der Ideator braucht alle Recherchen, und die Angriffe
brauchen die Kandidaten, die der Fit-Filter erst erzeugt.

Warum parallel: Sequenziell dauerte ein voller Lauf über acht Stunden -- er hätte um
03:00 begonnen und wäre mittags noch gelaufen, mitten in den nächsten Sensorlauf hinein.
Die Agenten einer Phase sind voneinander unabhängig; sie nacheinander laufen zu lassen
war reine Verschwendung.

Ist das WIP-Limit erreicht, bleibt nur die Sensorik. Neue Kandidaten wären dann Ballast:
Sie könnten ohnehin nicht hochgestuft werden und würden nur Angriffsläufe kosten.
"""

from __future__ import annotations

import sqlite3
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import db, jetzt, lauf  # noqa: E402

# Fünf Sensoren, nicht einer. Der erste echte Lauf hat gezeigt, warum: Mit dem
# Regel-Scout als einziger Quelle stammen alle Ideen aus gesetzlichen Pflichten, und
# solche Ideen laufen fast zwangsläufig darauf hinaus, eine Rechtsfrage zu beantworten
# -- Grenze G5. Beide Ideen des ersten Laufs starben genau daran.
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

# Nach den Sensoren, vor dem Ideator: Der Rechercheur gräbt jedes neue Signal aus,
# damit die Ideen auf Zahlen stehen statt auf Vermutungen. Er läuft je Signal einmal.
VERDICHTUNG = ["ideator", "fit-filter"]

KETTE = SENSOREN + VERDICHTUNG

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1

# ---------------------------------------------------------------- Skalierung
#
# Diese drei Zahlen bestimmen, wie viel Arbeit eine Nacht bewegt. Sie hochzudrehen
# kostet Tokens, nicht Lesezeit -- der Betreiber sieht ohnehin höchstens eine
# Gate-Vorlage pro Woche.
#
# Nach jeder Erhöhung `python3 agents/kontingent.py` und `agents/stand.py` gegenlesen:
# Die Frage ist nie, ob mehr Läufe möglich sind, sondern ob sie noch Neues finden.

RECHERCHEN_MAX = 15       # Signale, die pro Nacht ausgegraben werden
ANGRIFFE_MAX_IDEEN = 10   # Kandidaten, die pro Nacht angegriffen werden (× 5 Linsen)

# Wie viele Agenten gleichzeitig. Nach oben begrenzt durch das Kontingent, nicht durch
# die Maschine -- ein Agentenlauf wartet die meiste Zeit auf Antworten. Sechs ist
# konservativ gewählt: genug, um die Laufzeit zu drücken, wenig genug, um ein
# Fünf-Stunden-Fenster nicht in Minuten zu leeren.
GLEICHZEITIG = 6


def wip() -> tuple[int, int]:
    verbindung: sqlite3.Connection = db()
    zeile = verbindung.execute("SELECT aktiv, im_bau FROM wip").fetchone()
    verbindung.close()
    return (zeile[0] or 0, zeile[1] or 0) if zeile else (0, 0)


def phase(name: str, auftraege: list[tuple[str, str | None]]) -> int:
    """Führt eine Phase gleichzeitig aus und wartet, bis alle fertig sind.

    Gibt die Zahl der Fehlschläge zurück. Ein einzelner Fehler bricht die Phase nicht
    ab -- die übrigen Agenten haben mit ihm nichts zu tun.
    """
    if not auftraege:
        return 0
    print(f"[{jetzt()}] {name}: {len(auftraege)} Läufe, "
          f"{min(GLEICHZEITIG, len(auftraege))} gleichzeitig")

    fehler = 0
    with ThreadPoolExecutor(max_workers=GLEICHZEITIG) as pool:
        ergebnisse = pool.map(lambda a: lauf(a[0], a[1]), auftraege)
        for code in ergebnisse:
            if code != 0:
                fehler += 1
    if fehler:
        print(f"  {fehler} von {len(auftraege)} fehlgeschlagen -- Kette läuft weiter.")
    return fehler


def main(trocken: bool = False) -> int:
    aktiv, im_bau = wip()
    voll = aktiv >= WIP_AKTIV_MAX

    print(f"[{jetzt()}] Nachtlauf -- WIP: {aktiv}/{WIP_AKTIV_MAX} aktiv, "
          f"{im_bau}/{WIP_BAU_MAX} im Bau")

    if voll:
        print("  WIP-Limit erreicht: nur Sensorik. Ideenfindung und Angriffe entfallen,")
        print("  bis an Gate 4 etwas eingestellt wird.")

    if trocken:
        recherchen = [] if voll else repo.offene_recherchen(RECHERCHEN_MAX)
        offen = [] if voll else repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        print(f"  Trockenlauf, {GLEICHZEITIG} Agenten gleichzeitig je Phase:")
        print(f"    1. Sensorik      {len(SENSOREN)} Läufe")
        print(f"    2. Recherche     {len(recherchen)} Läufe (Stand jetzt)")
        if not voll:
            print(f"    3. Verdichtung   {len(VERDICHTUNG)} Läufe, nacheinander")
            print(f"    4. Angriffe      {len(offen)} Läufe (Stand jetzt)")
        return 0

    fehler = 0

    # --- 1. Sensorik: fünf unabhängige Quellen -----------------------------
    fehler += phase("Sensorik", [(r, None) for r in SENSOREN])

    if not voll:
        # --- 2. Recherche: erst jetzt bestimmen, die Sensoren haben gerade
        #        Signale erzeugt. Jede Recherche ist unabhängig.
        recherchen = repo.offene_recherchen(RECHERCHEN_MAX)
        fehler += phase("Recherche", [("rechercheur", p) for p in recherchen])

        # --- 3. Verdichtung: nacheinander. Der Fit-Filter braucht die Ideen,
        #        die der Ideator im selben Lauf erst schreibt.
        for rolle in VERDICHTUNG:
            if lauf(rolle) != 0:
                fehler += 1
                print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

        # --- 4. Angriffe: erst jetzt bestimmen, der Fit-Filter hat gerade
        #        Kandidaten erzeugt. Fünf Linsen je Idee, alle unabhängig.
        offen = repo.offene_angriffe(ANGRIFFE_MAX_IDEEN)
        fehler += phase(
            "Angriffe", [(f"advocatus-{linse}", idee) for idee, linse in offen])

    print(f"[{jetzt()}] Nachtlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
