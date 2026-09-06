#!/usr/bin/env python3
"""Baut den Riegel aus Paket 0186 in die drei Dateien ein.

Jede Mutation prueft zuerst, dass ihr Suchtext genau einmal vorkommt; sonst bricht das
Skript ab, ohne etwas zu schreiben. Am Ende steht "Abweichungen: 0".
"""
import sys

WURZEL = "/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/"

QUELLE_ALT = """    laufende.anhaengen(satz);
"""

QUELLE_NEU = """    if (satz.runde != nummer_[runden_ - 1]) {
        Meldung meldung;
        meldung.text("kern::verlauf -- das Glied traegt die Runde ");
        meldung.zahl(satz.runde);
        meldung.text(", abgelegt wird es unter der Runde ");
        meldung.zahl(nummer_[runden_ - 1]);
        meldung.text(". Nach T18 nennt der Ursachensatz die Runde, in der geschrieben "
                     "wurde; die Rueckwaertsaufloesung nach T20 haelt beide Zahlen "
                     "gegeneinander und verglich sonst lautlos zwei Zeitrechnungen.");
        festkomma::abbruch(meldung.fertig());
    }

    laufende.anhaengen(satz);
"""

mutationen = [("src/verlauf.cpp", QUELLE_ALT, QUELLE_NEU)]

abweichungen = 0
for datei, alt, neu in mutationen:
    pfad = WURZEL + datei
    text = open(pfad, encoding="utf-8").read()
    treffer = text.count(alt)
    if treffer != 1:
        print("ABBRUCH %s: Suchtext kommt %d mal vor, erwartet 1" % (datei, treffer))
        abweichungen += 1
        continue
    open(pfad, "w", encoding="utf-8").write(text.replace(alt, neu))
    print("%s: 1 Stelle ersetzt" % datei)

print("Abweichungen: %d" % abweichungen)
sys.exit(1 if abweichungen else 0)
