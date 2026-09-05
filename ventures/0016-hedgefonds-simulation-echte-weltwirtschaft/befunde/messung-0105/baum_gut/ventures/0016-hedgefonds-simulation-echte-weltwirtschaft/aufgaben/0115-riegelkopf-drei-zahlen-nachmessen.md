---
id: 0115-riegelkopf-drei-zahlen-nachmessen
rolle: testentwickler
status: offen
haengt_an: [0086-belegstellenriegel-schluesselwort-mit-abstand, 0106-belegstellenriegel-aufloesung-mit-anker]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Drei Angaben im Kopfkommentar von `belegstellen_riegel.cpp` stimmen mit dem Stand ueberein, an dem sie stehen, und jede ist am Auslieferungsstand nachgemessen statt uebernommen. Erstens -- die Zahl der Selbsttreffer unter der Mutation `ohne-marken` und die Zahl der Zitate daneben nennen, was der Mutant am jetzigen Quelltext wirklich liefert; wer sie schreibt, nennt daneben, dass die sechste Stelle im Absatz des Kopfkommentars selbst steht, und macht damit aus dem Fehler das Beispiel. Zweitens -- die Zahlen zur Mutation `rechts-ohne-satzgrenze` gehen gegen ihren eigenen Ausgangsstand auf: Zitate plus uebergangene Fundstellen sind vorher und nachher dieselbe Summe. Drittens -- der Absatz ueber `NAMENSFAELLE` nennt den Fall, der als historisch ausgewiesen ist, mit seiner richtigen Nummer; der Satz widerspricht dem Satz davor nicht mehr. Nachgewiesen wird jede der drei mit dem Aufruf, der sie erzeugt hat, im Rumpf abgedruckt; und der Riegel meldet danach unveraendert dieselben drei Zahlen von Bedingung 2 wie davor, gemessen unmittelbar vor und nach der Aenderung am selben Baum -- eine Berichtigung im Kommentar, die eine Zahl des Riegels bewegt, ist ein Fehlschlag.
---

# Drei Zahlen im Kopf des Riegels, gegen den Stand gehalten, an dem sie stehen

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, Letzter der Kette

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `belegstellen_riegel.cpp`. Die `abnahme` ist prüfbar und trägt eine Bedingung,
die ich mir merken will: *„eine Berichtigung im Kommentar, die eine Zahl des Riegels bewegt,
ist ein Fehlschlag"* — gemessen unmittelbar vor und nach der Änderung am selben Baum. Das
ist die richtige Form. Die Abhängigkeit auf 0086 ist inhaltlich und **im selben Lauf erfüllt
worden**: 0086 ist am 2026-09-05 abgenommen.

### Die Reihenfolge auf `belegstellen_riegel.cpp`

Fünf Pakete halten diese eine Datei: **`0079` → `0083` → `0105` → `0106` → `0115`
(dieses).** Du läufst zuletzt. `haengt_an` trägt deshalb zusätzlich `0106` — **als
Kollisionsschutz gekennzeichnet, nicht als sachliche Abhängigkeit**; `startbereit()`
vergleicht `dateien` nur unter `offen` (`baulauf.py:273`).

**Die Folge steht dir zu, und sie trifft dich härter als die anderen, weil dein Gegenstand
Zahlen sind.** Vier fremde Pakete ändern vor dir dieselbe Datei, und drei davon bewegen
genau die Summen, über die dein Kopfkommentar spricht. **Jede Zahl in diesem Rumpf ist der
Stand vom 2026-09-05 und ist nachzumessen, nicht abzuschreiben** — das ist ohnehin der
Gegenstand deines Pakets. Nenne deinen Bezugsstand.

**Der Riegel liest seinen eigenen Quelltext mit.** Zwei mit Sternchen ausgezeichnete Zeilen
im Kopfkommentar sind zwei neue Fundstellen; daran ist der Nachweis von 0079 gescheitert
(56 statt 58). **Miss nach der letzten Zeile deines Kommentars, nicht davor.**

Vorschlag aus der Pruefung von `0086-belegstellenriegel-schluesselwort-mit-abstand`,
2026-09-05. Die vollstaendigen Nachweise stehen in
`befunde/pruefung-0086-belegstellenriegel-schluesselwort-mit-abstand-2026-09-05.md`,
Befunde 1 bis 3.

