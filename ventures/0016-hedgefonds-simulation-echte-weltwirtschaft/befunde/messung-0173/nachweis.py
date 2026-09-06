#!/usr/bin/env python3
"""Nachweis zu Paket 0173 -- der Kommentar steht wieder ueber seiner Funktion.

Der Arbeitsbaum trug waehrend des Laufs die halbfertige Arbeit anderer Pakete
(`verlauf.cpp`, `zustandsausgabe.cpp`, `belegstellen_riegel.cpp` und zwei Koepfe).
Deshalb wird nicht im Arbeitsbaum gebaut, sondern in zwei Wegwerfbaeumen aus
`git archive <STAND>`: einmal unveraendert (VORHER), einmal mit ausschliesslich
meiner `werte.cpp` darueber (NACHHER). `diff -rq` der beiden belegt in einer Zeile,
dass genau eine Datei verschieden ist.

Geprueft werden die drei Abnahmebedingungen:

  1. `pruefe_landessektor` traegt den Kommentar von vor `0152` wieder unmittelbar
     ueber sich -- Wortlautvergleich gegen `git show e0682a1:...`.
  2. `pruefe_handelssektor` traegt allein den Kommentar aus `0152`. Nachpruefbar
     gemacht als: zwischen dem letzten `///` der einen Funktion und dem ersten der
     naechsten steht die Funktion selbst; dazu die drei Negativproben (kein "Land",
     kein "beiden Zollkeilgroessen", keine vier spielbaren Laender in ihrem Kopf).
  3. Sonst aendert sich nichts -- `git diff --numstat` zeigt 9/9 in einer Datei,
     ausserhalb der beiden Kommentarbloecke ist kein Unterschied, und beide
     Bauprofile sind gruen (Uebersetzung und `ctest`, Riegel eingeschlossen).

Aufruf: python3 nachweis.py <STAND>
"""

import os
import re
import shutil
import subprocess
import sys

WURZEL = "/home/adria/fabrik"
VENTURE = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
QUELLE = VENTURE + "/kern/src/werte.cpp"
ARBEIT = os.environ.get("TMPDIR", "/tmp") + "/0173"

abweichungen = 0
zeilen = []


def sag(text=""):
    print(text)
    zeilen.append(text)


def pruefe(bedingung, was):
    global abweichungen
    if not bedingung:
        abweichungen += 1
    sag(("  OK   " if bedingung else "  FEHL ") + was)


def lauf(befehl, cwd=WURZEL):
    return subprocess.run(befehl, cwd=cwd, capture_output=True, text=True)


def zeige(befehl, cwd=WURZEL):
    """Fuehrt aus, druckt Ruecklaufcode und Ausgabe, gibt den Lauf zurueck."""
    e = lauf(befehl, cwd)
    sag("$ " + " ".join(befehl))
    sag("  Code " + str(e.returncode))
    for z in (e.stdout + e.stderr).splitlines():
        sag("  | " + z)
    return e


def auspacken(stand, ziel):
    if os.path.isdir(ziel):
        shutil.rmtree(ziel)
    os.makedirs(ziel)
    tar = subprocess.run(["git", "archive", stand], cwd=WURZEL, capture_output=True)
    if tar.returncode != 0:
        raise SystemExit("git archive fehlgeschlagen: " + tar.stderr.decode())
    packer = subprocess.run(["tar", "-x", "-C", ziel], input=tar.stdout)
    if packer.returncode != 0:
        raise SystemExit("tar fehlgeschlagen")


def bauen(name, quellbaum, baubaum):
    """Ein Bauprofil: konfigurieren, uebersetzen, testen. Jeder Baum aus dem Leeren."""
    sag()
    sag("### " + name)
    if os.path.isdir(baubaum):
        shutil.rmtree(baubaum)
    for schritt in (
        ["cmake", "-S", quellbaum, "-B", baubaum],
        ["cmake", "--build", baubaum, "-j", "4"],
        ["ctest", "--test-dir", baubaum, "--output-on-failure"],
    ):
        e = zeige(schritt)
        pruefe(e.returncode == 0,
               name + ": `" + " ".join(schritt[:2]) + "` Code 0")
        if e.returncode != 0:
            return


# --------------------------------------------------------------------------
stand = sys.argv[1]
sag("# Nachweis 0173 -- Stand " + stand)
sag()
sag("Der Stand ist einmal festgehalten und wird ueberall zitiert; der Kopf des")
sag("Zweiges bewegt sich waehrend des Laufs.")

