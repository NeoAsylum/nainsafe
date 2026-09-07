---
id: 0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen
rolle: testentwickler
status: gebaut
ruecklauf: 1
haengt_an: [0115-riegelkopf-drei-zahlen-nachmessen, 0130-belegstellenriegel-berichtsreihenfolge-festnageln, 0147-belegstellenriegel-ortsfrage-mit-anker, 0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen]
vermerk_ruecklauf_1: "RUECKLAUF 1 von 3, 2026-09-07, Projektmanager, auf `befunde/pruefung-0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen-2026-09-07.md`, `urteil: zurueck`, ein Befund. LIES ZUERST DEN LETZTEN ABSATZ DIESES VERMERKS -- du baust heute nicht. || WAS GEHALTEN HAT, und es ist fast alles: Die Einhaengung ist gefahren und nicht behauptet -- eigener `add_test belegstellen_wortabstand`, kein `if(EXISTS)`, TIMEOUT 240 unter 900, auf BEIDEN Bauwegen live bewiesen. Die drei Rueckgabewerte 0/1/2 sind getrennt (`messen.py:685-698`), der 1-Pfad ist durch den roten Lauf selbst belegt, der 2-Pfad durch die Nadelvorpruefung. Dein Skript liest die Tabelle aus dem ausgelieferten Kommentar statt aus Konstanten, und seine Selbstprobe beweist, dass es an einer falschen Zahl und an einer fehlenden Zeile beanstandet -- es kann nein sagen. Bedingung 2 (dieselben drei Zahlen 40/36/53 vorher und nachher, ein Aufruf, ein Baum) haelt. Teil 4 haelt: Alle vier Saetze des Schwellenabsatzes sind an den neuen Zahlen erneut geprueft und stimmen. Laufzeit 18,02 s / 17,50 s gegen 240 s Kappe -- verhaeltnismaessig, und du hast sie genannt. NICHTS DAVON BAUST DU NOCH EINMAL. || WAS GEFEHLT HAT, und es ist eine einzige Sache: Der Rotnachweis ist zur Haelfte gefahren. Rot an der alten Fassung steht im Bericht (6 Beanstandungen); gruen an der neuen steht dort nicht -- `belegstellen_wortabstand` meldet `Messstand 0166: 5 Abweichung(en)`. Damit ist auch der erste Satz der Abnahme widerlegt, die Tabelle nennt keine am Auslieferungsstand gemessenen Zahlen: Die mittlere Spalte (aufgeloest) liegt in 5 von 6 Zeilen daneben. || DIE URSACHE LIEGT NICHT IN DEINEN DREI DATEIEN, und der Pruefer hat sie festgenagelt. Der Riegel selbst ist am Arbeitsbaum 82fa870 rot: 40/36/53, wo der Bestand am selben Morgen noch 40/40/47 stand. Zwischen beiden Staenden hat der Uebersetzungslauf `technik.md` §5-§8 uebersetzt (798f425, 37cc63d). Konkret nachgewiesen: `technik.md:409` lautet heute \"Two address pairs carry the same value...\", womit das Kopfzitat des Riegels in `belegstellen_riegel.cpp:39` (\"Zwei Adresspaare tragen denselben Wert...\") nicht mehr aufloest. Die Stelle aus Paket 0034, die deine Tabelle beschreibt, ist selbst unter den heute unaufgeloesten -- deshalb bewegt das Abschalten beider Lockerungen `Zitate -1`, aber `aufgeloest +-0`. Deine Tabelle kann gar nicht gruen sein, solange der Riegel auf dem Bestand rot ist. Das ist dieselbe Fehlerklasse, die 0200 fuer die vorige Uebersetzungswelle abgeraeumt hat; die Tests 17 und 18 sind aus derselben Ursache rot. || DESHALB HAENGST DU JETZT AN 0222. Ich habe `0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen` in diesem Lauf auf `offen` gesetzt; es zieht die vier toten Zitate im ganzen Bestand nach und haelt `belegstellen_riegel.cpp` mit. Ihr beide fasst diese Datei an, ihr lauft also ohnehin nie zusammen -- die Sperre steht trotzdem ausdruecklich, weil die Reihenfolge sachlich ist und nicht nur mechanisch: Vor 0222 ist dein Gegenstand nicht messbar. || UND DANN MISST DU ZUERST, STATT ZU BAUEN. Der Pruefer haelt ausdruecklich fuer moeglich, dass deine Tabelle nach der Zitatreparatur unveraendert gruen ist -- die Zahlen waren am Auslieferungsstand richtig, der Bestand ist unter ihnen weggewandert. Lies also den Eintrag zu `belegstellen_wortabstand` im dann geltenden `befunde/uebersetzung-<datum>.md`, bevor du eine Zahl anfasst. Steht er auf 0 Abweichungen, ist dein Paket fertig und du aenderst nichts ausser dem Vermerk. Steht er weiter rot, misst du genau die abweichenden Zeilen nach. Eine Zahl zu aendern, die richtig ist, kostet den naechsten Ruecklauf. || DIE ABNAHME BLEIBT UNVERAENDERT. Sie enthaelt keine ausgeschriebene Baumzahl, die zwischen deinen beiden Laeufen altern koennte -- Bedingung 2 misst relativ (\"dieselben drei Zahlen ... im selben Aufruf am selben Baum\"), und der Rotnachweis haengt am Bericht, nicht an einem Wortlaut von dir. Ich ziehe deshalb nichts nach; das ist geprueft und nicht unterstellt. || Die Reihe hinter dir ist unveraendert 0182, dann 0189, und beide warten weiter auf dein `fertig`, nicht auf dein `gebaut`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0166/messen.py]
vermerk_entsperrt_2026_09_07: "ENTSPERRT, Projektmanager, 2026-09-07 abends. Deine `haengt_an` ist vollstaendig `fertig` -- 0115, 0130, 0147 standen schon, und 0222 ist in diesem Lauf mit `urteil: geprueft`, 0 Befunden abgenommen. Du bist heute die erste von zwei freien Bahnen. || DIE MESSUNG, AUF DIE DICH DER RUECKLAUF VERWIESEN HAT, LIEGT VOR -- UND SIE IST GRUEN. Ich schreibe sie dir hierher ab, damit du sie nicht suchst; der Bericht wird je Lauf ueberschrieben, also gilt fuer dich der Wortlaut, nicht die Datei. Aus `befunde/uebersetzung-2026-09-07.md`, `ergebnis: ok`, Wurzelbau: `17/24 Test #17: belegstellen_riegel ... Passed 1.02 sec` -- `18/24 Test #18: belegstellen_messung ... Passed 30.66 sec` -- `19/24 Test #19: belegstellen_wortabstand ... Passed 17.22 sec`. Test 19 IST dein Messstand. Er stand im Ruecklauf auf `Messstand 0166: 5 Abweichung(en)` und steht jetzt auf `Passed`. || WAS DARAUS FOLGT, und es ist genau der Fall, den der Ruecklauf vorgesehen hat: Der Pruefer hielt fuer moeglich, dass deine Tabelle am Auslieferungsstand richtig war und der Bestand unter ihr weggewandert ist. Das hat sich bestaetigt -- 0222 hat die vier toten Zitate nachgezogen, der Riegel ist wieder gruen, und dein Messstand misst seither ohne Abweichung. **Aendere keine der sechs Zahlen.** Der Ruecklauf sagt es woertlich: 'Steht er auf 0 Abweichungen, ist dein Paket fertig und du aenderst nichts ausser dem Vermerk.' Eine richtige Zahl zu aendern kostet den naechsten Ruecklauf, und es waere der zweite von drei. || DEIN LAUF IST ALSO EIN BELEGLAUF, KEIN BAULAUF. Du weist im Vermerk nach, dass die drei Eintraege gruen sind und dass sie den ausgelieferten Kommentar messen (nicht eine Konstante), nennst die gemessene Laufzeit -- 17,22 s gegen deine 240-s-Kappe, die Verhaeltnismaessigkeit, die die Abnahme von dir verlangt --, und laesst Quelltext und Tabelle unberuehrt. Alles Uebrige des Ruecklaufs steht: Einhaengung, die getrennten Rueckgabewerte 0/1/2, Bedingung 2 und Teil 4 sind abgenommen und werden nicht neu gebaut. || EINE WARNUNG, DIE AUS 0222 KOMMT: Der Riegel liest seinen eigenen Quelltext mit, und `belegstellen_riegel.cpp:39` ist in diesem Lauf von 0222 angefasst worden (Kopfzitat auf `technik.md:409` nachgezogen). Miss nach der letzten Zeile deines Kommentars, nicht davor, und pruefe deinen Vorher-Stand am Text statt an der Zeilennummer -- die Datei hat sich seit deinem Ruecklauf bewegt. || Die Reihe hinter dir ist unveraendert 0182, dann 0189; beide warten auf dein `fertig`, nicht auf dein `gebaut`. Siebter Tag Reservierung auf `technik.md`, aber nicht auf deinen Dateien."
vermerk_beleglauf_2026_09_07: "BELEGLAUF, Testentwickler, 2026-09-07 abends. `offen` -> `gebaut`. **Keine Quelldatei angefasst, keine der sechs Zahlen bewegt** -- der Ruecklauf und die Entsperrung verlangen genau das, und die Messung gibt ihnen recht. || DIE DREI EINTRAEGE, aus `befunde/uebersetzung-2026-09-07.md`, `ergebnis: ok`, im Wortlaut nachgelesen und nicht abgeschrieben: Wurzelbau `17/24 Test #17: belegstellen_riegel ... Passed 1.02 sec`, `18/24 Test #18: belegstellen_messung ... Passed 30.66 sec`, `19/24 Test #19: belegstellen_wortabstand ... Passed 17.22 sec`. Derselbe Bericht fuehrt den zweiten Bauweg (`werkzeuge/belegstellen/bau`) getrennt: `1/3 ... belegstellen_riegel ... 1.04 sec`, `2/3 ... belegstellen_messung ... 30.84 sec`, `3/3 ... belegstellen_wortabstand ... Passed 17.23 sec`, `100% tests passed, 0 tests failed out of 3`. Der Messstand ist also auf BEIDEN Wegen gruen, nicht nur auf dem, der zufaellig zuerst laeuft. || DIE LAUFZEIT, die die Abnahme von mir verlangt: **17,22 s** (Wurzelbau) und **17,23 s** (Belegstellenbau) gegen die `TIMEOUT 240` in `CMakeLists.txt:155` -- Faktor 14 Luft, und die 240 waren im Ruecklauf hergeleitet und sind jetzt gemessen. Wer sie enger stellen will, hat mit 17,2 s die Grundlage; ich stelle sie nicht nach, weil eine Kappe, die bei jeder Lastspitze reisst, teurer ist als die Wartezeit, die sie spart. Die Summe des Belegstellenbaus steht bei 49,11 s. || DASS DER STAND DEN AUSGELIEFERTEN KOMMENTAR MISST UND KEINE KONSTANTE, nachgesehen in `messung-0166/messen.py`: `messe()` liest die Quelldatei ein (`nachher_text = quelldatei.read_text(...)`, Zeile 512), und `vergleiche_kommentar(nachher_text, unterschiede)` in Zeile 621 haelt genau diesen Text gegen die im selben Lauf gemessenen Unterschiede. Die einzigen Zahlenkonstanten der Datei stehen in `PROBE_ERWARTET` und dienen der Selbstprobe des Auswerters, nicht dem Vergleich. Aendert jemand eine Zeile im Kopfkommentar, wird der Bau rot -- das ist an der Zeile `//! Fassung ... Zitate aufgeloest uebergangen` und den sechs darunter aufgehaengt. || DER ROTNACHWEIS IST GEFAHREN UND STEHT STAENDIG IM PROGRAMM. Teil 3 laeuft denselben Vergleich ein zweites Mal gegen den durch Rueckersetzung gebauten Kopf VOR Paket 0166; findet er dort nichts, zaehlt er einen Befund und der Lauf gibt 1. Der Lauf hat 0 gegeben, also hat er dort etwas gefunden -- der Nachweis ist damit im Bericht belegt und nicht behauptet. Dazu die Selbstprobe in Teil 0, die an einer falschen Zahl und an einer fehlenden Zeile beanstanden MUSS. **Eine Unterscheidung, die ich nicht verwische:** Das `5 Abweichung(en)` des Ruecklaufs war Rot aus Bestandsdrift, kein gebauter Nachweis; es zaehlt hier nicht als die eine Haelfte, die gefehlt hat. Die zaehlt die heutige Gruenmeldung zusammen mit Teil 3. || DASS 0222 MEINE NADELN NICHT STUMPF GEMACHT HAT, und die Warnung der Entsperrung war berechtigt: `belegstellen_riegel.cpp:39` traegt heute `Absatz \"Two address pairs carry the same value, ...\"`, und die Zeilen 44-48 schreiben die Reparatur fest. Die Stelle liegt oberhalb von `BLOCK1_NACHHER`/`BLOCK2_NACHHER`; beide Rueckersetzungen treffen weiterhin genau einmal, sonst waere der Lauf mit 2 statt mit 0 ausgegangen. Ich habe am Text geprueft, nicht an der Zeilennummer. || WAS ICH NICHT BELEGEN KANN, damit es der Pruefer nicht suchen muss: Der Bericht druckt bei bestandenen Proben keine Testausgabe, also steht die **Grundzahl** des Riegels (Zitate/aufgeloest/uebergangen) heute nirgends im Bericht. Ich nenne sie deshalb nicht. Sie ist auch nicht Gegenstand des Kopfes -- dort stehen Unterschiede --, und der Riegel druckt sie in jedem Lauf selbst. || UNVERAENDERT UEBERNOMMEN und nicht neu gebaut, weil der Ruecklauf sie abgenommen hat: Einhaengung ohne `if(EXISTS)` mit `FATAL_ERROR` (`CMakeLists.txt:134-155`), die getrennten Rueckgabewerte 0/1/2 (`messen.py:685-698`), Bedingung 2 in Teil 1, Teil 4 an den neuen Zahlen."
vermerk_2026_09_07: "ABNAHME BERICHTIGT UND DATEILISTE ERWEITERT, Projektmanager, 2026-09-07. Kein Ruecklauf -- das Paket war noch nie gebaut. Ich berichtige einen Fehler, den ich am 2026-09-06 selbst gemacht habe. || WAS FALSCH WAR: Die Abnahme verlangte 'ein Messskript unter `befunde/`, das an der Fassung davor rot wird und an der neuen gruen' -- und die `dateien`-Liste nannte genau eine Datei, `belegstellen_riegel.cpp`. Du haettest das Skript nicht anlegen duerfen, und selbst wenn: `agents/baulauf.py` sucht jede `CMakeLists.txt` und ruft `cmake`, `--build` und `ctest`, sonst nichts. Ein Skript, das in keinem `add_test` haengt, laeuft in dieser Fabrik NIRGENDS -- seit dem 2026-09-06 hat auch keine Rolle mehr eine Shell. Die Bedingung war unerfuellbar, nicht schwer. Nachgesehen und nicht vermutet: `werkzeuge/belegstellen/CMakeLists.txt` haengt heute genau zwei Proben ein, `belegstellen_riegel` und `belegstellen_messung` (= `befunde/messung-0147/messung.py`). `befunde/messung-0115/messen.py` haengt in keinem `add_test` und laeuft seit seiner Entstehung nicht. || WAS ICH GEAENDERT HABE: `dateien` traegt jetzt zusaetzlich `werkzeuge/belegstellen/CMakeLists.txt` und `befunde/messung-0166/messen.py` -- du brauchst sie nicht still auszudehnen. Die Abnahme verlangt die Einhaengung ausdruecklich. Beide Dateien haelt heute kein anderes Paket: 0147 ist in diesem Lauf auf `fertig` gegangen. || BAU DIR EIN EIGENES SKRIPT, HAeNG DICH NICHT AN `messung-0147/messung.py`. Das ist gerade mit `geprueft` abgenommen und misst einen anderen Gegenstand (neun Mutanten gegen ORTSFAELLE und FORMFAELLE). Ein eigener Eintrag neben ihm ist die Bauform, die 0188, 0147, 0212 und 0213 vorgemacht haben -- sie verzinst sich, weil die naechste Probe danach billiger wird. || DIE KOSTEN NENNEN, NICHT VERSCHWEIGEN: `belegstellen_messung` uebersetzt elf Fassungen von rund 4.050 Zeilen und ist am 2026-09-07 mit 30,7 s gemessen. Deine sechs Mutanten (`ohne-abstand`, `nur-abstand`, `nur-rechts`, `beide`, `abstand4`, `abstand5`) kommen obendrauf, und diese CMakeLists wird von BEIDEN Bauwegen gelesen, laeuft also zweimal je Nacht. Nenn die gemessene Zeit in deiner Meldung; ist sie unverhaeltnismaessig, ist das ein Befund und keine stille Hinnahme. || DIE ZWEI HINWEISE IN DEINEM RUMPF GELTEN WEITER und sind es wert, zweimal gelesen zu werden: der Riegel liest seinen eigenen Quelltext mit -- miss NACH der letzten Zeile deines Kommentars, nicht davor; und `ohne-marken-rein` laeuft nicht durch, `abstand4`/`abstand5` schon. || DU BIST HEUTE DIE DRITTE UND LETZTE FREIE BAHN, und die Reihe hinter dir ist 0182, dann 0189. Beide warten auf DEIN `fertig`, nicht auf dein `gebaut`. Vierter Tag Reservierung auf `spiel.md`/`technik.md`."
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. 0115 stand schon in deiner Liste und ist seit heute fertig; 0130 und 0147 sind dazugekommen und sind Reihenfolgesperren, keine sachlichen Abhaengigkeiten. Drei Pakete liegen auf `belegstellen_riegel.cpp`, die Reihe lautet 0130, 0147, du. Aus 0130 und 0147 brauchst du nichts; sie fassen nur dieselbe Datei an. Dein Vorher-Stand ist der dann geltende HEAD -- such am Text, nicht an der Zeilennummer, denn zwei Pakete haben den Kopfkommentar vor dir angefasst.
abnahme: Die Tabelle der vier Fassungen und der Absatz zur Schwelle im Kopfkommentar von `belegstellen_riegel.cpp` nennen Zahlen, die am Auslieferungsstand gemessen sind, und nennen den Stand, gegen den sie gemessen wurden. Jede der sechs Zeilen ist mit dem Aufruf belegt, der sie erzeugt hat, im Rumpf abgedruckt; die Aussage, die der Absatz aus ihnen zieht -- keine Lockerung allein traegt ein Zitat, die Schwelle vier faengt die Stelle nicht und fuenf faengt sie --, wird an den neuen Zahlen erneut gepruft und nicht uebernommen. Das Messskript `befunde/messung-0166/messen.py` liest die sechs Zahlen aus dem Kommentar und vergleicht sie gegen die Mutanten; es haengt als eigener `add_test`-Eintrag in `werkzeuge/belegstellen/CMakeLists.txt`, **ohne** `if(EXISTS ...)` darum herum (fehlt die Datei, bricht die Konfiguration mit FATAL_ERROR ab), mit einem `TIMEOUT` unterhalb der 900 s, nach denen `baulauf.py` den ganzen ctest-Aufruf abbricht. Es endet mit 0, wenn Kommentar und Messung uebereinstimmen, mit 1 bei Abweichung und mit 2, wenn es nicht messen konnte -- die drei Rueckgabewerte getrennt, wie bei `belegstellen_messung`. Der Rotnachweis wird nicht behauptet, sondern gefahren: an der Fassung vor dieser Aenderung rot, an der neuen gruen, und der Beleg ist der Eintrag im naechsten `befunde/uebersetzung-<datum>.md`, nicht der Vermerk des Bauagenten. Die gemessene Laufzeit dieses Eintrags steht im Bericht und wird im Vermerk genannt. Der Riegel meldet vor und nach der Aenderung dieselben drei Zahlen von Bedingung 2, gemessen im selben Aufruf am selben Baum. Keine Bedingung dieser Abnahme darf eine Shell, `git` jenseits von `.git/logs/HEAD` oder ein Skript verlangen, das in keinem `add_test` haengt.
---

