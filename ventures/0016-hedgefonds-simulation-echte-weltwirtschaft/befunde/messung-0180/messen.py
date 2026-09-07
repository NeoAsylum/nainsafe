#!/usr/bin/env python3
"""Messung zu Paket 0180, auf den Stand nach 0194 nachgezogen in Paket 0199.

Laeuft als Probe `zahlwort_messung` unter `ctest`. Von Hand, aus beliebigem
Verzeichnis -- die Wurzel des Vorhabens kommt aus dem eigenen Pfad:

    python3 befunde/messung-0180/messen.py [--uebersetzer <pfad>]

Das Skript ist selbst ein Riegel und kein Bericht: Zu jedem Fall steht die Erwartung
hier im Skript, und bei der ersten Abweichung endet der Lauf mit Code 1. Wer nur die
Ausgabe liest, liest ein Ergebnis; wer den Code liest, liest ein Urteil.

Gemessen werden zwei Sorten Fall, und sie beantworten zwei verschiedene Fragen:

  **Teil A -- wird der Riegel rot, wenn die Datei falsch wird?** Drei Staende von
  `werte.hpp`, jeder in einer eigenen Wegwerfwurzel, dazu der heutige Stand als
  Gegenprobe. Das ist Abnahmebedingung 2 von Paket 0180.

  **Teil B -- wird der Selbsttest rot, wenn der Riegel falsch wird?** Fuenf Mutanten
  des Quelltextes, je einer gegen eine der fuenf Tabellen. Zu jedem steht hier, welche
  Faelle reissen muessen -- **namentlich** und vollstaendig. Ein Mutant, bei dem eine
  fremde Tabelle mitreisst, ist genauso ein Fehlschlag wie einer, bei dem gar nichts
  reisst: Im ersten Fall misst die Tabelle nicht, was sie zu messen vorgibt.

Der fuenfte Mutant ist der wichtigste. Er verstellt **nur die Verdrahtung** -- die
Zaehlung wird an die falsche Sorte gebunden -- und laesst jeden Baustein unberuehrt.
Die vier Bausteintabellen bleiben deshalb gruen, und nur die fuenfte reisst. Genau das
ist ihre Rechtfertigung.

## Die Faelle heissen bei ihrem Wortlaut und nicht bei ihrer Nummer

Bis 0194 stand hier `("Behauptung", "17")`. Dann hat 0194 zwei Faelle an Stelle 12 und
13 eingesetzt, und aus 17 wurde 19 -- die Erwartung stimmte weiter, zeigte aber auf den
falschen Fall. Eine Fallnummer ist ein Messwert ihres Zuschnittstags.

Erwartet wird deshalb ein **Teilwortlaut des `was`**, das jeder Fall im Riegel traegt
und das in jeder seiner Meldungen steht. Aufgeloest wird gegen die Meldung selbst:
Jeder erwartete Wortlaut muss auf **genau einen** gerissenen Fall passen, und jeder
gerissene Fall muss von genau einem Wortlaut getroffen sein. Wird ein Fall umformuliert,
reisst die Messung laut; wird er umnummeriert, merkt sie es gar nicht -- und das ist
richtig so. Die aufgeloeste Nummer steht in der Ausgabe, damit sie lesbar bleibt.

## Der Uebersetzer kommt von aussen

Uebersetzt wird unmittelbar, weil ein Mutant nicht in den Quellbaum gehoert und
`add_test` keine Wegwerfwurzel als Argument hergibt. Welcher Uebersetzer, sagt CMake
ueber `--uebersetzer ${CMAKE_CXX_COMPILER}`; ohne den Schalter `g++`. Ein fest
eingebautes `g++` waere ein zweiter Uebersetzer neben dem, gegen den gebaut wird.

Die Sprachschalter sind dieselben wie in `werkzeugkette.cmake`, **ohne** die
Sanitizer und **ohne** `-Werror`: Ein Mutant soll am Selbsttest scheitern und nicht am
Warnsatz. Der Vergleichsstand wird mit denselben Schaltern gebaut, damit der
Unterschied zwischen ihm und einem Mutanten allein der Mutant ist.

## Die drei Rueckgabewerte

  * **2** -- die Messung hat gar nicht stattgefunden: die Selbstprobe unten ist
    verfehlt, es gibt keinen Uebersetzer, oder der Bezugsstand aus dem Verlauf ist
    nicht zu holen. Das ist kein Befund gegen den Riegel, sondern ein Messgeraet ohne
    Messung.
  * **1** -- ein Fall ist anders ausgegangen als erwartet, oder der Wortlaut eines
    Mutanten steht nicht mehr genau einmal im Riegel.
  * **0** -- jeder Fall ist ausgegangen wie erwartet.
"""

