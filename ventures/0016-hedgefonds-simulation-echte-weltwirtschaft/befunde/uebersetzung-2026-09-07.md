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
[  6%] Built target bezeichner_riegel
[  6%] Built target zahlwort_riegel
[ 13%] Built target belegstellen_riegel
[ 13%] Built target pruefstand_geprueft
[ 21%] Built target pruefstand
[ 21%] Built target mutationstreiber
[ 37%] Built target kern_geprueft
[ 54%] Built target kern
[ 57%] Built target vorrat_verfahren_probe
[ 60%] Built target vorrat_probe
[ 66%] Built target festkomma_probe
[ 66%] Built target aktion_probe
[ 69%] Built target vorrat_kernanker_probe
[ 72%] Built target schranken_probe
[ 75%] Built target pruefsumme_probe
[ 78%] Built target meldung_probe
[ 81%] Built target schreiber_probe
[ 87%] Built target schritt_probe
[ 87%] Built target zufall_probe
[ 93%] Built target verlauf_probe
[ 93%] Built target werte_probe
[100%] Built target zustandsausgabe_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
............   Passed    0.01 sec
      Start 11: zustand_probe
11/26 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/26 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: wandschranke
13/26 Test #13: wandschranke .....................   Passed    0.49 sec
      Start 14: vorrat_kernanker_probe
14/26 Test #14: vorrat_kernanker_probe ...........   Passed    0.01 sec
      Start 15: vorrat_probe
15/26 Test #15: vorrat_probe .....................   Passed    0.01 sec
      Start 16: vorrat_verfahren_probe
16/26 Test #16: vorrat_verfahren_probe ...........   Passed    0.01 sec
      Start 17: belegstellen_riegel
17/26 Test #17: belegstellen_riegel ..............   Passed    1.04 sec
      Start 18: belegstellen_messung
18/26 Test #18: belegstellen_messung .............   Passed   30.52 sec
      Start 19: belegstellen_wortabstand
19/26 Test #19: belegstellen_wortabstand .........   Passed   16.94 sec
      Start 20: belegstellen_sammelordnung
20/26 Test #20: belegstellen_sammelordnung .......   Passed    5.61 sec
      Start 21: belegstellen_kopfzahlen
21/26 Test #21: belegstellen_kopfzahlen ..........***Failed   15.51 sec
Vorfassung: gefehlt und ist geholt worden -- Blob e3038e23316f4c18ca9bdd6cbab51e42579e7838 aus 83faa06^:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 5d5e2d6; HEAD zu Beginn: 7ebc1a9
A  vorher : Code 1, 36 Zitate, 34 aufgeloest, 57 uebergangen
A  nachher: Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Die Berichtigung bewegt die drei Zahlen des Riegels: (36, 34, 57) -> (36, 36, 57). Die Abnahme von 0115 nennt genau das einen Fehlschlag.
  FEHLSCHLAG: Die Berichtigung bewegt den Rueckgabewert: 1 -> 0.
  FEHLSCHLAG: Die Befundlisten sind nicht dieselben. Nur vorher: ['zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32', 'zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:39']. Nur nachher: [].
B1 ohne-marken-rein: Code 1, 47 Zitate, 36 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 51 Zitate unter der Mutation, gemessen sind 47.
  FEHLSCHLAG: Der Kopfkommentar nennt 40 Zitate ohne die Mutation, gemessen sind 36.
  FEHLSCHLAG: Der Kopfkommentar nennt 40 aufgeloeste Zitate, gemessen sind 36.
  FEHLSCHLAG: Der Kopfkommentar nennt 59 uebergangene Fundstellen unter der Mutation, gemessen sind 70.
  FEHLSCHLAG: Der Kopfkommentar nennt 47 uebergangene Fundstellen ohne sie, gemessen sind 57.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (40, 40, 47) als die Zahlen des unveraenderten Riegels, gemessen sind (36, 36, 57).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (36, 36, 57) statt (40, 40, 47).
  FEHLSCHLAG: Angabe 2 nennt die Summe 87; Zitate plus uebergangene Fundstellen sind 93.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 47 Zitate, 36 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'sonst': 8}
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die Angabe 1 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die die Aufschluesselung bei Klammer::kuendigt_an traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
  FEHLSCHLAG: 8 Selbsttreffer liegen weder im Kopfkommentar noch in einer genannten Falltabelle -- die Aufschluesselung ist unvollstaendig.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die Angabe 2 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die die Fallangabe von Angabe 2 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt achte
  FEHLSCHLAG: Der Kopf nennt den achte Fall, historisch ausgewiesen ist der 7.
  FEHLSCHLAG: Der Kopf nennt den achten Fall zugleich historisch und abgewandelt -- genau der Widerspruch, den 0115 aufloest.
G  Gegenprobe am Wortlaut vor der Berichtigung -- Angabe 1: 3 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 2 Meldung(en)
HEAD am Ende: 7ebc1a9
Hinweis: HEAD steht auf 7ebc1a9, gemessen und niedergeschrieben ist der Stand 5d5e2d6. Die Zahlen sind damit aelter als der Baum.

11 Erwartung(en) nicht erfuellt.

      Start 22: bezeichner_riegel
22/26 Test #22: bezeichner_riegel ................   Passed    0.37 sec
      Start 23: schlussriegel_nachbau
23/26 Test #23: schlussriegel_nachbau ............   Passed    0.51 sec
      Start 24: zahlwort_riegel
