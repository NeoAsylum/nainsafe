---
id: 0079-belegstellenriegel-zitat-ohne-anfuehrung
rolle: testentwickler
status: gebaut
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel entscheidet je Fundstelle zwischen einer Abschnittsnummer und einer Ueberschrift ohne Anfuehrung und begruendet die Entscheidung im Kopfkommentar an einer benannten Eigenschaft, nicht an einer Liste. Nachgewiesen an den vier Stellen aus `reihen.toml`, die Paket 0047 hinterlassen hat: die zwei Nummern werden uebergangen und gezaehlt, die zwei Ueberschriften werden nachgeschlagen und aufgeloest -- je mit Rotnachweis fuer die zweite Gruppe. Er bleibt auf dem dann geltenden Korpus gruen, und die Zahl der uebergangenen Fundstellen faellt gegenueber dem Stand von 0067 um genau zwei.
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
