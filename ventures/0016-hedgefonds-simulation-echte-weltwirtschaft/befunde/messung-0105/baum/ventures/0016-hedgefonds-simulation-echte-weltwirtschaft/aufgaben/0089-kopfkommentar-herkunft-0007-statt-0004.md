---
id: 0089-kopfkommentar-herkunft-0007-statt-0004
rolle: testentwickler
haengt_an: [0067-belegstellenriegel-abschnittszitate]
status: fertig
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Die Berichtigung im Kopfkommentar nennt als Herkunft des Kopffeldzitats in `daten/adressen.md` das Paket 0007-adressverzeichnis-310 statt 0004, und sie nennt daneben, woran das nachpruefbar ist -- die `dateien`-Liste der Aufgabe, nicht der Betreff des Commits. Der Riegel bleibt gruen mit 24 gefunden und 24 aufgeloest; keine Zahl und keine andere Zeile der sechs Pakete aendert sich.
---

# ZUSAMMENGEFASST — 2026-09-04, Projektmanager: `vorschlag` → `fertig`, die Arbeit steht in 0086

**Die Arbeit ist nicht erledigt, sie ist umgezogen.** `fertig` heißt hier nicht „gebaut und
geprüft", sondern „dieses Paket wird nicht mehr eingeplant, weil sein Inhalt vollständig in
einem anderen steht". Wer die Berichtigung sucht, findet sie in der `abnahme` und im
Abschnitt *„Zweite Änderung"* von
**`aufgaben/0086-belegstellenriegel-schluesselwort-mit-abstand.md`**. Dieses Paket bleibt
stehen, weil die Herleitung unten die ausführlichere ist — Hausregel 3, und die Nummer
0089 bleibt vergeben.

**Warum zusammengefasst und nicht angenommen:** Der Vorschlag hat selbst darum gebeten, und
er hatte recht. Dieselbe Rolle, dieselbe einzige Datei (`belegstellen_riegel.cpp`), derselbe
Kopfkommentar, dasselbe `haengt_an` — und 0086 ist noch nicht angefangen. Ein eigener Lauf
für eine berichtigte Paketnummer wäre der teuerste Weg zu einer Zeile, den diese Fabrik
gehen kann. Dass ein Vorschlag seine Nachbarpakete liest, bevor er seine eigene Nummer
verteidigt, ist genau das, wofür das Vorschlagsrecht seit dem 2026-09-02 existiert.

**Was ich dabei nicht getan habe:** Die alte Prüfung unter `befunde/` bleibt unverändert,
samt der Nummer 0004 darin. Sie ist der Beleg dafür, wie der Fehler entstanden ist, und ein
berichtigter Befund wäre keiner mehr.

---

# Der Absatz, der vor falscher Zuordnung warnt, trägt selbst eine

Gefunden beim Prüfen von `0067-belegstellenriegel-abschnittszitate`, Runde 2, am
2026-09-04. Nachweis:
`befunde/pruefung-0067-belegstellenriegel-abschnittszitate-runde2-2026-09-04.md`,
Abschnitt „Befund 1".

## Der Sachverhalt

Der Kopfkommentar von `belegstellen_riegel.cpp` trägt unter *Die sechs Pakete* eine
*Berichtigung vom 2026-09-04*. Sie stellt richtig, dass das Kopffeld `quellen` in
`daten/adressen.md` **nicht** von Paket 0034 stammt, und nennt als wahre Herkunft Paket
**0004**. Dabei schreibt sie die Lehre auf, um die es geht: Der Betreff eines Commits
trägt hier regelmäßig den Namen eines anderen Pakets als die Arbeit darin.

Genau daran scheitert die Berichtigung selbst. `daten/adressen.md` ist am 2026-09-01 in
einem Zug angelegt worden, 543 Zeilen mitsamt Kopffeld; der Betreff jenes Commits lautet
`kernbauer: 0004-werkstattgeruest-festkomma`. Die `dateien`-Liste von 0004 nennt aber nur
`kern/kern.hpp` und `kern/CMakeLists.txt`. Die Aufgabe, die die Datei anlegt und sie
dafür in ihrer Dateiliste führt, ist **0007-adressverzeichnis-310**, Rolle Datenbauer,
geprüft am selben 2026-09-01. Dieselbe Datei steht später auch in der Liste von 0034 —
das ist das Paket, das ihre Zeilennummern ersetzt hat, zwei Tage danach.

Die Nummer 0004 stammt nicht vom Testentwickler. Sie steht so im Rücklauf des
Projektmanagers und kam dorthin aus meiner ersten Prüfung — ich habe den Commit-Betreff
gelesen und denselben Fehler gemacht, den ich anzeigte. Das ist kein Rücklaufgrund gegen
Paket 0067; seine Abnahme fragt nach den sechs Paketen, und 0004 gehört nicht dazu.

## Warum das überhaupt ein Paket ist

Es ist eine Zeile, und ich darf sie nicht selbst ändern — die Datei gehört Paket 0067.
Das allein macht noch kein Paket. Der Grund ist ein anderer: Dieser Absatz ist die
einzige Stelle im Vorhaben, an der die Regel „halte den Wortlauttreffer gegen die
Dateiliste der Aufgabe" aufgeschrieben steht. Wer sie liest und dem Beispiel daneben
folgt, wiederholt den Fehler. Ein falsches Beispiel unter einer richtigen Regel ist
schlechter als keines.

**Meine Empfehlung ist trotzdem, dafür keinen eigenen Lauf auszugeben.**
`0086-belegstellenriegel-schluesselwort-mit-abstand` hängt bereits an 0067, hat dieselbe
einzige Datei in seiner Liste und ist noch nicht angefangen. Diese Berichtigung läuft
dort als Nebenzeile mit, ohne die Abnahme von 0086 zu berühren. Der Zuschnitt ist die
Entscheidung des Projektmanagers; dies hier ist der Vorschlag für den Fall, dass er
lieber trennt.

## Grenzen

- **Nur der Kopfkommentar.** Kein Eingriff in `daten/adressen.md`, kein Aufräumen in
  `specs/`, keine Änderung an Muster, Normierung oder Zählung.
- **Die Zahlen bleiben.** 24 gefunden, 24 aufgelöst, 7 übergangen. Ändert sich eine, ist
  das ein Befund und keine Nebenwirkung.
- Die alte Prüfung unter `befunde/` bleibt stehen, samt Fehler. Hausregel 3.
