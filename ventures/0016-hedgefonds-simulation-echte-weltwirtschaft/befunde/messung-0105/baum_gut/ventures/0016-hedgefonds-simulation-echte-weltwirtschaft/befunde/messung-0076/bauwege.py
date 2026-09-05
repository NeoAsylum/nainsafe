#!/usr/bin/env python3
"""Die drei Bauwege in beiden Profilen -- gegen den eigenen Stand davor, nicht gegen
eine feste Zahl.

Konfiguriert den Arbeitsbereich, `kern` allein und `pruefstand` allein je in einen
Wegwerf-Baum unter `$TMPDIR`, baut ihn und faehrt `ctest`. Zweimal: einmal mit
`FABRIK_SANITIZER=ON` (Vorgabe, ADR 0011 Massnahme 2) und einmal mit `OFF`. Der
Arbeitsbaum bleibt unberuehrt -- kein `build/` im Repo.

Aufruf aus WSL heraus:

    python3 befunde/messung-0076/bauwege.py vorher
    python3 befunde/messung-0076/bauwege.py nachher
    python3 befunde/messung-0076/bauwege.py nachher --gegen-datei <ablage>/stand.json

Der erste Wortteil ist nur die Ablage; gemessen wird immer der Baum, in dem dieses
Skript liegt, so wie er gerade dasteht.

Der Vergleichsstand
-------------------

Bis zum 2026-09-05 stand die erwartete Zahl uebersetzender Ziele als Tripel im
Quelltext (`"arbeitsbereich": (WURZEL, 16, {"ON": 18, "OFF": 16})`). Sie war zu dem
Zeitpunkt schon falsch: Der Baum meldete 19 und 17, das Skript meldete `2
Abweichung(en)` und Rueckgabewert 1 an einem Baum, an dem nichts falsch war. Die Zahl
haengt an den Manifesten der Mitglieder und waechst mit jedem neuen Ziel; eine feste
Zahl im Messgeraet ist deshalb ein Wert mit Verfallsdatum, und ein Messgeraet, das
immer rot meldet, gewoehnt seine Leser daran, die Zahl zu ueberspringen. Paket 0104
hat daraus am 2026-09-05 die Regel gemacht: **Gleichheitsmass gegen den unmittelbar
vorhergehenden Stand desselben Baums und desselben Profils, keine ausgeschriebene
Sollzahl.** Dieses Skript folgt ihr.

Woher der Stand davor kommt, in dieser Reihenfolge:

1. `--gegen-datei <pfad>` -- die `stand.json`, die ein frueherer Lauf geschrieben hat.
   Das ist das Paar `vorher` / `nachher`: einmal vor der Aenderung laufen, einmal
   danach gegen dessen Ablage.
2. `--gegen <commit>` (Vorgabe: `HEAD`) -- der Stand wird selbst gemessen. Das Skript
   packt den Vorhabensbaum mit `git archive` aus dem Commit in einen Wegwerf-Baum
   unter `$TMPDIR` und konfiguriert dort dieselben drei Wege in denselben zwei
   Profilen. Gebaut und geprueft wird der Vergleichsstand nicht -- gezaehlt wird beim
   Konfigurieren, und alles darueber hinaus kostete Minuten ohne Aussage.

**Ist der Stand davor nicht zu bekommen, ist das eine Abweichung und kein
uebersprungener Punkt.** Kein Repo, ein unbekannter Commit, ein Vergleichsbaum, der
nicht konfiguriert: In all diesen Faellen faellt das Gleichheitsmass aus, und ein
ausgefallenes Mass, das gruen meldet, ist genau der Fehler, gegen den diese Fassung
geschrieben ist. Deshalb gibt es keinen Schalter, der den Vergleich abschaltet.

Zahlen, die hier trotzdem stehen duerfen, tragen Bauweg, Profil, Datum und Stand
(Paket 0104). Gemessen am 2026-09-05 am Stand `497bcbc`, mit dieser Fassung, in
Wegwerf-Baeumen unter `$TMPDIR`:

    FABRIK_SANITIZER=ON    Arbeitsbereich 20  kern allein 12  pruefstand allein 5
    FABRIK_SANITIZER=OFF   Arbeitsbereich 18  kern allein 11  pruefstand allein 4

Das ist ein Messwert von diesem Tag und keine Vorgabe. Wer ihn in eine Abnahme
schreibt, hat die Regel aus 0104 wieder gebrochen.

Wie schnell er verfaellt, ist an diesem Paket selbst zu sehen und nicht geschaetzt:
Waehrend seines Baulaufs, innerhalb einer knappen Stunde, stieg der Arbeitsbereich von
19 auf 20 (ON) und von 17 auf 18 (OFF) -- Paket 0083 legte nebenher ein uebersetzendes
Ziel an. Eine feste Zahl im Quelltext waere zwischen zwei Laeufen desselben Laufs
falsch geworden; das Gleichheitsmass hat beide Male gestimmt.
"""

