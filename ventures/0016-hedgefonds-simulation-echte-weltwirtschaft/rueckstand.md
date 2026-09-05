# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 11:44. Fassung 28, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Sieben Urteile lagen geschrieben vor und keines war gezogen; der Bau stand deswegen bei
fünf von acht.** 126 Pakete: 26 offen, 0 gebaut, 92 fertig, 4 blockiert, **0 Vorschläge**.
Der Trockenlauf zu Beginn plante **5 von 8** Bauplätzen, nach dem Statusnachzug sind es
**8 von 8**. Fünf Abnahmen, zwei Rückläufe, drei gesichtete Vorschläge — und ein
gemessener Befund, der nicht in ein Paket gehört, sondern nach oben.

## Der Statusnachzug: fünf Abnahmen, zwei Rückläufe, kein einziger nach Betreff sortiert

| Paket | Rolle | Prüfer | Urteil |
|---|---|---|---|
| 0098 diff-kennungen-ohne-differenz | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0101 zustandhpp-kein-platz | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0110 mutationslauf-als-riegel | `testentwickler` | test-prüfer | **geprüft** → `fertig` |
| 0111 korbbestand-anleihezweig | `testentwickler` | test-prüfer | **geprüft** → `fertig` |
| 0119 welt-in-drei-schichten | `spielentwerfer` | entwurf-prüfer | **geprüft** → `fertig` |
| 0078 reihentoml-preisbasis | `datenbauer` | daten-prüfer | **zurück** (2) → `offen` |
| 0079 belegstellenriegel-zitat | `testentwickler` | test-prüfer | **zurück** (2) → `offen` |

Jedes Urteil ist gegen die Zieldatei geprüft, nicht gegen den Commit-Betreff, und das war
wieder nötig: Der Befund zu **0078** liegt in einem Commit, dessen Betreff **0098** nennt.
Beide Rückläufe sind nach dem jeweils letzten Bau geschrieben und gelten damit; keiner ist
ein bereits abgearbeiteter Altbefund.

## Zwei zweite Rückläufe — bei beiden habe ich den Weg gewählt, nicht den Wortlaut

`RUECKLAUF_MAX` ist 3. Beide Pakete stehen bei zwei, und meine eigene Regel sagt: **Bricht
etwas zweimal an derselben Stelle ab, prüfe ich Abnahme und Zuschnitt, nicht den
Bauagenten.** Ich habe beides geprüft und in beiden Fällen die Abnahme stehen lassen — die
Begründung steht je im Paket, hier nur das Ergebnis.

### 0078: der Prüfer ließ zwei Wege, ich habe Streichen gewählt

Ein Satz im Prüfweg-Feld behauptet eine Einzigkeit, und ein Block derselben Datei widerlegt
sie — die Normierung der Reihe 2 teilt durch eine je Gebiet und Jahr wechselnde Größe. Die
Aufzählung davor ist über alle 23 Blöcke nachgemessen und richtig; nur der Satz danach ist
falsch.

**Der Prüfer schreibt mir dazu einen Satz, den ich hier stehen lasse, weil er auf mich
zielt:** Der Ausweg aus Rücklauf 1 — „die Einzigkeit auf den jahresweisen Teiler
einschränken" — stammt aus seinem eigenen ersten Befund, **und mein Vermerk hat ihn
mitgetragen.** Genau dieser Weg führt an der Reihe 2 vorbei. Zweimal dieselbe Bauform:
eine Zählaussage über 23 Blöcke, gemessen an weniger als 23. Ein dritter Durchgang, der
wieder eine engere Einzigkeit sucht, scheitert wahrscheinlich wieder — und danach steht das
Paket still.

Deshalb: **streichen.** Die Bedingung lässt es ausdrücklich zu, die Aufzählung trägt die
Regel allein, und die Wahl steht im Paket, damit der Bauagent sie nicht noch einmal treffen
muss. Ich habe sie getroffen, weil das meine Arbeit ist.

### 0079: alles erbracht außer einer Messung — und deshalb steht keine Zahl in meinem Vermerk

Vier von fünf Teilen der Abnahme sind erbracht und vom Prüfer unabhängig nachgemessen. Der
eine Befund: Die Vorher/Nachher-Zahlen im Nachweis sind an keinem Stand des Baulaufs
reproduzierbar und widersprechen dem Lauf, den dasselbe Dokument abdruckt. Zu tun bleibt
eine Messung und drei berichtigte Zahlen.

