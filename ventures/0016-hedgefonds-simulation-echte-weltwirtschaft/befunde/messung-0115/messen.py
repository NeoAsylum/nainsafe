#!/usr/bin/env python3
"""Paket 0115 -- der Riegel zu den drei berichtigten Zahlen im Kopf des
`belegstellen_riegel`.

Kein Bericht: Jede Erwartung steht hier im Skript, und der Rueckgabewert ist 1,
sobald eine nicht aufgeht. Was das Skript prueft:

  A. **Zwei Uebersetzungen, ein Bestand.** Die alte und die neue Fassung des
     Riegels laufen im *selben* Aufruf ueber den *selben* Baum, wenige Sekunden
     auseinander, und muessen dieselben drei Zahlen von Bedingung 2, denselben
     Rueckgabewert und dieselbe Befundliste melden. Zwei getrennte Laeufe
     wuerden die Drift des Baums mitmessen -- am 2026-09-05 ist der Bestand
     einer Rolle waehrend ihres eigenen Laufs von 37 auf 40 Zitate gewandert,
     von fremder Hand.

     **Seit Paket 0283 steht der Bestand fuer beide Laeufe still, und das ist
     der ganze Teil A.** Bis dahin stellte er den Quellbaum fuer die Dauer von
     Lauf A auf die alte Fassung zurueck. Damit unterschieden sich die beiden
     Laeufe im Code **und** im Bestand -- dieser Riegel zaehlt einen Bestand,
     der seinen eigenen Quelltext enthaelt.

     **Wie ein Leser damit das alte Rot erzeugt hat.** Ein Zitat im Sinn von
     Bedingung 2 braucht eines der vier Schluesselwoerter aus `SCHLUESSEL` und
     dahinter eine Ueberschrift, die es gibt. Der Kopfkommentar des Riegels
     fuehrt solche Stellen selbst. Wer eine davon berichtigte -- nur den
     Kommentar, keine Codezeile --, aenderte den Arbeitsbaum, und den las im
     Tauschfenster allein **Lauf B**: Lauf A lief ueber den archivierten
     Wortlaut aus `VORFASSUNGSSTAND`, den keine Aenderung im Arbeitsbaum
     erreicht. Die berichtigte Stelle fiel damit auf der einen Seite weg und auf
     der anderen nicht, der Vergleich wurde rot, und die Meldung schickte den
     Leser nach einem fremden Commit statt zu seiner eigenen, noch nicht
     eingecheckten Aenderung.

     **Gemessen ist der Tausch, nicht dieser Fall.** Der Nachtlauf zum
     2026-09-07 zeigt Teil A rot: Code 1 gegen Code 0, (36, 34, 57) gegen
     (36, 36, 57), Unterschied genau zwei Fundstellen im eigenen Kopfkommentar,
     `belegstellen_riegel.cpp:32` und `:39`
     (`befunde/uebersetzung-2026-09-07.md:285-289`). Beide standen dort unter
     *„Nur vorher"*, also im archivierten Text des damaligen Ankers `83faa06^`
     (Blob e3038e2, ebd. :281) -- eine nicht eingecheckte Aenderung erreicht ihn
     nicht. Ursache war in jener Nacht eingecheckte Geschichte zwischen Anker
     und heute (0147, 0166, 0182; unten bei `VORFASSUNGSSTAND` mit denselben
     Zahlen belegt), und *„Welcher Commit dazwischen"* war die richtige Antwort.
     Beide Faelle haben dieselbe Wurzel: zwei Laeufe ueber zwei Bestaende.

     (Die vier Woerter stehen im Riegel aus demselben Grund als Oktalfolge da.
     Hier duerfen sie ausgeschrieben stehen: Diese Datei liegt unter `befunde/`
     und damit in `UNGELESENE_ORDNER` -- der Riegel liest sie nicht. Wer diesen
     Stand einmal woandershin legt, muss das mitbedenken.)

     **Warum das nicht mehr geht:** Dieser Stand schreibt `QUELLE` nicht mehr.
     Beide Laeufe lesen den Baum, wie er liegt; eine Kommentaraenderung liegt
     fuer beide gleich da und faellt aus dem Unterschied heraus. Die Stelle, an
     der der Bestand festgelegt wird, ist die, an der nichts geschrieben wird --
     sie steht in `teil_a` benannt, und dass er wirklich stillstand, sieht
     `teil_a` danach nach.

     **Was damit entfaellt, und wer es traegt.** Teil A war die einzige
     Vorrichtung dieses Standes, die alten Kopftext gegen neuen Kopftext gemessen
     hat: Ein Zitat, das im Kopfkommentar ins Leere zeigte, wurde als
     Unterschied zwischen den beiden Laeufen sichtbar. Das deckt Teil A nicht
     mehr ab. Gedeckt bleibt es dreifach:

       * Ein Zitat im Kopfkommentar, das seine Ueberschrift nicht findet, macht
         den `belegstellen_riegel` **selbst** rot -- er liest seinen eigenen
         Quelltext mit, in jedem Nachtlauf und ohne diesen Stand. Genau das war
         am 2026-09-07 der Code 1 der alten Fassung.
       * Die Aussagen des Kopfes prueft Teil B, jede gegen eine eigene Messung:
         `pruefe_angabe1`, `pruefe_angabe2`, `pruefe_fall6`, `teil_b3`.
       * Die Tabelle der sechs Fassungen haelt `befunde/messung-0166/messen.py`
         unter der Probe `belegstellen_wortabstand`.

     Was Teil A seither misst, ist enger und dafuer wahr: ob sich das
     **Verhalten** des Riegels zwischen dem festgeschriebenen Stand und heute
     bewegt hat.
  B. **Die Aussagen des Kopfkommentars selbst**, jede als Beziehung zwischen
     zwei Laeufen desselben Aufrufs. Bis zum 2026-09-08 standen dort die drei
     Zahlen des Bestands als Abschrift, und dieser Stand hielt sie dagegen. Sechs
     fertige Pakete haben sie nacheinander nachgetragen -- 0115, 0166, 0189,
     0227, 0232, 0233 --, und jede Abschrift war mit dem naechsten Commit wieder
     falsch: Der Riegel zaehlt einen Bestand, der seinen eigenen Quelltext
     enthaelt. **Seit Paket 0278 vergleicht dieser Teil ausschliesslich
     Gemessenes mit Gemessenem.** Was der Kopf an absoluten Zahlen fuer den
     menschlichen Leser behaelt, ist dort als Momentaufnahme mit Datum
     ausgewiesen und wird hier nicht mehr geprueft; was hier geprueft wird, sind
     Unterschiede und Gleichheiten zwischen zwei Fassungen, die im selben Aufruf
     ueber denselben Baum laufen.
  C. **Die Vorfassung, an der Teil A haengt, bringt das Skript selbst mit**
     (Paket 0171). Sie ist nicht das, was unter `$TMPDIR` liegt,
     sondern ein benannter Stand aus dem Archiv, festgeschrieben unter
     `VORFASSUNGSSTAND`. Fehlt sie, holt das Skript sie; liegt dort etwas
     anderes, endet der Lauf rot. Vorher hing die Beweiskraft an einer Eingabe,
     die niemand kontrollierte -- geprueft wurde an ihr nur, dass sie ungleich
     der neuen Fassung ist, und `$TMPDIR` ist fluechtig.

     **Ab Paket 0278 wandert dieser Stand nicht mehr mit.** Bis dahin zog ihn
     jede Berichtigung des Kopfkommentars nach (Paket 0189), damit Teil A die
     Wirkung der Berichtigung und nicht den fremden Code dazwischen misst. Es
     gibt keine Berichtigung mehr, die er begleiten koennte: Die Zahlen stehen
     nicht mehr im Kopf.

     **Und seit Paket 0283 heisst sein Rot, was die Meldung sagt.** Solange
     Teil A den Quellbaum tauschte, konnte der Vergleich auch an der eigenen,
     nicht eingecheckten Kommentaraenderung des Lesers rot werden, waehrend die
     Meldung ihn nach einem fremden Commit suchen schickte (siehe A). Beide
     Laeufe lesen jetzt denselben Bestand; bleibt ein Unterschied, ist er im
     uebersetzten Code, und dann gehoert der Commit dazwischen benannt, bevor
     jemand den Stand weiterschiebt.
  D. **Die beiden Mutanten bringt das Skript ebenfalls selbst mit** (Paket 0189).
     Bis dahin holte es sie von einem Erzeuger im Bauordner von CMake. Der wird
     bei jedem frischen Bau neu angelegt; der Erzeuger liegt seit langem nicht
     mehr darin, und damit brach dieser Stand beim ersten Mutanten ab, ohne je
     eine Zahl zu melden. Was ersetzt wird, steht unten als Textersetzung da und
     nicht als Beschreibung, und jede Nadel muss genau einmal treffen.

Gebaut wird ausschliesslich in `$TMPDIR`; was dort angelegt wurde, raeumt der
Lauf am Ende selbst wieder weg. **In den Quellbaum schreibt dieser Stand nicht**
-- seit Paket 0283 an keiner Stelle mehr. Damit sind auch das Tauschfenster, die
Marke `SCHWEBT`, der Signalhandgriff und die Heilung eines unterbrochenen
Vorlaufs entfallen: Sie gab es allein, damit der Tausch einen Abbruch ueberlebt.

Aufruf:  python3 messen.py [--vorhaben <wurzel>] [--uebersetzer <pfad>]
"""
import argparse
import hashlib
import os
import re
import shutil
import subprocess
import sys

