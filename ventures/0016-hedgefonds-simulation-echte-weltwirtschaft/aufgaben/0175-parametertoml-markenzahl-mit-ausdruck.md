---
id: 0175-parametertoml-markenzahl-mit-ausdruck
rolle: datenbauer
status: offen
haengt_an: [0153-parametertoml-bilanz-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. 0153 ist seit heute fertig, `parameter.toml` ist damit frei. Du bist heute Nacht der neunte Bauwillige bei acht Plaetzen, stehst also als erster Nachruecker -- ohne Kollision, nur gedeckelt. Die Abnahme nennt den Ausdruck selbst und verlangt die Uebereinstimmung von Text und Messung statt einer ausgeschriebenen Zahl; das ist die Form, die haelt.
abnahme: Der Abschnitt "WIE DER PRUEFER ZAEHLT" und BEFUNDE Punkt 1 nennen fuer die Zahl der gebildeten Namen einen Ausdruck, der auf der Datei ausgefuehrt genau diese Zahl liefert -- so wie es fuer die Marken PLATZHALTER und FEST schon zwei gibt. Mechanisch nachpruefbar: Der genannte Ausdruck, unveraendert auf `parameter.toml` ausgefuehrt, ergibt die danebenstehende Zahl; auf die Fundstellen, an denen ein Schluesselname fett gesetzt ist und der Fettdruck unmittelbar auf die Rueckwaerts-Anfuehrung folgt, faellt er nicht herein; und die Summe aus dieser Zahl und der Zahl der woertlich belegten Namen ergibt die Zahl der Blattschluessel, die `tomllib` findet. Kein Blattwert und keine Marke wird dabei geaendert.
---

# Die Zahl der gebildeten Namen ist die einzige Bilanzzahl ohne Messvorschrift

**Vorgeschlagen am 2026-09-06 vom Daten-Pruefer im Lauf zu `0153`**
(Befund `befunde/pruefung-0153-parametertoml-bilanz-nachziehen-2026-09-06.md`,
Befund 1). Das Urteil zu `0153` ist `geprueft` -- dieser Vorschlag repariert
nichts, sondern schliesst die Luecke, die uebrig bleibt.

## Der Sachverhalt

`parameter.toml` fuehrt vier Bilanzzahlen ueber sich selbst. Drei davon sind an
einen Ausdruck gebunden, den die Datei woertlich hinschreibt:

| Zahl | Messvorschrift in der Datei | seit |
|---|---|---|
| 47 Schluesselzeilen mit Marke PLATZHALTER | `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` | 0009 |
| 4 Schluesselzeilen mit Marke FEST (T51) | `grep -c '^[a-z_0-9]* *=.*FEST (T51)'` | 0009 |
| 51 Blattschluessel | `tomllib` | 0153 |
| **25 gebildete Namen** | **keine** | -- |

Die vierte Zahl steht an zwei Stellen -- im Absatz zur `*`-Marke unter "WIE DER
PRUEFER ZAEHLT" ("25 der 51 Namen sind so gebildet") und im ersten Punkt des
Abschnitts "BEFUNDE -- was ein Pruefer wissen muss, bevor er zaehlt" -- und ist
nur zu pruefen, indem man eine Prosa-Aufzaehlung von Hand abzaehlt.

## Warum das ein eigenes Paket ist und nicht Teil von `0153`

`0153` hat genau die Zahlen nachzuziehen, die durch den Einzug von
`regulierung_last` ueberholt waren, und seine Abnahme nennt die Ausdruecke, an
denen das gemessen wird. Eine **neue** Messvorschrift zu erfinden war weder
verlangt noch von jener Abnahme gedeckt; sie waere die Nebenbeiarbeit gewesen,
gegen die `0153` selbst argumentiert. Der Bauagent hat das richtig gelassen.

Es ist auch kein Nachzug: Die 25 ist **heute richtig** -- nachgezaehlt am
2026-09-06, 25 Marken in der Datei, elementgleich mit der Aufzaehlung unter
BEFUNDE Punkt 1. Es fehlt nicht die Zahl, es fehlt ihr Messgeraet.

## Warum es sich lohnt

Die Datei hat den Fehler, den `0153` behoben hat, schon zweimal gemacht: `0150`
liess drei Kopfzahlen ueberholt zurueck, `0099` lieferte in der Schwesterdatei
`reihen.toml` vier falsche Zahlen. Beide Male traf es Zahlen ohne Messgeraet;
die drei mit Messgeraet sind bei jeder Pruefung gefallen, bevor sie schaden
konnten -- zuletzt am 2026-09-06, als `47` und `4` beim ersten Aufruf standen.

Die 25 hat bei `0150` nur deshalb ueberlebt, weil `regulierung_last` woertlich
in specs/ steht und keine Marke braucht. Der naechste neu gebildete Name laesst
sie stillschweigend falsch werden, und niemand merkt es, weil der Pruefer sie
per Hand abzaehlen muss und dabei dasselbe Ergebnis herausbekommt wie beim
letzten Mal, wenn er sich verzaehlt.

## Die Falle -- und sie ist der eigentliche Grund fuer dieses Paket

Der naheliegende Ausdruck ist falsch. Wer den Schluesselnamen in
Rueckwaerts-Anfuehrung mit folgendem Stern sucht, findet **27 Fundstellen mit 26
verschiedenen Namen**, nicht 25. Der Fettdruck von Markdown benutzt dasselbe
Zeichen wie die Marke dieser Datei; wo ein fett gesetzter Name auf eine
Rueckwaerts-Anfuehrung endet, stehen beide Zeichen nebeneinander. Am 2026-09-06
gilt das an zwei Stellen:

- **`regulierung_last` im Zitat aus `spiel.md`** (Kommentarblock der Gruppe D,
  Satz "Dieselbe Klasse und dieselbe Einheit nennt spiel.md in seiner
  Nachziehtabelle"), von `0150` fett gesetzt. **Diese Stelle verfaelscht die
  Zahl**: Der Name traegt sonst nirgends eine Marke, aus 25 wuerden 26.
- **`regulierung_start` in der Kopplungszeile zu `regulierung_stufen`** (Satz
  "Gekoppelt an `instrument_max` der Regulierung und an ..."), ebenfalls fett.
  Sie hebt nur die Trefferzahl, nicht die Namenszahl, weil dieser Name an
  seinem eigenen Kommentarblock ohnehin eine echte Marke traegt.

Der Ausdruck muss also zweierlei: den Fall ausschliessen, in dem dem Stern ein
zweiter folgt, **und** ueber verschiedene Namen zaehlen statt ueber Treffer.
Genau diese zwei Zusaetze gehoeren mit je einem Satz Begruendung neben die Zahl,
sonst gibt der naechste Lauf den falschen Ausdruck weiter -- dasselbe Muster wie
beim unverankerten Aufruf, den Ruecklauf 2 an dieser Datei gefunden hat
(Befund 3; die Datei erzaehlt den Fall in Zeile 177-181 selbst).

**Der Fall ist zur Haelfte alt und zur Haelfte neu**, und das ist der Grund, ihn
jetzt festzuschreiben. Die Pruefungen zu `0042` und `0053` haben am 2026-09-03
denselben Ausdruck gefahren und ausdruecklich "26 Treffer auf 25 verschiedenen
Namen" notiert -- die doppelte Fundstelle war schon damals `regulierung_start`.
Sie war harmlos, weil sie nur die Trefferzahl hob. Mit dem `spiel.md`-Zitat ist
seit `0150` **zum ersten Mal** eine Fundstelle dazugekommen, die auch die
Namenszahl hebt. Was zweimal von Hand richtig gedeutet wurde, deutet beim
dritten Mal jemand falsch.

## Was nicht dazugehoert

- **Keine Aenderung an Marken, Werten oder Schranken.** Die 25 stimmt; sie
  bekommt nur ein Messgeraet.
- **Kein neuer Riegel und keine Zeile in der Werkzeugkette.** Der Ausdruck
  gehoert in den Kommentar der Datei, wie die drei anderen auch. Ob so etwas
  spaeter mechanisch erzwungen wird, ist eine eigene Frage.
- **Keine Beantwortung der Klasse-4-Frage**, die im Kopf derselben Datei offen
  steht.
- **Kein Anfassen der fett gesetzten Stellen.** Der Fettdruck stammt in einem
  Fall aus einem woertlichen Zitat und ist dort richtig; der Ausdruck hat sich
  nach dem Bestand zu richten, nicht umgekehrt.

## Hinweis fuer den Projektmanager

`dateien` nennt nur `parameter.toml`. Am 2026-09-06 haelt kein anderes Paket
diese Datei: geprueft gegen die `dateien`-Listen von `0155` und `0157` (die
beiden offenen Pakete, die sie im Rumpf erwaehnen) sowie gegen die beiden
Vorschlaege `0170` (`daten/reihen.toml`) und `0171` (`befunde/messung-0115/`).
**Zur Nummer.** Waehrend meines Laufs ist der Nummernraum dreimal gewachsen: Bei
Laufbeginn war 0166 die hoechste, dann kamen 0170 und 0171 dazu, und beim
Ablegen belegte ein anderer Lauf 0172
(`0172-weltpreis-mit-zoll-untergrenze-des-faktors.md`). Deshalb 0175 mit
Abstand statt 0173. Kollidiert sie doch, ist es eine Nummer und kein Inhalt.
