---
id: 0103-notfound-endung-verdeckt-schalter
rolle: kernbauer
status: vorschlag
haengt_an: [0076-riegel-sammeln-notfound-je-quelle]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Eine Eigenschaft, die auf `-NOTFOUND` endet, gilt als leer -- auch wenn ein `-w` darin steht

Aus der Pruefung von Paket 0076 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0076-riegel-sammeln-notfound-je-quelle-2026-09-05.md`, Befund 1 und 2.

**Paket 0076 ist erfuellt**, beide Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme und ist **aelter** als es -- gemessen verhaelt sich der Stand
davor zeichengleich.

## Der Befund, zwei Wirkungen einer Ursache

CMakes Wahrheitsregel und die Frage dieses Riegels sind nicht dieselbe Frage. Fuer
CMake ist jede Zeichenkette auf `-NOTFOUND` falsch, und zwar die **ganze** Zeichenkette
-- auch wenn sie eine Liste ist, deren letzter Eintrag zufaellig so endet. Der Riegel
will aber nicht wissen, ob CMake den Wert wahr nennt, sondern ob die Eigenschaft
Schalter traegt.

**Erste Wirkung, still.** `fabrik_riegel_sammeln` (Zeile 282/283) verwirft die ganze
Eigenschaft. Gemessen am 2026-09-05 mit CMake 4.2.3 an `HEAD`, Wegwerf-Baum mit
`int f(double d){ int i = d; return i; }`:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
```

Konfiguration **Code 0**, Riegel meldet `alle mit Warnsatz und ohne
Pauschalabschalter`, Bau **Code 0**, **null Diagnosen**, `-w` steht auf der
Uebersetzerzeile. Dieselbe Zeile ohne die Endung (`"-w -DPFAD=x"`) bricht ab: Code 1,
`hebt den Satz wieder auf: -w`. Dieselbe Quelle ohne `-w` baut rot -- die
Positivkontrolle steht.

**Zweite Wirkung, laut.** Zeile 409-412, `if(NOT schalter)`, dieselbe Wahrheitsregel:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)
```

Konfiguration Code 1 mit `es fehlen: -Wall -Wextra -Werror ... -fno-fast-math` -- alle
17 Schalter angeblich fort, obwohl `fabrik_warnsatz_anlegen(z)` sie eine Zeile vorher
angelegt hat. Mit `-DPFAD=x` konfiguriert derselbe Baum Code 0.

## Warum das jetzt ein Paket ist und nicht seit Wochen eines war

**Weil der Kommentar seit dem 2026-09-05 das Gegenteil behauptet.** Er steht direkt
ueber der Bedingung und sagt:

> Verankert an **beiden** Enden, weil der Nichtwert immer der ganze Wert ist: Eine
> gesetzte Eigenschaft, deren letzter Listeneintrag zufaellig so hiesse, traegt einen
> Schalter und ist keine leere Menge.

Der Anker am Anfang leistet das nicht: `(.*-)?` darf alles davor schlucken, das
Semikolon einer CMake-Liste eingeschlossen. Damit ist genau der Fall, den der Satz fuer
ausgeschlossen erklaert, der Fall aus der Messung oben. Das ist wortwoertlich die
Fehlerklasse, gegen die Paket 0076 geschrieben wurde -- ein Kommentar, der einen
Randfall abhakt, ist teurer als gar keiner. Ohne diesen Satz waere der Befund eine
Fussnote; mit ihm wird der naechste, der die Zeile anfasst, nicht mehr nachsehen.

**Und weil der Riegel es nicht selbst zeigt.** Seine Meldung nennt die Zahl der Ziele,
nicht die Zahl der gesammelten oder verworfenen Eintraege. Beide Nachweise zu 0076 --
der des Bauagenten und der der Pruefung -- brauchten dafuer eine eingeschobene
`message()`. Solange das so ist, faellt ein stumpf gewordener Riegel an keiner Zahl auf.

**Nicht in 0076 nachtragen:** Das Paket ist gebaut und geprueft; ein nachgeschobenes
Kriterium entwertet eine erbrachte Abnahme. Und nicht in 0104: Dort geht es um die
Zielzahlen in Meldung und Kommentar, hier um eine Bedingung. Die Dateilisten schneiden
sich -- das serialisiert der Projektmanager.

## Was zu tun ist

Die Bauform steht frei. Verlangt ist:

1. Ein Wert, der **nur** aus dem Nichtwert besteht, gilt weiter als leere Menge.
2. Ein Wert, der **ausser** dem Nichtwert noch etwas traegt, wird nicht mehr
   weggeworfen. Der naheliegende Weg ist, je Listeneintrag statt ueber die
   zusammengefuegte Zeichenkette zu entscheiden -- die Schleife darunter laeuft ohnehin
   ueber die Eintraege. Ob Zeile 409-412 dieselbe Behandlung bekommt oder ihre
   Sonderbehandlung ganz verliert, entscheidet der Bauagent.
3. Der Kommentar sagt danach, was gemessen ist, und nicht, was der Anker leisten
   soll. Der Satz ueber den letzten Listeneintrag faellt oder wird richtig.

**Was nicht dazugehoert:** die Sperrliste anfassen; weitere Eigenschaften einsammeln;
die Meldung um einen Zaehler erweitern (das waere ein eigenes Paket, und 0076 hat es
ausdruecklich ausgeschlossen); die zwei `-NOTFOUND$`-Tests der
Nullabhaengigkeitspruefung in Zeile 661 und 682 aendern -- die lesen nur
`get_target_property` und sind dort richtig.

**Nicht vorgebaut.** Ich habe den Fehler erzeugt, nicht die Behebung; die zwei
Wegwerf-Baeume oben sind der Nachweis, dass er erreichbar ist.

## Abnahme

1. **Der getarnte Schalter wird gefangen.** Nachweis: der erste Wegwerf-Baum oben,
   unveraendert. Konfiguration bricht mit Code 1 ab und nennt in `gefunden in` die
   Eigenschaft `COMPILE_FLAGS an .../z.cpp` und das Wort `-w`. Daneben, am Stand vor
   der Aenderung mit demselben Baum gemessen, Code 0 und die Meldung `alle mit
   Warnsatz und ohne Pauschalabschalter` -- ohne diese Gegenprobe belegt die erste
   Haelfte nur, dass irgendetwas rot ist.
2. **Kein Fehlalarm mehr am Ziel, und keiner neu.** Nachweis: der zweite Wegwerf-Baum
   oben konfiguriert mit Code 0. Dazu ein Baum mit
   `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)`, der mit Code 1 und
   `gefunden in: COMPILE_OPTIONS an z` abbricht -- der Riegel darf die Endung nicht
   dadurch entschaerfen, dass er sie ganz ignoriert.
3. **Kein Urteil aendert sich.** Nachweis: `befunde/pruefung-0066/nachbau.py` fuehrt
   22 Wegwerf-Baeume; jeder meldet denselben Konfigurationscode wie vorher, im Wortlaut
   die Zeilen `gefunden in` und `es fehlen` unveraendert, und `0 Abweichung(en) vom
   Soll`. Dazu die drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein) in
   **beiden** Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl der
   uebersetzenden Ziele wird je Profil **gegen den eigenen Stand davor** verglichen und
   nicht gegen einen festen Sollwert (Begruendung in 0104).

**Nachweisort:** dieselbe Staffelung wie in 0066 und 0076 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort
keine Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am 2026-09-05
kam ich mit Rang 1 aus.

## Rueckläufe

0.
