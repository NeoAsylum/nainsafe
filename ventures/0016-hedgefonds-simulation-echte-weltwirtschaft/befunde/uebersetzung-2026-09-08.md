---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-08
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
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand
[ 10%] Built target pruefstand_geprueft
[  9%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 13%] Built target zahlwort_riegel
[ 19%] Built target bezeichner_riegel
[ 19%] Built target mutationstreiber
[ 21%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 30%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 34%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 39%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 39%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 39%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 40%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 43%] Built target vorrat_kernanker_probe
[ 45%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 46%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 50%] Built target vorrat_probe
[ 53%] Built target vorrat_verfahren_probe
[ 54%] Linking CXX static library libkern_geprueft.a
[ 57%] Built target kern_geprueft
[ 59%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 60%] Linking CXX executable pruefsumme_probe
[ 62%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 63%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 65%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 66%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 69%] Linking CXX executable zufall_probe
[ 69%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 74%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 75%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 77%] Linking CXX static library libkern.a
[ 78%] Built target pruefsumme_probe
[ 80%] Built target zufall_probe
[ 83%] Built target kern
[ 84%] Linking CXX executable meldung_probe
[ 84%] Built target meldung_probe
[ 86%] Linking CXX executable festkomma_probe
[ 86%] Built target festkomma_probe
[ 87%] Linking CXX executable schreiber_probe
[ 87%] Built target schreiber_probe
[ 89%] Linking CXX executable schranken_probe
[ 90%] Linking CXX executable zustand_probe
[ 90%] Built target schranken_probe
[ 92%] Linking CXX executable werte_probe
[ 92%] Built target werte_probe
[ 92%] Built target zustand_probe
[ 93%] Linking CXX executable aktion_probe
[ 95%] Linking CXX executable verlauf_probe
[ 95%] Built target aktion_probe
[ 96%] Linking CXX executable schritt_probe
[ 96%] Built target verlauf_probe
[ 96%] Built target schritt_probe
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: aktion_probe
 1/26 Test  #1: aktion_probe .....................   Passed    0.02 sec
      Start  2: festkomma_probe
 2/26 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/26 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/26 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/26 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/26 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/26 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/26 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/26 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/26 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/26 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/26 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: wandschranke
13/26 Test #13: wandschranke .....................   Passed    0.42 sec
      Start 14: vorrat_kernanker_probe
14/26 Test #14: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 15: vorrat_probe
15/26 Test #15: vorrat_probe .....................   Passed    0.01 sec
      Start 16: vorrat_verfahren_probe
16/26 Test #16: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 17: belegstellen_riegel
17/26 Test #17: belegstellen_riegel ..............   Passed    1.12 sec
      Start 18: belegstellen_messung
18/26 Test #18: belegstellen_messung .............   Passed   30.79 sec
      Start 19: belegstellen_wortabstand
19/26 Test #19: belegstellen_wortabstand .........   Passed   17.05 sec
      Start 20: belegstellen_sammelordnung
20/26 Test #20: belegstellen_sammelordnung .......   Passed    5.65 sec
      Start 21: belegstellen_kopfzahlen
21/26 Test #21: belegstellen_kopfzahlen ..........   Passed   15.74 sec
      Start 22: bezeichner_riegel
22/26 Test #22: bezeichner_riegel ................   Passed    0.43 sec
      Start 23: schlussriegel_nachbau
23/26 Test #23: schlussriegel_nachbau ............   Passed    0.50 sec
      Start 24: zahlwort_riegel
24/26 Test #24: zahlwort_riegel ..................   Passed    0.05 sec
      Start 25: zahlwort_reihen
25/26 Test #25: zahlwort_reihen ..................   Passed    0.13 sec
      Start 26: zahlwort_messung
26/26 Test #26: zahlwort_messung .................   Passed   18.34 sec

100% tests passed, 0 tests failed out of 26

Total Test time (real) =  90.50 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 242 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  2%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[  8%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 15%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 19%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 19%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 21%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/aktion.cpp.o
[ 26%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 28%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 30%] Building CXX object CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 32%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 34%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 36%] Linking CXX static library libkern_geprueft.a
[ 41%] Built target kern_geprueft
[ 45%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 45%] Building CXX object CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 47%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 50%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 54%] Linking CXX executable zufall_probe
[ 56%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 58%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 63%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 65%] Linking CXX executable pruefsumme_probe
[ 67%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 69%] Built target zufall_probe
[ 71%] Built target pruefsumme_probe
[ 73%] Linking CXX static library libkern.a
[ 76%] Linking CXX executable festkomma_probe
[ 78%] Linking CXX executable meldung_probe
[ 82%] Built target kern
[ 82%] Built target festkomma_probe
[ 82%] Built target meldung_probe
[ 84%] Linking CXX executable schreiber_probe
[ 86%] Linking CXX executable zustand_probe
[ 86%] Built target schreiber_probe
[ 89%] Linking CXX executable schranken_probe
[ 89%] Built target zustand_probe
[ 89%] Built target schranken_probe
[ 91%] Linking CXX executable aktion_probe
[ 91%] Built target aktion_probe
[ 93%] Linking CXX executable werte_probe
[ 93%] Built target werte_probe
[ 95%] Linking CXX executable verlauf_probe
[ 95%] Built target verlauf_probe
[ 97%] Linking CXX executable schritt_probe
[ 97%] Built target schritt_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: aktion_probe
 1/13 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/13 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/13 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/13 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/13 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/13 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/13 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/13 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/13 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/13 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/13 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/13 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: wandschranke
13/13 Test #13: wandschranke .....................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 13

Total Test time (real) =   0.64 sec
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
[ 50%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
[100%] Built target vorrat_kernanker_probe
[100%] Built target vorrat_probe
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
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.1s)
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
1/5 Test #1: belegstellen_riegel ..............   Passed    1.12 sec
    Start 2: belegstellen_messung
2/5 Test #2: belegstellen_messung .............   Passed   31.16 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........   Passed   17.11 sec
    Start 4: belegstellen_sammelordnung
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.66 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........   Passed   15.84 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =  70.89 sec
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.42 sec
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.50 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.50 sec
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
2/3 Test #2: zahlwort_reihen ..................   Passed    0.13 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................   Passed   18.38 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.55 sec
```
