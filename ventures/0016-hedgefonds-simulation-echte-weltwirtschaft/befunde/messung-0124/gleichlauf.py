#!/usr/bin/env python3
"""Der Nachweis zu Paket 0124 -- die Zerlegung steht einmal, und nichts aendert sich.

Zwei Abnahmebedingungen, zwei Teile:

  1. `separate_arguments` steht in `werkzeugkette.cmake` genau einmal ausserhalb von
     Kommentaren, und beide Durchgaenge rufen die benannte Folge auf.
  2. Vorher-Stand und Nachher-Stand liefern an derselben Eintragsmatrix zeichengleiche
     Konfigurationsausgabe; dazu der unveraenderte Baum gruen mit gleicher Testzahl.

Der Vorher-Stand ist `befunde/messung-0124/werkzeugkette-vorher.cmake`, eine **Kopie**
aus dem Arbeitsbereich (md5 08aa087bb845c17d1e12e65679243513, 59408 Bytes, 2026-09-06)
und kein Git-Stand: Ein Fremdlauf, der mitten in der Messung committet, verschiebt
`HEAD`, die Kopie nicht.

Gefahren wird an zwei vollstaendigen Kopien des Arbeitsbereichs unter `$TMPDIR`, die
sich durch nichts als diese eine Datei unterscheiden. Die Angriffszeile haengt ueber
`-DCMAKE_PROJECT_INCLUDE` daran, der Arbeitsbaum bleibt unberuehrt.

    python3 befunde/messung-0124/gleichlauf.py

Rueckgabe 0 heisst `Abweichungen: 0`.
"""

import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
EIGEN = Path(__file__).resolve().parent
KETTE_VORHER = EIGEN / "werkzeugkette-vorher.cmake"

# Die Matrix steht so im Paket. Erwartet ist der Code, und wo das Paket ein Fundwort
# nennt, muss es in der Meldung stehen -- an **beiden** Staenden, denn dieses Paket
# aendert kein Verhalten.
MATRIX = [
    ("-Wl,-lz", 1, "-lz"),
    ("-l:z", 1, "-l:z"),
    ("SHELL:-Wl,-lz", 1, "-lz"),
    ("$<1:-lz>", 1, "-lz"),
    ("-Wl,-lz,-lssl", 1, "-lz"),
    ("/usr/lib/libz.so", 1, ""),
    ("-Wl,-l,z", 0, ""),
    ("/usr/lib/libz.so.1", 0, ""),
    ("-Wl,-z,now", 0, ""),
    (",,,", 0, ""),
]

def uebergehen(verzeichnis, namen):
    """Was nicht mitkopiert wird.

    `bau` traegt absolute Pfade auf den Arbeitsbaum, `befunde` wird verlinkt (siehe
    unten), und alles mit einem Punkt am Anfang gehoert der Werkzeugumgebung und nicht
    dem Erzeugnis -- der Bau liest davon nichts.
    """
    del verzeichnis
    return [n for n in namen if n == "bau" or n == "befunde" or n.startswith(".")]


def baum_anlegen(ziel, kette):
    """Eine vollstaendige Kopie des Arbeitsbereichs ohne Bauordner.

    Ein mitkopierter Bauordner traegt absolute Pfade auf den Arbeitsbaum und macht
    jede Messung zur Messung des falschen Baums.
    """
    # Die Lage wird nachgebaut, nicht nur der Inhalt: Der Belegstellenriegel sucht
    # seine `specs` als `<wurzel>/../../specs/<name des vorhabens>`. Ein flach
    # abgelegter Baum laesst ihn ins Leere greifen -- gemessen am 2026-09-06:
    # "'/tmp/.../specs/vorher' ist kein Verzeichnis", an beiden Staenden gleich.
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.mkdir(parents=True)
    (ziel / "specs").symlink_to(WURZEL.parents[1] / "specs")
    ziel = ziel / "ventures" / WURZEL.name
    shutil.copytree(WURZEL, ziel, ignore=uebergehen)
    # `befunde/` wird verlinkt statt kopiert: Es traegt 1,4 GB fremder Baubaeume, und
    # die Konfiguration braucht daraus genau eine Datei (`FABRIK_NACHBAU`). Gelesen
    # wird es von beiden Staenden gleich; geschrieben wird dorthin nicht.
    (ziel / "befunde").symlink_to(WURZEL / "befunde")
    if kette is not None:
        shutil.copyfile(kette, ziel / "werkzeugkette.cmake")
    return ziel


