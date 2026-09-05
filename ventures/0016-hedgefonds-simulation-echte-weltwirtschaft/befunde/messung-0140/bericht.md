# Messung zu Paket 0140 -- Nachweis

Erzeugt von `befunde/messung-0140/nachweis.py`. Vier Wegwerfbaeume unter TMPDIR plus zweimal der Arbeitsbereich, je `cmake -S`, `cmake --build`, `ctest`.

**Bezugsstand.** Der Baum *vorher* ist der Arbeitsbaum dieses Laufs ohne die drei Dateien des Pakets -- also der unmittelbar vorhergehende Stand desselben Baums. Gemessen am 2026-09-05, Git-Stand `8bfae3b` (er kann waehrend des Laufs weiterwandern; massgeblich ist die Kopie, nicht der Verweis).

## Ergebnis

```
OK   ctest-Eintraege ON: vorher 10, nachher 11, Zuwachs 1 (erwartet 1)
OK   ON schritt_probe: Ausgabe vorher/nachher zeichengleich
OK   ON zustand_probe: Ausgabe vorher/nachher zeichengleich
OK   ON zustandsausgabe_probe: Ausgabe vorher/nachher zeichengleich
OK   Arbeitsbereich ON: cmake/build/ctest je Code 0, 17 ctest-Eintraege
OK   ctest-Eintraege OFF: vorher 10, nachher 11, Zuwachs 1 (erwartet 1)
OK   OFF schritt_probe: Ausgabe vorher/nachher zeichengleich
OK   OFF zustand_probe: Ausgabe vorher/nachher zeichengleich
OK   OFF zustandsausgabe_probe: Ausgabe vorher/nachher zeichengleich
OK   Arbeitsbereich OFF: cmake/build/ctest je Code 0, 17 ctest-Eintraege
Abweichungen: 0
```

## FABRIK_SANITIZER=ON, Baum nachher

### cmake -S -- Code 0

```
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 13 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/claude-1000/messung-0140/nachher-on/bau
```

### cmake --build -- Code 0

```
[ 92%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 92%] Built target verlauf_probe
[ 95%] Linking CXX executable zufall_probe
[ 95%] Built target zufall_probe
[ 97%] Linking CXX executable zustand_probe
[ 97%] Built target zustand_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

### ctest --test-dir -- Code 0

```
      Start  9: zufall_probe
 9/11 Test  #9: zufall_probe .....................   Passed    0.01 sec
      Start 10: zustand_probe
10/11 Test #10: zustand_probe ....................   Passed    0.05 sec
      Start 11: zustandsausgabe_probe
11/11 Test #11: zustandsausgabe_probe ............   Passed    0.19 sec
100% tests passed, 0 tests failed out of 11
Total Test time (real) =   0.35 sec
```

### Die neue Probe im Wortlaut -- beide Seiten jeder Schranke

```
Code 0
Bedingung 1 -- die Partie und ihre Ketten:
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 2: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 3: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 4: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 4 Runden: 700 Glieder im Verlauf, Zustandspruefsumme 0a31f624003d031b
Bedingung 2 -- die Aufnahmekapazitaet je Runde:
  an der Grenze: Runde 7 mit 310 Gliedern aufgenommen, 0 abweichend, kein Abbruch
  eines darueber: Abbruch mit "kern::verlauf -- die Kette der Runde 7 ist voll: die Aufnahmekapazitaet je Runde betraegt 310 Glieder (T19). Ein weiteres Glied waere eine stille Kuerzung."
  danach unveraendert: 310 Glieder in Runde 7
Bedingung 3 -- die Kapazitaet ueber die Partie:
  an der Grenze: 20 Runden aufgenommen, kein Abbruch
  eine darueber: Abbruch mit "kern::verlauf -- der Verlauf ist voll: er nimmt 20 Runden auf, und die Runde 21 waere die naechste. Eine stille Kuerzung gibt es nicht (T19)."
Bedingung 4 -- Ordnung und Griffe daneben:
  Glied ohne Runde: kern::verlauf -- es ist keine Runde begonnen; ein Glied ohne Runde gehoert in keine Kette
  Runde 0: kern::verlauf -- eine Runde vor der ersten gibt es nicht; angeboten war die Runde 0. Rundennummern beginnen bei eins.
  Runde -1: kern::verlauf -- eine Runde vor der ersten gibt es nicht; angeboten war die Runde -1. Rundennummern beginnen bei eins.
  nach Runde 6 noch Runde 6: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 6, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  nach Runde 6 noch Runde 5: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 5, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  nach Runde 6 noch Runde 1: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 1, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  Kette der Runde 2: kern::verlauf -- zur Runde 2 traegt der Verlauf keine Kette. Eine leere Kette an ihrer Stelle saehe aus wie eine Runde ohne Schreibzugriffe.
  Kette der Runde 4: kern::verlauf -- zur Runde 4 traegt der Verlauf keine Kette. Eine leere Kette an ihrer Stelle saehe aus wie eine Runde ohne Schreibzugriffe.