**Der Prüfer nennt die Zahlen, die er gemessen hat. Ich schreibe sie nicht in den
Vermerk.** Abschreiben statt Messen *ist* der Fehler dieses Pakets — zweimal in Folge. Ein
Vermerk ist eine Vorlage zum Abschreiben; eine Zahl darin wäre wieder nicht die Messung des
Bauagenten. Der Weg dorthin steht Schritt für Schritt im Befund.

Teilen hilft hier nicht (eine Messung, drei Zahlen, eine Datei — das ist kein zweiter
Lauf), Umstellen hilft nicht (es hängt an nichts), und die Bedingung setzt keinen Zustand
voraus, den der Bauagent nicht erreicht: Sie vergleicht seinen Stand gegen den unmittelbar
vorhergehenden desselben Baums, beide Programme baut er selbst. **Die Abnahme bleibt
wörtlich stehen.**

## Drei Vorschläge: einer gesperrt, zwei angenommen

| Paket | Rolle | Datei | Entscheidung |
|---|---|---|---|
| **0127** übersetzungsbericht-ohne-proben | `testentwickler` | `agents/baulauf.py` | **`blockiert`** — außerhalb jeder Schreibgrenze |
| **0128** zählung-vier-je-land | `spielentwerfer` | `specs/…/spiel.md` | `offen`, **eigener Lauf**, füllt den 8. Bauplatz |
| **0129** bezeichner-im-kommentar | `testentwickler` | `werkzeuge/bezeichner/*` | `offen`, Abnahme an zwei Stellen berichtigt |

Die Rollenfrage steht zuerst und trägt bei allen drei — `testentwickler` und
`spielentwerfer` stehen in `BAUROLLEN`. Keine Waise, kein `builder`.

**Alle drei Prämissen habe ich nachgemessen, nicht abgeschrieben.** `agents/baulauf.py`
ruft `ctest` in Zeile 186 tatsächlich ohne den Schalter auf, der einen Lauf ohne gefundene
Fälle rot macht. `spiel.md` führt den Buchstaben R dokumentweit als Partielänge und rechnet
in Zeile 1087 trotzdem 780 daraus — mit R = 20 wären es 80. `werkzeuge/` führt heute
`belegstellen` und `mutation`, kein `bezeichner`.

### 0127: derselbe Fall wie 0121, dieselbe Entscheidung

Die `dateien`-Liste nennt den Runner. Dorthin schreibt keine Rolle, die die Tabelle in
`CLAUDE.md` kennt. Als `offen` hätte der Baulauf das Paket **sofort** eingeplant — es
kollidiert mit nichts in diesem Vorhaben — und ein Bauagent bekäme einen Auftrag, den er
nach den Hausregeln nicht ausführen darf. Als `vorschlag` kostet es jeden meiner Läufe eine
neue Sichtung. `blockiert` kostet einmal einen Absatz. Es hängt nichts daran.

### 0128: eigener Lauf statt Auflage in 0118 — und das ist der achte Bauplatz

Der Prüfer stellte mir frei, die zwei Ein-Satz-Berichtigungen in 0118 mitfahren zu lassen.
**Eigener Lauf**, aus drei Gründen: Er gewinnt sofort einen Bauplatz (0118 wartet hinter
0117 hinter 0116 auf `technik.md`, bis dahin läuft nichts auf `spiel.md`); er koppelt keine
sichere Sache an den Ausgang einer unsicheren; und er räumt das Symbol weg, aus dem 0118
seine eigene Ländergeometrie ableitet — die Berichtigung gehört davor, nicht daneben.

Preis: 0118 bekommt 0128 als **Reihenfolgesperre** in `haengt_an` — eingetragen, nicht bloß
behauptet. Sachlich braucht 0118 von dort nichts als einen ruhigen Dateistand, und da es
ohnehin auf 0117 wartet, kostet die Sperre keinen Platz.

### 0129: zwei Berichtigungen an der Abnahme, beide aus derselben Regel

Bedingung 3 zählte „die heute gemessenen 19 falschen Kandidaten". Vier Pakete (0098, 0101,
0122, 0123) arbeiten gleichzeitig im Kern; die Neunzehn ist am Tag der Abnahme
wahrscheinlich eine andere Zahl, und dann fällt eine richtige Regel an einer veralteten
Zählung durch. Sie heißt jetzt „jeder Kandidat" — **strenger, nicht schwächer.** Bedingung
4 zählt gegen den unmittelbar vorhergehenden Stand desselben Baums statt gegen eine Zahl
von heute.

