---
id: 0097-zustandsausgabe-probe-zuordnungen-festnageln
rolle: testentwickler
status: vorschlag
haengt_an: [0010-zustandsausgabe-drei-ebenen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustandsausgabe_probe.cpp]
abnahme: Erstens -- jeder der dreizehn Klassennamen, jede der dreizehn Einheiten und jeder der fuenf Herkunftsnamen kommt im Wortlaut in mindestens einer Zusicherung vor, geprueft am erzeugten Blatt gegen eine Adresse, die die Klasse beziehungsweise die Herkunft wirklich traegt (fuer die Klasse 13, die keine Zustandsadresse hat, gegen `klasseneinheit` unmittelbar). Zweitens -- jede Spalte der Uebersicht wird gegen einen Wert geprueft, den im geprueften Zustand keine andere von der Uebersicht gelesene Adresse traegt; dazu gehoert eine zweite, absichtlich halb gerechnete Belegung, in der `land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` verschieden sind, und die Zusicherung, dass die Uebersicht den Instrumentenstand zeigt. Drittens der Nachweis -- die siebzehn in `befunde/pruefung-0010-zustandsausgabe-drei-ebenen-2026-09-04.md` aufgezaehlten Mutationen werden einzeln gefahren und sind danach alle rot, waehrend die unveraenderte Probe gruen bleibt.
---

# Die Probe prueft, dass eine Zahl dasteht, nicht dass die richtige dasteht

## Was gemessen ist

Fuenfzig Mutationen an den drei Dateien von Paket 0010, je Mutation eine Textersetzung,
uebersetzen, `zustandsausgabe_probe` fahren. **Zwanzig ueberleben, siebzehn davon zu
Unrecht** -- und keine einzige davon macht eine Zahl falsch. Alle siebzehn machen
dasselbe: Sie haengen eine richtige Zahl an die falsche Beschriftung oder eine falsche
Einheit an eine richtige Zahl. Die Aufzaehlung mit Ergebnis je Mutation steht im Befund.

Der teuerste Fall in drei Zeilen: In `KLASSENEINHEIT` den zweiten Eintrag
(`"Tausend USD zu konstanten Preisen 2015"`) durch `"Stueck bzw. Runden"` ersetzen --
uebersetzt, Probe bestanden. Danach schreibt die Detailebene fuer **71 der 310
Adressen**, ihre Zahl sei ein Stueckzaehler statt eines Betrags in Tausend USD. Das ist
Klasse 2, die groesste ueberhaupt: jede Wertschoepfung, jeder Kapitalstock, jeder
Handelsstrom, der Marktkorb.

## Warum die vorhandenen Riegel das nicht fangen

Sie sind stark und sie zielen woanders hin, und beides ist wichtig:

- Die `static_assert`-Kette im Kopf des Moduls zaehlt **Adressen** ab -- zwoelf
  Klassenzahlen aus T49 und fuenf Herkunftszahlen aus T45, jede einzeln, dazu beide
  Summen. Sie faengt jede verschobene Zuordnung (`M36`, `M37` scheitern beim
  Uebersetzen). Sie sieht Zeichenketten nicht und kann sie nicht sehen.
- Die laufende Probe nagelt drei der dreizehn Klassen fest (K1, K4, K6, ueber je eine
  vollstaendig zitierte Zeile) und eine der fuenf Herkunftsarten (`Vorgabe`). Die
  uebrigen zehn und vier kommen in keiner Zusicherung im Wortlaut vor.

Dazwischen liegt eine Luecke, die keiner der beiden gehoert: die Abbildung von der
abgezaehlten Klasse auf ihren Namen und ihre Einheit.

## Der zweite Grund, und er ist der unangenehmere

Die Grundbelegung `belege_tragfaehig` macht richtige und falsche Quelle an mehreren
Stellen ununterscheidbar. Zwei Beispiele, beide gemessen:

- **`M20`.** Die Belegung setzt `Aggregat::Leitzins` auf 250 **und**
  `instrument.leitzins.stand` auf 250. Der Kommentar in `src/zustandsausgabe.cpp`
  (Zeile 154 bis 158) begruendet ausfuehrlich, warum die Uebersicht den Instrumentenstand
  liest und nicht das Aggregat -- "der Stand entsteht in Schritt 3, das Aggregat
  uebernimmt ihn in Schritt 4", wer das Aggregat laese, saehe in einer halb gerechneten
  Runde die Zahl der Vorrunde. Keine Probe kann diese Entscheidung heute unterscheiden,
  weil beide Adressen dieselbe Zahl tragen.
- **`N02`.** Alle fuenf Gebiete haben BIP 3.000.000. Die Uebersicht darf fuer jedes
  Gebiet das der USA lesen, ohne dass etwas rot wird.

**Zum Leitzins gehoert deshalb ein zweiter Zustand und nicht ein veraenderter erster.**
T49 nennt `land.<L>.leitzins = land.<L>.instrument.leitzins.stand` als Gleichheit; eine
Grundbelegung, die sie bricht, waere ein ungueltiger Zustand und wuerde spaeteren
Invariantentests im Weg stehen. Der Fall, den der Kommentar beschreibt, ist gerade der
halb gerechnete: Genau dafuer gehoert eine zweite, ausdruecklich so benannte Belegung
daneben. Die Musterlage steht schon in der Probe -- der Abschnitt 7 baut sich fuer die
Gegenprobe zum Fondsvermoegen bereits einen zweiten, absichtlich kaputten Zustand.

## Warum das ein eigenes Paket ist und kein Ruecklauf gegen 0010

**Weil 0010 seine Abnahme erfuellt.** Der gebaute Code ist richtig: Ich habe jede Zeile
von `uebersicht` gegen ihre Adresse gehalten, alle vier Instrumente stehen da und lesen
ihr eigenes Feld, und alle dreizehn Einheiten stimmen wortgleich mit der Tabelle aus T5.
Was fehlt, ist nicht die Leistung, sondern der Riegel, der sie haelt. Ein Ruecklauf
gegen ein Paket, das liefert, was sein Kriterium verlangt, waere die nachtraegliche
Erweiterung dieses Kriteriums.

**Weil es eine andere Rolle ist.** Was hier entsteht, sind Zusicherungen und eine zweite
Belegung, kein Modul. Das ist Arbeit des Testentwicklers, nicht des Kernbauers, und sie
faellt in genau einer Datei an.

**Und weil die Luecke sonst genau jetzt zugeht.** Sobald 0010 auf `fertig` steht, sieht
"die drei Zustandsebenen sind gebaut und geprueft" vollstaendig aus. Diese Ebenen sind
nach dem Arbeitspaket das, "worueber diese Fabrik ihr eigenes Erzeugnis ueberhaupt
kennt" -- Selbstspieler, Rueckvergleicher und jeder Pruefer lesen nichts anderes. Eine
Ausgabe, die eine richtige Zahl mit einer falschen Einheit beschriftet, ist fuer diese
Leser schlimmer als eine, die schweigt.

## Fuer den Projektmanager

Die `dateien`-Liste dieses Vorschlags schneidet sich mit der von
`0098-diff-kennungen-ohne-differenz` aus demselben Pruefbericht: Beide fassen
`kern/test/zustandsausgabe_probe.cpp` an. Sie sind trotzdem getrennt, weil 0098 eine
Entscheidung zwischen zwei Dokumenten braucht und dieser Vorschlag keine. Wird 0098
verworfen, bleibt dieser hier unveraendert gueltig.
