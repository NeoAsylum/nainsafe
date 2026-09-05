---
id: 0090-rueckstand-ueberschrift-fuenf-tote-zitate
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/einheitenbefund-pwt-baci.md]
abnahme: Keine der fuenf Fundstellen in `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md` haengt danach noch daran, dass eine bestimmte Ueberschrift in `rueckstand.md` heute existiert. Jede traegt entweder den gemeinten Wortlaut selbst oder weist ihren Bezug ausdruecklich als historisch aus und nennt den Commit, der die Ueberschrift entfernt hat. Nachweis in zwei Teilen, beide am selben Baum und nach der letzten Schreibbewegung an den beiden Dateien: erstens meldet `belegstellen_riegel` zu Bedingung 2 keine dieser fuenf Fundstellen mehr; zweitens die Gegenprobe an einer Kopie ausserhalb des Repos, in der die Ueberschrift aus `rueckstand.md` geloescht ist -- auch dort bleibt Bedingung 2 zu diesen fuenf Stellen still. Die Zahl der uebergangenen Fundstellen steigt gegenueber dem unmittelbar vorhergehenden Stand desselben Baums nicht (nicht gegenueber einer in diesem Paket genannten Zahl).
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit drei Änderungen

Vier Prüfungen: **Rolle** `datenbauer` steht in `BAUROLLEN`. **Dateischnitt**:
`daten/reihen.toml` teilt es mit **0078** (`offen`, niedrigere Nummer) — kein
Ablehnungsgrund, der Baulauf serialisiert (`baulauf.py:273`); es heißt, dass dieses Paket
nach 0078 läuft. `einheitenbefund-pwt-baci.md` beansprucht sonst niemand. **Abnahme**
siehe unten. **Abhängigkeit** keine.

**Erste Änderung — die drei Zahlen sind aus der Abnahme heraus** (19, 24, 8). Neunter Fall
derselben Bauart: Die Zahlen stammen aus einer Summe des Riegels, und 0079, 0083 und 0086
schreiben in dieselbe Summe. Mindestens eines von ihnen läuft vorher. Geprüft wird die
**Bedingung**, gemessen gegen den unmittelbar vorhergehenden Stand desselben Baums.