# Vorgabewerte fuer den Aufruf von Hand. Im Nachtlauf kommen beide von CMake --
# der Uebersetzer vor allem deshalb, damit hier nicht ein zweiter neben dem
# steht, gegen den der Kasten gebaut wird. Ein Unterschied zwischen beiden faende
# sich sonst nirgends wieder.
VORHABEN_VORGABE = ("/home/adria/fabrik/ventures/"
                    "0016-hedgefonds-simulation-echte-weltwirtschaft")
UEBERSETZER_VORGABE = "/usr/bin/c++"

W = VORHABEN_VORGABE
QUELLE = W + "/werkzeuge/belegstellen/belegstellen_riegel.cpp"
REPO = os.path.dirname(os.path.dirname(W))
UEBERSETZER = UEBERSETZER_VORGABE
TMP = os.environ.get("TMPDIR", "/tmp") + "/k0115"
VORHER = TMP + "/vorher.cpp"
# Hier standen bis zum 2026-09-09 `NACHHER` und `SCHWEBT` -- der Rueckweg und
# die Marke fuer den Fall, dass der Lauf im Tauschfenster stirbt. Mit dem Tausch
# sind sie entfallen (Paket 0283); dieser Stand schreibt nichts in den Quellbaum,
# also gibt es nichts zurueckzulegen.

# Woher die Vorfassung kommt, aus der Teil A seine zweite Uebersetzung baut: ein
# festgeschriebener Stand aus dem Archiv. Die Gegenprobe braucht sie seit Paket
# 0278 nicht mehr -- sie verfaelscht die neue Fassung.
#
# Bis zum 2026-09-08 stand hier der Elternstand des Baucommits von 0115
# (`83faa06^`, Blob e3038e2) fest. Beides ist mit Paket 0189 ersetzt, aus zwei
# Gruenden:
#
#   * Die Vorfassung von 0115 unterscheidet sich vom heutigen Riegel inzwischen
#     durch **Verhalten** und nicht mehr nur durch den berichtigten Kommentar --
#     0147, 0166 und 0182 liegen dazwischen. Teil A verglich damit drei
#     Codestaende und legte den Unterschied der Berichtigung zur Last. Gemessen
#     im Nachtlauf zum 2026-09-07: vorher Code 1 und (36, 34, 57), nachher
#     Code 0 und (36, 36, 57), dazu zwei Befunde nur auf der alten Seite.
#   * Eine Blobkennung laesst sich hier nicht mehr eintragen. Der Stand, den
#     dieses Skript als Vorfassung braucht, ist der, den der schreibende Agent
#     gerade selbst verlaesst; seine Kennung kennt er nicht, denn seit dem
#     2026-09-06 hat keine Rolle eine Schale. Ein **absoluter** Commit ist als
#     Anker aber nicht schwaecher als ein Blob: Er legt den Baum und damit den
#     Inhalt unter dem Pfad kryptographisch fest. Den zweiten Anker brauchte
#     allein die *relative* Angabe `X^`, deren Ziel beim Umschreiben der
#     Geschichte wandert. Die Kennung wird deshalb einmal erfragt und danach
#     genauso nachgerechnet wie zuvor.
#
# Zuletzt nachgezogen mit Paket 0233, von `4d14905` auf den Stand, den jener Lauf
# selbst verliess. **Mit Paket 0278 steht er still** -- siehe C oben: Es gibt
# keine Berichtigung mehr, die er begleiten koennte, und er ist damit ein fester
# Anker fuer das Verhalten des Riegels statt ein mitwandernder Nullpunkt.
VORFASSUNGSSTAND = "dbcd637"
HERKUNFTSPFAD = ("ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
                 "/werkzeuge/belegstellen/belegstellen_riegel.cpp")

# Hier stand bis zum 2026-09-08 ein `BEZUGSSTAND` -- der Commit, gegen den die
# Zahlen im Kopfkommentar erhoben waren. Er ist mit Paket 0278 entfallen, und mit
# ihm die Pruefung, dass Kommentar und Skript denselben Commit nennen. Der Grund
# ist derselbe, aus dem die Zahlen entfallen sind: Der Kopfkommentar behauptet
# nichts mehr ueber einen Baum von gestern, sondern nur noch Beziehungen zwischen
# zwei Fassungen, die dieser Aufruf beide selbst laufen laesst. Ein Bezugsstand
# haette danach nur noch etwas zu binden, was niemand mehr abschreibt.
#
# Die Zaehlzeile der Selbsttests. Wird sie herausgenommen, verlieren die
# Falltabellen ihre Abbruchwirkung, nicht ihre Meldung -- erst dadurch kommt ein
# Mutant, der eine Tabelle reissen laesst, ueberhaupt bis zum Bestand.
ZAEHLZEILE = "            ++falsch;\n"

