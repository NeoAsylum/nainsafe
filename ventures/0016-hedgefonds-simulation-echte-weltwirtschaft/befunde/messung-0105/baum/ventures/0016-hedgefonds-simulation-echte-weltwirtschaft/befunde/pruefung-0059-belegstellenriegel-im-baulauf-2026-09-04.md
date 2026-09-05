---
typ: pruefung
paket: 0059-belegstellenriegel-im-baulauf
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Beide Bauwege uebersetzt, ctest -R belegstellen_riegel gruen (37/5/0, die 5 Treffer von Hand nachgeschlagen), Rotnachweis zu Pruefbedingung 1 an 18 eingefuegten Belegstellen gefuehrt -- 11 rot, 7 gruen mit Grund.
befunde: 1
---

# Der Riegel wird rot, wenn man die Sache kaputtmacht -- an 11 von 18 Bauarten

## Wie geprueft wurde, ohne eine Datei des Pakets anzufassen

Der Riegel bekommt die Wurzel des Quellbaums als **Argument**. Das ist die Eigenschaft,
die Abnahmebedingung 1 verlangt -- und zugleich der Weg, den Rotnachweis zu fuehren, ohne
den Baum zu veraendern: Das gebaute Programm lief gegen einen **synthetischen Baum** in
`$TMPDIR`, in dem jede Belegstellenform einmal vorkommt. Unter `ventures/` wurde nichts
geschrieben.

Einzelne Binaerdateien liessen sich in dieser Sitzung nicht ausfuehren, `ctest` schon.
Der Antrieb ist deshalb ein CMake-Pruefstand in `$TMPDIR` mit `WILL_FAIL TRUE` auf jeder
Probe, die rot sein muss -- ein gruener Lauf heisst dann: jeder Rotfall wurde gefangen.

## Bedingung 1 -- benannter Test, Wurzel von CMake: erfuellt

Beide Bauwege, die die Bauliste des Pakets behauptet, tragen:

| Weg | Ergebnis |
|---|---|
| Arbeitsbereich, `cmake -S .` | `Test #12: belegstellen_riegel ... Passed` |
| allein, `cmake -S werkzeuge/belegstellen` | `Test #1: belegstellen_riegel ... Passed` |

Die Wurzel steht nicht im Programm; `ctest -V` zeigt sie als Argument:

```
Test command: .../belegstellen_riegel "/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
```

Beide Wege liefern denselben Pfad, obwohl das Bauverzeichnis in `$TMPDIR` liegt -- er
haengt an `CMAKE_CURRENT_SOURCE_DIR`, nicht am Bauort. Ein Rechnerwechsel bricht ihn
nicht. Der Alleinbau meldet ausserdem `Warnsatz-Schlussriegel: 1 uebersetzende Ziele
geprueft, alle mit Warnsatz`; der Zustand vom Vormittag (`No project() command is
present`, `No tests were found!!!`) ist weg.

## Bedingung 2 -- gruen auf dem heutigen Stand, mit Zahl: erfuellt

```
belegstellen_riegel: 37 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei.
```

Die 5 Treffer sind einzeln nachgeschlagen, weil eine Null bei "davon 0 mit Dateinamen
daneben" auch von einem kaputten Dateinamensucher kommen koennte. Alle fuenf stehen in
`kern/src/zustand.cpp`, im Block der vier Stichproben an den Blockgrenzen unter dem
Kommentar "Vier Stichproben an den Blockgrenzen, ausgeschrieben", und sind der Fall, den
der Kopfkommentar ausdruecklich als keinen Befund beschreibt: die 1-basierte Nummer der
Adresstabelle im Zeilenendkommentar, deren 0-basierte Entsprechung die `static_assert`
in derselben Zeile nachrechnet. Es steht kein Dateiname daneben, weil dort nichts nach
auswaerts zeigt. Die Null ist keine Blindheit.

## Bedingung 3 -- der Rotnachweis: gefuehrt, hier, im Wortlaut

