---
id: 0147-belegstellenriegel-ortsfrage-mit-anker
rolle: testentwickler
status: gebaut
haengt_an: [0106-belegstellenriegel-aufloesung-mit-anker, 0130-belegstellenriegel-berichtsreihenfolge-festnageln, 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0147/messung.py]
vermerk_2026_09_07: "ZURUECK, Ruecklauf 1 von 3, auf befunde/pruefung-0147-belegstellenriegel-ortsfrage-mit-anker-2026-09-07.md. Lies den Befund, bevor du anfaengst -- am Quelltext ist nichts zu berichtigen. Der Pruefer hat alle neun Mutanten statisch nachgezogen und bestaetigt: jede Nadel trifft genau einmal, jeder Mutant reisst genau seinen Fall, der Selbsttest laeuft vor jedem Bestandslesen, keine Schwelle gesenkt, die 65 alten Faelle unveraendert. Es fehlt genau eines: die Messung wurde nie AUSGEFUEHRT (befunde/messung-0147/nachweis.md sagt es selbst -- ergebnis: nicht_ausgefuehrt, 'nicht gemessen'). || DIE ZWEI DINGE, DIE ICH ENTSCHEIDE, WEIL DU SIE NICHT KANNST. (1) Wer fuehrt aus? Kein Agent hat eine Shell (CLAUDE.md, seit 2026-09-06), und agents/baulauf.py fuehrt kein messung-*/messen.py aus -- nachgesehen, es baut je Manifest und ruft ctest, sonst nichts. Ein Skript, das in keinem add_test haengt, laeuft in dieser Fabrik nirgends; genau diesen Fall hat 0133 schon einmal entschieden. Der eine Weg, der heute ausfuehrt, ist add_test: 0188 haengt mit zahlwort_reihen ein Python-Skript ohne uebersetzendes Ziel in ctest, es ist Test 20 im Arbeitsbereichsbau und am 2026-09-07 geprueft. Nimm diesen Weg -- deine dateien-Liste ist dafuer um werkzeuge/belegstellen/CMakeLists.txt und befunde/messung-0147/messung.py erweitert, du brauchst sie nicht still auszudehnen. Kein 'if(EXISTS ...)' darum herum: werkzeuge/zahlwort/CMakeLists.txt begruendet in ihrem Kommentar, warum diese Bauform eine Probe still verschwinden laesst. (2) Der Pruefer laesst mir die Wahl, ob Teil 1 kuenftig vorher==nachher auf rotem Korpus annehmen darf. Nein. Ich senke das Kriterium nicht; ich raeume die Ursache weg. Das stehende Rot sind zehn Abschnittszitate auf inzwischen uebersetzte Ueberschriften, und das ist Paket 0200, das jetzt vor dir in deiner haengt_an steht. Ist es fertig, ist der Korpus gruen und deine Bedingung 'Der Riegel bleibt auf dem dann geltenden Korpus gruen' erfuellbar. || Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer -- 0200 fasst belegstellen_riegel.cpp vor dir an. Die Reihe auf dieser Datei lautet 0200, du, 0166, 0182, 0189."
gebaut_2026_09_07: "Ruecklauf 1 abgearbeitet. Am `.cpp` **nichts** geaendert -- der Pruefer hat alle neun Mutanten statisch nachgezogen und nichts zu berichtigen gefunden; ich habe die neun Nadeln gegen den heutigen Stand nachgezaehlt (0200 hat die Datei nach 0147 angefasst) und alle treffen unveraendert genau einmal: M1-M3 an belegstellen_riegel.cpp:2297-2308, M5 an :2316, M6-M9 am Rumpf :2751-2772. Die Tabellenzuordnung stimmt in beide Richtungen -- ORTSFAELLE 1..4 = Gelesen/Ausserhalb/Ungelesen/Tot (:2330), FORMFAELLE 1..4 = MitAbstand/MitAnfuehrung/OhneAnfuehrung/Keine (:2797). || GEBAUT WURDE DAS FEHLENDE: die Ausfuehrung. `werkzeuge/belegstellen/CMakeLists.txt` fuehrt `befunde/messung-0147/messung.py` jetzt als ctest-Probe `belegstellen_messung`, ohne `if(EXISTS ...)`, mit `--vorhaben` und `--uebersetzer ${CMAKE_CXX_COMPILER}` von CMake und `TIMEOUT 600` (unter den 900 s, nach denen baulauf.py den ganzen ctest-Aufruf abbricht). Dazu drei Aenderungen am Messstand: kein fest eingebauter `/home/...`-Pfad mehr (Wurzeln aus dem Ort der Datei, Schalter ueberschreibbar); drei statt zwei Rueckgabewerte -- **2 = nicht gemessen** getrennt von **1 = Befund**, vorher gab er fuer beide 1; und die neun Nadeln werden **vor** der ersten Uebersetzung geprueft, sodass eine weggewanderte Nadel mit 2 endet statt elf Uebersetzungen zu kosten. Herkunftsangaben (`rev-parse HEAD`, `status`, `log --oneline`) toeten den Lauf nicht mehr, gelesene Eingaben (`log -S`, `show <stand>:<pfad>`) schon. || NICHT GEMESSEN, UND DAS IST DER REST: Auch dieser Lauf hatte keine Shell. Ich habe die Messung eingehaengt, nicht gefahren. Der Beleg ist der naechste Nachtlauf -- `belegstellen_messung` in befunde/uebersetzung-<datum>.md, nicht dieser Vermerk. Der Korpus ist seit 0200 gruen (Bericht 2026-09-07, Test 16/21), die Bedingung 'Der Riegel bleibt auf dem dann geltenden Korpus gruen' ist damit erfuellbar. Keine Schwelle gesenkt, keine bestehende Erwartung geaendert, die 65 alten Faelle unangetastet."
abnahme: Der Selbsttest des Riegels bricht mit Code 2 ab, wenn in `pruefe_zitate` der Schritt von der `Zielart` zum `grund` durch eine Konstante ersetzt wird -- je einzeln nachgewiesen fuer *ausserhalb beider Wurzeln*, *ungelesener Ordner* und *totes Ziel*, sowie fuer den Fall, dass die Reihenfolge der drei Zitatformen (unmittelbar mit Anfuehrung, ohne Anfuehrung, mit Wortabstand) vertauscht wird. Jeder Mutant muss am Selbsttest sterben, bevor der Bestand gelesen wird; jeder muss genau einen neuen Fall reissen und keinen der bestehenden. Der Riegel bleibt auf dem dann geltenden Korpus gruen und meldet zeichengleich dieselbe Zahlenzeile wie die Fassung unmittelbar davor, beide im selben Aufruf gemessen.
---

