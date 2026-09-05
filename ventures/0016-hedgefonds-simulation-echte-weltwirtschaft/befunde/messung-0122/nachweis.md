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
