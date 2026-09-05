#!/usr/bin/env python3
"""Der Nachweis zu Paket 0108 -- die `-NOTFOUND`-Endungsfalle an zwei weiteren Stellen.

Er faehrt jeden Wegwerf-Baum **zweimal**: einmal gegen
`befunde/messung-0108/werkzeugkette-vorher.cmake` (der eingefrorene Stand vor der
Aenderung, md5 5505cf7704b164d9ce44fda58f7895ca, 55139 Bytes, Kopie vom 2026-09-05
aus dem Arbeitsbereich) und einmal gegen die Fassung im Arbeitsbereich. Verglichen
wird gegen eine Sollspalte je Stand -- ein Baum, der vorher wie nachher rot ist,
belegt fuer sich genommen nichts.

Eingefroren wird als **Kopie** und nicht als Git-Stand: Ein Fremdlauf, der mitten in
der Messung committet, verschiebt `HEAD`, die Kopie nicht.

Aufruf aus WSL heraus:

    python3 befunde/messung-0108/endungsfalle.py

Rueckgabe 0 heisst: keine Abweichung vom Soll, an beiden Staenden.
"""

import os
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
KETTE_NACHHER = WURZEL / "werkzeugkette.cmake"
KETTE_VORHER = Path(__file__).resolve().parent / "werkzeugkette-vorher.cmake"

# Sauber unter dem Warnsatz: keine Umwandlung, kein alter Umwandlungsstil. Sonst
# wuerde ein Kontrollbaum am Uebersetzer rot statt am Riegel -- und belegte nichts.
QUELLE = "int f(int i){ return i + 1; }" + chr(10)
ZWEITE = "int g(int i){ return i + 2; }" + chr(10)

SATZ_Z = "add_library(z STATIC z.cpp)\nfabrik_warnsatz_anlegen(z)\n"
SATZ_K = "add_library(kern STATIC z.cpp)\nfabrik_warnsatz_anlegen(kern)\n"


def quellenbaum(zweitname):
    """Befund 1: eine zweite Quelldatei, deren **Name** die Falle stellt.

    Die zwei Baeume unterscheiden sich durch nichts als diesen Namen. Die
    Eigenschaft, die der Riegel finden muss, haengt an `z.cpp` und ist in beiden
    Faellen dieselbe.
    """
    rumpf = (SATZ_Z
             + "set_source_files_properties(" + zweitname + " PROPERTIES LANGUAGE CXX)\n"
             + "target_sources(z PRIVATE " + zweitname + ")\n"
             + 'set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")\n')
    return {zweitname: ZWEITE}, rumpf


# name -> (soll vorher, soll nachher, zusatzdateien, rumpf, erwartete Marke nachher)
#
# Die Ruempfe stehen vollstaendig da und nicht als Schablone -- wer den Fall in drei
# Monaten liest, soll ihn abschreiben koennen, ohne dieses Skript zu verstehen.
BAEUME = {
    # --- Abnahmebedingung 1: die verdeckte Quelldatei
    "q1_notfound": (0, 1) + quellenbaum("y-NOTFOUND") + ("COMPILE_FLAGS an ",),
    "q2_harmlos": (1, 1) + quellenbaum("y-HARMLOS") + ("COMPILE_FLAGS an ",),
    # Gegenprobe: ohne den Abschalter darf kein Stand rot werden. Sonst wirkte die
    # Aenderung womoeglich dadurch, dass sie alles faengt.
    "q3_sauber": (0, 0, {"y-NOTFOUND": ZWEITE},
                  SATZ_Z
                  + "set_source_files_properties(y-NOTFOUND PROPERTIES LANGUAGE CXX)\n"
                  + "target_sources(z PRIVATE y-NOTFOUND)\n", ""),

    # --- Abnahmebedingung 2: der verdeckte Linkschalter
    "l1_notfound": (0, 1, {}, SATZ_K
                    + "target_link_options(kern PRIVATE -lfremd -Wl,-rpath,/x-NOTFOUND)\n",
                    "kern: LINK_OPTIONS nennt -lfremd"),
    "l2_klar": (1, 1, {}, SATZ_K
                + "target_link_options(kern PRIVATE -lfremd -Wl,-rpath,/x)\n",
                "kern: LINK_OPTIONS nennt -lfremd"),
    # Der Unterschied zwischen "leer" und "geleert": derselbe Code an beiden Staenden,
    # aber eine andere Meldung. Vorher stand dort der geleerte Wert und war von einer
    # wirklich leeren Eigenschaft nicht zu unterscheiden.
    "l3_rpath_ohne_fremd": (0, 0, {}, SATZ_K
                            + "target_link_options(kern PRIVATE -Wl,-rpath,/x-NOTFOUND)\n",
                            "kern.LINK_OPTIONS=[-Wl,-rpath,/x-NOTFOUND]"),
    # Und die wirklich leere Eigenschaft bleibt `[]` -- sonst waere der Unterschied
    # nur verschoben statt aufgeloest.
    "l4_leer": (0, 0, {}, SATZ_K, "kern.LINK_OPTIONS=[]"),
    # Die gemessene Einschraenkung aus dem Paket: bei `LINK_LIBRARIES` faellt die Falle
    # heute nicht auf, weil CMake die PRIVATE-Eintraege als LINK_ONLY-Ausdruck nach
    # `INTERFACE_LINK_LIBRARIES` spiegelt und jene Zeichenkette auf > endet. Der Baum
    # steht hier, damit sein Urteil sich nicht heimlich aendert.
    "l5_libs": (1, 1, {}, SATZ_K
                + "find_library(GIBTSNICHT gibtsnichtxyz)\n"
                + "target_link_libraries(kern PRIVATE fremdlib ${GIBTSNICHT})\n",
                "kern: LINK_LIBRARIES nennt fremdlib"),
}


