#!/usr/bin/env python3
"""Nachweis zu Paket 0144 -- die Rundenkapazitaet des Verlaufs haengt nicht mehr an R.

Faehrt alle Baeume in einem Aufruf und endet mit einer Zahl.

  A  vorher/nachher x FABRIK_SANITIZER=ON/OFF -- Alleinbau des Kerns, cmake/build/ctest.
  B  Arbeitsbereich x ON/OFF -- dort greifen auch die Riegel, die der Alleinbau nicht kennt.
  C  Drei Wegwerfbaeume, die je eine einzelne Zeile aendern:
       kapazitaet-27      RUNDEN_KAPAZITAET eins ueber die Wand  -> Bau muss ROT werden
       alte-schranke-27   dasselbe mit der alten 512-KB-Schranke -> Bau wird GRUEN
                          (der Beleg, dass die alte Schranke bei 27 nicht gegriffen hat)
       kapazitaet-20      RUNDEN_KAPAZITAET wieder an R = 20 gebunden -> Bau gruen,
                          verlauf_probe aber ROT (der Beleg, dass Bedingung 1 nicht
                          leerlaeuft, sondern den Fehler des Pakets wirklich faengt)

Der Baum *vorher* ist derselbe Arbeitsbaum mit den drei Dateien aus `vorher/` daneben --
nicht ein Git-Stand: Ein Fremdlauf, der mitten im Lauf committet, verschiebt HEAD, die
Kopie nicht.
"""

import datetime
import os
import pathlib
import re
import shutil
import subprocess

HIER = pathlib.Path(__file__).resolve().parent
WURZEL = HIER.parents[1]
DATEIEN = [
    "kern/include/kern/verlauf.hpp",
    "kern/src/verlauf.cpp",
    "kern/test/verlauf_probe.cpp",
]
ZUSTANDSPROBEN = ["schritt_probe", "zustand_probe", "zustandsausgabe_probe"]
TMP = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0144"
HEUTE = datetime.date.today().isoformat()
GITSTAND = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=str(WURZEL),
                          capture_output=True, text=True).stdout.strip() or "unbekannt"

ALTE_SCHRANKE = """static_assert(sizeof(Verlauf) < std::size_t{512} * 1024,
              "ein Verlauf bleibt unter einem halben Megabyte");"""
NEUE_SCHRANKE = """static_assert(sizeof(Verlauf) < (PARTIELAENGE_HOECHSTENS + 1) * sizeof(Kette),
              "T40: ein Verlauf traegt hoechstens die Runden der laengsten zulaessigen "
              "Partie, und eine weitere passt nicht mehr hinein");"""


def lauf(befehl):
    ergebnis = subprocess.run(befehl, capture_output=True, text=True)
    return ergebnis.returncode, ergebnis.stdout + ergebnis.stderr


