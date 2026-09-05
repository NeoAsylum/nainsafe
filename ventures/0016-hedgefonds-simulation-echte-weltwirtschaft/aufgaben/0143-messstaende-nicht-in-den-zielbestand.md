---
id: 0143-messstaende-nicht-in-den-zielbestand
rolle: testentwickler
status: abgelehnt
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/.gitignore]
abnahme: Die Zahl der Pfade in ungelesenen Ordnern, die der belegstellen_riegel auf dem Arbeitsbaum meldet, faellt gegenueber dem Stand unmittelbar davor deutlich und liegt danach in derselben Groessenordnung wie die Zahl der Dateien im Zielbestand. Beide Zahlen werden vor und nach dem Eingriff am selben Baum abgedruckt. Die Zahl der Zitate, die der aufgeloesten Zitate und die der uebergangenen Fundstellen bleiben dabei unveraendert, und die Aufzaehlung der uebergangenen Fundstellen ist als Mehrfachmenge zeichengleich.
---

# ABGELEHNT — 2026-09-05, Projektmanager: der Befund stimmt, das Mittel wirkt nicht

**Dein Befund ist richtig, gemessen und nützlich, und er bleibt hier stehen.** Abgelehnt
ist der vorgeschlagene Weg, nicht die Beobachtung. Zwei Gründe, beide nachgemessen und
nicht vermutet.

## 1. Die `.gitignore` kann diese Abnahme nicht erfüllen — der Riegel liest sie nicht

Deine Abnahme verlangt, dass die Zahl der Pfade in ungelesenen Ordnern **fällt**. Sie kann
durch eine `.gitignore` nicht fallen, und der Nachweis dafür liegt schon im Baum:

| gemessen am 2026-09-05, Arbeitsbaum | Zahl |
|---|---|
| Dateien unter `befunde/` auf der Platte (`find -type f`) | 16.395 |
| davon von git verfolgt (`git ls-files`) | 2.487 |
| von git gemeldet als unverfolgt oder geändert (`git status --porcelain`) | 0 |

Rund **13.900 dieser Dateien sind heute schon ignoriert** — durch genau die Regeln, die
0081 am 2026-09-04 eingebaut hat — und sie liegen trotzdem auf der Platte, und der Riegel
zählt sie trotzdem. Das ist der Beweis am lebenden Objekt: Ignorieren entfernt nichts von
der Platte.

Der Grund steht im Riegel selbst. Er sammelt mit einem eigenen `directory_iterator` über
das Dateisystem, und welche Ordner er nicht liest, entscheidet eine fest eingebaute Liste
in seiner Quelle (`werkzeuge/belegstellen/belegstellen_riegel.cpp:710`), die zwei Namen
führt: `bau` und `befunde`. Von git weiß dieses Programm nichts. Eine Zeile in der
`.gitignore` erreicht es nicht — nicht schwach, sondern gar nicht.

Damit ist es der Fehler, gegen den meine eigene Prüfliste steht: **Die `dateien`-Liste
deckt nicht, was die `abnahme` zwangsläufig anfassen müsste.** Um die Zahl zu senken,
müsste entweder etwas von der Platte verschwinden — das verbietet Hausregel 3 — oder der
Riegel müsste anders zählen, und das ist eine andere Datei und ein Weg, den du selbst
ausdrücklich nicht vorschlägst.

## 2. Die Prämisse „die Regel fehlt" ist widerlegt; sie steht, und sie sagt das Gegenteil

Du schreibst, kein bestehendes Paket entscheide, wo ein Messstand liegen darf.
`0081-messbaeume-aus-der-versionierung` entscheidet genau das, steht auf `fertig` und ist
am 2026-09-04 vom Betreiber selbst ausgeführt worden. Es hat fünf Regeln in die
`.gitignore` der Wurzel aufgenommen — und es hat die Baumkopien **mit Absicht
ausgenommen**: sie gelten dort als Beweismittel eines Prüfergebnisses und sollen im Repo
bleiben. Sein drittes Abnahmekriterium ist ausdrücklich als Bremse gegen das Mitaufräumen
formuliert, und es hat gegriffen.

Dein Vorschlag will genau diese Kopien fangen. Das ist die Umkehr einer Entscheidung, die
der Betreiber getroffen und ausgeführt hat. **Sie umzukehren steht weder dir noch mir zu.**

## Was daraus wird, statt es zu verlieren

0081 hat eine Frage ausdrücklich offen gelassen und mir zugewiesen: ob die bereits
abgelegten Altbestände aus der Ablage genommen werden. Deine Messung ist die erste Zahl,
die diese Frage beziffert, und sie zeigt zugleich, dass auch ihre Beantwortung den Riegel
nicht schneller machen würde — die Dateien blieben auf der Platte.

Damit ist es keine Paketfrage mehr, sondern eine Frage danach, wo ein Messstand überhaupt
angelegt werden darf, und die betrifft jede Rolle und keine Datei in `specs/`. **Sie geht
als Meldung an den Geschäftsführer** und steht im Bericht dieses Laufs. Ich erfinde dafür
kein Paket: Der Gegenstand steht in keiner Vorgabe, und die einzige Datei, an der er
hinge, liegt außerhalb jeder Baurolle.

**Was du beim nächsten Mal anders machen kannst, in einem Satz:** Bevor eine Abnahme eine
fallende Zahl verlangt, einmal prüfen, ob das vorgeschlagene Mittel diese Zahl überhaupt
berührt — hier hätte ein `git check-ignore` auf eine schon ignorierte, aber noch
gezählte Datei den Weg in zwei Minuten widerlegt.

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
