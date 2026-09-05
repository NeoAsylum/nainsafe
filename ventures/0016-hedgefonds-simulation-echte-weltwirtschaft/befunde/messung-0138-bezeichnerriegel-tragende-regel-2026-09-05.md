---
typ: messung
paket: 0138-bezeichnerriegel-tragende-regel-dauerhaft-gedeckt
rolle: testentwickler
datum: 2026-09-05
bezugsstand: 456aefa (Arbeitsbaum, mit fremder Drift -- siehe unten)
ergebnis: die Regel ist mitlaufend gedeckt
---

# Der Mutant an der tragenden Regel wird von selbst rot

## Der gewaehlte Weg

Das Paket liess zwei zu: ein dateifreier Eingang in `lies_datei` oder ein Katalogfall
des Mutationslaufs. Gewaehlt ist der **dateifreie Eingang**, und zwar aus dem Grund, den
der Projektmanager als Kollisionsgrenze notiert hat: Der Katalogweg haette
`werkzeuge/mutation/` mitgeaendert, und dieses Paket haelt nur
`werkzeuge/bezeichner/bezeichner_riegel.cpp`.

Geaendert ist genau eine Datei; ein neues Uebersetzungsziel und einen neuen
ctest-Eintrag legt der Weg nicht an.

## Was gebaut wurde

`lies_datei` ist in zwei Teile zerlegt:

* `lies_text(std::string_view inhalt, ...)` -- der ganze bisherige Rumpf. Er nimmt
  Wortlaut statt Pfad und ist damit vom Selbsttest aus erreichbar.
* `lies_datei(const fs::path& pfad, ...)` -- oeffnet die Datei, liest sie ein und reicht
  weiter. Eine nicht lesbare Datei zaehlt weiterhin nicht mit.

Dazu eine **fuenfte Falltabelle** `EINLESEFAELLE` mit fuenf Textproben und der Laeufer
`selbsttest_einlesen()`. Er laeuft je Probe genau die Kette, die `main` fuer eine
Kernquelle laeuft: einlesen, `sammle_behaelter` ueber den Codetext, und je Kandidat erst
die Deklarationsmenge, dann `regel`. Geprueft wird viererlei: ob der Name in der
Deklarationsmenge steht, wie viele Zusicherungen und Kandidaten gezaehlt wurden, wie der
Kandidat ausgeht, und ob der **Vorspann** deklariert bleibt.

Die fuenf Proben:

| # | Wortlaut | erwartet |
|---|---|---|
| 1 | Name nur als Mitglied einer negativen Zusicherung | nicht deklariert, **Befund** |
| 2 | derselbe Name als gewoehnliche Deklaration | deklariert, aufgeloest |
| 3 | beides in einer Quelle | deklariert, aufgeloest |
| 4 | Anforderung mit Parameterliste | deklariert, aufgeloest |
| 5 | Zusicherung, Kommentar mit Wendung "nicht mehr" | nicht deklariert, `abgelegter_name` |

1 und 5 sind der Gegenstand, 2 bis 4 die Gegenprobe. Fall 3 haelt fest, dass die Regel
die **Fundstelle** ueberspringt und nicht den Namen; Fall 4, dass der Mustervergleich
eine Anforderung mit Parameterliste nicht mitfaengt -- taete er es, striche er einen
Namen aus der Menge, den es gibt.

## Lauf 1 -- die ausgelieferte Fassung, Code 0

Arbeitsbereich, `ctest -R bezeichner_riegel --no-tests=error`:

```
bezeichner_riegel, Selbsttest: 9 Faelle zur Zerlegung, 6 zur negativen
Zusicherung, 10 zur Form eines Kandidaten, 18 zu den Regeln und 5 zum Einlesepfad,
alle wie erwartet.
bezeichner_riegel: 29 Kernquellen mit 15183 Zeilen gelesen, davon 5682 Kommentarzeilen
in 1246 Bloecken; 898 Bezeichner in Rueckwaerts-Anfuehrung geprueft, 854 davon
aufgeloest, 44 Fundstellen uebergangen. 1994 Namen im Kern deklariert, 4 negative
Sichtbarkeitszusicherungen abgezogen.
...
Kein Bezeichner in einem Kommentar des Kerns zeigt ins Leere.
```

`Rueckgabewert der ausgelieferten Fassung: 0`

**Der Umbau ist wirkungsfrei.** Alle Korpuszahlen sind zeichengleich mit dem Stand
davor: 29 Kernquellen, 15183 Zeilen, 5682 Kommentarzeilen, 1246 Bloecke, 898 Kandidaten,
854 aufgeloest, 44 uebergangen, 1994 Namen, 4 Zusicherungen; auch die Aufstellung je
Regel (`abgelegter_name 4; bauziel 9; commitkennung 1; dateiname 6; fremder_behaelter 4;
fremdwort 2; kennung 6; namensteil 1; namensvorsilbe 1; parameterschluessel 5;
quellenangabe 3; reserviert 1; schluesselwort 1`) ist unveraendert. Geaendert hat sich
allein die Zahl der Selbsttestfaelle, 43 -> 48.

