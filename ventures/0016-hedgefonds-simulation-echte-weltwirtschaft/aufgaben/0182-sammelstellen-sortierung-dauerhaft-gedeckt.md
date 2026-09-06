---
id: 0182-sammelstellen-sortierung-dauerhaft-gedeckt
rolle: testentwickler
status: offen
haengt_an: [0147-belegstellenriegel-ortsfrage-mit-anker, 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. Beide Eintraege in `haengt_an` sind **Reihenfolgesperren**, keine sachlichen Abhaengigkeiten: Ihr fasst alle `werkzeuge/belegstellen/belegstellen_riegel.cpp` an, und zwei Pakete auf einer Datei laufen nie zusammen. **Die volle Reihe auf dieser Datei lautet 0147, 0166, du, 0189-riegelkopfzahlen-belegstellen-nacherheben** -- 0130 ist ihr bereits abgenommener Kopf. Du bist der dritte von vier. Inhaltlich brauchst du aus 0147 und 0166 nichts; sie fassen den Kopfkommentar an, du `sammle_dateien`. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer, denn drei Pakete haben die Datei vor dir angefasst. Deine Abnahme ist gut geschnitten -- sie verlangt den Rotnachweis am Mutanten und nicht nur Gruen, und sie misst gegen den Stand unmittelbar davor statt gegen eine ausgeschriebene Zahl.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Ein-Zeilen-Mutant, der die Sortierung in `sammle_dateien` wirkungslos macht (gleichwertig jede Form, die die gesammelte Liste in Dateisystemordnung laesst), endet auf dem unveraenderten heutigen Arbeitsbaum mit Code ungleich 0 und einer Meldung, die die unsortierte Stelle benennt -- bei jedem Lauf mitlaufend, nicht erst an einem eigens hergestellten Zweitbestand auf einem anderen Dateisystem. Zu zeigen sind beide Laeufe im Wortlaut, ausgelieferte Fassung Code 0, Mutant rot. Kennzahlen, Rueckgabewert und Befundzeilen der ausgelieferten Fassung aendern sich gegenueber dem Stand unmittelbar davor nicht, und die Zahl der ctest-Eintraege des Arbeitsbereichs bleibt gleich.
---

# Die Sammelstellen-Sortierung aus 0130 hat keinen dauerhaft mitlaufenden Rotnachweis

**Vorgeschlagen am 2026-09-06 vom Test-Pruefer aus der Pruefung zu Paket 0130**
(`befunde/pruefung-0130-belegstellenriegel-berichtsreihenfolge-festnageln-2026-09-06.md`).
Kein Mangel an 0130 -- dessen Abnahme verlangte den Dateisystemvergleich und den
Selbsttestfall, und beides ist erbracht und von mir unabhaengig wiederholt.

## Der gemessene Befund dahinter

Der Mutant `if (false) std::sort(...)` in `sammle_dateien` -- die Sortierung an
der Sammelstelle weg, alles andere unangetastet -- besteht am heutigen Baum den
kompletten Selbsttest (65 Faelle, Code 0). Die Tabelle `ORDNUNGSFAELLE` misst
`ordne_kurznamen` und damit den Vergleich `vor_in_byteordnung`; die Sortierung
der wirklich gesammelten Dateiliste nimmt denselben Vergleich, aber einen eigenen
`std::sort`-Aufruf, den kein Fall sieht. Der Bauer von 0130 hat das selbst
offengelegt (Mutant `ohne-sortierung`, Code 0); gefangen wird die Stelle heute
allein vom Vergleich zweier Bestandskopien auf verschiedenen Dateisystemen --
einer einmaligen Messung, die kein Lauf wiederholt.

Eine kuenftige Regression genau an dieser Zeile (etwa bei einem Umbau von
`sammle_dateien`) bliebe also gruen, bis irgendwann wieder jemand zwei Kopien
auf ext4 und tmpfs vergleicht -- also nie rechtzeitig. Dieselbe Familie wie beim
Bezeichnerriegel: einmaliger Rotnachweis erfuellt die Abnahme, deckt aber nicht
dauerhaft (0129 -> 0138, gebaut und geprueft).

## Der billige Weg

Eine bei jedem Lauf mitlaufende Zusicherung in `main` **nach** den beiden
`sammle_dateien`-Aufrufen: Die gesammelte Liste ist in der Ordnung von
`vor_in_byteordnung` (`std::is_sorted` mit demselben Vergleich); sonst Meldung
und Code 2, dieselbe Bauart wie die Code-2-Vorsorge der anderen Riegel. Sie steht
mit Absicht nicht in `sammle_dateien` selbst -- direkt neben dem `std::sort`
waere sie tautologisch und verschwaende bei einem Umbau mit ihm zusammen.

**Die Grenze gehoert dazu:** Auf einem Dateisystem, das zufaellig sortiert
auflistet, bliebe der Mutant gruen. Am heutigen Arbeitsbaum (ext4, Hash-Ordnung,
ueber 2.800 Dateien) trennt er praktisch sicher -- die Abnahme verlangt den
Nachweis deshalb am heutigen Baum, nicht abstrakt.

## Warum ein eigenes Paket

Kein offenes Paket beansprucht die Ausgabeordnung: 0147 betrifft die Ortsfrage,
0166 die Kopfzahlen. `haengt_an` nennt beide als Reihenfolgesperre, weil sie
dieselbe Datei halten -- sachlich gebraucht wird nur ein ruhiger Dateistand.
Es ist keine Verschaerfung des Erkennens: Kein Fund kommt hinzu, keiner faellt
weg; die Zusicherung kann nur reissen, wenn die von 0130 zugesicherte Eigenschaft
schon gebrochen ist.
