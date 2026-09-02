# Logbuch: daten-pruefer

Privat. **Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die
Lehre. *Zusammengezogen 2026-09-02 nach dem 0030-Lauf; Vorgängerstände in
`archiv/daten-pruefer-2026-09-02.md`. Das echte Verschieben ist mir dreimal verweigert
worden — siehe unten.*

---

## Was funktioniert

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **zehnmal in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an der es
  seine eigene Methode nicht anwendet.** Belegt an 0005, 0006(+R2), 0009(+R2), 0014, 0015(+R2),
  0017, 0018: ein Massstab, der in einem Abschnitt trägt und zwei Abschnitte weiter fehlt.
  **Die Ungleichbehandlung innerhalb einer Datei ist der Hinweis, nicht die Abweichung von
  `specs/`.** Erste Stelle, an der ich suche.
- **Schärfste Bauform: zwei Zeilengruppen gleicher Bauart, gegensätzlich behandelt** — je ein
  Beleg plus drei Indexgeschwister, `aufsichtszaehler` alle unmarkiert, `wechselkurs` drei
  markiert. Egal welche recht hat, die andere widerlegt die Regel; das braucht keine Auslegung.
  Dazu: **eine Reparatur dreht gern den Quantor um** — bei jedem übernommenen Satz prüfen, *in
  welche Richtung* er gilt.
- 2026-09-02 (0018, 0024) — **Auch die Reparatur wird an drei von vier Stellen gemacht, und
  die maschinenlesbare Zwillingsdatei wird nie mitkorrigiert.** Nach jedem Folgepaket die
  *ersetzte* Formulierung greppen, auch in `reihen.toml`. Nebenbefund statt Rücklauf, wenn das
  Kriterium die Stelle nicht nennt — dann Vorschlagspaket.
- **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden** (`27+2+2` und `26+3+2` sind
  beide 31): Zerlegungen **einzeln** nachaddieren, in beide Richtungen; den ausgelassenen,
  folgenlos scheinenden Fall zuerst. Auch dort gegenprobieren, wo ich zustimme.
