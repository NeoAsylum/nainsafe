#!/usr/bin/env python3
"""Der Messstand zu Paket 0106 -- der Anker am Urteilsschritt des Belegstellenriegels.

Er misst zweierlei und behauptet nichts:

  1. **Der Vorlauf.** Die Fassung vor diesem Paket und die danach laufen im selben
     Aufruf ueber denselben Arbeitsbaum. Nur so ist "meldet dieselben Zahlen wie
     vorher" belastbar -- der Korpus driftet waehrend eines Laufs, gemessen elfmal.
  2. **Fuenf Mutanten.** Jeder ist eine Textersetzung auf einer Kopie ausserhalb des
     Quellbaums; das Kopierskript bricht ab, wenn der erwartete Wortlaut nicht genau
     einmal vorkommt. Jeder muss am **Selbsttest** sterben (Rueckgabe 2), also bevor
     der Bestand gelesen wird -- ein Anker am Bestand waere ein wandernder Anker.

Dieses Skript ist selbst ein Riegel und kein Bericht: Es vergleicht gegen die
Erwartungstabelle unten und gibt bei jeder Abweichung 1 zurueck.

Gebaut wird ohne `-Werror`. Das ist Absicht und kein Nachlassen: Beim Sabotieren
faellt regelmaessig eine Variable aus dem Spiel, und dann wuerde der **Bau** rot statt
des Tests -- gemessen, dreimal. Die Sprachschalter sind dieselben wie im Baulauf.

Aufruf:  python3 messung.py
"""

import os
import pathlib
import subprocess
import sys

REPO = pathlib.Path("/home/adria/fabrik")
VORHABEN = REPO / "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
QUELLE = VORHABEN / "werkzeuge/belegstellen/belegstellen_riegel.cpp"
IM_REPO = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp"

# Der benannte Vergleichsstand. Eine Messung gegen "den Stand davor" muss ihn
# abdrucken, sonst ist sie nicht nachvollziehbar.
VORSTAND = "5605c54"

SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O2"]

# --- Die Mutanten, je eine Textersetzung -----------------------------------------
#
# `alt` muss im Quelltext **genau einmal** vorkommen; sonst bricht der Lauf ab, statt
# still an der falschen Stelle zu treffen.

MUTANTEN = [
    {
        "name": "M1-ohne-anfuehrung-immer",
        "was": "Zweig ohne Anfuehrung: steht_da = true",
        "alt": "        urteil.steht_da = art == Namensart::Ueberschrift;",
        "neu": "        urteil.steht_da = true;",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 2"],
    },
    {
        "name": "M2-ohne-anfuehrung-nie",
        "was": "Zweig ohne Anfuehrung: steht_da = false",
        "alt": "        urteil.steht_da = art == Namensart::Ueberschrift;",
        "neu": "        urteil.steht_da = false;",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 1"],
    },
    {
        "name": "M3-mit-anfuehrung-immer",
        "was": "Zweig mit Anfuehrung: steht_da = true",
        "alt": (
            "        for (std::size_t u = 0; u < liste.size() && !urteil.steht_da; ++u) {\n"
            "            urteil.steht_da = liste[u] == gesucht;\n"
            "        }"
        ),
        "neu": "        urteil.steht_da = true;",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 4"],
    },
    {
        "name": "M4-einzelzeichen-verdrahtung",
        "was": "die Art einzelnes Zeichen entfaellt in beurteile_zitat",
        "alt": (
            "        } else if (art == Namensart::Einzelzeichen) {\n"
            "            urteil.grund = \"einzelnes Zeichen statt Ueberschrift: \"\n"
            "                           + std::string(erstes_wort(gesucht));\n"
            "        } else if (art == Namensart::Ohne_Gliederung) {"
        ),
        "neu": "        } else if (art == Namensart::Ohne_Gliederung) {",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 5"],
    },
    {
        # Nicht aus der Abnahme, sondern aus der Rollenregel: Ein Test, der nie
        # fehlschlaegt, prueft nichts. M1 bis M5 lassen die Faelle 1, 2, 4 und 5
        # reissen -- M6 und M7 holen die beiden nach, die sonst nur mitlaufen.
        "name": "M6-mit-anfuehrung-nie",
        "was": "Zweig mit Anfuehrung: steht_da = false",
        "alt": (
            "        for (std::size_t u = 0; u < liste.size() && !urteil.steht_da; ++u) {\n"
            "            urteil.steht_da = liste[u] == gesucht;\n"
            "        }"
        ),
        "neu": "        urteil.steht_da = false;",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 3"],
    },
    {
        "name": "M7-ohne-gliederung-verdrahtung",
        "was": "die Art ohne Gliederung entfaellt in beurteile_zitat",
        "alt": (
            "        } else if (art == Namensart::Ohne_Gliederung) {\n"
            "            urteil.grund = \"Zieldatei fuehrt keine Ueberschrift: \""
            " + zielanzeige;\n"
            "        }"
        ),
        "neu": "        }",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 6"],
    },
    {
        "name": "M5-einzelzeichen-art",
        "was": "die Art einzelnes Zeichen entfaellt in namensart",
        "alt": (
            "    if (kopfwort.size() == 1 && !ist_ziffer(kopfwort.front())) {\n"
            "        return Namensart::Einzelzeichen;\n"
            "    }\n"
        ),
        "neu": "",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Urteilsfall 5"],
    },
]

# Die Praefixe der fuenf aelteren Selbsttesttabellen. Kein Mutant dieses Pakets darf
# einen von ihnen reissen lassen -- sonst belegte sein Sterben nur, dass der
# Selbsttest als Ganzes reisst, und nicht, dass die neue Tabelle greift.
FREMDE_FAELLE = ["Namensfall", "Zitatfall", "Zielfall", "Abstandsfall", "Satzfall"]


