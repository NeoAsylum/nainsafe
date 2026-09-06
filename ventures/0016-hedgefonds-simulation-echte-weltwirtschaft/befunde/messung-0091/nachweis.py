#!/usr/bin/env python3
"""Nachweis zur neuen Zusicherung aus Paket 0091 -- vier Faelle, ein Aufruf.

Die Zusicherung steht im Kopf der Zustandsausgabe und haelt den Puffer der vierten
Abfrage gegen den Stapel eines Fadens:

    static_assert(sizeof(Kettenblatt) < verlauf::STAPEL_JE_FADEN, ...)

Drei Faelle belegen, dass die Zahl reisst, wo sie soll; der vierte belegt, dass **diese**
Zeile es tut und nicht eine der beiden Nachbarzusicherungen aus dem Verlauf:

  1. heutiger Stand  (Kettenzeilen je Adresse = RUNDEN_KAPAZITAET + 1 = 27)  -> gruen
  2. knapp darunter  (139)                                                   -> gruen
  3. eines darueber  (140)                                                   -> rot
  4. Fall 3, aber mit entfernter Zusicherung                                 -> gruen

Ohne Fall 4 waere belegt, dass 140 rot macht -- nicht, dass meine Zeile es tut. Dazu der
zweiseitige Wortlautvergleich: Die Meldung muss meinen Text nennen und den der
Nachbarzusicherung nicht.

Der Grenzwert 139/140 ist nicht gewaehlt, sondern gerechnet und unten nachgerechnet.

Uebersetzt wird nur syntaktisch: Eine Zusicherung im Kopf braucht keinen Binder und kein
Programm, und der Lauf kostet damit Sekunden statt Minuten.

Aufruf aus dem Vorhabensverzeichnis:
    python3 befunde/messung-0091/nachweis.py
"""

import pathlib
import shutil
import subprocess
import sys
import tempfile

WURZEL = pathlib.Path(__file__).resolve().parents[2]
KOPF = "kern/include/kern/zustandsausgabe.hpp"

ZEILE = ("inline constexpr std::size_t KETTENZEILEN_JE_ADRESSE = "
         "verlauf::RUNDEN_KAPAZITAET + 1;")

MEIN_TEXT = "ein Kettenblatt lebt auf dem Stapel des Aufrufers"
FREMDER_TEXT = "ein Verlauf ist groesser als der Stapel eines Fadens"

ZUSICHERUNG = """static_assert(sizeof(Kettenblatt) < verlauf::STAPEL_JE_FADEN,
              "T2: ein Kettenblatt lebt auf dem Stapel des Aufrufers und passt dort nicht "
              "mehr hinein -- die Zeilen je Adresse oder die Zeichen je Zeile wurden "
              "heraufgesetzt");"""

PRUEFQUELLE = chr(35) + 'include "kern/zustandsausgabe.hpp"\n\nint main() { return 0; }\n'


def ersetze_einmal(text, alt, neu, wo):
    """Ersetzt `alt` durch `neu` und besteht darauf, dass es genau ein Vorkommen gab.

    Ein kuerzerer Suchtext mutiert sonst still nichts oder die falsche Stelle -- und eine
    Messung, deren Mutation nicht griff, sieht aus wie ein bestandener Fall.
    """
    anzahl = text.count(alt)
    if anzahl != 1:
        raise SystemExit("%s: Suchtext kommt %d-mal vor, erwartet genau einmal"
                         % (wo, anzahl))
    return text.replace(alt, neu)


def uebersetze(kettenzeilen, mit_zusicherung):
    """Baut einen Wegwerfbaum, mutiert ihn und ruft den Uebersetzer. Gibt (code, text)."""
    with tempfile.TemporaryDirectory() as ordner:
        baum = pathlib.Path(ordner)
        shutil.copytree(WURZEL / "kern", baum / "kern",
                        ignore=shutil.ignore_patterns("bau"))

        pfad = baum / KOPF
        inhalt = pfad.read_text(encoding="utf-8")

        if kettenzeilen is not None:
            neu = ("inline constexpr std::size_t KETTENZEILEN_JE_ADRESSE = %d;"
                   % kettenzeilen)
            inhalt = ersetze_einmal(inhalt, ZEILE, neu, "Kettenzeilen je Adresse")
        if not mit_zusicherung:
            inhalt = ersetze_einmal(inhalt, ZUSICHERUNG, "", "Zusicherung entfernen")

        pfad.write_text(inhalt, encoding="utf-8")

        quelle = baum / "pruefstelle.cpp"
        quelle.write_text(PRUEFQUELLE, encoding="utf-8")

        lauf = subprocess.run(
            ["g++", "-std=c++20", "-fsyntax-only", "-fwrapv",
             "-I", str(baum / "kern" / "include"), str(quelle)],
            capture_output=True, text=True, check=False)
        return lauf.returncode, lauf.stdout + lauf.stderr


def groesse(kettenzeilen):
    """Die Puffergroesse zu einer Zahl von Kettenzeilen -- die Rechnung aus dem Kopf."""
    return (310 * (1 + kettenzeilen) + 4) * 192 + 1


def main():
    faelle = [
        ("1. heutiger Stand (27)", None, True, True),
        ("2. knapp darunter (139)", 139, True, True),
        ("3. eines darueber (140)", 140, True, False),
        ("4. 140 ohne die Zusicherung", 140, False, True),
    ]

    abweichungen = 0
    for name, kettenzeilen, mit_zusicherung, soll_gruen in faelle:
        code, text = uebersetze(kettenzeilen, mit_zusicherung)
        ist_gruen = code == 0
        zeichen = "gruen" if ist_gruen else "rot"
        rechnung = "" if kettenzeilen is None else (", Puffer %d Byte"
                                                    % groesse(kettenzeilen))
        print("%s: %s (Code %d)%s" % (name, zeichen, code, rechnung))

        if ist_gruen != soll_gruen:
            abweichungen += 1
            print("   ABWEICHUNG: erwartet war %s" % ("gruen" if soll_gruen else "rot"))
            print(text[:2000])
            continue

        if not soll_gruen:
            if MEIN_TEXT not in text:
                abweichungen += 1
                print("   ABWEICHUNG: die Meldung nennt nicht %r" % MEIN_TEXT)
            if FREMDER_TEXT in text:
                abweichungen += 1
                print("   ABWEICHUNG: die Meldung nennt auch %r" % FREMDER_TEXT)
            treffer = [z for z in text.splitlines() if "static assertion failed" in z]
            print("   %d fehlgeschlagene Zusicherung(en)" % len(treffer))
            for z in treffer:
                print("   %s" % z.strip())

    print("Rechnung: 139 -> %d Byte, 140 -> %d Byte, Stapel je Faden 8388608 Byte"
          % (groesse(139), groesse(140)))
    print("Abweichungen: %d" % abweichungen)
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
