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
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Mitglied 'daten' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'schnittstelle' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'konsole' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'oberflaeche' ist noch nicht gebaut -- uebersprungen.
-- Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 24 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 426 Schaltereintraege.
-- Configuring done (0.4s)
-- Generating done (0.1s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/bau
```

## `cmake --build` -- ok (Code 0)

```
[  8%] Built target pruefstand_geprueft
[  8%] Built target pruefstand
[ 10%] Building CXX object werkzeuge/kennzeichen/CMakeFiles/kennzeichen_riegel.dir/kennzeichen_riegel.cpp.o
[ 13%] Built target bezeichner_riegel
[ 14%] Building CXX object kern/CMakeFiles/kern.dir/src/werte.cpp.o
[ 16%] Building CXX object werkzeuge/belegstellen/CMakeFiles/belegstellen_riegel.dir/belegstellen_riegel.cpp.o
[ 19%] Built target mutationstreiber
[ 22%] Built target zahlwort_riegel
[ 23%] Building CXX object kern/CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[ 26%] Built target vorrat_kernanker_probe
[ 29%] Built target vorrat_verfahren_probe
[ 32%] Built target vorrat_probe
[ 33%] Linking CXX static library libkern.a
[ 47%] Built target kern
[ 48%] Linking CXX static library libkern_geprueft.a
[ 61%] Built target kern_geprueft
[ 63%] Linking CXX executable aktion_probe
[ 64%] Linking CXX executable festkomma_probe
[ 66%] Linking CXX executable schreiber_probe
[ 67%] Linking CXX executable meldung_probe
[ 69%] Linking CXX executable schritt_probe
[ 70%] Linking CXX executable schranken_probe
[ 72%] Linking CXX executable verlauf_probe
[ 73%] Linking CXX executable werte_probe
[ 75%] Linking CXX executable zustand_probe
[ 76%] Linking CXX executable pruefsumme_probe
[ 77%] Linking CXX executable zufall_probe
[ 79%] Linking CXX executable zustandsausgabe_probe
[ 80%] Built target werte_probe
[ 82%] Built target aktion_probe
[ 83%] Built target zustand_probe
[ 85%] Built target meldung_probe
[ 86%] Built target zufall_probe
[ 88%] Built target festkomma_probe
[ 89%] Built target pruefsumme_probe
[ 91%] Built target schritt_probe
[ 92%] Built target schranken_probe
[ 94%] Built target schreiber_probe
[ 95%] Built target verlauf_probe
[ 97%] Built target zustandsausgabe_probe
[ 98%] Linking CXX executable kennzeichen_riegel
[ 98%] Built target kennzeichen_riegel
[100%] Linking CXX executable belegstellen_riegel
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
nangabe        kern/src/pruefsumme.cpp (Zeile 31)
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
  pruefstand               bauziel              kern/include/kern/werte.hpp (Zeile 66)
  zwangsabschlag           parameterschluessel  kern/include/kern/werte.hpp (Zeile 353)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 497)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 498)
  grep                     quellenangabe        kern/include/kern/pruefsumme.hpp (Zeile 48)
  to_string                fremder_behaelter    kern/include/kern/sperre.hpp (Zeile 18)
  zustandsausgabe_probe    dateiname            kern/include/kern/verlauf.hpp (Zeile 114)
  Rest                     namensteil           kern/include/kern/zustand.hpp (Zeile 191)
  schreibe                 abgelegter_name      kern/include/kern/zustand.hpp (Zeile 465)
  kern_geprueft            bauziel              kern/test/festkomma_probe.cpp (Zeile 12)
  MAL_                     namensvorsilbe       kern/test/festkomma_probe.cpp (Zeile 77)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 138)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 161)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 178)
  werte_probe              dateiname            kern/test/kennzeichen.hpp (Zeile 98)
  kern_geprueft            bauziel              
1 Bezeichner in Kommentaren des Kerns loesen nicht auf:

  kern/test/festkomma_probe.cpp (Zeile 136)
      genannt: ABBRUCH_MELDET
      gesucht: ABBRUCH_MELDET

