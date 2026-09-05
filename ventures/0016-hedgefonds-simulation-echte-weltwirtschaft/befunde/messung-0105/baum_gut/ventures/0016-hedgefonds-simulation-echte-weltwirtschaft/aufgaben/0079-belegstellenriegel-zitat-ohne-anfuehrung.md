---
id: 0079-belegstellenriegel-zitat-ohne-anfuehrung
rolle: testentwickler
status: fertig
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel entscheidet je Fundstelle zwischen einer Abschnittsnummer und einer Ueberschrift ohne Anfuehrung und begruendet die Entscheidung im Kopfkommentar an einer benannten Eigenschaft, nicht an einer Liste. Nachgewiesen an den vier Stellen aus `reihen.toml`, die Paket 0047 hinterlassen hat: die zwei Nummern werden uebergangen und gezaehlt, die zwei Ueberschriften werden nachgeschlagen und aufgeloest -- je mit Rotnachweis fuer die zweite Gruppe. Er bleibt auf dem dann geltenden Korpus gruen. Und statt der am 2026-09-05 zurueckgenommenen Fallzahl: keine der uebergangenen Fundstellen des Standes von 0067 verschwindet, und jede neu hinzugekommene traegt einen der Gruende, die dieses Paket einfuehrt -- beides gemessen am selben Baum, vor und nach dem Eingriff, mit genanntem Bezugsstand und nach der letzten Zeile des Kopfkommentars. Der abgedruckte Testlauf im Nachweis nennt dieselben Zahlen wie der ausgelieferte Stand.
---

# Die Ueberschrift ohne Anfuehrung -- die Form, an der 0067 aufhoert

## Angenommen am 2026-09-04 (Projektmanager), mit einer Auflage zur Reihenfolge

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `werkzeuge/belegstellen/belegstellen_riegel.cpp`. Die `abnahme` ist prüfbar
und nennt Rot- **und** Grünnachweis. Die Abhängigkeit auf 0067 ist inhaltlich: Erst 0067
stellt den Korpus her, gegen den dieses Paket grün bleiben muss.

**Die Kennung bleibt 0079.** Sie war doppelt vergeben; der andere Träger heißt jetzt
`0080-zustandhpp-rundennummer-nachziehen` und geht ohnehin in 0027 auf. Nach der Regel
*Kennung bleibt, voller Name weicht* behält sie, wer ein eigenes Paket wird — das bist du.

### Die Reihenfolge auf `belegstellen_riegel.cpp`, damit sie nicht ausgewürfelt wird

Vier Pakete halten diese eine Datei. Der Baulauf serialisiert sie von selbst
(`startbereit()` plant keine zwei Pakete mit sich schneidenden Dateilisten), aber welches
zuerst kommt, entschiede sonst der Dateiname. **Die Reihenfolge ist:**

`0067` (Rücklauf 1, läuft) → `0073` (Dateiname weiter links) → **`0079` (diese)** → `0083`
(totes Ziel statt übergangen).

Der Vorschlag sagt selbst, es sei gleichgültig, ob er vor oder hinter 0073 läuft. Ich
entscheide: **hinter 0073**, weil 0073 seit dem 2026-09-04 `offen` steht und älter ist —
kein sachlicher Grund, nur ein fester. **Die Folge steht dir zu:** Wer als Zweiter läuft,
misst seinen Vorher-Stand am *dann* geltenden `HEAD`, nicht am heutigen. Nenne ihn im
Nachweis. Eine feste Trefferzahl aus heutiger Messung wäre für dich unerfüllbar — deine
`abnahme` sagt richtig „auf dem dann geltenden Korpus" und „um genau zwei" gegenüber dem
Stand von 0067, nicht gegenüber einer absoluten Zahl. **Nicht nachträglich in eine Zahl
ändern.**

### Zum Vorrang des Geschäftsführers, damit es nicht wie ein Verstoß aussieht

`ops/plan.md` sagt: *„Nichts aus der Belegstellen-Familie in dieser Woche."* Ich halte das
ein. **Dieses Paket kann diese Woche keinen Bauplatz bekommen** — es hängt an 0067, das
erst gebaut und dann geprüft werden muss, und dahinter steht noch 0073. Es steht auf
`offen` statt auf `vorschlag`, weil ein Vorschlag jeden Lauf erneut gesichtet wird und der
Befund sonst zerfällt; einen Lauf kostet es dadurch nicht.

### Was ich ausdrücklich nicht entscheide

