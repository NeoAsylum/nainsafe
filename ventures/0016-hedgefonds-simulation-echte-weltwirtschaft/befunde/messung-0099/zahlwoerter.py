#!/usr/bin/env python3
# Die drei Zahlwoerter im Kopf von `daten/reihen.toml`, nachgezaehlt statt geglaubt.
#
# Paket 0099 hat die Zaehlung gebaut, Paket 0188 die Vergleichsseite. Die Zaehlung
# selbst ist unveraendert -- sie ist seit 0099 zweimal gegen historische Staende
# bestaetigt, und was bestaetigt ist, wird nicht neu geschrieben.
#
# ZWEI BETRIEBSARTEN
#
#   zahlwoerter.py <blob-sha|-> <pfad>    Bericht, wie seit Paket 0099. Druckt Zahlen,
#                                         urteilt nicht, gibt 0.
#   zahlwoerter.py --riegel <wurzel>      Riegel. Haelt drei Behauptungen des
#                                         Kopfkommentars gegen drei Zaehlungen
#                                         derselben Datei und gibt 0, 1 oder 2.
#
# Die alte Form bleibt Zeichen fuer Zeichen dieselbe: Zwei Abnahmen nennen sie im
# Wortlaut, und ein Aufruf, der gestern eine Ausgabe hatte, hat heute dieselbe.
#
# WARUM ES DIESEN RIEGEL GIBT
#
# Die Zahl im Kopf ist binnen zweier Tage zweimal falsch geworden, beide Male ohne dass
# jemand die Zaehlung angefasst haette: Ein Paket schrieb einen Nachtrag in
# `pruefweg.toml_geprueft`, der eine Datei beim Namen nennt, und trug die gezaehlte
# Zeichenfolge damit in einen weiteren Blattwert. Beide Male hat die Zahl einen Lauf
# ueberlebt, in dem sie schon falsch war, und beide Male hat sie ein zufaellig
# danebenstehender Lauf gefunden. Das Werkzeug lag die ganze Zeit im Baum und ist nicht
# gelaufen -- weil es ein Bericht war und keine Probe.
#
# DIE DREI BEHAUPTUNGEN, UND WORAN SIE ERKANNT WERDEN
#
#   1. `vorlagen`   -- "Der Stand der <n> Vorlagen"
#                      gegen die Zahl der Schluessel in [datei.vorlagen].
#   2. `nennung`    -- "genannt wird er in <n> Blattwerten"
#                      gegen die Zahl der Blattwerte mit der Marke.
#   3. `zerlegung`  -- "Diese <n> zerfallen ohne Rest in <a> plus <b> plus <c>"
#                      gegen die Aufteilung derselben Menge in `beleg`,
#                      Vorlagenschluessel und Rest.
#
# WAS DIE GEPRUEFTEN STELLEN VON DEN HISTORISCHEN TRENNT
#
# Der Kopfkommentar fuehrt dieselben Zahlwoerter noch ein zweites Mal, in Absaetzen, die
# ausdruecklich ueberholt sind: "Paket 0099 hat hier am 2026-09-05 **sieben** und **zwei
# plus eins plus vier** gemessen", "Bis Paket 0099 stand hier fuenf", "der fuenf
# Vorlagen, die vor Paket 0099 in dieser Tabelle standen". Diese Saetze duerfen und
# sollen falsch aussehen -- sie berichten, was einmal galt. Ein Riegel, der sie
# mitpruefte, waere ein Dauerbefund, und ein Dauerbefund wird abgeschaltet.
#
# Getrennt wird an der **Wortfolge des behauptenden Satzes**, nicht an Auszeichnung und
# nicht an der Zeilennummer. Die drei Muster oben nennen je vier bis neun Woerter in
# fester Folge; jeder historische Satz bricht die Folge an einer festen Stelle: er sagt
# "hat hier ... gemessen", "stand hier", "Zerlegung <a> plus <b> plus <c>" oder "zerlegt
# in <a> plus <b> plus <c>" -- nie "zerfallen ohne Rest in", nie "genannt wird er in",
# nie "Stand der <n> Vorlagen". Fettauszeichnung taugt nicht zur Trennung: Die
# historische Stelle traegt sie genauso. Der Selbsttest unten nagelt beide Richtungen
# fest, jede an dem Satz, wie er in der Datei steht.
#
# Was das kostet, ausgeschrieben: Wer den behauptenden Satz umformuliert, verliert den
# Riegel nicht still, sondern laut -- ein Anker, der nicht genau einmal vorkommt, ist
# Code 2 und kein gruener Lauf. Das ist die Richtung, in der ein Messgeraet irren darf.
#
# DIE ZAHLWOERTER WERDEN GERECHNET, NICHT AUFGEZAEHLT
#
# Uebernommen aus dem Zahlwortriegel des Pakets 0180, samt seiner tragenden Regel: `ein`
# und `eine` sind zugleich unbestimmter Artikel und Kardinalzahl, und nur ein bestimmter
# Artikel unmittelbar davor macht aus dem Begleiter eine Zahl. Zusammengesetzte
# Zahlwoerter werden zerlegt (`<einer>und<zehner>`), damit ein Wort, das heute noch
# nicht gebraucht wird, morgen trotzdem erkannt ist.
#
# **Die Grenze, die daraus folgt:** Faellt eine der drei Zaehlungen je auf eins, hiesse
# der Satz "in einem Blattwert", und dort steht kein bestimmter Artikel davor. Der Anker
# faende nichts und der Lauf gaebe Code 2 -- laut und nicht still. Der Selbsttest haelt
# den Fall fest, damit ihn niemand fuer eine Deckung haelt.
#
# DER SELBSTTEST, DER BEI JEDEM AUFRUF MITLAEUFT
#
# Ein Test, der nie fehlschlaegt, prueft nichts. Drei Tafeln laufen vor dem Urteil, und
# eine verfehlte bricht den Lauf mit Code 2 ab:
#
#   Tafel 1 -- die Zahlwoerter selbst.
#   Tafel 2 -- die Trennung: je ein historischer und ein lebender Satz im Wortlaut der
#              Datei, der eine ohne Anker, der andere mit.
#   Tafel 3 -- die Verdrahtung, an drei Mutanten des wirklichen Standes:
#              (a) ein Zahlwort im Kopf verstellt -- an der gemessenen Stelle und nicht
#                  per Textsuche, also auch dann, wenn die Stelle wandert;
#              (b) ein Blattwert mit der Marke ergaenzt, ohne das Zahlwort nachzuziehen;
#              (c) der festgenagelte Blob nach Paket 0126, wo sieben steht und acht
#                  gezaehlt sind, ueber `git cat-file blob` und ohne Zwischendatei.
#
# Tafel 3 urteilt **gegen den Bestand von heute** und nicht gegen eine feste Sollzahl:
# Die Erwartung lautet "der Mutant zaehlt eins mehr als der Bestand", nicht "der Mutant
# zaehlt neun". Eine feste Zahl hier verfiele in Stunden.
#
# Der Preis von (c): Ohne `.git` neben dem Vorhaben gibt es diesen Nachweis nicht, und
# der Lauf endet mit Code 2 statt still ohne ihn. In einem Baum aus `git archive` ist
# das kein Fehlalarm, sondern die richtige Meldung -- dort ist der Riegel stumpf.
#
# DIE DREI RUECKGABEWERTE
#
#   2 -- der Selbsttest ist verfehlt, die Datei fehlt, sie ist kein gueltiges TOML, ein
#        Anker kommt nicht genau einmal vor, oder der Blob ist nicht zu holen. Kein
#        gruener Lauf, sondern ein Messgeraet ohne Messung.
#   1 -- eine Behauptung weicht von ihrer Zaehlung ab.
#   0 -- alle drei decken sich.
import pathlib
import subprocess
import sys
import tomllib