SCHALTER = ["-fwrapv", "-O1", "-std=c++20"]

ZAHLEN = re.compile(
    r"(\d+) Zitate der geprueften Form gefunden, (\d+) davon aufgeloest "
    r"\(Untergrenze \d+\), (\d+) Fundstellen uebergangen")

fehler = []


def melde(satz):
    fehler.append(satz)
    print("  FEHLSCHLAG: " + satz)


def lies(pfad):
    return open(pfad, encoding="utf-8").read()


# Hier stand bis zum 2026-09-09 ein `schreib(pfad, text)`. Es ist mit dem Tausch
# entfallen und **absichtlich nicht durch etwas anderes ersetzt**: Der einzige
# schreibende Aufruf dieses Standes steht seither in `vorfassung` und legt die
# geholte Vorfassung unter `$TMPDIR` ab. Wer nachsehen will, ob dieser Stand den
# Quellbaum anfasst, sucht nach einem Oeffnen im Schreibmodus -- es gibt genau
# eines, und sein Ziel ist `VORHER`.


def git(*teile):
    """git im Repo, Rueckgabe als Bytes. Ein Fehlschlag beendet den Lauf."""
    p = subprocess.run(["git", "-C", REPO] + list(teile),
                       capture_output=True)
    if p.returncode != 0:
        raise SystemExit("`git %s` ist mit Code %d gescheitert: %s"
                         % (" ".join(teile), p.returncode,
                            p.stderr.decode("utf-8", "replace").strip()))
    return p.stdout


def blobkennung(daten):
    """Die Objektkennung, die git diesem Inhalt gaebe -- ohne git zu fragen.

    Selbst gerechnet und nicht ueber `git hash-object`, damit die Pruefung des
    Inhalts nicht an derselben Stelle haengt wie seine Beschaffung.
    """
    return hashlib.sha1(b"blob %d\0" % len(daten) + daten).hexdigest()


_vorfassung = None
_blob = None


def vorfassung_blob():
    """Die Objektkennung der Vorfassung, einmal aus dem Archiv erfragt.

    Sie steht nicht mehr als Konstante da (siehe oben), sondern folgt aus dem
    festgeschriebenen Stand. Kennt das Archiv den Stand nicht -- weil die
    Geschichte umgeschrieben wurde --, endet der Lauf hier und nicht mit einer
    stillschweigend anderen Messung: `git` faellt durch, und `git()` bricht ab.
    """
    global _blob
    if _blob is None:
        _blob = git("rev-parse", VORFASSUNGSSTAND + ":"
                    + HERKUNFTSPFAD).decode("utf-8").strip()
    return _blob


def vorfassung():
    """Der Wortlaut des festgeschriebenen Standes, an seine Herkunft gebunden.

    Drei Schritte, und jeder kann den Lauf rot machen:

      1. Die Herkunftsangabe wird gegen das Archiv gehalten: Fuehrt der
         festgeschriebene Stand den Pfad ueberhaupt noch? Wer die Geschichte
         umschreibt, bekommt eine Meldung statt einer stillschweigend anderen
         Messung.
      2. Liegt schon eine Datei unter `VORHER`, wird ihr Inhalt nachgerechnet.
         Eine untergeschobene aeltere oder fremde Fassung faellt damit auf,
         bevor eine einzige Zahl erhoben ist. Sie wird **nicht** ueberschrieben:
         Wer sie dort hingelegt hat, soll die Meldung lesen und nicht ihr
         spurloses Verschwinden.
      3. Fehlt sie, holt das Skript sie selbst und rechnet sie genauso nach.
         Damit laeuft der Riegel auf einer frischen Umgebung ohne Handarbeit
         durch, und `$TMPDIR` ist nur noch Zwischenlager statt Eingabe.

    Der Text wird einmal beschafft und gemerkt. Was danach unter dem Pfad
    passiert, aendert nichts mehr an dem, wogegen gemessen wird.
    """
    global _vorfassung
    if _vorfassung is not None:
        return _vorfassung
    herkunft = VORFASSUNGSSTAND + ":" + HERKUNFTSPFAD
    soll = vorfassung_blob()
    if os.path.exists(VORHER):
        with open(VORHER, "rb") as f:
            daten = f.read()
        ist = blobkennung(daten)
        if ist != soll:
            raise SystemExit(
                "Unter %s liegt nicht die Vorfassung von 0115: Der Inhalt "
                "traegt die Blobkennung %s, erwartet ist %s aus %s. Teil A "
                "wuerde das Verhalten des Riegels gegen den falschen Stand "
                "halten, und zwar ohne eine Meldung. Loesche die Datei; das "
                "Skript holt die richtige selbst."
                % (VORHER, ist, soll, herkunft))
        woher = "lag bereit und ist nachgerechnet"
    else:
        daten = git("cat-file", "blob", soll)
        ist = blobkennung(daten)
        if ist != soll:
            raise SystemExit(
                "Das Archiv hat zu %s einen Inhalt mit der Kennung %s "
                "geliefert. Das darf nicht vorkommen." % (soll, ist))
        with open(VORHER, "wb") as f:
            f.write(daten)
        woher = "gefehlt und ist geholt worden"
    print("Vorfassung: %s -- Blob %s aus %s" % (woher, soll,
                                                herkunft))
    _vorfassung = daten.decode("utf-8")
    return _vorfassung


# ---------------------------------------------------------------------------
# Die beiden Mutanten -- Paket 0086, seit Paket 0189 hier statt im Bauordner
#
# Abgeschaltet wird **im Rumpf** und nie am Aufruf: Faellt eine Funktion aus dem
# Spiel, bricht ein Warnsatz mit `-Werror` den Bau ab, statt den Riegel rot zu
# machen. Deshalb bleibt bei beiden der Aufruf stehen und verliert nur seine
# Wirkung.
#
# Was jeder belegen soll, steht im Nachweis zu Paket 0086:
#
#   `ohne-marken-rein`             -- nur ankuendigende Anfuehrungszeichen;
#                                     laesst Fall 4 zum Wortabstand reissen.
#   `rechts-ohne-satzgrenze-rein`  -- die Satzgrenze der Rechtssuche;
#                                     laesst Fall 6 zum Wortabstand reissen.
#
# Das Suffix bedeutet, dass die jeweils **andere** Lockerung nicht mit
# abgeschaltet wird -- sonst fielen Faelle, die mit der gemessenen Regel nichts
# zu tun haben, und der Nachweis zeigte auf die falsche Stelle. Beide Nadeln
# stehen deshalb an genau einer Stelle des Riegels, und dass es genau eine ist,
# wird bei jedem Aufruf nachgezaehlt.
MUTANTEN = {
    "ohne-marken-rein": (
        "        if (nur_ankuendigende && !klammer.kuendigt_an) {",
        "        if (false && nur_ankuendigende && !klammer.kuendigt_an) {"),
    "rechts-ohne-satzgrenze-rein": (
        "    const std::size_t obergrenze = satzende_nach(text, ab);",
        "    const std::size_t satzende = satzende_nach(text, ab);\n"
        "    const std::size_t obergrenze = "
        "satzende > text.size() ? satzende : text.size();"),
}

