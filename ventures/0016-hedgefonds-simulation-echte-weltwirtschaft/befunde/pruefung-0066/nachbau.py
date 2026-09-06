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

Seit Paket 0185 (2026-09-06) prueft er ausserdem die **Profilangabe** der Riegelzeile:
Ein einziger seiner Baeume wird zusaetzlich in beiden Profilen konfiguriert, und die
Zeile muss unter jedem den Schalter nennen, mit dem konfiguriert wurde. Warum das hier
haengt und nicht in `bauwege.py`, steht in `aufgaben/0185-...` -- kurz: dieses Skript
laeuft bei jeder Abnahme mit, jenes nur, wenn jemand es ruft.

Aufruf aus WSL heraus:

    python3 befunde/pruefung-0066/nachbau.py            # gegen HEAD
    python3 befunde/pruefung-0066/nachbau.py 8fff575^   # gegen den Stand vor 0066

    python3 befunde/pruefung-0066/nachbau.py --bruch=rohwert   # der Rotnachweis

Der Rotnachweis ist kein Handgriff daneben, sondern dieser Schalter: `--bruch=<name>`
verbiegt die geholte Fassung der Kette an genau einer Stelle und laesst alles andere
laufen wie sonst. Die drei Namen stehen in `BRUECHE`. Sie sind der Beleg, dass die neue
Bedingung misst und nicht nur laeuft -- und weil dabei die 22 Baeume gruen bleiben und
nur die neue Zeile rot wird, zeigt derselbe Lauf noch einmal die Luecke, gegen die 0185
geschrieben ist.

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

