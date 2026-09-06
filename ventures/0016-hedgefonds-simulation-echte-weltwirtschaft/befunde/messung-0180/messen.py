#!/usr/bin/env python3
"""Messung zu Paket 0180 -- der Zahlwortriegel wird rot, wenn man ihn kaputtmacht.

Aufruf aus dem Vorhabensverzeichnis:

    python3 befunde/messung-0180/messen.py

Das Skript ist selbst ein Riegel und kein Bericht: Zu jedem Fall steht die Erwartung
hier im Skript, und bei der ersten Abweichung endet der Lauf mit Code 1. Wer nur die
Ausgabe liest, liest ein Ergebnis; wer den Code liest, liest ein Urteil.

Gemessen werden zwei Sorten Fall, und sie beantworten zwei verschiedene Fragen:

  **Teil A -- wird der Riegel rot, wenn die Datei falsch wird?** Drei Staende von
  `werte.hpp`, jeder in einer eigenen Wegwerfwurzel, dazu der heutige Stand als
  Gegenprobe. Das ist Abnahmebedingung 2 des Pakets.

  **Teil B -- wird der Selbsttest rot, wenn der Riegel falsch wird?** Fuenf Mutanten
  des Quelltextes, je einer gegen eine der fuenf Tabellen. Zu jedem steht hier, welche
  Faelle reissen muessen -- **namentlich** und vollstaendig. Ein Mutant, bei dem eine
  fremde Tabelle mitreisst, ist genauso ein Fehlschlag wie einer, bei dem gar nichts
  reisst: Im ersten Fall misst die Tabelle nicht, was sie zu messen vorgibt.

Der fuenfte Mutant ist der wichtigste. Er verstellt **nur die Verdrahtung** -- die
Zaehlung wird an die falsche Sorte gebunden -- und laesst jeden Baustein unberuehrt.
Die vier Bausteintabellen bleiben deshalb gruen, und nur die fuenfte reisst. Genau das
ist ihre Rechtfertigung.

Uebersetzt wird mit `g++` unmittelbar, weil ein Mutant nicht in den Quellbaum gehoert
und `add_test` keine Wegwerfwurzel als Argument hergibt. Die Sprachschalter sind
dieselben wie in `werkzeugkette.cmake`; `-Werror` bleibt weg, damit ein Mutant am
Uebersetzer scheitert und nicht am Warnsatz -- der Vergleichsstand wird mit **denselben**
Schaltern gebaut.
"""

import os
import pathlib
import re
import shutil
import subprocess
import sys

VORHABEN = pathlib.Path(__file__).resolve().parents[2]
QUELLE = VORHABEN / "werkzeuge" / "zahlwort" / "zahlwort_riegel.cpp"
PRUEFLING_REL = pathlib.Path("kern") / "include" / "kern" / "werte.hpp"
PRUEFLING = VORHABEN / PRUEFLING_REL
VORSTAND = "b2829c8"

ARBEIT = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0180"
SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O1", "-g"]

fehler = []


def melde(satz):
    fehler.append(satz)
    print("  FEHLSCHLAG: " + satz)


def git(*argumente):
    return subprocess.run(["git", *argumente], cwd=str(VORHABEN), check=True,
                          capture_output=True).stdout


def uebersetze(quelltext, name):
    """Einen Quelltext nach `ARBEIT/<name>` uebersetzen und den Pfad zurueckgeben."""
    cpp = ARBEIT / (name + ".cpp")
    binaer = ARBEIT / name
    cpp.write_text(quelltext, encoding="utf-8")
    lauf = subprocess.run(["g++", *SCHALTER, "-o", str(binaer), str(cpp)],
                          capture_output=True, text=True)
    if lauf.returncode != 0:
        print(lauf.stderr[-3000:])
        sys.exit(f"Mutant '{name}' liess sich nicht uebersetzen -- die Messung waere "
                 f"gegenstandslos.")
    return binaer


def rufe(binaer, wurzel):
    lauf = subprocess.run([str(binaer), str(wurzel)], capture_output=True, text=True)
    return lauf.returncode, lauf.stdout, lauf.stderr