_neu = None


def mutant(art):
    """Der Wortlaut von **heute** mit genau einer Ersetzung.

    Immer aus der neuen Fassung, auch waehrend der Gegenprobe: Dort wechselt die
    gepruefte Aussage, nicht der Mutant. Ein Mutant aus der alten Fassung wuerde
    die Gegenprobe an einem zweiten Unterschied gruen werden lassen und niemand
    saehe, an welchem von beiden.
    """
    such, ersatz = MUTANTEN[art]
    if _neu is None:
        raise SystemExit("Der Mutant `" + art + "` ist verlangt worden, ehe die "
                         "neue Fassung gelesen war.")
    if _neu.count(such) != 1:
        raise SystemExit(
            "Die Nadel des Mutanten `%s` trifft %d mal statt genau einmal. Der "
            "Riegel ist an dieser Stelle umgeschrieben worden; gemessen wird "
            "nichts, bis die Nadel nachgezogen ist. Gesucht wurde:\n%s"
            % (art, _neu.count(such), such))
    return _neu.replace(such, ersatz)


def bauen(text, name, entschaerfen):
    if entschaerfen:
        if text.count(ZAEHLZEILE) == 0:
            raise SystemExit("Der Filter greift nicht mehr -- die Zaehlzeile "
                             "der Selbsttests hat ihre Gestalt geaendert.")
        text = text.replace(ZAEHLZEILE, "")
    pfad = TMP + "/m_" + name
    p = subprocess.run([UEBERSETZER, "-x", "c++", "-"] + SCHALTER
                       + ["-o", pfad], input=text, text=True,
                       capture_output=True)
    if p.returncode != 0:
        print(p.stderr[-3000:])
        raise SystemExit("Bau von " + name + " fehlgeschlagen")
    return pfad


def laufen(pfad):
    """Rueckgabe, gesamte Ausgabe, `stderr` einzeln.

    Die Befundliste steht auf `stderr`, die drei Zahlen auf `stdout` -- wer nur
    eines von beiden liest, misst die Haelfte.
    """
    p = subprocess.run([pfad, W], capture_output=True, text=True)
    return p.returncode, p.stdout + p.stderr, p.stderr


def drei(ausgabe, wobei):
    t = ZAHLEN.search(ausgabe)
    if not t:
        raise SystemExit("Bedingung 2 hat bei " + wobei + " keine Zahlen "
                         "gemeldet -- der Bestand wurde nicht gelesen.")
    return int(t.group(1)), int(t.group(2)), int(t.group(3))


def kopf():
    return subprocess.run(["git", "-C", REPO, "rev-parse", "--short", "HEAD"],
                          capture_output=True, text=True).stdout.strip()


# ---------------------------------------------------------------------------
# A -- zwei Uebersetzungen, ein Bestand: derselbe Baum, derselbe Aufruf, und
#      zwischen den beiden Laeufen schreibt niemand
# ---------------------------------------------------------------------------
def teil_a(neu):
    alt = vorfassung()
    if alt == neu:
        # Faengt zugleich den Rest eines Laufs von **vor** Paket 0283: Jener
        # Stand tauschte den Quellbaum und konnte ihn, abgeschossen im
        # Tauschfenster, auf der alten Fassung stehen lassen. Steht er dort,
        # sind alt und neu zeichengleich, und der Lauf endet hier laut, statt
        # unter lauter richtigen Zahlen den falschen Bestand zu messen.
        raise SystemExit(
            "Alte und neue Fassung sind zeichengleich -- es gibt nichts zu "
            "messen. Steht der Quellbaum unter %s auf dem Stand %s, gehoert er "
            "zurueckgesetzt." % (HERKUNFTSPFAD, VORFASSUNGSSTAND))
    bin_alt = bauen(alt, "vorher", False)
    bin_neu = bauen(neu, "nachher", False)
    # **Hier wird der Bestand der beiden Laeufe festgelegt, und zwar dadurch,
    # dass nichts geschrieben wird.** Beide lesen den Baum, wie er in diesem
    # Augenblick liegt: dieselben Dateien, derselbe Kopfkommentar. Bis zum
    # 2026-09-09 stand an dieser Stelle `schreib(QUELLE, alt)` samt Tauschfenster,
    # Signalhandgriff und Ruecktausch -- und damit las Lauf A einen anderen
    # Bestand als Lauf B. Der einzige Unterschied zwischen den beiden Laeufen ist
    # jetzt der uebersetzte Code; siehe A im Kopf.
    stand = lies(QUELLE)
    code_a, aus_a, _ = laufen(bin_alt)
    a = drei(aus_a, "der alten Fassung")
    befunde_a = befundliste(aus_a)
    code_b, aus_b, _ = laufen(bin_neu)
    b = drei(aus_b, "der neuen Fassung")
    befunde_b = befundliste(aus_b)
    # Nachgesehen statt behauptet. Deckt die Datei ab, die dieser Stand selbst
    # bewegt hat und an der ein Leser arbeitet; fuer den uebrigen Baum tragen die
    # wenigen Sekunden zwischen beiden Laeufen und der HEAD-Vergleich in `main`.
    if lies(QUELLE) != stand:
        melde("Die Quelldatei hat sich zwischen den beiden Laeufen von Teil A "
              "geaendert. Die beiden Zahlenreihen sind damit ueber verschiedene "
              "Bestaende erhoben und gehoeren neu erhoben.")

    print("A  vorher : Code %d, %d Zitate, %d aufgeloest, %d uebergangen"
          % ((code_a,) + a))
    print("A  nachher: Code %d, %d Zitate, %d aufgeloest, %d uebergangen"
          % ((code_b,) + b))
    if a != b:
        melde("Zwischen dem festgeschriebenen Stand %s und heute hat sich das "
              "Verhalten des Riegels bewegt: %s -> %s. Beide Laeufe gingen im "
              "selben Aufruf ueber denselben Bestand -- der Unterschied liegt "
              "im uebersetzten Code, nicht im Baum. Welcher Commit dazwischen "
              "das getan hat, gehoert benannt." % (VORFASSUNGSSTAND, a, b))
    if code_a != code_b:
        melde("Derselbe Vergleich am Rueckgabewert: %d -> %d."
              % (code_a, code_b))
    # Die Zahlen allein genuegen nicht: Ein weggefallener und ein neuer Befund
    # heben einander in der Summe auf. Verglichen werden deshalb die Listen.
    if sorted(befunde_a) != sorted(befunde_b):
        melde("Die Befundlisten sind nicht dieselben. Nur vorher: %s. Nur "
              "nachher: %s."
              % (sorted(set(befunde_a) - set(befunde_b)),
                 sorted(set(befunde_b) - set(befunde_a))))
    if code_b != 0:
        # Kein Fehlschlag dieses Pakets, aber es gehoert abgedruckt: Der Riegel
        # ist ueber diesem Baum rot, und beide Fassungen sehen dasselbe -- es
        # liegt also am Bestand und nicht an einem Commit zwischen den beiden.
        print("A  Der Riegel ist rot -- vorher wie nachher (Code %d). Die "
              "Befunde stehen unten und gehoeren nicht zu 0115:" % code_b)
        for z in befunde_b:
            print("     " + z)
    return b


