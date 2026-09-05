#!/usr/bin/env python3
"""Die drei Bauwege in beiden Profilen -- an einem Baum, in dem **nur** diese eine
Datei geaendert ist.

Warum es diese zweite Messung neben `befunde/messung-0076/bauwege.py` gibt: Am
2026-09-05 lagen waehrend des Baulaufs von Paket 0108 vier fremde Aenderungen
unversioniert im Arbeitsbereich (`CMakeLists.txt`, `daten/reihen.toml`,
`werkzeuge/belegstellen/belegstellen_riegel.cpp`,
`werkzeuge/bezeichner/bezeichner_riegel.cpp`) -- andere Agenten arbeiteten gleichzeitig.
Eine davon uebersetzte im Profil `FABRIK_SANITIZER=OFF` nicht
(`belegstellen_riegel.cpp:1508: 'absatz_aus_fall' defined but not used`, unter
`-Werror`). Am Arbeitsbereich gemessen faellt dieser Bauweg rot aus, und das Rot
gehoerte nicht zu dieser Aenderung.

Dieses Skript trennt beides. Es packt den Vorhabensbaum mit `git archive` aus einem
Commit aus -- also **ohne** die fremden Halbstaende --, legt ihn zweimal hin und
setzt in **beide** Kopien `werkzeugkette.cmake` ausdruecklich: in `vorher` die
eingefrorene Fassung `befunde/messung-0108/werkzeugkette-vorher.cmake`, in `nachher`
die aus dem Arbeitsbereich. Danach faehrt es beide Baeume ueber dieselben sechs
Kombinationen aus Bauweg und Profil und vergleicht Konfigurations-, Bau- und
`ctest`-Code sowie die Zahl uebersetzender Ziele.

**Warum beide Kopien gesetzt werden und nicht nur die zweite** (geaendert am
2026-09-05, nachdem die Aenderung committet war): Bis dahin nahm `vorher` die Fassung
aus dem Commit. Sobald die Aenderung in `HEAD` steht, ist das dieselbe Datei wie im
Arbeitsbereich -- die zwei Baeume sind gleich, und die Messung sagt nichts mehr. Wer
stattdessen einen aelteren Commit waehlt, um an die alte Fassung zu kommen, nimmt
dessen ganzen uebrigen Baum mit, und der kann aus fremdem Grund rot sein.
Gemessen am 2026-09-05: aus `4ee0f79` ausgepackt uebersetzte der Bauweg
`arbeitsbereich` in beiden Profilen nicht --
`werkzeuge/belegstellen/belegstellen_riegel.cpp:1824: too many initializers for
'std::__array_traits<...>'`, an beiden Staenden dieselbe Zeile. Ab hier ist der
Commit allein die **Umgebung**; welche zwei Fassungen verglichen werden, haengt nicht
mehr an ihm.

Zwei Aussagen kommen dabei heraus, und beide werden gebraucht:

1. **Kein Urteil aendert sich** -- jede der sechs Kombinationen meldet vorher wie
   nachher dasselbe. Das ist Abnahmebedingung 3 des Pakets.
2. **Der Bauweg, der am Arbeitsbereich rot ist, ist hier gruen** -- also liegt sein
   Rot an einer fremden Datei und nicht an dieser Aenderung.

Aufruf aus WSL heraus:

    python3 befunde/messung-0108/bauwege-isoliert.py            # Umgebung aus HEAD
    python3 befunde/messung-0108/bauwege-isoliert.py 456aefa    # Umgebung aus 456aefa

Das Argument waehlt allein die Umgebung. Nimm einen Commit, dessen uebriger Baum
gruen uebersetzt -- sonst ist das Rot des Bauwegs `arbeitsbereich` an beiden Staenden
dasselbe und sagt ueber diese Aenderung nichts.

Rueckgabe 0 heisst: kein Unterschied zwischen den Staenden, und jeder Code 0.
"""

import os
import subprocess
import sys
import re
import shutil
import tarfile
from io import BytesIO
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
# Die zwei verglichenen Fassungen stehen hier und kommen nicht aus dem Commit -- die
# Begruendung steht oben im Kopf dieser Datei.
KETTE_NACHHER = WURZEL / "werkzeugkette.cmake"
KETTE_VORHER = Path(__file__).resolve().parent / "werkzeugkette-vorher.cmake"
WEGE = {"arbeitsbereich": ".", "kern": "kern", "pruefstand": "pruefstand"}
PROFILE = ("ON", "OFF")
ZIELZAHL = re.compile(r"(\d+) uebersetzende Ziele")


def git(argumente, cwd):
    r = subprocess.run(["git"] + argumente, cwd=str(cwd), capture_output=True, text=True)
    if r.returncode != 0:
        raise SystemExit("git " + " ".join(argumente) + " -> " + r.stderr.strip())
    return r.stdout.strip()


