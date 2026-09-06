"""Wie klein darf eine Kopie sein, ueber die der Riegel dasselbe meldet?

Zwei Verkuerzungen sind moeglich, ohne dass sich seine Ausgabe aendert, und beide
folgen aus seinem eigenen Quelltext:

  1. Von `bau` und `befunde` liest er keinen Inhalt -- er sammelt von dort nur
     Pfade in die Menge der ungelesenen Orte. Dort genuegen leere Dateien.
  2. `ist_zieldatei` laesst nur `CMakeLists.txt` und die Endungen aus `ENDUNGEN`
     durch. Was daran scheitert, sieht er ueberhaupt nicht -- weder mit Inhalt
     noch mit Namen.

Diese Erkundung zaehlt, was danach uebrig bleibt. Der erste Anlauf am 2026-09-06
kopierte alle 126.339 Namen und liess den tmpfs volllaufen; auf tmpfs kostet auch
eine leere Datei eine Seite.
"""
import os

WURZEL = "/home/adria/fabrik"
STAEMME = ("ventures/0016-hedgefonds-simulation-echte-weltwirtschaft",
           "specs/0016-hedgefonds-simulation-echte-weltwirtschaft")
NUR_NAMEN = ("bau", "befunde")
ENDUNGEN = (".md", ".toml", ".cpp", ".hpp", ".txt", ".cmake", ".py", ".rs")


def sieht_der_riegel(name):
    if name == "CMakeLists.txt":
        return True
    punkt = name.rfind(".")
    return punkt != -1 and name[punkt:] in ENDUNGEN


for stamm in STAEMME:
    voll = [0, 0]
    leer = [0, 0]
    uebergangen = 0
    for ordner, unter, dateien in os.walk(os.path.join(WURZEL, stamm)):
        unter[:] = [u for u in unter if not u.startswith(".")]
        rel = os.path.relpath(ordner, os.path.join(WURZEL, stamm))
        hohl = rel.split(os.sep)[0] in NUR_NAMEN
        for d in dateien:
            if not sieht_der_riegel(d):
                uebergangen += 1
                continue
            ziel = leer if hohl else voll
            ziel[0] += 1
            try:
                ziel[1] += os.path.getsize(os.path.join(ordner, d))
            except OSError:
                pass
    print("%s:" % stamm)
    print("  abgeschrieben:      %6d Dateien, %8.1f MB" % (voll[0], voll[1] / 1e6))
    print("  nur als leerer Name:%6d Dateien, %8.1f MB im Original"
          % (leer[0], leer[1] / 1e6))
    print("  gar nicht angelegt: %6d Dateien (Endung, die der Riegel nicht kennt)"
          % uebergangen)