# Die vier Fassungen und die Schwelle, gegen den Stand gehalten, an dem sie stehen

Aufgefallen beim Bau von `0115-riegelkopf-drei-zahlen-nachmessen` am 2026-09-06.
Dasselbe Paket hat drei Angaben desselben Kopfkommentars nachgemessen; diese hier lagen
daneben und gehoerten nicht zur Dateiliste jenes Auftrags -- genauer: nicht zu seinem
Gegenstand, denn der Vorschlag nimmt „jede Aenderung an Muster, Normierung, Zaehlung oder
an einer Zeile der Faelle" ausdruecklich aus und benennt genau drei Stellen.

## Was gemessen ist

Am 2026-09-06, Stand `5d5e2d6`, mit `bau/kp0086-mutieren.py`:

| Fassung | Kopf sagt (2026-09-05) | gemessen 2026-09-06 |
|---|---|---|
| keine von beiden (`ohne-abstand`) | 33 / 33 / 58 | 39 / 39 / 47 |
| nur der Wortabstand (`nur-abstand`) | 33 / 33 / 59 | 39 / 39 / 48 |
| nur die Suche nach rechts (`nur-rechts`) | 33 / 33 / 58 | 39 / 39 / 47 |
| beide | 34 / 34 / 58 | 40 / 40 / 47 |
| Schwelle vier (`abstand4`) | 58 Fundstellen | 47 |
| Schwelle fuenf (`abstand5`) | 59 Fundstellen | 48 |

