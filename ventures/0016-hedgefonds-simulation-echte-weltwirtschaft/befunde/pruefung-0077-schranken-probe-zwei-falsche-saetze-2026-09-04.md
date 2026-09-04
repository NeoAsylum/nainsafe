---
typ: pruefung
paket: 0077-schranken-probe-zwei-falsche-saetze
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen selbst nachgemessen -- die vier Muster mit ihren Trefferzahlen, die 12 in `parameter.toml`, eigener Neubau samt `ctest`; dazu beide Ersatzsaetze gegen `parameter.toml` nachgeschlagen, ein Mutationsstand mit vier Faellen (Kontrolle gruen, drei Mutanten tot, darunter der auf die geschuetzte Konstante) und ein Maschinencodevergleich alt/neu, der zeigt, dass keine Zusicherung angefasst wurde.
befunde: 1
---

# 0077: Abnahme erfuellt. Beide Ersatzsaetze sind nachgeschlagen und tragen.

## Vorbemerkung: was dieses Paket pruefbar macht, und was nicht

Das Paket aendert ausschliesslich Kommentartext. Damit zerfaellt die Pruefung in zwei
Fragen, die verschiedene Nachweise brauchen:

1. **Steht der neue Text da, und ist er wahr?** Das ist die eigentliche Sache. 0044 hat
   seine Abnahme erfuellt und trotzdem einen falschen Satz hinterlassen, weil die
   Bedingung nur die *Abwesenheit eines Musters* mass. Ich messe deshalb den **Ersatz**
   gegen `parameter.toml`, nicht gegen den Paketrumpf.
2. **Ist unterwegs eine Zusicherung verlorengegangen?** Kommentaraenderungen sind der
   bequemste Ort, um still eine Schwelle mitzunehmen. Dagegen hilft kein Lesen, sondern
   ein Vergleich des erzeugten Maschinencodes.

## Bedingung 1 -- der Kopfsatz verspricht keine Zeilennummer mehr

Muster `Schluesselname und Zeile` ueber `kern/test/schranken_probe.cpp`: **kein Treffer.**
Muster `Zeile 0-9 (Ziffer hinter dem Wort)` ueber dieselbe Datei: **kein Treffer.**

**Der Rotnachweis dazu, damit die beiden Nullen etwas heissen:** Beide Muster gegen die
Fassung *vor* dem Baucommit gelegt (`git show 113d91b^:.../schranken_probe.cpp`) --
`Schluesselname und Zeile` **1 Treffer**, `Jeder Schluessel der Datei steht genau einmal`
**1 Treffer**. Die Bedingungen unterscheiden also den kaputten vom heilen Stand; sie sind
nicht bloss zwei Muster, die nirgends vorkommen.

**Und der Ersatz traegt.** Der Satz lautet heute "Schluesselname und die zitierte
Schluesselzeile stehen bei jedem". Beides steht bei jedem der drei Schluessel -- der Name
im Feldkommentar und noch einmal im Belegblock, die Schluesselzeile als Zitat darunter.
Nachgeschlagen gegen `parameter.toml`:

| Schluessel | Zeile heute | Wortlaut | Zitat in der Probe |
|---|---:|---|---|
| `stufen_max` | 254 | Wert 1, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |
| `aufschlag` | 299 | Wert 51, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |
| `druck_max` | 353 | Wert 1, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |

