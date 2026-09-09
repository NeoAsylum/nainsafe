---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-08
bauart: cmake
manifeste: 10
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
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 26 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 462 Schaltereintraege.
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Built target pruefstand
[  5%] Building CXX object werkzeuge/kennzeichen/CMakeFiles/kennzeichen_riegel.dir/kennzeichen_riegel.cpp.o
[ 11%] Built target zahlwort_riegel
[ 11%] Built target bezeichner_riegel
[ 15%] Built target pruefstand_geprueft
[ 30%] Built target kern_geprueft
[ 33%] Built target mutationstreiber
[ 34%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 37%] Built target multiplikationsriegel
[ 52%] Built target kern
[ 55%] Built target aktion_probe
[ 58%] Built target vorrat_verfahren_probe
[ 61%] Built target meldung_probe
[ 63%] Built target vorrat_kernanker_probe
[ 66%] Built target vorrat_probe
[ 69%] Built target pruefsumme_probe
[ 72%] Built target schreiber_probe
[ 75%] Built target schranken_probe
[ 77%] Built target festkomma_probe
[ 80%] Built target verlauf_probe
[ 83%] Built target schritt_probe
[ 86%] Built target kennzeichen_probe
[ 88%] Built target zufall_probe
[ 91%] Built target zustandsausgabe_probe
[ 94%] Built target werte_probe
[ 97%] Built target zustand_probe
[ 98%] Linking CXX executable kennzeichen_riegel
[ 98%] Built target kennzeichen_riegel
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
belegstellen_riegel ..............   Passed    1.22 sec
      Start 19: belegstellen_messung
19/29 Test #19: belegstellen_messung .............   Passed   31.26 sec
      Start 20: belegstellen_wortabstand
20/29 Test #20: belegstellen_wortabstand .........***Failed   17.37 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: a44c183
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

      Start 21: belegstellen_sammelordnung
21/29 Test #21: belegstellen_sammelordnung .......   Passed    5.71 sec
      Start 22: belegstellen_kopfzahlen
22/29 Test #22: belegstellen_kopfzahlen ..........   Passed   10.06 sec
      Start 23: bezeichner_riegel
23/29 Test #23: bezeichner_riegel ................   Passed    0.46 sec
      Start 24: schlussriegel_nachbau
24/29 Test #24: schlussriegel_nachbau ............   Passed    0.50 sec
      Start 25: zahlwort_riegel
25/29 Test #25: zahlwort_riegel ..................   Passed    0.05 sec
      Start 26: zahlwort_reihen
26/29 Test #26: zahlwort_reihen ..................   Passed    0.13 sec
      Start 27: zahlwort_messung
27/29 Test #27: zahlwort_messung .................   Passed   18.49 sec
      Start 28: kennzeichen_riegel
28/29 Test #28: kennzeichen_riegel ...............   Passed    0.12 sec
      Start 29: multiplikationsriegel
29/29 Test #29: multiplikationsriegel ............***Failed    0.06 sec

multiplikationsriegel: blanke Multiplikation ohne benannte Regel. Massnahme 4.3
aus T7 verlangt `mal(a, b)` und den `__int128`-Waechter:

  kern/include/kern/festkomma.hpp:99
      const i128 rest = az - ganz * an;          // 0 <= rest < an, weil beide >= 0 sind
  kern/include/kern/festkomma.hpp:356
      const i128 naechst = ((static_cast<i128>(n) - 1) * r + ziel / intern::potenz_i128(r, n - 1))

2 Stelle(n). Wer eine davon fuer richtig haelt, aendert nicht diesen Riegel,
sondern den Regelsatz in T7 -- und dann faellt sie unter eine **benannte** Regel.
multiplikationsriegel, Selbsttest: 9 Faelle zur Lesung und 23 zu den Regeln,
alle wie erwartet.
multiplikationsriegel: 23 Dateien gelesen, 84 Namen in der Liste der Layout-
konstanten, 7 in der der u64-Konstanten. Binaere `*` nach der Lesung:
42 Vorkommen in 36 Zeilen.
  Regel 1  Layoutkonstante (Index, std::size_t)               31 Vorkommen in  26 Zeilen
  Regel 2  sizeof                                              0 Vorkommen in   0 Zeilen
  Regel 3  vorzeichenlos (Literal oder u64-Konstante)          6 Vorkommen in   5 Zeilen
  Regel 4  static_cast<i128> auf beiden Seiten                 2 Vorkommen in   2 Zeilen
  Regel 5  Literale in der Bedingung eines static_assert       1 Vorkommen in   1 Zeilen
  BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)   2 Vorkommen in   2 Zeilen


