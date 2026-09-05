---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-05
bauart: cmake
manifeste: 5
ergebnis: ok
---

# Der Compiler hat gesprochen: ok

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

## `cmake -S` -- ok (Code 0)

```
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 19 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  9%] Built target belegstellen_riegel
[  9%] Built target pruefstand
[ 18%] Built target mutationstreiber
[ 18%] Built target pruefstand_geprueft
[ 20%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 37%] Built target kern_geprueft
[ 44%] Built target vorrat_kernanker_probe
[ 44%] Built target vorrat_probe
[ 46%] Linking CXX executable festkomma_probe
[ 48%] Linking CXX executable schreiber_probe
[ 50%] Linking CXX executable schritt_probe
[ 51%] Linking CXX executable schranken_probe
[ 55%] Built target vorrat_verfahren_probe
[ 57%] Linking CXX executable meldung_probe
[ 59%] Linking CXX executable werte_probe
[ 61%] Linking CXX executable pruefsumme_probe
[ 62%] Linking CXX executable zufall_probe
[ 64%] Linking CXX executable zustand_probe
[ 68%] Built target zustandsausgabe_probe
[ 70%] Built target festkomma_probe
[ 72%] Built target pruefsumme_probe
[ 74%] Built target zufall_probe
[ 75%] Built target schritt_probe
[ 77%] Built target werte_probe
[ 79%] Built target schranken_probe
[ 81%] Built target schreiber_probe
[ 83%] Built target zustand_probe
[ 85%] Built target meldung_probe
[ 87%] Linking CXX static library libkern.a
[100%] Built target kern
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/14 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/14 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/14 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/14 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/14 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/14 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: werte_probe
 7/14 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/14 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/14 Test  #9: zustand_probe ....................   Passed    0.01 sec
      Start 10: zustandsausgabe_probe
10/14 Test #10: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 11: vorrat_kernanker_probe
11/14 Test #11: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 12: vorrat_probe
12/14 Test #12: vorrat_probe .....................   Passed    0.01 sec
      Start 13: vorrat_verfahren_probe
13/14 Test #13: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 14: belegstellen_riegel
14/14 Test #14: belegstellen_riegel ..............   Passed    0.79 sec

100% tests passed, 0 tests failed out of 14

Total Test time (real) =   1.00 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 12 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  2%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 13%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 13%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 15%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 18%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 23%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 26%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 28%] Linking CXX static library libkern.a
[ 36%] Built target kern
[ 39%] Linking CXX static library libkern_geprueft.a
[ 47%] Built target kern_geprueft
[ 55%] Linking CXX executable pruefsumme_probe
[ 55%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 55%] Linking CXX executable festkomma_probe
[ 57%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 68%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 68%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 68%] Linking CXX executable zufall_probe
[ 68%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 71%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 73%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 76%] Built target pruefsumme_probe
[ 78%] Built target zufall_probe
[ 81%] Built target festkomma_probe
[ 84%] Linking CXX executable meldung_probe
[ 84%] Built target meldung_probe
[ 86%] Linking CXX executable werte_probe
[ 86%] Built target werte_probe
[ 89%] Linking CXX executable schreiber_probe
[ 89%] Built target schreiber_probe
[ 92%] Linking CXX executable schritt_probe
[ 94%] Linking CXX executable zustand_probe
[ 97%] Linking CXX executable schranken_probe
[ 97%] Built target schritt_probe
[ 97%] Built target zustand_probe
[ 97%] Built target schranken_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/10 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/10 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/10 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/10 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/10 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/10 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: werte_probe
 7/10 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/10 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/10 Test  #9: zustand_probe ....................   Passed    0.01 sec
      Start 10: zustandsausgabe_probe
10/10 Test #10: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   0.18 sec
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
1/1 Test #1: belegstellen_riegel ..............   Passed    0.79 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.80 sec
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
