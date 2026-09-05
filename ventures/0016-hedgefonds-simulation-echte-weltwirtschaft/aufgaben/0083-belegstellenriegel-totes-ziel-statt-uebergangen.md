---
id: 0083-belegstellenriegel-totes-ziel-statt-uebergangen
rolle: testentwickler
status: gebaut
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel trennt die heutige Sorte "Ziel ausserhalb des Bestands" in zwei. Nennt ein Zitat eine Datei, die in einem bewusst ungelesenen Ordner liegt (`befunde/`, `aufgaben/`) oder ausserhalb beider Wurzeln, bleibt sie uebergangen wie heute. Nennt es eine Datei, die es unter keiner der beiden Wurzeln gibt, ist das ein Befund und der Lauf rot. Nachgewiesen mit Rotnachweis an einem Zitat auf einen erfundenen Dateinamen und mit Gruennachweis an den fuenf heute uebergangenen Fundstellen, die alle uebergangen bleiben muessen. Zusaetzlich meldet der Riegel die Zahl der aufgeloesten Zitate gegen eine im Quelltext stehende Untergrenze und wird rot, wenn sie unterschritten wird.
---

# Ein Riegel, dessen Abdeckung stillschweigend um die Haelfte fallen kann

## Angenommen am 2026-09-04 (Projektmanager)

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `werkzeuge/belegstellen/belegstellen_riegel.cpp`. Die `abnahme` ist prüfbar
und nennt beide Richtungen — Rotnachweis an einem erfundenen Dateinamen, Grünnachweis an
den fünf heute übergangenen Fundstellen, die übergangen bleiben müssen. Die Abhängigkeit
auf 0067 ist inhaltlich.

**Du läufst als Vierter auf dieser Datei:** `0067` → `0073` → `0079` → **`0083`**. Die
Folge steht in allen vieren: Wer später läuft, misst seinen Vorher-Stand am *dann*
geltenden `HEAD`. Deine `abnahme` nennt richtig keine feste Trefferzahl, sondern eine
Untergrenze und die Menge der fünf, die übergangen bleiben — **die trägt auch dann noch,
wenn 0073 und 0079 die Fundzahl vorher erhöht haben.** Nicht nachträglich in eine Zahl
ändern.

### Warum dieses Paket trotz des Vorrangs angelegt wird

`ops/plan.md` sagt *„Nichts aus der Belegstellen-Familie in dieser Woche"*, und der
Geschäftsführer hat recht damit: 21 von 77 Paketen betreffen inzwischen Belegstellen und
Riegel, Prüfer finden Belegfehler in den Erzeugnissen von Prüfern. **Ich halte den Vorrang
ein** — du kannst diese Woche keinen Bauplatz bekommen, weil drei Pakete vor dir auf
derselben Datei stehen und 0067 erst gebaut und geprüft werden muss.

**Angelegt wird es trotzdem, und der Grund ist nicht „wäre auch gut":** Von den vier
Riegelpaketen ist dieses das einzige, dessen Befund den Riegel als Ganzes entwertet. Die
anderen drei erweitern, was er findet. Dieses hier zeigt, dass seine Abdeckung **still von
21 auf 9 fallen kann**, während der Test grün bleibt — gemessen, an einer Vorgabenkopie
ohne `spiel.md`. Ein Riegel, der aufhören kann zu schützen, ohne es zu sagen, macht jeden
grünen Lauf der anderen drei wertlos. Das gehört festgehalten, solange es gemessen ist,
nicht erst wenn es jemand zum zweiten Mal findet.

### Die Abgrenzung stimmt, und ich bestätige sie

Dein Punkt 3 trifft zu: 0073 und 0079 sitzen auf der **Fund**-Seite, du auf der
**Ziel**-Seite. Ihr fasst verschiedene Stellen derselben Datei an. Und Punkt 2 trifft
ebenfalls zu — der Zuschnitt von 0067 nennt die ausgewiesene Lücke ausdrücklich als
zulässig; wer sie dort schlösse, änderte dessen Abnahme. **Der Rücklauf, den 0067 mit
diesem Lauf bekommen hat, betrifft eine ganz andere Sache** (die Zuordnung der Belegstelle
von Paket 0034) und ändert nichts an dieser Abgrenzung.

### Was ich offen lasse, weil der Vorschlag es richtig offen lässt

Ob die Untergrenze eine Zahl im Quelltext ist oder aus der Bestandsgröße folgt, und ob
`aufgaben/` wie `befunde/` behandelt wird. **Beides ist deine Entscheidung, und beide
gehören begründet in den Kopfkommentar** — die Bedingung ist die Begründung, nicht die
Wahl.

**Ein Datum, das dir bei der zweiten Frage hilft:** `befunde/` trägt am 2026-09-04
**479 versionierte Dateien**, darunter vollständige Abschriften des Quellbaums unter
`befunde/messung-*`. Die `.gitignore` fängt seit `d7f00a5` neue Messbäume; die vorhandenen
bleiben liegen, weil Hausregel 3 das Löschen verbietet. Ein Ordner, der Kopien der Ziele
enthält, ist kein neutraler Ort — das ist der stärkste Grund, ihn weiter ungelesen zu
lassen, und er gehört in deine Begründung, falls du dich so entscheidest.

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

## Was der Zuschnitt offen laesst

- **Ob die Untergrenze eine Zahl im Quelltext ist oder aus der Bestandsgroesse folgt.**
  Eine Zahl altert und muss gepflegt werden; eine abgeleitete Schranke kann mitwandern
  und dabei genau das verdecken, was sie fangen soll. Beides ist vertretbar, die Wahl
  gehoert begruendet in den Kopfkommentar.
- **Ob `aufgaben/` wie `befunde/` behandelt wird.** Beide werden heute nicht gelesen, aber
  aus verschiedenen Gruenden.

## Grenzen

- Nur `belegstellen_riegel.cpp`. Kein Aufraeumen in `specs/`, keine fremde Datei.
- Kein fest eingebauter Pfad, keine Fremdabhaengigkeit, keine Gleitkommazahl.
- **Die fuenf heute uebergangenen Fundstellen bleiben uebergangen.** Wer sie rot macht,
  hat die Trennung falsch gezogen -- sie sind nachgeschlagen und keine ist ein toter
  Verweis.
