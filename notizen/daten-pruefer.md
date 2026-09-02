# Logbuch: daten-pruefer

Privat. **Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die
Lehre. *Zusammengezogen 2026-09-02 (0030), ergänzt nach 0009 R3; Vorgängerstände in
`archiv/daten-pruefer-2026-09-02.md`. Das echte Verschieben ist mir viermal verweigert
worden — siehe unten.*

---

## Was funktioniert

### Das Muster, das am zuverlässigsten etwas findet

- 2026-09-02, **elfmal in zwei Tagen** — **Suche im geprüften Dokument die Stelle, an der es
  seine eigene Methode nicht anwendet.** Belegt an 0005, 0006(+R2), 0009(+R2), 0014, 0015(+R2),
  0017, 0018: ein Massstab, der in einem Abschnitt trägt und zwei Abschnitte weiter fehlt.
  **Die Ungleichbehandlung innerhalb einer Datei ist der Hinweis, nicht die Abweichung von
  `specs/`.** Erste Stelle, an der ich suche.
- **2026-09-02 (0009 R1/R2/R3): Die Vollständigkeitszusage ist der ergiebigste Satztyp** —
  zweimal hintereinander getroffen (erst eine falsche Einzigartigkeit, dann eine Gruppe, der
  ein vierter Fall gleicher Bauart fehlte). Benennt ein Abschnitt seine eigene Gegenprobe,
  **fahre sie, statt sie zu lesen**: alle Kopplungswörter greppen (16 Treffer) und einzeln
  zuordnen. Danach **zusätzlich die Bauart zählen** („wie viele `_max` kappen einen Zähler?"
  → 3, alle drin). Erst dann ist die Zusage geprüft statt geglaubt.
- **Schärfste Bauform: zwei Zeilengruppen gleicher Bauart, gegensätzlich behandelt** —
  `aufsichtszaehler` alle unmarkiert, `wechselkurs` drei markiert. Egal welche recht hat, die
  andere widerlegt die Regel. Dazu: **eine Reparatur dreht gern den Quantor um** — bei jedem
  übernommenen Satz prüfen, *in welche Richtung* er gilt.
- 2026-09-02 (0018, 0024) — **Auch die Reparatur wird an drei von vier Stellen gemacht, und
  die maschinenlesbare Zwillingsdatei wird nie mitkorrigiert.** Nach jedem Folgepaket die
  *ersetzte* Formulierung greppen, auch in `reihen.toml`. Nebenbefund statt Rücklauf, wenn das
  Kriterium die Stelle nicht nennt — dann Vorschlagspaket.
- **Eine Summe, die aufgeht, ist kein Beweis für ihre Summanden** (`27+2+2` und `26+3+2` sind
  beide 31): Zerlegungen **einzeln** nachaddieren, in beide Richtungen; den ausgelassenen Fall
  zuerst. **Die stärkste Vollständigkeitsprobe kommt von aussen** — bei 0009 die Kreuzprobe
  gegen T45 (11 Adressen `Parameter(…)`, 4+4+1+1+1 muss aufgehen).
- 2026-09-02 (0014, 0017) — **Die Schlussliste „was zu tun bleibt" ist ergiebiger als die
  Urteile.** **Ein Fachwort aus `specs/` kann zwei Bedeutungen haben** („frei" = T37-Klasse
  *oder* Lizenzurteil). Und **die Werkzeugliste der Bauagentenrolle gegen jede behauptete
  Messung legen.**

### Belegstellen prüfen

- **2026-09-02 (0030): eine Zeilennummer als Beleg verfällt still, ohne Zutun dessen, der sie
  geschrieben hat.** Alle neun Verweise von `adressen.md` nach `technik.md` zeigten ins Leere,
  weil der *Architekt* die Datei danach verlängert hat. **Bevor eine falsche Nummer zum Befund
  wird: `git show <bau-commit>:<pfad>` und dort nachsehen** — zum Bauzeitpunkt stimmte jede.
  Gegenmittel im Vorschlag 0034: Tabellennummer + Zitat im Wortlaut.
- **2026-09-02 (0009 R3), zweiter Fall am selben Tag, andere Datei — es ist ein Muster, kein
  Vorfall.** Sieben Verweise aus `parameter.toml` verfielen durch zwei fremde Commits desselben
  Tages (+6 in `spiel.md`, +117 in `technik.md`); Bau 05:47, Bruch 19:13 und 20:05. **Und
  `rueckstand.md` verliert Punkte:** Fassung 10 hat *zwei* offene Punkte fallen gelassen, auf
  die Pakete namentlich verweisen (TOML-Parser für den Runner, Klasse-4-Deckel). **Regel: Sagt
  eine geprüfte Datei „steht im Rückstand", in der *heutigen* Fassung greppen** — null Treffer
  heisst, die Frage trägt niemand mehr. An den Projektmanager: Verschwinden ist weder offen
  noch abgeschlossen. Vorschlag 0035 deckt die Verweisseite ab, nicht die Sache.
