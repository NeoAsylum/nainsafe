#!/usr/bin/env python3
"""Nachweis zu Paket 0151 -- T48 Nr. 18 bis 20 in `kern::werte`.

Der Lauf beantwortet vier Fragen an einer Wegwerfkopie des Kerns, damit der
Arbeitsbaum unberuehrt bleibt:

  1. **Bestand.** Uebersetzt und besteht `ctest` in beiden Bauprofilen
     (`FABRIK_SANITIZER=ON` und `OFF`)?
  2. **Beisst die Probe?** Jede Mutation unten dreht genau eine Entscheidung der
     Vorgabe um. Wird sie nicht rot, prueft die zugehoerige Probe die Entscheidung
     nicht, sondern nur die Rechnung.
  3. **Riegel.** Belegstellen-, Bezeichner- und Sperrebindungsriegel mit Code 0.
  4. **Die drei Zahlwoerter.** `siebzehn` steht in `werte.hpp` genauso oft wie vor
     dem Paket -- die Zahl wird erst mit Paket 0152 richtig.

Aufruf ohne Argumente. Am Ende steht `Abweichungen: 0`, wenn alles stimmt.
"""

import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
SPECS = WURZEL.parents[1] / "specs" / WURZEL.name

abweichungen = 0


def melde(gut, text, beiwerk=""):
    global abweichungen
    if not gut:
        abweichungen += 1
    print(f"  [{'ok ' if gut else 'ABW'}] {text}")
    if beiwerk and not gut:
        for zeile in beiwerk.strip().splitlines()[-25:]:
            print(f"        {zeile}")


