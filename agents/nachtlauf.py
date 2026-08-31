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

# Der Markt-Analyst steht nicht in SENSOREN, obwohl er einer ist. Zwei Gruende:
#
# Erstens arbeitet er andersherum -- nicht vom Vorfall zur Idee, sondern vom Markt zum
# Produkt. Er prueft Zahlungsbereitschaft und Vertriebskanal zuerst statt zuletzt,
# genau daran sind die bisherigen Ideen reihenweise gestorben.
#
# Zweitens ist er die einzige Rolle mit unerschoepftem Vorrat: Er wartet nicht auf
# Ereignisse, sondern arbeitet eine Segmentliste ab. Als einzelner Sensorlauf haette er
# fuer die 25 offenen Segmente 25 Naechte gebraucht -- und die Haelfte davon steht erst
# seit ADR 0004 auf der Liste, weil der Suchraum vorher unbegruendet auf deutsche KMU
# verengt war. Drei je Nacht bringen den neuen Suchraum in gut einer Woche durch.
#
# Jeder Lauf bekommt sein Segment ausdruecklich zugewiesen. Ohne das wuerden drei
# gleichzeitig laufende Analysten dieselbe Liste lesen, dasselbe erste unbearbeitete
# Segment sehen und dieselbe Arbeit dreimal machen.
MARKT_MAX = 2

# Die zweite Achse, seit ADR 0005. Der Markt-Analyst schneidet nach Branche, der
# Prozess-Analyst nach Vorgang -- auf denselben Daten, mit ganz anderem Ergebnis:
# Sechs Segmente, die einzeln als "zu klein" abgelegt waren, nennen denselben
# Pruefnachweis und sind zusammen 65.433 Betriebe. Er laeuft nach dem Markt-Analysten
# in derselben Phase, weil er dessen Profile liest -- die von heute Nacht noch nicht,
# aber die von gestern schon. Das reicht: Sein Rohstoff sind achtzehn vorhandene
# Profile, nicht die drei neuen.
PROZESS_MAX = 2

# Nach den Sensoren, vor dem Ideator: Der Rechercheur gräbt jedes neue Signal aus,
# damit die Ideen auf Zahlen stehen statt auf Vermutungen. Er läuft je Signal einmal.
# Der Fit-Filter liegt seit dem 2026-08-31 im Archiv -- die Fabrik bewertet keine neuen
# Ideen mehr, sie baut eine. Er bleibt hier auskommentiert stehen statt geloescht:
# Wer die Suche ueber FOKUS = None wieder aufnimmt, braucht ihn zurueck.
#     VERDICHTUNG = ["ideator", "fit-filter"]
VERDICHTUNG = ["ideator"]

KETTE = SENSOREN + VERDICHTUNG

# ---------------------------------------------------------------- Fokus
#
# Steht hier eine Ideen-ID, sucht die Fabrik nicht mehr. Entschieden vom Betreiber am
# 2026-08-31: "Ab jetzt bauen wir nur noch das Spiel."
#
# Abgeschaltet werden damit die Sensorik (sechs Scouts), die Marktprofile, die
# Prozessprofile, die Recherche und der Ideator -- alles, was NEUE Ideen erzeugt. Das
# ist der weitaus groesste Teil des Verbrauchs: Rechercheur und Analysten waren
# zusammen ueber siebzig Prozent.
#
# Weiter laufen ausschliesslich Rollen, die AN DIESER Idee arbeiten. Solange sie noch
# `entwurf` oder `kandidat` ist, sind das Fit-Filter, die fuenf Linsen und der Anwalt --
# die einzige Mechanik, die je den toedlichen Einwand gefunden hat, und ihre Befunde
# sind der Rohstoff der Konzeptionsphase. Steht die Idee auf `erkundung` oder weiter,
# hat der Nachtlauf nichts mehr zu tun: Dann faehrt `agents/konzeptlauf.py` auf Zuruf.
#
# Nichts ist geloescht. FOKUS = None stellt die Suche vollstaendig wieder her, und
# quellen.yml behaelt alle 44 Segmente und acht Vorgaenge.
FOKUS: str | None = "0016-hedgefonds-simulation-echte-weltwirtschaft"

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1