import os
import pathlib
import re
import shutil
import subprocess
import sys

VORHABEN = pathlib.Path(__file__).resolve().parents[2]
QUELLE = VORHABEN / "werkzeuge" / "zahlwort" / "zahlwort_riegel.cpp"
PRUEFLING_REL = pathlib.Path("kern") / "include" / "kern" / "werte.hpp"
PRUEFLING = VORHABEN / PRUEFLING_REL
VORSTAND = "b2829c8"

ARBEIT = pathlib.Path(os.environ.get("TMPDIR", "/tmp")) / "messung-0180"
SCHALTER = ["-std=c++20", "-fwrapv", "-fno-fast-math", "-O1", "-g"]

fehler = []


class Messfehler(Exception):
    """Der Messung ist ihr Gegenstand weggewandert -- kein Befund, sondern kein Messwert."""


def melde(satz):
    fehler.append(satz)
    print("  FEHLSCHLAG: " + satz)


def abbruch(satz):
    """Code 2: Die Messung konnte nicht stattfinden. Nicht dasselbe wie ein Befund."""
    print("\nmessen.py: " + satz, file=sys.stderr)
    raise SystemExit(2)


def einmal_ersetzen(text, alt, neu, wo):
    if text.count(alt) != 1:
        raise Messfehler(
            f"{wo}: '{alt[:60]}' kommt {text.count(alt)} mal vor, erwartet war genau "
            f"einmal. Der Wortlaut hat sich verschoben; die Messung waere gegenstandslos.")
    return text.replace(alt, neu)


# ---------------------------------------------------------------------------
# Die Selbstprobe -- der Rotnachweis dieses Skripts, bei jedem Aufruf
# ---------------------------------------------------------------------------
#
# `einmal_ersetzen` ist die einzige Stelle, an der diese Messung merkt, dass ihr
# Gegenstand weggewandert ist -- genau der Fall, der am 2026-09-07 eingetreten war und
# den niemand sah, weil das Skript in keinem `add_test` stand. Eine Schranke, von der
# niemand gezeigt hat, dass sie zuschlaegt, ist keine. Die Probe kostet keine
# Uebersetzung und laeuft deshalb vor allem anderen.

def selbstprobe():
    faelle = [
        ("Wortlaut fehlt", "aa bb", "cc", True, None),
        ("Wortlaut steht zweimal", "aa bb aa", "aa", True, None),
        ("Wortlaut steht genau einmal", "aa bb", "bb", False, "aa XX"),
    ]
    for name, text, alt, soll_reissen, soll_text in faelle:
        try:
            ergebnis = einmal_ersetzen(text, alt, "XX", "Selbstprobe")
            gerissen = False
        except Messfehler:
            ergebnis, gerissen = None, True
        if gerissen != soll_reissen:
            abbruch(f"Selbstprobe '{name}' ist verfehlt: einmal_ersetzen hat "
                    f"{'nicht ' if soll_reissen else ''}abgebrochen. Dieses Skript kann "
                    f"nicht mehr erkennen, dass sein Gegenstand weggewandert ist -- dann "
                    f"misst Teil B nichts und meldete es nicht.")
        if not gerissen and ergebnis != soll_text:
            abbruch(f"Selbstprobe '{name}' ist verfehlt: ersetzt wurde [{ergebnis}], "
                    f"erwartet war [{soll_text}].")
    print(f"  Selbstprobe: {len(faelle)} Faelle zu einmal_ersetzen, alle wie erwartet.")


# ---------------------------------------------------------------------------
# Werkzeug von aussen: Uebersetzer und Verlauf
# ---------------------------------------------------------------------------