def baum_anlegen(name, mit_vorher=False):
    """Wegwerfbaum unter TMPDIR -- nur `kern/` und die Werkzeugkette.

    `kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein; der
    Bauordner wird nicht mitkopiert, weil er absolute Pfade traegt.
    """
    ziel = TMP / name
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.mkdir(parents=True)
    shutil.copytree(WURZEL / "kern", ziel / "kern", ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(WURZEL / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")
    if mit_vorher:
        for datei in DATEIEN:
            shutil.copyfile(HIER / "vorher" / pathlib.Path(datei).name, ziel / datei)
    return ziel


def ctest_eintraege(bau):
    _, aus = lauf(["ctest", "--test-dir", str(bau), "-N"])
    return sum(1 for z in aus.splitlines() if z.strip().startswith("Test #")
               or z.strip().startswith("Test  #"))


def messe(name, mit_vorher, profil):
    """Konfiguriert, baut und testet einen Baum; gibt zurueck, was verglichen wird."""
    baum = baum_anlegen("{0}-{1}".format(name, profil.lower()), mit_vorher)
    bau = baum / "bau"
    protokoll = []
    for befehl in (
        ["cmake", "-S", str(baum / "kern"), "-B", str(bau), "-DFABRIK_SANITIZER=" + profil],
        ["cmake", "--build", str(bau), "-j", "4"],
        ["ctest", "--test-dir", str(bau), "--output-on-failure"],
    ):
        code, aus = lauf(befehl)
        protokoll.append((befehl[0] + " " + befehl[1], code, aus))
        if code != 0:
            return {"protokoll": protokoll, "eintraege": -1, "proben": {}}
    proben = {}
    for probe in ZUSTANDSPROBEN + ["verlauf_probe"]:
        proben[probe] = lauf([str(bau / probe)])
    return {"protokoll": protokoll, "eintraege": ctest_eintraege(bau), "proben": proben}


def arbeitsbereich(profil):
    """Derselbe Lauf am echten Arbeitsbereich."""
    bau = TMP / ("arbeitsbereich-" + profil.lower())
    if bau.exists():
        shutil.rmtree(bau)
    protokoll = []
    for befehl in (
        ["cmake", "-S", str(WURZEL), "-B", str(bau), "-DFABRIK_SANITIZER=" + profil],
        ["cmake", "--build", str(bau), "-j", "4"],
        ["ctest", "--test-dir", str(bau), "--output-on-failure"],
    ):
        code, aus = lauf(befehl)
        protokoll.append((befehl[0] + " " + befehl[1], code, aus))
        if code != 0:
            return protokoll, -1
    return protokoll, ctest_eintraege(bau)


def verstoss(name, ersetzungen, probe_laufen):
    """Baut einen Baum mit genau den angegebenen Ersetzungen im Kopf des Kastens.

    Gebaut wird nur das Ziel `verlauf_probe` und ohne Sanitizer: Geprueft wird eine
    Zusicherung des Uebersetzers, und die faellt vor jedem Laufzeitwerkzeug.
    """
    baum = baum_anlegen(name)
    kopf = baum / "kern/include/kern/verlauf.hpp"
    text = kopf.read_text(encoding="utf-8")
    for alt, neu in ersetzungen:
        if text.count(alt) != 1:
            return {"name": name, "gebaut": None, "aus": "Ersetzung nicht eindeutig: " + alt,
                    "probe": None}
        text = text.replace(alt, neu)
    kopf.write_text(text, encoding="utf-8")

    bau = baum / "bau"
    code, aus = lauf(["cmake", "-S", str(baum / "kern"), "-B", str(bau),
                      "-DFABRIK_SANITIZER=OFF"])
    if code != 0:
        return {"name": name, "gebaut": False, "aus": aus[-2000:], "probe": None}
    code, aus = lauf(["cmake", "--build", str(bau), "-j", "4", "--target", "verlauf_probe"])
    ergebnis = {"name": name, "gebaut": code == 0, "aus": aus, "probe": None}
    if code == 0 and probe_laufen:
        ergebnis["probe"] = lauf([str(bau / "verlauf_probe")])
    return ergebnis


def kopf_gelesen():
    """Bedingung 2, mechanisch: Keine Zahl im Kasten ist mehr die Partielaenge."""
    kopf = (WURZEL / "kern/include/kern/verlauf.hpp").read_text(encoding="utf-8")
    quelle = (WURZEL / "kern/src/verlauf.cpp").read_text(encoding="utf-8")
    zahlkonstanten = re.findall(r"constexpr std::size_t (\w+) = (\d+);", kopf)
    befunde = []
    befunde.append(("RUNDEN_KAPAZITAET ist keine Zahl, sondern die Wand",
                    bool(re.search(r"RUNDEN_KAPAZITAET = PARTIELAENGE_HOECHSTENS;", kopf))))
    befunde.append(("die einzige Zahlkonstante des Kopfes ist die Wand aus T40",
                    [name for name, _ in zahlkonstanten] == ["PARTIELAENGE_HOECHSTENS"]))
    befunde.append(("keine Konstante ist mehr als Partielaenge R begruendet",
                    "die Partielaenge R aus spiel.md" not in kopf
                    and "ist die Partielaenge R" not in kopf))
    befunde.append(("die Wand ist im Kopf aus T40 begruendet", "T40" in kopf))
    befunde.append(("die Abbruchmeldung nennt die Schranke",
                    "meldung.zahl(static_cast<i64>(RUNDEN_KAPAZITAET));" in quelle))
    befunde.append(("kein Gleitkommatyp im Kasten (T4, mit blossem Auge)",
                    not re.search(r"\b(float|double|long double)\b", kopf + quelle)))
    return befunde, zahlkonstanten


def marken(protokoll, zeilen=8):
    """Die letzten Zeilen je Schritt -- ohne sie steht bei einem Abbruch nur `Code 1` da."""
    stuecke = []
    for schritt, code, aus in protokoll:
        letzte = [z for z in aus.splitlines() if z.strip()][-zeilen:]
        stuecke.append("### {0} -- Code {1}\n\n```\n{2}\n```\n".format(
            schritt, code, "\n".join(letzte)))
    return "\n".join(stuecke)


def hauptlauf():
    abweichungen = 0
    zeilen = []
    stand = {}

    # --- A und B: die vier Baeume und der Arbeitsbereich ----------------------------
    for profil in ("ON", "OFF"):
        vorher = messe("vorher", True, profil)
        nachher = messe("nachher", False, profil)

        for name, ergebnis in (("vorher", vorher), ("nachher", nachher)):
            for schritt, code, _ in ergebnis["protokoll"]:
                if code != 0:
                    abweichungen += 1
                    zeilen.append("ROT  {0} {1}: {2} Code {3}".format(name, profil, schritt,
                                                                     code))
        if vorher["eintraege"] < 0 or nachher["eintraege"] < 0:
            abweichungen += 1
            zeilen.append("ROT  {0}: ein Baum kam nicht bis zum ctest".format(profil))
            continue

        gleich = nachher["eintraege"] == vorher["eintraege"]
        if not gleich:
            abweichungen += 1
        zeilen.append("{0} ctest-Eintraege {1}: vorher {2}, nachher {3} (erwartet gleich, "
                      "das Paket legt keine Probe an)".format("OK  " if gleich else "ROT ",
                                                              profil, vorher["eintraege"],
                                                              nachher["eintraege"]))

        for probe in ZUSTANDSPROBEN:
            g = vorher["proben"].get(probe) == nachher["proben"].get(probe)
            if not g:
                abweichungen += 1
            zeilen.append("{0} {1} {2}: Ausgabe vorher/nachher {3}".format(
                "OK  " if g else "ROT ", profil, probe,
                "zeichengleich" if g else "VERSCHIEDEN"))

        # Bedingung 1: der Nachweis zaehlt die Runden, die wirklich gelaufen sind.
        runden_vorher = len(re.findall(r"^  Runde \d+: \d+ Glieder",
                                       vorher["proben"]["verlauf_probe"][1], re.M))
        runden_nachher = len(re.findall(r"^  Runde \d+: \d+ Glieder",
                                        nachher["proben"]["verlauf_probe"][1], re.M))
        genug = runden_nachher >= 26 and nachher["proben"]["verlauf_probe"][0] == 0
        if not genug:
            abweichungen += 1
        zeilen.append("{0} {1} Bedingung 1: Partie ueber {2} Runden aufgenommen, Code {3} "
                      "(vorher {4} Runden)".format("OK  " if genug else "ROT ", profil,
                                                   runden_nachher,
                                                   nachher["proben"]["verlauf_probe"][0],
                                                   runden_vorher))

        arbeit, arbeit_eintraege = arbeitsbereich(profil)
        rot = any(code != 0 for _, code, _ in arbeit)
        if rot:
            abweichungen += 1
        zeilen.append("{0} Arbeitsbereich {1}: cmake/build/ctest je Code 0, {2} "
                      "ctest-Eintraege".format("ROT " if rot else "OK  ", profil,
                                               arbeit_eintraege))
        stand[profil] = (vorher, nachher, arbeit)

    # --- C: die drei Wegwerfbaeume mit je einer geaenderten Zeile -------------------
    ueber_die_wand = [("inline constexpr std::size_t RUNDEN_KAPAZITAET = "
                       "PARTIELAENGE_HOECHSTENS;",
                       "inline constexpr std::size_t RUNDEN_KAPAZITAET = "
                       "PARTIELAENGE_HOECHSTENS + 1;")]
    an_r_gebunden = [("inline constexpr std::size_t RUNDEN_KAPAZITAET = "
                      "PARTIELAENGE_HOECHSTENS;",
                      "inline constexpr std::size_t RUNDEN_KAPAZITAET = 20;")]

    r27 = verstoss("kapazitaet-27", ueber_die_wand, False)
    if r27["gebaut"] is not False:
        abweichungen += 1
    nennt = r27["gebaut"] is False and "static_assert" in r27["aus"]
    if not nennt:
        abweichungen += 1
    zeilen.append("{0} Riegel kapazitaet-27: Bau {1} (erwartet ROT), Meldung nennt "
                  "static_assert: {2}".format(
                      "OK  " if (r27["gebaut"] is False and nennt) else "ROT ",
                      "ROT" if r27["gebaut"] is False else "gruen",
                      "ja" if nennt else "NEIN"))

    alt27 = verstoss("alte-schranke-27",
                     ueber_die_wand + [(NEUE_SCHRANKE, ALTE_SCHRANKE)], False)
    if alt27["gebaut"] is not True:
        abweichungen += 1
    zeilen.append("{0} Kontrolle alte-schranke-27: mit der alten 512-KB-Schranke daneben "
                  "waere derselbe Verstoss {1} -- sie griff bei 27 nicht".format(
                      "OK  " if alt27["gebaut"] else "ROT ",
                      "gruen" if alt27["gebaut"] else "ROT"))

    r20 = verstoss("kapazitaet-20", an_r_gebunden, True)
    probe_rot = r20["gebaut"] is True and r20["probe"] is not None and r20["probe"][0] != 0
    faengt = probe_rot and "der Verlauf ist voll" in r20["probe"][1]
    if not faengt:
        abweichungen += 1
    zeilen.append("{0} Gegenprobe kapazitaet-20: Bau {1}, verlauf_probe {2}, Meldung "
                  "\"der Verlauf ist voll\": {3}".format(
                      "OK  " if faengt else "ROT ",
                      "gruen" if r20["gebaut"] else "ROT",
                      "ROT" if probe_rot else "GRUEN (die Probe laeuft leer)",
                      "ja" if faengt else "NEIN"))

    # --- Bedingung 2, mechanisch am Quelltext --------------------------------------
    befunde, zahlkonstanten = kopf_gelesen()
    for text, erfuellt in befunde:
        if not erfuellt:
            abweichungen += 1
        zeilen.append("{0} Bedingung 2: {1}".format("OK  " if erfuellt else "ROT ", text))

    # --- Der Bericht ---------------------------------------------------------------
    bericht = ["# Messung zu Paket 0144 -- Nachweis", ""]
    bericht.append("Erzeugt von `befunde/messung-0144/nachweis.py`. Kein Modell, keine "
                   "Einschaetzung -- Uebersetzer, `ctest` und die Proben im Wortlaut.")
    bericht.append("")
    bericht.append("**Bezugsstand.** Der Baum *vorher* ist der Arbeitsbaum dieses Laufs "
                   "mit den drei Dateien aus `befunde/messung-0144/vorher/` an ihrer "
                   "Stelle -- also der unmittelbar vorhergehende Stand desselben Baums, "
                   "als Kopie eingefroren und nicht als Git-Verweis. Gemessen am {0}, "
                   "Git-Stand `{1}`.".format(HEUTE, GITSTAND))
    bericht.append("")
    bericht.append("## Ergebnis")
    bericht.append("")
    bericht.append("```")
    bericht.extend(zeilen)
    bericht.append("Abweichungen: {0}".format(abweichungen))
    bericht.append("```")
    bericht.append("")
    bericht.append("Zahlkonstanten im Kopf des Kastens: {0}".format(
        ", ".join("{0} = {1}".format(n, w) for n, w in zahlkonstanten) or "keine"))

    for profil in ("ON", "OFF"):
        if profil not in stand:
            continue
        vorher, nachher, _ = stand[profil]
        bericht.append("")
        bericht.append("## FABRIK_SANITIZER={0}, Baum nachher".format(profil))
        bericht.append("")
        bericht.append(marken(nachher["protokoll"]))
        bericht.append("### verlauf_probe im Wortlaut -- nachher")
        bericht.append("")
        bericht.append("```")
        bericht.append("Code {0}".format(nachher["proben"]["verlauf_probe"][0]))
        bericht.append(nachher["proben"]["verlauf_probe"][1].rstrip())
        bericht.append("```")
        bericht.append("")
        bericht.append("### verlauf_probe im Wortlaut -- vorher (dieselbe Probe, alter "
                       "Kasten: sie zaehlt nur bis vier)")
        bericht.append("")
        bericht.append("```")
        bericht.append("Code {0}".format(vorher["proben"]["verlauf_probe"][0]))
        bericht.append(vorher["proben"]["verlauf_probe"][1].rstrip())
        bericht.append("```")

    bericht.append("")
    bericht.append("## Die drei Wegwerfbaeume im Wortlaut")
    for ergebnis, ueberschrift in ((r27, "kapazitaet-27 -- eine Runde ueber die Wand"),
                                   (alt27, "alte-schranke-27 -- derselbe Verstoss, alte "
                                           "Schranke daneben"),
                                   (r20, "kapazitaet-20 -- wieder an R gebunden")):
        bericht.append("")
        bericht.append("### {0}".format(ueberschrift))
        bericht.append("")
        bericht.append("```")
        bericht.append("Bau: {0}".format("gruen" if ergebnis["gebaut"] else "ROT"))
        letzte = [z for z in (ergebnis["aus"] or "").splitlines() if z.strip()][-12:]
        bericht.extend(letzte)
        if ergebnis["probe"] is not None:
            bericht.append("--- verlauf_probe Code {0} ---".format(ergebnis["probe"][0]))
            bericht.extend([z for z in ergebnis["probe"][1].splitlines() if z.strip()][-8:])
        bericht.append("```")

    pfad = HIER / "bericht.md"
    pfad.write_text("\n".join(bericht) + "\n", encoding="utf-8")
    print("\n".join(zeilen))
    print("Abweichungen: {0}".format(abweichungen))
    print("Bericht: {0}".format(pfad))
    return abweichungen


if __name__ == "__main__":
    raise SystemExit(1 if hauptlauf() else 0)
