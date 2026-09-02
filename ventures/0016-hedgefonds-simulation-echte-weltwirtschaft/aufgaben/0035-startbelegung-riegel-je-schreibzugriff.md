---
id: 0035-startbelegung-riegel-je-schreibzugriff
rolle: kernbauer
status: vorschlag
haengt_an: [0027-zustand-schreibweg-schliessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustand_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schreiber_probe.cpp]
abnahme: Die vier Bedingungen im Abschnitt Abnahme. Der Pruefer urteilt gegen diese Liste und gegen nichts sonst.
---

# Der Startwertzugang wird beim Schreiben verriegelt, nicht beim Binden

Vorgabe: `technik.md` T18. Der Befund, aus dem dieses Paket entsteht:
`befunde/pruefung-0027-zustand-schreibweg-schliessen-2026-09-02.md`, Befund 1. Lies ihn im
Wortlaut; hier steht nur, was zu tun ist.

## Der Befund, in drei Saetzen

Paket 0027 hat den rohen Schreibzugriff des Zustands geschlossen und einen benannten
Startwertzugang danebengestellt. Dieser Zugang fragt genau einmal, ob die Partie noch vor
ihrer ersten Runde steht: **im Konstruktor**. Seine Setzfunktion fragt nichts, und deshalb
schreibt ein einmal gebundener Zugang beliebig lange weiter -- auch dann, wenn der Zustand
inzwischen eine Rundennummer traegt.

**So erzeugt man den Fehler, ohne eine Zeile zu schreiben:** `zustand_probe.cpp:619-625`
bindet einen Zugang an einen frischen Zustand und benutzt ihn in einer Schleife ueber alle
310 Plaetze. Bei Platz 306 setzt die Schleife `partie.runde` auf 306; ab Platz 307 ist die
Partie also formal gelaufen, und der Zugang schreibt trotzdem weiter -- dreimal dort und
fuenfmal im Block darunter. Acht Schreibzugriffe hinter dem Riegel, ohne Ursachensatz, in
einem gruenen Test.

## Warum das ein eigenes Paket ist

Es ist **kein Ruecklauf zu 0027** in der Sache: Die Wahl der Zugriffsform und die
Entscheidung gegen eine stumpfe Pruefung je Aufruf sind richtig und im Quelltext gut
begruendet. Der Bauagent hat den Preis dieser Wahl sogar hingeschrieben. Was fehlt, ist
die Fassung dazwischen -- und die braucht eine eigene Ueberlegung, keine Nachbesserung im
Vorbeigehen.

Es ist auch nichts, was ein spaeteres Paket beilaeufig mitnimmt: Solange der Zugang offen
bleibt, gelten die beiden Zusagen des Schreibers (genau einmal je Runde, acht Kanaele und
nicht neun) wieder nur fuer den, der sich daran haelt. Das ist genau der Zustand, den 0027
beenden sollte.

## Was du baust

Eine Verriegelung, die beim **Schreiben** greift und nicht beim Binden -- ohne die
vorhandenen Belegungsschleifen zu brechen.

Der Grund, warum die naheliegende Fassung nicht geht, steht im Quelltext von 0027 und gilt:
Unter den 310 Groessen ist `partie.runde` selbst. Eine Pruefung, die vor jeder Setzung
stumpf verlangt, dass die Runde null ist, wuerde eine Belegung je nach Reihenfolge ihrer
Aufrufe mal zulassen und mal abbrechen -- und die beiden Schleifen in `zustand_probe.cpp`
sofort roten.

Der Ausweg, den ich sehe (die Form entscheidest du): Ein Zugang darf weiterschreiben,
solange die Partie vor ihrer ersten Runde steht **oder** er die Rundennummer selbst gesetzt
hat. Dann traegt die Schleife weiter, und ein Zugang, an dem die Runde vorbeigelaufen ist,
faellt beim naechsten Schreibzugriff auf.

Zwei Nebendinge, die dazugehoeren:

1. **Ein Zugang laesst sich heute kopieren.** Ob eine Kopie das Recht mitnimmt, ist eine
   Frage, die dieses Paket beantworten muss -- so oder so, aber ausgeschrieben.
2. **Der Zugang zeigt auf einen Zustand, den er nicht besitzt.** Dass er ihn ueberleben
   kann, ist der Kern des Befundes; ob du das mit einer Verriegelung oder mit einer
   engeren Lebensdauer loest, ist deine Entscheidung.

## Was du nicht baust

- **Keine Aenderung an der Setzfunktion des Schreibers, an der Ursachenkette, am Bitfeld
  oder an der Rundenendpruefung.** Sie sind abgenommen.
- **Keine Aenderung an der Sichtbarkeit des rohen Schreibzugriffs.** Bedingung 1 und 2 von
  0027 sind erfuellt und mit eigenen Uebersetzungsversuchen belegt; sie muessen erfuellt
  bleiben.
- **Kein elftes Feld im Zustand.** T15 haelt die 310, und 0027 hat aus gutem Grund den
  Riegel in den Zustand selbst gelegt statt in einen Merker daneben.

## Abnahme

1. **Ein Zugang, an dem eine Runde vorbeigelaufen ist, bricht beim naechsten
   Schreibzugriff ab.** Die Probe bindet einen Zugang vor der ersten Runde, laesst eine
   Runde ueber denselben Zustand laufen, schreibt das Rundenende zurueck und benutzt den
   alten Zugang. Das muss ein harter Fehler mit ausgeschriebener Meldung sein, und die
   Meldung nennt den Grund, nicht nur den Ort.
2. **Die beiden Belegungsschleifen in `zustand_probe.cpp` laufen unveraendert durch.** Der
   Zaehlzustand ergibt weiterhin die Pruefsumme `25e8b19071bea26c`, und die Gegenprobe mit
   zwei getauschten Feldern ergibt weiterhin eine andere. Wer diese Zahl aendert, hat die
   Feldreihenfolge angefasst und braucht dafuer einen eigenen Grund.
3. **Alle fuenf Bedingungen von 0027 halten unveraendert**, insbesondere: Feld und roher
   Schreibzugriff bleiben von aussen Uebersetzungsfehler, die beiden Suchlaeufe ueber
   `kern/` bleiben leer, ein Startwert erzeugt weiterhin keinen Ursachensatz, und das
   Binden an einen Zustand mit gelaufener Runde bleibt ein harter Fehler.
4. **Beide Kaesten stehen namentlich und bestanden im Uebersetzungsbericht**
   (`zustand_probe` und `schreiber_probe`). Ein leerer Bauabschnitt ist ein Ruecklauf.

## Was ausdruecklich kein Befund ist

- **Wie die Verriegelung gebaut ist** -- ob als Merker im Zugang, als engere Lebensdauer
  oder als Zugang, der den Zustand als Wert nimmt und ihn zurueckgibt. `specs/` schweigt
  dazu, also ist die Entscheidung des Bauagenten gueltig, solange Bedingung 1 und 3
  zugleich halten.
- **Der Name der Meldung und der Wortlaut ihres Textes.**

## Was hier nicht hingehoert

Der zweite Befund derselben Pruefung -- dass `kern/test/schranken_probe.cpp` von Paket 0027
geaendert wurde, ohne in dessen Dateiliste zu stehen -- ist eine Sache fuer `rueckstand.md`
und nicht fuer dieses Paket. Erwaehnt sei nur die Fussangel: Die dortige Hilfsfunktion
bindet je Aufruf einen neuen Zugang und bricht deshalb ab, sobald eine Schranke einen
Randfall auf einem Zustand mit gelaufener Runde braucht.

## Rueckläufe

0.

## Berichtigung

Im Abschnitt *Was du nicht baust* steht "kein elftes Feld im Zustand". Gemeint ist das
**311.** Feld: T15 haelt die Zahl der Groessen bei 310, und genau deshalb hat 0027 den
Riegel auf ein vorhandenes Feld gelegt statt auf einen Merker daneben.