def uebersetzer_aus(argumente):
    if not argumente:
        return "g++"
    if len(argumente) == 2 and argumente[0] == "--uebersetzer":
        return argumente[1]
    abbruch("Aufruf: messen.py [--uebersetzer <pfad>]\n"
            f"Bekommen: {argumente}")


def git(*argumente):
    try:
        lauf = subprocess.run(["git", *argumente], cwd=str(VORHABEN),
                              capture_output=True)
    except OSError as ursache:
        raise Messfehler(f"git ist nicht aufrufbar: {ursache}")
    if lauf.returncode != 0:
        raise Messfehler("git " + " ".join(argumente) + f" gab {lauf.returncode}: "
                         + lauf.stderr.decode("utf-8", "replace").strip())
    return lauf.stdout


def herkunft(*argumente):
    """Eine Herkunftsangabe und keine Bedingung -- ohne Verlauf steht hier 'unbekannt'."""
    try:
        return git(*argumente).decode("utf-8", "replace").strip()
    except Messfehler:
        return "unbekannt"


def uebersetze(quelltext, name):
    """Einen Quelltext nach `ARBEIT/<name>` uebersetzen und den Pfad zurueckgeben."""
    cpp = ARBEIT / (name + ".cpp")
    binaer = ARBEIT / name
    cpp.write_text(quelltext, encoding="utf-8")
    lauf = subprocess.run([UEBERSETZER, *SCHALTER, "-o", str(binaer), str(cpp)],
                          capture_output=True, text=True)
    if lauf.returncode != 0:
        print(lauf.stderr[-3000:], file=sys.stderr)
        abbruch(f"Mutant '{name}' liess sich nicht uebersetzen -- die Messung waere "
                f"gegenstandslos.")
    return binaer


def rufe(binaer, wurzel):
    lauf = subprocess.run([str(binaer), str(wurzel)], capture_output=True, text=True)
    return lauf.returncode, lauf.stdout, lauf.stderr


def wurzel_mit(name, inhalt):
    """Eine Wegwerfwurzel, die nichts als den Pruefling traegt."""
    wurzel = ARBEIT / name
    ziel = wurzel / PRUEFLING_REL
    ziel.parent.mkdir(parents=True, exist_ok=True)
    ziel.write_text(inhalt, encoding="utf-8")
    return wurzel


# Jede Selbsttestmeldung des Riegels hat diese Form -- Tabelle, Nummer, `was`.
GERISSEN = re.compile(r"Selbsttest (\w+), Fall (\d+) \((.*?)\):")


def gerissene_faelle(text):
    return [(tab, int(nr), was) for tab, nr, was in GERISSEN.findall(text)]


def ordne_zu(name, erwartet, beobachtet):
    """Erwartete Teilwortlaute gegen gerissene Faelle -- eine Zuordnung, kein Vergleich.

    Verlangt wird eine Bijektion: jeder erwartete Wortlaut trifft genau einen
    gerissenen Fall, und kein gerissener Fall bleibt uebrig. Beide Richtungen einzeln
    gemeldet -- 'zu wenig gerissen' und 'zu viel gerissen' sind verschiedene Fehler.
    """
    offen = list(beobachtet)
    aufgeloest = []
    for tabelle, teil in erwartet:
        treffer = [b for b in offen if b[0] == tabelle and teil in b[2]]
        if len(treffer) == 1:
            offen.remove(treffer[0])
            aufgeloest.append(f"{treffer[0][0]} {treffer[0][1]}")
            continue
        aufgeloest.append(f"{tabelle} ?")
        melde(f"{name}: '{teil}' passt in Tabelle {tabelle} auf {len(treffer)} "
              f"gerissene Faelle, erwartet war genau einer")
    for tabelle, nr, was in offen:
        melde(f"{name}: Selbsttest {tabelle}, Fall {nr} ({was}) ist gerissen, ohne "
              f"erwartet zu sein -- eine fremde Tabelle misst mit")
    return aufgeloest


# ---------------------------------------------------------------------------
# Der Stand, gegen den gemessen wird
# ---------------------------------------------------------------------------

selbstprobe()
UEBERSETZER = uebersetzer_aus(sys.argv[1:])

try:
    fassung = subprocess.run([UEBERSETZER, "--version"], capture_output=True, text=True)
