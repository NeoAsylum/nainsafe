#!/usr/bin/env python3
"""Der Messstand zu Paket 0147 -- die Anker an der Ortsfrage und an der Formreihenfolge.

Er misst dreierlei und behauptet nichts:

  0. **Die Selbstprobe des Auswerters.** Bevor irgendetwas uebersetzt wird, laeuft der
     Zeilenleser unten gegen einen gebauten Meldungstext und muss die neun Marken
     namentlich wiederfinden. Ohne diesen Schritt bliebe ein Auswerter, der gar nichts
     erkennt, in jedem Lauf still gruen -- gemessen an `messung-0106/messung.py`, dessen
     Liste `FREMDE_FAELLE` zwei Marken fuehrt (`Namensfall`, `Abstandsfall`), die der
     Riegel so nie schreibt: er meldet sie als `Selbsttest N:` und `Selbsttest Abstand
     N:`. Diese beiden Eintraege konnten dort nie treffen.

  1. **Der Vorlauf.** Die Fassung vor diesem Paket und die danach laufen im selben
     Aufruf ueber denselben Arbeitsbaum. Nur so ist "meldet dieselbe Zahlenzeile wie
     vorher" belastbar -- der Korpus driftet waehrend eines Laufs, gemessen zwoelfmal.
     Der Vergleichsstand wird **nicht von Hand eingetragen**, sondern aus dem
     Aenderungsverlauf der Datei selbst geholt und danach abgedruckt; eine fest
     eingetragene Kennung verfaellt in Stunden (Lehre aus Paket 0135).

  2. **Neun Mutanten.** Jeder ist eine Textersetzung auf einer Kopie ausserhalb des
     Quellbaums; der Lauf bricht ab, wenn der erwartete Wortlaut nicht genau einmal
     vorkommt. Jeder muss am **Selbsttest** sterben (Rueckgabe 2), also bevor der
     Bestand gelesen wird -- ein Anker am Bestand waere ein wandernder Anker.

Je Mutant werden fuenf Dinge geprueft und nicht vier wie in 0106:

    Rueckgabewert  |  **wie viele** Faelle gerissen sind (aus der Schlusszeile des
    Selbsttests, nicht aus meiner Liste)  |  **welcher** Fall namentlich  |  dass keine
    fremde Tabelle riss  |  dass der Bestand gar nicht erst gelesen wurde.

Die dritte Groesse ist die neue. Sie schliesst die Luecke, die eine reine Namensliste
laesst: Reisst ein Fall, dessen Marke der Auswerter nicht kennt, faellt das ohne sie
nicht auf, weil die Namensliste dann eben leer bleibt.

Dieses Skript ist selbst ein Riegel und kein Bericht: Es vergleicht gegen die
Erwartungstabelle unten und gibt bei jeder Abweichung 1 zurueck.

Gebaut wird ohne `-Werror`. Das ist Absicht und kein Nachlassen: Beim Sabotieren faellt
regelmaessig eine Variable aus dem Spiel, und dann wuerde der **Bau** rot statt des
Tests -- gemessen, dreimal. Die Sprachschalter sind dieselben wie im Baulauf.

Was dieses Skript ausserhalb des Repos anlegt, raeumt `aufraeumen.py` daneben weg.

Aufruf:  python3 messung.py
"""

import os
import pathlib
import re
import subprocess
import sys

REPO = pathlib.Path("/home/adria/fabrik")
VORHABEN = REPO / "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
QUELLE = VORHABEN / "werkzeuge/belegstellen/belegstellen_riegel.cpp"
IM_REPO = ("ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/"
           "werkzeuge/belegstellen/belegstellen_riegel.cpp")

SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O2"]

ARBEITSNAME = "messung-0147"

# --- Der Auswerter ---------------------------------------------------------------
#
# Die neun Selbsttesttabellen des Riegels melden ihre Faelle in **vier verschiedenen**
# Schreibweisen. Wer sie fuer einheitlich haelt, baut einen Auswerter, der die Haelfte
# uebersieht und trotzdem gruen meldet.

