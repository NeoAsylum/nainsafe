#!/usr/bin/env python3
"""Nachweis zu Paket 0152 -- T48 Nr. 11 in beiden Stelligkeiten sowie Nr. 21 und Nr. 22.

Der Lauf beantwortet vier Fragen an einer Wegwerfkopie des Kerns, damit der
Arbeitsbaum unberuehrt bleibt:

  1. **Bestand.** Uebersetzt und besteht `ctest` in beiden Bauprofilen
     (`FABRIK_SANITIZER=ON` und `OFF`)?
  2. **Beisst die Probe?** Jede Mutation unten dreht genau eine Entscheidung der
     Vorgabe um. Wird sie nicht rot, prueft die zugehoerige Probe die Entscheidung
     nicht, sondern nur die Rechnung.
  3. **Riegel.** Belegstellen-, Bezeichner- und Sperrebindungsriegel mit Code 0.
  4. **Der Zaehlnachweis aus T48.** `siebzehn` kommt in `werte.hpp` nicht mehr vor;
     der Kopf traegt **zweiundzwanzig** Groessen in **dreiundzwanzig** Deklarationen,
     und der Unterschied ist genau Nr. 11 mit ihren zwei Stelligkeiten. Gezaehlt wird
     aus der Datei, nicht aus dem Paket -- steht am Ende eine andere Zahl, ist das ein
     Befund. Dazu die Gegenprobe, dass `menge` und `verschiebung` keine Deklaration
     haben (T48: "und das ist eine Vorgabe und kein Vergessen").

Aufruf ohne Argumente. Am Ende steht `Abweichungen: 0`, wenn alles stimmt.
"""

import re
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
    ("nr11-eine-richtung", "kern/src/werte.cpp",
     "        summe = plus(summe, z.lies(zustand::stelle_handel(gegenueber, land, sektor)));\n",
     "",
     "Nr. 11 zaehlt nur die Ausfuhr statt beider Richtungen je Paar"),

    ("nr11-nur-ein-sektor", "kern/src/werte.cpp",
     "        summe = plus(summe, handelsvolumen(z, land, sektor));",
     "        summe = plus(summe, handelsvolumen(z, land, Sektor::Landwirtschaft));",
     "die einstellige Fassung summiert nicht ueber beide handelbaren Sektoren"),

    ("nr11-ohne-sektorriegel", "kern/src/werte.cpp",
     '    pruefe_handelssektor("kern::werte::handelsvolumen", sektor,\n'
     '                         " hat keine Handelszeile; ein Handelsvolumen gibt es nur fuer "\n'
     '                         "die handelbaren Sektoren (T15, T48).");\n',
     "",
     "Nr. 11 laesst den dritten Sektor eine Ebene tiefer melden"),
]

MUTATIONEN += [
    ("nr21-additiv", "kern/src/werte.cpp",
     "    return mal_geteilt(z.lies(zustand::stelle_weltpreis(sektor)), plus(10'000, zoll), 10'000);",
     "    return plus(z.lies(zustand::stelle_weltpreis(sektor)), zoll);",
     "Nr. 21 liest den Keil additiv statt multiplikativ (T5, spiel.md)"),

    ("nr21-zoll-ignoriert", "kern/src/werte.cpp",
     "plus(10'000, zoll), 10'000);",
     "plus(10'000, 0), 10'000);",
     "Nr. 21 nimmt den Zollstand des Gebiets gar nicht auf"),

    ("nr21-restwelt-liest", "kern/src/werte.cpp",
     "        g < LAENDER\n"
     "            ? z.lies(zustand::stelle_instrument(gebiet, Instrument::Zoll, InstrumentFeld::Stand))",
     "        g <= LAENDER\n"
     "            ? z.lies(zustand::stelle_instrument(gebiet, Instrument::Zoll, InstrumentFeld::Stand))",
     "Nr. 21 sucht fuer die Restwelt eine Zolladresse, die es nicht gibt"),

    ("nr21-ohne-gebietsriegel", "kern/src/werte.cpp",
     '        text.text("kern::werte::weltpreis_mit_zoll -- das Gebiet ");',
     '        text.text("kern::zustand -- das Gebiet ");',
     "Nr. 21 meldet ihr Gebiet unter fremdem Namen"),
]

MUTATIONEN += [
    ("nr22-menge-einstellig", "kern/src/werte.cpp",
     "                         mal_geteilt(handelsvolumen(z, land, sektor),",
     "                         mal_geteilt(handelsvolumen(z, land),",
     "die Zollzeile nimmt das Handelsvolumen aller Sektoren statt des eigenen"),

    ("nr22-leitzins-nimmt-bip", "kern/src/werte.cpp",
     "        return mal_geteilt(schuld(z, land), hub(rundenschreiber, land, Instrument::Leitzins),",
     "        return mal_geteilt(bip(z, land), hub(rundenschreiber, land, Instrument::Leitzins),",
     "die Zinszeile misst das Bruttoinlandsprodukt statt der Staatsschuld"),

    ("nr22-haushalt-fremder-hub", "kern/src/werte.cpp",
     "        return mal_geteilt(bip(z, land), hub(rundenschreiber, land, Instrument::Haushalt),",
     "        return mal_geteilt(bip(z, land), hub(rundenschreiber, land, Instrument::Leitzins),",
     "die Haushaltszeile liest den Hub eines anderen Instruments"),
]

