---
id: 0120-abschnittszitat-nachmessung-zinsreihen
rolle: datenbauer
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/nachmessung-zinsreihen-2026-09-05.md]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Ein Abschnittszitat zeigt auf Fliesstext, und der ganze Uebersetzungsbericht traegt deswegen `fehler`

`daten/nachmessung-zinsreihen-2026-09-05.md` zitiert im Frontmatter (Zeile 6,
`berichtigt:`) den Abschnitt „Die Reihenliste nennt IWF IFS" aus
`daten/deckungsbefund-1997.md`. Dort ist dieser Wortlaut kein Abschnittstitel, sondern
der erste Satz des Fliesstexts unter `### Reihe 9 — Leitzins (4 Sollreihen) — **die
Reihe, an der es reißt**` (Zeilen 138-140). Der `belegstellen_riegel` meldet das als
seinen einzigen bewerteten Fehler („1 Abschnittszitat(e) finden ihre Ueberschrift
nicht"), der Arbeitsbereichs-`ctest` steht damit auf 13/14, und
`befunde/uebersetzung-2026-09-05.md` traegt `ergebnis: fehler` — obwohl alle
uebersetzenden Ziele und alle Proben gruen sind.

Die zitierende Datei stammt aus `a6c55e0` („Betreiber: Nachmessung Reihe 9",
2026-09-05 09:38); der Riegel war also schon vor dem Baulauf von 11:36 rot. Zwei
GEBAUT-Eintraege (0061, 0107) haben es gemeldet, keiner durfte es beheben, und kein
Paket traegt es bisher.

## Warum ein eigenes Paket

Es gibt kein offenes Paket, dessen `dateien`-Liste die zitierende Datei haelt
(nachgesehen ueber alle Aufgaben am 2026-09-05), und die Berichtigung ist keinem
laufenden Auftrag zuzuschlagen: Sie ist eine Ein-Zeilen-Aenderung an einer
Betreiber-Datei unter `daten/`. Liegen bleiben kann sie nicht: Solange der Riegel rot
ist, meldet **jeder** Uebersetzungsbericht `ergebnis: fehler`, und jede kuenftige
Abnahmebedingung der Form „im Uebersetzungsbericht steht Passed" muss den Fremdfehler
von Hand herausrechnen — genau die Sorte Rauschen, gegen die der Riegel gebaut wurde.
Die Riegelausgabe selbst verlangt die Berichtigung: „Beides wird berichtigt und nicht
ausgenommen."

## Was du baust

Die Zeile 6 des Frontmatters nennt statt des Fliesstext-Wortlauts den tatsaechlichen
Abschnittstitel, auf den sie zeigt: `Reihe 9 — Leitzins (4 Sollreihen) — die Reihe, an
der es reißt` (Schreibweise bis auf Umlautumschrift, Auszeichnung und Leerraum
wortgleich, so prueft der Riegel). Inhaltlich aendert sich nichts — gemeint war
erkennbar dieser Abschnitt, denn die Nachmessung berichtigt dessen Reihe 9. Keine
Ausnahmeliste anfassen, keinen Riegel lockern.

## Abnahme

1. Der `belegstellen_riegel` findet **null** Abschnittszitate ohne Ueberschrift, und
   die Fundstelle `daten/nachmessung-zinsreihen-2026-09-05.md:6` verschwindet aus
   seiner Fehlerausgabe.
2. Im naechsten `befunde/uebersetzung-<datum>.md` ist der Arbeitsbereichs-`ctest`
   14/14 gruen — sofern kein **neuer** Fremdfehler dazwischenkommt; dann gilt statt
   dessen Bedingung 1 am Riegel allein.
