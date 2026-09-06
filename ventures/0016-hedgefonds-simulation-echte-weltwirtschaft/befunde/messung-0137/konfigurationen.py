#!/usr/bin/env python3
# Sechs Konfigurationen: drei Bauwege mal zwei Profile, je in einem leeren Baubaum.
#
# Das ist die halbe Miete von `nachweis.py` daneben, an **einem** Stand statt an
# zweien. Wer nur sehen will, was ein bestimmter Baum heute meldet, nimmt dieses
# Skript; wer die Abnahme von Paket 0137 nachfahren will, nimmt jenes.
#
# Aufruf:  python3 konfigurationen.py <wurzel> <ausgabeverzeichnis>
#
# <wurzel> ist das Verzeichnis, das `ventures/` und `specs/` nebeneinander traegt --
# also ein Wegwerfbaum aus `git archive`, nicht der Arbeitsbaum. Der Belegstellenriegel
# sucht seine Vorgaben als `<venture>/../../specs/<name>`; flach abgelegt faellt er aus,
# und zwar an beiden Staenden gleich.
#
# Jeder Baubaum wird vorher geloescht und neu angelegt -- ein stehengebliebener Baum
# bricht mit "does not match the source used to generate cache" ab, an beiden Staenden
# gleich, sieht also nach Gleichstand aus und ist keiner.
#
# Geschrieben wird je Fall `<bauweg>-<profil>.txt` mit der reinen Konfigurationsausgabe
# (stdout und stderr hintereinander); die sechs Rueckgabecodes stehen in
# `ergebnisse.txt`.
import os
import shutil
import subprocess
import sys

VENTURE = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"

BAUWEGE = [
    ("arbeitsbereich", VENTURE),
    ("kern-allein", VENTURE + "/kern"),
    ("pruefstand-allein", VENTURE + "/pruefstand"),
]
PROFILE = ["ON", "OFF"]


def main():
    wurzel = os.path.abspath(sys.argv[1])
    ziel = os.path.abspath(sys.argv[2])
    os.makedirs(ziel, exist_ok=True)
    protokoll = []
    schlecht = 0

    for bauweg, unterpfad in BAUWEGE:
        for profil in PROFILE:
            quelle = os.path.join(wurzel, unterpfad)
            baum = os.path.join(ziel, "bau", bauweg + "-" + profil)
            if os.path.exists(baum):
                shutil.rmtree(baum)
            os.makedirs(baum)
            lauf = subprocess.run(
                ["cmake", "-S", quelle, "-B", baum,
                 "-DFABRIK_SANITIZER=" + profil],
                capture_output=True, text=True)
            name = bauweg + "-" + profil + ".txt"
            with open(os.path.join(ziel, name), "w") as f:
                f.write(lauf.stdout)
                f.write(lauf.stderr)
            protokoll.append("%-28s Code %d" % (name, lauf.returncode))
            if lauf.returncode != 0:
                schlecht += 1

    with open(os.path.join(ziel, "ergebnisse.txt"), "w") as f:
        f.write("\n".join(protokoll) + "\n")
    print("\n".join(protokoll))
    return 1 if schlecht else 0


if __name__ == "__main__":
    sys.exit(main())
