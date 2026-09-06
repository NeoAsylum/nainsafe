---
typ: messung
paket: 0156-verlaufgroesse-auch-absolut-beschraenkt
rolle: kernbauer
datum: 2026-09-06
bezugsstand: d80beae
---

# Die Groesse des Verlaufs haengt jetzt an zwei Reglern, nicht mehr an einem

Geaendert ist **eine** Datei: `kern/include/kern/verlauf.hpp`. Darin eine Konstante
(`STAPEL_JE_FADEN`), eine dritte Zusicherung ueber die Typgroesse und der Absatz, der
beide begruendet. `kern/src/verlauf.cpp` und `kern/test/verlauf_probe.cpp` sind
unberuehrt -- eine Zusicherung beim Uebersetzen braucht keine Probe zur Laufzeit.

Wiederholbar: `python3 befunde/messung-0156/schranke.py`, Rueckgabe 0 heisst, dass alle
vier Faelle so ausgegangen sind wie erwartet. Der Lauf steht daneben in `lauf.txt`.

# Bedingung 1 -- ein Verschieben der Wand macht den Bau rot

Gebaut wird der Kern im Alleinbau in einem Wegwerfbaum aus dem Leeren, je Fall zweimal:
mit dem Sanitizerprofil und ohne. Veraendert ist an jedem Baum genau eine Zeile, die
Wand `PARTIELAENGE_HOECHSTENS`; die Kapazitaet folgt ihr, weil sie aus ihr gebildet ist.

| Wand | Groesse des Behaelters | Sanitizer ON | Sanitizer OFF |
|---|---|---|---|
| 26 (heute) | 451.784 Byte | gruen | gruen |
| 482 | 8.375.240 Byte | gruen | gruen |
| 483 | 8.392.616 Byte | **rot** | **rot** |
| 483, ohne die neue Zusicherung | 8.392.616 Byte | gruen | gruen |

Die Meldung des roten Falls im Wortlaut, beide Profile zeichengleich:

```
kern/include/kern/verlauf.hpp:253:31: error: static assertion failed: T19: ein Verlauf
ist groesser als der Stapel eines Fadens (8.388.608 Byte) und damit groesser, als ein
Aufrufer ihn tragen kann -- die Wand aus T40 oder die Kapazitaet je Runde wurde
heraufgesetzt
```

**Die vierte Zeile ist die Gegenprobe und gehoert dazu.** Ohne sie waere belegt, dass
Wand 483 rot wird, aber nicht, dass die **neue** Zusicherung sie rot macht. Derselbe
Baum, dieselbe Wand, nur die drei Zeilen der neuen Zusicherung entfernt: gruen, in
beiden Profilen. Dazu prueft das Skript den Wortlaut zweiseitig -- die Meldung muss die
Stapelschranke nennen und darf die Meldung der T40-Zusicherung *nicht* enthalten.

# Bedingung 2 -- woher die Obergrenze kommt

**Aus dem, was ein Aufrufer traegt.** Jeder heutige Aufrufer legt seinen Verlauf als
oertliche Groesse an -- in `kern/test/verlauf_probe.cpp` an sieben Stellen (Zeilen 239,
321, 378, 409, 421, 435, 459), gezaehlt und nicht abgeschrieben. Der Platz, den ein
solcher Aufrufer hat, ist damit der Stapel seines Fadens und nicht der Freispeicher.

Diese Zahl ist gemessen, nicht gewaehlt: `ulimit -s` meldet auf der Baumaschine 8192,
also Kibibyte, und `getrlimit(RLIMIT_STACK)` denselben Wert als 8.388.608 Byte
(2026-09-06, Ubuntu unter WSL2, `g++` 15.2.0). Sie steht im Kopf als Kibibyte mal 1024 und nicht
als runde Bytezahl, damit ihre Herkunft am Ausdruck ablesbar bleibt.

**Der Abstand steht daneben**, wie die Bedingung es verlangt: heute 451.784 Byte, also
gut ein Zwanzigstel (5,4 Prozent) dessen, was ein Faden ueberhaupt an Stapel hat. Die
Schranke reisst erst, wenn die Wand von 26 auf 483 stiege.

## Die beiden Saetze, die mehr behaupteten, als die Zusicherungen deckten

