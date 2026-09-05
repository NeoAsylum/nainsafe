---
id: 0143-messstaende-nicht-in-den-zielbestand
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/.gitignore]
abnahme: Die Zahl der Pfade in ungelesenen Ordnern, die der belegstellen_riegel auf dem Arbeitsbaum meldet, faellt gegenueber dem Stand unmittelbar davor deutlich und liegt danach in derselben Groessenordnung wie die Zahl der Dateien im Zielbestand. Beide Zahlen werden vor und nach dem Eingriff am selben Baum abgedruckt. Die Zahl der Zitate, die der aufgeloesten Zitate und die der uebergangenen Fundstellen bleiben dabei unveraendert, und die Aufzaehlung der uebergangenen Fundstellen ist als Mehrfachmenge zeichengleich.
---

# Ein Messstand gehoert nicht in die Menge, gegen die nachgeschlagen wird

## Was gemessen ist

Der `belegstellen_riegel` liest den Inhalt von `bau/` und `befunde/` nicht -- aber er
sammelt seit Paket 0083 aus beiden die **Dateinamen** ein. Er braucht sie, um ein totes
Ziel von einem Ziel in einem mit Absicht ungelesenen Ordner zu unterscheiden.

Am 2026-09-05, derselbe Riegel, dieselbe Stunde, zwei Baeume:

| Bestand | Dateien im Zielbestand | Pfade in ungelesenen Ordnern | Laufzeit |
|---|---|---|---|
| eingefrorene Kopie (456aefa) | 196 | 452 | 0,23 s |
| Arbeitsbaum | 198 | **21.207** | 0,84 s |

Der Unterschied ist fast vollstaendig **eine committete Kopie des ganzen Vorhabens**:
Der Messstand zu Paket 0105 haelt unter `befunde/messung-0105/` drei Baeume, jeder eine
Kopie von `ventures/` und `specs/`, und alle drei sind in `0333b81` in die Ablage
gegangen.

## Warum das ein eigenes Paket ist

**Es ist keine Aufraeumarbeit an fremdem Gebiet, sondern eine Regel, die fehlt.** Kein
bestehendes Paket entscheidet, wo ein Messstand liegen darf; jede Rolle waehlt den Ort
neu, und die Waehler haben gute Gruende: `befunde/` wird vom Riegel nicht gelesen und
von `baulauf.py` nicht nach Manifesten durchsucht (`AUSGENOMMEN`, `baulauf.py:132`).
Beides stimmt. Uebersehen wird die dritte Menge -- die der eingesammelten **Namen**.

**Der Schaden ist heute noch keiner, und genau deshalb gehoert er jetzt entschieden.**
Die Einstufungen sind unveraendert (37 Zitate, 37 aufgeloest, 47 uebergangen auf beiden
Seiten). Aber die Menge, gegen die jedes Zitat nachgeschlagen wird, ist um den Faktor 47
gewachsen und waechst mit jedem weiteren Messstand weiter. Sie enthaelt jetzt fuer jeden
Pfad des Vorhabens einen zweiten unter `befunde/messung-.../baum/...`, und ein Zitat, das
auf einen dieser Pfade trifft, wird als "Ziel in einem mit Absicht ungelesenen Ordner"
eingestuft statt als das, was es ist.

**Es passt in kein laufendes Paket.** 0105, 0106 und 0115 halten `belegstellen_riegel.cpp`
und entscheiden ueber das Erkennen von Zitaten, nicht ueber die Ablage von Messstaenden.
Der naheliegende Eingriff liegt ausserdem in einer anderen Datei als alle drei.

## Der vorgeschlagene Weg

Die `.gitignore` des Vorhabens faengt die Baumkopien und die Bauordner der Messstaende,
so wie sie `bau/` schon faengt. Was in die Ablage gehoert, ist der **Messstand** --
`CMakeLists.txt`, die Skripte, die Mitschnitte --, nicht die kopierten Baeume: Die sind
aus dem in `bezugsstand.txt` genannten Commit jederzeit wiederherstellbar und stehen
schon einmal in der Ablage.

Die Alternative, den Riegel Pfade unter `messung-*/` ueberspringen zu lassen, ist
absichtlich **nicht** vorgeschlagen: Das waere die erste Zeile einer Ausnahmeliste nach
Pfadnamen, und der Kopf jenes Programms hat genau das schon einmal verworfen.

## Grenzen

* Nur die `.gitignore`. Kein Loeschen von etwas, das schon in der Ablage steht --
  Hausregel 3. Bereits committete Kopien bleiben liegen; der Vorschlag verhindert die
  naechsten und macht die vorhandenen zur benannten Altlast.
* Wer das aendert, misst vor und nach dem Eingriff am selben Baum und druckt beide
  Zahlen ab. Eine hier notierte Zahl ist ein Messwert vom 2026-09-05.

Vorschlag des Testentwicklers vom 2026-09-05, gemessen bei der Arbeit an
`0105-belegstellenriegel-name-am-zeilenende`
(`befunde/messung-0105-belegstellenriegel-name-am-zeilenende-2026-09-05.md`, Befund 1).
