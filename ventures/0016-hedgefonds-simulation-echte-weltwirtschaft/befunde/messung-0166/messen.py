#!/usr/bin/env python3
"""Der Messstand zu Paket 0166 -- die sechs Fassungen des Wortabstands, nachgemessen.

Der Kopfkommentar von `belegstellen_riegel.cpp` traegt eine Tabelle mit sechs Zeilen
und einen Absatz zur Schwelle. Bis zum 2026-09-07 standen dort **Grundzahlen**: 33/33/58
bis 34/34/58, gemessen am 2026-09-05. Am 2026-09-06 gab derselbe Satz Mutanten 39/39/47
bis 40/40/47 -- jede der zwoelf Zahlen war beim Aufschreiben richtig und einen Tag darauf
falsch, waehrend die **Unterschiede** zwischen den Fassungen an beiden Tagen dieselben
waren. Seit Paket 0166 steht deshalb der Unterschied im Kopf, und dieser Stand misst ihn
bei jedem Bau nach.

Er misst viererlei und behauptet nichts:

  0. **Die Selbstprobe.** Der Auswerter muss die sechs Zeilen im Wortlaut des Kopfes
     lesen, er muss an einer falschen Zahl und an einer fehlenden Zeile **nein** sagen
     koennen, und jede Nadel muss im Quelltext genau einmal vorkommen. Ohne die zweite
     Haelfte bliebe ein Auswerter, der nie etwas findet, in jedem Lauf still gruen.
     Alles davon laeuft **vor** der ersten Uebersetzung und kostet nichts.

  1. **Der Vorlauf.** Die Fassung vor Paket 0166 und die danach laufen im selben Aufruf
     ueber denselben Baum und muessen dieselben drei Zahlen melden. Die Fassung davor
     wird nicht aus dem Aenderungsverlauf geholt, sondern aus der heutigen durch
     Rueckersetzung der beiden geaenderten Bloecke gebaut -- `git` steht diesem Stand
     nicht zur Verfuegung, und eine eingetragene Kennung verfaellt in Stunden.
     **Was dieser Vergleich zeigt und was nicht:** Paket 0166 aendert nur Kommentartext,
     also sind beide Programme im Verhalten gleich und der Vergleich ist notwendig gruen.
     Er steht hier, weil die Abnahme ihn verlangt, und er wird rot, sobald jemand in
     diese beiden Bloecke Code hineinschreibt. Ob der **neue Kommentartext** seinerseits
     eine Fundstelle erzeugt, beantwortet er nicht -- das beantwortet der Riegel selbst,
     der seinen eigenen Quelltext mitliest und rot wird, wenn dort ein totes Zitat steht.

  2. **Die sechs Fassungen.** Jede ist eine Textersetzung auf einer Kopie ausserhalb des
     Quellbaums. Anders als bei Paket 0147 muss hier **keine** am Selbsttest sterben:
     Diese Fassungen sollen den Bestand lesen, denn ihre Zahlen sind der Gegenstand.
     Genau daran waeren die Mutanten vom 2026-09-06 heute gescheitert -- sie schalteten
     die Lockerung in `waehle_zitatform` und in `WORTABSTAND_HOECHSTENS` ab, und seit
     Paket 0147 haengen dort `FORMFAELLE` und `ABSTANDSFAELLE`, die dann reissen und den
     Lauf mit 2 beenden, ehe eine Zahl entsteht. Die Fassungen unten greifen deshalb an
     der **Aufrufstelle** im Lauf ueber den Bestand an, nicht am gemeinsamen Baustein.

  3. **Der Rotnachweis, gefahren statt behauptet.** Derselbe Vergleich laeuft ein zweites
     Mal gegen den Kopfkommentar der Fassung **vor** Paket 0166. Er muss dort etwas zu
     beanstanden haben; findet er nichts, misst die ganze Tabelle nichts und der Lauf
     ist rot. Das ist der Nachweis, den die Rollenregel verlangt -- eine Dauereinrichtung
     im Programm und kein Protokoll daneben.

**Drei Rueckgabewerte, und der Unterschied ist der Zweck dieser Datei:**

    0  gruen -- Kommentar und Messung stimmen ueberein.
    1  **Befund** -- gemessen wurde, und eine Zahl weicht ab.
    2  **Messgeraet ohne Messung** -- eine Nadel trifft nicht mehr, etwas uebersetzt
       nicht, der Riegel druckt seine Zahlenzeile nicht. Ein Lauf, der 2 gibt, sagt
       ueber den Riegel nichts, weder gut noch schlecht.

Gebaut wird ohne `-Werror`, aus demselben Grund wie bei Paket 0147: Beim Abschalten
faellt regelmaessig eine Groesse aus dem Spiel, und dann wuerde der Bau rot statt der
Messung. Die Sprachschalter sind die des Baulaufs.

Aufruf:  python3 messen.py [--vorhaben <wurzel>] [--uebersetzer <pfad>]
"""

