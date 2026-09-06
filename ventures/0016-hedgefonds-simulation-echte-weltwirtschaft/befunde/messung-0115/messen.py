#!/usr/bin/env python3
"""Paket 0115 -- der Riegel zu den drei berichtigten Zahlen im Kopf des
`belegstellen_riegel`.

Kein Bericht: Jede Erwartung steht hier im Skript, und der Rueckgabewert ist 1,
sobald eine nicht aufgeht. Was das Skript prueft:

  A. **Der Vorher-Nachher-Riegel der Abnahme.** Die alte und die neue Fassung
     laufen im *selben* Aufruf ueber den *selben* Baum, wenige Sekunden
     auseinander, und muessen dieselben drei Zahlen von Bedingung 2 melden. Zwei
     getrennte Laeufe wuerden die Drift des Baums mitmessen -- am 2026-09-05 ist
     der Bestand einer Rolle waehrend ihres eigenen Laufs von 37 auf 40 Zitate
     gewandert, von fremder Hand.
  B. **Die drei berichtigten Angaben selbst**, jede gegen den Mutanten, der sie
     erzeugt. Eine Zahl im Kommentar, die nicht aus einem Aufruf stammt, ist eine
     Falschaussage in Wartestellung -- genau die Sorte, gegen die dieses Paket
     geschrieben ist.
  C. **Die Vorfassung, an der A und die Gegenprobe haengen, bringt das Skript
     selbst mit** (Paket 0171). Sie ist nicht das, was unter `$TMPDIR` liegt,
     sondern ein benannter Stand aus dem Archiv: der Elternstand des Baucommits
     von 0115. Fehlt sie, holt das Skript sie; liegt dort etwas anderes, endet
     der Lauf rot. Vorher hing die Beweiskraft an einer Eingabe, die niemand
     kontrollierte -- geprueft wurde an ihr nur, dass sie ungleich der neuen
     Fassung ist, und `$TMPDIR` ist fluechtig.

Gebaut wird ausschliesslich in `$TMPDIR`. Der Quellbaum wird nur fuer die Dauer
von Lauf A auf die alte Fassung zurueckgestellt und in jedem Fall wieder auf die
neue gebracht.
"""
import hashlib
import os
import re
import subprocess
import sys

W = ("/home/adria/fabrik/ventures/"
     "0016-hedgefonds-simulation-echte-weltwirtschaft")
QUELLE = W + "/werkzeuge/belegstellen/belegstellen_riegel.cpp"
MUTIEREN = W + "/bau/kp0086-mutieren.py"
TMP = os.environ.get("TMPDIR", "/tmp") + "/k0115"
VORHER = TMP + "/vorher.cpp"

# Woher die Vorfassung kommt, gegen die Teil A und die Gegenprobe messen: der
# Elternstand des Baucommits von 0115, also genau der Wortlaut, den dieses Paket
# berichtigt hat. Beides ist festgeschrieben -- die Herkunft, damit ein Leser
# weiss, was gemessen wird, und die Blobkennung, damit der Inhalt sich ohne
# fremdes Zutun nachrechnen laesst.
BAUCOMMIT_0115 = "83faa06"
HERKUNFTSPFAD = ("ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
                 "/werkzeuge/belegstellen/belegstellen_riegel.cpp")
VORFASSUNG_BLOB = "e3038e23316f4c18ca9bdd6cbab51e42579e7838"

# Der Stand, gegen den die Zahlen im Kopfkommentar geschrieben sind. Er wird
# abgedruckt und nicht geprueft: Ein fester Sollwert verfiele hier in Stunden.
BEZUGSSTAND = "5d5e2d6"

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


def schreib(pfad, text):
    with open(pfad, "w", encoding="utf-8") as f:
        f.write(text)


