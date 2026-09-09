---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-09
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
[  6%] Built target pruefstand
[  6%] Built target zahlwort_riegel
[  8%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 11%] Built target mutationstreiber
[ 13%] Built target multiplikationsriegel
[ 18%] Built target pruefstand_geprueft
[ 19%] Building CXX object werkzeuge/kennzeichen/CMakeFiles/kennzeichen_riegel.dir/kennzeichen_riegel.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 22%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[ 25%] Built target bezeichner_riegel
[ 26%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 27%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 29%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 30%] Building CXX object kern/CMakeFiles/kern.dir/src/aktion.cpp.o
[ 31%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 33%] Building CXX object kern/CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern.dir/src/zustand.cpp.o
[ 36%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 38%] Building CXX object kern/CMakeFiles/kern.dir/src/verlauf.cpp.o
[ 38%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 41%] Building CXX object kern/CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 41%] Building CXX object kern/CMakeFiles/kern.dir/src/schritt.cpp.o
[ 47%] Built target vorrat_kernanker_probe
[ 47%] Built target vorrat_verfahren_probe
[ 50%] Built target vorrat_probe
[ 51%] Linking CXX static library libkern_geprueft.a
[ 55%] Built target kern_geprueft
[ 56%] Linking CXX executable festkomma_probe
[ 58%] Building CXX object kern/CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 61%] Linking CXX executable kennzeichen_probe
[ 61%] Building CXX object kern/CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 62%] Building CXX object kern/CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 63%] Linking CXX executable pruefsumme_probe
[ 65%] Building CXX object kern/CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 66%] Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 68%] Linking CXX executable zufall_probe
[ 69%] Building CXX object kern/CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 70%] Building CXX object kern/CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 72%] Building CXX object kern/CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 73%] Building CXX object kern/CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 75%] Built target zufall_probe
[ 76%] Built target kennzeichen_probe
[ 77%] Built target pruefsumme_probe
[ 79%] Built target festkomma_probe
[ 80%] Linking CXX executable meldung_probe
[ 81%] Linking CXX static library libkern.a
[ 86%] Built target kern
[ 86%] Built target meldung_probe
[ 87%] Linking CXX executable schreiber_probe
[ 87%] Built target schreiber_probe
[ 88%] Linking CXX executable zustand_probe
[ 90%] Linking CXX executable verlauf_probe
[ 91%] Linking CXX executable aktion_probe
[ 93%] Linking CXX executable schranken_probe
[ 93%] Built target verlauf_probe
[ 93%] Built target zustand_probe
[ 93%] Built target aktion_probe
[ 93%] Built target schranken_probe
[ 94%] Linking CXX executable schritt_probe
[ 94%] Built target schritt_probe
[ 95%] Linking CXX executable werte_probe
[ 97%] Linking CXX executable zustandsausgabe_probe
[ 97%] Built target zustandsausgabe_probe
[ 97%] Built target werte_probe
[ 98%] Linking CXX executable kennzeichen_riegel
[ 98%] Built target kennzeichen_riegel
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
serviert 1;

      Start 24: schlussriegel_nachbau
24/29 Test #24: schlussriegel_nachbau ............   Passed    0.51 sec
      Start 25: zahlwort_riegel
25/29 Test #25: zahlwort_riegel ..................***Failed    0.05 sec

1 Befunde:

  Funktionsdeklaration 'pfadstand' ab Zeilennummer 265 nennt keine Nummer der Tabelle -- sie faellt damit aus der Zaehlung

Entweder ist unter dem Satz etwas dazugekommen -- dann wird das Zahlwort nachgezogen --,
oder der Satz hat nie gestimmt. Beides wird berichtigt und nicht ausgenommen. Die
Zahl kommt aus dem Quelltext und nicht aus diesem Programm; eine Schwelle, an der
sich etwas drehen liesse, gibt es hier nicht.
zahlwort_riegel, Selbsttest: 9 Faelle zur Zerlegung, 20 zur Zahlbehauptung,
8 zum Urteil, 7 zu den Zaehlungen und 9 zur Verdrahtung, alle wie erwartet.
zahlwort_riegel, Empfindlichkeitsprobe: mit einer weiteren Deklaration unter einer
vorhandenen Nummer zaehlt der Riegel 25 statt 24 Deklarationen -- die Sorten 1 und 2
bleiben, wie sie waren. Sorte 3 stand davor auf
  Zeile 25: ohne Zahlbehauptung; Zeile 32: kardinal 24 gegen 24 -> gruen; Zeile 46: ohne Zahlbehauptung