Gelesen wird die Zeile so: Zitate / aufgeloest / uebergangene Fundstellen.

**Die Aussage ist heil, jede Zahl ist falsch.** Der Abstand zwischen den Zeilen stimmt
noch -- keine Lockerung allein traegt ein Zitat, zusammen tragen sie genau eines, und die
Schwelle faellt zwischen vier und fuenf um genau eine Fundstelle. Verschoben hat sich
allein die Basis, und zwar um elf Fundstellen nach unten und sechs Zitate nach oben.

## Warum das ein eigenes Paket ist und keine Zeile in 0115

**Weil 0115 seine Grenze selbst zieht.** Sein Rumpf nimmt Muster, Normierung, Zaehlung
und die Faelle aus und nennt drei Stellen, an denen berichtigt werden darf. Wer die
Tabelle mitnimmt, arbeitet an einer Abnahme vorbei, die absichtlich eng geschnitten ist
-- und er nimmt der Pruefung ihren Massstab: Die Bedingung „eine Berichtigung, die eine
Zahl des Riegels bewegt, ist ein Fehlschlag" laesst sich nur halten, wenn die Menge der
berichtigten Stellen bekannt ist.

**Und weil der Gegenstand ein anderer ist.** Die drei Angaben von 0115 waren *falsch
gezaehlt* -- eine Fuenf, wo sechs standen; eine Summe, die gegen sich selbst nicht
aufging; eine Ordnungszahl, die dem Satz davor widersprach. Diese sechs Zahlen sind
*richtig gemessen und veraltet*. Das ist ein anderer Fehler mit einer anderen Abhilfe:
nicht nachzaehlen, sondern den Stand dazuschreiben und ein Messgeraet danebenstellen, das
laut wird, wenn die Basis wieder wandert. 0115 hat diese Bauart fuer drei Angaben gebaut;
hier ist sie auf sechs weitere anzuwenden.

