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
[  4%] Built target pruefstand
[ 10%] Built target mutationstreiber
[ 10%] Built target belegstellen_riegel
[ 15%] Built target pruefstand_geprueft
[ 27%] Built target zahlwort_riegel
[ 34%] Built target kern_geprueft
[ 51%] Built target kern
[ 54%] Built target bezeichner_riegel
[ 60%] Built target vorrat_kernanker_probe
[ 60%] Built target vorrat_verfahren_probe
[ 63%] Built target vorrat_probe
[ 66%] Built target aktion_probe
[ 72%] Built target pruefsumme_probe
[ 72%] Built target festkomma_probe
[ 78%] Built target schreiber_probe
[ 78%] Built target meldung_probe
[ 81%] Built target schranken_probe
[ 84%] Built target schritt_probe
[ 87%] Built target verlauf_probe
[ 90%] Built target werte_probe
[ 93%] Built target zustand_probe
[ 96%] Built target zufall_probe
[100%] Built target zustandsausgabe_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
aten/reihen.toml:406  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:406  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:456  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:457  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:501  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:508  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:555  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:556  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als Sollreihe der Klasse gesetzt
  daten/reihen.toml:586  (Gliederungsziffer stat
2 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/reihen.toml:406
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Leitzins ist seit dem 2026-09-03 keine Sollreihe

  zitierend: daten/reihen.toml:556
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Leitzins ist seit dem 2026-09-03 keine Sollreihe

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
t Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:587  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:691  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:810  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:810  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:819  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:819  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:1126  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1324  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1601  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1601  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1757  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1813  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:1946  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 -- fd777fb und 89dc83c vom 2026-08-31
  daten/reihen.toml:1946  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 vom 2026-09-05 steht dort nicht
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  parameter.toml:20  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:80  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  parameter.toml:898  (kein Dokumentname im Absatz)
      gesucht war: WIE DER PRUEFER ZAEHLT
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig
  werkzeuge/belegstellen/belegstellen_riegel.cpp:280  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:283  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet

      Start 18: belegstellen_messung
18/23 Test #18: belegstellen_messung .............***Failed    0.04 sec
Messstand 0147 -- Anker an der Ortsfrage und an der Formreihenfolge
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++

Teil 0 -- der Messstand selbst
OK  Selbstprobe: alle neun Marken werden namentlich gelesen.
OK  Selbstprobe: die Schlusszeile wird gelesen.
OK  Selbstprobe: eine gruene Ausgabe gibt nichts her.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'fehlt'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'zweimal'.
ROT Selbstprobe: `einmal_ersetzen` geht im Fall 'genau einmal' aus als yxb, erwartet war ayb.

Messstand 0147: NICHT GEMESSEN -- der Auswerter misst nicht. Alles Weitere waere wertlos.
Rueckgabe 2. Dieser Lauf sagt ueber den Riegel nichts, weder gut noch schlecht.

      Start 19: bezeichner_riegel
19/23 Test #19: bezeichner_riegel ................   Passed    0.36 sec
      Start 20: schlussriegel_nachbau
20/23 Test #20: schlussriegel_nachbau ............   Passed    0.49 sec
      Start 21: zahlwort_riegel
21/23 Test #21: zahlwort_riegel ..................   Passed    0.04 sec
      Start 22: zahlwort_reihen
22/23 Test #22: zahlwort_reihen ..................   Passed    0.12 sec
      Start 23: zahlwort_messung
23/23 Test #23: zahlwort_messung .................   Passed   18.27 sec

91% tests passed, 2 tests failed out of 23

Total Test time (real) =  21.06 sec

The following tests FAILED:
	 17 - belegstellen_riegel (Failed)
	 18 - belegstellen_messung (Failed)
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
[ 56%] Built target aktion_probe
[ 60%] Built target zufall_probe
[ 65%] Built target schranken_probe
[ 69%] Built target zustand_probe
[ 78%] Built target meldung_probe
[ 78%] Built target pruefsumme_probe
[ 82%] Built target festkomma_probe
[ 86%] Built target werte_probe
[ 95%] Built target schritt_probe
[ 95%] Built target verlauf_probe
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
11/13 Test #11: zustand_probe ....................   Passed    0.02 sec
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
[ 41%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
[ 66%] Built target vorrat_probe
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
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
.toml:205  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 selbst -- dieselbe Form wie bei
  daten/reihen.toml:211  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 stammt vom 2026-09-05 aus dem Paket
  daten/reihen.toml:227  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und der naechsten
  daten/reihen.toml:374  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:374  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 selbst vom 2026-09-05
  daten/reihen.toml:406  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:406  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:456  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:457  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:501  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:508  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:555  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:556  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als Sollreihe der Klasse gesetzt
  daten/reihen.toml:586  (Gliederungsziffer stat
2 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/reihen.toml:406
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Leitzins ist seit dem 2026-09-03 keine Sollreihe

  zitierend: daten/reihen.toml:556
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Der Leitzins ist seit dem 2026-09-03 keine Sollreihe

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
t Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:587  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:691  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:810  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:810  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:819  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:819  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:1126  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1324  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1600  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1601  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1601  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1757  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1813  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:1946  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 -- fd777fb und 89dc83c vom 2026-08-31
  daten/reihen.toml:1946  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 vom 2026-09-05 steht dort nicht
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  parameter.toml:20  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:80  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  parameter.toml:898  (kein Dokumentname im Absatz)
      gesucht war: WIE DER PRUEFER ZAEHLT
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig
  werkzeuge/belegstellen/belegstellen_riegel.cpp:280  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:283  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet

    Start 2: belegstellen_messung
2/2 Test #2: belegstellen_messung .............***Failed    0.04 sec
Messstand 0147 -- Anker an der Ortsfrage und an der Formreihenfolge
Vorhaben:    /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Uebersetzer: /usr/bin/c++

Teil 0 -- der Messstand selbst
OK  Selbstprobe: alle neun Marken werden namentlich gelesen.
OK  Selbstprobe: die Schlusszeile wird gelesen.
OK  Selbstprobe: eine gruene Ausgabe gibt nichts her.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'fehlt'.
OK  Selbstprobe: `einmal_ersetzen` haelt den Fall 'zweimal'.
ROT Selbstprobe: `einmal_ersetzen` geht im Fall 'genau einmal' aus als yxb, erwartet war ayb.

Messstand 0147: NICHT GEMESSEN -- der Auswerter misst nicht. Alles Weitere waere wertlos.
Rueckgabe 2. Dieser Lauf sagt ueber den Riegel nichts, weder gut noch schlecht.


0% tests passed, 2 tests failed out of 2

Total Test time (real) =   1.04 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
	  2 - belegstellen_messung (Failed)
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
1/1 Test #1: bezeichner_riegel ................   Passed    0.36 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.36 sec
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
2/3 Test #2: zahlwort_reihen ..................   Passed    0.12 sec
    Start 3: zahlwort_messung
3/3 Test #3: zahlwort_messung .................   Passed   18.34 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =  18.51 sec
```
