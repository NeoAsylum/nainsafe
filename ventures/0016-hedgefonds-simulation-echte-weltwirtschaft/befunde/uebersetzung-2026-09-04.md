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
-- Warnsatz-Schlussriegel: 15 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 14%] Built target pruefstand_geprueft
[ 14%] Built target pruefstand
[ 33%] Built target kern_geprueft
[ 47%] Built target kern
[ 57%] Built target vorrat_probe
[ 57%] Built target vorrat_kernanker_probe
[ 61%] Built target vorrat_verfahren_probe
[ 66%] Built target festkomma_probe
[ 76%] Built target meldung_probe
[ 76%] Built target schranken_probe
[ 85%] Built target pruefsumme_probe
[ 85%] Built target zufall_probe
[ 90%] Built target schritt_probe
[100%] Built target schreiber_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/11 Test  #1: festkomma_probe ..................   Passed    0.03 sec
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

Total Test time (real) =   0.15 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Warnsatz-Schlussriegel: 10 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 46%] Built target kern
[ 46%] Built target kern_geprueft
[ 66%] Built target festkomma_probe
[ 66%] Built target meldung_probe
[ 66%] Built target schranken_probe
[ 80%] Built target zufall_probe
[ 80%] Built target zustand_probe
[ 86%] Built target pruefsumme_probe
[ 93%] Built target schritt_probe
[100%] Built target schreiber_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
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
8/8 Test #8: zustand_probe ....................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.10 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
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
[  9%] Built target mut3_ordnung_a5_bis_a1
[ 45%] Built target mut4_kennung_einsbasiert
[ 45%] Built target kontrolle_unveraendert
[ 36%] Built target mut1_dreiwertiger_kern
[ 45%] Built target mut2_gleichstand_an_groessere_kennung
[ 54%] Built target mut6_abgelegter_kern_immer_ohne
[ 63%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 72%] Built target anker_von_hand
[ 90%] Built target mut8_profil_doppelt_eines_fehlt
[ 90%] Built target mut7_position_und_lobby_vertauscht
[100%] Built target anker_gegen_mut2
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
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
CMake Warning (dev) in CMakeLists.txt:
  No project() command is present.  The top-level CMakeLists.txt file must
  contain a literal, direct call to the project() command.  Add a line of
  code such as

    project(ProjectName)

  near the top of the file, but after cmake_minimum_required().

  CMake is pretending there is a "project(Project)" command on the first
  line.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Warning (dev) in CMakeLists.txt:
  cmake_minimum_required() should be called prior to this top-level project()
  call.  Please see the cmake-commands(7) manual for usage documentation of
  both commands.
This warning is for project developers.  Use -Wno-dev to suppress it.
```

## `cmake --build` -- ok (Code 0)

```

```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
No tests were found!!!
```
