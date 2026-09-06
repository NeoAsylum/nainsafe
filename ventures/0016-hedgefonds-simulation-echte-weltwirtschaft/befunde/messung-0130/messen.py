"""Messung zu Paket 0130 -- die Berichtsordnung des Belegstellenriegels.

Gemessen werden die beiden Bedingungen der Abnahme, und zwar so, dass jede
einzeln reissen kann:

  A. **Zwei Kopien desselben Bestands auf verschiedenen Dateisystemen.** Derselbe
     selbst uebersetzte Riegel laeuft ueber beide; `stdout` und `stderr` muessen
     zeichengleich sein. Der Positiv-Zwilling ist der Stand **vor** der Aenderung
     (aus `git show`), uebersetzt mit denselben Schaltern: Dort muss derselbe
     Vergleich einen Unterschied zeigen, sonst belegt das Gruen nichts ueber die
     Ursache.

  B. **Der neue Fall im Selbsttest.** Vier Mutanten des ausgelieferten Standes,
     jeder gegen eine der drei Regeln in `vor_in_byteordnung` und einer gegen die
     Sortierung selbst. Geprueft wird nicht nur, dass sie sterben, sondern
     **woran**: Reisst eine fremde Falltabelle mit, misst der Mutant nicht die
     Regel, die er treffen soll.

## Wie die Kopien hergestellt sind

Der ganze Arbeitsbaum misst 3,4 GB, und keine zweite Ablage dieses Rechners nimmt
ihn zweimal auf. Zwei Verkuerzungen sind moeglich, ohne dass sich an der Ausgabe
des Riegels etwas aendert, und beide folgen aus seinem eigenen Quelltext:

  1. Von `bau` und `befunde` liest er keinen Inhalt -- von dort sammelt er allein
     Pfade in die Menge der ungelesenen Orte. Dort genuegen leere Dateien.
  2. `ist_zieldatei` laesst nur `CMakeLists.txt` und die acht Endungen aus
     `ENDUNGEN` durch. Was daran scheitert, sieht er ueberhaupt nicht -- weder mit
     Inhalt noch mit Namen. Diese 39.671 Dateien entstehen gar nicht erst.

Uebrig bleiben 796 abgeschriebene Dateien mit 7,3 MB und 87.548 leere Namen.

Dass die Verkuerzung nichts an der Messung aendert, wird nicht behauptet, sondern
geprueft: Schritt 0 laesst den neuen Riegel ueber den **echten** Arbeitsbaum und
ueber Kopie A laufen und verlangt zeichengleiche Ausgabe. Erst danach zaehlt der
Rest.

Versteckte Ordner (`.git`, `.claude`) faehrt die Kopie nicht mit -- dieselbe Regel,
nach der `ist_maschinerie` sie im Riegel uebergeht.

Drei Kopien entstehen, alle mit derselben Funktion. Aus dem Arbeitsbaum
abgeschrieben wird **einmal** -- B und C entstehen aus A und nicht aus dem Baum:

  A  ext4  (`/home/adria/fabrik/.messung-0130-ext4`),    aus dem Arbeitsbaum, aufsteigend
  B  tmpfs (`$TMPDIR/messung-0130-tmpfs`),               aus A, aufsteigend
  C  ext4  (`/home/adria/fabrik/.messung-0130-ext4-ab`), aus A, absteigend

Der Grund steht bei `baue_kopie`: An diesem Vorhaben arbeiten mehrere Agenten
gleichzeitig, und der Lauf um 03:40 am 2026-09-06 hat drei verschiedene
Fingerabdruecke gemeldet, weil zwischen A und B ein fremdes Paket eine Datei
angelegt hat.

A gegen B ist der Vergleich, den die Abnahme woertlich verlangt: zwei
Dateisysteme. A gegen C ist der Vergleich, der den Zwilling **sicher** rot macht --
zwei frisch angelegte Baeume koennen auf verschiedenen Dateisystemen zufaellig
dieselbe Auflistungsordnung haben, zwei in verschiedener Ordnung angelegte nicht.
Beide werden gemessen und beide berichtet. Nur eine der drei Kopien liegt im
tmpfs: Dort kostet auch eine leere Datei eine Seite, und der erste Anlauf am
2026-09-06 hat mit zweien den Dateibaum volllaufen lassen.

Dass A, B und C denselben Inhalt tragen, steht nicht als Behauptung da: Zu jeder
Kopie wird ein Verzeichnis aus Pfad, Groesse und SHA-256 jeder Datei gebildet und
dessen SHA-256 gedruckt. Drei gleiche Fingerabdruecke sind der Nachweis.

Aufruf (aus WSL, aus dem Wurzelverzeichnis der Fabrik):

    python3 ventures/0016-.../befunde/messung-0130/messen.py

Rueckgabe 0, wenn beide Bedingungen halten; 1 bei der ersten Abweichung. Das
Skript ist damit selbst ein Riegel und kein Bericht.
"""
import hashlib
import os
import shutil
import subprocess
import sys