**Zeile 72/73**, „Wer die Kapazitaeten hochsetzt, ohne die Folge zu bedenken, bekommt
einen roten Bau": Der Satz nennt jetzt beide Regler -- Kapazitaet *und* Wand -- und die
Tabelle oben belegt ihn fuer den zweiten, fuer den er bis heute nicht galt.

**Zeile 202**, „Ein Verlauf gehoert damit nicht beilaeufig auf einen Stapelrahmen": Der
Satz stand hinter einem „damit", das ins Leere zeigte. Er steht jetzt bei der dritten
Zusicherung, die tatsaechlich vom Stapel handelt, und nennt das Verhaeltnis, aus dem er
folgt.

**Und was die neue Zusicherung nicht sagt, steht im Kopf ausdruecklich dabei:** Ein
Stapelrahmen traegt mehr als den Verlauf. Wer die Wand bis 482 schoebe, bekaeme einen
gruenen Bau und trotzdem einen Stapelueberlauf. Die Schranke markiert die Stelle, an
der es *sicher* nicht mehr geht, nicht die, an der es bequem bleibt; eng gehalten wird
der Behaelter weiter von der Wandschranke aus Paket 0144, die bei 27 reisst.

# Bedingung 3 -- beide Profile gruen, gleich viele ctest-Eintraege

**Der Bezugsstand ist `d80beae`**, der Kopf des Zweiges zu Beginn dieses Laufs. Er und
nicht der Arbeitsbaum, weil waehrend des Laufs ein Fremdlauf an `kern/src/werte.cpp`,
`kern/include/kern/werte.hpp` und `kern/test/werte_probe.cpp` geschrieben hat: Zu
Beginn meiner Messung war der Arbeitsbaum an zwei ungenutzten Funktionen in
`werte_probe.cpp` rot (`-Werror=unused-function`, Zeilen 1398 und 1452), am Ende
gruen. Ein Stand, der sich unter der
Messung bewegt, ist kein Bezugsstand. Gebaut wurde deshalb aus `git archive d80beae`,
je Baum und Profil aus dem Leeren.

| Baum | Profil | vorher (`d80beae`) | nachher (mit dieser Aenderung) |
|---|---|---|---|
| Kern allein | Sanitizer ON | 0/0/0, 12 von 12 | 0/0/0, 12 von 12 |
| Kern allein | Sanitizer OFF | 0/0/0, 12 von 12 | 0/0/0, 12 von 12 |
| Arbeitsbereich | Sanitizer ON | 0/0/0, 18 von 18 | 0/0/0, 18 von 18 |
| Arbeitsbereich | Sanitizer OFF | 0/0/0, 18 von 18 | 0/0/0, 18 von 18 |

Die drei Zahlen sind die Rueckgaben von `cmake -S`, `cmake --build` und `ctest`. Die
Zahl der ctest-Eintraege ist unveraendert -- dieses Paket legt keine Probe an und nimmt
keine weg.

**Derselbe Lauf noch einmal im Arbeitsbaum**, nachdem der Fremdlauf fertig war: alle
vier Zeilen ebenso 0/0/0 bei 12 beziehungsweise 18 Eintraegen. Darin enthalten sind
`belegstellen_riegel` (#16), `bezeichner_riegel` (#17) und `schlussriegel_nachbau`
(#18).

# Was ich nicht gemessen habe

`ctest` laeuft in den drei Faellen der Bedingung 1 **nicht**, und das ist Absicht: Bei
Wand 482 legt `verlauf_probe` acht Megabyte auf einen Stapelrahmen und liefe in einen
Stapelueberlauf. Das ist genau die Grenze, die der Kopf der Schranke selbst nennt --
geprueft wird dort die Uebersetzung, nicht der Lauf. Bei Wand 26, dem einzigen Wert,
der im Baum steht, laeuft ctest vollstaendig (Bedingung 3).

Nicht geprueft habe ich, ob eine andere Baumaschine einen anderen Stapel voreinstellt.
Die Zusicherung wuerde davon nicht beruehrt -- sie vergleicht gegen die im Kopf
festgehaltene Zahl, nicht gegen die Umgebung --, aber die Begruendung dieser Zahl
haengt an der Messung vom 2026-09-06.