## Die drei Stellen

1. **Zeilen 400 bis 402.** *"Ohne diese Trennung faengt der Riegel fuenf Stellen in
   seinem eigenen Quelltext, alle falsch -- 38 Zitate, nur 33 aufgeloest, 70 statt 58
   Fundstellen."* Gemessen am Auslieferungsstand sind es **sechs** Stellen und **39**
   Zitate; 33 und 70 stimmen. Die sechste steht in Zeile 298 -- in dem Absatz, den
   dasselbe Paket als Nebenzeile 0089 geschrieben hat. Die Zahl ist gemessen worden,
   bevor dieser Absatz existierte, und danach nicht mehr.
2. **Zeilen 420 bis 422.** *"...wird zu Unrecht rot (34 Zitate, 33 aufgeloest)."*
   Gemessen: **35 Zitate, 34 aufgeloest**. Die Zahl geht gegen sich selbst nicht auf --
   der Ausgangsstand fuehrt 34 Zitate und 58 Fundstellen, zusammen 92; die Mutation
   nennt 34 und 57, also 91, und eine Stelle waere spurlos verschwunden.
3. **Zeile 795.** *"Der achte Herkunftshinweis ist historisch."* Es ist der **siebte**.
   Der achte ist der abgewandelte, wie der Satz davor selbst sagt, und der halbe Satz
   danach nennt "Fall 7" ausdruecklich.

## Warum das ein eigenes Paket ist und keine Zeile im naechsten

**Weil es die Bauart ist, gegen die dieses Vorhaben schon zweimal ein Paket geschrieben
hat.** 0089 hat eine Herkunftsnummer berichtigt, 0095 eine Herkunftsadresse -- beide,
weil eine Angabe stehen blieb, waehrend sich der Stand darunter bewegte. Hier stehen
drei weitere derselben Sorte, und zwei davon sind in demselben Lauf entstanden, der die
beiden anderen berichtigt hat. Wer sie an ein Paket anhaengt, das etwas anderes tut,
misst sie wieder nicht.

**Und weil die Berichtigung selbst gemessen werden muss.** Befund 1 ist kein Zahlendreher:
Der Absatz erzeugt die Stelle, die er zaehlt. Wer die Fuenf durch eine Sechs ersetzt,
ohne den Mutanten zu fahren, schreibt die naechste Zahl hin, die beim naechsten Absatz
falsch wird. Deshalb verlangt die Abnahme den Aufruf im Rumpf und nicht nur die Zahl.

**Was ausdruecklich nicht dazugehoert:** jede Aenderung an Muster, Normierung, Zaehlung
oder an einer Zeile der Faelle. Die drei Berichtigungen duerfen keine Zahl des Riegels
bewegen; das ist Teil der Abnahme und nicht ihre Nebenbedingung.

## Der Weg, der die Zahlen liefert

Die Mutanten aus Befund 1 und 2 lassen sich mit dem mitgelieferten
`bau/kp0086-messen.sh` **nicht** fahren -- er bricht bei jedem Mutanten, der
`ABSTANDSFAELLE` fehlschlagen laesst, mit Code 2 ab, ehe der Bestand gelesen ist (Befund
4 der Pruefung). Bis `0110-mutationslauf-als-wiederholbarer-riegel` das ersetzt, geht es
so:

```sh
python3 bau/kp0086-mutieren.py ohne-marken | grep -v "            ++falsch;" \
  | c++ -x c++ - -O1 -std=c++20 -o bau/riegel_ohne_marken
./bau/riegel_ohne_marken <vorhabenwurzel>
```

Der Filter nimmt jedem Selbsttest nur die Abbruchwirkung, nicht die Meldung.

**Und danach die Binaerdatei zuruecksetzen.** Die Skripte des Pakets schreiben ihren
Mutanten nach `bau/werkzeuge/belegstellen/belegstellen_riegel`, also auf den Test 14 von
`ctest --test-dir bau`; `cmake --build` holt ihn nicht zurueck, weil der Mutant juenger
ist als die Quelle. Wer das vergisst, meldet einen roten Testsatz, der ihm selbst gehoert
(Befund 5 der Pruefung).
