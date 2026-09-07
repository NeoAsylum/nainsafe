---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-07
bauart: cmake
manifeste: 8
ergebnis: fehler
---

# Der Compiler hat gesprochen: fehler

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 23 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 407 Schaltereintraege.
-- Configuring done (0.5s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  3%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[  3%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[  4%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[  6%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[  7%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[  9%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 10%] Building CXX object kern/CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 12%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 13%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 15%] Building CXX object werkzeuge/bezeichner/CMakeFiles/bezeichner_riegel.dir/bezeichner_riegel.cpp.o
[ 16%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 19%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 21%] Building CXX object werkzeuge/zahlwort/CMakeFiles/zahlwort_riegel.dir/zahlwort_riegel.cpp.o
[ 22%] Building CXX object werkzeuge/mutation/CMakeFiles/mutationstreiber.dir/mutationslauf.cpp.o
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 30%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 34%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern.dir/src/zufall.cpp.o
[ 37%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 39%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 40%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 42%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 43%] Linking CXX static library libpruefstand.a
[ 43%] Built target pruefstand
[ 45%] Linking CXX static library libpruefstand_geprueft.a
[ 45%] Built target pruefstand_geprueft
[ 46%] Building CXX object pruefstand/CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 48%] Building CXX object pruefstand/CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 50%] Building CXX object pruefstand/CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 51%] Linking CXX executable vorrat_probe
[ 51%] Built target vorrat_probe
[ 53%] Linking CXX executable vorrat_kernanker_probe
[ 53%] Built target vorrat_kernanker_probe
[ 54%] Linking CXX executable vorrat_verfahren_probe
[ 54%] Built target vorrat_verfahren_probe
[ 56%] Linking CXX static library libkern_geprueft.a
[ 56%] Built target kern_geprueft
[ 57%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 59%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 60%] Building CXX object kern/CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 62%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 63%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 65%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 68%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 68%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 69%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 74%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 75%] Linking CXX executable zufall_probe
[ 75%] Built target zufall_probe
[ 77%] Linking CXX executable pruefsumme_probe
[ 78%] Linking CXX executable meldung_probe
[ 80%] Linking CXX static library libkern.a
[ 80%] Built target pruefsumme_probe
[ 80%] Built target kern
[ 80%] Built target meldung_probe
[ 81%] Linking CXX executable festkomma_probe
[ 81%] Built target festkomma_probe
[ 83%] Linking CXX executable schranken_probe
[ 84%] Linking CXX executable werte_probe
[ 84%] Built target schranken_probe
[ 86%] Linking CXX executable schreiber_probe
[ 86%] Built target werte_probe
[ 87%] Linking CXX executable schritt_probe
[ 89%] Linking CXX executable zustand_probe
[ 89%] Built target schreiber_probe
[ 89%] Built target schritt_probe
[ 89%] Built target zustand_probe
[ 90%] Linking CXX executable aktion_probe
[ 90%] Built target aktion_probe
[ 92%] Linking CXX executable verlauf_probe
[ 92%] Built target verlauf_probe
[ 93%] Linking CXX executable zustandsausgabe_probe
[ 93%] Built target zustandsausgabe_probe
[ 95%] Linking CXX executable mutationstreiber
[ 95%] Built target mutationstreiber
[ 96%] Linking CXX executable zahlwort_riegel
[ 96%] Built target zahlwort_riegel
[ 98%] Linking CXX executable bezeichner_riegel
[ 98%] Built target bezeichner_riegel
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
eihen.toml:368  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 selbst vom 2026-09-05
  daten/reihen.toml:400  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:400  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:450  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:451  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:495  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:502  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:549  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:550  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als So
10 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/adressen.md:5
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Zustand

  zitierend: daten/reihen.toml:468
  nachgeschlagen in: specs/daten.md
  gesuchte Ueberschrift: Was dafuer zu tun ist -- Namensnennung, konkret

  zitierend: kern/include/kern/aktion.hpp:10
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/aktion.hpp:82
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/aktion.hpp:401
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/schritt.hpp:7
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

  zitierend: kern/include/kern/zustand.hpp:226
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Fonds

  zitierend: kern/src/schritt.cpp:122
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

  zitierend: parameter.toml:787
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
llreihe der Klasse gesetzt
  daten/reihen.toml:580  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:581  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:685  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:804  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:804  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:813  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:813  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:1120  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1318  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1595  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1595  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1751  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1807  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:1940  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 -- fd777fb und 89dc83c vom 2026-08-31
  daten/reihen.toml:1940  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 vom 2026-09-05 steht dort nicht
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:71  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  parameter.toml:876  (kein Dokumentname im Absatz)
      gesucht war: WIE DER PRUEFER ZAEHLT
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig
  werkzeuge/belegstellen/belegstellen_riegel.cpp:280  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:283  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet

      Start 17: bezeichner_riegel
17/20 Test #17: bezeichner_riegel ................   Passed    0.37 sec
      Start 18: schlussriegel_nachbau
