---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-04
bauart: cmake
manifeste: 5
ergebnis: fehler
---

# Der Compiler hat gesprochen: fehler

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
-- Warnsatz-Schlussriegel: 16 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 15%] Built target pruefstand_geprueft
[  9%] Built target belegstellen_riegel
[ 18%] Built target pruefstand
[ 34%] Built target kern
[ 50%] Built target kern_geprueft
[ 54%] Built target vorrat_kernanker_probe
[ 59%] Built target schranken_probe
[ 68%] Built target meldung_probe
[ 68%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 72%] Built target vorrat_probe
[ 75%] Built target pruefsumme_probe
[ 79%] Built target zustand_probe
[ 84%] Built target schreiber_probe
[ 88%] Built target vorrat_verfahren_probe
[ 93%] Built target schritt_probe
[ 97%] Built target zufall_probe
[100%] Linking CXX executable festkomma_probe
[100%] Built target festkomma_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/12 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/12 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/12 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/12 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/12 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/12 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: zufall_probe
 7/12 Test  #7: zufall_probe .....................   Passed    0.01 sec
      Start  8: zustand_probe
 8/12 Test  #8: zustand_probe ....................   Passed    0.01 sec
      Start  9: vorrat_kernanker_probe
 9/12 Test  #9: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 10: vorrat_probe
10/12 Test #10: vorrat_probe .....................   Passed    0.01 sec
      Start 11: vorrat_verfahren_probe
11/12 Test #11: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 12: belegstellen_riegel
12/12 Test #12: belegstellen_riegel ..............***Failed    0.03 sec

4 Verweis(e) zeigen mit einer Zeilennummer in eine fremde Datei:

  kern/include/kern/zustand.hpp:224  -> daten/adressen.md
      :477`), `daten/adressen.md` Zeile 255
  kern/test/schranken_probe.cpp:423  -> parameter.toml
      ///   parameter.toml Zeile 304
  kern/test/schranken_probe.cpp:424  -> parameter.toml
      ///   parameter.toml Zeile 205
  kern/test/schranken_probe.cpp:425  -> parameter.toml
      ///   parameter.toml Zeile 250

Eine Zeilennummer in eine fremde Datei wandert, ohne dass jemand etwas tut.
Sie wird ersetzt -- durch einen Bezeichner, eine Abschnittsueberschrift oder eine
Schluesselzeile im Wortlaut --, nicht ausgenommen und nicht nachgezogen.
belegstellen_riegel: 37 Bauquellen gelesen, 12 Zeilenverweise getroffen, davon 4 mit Dateinamen daneben.


92% tests passed, 1 tests failed out of 12

Total Test time (real) =   0.15 sec

The following tests FAILED:
	 12 - belegstellen_riegel (Failed)
Errors while running CTest
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
[ 10%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 23%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 16%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 26%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 30%] Linking CXX static library libkern.a
[ 33%] Linking CXX static library libkern_geprueft.a
[ 40%] Built target kern
[ 46%] Built target kern_geprueft
[ 53%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 53%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 60%] Linking CXX executable pruefsumme_probe
[ 63%] Linking CXX executable zufall_probe
[ 66%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 70%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 73%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 76%] Built target zufall_probe
[ 80%] Built target pruefsumme_probe
[ 83%] Linking CXX executable festkomma_probe
[ 86%] Linking CXX executable meldung_probe
[ 86%] Built target festkomma_probe
[ 86%] Built target meldung_probe
[ 90%] Linking CXX executable schritt_probe
[ 90%] Built target schritt_probe
[ 93%] Linking CXX executable schreiber_probe
[ 93%] Built target schreiber_probe
[ 96%] Linking CXX executable zustand_probe
[100%] Linking CXX executable schranken_probe
[100%] Built target zustand_probe
[100%] Built target schranken_probe
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
8/8 Test #8: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.09 sec
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
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[ 41%] Linking CXX static library libpruefstand.a
[ 50%] Linking CXX static library libpruefstand_geprueft.a
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[ 66%] Building CXX object CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 83%] Linking CXX executable vorrat_probe
[ 91%] Linking CXX executable vorrat_kernanker_probe
[ 91%] Built target vorrat_probe
[ 91%] Built target vorrat_kernanker_probe
[100%] Linking CXX executable vorrat_verfahren_probe
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
[ 18%] Built target mut3_ordnung_a5_bis_a1
[ 18%] Built target mut6_abgelegter_kern_immer_ohne
[ 27%] Built target mut2_gleichstand_an_groessere_kennung
[ 36%] Built target mut7_position_und_lobby_vertauscht
[ 69%] Built target kontrolle_unveraendert
[ 69%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 72%] Built target mut8_profil_doppelt_eines_fehlt
[ 69%] Built target mut1_dreiwertiger_kern
[ 81%] Built target anker_von_hand
[ 90%] Built target mut4_kennung_einsbasiert
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
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............***Failed    0.02 sec

4 Verweis(e) zeigen mit einer Zeilennummer in eine fremde Datei:

  kern/include/kern/zustand.hpp:224  -> daten/adressen.md
      :477`), `daten/adressen.md` Zeile 255
  kern/test/schranken_probe.cpp:423  -> parameter.toml
      ///   parameter.toml Zeile 304
  kern/test/schranken_probe.cpp:424  -> parameter.toml
      ///   parameter.toml Zeile 205
  kern/test/schranken_probe.cpp:425  -> parameter.toml
      ///   parameter.toml Zeile 250

Eine Zeilennummer in eine fremde Datei wandert, ohne dass jemand etwas tut.
Sie wird ersetzt -- durch einen Bezeichner, eine Abschnittsueberschrift oder eine
Schluesselzeile im Wortlaut --, nicht ausgenommen und nicht nachgezogen.
belegstellen_riegel: 37 Bauquellen gelesen, 12 Zeilenverweise getroffen, davon 4 mit Dateinamen daneben.


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.03 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
Errors while running CTest
```