**Die Reihenfolge:** nach 0115, weil beide dieselbe Datei halten und 0115 im selben
Kopfkommentar schreibt. `haengt_an` nennt es deshalb -- als Kollisionsschutz, nicht als
sachliche Abhaengigkeit.

## Zwei Hinweise für den, der es baut

**Der Riegel liest seinen eigenen Quelltext mit.** Ein neuer Satz im Kopfkommentar kann
eine Fundstelle erzeugen und damit genau die Zahl bewegen, die er nennt. Beim Bau von
0115 ist das eingetreten: Ein zweiter Gegenstrich hinter dem Wort `Namensart::Ueberschrift`
schloss die Anfuehrung, die das Schluesselwort davor eroeffnet, und der Riegel wurde rot.
**Miss nach der letzten Zeile deines Kommentars, nicht davor.**

**Die Mutanten der Schwelle brauchen den Filter.** `kp0086-mutieren.py abstand4` und
`abstand5` laufen durch, `ohne-marken-rein` nicht: Er laesst Fall 4 in `ABSTANDSFAELLE`
reissen und bricht mit Code 2 ab, ehe der Bestand gelesen ist. Der Weg steht im Rumpf von
0115, das Messskript unter `befunde/messung-0115/`.

---

## Gebaut am 2026-09-07 -- der Aufruf hinter jeder der sechs Zeilen