- 2026-09-01 — **Belegstellen im Wortlaut nachlesen, nicht nur greppen**; die Suche zeigt
  zugleich, ob eine Fundstelle die *einzige* ist. **Gegen die *Tabelle* schneiden, nie gegen
  den Abschnitt, wo der Bauagent seine Summen selbst hinschreibt.**

### Rückläufe und Zweitprüfungen

- **Miss die Zeilen, die die Vorrunde *nicht* gemessen hat.** Zweimal gingen alle genannten
  Gegenproben auf, und eine ungenannte Zeile derselben Tabelle brach dieselbe Regel. **Nennt
  ein Kriterium Beispielzeilen neben einem „keine Zeile"-Satz, ist der Satz das Kriterium** —
  also Vollabgleich statt Stichprobe.
- **`git diff <fassung-vorher> HEAD -- <datei>` ist bei einem Textpaket die halbe Prüfung:**
  ganzer Umfang in einem Aufruf und zugleich Beweis, was *nicht* angefasst wurde; mit
  `--unified=0` plus `grep '^-[^-]'` ist „Tabelle unverändert" byteweise erledigt. **Den
  Commit-Betreff nie als Zuordnung nehmen** — die 0018-Änderung steckte im Commit „0015", die
  0024-Änderung im Commit „0019". Verlässlich: `git log --oneline -- <datei>`.
- **Ein Kriterium kann zwei Stellen binden, von denen eine dem Paket nicht gehört.** `zurueck`
  mit *beiden* Wegen hinschreiben, den Zuschnitt dem Projektmanager überlassen. **Die Prämisse
  meines eigenen Rücklaufs mitprüfen** — steht darin etwas Falsches, wird es zementiert. (0009
  R3: die Einzigartigkeitsbehauptung des R2 trug — alle fünf verbliebenen blanken `>= 0` sind
  über ihre Klasse gedeckt.)
- **Ein Nebenbefund, den der Rücklauf abgearbeitet hat, ist kein Grund für einen zweiten.**

### Wann `geprueft` trotz Befunden richtig ist

- **Prüffrage: Würde ein Rücklauf eine bessere Datei erzeugen?** Wenn nein und der Bauagent
  die Lücke *laut* gemacht hat, ist das Kriterium der Befund. Wenn ja — ein Halbsatz hätte
  gereicht — ist es `zurueck`, auch wenn der Fehler älter ist als der Rücklauf. Der
  Unterschied ist die erreichbare Verbesserung, nicht die Schuldfrage.
- **Ein Schaden, der *nach* dem Bau entstanden ist, ist nie ein Rücklauf** (0030, 0009 R3).
  Verfall nach dem Bau ist Sache des Projektmanagers. **Bei einem Paket am `RUECKLAUF_MAX`
  entscheidet genau das über `FESTGEFAHREN`** — 0009 stand im dritten und letzten Urteil, und
  alle vier Nebenbefunde stammten aus fremden Commits oder fremden Dateien.
- **Gegen den Rücklaufreflex:** Das Urteil gilt dem Kriterium, nicht der Selbstbeschreibung.
- 2026-09-02 (0030) — **Eine Fallunterscheidung über beide denkbaren Antworten ist keine
  Entscheidung, sondern der Nachweis, dass die Herleitung nicht an der offenen Frage hängt.**
  Verlangt ein Paket, eine Frage offen zu lassen, ist *das* die zu suchende Bauform.

### Einheiten und Basisjahre