und danach auf
  Zeile 25: ohne Zahlbehauptung; Zeile 32: kardinal 24 gegen 25 -> rot; Zeile 46: ohne Zahlbehauptung
Der rote Lauf im Wortlaut: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft --bruch=stelligkeit.
zahlwort_riegel: kern/include/kern/werte.hpp gelesen. 22 Nummern der Tabelle in 24 Funktionsdeklarationen;
10 Felder in struct Konstanten, davon 3 Groessen des Jahrgangs und 7 Parameterschluessel.
13 Fundstellen der drei Nomen, davon 8 mit Zahlbehauptung (4 zu den Groessen,
3 zu den Jahrgangskonstanten, 1 zu den Deklarationen).

  Groessen des Jahrgangs:  leitzins_start durchgriff pfadstand
  Parameterschluessel:     stufenweite ausstiegsabschlag aufschlag lobbykosten gegenlobby_satz regulierung_last zustimmung_elastizitaet

Jede Fundstelle mit ihrem Urteil -- der ausgeschriebene Nachlass dieses Riegels.
Genannt wird auch, was keine Zahl behauptet:

      2  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
      6  Groessen               keine Zahlbehauptung
     15  Jahrgangskonstante[n]  keine Zahlbehauptung
     16  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
     25  Deklarationen          keine Zahlbehauptung
     32  Groessen               Kardinalzahl: 'Zweiundzwanzig' nennt 22, gezaehlt 22
     32  Deklarationen          Kardinalzahl: 'vierundzwanzig' nennt 24, gezaehlt 24
     46  Deklarationen          keine Zahlbehauptung
     92  Jahrgangskonstante[n]  Kardinalzahl: 'drei' nennt 3, gezaehlt 3
    185  Jahrgangskonstante[n]  Ordnungszahl: 'zweite' nennt 2, gezaehlt 3
    204  Jahrgangskonstante[n]  Ordnungszahl: 'dritte' nennt 3, gezaehlt 3
    269  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
    586  Groessen               keine Zahlbehauptung

      Start 26: zahlwort_reihen
26/29 Test #26: zahlwort_reihen ..................   Passed    0.13 sec
      Start 27: zahlwort_messung
27/29 Test #27: zahlwort_messung .................***Failed    2.37 sec

messen.py: A2: '**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen' kommt 0 mal vor, erwartet war genau einmal. Die Zeilennummer dieser Behauptung ist damit nicht zu erheben; die Erwartung waere geraten.
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
  Selbstprobe: 5 Faelle zu zeile_von, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD e6924bf8cc970b1555f8b1863b656b32bec64610
  Pruefling  kern/include/kern/werte.hpp  Blob 9e24b723ec52191b7ca2a065414ebcbb9db9237a
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 709f016f1480fa63e7b8f5469c2c2ab7fd14aef1
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp


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
multiplikationsriegel: 23 Dateien gelesen, 85 Namen in der Liste der Layout-
konstanten, 7 in der der u64-Konstanten. Binaere `*` nach der Lesung:
42 Vorkommen in 36 Zeilen.
  Regel 1  Layoutkonstante (Index, std::size_t)               31 Vorkommen in  26 Zeilen
  Regel 2  sizeof                                              0 Vorkommen in   0 Zeilen
  Regel 3  vorzeichenlos (Literal oder u64-Konstante)          6 Vorkommen in   5 Zeilen
  Regel 4  static_cast<i128> auf beiden Seiten                 2 Vorkommen in   2 Zeilen
  Regel 5  Literale in der Bedingung eines static_assert       1 Vorkommen in   1 Zeilen
  BEFUND   keine Regel -- zwei i64 mit Groessenbedeutung (T5)   2 Vorkommen in   2 Zeilen