def befundliste(ausgabe):
    """Alle gemeldeten Stellen beider Bedingungen, ohne die Zaehlzeilen."""
    treffer = re.findall(r"^  (\S+:\d+  ->.*|zitierend: \S+:\d+)$", ausgabe,
                         re.M)
    return [t.strip() for t in treffer]


# ---------------------------------------------------------------------------
# B -- die Aussagen des Kopfkommentars, jede gegen zwei Messungen desselben
#      Aufrufs
#
# Bis zum 2026-09-08 stand die Erwartung als Zahlwort im Kommentar und wurde von
# dort gelesen. Der Gedanke war richtig -- eine Zahl, die nur im Messgeraet steht,
# kann im Text still falsch werden -- und die Ausfuehrung trug ihn nicht: Der
# Riegel zaehlt einen Bestand, der seinen eigenen Quelltext enthaelt, also
# veraltete jede Abschrift mit dem naechsten Commit, sechsmal hintereinander.
#
# Seit Paket 0278 traegt keine Pruefung dieses Teils eine abgeschriebene Zahl.
# Was hier steht, sind Beziehungen: eine Gleichheit, ein Unterschied, eine
# Zuordnung -- und **beide Seiten jeder Beziehung erhebt dieser Aufruf selbst**,
# aus Laeufen, die wenige Sekunden auseinander ueber denselben Baum gehen.
# Gelesen wird aus dem Kommentar nur noch der **Satz**, der die Beziehung
# behauptet; verschwindet er, meldet `gelesen()` das. Damit kann eine Pruefung
# hier nur noch aus zwei Gruenden rot werden: Der Satz ist weg, oder er ist
# falsch. Nicht mehr: Der Baum ist inzwischen ein anderer.
# ---------------------------------------------------------------------------


def flach(text):
    """Kommentarkoepfe und Zeilenumbrueche weg -- eine Aussage, die ueber vier
    Zeilen laeuft, soll sich in einem Muster fassen lassen."""
    ohne = re.sub(r"(?m)^\s*//[!/]?", " ", text)
    return re.sub(r"\s+", " ", ohne)


def gelesen(text, muster, was):
    t = re.search(muster, flach(text))
    if not t:
        melde("Im Quelltext steht keine Aussage der Form, die %s traegt -- "
              "entweder ist sie geloescht oder umformuliert worden. Ohne sie "
              "misst dieser Riegel nichts." % was)
        return None
    return t


def messe_ohne_marken(text):
    """Der Mutant `ohne-marken-rein`, einmal gebaut und einmal gelaufen.

    Getrennt vom Urteil, weil dieselbe Messung zweimal beurteilt wird: einmal
    gegen den ausgelieferten Riegel (die Pruefung) und einmal gegen sich selbst
    (die Gegenprobe). Zwei Uebersetzungen desselben Wortlauts waeren derselbe
    Nachweis zum doppelten Preis.

    Zurueck kommen: Rueckgabewert, die drei Zahlen des Bestands unter der
    Mutation, die Zahl der gemeldeten Stellen, die davon im eigenen Quelltext und
    deren Verteilung ueber Kopfkommentar und Falltabellen.
    """
    pfad = bauen(mutant("ohne-marken-rein"), "ohne_marken_rein", True)
    code, aus, _ = laufen(pfad)
    zahlen = drei(aus, "ohne-marken-rein")
    stellen = re.findall(r"zitierend: (\S+?):(\d+)", aus)
    eigen = [int(n) for d, n in stellen
             if d.endswith("werkzeuge/belegstellen/belegstellen_riegel.cpp")]
    verteilung = einordnen(text, eigen)
    print("B1 ohne-marken-rein: Code %d, %d Zitate, %d aufgeloest, %d "
          "uebergangen; %d Stellen zu Unrecht, davon %d im eigenen Quelltext %s"
          % ((code,) + zahlen + (len(stellen), len(eigen), verteilung)))
    return code, zahlen, len(stellen), len(eigen), verteilung


def pruefe_angabe1(text, grund, mess, wobei):
    """Angabe 1: drei Beziehungen zwischen dem ausgelieferten Riegel und dem
    Mutanten `ohne-marken-rein`. Keine traegt eine abgeschriebene Zahl.

    `grund` sind die drei Zahlen des ausgelieferten Riegels aus Teil A, `mess`
    die Messung des Mutanten -- beide aus diesem Aufruf, ueber denselben Baum.

    Die drei Beziehungen, in der Reihenfolge der drei Halbsaetze im Kopf:

      1. *Jede dieser Stellen meldet er als unaufgeloestes Zitat.* Die Zahl der
         gemeldeten Stellen ist die Zahl der Zitate, die er nicht aufloest.
      2. *Aufgeloest wird keine einzige davon.* Er loest genauso viele auf wie
         der unveraenderte Riegel -- was er zusaetzlich faengt, bleibt offen.
      3. *Zitate wie uebergangene Fundstellen werden dabei mehr.* Beide Zahlen
         steigen. Steigt eine nicht, misst dieser Stand nichts mehr: Entweder
         traegt der Bestand die Form nicht mehr, oder die Trennung ist aus dem
         ausgelieferten Riegel verschwunden. Beides gehoert gemeldet.

    Keine der drei bricht, wenn der Riegel aus fremdem Grund rot ist: Verglichen
    werden nur Zahlen desselben Laufs mit Zahlen desselben Laufs.
    """
    _code, zahlen, stellen, _eigen, verteilung = mess
    if gelesen(text,
               r"\*\*Jede dieser Stellen meldet er als unaufgeloestes Zitat; "
               r"aufgeloest wird keine einzige davon, und Zitate wie "
               r"uebergangene Fundstellen werden dabei mehr\.\*\*",
               "Angabe 1"):
        if stellen != zahlen[0] - zahlen[1]:
            melde("%s: Der Mutant meldet %d Stellen, laesst aber %d Zitate "
                  "unaufgeloest (%d von %d). Der erste Halbsatz sagt, das sei "
                  "dieselbe Menge."
                  % (wobei, stellen, zahlen[0] - zahlen[1], zahlen[1],
                     zahlen[0]))
        if zahlen[1] != grund[1]:
            melde("%s: Der Mutant loest %d Zitate auf, der unveraenderte Riegel "
                  "%d. Der zweite Halbsatz sagt, keine der zu Unrecht "
                  "gefangenen Stellen werde aufgeloest."
                  % (wobei, zahlen[1], grund[1]))
        if zahlen[0] <= grund[0] or zahlen[2] <= grund[2]:
            melde("%s: Der Mutant nennt %d Zitate und %d uebergangene "
                  "Fundstellen, der unveraenderte Riegel %d und %d -- mehr "
                  "werden sie damit nicht. Entweder traegt der Bestand die Form "
                  "nicht mehr, oder die Trennung ist aus dem ausgelieferten "
                  "Riegel verschwunden; gemessen wird so oder so nichts mehr."
                  % (wobei, zahlen[0], zahlen[2], grund[0], grund[2]))
    if verteilung.get("sonst"):
        melde("%s: %d Selbsttreffer liegen weder im Kopfkommentar noch in einer "
              "genannten Falltabelle -- die Momentaufnahme im Kopf zaehlt sie "
              "nicht auf." % (wobei, verteilung["sonst"]))