def normieren(text, baum, bau):
    """Alles wegnehmen, was zwischen zwei Baeumen verschieden sein **darf**.

    Das sind genau zwei Dinge: die Pfade der zwei Wegwerfbaeume und die
    Zeitangaben, die CMake in `Configuring done (0.1s)` druckt. Bliebe eines von
    beiden stehen, waere die Bedingung "zeichengleich" nie erfuellbar und der
    Nachweis wertlos.
    """
    text = text.replace(str(bau), "<bau>").replace(str(baum), "<baum>")
    text = re.sub(r"\(\d+[.,]\d+s\)", "(<zeit>)", text)
    return text


MUSTER_KETTE = re.compile(r"(werkzeugkette\.cmake:)(\d+)")


def zeilennummern_tilgen(text):
    """Die Zeilennummern **der Kette selbst** aus dem Aufrufkeller nehmen.

    Die benannte Folge steht vierundvierzig Zeilen ueber beiden Aufrufstellen, also
    verschiebt sie jede spaetere Zeilennummer um denselben Betrag. Das ist die einzige
    zulaessige Abweichung, und sie wird nicht einfach weggetilgt: `versatz` unten
    verlangt, dass **jeder** Unterschied von dieser Bauart ist und dass alle denselben
    Betrag tragen. Bliebe irgendwo eine Meldung mit anderem Inhalt, faellt sie dort auf.
    """
    return MUSTER_KETTE.sub(r"\1<zeile>", text)


def angriffsdatei(ablage, nummer, eintrag):
    """Die Angriffszeile als `CMAKE_PROJECT_INCLUDE`, nicht im Wurzelmanifest.

    Sie wird direkt hinter `project()` eingebunden und damit **vor** der Zeile, die
    `werkzeugkette.cmake` einbindet. Der aufgeschobene Aufruf steht deshalb vor dem
    aufgeschobenen Riegel in der Reihe und ist gesetzt, wenn dieser liest; ein Ziel
    namens `kern` gibt es zu diesem Zeitpunkt noch nicht.
    """
    d = ablage / ("angriff-" + str(nummer) + ".cmake")
    d.write_text(
        "cmake_language(DEFER DIRECTORY " + chr(34) + "${CMAKE_SOURCE_DIR}" + chr(34)
        + " CALL target_link_options kern INTERFACE [==[" + eintrag + "]==])\n")
    return d


def konfigurieren(baum, bau, zusatz):
    # Immer aus dem Leeren. Ein stehengebliebener Baubaum eines frueheren Laufs traegt
    # den Quellpfad im Zwischenspeicher und laesst cmake mit "does not match the source
    # used to generate cache" abbrechen -- an beiden Staenden gleich, also unauffaellig
    # falsch.
    if bau.exists():
        shutil.rmtree(bau)
    bau.mkdir(parents=True)
    lauf = subprocess.run(["cmake", "-S", str(baum), "-B", str(bau),
                           "-DFABRIK_SANITIZER=ON"] + zusatz,
                          capture_output=True, text=True)
    return lauf.returncode, normieren(lauf.stdout + lauf.stderr, baum, bau)


