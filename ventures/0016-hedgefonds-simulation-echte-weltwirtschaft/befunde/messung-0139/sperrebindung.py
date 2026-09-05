#!/usr/bin/env python3
"""Nachweis zu Paket 0139 -- der Sperrebindungsriegel deckt auch `kern/test`.

Sechs Baeume in einem Aufruf, jeder in einer eigenen Abschrift unter `$TMPDIR`. Der
Baum im Repo wird nicht angefasst; die beiden Fassungen der `CMakeLists.txt` liegen
als Kopie daneben (`cmakelists-vorher.txt`, `cmakelists-nachher.txt`), damit die
Messung ohne einen bestimmten Git-Stand wiederholbar ist.

Aufruf:  python3 sperrebindung.py
Ende:    "Abweichungen: 0" und Rueckgabe 0.
"""

from __future__ import annotations

import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

HIER = Path(__file__).resolve().parent
VORHABEN = HIER.parent.parent
KERN = VORHABEN / "kern"
WERKZEUGKETTE = VORHABEN / "werkzeugkette.cmake"
PROBEN = HIER / "proben"
FASSUNG = {"vorher": HIER / "cmakelists-vorher.txt",
           "nachher": HIER / "cmakelists-nachher.txt"}


def baum_anlegen(wurzel: Path, fassung: str, zulage) -> Path:
    """Abschrift von `kern/` samt Werkzeugkette; `bau/` bleibt draussen (absolute Pfade)."""
    ziel = wurzel / "kern"
    shutil.copytree(KERN, ziel, ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WERKZEUGKETTE, wurzel / "werkzeugkette.cmake")
    shutil.copyfile(FASSUNG[fassung], ziel / "CMakeLists.txt")
    if zulage is not None:
        wohin, woher = zulage
        shutil.copyfile(PROBEN / woher, ziel / wohin)
    return ziel


def lauf(befehl):
    e = subprocess.run(befehl, capture_output=True, text=True)
    return e.returncode, e.stdout + e.stderr


def marken(text: str, wieviel: int = 4) -> str:
    """Die letzten Ausgabezeilen -- ein blosser Exitcode belegt nichts."""
    zeilen = [z for z in text.splitlines() if z.strip()]
    return "\n".join("      | " + z for z in zeilen[-wieviel:])


MELDUNGSMUSTER = re.compile(
    r"Sperrebindungsriegel [^\n]*?(\d+) Kernquelle\(n\) und (\d+) Probe\(n\) geprueft")


def zaehlung_pruefen(ziel: Path, ausgabe: str) -> list:
    """Die beiden Zahlen der Statusmeldung gegen den Baum selbst, nicht gegen eine
    ausgeschriebene Sollzahl -- die veraltet mit dem naechsten Kernpaket."""
    treffer = MELDUNGSMUSTER.search(ausgabe)
    if treffer is None:
        return ["die Statusmeldung nennt Quellen und Proben nicht getrennt"]
    gemeldet = (int(treffer.group(1)), int(treffer.group(2)))
    gezaehlt = (len(list((ziel / "src").glob("*.cpp"))),
                len(list((ziel / "test").glob("*.cpp"))))
    if gemeldet != gezaehlt:
        return ["Meldung sagt %s, im Baum liegen %s" % (gemeldet, gezaehlt)]
    if 0 in gezaehlt:
        return ["eine der beiden Mengen ist leer -- der Baum belegt nichts"]
    return []


