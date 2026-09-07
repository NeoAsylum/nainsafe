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
[  3%] Built target mutationstreiber
[ 10%] Built target pruefstand_geprueft
[ 12%] Built target pruefstand
[ 15%] Built target zahlwort_riegel
[ 31%] Built target kern
[ 37%] Built target bezeichner_riegel
[ 53%] Built target belegstellen_riegel
[ 54%] Built target kern_geprueft
[ 60%] Built target aktion_probe
[ 60%] Built target vorrat_kernanker_probe
[ 72%] Built target festkomma_probe
[ 72%] Built target vorrat_verfahren_probe
[ 72%] Built target meldung_probe
[ 72%] Built target pruefsumme_probe
[ 75%] Built target schranken_probe
[ 78%] Built target vorrat_probe
[ 81%] Built target schreiber_probe
[ 95%] Built target zufall_probe
[ 95%] Built target verlauf_probe
[ 95%] Built target zustand_probe
[ 95%] Built target schritt_probe
[ 96%] Built target werte_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
4'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M6-anfuehrung-nach-hinten -- die unmittelbare Anfuehrung wird zuletzt gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 2'] (erwartet ['Formfall 2'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M7-ohne-anfuehrung-nach-hinten -- die Form ohne Anfuehrung wird zuletzt gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 3'] (erwartet ['Formfall 3'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M8-abstand-entfaellt -- die dritte Form wird gar nicht mehr gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 1'] (erwartet ['Formfall 1'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M9-immer-eine-form -- jede Stelle gilt als Fundstelle
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 4'] (erwartet ['Formfall 4'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)

Arbeitsbaum vorher/nachher: 82fa870 / 82fa870
Aenderungen an der gemessenen Datei seit adbf4a8:
  6c34479 testentwickler: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen (5 Dateien)
  f66da43 testentwickler: 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen (10 Dateien)
  584326c testentwickler: 0147-belegstellenriegel-ortsfrage-mit-anker (1 Dateien)

Messstand 0147: 2 Abweichung(en).

      Start 19: belegstellen_wortabstand
19/24 Test #19: belegstellen_wortabstand .........***Failed   18.02 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: 82fa870
Schalter:    -std=c++20 -fwrapv -fno-fast-math -O2

Teil 0 -- der Messstand selbst
OK  Selbstprobe: alle sechs Zeilen werden gelesen und keine fremde dazu.
OK  Selbstprobe: der Vergleich schweigt, wo alles stimmt.
OK  Selbstprobe: eine falsche Zahl wird genau einmal und namentlich beanstandet.
OK  Selbstprobe: eine fehlende Zeile wird beanstandet und nicht ueberlesen.
OK  Selbstprobe: die Zahlenzeile des Riegels wird gelesen.
OK  Selbstprobe: eine Ausgabe ohne Zahlenzeile gibt nichts her.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'fehlt'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'zweimal'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'genau einmal'.
OK  Selbstprobe: alle Nadeln treffen genau einmal.

Teil 1 -- der Vorlauf: die Fassung vor 0166 und die danach
[vorher ] Rueckgabe 1, Zahlen (40, 36, 53)
[nachher] Rueckgabe 1, Zahlen (40, 36, 53)
GLEICH  die drei Zahlen von Bedingung 2.

Teil 2 -- die sechs Fassungen
    ohne-abstand  Rueckgabe 1, Zahlen (39, 36, 53)  -- keine der beiden Lockerungen
    nur-abstand   Rueckgabe 1, Zahlen (39, 36, 54)  -- nur der Wortabstand, die Suche nach rechts abgeschaltet
    nur-rechts    Rueckgabe 1, Zahlen (39, 36, 53)  -- nur die Suche nach rechts, der Wortabstand abgeschaltet
    beide         wortgleich mit riegel-nachher aus Teil 1 -- dieselbe Messung, nicht noch einmal uebersetzt.
    beide         Rueckgabe 1, Zahlen (40, 36, 53)  -- die unveraenderte Fassung -- der Nullpunkt
    abstand4      Rueckgabe 1, Zahlen (39, 36, 53)  -- Schwelle vier, sonst wie 'nur der Wortabstand'
    abstand5      wortgleich mit nur-abstand -- dieselbe Messung, nicht noch einmal uebersetzt.
    abstand5      Rueckgabe 1, Zahlen (39, 36, 54)  -- Schwelle fuenf, sonst wie 'nur der Wortabstand'

Grundzahl (unveraenderte Fassung): (40, 36, 53)
Unterschiede:
    keine von beiden          (-1, 0, 0)
    nur der Wortabstand       (-1, 0, 1)
    nur die Suche nach rechts (-1, 0, 0)
    beide                     (0, 0, 0)
    Schwelle vier             (-1, 0, 0)
    Schwelle fuenf            (-1, 0, 1)

Teil 3 -- der Kopfkommentar gegen die Messung
ROT die Zeile 'keine von beiden' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'nur der Wortabstand' sagt (-1, -1, 1), gemessen wurde (-1, 0, 1)
ROT die Zeile 'nur die Suche nach rechts' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'Schwelle vier' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'Schwelle fuenf' sagt (-1, -1, 1), gemessen wurde (-1, 0, 1)
OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich 6 Beanstandung(en):
      die Zeile 'keine von beiden' sagt (33, 33, 58), gemessen wurde (-1, 0, 0)
      die Zeile 'nur der Wortabstand' sagt (33, 33, 59), gemessen wurde (-1, 0, 1)
      die Zeile 'nur die Suche nach rechts' sagt (33, 33, 58), gemessen wurde (-1, 0, 0)

Teil 4 -- die Aussage des Kopfes, an den gemessenen Zahlen nachgerechnet
OK  keine Lockerung allein traegt ein Zitat
OK  die Suche nach rechts allein aendert keine der drei Zahlen
OK  die Schwelle vier faengt die Stelle nicht
OK  die Schwelle fuenf faengt sie -- eine uebergangene Fundstelle mehr

Messstand 0166: 5 Abweichung(en).

      Start 20: bezeichner_riegel
20/24 Test #20: bezeichner_riegel ................   Passed    0.38 sec
      Start 21: schlussriegel_nachbau
21/24 Test #21: schlussriegel_nachbau ............   Passed    0.54 sec
      Start 22: zahlwort_riegel
22/24 Test #22: zahlwort_riegel ..................   Passed    0.05 sec
      Start 23: zahlwort_reihen
23/24 Test #23: zahlwort_reihen ..................   Passed    0.14 sec
      Start 24: zahlwort_messung
24/24 Test #24: zahlwort_messung .................   Passed   19.20 sec

88% tests passed, 3 tests failed out of 24

Total Test time (real) =  71.77 sec

The following tests FAILED:
	 17 - belegstellen_riegel (Failed)
	 18 - belegstellen_messung (Failed)
	 19 - belegstellen_wortabstand (Failed)
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
[ 47%] Built target kern_geprueft
[ 47%] Built target kern
[ 52%] Built target festkomma_probe
[ 60%] Built target meldung_probe
[ 58%] Built target pruefsumme_probe
[ 65%] Built target aktion_probe
[ 69%] Built target schritt_probe
[ 73%] Built target schreiber_probe
[ 78%] Built target verlauf_probe
[ 82%] Built target schranken_probe
[ 86%] Built target werte_probe
[ 91%] Built target zufall_probe
[ 95%] Built target zustand_probe
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
 7/13 Test  #7: schritt_probe ....................   Passed    0.02 sec
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
13/13 Test #13: wandschranke .....................   Passed    0.45 sec

100% tests passed, 0 tests failed out of 13

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
[ 83%] Built target vorrat_verfahren_probe
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
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
rtet False)
OK  M4-nachschlagen-uebergangen -- der Regelfall: nachschlagen wird zu uebergangen
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Ortsfall 1'] (erwartet ['Ortsfall 1'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M5-zaehlregel-abgeschaltet -- das tote Ziel zaehlt nicht mehr als Zitat
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Ortsfall 4'] (erwartet ['Ortsfall 4'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M6-anfuehrung-nach-hinten -- die unmittelbare Anfuehrung wird zuletzt gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 2'] (erwartet ['Formfall 2'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M7-ohne-anfuehrung-nach-hinten -- die Form ohne Anfuehrung wird zuletzt gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 3'] (erwartet ['Formfall 3'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M8-abstand-entfaellt -- die dritte Form wird gar nicht mehr gefragt
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 1'] (erwartet ['Formfall 1'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)
OK  M9-immer-eine-form -- jede Stelle gilt als Fundstelle
      Rueckgabe 2 (erwartet 2)
      Faelle gerissen laut Riegel: 1 (erwartet 1)
      gerissen: ['Formfall 4'] (erwartet ['Formfall 4'])
      fremde Tabellen gerissen: [] (erwartet [])
      Bestand gelesen: False (erwartet False)

Arbeitsbaum vorher/nachher: 82fa870 / 82fa870
Aenderungen an der gemessenen Datei seit adbf4a8:
  6c34479 testentwickler: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen (5 Dateien)
  f66da43 testentwickler: 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen (10 Dateien)
  584326c testentwickler: 0147-belegstellenriegel-ortsfrage-mit-anker (1 Dateien)

Messstand 0147: 2 Abweichung(en).

    Start 3: belegstellen_wortabstand
3/3 Test #3: belegstellen_wortabstand .........***Failed   17.50 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: 82fa870
Schalter:    -std=c++20 -fwrapv -fno-fast-math -O2

Teil 0 -- der Messstand selbst
OK  Selbstprobe: alle sechs Zeilen werden gelesen und keine fremde dazu.
OK  Selbstprobe: der Vergleich schweigt, wo alles stimmt.
OK  Selbstprobe: eine falsche Zahl wird genau einmal und namentlich beanstandet.
OK  Selbstprobe: eine fehlende Zeile wird beanstandet und nicht ueberlesen.
OK  Selbstprobe: die Zahlenzeile des Riegels wird gelesen.
OK  Selbstprobe: eine Ausgabe ohne Zahlenzeile gibt nichts her.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'fehlt'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'zweimal'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'genau einmal'.
OK  Selbstprobe: alle Nadeln treffen genau einmal.

Teil 1 -- der Vorlauf: die Fassung vor 0166 und die danach
[vorher ] Rueckgabe 1, Zahlen (40, 36, 53)
[nachher] Rueckgabe 1, Zahlen (40, 36, 53)
GLEICH  die drei Zahlen von Bedingung 2.

Teil 2 -- die sechs Fassungen
    ohne-abstand  Rueckgabe 1, Zahlen (39, 36, 53)  -- keine der beiden Lockerungen
    nur-abstand   Rueckgabe 1, Zahlen (39, 36, 54)  -- nur der Wortabstand, die Suche nach rechts abgeschaltet
    nur-rechts    Rueckgabe 1, Zahlen (39, 36, 53)  -- nur die Suche nach rechts, der Wortabstand abgeschaltet
    beide         wortgleich mit riegel-nachher aus Teil 1 -- dieselbe Messung, nicht noch einmal uebersetzt.
    beide         Rueckgabe 1, Zahlen (40, 36, 53)  -- die unveraenderte Fassung -- der Nullpunkt
    abstand4      Rueckgabe 1, Zahlen (39, 36, 53)  -- Schwelle vier, sonst wie 'nur der Wortabstand'
    abstand5      wortgleich mit nur-abstand -- dieselbe Messung, nicht noch einmal uebersetzt.
    abstand5      Rueckgabe 1, Zahlen (39, 36, 54)  -- Schwelle fuenf, sonst wie 'nur der Wortabstand'

Grundzahl (unveraenderte Fassung): (40, 36, 53)
Unterschiede:
    keine von beiden          (-1, 0, 0)
    nur der Wortabstand       (-1, 0, 1)
    nur die Suche nach rechts (-1, 0, 0)
    beide                     (0, 0, 0)
    Schwelle vier             (-1, 0, 0)
    Schwelle fuenf            (-1, 0, 1)

Teil 3 -- der Kopfkommentar gegen die Messung
ROT die Zeile 'keine von beiden' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'nur der Wortabstand' sagt (-1, -1, 1), gemessen wurde (-1, 0, 1)
ROT die Zeile 'nur die Suche nach rechts' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'Schwelle vier' sagt (-1, -1, 0), gemessen wurde (-1, 0, 0)
ROT die Zeile 'Schwelle fuenf' sagt (-1, -1, 1), gemessen wurde (-1, 0, 1)
OK  Rotnachweis: gegen den Kopf vor Paket 0166 haette dieser Vergleich 6 Beanstandung(en):
      die Zeile 'keine von beiden' sagt (33, 33, 58), gemessen wurde (-1, 0, 0)
      die Zeile 'nur der Wortabstand' sagt (33, 33, 59), gemessen wurde (-1, 0, 1)
      die Zeile 'nur die Suche nach rechts' sagt (33, 33, 58), gemessen wurde (-1, 0, 0)

Teil 4 -- die Aussage des Kopfes, an den gemessenen Zahlen nachgerechnet
OK  keine Lockerung allein traegt ein Zitat
OK  die Suche nach rechts allein aendert keine der drei Zahlen
OK  die Schwelle vier faengt die Stelle nicht
OK  die Schwelle fuenf faengt sie -- eine uebergangene Fundstelle mehr

Messstand 0166: 5 Abweichung(en).


0% tests passed, 3 tests failed out of 3

Total Test time (real) =  50.33 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
	  2 - belegstellen_messung (Failed)
	  3 - belegstellen_wortabstand (Failed)
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
1/1 Test #1: schlussriegel_nachbau ............   Passed    0.52 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.52 sec
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
3/3 Test #3: zahlwort_messung .................   Passed   19.22 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  19.39 sec
```
