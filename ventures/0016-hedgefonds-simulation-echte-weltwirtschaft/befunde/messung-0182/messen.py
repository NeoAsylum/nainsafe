#!/usr/bin/env python3
"""Der Messstand zu Paket 0182 -- die Sammelstellen-Sortierung, dauerhaft gedeckt.

Paket 0130 hat die Ordnung des Berichts an eine Regel gebunden statt an das
Dateisystem. Gemessen wurde das seither an zwei Stellen: die Tabelle ORDNUNGSFAELLE
prueft `ordne_kurznamen`, und **einmal** hat jemand zwei Bestandskopien auf ext4 und
tmpfs verglichen. Die Sortierung der wirklich gesammelten Dateiliste nimmt denselben
Vergleich, aber einen eigenen Aufruf, den kein Fall des Selbsttests sieht: Der Mutant
`ohne-sortierung` bestand am 2026-09-06 den vollstaendigen Selbsttest und den ganzen
Lauf. Seit Paket 0182 haelt eine Zusicherung in `main` die gesammelte Liste in der
Ordnung von `vor_in_byteordnung`; dieser Stand ist der Nachweis, dass sie reissen
**kann** -- und er faehrt ihn bei jedem Bau, statt ihn abzudrucken.

Er misst dreierlei und behauptet nichts:

  0. **Die Selbstprobe.** Der Auswerter muss die Meldung der Zusicherung im Wortlaut
     erkennen und an einer Ausgabe ohne sie **nein** sagen koennen; die Nadel des
     Mutanten muss im Quelltext genau einmal vorkommen, und der Wortlaut der Meldung
     ebenso. Ohne die zweite Haelfte bliebe ein Auswerter, der nie etwas findet, in
     jedem Lauf still gruen. Alles davon laeuft **vor** der ersten Uebersetzung.

  1. **Die ausgelieferte Fassung.** Uebersetzt und ueber den heutigen Arbeitsbaum
     gelaufen: Die Meldung darf nicht kommen. Kommt sie, ist entweder die Sortierung
     an der Sammelstelle kaputt oder die Zusicherung selbst -- beides ein Befund.

  2. **Der Mutant, gefahren statt behauptet.** Eine Ersetzung, die den Sortieraufruf in
     `sammle_dateien` entfernt und sonst nichts. Er muss den Selbsttest bestehen -- der
     sieht diesen Aufruf nicht, das ist der ganze Befund dahinter -- und danach mit
     Rueckgabe 2 und der Meldung abbrechen, die die unsortierte Stelle benennt. Tut er
     das nicht, deckt die Zusicherung nichts.

**Die Grenze gehoert dazu, und sie ist der Grund, warum dieser Stand faehrt statt zu
rechnen:** Auf einem Dateisystem, das zufaellig sortiert auflistet, bliebe der Mutant
gruen, ohne dass an der Zusicherung etwas fehlte. Der Nachweis gilt fuer den Baum, ueber
den er gerade gelaufen ist, und fuer keinen anderen. Bleibt der Mutant gruen, meldet
dieser Stand deshalb einen Befund **und** nennt diese Moeglichkeit beim Namen, damit sie
nicht als Beweis fuer eine kaputte Zusicherung durchgeht.

**Drei Rueckgabewerte, und der Unterschied ist der Zweck dieser Datei:**

    0  gruen -- die ausgelieferte Fassung schweigt, der Mutant reisst.
    1  **Befund** -- gemessen wurde, und etwas ging anders aus als erwartet.
    2  **Messgeraet ohne Messung** -- eine Nadel trifft nicht mehr, etwas uebersetzt
       nicht, die ausgelieferte Fassung kommt gar nicht bis zur Sammelstelle. Ein Lauf,
       der 2 gibt, sagt ueber die Zusicherung nichts, weder gut noch schlecht.

**Was dieser Stand ausdruecklich nicht zum Befund macht:** einen Rueckgabewert 1 der
ausgelieferten Fassung. Das ist ein Fund des Riegels ueber den Bestand -- ein totes
Zitat, das jemand anders hineingeschrieben hat -- und nicht diese Zusicherung. Der
Wert wird gedruckt und nicht gewertet. Am 2026-09-07 hat genau diese Verwechslung dem
Nachbarstand zu Paket 0166 einen Ruecklauf gekostet: Der Bestand war unter der Messung
weggewandert, die Messung war richtig, und rot wurde trotzdem sie.

Gebaut wird ohne `-Werror`, aus demselben Grund wie bei den Nachbarstaenden: Beim
Entfernen des Sortieraufrufs faellt leicht eine Groesse aus dem Spiel, und dann wuerde
der Bau rot statt der Messung. Die Sprachschalter sind die des Baulaufs.

Aufruf:  python3 messen.py [--vorhaben <wurzel>] [--uebersetzer <pfad>]
"""