def fahre(baum: dict) -> list:
    abweichungen = []
    schalter = "-DFABRIK_SANITIZER=" + ("ON" if baum["sanitizer"] else "OFF")
    print("\n[%s] %s" % (baum["nummer"], baum["titel"]))
    print("      Fassung %s, %s, Zulage: %s"
          % (baum["fassung"], schalter, baum["zulage"] or "keine"))

    with tempfile.TemporaryDirectory() as ort:
        wurzel = Path(ort)
        ziel = baum_anlegen(wurzel, baum["fassung"], baum["zulage"])
        bau = wurzel / "bau"
        code, ausgabe = lauf(["cmake", "-S", str(ziel), "-B", str(bau), schalter])
        print("      cmake -S  -> Code %d" % code)
        print(marken(ausgabe))

        if not baum["gruen"]:
            if code == 0:
                abweichungen.append("%s: konfiguriert mit Code 0, erwartet war Abbruch"
                                    % baum["nummer"])
            for stueck in baum["enthaelt"]:
                if stueck not in ausgabe:
                    abweichungen.append("%s: Abbruchmeldung ohne %r"
                                        % (baum["nummer"], stueck))
            return abweichungen

        if code != 0:
            abweichungen.append("%s: Konfigurieren mit Code %d, erwartet war gruen"
                                % (baum["nummer"], code))
            return abweichungen
        abweichungen += ["%s: %s" % (baum["nummer"], m)
                         for m in zaehlung_pruefen(ziel, ausgabe)]

        code, gebaut = lauf(["cmake", "--build", str(bau)])
        print("      cmake --build -> Code %d" % code)
        if code != 0:
            print(marken(gebaut))
            abweichungen.append("%s: Bauen mit Code %d" % (baum["nummer"], code))
            return abweichungen

        code, getestet = lauf(["ctest", "--test-dir", str(bau), "--output-on-failure"])
        print("      ctest     -> Code %d" % code)
        print(marken(getestet, 2))
        if code != 0:
            abweichungen.append("%s: ctest mit Code %d" % (baum["nummer"], code))
    return abweichungen


# Zu jedem Baum, der neu rot wird, gehoert einer, der nicht rot werden darf. Bei zwei
# Bedingungen sind das fuenf Baeume; der sechste ist die Gegenprobe auf der Seite der
# Bibliotheksquellen, damit der Umbau der Schleife die erste Haelfte nicht verliert.
BAEUME = [
    dict(nummer="B1", fassung="nachher", zulage=None, sanitizer=True, gruen=True,
         titel="Unveraendert + neuer Riegel, Testprofil -- muss gruen bleiben"),
    dict(nummer="B2", fassung="nachher", zulage=None, sanitizer=False, gruen=True,
         titel="Unveraendert + neuer Riegel, Freigabeprofil -- muss gruen bleiben"),
    dict(nummer="B3", fassung="vorher", zulage=('test/luecke_ohne_sperre_probe.cpp', 'luecke_ohne_sperre_probe.cpp'), sanitizer=True,
         gruen=True,
         titel="Probe ohne Sperre + alter Riegel -- Kontrolle, muss gruen sein"),
    dict(nummer="B4", fassung="nachher", zulage=('test/luecke_ohne_sperre_probe.cpp', 'luecke_ohne_sperre_probe.cpp'), sanitizer=True,
         gruen=False, enthaelt=["'test/luecke_ohne_sperre_probe.cpp'",
                                "Die fehlende Zeile"],
         titel="Probe ohne Sperre + neuer Riegel -- muss beim Konfigurieren abbrechen"),
    dict(nummer="B5", fassung="vorher", zulage=('test/luecke_reihenfolge_probe.cpp', 'luecke_reihenfolge_probe.cpp'), sanitizer=True,
         gruen=True,
         titel="Probe mit Sperre nicht zuletzt + alter Riegel -- Kontrolle, gruen"),
    dict(nummer="B6", fassung="nachher", zulage=('test/luecke_reihenfolge_probe.cpp', 'luecke_reihenfolge_probe.cpp'), sanitizer=True,
         gruen=False, enthaelt=["'test/luecke_reihenfolge_probe.cpp'",
                                "aber nicht als letzten"],
         titel="Probe mit Sperre nicht zuletzt + neuer Riegel -- muss abbrechen"),
    dict(nummer="B7", fassung="nachher", zulage=('src/luecke_quelle.cpp', 'luecke_quelle.cpp'), sanitizer=True,
         gruen=False, enthaelt=["'src/luecke_quelle.cpp'", "Die fehlende Zeile"],
         titel="Quelle ohne Sperre + neuer Riegel -- die erste Haelfte haelt weiter"),
]


def main() -> int:
    fehlend = [p for p in (FASSUNG["vorher"], FASSUNG["nachher"], PROBEN) if not p.exists()]
    if fehlend:
        print("Fehlende Nachweisdatei(en): %s" % fehlend)
        return 2

    abweichungen = []
    for baum in BAEUME:
        abweichungen += fahre(baum)

    print("")
    for satz in abweichungen:
        print("ABWEICHUNG: " + satz)
    print("Abweichungen: %d" % len(abweichungen))
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