import argparse
import os
import pathlib
import re
import subprocess
import sys

HIER = pathlib.Path(__file__).resolve()
VORHABEN_VORGABE = HIER.parents[2]

SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O2"]

ARBEITSNAME = "messung-0166"

QUELLE_IM_VORHABEN = "werkzeuge/belegstellen/belegstellen_riegel.cpp"


class Messfehler(Exception):
    """Der Stand kann nicht messen. Fuehrt zu Rueckgabe 2, nie zu 1."""


# --- Der Auswerter der Zahlenzeile ------------------------------------------------

ZAHLENZEILE = re.compile(
    r"(\d+) Zitate der geprueften Form gefunden, (\d+) davon aufgeloest "
    r"\(Untergrenze \d+\), (\d+) Fundstellen uebergangen")


def drei_zahlen(text):
    """Zitate, aufgeloest, uebergangen -- oder `None`, wenn der Riegel nicht bis zu
    seiner Zahlenzeile gekommen ist."""
    fund = ZAHLENZEILE.search(text)
    if fund is None:
        return None
    return (int(fund.group(1)), int(fund.group(2)), int(fund.group(3)))


# --- Der Auswerter der Tabelle im Kopfkommentar -----------------------------------
#
# Gelesen werden nur Zeilen, deren Name in `ZEILENNAMEN` steht. Ein Muster ohne diese
# Liste faenge auch die Markdown-Tabelle weiter oben im selben Kopf.

ZEILENNAMEN = ["keine von beiden", "nur der Wortabstand", "nur die Suche nach rechts",
               "beide", "Schwelle vier", "Schwelle fuenf"]

TABELLENZEILE = re.compile(
    r"^//!\s{2,}(?P<name>\S.*?\S)\s{2,}"
    r"(?P<a>[+-]?\d+)\s{2,}(?P<b>[+-]?\d+)\s{2,}(?P<c>[+-]?\d+)\s*$")


def lies_tabelle(text):
    """Die im Kopf aufgeschriebenen Zeilen als Name -> (a, b, c). Unbekannte Namen
    fallen weg, doppelte sind ein Grund zur Beanstandung weiter unten."""
    gelesen = {}
    for zeile in text.splitlines():
        fund = TABELLENZEILE.match(zeile)
        if fund is None:
            continue
        name = fund.group("name")
        if name not in ZEILENNAMEN:
            continue
        werte = (int(fund.group("a")), int(fund.group("b")), int(fund.group("c")))
        if name in gelesen and gelesen[name] != werte:
            gelesen[name] = None  # zweimal verschieden -- weiter unten ein Befund
        else:
            gelesen[name] = werte
    return gelesen


def vergleiche_kommentar(text, unterschiede):
    """Haelt die Tabelle im Kopf gegen die gemessenen Unterschiede.

    Rueckgabe: die Liste der Beanstandungen, leer heisst gruen. Sie **wirft** nicht --
    eine Abweichung ist ein Befund und kein blindes Messgeraet. Nur der Fall "gar keine
    Zeile lesbar" ist ein `Messfehler`, denn dann ist nichts verglichen worden.
    """
    gelesen = lies_tabelle(text)
    if not gelesen:
        raise Messfehler("im Kopfkommentar steht keine einzige lesbare Zeile der "
                         "Tabelle -- verglichen wurde nichts.")
    klagen = []
    for name in ZEILENNAMEN:
        if name not in gelesen:
            klagen.append("die Zeile '" + name + "' fehlt im Kopfkommentar")
            continue
        if gelesen[name] is None:
            klagen.append("die Zeile '" + name + "' steht zweimal mit verschiedenen "
                          "Zahlen im Kopfkommentar")
            continue
        if gelesen[name] != unterschiede[name]:
            klagen.append("die Zeile '" + name + "' sagt " + str(gelesen[name])
                          + ", gemessen wurde " + str(unterschiede[name]))
    return klagen


