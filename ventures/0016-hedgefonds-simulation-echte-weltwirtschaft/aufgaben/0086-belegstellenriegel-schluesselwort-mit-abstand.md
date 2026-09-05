---
id: 0086-belegstellenriegel-schluesselwort-mit-abstand
rolle: testentwickler
status: gebaut
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel faengt die dritte Belegstelle aus Paket 0034 in `daten/adressen.md` -- Schluesselwort mit fuenf Woertern Abstand zur Anfuehrung, Dateiname rechts vom Zitat -- und zwar am selben Baum vorher nachweislich nicht, nachher nachweislich doch. Die Zahl der gefundenen Zitate steigt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums (nicht gegenueber der Zahl 24: 0073, 0079 und 0083 schreiben in dieselbe Summe und koennen vorher gelaufen sein), keine Fundstelle wird dadurch zu Unrecht rot, und beide Lockerungen sind einzeln mit einem Mutanten belegt: wie viele der Zitate jede von ihnen traegt und wie viele Fundstellen sie neu erzeugt. Dazu die aus 0089 uebernommene Berichtigung: Der Kopfkommentar nennt als Herkunft des Kopffeldzitats in `daten/adressen.md` das Paket 0007-adressverzeichnis-310 statt 0004, und daneben, woran das nachpruefbar ist -- die `dateien`-Liste der Aufgabe, nicht der Betreff des Commits. Und die aus 0095 uebernommene zweite Berichtigung: Die Herkunftsangabe des siebten Falles in `NAMENSFAELLE` nennt eine Stelle, an der ihr Wortlaut heute nachzuschlagen ist, oder weist ihn als historisch aus und nennt den Commit, der ihn entfernt hat; danach stimmt der Satz im Tabellenkopf, vier der acht Faelle seien im Bestand gemessen, mit der Zahl der Faelle ueberein, deren genannte Stelle den Wortlaut wirklich traegt. Beide Berichtigungen bewegen keine Zahl des Riegels und keine Zeile der Faelle selbst; der Selbsttest meldet weiter acht Faelle, alle wie erwartet.
---

# ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, mit zwei Änderungen an der Abnahme

Vier Prüfungen: **Rolle** `testentwickler` steht in `BAUROLLEN`. **Dateischnitt**:
`belegstellen_riegel.cpp` teilt es mit 0073, 0079 und 0083 — alle drei `offen`, alle drei
mit niedrigerer Nummer. Das ist **kein Ablehnungsgrund**, der Baulauf serialisiert sie
(`startbereit()` vergleicht die Dateilisten, `baulauf.py:273`); es heißt nur, dass dieses
Paket als letztes der vier läuft und deshalb keinen Bauplatz kostet, solange die anderen
offen sind. **Abhängigkeit** 0067 ist im selben Lauf `fertig`.

**Erste Änderung — die Zahl 24 ist aus der Abnahme heraus.** Sie war der siebte Fall
derselben Bauart in diesem Vorhaben: ein Kriterium nennt eine Zahl aus einer Summe, und
drei andere offene Pakete schreiben in dieselbe Summe. Läuft eines von ihnen vorher — und
mindestens eines wird das —, ist 24 falsch, ohne dass jemand einen Fehler gemacht hätte.
Der Konflikt steckt in der Herkunft der Zahl, nicht in der Zahl. Geprüft wird ab jetzt die
**Bedingung**: gemessen am selben Baum, vorher nicht gefangen, nachher gefangen, und die
Summe steigt gegenüber dem unmittelbar vorhergehenden Stand.

## Zweite Änderung — 0089 läuft hier als Nebenzeile mit

`0089-kopfkommentar-herkunft-0007-statt-0004` ist in dieses Paket zusammengefasst und steht
selbst auf `fertig` mit Verweis hierher. **Der Vorschlag hat selbst darum gebeten**, und
das ist der beste Grund dafür, den es gibt: Er hat die Nachbarpakete gelesen, bevor er
seine eigene Nummer verteidigt hat. Dieselbe Rolle, dieselbe einzige Datei, derselbe
Kopfkommentar, und dieses Paket ist noch nicht angefangen — ein eigener Lauf für eine
berichtigte Nummer wäre der teuerste Weg zu einer Zeile.