import argparse
import os
import pathlib
import subprocess
import sys

HIER = pathlib.Path(__file__).resolve()
VORHABEN_VORGABE = HIER.parents[2]

SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O2"]

ARBEITSNAME = "messung-0182"

QUELLE_IM_VORHABEN = "werkzeuge/belegstellen/belegstellen_riegel.cpp"


class Messfehler(Exception):
    """Der Stand kann nicht messen. Fuehrt zu Rueckgabe 2, nie zu 1."""


# --- Die beiden Nadeln ------------------------------------------------------------
#
# Zwei verschiedene Wortlaute, und der Unterschied ist keine Nachlaessigkeit: Im
# Quelltext steht die Meldung als Folge von Teilstuecken, die der Uebersetzer
# zusammenzieht. Die Nadel im Quelltext muss deshalb **ein** Teilstueck sein, die Nadel
# in der Ausgabe das Zusammengezogene.

# Die Nadel im Quelltext: ein zusammenhaengendes Teilstueck der Meldung. Sie wird vor
# der ersten Uebersetzung geprueft -- wer die Meldung umformuliert, macht diesen Stand
# blind (Rueckgabe 2), und das ist der richtige Ausgang.
MARKE_QUELLE = ("belegstellen_riegel: die gesammelte Liste '%s' ist nicht in der "
                "Ordnung ")

# Die Nadel in der Ausgabe: was der Uebersetzer daraus macht.
MARKE_AUSGABE = "ist nicht in der Ordnung von"

# Die Meldung soll die Stelle **benennen** und nicht nur melden, dass es eine gibt.
MARKE_STELLE = "Zuerst an Platz "

# Der Abbruch am Selbsttest. Der Mutant darf ihn **nicht** ausloesen -- dass kein Fall
# des Selbsttests den entfernten Aufruf sieht, ist der gemessene Befund hinter diesem
# ganzen Paket. Reisst der Mutant hier, misst er etwas anderes als das Gemeinte.
MARKE_SELBSTTEST = "Faellen des Selbsttests"

# Der Mutant, eine Ersetzung. Der Sortieraufruf an der Sammelstelle faellt weg, alles
# andere bleibt -- insbesondere `vor_in_byteordnung` und `ordne_kurznamen`, damit der
# Selbsttest weiterhin gruen ist. Genau das ist der gemessene Befund dahinter: Diese
# Fassung besteht alle Faelle des Selbsttests.
SORTIERUNG_ALT = """    std::sort(gefunden.begin(), gefunden.end(),
              [](const fs::path& links, const fs::path& rechts) {
                  const std::string a = links.string();
                  const std::string b = rechts.string();
                  return vor_in_byteordnung(a, b);
              });
"""

SORTIERUNG_NEU = """    // Messung 0182: der Sortieraufruf ist hier entfernt. Die gesammelte Liste bleibt
    // in der Ordnung, in der das Dateisystem sie ausgibt.
"""


