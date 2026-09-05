# Messwerkzeug zu Paket 0090. Es misst und aendert nichts am Vorhaben.
#
# Zwei Teile, beide aus der Abnahme:
#   1. Der Riegel gegen den Arbeitsbaum -- Bedingung 2 darf zu den fuenf
#      Fundstellen still sein, und die Zahl der uebergangenen Fundstellen darf
#      gegenueber dem Stand vor dem Lauf nicht steigen.
#   2. Die Gegenprobe: dieselbe Messung an einer Kopie **ausserhalb des Repos**,
#      in der die Gliederungszeile aus `rueckstand.md` geloescht ist.
#
# Dazu die Bilanz mit `tomllib` gegen den vor dem Lauf notierten Blob, wie sie
# `pruefweg.toml_geprueft` fuer jede Aenderung an `reihen.toml` verlangt.

import os
import shutil
import subprocess
import sys
import tomllib

REPO = "/home/adria/fabrik"
VORHABEN = REPO + "/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
RIEGEL = VORHABEN + "/werkzeuge/belegstellen/bau/belegstellen_riegel"
ZEILE = "## Was der Geschäftsführer entscheiden lassen muss"

FUENF = (
    "daten/reihen.toml",
    "daten/einheitenbefund-pwt-baci.md",
)


def lauf(wurzel):
    e = subprocess.run([RIEGEL, wurzel], capture_output=True, text=True)
    return e.returncode, e.stdout + e.stderr


def kennzahlen(text):
    zahlen = {}
    for zeile in text.splitlines():
        if "Zitate der geprueften Form" in zeile:
            zahlen["bilanzzeile"] = zeile.strip()
    zahlen["uebergangen"] = [
        z.strip() for z in text.splitlines()
        if z.strip().startswith(("daten/", "rueckstand.md:", "parameter.toml:",
                                 "kern/", "pruefstand/", "werkzeuge/"))
        and ":" in z and "(" in z
    ]
    return zahlen


def bericht(titel, wurzel):
    code, text = lauf(wurzel)
    z = kennzahlen(text)
    print("=" * 70)
    print(titel)
    print("  Rueckgabecode:", code)
    print(" ", z.get("bilanzzeile", "<keine Bilanzzeile>"))
    print("  uebergangene Fundstellen gezaehlt:", len(z["uebergangen"]))
    for zeile in text.splitlines():
        if "belegstellen_riegel:" in zeile or "Abschnittszitat(e)" in zeile:
            print("  !", zeile.strip())
    treffer = [z2 for z2 in text.splitlines()
               if "Geschaeftsfuehrer entscheiden lassen muss" in z2]
    print("  Zeilen der Ausgabe, die den gesuchten Wortlaut nennen:", len(treffer))
    for t in treffer:
        print("     ", t.strip())
    fuenf = [z2 for z2 in text.splitlines()
             if any(f in z2 for f in FUENF) and "zitierend" in z2]
    print("  Befundzeilen zu den beiden Dateien:", len(fuenf))
    for f in fuenf:
        print("     ", f.strip())
    return code, text, z


def gegenprobe(ziel):
    # Der Riegel sucht seine zweite Wurzel als <X>/specs/<name>, wenn die erste
    # <X>/ventures/<name> ist (belegstellen_riegel.cpp, die Zeile mit
    # parent_path().parent_path()). Die Kopie muss diesen Bau nachstellen, sonst
    # faellt die halbe Zielmenge weg und der Lauf bricht an der Untergrenze ab --
    # gemessen, der erste Versuch endete so mit Code 2.
    if os.path.exists(ziel):
        shutil.rmtree(ziel)
    name = os.path.basename(VORHABEN)
    ohne = shutil.ignore_patterns("bau", ".git")
    shutil.copytree(VORHABEN, ziel + "/ventures/" + name, ignore=ohne)
    shutil.copytree(REPO + "/specs/" + name, ziel + "/specs/" + name, ignore=ohne)
    ziel = ziel + "/ventures/" + name
    pfad = ziel + "/rueckstand.md"
    quelle = open(pfad, encoding="utf-8").read().splitlines(keepends=True)
    behalten = [z for z in quelle if z.rstrip("\n") != ZEILE]
    weg = len(quelle) - len(behalten)
    open(pfad, "w", encoding="utf-8").writelines(behalten)
    print("Gegenprobe vorbereitet:", ziel)
    print("  geloeschte Zeilen aus rueckstand.md:", weg)
    assert weg == 1, "die Gliederungszeile stand nicht genau einmal da"
    return ziel


