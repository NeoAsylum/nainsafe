# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz; **jede neue kostet eine alte.** Neu begonnen am 2026-09-04, Ausgeschiedenes in
`notizen/archiv/projektmanager-2026-09-04.md` — **dort nachsehen, bevor ich eine Lehre für
neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' -25`.** Wer hat geliefert? Dagegen halten, wessen Paket
   den Status gewechselt hat. **Die Differenz sind die Fälle (c) und (d) unten.**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archivierte Pakete = Zahl der Paketdateien** (2026-09-04: 69 + 1 = 70).
   Liegt `ls | wc -l` darüber, sind es erst archivierte Pakete, dann Fehler.

## Die Lehre des 2026-09-04: der Nachzug ist der Hebel — und nicht die ganze Ursache

**Nachzug zuerst.** `reviewbereit()` schneidet bei vier ab und sortiert nach Rücklaufzahl
(`baulauf.py:264`); vier Pakete mit null Rückläufen belegen alle Plätze dauerhaft, und wer
einmal zurückkam, kommt nie dran. Zwei Läufe Nachzug brachten die Schlange von vier auf zwei.
**Ein Lauf, der nur Pakete anlegt, verstopft die Fabrik.**

**Fall (e): der Prüfer liefert nicht.** 0011 kam einmal ohne Befund vom Prüfplatz und war im
Durchgang darauf `geprueft` — **Einzelfall, Ursache war die Schlange.** Detektor wie (c)/(d):
Paket weiter `gebaut`, Commit mit seinem Namen, `befunde/pruefung-<paket>-*` unverändert.
Erst beim zweiten Mal melden.

**Teilen hilft nur, wo etwas Halbes dasteht.** Schnitt entlang der Prüfbedingungen, nie
zwischen Gerüst und Inhalt — sonst ist die erste Hälfte ein grüner Test über nichts.

## 2026-09-04: wann `blockiert` falsch ist, obwohl der Zähler bei drei steht

**Die Regel nennt zwei Ursachen — Abnahmekriterium oder Vorgabe. Kann ich beide widerlegen,
greift sie nicht.** 0059: Nach dem verengten Zuschnitt kam **gar nichts** statt zu wenig; zu
großer Zuschnitt erzeugt Abbrüche auf halbem Weg, keinen Nullstand. Die Vorgabe war
dieselbe, unter der das Paket vorher 91 Zeilen erzeugt hat.

**Zweite Prüffrage, die stärkere: Was rückt nach?** Ist die Ursache die *Rolle*, holt die
Sperre nur das nächste Paket derselben Rolle in den Platz — nichts geheilt, und die
abgetrennte Hälfte (0067 an 0059) geht mit unter. Dann ist es eine Meldung, kein `blockiert`.

**Leerlauf nur zählen, wenn der Bauplatz nachweisbar belegt war.** Kein Commit mit der
Kennung = kein Beleg. Sonst sperre ich auf Vermutung.

**Bauplätze gehen nach Paketnummer, also nach Alter** (`sorted(glob)`, Schnitt bei vier,
`baulauf.py:301`): **alte Sorgenpakete halten die Plätze nach Dienstalter**, hochnummerierte
Reserve läuft nie. Preis des Nichtsperrens — in Plätzen ausrechnen und melden.

## Die teuerste Lehre, zweimal in derselben Kette bezahlt

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor und
nicht den Wortlaut.** Ein vorgeschriebener Halbsatz wandert ungeprüft in die Datei; findet
der Prüfer ihn falsch, kann der Bauagent nichts dafür (0028 → 0042 → 0053; 0065 ist eine
Generation weiter — dort zählte ein selbst erfundener Satz sich zweimal mit).
**Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in Anführungszeichen, den der
Bauagent abschreiben soll? Dann streichen und durch die Bedingung ersetzen.**

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`; Abschnitt 13 nennt Kollisionsschnitt und Reihenfolge.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), der GLOB sammelt sie ein. **Zwingt mein Paket jemanden, die
  `CMakeLists.txt` zu ändern?** Nein → es kollidiert nicht.
- **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`**, oft bestätigt. **Jeden
  Befund ganz lesen** — „an den Projektmanager" steht meist erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Eine Sperre, die ein Paket auflöst, gehört in `haengt_an` — nicht in `blockiert`.**
  Übrig bleiben Betreiberentscheidung (0003) und fehlende Rolle (0041).
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. Eine Ermahnung ist kein Zuschnitt. Beim ersten den **gemessenen
  Zwischenstand** ins Paket (welche Datei wie weit), damit der nächste Lauf nicht bei null
  anfängt.

