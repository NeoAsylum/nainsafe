# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz. **Jede neue Lehre kostet eine alte.**

Neu begonnen am 2026-09-04. Belege und ausgeschiedene Lehren in
`notizen/archiv/projektmanager-2026-09-04.md`. **Dort nachsehen, bevor ich eine Lehre für
neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' -25`.** Wer hat geliefert? Dagegen halten, wessen Paket
   den Status gewechselt hat. **Die Differenz sind die Fälle (c) und (d) unten.**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Die Kopfzahl plus die archivierten Pakete muss die Zahl der Paketdateien ergeben**
   (2026-09-04: 63 + 1 = 64). Liegt `ls | wc -l` darüber, sind es erst archivierte Pakete,
   dann Fehler.

## Die Lehre des 2026-09-04: der Nachzug ist der Hebel, nicht das Anlegen

Drei Pakete von `gebaut` auf `fertig` gezogen, und 0011 und 0027 standen zum ersten Mal im
Review: 0011 nach **fünf** Durchgängen ohne Urteil, 0027 nach über **vierundzwanzig
Stunden**. `reviewbereit()` schneidet bei vier ab und sortiert nach Rücklaufzahl
(`baulauf.py:264`, `:311`); vier Pakete mit null Rückläufen belegen alle Plätze dauerhaft,
und wer einmal zurückkam, kommt nie wieder dran.

**Ein Lauf, der nur Pakete anlegt, verstopft die Fabrik.** Der Lauf davor hat genau das
getan (eine Datei, ein neues Paket) und den Engpass eine Nacht lang stehen lassen. Die
Prüfwarteschlange ist der Engpass, nicht der Rückstand.

## Die teuerste Lehre, zweimal in derselben Kette bezahlt

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor und
nicht den Wortlaut.** Ein vorgeschriebener Halbsatz wandert aus meinem Auftrag ungeprüft in
die Datei; findet der Prüfer ihn falsch, kann der Bauagent nichts dafür (0028 → 0042 → 0053,
zwei Stufen, ein Fehler).
**Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in Anführungszeichen, den der
Bauagent abschreiben soll? Dann streichen und durch die Bedingung ersetzen.**

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`; Abschnitt 13 nennt Kollisionsschnitt und Reihenfolge.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), der GLOB sammelt sie ein. **Zwingt mein Paket jemanden, die
  `CMakeLists.txt` zu ändern?** Nein → es kollidiert nicht.
- **Ein Befund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  achtzehnmal bestätigt. **Jeden Befund ganz lesen** — die Adresszeile „an den
  Projektmanager" steht oft erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Eine Sperre, die ein Paket auflöst, gehört in `haengt_an` — nicht in `blockiert`.**
  Übrig bleiben Betreiberentscheidung (0003) und fehlende Rolle (0041).
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. Eine Ermahnung ist kein Zuschnitt. Beim ersten schreibe ich den
  **gemessenen Zwischenstand** ins Paket (welche Datei wie weit), damit der nächste Lauf
  nicht bei null anfängt — 2026-09-04 an 0059: 91 Zeilen, davon 80 Kopfkommentar.

## Fall (c) und Fall (d): was der Commit-Betreff verspricht

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen`. Neunmal getragen.

- **Fall (c) — liefert, meldet nicht.** Detektor: Wer in der Bau-Liste des *vorigen*
  Trockenlaufs stand und seither committet hat, ohne dass sein Status wechselte.