WURZEL = "/home/adria/fabrik"
VENTURE = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
SPECS = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
QUELLE = os.path.join(VENTURE, "werkzeuge/belegstellen/belegstellen_riegel.cpp")
# Die beiden Ordner, von denen der Riegel nur die Namen sammelt.
NUR_NAMEN = ("bau", "befunde")
# `ENDUNGEN` aus dem Riegel. Was hier fehlt, sieht er nicht -- und muss deshalb in
# der Kopie auch nicht liegen. Weicht die Liste einmal ab, faellt Schritt 0.
ENDUNGEN = (".md", ".toml", ".cpp", ".hpp", ".txt", ".cmake", ".py", ".rs")

TMP = os.environ.get("TMPDIR") or "/tmp"
ARBEIT = os.path.join(TMP, "messung-0130")
EXT4 = os.path.join(WURZEL, ".messung-0130-ext4")
EXT4_AB = os.path.join(WURZEL, ".messung-0130-ext4-ab")

# Dieselben Schalter fuer jeden Bau dieses Laufs -- Stand, Mutanten und
# Vergleichsstand. Ohne `-Werror`: Ein Mutant laesst gern etwas ungenutzt liegen,
# und dann wuerde der Bau rot statt des Tests.
SCHALTER = ["-std=c++20", "-fwrapv", "-O1", "-Wall", "-Wextra"]

fehler = []


def melde(satz):
    fehler.append(satz)
    print("  ROT: %s" % satz)


def lauf(befehl, **kw):
    return subprocess.run(befehl, capture_output=True, text=True, **kw)


def kopf():
    return lauf(["git", "-C", WURZEL, "rev-parse", "--short", "HEAD"]).stdout.strip()


# ---------------------------------------------------------------------------
# Die Kopien
# ---------------------------------------------------------------------------

def sieht_der_riegel(name):
    """`ist_zieldatei` nachgebaut. Was hier durchfaellt, legt die Kopie nicht an."""
    if name == "CMakeLists.txt":
        return True
    punkt = name.rfind(".")
    return punkt != -1 and name[punkt:] in ENDUNGEN


def _abstieg(quelle, ziel, hohl, absteigend):
    eintraege = sorted(os.listdir(quelle), reverse=absteigend)
    for name in eintraege:
        q = os.path.join(quelle, name)
        z = os.path.join(ziel, name)
        if os.path.isdir(q) and not os.path.islink(q):
            if name.startswith("."):
                continue  # dieselbe Regel wie `ist_maschinerie` im Riegel
            os.mkdir(z)
            _abstieg(q, z, hohl or name in NUR_NAMEN, absteigend)
        elif os.path.isfile(q) and sieht_der_riegel(name):
            if hohl:
                open(z, "wb").close()
            else:
                shutil.copyfile(q, z)