MARKE = "einheitenbefund" + "-pwt-baci"

#: Der Pruefling, relativ zur Wurzel des Vorhabens. Die Wurzel kommt von CMake und
#: nicht aus diesem Programm -- ein eingebauter Pfad liefe nur auf einem Rechner.
PRUEFLING = "daten/reihen.toml"

#: Der Stand nach Paket 0126: dort steht sieben und gezaehlt sind acht. Ein
#: Bezugsstand, den kein spaeterer Lauf mehr bewegen kann.
BLOB_NACH_0126 = "d18ca197812364ac65dba58dd67a7851339ddfe7"


# ---------------------------------------------------------------------------
# Die Zaehlung -- unveraendert seit Paket 0099
# ---------------------------------------------------------------------------


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


def zaehle(baum):
    """Die drei Groessen, gegen die der Kopfkommentar gehalten wird."""
    blaetter = dict(flach(baum))
    treffer = {k: v for k, v in blaetter.items() if isinstance(v, str) and MARKE in v}
    belege = sorted(k for k in treffer if k[-1] == "beleg")
    vorlage = sorted(k for k in treffer if k[:2] == ("datei", "vorlagen"))
    rest = sorted(set(treffer) - set(belege) - set(vorlage))
    doppelt = ((set(belege) & set(vorlage)) | (set(belege) & set(rest))
               | (set(vorlage) & set(rest)))
    return {
        "vorlagen": len(baum["datei"]["vorlagen"]),
        "gesamt": len(treffer),
        "belege": len(belege),
        "vorlage": len(vorlage),
        "rest": len(rest),
        "doppelt": sorted(".".join(k) for k in doppelt),
        "schluessel": sorted(".".join(k) for k in treffer),
    }


# ---------------------------------------------------------------------------
# Zahlwoerter -- gerechnet statt aufgezaehlt (Bauart aus Paket 0180)
# ---------------------------------------------------------------------------

