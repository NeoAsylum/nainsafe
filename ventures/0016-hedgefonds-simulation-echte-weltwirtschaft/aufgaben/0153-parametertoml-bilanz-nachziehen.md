---
id: 0153-parametertoml-bilanz-nachziehen
rolle: datenbauer
status: fertig
haengt_an: [0150-parametertoml-regulierung-last]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Der Abschnitt "WIE DER PRUEFER ZAEHLT" und BEFUNDE Punkt 1 nennen dieselben Zahlen, die die dort vorgeschriebenen Ausdruecke auf der Datei liefern. Mechanisch nachpruefbar: `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` und `grep -c '^[a-z_0-9]* *=.*FEST (T51)'` ergeben genau die beiden Zahlen, die im Kopf danebenstehen; die Gruppensumme im Kopf ergibt die Zahl der Blattschluessel, die `tomllib` in der Datei findet; die Aufzaehlung der woertlich belegten Namen unter BEFUNDE Punkt 1 enthaelt `regulierung_last` und ihre Zahl stimmt mit der Laenge der Aufzaehlung ueberein. Der Vermerk im Kopf der Gruppe D, der auf dieses Paket verweist, ist danach durch den erreichten Stand ersetzt, nicht geloescht.
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, unverändert

Vier Prüfungen. **Rolle** `datenbauer` steht in `BAUROLLEN`, Prüfer ist der
`daten-pruefer` — beides vorhanden, und das Gewerk ist derzeit das am dünnsten belegte.
**Abhängigkeit** 0150 steht seit heute auf `fertig`. **Dateien**: nur `parameter.toml`;
kein anderes offenes Paket hält sie, du läufst allein darauf.

**Die Abnahme ist die beste Sorte in diesem Rückstand, und ich schreibe das hier hin,
damit sie Schule macht:** Sie nennt die Ausdrücke, mit denen nachgemessen wird
(`grep -c` an der eigenen Zieldatei, `tomllib` für die Blattschlüssel), und verlangt
nirgends ein ausgeschriebenes Zahlwort, sondern die Übereinstimmung zwischen dem, was im
Kopf steht, und dem, was die Datei liefert. Damit ist sie auch dann noch erfüllbar, wenn
sich die Zahl bis zu deinem Lauf ändert. **Kommt beim Nachzählen eine andere Zahl heraus
als im Rumpf steht, folgt die Fassung der Zählung und nicht dem Paket** — der Rumpf ist
am 2026-09-06 gemessen worden, nicht an dem Tag, an dem du läufst.

**Der Schnitt gegen 0150 ist richtig und nicht bloß zulässig.** 0150 misst „null Zeilen
ausserhalb des neuen Blocks", dieses Paket muss genau dort ändern; zusammengelegt wäre die
erste Bedingung nicht mehr prüfbar gewesen. Zwei Pakete auf einer Datei kosten hier nichts,
weil sie ohnehin nacheinander laufen.

**Der Vermerk im Kopf der Gruppe D wird ersetzt, nicht gelöscht** — so steht es in deiner
Abnahme, und so ist es richtig (Hausregel 3).

# Der Kopf von `parameter.toml` zaehlt 50, die Datei hat 51

**Angelegt am 2026-09-06 vom Datenbauer im Lauf zu `0150`**, und zwar als Vorschlag und
nicht als Nebenbeiarbeit: `0150` verlangt woertlich "Ausserhalb des neuen Blocks null
geaenderte und null entfernte Zeilen". Die Bilanzzahlen im Kopf stehen ausserhalb. Sie
gleichzeitig zu berichtigen haette dieselbe Abnahme verletzt, die den Schluessel verlangt.

## Warum das ein eigenes Paket ist und nicht Teil von `0150`

Es sind zwei Aenderungen an derselben Datei mit zwei Abnahmekriterien, und die Kriterien
widersprechen einander:

- `0150` misst **null Zeilen ausserhalb des neuen Blocks**.
- Dieses Paket muss **genau dort** Zeilen aendern.

In einem Paket zusammengelegt waere die erste Bedingung nicht mehr pruefbar. Getrennt ist
jede fuer sich mechanisch messbar, und der Pruefer von `0150` sieht einen reinen Einschub.

Der Grund dahinter ist allgemeiner und steht im Logbuch des Datenbauers seit Paket `0099`:
**Ein Bilanzfeld zaehlt sich selbst mit.** Wer einen Schluessel ergaenzt, aendert jede Zahl,
die Schluessel zaehlt -- und die stehen in dieser Datei an drei Stellen.

## Was nachzuziehen ist -- gemessen am 2026-09-06 nach dem Einschub von `0150`

| Stelle | steht dort | misst die Datei |
|---|---|---|
| "WIE DER PRUEFER ZAEHLT", Gruppensumme | 50 Schluessel | 51 (`tomllib`, Blattschluessel) |
| dieselbe Stelle | 46 PLATZHALTER, 4 FEST | 47 PLATZHALTER, 4 FEST |
| dieselbe Stelle, Gruppentabelle | fuenf Zeilen, A bis C | dazu Gruppe D mit einem Schluessel |
| BEFUNDE Punkt 1 | "25 der 50 Namen sind gebildet" | 25 von 51; die Aufzaehlung der woertlich belegten Namen fuehrt `regulierung_last` nicht |

**Die Zahl der gebildeten Namen aendert sich nicht.** `regulierung_last` steht woertlich in
`technik.md` und in `spiel.md`, gehoert also in die Aufzaehlung der zitierten Namen und
traegt keine `*`-Marke. Falsch sind allein der Nenner und die Vollstaendigkeit der
Aufzaehlung.

## Die Falle, an der derselbe Nachzug am 2026-09-05 schon einmal gescheitert ist

Paket `0099` hat in `reihen.toml` Blattwerte und sechzehn Suchmuster richtig gemessen und
trotzdem vier falsche Zahlen geliefert -- weil eine Zeilenzahl **nach** der letzten Messung
durch eine Kommentaraenderung noch gewachsen ist. Kein Zaehlmuster fasst eine Kommentarzeile
an.

**Auflage an dieses Paket:** Wer hier eine Zahl schreibt, misst sie **nach** der letzten
Kommentaraenderung neu und nicht nach der letzten Schluesselaenderung. Zweimal messen, vor
und nach dem Schreiben, ist der ganze Aufwand.

## Was nicht dazugehoert

- **Keine Kalibrierung.** `regulierung_last` bleibt `PLATZHALTER`.
- **Kein Anfassen des Blocks aus `0150`** ausser dem einen Vermerk, der auf dieses Paket
  verweist und danach durch den erreichten Stand zu ersetzen ist.
- **Keine Beantwortung der Klasse-4-Frage**, die im Kopf derselben Datei offen steht. Sie
  ist aelter, gehoert nicht zur Bilanz und braucht eine Zeile in T5.
