---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-05
bauart: cmake
manifeste: 13
ergebnis: fehler
---

# Der Compiler hat gesprochen: fehler

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
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 18 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 13%] Built target pruefstand
[ 13%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 13%] Built target pruefstand_geprueft
[ 30%] Built target kern
[ 48%] Built target kern_geprueft
[ 51%] Built target vorrat_kernanker_probe
[ 55%] Built target vorrat_verfahren_probe
[ 63%] Built target pruefsumme_probe
[ 67%] Built target schranken_probe
[ 67%] Built target festkomma_probe
[ 71%] Built target schritt_probe
[ 75%] Built target meldung_probe
[ 78%] Built target vorrat_probe
[ 82%] Built target zufall_probe
[ 86%] Built target schreiber_probe
[ 94%] Built target zustand_probe
[ 94%] Built target werte_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/14 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/14 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/14 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/14 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/14 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/14 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: werte_probe
 7/14 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/14 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/14 Test  #9: zustand_probe ....................   Passed    0.01 sec
      Start 10: zustandsausgabe_probe
10/14 Test #10: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 11: vorrat_kernanker_probe
11/14 Test #11: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 12: vorrat_probe
12/14 Test #12: vorrat_probe .....................   Passed    0.01 sec
      Start 13: vorrat_verfahren_probe
13/14 Test #13: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 14: belegstellen_riegel
14/14 Test #14: belegstellen_riegel ..............   Passed    0.70 sec

100% tests passed, 0 tests failed out of 14

Total Test time (real) =   0.91 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 20 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  5%] Built target pruefstand_geprueft
[ 12%] Built target belegstellen_riegel
[ 14%] Built target pruefstand
[ 30%] Built target kern
[ 46%] Built target kern_geprueft
[ 50%] Built target vorrat_probe
[ 53%] Built target vorrat_verfahren_probe
[ 57%] Built target vorrat_kernanker_probe
[ 60%] Built target meldung_probe
[ 64%] Built target randmass_probe
[ 67%] Built target pruefsumme_probe
[ 71%] Built target schritt_probe
[ 75%] Built target zufall_probe
[ 78%] Built target festkomma_probe
[ 82%] Built target schranken_probe
[ 85%] Built target kennung_probe
[ 89%] Built target zustandsausgabe_probe
[ 92%] Built target schreiber_probe
[ 96%] Built target werte_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/16 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: kennung_probe
 2/16 Test  #2: kennung_probe ....................   Passed    0.01 sec
      Start  3: meldung_probe
 3/16 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/16 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: randmass_probe
 5/16 Test  #5: randmass_probe ...................   Passed    0.04 sec
      Start  6: schranken_probe
 6/16 Test  #6: schranken_probe ..................   Passed    0.01 sec
      Start  7: schreiber_probe
 7/16 Test  #7: schreiber_probe ..................   Passed    0.01 sec
      Start  8: schritt_probe
 8/16 Test  #8: schritt_probe ....................   Passed    0.01 sec
      Start  9: werte_probe
 9/16 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/16 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/16 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/16 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 13: vorrat_kernanker_probe
13/16 Test #13: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 14: vorrat_probe
14/16 Test #14: vorrat_probe .....................   Passed    0.01 sec
      Start 15: vorrat_verfahren_probe
15/16 Test #15: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 16: belegstellen_riegel
16/16 Test #16: belegstellen_riegel ..............***Failed    0.44 sec

5 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/reihen.toml:38
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:345
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:493
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:513
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/einheitenbefund-pwt-baci.md:100
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
belegstellen_riegel, Selbsttest der Suche nach links: 8 Faelle, alle wie erwartet.
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 44 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 44 Bauquellen und 11 Datendokumente gelesen, 148 Dateien im Zielbestand; 24 Zitate der geprueften Form gefunden, 19 davon aufgeloest, 8 Fundstellen uebergangen.