def baue_kopie(ziel, quelle, absteigend):
    """Kopie von `quelle` nach `ziel`, Eintraege in der gewaehlten Ordnung angelegt.

    `quelle` ist fuer A der Arbeitsbaum und fuer B und C die Kopie A. Aus dem
    Arbeitsbaum abgeschrieben wird also **einmal**, und das ist der Grund: An
    diesem Vorhaben arbeiten mehrere Agenten gleichzeitig. Der Lauf um 03:40 am
    2026-09-06 hat drei verschiedene Fingerabdruecke gemeldet, weil zwischen A und
    B ein fremdes Paket eine Datei anlegte. Ein Vergleich zwischen zwei Baeumen,
    die zu verschiedenen Zeitpunkten entstanden sind, misst die Drift mit."""
    if os.path.exists(ziel):
        shutil.rmtree(ziel)
    os.makedirs(ziel)
    for stamm in (VENTURE, SPECS):
        unten = os.path.join(ziel, stamm)
        os.makedirs(unten)
        _abstieg(os.path.join(quelle, stamm), unten, False, absteigend)
    return ziel


def fingerabdruck(baum):
    """Pfad, Groesse und Inhalt jeder Datei -- in fester Ordnung, damit der
    Fingerabdruck den Inhalt misst und nicht die Auflistungsordnung."""
    zeilen = []
    for ordner, unter, dateien in os.walk(baum):
        unter[:] = [u for u in unter if not u.startswith(".")]
        for d in dateien:
            voll = os.path.join(ordner, d)
            with open(voll, "rb") as f:
                inhalt = f.read()
            zeilen.append("%s %d %s" % (os.path.relpath(voll, baum), len(inhalt),
                                        hashlib.sha256(inhalt).hexdigest()))
    zeilen.sort()
    return hashlib.sha256("\n".join(zeilen).encode()).hexdigest(), len(zeilen)


# ---------------------------------------------------------------------------
# Bauen und Laufen
# ---------------------------------------------------------------------------

def uebersetze(quelltext, name):
    cpp = os.path.join(ARBEIT, name + ".cpp")
    bin_ = os.path.join(ARBEIT, name)
    with open(cpp, "w") as f:
        f.write(quelltext)
    e = lauf(["g++"] + SCHALTER + ["-o", bin_, cpp])
    if e.returncode != 0:
        print(e.stderr[-3000:])
        raise SystemExit("Bau von '%s' fehlgeschlagen." % name)
    return bin_


def laufe(binaer, baum):
    e = lauf([binaer, os.path.join(baum, VENTURE)])
    return e.returncode, e.stdout, e.stderr


def vergleiche(binaer, links, rechts):
    cl, al, fl = laufe(binaer, links)
    cr, ar, fr = laufe(binaer, rechts)
    gleich = (al == ar) and (fl == fr)
    return gleich, (cl, cr), (al, fl), (ar, fr)


def erster_unterschied(a, b):
    za, zb = a.split("\n"), b.split("\n")
    for i in range(min(len(za), len(zb))):
        if za[i] != zb[i]:
            return "Zeile %d:\n      A: %s\n      B: %s" % (i + 1, za[i][:100],
                                                            zb[i][:100])
    return "verschiedene Laenge: %d gegen %d Zeilen" % (len(za), len(zb))


# ---------------------------------------------------------------------------
# Die Mutanten
# ---------------------------------------------------------------------------

