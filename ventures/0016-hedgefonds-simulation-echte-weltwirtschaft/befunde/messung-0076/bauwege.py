#!/usr/bin/env python3
"""Bedingung 2 von Paket 0076, zweite Haelfte -- die drei Bauwege in beiden Profilen.

Konfiguriert den Arbeitsbereich, `kern` allein und `pruefstand` allein je in einen
Wegwerf-Baum unter `$TMPDIR`, baut ihn und faehrt `ctest`. Zweimal: einmal mit
`FABRIK_SANITIZER=ON` (Vorgabe, ADR 0011 Massnahme 2) und einmal mit `OFF`. Der
Arbeitsbaum bleibt unberuehrt -- kein `build/` im Repo.

Aufruf aus WSL heraus:

    python3 befunde/messung-0076/bauwege.py vorher
    python3 befunde/messung-0076/bauwege.py nachher

Der Name ist nur die Ablage; gemessen wird immer der Arbeitsbaum, wie er gerade
dasteht. Zwei Laeufe mit verschiedenen Namen ergeben die Gegenprobe.

Zur Sollspalte: Die Abnahme von 0076 nennt die Zahlen 16 / 10 / 5. Der Baum traegt
seit dem 2026-09-05 mehr Ziele; gemessen sind 18 / 12 / 5, und zwar **vor** wie nach
der Aenderung dieses Pakets. Beide Zahlen stehen deshalb nebeneinander -- die aus der
Abnahme, damit niemand sie fuer erfuellt haelt, und die gemessene als das, woran sich
die Gleichheit von vorher und nachher zeigt.
"""

import os
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
# name -> (Quellverzeichnis, Zahl aus der Abnahme, gemessene Zahl je Profil)
#
# Die gemessenen Zahlen haengen am Profil: Das Testprofil legt je Baum zusaetzliche
# Ziele an. Die eine Zahl aus der Abnahme kann deshalb hoechstens fuer eines der
# beiden Profile gelten -- sie tut es fuer keines vollstaendig.
WEGE = {
    "arbeitsbereich": (WURZEL, 16, {"ON": 18, "OFF": 16}),
    "kern": (WURZEL / "kern", 10, {"ON": 12, "OFF": 11}),
    "pruefstand": (WURZEL / "pruefstand", 5, {"ON": 5, "OFF": 4}),
}
PROFILE = {"sanitizer-an": "ON", "sanitizer-aus": "OFF"}
MARKEN = ("uebersetzende Ziele", "Nullabhaengigkeit", "gefunden in", "es fehlen")


def marken_zeilen(txt):
    return [t.strip() for t in txt.splitlines() if any(m in t for m in MARKEN)]


def main():
    marke = sys.argv[1] if len(sys.argv) > 1 else "lauf"
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / ("bauwege0076-" + marke)
    ablage.mkdir(parents=True, exist_ok=True)
    fehler = 0
    for profil, wert in PROFILE.items():
        print("=== Profil " + profil + " (FABRIK_SANITIZER=" + wert + ") ===")
        for name, (quelle, abnahmezahl, sollje) in WEGE.items():
            sollzahl = sollje[wert]
            b = ablage / (profil + "-" + name)
            r = subprocess.run(["cmake", "-S", str(quelle), "-B", str(b),
                                "-DFABRIK_SANITIZER=" + wert],
                               capture_output=True, text=True)
            txt = r.stdout + r.stderr
            (ablage / (profil + "-" + name + "-konfig.log")).write_text(txt)
            zeilen = marken_zeilen(txt)
            gezaehlt = None
            for t in zeilen:
                if "uebersetzende Ziele" in t:
                    for wort in t.split():
                        if wort.isdigit():
                            gezaehlt = int(wort)
                            break
            passt = "  " if (r.returncode == 0 and gezaehlt == sollzahl) else "!!"
            if passt == "!!":
                fehler += 1
            print(passt + " " + name.ljust(16) + " konfig code=" + str(r.returncode)
                  + "  uebersetzende Ziele=" + str(gezaehlt)
                  + " (gemessen " + str(sollzahl) + ", Abnahme nennt " + str(abnahmezahl) + ")")
            for t in zeilen:
                print("        " + t[:150])
            rb = subprocess.run(["cmake", "--build", str(b), "-j", "4"],
                                capture_output=True, text=True)
            (ablage / (profil + "-" + name + "-bau.log")).write_text(rb.stdout + rb.stderr)
            print("   " + ("  " if rb.returncode == 0 else "!!") + " bau code=" + str(rb.returncode))
            if rb.returncode != 0:
                fehler += 1
                for t in (rb.stdout + rb.stderr).splitlines():
                    if "error:" in t:
                        print("        " + t.strip()[:150])
            rt = subprocess.run(["ctest", "--test-dir", str(b), "--output-on-failure"],
                                capture_output=True, text=True)
            ttxt = rt.stdout + rt.stderr
            (ablage / (profil + "-" + name + "-ctest.log")).write_text(ttxt)
            bilanz = [t.strip() for t in ttxt.splitlines()
                      if "tests passed" in t or "No tests were found" in t]
            print("   " + ("  " if rt.returncode == 0 else "!!") + " ctest code="
                  + str(rt.returncode) + "  " + " | ".join(bilanz))
            if rt.returncode != 0:
                fehler += 1
                for t in ttxt.splitlines():
                    if "(Failed)" in t:
                        print("        " + t.strip()[:150])
    print(chr(10) + str(fehler) + " Abweichung(en). Ablage: " + str(ablage))
    return 1 if fehler else 0


if __name__ == "__main__":
    raise SystemExit(main())