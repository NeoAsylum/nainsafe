---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-04
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
-- Warnsatz-Schlussriegel: 17 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  6%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 16%] Built target pruefstand
[ 18%] Built target pruefstand_geprueft
[ 18%] Built target belegstellen_riegel
[ 20%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 25%] Built target vorrat_kernanker_probe
[ 33%] Built target vorrat_probe
[ 33%] Built target vorrat_verfahren_probe
[ 35%] Linking CXX static library libkern.a
[ 47%] Built target kern
[ 50%] Linking CXX static library libkern_geprueft.a
[ 62%] Built target kern_geprueft
[ 66%] Linking CXX executable meldung_probe
[ 66%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 68%] Linking CXX executable festkomma_probe
[ 77%] Linking CXX executable schritt_probe
[ 77%] Linking CXX executable schranken_probe
[ 79%] Linking CXX executable schreiber_probe
[ 77%] Linking CXX executable pruefsumme_probe
[ 79%] Linking CXX executable zufall_probe
[ 81%] Linking CXX executable zustand_probe
[ 83%] Built target pruefsumme_probe
[ 85%] Built target festkomma_probe
[ 87%] Built target schranken_probe
[ 89%] Built target schreiber_probe
[ 91%] Built target zufall_probe
[ 93%] Built target zustand_probe
[ 95%] Built target meldung_probe
[ 97%] Built target schritt_probe
[100%] Linking CXX executable werte_probe
[100%] Built target werte_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/13 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/13 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/13 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/13 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/13 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/13 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: werte_probe
 7/13 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/13 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/13 Test  #9: zustand_probe ....................   Passed    0.01 sec
      Start 10: vorrat_kernanker_probe
10/13 Test #10: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 11: vorrat_probe
11/13 Test #11: vorrat_probe .....................   Passed    0.01 sec
      Start 12: vorrat_verfahren_probe
12/13 Test #12: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 13: belegstellen_riegel
13/13 Test #13: belegstellen_riegel ..............   Passed    0.40 sec

100% tests passed, 0 tests failed out of 13

Total Test time (real) =   0.54 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Warnsatz-Schlussriegel: 11 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  5%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[  5%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 17%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 17%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 23%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 26%] Linking CXX static library libkern.a
[ 35%] Built target kern
[ 38%] Linking CXX static library libkern_geprueft.a
[ 47%] Built target kern_geprueft
[ 50%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 52%] Linking CXX executable pruefsumme_probe
[ 55%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 61%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 61%] Linking CXX executable festkomma_probe
[ 64%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 67%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 70%] Linking CXX executable zufall_probe
[ 73%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 76%] Built target zufall_probe
[ 79%] Built target festkomma_probe
[ 82%] Built target pruefsumme_probe
[ 85%] Linking CXX executable meldung_probe
[ 88%] Linking CXX executable werte_probe
[ 88%] Built target meldung_probe
[ 88%] Built target werte_probe
[ 91%] Linking CXX executable schritt_probe
[ 91%] Built target schritt_probe
[ 94%] Linking CXX executable schreiber_probe
[ 94%] Built target schreiber_probe
[ 97%] Linking CXX executable zustand_probe
[100%] Linking CXX executable schranken_probe
[100%] Built target zustand_probe
[100%] Built target schranken_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
    Start 1: festkomma_probe
1/9 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: meldung_probe
2/9 Test #2: meldung_probe ....................   Passed    0.01 sec
    Start 3: pruefsumme_probe
3/9 Test #3: pruefsumme_probe .................   Passed    0.01 sec
    Start 4: schranken_probe
4/9 Test #4: schranken_probe ..................   Passed    0.01 sec
    Start 5: schreiber_probe
5/9 Test #5: schreiber_probe ..................   Passed    0.01 sec
    Start 6: schritt_probe
6/9 Test #6: schritt_probe ....................   Passed    0.01 sec
    Start 7: werte_probe
7/9 Test #7: werte_probe ......................   Passed    0.01 sec
    Start 8: zufall_probe
8/9 Test #8: zufall_probe .....................   Passed    0.01 sec
    Start 9: zustand_probe
9/9 Test #9: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   0.10 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
[100%] Built target vorrat_verfahren_probe
[100%] Built target vorrat_kernanker_probe
[100%] Built target vorrat_probe
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
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 57%] Built target kontrolle_unveraendert
[ 69%] Built target anker_von_hand
[ 57%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 57%] Built target mut3_ordnung_a5_bis_a1
[ 57%] Built target mut4_kennung_einsbasiert
[ 69%] Built target mut1_dreiwertiger_kern
[ 69%] Built target mut2_gleichstand_an_groessere_kennung
[ 72%] Built target mut7_position_und_lobby_vertauscht
[ 81%] Built target mut8_profil_doppelt_eines_fehlt
[ 90%] Built target anker_gegen_mut2
[100%] Built target mut6_abgelegter_kern_immer_ohne
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/bau
      Start  1: kontrolle_unveraendert
 1/11 Test  #1: kontrolle_unveraendert ..................   Passed    0.00 sec
      Start  2: mut1_dreiwertiger_kern
 2/11 Test  #2: mut1_dreiwertiger_kern ..................   Passed    0.00 sec
      Start  3: mut2_gleichstand_an_groessere_kennung
 3/11 Test  #3: mut2_gleichstand_an_groessere_kennung ...   Passed    0.00 sec
      Start  4: mut3_ordnung_a5_bis_a1
 4/11 Test  #4: mut3_ordnung_a5_bis_a1 ..................   Passed    0.00 sec
      Start  5: mut4_kennung_einsbasiert
 5/11 Test  #5: mut4_kennung_einsbasiert ................   Passed    0.00 sec
      Start  6: mut5_hebel_und_sichtbarkeit_im_kern
 6/11 Test  #6: mut5_hebel_und_sichtbarkeit_im_kern .....   Passed    0.00 sec
      Start  7: mut6_abgelegter_kern_immer_ohne
 7/11 Test  #7: mut6_abgelegter_kern_immer_ohne .........   Passed    0.00 sec
      Start  8: mut7_position_und_lobby_vertauscht
 8/11 Test  #8: mut7_position_und_lobby_vertauscht ......   Passed    0.00 sec
      Start  9: mut8_profil_doppelt_eines_fehlt
 9/11 Test  #9: mut8_profil_doppelt_eines_fehlt .........   Passed    0.00 sec
      Start 10: anker_von_hand
10/11 Test #10: anker_von_hand ..........................   Passed    0.00 sec
      Start 11: anker_gegen_mut2
11/11 Test #11: anker_gegen_mut2 ........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 11

Total Test time (real) =   0.03 sec
```

## `cmake -S` -- ok (Code 0)

```
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
1/1 Test #1: belegstellen_riegel ..............   Passed    0.37 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.37 sec
```