Entweder ist der Name umbenannt worden -- dann wird der Kommentar nachgezogen --,
oder er hiess nie so. Beides wird berichtigt und nicht ausgenommen. Ist der Name
zu Recht keiner des Kerns, gehoert er unter eine der benannten Regeln, und die
Regel wird begruendet, wo sie steht -- nicht der einzelne Name geduldet.
kern/test/pruefsumme_probe.cpp (Zeile 7)
  kern_geprueft            bauziel              kern/test/zustand_probe.cpp (Zeile 7)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 50)
  kern_geprueft            bauziel              kern/test/schritt_probe.cpp (Zeile 61)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 327)
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

  je Regel: abgelegter_name 4; bauziel 9; dateiname 17; fremder_behaelter 4; fremdwort 4; kennung 6; namensteil 1; namensvorsilbe 1; parameterschluessel 5; quellenangabe 3; reserviert 1;

      Start 23: schlussriegel_nachbau
23/27 Test #23: schlussriegel_nachbau ............   Passed    0.50 sec
      Start 24: zahlwort_riegel
24/27 Test #24: zahlwort_riegel ..................   Passed    0.05 sec
      Start 25: zahlwort_reihen
25/27 Test #25: zahlwort_reihen ..................   Passed    0.13 sec
      Start 26: zahlwort_messung
26/27 Test #26: zahlwort_messung .................   Passed   18.48 sec
      Start 27: kennzeichen_riegel
27/27 Test #27: kennzeichen_riegel ...............   Passed    0.14 sec

81% tests passed, 5 tests failed out of 27

Total Test time (real) =  91.77 sec

The following tests FAILED:
	 17 - belegstellen_riegel (Failed)
	 18 - belegstellen_messung (Failed)
	 19 - belegstellen_wortabstand (Failed)
	 21 - belegstellen_kopfzahlen (Failed)
	 22 - bezeichner_riegel (Failed)
Errors while running CTest
```

## `cmake -S` -- ok (Code 0)

```
-- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet "kern/sperre.hpp" als letzten #include. Dazu 1 Kopf/Koepfe unter test/, die ihn nicht binden koennen, gegen die 20 dort vergifteten Bezeichner gehalten: 20 Paar(e) geprueft.
-- Nullabhaengigkeitsriegel (T2): 2 Ziel(e) gelesen -- kern.LINK_LIBRARIES=[]; kern.INTERFACE_LINK_LIBRARIES=[]; kern.LINK_OPTIONS=[]; kern.INTERFACE_LINK_OPTIONS=[]; kern_geprueft.LINK_LIBRARIES=[]; kern_geprueft.INTERFACE_LINK_LIBRARIES=[]; kern_geprueft.LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]; kern_geprueft.INTERFACE_LINK_OPTIONS=[-fsanitize=undefined,address;-fno-sanitize-recover=all]
-- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 14 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten: 242 Schaltereintraege.
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/bau
```

## `cmake --build` -- ok (Code 0)

```
[  4%] Building CXX object CMakeFiles/kern_geprueft.dir/src/werte.cpp.o
[  4%] Building CXX object CMakeFiles/kern.dir/src/werte.cpp.o
[  6%] Linking CXX static library libkern.a
[ 26%] Built target kern
[ 28%] Linking CXX static library libkern_geprueft.a
[ 47%] Built target kern_geprueft
[ 50%] Linking CXX executable schranken_probe
[ 52%] Linking CXX executable schreiber_probe
[ 54%] Linking CXX executable aktion_probe
[ 56%] Linking CXX executable festkomma_probe
[ 58%] Linking CXX executable pruefsumme_probe
[ 60%] Linking CXX executable werte_probe
[ 63%] Linking CXX executable meldung_probe
[ 65%] Linking CXX executable verlauf_probe
[ 67%] Linking CXX executable zufall_probe
[ 69%] Linking CXX executable zustandsausgabe_probe
[ 71%] Linking CXX executable zustand_probe
[ 73%] Linking CXX executable schritt_probe
[ 76%] Built target aktion_probe
[ 78%] Built target festkomma_probe
[ 80%] Built target schranken_probe
[ 82%] Built target meldung_probe
[ 84%] Built target schreiber_probe
[ 86%] Built target zufall_probe
[ 89%] Built target pruefsumme_probe
[ 93%] Built target zustand_probe
[ 93%] Built target verlauf_probe
[ 95%] Built target werte_probe
[ 97%] Built target zustandsausgabe_probe
[100%] Built target schritt_probe
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

