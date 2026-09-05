#!/usr/bin/env python3
"""Nachweis zu Paket 0140 -- der Verlauf sammelt die Rundenketten.

Faehrt vier Baeume in einem Aufruf und endet mit einer Zahl:

  vorher/nachher  x  FABRIK_SANITIZER=ON/OFF

Der Baum *vorher* ist derselbe Arbeitsbaum ohne die drei Dateien dieses Pakets --
nicht ein Git-Stand: Ein Fremdlauf, der mitten im Lauf committet, verschiebt HEAD, die
Kopie nicht. Kopiert wird nur `kern/` und `werkzeugkette.cmake`, ohne den Bauordner;
`kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein.

Geprueft wird:

  1. Konfigurieren, Bauen und ctest je Code 0 -- in allen vier Baeumen.
  2. Die Zahl der ctest-Eintraege steigt von *vorher* nach *nachher* um genau eins,
     je Profil gegen denselben Baum und dasselbe Profil.
  3. Die Ausgabe der drei Proben, die den Zustand rechnen, ist zwischen *vorher* und
     *nachher* zeichengleich -- darin stehen die Pruefsummen der Partie.
"""

import datetime
import os
import pathlib
import shutil
import subprocess

WURZEL = pathlib.Path(__file__).resolve().parents[2]
NEUE_DATEIEN = [
    "kern/include/kern/verlauf.hpp",
    "kern/src/verlauf.cpp",
    "kern/test/verlauf_probe.cpp",
]
ZUSTANDSPROBEN = ["schritt_probe", "zustand_probe", "zustandsausgabe_probe"]
TMP = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0140"
HEUTE = datetime.date.today().isoformat()
GITSTAND = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=str(WURZEL),
                          capture_output=True, text=True).stdout.strip() or "unbekannt"


