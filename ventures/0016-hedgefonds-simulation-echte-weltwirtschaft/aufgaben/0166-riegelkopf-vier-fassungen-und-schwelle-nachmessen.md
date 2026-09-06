---
id: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen
rolle: testentwickler
status: offen
haengt_an: [0115-riegelkopf-drei-zahlen-nachmessen, 0130-belegstellenriegel-berichtsreihenfolge-festnageln, 0147-belegstellenriegel-ortsfrage-mit-anker]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. 0115 stand schon in deiner Liste und ist seit heute fertig; 0130 und 0147 sind dazugekommen und sind Reihenfolgesperren, keine sachlichen Abhaengigkeiten. Drei Pakete liegen auf `belegstellen_riegel.cpp`, die Reihe lautet 0130, 0147, du. Aus 0130 und 0147 brauchst du nichts; sie fassen nur dieselbe Datei an. Dein Vorher-Stand ist der dann geltende HEAD -- such am Text, nicht an der Zeilennummer, denn zwei Pakete haben den Kopfkommentar vor dir angefasst.
abnahme: Die Tabelle der vier Fassungen und der Absatz zur Schwelle im Kopfkommentar von `belegstellen_riegel.cpp` nennen Zahlen, die am Auslieferungsstand gemessen sind, und nennen den Stand, gegen den sie gemessen wurden. Jede der sechs Zeilen ist mit dem Aufruf belegt, der sie erzeugt hat, im Rumpf abgedruckt; die Aussage, die der Absatz aus ihnen zieht -- keine Lockerung allein traegt ein Zitat, die Schwelle vier faengt die Stelle nicht und fuenf faengt sie --, wird an den neuen Zahlen erneut gepruft und nicht uebernommen. Ein Messskript unter `befunde/` liest die Zahlen aus dem Kommentar und vergleicht sie gegen die Mutanten, wird an der Fassung davor rot und bleibt an der neuen gruen. Der Riegel meldet vor und nach der Aenderung dieselben drei Zahlen von Bedingung 2, gemessen im selben Aufruf am selben Baum.
---

# Die vier Fassungen und die Schwelle, gegen den Stand gehalten, an dem sie stehen

Aufgefallen beim Bau von `0115-riegelkopf-drei-zahlen-nachmessen` am 2026-09-06.
Dasselbe Paket hat drei Angaben desselben Kopfkommentars nachgemessen; diese hier lagen
daneben und gehoerten nicht zur Dateiliste jenes Auftrags -- genauer: nicht zu seinem
Gegenstand, denn der Vorschlag nimmt „jede Aenderung an Muster, Normierung, Zaehlung oder
an einer Zeile der Faelle" ausdruecklich aus und benennt genau drei Stellen.

## Was gemessen ist

Am 2026-09-06, Stand `5d5e2d6`, mit `bau/kp0086-mutieren.py`:

| Fassung | Kopf sagt (2026-09-05) | gemessen 2026-09-06 |
|---|---|---|
| keine von beiden (`ohne-abstand`) | 33 / 33 / 58 | 39 / 39 / 47 |
| nur der Wortabstand (`nur-abstand`) | 33 / 33 / 59 | 39 / 39 / 48 |
| nur die Suche nach rechts (`nur-rechts`) | 33 / 33 / 58 | 39 / 39 / 47 |
| beide | 34 / 34 / 58 | 40 / 40 / 47 |
| Schwelle vier (`abstand4`) | 58 Fundstellen | 47 |
| Schwelle fuenf (`abstand5`) | 59 Fundstellen | 48 |

Gelesen wird die Zeile so: Zitate / aufgeloest / uebergangene Fundstellen.

**Die Aussage ist heil, jede Zahl ist falsch.** Der Abstand zwischen den Zeilen stimmt
noch -- keine Lockerung allein traegt ein Zitat, zusammen tragen sie genau eines, und die
Schwelle faellt zwischen vier und fuenf um genau eine Fundstelle. Verschoben hat sich
allein die Basis, und zwar um elf Fundstellen nach unten und sechs Zitate nach oben.

## Warum das ein eigenes Paket ist und keine Zeile in 0115

**Weil 0115 seine Grenze selbst zieht.** Sein Rumpf nimmt Muster, Normierung, Zaehlung
und die Faelle aus und nennt drei Stellen, an denen berichtigt werden darf. Wer die
Tabelle mitnimmt, arbeitet an einer Abnahme vorbei, die absichtlich eng geschnitten ist
-- und er nimmt der Pruefung ihren Massstab: Die Bedingung „eine Berichtigung, die eine
Zahl des Riegels bewegt, ist ein Fehlschlag" laesst sich nur halten, wenn die Menge der
berichtigten Stellen bekannt ist.

**Und weil der Gegenstand ein anderer ist.** Die drei Angaben von 0115 waren *falsch
gezaehlt* -- eine Fuenf, wo sechs standen; eine Summe, die gegen sich selbst nicht
aufging; eine Ordnungszahl, die dem Satz davor widersprach. Diese sechs Zahlen sind
*richtig gemessen und veraltet*. Das ist ein anderer Fehler mit einer anderen Abhilfe:
nicht nachzaehlen, sondern den Stand dazuschreiben und ein Messgeraet danebenstellen, das
laut wird, wenn die Basis wieder wandert. 0115 hat diese Bauart fuer drei Angaben gebaut;
hier ist sie auf sechs weitere anzuwenden.

**Die Reihenfolge:** nach 0115, weil beide dieselbe Datei halten und 0115 im selben
Kopfkommentar schreibt. `haengt_an` nennt es deshalb -- als Kollisionsschutz, nicht als
sachliche Abhaengigkeit.

## Zwei Hinweise für den, der es baut

**Der Riegel liest seinen eigenen Quelltext mit.** Ein neuer Satz im Kopfkommentar kann
eine Fundstelle erzeugen und damit genau die Zahl bewegen, die er nennt. Beim Bau von
0115 ist das eingetreten: Ein zweiter Gegenstrich hinter dem Wort `Namensart::Ueberschrift`
schloss die Anfuehrung, die das Schluesselwort davor eroeffnet, und der Riegel wurde rot.
**Miss nach der letzten Zeile deines Kommentars, nicht davor.**

**Die Mutanten der Schwelle brauchen den Filter.** `kp0086-mutieren.py abstand4` und
`abstand5` laufen durch, `ohne-marken-rein` nicht: Er laesst Fall 4 in `ABSTANDSFAELLE`
reissen und bricht mit Code 2 ab, ehe der Bestand gelesen ist. Der Weg steht im Rumpf von
0115, das Messskript unter `befunde/messung-0115/`.