MUTATIONEN += [
    ("nr22-regulierung-literal", "kern/src/werte.cpp",
     "                               konst.regulierung_last),",
     "                               7),",
     "die Regulierungszeile traegt ein Literal statt des Parameterschluessels"),

    ("nr22-fremder-name", "kern/src/werte.cpp",
     '    text.text("kern::werte::schaden -- zur Instrumentenkennung ");',
     '    text.text("kern::werte::hub -- zur Instrumentenkennung ");',
     "das fuenfte Instrument wird unter dem Namen von Nr. 18 gemeldet"),
]

MUTATIONEN += [
    ("nr22-ohne-landriegel", "kern/src/werte.cpp",
     '    if (g >= LAENDER) {\n        Meldung text;\n        text.text("kern::werte::schaden -- das Gebiet ");',
     '    if (g >= GEBIETE) {\n        Meldung text;\n        text.text("kern::werte::schaden -- das Gebiet ");',
     "Nr. 22 laesst die Restwelt eine Ebene tiefer melden"),
]


# --- Der Zaehlnachweis aus T48 --------------------------------------------
#
# Gezaehlt wird aus der Datei und nicht aus dem Paket: T48 verlangt den Kopf gegen
# seine Tabelle gelegt, und eine uebernommene Zahl ist kein Nachweis.

DEKLARATION = re.compile(r"^\[\[nodiscard\]\] zustand::i64 (\w+)\(", re.M)
NUMMER = re.compile(r"\*\*T48 Nr\. (\d+)")


def zaehle_kopf():
    kopf = (WURZEL / "kern" / "include" / "kern" / "werte.hpp").read_text()
    namen = DEKLARATION.findall(kopf)
    nummern = [int(n) for n in NUMMER.findall(kopf)]
    return kopf, namen, nummern


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
    bau = WURZEL / "kern" / "bau" / "riegel0152"
    r = subprocess.run(["cmake", "-S", str(WURZEL / "kern"), "-B", str(bau),
                        "-DFABRIK_SANITIZER=OFF"], capture_output=True, text=True)
    zeilen = [z for z in (r.stdout + r.stderr).splitlines() if "Sperrebindungsriegel" in z]
    melde(r.returncode == 0 and len(zeilen) == 1,
          "Sperrebindungsriegel: " + (zeilen[0].strip("- ") if zeilen else "keine Zeile"),
          r.stdout + r.stderr)
    shutil.rmtree(bau, ignore_errors=True)

    print()
    print("4. Der Zaehlnachweis aus T48")
    kopf, namen, nummern = zaehle_kopf()
    melde(kopf.count("siebzehn") == 0,
          f"werte.hpp nennt 'siebzehn' {kopf.count('siebzehn')}-mal (erwartet 0)")
    zahlwort = kopf.count("zweiundzwanzig") + kopf.count("Zweiundzwanzig")
    # Sechs und nicht vier: Das Paket nennt die Kopfzeile, den Absatz ueber den
    # mechanischen Nachweis und die Zwischenueberschrift. Dazu kommen die Aufzaehlung
    # der vier Mengen, die Begruendung von `Konstanten` und der neue Satz ueber den
    # Unterschied zwischen Groessen und Deklarationen. Nachgezaehlt, nicht uebernommen.
    melde(zahlwort == 6,
          f"werte.hpp traegt das nachgezaehlte Zahlwort {zahlwort}-mal (erwartet 6)")

    melde(sorted(set(nummern)) == list(range(1, 23)),
          f"die Nummern der Tabelle sind luecken- und dublettenfrei 1 bis 22: "
          f"{len(set(nummern))} verschiedene, {len(nummern)} Ueberschriften")
    melde(len(namen) == 23,
          f"dreiundzwanzig Deklarationen ausserhalb von intern (gezaehlt {len(namen)})")
    doppelt = [n for n in set(namen) if namen.count(n) > 1]
    melde(doppelt == ["handelsvolumen"],
          f"und der eine Unterschied ist Nr. 11 mit zwei Stelligkeiten: {doppelt}")

    # Die Gegenprobe zur Vorgabe aus T48: keine Deklaration heisst so.
    verboten = [n for n in namen if n in ("menge", "verschiebung")]
    melde(not verboten,
          f"`menge` und `verschiebung` haben keine Deklaration im Kopf: {verboten or 'keine'}")

    print()
    print("Die dreiundzwanzig Deklarationen, in der Reihenfolge des Kopfes:")
    for i, n in enumerate(namen, 1):
        print(f"  {i:2d}  {n}")

    print()
    print(f"Abweichungen: {abweichungen}")
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(lauf())
