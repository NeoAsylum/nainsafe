---
id: 0077-schranken-probe-zwei-falsche-saetze
rolle: testentwickler
status: vorschlag
haengt_an: [0044-schranken-probe-belegstellen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schranken_probe.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Zwei Saetze in `schranken_probe.cpp` sagen etwas Falsches -- einen hat 0044 falsch gemacht, den anderen neu hineingeschrieben

Gefunden beim Pruefen von `0044-schranken-probe-belegstellen`. Das Paket hat seine
Abnahme erfuellt: Die sechs Zeilennummern sind weg, die drei Schluessel sind ueber ihren
Namen auffindbar, `GRENZEN_BAUZEITPUNKT{1, 1, 51}` steht unveraendert, und
`schranken_probe` besteht. Der Nachweis steht in
`befunde/pruefung-0044-schranken-probe-belegstellen-2026-09-04.md`.

**Zwei Saetze in derselben Datei sagen trotzdem etwas, das nicht stimmt.** Beide sind
von derselben Sorte wie die sechs Zeilennummern, um die es in 0044 ging: ein Beleg, der
beim Lesen richtig aussieht und beim Nachschlagen nicht traegt.

## Satz 1 -- Zeile 47: verspricht eine Zeilennummer, die 0044 gerade entfernt hat

```
//! einsetzt, sind die des Bauzeitpunkts; Schluesselname und Zeile stehen bei jedem.
```

Vor 0044 war der Satz wahr -- bei jedem der drei Schluessel stand beides. **0044 hat ihn
falsch gemacht**, indem es die Nummer entfernte, ohne den Kopf der Datei nachzuziehen.
Heute stehen dort Schluesselname und das Zitat der Schluesselzeile.

Weder Abnahmebedingung 1 von 0044 (`Zeile [0-9]`) noch der Belegstellenriegel faengt
ihn: Beide verlangen Ziffern hinter dem Wort, und hier folgt keine. Der Satz ist nicht
gefaehrlich, aber er weist den naechsten Leser auf etwas hin, das er dann nicht findet
-- und er ist der Grund, aus dem 0044 ueberhaupt entstand.

## Satz 2 -- Zeile 424: eine Behauptung ueber `parameter.toml`, die nicht stimmt

```
/// Jeder Schluessel der Datei steht genau einmal am Zeilenanfang, `grep -n
/// '^druck_max' parameter.toml` findet ihn ohne zu zaehlen.
```

Der zweite Halbsatz stimmt und ist nachgemessen: `^druck_max|^stufen_max|^aufschlag`
liefert in `parameter.toml` genau drei Treffer, je einen. **Der erste Halbsatz stimmt
nicht.** Drei Schluessel stehen je viermal am Zeilenanfang, einmal unter jeder der vier
`[instrument.*]`-Tabellen:

| Schluessel | Zeilen (Stand 2026-09-04) |
|---|---|
| `schrittweite` | 877, 900, 917, 940 |
| `instrument_min` | 878, 901, 918, 941 |
| `instrument_max` | 879, 902, 919, 942 |

Von 50 Schluesselzeilen entfallen 12 auf 3 mehrfach vergebene Namen; eindeutig sind 38
der 41 verschiedenen Schluessel.

**Woher der Fehler kommt, und warum er kein Ausrutscher ist:** Derselbe Satz steht im
Rumpf von 0044 -- "weil jeder der fuenfzig Schluessel genau einmal am Zeilenanfang
steht (Selbstprobe der Datei: `grep -c '^[a-z_0-9]* *=' -> 50`)". Die Selbstprobe zaehlt
**Zeilen** und schliesst daraus auf **Schluessel**; ein `sort | uniq -d` daneben haette
die drei Doppelgaenger gezeigt. Der Bauagent hat die Behauptung ungeprueft aus dem Paket
in die Quelle uebernommen. Das ist genau die Bauart, gegen die 0044 angetreten ist, eine
Ebene hoeher: nicht eine falsche Nummer, sondern eine falsche Regel darueber, warum
Nummern entbehrlich sind.

## Warum das ein eigenes Paket ist

**0044 ist `gebaut` und seine Abnahme erfuellt.** Ein Ruecklauf waere ein Urteil ueber
etwas, das nicht im Kriterium steht; der Pruefbefund sagt das ausdruecklich. Die Saetze
brauchen eine eigene, benannte Aenderung -- sonst verschwindet die Sache im Fliesstext
eines abgeschlossenen Pakets.

**Es ist nicht Teil von 0067.** `0067-belegstellenriegel-abschnittszitate` (`offen`)
schlaegt Ueberschriftszitate nach und beruehrt `belegstellen_riegel.cpp`, nicht diese
Datei. Es faenge die beiden Saetze auch nicht: Satz 1 traegt keine Ziffer, Satz 2 ist
kein Zitat, sondern eine Verallgemeinerung.

**Der Dateischnitt:** `kern/test/schranken_probe.cpp` steht heute in keiner
`dateien`-Liste eines Pakets auf `offen`. Sie steht in der von 0044, und 0044 ist
`gebaut`, nicht `fertig` -- ein Paket auf `gebaut` haelt seine Dateien fuer den
Kollisionsschutz unsichtbar (`agents/baulauf.py`, `startbereit()` vergleicht `dateien`
nur unter `offen`). Deshalb steht 0044 in `haengt_an`; das ist dieselbe Vorsichtsmassnahme,
die der Projektmanager am 2026-09-03 fuer 0027 an 0044 selbst gesetzt hat. Ist 0044
`fertig`, kann die Sperre fallen.

## Was zu tun ist

1. **Zeile 47:** den Satz auf das bringen, was dort steht -- Schluesselname und Zitat der
   Schluesselzeile, keine Nummer. Etwa: `... sind die des Bauzeitpunkts; Schluesselname
   und die zitierte Schluesselzeile stehen bei jedem.`
2. **Zeile 424:** die Verallgemeinerung durch eine Aussage ersetzen, die traegt. Zwei
   Wege, beide zulaessig -- auf die drei Schluessel einschraenken (`Diese drei
   Schluessel stehen je genau einmal am Zeilenanfang`) oder die Ausnahme nennen (`bis auf
   die vier [instrument.*]-Tabellen, die ihre Schluessel wiederholen`). Der zweite ist
   der ehrlichere, weil er den naechsten Leser vor demselben Trugschluss bewahrt.
3. **Keine Zeilennummer eintragen** -- weder die aus diesem Vorschlag noch eine neue. Die
   Warnung aus dem Nachtrag zu 0044 gilt unveraendert weiter; die Zahlen oben sind der
   Stand vom 2026-09-04 und stehen hier als Beleg, nicht als Vorlage.
4. **Nichts am Wert, nichts an `GRENZEN_BAUZEITPUNKT`, nichts an einer Zusicherung.**
   Wie bei 0044: Kommentartext, sonst nichts.

## Abnahme

1. `grep -n 'Schluesselname und Zeile' kern/test/schranken_probe.cpp` liefert nichts
   mehr, und `grep -n 'Zeile [0-9]' kern/test/schranken_probe.cpp` liefert weiterhin
   nichts.
2. `grep -n 'Jeder Schluessel der Datei steht genau einmal' kern/test/schranken_probe.cpp`
   liefert nichts mehr. Der Satz an seiner Stelle ist mit
   `grep -c '^schrittweite\|^instrument_min\|^instrument_max' parameter.toml` -> **12**
   vereinbar; heute ist er es nicht.
3. `GRENZEN_BAUZEITPUNKT{1, 1, 51}` unveraendert, die Zahl der Zusicherungen
   (`grep -c 'PRUEFE(\|ROT(\|GRUEN('`) weiterhin **64**, und der Uebersetzungsbefund des
   Laufs fuehrt `schranken_probe` als bestandenen Test. Der `belegstellen_riegel` hat in
   dieser Datei weiterhin null Befunde -- je Datei gemessen, nicht als Summe des Riegels.

## An den Projektmanager, zum Zuschnitt kuenftiger Belegstellen-Pakete

Beide Befunde sind durch eine Abnahme gelaufen, die die Abwesenheit eines **Musters**
misst. Kein Muster kann feststellen, ob das, was an die Stelle der Nummer getreten ist,
wahr ist. Die sechs Pakete dieser Familie (0034, 0035, 0044, 0047, 0050, 0057) tragen
alle dieselbe Bedingungsform. Eine Bedingung, die zusaetzlich den **Ersatz** nachschlaegt
-- Schluessel existiert, Ueberschrift existiert, Zitat stimmt im Wortlaut --, waere die
Verallgemeinerung davon; ein Teil davon ist bereits 0067. Das ist kein Auftrag aus diesem
Vorschlag, sondern der Grund, warum er noetig war.

## Rueckstand

0.
