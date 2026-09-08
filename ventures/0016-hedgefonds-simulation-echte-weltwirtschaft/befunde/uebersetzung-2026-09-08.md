---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-08
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
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 23 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 407 Schaltereintraege.
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand
[  6%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 10%] Built target pruefstand_geprueft
[ 13%] Built target bezeichner_riegel
[ 18%] Built target zahlwort_riegel
[ 19%] Built target mutationstreiber
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 24%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 34%] Built target vorrat_kernanker_probe
[ 34%] Built target vorrat_probe
[ 37%] Built target vorrat_verfahren_probe
[ 39%] Linking CXX static library libkern_geprueft.a
[ 50%] Built target kern_geprueft
[ 51%] Linking CXX executable meldung_probe
[ 53%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 54%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 56%] Linking CXX executable pruefsumme_probe
[ 57%] Linking CXX executable schranken_probe
[ 59%] Linking CXX executable festkomma_probe
[ 60%] Linking CXX executable schreiber_probe
[ 62%] Linking CXX executable aktion_probe
[ 63%] Linking CXX executable zufall_probe
[ 65%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 66%] Linking CXX executable zustand_probe
[ 68%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 69%] Built target zufall_probe
[ 71%] Built target pruefsumme_probe
[ 72%] Built target aktion_probe
[ 74%] Built target schranken_probe
[ 75%] Built target zustand_probe
[ 77%] Built target festkomma_probe
[ 78%] Built target meldung_probe
[ 80%] Built target schreiber_probe
[ 81%] Linking CXX static library libkern.a
[ 92%] Built target kern
[ 93%] Linking CXX executable werte_probe
[ 93%] Built target werte_probe
[ 95%] Linking CXX executable schritt_probe
[ 96%] Linking CXX executable verlauf_probe
[ 96%] Built target schritt_probe
[ 96%] Built target verlauf_probe
[ 98%] Linking CXX executable zustandsausgabe_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 36 Zitate ohne die Mutation, gemessen sind 37.
  FEHLSCHLAG: Der Kopfkommentar nennt 36 aufgeloeste Zitate, gemessen sind 37.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 37 Zitate, 37 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (36, 36, 57) als die Zahlen des unveraenderten Riegels, gemessen sind (37, 37, 57).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (37, 37, 57) statt (36, 36, 57).
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt erste
  FEHLSCHLAG: Der Kopf nennt den erste Fall, historisch ausgewiesen ist der 7.
G  Gegenprobe an der verstellten Angabe -- Angabe 1: 2 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 1 Meldung(en)
HEAD am Ende: d17b26d
Hinweis: HEAD steht auf d17b26d, gemessen und niedergeschrieben ist der Stand 7ebc1a9. Die Zahlen sind damit aelter als der Baum.

6 Erwartung(en) nicht erfuellt.

      Start 22: bezeichner_riegel
22/26 Test #22: bezeichner_riegel ................   Passed    0.38 sec
      Start 23: schlussriegel_nachbau
23/26 Test #23: schlussriegel_nachbau ............   Passed    0.50 sec
      Start 24: zahlwort_riegel
24/26 Test #24: zahlwort_riegel ..................   Passed    0.04 sec
      Start 25: zahlwort_reihen
25/26 Test #25: zahlwort_reihen ..................   Passed    0.14 sec
      Start 26: zahlwort_messung
26/26 Test #26: zahlwort_messung .................***Failed   18.59 sec
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD d17b26de5fbfe214cd40be5dcfc2946aa4348a16
  Pruefling  kern/include/kern/werte.hpp  Blob 1a7a6e489ee32bab31a0058a1b789ca065eebc19
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 709f016f1480fa63e7b8f5469c2c2ab7fd14aef1
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp

  A0 heutiger Stand: Code 0 (erwartet 0), 0 Befunde
  A1 Zahlwort im Kopf verstellt: Code 1 (erwartet 1), 1 Befunde
      Zeilennummer 2: 'einundzwanzig Groessen' nennt 21, gezaehlt sind 22
  A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Code 1 (erwartet 1), 5 Befunde
      Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24
      Zeilennummer 185: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
  FEHLSCHLAG: A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Befunde weichen ab -- erwartet ["Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24", "Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23"]
  A3 Stand vor 0155 (b2829c8): Code 1 (erwartet 1), 1 Befunde
      Zeilennummer 73: 'eine Jahrgangskonstante[n]' nennt 1, gezaehlt sind 2