import argparse
import json
import os
import re
import shutil
import subprocess
import tarfile
from datetime import date
from io import BytesIO
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]

# name -> Unterverzeichnis des Vorhabens, das als Bauwurzel dient. Ohne Sollzahl:
# Die einzige Erwartung dieses Skripts an die Zahl ist, dass sie dieselbe ist wie am
# Vergleichsstand -- und die steht nicht hier, sondern wird gemessen.
WEGE = {
    "arbeitsbereich": ".",
    "kern": "kern",
    "pruefstand": "pruefstand",
}
PROFILE = {"sanitizer-an": "ON", "sanitizer-aus": "OFF"}
MARKEN = ("uebersetzende Ziele", "Nullabhaengigkeit", "gefunden in", "es fehlen")

# Anker am ganzen Satzteil, nicht an "irgendeiner Zahl in der Zeile": Die Meldung des
# Riegels nennt hinter derselben Zahl noch die Schnittstellenziele, und eine Suche nach
# dem ersten Ziffernwort faende bei einer umgestellten Meldung stillschweigend die
# falsche. Gefunden wird ausserdem *jedes* Vorkommen -- sind es nicht genau eines, ist
# das eine Abweichung und keine Auswahlfrage.
ZIELZAHL = re.compile(r"(\d+) uebersetzende Ziele")


class Messfehler(Exception):
    """Der Vergleichsstand ist nicht zu bekommen. Kein Grund, gruen zu melden."""


def marken_zeilen(txt):
    return [t.strip() for t in txt.splitlines() if any(m in t for m in MARKEN)]


def zielzahl(txt):
    """(zahl, grund) -- `zahl` ist None, wenn die Meldung nicht eindeutig ist."""
    treffer = ZIELZAHL.findall(txt)
    if len(treffer) == 1:
        return int(treffer[0]), ""
    if not treffer:
        return None, "keine Zeile 'N uebersetzende Ziele' in der Ausgabe"
    return None, str(len(treffer)) + " Zeilen 'N uebersetzende Ziele' -- mehrdeutig"


def bauplatz_raeumen(quelle, bauverzeichnis):
    """Einen Baubaum wegwerfen, der zu einer anderen Quelle gehoert.

    Die Ablage haengt am Namen des Laufs, nicht am gemessenen Baum. Wer denselben
    Namen zweimal fuer zwei Baeume benutzt -- eine Gegenprobe an einem Wegwerf-Baum tut
    genau das --, faende sonst den Cache des ersten vor, und `cmake` braeche mit Code 1
    ab ("The current CMakeCache.txt is different than the one used to generate").
    Das saehe im Bericht aus wie ein kaputter Baum und waere keiner. Gemessen am
    2026-09-05 beim Bau dieser Fassung: sechs Bauwege, alle `konfig code=1`,
    `uebersetzende Ziele=None`, 16 Abweichungen an einem fehlerfreien Baum.

    Nur bei Nichtuebereinstimmung, damit der Normalfall inkrementell bleibt.
    """
    cache = bauverzeichnis / "CMakeCache.txt"
    if not cache.exists():
        return
    for zeile in cache.read_text(errors="replace").splitlines():
        if zeile.startswith("CMAKE_HOME_DIRECTORY:INTERNAL="):
            alt = zeile.split("=", 1)[1].strip()
            if alt and Path(alt) != Path(quelle).resolve():
                shutil.rmtree(bauverzeichnis)
            return


