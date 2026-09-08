---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-08
bauart: cmake
manifeste: 9
ergebnis: fehler
---

# Der Compiler hat gesprochen: fehler

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 13 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 25 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 443 Schaltereintraege.
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand
[  7%] Built target zahlwort_riegel
[ 12%] Built target bezeichner_riegel
[ 14%] Built target pruefstand_geprueft
[ 15%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 31%] Built target kern
[ 47%] Built target kern_geprueft
[ 50%] Building CXX object werkzeuge/kennzeichen/CMakeFiles/kennzeichen_riegel.dir/kennzeichen_riegel.cpp.o
[ 51%] Built target mutationstreiber
[ 54%] Built target vorrat_verfahren_probe
[ 57%] Built target vorrat_kernanker_probe
[ 62%] Built target meldung_probe
[ 62%] Built target vorrat_probe
[ 65%] Built target festkomma_probe
[ 68%] Built target kennzeichen_probe
[ 74%] Built target verlauf_probe
[ 74%] Built target pruefsumme_probe
[ 77%] Built target aktion_probe
[ 80%] Built target schritt_probe
[ 82%] Built target zufall_probe
[ 85%] Built target schranken_probe
[ 91%] Built target schreiber_probe
[ 91%] Built target zustand_probe
[ 94%] Built target werte_probe
[ 97%] Built target zustandsausgabe_probe
[ 98%] Linking CXX executable kennzeichen_riegel
[ 98%] Built target kennzeichen_riegel
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
e         Rueckgabe 0, Zahlen (50, 50, 45)  -- die unveraenderte Fassung -- der Nullpunkt
    abstand4      Rueckgabe 0, Zahlen (49, 49, 45)  -- Schwelle vier, sonst wie 'nur der Wortabstand'
    abstand5      wortgleich mit nur-abstand -- dieselbe Messung, nicht noch einmal uebersetzt.
    abstand5      Rueckgabe 0, Zahlen (49, 49, 46)  -- Schwelle fuenf, sonst wie 'nur der Wortabstand'

Grundzahl (unveraenderte Fassung): (50, 50, 45)
Unterschiede:
    keine von beiden          (-1, -1, -1)
    nur der Wortabstand       (-1, -1, 1)
    nur die Suche nach rechts (-1, -1, -1)
    beide                     (0, 0, 0)
    Schwelle vier             (-1, -1, 0)
    Schwelle fuenf            (-1, -1, 1)

Teil 3 -- der Kopfkommentar gegen die Messung
ROT die Zeile 'keine von beiden' sagt (-1, -1, 0), gemessen wurde (-1, -1, -1)
ROT die Zeile 'nur die Suche nach rechts' sagt (-1, -1, 0), gemessen wurde (-1, -1, -1)
OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich 6 Beanstandung(en):
      die Zeile 'keine von beiden' sagt (33, 33, 58), gemessen wurde (-1, -1, -1)
      die Zeile 'nur der Wortabstand' sagt (33, 33, 59), gemessen wurde (-1, -1, 1)
      die Zeile 'nur die Suche nach rechts' sagt (33, 33, 58), gemessen wurde (-1, -1, -1)

Teil 4 -- die Aussage des Kopfes, an den gemessenen Zahlen nachgerechnet
OK  keine Lockerung allein traegt ein Zitat
OK  die Suche nach rechts allein aendert keine der drei Zahlen
ROT die Schwelle vier faengt die Stelle nicht
OK  die Schwelle fuenf faengt sie -- eine uebergangene Fundstelle mehr

Messstand 0166: 3 Abweichung(en).

      Start 21: belegstellen_sammelordnung
21/28 Test #21: belegstellen_sammelordnung .......   Passed    5.71 sec
      Start 22: belegstellen_kopfzahlen
22/28 Test #22: belegstellen_kopfzahlen ..........***Failed   15.96 sec
Vorfassung: gefehlt und ist geholt worden -- Blob ee8d0283558d485f3b3482f025ad18769bf414a5 aus dbcd637:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 2f2f79f; HEAD zu Beginn: bff08ee
A  vorher : Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
A  nachher: Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
B1 ohne-marken-rein: Code 1, 61 Zitate, 50 aufgeloest, 59 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 52 Zitate unter der Mutation, gemessen sind 61.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 aufgeloeste Zitate, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 59.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 45.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (50, 50, 45).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (50, 50, 45) statt (41, 41, 53).
  FEHLSCHLAG: Angabe 2 nennt die Summe 94; Zitate plus uebergangene Fundstellen sind 95.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 61 Zitate, 50 aufgeloest, 59 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 53 Zitate unter der Mutation, gemessen sind 61.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 aufgeloeste Zitate, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 59.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 45.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (50, 50, 45).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (50, 50, 45) statt (41, 41, 53).
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt erste
  FEHLSCHLAG: Der Kopf nennt den erste Fall, historisch ausgewiesen ist der 7.