def teil1(bericht):
    """Bedingung 1 -- die Zerlegung steht nur noch einmal."""
    zeilen = (WURZEL / "werkzeugkette.cmake").read_text().splitlines()
    code = [s for s in zeilen if not s.lstrip().startswith("#")]
    einmal = [s for s in code if "separate_arguments" in s]
    aufrufe = [s for s in code if "fabrik_schalter_zerlegen(" in s]
    bericht.append("Bedingung 1")
    for s in einmal + [s for s in code
                       if s.startswith("macro(fabrik_schalter_zerlegen")] + aufrufe:
        bericht.append("    " + s.strip())
    # Vier Zeilen: die eine Zerlegung, ihre Makrozeile und die zwei Aufrufstellen.
    fehlt = 0
    if len(einmal) != 1:
        fehlt += 1
    if len(aufrufe) != 2:
        fehlt += 1
    benannt = [s for s in code if s.startswith("macro(fabrik_schalter_zerlegen")]
    if len(benannt) != 1:
        fehlt += 1
    bericht.append("    " + str(len(einmal)) + " x separate_arguments (soll 1), "
                   + str(len(benannt)) + " x die benannte Folge (soll 1), "
                   + str(len(aufrufe)) + " Aufrufstellen (soll 2)")
    return fehlt


def teil2(baeume, ablage, bericht):
    """Bedingung 2, erster Teil -- dieselbe Matrix, zeichengleiche Ausgabe."""
    fehlt = 0
    bericht.append("Bedingung 2a -- Eintragsmatrix, je an kern INTERFACE")
    for nummer, (eintrag, sollcode, fundwort) in enumerate(MATRIX):
        ausgaben = {}
        codes = {}
        for stand, baum in baeume.items():
            hang = angriffsdatei(ablage, nummer, eintrag)
            bau = ablage / ("bau-" + stand + "-" + str(nummer))
            codes[stand], ausgaben[stand] = konfigurieren(
                baum, bau, ["-DCMAKE_PROJECT_INCLUDE=" + str(hang)])
        roh = ausgaben["vorher"] == ausgaben["nachher"]
        nurzeilen, versaetze = versatz(ausgaben["vorher"], ausgaben["nachher"])
        gleich = (zeilennummern_tilgen(ausgaben["vorher"])
                  == zeilennummern_tilgen(ausgaben["nachher"])) and nurzeilen
        codepasst = all(c == sollcode for c in codes.values())
        wortpasst = (not fundwort
                     or all("Fundwort: " + fundwort in a for a in ausgaben.values()))
        # Ein Versatz, ueberall derselbe. Zwei verschiedene Betraege waeren
        # keine Verschiebung mehr, sondern eine geaenderte Meldung.
        gut = gleich and codepasst and wortpasst and len(versaetze) <= 1
        if not gut:
            fehlt += 1
        bericht.append(("    " if gut else "!!  ") + eintrag.ljust(20)
                       + " code=" + str(codes["vorher"]) + "/" + str(codes["nachher"])
                       + " (soll " + str(sollcode) + ")"
                       + "  zeichengleich=" + str(roh)
                       + " (bis auf Kettenzeilen: " + str(gleich)
                       + ", Versatz " + str(sorted(versaetze)) + ")"
                       + ("" if not fundwort else "  Fundwort " + fundwort
                          + "=" + str(wortpasst)))
        if not gleich:
            fehlt += 0
            for zeile in unterschied(ausgaben["vorher"], ausgaben["nachher"]):
                bericht.append("        " + zeile)
    return fehlt


def versatz(a, b):
    """Trennt zwei Ausgaben nichts als Zeilennummern der Kette -- und welcher Versatz?

    Rueckgabe (nur_zeilennummern, Menge der Versaetze). Eine Menge mit genau einem
    Element heisst: derselbe Betrag ueberall, also eine Verschiebung und keine
    Verhaltensaenderung.
    """
    za, zb = a.splitlines(), b.splitlines()
    if len(za) != len(zb):
        return False, set()
    versaetze = set()
    for x, y in zip(za, zb):
        if x == y:
            continue
        if zeilennummern_tilgen(x) != zeilennummern_tilgen(y):
            return False, versaetze
        nx = [int(p[1]) for p in MUSTER_KETTE.findall(x)]
        ny = [int(p[1]) for p in MUSTER_KETTE.findall(y)]
        versaetze.update(b - a for a, b in zip(nx, ny))
    return True, versaetze


def unterschied(a, b):
    """Die ersten Zeilen, in denen sich zwei Ausgaben unterscheiden."""
    za, zb = a.splitlines(), b.splitlines()
    raus = []
    for i in range(max(len(za), len(zb))):
        x = za[i] if i < len(za) else "<fehlt>"
        y = zb[i] if i < len(zb) else "<fehlt>"
        if x != y:
            raus.append("vorher : " + x[:150])
            raus.append("nachher: " + y[:150])
        if len(raus) >= 6:
            break
    return raus


