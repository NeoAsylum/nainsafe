---
typ: stackmessung
datum: 2026-09-01
sprachen_gemessen: 4
pruefsummen_einig: ja
---

# Vier Sprachen, dieselbe Aufgabe

Erzeugt von `agents/stackmessung.py`. Kein Modell, kein Gutachten -- das
Urteil des Compilers und der Uhr.

| Sprache | übersetzt | Zeilen | ns/Schritt | wiederholbar | Gleitkomma | Prüfsumme |
|---|---|---:|---:|---|---:|---:|
| rust | ja | 78 | 494 | ja | 0 | 1163237642073673 |
| cpp | ja | 82 | 947 | ja | 0 | 1163237642073673 |
| java | ja | 106 | 316 | ja | 0 | 1163237642073673 |
| python | gedeutet | 82 | 50383 | ja | 0 | 1163237642073673 |

## Stimmen die Prüfsummen überein?

**Ja** — alle 4 auf `1163237642073673`. Damit haben die Umsetzungen dieselbe Rechenvorschrift getroffen, und die übrigen Spalten sind vergleichbar.
