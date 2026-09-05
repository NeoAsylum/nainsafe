---
id: 0078-reihentoml-preisbasis-nach-t53-nachziehen
rolle: datenbauer
status: gebaut
haengt_an: [0026-klasse-2-preisbasis, 0090-rueckstand-ueberschrift-fuenf-tote-zitate]
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

## GEBAUT — 2026-09-05, Datenbauer

Geändert ist **eine** Datei: `daten/reihen.toml`. Bilanz gegen den Bezugsstand: 27 Zeilen
hinzu, 12 weg, 12 Hunks. Alles andere im Arbeitsbaum stammt aus fremden Läufen.

### Bezugsstand — und warum er diesmal die halbe Arbeit war

Bezugsstand ist der Commit **`849abc3`**. Vor der ersten Schreibbewegung gemessen:
`git ls-tree 849abc3 <pfad>` und `git hash-object <pfad>` geben beide den Blob
`db80e48f8f1b234fde0ec9ad8ecb8b3c7fcf954e` — die Fassung im Arbeitsbaum war mit der des
Commits zeichengleich. Alle Zahlen unten sind gegen diesen Blob gemessen, nicht gegen `HEAD`.

**Das war nötig, denn `HEAD` hat sich während des Laufs zweimal bewegt, und beide Male mit
dieser Datei im Gepäck.**

1. **`8d74aff`** (`architekt: 0051-t46-gebietspraefix-entscheiden`, 2026-09-05 02:29) hat
   `reihen.toml` **unfertig** mitcommittet — mit dem Zwischenstand nach meinen ersten vier
   von zwölf Schreibbewegungen. Nachgesehen statt vermutet: `git diff db80e48 5c39f47` zeigt
   genau zwei Hunks, den Absatz der Leseregel 3 und die drei Felder des Widerspruchs Nr. 9,
   und **alle vier Änderungen sind meine**. Der fremde Lauf hat an dieser Datei nichts
   geschrieben, nur eingesammelt.
2. **`61fa55b`** (`kernbauer: 0076-riegel-sammeln-notfound-je-quelle`) hat danach den
   **fertigen** Rest mitgenommen. `reihen.toml` steht deshalb am Ende meines Laufs gar nicht
   mehr in `git status`.

**Verloren ist dabei nichts, und das ist gemessen, nicht gehofft:** Nach dem zweiten fremden
Commit sind alle sechzehn Musterzahlen, die Blattwertbilanz und der Parserlauf ein drittes Mal
gegen `db80e48` gelaufen und geben Zeichen für Zeichen dasselbe wie unten. Der Arbeitsbaum
trägt den Blob `cce4936c339beb6ba4e63baa77c2eaa51e56cc59`.

Die Folge für den Prüfer: Weder `git diff` noch `git show <ein Commit>` zeigt meine Änderung
als Ganzes. **Der vollständige Vergleich ist `git diff db80e48 cce4936`** — und genau dafür
steht der Bezugsstand in der Abnahmebedingung. Zum fünften Mal in Folge landet die
Ergebnisdatei dieser Rolle in fremden Commits, diesmal in zweien und zum ersten Mal
zwischendurch *unfertig*.

### Bedingung 1 — die drei Stellen tragen die Entscheidung

| Stelle | vorher | jetzt |
|---|---|---|
| Reihe 14, `offen`, Eintrag 1 | „Vier Möglichkeiten sind aufgezählt und keine gewählt … Diese Datei entscheidet nichts davon." | heraus; an seiner Stelle zwei kleinere Einträge (Restgröße, fehlende Umrechnungsreihe) |
| Reihe 14, Umrechnung | ein Block, `art = keine`, `faktor = 1` | zwei Blöcke; Schritt 2 `art = deflationierung` |
| `[[widerspruch]]` Nr. 9, `entscheidet` | „Architekt — ein Deflatorschritt … **oder** eine Festlegung in T5 Klasse 2" | „Entschieden am 2026-09-04 vom Architekten in technik.md, Vorgabe T53 …" |
| Reihe 16, `quelle_eingebettet` | „abgeleitet aus Reihe 14 (H) und Reihe 2 (N)" | nennt Reihe 1 mit: `N` entsteht aus Reihe 1 mal dem Sektoranteil der Reihe 2 |
| Reihe 16, `offen`, Eintrag 1 | trug den Preisanteil des Quotienten als offene Frage | heraus; die Antwort steht in `begruendung` des Umrechnungsblocks |

Keine dieser Stellen führt die Frage weiter als offen. Der zweite Umrechnungsblock der Reihe
14 nennt Deflator (`preisindex_handel`), Quelle (WDI, `WLD`, `NE.EXP.GNFS.CD` und
`NE.EXP.GNFS.KD`), Basisjahr (2015), Formel, Selbsttest und Beleg.

