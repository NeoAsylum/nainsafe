---
id: 0130-belegstellenriegel-berichtsreihenfolge-festnageln
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Der Riegel meldet dieselben Funde in wechselnder Reihenfolge, weil er die Dateien nie sortiert

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
