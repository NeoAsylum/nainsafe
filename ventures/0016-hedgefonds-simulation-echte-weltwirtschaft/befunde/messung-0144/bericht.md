# Messung zu Paket 0144 -- Nachweis

Erzeugt von `befunde/messung-0144/nachweis.py`. Kein Modell, keine Einschaetzung -- Uebersetzer, `ctest` und die Proben im Wortlaut.

**Bezugsstand.** Der Baum *vorher* ist der Arbeitsbaum dieses Laufs mit den drei Dateien aus `befunde/messung-0144/vorher/` an ihrer Stelle -- also der unmittelbar vorhergehende Stand desselben Baums, als Kopie eingefroren und nicht als Git-Verweis. Gemessen am 2026-09-05, Git-Stand `4ff788d`.

## Ergebnis

```
OK   ctest-Eintraege ON: vorher 12, nachher 12 (erwartet gleich, das Paket legt keine Probe an)
OK   ON schritt_probe: Ausgabe vorher/nachher zeichengleich
OK   ON zustand_probe: Ausgabe vorher/nachher zeichengleich
OK   ON zustandsausgabe_probe: Ausgabe vorher/nachher zeichengleich
OK   ON Bedingung 1: Partie ueber 26 Runden aufgenommen, Code 0 (vorher 4 Runden)
OK   Arbeitsbereich ON: cmake/build/ctest je Code 0, 18 ctest-Eintraege
OK   ctest-Eintraege OFF: vorher 12, nachher 12 (erwartet gleich, das Paket legt keine Probe an)
OK   OFF schritt_probe: Ausgabe vorher/nachher zeichengleich
OK   OFF zustand_probe: Ausgabe vorher/nachher zeichengleich
OK   OFF zustandsausgabe_probe: Ausgabe vorher/nachher zeichengleich
OK   OFF Bedingung 1: Partie ueber 26 Runden aufgenommen, Code 0 (vorher 4 Runden)
OK   Arbeitsbereich OFF: cmake/build/ctest je Code 0, 18 ctest-Eintraege
OK   Riegel kapazitaet-27: Bau ROT (erwartet ROT), Meldung nennt static_assert: ja
OK   Kontrolle alte-schranke-27: mit der alten 512-KB-Schranke daneben waere derselbe Verstoss gruen -- sie griff bei 27 nicht
OK   Gegenprobe kapazitaet-20: Bau gruen, verlauf_probe ROT, Meldung "der Verlauf ist voll": ja
OK   Bedingung 2: RUNDEN_KAPAZITAET ist keine Zahl, sondern die Wand
OK   Bedingung 2: die einzige Zahlkonstante des Kopfes ist die Wand aus T40
OK   Bedingung 2: keine Konstante ist mehr als Partielaenge R begruendet
OK   Bedingung 2: die Wand ist im Kopf aus T40 begruendet
OK   Bedingung 2: die Abbruchmeldung nennt die Schranke
OK   Bedingung 2: kein Gleitkommatyp im Kasten (T4, mit blossem Auge)
Abweichungen: 0
```

Zahlkonstanten im Kopf des Kastens: PARTIELAENGE_HOECHSTENS = 26

## FABRIK_SANITIZER=ON, Baum nachher

### cmake -S -- Code 0

```
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/claude-1000/messung-0144/nachher-on/bau
```

### cmake --build -- Code 0

```
[ 93%] Linking CXX executable werte_probe
[ 95%] Linking CXX executable zufall_probe
[ 95%] Built target werte_probe
[ 95%] Built target zufall_probe
[ 97%] Linking CXX executable zustand_probe
[ 97%] Built target zustand_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

### ctest --test-dir -- Code 0

```
      Start 10: zufall_probe
10/12 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/12 Test #11: zustand_probe ....................   Passed    0.05 sec
      Start 12: zustandsausgabe_probe
12/12 Test #12: zustandsausgabe_probe ............   Passed    0.19 sec
100% tests passed, 0 tests failed out of 12
Total Test time (real) =   0.37 sec
```

### verlauf_probe im Wortlaut -- nachher

```
Code 0
Groessen: sizeof(Verlauf) 451784, sizeof(Kette) 17368, RUNDEN_KAPAZITAET 26, PARTIELAENGE_HOECHSTENS 26
Bedingung 1 -- die Partie und ihre Ketten:
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 2: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 3: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 4: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 5: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 6: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 7: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 8: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 9: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 10: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 11: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 12: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 13: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 14: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 15: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 16: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 17: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 18: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 19: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 20: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 21: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 22: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 23: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 24: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 25: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 26: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 26 Runden: 4550 Glieder im Verlauf, Zustandspruefsumme 632e47f488471e75
Bedingung 2 -- die Aufnahmekapazitaet je Runde:
  an der Grenze: Runde 7 mit 310 Gliedern aufgenommen, 0 abweichend, kein Abbruch
  eines darueber: Abbruch mit "kern::verlauf -- die Kette der Runde 7 ist voll: die Aufnahmekapazitaet je Runde betraegt 310 Glieder (T19). Ein weiteres Glied waere eine stille Kuerzung."
  danach unveraendert: 310 Glieder in Runde 7
Bedingung 3 -- die Kapazitaet ueber die Partie:
  an der Grenze: 26 Runden aufgenommen, kein Abbruch
  eine darueber: Abbruch mit "kern::verlauf -- der Verlauf ist voll: er nimmt 26 Runden auf -- so viele, wie die laengste nach T40 zulaessige Partie hat --, und die Runde 27 waere die naechste. Eine stille Kuerzung gibt es nicht (T19)."
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