79% tests passed, 6 tests failed out of 29

Total Test time (real) =  70.32 sec

The following tests FAILED:
	  9 - verlauf_probe (Subprocess aborted)
	 20 - belegstellen_wortabstand (Failed)
	 23 - bezeichner_riegel (Failed)
	 25 - zahlwort_riegel (Failed)
	 27 - zahlwort_messung (Failed)
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
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schritt.cpp.o
[  4%] Building CXX object CMakeFiles/kern.dir/src/schritt.cpp.o
[  6%] Building CXX object CMakeFiles/kern.dir/src/verlauf.cpp.o
[  8%] Building CXX object CMakeFiles/kern.dir/src/schreiber.cpp.o
[ 10%] Building CXX object CMakeFiles/kern_geprueft.dir/src/schreiber.cpp.o
[ 12%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[ 14%] Building CXX object CMakeFiles/kern_geprueft.dir/src/aktion.cpp.o
[ 16%] Building CXX object CMakeFiles/kern.dir/src/aktion.cpp.o
[ 18%] Building CXX object CMakeFiles/kern_geprueft.dir/src/verlauf.cpp.o
[ 20%] Building CXX object CMakeFiles/kern.dir/src/zustandsausgabe.cpp.o
[ 22%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 25%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustand.cpp.o
[ 27%] Building CXX object CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
[ 29%] Building CXX object CMakeFiles/kern.dir/src/zustand.cpp.o
[ 31%] Linking CXX static library libkern_geprueft.a
[ 37%] Built target kern_geprueft
[ 41%] Linking CXX executable kennzeichen_probe
[ 41%] Linking CXX executable festkomma_probe
[ 43%] Building CXX object CMakeFiles/aktion_probe.dir/test/aktion_probe.cpp.o
[ 45%] Building CXX object CMakeFiles/schreiber_probe.dir/test/schreiber_probe.cpp.o
[ 47%] Linking CXX executable pruefsumme_probe
[ 50%] Linking CXX executable zufall_probe
[ 52%] Building CXX object CMakeFiles/zustand_probe.dir/test/zustand_probe.cpp.o
[ 54%] Building CXX object CMakeFiles/schranken_probe.dir/test/schranken_probe.cpp.o
[ 56%] Building CXX object CMakeFiles/werte_probe.dir/test/werte_probe.cpp.o
[ 58%] Building CXX object CMakeFiles/meldung_probe.dir/test/meldung_probe.cpp.o
[ 60%] Building CXX object CMakeFiles/verlauf_probe.dir/test/verlauf_probe.cpp.o
[ 62%] Building CXX object CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o
[ 64%] Building CXX object CMakeFiles/zustandsausgabe_probe.dir/test/zustandsausgabe_probe.cpp.o
[ 66%] Built target zufall_probe
[ 68%] Built target kennzeichen_probe
[ 70%] Built target festkomma_probe
[ 72%] Built target pruefsumme_probe
[ 75%] Linking CXX executable meldung_probe
[ 77%] Linking CXX static library libkern.a
[ 83%] Built target kern
[ 83%] Built target meldung_probe
[ 85%] Linking CXX executable zustand_probe
[ 87%] Linking CXX executable schreiber_probe
[ 89%] Linking CXX executable schranken_probe
[ 89%] Built target zustand_probe
[ 89%] Built target schreiber_probe
[ 89%] Built target schranken_probe
[ 91%] Linking CXX executable aktion_probe
[ 91%] Built target aktion_probe
[ 93%] Linking CXX executable verlauf_probe
[ 93%] Built target verlauf_probe
[ 95%] Linking CXX executable schritt_probe
[ 95%] Built target schritt_probe
[ 97%] Linking CXX executable werte_probe
[100%] Linking CXX executable zustandsausgabe_probe
[100%] Built target werte_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

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
 8/14 Test  #8: schritt_probe ....................   Passed    0.01 sec
      Start  9: verlauf_probe
 9/14 Test  #9: verlauf_probe ....................Subprocess aborted***Exception:   0.01 sec
terminate called after throwing an instance of 'std::domain_error'
  what():  plus: Summe ausserhalb von i64 (T7)

      Start 10: werte_probe
10/14 Test #10: werte_probe ......................   Passed    0.02 sec
      Start 11: zufall_probe
11/14 Test #11: zufall_probe .....................   Passed    0.01 sec
      Start 12: zustand_probe
12/14 Test #12: zustand_probe ....................   Passed    0.01 sec
      Start 13: zustandsausgabe_probe
13/14 Test #13: zustandsausgabe_probe ............   Passed    0.08 sec
      Start 14: wandschranke
14/14 Test #14: wandschranke .....................   Passed    0.43 sec

93% tests passed, 1 tests failed out of 14

Total Test time (real) =   0.66 sec

The following tests FAILED:
	  9 - verlauf_probe (Subprocess aborted)
Errors while running CTest
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
[ 75%] Built target vorrat_probe
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

Total Test time (real) =   0.03 sec
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
1/5 Test #1: belegstellen_riegel ..............   Passed    1.22 sec
    Start 2: belegstellen_messung
2/5 Test #2: belegstellen_messung .............   Passed   31.17 sec
    Start 3: belegstellen_wortabstand
3/5 Test #3: belegstellen_wortabstand .........***Failed   17.45 sec
Messstand 0166 -- die sechs Fassungen des Wortabstands
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Arbeitsbaum: e6924bf
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
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.76 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........   Passed   10.13 sec

80% tests passed, 1 tests failed out of 5

Total Test time (real) =  65.75 sec

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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Uebergangen -- der ausgeschriebene Nachlass dieses Riegels. Jede Fundstelle mit
der Regel, die sie durchgelassen hat. Gezaehlt und genannt, aber nicht bewertet:

  festkomma_probe          dateiname            kern/src/werte.cpp (Zeile 106)
  beteiligungsrabatt       parameterschluessel  kern/src/werte.cpp (Zeile 136)
  werte_probe              dateiname            kern/src/werte.cpp (Zeile 778)
  verschiebung             fremdwort            kern/src/werte.cpp (Zeile 1066)
  abort                    abgelegter_name      kern/src/festkomma.cpp (Zeile 24)
  fnv1a_64_test_vector     quellenangabe        kern/src/pruefsumme.cpp (Zeile 31)
  fnv1a_64_test_vector     quellenangabe        kern/src/pruefsumme.cpp (Zeile 84)
  zustandsausgabe_probe    dateiname            kern/src/zustandsausgabe.cpp (Zeile 57)
  map                      fremder_behaelter    kern/include/kern/kern.hpp (Zeile 44)
  set                      fremder_behaelter    kern/include/kern/kern.hpp (Zeile 44)
  unsafe                   abgelegter_name      kern/include/kern/kern.hpp (Zeile 58)
  abort                    abgelegter_name      kern/include/kern/festkomma.hpp (Zeile 51)
  abort                    fremdwort            kern/include/kern/festkomma.hpp (Zeile 55)
  bit_width                fremder_behaelter    kern/include/kern/festkomma.hpp (Zeile 71)
  festkomma_probe          dateiname            kern/include/kern/festkomma.hpp (Zeile 191)
  __builtin_mul_overflow   reserviert           kern/include/kern/festkomma.hpp (Zeile 229)
  werte_probe              dateiname            kern/include/kern/festkomma.hpp (Zeile 261)
  festkomma_probe          dateiname            kern/include/kern/festkomma.hpp (Zeile 265)
  werte_probe              dateiname            kern/include/kern/festkomma.hpp (Zeile 266)
  zustandsausgabe_probe    dateiname            kern/include/kern/zustandsausgabe.hpp (Zeile 16)
  zustandsausgabe_probe    dateiname            kern/include/kern/zustandsausgabe.hpp (Zeile 707)
  zustandsausgabe_probe    dateiname            kern/include/kern/zustandsausgabe.hpp (Zeile 743)
  pruefstand               bauziel              kern/include/kern/werte.hpp (Zeile 77)
  zwangsabschlag           parameterschluessel  kern/include/kern/werte.hpp (Zeile 437)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 581)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 582)
  grep                     quellenangabe        kern/include/kern/pruefsumme.hpp (Zeile 48)
  to_string                fremder_behaelter    kern/include/kern/sperre.hpp (Zeile 18)
  zustandsausgabe_probe    dateiname            kern/include/kern/verlauf.hpp (Zeile 114)
  Rest                     namensteil           kern/include/kern/zustand.hpp (Zeile 211)
  schreibe                 abgelegter_name      kern/include/kern/zustand.hpp (Zeile 485)
  kern_geprueft            bauziel              kern/test/festkomma_probe.cpp (Zeile 12)
  MAL_                     namensvorsilbe       kern/test/festkomma_probe.cpp (Zeile 77)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 138)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 161)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 178)
  werte_probe              dateiname            kern/test/kennzeichen.hpp (Zeile 131)
  kern_geprueft            bauziel             
