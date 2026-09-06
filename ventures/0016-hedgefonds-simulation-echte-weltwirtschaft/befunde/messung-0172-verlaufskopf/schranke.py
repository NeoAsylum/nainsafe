#!/usr/bin/env python3
"""Nachweis zu Paket 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen.

Der Kopf `kern/include/kern/verlauf.hpp` nennt fuer die Wand 2169 eine Bytezahl und
weist sie als Messung aus. Dieses Skript misst sie nach -- **uebersetzt, nicht
gerechnet**: Jeder Fall baut einen Wegwerfbaum aus `git archive <STAND>`, setzt darin
die Wand, uebersetzt `groesse.cpp` gegen genau diesen Kopf und laesst das Programm die
Zahl selbst abdrucken. Die Formel aus dem Paketrumpf steht hier nirgends; sie ist das,
was geprueft wird, und darf deshalb nicht die Quelle der Zahl sein.

Vier Faelle:

  1. Wand 26, beide Zusicherungen        -> gruen. Rueckbindung an die Messung zu 0156:
                                            dieselben 451.784 Byte muessen herauskommen.
  2. Wand 2169, ohne die Stapelzusicherung -> gruen. Die Zahl fuer den Kopf.
  3. Wand 2170, ohne die Stapelzusicherung -> rot. Die Meldung im Wortlaut; sie muss die
                                            T40-Zusicherung nennen.
  4. Wand 2170, ohne beide oberen Zusicherungen -> gruen. Die Gegenprobe zu 3: ohne sie
                                            waere nicht gezeigt, dass allein die
                                            T40-Zusicherung reisst.

**Warum die Stapelzusicherung in den Faellen 2 bis 4 fehlt.** Sie reisst schon bei der
Wand 483 (Messung zu 0156) und wuerde jeden Fall oberhalb rot machen, bevor die
T40-Zusicherung ueberhaupt zu Wort kaeme. Der Satz im Kopf spricht ausdruecklich davon,
wie weit *Wand und Kapazitaet gemeinsam* durchlaufen -- das ist die T40-Zusicherung.

Gebaut wird nur `groesse.cpp`; der Kern wird nicht gebaut und `ctest` laeuft hier nicht.
Beides waere sinnlos: Bei 2169 Runden legt `verlauf_probe` 37 Megabyte auf einen
Stapelrahmen und liefe in einen Stapelueberlauf -- genau die Grenze, die die dritte
Zusicherung nennt und die hier absichtlich entfernt ist. Dass beide Profile am wirklichen
Stand gruen sind, weist `lauf-profile.txt` daneben nach.

Rueckgabe 0 heisst: alle Faelle so ausgegangen wie erwartet.
"""

import pathlib
import subprocess
import sys
import tarfile
import tempfile

HIER = pathlib.Path(__file__).resolve().parent
VENTURE = HIER.parents[1]
REPO = VENTURE.parents[1]

# Der Stand wird einmal festgehalten und ueberall zitiert -- der Kopf des Zweiges
# bewegt sich waehrend eines Laufs, und ein Nachweis, der "HEAD" sagt, misst spaeter
# etwas anderes.
STAND = "45fc32ff156eef604ce419b736fbd7e15941efe9"

EINSCHLUSS_IM_REPO = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include"
KOPF_IM_REPO = EINSCHLUSS_IM_REPO + "/kern/verlauf.hpp"

WAND = "inline constexpr std::size_t PARTIELAENGE_HOECHSTENS = 26;"
STAPEL_ZUSICHERUNG = "static_assert(sizeof(Verlauf) < STAPEL_JE_FADEN,"
T40_ZUSICHERUNG = "static_assert(sizeof(Verlauf) < (PARTIELAENGE_HOECHSTENS + 1) * sizeof(Kette),"

# Woran die rote Uebersetzung erkannt wird -- und woran nicht.
SOLL_T40 = "eine weitere passt nicht mehr hinein"
NICHT_STAPEL = "groesser als der Stapel eines Fadens"

# Wand, Stapelzusicherung, T40-Zusicherung, erwartetes Urteil, Zweck der Zeile.
FAELLE = [
    (26, True, True, "gruen", "die Wand auf ihrem heutigen Wert -- Rueckbindung an 0156"),
    (2169, False, True, "gruen", "der letzte Wert, den Wand und Kapazitaet gemeinsam tragen"),
    (2170, False, True, "rot", "der erste Wert darueber -- welche Zusicherung reisst?"),
    (2170, False, False, "gruen", "Gegenprobe: derselbe Fall ohne die T40-Zusicherung"),
]


def genau_einmal(text, muster, wo):
    """Ein Suchtext, der zweimal vorkommt, mutiert still die falsche Stelle."""
    n = text.count(muster)
    if n != 1:
        raise SystemExit("Suchtext %r kommt %d mal in %s vor, erwartet genau einmal"
                         % (muster[:48], n, wo))


