---
id: 0068-technikmd-reihe-9-ohne-sollrolle
rolle: architekt
status: offen
haengt_an: [0065-reihentoml-reihe-9-ohne-sollrolle, 0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme", Bedingung 1 in der berichtigten Fassung des Annahmevermerks vom 2026-09-04 (Abschnitt "Berichtigung an Bedingung 1") -- ohne die Zahlen 23, 4 und 27, dafuer selbst nachgezaehlt und mit genannter Differenz. Bedingung 2 heisst "dieses Paket fasst die Zahl nicht an", nicht "die Ziffer 16 steht woertlich da"; siehe den Vermerk vom 2026-09-05.
---

# VERMERK — 2026-09-05, Projektmanager: die 16 wird vor dir zu einer Formel

Deine Bedingung 2 lautet: *„Die 16 Prüfgegenstände und die Toleranz 2 in T37 bleiben
unangetastet."* Sie stand da, als die 16 eine Ziffer war.

`0117-geschaetzter-politikpfad-und-zwei-laenderklassen` läuft **vor** dir in derselben Datei
und macht ebendiese Zahl parametrisch — seine Bedingung 2 verlangt „eine Formel in der Zahl
der Rückvergleichsländer; Einsetzen von vier ergibt genau 16". Der Betreiber hat 0117 am
2026-09-05 selbst eingestellt.

**Die Bedingung ist damit nicht hinfällig, sondern nur missverständlich geworden.** Sie
verlangt eine *Unterlassung*: dass **du** die Zahl und die Toleranz nicht anfasst. Gemessen
wird gegen den Stand, den du bei Beginn vorfindest, nicht gegen die Fassung von heute. Steht
dort dann eine Formel mit der eingesetzten 16 daneben, ist das der Bezugspunkt — und der
Satz aus deiner Bedingung, *warum* sie unangetastet bleibt (Reihe 9 trug die Klasse
`gesetzt` und kam in keinem der sechzehn vor), gilt unverändert und ist weiter zu schreiben.

**An den Prüfer:** Ein Bericht, der Bedingung 2 daran scheitern lässt, dass die Ziffer 16
nicht mehr allein dasteht, misst die Arbeit von 0117 und nicht die dieses Pakets. Der
Vermerk in Gegenrichtung steht in 0117.

**Zur Reihenfolge:** `0051 (gebaut) → 0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092`. Dein
`haengt_an` nennt 0064 und trägt die Kette damit transitiv; es musste nicht geändert werden.

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

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, mit einer Berichtigung an Bedingung 1

Vier Prüfungen, alle bestanden:

- **Die Rolle gibt es, und ein Runner plant sie ein.** `architekt` steht in `BAUROLLEN`
  (`agents/baulauf.py`) und hat mit `entwurf-pruefer` einen eigenen Prüfer in `REVIEW`.
- **Die Dateiliste schneidet vier offene Pakete** — 0026, 0051, 0064 und 0043 führen
  ebenfalls nur `specs/…/technik.md`. Das ist **kein Ablehnungsgrund, sondern der Zweck des
  Feldes**: `startbereit()` lässt von fünf Paketen auf derselben Datei immer nur eines
  gleichzeitig starten. Genau dafür ist `technik.md` in diesem Vorhaben die
  Kollisionseinheit.
- **Kein Paket auf `gebaut` hält diese Datei.** Der Kollisionsschutz vergleicht `dateien`
  nur unter `offen`; die beiden `gebaut`-Pakete dieses Laufs führen `kern/…` (0027) und
  `spiel.md` (0055). Geprüft, weil der Schutz an dieser Stelle blind ist.
- **Es hängt an zwei unfertigen Paketen** (0065, 0064). Das ist zulässig — `haengt_an`
  hält es zurück, bis beide abgenommen sind, und kostet keinen Bauplatz.

### Berichtigung an Bedingung 1: die Zahlen 23, 4 und 27 sind gestrichen

Bedingung 1 verlangt, die Klassentabelle in T37 führe danach *„`frei` (23) und `abgeleitet`
(4), und ihre Zahlen ergeben addiert 27."* **Diese drei Zahlen nehme ich heraus**, und der
Grund ist eine Falle, die in diesem Vorhaben dreimal zugeschlagen hat: Ein Kriterium, das
eine Zahl aus einer Summe festschreibt, wird durch **fremde** Arbeit unerfüllbar. Vier
weitere offene Pakete schreiben in dieselbe Datei, darunter mit `0026-klasse-2-preisbasis`
eines, das ausdrücklich an Klassen und Skalen arbeitet. Steht das Paket dann vor einer
Tabelle mit 24 freien Reihen, hat es die Wahl zwischen einer Falschaussage und einem
Rücklauf, den es nicht verschuldet hat.

**An ihre Stelle tritt die Bedingung statt der Zahl:**

> 1. (berichtigt) Keine der drei Stellen führt Reihe 9 mehr als Sollreihe; der Prüfer sucht
>    dateiweit statt gegen eine Tabelle. Die Klassentabelle in T37 führt danach **genau die
>    zwei Zeilen `frei` und `abgeleitet`** — die Zeile `gesetzt` ist fort, nicht auf null
>    gesetzt. **Die je Zeile genannte Anzahl und die genannte Gesamtzahl stimmen mit dem
>    überein, was in der Datei tatsächlich steht**, selbst nachgezählt und nicht aus diesem
>    Paket übernommen. Weicht eine Zahl von der ab, die hier oder in 0065 steht, ist das
>    kein Fehler: Dann nennt der Baubericht die Differenz und was sie trägt.

Bedingungen 2 und 3 bleiben unverändert; beide sind an einem Satz im Dokument prüfbar und
nennen keine Zahl aus einer Summe.

**Und der übliche Hinweis, weil er hier greift:** Ich schreibe dir keinen Wortlaut für den
Satz aus Bedingung 3 vor. Was an die Stelle der Klasse tritt — Invariante statt Fehlermaß —
ist eine Aussage über den Entwurf, und sie muss von dir stammen, damit der Prüfer sie
prüfen kann statt sie wiederzuerkennen.
