#!/usr/bin/env python3
"""Bedingung 3 zu Paket 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen.

Vier Laeufe: Alleinbau des Kerns und Arbeitsbereich, je mit und ohne Sanitizerprofil.
Konfigurieren, Bauen und `ctest`, jede Rueckgabe muss 0 sein. Gezaehlt wird zusaetzlich,
wie viele `ctest`-Eintraege liefen -- eine Aenderung, die still eine Probe verliert, sieht
an den Rueckgaben aus wie ein gruener Lauf.

Bezugsstand fuer die Zahl der Eintraege ist der 2026-09-06 laut Paketrumpf:
Alleinbau 12, Arbeitsbereich 18, in beiden Profilen.

Gebaut wird gegen den Arbeitsbaum -- er traegt die Aenderung, um die es geht. Die
Baubaeume liegen im Wegwerfverzeichnis und entstehen aus dem Leeren: Ein
stehengebliebener Baum bricht mit "does not match the source used to generate cache" ab
und sieht dabei an beiden Staenden gleich aus.

Rueckgabe 0 heisst: alle vier Laeufe gruen und die Zahl der Eintraege wie erwartet.
"""

import pathlib
import re
import subprocess
import sys
import tempfile

VENTURE = pathlib.Path(__file__).resolve().parents[2]

# Name, Quellverzeichnis, erwartete Zahl der ctest-Eintraege (Stand 2026-09-06).
BAEUME = [
    ("Alleinbau", VENTURE / "kern", 12),
    ("Arbeitsbereich", VENTURE, 18),
]


def lauf(befehl):
    p = subprocess.run(befehl, capture_output=True, text=True)
    return p.returncode, p.stdout + p.stderr


def eintraege(text):
    """`ctest` meldet 'N tests passed ... out of M' -- M ist die Zahl der Eintraege.

    Gelesen wird M und nicht N: Ein Eintrag, der still verschwindet, senkt beide Zahlen
    gleichzeitig, und nur M steht auch dann noch da, wenn einer rot war.
    """
    treffer = re.search(r"out of\s+(\d+)", text)
    return int(treffer.group(1)) if treffer else -1


def main():
    stand, _ = lauf(["git", "-C", str(VENTURE), "rev-parse", "HEAD"])
    _, kopf = lauf(["git", "-C", str(VENTURE), "rev-parse", "--short", "HEAD"])
    print("Stand des Zweiges: %s" % kopf.strip())
    _, schmutz = lauf(["git", "-C", str(VENTURE), "status", "--porcelain", "."])
    print("Arbeitsbaum vor dem Lauf:\n%s" % (schmutz.rstrip() or "  (sauber)"))

    abweichungen = 0
    with tempfile.TemporaryDirectory() as ordner:
        for name, quelle, soll in BAEUME:
            for sanitizer in ("ON", "OFF"):
                bau = pathlib.Path(ordner) / ("%s-%s" % (name, sanitizer))
                print("\n=== %s, Sanitizer %s (erwartet: 12/18 Eintraege, alles gruen) ==="
                      % (name, sanitizer))
                for schritt, befehl in [
                    ("cmake -S", ["cmake", "-S", str(quelle), "-B", str(bau),
                                  "-DFABRIK_SANITIZER=" + sanitizer]),
                    ("cmake --build", ["cmake", "--build", str(bau), "-j", "8"]),
                    ("ctest", ["ctest", "--test-dir", str(bau), "--output-on-failure"]),
                ]:
                    rc, text = lauf(befehl)
                    print("  %-14s -> Code %d" % (schritt, rc))
                    if rc != 0:
                        abweichungen += 1
                        print("\n".join("    | " + z
                                        for z in text.strip().splitlines()[-25:]))
                        break
                    if schritt == "ctest":
                        n = eintraege(text)
                        print("  ctest-Eintraege: %d (Bezugsstand 2026-09-06: %d)"
                              % (n, soll))
                        if n != soll:
                            print("  ABWEICHUNG: %d Eintraege, erwartet %d" % (n, soll))
                            abweichungen += 1

    _, schmutz = lauf(["git", "-C", str(VENTURE), "status", "--porcelain", "."])
    print("\nArbeitsbaum nach dem Lauf:\n%s" % (schmutz.rstrip() or "  (sauber)"))
    print("\nAbweichungen: %d" % abweichungen)
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