GRUNDZAHL = ["null", "eins", "zwei", "drei", "vier", "fuenf", "sechs", "sieben",
             "acht", "neun", "zehn", "elf", "zwoelf", "dreizehn", "vierzehn",
             "fuenfzehn", "sechzehn", "siebzehn", "achtzehn", "neunzehn"]
ZEHNER = ["zwanzig", "dreissig", "vierzig", "fuenfzig",
          "sechzig", "siebzig", "achtzig", "neunzig"]
#: Die Einerform, wie sie in einer Zusammensetzung steht: `ein` und nicht `eins`.
EINERFORM = ["", "ein", "zwei", "drei", "vier", "fuenf", "sechs", "sieben", "acht",
             "neun"]
#: Die Formen, in denen die Kardinalzahl eins mit dem unbestimmten Artikel
#: zusammenfaellt. Sie sind der ganze Grund fuer die Artikelregel.
MEHRDEUTIG = ("ein", "eine", "einer", "eines", "einem", "einen")
ARTIKEL_BESTIMMT = ("die", "der", "das", "den", "dem", "des")


def kardinalwert(wort):
    """Der Wert einer Kardinalzahl, oder None. Zusammensetzungen werden zerlegt."""
    k = wort.lower()
    if k in GRUNDZAHL:
        return GRUNDZAHL.index(k)
    if k in MEHRDEUTIG:
        return 1
    if k in ZEHNER:
        return 20 + ZEHNER.index(k) * 10
    fuge = k.find("und")
    if fuge <= 0:
        return None
    links, rechts = k[:fuge], k[fuge + 3:]
    if links in EINERFORM[1:] and rechts in ZEHNER:
        return 20 + ZEHNER.index(rechts) * 10 + EINERFORM.index(links)
    return None


# ---------------------------------------------------------------------------
# Die Zerlegung des Kommentars in Woerter und Bloecke
# ---------------------------------------------------------------------------


class Wort:
    """Ein Wort mit seiner Stelle im **rohen** Text. Die Stelle ist keine Zugabe: An ihr
    haengt die Zeilennummer jeder Meldung und der Eingriff des Mutanten."""

    __slots__ = ("text", "zeile", "a", "e")

    def __init__(self, text, zeile, a, e):
        self.text, self.zeile, self.a, self.e = text, zeile, a, e


def ist_buchstabe(c):
    return ("a" <= c <= "z") or ("A" <= c <= "Z")


def worte_der_zeile(roh, zeile, ab):
    """Woerter sind maximale Laeufe lateinischer Buchstaben. Alles andere trennt --
    Auszeichnung, Satzzeichen, Ziffern, Akzente. Damit zerfaellt `**acht**` in sein
    blosses Wort, und die Stelle darin zeigt auf die vier Buchstaben."""
    worte = []
    i = ab
    while i < len(roh):
        if not ist_buchstabe(roh[i]):
            i += 1
            continue
        a = i
        while i < len(roh) and ist_buchstabe(roh[i]):
            i += 1
        worte.append(Wort(roh[a:i], zeile, a, i))
    return worte


def bloecke_von(zeilen):
    """Ein Block ist ein Lauf zusammenhaengender Kommentarzeilen, die je mindestens ein
    Wort tragen. Zusammengezogen wird ueber die Zeilengrenze, weil der Kopf seine Saetze
    mitten in der Wortgruppe umbricht -- `in **acht**` steht auf der einen Zeile,
    `Blattwerten` auf der naechsten. Getrennt wird an jeder Codezeile, an der leeren
    Kommentarzeile und an der Strichzeile; ohne diese Trennung koennten zwei Saetze aus
    verschiedenen Absaetzen eine Wortfolge bilden, die keiner von beiden sagt.

    Gelesen werden nur ganzzeilige Kommentare. Ein `#` hinter einem Wert waere in TOML
    kein Kommentar, wenn es in einer Zeichenkette steht, und diese Datei ist voll davon.
    """
    bloecke = []
    laufend = []
    for i, roh in enumerate(zeilen):
        v = 0
        while v < len(roh) and roh[v] in " \t":
            v += 1
        worte = []
        if v < len(roh) and roh[v] == "#":
            while v < len(roh) and roh[v] == "#":
                v += 1
            worte = worte_der_zeile(roh, i, v)
        if not worte:
            if laufend:
                bloecke.append(laufend)
                laufend = []
            continue
        laufend.extend(worte)
    if laufend:
        bloecke.append(laufend)
    return bloecke


# ---------------------------------------------------------------------------
# Die drei Anker
# ---------------------------------------------------------------------------

#: Das Musterglied "hier steht ein Zahlwort". Ein eigenes Objekt und keine Zeichenkette:
#: Ein Muster wird gliedweise auf Gleichheit geprueft, und ein Wort namens `<zahl>` gibt
#: es zwar nicht -- aber eine Marke, die mit einem Wort verwechselbar ist, ist eine
#: Falle, die erst auffaellt, wenn jemand sie stellt.
ZAHL = object()

