"""Legt unter bau/kp0129/altbaum eine Kopie des Vorhabens an und stellt darin den
Wortlaut vor Paket 0101 wieder her. Nur fuer den Rotnachweis, nicht ausgeliefert."""
import os, shutil, sys

QUELLE = sys.argv[1]
ZIEL = os.path.join(QUELLE, "bau", "kp0129", "altbaum")

if os.path.isdir(ZIEL):
    shutil.rmtree(ZIEL)
os.makedirs(ZIEL)
for n in sorted(os.listdir(QUELLE)):
    if n == "bau" or n.startswith("."):
        continue
    q = os.path.join(QUELLE, n)
    z = os.path.join(ZIEL, n)
    if os.path.isdir(q):
        shutil.copytree(q, z)
    else:
        shutil.copy2(q, z)

ZUSTAND = os.path.join(ZIEL, "kern", "include", "kern", "zustand.hpp")
t = open(ZUSTAND, encoding="utf-8").read()

NEU = """/// der ganze Zweck: `lies`, `lege_ab` und `index_zu_adresse` pruefen `index >=
/// FELDER` ohnehin, also wird aus einer nicht ausgewerteten Fehlanzeige ein Abbruch
/// statt eines Zugriffs auf ein fremdes Feld.
///
/// **Alle drei Namen sind die heutigen, und zwei davon traegt `Zustand` selbst.**
/// `lies` und `lege_ab` stehen oben an der Klasse, `index_zu_adresse` weiter unten
/// in diesem Kopf und ausgeschrieben in `zustand.cpp`. Der mittlere hiess bis zu
/// seiner Umbenennung anders, und dieser Satz nannte ihn noch lange danach so --
/// eine Zusicherung ueber eine Funktion, die es nicht mehr gab. Wer einen der drei
/// umbenennt, benennt ihn hier mit um; die Probe ist der Mustervergleich ueber
/// `kern/`, auf den sich die Umbenennung oben ausdruecklich beruft.
"""

ALT = """/// der ganze Zweck: `lies`, `schreibe` und `index_zu_adresse` pruefen `index >=
/// FELDER` ohnehin, also wird aus einer nicht ausgewerteten Fehlanzeige ein Abbruch
/// statt eines Zugriffs auf ein fremdes Feld.
"""

if t.count(NEU) != 1:
    raise SystemExit("Wortlaut nach 0101 kommt %d mal vor -- erwartet genau einmal."
                     % t.count(NEU))
open(ZUSTAND, "w", encoding="utf-8").write(t.replace(NEU, ALT))
print("altbaum angelegt, Wortlaut vor 0101 wiederhergestellt:", ZIEL)
