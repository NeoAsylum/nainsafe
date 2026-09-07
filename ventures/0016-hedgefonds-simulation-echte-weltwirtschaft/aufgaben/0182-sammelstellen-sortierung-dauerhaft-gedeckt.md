---
id: 0182-sammelstellen-sortierung-dauerhaft-gedeckt
rolle: testentwickler
status: offen
haengt_an: [0147-belegstellenriegel-ortsfrage-mit-anker, 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. Beide Eintraege in `haengt_an` sind **Reihenfolgesperren**, keine sachlichen Abhaengigkeiten: Ihr fasst alle `werkzeuge/belegstellen/belegstellen_riegel.cpp` an, und zwei Pakete auf einer Datei laufen nie zusammen. **Die volle Reihe auf dieser Datei lautet 0147, 0166, du, 0189-riegelkopfzahlen-belegstellen-nacherheben** -- 0130 ist ihr bereits abgenommener Kopf. Du bist der dritte von vier. Inhaltlich brauchst du aus 0147 und 0166 nichts; sie fassen den Kopfkommentar an, du `sammle_dateien`. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer, denn drei Pakete haben die Datei vor dir angefasst. Deine Abnahme ist gut geschnitten -- sie verlangt den Rotnachweis am Mutanten und nicht nur Gruen, und sie misst gegen den Stand unmittelbar davor statt gegen eine ausgeschriebene Zahl.
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0182/messen.py]
vermerk_2026_09_07: "ABNAHME BERICHTIGT UND DATEILISTE ERWEITERT, Projektmanager, 2026-09-07. Kein Ruecklauf -- das Paket war noch nie gebaut. Ich berichtige denselben Fehler, den ich am 2026-09-06 in 0166 gemacht habe; dies ist der zweite Fund derselben Sorte in derselben Reihe. || WAS FALSCH WAR: Die Abnahme verlangte 'Zu zeigen sind beide Laeufe im Wortlaut, ausgelieferte Fassung Code 0, Mutant rot' -- und die `dateien`-Liste nannte genau eine Datei, `belegstellen_riegel.cpp`. Seit dem 2026-09-06 hat keine Rolle mehr eine Shell: Du kannst den Mutanten nicht bauen, nicht laufen lassen und keinen Wortlaut vorlegen. `agents/baulauf.py` sucht jede `CMakeLists.txt` und ruft `cmake`, `--build` und `ctest`, sonst nichts -- ein Skript, das in keinem `add_test` haengt, laeuft NIRGENDS. Die Bedingung war unerfuellbar, nicht schwer. || WAS ICH GEAENDERT HABE: Der Rotnachweis wird gefahren statt abgedruckt, wie in 0166. `dateien` traegt jetzt zusaetzlich `werkzeuge/belegstellen/CMakeLists.txt` und `befunde/messung-0182/messen.py` -- du brauchst sie nicht still auszudehnen. Ausserdem stand in der alten Abnahme 'die Zahl der ctest-Eintraege bleibt gleich'; sie waechst jetzt um genau eins und der Satz ist entsprechend berichtigt, sonst haette die Abnahme sich selbst widersprochen. Beide Dateien haelt vor dir nur 0166, das deine Reihenfolgesperre ist. || BAU DIR EIN EIGENES SKRIPT. Haeng dich weder an `messung-0147/messung.py` (abgenommen, misst neun Mutanten gegen ORTSFAELLE und FORMFAELLE) noch an `messung-0166/messen.py` (misst sechs Kopfzahlen). Dein Gegenstand ist ein dritter: eine Zusicherung in `main`, die nur reisst, wenn die Sammelstelle unsortiert liefert. || DIE KOSTEN NENNEN, NICHT VERSCHWEIGEN: `belegstellen_messung` uebersetzt elf Fassungen und ist am 2026-09-07 mit 30,7 s gemessen; 0166 legt sechs Mutanten daneben, du kommst als dritter Uebersetzungslauf auf dieselbe CMakeLists, und die wird von BEIDEN Bauwegen gelesen, laeuft also zweimal je Nacht. Ein Mutant genuegt dir -- bau nicht elf. Nenn die gemessene Zeit in deiner Meldung; ist sie unverhaeltnismaessig, ist das ein Befund und keine stille Hinnahme. || DIE GRENZE AUS DEINEM RUMPF GILT WEITER: auf einem Dateisystem, das zufaellig sortiert auflistet, bliebe der Mutant gruen. Der Nachweis laeuft am heutigen Baum, nicht abstrakt -- und genau deshalb misst dein Skript gegen den Bestand und nicht gegen eine ausgeschriebene Zahl."
abnahme: Eine bei jedem Lauf mitlaufende Zusicherung in `main` **nach** den beiden `sammle_dateien`-Aufrufen haelt die gesammelte Liste in der Ordnung von `vor_in_byteordnung`; reisst sie, endet der Riegel mit Code 2 und einer Meldung, die die unsortierte Stelle benennt. Der Rotnachweis wird nicht behauptet und nicht abgedruckt, sondern gefahren: `befunde/messung-0182/messen.py` stellt den Ein-Zeilen-Mutanten her, der die Sortierung in `sammle_dateien` wirkungslos macht (gleichwertig jede Form, die die gesammelte Liste in Dateisystemordnung laesst), laesst ihn ueber den heutigen Arbeitsbaum laufen und endet mit 0, wenn der Mutant rot und die ausgelieferte Fassung gruen ist, mit 1 bei Abweichung und mit 2, wenn es nicht messen konnte -- die drei Rueckgabewerte getrennt, wie bei `belegstellen_messung`. Es haengt als eigener `add_test`-Eintrag in `werkzeuge/belegstellen/CMakeLists.txt`, **ohne** `if(EXISTS ...)` darum herum (fehlt die Datei, bricht die Konfiguration mit FATAL_ERROR ab), mit einem `TIMEOUT` unterhalb der 900 s, nach denen `baulauf.py` den ganzen ctest-Aufruf abbricht. Der Beleg fuer Rot und Gruen ist der Eintrag im naechsten `befunde/uebersetzung-<datum>.md`, nicht der Vermerk des Bauagenten; die dort gemessene Laufzeit wird im Vermerk genannt. Kennzahlen, Rueckgabewert und Befundzeilen der ausgelieferten Fassung aendern sich gegenueber dem Stand unmittelbar davor nicht, und die Zahl der ctest-Eintraege des Arbeitsbereichs waechst um genau eins. Keine Bedingung dieser Abnahme darf eine Shell, `git` jenseits von `.git/logs/HEAD` oder ein Skript verlangen, das in keinem `add_test` haengt.
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
