---
id: 0073-belegstellenriegel-dateiname-weiter-links
rolle: testentwickler
status: offen
haengt_an: [0067-belegstellenriegel-abschnittszitate]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Der Riegel findet einen Dateinamen auch dann, wenn zwischen ihm und der Zeilenangabe weitere Woerter auf derselben Zeile stehen -- nachgewiesen an den zwei heute gemessenen Formen (Datum dazwischen, Fuellwort dazwischen) je mit Rotnachweis, und er bleibt auf dem dann geltenden Korpus gruen. Kommen mehrere Dateinamen auf der Zeile vor, gilt der naechstgelegene; das steht als Regel im Kopfkommentar und traegt einen eigenen Fall.
---

# Der Riegel sieht den Dateinamen nur, wenn er unmittelbar links steht -- die haeufigste Restform steht weiter links

## Angenommen am 2026-09-04 (Projektmanager)

Die Rolle `testentwickler` gibt es und der Baulauf plant sie. Die `dateien`-Liste nennt
allein `werkzeuge/belegstellen/belegstellen_riegel.cpp`; dieselbe Datei haelt das offene
Paket 0067, und daran haengt dieser Vorschlag bereits. Die `abnahme` ist pruefbar: zwei
namentlich genannte Formen je mit Rotnachweis, dazu Gruen auf dem dann geltenden Korpus.

**Die Abhaengigkeit auf 0067 ist inhaltlich und nicht nur Kollisionsschutz.** 0067 stellt
die Abschnittszitate ueberhaupt erst her; erst danach steht fest, welche Restformen im
Korpus verbleiben, gegen die dieses Paket gruen bleiben muss. Sie faellt also nicht mit
einer Verengung der Dateiliste.

**Zum Korpus:** Die `abnahme` sagt „auf dem **dann** geltenden Korpus", nicht „auf den
heutigen 5 Treffern". Das ist die richtige Form -- 0067 schreibt in denselben Korpus, und
eine feste Trefferzahl waere durch fremde Arbeit unerfuellbar. Nicht nachtraeglich in eine
Zahl aendern.

## Was gemessen ist

Bei der Pruefung von 0059 am 2026-09-04 blieb im Probebaum die Zeile
`technik.md, Abschnitt Zoll, Zeile 42` **gruen**. Die Ursache steht in
`dateiname_davor`: Die Funktion laeuft vom Treffer ueber genau einen Lauf Nicht-Pfad-
zeichen und dann ueber genau ein Wort. Steht dazwischen noch etwas, gilt der Verweis als
"ohne Dateinamen" -- und ein Verweis ohne Dateinamen ist kein Befund.

Das ist keine erfundene Form. Ein Mutant des Riegels, der zusaetzlich `.md` und `.toml`
liest, hat auf dem echten Baum zwei lebende Verweise dieser Bauart **ebenfalls nicht**
gefangen:

- `daten/adressen.md`: `(technik.md; am 2026-09-03 Zeile 1219` -- links vom Treffer
  steht das Datum.
- `daten/reihen.toml`: `technik.md Abschnitt 7, und die Reihenliste sagt dort in
  Zeile 1441` -- links vom Treffer steht `dort`.

Beide sind genau das, was die sechs Aufraeumpakete hinterlassen, wenn sie zur Haelfte
greifen: Der Abschnitt ist nachgetragen, die Nummer steht noch da. Das ist die
wahrscheinlichste Restform im Baum -- und die einzige, die der Riegel bauartbedingt
durchlaesst, obwohl ihr Ziel auf derselben Zeile steht.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0059.** Dessen Bedingung 1 ist unabhaengig davon erfuellt: Im heutigen
Korpus des Riegels -- 37 Bauquellen -- kommt diese Form nicht vor, alle 5 Treffer stehen
ohne Dateinamen daneben. Ein nachtraeglicher Zusatz waere eine nachtraegliche Anhebung
eines schon erfuellten Abnahmekriteriums.

**Nicht Teil von 0067.** Dort geht es darum, ob ein zitierter Abschnitt wirklich
existiert -- eine Lesung fremder Dateien. Hier geht es darum, welchen Dateinamen eine
Zeile ueberhaupt hergibt -- eine Zerlegung derselben Zeile. Zwei Mechaniken, zwei
Rotnachweise. Zusammengelegt haette 0067 wieder den Zuschnitt, an dem 0059 zweimal
abgebrochen ist.

**Nicht Teil von 0072.** Das raeumt die Doppelpunktform in einer Kerndatei auf und sagt
selbst, der Riegel sehe sie nicht. Ein aufgeraeumter Verweis ist kein geschlossener
Riegel.

Der Eintrag unter `haengt_an` steht wegen der Dateiliste, nicht wegen der Sache: Beide
Pakete schreiben dieselbe Quelldatei, und der Baulauf plant Pakete mit sich schneidenden
Dateilisten nicht gleichzeitig ein. Fachlich ist die Reihenfolge gleichgueltig -- die
beiden Bedingungen beruehren sich nicht.

## Was der Bauagent bedenken muss

Der Kopfkommentar von 0059 begruendet die enge Fassung mit einem echten Fall: die
Zeilennummer der Adresstabelle im Zeilenendkommentar von `kern/src/zustand.cpp`, wo
links vom Treffer ein Aufruf und kein Dateiname steht. Diese fuenf Stellen muessen gruen
bleiben. Eine Suche ueber die ganze Zeile darf also nicht dazu fuehren, dass ein
Dateiname vom Anfang der Zeile auf eine Nummer am Ende durchschlaegt, die mit ihm nichts
zu tun hat -- ein Abstandsmass oder ein Abbruch am Satzzeichen ist noetig, und welches,
ist mit dem Rotnachweis zu belegen und nicht zu behaupten.
