---
id: 0133-schlussriegel-nachbau-laeuft-nirgends
rolle: testentwickler
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/pruefung-0066/nachbau.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Der einzige Regressionsnachweis des Schlussriegels ruft niemand, und daneben steht einer, der immer rot meldet

## GEBAUT -- 2026-09-05, Testentwickler

Beide Bedingungen gemessen; der Nachweis liegt unter `befunde/messung-0133/nachweis.md`,
alle Messbaeume unter `$TMPDIR` ausserhalb des Repos.

`nachbau.py` haengt als `ctest`-Probe `schlussriegel_nachbau` in
`pruefstand/CMakeLists.txt`. Ein Baum mit **einer** stumpf gemachten Zeile in
`fabrik_riegel_sammeln` konfiguriert weiter gruen und mit demselben Meldungswortlaut --
die Probe faengt ihn trotzdem, mit 15 von 22 gekippten Urteilen; am unveraenderten Baum
ist derselbe Aufruf gruen. Die drei Bauwege sind in beiden Profilen bei
Konfigurations-, Bau- und `ctest`-Code 0, die Probenzahl steigt um genau eins auf den
zwei Wegen, die den Pruefstand enthalten (14→15 und 3→4), und bleibt auf `kern` bei 10.

**Zwei Dinge, die ueber den Buchstaben der Abnahme hinausgehen und die der Pruefer
eigens ansehen soll**, beide im Nachweis begruendet und je mit eigenem Rotnachweis:
Die Positivkontrolle `p_positiv` zaehlt jetzt in den Rueckgabewert von `nachbau.py`
(`ctest` liest nur ihn, nicht die Ausgabe), und `NACHBAU_ABLAGE` trennt die Wegwerf-
Baeume je Baubaum. Der Aufruf von Hand bleibt in Pfad, Ausgabe und Rueckgabewert
unveraendert -- 0103 und 0108 sehen keinen Unterschied.

Gemessen wurde an einem aus `8a2c381` ausgepackten Baum und nicht am Arbeitsbereich:
Zwei Nachbarpakete hatten `belegstellen_riegel.cpp` und `werkzeugkette.cmake` waehrend
meines Laufs halbfertig stehen. Begruendung und `diff -rq` im Nachweis.

Zum Ort der Bahn liegt Vorschlag `0136-schlussriegel-nachbau-in-eigenes-mitglied` bei.

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, **geteilt und umgehaengt**

**Die Rollenfrage traegt** (`testentwickler` steht in `BAUROLLEN`), und **beide Praemissen
habe ich selbst nachgemessen statt sie abzuschreiben:** Weder `nachbau.py` noch
`bauwege.py` kommt in der Werkzeugkette, in der CMakeLists des Vorhabens oder in der des
Pruefstands vor -- sie haengen tatsaechlich in keiner automatischen Bahn. Und `bauwege.py`
traegt in Zeile 36 die fest eingetragene Erwartung `{"ON": 18, "OFF": 16}`, waehrend der
Baum 19 und 17 liefert.

Drei Aenderungen, alle aus der Dateifrage und keine aus der Sachfrage.

### 1. Geteilt: die zweite Haelfte wird `0135`

Der Vorschlag begruendet, warum beide Haelften ein Paket sein sollen -- dieselbe Frage,
benachbarte Dateien. Die Begruendung ist gut und trotzdem nicht die, die hier zaehlt. **Der
Baulauf plant nach Dateien, nicht nach Themen**, und die beiden Haelften teilen keine
einzige Datei. Zusammen waren sie ein Bauplatz, getrennt sind sie zwei -- und zwei
Bauplaetze sind heute genau das, woran es fehlt.

`0135-bauwege-sollzahl-gegen-eigenen-stand` traegt die zweite Haelfte samt der Bedingung 2
des Vorschlags. Sie steht dort woertlich, wo sie hier stand. Der Text der zweiten Haelfte
bleibt unten stehen, weil er den Befund traegt und Hausregel 3 gilt; die **Arbeit** daran
gehoert 0135, nicht dir. Fass `bauwege.py` nicht an.

### 2. Umgehaengt: die Bahn geht in `pruefstand/CMakeLists.txt`