def einmal_ersetzen(text, alt, neu):
    """Ersetzt `alt` durch `neu` und besteht darauf, dass `alt` **genau einmal**
    vorkommt.

    Die einzige Stelle, an der dieser Stand merkt, dass sein Gegenstand weggewandert
    ist. Sie **wirft** und ruft nicht `sys.exit`, damit daraus die Rueckgabe 2 wird und
    nicht die 1: Eine nicht mehr treffende Nadel ist kein Befund ueber die Zusicherung,
    sondern ein blindes Messgeraet.
    """
    anzahl = text.count(alt)
    if anzahl != 1:
        raise Messfehler("der erwartete Wortlaut kommt " + str(anzahl)
                         + "-mal vor, erwartet genau einmal")
    return text.replace(alt, neu)


def meldet_unordnung(ausgabe):
    """Traegt die Ausgabe die Meldung der Zusicherung?"""
    return MARKE_AUSGABE in ausgabe


# --- Die Selbstprobe des Auswerters -----------------------------------------------

PROBE_MELDUNG = (
    "belegstellen_riegel: die gesammelte Liste 'Bestand' ist nicht in der Ordnung von\n"
    "`vor_in_byteordnung`. Zuerst an Platz 7:\n"
    "  Platz 6: /w/werkzeuge/b.cpp\n"
    "  Platz 7: /w/daten/a.md\n")

PROBE_OHNE = (
    "belegstellen_riegel, Selbsttest: 12 Faelle zur Suche nach links, alle wie "
    "erwartet.\n"
    "belegstellen_riegel: keine einzige Bauquelle gefunden.\n")

PROBE_SELBSTTEST_ROT = (
    "\nbelegstellen_riegel: 3 von 65 Faellen des Selbsttests sind nicht wie erwartet\n"
    "ausgegangen. Der Riegel hat den Bestand gar nicht erst gelesen.\n")


def selbstprobe():
    """Rueckgabe: Zahl der Abweichungen. Jede davon heisst: der Stand misst nicht."""
    fehler = 0

    def haelt(bedingung, gut, schlecht):
        nonlocal fehler
        if bedingung:
            print("OK  Selbstprobe: " + gut)
        else:
            print("ROT Selbstprobe: " + schlecht)
            fehler += 1

    # 1. Der Auswerter muss ja sagen -- und, was mehr wert ist, nein. Die zweite Probe
    #    laeuft gegen eine Ausgabe, die den Riegel bei einem *anderen* Abbruch mit
    #    Rueckgabe 2 zeigt: Genau daran wuerde ein Auswerter, der nur auf den
    #    Rueckgabewert sieht, den Mutanten faelschlich fuer gefangen halten.
    haelt(meldet_unordnung(PROBE_MELDUNG),
          "die Meldung der Zusicherung wird erkannt.",
          "die Meldung der Zusicherung wird nicht erkannt -- der Wortlaut hat sich "
          "geaendert und dieser Stand misst nichts mehr.")
    haelt(not meldet_unordnung(PROBE_OHNE),
          "eine Ausgabe ohne die Meldung gibt nichts her.",
          "der Auswerter findet die Meldung in einer Ausgabe ohne sie.")
    haelt(MARKE_STELLE in PROBE_MELDUNG,
          "die Meldung nennt die unsortierte Stelle.",
          "die Probe der Meldung nennt keine Stelle -- die Nadel " + MARKE_STELLE
          + " trifft nicht.")

    # Die Nadel auf den Abbruch am Selbsttest, in beide Richtungen. Ohne die zweite
    # Haelfte koennte sie auf jede Ausgabe passen, in der das Wort `Selbsttest`
    # vorkommt -- und das tut es in **jedem** gruenen Lauf des Riegels.
    haelt(MARKE_SELBSTTEST in PROBE_SELBSTTEST_ROT,
          "der Abbruch am Selbsttest wird erkannt.",
          "der Abbruch am Selbsttest wird nicht erkannt -- der Wortlaut hat sich "
          "geaendert.")
    haelt(MARKE_SELBSTTEST not in PROBE_OHNE,
          "die Meldung eines bestandenen Selbsttests gilt nicht als Abbruch.",
          "die Nadel auf den Abbruch trifft auch einen bestandenen Selbsttest -- dann "
          "waere jeder Lauf ein Messfehler.")

    # 2. `einmal_ersetzen`, dreimal: fehlt / zweimal / genau einmal. Die Nadel des
    #    dritten Falls steht **in der Mitte** und nicht am Anfang -- ersetzt jemand den
    #    Rumpf durch `neu + text[len(alt):]`, gaebe die Nadel "a" auf "axb" weiterhin
    #    brav "yxb" und der Fall bliebe gruen. Die Nadel "x" gibt dort "yb" statt "ayb"
    #    und reisst. Das linke "a" und das rechte "b" bezeugen Kopf und Fuss.
    for name, text, nadel, erwartet in [("fehlt", "abc", "x", None),
                                        ("zweimal", "axax", "a", None),
                                        ("genau einmal", "axb", "x", "ayb")]:
        try:
            gab = einmal_ersetzen(text, nadel, "y")
        except Messfehler:
            gab = None
        haelt(gab == erwartet,
              "`einmal_ersetzen` haelt den Fall '" + name + "'.",
              "`einmal_ersetzen` geht im Fall '" + name + "' aus als " + str(gab)
              + ", erwartet war " + str(erwartet) + ".")
    return fehler


