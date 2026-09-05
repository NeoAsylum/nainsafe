---
id: 0121-nachmessung-zinsreihen-zitiert-keine-gliederungszeile
rolle: datenbauer
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/nachmessung-zinsreihen-2026-09-05.md]
abnahme: `belegstellen_riegel` meldet zu Bedingung 2 keinen Befund mehr zu `daten/nachmessung-zinsreihen-2026-09-05.md` und gibt, sofern kein anderer Befund hinzugekommen ist, Code 0. Der Nachweis nennt den Aufruf und die volle Kopfzeile von Bedingung 2 vor und nach dem Eingriff. Die Zahl der uebergangenen Fundstellen steigt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums nicht, und die Zahl der aufgeloesten Zitate sinkt nicht -- ein Verweis, der nur noch unbewertet durchlaeuft, ist keine Reparatur. Traegt das Feld `berichtigt:` danach den Wortlaut einer Gliederungszeile aus `deckungsbefund-1997.md`, steht diese Zeile im Nachweis mit ihrer Zeilennummer.
---

# `berichtigt:` nennt einen Abschnitt, den es in `deckungsbefund-1997.md` nicht gibt

## Was gemessen ist

`belegstellen_riegel`, uebersetzt aus der Quelle vom 2026-09-05 und gegen den Baum von
`2ed2e0c` gelaufen, meldet zu Bedingung 2 genau einen Befund:

```
  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6
  nachgeschlagen in: daten/deckungsbefund-1997.md
  gesuchte Ueberschrift: Die Reihenliste nennt IWF IFS
```

Zeile 6 der Nachmessung ist das Frontmatter-Feld `berichtigt:`. Der genannte Wortlaut
steht in `deckungsbefund-1997.md` tatsaechlich -- aber als **Satz** in Zeile 140, nicht
als Gliederungszeile. Die Zeile, unter der er steht, ist Zeile 138:
`### Reihe 9 — Leitzins (4 Sollreihen) — **die Reihe, an der es reisst**`.

Es ist also nicht der Fall „umbenannt", sondern der Fall „stand nie so da": Ein Satz aus
dem Fliesstext ist als Abschnittsname zitiert worden.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0090.** Aufgefallen ist es bei dessen Pruefung, aber die Datei ist erst
am 2026-09-05 um 09:38 mit `a6c55e0` („Betreiber: Nachmessung Reihe 9") entstanden, also
rund fuenf Stunden **nach** dem Baulauf von 0090 um 04:35, und sie steht in keiner
Dateiliste jenes Pakets. Der Riegel meldet sie in allen fuenf Pruefungslaeufen
unveraendert mit -- vor wie nach dem Eingriff von 0090 und auf beiden Vorher-Staenden.

**Nicht Teil des Riegels.** Er arbeitet richtig: Das ist genau der Fund, fuer den
Bedingung 2 gebaut ist.

**Warum es eilt.** Solange der Befund steht, gibt der Riegel Code 1. Damit ist jeder
Uebersetzungsbericht dieses Vorhabens rot, und vier Bauagenten je Durchgang messen ihren
Vorher-Stand gegen ein rotes Werkzeug -- aus einem Grund, der mit ihrer Arbeit nichts zu
tun hat. Es ist derselbe Schaden, um dessentwillen der Projektmanager die
Gliederungszeile in `rueckstand.md` als Stuetze auf Zeit wieder eingesetzt hat; hier gibt
es keine Stuetze, sondern nur die Reparatur.

## Was der Bauagent entscheiden muss

Der Wortlaut in `berichtigt:` soll sagen, welcher Teil von `deckungsbefund-1997.md`
berichtigt wird. Zwei Wege:

1. **Die tragende Gliederungszeile nennen** -- Zeile 138. Dann ist zu belegen, dass sie
   denselben Gegenstand meint und nicht nur, dass sie existiert.
2. **Den Bezug auf die Zeile umstellen, an der es haengt** -- den Satz aus Zeile 140 im
   Wortlaut als Zitat kenntlich machen, ohne ihn einen Abschnitt zu nennen. Genauer,
   solange die Datei sich noch aendert.

Der Riegel prueft in beiden Faellen dasselbe; die Wahl entscheidet, was ein Leser findet.