MUSTER = {
    "vorlagen": [("stand",), ("der",), ZAHL, ("vorlagen",)],
    "nennung": [("genannt",), ("wird",), ("er",), ("in",), ZAHL,
                ("blattwerten", "blattwert")],
    "zerlegung": [("zerfallen",), ("ohne",), ("rest",), ("in",), ZAHL, ("plus",), ZAHL,
                  ("plus",), ZAHL],
}


def zahlwert_an(worte, p):
    """Der Wert des Zahlworts an der Stelle p -- oder None, wenn dort keine Zahl steht.

    Die tragende Regel des Pakets 0180: Ist die Form mehrdeutig (`ein`, `eine`, ...),
    zaehlt sie nur mit bestimmtem Artikel unmittelbar davor. Ohne ihn ist sie der
    unbestimmte Artikel und behauptet keine Anzahl."""
    wert = kardinalwert(worte[p].text)
    if wert is None:
        return None
    if worte[p].text.lower() in MEHRDEUTIG:
        if p == 0 or worte[p - 1].text.lower() not in ARTIKEL_BESTIMMT:
            return None
    return wert


def finde_folge(worte, muster):
    """Alle Stellen, an denen die Wortfolge passt, samt der Zahlen darin."""
    treffer = []
    for s in range(len(worte) - len(muster) + 1):
        zahlen = []
        passt = True
        for k, glied in enumerate(muster):
            p = s + k
            if glied is ZAHL:
                wert = zahlwert_an(worte, p)
                if wert is None:
                    passt = False
                    break
                zahlen.append((p, wert))
            elif worte[p].text.lower() not in glied:
                passt = False
                break
        if passt:
            treffer.append((s, zahlen))
    return treffer


def anker_finden(rohtext):
    """Je Anker die Liste seiner Fundstellen. Ohne TOML -- die Trennung von lebendem und
    historischem Satz haengt am Text und soll auch an einem Bruchstueck pruefbar sein."""
    gefunden = {name: [] for name in MUSTER}
    for block in bloecke_von(rohtext.split("\n")):
        for name, muster in MUSTER.items():
            for s, zahlen in finde_folge(block, muster):
                stelle = {"block": block, "start": s, "zahlen": zahlen, "diese": None}
                if name == "zerlegung" and s >= 2 and block[s - 2].text.lower() == "diese":
                    wert = zahlwert_an(block, s - 1)
                    if wert is not None:
                        stelle["diese"] = (s - 1, wert)
                gefunden[name].append(stelle)
    return gefunden


def zahlwort_von(stelle, nr=0):
    p, wert = stelle["zahlen"][nr]
    return stelle["block"][p], wert


# ---------------------------------------------------------------------------
# Die Pruefung -- die Verdrahtung von Ankern und Zaehlung
# ---------------------------------------------------------------------------


class Ergebnis:
    def __init__(self):
        self.zaehlung = None
        self.stellen = {}
        self.fehlend = []      # Anker, die nicht genau einmal vorkommen
        self.befunde = []      # Abweichungen, je eine Zeile
        self.abweichend = set()


def pruefe(rohtext):
    """Drei Behauptungen gegen drei Zaehlungen derselben Bytes."""
    e = Ergebnis()
    e.zaehlung = zaehle(tomllib.loads(rohtext))
    gefunden = anker_finden(rohtext)
    for name in MUSTER:
        if len(gefunden[name]) != 1:
            e.fehlend.append("%s: %d Fundstellen statt genau einer"
                             % (name, len(gefunden[name])))
            continue
        e.stellen[name] = gefunden[name][0]

    def melde(name, wort, genannt, gezaehlt, was):
        if genannt == gezaehlt:
            return
        e.abweichend.add(name)
        e.befunde.append("Zeile %d: '%s' nennt %d, gezaehlt sind %d (%s)"
                         % (wort.zeile + 1, wort.text, genannt, gezaehlt, was))

    if "vorlagen" in e.stellen:
        wort, genannt = zahlwort_von(e.stellen["vorlagen"])
        melde("vorlagen", wort, genannt, e.zaehlung["vorlagen"],
              "Schluessel in [datei.vorlagen]")
    if "nennung" in e.stellen:
        wort, genannt = zahlwort_von(e.stellen["nennung"])
        melde("nennung", wort, genannt, e.zaehlung["gesamt"], "Blattwerte mit der Marke")
    if "zerlegung" in e.stellen:
        stelle = e.stellen["zerlegung"]
        for nr, (schluessel, was) in enumerate(
                [("belege", "Blattwerte mit dem Schluessel `beleg`"),
                 ("vorlage", "Vorlagenschluessel"),
                 ("rest", "uebriger Blattwerte")]):
            wort, genannt = zahlwort_von(stelle, nr)
            melde("zerlegung", wort, genannt, e.zaehlung[schluessel], was)
        if stelle["diese"] is not None:
            p, genannt = stelle["diese"]
            melde("zerlegung", stelle["block"][p], genannt, e.zaehlung["gesamt"],
                  "Blattwerte mit der Marke")

    if e.zaehlung["doppelt"]:
        e.abweichend.add("zerlegung")
        e.befunde.append("Die drei Teile ueberschneiden sich, die Zerlegung ist also "
                         "nicht ohne Rest: %s" % ", ".join(e.zaehlung["doppelt"]))
    return e


