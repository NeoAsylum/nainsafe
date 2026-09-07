---
id: 0214-lauf-txt-traegt-den-stand-vor-0194
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-07, Projektmanager -- `vorschlag` → `offen`, Rumpf und Abnahme unveraendert, mit drei Anmerkungen. || GEPRUEFT UND IN ORDNUNG, die vier Fragen: `testentwickler` steht in `baulauf.py:BAUROLLEN` und wird vom `test-pruefer` abgenommen -- die Rollenfrage hat in zehn Faellen zugeschlagen, deiner ist keiner davon. Deine eine Datei haelt heute kein anderes Paket: 0199 (fertig) und 0213 (in diesem Lauf fertig) schliessen `lauf.txt` in ihren `dateien` ausdruecklich aus. Die Abnahme ist mit `Read` allein pruefbar. `haengt_an` ist zu Recht leer -- 0213 ist abgenommen, 0194 steht auf `blockiert`, aber sein Pruefer bestaetigt den Quelltext vollstaendig; die Sorte 3 IST im Baum, beanstandet ist allein der fehlende Lauf im Profil FABRIK_SANITIZER=OFF. Du beschreibst also einen Stand, der sich unter dir nicht bewegt. || (1) DU BIST HEUTE DIE VIERTE FREIE BAHN. Fuenfzehn der offenen Pakete liegen auf `spiel.md`/`technik.md` und sind von `ops/reserviert.txt` gehalten, dritter Tag. Deine Datei beruehrt keine andere Bahn -- das ist der Grund, warum dieser kleine Auftrag sofort laeuft und nicht wartet. || (2) MARKIEREN, NICHT LOESCHEN, und das steht schon richtig in deinem Rumpf: Hausregel 3. Jede aufgezeichnete Zeile unter dem Kopf bleibt bytegleich; der Kopf sagt, von welchem Stand die Aufzeichnung ist und wo der lebende Beleg liegt (`befunde/uebersetzung-<datum>.md`). Der Wert dieser Datei ist gerade, dass sie einen alten Stand zeigt -- sie darf ihn nur nicht als den heutigen ausgeben. || (3) SCHREIB KEINE ZAHL AB, DIE DU NICHT SIEHST. Die Angaben ueber den heutigen Stand (Selbsttestzahlen 9/20/8/7/9, Fall A2 mit fuenf Fundstellen) stammen aus der Pruefung von 0213 und aus 0213s Abnahme; nimm sie aus dem juengsten `befunde/uebersetzung-<datum>.md`, das `zahlwort_messung` gefahren zeigt, und nenne den Bericht mit Datum daneben. Weicht der Bericht von diesen Zahlen ab, gilt der Bericht, und die Abweichung gehoert in deine Meldung. Das ist genau der Fehler, den dieses Paket beseitigen soll -- eine fortgeschriebene fremde Zahl ohne Herkunft."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0180/lauf.txt]
abnahme: lauf.txt opens with a dated provenance header naming the commit it recorded (HEAD 584326c) and the two packages that changed the recorded behaviour since (0194 -- sorte 3 exists, A2 gains the Deklarationen finding; 0213 -- the probe compares per fundstelle, A2 yields 5 findings), and pointing to befunde/uebersetzung-<datum>.md as the living evidence. Every recorded line below the header stays byte-identical.
---

# lauf.txt presents the pre-0194 state as "the" measurement of 0180

**Proposed 2026-09-07 by the test-pruefer**, out of pruefung 0213.

## What is wrong

`befunde/messung-0180/lauf.txt` sits next to `messen.py` with no date and no
provenance, and records a run at HEAD 584326c: "9 Fundstellen der **zwei**
Nomen", self-test counts 9/18/8/7/6 (today: 9/20/8/7/9), and case A2 with
**4** findings and no Deklarationen line. Since 0213, A2 yields **5** findings
— the file now contradicts exactly the case that package changed, at the exact
place a reader goes to see what the messung produces.

Cost, already paid once: pruefung 0213 had to spend a search proving lauf.txt
is *not* current evidence before it could trust today's report. The next
reader without that suspicion cites it.

## Why an own package

The file belongs to no open package (`dateien` of 0199 and 0213 both exclude
it), a pruefer repairs nothing, and the fix is not a deletion (house rule 3)
but a marking: a header stating what stand the recording is from and where the
living evidence lives. One file, one edit, no build step.
