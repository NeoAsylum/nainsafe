---
id: 0078-reihentoml-preisbasis-nach-t53-nachziehen
rolle: datenbauer
status: offen
haengt_an: [0026-klasse-2-preisbasis]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die fuenf Bedingungen im Abschnitt "Abnahme". Bedingung 5 (die Selbstmessungen) ist die, an der dieses Feld dreimal gescheitert ist -- sie wird nach der letzten Schreibbewegung gemessen, nicht vorher, und mit genanntem Bezugsstand.
---

# `reihen.toml` führt einen Widerspruch weiter, den `technik.md` T53 entschieden hat

Angelegt vom Projektmanager am 2026-09-04 aus **Meldung 2** des Architekten in
`specs/0016-…/technik.md`, Abschnitt 17. Er kann sie nicht selbst ausführen: `daten/` liegt
außerhalb seines Zielverzeichnisses, und er hat sie deshalb als Meldung abgelegt.

**Nachgemessen, bevor ich das Paket angelegt habe** — seine Behauptung, der Übertrag
existiere nirgends, stimmt: `grep -lE 'Ausfuhrpreisindex|Reihe 20|Deflator'` über alle
Aufgabendateien trifft nur `0025` und `0026`, also die beiden Quellen und keinen Auftrag.

## Der Sachverhalt

