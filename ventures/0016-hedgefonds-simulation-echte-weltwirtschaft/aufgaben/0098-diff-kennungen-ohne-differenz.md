---
id: 0098-diff-kennungen-ohne-differenz
rolle: projektmanager
status: vorschlag
haengt_an: [0010-zustandsausgabe-drei-ebenen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustandsausgabe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustandsausgabe_probe.cpp]
abnahme: Entschieden ist, welche der beiden Vorgaben fuer die Klasse 12 gilt -- die Abnahme von 0010 ("jede Adresse ... mit alter Wert, neuer Wert und Differenz") oder T5 ("jede Arithmetik ausser Gleichheit ist ein Fehler"), und die Entscheidung steht mit Begruendung an genau einer Stelle. Faellt sie zugunsten von T5, nennt die Unterschiedsebene fuer `partie.jahrgang_id` und `partie.parameter_pruefsumme` alten und neuen Wert und an der Stelle der Differenz einen Strich samt Grund, waehrend jede Adresse der zwoelf uebrigen Klassen ihre Differenz unveraendert behaelt; eine Probe weist beides an einem Zustandspaar nach, das sich in genau einer Kennung und in genau einer Nicht-Kennung unterscheidet. Faellt sie zugunsten der Abnahme, traegt T5 Klasse 12 den Zusatz, dass die Anzeige einer Differenz keine Arithmetik im Sinne des Verbots ist -- dann aendert sich am Code nichts und dieses Paket schliesst mit der Berichtigung des Dokuments.
---

# Zwei Vorgaben, ein Feld: `diff` subtrahiert Bitmuster

## Der Widerspruch, beide Seiten im Wortlaut

**T5, Klasse 12** (`specs/0016-.../technik.md`, Zeile 291):

> | 12 | **Kennungen** (Jahrgangskennung, Parametersatz-Pruefsumme) | Bitmuster ohne
> Groessenbedeutung | -- | jede `i64`; **jede Arithmetik ausser Gleichheit ist ein
> Fehler** |

Und der Absatz darunter (Zeile 315) nennt das Verbot "den eigentlichen Inhalt" der
Klasse: "Eine Pruefsumme, die versehentlich in eine Summe geraet, erzeugt eine Zahl, die
keine Pruefung bemerkt, weil sie in keinem Wertebereich liegt."

**Die Abnahme von Paket 0010:**

> `diff(a, b)` nennt **jede** Adresse, die sich zwischen zwei Zeitpunkten geaendert hat,
> mit altem Wert, neuem Wert und Differenz.

Beides gleichzeitig ist nicht zu haben, solange "Differenz" eine Subtraktion bedeutet.

## Was heute geschieht

Gemessen am 2026-09-04 mit einer eigenen Probe im Pruefbaum, zwei Zustaende, die sich in
genau einem Feld unterscheiden:

```
partie.parameter_pruefsumme  alt -6917529027641081856  neu 4611686018427387904
    Differenz 11529215046068469760  [K12 Kennung, Bitmuster ohne Groessenbedeutung]
```

Die Zeile widerspricht sich in sich selbst: Am Ende sagt sie, die Zahl habe keine
Groessenbedeutung; in der Mitte nennt sie eine Groessendifferenz. Dasselbe fuer
`partie.jahrgang_id`.

Der Kopf des Moduls kennt die Regel und zitiert sie -- `zustandsausgabe.hpp`,
Zeile 325 bis 327: *"Die beiden Kennungen sind die einzigen Adressen, auf denen nach T5
jede Arithmetik ausser der Gleichheit ein Fehler ist. Sie stehen hier mit ihrer Klasse,
damit das in der Ausgabe abzulesen ist, statt in einem Dokument zu stehen."* Zwei
Funktionen weiter laeuft `diff` ueber alle 310 Plaetze ohne Ausnahme und subtrahiert.

## Warum das an den Projektmanager geht und nicht an den Bauagenten

Der Bauagent hat seine Abnahme woertlich genommen, und das war die zulaessige Lesart --
sie sagt "jede Adresse" und macht keine Ausnahme. **Ein Pruefer senkt kein
Abnahmekriterium und hebt keine Vorgabe auf.** Beides steht hier gegeneinander, und die
Wahl ist eine Entscheidung ueber Dokumente, nicht ueber Code. Paket 0010 selbst ist
damit erfuellt und bekommt von mir `geprueft`.

## Warum es trotzdem entschieden werden muss und nicht liegen bleiben kann

Die Unterschiedsebene ist nach dem Arbeitspaket 0010 "die Ebene, an der ein Agent
erkennt, ob eine Aenderung gewirkt hat und wie" -- und ihr Leser ist ausdruecklich eine
Maschine. Ein Selbstspieler, der Differenzen ueber Runden verfolgt, hat keinen Anlass,
eine Spalte je Skalenklasse verschieden zu lesen. `11529215046068469760` sieht aus wie
ein Ausschlag und ist keiner. Genau davor warnt T5, und zwar mit derselben Begruendung,
mit der dieselbe Datei ihre eigene `i128`-Entscheidung begruendet: eine wohlgeformte
falsche Zahl, die keine Pruefung bemerkt.

Der Aufwand ist in beiden Richtungen klein. Die eine Fassung ist ein `if` auf die
Skalenklasse in `diff` plus zwei Zusicherungen; die andere ist ein Halbsatz in T5.
Teuer ist allein, die Frage offen zu lassen, weil sie mit dem Abschluss von 0010 aus dem
Blick faellt.

## Fuer den Projektmanager

**Die `dateien`-Liste schneidet sich mit
`0097-zustandsausgabe-probe-zuordnungen-festnageln`** aus demselben Pruefbericht: Beide
fassen `kern/test/zustandsausgabe_probe.cpp` an. Die beiden koennen deshalb nicht
gleichzeitig laufen. Sie sind trotzdem getrennt, weil dieses Paket eine Entscheidung
braucht und 0097 keine -- und weil dieses Paket in der einen Auslegung gar keinen Code
anfasst, in welchem Fall die `dateien`-Liste auf `specs/` schrumpft und die Kollision
entfaellt.

**`rolle: projektmanager`** steht hier, weil der erste Schritt die Entscheidung ist und
nicht das Bauen. Steht sie, ist der Rest je nach Ausgang ein Kernbauer- oder ein
Architektenlauf.