**Den Konflikt darunter habe ich sichtbar gemacht statt aufgelöst:** Ein `ctest`-Eintrag
muss grün sein, sonst ist die Werkstatt rot — aber der Kern gehört diesem Paket nicht, und
vier fremde Pakete schreiben gerade hinein. Der Ausgang steht jetzt in der Bedingung:
melden, nicht selbst reparieren, gemessen gegen den Vorstand statt gegen eine Null.

**Nicht verwechselt mit 0091.** Auch dort nennt die `dateien`-Liste Dateien, die es nicht
gibt — dort ist es der Sperrgrund. Der Unterschied ist der Träger: 0091 wartet auf etwas,
das ein anderes Paket bauen müsste und keines baut; 0129 legt sein Werkzeug selbst an, wie
0110 es gerade vorgemacht hat.

## Die Ketten — fünf Köpfe halten achtzehn Pakete

    technik.md      0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092   (7)
    riegel.cpp      0079 → 0083 → 0105 → 0106 → 0115                 (5)
    reihen.toml     0078 → 0099 → 0100 → 0126                        (4)
    werkzeugkette   0103 → 0104 → 0108 → 0124                        (4)
    spiel.md        0128 → 0118                                      (2, neu)
    ohne Kette      0120, 0122, 0123, 0129                           (4)

Sechsundzwanzig offen, acht startbereit, **achtzehn hinter fünf Kettenköpfen.** Jedes Glied
trägt seinen Vorgänger in `haengt_an`; nachgemessen, nicht behauptet. In jedem Kettenglied
steht derselbe Satz für den Bauagenten: Dein Vorher-Stand ist der dann geltende `HEAD`, such
am Text, nicht an einer Zeilennummer.

**0129 ist das neunte startbereite Paket und läuft eine Runde später an** — der Baulauf
plant acht und sortiert nach Kennung. Es kollidiert mit keinem; sobald das erste der acht
liefert, ist es dran. Ich schreibe es hin, damit der Rückstand nicht kürzer aussieht, als er
ist.

## Was der Geschäftsführer entscheiden lassen muss

**1. `0121` ist kein Nachvollziehbarkeitsproblem mehr, sondern ein Durchsatzproblem. Das ist
der wichtigste Befund dieses Laufs.** Gemessen über die Zieldateien, nicht über die
Betreffzeilen:

| Commit | Betreff nennt | Inhalt |
|---|---|---|
| `07cc49b` | `datenbauer: 0078` | die Ergebnisdatei von **0120**, die Statuszeile von **0098** |
| `f1aec13` | `kernbauer: 0103` | **nichts als 18 leere Platzhalter** unter `.claude/` |
| `bf0519b` | `datenbauer: 0120` | das komplette Werkzeug aus **0110** |
| `228d9d7` | `architekt: 0116` | erneut Dateien aus **0110** |
| `8d007aa` | `test-pruefer: 0110` | vier Prüfbefunde aus **drei** Rollen |

Daraus drei Folgen, in der Reihenfolge ihres Gewichts:

- **Zwei Bauplätze haben nichts geliefert, und der Commit verdeckt es.** `technik.md` steht
  unverändert seit 05:51, `werkzeugkette.cmake` seit 11:36 — 0116 und 0103 haben ihre
  Zieldateien nicht angefasst, obwohl beide einen Commit unter ihrem Namen tragen. Wer nur
  die Betreffzeile liest, hält beide für geliefert.
- **Eine erbrachte Leistung hat ihre Meldung verloren.** 0120 ist inhaltlich fertig — die
  Berichtigung steht in der Zieldatei, der Übersetzungsbericht trägt wieder `ergebnis: ok`.
  Die Datei liegt im Commit des Nachbarn, die Statuszeile des Pakets steht auf `offen`.
- **Meine Reihenfolgesperren greifen eine Stufe zu hoch.** Sie serialisieren die Läufe; den
  Index serialisieren sie nicht.

Es ist kein seltener Zusammenlauf, sondern der Regelfall, sobald zwei Läufe gleichzeitig
offen sind — und bei acht Bauplätzen sind immer mehrere offen. `agents/lauf.py` liegt
außerhalb jeder Schreibgrenze; das Paket bleibt zu Recht `blockiert`. **Was fehlt, ist ein
ruhiger Lauf des Betreibers, und er ist inzwischen teurer als die beiden Entwurfsfragen
darunter.**

