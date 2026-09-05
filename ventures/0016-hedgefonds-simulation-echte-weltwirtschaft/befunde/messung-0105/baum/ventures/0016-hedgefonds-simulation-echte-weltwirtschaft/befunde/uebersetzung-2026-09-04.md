---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-04
bauart: cmake
manifeste: 5
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
[  7%] Built target pruefstand_geprueft
[  5%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 13%] Built target pruefstand
[ 15%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 17%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 21%] Built target vorrat_probe
[ 28%] Built target vorrat_verfahren_probe
[ 28%] Built target vorrat_kernanker_probe
[ 30%] Linking CXX static library libkern_geprueft.a
[ 44%] Built target kern_geprueft
[ 51%] Linking CXX executable festkomma_probe
[ 51%] Linking CXX executable pruefsumme_probe
[ 51%] Linking CXX executable schritt_probe
[ 51%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 53%] Linking CXX executable zufall_probe
[ 63%] Linking CXX executable schranken_probe
[ 63%] Linking CXX executable schreiber_probe
[ 63%] Linking CXX executable meldung_probe
[ 63%] Linking CXX executable werte_probe
[ 63%] Linking CXX executable zustand_probe
[ 65%] Built target zustand_probe
[ 67%] Built target festkomma_probe
[ 69%] Built target meldung_probe
[ 73%] Built target werte_probe
[ 73%] Built target pruefsumme_probe
[ 75%] Built target schranken_probe
[ 76%] Built target zufall_probe
[ 78%] Built target schritt_probe
[ 80%] Built target schreiber_probe
[ 82%] Linking CXX static library libkern.a
[ 96%] Built target kern
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

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
14/14 Test #14: belegstellen_riegel ..............***Failed    0.42 sec

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
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 42 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 42 Bauquellen und 11 Datendokumente gelesen, 146 Dateien im Zielbestand; 24 Zitate der geprueften Form gefunden, 19 davon aufgeloest, 8 Fundstellen uebergangen.

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


93% tests passed, 1 tests failed out of 14

Total Test time (real) =   0.63 sec

The following tests FAILED:
	 14 - belegstellen_riegel (Failed)
Errors while running CTest
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
[  5%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[  5%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[  7%] Linking CXX static library libkern_geprueft.a
[ 26%] Built target kern_geprueft
[ 34%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 34%] Linking CXX executable meldung_probe
[ 34%] Linking CXX executable pruefsumme_probe
[ 36%] Linking CXX executable festkomma_probe
[ 39%] Linking CXX executable schritt_probe
[ 42%] Linking CXX executable zustand_probe
[ 44%] Linking CXX executable werte_probe
[ 47%] Linking CXX executable schreiber_probe
[ 50%] Linking CXX executable zufall_probe
[ 52%] Linking CXX executable schranken_probe
[ 55%] Built target pruefsumme_probe
[ 57%] Built target zufall_probe
[ 60%] Built target festkomma_probe
[ 63%] Built target schreiber_probe
[ 68%] Built target meldung_probe
[ 71%] Built target werte_probe
[ 71%] Built target schranken_probe
[ 76%] Built target zustand_probe
[ 76%] Built target schritt_probe
[ 78%] Linking CXX static library libkern.a
[ 97%] Built target kern
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: festkomma_probe
 1/10 Test  #1: festkomma_probe ..................   Passed    0.01 sec
      Start  2: meldung_probe
 2/10 Test  #2: meldung_probe ....................   Passed    0.01 sec
      Start  3: pruefsumme_probe
 3/10 Test  #3: pruefsumme_probe .................   Passed    0.01 sec
      Start  4: schranken_probe
 4/10 Test  #4: schranken_probe ..................   Passed    0.01 sec
      Start  5: schreiber_probe
 5/10 Test  #5: schreiber_probe ..................   Passed    0.01 sec
      Start  6: schritt_probe
 6/10 Test  #6: schritt_probe ....................   Passed    0.01 sec
      Start  7: werte_probe
 7/10 Test  #7: werte_probe ......................   Passed    0.01 sec
      Start  8: zufall_probe
 8/10 Test  #8: zufall_probe .....................   Passed    0.01 sec
      Start  9: zustand_probe
 9/10 Test  #9: zustand_probe ....................   Passed    0.01 sec
      Start 10: zustandsausgabe_probe
10/10 Test #10: zustandsausgabe_probe ............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   0.18 sec
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
[ 27%] Built target mut2_gleichstand_an_groessere_kennung
[ 27%] Built target mut5_hebel_und_sichtbarkeit_im_kern
[ 27%] Built target mut3_ordnung_a5_bis_a1
[ 63%] Built target mut1_dreiwertiger_kern
[ 63%] Built target mut7_position_und_lobby_vertauscht
[ 63%] Built target mut4_kennung_einsbasiert
[ 63%] Built target kontrolle_unveraendert
[ 72%] Built target mut6_abgelegter_kern_immer_ohne
[ 90%] Built target mut8_profil_doppelt_eines_fehlt
[ 90%] Built target anker_gegen_mut2
[100%] Built target anker_von_hand
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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/1 Test #1: belegstellen_riegel ..............***Failed    0.41 sec

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
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 42 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 42 Bauquellen und 11 Datendokumente gelesen, 146 Dateien im Zielbestand; 24 Zitate der geprueften Form gefunden, 19 davon aufgeloest, 8 Fundstellen uebergangen.

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

Total Test time (real) =   0.42 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
Errors while running CTest
```
