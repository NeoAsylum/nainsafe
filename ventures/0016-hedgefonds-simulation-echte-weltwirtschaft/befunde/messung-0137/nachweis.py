#!/usr/bin/env python3
# Der Nachweis zu Paket 0137, beide Bedingungen in einem Aufruf.
#
# Aufruf:  python3 nachweis.py [<ablage>]        (Vorgabe: $TMPDIR/p0137-nachweis)
#
# Was er fuehrt:
#
#   Bedingung 1 -- Drei Bauwege mal zwei Profile, sechs leere Baubaeume je Stand. Die
#   Paare ON/OFF werden je Bauweg gegenuebergestellt; verlangt ist eine Zeile, die
#   `FABRIK_SANITIZER` samt Wert nennt und in den beiden Laeufen verschieden lautet.
#   Zweiseitig geprueft: Am Stand **vor** der Aenderung darf keine solche Zeile stehen,
#   am Stand **nach** ihr in jedem der drei Paare eine.
#
#   Bedingung 2 -- Dieselben sechs Konfigurationen an beiden Staenden mit Code 0, und je
#   (Bauweg, Profil) der Vergleich vor gegen nach. Verglichen wird gegen den **eigenen**
#   Stand desselben Profils und nicht gegen einen ausgeschriebenen Sollwert; die
#   Begruendung dafuer steht in Paket 0104 und im Kommentar ueber der Meldung. Verlangt
#   ist, dass sich genau die Zeile des Warnsatz-Schlussriegels aendert und keine andere,
#   und dass ihre drei Zahlen dieselben bleiben. Dazu Bau und `ctest` in beiden Profilen.
#
# Beide Staende sind Wegwerfbaeume: `vor` kommt aus `git archive HEAD`, `nach` ist
# dessen Kopie mit der einen Datei aus dem Arbeitsbaum darueber. Der Arbeitsbaum selbst
# wird nie gebaut -- er traegt die halbfertige Arbeit fremder Parallellaeufe, und ein
# Vorher-Nachher-Vergleich darauf misst den Fremdlauf.
import os
import re
import shutil
import subprocess
import sys

REPO = "/home/adria/fabrik"
VENTURE = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
KETTE = VENTURE + "/werkzeugkette.cmake"

BAUWEGE = [
    ("arbeitsbereich", VENTURE),
    ("kern-allein", VENTURE + "/kern"),
    ("pruefstand-allein", VENTURE + "/pruefstand"),
]
PROFILE = ["ON", "OFF"]

# Was zwischen zwei Laeufen ohnehin verschieden ist und nichts ueber die Aenderung sagt:
# der Pfad des Baubaums und die gemessene Dauer. Beides wird vor jedem Vergleich
# eingeebnet, sonst ertraenkt es den Unterschied, um den es geht.
def einebnen(text):
    text = re.sub(r"\(\d+\.\d+s\)", "(Zs)", text)
    text = re.sub(r"Build files have been written to: .*", "Build files ...", text)
    return text


def zeilen(pfad):
    return einebnen(open(pfad).read()).splitlines()


def konfigurieren(wurzel, ziel):
    os.makedirs(ziel, exist_ok=True)
    codes = {}
    for bauweg, unterpfad in BAUWEGE:
        for profil in PROFILE:
            baum = os.path.join(ziel, "bau", bauweg + "-" + profil)
            if os.path.exists(baum):
                shutil.rmtree(baum)
            os.makedirs(baum)
            lauf = subprocess.run(
                ["cmake", "-S", os.path.join(wurzel, unterpfad), "-B", baum,
                 "-DFABRIK_SANITIZER=" + profil],
                capture_output=True, text=True)
            with open(os.path.join(ziel, bauweg + "-" + profil + ".txt"), "w") as f:
                f.write(lauf.stdout + lauf.stderr)
            codes[(bauweg, profil)] = lauf.returncode
    return codes


def schalterzeilen(zeilenliste):
    return [z for z in zeilenliste if "FABRIK_SANITIZER=" in z]