## Teil B: fuenf Mutanten des Riegels gegen die fuenf Tabellen

  M1 die Artikelregel faellt weg
      Code 2 (erwartet 2), gerissen: ['Behauptung 19', 'Behauptung 3']
      aufgeloest aus dem Wortlaut: ['Behauptung 3', 'Behauptung 19']
  M2 das Kardinalurteil ist immer gruen
      Code 2 (erwartet 2), gerissen: ['Urteil 2', 'Urteil 3', 'Verdrahtung 2', 'Verdrahtung 3', 'Verdrahtung 8', 'Verdrahtung 9']
      aufgeloest aus dem Wortlaut: ['Urteil 2', 'Urteil 3', 'Verdrahtung 2', 'Verdrahtung 3', 'Verdrahtung 8', 'Verdrahtung 9']
  M3 jede Fundstelle bekommt eine eigene Nummer -- gezaehlt werden Zeilen
      Code 2 (erwartet 2), gerissen: ['Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9', 'Zaehlung 2']
      aufgeloest aus dem Wortlaut: ['Zaehlung 2', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']
  M4 eine wortlose Zeile trennt keinen Block mehr
      Code 2 (erwartet 2), gerissen: ['Bloecke 3', 'Bloecke 4']
      aufgeloest aus dem Wortlaut: ['Bloecke 3', 'Bloecke 4']
  M5 die Zaehlung wird an die falsche Sorte gebunden
      Code 2 (erwartet 2), gerissen: ['Verdrahtung 1', 'Verdrahtung 3', 'Verdrahtung 5', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']
      aufgeloest aus dem Wortlaut: ['Verdrahtung 1', 'Verdrahtung 3', 'Verdrahtung 5', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']

## Teil C: zwei Mutanten der Empfindlichkeitsprobe

  C1 die Probe vergleicht die falsche Sorte
      Code 2 (erwartet 2), Selbsttest gerissen: nichts
  C2 das Urteil an der Fundstelle bewegt sich nicht mehr
      Code 2 (erwartet 2), Selbsttest gerissen: nichts

  Gegenprobe, unveraenderter Riegel am heutigen Baum: Code 0 (erwartet 0)

Fehlschlaege: 1
  A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Befunde weichen ab -- erwartet ["Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24", "Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23"]


92% tests passed, 2 tests failed out of 26

Total Test time (real) =  91.40 sec

The following tests FAILED:
	 21 - belegstellen_kopfzahlen (Failed)
	 26 - zahlwort_messung (Failed)
Errors while running CTest
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
[  6%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[  6%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[  6%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 13%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 13%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 15%] Linking CXX static library libkern_geprueft.a
[ 30%] Built target kern_geprueft
[ 32%] Linking CXX executable meldung_probe
[ 34%] Linking CXX executable pruefsumme_probe
[ 36%] Linking CXX executable schranken_probe
[ 39%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 41%] Linking CXX executable aktion_probe
[ 43%] Linking CXX executable festkomma_probe
[ 45%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 47%] Linking CXX executable schreiber_probe
[ 50%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 52%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 54%] Linking CXX executable zufall_probe
[ 56%] Linking CXX executable zustand_probe
[ 58%] Built target festkomma_probe
[ 60%] Built target zufall_probe
[ 63%] Built target zustand_probe
[ 65%] Built target aktion_probe
[ 67%] Built target pruefsumme_probe
[ 69%] Built target meldung_probe
[ 71%] Built target schreiber_probe
[ 73%] Built target schranken_probe
[ 76%] Linking CXX static library libkern.a
[ 91%] Built target kern
[ 93%] Linking CXX executable werte_probe
[ 95%] Linking CXX executable schritt_probe
[ 95%] Built target werte_probe
[ 95%] Built target schritt_probe
[ 97%] Linking CXX executable verlauf_probe
[ 97%] Built target verlauf_probe
[100%] Linking CXX executable zustandsausgabe_probe
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
11/13 Test #11: zustand_probe ....................   Passed    0.01 sec
      Start 12: zustandsausgabe_probe
12/13 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: wandschranke
13/13 Test #13: wandschranke .....................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 13

Total Test time (real) =   0.64 sec
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
[ 83%] Built target vorrat_kernanker_probe
[ 83%] Built target vorrat_probe
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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/5 Test #1: belegstellen_riegel ..............   Passed    1.03 sec
    Start 2: belegstellen_messung
2/5 Test #2: belegstellen_messung .............   Passed   31.15 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........   Passed   17.43 sec
    Start 4: belegstellen_sammelordnung
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.73 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........***Failed   16.02 sec
Vorfassung: gefehlt und ist geholt worden -- Blob 2aea68a5926bf7fe2560e814c989f6e51880223a aus d8e3bfb:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 7ebc1a9; HEAD zu Beginn: d17b26d
A  vorher : Code 0, 37 Zitate, 37 aufgeloest, 57 uebergangen
A  nachher: Code 0, 37 Zitate, 37 aufgeloest, 57 uebergangen
B1 ohne-marken-rein: Code 1, 48 Zitate, 37 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 47 Zitate unter der Mutation, gemessen sind 48.
  FEHLSCHLAG: Der Kopfkommentar nennt 36 Zitate ohne die Mutation, gemessen sind 37.
  FEHLSCHLAG: Der Kopfkommentar nennt 36 aufgeloeste Zitate, gemessen sind 37.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 37 Zitate, 37 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (36, 36, 57) als die Zahlen des unveraenderten Riegels, gemessen sind (37, 37, 57).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (37, 37, 57) statt (36, 36, 57).
  FEHLSCHLAG: Angabe 2 nennt die Summe 93; Zitate plus uebergangene Fundstellen sind 94.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 48 Zitate, 37 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 36 Zitate ohne die Mutation, gemessen sind 37.
  FEHLSCHLAG: Der Kopfkommentar nennt 36 aufgeloeste Zitate, gemessen sind 37.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 37 Zitate, 37 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (36, 36, 57) als die Zahlen des unveraenderten Riegels, gemessen sind (37, 37, 57).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (37, 37, 57) statt (36, 36, 57).
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt erste
  FEHLSCHLAG: Der Kopf nennt den erste Fall, historisch ausgewiesen ist der 7.
G  Gegenprobe an der verstellten Angabe -- Angabe 1: 2 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 1 Meldung(en)
HEAD am Ende: d17b26d
Hinweis: HEAD steht auf d17b26d, gemessen und niedergeschrieben ist der Stand 7ebc1a9. Die Zahlen sind damit aelter als der Baum.

6 Erwartung(en) nicht erfuellt.


80% tests passed, 1 tests failed out of 5

Total Test time (real) =  71.37 sec

The following tests FAILED:
	  5 - belegstellen_kopfzahlen (Failed)
Errors while running CTest
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.50 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.51 sec
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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/3 Test #1: zahlwort_riegel ..................   Passed    0.05 sec
    Start 2: zahlwort_reihen
2/3 Test #2: zahlwort_reihen ..................   Passed    0.13 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................***Failed   18.62 sec
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD d17b26de5fbfe214cd40be5dcfc2946aa4348a16
  Pruefling  kern/include/kern/werte.hpp  Blob 1a7a6e489ee32bab31a0058a1b789ca065eebc19
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 709f016f1480fa63e7b8f5469c2c2ab7fd14aef1
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp

  A0 heutiger Stand: Code 0 (erwartet 0), 0 Befunde
  A1 Zahlwort im Kopf verstellt: Code 1 (erwartet 1), 1 Befunde
      Zeilennummer 2: 'einundzwanzig Groessen' nennt 21, gezaehlt sind 22
  A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Code 1 (erwartet 1), 5 Befunde
      Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
      Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24
      Zeilennummer 185: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23
  FEHLSCHLAG: A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Befunde weichen ab -- erwartet ["Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24", "Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23"]
  A3 Stand vor 0155 (b2829c8): Code 1 (erwartet 1), 1 Befunde
      Zeilennummer 73: 'eine Jahrgangskonstante[n]' nennt 1, gezaehlt sind 2

## Teil B: fuenf Mutanten des Riegels gegen die fuenf Tabellen

  M1 die Artikelregel faellt weg
      Code 2 (erwartet 2), gerissen: ['Behauptung 19', 'Behauptung 3']
      aufgeloest aus dem Wortlaut: ['Behauptung 3', 'Behauptung 19']
  M2 das Kardinalurteil ist immer gruen
      Code 2 (erwartet 2), gerissen: ['Urteil 2', 'Urteil 3', 'Verdrahtung 2', 'Verdrahtung 3', 'Verdrahtung 8', 'Verdrahtung 9']
      aufgeloest aus dem Wortlaut: ['Urteil 2', 'Urteil 3', 'Verdrahtung 2', 'Verdrahtung 3', 'Verdrahtung 8', 'Verdrahtung 9']
  M3 jede Fundstelle bekommt eine eigene Nummer -- gezaehlt werden Zeilen
      Code 2 (erwartet 2), gerissen: ['Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9', 'Zaehlung 2']
      aufgeloest aus dem Wortlaut: ['Zaehlung 2', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']
  M4 eine wortlose Zeile trennt keinen Block mehr
      Code 2 (erwartet 2), gerissen: ['Bloecke 3', 'Bloecke 4']
      aufgeloest aus dem Wortlaut: ['Bloecke 3', 'Bloecke 4']
  M5 die Zaehlung wird an die falsche Sorte gebunden
      Code 2 (erwartet 2), gerissen: ['Verdrahtung 1', 'Verdrahtung 3', 'Verdrahtung 5', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']
      aufgeloest aus dem Wortlaut: ['Verdrahtung 1', 'Verdrahtung 3', 'Verdrahtung 5', 'Verdrahtung 7', 'Verdrahtung 8', 'Verdrahtung 9']

## Teil C: zwei Mutanten der Empfindlichkeitsprobe

  C1 die Probe vergleicht die falsche Sorte
      Code 2 (erwartet 2), Selbsttest gerissen: nichts
  C2 das Urteil an der Fundstelle bewegt sich nicht mehr
      Code 2 (erwartet 2), Selbsttest gerissen: nichts

  Gegenprobe, unveraenderter Riegel am heutigen Baum: Code 0 (erwartet 0)

Fehlschlaege: 1
  A2 Deklaration ergaenzt, Zahlwort nicht nachgezogen: Befunde weichen ab -- erwartet ["Zeilennummer 2: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 16: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'Zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23", "Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23, gezaehlt sind 24", "Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23"]


67% tests passed, 1 tests failed out of 3

Total Test time (real) =  18.79 sec

The following tests FAILED:
	  3 - zahlwort_messung (Failed)
Errors while running CTest
```