def einordnen(text, nummern):
    """Wo im eigenen Quelltext eine Fundstelle liegt: im Kopfkommentar oder in
    welcher Falltabelle. Die Grenzen kommen aus dem Text, nicht aus einer Liste
    -- eine Tabelle, die dazukommt, faellt sonst still unter `sonst`."""
    zeilen = text.split("\n")
    kopfende = 1
    for i, z in enumerate(zeilen):
        if z.startswith("//!"):
            kopfende = i + 1
    grenzen = []
    for m in re.finditer(r"(?m)^constexpr std::array<\w+, \d+> (\w+FAELLE) = "
                         r"\{\{$", text):
        von = text[:m.start()].count("\n") + 1
        bis = von + text[m.start():].index("\n}};")
        bis = text[:m.start() + text[m.start():].index("\n}};")].count("\n") + 1
        grenzen.append((von, bis, m.group(1)))
    aus = {}
    for n in nummern:
        wo = "Kopf" if n <= kopfende else "sonst"
        for von, bis, name in grenzen:
            if von <= n <= bis:
                wo = name
        aus[wo] = aus.get(wo, 0) + 1
    return aus


def messe_rechts_ohne_satzgrenze():
    """Der Mutant `rechts-ohne-satzgrenze-rein`, zweimal gebaut und zweimal
    gelaufen: entschaerft fuer die drei Zahlen, scharf fuer den Selbsttest.

    Beide werden gebraucht. Entschaerft laeuft er bis zum Bestand durch und nennt
    Zahlen; scharf bricht er an der Falltabelle ab und nennt den Fall, der die
    Regel traegt. Ein Lauf allein gibt immer nur eines von beiden.
    """
    frei = bauen(mutant("rechts-ohne-satzgrenze-rein"), "rosg_frei", True)
    code, aus, _ = laufen(frei)
    m = drei(aus, "rechts-ohne-satzgrenze-rein")
    print("B2 rechts-ohne-satzgrenze-rein (entschaerft): Code %d, %d Zitate, "
          "%d aufgeloest, %d uebergangen" % ((code,) + m))

    roh = bauen(mutant("rechts-ohne-satzgrenze-rein"), "rosg_roh", False)
    code_roh, _, stderr = laufen(roh)
    zeilen = [z for z in stderr.splitlines() if z.startswith("Selbsttest")]
    print("B2 rechts-ohne-satzgrenze-rein (scharf): Code %d, %d Meldung(en)"
          % (code_roh, len(zeilen)))
    for z in zeilen:
        print("     " + z)
    return m, code_roh, zeilen


def pruefe_angabe2(text, grund, m, wobei):
    """Angabe 2: der Mutant bewegt den Bestand nicht.

    Eine Gleichheit zwischen zwei Laeufen desselben Aufrufs, ohne jede Zahl im
    Text. Bis zum 2026-09-08 stand die Aussage als Abschrift da -- `41 Zitate,
    41 aufgeloest, 53 uebergangene Fundstellen, die Summe 94` --, und sie war am
    naechsten Tag falsch, waehrend die Gleichheit, die sie meinte, weiter galt.

    Rot wird sie an dem Tag, an dem der Bestand wieder eine Stelle traegt, an der
    die Satzgrenze wirkt. Dass sie das merken wuerde, weist die Gegenprobe nach:
    Dort steht in `m` der Mutant `ohne-marken-rein`, der den Bestand
    nachweislich bewegt.
    """
    if gelesen(text,
               r"Derselbe Mutant nennt \*\*genau dieselben drei Zahlen wie der "
               r"unveraenderte Riegel\*\*", "Angabe 2"):
        if m != grund:
            melde("%s: Der Mutant nennt %s, der unveraenderte Riegel %s. Der "
                  "Kopf sagt, es seien genau dieselben drei Zahlen."
                  % (wobei, m, grund))


def pruefe_fall6(text, code, zeilen, wobei):
    """Die Fallangabe von Angabe 2: welcher Selbsttestfall die Regel traegt.

    Das ist keine Zahl des Bestands, sondern eine ueber diese Datei selbst -- die
    Nummer eines Falls in einer Tabelle, die hier steht. Sie veraltet nicht mit
    fremden Commits, sondern nur, wenn jemand die Tabelle umstellt, und dann ist
    Rot die richtige Antwort. Sie bleibt deshalb geprueft.
    """
    f = gelesen(text, r"heute allein an Fall (\d+) in `(\w+)`\. Der Mutant "
                      r"`([\w-]+)` laesst ihn reissen und bricht mit Code (\d+) "
                      r"ab: (.*?)\.", "die Fallangabe von Angabe 2")
    if not f:
        return
    if int(f.group(4)) != code:
        melde("%s: Der Kopf nennt Code %s, gemessen ist %d."
              % (wobei, f.group(4), code))
    # `ABSTANDSFAELLE` -> `Abstand`: der Selbsttest nennt den Fall im
    # Singular, die Tabelle im Plural mit Fugen-s.
    erwartet = "Selbsttest %s %s:" % (
        f.group(2).removesuffix("FAELLE").rstrip("S").capitalize(),
        f.group(1))
    if len(zeilen) != 1 or not zeilen[0].startswith(erwartet):
        melde("%s: Der Kopf nennt Fall %s in `%s` als den einzigen, der "
              "reisst (%r). Gerissen sind: %s"
              % (wobei, f.group(1), f.group(2), erwartet, zeilen or "keiner"))
    elif f.group(5).replace("`", "") not in zeilen[0]:
        melde("%s: Der Kopf druckt den Wortlaut der Meldung ab; er lautet heute "
              "anders: %s" % (wobei, zeilen[0]))


