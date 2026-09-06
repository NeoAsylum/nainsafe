---
typ: pruefung
paket: 0171-messskript-0115-vorfassung-anbinden
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Frischlauf, beide Rotnachweise und die Herkunftsbindung mit eigenen Mutanten nachgemessen; das heutige Rot des Frischlaufs als Korpusdrift isoliert (alte Skriptfassung liefert dieselben Fehlschlaege).
befunde: 1
---

# Pruefung 0171 -- messen.py bindet seine Vorfassung an die Herkunft

## Herkunftsangaben, unabhaengig nachgerechnet

`git rev-parse 83faa06^:ventures/.../werkzeuge/belegstellen/belegstellen_riegel.cpp`
liefert `e3038e23316f4c18ca9bdd6cbab51e42579e7838`; `83faa06` ist der Baucommit von
0115 (`testentwickler: 0115-riegelkopf-drei-zahlen-nachmessen`), der Stand danach
traegt `14eda9f`. Beide Behauptungen des Pakets stimmen mit dem Archiv ueberein.

## Frischlauf ohne Handarbeit (Abnahme Teil 1)

`$TMPDIR/k0115` beiseitegeschoben (nach `k0115-stand-vor-pruefung-0171`), ein
Aufruf: erste Zeile `Vorfassung: gefehlt und ist geholt worden -- Blob e3038e2...
aus 83faa06^:...`, danach laeuft die komplette Messung ohne Handgriff. Zweiter
Aufruf mit liegender Datei: `lag bereit und ist nachgerechnet`. Der Bindungsteil
der Abnahme ist erfuellt; zum Rueckgabewert siehe Befund 1.

## Rotnachweis mit eigener Mutante (Abnahme Teil 2)

Nicht die Mutante des Bauers (`14eda9f`), sondern die haertere: die korrekte
Vorfassung mit **genau einem gekippten Byte** in einer Kommentarzeile -- gleiche
Laenge, Blob `57ef059dd430be47d86c640b2c971c552ed3c711`. Genau diese Sorte Datei
haette die alte Pruefung (`alt != neu`) nie bemerkt.

- **Neue Fassung:** Rueckgabe 1 **vor der ersten Zahl**; die Meldung nennt beide
  Blobkennungen und die Herkunft. Die untergeschobene Datei liegt danach
  **unveraendert** da (Blob nachgerechnet: weiterhin `57ef059...`) -- nicht
  ueberschrieben, wie zugesagt.
- **Alte Fassung** (`591fdc5^`, in Arbeitskopie unter `bau/pruefung-0171/`
  ausgefuehrt) am **selben** Mutanten: laeuft die komplette Messung stumm durch,
  kein Wort zur Vorfassung. Luecke und Schliessung in einem Laeufepaar belegt.

## Riegel 1 einzeln, eigene Mutation

`BAUCOMMIT_0115` in einer Kopie auf `591fdc5` gesetzt (eigene Wahl statt des
`e34ab65` aus dem Nachweis des Bauers): Rueckgabe 1 bei **leerem stdout** -- der
Abbruch kommt vor jeder Messung, die Meldung nennt `14eda9f` gegen `e3038e2`.

## Uebriges

- Memoisierung („was danach unter dem Pfad passiert, aendert nichts mehr"): per
  Codelektuere -- `_vorfassung` wird beim ersten Aufruf gesetzt, `teil_a` und
  `gegenprobe` lesen den Pfad nicht mehr.
- Dateiliste: Baucommit `591fdc5` traegt `messen.py`, den Ergebnisteil des
  Pakets und das eigene Logbuch -- `dateien` eingehalten.
- Der Diff schwaecht nichts ab: entfallen ist nur der blosse Existenz-Check,
  ersetzt durch drei schaerfere Riegel; beide `lies(VORHER)` durch `vorfassung()`.
- `belegstellen_riegel.cpp` ist nach allen Laeufen unveraendert (git status leer).

## Befund 1 (kein Mangel dieses Pakets): Der Frischlauf endet heute mit Rueckgabe 1 -- Korpusdrift, nicht 0171

Die Abnahme verlangt Rueckgabe 0. Heute kommen 6 Fehlschlaege, alle aus einer
Familie: Die Kopfzahlen des Riegels (47 uebergangene Fundstellen, 59 unter der
Mutation, Summe 87 -- erhoben gegen Stand `5d5e2d6`) stehen gegen heute gemessene
55/67/95. Dazu wanderte HEAD waehrend der Messung (die Fabrik committet laufend),
was das Skript selbst als Fehlschlag meldet.

Drei Belege, dass das Rot nicht aus dem Paket stammt:

1. Die **alte Skriptfassung liefert am heutigen Korpus die identische
   Fehlschlagmenge** -- dieselben 6, im direkten Nebeneinanderlauf.
2. Am Baustand (`95fb409`) stimmen die Zahlen des Bauers (40/40/47, Gegenprobe
   3/2/2) mit meiner **eigenen unabhaengigen Messung aus der Pruefung 0115 vom
   Vortag** ueberein -- das Kriterium war am Messstand erfuellt, das ist
   trianguliert, nicht geglaubt.
3. Seit `95fb409`: 42 geaenderte Dateien, +6.219 Zeilen im Venture, darunter
   `belegstellen_riegel.cpp` selbst +252 (neue Falltabellen, u. a.
   `URTEILSFAELLE`). Die uebergangenen Fundstellen wuchsen um 8 -- genau die
   Groesse, die reisst. Die relativen Pruefungen (Summenerhalt, Mutant bewegt
   den Bestand nicht) hielten auch heute.

**Folge fuer den Projektmanager:** „Rueckgabe 0" ist an diesem Riegel nur in
einem Zeitfenster erfuellbar -- solange die Kopfzahlen frisch sind. Das ist eine
gewollte Eigenschaft des Pruefgegenstands von 0115 (veraltete Zahlen sollen
sichtbar reissen), kein Mangel der Anbindung. Aber solange niemand nacherhebt,
muss jede kuenftige Pruefung, die `messen.py` als Beleg nutzt, dieses Rot erst
als Drift entschluesseln. Nacherheben ist ein eigenes Paket: **Vorschlag 0189**
(Kopfzahlen im Riegel nachziehen; `BEZUGSSTAND` in `messen.py` muss mitziehen,
sonst reisst dessen Standpruefung).

## Wonach ich sonst gesucht und nichts gefunden habe

Ueberschreiben der untergeschobenen Datei (bleibt liegen), stiller Weiterlauf
bei falscher Herkunft (bricht vor der Messung ab), eine Vorfassung gleicher
Laenge mit anderem Inhalt (faellt am Blob), Abschwaechung bestehender
Erwartungen durch den Diff (keine gesenkt, keine entfernt).
