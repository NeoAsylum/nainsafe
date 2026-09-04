---
id: 0079-belegstellenriegel-zitat-ohne-anfuehrung
rolle: testentwickler
status: vorschlag
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel entscheidet je Fundstelle zwischen einer Abschnittsnummer und einer Ueberschrift ohne Anfuehrung und begruendet die Entscheidung im Kopfkommentar an einer benannten Eigenschaft, nicht an einer Liste. Nachgewiesen an den vier Stellen aus `reihen.toml`, die Paket 0047 hinterlassen hat: die zwei Nummern werden uebergangen und gezaehlt, die zwei Ueberschriften werden nachgeschlagen und aufgeloest -- je mit Rotnachweis fuer die zweite Gruppe. Er bleibt auf dem dann geltenden Korpus gruen, und die Zahl der uebergangenen Fundstellen faellt gegenueber dem Stand von 0067 um genau zwei.
---

# Die Ueberschrift ohne Anfuehrung -- die Form, an der 0067 aufhoert

## Warum das ein eigenes Paket ist

Paket 0067 faengt fuenf der sechs Pakete, um derentwillen der Riegel existiert. Das
sechste ist 0047, und es faellt an einer Sache durch, die keine Nachbesserung ist,
sondern eine Entscheidung mit eigenem Nachweis.

0047 hat seine Ueberschriften **ohne jede Anfuehrung** zitiert. `daten/reihen.toml`
traegt dadurch viermal die Form `<datei>, Abschnitt <Name>`, wo der Name unmittelbar im
Satz weiterlaeuft:

```
daten/lizenzbefund-reihen.md, Abschnitt 5
daten/lizenzbefund-reihen.md, Abschnitt 3
lizenzbefund-reihen.md, Abschnitt Reihe 1
lizenzbefund-reihen.md, Abschnitt 2b und 2c
```

**Zwei davon sind Nummern, zwei sind Namen, und beide sehen gleich aus.** Genau daran
haengt die Arbeit: Ohne Anfuehrung ist nicht bestimmt, wo der Name aufhoert, und ohne
Ende ist nicht bestimmt, ob eine Nummer oder eine Ueberschrift gemeint ist. Ein Riegel,
der bis zum naechsten Satzzeichen liest und alles nachschlaegt, wird rot an "Abschnitt 5"
-- wo nichts kaputt ist. Ein Riegel, der bei Zweifel uebergeht, prueft an dieser Form
wieder nichts.

Das in 0067 mitzuerledigen haette geheissen, die Entscheidung nebenbei zu treffen und
ihren Nachweis in eine Abnahme zu haengen, die vier andere Bedingungen traegt. Der
Zuschnitt von 0067 nennt das Muster ausdruecklich als meine Entscheidung und die
ausgewiesene Luecke ausdruecklich als zulaessig -- sie steht im Kopfkommentar des Riegels
und in `befunde/messung-0067/nachweis.md`. Dies ist die Fortsetzung, nicht ihre
Berichtigung.

## Warum nicht einfach die vier Stellen in Anfuehrung setzen

Weil `daten/reihen.toml` fremdes Gebiet ist -- sie stand nicht in der Dateiliste von 0067
und steht nicht in der dieses Vorschlags. Und weil es der falsche Weg waere: Der Riegel
soll die Form fangen, die dasteht, nicht die Form vorschreiben, die er schon kann. Wer
die Datei umschreibt, damit der Riegel gruen wird, hat den Riegel geprueft und nicht die
Datei.

## Ein Weg, der nicht vorgeschrieben ist

Nicht die Gestalt des Namens entscheiden lassen, sondern den **Bestand**: Ein Name, der
sich als Ueberschrift der Zieldatei wiederfindet, ist eine Ueberschrift; einer, der aus
Ziffern und hoechstens einem Buchstaben besteht, ist eine Nummer; alles dazwischen ist
eine uebergangene Fundstelle mit Namen. Das hat einen Haken, und er gehoert in den
Nachweis: Eine Ueberschrift, die **gerade umbenannt wurde**, findet sich nicht wieder und
saehe damit aus wie der dritte Fall -- also genau der Fehler, gegen den der Riegel
geschrieben ist. Wer diesen Weg geht, braucht dafuer eine Antwort; wer einen anderen
Weg findet, braucht sie nicht.

## Was ausdruecklich kein Befund ist

- **Dass 0067 diese Form nicht faengt.** Sie ist dort ausgewiesen, mit Grund. Eine
  ausgewiesene Luecke ist kein Rueckstand, sondern der Anfang dieses Pakets.
- **Die vier uebrigen uebergangenen Fundstellen aus 0067.** Sie tragen ihr Ziel nicht bei
  sich (Selbstverweis, Netzadresse, Rust-Manifestgruppe) und sind eine andere Sache.

## Grenzen

- **Nur `belegstellen_riegel.cpp`.** Dieselbe Datei wie 0067 und 0073, deshalb haengt
  dieser Vorschlag hinter 0067. Ob er vor oder hinter 0073 laeuft, ist gleichgueltig --
  beide fassen verschiedene Stellen an --, aber gleichzeitig geht nicht.
- **Kein Aufraeumen in `daten/` und keins in `specs/`.**
- Keine Gleitkommazahl, keine Fremdabhaengigkeit, kein fest eingebauter Pfad.
