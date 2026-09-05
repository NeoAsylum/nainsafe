---
typ: pruefung
paket: 0097-zustandsausgabe-probe-zuordnungen-festnageln
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Teile einzeln -- die 13+13+5 Wortlaute gegen T5/T45 gehalten und die Messschleifen nachvollzogen, die 55 Spaltenzusicherungen abgezaehlt, und die siebzehn Mutationen aus dem 0010-Befund selbst gebaut und gefahren, alle rot, M0 zweimal gruen.
befunde: 0
---

# Pruefung 0097 -- Zuordnungen der Zustandsausgabe festgenagelt

## Wie gemessen wurde

Prüfbaum aus `git archive HEAD` in ein Verzeichnis ausserhalb des Arbeitsbaums
(`kern/` ist im Arbeitsbaum bei HEAD unverändert, `git status` leer). Gebaut mit den
Schaltern des Runners (`baulauf.py`: `RelWithDebInfo`, `-fwrapv -fno-fast-math`).
Jede Mutation als Textersetzung mit Trefferbremse (`count == 1`, sonst Abbruch) an der
Kopie, übersetzen, `zustandsausgabe_probe` fahren, zurücksetzen. Keine Datei des
Pakets im Arbeitsbaum angefasst. `ctest` am unveränderten Prüfbaum: 10 von 10 grün.

## Teil 1 -- die 13 Namen, 13 Einheiten, 5 Herkunftsnamen im Wortlaut

**Erfüllt.** `KLASSE_SOLL` (Probe, Zeilen 404-419) trägt alle dreizehn Namen und
Einheiten als zweite Abschrift, `HERKUNFT_SOLL` (Zeile 423-425) alle fünf
Herkunftsnamen. Ich habe die Abschrift gegen die T5-Tabelle (`technik.md` Zeile
278-292) und die Herkunftszeile (`technik.md` Zeile 19, T45) gehalten: wortgleich in
der deklarierten Umschrift (ohne erläuternde Klammern, Umlautumschrift, ohne `=` vor
dem Startjahr, „des Jahres 2015" → „2015"). Abschnitt 4b misst jede Klasse an einer
Adresse, die per `skalenklasse_von` gesucht wird -- nicht abgeschrieben -- und hält
die Nadel `[K<N> <name>, <einheit>]` gegen das erzeugte Ein-Adress-Blatt
(`detail(z, adresse)`); die schliessende Klammer in der Nadel verhindert
Präfixtreffer (K5-Einheit steckt als Präfix in der K7-Einheit). Klasse 13 wird, wie
verlangt, unmittelbar an `klassenname`/`klasseneinheit` geprüft (Zeilen 843-845),
mit Negativkontrolle gegen die Klasse-11-Werte (Zeilen 905-906).
`mit_adressen == SKALENKLASSEN_MIT_ADRESSEN` und `herkuenfte == HERKUNFTSARTEN`
sichern, dass keine Klasse und keine Herkunft still übersprungen wird.

## Teil 2 -- jede Spalte gegen einen einzigartigen Wert, plus die halb gerechnete Runde

**Erfüllt.** `belege_unterscheidbar` belegt so, dass die 55 gedruckten Zahlen
paarweise verschieden sind, und die Probe **zählt** das (alle Paare, `doppelt == 0`)
statt es zu behaupten. Die Spaltenzählung 55 ist per `static_assert` an die
Aufzählungen gebunden; daraus folgt `SEKTOREN_HANDELBAR == 2`, beide Weltpreise sind
einzeln geprüft. Abgezählt: 4 Partiefelder + 4 erste Fondszeile + 2 zweite
Fondszeile + die drei Überrenditen als Gesamtaufzählung (Reihenfolge in der Nadel) +
2 Markt + 2 Weltpreise + 5×(BIP, Wechselkurs) + 4×(Zins, Zoll, Haushalt,
Regulierung, Einfluss, Zustimmung, Aufsicht) = 55 Zahlen, jede mit
`zeile_endet_wert`, dessen Abschlussbedingung selbst eine Gegenprobe hat (Zeilen
1133-1141). Die zweite, ausdrücklich halb gerechnete Belegung steht in Abschnitt 6c:
`land.<L>.leitzins` (Aggregat) auf `u_zins_vorrunde` verstellt, Stand unverändert,
und die Zusicherung prüft **beide** Hälften -- der Instrumentenstand steht da, die
Aggregatzahl steht nicht da.

## Teil 3 -- die siebzehn Mutationen, einzeln gefahren