# Name, erwarteter Wortlaut, Ersatz, was der Mutant trifft, und der Fall, der
# **namentlich** reissen muss. Das letzte Feld ist der Unterschied zwischen "ein
# Mutant stirbt" und "er stirbt an der Regel, die er treffen soll".
MUTANTEN = [
    ("char-statt-unsigned",
     "        const unsigned char l = static_cast<unsigned char>(links[i]);\n"
     "        const unsigned char r = static_cast<unsigned char>(rechts[i]);",
     "        const char l = static_cast<char>(links[i]);\n"
     "        const char r = static_cast<char>(rechts[i]);",
     "der Umlautfall: vorzeichenbehaftet ist 0xC3 negativ und steht ganz vorn",
     "Übersicht.md"),
    ("gross-wie-klein",
     "        if (l != r) {\n            return l < r;\n        }",
     "        const unsigned char lk = (l >= 'A' && l <= 'Z')\n"
     "                                     ? static_cast<unsigned char>(l + 32) : l;\n"
     "        const unsigned char rk = (r >= 'A' && r <= 'Z')\n"
     "                                     ? static_cast<unsigned char>(r + 32) : r;\n"
     "        if (lk != rk) {\n            return lk < rk;\n        }",
     "das Gebietsschema nachgestellt: Gross- und Kleinschreibung ineinander",
     "CMakeLists.txt"),
    ("laengeres-zuerst",
     "    return links.size() < rechts.size();",
     "    return links.size() > rechts.size();",
     "die Regel zum gemeinsamen Anfang umgedreht",
     "daten/reihen.toml.alt"),
    ("ohne-sortierung",
     "    std::sort(gefunden.begin(), gefunden.end(),\n"
     "              [](const fs::path& links, const fs::path& rechts) {\n"
     "                  const std::string a = links.string();\n"
     "                  const std::string b = rechts.string();\n"
     "                  return vor_in_byteordnung(a, b);\n"
     "              });\n"
     "    return gefunden;",
     "    return gefunden;",
     "die Sortierung an der Sammelstelle weg -- der Selbsttest sieht sie nicht",
     None),
]

# Die Koepfe der sieben Falltabellen auf `stderr`. `Selbsttest ` deckt drei davon
# ab (Suche nach links, Abstand, Satzgrenze); genauer muss es nicht sein, denn
# gefragt ist allein, ob **ausser** der Ordnung etwas reisst.
MARKEN = ("Ordnungsfall ", "Selbsttest ", "Urteilsfall ", "Zielfall ", "Zitatfall ")


def tabellen_gerissen(text):
    getroffen = []
    for zeile in text.split("\n"):
        z = zeile.strip()
        for marke in MARKEN:
            if z.startswith(marke):
                getroffen.append(marke.strip())
    return sorted(set(getroffen))


# ---------------------------------------------------------------------------