**Fuer die Profilangabe gilt die Sollspalte nicht**, und das ist Absicht: Sie ist
entweder da oder nicht, waehrend die 22 Urteile sich mit dem Baum aendern duerfen. Ein
Stand vor Paket 0137 hat sie noch nicht und macht die neue Bedingung darum ohne jeden
Bruch rot -- `python3 ... 5d5e2d6` endet seit 0185 mit 1 statt mit 0. Der Lauf druckt
dazu, dass das eine Aussage ueber jenen Stand ist und nicht ueber HEAD. Damit ist der
Baum vor 0137 der vierte Rotnachweis, und der einzige, den niemand gebaut hat.
"""

import os
import re
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


# --- Die Profilangabe der Riegelzeile (Paket 0185) ------------------------------------
#
# Die Zeile lautet
#
#   -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 22 uebersetzende ...
#
# und traegt zwei Haelften, die verschiedene Dinge fangen (begruendet in
# `werkzeugkette.cmake` ueber dem `message`): den **rohen Wert**, der sich allein gegen
# die Kommandozeile abgleichen laesst, und sein **Wahrheitswort**, das `=1` und `=ON` als
# dasselbe Profil liest. Geprueft werden sie darum einzeln -- ein Riegel, der nur die
# Zeile als ganze vergleicht, sagt einem Leser nicht, welche der beiden riss.
PROFILE = (("ON", "wahr"), ("OFF", "falsch"))
RIEGELMARKE = "Warnsatz-Schlussriegel"
WERT_MUSTER = re.compile(r"FABRIK_SANITIZER=(\S*)")
WORT_MUSTER = re.compile(r"\((wahr|falsch)\)")

# Die drei Brueche, je einer je Haelfte und einer fuer beide zusammen. Sie werden nicht
# von Hand hingeschrieben, sondern aus der geholten Fassung erzeugt: Ein handgeschriebenes
# `werkzeugkette.cmake` waere in drei Wochen ein anderes Stueck Software als das im Baum,
# und der Rotnachweis belegte dann etwas ueber eine Datei, die niemand mehr baut.
#
# Jeder Eintrag ist (Wortlaut im Baum, Ersatz). Kommt der Wortlaut nicht **genau einmal**
# vor, bricht der Lauf ab -- ein Bruch, der nichts trifft, laesst die Probe gruen und
# sieht wie ein Beweis aus.
BRUECHE = {
    # Der Schalter steht richtig da, das Wort dazu ist festgenagelt. Faengt allein die
    # zweite Haelfte, und zwar nur unter OFF.
    "wahrheitswort": ('    set(profilwort "falsch")\n',
                      '    set(profilwort "wahr")\n'),
    # Umgekehrt: das Wort folgt dem Schalter, der Wert daneben ist festgenagelt. Das ist
    # der Bruch, den kein Bericht dieser Fabrik sehen wuerde -- der Baulauf faehrt nur ON.
    "rohwert": ('"Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=${FABRIK_SANITIZER} "',
                '"Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON "'),
    # Die Angabe ganz weg -- der Stand vor Paket 0137. Beide Haelften fehlen.
    "ohne": ('"Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=${FABRIK_SANITIZER} "\n'
             '    "(${profilwort}): ${gezaehlt} uebersetzende Ziele geprueft, "',
             '"Warnsatz-Schlussriegel: ${gezaehlt} uebersetzende Ziele geprueft, "'),
}


def kette_verbiegen(roh: bytes, bruch: str) -> bytes:
    """Genau eine Stelle der geholten Kette austauschen -- fuer den Rotnachweis."""
    if bruch not in BRUECHE:
        raise SystemExit(f"Unbekannter Bruch {bruch!r}. Bekannt: {', '.join(sorted(BRUECHE))}")
    suchen, ersetzen = BRUECHE[bruch]
    txt = roh.decode()
    if txt.count(suchen) != 1:
        raise SystemExit(
            f"Bruch {bruch!r}: der erwartete Wortlaut kommt {txt.count(suchen)}-mal vor, "
            "erwartet ist genau einmal. Die Kette hat sich geaendert -- der Bruch waere "
            "keiner, und ein gruener Lauf belegte nichts.")
    return txt.replace(suchen, ersetzen).encode()


def kette_holen(stand: str, ablage: Path, bruch: str | None = None) -> Path:
    """Die zu pruefende Fassung als eigene Datei -- nie die im Baum einbinden."""
    ziel = ablage / "werkzeugkette.cmake"
    if stand == "HEAD":
        roh = KETTE.read_bytes()
    else:
        rel = KETTE.relative_to(WURZEL.parents[1])
        roh = subprocess.run(["git", "-C", str(WURZEL.parents[1]), "show", f"{stand}:{rel}"],
                             capture_output=True, check=True).stdout
    if bruch:
        roh = kette_verbiegen(roh, bruch)
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


def profilangabe_pruefen(baum: Path) -> list[str]:
    """Einen Baum in beiden Profilen konfigurieren und die zwei Haelften einzeln pruefen.

    Genommen wird **ein** Baum, nicht alle 22: Die Angabe haengt am Schalter und an
    nichts sonst, und 22 zweite Konfigurationen verdoppelten die Laufzeit ohne eine
    zweite Erkenntnis. Uebersetzt wird nichts -- die Zeile faellt beim Konfigurieren.

    Verglichen wird der Kopf der Zeile bis zum Doppelpunkt, nicht die ganze Zeile. Das
    ist hier das schaerfere Mass: In diesem winzigen Baum steht kein Sanitizerziel, die
    drei Zahlen hinter dem Doppelpunkt sind unter ON und OFF also ohnehin dieselben.
    Unterscheiden sich die beiden Zeilen, dann **nur** durch die Angabe -- und wer die
    ganze Zeile vergleicht, koennte das mit einem gewanderten Zaehlwerk verwechseln.
    """
    risse: list[str] = []
    koepfe: dict[str, str] = {}
    for wert, wort in PROFILE:
        r = subprocess.run(["cmake", "-S", str(baum), "-B", str(baum / f"profil-{wert}"),
                            f"-DFABRIK_SANITIZER={wert}"], capture_output=True, text=True)
        txt = r.stdout + r.stderr
        (baum / f"profil-{wert}.log").write_text(txt)
        zeile = next((z.strip() for z in txt.splitlines() if RIEGELMARKE in z), None)
        if zeile is None:
            risse.append(f"-DFABRIK_SANITIZER={wert}: in der Ausgabe steht ueberhaupt "
                         f"keine Zeile des Schlussriegels (cmake-Code {r.returncode}) -- "
                         "beide Haelften fehlen")
            continue
        kopf = zeile.split(":", 1)[0]
        koepfe[wert] = kopf
        print(f"   -D{wert:<3s} {zeile[:150]}")
        t = WERT_MUSTER.search(kopf)
        if t is None or t.group(1) != wert:
            risse.append(f"Haelfte 'roher Wert' unter -DFABRIK_SANITIZER={wert}: die Zeile "
                         f"nennt {'nichts' if t is None else repr(t.group(1))}, "
                         f"konfiguriert wurde {wert!r}")
        w = WORT_MUSTER.search(kopf)
        if w is None or w.group(1) != wort:
            risse.append(f"Haelfte 'Wahrheitswort' unter -DFABRIK_SANITIZER={wert}: die "
                         f"Zeile nennt {'nichts' if w is None else repr(w.group(1))}, "
                         f"erwartet ist {wort!r}")
    if len(koepfe) == 2 and koepfe["ON"] == koepfe["OFF"]:
        risse.append("Beide Haelften zusammen: ON und OFF melden zeichengleich "
                     f"{koepfe['ON']!r} -- die Angabe haengt nicht am Schalter")
    return risse


def main() -> int:
    bruch = next((a.split("=", 1)[1] for a in sys.argv[1:] if a.startswith("--bruch=")), None)
    frei = [a for a in sys.argv[1:] if not a.startswith("--bruch=")]
    stand = frei[0] if frei else "HEAD"
    # Der Vorgabepfad haengt allein am **Stand**, nicht am **Baum**. Solange dieses
    # Skript nur von Hand im Arbeitsbaum lief, war das gleichgueltig. Als Probe laeuft
    # es auch in einem Wegwerf-Baum -- und die Gegenprobe zu Paket 0133 faehrt genau
    # zwei Baeume nacheinander, den unveraenderten und den stumpf gemachten. Beide
    # haetten unter demselben Pfad geschrieben und einander ihre Bauablagen und
    # `konfig.log`s hinterlassen; was dann rot ist, gehoerte womoeglich zum anderen
    # Baum. `NACHBAU_ABLAGE` trennt sie. Der Aufruf ohne die Variable verhaelt sich
    # unveraendert -- die zwei Abnahmen, die diesen Aufruf namentlich nennen (0103,
    # 0108), sehen denselben Pfad wie zuvor.
    #
    # Ein Bruch bekommt aus demselben Grund seine eigene Ablage: Der Rotnachweis faehrt
    # unmittelbar vor oder nach einem gruenen Lauf, und beide haetten sonst unter
    # `nachbau0066-HEAD` einander die Bauablagen ueberschrieben. Ohne `--bruch` ist der
    # Pfad zeichengleich der von vorher -- die zwei Abnahmen, die ihn nennen, sehen ihn
    # unveraendert.
    marke = stand.replace("^", "v") + (f"-bruch-{bruch}" if bruch else "")
    vorgabe = Path(os.environ.get("TMPDIR", "/tmp")) / f"nachbau0066-{marke}"
    ablage = Path(os.environ.get("NACHBAU_ABLAGE") or vorgabe)
    ablage.mkdir(parents=True, exist_ok=True)
    kette = kette_holen(stand, ablage, bruch)
    print(f"Stand: {stand}   Kette: {kette}   ({kette.stat().st_size} Bytes)")
    if bruch:
        print(f"BRUCH {bruch!r} eingelegt -- dies ist ein Rotnachweis, kein Urteil "
              "ueber den Baum.")
    print()

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

    # Die Profilangabe (Paket 0185). Sie steht hinter der Positivkontrolle, damit die
    # Ausgabe bis hierher zeichengleich die von vorher ist.
    print("\nProfilangabe der Riegelzeile, ein Baum in beiden Profilen:")
    risse = profilangabe_pruefen(ablage / "p_positiv")
    for r in risse:
        print(f"     !! {r}")
    if risse and stand != "HEAD":
        # Anders als die Sollspalte oben zaehlt diese Bedingung an **jedem** Stand in den
        # Rueckgabewert, und das ist Absicht: Die Sollspalte beschreibt 22 Urteile, die
        # sich mit der Zeit aendern duerfen, und ein alter Stand faellt darum nicht
        # deswegen durch. Die Angabe dagegen ist entweder da oder nicht. Wer einen Stand
        # vor Paket 0137 faehrt, bekommt hier eine rote Zeile ueber **jenen** Stand.
        print(f"     (Der Stand {stand} liegt vor Paket 0137 oder hat die Angabe sonst "
              "nicht. Das ist eine Aussage ueber ihn, nicht ueber HEAD.)")
    if not risse:
        print("     beide Haelften nennen das konfigurierte Profil, und die beiden "
              "Angaben unterscheiden sich.")

    print(f"\n{abweichungen} Abweichung(en) vom Soll.")
    return 1 if (abweichungen or positiv_stumpf or risse) else 0


if __name__ == "__main__":
    raise SystemExit(main())