## Lauf 2 -- der Mutant, Code 2

Aufgelegt auf eine Abschrift ausserhalb des Quellbaums: die Zeile
`                    zugesichert = true;` (kommt genau einmal vor, vom Skript geprueft)
zu `                    zugesichert = false;`. Wortlaut des Laufs:

```
Selbsttest Einlesepfad, Fall 1 verfehlt.
  Name 'schreibe': deklariert 1 erwartet 0
  Zusicherungen 1 erwartet 1; Kandidaten 1 erwartet 1
  Ausgang 'aufgeloest' erwartet 'befund'
  Mitname 'Z' deklariert 1 erwartet 1
Selbsttest Einlesepfad, Fall 5 verfehlt.
  Name 'schreibe': deklariert 1 erwartet 0
  Zusicherungen 1 erwartet 1; Kandidaten 1 erwartet 1
  Ausgang 'aufgeloest' erwartet 'abgelegter_name'
  Mitname 'Z' deklariert 1 erwartet 1

bezeichner_riegel: 2 von 48 Faellen des Selbsttests sind nicht wie erwartet
ausgegangen. Der Riegel hat den Bestand gar nicht erst gelesen -- ein Messgeraet,
das seine eigenen Faelle verfehlt, misst auch fremde nicht.
```

`Rueckgabewert des Mutanten: 2`

**Er stirbt aus dem gemeinten Grund**, und das steht in den Zahlen daneben:
`Zusicherungen 1` und `Kandidaten 1` sind unveraendert -- der Mustervergleich liest die
Zusicherung weiter, sie wird nur nicht mehr abgezogen. Genau diese Trennung fing die
bisherige Code-2-Vorsorge nicht, denn sie zaehlt Zusicherungen und faende hier vier.

**Zwei von 48 verfehlt, und zwar die gemeinten.** Die Faelle 2, 3 und 4 bleiben gruen;
sie haengen nicht an der Ausnahme und belegen damit, dass die Tabelle nicht als Ganzes
reisst. `Mitname 'Z' deklariert 1` in beiden roten Faellen zeigt, dass der Vorspann auch
unter dem Mutanten unberuehrt bleibt -- gemessen wird der letzte Namensteil und nichts
sonst.

Der Lauf endet auf dem **unveraenderten heutigen Baum**, nicht an einem eigens gebauten
Altbaum. Das war der Zweck des Pakets.

## Der Messstand

`bau/messung-0138/` -- ein Wegwerfprojekt: `auflegen.py` schreibt `geliefert.cpp` und
`mutant.cpp` aus der Quelle (und bricht ab, wenn der Wortlaut nicht genau einmal
vorkommt), die `CMakeLists.txt` baut beide mit den Schaltern des Arbeitsbereichs
(`-fwrapv -fno-fast-math`, Sanitizer) und traegt drei Proben ein: `geliefert_0138`
(muss durchkommen -- der Vorlauf), `mutant_0138` (`WILL_FAIL`) und `beide_laeufe_0138`,
das beide nacheinander laeuft und die Rueckgabewerte abdruckt.

Er liegt unter `bau/` und nicht daneben, aus zwei Gruenden: Der Riegel betritt diesen
Ordner gar nicht erst, und `baulauf.py` nimmt ihn von der Manifestsuche aus
(`AUSGENOMMEN`). Laege er woandershin im Vorhaben, zaehlte der Riegel seine Datei- und
Zielnamen mit, und der Vorlauf haette nicht mehr die Zahlen des Arbeitsbereichs. Der
Vorlauf hat sie: `geliefert_0138` meldet dieselben 29 / 15183 / 854 wie der
Arbeitsbereich.

## ctest-Eintraege

Vor der Aenderung 16, nach der Aenderung 16 -- beides an demselben Baum gemessen, mit
`ctest --test-dir bau -N`. Der Weg legt konstruktionsbedingt keinen an: Der Diff dieses
Pakets umfasst eine `.cpp` und keine `add_test`- oder `add_executable`-Zeile.

## Was mir nicht gehoert

Der Arbeitsbereich laesst sich zur Stunde **nicht vollstaendig uebersetzen**:

```
werkzeuge/belegstellen/belegstellen_riegel.cpp:2509:46: error: invalid initialization
of reference of type 'const {anonymous}::Absatz&' from expression of type
'const std::string_view'
```

Die Datei ist zur selben Zeit von einem anderen Lauf geaendert (`git status` fuehrt
ausserdem `werkzeugkette.cmake`, `daten/reihen.toml` und ein neues
`werkzeuge/schlussriegel/`). Das ist nicht mein Paket und kein Befund gegen dieses
Ergebnis -- gemeldet, nicht angefasst. Das gebaute `belegstellen_riegel`-Binaerprogramm
des heutigen Uebersetzungsberichts laeuft ueber meinen geaenderten Wortlaut und bleibt
gruen (`Test #15 ... Passed`), ebenso alle uebrigen 16 Proben.
