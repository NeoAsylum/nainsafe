#!/usr/bin/env python3
"""Vorentscheidung zu Paket 0124: Welche Uebergabeform bildet die Abschrift ab?

Die zwei Abschriften der Zerlegung bekommen ihre Eingabe einmal aus `list(GET ...)`
und einmal aus einer `foreach`-Variablen. Eine benannte Folge kann sie auf zwei Wegen
entgegennehmen -- als **Wert** oder als **Name** der Variablen.

Gemessen wird beides **gegen die eingebaute Abschrift** an denselben Eingaben. Eine
Form, die an irgendeiner Eingabe eine andere Wortliste liefert als die Abschrift,
aendert Verhalten -- und genau das darf dieses Paket nicht.

    python3 befunde/messung-0124/uebergabeform.py

Rueckgabe 0 heisst: kein Unterschied, oder der Bericht nennt jeden.
"""
import os
import subprocess
import sys
from pathlib import Path

# Die Eingaben stehen als CMake-Quelltext da: gemessen wird die Zerlegung genau der
# Zeile, die ein Manifest schreiben wuerde -- Anfuehrung, Fluchtzeichen, Semikolon
# (CMakes Listentrenner), Generatorausdruck, leer, dazu die Abnahmematrix.
EINGABEN = [
    ('schlicht', '-Wl,-lz'),
    ('anfuehrung', '-DX=\\"a b\\"'),
    ('backslash', '-DPFAD=a\\\\b'),
    ('semikolon', '-a;-b'),
    ('generator', '$<1:-lz>'),
    ('shellpraefix', 'SHELL:-Wl,-lz'),
    ('leer', ''),
    ('nurkommas', ',,,'),
    ('getrenntes_l', '-Wl,-l,z'),
    ('pfad', '/usr/lib/libz.so'),
    ('sanitizer', '-fsanitize=undefined,address'),
]

KOPF = """cmake_minimum_required(VERSION 3.22)
project(uebergabeform NONE)

# Die eingebaute Abschrift -- der Stand vor Paket 0124, Zeichen fuer Zeichen.
macro(abschrift_inline)
  string(REPLACE "SHELL:" " " zerlegt "${eingabe}")
  string(REGEX REPLACE "[$<>:,]" " " zerlegt "${zerlegt}")
  separate_arguments(worte UNIX_COMMAND "${zerlegt}")
endmacro()

# Form A: der Wert wird uebergeben.
macro(form_wert wortliste eingabewert)
  string(REPLACE "SHELL:" " " fabrik_zerlegt "${eingabewert}")
  string(REGEX REPLACE "[$<>:,]" " " fabrik_zerlegt "${fabrik_zerlegt}")
  separate_arguments(${wortliste} UNIX_COMMAND "${fabrik_zerlegt}")
endmacro()

# Form B: der Name der Eingabevariablen wird uebergeben.
macro(form_name wortliste eingabename)
  string(REPLACE "SHELL:" " " fabrik_zerlegt "${${eingabename}}")
  string(REGEX REPLACE "[$<>:,]" " " fabrik_zerlegt "${fabrik_zerlegt}")
  separate_arguments(${wortliste} UNIX_COMMAND "${fabrik_zerlegt}")
endmacro()
"""

# Je Form ein eigener Baum, und in jedem steht die Abschrift daneben. Sonst verdeckt
# ein Abbruch der einen Form die Messung der anderen -- genau das ist am 2026-09-06 an
# der Eingabe `backslash` passiert.
FALL_ABSCHRIFT = """
set(eingabe "@WERT@")
abschrift_inline()
message(STATUS "@NAME@ abschrift [${worte}]")
"""

FALL_WERT = """
form_wert(wa "${eingabe}")
message(STATUS "@NAME@ wert [${wa}]")
"""

FALL_NAME = """
form_name(wb eingabe)
message(STATUS "@NAME@ name [${wb}]")
"""


def fahren(ablage, name, wert, anhang, marke):
    text = (KOPF
            + FALL_ABSCHRIFT.replace("@WERT@", wert).replace("@NAME@", name)
            + anhang.replace("@WERT@", wert).replace("@NAME@", name))
    d = ablage / (name + "-" + marke)
    d.mkdir(parents=True, exist_ok=True)
    (d / "CMakeLists.txt").write_text(text)
    lauf = subprocess.run(["cmake", "-S", str(d), "-B", str(d / "build")],
                          capture_output=True, text=True)
    ganz = lauf.stdout + lauf.stderr
    (d / "konfig.log").write_text(ganz)
    return lauf.returncode, ganz


def lesen(text):
    gelesen = {}
    for zeile in text.splitlines():
        roh = zeile.strip()
        if not roh.startswith("-- "):
            continue
        teile = roh[3:].split(" ", 2)
        if len(teile) == 3 and teile[1] in ("abschrift", "wert", "name"):
            gelesen[teile[1]] = teile[2].strip()
    return gelesen


def fehlerzeilen(text):
    return [s.strip()[:150] for s in text.splitlines()
            if "Error" in s or "Invalid" in s][:2]


def main():
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / "messung0124-uebergabe"
    # Gezaehlt wird die **gewaehlte** Form. Die verworfene wird trotzdem gefahren:
    # Ohne einen Fall, an dem sie wirklich anders ausgeht, waere die Wahl unbelegt.
    abweichungen = 0
    wertfaelle = []
    for name, wert in EINGABEN:
        cw, tw = fahren(ablage, name, wert, FALL_WERT, "wert")
        cn, tn = fahren(ablage, name, wert, FALL_NAME, "name")
        gw, gn = lesen(tw), lesen(tn)
        soll = gn.get("abschrift")
        a, b = gw.get("wert"), gn.get("name")
        if b != soll or soll is None:
            abweichungen += 1
        if a != soll:
            wertfaelle.append(name)
        print(("  " if b == soll and soll is not None else "!!") + " " + name.ljust(14)
              + " eingabe=" + repr(wert))
        print("     Abschrift=" + str(soll) + "  (code " + str(cn) + ")")
        print("     Form Name=" + str(b) + "  (code " + str(cn) + ")"
              + ("" if b == soll else "   <-- weicht ab"))
        for s in fehlerzeilen(tn):
            print("        " + s)
        print("     Form Wert=" + str(a) + "  (code " + str(cw) + ")"
              + ("" if a == soll else "   <-- weicht ab, siehe unten"))
        for s in fehlerzeilen(tw):
            print("        " + s)


    print("")
    print("Gewaehlt ist die Form Name -- sie bildet die Abschrift an jeder Eingabe ab.")
    print("Die Form Wert weicht ab bei: "
          + (", ".join(wertfaelle) if wertfaelle else "KEINER -- die Wahl waere unbelegt"))
    if not wertfaelle:
        abweichungen += 1
    print("Abweichungen: " + str(abweichungen))
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