18 Belegstellen in einen Baum eingefuegt, gelaufen, Baum weggeraeumt. **11 rot, 7 gruen.**
Der Lauf im Wortlaut, gekuerzt um Wiederholungen gleicher Bauart:

```
11 Verweis(e) zeigen mit einer Zeilennummer in eine fremde Datei:

  CMakeLists.txt:1  -> technik.md
      # F19 siehe technik.md, Zeile 77
  faelle.cpp:2  -> kern/src/zustand.cpp
       siehe kern/src/zustand.cpp Zeile 1318
  faelle.cpp:3  -> spiel.md
      // F03 spiel.md Z. 197
  faelle.cpp:13  -> parameter.toml
      // F15 parameter.toml, Zeile 88
  unterordner/tief.hpp:1  -> technik.md
      // F20 siehe technik.md, Zeile 55

Eine Zeilennummer in eine fremde Datei wandert, ohne dass jemand etwas tut.
Sie wird ersetzt -- durch einen Bezeichner, eine Abschnittsueberschrift oder eine
Schluesselzeile im Wortlaut --, nicht ausgenommen und nicht nachgezogen.
belegstellen_riegel: 3 Bauquellen gelesen, 14 Zeilenverweise getroffen, davon 12 mit Dateinamen daneben.
```

Rot gefangen wurden: `Zeile 42`, `Zeilen 1318`, `Zeile 1318 f.`, `Z. 197`, `Z.197`,
`Z. 12345` (fuenfstellig -- die Obergrenze aus der Suchschreibweise ist zu Recht keine),
Ziel mit Pfad, Ziel mit Endung `.md`, `.toml` und `.cmake`, Fundort `CMakeLists.txt` und
Fundort in einem Unterverzeichnis.

Gruen geblieben, **jedes mit Grund**:

| Fall | warum gruen |
|---|---|
| `Zeile 42` ohne Datei auf der Zeile | Kopf, "Die Grenze dieser Messung"; als Treffer mitgezaehlt |
| `faelle.cpp, Zeile 42` in `faelle.cpp` | eigene Datei, kein Verweis nach auswaerts |
| `Zeile 9` | einstellig, die Suchschreibweise verlangt zwei Ziffern |
| `ZEILE 42`, `zeile 42`, `Zeile42` | ausserhalb der Suchschreibweise des Pakets |
| `technik.md:42` | Doppelpunktform, steht bereits als Paket 0072 |
| Treffer unter `bau/` und `befunde/` | gesperrte Ordner, im Kopf begruendet |

Die Zaehlung des Laufs geht auf: 14 Treffer, davon 12 mit Dateinamen (11 fremde plus
einmal die eigene Datei), 3 gelesene Bauquellen -- die `.md`- und `.toml`-Datei des
Probebaums sind keine. Die Zahlen sind gerechnet, nicht behauptet.

Drei weitere Proben, alle mit `WILL_FAIL TRUE` und alle bestanden: leerer Baum gibt
Code 2 mit "Der Riegel hat damit nichts geprueft -- das ist kein gruener Lauf, sondern
ein Riegel ohne Gegenstand"; Aufruf ohne Argument gibt Code 2; nicht vorhandene Wurzel
gibt Code 2. Der Nullriegel greift.

**Zur Herkunft dieses Nachweises, und das gehoert dazu:** Im Venture liegt kein
Erzeugnis des Bauagenten, das ihn fuehrt -- weder ein Baubericht noch ein Abschnitt in
der Paketdatei; der Liefercommit fasst unter `ventures/` nur Quelle, Bauliste und einen
neuen Paketvorschlag an. Die einzige verbleibende Stelle waere sein Logbuch, das diese
Rolle nicht liest und in dem nach den Hausregeln ohnehin keine Belege stehen duerfen.
Der Nachweis steht damit hier. Das ist kein Rueckweisungsgrund -- die Bedingung verlangt,
dass er *steht*, und der Projektmanager hat sie ausdruecklich dem Pruefer zugewiesen --,
aber wer spaeter fragt, wo der Rotnachweis zu 0059 liegt, findet ihn in dieser Datei.

## Wonach ausserdem gesucht wurde