def main():
    os.chdir(WURZEL)
    stand_vorher = kopf()
    print("HEAD vor der Messung: %s" % stand_vorher)
    if os.path.exists(ARBEIT):
        shutil.rmtree(ARBEIT)
    os.makedirs(ARBEIT)

    with open(os.path.join(WURZEL, QUELLE)) as f:
        neu_text = f.read()
    alt_text = lauf(["git", "-C", WURZEL, "show", "HEAD:" + QUELLE]).stdout
    if not alt_text.strip():
        raise SystemExit("Der Stand vor der Aenderung liess sich nicht lesen.")
    if "vor_in_byteordnung" in alt_text:
        raise SystemExit("HEAD traegt die Aenderung schon -- kein Zwilling moeglich.")

    print("\n== Bauen ==")
    alt = uebersetze(alt_text, "riegel_alt")
    neu = uebersetze(neu_text, "riegel_neu")
    print("  alt (HEAD, ohne Sortierung) und neu (Arbeitsbaum) uebersetzt, Schalter %s"
          % " ".join(SCHALTER))

    # -- Schritt 0: taugt die verkuerzte Kopie als Bestand? -------------------
    #
    # Bis zu drei Anlaeufe: An diesem Vorhaben arbeiten mehrere Agenten
    # gleichzeitig, und legt einer waehrend des Abschreibens eine Datei an, ist der
    # Unterschied die Drift und nicht die Verkuerzung. Ein einziger Anlauf, der
    # zusammenpasst, genuegt als Nachweis; drei, die es nicht tun, sind ein Befund.
    print("\n== Schritt 0: Kopie A gegen den echten Arbeitsbaum ==")
    gelungen = False
    for versuch in (1, 2, 3):
        baue_kopie(EXT4, WURZEL, False)
        ce, ae, fe = laufe(neu, WURZEL)
        ck, ak, fk = laufe(neu, EXT4)
        print("  Anlauf %d: echter Baum Code %d, Kopie A Code %d -- %s"
              % (versuch, ce, ck,
                 "gleich" if (ae == ak and fe == fk) else "VERSCHIEDEN"))
        if ae == ak and fe == fk:
            gelungen = True
            break
        print("    %s" % erster_unterschied(ae + fe, ak + fk))
    if not gelungen:
        melde("Der neue Riegel meldet ueber Kopie A dreimal etwas anderes als "
              "ueber den echten Baum. Entweder aendert die Verkuerzung (leere "
              "Dateien unter bau/ und befunde/) die Messung, oder der Baum steht "
              "keine zwei Laeufe lang still. Alles Weitere haengt in der Luft.")
        return
    print("  gleich auf stdout und stderr -- die verkuerzte Kopie ist ein "
          "tauglicher Bestand.")

    print("\n== Die drei Kopien ==")
    kopien = [("A ext4  aufsteigend", EXT4),
              ("B tmpfs aufsteigend",
               baue_kopie(os.path.join(TMP, "messung-0130-tmpfs"), EXT4, False)),
              ("C ext4  absteigend", baue_kopie(EXT4_AB, EXT4, True))]
    abdruecke = []
    for name, pfad in kopien:
        fa, n = fingerabdruck(pfad)
        abdruecke.append(fa)
        print("  %s: %d Dateien, Fingerabdruck %s" % (name, n, fa[:16]))
    if len(set(abdruecke)) != 1:
        melde("Die drei Kopien tragen nicht denselben Inhalt. Jeder Vergleich "
              "darunter misst damit den Inhalt und nicht die Ordnung.")
        return

    # -- Bedingung 1 ---------------------------------------------------------
    print("\n== Bedingung 1: dieselbe Ausgabe ueber verschiedene Dateisysteme ==")
    for links, rechts, was in ((0, 1, "A ext4 gegen B tmpfs, beide aufsteigend"),
                               (0, 2, "A gegen C, beide ext4, C absteigend angelegt")):
        gleich_alt, codes_alt, la, ra = vergleiche(alt, kopien[links][1],
                                                   kopien[rechts][1])
        gleich_neu, codes_neu, ln, rn = vergleiche(neu, kopien[links][1],
                                                   kopien[rechts][1])
        print("\n  %s" % was)
        print("    vorher (HEAD):        %s  (Code %d / %d)"
              % ("gleich" if gleich_alt else "VERSCHIEDEN", *codes_alt))
        if not gleich_alt:
            print("    %s" % erster_unterschied(la[0] + la[1], ra[0] + ra[1]))
        print("    nachher (Arbeitsbaum): %s  (Code %d / %d)"
              % ("gleich" if gleich_neu else "VERSCHIEDEN", *codes_neu))
        if not gleich_neu:
            melde("%s: der neue Riegel meldet ueber zwei inhaltsgleiche Kopien "
                  "Verschiedenes.\n      %s"
                  % (was, erster_unterschied(ln[0] + ln[1], rn[0] + rn[1])))

    # Der Zwilling: mindestens einer der beiden Vergleiche muss vorher rot sein.
    zwilling = []
    for links, rechts, was in ((0, 1, "A gegen B"), (0, 2, "A gegen C")):
        g, _, _, _ = vergleiche(alt, kopien[links][1], kopien[rechts][1])
        zwilling.append((was, g))
    if all(g for _, g in zwilling):
        melde("Der Stand vor der Aenderung zeigt in **keinem** der beiden "
              "Vergleiche einen Unterschied. Damit belegt das Gruen nachher "
              "nichts ueber die Ursache -- der Vergleich misst die Ordnung nicht.")
    else:
        rote = [w for w, g in zwilling if not g]
        print("\n  Zwilling: vorher verschieden bei %s -- der Vergleich misst die "
              "Ordnung." % " und ".join(rote))

    # -- Bedingung 2 ---------------------------------------------------------
    print("\n== Bedingung 2: der neue Fall im Selbsttest ==")
    code, aus, err = laufe(neu, kopien[0][1])
    if "zur Ausgabeordnung" not in aus:
        melde("Die Kopfzeile des Riegels nennt die Ausgabeordnung nicht.")
    else:
        for zeile in aus.split("\n")[:4]:
            print("  %s" % zeile)

    for name, alt_text_m, neu_text_m, was, marke in MUTANTEN:
        if neu_text.count(alt_text_m) != 1:
            melde("Mutant '%s': der erwartete Wortlaut kommt %d mal vor, nicht "
                  "genau einmal." % (name, neu_text.count(alt_text_m)))
            continue
        mut = uebersetze(neu_text.replace(alt_text_m, neu_text_m), "mut_" + name)
        code_m, aus_m, err_m = laufe(mut, kopien[0][1])
        getroffen = tabellen_gerissen(err_m)
        print("\n  %s -- %s" % (name, was))
        print("    Code %d, gerissen: %s" % (code_m, ", ".join(getroffen) or "nichts"))
        if marke is None:
            # Dieser Mutant sitzt ausserhalb des Selbsttests: Er muss ihn gruen
            # lassen und stattdessen den Vergleich der Kopien rot machen. Waere er
            # im Selbsttest rot, hielte die Tabelle etwas, das sie nicht kann.
            if code_m == 2:
                melde("Mutant '%s' faellt im Selbsttest. Er sitzt aber an der "
                      "Sammelstelle, die kein Fall der Tabelle sieht -- dann misst "
                      "der Fall etwas anderes, als er behauptet." % name)
            g, _, l2, r2 = vergleiche(mut, kopien[0][1], kopien[1][1])
            print("    A gegen B: %s" % ("gleich" if g else "VERSCHIEDEN"))
            if not g:
                print("    %s" % erster_unterschied(l2[0] + l2[1], r2[0] + r2[1]))
            else:
                melde("Mutant '%s' laesst den Vergleich A gegen B gruen. Dann "
                      "belegt der gruene Lauf des Standes nicht die Sortierung."
                      % name)
            continue
        if code_m != 2:
            melde("Mutant '%s' bricht nicht im Selbsttest ab (Code %d). Der Fall "
                  "misst die Regel nicht." % (name, code_m))
            continue
        if getroffen != ["Ordnungsfall"]:
            melde("Mutant '%s' laesst nicht die Ordnung allein reissen, sondern "
                  "%s. Dann ist die Zahl keiner Regel allein zuzurechnen."
                  % (name, ", ".join(getroffen) or "gar nichts"))
        rote = [z.strip() for z in err_m.split("\n")
                if z.strip().startswith("Ordnungsfall")]
        for zeile in rote:
            print("    %s" % zeile[:120])
        if not any(marke in z for z in rote):
            melde("Mutant '%s' reisst, aber an keinem Fall, der '%s' nennt. Er "
                  "stirbt aus einem anderen Grund als dem gemeinten."
                  % (name, marke))

    # -- Aufraeumen ----------------------------------------------------------
    shutil.rmtree(EXT4)
    shutil.rmtree(EXT4_AB)
    stand_nachher = kopf()
    print("\nHEAD nach der Messung: %s" % stand_nachher)
    if stand_vorher != stand_nachher:
        print("  Achtung: der Baum ist waehrend der Messung gewandert. Die Zahlen "
              "oben gehoeren zu keinem einzelnen Stand.")

    print("\n" + "=" * 70)
    if fehler:
        print("%d Abweichung(en). Die Abnahme haelt nicht." % len(fehler))
        return 1
    print("Beide Bedingungen halten, gemessen gegen %s." % stand_vorher)
    return 0


if __name__ == "__main__":
    sys.exit(main())