def teil_b3(text):
    """Angabe 3: der als historisch ausgewiesene Fall in NAMENSFAELLE traegt
    die Nummer, die der Kopf ueber der Tabelle nennt."""
    anfang = text.index("NAMENSFAELLE = {{")
    ende = text.index("}};", anfang)
    tabelle = text[anfang:ende]
    # Ein Fall beginnt am Zeilenanfang mit `    {"` -- die Fortsetzungszeilen
    # einer Zeichenkette tun das nicht.
    starts = [m.start() for m in re.finditer(r"\n    \{\"", tabelle)]
    hist = [i + 1 for i, s in enumerate(starts)
            if "**historisch**" in tabelle[s:(starts[i + 1]
                                              if i + 1 < len(starts)
                                              else len(tabelle))]]
    genannt = re.search(r"\*\*Der (\w+) Herkunftshinweis ist historisch", text)
    wort = {"erste": 1, "zweite": 2, "dritte": 3, "vierte": 4, "fuenfte": 5,
            "sechste": 6, "siebte": 7, "achte": 8}
    print("B3 NAMENSFAELLE: %d Faelle, historisch ausgewiesen ist Nummer %s; "
          "der Kopf nennt %s" % (len(starts), hist,
                                 genannt.group(1) if genannt else "nichts"))
    if len(hist) != 1:
        melde("Genau ein Fall soll als historisch ausgewiesen sein, gefunden: %s"
              % hist)
    elif not genannt:
        melde("Der Kopf ueber NAMENSFAELLE nennt keinen historischen Fall mehr.")
    elif wort.get(genannt.group(1)) != hist[0]:
        melde("Der Kopf nennt den %s Fall, historisch ausgewiesen ist der %d."
              % (genannt.group(1), hist[0]))
    # Und der Satz davor darf ihm nicht widersprechen. Der Wortlaut steht ueber
    # zwei Zeilen und traegt dazwischen den Kommentarkopf -- deshalb `\s+//\s*`
    # statt eines Leerzeichens.
    if re.search(r"der achte ist aus einem echten(\s+//)?\s+Arbeitspaket "
                 r"abgewandelt", text) is None:
        melde("Der Satz ueber den achten Fall ist verschwunden -- die "
              "Widerspruchsfreiheit ist damit nicht mehr geprueft.")
    elif genannt and wort.get(genannt.group(1)) == 8:
        melde("Der Kopf nennt den achten Fall zugleich historisch und "
              "abgewandelt -- genau der Widerspruch, den 0115 aufloest.")


# ---------------------------------------------------------------------------
# Die Gegenprobe -- ein Riegel, der nie rot wird, prueft nichts
#
# Bis zum 2026-09-08 lief sie gegen den Wortlaut **vor** der Berichtigung. Das
# traegt seit Paket 0189 nicht mehr: Der Vorfassungsstand wandert mit, und damit
# ist die alte Fassung nur noch in den Angaben falsch, die das jeweils letzte
# Paket angefasst hat. Angabe 3 stand am 2026-09-08 in beiden Fassungen richtig
# da -- ihre Gegenprobe waere lautlos gruen geworden und haette von da an nichts
# mehr geprueft. Ein Rotnachweis, der davon abhaengt, was zufaellig im vorigen
# Commit stand, ist kein Nachweis.
#
# **Seit Paket 0278 gibt es zwei Sorten Gegenprobe, und die Sorte folgt aus dem,
# was die Pruefung liest.** Wo im Kommentar noch eine Zahl steht, wird die Zahl
# verstellt; wo nur noch ein Satz ueber eine Beziehung steht, hilft das nichts --
# den Satz zu loeschen belegt bloss, dass `gelesen()` ihn sucht. Verfaelscht wird
# dort deshalb der **Quelltext**, gegen den gemessen wird:
#
#   * *Angabe 1* -- der ausgelieferte Riegel wird durch den Mutanten
#     `ohne-marken-rein` ersetzt. Dann sind Riegel und Mutant dieselbe Fassung,
#     Zitate und uebergangene Fundstellen werden nicht mehr, und der dritte
#     Halbsatz im Kopf ist falsch. Die Pruefung muss das melden.
#   * *Angabe 2* -- an die Stelle des Mutanten, der den Bestand nicht bewegt,
#     tritt `ohne-marken-rein`, der ihn nachweislich bewegt. Die behauptete
#     Gleichheit ist damit falsch, und die Pruefung muss es merken.
#   * *die Fallangabe* und *Angabe 3* tragen weiter je eine Zahl bzw. ein
#     Zahlwort ueber diese Datei selbst. Dort bleibt es bei der Verstellung im
#     Text, mit einer Nadel, die die heutige Zahl **nicht** im Muster traegt,
#     sondern eine Gruppe um sie herum -- eine Nadel mit der Zahl darin waere
#     nach der naechsten Aenderung stumpf, und eine stumpfe Nadel liesse die
#     Gegenprobe still bestehen.
#
# Keine der vier braucht eine eigene Uebersetzung: Alle vier beurteilen Messungen
# neu, die schon vorliegen.
# ---------------------------------------------------------------------------
def verstellen(text, muster, anders, was):
    """Genau eine Angabe im Rohtext um einen Schritt verstellen.

    Am Rohtext und nicht ueber `flach`, weil das Ergebnis wieder Quelltext sein
    muss. Trifft die Nadel nicht genau einmal, endet der Lauf: Eine Nadel ins
    Leere ginge sonst als bestandene Gegenprobe durch.
    """
    treffer = list(re.finditer(muster, text))
    if len(treffer) != 1:
        raise SystemExit(
            "Die Nadel der Gegenprobe zu %s trifft %d mal statt genau einmal. "
            "Die Angabe ist umgeschrieben worden; ihre Rotfaehigkeit ist damit "
            "nicht mehr geprueft, und gemessen wird nichts, bis die Nadel "
            "nachgezogen ist. Gesucht wurde: %s" % (was, len(treffer), muster))
    t = treffer[0]
    return text[:t.start(1)] + anders(t.group(1)) + text[t.end(1):]


VERFAELSCHUNGEN = {
    "die Fallangabe": (r"heute allein an Fall (\d+) in",
                       lambda z: str(int(z) + 1)),
    "Angabe 3": (r"\*\*Der (\w+) Herkunftshinweis ist historisch",
                 lambda w: "zweite" if w == "erste" else "erste"),
}


