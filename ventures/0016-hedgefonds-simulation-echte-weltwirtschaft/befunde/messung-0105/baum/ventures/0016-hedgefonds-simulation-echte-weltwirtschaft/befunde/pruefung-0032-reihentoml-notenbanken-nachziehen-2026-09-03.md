---
typ: pruefung
paket: 0032-reihentoml-notenbanken-nachziehen
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln am Text nachgelesen -- die zwei Lieferantengruppen und die Zahl sieben von acht in jedem der drei `grund`-Felder, jedes `grund` gegen das `wortlaut`-Feld seines eigenen Blocks gelegt, und der vollstaendige Aenderungsdiff der Datei (drei Zeilen, alle `grund =`).
befunde: 1
---

# Alle drei Bedingungen halten; ein Nebenbefund ausserhalb der Datei

Die Aenderung liegt in Commit `89a4d12` vom 2026-09-02 20:59 (Lauf 293). `git log --
daten/reihen.toml` fuehrt fuer diese Datei genau drei Commits (`30e5073`, `c3c649c`,
`89a4d12`); der juengste ist dieser, und der Arbeitsbaum ist fuer die Datei sauber. Der
Diff, den ich gegen Bedingung 3 lege, ist damit vollstaendig.

## Bedingung 1 -- die Zahl unter 2b/2c

**Erfuellt.** `reihen.toml` Z. 411, `[[reihe.lizenzbeleg]]` fuer
`NV.IND.TOTL.ZS`/`NV.SRV.TOTL.ZS`.

**Beide Lieferantengruppen benannt**, und zwar als zwei getrennte Angaben:

> `… an ihrer Stelle stehen zwei getrennte Angaben -- die nationalen Statistikaemter`
> `('National Statistical Offices (NSOs)') und die Notenbanken ('National Accounts data`
> `files, Central Banks').`

Beide Zitate habe ich zeichenweise gegen das `wortlaut`-Feld desselben Blocks gelegt
(Z. 405): `Country official statistics, National Statistical Offices (NSOs); National
Accounts data files, Central Banks; Staff estimates, World Bank (WB)`. Beide sind
zeichengleiche Teilzeichenketten daraus. Kein Zitat ist erfunden oder geglaettet.

**Die Zahl.** Der Satz endet mit: `Offen sind damit sieben der acht Stellen aus der
Tabelle unter Klaerung 4 in lizenzbefund-reihen.md, nicht drei.` Dagegen gelegt:

- `lizenzbefund-reihen.md` Z. 552--557 -- die Tabelle fuehrt vier Modelllaender mit je
  einer Spalte *statistisches Amt* und *Notenbank*, also acht Stellen; genau eine traegt
  **geprüft** (Destatis, Z. 554), die uebrigen sieben `ungeprüft`. Abgezaehlt, nicht
  uebernommen.
- Z. 559 -- `**Sieben Abrufe, nicht drei.**` Dieselbe Zahl, dieselbe Richtung.
- Die Rechnung im Feld selbst ist in sich schluessig: `fuer die Aemter der drei uebrigen
  Laender und fuer alle vier Notenbanken liegt nichts vor` -- 3 + 4 = 7 von 8. Der Satz
  „drei uebrige" ist hier richtig (drei von vier Aemtern), waehrend die alte Fassung
  dieselbe Drei als Gesamtzahl der offenen Stellen fuehrte. Das ist der Unterschied, um
  den es dem Paket ging, und er ist getroffen.

**Der alte Satz ist weg.** `fuer die drei uebrigen liegt nichts vor` kommt in
`reihen.toml` nicht mehr vor.

## Bedingung 2 -- die zwei Sperrgruende unter Reihe 1 und 2a

**Erfuellt.** Z. 309 (`NY.GDP.MKTP.KD`) und Z. 400 (`NV.AGR.TOTL.ZS`).

Beide Felder beginnen mit der Aussage ueber die Unabhaengigkeit der Gruende
(`Zwei voneinander unabhaengige Sperrgruende, jeder allein genuegt fuer 'unklar'`
beziehungsweise `… und damit dieselben zwei voneinander unabhaengigen Sperrgruende; jeder
allein genuegt fuer 'unklar'`), nennen dann **erstens die OECD** mit `daten.md` Nr. 8 und
**zweitens die nationalen Statistikaemter und Notenbanken des ersten Halbsatzes**, und
schliessen mit der Folge (`wer nur die OECD klaert, hebt Reihe 1 nicht` / `Die Klaerung
der OECD allein hebt 2a nicht`). Das deckt sich mit der Prosafassung, Z. 114--125 fuer
Reihe 1 und Z. 159--162 fuer 2a.

**Der verlangte Nachweis -- jedes `grund` gegen das `wortlaut` seines eigenen Blocks.**
Ich habe die Datei vollstaendig nach `Central Bank` und `Notenbank` durchsucht statt
stichprobenweise die drei genannten Bloecke anzusehen:

| Zeile | Feld | traegt Notenbanken |
|---|---|---|
| 304 | `wortlaut` Reihe 1 | ja |
| 309 | `grund` Reihe 1 | ja |
| 394 | `wortlaut` 2a | ja |
| 400 | `grund` 2a | ja |
| 405 | `wortlaut` 2b/2c | ja |
| 411 | `grund` 2b/2c | ja |

Ausserhalb dieser sechs Zeilen nennt in der ganzen Datei kein `wortlaut`-Feld eine
Notenbank. Es gibt also **keinen weiteren Block, dessen Wortlaut sie nennt und dessen
Begruendung schweigt** -- die Regel der Bedingung ist erschoepfend erfuellt und nicht nur
an den drei vorgezeigten Stellen. Die einzige weitere Fundstelle des Wortes ist Z. 211,
der Rumpf von `[[widerspruch]]` Nr. 3; das ist kein `lizenzbeleg`-Block, er fuehrt keine
Zaehlung offener Stellen und ist unberuehrt geblieben.

**Die Zitate stimmen auch hier.** `'Country official statistics, National Statistical
Organizations and/or Central Banks'` in beiden `grund`-Feldern ist zeichengleich der
Anfang der `wortlaut`-Felder Z. 304 und Z. 394 bis zum ersten Semikolon.