### verlauf_probe im Wortlaut -- vorher (dieselbe Probe, alter Kasten: sie zaehlt nur bis vier)

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

## FABRIK_SANITIZER=OFF, Baum nachher

### cmake -S -- Code 0

```
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 1 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]
-- Warnsatz-Schlussriegel: 13 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /tmp/claude-1000/messung-0144/nachher-off/bau
```

### cmake --build -- Code 0

```
[ 91%] Linking CXX executable werte_probe
[ 91%] Built target werte_probe
[ 94%] Linking CXX executable zufall_probe
[ 94%] Built target zufall_probe
[ 97%] Linking CXX executable zustand_probe
[ 97%] Built target zustand_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

### ctest --test-dir -- Code 0

```
      Start 10: zufall_probe
10/12 Test #10: zufall_probe .....................   Passed    0.00 sec
      Start 11: zustand_probe
11/12 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/12 Test #12: zustandsausgabe_probe ............   Passed    0.05 sec
100% tests passed, 0 tests failed out of 12
Total Test time (real) =   0.09 sec
```

### verlauf_probe im Wortlaut -- nachher

```
Code 0
Groessen: sizeof(Verlauf) 451784, sizeof(Kette) 17368, RUNDEN_KAPAZITAET 26, PARTIELAENGE_HOECHSTENS 26
Bedingung 1 -- die Partie und ihre Ketten:
  Runde 1: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 2: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 3: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 4: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 5: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 6: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 7: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 8: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 9: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 10: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 11: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 12: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 13: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 14: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 15: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 16: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 17: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 18: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 19: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 20: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 21: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 22: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 23: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 24: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 25: 175 Glieder, zeichengleich ja, fremde Glieder 0
  Runde 26: 175 Glieder, zeichengleich ja, fremde Glieder 0
  nach 26 Runden: 4550 Glieder im Verlauf, Zustandspruefsumme 632e47f488471e75
Bedingung 2 -- die Aufnahmekapazitaet je Runde:
  an der Grenze: Runde 7 mit 310 Gliedern aufgenommen, 0 abweichend, kein Abbruch
  eines darueber: Abbruch mit "kern::verlauf -- die Kette der Runde 7 ist voll: die Aufnahmekapazitaet je Runde betraegt 310 Glieder (T19). Ein weiteres Glied waere eine stille Kuerzung."
  danach unveraendert: 310 Glieder in Runde 7
Bedingung 3 -- die Kapazitaet ueber die Partie:
  an der Grenze: 26 Runden aufgenommen, kein Abbruch
  eine darueber: Abbruch mit "kern::verlauf -- der Verlauf ist voll: er nimmt 26 Runden auf -- so viele, wie die laengste nach T40 zulaessige Partie hat --, und die Runde 27 waere die naechste. Eine stille Kuerzung gibt es nicht (T19)."
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

### verlauf_probe im Wortlaut -- vorher (dieselbe Probe, alter Kasten: sie zaehlt nur bis vier)

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

## Die drei Wegwerfbaeume im Wortlaut

### kapazitaet-27 -- eine Runde ueber die Wand

```
Bau: ROT
[ 53%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 61%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
In file included from /tmp/claude-1000/messung-0144/kapazitaet-27/kern/src/verlauf.cpp:34:
/tmp/claude-1000/messung-0144/kapazitaet-27/kern/include/kern/verlauf.hpp:205:31: error: static assertion failed: T40: ein Verlauf traegt hoechstens die Runden der laengsten zulaessigen Partie, und eine weitere passt nicht mehr hinein
  205 | static_assert(sizeof(Verlauf) < (PARTIELAENGE_HOECHSTENS + 1) * sizeof(Kette),
      |               ~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/tmp/claude-1000/messung-0144/kapazitaet-27/kern/include/kern/verlauf.hpp:205:31: note: the comparison reduces to ‘(469160 < 468936)’
gmake[3]: *** [CMakeFiles/kern.dir/build.make:149: CMakeFiles/kern.dir/src/verlauf.cpp.o] Error 1
gmake[3]: *** Waiting for unfinished jobs....
gmake[2]: *** [CMakeFiles/Makefile2:123: CMakeFiles/kern.dir/all] Error 2
gmake[1]: *** [CMakeFiles/Makefile2:386: CMakeFiles/verlauf_probe.dir/rule] Error 2
gmake: *** [Makefile:239: verlauf_probe] Error 2
```

### alte-schranke-27 -- derselbe Verstoss, alte Schranke daneben

```
Bau: gruen
[ 30%] Building CXX object CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 38%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 46%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 53%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 61%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 69%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 76%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 84%] Linking CXX static library libkern.a
[ 84%] Built target kern
[ 92%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[100%] Linking CXX executable verlauf_probe
[100%] Built target verlauf_probe
```

### kapazitaet-20 -- wieder an R gebunden

```
Bau: gruen
[ 30%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 38%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 46%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 53%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 61%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 69%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 76%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 84%] Linking CXX static library libkern.a
[ 84%] Built target kern
[ 92%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[100%] Linking CXX executable verlauf_probe
[100%] Built target verlauf_probe
--- verlauf_probe Code -6 ---
terminate called after throwing an instance of 'std::domain_error'
  what():  kern::verlauf -- der Verlauf ist voll: er nimmt 20 Runden auf -- so viele, wie die laengste nach T40 zulaessige Partie hat --, und die Runde 21 waere die naechste. Eine stille Kuerzung gibt es nicht (T19).
```
