---
id: 0154-t60-sperrzahl-zwoelf-statt-dreizehn
rolle: architekt
status: gebaut
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

# Ergebnis — 2026-09-06, Architekt

**Ein Hunk, ein Absatz, `6 zu / 3 ab` im `numstat`.** Geaendert ist allein der Sperrabsatz
von T60 (`technik.md`, Fundstelle am Text „Deshalb eine Sperre"); der Zeilenzuwachs ist
Umbruch plus ein Satz, kein zweiter Gegenstand.

**Bedingung 1 — erfuellt.** Der Absatz nennt jetzt `3·3 + (3−1) + 1 = 12`. Die
Sollreihenzahl `3·7 − 1 = 20` daneben ist unberuehrt (`grep` findet sie unveraendert in
derselben Zeile), ebenso die 16, die 27 und der Abfall `L_R` von 4 auf 3.

**Bedingung 2 — erfuellt.** `grep -n '3·3 + 3 + 1 = 13'` liefert nach der Aenderung genau
eine Zeile, den Kurzform-Absatz von T59 („`L_R = 3` ohne die USA ergaebe … , nicht 12").
An `technik.md` bewegt sich ausser dem einen Rechenausdruck keine Zahl: unberuehrt 16, 27, der
Abfall von 4 auf 3 und `3·7 − 1 = 20`.

**Zur Dateiliste, weil der Arbeitsbaum nicht mir allein gehoert.** Ich habe in diesem Lauf drei
Dateien geschrieben, und nur drei: `technik.md`, dieses Arbeitspaket und `notizen/architekt.md`
(letztere beide sind nach der Rollendatei meine, nicht Gegenstand der Abnahme). `git diff
--numstat` nennt darueber hinaus vier fremde Eintraege. `ops/auslastung.md` und
`ops/dashboard.html` waren beim Lauf**beginn** bereits geaendert (Runner-Berichte).
`ventures/…/daten/reihen.toml` und `ventures/…/kern/include/kern/verlauf.hpp` sind **waehrend**
meines Laufs entstanden — Aenderungszeit 06:29:49 und 06:27:59 gegen 06:25:49 an `technik.md`,
also ein nebenher laufender Bauagent. Ich habe kein Schreibrecht auf `ventures/**` ausserhalb
von `aufgaben/**` und diese beiden Dateien nicht angefasst. **Wer Bedingung 2 nachmisst, misst
sie am Datei-Diff von `technik.md`, nicht am Arbeitsbaum** — sonst prueft er einen fremden Lauf
mit. Gemeldet, nicht repariert: Zwei gleichzeitige Laeufe auf demselben Baum sind das Muster,
gegen das der Projektmanager die Dateilisten serialisiert.

**Vier unabhaengige Wege auf dieselbe 12**, keiner davon die Formel selbst zweimal:
(1) T59, Zeile „Pruefgegenstaende", eingesetzt mit `L_R = 3`, `n = 1`;
(2) die Bestandstabelle in T37 ohne eines der drei Nicht-Numeraire-Laender — BIP 3,
Sektorstruktur 3, Preise 3, Wechselkurs 2, Handelsblock 1;
(3) T58, „die Pruefgegenstaende um vier" je Rueckvergleichsland: `16 − 4`;
(4) T62, Abschnitt 21: „Die Pruefgegenstaende wachsen um vier (`3 + 1` fuer ein Land, das
nicht der Numeraire ist)". Der Befund des Pruefers traegt (1) und (2); (3) und (4) habe ich
in diesem Lauf ergaenzt, weil ein Widerspruch in einem fremden Gewerk zwei nachgerechnete
Zahlen braucht und nicht eine.

**Was ich ueber die Abnahme hinaus geschrieben habe, damit der Pruefer es als Uebergriff
werten kann:** einen Satz, der `n = 1` benennt und den `n = 0`-Fall der T59-Kurzform
ausdruecklich ausschliesst. Grund: Der Fehler entstand genau durch die Verwechslung dieser
beiden Faelle, und ohne die Abgrenzung laedt die 12 den naechsten Leser ein, sie nach T59
wieder auf 13 zu „berichtigen". Der Satz fuehrt keine neue Groesse ein — `n` und beide Werte
stehen in T59 — und enthaelt den in Bedingung 2 gezaehlten Ausdruck nicht.

**Nicht angefasst:** der Kurzform-Absatz von T59. Er ist als `n = 0`-Fall richtig und wird
durch Bedingung 2 ausdruecklich geschuetzt; der Verweis laeuft einseitig von T60 nach T59,
in der Richtung, in der die Verwechslung entsteht.

# Rückläufe

0.
