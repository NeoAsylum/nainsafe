#!/usr/bin/env python3
"""Nachweis zu Paket 0132: Die Meldung des Schlussriegels nennt die eingesammelten
Eintraege -- und ein stumpf gemachtes `fabrik_riegel_sammeln` faellt an dieser Zahl auf.

Vier Laeufe, zwei Wegwerf-Baeume mit je einem Ziel und einer Quelldatei ohne eigene
Schalter, zwei Fassungen der Kette. Welche Fassung ein Lauf einbindet, entscheidet
allein der Schalter `-DFABRIK_KETTE=`: A und B fahren damit denselben Quellbaum,
Byte fuer Byte, und C und D ebenso.

    A  ohne -w, unveraendert   Code 0, gruene Meldung, Zaehler > 0
    B  ohne -w, stumpf         Code 0, gruene Meldung, Zaehler 0
    C  mit  -w, unveraendert   Code 1 -- der Riegel greift
    D  mit  -w, stumpf         Code 0, gruene Meldung; der Zaehler ist das Einzige,
                               was diesen Baum noch von A unterscheidet

A und B sind die Abnahmebedingung 1: gleicher Code, zeichengleicher Satz daneben, und
allein die neue Zahl trennt sie. C und D stehen dabei, weil "stumpf" sonst eine
Behauptung ueber die Mutation waere und keine Messung -- C zeigt, dass die
unveraenderte Fassung hier wirklich abbricht, D, dass die mutierte es nicht mehr tut.

Die stumpfe Fassung wird nicht eingecheckt; sie entsteht in der Ablage unter `$TMPDIR`
und ist das Messwerkzeug.

Aufruf aus WSL heraus:

    python3 befunde/messung-0132/zaehler.py

Rueckgabewert 0 heisst: keine Abweichung.
"""

import os
import re
import shutil
import subprocess
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
KETTE = WURZEL / "werkzeugkette.cmake"
QUELLE = "int f(double d){ int i = d; return i; }\n"

# Der Suchtext der Mutation muss genau einmal vorkommen. Eine Bereichspruefung, die
# wortgleich an zwei Stellen steht, mutierte sonst still nur eine davon -- und der
# Unterschied, den diese Messung zeigt, waere ein anderer als der behauptete.
SUCHE = '  if(NOT "${${listenname}}" STREQUAL "")\n'
ERSATZ = "  if(FALSE)  # stumpf gemacht -- allein fuer diese Messung\n"

SATZ = "alle mit Warnsatz und ohne Pauschalabschalter"
RIEGEL = re.compile(r"^-- (Warnsatz-Schlussriegel: .*)$", re.M)
ZAHL = re.compile(r"Eingesammelt und gegen die Pauschalmuster gehalten: (\d+) ")


def ketten_schreiben(ablage):
    """Beide Fassungen als eigene Dateien -- nie die Kette im Arbeitsbaum einbinden."""
    roh = KETTE.read_text(encoding="utf-8")
    if roh.count(SUCHE) != 1:
        raise SystemExit("Der Suchtext der Mutation kommt " + str(roh.count(SUCHE))
                         + " mal vor, erwartet war genau einmal.")
    unveraendert = ablage / "kette-unveraendert.cmake"
    stumpf = ablage / "kette-stumpf.cmake"
    unveraendert.write_text(roh, encoding="utf-8")
    stumpf.write_text(roh.replace(SUCHE, ERSATZ), encoding="utf-8")
    return unveraendert, stumpf


def baum_anlegen(ablage, name, mit_w):
    """Ein Ziel, eine Quelldatei. Welche Kette gilt, kommt erst beim Konfigurieren."""
    d = ablage / ("baum-" + name)
    if d.exists():
        shutil.rmtree(d)
    d.mkdir(parents=True)
    (d / "z.cpp").write_text(QUELLE)
    rumpf = "add_library(z STATIC z.cpp)\nfabrik_warnsatz_anlegen(z)\n"
    if mit_w:
        rumpf += "target_compile_options(z PRIVATE -w)\n"
    (d / "CMakeLists.txt").write_text(
        "cmake_minimum_required(VERSION 3.22)\nproject(z LANGUAGES CXX)\n"
        "include(${FABRIK_KETTE})\n" + rumpf)
    return d