def main():
    ablage = os.path.abspath(sys.argv[1]) if len(sys.argv) > 1 else os.path.join(
        os.environ.get("TMPDIR", "/tmp"), "p0137-nachweis")
    if os.path.exists(ablage):
        shutil.rmtree(ablage)
    os.makedirs(ablage)

    stand = subprocess.run(["git", "-C", REPO, "rev-parse", "HEAD"],
                           capture_output=True, text=True).stdout.strip()
    print("Bezugsstand (vor): " + stand)

    vor = os.path.join(ablage, "vor")
    os.makedirs(vor)
    p1 = subprocess.Popen(["git", "-C", REPO, "archive", stand, VENTURE, "specs"],
                          stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["tar", "-x", "-C", vor], stdin=p1.stdout)
    p1.stdout.close()
    p2.wait()
    p1.wait()

    nach = os.path.join(ablage, "nach")
    shutil.copytree(vor, nach)
    shutil.copy2(os.path.join(REPO, KETTE), os.path.join(nach, KETTE))
    unterschied = subprocess.run(["diff", "-rq", vor, nach],
                                 capture_output=True, text=True).stdout.strip()
    print("vor gegen nach, Dateiliste (soll: genau werkzeugkette.cmake):")
    print("  " + (unterschied or "(kein Unterschied -- Fehler)"))

    schlecht = 0
    codes = {}
    for name, wurzel in (("vor", vor), ("nach", nach)):
        codes[name] = konfigurieren(wurzel, os.path.join(ablage, "aus-" + name))
    print("")
    print("Rueckgabecodes der zwoelf Konfigurationen:")
    for name in ("vor", "nach"):
        for schluessel, code in sorted(codes[name].items()):
            print("  %-4s %-18s %-3s Code %d" % (name, schluessel[0], schluessel[1], code))
            if code != 0:
                schlecht += 1

    # ---- Bedingung 1: das Profil steht in der Ausgabe, und zwar zweiseitig -----------
    print("")
    print("BEDINGUNG 1 -- Paarvergleich ON gegen OFF je Bauweg")
    for name in ("vor", "nach"):
        for bauweg, _ in BAUWEGE:
            d = os.path.join(ablage, "aus-" + name)
            a = zeilen(os.path.join(d, bauweg + "-ON.txt"))
            b = zeilen(os.path.join(d, bauweg + "-OFF.txt"))
            sa, sb = schalterzeilen(a), schalterzeilen(b)
            traegt = bool(sa) and bool(sb) and sa != sb
            soll = (name == "nach")
            urteil = "ok" if traegt == soll else "FEHLER"
            print("  %-4s %-18s Zeile mit Schalter und Wert: %-5s (erwartet %-5s) %s"
                  % (name, bauweg, str(traegt), str(soll), urteil))
            if traegt != soll:
                schlecht += 1
            for z in sa:
                print("      ON : " + z.strip())
            for z in sb:
                print("      OFF: " + z.strip())

    # ---- Bedingung 2: kein Urteil aendert sich ---------------------------------------
    print("")
    print("BEDINGUNG 2 -- vor gegen nach, je Bauweg und Profil (Pfad und Dauer eingeebnet)")
    for bauweg, _ in BAUWEGE:
        for profil in PROFILE:
            a = zeilen(os.path.join(ablage, "aus-vor", bauweg + "-" + profil + ".txt"))
            b = zeilen(os.path.join(ablage, "aus-nach", bauweg + "-" + profil + ".txt"))
            nur_a = [z for z in a if z not in b]
            nur_b = [z for z in b if z not in a]
            ok = (len(nur_a) == 1 and len(nur_b) == 1
                  and "Warnsatz-Schlussriegel" in nur_a[0]
                  and "Warnsatz-Schlussriegel" in nur_b[0])
            print("  %-18s %-3s geaenderte Zeilen: %d/%d %s"
                  % (bauweg, profil, len(nur_a), len(nur_b), "ok" if ok else "FEHLER"))
            if not ok:
                schlecht += 1
            for z in nur_a:
                print("      vor : " + z.strip())
            for z in nur_b:
                print("      nach: " + z.strip())
            zahlen_a = re.findall(r"\d+", " ".join(nur_a))
            zahlen_b = re.findall(r"\d+", " ".join(nur_b))
            gleich = zahlen_a == zahlen_b
            print("      Zahlen vor %s gegen nach %s -- %s"
                  % (zahlen_a, zahlen_b, "gleich" if gleich else "VERSCHOBEN"))
            if not gleich:
                schlecht += 1

    # ---- Bedingung 2, zweite Haelfte: Bau und ctest in beiden Profilen ---------------
    print("")
    print("BEDINGUNG 2 -- Bau und ctest im Arbeitsbereich, beide Profile")
    for profil in PROFILE:
        baum = os.path.join(ablage, "aus-nach", "bau", "arbeitsbereich-" + profil)
        bau = subprocess.run(["cmake", "--build", baum, "-j", "4"],
                             capture_output=True, text=True)
        with open(os.path.join(ablage, "bau-" + profil + ".txt"), "w") as f:
            f.write(bau.stdout + bau.stderr)
        pruef = subprocess.run(["ctest", "--test-dir", baum, "--output-on-failure"],
                               capture_output=True, text=True)
        with open(os.path.join(ablage, "ctest-" + profil + ".txt"), "w") as f:
            f.write(pruef.stdout + pruef.stderr)
        letzte = [z for z in pruef.stdout.splitlines() if "tests passed" in z
                  or "tests failed" in z]
        print("  Profil %-3s  cmake --build Code %d   ctest Code %d   %s"
              % (profil, bau.returncode, pruef.returncode,
                 letzte[0].strip() if letzte else "(keine Zusammenfassung)"))
        if bau.returncode != 0 or pruef.returncode != 0:
            schlecht += 1

    print("")
    print("Abweichungen: %d" % schlecht)
    return 1 if schlecht else 0


if __name__ == "__main__":
    sys.exit(main())