def schreiben(d, kette, zusatz, rumpf):
    d.mkdir(parents=True, exist_ok=True)
    (d / "z.cpp").write_text(QUELLE)
    for name, inhalt in zusatz.items():
        (d / name).write_text(inhalt)
    kopf = ("cmake_minimum_required(VERSION 3.22)\nproject(z LANGUAGES CXX)\n"
            "include(" + str(kette) + ")\n")
    (d / "CMakeLists.txt").write_text(kopf + rumpf)


def fahren(d):
    r = subprocess.run(["cmake", "-S", str(d), "-B", str(d / "build")],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    (d / "konfig.log").write_text(txt)
    # Die Marken sind der eigentliche Nachweis: Ein Baum kann an beiden Staenden
    # denselben Code melden und trotzdem etwas anderes aussagen.
    marken = [s.strip() for s in txt.splitlines()
              if ("gefunden in" in s and "Zeile" not in s)
              or "es fehlen:" in s
              or "Nullabhaengigkeitsriegel" in s
              or " nennt " in s]
    return r.returncode, marken


def main():
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / "messung0108"
    ablage.mkdir(parents=True, exist_ok=True)
    for kette in (KETTE_VORHER, KETTE_NACHHER):
        if not kette.is_file():
            print("FEHLT: " + str(kette))
            return 2

    abweichungen = 0
    for name in sorted(BAEUME):
        sollv, solln, zusatz, rumpf, marke = BAEUME[name]
        print("=== " + name)
        for stand, kette, soll in (("vorher", KETTE_VORHER, sollv),
                                   ("nachher", KETTE_NACHHER, solln)):
            d = ablage / (name + "-" + stand)
            schreiben(d, kette, zusatz, rumpf)
            code, marken = fahren(d)
            passt = (code != 0) == (soll != 0)
            # Die erwartete Marke wird nur am Stand "nachher" verlangt: Sie ist die
            # Aussage der Aenderung, nicht die des alten Standes.
            markepasst = True
            if stand == "nachher" and marke:
                markepasst = any(marke in m for m in marken)
            zeichen = "  " if (passt and markepasst) else "!!"
            if zeichen == "!!":
                abweichungen += 1
            print(zeichen + " " + stand.ljust(8) + " code=" + str(code)
                  + " (soll " + str(soll) + ")"
                  + ("" if markepasst else "   MARKE FEHLT: " + marke))
            for m in marken[:3]:
                print("          " + m[:170])

    print(chr(10) + str(abweichungen) + " Abweichung(en) vom Soll.")
    return 1 if abweichungen else 0


if __name__ == "__main__":
    raise SystemExit(main())