def frische_kopie(ziel):
    """Kern plus Werkzeugkette. Der Bauordner bleibt draussen -- er traegt
    absolute Pfade und macht die Kopie unbrauchbar."""
    shutil.copytree(WURZEL / "kern", ziel / "kern", ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WURZEL / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")


def baue_und_pruefe(ziel, sanitizer):
    """Gibt (uebersetzt, ctest_code, testzahl, protokoll) zurueck."""
    bau = ziel / ("bau_" + sanitizer)
    k = subprocess.run(["cmake", "-S", str(ziel / "kern"), "-B", str(bau),
                        f"-DFABRIK_SANITIZER={sanitizer}"], capture_output=True, text=True)
    if k.returncode != 0:
        return False, None, 0, k.stdout + k.stderr
    b = subprocess.run(["cmake", "--build", str(bau), "-j", "4"], capture_output=True, text=True)
    if b.returncode != 0:
        return False, None, 0, b.stdout + b.stderr
    t = subprocess.run(["ctest", "--test-dir", str(bau), "--output-on-failure"],
                       capture_output=True, text=True)
    zahl = 0
    for zeile in t.stdout.splitlines():
        if "tests passed" in zeile and "out of" in zeile:
            zahl = int(zeile.rsplit("out of", 1)[1].strip())
    return True, t.returncode, zahl, t.stdout + t.stderr


# Jede Zeile: (Kurzname, Datei, Suchtext, Ersatz, welche Entscheidung sie umdreht).
# Der Suchtext muss **genau einmal** vorkommen -- sonst mutiert der Lauf still nichts.
MUTATIONEN = [
    ("betrag-weg", "kern/src/werte.cpp",
     "    return betrag(unterschied);",
     "    return unterschied;",
     "Nr. 18 gibt die blanke Differenz statt ihres Betrags"),

    ("zweimal-alt", "kern/src/werte.cpp",
     "    const i64 jetzt  = rundenschreiber.lies_neu(stand);",
     "    const i64 jetzt  = rundenschreiber.lies_alt(stand);",
     "Nr. 18 liest zweimal die Vorrunde statt beider Lesearten (T39)"),

    ("kein-ueberlaufwaechter", "kern/src/werte.cpp",
     "    if (unterschied == festkomma::I64_MIN) {",
     "    if (unterschied == festkomma::I64_MAX) {",
     "Nr. 18 meldet den Rand des Wertebereichs unter fremdem Namen"),
]

MUTATIONEN += [
    ("klasse-einheitlich", "kern/src/werte.cpp",
     "    case Instrument::Regulierung:\n        return 10;  // Regulierungsstufen",
     "    case Instrument::Regulierung:\n        return 3;  // Regulierungsstufen",
     "die Klasse von Nr. 18 haengt nicht mehr am Instrument (T48)"),

    ("kein-instrumentriegel", "kern/src/werte.cpp",
     "    static_cast<void>(hubklasse(instrument));",
     "    static_cast<void>(hubklasse(Instrument::Zoll));",
     "Nr. 18 laesst das unbekannte Instrument den Zustand melden"),

    ("weltpreis-vorrunde", "kern/src/werte.cpp",
     "    const i64 weltpreis = rundenschreiber.lies_neu(zustand::stelle_weltpreis(sektor));",
     "    const i64 weltpreis = rundenschreiber.lies_alt(zustand::stelle_weltpreis(sektor));",
     "Nr. 19 liest den Weltpreis der Vorrunde statt dieser Runde"),
]

MUTATIONEN += [
    ("eine-rundung", "kern/src/werte.cpp",
     "    return mal_geteilt(keilhub(rundenschreiber, land, sektor), durchgriff, 10'000);",
     "    return mal_geteilt(mal(rundenschreiber.lies_neu(zustand::stelle_weltpreis(sektor)),\n"
     "                           hub(rundenschreiber, land, Instrument::Zoll)),\n"
     "                       durchgriff, 100'000'000);",
     "Nr. 20 rundet einmal statt zweimal -- die zusammengezogene Form"),

    ("durchgriff-erste-zeile", "kern/src/werte.cpp",
     "        konst.durchgriff[static_cast<std::size_t>(land)][zustand::sektor_index(sektor)];",
     "        konst.durchgriff[0][zustand::sektor_index(sektor)];",
     "Nr. 20 liest den Durchgriff immer aus der ersten Zeile"),
]

MUTATIONEN += [
    ("keilhub-ohne-landriegel", "kern/src/werte.cpp",
     "    if (g >= LAENDER) {\n        Meldung text;\n        text.text(groesse);",
     "    if (g >= GEBIETE) {\n        Meldung text;\n        text.text(groesse);",
     "Nr. 19 laesst die Restwelt eine Ebene tiefer melden"),

    ("preishub-ohne-eigenen-riegel", "kern/src/werte.cpp",
     '    pruefe_landessektor("kern::werte::preishub_zoll", land, sektor);\n\n',
     "",
     "Nr. 20 meldet ihre Raender unter dem Namen von Nr. 19"),
]


def lauf():
    print("1. Der Bestand, beide Bauprofile")
    with tempfile.TemporaryDirectory() as roh:
        ziel = Path(roh) / "kontrolle"
        ziel.mkdir()
        frische_kopie(ziel)
        for sanitizer in ("ON", "OFF"):
            gebaut, code, zahl, protokoll = baue_und_pruefe(ziel, sanitizer)
            melde(gebaut and code == 0,
                  f"FABRIK_SANITIZER={sanitizer}: uebersetzt und ctest gruen ({zahl} Proben)",
                  protokoll)

    print()
    print("2. Beisst die Probe? Jede Mutation dreht genau eine Entscheidung um")
    for name, datei, suchtext, ersatz, was in MUTATIONEN:
        with tempfile.TemporaryDirectory() as roh:
            ziel = Path(roh) / "mutant"
            ziel.mkdir()
            frische_kopie(ziel)
            pfad = ziel / datei
            inhalt = pfad.read_text()
            treffer = inhalt.count(suchtext)
            if treffer != 1:
                melde(False, f"{name}: Suchtext kommt {treffer}-mal vor, erwartet genau einmal")
                continue
            pfad.write_text(inhalt.replace(suchtext, ersatz))
            gebaut, code, _, protokoll = baue_und_pruefe(ziel, "OFF")
            rot = (not gebaut) or code != 0
            grund = "uebersetzt nicht" if not gebaut else "ctest rot"
            melde(rot, f"{name}: {was} -> {grund if rot else 'BLEIBT GRUEN'}",
                  "" if rot else protokoll)

    print()
    print("3. Die drei Riegel am Arbeitsbaum")
    for werkzeug, argumente in (("belegstellen", [str(WURZEL), str(SPECS)]),
                                ("bezeichner", [str(WURZEL)])):
        exe = WURZEL / "werkzeuge" / werkzeug / "bau" / (werkzeug + "_riegel")
        if not exe.exists():
            melde(False, f"{werkzeug}_riegel ist nicht gebaut ({exe})")
            continue
        r = subprocess.run([str(exe)] + argumente, capture_output=True, text=True)
        melde(r.returncode == 0, f"{werkzeug}_riegel: Code {r.returncode}",
              r.stdout + r.stderr)

    # Der Sperrebindungsriegel laeuft beim Konfigurieren und zaehlt dabei mit. Er
    # steht hier noch einmal am Arbeitsbaum, damit ein Pruefer seine Zeile im
    # Wortlaut sieht, ohne selbst zu konfigurieren.
    bau = WURZEL / "kern" / "bau" / "riegel0151"
    r = subprocess.run(["cmake", "-S", str(WURZEL / "kern"), "-B", str(bau),
                        "-DFABRIK_SANITIZER=OFF"], capture_output=True, text=True)
    zeilen = [z for z in (r.stdout + r.stderr).splitlines() if "Sperrebindungsriegel" in z]
    melde(r.returncode == 0 and len(zeilen) == 1,
          "Sperrebindungsriegel: " + (zeilen[0].strip("- ") if zeilen else "keine Zeile"),
          r.stdout + r.stderr)
    shutil.rmtree(bau, ignore_errors=True)

    print()
    print("4. Die drei Zahlwoerter in werte.hpp bleiben unberuehrt")
    kopf = (WURZEL / "kern" / "include" / "kern" / "werte.hpp").read_text()
    # Fuenf und nicht vier: Das Paket nennt die Kopfzeile, den Absatz ueber den
    # mechanischen Nachweis und die Zwischenueberschrift, uebersieht aber die
    # Begruendung von `Konstanten` ("muesste jede der siebzehn Funktionen sie einzeln
    # durchreichen"). Gezaehlt statt abgeschrieben -- gemessen am Stand vor dem Paket.
    melde(kopf.count("siebzehn") == 5,
          f"werte.hpp nennt 'siebzehn' {kopf.count('siebzehn')}-mal (erwartet 5, "
          "Stand vor dem Paket -- die Zahl wird erst mit 0152 richtig)")

    print()
    print(f"Abweichungen: {abweichungen}")
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(lauf())