def warten_bis_baubar(ablage, bericht):
    """Bis der **fremde** Baum wieder uebersetzt -- an einer Wegwerfkopie geprueft.

    Am 2026-09-06 lag `kern/test/werte_probe.cpp` halbfertig im Arbeitsbereich (ein
    Lauf schrieb gerade daran) und brach mit `expected } at end of input` ab. Das sagt
    nichts ueber dieses Paket, macht aber jede Messung rot. Geprueft wird deshalb an
    einer eigenen Kopie, und erst wenn die uebersetzt, laeuft der Vergleich.
    """
    grenze = int(os.environ.get("FABRIK_WARTEN", "45"))
    for versuch in range(grenze):
        probe = baum_anlegen(ablage / "probe", None)
        bau = ablage / "bau-probe"
        code, _ = konfigurieren(probe, bau, [])
        if code == 0:
            lauf = subprocess.run(["cmake", "--build", str(bau), "-j", "4"],
                                  capture_output=True, text=True)
            if lauf.returncode == 0:
                bericht.append("    Fremdbaum uebersetzt nach " + str(versuch)
                               + " Wartezyklen.")
                return True
            fehler = [s for s in (lauf.stdout + lauf.stderr).splitlines()
                      if "error:" in s]
        else:
            fehler = ["Konfiguration Code " + str(code)]
        if versuch == 0:
            bericht.append("    Fremdbaum uebersetzt nicht, warte: "
                           + (fehler[0][:160] if fehler else "?"))
        time.sleep(60)
    bericht.append("!!  Fremdbaum uebersetzt auch nach " + str(grenze)
                   + " Minuten nicht -- Teil 2b nicht gefahren.")
    return False


def teil3(baeume, ablage, bericht):
    """Bedingung 2, zweiter Teil -- der unveraenderte Baum, gebaut und gefahren."""
    fehlt = 0
    bericht.append("Bedingung 2b -- unveraenderter Baum, FABRIK_SANITIZER=ON")
    zahlen = {}
    for stand, baum in baeume.items():
        bau = ablage / ("bau-voll-" + stand)
        code, text = konfigurieren(baum, bau, [])
        if code != 0:
            bericht.append("!!  " + stand + ": Konfiguration Code " + str(code))
            bericht.append("        " + text[-400:].replace(chr(10), " | "))
            fehlt += 1
            continue
        bauen = subprocess.run(["cmake", "--build", str(bau), "-j", "4"],
                               capture_output=True, text=True)
        if bauen.returncode != 0:
            bericht.append("!!  " + stand + ": Bau Code " + str(bauen.returncode))
            bericht.append("        "
                           + (bauen.stdout + bauen.stderr)[-400:].replace(chr(10), " | "))
            fehlt += 1
            continue
        pruef = subprocess.run(["ctest", "--test-dir", str(bau), "--output-on-failure"],
                               capture_output=True, text=True)
        ganz = pruef.stdout + pruef.stderr
        (ablage / ("ctest-" + stand + ".log")).write_text(ganz)
        treffer = re.search(r"(\d+)% tests passed, (\d+) tests failed out of (\d+)", ganz)
        zahlen[stand] = (pruef.returncode, treffer.group(0) if treffer else "?")
        bericht.append("    " + stand + ": ctest Code " + str(pruef.returncode)
                       + " -- " + zahlen[stand][1])
    if len(zahlen) == 2 and len(set(zahlen.values())) != 1:
        bericht.append("!!  Die zwei Staende unterscheiden sich im Testlauf.")
        fehlt += 1
    if any(c != 0 for c, _ in zahlen.values()):
        fehlt += 1
    return fehlt


