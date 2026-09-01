---
id: 0010-zustandsausgabe-drei-ebenen
rolle: kernbauer
status: offen
haengt_an: [0002-fondsbewertung-definieren]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/zustandsausgabe.rs]
abnahme: Drei Aufrufe liefern Text. `uebersicht()` fasst den Zustand in höchstens 40 Zeilen. `detail(bereich)` gibt einen Bereich vollständig mit allen 310 Adressen ihres Bereichs, je mit Wert, Skalenklasse und Herkunft. `diff(a, b)` nennt jede Adresse, die sich zwischen zwei Zeitpunkten geändert hat, mit altem Wert, neuem Wert und Differenz. Ein Test weist für jede der 310 Adressen nach, dass sie in mindestens einer der drei Ausgaben vorkommt.
---

# Die Zustandsausgabe — und sie ist die erste Oberfläche

G8 verlangt sie ohnehin: Übersicht, Detail, Veränderung. Sie ist keine Debug-Zugabe,
sondern **das, worüber diese Fabrik ihr eigenes Produkt überhaupt kennt** — der
Selbstspieler, der Rückvergleicher, der Bruchtester und jeder Prüfer lesen nichts
anderes.

Und sie ist zugleich Stufe 1 der Oberfläche (`specs/.../zielbild.md`): Mit ihr ist das
Spiel spielbar und selbstspielbar, bevor eine einzige Grafik existiert.

## Die drei Ebenen

**`uebersicht()`** — der Gesamtzustand aggregiert, in einem Blick erfassbar, höchstens
40 Zeilen. Fondsvermögen, Einfluss je Land, die vier Politikinstrumente je Land, Runde,
Stand gegenüber der Siegbedingung.

**`detail(bereich)`** — ein Bereich vollständig. Jede Adresse mit ihrem Wert, ihrer
Skalenklasse (dreizehn nach T49) und ihrer Herkunft (fünf Arten nach T45). Wer hier
liest, muss nicht raten, ob eine Zahl Cent oder Tausend ist.

**`diff(a, b)`** — was sich zwischen zwei Zeitpunkten geändert hat, mit altem Wert,
neuem Wert und Differenz. Das ist die Ebene, an der ein Agent erkennt, **ob eine
Änderung gewirkt hat und wie** — und damit die wichtigste der drei.

## Die Prüffrage, an der es sich messen lässt

> **Kann ein Agent aus der Textausgabe allein erkennen, ob das System richtig gerechnet
> hat?** Nicht ob es lief — ob das Ergebnis *stimmt*.

Fehlt eine Größe, ist das Produkt für diese Fabrik an dieser Stelle blind. Deshalb
verlangt die Abnahme den Nachweis über **alle 310 Adressen**: Jede muss in mindestens
einer der drei Ausgaben vorkommen. Das ist mechanisch prüfbar und genau deshalb das
Kriterium.

## Was hier nicht hineingehört

Keine Farben, keine Rahmen, kein Layout. Das ist Stufe 2 und 3 und wird aus dem Schema
erzeugt, nicht hier von Hand geschrieben. Deine Ausgabe ist Text, den ein Mensch lesen
**kann** und ein Agent lesen **muss**.
