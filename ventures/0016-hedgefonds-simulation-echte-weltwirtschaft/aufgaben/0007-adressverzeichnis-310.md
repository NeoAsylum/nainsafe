---
id: 0007-adressverzeichnis-310
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Das Verzeichnis führt genau 310 Zeilen, jede mit Adresse nach T17, Gruppe nach T15, Herkunft nach T45/T46 und genau einer Skalenklasse nach T5/T49; die drei Gruppierungen summieren auf 198+56+52+4, auf 136+150+11+2+11 und auf die zwölf Klassenzeilen aus T49, jede Summe 310.
---

# Die 310 Adressen, einzeln hingeschrieben

Drei Dokumente zählen dieselbe Menge dreimal ab — T15 nach Gruppen, T45/T46 nach
Herkunft, T49 nach Skalenklasse — und alle drei Summen gehen auf 310 auf. **Aufgezählt
ist die Menge nirgends.** Sie steht nur als Rechnung da.

Das ist genau die Lücke, an der Befund 1 der Runde 6 hing: „T45s Abzählschritt findet
sie nicht, weil sie keine Zustandsadresse ist." Umgekehrt gilt dasselbe — eine Adresse,
die in einer der drei Zerlegungen fehlt und in einer anderen doppelt steht, hält jede
Summe ein und ist trotzdem falsch. Dieses Verzeichnis ist die Stelle, an der das
auffällt, **bevor** ein Kernbauer 310 Felder tippt.

Vorher lesen: `technik.md` T15, T17, T45, T46, T49; `rueckstand.md`, Abschnitt
*Es gibt keinen Übersetzer*.

## Was du baust

Eine Textdatei mit **einer Tabelle, 310 Zeilen**, je Zeile:

| Spalte | Inhalt | Vorgabe |
|---|---|---|
| Adresse | `land.DE.sektor.2.preis`, `handel.DE.CN.1`, `markt.rendite` … | T17 |
| Gruppe | die Zeile aus der Tabelle in T15, aus der sie stammt | T15 |
| Herkunft | `Datenanker` \| `Entwurf` \| `Parameter(<schluessel>)` \| `Manifest` \| `Vorgabe` | T45, T46 |
| Klasse | 1 bis 12 | T5, T49 |
| Startwert | nur wo T45 `Entwurf` oder T46 `Vorgabe` sagt; sonst leer | Entwurfstabelle `spiel.md`, T46 |

Die Adressform ist **vorgegeben und nicht deine Wahl** (T17): Wer eine umbenennt, macht
den Regressionsbestand ungültig und braucht einen ADR. Wo die Dokumente eine Adresse nur
umschreiben statt sie zu schreiben, bilde sie nach dem Muster der Beispiele in T17 und
**markier die Zeile**, damit der Prüfer sie findet.

## Abnahme

Vier Zählungen, alle nachrechenbar, keine davon braucht einen Übersetzer:

1. **310 Zeilen**, keine Adresse zweimal.
2. **Nach Gruppe** summiert es auf `4 × 44 + 22 = 198` Gebiete, `40 + 2 + 12 + 2 = 56`
   Welt, `5 + 3 + 20 + 24 = 52` Fonds, `4` Partie (T15).
3. **Nach Herkunft** auf `136 + 150 + 11 + 2 + 11` (T45). Die elf Adressen mit Herkunft
   `Vorgabe` sind abschliessend in T46 aufgezählt und müssen Zeile für Zeile
   wiederzufinden sein; ebenso die elf mit `Parameter`.
4. **Nach Klasse** auf die zwölf Zeilen der Zerlegung in T49
   (`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2 = 310`), und je spielbarem
   Land auf `6 + 5 + 4 + 1 + 7 + 1 + 2 + 8 + 1 + 9 = 44`.

**Jede Zeile trägt genau eine Klasse und genau eine Herkunft.** T49: eine Adresse ohne
Klasse und eine mit zwei Klassen brechen den Jahrgangsbau ab. Hier ist dieselbe Regel
eine Spalte, die leer nicht sein darf.

## Zwei Fälle, die dir begegnen werden, und wie sie geregelt sind

- **`land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` tragen denselben
  Wert**, ebenso beim Haushaltssaldo. Beide bekommen eine Zeile — T15 führt beide, weil
  `spiel.md` beide aufzählt. Die Schreibregel steht in T49 und ist nicht deine
  Entscheidung: geschrieben wird der Instrumentenstand in Schritt 3, die Aggregatgröße
  übernimmt ihn in Schritt 4.
- **Eine Adresse, die zwei Herkunftseinträge zu haben scheint** (etwa `markt.wert`).
  T45s Vorrangregel löst das: Der Eintrag ist die Stelle, die den Wert *bestimmt*; ein
  Verweis ist kein zweiter Eintrag.

## Wenn eine Summe nicht aufgeht

Dann ist das **der Befund**, und er gehört in die Datei, nicht wegkorrigiert. Schreib
hin, welche Adresse fehlt oder doppelt steht und welche der drei Zerlegungen dadurch
reisst. Eine Zahl, die nur einmal entsteht, ist unbelegt, auch wenn sie stimmt — das
steht so in T49, und dieses Paket ist die vierte unabhängige Zählung.

## Rückläufe

0.