def auspacken(commit, ziel):
    """Den Vorhabensbaum aus `commit` nach `ziel` auspacken -- ohne Arbeitsstaende.

    Derselbe Weg wie in `befunde/messung-0076/bauwege.py`: Der Pfad des Vorhabens
    innerhalb des Repos wird abgeschnitten, damit die Wurzel des Wegwerf-Baums die
    Wurzel des Vorhabens ist. `kern/CMakeLists.txt` bindet `../werkzeugkette.cmake`
    ein, also traegt keine andere Gestalt.
    """
    oberstes = Path(git(["rev-parse", "--show-toplevel"], WURZEL))
    innen = WURZEL.relative_to(oberstes).as_posix()
    argumente = ["archive", "--format=tar", commit]
    if innen != ".":
        argumente.append(innen)
    r = subprocess.run(["git"] + argumente, cwd=str(oberstes), capture_output=True)
    if r.returncode != 0:
        raise SystemExit("git archive " + commit + " -> " + r.stderr.decode(errors="replace"))
    praefix = "" if innen == "." else innen + "/"
    ziel.mkdir(parents=True, exist_ok=True)
    with tarfile.open(fileobj=BytesIO(r.stdout)) as tar:
        glieder = []
        for g in tar.getmembers():
            if praefix and not g.name.startswith(praefix):
                continue
            g.name = g.name[len(praefix):] or "."
            glieder.append(g)
        if not glieder:
            raise SystemExit("git archive lieferte unter " + praefix + " keine Datei")
        tar.extractall(str(ziel), members=glieder, filter="data")


def fahren(quelle, bau, wert, log):
    e = {}
    rk = subprocess.run(["cmake", "-S", str(quelle), "-B", str(bau),
                         "-DFABRIK_SANITIZER=" + wert], capture_output=True, text=True)
    txt = rk.stdout + rk.stderr
    (log.parent / (log.name + "-konfig.log")).write_text(txt)
    treffer = ZIELZAHL.findall(txt)
    e["konfig"] = rk.returncode
    e["ziele"] = int(treffer[0]) if len(treffer) == 1 else None
    rb = subprocess.run(["cmake", "--build", str(bau), "-j", "4"],
                        capture_output=True, text=True)
    (log.parent / (log.name + "-bau.log")).write_text(rb.stdout + rb.stderr)
    e["bau"] = rb.returncode
    e["baufehler"] = [t.strip()[:150] for t in (rb.stdout + rb.stderr).splitlines()
                      if "error:" in t][:2]
    rt = subprocess.run(["ctest", "--test-dir", str(bau), "--output-on-failure",
                         "--no-tests=error"], capture_output=True, text=True)
    ttxt = rt.stdout + rt.stderr
    (log.parent / (log.name + "-ctest.log")).write_text(ttxt)
    e["ctest"] = rt.returncode
    e["bilanz"] = " | ".join(t.strip() for t in ttxt.splitlines()
                             if "tests passed" in t or "No tests were found" in t)
    return e


def main():
    commit = sys.argv[1] if len(sys.argv) > 1 else "HEAD"
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / "isoliert0108"
    if ablage.exists():
        shutil.rmtree(ablage)
    rein = ablage / "rein"
    auspacken(commit, rein)
    kennung = git(["rev-parse", "--short", commit], WURZEL)

    baeume = {}
    for stand in ("vorher", "nachher"):
        b = ablage / stand
        shutil.copytree(rein, b)
        baeume[stand] = b
    # Genau eine Datei unterscheidet die beiden Baeume. Nachgewiesen und nicht beteuert:
    # die Liste der Unterschiede wird unten gedruckt.
    for stand, kette in (("vorher", KETTE_VORHER), ("nachher", KETTE_NACHHER)):
        if not kette.is_file():
            print("FEHLT: " + str(kette))
            return 2
        (baeume[stand] / "werkzeugkette.cmake").write_bytes(kette.read_bytes())
    r = subprocess.run(["diff", "-rq", str(baeume["vorher"]), str(baeume["nachher"])],
                       capture_output=True, text=True)
    unterschiede = [t for t in r.stdout.splitlines() if t.strip()]
    print("Ausgepackt aus " + kennung + " nach " + str(rein))
    print("Unterschied zwischen den zwei Baeumen (" + str(len(unterschiede)) + "):")
    for t in unterschiede:
        print("   " + t)
    if len(unterschiede) != 1 or "werkzeugkette.cmake" not in unterschiede[0]:
        print("!! Die Baeume unterscheiden sich nicht in genau dieser einen Datei.")
        return 2
    print("")

    fehler = 0
    for wert in PROFILE:
        for name, unter in WEGE.items():
            ergebnisse = {}
            for stand in ("vorher", "nachher"):
                log = ablage / (wert + "-" + name + "-" + stand)
                ergebnisse[stand] = fahren(baeume[stand] / unter,
                                           ablage / ("bau-" + wert + "-" + name + "-" + stand),
                                           wert, log)
            v, n = ergebnisse["vorher"], ergebnisse["nachher"]
            gleich = all(v[s] == n[s] for s in ("konfig", "ziele", "bau", "ctest"))
            alles_gruen = all(n[s] == 0 for s in ("konfig", "bau", "ctest"))
            if not gleich or not alles_gruen:
                fehler += 1
            print(("!! " if (not gleich or not alles_gruen) else "   ")
                  + ("FABRIK_SANITIZER=" + wert).ljust(24) + name.ljust(16))
            for stand in ("vorher", "nachher"):
                e = ergebnisse[stand]
                print("        " + stand.ljust(8) + " konfig=" + str(e["konfig"])
                      + " ziele=" + str(e["ziele"]) + " bau=" + str(e["bau"])
                      + " ctest=" + str(e["ctest"]) + "   " + e["bilanz"])
                for t in e["baufehler"]:
                    print("                 " + t)

    print("")
    print(str(fehler) + " Abweichung(en). Ablage: " + str(ablage))
    return 1 if fehler else 0


if __name__ == "__main__":
    raise SystemExit(main())
