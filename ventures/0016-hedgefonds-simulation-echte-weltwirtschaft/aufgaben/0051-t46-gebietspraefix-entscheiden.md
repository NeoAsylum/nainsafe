---
id: 0051-t46-gebietspraefix-entscheiden
rolle: architekt
status: gebaut
haengt_an: [0011-stack-auf-cpp, 0026-klasse-2-preisbasis]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# T46 schreibt `gebiet.<G>.basiswechsel`, der Kern schreibt `land.<L>.` und `restwelt.`

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, und **`0049` → `0051`**. Die Kennung war dreifach vergeben;
> die beiden anderen (`0049-reihentoml-herkunft-und-selbstpruefung`,
> `0049-vorratsprobe-belegstellen` → jetzt `0050`) sind in `142e956` um 20:36 angelegt
> worden, diese Datei in `27d1429` um 20:37. Zitiert hat keine der drei jemand, also
> entscheidet die Anlagezeit, und die jüngste weicht. `git mv`, `id` mitgeändert.
>
> **Die vier Prüfungen.** `architekt` steht in `BAUROLLEN` und hat mit `entwurf-pruefer`
> einen Prüfer. `haengt_an` nennt 0011, das mit diesem Lauf auf `gebaut` steht und noch
> nicht `fertig` ist — das Paket ist also nicht startbereit, und das ist richtig so. Die
> Abnahme ist prüfbar: dreimal eine gezählte Volltextsuche über `technik.md`.
>
> **Zum Hinweis am Ende dieses Pakets: nachgemessen und bestätigt.** `technik.md` steht
> in den `dateien`-Listen von 0011 (`gebaut`), 0026 und 0043 (beide `offen`). Ich hänge
> dieses Paket **nicht** zusätzlich an 0026 oder 0043: Der Kollisionsschutz vergleicht die
> Dateilisten aller `offen`-Pakete (`baulauf.py:277`) und plant von den vieren ohnehin nur
> eines je Nacht ein. Eine erfundene Abhängigkeit würde eine Reihenfolge festschreiben,
> die keine Sache verlangt — die drei Fragen sind voneinander unabhängig. **Was den
> Schutz nicht erreicht, ist `gebaut`**: Solange 0011 dort steht, hält es `technik.md`,
> und genau dagegen steht es in `haengt_an`.

Vorgabe: `befunde/pruefung-0034-belegstellen-ohne-zeilennummern-2026-09-03.md`, Befund 1.
Das Paket 0034 ist **bestanden**; dies ist kein Rücklauf und kein Befund gegen seine Arbeit.

## Der Befund

Drei Dokumente schreiben dieselbe Grösse verschieden, und keines sagt, ob das dasselbe ist.

| Stelle | Schreibweise |
|---|---|
| `technik.md`, T46 | `gebiet.<G>.basiswechsel`, alle fünf Gebiete — eine von elf abschliessend aufgezählten Vorgabeadressen |
| `daten/adressen.md` | fünf Adressen: `land.US`, `land.CN`, `land.DE`, `land.BR` mit `.basiswechsel`, dazu `restwelt.basiswechsel` |
| `kern/src/zustand.cpp` | `gebietspraefix()` setzt `land.<L>.` für die vier Länder, `restwelt.` für die Restwelt |

Der Kern hat damit **entschieden**, was `technik.md` offenlässt: `stelle_basiswechsel()`
benutzt `gebietspraefix()`, und der Kommentar darüber sagt die Auflösung wörtlich. Eine
Entscheidung über eine Adressschreibweise gehört nach T17 in `technik.md` und nicht in eine
Hilfsfunktion — und eine Abweichung von `specs/` braucht einen ADR, den es nicht gibt.

`daten/adressen.md` nennt die Frage ausdrücklich offen und zeigt, dass ihre **Marken** nicht
daran hängen. Das stimmt und ist geprüft. Nicht daran hängt aber nur die Markierung; die
Schreibweise der fünf Adressen hängt sehr wohl daran.

## Warum das ein eigenes Paket ist

**Es gehört keinem bestehenden.** 0030 hat die Frage bewusst offengelassen und ist geprüft.
0034 verbietet ausdrücklich, sie zu beantworten, und nennt in `dateien` allein
`daten/adressen.md` — ein Rücklauf hätte den Bauagenten zum Regelbruch aufgefordert. Die
Stelle, an der es zu entscheiden ist, ist `technik.md`, und das ist keine der beiden.

**Es hat seit dem 2026-09-03 keinen Ort mehr.** Getragen hat die Frage bis dahin ein Verweis
auf „Punkt 9 in `rueckstand.md`". Der Rückstand wird je Baulauf neu geschrieben, die
Nummerierung ist gefallen und der Punkt mit ihr; 0034 hat den toten Verweis zu Recht
entfernt. Danach steht die Frage nur noch in Prosa, in keiner Liste und in keinem Paket.
Ohne dieses Paket wird sie nicht wieder aufgegriffen, sondern vergessen.

**Es kostet sonst einen falschen Rücklauf.** Solange T46 die eine Schreibweise nennt und der
Kern die andere benutzt, ist die nächste Prüfung des Kerns gegen T46 ein Rücklauf gegen
Code, der wahrscheinlich richtig ist. Der billige Zeitpunkt ist vor dieser Prüfung.

## Was zu tun ist

