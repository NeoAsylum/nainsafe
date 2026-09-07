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
-- Configuring done (0.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand
[ 27%] Built target mutationstreiber
[ 33%] Built target kern_geprueft
[ 48%] Built target bezeichner_riegel
[ 48%] Built target kern
[ 46%] Built target pruefstand_geprueft
[ 50%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 53%] Built target zahlwort_riegel
[ 56%] Built target meldung_probe
[ 59%] Built target pruefsumme_probe
[ 62%] Built target aktion_probe
[ 65%] Built target schranken_probe
[ 68%] Built target verlauf_probe
[ 71%] Built target schritt_probe
[ 74%] Built target schreiber_probe
[ 77%] Built target zustand_probe
[ 83%] Built target vorrat_kernanker_probe
[ 86%] Built target werte_probe
[ 89%] Built target festkomma_probe
[ 92%] Built target zustandsausgabe_probe
[ 92%] Built target zufall_probe
[ 95%] Built target vorrat_probe
[ 98%] Built target vorrat_verfahren_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: aktion_probe
 1/24 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/24 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/24 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/24 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/24 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/24 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/24 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/24 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/24 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/24 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/24 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/24 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: wandschranke
13/24 Test #13: wandschranke .....................   Passed    0.42 sec
      Start 14: vorrat_kernanker_probe
14/24 Test #14: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 15: vorrat_probe
15/24 Test #15: vorrat_probe .....................   Passed    0.01 sec
      Start 16: vorrat_verfahren_probe
16/24 Test #16: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 17: belegstellen_riegel
17/24 Test #17: belegstellen_riegel ..............   Passed    1.02 sec
      Start 18: belegstellen_messung
18/24 Test #18: belegstellen_messung .............   Passed   30.66 sec
      Start 19: belegstellen_wortabstand
19/24 Test #19: belegstellen_wortabstand .........   Passed   17.22 sec
      Start 20: bezeichner_riegel
20/24 Test #20: bezeichner_riegel ................   Passed    0.38 sec
      Start 21: schlussriegel_nachbau
21/24 Test #21: schlussriegel_nachbau ............   Passed    0.48 sec
      Start 22: zahlwort_riegel
22/24 Test #22: zahlwort_riegel ..................   Passed    0.04 sec
      Start 23: zahlwort_reihen
23/24 Test #23: zahlwort_reihen ..................   Passed    0.13 sec
      Start 24: zahlwort_messung
24/24 Test #24: zahlwort_messung .................   Passed   19.21 sec

100% tests passed, 0 tests failed out of 24

Total Test time (real) =  69.83 sec
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
[ 47%] Built target kern_geprueft
[ 47%] Built target kern
[ 52%] Built target aktion_probe
[ 56%] Built target meldung_probe
[ 60%] Built target schranken_probe
[ 67%] Built target schreiber_probe
[ 69%] Built target pruefsumme_probe
[ 73%] Built target festkomma_probe
[ 78%] Built target schritt_probe
[ 82%] Built target verlauf_probe
[ 91%] Built target werte_probe
[ 91%] Built target zufall_probe
[ 95%] Built target zustand_probe
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
11/13 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/13 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: wandschranke
13/13 Test #13: wandschranke .....................   Passed    0.43 sec

100% tests passed, 0 tests failed out of 13

Total Test time (real) =   0.66 sec
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
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
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
1/3 Test #1: belegstellen_riegel ..............   Passed    1.04 sec
    Start 2: belegstellen_messung
2/3 Test #2: belegstellen_messung .............   Passed   30.84 sec
    Start 3: belegstellen_wortabstand
3/3 Test #3: belegstellen_wortabstand .........   Passed   17.23 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  49.11 sec
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.38 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.38 sec
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.48 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.48 sec
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
3/3 Test #3: zahlwort_messung .................   Passed   18.71 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.88 sec
```