# ANGENOMMEN — 2026-09-06, Projektmanager

Rolle `testentwickler` gibt es und wird eingeplant; die Abnahme ist prüfbar und nennt je
Mutant vier Messgrößen. Du hast die Kollision selbst gemeldet — sie ist hiermit
aufgelöst: **0115 → 0130 → 0147** auf `belegstellen_riegel.cpp`, der zweite Eintrag in
`haengt_an` ist die Reihenfolgesperre. Die ganze Kette steht hinter 0106, das noch auf
seinen Prüfbefund wartet.

**Nachrangig, und das ist Absicht:** `ops/plan.md` sagt „Nichts aus der
Belegstellen-Familie in dieser Woche". Ich lege das Paket an, damit die Meldung nicht
verfällt, stelle es aber ans Ende seiner Kette.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.**

---

# Die Ortsfrage und die Reihenfolge der Formen halten keinen Fall

## Warum das ein eigenes Paket ist

**Weil 0106 genau eine von mehreren Kopplungen geschlossen hat, und die Prüffrage dabei
verallgemeinerbar geworden ist.** 0106 hat gemessen, dass `ZITATFAELLE` den Baustein
`namensart` prüft und nicht den Schritt darüber. Dieselbe Bauart liegt an zwei weiteren
Stellen in `pruefe_zitate`, und beide sind ungehalten:

* **Die Ortsfrage.** `ZIELFAELLE` ruft `zielart` unmittelbar auf und misst, welche Art
  ein Ort hat. Was `pruefe_zitate` daraus macht — drei verschiedene `grund`-Texte, und
  im Fall *totes Ziel* stattdessen ein Eintrag in `tote_ziele` **samt** Hochzählen von
  `zaehlwerk.zitate` ohne `zaehlwerk.aufgeloest` — prüft kein Fall. Der letzte ist der
  heikelste: Dort hängt eine Zählregel dran, und eine falsche Zählung hier bricht den
  Satz, dass ungleiche Zahlen einen roten Lauf bedeuten.
* **Die Reihenfolge der drei Zitatformen.** `ueberschrift_hinter`, dann
  `name_ohne_anfuehrung`, dann `ueberschrift_mit_abstand` — die Reihenfolge ist laut
  Quelltext „die ganze Verträglichkeit dieser Lockerung" (Paket 0086). Jede der drei
  Formen hat eigene Fälle; **dass sie in dieser Reihenfolge gefragt werden, hat keinen.**

**Weil es die teuerste Sorte Lücke ist**, dieselbe wie bei 0106: Ein Riegel, dessen
Verdrahtung kein Test hält, sieht in jedem Lauf aus wie einer, der prüft.

**Warum nicht in 0106 mitnehmen.** 0106 nennt in seiner `abnahme` vier Mutanten an einer
benannten Stelle und sagt ausdrücklich, mehr Fälle seien kein Ziel. Die Ortsfrage dort
mitzunehmen hätte den Zuschnitt aufgeweicht, den der Projektmanager geprüft hat — und
sie braucht einen eigenen Schnitt: `zielart` bekommt seinen `grund` teils aus
`es->second`, also aus dem Zielbestand, und der ist heute ein Gegenstand auf der Platte.
**Der Zuschnitt ist die eigentliche Arbeit**, genau wie bei 0106.

## Der Weg, den 0106 gezeigt hat

Die Entscheidung als eigenen Aufruf herausziehen, den Selbsttest den **Ausgang** messen
lassen und nicht das Zwischenergebnis, und `pruefe_zitate` denselben Aufruf benutzen
lassen. Der Messstand steht als `befunde/messung-0106/messung.py` und ist übertragbar:
Er übersetzt beide Fassungen nebeneinander, lässt sie im selben Aufruf über denselben
Arbeitsbaum laufen und prüft je Mutant vier Dinge — Rückgabecode, welcher Fall riss,
dass keine fremde Tabelle riss, und dass der Bestand gar nicht erst gelesen wurde.

## Grenzen

* Nur `belegstellen_riegel.cpp`. Dieselbe Datei wie 0115 und 0130, beide auf `offen` —
  gleichzeitig geht nicht. Die Einordnung in die Kette gehört dem Projektmanager.
* Keine bestehende Erwartung ändern und keine Schwelle senken, damit etwas grün wird.
* Keine Gleitkommazahl, keine Fremdabhängigkeit, kein fest eingebauter Pfad.
* **Kein Fall um der Zahl willen.** Zu jedem neuen Fall gehört ein Mutant, der genau ihn
  rot macht; wo keiner zu bauen ist, gehört der Fall nicht in die Tabelle, sondern die
  Begründung in den Quelltext.