MARKEN = [
    ("Namensfall", re.compile(r"^Selbsttest (\d+):")),
    ("Abstandsfall", re.compile(r"^Selbsttest Abstand (\d+):")),
    ("Satzfall", re.compile(r"^Selbsttest Satzgrenze (\d+):")),
    ("Zitatfall", re.compile(r"^Zitatfall (\d+):")),
    ("Urteilsfall", re.compile(r"^Urteilsfall (\d+):")),
    ("Zielfall", re.compile(r"^Zielfall (\d+):")),
    ("Ortsfall", re.compile(r"^Ortsfall (\d+):")),
    ("Formfall", re.compile(r"^Formfall (\d+):")),
    ("Ordnungsfall", re.compile(r"^Ordnungsfall (\d+):")),
]

# Die Schlusszeile des Selbsttests. Sie traegt die **Anzahl** der gerissenen Faelle und
# ist damit von meiner Namensliste unabhaengig.
SCHLUSSZEILE = re.compile(
    r"^belegstellen_riegel: (\d+) von (\d+) Faellen des Selbsttests")

ZAHLENMARKE = "belegstellen_riegel, Bedingung 2 (Abschnittszitat)"


def gerissene_faelle(text):
    """Welche Faelle hat der Selbsttest namentlich gemeldet? In Reihenfolge, ohne
    Doppelungen."""
    treffer = []
    for zeile in text.splitlines():
        # Die laengeren Formen zuerst pruefen: `Selbsttest Abstand 3:` faengt sonst am
        # Muster fuer `Selbsttest 3:` vorbei, weil dieses auf einer Ziffer besteht --
        # die Reihenfolge ist hier trotzdem ausgeschrieben und nicht dem Zufall
        # ueberlassen.
        for name, muster in sorted(MARKEN, key=lambda m: -len(m[1].pattern)):
            fund = muster.match(zeile)
            if fund:
                marke = name + " " + fund.group(1)
                if marke not in treffer:
                    treffer.append(marke)
                break
    return treffer


def anzahl_gerissen(text):
    """Wie viele Faelle meldet der Riegel selbst als gerissen? `None`, wenn seine
    Schlusszeile fehlt -- dann ist der Selbsttest gar nicht rot geworden."""
    for zeile in text.splitlines():
        fund = SCHLUSSZEILE.match(zeile)
        if fund:
            return int(fund.group(1))
    return None


def zahlenzeile(text):
    for zeile in text.splitlines():
        if ZAHLENMARKE in zeile:
            return zeile.strip()
    return "(keine Zahlenzeile)"


def bericht(text):
    """Die Ausgabe ohne den Vorspann des Selbsttests. Der Vorspann nennt die Groessen
    der Tabellen und ist zwischen vorher und nachher **notwendig** verschieden -- ein
    Vergleich der ganzen Ausgabe wuerde daran scheitern und nichts ueber die Sache
    sagen."""
    zeilen = text.splitlines()
    for k, zeile in enumerate(zeilen):
        if zeile.startswith("belegstellen_riegel, Bedingung"):
            return "\n".join(zeilen[k:])
    return text


# --- Die Selbstprobe des Auswerters ----------------------------------------------
#
# Ein Auswerter, der nie etwas findet, macht jeden Mutanten gruen. Diese Probe ist der
# Nachweis, dass er ueberhaupt feuern kann -- je Marke einmal, im Wortlaut des Riegels.