18/20 Test #18: schlussriegel_nachbau ............   Passed    4.73 sec
      Start 19: zahlwort_riegel
19/20 Test #19: zahlwort_riegel ..................   Passed    0.04 sec
      Start 20: zahlwort_reihen
20/20 Test #20: zahlwort_reihen ..................   Passed    0.13 sec

95% tests passed, 1 tests failed out of 20

Total Test time (real) =   6.48 sec

The following tests FAILED:
	 16 - belegstellen_riegel (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 242 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[  4%] Building CXX object CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[  6%] Building CXX object CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[  8%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 15%] Building CXX object CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 17%] Building CXX object CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 19%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 21%] Building CXX object CMakeFiles/kern.dir/src/aktion.cpp.o
[ 23%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 26%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 28%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 30%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 32%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 34%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 36%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 41%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 43%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 39%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 45%] Linking CXX static library libkern_geprueft.a
[ 45%] Built target kern_geprueft
[ 47%] Building CXX object CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 50%] Building CXX object CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 54%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 56%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 58%] Building CXX object CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 63%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 65%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 67%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 69%] Building CXX object CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 71%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 73%] Linking CXX static library libkern.a
[ 73%] Built target kern
[ 76%] Linking CXX executable pruefsumme_probe
[ 78%] Linking CXX executable festkomma_probe
[ 78%] Built target pruefsumme_probe
[ 78%] Built target festkomma_probe
[ 80%] Linking CXX executable zufall_probe
[ 80%] Built target zufall_probe
[ 82%] Linking CXX executable meldung_probe
[ 82%] Built target meldung_probe
[ 84%] Linking CXX executable schritt_probe
[ 84%] Built target schritt_probe
[ 86%] Linking CXX executable schreiber_probe
[ 89%] Linking CXX executable schranken_probe
[ 91%] Linking CXX executable werte_probe
[ 91%] Built target schranken_probe
[ 91%] Built target schreiber_probe
[ 91%] Built target werte_probe
[ 93%] Linking CXX executable zustand_probe
[ 93%] Built target zustand_probe
[ 95%] Linking CXX executable aktion_probe
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
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 89 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 33%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 41%] Linking CXX static library libpruefstand.a
[ 50%] Linking CXX static library libpruefstand_geprueft.a
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[ 58%] Building CXX object CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 66%] Building CXX object CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
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
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
 dieselbe Form wie bei
  daten/reihen.toml:211  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 stammt vom 2026-09-05 aus dem Paket
  daten/reihen.toml:221  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:229  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 nicht
  daten/reihen.toml:368  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:368  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 selbst vom 2026-09-05
  daten/reihen.toml:400  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:400  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:450  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:451  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:495  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:502  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:549  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:550  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als So
10 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/adressen.md:5
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Zustand

  zitierend: daten/reihen.toml:468
  nachgeschlagen in: specs/daten.md
  gesuchte Ueberschrift: Was dafuer zu tun ist -- Namensnennung, konkret

  zitierend: kern/include/kern/aktion.hpp:10
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/aktion.hpp:82
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/aktion.hpp:401
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: kern/include/kern/schritt.hpp:7
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

  zitierend: kern/include/kern/zustand.hpp:226
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Fonds

  zitierend: kern/src/schritt.cpp:122
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

  zitierend: parameter.toml:787
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Aktionen

  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
llreihe der Klasse gesetzt
  daten/reihen.toml:580  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:581  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:685  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:804  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:804  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:813  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:813  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:1120  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1318  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1594  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1595  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1595  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1751  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1807  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:1940  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 -- fd777fb und 89dc83c vom 2026-08-31
  daten/reihen.toml:1940  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 vom 2026-09-05 steht dort nicht
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:71  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  parameter.toml:876  (kein Dokumentname im Absatz)
      gesucht war: WIE DER PRUEFER ZAEHLT
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig
  werkzeuge/belegstellen/belegstellen_riegel.cpp:280  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:283  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.98 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/bezeichner_riegel.dir/bezeichner_riegel.cpp.o
[100%] Linking CXX executable bezeichner_riegel
[100%] Built target bezeichner_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bau
    Start 1: bezeichner_riegel
1/1 Test #1: bezeichner_riegel ................   Passed    0.37 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.37 sec
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/mutationstreiber.dir/mutationslauf.cpp.o
[100%] Linking CXX executable mutationstreiber
[100%] Built target mutationstreiber
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/mutation/bau
No tests were found!!!
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.3s)
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    4.68 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   4.68 sec
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/zahlwort_riegel.dir/zahlwort_riegel.cpp.o
[100%] Linking CXX executable zahlwort_riegel
[100%] Built target zahlwort_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/2 Test #1: zahlwort_riegel ..................   Passed    0.04 sec
    Start 2: zahlwort_reihen
2/2 Test #2: zahlwort_reihen ..................   Passed    0.13 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.17 sec
```
