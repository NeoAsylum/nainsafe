# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz; **jede neue kostet eine alte.** Neu begonnen am 2026-09-04 (zweites Mal),
Ausgeschiedenes in `notizen/archiv/projektmanager-2026-09-04-2.md` — **dort nachsehen,
bevor ich eine Lehre für neu halte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=short -30`.** Wer hat geliefert? Dagegen halten,
   wessen Paket den Status gewechselt hat. **Die Differenz sind die Fälle (c) und (d).**
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   **Kopfzahl + archivierte Pakete = `ls aufgaben/*.md | wc -l`** (2026-09-04: 71 + 1 = 72).

## Die Lehre des 2026-09-04: erst die Sperren zählen, die nur Reihenfolge waren

**Der größte Hebel eines Laufs war nicht ein neues Paket, sondern das Verengen einer
`dateien`-Liste.** 0027 kam zum zweiten Mal zurück; beim Verengen von fünf Dateien auf eine
fielen **zwei** `haengt_an`-Einträge weg, die ich selbst gesetzt hatte — beide nur wegen der
unsichtbaren Kollision (`gebaut` hält Dateien, `startbereit()` sieht sie nicht). Zwei
Pakete hatten einen Tag auf eine reine Reihenfolgesperre gewartet.

**Prüffrage bei jedem Rücklauf: Welche `haengt_an`-Einträge zeigen hierher, und sind sie
inhaltlich oder nur Kollisionsschutz?** Steht der Grund im Annahmevermerk („hält Datei X"),
fällt er mit der Verengung — nachlesen, nicht raten.

## Wann `blockiert` richtig ist — die Frage ist nicht der Zähler

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Bei 0059 hing 0067 daran → nicht sperren, melden. Bei 0061 hing nichts daran und der Plan
nannte es nicht → sperren, obwohl ich **alle vier** Ursachen (Kriterium, Vorgabe, Zuschnitt,
Rolle) einzeln nachgemessen und widerlegt hatte.

**Dann schreibe ich in das Paket, was `blockiert` hier *nicht* heißt** — nicht „das
Kriterium ist falsch", sondern „die Ursache liegt außerhalb dessen, was meine Rolle prüfen
kann". Sonst liest der Nächste ein Urteil über den Auftrag.

**Einen angekündigten Auslöser ziehe ich, oder ich hätte ihn nicht ankündigen dürfen.**
Zweimal daran vorbeizuargumentieren macht jede weitere Ankündigung wertlos.

**Leerlauf nur zählen, wenn ein Commit die Kennung im Betreff trägt.** Sonst sperre ich auf
Vermutung. **Bauplätze gehen nach Paketnummer** (`baulauf.py:301`): Ein altes Sorgenpaket
hält seinen Platz nach Dienstalter. Preis in Plätzen ausrechnen und melden.

## Aus einer Korrelation über zwei Pakete keine Ursache machen

**Die teuerste Fehldiagnose des 2026-09-04.** Aus drei leeren Bauplätzen über zwei Pakete
habe ich auf eine schwache **Rolle** geschlossen und das gemeldet. Im selben Durchgang hat
dieselbe Rolle 458 Zeilen geliefert, und ein abgenommenes Paket derselben Rolle hatte
dieselbe Zieldatei schon gebaut.

**Zwei Gegenproben, bevor ich eine Rolle beschuldige:** Hat sie *irgendwo* in demselben
Zeitraum geliefert? Gibt es ein `fertig`-Paket derselben Rolle mit derselben `dateien`-Liste?
Beides ist ein `grep`, und beides hätte die Meldung verhindert.

**Widerrufen gehört in dieselben Dateien wie die Meldung** — Paket, Rückstand, hier.

## Die teuerste Lehre, mehrfach in derselben Kette bezahlt

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor und
nicht den Wortlaut.** Ein vorgeschriebener Halbsatz wandert ungeprüft in die Datei; findet
der Prüfer ihn falsch, kann der Bauagent nichts dafür (0028 → 0042 → 0053, dann 0065).
**Prüffrage: Steht in meinem *Was zu tun ist* ein Satz in Anführungszeichen, den der
Bauagent abschreiben soll? Dann streichen und durch die Bedingung ersetzen.**

## Die Falle mit der absoluten Zahl — fünfter Fall

**Nennt ein Kriterium eine Zahl aus einer Summe — und schreibt ein anderes offenes Paket in
dieselbe Summe?** Dann ist die Abnahme durch fremde Arbeit unerfüllbar. Fünfmal.
**Heilung ist die Bedingung statt der Zahl**, und zwar **je Datei**: Der Riegel meldete „4
Treffer", einer lag bei 0027, drei bei 0044 — keines von beiden kann „0" belegen, beide
können „in *meiner* Datei kein Treffer mehr" belegen.

**Zwilling: der Nachweis, der an der Datei hängt, die er selbst ändert.** Heilung:
**Bezugsstand nennen und nach dem letzten Schreiben nachmessen.**

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`; Abschnitt 13 nennt Kollisionsschnitt und Reihenfolge.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), der GLOB sammelt sie ein. **Zwingt mein Paket jemanden, die
  `CMakeLists.txt` zu ändern?** Nein → es kollidiert nicht.
- **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.** **Jeden Befund ganz
  lesen** — „an den Projektmanager" steht meist erst hinter der Abnahmetabelle.
- **Lässt ein Prüfer mir ausdrücklich zwei Wege, wählt er keinen — das ist meine Arbeit,
  nicht seine Unentschlossenheit.** Und ich schreibe die Wahl in **beide** Pakete.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. Beim ersten den **gemessenen Zwischenstand** ins Paket (welche Datei
  wie weit), damit der nächste Lauf nicht bei null anfängt.
- **`RUECKLAUF_MAX = 3`** (`baulauf.py:87`): Bei drei Rückläufen bekommt ein Paket weder
  Bau- noch Prüfplatz. **Bei zwei ist der Zuschnitt fällig, nicht bei drei** — sonst gehen
  die daran hängenden Pakete mit.

## Fall (c) und Fall (d): was der Commit-Betreff verspricht

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen`. Elfmal getragen — als Vorlage an den Betreiber gemeldet.

- **(c) liefert, meldet nicht** — hat committet, Status unverändert. **(d) meldet, liefert
  nicht** — Commit trägt seinen Namen, Zieldatei unberührt. **Ein belegter Bauplatz belegt
  keine Arbeit.**
- **Gegenprobe für beide ist immer die Zieldatei**, `git log -- <zieldatei>`: fehlt der
  **zentrale Begriff des Pakettitels** → leer; paketeigene Bezeichner drin und Probe
  namentlich `Passed` → geliefert. **Immer hinschreiben, was ich gemessen habe.**
- **Fall (c) kann eine ganze Fehldiagnose tragen.** 0059 galt drei Fassungen lang als
  Sorgenfall und war geliefert.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs. Verlässlich: `grep`, `head`, `tail -n`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. **Ich committe nicht selbst.**
- **Nie aus `~/fabrik` heraus `cd`en.** Die Arbeitsrichtung überlebt den Aufruf; nach einem
  `cd` scheitert jedes `Edit(ventures/**)` mit „don't ask mode" statt mit einem Pfadfehler.
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer** (48 kB). Nur
  `^status:` oder `^haengt_an:` greppen, nie beides mit den langen Feldern zusammen.
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status:` steht in
  manchen Paketen zweimal — **mit der `rolle:`-Zeile davor ankern**, nie `replace_all`.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** Die Bündelung
  des Baulaufs verschiebt fremde Arbeit um einen Commit. Umgekehrt ist eine Datei
  **ausserhalb** der `dateien`-Liste im Commit kein Regelbruch, solange ihr Inhalt einen
  fremden Paketnamen trägt.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste dafür in die Abnahme. **Und die Datei aufnehmen, die der Bauagent anfassen
  *musste*.** Dazu ins Paket schreiben, welche Dateien er **nicht** mehr anfassen darf und
  welches fremde Paket sie jetzt hält.
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot.
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage.**
- **Der Kollisionsschutz sieht `gebaut` nicht** (`baulauf.py:270-281`). **Prüffrage bei
  jedem startbereiten Paket: Hält ein Paket auf `gebaut` eine seiner Dateien?**
- **`dateien` eines *abgenommenen* Pakets nicht nachziehen** — die Liste ist der Maßstab,
  gegen den der nächste Lauf Kollisionen prüft. Beim Rücklauf gilt das Gegenteil.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich sind sie
  fast immer richtig; der Fehler steckt im Kriterium oder in der Liste.
- **Zwei Vorschläge können dieselbe Arbeit sein, von zwei Gewerken gefunden.** 0070
  (Riegelmessung) und 0044 (Handnachschlag) nannten dieselben drei Schlüssel in derselben
  Datei. **Vor dem Annehmen: Hält ein offenes Paket diese Datei schon — und tut es dort
  dasselbe?** Dann zusammenfassen, auch wenn die Befunde unabhängig entstanden sind.
- **Ein Vorschlag mit zwei Dateien kann zwei Rollen sein.** Der Schnitt entlang der Gewerke
  ist dann der richtige, kein Zugeständnis an die Mechanik.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock**
  — besonders wenn ich eine Bedingung *dorthin* verlege. Dann `haengt_an` streichen und
  begründen.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext.** Nebenbefunde bei
  `geprueft` sind kein Rücklauf; sie bekommen ein eigenes Paket — **oder ausdrücklich
  keines**, wenn sie eine Entwurfsfrage sind. Dann in den Rückstand, nicht ignorieren.
- **Doppelte Kennungen kommen von parallelen Läufen.** `git mv`, `id` mitändern, vorher
  `grep` auf `haengt_an`, `befunde/`, `ops/plan.md`; alten Namen ins Paket. **Die bloße
  Kennung bleibt, der volle Name weicht.**
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge.** Zwei Greps: Rolle in
  `BAUROLLEN`/`PRUEFROLLEN` (`baulauf.py:59`)? Rollendatei mit `Edit()` auf das Ziel?
- **Verlangt ein Kriterium einen Lauf: staffeln** (`$TMPDIR`, sonst `befunde/`, sonst
  ausgewiesene Nichtmessung). **Verlangt es einen Eingriff in eine fremde Datei: Nachweis
  auf eine Kopie unter `befunde/<messung>/`** — `baulauf.py` übersetzt jedes Verzeichnis
  außer `befunde/`.

## Offene Fährten

- **2026-09-04, nachzuprüfen im nächsten Lauf:** In jedem Durchgang, in dem **zwei Pakete
  derselben Rolle** einen Bauplatz hatten, hat höchstens eines geliefert (0059/0061 dreimal).
  Der nächste Durchgang plant 0027 und 0048 — **beide `kernbauer`**. Liefern beide, ist die
  Korrelation tot; liefert nur eines, ist es der vierte Fall und gehört gemeldet.
- **Ein Paket, das eine neue `CMakeLists.txt` anlegt, steht ab dem ersten Teilstand im
  Übersetzungsbericht.** **Zuschnittsfrage: Kommt es in einem Lauf bis zum laufenden Test?**
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen.** In beide Richtungen
  prüfen.
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  Abschnittsüberschrift plus Zitat, **nie die nachgezogene Nummer** — sie ist beim nächsten
  Lauf wieder falsch. Seit dem 2026-09-04 misst der Riegel aus 0059 das automatisch.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden.
- **Ein Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis.**
