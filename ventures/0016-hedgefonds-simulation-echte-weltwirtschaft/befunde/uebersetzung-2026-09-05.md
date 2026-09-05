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
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 21 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 10%] Built target pruefstand_geprueft
[ 10%] Built target pruefstand
[ 13%] Built target mutationstreiber
[ 16%] Built target bezeichner_riegel
[ 18%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 20%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 23%] Built target belegstellen_riegel
[ 33%] Built target vorrat_probe
[ 33%] Built target vorrat_verfahren_probe
[ 33%] Built target vorrat_kernanker_probe
[ 35%] Linking CXX static library libkern.a
[ 48%] Built target kern
[ 50%] Linking CXX static library libkern_geprueft.a
[ 63%] Built target kern_geprueft
[ 70%] Linking CXX executable schreiber_probe
[ 70%] Linking CXX executable zustand_probe
[ 70%] Linking CXX executable meldung_probe
[ 70%] Linking CXX executable festkomma_probe
[ 71%] Linking CXX executable zufall_probe
[ 76%] Linking CXX executable schranken_probe
[ 76%] Linking CXX executable pruefsumme_probe
[ 76%] Linking CXX executable werte_probe
[ 78%] Linking CXX executable schritt_probe
[ 80%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 81%] Linking CXX executable zustandsausgabe_probe
[ 83%] Built target zufall_probe
[ 85%] Built target festkomma_probe
[ 86%] Built target schreiber_probe
[ 88%] Built target werte_probe
[ 90%] Built target schritt_probe
[ 91%] Built target meldung_probe
[ 93%] Built target pruefsumme_probe
[ 95%] Built target zustand_probe
[ 96%] Built target schranken_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable verlauf_probe
[100%] Built target verlauf_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/17 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/17 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/17 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/17 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/17 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/17 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: verlauf_probe
 7/17 Test  #7: verlauf_probe ....................   Passed    0.01 sec
      Start  8: werte_probe
 8/17 Test  #8: werte_probe ......................   Passed    0.01 sec
      Start  9: zufall_probe
 9/17 Test  #9: zufall_probe .....................   Passed    0.01 sec
      Start 10: zustand_probe
10/17 Test #10: zustand_probe ....................   Passed    0.01 sec
      Start 11: zustandsausgabe_probe
11/17 Test #11: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 12: vorrat_kernanker_probe
12/17 Test #12: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 13: vorrat_probe
13/17 Test #13: vorrat_probe .....................   Passed    0.01 sec
      Start 14: vorrat_verfahren_probe
14/17 Test #14: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 15: belegstellen_riegel
15/17 Test #15: belegstellen_riegel ..............   Passed    1.23 sec
      Start 16: bezeichner_riegel
16/17 Test #16: bezeichner_riegel ................   Passed    0.30 sec
      Start 17: schlussriegel_nachbau
17/17 Test #17: schlussriegel_nachbau ............   Passed    0.44 sec

100% tests passed, 0 tests failed out of 17

Total Test time (real) =   2.19 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 9 Kernquelle(n) und 11 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 13 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[  7%] Linking CXX static library libkern.a
[ 26%] Built target kern
[ 28%] Linking CXX static library libkern_geprueft.a
[ 47%] Built target kern_geprueft
[ 57%] Linking CXX executable schritt_probe
[ 57%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 57%] Linking CXX executable meldung_probe
[ 57%] Linking CXX executable schranken_probe
[ 59%] Linking CXX executable festkomma_probe
[ 64%] Linking CXX executable werte_probe
[ 64%] Linking CXX executable schreiber_probe
[ 69%] Linking CXX executable pruefsumme_probe
[ 69%] Linking CXX executable zustandsausgabe_probe
[ 71%] Linking CXX executable zufall_probe
[ 73%] Linking CXX executable zustand_probe
[ 76%] Built target zufall_probe
[ 80%] Built target pruefsumme_probe
[ 80%] Built target zustand_probe
[ 83%] Built target schranken_probe
[ 85%] Built target festkomma_probe
[ 88%] Built target schreiber_probe
[ 90%] Built target meldung_probe
[ 92%] Built target werte_probe
[ 95%] Built target zustandsausgabe_probe
[ 97%] Built target schritt_probe
[100%] Linking CXX executable verlauf_probe
[100%] Built target verlauf_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/11 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/11 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/11 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/11 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/11 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/11 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: verlauf_probe
 7/11 Test  #7: verlauf_probe ....................   Passed    0.01 sec
      Start  8: werte_probe
 8/11 Test  #8: werte_probe ......................   Passed    0.01 sec
      Start  9: zufall_probe
 9/11 Test  #9: zufall_probe .....................   Passed    0.01 sec
      Start 10: zustand_probe
10/11 Test #10: zustand_probe ....................   Passed    0.01 sec
      Start 11: zustandsausgabe_probe
11/11 Test #11: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 11

Total Test time (real) =   0.20 sec
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
[ 83%] Built target vorrat_kernanker_probe
[ 83%] Built target vorrat_probe
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

Total Test time (real) =   0.03 sec
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
[ 50%] Building CXX object CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............   Passed    1.27 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   1.27 sec
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.30 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.30 sec
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.47 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.47 sec
```