PROBETEXT = """
Selbsttest 3: erwartet war kein Dateiname, gefunden wurde spiel.md.
      Zeile:    ...
Selbsttest Abstand 5: erwartet war keine, gefunden wurde 'Reihe 2'.
Selbsttest Satzgrenze 2: der Weg ohne Anfuehrung war erwartet, genommen wurde er nicht.
Zitatfall 7: die Art ist 1, erwartet war 2.
Urteilsfall 4: der Ausgang ist 'Befund', erwartet war 'aufgeloest'.
Zielfall 11: die Art ist 3, erwartet war 2.
Ortsfall 2: der Grund ist 'x', erwartet war 'y'.
Formfall 3: die Form ist 'mit Wortabstand', erwartet war 'ohne Anfuehrung'.
Ordnungsfall 6: an Platz 6 steht 'a', erwartet war 'b'.
      Herkunft: ...
belegstellen_riegel: 9 von 73 Faellen des Selbsttests sind nicht wie erwartet
"""

PROBE_ERWARTET = ["Namensfall 3", "Abstandsfall 5", "Satzfall 2", "Zitatfall 7",
                  "Urteilsfall 4", "Zielfall 11", "Ortsfall 2", "Formfall 3",
                  "Ordnungsfall 6"]


def selbstprobe():
    """Rueckgabe: Zahl der Abweichungen."""
    fehler = 0
    gefunden = gerissene_faelle(PROBETEXT)
    if gefunden != PROBE_ERWARTET:
        print("ROT Selbstprobe: der Auswerter liest " + str(gefunden))
        print("                 erwartet war        " + str(PROBE_ERWARTET))
        fehler += 1
    else:
        print("OK  Selbstprobe: alle neun Marken werden namentlich gelesen.")

    if anzahl_gerissen(PROBETEXT) != 9:
        print("ROT Selbstprobe: die Schlusszeile wird als "
              + str(anzahl_gerissen(PROBETEXT)) + " gelesen, erwartet war 9.")
        fehler += 1
    else:
        print("OK  Selbstprobe: die Schlusszeile wird gelesen.")

    # Die Gegenprobe: ein Text ohne Meldung darf nichts hergeben. Ohne sie wuerde ein
    # Auswerter, der alles trifft, ebenso durchgehen wie einer, der nichts trifft.
    leer = "belegstellen_riegel, Selbsttest: 8 Faelle zur Suche nach links, alle wie\n"
    if gerissene_faelle(leer) != [] or anzahl_gerissen(leer) is not None:
        print("ROT Selbstprobe: der Auswerter findet in einer gruenen Ausgabe etwas.")
        fehler += 1
    else:
        print("OK  Selbstprobe: eine gruene Ausgabe gibt nichts her.")
    return fehler


# --- Die Mutanten ------------------------------------------------------------------
#
# `alt` muss im Quelltext **genau einmal** vorkommen; sonst bricht der Lauf ab, statt
# still an der falschen Stelle zu treffen.

# Der Rumpf von `waehle_zitatform`, aus seinen drei Bloecken zusammengesetzt. So ist
# eine Vertauschung eine Umstellung dieser Liste und keine abgeschriebene zweite
# Fassung, die beim naechsten Umbruch der Zeile still danebengreift.
WAHL_KOPF = ("Formwahl waehle_zitatform(const Absatz& absatz, std::size_t hinter) {\n"
             "    Formwahl wahl;\n")
WAHL_MIT = (
    "    const std::size_t mit = ueberschrift_hinter(absatz.text, hinter, wahl.roh);\n"
    "    if (mit != 0) {\n"
    "        wahl.form = Zitatform::MitAnfuehrung;\n"
    "        wahl.zitatteil = mit;\n"
    "        return wahl;\n"
    "    }\n")
WAHL_OHNE = (
    "    if (name_ohne_anfuehrung(absatz, hinter, wahl.roh) != 0) {\n"
    "        wahl.form = Zitatform::OhneAnfuehrung;\n"
    "        wahl.zitatteil = 0;\n"
    "        return wahl;\n"
    "    }\n")