1 Bezeichner in Kommentaren des Kerns loesen nicht auf:

  kern/include/kern/werte.hpp (Zeile 218)
      genannt: daten_pruefsumme
      gesucht: daten_pruefsumme

Entweder ist der Name umbenannt worden -- dann wird der Kommentar nachgezogen --,
oder er hiess nie so. Beides wird berichtigt und nicht ausgenommen. Ist der Name
zu Recht keiner des Kerns, gehoert er unter eine der benannten Regeln, und die
Regel wird begruendet, wo sie steht -- nicht der einzelne Name geduldet.
 kern/test/pruefsumme_probe.cpp (Zeile 7)
  kern_geprueft            bauziel              kern/test/zustand_probe.cpp (Zeile 7)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 50)
  kern_geprueft            bauziel              kern/test/schritt_probe.cpp (Zeile 61)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 484)
  ElfFelder                fremdwort            kern/test/schritt_probe.cpp (Zeile 2074)
  kern_geprueft            bauziel              kern/test/schreiber_probe.cpp (Zeile 10)
  kern_geprueft            bauziel              kern/test/zufall_probe.cpp (Zeile 7)
  kern_geprueft            bauziel              kern/test/zustandsausgabe_probe.cpp (Zeile 18)
  M15                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 412)
  M16                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 412)
  M18                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 412)
  M17                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 412)
  N10                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 412)
  N11                      kennung              kern/test/zustandsausgabe_probe.cpp (Zeile 1252)
  schrittweite             parameterschluessel  kern/test/schranken_probe.cpp (Zeile 427)
  instrument_min           parameterschluessel  kern/test/schranken_probe.cpp (Zeile 427)
  instrument_max           parameterschluessel  kern/test/schranken_probe.cpp (Zeile 427)
  kern_geprueft            bauziel              kern/test/meldung_probe.cpp (Zeile 33)

  je Regel: abgelegter_name 4; bauziel 9; dateiname 17; fremder_behaelter 4; fremdwort 5; kennung 6; namensteil 1; namensvorsilbe 1; parameterschluessel 5; quellenangabe 3; reserviert 1;


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.46 sec

