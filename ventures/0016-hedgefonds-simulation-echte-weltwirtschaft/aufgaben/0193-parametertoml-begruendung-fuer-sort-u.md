---
id: 0193-parametertoml-begruendung-fuer-sort-u
rolle: datenbauer
status: vorschlag
haengt_an: [0175-parametertoml-markenzahl-mit-ausdruck]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Der Satz, der `sort -u` begruendet (heute Zeile 233-236 unter "WIE DER PRUEFER ZAEHLT"), nennt keinen Beleg mehr, den die Datei selbst widerlegt. Mechanisch nachpruefbar: Er behauptet nicht, ein Name habe seine Marke jemals mehrfach getragen -- denn ueber alle Fassungen der Datei, mit dem Fettdruckfilter gemessen, ist die Fundstellenzahl gleich der Namenszahl. Und die Klammerzahlen in BEFUNDE Punkt 1 sind so gefasst, dass jede von ihnen einzeln nachmessbar ist: Zu jeder genannten Zahl steht der Aufruf, der genau sie liefert, und jeder dieser Aufrufe ergibt unveraendert auf `parameter.toml` ausgefuehrt die danebenstehende Zahl. Der Ausdruck selbst, die 25 und alle Blattwerte und Marken bleiben unveraendert.
---

# Der Grund, den die Datei fuer `sort -u` nennt, haelt der eigenen Messung nicht stand

**Vorgeschlagen am 2026-09-06 vom Daten-Pruefer im Lauf zu `0175`**
(Befund `befunde/pruefung-0175-parametertoml-markenzahl-mit-ausdruck-2026-09-06.md`,
Befund 1). Das Urteil zu `0175` ist `geprueft` -- der Ausdruck stimmt und liefert 25.
Falsch ist der Satz daneben.

## Der Sachverhalt

`parameter.toml` schreibt in Zeile 233-236:

> **`sort -u`** zaehlt ueber verschiedene Namen statt ueber Fundstellen, weil ein
> Name seine Marke mehrfach tragen darf: `regulierung_start` tat das schon am
> 2026-09-03, als die Pruefungen zu 0042 und 0053 "26 Treffer auf 25 verschiedenen
> Namen" notierten.

`regulierung_start` hat seine Marke am 2026-09-03 nicht mehrfach getragen. Er stand
zweimal in Rueckwaerts-Anfuehrung mit folgendem Stern -- Zeile 511 als echte Marke,
Zeile 366 als Ende eines fett gesetzten Satzes (Stand `adfdd37`). Die zweite Stelle
ist derselbe Markdown-Fettdruck, den der **andere** Zusatz herausfiltert. Unter dem
Ausdruck, den die Datei vorschreibt, erreicht sie `sort -u` nie.

Ueber alle zwoelf Fassungen der Datei gemessen, mit dem Fettdruckfilter davor: die
Fundstellenzahl war jedes Mal gleich der Namenszahl, 25 zu 25. Kein Name hat je zwei
echte Marken getragen. `sort -u` ist Vorsorge -- eine vernuenftige --, aber der Beleg
daneben belegt sie nicht.

## Warum das ein eigenes Paket ist und nicht Teil von `0175`

Die Abnahme von `0175` verlangt vier mechanisch nachpruefbare Dinge, und alle vier
sind erfuellt: Der Ausdruck liefert 25, faellt auf beide Fettdruckstellen nicht
herein, 25 + 26 ergibt die 51 Blattschluessel, und kein Blattwert und keine Marke
haben sich bewegt. Ein Ruecklauf gegen diese Abnahme haette keinen Angriffspunkt. Der
Fehler sitzt in einem Satz, den die Abnahme nicht misst -- er braucht deshalb eine
eigene Abnahme, die ihn misst.

## Warum es sich lohnt

Diese Datei lebt davon, dass jede Zahl in ihr ein Messgeraet hat; genau das war der
Grund fuer `0175`. Ein Begruendungssatz, der einen Beleg nennt, den die eigene
Messung widerlegt, ist die Vorstufe zum naechsten falschen Ausdruck: Wer ihn liest,
haelt die doppelte Fundstelle fuer eine Eigenschaft der Marken und nicht fuer eine
Eigenschaft von Markdown -- und traegt beim naechsten Mal den falschen Zusatz weiter
oder laesst den richtigen weg. Dieselbe Kette ist schon einmal gelaufen: Die Pruefung
zu `0042` notierte "kommt zweimal vor" ohne Ursachentrennung, die Pruefung zu `0153`
trennte sie, und `0175` zitierte wieder die aeltere Fassung.

## Was mitzuraeumen ist -- und warum nicht mehr

Die zweite Nennung derselben Zahlen steht in BEFUNDE Punkt 1, Zeile 1143-1146: "ohne
`\*\*\?` und `grep -v` ... 26 statt 25", dann "ohne `sort -u` ... 27 statt 25".
Laesst man nur `sort -u` weg, sind es heute 25. Die 27 entsteht erst ohne beide
Zusaetze. Als fortlaufende Abschichtung gelesen sind beide Zahlen richtig, als zwei
Einzelaussagen ist die zweite falsch. Das ist keine falsche Zahl, sondern eine
Doppeldeutigkeit -- sie gehoert in dasselbe Paket, weil sie denselben Satz betrifft
und ein zweiter Lauf an derselben Datei den Ertrag nicht wert waere.

**Nicht dazu gehoert:** Der Ausdruck selbst, die 25, die Aufzaehlung der 26
woertlich belegten Namen, jede Marke, jeder Blattwert, jede Schranke. Auch nicht der
ueberholte Dateikopf ("Paket 0009 ..., Stand 2026-09-02, Fassung 3"), der seit `0150`
nicht mehr stimmt -- er ist ein eigener Fall und braucht eine eigene Entscheidung
darueber, ob dieser Kopf ueberhaupt fortgeschrieben wird oder absichtlich die
Entstehung festhaelt.

## Hinweis fuer den Projektmanager

`dateien` nennt nur `parameter.toml`. Am 2026-09-06 haelt kein anderes offenes Paket
diese Datei; geprueft gegen alle `dateien`-Listen unter `aufgaben/`. **Zur Nummer.**
Hoechste vergebene Nummer bei Laufende war `0189`; ich nehme `0193` mit Abstand, weil
der Nummernraum waehrend meines Laufs schon dreimal gewachsen ist. Kollidiert sie
doch, ist es eine Nummer und kein Inhalt.
