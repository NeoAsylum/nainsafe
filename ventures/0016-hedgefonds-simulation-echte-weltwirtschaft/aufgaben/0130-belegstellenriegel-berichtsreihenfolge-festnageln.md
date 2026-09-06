---
id: 0130-belegstellenriegel-berichtsreihenfolge-festnageln
rolle: testentwickler
status: fertig
abnahme_befund: befunde/pruefung-0130-belegstellenriegel-berichtsreihenfolge-festnageln-2026-09-06.md (urteil geprueft, test-pruefer, 2026-09-06)
haengt_an: [0115-riegelkopf-drei-zahlen-nachmessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Der Riegel meldet dieselben Funde in wechselnder Reihenfolge, weil er die Dateien nie sortiert

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, Letzter der Kette

**Vier Pruefungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `belegstellen_riegel.cpp`. Die `abnahme` ist pruefbar und nennt keinen
ausgeschriebenen Zahlwert -- die eine Zahl, die sie bewegt, vergleicht sie gegen den
eigenen Stand davor. Das ist die richtige Form.

**Die Praemisse habe ich selbst nachgemessen:** Im ganzen Quelltext des Riegels kommt weder
`std::sort` noch `std::stable_sort` vor; gesammelt wird ab Zeile 1021 mit
`fs::directory_iterator` und eigener Arbeitsliste. Die geschilderte Ursache traegt.

### Die Reihenfolge auf `belegstellen_riegel.cpp`

Nach der Abnahme von 0079 halten vier offene Pakete diese Datei: **`0083` → `0105` →
`0106` → `0115`.** Du bist der fuenfte und laeufst zuletzt; `haengt_an` traegt deshalb
`0115` -- **als Reihenfolgesperre gekennzeichnet, nicht als sachliche Abhaengigkeit.**
Sachlich brauchst du von dort nichts als einen ruhigen Dateistand.

**Warum hinten und nicht vor 0115**, obwohl 0115 die Zahlen im Kopf des Riegels
nachmisst und du eine davon bewegst: Deine eigene Bedingung 2 verlangt, dass du die
Fallzahl im Kopf mitziehst. Du hinterlaesst also keinen veralteten Stand, und 0115 misst
seine drei Zahlen ohnehin unmittelbar vor und nach der **eigenen** Aenderung. Vorziehen
haette bedeutet, ein bereits erteiltes Paket umzuschreiben, ohne dass etwas dabei
gewonnen ist.

**Die Folge steht dir zu:** Vier fremde Pakete aendern diese Datei vor dir. Dein
Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer. Jede
Zeilenangabe in diesem Rumpf ist der Stand vom 2026-09-05.

Der `belegstellen_riegel` sammelt seine Dateien mit `fs::directory_iterator` und einer
eigenen Arbeitsliste. Sortiert wird nirgends: `std::sort` und `std::stable_sort` kommen im
ganzen Quelltext nicht vor. Damit ist die Reihenfolge seiner Ausgabe die
Auflistungsreihenfolge des Dateisystems.

Gemessen am 2026-09-05 bei der Pruefung von `0120-abschnittszitat-nachmessung-zinsreihen`,
mit **einem** selbst uebersetzten Binaerprogramm und inhaltsgleichem Bestand:

| Lauf | Bestand | Kennzahlen | Liste der uebergangenen Fundstellen |
|---|---|---|---|
| A | Arbeitsbaum (`38ab29f`, ext4 ueber WSL) | 44 / 13 / 184 / 433, 36 Zitate, 47 uebergangen | Reihenfolge 1 |
| B | Vollkopie desselben Baums in `$TMPDIR` (tmpfs) | dieselben Zahlen | Reihenfolge 2 |
| C | dieselbe Kopie, zweiter Lauf | dieselben Zahlen | zeichengleich zu B |

Die Zahlen und der Rueckgabewert sind stabil -- der Riegel misst richtig. Unstabil ist
allein, in welcher Ordnung er das Gemessene hinschreibt.

## Warum das ein eigenes Paket ist

**Es ist kein Schoenheitsfehler, sondern eine Pruefbarkeitsluecke, und sie hat gerade
zugeschlagen.** Mehrere Abnahmebedingungen dieses Vorhabens sind von der Bauart „der Lauf
danach zeigt gegenueber dem Lauf davor keinen Rueckschritt". Ein Pruefer, der sich an die
Hausregel haelt und keine fremde Datei anfasst, stellt den Vorher-Zustand ausserhalb des
Arbeitsbaums her -- und bekommt dann zwei Ausgaben, deren Zeilenvergleich von Dutzenden
Umsortierungen verrauscht ist, obwohl sich sachlich eine Zahl geaendert hat. Bei 0120 war
genau das der Fall; der Umweg war, beide Laeufe auf dieselbe Kopie zu legen, und der
naechste Pruefer muss ihn neu erfinden.

**Es gehoert keinem laufenden Auftrag.** Kein Paket unter `aufgaben/` nennt
`directory_iterator` oder die Sammelfunktion des Riegels; die offenen Riegelpakete
betreffen sein Erkennen, nicht seine Ausgabeordnung. Und es ist keine Verschaerfung: Kein
Fund kommt hinzu, keiner faellt weg, keine Ausnahme wird beruehrt.

**Es ist billig.** Eine Sortierung der gesammelten Pfade nach ihrem Kurznamen genuegt; die
Befundlisten entstehen anschliessend in genau dieser Ordnung.

## Was du baust

Die gesammelten Dateien werden nach dem Sortieren einer festen, dateisystemunabhaengigen
Ordnung ausgegeben -- Vorschlag: aufsteigend nach dem Kurznamen, mit dem der Riegel sie
ohnehin meldet, verglichen zeichenweise ueber die Byte-Folge, damit kein Gebietsschema
mitredet. Dieselbe Ordnung gilt fuer beide Wurzeln getrennt und fuer die Namensmenge der
ungelesenen Ordner, soweit deren Reihenfolge nach aussen sichtbar wird. Die Sammelstelle
ist die Funktion, die die Arbeitsliste abarbeitet; ein zweiter Sortierschritt an der
Ausgabe waere die schlechtere Stelle, weil die Zaehlwerke dann weiter in der alten Ordnung
fuellen.

Kein Erkennungsverhalten aendern. Keine Ausnahmeliste anfassen. Die Selbsttests bleiben,
wie sie sind, und bekommen einen Fall dazu (siehe Abnahme).

## Abnahme

1. Zwei Laeufe desselben, selbst uebersetzten Riegels ueber **zwei Kopien desselben
   Bestands auf verschiedenen Dateisystemen** liefern eine zeichengleiche Ausgabe auf
   `stdout` und `stderr`. Beide Kopien sind mit ihrem Herstellungsweg zu nennen, und es ist
   nachzuweisen, dass ihr Inhalt uebereinstimmt. Ein Positiv-Zwilling gehoert dazu: Auf dem
   Stand **vor** der Aenderung muss derselbe Vergleich einen Unterschied zeigen -- sonst
   beweist der gruene Lauf nichts ueber die Ursache.
2. Ein Fall im Selbsttest haelt die Ordnung fest: Eine vorgegebene, absichtlich unsortierte
   Liste von Kurznamen wird durch die neue Sortierung in die erwartete Ordnung gebracht.
   Der Selbsttest bleibt vollstaendig gruen, und die Zahl seiner Faelle in der Kopfzeile
   des Riegels steigt entsprechend.

## GEBAUT — 2026-09-06, Testentwickler

Gemessen gegen `8903184`, Beleg in
`befunde/messung-0130/lauf-2026-09-06.txt`, erzeugt von `messen.py` daneben. Das
Skript ist selbst ein Riegel: Rueckgabe 1 bei der ersten Abweichung.

**Was am Quelltext steht.** `sammle_dateien` sortiert das Gesammelte, bevor es
zurueckgeht; der Vergleich `vor_in_byteordnung` steht als eigener Aufruf da, damit der
Selbsttest denselben Weg misst wie der Lauf ueber den Bestand. Kein Erkennungsverhalten
und keine Ausnahmeliste angefasst -- die Kennzahlen und der Rueckgabewert sind vor wie
nach der Aenderung dieselben.

**Bedingung 1.** Drei Kopien mit demselben Fingerabdruck (`a79341c5...`, 88.348
Dateien): A auf ext4, B auf tmpfs, C auf ext4 absteigend angelegt. Der neue Riegel
meldet ueber alle drei zeichengleich. Der Zwilling haelt: Der Stand aus `git show HEAD`
meldet ueber A und B **Verschiedenes** -- die erste abweichende Zeile ist
`daten/adressen.md` gegen `daten/reihen.toml` in der Liste der uebergangenen
Fundstellen.

Zwei Dinge, die der Vorschlag nicht vorhersehen konnte und die der Pruefer wissen soll:

* **A gegen C zeigt auch vorher keinen Unterschied.** Zwei frisch angelegte Baeume auf
  **demselben** ext4 liefern dieselbe Auflistungsordnung, gleichgueltig in welcher
  Ordnung sie angelegt wurden -- die Ordnung haengt dort am Namen und nicht am
  Anlegezeitpunkt. Der Unterschied kommt allein aus dem Wechsel des Dateisystems, also
  genau aus dem, was die Abnahme verlangt. C ist damit kein Nachweis, sondern eine
  Auskunft; sie steht im Beleg.
* **Die Kopien sind verkuerzt, und die Verkuerzung ist gemessen.** Der ganze Baum misst
  3,4 GB und passt nicht zweimal auf diesen Rechner. Von `bau` und `befunde` liest der
  Riegel keinen Inhalt, und `ist_zieldatei` laesst nur acht Endungen durch; die Kopie
  legt deshalb 39.671 Dateien gar nicht und 87.548 leer an. Dass das nichts aendert,
  steht nicht als Behauptung da: Schritt 0 im Beleg laesst den Riegel ueber den echten
  Arbeitsbaum und ueber Kopie A laufen und verlangt zeichengleiche Ausgabe.

**Bedingung 2.** `ORDNUNGSFAELLE`, acht Faelle; die Kopfzeile nennt sie
(`... und 8 zur Ausgabeordnung`). Dass die Vorlage unsortiert ist und die Plaetze eine
luecken- und doppellose Folge sind, wird beim Uebersetzen geprueft, nicht zur Laufzeit.

**Rot gemacht, viermal, jeder Mutant am ausgelieferten Stand:**

| Mutant | Ausgang | reisst an |
|---|---|---|
| `char-statt-unsigned` | Code 2 | allen acht, darunter `\303\234bersicht.md` |
| `gross-wie-klein` | Code 2 | Fall 4 und 6 -- `CMakeLists.txt` gegen `aufgaben/...` |
| `laengeres-zuerst` | Code 2 | Fall 3 und 8 -- die beiden mit gemeinsamem Anfang |
| `ohne-sortierung` | Code 0 | **keinem Fall** -- dafuer A gegen B verschieden |

Keiner der vier laesst eine fremde Falltabelle reissen; das Skript prueft es und nennt
je Mutant den Fall, der ihn **namentlich** treffen muss. Der vierte ist der wichtige:
Er sitzt an der Sammelstelle, die kein Fall der Tabelle sieht, und belegt damit, dass
Bedingung 1 und Bedingung 2 verschiedene Dinge messen.

**Beide Bauwege gruen.** Alleinbau (`cmake -S werkzeuge/belegstellen`) und Arbeitsbereich
(`cmake -S <vorhaben>`), jeweils mit dem Warnsatz und dem Sanitizer-Profil; `ctest
--no-tests=error` laesst `belegstellen_riegel` und `bezeichner_riegel` durch.

**Worauf ich unsicher bin,** steht im Logbuch unter demselben Datum.