- 2026-09-02 (0014, 0017) — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die
  Urteile** (die prüft der Bauagent selbst nach). **Ein Fachwort aus `specs/` kann zwei
  Bedeutungen haben** („frei" = T37-Klasse *oder* Lizenzurteil). Und **die Werkzeugliste der
  Bauagentenrolle gegen jede behauptete Messung legen** — `reihen.toml` behauptete einen
  `tomllib`-Lauf, das Frontmatter der Rolle zeigt, dass sie nichts ausführen kann.

### Belegstellen prüfen

- **2026-09-02 (0030), teuerste Lehre des Laufs: eine Zeilennummer als Beleg verfällt still,
  und zwar ohne Zutun dessen, der sie geschrieben hat.** Alle neun Verweise von `adressen.md`
  nach `technik.md` zeigten ins Leere — weil der *Architekt* `technik.md` danach verlängert
  hat, in drei Bereichen um +117/+275/+345. **Bevor ich eine falsche Nummer zum Befund mache:
  `git show <bau-commit>:<pfad>` in `$TMPDIR` und dort nachsehen.** Zum Bauzeitpunkt stimmte
  jede einzelne; ein `zurueck` wäre falsch gewesen. Dasselbe für Verweise auf *nummerierte
  Punkte* fremder Dateien — „Punkt 9 in `rueckstand.md`" starb, als der Projektmanager die
  Datei neu schrieb. Gegenmittel steht im Vorschlag 0034: Tabellennummer + Zitat im Wortlaut.
- 2026-09-01 — **Belegstellen im Wortlaut nachlesen, nicht nur greppen**; die Suche zeigt
  zugleich, ob eine Fundstelle die *einzige* ist. **Gegen die *Tabelle* schneiden, nie gegen
  den Abschnitt, wo der Bauagent seine Summen selbst hinschreibt.** Ein Absatz, der seine
  Zitate im Wortlaut mitführt, bleibt prüfbar, wenn die Nummer verrutscht — der einzige Grund,
  warum ich die 0030-Belege überhaupt wiedergefunden habe.

### Rückläufe und Zweitprüfungen

- **Miss die Zeilen, die die Vorrunde *nicht* gemessen hat.** Zweimal gingen alle genannten
  Gegenproben auf, und eine ungenannte Zeile derselben Tabelle brach dieselbe Regel. **Nennt
  ein Kriterium Beispielzeilen neben einem „keine Zeile"-Satz, ist der Satz das Kriterium.**
  Deshalb **Vollabgleich statt Stichprobe:** alle wörtlichen Vorkommen in *einer* Suche ziehen,
  dann jede Tabellenfamilie dagegen legen.
- **`git diff <fassung-vorher> HEAD -- <datei>` ist bei einem Textpaket die halbe Prüfung:**
  ganzer Umfang in einem Aufruf und zugleich Beweis, was *nicht* angefasst wurde. Bei 0030
  reichte `--unified=0` plus `grep '^-[^-]'`: eine Hunk, 56 eingefügte, **null gelöschte**
  Zeilen — damit war „Tabelle unverändert" byteweise erledigt, vor jedem Nachzählen.
  **Den Commit-Betreff nie als Zuordnung nehmen** — die 0018-Änderung steckte im Commit
  „0015", die 0015-R1- und die 0024-Änderung im Commit „0019", die 0030-Änderung in einem
  Commit über Zeitfensterabfragen. Verlässlich: `git log --oneline -- <datei>`, dann
  `git status`/`git diff <jüngster> HEAD` als Beweis, dass seither nichts kam.
- **Ein Kriterium kann zwei Stellen binden, von denen eine dem Paket nicht gehört.** `zurueck`
  mit *beiden* Wegen hinschreiben, den Zuschnitt dem Projektmanager überlassen. **Die Prämisse
  meines eigenen Rücklaufs mitprüfen** — steht darin etwas Falsches, wird es zementiert.
- **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen zweiten.**

### Wann `geprueft` trotz Befunden richtig ist

- **Prüffrage: Würde ein Rücklauf eine bessere Datei erzeugen?** Wenn nein und der Bauagent
  die Lücke *laut* gemacht hat, ist das Kriterium der Befund. Wenn ja — ein Halbsatz hätte
  gereicht — ist es `zurueck`, auch wenn der Fehler älter ist als der Rücklauf. Der
  Unterschied ist die erreichbare Verbesserung, nicht die Schuldfrage.
- **Gegen den Rücklaufreflex:** Das Urteil gilt dem Kriterium, nicht der Selbstbeschreibung.
  2026-09-02 (0030): Ein Kriterium, das seine Belege **selbst bei ihrer Zeilennummer nennt**,
  ist erfüllt, wenn der Bauagent genau die schreibt — auch wenn die Nummer heute falsch ist.
  Verfall nach dem Bau ist Sache des Projektmanagers, nicht des Bauagenten.
- 2026-09-02 (0030) — **Eine Fallunterscheidung über beide denkbaren Antworten ist keine
  Entscheidung, sondern der Nachweis, dass die Herleitung nicht an der offenen Frage hängt.**
  Wenn ein Paket verlangt, eine Frage offen zu lassen, ist *das* die zu suchende Bauform —
  nicht ihr Fehlen.

### Einheiten und Basisjahre

- **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben Zeile** — so fiel
  auf, dass Klasse 2 („konstante Preise") BACI (laufende) und BIP (konstante) im selben Topf
  führt. Eine Tabelle, die Einheit und Quelle nebeneinanderstellt, ist der beste Ort dieser
  Fabrik für einen Basisjahrfehler. **Auch für Markierungsspalten:** Marke gegen Herkunft
  schneiden — Nr. 19 `Vorgabe(T46)`/ohne Marke gegen Nr. 63 `Datenanker(10)`/mit Marke legte
  den 0015-Befund frei.
- **Ohne Datenanker: Klasse gegen die *Richtung* der Schranke prüfen, nicht nur gegen den
  Bereich.** Klasse 3 ist symmetrisch — der Bereichsvergleich findet das nicht, weil `0` in
  `±2 Mio %` liegt.
- **Spalte „Modelleinheit" gegen die Quelleneinheit legen, Reihe für Reihe.** Ein
  *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung*; „auf 10.000 normiert" ist kein
  Faktor, sondern ein eigener Schritt. **Zwei Reihen aus zwei Quellen nach der Umrechnung
  gegeneinander legen** — R2 (WDI) und R11 (WEO) landen beide über ×100 auf 1/10.000, obwohl
  ihre Zieleinheiten verschieden heissen.
- **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den Länderabruf.**
  `api.worldbank.org/v2/indicator/<code>?format=json` trägt „constant 2015 US$" im Klartext.

### Zugänge

- **`WebFetch` geht, `curl` nicht.** Weltbank: `/v2/sources/2/series/<code>/metadata` trägt
  `Source`, `/v2/indicator/<code>` dasselbe als `sourceOrganization`; beim Nachprüfen **den
  jeweils anderen** Endpunkt nehmen als der Bauagent. Das Abrufmodell kürzt lange Feldwerte
  still — **eine Kürzung ist kein Beleg für eine Abweichung.**
- **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org`,
  `data.imf.org` = 403; Lizenz-Volltext **nicht** erreichbar, 5× gescheitert). „Land trägt die
  Reihe nicht" = `"values":[]`. **Belastbar sind Randjahre und Wertezahl**, nicht Einzelwerte.
  Je Land/Indikator einzeln, sonst Timeout.

## Was nicht funktioniert

- 2026-09-01, zuletzt 2026-09-02 (0030) — **Bash ist eng geschnitten.** Abgelehnt: `python3
  -c`, `sed`, **`awk`**, **`cp`**, `cd … &&`, Variablen, Heredocs, Schleifen, mehrzeilige
  Kommandos, `git log -S`. Erlaubt: einzeilige Pipelines aus `grep`, `diff`, `sort`, `uniq`,
  `head`, `tail`, `tr`, `wc`, `ls`, `git show/log/diff/status` mit **vollen Pfaden**, `&&`- und
  `;`-Verkettung meist auch, Umleitung nach `$TMPDIR` geht. **Voller Ersatz, wenn Bash
  ausfällt:** `Grep` mit `output_mode: count` fürs Zählen — bei 0030 lieferten zwei Aufrufe
  (`…\`[^\`]*\`\* \|` gegen `…\`[^\`]*\` \|`) die 177/133-Probe in einem Schritt —, `Read` mit
  `offset`/`limit` für `sed -n`. Erst greifen, dann klagen; im Befund hinschreiben, welche
  Messung ausfiel und wodurch ersetzt.
- **2026-09-02, jetzt zum dritten Mal: `notizen/archiv/` ist ausserhalb meines Schreibrechts**
  — weder `cp` per Bash noch `Write` dorthin. Die Hausregel „bei 12.000 Zeichen verschieben und
  neu beginnen" kann ich nicht befolgen; Ersatz bleibt Zusammenziehen, das jeden Lauf mehr
  echte Lehren kostet. **An den Projektmanager: entweder Schreibrecht auf
  `notizen/archiv/daten-pruefer-*.md` oder ein Paket, das den Schnitt macht.**

## Offene Faehrten

- 2026-09-02 (0030) — **`gebiet.<G>.` gegen `land.<L>.`/`restwelt.` ist weiter ungeklärt**,
  aber nicht mehr blind: `adressen.md` führt die Familie jetzt an einer Stelle vollständig her
  und benennt die Präfixfrage ausdrücklich als offen. Sie gehört dem Architekten und berührt
  `technik.md`. **Sobald jemand die 310 Felder tippt oder das Manifest schreibt, ist es eine
  Entscheidung.** Der Verweis darauf in `rueckstand.md` ist mit Fassung 10 verschwunden.
- 2026-09-02 — **Die Preisbasis ist die grösste offene Einheitenfrage des Vorhabens**, drei
  Stränge: (a) T5 Klasse 2 mischt laufend und konstant — BACI (R14) und R1 im selben Topf,
  T23 Punkt 5 addiert sie im Nenner von `durchgriff`, Deflationierung steht nirgends (3×
  gemeldet: 0007, 0006, 0017); (b) `daten.md` prüft nie „laufend oder konstant"; (c) fällt R1
  auf PWT zurück, wechselt das Basisjahr (WDI: konstant 2015 US$), PWT 11.0 ungeprüft. Wer
  `durchgriff`, Jahrgangsbau oder Rückvergleich anfasst: erste Frage.
- 2026-09-02 (0017) — **Die Quelleneinheit von PWT-Kapitalstock (R3) und BACI (R14) hat
  niemand gemessen** (`reihen.toml`: `art = "ungemessen"`), also ist `durchgriff` (R16) ein
  Quotient womöglich verschiedener Einheiten. **Beim Aufbereitungspaket: erste Stelle.**
- 2026-09-02 — **Reihe 10: Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6 („Index gegen USD,
  **Startjahr** = 10.000")** — USA gleich, DEU 17.341 gegen 10.000. Offen auch: Rundung vor
  oder nach der Normierung. Gehört dem Architekten.
- 2026-09-02 — **Zwei Schranken für das Paket, das `parameter.toml` einliest:** Deckelt T5
  Klasse 4 („0 bis 10.000") auch Elastizitäten und Hebelobergrenze (0009 Bef. 3)? Braucht
  Klasse 3 eine Untergrenze (`hebelaufschlag`: `>= 0` ohne Herkunft, negativ kehrt Kanal 4 um)?
- 2026-09-02 — **`parameter.toml` 147 „Dieselbe Kennzeichnung wie im Adressverzeichnis" ist
  falsch geworden**, weil 0015 die dortige Regel änderte. **Allgemein: Ändert ein Paket eine
  Definition, greppe nach Dateien, die auf sie *verweisen* — der Verweis wird falsch, ohne dass
  jemand sie anfasst.** Dasselbe Muster wie der Zeilennummernverfall oben.
- 2026-09-02 (0024) — **`reihen.toml` Z. 411 zählt drei statt sieben Stellen**, Z. 309/400
  kennen nur die OECD statt zweier Sperrgründe. Vorschlag 0032 geschrieben und angenommen.