def einmal_ersetzen(text, alt, neu):
    """Ersetzt `alt` durch `neu` und besteht darauf, dass `alt` **genau einmal**
    vorkommt.

    Die einzige Stelle, an der dieser Stand merkt, dass sein Gegenstand weggewandert
    ist. Sie **wirft** und ruft nicht `sys.exit`, damit daraus die Rueckgabe 2 wird und
    nicht die 1: Eine nicht mehr treffende Nadel ist kein Befund ueber den Riegel,
    sondern ein blindes Messgeraet.
    """
    anzahl = text.count(alt)
    if anzahl != 1:
        raise Messfehler("der erwartete Wortlaut kommt " + str(anzahl)
                         + "-mal vor, erwartet genau einmal")
    return text.replace(alt, neu)


# --- Die Nadeln -------------------------------------------------------------------
#
# Alle vier greifen so an, dass **kein Fall des Selbsttests reisst** -- sonst bricht der
# Riegel mit 2 ab, ehe er den Bestand liest, und es entsteht keine Zahl.

# Die Suche nach rechts, abgeschaltet an ihrer Aufrufstelle im Lauf ueber den Bestand.
# `verweis_rechts` selbst bleibt stehen und wird von Fall 6 bis 8 in ABSTANDSFAELLE
# weiterhin unmittelbar gemessen; deshalb bleibt der Selbsttest gruen.
RECHTS_ALT = """            if (!gefunden && !ohne_anfuehrung) {
                // Paket 0086: der Dokumentname rechts vom Zitat. Nur als Rueckfall,
                // damit die gemessene Linksregel den Vorrang behaelt.
                gefunden = verweis_rechts(absatz.text, i + schluessel + zitatteil, name,
                                          netzadresse);
            }
"""
RECHTS_NEU = """            // Messung 0166: die Suche nach rechts ist hier abgeschaltet.
"""

# Der Wortabstand, abgeschaltet an derselben Stelle: Die Form wird weiterhin gewaehlt --
# `FORMFAELLE` misst genau diese Wahl und bliebe sonst rot --, aber der Lauf ueber den
# Bestand behandelt sie wie "keine Fundstelle" und rueckt genauso weiter wie dort.
ABSTAND_ALT = """            const Formwahl wahl = waehle_zitatform(absatz, i + schluessel);
            if (wahl.form == Zitatform::Keine) {
"""
ABSTAND_NEU = """            const Formwahl wahl = waehle_zitatform(absatz, i + schluessel);
            if (wahl.form == Zitatform::Keine
                || wahl.form == Zitatform::MitAbstand) {  // Messung 0166
"""

# Die Schwelle. Vier statt fuenf laesst Fall 1 in ABSTANDSFAELLE reissen -- er ist die
# gemessene Form mit fuenf Woertern Abstand --, und ein gerissener Fall beendet den Lauf
# mit 2. Die Fassung "Schwelle vier" stellt deshalb zugleich die Erwartung jenes Falls
# auf das, was in einer Welt mit der Schwelle vier richtig waere: nichts gefunden.
SCHWELLE_ALT = "constexpr std::size_t WORTABSTAND_HOECHSTENS = 5;\n"
SCHWELLE_NEU4 = "constexpr std::size_t WORTABSTAND_HOECHSTENS = 4;\n"

FALL1_ALT = ('     "T46 -- Die elf Adressen, deren Herkunft dieses Dokument ist, '
             'abschliessend",\n     "technik.md",\n')
FALL1_NEU = '     "",\n     "",\n'

# --- Die sechs Fassungen ----------------------------------------------------------
#
# `beide` ist die unveraenderte Fassung und damit der Nullpunkt, gegen den die anderen
# fuenf gerechnet werden. `Schwelle fuenf` ist wortgleich mit `nur der Wortabstand`, und
# das ist keine Nachlaessigkeit, sondern die Aussage selbst: Die ausgelieferte Schwelle
# **ist** fuenf. Der Stand prueft die Wortgleichheit unten nach, statt sie anzunehmen.

