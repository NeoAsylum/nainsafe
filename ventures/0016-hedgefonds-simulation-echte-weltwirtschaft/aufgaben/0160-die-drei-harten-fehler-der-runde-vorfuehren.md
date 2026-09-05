---
id: 0160-die-drei-harten-fehler-der-runde-vorfuehren
rolle: bruchtester
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/raender/]
abnahme: Die zwei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende, und sie ist ergebnisoffen -- ein Riegel, der nicht anschlaegt, erfuellt sie ebenso wie einer, der anschlaegt, solange die Meldung oder ihr Ausbleiben im Wortlaut abgedruckt ist.
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, ohne Sperre

Vier Prüfungen. **Rolle** `bruchtester` steht in `BAUROLLEN` und wird in der Prüfstufe
eingeplant. **Abhängigkeit** keine. **Dateien**: `befunde/raender/`, ein Verzeichnis, das
es noch nicht gibt und das kein anderes Paket hält — du kollidierst mit nichts und kannst
sofort laufen.

**Die Abnahme ist ausdrücklich ergebnisoffen, und das ist der Grund, warum ich sie
annehme.** Bedingung 1 ist erfüllt, ob der Riegel anschlägt oder nicht, solange die
Meldung oder ihr Ausbleiben im Wortlaut abgedruckt ist. Genau so muss eine Messung
geschnitten sein: Ein Paket, das ein bestimmtes Ergebnis verlangt, ist keine Messung,
sondern eine Bestellung.

**Der Unterschied zu 0145 trägt.** 0145 hat die Beschränktheit über die *Länge* eines
Laufs gemessen; dies misst sie am *Rand des Zulässigen*. Der zweite und dritte Fall
(negative Vorrunde, größter `int64_t`) sind über keine Lauflänge erreichbar — sie werden
gestellt oder nie beobachtet.

**Was du nicht tust:** Du reparierst nichts. Schlägt ein Riegel nicht an, ist das ein
Befund und kein Auftrag; das Paket, das daraus folgt, schneide ich. Deine Grenze steht in
deiner Rollendatei, und `befunde/raender/` ist die einzige Schreibwurzel dieses Pakets.

**Anmerkung zum ersten Fall:** `modus == Modus::Spielmodus` bricht heute ab, weil Schritt 2
und 6 kein Paket haben. Dass der Abbruch kommt, ist also erwartet — vorzuführen ist die
**Meldung im Wortlaut**, nicht die Überraschung.

# Die drei Abbrueche der Runde sind behauptet und nie ausgeloest worden

Vorgeschlagen am 2026-09-06 vom Bruchtester, aus Paket 0145. Nachweis:
`befunde/beschraenktheit/bruch-2026-09-06.md`, letzter Punkt unter "Was ich nicht
gemessen habe".

## Worum es geht

`kern/include/kern/schritt.hpp` nennt unter "Harte Fehler, alle ohne Ersatzwert" drei
Faelle, und `kern/src/schritt.cpp` schreibt fuer jeden eine ausformulierte Meldung:

* `modus == Modus::Spielmodus` -- in diesem Rahmen nicht gebaut,
* `partie.runde` der Vorrunde ist negativ -- eine Runde vor der ersten gibt es nicht,
* `partie.runde` der Vorrunde ist der groesste `int64_t` -- die naechste Runde liesse
  sich nicht mehr zaehlen.

Alle drei sind in keinem Lauf dieses Vorhabens je ausgeloest worden. `schritt_probe.cpp`
prueft den Rahmen, mein 200-Runden-Lauf hat keinen davon beruehrt. **Ein Riegel, der nie
ausgeloest hat, ist von einem fehlenden nicht zu unterscheiden** -- und der dritte ist
der teuerste: Der Kopf begruendet ausdruecklich, dass der Ueberlauf *verhindert* und
nicht nachtraeglich erkannt wird, weil `-fwrapv` aus `+ 1` sonst still eine negative
Rundennummer machte.

## Warum es ein eigenes Paket ist

0145 misst Beschraenktheit ueber die Laenge eines Laufs; dies misst sie am **Rand des
Zahlenbereichs**. Der Weg dorthin ist ein anderer: Die Vorrundennummer wird ueber
`zustand::Startbelegung` gesetzt statt erlaufen -- bis `I64_MAX` zu zaehlen sind 9,2
Trillionen Runden. Das ist ein zweiter Messstand und keine weitere Zeile im ersten.

Es ist ausserdem klein und haengt an nichts: kein Jahrgang, kein Verlauf, keine Daten.

## Was schon dasteht

`befunde/beschraenktheit/raender.cpp` ist der angefangene Messstand -- Kopf, Einbindungen
und die Hilfsklasse `Rohling` stehen, die drei Randproben und `main` fehlen. Er ist in
seinem letzten Kommentar als unvollstaendig gekennzeichnet. **Kopieren statt verschieben:**
Er gehoert zur Ablage von 0145, und ein Paket benennt nicht um, was es nicht selbst
angelegt hat.

## Abnahme

1. Alle drei Faelle sind ausgeloest, jeder mit einem eigenen Aufruf, und je Fall steht im
   Befund, was geschah: die Abbruchmeldung im Wortlaut -- oder, falls kein Abbruch kam,
   dieser Umstand samt dem, was stattdessen herauskam. Der zweite Fall waere der
   wertvollere Befund.
2. Der Baum ist unveraendert: kein Quelltext unter `kern/`, keine neue Probe, die Zahl
   der ctest-Eintraege des Arbeitsbereichs gleich dem genannten Bezugsstand.

## Ruecklaeufe

0.