# --- Bedingung 3a: nur meine Datei ist angefasst -------------------------
sag()
sag("## Bedingung 3 -- ausserhalb der beiden Kommentarbloecke aendert sich nichts")
sag()
e = lauf(["git", "diff", "--numstat", "--", QUELLE])
sag("$ git diff --numstat -- " + QUELLE)
for z in e.stdout.splitlines():
    sag("  | " + z)
pruefe(e.stdout.strip().split("\t")[:2] == ["9", "9"],
       "genau 9 Zeilen hinzu, 9 fort -- der verschobene Block, sonst nichts")

# Kein ausfuehrbarer Code: jede Zeile des Diffs beginnt mit `///`.
e = lauf(["git", "diff", "-U0", "--", QUELLE])
geaendert = [z for z in e.stdout.splitlines()
             if (z.startswith("+") or z.startswith("-"))
             and not z.startswith("+++") and not z.startswith("---")]
sag()
sag("$ git diff -U0 -- <quelle>   (nur die Aenderungszeilen)")
for z in geaendert:
    sag("  | " + z)
pruefe(len(geaendert) == 18, "18 Aenderungszeilen (9 hinzu, 9 fort)")
pruefe(all(z[1:].lstrip().startswith("///") for z in geaendert),
       "jede Aenderungszeile ist eine Doxygen-Zeile -- keine Zeile Code")

# --- die beiden Baeume ---------------------------------------------------
vorher = ARBEIT + "/vorher"
nachher = ARBEIT + "/nachher"
sag()
sag("## Die zwei Wegwerfbaeume")
sag()
auspacken(stand, vorher)
if os.path.isdir(nachher):
    shutil.rmtree(nachher)  # Jeden Baum aus dem Leeren -- sonst laeuft nur der erste Lauf.
shutil.copytree(vorher, nachher)
shutil.copy2(os.path.join(WURZEL, QUELLE), os.path.join(nachher, QUELLE))
sag("VORHER  = " + vorher + "   (git archive " + stand + ", unveraendert)")
sag("NACHHER = VORHER kopiert, darueber meine Datei -- kein zweiter Export.")
sag()
e = zeige(["diff", "-rq", vorher, nachher])
unterschiede = e.stdout.strip().splitlines()
pruefe(len(unterschiede) == 1 and unterschiede[0].count("/kern/src/werte.cpp") == 2,
       "genau eine Datei unterscheidet die Baeume, und es ist `werte.cpp`")


# --- Bedingungen 1 und 2: der Wortlaut -----------------------------------
def bloecke(pfad):
    """Ordnet jeder Funktion den Doxygen-Block zu, der unmittelbar ueber ihr steht."""
    zs = open(pfad, encoding="utf-8").read().splitlines()
    gefunden = {}
    for i, z in enumerate(zs):
        m = re.match(r"^(?:void|std::size_t) (pruefe_\w+|land_nummer)\(", z)
        if not m:
            continue
        k = i - 1
        block = []
        while k >= 0 and zs[k].startswith("///"):
            block.insert(0, zs[k])
            k -= 1
        gefunden[m.group(1)] = block
    return gefunden


alt = subprocess.run(["git", "show", "e0682a1:" + QUELLE],
                     cwd=WURZEL, capture_output=True, text=True).stdout
open(ARBEIT + "/werte-e0682a1.cpp", "w", encoding="utf-8").write(alt)
vor_0152 = bloecke(ARBEIT + "/werte-e0682a1.cpp")
jetzt = bloecke(os.path.join(WURZEL, QUELLE))
davor = bloecke(os.path.join(vorher, QUELLE))

sag()
sag("## Bedingung 1 -- `pruefe_landessektor` traegt ihren Kommentar wieder")
sag()
sag("Vor `0152` (Stand e0682a1), " + str(len(vor_0152["pruefe_landessektor"]))
    + " Zeilen ueber `pruefe_landessektor`:")
for z in vor_0152["pruefe_landessektor"]:
    sag("  | " + z)
sag()
sag("Am Stand " + stand + " (vor meinem Lauf): "
    + str(len(davor.get("pruefe_landessektor", []))) + " Zeilen.")
