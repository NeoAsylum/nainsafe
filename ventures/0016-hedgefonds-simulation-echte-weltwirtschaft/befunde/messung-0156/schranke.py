#!/usr/bin/env python3
"""Nachweis zu Paket 0156 -- die absolute Schranke auf der Groesse des Verlaufs.

Drei Faelle, je zweimal uebersetzt (Sanitizerprofil und ohne):

  * die Wand auf ihrem heutigen Wert (26)         -> gruen
  * die Wand auf dem letzten Wert darunter (482)  -> gruen
  * die Wand auf dem ersten Wert darueber (483)   -> rot, Meldung im Wortlaut

Dazu die Gegenprobe: derselbe Fall 483 **ohne** die neue Zusicherung uebersetzt gruen.
Ohne sie waere nicht gezeigt, dass die dritte Zusicherung den Bau rot macht und nicht
eine der beiden anderen.

Gebaut wird der Kern im Alleinbau in einem Wegwerfbaum aus dem Leeren; die Quellen
bleiben unberuehrt. `ctest` laeuft hier absichtlich nicht: Bei 482 Runden legt
`verlauf_probe` acht Megabyte auf einen Stapelrahmen und liefe in einen
Stapelueberlauf -- genau die Grenze, die der Kopf der Schranke selbst nennt. Geprueft
wird die Uebersetzung, nicht der Lauf.

Rueckgabe 0 heisst: alle Faelle so ausgegangen wie erwartet.
"""

import pathlib
import shutil
import subprocess
import sys
import tempfile

VENTURE = pathlib.Path(__file__).resolve().parents[2]
WAND = "inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = 26;"
ZUSICHERUNG = "static_assert(sizeof(Verlauf) < STAPEL_JE_FADEN,"


def genau_einmal(text, muster, wo):
    """Ein Suchtext, der zweimal vorkommt, mutiert still die falsche Stelle."""
    n = text.count(muster)
    if n != 1:
        raise SystemExit("Suchtext %r kommt %d mal in %s vor, erwartet genau einmal"
                         % (muster[:40], n, wo))


def baum(ziel, wand, mit_zusicherung):
    """Ein Wegwerfbaum: der Kern und die Werkzeugkette, sonst nichts."""
    shutil.copytree(VENTURE / "kern", ziel / "kern",
                    ignore=shutil.ignore_patterns("bau", "*.o", "*.a"))
    shutil.copy2(VENTURE / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")
    kopf = ziel / "kern" / "include" / "kern" / "verlauf.hpp"
    text = kopf.read_text()
    genau_einmal(text, WAND, "verlauf.hpp")
    text = text.replace(WAND, WAND.replace("= 26;", "= %d;" % wand))
    if not mit_zusicherung:
        genau_einmal(text, ZUSICHERUNG, "verlauf.hpp")
        i = text.index(ZUSICHERUNG)
        j = text.index(");", i) + len(");\n")
        text = text[:i] + text[j:]
    kopf.write_text(text)
    return ziel


def groesse(wurzel):
    """sizeof(Verlauf) aus demselben Kopf, ohne den Kern zu linken."""
    quelle = wurzel / "groesse.cpp"
    shutil.copy2(pathlib.Path(__file__).resolve().parent / "groesse.cpp", quelle)
    prog = wurzel / "groesse"
    p = subprocess.run(["g++", "-std=c++20", "-I", str(wurzel / "kern" / "include"),
                        str(quelle), "-o", str(prog)], capture_output=True, text=True)
    if p.returncode != 0:
        return "(uebersetzt nicht)"
    return subprocess.run([str(prog)], capture_output=True, text=True).stdout


def uebersetze(wurzel, sanitizer):
    """Konfigurieren und den Kern samt Verlaufsprobe bauen. Kein ctest -- siehe Kopf."""
    bau = wurzel / ("bau-" + sanitizer)
    k = subprocess.run(["cmake", "-S", str(wurzel / "kern"), "-B", str(bau),
                        "-DFABRIK_SANITIZER=" + sanitizer],
                       capture_output=True, text=True)
    if k.returncode != 0:
        return k.returncode, k.stdout + k.stderr
    b = subprocess.run(["cmake", "--build", str(bau), "-j", "8",
                        "--target", "kern", "verlauf_probe"],
                       capture_output=True, text=True)
    return b.returncode, b.stdout + b.stderr


# Wand, Zusicherung vorhanden, erwartetes Urteil, Zweck der Zeile.
FAELLE = [
    (26, True, "gruen", "die Wand auf ihrem heutigen Wert"),
    (482, True, "gruen", "der letzte Wert unterhalb der Schranke"),
    (483, True, "rot", "der erste Wert oberhalb der Schranke"),
    (483, False, "gruen", "Gegenprobe: derselbe Fall ohne die neue Zusicherung"),
]

# Woran die rote Uebersetzung erkannt wird -- und woran nicht. Ohne die zweite Zeile
# waere nicht gezeigt, dass die dritte Zusicherung reisst und nicht die aus T40.
SOLL = "ein Verlauf ist groesser als der Stapel eines Fadens"
NICHT = "eine weitere passt nicht mehr hinein"


def main():
    abweichungen = 0
    for wand, mit, erwartet, zweck in FAELLE:
        marke = "Wand %d%s" % (wand, "" if mit else ", ohne die Zusicherung")
        print("\n=== %s -- %s (erwartet: %s) ===" % (marke, zweck, erwartet))
        with tempfile.TemporaryDirectory() as ordner:
            wurzel = baum(pathlib.Path(ordner), wand, mit)
            print("  sizeof(Verlauf) = %s Byte" % groesse(wurzel))
            for sanitizer in ("ON", "OFF"):
                rc, text = uebersetze(wurzel, sanitizer)
                urteil = "gruen" if rc == 0 else "rot"
                print("  Sanitizer %-3s -> %s (Code %d)" % (sanitizer, urteil, rc))
                abweichungen += pruefe(urteil, erwartet, text, marke, sanitizer)
    print("\nAbweichungen: %d" % abweichungen)
    return 1 if abweichungen else 0


def pruefe(urteil, erwartet, text, marke, sanitizer):
    """Ein Abweichungszaehler. Bei rot zaehlt auch, welche Zusicherung gerissen ist."""
    schlecht = 0
    if urteil != erwartet:
        print("  ABWEICHUNG: %s/%s ist %s, erwartet %s" % (marke, sanitizer, urteil, erwartet))
        print("\n".join("    | " + z for z in text.strip().splitlines()[-12:]))
        schlecht += 1
    if erwartet == "rot":
        for zeile in text.splitlines():
            if "error:" in zeile or "static assertion failed" in zeile:
                print("    Wortlaut: %s" % zeile.strip())
        if SOLL not in text:
            print("  ABWEICHUNG: die Meldung nennt die Stapelschranke nicht")
            schlecht += 1
        if NICHT in text:
            print("  ABWEICHUNG: gerissen ist die T40-Zusicherung, nicht die neue")
            schlecht += 1
    return schlecht


if __name__ == "__main__":
    sys.exit(main())
