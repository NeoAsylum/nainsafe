---
id: 0038-meldung-mit-adresse-gemeinsam
rolle: kernbauer
status: offen
haengt_an: [0016-schreiber-ursachenkette, 0033-schritt-rundengeruest-weltlauf]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/meldung.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schreiber.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/meldung_probe.cpp]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# `kern::meldung` — der Meldungsbau aus `schreiber.cpp` als eigener Kasten

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`.** Die Rolle `kernbauer` gibt es und `baulauf.py:59` plant sie
> ein; die Abnahme nennt vier Bedingungen, drei davon an Nachweisen, die der
> Übersetzungsbericht führt.
>
> **Die Dateiprüfung ist hier die eigentliche Arbeit, und der Vorschlag hat sie selbst
> richtig gemacht.** `kern/src/schritt.cpp` gehört Paket 0033, das auf `gebaut` steht —
> und `startbereit()` sieht `gebaut` nicht (`baulauf.py:273`, es vergleicht die
> Dateilisten nur unter `offen`). Ohne den Eintrag `0033` in `haengt_an` wäre dieses
> Paket startbereit, während 0033 nach einem Rücklauf dieselbe Datei zurückbekommt.
> `kern/src/schreiber.cpp` gehört 0016 (`fertig`), die beiden übrigen Dateien sind neu.
>
> **Nicht in `dateien` und trotzdem angefasst — die Falle, in die ich bei 0027 gelaufen
> bin:** Bedingung 2 verlangt, dass `schreiber_probe` und `schritt_probe` grün bleiben.
> Das ist ein Lauf, kein Schreibzugriff — die beiden Probendateien gehören 0027
> (`gebaut`) bzw. 0033. **Wer sie ändern muss, hat einen Befund und kein Recht dazu:**
> Der Umzug soll das Verhalten nicht ändern, und genau das ist der Nachweis. Ändert eine
> der beiden Proben sich, ist es ein Rücklauf.
>
> **Es läuft heute noch nicht** — 0033 wartet auf sein Urteil.

## Was fehlt

`festkomma::abbruch` nimmt **einen** `const char*`. Wer in einer Fehlermeldung eine
Adresse, eine Rundennummer oder einen Wert nennen will, muss den Text selbst
zusammensetzen — und weil der Kern keine eigene Speicherverwaltung hat (T2b), heisst das:
Puffer fester Groesse auf dem Stapel, Laengenpruefung bei jedem Zeichen, Zahlenumwandlung
von Hand.

Genau das steht seit Paket 0016 in `kern/src/schreiber.cpp` als Klasse `Meldung` in einem
anonymen Namensraum — rund 65 Zeilen mit drei nicht trivialen Stellen: der Betrag des
kleinsten `int64_t` (nur ueber `u64` zu bilden), das Abschneiden statt Ueberlaufen am
Pufferende, und die Adressform „Textform plus laufende Nummer aus `daten/adressen.md`".

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Weil es drei Dateien beruehrt, die drei verschiedenen Paketen gehoeren.** Ein neuer
Kopf `kern/include/kern/meldung.hpp`, der Umzug der Klasse aus `schreiber.cpp` (Paket
0016, `fertig`) und der Anschluss in `schritt.cpp` (Paket 0033) schneiden sich in ihren
`dateien`-Listen mit jedem Paket, das an einer dieser Quellen arbeitet. Genau diese
Pruefung serialisiert der Projektmanager, und deshalb kann kein Bauagent den Umzug
nebenbei machen.

**Und weil der Anlass belegt ist, nicht vermutet.** Paket 0033 hat vier Abbrueche gebaut,
die eine Adresse im Wortlaut tragen sollten, und traegt sie **nicht**: Sie nennen
stattdessen die Datei, in der die Zuordnungstafel steht. Der Grund war, dass die Wahl
zwischen 65 abgeschriebenen Zeilen in einem Rahmenpaket und einer schlechteren Meldung
bestand — und ein Bauagent, der eine Fehlermeldungsklasse abschreibt, hat sie beim
naechsten Mal in zwei Fassungen, die auseinanderlaufen.

Die fuenf Folgepakete der Runde (die sechs Schritte aus `spiel.md`) brauchen dieselbe
Klasse, jedes einzeln. Der Umzug kostet einmal einen Lauf; das Abschreiben kostet fuenfmal
einen und erzeugt fuenf Fassungen.

## Was zu bauen ist

1. `kern/include/kern/meldung.hpp` — die Klasse aus `schreiber.cpp`, unveraendert in ihrem
   Verhalten, mit den Erklaerungen aus ihrem heutigen Kommentar. Sie hat keine
   Abhaengigkeit ausser `kern/zustand.hpp` (fuer `index_zu_adresse`) und der
   Standardbibliothek (T2).
2. `kern/src/schreiber.cpp` — die eigene Fassung entfaellt, der Kopf wird eingebunden.
   Kein Verhalten aendert sich; `schreiber_probe` schreibt die Abbruchmeldungen ohnehin
   im Wortlaut ins Protokoll und ist damit der Rueckvergleich.
3. `kern/src/schritt.cpp` — die vier Abbrueche der Zuordnungspruefung und die beiden der
   Rundennummer nennen die Adresse bzw. die Zahl im Wortlaut.

## Abnahme

1. **Der Kopf traegt die Klasse, und sie ist die einzige Fassung.** Ein Mustervergleich
   ueber `kern/src/` findet keinen zweiten Puffer, der Zeichen fuer Zeichen anhaengt.
2. **`schreiber_probe` und `schritt_probe` bleiben gruen**, und die Abbruchmeldungen im
   Protokoll von `schreiber_probe` sind Zeichen fuer Zeichen dieselben wie vorher. Das
   ist der Nachweis, dass der Umzug nichts am Verhalten geaendert hat.
3. **`kern/src/schritt.cpp` nennt in jedem seiner Abbrueche die Adresse in ihrer Textform
   nach T17 und ihre laufende Nummer** — die vier Zuordnungsabbrueche zusaetzlich die
   Zahl, die nicht aufging.
4. **`meldung_probe` steht namentlich als `Passed` im Uebersetzungsbericht des Tages** und
   prueft die drei nicht trivialen Stellen: `I64_MIN`, das Abschneiden am Pufferende, und
   eine Adresse ausserhalb der 310.

## Rueckläufe

0.
