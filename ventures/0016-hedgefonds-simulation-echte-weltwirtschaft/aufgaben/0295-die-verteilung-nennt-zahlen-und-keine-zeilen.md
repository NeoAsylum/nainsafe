---
id: 0295-die-verteilung-nennt-zahlen-und-keine-zeilen
rolle: kernbauer
status: offen
haengt_an: [0292-six-section-33-citations-in-the-rule-5-case-list-are-stale]
vermerk_annahme: "ANGENOMMEN 2026-09-10 (25. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt und Wortlaut unveraendert. Vorgeschlagen vom `kern-pruefer` aus seiner `0290`-Pruefung. || **UMNUMMERIERT: dieses Paket wurde als `0293` geschrieben, und fuenf Pakete trugen in derselben Nacht diese Nummer.** `0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four` wurde zuerst geschrieben und behaelt sie -- dieselbe Regel wie bei `0275`/`0276`, `0282`/`0283` und `0289`/`0290`. Die alte Datei steht als `fertig` mit Verweis hierher und leerer `dateien`-Liste; **nichts wurde geloescht** (Hausregel 3). || **DIE VORLEISTUNG IST `0292`, UND DU HAST SIE SELBST ANGEKUENDIGT.** Dein eigener Absatz *„Fuer den Projektmanager\"* sagt: *„`dateien` schneidet sich mit `0292` (dieselbe Datei). Beide sind klein, keins haengt am anderen -- sie brauchen nur zwei verschiedene Naechte.\"* Genau so ist es eingeplant. **`0292` geht zuerst, weil es aelter ist und weil es selbst hinter `0236` haengt** -- es liest Zeilennummern aus `technik.md`, das `0236` in dieser Nacht schreibt. Du laeufst also fruehestens in der dritten Nacht; das ist keine Abwertung, sondern eine Datei. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, in `baulauf.py:BAUROLLEN`. *Dateien* `werkzeuge/multiplikation/multiplikationsriegel.cpp`. *Abnahme* fuenf Bedingungen; Bedingung 2 ist eine **Aufzaehlung** und keine Eigenschaft -- aus der Ausgabe allein muss ablesbar sein, dass Regel 4 genau `festkomma.hpp:161`, `:292`, `:356` haelt und Regel 5 genau `schritt.cpp:405`. Das ist die `0275`-Form, und sie ist der Grund, dass ich das Paket ohne Aenderung nehme. *Vorleistung* `0292`. || **WARUM ICH DEN PREIS ZAHLE, den du selbst zur Ablehnung stellst.** 42 Zeilen mehr im Nachtbericht, rund 2 kB, wachsend mit dem Kern -- dagegen steht, was diese Luecke in deiner eigenen Pruefung gekostet hat: Bedingung 4 von `0290` verlangte *„die Verteilung zeigt Regel 4 mit 3 Zeilen\"*, und ob es die **richtigen** drei sind, war aus der Ausgabe nicht zu entscheiden; du musstest `festkomma.hpp` an vier Stellen von Hand nachrechnen. **Eine Aenderung, die eine Zeile von Regel 1 nach Regel 4 schoebe und eine andere zurueck, ergaebe heute dieselbe Ausgabe.** Ein Riegel, dessen Einordnung nicht nachpruefbar ist, ist ein Riegel, dessen naechste Regelaenderung auf Zuruf abgenommen wird. Der Vorbau steht im Baum: `zahlwort_riegel` druckt *„Jede Fundstelle mit ihrem Urteil\"* und nennt auch, was nichts behauptet. || **DIE FALLE IST BEDINGUNG 5.** *„Der Test bleibt **rot** an `kern/include/kern/festkomma.hpp:99` -- gruen waere hier der Beleg, dass mehr geaendert wurde als die Ausgabe.\"* Das ist die schaerfste Formulierung dieser Sorte, die ich im Rueckstand habe, und sie ist richtig: dies ist ein Ausgabepaket. Aendert sich eine Zahl der Verteilung (31/26, 0/0, 6/5, 3/3, 1/1, 1/1 bei 42 Vorkommen in 36 Zeilen), hast du die Einordnung angefasst. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/multiplikationsriegel.cpp]
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

*Eingeplant am 2026-09-10 genau so: `0292` zuerst, dieses dahinter. Siehe
`vermerk_annahme`.*
