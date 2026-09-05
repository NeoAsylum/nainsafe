#!/usr/bin/env python3
# Nachweis zu Paket 0134 -- der Sperrebindungsriegel in kern/CMakeLists.txt.
#
# Sechs Baeume, jeder einzeln gefahren, jeder mit Marke und Exitcode:
#
#   1  unveraendert, MIT Riegel, kern allein + Arbeitsbereich, beide Profile -> gruen
#   2  src/luecke.cpp ohne jede Bindung, OHNE Riegel  -> gruen (die Luecke, gemessen)
#   3  src/luecke.cpp ohne jede Bindung, MIT  Riegel  -> Abbruch beim Konfigurieren
#   4  src/luecke.cpp Bindung nicht zuletzt, OHNE Riegel -> gruen
#   5  src/luecke.cpp Bindung nicht zuletzt, MIT  Riegel -> Abbruch beim Konfigurieren
#
# Baum 1 ist nicht wegzulassen: Ein Riegel, der alles verbietet, besteht 3 und 5 und
# faellt nur an ihm auf. Die Baeume OHNE Riegel sind ebensowenig wegzulassen -- sonst
# wirkte die Aenderung womoeglich dadurch, dass sie alles faengt.
#
# Die Fassung VOR der Aenderung liegt als CMakeLists-vorher.txt daneben, damit der
# Nachweis ohne Git-Stand wiederholbar ist: Ein Fremdlauf verschiebt HEAD, die Kopie
# nicht.
#
# Aufruf:  python3 befunde/messung-0134/bindungsriegel.py
# Exitcode 0, wenn alle sechs Baeume ihre Erwartung erfuellen.
import os
import pathlib
import shutil
import subprocess
import sys

HIER = pathlib.Path(__file__).resolve().parent
VENTURE = HIER.parents[1]
NACHHER = VENTURE / "kern" / "CMakeLists.txt"
VORHER = HIER / "CMakeLists-vorher.txt"
TMP = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0134"

# Die Wegwerfquelle des Verstosses 1: Sie bindet kern/sperre.hpp gar nicht und enthaelt
# beides, was der Kern verbietet -- eine Rechnung auf double (T4) und eine eigene
# Fassung der Strichrechnung (T7, Massnahme 4.2). Ohne Riegel uebersetzt sie gruen.
LUECKE_OHNE = """// Wegwerfquelle des Nachweises zu Paket 0134 -- gehoert nicht ins Repo.
#include <cstdint>

namespace {
double luecke_gleitkomma(double a, double b) { return a * b; }

std::int64_t luecke_plus(std::int64_t a, std::int64_t b) {
  std::int64_t r = 0;
  if (__builtin_add_overflow(a, b, &r)) { return 0; }
  return r;
}
}  // namespace

std::int64_t luecke_zeigt(std::int64_t a, std::int64_t b);
std::int64_t luecke_zeigt(std::int64_t a, std::int64_t b) {
  return luecke_plus(a, b)
       + static_cast<std::int64_t>(luecke_gleitkomma(2.0, 3.0));
}
"""

# Die Wegwerfquelle des Verstosses 2: Sie bindet den Kopf, aber nicht als letzten
# #include. Der nachgestellte Kopf ist ein bereits gebundener -- seine Einbindesperre
# macht die zweite Zeile folgenlos, also uebersetzt die Quelle ohne Riegel gruen.
# Genau das ist der schaerfste Zuschnitt fuer diesen Fall: Der Verstoss ist fuer den
# Uebersetzer unsichtbar, und nichts ausser dem Riegel faengt ihn.
#
# Gemessen am 2026-09-05, warum es nicht irgendein Kopf sein darf: Mit <cstddef> an
# dieser Stelle bricht schon der Bau ab (max_align_t nennt `long double`, und `double`
# ist vergiftet). Der Baum ohne Riegel waere dann rot, und der Nachweis zeigte nur
# noch, dass die Vergiftung wirkt -- nicht, dass der Riegel etwas faengt.
LUECKE_MITTE = """// Wegwerfquelle des Nachweises zu Paket 0134 -- gehoert nicht ins Repo.
#include <cstdint>

#include "kern/sperre.hpp"  // steht absichtlich NICHT an letzter Stelle

#include <cstdint>  // Wiedereinbindung, folgenlos -- und trotzdem der letzte #include

std::int64_t luecke_mitte(std::int64_t a);
std::int64_t luecke_mitte(std::int64_t a) {
  return a + static_cast<std::int64_t>(sizeof(std::size_t));
}
"""


def lauf(argv):
    e = subprocess.run(argv, capture_output=True, text=True)
    return e.returncode, e.stdout + e.stderr


def marken(text):
    return [z.strip() for z in text.splitlines() if "Sperrebindungsriegel" in z]


def baum_anlegen(name, cmakelists, zusatz):
    """Kopiert kern/ und werkzeugkette.cmake nach TMPDIR und legt die Wegwerfquelle."""
    wurzel = TMP / name
    shutil.rmtree(wurzel, ignore_errors=True)
    wurzel.mkdir(parents=True)
    shutil.copytree(VENTURE / "kern", wurzel / "kern",
                    ignore=shutil.ignore_patterns("bau", "build"))
    shutil.copyfile(VENTURE / "werkzeugkette.cmake", wurzel / "werkzeugkette.cmake")
    shutil.copyfile(cmakelists, wurzel / "kern" / "CMakeLists.txt")
    if zusatz is not None:
        (wurzel / "kern" / "src" / "luecke.cpp").write_text(zusatz)
    return wurzel / "kern"


