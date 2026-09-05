#!/usr/bin/env python3
"""Faehrt die drei echten Bauwege zu Paket 0063 gegen EINE Fassung der Werkzeugkette.

Aufruf:  python3 bauwege.py <marke>

Anders als `fahre.py` wird hier die Kette NICHT ueber `-D` untergeschoben: Die drei
Baeume binden `werkzeugkette.cmake` selbst ein, und genau dieser Weg soll gemessen
werden. `<marke>` unterscheidet nur die Bauverzeichnisse; welche Fassung der Kette
gilt, entscheidet der Stand der Datei im Repo zum Zeitpunkt des Aufrufs.

Gesammelt wird ausserdem jede `CXX_FLAGS`-Zeile aus jeder erzeugten `flags.make` des
Arbeitsbereichs, mit dem Pfad als Praefix und sortiert. Der Pfad des Bauverzeichnisses
wird textlich auf `<BAU>` normalisiert -- sonst vergleicht der Bytevergleich die Marke
statt der Schalter.
"""
import subprocess
import sys
import pathlib
import re

HIER = pathlib.Path(__file__).resolve().parent
VENTURE = HIER.parent.parent
RUNNER = ["-DCMAKE_BUILD_TYPE=RelWithDebInfo", "-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math"]
WEGE = [("arbeitsbereich", VENTURE), ("kern", VENTURE / "kern"),
        ("pruefstand", VENTURE / "pruefstand")]


def lauf(befehl):
    fertig = subprocess.run(befehl, capture_output=True, text=True,
                            encoding="utf-8", errors="replace", timeout=900)
    return fertig.returncode, (fertig.stdout or "") + (fertig.stderr or "")


def flaggen(bau):
    """Jede CXX_FLAGS-Zeile jeder flags.make, mit Pfad als Praefix, sortiert."""
    zeilen = []
    for datei in sorted(bau.rglob("flags.make")):
        rel = datei.relative_to(bau).as_posix()
        for zeile in datei.read_text(encoding="utf-8", errors="replace").splitlines():
            if zeile.startswith("CXX_FLAGS"):
                zeilen.append(rel + "\t" + zeile.replace(str(bau), "<BAU>"))
    return sorted(zeilen)


def main():
    marke = sys.argv[1]
    zeilen = ["# Die drei Bauwege -- Fassung `%s`" % marke, ""]
    for name, quelle in WEGE:
        bau = HIER / ("bau-%s-%s" % (name, marke))
        code, text = lauf(["cmake", "-S", str(quelle), "-B", str(bau)] + RUNNER)
        riegel = [z for z in text.splitlines() if "Schlussriegel" in z]
        zahl = re.search(r"Schlussriegel: (\d+) ", " ".join(riegel))
        zeilen += ["## `%s`" % name, "", "`cmake -S` **CODE=%d**" % code, "",
                   "```", text.strip(), "```", ""]
        bcode = ccode = None
        if code == 0:
            bcode, btext = lauf(["cmake", "--build", str(bau), "--parallel"])
            zeilen += ["`cmake --build` **CODE=%d**" % bcode, "",
                       "```", btext.strip(), "```", ""]
            ccode, ctext = lauf(["ctest", "--test-dir", str(bau), "--output-on-failure"])
            zeilen += ["`ctest` **CODE=%d**" % ccode, "",
                       "```", ctext.strip(), "```", ""]
        print("%-15s cmake -S CODE=%s  build CODE=%s  ctest CODE=%s  Riegelzahl=%s"
              % (name, code, bcode, ccode, zahl.group(1) if zahl else "-"))
        if name == "arbeitsbereich" and code == 0:
            liste = flaggen(bau)
            (HIER / ("cxxflags-%s.txt" % marke)).write_text(
                "\n".join(liste) + "\n", encoding="utf-8")
            print("  CXX_FLAGS-Zeilen des Arbeitsbereichs:", len(liste))
    (HIER / ("protokoll-bauwege-%s.md" % marke)).write_text(
        "\n".join(zeilen) + "\n", encoding="utf-8")
    print("geschrieben: protokoll-bauwege-%s.md" % marke)


main()