# ---------------------------------------------------------------------------
# Selbsttest, Tafel 1: die Zahlwoerter
# ---------------------------------------------------------------------------

ZAHLFAELLE = [
    ("null", 0, "die Null ist eine Zahl und keine Fehlanzeige"),
    ("zwei", 2, "der erste Teil der heutigen Zerlegung"),
    ("fuenf", 5, "der dritte Teil der heutigen Zerlegung"),
    ("sechs", 6, "die heutige Zahl der Vorlagen"),
    ("sieben", 7, "die Zahl, die am Blob nach 0126 falsch dasteht"),
    ("acht", 8, "die heutige Gesamtzahl"),
    ("Acht", 8, "gross geschrieben am Satzanfang"),
    ("neunzehn", 19, "die letzte Grundzahl"),
    ("zwanzig", 20, "der erste volle Zehner"),
    ("einundzwanzig", 21, "zusammengesetzt, mit der Einerform ein"),
    ("dreiundfuenfzig", 53, "ein Wort, das im Bestand nicht vorkommt und trotzdem zaehlt"),
    ("neunundneunzig", 99, "die groesste zweistellige Form"),
    ("eins", 1, "die freistehende Eins"),
    ("plus", None, "das Bindewort der Zerlegung ist kein Zahlwort"),
    ("Vorlagen", None, "ein Nomen ist kein Zahlwort"),
    ("und", None, "die blosse Fuge zaehlt nicht"),
    ("undzwanzig", None, "eine Fuge am Wortanfang zaehlt nicht"),
    ("zweiundacht", None, "rechts der Fuge muss ein voller Zehner stehen"),
]

#: Satz, Stelle des geprueften Wortes im Satz, erwarteter Wert, Fallname.
ARTIKELFAELLE = [
    ("die eine Vorlagen", 1, 1, "der bestimmte Artikel macht aus dem Begleiter eine Zahl"),
    ("in eine Vorlagen", 1, None, "ohne ihn ist es der unbestimmte Artikel"),
    ("die zwei Vorlagen", 1, 2, "eine eindeutige Form braucht keinen Artikel"),
    ("eine Vorlagen", 0, None, "nichts davor, also kein Artikel"),
]


def selbsttest_zahlwoerter():
    verfehlt = 0
    for wort, erwartet, was in ZAHLFAELLE:
        ist = kardinalwert(wort)
        if ist != erwartet:
            verfehlt += 1
            sys.stderr.write("Selbsttest Zahlwort (%s): '%s' -> %r statt %r\n"
                             % (was, wort, ist, erwartet))
    for satz, stelle, erwartet, was in ARTIKELFAELLE:
        worte = worte_der_zeile("# " + satz, 0, 1)
        ist = zahlwert_an(worte, stelle)
        if ist != erwartet:
            verfehlt += 1
            sys.stderr.write("Selbsttest Artikelregel (%s): '%s' -> %r statt %r\n"
                             % (was, satz, ist, erwartet))
    return verfehlt


# ---------------------------------------------------------------------------
# Selbsttest, Tafel 2: die Trennung des lebenden vom historischen Satz
#
# Jeder Text unten steht so im Kopf von `reihen.toml`, mit seinen Umbruechen. Das ist
# der Punkt: Ein zurechtgelegter Satz bewiese die Trennung nicht.
# ---------------------------------------------------------------------------