def schreibe(pfad, text):
    pfad.write_text(text, encoding="utf-8")


def uebersetze(quelle, ziel):
    ruf = ["g++"] + SCHALTER + [str(quelle), "-o", str(ziel)]
    fertig = subprocess.run(ruf, capture_output=True, text=True)
    if fertig.returncode != 0:
        print("BAU ROT: " + " ".join(ruf))
        print(fertig.stderr[-4000:])
        return False
    return True


def laufe(programm):
    fertig = subprocess.run([str(programm), str(VORHABEN)],
                            capture_output=True, text=True)
    return fertig.returncode, fertig.stdout, fertig.stderr


def gerissene_faelle(text):
    """Welche Faelle hat der Selbsttest namentlich gemeldet?"""
    treffer = []
    for zeile in text.splitlines():
        for wort in ["Urteilsfall"] + FREMDE_FAELLE:
            if zeile.startswith(wort + " "):
                marke = zeile.split(":")[0].strip()
                if marke not in treffer:
                    treffer.append(marke)
    return treffer


def zahlenzeile(text):
    for zeile in text.splitlines():
        if "Bedingung 2 (Abschnittszitat)" in zeile:
            return zeile.strip()
    return "(keine Zahlenzeile)"


def main():
    arbeit = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0106"
    arbeit.mkdir(parents=True, exist_ok=True)

    nachher_text = QUELLE.read_text(encoding="utf-8")
    vorher_text = subprocess.run(
        ["git", "-C", str(REPO), "show", VORSTAND + ":" + IM_REPO],
        capture_output=True, text=True, check=True).stdout

    print("Messstand 0106 -- Anker am Urteilsschritt")
    print("Vergleichsstand: " + VORSTAND)
    print("Arbeitsbaum:     " + subprocess.run(
        ["git", "-C", str(REPO), "rev-parse", "--short", "HEAD"],
        capture_output=True, text=True, check=True).stdout.strip())
    print("Schalter:        " + " ".join(SCHALTER))
    print("")

    fehler = 0

    # --- Teil 1: der Vorlauf, beide Fassungen im selben Aufruf -------------------
    zahlen = {}
    for marke, text in [("vorher", vorher_text), ("nachher", nachher_text)]:
        quelle = arbeit / ("riegel-" + marke + ".cpp")
        programm = arbeit / ("riegel-" + marke)
        schreibe(quelle, text)
        if not uebersetze(quelle, programm):
            print("FEHLER: " + marke + " uebersetzt nicht.")
            return 1
        rc, aus, err = laufe(programm)
        zahlen[marke] = zahlenzeile(aus)
        print("[" + marke + "] Rueckgabe " + str(rc))
        print("    " + aus.splitlines()[0] if aus else "    (keine Ausgabe)")
        print("    " + zahlen[marke])
        if rc != 0:
            print("FEHLER: " + marke + " ist nicht gruen.")
            print(err[-2000:])
            fehler += 1
    print("")

    if zahlen.get("vorher") == zahlen.get("nachher"):
        print("GLEICH: beide Fassungen melden zeichengleich dieselbe Zahlenzeile.")
    else:
        print("ABWEICHUNG in der Zahlenzeile -- der Umbau ist nicht wirkungsfrei:")
        print("   vorher:  " + str(zahlen.get("vorher")))
        print("   nachher: " + str(zahlen.get("nachher")))
        fehler += 1
    print("")

    # --- Teil 2: die Mutanten ----------------------------------------------------
    for mutant in MUTANTEN:
        anzahl = nachher_text.count(mutant["alt"])
        if anzahl != 1:
            print("ABBRUCH " + mutant["name"] + ": der Wortlaut kommt " + str(anzahl)
                  + "-mal vor, erwartet genau einmal.")
            fehler += 1
            continue
        quelle = arbeit / (mutant["name"] + ".cpp")
        programm = arbeit / mutant["name"]
        schreibe(quelle, nachher_text.replace(mutant["alt"], mutant["neu"]))
        if not uebersetze(quelle, programm):
            print("ABBRUCH " + mutant["name"] + ": uebersetzt nicht.")
            fehler += 1
            continue
        rc, aus, err = laufe(programm)
        faelle = gerissene_faelle(err)
        fremd = [f for f in faelle if not f.startswith("Urteilsfall")]
        las_bestand = "Bedingung 2 (Abschnittszitat)" in aus

        marke = "OK  "
        if rc != mutant["erwartet_rc"]:
            marke = "ROT "
            fehler += 1
        elif faelle != mutant["erwartet_faelle"]:
            marke = "ROT "
            fehler += 1
        elif fremd:
            marke = "ROT "
            fehler += 1
        elif las_bestand:
            marke = "ROT "
            fehler += 1

        print(marke + mutant["name"] + " -- " + mutant["was"])
        print("      Rueckgabe " + str(rc) + " (erwartet "
              + str(mutant["erwartet_rc"]) + ")")
        print("      gerissen: " + str(faelle) + " (erwartet "
              + str(mutant["erwartet_faelle"]) + ")")
        print("      fremde Tabellen gerissen: " + str(fremd) + " (erwartet [])")
        print("      Bestand gelesen: " + str(las_bestand) + " (erwartet False)")
    print("")

    if fehler == 0:
        print("Messstand 0106: alles wie erwartet.")
        return 0
    print("Messstand 0106: " + str(fehler) + " Abweichung(en).")
    return 1


if __name__ == "__main__":
    sys.exit(main())