Der Vorschlag nennt `CMakeLists.txt` des Vorhabens. Diese Datei haelt heute **`0129`**,
das im selben Durchgang laeuft -- damit waere dein Paket hinter 0129 gefallen und haette
eine Runde verloren. `pruefstand/CMakeLists.txt` haelt kein offenes Paket, und dort steht
schon der Praezedenzfall, den der Vorschlag selbst nennt: die `add_test`-Zeile, mit der der
Belegstellenriegel bei jeder Abnahme mitlaeuft. Die Bahn geht also dorthin.

**Das ist eine Kollisionsentscheidung, keine Entwurfsentscheidung** -- und wenn sich beim
Bauen zeigt, dass die Bahn an dieser Stelle sachlich falsch liegt, dann meldest du das und
baust sie nicht trotzdem. Eine falsche Bahn ist teurer als eine verlorene Runde.

### 3. Der Pfad von `nachbau.py` bleibt, wo er ist

Der Vorschlag stellt dir frei, das Skript aus `befunde/` herauszuziehen. **Diese Freiheit
nehme ich dir**, und zwar aus einem Grund, der nicht in deinem Paket sichtbar ist: Drei
weitere Abnahmen nennen den Pfad namentlich -- `0108` und `0132` sind offen, `0103` ist
abgenommen. Ein Zeiger am alten Ort ist lesbar, aber nicht ausfuehrbar; die drei wuerden
ins Leere laufen. `befunde/` liegt ohnehin in der Menge `AUSGENOMMEN` des Baulaufs, es
sammelt dort also nichts ein. Verschieben kostet drei Berichtigungen und bringt nichts.

### 4. Die Zahl aus Bedingung 3 ist gestrichen

Sie nannte die Probenzahl je Bauweg als ausgeschriebenen Wert vom 2026-09-05. Im selben
Durchgang legt `0129` eine neue Probe an und `0134` womoeglich eine zweite; die Zahl ist am
Tag deiner Abnahme mit einiger Wahrscheinlichkeit eine andere, und dann faellt eine
richtige Regel an einer veralteten Zaehlung durch. Sie heisst jetzt „gegen den unmittelbar
vorhergehenden Stand desselben Baums und desselben Profils" -- **strenger, nicht
schwaecher**, denn sie verlangt eine Messung statt eines Abgleichs.

**Und die Gegenprobe aus Bedingung 1 ist die tragende:** Ohne den gruenen Lauf am
unveraenderten Baum belegt das Rot nur, dass irgendetwas rot ist.

