#!/usr/bin/env python3
# Paket 0099 -- der Eingriff an daten/reihen.toml, als Skript statt von Hand,
# damit er wiederholbar ist und jede Ersetzung genau einmal greift.
# Drei Stellen: der Kommentar ueber [datei.vorlagen], die Tabelle selbst,
# und die Kennung dieses Pakets in datei.nachgezogen_durch.
import sys

PFAD = sys.argv[1]

ERSETZUNGEN = []

# --- 1. Kommentar ueber der Tabelle -------------------------------------
ERSETZUNGEN.append((
"""# Der Stand der fuenf Vorlagen, gegen den diese Datei geschrieben ist.
# Aendert sich eine davon, ist diese Datei nachzuziehen -- sie ist eine
# Uebertragung, keine zweite Messung.
#
# Der Schluessel `einheiten` ist mit Paket 0049 dazugekommen.""",
"""# Der Stand der sechs Vorlagen, gegen den diese Datei geschrieben ist.
# Aendert sich eine davon, ist diese Datei nachzuziehen -- sie ist eine
# Uebertragung, keine zweite Messung.
#
# Das Zahlwort ist gezaehlt und nicht fortgeschrieben: Die Tabelle
# unter diesem Kommentar fuehrt sechs Schluessel -- deckung, einheiten,
# lizenz_reihen, lizenz_wdi, preisbasis, reihenliste --, maschinell aus
# `datei.vorlagen` gelesen. Bis Paket 0099 stand hier "fuenf";
# hinzugekommen ist `preisbasis`.
#
# Warum `preisbasis` einen eigenen Schluessel bekommt, statt in
# `reihenliste` hineingeschrieben zu werden: Ein Schluessel traegt
# genau einen Stand. Abschnitt 7 und die Vorgabe T53 stehen in
# derselben Datei, aendern sich aber unabhaengig voneinander -- T53 ist
# erst mit der Fassung 7 dazugekommen --, und ein gemeinsamer Eintrag
# koennte nach einer Aenderung nicht sagen, welche der beiden gewandert
# ist. Ein verbreiterter Eintrag haette ausserdem keine Zahl geaendert
# und deshalb auch nichts ausgeloest.
#
# Was `preisbasis` deckt: Der zweite Umrechnungsblock der Reihe 14
# nimmt Deflator, Quelle, Basisjahr, Formel und Selbsttest aus T53;
# [[widerspruch]] Nr. 9 ist mit T53 als Fundstelle aufgeloest; Reihe 16
# nennt T53 in `quelle_eingebettet`, `begruendung` und `beleg`. Der
# Kopfkommentar fuehrt T53 seit Paket 0078 unter "Quellen dieser
# Datei"; in dieser Tabelle, die als einzige den Stand mitfuehrt und
# damit die Nachziehpflicht ausloest, fehlte er bis Paket 0099.
#
# Der Stand von technik.md ist die Zeile `fassung` im Frontmatter und
# nicht das Datum des letzten Commits. Ihre Schwaeche steht hier, damit
# sie niemanden ueberrascht: Die Fassung 7 ist mehrfach nachgebessert
# worden, ohne dass die Zahl gewachsen waere. Der Eintrag nennt deshalb
# beides, die Fassung und das Datum der Nachbesserung, mit der T53
# entstanden ist.
#
# Abschnitt 17 gehoert nicht in diese Tabelle, obwohl ein
# `offen`-Eintrag der Reihe 14 ihn zitiert. Er haelt den Umfang eines
# gelieferten Pakets fest (0026), ist also ein Bericht und kein
# Sollzustand; was er beschreibt, uebertraegt diese Datei nicht. Was an
# ihm haengt, ist ein Zitat, und dafuer ist der Belegstellenriegel das
# Werkzeug und nicht der Stand einer Vorlage.
#
# Gemessen und ausdruecklich nicht behoben: `reihenliste` ist der
# einzige der sechs Eintraege ohne Stand -- die anderen fuenf nennen
# einen, gezaehlt an den Werten der Tabelle. Ein Eintrag ohne Stand
# kann keine Nachziehpflicht ausloesen; dort fehlt der Tabelle also
# genau das, wozu es sie gibt. Welcher Stand fuer Abschnitt 7 der
# richtige ist, entscheidet dieses Paket nicht, es steht als Vorschlag
# 0141 in `aufgaben/`.
#
# Der Schluessel `einheiten` ist mit Paket 0049 dazugekommen."""))

