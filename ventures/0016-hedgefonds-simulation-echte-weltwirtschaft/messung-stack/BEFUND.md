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
| rust | ja | 73 | 653 | ja | 0 | 2080000000000000 |
| cpp | ja | 70 | 520 | ja | 0 | 2080000000000000 |
| java | ja | 110 | 312 | ja | 0 | 2080000000000000 |
| python | gedeutet | 104 | 19879 | ja | 0 | 2080000000000000 |

## Stimmen die Prüfsummen überein?

**Ja** — alle 4 auf `2080000000000000`. Damit haben die Umsetzungen dieselbe Rechenvorschrift getroffen, und die übrigen Spalten sind vergleichbar.