# ---------------------------------------------------------------- Skalierung
#
# Diese Zahlen bestimmen, wie viel Arbeit eine Nacht bewegt.
#
# Am 2026-08-29 von 15 auf 5 und von 10 auf 4 gesenkt. Grund war nicht Sparsamkeit,
# sondern Ertrag: Der Rechercheur verbrauchte 66 Prozent des Wochenkontingents bei
# 43 Laeufen, von denen 16 leer blieben -- und der Ideator meldete am selben Tag,
# dass jede vorliegende Recherche rot oder verarbeitet ist. Der Engpass war nie die
# Zahl der Recherchen, sondern die Zahl brauchbarer Signale.
#
# Nach jeder Aenderung `python3 agents/kontingent.py` gegenlesen: Die Frage ist nie,
# ob mehr Laeufe moeglich sind, sondern ob sie noch Neues finden.

RECHERCHEN_MAX = 5        # Signale, die pro Nacht ausgegraben werden
ANGRIFFE_MAX_IDEEN = 4    # Kandidaten, die pro Nacht angegriffen werden (× 5 Linsen)

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


def fokuslauf(trocken: bool) -> int:
    """Der Nachtlauf, wenn die Fabrik nicht mehr sucht, sondern an einer Idee arbeitet."""
    kopf = next((k for k in repo.ideen(mit_eichung=False) if k["_id"] == FOKUS), None)
    if kopf is None:
        print(f"  FOKUS steht auf {FOKUS}, aber die Idee gibt es nicht.")
        return 1
    st = kopf.get("status")
    print(f"[{jetzt()}] Fokus auf {FOKUS} -- Status `{st}`. Die Suche ruht.")

    if st in ("entwurf", "kandidat"):
        print("  Die Bewertungskette ist seit dem 2026-08-31 archiviert -- der")
        print("  Betreiber hat entschieden, dass gebaut statt bewertet wird.")
        print(f"  Weiter mit:  python3 agents/konzeptlauf.py {FOKUS} --ab 2")
        print("  (Status vorher auf `erkundung` setzen -- das ist Gate 1.)")
        return 0

    print("  Die Bewertung ist abgeschlossen. Weiter geht es nicht naechtlich,")
    print(f"  sondern auf Zuruf:  python3 agents/konzeptlauf.py {FOKUS}")
    return 0


def main(trocken: bool = False) -> int:
    if FOKUS:
        return fokuslauf(trocken)

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
        maerkte = repo.offene_segmente()[:MARKT_MAX]
        prozesse = repo.offene_prozesse()[:PROZESS_MAX]
        print(f"    1. Sensorik      {len(SENSOREN) + len(maerkte) + len(prozesse)} Läufe "
              f"({len(SENSOREN)} Sensoren + {len(maerkte)} Marktprofile "
              f"+ {len(prozesse)} Prozessprofile)")
        for s in maerkte:
            print(f"                     markt-analyst   -> {s}")
        for v in prozesse:
            print(f"                     prozess-analyst -> {v}")
        print(f"    2. Recherche     {len(recherchen)} Läufe (Stand jetzt)")
        if not voll:
            print(f"    3. Verdichtung   {len(VERDICHTUNG)} Läufe, nacheinander")
            print(f"    4. Angriffe      {len(offen)} Läufe (Stand jetzt)")
        return 0

    fehler = 0

    # --- 1. Sensorik: unabhängige Quellen, dazu die Marktprofile -----------
    auftraege: list[tuple[str, str | None]] = [(r, None) for r in SENSOREN]
    auftraege += [("markt-analyst", s) for s in repo.offene_segmente()[:MARKT_MAX]]
    auftraege += [("prozess-analyst", v) for v in repo.offene_prozesse()[:PROZESS_MAX]]
    fehler += phase("Sensorik", auftraege)

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

        # --- 5. Verteidigung: erst wenn alle fuenf Linsen vorliegen. Der Anwalt
        #        prueft, ob die Einwaende loesbar sind, statt sie als Endurteil zu
        #        nehmen -- Unternehmertum heisst, Probleme zu loesen, nicht vor ihnen
        #        aufzugeben.
        fehler += phase(
            "Verteidigung",
            [("anwalt", i) for i in repo.offene_anwaelte(ANGRIFFE_MAX_IDEEN)])

    print(f"[{jetzt()}] Nachtlauf beendet, {fehler} Fehler.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