G  Gegenprobe an der verstellten Angabe -- Angabe 1: 5 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 1 Meldung(en)
HEAD am Ende: bff08ee
Hinweis: HEAD steht auf bff08ee, gemessen und niedergeschrieben ist der Stand 2f2f79f. Die Zahlen sind damit aelter als der Baum.

8 Erwartung(en) nicht erfuellt.

      Start 23: bezeichner_riegel
23/28 Test #23: bezeichner_riegel ................   Passed    0.44 sec
      Start 24: schlussriegel_nachbau
24/28 Test #24: schlussriegel_nachbau ............   Passed    0.51 sec
      Start 25: zahlwort_riegel
25/28 Test #25: zahlwort_riegel ..................   Passed    0.04 sec
      Start 26: zahlwort_reihen
26/28 Test #26: zahlwort_reihen ..................   Passed    0.13 sec
      Start 27: zahlwort_messung
27/28 Test #27: zahlwort_messung .................   Passed   18.60 sec
      Start 28: kennzeichen_riegel
28/28 Test #28: kennzeichen_riegel ...............   Passed    0.12 sec

93% tests passed, 2 tests failed out of 28

Total Test time (real) =  91.79 sec

The following tests FAILED:
	 20 - belegstellen_wortabstand (Failed)
	 22 - belegstellen_kopfzahlen (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 13 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 15 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 259 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 45%] Built target kern
[ 45%] Built target kern_geprueft
[ 50%] Built target meldung_probe
[ 54%] Built target schreiber_probe
[ 62%] Built target kennzeichen_probe
[ 62%] Built target pruefsumme_probe
[ 66%] Built target festkomma_probe
[ 75%] Built target schranken_probe
[ 75%] Built target schritt_probe
[ 79%] Built target verlauf_probe
[ 83%] Built target aktion_probe
[ 87%] Built target zufall_probe
[ 91%] Built target werte_probe
[100%] Built target zustand_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
      Start  1: aktion_probe
 1/14 Test  #1: aktion_probe .....................   Passed    0.01 sec
      Start  2: festkomma_probe
 2/14 Test  #2: festkomma_probe ..................   Passed    0.01 sec
      Start  3: kennzeichen_probe
 3/14 Test  #3: kennzeichen_probe ................   Passed    0.02 sec
      Start  4: meldung_probe
 4/14 Test  #4: meldung_probe ....................   Passed    0.01 sec
      Start  5: pruefsumme_probe
 5/14 Test  #5: pruefsumme_probe .................   Passed    0.01 sec
      Start  6: schranken_probe
 6/14 Test  #6: schranken_probe ..................   Passed    0.01 sec
      Start  7: schreiber_probe
 7/14 Test  #7: schreiber_probe ..................   Passed    0.01 sec
      Start  8: schritt_probe
 8/14 Test  #8: schritt_probe ....................   Passed    0.02 sec
      Start  9: verlauf_probe
 9/14 Test  #9: verlauf_probe ....................   Passed    0.02 sec
      Start 10: werte_probe
10/14 Test #10: werte_probe ......................   Passed    0.02 sec
      Start 11: zufall_probe
11/14 Test #11: zufall_probe .....................   Passed    0.01 sec
      Start 12: zustand_probe
12/14 Test #12: zustand_probe ....................   Passed    0.02 sec
      Start 13: zustandsausgabe_probe
13/14 Test #13: zustandsausgabe_probe ............   Passed    0.09 sec
      Start 14: wandschranke
14/14 Test #14: wandschranke .....................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 14

Total Test time (real) =   0.69 sec
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
inmal.

Teil 1 -- der Vorlauf: die Fassung vor 0166 und die danach
[vorher ] Rueckgabe 0, Zahlen (50, 50, 45)
[nachher] Rueckgabe 0, Zahlen (50, 50, 45)
GLEICH  die drei Zahlen von Bedingung 2.

Teil 2 -- die sechs Fassungen
    ohne-abstand  Rueckgabe 0, Zahlen (49, 49, 44)  -- keine der beiden Lockerungen
    nur-abstand   Rueckgabe 0, Zahlen (49, 49, 46)  -- nur der Wortabstand, die Suche nach rechts abgeschaltet
    nur-rechts    Rueckgabe 0, Zahlen (49, 49, 44)  -- nur die Suche nach rechts, der Wortabstand abgeschaltet
    beide         wortgleich mit riegel-nachher aus Teil 1 -- dieselbe Messung, nicht noch einmal uebersetzt.
    beide         Rueckgabe 0, Zahlen (50, 50, 45)  -- die unveraenderte Fassung -- der Nullpunkt
    abstand4      Rueckgabe 0, Zahlen (49, 49, 45)  -- Schwelle vier, sonst wie 'nur der Wortabstand'
    abstand5      wortgleich mit nur-abstand -- dieselbe Messung, nicht noch einmal uebersetzt.
    abstand5      Rueckgabe 0, Zahlen (49, 49, 46)  -- Schwelle fuenf, sonst wie 'nur der Wortabstand'