Total Test time (real) =   0.65 sec
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
-abstand  Rueckgabe 1, Zahlen (41, 40, 53)  -- keine der beiden Lockerungen
    nur-abstand   Rueckgabe 1, Zahlen (41, 40, 55)  -- nur der Wortabstand, die Suche nach rechts abgeschaltet
    nur-rechts    Rueckgabe 1, Zahlen (41, 40, 53)  -- nur die Suche nach rechts, der Wortabstand abgeschaltet
    beide         wortgleich mit riegel-nachher aus Teil 1 -- dieselbe Messung, nicht noch einmal uebersetzt.
    beide         Rueckgabe 1, Zahlen (42, 41, 54)  -- die unveraenderte Fassung -- der Nullpunkt
    abstand4      Rueckgabe 1, Zahlen (41, 40, 54)  -- Schwelle vier, sonst wie 'nur der Wortabstand'
    abstand5      wortgleich mit nur-abstand -- dieselbe Messung, nicht noch einmal uebersetzt.
    abstand5      Rueckgabe 1, Zahlen (41, 40, 55)  -- Schwelle fuenf, sonst wie 'nur der Wortabstand'

Grundzahl (unveraenderte Fassung): (42, 41, 54)
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
4/5 Test #4: belegstellen_sammelordnung .......   Passed    5.73 sec
    Start 5: belegstellen_kopfzahlen
5/5 Test #5: belegstellen_kopfzahlen ..........***Failed   16.04 sec
Vorfassung: gefehlt und ist geholt worden -- Blob ee8d0283558d485f3b3482f025ad18769bf414a5 aus dbcd637:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++
Bezugsstand im Kommentar: 2f2f79f; HEAD zu Beginn: ceee29d
A  vorher : Code 1, 42 Zitate, 41 aufgeloest, 54 uebergangen
A  nachher: Code 1, 42 Zitate, 41 aufgeloest, 54 uebergangen
A  Der Riegel ist rot -- vorher wie nachher (Code 1). Die Befunde stehen unten und gehoeren nicht zu 0115:
     zitierend: kern/test/festkomma_probe.cpp:259
B1 ohne-marken-rein: Code 1, 53 Zitate, 41 aufgeloest, 68 uebergangen; 12 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 11 Stellen zu Unrecht, gemessen sind 12.
  FEHLSCHLAG: Der Kopfkommentar nennt 52 Zitate unter der Mutation, gemessen sind 53.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 42.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 68.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 54.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 1, 42 Zitate, 41 aufgeloest, 54 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (42, 41, 54).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (42, 41, 54) statt (41, 41, 53).
  FEHLSCHLAG: Angabe 2 nennt die Summe 94; Zitate plus uebergangene Fundstellen sind 96.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte

