# Messung zu Paket 0076 -- der Nichtwert je Abfrageart

Gemessen am 2026-09-05, Rolle `kernbauer`, CMake 4.2.3, g++ unter WSL/Ubuntu.
Bezugsstand fuer jedes Vorher ist `HEAD` = `dffb251`.

Alle Wegwerf-Baeume liegen unter `$TMPDIR` ausserhalb des Repos (Rang 1 der
Nachweisorte). Der Arbeitsbaum hat zu keinem Zeitpunkt ein `build/` bekommen.

Drei Skripte daneben, alle wiederholbar:

| Datei | misst |
|---|---|
| `notfound.py` | Bedingung 1: was in `eintraege` landet, mit Gegenprobe gegen einen Commit |
| `bauwege.py` | Bedingung 2, zweite Haelfte: drei Bauwege mal zwei Profile |
| `haelften.py` | beide Haelften des neuen Musters einzeln stumpf gemacht |

Die 22 Wegwerf-Baeume der Bedingung 2 laufen ueber `befunde/pruefung-0066/nachbau.py`,
unveraendert uebernommen.

## Die Aenderung

In `fabrik_riegel_sammeln` (`werkzeugkette.cmake`) das Muster
`-NOTFOUND$` durch `^(.*-)?NOTFOUND$` ersetzt, die Bedingung auf zwei Zeilen
umgebrochen und der Kommentar darueber ersetzt. Sonst nichts. Die Sperrliste
`pauschalmuster`, die Meldung und der zweite Zaehler sind unberuehrt.

## Bedingung 1 -- der Nichtwert kommt nicht mehr durch

Wegwerf-Baum: ein Ziel `z` (STATIC), eine Quelle `z.cpp`, keine Quelleigenschaft.
Instrumentierung: zwei `message()` unmittelbar vor `set(pauschal "")`, sonst die
Datei unveraendert. Gezaehlt wird nach dem Zerlegen an `;`, nicht per Textsuche.

**Vorher** (`python3 befunde/messung-0076/notfound.py` am Stand vor der Aenderung):

```
-- MESS z: eintraege=[-Wall;...;-fwrapv;-fno-fast-math;NOTFOUND;NOTFOUND]
        19 Eintraege, davon Nichtwert: 2 [NOTFOUND, NOTFOUND]
        letzter Eintrag: NOTFOUND
-- MESS z: herkuenfte=[...;COMPILE_OPTIONS an .../z.cpp;COMPILE_FLAGS an .../z.cpp]

Nichtwerte in `eintraege` insgesamt: 2
```

**Nachher:**

```
-- MESS z: eintraege=[-Wall;...;-fwrapv;-fno-fast-math]
        17 Eintraege, davon Nichtwert: 0 []
        letzter Eintrag: -fno-fast-math
-- MESS z: herkuenfte=[17-mal COMPILE_OPTIONS an z]

Nichtwerte in `eintraege` insgesamt: 0
```

Die Herkunftszeile traegt die Aussage mit: Vorher stammten die beiden letzten
Eintraege aus den **Quelldatei**abfragen, nachher steht in `herkuenfte`
siebzehnmal derselbe Eintrag `COMPILE_OPTIONS an z`. Also sind auch die beiden
Zielabfragen (`COMPILE_FLAGS an z`, `INTERFACE_COMPILE_OPTIONS an z`) weiter
ausgeschlossen -- die Aenderung hat die eine Form nicht gegen die andere getauscht.

### Beide Haelften des Musters einzeln stumpf gemacht

`python3 befunde/messung-0076/haelften.py`, derselbe Baum:

| Muster | Eintraege | Nichtwerte | Herkunft |
|---|---|---|---|
| `^(.*-)?NOTFOUND$` (gebaut) | 17 | keine | -- |
| `^NOTFOUND$` | 19 | `zielflags-NOTFOUND`, `schnittstellenschalter-NOTFOUND` | `COMPILE_FLAGS an z`, `INTERFACE_COMPILE_OPTIONS an z` |
| `-NOTFOUND$` (Stand vor 0076) | 19 | `NOTFOUND`, `NOTFOUND` | beide Quelldateiabfragen |
| `NOTFOUND` (ohne Anker) | 17 | keine | -- |

Die mittleren zwei Zeilen sind der Nachweis, dass keine Haelfte ueberfluessig ist.

**Was die letzte Zeile nicht belegt:** Das unverankerte Muster faengt an diesem Baum
genau so viel wie das gebaute. Die Verankerung ist eine Vorsichtsmassnahme gegen
einen Schalter, der das Wort im Inneren traegt -- so einen gibt es heute nicht, also
unterscheidet ihn keine Messung. Sie steht im Kommentar als Begruendung da und nicht
als Messergebnis.