def entferne_zusicherung(text, anker):
    """Schneidet die Zusicherung ab `anker` bis einschliesslich ihrer Schlussklammer."""
    genau_einmal(text, anker, "verlauf.hpp")
    i = text.index(anker)
    j = text.index(");", i) + len(");\n")
    return text[:i] + text[j:]


def baum(ziel, wand, mit_stapel, mit_t40):
    """Ein Wegwerfbaum aus `git archive STAND` -- nie aus dem Arbeitsbaum.

    Waehrend dieses Laufs schreiben andere Agenten in denselben Arbeitsbaum. Wer ihn
    kopiert, misst ihre halbfertige Arbeit mit.
    """
    archiv = ziel / "stand.tar"
    p = subprocess.run(
        ["git", "-C", str(REPO), "archive", "--output", str(archiv), STAND,
         EINSCHLUSS_IM_REPO],
        capture_output=True, text=True)
    if p.returncode != 0:
        raise SystemExit("git archive fehlgeschlagen: " + p.stdout + p.stderr)
    with tarfile.open(archiv) as t:
        t.extractall(ziel, filter="data")

    kopf = ziel / KOPF_IM_REPO
    text = kopf.read_text()
    genau_einmal(text, WAND, "verlauf.hpp")
    text = text.replace(WAND, WAND.replace("= 26;", "= %d;" % wand))
    if not mit_stapel:
        text = entferne_zusicherung(text, STAPEL_ZUSICHERUNG)
    if not mit_t40:
        text = entferne_zusicherung(text, T40_ZUSICHERUNG)
    kopf.write_text(text)
    return ziel / EINSCHLUSS_IM_REPO


def uebersetze(einschluss, ziel):
    """`groesse.cpp` gegen genau diesen Kopf. Rueckgabe: Code, Ausgabe, Zahlen."""
    prog = ziel / "groesse"
    p = subprocess.run(
        ["g++", "-std=c++20", "-fwrapv", "-I", str(einschluss),
         str(HIER / "groesse.cpp"), "-o", str(prog)],
        capture_output=True, text=True)
    if p.returncode != 0:
        return p.returncode, p.stdout + p.stderr, None
    lauf = subprocess.run([str(prog)], capture_output=True, text=True)
    if lauf.returncode != 0:
        return lauf.returncode, lauf.stdout + lauf.stderr, None
    return 0, "", [int(x) for x in lauf.stdout.split()]


def pruefe(urteil, erwartet, text, zahlen, wand, marke):
    """Ein Abweichungszaehler. Bei rot zaehlt auch, welche Zusicherung gerissen ist."""
    schlecht = 0
    if urteil != erwartet:
        print("  ABWEICHUNG: %s ist %s, erwartet %s" % (marke, urteil, erwartet))
        print("\n".join("    | " + z for z in text.strip().splitlines()[-12:]))
        schlecht += 1
    if urteil == "gruen" and zahlen is not None:
        if zahlen[2] != wand:
            print("  ABWEICHUNG: der Kopf traegt die Wand %d, gesetzt war %d"
                  % (zahlen[2], wand))
            schlecht += 1
    if erwartet == "rot":
        for zeile in text.splitlines():
            if "error:" in zeile or "static assertion failed" in zeile:
                print("    Wortlaut: %s" % zeile.strip())
        if SOLL_T40 not in text:
            print("  ABWEICHUNG: die Meldung nennt die T40-Zusicherung nicht")
            schlecht += 1
        if NICHT_STAPEL in text:
            print("  ABWEICHUNG: gerissen ist die Stapelzusicherung, nicht die aus T40")
            schlecht += 1
    return schlecht


def main():
    print("Stand: %s" % STAND)
    abweichungen = 0
    for wand, mit_stapel, mit_t40, erwartet, zweck in FAELLE:
        fehlt = []
        if not mit_stapel:
            fehlt.append("Stapel")
        if not mit_t40:
            fehlt.append("T40")
        marke = "Wand %d%s" % (wand, (", ohne " + " und ".join(fehlt)) if fehlt else "")
        print("\n=== %s -- %s (erwartet: %s) ===" % (marke, zweck, erwartet))
        with tempfile.TemporaryDirectory() as ordner:
            ziel = pathlib.Path(ordner)
            einschluss = baum(ziel, wand, mit_stapel, mit_t40)
            rc, text, zahlen = uebersetze(einschluss, ziel)
            urteil = "gruen" if rc == 0 else "rot"
            print("  Urteil: %s (Code %d)" % (urteil, rc))
            if zahlen is not None:
                print("  sizeof(Verlauf) = %d Byte, sizeof(Kette) = %d Byte, "
                      "PARTIELAENGE_HOECHSTENS = %d" % (zahlen[0], zahlen[1], zahlen[2]))
            abweichungen += pruefe(urteil, erwartet, text, zahlen, wand, marke)
    print("\nAbweichungen: %d" % abweichungen)
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