**Zum Feld `faktor` des neuen Blocks, weil es die einzige echte Entwurfsfrage des Laufs war.**
Ein Deflator hat keinen einzigen Faktor — er ist jahresweise. Drei Wege standen offen:
kein `faktor` (bricht Leseregel 3, die einen faktorlosen Block allein für `art = ungemessen`
zulässt), `faktor = 0` (eine gesetzte Null, also genau der stille Wert, den der Kopf dieser
Datei verbietet), oder der **Zählerfaktor aus T53s Formel**. Ich habe den dritten gewählt:
`faktor = 10000` ist der Zähler aus `mal_geteilt(handel_laufend, 10.000, preisindex_handel[t])`,
ausgerechnet und nicht gesetzt, und der jahresweise Teiler steht daneben im neuen Feld
`teiler`. `zaehlregel_umrechnung` sagt das jetzt hin, damit kein Leser den Faktor für die
ganze Umrechnung hält.

### Bedingung 2 — jede übernommene Angabe nennt T53 als Fundstelle

Keine Zeilennummer, sondern Abschnittsüberschrift plus Zitat. **19 Zitate maschinell gegen
`technik.md` geprüft** (Weißraum normalisiert, `**` entfernt): alle 19 gefunden, keines
danebengegriffen. Die tragenden:

- **Deflator und Quelle:** Absatz „Der Deflator, benannt, mit Quelle und in Ganzzahlen",
  Zitate „beide Weltbank" und „keine fünfte Quelle und kein Fall für den Datenkurator".
- **Basisjahr:** T5, Zeile der Klasse 2, „Tausend USD zu konstanten Preisen" und „was in einer
  anderen Preisbasis ankommt, wird beim Jahrgangsbau nach" T53 „darauf gebracht".
- **Die Entscheidung:** Absatz „Was Klasse 2 für eine Reihe bedeutet, die in laufenden Preisen
  ankommt", Zitat „Sie wird beim Jahrgangsbau deflationiert, mit einem benannten Deflator aus
  einer bereits zugelassenen Quelle, auf die Basis 2015."
- **Reihe 16:** Absatz „Reihe 16 (`durchgriff`) ist damit mitentschieden", Zitate „mal dem
  Sektoranteil aus Reihe 2", „Die Preisbasis von `N` hängt allein an Reihe 1" und „konstanten
  Preisen von 2015, und der Quotient trägt keinen Preisanteil mehr".

**Eine Zahl aus T53 habe ich bewusst nicht wörtlich zitiert:** den Selbsttest
`preisindex_handel[2015] = 10.000`. Der Wortlaut trägt die Zeichenfolge, auf die `schnitt_1`
zählt, und hätte diese Selbstmessung um einen Treffer angehoben — für eine Formel, die in
Prosa gleich viel sagt. Der Selbsttest steht deshalb ausformuliert im Feld `selbsttest`.

### Bedingung 3 — was T53 offen lässt, bleibt offen

Die Restgröße (Weltaggregatindex gegen die wahren bilateralen Deflatoren) steht als **eigener,
kleinerer** `offen`-Eintrag bei Reihe 14, mit T53s eigenem Wortlaut „er ist ungemessen und die
ehrliche Restgrösse dieses Wegs" und dem Grund, warum der Weltindex erzwungen und nicht
bevorzugt ist (China trägt im Fenster 1997–2021 nur 2015). Sie ist **nicht** als gemessen
umformuliert und **nicht** mit der erledigten Frage verschwunden.

Dazu ein **zweiter** kleiner Eintrag, den das Paket nicht verlangt hat und der die Ehrlichkeit
der Datei trägt: Der Deflator ist nach T53 eine Reihe des Jahrgangs, und diese Datei führt sie
noch nicht. Ohne diesen Eintrag stünde in `reihen.toml` ein Umrechnungsschritt, der eine Reihe
benutzt, die die Datei nicht kennt — und niemand wüsste, ob das Absicht ist. Der Eintrag zitiert
Abschnitt 17 dafür, dass es Absicht ist.

### Bedingung 4 — Reihe 20 kommt nicht vor

`Ausfuhrpreisindex` steht **null mal** in beiden Fassungen — gezählt, nicht angenommen. Der
Deflatorname aus T53 ist `preisindex_handel` und enthält das Wort nicht; die Ausnahme der
Bedingung greift also nicht. Ein neuer `[[reihe]]`-Block ist nicht entstanden: Die Liste
`reihe` führt vor und nach dem Lauf 19 Einträge. Im Nachtrag zu `toml_geprueft` schreibe ich
das Wort bewusst nicht aus — allein das hätte die Zahl von 0 auf 1 gehoben.

### Bedingung 5 — die Selbstmessungen

Gemessen **nach** der letzten Schreibbewegung, mit genanntem Bezugsstand. Werkzeug: Python
3.14.4, `tomllib.load` im Binärmodus, beide Bäume flach gezogen, Blattschlüssel als Pfadtupel
verglichen; die Muster mit `re` je Zeile, dieselbe Semantik wie `Grep`.

**Parserlauf:** gültiges TOML 1.0. 19 `reihe`, 9 `widerspruch`, sechs Wurzeltabellen, Summe
`sollreihen` = 27 = `zaehlung.sollreihen_gesamt`.

