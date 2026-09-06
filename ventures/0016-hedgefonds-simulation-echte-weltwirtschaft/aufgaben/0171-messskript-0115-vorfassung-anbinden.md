---
id: 0171-messskript-0115-vorfassung-anbinden
rolle: testentwickler
status: fertig
abnahme_befund: befunde/pruefung-0171-messskript-0115-vorfassung-anbinden-2026-09-06.md (urteil geprueft, test-pruefer, 2026-09-06)
haengt_an: [0115-riegelkopf-drei-zahlen-nachmessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. 0115 ist seit heute fertig, deine Datei kollidiert mit keinem offenen Paket, und du bist noch heute Nacht eingeplant. Die Abnahme ist vorbildlich geschnitten: Sie nennt den Rotnachweis mit, statt nur Gruen zu verlangen.
abnahme: Nach Loeschen von `$TMPDIR/k0115` endet `python3 befunde/messung-0115/messen.py` ohne Handarbeit mit Rueckgabe 0. Die dabei verwendete Vorfassung ist nachweislich der Elternstand des Baucommits von 0115 (Blob `e3038e2`, Elter von `83faa06`) -- das Skript bindet sie an diese Herkunft, statt zu nehmen, was unter dem Pfad liegt, und eine Vorfassung mit anderem Inhalt macht den Lauf rot statt still anders zu messen. Der Rotnachweis dafuer steht im Paket: ein Lauf mit untergeschobener falscher Vorfassung, abgedruckt mit seiner Meldung.
---

# Das Messskript von 0115 traegt seine Vorfassung nicht bei sich

## Warum ueberhaupt ein Paket

Aus der Pruefung von `0115-riegelkopf-drei-zahlen-nachmessen`, 2026-09-06 (Befund 1
in `befunde/pruefung-0115-riegelkopf-drei-zahlen-nachmessen-2026-09-06.md`).

`messen.py` ist mit Absicht als dauerhafter Riegel gebaut -- die Erwartungen stehen
nicht im Skript, sondern werden aus dem Kommentar gelesen, der sie behauptet. Aber
sein Teil A und seine Gegenprobe haengen an `$TMPDIR/k0115/vorher.cpp`, und diese
Datei erzeugt das Skript nicht, ihre Herkunft steht nirgends, und geprueft wird an
ihr nur `alt != neu`:

1. `$TMPDIR` ist fluechtig. Auf jeder frischen Umgebung bricht der im Paketrumpf
   versprochene "eine Aufruf, der alles laeuft" mit "Die alte Fassung fehlt" ab,
   und der naechste Leser muss selbst darauf kommen, dass dort der Elternstand des
   Baucommits hingehoert.
2. Schwerer: **Der Inhalt ist ungebunden.** Wer eine beliebige aeltere oder fremde
   Fassung unter den Pfad legt, bekommt einen Lauf, der etwas anderes misst --
   Teil A vergleicht dann gegen den falschen Stand, und die Gegenprobe prueft ihre
   Rotfaehigkeit am falschen Wortlaut. Beides ohne eine einzige Meldung. Die
   Beweiskraft des Skripts haengt damit an einer Eingabe, die niemand kontrolliert.

Die Pruefung 0115 hat die Vorfassung deshalb selbst aus git gezogen
(`git show 83faa06^:...`) und den Blob gegen den Diff-Elternstand `e3038e2`
gehalten -- genau diesen Handgriff soll das Skript selbst tun oder erzwingen.

## Warum es kein Teil eines bestehenden Pakets ist

`0110-mutationslauf-als-wiederholbarer-riegel` (und Vorschlag 0127) ersetzt
`kp0086-messen.sh`, den Treiber der Mutationslaeufe -- nicht dieses Skript und nicht
seine Vorher-Nachher-Mechanik. Die Luecke hier ist eine andere: eine ungebundene
Eingabe eines fertigen, abgenommenen Riegels. Haengt man sie an 0110 an, wird sie
dort zur Randnotiz und faellt beim Zuschnitt heraus; ein eigenes Paket ist eine
Stunde Arbeit mit pruefbarer Abnahme.

Der kleinste Weg: `messen.py` zieht die Vorfassung selbst per
`git show <festgeschriebener Stand>:<Pfad>` nach `$TMPDIR` und prueft den Blob;
alternativ liegt sie als Datei neben dem Skript und wird gegen ihren
festgeschriebenen Hash geprueft. Die Wahl trifft der Bauer; die Abnahme verlangt nur
die Eigenschaft.

---

# Ergebnis, 2026-09-06

Gewaehlt ist der erste Weg: Das Skript holt die Vorfassung selbst aus dem
Archiv. Sie liegt damit nicht im Korpus, sondern nur im Zwischenlager -- der
`belegstellen_riegel` liest den Baum, und eine zweite Fassung von 189 kB
Quelltext neben dem Skript waere fuer jeden anderen Riegel eine Aenderung des
Gegenstands.

Festgeschrieben sind in `messen.py` drei Angaben statt einer, und das ist der
Punkt: der Baucommit von 0115 (`83faa06`), der Pfad im Baum und die Blobkennung
`e3038e2` des Elternstandes. Die ersten beiden sagen einem Leser, *was* gemessen
wird; die dritte macht es nachrechenbar, ohne jemandem glauben zu muessen.

## Drei Riegel, in dieser Reihenfolge

1. **Die Herkunftsangabe gegen das Archiv.** `git rev-parse 83faa06^:<Pfad>`
   muss die festgeschriebene Blobkennung nennen. Damit ist auch die Behauptung
   des Paketrumpfs selbst geprueft und nicht nur behauptet.
2. **Was unter dem Pfad liegt, wird nachgerechnet** -- mit der
   Blob-Kennungsformel von git, in Python, ohne `git hash-object`: Die Pruefung
   des Inhalts soll nicht an derselben Stelle haengen wie seine Beschaffung.
   Eine untergeschobene Fassung wird **nicht** ueberschrieben, sondern gemeldet.
   Wer sie hingelegt hat, soll die Meldung lesen und nicht ihr spurloses
   Verschwinden.
3. **Fehlt sie, holt das Skript sie** (`git cat-file blob`) und rechnet das
   Geholte genauso nach.

Der Text wird einmal beschafft und gemerkt; `teil_a` und die Gegenprobe lesen
den Pfad nicht mehr. Was danach unter `$TMPDIR` passiert, aendert nicht mehr,
wogegen gemessen wird.

## Abnahme, Teil 1 -- frisch und ohne Handarbeit

`$TMPDIR/k0115` beiseitegeschoben (Hausregel 3: verschoben nach
`k0115-stand-vor-0171`, nicht geloescht), dann ein Aufruf ohne Vorbereitung:

```
$ python3 befunde/messung-0115/messen.py
Vorfassung: gefehlt und ist geholt worden -- Blob e3038e23316f4c18ca9bdd6cbab51e42579e7838 aus 83faa06^:ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp
Bezugsstand im Kommentar: 5d5e2d6; HEAD zu Beginn: 95fb409
A  vorher : Code 0, 40 Zitate, 40 aufgeloest, 47 uebergangen
A  nachher: Code 0, 40 Zitate, 40 aufgeloest, 47 uebergangen
...
Alle Erwartungen erfuellt.
RC=0
```

Der zweite Aufruf meldet `lag bereit und ist nachgerechnet` und endet ebenfalls
mit 0. Die Zahlen sind dieselben wie vor der Aenderung (Lauf vom selben Tag
gegen HEAD `d8eb90a`): 40/40/47 in Teil A, 51/40/59 unter `ohne-marken-rein`,
je zwei bis drei Meldungen in der Gegenprobe. Die Anbindung verschiebt keine
Messung, sie bindet nur ihre Eingabe.

## Abnahme, Teil 2 -- der Rotnachweis

**Untergeschobene falsche Vorfassung.** Unter den Pfad gelegt wurde der Stand
*nach* der Berichtigung (Blob `14eda9f`, derselbe Baucommit statt seines
Elternstandes) -- also genau die Sorte Datei, die der alten Fassung nicht
aufgefallen waere: Sie prueft nur `alt != neu`, und gegen den heutigen
Arbeitsbaum ist auch dieser Stand ungleich. Der Lauf haette still etwas anderes
gemessen.

```
$ python3 befunde/messung-0115/messen.py
Unter /tmp/claude-1000/k0115/vorher.cpp liegt nicht die Vorfassung von 0115: Der
Inhalt traegt die Blobkennung 14eda9f1abfeafd386a152c63581eb8d892ca26e, erwartet
ist e3038e23316f4c18ca9bdd6cbab51e42579e7838 aus 83faa06^:ventures/0016-hedge...
/werkzeuge/belegstellen/belegstellen_riegel.cpp. Teil A wuerde gegen den falschen
Stand vergleichen und die Gegenprobe ihre Rotfaehigkeit am falschen Wortlaut
pruefen -- beides ohne eine Meldung. Loesche die Datei; das Skript holt die
richtige selbst.
RC=1
```

**Und der erste Riegel einzeln**, weil eine geloeste Herkunft sonst ungeprueft
bliebe: `BAUCOMMIT_0115` versuchsweise auf `e34ab65` gesetzt -- den Commit, der
den Riegel davor zuletzt angefasst hat. Danach zurueckgesetzt und gruen
nachgemessen.

```
$ python3 befunde/messung-0115/messen.py
Der Elternstand des Baucommits von 0115 (e34ab65^:ventures/0016-hedge...
/werkzeuge/belegstellen/belegstellen_riegel.cpp) fuehrt heute den Blob
94f7a8879396506fc755f9ce04cbb651a189b996; festgeschrieben ist
e3038e23316f4c18ca9bdd6cbab51e42579e7838. Die Herkunft der Vorfassung stimmt
nicht mehr -- gemessen wird nichts.
RC=1
```

Beide Riegel schlagen zu, **bevor** eine Zahl erhoben ist. Das ist Absicht: Eine
Messung gegen den falschen Ausgangsstand ist nicht ein bisschen falsch, sondern
gegenstandslos.