Uebergangen -- der ausgeschriebene blinde Fleck von Bedingung 2. Diese
Fundstellen tragen ihr Ziel nicht bei sich; sie werden gezaehlt und genannt,
aber nicht bewertet:

  rueckstand.md:81  (kein Dokumentname im Absatz)
      gesucht war: "Wenn du fertig bist"
  parameter.toml:11  (Ziel ausserhalb des Bestands: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
      gesucht war: Droits de propriété intellectuelle
  daten/einheitenbefund-pwt-baci.md:20  (kein Dokumentname im Absatz)
      gesucht war: Woran es haengt
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig


94% tests passed, 1 tests failed out of 16

Total Test time (real) =   0.72 sec

The following tests FAILED:
	 16 - belegstellen_riegel (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 42%] Built target kern_geprueft
[ 42%] Built target kern
[ 57%] Built target festkomma_probe
[ 57%] Built target schritt_probe
[ 73%] Built target meldung_probe
[ 73%] Built target schranken_probe
[ 73%] Built target werte_probe
[ 73%] Built target schreiber_probe
[ 76%] Built target kennung_probe
[ 80%] Built target pruefsumme_probe
[ 85%] Built target zufall_probe
[ 90%] Built target randmass_probe
[ 95%] Built target zustand_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/12 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: kennung_probe
 2/12 Test  #2: kennung_probe ....................   Passed    0.01 sec
      Start  3: meldung_probe
 3/12 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/12 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: randmass_probe
 5/12 Test  #5: randmass_probe ...................   Passed    0.04 sec
      Start  6: schranken_probe
 6/12 Test  #6: schranken_probe ..................   Passed    0.01 sec
      Start  7: schreiber_probe
 7/12 Test  #7: schreiber_probe ..................   Passed    0.01 sec
      Start  8: schritt_probe
 8/12 Test  #8: schritt_probe ....................   Passed    0.01 sec
      Start  9: werte_probe
 9/12 Test  #9: werte_probe ......................   Passed    0.01 sec
      Start 10: zufall_probe
10/12 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/12 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/12 Test #12: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.24 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
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
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
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
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0010/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............***Failed    0.42 sec

5 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/reihen.toml:38
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:345
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:493
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/reihen.toml:513
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

  zitierend: daten/einheitenbefund-pwt-baci.md:100
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
belegstellen_riegel, Selbsttest der Suche nach links: 8 Faelle, alle wie erwartet.
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 44 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 44 Bauquellen und 11 Datendokumente gelesen, 148 Dateien im Zielbestand; 24 Zitate der geprueften Form gefunden, 19 davon aufgeloest, 8 Fundstellen uebergangen.

Uebergangen -- der ausgeschriebene blinde Fleck von Bedingung 2. Diese
Fundstellen tragen ihr Ziel nicht bei sich; sie werden gezaehlt und genannt,
aber nicht bewertet:

  rueckstand.md:81  (kein Dokumentname im Absatz)
      gesucht war: "Wenn du fertig bist"
  parameter.toml:11  (Ziel ausserhalb des Bestands: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
      gesucht war: Droits de propriété intellectuelle
  daten/einheitenbefund-pwt-baci.md:20  (kein Dokumentname im Absatz)
      gesucht war: Woran es haengt
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.43 sec

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
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 19 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  7%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[  7%] Building CXX object kern/CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[  7%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[  9%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 11%] Building CXX object pruefstand/CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 12%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 14%] Building CXX object pruefstand/CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[ 16%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 20%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 29%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern.dir/src/zufall.cpp.o
[ 35%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 37%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 38%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 40%] Linking CXX static library libpruefstand.a
[ 40%] Built target pruefstand
[ 42%] Linking CXX static library libpruefstand_geprueft.a
[ 42%] Built target pruefstand_geprueft
[ 44%] Building CXX object pruefstand/CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 48%] Building CXX object pruefstand/CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 48%] Building CXX object pruefstand/CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 50%] Linking CXX executable vorrat_probe
[ 50%] Built target vorrat_probe
[ 51%] Linking CXX executable vorrat_kernanker_probe
[ 51%] Built target vorrat_kernanker_probe
[ 53%] Linking CXX static library libkern_geprueft.a
[ 55%] Linking CXX static library libkern.a
[ 55%] Built target kern
[ 55%] Built target kern_geprueft
[ 57%] Linking CXX executable vorrat_verfahren_probe
[ 61%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 61%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 62%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 64%] Building CXX object kern/CMakeFiles/kp0027r3_messung.dir/test/kp0027r3_messung.cpp.o
[ 66%] Building CXX object kern/CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 68%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 70%] Building CXX object kern/CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 74%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 75%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 77%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 77%] Built target vorrat_verfahren_probe
[ 79%] Linking CXX executable pruefsumme_probe
[ 81%] Linking CXX executable festkomma_probe
[ 83%] Linking CXX executable kp0027r3_messung
[ 85%] Linking CXX executable meldung_probe
[ 85%] Built target pruefsumme_probe
[ 85%] Built target festkomma_probe
[ 87%] Linking CXX executable zufall_probe
[ 87%] Built target kp0027r3_messung
[ 88%] Linking CXX executable werte_probe
[ 88%] Built target meldung_probe
[ 90%] Linking CXX executable schritt_probe
[ 90%] Built target werte_probe
[ 90%] Built target zufall_probe
[ 90%] Built target schritt_probe
[ 92%] Linking CXX executable schreiber_probe
[ 92%] Built target schreiber_probe
[ 94%] Linking CXX executable schranken_probe
[ 96%] Linking CXX executable zustand_probe
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target schranken_probe
[ 98%] Built target zustand_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
      Start  1: festkomma_probe
 1/15 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: kp0027r3_messung
 2/15 Test  #2: kp0027r3_messung .................   Passed    0.01 sec
      Start  3: meldung_probe
 3/15 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/15 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/15 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/15 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/15 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: werte_probe
 8/15 Test  #8: werte_probe ......................   Passed    0.01 sec
      Start  9: zufall_probe
 9/15 Test  #9: zufall_probe .....................   Passed    0.01 sec
      Start 10: zustand_probe