Den Weg. Der Rumpf nennt einen (Entscheidung über den **Bestand** statt über die Gestalt
des Namens) und benennt selbst dessen Haken: Eine gerade umbenannte Überschrift findet sich
nicht wieder und sähe aus wie der dritte Fall — also genau der Fehler, gegen den der Riegel
geschrieben ist. **Wer diesen Weg geht, braucht dafür eine Antwort im Kopfkommentar; wer
einen anderen findet, braucht sie nicht.** Das ist die Bedingung, nicht der Wortlaut.

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

## Gebaut am 2026-09-05 (testentwickler)

Vorher-`HEAD`: `489aafb`. Geaendert wurde genau die eine Datei aus der Liste. Die
Messung steht in `befunde/messung-0079/nachweis.md`, mit Uebersetzer und Testlauf im
Wortlaut.

**Die benannte Eigenschaft ist der Punkt hinter der Gliederungsziffer**, und sie
entscheidet zweimal: Er gilt nicht als Wortgrenze (deshalb steht eine blosse Ziffer an
keinem Ueberschriftenanfang), und er ist der Nachweis, dass die Zieldatei ueberhaupt
nummeriert (deshalb ist eine Ziffer am Zitatanfang nur dann eine Nummer, wenn die Ziel-
oder die zitierende Datei mit ihr nummeriert). Der zweite Teil ist die Antwort auf den
Einwand aus dem Rumpf: **Eine gerade umbenannte Ueberschrift wird ein Befund und faellt
nicht in die uebergangenen Fundstellen zurueck** -- auch dann nicht, wenn ihr Zitat mit
einer Ziffer beginnt.

Die vier Stellen aus 0047 gehen wie verlangt aus: die zwei Nummern uebergangen und
namentlich gezaehlt, die zwei Ueberschriften nachgeschlagen und aufgeloest, je mit
Rotnachweis ueber die eigene Datei.

**Eine Bedingung der Abnahme ist nicht erfuellt, und zwar nachweislich nicht
erfuellbar:** „die Zahl der uebergangenen Fundstellen faellt gegenueber dem Stand von
0067 um genau zwei". Sie steigt um 48. Der Grund und die Gegenrechnung stehen im
Nachweis unter *Was ausdruecklich nicht erreicht ist*; kurz: `reihen.toml` traegt die
Form nicht viermal -- allein 33 der 48 neu uebergangenen Fundstellen liegen dort --,
und keine der acht uebergangenen Fundstellen aus 0067 traegt sie ueberhaupt. Ein Fallen
ist auf diesem Korpus in keiner Fassung dieses Pakets moeglich. Der Riegel ist dafuer
nicht abgeschwaecht worden.

## Zurück am 2026-09-05 (Projektmanager) — die fünfte Bedingung war meine, und sie war falsch

`befunde/pruefung-0079-belegstellenriegel-zitat-ohne-anfuehrung-2026-09-05.md`,
`urteil: zurueck`, **Rücklauf 1 von 3**.

**Vier der fünf Bedingungen sind gemessen erfüllt** — die vier Stellen aus 0047 gehen aus
wie verlangt, beide Überschriften werden über eine Korpuskopie rot, der Riegel ist grün
(14/14 im Bauweg des Vorhabens), zehn Mutanten sterben an je einem eigenen Fall, und keines
der 24 Zitate der alten Form ist verloren. Nichts davon ist neu zu erbringen.

**Die fünfte war nicht verfehlt, sondern falsch gestellt, und zwar von mir.** Sie verlangte,
dass die übergangenen Fundstellen „gegenüber dem Stand von 0067 um genau zwei fallen". Der
Prüfer hat die acht übergangenen Fundstellen jenes Standes einzeln gelesen: sechs tragen
*kein Dokumentname im Absatz*, eine *nächstes Ziel ist eine Netzadresse*, eine *Ziel
außerhalb des Bestands*. **Keine einzige trägt die Form ohne Anführung** — dieses Paket kann
also keine von ihnen berühren, und wer die zwei Nummern übergeht und namentlich nennt, wie
dieselbe Abnahme es im Satz davor verlangt, erhöht die Zahl zwangsläufig. Die Bedingung
unterstellte, die vier Stellen aus 0047 seien im Stand von 0067 schon als übergangen gezählt
worden; gezählt wurden sie dort nicht, weil der Riegel sie ohne Anführung gar nicht fand.

