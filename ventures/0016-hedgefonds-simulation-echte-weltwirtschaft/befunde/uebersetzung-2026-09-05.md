---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-05
bauart: cmake
manifeste: 7
ergebnis: ok
---

# Der Compiler hat gesprochen: ok

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 22 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.1s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand_geprueft
[ 15%] Built target belegstellen_riegel
[ 15%] Built target mutationstreiber
[ 15%] Built target pruefstand
[ 17%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 20%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 21%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 25%] Built target bezeichner_riegel
[ 31%] Built target vorrat_kernanker_probe
[ 31%] Built target vorrat_probe
[ 34%] Built target vorrat_verfahren_probe
[ 35%] Linking CXX static library libkern_geprueft.a
[ 48%] Built target kern_geprueft
[ 50%] Linking CXX executable pruefsumme_probe
[ 51%] Linking CXX executable verlauf_probe
[ 53%] Linking CXX executable schritt_probe
[ 54%] Linking CXX executable aktion_probe
[ 57%] Linking CXX executable festkomma_probe
[ 57%] Linking CXX executable schranken_probe
[ 59%] Linking CXX executable meldung_probe
[ 60%] Linking CXX executable schreiber_probe
[ 62%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 64%] Linking CXX executable zufall_probe
[ 65%] Linking CXX executable zustand_probe
[ 67%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 68%] Built target festkomma_probe
[ 70%] Built target aktion_probe
[ 71%] Built target pruefsumme_probe
[ 73%] Built target verlauf_probe
[ 75%] Built target schranken_probe
[ 76%] Built target zustand_probe
[ 78%] Built target schreiber_probe
[ 79%] Built target schritt_probe
[ 81%] Built target zufall_probe
[ 82%] Linking CXX static library libkern.a
[ 84%] Built target meldung_probe
[ 96%] Built target kern
[ 98%] Linking CXX executable werte_probe
[ 98%] Built target werte_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: aktion_probe
 1/18 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/18 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/18 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/18 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/18 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/18 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/18 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/18 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/18 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/18 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/18 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/18 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: vorrat_kernanker_probe
13/18 Test #13: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 14: vorrat_probe
14/18 Test #14: vorrat_probe .....................   Passed    0.01 sec
      Start 15: vorrat_verfahren_probe
15/18 Test #15: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 16: belegstellen_riegel
16/18 Test #16: belegstellen_riegel ..............   Passed    3.15 sec
      Start 17: bezeichner_riegel
17/18 Test #17: bezeichner_riegel ................   Passed    0.33 sec
      Start 18: schlussriegel_nachbau
18/18 Test #18: schlussriegel_nachbau ............   Passed    0.46 sec

100% tests passed, 0 tests failed out of 18

Total Test time (real) =   4.19 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  8%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[  8%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 10%] Linking CXX static library libkern_geprueft.a
[ 28%] Built target kern_geprueft
[ 30%] Linking CXX executable pruefsumme_probe
[ 32%] Linking CXX executable meldung_probe
[ 34%] Linking CXX executable festkomma_probe
[ 36%] Linking CXX executable zufall_probe
[ 41%] Linking CXX executable schritt_probe
[ 41%] Linking CXX executable aktion_probe
[ 43%] Linking CXX executable schreiber_probe
[ 45%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 47%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 50%] Linking CXX executable schranken_probe
[ 52%] Linking CXX executable zustand_probe
[ 54%] Linking CXX executable verlauf_probe
[ 56%] Built target aktion_probe
[ 58%] Built target festkomma_probe
[ 60%] Built target schranken_probe
[ 63%] Built target schritt_probe
[ 65%] Built target zustand_probe
[ 67%] Built target meldung_probe
[ 69%] Built target pruefsumme_probe
[ 71%] Built target verlauf_probe
[ 73%] Built target zufall_probe
[ 76%] Built target schreiber_probe
[ 78%] Linking CXX static library libkern.a
[ 95%] Built target kern
[ 97%] Linking CXX executable werte_probe
[ 97%] Built target werte_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: aktion_probe
 1/12 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/12 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/12 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/12 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/12 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/12 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/12 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/12 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/12 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/12 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/12 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/12 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.21 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[ 83%] Built target vorrat_probe
[ 83%] Built target vorrat_kernanker_probe
[100%] Built target vorrat_verfahren_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
    Start 1: vorrat_kernanker_probe
1/3 Test #1: vorrat_kernanker_probe ...........   Passed    0.01 sec
    Start 2: vorrat_probe
2/3 Test #2: vorrat_probe .....................   Passed    0.01 sec
    Start 3: vorrat_verfahren_probe
3/3 Test #3: vorrat_verfahren_probe ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.04 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............   Passed    3.23 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   3.23 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target bezeichner_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bau
    Start 1: bezeichner_riegel
1/1 Test #1: bezeichner_riegel ................   Passed    0.32 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.32 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target mutationstreiber
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/bau
No tests were found!!!
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/schlussriegel/bau
```

## `cmake --build` -- ok (Code 0)

```

```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/schlussriegel/bau
    Start 1: schlussriegel_nachbau
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.46 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.46 sec
```
