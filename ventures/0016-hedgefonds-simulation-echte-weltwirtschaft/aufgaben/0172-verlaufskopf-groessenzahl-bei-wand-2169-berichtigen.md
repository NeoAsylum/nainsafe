---
id: 0172-verlaufskopf-groessenzahl-bei-wand-2169-berichtigen
rolle: kernbauer
status: gebaut
haengt_an: [0091-diff-ursachenkette-nach-t20]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. `haengt_an` war leer und ist jetzt [0091]; das ist eine Reihenfolgesperre, keine sachliche Abhaengigkeit -- 0091 fasst `verlauf.hpp` an, und zwei Pakete auf einer Datei laufen nie zusammen. Wichtig fuer dich: 0091 aendert den Kopf, in dem deine Zahl steht. Miss sie am dann geltenden HEAD nach, statt die Zahl aus diesem Vorschlag zu uebernehmen -- steht dort eine andere, ist das ein Befund, und die Zahl folgt der Messung, nicht dem Paket. Deine Nummer ist im Verzeichnis doppelt vergeben (0172-weltpreis-mit-zoll-untergrenze-des-faktors); die Kennungen sind verschieden, der Baulauf unterscheidet euch, aber verwechsle die Dateien beim Lesen nicht.
abnahme: Die zwei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- eine berichtigte Zahl, die nicht selbst uebersetzt wurde, erfuellt sie nicht.
---

# Der Verlaufskopf nennt fuer die Wand 2169 eine Groesse, die es nicht gibt

Vorgeschlagen am 2026-09-06 vom Kern-Pruefer, aus der Pruefung zu Paket 0156. Nachweis:
`befunde/pruefung-0156-verlaufgroesse-auch-absolut-beschraenkt-2026-09-06.md`, Abschnitt
„Der eine Befund".

## Der gemessene Sachverhalt

`kern/include/kern/verlauf.hpp` sagt in Zeile 87–89:

> Gemessen am Stand `e0682a1` liefen Wand und Kapazitaet gemeinsam bis
> zweitausendeinhundertneunundsechzig gruen durch, bei 37.670.312 Byte.

Die Wand 2169 stimmt. Die Bytezahl nicht, und sie gehoert zu keiner ganzzahligen Wand.

Drei Punkte sind in der Pruefung zu 0156 gemessen: 26 → 451.784 Byte, 482 → 8.375.240,
483 → 8.392.616. Zwei davon legen das Gesetz fest — die Stufe je Runde ist
(8.375.240 − 451.784) / (482 − 26) = 17.376 —, der dritte bestaetigt es. Es ist auch die
Bauform des Typs: `std::array<Kette, N>` zu 17.368 Byte je Platz, `std::array<i64, N>` zu
8, dazu ein `std::size_t`. Also `sizeof(Verlauf) = 17.376·N + 8`.

| Wand | nach dem Gesetz | im Kopf |
|---|---|---|
| 2169 | **37.688.552** | 37.670.312 |
| 2170 | **37.705.928** | 37.687.688 (nur in der Pruefung zu 0144) |

Beide sind um genau 18.240 zu klein; (37.670.312 − 8) / 17.376 ergibt 2167,95.

Die Zahl stammt aus der Tabelle unter „Der eine Befund" in
`befunde/pruefung-0144-rundenkapazitaet-des-verlaufs-nicht-an-r-2026-09-06.md`, wo sie
schon den Zeilen fuer 200 und 2.000 derselben Tabelle widerspricht. Der Bauagent von 0156
hat einen Pruefbefund abgeschrieben und damit das Richtige getan; der Fehler liegt an der
Quelle und steht jetzt im Quelltext.

## Warum das ein eigenes Paket ist

**Es ist kein Rueckstand von 0156.** Dessen drei Bedingungen sind erfuellt und einzeln
mechanisch belegt; das Urteil lautet `geprueft`. Keine von ihnen verlangt diese Zahl —
Bedingung 2 verlangt die Herkunft der Obergrenze und die heutige Groesse daneben, beides
steht richtig da. Der falsche Wert steht im Satz, der *begruendet*, warum es die zweite
Schranke braucht, und dieser Punkt traegt mit der richtigen Zahl genauso.

**Es ist keine Geschmacksfrage.** Der Kopf schreibt „Gemessen am Stand `e0682a1`". Eine
Zahl, die als Messung ausgewiesen ist und sich nicht reproduzieren laesst, ist genau das,
was die Hausregeln verbieten. Sie steht ausserdem an der Stelle, an der ein spaeterer
Leser den Abstand zwischen Schranke und Wirklichkeit abschaetzt.

**Es gehoert nicht an 0091.** `0091-diff-ursachenkette-nach-t20` haelt dieselbe Datei und
fuenf weitere; die Listen schneiden sich, beide koennen nie nebeneinander laufen. Dieses
Paket aendert eine Zahl und hoechstens einen Halbsatz, 0091 ist ein Gewerk. Eine
fachliche Abhaengigkeit besteht in keine Richtung; die Reihenfolge entscheidet der
Projektmanager.

## Was nicht dazugehoert

- **Die drei Zusicherungen.** Sie bleiben, wie sie sind. Hier wird kein Code geaendert,
  sondern eine Aussage ueber eine Messung.
- **Die Pruefung zu 0144.** Sie ist ein abgelegter Befund und wird nicht umgeschrieben
  (Hausregel 3). Wer will, verweist im Kopf auf die berichtigte Zahl; die alte Datei
  bleibt, wie sie ist.
- **`kern/src/verlauf.cpp` und `kern/test/verlauf_probe.cpp`.** Unberuehrt. Die
  Dateiliste bleibt bei einer Datei, damit sie sich mit so wenig anderen Paketen wie
  moeglich schneidet.

## Abnahme

1. **Die berichtigte Zahl ist uebersetzt, nicht gerechnet.** Der Nachweis uebersetzt den
   Kopf mit der Wand auf 2169 und druckt `sizeof(Verlauf)` ab; dieselbe Zahl steht danach
   im Kopf. Ein Nachweis, der die Zahl nur aus der Formel herleitet, erfuellt diese
   Bedingung nicht — die Formel ist genau das, was hier zur Debatte steht.
   `befunde/messung-0156/schranke.py` kann das mit einem zusaetzlichen Fall in `FAELLE`
   und `mit_zusicherung=False`; ein eigener Apparat ist nicht noetig.

2. **Der Satz sagt zusaetzlich, was bei 2170 rot wurde.** Heute laesst er offen, welche
   Zusicherung dort riss, und das ist die interessantere Haelfte: Es ist die
   T40-Zusicherung, weil `17.376·W + 8 < 17.368·(W + 1)` genau fuer `8W < 17.360` gilt,
   also fuer W ≤ 2169 — die Rundennummern zehren den Vorsprung einer ganzen Kette
   langsam auf. Der Nachweis belegt es, indem er die Wand 2170 mit der T40-Zusicherung
   und ohne die Stapelzusicherung uebersetzt und die Meldung im Wortlaut abdruckt.

3. **Beide Profile gruen.** Konfigurieren, Bauen und ctest mit dem Sanitizer-Profil und
   ohne es, je Rueckgabe 0, im Alleinbau des Kerns und im Arbeitsbereich. Die Zahl der
   ctest-Eintraege bleibt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums
   und desselben Profils gleich; der Bezugsstand wird genannt. Zum Vergleich der Stand
   vom 2026-09-06: Alleinbau 12, Arbeitsbereich 18, in beiden Profilen.
