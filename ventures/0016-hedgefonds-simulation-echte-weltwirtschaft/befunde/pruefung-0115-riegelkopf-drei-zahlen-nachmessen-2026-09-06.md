---
typ: pruefung
paket: 0115-riegelkopf-drei-zahlen-nachmessen
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei berichtigten Angaben mit eigener, treiberunabhaengiger Mutation bzw. eigener Tabellenzaehlung nachgemessen; Vorher-Nachher-Gleichheit der Riegelzahlen am selben Baum mit selbst aus git gezogener Vorfassung geprueft; Gegenprobe am alten Wortlaut dreifach rot.
befunde: 1
---

# Pruefung 0115 -- die drei Zahlen im Riegelkopf

Gemessen am 2026-09-06, HEAD `83faa06` (der Baucommit selbst ist der juengste Stand
der Datei). `git status` an `werkzeuge/belegstellen/` war vor und nach jeder Messung
leer; die Binaerdatei unter `bau/` wurde nicht angefasst, alle Bauten liegen in
`$TMPDIR/k0115`.

## Der Diff des Baucommits

`git show 83faa06 -- .../belegstellen_riegel.cpp`: Jede geaenderte Zeile beginnt mit
`//!`, `//` oder `///`. Keine Aenderung an Muster, Normierung, Zaehlung, Schwellen
oder einer Zeile der Falltabellen -- die Ausnahme des Vorschlags ist eingehalten.
Der Commit traegt daneben nur die Paketdatei und das eigene Logbuch des Bauers;
die `dateien`-Liste ist gewahrt.

## Die zuerst geltende Bedingung: keine Zahl des Riegels bewegt

`befunde/messung-0115/messen.py` verlangt die Vorfassung unter
`$TMPDIR/k0115/vorher.cpp` und erzeugt sie nicht (Befund 1). Ich habe sie selbst aus
git gezogen -- `git show 83faa06^:.../belegstellen_riegel.cpp` -- und den Blob
gegengeprueft: `e3038e2`, exakt der Elternstand des Diffs. Damit ist die Herkunft der
"alten Fassung" fuer diesen Lauf gesichert, unabhaengig davon, was der Bauer dort
liegen hatte.

Dann `python3 befunde/messung-0115/messen.py`: Ausgabe endet mit "Alle Erwartungen
erfuellt." (Rueckgabe 0), und Teil A meldet vorher wie nachher **Code 0, 40 Zitate,
40 aufgeloest, 47 uebergangen** -- gemessen im selben Aufruf ueber denselben Baum,
einschliesslich Vergleich der Befundlisten, nicht nur der Summen. Die Quelldatei
stand danach unveraendert (git status leer).

## Angabe 1 -- mit eigener Mutation bestaetigt, nicht mit der des Treibers

Der Treiber `kp0086-mutieren.py` kippt das Argument an der Aufrufstelle
(`klammer_ab(..., true)` -> `false`, Zeile 2241). Meine eigene Ersetzung setzt
stattdessen die Bedingung **in** `klammer_ab` ausser Kraft (Zeile 2121,
`... && !klammer.kuendigt_an && false`), Trefferbremse `count == 1`, Zaehlzeilen
gefiltert, Bau mit denselben Schaltern in `$TMPDIR`:

    basis            : Code 0, (40, 40, 47),  0 Befunde
    eigene Mutation  : Code 1, (51, 40, 59), 11 Befunde
    ohne-marken-rein : Code 1, (51, 40, 59), 11 Befunde   (Treiber)
    nur-abstand      : Code 0, (39, 39, 48),  0 Befunde   (Treiber)
    ohne-marken      : Code 1, (50, 39, 60), 11 Befunde   (Treiber, unrein)

Identische Kippmenge auf zwei Wegen -- die Zahl haengt an der Eigenschaft, nicht an
der Bauart des Treibers. Auch die beiden weiteren Zeilen der Rumpf-Tabelle (39/39/48
und 50/39/60) stimmen.

Die elf Fundstellen meiner Mutation, gegen die Tabellengrenzen des heutigen
Quelltexts gelegt (Kopfkommentar endet Zeile 709; `SATZFAELLE` ab 2536; `ZITATFAELLE`
ab 2893): Zeilen 92 und 309 im Kopf, 2560 in `SATZFAELLE`, 2897/2907/2926/2933/2970/
2984/2991 in `ZITATFAELLE`, dazu `parameter.toml:845`. Das ist exakt die
Aufschluesselung des Kommentars (zwei/eine/sieben, die elfte in `parameter.toml`).
Der Absatz nennt ausserdem selbst, dass die Zahl sich mitzaehlt und ihre Vorgaengerin
genau daran falsch wurde -- die Bedingung "macht aus dem Fehler das Beispiel" ist
erfuellt.

