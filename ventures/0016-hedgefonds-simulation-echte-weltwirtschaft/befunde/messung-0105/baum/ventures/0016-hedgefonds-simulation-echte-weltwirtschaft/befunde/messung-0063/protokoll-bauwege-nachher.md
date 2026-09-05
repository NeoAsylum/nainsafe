# Die drei Bauwege -- Fassung `nachher`

## `arbeitsbereich`

`cmake -S` **CODE=0**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Warnsatz-Schlussriegel: 15 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-arbeitsbereich-nachher
```

`cmake --build` **CODE=0**

```
[  9%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[  9%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[  9%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[  9%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 16%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 16%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 16%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 19%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 21%] Building CXX object kern/CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 23%] Building CXX object kern/CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 26%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 30%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 35%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 38%] Building CXX object kern/CMakeFiles/kern.dir/src/zufall.cpp.o
[ 40%] Linking CXX static library libpruefstand.a
[ 40%] Built target pruefstand
[ 42%] Linking CXX static library libpruefstand_geprueft.a
[ 42%] Built target pruefstand_geprueft
[ 45%] Building CXX object pruefstand/CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 50%] Building CXX object pruefstand/CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 50%] Building CXX object pruefstand/CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 52%] Linking CXX executable vorrat_probe
[ 52%] Built target vorrat_probe
[ 54%] Linking CXX static library libkern.a
[ 54%] Built target kern
[ 57%] Linking CXX executable vorrat_kernanker_probe
[ 57%] Built target vorrat_kernanker_probe
[ 59%] Linking CXX executable vorrat_verfahren_probe
[ 61%] Linking CXX static library libkern_geprueft.a
[ 61%] Built target kern_geprueft
[ 76%] Building CXX object kern/CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 76%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 76%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 76%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 76%] Building CXX object kern/CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 76%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 78%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 80%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 80%] Built target vorrat_verfahren_probe
[ 83%] Linking CXX executable pruefsumme_probe
[ 85%] Linking CXX executable festkomma_probe
[ 88%] Linking CXX executable meldung_probe
[ 88%] Built target pruefsumme_probe
[ 88%] Built target festkomma_probe
[ 88%] Built target meldung_probe
[ 90%] Linking CXX executable schritt_probe
[ 92%] Linking CXX executable zufall_probe
[ 92%] Built target schritt_probe
[ 92%] Built target zufall_probe
[ 95%] Linking CXX executable schreiber_probe
[ 95%] Built target schreiber_probe
[ 97%] Linking CXX executable zustand_probe
[ 97%] Built target zustand_probe
[100%] Linking CXX executable schranken_probe
[100%] Built target schranken_probe
```

`ctest` **CODE=0**

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-arbeitsbereich-nachher
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
      Start  7: zufall_probe
 7/11 Test  #7: zufall_probe .....................   Passed    0.01 sec
      Start  8: zustand_probe
 8/11 Test  #8: zustand_probe ....................   Passed    0.02 sec
      Start  9: vorrat_kernanker_probe
 9/11 Test  #9: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 10: vorrat_probe
10/11 Test #10: vorrat_probe .....................   Passed    0.01 sec
      Start 11: vorrat_verfahren_probe
11/11 Test #11: vorrat_verfahren_probe ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 11

Total Test time (real) =   0.14 sec
```

## `kern`

`cmake -S` **CODE=0**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Warnsatz-Schlussriegel: 10 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-kern-nachher
```

`cmake --build` **CODE=0**

```
[ 10%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 16%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 26%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 30%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 36%] Building CXX object CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 36%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 40%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 43%] Linking CXX static library libkern.a
[ 43%] Built target kern
[ 46%] Linking CXX static library libkern_geprueft.a
[ 46%] Built target kern_geprueft
[ 66%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 70%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 73%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 76%] Linking CXX executable festkomma_probe
[ 80%] Linking CXX executable pruefsumme_probe
[ 83%] Linking CXX executable meldung_probe
[ 83%] Built target festkomma_probe
[ 83%] Built target pruefsumme_probe
[ 83%] Built target meldung_probe
[ 86%] Linking CXX executable schritt_probe
[ 90%] Linking CXX executable zufall_probe
[ 90%] Built target schritt_probe
[ 90%] Built target zufall_probe
[ 93%] Linking CXX executable schreiber_probe
[ 93%] Built target schreiber_probe
[ 96%] Linking CXX executable zustand_probe
[100%] Linking CXX executable schranken_probe
[100%] Built target zustand_probe
[100%] Built target schranken_probe
```

`ctest` **CODE=0**

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-kern-nachher
    Start 1: festkomma_probe
1/8 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: meldung_probe
2/8 Test #2: meldung_probe ....................   Passed    0.01 sec
    Start 3: pruefsumme_probe
3/8 Test #3: pruefsumme_probe .................   Passed    0.01 sec
    Start 4: schranken_probe
4/8 Test #4: schranken_probe ..................   Passed    0.01 sec
    Start 5: schreiber_probe
5/8 Test #5: schreiber_probe ..................   Passed    0.01 sec
    Start 6: schritt_probe
6/8 Test #6: schritt_probe ....................   Passed    0.01 sec
    Start 7: zufall_probe
7/8 Test #7: zufall_probe .....................   Passed    0.01 sec
    Start 8: zustand_probe
8/8 Test #8: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.09 sec
```

## `pruefstand`

`cmake -S` **CODE=0**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-pruefstand-nachher
```

`cmake --build` **CODE=0**

```
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[ 41%] Linking CXX static library libpruefstand.a
[ 41%] Built target pruefstand
[ 50%] Linking CXX static library libpruefstand_geprueft.a
[ 50%] Built target pruefstand_geprueft
[ 75%] Building CXX object CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 83%] Linking CXX executable vorrat_probe
[ 91%] Linking CXX executable vorrat_kernanker_probe
[ 91%] Built target vorrat_probe
[ 91%] Built target vorrat_kernanker_probe
[100%] Linking CXX executable vorrat_verfahren_probe
[100%] Built target vorrat_verfahren_probe
```

`ctest` **CODE=0**

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/bau-pruefstand-nachher
    Start 1: vorrat_kernanker_probe
1/3 Test #1: vorrat_kernanker_probe ...........   Passed    0.01 sec
    Start 2: vorrat_probe
2/3 Test #2: vorrat_probe .....................   Passed    0.01 sec
    Start 3: vorrat_verfahren_probe
3/3 Test #3: vorrat_verfahren_probe ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.03 sec
```