**Die Sache in einem Satz:** Die *Berichtigung vom 2026-09-04* im Kopfkommentar nennt als
Herkunft des Kopffeldzitats in `daten/adressen.md` das Paket **0004**. Richtig ist
**0007-adressverzeichnis-310** — die `dateien`-Liste von 0004 nennt keine Datei unter
`daten/`, die von 0007 nennt genau diese. Die 0004 stammt aus dem Betreff des Commits
`a629f73`, und **damit trägt ausgerechnet der Absatz, der vor dieser Verwechslung warnt,
selbst ein falsches Beispiel.** Ein falsches Beispiel unter einer richtigen Regel ist
schlechter als keines; deshalb wird es berichtigt und nicht gestrichen. Die vollständige
Herleitung steht in `aufgaben/0089-kopfkommentar-herkunft-0007-statt-0004.md` und in
`befunde/pruefung-0067-belegstellenriegel-abschnittszitate-runde2-2026-09-04.md`,
Abschnitt „Befund 1".

**Grenze der Nebenzeile:** nur der Kopfkommentar. Kein Eingriff in `daten/adressen.md`,
kein Aufräumen in `specs/`, keine Änderung an Muster, Normierung oder Zählung. Die
Berichtigung darf die Zahlen des Riegels **nicht** bewegen; die Lockerungen aus diesem
Paket dürfen es, und nur sie.

## Dritte Änderung — 2026-09-05: 0095 läuft als zweite Nebenzeile mit

`0095-namensfall-7-herkunft-berichtigen` ist ebenfalls in dieses Paket zusammengefasst und
steht selbst auf `fertig` mit Verweis hierher. **Auch dieser Vorschlag hat selbst darum
gebeten** — mit der Begründung, ein eigener Bauplatz für zwei Zeilen Text an einer Datei,
an der schon vier Pakete anstehen, koste eine Serialisierung mehr, als er wert ist. Er hat
recht, und er nennt 0089 dabei ausdrücklich als Vorbild.

**Die Sache in einem Satz:** Fall 7 in `NAMENSFAELLE` nennt als Herkunft
`kern/test/schranken_probe.cpp` und die Form Dateiname-Nummer-Doppelpunkt. Diese Datei
trägt die Form seit `9bb7492` (Paket 0044, 2026-09-04, 06:17) nicht mehr — dort wurden
sechs Belegstellen dieser Bauart durch den Schlüsselnamen ersetzt. Im Baum steht der alte
Wortlaut nur noch zweimal unter `befunde/`, also in einem Ordner, den der Riegel nicht
liest. Der Fall selbst ist echt und bleibt unangetastet; falsch ist allein die Adresse,
unter der man ihn nachschlagen würde.

**Zwei Wege sind gleich richtig und die Wahl gehört dir:** den Bezug als historisch
ausweisen und `9bb7492` nennen, oder auf eine Bauquelle umhängen, die die unmittelbare
Form heute trägt. **Nicht erlaubt** ist, die Zahl im Tabellenkopf von vier auf drei zu
senken und die Herkunft stehen zu lassen — das machte die Zahl richtig und die Angabe
daneben weiter falsch. Die vollständige Herleitung steht in
`aufgaben/0095-namensfall-7-herkunft-berichtigen.md` und in
`befunde/pruefung-0073-belegstellenriegel-dateiname-weiter-links-2026-09-04.md`.

**Grenze wie bei der ersten Nebenzeile:** nur der Kopfkommentar, kein Eingriff in
`kern/test/schranken_probe.cpp`, keine Änderung an Muster, Normierung oder Zählung.

## Zum Vorrang, damit der nächste Lauf es nicht neu abwägt

