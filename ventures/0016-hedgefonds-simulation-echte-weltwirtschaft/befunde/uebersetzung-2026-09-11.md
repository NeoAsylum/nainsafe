---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-11
bauart: cmake
manifeste: 12
ergebnis: fehler
---

# Der Compiler hat gesprochen: fehler

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 13 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 32 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 572 Schaltereintraege.
-- Configuring done (0.5s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  9%] Built target mutationstreiber
[  9%] Built target pruefstand
[  9%] Built target pruefstand_geprueft
[ 10%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 13%] Built target zahlwort_riegel
[ 15%] Built target multiplikationsriegel
[ 17%] Built target belegstellen_riegel
[ 19%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[ 21%] Built target kennzeichen_riegel
[ 23%] Built target bezeichner_riegel
[ 26%] Built target vorrat_probe
[ 28%] Built target vorrat_kernanker_probe
[ 30%] Built target vorrat_verfahren_probe
[ 32%] Linking CXX static library libkern.a
[ 42%] Built target kern
[ 44%] Linking CXX static library libkern_geprueft.a
[ 46%] Built target daten
[ 47%] Building CXX object schnittstelle/CMakeFiles/schnittstelle.dir/src/partie.cpp.o
[ 58%] Built target kern_geprueft
[ 59%] Linking CXX executable meldung_probe
[ 60%] Linking CXX executable pruefsumme_probe
[ 61%] Linking CXX executable festkomma_probe
[ 63%] Linking CXX executable schranken_probe
[ 64%] Linking CXX executable kennzeichen_probe
[ 65%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 66%] Linking CXX executable schreiber_probe
[ 67%] Linking CXX executable verlauf_probe
[ 69%] Linking CXX executable werte_probe
[ 70%] Linking CXX executable zustand_probe
[ 71%] Linking CXX executable schritt_probe
[ 73%] Built target daten_geprueft
[ 75%] Linking CXX executable zustandsausgabe_probe
[ 76%] Linking CXX executable zufall_probe
[ 77%] Building CXX object schnittstelle/CMakeFiles/schnittstelle_geprueft.dir/src/partie.cpp.o
[ 78%] Linking CXX executable jahrgang_probe
[ 79%] Built target zufall_probe
[ 80%] Built target schranken_probe
[ 82%] Built target meldung_probe
[ 83%] Built target werte_probe
[ 84%] Built target zustand_probe
[ 85%] Built target schreiber_probe
[ 86%] Built target festkomma_probe
[ 88%] Built target schritt_probe
[ 89%] Built target zustandsausgabe_probe
[ 90%] Built target pruefsumme_probe
[ 91%] Built target kennzeichen_probe
[ 92%] Built target verlauf_probe
[ 94%] Built target jahrgang_probe
[ 95%] Linking CXX static library libschnittstelle.a
[ 95%] Built target schnittstelle
[ 96%] Linking CXX static library libschnittstelle_geprueft.a
[ 96%] Built target schnittstelle_geprueft
[ 97%] Building CXX object schnittstelle/CMakeFiles/partie_probe.dir/test/partie_probe.cpp.o
[ 98%] Linking CXX executable partie_probe
[100%] Linking CXX executable aktion_probe
[100%] Built target partie_probe
[100%] Built target aktion_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
t nichts her.
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

      Start 23: belegstellen_sammelordnung
23/31 Test #23: belegstellen_sammelordnung .......   Passed    5.67 sec
      Start 24: belegstellen_kopfzahlen
24/31 Test #24: belegstellen_kopfzahlen ..........   Passed   10.04 sec
      Start 25: bezeichner_riegel
25/31 Test #25: bezeichner_riegel ................   Passed    0.50 sec
      Start 26: schlussriegel_nachbau
26/31 Test #26: schlussriegel_nachbau ............   Passed    0.52 sec
      Start 27: zahlwort_riegel
27/31 Test #27: zahlwort_riegel ..................   Passed    0.06 sec
      Start 28: zahlwort_reihen
28/31 Test #28: zahlwort_reihen ..................   Passed    0.14 sec
      Start 29: zahlwort_messung
29/31 Test #29: zahlwort_messung .................***Failed    2.38 sec

messen.py: A2: '**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen' kommt 0 mal vor, erwartet war genau einmal. Die Zeilennummer dieser Behauptung ist damit nicht zu erheben; die Erwartung waere geraten.
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
  Selbstprobe: 5 Faelle zu zeile_von, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD 475f9718cb954b7fca7a004345e8aa4609d86655
  Pruefling  kern/include/kern/werte.hpp  Blob e6edd48208427e45f138b662c52d754f27f7cb18
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 44b531748490223616949f28c6ee1650f12ddb5b
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp


      Start 30: kennzeichen_riegel
30/31 Test #30: kennzeichen_riegel ...............   Passed    0.13 sec
      Start 31: multiplikationsriegel
31/31 Test #31: multiplikationsriegel ............***Failed    0.06 sec

multiplikationsriegel: blanke Multiplikation ohne benannte Regel. Massnahme 4.3
aus T7 verlangt `mal(a, b)` und den `__int128`-Waechter:

  kern/include/kern/festkomma.hpp:99
      const i128 rest = az - ganz * an;          // 0 <= rest < an, weil beide >= 0 sind

1 Stelle(n). Wer eine davon fuer richtig haelt, aendert nicht diesen Riegel,
sondern den Regelsatz in T7 -- und dann faellt sie unter eine **benannte** Regel.
multiplikationsriegel, Selbsttest: 9 Faelle zur Lesung und 27 zu den Regeln,
alle wie erwartet.
multiplikationsriegel: 23 Dateien gelesen, 89 Namen in der Liste der Layout-
konstanten, 7 in der der u64-Konstanten. Binaere `*` nach der Lesung:
45 Vorkommen in 39 Zeilen.
  Regel 1  Layoutkonstante (Index, std::size_t)               34 Vorkommen in  29 Zeilen
  Regel 2  sizeof                                              0 Vorkommen in   0 Zeilen
  Regel 3  vorzeichenlos (Literal oder u64-Konstante)          6 Vorkommen in   5 Zeilen
  Regel 4  static_cast<i128> am Kopf einer Seite, kein ?       3 Vorkommen in   3 Zeilen
  Regel 5  Literale in der Bedingung eines static_assert       1 Vorkommen in   1 Zeilen
  BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)   1 Vorkommen in   1 Zeilen