`technik.md` T53 hat entschieden, was mit einer Klasse-2-Reihe geschieht, die in laufenden
Preisen ankommt: **Sie wird beim Jahrgangsbau deflationiert**, mit einem benannten Deflator.
Betroffen sind die 40 Handelsströme der Reihe 14 aus CEPII BACI (gemessen laufend,
„in thousands current USD").

`reihen.toml` weiß davon nichts und führt an drei Stellen weiter, die Frage sei offen:

1. **Reihe 14, Feld `offen`, erster Eintrag** — „Vier Möglichkeiten sind aufgezählt und keine
   gewählt … Diese Datei entscheidet nichts davon." Eine davon **ist** jetzt gewählt.
2. **`[[widerspruch]]` Nr. 9**, Feld `entscheidet` — „Architekt: ein Deflatorschritt in der
   Umrechnung der Reihe 14 **oder** eine Festlegung in T5 Klasse 2". Der Architekt hat
   geantwortet; das Feld fragt weiter.
3. **Reihe 16, Feld `offen`, erster Eintrag** — trägt denselben Widerspruch über den
   Quotienten `H/N` weiter. T53 sagt jetzt, dass beide Seiten dieselbe Preisbasis tragen.

Das ist keine Schönheitsfrage: Solange die Datei den Widerspruch als offen führt, liest die
nächste Rolle eine Entscheidung als ungetroffen, die getroffen ist — und `[[widerspruch]]`
ist genau die Liste, in der diese Datei ihre ungelösten Fälle sammelt.

## Was du tust

Du **trägst nach, was T53 entschieden hat.** Lies T53 im Wortlaut; er ist die Vorgabe, diese
Datei ist ihr Abbild.

1. **Reihe 14** bekommt den Deflatorschritt in ihrer Umrechnung, mit dem Deflator, den T53
   benennt, samt Quelle und Basisjahr **aus T53** — nicht aus eigener Suche.
2. **Reihe 14, Feld `offen`:** Der Eintrag, der die vier Möglichkeiten aufzählt, ist erledigt
   und geht heraus. Was von ihm bleibt — etwa die Restgröße, die T53 ausdrücklich als
   ungemessen führt —, bleibt als eigener, kleinerer Eintrag stehen.
3. **`[[widerspruch]]` Nr. 9:** trägt die Auflösung, mit T53 als Fundstelle.
4. **Reihe 16:** Die Herkunft von `N` ist nach T53 **Reihe 1 mal dem Sektoranteil aus
   Reihe 2**; die Datei führt heute „abgeleitet aus Reihe 14 (H) und Reihe 2 (N)" und nennt
   Reihe 1 nicht. Der dritte Lauf des Architekten hat genau das gefunden. Nachziehen, und
   der `offen`-Eintrag zur Preisbasis geht heraus.

## Was ausdrücklich NICHT dazugehört — Reihe 20

T53 nennt eine neue Reihe des Jahrgangs, den **Ausfuhrpreisindex der Welt**, und der
Architekt hat ihre Zeile in Abschnitt 17 fertig hingelegt. **Sie kommt trotzdem nicht in
diesem Paket in die Datei, und der Grund ist eine Reihenfolge:**

Die **Reihenliste in `technik.md` Abschnitt 7 führt Reihe 20 noch nicht.** Der Architekt hat
sie dort bewusst nicht eingetragen, weil dieselbe Tabelle an zwei offenen Fragen des
Rückstands hängt und ein zweites Paket sie anfassen wird. Trüge `reihen.toml` die Reihe 20
schon, liefe die Datei ihrer Vorgabe **voraus** — und diese Datei hätte einen neuen
Widerspruch derselben Bauart, wie der ist, den sie hier gerade loswird. Genau das wäre der
Fehler, gegen den dieses Paket antritt, mit umgekehrtem Vorzeichen.

Reihe 20 kommt in einem Folgepaket, nachdem das nächste Architektenpaket die Reihenliste
nachgezogen hat. **Der zweite Grund ist der Umfang:** Ein neuer `[[reihe]]`-Block verschiebt
sieben Selbstmessungen in `[pruefweg]` auf einmal (siehe Bedingung 5). Beides zusammen ist
kein Lauf.

## Was du sonst nicht tust

- **Keine eigene Quellensuche.** Findest du, dass T53 einen Deflator nennt, den die Datei
  nicht führen kann, ist das ein Befund an den Architekten — melden, nicht ersetzen.
- **Keine Blattwerte anfassen, die T53 nicht berührt.** Insbesondere nicht `quellenwahl` von
  Reihe 1, nicht die Lizenzblöcke, nicht die Deckungsblöcke.
- **Nichts an Reihe 9.** Die ist gerade mit 0065 abgenommen worden.
- **Du gibst keinen Rechtsrat** und legst keine Lizenz neu aus.

## Abnahme

1. **Die drei Stellen tragen die Entscheidung.** Reihe 14 (`offen` und Umrechnung),
   `[[widerspruch]]` Nr. 9 (`entscheidet`) und Reihe 16 (`offen`, Herkunft) sagen, was T53
   entschieden hat, und keine von ihnen führt die Frage weiter als offen.
2. **Jede übernommene Angabe nennt T53 als Fundstelle** — Deflator, Quelle, Basisjahr. Eine
   Zahl ohne Fundstelle ist ein Rücklauf. **Keine Zeilennummer**: Abschnittsüberschrift und
   Zitat, wie in dieser Datei üblich, weil die Nummer schneller wandert als das Paket.
3. **Was T53 offen lässt, bleibt offen.** T53 führt die Restgröße zwischen dem Weltausfuhr-
   index und den wahren bilateralen Deflatoren ausdrücklich als ungemessen. Steht sie
   danach als gemessen oder gar nicht mehr da, ist das ein Rücklauf. Eine erledigte Frage
   verschwindet, eine offene wird kleiner — sie verschwindet nicht mit.
4. **Reihe 20 kommt nicht vor.** `grep -c 'Ausfuhrpreisindex' daten/reihen.toml` darf durch
   diesen Lauf nicht steigen, außer der Deflatorname aus T53 enthält das Wort — dann steht im
   Ergebnis, an welcher Stelle und warum, und ein neuer `[[reihe]]`-Block entsteht trotzdem
   nicht.
5. **Die Selbstmessungen stimmen nach dem letzten Schreiben — das ist die Bedingung, an der
   `pruefweg.toml_geprueft` dreimal gescheitert ist.** Verlangt ist beides:
   - **Ein genannter Bezugsstand** (Commit-Kennung, deren Fassung dieser Datei mit deinem
     Arbeitsbaum vor dem Lauf übereinstimmt), und die Messung **nach** deiner letzten
     Schreibbewegung an dieser Datei wiederholt. Eine Messung, die vor der letzten Änderung
     an der Datei geschrieben wurde, die sie misst, ist der Fehler selbst und kein Nachweis.
   - **Die Muster einzeln neu gezählt**, nicht als Summe: die sieben Schnitte `schnitt_1` bis
     `schnitt_7`. Ändert dein Eingriff eine dieser Zahlen — ein zusätzlicher
     `[[reihe.umrechnung]]`-Block hebt die 113 aus `schnitt_3` —, ziehst du sie nach **und
     nennst die alte daneben**. Bleiben sie gleich, schreibst du hin, dass du sie gezählt
     hast, nicht dass sie gleich „sind".

   **Bei `schnitt_1` zusätzlich die Trefferkontexte vergleichen**, nicht nur die Zahl. Der
   Lauf von 0065 hat das vorgemacht: Eine gleiche Zahl aus anderen Stellen wäre sonst
   unbemerkt geblieben.

**Nachweisort:** dieselbe Staffelung wie in 0062 und 0065 — zuerst `$TMPDIR` außerhalb des
Repos, sonst unterhalb von `befunde/`, sonst ausgewiesene Nichtmessung mit Begründung.
Bekommt dein Lauf kein ausführbares Werkzeug, ist `Grep` für alle sieben Schnitte
ausreichend; der Parserlauf ist dann die ausgewiesene Nichtmessung und **kein** Rücklauf.

## Was ausdrücklich kein Befund ist

- **Die Wortwahl.** Wo `specs/` und der Kopf dieser Datei schweigen, gilt deine Entscheidung.
- **Dass der Eingriff größer ausfällt als hier beschrieben**, wenn T53 mehr verlangt. T53 ist
  die Vorgabe, dieses Paket ist ihre Zusammenfassung — im Zweifel gilt T53, und der
  Unterschied gehört in dein Ergebnis.
- **Ein Widerspruch, den du dabei findest und der nicht in der Liste steht.** Er wird
  gemeldet, nicht nebenbei aufgelöst.

## Rückläufe

0.