except OSError as ursache:
    abbruch(f"'{UEBERSETZER}' ist nicht aufrufbar: {ursache}. Ohne Uebersetzer laesst "
            f"sich kein Mutant bilden, und ohne Mutant misst dieses Skript nichts.")
if fassung.returncode != 0:
    abbruch(f"'{UEBERSETZER} --version' gab {fassung.returncode}.")
KOPFZEILE = (fassung.stdout.splitlines() or ["ohne Fassungsangabe"])[0]

try:
    OBEN = pathlib.Path(git("rev-parse", "--show-toplevel").decode().strip())
    VORSTAND_PFAD = (VORHABEN.relative_to(OBEN) / PRUEFLING_REL).as_posix()
    vorher = git("show", f"{VORSTAND}:{VORSTAND_PFAD}").decode("utf-8")
except (Messfehler, ValueError) as ursache:
    abbruch(f"Der Stand vor 0155 ({VORSTAND}) ist nicht zu holen: {ursache}\n"
            f"Fall A3 misst den Riegel gegen einen wirklich dagewesenen Fehler; ohne "
            f"den Verlauf gibt es diesen Nachweis nicht. In einem Baum aus "
            f"`git archive` endet dieser Lauf deshalb mit 2 und nicht still ohne ihn.")

if ARBEIT.exists():
    shutil.rmtree(ARBEIT)
ARBEIT.mkdir(parents=True)

print("=" * 78)
print(f"Messung 0180, Stand HEAD {herkunft('rev-parse', 'HEAD')}")
print(f"  Pruefling  {PRUEFLING_REL}  Blob {herkunft('hash-object', str(PRUEFLING))}")
print(f"  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob "
      f"{herkunft('hash-object', str(QUELLE))}")
print(f"  Uebersetzer  {UEBERSETZER} -- {KOPFZEILE}")
print(f"  Arbeitsplatz {ARBEIT}")
print("=" * 78)

rein = QUELLE.read_text(encoding="utf-8")
heutig = PRUEFLING.read_text(encoding="utf-8")

vergleich = uebersetze(rein, "rein")

# ---------------------------------------------------------------------------
# Teil A -- wird der Riegel rot, wenn die Datei falsch wird?
# ---------------------------------------------------------------------------

print("\n## Teil A: der Riegel gegen vier Staende von werte.hpp\n")

