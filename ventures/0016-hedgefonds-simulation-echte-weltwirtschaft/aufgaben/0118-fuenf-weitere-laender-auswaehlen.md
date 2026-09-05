---
id: 0118-fuenf-weitere-laender-auswaehlen
rolle: spielentwerfer
status: vorschlag
haengt_an: [0117-geschaetzter-politikpfad-und-zwei-laenderklassen]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme".
---

# Fünf weitere Länder — welche, warum, und in welcher Klasse

**Anweisung des Betreibers, 2026-09-05:** *„Lass uns insofern direkt 5 weitere Länder
einplanen."* Aus vier werden neun.

Das **widerspricht einer festgehaltenen Entscheidung.** `spiel.md`, *Was bewusst fehlt*:
„Zwölf Länder vervierfachen die Rückkopplungswege ohne ein Maß zu verbessern." Neun liegt
zwischen den vier des Entwurfs und den zwölf der Idee. Der Betreiber hat die Zahlen
unten gesehen und entschieden; deine Aufgabe ist die Ausführung, nicht die Revision.
**Widersprich nicht, sondern gestalte.**

## Was neun Länder kosten

Gerechnet aus den Konstanten in `kern/zustand.hpp`; die Formel reproduziert für `L = 4`
exakt die heutigen 310.

| Block | L=4 | L=9 | |
|---|---:|---:|---|
| Länder (44 je Land) | 176 | 396 | 2,2× |
| Handel `G·(G−1)·2` | 40 | **180** | **4,5×** |
| Nachahmer | 12 | 27 | 2,2× |
| Positionssteckplätze | 20 | **45** | 2,2× |
| Beteiligungen | 24 | 54 | 2,2× |
| fest (Restwelt, Fonds, Markt, Partie …) | 38 | 38 | 1,0× |
| **Zustand gesamt** | **310** | **740** | **2,4×** |

Und je nach Klassenwahl aus 0117:

| | alle neun als Rückvergleichsland | fünf als Spielland |
|---|---:|---:|
| Sollreihen | 62 | **27** |
| Prüfgegenstände | 36 | **16** |
| Datenreihen zu beschaffen | 5 × 19 | 5 × 19 |
| Lizenzstellen zusätzlich | 10 | 10 |

**Die Klassentrennung spart Daten und Prüfaufwand, keine Adressen.** Der Zustand wächst
in beiden Fällen auf 740.

## Die Entwurfsfrage, die das aufwirft

**Die Positionssteckplätze wachsen von 20 auf 45 — und das ist kein Geometriefall.**

`spiel.md` begründet die Knappheit als Quelle der Entscheidungsdichte: bis zu **drei**
Aktionen je Runde, und *„wer alles tun kann, wählt nicht"*. Bei 20 Plätzen und drei
Aktionen ist die Wahl eng; bei 45 ist sie es nicht mehr im selben Maß. Der Zustand
kommentiert die Zwanzig ausdrücklich als feste Größe: *„Es gibt keine Liste, in die etwas
aufgenommen oder aus der etwas entfernt würde."*

**Der Betreiber hat am 2026-09-05 Weg A gewählt: die Steckplätze wachsen mit `L`,
von 20 auf 45.** Die Wahl steht nicht mehr offen. Was offen ist, ist die Folge daraus,
und sie ist deine Aufgabe:

> Drei Aktionen je Runde auf 45 Plätzen sind ein anderes Spiel als drei auf 20.
> **Sag, wie die Entscheidungsdichte erhalten bleibt.**

`spiel.md` nennt die Knappheit unter *Die härteste Vorgabe* als Quelle der
Entscheidungsdichte — *„wer alles tun kann, wählt nicht"*. Bei 45 Plätzen und
unveränderten drei Aktionen sinkt der Anteil des Spielfelds, den ein Spieler je Runde
berühren kann, von 15 auf 7 Prozent. Das kann richtig sein: Ein grösseres Brett bei
gleicher Zugzahl macht die Wahl **wichtiger**, nicht beliebiger. Es kann aber auch
bedeuten, dass eine Partie über R Runden das Feld nicht mehr abdeckt.

