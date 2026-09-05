#!/usr/bin/env python3
"""Nachweis zu Paket 0146 -- Aktionstyp und kanonische Ordnung.

Faehrt alle Baeume in einem Aufruf und schreibt seinen Bericht selbst. Er endet mit
"Abweichungen: 0", wenn jeder Baum das getan hat, was von ihm erwartet wird.

Fuenf Baeume, und die ersten beiden sind die Zahlen der Abnahme:

  vorher      der heutige Stand **ohne** die drei Dateien dieses Pakets. Nur
              konfiguriert, nicht gebaut -- gebraucht werden die Zahlen des
              Sperrebindungsriegels und die Zahl der ctest-Eintraege.
  nachher     derselbe Stand mit den drei Dateien. Konfiguriert, gebaut, gelaufen,
              in beiden Profilen.
  m1          Mutant: `ordnungsvergleich` laeuft die Raenge rueckwaerts -- also die
              Ordnung "Stufe zuerst". Muss rot werden, und zwar schon beim
              Uebersetzen, an den Zusicherungen im Kopf.
  m2          Mutant: die Einfuegeschleife in `ordne` tauscht nie. Uebersetzt gruen,
              muss an der Probe rot werden.
  m3          Mutant: `ordne` sortiert absteigend. Dasselbe.

Der Baum "nachher" ist zugleich die Kontrolle: Ein Mutantenlauf, in dem der
unveraenderte Baum nicht gruen bleibt, misst die Werkzeugkette und nicht die Mutation.
"""

import os
import pathlib
import shutil
import subprocess
import sys

HIER = pathlib.Path(__file__).resolve().parent
VENTURE = HIER.parent.parent
NEUE_DATEIEN = [
    "include/kern/aktion.hpp",
    "src/aktion.cpp",
    "test/aktion_probe.cpp",
]

# Jede Mutation ist ein Paar (suchen, ersetzen) auf einer Datei des Kerns. Die
# Suchtexte stehen genau einmal in ihrer Datei; das prueft `mutiere`.
MUTATIONEN = {
    "m1": ("include/kern/aktion.hpp",
           "schluessel_des_ranges(rang);",
           "schluessel_des_ranges(SCHLUESSEL - 1 - rang);"),
    "m2": ("include/kern/aktion.hpp",
           "ordnungsvergleich(liste[platz - 1], eintrag) > 0",
           "ordnungsvergleich(liste[platz - 1], eintrag) > 1"),
    "m3": ("include/kern/aktion.hpp",
           "ordnungsvergleich(liste[platz - 1], eintrag) > 0",
           "ordnungsvergleich(liste[platz - 1], eintrag) < 0"),
}

sammlung = []
abweichungen = 0


def melde(zeile):
    print(zeile)
    sammlung.append(zeile)


def baum_anlegen(arbeit, name):
    """Legt eine Abschrift des Kerns samt Werkzeugkette an -- ohne den Bauordner.

    Ein mitkopierter Bauordner traegt absolute Pfade und macht den neuen Baum zu einer
    Fassade vor dem alten.
    """
    ziel = arbeit / name
    if ziel.exists():
        shutil.rmtree(ziel)
    ziel.mkdir(parents=True)
    shutil.copytree(VENTURE / "kern", ziel / "kern",
                    ignore=shutil.ignore_patterns("bau"))
    shutil.copyfile(VENTURE / "werkzeugkette.cmake", ziel / "werkzeugkette.cmake")
    return ziel


def mutiere(baum, kennung):
    datei, suchen, ersetzen = MUTATIONEN[kennung]
    pfad = baum / "kern" / datei
    text = pfad.read_text()
    if text.count(suchen) != 1:
        raise SystemExit("Mutation " + kennung + ": Suchtext steht "
                         + str(text.count(suchen)) + "-mal in " + datei)
    pfad.write_text(text.replace(suchen, ersetzen))


def konfigurieren(baum, bau, profil):
    return subprocess.run(
        ["cmake", "-S", str(baum / "kern"), "-B", str(bau),
         "-DFABRIK_SANITIZER=" + profil],
        capture_output=True, text=True)


def riegelzahlen(text):
    for zeile in text.splitlines():
        if "Sperrebindungsriegel" in zeile and "geprueft" in zeile:
            return zeile.strip().lstrip("- ").strip()
    return "(keine Meldung des Sperrebindungsriegels)"


def ctest_anzahl(bau):
    r = subprocess.run(["ctest", "-N"], cwd=str(bau), capture_output=True, text=True)
    for zeile in r.stdout.splitlines():
        if "Total Tests" in zeile:
            return int(zeile.split(":")[1].strip())
    return -1


