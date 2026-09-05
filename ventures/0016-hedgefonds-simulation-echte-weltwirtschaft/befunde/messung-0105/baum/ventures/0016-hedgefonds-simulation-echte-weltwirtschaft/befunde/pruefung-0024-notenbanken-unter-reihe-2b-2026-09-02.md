---
typ: pruefung
paket: 0024-notenbanken-unter-reihe-2b
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln — Bedingung 1 gegen die Tabelle unter Klärung 4 nachgezählt, Bedingung 2 als Vollabgleich aller Fundstellen von „liegt nichts vor" gegen das `Source`-Zitat ihrer eigenen Reihe, Bedingungen 3 und 4 gegen den vollständigen Änderungsdiff der Datei plus nachgerechneter Kaskade
befunde: 1
---

# Die Korrektur trägt, und sie ist auf genau die eine Stelle beschränkt

Ein Nebenbefund, kein Rücklauf: Die falsche Zahl **drei** steht bereits in
`daten/reihen.toml`, Zeile 411 — genau der Weg, vor dem das Arbeitspaket unter „Zweite
Folge" gewarnt hat. Die Datei gehört diesem Paket nicht (`dateien` nennt nur
`lizenzbefund-reihen.md`), das Kriterium erreicht sie nicht, und der Bauagent hat sie
richtigerweise nicht angefasst. Vorschlag `0032-reihentoml-notenbanken-nachziehen`.

---

## Wie ich den Änderungsumfang bestimmt habe

`git log --oneline --name-only -- daten/lizenzbefund-reihen.md` nennt als jüngsten Commit
**`c8ff8c4`**, betitelt „testentwickler: 0019-vorratsverfahren-profilliste". Der Betreff ist
falsch — der Commit enthält genau zwei Dateien: `aufgaben/0024-notenbanken-unter-reihe-2b.md`
(`status: gebaut`) und `daten/lizenzbefund-reihen.md`. Der Commit `e2383dd`, der 0024 im
Betreff führt, berührt die Datei nicht. `git diff c8ff8c4 HEAD -- daten/lizenzbefund-reihen.md`
ist leer; die geprüfte Fassung ist also die aus `c8ff8c4`.

**`git show c8ff8c4 -- daten/lizenzbefund-reihen.md` ergibt zwei Hunks und sonst nichts.**
Das ist die Grundlage für die Bedingungen 3 und 4: Was in keinem der beiden Hunks steht, ist
zeichengleich unverändert.

1. Frontmatter Zeile 6: `ueberarbeitet:` nennt zusätzlich Paket 0024.
2. Zeilen 188–196 (neue Zählung 191–196): die Begründung unter 2b/2c, +6/−2 Zeilen.

---

## Bedingung 1 — beide Lieferantengruppen, und die Zahl stimmt mit der Tabelle

**Erfüllt.** Der neue Text (Zeilen 191–196) lautet:

> … genau ein statistisches Amt geprüft: **Destatis, Nr. 5, positiv** (…) — und **keine
> einzige Notenbank**. Die Notenbanken sind hier der zweite Lieferant, im Feld `Source` als
> eigene, zweite Angabe ausgewiesen („National Accounts data files, Central Banks"), und
> Destatis deckt sie nicht mit ab: Für die Ämter der drei übrigen Länder **und für alle vier
> Notenbanken** liegt nichts vor — offen sind damit **sieben der acht Stellen** aus der
> Tabelle unter Klärung 4, nicht drei.

- **Beide Gruppen genannt:** „ein statistisches Amt … Destatis" und „alle vier Notenbanken". ✔
- **Gegen die Tabelle gezählt** (Zeilen 552–557): vier Zeilen × zwei Spalten (Amt, Notenbank)
  = **acht Stellen**; als **geprüft** ist genau eine markiert (Destatis, `daten.md` Nr. 5).
  8 − 1 = **7**. Die Begründung sagt 7. ✔
- **Gegen die Aufschlüsselung im Satz selbst:** drei übrige Ämter + vier Notenbanken = 7. ✔
- **Gegen Zeile 559** („**Sieben Abrufe, nicht drei.**"): dieselbe Zahl. ✔

Der Beleg für die „eigene, zweite Angabe" hält gegen das `Source`-Zitat der Zeilen 177–179:
Dort steht `National Accounts data files, Central Banks;` als **zweite** von drei Angaben,
getrennt durch Semikolon und Zeilenumbruch. Die Behauptung ist also gemessen, nicht behauptet.

## Bedingung 2 — Vollabgleich statt Stichprobe

**Erfüllt.** `Grep` auf `liegt nichts vor|liegen nichts|nichts vor` über die ganze Datei
liefert **genau zwei** Fundstellen. Jede einzeln gegen das `Source`-Zitat *ihrer* Reihe:

| Fundstelle | Reihe | `Source` nennt Notenbanken? | zählt sie mit? |
|---|---|---|---|
| Zeile 119 | 1 (`NY.GDP.MKTP.KD`), Zitat Z. 97 | ja, „…and/or **Central Banks**" | ja — „und für alle vier Notenbanken" |
| Zeilen 194–195 | 2b/2c, Zitat Z. 177–179 | ja, „National Accounts data files, **Central Banks**" | ja — neu |

Gegenprobe in die andere Richtung, damit nicht überall „sieben" hingeschrieben wurde:
`Grep` auf `Notenbank|Central Bank|NSOs|National Statistical` zeigt alle sechs `Source`-Zitate.
**Reihe 5** (`SP.POP.TOTL`, Zitat Z. 244) nennt zwar `National Statistical Offices`, aber
**keine Notenbank**; ihre Begründung (Z. 246–255) zählt gar keine offenen Stellen und wurde
nicht angefasst. **Reihe 6** (Zitat Z. 277–279) nennt weder das eine noch das andere, ebenfalls
unberührt. **Reihe 2a** (Z. 159–162) nennt die Notenbanken („keine Notenbank"), gibt aber keine
Stellenzahl an — richtig so, sie verweist auf Klärung 4. Kein Fall von „sieben überall". ✔

Ergänzend `Grep` auf `drei übrigen|drei Nicht-EU|nicht drei|acht Stellen|Sieben Abrufe|sieben der acht`:
sechs Treffer, alle geprüft. Zeile 559–561 zitiert „die Statistikämter der drei
Nicht-EU-Modellländer" ausdrücklich als **die erste Fassung** — historische Angabe, keine
laufende Behauptung. Zeile 617 („nicht drei") zählt OECD-Fragen, nicht Prüfstellen.

## Bedingung 3 — alle übrigen Zahlen unverändert, Kaskade nachgerechnet

**Erfüllt.** Der Diff berührt keine einzige Zahl ausserhalb des einen Satzes; die zwölf
`reihen_*`/`sollreihen_*`-Felder, `codes_abgerufen_reihen: 6`, `codes_abgerufen_gegenprobe: 2`
und `pruefgegenstaende_ungefaehrdet_gesamt: 1 von 16` stehen zeichengleich. Ich habe sie
trotzdem gerechnet, weil das Kriterium es verlangt:

- **Paketebene:** 4 frei + 7 unklar + 0 gesperrt = **11** = `reihen_paket`. Die Listen in den
  Klammern sind disjunkt und vollständig.
- **Gesamtebene:** 6 + 8 + 1 = **15** Reihen mit Datenanker.
- **Sollreihen:** 7 frei + 24 unklar + 0 gesperrt = **31**, wie im Titel. Die 24 zerlegt sich
  in Reihe 1 (4) + Reihe 2 (4 + 8 = 12) + Reihe 9 (4) + Reihe 11 (4) = 24. Die
  Abschnittszahlen tragen das: „Sollreihen an diesem Code: 4" (Z. 138), „Sollreihen: 4"
  (Z. 168, 2a), „Sollreihen: 4 + 4 = 8" (Z. 205, 2b/2c), „Sollreihen: 0" bei Reihe 5 und 6.
- **Prüfgegenstände**, Tabelle Z. 478–484: 4 + 4 + 4 + 3 + 1 = **16**. ✔
- **Kaskade 16 → 8 → 1:** Fallen Reihe 1 und 2, fallen BIP (4) und Sektorstruktur (4);
  16 − 8 = **8**. Fällt zusätzlich die IWF-Kette, fallen Verbraucherpreise (4) und Wechselkurs
  (3); 8 − 7 = **1**, der Handelsblock. Deckt sich mit `pruefgegenstaende_ungefaehrdet_gesamt`. ✔
- **Die vier „Allein:"-Zeilen:** Klärung 1 = 0/0 (Z. 519), Klärung 4 = 8 Sollreihen/0 (Z. 525),
  Klärung 2 = 8 Sollreihen/0 (Z. 577), Klärung 3 = 0/0 (Z. 585). Unverändert.
- **Die Probe 16 + 8 = 24** (Z. 588): Klärung 1 **und** 4 zusammen heben 8 (Reihe 1, 2a) + 8
  (2b, 2c) = 16 laut Tabelle Z. 533–537; plus Klärung 2 mit 8 = **24** = `sollreihen_unklar`.
  Prüfgegenstände: 8 gehoben + 7 gesichert + 1 stehend = **16**. ✔

**Keine Abweichung gefunden.** Wichtig für dieses Paket: Die neue Zahl **sieben** ist eine
Zahl *offener Prüfstellen*, keine Sollreihen- und keine Prüfgegenstandszahl. Sie geht in keine
der obigen Summen ein, und deshalb bewegt die Korrektur zu Recht nichts anderes.

## Bedingung 4 — kein neuer Abruf, kein neues Urteil

**Erfüllt**, direkt aus dem Diff:

- **Keine URL, kein Abrufdatum hinzugekommen.** Der eingefügte Text enthält weder `http` noch
  eine Datumsangabe.
- **Die sechs `Source`-Zitatzeilen unangetastet** — keine der Zeilen 97, 157, 177–179, 244,
  277–279, 295 liegt in einem Hunk. Der neue Satz zitiert lediglich das Fragment
  „National Accounts data files, Central Banks" *im Fliesstext*; ich habe es zeichenweise gegen
  Zeile 178 gelegt: identisch bis auf das dort abschliessende Semikolon.
- **Urteil `unklar` für 2b/2c steht** (Z. 186, ausserhalb der Hunks), ebenso der Rechtsfrage-
  Vorbehalt („gehört dem Betreiber", Z. 197–199) und die gemeinsame **T26-Folgezeile**
  (jetzt Z. 201–203, vorher 196–198) — unverändert.

---

## Wonach ich noch gesucht und nichts gefunden habe

- **Ob der Bauagent über sein Paket hinaus geschrieben hat.** `git show --stat c8ff8c4` zeigt
  zwei Dateien: die Ergebnisdatei und die Paketdatei. `daten/reihen.toml` ist nicht dabei —
  korrekt, sie steht nicht in `dateien`.
- **Ob die Korrektur einen dritten Widerspruch erzeugt hat.** Die Datei behauptet an drei
  Stellen etwas über die Zahl der Prüfstellen (Z. 119, Z. 195, Z. 559); alle drei sagen jetzt
  sieben.
- **Ob die Tabelle unter Klärung 4 überhaupt auf 2b/2c anwendbar ist.** Sie ist es: Ihr
  Vorspann (Z. 544–548) leitet die acht Stellen ausdrücklich aus **beiden** Zitatformen her,
  der von Reihe 1/2a und der von 2b/2c. Für 2b/2c ist Klärung 4 laut Z. 526 sogar der einzige
  Sperrgrund — die acht Stellen gelten also vollständig, nicht anteilig.
- **Ob der eingefügte Zeilenumbruch vor „Ich löse das nicht auf" (Z. 196/197) etwas kaputt
  macht.** Nein — Markdown setzt den Absatz fort. Das Arbeitspaket erklärt die Form
  ausdrücklich zum Nicht-Befund, und `specs/` schweigt dazu.

---

# Nebenbefund — die Zahl drei ist schon in `daten/reihen.toml` angekommen

Nicht Gegenstand des Kriteriums, aber die Vorhersage des Arbeitspakets ist bereits eingetreten.
`daten/reihen.toml`, Zeile 411, `[[reihe.lizenzbeleg]]` für `NV.IND.TOTL.ZS`/`NV.SRV.TOTL.ZS`:

> `grund = "… Von den vier Modelllaendern ist genau ein Statistikamt geprueft (Destatis,`
> `daten.md Nr. 5, positiv); fuer die drei uebrigen liegt nichts vor."`

— und zwar unmittelbar unter einem `wortlaut`-Feld (Z. 405), das die Notenbanken selbst nennt.
Damit steht die falsche Abzählung in der **maschinenlesbaren** Fassung und ist zitierbar.

Zwei weitere Stellen derselben Datei tragen dieselbe Bruchlinie, aus dem Stand vor Paket 0018:
`grund` für Reihe 1 (Z. 309) und für 2a (Z. 400) nennen **nur die OECD** und lassen den
zweiten, unabhängigen Sperrgrund weg — den, den `lizenzbefund-reihen.md` seit 0018 an beiden
Stellen führt (Z. 114–120, Z. 159–162) und ohne den die Aussage „Klärung 1 allein hebt nichts"
in `reihen.toml` nicht nachvollziehbar ist.

Paket 0022 (`fertig`) hat `reihen.toml` zuletzt angefasst, aber drei andere Sachaussagen; die
`lizenzbeleg`-Begründungen kommen darin nicht vor. Vorschlag als eigenes Paket:
`aufgaben/0032-reihentoml-notenbanken-nachziehen.md`, `status: vorschlag`.
