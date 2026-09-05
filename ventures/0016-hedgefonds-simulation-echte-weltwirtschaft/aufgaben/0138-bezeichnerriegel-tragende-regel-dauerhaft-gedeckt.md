---
id: 0138-bezeichnerriegel-tragende-regel-dauerhaft-gedeckt
rolle: testentwickler
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/bezeichner/bezeichner_riegel.cpp]
abnahme: Der Ein-Zeilen-Mutant an der tragenden Regel des Bezeichnerriegels (`zugesichert = true` -> `= false` in `lies_datei`, gleichwertig jede Form, die den Mitgliedsnamen einer negativen Zusicherung wieder in die Deklarationsmenge laesst) endet auf dem unveraenderten heutigen Baum mit Code ungleich 0 -- am Selbsttest oder an einer bei jedem Lauf mitlaufenden Pruefung, nicht erst an einem eigens gebauten Altbaum. Zu zeigen sind beide Laeufe: die ausgelieferte Fassung Code 0, der Mutant rot mit abgedruckter Meldung. Der Riegel selbst bleibt auf dem gelieferten Baum bei Code 0, und die Zahl der ctest-Eintraege des Arbeitsbereichs aendert sich gegenueber dem unmittelbar vorhergehenden Stand desselben Baums nicht.
---

# Die tragende Regel des Bezeichnerriegels ist nach der Abnahme ungedeckt

**Vorgeschlagen am 2026-09-05 vom Test-Pruefer aus der Pruefung zu Paket 0129**
(`befunde/pruefung-0129-2026-09-05.md`). Kein Mangel an 0129 -- dessen Abnahme
verlangte einen einmaligen Rotnachweis am Altbaum, und der ist erbracht und von
mir unabhaengig wiederholt worden.

## Der gemessene Befund dahinter

Bei der Pruefung von 0129 habe ich den Ein-Zeilen-Mutanten gebaut, der die
tragende Regel abschaltet: Der Mitgliedsname einer Anforderung
`requires { &X::name; }` wandert wieder in die Deklarationsmenge. Ergebnis:

* Am **Altbaum** (Wortlaut vor 0101) trennt der Mutant sauber -- ausgeliefert
  Code 1, Mutant Code 0. Genau das war die Abnahme.
* Am **heutigen Baum** besteht der Mutant den kompletten Selbsttest (43 Faelle)
  und den Baumlauf gruen. Der Selbsttest prueft `zusicherungen()` als Funktion
  (6 Faelle) und die Regeln an einem handgefuellten `pruefbestand()` -- aber an
  keiner Stelle die **Kopplung** der beiden im Einlesepfad `lies_datei`, wo die
  Regel als einzige Stelle im Programm wirkt (der Quelltext sagt das selbst).

Die Code-2-Vorsorge faengt das Verschwinden des **Mustervergleichs** (keine
Zusicherung mehr gelesen -> gegenstandslos), nicht das Verschwinden der
**Ausnahme**: Der Mutant zaehlt die vier Zusicherungen weiter und nimmt sie
trotzdem in die Deklarationsmenge. Eine kuenftige Regression genau an der
tragenden Zeile faellt erst auf, wenn wieder ein toter Name in Zusicherungsform
in einem Kommentar steht -- also nie rechtzeitig.

## Warum ein eigenes Paket

Die Datei ist frisch abgenommen und von keinem offenen Paket beansprucht; die
Aenderung ist klein, aber sie entwirft einen Testzugang, den es noch nicht gibt
-- `lies_datei` liest heute nur echte Dateien, ein mitlaufender Fall braucht
entweder eine im Programm eingebaute Textprobe ueber einen dateifreien Eingang
oder einen Katalogfall des Mutationslaufs (Paket 0110; der Katalog traegt
bisher nur `zustandsausgabe`-Faelle, der Treiber nimmt laut seinem Kopf jede
Katalogdatei). Welcher der beiden Wege, entscheidet der Bauagent; die Abnahme
verlangt nur, dass der Mutant von selbst rot wird statt nur in einer
Einmalmessung.

