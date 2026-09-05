#!/usr/bin/env python3
"""Der Rotnachweis am neuen Ort -- Abnahme zu Paket 0136, zweiter Teil.

Der Umzug einer Bahn ist erst dann keiner, wenn der Waechter am Ziel noch beisst. Ein
gruener Lauf allein belegt das nicht: Ein `add_test`, das am neuen Ort ins Leere zeigt,
meldet ebenfalls gruen. Deshalb dieselbe Gegenprobe wie in Paket 0133, nur an der neuen
Bahn -- ein Baum mit **einer** stumpf gemachten Zeile in `fabrik_riegel_sammeln` muss
rot werden, derselbe Lauf am unveraenderten Baum gruen bleiben.

Gemessen wird an drei Stellen, weil der Umzug drei betrifft:

    arbeitsbereich            der Weg, den der Nachtlauf faehrt -- hier haengt die
                              Probe ueber `FABRIK_MITGLIEDER`
    werkzeuge/schlussriegel   der Alleinbau des neuen Kastens
    pruefstand                der alte Ort -- dort darf die Probe **nicht** mehr sein,
                              und `--no-tests=error` macht aus "nicht da" einen roten
                              Lauf statt einer gruenen Null

Gebaut wird nichts. Die Probe ist ein Skriptaufruf und haengt an keinem Ziel; `cmake -S`
allein reicht, damit `ctest` sie kennt. Das spart je Baum einen vollen Bau und misst
genau die Frage, um die es geht.

Vor dem Aufruf muss `aufbau.py` gelaufen sein.

    python3 befunde/messung-0136/aufbau.py
    python3 befunde/messung-0136/rotnachweis.py
"""

import re
import subprocess
import sys

from aufbau import ABLAGE, ALT, NEU

# Bauweg -> (Unterverzeichnis, erwarteter ctest-Code am gruenen Baum,
#            erwarteter ctest-Code am stumpfen Baum)
#
# Der Pruefstand erwartet in **beiden** Spalten einen Fehlschlag, und das ist kein
# Schoenheitsfehler, sondern der Gegenstand des Pakets: Die Probe ist dort fort.
# `--no-tests=error` ist die Zeile, die daraus eine Aussage macht -- ohne sie gaebe
# `ctest` fuer "kein Treffer" den Code 0 zurueck (Logbuch des Testentwicklers,
# 2026-09-05, Paket 0110).
WEGE = {
    "arbeitsbereich": (".", 0, 1),
    "werkzeuge/schlussriegel": ("werkzeuge/schlussriegel", 0, 1),
    "pruefstand": ("pruefstand", 1, 1),
}

# Die Urteilszeilen von `nachbau.py`: `!!` vor einem Fall, dessen Code vom Soll abweicht.
GEKIPPT = re.compile(r"^!! +(\S+)", re.M)
GEPRUEFT = re.compile(r"^(?:!! |   )(\S+) +code=", re.M)


def lauf(befehl):
    r = subprocess.run(befehl, capture_output=True, text=True)
    return r.returncode, (r.stdout + r.stderr)


def messen(baum, name, unter):
    quelle = ABLAGE / baum / unter
    bauplatz = ABLAGE / baum / ("bau-rot-" + name.replace("/", "-"))
    k_code, k_txt = lauf(["cmake", "-S", str(quelle), "-B", str(bauplatz),
                          "-DFABRIK_SANITIZER=ON"])
    t_code, t_txt = lauf(["ctest", "--test-dir", str(bauplatz), "--output-on-failure",
                          "-R", "schlussriegel_nachbau", "--no-tests=error"])
    return {"quelle": quelle, "bauplatz": bauplatz,
            "konfig_code": k_code, "konfig": k_txt,
            "ctest_code": t_code, "ctest": t_txt}


def riegelzeile(txt):
    for zeile in txt.splitlines():
        if "Warnsatz-Schlussriegel" in zeile:
            return zeile.strip()
    return "(keine Riegelmeldung in der Ausgabe)"


def main():
    if not (ABLAGE / "gruen").exists() or not (ABLAGE / "stumpf").exists():
        raise SystemExit("Die Vergleichsbaeume fehlen unter " + str(ABLAGE)
                         + " -- erst `aufbau.py` laufen lassen.")

    print("Die eine geaenderte Zeile im Baum `stumpf`, in `fabrik_riegel_sammeln`:")
    print("    " + ALT)
    print("->  " + NEU)
    print("")

    abweichungen = 0
    for name, (unter, soll_gruen, soll_stumpf) in WEGE.items():
        for baum, soll in (("gruen", soll_gruen), ("stumpf", soll_stumpf)):
            e = messen(baum, name, unter)
            gut = (e["konfig_code"] == 0
                   and (e["ctest_code"] == 0) == (soll == 0))
            if not gut:
                abweichungen += 1
            print("=" * 78)
            print(("!! " if not gut else "   ") + "Baum " + baum
                  + ", Bauweg " + name)
            print("=" * 78)
            print("$ cmake -S " + str(e["quelle"]) + " -B " + str(e["bauplatz"])
                  + " -DFABRIK_SANITIZER=ON")
            print("   code=" + str(e["konfig_code"]) + "   " + riegelzeile(e["konfig"]))
            print("$ ctest --test-dir " + str(e["bauplatz"]) + " --output-on-failure "
                  + "-R schlussriegel_nachbau --no-tests=error")
            print("   code=" + str(e["ctest_code"]) + "   erwartet "
                  + ("0" if soll == 0 else "ungleich 0"))
            for zeile in e["ctest"].splitlines():
                if ("schlussriegel_nachbau" in zeile or "tests passed" in zeile
                        or "No tests were found" in zeile or "Errors while" in zeile):
                    print("        " + zeile.strip()[:150])
            gekippt = GEKIPPT.findall(e["ctest"])
            geprueft = GEPRUEFT.findall(e["ctest"])
            if geprueft:
                print("        " + str(len(gekippt)) + " von " + str(len(geprueft))
                      + " Faellen gekippt"
                      + (": " + ", ".join(gekippt) if gekippt else ""))
            print("")

    print(str(abweichungen) + " Abweichung(en). Ablage: " + str(ABLAGE))
    return 1 if abweichungen else 0


if __name__ == "__main__":
    sys.exit(main())