verlauf_probe: alle Pruefungen bestanden
```

### Pruefsummen der Partie (schritt_probe), vorher und nachher gleich

```
  Vorrunde 0 -> Runde 1: Pruefsumme bec587d71f6905ff vorher, a28c49f74de4388a nachher; 1 von 310 Groessen geaendert (partie.runde)
  Vorrunde 9223372036854775806 -> Runde 9223372036854775807: Pruefsumme cedf8f3d65103b52 vorher, 098a309309d1f747 nachher; 1 von 310 Groessen geaendert (partie.runde)
```

## FABRIK_SANITIZER=OFF, Baum nachher

### cmake -S -- Code 0

```
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 1 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]
-- Warnsatz-Schlussriegel: 12 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/claude-1000/messung-0140/nachher-off/bau
```

### cmake --build -- Code 0

```
[ 90%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 90%] Built target werte_probe
[ 93%] Linking CXX executable zufall_probe
[ 96%] Linking CXX executable zustand_probe
[ 96%] Built target zufall_probe
[ 96%] Built target zustand_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

### ctest --test-dir -- Code 0

```
      Start  9: zufall_probe
 9/11 Test  #9: zufall_probe .....................   Passed    0.00 sec
      Start 10: zustand_probe
10/11 Test #10: zustand_probe ....................   Passed    0.01 sec
      Start 11: zustandsausgabe_probe
11/11 Test #11: zustandsausgabe_probe ............   Passed    0.05 sec
100% tests passed, 0 tests failed out of 11
Total Test time (real) =   0.08 sec
```

### Die neue Probe im Wortlaut -- beide Seiten jeder Schranke

```
Code 0
Bedingung 1 -- die Partie und ihre Ketten:
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 2: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 3: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 4: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 4 Runden: 700 Glieder im Verlauf, Zustandspruefsumme 0a31f624003d031b
Bedingung 2 -- die Aufnahmekapazitaet je Runde:
  an der Grenze: Runde 7 mit 310 Gliedern aufgenommen, 0 abweichend, kein Abbruch
  eines darueber: Abbruch mit "kern::verlauf -- die Kette der Runde 7 ist voll: die Aufnahmekapazitaet je Runde betraegt 310 Glieder (T19). Ein weiteres Glied waere eine stille Kuerzung."
  danach unveraendert: 310 Glieder in Runde 7
Bedingung 3 -- die Kapazitaet ueber die Partie:
  an der Grenze: 20 Runden aufgenommen, kein Abbruch
  eine darueber: Abbruch mit "kern::verlauf -- der Verlauf ist voll: er nimmt 20 Runden auf, und die Runde 21 waere die naechste. Eine stille Kuerzung gibt es nicht (T19)."
Bedingung 4 -- Ordnung und Griffe daneben:
  Glied ohne Runde: kern::verlauf -- es ist keine Runde begonnen; ein Glied ohne Runde gehoert in keine Kette
  Runde 0: kern::verlauf -- eine Runde vor der ersten gibt es nicht; angeboten war die Runde 0. Rundennummern beginnen bei eins.
  Runde -1: kern::verlauf -- eine Runde vor der ersten gibt es nicht; angeboten war die Runde -1. Rundennummern beginnen bei eins.
  nach Runde 6 noch Runde 6: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 6, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  nach Runde 6 noch Runde 5: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 5, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  nach Runde 6 noch Runde 1: kern::verlauf -- die Runden werden aufsteigend gesammelt (T9); angeboten war die Runde 1, zuletzt begonnen ist die Runde 6. Eine Runde, die nicht groesser ist, koennte nur auf Kosten einer schon aufgenommenen Kette dazukommen.
  Kette der Runde 2: kern::verlauf -- zur Runde 2 traegt der Verlauf keine Kette. Eine leere Kette an ihrer Stelle saehe aus wie eine Runde ohne Schreibzugriffe.
  Kette der Runde 4: kern::verlauf -- zur Runde 4 traegt der Verlauf keine Kette. Eine leere Kette an ihrer Stelle saehe aus wie eine Runde ohne Schreibzugriffe.
verlauf_probe: alle Pruefungen bestanden
```

### Pruefsummen der Partie (schritt_probe), vorher und nachher gleich

```
  Vorrunde 0 -> Runde 1: Pruefsumme bec587d71f6905ff vorher, a28c49f74de4388a nachher; 1 von 310 Groessen geaendert (partie.runde)
  Vorrunde 9223372036854775806 -> Runde 9223372036854775807: Pruefsumme cedf8f3d65103b52 vorher, 098a309309d1f747 nachher; 1 von 310 Groessen geaendert (partie.runde)
```