TRENNFAELLE = [
    ("Geschichte der zweiten Zahl, historisch",
     "# Geschichte der zweiten Zahl, weil dieselbe Stelle ein zweites Mal\n"
     "# gealtert ist: Paket 0099 hat hier am 2026-09-05 **sieben** und\n"
     "# **zwei plus eins plus vier** gemessen, ohne den Rest-Eintrag\n"
     "# `toml_geprueft`.\n",
     {}),
    ("die bestaetigte alte Zaehlung, historisch",
     "# ist die alte Zaehlung mit demselben Werkzeug bestaetigt worden --\n"
     "# sieben Blattwerte, Zerlegung zwei plus eins plus vier, ohne den\n"
     "# Rest-Eintrag `toml_geprueft`.\n",
     {}),
    ("die 0065-Zaehlung, historisch",
     "# Paket 0065 hat hier \"genau einmal\" und \"acht\" gemessen, zerlegt in\n"
     "# eins plus eins plus sechs (viermal `offen`, einmal `begruendung`,\n"
     "# einmal `lang`); davor stand \"vier Pakete\" und \"viermal als `beleg`\",\n"
     "# und das war falsch.\n",
     {}),
    ("Bis Paket 0099 stand hier fuenf, historisch",
     "# unter diesem Kommentar fuehrt sechs Schluessel -- deckung, einheiten,\n"
     "# lizenz_reihen, lizenz_wdi, preisbasis, reihenliste --, maschinell aus\n"
     "# `datei.vorlagen` gelesen. Bis Paket 0099 stand hier \"fuenf\";\n"
     "# hinzugekommen ist `preisbasis`.\n",
     {}),
    ("der Rest der fuenf Vorlagen, historisch",
     "# Sie traegt den groessten offenen Rest der fuenf Vorlagen, die vor\n"
     "# Paket 0099 in dieser Tabelle standen -- gegen `preisbasis` ist der\n"
     "# Vergleich nicht nachgemessen.\n",
     {}),
    ("der Stand der Vorlagen, lebend",
     "# Der Stand der sechs Vorlagen, gegen den diese Datei geschrieben ist.\n"
     "# Aendert sich eine davon, ist diese Datei nachzuziehen.\n",
     {"vorlagen": [6]}),
    ("die Nennung ueber den Zeilenumbruch, lebend",
     "# zaehlt ab null). Ueberhaupt genannt wird er in **acht**\n"
     "# Blattwerten -- dieselbe Zeichenfolge, aber ohne Ruecksicht auf den\n"
     "# Schluessel.\n",
     {"nennung": [8]}),
    ("die Zerlegung ueber den Zeilenumbruch, lebend",
     "# Schluessel. Diese acht zerfallen ohne Rest in **zwei plus eins\n"
     "# plus fuenf**: die zwei `beleg` von eben; der Vorlagenschluessel\n"
     "# `datei.vorlagen.einheiten` in der Tabelle unter diesem Kommentar.\n",
     {"zerlegung": [2, 1, 5]}),
    ("die leere Kommentarzeile trennt",
     "# Diese acht zerfallen ohne Rest in zwei plus eins\n"
     "#\n"
     "# plus fuenf.\n",
     {}),
    ("eine Codezeile trennt",
     "# Der Stand der sechs\n"
     "reihen = 19\n"
     "# Vorlagen, gegen den diese Datei geschrieben ist.\n",
     {}),
    ("ein Kommentarzeichen in einer Zeichenkette ist kein Kommentar",
     "hinweis = \"# Der Stand der sechs Vorlagen\"\n",
     {}),
    ("die benannte Grenze: eins ohne bestimmten Artikel",
     "# Ueberhaupt genannt wird er in einem Blattwert.\n",
     {}),
]


def selbsttest_trennung():
    verfehlt = 0
    for name, text, erwartet in TRENNFAELLE:
        gefunden = anker_finden(text)
        ist = {k: [w for _, w in v[0]["zahlen"]]
               for k, v in gefunden.items() if v}
        mehrfach = [k for k, v in gefunden.items() if len(v) > 1]
        if ist != erwartet or mehrfach:
            verfehlt += 1
            sys.stderr.write("Selbsttest Trennung (%s):\n  erwartet %r\n  gefunden %r%s\n"
                             % (name, erwartet, ist,
                                "  mehrfach: %r" % mehrfach if mehrfach else ""))
    return verfehlt


# ---------------------------------------------------------------------------
# Selbsttest, Tafel 3: die Verdrahtung, an Mutanten des wirklichen Standes
#
# Der Baum von heute ist der billigste Mutant: schon da, und niemand kann ihn fuer
# zurechtgelegt halten. Verbogen wird nur im Speicher -- kein Schreiben in den
# Quellbaum, keine Zwischendatei.
# ---------------------------------------------------------------------------


def mutant_zahlwort(rohtext, ankername, ersatz):
    """Verbiegt das Zahlwort eines Ankers an seiner **gemessenen** Stelle.

    Nicht per Textsuche: Ein `replace` traefe jedes gleichlautende Wort der Datei, und
    die Stelle wandert mit jedem Paket. Die Stelle kommt aus derselben Zerlegung, die
    auch das Urteil traegt."""
    stellen = anker_finden(rohtext)[ankername]
    if len(stellen) != 1:
        return None
    wort, _ = zahlwort_von(stellen[0])
    zeilen = rohtext.split("\n")
    roh = zeilen[wort.zeile]
    zeilen[wort.zeile] = roh[:wort.a] + ersatz + roh[wort.e:]
    return "\n".join(zeilen)


def mutant_blattwert(rohtext, tafelname):
    """Ergaenzt einen Blattwert, der die Marke traegt -- ohne das Zahlwort nachzuziehen.
    Genau der Vorgang, der die Zahl zweimal falsch gemacht hat."""
    return rohtext + ("\n[%s]\nnachweis = \"Ein Blattwert, der %s nennt, ohne dass "
                      "das Zahlwort im Kopf nachgezogen waere.\"\n" % (tafelname, MARKE))


