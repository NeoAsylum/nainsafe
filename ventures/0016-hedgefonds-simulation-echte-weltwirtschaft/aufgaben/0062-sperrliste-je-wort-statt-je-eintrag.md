---
id: 0062-sperrliste-je-wort-statt-je-eintrag
rolle: kernbauer
status: vorschlag
haengt_an: [0060-schlussriegel-blinde-flecken]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Die Sperrliste prueft ganze Eintraege, der Uebersetzer liest Woerter

Aus der Pruefung von Paket 0060 (2026-09-04, Rolle `kern-pruefer`), Befund 1 in
`befunde/pruefung-0060-schlussriegel-blinde-flecken-2026-09-04.md`.

**Paket 0060 ist erfuellt**, alle drei Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme.

## Der Befund

`fabrik_schlussriegel` haelt jeden Eintrag von `COMPILE_OPTIONS` als ganze Zeichenkette
gegen `^-w$` und `^-Wno-error(=.+)?$`. Ein Eintrag ist aber nicht notwendig ein Schalter:

```
target_compile_options(z PRIVATE "SHELL:-Wno-error -w")
   Riegel:  CODE=0, "1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne
            Pauschalabschalter."
   Bau:     CODE=0, keine einzige Diagnose
```

Gemessen am 2026-09-04 an derselben Quelle wie Befund 3 von 0060,
`int f(double d){ int i = d; return i; }`. `SHELL:` ist CMakes dokumentierter Weg, mehrere
Schalter in **einem** Eintrag zu uebergeben; der Uebersetzer bekommt beide, der Riegel
sieht einen Eintrag, der auf `S` beginnt. Dasselbe gilt fuer den Generatorausdruck --
`$<1:-w>` und `$<$<CONFIG:Release>:-w>`, beide gemessen, beide gruen bei stiller
Uebersetzung.

Der Generatorausdruck steht in 0060 unter "Nicht abgedeckt" und ist damit eine bekannte
Grenze; `SHELL:` steht dort nicht. Beide haben dieselbe Ursache, und die ist eine Zeile
weit weg: **Der Riegel haelt den Eintrag schon in der Hand.** Die zwei anderen bekannten
Luecken -- ein Abschalter aus `CMAKE_CXX_FLAGS` von aussen und einer aus der Kommandozeile
-- stehen woanders und gehoeren nicht hierher.

## Warum das ein eigenes Paket ist

Es aendert dieselbe Funktion wie 0060, das gerade `fertig` wird, und liegt ausserhalb aller
drei Abnahmebedingungen von 0060: Bedingung 3 nennt den Nachweis woertlich mit
`target_compile_options(z PRIVATE -Wno-error -w)`, und der ist erbracht. Ein Bauagent, der
`SHELL:` nebenbei mitgenommen haette, waere aus seiner Abnahme herausgelaufen.

Es gehoert auch nicht in 0060 nachgetragen: Das Paket ist gebaut und geprueft, und ein
nachgeschobenes Kriterium entwertet eine bereits erbrachte Abnahme.

## Was zu tun ist

Die Bauform steht frei. Ein Weg, den ich am 2026-09-04 gebaut und gemessen habe -- fuenf
Zeilen, nur im zweiten Durchgang, der erste (`luecke`) bleibt unberuehrt: vor dem Abgleich
jeden Eintrag in Woerter zerlegen, `SHELL:` und die Zeichen `$ < > : ,` als Trenner, dann
je Wort gegen die unveraenderte Sperrliste.

```cmake
foreach(schalterwert IN LISTS schalter)
  string(REPLACE "SHELL:" " " wert "${schalterwert}")
  string(REGEX REPLACE "[$<>:,]" " " wert "${wert}")
  separate_arguments(worte UNIX_COMMAND "${wert}")
  foreach(wort IN LISTS worte)
    ...  # Sperrliste wie bisher, gegen ${wort} statt gegen ${schalterwert}
```

Gemessen mit dieser Fassung:

```
SHELL:-Wno-error -w          -> CODE=1, "hebt den Satz wieder auf: -Wno-error -w"
$<1:-w>                      -> CODE=1, "hebt den Satz wieder auf: -w"
$<$<CONFIG:Release>:-w>      -> CODE=1, "hebt den Satz wieder auf: -w"
-Wno-error -w (wie in 0060)  -> CODE=1, unveraendert
-Wno-conversion              -> CODE=0, unveraendert
Arbeitsbereich / kern / pruefstand  -> CODE=0, 15 / 10 / 5, unveraendert
```

Die letzte Zeile ist der eigentliche Punkt: Zerlegen erzeugt mehr Woerter und damit mehr
Gelegenheit zum Falschalarm. `-Wall`, `-Wno-conversion`, `-fsanitize=undefined,address`
und `-fno-sanitize-recover=all` erzeugen kein Wort, das `^-w$` oder `^-Wno-error(=.+)?$`
trifft.

**Was nicht dazugehoert:** die Sperrliste um weitere Schalter erweitern, `CMAKE_CXX_FLAGS`
oder die Kommandozeile in die Pruefung ziehen, den ersten Durchgang (`luecke`) auf
Generatorausdruecke ausdehnen -- der ist eine andere Frage und hat andere Falschalarme,
weil dort **Anwesenheit** geprueft wird und nicht Abwesenheit.

## Abnahme

1. **`SHELL:` wird gefangen.** Nachweis: Wegwerf-Baum mit `fabrik_warnsatz_anlegen(z)` und
   `target_compile_options(z PRIVATE "SHELL:-Wno-error -w")` endet mit Code ungleich 0, und
   die Meldung nennt den Schalter. Daneben, am Stand **vor** der Aenderung gemessen,
   dieselbe Datei mit Code 0, `1 ... alle mit Warnsatz und ohne Pauschalabschalter` und
   einem Bau mit Code 0 ohne jede Diagnose -- ohne diese Gegenprobe belegt die erste
   Haelfte nur, dass irgendetwas rot wurde.
2. **Der Generatorausdruck ebenso.** Nachweis: dasselbe mit `"$<1:-w>"` und mit
   `"$<$<CONFIG:Release>:-w>"`, beide Code ungleich 0, beide vorher Code 0.
3. **Nichts wird ueber-scharf.** Nachweis, alle vier: `-Wno-conversion` an einem Ziel mit
   Satz konfiguriert weiter mit Code 0; die drei Bauwege (Arbeitsbereich, `kern` allein,
   `pruefstand` allein) konfigurieren mit Code 0 und melden je eine Zahl groesser als null,
   wobei die des Arbeitsbereichs die Summe der beiden anderen ist -- **nenne die drei
   Zahlen**, am 2026-09-04 waren es 15 / 10 / 5, die Zahl ist zu nennen, nicht zu treffen.
   Dazu der Bytevergleich aller erzeugten `CXX_FLAGS` des Arbeitsbereichs vorher gegen
   nachher, bytegleich, mit textlich normalisierter Baumwurzel. Und der Bau selbst gruen
   mit `ctest` ohne Ausfall. Nicht "der Bau ist gruen" allein.

**Nachweisort:** dieselbe Staffelung wie in 0046, 0058 und 0060 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort keine
Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am 2026-09-04 kam ich mit
Rang 1 aus.
