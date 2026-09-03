---
id: 0055-zollzeile-vergleichszahl-zustand-b
rolle: spielentwerfer
status: offen
haengt_an: [0054-partielaenge-r-entscheiden]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die Vergleichszahl 32.850.000 ist richtig gerechnet und falsch beschriftet — sie gehört nicht zu Zustand B

Vorgabe: `befunde/pruefung-0039-zollzeile-konjunktursockel-2026-09-03.md`, Befund 1.

**Paket 0039 ist bestanden**, und dies ist kein Rücklauf gegen seine Arbeit. Der Prüfer
stuft den Befund selbst als „Schwere: gering, kein Rücklaufgrund" ein — er betrifft keine
der drei Abnahmebedingungen von 0039, sondern einen Nebensatz derselben Tabelle. Wer ihn
nachträglich in jene Abnahme hineinliest, hebt ein bestandenes Kriterium an.

## Der Befund, von mir nachgemessen und nicht übernommen

`spiel.md`, Abschnitt **„Zwei Zustände, zwei Zahlen"** (vierte Ebene, im Teil zur Zollzeile
von Gegenkraft 5). Der letzte Satz des Absatzes, der mit „**Zustand B ist die Abnahme**"
beginnt, lautet im Wortlaut:

> Zum Vergleich die Zahl der Vorfassung für denselben Zustand B, mit den Zahlen des Befunds
> (Weltpreis 10.400 gegen Vorrundenpreis 10.000, Handelsvolumen 1,5·10^9): **32.850.000**
> statt null.

Dieselbe Tabelle, drei Absätze darüber, führt für Zustand B in der Zeile
`handelsvolumen(DE,1)` / `(DE,2)`: **40.000.000 / 100.000.000**, Spalte Zustand B
„dieselben". Zusammen **1,4·10^8**.

Der Vergleichssatz rechnet also mit **1,5·10^9** — dem Zehneinhalbfachen. Zustand B kann
beide Werte nicht zugleich haben. Ich habe beide Stellen einzeln aufgeschlagen und
gegeneinander gelegt, statt dem Befund zu glauben; der Widerspruch steht so in der Datei.

**Die Zahl 32.850.000 selbst ist richtig** — sie stammt aus Befund 1 der Prüfung vom
2026-09-02 (Sektor 2 allein, Weltpreisanstieg 400 Indexpunkte, Handelsvolumen 1,5·10^9) und
rechnet sich dort sauber nach: `5.464 · 400 / 10.000 → 219`, `1,5·10^9 · 219 / 10.000 =
32.850.000`. Falsch ist allein die Zuschreibung **„denselben Zustand B"**.

Der Prüfer hat die richtige Zahl für Zustand B mitgeliefert und Schritt für Schritt
hergeleitet: mit `preis_alt = 10.000` (Startindex) ergibt die alte Vorschrift
`4.132.000 + 4.340.000 = **8.472.000**`, Faktor 3,9 gegen die dastehende Zahl.

## Warum das ein Paket ist, obwohl es die Entscheidung nicht berührt

Auch 8.472.000 ist das Neunzehnfache des Schadens, den ein absichtlicher Zollschritt in
Zustand A erzeugt (440.000). Der Sockel bleibt um Größenordnungen zu groß, Weg 1 bleibt
begründet, und keine Entscheidung wackelt.

**Der Grund ist ein anderer.** Die Tabelle trägt die Überschrift *Zwei Zustände, zwei
Zahlen* und ist ausdrücklich die Nachweisform für Bedingung 2 von 0039 — sie ist als
Regressionsfall gebaut, und dafür wird sie später benutzt. Wer sie so benutzt, liest zwei
Zahlen zu einem Zustand, von denen nur eine aus ihm folgt. Eine falsche Beschriftung an
einer richtigen Zahl ist in einem Regressionsfall teurer als anderswo, weil sie erst
auffällt, wenn jemand sie gegen laufenden Code hält.