def selbsttest_verdrahtung(rohtext, bestand, wurzel):
    verfehlt = 0

    def klage(fall, text):
        sys.stderr.write("Selbsttest Verdrahtung (%s): %s\n" % (fall, text))

    # (a) Ein Zahlwort verstellt. Der Ersatz wird gewaehlt, nicht gesetzt: Er muss von
    #     der heutigen Zaehlung abweichen, und die bewegt sich.
    fall = "ein Zahlwort im Kopf verstellt"
    if "nennung" not in bestand.stellen:
        klage(fall, "der Anker `nennung` steht nicht genau einmal im Bestand")
        verfehlt += 1
    else:
        ersatz = next(w for w in ("zwei", "drei", "neunzehn")
                      if kardinalwert(w) != bestand.zaehlung["gesamt"])
        text = mutant_zahlwort(rohtext, "nennung", ersatz)
        m = pruefe(text)
        _, genannt = zahlwort_von(m.stellen["nennung"]) if "nennung" in m.stellen \
            else (None, None)
        if genannt != kardinalwert(ersatz):
            klage(fall, "der Eingriff hat nicht gegriffen: gelesen %r statt %r"
                  % (genannt, kardinalwert(ersatz)))
            verfehlt += 1
        elif "nennung" not in m.abweichend:
            klage(fall, "verstellt auf '%s', und der Riegel bleibt gruen" % ersatz)
            verfehlt += 1
        elif m.abweichend - {"nennung"} != bestand.abweichend - {"nennung"}:
            klage(fall, "rot an der falschen Stelle: %r, im Bestand %r"
                  % (sorted(m.abweichend), sorted(bestand.abweichend)))
            verfehlt += 1

    # (b) Ein Blattwert ergaenzt. Gemessen wird gegen den Bestand von heute und nicht
    #     gegen eine feste Zahl -- die verfiele in Stunden.
    fall = "ein Blattwert mit der Marke ergaenzt"
    tafelname = "selbsttest_dieser_probe"
    if tafelname in tomllib.loads(rohtext):
        klage(fall, "die Tabelle `%s` gibt es im Pruefling schon" % tafelname)
        verfehlt += 1
    else:
        m = pruefe(mutant_blattwert(rohtext, tafelname))
        gewachsen = (m.zaehlung["gesamt"] == bestand.zaehlung["gesamt"] + 1
                     and m.zaehlung["rest"] == bestand.zaehlung["rest"] + 1
                     and m.zaehlung["belege"] == bestand.zaehlung["belege"]
                     and m.zaehlung["vorlage"] == bestand.zaehlung["vorlage"])
        if not gewachsen:
            klage(fall, "die Zaehlung ist nicht um genau einen Rest-Eintrag gewachsen: "
                        "%r gegen %r" % (m.zaehlung, bestand.zaehlung))
            verfehlt += 1
        elif "nennung" not in m.abweichend or "zerlegung" not in m.abweichend:
            klage(fall, "ein Blattwert mehr, und rot sind nur %r" % sorted(m.abweichend))
            verfehlt += 1
        elif "vorlagen" in m.abweichend - bestand.abweichend:
            klage(fall, "die Zahl der Vorlagen hat sich nicht bewegt und ist trotzdem rot")
            verfehlt += 1

    # (c) Der festgenagelte Stand nach Paket 0126. Hier stehen zwei feste Zahlen, und
    #     das ist der eine Fall, in dem eine feste Sollzahl richtig ist: Der Gegenstand
    #     ist ein Blob und kann sich nicht mehr bewegen. Bei (a) und (b) waere dieselbe
    #     Zahl in Stunden verfallen -- dort wird gegen den Bestand von heute gemessen.
    fall = "der Blob nach Paket 0126"
    alt = blob_holen(wurzel, BLOB_NACH_0126)
    if isinstance(alt, str):
        klage(fall, alt)
        return verfehlt + 1
    try:
        m = pruefe(alt.decode("utf-8"))
    except (tomllib.TOMLDecodeError, KeyError, UnicodeDecodeError) as fehler:
        klage(fall, "der Blob ist nicht zu lesen: %r" % (fehler,))
        return verfehlt + 1
    if "nennung" not in m.stellen:
        klage(fall, "der Anker `nennung` steht dort nicht genau einmal -- der Wortlaut "
                    "jenes Standes ist ein anderer als angenommen: %r" % m.fehlend)
        verfehlt += 1
    else:
        _, genannt = zahlwort_von(m.stellen["nennung"])
        if (genannt, m.zaehlung["gesamt"]) != (7, 8):
            klage(fall, "erwartet genannt 7 gegen gezaehlt 8, gefunden %d gegen %d"
                  % (genannt, m.zaehlung["gesamt"]))
            verfehlt += 1
        elif "nennung" not in m.abweichend:
            klage(fall, "sieben gegen acht, und der Riegel bleibt gruen")
            verfehlt += 1
    # Die Zerlegung wird an jenem Stand nicht verlangt, sondern nur gehalten, falls sie
    # dort steht: Der Wortlaut eines fremden Standes ist keine Bedingung dieses Pakets,
    # und ein Anker, der sich in der Geschichte anders schreibt, ist kein Befund.
    if "zerlegung" in m.stellen and "zerlegung" not in m.abweichend:
        klage(fall, "die Zerlegung steht dort und wird trotzdem nicht rot")
        verfehlt += 1
    return verfehlt


