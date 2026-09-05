# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 10:28. Fassung 27, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Die Bauseite stand auf null, und die Ursache waren nicht die Dateischnitte, sondern
zehn nicht gezogene Urteile.** 123 Pakete: 27 offen, 2 gebaut, 87 fertig, 3 blockiert,
**0 Vorschläge**. Der Trockenlauf zu Beginn plante **0 von 8** Bauplätzen; nach dem
Statusnachzug sind es **8 von 8**. Acht Abnahmen, fünf gesichtete Vorschläge.

## Null Bauplätze bei 22 offenen Paketen — die Messung und was sie widerlegt

Der erste Trockenlauf dieses Laufs meldete `Bau 0 Pakete gleichzeitig`, bei 22 offenen
Paketen und acht freien Plätzen. Das sieht nach dem Kollisionsproblem aus, das die
letzten drei Fassungen beschrieben haben. **Es war ein anderes.**

Nachgezählt über alle 22, je Paket die Frage aus meinem Logbuch — hält es eine
Abhängigkeit oder nur der Dateischnitt:

| Warum kein Platz | Pakete |
|---|---:|
| wartet auf ein Urteil über ein `gebaut`-Paket (direkt oder über eine Kette) | **22** |
| verliert allein am Dateischnitt, Abhängigkeiten erfüllt | **0** |

**Jede** Abhängigkeit der 22 war entweder schon `fertig` oder eines der zehn
`gebaut`-Pakete. Zehn Urteile lagen vor, acht davon waren geschrieben und nicht gezogen.
Das Ziehen allein hat die Bauseite von 0 auf 7 gebracht, ohne ein einziges neues Paket;
das achte kam aus den Vorschlägen.

**Was daraus folgt, und es ist die Korrektur einer eigenen früheren Aussage:** Der
Dateischnitt ist der Engpass, sobald die Urteile gezogen sind — aber er war es an diesem
Morgen nicht. Ein Rückstand, der auf Urteile wartet, sieht genauso aus wie einer, der an
Dateien klemmt, und die beiden verlangen entgegengesetzte Antworten. **Die Unterscheidung
kostet einen Trockenlauf und die Frage „hält es eine Abhängigkeit oder eine Datei?".**

## Acht Abnahmen, und warum keine davon dem Commit-Betreff geglaubt hat

| Paket | Rolle | Prüfer | Nebenbefunde |
|---|---|---|---:|
| 0051 t46-gebietspräfix | `architekt` | entwurf-prüfer | 0 |
| 0061 kernanker-sichtbarkeit | `testentwickler` | test-prüfer | 0 |
| 0072 zustandhpp-doppelpunktverweise | `kernbauer` | kern-prüfer | 0 |
| 0087 plus-und-minus-in-festkomma | `kernbauer` | kern-prüfer | 0 |
| 0090 rückstand-fünf-tote-zitate | `datenbauer` | daten-prüfer | **2** |
| 0094 linkschalterform | `kernbauer` | kern-prüfer | 0 |
| 0097 zustandsausgabe-zuordnungen | `testentwickler` | test-prüfer | 0 |
| 0107 kennzeichen-gegen-nachbarmeldungen | `testentwickler` | test-prüfer | 0 |

Alle acht tragen `urteil: geprueft`. **Ein Befund gehört zu einem Bau, nicht zu einem
Paket** — deshalb ist jeder gegen die Zieldatei geprüft, nicht gegen den Betreff. Das war
nötig, und zwar messbar: Der Befund zu **0097** und der zu **0072** liegen in Commits, die
im Betreff `0087` und `0094` nennen. Wer nach dem Betreff sortiert, zieht zwei Urteile
nicht und hält zwei für neu, die es nicht sind.

**0079 sieht aus wie das neunte und ist es nicht.** Es trägt einen Befund von heute mit
`urteil: zurueck` — geschrieben um 03:22, verarbeitet in meinem Lauf um 05:43, und das
Paket ist um 06:09 neu gebaut worden. Der Befund ist abgearbeitet, das Paket wartet auf
sein **nächstes** Urteil. Es steht weiter auf `gebaut` und hat einen Prüfplatz.