FASSUNGEN = [
    {"name": "ohne-abstand", "zeile": "keine von beiden",
     "was": "keine der beiden Lockerungen",
     "ersetzungen": [(ABSTAND_ALT, ABSTAND_NEU), (RECHTS_ALT, RECHTS_NEU)]},
    {"name": "nur-abstand", "zeile": "nur der Wortabstand",
     "was": "nur der Wortabstand, die Suche nach rechts abgeschaltet",
     "ersetzungen": [(RECHTS_ALT, RECHTS_NEU)]},
    {"name": "nur-rechts", "zeile": "nur die Suche nach rechts",
     "was": "nur die Suche nach rechts, der Wortabstand abgeschaltet",
     "ersetzungen": [(ABSTAND_ALT, ABSTAND_NEU)]},
    {"name": "beide", "zeile": "beide",
     "was": "die unveraenderte Fassung -- der Nullpunkt",
     "ersetzungen": []},
    {"name": "abstand4", "zeile": "Schwelle vier",
     "was": "Schwelle vier, sonst wie 'nur der Wortabstand'",
     "ersetzungen": [(RECHTS_ALT, RECHTS_NEU), (SCHWELLE_ALT, SCHWELLE_NEU4),
                     (FALL1_ALT, FALL1_NEU)]},
    {"name": "abstand5", "zeile": "Schwelle fuenf",
     "was": "Schwelle fuenf, sonst wie 'nur der Wortabstand'",
     "ersetzungen": [(RECHTS_ALT, RECHTS_NEU)]},
]

# --- Die Rueckersetzung auf die Fassung vor Paket 0166 -----------------------------
#
# Die **ganzen** zwei Bloecke, die Paket 0166 angefasst hat, und keine Zeile weniger.
# Ein Halbstueck davon gaebe ein `vorher`, das es nie gab -- alten Kopf mit neuem Rumpf.
# Der Preis ist Sproedigkeit: Wer eine dieser Zeilen berichtigt, macht die Nadel stumpf
# und diesen Stand mit Rueckgabe 2 blind. Das ist der richtige Ausgang: Er sagt dann,
# dass er nicht messen konnte, statt eine erfundene Vorfassung zu vergleichen.

BLOCK1_NACHHER = """//! **Dass keine der beiden Lockerungen allein genuegt, ist gemessen und nicht
//! nachgesprochen.** Sechs Fassungen, alle im selben Aufruf ueber denselben Baum, und
//! die Messung laeuft bei **jedem** Bau: Der Messstand zu Paket 0166 baut die sechs,
//! misst sie und haelt sie gegen diese Tabelle; weicht eine Zahl ab, wird der Bau rot.
//! Den Stand, an dem gemessen wurde, druckt er dabei mit.
//!
//! Aufgeschrieben ist der **Unterschied zur unveraenderten Fassung**, nicht die
//! Grundzahl -- und auch das ist gemessen und nicht vorsorglich. Hier standen bis zum
//! 2026-09-07 die Grundzahlen vom 2026-09-05 (33/33/58 bis 34/34/58). Am 2026-09-06,
//! Stand 5d5e2d6, gab derselbe Satz Mutanten 39/39/47 bis 40/40/47: Jede der zwoelf
//! Zahlen war beim Aufschreiben richtig und einen Tag darauf falsch, waehrend die
//! Unterschiede zwischen den Fassungen an beiden Tagen dieselben blieben. Die Grundzahl
//! druckt der Riegel in jedem Lauf selbst; sie hier zu wiederholen heisst, sie in dem
//! Augenblick zu faelschen, in dem der naechste Lauf ueber den Baum geht.
//!
//!     Fassung                    Zitate  aufgeloest  uebergangen
//!     keine von beiden               -1          -1            0
//!     nur der Wortabstand            -1          -1           +1
//!     nur die Suche nach rechts      -1          -1            0
//!     beide                           0           0            0
//!     Schwelle vier                  -1          -1            0
//!     Schwelle fuenf                 -1          -1           +1
//!
//! Jede Zeile ist der Unterschied zu "beide", also zur unveraenderten Fassung; deren
//! eigene Zeile ist damit der Nullpunkt und keine Messung. Die beiden Schwellenzeilen
//! gehoeren zu dem Wert weiter unten und sind gebaut wie "nur der Wortabstand", die
//! Suche nach rechts also abgeschaltet -- sonst waere der Unterschied zwischen vier und
//! fuenf an keiner der drei Zahlen zu sehen. Wie jede der sechs gebaut wird, steht im
//! Messstand als Textersetzung da und nicht als Beschreibung.
//!
//! Der Wortabstand macht die Stelle **sichtbar** -- sie wandert unter die uebergangenen
//! Fundstellen, weil links kein Dokumentname steht. Die Suche nach rechts macht sie
//! **aufloesbar**. Allein traegt keine ein einziges Zitat; die Rechtssuche allein
//! aendert nicht eine Zahl, und das ist zugleich der Beleg, dass sie keine vorhandene
//! Zuordnung umhaengt. Zusammen sind es genau ein Zitat mehr und keine Fundstelle mehr.
"""

