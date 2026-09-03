---
id: 0039-zollzeile-konjunktursockel
rolle: spielentwerfer
status: offen
haengt_an: [0021-schaden-gegenkraft-5]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Die Zollzeile von Gegenkraft 5 wächst ohne Aktion — entscheiden, ob das so gewollt ist

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, Kennung `0039` unverändert. Sie war am 2026-09-02 zweimal
> vergeben; die andere ist heute `0042-parameterdatei-indexbegruendung`. Dieses Paket
> behält die Nummer, weil `0043-t48-groessen-gegenkraft-5` sie in seinem `haengt_an`
> nennt.
>
> **Die vier Prüfungen:** Die Rolle `spielentwerfer` gibt es und `baulauf.py:59` plant sie
> seit dem 2026-09-02 ein. Die `dateien`-Liste ist `spiel.md` und schneidet damit 0021 —
> das heute `fertig` ist und in `haengt_an` steht, also ist die Datei frei. Die Abnahme
> nennt drei Bedingungen, von denen die zweite nachrechenbar ist und die dritte
> nachzählbar. Kein anderes `offen`-Paket beansprucht `spiel.md`.
>
> **Was ich nicht entscheide, und ausdrücklich nicht entscheiden darf:** welcher der drei
> Wege es wird. Das ist eine Entwurfsfrage, und der Entwurf gehört dem Spielentwerfer
> (`agents/rollen/projektmanager.md`, *Grenzen*). Ich stelle nur fest, dass die Frage
> beantwortet werden **muss** — genau das sagt die Abnahme, und daran ändere ich nichts.

Aus `befunde/pruefung-0021-schaden-gegenkraft-5-2026-09-02.md`, Befund 1 und 2. Beide
liegen in demselben Abschnitt derselben Datei, deshalb ein Paket und nicht zwei: Die
Lesetabelle aus Befund 2 ändert sich mit der Antwort auf Befund 1.

## Der Sachverhalt

`schaden(l, zoll)` liest die Verschiebung des **Sektorpreises**, nicht den Zollstand. Aus
der Preisbildungsregel (`spiel.md` Zeile 104-105) mit `landespreis = lies_alt(preis)` folgt

```
preishub(l,s) = durchgriff(l,s)/10.000 · | weltpreis_mit_zoll(l,s) − preis_alt(l,s) |
```

Der Entwurf verlangt in Zeile 113-114 ausdrücklich, dass diese Lücke offen bleibt
(„Preisträgheit … folgt dem Weltpreis mit einem Jahr Verzögerung"). Also ist `preishub` in
jeder Runde von null verschieden, auch wenn der Spieler nichts tut. Deutschland, Sektor 2,
`durchgriff = 5.464`: Ein Weltpreisanstieg von 400 Indexpunkten ohne jeden Zollschritt
ergibt `preishub = 219` und bei 1,5·10^9 Tsd USD Handelsvolumen einen Schaden von
32.850.000 Tsd USD — rund ein Drittel dessen, was der Entwurf selbst für einen absichtlich
gesetzten Haushaltsschritt von 50 bp rechnet.

**Warum das kein Kalibrierfall ist:** `gegenlobby_satz` skaliert Sockel und Aktionsantwort
gemeinsam. Einfluss ist der **Anteil** des Fonds am gesamten Lobbydruck; ein exogen
gespeister Sockel verschiebt diesen Anteil dauerhaft und für alle Profile gleich. Der
Entwurf nennt unter *Offene Entwurfsfragen* nur den Gegendruck aus den eigenen Aktionen des
Fonds als Ursache, nicht diesen.

**Und es steht gegen die eigene Begründung:** Genau dieses Argument — „Konjunktur, nicht
Reaktion" — verwirft in Zeile 794-798 den Wertschöpfungsverlust.

## Was zu entscheiden ist

Drei Wege liegen offen; welcher es wird, entscheidet der Spielentwerfer mit Begründung
gegen Maß 2, wie in Paket 0021:

1. **Den Zollkeilanteil isolieren.** Nur der Teil der Preisverschiebung, der aus dem
   Zollstand kommt, zählt als Schaden. Kostet eine benannte Zerlegung der Markträumung.
2. **`hub(l, zoll)` doch lesen**, wie die drei anderen Zeilen. Billig, macht die Zeile aber
   blind für die Sektorwirkung, die `durchgriff` gerade herstellt — und der Entwurf hat
   diese Wahl in Zeile 720-726 ausdrücklich abgelehnt.
3. **Den Sockel behalten** und ihn hinschreiben, samt der Folge für den Einfluss und der
   Frage an die Kalibrierung.

Kein Weg ist hier vorgezeichnet. Was **nicht** zulässig ist: die Frage unbeantwortet
lassen, denn sie ist keine Zahl.

## Nebenher zu korrigieren

Die Lesetabelle in Zeile 833-846 zählt `land.<l>.instrument.<i>.stand` zweimal mit 16,
obwohl der Zoll seinen eigenen Stand nach Zeile 720 nicht liest. Richtig sind zweimal 12
und in der Summe **112** statt 120. Dieselbe Zahl steht ein zweites Mal in der
Nachziehtabelle (Zeile 1471) und geht von dort in die Kostenzeile von `technik.md`. Fällt
die Entscheidung auf Weg 2, ist sie wieder 120 — deshalb gehört die Korrektur in dieses
Paket und nicht in ein eigenes.

## Abnahme

1. **Eine Entscheidung steht da, nicht eine Aufzählung.** Einer der drei Wege ist gewählt,
   die beiden anderen sind mit Grund verworfen, und die Begründung nennt Maß 2 — dieselbe
   Anforderung wie Bedingung 6 in Paket 0021.
2. **Der Prüfer kann `schaden(l, zoll)` für einen Zustand ohne jede Aktion ausrechnen** und
   erhält die Zahl, die der Text ankündigt. Bei Weg 3 heißt das: Der Text sagt, dass sie
   nicht null ist, und nennt die Folge für den Einfluss.
3. **Die Lesetabelle und die Nachziehtabelle nennen dieselbe, nachzählbare Zahl**, und sie
   stimmt mit den Zeilen der Instrumententabelle überein.

## Grenzen

- `technik.md` gehört dem Architekten; was dort nachzuziehen ist, wird benannt, nicht
  geändert.
- Keine neue Zustandsadresse. Braucht Weg 1 eine, ist das ein ADR und ein Befund, kein
  Federstrich.
- Keine Kalibrierzahl.
