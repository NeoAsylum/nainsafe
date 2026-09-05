#!/usr/bin/env python3
"""Der Pruefstand der Pruefung von Paket 0066 -- zum Nachbauen.

Er legt 22 Wegwerf-Baeume unter $TMPDIR an, haengt in jeden per `include()` eine
Fassung von `werkzeugkette.cmake` und meldet je Baum den Konfigurationscode und die
Zeilen `gefunden in` / `es fehlen`.

Warum die Datei hier liegt und nicht bei den Aufgaben: `baulauf.py:116` sammelt unter
`befunde/` keine Manifeste ein, also stoert kein Wegwerf-Manifest den naechsten
Baulauf. Warum sie ueberhaupt bleibt: Der Schlussriegel hat keinen Regressionstest --
im echten Baum steht nirgends ein `-w`, also wird nichts rot, wenn jemand die Pruefung
stumpf macht. Diese Datei ist der billigste Ersatz.

Aufruf aus WSL heraus:

    python3 befunde/pruefung-0066/nachbau.py            # gegen HEAD
    python3 befunde/pruefung-0066/nachbau.py 8fff575^   # gegen den Stand vor 0066

Seit Paket 0133 (2026-09-05) ruft ihn ausserdem `ctest` von selbst: In
`pruefstand/CMakeLists.txt` haengt er als Probe `schlussriegel_nachbau` und laeuft
damit bei jeder Abnahme mit. Der Aufruf von Hand bleibt Wort fuer Wort derselbe.
Zwei Dinge unterscheiden den automatischen Lauf, beide ueber die Umgebung und
beide unten begruendet: `NACHBAU_ABLAGE` verlegt die Wegwerf-Baeume in den
Baubaum, und die Positivkontrolle zaehlt seither in den Rueckgabewert.

Die Sollspalte gilt fuer HEAD. Am Stand `8fff575^` (vor Paket 0066) laufen genau
zehn Baeume mit Code 0 durch, die heute Code 1 melden -- das ist die gemessene
Luecke, gegen die 0066 geschrieben ist:

    a1_zielflags  b1_quellflags  b1b_quellopt  b2_iface  e4_zweiworte
    e5_zweitequelle  e8_wnoerrorquelle  e10_genexquelle  f1_targetdir  x_unterbaum

Die uebrigen zwoelf urteilen an beiden Staenden gleich. Das gilt ausdruecklich auch
fuer `e1_addcompileopt` und `e2_dirprop`: Eine Verzeichniseigenschaft erbt in
`COMPILE_OPTIONS` des Ziels und wurde schon vorher gefangen -- der Weg ueber
`add_compile_options` war nie offen. Nachgemessen, nicht angenommen.
"""

import os
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
KETTE = WURZEL / "werkzeugkette.cmake"
QUELLE = "int f(double d){ int i = d; return i; }\n"
ZWEITE = "int g(double d){ int i = d; return i; }\n"

# name -> (soll-code am Stand HEAD, zusaetzliche Quelldateien, Rumpf der CMakeLists)
#
# Der Rumpf steht vollstaendig da und nicht als Schablone: Wer den Fall in drei Monaten
# liest, soll ihn abschreiben koennen, ohne diese Datei zu verstehen.
SATZ = "add_library(z STATIC z.cpp)\nfabrik_warnsatz_anlegen(z)\n"