## Fünf Vorschläge, fünf Annahmen — drei davon kosten keinen Platz

| Paket | Rolle | Datei | Entscheidung |
|---|---|---|---|
| **0120** abschnittszitat-nachmessung | `datenbauer` | `daten/nachmessung-…` | `offen`, **baut sofort**, Bedingung 1 verengt |
| **0122** strichrechnung-sperre | `kernbauer` | `kern/…/sperre.hpp` | `offen`, kollidiert mit nichts |
| **0123** mal-kopf-null-aufrufer | `kernbauer` | `kern/…/festkomma.hpp` | `offen`, kollidiert mit nichts |
| **0124** zerlegung-als-folge | `kernbauer` | `werkzeugkette.cmake` | `offen`, Ende der cmake-Kette |
| **0126** historischer-verweis | `datenbauer` | `daten/reihen.toml` | `offen`, **Weg gewählt**, Kette ergänzt |

Die Rollenfrage steht zuerst und trägt diesmal bei allen fünf: `datenbauer` und
`kernbauer` stehen in `BAUROLLEN`. Keine Waise, kein `builder`, kein `projektmanager`.

**Die Nummernkollisionen haben sich selbst gelöst**, wie erwartet: `0121-zerlegung` steht
auf `umgezogen` (nach 0124), `0125-nachmessung` auf `zurueckgezogen`. Erst zusammenfassen,
dann umbenennen — hier war beides schon geschehen.

**Drei der fünf halten eine Datei, die kein anderes Paket beansprucht.** Das ist der
seltene Fall, und er ist der Grund, warum die Bauseite jetzt voll ist statt bei sieben.

### 0126: der Prüfer ließ mir zwei Wege, ich habe Weg 2 genommen

Die fünf toten Verweise sollten entweder je den richtigen Commit nennen (Weg 1) oder
ganz aufgelöst werden (Weg 2). **Weg 2**, aus drei Gründen; der dritte ist der eigentliche:

1. Das Paket trägt sein Argument selbst: `rueckstand.md` ist eine Verlaufsdatei, ihre
   Geschichte ein noch schlechteres Ziel für einen dauerhaften Verweis.
2. Weg 1 heilt fünf Fundstellen, Weg 2 beseitigt die **Sorte**. Sie ist hier dreimal
   aufgetreten (0073, 0090, 0126).
3. Weg 1 misst gegen die Commit-Geschichte, die sich ändern kann, während das Paket offen
   ist. Weg 2 ist vollständig am Dateistand messbar. **Ein Nachweis, der nur am
   Arbeitsbaum hängt, ist der belastbarere** — dieselbe Überlegung wie hinter meiner Regel
   gegen ausgeschriebene Zahlen.

Die `abnahme` ist entsprechend neu geschrieben und verlangt die Bedingung, nicht den
Wortlaut. **Der Hinweis des Prüfers auf 0095 ist erledigt und erzeugt kein Paket:** 0095
ist `fertig`, hält `belegstellen_riegel.cpp`, und der strittige Commit steht dort nicht.
Nachgemessen über den ganzen Arbeitsbaum (`bau/` und `befunde/` ausgenommen, beides
Abschriften): nur `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md` — also genau
die zwei Dateien dieses Pakets.

### 0120: ich hätte den Fehler beinahe selbst erzeugt, den das Paket beseitigt

0120 bringt den einzigen bewerteten Riegelfehler weg. Solange er steht, trägt **jeder**
Übersetzungsbericht `ergebnis: fehler`, und jede Abnahme, die sich darauf stützt, muss ihn
herausrechnen. Deshalb steht es im Bau, obwohl kein Vorrang es nennt.

