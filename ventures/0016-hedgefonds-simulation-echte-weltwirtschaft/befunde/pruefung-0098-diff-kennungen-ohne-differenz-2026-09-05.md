---
typ: pruefung
paket: 0098-diff-kennungen-ohne-differenz
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Probe gruen gefahren (308 von 310 Adressen mit gerechneter Differenz, 2 mit Strich), und der von der Abnahme verlangte Rotnachweis selbst erzeugt -- ein Mutant ohne die Ausnahme faellt mit drei fehlgeschlagenen Zusicherungen auf Ruecksprungwert 1.
befunde: 1
---

# 0098 -- die Kennungen tragen einen Strich statt einer Differenz

## Das Abnahmekriterium, in vier Teilen geprueft

### 1. Strich samt Grund auf beiden Kennungen

`kern/src/zustandsausgabe.cpp:372-383` fragt in `diff` die Skalenklasse und schreibt an
der Stelle der Differenz `STRICH_STATT_DIFFERENZ` statt einer Subtraktion. Alter und
neuer Wert stehen wie auf jeder anderen Adresse -- weggelassen wird nichts.

Gemessene Ausgabe (`./bau/zustandsausgabe_probe`, Ruecksprungwert 0):

```
partie.parameter_pruefsumme  alt 12345  neu 20000  Differenz -  (T5: auf einer Kennung nur Gleichheit)  [K12 Kennung, Bitmuster ohne Groessenbedeutung]
```

Dass **beide** Kennungen erfasst sind und nicht nur die gemessene, zeigt erst der
Mutant weiter unten: Er nennt `partie.jahrgang_id` und `partie.parameter_pruefsumme`
als die genau zwei Abweichungen.

### 2. Die zwoelf uebrigen Klassen behalten ihre Differenz

`differenz_hat_bedeutung` (`zustandsausgabe.hpp:476-479`) nimmt allein
`Skalenklasse::Kennung` aus. Dass es bei einer Ausnahme bleibt, zaehlt
`klassen_ohne_differenz()` beim Uebersetzen nach; drei `static_assert` (Zeile 493-498)
nageln Klasse 12 als ausgenommen und Klasse 11 als rechnend fest. Die Ausnahme haengt
an der Klasse, nicht an einer zweiten Adressliste.

Gemessen, in derselben Ausgabe wie oben:

```
fonds.marktanteil  alt 420  neu 500  Differenz 80  [K4 Anteile, Zehntausendstel]
Differenzspalte: 308 von 310 Adressen tragen die gerechnete Differenz, 2 den Strich.
```

Von Hand nachgerechnet: 500 − 420 = 80 ✓, und 20000 − 12345 = 7655 -- die Zahl, die auf
der Kennung gerade **nicht** erscheinen darf.

### 3. Ein einziges Zustandspaar weist beides nach

Der Block ab `zustandsausgabe_probe.cpp:1322` aendert genau zwei Adressen -- eine
Kennung (`ParameterPruefsumme`) und eine Nicht-Kennung (`Marktanteil`) -- und prueft
`"2 von 310 Adressen geaendert."`. Beide Haelften stehen damit in derselben Ausgabe:
Die Ausnahme greift, und sie greift nur dort. Danach fuehrt eine Schleife dieselbe Frage
fuer jede der 310 Adressen einzeln, mit der Erwartung aus der Skalenklasse statt aus
einer Adressliste, und prueft `kennungen == 2`.

### 4. Der Rotnachweis -- selbst erzeugt

Die Abnahme sagt: *"Ein Mutant, der die Ausnahme wieder herausnimmt, macht diese Probe
rot -- ohne diesen Rotnachweis ist die Probe nicht belegt."* Im Mutationskatalog
(`werkzeuge/mutation/katalog.md`, 19 Faelle) steht dafuer **kein** Fall; der Nachweis
war also zu fuehren.

Gefuehrt, ohne eine Datei des Vorhabens anzufassen: Die echte Quelldatei wurde ein
zweites Mal uebersetzt, wobei die Aufrufstelle in `diff` per Makro auf `true` verkuerzt
wurde -- das ist der Stand vor 0098. Der Kopf wird vorher regulaer eingelesen, sein
`#pragma once` verhindert, dass das Makro die Definition selbst trifft:

```
c++ <die Schalter aus flags.make> \
    -include kern/zustandsausgabe.hpp \
    -include <tmp>/mutation_def.h \      # #define differenz_hat_bedeutung(k) true
    -c src/zustandsausgabe.cpp -o <tmp>/mutant.o
```

Gebunden wurde gegen das **unveraenderte** Probenobjekt und die uebrigen sieben
Kernobjekte aus dem bestehenden Baubaum. Ergebnis -- Ruecksprungwert **1**:

```
FEHLGESCHLAGEN Zeile 1340: enthaelt(..., "partie.parameter_pruefsumme  alt 12345  neu 20000  Differenz -  (T5: ...)  [K12 ...]")
FEHLGESCHLAGEN Zeile 1355: !enthaelt(blatt.fertig(), "Differenz 7655")
Differenzspalte falsch: partie.jahrgang_id erwartet   Differenz -  (T5: auf einer Kennung nur Gleichheit)  [K
Differenzspalte falsch: partie.parameter_pruefsumme erwartet   Differenz -  (T5: auf einer Kennung nur Gleichheit)  [K
FEHLGESCHLAGEN Zeile 1399: abweichungen == 0
kern::zustandsausgabe -- 3 Probe(n) fehlgeschlagen.
```

Die Probe ist damit belegt **und** trennscharf: Der Mutant laesst die Zusicherung auf
`fonds.marktanteil  ...  Differenz 80` unberuehrt gruen -- die Probe misst die Ausnahme,
nicht bloss irgendeine Aenderung.

## Wonach ausserdem gesucht wurde

- **Determinismus.** `diff` laeuft ueber `platz = 0 … FELDER` in Indexreihenfolge, nicht
  ueber eine ungeordnete Menge. Kein Gleitkomma (`sperre.hpp` macht es ab Zeile 29 zum
  Uebersetzungsfehler), keine Adresse und keine Zeit im Ergebnis.
- **Der Zahlenrand.** Die Subtraktion der uebrigen Klassen steht auf `i128`
  (`zustandsausgabe.cpp:376`); der Abstand zweier `i64` ist keine `i64`. Ohne die
  Erweiterung waere der Umlauf unter `-fwrapv` definiert und die Zahl wohlgeformt
  falsch -- genau die Sorte Wert, vor der T5 warnt.
- **Verliert der Strich etwas?** Nein. Alter und neuer Wert stehen weiter in der Zeile;
  ein Leser sieht beide Bitmuster und ihre Ungleichheit. Der Grund steht in der Zeile
  statt in einem Dokument.
- **Arithmetik auf Kennungen anderswo.** `uebersicht` (`zustandsausgabe.cpp:204-206`)
  gibt Jahrgang und Parametersatz unveraendert aus, `detail` ebenso. Kein zweiter
  Verstoss gegen T5 in diesem Modul.
- **`specs/` unangetastet** -- weder `7c3a2b6` noch `c30acc5` fassen `specs/` an. ✓

## Der eine Befund -- ausserhalb des Pakets

**Der Code zu 0098 liegt nicht im Commit zu 0098.** `7c3a2b6`
(`kernbauer: 0098-…`) enthaelt genau eine Datei: `notizen/kernbauer.md`. Alle drei
Dateien der `dateien`-Liste liegen in `c30acc5`, das den Betreff
`testentwickler: 0111-korbbestand-anleihezweig-betrag-der-stufen` traegt -- dessen
`dateien`-Liste allein `kern/test/werte_probe.cpp` nennt. Im Probenkommentar dieses
Commits steht woertlich „Abschnitt 8b, Paket 0098".

Das ist **kein neuer Befund**, sondern ein zweiter Beleg fuer
`0121-commit-schnitt-folgt-nicht-dem-paket` (`status: blockiert`, vorgeschlagen am
2026-09-05 bei der Pruefung zu 0072). Deshalb schreibe ich dafuer kein eigenes Paket.
Bemerkenswert ist allein, dass die Reihenfolgesperre gegen 0097, die der
Projektmanager im Annahmevermerk ausdruecklich gegen diese Klasse von Kollision gesetzt
hat, hier von der **Commit**-Stufe unterlaufen wurde: Sie serialisiert die Laeufe, nicht
den Index.

Auf das Abnahmekriterium wirkt sich das nicht aus -- der Code ist da, ist versioniert
und ist geprueft. Es wirkt auf die Nachvollziehbarkeit: Wer die Aenderung zu 0098 ueber
`git log` sucht, findet sie nicht.

## Anmerkung zur Werkstatt

Der Mutantenbinaerling wurde als `kern/bau/kp0098_mutant_kennung` gebunden, weil das
Ausfuehren aus dem Temporaerverzeichnis in diesem Lauf nicht erlaubt war. Das Loeschen
war es ebenso wenig, er liegt also noch dort. `bau/` ist ueber `.gitignore` (Zeile 233,
`ventures/**/bau/`) ausgenommen -- er kann nicht in einen Commit geraten und ist beim
naechsten sauberen Bau fort.