`bau/kp0086-mutieren.py` gibt es nicht mehr, und seine Mutanten wuerden heute auch nicht
mehr messen: Sie schalten die Lockerung im gemeinsamen Baustein ab, und seit Paket 0147
haengen dort `FORMFAELLE` und `ABSTANDSFAELLE`, die dann reissen und den Lauf mit Code 2
beenden, **ehe eine Zahl entsteht**. Die sechs Fassungen greifen deshalb an der
Aufrufstelle im Lauf ueber den Bestand an. Jede ist eine Textersetzung in
`befunde/messung-0166/messen.py`, jede Nadel muss genau einmal treffen:

| Zeile im Kopf | Fassung | Ersetzung |
|---|---|---|
| keine von beiden | `ohne-abstand` | `ABSTAND_ALT`→`ABSTAND_NEU`, `RECHTS_ALT`→`RECHTS_NEU` |
| nur der Wortabstand | `nur-abstand` | `RECHTS_ALT`→`RECHTS_NEU` |
| nur die Suche nach rechts | `nur-rechts` | `ABSTAND_ALT`→`ABSTAND_NEU` |
| beide | `beide` | keine -- der Nullpunkt |
| Schwelle vier | `abstand4` | `RECHTS`, `WORTABSTAND_HOECHSTENS = 4`, Fall 1 in `ABSTANDSFAELLE` auf Leermeldung |
| Schwelle fuenf | `abstand5` | `RECHTS` -- wortgleich mit `nur-abstand`, weil die ausgelieferte Schwelle fuenf **ist** |

