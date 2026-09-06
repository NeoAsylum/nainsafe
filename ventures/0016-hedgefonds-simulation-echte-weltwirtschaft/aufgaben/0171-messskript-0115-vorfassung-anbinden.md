---
id: 0171-messskript-0115-vorfassung-anbinden
rolle: testentwickler
status: offen
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
