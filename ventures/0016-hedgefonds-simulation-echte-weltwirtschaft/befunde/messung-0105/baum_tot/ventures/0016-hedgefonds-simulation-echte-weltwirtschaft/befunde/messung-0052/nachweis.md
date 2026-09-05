# Nachweis zu Paket 0052 -- `mal(a, b)` mit Waechter

Gemessen am 2026-09-04 vom Kernbauer. Jede Zahl unten stammt aus einem der Laeufe in
diesem Dokument, keine aus einer Nebenrechnung.

## Die benannten Wertepaare

| Fall | a | b | Produkt | Verhalten von `mal` |
|---|---|---|---|---|
| passt | 3.037.000.499 | 3.037.000.499 | 9.223.372.030.926.249.001 | kehrt zurueck, positiv |
| passt | -3.037.000.499 | 3.037.000.499 | -9.223.372.030.926.249.001 | kehrt zurueck, negativ |
| bricht ab | 3.037.000.500 | 3.037.000.500 | 9.223.372.037.000.250.000 | `std::domain_error` |
| bricht ab | -3.037.000.500 | 3.037.000.500 | -9.223.372.037.000.250.000 | `std::domain_error` |

`I64_MAX` ist 9.223.372.036.854.775.807. Das erste Produkt liegt 5.928.526.806
darunter, das dritte 145.474.193 darueber. Zwischen den beiden Faktoren, die um genau
einen Schritt auseinanderliegen, verlaeuft also die Grenze.

Keiner der beiden Faktoren steht als Literal in den neuen Konstanten: `MAL_FAKTOR_PASST` entsteht in
`kern/test/festkomma_probe.cpp` als `wurzel(I64_MAX, 2)`, `MAL_FAKTOR_BRICHT_AB` als
dessen Nachfolger, `MAL_PRODUKT_PASST` ueber `mal_geteilt` mit Nenner 1 -- also ueber
den zweiten, unabhaengig festgenagelten Weg derselben Rechnung.

## Lauf 1 -- der Kern in der Konfiguration des Runners

Dieselben drei Aufrufe wie `baulauf.py:162` (`RelWithDebInfo`, `-fwrapv`
`-fno-fast-math`), Bauverzeichnis `befunde/messung-0052/bau`:

```
-- Warnsatz-Schlussriegel: 10 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
[100%] Built target festkomma_probe
1/8 Test #1: festkomma_probe ..................   Passed    0.01 sec
100% tests passed, 0 tests failed out of 8
```

Keine Warnung, kein Hinweis. Die drei `static_assert` zu `mal` sind damit schon beim
Uebersetzen erfuellt; sie treffen den Fall, der passt.

## Lauf 2 -- die Gegenprobe mit Positivkontrolle

Ein gruener Test belegt noch nicht, dass er den Waechter misst. Deshalb ein zweiter
Baum unter `befunde/messung-0052/gegenprobe/`: derselbe Kern, in dem allein die
Rueckkehr von `mal` durch eine ungeprueft verengende ersetzt ist. Die Zeile traegt
dort den Vermerk GEGENPROBE. Der Rest ist bytegleich.

```
1/1 Test #1: festkomma_probe ..................***Failed    0.02 sec
KEIN ABBRUCH Zeile 185: mal(undurchsichtig(MAL_FAKTOR_BRICHT_AB), undurchsichtig(MAL_FAKTOR_BRICHT_AB))
KEIN ABBRUCH Zeile 187: mal(undurchsichtig(-MAL_FAKTOR_BRICHT_AB), undurchsichtig(MAL_FAKTOR_BRICHT_AB))
KEIN ABBRUCH Zeile 189: mal(undurchsichtig(I64_MIN), undurchsichtig(-1))
kern::festkomma -- 3 Probe(n) fehlgeschlagen.
```

Drei Meldungen, und zwar genau die drei Abbruchfaelle von `mal` -- jede uebrige
Pruefung derselben Datei bleibt gruen, und der Bau bleibt warnungsfrei. Damit ist
gemessen statt behauptet, dass die Probe den Waechter prueft und nicht sich selbst.

Der entfernte Waechter faellt uebrigens **nicht** beim Uebersetzen auf: Die drei
`static_assert` treffen den Fall, der passt, und der bleibt richtig. Ein Waechter ist
nur an seinem Nein-Fall pruefbar.

## Die drei Abnahmebedingungen

1. `grep -n "i64 mal(" kern/include/kern/festkomma.hpp` findet eine Zeile, Zeile 200;
   die Funktion kehrt ueber `intern::nach_i64` zurueck. Die Massnahme 4.3 steht im
   Kommentar darueber im Wortlaut, mit der Anforderungsnummer T7 und ohne Zeilenangabe.
2. Beide Wertepaare stehen in der Tabelle oben und als benannte Groessen im Quelltext.
   Der Abbruchfall ist in Lauf 2 mit Positivkontrolle gemessen.
3. `festkomma_probe` steht in Lauf 1 namentlich als `Passed`; den Bericht des Tages
   erzeugt der Runner.

## Was offen bleibt

`mal` hat heute keinen Aufrufer, und das Paket verbietet ausdruecklich, einen zu
bauen. Der Nachweis, dass die Vorgabe **flaechendeckend** eingehalten wird -- die
Zuordnung aller Treffer von `grep -rn` auf die vier zugelassenen Rechenarten aus T7 --
gehoert deshalb zu dem Paket, das `kern::werte` baut, nicht zu diesem.

Der Baum unter `gegenprobe/` enthaelt eine absichtlich beschaedigte Fassung von `mal`.
Er liegt unter `befunde/`, das `baulauf.py:116` von der Manifestsuche ausschliesst, und
die Zeile traegt den Vermerk GEGENPROBE. Wer dort je aufraeumt, sollte es wissen.
