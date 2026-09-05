---
typ: messung
paket: 0122-strichrechnung-sperre-in-sperrehpp
rolle: kernbauer
datum: 2026-09-05
---

# Nachweis zu 0122 -- die Strichrechnungssperre in `sperre.hpp`

Gefahren mit `g++`, Uebersetzer und `ctest` aus `subprocess`, alle Baubaeume unter
`$TMPDIR`. Der Quellbaum ist nur an der einen Datei der Dateiliste angefasst.

## Die geschriebene Zeile

    #pragma GCC poison __builtin_add_overflow __builtin_sub_overflow

Dazu ein Kopfabsatz unter eigener Ueberschrift, der die Einbauregel als Grund nennt.

## Erste Haelfte -- der unveraenderte Baum bleibt gruen

Gemessen am echten Baum, Vorher und Nachher unmittelbar hintereinander:

| Stand | Profil | cmake | build | ctest |
|---|---|---|---|---|
| vorher | `FABRIK_SANITIZER=ON`  | 0 | 0 | 0 -- 14 von 14 |
| vorher | `FABRIK_SANITIZER=OFF` | 0 | 0 | 0 -- 14 von 14 |
| nachher | `FABRIK_SANITIZER=ON`  | 0 | 0 | 0 -- 14 von 14 |
| nachher | `FABRIK_SANITIZER=OFF` | 0 | 0 | 0 -- 14 von 14 |

Der `belegstellen_riegel` meldet vorher und nachher dieselben Zahlen: 44 Bauquellen,
5 Zeilenverweise mit 0 Dateinamen daneben, 36 Zitate, 36 aufgeloest, 47 uebergangen,
14 ohne Anfuehrung.

**Zur Vorsicht des Lesers:** Zu Beginn des Laufs war der `belegstellen_riegel` im
Profil `ON` rot, und zwar an einem Zitat in `daten/`, das nicht zu diesem Paket
gehoert. Waehrend meiner Grundmessung hat ein Fremdlauf (Paket 0120) es berichtigt.
Alle vier Zeilen oben stammen von **nach** diesem Fremdlauf.

## Zweite Haelfte -- der Verstoss bricht ab

An fuenf eingefrorenen Wegwerfbaeumen unter `$TMPDIR`, alle aus **einem**
Schnappschuss des Quellbaums kopiert, damit kein Fremdlauf dazwischenfaellt. Der
Verstoss ist jedes Mal derselbe: die betroffene Funktion als eigene Fassung im
anonymen Namensraum von `kern/src/werte.cpp`, die zugehoerige `using`-Zeile entfernt.

| Baum | Sperrzeile | Verstoss | Ergebnis |
|---|---|---|---|
| S  | nein | -- | build 0, ctest 13 von 14 |
| S1 | ja   | -- | build 0, ctest 13 von 14 |
| S2 | nein | eigenes `plus`  | build 0, ctest 13 von 14 |
| S3 | ja   | eigenes `plus`  | **build 2** -- `werte.cpp:103:9: error: attempt to use poisoned` `__builtin_add_overflow` |
| S5 | nein | eigenes `minus` | build 0, ctest 13 von 14 |
| S4 | ja   | eigenes `minus` | **build 2** -- `werte.cpp:103:9: error: attempt to use poisoned` `__builtin_sub_overflow` |

GCC nennt in beiden roten Faellen die Zeile der Vergiftung als Fundort dazu
(`sperre.hpp:69`, Spalte 20 fuer die Addition, Spalte 43 fuer die Subtraktion).

**Warum sechs Baeume und nicht zwei.** S1 ist die Positivkontrolle: Eine Sperre, die
alles verbietet, saehe im Negativtest gleich aus. S2 und S5 sind die Luecke selbst --
ohne die Zeile laeuft der Verstoss durch. Und beide Bezeichner der Vergiftungszeile
sind einzeln sabotiert; eine Mutation allein haette die halbe Zeile belegt.

**Das schaerfste Einzelergebnis:** Das `ctest`-Protokoll von S2 ist nach dem Ersetzen
des Baumnamens **zeichengleich** zu dem von S. Der Satz aus dem Paket -- keine Messung
unterscheidet die Zweitfassung von der richtigen -- ist damit selbst gemessen und nicht
abgeschrieben.

**Eine Einschraenkung, die dazugehoert:** An den Wegwerfbaeumen ist der
`belegstellen_riegel` rot, weil ein Baum ausserhalb des Repos kein `specs/` hat und der
Riegel ueber das fehlende Verzeichnis faellt -- nicht ueber einen Inhalt. Deshalb steht
dort 13 von 14 und deshalb sind die Zitatzahlen oben am echten Baum gemessen.

## Was die Zeile nicht tut

`*`, `+` und `-` als **Operator** sind nicht vergiftet; das ist Massnahme 4.3 und liegt
bei Paket 0074. `__builtin_mul_overflow` ist ebenfalls nicht vergiftet: Der Kern
benutzt ihn nirgends (`grep -rln` ueber `kern/` und `pruefstand/`), und eine Vergiftung
ohne eine einzige erlaubte Stelle waere ein Verbot statt eines Riegels.