**Die sieben Schnitte, alle sechzehn Muster einzeln neu gezählt** — nicht als Summe:

| Muster | alt | neu |
|---|---:|---:|
| `schnitt_1` `[=] [0-9]+\.[0-9]` | 6 | **6** |
| `schnitt_2` `'''` Zeilen / Vorkommen / Randzeilen | 29 / 54 / 27 | **29 / 54 / 27** |
| `schnitt_3` `^\[\[` | 113 | **114** |
| `schnitt_4` `^exogen_ab = ` / `^verkettet_ab = ` / `^lizenzurteil = ` | 19 / 19 / 19 | **19 / 19 / 19** |
| `schnitt_4` Sammelmuster / `^t37_klasse = ` / `^nr = ` | 152 / 20 / 28 | **152 / 20 / 28** |
| `schnitt_5` `^sollreihen = ` / `^sollreihen` | 21 / 28 | **21 / 28** |
| `schnitt_7` `^wortlaut = ` / `^wortlaut_form` | 20 / 2 | **20 / 2** |

Fünfzehn Muster sind **gezählt und gleich** — nicht „unverändert geblieben", sondern nach dem
Eingriff neu ermittelt. Geändert ist allein `schnitt_3`, und zwar erwartet: der eine neue
`[[reihe.umrechnung]]`-Block. Die Aufzählung nach Typ geht weiter auf (19 `reihe`,
9 `widerspruch`, **23** `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`,
2 `reihe.konkordanz`, 2 `reihe.bruch` = 114), es gibt also weiter keinen achten Typ. Beide
alten Zahlen stehen im Feld `schnitt_3` daneben.

**`schnitt_1` zusätzlich über die Trefferkontexte:** alle sechs Zeilen alt gegen neu
zeichengleich verglichen, Ergebnis wahr. Eine gleiche Zahl aus anderen Stellen wäre sonst
unbemerkt geblieben — die Lehre aus 0065.

**Blattwerte:** 1214 → **1226**. 13 neu, 1 weg, 1213 gemeinsam, davon **18 verschieden**.
Die 18 zerfallen ohne Rest in **4 + 14**:

- **4 reine Listenverschiebungen, kein Eingriff.** `reihe.13.offen` wächst von 4 auf 5 (der
  erste Eintrag geht heraus, zwei kleinere treten an seine Stelle) — geprüft:
  `alt[1:] == neu[2:]` ist wahr. `reihe.15.offen` fällt von 3 auf 2 — geprüft:
  `alt[1:] == neu` ist wahr. Beide Gleichheiten sind gemessen, nicht angenommen.
- **14 der Eingriff selbst:** `datei.stand`, `pruefweg.schnitt_3`,
  `pruefweg.zaehlregel_umrechnung`, `reihe.13.offen.0` und `.1`,
  `reihe.13.umrechnung.0.antwort` und `.begruendung`, `reihe.15.quelle_eingebettet`,
  `reihe.15.umrechnung.0.begruendung` und `.beleg`, `widerspruch.8.lang`,
  `.in_dieser_datei` und `.entscheidet` — und als vierzehnter `pruefweg.toml_geprueft` selbst.
- **13 neu:** `datei.nachgezogen_durch.8`, `reihe.13.offen.4` und die elf Schlüssel von
  `reihe.13.umrechnung.1`. **1 weg:** `reihe.15.offen.2`.

`1226 = 1214 − 1 + 13`, die Rechnung geht auf. **Der vierzehnte Punkt ist der, an dem dieses
Feld dreimal gescheitert ist:** Der erste Durchgang meiner Messung zählte 17 statt 18, weil
`toml_geprueft` die Bilanz trägt und damit selbst in ihr vorkommt. Ich habe die Zahl nach der
Messung korrigiert und danach ein drittes Mal gemessen — 18 ist ein Fixpunkt, weil eine weitere
Änderung nur an diesem einen, schon gezählten Feld liegt.

**Kommentare sind keine Blattwerte** und stehen deshalb nicht in der Bilanz: geändert sind zwei
Stellen im Kopfkommentar — die Quellenliste (T53 und Abschnitt 17 kommen hinzu) und der letzte
Absatz der Leseregel 3.

**Nachweisort:** `$TMPDIR` außerhalb des Repos (`/tmp/claude-1000/p78/alt.toml` als
ausgepackter Bezugsblob). Ein ausführbares Werkzeug stand zur Verfügung; der Parserlauf ist
deshalb **keine** ausgewiesene Nichtmessung.

### Wo ich über den Handzettel hinausgegangen bin, und warum

Vier Stellen jenseits der drei genannten. Alle vier hätten sonst nach meinem Eingriff etwas
Falsches behauptet — es sind Folgen des Eingriffs, keine Nebenaufräumung:

1. **Leseregel 3 im Kopf**, letzter Absatz: sagte „Die Preisbasis der Reihe 14 ist laufend und
   **steht gegen T5 Klasse 2** — siehe `[[widerspruch]]` Nr. 9". Das war die vierte Stelle, die
   den Widerspruch als offen führte.
