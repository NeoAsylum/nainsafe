#!/usr/bin/env python3
# Paket 0099 -- misst die drei Zahlwoerter des Kommentars ueber [datei.vorlagen].
#
# 1. "Der Stand der <N> Vorlagen"  -> Zahl der Schluessel in [datei.vorlagen].
# 2. Die 0065-Zaehlung, Teil eins: Blattwerte, deren Schluessel `beleg` heisst
#    und die die Zeichenfolge einheitenbefund-pwt-baci tragen.
# 3. Die 0065-Zaehlung, Teil zwei: alle Blattwerte mit dieser Zeichenfolge,
#    zerlegt in beleg + Vorlagenschluessel + Rest (benannt nach dem letzten
#    Pfadteil, der keine Listennummer ist).
#
# Aufruf: python3 befunde/messung-0099/zahlwoerter.py <blob-sha|-> <pfad>
# Bei "-" wird allein der Arbeitsbaum gemessen, sonst Bezugsstand und Arbeitsbaum.
import subprocess, sys, tomllib

MARKE = "einheitenbefund" + "-pwt-baci"


def flach(o, p=()):
    if isinstance(o, dict):
        for k, v in o.items():
            yield from flach(v, p + (k,))
    elif isinstance(o, list):
        for i, v in enumerate(o):
            yield from flach(v, p + (str(i),))
    else:
        yield p, o


def letzter_name(pfad):
    for teil in reversed(pfad):
        if not teil.isdigit():
            return teil
    return "?"


def messe(name, roh):
    baum = tomllib.loads(roh.decode("utf-8"))
    blaetter = dict(flach(baum))
    print("== %s ==" % name)

    vorlagen = sorted(baum["datei"]["vorlagen"])
    print("  [datei.vorlagen]: %d Schluessel -- %s" % (len(vorlagen), ", ".join(vorlagen)))
    for k in vorlagen:
        wert = baum["datei"]["vorlagen"][k]
        print("      %-14s Stand genannt: %-5s | %s"
              % (k, "Stand" in wert or "Fassung" in wert, wert))

    treffer = {k: v for k, v in blaetter.items()
               if isinstance(v, str) and MARKE in v}
    belege = sorted(k for k in treffer if k[-1] == "beleg")
    vorlage = sorted(k for k in treffer if k[:2] == ("datei", "vorlagen"))
    rest = sorted(set(treffer) - set(belege) - set(vorlage))
    print("  0065 Teil 1 -- Schluessel `beleg` mit der Marke: %d  %s"
          % (len(belege), [".".join(k) for k in belege]))
    print("  0065 Teil 2 -- Blattwerte mit der Marke insgesamt: %d" % len(treffer))
    print("       Zerlegung %d + %d + %d = %d"
          % (len(belege), len(vorlage), len(rest), len(treffer)))
    print("       Vorlagenschluessel: %s" % [".".join(k) for k in vorlage])
    namen = {}
    for k in rest:
        namen[letzter_name(k)] = namen.get(letzter_name(k), 0) + 1
    print("       Rest nach letztem Namensteil: %s" % namen)
    for k in rest:
        print("         %s" % ".".join(k))
    doppelt = (set(belege) & set(vorlage)) | (set(belege) & set(rest)) | (set(vorlage) & set(rest))
    print("       keiner doppelt: %s | keiner ausgelassen: %s"
          % (not doppelt, len(belege) + len(vorlage) + len(rest) == len(treffer)))
    print()


ziel = sys.argv[2]
if sys.argv[1] != "-":
    alt = subprocess.run(["git", "cat-file", "blob", sys.argv[1]],
                         cwd="/home/adria/fabrik", capture_output=True, check=True).stdout
    messe("Bezugsstand " + sys.argv[1][:7], alt)
with open(ziel, "rb") as f:
    messe("Arbeitsbaum " + ziel, f.read())
