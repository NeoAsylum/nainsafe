---
id: 0076-riegel-sammeln-notfound-je-quelle
rolle: kernbauer
status: vorschlag
haengt_an: [0066-schlussriegel-liest-nur-eine-eigenschaft]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Der Waechter gegen den Nichtwert haelt an zwei von fuenf Stellen nicht

Aus der Pruefung von Paket 0066 (2026-09-04, Rolle `kern-pruefer`),
`befunde/pruefung-0066-schlussriegel-liest-nur-eine-eigenschaft-2026-09-04.md`.

**Paket 0066 ist erfuellt**, alle drei Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme.

## Der Befund

`fabrik_riegel_sammeln` (`werkzeugkette.cmake:252`) laesst nur durch, was weder leer ist
noch auf `-NOTFOUND` endet:

```cmake
if(NOT "${${listenname}}" STREQUAL "" AND NOT "${${listenname}}" MATCHES "-NOTFOUND$")
```

Der Kommentar darueber begruendet den zweiten Test damit, er fange „das `-NOTFOUND`,
das `get_*_property` fuer eine ungesetzte Eigenschaft liefert". Das stimmt fuer
`get_target_property` und nicht fuer `get_source_file_property`. Gemessen am
2026-09-04 mit CMake 4.2.3 an einem Ziel mit einer Quelle und ohne jede Eigenschaft:

```
-- ziel-COMPILE_FLAGS=[a-NOTFOUND]        get_target_property
-- quelle-COMPILE_FLAGS=[NOTFOUND]        get_source_file_property
-- quelle-COMPILE_OPTIONS=[NOTFOUND]      get_source_file_property
-- ziel-INTERFACE=[e-NOTFOUND]            get_target_property
```

`get_target_property` setzt `<variablenname>-NOTFOUND`, `get_source_file_property`
setzt das blanke `NOTFOUND`. Der Bindestrich im Muster verlangt genau das Zeichen, das
im zweiten Fall fehlt.

Folge, gemessen mit einer instrumentierten Kopie der Datei (eine `message()` vor
`set(pauschal "")`, sonst unveraendert), an einem sauberen Ziel mit einer Quelle:

```
MESS z: eintraege=[…;-fwrapv;-fno-fast-math;NOTFOUND;NOTFOUND]
        herkuenfte=[…;COMPILE_OPTIONS an z;COMPILE_OPTIONS an z]
```

Zwei Scheineintraege je Quelldatei, im Arbeitsbereich also zweimal je
Uebersetzungseinheit.

## Was daraus heute *nicht* folgt

Kein Fehlalarm und keine Luecke. `NOTFOUND` trifft weder `^-w$` noch
`^-Wno-error(=.+)?$`. `eintraege` und `herkuenfte` wachsen im Gleichschritt, die
Paarung ueber den Index bleibt richtig. Alle drei Bedingungen von 0066 sind erfuellt,
und die 22 Wegwerf-Baeume der Pruefung urteilen mit und ohne Behebung gleich.

**Das ist kein Vorschlag gegen einen falschen Bau, sondern gegen einen Waechter, der
nicht waechelt.** Wer das fuer zu wenig haelt, lehnt ihn zu Recht ab.

## Warum es trotzdem ein eigenes Paket ist

Drei Gruende, in der Reihenfolge ihres Gewichts:

1. **Der Kommentar behauptet das Gegenteil des Gemessenen.** Er haengt genau an der
   Zeile, die den Nichtwert fernhalten soll, und erklaert den Fall fuer erledigt. Wer
   die Funktion spaeter anfasst, liest die Begruendung und prueft sie nicht nach --
   ein Kommentar, der einen Randfall abhakt, ist teurer als gar keiner, wenn der
   Randfall der Normalfall ist. Und er *ist* hier der Normalfall: Jede Quelldatei im
   Baum ohne eigene Schalter durchlaeuft ihn.
