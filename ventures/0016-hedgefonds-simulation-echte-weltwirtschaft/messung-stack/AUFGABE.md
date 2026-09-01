# Messung: welche Sprache schreibt ein Bauagent hier am besten?

Vier Argumente über den Stack, alle aus fremden Benchmarks. Diese Messung ersetzt sie
durch eigene Zahlen.

**Dieselbe Aufgabe, vier Sprachen, ein Vergleich.** Die Aufgabe ist absichtlich klein
und vollständig festgelegt — es geht nicht um Erfindung, sondern darum, wie zuverlässig
ein Agent eine präzise Vorgabe in der jeweiligen Sprache trifft.

## Die Aufgabe

Ein deterministischer Festkomma-Weltschritt, wie ihn der Kern von 0016 braucht.

**Zustand:** 64 Werte, ganzzahlig, 64 Bit vorzeichenbehaftet. Startbelegung:
`z[i] = 1_000_000 + i * 37` für `i` von 0 bis 63.

**Ein Weltschritt**, genau in dieser Reihenfolge, `i` aufsteigend von 0 bis 63:

1. `nachbar = z[(i + 17) mod 64]`
2. `roh = mal_geteilt(z[i], 10_000 + (nachbar mod 977), 10_000)`
3. `z[i] = klemme(roh + (nachbar / 1024) - (z[i] / 4096), 0, 1_000_000_000_000)`

Dabei:

- **`mal_geteilt(a, b, c)`** rechnet `a * b / c` **ohne Überlauf im Zwischenergebnis**
  (128 Bit oder gleichwertig) und rundet **auf halbe Beträge von null weg**.
- **`klemme(x, u, o)`** begrenzt `x` auf `[u, o]`.
- **Ganzzahldivision schneidet gegen null ab.**

**Ausgabe nach genau 1.000.000 Weltschritten**, drei Zeilen, exakt dieses Format:

```
pruefsumme=<dezimal>
nanosekunden_je_schritt=<dezimal>
zustand0=<dezimal>
```

Die Prüfsumme ist `summe(z[i] * (i + 1)) mod 2^63 - 1`, berechnet mit Überlaufumbruch.

## Regeln

- **Kein Gleitkommatyp.** Nirgends, auch nicht für die Zeitmessung der Ausgabe.
- **Keine Fremdbibliothek** über die Standardbibliothek hinaus.
- **Eine Datei**, wenn die Sprache es zulässt.
- Das Programm läuft ohne Argumente und ohne Eingabe.

## Was gemessen wird

| Größe | wie |
|---|---|
| Anläufe bis zum grünen Übersetzungslauf | der Runner zählt sie |
| Zeilen Code | `wc -l` |
| Nanosekunden je Schritt | das Programm gibt sie selbst aus |
| Wiederholbarkeit | zweimal laufen lassen, Prüfsummen vergleichen |
| Gleitkomma im Quelltext | `grep` nach `float`, `double`, `f64`, `f32` |

Die Prüfsummen **aller vier Sprachen müssen übereinstimmen**. Tun sie es nicht, hat
mindestens eine Umsetzung die Vorgabe verfehlt — und *welche*, sagt der Vergleich mit
den übrigen drei.

Das ist der eigentliche Wert dieser Messung: Sie prüft nicht nur, ob eine Sprache
schnell ist, sondern ob vier unabhängige Agenten dieselbe präzise Rechenvorschrift
treffen.