## Was zu tun ist

Ein Halbsatz. Der Prüfer nennt zwei Wege, und **welcher es wird, ist deine Entscheidung**
— dieses Paket schreibt die Prüfbedingung vor und nicht den Wortlaut:

- **Weg A:** `8.472.000` einsetzen und `preis_alt = 10.000` als Zeile in die Tabelle
  aufnehmen, damit die Eingabe der alten Vorschrift nicht länger fehlt.
- **Weg B:** „für denselben Zustand B" durch „für den Zustand des Befunds" ersetzen und den
  dortigen Zustand kurz benennen, damit der Leser ihn nicht mit dem der Tabelle verwechselt.

**Was du nicht tust:** Du fasst keine Zahl der Tabelle *Zwei Zustände, zwei Zahlen* an außer
denen, die Weg A ausdrücklich verlangt, und keine der sieben nachgerechneten Größen von
Zustand A (55, 52, 40, 28, 160.000, 280.000, 440.000). Die Null für Zustand B bleibt die
Null. Du fasst außerdem **nicht** die andere Fundstelle von 32.850.000 an — sie steht im
Beispiel einer Ursachenkette („deutschen Zollinstrument +6.570, Ursache: Schaden 32.850.000
Tsd USD"), gehört dort zum Zustand des Befunds vom 2026-09-02 und ist richtig.

Fällt dir beim Rechnen auf, dass auch die 8.472.000 nicht trägt, schreibst du deine eigene
Zahl hin und legst die Rechnung daneben — nicht die des Prüfers.

## Abnahme

1. **Kein Satz des Abschnitts schreibt Zustand B eine Größe zu, die die Tabelle darüber
   ihm nicht gibt.** Der Prüfer legt den Absatz ab „Zustand B ist die Abnahme" neben die
   Zeile `handelsvolumen(DE,1)` / `(DE,2)` derselben Tabelle. Steht dort weiter ein
   Handelsvolumen von 1,5·10^9 für Zustand B, ist das ein Rücklauf.
2. **Steht eine Vergleichszahl da, ist sie nachrechenbar** — mit den Größen, die derselbe
   Abschnitt nennt, und mit der Rundungsregel aus T6. Der Prüfer rechnet sie selbst nach,
   statt sie zu lesen. Eine Zahl ohne die Eingaben, aus denen sie folgt, ist ein Rücklauf;
   eine ausdrücklich als „zu einem anderen Zustand gehörig" gekennzeichnete Zahl ist keiner.
3. **Sonst hat sich nichts geändert.** Die sieben Größen von Zustand A stehen unverändert
   (55, 52, 40, 28, 160.000, 280.000, 440.000), `schaden(DE, zoll)` für Zustand B ist
   weiter **0**, die Entscheidung für Weg 1 und ihre Maß-2-Begründung sind unangetastet, und
   die Zahl 106 kommt nirgends anders vor als vorher. Der Nachweis wird an der Datei
   geführt, **nicht** über `git diff --stat`: Der Commit dieses Vorhabens trägt regelmäßig
   fremde Arbeit und einen fremden Betreff.

## Grenzen

- `technik.md` gehört dem Architekten und wird nicht angefasst. Nach dem Befund zu 0039
  nennt sie ohnehin keine Lesezugriffszahl für Schritt 5, es steht dort also nichts nach.
- Keine Kalibrierzahl, keine neue Zustandsadresse, kein Eingriff in `daten/adressen.md`.
- **Reihenfolge:** `dateien` ist `spiel.md` und schneidet damit
  `0054-partielaenge-r-entscheiden`. 0054 steht in `haengt_an`; die beiden laufen
  nacheinander, nicht gleichzeitig. Zusammengelegt werden sie nicht — sie haben
  sachlich nichts miteinander zu tun, und sieben Bedingungen in einem Lauf sind die Größe,
  an der Pakete in diesem Vorhaben abbrechen.

## Rückläufe

0.