**Beim Schreiben meines Annahmevermerks habe ich das Schlüsselwort des Riegels neben einen
Dokumentnamen gestellt** — in genau der Datei, deren Paket die Zahl auf null bringen soll.
Der Riegel liest das ganze Vorhaben und nimmt nur `bau/` und `befunde/` aus; `aufgaben/`
gehört dazu. Der Vermerk ist umformuliert. **Fassung 23 hat auf dieselbe Weise die
Werkzeugkette rot gemacht; diesmal ist es vor dem Schreiben gefangen.**

**Daraus folgte die zweite Änderung, und sie ist die wichtigere.** Bedingung 1 verlangte
„**null** Zitate ohne Überschrift" — eine Aussage über den ganzen Korpus, in den jede
Rolle jederzeit schreibt. Ein Bauagent kann diese Null nicht herstellen und nicht halten:
Es genügt, dass während seines Laufs ein Prüfer ein Paket ablegt, und seine erbrachte
Leistung fällt an einer Ursache durch, die er nicht erreicht. **Das ist die Bauart, an der
hier schon drei Pakete gescheitert sind, und zwei davon gehen auf meine Formulierung
zurück.** Die Bedingung heißt jetzt: die eigene Fundstelle verschwindet, und die Zahl
steigt gegenüber dem unmittelbar vorhergehenden Stand desselben Baums nicht.

## Die vier Ketten — der Rückstand ist jetzt abhängigkeits-, nicht dateigebunden

    technik.md      0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092   (7, davon 1 im Bau)
    riegel.cpp      0079 → 0083 → 0105 → 0106 → 0115                 (5, davon 1 in Prüfung)
    reihen.toml     0078 → 0099 → 0100 → 0126                        (4, davon 1 im Bau)
    werkzeugkette   0103 → 0104 → 0108 → 0124                        (4, davon 1 im Bau)

Jedes Glied trägt seinen Vorgänger in `haengt_an`; nachgemessen, nicht behauptet. **Neu in
diesem Lauf ist das vierte Glied der `reihen.toml`-Kette.** 0126 hing nur an 0090, das
jetzt `fertig` ist — es wäre damit sofort startbereit gewesen und neben der Prüfung von
0078 gegen einen wandernden `reihen.toml` gelaufen. `startbereit()` vergleicht die
Dateilisten nur unter `offen`; ein Paket auf `gebaut` schützt seine Datei nicht.

**In jedem der vier Ketten-Endpakete steht jetzt derselbe Satz für den Bauagenten:** Dein
Vorher-Stand ist der dann geltende `HEAD`, nicht der Stand von heute; such die Stellen am
Text, nicht an einer Zeilennummer.

## Was der Geschäftsführer entscheiden lassen muss

> **Diese Überschrift trägt keine technische Last mehr, bleibt aber im Wortlaut stehen.**
> 0090 ist seit diesem Lauf abgenommen, die Stütze ist damit gefallen. Ich benenne sie
> trotzdem nicht um: 0126 arbeitet gerade an denselben Verweisen, und eine Umbenennung
> während eines laufenden Pakets ist genau der Handgriff, der Fassung 23 rot gemacht hat.
> Sie wird frei, wenn 0126 abgenommen ist — nicht wenn es geliefert hat.

**1. Ein neuer Vorrang. Die Liste in `ops/plan.md` ist vollständig abgearbeitet.** Alle
fünf — 0026, 0002, 0071, 0027, 0010 — stehen auf `fertig`; der Plan stammt vom 2026-09-04
07:49 und ist seither nicht erneuert worden. Ich habe die vier Pakete des Betreibers vom
2026-09-05 als Vorrang behandelt und 0116 an die Spitze von `technik.md` gestellt. **Das
war eine Auslegung, keine Anweisung** — zum zweiten Mal, und zum zweiten Mal unbeantwortet.
Offen ist vor allem, was nach 0118 kommt: Fünf Länder auswählen ist ein Entwurf; sie
einzubauen ist ein Kern-, Daten- und Prüfgewerk, das im Rückstand mit keinem Paket
vertreten ist.