10/15 Test #10: zustand_probe ....................   Passed    0.01 sec
      Start 11: zustandsausgabe_probe
11/15 Test #11: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 12: vorrat_kernanker_probe
12/15 Test #12: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 13: vorrat_probe
13/15 Test #13: vorrat_probe .....................   Passed    0.01 sec
      Start 14: vorrat_verfahren_probe
14/15 Test #14: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 15: belegstellen_riegel
15/15 Test #15: belegstellen_riegel ..............   Passed    0.49 sec

100% tests passed, 0 tests failed out of 15

Total Test time (real) =   0.72 sec
```

## `cmake -S` -- ok (Code 0)

```
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 13 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  5%] Building CXX object CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[  5%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[  7%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 10%] Building CXX object CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[ 15%] Building CXX object CMakeFiles/kern.dir/src/zufall.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 20%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[ 22%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 25%] Building CXX object CMakeFiles/kern.dir/src/festkomma.cpp.o
[ 27%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 30%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 32%] Building CXX object CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[ 35%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 37%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 40%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 42%] Linking CXX static library libkern_geprueft.a
[ 45%] Linking CXX static library libkern.a
[ 45%] Built target kern_geprueft
[ 45%] Built target kern
[ 52%] Building CXX object CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/kp0027r3_messung.dir/test/kp0027r3_messung.cpp.o
[ 55%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 65%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 65%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 72%] Building CXX object CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 72%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 72%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 75%] Linking CXX executable festkomma_probe
[ 77%] Linking CXX executable pruefsumme_probe
[ 80%] Linking CXX executable kp0027r3_messung
[ 82%] Linking CXX executable meldung_probe
[ 82%] Built target festkomma_probe
[ 85%] Linking CXX executable werte_probe
[ 85%] Built target pruefsumme_probe
[ 87%] Linking CXX executable zufall_probe
[ 87%] Built target kp0027r3_messung
[ 87%] Built target meldung_probe
[ 90%] Linking CXX executable schritt_probe
[ 90%] Built target werte_probe
[ 90%] Built target zufall_probe
[ 90%] Built target schritt_probe
[ 92%] Linking CXX executable schreiber_probe
[ 95%] Linking CXX executable zustand_probe
[ 95%] Built target schreiber_probe
[ 97%] Linking CXX executable schranken_probe
[ 97%] Built target zustand_probe
[ 97%] Built target schranken_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/11 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: kp0027r3_messung
 2/11 Test  #2: kp0027r3_messung .................   Passed    0.01 sec
      Start  3: meldung_probe
 3/11 Test  #3: meldung_probe ....................   Passed    0.01 sec
      Start  4: pruefsumme_probe
 4/11 Test  #4: pruefsumme_probe .................   Passed    0.01 sec
      Start  5: schranken_probe
 5/11 Test  #5: schranken_probe ..................   Passed    0.01 sec
      Start  6: schreiber_probe
 6/11 Test  #6: schreiber_probe ..................   Passed    0.01 sec
      Start  7: schritt_probe
 7/11 Test  #7: schritt_probe ....................   Passed    0.01 sec
      Start  8: werte_probe
 8/11 Test  #8: werte_probe ......................   Passed    0.01 sec
      Start  9: zufall_probe
 9/11 Test  #9: zufall_probe .....................   Passed    0.01 sec
      Start 10: zustand_probe
10/11 Test #10: zustand_probe ....................   Passed    0.01 sec
      Start 11: zustandsausgabe_probe
11/11 Test #11: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 11

