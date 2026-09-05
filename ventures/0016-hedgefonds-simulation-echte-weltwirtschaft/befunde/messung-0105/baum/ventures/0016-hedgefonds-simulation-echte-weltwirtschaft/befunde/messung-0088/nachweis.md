# Messung zu Paket 0088 -- die vier unbelegten Vorgaben

Datum: 2026-09-05. Rolle: testentwickler. Geaenderte Datei: genau eine,
`kern/test/werte_probe.cpp`.

**Vorher-Stand.** `HEAD` beim Beginn dieses Laufs: `dd94ab9`. `kern/src/werte.cpp` steht
darin auf `ceebee3` (`kernbauer: 0002`) -- also genau auf dem Bezugsstand, den das
Arbeitspaket fuer seine Zeilennummern nennt. Nachgemessen mit
`git log -1 -- kern/src/werte.cpp`, nichts zu tun.

## Wie der Rotnachweis gefahren wurde, ohne eine fremde Datei anzufassen

Das Arbeitspaket verbietet jede bleibende Aenderung an `kern/src/werte.cpp`; die vier
Mutationen muessen aber genau dort sitzen. Beides zusammen geht, wenn der mutierte
Quelltext **nie auf die Platte kommt**: `python3 -c` liest die Datei, ersetzt die eine
Stelle im Speicher und schreibt das Ergebnis auf die Standardausgabe, und `c++ -x c++ -`
uebersetzt aus der Pipe.

```
python3 -c "<ersetzung>" | c++ -x c++ - -c -o $TMPDIR/w_mutN.o <Warnsatz> \
    -fsanitize=undefined,address -fno-sanitize-recover=all
c++ ... -o bau/kern/werte_probe $TMPDIR/w_mutN.o \
    bau/kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o bau/kern/libkern_geprueft.a
ctest --test-dir bau -R werte_probe --output-on-failure
```

Jede Ersetzung traegt ein `assert s.count(a) == 1` -- eine Mutation, die zwei Stellen
oder keine getroffen haette, waere ein Abbruch statt einer stillen Fehlmessung.

Uebersetzt wurde mit dem Warnsatz des Testprofils aus `flags.make`, also
`-std=c++20 -fwrapv -fno-fast-math -Werror -Wconversion -Wsign-conversion` und den
uebrigen Schaltern, dazu `-fsanitize=undefined,address -fno-sanitize-recover=all`.
Keine der vier Uebersetzungen gab eine Warnung.

**Nachweis, dass nichts haengengeblieben ist:** `git status --short` fuehrt
`kern/src/werte.cpp` nicht. Modifiziert sind allein `kern/test/werte_probe.cpp` (dieses
Paket) sowie `kern/test/schritt_probe.cpp` und
`werkzeuge/belegstellen/belegstellen_riegel.cpp` -- beide aus parallel laufenden
Paketen, beide nicht von mir angefasst.

## Die gruene Seite -- unveraendertes Modul

```
    Start 7: werte_probe
1/1 Test #7: werte_probe ......................   Passed    0.01 sec
100% tests passed, 0 tests failed out of 1
```

Und der ganze Kern, nachdem der echte Binaerstand wiederhergestellt war:

```
13/13 Test #13: vorrat_verfahren_probe ...........   Passed    0.01 sec
100% tests passed, 0 tests failed out of 13
```

## Die rote Seite -- je Vorgabe einzeln

### 1. Skalengrenze am aeussersten Aufruf (T47, T50)

Mutation: `mal_geteilt(korb, anteil, 10'000)` → `mal_geteilt(tsd_in_cent(korb), anteil,
10'000)`, dazu `return tsd_in_cent(nach_abschlag);` → `return nach_abschlag;`.

```
FEHLGESCHLAGEN Zeile 693: beteiligung_wert(z, K_GRUND, Gebiet::US, Sektor::Industrie) == 100'000
FEHLGESCHLAGEN Zeile 698: beteiligung_wert(z, K_GRUND, Gebiet::US, Sektor::Industrie) != 99'990
FEHLGESCHLAGEN Zeile 708: beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie) == 100'000
FEHLGESCHLAGEN Zeile 716: beteiligung_wert(z, mit_abschlag, Gebiet::US, Sektor::Industrie) != 66'663
4 Pruefung(en) fehlgeschlagen
```

Die Zeile mit `!= 99'990` schlaegt fehl -- der Mutant liefert also **genau** die Zahl,
die das Arbeitspaket von Hand vorgerechnet hat (Korb 3, Anteil 3.333, Abschlag 0).

**Eine Zutat ueber das Arbeitspaket hinaus.** Die dort genannte Mutation zieht die
Umrechnung ganz nach innen. Es gibt aber eine **zweite** Fehlstelle derselben Art: die
Umrechnung zwischen Korbanteil und Abschlag. Mit `ausstiegsabschlag = 0` ist sie von der
richtigen Form nicht zu unterscheiden, weil der Abschlag dann mit 10.000/10.000
multipliziert. Der zweite Block der Pruefung setzt den Abschlag deshalb auf 3.333 und
schreibt beide Gegenzahlen aus:

| Form | Rechnung | Ergebnis |
|---|---|---|
| verbindlich (T47) | `runde(3·3333/10^4)=1`, `runde(1·6667/10^4)=1`, `·10^5` | **100.000** |
| Umrechnung ganz innen | `runde(300000·3333/10^4)=99990`, `runde(99990·6667/10^4)` | 66.663 |
| Umrechnung in der Mitte | `runde(3·3333/10^4)=1`, `·10^5=100000`, `runde(100000·6667/10^4)` | 66.670 |