BLOCK1_VORHER = """//! **Dass keine der beiden Lockerungen allein genuegt, ist gemessen und nicht
//! nachgesprochen.** Am selben Baum, am 2026-09-05, je ein Mutant:
//!
//!     Fassung                   Zitate  aufgeloest  uebergangen
//!     keine von beiden              33          33           58
//!     nur der Wortabstand           33          33           59
//!     nur die Suche nach rechts     33          33           58
//!     beide                         34          34           58
//!
//! Der Wortabstand macht die Stelle **sichtbar** -- sie wandert unter die uebergangenen
//! Fundstellen, weil ihr Absatz links keinen Dokumentnamen nennt. Die Suche nach rechts
//! macht sie **aufloesbar**. Allein traegt keine ein einziges Zitat; die Rechtssuche
//! allein aendert nicht eine Zahl, und das ist zugleich der Beleg, dass sie keine
//! vorhandene Zuordnung umhaengt. Zusammen sind es genau ein Zitat mehr und keine
//! Fundstelle mehr.
"""

BLOCK2_NACHHER = """//! **Die Schwelle fuenf ist gemessen.** Bei vier bleibt die Stelle ungefangen: Die
//! Fassung "Schwelle vier" oben steht Zahl fuer Zahl auf "keine von beiden". Bei fuenf
//! faellt sie unter die uebergangenen Fundstellen, und dieselbe Fassung steht dann auf
//! "nur der Wortabstand" -- ein Zitat gewinnt sie damit noch nicht, dafuer braucht es
//! die Suche nach rechts dazu. Gewaehlt ist deshalb der kleinste Wert, der die
//! gemessene Stelle traegt, und nicht der groesste, der noch nichts kaputt macht.
//!
//! **Was hier nicht mehr mitgemessen wird, damit es niemand fuer gemessen haelt:** dass
//! sechs und acht gegenueber fuenf nichts aendern und der Bestand zwischen fuenf und
//! acht Woertern keine weitere Form fuehrt. Das ist am 2026-09-05 gemessen und seither
//! nicht wiederholt worden; der Messstand zu Paket 0166 baut die Schwellen vier und
//! fuenf und sagt ueber sechs und acht nichts.
"""

BLOCK2_VORHER = """//! **Die Schwelle fuenf ist gemessen.** Bei vier bleibt die Stelle ungefangen (58
//! Fundstellen wie ohne die Lockerung), bei fuenf faellt sie an (59); sechs und acht
//! aendern gegenueber fuenf nichts mehr -- der Bestand fuehrt zwischen fuenf und acht
//! Woertern keine weitere Form. Gewaehlt ist deshalb der kleinste Wert, der die
//! gemessene Stelle traegt, und nicht der groesste, der noch nichts kaputt macht.
"""


def baue_vorher(text):
    """Die Fassung vor Paket 0166, aus der heutigen zurueckgerechnet."""
    zwischen = einmal_ersetzen(text, BLOCK1_NACHHER, BLOCK1_VORHER)
    return einmal_ersetzen(zwischen, BLOCK2_NACHHER, BLOCK2_VORHER)


# --- Die Selbstprobe des Auswerters -----------------------------------------------

PROBE_KOPF = """//! irgendein Satz davor, der keine Zahl traegt.
//!
//!     Fassung                    Zitate  aufgeloest  uebergangen
//!     keine von beiden               -1          -1            0
//!     nur der Wortabstand            -1          -1           +1
//!     nur die Suche nach rechts      -1          -1            0
//!     beide                           0           0            0
//!     Schwelle vier                  -1          -1            0
//!     Schwelle fuenf                 -1          -1           +1
//!
//! | | ohne Schranke | mit Schranke |
//! |---|---|---|
//! | Zitate | 36 | 35 |
"""