Dass im Kommentar `ohne-marken-rein` statt des in der Abnahme genannten
`ohne-marken` steht, ist keine Absenkung: Die unreine Fassung misst zwei Lockerungen
auf einmal, beide Fassungen sind gemessen und stehen im Rumpf, und beide habe ich
nachvollzogen.

## Angabe 2 -- Summe geht auf, Fall 6 traegt allein

Entschaerfter Mutant `rechts-ohne-satzgrenze-rein`: Code 0, 40/40/47 -- identisch
mit dem unveraenderten Riegel, Zitate plus uebergangene Fundstellen 87 = 87. Scharfer
Mutant: Code 2 mit **genau einer** Meldung, `Selbsttest Abstand 6: rechts erwartet
war kein Dateiname, gefunden wurde spiel.md.` -- kein zweiter Fall reisst. Der
Kommentar sagt beides (Bestand misst die Grenze nicht mehr, Fall 6 traegt sie) und
nennt die richtigen Zahlen.

## Angabe 3 -- an der Tabelle gezaehlt, nicht am Satz geglaubt

Fallanfaenge von `NAMENSFAELLE` (Zeilen 999, 1004, 1011, 1015, 1018, 1021, 1026,
1033): acht Faelle. `**historisch**` steht genau einmal, Zeile 1027, also im
**siebten** Fall. Der Kopf sagt "Der siebte Herkunftshinweis ist historisch", der
Satz davor haelt den achten weiter fuer den abgewandelten, und die Arithmetik des
Kopfes geht auf (drei gemessene + vier Entscheidungen + ein abgewandelter = acht).
Kein Widerspruch mehr.

## Wird die Pruefung rot, wenn man die Sache kaputtmacht?

Die Erwartungen von `messen.py` stehen nicht im Skript, sondern werden aus dem
Kommentar gelesen -- und die mitlaufende Gegenprobe fuehrt dieselben drei Pruefungen
gegen den Wortlaut **vor** der Berichtigung: Angabe 1 drei Meldungen, Angabe 2 zwei,
Angabe 3 zwei. Jede der drei Pruefungen wird an der falschen Fassung rot; eine
stumme haette das Skript selbst als Fehlschlag gemeldet. Teil A meldet ein
Auseinanderlaufen von Zahlen, Rueckgabewert oder Befundlisten als Fehlschlag
(Sichtpruefung des Codes; die Vergleiche sind unbedingt).

Gesucht und nicht gefunden: abgeschwaechte Zusicherungen oder Schwellen im Diff
(keine); ein Filter, der am Repo-Bau wirkt (der Zaehlzeilenfilter greift nur in
Mutantenbauten unter `$TMPDIR`); eine zurueckgelassene Binaerdatei oder ein
veraenderter Baum (git status leer, `bau/` unberuehrt).

## Befund 1 (Nebenbefund, kein Abnahmeverstoss)

`messen.py` bricht ohne `$TMPDIR/k0115/vorher.cpp` ab, erzeugt die Datei nicht,
dokumentiert ihre Herkunft nicht und prueft ihren Inhalt nur auf "ungleich neu".
`$TMPDIR` ist fluechtig: Der "eine Aufruf, der alles laeuft" laeuft auf jeder
frischen Umgebung zuerst gar nicht, und mit einer falschen Vorfassung misst Teil A
wie die Gegenprobe etwas anderes, ohne rot zu werden. Die Abnahme verlangt die
Messung, nicht die dauerhafte Wiederholbarkeit -- deshalb kein `zurueck`; aber die
Beweiskraft des Skripts haengt an einer ungebundenen Eingabe. **Vorschlag `0171`
liegt daneben.**

Der zweite Nebenbefund des Bauers (Schwellenmessung und Vier-Fassungen-Tabelle im
selben Kopf fuehren die Zahlen vom 2026-09-05 weiter) ist bereits durch Vorschlag
`0166` abgedeckt; meine Messung bestaetigt die dortigen Ist-Zahlen fuer
`nur-abstand` (39/39/48) nebenbei.