sag()
sag("Jetzt, " + str(len(jetzt["pruefe_landessektor"])) + " Zeilen:")
for z in jetzt["pruefe_landessektor"]:
    sag("  | " + z)
sag()
pruefe(davor.get("pruefe_landessektor", []) == [],
       "vorher stand ueber `pruefe_landessektor` kein einziges `///` -- das ist der Befund")
pruefe(jetzt["pruefe_landessektor"] == vor_0152["pruefe_landessektor"],
       "jetzt steht dort Zeile fuer Zeile der Wortlaut von vor `0152`")

kopf_handel = jetzt["pruefe_handelssektor"]
kopf_handel_vorher = davor["pruefe_handelssektor"]
sag()
sag("## Bedingung 2 -- `pruefe_handelssektor` traegt allein den Kommentar aus `0152`")
sag()
sag("Vorher " + str(len(kopf_handel_vorher)) + " Zeilen, jetzt "
    + str(len(kopf_handel)) + ":")
for z in kopf_handel:
    sag("  | " + z)
sag()
# Der 0152-Kommentar ist der Rest des alten Doppelblocks nach Abzug des alten Kopfes.
erwartet = kopf_handel_vorher[len(vor_0152["pruefe_landessektor"]):]
pruefe(kopf_handel == erwartet,
       "jetzt steht dort genau der Rest des Doppelblocks -- der von `0152` geschriebene Teil")
pruefe(len(kopf_handel) + len(jetzt["pruefe_landessektor"]) == len(kopf_handel_vorher),
       "die beiden Bloecke ergeben zusammen den alten Doppelblock -- keine Zeile erfunden")

text = "\n".join(kopf_handel)
pruefe("Land" not in text and " Laender" not in text,
       "keine Aussage ueber ein Land im Kopf von `pruefe_handelssektor`")
pruefe("Zollkeilgroessen" not in text,
       "keine Aussage ueber \"die beiden Zollkeilgroessen\"")
pruefe("grund" in text and "SEKTOREN_HANDELBAR" in text,
       "der Absatz zur Sektorzaehlung und das Argument `grund` stehen darin")

# "Zwischen dem letzten /// der einen Funktion und dem ersten der naechsten
# steht die Funktion selbst."
zs = open(os.path.join(WURZEL, QUELLE), encoding="utf-8").read().splitlines()
i_handel = next(i for i, z in enumerate(zs) if z.startswith("void pruefe_handelssektor("))
i_land = next(i for i, z in enumerate(zs) if z.startswith("void pruefe_landessektor("))
dazwischen = [z for z in zs[i_handel:i_land] if z.startswith("///")]
sag()
sag("Zwischen den beiden Funktionsdeklarationen (Zeile " + str(i_handel + 1)
    + " und " + str(i_land + 1) + ") liegen " + str(len(dazwischen))
    + " `///`-Zeilen -- und sie gehoeren zum zweiten Block, nicht zum ersten:")
pruefe(len(dazwischen) == len(jetzt["pruefe_landessektor"]),
       "genau der Kopf von `pruefe_landessektor` liegt dazwischen, kein Rest des ersten")
pruefe(zs[i_handel - 1].startswith("///") and zs[i_land - 1].startswith("///"),
       "beide Funktionen tragen unmittelbar ueber sich eine `///`-Zeile")
i_rumpfende = next(i for i in range(i_handel, i_land) if zs[i] == "}")
pruefe(zs[i_rumpfende + 1] == ""
       and zs[i_rumpfende + 2] == jetzt["pruefe_landessektor"][0],
       "auf das Rumpfende der ersten folgen eine Leerzeile und der Kopf der zweiten")

# --- Bedingung 3b: beide Bauprofile gruen --------------------------------
sag()
sag("## Bedingung 3 -- beide Bauprofile gruen, im NACHHER-Baum")
kern = nachher + "/" + VENTURE
bauen("Arbeitsbereich (kern, kern_geprueft, Belegstellen-, Bezeichner- und "
      "Sperrebindungsriegel)", kern, kern + "/bau")
bauen("Kern allein (kern, kern_geprueft)", kern + "/kern", kern + "/kern/bau")

sag()
sag("Abweichungen: " + str(abweichungen))
open(os.path.dirname(os.path.abspath(__file__)) + "/lauf.txt", "w",
     encoding="utf-8").write("\n".join(zeilen) + "\n")
sys.exit(1 if abweichungen else 0)
