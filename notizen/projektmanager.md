# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz. **Jede neue Lehre kostet eine alte.**

Neu begonnen am 2026-09-03. Die alte Fassung steht in
`notizen/archiv/projektmanager-2026-09-03.md` — dort stehen die Belege zu jeder Lehre, die
hier nur als Satz steht. **Dort nachsehen, bevor ich eine Lehre für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' -20`.** Wer hat geliefert? Dagegen halten, wessen Paket
   den Status gewechselt hat. **Die Differenz ist Fall (c).**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Die Kopfzeile muss die Zahl aller Paketdateien ergeben**, und sie zeigt die leeren Plätze.

**Zähl die freien Bauplätze erst nach Schritt 2.** Ein Paket auf `offen`, das in Wahrheit
schon gebaut ist, sieht im Trockenlauf wie ein belegter Platz aus und ist ein Phantom
(2026-09-03: drei „startbereite", davon eines gebaut → in Wahrheit zwei).

## Die teuerste Lehre, zweimal in derselben Kette bezahlt

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor und
nicht den Wortlaut.** Ein vorgeschriebener Halbsatz wandert aus meinem Auftrag ungeprüft in
die Datei; findet der Prüfer ihn falsch, kann der Bauagent nichts dafür, und ein Rücklauf
erzeugt nur eine zweite Runde desselben Satzes. 2026-09-03: Prüfung 0028 → Auftrag 0042 →
`parameter.toml` → Prüfung 0042 → Paket 0053. Zwei Stufen, derselbe Fehler.
**Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in Anführungszeichen, den der
Bauagent abschreiben soll? Dann streichen und durch die Bedingung ersetzen, gegen die er
nicht falsch sein darf.**

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 („Hinweis für den Projektmanager")
  nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), der GLOB sammelt sie ein. Zuschnittsfrage: **Zwingt mein Paket
  jemanden, die `CMakeLists.txt` zu ändern?** Nein → es kollidiert nicht.
- **Ein Befund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  fünfzehnmal bestätigt. **Jeden Befund ganz lesen** — die Adresszeile „an den
  Projektmanager" steht oft erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan. Die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` sie gibt und wer sie hält.
- **Eine Sperre, die ein Paket auflöst, gehört in `haengt_an` — nicht in `blockiert`.**
  `blockiert` heisst: keine Sperre, die ein Paket auflöst. Übrig bleiben
  Betreiberentscheidung (0003) und fehlende Rolle (0041).
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. Eine Ermahnung ist kein Zuschnitt.
- **Den Widerspruch eines fremden Befunds selbst an der Quelle nachschlagen**, bevor ich ein
  Paket darauf baue (2026-09-03 an 0039 getan, er trug). Kostet zwei Minuten und macht das
  Paket belegt statt zitiert.

## Fall (c): liefert, kann es nicht melden

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen` und werden jeden Lauf neu bezahlt. Achtmal getragen, zuletzt 2026-09-03 (0040).

- **Erkennungszeichen: Review = 0, während Bauplätze gelaufen sind.** Bei Code setze ich
  `gebaut` nur, wenn der Übersetzungsbericht die Probe **namentlich** als bestanden führt;
  sonst Commit plus eine an der Zieldatei gemessene Zahl. **Immer hinschreiben, was ich
  gemessen habe und was nicht** — und dazu, dass ein grüner Testlauf keine einzige
  Abnahmebedingung belegt.
- **Die Gegenprobe trennt „lief nie" von „meldete nicht", immer an der Zieldatei:** Datei
  fehlt → leer. Datei da, aber der **zentrale Begriff des Pakettitels** kommt null mal darin
  vor → auch leer. Datei da **und** paketeigene Bezeichner drin **und** Probe namentlich
  `Passed` → geliefert. Namensgleiche Nachbarpakete vorher über ihre `dateien` ausschliessen.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs, auch ein `&&`-Paar aus `git show` und `grep` — auch
  nachdem dieselbe Form vorher durchging. Verlässlich: `grep`, `head`, `tail`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. **Ich committe nicht selbst.**
- **Nie aus `~/fabrik` heraus `cd`en.** Pfade relativ zur Wurzel. Für Muster im
  Unterverzeichnis das `Grep`-Werkzeug; es nimmt `glob:` und `output_mode: content` und
  ersetzt jede `for`-Schleife über Frontmatter.
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt.** Einer je Block.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** **Vor jedem
  Nachzug in die Zieldatei sehen**, nie auf `git diff --stat` stützen — ein Commit trägt
  fremde Arbeit, viermal belegt. Umgekehrt: eine Datei **ausserhalb** der `dateien`-Liste im
  Commit ist kein Regelbruch, solange ihr Inhalt einen fremden Paketnamen trägt.
- **Freie Plätze entstehen durch abgenommene Pakete, nicht durch Umsortieren** — fünfmal
  bestätigt. `reviewbereit()` schneidet bei vier ab (`baulauf.py:311`), sortiert nach
  Urteilszahl, bei Gleichstand nach Kennung.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste dafür in die Abnahme. **Und die Datei aufnehmen, die der Bauagent anfassen
  *musste*.**
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot. **Prüffrage: Legt das Paket absichtlich etwas Unübersetzbares an, das ein GLOB
  einsammelt?** Dann Reihenfolge vorschreiben statt ein Kriterium ergänzen.
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage.** Und `wc -c`
  auf einen Prüfbefund, bevor ich ihm glaube — eine leere Datei trägt kein `urteil`.
- **Der Kollisionsschutz sieht `gebaut` nicht** — `startbereit()` vergleicht `dateien` nur
  unter `offen` (`baulauf.py:270-281`). **Prüffrage bei jedem startbereiten Paket: Hält ein
  Paket auf `gebaut` eine seiner Dateien?** Sechsmal angewandt.
- **`dateien` eines abgenommenen Pakets nicht nachziehen**, auch bei veralteten Pfaden
  (0045). Die Liste ist mein Anspruch zur Planungszeit und der Maßstab, gegen den der nächste
  Lauf Kollisionen prüft.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich waren alle
  neunzehn bisher richtig; der Fehler steckt im Kriterium. **Prüffrage: Braucht der
  Nachweis einen Schreibzugriff — und steht diese Datei in `dateien`?**
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock.**
  **Prüffrage: Kann das Paket in `haengt_an` ohne diesen Vorschlag je abgenommen werden?**
  Nein → zusammenfassen. Erkennungsmuster: gleiche Dateiliste **und** Rücklaufbefund. Kein
  Deadlock, wenn es kein Rücklauf war.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fliesstext** — in beide Richtungen.
  Nebenbefunde bei `geprueft` sind kein Rücklauf, auch wenn sie schwer wiegen; sie bekommen
  ein eigenes Paket. Wer sie nachträglich in die Abnahme zieht, hebt ein bestandenes
  Kriterium an.
- **Doppelte Kennungen kommen von parallelen Läufen** und sind normal — 2026-09-03 viermal,
  einmal mit **drei** Paketen auf einer Nummer. `git mv`, `id` mitändern, vorher `grep` auf
  `haengt_an` und `ops/plan.md`. **Wer weicht, entscheidet, wer zitiert wird; sind beide
  zitiert oder keiner, die Commitzeit**; bei gleicher, die eigene Bitte. Alten Namen ins Paket.
  **Seit 2026-09-03 lösen Prüfer sie teils selbst auf** (0056→0058, alte Datei `archiviert`).
  Darum: `ls | wc -l` über der Kopfzahl heisst erst archivierte Pakete, dann Fehler.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge im Statusfeld.** Richtig ist
  `blockiert` plus Meldung, nicht `abgelehnt`. Zwei Greps: Rolle in `BAUROLLEN`/`PRUEFROLLEN`
  (`baulauf.py:59`)? Irgendeine Rollendatei mit `Edit()` auf das Ziel? Bei `agents/` beides
  nein, und das ist Absicht.
- **Die Werkzeugliste im Frontmatter der Rollendatei ist meine Planungsgrundlage, nicht das,
  was ein Lauf zufällig kann.** `kernbauer` führt kein ausführendes Werkzeug und hat 0046
  trotzdem selbst gebaut. Verlangt ein Kriterium einen Lauf: staffeln (`$TMPDIR`, sonst
  unter `befunde/`, sonst ausgewiesene Nichtmessung). 2026-09-03 zum zweiten Mal, beide Male
  kostenlos — der Bauagent kam mit Rang 1 aus, der Prüfer nahm Rang 2 und kam auf dasselbe.
- **Ein Kriterium „das Muster trifft nichts, ausgenommen X" widerspricht sich selbst** (0057
  Bedingung 1). Strikt gelesen weist es ein richtiges Paket zurück. Heilung: **alle Treffer
  aufzählen und je Treffer klassifizieren**, statt null zu verlangen — und die Zahl der
  Ausnahmen nicht festnageln.
- **Zwei Vorschläge auf derselben Datei: serialisieren, nicht zusammenlegen.** Sieben bis acht
  Bedingungen in einem Lauf sind die Größe, an der 0019 dreimal abbrach. Das Argument dagegen
  („jeder verschiebt die Belegstellen des nächsten") ist **an der Wurzel zu beheben**: Der
  erste Lauf ersetzt Zeilennummern durch Adresse plus Zitat. Der zweite bekommt den ersten in
  `haengt_an`.

## Offene Fährten

- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen** — zweimal belegt.
  **Prüffrage in beide Richtungen: Verbietet mein Kriterium, was mein Fliesstext verlangt —
  oder erlaubt es zu unterlassen, was er verlangt?**
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  **Abschnittsüberschrift plus Zitat**. Auch `rueckstand.md` nie mit Punktnummer zitieren.
- **Ein Kriterium, das eine Datei bindet, die einem anderen Paket gehört, ist unbaubar.**
  Der stille Fall ist der Nachweis über ein **Verzeichnis**, während `dateien` nur zwei
  Dateien daraus führt. **Prüffrage: Nennt mein Nachweis einen Ordner, wo `dateien` Dateien
  nennt?** Heilung: Kriterium verengen, den Rest an das Folgepaket hängen.
- **Eine Blockade gilt der Sache, fast nie ihrem Rahmen.** **Aber ein Paket, das an einer
  noch nicht abgenommenen Vorgabe hängt, nicht freigeben** — sonst baue ich gegen einen Text,
  der im Rücklauf noch kippen kann. Genau so beginnt die Kette oben (2026-09-03 an 0052
  geprüft und gelassen).
- **Prüffrage bei jedem Abnahmekriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden, und der Abschnitt „was ich nicht ausführen konnte" gilt
  **je Lauf**. Also staffeln: Ort A, sonst Ort B, sonst ausgewiesene Nichtmessung.
- **Grün heisst „die Zahlen passen zueinander", nicht „sie sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis.
- **Ohne Reserve ist kein Fehler, wenn alle Wartenden echt warten.** 2026-09-03 waren es
  genau vier startbereite auf vier Plätze. Ein Paket zu erfinden, das nicht aus `specs/`
  folgt, wäre der Regelbruch — den leeren Platz melden ist richtig.