WAHL_ABSTAND = (
    "    const std::size_t abstand = ueberschrift_mit_abstand(absatz.text, hinter,"
    " wahl.roh);\n"
    "    if (abstand != 0) {\n"
    "        wahl.form = Zitatform::MitAbstand;\n"
    "        wahl.zitatteil = abstand;\n"
    "        return wahl;\n"
    "    }\n")
WAHL_FUSS = "    wahl.roh.clear();\n    return wahl;\n}\n"

WAHL_ALT = WAHL_KOPF + WAHL_MIT + WAHL_OHNE + WAHL_ABSTAND + WAHL_FUSS

MUTANTEN = [
    # --- Die Ortsfrage: der Schritt von der Art zum Grund, je Art einer -----------
    {
        "name": "M1-ausserhalb-fester-grund",
        "was": "Ziel ausserhalb beider Wurzeln: der Grund als Konstante ohne den Namen",
        "alt": ("        case Zielart::Ausserhalb:\n"
                "            return Ortsurteil{Ortsausgang::Uebergangen,\n"
                "                              \"Ziel ausserhalb beider Wurzeln: \""
                " + name};\n"),
        "neu": ("        case Zielart::Ausserhalb:\n"
                "            return Ortsurteil{Ortsausgang::Uebergangen,\n"
                "                              \"Ziel ausserhalb beider Wurzeln\"};\n"),
        "erwartet_rc": 2,
        "erwartet_faelle": ["Ortsfall 2"],
        "eigen": "Ortsfall",
    },
    {
        "name": "M2-ungelesen-fester-grund",
        "was": "Ziel in einem ungelesenen Ordner: der Grund als Konstante ohne den Namen",
        "alt": ("        case Zielart::Ungelesen:\n"
                "            return Ortsurteil{Ortsausgang::Uebergangen,\n"
                "                              \"Ziel in einem mit Absicht ungelesenen"
                " Ordner: \" + name};\n"),
        "neu": ("        case Zielart::Ungelesen:\n"
                "            return Ortsurteil{Ortsausgang::Uebergangen,\n"
                "                              \"Ziel in einem mit Absicht ungelesenen"
                " Ordner\"};\n"),
        "erwartet_rc": 2,
        "erwartet_faelle": ["Ortsfall 3"],
        "eigen": "Ortsfall",
    },
    {
        "name": "M3-totes-ziel-uebergangen",
        "was": "totes Ziel: der Ausgang als Konstante -- uebergangen statt Befund",
        "alt": ("        case Zielart::Tot:\n"
                "            return Ortsurteil{Ortsausgang::TotesZiel, std::string()};\n"),
        "neu": ("        case Zielart::Tot:\n"
                "            return Ortsurteil{Ortsausgang::Uebergangen,\n"
                "                              \"Ziel ausserhalb beider Wurzeln: \""
                " + name};\n"),
        "erwartet_rc": 2,
        "erwartet_faelle": ["Ortsfall 4"],
        "eigen": "Ortsfall",
    },
    {
        # Nicht aus der Abnahme, sondern aus der Rollenregel: Ein Test, der nie
        # fehlschlaegt, prueft nichts. M1 bis M3 lassen die Faelle 2, 3 und 4 reissen --
        # M4 holt den ersten nach, der sonst nur mitliefe.
        "name": "M4-nachschlagen-uebergangen",
        "was": "der Regelfall: nachschlagen wird zu uebergangen",
        "alt": "    return Ortsurteil{Ortsausgang::Nachschlagen, std::string()};\n",
        "neu": "    return Ortsurteil{Ortsausgang::Uebergangen, std::string()};\n",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Ortsfall 1"],
        "eigen": "Ortsfall",
    },
    {
        # Die Zaehlregel am toten Ziel -- laut Arbeitspaket der heikelste Teil. M3
        # reisst Ortsfall 4 am **Ausgang**; dieser hier reisst denselben Fall an der
        # **Zaehlung**, und nur er zeigt, dass die zweite Haelfte der Zeile geprueft
        # wird. Ohne ihn bliebe `zaehlt_als_zitat` eine Behauptung.
        "name": "M5-zaehlregel-abgeschaltet",
        "was": "das tote Ziel zaehlt nicht mehr als Zitat",
        "alt": ("bool zaehlt_als_zitat(Ortsausgang wie) { return wie =="
                " Ortsausgang::TotesZiel; }\n"),
        "neu": "bool zaehlt_als_zitat(Ortsausgang) { return false; }\n",
        "erwartet_rc": 2,
        "erwartet_faelle": ["Ortsfall 4"],
        "eigen": "Ortsfall",
    },

    # --- Die Reihenfolge der drei Zitatformen -------------------------------------
    {
        "name": "M6-anfuehrung-nach-hinten",
        "was": "die unmittelbare Anfuehrung wird zuletzt gefragt",
        "alt": WAHL_ALT,
        "neu": WAHL_KOPF + WAHL_OHNE + WAHL_ABSTAND + WAHL_MIT + WAHL_FUSS,
        "erwartet_rc": 2,
        "erwartet_faelle": ["Formfall 2"],
        "eigen": "Formfall",
    },
    {
        "name": "M7-ohne-anfuehrung-nach-hinten",
        "was": "die Form ohne Anfuehrung wird zuletzt gefragt",
        "alt": WAHL_ALT,
        "neu": WAHL_KOPF + WAHL_MIT + WAHL_ABSTAND + WAHL_OHNE + WAHL_FUSS,
        "erwartet_rc": 2,
        "erwartet_faelle": ["Formfall 3"],
        "eigen": "Formfall",
    },
    {
        # Wieder aus der Rollenregel und nicht aus der Abnahme: M6 und M7 reissen die
        # Faelle 2 und 3. Die Faelle 1 und 4 -- die dritte Form als die gewaehlte und
        # die Stelle, die keine ist -- brauchen ihre eigenen.
        "name": "M8-abstand-entfaellt",
        "was": "die dritte Form wird gar nicht mehr gefragt",
        "alt": WAHL_ALT,
        "neu": WAHL_KOPF + WAHL_MIT + WAHL_OHNE + WAHL_FUSS,
        "erwartet_rc": 2,
        "erwartet_faelle": ["Formfall 1"],
        "eigen": "Formfall",
    },
    {
        "name": "M9-immer-eine-form",
        "was": "jede Stelle gilt als Fundstelle",
        "alt": WAHL_ALT,
        "neu": (WAHL_KOPF + WAHL_MIT + WAHL_OHNE + WAHL_ABSTAND
                + "    wahl.roh.clear();\n"
                  "    wahl.form = Zitatform::MitAnfuehrung;\n"
                  "    return wahl;\n}\n"),
        "erwartet_rc": 2,
        "erwartet_faelle": ["Formfall 4"],
        "eigen": "Formfall",
    },
]


