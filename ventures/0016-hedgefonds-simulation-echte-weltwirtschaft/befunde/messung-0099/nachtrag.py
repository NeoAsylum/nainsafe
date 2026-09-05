#!/usr/bin/env python3
# Paket 0099 -- die letzte Schreibbewegung: der Nachtrag in pruefweg.toml_geprueft.
# Getrennt von eingriff.py, weil er die Bilanz traegt und deshalb nach allen
# anderen Aenderungen geschrieben werden muss.
import sys

PFAD = sys.argv[1]

ANKER = "weil die Aufzaehlung der drei Gruppen davor die Zaehlregel allein traegt."

NACHTRAG = (
 " Nachtrag vom 2026-09-05, Baulauf des Pakets 0099: Bezugsstand ist der Commit"
 " 456aefa, dessen Fassung dieser Datei mit dem Arbeitsbaum vor dem Lauf"
 " zeichengleich war -- git ls-tree auf den Commit und git hash-object auf den"
 " Arbeitsbaum geben beide den Blob"
 " 736610e78931b608652f38320c252d8fba8516be. Verglichen wird gegen die hier"
 " vorliegende Fassung, und die Messung ist nach der letzten Schreibbewegung"
 " dieses Pakets an dieser Datei wiederholt worden -- dieses Feld ist die letzte."
 " Werkzeug wie oben: Python 3.14.4, tomllib.loads auf den Bytes beider"
 " Fassungen, die alte ueber git cat-file blob und ohne Zwischendatei, beide"
 " Baeume flach gezogen, Blattschluessel als Pfadtupel verglichen; das Messskript"
 " ist das des Pakets 0078 unter befunde/messung-0078/messung.py, unveraendert"
 " uebernommen und mit Blobkennung und Dateipfad wiederholbar. Ergebnis des"
 " Parserlaufs gegen die vorliegende Fassung: gueltiges TOML 1.0; die Liste reihe"
 " hat 19 Eintraege, die Liste widerspruch 9, die Wurzel fuehrt sechs Tabellen"
 " (datei, namensnennung, pruefweg, reihe, widerspruch, zaehlung); die Summe des"
 " Schluessels sollreihen ueber die 19 Reihenbloecke ist 27 und damit gleich"
 " zaehlung.sollreihen_gesamt; zweimal eingelesen ergibt dieselbe Struktur. Der"
 " Bezugsstand traegt 1227 Blattwerte, die vorliegende Fassung 1229. Zwei"
 " Schluessel sind neu, datei.vorlagen.preisbasis und datei.nachgezogen_durch.10"
 " mit der Kennung dieses Pakets; weggefallen ist keiner. Von den 1227"
 " gemeinsamen Schluesseln traegt genau einer einen anderen Wert: dieses Feld"
 " selbst, das die Bilanz traegt und deshalb in ihr vorkommt. Die Messung ist"
 " zweimal gelaufen, vor dem Schreiben dieses Feldes und danach: davor war kein"
 " gemeinsamer Wert verschieden, danach genau einer, und die zweite Zahl steht"
 " hier. Keiner doppelt, keiner ausgelassen. Nicht geaendert ist datei.stand,"
 " weil dort schon 2026-09-05 steht. Kommentare sind keine Blattwerte und stehen"
 " deshalb nicht in dieser Bilanz: geaendert ist genau eine Stelle, der Kommentar"
 " ueber [datei.vorlagen], der dabei von 39 auf 105 Zeilen waechst. Die Datei"
 " waechst von 1763 auf 1831 Zeilen, und die 68 zerfallen ohne Rest in eine Zeile"
 " in datei.nachgezogen_durch, 66 im Kommentar und eine in der Tabelle selbst."
 " Die sechzehn Muster sind nach dem Eingriff einzeln neu gezaehlt worden, nicht"
 " als Summe -- die fuenfzehn Zaehlmuster der sieben Schnitte und als sechzehntes"
 " die Typaufzaehlung hinter schnitt_3 --, und alle sechzehn sind unveraendert:"
 " schnitt_1 sechs Treffer; schnitt_2 neunundzwanzig Zeilen, vierundfuenfzig"
 " Vorkommen und siebenundzwanzig Randzeilen; schnitt_3 hundertvierzehn"
 " Tabellenkoepfe, nach Typ einzeln nachgezaehlt und wieder dreiundzwanzig vom"
 " Typ reihe.umrechnung bei gleicher Summe, also weiterhin kein achter Typ;"
 " schnitt_4 neunzehn, neunzehn, neunzehn, hundertzweiundfuenfzig, zwanzig und"
 " achtundzwanzig; schnitt_5 einundzwanzig und achtundzwanzig; schnitt_7 zwanzig"
 " und zwei. Bei schnitt_1 sind zusaetzlich die sechs Trefferkontexte alt gegen"
 " neu verglichen worden und sind zeichengleich dieselben. Ein neuer Schluessel"
 " in [datei.vorlagen] hebt also keine der sechzehn Musterzahlen, wie es"
 " Bedingung 3 des Arbeitspakets erwartet. Und was dieses Paket ausserdem"
 " gemessen hat, weil Bedingung 2 es verlangt: Die Zaehlung des Pakets 0065 im"
 " Kommentar ueber [datei.vorlagen] war beim Laufbeginn falsch -- nicht durch"
 " dieses Paket, sondern durch Paket 0078. Sie lautete genau einmal als beleg und"
 " acht Blattwerte in der Zerlegung eins plus eins plus sechs; gemessen sind zwei"
 " als beleg und sieben Blattwerte in der Zerlegung zwei plus eins plus vier. Am"
 " Blob db80e48, der Fassung vor Paket 0078, ist die alte Zaehlung mit demselben"
 " Werkzeug bestaetigt worden; sie war fuer ihren Stand richtig und ist es seit"
 " dem 2026-09-05 nicht mehr. Der Kommentar traegt jetzt die gemessene Zaehlung"
 " und die alte als Geschichte; das Werkzeug liegt unter"
 " befunde/messung-0099/zahlwoerter.py und laesst sich mit Blobkennung und"
 " Dateipfad wiederholen.")

if '"' in NACHTRAG:
    raise SystemExit("Der Nachtrag enthaelt ein doppeltes Anfuehrungszeichen und braeche das Feld.")

with open(PFAD, encoding="utf-8") as f:
    text = f.read()
n = text.count(ANKER)
if n != 1:
    raise SystemExit("Anker greift %d mal statt genau einmal" % n)
text = text.replace(ANKER, ANKER + NACHTRAG)
with open(PFAD, "w", encoding="utf-8") as f:
    f.write(text)
print("Nachtrag geschrieben, %d Zeichen" % len(NACHTRAG))