PROBE_ERWARTET = {
    "keine von beiden": (-1, -1, 0),
    "nur der Wortabstand": (-1, -1, 1),
    "nur die Suche nach rechts": (-1, -1, 0),
    "beide": (0, 0, 0),
    "Schwelle vier": (-1, -1, 0),
    "Schwelle fuenf": (-1, -1, 1),
}

PROBE_ZAHLENZEILE = (
    "belegstellen_riegel, Bedingung 2 (Abschnittszitat): 53 Bauquellen und 13 "
    "Datendokumente gelesen, 209 Dateien im Zielbestand, 15591 Pfade in ungelesenen "
    "Ordnern; 40 Zitate der geprueften Form gefunden, 40 davon aufgeloest (Untergrenze "
    "16), 47 Fundstellen uebergangen.\n")


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

    # 1. Der Auswerter liest die sechs Zeilen -- und **nur** sie. Die Markdown-Tabelle
    #    im Probetext steht mit Absicht darunter: Sie traegt ebenfalls Zahlen, und ein
    #    Muster ohne die Namensliste faenge sie mit.
    gelesen = lies_tabelle(PROBE_KOPF)
    haelt(gelesen == PROBE_ERWARTET,
          "alle sechs Zeilen werden gelesen und keine fremde dazu.",
          "der Auswerter liest " + str(gelesen) + ", erwartet war "
          + str(PROBE_ERWARTET) + ".")

    # 2. Er muss **nein** sagen koennen -- an einer falschen Zahl und an einer fehlenden
    #    Zeile. Ohne diese beiden Proben waere ein Auswerter, der immer zustimmt, von
    #    einem richtigen nicht zu unterscheiden.
    try:
        stumm = vergleiche_kommentar(PROBE_KOPF, PROBE_ERWARTET)
    except Messfehler as grund:
        stumm = ["Messfehler: " + str(grund)]
    haelt(stumm == [], "der Vergleich schweigt, wo alles stimmt.",
          "der Vergleich beanstandet etwas an einem richtigen Kopf: " + str(stumm))

    falsch = dict(PROBE_ERWARTET)
    falsch["Schwelle fuenf"] = (-1, -1, 0)
    try:
        laut = vergleiche_kommentar(PROBE_KOPF, falsch)
    except Messfehler as grund:
        laut = ["Messfehler: " + str(grund)]
    haelt(len(laut) == 1 and "Schwelle fuenf" in laut[0],
          "eine falsche Zahl wird genau einmal und namentlich beanstandet.",
          "eine falsche Zahl gibt " + str(laut) + ".")

    # Die Zeile wird ueber ihren Namen entfernt und nicht ueber einen abgeschriebenen
    # Wortlaut: Eine abgeschriebene Zeile, deren Leerraum um ein Zeichen danebenliegt,
    # entfernt nichts -- und die Probe waere dann gruen, ohne etwas zu pruefen.
    ohne_zeile = "\n".join(z for z in PROBE_KOPF.splitlines()
                           if "Schwelle vier" not in z) + "\n"
    try:
        vermisst = vergleiche_kommentar(ohne_zeile, PROBE_ERWARTET)
    except Messfehler as grund:
        vermisst = ["Messfehler: " + str(grund)]
    haelt(len(vermisst) == 1 and "fehlt" in vermisst[0],
          "eine fehlende Zeile wird beanstandet und nicht ueberlesen.",
          "eine fehlende Zeile gibt " + str(vermisst) + ".")

    # 3. Der Auswerter der Zahlenzeile, an einer echten Zeile und an einer leeren.
    haelt(drei_zahlen(PROBE_ZAHLENZEILE) == (40, 40, 47),
          "die Zahlenzeile des Riegels wird gelesen.",
          "die Zahlenzeile wird als " + str(drei_zahlen(PROBE_ZAHLENZEILE))
          + " gelesen, erwartet war (40, 40, 47).")
    haelt(drei_zahlen("belegstellen_riegel: Selbsttest bestanden.\n") is None,
          "eine Ausgabe ohne Zahlenzeile gibt nichts her.",
          "der Auswerter findet in einer Ausgabe ohne Zahlenzeile etwas.")

    # 4. `einmal_ersetzen`, dreimal: fehlt / zweimal / genau einmal. Die Nadel des
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


def laufe(programm, vorhaben):
    fertig = subprocess.run([str(programm), str(vorhaben)],
                            capture_output=True, text=True)
    return fertig.returncode, fertig.stdout, fertig.stderr


