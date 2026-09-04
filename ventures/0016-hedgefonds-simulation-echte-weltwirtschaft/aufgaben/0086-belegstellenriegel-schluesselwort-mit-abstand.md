---
id: 0086-belegstellenriegel-schluesselwort-mit-abstand
rolle: testentwickler
status: vorschlag
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel faengt die dritte Belegstelle aus Paket 0034 in `daten/adressen.md` -- Schluesselwort mit fuenf Woertern Abstand zur Anfuehrung, Dateiname rechts vom Zitat. Die Zahl der gefundenen Zitate steigt gegenueber 24, keine Fundstelle wird dadurch zu Unrecht rot, und beide Lockerungen sind einzeln mit einem Mutanten belegt: wie viele der Zitate jede von ihnen traegt und wie viele Fundstellen sie neu erzeugt.
---

# Ein Schluesselwort, das nicht direkt vor der Anfuehrung steht, und ein Dateiname rechts davon

Vorschlag aus dem zweiten Lauf von `0067-belegstellenriegel-abschnittszitate`, 2026-09-04.
Die Form ist im Kopfkommentar von `belegstellen_riegel.cpp` als zweite ausgewiesene Luecke
beschrieben; hier steht, was sie kosten wuerde.

## Der Fall, und er ist echt

`daten/adressen.md` zitiert in der Herleitung zu `land.CN.wechselkurs` den T46-Vorspann aus
`technik.md`. Sinngemaess: *T46 zaehlt seine elf Vorgabeadressen abschliessend auf -- die
<Schluesselwort> der Tabelle sagt es selbst: „…"* und dahinter, in Klammern, der Dateiname.

Paket 0034 hat diese Stelle am 2026-09-03 angelegt -- eine von dreien, um derentwillen der
Riegel ueberhaupt existiert. Zwei davon fangen seit dem 2026-09-04; diese nicht.

## Zwei Hindernisse, und keines allein reicht

1. **Abstand.** `ueberschrift_hinter` ueberspringt hinter dem Schluesselwort nur Leerzeichen
   und einen Gegenschraegstrich. Hier stehen fuenf Woerter dazwischen.
2. **Richtung.** `naechster_verweis` sucht den Dokumentnamen nur **links** vom Zitat. Hier
   steht er rechts, in der Klammer dahinter.

Wer nur eines loest, faengt die Stelle immer noch nicht. Das ist der Grund, warum es ein
Paket ist und keine Zeile im laufenden.

## Warum es ein eigenes Paket ist und nicht Teil von 0067

Beide Lockerungen sind Entscheidungen mit eigenem Nachweis, nicht Ergaenzungen einer
vorhandenen. Sie haben genau die Bauart, an der schon 0047 haengt:

* Wer beliebig viele Woerter zwischen Schluesselwort und Anfuehrung zulaesst, bindet jede
  Anfuehrung eines Satzes an das naechstgelegene Schluesselwort -- und wird rot, wo nichts
  kaputt ist. Ein Wortabstand ist eine Schwelle, und eine Schwelle ohne Messung ist geraten.
* Wer zusaetzlich nach rechts sucht, muss entscheiden, welcher der beiden Nachbarn gewinnt,
  wenn links und rechts ein Dokumentname steht. Dafuer gibt es heute kein Mass. Die
  Linksregel selbst ist gemessen und nicht gewaehlt: Ohne sie band der Riegel ein
  franzoesisches Zitat in `lizenzbefund-reihen.md` an die falsche Datei und wurde zu
  Unrecht rot.

Beides in 0067 mitzunehmen hiesse, eine gemessene Regel gegen eine ungemessene zu tauschen,
und zwar in demselben Lauf, in dem der Riegel gruen gemeldet wird. Der Ruecklauf zu 0067
verlangt ausdruecklich nur die **Aussage** ueber diese Form, nicht ihr Fangen.

## Wovor es zu warnen gilt

Der Riegel liest seinen eigenen Quelltext mit. Wird der Abstand gelockert, faengt er
Formulierungen im eigenen Kopfkommentar, die heute harmlos sind -- jede Prosa, die ein
Schluesselwort und irgendwo dahinter eine Anfuehrung traegt. Wer dieses Paket abarbeitet,
misst das zuerst und schreibt nicht zuerst.

## Was ausdruecklich nicht dazugehoert

* **Aufraeumen in `specs/` oder in `daten/adressen.md`.** Die Form wird gefangen, nicht
  umgeschrieben.
* **Die Luecke aus Paket 0079** (Ueberschrift ohne Anfuehrung). Andere Ursache, anderer
  Nachweis.