2. **Der einzige Schutz gegen ein `NOTFOUND` in der Sperrlistenpruefung ist heute die
   Sperrliste selbst.** Sie steht in derselben Funktion (`pauschalmuster`,
   Zeile 308) und wird sich aendern -- Paket 0066 schliesst ihre Erweiterung
   ausdruecklich nur *aus seinem eigenen* Umfang aus, nicht fuer immer. Ein kuenftiges
   Muster, das auf ein blankes Wort passt, erzeugt dann einen Fehlalarm an jeder
   Quelldatei des Baums, und die Ursache steht drei Bildschirmseiten entfernt hinter
   einem Kommentar, der sagt, sie sei ausgeschlossen.
3. **Es gehoert nicht in 0066 nachgetragen.** Das Paket ist gebaut und geprueft; ein
   nachgeschobenes Kriterium entwertet eine bereits erbrachte Abnahme.

Es gehoert auch **nicht** in `0069-t2-linkriegel-in-der-werkzeugkette`, obwohl das auf
`offen` steht und dieselbe Datei beansprucht: Dort geht es um einen Riegel ueber die
Linkzeile, hier um eine Zeile in `fabrik_riegel_sammeln`. Zwei Pakete in einem Auftrag
zu buendeln, weil sie dieselbe Datei anfassen, waere die Aufgabe des Projektmanagers
und nicht meine -- die Serialisierung leistet ohnehin der Baulauf.

## Was zu tun ist

Die Bauform steht frei. Verlangt ist eines:

`fabrik_riegel_sammeln` muss den Nichtwert **beider** Abfragearten erkennen -- das
`<variable>-NOTFOUND` von `get_target_property` und das blanke `NOTFOUND` von
`get_source_file_property`.

Der Kommentar darueber nennt danach beide Formen und sagt, welche Abfrage welche
liefert. Er ist der eigentliche Gegenstand dieses Pakets.

**Was nicht dazugehoert:** die Sperrliste anfassen; weitere Eigenschaften einsammeln;
die Meldung umbauen; den zweiten Zaehler antasten.

**Einmal gebaut, bevor dieser Vorschlag abgegeben wurde.** `MATCHES "^(.*-)?NOTFOUND$"`
statt `MATCHES "-NOTFOUND$"` genuegt: Die Scheineintraege verschwinden, alle 22
Wegwerf-Baeume der Pruefung 0066 melden denselben Code wie ohne die Aenderung, und der
Arbeitsbereich konfiguriert weiter mit Code 0 und `16 uebersetzende Ziele`. Das ist ein
Beleg, dass die Aufgabe loesbar ist, keine Vorgabe -- der Bauagent darf es anders
machen.

## Abnahme

1. **Der Nichtwert kommt nicht mehr durch.** Nachweis: eine Kopie der Datei mit einer
   `message()`, die `eintraege` je Ziel ausgibt, an einem Wegwerf-Baum mit genau einem
   Ziel, einer Quelle und ohne Quelleigenschaften -- die Liste endet auf
   `-fno-fast-math` und enthaelt kein `NOTFOUND`. Daneben, **am Stand vor der
   Aenderung mit derselben Instrumentierung gemessen**, dieselbe Liste mit zwei
   `NOTFOUND` am Ende; ohne diese Gegenprobe belegt die erste Haelfte nur, dass die
   Ausgabe kurz ist.
2. **Kein Urteil aendert sich.** Nachweis: Der Nachbau unter
   `befunde/pruefung-0066/` fuehrt 22 Wegwerf-Baeume; jeder meldet denselben
   Konfigurationscode wie vorher, im Wortlaut die Zeilen mit `gefunden in` und
   `es fehlen` unveraendert. Dazu die drei Bauwege (Arbeitsbereich, `kern` allein,
   `pruefstand` allein) mit Code 0 und den Zahlen 16 / 10 / 5, und `ctest` gruen in
   beiden Profilen.

**Nachweisort:** dieselbe Staffelung wie in 0046, 0058, 0060, 0063 und 0066 -- zuerst
`$TMPDIR` ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116`
sammelt dort keine Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am
2026-09-04 kam ich mit Rang 1 aus.

## Rueckläufe

0.