def baue_und_miss(uebersetzer, arbeit, vorhaben, name, text):
    """Uebersetzt `text`, laesst ihn ueber den Baum laufen und gibt die drei Zahlen.

    Der Rueckgabewert des Riegels ist hier **kein** Kriterium: Eine abgeschaltete
    Lockerung darf durchaus einen Befund erzeugen, und die Zahlen stehen trotzdem da.
    Fehlt die Zahlenzeile, ist nichts gemessen -- das ist ein `Messfehler`.
    """
    quelle = arbeit / (name + ".cpp")
    programm = arbeit / name
    quelle.write_text(text, encoding="utf-8")
    uebersetze(uebersetzer, quelle, programm)
    rc, aus, err = laufe(programm, vorhaben)
    zahlen = drei_zahlen(aus)
    if zahlen is None:
        raise Messfehler(
            "die Fassung '" + name + "' ist nicht bis zu ihrer Zahlenzeile gekommen "
            "(Rueckgabe " + str(rc) + "). Sie hat damit nichts gemessen.\n"
            "  stderr (Ende): " + err[-1500:])
    return rc, zahlen


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
    nachher_text = quelldatei.read_text(encoding="utf-8")

    arbeit = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / ARBEITSNAME
    arbeit.mkdir(parents=True, exist_ok=True)

    print("Messstand 0166 -- die sechs Fassungen des Wortabstands")
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

    # Jede Nadel **vor** der ersten Uebersetzung. Eine, die ihren Gegenstand verloren
    # hat, kostet hier eine Sekunde und weiter unten sechs Uebersetzungen.
    stumpf = []
    for fassung in FASSUNGEN:
        for alt, neu in fassung["ersetzungen"]:
            try:
                einmal_ersetzen(nachher_text, alt, neu)
            except Messfehler as grund:
                stumpf.append(fassung["name"] + ": " + str(grund))
    try:
        vorher_text = baue_vorher(nachher_text)
    except Messfehler as grund:
        stumpf.append("Rueckersetzung auf die Fassung vor 0166: " + str(grund))
        vorher_text = None
    if stumpf:
        raise Messfehler("Nadeln treffen ihren Gegenstand nicht mehr:\n  - "
                         + "\n  - ".join(stumpf))
    print("OK  Selbstprobe: alle Nadeln treffen genau einmal.")
    print("")

    # --- Teil 1: der Vorlauf -----------------------------------------------------
    print("Teil 1 -- der Vorlauf: die Fassung vor 0166 und die danach")
    rc_vorher, zahlen_vorher = baue_und_miss(uebersetzer, arbeit, vorhaben,
                                             "riegel-vorher", vorher_text)
    rc_nachher, zahlen_nachher = baue_und_miss(uebersetzer, arbeit, vorhaben,
                                               "riegel-nachher", nachher_text)
    print("[vorher ] Rueckgabe " + str(rc_vorher) + ", Zahlen " + str(zahlen_vorher))
    print("[nachher] Rueckgabe " + str(rc_nachher) + ", Zahlen " + str(zahlen_nachher))
    if zahlen_vorher == zahlen_nachher:
        print("GLEICH  die drei Zahlen von Bedingung 2.")
    else:
        print("ABWEICHUNG: die Aenderung ist nicht wirkungsfrei.")
        befunde += 1
    print("")

    # --- Teil 2: die sechs Fassungen ---------------------------------------------
    print("Teil 2 -- die sechs Fassungen")
    gemessen = {}
    fassungstext = {}
    for fassung in FASSUNGEN:
        text = nachher_text
        for alt, neu in fassung["ersetzungen"]:
            text = einmal_ersetzen(text, alt, neu)
        fassungstext[fassung["name"]] = text

        # Wortgleiche Fassungen werden einmal uebersetzt und nicht zweimal. Das trifft
        # heute zweimal zu: `beide` ist der Auslieferungsstand und damit die Fassung, die
        # in Teil 1 schon gelaufen ist, und `abstand5` ist wortgleich mit `nur-abstand`.
        # Das zweite ist keine Sparsamkeit, sondern die Aussage selbst: Die ausgelieferte
        # Schwelle **ist** fuenf. Nachgesehen wird die Gleichheit jedesmal und nicht
        # angenommen -- faellt sie weg, wird eben uebersetzt.
        zwilling = None
        if text == nachher_text:
            zwilling = "riegel-nachher aus Teil 1"
            rc, zahlen = rc_nachher, zahlen_nachher
        else:
            for frueher in FASSUNGEN:
                if frueher["name"] == fassung["name"]:
                    break
                if fassungstext[frueher["name"]] == text:
                    zwilling = frueher["name"]
                    rc, zahlen = gemessen[zwilling]
                    break

        if zwilling is not None:
            print("    " + fassung["name"].ljust(13) + " wortgleich mit " + zwilling
                  + " -- dieselbe Messung, nicht noch einmal uebersetzt.")
        else:
            rc, zahlen = baue_und_miss(uebersetzer, arbeit, vorhaben,
                                       "riegel-" + fassung["name"], text)
        gemessen[fassung["name"]] = (rc, zahlen)
        print("    " + fassung["name"].ljust(13) + " Rueckgabe " + str(rc)
              + ", Zahlen " + str(zahlen) + "  -- " + fassung["was"])
    print("")

    zahlen_von = {marke: paar[1] for marke, paar in gemessen.items()}
    grundzahl = zahlen_von["beide"]
    unterschiede = {}
    for fassung in FASSUNGEN:
        zahlen = zahlen_von[fassung["name"]]
        unterschiede[fassung["zeile"]] = tuple(zahlen[k] - grundzahl[k]
                                               for k in range(3))
    print("Grundzahl (unveraenderte Fassung): " + str(grundzahl))
    print("Unterschiede:")
    for name in ZEILENNAMEN:
        print("    " + name.ljust(26) + str(unterschiede[name]))
    print("")

    # --- Teil 3: der Kopfkommentar, und der Rotnachweis daneben ------------------
    print("Teil 3 -- der Kopfkommentar gegen die Messung")
    klagen = vergleiche_kommentar(nachher_text, unterschiede)
    if klagen:
        befunde += len(klagen)
        for klage in klagen:
            print("ROT " + klage)
    else:
        print("OK  alle sechs Zeilen des Kopfkommentars stimmen mit der Messung.")

    # Der Rotnachweis: derselbe Vergleich gegen den Kopf **vor** dieser Aenderung. Er
    # muss dort etwas finden; findet er nichts, misst die ganze Tabelle nichts.
    try:
        alt_klagen = vergleiche_kommentar(vorher_text, unterschiede)
    except Messfehler as ausfall:
        alt_klagen = ["Messfehler: " + str(ausfall)]
    if alt_klagen:
        print("OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich "
              + str(len(alt_klagen)) + " Beanstandung(en):")
        for klage in alt_klagen[:3]:
            print("      " + klage)
    else:
        print("ROT Rotnachweis: der Vergleich beanstandet am Kopf vor Paket 0166 "
              "nichts. Er kann nicht rot werden und misst damit nichts.")
        befunde += 1
    print("")

    # --- Teil 4: die Aussage, an den neuen Zahlen nachgerechnet ------------------
    #
    # Nicht aus dem Kopf uebernommen, sondern aus dem hier Gemessenen neu hergeleitet.
    print("Teil 4 -- die Aussage des Kopfes, an den gemessenen Zahlen nachgerechnet")
    for satz, gut in [
        ("keine Lockerung allein traegt ein Zitat",
         all(zahlen_von[n][0] < zahlen_von["beide"][0]
             for n in ("ohne-abstand", "nur-abstand", "nur-rechts"))),
        ("die Suche nach rechts allein aendert keine der drei Zahlen",
         zahlen_von["nur-rechts"] == zahlen_von["ohne-abstand"]),
        ("die Schwelle vier faengt die Stelle nicht",
         zahlen_von["abstand4"] == zahlen_von["ohne-abstand"]),
        ("die Schwelle fuenf faengt sie -- eine uebergangene Fundstelle mehr",
         zahlen_von["abstand5"][2] == zahlen_von["abstand4"][2] + 1),
    ]:
        if gut:
            print("OK  " + satz)
        else:
            print("ROT " + satz)
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
        print("Messstand 0166: NICHT GEMESSEN -- " + str(grund))
        print("Rueckgabe 2. Dieser Lauf sagt ueber den Riegel nichts, weder gut noch "
              "schlecht.")
        return 2

    if befunde == 0:
        print("Messstand 0166: alles wie erwartet.")
        return 0
    print("Messstand 0166: " + str(befunde) + " Abweichung(en).")
    return 1


if __name__ == "__main__":
    sys.exit(main())