BAEUME = {
    # --- Abnahmebedingung 1
    "a1_zielflags": (1, {}, SATZ + 'set_target_properties(z PROPERTIES COMPILE_FLAGS "-w")'),
    "p_positiv": (0, {}, SATZ),  # konfiguriert gruen, BAUT rot -- die Positivkontrolle
    # --- Abnahmebedingung 2
    "b1_quellflags": (1, {}, SATZ + 'set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")'),
    "b1b_quellopt": (1, {}, SATZ + 'set_source_files_properties(z.cpp PROPERTIES COMPILE_OPTIONS "-w")'),
    "b2_iface": (1, {}, SATZ + "add_library(iface INTERFACE)\n"
                 "target_compile_options(iface INTERFACE -w)\n"
                 "target_link_libraries(z PRIVATE iface)"),
    # --- Abnahmebedingung 3: nichts wird ueber-scharf
    "c1_wnoconv": (0, {}, SATZ + "target_compile_options(z PRIVATE -Wno-conversion)"),
    "c2_leereiface": (0, {}, SATZ + "add_library(x INTERFACE)"),
    "e7_ifacegut": (0, {}, SATZ + "add_library(gut INTERFACE)\n"
                    "target_compile_options(gut INTERFACE -Wno-conversion)\n"
                    "target_link_libraries(z PRIVATE gut)"),
    "e6_targetobjects": (0, {}, "add_library(obj OBJECT z.cpp)\nfabrik_warnsatz_anlegen(obj)\n"
                         "add_library(z STATIC $<TARGET_OBJECTS:obj>)\n"
                         "set_target_properties(z PROPERTIES LINKER_LANGUAGE CXX)\n"
                         "fabrik_warnsatz_anlegen(z)"),
    # --- alte Zusagen aus 0058 / 0060 / 0063
    "r1_ohnesatz": (1, {}, "add_library(z STATIC z.cpp)"),
    "r2_privatw": (1, {}, SATZ + "target_compile_options(z PRIVATE -w)"),
    "r3_shellform": (1, {}, SATZ + 'target_compile_options(z PRIVATE "SHELL:-Wno-error -w")'),
    "r4_staticpublic": (1, {}, SATZ + "target_compile_options(z PUBLIC -w)"),
    "r5_nurschnittstelle": (1, {}, "add_library(x INTERFACE)\ntarget_compile_options(x INTERFACE -Wall)"),
    # --- weitere Wege, die ich zu finden versucht habe
    "e1_addcompileopt": (1, {}, "add_compile_options(-w)\n" + SATZ),
    "e2_dirprop": (1, {}, "set_property(DIRECTORY APPEND PROPERTY COMPILE_OPTIONS -w)\n" + SATZ),
    "e4_zweiworte": (1, {}, SATZ + 'set_target_properties(z PROPERTIES COMPILE_FLAGS "-O0 -w")'),
    "e5_zweitequelle": (1, {"y.cpp": ZWEITE},
                        "add_library(z STATIC z.cpp y.cpp)\nfabrik_warnsatz_anlegen(z)\n"
                        'set_source_files_properties(y.cpp PROPERTIES COMPILE_FLAGS "-w")'),
    "e8_wnoerrorquelle": (1, {}, SATZ + 'set_source_files_properties(z.cpp PROPERTIES COMPILE_OPTIONS "-Wno-error=conversion")'),
    "e10_genexquelle": (1, {}, SATZ + 'set_source_files_properties(z.cpp PROPERTIES COMPILE_OPTIONS "$<1:-w>")'),
}

# Zwei Baeume mit Unterverzeichnis -- sie tragen den Kern der Sache. Alle Faelle der
# Abnahme spielen in EINEM Verzeichnis, im echten Baum steht dagegen kein einziges Ziel
# im obersten. Ohne `TARGET_DIRECTORY` an `get_source_file_property` faende der Riegel
# hier nichts und meldete gruen.
GESCHACHTELT = {
    "x_unterbaum": (1, {
        "CMakeLists.txt": "{kopf}add_subdirectory(mitglied)\n",
        "mitglied/CMakeLists.txt": "add_library(z STATIC src/z.cpp)\nfabrik_warnsatz_anlegen(z)\n"
                                   'set_source_files_properties(src/z.cpp PROPERTIES COMPILE_FLAGS "-w")\n',
        "mitglied/src/z.cpp": QUELLE,
    }),
    "f1_targetdir": (1, {
        "CMakeLists.txt": "{kopf}" + SATZ + "add_subdirectory(sub)\n",
        "z.cpp": QUELLE,
        "sub/CMakeLists.txt": "target_sources(z PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/y.cpp)\n"
                              "set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/y.cpp"
                              ' TARGET_DIRECTORY z PROPERTIES COMPILE_FLAGS "-w")\n',
        "sub/y.cpp": ZWEITE,
    }),
}


def kette_holen(stand: str, ablage: Path) -> Path:
    """Die zu pruefende Fassung als eigene Datei -- nie die im Baum einbinden."""
    ziel = ablage / "werkzeugkette.cmake"
    if stand == "HEAD":
        ziel.write_bytes(KETTE.read_bytes())
    else:
        rel = KETTE.relative_to(WURZEL.parents[1])
        roh = subprocess.run(["git", "-C", str(WURZEL.parents[1]), "show", f"{stand}:{rel}"],
                             capture_output=True, check=True).stdout
        ziel.write_bytes(roh)
    return ziel


def schreiben(d: Path, kette: Path, zusatz: dict, rumpf: str) -> None:
    d.mkdir(parents=True, exist_ok=True)
    (d / "z.cpp").write_text(QUELLE)
    for name, inhalt in zusatz.items():
        (d / name).write_text(inhalt)
    kopf = ("cmake_minimum_required(VERSION 3.22)\nproject(z LANGUAGES CXX)\n"
            f"include({kette})\n")
    (d / "CMakeLists.txt").write_text(kopf + rumpf + "\n")