def fahren(quelle, bau, profil):
    """cmake -S, --build, ctest -- bricht ab, sobald ein Schritt rot ist."""
    shutil.rmtree(bau, ignore_errors=True)
    schritte = []
    code, aus = lauf(["cmake", "-S", str(quelle), "-B", str(bau),
                      "-DFABRIK_SANITIZER=" + profil])
    schritte.append(("cmake -S", code, marken(aus), aus))
    if code == 0:
        code, aus = lauf(["cmake", "--build", str(bau), "-j", "4"])
        schritte.append(("cmake --build", code, [], aus))
    if code == 0:
        code, aus = lauf(["ctest", "--test-dir", str(bau), "--output-on-failure"])
        treffer = [z.strip() for z in aus.splitlines()
                   if "tests passed" in z or "No tests" in z]
        schritte.append(("ctest", code, treffer, aus))
    return schritte


def melden(titel, erwartung, schritte):
    """Druckt jeden Schritt mit Marke und Code. erwartung: "gruen" oder "abbruch"."""
    print("=" * 78)
    print(titel)
    print("   erwartet: " + erwartung)
    for schritt, code, treffer, aus in schritte:
        print("   {0:14s} Code {1}".format(schritt, code))
        for z in treffer:
            print("      | " + z)
        if code != 0:
            for z in aus.strip().splitlines()[-14:]:
                print("      > " + z)
    codes = [c for _, c, _, _ in schritte]
    if erwartung == "gruen":
        gut = all(c == 0 for c in codes) and len(schritte) == 3
    elif erwartung == "ein schritt gruen":
        gut = len(schritte) == 1 and codes[0] == 0
    else:
        gut = len(schritte) == 1 and codes[0] != 0
    print("   ERGEBNIS: " + ("wie erwartet" if gut else "ABWEICHUNG"))
    return 0 if gut else 1


def main():
    TMP.mkdir(parents=True, exist_ok=True)
    abweichungen = 0
    for profil in ("ON", "OFF"):
        for name, quelle in (("kern allein", VENTURE / "kern"),
                             ("Arbeitsbereich", VENTURE)):
            abweichungen += melden(
                "1  unveraendert, MIT Riegel -- {0}, FABRIK_SANITIZER={1}".format(
                    name, profil),
                "gruen", fahren(quelle, TMP / "bau-rein", profil))

    faelle = (
        ("2", "luecke.cpp ohne jede Bindung, OHNE Riegel", VORHER, LUECKE_OHNE, "gruen"),
        ("3", "luecke.cpp ohne jede Bindung, MIT Riegel", NACHHER, LUECKE_OHNE, "abbruch"),
        ("4", "luecke.cpp Bindung nicht zuletzt, OHNE Riegel", VORHER, LUECKE_MITTE, "gruen"),
        ("5", "luecke.cpp Bindung nicht zuletzt, MIT Riegel", NACHHER, LUECKE_MITTE, "abbruch"),
    )
    for nummer, titel, liste, quelltext, erwartung in faelle:
        wurzel = baum_anlegen("baum" + nummer, liste, quelltext)
        abweichungen += melden(
            "{0}  {1} -- kern allein, FABRIK_SANITIZER=ON".format(nummer, titel),
            erwartung, fahren(wurzel, TMP / ("bau" + nummer), "ON"))

    abweichungen += nachziehen(
        "6", "Include-Zeile aus vorhandener Quelle entfernt, OHNE Riegel",
        VORHER, "ein schritt gruen")
    abweichungen += nachziehen(
        "7", "Include-Zeile aus vorhandener Quelle entfernt, MIT Riegel",
        NACHHER, "abbruch")

    print("=" * 78)
    print("Abweichungen: {0}".format(abweichungen))
    return 1 if abweichungen else 0




def nachziehen(nummer, name, cmakelists, erwartung):
    """Der Fall, den CONFIGURE_DEPENDS am Sammler nicht sieht.

    Ein Baum wird gruen gebaut, dann faellt die Include-Zeile aus einer **vorhandenen**
    Quelle weg -- die Dateiliste aendert sich dabei nicht. Danach nur `cmake --build`,
    ohne neues `cmake -S`. Mit CMAKE_CONFIGURE_DEPENDS zieht CMake den
    Konfigurationslauf selbst nach und bricht ab; ohne ihn baut es still weiter.
    """
    quelle = baum_anlegen("baum" + nummer, cmakelists, None)
    bau = TMP / ("bau" + nummer)
    schritte = fahren(quelle, bau, "ON")
    fehler = melden("{0}a {1} -- Vorbau, FABRIK_SANITIZER=ON".format(nummer, name),
                    "gruen", schritte)
    if fehler:
        return fehler + 1
    ziel = quelle / "src" / "werte.cpp"
    text = ziel.read_text()
    treffer = [z for z in text.splitlines() if "kern/sperre.hpp" in z]
    assert len(treffer) == 1, treffer
    ziel.write_text(text.replace(treffer[0] + chr(10), ""))
    code, aus = lauf(["cmake", "--build", str(bau), "-j", "4"])
    return fehler + melden(
        "{0}b {1} -- nur `cmake --build` nach dem Eingriff".format(nummer, name),
        erwartung, [("cmake --build", code, marken(aus), aus)])


if __name__ == "__main__":
    sys.exit(main())