**Rechne es aus, statt es zu behaupten.** Wie viele der 45 Plätze kann ein Spieler über
die volle Partielänge überhaupt erreichen, und wie verhält sich das zu den 20 von heute?
Fällt die Deckung unter das, was die vier Masse tragen, benenne die Stellschraube, die
du empfiehlst — Aktionszahl, Partielänge oder Zusammenfassung von Plätzen — **und
empfiehl genau eine.** Der Betreiber entscheidet, du legst vor.

Verworfen ist damit **B** (gedeckelte Steckplätze mit Auswahlmechanik); die Begründung
für die Verwerfung ist die Entscheidung des Betreibers, nicht eine fachliche, und das
gehört so hingeschrieben.

## Wonach die fünf zu wählen sind

Dieselbe Regel wie bei den ersten vier: **strukturelle Verschiedenheit, nicht Bedeutung.**
Vier Kopien wären vier Kopien. Die heutigen vier decken großer Binnenmarkt mit Leitwährung
(US), Industrie mit gemanagtem Kurs (CN), Exportüberschuss ohne Zinshebel (DE),
Agrarexport mit volatiler Währung (BR).

Benenne für jedes neue Land die **Eigenschaft, die noch keines trägt** — Kandidatenfelder,
nicht Vorgaben: Rohstoffexporteur mit Währungsbindung, Finanzplatz ohne eigene Industrie,
Wirtschaft unter Kapitalverkehrskontrollen, Land in einer Zollunion, Schuldnerland unter
IWF-Programm.

**Die Datenlage ist Mitentscheider, nicht Nachgedanke.** `daten/nachmessung-zinsreihen-2026-09-05.md`
zeigt, wie unterschiedlich die Deckung ausfällt: Die USA tragen die Anleiherendite von
1953 bis 2021, Deutschland nur bis 2017, China trägt im ganzen Fenster keine einzige
jährliche Zinsreihe. Ein Land, dessen Reihen fehlen, ist damit nicht ausgeschlossen — es
wird ein **Spielland** nach 0117. Sag für jedes der fünf, welche Klasse du erwartest und
woran das hängt.

**Was nicht dazugehört:** Daten beschaffen, Lizenzen prüfen, `technik.md` ändern, den Kern
anfassen. Die Adressarithmetik ist 0116, die Klassen sind 0117.

## Abnahme

1. **Fünf Länder sind namentlich benannt**, jedes mit der strukturellen Eigenschaft, die
   noch keines der vier heutigen trägt, in einem Satz je Land.
2. **Jedem ist eine Klasse zugeordnet** (Rückvergleichsland oder Spielland) mit der
   Bedingung, unter der es die Klasse wechseln würde.
3. **Die Folge aus Weg A ist gerechnet, nicht behauptet.** Der Abschnitt nennt, wie
   viele der 45 Plätze ein Spieler über die volle Partielänge erreichen kann, gegen die
   20 von heute gerechnet, und benennt genau eine empfohlene Stellschraube, falls die
   Deckung unter das fällt, was die vier Masse tragen.
4. **Die Tabelle oben steht in `spiel.md`** mit den Werten für `L = 9`, und der Abschnitt
   *Was bewusst fehlt* ist auf die neue Zahl nachgezogen — die alte Aussage über zwölf
   Länder bleibt stehen und wird nicht gelöscht, sondern eingeordnet.
5. **`git diff` zeigt Änderungen ausschließlich in `spiel.md`.** Keine Zahl in
   `technik.md`, `reihen.toml` oder im Kern wird angefasst; die 310 bleiben stehen, bis
   0116 die Ableitungskette geschrieben hat.

## Rückläufe

0.
