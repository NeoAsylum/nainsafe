---
id: 0087-geprueftes-plus-und-minus-in-festkomma
rolle: kernbauer
status: vorschlag
haengt_an: [0002-fondsbewertung-definieren]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: `plus` und `minus` stehen als geprueftes Paar in `festkomma.hpp` neben `mal`, `werte.cpp` hat keine eigene Fassung mehr, und `festkomma_probe` weist beide Abbruchpfade an den Raendern von i64 nach -- je eine Positivkontrolle mit dem groessten noch passenden Wert davor.
---

# Die geprueften Strichrechnungen gehoeren neben `mal`

**Vorgeschlagen am 2026-09-04 vom Kernbauer aus Paket 0002.**

## Der Sachverhalt

T7 Massnahme 4 schneidet die geprueften Rechenarten nach der **Rechenart** und nicht
nach der Stelle, "damit keine Art zwischen ihnen liegen bleibt". Drei Formen:
die Verengung jedes 128-Bit-Zwischenwerts (4.1), die Strichrechnung auf `i64` (4.2)
und die Multiplikation ohne folgende Division (4.3).

Zwei der drei stehen in `festkomma.hpp`: 4.1 als `intern::nach_i64`, 4.3 als `mal`.
Die dritte stand bis zu Paket 0002 nirgends, weil der Kern keine Strichrechnung auf
Groessen nach T5 hatte. Mit `kern::werte` hat er sie -- `fondsvermoegen`, `bip`,
`handelsvolumen`, `fondsanteil`, `korbbestand` und `marktkorb` addieren alle --, und
sie steht jetzt als `plus` und `minus` im anonymen Namensraum von `kern/src/werte.cpp`.

## Warum das ein eigenes Paket ist und nicht Teil von 0002

Die Dateiliste von 0002 nennt `festkomma.hpp` nicht. Der Baulauf plant nur Pakete
gleichzeitig ein, deren Dateilisten sich nicht schneiden; ein Bauagent, der ausserhalb
seiner Liste schreibt, trifft den, der gerade daran arbeitet. Paket 0052 hat `mal` in
genau jene Datei gelegt und sie damit beansprucht. Der richtige Weg ist deshalb nicht,
0002 zu erweitern, sondern den Umzug einzeln zu planen.

## Warum es nicht bei "waere auch gut" bleibt

Der Ort entscheidet ueber die Wirkung der Vorgabe, nicht ueber ihre Schoenheit. Drei
belegbare Folgen des heutigen Zustands:

1. **Das naechste Modul schreibt seine eigene Fassung.** Der Kopf von `meldung.hpp`
   beschreibt genau diesen Verlauf fuer die Meldungsklasse: Sie stand in einer Quelle
   im anonymen Namensraum, die sechs Schrittpakete brauchten sie einzeln, und ohne den
   Umzug haette sie in zwei Fassungen dagelegen, die auseinanderlaufen. Bei einer
   Ueberlaufpruefung heisst auseinanderlaufen: Ein Modul bricht ab, das andere bricht
   um.
2. **Der mechanische Nachweis aus T6b greift nicht.** `festkomma.hpp` ist nach T6 "die
   einzige Rechenstelle des Kerns"; eine gepruefte Addition ausserhalb macht diesen
   Satz zu einem, der eine Ausnahme hat -- und eine Ausnahme, die nur ein Bauagent
   kennt, ist keine.
3. **Die Abbruchpfade sind heute unpruefbar.** `plus` und `minus` sind privat und
   haben keinen Aufrufer ausserhalb ihrer Datei; die Probe von 0002 kommt an sie nicht
   heran und weist die beiden Ueberlaeufe deshalb nicht nach. Neben `mal` in
   `festkomma.hpp` prueft sie `festkomma_probe` mit derselben Bauart, mit der sie den
   Waechter von `mal` schon prueft.

## Umfang

* `plus(i64, i64)` und `minus(i64, i64)` nach `festkomma.hpp`, `constexpr`, gebaut
  ueber die Ueberlaufbausteine des Uebersetzers wie in T7 Massnahme 4.2 vorgeschrieben,
  mit Abbruch statt Kappung.
* Die beiden Fassungen aus dem anonymen Namensraum von `werte.cpp` entfernen und die
  Aufrufe auf die neuen umstellen. `betrag` bleibt vorerst dort: Es ist keine der drei
  Rechenarten aus T7, sondern eine Vorzeichenregel, und wo sie hingehoert, entscheidet
  das erste Modul, das sie ein zweites Mal braucht.
* In `festkomma_probe` je zwei Pruefungen: der groesste noch passende Wert als
  Positivkontrolle, ein Schritt darueber als Abbruch -- fuer beide Vorzeichen. Die
  Zahlen werden hergeleitet (`I64_MAX`, `I64_MIN`) und nicht abgeschrieben.

## Was ausdruecklich nicht dazugehoert

Eine gepruefte Fassung fuer `+=` in Schleifen oder ein eigener Summentyp. T7 nennt
zwei Bausteine und keine Bibliothek; alles darueber hinaus waere Entwurf und braeuchte
einen ADR.