def git(*teile):
    """git im Repo, Rueckgabe als Bytes. Ein Fehlschlag beendet den Lauf."""
    p = subprocess.run(["git", "-C", "/home/adria/fabrik"] + list(teile),
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


def vorfassung():
    """Der Wortlaut vor der Berichtigung, an seine Herkunft gebunden.

    Drei Schritte, und jeder kann den Lauf rot machen:

      1. Die Herkunftsangabe wird gegen das Archiv gehalten: Fuehrt der
         Elternstand des Baucommits wirklich diesen Blob? Wer die Geschichte
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
    herkunft = BAUCOMMIT_0115 + "^:" + HERKUNFTSPFAD
    steht = git("rev-parse", herkunft).decode("utf-8").strip()
    if steht != VORFASSUNG_BLOB:
        raise SystemExit(
            "Der Elternstand des Baucommits von 0115 (%s) fuehrt heute den "
            "Blob %s; festgeschrieben ist %s. Die Herkunft der Vorfassung "
            "stimmt nicht mehr -- gemessen wird nichts." % (herkunft, steht,
                                                            VORFASSUNG_BLOB))
    if os.path.exists(VORHER):
        with open(VORHER, "rb") as f:
            daten = f.read()
        ist = blobkennung(daten)
        if ist != VORFASSUNG_BLOB:
            raise SystemExit(
                "Unter %s liegt nicht die Vorfassung von 0115: Der Inhalt "
                "traegt die Blobkennung %s, erwartet ist %s aus %s. Teil A "
                "wuerde gegen den falschen Stand vergleichen und die "
                "Gegenprobe ihre Rotfaehigkeit am falschen Wortlaut pruefen -- "
                "beides ohne eine Meldung. Loesche die Datei; das Skript holt "
                "die richtige selbst."
                % (VORHER, ist, VORFASSUNG_BLOB, herkunft))
        woher = "lag bereit und ist nachgerechnet"
    else:
        daten = git("cat-file", "blob", VORFASSUNG_BLOB)
        ist = blobkennung(daten)
        if ist != VORFASSUNG_BLOB:
            raise SystemExit(
                "Das Archiv hat zu %s einen Inhalt mit der Kennung %s "
                "geliefert. Das darf nicht vorkommen." % (VORFASSUNG_BLOB, ist))
        with open(VORHER, "wb") as f:
            f.write(daten)
        woher = "gefehlt und ist geholt worden"
    print("Vorfassung: %s -- Blob %s aus %s" % (woher, VORFASSUNG_BLOB,
                                                herkunft))
    _vorfassung = daten.decode("utf-8")
    return _vorfassung


def mutant(art):
    return subprocess.run([sys.executable, MUTIEREN, art], check=True,
                          capture_output=True, text=True).stdout


def bauen(text, name, entschaerfen):
    if entschaerfen:
        if text.count(ZAEHLZEILE) == 0:
            raise SystemExit("Der Filter greift nicht mehr -- die Zaehlzeile "
                             "der Selbsttests hat ihre Gestalt geaendert.")
        text = text.replace(ZAEHLZEILE, "")
    pfad = TMP + "/m_" + name
    p = subprocess.run(["/usr/bin/c++", "-x", "c++", "-"] + SCHALTER
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
    return subprocess.run(["git", "-C", "/home/adria/fabrik", "rev-parse",
                           "--short", "HEAD"], capture_output=True,
                          text=True).stdout.strip()


# ---------------------------------------------------------------------------
# A -- vorher und nachher am selben Baum, im selben Aufruf
# ---------------------------------------------------------------------------
def teil_a(neu):
    alt = vorfassung()
    if alt == neu:
        raise SystemExit("Alte und neue Fassung sind zeichengleich -- es gibt "
                         "nichts zu messen.")
    bin_alt = bauen(alt, "vorher", False)
    bin_neu = bauen(neu, "nachher", False)
    try:
        schreib(QUELLE, alt)
        code_a, aus_a, _ = laufen(bin_alt)
        a = drei(aus_a, "der alten Fassung")
        befunde_a = befundliste(aus_a)
    finally:
        schreib(QUELLE, neu)
    code_b, aus_b, _ = laufen(bin_neu)
    b = drei(aus_b, "der neuen Fassung")
    befunde_b = befundliste(aus_b)

    print("A  vorher : Code %d, %d Zitate, %d aufgeloest, %d uebergangen"
          % ((code_a,) + a))
    print("A  nachher: Code %d, %d Zitate, %d aufgeloest, %d uebergangen"
          % ((code_b,) + b))
    if a != b:
        melde("Die Berichtigung bewegt die drei Zahlen des Riegels: %s -> %s. "
              "Die Abnahme von 0115 nennt genau das einen Fehlschlag." % (a, b))
    if code_a != code_b:
        melde("Die Berichtigung bewegt den Rueckgabewert: %d -> %d."
              % (code_a, code_b))
    # Die Zahlen allein genuegen nicht: Ein weggefallener und ein neuer Befund
    # heben einander in der Summe auf. Verglichen werden deshalb die Listen.
    if sorted(befunde_a) != sorted(befunde_b):
        melde("Die Befundlisten sind nicht dieselben. Nur vorher: %s. Nur "
              "nachher: %s."
              % (sorted(set(befunde_a) - set(befunde_b)),
                 sorted(set(befunde_b) - set(befunde_a))))
    if code_b != 0:
        # Kein Fehlschlag dieses Pakets, aber es gehoert abgedruckt: Der Baum
        # war schon vor der Berichtigung rot, und zwar von fremder Hand.
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
# B -- die drei berichtigten Angaben, jede gegen ihren Mutanten
#
# Die Erwartung steht **nicht** als Zahl im Skript, sondern wird aus dem
# Kommentar gelesen, der sie behauptet. Das ist der ganze Punkt von 0115: Eine
# Zahl, die nur im Messgeraet mitgefuehrt wird, kann im Text still falsch werden.
# ---------------------------------------------------------------------------
ZAHLWORT = {"eine": 1, "zwei": 2, "drei": 3, "vier": 4, "fuenf": 5,
            "sechs": 6, "sieben": 7, "acht": 8, "neun": 9, "zehn": 10,
            "elf": 11, "zwoelf": 12, "zweit": 2}


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


def teil_b1(text, grund):
    """Angabe 1: die Selbsttreffer unter `ohne-marken-rein`, gegen den Wortlaut
    des Kopfkommentars und gegen die Aufschluesselung bei `Klammer`."""
    pfad = bauen(mutant("ohne-marken-rein"), "ohne_marken_rein", True)
    code, aus, _ = laufen(pfad)
    z, auf, ueb = drei(aus, "ohne-marken-rein")
    stellen = re.findall(r"zitierend: (\S+?):(\d+)", aus)
    eigen = [int(n) for d, n in stellen
             if d.endswith("werkzeuge/belegstellen/belegstellen_riegel.cpp")]
    verteilung = einordnen(text, eigen)
    print("B1 ohne-marken-rein: Code %d, %d Zitate, %d aufgeloest, %d "
          "uebergangen; %d Stellen zu Unrecht, davon %d im eigenen Quelltext %s"
          % (code, z, auf, ueb, len(stellen), len(eigen), verteilung))

    t = gelesen(text,
                r"\*\*(\w+) Stellen zu Unrecht, (\w+) davon in seinem eigenen "
                r"Quelltext\*\* -- (\d+) statt (\d+) Zitate, weiterhin nur "
                r"(\d+) aufgeloest, (\d+) statt (\d+) Fundstellen",
                "Angabe 1")
    if t:
        for genannt, ist, was in (
                (ZAHLWORT.get(t.group(1)), len(stellen), "Stellen zu Unrecht"),
                (ZAHLWORT.get(t.group(2)), len(eigen), "davon im eigenen Quelltext"),
                (int(t.group(3)), z, "Zitate unter der Mutation"),
                (int(t.group(4)), grund[0], "Zitate ohne die Mutation"),
                (int(t.group(5)), auf, "aufgeloeste Zitate"),
                (int(t.group(6)), ueb, "uebergangene Fundstellen unter der Mutation"),
                (int(t.group(7)), grund[2], "uebergangene Fundstellen ohne sie")):
            if genannt != ist:
                melde("Der Kopfkommentar nennt %s %s, gemessen sind %d."
                      % (genannt, was, ist))

    a = gelesen(text,
                r"faengt der Riegel (\w+) Stellen in seinem eigenen Quelltext, "
                r"alle falsch -- (\w+) im Kopfkommentar .*?, (\w+) in "
                r"`SATZFAELLE` und (\w+) in `ZITATFAELLE`",
                "die Aufschluesselung bei Klammer::kuendigt_an")
    if a:
        for genannt, schluessel in ((a.group(1), None), (a.group(2), "Kopf"),
                                    (a.group(3), "SATZFAELLE"),
                                    (a.group(4), "ZITATFAELLE")):
            ist = len(eigen) if schluessel is None else verteilung.get(schluessel, 0)
            if ZAHLWORT.get(genannt) != ist:
                melde("Die Aufschluesselung bei `Klammer::kuendigt_an` nennt "
                      "%s fuer %s, gemessen sind %d."
                      % (genannt, schluessel or "den eigenen Quelltext", ist))
    if verteilung.get("sonst"):
        melde("%d Selbsttreffer liegen weder im Kopfkommentar noch in einer "
              "genannten Falltabelle -- die Aufschluesselung ist unvollstaendig."
              % verteilung["sonst"])


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


def teil_b2(text, grund):
    """Angabe 2: `rechts-ohne-satzgrenze-rein` bewegt den Bestand nicht mehr,
    und Fall 6 in ABSTANDSFAELLE traegt die Regel allein."""
    frei = bauen(mutant("rechts-ohne-satzgrenze-rein"), "rosg_frei", True)
    code, aus, _ = laufen(frei)
    m = drei(aus, "rechts-ohne-satzgrenze-rein")
    print("B2 rechts-ohne-satzgrenze-rein (entschaerft): Code %d, %d Zitate, "
          "%d aufgeloest, %d uebergangen" % ((code,) + m))

    t = gelesen(text,
                r"nennt derselbe Mutant genau dieselben drei Zahlen wie der "
                r"unveraenderte Riegel -- (\d+) Zitate, (\d+) aufgeloest, "
                r"(\d+) uebergangene Fundstellen, vorher wie nachher die "
                r"Summe (\d+)", "Angabe 2")
    if t:
        genannt = (int(t.group(1)), int(t.group(2)), int(t.group(3)))
        if genannt != grund:
            melde("Angabe 2 nennt %s als die Zahlen des unveraenderten "
                  "Riegels, gemessen sind %s." % (genannt, grund))
        if genannt != m:
            melde("Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt "
                  "%s statt %s." % (m, genannt))
        if int(t.group(4)) != m[0] + m[2]:
            melde("Angabe 2 nennt die Summe %s; Zitate plus uebergangene "
                  "Fundstellen sind %d." % (t.group(4), m[0] + m[2]))
    if m[0] + m[2] != grund[0] + grund[2]:
        melde("Zitate plus uebergangene Fundstellen gehen gegen den eigenen "
              "Ausgangsstand nicht auf: %d statt %d."
              % (m[0] + m[2], grund[0] + grund[2]))

    roh = bauen(mutant("rechts-ohne-satzgrenze-rein"), "rosg_roh", False)
    code, _, stderr = laufen(roh)
    zeilen = [z for z in stderr.splitlines() if z.startswith("Selbsttest")]
    print("B2 rechts-ohne-satzgrenze-rein (scharf): Code %d, %d Meldung(en)"
          % (code, len(zeilen)))
    for z in zeilen:
        print("     " + z)
    f = gelesen(text, r"heute allein an Fall (\d+) in `(\w+)`\. Der Mutant "
                      r"`([\w-]+)` laesst ihn reissen und bricht mit Code (\d+) "
                      r"ab: (.*?)\.", "die Fallangabe von Angabe 2")
    if f:
        if int(f.group(4)) != code:
            melde("Angabe 2 nennt Code %s, gemessen ist %d."
                  % (f.group(4), code))
        # `ABSTANDSFAELLE` -> `Abstand`: der Selbsttest nennt den Fall im
        # Singular, die Tabelle im Plural mit Fugen-s.
        erwartet = "Selbsttest %s %s:" % (
            f.group(2).removesuffix("FAELLE").rstrip("S").capitalize(),
            f.group(1))
        if len(zeilen) != 1 or not zeilen[0].startswith(erwartet):
            melde("Angabe 2 nennt Fall %s in `%s` als den einzigen, der "
                  "reisst (%r). Gerissen sind: %s"
                  % (f.group(1), f.group(2), erwartet, zeilen or "keiner"))
        elif f.group(5).replace("`", "") not in zeilen[0]:
            melde("Angabe 2 druckt den Wortlaut der Meldung ab; er lautet "
                  "heute anders: %s" % zeilen[0])


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
# ---------------------------------------------------------------------------
def gegenprobe(grund):
    """Dieselben drei Pruefungen, aber gegen den Wortlaut **vor** der
    Berichtigung. Der Bestand und die Mutanten bleiben dabei die von heute; was
    sich unterscheidet, ist allein die Aussage, die geprueft wird.

    Alle drei muessen reissen. Tut es eine nicht, misst sie nicht die Angabe,
    sondern laeuft nur mit."""
    alt = vorfassung()
    vorher_fehler = len(fehler)
    teil_b1(alt, grund)
    n1 = len(fehler)
    teil_b2(alt, grund)
    n2 = len(fehler)
    teil_b3(alt)
    n3 = len(fehler)
    ergebnis = []
    for name, zahl in (("Angabe 1", n1 - vorher_fehler), ("Angabe 2", n2 - n1),
                       ("Angabe 3", n3 - n2)):
        ergebnis.append("%s: %d Meldung(en)" % (name, zahl))
    del fehler[vorher_fehler:]
    print("G  Gegenprobe am Wortlaut vor der Berichtigung -- " +
          ", ".join(ergebnis))
    for name, zahl in (("Angabe 1", n1 - vorher_fehler), ("Angabe 2", n2 - n1),
                       ("Angabe 3", n3 - n2)):
        if zahl == 0:
            melde("Die Pruefung zu %s wird an der alten, falschen Fassung "
                  "nicht rot. Sie misst die Angabe nicht." % name)


def main():
    os.makedirs(TMP, exist_ok=True)
    # Vor allem anderen: Die Vorfassung wird beschafft und an ihre Herkunft
    # gebunden. Was danach kommt, misst gegen sie -- eine falsche Eingabe hier
    # macht jede Zahl weiter unten wertlos, und zwar lautlos.
    vorfassung()
    neu = lies(QUELLE)
    vor = kopf()
    print("Bezugsstand im Kommentar: %s; HEAD zu Beginn: %s" % (BEZUGSSTAND, vor))
    grund = teil_a(neu)
    teil_b1(neu, grund)
    teil_b2(neu, grund)
    teil_b3(neu)
    print()
    gegenprobe(grund)
    nach = kopf()
    print("HEAD am Ende: %s" % nach)
    if vor != nach:
        melde("Der Baum ist waehrend der Messung gewandert (%s -> %s). Die "
              "Zahlen gehoeren neu erhoben." % (vor, nach))
    # Der Stand im Kommentar ist eine Herkunftsangabe, keine Bedingung: Ein
    # fremder Commit darf dieses Skript nicht rot machen. Geprueft wird nur,
    # dass Kommentar und Skript denselben Stand nennen; weicht HEAD davon ab,
    # steht es als Hinweis da und nicht als Fehlschlag.
    # Ueber `flach` und nicht ueber den Rohtext: Die Angabe bricht um, und ein
    # Muster am Rohtext uebersieht genau die Fundstelle, die dann stehen bleibt.
    staende = set(re.findall(r"gegen den Stand `(\w+)`", flach(neu)))
    if staende != {BEZUGSSTAND}:
        melde("Das Skript nennt %s als Bezugsstand, der Kommentar nennt %s."
              % (BEZUGSSTAND, sorted(staende) or "keinen"))
    if BEZUGSSTAND not in (vor, nach):
        print("Hinweis: HEAD steht auf %s, gemessen und niedergeschrieben ist "
              "der Stand %s. Die Zahlen sind damit aelter als der Baum."
              % (nach, BEZUGSSTAND))
    if lies(QUELLE) != neu:
        melde("Die Quelldatei steht am Ende nicht auf der neuen Fassung.")
    if fehler:
        print("\n%d Erwartung(en) nicht erfuellt." % len(fehler))
        return 1
    print("\nAlle Erwartungen erfuellt.")
    return 0


sys.exit(main())
