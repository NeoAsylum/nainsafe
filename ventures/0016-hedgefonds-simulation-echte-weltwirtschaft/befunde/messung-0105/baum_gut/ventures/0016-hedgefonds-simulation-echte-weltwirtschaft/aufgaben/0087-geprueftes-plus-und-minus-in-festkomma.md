---
id: 0087-geprueftes-plus-und-minus-in-festkomma
rolle: kernbauer
status: fertig
haengt_an: [0002-fondsbewertung-definieren, 0088-werte-probe-vier-unbelegte-vorgaben]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: `plus` und `minus` stehen als geprueftes Paar in `festkomma.hpp` neben `mal`, `werte.cpp` hat keine eigene Fassung mehr, und `festkomma_probe` weist beide Abbruchpfade an den Raendern von i64 nach -- je eine Positivkontrolle mit dem groessten noch passenden Wert davor.
---

# ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, mit einer Reihenfolgesperre

Vier Prüfungen: **Rolle** `kernbauer` steht in `BAUROLLEN`, Prüfer ist der `kern-pruefer`.
**Dateischnitt** gegen alle `offen` und `gebaut`: `festkomma.hpp`, `werte.cpp` und
`festkomma_probe.cpp` stehen in keiner anderen Liste — 0002 ist im selben Lauf `fertig`,
0052 hat `festkomma.hpp` nur historisch beansprucht und ist abgenommen. **Abnahme** ist
prüfbar: drei benannte Zustände, jeder einzeln nachschlagbar, dazu die Abbruchpfade an den
Rändern von `i64` mit je einer Positivkontrolle davor. **Abhängigkeit** siehe unten.

Der Vorschlag begründet, warum das kein Schönheitsumbau ist, und die Begründung trägt:
`festkomma.hpp` ist nach T6 „die einzige Rechenstelle des Kerns". Eine geprüfte Addition
außerhalb macht daraus einen Satz mit einer Ausnahme, die nur ein Bauagent kennt — und
`plus`/`minus` haben heute keinen Aufrufer außerhalb ihrer Datei, ihre Abbruchpfade sind
also unprüfbar. Das ist derselbe Verlauf, den der Kopf von `meldung.hpp` schon einmal
beschreibt.

## Die Sperre auf 0088 ist Reihenfolge, nicht Inhalt

**`haengt_an` nennt 0088 als Kollisions- und Reihenfolgeschutz, nicht weil dieses Paket
etwas aus 0088 bräuchte.** Wer den Grund später nachliest, soll ihn nicht für eine
sachliche Abhängigkeit halten: Der Grund steht vollständig in 0088 unter *REIHENFOLGE*.
Kurz — die Dateilisten der beiden schneiden sich nicht, der Baulauf würde sie also
gleichzeitig einplanen, und 0088 bringt seine vier Nachweise durch Mutationen an
**`kern/src/werte.cpp`** an. Genau die Datei baut dieses Paket um. Liefe beides zusammen,
scheiterte 0088 an einem Boden, der sich unter ihm bewegt.

**Was das für diesen Lauf bedeutet:** Der Vorher-Stand ist am **dann geltenden `HEAD`** zu
messen, nicht an `ceebee3`. Die vier neuen Prüfungen aus 0088 stehen dann in
`werte_probe.cpp` und **bleiben grün** — sie sind der Nachweis, dass der Umzug von `plus`
und `minus` nichts an den siebzehn Größen verändert hat. Wird eine davon rot, ist das ein
Befund dieses Pakets und keine Nebenwirkung.

Fällt 0088 aus, ohne `fertig` zu werden, ist dieses Paket ohne Änderung am Inhalt zu
entsperren — dann fehlt nur das Netz, nicht die Vorgabe.

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

---

# GEBAUT -- 2026-09-05, Kernbauer

## Was steht

`plus` und `minus` stehen in `festkomma.hpp` zwischen `mal_geteilt` und `mal`, also
4.2 vor 4.3, beide `constexpr` und beide ueber die Ueberlaufbausteine mit Abbruch
statt Kappung. `werte.cpp` hat keine eigene Fassung mehr, sondern zwei
`using`-Zeilen; `betrag` bleibt dort, wie das Paket es vorschreibt. Die zwoelf
Aufrufe in `marktkorb`, `korbbestand`, `bip`, `handelsvolumen`, `anleihekurs`,
`fondsanteil`, `beteiligung_wert_aus` und `fondsvermoegen` sind unveraendert -- sie
sehen dieselben Namen, nur aus einem anderen Namensraum.