93% tests passed, 2 tests failed out of 29

Total Test time (real) =  86.17 sec

The following tests FAILED:
	 20 - belegstellen_wortabstand (Failed)
	 29 - multiplikationsriegel (Failed)
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
[ 50%] Built target aktion_probe
[ 54%] Built target kennzeichen_probe
[ 60%] Built target meldung_probe
[ 62%] Built target pruefsumme_probe
[ 70%] Built target festkomma_probe
[ 70%] Built target schreiber_probe
[ 75%] Built target schranken_probe
[ 79%] Built target verlauf_probe
[ 91%] Built target werte_probe
[ 91%] Built target zufall_probe
[ 91%] Built target schritt_probe
[ 95%] Built target zustandsausgabe_probe
[100%] Built target zustand_probe
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
14/14 Test #14: wandschranke .....................   Passed    0.43 sec

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
[ 50%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
[100%] Built target vorrat_verfahren_probe
[100%] Built target vorrat_probe
[100%] Built target vorrat_kernanker_probe
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
1/5 Test #1: belegstellen_riegel ..............   Passed    1.20 sec
    Start 2: belegstellen_messung
2/5 Test #2: belegstellen_messung .............   Passed   31.09 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........***Failed   17.46 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: a44c183
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
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.77 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........   Passed   10.08 sec

80% tests passed, 1 tests failed out of 5

Total Test time (real) =  65.60 sec

The following tests FAILED:
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.49 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.49 sec
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
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/bau
```

## `cmake --build` -- ok (Code 0)

```
[100%] Built target multiplikationsriegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/bau
    Start 1: multiplikationsriegel
1/1 Test #1: multiplikationsriegel ............***Failed    0.06 sec

multiplikationsriegel: blanke Multiplikation ohne benannte Regel. Massnahme 4.3
aus T7 verlangt `mal(a, b)` und den `__int128`-Waechter:

  kern/include/kern/festkomma.hpp:99
      const i128 rest = az - ganz * an;          // 0 <= rest < an, weil beide >= 0 sind
  kern/include/kern/festkomma.hpp:356
      const i128 naechst = ((static_cast<i128>(n) - 1) * r + ziel / intern::potenz_i128(r, n - 1))

2 Stelle(n). Wer eine davon fuer richtig haelt, aendert nicht diesen Riegel,
sondern den Regelsatz in T7 -- und dann faellt sie unter eine **benannte** Regel.
multiplikationsriegel, Selbsttest: 9 Faelle zur Lesung und 23 zu den Regeln,
alle wie erwartet.
multiplikationsriegel: 23 Dateien gelesen, 84 Namen in der Liste der Layout-
konstanten, 7 in der der u64-Konstanten. Binaere `*` nach der Lesung:
42 Vorkommen in 36 Zeilen.
  Regel 1  Layoutkonstante (Index, std::size_t)               31 Vorkommen in  26 Zeilen
  Regel 2  sizeof                                              0 Vorkommen in   0 Zeilen
  Regel 3  vorzeichenlos (Literal oder u64-Konstante)          6 Vorkommen in   5 Zeilen
  Regel 4  static_cast<i128> auf beiden Seiten                 2 Vorkommen in   2 Zeilen
  Regel 5  Literale in der Bedingung eines static_assert       1 Vorkommen in   1 Zeilen
  BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)   2 Vorkommen in   2 Zeilen


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.06 sec

The following tests FAILED:
	  1 - multiplikationsriegel (Failed)
Errors while running CTest
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