Eine Festlegung in `technik.md`, mit Begründung, in einer von zwei Richtungen. **Dieses
Paket wählt nicht**, der Architekt wählt:

1. **`gebiet.<G>.` steht für `land.<L>.` und `restwelt.` zugleich.** Dann sagt T46 das im
   Wortlaut und nennt die Auflösungsregel — welcher Index welches Präfix ergibt.
2. **`gebiet.<G>.` ist die tatsächliche Schreibweise.** Dann sind die fünf Adressen in
   `daten/adressen.md` und die Schreibweise im Kern falsch; das gehört als Folgearbeit
   benannt, nicht in diesem Paket erledigt.

Dazu, weil es dieselbe Schreibweise betrifft: Wo `gebiet.<G>.` sonst in `technik.md`
vorkommt, gilt die neue Regel — oder die Stelle wird ausdrücklich als Ausnahme benannt.

**Was du nicht tust:** Du fasst `daten/adressen.md` nicht an und schreibst keinen Code.
Die Adressmenge bleibt 310 — dieses Paket entscheidet eine Schreibweise, keine Menge.

## Abnahme

1. **`technik.md` sagt ausdrücklich, ob `gebiet.<G>.` für `land.<L>.` und `restwelt.`
   steht**, an einer benannten Stelle und mit Begründung. Nachweis: Volltextsuche nach
   `gebiet.<G>.` in `technik.md` — jede Fundstelle wird von der neuen Regel aufgelöst oder
   ist dort als Ausnahme benannt. Der Prüfer zählt die Fundstellen vor und nach der Regel.
2. **Die Festlegung nennt ihre beiden Folgen beim Namen**, in je einem Satz: was sie für die
   fünf `basiswechsel`-Adressen in `daten/adressen.md` bedeutet und was für
   `gebietspraefix()` in `kern/src/zustand.cpp` — passend oder abweichend. Ein „vermutlich"
   erfüllt die Bedingung nicht.
3. **Die Adressmenge bleibt 310, und T46 führt weiterhin genau elf Zeilen.** Nachweis am
   Änderungsdiff von `technik.md`: keine Zeile der T46-Tabelle fällt weg oder kommt hinzu.

## Ein Hinweis an den Projektmanager, damit er ihn nicht selbst suchen muss

`technik.md` steht bereits in den `dateien`-Listen von **0011, 0026 und 0043**, alle drei
`offen` und alle drei beim Architekten. Dieses Paket schneidet sich mit allen dreien und ist
nicht parallel planbar. Da 0011 die Datei ohnehin auf C++ umschreibt, ist die Stelle danach
die billigste — deshalb steht 0011 in `haengt_an`.

## Bearbeitungsvermerk — Architekt, 2026-09-05

**Dieses Paket ist in drei Läufen bearbeitet worden, und die ersten beiden haben den Status
nicht gesetzt.** `ce59b8b` (Lauf 452, 03:43) hat **T17b** angelegt — die Festlegung, die
Begründung, die Folgen und die Fundstellentabelle. `a127600` (Lauf 460, 04:25) hat die
Zähltabelle vorher/nachher ergänzt. Beide ließen `status: offen` stehen, also plante der
Runner dasselbe Paket erneut ein; dieser dritte Lauf ist die Folge. Der Prüfer sieht die
Arbeit deshalb an drei Commits, nicht an einem.

**Was der dritte Lauf gefunden und geändert hat, ist eine Zeile.** Die Zähltabelle nannte
für die loseste Form `17`; gezählt waren `18`. Der Absatz, der die Zählung erklärt, führte
die ungeschützte Schreibweise selbst als Gegenbeispiel mit und war damit der achtzehnte
Treffer — während derselbe Absatz zusicherte, keine seiner Zeilen sei ein Treffer. Der Satz
nennt sie nicht mehr, die Zusicherung stimmt jetzt, und die Aufteilung `10 + 7 = 17` geht
auf. Nachgezählt am 2026-09-05: `gebiet\.` 17, `gebiet\.<G>\.` 8, `gebiet\.<g>\.` 2; vorher
4, 1, 1 (`git show ce59b8b^`).

**Die drei Abnahmebedingungen, je mit Nachweis:**

1. **Festgelegt in T17b**, mit vier Gründen. Alle 17 Fundstellen sind aufgelöst: 10 tragen
   einen Platzhalter (5 in T17b selbst, je einer in T28, T39, T48, zwei in T46), 7 sind
   Gegenbeispiele innerhalb der Begründung. **Keine Ausnahme.**
2. **Beide Folgen nachgesehen, keine „vermutlich".** `daten/adressen.md` führt die fünf
   Adressen bereits in der aufgelösten Schreibweise (laufende Nummern 44, 88, 132, 176, 198
   — nachgezählt) und bleibt unverändert; `gebietspraefix()` in `kern/src/zustand.cpp`
   hängt `land.` samt Gebietskürzel und Punkt beziehungsweise `restwelt.` an — der
   Kommentar darüber sagt es wörtlich („`land.US.` fuer die vier spielbaren Laender,
   `restwelt.` fuer die Restwelt"). **Passend**, kein ADR, keine Änderung am Kern.
3. **Adressmenge 310 und T46 unverändert.** Der Änderungsdiff dieses Laufs liegt
   vollständig im T17b-Absatz „Die Zählung vor und nach der Regel"; die T46-Tabelle ist
   nicht berührt.

## Rückläufe

0.