Total Test time (real) =   0.19 sec
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
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat_verfahren.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand_geprueft.dir/src/vorrat.cpp.o
[ 25%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat_verfahren.cpp.o
[ 33%] Building CXX object CMakeFiles/pruefstand.dir/src/vorrat.cpp.o
[ 41%] Linking CXX static library libpruefstand.a
[ 41%] Built target pruefstand
[ 50%] Linking CXX static library libpruefstand_geprueft.a
[ 50%] Built target pruefstand_geprueft
[ 75%] Building CXX object CMakeFiles/vorrat_kernanker_probe.dir/test/vorrat_kernanker_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_probe.dir/test/vorrat_probe.cpp.o
[ 75%] Building CXX object CMakeFiles/vorrat_verfahren_probe.dir/test/vorrat_verfahren_probe.cpp.o
[ 83%] Linking CXX executable vorrat_probe
[ 83%] Built target vorrat_probe
[ 91%] Linking CXX executable vorrat_kernanker_probe
[ 91%] Built target vorrat_kernanker_probe
[100%] Linking CXX executable vorrat_verfahren_probe
[100%] Built target vorrat_verfahren_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
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
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau/kp0027r3/quelle/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............   Passed    0.48 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.48 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel: 12 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  5%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[  5%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[  7%] Linking CXX static library libkern.a
[ 10%] Linking CXX static library libkern_geprueft.a
[ 28%] Built target kern
[ 47%] Built target kern_geprueft
[ 50%] Linking CXX executable festkomma_probe
[ 52%] Linking CXX executable meldung_probe
[ 55%] Linking CXX executable schreiber_probe
[ 57%] Linking CXX executable schranken_probe
[ 60%] Linking CXX executable pruefsumme_probe
[ 63%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 65%] Linking CXX executable zustandsausgabe_probe
[ 73%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 73%] Linking CXX executable zustand_probe
[ 73%] Linking CXX executable zufall_probe
[ 76%] Built target zufall_probe
[ 81%] Built target schranken_probe
[ 81%] Built target meldung_probe
[ 84%] Built target festkomma_probe
[ 86%] Built target pruefsumme_probe
[ 89%] Built target zustandsausgabe_probe
[ 92%] Built target schreiber_probe
[ 94%] Built target zustand_probe
[ 97%] Linking CXX executable werte_probe
[ 97%] Built target werte_probe
[100%] Linking CXX executable schritt_probe
[100%] Built target schritt_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/10 Test  #1: festkomma_probe ..................   Passed    0.02 sec
      Start  2: meldung_probe
 2/10 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/10 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/10 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/10 Test  #5: schreiber_probe ..................   Passed    0.02 sec
      Start  6: schritt_probe
 6/10 Test  #6: schritt_probe ....................   Passed    0.02 sec
      Start  7: werte_probe
 7/10 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/10 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/10 Test  #9: zustand_probe ....................   Passed    0.02 sec
      Start 10: zustandsausgabe_probe
10/10 Test #10: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   0.22 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 25%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
[ 66%] Built target vorrat_kernanker_probe
[ 91%] Built target vorrat_probe
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
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 18%] Built target mut3_ordnung_a5_bis_a1
[ 18%] Built target kontrolle_unveraendert
[ 27%] Built target mut6_abgelegter_kern_immer_ohne
[ 66%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 66%] Built target mut4_kennung_einsbasiert
[ 66%] Built target mut2_gleichstand_an_groessere_kennung
[ 66%] Built target mut1_dreiwertiger_kern
[ 72%] Built target mut7_position_und_lobby_vertauscht
[ 81%] Built target mut8_profil_doppelt_eines_fehlt
[ 93%] Built target anker_von_hand
[100%] Built target anker_gegen_mut2
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/bau
      Start  1: kontrolle_unveraendert
 1/11 Test  #1: kontrolle_unveraendert ..................   Passed    0.00 sec
      Start  2: mut1_dreiwertiger_kern
 2/11 Test  #2: mut1_dreiwertiger_kern ..................   Passed    0.00 sec
      Start  3: mut2_gleichstand_an_groessere_kennung
 3/11 Test  #3: mut2_gleichstand_an_groessere_kennung ...   Passed    0.00 sec
      Start  4: mut3_ordnung_a5_bis_a1
 4/11 Test  #4: mut3_ordnung_a5_bis_a1 ..................   Passed    0.00 sec
      Start  5: mut4_kennung_einsbasiert
 5/11 Test  #5: mut4_kennung_einsbasiert ................   Passed    0.00 sec
      Start  6: mut5_hebel_und_sichtbarkeit_im_kern
 6/11 Test  #6: mut5_hebel_und_sichtbarkeit_im_kern .....   Passed    0.00 sec
      Start  7: mut6_abgelegter_kern_immer_ohne
 7/11 Test  #7: mut6_abgelegter_kern_immer_ohne .........   Passed    0.00 sec
      Start  8: mut7_position_und_lobby_vertauscht
 8/11 Test  #8: mut7_position_und_lobby_vertauscht ......   Passed    0.00 sec
      Start  9: mut8_profil_doppelt_eines_fehlt
 9/11 Test  #9: mut8_profil_doppelt_eines_fehlt .........   Passed    0.00 sec
      Start 10: anker_von_hand
10/11 Test #10: anker_von_hand ..........................   Passed    0.00 sec
      Start 11: anker_gegen_mut2
11/11 Test #11: anker_gegen_mut2 ........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 11

Total Test time (real) =   0.03 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
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
1/1 Test #1: belegstellen_riegel ..............   Passed    0.73 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.74 sec
```