try:
    # A0 -- die Gegenprobe. Ohne sie zeigt Teil A nur, dass der Riegel ueberhaupt rot
    # werden kann, und nicht, dass er es aus dem gemeinten Grund tut.
    A_FAELLE = [
        ("A0 heutiger Stand", heutig, 0, [],
         "Empfindlichkeitsprobe: mit einer weiteren Deklaration"),
        ("A1 Zahlwort im Kopf verstellt",
         einmal_ersetzen(heutig, "die zweiundzwanzig abgeleiteten Groessen",
                         "die einundzwanzig abgeleiteten Groessen", "A1"),
         1, ["Zeilennummer 2: 'einundzwanzig Groessen' nennt 21, gezaehlt sind 22"], ""),
        # A2 endet seit 0194 mit **2 und nicht mit 1**, und das ist ein Befund gegen den
        # Riegel und keine Eigenheit dieses Falles:
        #
        # Der Mutant setzt eine 23. Nummer ein. Damit wird die Behauptung 'dreiundzwanzig
        # Deklarationen' (Zeile 32) schon am Bestand rot -- rot_vorher der Sorte 3 ist 1.
        # Die Empfindlichkeitsprobe im Riegel verlangt danach `rot_nachher > rot_vorher`.
        # Es gibt aber nur *eine* Fundstelle der Sorte 3 in der Datei; sie ist schon rot
        # und kann nicht roeter werden. Die Probe schlaegt fehl, der Riegel gibt 2, und
        # seine Begruendung ("der Mutant bleibt an Sorte 3 gruen") sagt das Gegenteil des
        # Zutreffenden. Fuenf belegte Abweichungen -- vier an den Groessen (Zeilen 2, 16,
        # 32, 157) und eine an den Deklarationen (Zeile 32) -- werden dabei gar nicht
        # erst gedruckt.
        #
        # Die Erwartung steht so scharf da, wie der Zustand ist: Code 2 und dieser Satz.
        # Wer die Saettigung im Riegel behebt -- Vorschlag 0213 --, macht diesen Fall rot
        # und schreibt hier Code 1 mit den fuenf Abweichungen hin. Abgeschwaecht ist
        # nichts: vorher stand hier eine Erwartung ohne Grund, jetzt eine mit.
        ("A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen",
         einmal_ersetzen(
             heutig, "\n}  // namespace kern::werte\n",
             "\n/// **T48 Nr. 23** -- eine neue Groesse, und niemand zieht das Zahlwort nach.\n"
             "[[nodiscard]] zustand::i64 neuwert(const zustand::Zustand& z);\n"
             "\n}  // namespace kern::werte\n", "A2"),
         2, [], "der Mutant bleibt an Sorte 3 gruen"),
        (f"A3 Stand vor 0155 ({VORSTAND})", vorher, 1,
         ["Zeilennummer 73: 'eine Jahrgangskonstante[n]' nennt 1, gezaehlt sind 2"], ""),
    ]

    for name, inhalt, soll_code, soll_zeilen, soll_grund in A_FAELLE:
        wurzel = wurzel_mit(name.split()[0], inhalt)
        code, aus, err = rufe(vergleich, wurzel)
        gefunden = [z.strip() for z in err.splitlines()
                    if z.startswith("  Zeilennummer") or z.startswith("  Feld ")
                    or z.startswith("  Funktionsdeklaration ")]
        print(f"  {name}: Code {code} (erwartet {soll_code}), {len(gefunden)} Befunde")
        for z in gefunden:
            print(f"      {z}")
        if code != soll_code:
            melde(f"{name}: Code {code} statt {soll_code}")
        if gefunden != soll_zeilen:
            melde(f"{name}: Befunde weichen ab -- erwartet {soll_zeilen}")
        # Der Grund gehoert zur Erwartung: Ein Code allein sagt nicht, warum er kam --
        # und bei A2 kommt die 2 aus einer anderen Ecke als bei einem fehlenden Pruefling.
        if soll_grund and soll_grund not in (aus + err):
            melde(f"{name}: '{soll_grund}' steht in der Ausgabe nicht -- der Code stimmt, "
                  f"aber nicht aus dem erwarteten Grund")

    # -----------------------------------------------------------------------
    # Teil B -- wird der Selbsttest rot, wenn der Riegel falsch wird?
    # -----------------------------------------------------------------------

    print("\n## Teil B: fuenf Mutanten des Riegels gegen die fuenf Tabellen\n")

    B_FAELLE = [
        ("M1 die Artikelregel faellt weg",
         "if (i < abstand + 1\n                    "
         "|| !ist_bestimmter_artikel(worte[i - abstand - 1].text)) {",
         "if (false) {",
         None,
         [("Behauptung", "Kategorienzeile des Modulkopfes"),
          ("Behauptung", "mehrdeutige Form ueber ein Beiwort hinweg")]),
        ("M2 das Kardinalurteil ist immer gruen",
         "return b.zahl == gezaehlt ? Urteil::Gruen : Urteil::Rot;",
         "return Urteil::Gruen;",
         None,
         [("Urteil", "der Stand vor 0155"),
          ("Urteil", "Kardinalzahl zu gross"),
          ("Verdrahtung", "Sorte 1 weicht ab"),
          ("Verdrahtung", "Sorte 2 weicht ab"),
          ("Verdrahtung", "Sorte 1 zaehlt Nummern und nicht Deklarationen"),
          ("Verdrahtung", "Sorte 3 zaehlt Deklarationen und nicht Nummern")]),
        ("M3 jede Fundstelle bekommt eine eigene Nummer -- gezaehlt werden Zeilen",
         "hinein.insert(wert);",
         "hinein.insert(wert * 1000 + hinein.size());",
         None,
         [("Zaehlung", "gezaehlt werden Nummern und nicht Zeilen"),
          ("Verdrahtung", "der Bestandssatz im Kleinen"),
          ("Verdrahtung", "Sorte 1 zaehlt Nummern und nicht Deklarationen"),
          ("Verdrahtung", "Sorte 3 zaehlt Deklarationen und nicht Nummern")]),
        ("M4 eine wortlose Zeile trennt keinen Block mehr",
         "if (worte.empty()) {\n            if (!laufend.worte.empty()) {\n"
         "                bloecke.push_back(laufend);\n                laufend.worte.clear();\n"
         "            }\n            continue;\n        }",
         "if (worte.empty()) {\n            continue;\n        }",
         None,
         [("Bloecke", "die leere Kommentarzeile trennt"),
          ("Bloecke", "eine Codezeile trennt")]),
        # M5 sitzt seit 0194 in `zaehlung_zur_sorte()`; bis dahin stand die Bindung als
        # Bedingung mitten in der Schleife. Der Mutant ist derselbe geblieben -- die
        # Zaehlung an die falsche Sorte binden --, nur seine Stelle ist gewandert. Er
        # reisst heute sechs statt drei Faelle: Die drei Faelle von 0194 laufen auf dem
        # Kopf mit 2 Nummern in 3 Deklarationen, und genau dort trennt sich, welche
        # Zaehlung an welcher Sorte haengt. Dass die alten Mutanten die neuen Faelle
        # mitreissen, ist der Beleg, dass die neuen Faelle etwas messen.
        ("M5 die Zaehlung wird an die falsche Sorte gebunden",
         "    if (s == Sorte::Jahrgang) {\n        return z.jahrgang.size();\n    }\n"
         "    return z.deklarationen;",
         "    return z.nummern.size();",
         "Verdrahtung",
         [("Verdrahtung", "beide Behauptungen treffen"),
          ("Verdrahtung", "Sorte 2 weicht ab"),
          ("Verdrahtung", "eine Ordnungszahl jenseits der Zaehlung"),
          ("Verdrahtung", "der Bestandssatz im Kleinen"),
          ("Verdrahtung", "Sorte 1 zaehlt Nummern und nicht Deklarationen"),
          ("Verdrahtung", "Sorte 3 zaehlt Deklarationen und nicht Nummern")]),
    ]

    for nr, (name, alt, neu, nur_tabelle, soll) in enumerate(B_FAELLE, start=1):
        mutant = uebersetze(einmal_ersetzen(rein, alt, neu, name), f"m{nr}")
        code, aus, err = rufe(mutant, VORHABEN)
        ist = gerissene_faelle(err)
        print(f"  {name}")
        if code != 2:
            melde(f"{name}: Code {code} statt 2 -- der Selbsttest hat den Mutanten "
                  f"durchgelassen")
        aufgeloest = ordne_zu(name, soll, ist)
        print(f"      Code {code} (erwartet 2), gerissen: "
              f"{sorted(f'{t} {f}' for t, f, _ in ist) or 'nichts'}")
        print(f"      aufgeloest aus dem Wortlaut: {aufgeloest}")
        # Nur fuer M5, und deshalb als eigene Angabe im Fall und nicht als Fallnummer:
        # Sein Nachweis haengt daran, dass er keinen Baustein beruehrt.
        fremde = {t for t, _, _ in ist} - {nur_tabelle}
        if nur_tabelle and fremde:
            melde(f"{name}: fremde Tabellen mitgerissen ({sorted(fremde)}) -- der Nachweis "
                  f"fuer die Verdrahtungstabelle haengt daran, dass kein Baustein beruehrt ist")

    # -----------------------------------------------------------------------
    # Der Nachweis, dass der reine Stand nicht schon von selbst rot ist
    # -----------------------------------------------------------------------

    code, aus, err = rufe(vergleich, VORHABEN)
    print(f"\n  Gegenprobe, unveraenderter Riegel am heutigen Baum: Code {code} (erwartet 0)")
    if code != 0:
        melde(f"Der unveraenderte Riegel endet mit Code {code} statt 0")

except Messfehler as ursache:
    print(f"\nmessen.py: {ursache}", file=sys.stderr)
    shutil.rmtree(ARBEIT, ignore_errors=True)
    raise SystemExit(1)

shutil.rmtree(ARBEIT)

print()
print(f"Fehlschlaege: {len(fehler)}")
for f in fehler:
    print(f"  {f}")
sys.exit(1 if fehler else 0)
