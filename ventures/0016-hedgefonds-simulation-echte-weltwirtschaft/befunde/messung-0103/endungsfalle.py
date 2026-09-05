#!/usr/bin/env python3
"""Abnahmebedingung 1 und 2 von Paket 0103 -- zum Nachfahren.

Vier Wegwerf-Baeume unter `$TMPDIR`, je gegen eine **waehlbare** Fassung von
`werkzeugkette.cmake`. Sie unterscheiden sich von denen in
`befunde/pruefung-0066/nachbau.py` durch genau eine Sache: Der Nichtwert steckt als
**Endung** in einer gesetzten Eigenschaft, statt ihr ganzer Wert zu sein.

Aufruf aus WSL heraus:

    python3 befunde/messung-0103/endungsfalle.py            # gegen den Arbeitsbaum
    python3 befunde/messung-0103/endungsfalle.py <ref>      # gegen einen Git-Stand

Der Stand **vor** diesem Paket ist der letzte Commit, in dem
`fabrik_nichtwert_leeren` noch nicht vorkommt:

    git log -S fabrik_nichtwert_leeren -- <pfad>/werkzeugkette.cmake

Die Sollspalte steht je Lage getrennt, weil zwei der vier Baeume ihr Urteil
aendern **sollen** -- das ist der Gegenstand des Pakets. `b1k` und `b2b` aendern es
nicht: Sie sind die Kontrollen dagegen, dass die Aenderung dadurch wirkt, dass sie
alles faengt oder die Endung ganz uebergeht.

Gemessen am 2026-09-05 mit CMake 4.2.3:

    Baum                          vorher   nachher
    b1_getarnt_quellflags         0        1        <- Bedingung 1, der stille Fall
    b1k_kontrolle_ohne_endung     1        1        <- war rot, bleibt rot
    b2_fehlalarm_ziel             1        0        <- Bedingung 2, der laute Fall
    b2b_endung_entschaerft_nicht  1        1        <- rot, aber aus anderem Grund

`b2b` ist der Fall, den eine schlampige Behebung verliert: vorher rot mit
`es fehlen: -Wall ...` (Fehlalarm), nachher rot mit
`gefunden in: COMPILE_OPTIONS an z` (der wirkliche Befund). Der Konfigurationscode
allein unterscheidet die beiden nicht -- deshalb druckt dieses Skript die Marken.
"""

import os
import subprocess
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parents[2]
PRUEFUNG0066 = WURZEL / "befunde" / "pruefung-0066"
sys.path.insert(0, str(PRUEFUNG0066))
import nachbau  # noqa: E402  -- Geruest und Fahrmechanik, nicht zweimal schreiben

SATZ = nachbau.SATZ

# name -> (soll vorher, soll nachher, rumpf)
BAEUME = {
    # Bedingung 1: getarnter Schalter in einer ZEICHENKETTEN-Eigenschaft.
    # `COMPILE_FLAGS` ist keine CMake-Liste, ihr ganzer Wert ist der eine Eintrag --
    # und er endet auf `-NOTFOUND`. Deshalb traegt "je Listeneintrag entscheiden"
    # hier nicht (siehe die Berichtigung im Paket).
    "b1_getarnt_quellflags": (
        0, 1,
        SATZ + 'set_source_files_properties(z.cpp PROPERTIES'
               ' COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")'),
    # dieselbe Zeile ohne die Endung -- war vorher rot und muss rot bleiben
    "b1k_kontrolle_ohne_endung": (
        1, 1,
        SATZ + 'set_source_files_properties(z.cpp PROPERTIES'
               ' COMPILE_FLAGS "-w -DPFAD=x")'),
    # Bedingung 2, erster Baum: der Fehlalarm am Ziel muss verschwinden
    "b2_fehlalarm_ziel": (
        1, 0,
        SATZ + "target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)"),
    # Bedingung 2, zweiter Baum: die Endung darf den Schalter nicht entschaerfen
    "b2b_endung_entschaerft_nicht": (
        1, 1,
        SATZ + "target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)"),
}