def fahren(ablage, marke, quelle, kette):
    """Jeder Baubaum aus dem Leeren: Ein stehengebliebener bricht mit `does not match
    the source used to generate cache` ab -- an beiden Fassungen gleich, sieht also nach
    Gleichstand aus und ist keiner."""
    bau = ablage / ("bau-" + marke)
    if bau.exists():
        shutil.rmtree(bau)
    r = subprocess.run(["cmake", "-S", str(quelle), "-B", str(bau),
                        "-DFABRIK_KETTE=" + str(kette)],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    (ablage / (marke + "-konfig.log")).write_text(txt)
    zeile = RIEGEL.search(txt)
    treffer = ZAHL.findall(txt)
    return {"marke": marke, "code": r.returncode, "text": txt, "quelle": quelle,
            "zeile": zeile.group(1) if zeile else "",
            "zahl": int(treffer[0]) if len(treffer) == 1 else None}


def ohne_zaehler(zeile):
    """Die Riegelzeile ohne den neuen Satzteil -- der Rest muss zeichengleich sein.

    Abgeschnitten wird am Wort, nicht an der Zahl: Wer nur die Ziffern tilgt,
    laesst den Rest des Satzteils stehen und vergleicht ihn mit.
    """
    return zeile.split("Eingesammelt")[0].strip()


def pruefen(bedingung, text, gemessen):
    zeichen = "  " if bedingung else "!!"
    print(zeichen + " " + text + "   [" + gemessen + "]")
    return 0 if bedingung else 1


def main():
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / "messung0132"
    ablage.mkdir(parents=True, exist_ok=True)
    unveraendert, stumpf = ketten_schreiben(ablage)
    print("Gemessene Kette: " + str(KETTE) + "  ("
          + str(KETTE.stat().st_size) + " Bytes)")
    print("Ablage:          " + str(ablage))
    print("Die Mutation:    " + SUCHE.strip() + "  ->  " + ERSATZ.strip())
    print("")

    ohne = baum_anlegen(ablage, "ohne-w", False)
    mit = baum_anlegen(ablage, "mit-w", True)
    a = fahren(ablage, "A-ohne-w-unveraendert", ohne, unveraendert)
    b = fahren(ablage, "B-ohne-w-stumpf", ohne, stumpf)
    c = fahren(ablage, "C-mit-w-unveraendert", mit, unveraendert)
    d = fahren(ablage, "D-mit-w-stumpf", mit, stumpf)

    for e in (a, b, c, d):
        print(e["marke"].ljust(22) + " code=" + str(e["code"])
              + "  Zaehler=" + str(e["zahl"]))
        print("        " + (e["zeile"][:170] or "(keine Riegelzeile -- abgebrochen)"))
    print("")
    f = 0
    f += pruefen(a["quelle"] == b["quelle"],
                 "A und B fahren denselben Quellbaum", str(ohne))
    f += pruefen(a["code"] == 0 and b["code"] == 0,
                 "beide konfigurieren Code 0",
                 str(a["code"]) + " und " + str(b["code"]))
    f += pruefen(SATZ in a["text"] and SATZ in b["text"],
                 "beide melden `" + SATZ + "`", "zweimal vorhanden")
    f += pruefen(bool(ohne_zaehler(a["zeile"]))
                 and ohne_zaehler(a["zeile"]) == ohne_zaehler(b["zeile"]),
                 "die Riegelzeile ohne den Zaehler ist zeichengleich",
                 ohne_zaehler(a["zeile"]))
    f += pruefen(a["zahl"] is not None and b["zahl"] is not None
                 and a["zahl"] != b["zahl"],
                 "allein die neue Zahl unterscheidet A und B",
                 str(a["zahl"]) + " gegen " + str(b["zahl"]))
    f += pruefen(a["zahl"] not in (None, 0),
                 "die unveraenderte Fassung sammelt ein", str(a["zahl"]))
    f += pruefen(b["zahl"] == 0,
                 "die stumpfe Fassung sammelt nichts mehr ein", str(b["zahl"]))

    # Die Gegenprobe zur Mutation: Ohne sie waere "stumpf" ein Wort und keine Messung.
    f += pruefen(c["code"] != 0 and "hebt den Satz wieder auf" in c["text"],
                 "C: die unveraenderte Fassung bricht an `-w` ab",
                 "code=" + str(c["code"]))
    f += pruefen(d["code"] == 0 and SATZ in d["text"],
                 "D: die stumpfe Fassung laesst dasselbe `-w` gruen durch",
                 "code=" + str(d["code"]))
    f += pruefen(bool(ohne_zaehler(a["zeile"]))
                 and ohne_zaehler(d["zeile"]) == ohne_zaehler(a["zeile"]),
                 "D meldet ausser dem Zaehler zeichengleich dasselbe wie A",
                 ohne_zaehler(d["zeile"]))
    f += pruefen(d["zahl"] == 0,
                 "und der Zaehler ist das Einzige, was den Unterschied traegt",
                 str(a["zahl"]) + " gegen " + str(d["zahl"]))

    print("")
    print("Abweichungen: " + str(f))
    return 1 if f else 0


if __name__ == "__main__":
    raise SystemExit(main())
