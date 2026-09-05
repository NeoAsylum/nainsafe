#!/usr/bin/env python3
"""Die drei Bauwege in beiden Profilen, vorher gegen nachher -- Abnahme zu Paket 0136.

Gemessen wird mit `befunde/messung-0076/bauwege.py` und nicht mit einem zweiten
Messgeraet daneben: Es ist genau dafuer gebaut (Paket 0135), es faehrt beide Profile
ueber alle drei Bauwege, und es vergleicht gegen den **eigenen Stand davor** statt gegen
eine hingeschriebene Sollzahl. Dieses Skript tut dreierlei, das `bauwege.py` nicht tut:

1. Es zeigt seine Ablage von `$TMPDIR` weg. Auf dieser Maschine ist `$TMPDIR` ein
   `tmpfs` von 7,8 GB, das am 2026-09-05 zu 94 Prozent belegt war; sechs Baubaeume
   passen dort nicht mehr hinein, und ENOSPC saehe im Bericht aus wie ein kaputter Baum.
   Der Weg fuehrt ueber die Umgebung des Kindprozesses und nicht ueber eine Aenderung an
   `bauwege.py` -- jene Datei gehoert Paket 0135 und wird hier nicht angefasst.
2. Es faehrt das Paar `vorher` / `nachher` in einem Aufruf, damit der zweite Lauf
   wirklich gegen die `stand.json` des ersten vergleicht und nicht gegen `HEAD`. Gegen
   `HEAD` waere in diesem Paket wertlos: Der Umzug steckt schon in `HEAD`.
3. Es liest aus den `ctest`-Protokollen die **Zahl der Proben** je Bauweg und Profil
   heraus und stellt vorher gegen nachher. `bauwege.py` zaehlt uebersetzende Ziele; die
   Abnahme dieses Pakets fragt nach Proben, und der Waechter ist eine Probe ohne Ziel.

Vor dem Aufruf muss `aufbau.py` gelaufen sein.

    python3 befunde/messung-0136/aufbau.py
    python3 befunde/messung-0136/messen.py
"""

import os
import re
import subprocess
import sys

from aufbau import ABLAGE, WURZEL

BAUWEGE = "befunde/messung-0076/bauwege.py"
WEGE = ("arbeitsbereich", "kern", "pruefstand")
PROFILE = ("sanitizer-an", "sanitizer-aus")

# Die Bilanzzeile von `ctest`. Beide Schreibweisen, weil ein Bauweg ohne Probe die
# zweite liefert -- und ein Bauweg ohne Probe ist ein Befund und keine Null.
BILANZ = re.compile(r"tests passed, (\d+) tests failed out of (\d+)")


def bauwege_lauf(baum, marke, gegen_datei=None):
    """`bauwege.py` in `baum` laufen lassen; Ablage unter `ABLAGE`."""
    umgebung = dict(os.environ)
    umgebung["TMPDIR"] = str(ABLAGE)
    befehl = [sys.executable, str(baum / BAUWEGE), marke]
    if gegen_datei:
        befehl += ["--gegen-datei", str(gegen_datei)]
    r = subprocess.run(befehl, capture_output=True, text=True, env=umgebung)
    return r.returncode, r.stdout + r.stderr, befehl


def probenzahlen(marke):
    """Je Profil und Bauweg: (bestanden, verfehlt, gesamt) aus dem ctest-Protokoll.

    Gelesen wird das Protokoll, das `bauwege.py` selbst abgelegt hat, und nicht seine
    Zusammenfassung: Die Zahl der Proben steht nur dort, und eine zweite Quelle fuer
    dieselbe Zahl waere der Anfang zweier Wahrheiten.
    """
    zahlen = {}
    for profil in PROFILE:
        for weg in WEGE:
            pfad = ABLAGE / ("bauwege0076-" + marke) / (profil + "-" + weg + "-ctest.log")
            if not pfad.exists():
                zahlen[(profil, weg)] = None
                continue
            txt = pfad.read_text(errors="replace")
            treffer = BILANZ.search(txt)
            if treffer:
                verfehlt, gesamt = int(treffer.group(1)), int(treffer.group(2))
                zahlen[(profil, weg)] = (gesamt - verfehlt, verfehlt, gesamt)
            elif "No tests were found" in txt:
                zahlen[(profil, weg)] = (0, 0, 0)
            else:
                zahlen[(profil, weg)] = None
    return zahlen


def main():
    vorher = ABLAGE / "vorher"
    if not vorher.exists():
        raise SystemExit("Der Vergleichsbaum fehlt: " + str(vorher)
                         + " -- erst `aufbau.py` laufen lassen.")

    abweichungen = 0
    for name, baum, marke, gegen in (
            ("VORHER (Stand ohne den Umzug)", vorher, "vorher136", None),
            ("NACHHER (Arbeitsbaum)", WURZEL, "nachher136",
             ABLAGE / "bauwege0076-vorher136" / "stand.json")):
        print("=" * 78)
        print(name)
        print("=" * 78)
        code, txt, befehl = bauwege_lauf(baum, marke, gegen)
        print("$ " + " ".join(befehl))
        print(txt.rstrip())
        print("rueckgabe=" + str(code))
        print("")
        if name.startswith("NACHHER") and code != 0:
            abweichungen += 1

    print("=" * 78)
    print("Zahl der Proben je Bauweg und Profil -- vorher gegen nachher")
    print("=" * 78)
    v, n = probenzahlen("vorher136"), probenzahlen("nachher136")
    # Erwartung aus der Abnahme, hier als Bedingung und nicht als ausgeschriebene Zahl:
    # Der Arbeitsbereich haelt die Probe vorher wie nachher, nur in einem anderen
    # Kasten -- seine Zahl bleibt gleich. Der Pruefstand allein verliert sie: minus
    # eins. `kern` hat sie nie gehabt: gleich.
    SOLL = {"arbeitsbereich": 0, "kern": 0, "pruefstand": -1}
    for profil in PROFILE:
        for weg in WEGE:
            a, b = v[(profil, weg)], n[(profil, weg)]
            if a is None or b is None:
                abweichungen += 1
                print("!! " + profil.ljust(14) + weg.ljust(16)
                      + " keine Bilanzzeile im ctest-Protokoll (vorher="
                      + str(a) + ", nachher=" + str(b) + ")")
                continue
            aenderung = b[2] - a[2]
            schlecht = (aenderung != SOLL[weg] or a[1] or b[1])
            if schlecht:
                abweichungen += 1
            print(("!! " if schlecht else "   ")
                  + profil.ljust(14) + weg.ljust(16)
                  + "Proben " + str(a[2]) + " -> " + str(b[2])
                  + " (" + ("+" if aenderung >= 0 else "") + str(aenderung)
                  + ", erwartet " + ("+" if SOLL[weg] >= 0 else "") + str(SOLL[weg])
                  + ")   verfehlt vorher=" + str(a[1]) + " nachher=" + str(b[1]))

    print("")
    print(str(abweichungen) + " Abweichung(en). Ablage: " + str(ABLAGE))
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
