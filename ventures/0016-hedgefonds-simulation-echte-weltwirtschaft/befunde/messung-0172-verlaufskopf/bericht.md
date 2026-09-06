---
typ: messung
paket: 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen
rolle: kernbauer
datum: 2026-09-06
stand: 45fc32ff156eef604ce419b736fbd7e15941efe9
ergebnis: gruen
---

# Die Groesse des Verlaufs bei der Wand 2169, uebersetzt gemessen

Zwei Skripte daneben, beide mit Rueckgabe 0 und ihrem Lauf im Wortlaut:
`schranke.py` mit `lauf.txt` (Bedingungen 1 und 2), `profile.py` mit `lauf-profile.txt`
(Bedingung 3).

## Bedingung 1 -- die Zahl ist uebersetzt, nicht gerechnet

`schranke.py` baut je Fall einen Wegwerfbaum aus `git archive 45fc32f`, setzt darin die
Wand, uebersetzt `groesse.cpp` gegen genau diesen Kopf und laesst das Programm
`sizeof(Verlauf)` selbst abdrucken. Die Formel aus dem Paketrumpf steht im Skript
nirgends -- sie ist das, was geprueft wird, und darf deshalb nicht die Quelle der Zahl
sein.

| Wand | entfernte Zusicherung | Urteil | `sizeof(Verlauf)` |
|---|---|---|---|
| 26 | keine | gruen | 451.784 Byte |
| 2169 | Stapel | gruen | **37.688.552 Byte** |
| 2170 | Stapel | **rot** | uebersetzt nicht |
| 2170 | Stapel und T40 | gruen | 37.705.928 Byte |

Die erste Zeile ist die Rueckbindung: Es sind dieselben 451.784 Byte, die die Messung zu
Paket 0156 abgedruckt hat. Der Kopf trug bisher 37.670.312 Byte; das ist um 18.240 Byte
zu wenig und gehoert zu keiner ganzzahligen Wand. Im Kopf steht jetzt die gemessene Zahl.

`sizeof(Kette)` misst in allen Faellen 17.368 Byte -- die zweite Zahl, die der berichtigte
Satz nennt.

**Warum die Stapelzusicherung in den Faellen ab 2169 fehlt.** Sie reisst schon bei der
Wand 483 (Messung zu 0156) und machte jeden Fall darueber rot, bevor die T40-Zusicherung
zu Wort kaeme. Der Satz im Kopf spricht ausdruecklich davon, wie weit *Wand und
Kapazitaet gemeinsam* durchlaufen -- das ist die T40-Zusicherung.

## Bedingung 2 -- was bei 2170 rot wird

Die dritte Zeile ist der Nachweis, im Wortlaut aus `lauf.txt`:

```
error: static assertion failed: T40: ein Verlauf traegt hoechstens die Runden der
laengsten zulaessigen Partie, und eine weitere passt nicht mehr hinein
```

Das Skript prueft die Meldung zweiseitig: Sie **muss** die T40-Zusicherung nennen und
darf die Stapelschranke **nicht** nennen. Die vierte Zeile ist die Gegenprobe dazu --
derselbe Fall ohne die T40-Zusicherung uebersetzt gruen. Ohne sie waere nicht gezeigt,
dass genau diese eine Zusicherung den Bau rot macht.

Der berichtigte Satz im Kopf nennt zusaetzlich den Grund: Ein Verlauf traegt je Runde
neben der Kette noch ihre Rundennummer zu acht Byte. Die Zusicherung haelt, solange
acht mal die Wand unter 17.360 Byte bleibt -- also bis 2169 und keine Runde weiter.

## Bedingung 3 -- beide Profile gruen, in beiden Baeumen

`profile.py`, vier Laeufe gegen den Arbeitsbaum, Baubaeume aus dem Leeren:

| Baum | Profil | `cmake -S` | `cmake --build` | `ctest` | Eintraege |
|---|---|---|---|---|---|
| Alleinbau | Sanitizer ON | 0 | 0 | 0 | 12 |
| Alleinbau | Sanitizer OFF | 0 | 0 | 0 | 12 |
| Arbeitsbereich | Sanitizer ON | 0 | 0 | 0 | 18 |
| Arbeitsbereich | Sanitizer OFF | 0 | 0 | 0 | 18 |

Der Bezugsstand ist der 2026-09-06 aus dem Paketrumpf: Alleinbau 12, Arbeitsbereich 18,
in beiden Profilen. Die Zahlen sind gleich geblieben. Im Arbeitsbereichslauf laufen die
Riegel Nr. 16 bis 18 mit -- Belegstellen, Bezeichner und Schlussriegel lesen den
geaenderten Kommentartext und sind gruen.

## Was der Lauf nicht sagt

- **Die drei Zusicherungen sind unveraendert.** Geaendert ist nur Kommentartext; die
  Skripte mutieren die Kopfdatei ausschliesslich in ihren Wegwerfbaeumen.
- **Der Wegwerfbaum von `schranke.py` traegt den Stand 45fc32f, nicht die Aenderung.**
  Das ist Absicht: Gemessen wird die Groesse des Behaelters, und die haengt an den
  Feldern, nicht am Kommentar darueber. Bedingung 3 laeuft dafuer gegen den Arbeitsbaum
  mit der Aenderung.
- **`profile.py` haelt den Arbeitsbaum vor und nach dem Lauf fest.** Waehrend des Laufs
  standen dort fremde Aenderungen an `daten/reihen.toml` und an einem Aufgabenblatt --
  andere Agenten arbeiten gleichzeitig. Sie sind nicht Teil dieses Pakets und nicht
  mitcommittet.
