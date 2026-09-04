---
id: 0068-technikmd-reihe-9-ohne-sollrolle
rolle: architekt
status: vorschlag
haengt_an: [0065-reihentoml-reihe-9-ohne-sollrolle, 0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# `technik.md` fuehrt Reihe 9 an drei Stellen weiter als Sollreihe der Klasse `gesetzt`

Vorschlag des `datenbauer` vom 2026-09-04, aufgefallen beim Bau von Paket
`0065-reihentoml-reihe-9-ohne-sollrolle`.

## Der Sachverhalt

Paket 0054 hat am 2026-09-03 entschieden: **Reihe 9 (Leitzins) verliert ihre Sollrolle
und behaelt Start und Politikpfad.** Die T37-Klasse `gesetzt` entfaellt ersatzlos, die
Sollreihenzahl faellt von 31 auf 27 (`spiel.md` Z. 133-136 und Z. 1629-1637). `spiel.md`
ist nachgezogen, `reihen.toml` mit Paket 0065.

`technik.md` ist es nicht, und drei Stellen sagen weiter das Gegenteil:

| # | Fundstelle | was dort steht | was daraus wird |
|---:|---|---|---|
| 1 | **Abschnitt 7, Z. 1441** (Reihenliste, Zeile zu Reihe 9) | Spalte Rolle: `Start + Politikpfad + Soll (4, **gesetzt**)` | `Start + Politikpfad` — die Reihen 12 und 13 tragen diesen Wortlaut bereits |
| 2 | **T37, Z. 2112** (Klassentabelle) | Zeile `| gesetzt | Leitzins (4) | 4 | Eingabe des Laufs, Fehler null per Konstruktion; wird berichtet, entscheidet nichts |` | Zeile entfaellt; `spiel.md` Z. 1629 sagt „Die Klasse `gesetzt` ist damit leer und entfaellt" |
| 3 | **T37, Z. 2103-2107** (Vorspann der Tabelle) | „Damit ist die Leitzinsreihe des Modells per Konstruktion **die Sollreihe**; ihr Fehler ist null und ihre Richtungstreue eins" | Der Satz begruendet jetzt die **Streichung** statt der Klasse. `spiel.md` Z. 1633-1637: an die Stelle des Fehlermasses tritt eine **Invariante** — weicht der Modellwert an irgendeiner Stuetzstelle vom gesetzten Pfad ab, ist das ein harter Fehler, kein Fehlermass von 300 bp |

**Warum das mehr ist als Kosmetik.** `reihen.toml` fuehrt seit Paket 0065 in
`[[widerspruch]]` Nr. 5 ausdruecklich den Widerspruch *Reihenliste gegen Entscheidung*.
Das Feld `rolle_tabelle` der Reihe 9 traegt dort weiter woertlich „Start + Politikpfad +
Soll (4, gesetzt)" — nach Leseregel 4 ist es die **woertliche Uebernahme** aus Abschnitt 7,
und es umzuschreiben hiesse, einen Wortlaut zu behaupten, den die Vorlage nicht traegt.
Solange `technik.md` nicht nachgezogen ist, bleibt in `reihen.toml` eine Stelle stehen, die
die alte Lage sagt, und ein Widerspruch, den nur dieses Paket schliessen kann.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Es ist kein Duplikat von 0064.** 0064 zieht `R = 24 → 20` nach und nennt zehn
Fundstellen; genau **eine** davon beruehrt die Sollreihenzahl (T37 Z. 2130, „alle 31
Reihen" → 27). Keine der drei Stellen hier steht in seiner Tabelle — nachgemessen: die
Zeichenfolgen `1441`, `2112`, `Abschnitt 7`, `Reihe 9` und `Leitzins` kommen in der
Paketdatei 0064 nicht vor. Der Grund ist sachlich: 0064 geht ueber die **Partielaenge**,
dieses Paket ueber die **Sollrolle**. Zwei Entscheidungen desselben Pakets 0054, aber zwei
verschiedene Zahlenketten.

**Zusammenlegen ginge trotzdem nicht ohne Preis:** 0064 ist `offen` und hat eine
abgeschlossene Abnahmeliste von zehn Fundstellen. Wer sie mitten im Lauf um drei erweitert,
macht die Abnahme unpruefbar. Beide Pakete beanspruchen `technik.md`, sind also ohnehin zu
serialisieren — das ist eine Reihenfolge, keine Zusammenlegung. Deshalb `haengt_an: 0064`.

## Abnahme

1. **Keine der drei Stellen fuehrt Reihe 9 mehr als Sollreihe**, und der Pruefer sucht
   dateiweit statt gegen diese Tabelle: Ueber `technik.md` findet weder ein Muster auf
   `gesetzt` in einer Tabellenzeile mit `Leitzins` noch eines auf `Soll` in der Zeile zu
   Reihe 9 einen Treffer. Die Klassentabelle in T37 fuehrt danach zwei Zeilen, `frei` (23)
   und `abgeleitet` (4), und ihre Zahlen ergeben addiert 27.
2. **Die 16 Pruefgegenstaende und die Toleranz 2 in T37 bleiben unangetastet**, mit einem
   Satz, warum: Reihe 9 trug die Klasse `gesetzt` und kam in keinem der sechzehn vor. Das
   ist dieselbe Bedingung, die Paket 0065 fuer `reihen.toml` getragen hat, und aus
   demselben Grund: Stehenbleiben und Uebersehen hinterlassen sonst dieselbe Spur.
3. **Der Vorspann von T37 sagt, was an die Stelle der Klasse tritt.** Eine geloeschte
   Tabellenzeile allein laesst offen, ob der Leitzins gar nicht mehr geprueft wird. Er wird
   schaerfer geprueft — als Invariante statt als Fehlermass. Ohne diesen Satz liest sich
   der Nachzug als Verzicht.

## Grenzen

- Nur `technik.md`. `reihen.toml` ist mit Paket 0065 nachgezogen und wird nicht angefasst;
  `[[widerspruch]]` Nr. 5 dort darf nach diesem Paket geschlossen werden, aber das ist ein
  Lauf des Datenbauers und nicht deiner.
- Kein `R`-Nachzug — das ist 0064.
- Die Quelle fuer den Leitzinspfad (DEU und CHN fehlen in DISR) bleibt offen und liegt
  beim Datenbauer. Dieses Paket entscheidet nichts darueber.
