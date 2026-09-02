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
[ 50%] Built target kern_geprueft
[ 50%] Built target kern
[ 75%] Built target pruefsumme_probe
[ 75%] Built target festkomma_probe
[ 75%] Built target schreiber_probe
[100%] Built target zustand_probe
[100%] Built target zufall_probe
[100%] Built target schranken_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
    Start 1: festkomma_probe
1/6 Test #1: festkomma_probe ..................   Passed    0.02 sec
    Start 2: pruefsumme_probe
2/6 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: schranken_probe
3/6 Test #3: schranken_probe ..................   Passed    0.01 sec
    Start 4: schreiber_probe
4/6 Test #4: schreiber_probe ..................   Passed    0.01 sec
    Start 5: zufall_probe
5/6 Test #5: zufall_probe .....................   Passed    0.01 sec
    Start 6: zustand_probe
6/6 Test #6: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.09 sec
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
[ 66%] Built target pruefsumme_probe
[ 66%] Built target festkomma_probe
[ 91%] Built target zustand_probe
[ 91%] Built target schranken_probe
[ 91%] Built target zufall_probe
[100%] Built target schreiber_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
    Start 1: festkomma_probe
1/6 Test #1: festkomma_probe ..................   Passed    0.01 sec
    Start 2: pruefsumme_probe
2/6 Test #2: pruefsumme_probe .................   Passed    0.01 sec
    Start 3: schranken_probe
3/6 Test #3: schranken_probe ..................   Passed    0.01 sec
    Start 4: schreiber_probe
4/6 Test #4: schreiber_probe ..................   Passed    0.01 sec
    Start 5: zufall_probe
5/6 Test #5: zufall_probe .....................   Passed    0.01 sec
    Start 6: zustand_probe
6/6 Test #6: zustand_probe ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.07 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
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
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
No tests were found!!!
```