def blob_holen(wurzel, sha):
    """Die Bytes eines Blobs, oder eine Klage als Zeichenkette. Ohne Zwischendatei im
    Arbeitsbaum -- was gemessen wird, soll niemand vorher anfassen koennen."""
    behaelter = wurzel.parents[1]
    if not (behaelter / ".git").exists():
        return ("kein `.git` neben dem Vorhaben (%s) -- in einem Baum ohne Verlauf hat "
                "dieser Nachweis keinen Gegenstand" % behaelter)
    lauf = subprocess.run(["git", "cat-file", "blob", sha], cwd=behaelter,
                          capture_output=True)
    if lauf.returncode != 0:
        return "git cat-file blob %s gab %d: %s" % (
            sha[:7], lauf.returncode, lauf.stderr.decode("utf-8", "replace").strip())
    return lauf.stdout


# ---------------------------------------------------------------------------
# Die Betriebsart Riegel
# ---------------------------------------------------------------------------


def riegel(wurzel):
    pfad = wurzel / PRUEFLING
    if not pfad.is_file():
        sys.stderr.write("Der Pruefling fehlt: %s\n" % pfad)
        return 2
    rohtext = pfad.read_bytes().decode("utf-8")

    try:
        bestand = pruefe(rohtext)
    except tomllib.TOMLDecodeError as fehler:
        sys.stderr.write("%s ist kein gueltiges TOML: %s\n" % (pfad, fehler))
        return 2
    except KeyError as fehler:
        sys.stderr.write("%s hat keine Tabelle %s\n" % (pfad, fehler))
        return 2

    # Der fehlende Anker steht **vor** dem Selbsttest, obwohl beide Code 2 geben: Der
    # Selbsttest verbiegt den Anker `nennung` und klagte sonst ueber sein Fehlen, statt
    # die Stelle zu nennen, an der der Wortlaut sich bewegt hat.
    if bestand.fehlend:
        sys.stderr.write("Ein Anker steht nicht genau einmal im Kopfkommentar -- der "
                         "Riegel haette hier nichts zu pruefen:\n")
        for zeile in bestand.fehlend:
            sys.stderr.write("  %s\n" % zeile)
        return 2

    verfehlt = (selbsttest_zahlwoerter() + selbsttest_trennung()
                + selbsttest_verdrahtung(rohtext, bestand, wurzel))
    if verfehlt:
        sys.stderr.write("Selbsttest verfehlt in %d Fall/Faellen -- der Riegel misst "
                         "nicht, was er messen soll. Kein Urteil ueber den Bestand.\n"
                         % verfehlt)
        return 2

    z = bestand.zaehlung
    print("Zahlwortriegel fuer %s" % PRUEFLING)
    print("  [datei.vorlagen]:            %d Schluessel" % z["vorlagen"])
    print("  Blattwerte mit der Marke:    %d = %d beleg + %d Vorlage + %d Rest"
          % (z["gesamt"], z["belege"], z["vorlage"], z["rest"]))
    for name in MUSTER:
        stelle = bestand.stellen.get(name)
        if stelle is None:
            continue
        worte = ", ".join("%s (Zeile %d)" % (stelle["block"][p].text,
                                             stelle["block"][p].zeile + 1)
                          for p, _ in stelle["zahlen"])
        print("  Anker %-10s %s" % (name + ":", worte))

    if bestand.befunde:
        sys.stderr.write("Behauptung und Zaehlung gehen auseinander:\n")
        for zeile in bestand.befunde:
            sys.stderr.write("  %s\n" % zeile)
        return 1
    print("  Alle drei Behauptungen decken sich mit ihrer Zaehlung.")
    return 0


# ---------------------------------------------------------------------------
# Die Betriebsart Bericht -- unveraendert seit Paket 0099
# ---------------------------------------------------------------------------


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


def bericht(argv):
    ziel = argv[1]
    if argv[0] != "-":
        wurzel = pathlib.Path(__file__).resolve().parents[2]
        alt = subprocess.run(["git", "cat-file", "blob", argv[0]],
                             cwd=wurzel.parents[1], capture_output=True,
                             check=True).stdout
        messe("Bezugsstand " + argv[0][:7], alt)
    with open(ziel, "rb") as f:
        messe("Arbeitsbaum " + ziel, f.read())
    return 0


if len(sys.argv) == 3 and sys.argv[1] == "--riegel":
    sys.exit(riegel(pathlib.Path(sys.argv[2]).resolve()))
elif len(sys.argv) == 3:
    sys.exit(bericht(sys.argv[1:]))
else:
    sys.stderr.write(
        "Aufruf: zahlwoerter.py --riegel <wurzel des vorhabens>\n"
        "        zahlwoerter.py <blob-sha|-> <pfad>\n")
    sys.exit(2)