def git(*argumente):
    fertig = subprocess.run(["git", "-C", str(REPO)] + list(argumente),
                            capture_output=True, text=True)
    if fertig.returncode != 0:
        raise RuntimeError("git " + " ".join(argumente) + " gab "
                           + str(fertig.returncode) + ":\n" + fertig.stderr[-2000:])
    return fertig.stdout


def hole_vorstand():
    """Der Stand **unmittelbar vor** diesem Paket, aus dem Verlauf der Datei geholt.

    Eine von Hand eingetragene Kennung verfaellt in Stunden; eine geholte muss
    abgedruckt und **beprobt** werden, sonst hat man nur den Ort des Fehlers verschoben.
    Die vier Proben unten sind die Falle: Sie schlagen zu, wenn der Verlauf etwas
    anderes hergibt als gemeint.
    """
    zeilen = git("log", "--reverse", "--format=%H", "-S", "Paket 0147",
                 "--", IM_REPO).split()
    if not zeilen:
        raise RuntimeError("Kein Commit fuehrt 'Paket 0147' in " + IM_REPO
                           + " ein -- der Quelltext dieses Pakets fehlt.")
    einfuehrend = zeilen[0]
    vorstand = git("rev-parse", "--short", einfuehrend + "^").strip()
    text = git("show", vorstand + ":" + IM_REPO)

    proben = [
        ("der Vorstand darf 'Paket 0147' nicht kennen", "Paket 0147" not in text),
        ("der Vorstand muss 'Paket 0130' kennen -- er ist das Glied davor",
         "Paket 0130" in text),
        ("der Vorstand darf ORTSFAELLE nicht kennen", "ORTSFAELLE" not in text),
        ("der Vorstand darf FORMFAELLE nicht kennen", "FORMFAELLE" not in text),
    ]
    verfehlt = [wort for wort, gut in proben if not gut]
    if verfehlt:
        raise RuntimeError("Der geholte Vergleichsstand " + vorstand
                           + " ist nicht der gemeinte:\n  - "
                           + "\n  - ".join(verfehlt))
    return vorstand, text


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