24/26 Test #24: zahlwort_riegel ..................   Passed    0.05 sec
      Start 25: zahlwort_reihen
25/26 Test #25: zahlwort_reihen ..................   Passed    0.13 sec
      Start 26: zahlwort_messung
26/26 Test #26: zahlwort_messung .................   Passed   18.26 sec

96% tests passed, 1 tests failed out of 26

Total Test time (real) =  89.71 sec

The following tests FAILED:
	 21 - belegstellen_kopfzahlen (Failed)
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
[ 45%] Built target kern
[ 47%] Built target kern_geprueft
[ 52%] Built target schreiber_probe
[ 60%] Built target schranken_probe
[ 60%] Built target aktion_probe
[ 65%] Built target festkomma_probe
[ 69%] Built target meldung_probe
[ 76%] Built target schritt_probe
[ 78%] Built target werte_probe
[ 86%] Built target pruefsumme_probe
[ 86%] Built target zufall_probe
[ 91%] Built target zustandsausgabe_probe
[ 95%] Built target verlauf_probe
[100%] Built target zustand_probe
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
 9/13 Test  #9: werte_probe ......................   Passed    0.02 sec
      Start 10: zufall_probe
10/13 Test #10: zufall_probe .....................   Passed    0.01 sec
      Start 11: zustand_probe
11/13 Test #11: zustand_probe ....................   Passed    0.02 sec
      Start 12: zustandsausgabe_probe
12/13 Test #12: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 13: wandschranke
13/13 Test #13: wandschranke .....................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 13

Total Test time (real) =   0.66 sec
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
[ 50%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[ 66%] Built target vorrat_kernanker_probe
[100%] Built target vorrat_verfahren_probe
[100%] Built target vorrat_probe
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
2/5 Test #2: belegstellen_messung .............   Passed   30.44 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........   Passed   17.02 sec
    Start 4: belegstellen_sammelordnung
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.66 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........***Failed   15.51 sec
Vorfassung: gefehlt und ist geholt worden -- Blob e3038e23316f4c18ca9bdd6cbab51e42579e7838 aus 83faa06^:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 5d5e2d6; HEAD zu Beginn: 7ebc1a9
A  vorher : Code 1, 36 Zitate, 34 aufgeloest, 57 uebergangen
A  nachher: Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Die Berichtigung bewegt die drei Zahlen des Riegels: (36, 34, 57) -> (36, 36, 57). Die Abnahme von 0115 nennt genau das einen Fehlschlag.
  FEHLSCHLAG: Die Berichtigung bewegt den Rueckgabewert: 1 -> 0.
  FEHLSCHLAG: Die Befundlisten sind nicht dieselben. Nur vorher: ['zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32', 'zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:39']. Nur nachher: [].
B1 ohne-marken-rein: Code 1, 47 Zitate, 36 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 51 Zitate unter der Mutation, gemessen sind 47.
  FEHLSCHLAG: Der Kopfkommentar nennt 40 Zitate ohne die Mutation, gemessen sind 36.
  FEHLSCHLAG: Der Kopfkommentar nennt 40 aufgeloeste Zitate, gemessen sind 36.
  FEHLSCHLAG: Der Kopfkommentar nennt 59 uebergangene Fundstellen unter der Mutation, gemessen sind 70.
  FEHLSCHLAG: Der Kopfkommentar nennt 47 uebergangene Fundstellen ohne sie, gemessen sind 57.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (40, 40, 47) als die Zahlen des unveraenderten Riegels, gemessen sind (36, 36, 57).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (36, 36, 57) statt (40, 40, 47).
  FEHLSCHLAG: Angabe 2 nennt die Summe 87; Zitate plus uebergangene Fundstellen sind 93.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 47 Zitate, 36 aufgeloest, 70 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'sonst': 8}
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die Angabe 1 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die die Aufschluesselung bei Klammer::kuendigt_an traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
  FEHLSCHLAG: 8 Selbsttreffer liegen weder im Kopfkommentar noch in einer genannten Falltabelle -- die Aufschluesselung ist unvollstaendig.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 36 Zitate, 36 aufgeloest, 57 uebergangen
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die Angabe 2 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
  FEHLSCHLAG: Im Quelltext steht keine Aussage der Form, die die Fallangabe von Angabe 2 traegt -- entweder ist sie geloescht oder umformuliert worden. Ohne sie misst dieser Riegel nichts.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt achte
  FEHLSCHLAG: Der Kopf nennt den achte Fall, historisch ausgewiesen ist der 7.
  FEHLSCHLAG: Der Kopf nennt den achten Fall zugleich historisch und abgewandelt -- genau der Widerspruch, den 0115 aufloest.
G  Gegenprobe am Wortlaut vor der Berichtigung -- Angabe 1: 3 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 2 Meldung(en)
HEAD am Ende: 7ebc1a9
Hinweis: HEAD steht auf 7ebc1a9, gemessen und niedergeschrieben ist der Stand 5d5e2d6. Die Zahlen sind damit aelter als der Baum.

11 Erwartung(en) nicht erfuellt.


80% tests passed, 1 tests failed out of 5

Total Test time (real) =  69.67 sec

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
1/1 Test #1: bezeichner_riegel ................   Passed    0.37 sec

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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.51 sec

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

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/3 Test #1: zahlwort_riegel ..................   Passed    0.04 sec
    Start 2: zahlwort_reihen
2/3 Test #2: zahlwort_reihen ..................   Passed    0.13 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................   Passed   18.27 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.44 sec
```