# Je Durchgang eine Angriffszeile, die nur ueber die Zerlegung zu sehen ist: Beide
# verstecken den Schalter in einem Generatorausdruck, den erst die Trennzeichenklasse
# aufbricht. Der erste laeuft in den Nullabhaengigkeitsdurchgang, der zweite in den
# Durchgang gegen Pauschalabschalter -- das ist die zweite Aufrufstelle, die die Matrix
# oben gar nicht beruehrt.
VERDRAHTUNG = [
    ("nullabhaengigkeit", "target_link_options", "$<1:-lz>"),
    ("pauschalabschalter", "target_compile_options", "$<1:-w>"),
]


def teil4(ablage, bericht):
    """Gegenprobe: Ohne die benannte Folge muss beides blind werden.

    Eine Messung, die nur gruen sein kann, belegt nichts. Hier wird der Kette **eine**
    Zeile aus der benannten Folge genommen -- die Trennzeichenklasse -- und derselbe
    Angriff noch einmal gefahren. Faellt danach ein Durchgang **nicht** aus, laeuft er
    nicht ueber die benannte Folge, und die Zusammenlegung hat ihn verloren.
    """
    fehlt = 0
    bericht.append("Gegenprobe -- dieselben Angriffe ohne die Trennzeichenklasse")
    kette = (WURZEL / "werkzeugkette.cmake").read_text()
    zeile = ('  string(REGEX REPLACE "[$<>:,]" " " fabrik_zerlegt'
             ' "${fabrik_zerlegt}")\n')
    if kette.count(zeile) != 1:
        bericht.append("!!  Die zu entfernende Zeile kommt " + str(kette.count(zeile))
                       + " mal vor -- nicht mutiert, also nichts belegt.")
        return 1
    verstuemmelt = ablage / "mutiert.cmake"
    verstuemmelt.write_text(kette.replace(zeile, ""))
    baeume = {"heil": baum_anlegen(ablage / "g-heil", None),
              "blind": baum_anlegen(ablage / "g-blind", verstuemmelt)}
    for nummer, (name, befehl, eintrag) in enumerate(VERDRAHTUNG):
        codes = {}
        for stand, baum in baeume.items():
            hang = ablage / ("verdrahtung-" + str(nummer) + ".cmake")
            hang.write_text(
                "cmake_language(DEFER DIRECTORY " + chr(34) + "${CMAKE_SOURCE_DIR}"
                + chr(34) + " CALL " + befehl + " kern INTERFACE [==[" + eintrag
                + "]==])\n")
            bau = ablage / ("bau-g-" + stand + "-" + str(nummer))
            codes[stand], _ = konfigurieren(
                baum, bau, ["-DCMAKE_PROJECT_INCLUDE=" + str(hang)])
        gut = codes["heil"] == 1 and codes["blind"] == 0
        if not gut:
            fehlt += 1
        bericht.append(("    " if gut else "!!  ") + name.ljust(20) + eintrag.ljust(10)
                       + " heil=" + str(codes["heil"]) + " (soll 1)"
                       + "  ohne Trennzeichenklasse=" + str(codes["blind"])
                       + " (soll 0)")
    return fehlt


def main():
    if not KETTE_VORHER.is_file():
        print("FEHLT: " + str(KETTE_VORHER))
        return 2
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / "messung0124"
    ablage.mkdir(parents=True, exist_ok=True)
    baeume = {"vorher": baum_anlegen(ablage / "vorher", KETTE_VORHER),
              "nachher": baum_anlegen(ablage / "nachher", None)}
    bericht = []
    fehlt = teil1(bericht)
    fehlt += teil2(baeume, ablage, bericht)
    fehlt += teil4(ablage, bericht)
    if warten_bis_baubar(ablage, bericht):
        # Neu kopiert, nachdem der Fremdlauf fertig ist: Die zwei Baeume oben tragen
        # noch dessen halbfertige Datei, und Teil 2b baut wirklich.
        baeume = {"vorher": baum_anlegen(ablage / "vorher", KETTE_VORHER),
                  "nachher": baum_anlegen(ablage / "nachher", None)}
        fehlt += teil3(baeume, ablage, bericht)
    else:
        fehlt += 1
    for zeile in bericht:
        print(zeile)
    print("")
    print("Abweichungen: " + str(fehlt))
    return 1 if fehlt else 0


if __name__ == "__main__":
    sys.exit(main())