# --- 2. die 0065-Zaehlung, neu gemessen ---------------------------------
ERSETZUNGEN.append((
"""# Beide Zahlwoerter sind mit Paket 0065 nachgezaehlt; vorher stand hier
# "vier Pakete" und "viermal als `beleg`", und beides war falsch.
# Gezaehlt ist so, damit es wiederholbar ist. Erstens: als `beleg`
# steht der Einheitenbefund **genau einmal** -- Blattwerte, deren
# Schluessel `beleg` heisst und die die Zeichenfolge
# einheitenbefund-pwt-baci enthalten, ergeben allein
# reihe.13.umrechnung.0.beleg, den ersten Umrechnungsblock der Reihe 14
# (die Liste `reihe` zaehlt ab null). Ueberhaupt genannt wird er in
# **acht** Blattwerten -- dieselbe Zeichenfolge, aber ohne Ruecksicht
# auf den Schluessel. Diese acht zerfallen ohne Rest in **eins plus
# eins plus sechs**: der eine `beleg` von eben; der Vorlagenschluessel
# `datei.vorlagen.einheiten` in der Tabelle unter diesem Kommentar;
# und sechs weitere, benannt nach dem letzten Pfadteil, der keine
# Listennummer ist -- viermal `offen`, einmal `begruendung`, einmal
# `lang`, zusammen sechs. Jeder der acht Blattwerte liegt in genau
# einem der drei Teile; 1 + 1 + 6 = 8.
# Zweitens: die zwei Pakete sind aus `nachgezogen_durch` gezaehlt --""",
"""# Die beiden Zahlwoerter der 0065-Zaehlung sind mit Paket 0099 neu
# gemessen, und das erste hat sich geaendert. Es gilt die folgende
# Zaehlung; die von Paket 0065 steht weiter unten als Geschichte.
# Gezaehlt ist so, damit es wiederholbar ist. Erstens: als `beleg`
# steht der Einheitenbefund **zweimal** -- Blattwerte, deren
# Schluessel `beleg` heisst und die die Zeichenfolge
# einheitenbefund-pwt-baci enthalten, sind
# reihe.13.umrechnung.0.beleg und reihe.15.umrechnung.0.beleg, die
# ersten Umrechnungsbloecke der Reihen 14 und 16 (die Liste `reihe`
# zaehlt ab null). Ueberhaupt genannt wird er in **sieben**
# Blattwerten -- dieselbe Zeichenfolge, aber ohne Ruecksicht auf den
# Schluessel. Diese sieben zerfallen ohne Rest in **zwei plus eins
# plus vier**: die zwei `beleg` von eben; der Vorlagenschluessel
# `datei.vorlagen.einheiten` in der Tabelle unter diesem Kommentar;
# und vier weitere, benannt nach dem letzten Pfadteil, der keine
# Listennummer ist -- zweimal `offen` (reihe.13.offen.2 und
# reihe.2.offen.0), einmal `begruendung`
# (reihe.2.umrechnung.0.begruendung), einmal `lang`
# (widerspruch.8.lang), zusammen vier. Jeder der sieben Blattwerte
# liegt in genau einem der drei Teile; 2 + 1 + 4 = 7. Der neue
# Schluessel `preisbasis` traegt die Zeichenfolge nicht und geht in
# keine der drei Gruppen ein.
# Zweitens: die zwei Pakete sind aus `nachgezogen_durch` gezaehlt --"""))

ERSETZUNGEN.append((
"""# Datei im Git: der Beleg steht seit dem Commit ae6f605 (2026-09-03,
# die Aenderung des Pakets 0036), der Vorlagenschluessel seit 58908fa.
#
# Sie traegt den groessten offenen
# Rest der fuenf: Ihr Abschnitt 3 und ihr Abschnitt 4 messen Einheit""",
"""# Datei im Git: der Beleg steht seit dem Commit ae6f605 (2026-09-03,
# die Aenderung des Pakets 0036), der Vorlagenschluessel seit 58908fa.
# Diese zweite Zahl ist mit Paket 0099 nachgemessen und unveraendert.
#
# Geschichte der ersten Zahl, weil sie zeigt, wie diese Stelle altert:
# Paket 0065 hat hier "genau einmal" und "acht" gemessen, zerlegt in
# eins plus eins plus sechs (viermal `offen`, einmal `begruendung`,
# einmal `lang`); davor stand "vier Pakete" und "viermal als `beleg`",
# und das war falsch. Die 0065-Zaehlung war fuer ihren Stand richtig --
# am Blob db80e48, der Fassung vor Paket 0078, mit demselben Werkzeug
# nachgemessen und bestaetigt. Bewegt hat sie Paket 0078: Es hat die
# Zeichenfolge in reihe.15.umrechnung.0.beleg eingetragen und die
# beiden Eintraege reihe.13.offen.0 und reihe.15.offen.0 ersetzt, ohne
# diesen Kommentar nachzuziehen. Wer eine solche Zaehlung abschreibt,
# statt sie zu wiederholen, uebernimmt sie falsch; das Werkzeug dafuer
# liegt unter befunde/messung-0099/zahlwoerter.py.
#
# Sie traegt den groessten offenen Rest der fuenf Vorlagen, die vor
# Paket 0099 in dieser Tabelle standen -- gegen `preisbasis` ist der
# Vergleich nicht nachgemessen: Ihr Abschnitt 3 und ihr Abschnitt 4 messen Einheit"""))

# --- 3. die Tabelle ------------------------------------------------------
ERSETZUNGEN.append((
"""reihenliste = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md, Abschnitt 7"
""",
"""reihenliste = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md, Abschnitt 7"
preisbasis = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md, Vorgabe T53 (in Abschnitt 2), Fassung 7 -- Stand der Nachbesserung vom 2026-09-04, mit der T53 entstanden ist (Paket 0026-klasse-2-preisbasis)"
"""))

# --- 4. nachgezogen_durch ------------------------------------------------
ERSETZUNGEN.append((
"""  "0090-rueckstand-ueberschrift-fuenf-tote-zitate",
]""",
"""  "0090-rueckstand-ueberschrift-fuenf-tote-zitate",
  "0099-reihentoml-vorlagenliste-um-t53",
]"""))

with open(PFAD, encoding="utf-8") as f:
    text = f.read()

for i, (alt, neu) in enumerate(ERSETZUNGEN, 1):
    n = text.count(alt)
    if n != 1:
        raise SystemExit("Ersetzung %d greift %d mal statt genau einmal" % (i, n))
    text = text.replace(alt, neu)
    print("Ersetzung %d: genau einmal ersetzt" % i)

with open(PFAD, "w", encoding="utf-8") as f:
    f.write(text)
print("geschrieben:", PFAD)