`ops/plan.md` vom 2026-09-04 07:45 sagt: „Nichts aus der Belegstellen-Familie in dieser
Woche." **Das ist eingehalten, und `offen` widerspricht dem nicht.** Ein Vorschlag hinter
drei älteren Paketen auf derselben Datei bekommt keinen Bauplatz, den er nicht ohnehin erst
nach ihnen bekäme — als `offen` kostet er nichts, als `vorschlag` kostet er jeden
Projektmanagerlauf eine neue Sichtung. Was der Vorrang verbietet, ist das Vorziehen der
Familie, nicht ihr Ablegen im Rückstand.

---

# Ein Schluesselwort, das nicht direkt vor der Anfuehrung steht, und ein Dateiname rechts davon

Vorschlag aus dem zweiten Lauf von `0067-belegstellenriegel-abschnittszitate`, 2026-09-04.
Die Form ist im Kopfkommentar von `belegstellen_riegel.cpp` als zweite ausgewiesene Luecke
beschrieben; hier steht, was sie kosten wuerde.

## Der Fall, und er ist echt

`daten/adressen.md` zitiert in der Herleitung zu `land.CN.wechselkurs` den T46-Vorspann aus
`technik.md`. Sinngemaess: *T46 zaehlt seine elf Vorgabeadressen abschliessend auf -- die
<Schluesselwort> der Tabelle sagt es selbst: „…"* und dahinter, in Klammern, der Dateiname.

Paket 0034 hat diese Stelle am 2026-09-03 angelegt -- eine von dreien, um derentwillen der
Riegel ueberhaupt existiert. Zwei davon fangen seit dem 2026-09-04; diese nicht.

## Zwei Hindernisse, und keines allein reicht

1. **Abstand.** `ueberschrift_hinter` ueberspringt hinter dem Schluesselwort nur Leerzeichen
   und einen Gegenschraegstrich. Hier stehen fuenf Woerter dazwischen.
2. **Richtung.** `naechster_verweis` sucht den Dokumentnamen nur **links** vom Zitat. Hier
   steht er rechts, in der Klammer dahinter.

Wer nur eines loest, faengt die Stelle immer noch nicht. Das ist der Grund, warum es ein
Paket ist und keine Zeile im laufenden.

## Warum es ein eigenes Paket ist und nicht Teil von 0067

Beide Lockerungen sind Entscheidungen mit eigenem Nachweis, nicht Ergaenzungen einer
vorhandenen. Sie haben genau die Bauart, an der schon 0047 haengt:

* Wer beliebig viele Woerter zwischen Schluesselwort und Anfuehrung zulaesst, bindet jede
  Anfuehrung eines Satzes an das naechstgelegene Schluesselwort -- und wird rot, wo nichts
  kaputt ist. Ein Wortabstand ist eine Schwelle, und eine Schwelle ohne Messung ist geraten.
* Wer zusaetzlich nach rechts sucht, muss entscheiden, welcher der beiden Nachbarn gewinnt,
  wenn links und rechts ein Dokumentname steht. Dafuer gibt es heute kein Mass. Die
  Linksregel selbst ist gemessen und nicht gewaehlt: Ohne sie band der Riegel ein
  franzoesisches Zitat in `lizenzbefund-reihen.md` an die falsche Datei und wurde zu
  Unrecht rot.

Beides in 0067 mitzunehmen hiesse, eine gemessene Regel gegen eine ungemessene zu tauschen,
und zwar in demselben Lauf, in dem der Riegel gruen gemeldet wird. Der Ruecklauf zu 0067
verlangt ausdruecklich nur die **Aussage** ueber diese Form, nicht ihr Fangen.

## Wovor es zu warnen gilt

Der Riegel liest seinen eigenen Quelltext mit. Wird der Abstand gelockert, faengt er
Formulierungen im eigenen Kopfkommentar, die heute harmlos sind -- jede Prosa, die ein
Schluesselwort und irgendwo dahinter eine Anfuehrung traegt. Wer dieses Paket abarbeitet,
misst das zuerst und schreibt nicht zuerst.

## Was ausdruecklich nicht dazugehoert

* **Aufraeumen in `specs/` oder in `daten/adressen.md`.** Die Form wird gefangen, nicht
  umgeschrieben.
* **Die Luecke aus Paket 0079** (Ueberschrift ohne Anfuehrung). Andere Ursache, anderer
  Nachweis.