T7 `:882-888` nennt 36 Zeilen, gemessen sind es 39. Die Abweichung ist eine
Meldung ueber T7 und keine ueber diesen Riegel; die Stellen stehen unten.


90% tests passed, 3 tests failed out of 31

Total Test time (real) =  69.94 sec

The following tests FAILED:
	 22 - belegstellen_wortabstand (Failed)
	 29 - zahlwort_messung (Failed)
	 31 - multiplikationsriegel (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 13 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 18 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 314 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/bau
```

## `cmake --build` -- ok (Code 0)

```
[  3%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[  3%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[  5%] Linking CXX static library libkern.a
[ 22%] Built target kern
[ 24%] Linking CXX static library libkern_geprueft.a
[ 27%] Built target daten
[ 44%] Built target kern_geprueft
[ 46%] Linking CXX executable meldung_probe
[ 48%] Linking CXX executable festkomma_probe
[ 50%] Linking CXX executable kennzeichen_probe
[ 51%] Linking CXX executable pruefsumme_probe
[ 53%] Linking CXX executable schranken_probe
[ 55%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 57%] Linking CXX executable schritt_probe
[ 59%] Linking CXX executable schreiber_probe
[ 61%] Linking CXX executable verlauf_probe
[ 62%] Linking CXX executable zufall_probe
[ 66%] Linking CXX executable werte_probe
[ 66%] Linking CXX executable zustandsausgabe_probe
[ 68%] Linking CXX executable zustand_probe
[ 72%] Built target daten_geprueft
[ 74%] Linking CXX executable jahrgang_probe
[ 75%] Built target schranken_probe
[ 77%] Built target zustand_probe
[ 79%] Built target pruefsumme_probe
[ 81%] Built target meldung_probe
[ 83%] Built target zufall_probe
[ 85%] Built target verlauf_probe
[ 87%] Built target festkomma_probe
[ 88%] Built target werte_probe
[ 90%] Built target schritt_probe
[ 92%] Built target jahrgang_probe
[ 96%] Built target kennzeichen_probe
[ 96%] Built target schreiber_probe
[ 98%] Built target zustandsausgabe_probe
[100%] Linking CXX executable aktion_probe
[100%] Built target aktion_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/bau
      Start  1: jahrgang_probe
 1/15 Test  #1: jahrgang_probe ...................   Passed    0.01 sec
      Start  2: aktion_probe
 2/15 Test  #2: aktion_probe .....................   Passed    0.01 sec
      Start  3: festkomma_probe
 3/15 Test  #3: festkomma_probe ..................   Passed    0.01 sec
      Start  4: kennzeichen_probe
 4/15 Test  #4: kennzeichen_probe ................   Passed    0.02 sec
      Start  5: meldung_probe
 5/15 Test  #5: meldung_probe ....................   Passed    0.01 sec
      Start  6: pruefsumme_probe
 6/15 Test  #6: pruefsumme_probe .................   Passed    0.01 sec
      Start  7: schranken_probe
 7/15 Test  #7: schranken_probe ..................   Passed    0.01 sec
      Start  8: schreiber_probe
 8/15 Test  #8: schreiber_probe ..................   Passed    0.01 sec
      Start  9: schritt_probe
 9/15 Test  #9: schritt_probe ....................   Passed    0.02 sec
      Start 10: verlauf_probe
10/15 Test #10: verlauf_probe ....................   Passed    0.02 sec
      Start 11: werte_probe
11/15 Test #11: werte_probe ......................   Passed    0.02 sec
      Start 12: zufall_probe
12/15 Test #12: zufall_probe .....................   Passed    0.01 sec
      Start 13: zustand_probe
13/15 Test #13: zustand_probe ....................   Passed    0.01 sec
      Start 14: zustandsausgabe_probe
14/15 Test #14: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 15: wandschranke
15/15 Test #15: wandschranke .....................   Passed    0.43 sec

100% tests passed, 0 tests failed out of 15

Total Test time (real) =   0.68 sec
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
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[  4%] Building CXX object CMakeFiles/kern.dir/src/aktion.cpp.o
[  6%] Linking CXX static library libkern.a
[ 25%] Built target kern
[ 27%] Linking CXX static library libkern_geprueft.a
[ 45%] Built target kern_geprueft
[ 47%] Linking CXX executable meldung_probe
[ 50%] Linking CXX executable kennzeichen_probe
[ 52%] Linking CXX executable festkomma_probe
[ 54%] Linking CXX executable schritt_probe
[ 56%] Linking CXX executable pruefsumme_probe
[ 58%] Linking CXX executable schranken_probe
[ 60%] Building CXX object CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 62%] Linking CXX executable zustand_probe
[ 64%] Linking CXX executable werte_probe
[ 66%] Linking CXX executable schreiber_probe
[ 68%] Linking CXX executable zufall_probe
[ 70%] Linking CXX executable verlauf_probe
[ 72%] Linking CXX executable zustandsausgabe_probe
[ 75%] Built target pruefsumme_probe
[ 77%] Built target zustand_probe
[ 79%] Built target verlauf_probe
[ 81%] Built target schreiber_probe
[ 83%] Built target zustandsausgabe_probe
[ 85%] Built target festkomma_probe
[ 89%] Built target kennzeichen_probe
[ 89%] Built target zufall_probe
[ 91%] Built target meldung_probe
[ 93%] Built target schranken_probe
[ 95%] Built target werte_probe
[ 97%] Built target schritt_probe
[100%] Linking CXX executable aktion_probe
[100%] Built target aktion_probe
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
12/14 Test #12: zustand_probe ....................   Passed    0.01 sec
      Start 13: zustandsausgabe_probe
13/14 Test #13: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 14: wandschranke
14/14 Test #14: wandschranke .....................   Passed    0.42 sec

100% tests passed, 0 tests failed out of 14

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
[ 33%] Built target pruefstand
[ 50%] Built target pruefstand_geprueft
[ 75%] Built target vorrat_kernanker_probe
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
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 13 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 21 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 369 Schaltereintraege.
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/bau
```

## `cmake --build` -- ok (Code 0)

```
[  1%] Building CXX object kern/CMakeFiles/kern.dir/src/festkomma.cpp.o
[  3%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/festkomma.cpp.o
[  5%] Building CXX object kern/CMakeFiles/kern.dir/src/pruefsumme.cpp.o
[  6%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[  8%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 10%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[ 11%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 13%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 15%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/pruefsumme.cpp.o
[ 16%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 18%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 20%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zufall.cpp.o
[ 21%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 23%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 25%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 26%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 28%] Building CXX object kern/CMakeFiles/kern.dir/src/zufall.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 35%] Linking CXX static library libkern_geprueft.a
[ 35%] Built target kern_geprueft
[ 36%] Building CXX object daten/CMakeFiles/daten_geprueft.dir/src/jahrgang.cpp.o
[ 40%] Building CXX object kern/CMakeFiles/festkomma_probe.dir/test/festkomma_probe.cpp.o
[ 40%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 41%] Building CXX object kern/CMakeFiles/kennzeichen_probe.dir/test/kennzeichen_probe.cpp.o
[ 43%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 45%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 46%] Building CXX object kern/CMakeFiles/pruefsumme_probe.dir/test/pruefsumme_probe.cpp.o
[ 48%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 50%] Building CXX object kern/CMakeFiles/zufall_probe.dir/test/zufall_probe.cpp.o
[ 51%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 55%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 55%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 56%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 58%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 60%] Linking CXX executable pruefsumme_probe
[ 61%] Linking CXX executable meldung_probe
[ 63%] Linking CXX static library libkern.a
[ 63%] Built target meldung_probe
[ 63%] Built target kern
[ 63%] Built target pruefsumme_probe
[ 65%] Linking CXX static library libdaten_geprueft.a
[ 66%] Building CXX object daten/CMakeFiles/daten.dir/src/jahrgang.cpp.o
[ 66%] Built target daten_geprueft
[ 68%] Linking CXX executable zufall_probe
[ 70%] Building CXX object CMakeFiles/schnittstelle_geprueft.dir/src/partie.cpp.o
[ 71%] Building CXX object daten/CMakeFiles/jahrgang_probe.dir/test/jahrgang_probe.cpp.o
[ 71%] Built target zufall_probe
[ 73%] Linking CXX executable schreiber_probe
[ 73%] Built target schreiber_probe
[ 75%] Linking CXX executable schranken_probe
[ 76%] Linking CXX executable kennzeichen_probe
[ 76%] Built target schranken_probe
[ 76%] Built target kennzeichen_probe
[ 78%] Linking CXX static library libdaten.a
[ 78%] Built target daten
[ 80%] Building CXX object CMakeFiles/schnittstelle.dir/src/partie.cpp.o
[ 81%] Linking CXX executable zustand_probe
[ 83%] Linking CXX static library libschnittstelle_geprueft.a
[ 83%] Built target schnittstelle_geprueft
[ 85%] Building CXX object CMakeFiles/partie_probe.dir/test/partie_probe.cpp.o
[ 85%] Built target zustand_probe
[ 86%] Linking CXX executable verlauf_probe
[ 86%] Built target verlauf_probe
[ 88%] Linking CXX static library libschnittstelle.a
[ 90%] Linking CXX executable jahrgang_probe
[ 90%] Built target schnittstelle
[ 91%] Linking CXX executable festkomma_probe
[ 91%] Built target jahrgang_probe
[ 93%] Built target festkomma_probe
[ 93%] Linking CXX executable aktion_probe
[ 93%] Built target aktion_probe
[ 95%] Linking CXX executable schritt_probe
[ 95%] Built target schritt_probe
[ 96%] Linking CXX executable werte_probe
[ 96%] Built target werte_probe
[ 98%] Linking CXX executable partie_probe
[ 98%] Built target partie_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/bau
      Start  1: partie_probe
 1/16 Test  #1: partie_probe .....................   Passed    0.01 sec
      Start  2: aktion_probe
 2/16 Test  #2: aktion_probe .....................   Passed    0.01 sec
      Start  3: festkomma_probe
 3/16 Test  #3: festkomma_probe ..................   Passed    0.01 sec
      Start  4: kennzeichen_probe
 4/16 Test  #4: kennzeichen_probe ................   Passed    0.02 sec
      Start  5: meldung_probe
 5/16 Test  #5: meldung_probe ....................   Passed    0.01 sec
      Start  6: pruefsumme_probe
 6/16 Test  #6: pruefsumme_probe .................   Passed    0.01 sec
      Start  7: schranken_probe
 7/16 Test  #7: schranken_probe ..................   Passed    0.01 sec
      Start  8: schreiber_probe
 8/16 Test  #8: schreiber_probe ..................   Passed    0.01 sec
      Start  9: schritt_probe
 9/16 Test  #9: schritt_probe ....................   Passed    0.02 sec
      Start 10: verlauf_probe
10/16 Test #10: verlauf_probe ....................   Passed    0.02 sec
      Start 11: werte_probe
11/16 Test #11: werte_probe ......................   Passed    0.02 sec
      Start 12: zufall_probe
12/16 Test #12: zufall_probe .....................   Passed    0.01 sec
      Start 13: zustand_probe
13/16 Test #13: zustand_probe ....................   Passed    0.01 sec
      Start 14: zustandsausgabe_probe
14/16 Test #14: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 15: wandschranke
15/16 Test #15: wandschranke .....................   Passed    0.42 sec
      Start 16: jahrgang_probe
16/16 Test #16: jahrgang_probe ...................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 16

Total Test time (real) =   0.69 sec
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
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/bau
    Start 1: belegstellen_riegel
1/5 Test #1: belegstellen_riegel ..............   Passed    1.30 sec
    Start 2: belegstellen_messung
2/5 Test #2: belegstellen_messung .............   Passed   31.04 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........***Failed   17.38 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: 475f971
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
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.72 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........   Passed   10.10 sec

80% tests passed, 1 tests failed out of 5

Total Test time (real) =  65.55 sec

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
1/1 Test #1: bezeichner_riegel ................   Passed    0.48 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.48 sec
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
[100%] Built target kennzeichen_riegel
```

## `ctest --test-dir` -- ok (Code 0)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/bau
    Start 1: kennzeichen_riegel
1/1 Test #1: kennzeichen_riegel ...............   Passed    0.13 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.13 sec
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

1 Stelle(n). Wer eine davon fuer richtig haelt, aendert nicht diesen Riegel,
sondern den Regelsatz in T7 -- und dann faellt sie unter eine **benannte** Regel.
multiplikationsriegel, Selbsttest: 9 Faelle zur Lesung und 27 zu den Regeln,
alle wie erwartet.
multiplikationsriegel: 23 Dateien gelesen, 89 Namen in der Liste der Layout-
konstanten, 7 in der der u64-Konstanten. Binaere `*` nach der Lesung:
45 Vorkommen in 39 Zeilen.
  Regel 1  Layoutkonstante (Index, std::size_t)               34 Vorkommen in  29 Zeilen
  Regel 2  sizeof                                              0 Vorkommen in   0 Zeilen
  Regel 3  vorzeichenlos (Literal oder u64-Konstante)          6 Vorkommen in   5 Zeilen
  Regel 4  static_cast<i128> am Kopf einer Seite, kein ?       3 Vorkommen in   3 Zeilen
  Regel 5  Literale in der Bedingung eines static_assert       1 Vorkommen in   1 Zeilen
  BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)   1 Vorkommen in   1 Zeilen

T7 `:882-888` nennt 36 Zeilen, gemessen sind es 39. Die Abweichung ist eine
Meldung ueber T7 und keine ueber diesen Riegel; die Stellen stehen unten.


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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/3 Test #1: zahlwort_riegel ..................   Passed    0.06 sec
    Start 2: zahlwort_reihen
2/3 Test #2: zahlwort_reihen ..................   Passed    0.13 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................***Failed    2.39 sec

messen.py: A2: '**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen' kommt 0 mal vor, erwartet war genau einmal. Die Zeilennummer dieser Behauptung ist damit nicht zu erheben; die Erwartung waere geraten.
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
  Selbstprobe: 5 Faelle zu zeile_von, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD 475f9718cb954b7fca7a004345e8aa4609d86655
  Pruefling  kern/include/kern/werte.hpp  Blob e6edd48208427e45f138b662c52d754f27f7cb18
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 44b531748490223616949f28c6ee1650f12ddb5b
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp



67% tests passed, 1 tests failed out of 3

Total Test time (real) =   2.59 sec

The following tests FAILED:
	  3 - zahlwort_messung (Failed)
Errors while running CTest
```