**2. `technik.md` zerlegen — unverändert die teuerste offene Frage.** Sieben Pakete auf
einer Datei, strikt nacheinander, je zwei Durchgänge. Zwei davon gehören dem Betreiber und
sind das Tor zur Ländererweiterung. **Zum vierten Mal gemeldet, und ich ändere nichts** —
es wäre eine Entwurfsentscheidung. Was ich diesmal dazusagen kann: Die Kette ist mit 0116
an der Spitze angelaufen, und solange sie läuft, ist der Architekt eine Rolle mit einem
Platz.

**3. Die zweite Hälfte von 0121 braucht einen ruhigen Lauf des Betreibers.** Der Commit
bindet die Pfade an die **Werkzeugliste der Rolle** statt an die `dateien`-Liste des
Pakets. Der Betrieb hat am 2026-09-05 die schwerere Hälfte behoben — `git commit` bekommt
jetzt dieselbe Pfadangabe wie `git add` —, die erste steht noch. **Frischer Beleg aus
diesem Lauf:** Zwei Prüfbefunde lagen in Commits, deren Betreff ein anderes Paket nennt.
Es hat mich zwei zusätzliche Messungen gekostet und wäre ohne die Gegenprobe über die
Zieldatei ein falscher Statusnachzug geworden. Das Paket steht zu Recht auf `blockiert`:
`agents/lauf.py` liegt außerhalb jeder Schreibgrenze, die die Rollentabelle vergibt.

**4. `0091` bleibt gesperrt: der T19-Träger fehlt.** Der angekündigte Auslöser ist geprüft
und hat **nicht** gefeuert — `kern/include/kern/` führt keine `verlauf.hpp`. Es hängt
nichts daran.

**5. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen T5s Skalentabelle,
eine ADR-Entscheidung von dir. `einheiten.hpp` gibt es ebenfalls nicht. Hier nur, damit es
nicht aus dem Blick fällt.

## Was der nächste Lauf zuerst anfasst

1. **Die zwei Prüfplätze zuerst — 0119 und 0079.** An 0119 hängt 0118 und damit der Rest
   der Ländererweiterung; an 0079 hängt die ganze vierstellige Riegelkette (0083, 0105,
   0106, 0115). Zwei Urteile lösen fünf Pakete.
2. **Die Kettenköpfe nachziehen, sobald sie liefern.** 0078, 0103 und 0116 sind je der
   Kopf einer Kette; jedes gezogene Urteil macht genau ein Folgepaket startbereit. Das ist
   ab jetzt die Hauptarbeit des Statusnachzugs — vier Ketten, die sich Glied für Glied
   abarbeiten.
3. **Prüfen, ob 0120 die Riegelzahl wirklich gesenkt hat**, und zwar am Riegel selbst, nicht
   am Übersetzungsbericht. Steht dort danach weiter ein Fehler, stammt er aus einer
   Paketdatei unter `aufgaben/` — dann ist es meine Sorte Fehler und kein Rücklauf gegen
   den Bauagenten.
4. **Keinen neuen Auslöser an eine Platzzahl hängen.** Unverändert gültig: gegen
   `GLEICHZEITIG` messen, nie gegen eine ausgeschriebene Zahl.
5. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert; der
   Zählfehler in Abschnitt 18 vererbt sich sonst. Der Vermerk steht in 0092.
6. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`.
   Die Datei trägt dann schon 0078, 0099, 0100 und 0126; das neue Paket wird **fünftes**
   Glied jener Kette.
7. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 6 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus vier
   Fassungen.
8. **Nicht noch einmal untersucht werden muss:** `aufgaben/.kopf.tmp` und `.paket.tmp`,
   ebenso die `.tmp`-Dateien unter `daten/zwischenstaende/`. `pakete()` liest nur `*.md`,
   sie sind für den Baulauf unsichtbar. Die Kopfzahl stimmt ohne sie: 27 + 2 + 87 + 3 =
   119, plus je eine `archiviert`, `zurueckgezogen` und zwei `umgezogen` sind die 123
   Dateien im Verzeichnis. Hausregel 3 — sie bleiben liegen.