def konfigurieren(quelle, bauverzeichnis, wert):
    bauplatz_raeumen(quelle, bauverzeichnis)
    r = subprocess.run(["cmake", "-S", str(quelle), "-B", str(bauverzeichnis),
                        "-DFABRIK_SANITIZER=" + wert],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    zahl, grund = zielzahl(txt)
    return {"code": r.returncode, "zahl": zahl, "grund": grund,
            "zeilen": marken_zeilen(txt), "text": txt}


def git(argumente, cwd=WURZEL):
    r = subprocess.run(["git"] + argumente, cwd=str(cwd),
                       capture_output=True, text=True)
    if r.returncode != 0:
        raise Messfehler("`git " + " ".join(argumente) + "` gab Code "
                         + str(r.returncode) + ": " + (r.stderr.strip() or "(still)"))
    return r.stdout.strip()


def baum_auspacken(commit, ziel):
    """Den Vorhabensbaum aus `commit` nach `ziel` auspacken.

    Ueber `git archive` und nicht ueber eine Kopie des Arbeitsbaums: Gefragt ist der
    Stand *im Commit*, ohne unversionierte Dateien und ohne `bau/`. Der Pfad des
    Vorhabens innerhalb des Repos wird abgeschnitten, damit der Wegwerf-Baum dieselbe
    Gestalt hat wie der Arbeitsbaum -- `kern/CMakeLists.txt` bindet
    `../werkzeugkette.cmake` ein, also muss die Wurzel die Wurzel des Vorhabens sein.
    """
    oberstes = Path(git(["rev-parse", "--show-toplevel"]))
    innen = WURZEL.relative_to(oberstes).as_posix()
    argumente = ["archive", "--format=tar", commit]
    if innen != ".":
        argumente.append(innen)
    r = subprocess.run(["git"] + argumente, cwd=str(oberstes), capture_output=True)
    if r.returncode != 0:
        raise Messfehler("`git archive " + commit + "` gab Code " + str(r.returncode)
                         + ": " + r.stderr.decode("utf-8", "replace").strip())
    praefix = "" if innen == "." else innen + "/"
    ziel.mkdir(parents=True, exist_ok=True)
    with tarfile.open(fileobj=BytesIO(r.stdout)) as tar:
        glieder = []
        for g in tar.getmembers():
            if praefix and not g.name.startswith(praefix):
                continue
            g.name = g.name[len(praefix):] or "."
            glieder.append(g)
        if not glieder:
            raise Messfehler("`git archive " + commit + "` lieferte unter '" + praefix
                             + "' keine einzige Datei")
        tar.extractall(str(ziel), members=glieder, filter="data")


def stand_aus_commit(commit, ablage):
    """Den Vergleichsstand selbst messen: auspacken, konfigurieren, zaehlen."""
    kennung = git(["rev-parse", "--short", commit])
    datum = git(["show", "-s", "--format=%cs", commit])
    betreff = git(["show", "-s", "--format=%s", commit])
    baum = ablage / ("vergleichsstand-" + kennung)
    baum_auspacken(commit, baum)

    zahlen = {}
    for wert in sorted(set(PROFILE.values())):
        zahlen[wert] = {}
        for name, unter in WEGE.items():
            e = konfigurieren(baum / unter, baum / ("bau-" + wert + "-" + name), wert)
            (ablage / ("vergleichsstand-" + wert + "-" + name + "-konfig.log")
             ).write_text(e["text"])
            if e["code"] != 0 or e["zahl"] is None:
                raise Messfehler(
                    "Der Vergleichsstand " + kennung + " konfiguriert nicht: Bauweg '"
                    + name + "', Profil FABRIK_SANITIZER=" + wert + ", Code "
                    + str(e["code"]) + (", " + e["grund"] if e["grund"] else "")
                    + ". Log: " + str(ablage / ("vergleichsstand-" + wert + "-" + name
                                                + "-konfig.log")))
            zahlen[wert][name] = e["zahl"]
    return {"art": "commit", "stand": kennung, "datum": datum,
            "herkunft": "git " + kennung + " vom " + datum + " (\"" + betreff
                        + "\"), ausgepackt nach " + str(baum),
            "zahlen": zahlen}


def stand_aus_datei(pfad):
    p = Path(pfad)
    try:
        stand = json.loads(p.read_text())
    except OSError as f:
        raise Messfehler("Standdatei nicht lesbar: " + str(p) + " -- " + str(f))
    except ValueError as f:
        raise Messfehler("Standdatei ist kein JSON: " + str(p) + " -- " + str(f))
    # Die Datei stammt von einem frueheren Lauf desselben Skripts. Trotzdem geprueft,
    # und zwar vollstaendig: Ein Vergleich gegen einen halben Stand vergliche die
    # Haelfte und meldete fuer den Rest nichts -- also gruen.
    zahlen = stand.get("zahlen")
    if not isinstance(zahlen, dict):
        raise Messfehler("Standdatei ohne Feld 'zahlen': " + str(p))
    for wert in sorted(set(PROFILE.values())):
        for name in WEGE:
            if not isinstance(zahlen.get(wert, {}).get(name), int):
                raise Messfehler("Standdatei nennt keine Zahl fuer Profil "
                                 + wert + ", Bauweg '" + name + "': " + str(p))
    stand["herkunft"] = (stand.get("herkunft", "unbenannter Stand")
                         + " -- gelesen aus " + str(p))
    return stand


def eigener_stand(zahlen):
    """Was dieser Lauf gemessen hat, als Vergleichsstand fuer den naechsten."""
    try:
        kennung = git(["rev-parse", "--short", "HEAD"])
        schmutzig = bool(git(["status", "--porcelain", "--", str(WURZEL)]))
    except Messfehler:
        kennung, schmutzig = "ohne-git", False
    return {"art": "arbeitsbaum", "datum": date.today().isoformat(),
            "stand": kennung + ("+arbeitsbaum" if schmutzig else ""),
            "herkunft": "Arbeitsbaum " + str(WURZEL) + " am " + date.today().isoformat()
                        + " auf " + kennung
                        + (" mit unversionierten Aenderungen" if schmutzig else
                           " ohne Aenderung gegen den Commit"),
            "zahlen": zahlen}


def main():
    zerleger = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    zerleger.add_argument("marke", nargs="?", default="lauf",
                          help="Name der Ablage unter $TMPDIR")
    zerleger.add_argument("--gegen", default="HEAD", metavar="COMMIT",
                          help="Vergleichsstand selbst messen, aus diesem Commit "
                               "(Vorgabe: HEAD)")
    zerleger.add_argument("--gegen-datei", default=None, metavar="PFAD",
                          help="Vergleichsstand aus der stand.json eines frueheren Laufs")
    argumente = zerleger.parse_args()

    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / ("bauwege0076-" + argumente.marke)
    ablage.mkdir(parents=True, exist_ok=True)
    fehler = 0

    print("Gemessener Baum: " + str(WURZEL))
    try:
        if argumente.gegen_datei:
            stand = stand_aus_datei(argumente.gegen_datei)
        else:
            stand = stand_aus_commit(argumente.gegen, ablage)
    except Messfehler as f:
        stand = None
        # Kein `return` und kein stiller Verzicht: Der Rest der Messung -- baut es,
        # laeuft ctest -- ist ohne Vergleichsstand weiter aussagekraeftig und wird
        # gefahren. Nur das Gleichheitsmass faellt aus, und dafuer gibt es die
        # Abweichung hier.
        fehler += 1
        print("!! Vergleichsstand nicht zu bekommen: " + str(f))
        print("   Ohne ihn faellt das Gleichheitsmass ueber die Zielzahlen aus. Das "
              "zaehlt als Abweichung;")
        print("   ein ausgefallenes Mass, das gruen meldet, ist der Fehler, gegen den "
              "dieses Skript steht.")
    if stand:
        print("Stand davor: " + stand["herkunft"])
        for wert in sorted(set(PROFILE.values())):
            print("   FABRIK_SANITIZER=" + wert.ljust(4) + "  "
                  + "  ".join(n + "=" + str(stand["zahlen"][wert][n]) for n in WEGE))
    print("")

    gemessen = {wert: {} for wert in set(PROFILE.values())}
    for profil, wert in PROFILE.items():
        print("=== Profil " + profil + " (FABRIK_SANITIZER=" + wert + ") ===")
        for name, unter in WEGE.items():
            sollzahl = stand["zahlen"][wert][name] if stand else None
            b = ablage / (profil + "-" + name)
            e = konfigurieren(WURZEL / unter, b, wert)
            (ablage / (profil + "-" + name + "-konfig.log")).write_text(e["text"])
            gemessen[wert][name] = e["zahl"]

            # Drei Fragen, die auseinandergehalten gehoeren: Hat `cmake` ueberhaupt
            # durchkonfiguriert, war die Zahl ablesbar, und ist sie dieselbe wie davor.
            # Die dritte kann nur beantwortet werden, wenn es einen Stand gibt -- und
            # dass es keinen gab, steht dann oben schon als Abweichung.
            maengel = []
            if e["code"] != 0:
                maengel.append("konfig code=" + str(e["code"]))
            if e["zahl"] is None:
                maengel.append(e["grund"])
            elif sollzahl is not None and e["zahl"] != sollzahl:
                maengel.append("Zielzahl " + str(e["zahl"]) + " != Stand davor "
                               + str(sollzahl))
            if maengel:
                fehler += 1
            vergleich = ("Stand davor " + str(sollzahl) if sollzahl is not None
                         else "kein Stand davor")
            print(("!! " if maengel else "   ") + name.ljust(16) + " konfig code="
                  + str(e["code"]) + "  uebersetzende Ziele=" + str(e["zahl"])
                  + " (" + vergleich + ")"
                  + ("  -- " + "; ".join(maengel) if maengel else ""))
            for t in e["zeilen"]:
                print("        " + t[:150])

            rb = subprocess.run(["cmake", "--build", str(b), "-j", "4"],
                                capture_output=True, text=True)
            (ablage / (profil + "-" + name + "-bau.log")).write_text(rb.stdout + rb.stderr)
            print("   " + ("  " if rb.returncode == 0 else "!!") + " bau code=" + str(rb.returncode))
            if rb.returncode != 0:
                fehler += 1
                for t in (rb.stdout + rb.stderr).splitlines():
                    if "error:" in t:
                        print("        " + t.strip()[:150])
            rt = subprocess.run(["ctest", "--test-dir", str(b), "--output-on-failure",
                                 "--no-tests=error"],
                                capture_output=True, text=True)
            ttxt = rt.stdout + rt.stderr
            (ablage / (profil + "-" + name + "-ctest.log")).write_text(ttxt)
            bilanz = [t.strip() for t in ttxt.splitlines()
                      if "tests passed" in t or "No tests were found" in t]
            print("   " + ("  " if rt.returncode == 0 else "!!") + " ctest code="
                  + str(rt.returncode) + "  " + " | ".join(bilanz))
            if rt.returncode != 0:
                fehler += 1
                for t in ttxt.splitlines():
                    if "(Failed)" in t:
                        print("        " + t.strip()[:150])

    standdatei = ablage / "stand.json"
    standdatei.write_text(json.dumps(eigener_stand(gemessen), indent=2,
                                     ensure_ascii=False) + "\n")
    print("")
    print("Verglichen gegen: " + (stand["herkunft"] if stand else "nichts -- s. o."))
    print("Eigener Stand fuer den naechsten Lauf: " + str(standdatei))
    print(str(fehler) + " Abweichung(en). Ablage: " + str(ablage))
    return 1 if fehler else 0


if __name__ == "__main__":
    raise SystemExit(main())
