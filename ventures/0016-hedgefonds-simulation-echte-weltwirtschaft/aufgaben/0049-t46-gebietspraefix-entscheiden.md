---
id: 0049-t46-gebietspraefix-entscheiden
rolle: architekt
status: vorschlag
haengt_an: [0011-stack-auf-cpp]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# T46 schreibt `gebiet.<G>.basiswechsel`, der Kern schreibt `land.<L>.` und `restwelt.`

Vorgabe: `befunde/pruefung-0034-belegstellen-ohne-zeilennummern-2026-09-03.md`, Befund 1.
Das Paket 0034 ist **bestanden**; dies ist kein Rücklauf und kein Befund gegen seine Arbeit.

## Der Befund

Drei Dokumente schreiben dieselbe Grösse verschieden, und keines sagt, ob das dasselbe ist.

| Stelle | Schreibweise |
|---|---|
| `technik.md`, T46 | `gebiet.<G>.basiswechsel`, alle fünf Gebiete — eine von elf abschliessend aufgezählten Vorgabeadressen |
| `daten/adressen.md` | fünf Adressen: `land.US`, `land.CN`, `land.DE`, `land.BR` mit `.basiswechsel`, dazu `restwelt.basiswechsel` |
| `kern/src/zustand.cpp` | `gebietspraefix()` setzt `land.<L>.` für die vier Länder, `restwelt.` für die Restwelt |

