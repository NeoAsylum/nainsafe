#!/usr/bin/env python3
"""Laesst vier Bauagenten dieselbe Aufgabe in vier Sprachen umsetzen und misst."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path.home() / "fabrik" / "agents"))
sys.path.insert(0, "/home/adria/fabrik/agents")

import stackmessung  # noqa: E402
from nachtlauf import phase  # noqa: E402

ORT = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/messung-stack"

VORGABE = """Setze die Aufgabe aus `{ort}/AUFGABE.md` in **{sprache}** um.

Lies die Aufgabendatei vollstaendig und halte dich exakt an die Rechenvorschrift -- die
Reihenfolge der drei Schritte, die Rundung auf halbe Betraege von null weg, das
Abschneiden gegen null bei der Ganzzahldivision, die Klemmgrenzen und das
Ausgabeformat. Vier Agenten setzen dieselbe Aufgabe in vier Sprachen um; **die
Pruefsummen muessen uebereinstimmen**, und eine abweichende Pruefsumme ist der
eigentliche Messwert.

Schreibe genau eine Datei: `{ort}/{ordner}/{datei}`. Keine Projektdatei, kein
Buildskript, keine Fremdbibliothek. {zusatz}

Kein Gleitkommatyp, nirgends -- auch nicht fuer die Zeitmessung.

Das ist eine Messung, kein Arbeitspaket: Es gibt keine Datei unter `aufgaben/`, und du
setzt keinen Status. Deine Ausgabe ist der Quelltext, sonst nichts."""

SPRACHEN = [
    ("Rust", "rust", "schritt.rs",
     "Uebersetzt wird mit `rustc -O`, also eine freistehende Datei mit `fn main()`."),
    ("C++", "cpp", "schritt.cpp",
     "Uebersetzt wird mit `g++ -O2 -std=c++20`. Achte auf undefiniertes Verhalten bei "
     "vorzeichenbehaftetem Ueberlauf -- der Zwischenwert braucht 128 Bit."),
    ("Java", "java", "Schritt.java",
     "Uebersetzt wird mit `javac`; die Klasse heisst `Schritt` und hat `main`. "
     "Fuer den 128-Bit-Zwischenwert steht `Math.multiplyHigh` oder `BigInteger` "
     "zur Verfuegung -- waehle selbst."),
    ("Python", "python", "schritt.py",
     "Laeuft mit `python3` ohne Argumente. Pythons `int` ist beliebig genau, aber "
     "die Klemmung auf 64 Bit gehoert trotzdem umgesetzt."),
]

auftraege = [
    ("kernbauer", VORGABE.format(ort=ORT, sprache=name, ordner=ordner,
                                 datei=datei, zusatz=zusatz))
    for name, ordner, datei, zusatz in SPRACHEN
]

print(f"Vier Umsetzungen, gleichzeitig: {', '.join(s[0] for s in SPRACHEN)}")
fehler = phase("Stackmessung", auftraege)
print(f"Bauphase beendet, {fehler} Fehler.\n")
sys.exit(stackmessung.main())