def geschachtelt_schreiben(d: Path, kette: Path, dateien: dict) -> None:
    kopf = ("cmake_minimum_required(VERSION 3.22)\nproject(w LANGUAGES CXX)\n"
            f"include({kette})\n")
    for name, inhalt in dateien.items():
        p = d / name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(inhalt.replace("{kopf}", kopf) if "{kopf}" in inhalt else inhalt)


def fahren(d: Path) -> tuple[int, list[str]]:
    r = subprocess.run(["cmake", "-S", str(d), "-B", str(d / "build")],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    (d / "konfig.log").write_text(txt)
    marken = [z.strip() for z in txt.splitlines()
              if ("gefunden in" in z and "Zeile" not in z)
              or "es fehlen:" in z or "kein einziges uebersetzendes" in z]
    return r.returncode, marken


def main() -> int:
    stand = sys.argv[1] if len(sys.argv) > 1 else "HEAD"
    # Der Vorgabepfad haengt allein am **Stand**, nicht am **Baum**. Solange dieses
    # Skript nur von Hand im Arbeitsbaum lief, war das gleichgueltig. Als Probe laeuft
    # es auch in einem Wegwerf-Baum -- und die Gegenprobe zu Paket 0133 faehrt genau
    # zwei Baeume nacheinander, den unveraenderten und den stumpf gemachten. Beide
    # haetten unter demselben Pfad geschrieben und einander ihre Bauablagen und
    # `konfig.log`s hinterlassen; was dann rot ist, gehoerte womoeglich zum anderen
    # Baum. `NACHBAU_ABLAGE` trennt sie. Der Aufruf ohne die Variable verhaelt sich
    # unveraendert -- die zwei Abnahmen, die diesen Aufruf namentlich nennen (0103,
    # 0108), sehen denselben Pfad wie zuvor.
    vorgabe = Path(os.environ.get("TMPDIR", "/tmp")) / f"nachbau0066-{stand.replace('^', 'v')}"
    ablage = Path(os.environ.get("NACHBAU_ABLAGE") or vorgabe)
    ablage.mkdir(parents=True, exist_ok=True)
    kette = kette_holen(stand, ablage)
    print(f"Stand: {stand}   Kette: {kette}   ({kette.stat().st_size} Bytes)\n")

    abweichungen = 0
    for name in sorted(BAEUME) + sorted(GESCHACHTELT):
        d = ablage / name
        if name in BAEUME:
            soll, zusatz, rumpf = BAEUME[name]
            schreiben(d, kette, zusatz, rumpf)
        else:
            soll, dateien = GESCHACHTELT[name]
            geschachtelt_schreiben(d, kette, dateien)
        code, marken = fahren(d)
        zeichen = "  " if (code != 0) == (soll != 0) else "!!"
        if zeichen == "!!" and stand == "HEAD":
            abweichungen += 1
        print(f"{zeichen} {name:24s} code={code} (soll {soll} an HEAD)")
        for m in marken[:3]:
            print(f"        {m[:150]}")

    # Die Positivkontrolle: ohne Abschalter muss die Quelle rot BAUEN. Ohne sie belegt
    # jeder gruene Bau oben gar nichts.
    #
    # Seit Paket 0133 zaehlt sie in den Rueckgabewert, und der Grund ist der Wechsel
    # vom Aufruf von Hand zur Probe: Wer die Ausgabe selbst liest, sieht ein gruenes
    # `bau code=0` sofort; `ctest` liest nur den Rueckgabewert. Die Luecke, die dabei
    # offen blieb, ist keine gedachte -- verschwindet der Warnsatz ganz, dann fehlt er
    # in jedem der 22 Baeume gleichermassen, kein einziges Urteil kippt, und der Lauf
    # meldete `0 Abweichung(en)` ueber einen Baum, der nichts mehr prueft. Genau
    # diesen Fall faengt allein die Positivkontrolle.
    d = ablage / "p_positiv"
    r = subprocess.run(["cmake", "--build", str(d / "build")], capture_output=True, text=True)
    diag = [z for z in (r.stdout + r.stderr).splitlines() if "error:" in z]
    positiv_stumpf = r.returncode == 0
    print(f"\nPositivkontrolle p_positiv: bau code={r.returncode}, {len(diag)} Fehler"
          + ("   !! erwartet war ein roter Bau -- der Warnsatz greift nicht mehr"
             if positiv_stumpf else ""))
    for z in diag[:1]:
        print("        " + z.strip()[:150])

    print(f"\n{abweichungen} Abweichung(en) vom Soll.")
    return 1 if (abweichungen or positiv_stumpf) else 0


if __name__ == "__main__":
    raise SystemExit(main())
