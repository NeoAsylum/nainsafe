---
id: 0133-schlussriegel-nachbau-laeuft-nirgends
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/pruefung-0066/nachbau.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0076/bauwege.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Der einzige Regressionsnachweis des Schlussriegels ruft niemand, und daneben steht einer, der immer rot meldet

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
`add_test` in `ctest` (`pruefstand/CMakeLists.txt:90`) und laeuft bei jeder Abnahme mit;
der Mutationslauf tut das ausdruecklich **nicht**, weil ein Fall Uebersetzen, Binden und
einen Probenlauf kostet und ein Katalog auf Minuten waechst (entschieden vom
Projektmanager am 2026-09-05 im Rumpf von 0110, festgehalten im Kopfkommentar von
`CMakeLists.txt` im Absatz *„Der Unterschied zwischen den beiden ist der Aufrufort"*).
4,5 Sekunden liegen auf der billigen Seite dieser Grenze, und die Entscheidung ist damit
schon getroffen -- sie ist nur auf diesen Fall noch nicht angewandt.

## Zweite Haelfte -- `bauwege.py` meldet auf einem fehlerfreien Baum rot

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
ist `0132`).

## Abnahme

1. **Ein stumpfer Schlussriegel wird ohne Zutun rot.** Nachweis: In einem Wegwerf-Baum
   wird eine Zeile von `fabrik_riegel_sammeln` stumpf gemacht (die Fassung wird nicht
   eingecheckt, sie ist die Messung); der neue automatische Lauf meldet daraufhin einen
   Fehlschlag. Am **unveraenderten** Baum ist derselbe Lauf gruen. Beide Aufrufe und beide
   Ausgaben stehen im Nachweis -- ohne die Gegenprobe belegt das Rot nur, dass irgendetwas
   rot ist.
2. **`bauwege.py` meldet auf dem unveraenderten Arbeitsbaum Exitcode 0** und null
   Abweichungen, in **beiden** Profilen. Nachweis: der Aufruf und die sechs gemeldeten
   Zahlen abgedruckt. Nennt das Skript danach noch eine Sollzahl, nennt es Profil und
   Datum dazu; vergleicht es gegen den eigenen Stand davor, nennt es den Stand.
3. **Kein Urteil aendert sich.** Nachweis: `nachbau.py` meldet unveraendert `0
   Abweichung(en) vom Soll` und die Positivkontrolle `p_positiv` baut rot. Dazu die drei
   Bauwege in beiden Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl der
   Proben je Weg (14 / 10 / 3 am 2026-09-05) steigt um die neue und sonst um nichts.

**Nachweisort:** dieselbe Staffelung wie in 0066, 0076 und 0103 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/`, sonst ausgewiesene Nichtmessung mit
Begruendung.
