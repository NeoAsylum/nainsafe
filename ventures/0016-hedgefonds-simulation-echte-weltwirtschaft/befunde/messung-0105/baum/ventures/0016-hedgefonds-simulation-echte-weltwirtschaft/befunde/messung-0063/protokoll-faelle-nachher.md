# Wegwerf-Baeume zu 0063 -- Fassung `nachher`

Kette: `/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake`

## 1. `a_shell` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=1**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring incomplete, errors occurred!
CMake Error at /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:398 (message):
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/a_shell
        hebt den Satz wieder auf: -Wno-error -w
        im Eintrag:               SHELL:-Wno-error -w

  `-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus.
  Das Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder
  erwartete Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine
  Pruefung weiter oben sieht deshalb nichts.

  Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und
  benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz
  daneben, warum.  Das bleibt zugelassen.  Pauschal abgeschaltet wird nichts.
Call Stack (most recent call first):
  /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:452 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

Kein Bau: die Konfiguration ist schon abgebrochen.

## 2. `b_genex` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=1**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring incomplete, errors occurred!
CMake Error at /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:398 (message):
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/b_genex
        hebt den Satz wieder auf: -w
        im Eintrag:               $<1:-w>

  `-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus.
  Das Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder
  erwartete Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine
  Pruefung weiter oben sieht deshalb nichts.

  Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und
  benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz
  daneben, warum.  Das bleibt zugelassen.  Pauschal abgeschaltet wird nichts.
Call Stack (most recent call first):
  /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:452 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

Kein Bau: die Konfiguration ist schon abgebrochen.

## 3. `c_genex_config` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=1**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring incomplete, errors occurred!
CMake Error at /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:398 (message):
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/c_genex_config
        hebt den Satz wieder auf: -w
        im Eintrag:               $<$<CONFIG:Release>:-w>

  `-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus.
  Das Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder
  erwartete Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine
  Pruefung weiter oben sieht deshalb nichts.

  Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und
  benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz
  daneben, warum.  Das bleibt zugelassen.  Pauschal abgeschaltet wird nichts.
Call Stack (most recent call first):
  /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:452 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

## 4. `c_genex_config` -- -DCMAKE_BUILD_TYPE=Release

`cmake -S` **CODE=1**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring incomplete, errors occurred!
CMake Error at /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:398 (message):
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/c_genex_config
        hebt den Satz wieder auf: -w
        im Eintrag:               $<$<CONFIG:Release>:-w>

  `-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus.
  Das Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder
  erwartete Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine
  Pruefung weiter oben sieht deshalb nichts.

  Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und
  benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz
  daneben, warum.  Das bleibt zugelassen.  Pauschal abgeschaltet wird nichts.
Call Stack (most recent call first):
  /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:452 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

Kein Bau: die Konfiguration ist schon abgebrochen.

## 5. `d_0060` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=1**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring incomplete, errors occurred!
CMake Error at /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:398 (message):
  Diese Ziele tragen den Warnsatz und schalten ihn im selben Atemzug wieder
  ab:

    z (STATIC_LIBRARY) in /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/d_0060
        hebt den Satz wieder auf: -Wno-error -w

  `-w` und `-Wno-error` heben den ganzen Satz auf, nicht eine Warnung daraus.
  Das Ziel uebersetzt damit gruen und ohne jede Diagnose, waehrend jeder
  erwartete Schalter ordentlich in `COMPILE_OPTIONS` steht -- der Riegel eine
  Pruefung weiter oben sieht deshalb nichts.

  Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln und
  benennt sie dabei: `-Wno-conversion` an genau diesem Ziel, mit einem Satz
  daneben, warum.  Das bleibt zugelassen.  Pauschal abgeschaltet wird nichts.
Call Stack (most recent call first):
  /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake:452 (fabrik_schlussriegel)
  CMakeLists.txt:DEFERRED
```

## 6. `e_einzeln` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=0**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/e_einzeln/bau-nachher-6
```

`cmake --build` **CODE=0**

```
[ 50%] Building CXX object CMakeFiles/z.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/z.cpp.o
[100%] Linking CXX static library libz.a
[100%] Built target z
```

## 7. `f_ohne` -- -DCMAKE_BUILD_TYPE=RelWithDebInfo

`cmake -S` **CODE=0**

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/f_ohne/bau-nachher-7
```

`cmake --build` **CODE=2**

```
[ 50%] Building CXX object CMakeFiles/z.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/z.cpp.o
/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/z.cpp: In function ‘int f(double)’:
/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/z.cpp:4:26: error: conversion from ‘double’ to ‘int’ may change value [-Werror=float-conversion]
    4 | int f(double d){ int i = d; return i; }
      |                          ^
cc1plus: all warnings being treated as errors
gmake[2]: *** [CMakeFiles/z.dir/build.make:79: CMakeFiles/z.dir/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0063/z.cpp.o] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:87: CMakeFiles/z.dir/all] Error 2
gmake: *** [Makefile:91: all] Error 2
```

