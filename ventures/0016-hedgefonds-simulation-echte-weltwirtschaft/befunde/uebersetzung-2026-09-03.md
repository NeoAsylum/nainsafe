---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-03
bauart: cmake
manifeste: 4
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
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 10%] Built target pruefstand
[ 18%] Built target pruefstand_geprueft
[ 34%] Built target kern
[ 52%] Built target kern_geprueft
[ 68%] Built target schritt_probe
[ 68%] Built target schranken_probe
[ 68%] Built target festkomma_probe
[ 78%] Built target schreiber_probe
[ 78%] Built target zufall_probe
[ 86%] Built target vorrat_verfahren_probe
[ 89%] Built target vorrat_probe
[ 94%] Built target zustand_probe
[100%] Built target pruefsumme_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
    Start 1: festkomma_probe
1/9 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/9 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: schranken_probe
3/9 Test #3: schranken_probe ..................   Passed    0.01 sec
    Start 4: schreiber_probe
4/9 Test #4: schreiber_probe ..................   Passed    0.01 sec
    Start 5: schritt_probe
5/9 Test #5: schritt_probe ....................   Passed    0.01 sec
    Start 6: zufall_probe
6/9 Test #6: zufall_probe .....................   Passed    0.01 sec
    Start 7: zustand_probe
7/9 Test #7: zustand_probe ....................   Passed    0.01 sec
    Start 8: vorrat_probe
8/9 Test #8: vorrat_probe .....................   Passed    0.01 sec
    Start 9: vorrat_verfahren_probe
9/9 Test #9: vorrat_verfahren_probe ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   0.10 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Built target kern
[ 50%] Built target kern_geprueft
[ 64%] Built target schranken_probe
[ 64%] Built target pruefsumme_probe
[ 78%] Built target festkomma_probe
[ 78%] Built target schritt_probe
[ 85%] Built target zufall_probe
[ 92%] Built target schreiber_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
    Start 1: festkomma_probe
1/7 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/7 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: schranken_probe
3/7 Test #3: schranken_probe ..................   Passed    0.01 sec
    Start 4: schreiber_probe
4/7 Test #4: schreiber_probe ..................   Passed    0.01 sec
    Start 5: schritt_probe
5/7 Test #5: schritt_probe ....................   Passed    0.01 sec
    Start 6: zufall_probe
6/7 Test #6: zufall_probe .....................   Passed    0.01 sec
    Start 7: zustand_probe
7/7 Test #7: zustand_probe ....................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.09 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 60%] Built target pruefstand
[ 60%] Built target pruefstand_geprueft
[100%] Built target vorrat_verfahren_probe
[100%] Built target vorrat_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
    Start 1: vorrat_probe
1/2 Test #1: vorrat_probe .....................   Passed    0.01 sec
    Start 2: vorrat_verfahren_probe
2/2 Test #2: vorrat_verfahren_probe ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.02 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/bau
```

## `cmake --build` -- ok (Code 0)

```
[  6%] Building CXX object CMakeFiles/kontrolle_unveraendert.dir/mutant.cpp.o
[  6%] Building CXX object CMakeFiles/mut4_kennung_einsbasiert.dir/mutant.cpp.o
[  9%] Building CXX object CMakeFiles/kontrolle_unveraendert.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 12%] Building CXX object CMakeFiles/mut2_gleichstand_an_groessere_kennung.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 15%] Building CXX object CMakeFiles/mut5_hebel_und_sichtbarkeit_im_kern.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 18%] Building CXX object CMakeFiles/anker_von_hand.dir/anker.cpp.o
[ 21%] Building CXX object CMakeFiles/mut3_ordnung_a5_bis_a1.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 24%] Building CXX object CMakeFiles/mut4_kennung_einsbasiert.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 27%] Building CXX object CMakeFiles/mut1_dreiwertiger_kern.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 30%] Building CXX object CMakeFiles/mut8_profil_doppelt_eines_fehlt.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 36%] Building CXX object CMakeFiles/anker_gegen_mut2.dir/anker.cpp.o
[ 36%] Building CXX object CMakeFiles/mut6_abgelegter_kern_immer_ohne.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 39%] Building CXX object CMakeFiles/mut1_dreiwertiger_kern.dir/mutant.cpp.o
[ 42%] Building CXX object CMakeFiles/mut8_profil_doppelt_eines_fehlt.dir/mutant.cpp.o
[ 45%] Building CXX object CMakeFiles/mut7_position_und_lobby_vertauscht.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_probe.cpp.o
[ 48%] Building CXX object CMakeFiles/anker_von_hand.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/vorrat.cpp.o
[ 51%] Building CXX object CMakeFiles/mut2_gleichstand_an_groessere_kennung.dir/mutant.cpp.o
[ 54%] Building CXX object CMakeFiles/mut7_position_und_lobby_vertauscht.dir/mutant.cpp.o
[ 57%] Building CXX object CMakeFiles/mut5_hebel_und_sichtbarkeit_im_kern.dir/mutant.cpp.o
[ 63%] Building CXX object CMakeFiles/mut6_abgelegter_kern_immer_ohne.dir/mutant.cpp.o
[ 63%] Building CXX object CMakeFiles/anker_gegen_mut2.dir/mutant.cpp.o
[ 66%] Building CXX object CMakeFiles/mut3_ordnung_a5_bis_a1.dir/mutant.cpp.o
[ 69%] Linking CXX executable mut5_hebel_und_sichtbarkeit_im_kern
[ 72%] Linking CXX executable mut2_gleichstand_an_groessere_kennung
[ 75%] Linking CXX executable mut1_dreiwertiger_kern
[ 78%] Linking CXX executable anker_von_hand
[ 81%] Linking CXX executable mut8_profil_doppelt_eines_fehlt
[ 84%] Linking CXX executable mut7_position_und_lobby_vertauscht
[ 87%] Linking CXX executable mut3_ordnung_a5_bis_a1
[ 90%] Linking CXX executable kontrolle_unveraendert
[ 93%] Linking CXX executable mut6_abgelegter_kern_immer_ohne
[ 93%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 96%] Linking CXX executable anker_gegen_mut2
[ 96%] Built target mut2_gleichstand_an_groessere_kennung
[ 96%] Built target anker_von_hand
[100%] Linking CXX executable mut4_kennung_einsbasiert
[100%] Built target mut1_dreiwertiger_kern
[100%] Built target mut6_abgelegter_kern_immer_ohne
[100%] Built target mut3_ordnung_a5_bis_a1
[100%] Built target mut7_position_und_lobby_vertauscht
[100%] Built target mut8_profil_doppelt_eines_fehlt
[100%] Built target kontrolle_unveraendert
[100%] Built target anker_gegen_mut2
[100%] Built target mut4_kennung_einsbasiert
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

Total Test time (real) =   0.02 sec
```
