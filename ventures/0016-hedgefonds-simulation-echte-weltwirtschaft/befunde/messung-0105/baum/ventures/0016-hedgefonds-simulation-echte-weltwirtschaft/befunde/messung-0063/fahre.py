#!/usr/bin/env python3
"""Faehrt die sechs Wegwerf-Baeume zu Paket 0063 gegen EINE Fassung der Werkzeugkette.

Aufruf:  python3 fahre.py <kette.cmake> <marke>

`<marke>` ist `vorher` oder `nachher` und geht in die Namen der Bauverzeichnisse ein.
Es wird kein Verzeichnis geloescht -- jede Marke bekommt ihr eigenes, damit kein
Zwischenstand aus einem frueheren Lauf das Ergebnis traegt.

Konfiguriert wird mit derselben Zeile wie `agents/baulauf.py:162-164`, sonst misst der
Nachweis eine Umgebung, die im Nachtlauf nie vorkommt.
"""
import subprocess
import sys
import pathlib

HIER = pathlib.Path(__file__).resolve().parent
RUNNER = ["-DCMAKE_BUILD_TYPE=RelWithDebInfo", "-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math"]

# (Verzeichnis, Profilschalter, ob nach der Konfiguration gebaut wird)
FAELLE = [
    ("a_shell", RUNNER, True),
    ("b_genex", RUNNER, True),
    # `$<$<CONFIG:Release>:-w>` wirkt nur unter `Release`. Unter der Zeile des Runners
    # (`RelWithDebInfo`) traegt der Uebersetzer den Schalter gar nicht -- gemessen wird
    # deshalb beides: die Konfiguration unter der Runner-Zeile und, getrennt, der stille
    # Bau unter `Release`, wo der Abschalter tatsaechlich ankommt.
    ("c_genex_config", RUNNER, False),
    ("c_genex_config", ["-DCMAKE_BUILD_TYPE=Release",
                        "-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math"], True),
    ("d_0060", RUNNER, False),
    ("e_einzeln", RUNNER, True),
    ("f_ohne", RUNNER, True),
]


def lauf(befehl):
    fertig = subprocess.run(befehl, capture_output=True, text=True,
                            encoding="utf-8", errors="replace", timeout=600)
    return fertig.returncode, (fertig.stdout or "") + (fertig.stderr or "")


def main():
    kette, marke = pathlib.Path(sys.argv[1]).resolve(), sys.argv[2]
    zeilen = ["# Wegwerf-Baeume zu 0063 -- Fassung `%s`" % marke, "",
              "Kette: `%s`" % kette, ""]
    nummer = 0
    for name, profil, bauen in FAELLE:
        nummer += 1
        quelle = HIER / name
        bau = HIER / name / ("bau-%s-%d" % (marke, nummer))
        code, text = lauf(["cmake", "-S", str(quelle), "-B", str(bau)]
                          + profil + ["-DFABRIK_KETTE=" + str(kette)])
        zeilen.append("## %d. `%s` -- %s" % (nummer, name, profil[0]))
        zeilen.append("")
        zeilen.append("`cmake -S` **CODE=%d**" % code)
        zeilen.append("")
        zeilen.append("```")
        zeilen.append(text.strip())
        zeilen.append("```")
        zeilen.append("")
        if bauen and code == 0:
            bcode, btext = lauf(["cmake", "--build", str(bau)])
            zeilen.append("`cmake --build` **CODE=%d**" % bcode)
            zeilen.append("")
            zeilen.append("```")
            zeilen.append(btext.strip())
            zeilen.append("```")
            zeilen.append("")
        elif bauen:
            zeilen.append("Kein Bau: die Konfiguration ist schon abgebrochen.")
            zeilen.append("")
        print("%-16s %-28s cmake -S CODE=%d" % (name, profil[0], code))
    ziel = HIER / ("protokoll-faelle-%s.md" % marke)
    ziel.write_text("\n".join(zeilen) + "\n", encoding="utf-8")
    print("geschrieben:", ziel)


main()