def bilanz(altblob):
    pfad = VORHABEN + "/daten/reihen.toml"
    neu_roh = open(pfad, "rb").read()
    neu = tomllib.loads(neu_roh.decode("utf-8"))
    alt_roh = subprocess.run(["git", "-C", REPO, "cat-file", "blob", altblob],
                             capture_output=True, check=True).stdout
    alt = tomllib.loads(alt_roh.decode("utf-8"))
    print("=" * 70)
    print("reihen.toml, Parserlauf gegen die vorliegende Fassung")
    print("  gueltiges TOML 1.0; reihe", len(neu["reihe"]),
          "widerspruch", len(neu["widerspruch"]),
          "wurzeltabellen", sorted(neu))
    print("  sollreihen-Summe", sum(r["sollreihen"] for r in neu["reihe"]),
          "gegen zaehlung.sollreihen_gesamt", neu["zaehlung"]["sollreihen_gesamt"])
    print("  zweimal eingelesen ergibt dasselbe:",
          tomllib.loads(neu_roh.decode("utf-8")) == neu)

    def flach(o, p=()):
        if isinstance(o, dict):
            for k, v in o.items():
                yield from flach(v, p + (k,))
        elif isinstance(o, list):
            for i, v in enumerate(o):
                yield from flach(v, p + (i,))
        else:
            yield p, o

    a, b = dict(flach(alt)), dict(flach(neu))
    print("  Blattwerte alt", len(a), "neu", len(b))
    print("  weggefallen", sorted(set(a) - set(b)))
    print("  neu", sorted(set(b) - set(a)))
    versch = sorted(k for k in set(a) & set(b) if a[k] != b[k])
    print("  verschieden", len(versch))
    for k in versch:
        print("     ", ".".join(str(t) for t in k))


def fremdstand_zuruecksetzen(wurzel, datei, commit):
    """Setzt eine Datei, die ein **fremder** Lauf gerade halbfertig im
    Arbeitsbaum liegen hat, in der Kopie auf den Stand vor meinem Lauf zurueck.
    Der Arbeitsbaum selbst bleibt unberuehrt -- er gehoert dem anderen Paket."""
    roh = subprocess.run(["git", "-C", REPO, "show", commit + ":" + datei],
                         capture_output=True, check=True).stdout
    innen = datei.split("/", 2)[2]
    open(wurzel + "/" + innen, "wb").write(roh)
    print("  zurueckgesetzt auf", commit + ":", innen)


if __name__ == "__main__":
    basis = os.environ.get("TMPDIR", "/tmp") + "/gegenprobe-0090"
    bericht("Arbeitsbaum (die Gliederungszeile steht noch da)", VORHABEN)
    kopie = gegenprobe(basis)
    bericht("Kopie ausserhalb des Repos, Gliederungszeile geloescht", kopie)
    if len(sys.argv) > 2:
        # Dieselbe Kopie, aber ohne den fremden halbfertigen Stand. Sie trennt,
        # was dieses Paket verantwortet, von dem, was ein gleichzeitig laufendes
        # Paket in eine Datei ausserhalb meiner Dateiliste geschrieben hat.
        print("=" * 70)
        print("Dieselbe Kopie, fremder Zwischenstand zurueckgesetzt")
        fremdstand_zuruecksetzen(
            kopie,
            "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
            "/kern/test/zustandsausgabe_probe.cpp",
            sys.argv[2])
        bericht("  -> Messung", kopie)
    if len(sys.argv) > 1:
        bilanz(sys.argv[1])
