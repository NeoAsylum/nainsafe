---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-02
bauart: cmake
manifeste: 2
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
-- Mitglied 'pruefstand' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 22%] Building CXX object kern/CMakeFiles/kern.dir/src/zufall.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 27%] Linking CXX static library libkern.a
[ 38%] Built target kern
[ 44%] Linking CXX static library libkern_geprueft.a
[ 55%] Built target kern_geprueft
[ 61%] Building CXX object kern/CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 66%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 72%] Linking CXX executable festkomma_probe
[ 77%] Linking CXX executable pruefsumme_probe
[ 88%] Built target pruefsumme_probe
[ 88%] Built target festkomma_probe
[ 94%] Linking CXX executable zustand_probe
[100%] Linking CXX executable zufall_probe
[100%] Built target zustand_probe
[100%] Built target zufall_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
    Start 1: festkomma_probe
1/4 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/4 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: zufall_probe
3/4 Test #3: zufall_probe .....................   Passed    0.01 sec
    Start 4: zustand_probe
4/4 Test #4: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.04 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 16%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 16%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 16%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 22%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 27%] Linking CXX static library libkern.a
[ 38%] Built target kern
[ 44%] Linking CXX static library libkern_geprueft.a
[ 55%] Built target kern_geprueft
[ 61%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 77%] Linking CXX executable festkomma_probe
[ 77%] Linking CXX executable pruefsumme_probe
[ 83%] Built target pruefsumme_probe
[ 88%] Built target festkomma_probe
[ 94%] Linking CXX executable zustand_probe
[100%] Linking CXX executable zufall_probe
[100%] Built target zustand_probe
[100%] Built target zufall_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
    Start 1: festkomma_probe
1/4 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/4 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: zufall_probe
3/4 Test #3: zufall_probe .....................   Passed    0.01 sec
    Start 4: zustand_probe
4/4 Test #4: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.04 sec
```