B1 ohne-marken-rein: Code 1, 53 Zitate, 41 aufgeloest, 68 uebergangen; 12 Stellen zu Unrecht, davon 10 im eigenen Quelltext {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
  FEHLSCHLAG: Der Kopfkommentar nennt 11 Stellen zu Unrecht, gemessen sind 12.
  FEHLSCHLAG: Der Kopfkommentar nennt 41 Zitate ohne die Mutation, gemessen sind 42.
  FEHLSCHLAG: Der Kopfkommentar nennt 66 uebergangene Fundstellen unter der Mutation, gemessen sind 68.
  FEHLSCHLAG: Der Kopfkommentar nennt 53 uebergangene Fundstellen ohne sie, gemessen sind 54.
B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 1, 42 Zitate, 41 aufgeloest, 54 uebergangen
  FEHLSCHLAG: Angabe 2 nennt (41, 41, 53) als die Zahlen des unveraenderten Riegels, gemessen sind (42, 41, 54).
  FEHLSCHLAG: Angabe 2 sagt, der Mutant nenne dieselben Zahlen; er nennt (42, 41, 54) statt (41, 41, 53).
  FEHLSCHLAG: Angabe 2 nennt die Summe 95; Zitate plus uebergangene Fundstellen sind 96.
B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
     Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt erste
  FEHLSCHLAG: Der Kopf nennt den erste Fall, historisch ausgewiesen ist der 7.
G  Gegenprobe an der verstellten Angabe -- Angabe 1: 4 Meldung(en), Angabe 2: 3 Meldung(en), Angabe 3: 1 Meldung(en)
HEAD am Ende: ceee29d
Hinweis: HEAD steht auf ceee29d, gemessen und niedergeschrieben ist der Stand 2f2f79f. Die Zahlen sind damit aelter als der Baum.

8 Erwartung(en) nicht erfuellt.


20% tests passed, 4 tests failed out of 5

Total Test time (real) =  71.36 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
	  2 - belegstellen_messung (Failed)
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

## `ctest --test-dir` -- FEHLER (Code 8)

```
 aus 10 Bauskripten, 650 Datei- und Ordnernamen, 22 vergiftete Namen,
90 eigene Behaelter.

Uebergangen -- der ausgeschriebene Nachlass dieses Riegels. Jede Fundstelle mit
der Regel, die sie durchgelassen hat. Gezaehlt und genannt, aber nicht bewertet:

  festkomma_probe          dateiname            kern/src/werte.cpp (Zeile 106)
  beteiligungsrabatt       parameterschluessel  kern/src/werte.cpp (Zeile 136)
  werte_probe              dateiname            kern/src/werte.cpp (Zeile 744)
  verschiebung             fremdwort            kern/src/werte.cpp (Zeile 1032)
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
  pruefstand               bauziel              kern/include/kern/werte.hpp (Zeile 66)
  zwangsabschlag           parameterschluessel  kern/include/kern/werte.hpp (Zeile 353)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 497)
  verschiebung             fremdwort            kern/include/kern/werte.hpp (Zeile 498)
  grep                     quellenangabe        kern/include/kern/pruefsumme.hpp (Zeile 48)
  to_string                fremder_behaelter    kern/include/kern/sperre.hpp (Zeile 18)
  zustandsausgabe_probe    dateiname            kern/include/kern/verlauf.hpp (Zeile 114)
  Rest                     namensteil           kern/include/kern/zustand.hpp (Zeile 191)
  schreibe                 abgelegter_name      kern/include/kern/zustand.hpp (Zeile 465)
  kern_geprueft            bauziel              kern/test/festkomma_probe.cpp (Zeile 12)
  MAL_                     namensvorsilbe       kern/test/festkomma_probe.cpp (Zeile 77)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 138)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 161)
  werte_probe              dateiname            kern/test/festkomma_probe.cpp (Zeile 178)
  werte_probe              dateiname            kern/test/kennzeichen.hpp (Zeile 98)
  kern_geprueft            bauziel              
1 Bezeichner in Kommentaren des Kerns loesen nicht auf:

  kern/test/festkomma_probe.cpp (Zeile 136)
      genannt: ABBRUCH_MELDET
      gesucht: ABBRUCH_MELDET

Entweder ist der Name umbenannt worden -- dann wird der Kommentar nachgezogen --,
oder er hiess nie so. Beides wird berichtigt und nicht ausgenommen. Ist der Name
zu Recht keiner des Kerns, gehoert er unter eine der benannten Regeln, und die
Regel wird begruendet, wo sie steht -- nicht der einzelne Name geduldet.
kern/test/pruefsumme_probe.cpp (Zeile 7)
  kern_geprueft            bauziel              kern/test/zustand_probe.cpp (Zeile 7)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 50)
  kern_geprueft            bauziel              kern/test/schritt_probe.cpp (Zeile 61)
  werte_probe              dateiname            kern/test/schritt_probe.cpp (Zeile 327)
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

  je Regel: abgelegter_name 4; bauziel 9; dateiname 17; fremder_behaelter 4; fremdwort 4; kennung 6; namensteil 1; namensvorsilbe 1; parameterschluessel 5; quellenangabe 3; reserviert 1;


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.43 sec

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
1/1 Test #1: kennzeichen_riegel ...............   Passed    0.14 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.14 sec
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
3/3 Test #3: zahlwort_messung .................   Passed   18.52 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.70 sec
```