def wurzel_mit(name, inhalt):
    """Eine Wegwerfwurzel, die nichts als den Pruefling traegt."""
    wurzel = ARBEIT / name
    ziel = wurzel / PRUEFLING_REL
    ziel.parent.mkdir(parents=True, exist_ok=True)
    ziel.write_text(inhalt, encoding="utf-8")
    return wurzel


def einmal_ersetzen(text, alt, neu, wo):
    if text.count(alt) != 1:
        sys.exit(f"{wo}: '{alt[:60]}' kommt {text.count(alt)} mal vor, erwartet war "
                 f"genau einmal. Der Wortlaut hat sich verschoben; die Messung waere "
                 f"gegenstandslos.")
    return text.replace(alt, neu)


def gerissene_faelle(text):
    """Die Menge der Faelle, die der Selbsttest gemeldet hat -- Tabelle und Nummer."""
    return set(re.findall(r"Selbsttest (\w+), Fall (\d+)", text))


# ---------------------------------------------------------------------------
# Der Stand, gegen den gemessen wird
# ---------------------------------------------------------------------------

if ARBEIT.exists():
    shutil.rmtree(ARBEIT)
ARBEIT.mkdir(parents=True)

kopf = git("rev-parse", "HEAD").decode().strip()
print("=" * 78)
print(f"Messung 0180, Stand HEAD {kopf}")
print(f"  Pruefling  {PRUEFLING_REL}  Blob {git('hash-object', str(PRUEFLING)).decode().strip()}")
print(f"  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob "
      f"{git('hash-object', str(QUELLE)).decode().strip()}")
print(f"  Arbeitsplatz {ARBEIT}")
print("=" * 78)

rein = QUELLE.read_text(encoding="utf-8")
heutig = PRUEFLING.read_text(encoding="utf-8")
vorher = git("show", f"{VORSTAND}:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/"
             + PRUEFLING_REL.as_posix()).decode("utf-8")

vergleich = uebersetze(rein, "rein")

# ---------------------------------------------------------------------------
# Teil A -- wird der Riegel rot, wenn die Datei falsch wird?
# ---------------------------------------------------------------------------

print("\n## Teil A: der Riegel gegen vier Staende von werte.hpp\n")

# A0 -- die Gegenprobe. Ohne sie zeigt Teil A nur, dass der Riegel ueberhaupt rot
# werden kann, und nicht, dass er es aus dem gemeinten Grund tut.
A_FAELLE = [
    ("A0 heutiger Stand", heutig, 0, []),
    ("A1 Zahlwort im Kopf verstellt",
     einmal_ersetzen(heutig, "die zweiundzwanzig abgeleiteten Groessen",
                     "die einundzwanzig abgeleiteten Groessen", "A1"),
     1, ["Zeilennummer 2: 'einundzwanzig Groessen' nennt 21, gezaehlt sind 22"]),
    ("A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen",
     einmal_ersetzen(
         heutig, "\n}  // namespace kern::werte\n",
         "\n/// **T48 Nr. 23** -- eine neue Groesse, und niemand zieht das Zahlwort nach.\n"
         "[[nodiscard]] zustand::i64 neuwert(const zustand::Zustand& z);\n"
         "\n}  // namespace kern::werte\n", "A2"),
     1, ["Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23",
         "Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23",
         "Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23",
         "Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23"]),
    (f"A3 Stand vor 0155 ({VORSTAND})", vorher, 1,
     ["Zeilennummer 73: 'eine Jahrgangskonstante[n]' nennt 1, gezaehlt sind 2"]),
]

for name, inhalt, soll_code, soll_zeilen in A_FAELLE:
    wurzel = wurzel_mit(name.split()[0], inhalt)
    code, aus, err = rufe(vergleich, wurzel)
    gefunden = [z.strip() for z in err.splitlines()
                if z.startswith("  Zeilennummer") or z.startswith("  Feld ")
                or z.startswith("  Funktionsdeklaration ")]
    print(f"  {name}: Code {code} (erwartet {soll_code}), {len(gefunden)} Befunde")
    for z in gefunden:
        print(f"      {z}")
    if code != soll_code:
        melde(f"{name}: Code {code} statt {soll_code}")
    if gefunden != soll_zeilen:
        melde(f"{name}: Befunde weichen ab -- erwartet {soll_zeilen}")