def erwarte(bedingung, text):
    global abweichungen
    if bedingung:
        melde("    ok    " + text)
    else:
        abweichungen += 1
        melde("    ABWEICHUNG  " + text)


def lauf(baum, kennung, profil, erwartet_uebersetzt, erwartet_gruen, arbeit):
    """Konfiguriert, baut und laeuft einen Baum in einem Profil."""
    bau = arbeit / ("bau-" + kennung + "-" + profil)
    konf = konfigurieren(baum, bau, profil)
    melde("  " + kennung + " / Profil " + profil + " -- Konfiguration Code "
          + str(konf.returncode))
    melde("    " + riegelzahlen(konf.stdout + konf.stderr))
    if konf.returncode != 0:
        erwarte(not erwartet_uebersetzt, "Konfiguration bricht ab")
        return None

    anzahl = ctest_anzahl(bau)
    melde("    ctest-Eintraege: " + str(anzahl))

    gebaut = subprocess.run(["cmake", "--build", str(bau), "-j", "4"],
                            capture_output=True, text=True)
    melde("    Uebersetzung Code " + str(gebaut.returncode))
    erwarte((gebaut.returncode == 0) == erwartet_uebersetzt,
            "uebersetzt " + ("gruen" if erwartet_uebersetzt else "rot"))
    if gebaut.returncode != 0:
        for zeile in (gebaut.stdout + gebaut.stderr).splitlines():
            if "static_assert" in zeile or "error:" in zeile:
                melde("      " + zeile.strip()[:160])
        return anzahl

    gelaufen = subprocess.run(["ctest", "--output-on-failure"], cwd=str(bau),
                              capture_output=True, text=True)
    melde("    ctest Code " + str(gelaufen.returncode))
    erwarte((gelaufen.returncode == 0) == erwartet_gruen,
            "ctest " + ("gruen" if erwartet_gruen else "rot"))
    if not erwartet_gruen:
        for zeile in gelaufen.stdout.splitlines():
            if "FEHLGESCHLAGEN" in zeile or "Failed" in zeile:
                melde("      " + zeile.strip()[:160])
    return anzahl


def haupt():
    arbeit = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "nachweis-0146"
    arbeit.mkdir(parents=True, exist_ok=True)

    melde("# Nachweis 0146 -- Aktionstyp und kanonische Ordnung")
    melde("")

    # --- der Vorher-Stand: derselbe Baum ohne die drei neuen Dateien ---------
    melde("## Bezugsstand -- derselbe Baum ohne die drei Dateien dieses Pakets")
    vorher = baum_anlegen(arbeit, "vorher")
    for datei in NEUE_DATEIEN:
        (vorher / "kern" / datei).unlink()
    vorher_zahlen = {}
    for profil in ("ON", "OFF"):
        bau = arbeit / ("bau-vorher-" + profil)
        konf = konfigurieren(vorher, bau, profil)
        melde("  vorher / Profil " + profil + " -- Konfiguration Code "
              + str(konf.returncode))
        melde("    " + riegelzahlen(konf.stdout + konf.stderr))
        anzahl = ctest_anzahl(bau)
        melde("    ctest-Eintraege: " + str(anzahl))
        vorher_zahlen[profil] = anzahl
        erwarte(konf.returncode == 0, "der Bezugsstand konfiguriert durch")
    melde("")

    # --- der heutige Stand ---------------------------------------------------
    melde("## Der Stand mit den drei Dateien -- beide Profile")
    nachher = baum_anlegen(arbeit, "nachher")
    for profil in ("ON", "OFF"):
        anzahl = lauf(nachher, "nachher", profil, True, True, arbeit)
        erwarte(anzahl == vorher_zahlen[profil] + 1,
                "ein ctest-Eintrag mehr als im Bezugsstand ("
                + str(vorher_zahlen[profil]) + " -> " + str(anzahl) + ")")
    melde("")

    # --- die drei Mutanten ---------------------------------------------------
    melde("## Die Mutanten -- jeder muss rot werden, im Profil OFF")
    for kennung, erwartet_uebersetzt in (("m1", False), ("m2", True), ("m3", True)):
        baum = baum_anlegen(arbeit, kennung)
        mutiere(baum, kennung)
        lauf(baum, kennung, "OFF", erwartet_uebersetzt, False, arbeit)
    melde("")

    melde("Abweichungen: " + str(abweichungen))
    (HIER / "bericht.md").write_text("\n".join(sammlung) + "\n")
    return 0 if abweichungen == 0 else 1


if __name__ == "__main__":
    sys.exit(haupt())