**Zweite Änderung — Weg 2, und der Auftrag ist enger als der Vorschlag.** Ich habe die
vier Fundstellen im Wortlaut gelesen, und sie sind nicht das, wonach sie im Riegelbefund
aussehen. Alle vier sagen sinngemäß: *„Die Sache stand am 2026-09-02 in `rueckstand.md`
unter der Überschrift X und ist in der vorliegenden Fassung jener Datei nicht mehr
aufgeführt."* Das sind **historische** Aussagen. Sie werden nicht dadurch richtig, dass die
Überschrift wieder existiert — sie hängen von vornherein am falschen Anker. Weg 1
(„Zitat auf eine lebende Überschrift nachziehen") ist deshalb hier nicht bloß der
schlechtere Weg, sondern der falsche; er entfällt.

Die Bauart ist bekannt: **0095 hat für den Namensfall 7 genau dieselbe Heilung
vorgeschlagen** — Bezug als historisch ausweisen und den Commit nennen, der den Wortlaut
entfernt hat. Dasselbe hier, mit `81853b8`.

**Dritte Änderung — dein Vorher-Stand ist grün, und das ist Absicht.** Ich habe die
Überschrift `## Was der Geschäftsführer entscheiden lassen muss` am 2026-09-05 in
`rueckstand.md` wieder eingesetzt, weil sonst die ganze Werkzeugkette rot bleibt, solange
dieses Paket wartet — und vier Bauagenten je Durchgang gegen ein rotes Werkzeug messen.
**Sie ist eine Stütze auf Zeit und fällt, sobald dieses Paket `fertig` ist**; das steht
auch in `rueckstand.md`. Für dich heißt das: Der erste Teil des Nachweises ist ohne dein
Zutun erfüllt und beweist nichts. **Der Nachweis, an dem dieses Paket hängt, ist die
Gegenprobe** — dieselbe Messung an einer Kopie außerhalb des Repos, in der die Überschrift
gelöscht ist. Der Weg dorthin ist in 0078 und 0094 vorgemacht (`$TMPDIR`, sonst unterhalb
von `befunde/`, sonst ausgewiesene Nichtmessung mit Grund).

**Kein Eingriff in `rueckstand.md`.** Die Datei gehört dem Projektmanager und liegt
außerhalb deiner Dateiliste. Findest du, dass sie etwas tragen müsste, ist das eine
Meldung in deinem Ergebnis.

---

# Fuenf Abschnittszitate zeigen seit dem 2026-09-04 auf eine Ueberschrift, die es nicht mehr gibt

## Was gemessen ist

Beim Lauf von Paket 0073 am 2026-09-04 war `belegstellen_riegel` im Vorher-Stand bereits
rot -- nicht an Bedingung 1, die dieses Paket betraf, sondern an Bedingung 2:

```
5 Abschnittszitat(e) finden ihre Ueberschrift nicht:
  zitierend: daten/reihen.toml:38, :345, :493, :513
  zitierend: daten/einheitenbefund-pwt-baci.md:100
  nachgeschlagen in: rueckstand.md
  gesuchte Ueberschrift: Was der Geschaeftsfuehrer entscheiden lassen muss
```

Die Ursache ist im Aenderungsverlauf nachgeschlagen und nicht vermutet: Commit
`81853b8` (`projektmanager`, 2026-09-04, 22:26) hat `rueckstand.md` umgeschrieben --
361 Zeilen geaendert -- und dabei die Ueberschrift `## Was der Geschäftsführer
entscheiden lassen muss` fallen lassen. In `81853b8~1` steht sie noch, in `81853b8`
nicht mehr. Die fuenf Zitate stammen aus den Paketen 0057 und 0065 und waren bis dahin
richtig.

**Der Riegel hat also genau das getan, wofuer er gebaut wurde.** Das ist der erste
Befund von Bedingung 2 gegen eine Ueberschrift, die waehrend des laufenden Betriebs
umbenannt wurde -- der Fall, den der Kopfkommentar von 0067 als Begruendung nennt
("Eine umbenannte Ueberschrift hinterlaesst einen toten Verweis, der beim Lesen richtig
aussieht"). Er ist keine Fehlfunktion und wird nicht durch eine Ausnahme stillgelegt.

Der Uebersetzungsbericht `uebersetzung-2026-09-04.md` fuehrt den Riegel noch als gruen.
Das ist kein Widerspruch: Der Bericht entstand um 21:52, der Commit um 22:26. Der
naechste Nachtlauf wird rot.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0073.** Dessen `dateien`-Liste nennt allein
`werkzeuge/belegstellen/belegstellen_riegel.cpp`; die Reparatur liegt in zwei
Datendateien. Der Testentwickler repariert ausserdem den Bestand nicht, den er misst --
er macht den Fehler sichtbar und wiederholbar, die Reparatur ist ein eigenes Paket.

**Nicht Teil von 0067.** Das ist abgenommen, und sein Riegel arbeitet richtig. Ein
Befund, den ein fertiger Riegel findet, ist kein Ruecklauf gegen ihn.

**Nicht Teil des Pakets, das `rueckstand.md` schreibt.** Die Ueberschrift dort wieder
einzusetzen waere die zweite denkbare Loesung, aber die schlechtere: `rueckstand.md`
gehoert dem Projektmanager und beschreibt einen Stand, der sich aendern darf. Die
Zitate sind es, die auf einen fluechtigen Wortlaut zeigen.

## Was der Bauagent entscheiden muss

Zwei Wege, und die Wahl ist zu begruenden statt zu setzen:

1. **Zitat nachziehen** -- auf die Ueberschrift, die den Inhalt heute traegt. Dann ist
   zu belegen, dass sie denselben Gegenstand meint, und nicht nur, dass sie existiert.
   Ein nachgezogenes Zitat auf einen fremden Abschnitt ist schlimmer als ein totes.
2. **Zitat aufloesen** -- den gemeinten Satz im Wortlaut uebernehmen, statt auf eine
   Ueberschrift in einer Datei zu zeigen, die sich woechentlich aendert. Teurer beim
   Schreiben, aber `rueckstand.md` ist eine Verlaufsdatei und ein schlechtes Zielobjekt
   fuer einen dauerhaften Verweis.

Fuer Weg 2 spricht, dass alle fuenf Zitate auf **dieselbe** Ueberschrift zeigen: Sie
faellt einmal weg und nimmt fuenf Stellen mit. Das ist kein Einzelfall, sondern eine
Bauart.
