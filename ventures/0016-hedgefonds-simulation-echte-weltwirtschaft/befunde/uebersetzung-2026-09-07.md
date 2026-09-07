---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-07
bauart: cmake
manifeste: 8
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
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 23 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 407 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand_geprueft
[ 10%] Built target pruefstand
[ 12%] Built target bezeichner_riegel
[ 13%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 16%] Built target zahlwort_riegel
[ 19%] Built target mutationstreiber
[ 21%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 30%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 37%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 39%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 40%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 43%] Built target vorrat_kernanker_probe
[ 46%] Built target vorrat_probe
[ 50%] Built target vorrat_verfahren_probe
[ 51%] Linking CXX static library libkern_geprueft.a
[ 56%] Built target kern_geprueft
[ 57%] Linking CXX executable pruefsumme_probe
[ 59%] Linking CXX executable festkomma_probe
[ 60%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 62%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 63%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 65%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 66%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 68%] Linking CXX executable zufall_probe
[ 69%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 71%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 74%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 75%] Built target festkomma_probe
[ 77%] Built target zufall_probe
[ 78%] Built target pruefsumme_probe
[ 80%] Linking CXX executable meldung_probe
[ 81%] Linking CXX static library libkern.a
[ 81%] Built target meldung_probe
[ 86%] Built target kern
[ 87%] Linking CXX executable schreiber_probe
[ 87%] Built target schreiber_probe
[ 89%] Linking CXX executable schritt_probe
[ 89%] Built target schritt_probe
[ 90%] Linking CXX executable schranken_probe
[ 92%] Linking CXX executable zustand_probe
[ 92%] Built target schranken_probe
[ 93%] Linking CXX executable werte_probe
[ 93%] Built target zustand_probe
[ 95%] Linking CXX executable aktion_probe
[ 95%] Built target werte_probe
[ 95%] Built target aktion_probe
[ 96%] Linking CXX executable verlauf_probe
[ 96%] Built target verlauf_probe
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: aktion_probe
 1/21 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/21 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/21 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/21 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/21 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/21 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/21 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/21 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/21 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/21 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/21 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/21 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: vorrat_kernanker_probe
13/21 Test #13: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 14: vorrat_probe
14/21 Test #14: vorrat_probe .....................   Passed    0.01 sec
      Start 15: vorrat_verfahren_probe
15/21 Test #15: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 16: belegstellen_riegel
16/21 Test #16: belegstellen_riegel ..............   Passed    1.03 sec
      Start 17: bezeichner_riegel
17/21 Test #17: bezeichner_riegel ................   Passed    0.37 sec
      Start 18: schlussriegel_nachbau
18/21 Test #18: schlussriegel_nachbau ............   Passed    0.51 sec
      Start 19: zahlwort_riegel
19/21 Test #19: zahlwort_riegel ..................   Passed    0.04 sec
      Start 20: zahlwort_reihen
20/21 Test #20: zahlwort_reihen ..................   Passed    0.13 sec
      Start 21: zahlwort_messung
21/21 Test #21: zahlwort_messung .................   Passed   13.50 sec

100% tests passed, 0 tests failed out of 21

Total Test time (real) =  15.84 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 242 Schaltereintraege.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  2%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[  6%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[  6%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/aktion.cpp.o
[ 13%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 17%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 19%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 21%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 23%] Building CXX object CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 28%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 28%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 30%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 32%] Linking CXX static library libkern_geprueft.a
[ 39%] Built target kern_geprueft
[ 41%] Linking CXX executable festkomma_probe
[ 43%] Linking CXX executable pruefsumme_probe
[ 45%] Building CXX object CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 47%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 50%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 54%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 56%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 58%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 63%] Linking CXX executable zufall_probe
[ 65%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 67%] Built target pruefsumme_probe
[ 69%] Built target festkomma_probe
[ 71%] Built target zufall_probe
[ 73%] Linking CXX static library libkern.a
[ 80%] Built target kern
[ 82%] Linking CXX executable meldung_probe
[ 82%] Built target meldung_probe
[ 84%] Linking CXX executable schritt_probe
[ 86%] Linking CXX executable schranken_probe
[ 89%] Linking CXX executable zustand_probe
[ 91%] Linking CXX executable schreiber_probe
[ 91%] Built target schritt_probe
[ 91%] Built target zustand_probe
[ 91%] Built target schranken_probe
[ 91%] Built target schreiber_probe
[ 93%] Linking CXX executable werte_probe
[ 95%] Linking CXX executable aktion_probe
[ 95%] Built target werte_probe
[ 95%] Built target aktion_probe
[ 97%] Linking CXX executable verlauf_probe
[ 97%] Built target verlauf_probe
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

Total Test time (real) =   0.22 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 89 Schaltereintraege.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 41%] Built target pruefstand_geprueft
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
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: belegstellen_riegel ..............   Passed    0.99 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   1.00 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.36 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.37 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.51 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.51 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target zahlwort_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/3 Test #1: zahlwort_riegel ..................   Passed    0.04 sec
    Start 2: zahlwort_reihen
2/3 Test #2: zahlwort_reihen ..................   Passed    0.12 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................   Passed   13.55 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  13.72 sec
```