# --- Uebersetzen und laufen -------------------------------------------------------


def uebersetze(uebersetzer, quelle, ziel):
    ruf = [uebersetzer] + SCHALTER + [str(quelle), "-o", str(ziel)]
    try:
        fertig = subprocess.run(ruf, capture_output=True, text=True)
    except OSError as grund:
        raise Messfehler("der Uebersetzer ist nicht aufrufbar: " + str(grund))
    if fertig.returncode != 0:
        raise Messfehler("BAU ROT: " + " ".join(ruf) + "\n" + fertig.stderr[-4000:])


def baue_und_laufe(uebersetzer, arbeit, vorhaben, name, text):
    """Uebersetzt `text`, laesst ihn ueber den Baum laufen, gibt (rc, stdout, stderr)."""
    quelle = arbeit / (name + ".cpp")
    programm = arbeit / name
    quelle.write_text(text, encoding="utf-8")
    uebersetze(uebersetzer, quelle, programm)
    fertig = subprocess.run([str(programm), str(vorhaben)],
                            capture_output=True, text=True)
    return fertig.returncode, fertig.stdout, fertig.stderr


def stand_aus_dem_verlauf(repo):
    """Die Kennung des Arbeitsbaums, gelesen aus dem Aenderungsverlauf.

    **Beiwerk des Berichts, keine Bedingung der Messung** -- faellt sie aus, steht dort
    "unbekannt" und der Lauf geht weiter. Gelesen wird die letzte Zeile von
    `.git/logs/HEAD`; ein Aufruf von `git` steht diesem Stand nicht zur Verfuegung.
    """
    try:
        zeilen = (repo / ".git" / "logs" / "HEAD").read_text(
            encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return "unbekannt"
    if not zeilen:
        return "unbekannt"
    teile = zeilen[-1].split()
    if len(teile) < 2 or len(teile[1]) < 7:
        return "unbekannt"
    return teile[1][:7]


def messe(vorhaben, uebersetzer):
    """Rueckgabe: Zahl der **Befunde**. Wirft `Messfehler`, wenn nicht gemessen wurde."""
    quelldatei = vorhaben / QUELLE_IM_VORHABEN
    if not quelldatei.is_file():
        raise Messfehler("die gemessene Datei fehlt: " + str(quelldatei))
    quelltext = quelldatei.read_text(encoding="utf-8")

    arbeit = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / ARBEITSNAME
    arbeit.mkdir(parents=True, exist_ok=True)

    print("Messstand 0182 -- die Sammelstellen-Sortierung, dauerhaft gedeckt")
    print("Vorhaben:    " + str(vorhaben))
    print("Uebersetzer: " + uebersetzer)
    print("Arbeitsbaum: " + stand_aus_dem_verlauf(vorhaben.parent.parent))
    print("Schalter:    " + " ".join(SCHALTER))
    print("")

    befunde = 0

    # --- Teil 0: die Selbstprobe -------------------------------------------------
    print("Teil 0 -- der Messstand selbst")
    if selbstprobe():
        raise Messfehler("der Auswerter misst nicht. Alles Weitere waere wertlos.")

    # Beide Nadeln **vor** der ersten Uebersetzung. Eine, die ihren Gegenstand verloren
    # hat, kostet hier eine Sekunde und weiter unten zwei Uebersetzungen.
    stumpf = []
    try:
        mutant_text = einmal_ersetzen(quelltext, SORTIERUNG_ALT, SORTIERUNG_NEU)
    except Messfehler as grund:
        stumpf.append("der Sortieraufruf an der Sammelstelle: " + str(grund))
        mutant_text = None
    if quelltext.count(MARKE_QUELLE) != 1:
        stumpf.append("der Wortlaut der Meldung kommt "
                      + str(quelltext.count(MARKE_QUELLE))
                      + "-mal im Quelltext vor, erwartet genau einmal")
    if stumpf:
        raise Messfehler("Nadeln treffen ihren Gegenstand nicht mehr:\n  - "
                         + "\n  - ".join(stumpf))
    print("OK  Selbstprobe: beide Nadeln treffen genau einmal.")
    print("")

    # --- Teil 1: die ausgelieferte Fassung ---------------------------------------
    print("Teil 1 -- die ausgelieferte Fassung")
    rc_echt, aus_echt, err_echt = baue_und_laufe(uebersetzer, arbeit, vorhaben,
                                                 "riegel-echt", quelltext)
    print("    Rueckgabe " + str(rc_echt))
    if meldet_unordnung(aus_echt + err_echt):
        print("ROT die ausgelieferte Fassung meldet eine unsortierte Sammelstelle. "
              "Entweder ist")
        print("    die Sortierung kaputt oder die Zusicherung selbst. Der Wortlaut:")
        for zeile in (err_echt.splitlines() or ["<leer>"])[-6:]:
            print("      " + zeile)
        befunde += 1
    elif rc_echt == 2:
        raise Messfehler(
            "die ausgelieferte Fassung bricht mit Rueckgabe 2 ab, aber nicht an der "
            "Zusicherung.\nSie ist damit gar nicht bis zur Sammelstelle gekommen, und "
            "der Mutant unten waere\nmit derselben 2 nicht zu unterscheiden.\n"
            "  stderr (Ende): " + err_echt[-1500:])
    else:
        print("OK  die Zusicherung schweigt -- die gesammelte Liste ist geordnet.")
        if rc_echt != 0:
            print("    HINWEIS: Rueckgabe " + str(rc_echt) + " -- der Riegel hat am "
                  "Bestand etwas zu beanstanden.")
            print("    Das ist ein Fund ueber den Bestand und nicht ueber diese "
                  "Zusicherung; dieser")
            print("    Stand wertet ihn nicht. Wer ihn sehen will, liest den Eintrag "
                  "`belegstellen_riegel`")
            print("    im selben Bericht -- der wird davon rot, dieser hier zu Recht "
                  "nicht.")
    print("")

    # --- Teil 2: der Mutant, der Rotnachweis -------------------------------------
    print("Teil 2 -- der Mutant: der Sortieraufruf an der Sammelstelle entfernt")
    rc_mut, aus_mut, err_mut = baue_und_laufe(uebersetzer, arbeit, vorhaben,
                                              "riegel-ohne-sortierung", mutant_text)
    alles_mut = aus_mut + err_mut
    print("    Rueckgabe " + str(rc_mut))

    # Der Selbsttest des Mutanten muss durchgelaufen sein -- er ist der Befund
    # dahinter: Keiner seiner Faelle sieht diesen Sortieraufruf. Reisst er trotzdem,
    # misst der Mutant etwas anderes als das Gemeinte, und dieser Stand sagt es.
    if MARKE_SELBSTTEST in alles_mut:
        raise Messfehler(
            "der Mutant reisst schon im Selbsttest und kommt nie zur Sammelstelle. "
            "Damit\nmisst er nicht mehr, was er messen soll -- ein Fall des Selbsttests "
            "sieht den\nentfernten Aufruf inzwischen doch.\n"
            "  stderr (Ende): " + err_mut[-1500:])

    if meldet_unordnung(alles_mut) and rc_mut == 2:
        print("OK  Rotnachweis: der Mutant besteht den Selbsttest und reisst danach an "
              "der")
        print("    Zusicherung, mit Rueckgabe 2. Der Wortlaut:")
        for zeile in err_mut.splitlines()[-6:]:
            print("      " + zeile)
        if MARKE_STELLE not in alles_mut:
            print("ROT die Meldung benennt die unsortierte Stelle nicht.")
            befunde += 1
    elif meldet_unordnung(alles_mut):
        print("ROT der Mutant meldet die Unordnung, endet aber mit Rueckgabe "
              + str(rc_mut) + " statt mit 2.")
        befunde += 1
    else:
        print("ROT Rotnachweis: der Mutant laeuft durch, ohne dass die Zusicherung "
              "reisst.")
        print("    Zwei Lesarten, und dieser Stand kann sie nicht trennen:")
        print("      a) die Zusicherung deckt die Stelle nicht -- dann ist Paket 0182 "
              "wertlos;")
        print("      b) dieses Dateisystem listet zufaellig in der Ordnung von "
              "`vor_in_byteordnung`")
        print("         auf -- dann ist die Zusicherung in Ordnung und nur hier nicht "
              "zu messen.")
        print("    Wer das entscheidet, laesst denselben Mutanten ueber eine Kopie des "
              "Baums auf")
        print("    einem anderen Dateisystem laufen. Am 2026-09-06 trennte ext4 gegen "
              "tmpfs.")
        for zeile in (err_mut.splitlines() or ["<leer>"])[-4:]:
            print("      " + zeile)
        befunde += 1
    print("")
    return befunde


def main():
    zerleger = argparse.ArgumentParser(add_help=True)
    zerleger.add_argument("--vorhaben", default=str(VORHABEN_VORGABE),
                          help="Wurzel des Vorhabens; sonst aus dem Ort dieser Datei.")
    zerleger.add_argument("--uebersetzer", default=None,
                          help="Der Uebersetzer, gegen den gebaut wird. Aus CMake "
                               "${CMAKE_CXX_COMPILER}; sonst g++ aus dem Suchpfad.")
    wahl = zerleger.parse_args()

    if wahl.uebersetzer is None:
        print("HINWEIS: kein --uebersetzer uebergeben, Rueckfall auf 'g++' aus dem "
              "Suchpfad. Das ist nicht notwendig der, gegen den dieser Kasten gebaut "
              "wird.")
    uebersetzer = wahl.uebersetzer or "g++"

    try:
        befunde = messe(pathlib.Path(wahl.vorhaben).resolve(), uebersetzer)
    except Messfehler as grund:
        print("")
        print("Messstand 0182: NICHT GEMESSEN -- " + str(grund))
        print("Rueckgabe 2. Dieser Lauf sagt ueber die Zusicherung nichts, weder gut "
              "noch schlecht.")
        return 2

    if befunde == 0:
        print("Messstand 0182: die Zusicherung schweigt am Bestand und reisst am "
              "Mutanten.")
        return 0
    print("Messstand 0182: " + str(befunde) + " Abweichung(en).")
    return 1


if __name__ == "__main__":
    sys.exit(main())
