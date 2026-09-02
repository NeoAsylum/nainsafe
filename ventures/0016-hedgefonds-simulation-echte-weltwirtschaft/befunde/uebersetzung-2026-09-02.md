---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-02
bauart: cmake
manifeste: 3
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
[  5%] Built target pruefstand
[ 11%] Built target pruefstand_geprueft
[ 32%] Built target kern
[ 52%] Built target kern_geprueft
[ 79%] Built target vorrat_probe
[ 79%] Built target schreiber_probe
[ 85%] Built target zustand_probe
[ 79%] Built target schritt_probe
[ 88%] Built target festkomma_probe
[ 88%] Built target pruefsumme_probe
[ 94%] Built target schranken_probe
[100%] Built target zufall_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
    Start 1: festkomma_probe
1/8 Test #1: festkomma_probe ..................   Passed    0.03 sec
    Start 2: pruefsumme_probe
2/8 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: schranken_probe
3/8 Test #3: schranken_probe ..................   Passed    0.01 sec
    Start 4: schreiber_probe
4/8 Test #4: schreiber_probe ..................   Passed    0.01 sec
    Start 5: schritt_probe
5/8 Test #5: schritt_probe ....................   Passed    0.01 sec
    Start 6: zufall_probe
6/8 Test #6: zufall_probe .....................   Passed    0.01 sec
    Start 7: zustand_probe
7/8 Test #7: zustand_probe ....................   Passed    0.02 sec
    Start 8: vorrat_probe
8/8 Test #8: vorrat_probe .....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.12 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 46%] Built target kern
[ 50%] Built target kern_geprueft
[ 64%] Built target zustand_probe
[ 64%] Built target pruefsumme_probe
[ 71%] Built target festkomma_probe
[ 92%] Built target zufall_probe
[ 92%] Built target schreiber_probe
[ 92%] Built target schritt_probe
[100%] Built target schranken_probe
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
[ 66%] Built target pruefstand_geprueft
[ 66%] Built target pruefstand
[100%] Built target vorrat_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
    Start 1: vorrat_probe
1/1 Test #1: vorrat_probe .....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