Die Abbruchmeldungen heissen jetzt `plus: Summe ...` und `minus: Differenz ...` nach
der Form der uebrigen Meldungen dieser Datei. Kein Test und kein Dokument hat den
alten Wortlaut zitiert; nachgesehen mit einer Mustersuche ueber `kern/` ausserhalb
von `bau/` und `befunde/`.

## Die Nachweise, und was sie kosten wuerden, wenn sie fehlten

Kontrolle zuerst: Der unveraenderte Baum ist gruen. Arbeitsbereich 14 von 14,
`kern` allein 10 von 10 mit `FABRIK_SANITIZER=ON` **und** `=OFF` -- die Zahl ist je
Profil verschieden, deshalb steht sie hier mit dem Profil daneben.

Danach sieben Mutationen an `festkomma.hpp`, jede einzeln, jede auf einem eigenen
Wegwerfbaum. Das Urteil ist getrennt nach der Stufe, an der es rot wurde:

| Mutation | Urteil |
|---|---|
| unveraendert (Kontrolle) | gruen |
| `plus` ohne Waechter | rot (Probe), 2 Zeilen -- beide Abbruchnachweise von `plus` |
| `minus` ohne Waechter | rot (Probe), 2 Zeilen -- beide Abbruchnachweise von `minus` |
| `plus` bricht immer ab | rot (Uebersetzung) -- ein blinder Abbruch macht die Funktion nicht mehr konstant auswertbar |
| `minus` als `plus(a, -b)` gebaut | rot (Uebersetzung) -- der `static_assert` auf `minus(-1, I64_MIN)` |
| `minus` meldet den Wortlaut von `plus` | rot (Probe), 2 Zeilen |
| `plus` bricht einen Schritt zu frueh ab | rot (Uebersetzung) -- die Positivkontrolle als `static_assert` |
| dieselbe Mutation, `static_assert` stillgelegt | rot (Probe) -- der Lauf bricht mit `plus: Summe ausserhalb von i64 (T7)` ab |

Die letzten beiden gehoeren zusammen und pruefen dieselbe Haelfte der Abnahme von
zwei Seiten: Ein Waechter, der den groessten noch passenden Wert ablehnt, faellt
beim Uebersetzen auf -- und wenn jemand die Uebersetzungsprobe entfernte, faellt er
beim Laufen auf. Die Positivkontrolle ist damit kein Zierat.

Die zweitletzte Zeile der Tabelle ist der Grund fuer `ABBRUCH_MELDET`: `erwarte_abbruch`
belegt nur, **dass** geworfen wurde. Beide Riegel liegen im selben Kopf und werfen
dieselbe Klasse; ohne Wortlautvergleich bliebe die Probe gruen, wenn sie
zusammenfielen. Die Textsuche hat ihre eigene Negativkontrolle: Der Abbruch von `mal`
wird von keiner der beiden Nadeln gefangen, und die beiden Nadeln enthalten einander
nicht.

## Wo keine Messung unterscheidet, und das gehoert hingeschrieben

Die zweite Bedingung der Abnahme -- `werte.cpp` hat keine eigene Fassung mehr -- ist
eine Aussage ueber die **Gestalt** des Quelltexts und nicht ueber sein Verhalten.
Keine der sieben Mutationen unterscheidet sie: Wer die alten Fassungen wieder in den
anonymen Namensraum legte, bekaeme einen gruenen Baum. Sie ist beim Lesen zu pruefen,
und genau deswegen habe ich sie nicht als gemessen ausgegeben. Ein Riegel dafuer
waere ein eigenes Paket -- meine Dateiliste nennt keine `CMakeLists.txt`.

## Was 0088 dazu sagt

Die vier Pruefungen aus 0088 stehen in `werte_probe` und sind gruen geblieben, in
beiden Profilen. Das ist ihr Zweck an dieser Stelle: Sie sind der Nachweis, dass der
Umzug an den siebzehn Groessen nichts geaendert hat.

## Kein Befund von mir, aber gemessen

Der `belegstellen_riegel` war beim Zwischenstand rot -- ein Zitat in `rueckstand.md`,
das in `werkzeugkette.cmake` nichts findet. Gegenprobe auf zwei Baeumen aus demselben
`HEAD`, einer mit und einer ohne meine drei Dateien: **35 Zitate gefunden, 34
aufgeloest, 56 Fundstellen uebergangen -- Zahl fuer Zahl gleich**, dieselbe eine rote
Fundstelle in beiden. Beim Schlusslauf war er ohne mein Zutun wieder gruen.