## Fall (c) und Fall (d): was der Commit-Betreff verspricht

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen`. Zehnmal getragen — als Vorlage an den Betreiber gemeldet.

- **(c) liefert, meldet nicht** — stand in der vorigen Bau-Liste, hat committet, Status
  unverändert. **(d) meldet, liefert nicht** — Commit trägt seinen Namen, Zieldatei
  unberührt; getragen hat er fremde Arbeit. **Ein belegter Bauplatz belegt keine Arbeit.**
- **Gegenprobe für beide ist immer die Zieldatei**, `git log -- <zieldatei>`: fehlt sie oder
  fehlt der **zentrale Begriff des Pakettitels** → leer; paketeigene Bezeichner drin und
  Probe namentlich `Passed` → geliefert. **Immer hinschreiben, was ich gemessen habe.**

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
- **Heilung dafür ist ein Ort, nicht eine breitere Liste.** Verlangt ein Kriterium einen
  Eingriff in eine fremde Datei (0069: Rotnachweis im Wurzel-`CMakeLists.txt`), schreibe ich
  den Nachweis auf eine Kopie unter `befunde/<messung>/`. Erweitern würde gegen den
  Beanspruchenden serialisieren; und `baulauf.py` übersetzt **jedes** Verzeichnis außer
  `befunde/`, eine Baumkopie anderswo macht den Übersetzungsbericht unbrauchbar.
  Präzedenz 0063.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock**
  — gleiche Dateiliste **und** Rücklaufbefund.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext** — in beide Richtungen.
  Nebenbefunde bei `geprueft` sind kein Rücklauf, auch wenn sie schwer wiegen; sie bekommen
  ein eigenes Paket. **Und ich schreibe in das abgenommene Paket, wohin der Nebenbefund
  gegangen ist** — sonst sucht ihn der nächste Leser im Befund und findet keinen Auftrag.
- **Doppelte Kennungen kommen von parallelen Läufen** und sind normal. `git mv`, `id`
  mitändern, vorher `grep` auf `haengt_an`, `befunde/` und `ops/plan.md`; alten Namen ins
  Paket. **Die Zitierform entscheidet vor der Commitzeit: die bloße Kennung bleibt, der
  volle Name weicht.** Zweimal angewandt.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge.** Richtig ist `blockiert`
  plus Meldung, nicht `abgelehnt`. Zwei Greps: Rolle in `BAUROLLEN`/`PRUEFROLLEN`
  (`baulauf.py:59`)? Irgendeine Rollendatei mit `Edit()` auf das Ziel?
- **Verlangt ein Kriterium einen Lauf: staffeln** (`$TMPDIR`, sonst `befunde/`, sonst
  ausgewiesene Nichtmessung). Dreimal kostenlos aufgegangen.
- **Ein Kriterium „das Muster trifft nichts, ausgenommen X" widerspricht sich selbst.**
  Heilung: alle Treffer aufzählen und klassifizieren, statt null zu verlangen.
- **Wer ein neues Bauglied anlegt, muss auch die Datei beanspruchen, die es anmeldet**
  (`FABRIK_MITGLIEDER` in der `CMakeLists.txt` des Arbeitsbereichs, keine GLOB-Sammlung).

## Die Falle mit der absoluten Zahl — vierter Fall

**Nennt ein Kriterium eine Zahl aus einer Summe — und schreibt ein anderes offenes Paket in
dieselbe Datei?** Dann ist die Abnahme durch fremde Arbeit unerfüllbar. Viermal. **Heilung
ist die Bedingung statt der Zahl** („selbst nachzählen; weicht es ab, nenne die Differenz
und was sie trägt"), nie eine Reihenfolge. 0068: 23/4/27 gestrichen, vier Pakete auf
`technik.md`.

**Zwilling: der Nachweis, der an der Datei hängt, die er selbst ändert.** Heilung:
**Bezugsstand nennen und nach dem letzten Schreiben nachmessen.**

## Offene Fährten

- **Ein Paket, das eine neue `CMakeLists.txt` anlegt, steht ab dem ersten Teilstand im
  Übersetzungsbericht.** Eine halbe Bauliste ist ein grüner Bericht über nichts.
  **Zuschnittsfrage: Kommt das Paket in einem Lauf bis zum laufenden Test? Wenn nein, ist
  die Bauliste ein eigenes Paket.**
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen.** **In beide
  Richtungen prüfen: Verbietet mein Kriterium, was mein Fließtext verlangt — oder erlaubt es
  zu unterlassen, was er verlangt?**
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  Abschnittsüberschrift plus Zitat. Auch `rueckstand.md` nie mit Punktnummer zitieren.
- **Ein Kriterium, das eine fremde Datei bindet, ist unbaubar.** Stiller Fall: Nachweis über
  ein **Verzeichnis**, während `dateien` nur Dateien führt.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden.
- **Ein Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis.**
- **2026-09-04 offen:** Rollenfrage `testentwickler` liegt beim Geschäftsführer.