# ---------------------------------------------------------------------------
# Teil B -- wird der Selbsttest rot, wenn der Riegel falsch wird?
# ---------------------------------------------------------------------------

print("\n## Teil B: fuenf Mutanten des Riegels gegen die fuenf Tabellen\n")

B_FAELLE = [
    ("M1 die Artikelregel faellt weg",
     "if (i < abstand + 1\n                    "
     "|| !ist_bestimmter_artikel(worte[i - abstand - 1].text)) {",
     "if (false) {",
     "Behauptung",
     {("Behauptung", "3"), ("Behauptung", "17")}),
    ("M2 das Kardinalurteil ist immer gruen",
     "return b.zahl == gezaehlt ? Urteil::Gruen : Urteil::Rot;",
     "return Urteil::Gruen;",
     "Urteil",
     {("Urteil", "2"), ("Urteil", "3"), ("Verdrahtung", "2"), ("Verdrahtung", "3")}),
    ("M3 jede Fundstelle bekommt eine eigene Nummer -- gezaehlt werden Zeilen",
     "hinein.insert(wert);",
     "hinein.insert(wert * 1000 + hinein.size());",
     "Zaehlung",
     {("Zaehlung", "2")}),
    ("M4 eine wortlose Zeile trennt keinen Block mehr",
     "if (worte.empty()) {\n            if (!laufend.worte.empty()) {\n"
     "                bloecke.push_back(laufend);\n                laufend.worte.clear();\n"
     "            }\n            continue;\n        }",
     "if (worte.empty()) {\n            continue;\n        }",
     "Bloecke",
     {("Bloecke", "3"), ("Bloecke", "4")}),
    ("M5 die Zaehlung wird an die falsche Sorte gebunden",
     "f.gezaehlt = sorte == Sorte::Groessen ? e.zaehlung.nummern.size()\n"
     "                                                  : e.zaehlung.jahrgang.size();",
     "f.gezaehlt = e.zaehlung.nummern.size();",
     "Verdrahtung",
     {("Verdrahtung", "1"), ("Verdrahtung", "3"), ("Verdrahtung", "5")}),
]

for nr, (name, alt, neu, tabelle, soll) in enumerate(B_FAELLE, start=1):
    mutant = uebersetze(einmal_ersetzen(rein, alt, neu, name), f"m{nr}")
    code, aus, err = rufe(mutant, VORHABEN)
    ist = gerissene_faelle(err)
    print(f"  {name}")
    print(f"      Code {code} (erwartet 2), gerissen: "
          f"{sorted(f'{t} {f}' for t, f in ist) or 'nichts'}")
    if code != 2:
        melde(f"{name}: Code {code} statt 2 -- der Selbsttest hat den Mutanten "
              f"durchgelassen")
    if ist != soll:
        melde(f"{name}: gerissen sind {sorted(ist)}, erwartet waren {sorted(soll)}")
    fremde = {t for t, _ in ist} - {tabelle}
    if nr == 5 and fremde:
        melde(f"{name}: fremde Tabellen mitgerissen ({sorted(fremde)}) -- der Nachweis "
              f"fuer die Verdrahtungstabelle haengt daran, dass kein Baustein beruehrt ist")

# ---------------------------------------------------------------------------
# Der Nachweis, dass der reine Stand nicht schon von selbst rot ist
# ---------------------------------------------------------------------------

code, aus, err = rufe(vergleich, VORHABEN)
print(f"\n  Gegenprobe, unveraenderter Riegel am heutigen Baum: Code {code} (erwartet 0)")
if code != 0:
    melde(f"Der unveraenderte Riegel endet mit Code {code} statt 0")

shutil.rmtree(ARBEIT)

print()
print(f"Fehlschlaege: {len(fehler)}")
for f in fehler:
    print(f"  {f}")
sys.exit(1 if fehler else 0)