Die dritte Zeile ist der Fall, den das Arbeitspaket nicht nennt; ohne den Abschlag waere
er weiterhin unbelegt geblieben.

### 2. Vorzeichen der Stufenzahl im Positionswert (T48 Nr. 15)

Mutation: `mal(stufen, je_stufe)` → `mal(betrag(stufen), je_stufe)`.

```
FEHLGESCHLAGEN Zeile 756: positionswert(z, konst, platz) == -10'000'000'000
FEHLGESCHLAGEN Zeile 759: positionswert(z, konst, platz) != 10'000'000'000
FEHLGESCHLAGEN Zeile 772: fondsvermoegen(z, konst) == -10'000'000'000
FEHLGESCHLAGEN Zeile 773: fondsvermoegen(z, konst) < 0
4 Pruefung(en) fehlgeschlagen
```

Kapitalstock 1.000.000, `stufenweite` 250, `stufen = -4` -- dieselbe Belegung und
dieselben zwei Messwerte (`stufenwert=25000`, `positionswert=∓10^10`), die der
`kern-pruefer` gemessen hat. Bestaetigt.

Zeile 773 ist die Zeile, auf die es sachlich ankommt: Kasse und Hebelstand sind null und
jeder Beteiligungsanteil ebenfalls, das Fondsvermoegen ist also genau dieser eine
Positionswert. Unter der Mutation ist es **positiv**, und Todesart 1
(`fondsvermoegen <= 0`) greift bei einem Fonds, der sich mit Shorts ruiniert, nie.

### 3. Der Marktkorb enthaelt keine Waehrungen (T33 Punkt 1, T48 Nr. 7)

Mutation: in `marktkorb` je Land zusaetzlich `waehrungswert` aufaddieren.

```
FEHLGESCHLAGEN Zeile 820: marktkorb(z, z, K_GRUND) == 2'000'700
FEHLGESCHLAGEN Zeile 823: marktkorb(z, z, K_GRUND) != 3'800'700
2 Pruefung(en) fehlgeschlagen
```

Belegung: ein Korb (US/Landwirtschaft) mit 700, eine Anleihe (DE, Wertschoepfung
2.000.000 bei 10.000 Basispunkten Schuldenquote) mit 2.000.000, dazu ein Handelsstrom
CN→DE von 900.000, der zwei der vier Waehrungen auf je 900.000 hebt. Verbindlich sind
2.000.700; der Mutant liefert 3.800.700, also die vorhergesagten 1.800.000 zu viel --
belegt dadurch, dass gerade die `!=`-Zeile fehlschlaegt.

`probe_marktkorb_zwei_quellen` blieb dabei gruen, genau wie im Vorschlag beschrieben.

### 4. Der Waehrungswert nimmt den festen Kurs 10.000 (T48 Nr. 4)

Mutation: statt des Literals `10'000` den Wechselkurs des Gebiets als Kurs einsetzen.

```
FEHLGESCHLAGEN Zeile 860: waehrungswert(z, Gebiet::US) == 1'200'000
FEHLGESCHLAGEN Zeile 861: waehrungswert(z, Gebiet::CN) == 300'000
FEHLGESCHLAGEN Zeile 866: waehrungswert(z, Gebiet::US) != 600'000
FEHLGESCHLAGEN Zeile 867: waehrungswert(z, Gebiet::CN) != 600'000
4 Pruefung(en) fehlgeschlagen
```

Beide Gebiete tragen dasselbe Handelsvolumen 600.000 und unterscheiden sich allein im
Wechselkurs (US 5.000, CN 20.000). Verbindlich sind 1.200.000 und 300.000; unter der
Mutation kuerzt sich der Wechselkurs weg und **beide** stehen auf 600.000 -- zwei
Waehrungen, die sich um den Faktor vier unterscheiden, mit derselben Zahl. Dass beide
`!=`-Zeilen fehlschlagen, ist der Beleg dafuer.

Die Zeilen zu Deutschland (Wechselkurs auf dem Startwert 10.000, Waehrungswert gleich
dem Handelsvolumen 400.000) blieben **gruen** -- sie stehen in der Probe als Erklaerung
dafuer, warum die Grundbelegung diese Verletzung prinzipiell nicht sehen kann.

## Was dabei nebenbei sichtbar wurde

Unter keiner der vier Mutationen wurde eine **vorhandene** Pruefung rot -- nur die je
neue. Das ist die unabhaengige Bestaetigung der Ausgangsbehauptung des `kern-pruefers`:
Die vier Vorgaben waren bis zu diesem Paket tatsaechlich unbelegt, und zwar alle vier.

## Womit ich nicht fertig geworden bin

Der Baulauf ueber den ganzen Baum bricht derzeit in
`werkzeuge/belegstellen/belegstellen_riegel.cpp` ab (Argumenttyp bei `pruefe_zitate`,
vierter Parameter). Die Datei ist nicht meine und war im Uebersetzungsbericht desselben
Tages noch gruen -- sie wird also gerade von einem parallelen Lauf umgebaut. Gemeldet,
nicht angefasst. Die dreizehn Kernproben bauen und laufen davon unberuehrt.