MARKEN = ("gefunden in", "hebt den Satz wieder auf", "es fehlen:",
          "alle mit Warnsatz und ohne Pauschalabschalter")


def marken_lesen(d):
    raus = []
    for z in (d / "konfig.log").read_text().splitlines():
        z = z.strip()
        if any(m in z for m in MARKEN) and "Zeile" not in z:
            raus.append(z)
    return raus


def bauen(d):
    r = subprocess.run(["cmake", "--build", str(d / "build")],
                       capture_output=True, text=True)
    txt = r.stdout + r.stderr
    return r.returncode, [z.strip() for z in txt.splitlines()
                          if "error:" in z or "warning:" in z]


def main():
    stand = sys.argv[1] if len(sys.argv) > 1 else "HEAD"
    ablage = Path(os.environ.get("TMPDIR", "/tmp")) / (
        "messung0103-" + stand.replace("^", "v").replace("/", "_"))
    ablage.mkdir(parents=True, exist_ok=True)

    # `kette_holen("HEAD", ...)` kopiert den ARBEITSBAUM, nicht den Commit -- so ist es
    # in nachbau.py gebaut, und so ist es hier gewollt: gemessen wird, was dasteht.
    kette = nachbau.kette_holen(stand, ablage)
    lage = "nachher" if stand == "HEAD" else "vorher"
    print("Stand: " + stand + "  (Sollspalte '" + lage + "')")
    print("Kette: " + str(kette) + "  (" + str(kette.stat().st_size) + " Bytes)")
    print()

    abweichungen = 0
    for name in sorted(BAEUME):
        soll_v, soll_n, rumpf = BAEUME[name]
        soll = soll_v if lage == "vorher" else soll_n
        d = ablage / name
        nachbau.schreiben(d, kette, {}, rumpf)
        code, _ = nachbau.fahren(d)
        ok = (code != 0) == (soll != 0)
        if not ok:
            abweichungen += 1
        print(("  " if ok else "!!") + " " + name.ljust(30)
              + " code=" + str(code) + " (soll " + str(soll) + " " + lage + ")")
        for m in marken_lesen(d):
            print("        " + m[:170])

    # Der stille Schaden: baut der getarnte Baum wirklich ohne eine einzige Diagnose
    # durch? Am Stand davor ist die Antwort 0 Diagnosen -- das ist der ganze Grund
    # fuer dieses Paket. Danach konfiguriert er gar nicht mehr, also gibt es nichts
    # zu bauen.
    d = ablage / "b1_getarnt_quellflags"
    code, diag = bauen(d)
    print()
    print("b1_getarnt_quellflags bauen: code=" + str(code) + ", "
          + str(len(diag)) + " Diagnose(n)")
    print("   vorher erwartet: code 0 und 0 Diagnosen -- `-w` wirkte still.")
    print("   nachher erwartet: Bau schlaegt fehl, weil schon die Konfiguration abbrach.")

    # Positivkontrolle: dieselbe Quelle ohne jeden Abschalter muss rot BAUEN.
    # Ohne sie belegt kein gruener Bau oben irgendetwas.
    d = ablage / "p_positiv"
    nachbau.schreiben(d, kette, {}, SATZ)
    kcode, _ = nachbau.fahren(d)
    bcode, diag = bauen(d)
    print()
    print("Positivkontrolle p_positiv: konfig=" + str(kcode) + ", bau=" + str(bcode)
          + ", " + str(len(diag)) + " Diagnose(n)")
    for z in diag[:1]:
        print("        " + z[:170])
    if bcode == 0:
        print("!! Die Positivkontrolle baut gruen -- jede gruene Messung oben ist wertlos.")
        abweichungen += 1

    print()
    print(str(abweichungen) + " Abweichung(en) vom Soll (" + lage + ").")
    return 1 if abweichungen else 0


if __name__ == "__main__":
    raise SystemExit(main())