def main():
    arbeit = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / ARBEITSNAME
    arbeit.mkdir(parents=True, exist_ok=True)

    print("Messstand 0147 -- Anker an der Ortsfrage und an der Formreihenfolge")
    print("")

    fehler = 0

    # --- Teil 0: die Selbstprobe des Auswerters ---------------------------------
    print("Teil 0 -- der Auswerter selbst")
    fehler += selbstprobe()
    print("")
    if fehler:
        print("Messstand 0147: der Auswerter misst nicht. Alles Weitere waere "
              "wertlos.")
        return 1

    # --- Teil 1: der Vorlauf, beide Fassungen im selben Aufruf -------------------
    nachher_text = QUELLE.read_text(encoding="utf-8")
    if "Paket 0147" not in nachher_text:
        print("ABBRUCH: der Arbeitsbaum fuehrt kein 'Paket 0147' in " + IM_REPO)
        return 1
    try:
        vorstand, vorher_text = hole_vorstand()
    except RuntimeError as fehlschlag:
        print("ABBRUCH beim Holen des Vergleichsstands:")
        print(str(fehlschlag))
        return 1

    kopf_vorher = git("rev-parse", "--short", "HEAD").strip()
    schmutz = git("status", "--porcelain", "--", IM_REPO).strip()
    print("Teil 1 -- der Vorlauf")
    print("Vergleichsstand: " + vorstand + " (aus dem Verlauf geholt, vier Proben "
          "bestanden)")
    print("Arbeitsbaum:     " + kopf_vorher)
    print("Uneingecheckt:   " + (schmutz if schmutz else "nichts an dieser Datei"))
    print("Schalter:        " + " ".join(SCHALTER))
    print("")

    ergebnis = {}
    for marke, text in [("vorher", vorher_text), ("nachher", nachher_text)]:
        quelle = arbeit / ("riegel-" + marke + ".cpp")
        programm = arbeit / ("riegel-" + marke)
        quelle.write_text(text, encoding="utf-8")
        if not uebersetze(quelle, programm):
            print("ABBRUCH: " + marke + " uebersetzt nicht.")
            return 1
        rc, aus, err = laufe(programm)
        ergebnis[marke] = (rc, zahlenzeile(aus), bericht(aus), err)
        print("[" + marke + "] Rueckgabe " + str(rc))
        print("    " + zahlenzeile(aus))
        if rc != 0:
            print("ROT: " + marke + " ist nicht gruen auf dem heutigen Korpus.")
            print(err[-2000:])
            fehler += 1
    print("")

    # Drei Groessen und nicht eine -- sonst heben zwei Aenderungen einander in der
    # Summe auf (Lehre aus Paket 0115).
    for was, k in [("Rueckgabewert", 0), ("Zahlenzeile", 1), ("Befundteil", 2),
                   ("Fehlerkanal", 3)]:
        if ergebnis["vorher"][k] == ergebnis["nachher"][k]:
            print("GLEICH  " + was)
        else:
            print("ABWEICHUNG im " + was + " -- der Umbau ist nicht wirkungsfrei:")
            print("   vorher:  " + str(ergebnis["vorher"][k])[:600])
            print("   nachher: " + str(ergebnis["nachher"][k])[:600])
            fehler += 1
    print("")

    # --- Teil 2: die Mutanten ----------------------------------------------------
    print("Teil 2 -- die neun Mutanten")
    for mutant in MUTANTEN:
        anzahl = nachher_text.count(mutant["alt"])
        if anzahl != 1:
            print("ABBRUCH " + mutant["name"] + ": der Wortlaut kommt " + str(anzahl)
                  + "-mal vor, erwartet genau einmal.")
            fehler += 1
            continue
        quelle = arbeit / (mutant["name"] + ".cpp")
        programm = arbeit / mutant["name"]
        quelle.write_text(nachher_text.replace(mutant["alt"], mutant["neu"]),
                          encoding="utf-8")
        if not uebersetze(quelle, programm):
            print("ABBRUCH " + mutant["name"] + ": uebersetzt nicht.")
            fehler += 1
            continue
        rc, aus, err = laufe(programm)
        faelle = gerissene_faelle(err)
        wieviele = anzahl_gerissen(err)
        fremd = [f for f in faelle if not f.startswith(mutant["eigen"] + " ")]
        las_bestand = ZAHLENMARKE in aus

        abweichungen = []
        if rc != mutant["erwartet_rc"]:
            abweichungen.append("Rueckgabe")
        if wieviele != 1:
            abweichungen.append("Anzahl")
        if faelle != mutant["erwartet_faelle"]:
            abweichungen.append("Fall")
        if fremd:
            abweichungen.append("fremde Tabelle")
        if las_bestand:
            abweichungen.append("Bestand gelesen")
        if abweichungen:
            fehler += 1

        print(("ROT " if abweichungen else "OK  ") + mutant["name"] + " -- "
              + mutant["was"])
        print("      Rueckgabe " + str(rc) + " (erwartet "
              + str(mutant["erwartet_rc"]) + ")")
        print("      Faelle gerissen laut Riegel: " + str(wieviele) + " (erwartet 1)")
        print("      gerissen: " + str(faelle) + " (erwartet "
              + str(mutant["erwartet_faelle"]) + ")")
        print("      fremde Tabellen gerissen: " + str(fremd) + " (erwartet [])")
        print("      Bestand gelesen: " + str(las_bestand) + " (erwartet False)")
        if abweichungen:
            print("      abgewichen in: " + ", ".join(abweichungen))
            print("      stderr (Ende): " + err[-600:].replace("\n", "\n        "))
    print("")

    # --- Die Drift waehrend der Messung -----------------------------------------
    kopf_nachher = git("rev-parse", "--short", "HEAD").strip()
    wanderung = git("log", "--oneline", vorstand + "..HEAD", "--", IM_REPO).strip()
    print("Arbeitsbaum vorher/nachher: " + kopf_vorher + " / " + kopf_nachher)
    print("Aenderungen an der gemessenen Datei seit " + vorstand + ":")
    print("  " + (wanderung.replace("\n", "\n  ") if wanderung else "(keine)"))
    if kopf_vorher != kopf_nachher:
        print("HINWEIS: der Korpus ist waehrend der Messung gewandert. Das macht die "
              "Messung nicht falsch -- beide Fassungen liefen im selben Aufruf --, "
              "aber es gehoert abgedruckt.")
    print("")

    if fehler == 0:
        print("Messstand 0147: alles wie erwartet.")
        return 0
    print("Messstand 0147: " + str(fehler) + " Abweichung(en).")
    return 1


if __name__ == "__main__":
    sys.exit(main())