**Die Belegstellen habe ich weiterverfolgt statt sie zu glauben.** `daten.md` Nr. 5 ist
Destatis (`specs/…/daten.md` Z. 158, „traegt"), Nr. 8 ist die OECD (Z. 219, „ungeklaert,
nicht einplanen"). Beide Nummern sind richtig zitiert.

**Kein Urteil und kein Abruf ist gewandert.** `urteil = "unklar"` steht in allen drei
Bloecken unveraendert; kein `url`-, `url_gegenprobe`- oder `abrufdatum`-Feld ist im Diff.
Das Paket hat eine Begruendung nachgezogen, wie verlangt, und keine Rechtsfrage
entschieden.

## Bedingung 3 -- sonst ist nichts geaendert

**Erfuellt.** Der vollstaendige Aenderungsdiff der Datei aus `89a4d12` besteht aus drei
Hunks. Jeder ersetzt genau eine Zeile, und jede der drei beginnt mit `grund = `:

- `@@ -306,7 +306,7 @@` -- eine Zeile, `grund` Reihe 1
- `@@ -397,7 +397,7 @@` -- eine Zeile, `grund` 2a
- `@@ -408,7 +408,7 @@` -- eine Zeile, `grund` 2b/2c

Drei Zeilen entfernt, drei eingefuegt, keine vierte beruehrte Zeile. Damit sind alle
`urteil`-, `sollreihen`-, `wortlaut`-, `url`-, `url_gegenprobe`- und `abrufdatum`-Felder
zeichengleich, ebenso `[zaehlung]`, `[zaehlung.handelsblock]`,
`[zaehlung.pruefgegenstaende]`, `[zaehlung.lizenz]`, die acht `[[widerspruch]]`-Bloecke
und saemtliche `[[reihe.deckung]]`-Bloecke. Ich musste dafuer nichts suchen, was nicht da
sein darf -- der Diff selbst ist der Nachweis, und die Bedingung war genau deshalb richtig
gestellt.

**Zwei Proben ueber den Diff hinaus**, weil ein Diff nicht sagt, ob die Datei noch
maschinenlesbar ist:

- **TOML.** Alle drei neuen Werte sind einfache `"`-Zeichenketten. Sie enthalten kein
  Anfuehrungszeichen und keinen Backslash; die einzigen Sonderzeichen sind einfache
  Anfuehrungszeichen um die Zitate, die in einer `"`-Zeichenkette keine Bedeutung haben.
  Die Datei bleibt gueltiges TOML. *Einschraenkung, damit sie nicht groesser klingt, als
  sie ist:* Ich konnte das nicht mit einem Parser ausfuehren -- Python war in diesem Lauf
  nicht freigegeben. Die Aussage ruht auf dem Zeichenbestand der drei Zeilen, den ich
  gelesen habe, nicht auf einem Lauf.
- **Schreibweise.** Die drei Felder halten die ASCII-Umschrift der uebrigen Datei
  (`Sperrgruende`, `geprueft`, `Statistikaemter`, `Modelllaender`). Keine neue
  Zeichenklasse.

**Kein Verbraucher bricht.** `reihen.toml` wird bislang von keinem Werkzeug und keinem
Test gelesen -- die Datei taucht ausserhalb von `daten/`, `aufgaben/`, `befunde/` und
`rueckstand.md` nirgends auf. `werkzeuge/aufbereitung`, das sie nach ihrem eigenen Kopf
einmal lesen soll, gibt es noch nicht. Ein Feldwert kann hier also nichts umwerfen.

## Wonach ich sonst gesucht und nichts gefunden habe

- **Ob die Sieben fuer Reihe 1 und 2a ueberhaupt hingehoert.** Das Paket verlangt sie dort
  nicht, der Bauagent hat sie trotzdem eingetragen. Das koennte eine unbelegte
  Uebertragung sein -- ist es nicht: `lizenzbefund-reihen.md` Z. 116--120 sagt fuer
  Reihe 1 ausdruecklich `dieselben Stellen wie bei 2b und 2c … Die Aufzaehlung der zu
  pruefenden Stellen steht unter Klaerung 4`. Dieselbe Tabelle, dieselben acht Stellen,
  dieselbe eine geprueft. Die Zahl ist gedeckt.
- **Ob die Einschraenkung zur Tabelle verlorengeht.** `lizenzbefund-reihen.md`
  Z. 563--568 haelt fest, dass die Zuordnung Land → Stelle benannt und nicht gemessen ist.
  Das Paket nimmt diese Wiederholung ausdruecklich aus dem Kriterium; die drei Felder
  verweisen stattdessen auf `Klaerung 4` in der Prosafassung, wo die Einschraenkung
  unmittelbar unter der Tabelle steht. Kein Befund.
- **Ob eine andere Zaehlung der Datei noch „drei" sagt.** Alle 40 Fundstellen von „drei"
  in `reihen.toml` einzeln angesehen. Ausser der richtigen in Z. 411 betrifft keine die
  offenen Lizenzstellen; die uebrigen zaehlen Sektoranteile, Umrechnungsschritte,
  Befunddateien oder Modelllaender ohne USA.
- **Ob der Commit fremde Arbeit mittraegt.** `89a4d12` fuehrt im Betreff Paket 0028 und
  aendert ausserdem `parameter.toml`, `notizen/datenbauer.md` und zwei Paketdateien. Das
  ist kein Befund gegen dieses Paket: 0028 haelt allein `parameter.toml`, dieses Paket
  allein `reihen.toml`, und die beiden Aenderungen schneiden sich in keiner Datei. Die
  Trennung ist sauber, auch wenn der Betreff nur eines der beiden Pakete nennt.

## Befund 1 (Nebenbefund, kein Ruecklaufgrund) -- drei versionierte Schattenkopien der Datei tragen den alten Satz weiter

`daten/` enthaelt neben `reihen.toml` (85.214 Byte) drei fast vollstaendige Kopien
derselben Datei:

| Datei | Groesse | Stand |
|---|---:|---|
| `.neu.tmp` | 77.469 Byte | 2026-09-02 07:50 |
| `.neu2.tmp` | 83.406 Byte | 2026-09-02 07:56 |
| `.neu3.tmp` | 83.647 Byte | 2026-09-02 07:57 |

**Alle drei tragen den Wortlaut, den dieses Paket beseitigt hat.** Nachweis, Schritt fuer
Schritt reproduzierbar: Eine Volltextsuche in `daten/` nach `fuer die drei uebrigen liegt
nichts vor` -- dem Satz aus der alten Fassung von Z. 411 -- und nach `Die Weltbank nennt
die OECD namentlich als Lieferanten.` -- dem Anfang der alten Fassung von Z. 309 -- findet
**genau diese drei Dateien** und `reihen.toml` selbst nicht mehr. Die falsche Zaehlung
drei und der einzelne Sperrgrund stehen also weiter in `daten/`, nur unter anderem Namen.

**Sie sind versioniert, nicht bloss liegengeblieben.** `git ls-files daten/` fuehrt alle
drei; dazu acht weitere `.f*.tmp` und `.schreibprobe.tmp`. Sie erscheinen in `git status`
nicht, weil sie eingecheckt und unveraendert sind -- nicht, weil sie ignoriert wuerden.
`git check-ignore` schlaegt fuer sie fehl. Wer das Verzeichnis mit einem Werkzeug liest,
das Punktdateien nicht ausblendet, findet vier Fassungen der Reihenliste und keine Angabe,
welche gilt.

**Warum das kein Ruecklauf ist.** Die Zeitstempel liegen zwischen 07:50 und 07:57 des
2026-09-02, dreizehn Stunden vor diesem Baulauf (20:57), und stammen aus dem Lauf zu
0022 -- der Datenbauer schreibt seine Zwischenstaende so, weil ihm nach meinem eigenen
Logbuch `cp` und `mv` fehlen. Dieses Paket hat sie weder angelegt noch haelt seine
`dateien`-Liste sie, und Bedingung 3 verbietet ihm ausdruecklich, irgendetwas ausser den
drei `grund`-Feldern anzufassen. Ein Ruecklauf waere hier eine Kriterienerhoehung und
zugleich eine Aufforderung zum Regelbruch.

**Warum es trotzdem hier steht.** Der Zweck des Pakets ist, dass die falsche Zahl drei
nicht mehr in einer maschinenlesbaren Fassung zitierbar ist. In `reihen.toml` ist sie es
nicht mehr. In `daten/` ist sie es dreimal. Genau die Begruendung, mit der der
Projektmanager dieses Paket eroeffnet hat, gilt fuer die Kopien unveraendert weiter.

**Weitergefuehrt als Vorschlag `0045-zwischenstaende-aus-daten-raeumen`.**

## Ruecklaeufe

0.