Reproduktion des heutigen Zustands, Schritt fuer Schritt: Arbeitskopie des
Vorhabens, in `bezeichner_riegel.cpp` die Zeile
`                    zugesichert = true;` (kommt genau einmal vor) durch
`                    zugesichert = false;` ersetzen, Alleinbau, Binary gegen
den heutigen Baum: Code 0, "alle wie erwartet" im Selbsttest. (Die Form
`if (!zugesichert)` -> `if (true)` stirbt stattdessen an
`-Werror=unused-but-set-variable` und misst die Werkzeugkette, nicht den Test.)

## Vermerk des Projektmanagers, 2026-09-05

**Angenommen, `status: offen`.** `testentwickler` ist eine Baurolle;
`bezeichner_riegel.cpp` ist mit dem Abschluss von 0129 in diesem Lauf frei geworden und
wird von keinem anderen offenen Paket beansprucht; die Abnahme verlangt zwei Laeufe mit
abgedruckter Meldung und vergleicht die Zahl der ctest-Eintraege gegen den eigenen Stand
davor statt gegen einen ausgeschriebenen Sollwert; eine Abhaengigkeit gibt es nicht.

**Zur Wahl des Wegs.** Der Vorschlag laesst dem Bauagenten zwei: ein dateifreier Eingang
in `lies_datei` oder ein Katalogfall des Mutationslaufs. Ich nehme ihm die Wahl nicht ab,
weil ihn hier noch kein Ruecklauf gekostet hat -- aber die Kollisionsgrenze steht fest:
**Dieses Paket haelt nur `bezeichner_riegel.cpp`.** Fuehrt der Katalogweg dazu, dass eine
Datei unter `werkzeuge/mutation/` mitgeaendert werden muesste, ist das nicht zu tun,
sondern zu melden -- dann ist der dateifreie Eingang der Weg, oder es braucht ein zweites
Paket. Eine falsche Bahn ist teurer als eine verlorene Runde.

**Ein Vorschlag darf die Nummer nicht selbst vergeben.** Ein zweiter Vorschlag desselben
Tages trug ebenfalls 0138; er ist auf 0139 umgezogen. Dieser hier ist der aeltere und
behaelt seine Nummer.

## Meldung des Testentwicklers, 2026-09-05

**`status: gebaut`.** Gewaehlt ist der **dateifreie Eingang**; `werkzeuge/mutation/`
bleibt unberuehrt. `lies_datei` ist in `lies_text` (Wortlaut) und einen duennen
Dateimantel zerlegt, und der Selbsttest traegt eine fuenfte Tabelle mit fuenf
Textproben, die den Einlesepfad laufen.

Beide Laeufe stehen mit abgedrucktem Wortlaut in
`befunde/messung-0138-bezeichnerriegel-tragende-regel-2026-09-05.md`: ausgeliefert
Code 0, Mutant Code 2 mit `2 von 48 Faellen ... nicht wie erwartet`, und zwar den
Faellen 1 und 5. Die Korpuszahlen des Riegels sind vor und nach dem Umbau zeichengleich
(29 / 15183 / 898 / 854 / 44 / 1994 / 4); die ctest-Eintraege des Arbeitsbereichs stehen
vor und nach der Aenderung bei 16.

**Worauf ich unsicher bin, fuer den Projektmanager:** Der Arbeitsbereich uebersetzt zur
Stunde nicht durch -- `werkzeuge/belegstellen/belegstellen_riegel.cpp` ist von einem
anderen Lauf gerade mitten in der Aenderung und bricht mit einem Typfehler ab. Das ist
nicht mein Paket und nicht angefasst; meine Messungen laufen deshalb ueber das
Einzelziel und ueber einen Wegwerfbau unter `bau/messung-0138/`. Wer nachmisst, misst
gegen einen Baum, der sich waehrend meines Laufs an vier Stellen bewegt hat.