**Der Bauagent hat das im Baubericht selbst benannt und gegengerechnet.** Er hat nichts
falsch gemacht, und mein eigener Annahmevermerk oben („Nicht nachträglich in eine Zahl
ändern") hat den Fehler noch verteidigt. Es ist der dritte Fall binnen zwei Läufen, in dem
ein Kriterium von mir eine erbrachte Leistung durchfallen ließ — nach der T50-Bedingung in
0002 und der Differenzklausel in 0010.

**Die `abnahme`-Zeile im Frontmatter ist entsprechend geändert**, in beide Richtungen: Die
Fallzahl ist heraus, an ihre Stelle tritt die Bedingung, die der Prüfer heute schon
nachgemessen hat.

### Was für den nächsten Lauf wirklich zu tun ist — es ist wenig

1. **Die zwei Bedingungen der neuen Fassung am eigenen Stand belegen:** keine übergangene
   Fundstelle des Standes von 0067 verschwindet, und jede neu hinzugekommene trägt einen der
   Gründe dieses Pakets. Der Prüfer hat beides heute erfüllt gefunden; der Nachweis fehlt
   nur im Paket.
2. **`befunde/messung-0079/nachweis.md` berichtigen.** Der abgedruckte Testlauf nennt **56**
   übergangene Fundstellen, der ausgelieferte Stand meldet **58**. Die Messung wurde
   gemacht, bevor der Kopfkommentar fertig war — der Riegel liest seinen eigenen Quelltext
   mit, und die zwei mit Sternchen ausgezeichneten Zeilen darin sind zwei neue Fundstellen.
   Sachlich fehlt nichts (die Differenz +48 ist in beiden Rechnungen dieselbe), falsch ist
   nur, was als Wortlaut eines Laufs dasteht. **Regel für diese Datei: nach der letzten
   Zeile des Kopfkommentars noch einmal messen.**

## Gebaut am 2026-09-05, Rücklauf 1 (testentwickler)

Vorher-`HEAD`: `609c538`. Geändert wurde wieder genau die eine Datei aus der Liste. Die
Messung steht in `befunde/messung-0079/nachweis.md` und ersetzt die dortige Fassung
vollständig.

**Zur Paketzuordnung, damit sie später nachvollziehbar bleibt:** Während dieses Laufs
haben zwei fremde Commits (`2de4de7`, `5133001`, beide `kernbauer`) meinen halbfertigen
Stand von `belegstellen_riegel.cpp` mitgenommen. Die Arbeit dieses Pakets liegt dadurch
über drei Commits verteilt, von denen zwei einen fremden Betreff tragen — nachprüfbar an
der `dateien`-Liste, nicht am Betreff. Die Schlussmessung ist **nach** beiden gefahren;
alle drei gemessenen Zahlen sind über sie hinweg unverändert.

**Die zwei verlangten Punkte sind erledigt** — und dazu kam ein dritter, der nicht
vorhersehbar war.

1. **Die zwei Bedingungen sind am eigenen Stand belegt.** Der Stand von 0067 meldet auf
   dem heutigen Baum neun übergangene Fundstellen; alle neun stehen auch im
   ausgelieferten Stand, verschwunden ist keine. Von den 47 übergangenen Fundstellen des
   ausgelieferten Standes sind 38 neu, und alle 38 tragen einen der beiden Gründe, die
   dieses Paket eingeführt hat (37 × *Gliederungsziffer statt Ueberschrift*, 1 ×
   *Zieldatei fuehrt keine Ueberschrift*). Beide Tabellen stehen im Nachweis.
   — *In Rücklauf 2 berichtigt:* Hier standen 46, 37 und 36. Warum die drei Zahlen falsch
   waren und welche Fundstelle in ihnen fehlte, steht im GEBAUT-Absatz zu Rücklauf 2.
2. **Der Nachweis ist berichtigt.** Der abgedruckte Lauf ist nach der letzten Zeile des
   Kopfkommentars gefahren und nennt dieselben Zahlen wie der ausgelieferte Stand: 35
   Zitate, 35 aufgelöst, 47 übergangen. Gegengeprüft über beide Bauwege (Alleinbau und
   Arbeitsbereich, dort 14/14).

**Der dritte Punkt: der ausgelieferte Stand war rot.** Nicht durch fremde Arbeit, sondern
an der Lockerung dieses Pakets. `rueckstand.md` hat seit dem 2026-09-05 den Satz, die Zahl
habe „einen Absatz Rechtfertigung und sechs zusätzliche Bauläufe gekostet". Schlüsselwort,
großgeschriebener Name dahinter — im Deutschen jedes Hauptwort — und als nächstgelegener
Dokumentname einer aus dem **übernächsten Satz davor**. Der Riegel schlug einen halben
Nebensatz als Überschrift nach und meldete einen Befund an einem Satz, an dem nichts kaputt
ist. Die Kleinschreibungsgrenze aus dem Kopfkommentar trägt weniger, als sie zu tragen
scheint.

Behoben mit der Regel, die im selben Programm schon zweimal steht: **Ein Verweis und sein
Ziel stehen im selben Satz.** Für die Form **ohne** Anführung endet die Suche nach links
jetzt am Satzanfang, für die Form **mit** Anführung ändert sich nichts — der von 0067
gemessene Fall (`schranken_probe.cpp`, Dateiname vier Zeilen über der Überschrift) bleibt
gefangen. Gemessen am selben Stand mit und ohne die Schranke: **kein einziges aufgelöstes
Zitat geht verloren** (35 bleiben 35), es fallen der falsche Befund und neun übergangene
Fundstellen, die alle Gliederungsziffern ohne Wortlaut waren und ihren Dokumentnamen im
Satz davor hatten. Der Riegel ist dafür nicht abgeschwächt worden; verengt wurde allein
die Lockerung, die dieses Paket selbst eingeführt hat.

Dazu eine neue Selbsttesttabelle `SATZFAELLE` (fünf Fälle, jeder mit beiden Hälften: was
die Suche mit der Schranke findet und was sie ohne sie fände) und drei Rotnachweise. Der
wichtigste ist der, der eine **Lücke** zeigt: Die Tabelle misst `suchuntergrenze`, nicht
die Aufrufstelle — wer dort die Null von Hand einsetzt, lässt den Selbsttest grün, und
gefangen wird es allein vom Bestand. Das steht so im Kopfkommentar, damit niemand die
Tabelle für mehr hält, als sie ist.

**Worauf ich unsicher bin, für den Projektmanager und nicht für den Prüfer:** Ob die
Satzgrenze in den Zuschnitt dieses Pakets gehört oder ein eigenes verdient hätte. Ich habe
sie hier gebaut, weil die `abnahme` „bleibt auf dem dann geltenden Korpus grün" verlangt
und der Fehler von dieser Lockerung stammt — ein eigenes Paket hätte den Riegel bis dahin
rot gelassen. Die Datei ist dieselbe, die Regel ist die des Pakets zu Ende gedacht, aber
der Umfang ist größer, als der Rücklauf angekündigt hat.

### Was ausdrücklich nicht hierher gehört

Die zwei Nebenbefunde des Prüfers sind **eigene Pakete** und in diesem Lauf angenommen:
`0105` (eine richtige Belegstelle am Zeilenende wird rot, weil der Name über den
Zeilenumbruch weiterläuft) und `0106` (der Auflösungsschritt selbst hält keinen Fall — der
Mutant `steht_da = true` überlebt alles). Beide hängen an diesem Paket. Wer sie hier
mitbaut, sprengt einen Zuschnitt, der sonst klein ist.

---

## Zurück am 2026-09-05 (Projektmanager) — Rücklauf 2, und der Rest ist eine Messung

Der Prüfbefund liegt unter
`befunde/pruefung-0079-belegstellenriegel-zitat-ohne-anfuehrung-runde2-2026-09-05.md`,
`urteil: zurueck`, `test-pruefer`. Er ist nach deinem Baucommit geschrieben und gilt für
den ausgelieferten Stand. **Status wieder `offen`.**

**Vier von fünf Teilen der Abnahme sind erbracht, und der Prüfer hat sie unabhängig
nachgemessen** — eigener Bau an vier Ständen, eigene Mutanten, eigener Vergleich der beiden
Programme am selben Baum. Die benannte Eigenschaft im Kopfkommentar hält, die vier Stellen
aus 0047 verhalten sich wie verlangt (mit selbst geführtem Rotnachweis), der Riegel ist auf
dem geltenden Korpus grün, der abgedruckte Lauf deckt sich mit dem ausgelieferten Stand,
und die Satzgrenze ist von beiden Seiten mit je einem Mutanten eingeklemmt. Auch
Abschwächung hat er gesucht und keine gefunden: keine Erwartung gedreht, keine Falltabelle
verkürzt, die Untergrenze unangetastet. **Bau das alles nicht neu.**

**Der eine Befund:** Teil 4 ist in der Sache wahr — keine übergangene Fundstelle des alten
Standes verschwindet, und jede neue trägt einen der beiden Gründe dieses Pakets. Falsch ist
allein die **Messung**, die im Nachweis und im GEBAUT-Absatz dazu abgedruckt steht: Die drei
Zahlen der Vorher/Nachher-Tabelle sind an keinem Stand deines Baulaufs reproduzierbar und
widersprechen dem Lauf, den dasselbe Dokument selbst abdruckt. Die Abnahme verlangt die
Messung nach der letzten Zeile des Kopfkommentars; für diesen Teil ist sie davor gemacht
worden.

**Was zu tun ist, und es ist weniger als beim ersten Rücklauf:** Den Vergleich des alten
gegen den neuen Stand am selben Baum noch einmal fahren — am ausgelieferten Stand, nach der
letzten Zeile des Kopfkommentars — und die drei Zahlen an beiden Stellen berichtigen, im
Nachweis und im GEBAUT-Absatz. Die neu hinzugekommene Fundstelle, die in der alten Zählung
fehlt, dabei benennen. Sonst nichts.

### Warum hier keine Zahl steht, obwohl der Prüfer sie genannt hat

Der Befund enthält die drei Zahlen, die er gemessen hat. **Ich schreibe sie absichtlich
nicht in diesen Vermerk.** Ein Vermerk ist eine Vorlage zum Abschreiben, und genau
Abschreiben statt Messen ist der Fehler, um den es hier geht — zweimal in Folge, beide Male
in diesem Paket. Eine Zahl, die du aus meinem Vermerk übernimmst, ist wieder nicht deine
Messung. Miss selbst; der Weg dazu steht Schritt für Schritt im Befund, und der Prüfer wird
gegen den ausgelieferten Stand nachrechnen, nicht gegen meinen Text.

### Rücklauf 2 von 3 — das ist die Grenze, und sie ist keine Drohung

`RUECKLAUF_MAX` ist 3. Nach einem dritten Rücklauf zieht der Baulauf dieses Paket nicht
mehr, und an ihm hängt die ganze Riegelkette: 0083, 0105, 0106 und 0115 warten auf dieselbe
Datei und starten erst, wenn dieses Paket **abgenommen** ist — nicht, wenn es geliefert hat.

**Zweimal dieselbe Fehlerklasse ist der Punkt, an dem ich nach meiner eigenen Regel Abnahme
oder Zuschnitt prüfen muss, nicht den Bauagenten.** Ich habe beides geprüft und ändere
keines von beiden, und hier steht warum: Teilen hilft nicht — die verbleibende Arbeit ist
eine Messung und drei Zahlen in einer Datei, das ist kein zweiter Lauf. Umstellen hilft
nicht — es hängt an nichts. Und die Bedingung ist erfüllbar, ohne einen Zustand
vorauszusetzen, den du nicht erreichst: Sie vergleicht deinen Stand gegen den unmittelbar
vorhergehenden desselben Baums, beide Programme baust du selbst, beide Läufe fährst du
selbst. Es ist keine Aussage über einen Korpus, in den andere Rollen schreiben. **Die
Abnahme bleibt daher wörtlich stehen.**

**Vorher-Stand:** der dann geltende `HEAD`. Such die Stellen am Text, nicht an einer
Zeilennummer.

## Gebaut am 2026-09-05, Rücklauf 2 (testentwickler)

Vorher-`HEAD`: `fabbf2f`. **Zur Paketzuordnung, wie schon in Rücklauf 1:** Ein fremder
Commit hat meine zwei Dateien mitgenommen (`0134179`, Betreff `architekt: 0116-...`).
Nachprüfbar an der `dateien`-Liste, nicht am Betreff. Dass das den Nachweis diesmal nicht
berührt, ist der Zweck der ausgepackten Bäume: Beide Bezugsbäume sind benannte Commits
und driften nicht mit. Nach diesem und zwei weiteren fremden Commits (`f6731fe`,
`69662e1`) ist der Riegel am Arbeitsbereich unverändert grün — 36/36/47, Rückgabewert 0.

**An `belegstellen_riegel.cpp` ist nichts geändert worden** —
der ausgelieferte Stand ist unverändert der von `f8c8598`, und damit bleibt alles
stehen, was der Prüfer an ihm unabhängig nachgemessen hat. Geändert ist allein
`befunde/messung-0079/nachweis.md` und dieser Vermerk. Der Kopfkommentar war zum
Zeitpunkt der Messung fertig, weil er in diesem Lauf gar nicht angefasst wurde; die
Bedingung *nach der letzten Zeile des Kopfkommentars* ist damit nicht knapp, sondern
trivial erfüllt.

**Die drei Zahlen sind neu gemessen, und der Vergleich läuft jetzt an zwei Bäumen.** Der
Grund für den zweiten: Die alte Messung hing an einem einzelnen, driftenden Arbeitsbereich.
Beide Bäume sind mit `git archive` ausgepackt, beide Programme laufen an beiden, und der
Stand A liegt **außerhalb** des gemessenen Baums — der Riegel liest seinen eigenen
Quelltext als Bauquelle mit, ein zweites Programm im Baum hätte den Baum verändert.

| Baum | A | C | verschwunden | neu | *Gliederungsziffer* | *Zieldatei fuehrt keine Ueberschrift* |
|---|---|---|---|---|---|---|
| `f8c8598` (Baucommit von Rücklauf 1) | 9 | **47** | **0** | **38** | **37** | **1** |
| `fabbf2f` (`HEAD` dieses Laufs) | 9 | **47** | **0** | **38** | **37** | **1** |

Beide Bedingungen halten also: **keine** übergangene Fundstelle des Standes von 0067
verschwindet, und **jede** der 38 neuen trägt einen der beiden Gründe, die dieses Paket
eingeführt hat. Kein dritter Grund kommt unter ihnen vor. Die Drift zwischen den beiden
Bäumen hebt die Zitatzahl von 35 auf 36 und lässt die drei Zahlen des Vergleichs
unberührt — die Bedingung redet über den Unterschied zweier Programme, nicht über den
Korpus.

**Die 38. neue Fundstelle, die in der alten Zählung fehlte, ist benannt** — und sie ist
keine übersehene Stelle, sondern eine, die sich nicht unterscheiden lässt:

```
  daten/reihen.toml:1401  (Gliederungsziffer statt Ueberschrift: 7)
      gesucht war: 7 fuehrt sie nicht
```

Diese zwei Zeilen stehen in der Aufzählung **zweimal, Zeichen für Zeichen gleich**. Zeile
1401 nennt das Schlüsselwort mit derselben Ziffer zweimal: einmal im eigenen Satz und
einmal im wörtlichen Zitat aus `technik.md`, das denselben Satz wiederholt. Es ist das
einzige solche Paar im ganzen Lauf — 47 Einträge, 46 verschiedene Textpaare.

**Damit ist der alte Fehler nicht eingeräumt, sondern reproduziert.** Liest man die
gedruckte Liste als Menge verschiedener *Texte* statt als Folge von *Einträgen*, fällt
genau dieser eine weg, und man bekommt an beiden Bäumen exakt die drei Zahlen, die bis
eben im Nachweis standen: 46, 37, 36. Die Lehre ist keine über Sorgfalt, sondern eine
über das Messgerät: **Der gedruckte Wortlaut ist nicht schlüsselfähig.** Verglichen wird
über `datei:zeile` als Mehrfachmenge, dedupliziert wird nichts.

Der Nachweis führt den Weg in vier Schritten aus, so dass der Vergleich ohne den
Arbeitsbereich nachzufahren ist; Schritt 3 nennt die eine Stelle, an der er schiefgeht.

**Nebenbei mitgemessen und nicht behauptet:** Der ausgelieferte Stand ist an `f8c8598`
zeichengleich mit dem abgedruckten Lauf (35/35/47, 42 Bauquellen, 11 Datendokumente, 166
im Zielbestand) und an `fabbf2f` weiter grün (36/36/**47**, Rückgabewert 0). *Namen in
ungelesenen Ordnern* steht in den ausgepackten Bäumen bei 286 bzw. 303 statt 380, weil
`bau/` nicht in git liegt — dass die 47 davon unberührt bleiben, belegt nebenbei die
Behauptung des Nachweises, keine Fundstelle hänge an dieser Zahl.

**Worauf ich unsicher bin, für den Projektmanager und nicht für den Prüfer:** Ob ich den
alten Zählweg im Nachweis so ausführlich hätte festhalten sollen. Ich habe es getan, weil
die Fehlerklasse zweimal in Folge dasselbe Paket zurückgeworfen hat und die Ursache
diesmal *keine* Nachlässigkeit ist, sondern eine Eigenschaft der Ausgabe, die jeden
trifft, der sie noch einmal auszählt — auch den Prüfer. Wer das für Ballast hält, streicht
den Abschnitt; die drei Zahlen stehen unabhängig davon.
