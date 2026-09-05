---
id: 0154-t60-sperrzahl-zwoelf-statt-dreizehn
rolle: architekt
status: offen
haengt_an: [0117-geschaetzter-politikpfad-und-zwei-laenderklassen, 0141-pruefliste-fuenftes-land]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die zwei Bedingungen unter "Abnahme".
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, zweites Glied der `technik.md`-Reihe

Vier Prüfungen. **Rolle** `architekt` steht in `BAUROLLEN`, Prüfer ist der
`entwurf-pruefer` — beides vorhanden. **Abnahme** ist prüfbar: zwei benannte Bedingungen
über eine Zahl, die im Text steht und nachgerechnet werden kann; kein Vergleich gegen
einen fremden Korpus. **Abhängigkeit** 0117 ist seit heute `fertig`. **Dateien**: nur
`technik.md`.

**Der zweite Eintrag in `haengt_an` ist eine Reihenfolgesperre, keine fachliche
Abhängigkeit.** Du brauchst von 0141 nichts. `technik.md` ist eine einzige Datei, und
durch den Statusnachzug von heute wurden mehrere Pakete gleichzeitig für sie bereit; die
Reihe lautet jetzt

> 0141 → **0154** → 0158 → 0148 → 0149 → 0064 → 0068 → 0074 → 0084 → 0092.

**Warum du vor 0148 stehst** — das ist die Vorrangentscheidung dieses Laufs, und sie
korrigiert eine von gestern: 0148 ist der Kopf einer sechsgliedrigen Kette, die in dieser
Woche sicher nicht durchläuft. Du bist eine geschlossene Korrektur in einem Lauf, an einer
Zahl, die der Betreiber liest, wenn er über Chinas Leitzinsreihe entscheidet. Zwei fertige
Ergebnisse schlagen zwei weitere Glieder einer Kette, die stumm bleibt.

**Dein Vorher-Stand ist der dann geltende `HEAD`**, also die Fassung nach 0141. Die
Zeilennummern im Rumpf (3729, 3606) stammen vom 2026-09-06 — such am Text, nicht an der
Zeilennummer.

# Der Sperrabsatz von T60 beziffert den China/Deutschland-Fall mit der USA-Formel

**Vorgeschlagen vom entwurf-pruefer am 2026-09-06, Befund 1 der Pruefung zu `0117`**
(`befunde/pruefung-0117-geschaetzter-politikpfad-und-zwei-laenderklassen-2026-09-06.md`).

## Der Fehler, nachgemessen

`technik.md:3729` (Sperrabsatz von T60): „die Prüfgegenstände von 16 auf
`3·3 + 3 + 1 = 13`". Der Fall des Absatzes ist der Abstieg **Chinas oder
Deutschlands** auf Stufe 4 — die USA bleiben Rueckvergleichsland, also `n = 1`
nach T59. Die eigene Formel `3·L_R + (L_R − n) + 1` ergibt dann
`3·3 + (3−1) + 1 = 12`. Der geschriebene Ausdruck ist wortgleich der
`n = 0`-Fall, den T59 (Z. 3606) ausdruecklich fuer „`L_R = 3` **ohne die USA**"
vorrechnet; die Sollreihenzahl im selben Satz (`3·7 − 1 = 20`) rechnet dagegen
richtig mit `n = 1` — der Satz widerspricht sich selbst. Gegenprobe am Bestand:
ohne China bleiben BIP 3, Sektorstruktur 3, Preise 3, Wechselkurs 2 (DEU, BRA),
Handelsblock 1, zusammen 12; ebenso T58 („die Prüfgegenstände um vier" je
Rueckvergleichsland): 16 − 4 = 12.

## Warum ein eigenes Paket

`technik.md` ist die umkaempfteste Datei des Vorhabens; nur der Projektmanager
sieht die Dateiansprueche aller Pakete. Und der Absatz ist genau der, den der
Betreiber liest, wenn Chinas Leitzinsreihe endgueltig scheitert — die Zahl
beziffert dort den Einsatz seiner Entscheidung. Eine Zahl, die im
entscheidungstragenden Absatz um eins daneben liegt, laeuft in dieser Fabrik als
eigenes Berichtigungspaket (vgl. 0082, 0128). Keine Abnahmebedingung von 0117
verlangt diese Einsetzung, deshalb war es dort kein Ruecklauf.

## Abnahme

1. Der Sperrabsatz von T60 nennt fuer den Fall „China oder Deutschland faellt auf
   Stufe 4" die Zahl `3·3 + (3−1) + 1 = 12`, im Einklang mit `n = 1`; die
   Sollreihenzahl `3·7 − 1 = 20` daneben bleibt unveraendert.
2. Der Ausdruck `3·3 + 3 + 1 = 13` steht danach genau einmal in `technik.md`,
   naemlich im Kurzform-Absatz von T59 als `n = 0`-Fall („ohne die USA");
   `git diff` zeigt Aenderungen ausschliesslich in `technik.md`, und ausser dem
   einen Rechenausdruck bewegt sich keine Zahl.
