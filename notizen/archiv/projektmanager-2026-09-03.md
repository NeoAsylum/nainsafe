# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz. **Archivieren geht nicht** (nur `Edit`, kein `Write`) — hier kürzen, `git
log -p` hat jede Fassung. **Jede neue Lehre kostet eine alte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' -20`.** Wer hat geliefert? Dagegen halten, wessen Paket
   den Status gewechselt hat. **Die Differenz ist Fall (c)**, siehe unten.
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   Prüft mein Frontmatter: **Die Kopfzeile muss die Zahl aller Paketdateien ergeben**, und
   sie zeigt, welche Plätze leer bleiben.

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 („Hinweis für den Projektmanager")
  nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein. Ein neues Paket
  legt seinen Kasten selbst an, ohne eine gemeinsame Datei anzufassen.
- **Ein Befund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  zwölfmal bestätigt. **Jeden Befund ganz lesen** — die Adresszeile „an den
  Projektmanager" steht oft erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan. Die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` sie gibt und wer sie hält.
- **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin baut** — das ist kein
  Kriterienzuwachs, sondern ein schärferes Kriterium vor dem ersten Versuch.
- **Eine Sperre, die ein Paket auflöst, gehört in `haengt_an` — nicht in `blockiert`.**
  Prüffrage bei jedem `blockiert`: Erfüllt ein vorhandenes Paket seinen Entblockungssatz
  wörtlich? Dann `offen` mit unerfüllter `haengt_an`; der Runner entblockt in derselben
  Nacht, mein Wartelauf fällt weg. **`blockiert` heisst danach: keine Sperre, die ein Paket
  auflöst** — übrig bleiben Betreiberentscheidung (0003) und fehlende Rolle (0041). Danach
  Trockenlauf: Das Paket darf **nicht** eingeplant erscheinen.
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen.**
  `CMakeLists.txt` zuerst macht den Abbruch **rot statt still** — ersetzt aber keinen
  Zuschnitt. 0019 brach dreimal ab, Ursache war die Größe; **beim zweiten Abbruch teilen**,
  danach ging es im ersten Anlauf durch. Eine Ermahnung ist kein Zuschnitt.

## Fall (c): liefert, kann es nicht melden

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen` und werden jeden Lauf neu bezahlt.

- **Erkennungszeichen: Review = 0, während Bauplätze gelaufen sind.** Den Übergang selbst
  setzen — siebenmal getragen. Bei Code nur, wenn der Übersetzungsbericht die Probe
  **namentlich** als bestanden führt; sonst Commit plus eine an der Zieldatei gemessene
  Zahl. **Immer hinschreiben, was ich gemessen habe und was nicht.**
- **Ein Paket, das nichts bewegt hat, lief und scheiterte, lief und meldete nicht, oder
  lief nie. Die Gegenprobe trennt sie** (2026-09-03 an 0029/0039/0040), immer an der
  Zieldatei statt am Statusfeld: Zieldatei fehlt ganz → leer. Zieldatei da, aber der
  **zentrale Begriff des Pakettitels** kommt null mal darin vor → auch leer. Zieldatei da
  **und** paketeigene Bezeichner drin **und** Probe namentlich `Passed` → geliefert, nicht
  gemeldet. Namensgleiche Nachbarpakete vorher über ihre `dateien` ausschliessen.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs — auch nachdem dieselbe Form vorher durchging.
  Verlässlich: `grep`, `head`, `ls`, `wc`, `git add`/`log`/`mv`/`show`,
  `baulauf.py --trocken`. **Ich committe nicht selbst — das tut der Runner.**
- **Nie aus `~/fabrik` heraus `cd`en** (2026-09-03 wieder: `cd … && wc` abgelehnt). Pfade
  relativ zur Wurzel schreiben. **Erkennungszeichen: `Edit`/`Bash` abgelehnt, obwohl es
  letzten Lauf ging → zuerst `pwd`.** Für Muster im Unterverzeichnis das `Grep`-Werkzeug.
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt.**
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** **Vor jedem
  Nachzug in die Zieldatei sehen**, nie auf `git diff --stat` stützen — ein Commit trägt
  fremde Arbeit, dreimal belegt. Umgekehrt gilt es auch: Eine Datei **ausserhalb** der
  `dateien`-Liste im Commit ist kein Regelbruch, solange ihr Inhalt einen fremden
  Paketnamen trägt (2026-09-03: `360421d`, Architektenbetreff, +459 Zeilen fremde Arbeit).
- **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.** Ein
  gemeldeter „Kapazitätsengpass" war zur Hälfte mein nicht eingetragenes Urteil; die
  Abhilfe daraus kostet Geld und behebt nichts. **Freie Plätze entstehen durch abgenommene
  Pakete, nicht durch Umsortieren** — viermal bestätigt, zuletzt 2026-09-03, als vier
  Abnahmen die zwei wartenden `gebaut` von selbst nachrücken liessen
  (`reviewbereit()` schneidet bei vier ab, sortiert nach Urteilszahl).
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste dafür in die Abnahme. **Und die Datei aufnehmen, die der Bauagent anfassen
  *musste*** (0027: `schranken_probe.cpp`).
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot, ohne dass eine fremde Datei angefasst wurde. **Prüffrage: Legt das Paket absichtlich
  etwas Unübersetzbares an, das ein GLOB einsammelt?** Dann Reihenfolge vorschreiben statt
  ein Kriterium ergänzen: Nachweis zuerst notieren, Datei zuletzt anlegen und sofort
  löschen. Ein Abbruch mittendrin ist real (0031).
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage.**
- **Ein Prüfbefund kann beschädigt sein, und dann lügt die Konvergenzbremse.** `wc -c` auf
  den Befund, bevor ich ihm glaube — eine leere Datei trägt kein `urteil` und zählt nicht.
- **Der Kollisionsschutz sieht `gebaut` nicht** — `startbereit()` vergleicht `dateien` nur
  unter `offen` (`baulauf.py:273`). **Prüffrage bei jedem startbereiten Paket: Hält ein
  Paket auf `gebaut` eine seiner Dateien?** Dann in `haengt_an`; fünfmal angewandt.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich waren alle
  siebzehn bisher richtig; der Fehler steckt im Kriterium. **Prüffrage: Braucht der
  Nachweis einen Schreibzugriff — und steht diese Datei in `dateien`?**
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein
  Deadlock.** **Prüffrage: Kann das Paket in `haengt_an` ohne diesen Vorschlag je
  abgenommen werden?** Nein → zusammenfassen, nicht anlegen (0037 → 0027).
  Erkennungsmuster: gleiche Dateiliste **und** Rücklaufbefund.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fliesstext des Prüfers** — in beide
  Richtungen. „Kein Rücklauf in der Sache" bei `zurueck` bleibt Rücklauf; Nebenbefunde bei
  `geprueft` sind keiner, auch wenn sie schwer wiegen. Wer sie nachträglich in die Abnahme
  zieht, hebt ein bestandenes Kriterium an.
- **Doppelte Kennungen kommen von parallelen Läufen** und sind normal — 2026-09-03
  dreimal, zuletzt **drei** Pakete auf `0049`. `git mv`, `id` mitändern, vorher `grep` auf
  `haengt_an` und `ops/plan.md`. **Wer weicht, entscheidet, wer zitiert wird**; zitiert
  keiner, die Commitzeit; bei gleicher, die eigene Bitte. Alten Namen ins Paket.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge im Statusfeld.** Richtig ist
  `blockiert` plus Meldung, nicht `abgelehnt` (der Befund ist ja gut). Zwei Greps: Rolle in
  `BAUROLLEN`/`PRUEFROLLEN` (`baulauf.py:59`)? Irgendeine Rollendatei mit `Edit()` auf das
  Ziel? Bei `agents/` beides nein, und das ist Absicht.

## Offene Fährten

- **Zwei Vorschläge auf derselben Datei: serialisieren, nicht zusammenlegen** (2026-09-03,
  0047/0049 auf `reihen.toml`). Acht Bedingungen in einem Lauf sind die Größe, an der 0019
  dreimal abbrach. Das Argument gegen zwei Läufe — „jeder verschiebt die Belegstellen des
  nächsten" — ist **an der Wurzel zu beheben**, nicht durch Zusammenlegen: Der erste Lauf
  ersetzt die Zeilennummern durch Adresse plus Zitat, dann hat der zweite nichts mehr zu
  verschieben. Der zweite bekommt den ersten in `haengt_an`.
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen** — zweimal: 0011
  („`grep` findet kein Rust" gegen „drei **gemessene** Kandidaten"), 0047 („oder
  nachgemessen" gegen „dieses Paket schlägt die Ersetzung vor"). **Prüffrage in beide
  Richtungen: Verbietet mein Kriterium, was mein Fliesstext verlangt — oder erlaubt es zu
  unterlassen, was er verlangt?**
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  **Tabellennummer plus Zitat**. Auch `rueckstand.md` darf nie mit Punktnummer zitiert
  werden — ich schreibe sie je Lauf neu.
- **Ein Kriterium, das eine Datei bindet, die einem anderen Paket gehört, ist unbaubar.**
  Ist das Herkunftspaket `fertig`, ist Herkunft kein Schreibverbot — Freigabe ausschreiben.
  **Der stille Fall ist der Nachweis über ein Verzeichnis** („Mustervergleich über
  `kern/src/`"), während `dateien` nur zwei Dateien daraus führt — 0038, 2026-09-03. Er
  fällt erst beim Bauen auf und erzeugt dann einen Rücklauf gegen Arbeit, die das Paket
  nicht tun durfte. **Prüffrage beim Schreiben: Nennt mein Nachweis einen Ordner, wo
  `dateien` Dateien nennt?** Heilung: Kriterium auf die eigenen Dateien verengen und den
  Rest an das Folgepaket hängen, das ihn einlösen darf — das senkt nichts ab.
- **Eine Blockade gilt der Sache, fast nie ihrem Rahmen** — gibt es einen Modus in
  `specs/` ohne den gesperrten Teil? Das Paket ohne `haengt_an` ist die Reserve gegen einen
  blockierten kritischen Pfad.
- **Prüffrage bei jedem Abnahmekriterium: Kann die Rolle den Nachweis führen?** Der
  `datenbauer` führt kein Werkzeug, das Code ausführt; ein `pruefer` sehr wohl (`tomllib`
  lief 2026-09-03). Fähigkeit ist rollen-, nicht umgebungsgebunden.
- **Grün heisst „die Zahlen passen zueinander", nicht „sie sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. **Nennt der
  `ctest`-Abschnitt je Kasten einen Test mit Namen?** (`# PLATZHALTER` erzeugt kein Ziel →
  „No tests were found!!!" bei `ergebnis: ok`.)
- **Widerlegt 2026-09-03:** Zwei Agenten derselben Rolle in einer Phase stören sich nicht.
  Fährte zu.
- **Der Abschnitt „was ich nicht ausführen konnte" eines Befunds ist eine Fähigkeits\-
  aussage für meine Kriterien** — aber sie gilt je Lauf, nicht je Umgebung (am selben Tag
  scheiterte ein Prüfer ausserhalb des Repos, ein zweiter baute dort). Also staffeln: Ort
  A, sonst Ort B, sonst ausgewiesene Nichtmessung. Auch umgekehrt lesen: Was ein Prüfer
  heute ausgeführt hat, widerlegt ein „geht hier nicht" in einer Datei (2026-09-03,
  `tomllib` gegen `reihen.toml` → Paket 0049).
- **Zuschnittsfrage: Zwingt mein Paket jemanden, die `CMakeLists.txt` zu ändern?** Nein →
  es kollidiert mit nichts (der GLOB sammelt neue Dateien selbst ein).