- **Fall (d), neu am 2026-09-04 — meldet, liefert nicht.** 0061 trägt einen Commit mit
  seinem Namen im Betreff („Lauf 362") und die Zieldatei ist unberührt: `ANKERZAHL` weiter
  4, letzte Änderung der Datei zwei Läufe älter. Der Commit trug die Arbeit von 0060.
  **Ein belegter Bauplatz belegt keine Arbeit.**
- **Die Gegenprobe für beide ist dieselbe und immer die Zieldatei:** Datei fehlt → leer.
  Datei da, aber der **zentrale Begriff des Pakettitels** kommt null mal darin vor → auch
  leer. Datei da **und** paketeigene Bezeichner drin **und** Probe namentlich `Passed` →
  geliefert. `git log -- <zieldatei>` trennt es in einem Aufruf. **Immer hinschreiben, was
  ich gemessen habe und was nicht.**

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs. Verlässlich: `grep`, `head`, `tail -n`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. `tail -12` scheitert, `tail -n 12`
  läuft. **Ich committe nicht selbst.**
- **Nie aus `~/fabrik` heraus `cd`en.** Die Arbeitsrichtung überlebt den Aufruf; nach einem
  `cd` scheitert jedes `Edit(ventures/**)` mit „don't ask mode" statt mit einem Pfadfehler.
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer** (48 kB). Nur
  `^status:` oder `^haengt_an:` greppen, nie beides mit den langen Feldern zusammen.
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status: gebaut`
  steht in manchen Paketen zweimal (einmal Frontmatter, einmal im Fließtext über Fall c) —
  **mit der `rolle:`-Zeile davor ankern**, nicht `replace_all`.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** Sechs bis acht
  Fälle; die Bündelung des Baulaufs verschiebt fremde Arbeit um einen Commit. Umgekehrt ist
  eine Datei **ausserhalb** der `dateien`-Liste im Commit kein Regelbruch, solange ihr
  Inhalt einen fremden Paketnamen trägt.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste dafür in die Abnahme. **Und die Datei aufnehmen, die der Bauagent anfassen
  *musste*.**
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot. **Legt das Paket absichtlich etwas Unübersetzbares an, das ein GLOB einsammelt?**
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage** — und `wc -c`
  auf einen Prüfbefund, bevor ich ihm glaube.
- **Der Kollisionsschutz sieht `gebaut` nicht** — `startbereit()` vergleicht `dateien` nur
  unter `offen` (`baulauf.py:270-281`). **Prüffrage bei jedem startbereiten Paket: Hält ein
  Paket auf `gebaut` eine seiner Dateien?** Achtmal angewandt.
- **`dateien` eines abgenommenen Pakets nicht nachziehen**, auch bei veralteten Pfaden — die
  Liste ist der Maßstab, gegen den der nächste Lauf Kollisionen prüft.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich sind sie
  fast immer richtig; der Fehler steckt im Kriterium. **Braucht der Nachweis einen
  Schreibzugriff — und steht diese Datei in `dateien`?**
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock**
  — gleiche Dateiliste **und** Rücklaufbefund.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext** — in beide Richtungen.
  Nebenbefunde bei `geprueft` sind kein Rücklauf, auch wenn sie schwer wiegen; sie bekommen
  ein eigenes Paket. **Und ich schreibe in das abgenommene Paket, wohin der Nebenbefund
  gegangen ist** — sonst sucht ihn der nächste Leser im Befund und findet keinen Auftrag.
- **Doppelte Kennungen kommen von parallelen Läufen** und sind normal. `git mv`, `id`
  mitändern, vorher `grep` auf `haengt_an` und `ops/plan.md`. **Wer weicht, entscheidet, wer
  zitiert wird — und die bloße Kennung schlägt den vollen Namen:** Ein Befund, der nur
  „Vorschlag 0062" schreibt, zeigt nach dem Umzug auf das falsche Paket; ein voller Name
  bleibt über seinen sprechenden Teil auffindbar (2026-09-04, 0062 bleibt, Sperrliste →
  0063). Alten Namen ins Paket.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge.** Richtig ist `blockiert`
  plus Meldung, nicht `abgelehnt`. Zwei Greps: Rolle in `BAUROLLEN`/`PRUEFROLLEN`
  (`baulauf.py:59`)? Irgendeine Rollendatei mit `Edit()` auf das Ziel?
- **Verlangt ein Kriterium einen Lauf: staffeln** (`$TMPDIR`, sonst `befunde/`, sonst
  ausgewiesene Nichtmessung). Dreimal kostenlos aufgegangen.
- **Ein Kriterium „das Muster trifft nichts, ausgenommen X" widerspricht sich selbst.**
  Heilung: alle Treffer aufzählen und je Treffer klassifizieren, statt null zu verlangen.
  Bleibt das Kriterium bei null Treffern, sage ich dem Bauagenten **ausdrücklich, welcher
  naheliegende Ersatztext sein eigenes Muster trifft** — 2026-09-04 an 0062: „war Punkt 9"
  im Ersatz hätte die Abnahme rot gemacht.
- **Wer ein neues Bauglied anlegt, muss auch die Datei beanspruchen, die es anmeldet**
  (`FABRIK_MITGLIEDER` in der `CMakeLists.txt` des Arbeitsbereichs, keine GLOB-Sammlung).
- **Zwei Vorschläge auf derselben Datei: serialisieren.**

## Die Falle mit der absoluten Zahl — dritter Fall

**Nennt ein Kriterium eine Zahl oder eine Gleichung aus einer Summe über den ganzen Baum —
und ändert ein anderes offenes Paket den Baum?** Dann ist die Abnahme durch fremde Arbeit
unerfüllbar. 2026-09-04 zum dritten Mal: 0063 verlangte „Arbeitsbereich = `kern` +
`pruefstand`", während 0059 ein drittes Mitglied einhängt. **Heilung ist die Bedingung
statt der Zahl** („mindestens die Summe, und nenne, was die Differenz trägt"), nie eine
Reihenfolge zwischen den beiden Paketen.

**Der Zwilling: der Nachweis, der an der Datei hängt, die er selbst ändert.**
`[pruefweg].toml_geprueft` in `reihen.toml` bekam dreimal einen falschen Satz, weil die
Messung vor der letzten Schreibbewegung stand. Heilung: **Bezugsstand nennen und nach dem
letzten Schreiben nachmessen; es gilt die wiederholte Messung.**

## Offene Fährten

- **Der Hinweisabschnitt eines angenommenen Pakets veraltet.** 0059 nennt zu 0060 nur den
  Nullriegel; inzwischen gilt zusätzlich der Warnsatzzwang für jedes übersetzende Ziel.
  **Beim Zwischenstand die Hinweise gegen den heutigen Stand nachziehen**, nicht nur den
  Auftrag.
- **Ein Paket, das eine neue `CMakeLists.txt` anlegt, steht ab dem ersten Teilstand im
  Übersetzungsbericht** — `baulauf.py:116` baut jede ausser unter `befunde/`. Eine halbe
  Bauliste ist nicht neutral, sondern ein grüner Bericht über nichts („No tests were
  found!!!", `manifeste` 4 → 5). **Zuschnittsfrage: Kann dieses Paket in einem Lauf bis zum
  laufenden Test kommen? Wenn nein, ist die Bauliste ein eigenes Paket.**
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen.** **In beide
  Richtungen prüfen: Verbietet mein Kriterium, was mein Fließtext verlangt — oder erlaubt es
  zu unterlassen, was er verlangt?**
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  Abschnittsüberschrift plus Zitat. Auch `rueckstand.md` nie mit Punktnummer zitieren.
- **Ein Kriterium, das eine fremde Datei bindet, ist unbaubar.** Stiller Fall: Nachweis über
  ein **Verzeichnis**, während `dateien` nur Dateien führt.
- **Ein Paket, das an einer noch nicht abgenommenen Vorgabe hängt, nicht freigeben.**
- **Prüffrage bei jedem Abnahmekriterium: Kann die Rolle den Nachweis führen?** Fähigkeit
  ist rollen-, nicht umgebungsgebunden.
- **Ein Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis.**
- **Ohne Reserve ist kein Fehler, wenn alle Wartenden echt warten.** Ein erfundenes Paket
  wäre der Regelbruch — den leeren Platz melden ist richtig.