def baum_anlegen(name, mit_neuen):
    """Legt einen Wegwerfbaum unter TMPDIR an -- nur `kern/` und die Werkzeugkette."""
    ziel = TMP / name
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.mkdir(parents=True)
    shutil.copytree(WURZEL / "kern", ziel / "kern",
                    ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WURZEL / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")
    if not mit_neuen:
        for datei in NEUE_DATEIEN:
            (ziel / datei).unlink()
    return ziel


def lauf(befehl):
    ergebnis = subprocess.run(befehl, capture_output=True, text=True)
    return ergebnis.returncode, ergebnis.stdout + ergebnis.stderr


def ctest_eintraege(bau):
    code, aus = lauf(["ctest", "--test-dir", str(bau), "-N"])
    zahl = sum(1 for zeile in aus.splitlines() if zeile.strip().startswith("Test  #")
               or zeile.strip().startswith("Test #"))
    return code, zahl, aus


def messe(name, mit_neuen, profil):
    """Konfiguriert, baut und testet einen Baum; gibt alles zurueck, was verglichen wird."""
    baum = baum_anlegen("{0}-{1}".format(name, profil.lower()), mit_neuen)
    bau = baum / "bau"
    protokoll = []
    for befehl in (
        ["cmake", "-S", str(baum / "kern"), "-B", str(bau),
         "-DFABRIK_SANITIZER=" + profil],
        ["cmake", "--build", str(bau), "-j", "4"],
        ["ctest", "--test-dir", str(bau), "--output-on-failure"],
    ):
        code, aus = lauf(befehl)
        protokoll.append((befehl[0] + " " + befehl[1], code, aus))
        if code != 0:
            return {"baum": baum, "protokoll": protokoll, "eintraege": -1, "proben": {}}

    _, eintraege, _ = ctest_eintraege(bau)
    proben = {}
    for probe in ZUSTANDSPROBEN + (["verlauf_probe"] if mit_neuen else []):
        code, aus = lauf([str(bau / probe)])
        proben[probe] = (code, aus)
    return {"baum": baum, "protokoll": protokoll, "eintraege": eintraege, "proben": proben}


def arbeitsbereich(profil):
    """Derselbe Lauf am echten Arbeitsbereich -- dort greifen auch die beiden Riegel
    ueber Belegstellen und Bezeichner, die der Alleinbau des Kerns nicht kennt."""
    bau = TMP / ("arbeitsbereich-" + profil.lower())
    if bau.exists():
        shutil.rmtree(bau)
    protokoll = []
    for befehl in (
        ["cmake", "-S", str(WURZEL), "-B", str(bau), "-DFABRIK_SANITIZER=" + profil],
        ["cmake", "--build", str(bau), "-j", "4"],
        ["ctest", "--test-dir", str(bau), "--output-on-failure"],
    ):
        code, aus = lauf(befehl)
        protokoll.append((befehl[0] + " " + befehl[1], code, aus))
        if code != 0:
            return protokoll, -1
    _, eintraege, _ = ctest_eintraege(bau)
    return protokoll, eintraege


def marken(protokoll, zeilen=8):
    """Die letzten Zeilen je Schritt -- ohne sie steht bei einem Abbruch nur `Code 1` da."""
    stuecke = []
    for schritt, code, aus in protokoll:
        letzte = [z for z in aus.splitlines() if z.strip()][-zeilen:]
        stuecke.append("### {0} -- Code {1}\n\n```\n{2}\n```\n".format(
            schritt, code, "\n".join(letzte)))
    return "\n".join(stuecke)


def hauptlauf():
    abweichungen = 0
    zeilen = []
    stand = {}

    for profil in ("ON", "OFF"):
        vorher = messe("vorher", False, profil)
        nachher = messe("nachher", True, profil)

        for name, ergebnis in (("vorher", vorher), ("nachher", nachher)):
            for schritt, code, _ in ergebnis["protokoll"]:
                if code != 0:
                    abweichungen += 1
                    zeilen.append("ROT  {0} {1}: {2} Code {3}".format(
                        name, profil, schritt, code))


        if vorher["eintraege"] < 0 or nachher["eintraege"] < 0:
            abweichungen += 1
            zeilen.append("ROT  {0}: ein Baum kam nicht bis zum ctest".format(profil))
            continue

        gestiegen = nachher["eintraege"] - vorher["eintraege"]
        if gestiegen != 1:
            abweichungen += 1
        zeilen.append("{0} ctest-Eintraege {1}: vorher {2}, nachher {3}, Zuwachs {4} "
                      "(erwartet 1)".format("OK  " if gestiegen == 1 else "ROT ", profil,
                                            vorher["eintraege"], nachher["eintraege"],
                                            gestiegen))

        for probe in ZUSTANDSPROBEN:
            links = vorher["proben"].get(probe)
            rechts = nachher["proben"].get(probe)
            gleich = links is not None and links == rechts
            if not gleich:
                abweichungen += 1
            zeilen.append("{0} {1} {2}: Ausgabe vorher/nachher {3}".format(
                "OK  " if gleich else "ROT ", profil, probe,
                "zeichengleich" if gleich else "VERSCHIEDEN"))


        arbeit, arbeit_eintraege = arbeitsbereich(profil)
        for schritt, code, _ in arbeit:
            if code != 0:
                abweichungen += 1
        rot = any(code != 0 for _, code, _ in arbeit)
        zeilen.append("{0} Arbeitsbereich {1}: cmake/build/ctest je Code 0, "
                      "{2} ctest-Eintraege".format("ROT " if rot else "OK  ", profil,
                                                   arbeit_eintraege))
        stand[profil] = (vorher, nachher, arbeit)

    bericht = ["# Messung zu Paket 0140 -- Nachweis", ""]
    bericht.append("Erzeugt von `befunde/messung-0140/nachweis.py`. Vier Wegwerfbaeume "
                   "unter TMPDIR plus zweimal der Arbeitsbereich, je `cmake -S`, "
                   "`cmake --build`, `ctest`.")
    bericht.append("")
    bericht.append("**Bezugsstand.** Der Baum *vorher* ist der Arbeitsbaum dieses Laufs "
                   "ohne die drei Dateien des Pakets -- also der unmittelbar "
                   "vorhergehende Stand desselben Baums. Gemessen am {0}, Git-Stand "
                   "`{1}` (er kann waehrend des Laufs weiterwandern; massgeblich ist "
                   "die Kopie, nicht der Verweis).".format(HEUTE, GITSTAND))
    bericht.append("")
    bericht.append("## Ergebnis")
    bericht.append("")
    bericht.append("```")
    bericht.extend(zeilen)
    bericht.append("Abweichungen: {0}".format(abweichungen))
    bericht.append("```")

    for profil in ("ON", "OFF"):
        if profil not in stand:
            continue
        vorher, nachher, _ = stand[profil]
        bericht.append("")
        bericht.append("## FABRIK_SANITIZER={0}, Baum nachher".format(profil))
        bericht.append("")
        bericht.append(marken(nachher["protokoll"]))
        bericht.append("### Die neue Probe im Wortlaut -- beide Seiten jeder Schranke")
        bericht.append("")
        bericht.append("```")
        bericht.append("Code {0}".format(nachher["proben"]["verlauf_probe"][0]))
        bericht.append(nachher["proben"]["verlauf_probe"][1].rstrip())
        bericht.append("```")
        bericht.append("")
        if nachher["proben"].get("schritt_probe"):
            bericht.append("### Pruefsummen der Partie (schritt_probe), "
                           "vorher und nachher gleich")
            bericht.append("")
            bericht.append("```")
            for zeile in nachher["proben"]["schritt_probe"][1].splitlines():
                if "Pruefsumme" in zeile:
                    bericht.append(zeile)
            bericht.append("```")

    pfad = pathlib.Path(__file__).resolve().parent / "bericht.md"
    pfad.write_text("\n".join(bericht) + "\n", encoding="utf-8")
    print("\n".join(zeilen))
    print("Abweichungen: {0}".format(abweichungen))
    print("Bericht: {0}".format(pfad))
    return abweichungen


if __name__ == "__main__":
    raise SystemExit(1 if hauptlauf() else 0)
