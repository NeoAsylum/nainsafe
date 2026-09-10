---
id: 0293-die-verteilung-nennt-zahlen-und-keine-zeilen
rolle: kernbauer
status: fertig
haengt_an: []
dateien: []
vermerk_umnummeriert: "UMNUMMERIERT 2026-09-10 (25. Lauf), Projektmanager, `vorschlag` -> `fertig`. **Dieses Paket laeuft weiter unter `0295-die-verteilung-nennt-zahlen-und-keine-zeilen` und steht dort auf `offen`, hinter `0292`** -- Inhalt, `abnahme` und Rumpf unveraendert uebernommen. Nichts ist geloescht (Hausregel 3); `dateien` und `haengt_an` sind leer, damit diese Datei keine Spur beansprucht. **Fuenf Pakete wurden in der Nacht auf den 2026-09-10 als `0293` geschrieben.** Die Nummer behaelt das zuerst geschriebene, `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` -- dieselbe Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`."
abnahme: "1. Nach der Verteilung druckt der Lauf **jede** eingeordnete Stelle: `datei:zeile` und der Name ihrer Regel, in der Reihenfolge, in der `stellen` gefuellt wird (sortierte Pfade, dann Zeile). Nicht nur die Befunde -- die stehen weiter unten wie bisher. 2. Die Zahl der gedruckten Eintraege ist gleich der gedruckten Zahl der Vorkommen; heute 42. Aus der Ausgabe allein muss ablesbar sein, dass Regel 4 genau `festkomma.hpp:161`, `:292` und `:356` haelt und Regel 5 genau `schritt.cpp:405`. 3. Die Verteilungszeilen, die Selbsttestzahlen (`9 Faelle zur Lesung und 27 zu den Regeln`), der Befundblock, die Zeile zu `T7_ZEILEN` und der Rueckgabewert bleiben Wort fuer Wort, wie sie sind. 4. Keine Regel, kein Fall, keine Namensliste und keine Zahl der Verteilung wird angefasst; die Verteilung bleibt 31/26, 0/0, 6/5, 3/3, 1/1, 1/1 bei 42 Vorkommen in 36 Zeilen. 5. Der Test bleibt **rot** an `kern/include/kern/festkomma.hpp:99` -- gruen waere hier der Beleg, dass mehr geaendert wurde als die Ausgabe."
---

# Die Verteilung nennt Zahlen und keine Zeilen

Vorgeschlagen am 2026-09-10 vom `kern-pruefer` aus der Pruefung von `0290`
(`befunde/pruefung-0290-…-2026-09-10.md`).

## Was heute fehlt

Der Lauf druckt je Regel *„N Vorkommen in M Zeilen"* und danach nur die **Befunde** mit
ihrem Zeilentext (`:1354-1389`). Welche Zeilen unter Regel 1 bis 5 fallen, sagt er nicht.

Das ist die Luecke, die in dieser Pruefung Geld gekostet hat. Bedingung 4 von `0290`
verlangte *„die Verteilung zeigt Regel 4 mit 3 Zeilen"*. Ob das die **richtigen** drei sind,
war aus der Ausgabe nicht zu entscheiden: Ich musste `festkomma.hpp` an vier Stellen
oeffnen und `:161`, `:292`, `:356` von Hand nachrechnen. Eine Aenderung, die eine Zeile von
Regel 1 nach Regel 4 schoebe und eine andere zurueck, ergaebe **dieselbe Ausgabe**.

Die Gegenprobe steht heute nur im Kopfkommentar (`:120-125`, von Hand gezaehlt, mit
`festkomma.hpp:161,292,356` ausgeschrieben) — also genau die Sorte Zahl, die still veraltet,
weil kein Lauf sie prueft.

## Warum ein eigenes Paket

Es aendert die **Ausgabe** und nicht die Einordnung. Zusammen mit einer Regelaenderung
gefahren, waere der Unterschied zwischen „eine Zeile hat die Regel gewechselt" und „die
Ausgabe ist laenger geworden" im selben Lauf nicht mehr zu trennen — dasselbe Argument, mit
dem `0292` sich von `0290` trennt.

Der Vorbau steht in der Fabrik schon: `zahlwort_riegel` druckt *„Jede Fundstelle mit ihrem
Urteil -- der ausgeschriebene Nachlass dieses Riegels"* und nennt auch, was nichts
behauptet (`uebersetzung-2026-09-10.md:642-657`). Der Multiplikationsriegel ist der einzige
der fuenf Riegel, der seine Einordnung fuer sich behaelt.

## Was es kostet

42 Zeilen mehr im Nachtbericht, heute rund 2 kB, und die Zahl waechst mit dem Kern. Das ist
der Preis dafuer, dass die naechste Regelaenderung ueberhaupt pruefbar ist; wer ihn nicht
zahlen will, lehnt hier ab und nicht spaeter.

## Fuer den Projektmanager

`dateien` schneidet sich mit `0292` (dieselbe Datei). Beide sind klein, keins haengt am
anderen — sie brauchen nur zwei verschiedene Naechte.
