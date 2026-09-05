---
id: 0098-diff-kennungen-ohne-differenz
rolle: kernbauer
status: offen
haengt_an: [0010-zustandsausgabe-drei-ebenen, 0097-zustandsausgabe-probe-zuordnungen-festnageln]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustandsausgabe.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustandsausgabe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustandsausgabe_probe.cpp]
abnahme: Die Entscheidung ist getroffen und steht im Annahmevermerk vom 2026-09-05: Es gilt T5, nicht die Abnahmezeile von 0010. Zu bauen ist daher -- die Unterschiedsebene nennt fuer `partie.jahrgang_id` und `partie.parameter_pruefsumme` alten und neuen Wert und an der Stelle der Differenz einen Strich samt Grund, waehrend jede Adresse der zwoelf uebrigen Skalenklassen ihre Differenz unveraendert behaelt. Eine Probe weist beides an einem einzigen Zustandspaar nach, das sich in genau einer Kennung und in genau einer Nicht-Kennung unterscheidet: die Kennung ohne Differenz und mit Grund, die Nicht-Kennung mit ihrer Differenz wie bisher. Ein Mutant, der die Ausnahme wieder herausnimmt, macht diese Probe rot -- ohne diesen Rotnachweis ist die Probe nicht belegt. `specs/` wird nicht angefasst.
---

# ENTSCHIEDEN UND ANGENOMMEN — 2026-09-05, Projektmanager

## Die Entscheidung: **es gilt T5.**

Du hast sie richtigerweise nicht selbst getroffen, und sie war fällig. Hier ist sie, mit
Begründung, an genau einer Stelle:

**Von den beiden Zweigen, die du anbietest, steht mir nur einer offen.** Der andere —
„T5 Klasse 12 bekommt den Zusatz, dass die Anzeige einer Differenz keine Arithmetik im
Sinne des Verbots ist" — ändert `technik.md`. Das ist eine Entscheidung über den Entwurf,
und die trifft der Projektmanager nicht; er meldet sie. Ich könnte sie also nur an den
Geschäftsführer weiterreichen und das Paket so lange liegen lassen.

**Das ist nicht nötig, denn der Widerspruch ist gar keiner zwischen zwei Vorgaben.** T5 ist
die Vorgabe. Die andere Seite ist die `abnahme`-Zeile von 0010, und die habe **ich**
geschrieben. Sie sagt „jede Adresse … mit altem Wert, neuem Wert und Differenz" und macht
keine Ausnahme — das war zu weit gefasst, denn T5 stand da vorher. Ein Abnahmekriterium von
mir, das eine Vorgabe überschreibt, ist mein Fehler und nicht der Entwurf. Es ist derselbe
Fall wie die T50-Bedingung in der Abnahme von 0002: **das Kriterium war meines und war
falsch.**

Damit fällt der zweite Zweig weg, ohne dass jemand über `technik.md` entscheiden muss. Es
bleibt der erste, und der ist gebaut, nicht verhandelt.

**Der Bauagent von 0010 hat nichts falsch gemacht.** Er hat sein Kriterium wörtlich
genommen, und das war die zulässige Lesart. 0010 steht seit dem 2026-09-05 auf `fertig`;
dieses Paket ist kein Rücklauf gegen es und wird auch nicht als einer gezählt.

## Zur Annahme

Vier Prüfungen: **Rolle** — `projektmanager` steht **nicht** in `BAUROLLEN`; kein Runner
hätte dieses Paket je gezogen. Da der erste Schritt, die Entscheidung, mit diesem Vermerk
erledigt ist, ist der Rest ein Kernbauerlauf, und die Rolle ist auf `kernbauer` geändert.
Das ist genau der Fehler, den der erste Vorschlag dieses Vorhabens am 2026-09-02 mit
`rolle: builder` hatte, und der Grund, warum die Rollenfrage bei mir zuerst steht.

**Abnahme** auf den einen verbleibenden Zweig verkürzt, um den Rotnachweis ergänzt.
**Dateischnitt**: `zustandsausgabe.hpp` ist dazugekommen — der Kopf zitiert die T5-Regel
bereits in den Zeilen 325 bis 327 und wird den Strich mit erklären müssen; ohne die Datei
in der Liste müsstest du dafür außerhalb schreiben. Beide anderen Dateien waren von 0010
beansprucht, das im selben Lauf `fertig` geworden ist.

**Abhängigkeit** — **0097 ist als Reihenfolgesperre dazugekommen**, nicht als sachliche
Abhängigkeit. Du hast die Kollision selbst benannt; hier ist die Entscheidung, um die du
gebeten hast. 0097 nagelt in derselben Probendatei fest, was heute richtig ist; du änderst
danach eine Spalte. Umgekehrt schriebe 0097 seine siebzehn Mutationsnachweise gegen einen
Code, den du gerade bewegst. Die bloße Dateikollision reicht als Schutz nicht: Sobald 0097
auf `gebaut` steht, ist sein Anspruch für `startbereit()` unsichtbar (`baulauf.py:273`),
und du würdest eingeplant, während sein Prüfer misst.

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
