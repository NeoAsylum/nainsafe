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
[ 20%] Building CXX object kern/CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 20%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 30%] Linking CXX static library libkern.a
[ 40%] Linking CXX static library libkern_geprueft.a
[ 50%] Built target kern
[ 60%] Built target kern_geprueft
[ 70%] Building CXX object kern/CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 80%] Linking CXX executable festkomma_probe
[ 90%] Built target festkomma_probe
[100%] Linking CXX executable pruefsumme_probe
[100%] Built target pruefsumme_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
    Start 1: festkomma_probe
1/2 Test #1: festkomma_probe ..................   Passed    0.02 sec
    Start 2: pruefsumme_probe
2/2 Test #2: pruefsumme_probe .................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.03 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 20%] Building CXX object CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 20%] Building CXX object CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 30%] Linking CXX static library libkern.a
[ 40%] Linking CXX static library libkern_geprueft.a
[ 50%] Built target kern
[ 60%] Built target kern_geprueft
[ 70%] Building CXX object CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 80%] Linking CXX executable festkomma_probe
[ 90%] Built target festkomma_probe
[100%] Linking CXX executable pruefsumme_probe
[100%] Built target pruefsumme_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
    Start 1: festkomma_probe
1/2 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/2 Test #2: pruefsumme_probe .................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.02 sec
```
