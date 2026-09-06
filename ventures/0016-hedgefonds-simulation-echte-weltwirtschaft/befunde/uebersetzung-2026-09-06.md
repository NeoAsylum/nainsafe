---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-06
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
-- Warnsatz-Schlussriegel: 22 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 388 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand_geprueft
[  7%] Built target bezeichner_riegel
[  9%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 12%] Built target mutationstreiber
[ 14%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 15%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 17%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 25%] Built target pruefstand
[ 26%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 29%] Built target vorrat_verfahren_probe
[ 32%] Built target vorrat_probe
[ 35%] Built target vorrat_kernanker_probe
[ 37%] Linking CXX static library libkern_geprueft.a
[ 48%] Built target kern_geprueft
[ 50%] Linking CXX executable pruefsumme_probe
[ 51%] Linking CXX executable meldung_probe
[ 53%] Linking CXX executable aktion_probe
[ 54%] Linking CXX executable schranken_probe
[ 56%] Linking CXX executable festkomma_probe
[ 57%] Linking CXX executable schreiber_probe
[ 59%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 60%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 64%] Linking CXX executable schritt_probe
[ 64%] Linking CXX executable zustand_probe
[ 65%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 67%] Linking CXX executable zufall_probe
[ 68%] Built target schranken_probe
[ 70%] Built target schreiber_probe
[ 71%] Built target zustand_probe
[ 73%] Built target pruefsumme_probe
[ 76%] Built target zufall_probe
[ 76%] Built target festkomma_probe
[ 78%] Built target schritt_probe
[ 79%] Built target meldung_probe
[ 81%] Built target aktion_probe
[ 82%] Linking CXX static library libkern.a
[ 93%] Built target kern
[ 95%] Linking CXX executable verlauf_probe
[ 95%] Built target verlauf_probe
[ 96%] Linking CXX executable werte_probe
[ 96%] Built target werte_probe
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
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
11/18 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/18 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: vorrat_kernanker_probe
13/18 Test #13: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 14: vorrat_probe
14/18 Test #14: vorrat_probe .....................   Passed    0.01 sec
      Start 15: vorrat_verfahren_probe
15/18 Test #15: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 16: belegstellen_riegel
16/18 Test #16: belegstellen_riegel ..............   Passed    4.82 sec
      Start 17: bezeichner_riegel
17/18 Test #17: bezeichner_riegel ................   Passed    0.34 sec
      Start 18: schlussriegel_nachbau
18/18 Test #18: schlussriegel_nachbau ............   Passed    0.46 sec

100% tests passed, 0 tests failed out of 18

Total Test time (real) =   5.87 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 242 Schaltereintraege.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[  4%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[  8%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 15%] Linking CXX static library libkern_geprueft.a
[ 30%] Built target kern_geprueft
[ 32%] Linking CXX executable pruefsumme_probe
[ 36%] Linking CXX executable festkomma_probe
[ 36%] Linking CXX executable schranken_probe
[ 39%] Linking CXX executable schreiber_probe
[ 41%] Linking CXX executable aktion_probe
[ 43%] Linking CXX executable zustand_probe
[ 45%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 47%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 50%] Linking CXX executable zufall_probe
[ 52%] Linking CXX executable schritt_probe
[ 54%] Linking CXX executable meldung_probe
[ 56%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 60%] Built target schranken_probe
[ 60%] Built target zufall_probe
[ 63%] Built target meldung_probe
[ 65%] Built target pruefsumme_probe
[ 67%] Built target zustand_probe
[ 69%] Built target aktion_probe
[ 71%] Built target schreiber_probe
[ 73%] Built target festkomma_probe
[ 76%] Built target schritt_probe
[ 78%] Linking CXX static library libkern.a
[ 93%] Built target kern
[ 95%] Linking CXX executable verlauf_probe
[ 95%] Built target verlauf_probe
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
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 89 Schaltereintraege.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[100%] Built target vorrat_probe
[100%] Built target vorrat_kernanker_probe
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
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: belegstellen_riegel ..............   Passed    5.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   5.01 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.34 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.34 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.45 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.45 sec
```