Grundzahl (unveraenderte Fassung): (50, 50, 45)
Unterschiede:
    keine von beiden          (-1, -1, -1)
    nur der Wortabstand       (-1, -1, 1)
    nur die Suche nach rechts (-1, -1, -1)
    beide                     (0, 0, 0)
    Schwelle vier             (-1, -1, 0)
    Schwelle fuenf            (-1, -1, 1)

Teil 3 -- der Kopfkommentar gegen die Messung
ROT die Zeile 'keine von beiden' sagt (-1, -1, 0), gemessen wurde (-1, -1, -1)
ROT die Zeile 'nur die Suche nach rechts' sagt (-1, -1, 0), gemessen wurde (-1, -1, -1)
OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich 6 Beanstandung(en):
      die Zeile 'keine von beiden' sagt (33, 33, 58), gemessen wurde (-1, -1, -1)
      die Zeile 'nur der Wortabstand' sagt (33, 33, 59), gemessen wurde (-1, -1, 1)
      die Zeile 'nur die Suche nach rechts' sagt (33, 33, 58), gemessen wurde (-1, -1, -1)

Teil 4 -- die Aussage des Kopfes, an den gemessenen Zahlen nachgerechnet
OK  keine Lockerung allein traegt ein Zitat
OK  die Suche nach rechts allein aendert keine der drei Zahlen
ROT die Schwelle vier faengt die Stelle nicht
OK  die Schwelle fuenf faengt sie -- eine uebergangene Fundstelle mehr

Messstand 0166: 3 Abweichung(en).

    Start 4: belegstellen_sammelordnung
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.71 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........***Failed   16.02 sec
Vorfassung: gefehlt und ist geholt worden -- Blob ee8d0283558d485f3b3482f025ad18769bf414a5 aus dbcd637:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 2f2f79f; HEAD zu Beginn: bff08ee
A  vorher : Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
A  nachher: Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
B1 ohne-marken-rein: Code 1, 61 Zitate, 50 aufgeloest, 59 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 52 Zitate unter der Mutation, gemessen sind 61.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 aufgeloeste Zitate, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 59.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 45.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (50, 50, 45).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (50, 50, 45) statt (41, 41, 53).
  FEHLSCHLAG: Angabe 2 nennt die Summe 94; Zitate plus uebergangene Fundstellen sind 95.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 61 Zitate, 50 aufgeloest, 59 uebergangen; 11 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 53 Zitate unter der Mutation, gemessen sind 61.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 aufgeloeste Zitate, gemessen sind 50.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 59.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 45.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 50 Zitate, 50 aufgeloest, 45 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (50, 50, 45).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (50, 50, 45) statt (41, 41, 53).
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt erste
  FEHLSCHLAG: Der Kopf nennt den erste Fall, historisch ausgewiesen ist der 7.
G  Gegenprobe an der verstellten Angabe -- Angabe 1: 5 Meldung(en), Angabe 2: 2 Meldung(en), Angabe 3: 1 Meldung(en)
HEAD am Ende: bff08ee
Hinweis: HEAD steht auf bff08ee, gemessen und niedergeschrieben ist der Stand 2f2f79f. Die Zahlen sind damit aelter als der Baum.

8 Erwartung(en) nicht erfuellt.


60% tests passed, 2 tests failed out of 5

Total Test time (real) =  71.28 sec

The following tests FAILED:
	  3 - belegstellen_wortabstand (Failed)
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.44 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.44 sec
```

## `cmake -S` -- ok (Code 0)

```
-- Nullabhaengigkeitsriegel (T2): keines der Ziele aus FABRIK_NULLABHAENGIG (kern;kern_geprueft) liegt in diesem Baum -- nichts gelesen.
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 19 Schaltereintraege.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/bau
```

## `cmake --build` -- ok (Code 0)

```
[ 50%] Building CXX object CMakeFiles/kennzeichen_riegel.dir/kennzeichen_riegel.cpp.o
[100%] Linking CXX executable kennzeichen_riegel
[100%] Built target kennzeichen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/bau
    Start 1: kennzeichen_riegel
1/1 Test #1: kennzeichen_riegel ...............   Passed    0.12 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.12 sec
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
3/3 Test #3: zahlwort_messung .................   Passed   18.59 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.76 sec
```