**Abgeschwaechte Schwelle?** Nein. Zwischen dem Abbruchstand `1cf2e7c` und der Lieferung
`79a95eb` ist genau eine Konstante verschwunden: `MARKE`, die Marke fuer das
Abschnittszitat. Sie gehoert zu Pruefbedingung 2, die der Projektmanager nach 0067
abgetrennt hat, und der Kopfkommentar sagt das auch so. `ENDUNGEN` ist unveraendert.
Keine gesenkte Schwelle, keine entfernte Zusicherung, kein uebersprungener Test.

**Haelt die Dateiauswahl den Riegel kuenstlich gruen?** Das ist die Frage, an der ein
Riegel dieser Bauart stirbt, deshalb ist sie gemessen und nicht gelesen. Ein Mutant mit
`.md` und `.toml` in `ist_quelldatei` -- erzeugt per `cmake -P`, mit Fehlerbremse gegen
ein danebengreifendes Suchmuster --, auf den **echten** Baum gerichtet, meldet:

```
90 Verweis(e) zeigen mit einer Zeilennummer in eine fremde Datei
```

**Alle 90 liegen unter `aufgaben/`. Ausserhalb: null.** Damit ist die Auswahl belegt und
nicht nur begruendet: Was sie ausblendet, sind Arbeitspakete -- Messwerte vom Tag ihrer
Niederschrift, dieselbe Sorte wie `befunde/`, das der Kopf mit genau diesem Argument
sperrt. Sie blendet keine lebende Bauquelle aus. Die im Kopf genannten Kosten der
`bau`-Sperre sind heute ausserdem null: Unter `pruefstand/bau/pruefung-0019/` steht kein
einziger Zeilenverweis.

## Der eine Befund: der Dateiname muss unmittelbar links stehen

`dateiname_davor` geht vom Treffer **ein** Wort nach links. Steht der Dateiname weiter
links auf derselben Zeile, sieht der Riegel ihn nicht und zaehlt den Verweis als "ohne
Dateinamen", also als keinen Befund. Im Probebaum blieb `technik.md, Abschnitt Zoll,
Zeile 42` gruen.

Das ist **keine** der Grenzen, die der Kopf ausschreibt. Der beschreibt, dass eine Datei
drei Zeilen darueber nicht mehr zaehlt, und sagt "auf derselben Zeile links vom Treffer"
-- was mehr verspricht als "unmittelbar links". Im heutigen Korpus des Riegels kostet das
nichts; alle 5 Treffer stehen ohnehin ohne Datei daneben. Im Baum nebenan kostet es zwei
echte Verweise, die auch der Mutant nicht gefangen hat:

- `daten/adressen.md`, im Wortlaut `(technik.md; am 2026-09-03 Zeile 1219` -- links vom
  Treffer steht das Datum, und das traegt keine Endung.
- `daten/reihen.toml`, im Wortlaut `technik.md Abschnitt 7, und die Reihenliste sagt
  dort in Zeile 1441` -- links vom Treffer steht `dort`.

Beide sind genau die halb migrierte Form, die die sechs Aufraeumpakete hinterlassen:
Abschnitt genannt, Nummer stehen geblieben. Wer den Korpus spaeter erweitert -- der Kopf
nennt das als eigene Arbeit --, bekommt einen Riegel, der die haeufigste Restform
durchlaesst. Das ist Vorschlag `0073`. Es faellt nicht in dieses Paket: Die Verweisform
kommt im gelieferten Korpus nicht vor, und Bedingung 1 ist unabhaengig davon erfuellt.

Nicht wegzuraeumen war `befunde/append.tmp`, eine leere Zwischendatei aus diesem Lauf --
`rm` war in dieser Sitzung gesperrt, und Hausregel 3 gilt ohnehin. Sie gehoert zu dem
`.tmp`-Punkt, den der Rueckstand schon fuehrt.

Berichtigung zum Absatz darueber: `append.tmp` ist nicht leer, sondern traegt
versehentlich vier Zeilen des Frontmatters dieser Datei und sonst nichts.