Aus der Pruefung von Paket 0103 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0103-notfound-endung-verdeckt-schalter-2026-09-05.md`, Befund 2.

**Paket 0103 ist erfuellt.** Was hier steht, liegt ausserhalb seiner Abnahme und
ausserhalb seiner `dateien`-Liste; beide Befunde sind **aelter** als es und an beiden
Staenden gleich gemessen.

Ein Satz fuer beide Haelften: **Die zwei Werkzeuge, mit denen diese Fabrik den
Schlussriegel misst, sind nicht in dem Zustand, in dem man sich auf eine Messung verlassen
kann.** Deshalb ein Paket und nicht zwei -- die Dateien liegen nebeneinander, die Frage ist
dieselbe, und wer das eine anfasst, hat das andere ohnehin offen.

## Erste Haelfte -- `nachbau.py` haengt in keiner automatischen Bahn

Der Schlussriegel hat keinen Regressionstest. Sein eigener Docstring sagt warum: *„im
echten Baum steht nirgends ein `-w`, also wird nichts rot, wenn jemand die Pruefung stumpf
macht."* Der Riegel laeuft zwar bei jeder Konfiguration mit -- aber auf einem Baum, auf dem
nichts falsch ist, kann er nur Fehlalarme zeigen, nie seine eigene Stumpfheit.

`befunde/pruefung-0066/nachbau.py` ist der Ersatz und faehrt 22 Wegwerf-Baeume. Er haengt
in keinem `add_test`, in keinem Ziel und in keinem Baulauf. Er lief am 2026-09-05 nur
deshalb, weil die Abnahmen von 0103 und 0108 ihn **namentlich** nennen. Faellt dieser Satz
einmal aus einer Abnahme heraus, prueft ihn niemand mehr -- und der Riegel, der den
Warnsatz des ganzen Vorhabens haelt, hat dann gar keinen Waechter.

**Der Kostenbeleg, weil er die Entscheidung traegt:** Gemessen am 2026-09-05, Ablage
vorher geloescht, also kalt: **4,5 Sekunden** fuer alle 22 Baeume (`69662e1^`: 4,3 s). Zum
Vergleich die zwei Praezedenzfaelle im selben Baum -- der Belegstellenriegel haengt als
`add_test` in `ctest` (`pruefstand/CMakeLists.txt`, die `add_test`-Zeile in der Schleife
ueber die Proben) und laeuft bei jeder Abnahme mit;
der Mutationslauf tut das ausdruecklich **nicht**, weil ein Fall Uebersetzen, Binden und
einen Probenlauf kostet und ein Katalog auf Minuten waechst (entschieden vom
Projektmanager am 2026-09-05 im Rumpf von 0110, festgehalten im Kopfkommentar von
`CMakeLists.txt` im Absatz *„Der Unterschied zwischen den beiden ist der Aufrufort"*).
4,5 Sekunden liegen auf der billigen Seite dieser Grenze, und die Entscheidung ist damit
schon getroffen -- sie ist nur auf diesen Fall noch nicht angewandt.

## Zweite Haelfte -- `bauwege.py` meldet auf einem fehlerfreien Baum rot

> **Diese Haelfte ist am 2026-09-05 nach `0135-bauwege-sollzahl-gegen-eigenen-stand`
> gegangen.** Der Text bleibt hier stehen, weil er den Befund traegt und weil Hausregel 3
> nichts loescht. Die Arbeit daran gehoert 0135. Fuer dieses Paket ist er Hintergrund.

`befunde/messung-0076/bauwege.py` traegt eine fest eingetragene Sollzahl je Bauweg. Fuer
den Arbeitsbereich erwartet es 18 (Profil `ON`) und 16 (`OFF`); gemessen am 2026-09-05 sind
es **19 und 17**. Folge: `2 Abweichung(en)` und **Exitcode 1** auf einem Baum, an dem
nichts falsch ist.

Ich habe es an zwei Staenden gemessen -- am Arbeitsbaum und an einem vollstaendigen Baum,
in dem allein `werkzeugkette.cmake` auf `69662e1^` zurueckgedreht war. Beide melden
dieselben zwei Abweichungen. Es ist also eine gealterte Zahl im Skript und kein Befund am
Baum; der Baum hat seit dem Eintragen ein uebersetzendes Ziel dazubekommen.

**Warum das mehr ist als ein Schoenheitsfehler.** Die Abnahmebedingung 3 von **0103** und
die von **0108** verlangen beide einen Lauf dieses Skripts. Der Bauagent von 0103 musste
einen Absatz schreiben, warum das Rot nicht seines ist; ich musste beim Pruefen denselben
Absatz noch einmal schreiben; der Bauagent von 0108 und sein Pruefer werden ihn ein drittes
und viertes Mal schreiben. Ein Messwerkzeug, das immer rot meldet, gewoehnt seine Leser
daran, die Zahl zu ueberspringen -- und dann steht der echte Treffer zwischen denen, die
man gewohnt ist zu ueberspringen. Das ist wortwoertlich dieselbe Fehlerklasse, gegen die
die Kette 0076 / 0103 / 0104 / 0108 geschrieben ist: eine Zahl, die etwas anderes
behauptet, als sie misst.

**Die Zahl nicht einfach nachziehen.** 18 → 19 ist in zwei Wochen wieder falsch; der Baum
waechst weiter. Paket **0104** (`offen`) entscheidet gerade, nach welchem Verfahren
kuenftige Abnahmen die Zielzahl ueberhaupt benutzen duerfen, und die Antwort dort ist
bereits „gegen den eigenen Stand davor, nicht gegen einen festen Sollwert". Dieses Paket
soll `bauwege.py` auf genau dieses Verfahren bringen. **Es haengt trotzdem nicht an 0104**:
Die Dateien schneiden sich nicht (0104 haelt `werkzeugkette.cmake`), und die Bedingung
unten ist ohne 0104 erfuellbar. Laeuft 0104 vorher, liest der Bauagent dessen Ergebnis und
folgt ihm.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

`0104` aendert den **Kommentar in `werkzeugkette.cmake`** und nennt `bauwege.py` in seiner
`dateien`-Liste nicht. `0108` aendert `werkzeugkette.cmake`. Kein offenes Paket haelt eine
der drei Dateien dieses Vorschlags -- geprueft am 2026-09-05 ueber die `dateien`-Listen
aller Pakete mit `status: offen` oder `vorschlag`. Dieses Paket schneidet sich damit mit
keinem und kann jederzeit laufen; das ist der Grund, warum `haengt_an` leer ist.

## Was zu tun ist

Die Bauform steht frei. Verlangt sind die drei Bedingungen unten. Zwei Hinweise, die
Arbeit sparen, aber nichts vorschreiben:

- Wohin der Test gehoert, ist eine echte Entscheidung. Er misst den Baum, nicht das
  Erzeugnis, und braucht `python3` und einen Uebersetzer. Der Belegstellenriegel loest
  dieselbe Frage ueber ein eigenes Verzeichnis unter `werkzeuge/`.
- Ob `nachbau.py` dafuer aus `befunde/` herauszieht, entscheidet der Bauagent. Wenn ja,
  bleibt am alten Ort ein Zeiger stehen (Hausregel 3), und die beiden Abnahmen, die den
  Pfad namentlich nennen (0103 ist abgenommen, **0108 ist offen**), muessen ihn weiter
  finden.

**Was nicht dazugehoert:** `werkzeugkette.cmake` anfassen; den Riegel selbst aendern; die
22 Faelle in `nachbau.py` erweitern oder umschreiben; die Meldung des Riegels aendern (das
ist `0132`); `bauwege.py` anfassen (das ist `0135`); `nachbau.py` an einen anderen Ort
verschieben (Vermerk 3 oben); die `CMakeLists.txt` des Vorhabens anfassen (die haelt
`0129`).

## Abnahme

**Berichtigt am 2026-09-05 vom Projektmanager, zusammen mit dem Annahmevermerk oben.**
Zwei Bedingungen statt drei: Die alte Bedingung 2 ist woertlich nach `0135` gegangen, und
die alte Bedingung 3 nennt keine ausgeschriebene Probenzahl mehr. Der Rest steht
unveraendert.

1. **Ein stumpfer Schlussriegel wird ohne Zutun rot.** Nachweis: In einem Wegwerf-Baum
   wird eine Zeile von `fabrik_riegel_sammeln` stumpf gemacht (die Fassung wird nicht
   eingecheckt, sie ist die Messung); der neue automatische Lauf meldet daraufhin einen
   Fehlschlag. Am **unveraenderten** Baum ist derselbe Lauf gruen. Beide Aufrufe und beide
   Ausgaben stehen im Nachweis -- ohne die Gegenprobe belegt das Rot nur, dass irgendetwas
   rot ist.
2. **Kein Urteil aendert sich.** Nachweis: `nachbau.py` meldet unveraendert `0
   Abweichung(en) vom Soll` und die Positivkontrolle `p_positiv` baut rot. Dazu die drei
   Bauwege in **beiden** Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl
   der Proben je Weg steigt gegenueber dem unmittelbar vorhergehenden Stand desselben
   Baums und desselben Profils um die neue und sonst um nichts. Beide Zahlen -- vorher und
   nachher -- sind selbst zu messen und abzudrucken, keine darf uebernommen werden.

   **Zu `bauwege.py`:** Es meldet heute auf einem fehlerfreien Baum Exitcode 1, und das ist
   der Gegenstand von `0135`, nicht deiner. Sein eigener Rueckgabewert ist **kein**
   Kriterium dieses Pakets; was zaehlt, sind die Konfigurations-, Bau- und `ctest`-Codes
   der drei Bauwege. Laeuft `0135` vor dir, ist die Lage ohnehin bereinigt.

**Nachweisort:** dieselbe Staffelung wie in 0066, 0076 und 0103 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/`, sonst ausgewiesene Nichtmessung mit
Begruendung.
