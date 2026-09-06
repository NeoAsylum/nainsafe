#!/usr/bin/env python3
"""Nachweis zu Paket 0155 -- der Kopf von `Konstanten` zaehlt die Jahrgangskonstanten.

Aufruf aus dem Vorhabensverzeichnis:

    python3 befunde/messung-0155/nachweis.py

Er laeuft ueber zwei Staende: `werte.hpp.vorher` (Stand b2829c8, vor diesem Paket) und
die Arbeitsfassung. Beide tragen dieselbe Struktur -- das Paket aendert nur Kommentar --,
also ist die **Zaehlung** an beiden gleich und nur die **Behauptung** verschieden.

Das ist der Punkt: Ein Zaehler, der auch den alten Stand gruen meldet, beweist nichts.
Erwartet wird deshalb ausdruecklich

    vorher  = 1 Abweichung (Zeile 73: "die eine", gezaehlt sind zwei)
    nachher = 0 Abweichungen

Trifft eine der beiden Erwartungen nicht zu, endet der Lauf mit Code 1.

**Was als Zahlbehauptung gilt.** Nicht jede Stelle mit dem Wort behauptet eine Zahl:

  * `die <zahlwort> Jahrgangskonstante[n]` -- bestimmter Artikel und Kardinalzahl. Das
    ist eine Aussage ueber diesen Traeger und wird gegen die Zaehlung gehalten.
  * `die <ordnungszahl> Jahrgangskonstante` -- "die zweite". Sie behauptet nicht, wie
    viele es sind, sondern dass es mindestens so viele sind; geprueft wird `<=`.
  * alles andere -- Zeile 15 sagt "weder ... noch eine Jahrgangskonstante" und nennt
    damit eine Kategorie, keine Anzahl. Ohne diese Unterscheidung waere die Zeile ein
    Dauerbefund.
"""

import re
import sys

VORHER = "befunde/messung-0155/werte.hpp.vorher"
NACHHER = "kern/include/kern/werte.hpp"

KARDINAL = {"eine": 1, "zwei": 2, "drei": 3, "vier": 4, "fuenf": 5, "sechs": 6}
ORDINAL = {"erste": 1, "zweite": 2, "dritte": 3, "vierte": 4}
ARTIKEL = {"die", "der", "den"}


def felder_von_konstanten(zeilen, pfad):
    """Der Rumpf von `struct Konstanten` in Felder zerlegt, Kommentar am Feld."""
    anfang = next((i for i, z in enumerate(zeilen)
                   if z.startswith("struct Konstanten {")), None)
    if anfang is None:
        sys.exit(f"{pfad}: `struct Konstanten` nicht gefunden")
    ende = next((i for i in range(anfang, len(zeilen)) if zeilen[i] == "};"), None)
    if ende is None:
        sys.exit(f"{pfad}: Ende von `struct Konstanten` nicht gefunden")

    felder, block = [], []
    for z in zeilen[anfang + 1:ende]:
        block.append(z)
        if z.rstrip().endswith(";") and not z.lstrip().startswith("///"):
            felder.append("\n".join(block))
            block = []
    if [z for z in block if z.strip()]:
        sys.exit(f"{pfad}: Rest hinter dem letzten Feld -- die Zerlegung passt nicht")
    return felder


def name_von(feld, pfad):
    treffer = re.search(r"(\w+)(?:\{\}|\s*=\s*0)\s*;", feld)
    if treffer is None:
        sys.exit(f"{pfad}: Feld ohne erkennbaren Namen:\n{feld}")
    return treffer.group(1)


def pruefe(pfad):
    with open(pfad, encoding="utf-8") as datei:
        zeilen = datei.read().split("\n")
    felder = felder_von_konstanten(zeilen, pfad)

    # Die zwei Sorten, an ihrem eigenen Kommentar erkannt und nicht an einer Liste im
    # Skript: eine Jahrgangsgroesse beruft sich auf T23 Punkt 5, ein Parameterschluessel
    # nach T27 traegt seinen Schluesselnamen.
    jahrgang = [f for f in felder if "T23 Punkt 5" in f]
    schluessel = [f for f in felder if re.search(r"/// Schluessel `\w+`", f)]
    gezaehlt = len(jahrgang)

    print(f"--- {pfad}")
    print(f"    Felder in `Konstanten`:      {len(felder)}")
    print(f"    davon Jahrgang (T23 Pkt. 5): {gezaehlt}"
          f" -> {[name_von(f, pfad) for f in jahrgang]}")
    print(f"    davon Schluessel (T27):      {len(schluessel)}"
          f" -> {[name_von(f, pfad) for f in schluessel]}")

    abweichungen = []

    # Die zwei Sorten teilen die Felder restlos und ueberschneidungsfrei. Ohne das waere
    # `gezaehlt` die Zahl einer Teilmenge und nicht die des Traegers.
    if [f for f in jahrgang if f in schluessel] or gezaehlt + len(schluessel) != len(felder):
        abweichungen.append(f"{pfad}: Die Sorten teilen die Felder nicht restlos")

    print("    Stellen mit dem Wort:")
    for i, z in enumerate(zeilen, 1):
        if "Jahrgangskonstante" not in z:
            continue
        # Die zwei Woerter unmittelbar vor dem Wort -- ohne Auszeichnungszeichen.
        davor = re.sub(r"[*_`]", " ", z[:z.index("Jahrgangskonstante")]).split()
        letztes = davor[-1].lower() if davor else ""
        vorletztes = davor[-2].lower() if len(davor) > 1 else ""

        if letztes in KARDINAL and vorletztes in ARTIKEL:
            genannt = KARDINAL[letztes]
            passt = genannt == gezaehlt
            urteil = f"nennt {letztes} ({genannt}), gezaehlt {gezaehlt}"
        elif letztes in ORDINAL:
            genannt = ORDINAL[letztes]
            passt = genannt <= gezaehlt
            urteil = f"Ordnungszahl {letztes} ({genannt}) <= {gezaehlt}"
        else:
            genannt, passt, urteil = None, True, "keine Zahlbehauptung"

        if not passt:
            abweichungen.append(f"{pfad}:{i} nennt {genannt}, gezaehlt sind {gezaehlt}")
            urteil += " -- ABWEICHUNG"
        print(f"      {i}: {urteil}: {z.strip()}")

    print(f"    Abweichungen: {len(abweichungen)}")
    return abweichungen


alt = pruefe(VORHER)
neu = pruefe(NACHHER)

print()
for a in alt + neu:
    print(f"  {a}")

# Zweiseitig: der alte Stand muss rot werden, sonst misst der Zaehler nichts.
fehler = []
if len(alt) != 1:
    fehler.append(f"Erwartet war genau 1 Abweichung im alten Stand, gefunden {len(alt)}")
if neu:
    fehler.append(f"Erwartet waren 0 Abweichungen im neuen Stand, gefunden {len(neu)}")

print()
print(f"vorher {len(alt)} (erwartet 1), nachher {len(neu)} (erwartet 0)")
for f in fehler:
    print(f"FEHLSCHLAG: {f}")
print("Abweichungen: 0" if not fehler else "Abweichungen: " + str(len(fehler)))
sys.exit(1 if fehler else 0)