The following tests FAILED:
	  1 - bezeichner_riegel (Failed)
Errors while running CTest
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
multiplikationsriegel: 23 Dateien gelesen, 85 Namen in der Liste der Layout-
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

## `ctest --test-dir` -- FEHLER (Code 8)

```
Test project /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/bau
    Start 1: zahlwort_riegel
1/3 Test #1: zahlwort_riegel ..................***Failed    0.05 sec

1 Befunde:

  Funktionsdeklaration 'pfadstand' ab Zeilennummer 265 nennt keine Nummer der Tabelle -- sie faellt damit aus der Zaehlung

Entweder ist unter dem Satz etwas dazugekommen -- dann wird das Zahlwort nachgezogen --,
oder der Satz hat nie gestimmt. Beides wird berichtigt und nicht ausgenommen. Die
Zahl kommt aus dem Quelltext und nicht aus diesem Programm; eine Schwelle, an der
sich etwas drehen liesse, gibt es hier nicht.
zahlwort_riegel, Selbsttest: 9 Faelle zur Zerlegung, 20 zur Zahlbehauptung,
8 zum Urteil, 7 zu den Zaehlungen und 9 zur Verdrahtung, alle wie erwartet.
zahlwort_riegel, Empfindlichkeitsprobe: mit einer weiteren Deklaration unter einer
vorhandenen Nummer zaehlt der Riegel 25 statt 24 Deklarationen -- die Sorten 1 und 2
bleiben, wie sie waren. Sorte 3 stand davor auf
  Zeile 25: ohne Zahlbehauptung; Zeile 32: kardinal 24 gegen 24 -> gruen; Zeile 46: ohne Zahlbehauptung
und danach auf
  Zeile 25: ohne Zahlbehauptung; Zeile 32: kardinal 24 gegen 25 -> rot; Zeile 46: ohne Zahlbehauptung
Der rote Lauf im Wortlaut: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft --bruch=stelligkeit.
zahlwort_riegel: kern/include/kern/werte.hpp gelesen. 22 Nummern der Tabelle in 24 Funktionsdeklarationen;
10 Felder in struct Konstanten, davon 3 Groessen des Jahrgangs und 7 Parameterschluessel.
13 Fundstellen der drei Nomen, davon 8 mit Zahlbehauptung (4 zu den Groessen,
3 zu den Jahrgangskonstanten, 1 zu den Deklarationen).

  Groessen des Jahrgangs:  leitzins_start durchgriff pfadstand
  Parameterschluessel:     stufenweite ausstiegsabschlag aufschlag lobbykosten gegenlobby_satz regulierung_last zustimmung_elastizitaet

Jede Fundstelle mit ihrem Urteil -- der ausgeschriebene Nachlass dieses Riegels.
Genannt wird auch, was keine Zahl behauptet:

      2  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
      6  Groessen               keine Zahlbehauptung
     15  Jahrgangskonstante[n]  keine Zahlbehauptung
     16  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
     25  Deklarationen          keine Zahlbehauptung
     32  Groessen               Kardinalzahl: 'Zweiundzwanzig' nennt 22, gezaehlt 22
     32  Deklarationen          Kardinalzahl: 'vierundzwanzig' nennt 24, gezaehlt 24
     46  Deklarationen          keine Zahlbehauptung
     92  Jahrgangskonstante[n]  Kardinalzahl: 'drei' nennt 3, gezaehlt 3
    185  Jahrgangskonstante[n]  Ordnungszahl: 'zweite' nennt 2, gezaehlt 3
    204  Jahrgangskonstante[n]  Ordnungszahl: 'dritte' nennt 3, gezaehlt 3
    269  Groessen               Kardinalzahl: 'zweiundzwanzig' nennt 22, gezaehlt 22
    586  Groessen               keine Zahlbehauptung

    Start 2: zahlwort_reihen
2/3 Test #2: zahlwort_reihen ..................   Passed    0.13 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................***Failed    2.37 sec

messen.py: A2: '**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen' kommt 0 mal vor, erwartet war genau einmal. Die Zeilennummer dieser Behauptung ist damit nicht zu erheben; die Erwartung waere geraten.
  Selbstprobe: 3 Faelle zu einmal_ersetzen, alle wie erwartet.
  Selbstprobe: 5 Faelle zu zeile_von, alle wie erwartet.
==============================================================================
Messung 0180, Stand HEAD e6924bf8cc970b1555f8b1863b656b32bec64610
  Pruefling  kern/include/kern/werte.hpp  Blob 9e24b723ec52191b7ca2a065414ebcbb9db9237a
  Riegel     werkzeuge/zahlwort/zahlwort_riegel.cpp  Blob 709f016f1480fa63e7b8f5469c2c2ab7fd14aef1
  Uebersetzer  /usr/bin/c++ -- c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
  Arbeitsplatz /tmp/messung-0180
==============================================================================

## Teil A: der Riegel gegen vier Staende von werte.hpp



33% tests passed, 2 tests failed out of 3

Total Test time (real) =   2.55 sec

The following tests FAILED:
	  1 - zahlwort_riegel (Failed)
	  3 - zahlwort_messung (Failed)
Errors while running CTest
```