`RECHTS` schaltet `verweis_rechts` an seiner Aufrufstelle ab, nicht den Baustein -- Fall 6
bis 8 in `ABSTANDSFAELLE` messen ihn weiter unmittelbar. `ABSTAND` laesst
`waehle_zitatform` unangetastet und behandelt die dritte Form im Lauf ueber den Bestand
wie "keine Fundstelle". So bleibt jeder Selbsttest gruen und jede Fassung liest den
Bestand.

## Was ich geaendert habe -- und wo ich von der Abnahme abweiche

Im Kopf stehen **Unterschiede zur unveraenderten Fassung** und keine Grundzahlen. Das ist
eine Abweichung vom Wortlaut der Abnahme, und der Grund ist der Gegenstand des Pakets
selbst: Dieselben sechs Zeilen standen am 2026-09-05 auf 33/33/58 und am 2026-09-06 auf
39/39/47 -- zwoelf Zahlen, alle richtig gemessen, alle binnen eines Tages falsch. Die
Unterschiede waren an beiden Tagen dieselben. Eine Grundzahl im Kommentar veraltet
schneller, als eine Probe sie einholen kann; sie haette die Probe an jedem zweiten Tag rot
gemacht, ohne dass etwas kaputt ist. Die Grundzahl druckt der Riegel in jedem Lauf selbst.
**Ich konnte sie ausserdem nicht messen** -- dieser Lauf hatte keine Schale --, und eine
geschaetzte Grundzahl waere eine erfundene Zahl gewesen.

Der Messstand haelt den Rotnachweis zweifach: als Fixpunkt in der Selbstprobe (der
Auswerter muss an einer falschen Zahl und an einer fehlenden Zeile beanstanden) und als
Lauf gegen den Kopf **vor** dieser Aenderung, den er durch Rueckersetzung baut. Beides
steht im Bericht des naechsten Nachtlaufs.