## Bedingung 2 -- kein Urteil aendert sich

### Die 22 Wegwerf-Baeume

`befunde/pruefung-0066/nachbau.py`, vorher und nachher, Ausgabe Zeile fuer Zeile
verglichen: **47 Zeilen gegen 47 Zeilen, ein einziger Unterschied** -- die
Groessenangabe der eingebundenen Datei in der Kopfzeile (44575 -> 46305 Bytes).
Jeder Konfigurationscode, jede Zeile `gefunden in` und jede Zeile `es fehlen` steht
im Wortlaut unveraendert da; `0 Abweichung(en) vom Soll` in beiden Laeufen.

Die Positivkontrolle `p_positiv` (kein Abschalter, Bau muss rot werden) meldete in
beiden Laeufen `bau code=2` mit `error: conversion from double to int may change
value [-Werror=float-conversion]`. Ohne sie belegte jeder gruene Baum daneben nichts.

Vier der 22 Baeume sind zugleich die Positivkontrolle **fuer diese Aenderung**:
`b1_quellflags`, `b1b_quellopt`, `e8_wnoerrorquelle` und `e10_genexquelle` finden
ihr `-w` an einer Quelldatei und melden weiter Code 1. Das schaerfere Muster hat
also nur den Nichtwert weggenommen, nicht die echten Werte derselben Abfrage.

### Die drei Bauwege, in beiden Profilen

`python3 befunde/messung-0076/bauwege.py vorher|nachher`. Fuer das Vorher wurde die
Datei kurz auf ihren Stand an `dffb251` zurueckgesetzt und danach wiederhergestellt;
die SHA-256 vor und nach dem Zuruecksetzen ist dieselbe (`441355116c42aef2...`).

| Profil | Weg | uebersetzende Ziele | konfig | bau | ctest |
|---|---|---|---|---|---|
| `FABRIK_SANITIZER=ON` | Arbeitsbereich | 18 | 0 | 0 | 14/14 |
| | `kern` allein | 12 | 0 | 0 | 10/10 |
| | `pruefstand` allein | 5 | 0 | 0 | 3/3 |
| `FABRIK_SANITIZER=OFF` | Arbeitsbereich | 16 | 0 | 0 | 14/14 |
| | `kern` allein | 11 | 0 | 0 | 10/10 |
| | `pruefstand` allein | 4 | 0 | 0 | 3/3 |

Diese Tabelle gilt **vorher wie nachher**, Zahl fuer Zahl.

## Wo die Abnahme nicht mehr auf den Baum passt

Bedingung 2 nennt "die Zahlen 16 / 10 / 5". Der Baum liefert sie in keinem der
beiden Profile: `ON` gibt 18 / 12 / 5, `OFF` gibt 16 / 11 / 4. **Das gilt schon am
Stand vor dieser Aenderung** -- nachgemessen, siehe oben. Zwischen der Abnahme und
heute sind dem Baum Ziele zugewachsen, und die eine Zahl der Abnahme kann ohnehin
hoechstens fuer eines der beiden Profile gelten, weil das Testprofil je Baum eigene
Ziele anlegt.

Die Zahlen sind hier deshalb nicht als Sollwert gefuehrt, sondern als das, woran
sich Gleichheit von vorher und nachher zeigt. Die Aussage, die die Bedingung meint
-- "kein Urteil aendert sich" -- ist erfuellt; ihr Wortlaut ist es nicht, und das
aufzuloesen steht dem Pruefer und dem Projektmanager zu, nicht mir.

## Wo die Aenderung liegt, falls jemand sie ueber den Betreff sucht

Ein Fremdlauf hat mitten in diesem Lauf committet und dabei meine Arbeit
mitgenommen: `8d74aff architekt: 0051-t46-gebietspraefix-entscheiden` vom 2026-09-05
02:29 enthaelt `werkzeugkette.cmake` und die drei Skripte dieses Verzeichnisses.
Ueber den Betreff ist die Aenderung also nicht zu finden, ueber `git log -S` schon.

Nach diesem Commit sind Bedingung 1 und die 22 Wegwerf-Baeume ein drittes Mal
gefahren worden, mit demselben Ergebnis -- der Baum hat sich unter der Messung
bewegt, das Ergebnis nicht.
## Was hier nicht gemessen ist

Ob der Riegel nach dieser Aenderung einen Pauschalabschalter faengt, den er vorher
durchgelassen haette. Er faengt keinen zusaetzlichen -- die Aenderung nimmt nur
weg, was nie ein Schalter war. Sie ist gegen einen kuenftigen Fehlalarm gerichtet,
nicht gegen eine heutige Luecke; das steht so schon im Paket.