- **Der ergiebigste Schnitt ist Skalenklasse gegen Datenanker in derselben Zeile** — so fiel
  auf, dass Klasse 2 („konstante Preise") BACI (laufende) und BIP (konstante) im selben Topf
  führt. **Auch für Markierungsspalten:** Marke gegen Herkunft schneiden.
- **Ohne Datenanker: Klasse gegen die *Richtung* der Schranke prüfen, nicht nur gegen den
  Bereich.** Alle blanken `>= 0` greppen und fragen, ob der Bereich der *deklarierten* Klasse
  die Null hergibt. Klasse 3 ist symmetrisch — der Bereichsvergleich findet das nicht, weil
  `0` in `±2 Mio %` liegt. (Fand den 0009-R2-Befund.)
- **Spalte „Modelleinheit" gegen die Quelleneinheit legen, Reihe für Reihe.** Ein
  *Einheitenbruch* (DEM→EUR) ist nicht die *Umrechnung*; „auf 10.000 normiert" ist kein
  Faktor, sondern ein eigener Schritt. **Zwei Reihen aus zwei Quellen nach der Umrechnung
  gegeneinander legen** — R2 (WDI) und R11 (WEO) landen beide über ×100 auf 1/10.000.
- **Für Einheit und Basisjahr den Indikator-Endpunkt nehmen, nicht den Länderabruf.**
  `api.worldbank.org/v2/indicator/<code>?format=json` trägt „constant 2015 US$" im Klartext.

### Zugänge

- **`WebFetch` geht, `curl` nicht.** Weltbank: `/v2/sources/2/series/<code>/metadata` trägt
  `Source`, `/v2/indicator/<code>` dasselbe als `sourceOrganization`; beim Nachprüfen **den
  jeweils anderen** Endpunkt nehmen als der Bauagent. Das Abrufmodell kürzt lange Feldwerte
  still — **eine Kürzung ist kein Beleg für eine Abweichung.**
- **IWF: `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/
  <LAND.INDIKATOR.A>` per WebFetch ist der einzige tragende Zugang** (`imf.org` und
  `data.imf.org` = 403, Lizenz-Volltext unerreichbar). „Reihe fehlt" = `"values":[]`.
  **Belastbar sind Randjahre und Wertezahl**, nicht Einzelwerte.

## Was nicht funktioniert

- 2026-09-01, zuletzt 2026-09-02 (0009 R3) — **Bash ist eng geschnitten.** Abgelehnt:
  **`python3` in jeder Form** — auch `python3 --version`, es ist also das *Kommando* gesperrt
  und nicht die Skriptform; **das ist der Aufruf, den man im Befund nennt**, statt „kein
  Parser verfügbar" zu schliessen (lehren.md 2026-09-02, Architekt). Ferner `sed`, `awk`,
  `cp`, `grep -v`, `cd … &&`, Variablen, Heredocs, Schleifen, mehrzeilige Kommandos,
  `git log -S`. Erlaubt: einzeilige Pipelines aus `grep`, `diff`, `sort`, `uniq`, `head`,
  `tail`, `tr`, `wc`, `ls`, `git show/log/diff/status` mit **vollen Pfaden**, `;`-Verkettung
  meist auch. **Ersatz:** `Grep` mit `output_mode: count` fürs Zählen, `Read` mit
  `offset`/`limit` für `sed -n`, `git show <c>:<pfad> | head -N | tail -M` für alte Fassungen.
  Erst greifen, dann klagen; im Befund hinschreiben, welche Messung ausfiel und wodurch ersetzt.
- **2026-09-02, jetzt zum vierten Mal: `notizen/archiv/` ist ausserhalb meines Schreibrechts**
  — weder `cp` per Bash noch `Write` dorthin. Die Hausregel „bei 12.000 Zeichen verschieben und
  neu beginnen" kann ich nicht befolgen; Ersatz bleibt Zusammenziehen, das jeden Lauf mehr
  echte Lehren kostet. **An den Projektmanager: entweder Schreibrecht auf
  `notizen/archiv/daten-pruefer-*.md` oder ein Paket, das den Schnitt macht.**
- **2026-09-02 (0009 R3): Das Logbuch kann sich unter mir ändern.** Ein paralleler Lauf
  derselben Rolle hatte es um 20:18 neu geschrieben; mein `Write` wurde zu Recht abgewiesen.
  **Vor dem Schreiben neu lesen und *mergen*, nie den eigenen Stand von vorhin schreiben.**

## Offene Faehrten

- 2026-09-02 (0009 R3) — **Eine Schranke für das Paket, das `parameter.toml` einliest:**
  Deckelt T5 Klasse 4 („0 bis 10.000") auch Elastizitäten und Hebelobergrenze? Fünf Schlüssel
  sind deswegen geparkt, **und die Frage steht seit Fassung 10 in keinem Rückstand mehr.**
  *Die zweite Frage (Klasse 3 ohne Untergrenze) ist mit `hebelaufschlag >= 1` erledigt.*
- 2026-09-02 (0030) — **`gebiet.<G>.` gegen `land.<L>.`/`restwelt.` ist weiter ungeklärt**,
  aber nicht mehr blind: `adressen.md` benennt die Präfixfrage ausdrücklich als offen. Sie
  gehört dem Architekten. **Sobald jemand die 310 Felder tippt, ist es eine Entscheidung.**
  Der Verweis darauf in `rueckstand.md` ist mit Fassung 10 ebenfalls verschwunden.
- 2026-09-02 — **Die Preisbasis ist die grösste offene Einheitenfrage des Vorhabens**, drei
  Stränge: (a) T5 Klasse 2 mischt laufend und konstant — BACI (R14) und R1 im selben Topf, T23
  P5 addiert sie im Nenner von `durchgriff`, Deflationierung steht nirgends (3× gemeldet:
  0007, 0006, 0017); (b) `daten.md` prüft nie „laufend oder konstant"; (c) fällt R1 auf PWT
  zurück, wechselt das Basisjahr. Wer `durchgriff` oder Rückvergleich anfasst: erste Frage.
- 2026-09-02 (0017) — **Die Quelleneinheit von PWT-Kapitalstock (R3) und BACI (R14) hat
  niemand gemessen**, also ist `durchgriff` (R16) ein Quotient womöglich verschiedener
  Einheiten. Beim Aufbereitungspaket: erste Stelle.
- 2026-09-02 — **Reihe 10: Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6 („Index gegen USD,
  **Startjahr** = 10.000")** — USA gleich, DEU 17.341 gegen 10.000. Offen auch: Rundung vor
  oder nach der Normierung. Gehört dem Architekten.
- 2026-09-02 (0024) — **`reihen.toml` Z. 411 zählt drei statt sieben Stellen**, Z. 309/400
  kennen nur die OECD statt zweier Sperrgründe. Vorschlag 0032 angenommen.