**Erfüllt, selbst gemessen statt abgeschrieben.** Jede der siebzehn Mutationen aus
`befunde/pruefung-0010-zustandsausgabe-drei-ebenen-2026-09-04.md` nach ihrer
Beschreibung selbst gebaut; die Trefferbremse schlug bei keiner an.

| Mutation | Ergebnis | rote Zusicherungen |
|---|---|---|
| M15 (Klassenname 7/8 getauscht) | ROT | 2 |
| M16 (Einheit 8/9 getauscht) | ROT | 2 |
| M18 (Einheit Klasse 2 → „Stueck bzw. Runden") | ROT | 1 |
| N10 (Einheit Klasse 13 verstellt) | ROT | 1 |
| M17 (Herkunftsname 0/1 getauscht) | ROT | 2 |
| M19 (Zoll liest Haushaltsstand) | ROT | 4 |
| M20 (Zins liest Aggregat statt Stand) | ROT | 8 |
| M21 (Regulierung als Strich) | ROT | 4 |
| N02 (BIP liest überall USA) | ROT | 4 |
| N03 (Zustimmung als Strich) | ROT | 4 |
| N04 (Aufsicht liest Einfluss) | ROT | 4 |
| N05 (eine Überrendite fällt weg) | ROT | 1 |
| N06 (Korbwert liest Marktrendite) | ROT | 1 |
| N07 (Kasse liest Hebelstand) | ROT | 1 |
| N08 (Jahrgang liest Mandatsstand) | ROT | 1 |
| N09 (Weltpreis-Sektornummer +1) | ROT | 2 |
| N11 (Kopfzeile der Detailebene anders) | ROT | 1 |

M0 (Kontrolle ohne Eingriff) war **vor der Reihe und nach der letzten Rücknahme
grün** (Rückgabe 0, null rote Zusicherungen). M20 reisst mit 8 Zusicherungen genau
die beiden Hälften der halb gerechneten Runde in allen vier Ländern -- die neue
Belegung trägt die Unterscheidung, für die sie gebaut wurde.

Drei eigene Mutanten über die Liste hinaus, alle ROT:

- **E01** -- Herkunftsnamen „Parameter"/„Manifest" getauscht (eine Paarung, die der
  0010-Befund nicht enthielt): 2 rote Zusicherungen.
- **E02** -- Einheit der Klasse 6 auf die der Klasse 5 gekürzt (Präfixfall): 2 rote.
- **E03** -- in der **Probe** `U_MARKTANTEIL` auf den Wert von `U_MARKTRENDITE`
  gesetzt: die Eindeutigkeitszählung schlägt an. Der Selbstschutz der Belegung zählt
  wirklich, statt nur dazustehen.

## Wonach ich gesucht und nichts gefunden habe

- **Abgeschwächte Tests.** Die vier entfernten Zeilen der beiden Commits sind eine
  Umbenennung (`gleich` → `ohne_unterschied`, weil `gleich` jetzt die
  Vergleichsfunktion ist); beide betroffenen Zusicherungen bestehen unverändert
  weiter, eine Kopfzeilen-Zusicherung der Unterschiedsebene kam hinzu. Keine
  Schwelle gesenkt, kein Test übersprungen.
- **Selbstbestätigung der zweiten Abschrift.** `KLASSE_SOLL` könnte vom Modul statt
  von T5 abgeschrieben sein -- deshalb der Wortlautvergleich gegen `technik.md`
  selbst. Stimmt in der deklarierten Umschrift.
- **Grenzverletzung.** Die geänderten Kerndateien beider Commits liegen in der
  `dateien`-Liste des Pakets (nur `zustandsausgabe_probe.cpp`).
- **Nebenwirkung auf den Bestand.** Voller `ctest`-Lauf am unveränderten Prüfbaum:
  10 von 10 grün.

## Anmerkung zur Versionsgeschichte (kein Befund gegen das Paket)

Die eigentliche Arbeit (+573/−4 Zeilen an der Probe) liegt in Commit `757ae04` mit
dem Betreff `datenbauer: 0090-...`; der Commit mit dem 0097-Betreff (`3405c16`)
trägt nur eine Kommentarkorrektur von drei Zeilen. Das ist die bekannte
Runner-Familie „der Commit mit dem Quelltext trägt den Betreff eines anderen
Pakets" (zuletzt bei 0086, dort lag die Arbeit im Commit mit 0097-Betreff). Für das
Urteil zählt der Stand der Datei, nicht der Commitweg; wer die Geschichte dieser
Datei liest, nehme `git log -- <datei>` statt des Betreffs.