def gegenprobe(grund, mess, m_rosg, code_roh, zeilen):
    """Vier Rotnachweise, keiner davon mit einer eigenen Uebersetzung.

    Jeder laesst dieselbe Pruefung noch einmal laufen, mit genau einer
    verfaelschten Eingabe -- beim Quelltext oder beim Text. Alle vier muessen
    reissen. Tut es einer nicht, prueft die betreffende Pruefung nicht das, was
    ihr Name sagt, sondern laeuft nur mit.
    """
    ergebnis = []

    def nachweis(name, tun):
        vorher_fehler = len(fehler)
        tun()
        ergebnis.append((name, len(fehler) - vorher_fehler))
        del fehler[vorher_fehler:]

    # Angabe 1: der Mutant selbst als ausgelieferter Riegel. `mess[1]` sind
    # seine drei Zahlen -- steht dasselbe auf beiden Seiten, faellt der
    # Unterschied auf null, den der dritte Halbsatz behauptet.
    nachweis("Angabe 1 (Riegel := Mutant)",
             lambda: pruefe_angabe1(_neu, mess[1], mess,
                                    "Gegenprobe zu Angabe 1"))
    # Angabe 2: statt des Mutanten, der den Bestand nicht bewegt, der, der es
    # nachweislich tut. Die behauptete Gleichheit ist damit falsch.
    nachweis("Angabe 2 (Mutant := ohne-marken-rein)",
             lambda: pruefe_angabe2(_neu, grund, mess[1],
                                    "Gegenprobe zu Angabe 2"))
    # Die beiden Zahlen ueber diese Datei selbst: im Text verstellt.
    for name, pruefung in (("die Fallangabe",
                            lambda t: pruefe_fall6(t, code_roh, zeilen,
                                                   "Gegenprobe zur Fallangabe")),
                           ("Angabe 3", teil_b3)):
        muster, anders = VERFAELSCHUNGEN[name]
        verstellt = verstellen(_neu, muster, anders, name)
        nachweis(name + " (Zahl im Text verstellt)",
                 lambda t=verstellt, p=pruefung: p(t))

    print("G  Gegenprobe -- " +
          ", ".join("%s: %d Meldung(en)" % p for p in ergebnis))
    for name, zahl in ergebnis:
        if zahl == 0:
            melde("Der Rotnachweis `%s` bleibt gruen. Die zugehoerige Pruefung "
                  "misst nicht, was ihr Name sagt." % name)
    # Ein unbenutzter Wert waere hier ein stiller Fehler: `m_rosg` ist das, was
    # die regulaere Pruefung zu Angabe 2 gesehen hat, und die Gegenprobe muss
    # etwas **anderes** einsetzen, sonst wiederholt sie nur den gruenen Lauf.
    if m_rosg == mess[1]:
        melde("Die Gegenprobe zu Angabe 2 setzt dieselben Zahlen ein, die die "
              "regulaere Pruefung schon gesehen hat (%s). Sie kann damit nichts "
              "belegen -- der Mutant `ohne-marken-rein` bewegt den Bestand "
              "heute nicht mehr." % (m_rosg,))


def main():
    global _neu
    os.makedirs(TMP, exist_ok=True)
    # Zuerst die Vorfassung, beschafft und an ihre Herkunft gebunden. Was danach
    # kommt, misst gegen sie -- eine falsche Eingabe hier macht jede Zahl weiter
    # unten wertlos, und zwar ebenfalls lautlos.
    vorfassung()
    neu = lies(QUELLE)
    _neu = neu
    print("Vorhaben:    " + W)
    print("Uebersetzer: " + UEBERSETZER)
    vor = kopf()
    print("Vorfassungsstand: %s; HEAD zu Beginn: %s" % (VORFASSUNGSSTAND, vor))
    grund = teil_a(neu)
    mess = messe_ohne_marken(neu)
    pruefe_angabe1(neu, grund, mess, "Angabe 1")
    m_rosg, code_roh, zeilen = messe_rechts_ohne_satzgrenze()
    pruefe_angabe2(neu, grund, m_rosg, "Angabe 2")
    pruefe_fall6(neu, code_roh, zeilen, "die Fallangabe von Angabe 2")
    teil_b3(neu)
    print()
    gegenprobe(grund, mess, m_rosg, code_roh, zeilen)
    nach = kopf()
    print("HEAD am Ende: %s" % nach)
    if vor != nach:
        melde("Der Baum ist waehrend der Messung gewandert (%s -> %s). Die "
              "Zahlen gehoeren neu erhoben." % (vor, nach))
    # Hier stand bis zum 2026-09-08 der Abgleich zwischen dem `BEZUGSSTAND` des
    # Skripts und dem Commit, den der Kopfkommentar nannte, dazu ein Hinweis,
    # sobald HEAD von beiden abwich. Beides ist mit Paket 0278 entfallen: Der
    # Kommentar nennt keinen Commit mehr, weil er nichts mehr behauptet, was an
    # einem Commit haengt.
    #
    # Bis zum 2026-09-09 fragte die Zeile darunter, ob der Ruecktausch von Teil A
    # gegriffen hat. Getauscht wird nicht mehr, und die Frage bleibt trotzdem
    # sinnvoll -- sie faengt jetzt die fremde Hand: Ist die Quelldatei waehrend
    # der Messung eine andere geworden, sind Teil A und Teil B ueber zwei
    # verschiedene Bestaende erhoben.
    if lies(QUELLE) != neu:
        melde("Die Quelldatei hat sich waehrend der Messung geaendert. Dieser "
              "Stand schreibt sie nicht -- es war eine fremde Hand, und die "
              "Zahlen gehoeren neu erhoben.")
    # Der Arbeitsplatz wird geraeumt, sobald gemessen ist -- gleich, ob gruen
    # oder rot. Was zu sagen war, steht oben; unter `$TMPDIR` bleiben nur
    # Uebersetzungserzeugnisse. Nach einem Abbruch (SystemExit) laeuft diese
    # Zeile mit Absicht **nicht**: Dann ist der Arbeitsplatz das einzige, woran
    # sich nachsehen laesst, was schiefging.
    aufraeumen()
    if fehler:
        print("\n%d Erwartung(en) nicht erfuellt." % len(fehler))
        return 1
    print("\nAlle Erwartungen erfuellt.")
    return 0


def aufraeumen():
    shutil.rmtree(TMP, ignore_errors=True)


def einstellungen():
    """Vorhaben und Uebersetzer, beide mit Vorgabe.

    Ohne Schalter laeuft der Stand wie bisher; im Nachtlauf setzt CMake beide,
    damit hier kein zweiter Uebersetzer neben dem des Kastens steht.
    """
    global W, QUELLE, REPO, UEBERSETZER
    zerleger = argparse.ArgumentParser(add_help=True)
    zerleger.add_argument("--vorhaben", default=VORHABEN_VORGABE)
    zerleger.add_argument("--uebersetzer", default=UEBERSETZER_VORGABE)
    wahl = zerleger.parse_args()
    W = os.path.abspath(wahl.vorhaben).rstrip("/")
    QUELLE = W + "/werkzeuge/belegstellen/belegstellen_riegel.cpp"
    REPO = os.path.dirname(os.path.dirname(W))
    UEBERSETZER = wahl.uebersetzer


einstellungen()
sys.exit(main())
