---
typ: uebersetzung
venture: 0016-hedgefonds-simulation-echte-weltwirtschaft
datum: 2026-09-05
bauart: cmake
manifeste: 4
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
[  5%] Built target pruefstand
[  9%] Built target belegstellen_riegel
[ 15%] Built target pruefstand_geprueft
[ 38%] Built target kern_geprueft
[ 50%] Built target kern
[ 53%] Built target schranken_probe
[ 57%] Built target werte_probe
[ 65%] Built target festkomma_probe
[ 65%] Built target vorrat_verfahren_probe
[ 69%] Built target meldung_probe
[ 80%] Built target schritt_probe
[ 80%] Built target zufall_probe
[ 80%] Built target pruefsumme_probe
[ 84%] Built target vorrat_kernanker_probe
[ 88%] Built target zustandsausgabe_probe
[ 92%] Built target vorrat_probe
[100%] Built target schreiber_probe
[100%] Built target zustand_probe
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
 18 nennt drei von sechs Stellen mit
  parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:71  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  daten/adressen.md:637  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:11  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:63  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:64  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:94  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 stehen in
  daten/reihen.toml:108  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und Abschnitt 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
  daten/reihen.toml:108  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
  daten/reihen.toml:134  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:178  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:209  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:209  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:259  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:260  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:302  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:309  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:356  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:357  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als Sollreihe der Klasse gesetzt
  daten/reihen.toml:387  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:388  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:492  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:611  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:611  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:620  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:620  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:927  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1125  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der I
1 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6
  nachgeschlagen in: daten/deckungsbefund-1997.md
  gesuchte Ueberschrift: Die Reihenliste nennt IWF IFS

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
WF-Volltext ist ungelesen
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1402  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1402  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1558  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1614  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/deckungsbefund-1997.md:79  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 tatsaechlich eingebettet wird -- nicht ein Naeherungswert
  daten/lizenzbefund-wdi.md:152  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 als Modelleinheit
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:283  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 dieses Befundes
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
      gesucht war: Droits de propriété intellectuelle
  daten/einheitenbefund-pwt-baci.md:20  (kein Dokumentname im Absatz)
      gesucht war: Woran es haengt
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  werkzeuge/belegstellen/belegstellen_riegel.cpp:262  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:265  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig


93% tests passed, 1 tests failed out of 14

Total Test time (real) =   0.99 sec

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
[ 42%] Built target kern_geprueft
[ 47%] Built target kern
[ 52%] Built target schreiber_probe
[ 63%] Built target zustandsausgabe_probe
[ 63%] Built target meldung_probe
[ 68%] Built target schritt_probe
[100%] Built target festkomma_probe
[100%] Built target schranken_probe
[100%] Built target pruefsumme_probe
[100%] Built target zufall_probe
[100%] Built target werte_probe
[100%] Built target zustand_probe
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
[ 50%] Built target pruefstand_geprueft
[ 50%] Built target pruefstand
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
[100%] Built target belegstellen_riegel
```

## `ctest --test-dir` -- FEHLER (Code 8)

```
r: 18 nennt drei von sechs Stellen mit
  parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  parameter.toml:71  (Gliederungsziffer statt Ueberschrift: 12)
      gesucht war: 12 sagen dasselbe
  daten/adressen.md:637  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:11  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:63  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:64  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:94  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 stehen in
  daten/reihen.toml:108  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und Abschnitt 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
  daten/reihen.toml:108  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17 specs/0016-.../daten.md Quellen und Lizenzen daten/deckungsbefund-1997.md
  daten/reihen.toml:134  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:178  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:209  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:209  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter 31 -- siehe
  daten/reihen.toml:259  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:260  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 von lizenzbefund-reihen.md ein Vorbehalt steht
  daten/reihen.toml:302  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:309  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:356  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:357  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 und in T37 weiter als Sollreihe der Klasse gesetzt
  daten/reihen.toml:387  (Gliederungsziffer statt Ueberschrift: 5)
      gesucht war: 5
  daten/reihen.toml:388  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 die Umrechnungsreihe des Deflators noch nicht fuehrt
  daten/reihen.toml:492  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/reihen.toml:611  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3
  daten/reihen.toml:611  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4
  daten/reihen.toml:620  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 fuer die Einheit
  daten/reihen.toml:620  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 fuer das Basisjahr
  daten/reihen.toml:927  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der IWF-Volltext ist ungelesen
  daten/reihen.toml:1125  (Gliederungsziffer statt Ueberschrift: 3)
      gesucht war: 3 und 5 -- der I
1 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6
  nachgeschlagen in: daten/deckungsbefund-1997.md
  gesuchte Ueberschrift: Die Reihenliste nennt IWF IFS

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
WF-Volltext ist ungelesen
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 17)
      gesucht war: 17
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
  daten/reihen.toml:1402  (Gliederungsziffer statt Ueberschrift: 1)
      gesucht war: 1 und Abschnitt 7 Nr
  daten/reihen.toml:1402  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 Nr
  daten/reihen.toml:1558  (Gliederungsziffer statt Ueberschrift: 6)
      gesucht war: 6
  daten/reihen.toml:1614  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7
  daten/deckungsbefund-1997.md:79  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 tatsaechlich eingebettet wird -- nicht ein Naeherungswert
  daten/lizenzbefund-wdi.md:152  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 als Modelleinheit
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:283  (Gliederungsziffer statt Ueberschrift: 4)
      gesucht war: 4 dieses Befundes
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
      gesucht war: Droits de propriété intellectuelle
  daten/einheitenbefund-pwt-baci.md:20  (kein Dokumentname im Absatz)
      gesucht war: Woran es haengt
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
  werkzeuge/belegstellen/belegstellen_riegel.cpp:262  (kein Dokumentname im Absatz)
      gesucht war: -- Paket 0079, oben begruendet. Die groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen Wortlaut, an dem sich etwas nachschlagen liesse
  werkzeuge/belegstellen/belegstellen_riegel.cpp:265  (kein Dokumentname im Absatz)
      gesucht war: -- ein Formelzeichen oder ein Platzhalter, ebenfalls oben begruendet
  pruefstand/test/vorrat_kernanker_probe.cpp:3  (kein Dokumentname im Absatz)
      gesucht war: Strategiekern, vierwertig


0% tests passed, 1 tests failed out of 1

Total Test time (real) =   0.76 sec

The following tests FAILED:
	  1 - belegstellen_riegel (Failed)
Errors while running CTest
```
