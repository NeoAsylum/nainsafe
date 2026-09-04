---
id: 0083-belegstellenriegel-totes-ziel-statt-uebergangen
rolle: testentwickler
status: vorschlag
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel trennt die heutige Sorte "Ziel ausserhalb des Bestands" in zwei. Nennt ein Zitat eine Datei, die in einem bewusst ungelesenen Ordner liegt (`befunde/`, `aufgaben/`) oder ausserhalb beider Wurzeln, bleibt sie uebergangen wie heute. Nennt es eine Datei, die es unter keiner der beiden Wurzeln gibt, ist das ein Befund und der Lauf rot. Nachgewiesen mit Rotnachweis an einem Zitat auf einen erfundenen Dateinamen und mit Gruennachweis an den fuenf heute uebergangenen Fundstellen, die alle uebergangen bleiben muessen. Zusaetzlich meldet der Riegel die Zahl der aufgeloesten Zitate gegen eine im Quelltext stehende Untergrenze und wird rot, wenn sie unterschritten wird.
---

# Ein Riegel, dessen Abdeckung stillschweigend um die Haelfte fallen kann

Aus der Pruefung von 0067
(`befunde/pruefung-0067-belegstellenriegel-abschnittszitate-2026-09-04.md`, Abschnitt
"Zwei ausgewiesene Luecken, die ich bestaetige"). Dort ist es **kein** Ruecklauf, weil
der Kopfkommentar die Sache ausschreibt. Hier ist es ein Vorschlag, weil die
Ausschreibung an einer Stelle steht, die niemand liest.

## Der gemessene Sachverhalt

Bedingung 2 zaehlt ein Zitat nur dann als "gefunden", wenn seine Zieldatei im Bestand
steht. Faellt die Zieldatei weg -- umbenannt, verschoben, geloescht --, wandert das Zitat
in die dritte Zahl (uebergangen) und der Lauf bleibt gruen.

Gemessen am 2026-09-04 an einer Kopie der Vorgaben ohne `spiel.md`:

```
... 9 Zitate der geprueften Form gefunden, 9 davon aufgeloest, 17 Fundstellen uebergangen.
1/1 Test #1: ... Passed
```

Statt 21 werden 9 geprueft. Zwoelf Zitate sind von einer Sekunde auf die andere
ungeprueft, die beiden Zahlen bleiben gleich, der Test besteht.

## Warum das ein eigenes Paket ist

Drei Gruende, und keiner davon ist "waere auch gut".

1. **Es ist keine Nachbesserung an 0067, sondern eine Entscheidung mit eigenem Preis.**
   Die Sorte "Ziel ausserhalb des Bestands" traegt heute zwei ganz verschiedene Faelle:
   ein Zitat auf einen Pruefbericht unter `befunde/` (richtig uebergangen, denn dieser
   Ordner wird mit Absicht nicht gelesen) und ein Zitat auf eine Datei, die es nirgends
   mehr gibt (ein toter Verweis, also genau der Gegenstand des Riegels). Sie zu trennen
   heisst, eine Regel dafuer zu schreiben, wann ein unauffindbarer Name ein Fehler ist --
   das ist Arbeit mit eigenem Rotnachweis und nicht eine Zeile in einer bestehenden.
2. **Der Zuschnitt von 0067 verbietet es.** Sein Abschnitt "Was ausdruecklich kein Befund
   ist" nennt die ausgewiesene Luecke ausdruecklich als zulaessig. Wer sie im selben
   Paket schliesst, aendert dessen Abnahme.
3. **Es haengt an keinem der offenen Riegelpakete.** 0079 behandelt die Ueberschrift ohne
   Anfuehrung, 0073 den Dateinamen weiter links -- beide auf der **Fund**-Seite. Dieser
   Vorschlag sitzt auf der **Ziel**-Seite und beruehrt die anderen zwei nicht.