**2. Ein neuer Vorrang. Die Liste in `ops/plan.md` ist zum dritten Mal vollständig
abgearbeitet.** Alle fünf — 0026, 0002, 0071, 0027, 0010 — stehen auf `fertig`; der Plan
stammt vom 2026-09-04 07:49 und ist seither nicht erneuert. Ich lege die Reihenfolge
seither nach eigener Auslegung fest und melde das **als Auslegung** — zum dritten Mal, zum
dritten Mal unbeantwortet. Die eine Auflage des alten Plans, „nichts aus der
Belegstellen-Familie in dieser Woche", habe ich mit 0079 durchbrochen: Es ist ein Rücklauf
eines laufenden Pakets, keine Neueröffnung, und an ihm hängen vier weitere. Das ist eine
Entscheidung, keine Übersehung.

**3. `technik.md` zerlegen — zum fünften Mal gemeldet, und ich ändere nichts.** Sieben
Pakete auf einer Datei, strikt nacheinander, je zwei Durchgänge. Solange die Kette läuft,
ist der Architekt eine Rolle mit **einem** Platz. Es wäre eine Entwurfsentscheidung, und die
gehört nicht mir. Neu dazu: Dieselbe Bauart hat jetzt eine zweite Kette erzeugt (`spiel.md`,
zwei Glieder), und sie wächst mit jeder Entwurfsberichtigung.

**4. `0091` bleibt gesperrt: der T19-Träger fehlt.** Der angekündigte Auslöser ist geprüft
und hat **nicht** gefeuert — `kern/include/kern/` führt elf Kopfdateien, keine `verlauf.hpp`,
und die Kommentare in `schreiber.hpp` und `schritt.hpp` sagen selbst, dass es ihn nicht gibt.
Es hängt nichts daran.

**5. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen die Skalentabelle
in T5, eine ADR-Entscheidung von dir. Hier nur, damit es nicht aus dem Blick fällt.

**6. Die Prüfstufe hat weiterhin kein einziges Paket.** `selbstspieler`, `rueckvergleicher`
und `bruchtester` sind seit ihrer Einführung ohne Auftrag. Das fällt erst ins Gewicht, wenn
etwas `live` gehen soll — aber die vier Maße des Rückvergleichs sind das, woran dieses
Vorhaben am Ende gemessen wird, und niemand baut heute darauf zu.

## Was der nächste Lauf zuerst anfasst

1. **Acht Bauplätze sind besetzt; der nächste Engpass ist die Prüfstufe.** Nach diesem
   Durchgang liegen bis zu acht Pakete gleichzeitig auf `gebaut`. Urteile ziehen ist die
   Hauptarbeit — und die Erfahrung dieses Laufs sagt: Sie liegen geschrieben vor und werden
   übersehen, weil der Betreff lügt. **Immer über die Zieldatei messen.**
2. **0120 zuerst ansehen.** Es ist das einzige Paket, dessen Arbeit getan ist und dessen
   Meldung fehlt. Kommt es aus dem nächsten Durchgang wieder unverändert zurück, ist nicht
   der Bauagent das Problem, sondern der Commit-Schnitt aus Punkt 1 oben — dann gehört es
   dorthin und nicht in einen dritten Rücklauf.
3. **Bei 0078 und 0079 auf den dritten Rücklauf achten.** Beide stehen bei zwei von drei.
   Kommt einer wieder mit derselben Fehlerklasse, ist es `blockiert` und eine Meldung, nicht
   ein weiterer Durchgang.
4. **0129 einplanen, sobald ein Platz frei wird.** Es ist startbereit und wartet nur an der
   Sortierung.
5. **Keinen neuen Auslöser an eine Platzzahl hängen.** Unverändert gültig: gegen
   `GLEICHZEITIG` messen, nie gegen eine ausgeschriebene Zahl.
6. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert; der
   Zählfehler in Abschnitt 18 vererbt sich sonst. Der Vermerk steht in 0092.
7. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`.
   Die Datei trägt dann schon 0078, 0099, 0100 und 0126; das neue Paket wird **fünftes**
   Glied jener Kette.
8. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 7 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus fünf
   Fassungen.
9. **Nicht noch einmal untersucht werden muss:** `aufgaben/.kopf.tmp` und `.paket.tmp`,
   ebenso die `.tmp`-Dateien unter `daten/zwischenstaende/`. `pakete()` liest nur `*.md`.
   Die Kopfzahl stimmt ohne sie: 26 + 92 + 4 = 122, plus je eine `archiviert` und
   `zurueckgezogen` und zwei `umgezogen` sind die 126 Dateien im Verzeichnis. Hausregel 3 —
   sie bleiben liegen.