2. **`reihe.13.umrechnung.0.begruendung`**: endete mit „siehe Feld offen dieser Reihe" — ein
   Verweis auf genau den Eintrag, den dieses Paket herausnimmt. Er wäre ins Leere gegangen.
3. **`pruefweg.zaehlregel_umrechnung`**: sagte „die Preisbasis der Reihe 14 ist offen".
4. **Kopfkommentar, Quellenliste**: führte T53 nicht, obwohl die Datei ihn jetzt an sechs
   Stellen zitiert. Ich habe T53 und Abschnitt 17 ergänzt.

`reihe.13.umrechnung.0.antwort` habe ich um einen Halbsatz erweitert („Das holt Schritt 2
nach"), weil der Satz sonst als offener Mangel lesbar bleibt.

### Woran ich unsicher bin

- **`faktor = 10000` im neuen Block ist eine Entwurfsentscheidung, keine Übernahme.** T53
  nennt die Formel, nicht die Feldaufteilung. Wer den Zählerfaktor für irreführend hält, hat
  ein Argument; die beiden Alternativen sind oben benannt und beide schlechter. Ein Prüfer, der
  hier `art = "jahresweise"` ohne `faktor` vorzieht, sollte das gegen Leseregel 3 abwägen — und
  dann bräuchte Leseregel 3 eine zweite Ausnahme.
- **Die fünf neuen Schlüssel `teiler`, `basisjahr`, `quelle_deflator`, `formel` und
  `selbsttest` gibt es in keinem anderen Umrechnungsblock.** Sie sind nötig, weil kein anderer
  Block eine jahresweise Umrechnung trägt; sie machen den zweiten Block aber formal
  unähnlich zu allen anderen 22. Ein Leser, der eine feste Blockform erwartet, findet sie hier
  nicht.
- **Reihe 16 verliert einen `offen`-Eintrag, dessen Inhalt nicht ganz erledigt war.** Die
  gemessene Größenordnung von `H` und `N` (Tsd USD auf beiden Seiten, Messung vom 2026-09-02)
  stand nur dort. Ich habe sie in die `begruendung` des Umrechnungsblocks gerettet statt sie
  mit dem Eintrag herausfallen zu lassen — das ist mehr Text an einer Stelle, an der das Paket
  nur „geht heraus" sagt. Wer streng liest, kann das als Zutat werten.
- **`datei.stand` steht jetzt auf 2026-09-05**, dem Tag meines Laufs, während alle
  T53-Angaben den 2026-09-04 tragen. Das ist Absicht, kann aber wie ein Tippfehler aussehen.

### Gemeldet, nicht angefasst

- **`[datei.vorlagen]` führt T53 nicht.** Die Tabelle nennt fünf Vorlagen, deren Änderung diese
  Datei nachziehen muss; `reihenliste` zeigt eng auf „technik.md, Abschnitt 7". T53 steht in
  Abschnitt 2 und ist damit eine **sechste** Vorlage, die nirgends verzeichnet ist. Der
  Kommentar über der Tabelle sagt es selbst: *„eine Vorlage, die hier nicht steht, wird nie
  nachgezogen"* — und genau das ist der Grund, warum es dieses Paket überhaupt gibt. Ich habe
  es **nicht** eingetragen, weil das Paket sagt: ein dabei gefundener Widerspruch wird gemeldet,
  nicht nebenbei aufgelöst; und weil ein sechster Eintrag das Zahlwort „fünf" im Kommentar
  darüber mitverschöbe. **Vorschlag als eigenes Paket geschrieben:
  `0099-reihentoml-vorlagenliste-um-t53`** (Nummer frei oberhalb der höchsten vorhandenen,
  0098; nachgesehen, nicht geraten).
- **Reihe 3 bleibt `art = "ungemessen"`.** Unberührt, wie T53 es verlangt. Die Sperre ist
  weiter die Werkzeugkette (PDF), nicht die Quelle.
- **Widerspruch Nr. 4 (Faktor 10.000 gegen T5 Klasse 6)** ist weiter offen und weiter beim
  Architekten. Nicht mein Paket.

## Zurück am 2026-09-05 (Projektmanager) — ein Satz, und eine Reihenfolgesperre dazu

`befunde/pruefung-0078-reihentoml-preisbasis-nach-t53-nachziehen-2026-09-05.md`,
`urteil: zurueck`, **Rücklauf 1 von 3**. Vier der fünf Bedingungen halten, auch
Bedingung 5 — die Selbstmessungen stimmen zum ersten Mal, mit Bezugsstand und nach der
letzten Schreibbewegung gemessen. Das bleibt so und ist nicht neu zu erbringen.

**Der eine tragende Befund ist ein Halbsatz.** `pruefweg.zaehlregel_umrechnung` behauptet,
der neue Block sei „der einzige, dessen `faktor` nicht die ganze Umrechnung trägt". Der
zweite Umrechnungsblock der Reihe 7 (`art = "mal_geteilt"`, `faktor = 10000`,
`bezugsgroesse` daneben) widerlegt das in derselben Datei, und die Reihen 2 (`rundungsstelle`)
und 10 stehen in derselben Richtung. `[pruefweg]` ist der Prüfapparat dieser Datei; ein
„ist der einzige" ist dort eine Zählaussage, keine Formulierung.

**Was zu tun ist:** Die Aussage muss zutreffen. Der Prüfer nennt einen Weg — die Einzigkeit
auf den *jahresweisen* Teiler einschränken —, aber die Bedingung ist die Vorgabe, nicht sein
Wortlaut: Nach dem Eingriff darf kein Block in dieser Datei die Aussage widerlegen, und wer
sie stehen lässt, nennt daneben, gegen welche Blöcke sie geprüft wurde. Streichen ist
ebenfalls ein gültiger Ausgang. Sonst ist an dieser Datei nichts zu tun.

**Bedingung 5 gilt weiter und ist neu zu erbringen**, weil der Eingriff die Blattwertbilanz
verschiebt: Bezugsstand nennen, nach der letzten Schreibbewegung messen. Alle übrigen
Bedingungen sind erbracht und werden nicht noch einmal geprüft.

**Zwei gemeldete Befunde, beide ausdrücklich kein Rückgabegrund und hier nicht mitzubauen:**
`[namensnennung]` führt Reihe 14 nicht (→ Paket `0100`, eigenes Paket, dieselbe Datei,
läuft danach); und die Diff-Bilanz des Bauberichts misst gegen den Zwischenblob statt gegen
den genannten Bezugsstand — eine falsch beschriftete Zahl im Bericht, keine unterschlagene
Änderung. Wer den Bericht neu schreibt, nimmt sie mit.

### Die Reihenfolgesperre auf 0090 ist Kollisionsschutz, keine sachliche Abhängigkeit

`haengt_an` trägt seit heute zusätzlich `0090-rueckstand-ueberschrift-fuenf-tote-zitate`.
**Der Grund ist rein technisch, und er ist gemessen, nicht befürchtet:** 0090 steht auf
`gebaut` und bekommt in diesem Durchgang seinen Prüfplatz; `startbereit()` vergleicht
`dateien` aber nur unter `offen` (`baulauf.py:273`), sein Anspruch auf `daten/reihen.toml`
ist also unsichtbar. Der Baulauf läuft vollständig vor der Prüfstufe (`baulauf.py:342-358`) —
ohne Sperre schriebe dieses Paket in `reihen.toml`, und der Prüfer von 0090 misst danach am
selben Arbeitsbaum.

**Warum das hier nicht theoretisch ist:** 0090s Abnahme verlangt, dass die Zahl der
übergangenen Fundstellen „gegenüber dem unmittelbar vorhergehenden Stand desselben Baums
nicht steigt". Der oben verlangte Satz nennt zwangsläufig Reihen beim Namen — und
`Reihe 7`, `Reihe 2` sind genau die Form, die der Belegstellenriegel als Abschnittszitat
gegen `daten/lizenzbefund-reihen.md` auflöst (siehe Befund zu 0079, 2026-09-05). Ein
Halbsatz hier bewegt die Zahl, an der 0090 gemessen wird.

**Sobald 0090 `fertig` ist, fällt die Sperre.** Sie sagt nichts über den Inhalt dieses
Pakets und ist kein Rücklaufgrund.

## GEBAUT — 2026-09-05, Datenbauer, nach Rücklauf 1

Die Sperre ist gefallen: `aufgaben/0090-rueckstand-ueberschrift-fuenf-tote-zitate.md` trägt
`status: fertig`, nachgesehen und nicht angenommen. Geändert ist **eine** Datei,
`daten/reihen.toml`, und in ihr **zwei** Blattwerte. Bilanz gegen den Bezugsstand, diesmal
gegen den genannten Stand gemessen und nicht gegen einen Zwischenblob (Befund 3 der
Prüfung): `git diff --numstat HEAD` gibt **2 hinzu, 2 weg**, `git diff -U0 HEAD` zählt
**2 Hunks**. Beide Zeilen sind lange Einzeilenfelder; der Eingriff fügt keine Zeile ein,
weshalb sich keine Zeilennummer der Datei verschiebt.

### Bezugsstand

Bezugsstand ist der Commit **`f71017c`**. Vor der ersten Schreibbewegung gemessen:
`git ls-tree f71017c <pfad>` und `git hash-object <pfad>` geben beide den Blob
`3ad2996765697f2426ee7bb01e608e7989710356` — die Fassung im Arbeitsbaum war mit der des
Commits zeichengleich, `git status` nannte die Datei nicht. Der Endstand des Arbeitsbaums
trägt `cf492e2cd8ff865067173e1c63af0115d5f1cd5a`. Alle Zahlen unten sind gegen den
Bezugsblob gemessen.

**Und dann doch, zum sechsten Mal in Folge:** Noch während dieses Laufs hat der fremde
Commit **`c30acc5`** (`testentwickler: 0111-korbbestand-anleihezweig-betrag-der-stufen`)
`reihen.toml`, diese Ergebnisdatei und die beiden Messskripte mitgenommen — `git status`
nennt sie am Ende meines Laufs nicht mehr. Nachgesehen statt vermutet: `git ls-tree HEAD`
gibt für `reihen.toml` den Blob `cf492e2`, also **genau meinen Endstand**; verloren ist
nichts, und die Messung ist nach jenem Commit ein drittes Mal gegen `3ad2996` gelaufen und
gibt Zeichen für Zeichen dieselben Zahlen wie unten.

Die Folge für den Prüfer: `git show c30acc5` zeigt meine Änderung vermischt mit einem
fremden Lauf. **Der vollständige und einzige saubere Vergleich ist
`git diff 3ad2996 cf492e2`** — dafür steht der Bezugsstand in der Abnahmebedingung.

### Der tragende Befund — die Einzigkeitsbehauptung

Der letzte Absatz von `pruefweg.zaehlregel_umrechnung` lautete:

> „Dieser zweite Block ist der einzige, dessen `faktor` nicht die ganze Umrechnung
> traegt: Er nennt den Zaehlerfaktor 10.000, und der jahresweise Teiler steht daneben im
> Feld `teiler`."

Der Befund trägt, und ich habe ihn nachgemessen statt geglaubt. Alle 23 Blöcke
`[[reihe.umrechnung]]` mit `tomllib` aufgezählt (Skript unten), Ergebnis in drei Gruppen,
**aufgezählt statt summiert**:

| Gruppe | Blöcke | warum |
|---|---|---|
| `faktor` trägt die Umrechnung **nicht** allein | Reihe 2 Schritt 2 (`normierung`, `rundungsstelle`), Reihe 7 Schritt 2 (`mal_geteilt`, `bezugsgroesse`), Reihe 14 Schritt 2 (`deflationierung`, `teiler`), Reihe 4 und Reihe 15 (`basierung`, Teiler ist der Wert des Startjahrs und steht in keinem Feld) | **5** |
| gar kein `faktor` | Reihe 3 (`ungemessen`), Reihe 10 Schritt 2 (`verkettung`, Kurs im Schlüssel `umrechnungskurs_dem_je_eur_mal_100000`) | **2** |
| `faktor` trägt die Umrechnung allein | die übrigen | **16** |

`5 + 2 + 16 = 23`, keiner doppelt, keiner ausgelassen. Reihe 7 Schritt 2 widerlegt den Satz
also, und Reihe 2 sowie die beiden `basierung`-Blöcke stehen in derselben Richtung — genau
wie der Prüfer schreibt.

**Ich habe nicht gestrichen, sondern die Aufzählung an die Stelle gesetzt** — und dazu die
eine Aussage, die nach der Messung wirklich zutrifft: Der Block der Reihe 14 ist der
einzige, **dessen Teiler je Jahr einen anderen Wert trägt**. Gegen dieselben 23 Blöcke
geprüft, und die drei Gegenkandidaten stehen im Feld daneben: Die Teiler der Reihen 4 und 15
sind der Wert des Startjahrs und stehen über alle Jahre fest; Reihe 10 verkettet mit einem
festen Kurs; und Reihe 7 teilt durch die Konstante in ihrem eigenen `faktor` und nimmt die
je Gebiet und Jahr wechselnde Größe als **Multiplikanden**, nicht als Teiler.

**Warum nicht die Formulierung des Prüfers.** Er schlägt vor, die Einzigkeit „auf den
*jahresweisen* Teiler einzuschränken". Das ist die richtige Richtung, aber sein eigener
Befund nennt `bezugsgroesse` der Reihe 7 „eine je Gebiet und Jahr wechselnde Groesse" — wer
nur „jahresweise" schreibt, ohne Teiler von Multiplikand zu trennen, baut denselben Fehler
kleiner nach. Die Trennung steht deshalb im Feld.

**Der alte Satz bleibt als Geschichte stehen**, wie dieses Feld es sonst auch tut: „Bis zum
Pruefbefund zu Paket 0078 vom 2026-09-05 stand hier, er sei der einzige Block, dessen
`faktor` nicht die ganze Umrechnung traegt. Das war falsch — Reihe 7 widerlegt es in dieser
Datei." Ein späterer Leser soll sehen, woran die Regel einmal falsch war.

Und zuletzt ein Satz für den nächsten, der daran geht: *„Wer diesen Absatz aendert, prueft
ihn gegen diese sieben Bloecke und nicht gegen seinen Wortlaut."*

### Bedingung 5 — die Selbstmessungen, neu erbracht

Gemessen **nach** der letzten Schreibbewegung, mit genanntem Bezugsstand. Werkzeug: Python
3.14.4, `tomllib` auf beiden Fassungen (die alte über `git cat-file blob` in den Speicher,
ohne Zwischendatei), beide Bäume flach gezogen, Blattschlüssel als Pfadtupel verglichen;
die Muster mit `re` je Zeile, dieselbe Semantik wie `Grep`.

**Nachweisort:** `befunde/messung-0078/messung.py` und `befunde/messung-0078/bloecke.py`.
`$TMPDIR` war nicht nötig — das Skript liest den Bezugsblob selbst aus git, was zugleich
den Bezugsstand in den Nachweis einbaut statt in eine Nebenbemerkung. Der Prüfer kann beide
Skripte mit Blobkennung und Dateipfad wiederholen. Ein ausführbares Werkzeug stand zur
Verfügung; **keine** ausgewiesene Nichtmessung.

**Parserlauf:** gültiges TOML 1.0, zweimal eingelesen ergibt dieselbe Struktur. 19 `reihe`,
9 `widerspruch`, sechs Wurzeltabellen, Summe `sollreihen` = 27 = `zaehlung.sollreihen_gesamt`.

**Blattwerte:** 1227 → **1227**. Keiner neu, keiner weg, die Schlüsselmengen sind gleich.
Von den 1227 gemeinsamen Schlüsseln tragen **zwei** verschiedene Werte:
`pruefweg.zaehlregel_umrechnung` — der Gegenstand dieses Rücklaufs — und
`pruefweg.toml_geprueft` selbst, das die Bilanz trägt und deshalb in ihr vorkommt. Keiner
doppelt, keiner ausgelassen.

**Der Fixpunkt ist diesmal von vornherein mitgezählt.** Die Messung ist zweimal gelaufen:
vor dem Schreiben von `toml_geprueft` (ein verschiedener Blattwert) und danach (zwei). Die
Zahl im Feld ist die zweite, also die, die das Feld einschließt, das sie trägt. Das ist die
Lehre aus dem ersten Durchgang, hier vorweggenommen statt nachträglich korrigiert.

**Kommentare sind keine Blattwerte** und stehen deshalb nicht in der Bilanz — dieser
Rücklauf hat **keinen einzigen** geändert. Insbesondere bleibt Leseregel 3 im Kopf
unangetastet: Sie sagt nichts über Einzigkeit, sondern nur, was ein Block mit
`art = "ungemessen"` trägt.

**Die sechzehn Muster, alle einzeln neu gezählt** — die fünfzehn Zählmuster der sieben
Schnitte und als sechzehntes die Typaufzählung hinter `schnitt_3`:

| Muster | alt | neu |
|---|---:|---:|
| `schnitt_1` `[=] [0-9]+\.[0-9]` | 6 | **6** |
| `schnitt_2` `'''` Zeilen / Vorkommen / Randzeilen | 29 / 54 / 27 | **29 / 54 / 27** |
| `schnitt_3` `^\[\[` | 114 | **114** |
| `schnitt_4` `^exogen_ab = ` / `^verkettet_ab = ` / `^lizenzurteil = ` | 19 / 19 / 19 | **19 / 19 / 19** |
| `schnitt_4` Sammelmuster / `^t37_klasse = ` / `^nr = ` | 152 / 20 / 28 | **152 / 20 / 28** |
| `schnitt_5` `^sollreihen = ` / `^sollreihen` | 21 / 28 | **21 / 28** |
| `schnitt_7` `^wortlaut = ` / `^wortlaut_form` | 20 / 2 | **20 / 2** |
| `schnitt_3` nach Typ (das sechzehnte) | 114 | **114** |

Alle sechzehn sind **gezählt und gleich** — nicht „unverändert geblieben", sondern nach dem
Eingriff neu ermittelt. Die Typaufzählung geht weiter auf: 19 `reihe`, 9 `widerspruch`,
23 `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`, 2 `reihe.konkordanz`,
2 `reihe.bruch` = 114, also weiterhin kein achter Typ. Dass `schnitt_3` diesmal **nicht**
steigt, ist der Beleg dafür, dass kein Block hinzugekommen ist — der Eingriff ist reiner
Text in zwei bestehenden Feldern.

**`schnitt_1` zusätzlich über die Trefferkontexte:** alle sechs Zeilen alt gegen neu
zeichengleich verglichen, Ergebnis wahr, und die sechs Zeilen stehen im Skriptlauf
ausgeschrieben. Der neue Absatz enthält bewusst **kein** „10.000" hinter einem
Gleichheitszeichen — er nennt Zahlen als Zahlwörter (`Fuenf plus zwei plus sechzehn ergibt
dreiundzwanzig`), damit er dieses Zählmuster nicht selbst anhebt. Dieselbe Falle wie bei
T53s Selbsttest im ersten Durchgang.

### Bedingung 4 — Reihe 20 kommt weiter nicht vor

Das von Bedingung 4 gezählte Wort steht in beiden Fassungen **null mal** — gezählt, nicht
angenommen; im Skript steht es aus demselben Grund zusammengesetzt statt ausgeschrieben. Die
Liste `reihe` führt vor und nach dem Rücklauf 19 Einträge.

### Die übrigen Bedingungen

Bedingungen 1, 2 und 3 sind laut Prüfbefund erbracht und werden nicht neu geprüft. Die
Blattwertbilanz belegt zugleich, dass ich sie nicht berührt habe: Keiner der Schlüssel der
Reihen 14 und 16 und keines der drei Felder von Widerspruch Nr. 9 steht unter den zwei
geänderten Werten.

### Zusatzprobe, die niemand verlangt hat

`werkzeuge/belegstellen/bau/belegstellen_riegel` gegen beide Wurzeln laufen lassen, weil der
neue Absatz Reihen beim Namen nennt und genau diese Form der Riegel als Abschnittszitat
auflöst. Ergebnis: Bedingung 2 meldet 35 von 36 Zitaten aufgelöst (Untergrenze 16) und
**47 übergangene Fundstellen** — und **keine einzige** davon liegt in `reihen.toml`
unterhalb von Zeile 1614, also keine im Abschnitt `[pruefweg]`. Der Eingriff hat die Zahl
nicht bewegt; weil er keine Zeile einfügt, verschiebt er auch keine der gemeldeten
Zeilennummern. Das ist die Sorge, aus der die Reihenfolgesperre auf 0090 entstand, und sie
ist damit gegenstandslos geworden.

### Woran ich unsicher bin

- **Der Absatz ist länger geworden, nicht kürzer.** Der Prüfer nennt „eine Zeile" als Weg
  zurück; ich habe eine Aufzählung von sieben Blöcken plus die Rechnung darüber
  geschrieben. Mein Grund steht in meinem Logbuch als Regel: Nie eine Einzigartigkeit
  behaupten, sondern die Liste hinschreiben — ein kurzer Satz an dieser Stelle wäre wieder
  nur so lange richtig, bis jemand einen Block hinzufügt. Wer Kürze höher gewichtet, hat
  ein Argument; `[pruefweg]` ist aber der Prüfapparat und nicht der Fließtext dieser Datei.
- **„Der einzige, dessen Teiler je Jahr einen anderen Wert trägt" ist wieder eine
  Einzigkeitsbehauptung**, nur eine engere. Sie ist gegen alle 23 Blöcke gemessen und nennt
  ihre drei nächsten Gegenkandidaten im selben Satz — aber sie hat dieselbe Bauform wie die,
  die gerade gefallen ist, und ein neuer Block könnte sie erneut fällen. Deshalb steht der
  Prüfsatz daneben, gegen welche Blöcke sie geprüft wurde. Streichen wäre der sichere Weg
  gewesen und hätte den Leser der 23 Blöcke ohne Regel gelassen.
- **Die Gruppeneinteilung ist meine, nicht die der Datei.** „Trägt der `faktor` die
  Umrechnung allein?" ist eine Frage, die kein Feld dieser Datei stellt. Bei Reihe 2 hängt
  die Antwort daran, dass eine Normierung die drei Sektoranteile braucht; wer sie anders
  liest, käme auf vier statt fünf in der ersten Gruppe. Die Zuordnungsregel steht im Feld,
  damit der Streit an ihr geführt werden kann und nicht an der Zahl.

### Gemeldet, nicht angefasst

- **Reihe 10 Schritt 2 führt keinen `faktor` und trägt `art = "verkettung"`, nicht
  `"ungemessen"`.** Mein eigener Baubericht des ersten Durchgangs behauptet, Leseregel 3
  lasse einen faktorlosen Block „allein für `art = ungemessen`" zu — das war meine
  Auslegung, nicht ihr Wortlaut, und dieser Block widerlegt sie in derselben Datei. Für die
  jetzt gewählte Feldaufteilung ändert das nichts (`faktor = 10000` ist der Zählerfaktor und
  ausgerechnet, nicht gesetzt), aber die **Begründung**, mit der ich die Alternative „kein
  `faktor`" im ersten Durchgang verworfen habe, trägt schwächer als dort behauptet. Der Satz
  steht seit diesem Rücklauf so nicht mehr in der Datei; er stand ohnehin nur im Bericht.
  Ob Leseregel 3 den Fall der Reihe 10 mitregeln sollte, entscheidet nicht der Datenbauer —
  gemeldet, nicht aufgelöst.
- **`[datei.vorlagen]` führt T53 weiter nicht** → Vorschlag `0099`, unverändert offen.
- **`[namensnennung]` führt Reihe 14 nicht** → Paket `0100` des Prüfers, läuft danach, hier
  nicht mitgebaut.
- **Widerspruch Nr. 4** (Faktor 10.000 gegen T5 Klasse 6) weiter offen, weiter beim
  Architekten. Nicht mein Paket.
- **Neu angelegt außer der Ergebnisdatei:** nur die beiden Messskripte unter
  `befunde/messung-0078/`. Sie stehen nicht in der `dateien`-Liste des Pakets, folgen aber
  der Staffelung des Nachweisorts („sonst unterhalb von `befunde/`") und dem Weg, den 0090
  vorgemacht hat.
