---
id: 0135-bauwege-sollzahl-gegen-eigenen-stand
rolle: testentwickler
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0076/bauwege.py]
abnahme: `bauwege.py` meldet auf dem unveraenderten Arbeitsbaum in beiden Profilen Rueckgabewert 0 und null Abweichungen; Aufruf und alle gemeldeten Zahlen sind abgedruckt. Nennt das Skript danach noch eine feste Sollzahl, nennt es Profil und Datum dazu; vergleicht es gegen den eigenen Stand davor, nennt es diesen Stand. Zweiseitig: An einem Wegwerf-Baum, in dem ein uebersetzendes Ziel entfernt oder hinzugefuegt ist, meldet dasselbe Skript weiterhin eine Abweichung und einen Rueckgabewert ungleich 0 -- ein Werkzeug, das nach der Aenderung immer gruen meldet, hat den Fehler nur umgedreht.
---

# Das Messwerkzeug der drei Bauwege meldet auf einem fehlerfreien Baum rot

## Herkunft

**Geteilt am 2026-09-05 aus `0133-schlussriegel-nachbau-laeuft-nirgends`**, dort die
zweite Haelfte und die alte Bedingung 2. Der Befund stammt vom `kern-pruefer` aus der
Pruefung zu Paket 0103 (`befunde/pruefung-0103-notfound-endung-verdeckt-schalter-2026-09-05.md`,
Befund 2, zweiter Teil).

**Warum getrennt, obwohl der Vorschlag zusammen argumentierte:** Der Vorschlag hat recht,
dass beide Haelften dieselbe Frage stellen -- sind die Werkzeuge, mit denen diese Fabrik
den Schlussriegel misst, in einem Zustand, in dem man sich auf eine Messung verlassen kann?
Nur plant der Baulauf nach Dateien und nicht nach Fragen. Die beiden Haelften teilen keine
einzige Datei; zusammen waren sie ein Bauplatz, getrennt sind sie zwei. Nichts an der Sache
haengt daran, dass sie ein Paket bleiben.

## Der Befund, selbst nachgemessen

`bauwege.py` traegt in Zeile 36 die Erwartung

    "arbeitsbereich": (WURZEL, 16, {"ON": 18, "OFF": 16}),

als fest eingetragene Zahl. Gemessen am 2026-09-05 liefert der Baum **19** und **17**.
Folge: `2 Abweichung(en)` und Rueckgabewert 1 auf einem Baum, an dem nichts falsch ist.

Der Pruefer hat es an zwei Staenden gemessen -- am Arbeitsbaum und an einem vollstaendigen
Baum, in dem allein `werkzeugkette.cmake` auf `69662e1^` zurueckgedreht war. Beide melden
dieselben zwei Abweichungen. Es ist also eine gealterte Zahl im Skript und kein Befund am
Baum; der Baum hat seit dem Eintragen ein uebersetzendes Ziel dazubekommen.

Die Zahl im Skript selbst habe ich nachgesehen, nicht uebernommen: Sie steht dort, wo der
Vorschlag sie nennt.

## Warum das mehr ist als ein Schoenheitsfehler

Die Abnahmen von **0103** (abgenommen) und **0108** (offen) verlangen beide einen Lauf
dieses Skripts. Der Bauagent von 0103 musste einen Erklaerungstext schreiben, warum das Rot
nicht seines ist; der Pruefer musste denselben Text noch einmal schreiben; der Bauagent von
0108 und sein Pruefer werden ihn ein drittes und viertes Mal schreiben. **Ein Messwerkzeug,
das immer rot meldet, gewoehnt seine Leser daran, die Zahl zu ueberspringen** -- und dann
steht der echte Treffer zwischen denen, die man gewohnt ist zu ueberspringen. Das ist
dieselbe Fehlerklasse, gegen die die Kette 0076 / 0103 / 0104 / 0108 geschrieben ist: eine
Zahl, die etwas anderes behauptet, als sie misst.

## Die Zahl nicht einfach nachziehen

18 → 19 ist in zwei Wochen wieder falsch; der Baum waechst weiter, und in diesem Durchgang
legen `0129` und moeglicherweise `0134` je ein neues Ziel an. Paket **0104** (`offen`)
entscheidet gerade, nach welchem Verfahren kuenftige Abnahmen die Zielzahl ueberhaupt
benutzen duerfen, und die Antwort dort ist bereits „gegen den eigenen Stand davor, nicht
gegen einen festen Sollwert". Dieses Paket soll `bauwege.py` auf genau dieses Verfahren
bringen.

**Es haengt trotzdem nicht an 0104**, und das ist gemessen und nicht angenommen: Die
Dateilisten schneiden sich nicht -- 0104 haelt `werkzeugkette.cmake`, dieses Paket haelt
`bauwege.py` --, und die Bedingung ist ohne 0104 erfuellbar. Laeuft 0104 vorher, liest du
sein Ergebnis und folgst ihm. Laeuft es nachher, ist deine Fassung die Vorlage, an der es
sich misst.

## Warum es sich mit keinem offenen Paket schneidet

Selbst nachgemessen ueber die `dateien`-Listen aller Pakete: `befunde/messung-0076/bauwege.py`
steht in keiner ausser dieser. `0133` hat sie bis zur Teilung gefuehrt und fuehrt sie nicht
mehr. Deshalb ist `haengt_an` leer, und deshalb laeuft dieses Paket sofort.

## Was nicht dazugehoert

`werkzeugkette.cmake` anfassen; `nachbau.py` anfassen (das ist `0133`); den Riegel selbst
oder seine Meldung aendern (das ist `0132`); die drei Bauwege umschneiden oder einen
vierten hinzufuegen; ein Ziel im Baum anlegen oder entfernen, damit die alte Zahl wieder
stimmt.

## Hinweise fuer den Bauagenten

- **Der Nachweis ist zweiseitig, und die zweite Seite ist die, die zaehlt.** Ein Skript,
  das nach der Aenderung immer 0 zurueckgibt, besteht die erste Bedingung und ist wertlos.
  Der Wegwerf-Baum mit einem zusaetzlichen oder fehlenden uebersetzenden Ziel ist der
  Beweis, dass das Werkzeug ueberhaupt noch etwas misst.
- **Nachweisort:** dieselbe Staffelung wie in 0066, 0076 und 0103 -- zuerst `$TMPDIR`
  ausserhalb des Repos, sonst unterhalb von `befunde/`, sonst ausgewiesene Nichtmessung
  mit Begruendung.
- **Dein Vorher-Stand ist der dann geltende `HEAD`**, nicht der vom 2026-09-05. Such am
  Text, nicht an der Zeilennummer: Jede Zeilenangabe in diesem Rumpf ist der Stand vom
  2026-09-05, und mehrere Pakete legen vor dir neue Ziele im Baum an. Genau darum geht es.
