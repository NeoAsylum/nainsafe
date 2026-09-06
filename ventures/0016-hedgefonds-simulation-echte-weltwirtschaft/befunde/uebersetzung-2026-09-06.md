---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-06
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
-- Configuring done (0.1s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  6%] Built target bezeichner_riegel
[  6%] Built target belegstellen_riegel
[  9%] Built target mutationstreiber
[ 16%] Built target pruefstand_geprueft
[ 30%] Built target kern_geprueft
[ 37%] Built target pruefstand
[ 36%] Built target zahlwort_riegel
[ 54%] Built target kern
[ 57%] Built target meldung_probe
[ 63%] Built target vorrat_probe
[ 63%] Built target festkomma_probe
[ 66%] Built target vorrat_kernanker_probe
[ 69%] Built target vorrat_verfahren_probe
[ 72%] Built target pruefsumme_probe
[ 75%] Built target aktion_probe
[ 78%] Built target schranken_probe
[ 83%] Built target schreiber_probe
[ 84%] Built target schritt_probe
[ 87%] Built target verlauf_probe
[ 90%] Built target werte_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Built target zufall_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: aktion_probe
 1/19 Test  #1: aktion_probe .....................   Passed    0.02 sec
      Start  2: festkomma_probe
 2/19 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: meldung_probe
 3/19 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/19 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/19 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/19 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/19 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: verlauf_probe
 8/19 Test  #8: verlauf_probe ....................   Passed    0.02 sec
      Start  9: werte_probe
 9/19 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/19 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/19 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/19 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: vorrat_kernanker_probe
13/19 Test #13: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 14: vorrat_probe
14/19 Test #14: vorrat_probe .....................   Passed    0.01 sec
      Start 15: vorrat_verfahren_probe
15/19 Test #15: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 16: belegstellen_riegel
16/19 Test #16: belegstellen_riegel ..............   Passed    7.51 sec
      Start 17: bezeichner_riegel
17/19 Test #17: bezeichner_riegel ................   Passed    0.37 sec
      Start 18: schlussriegel_nachbau
18/19 Test #18: schlussriegel_nachbau ............   Passed    0.55 sec
      Start 19: zahlwort_riegel
19/19 Test #19: zahlwort_riegel ..................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 19

Total Test time (real) =   8.74 sec
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
[ 23%] Built target kern
[ 47%] Built target kern_geprueft
[ 52%] Built target pruefsumme_probe
[ 67%] Built target schranken_probe
[ 67%] Built target meldung_probe
[ 67%] Built target aktion_probe
[ 69%] Built target schritt_probe
[ 73%] Built target zustandsausgabe_probe
[ 78%] Built target festkomma_probe
[ 82%] Built target zufall_probe
[ 86%] Built target werte_probe
[ 91%] Built target zustand_probe
[ 95%] Built target schreiber_probe
[100%] Built target verlauf_probe
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
11/12 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/12 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec

100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.24 sec
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
[ 66%] Built target vorrat_probe
[ 83%] Built target vorrat_verfahren_probe
[100%] Built target vorrat_kernanker_probe
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
1/1 Test #1: belegstellen_riegel ..............   Passed    7.64 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   7.64 sec
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.50 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.50 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.0s)
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
1/1 Test #1: zahlwort_riegel ..................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.03 sec
```
