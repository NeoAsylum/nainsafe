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
   **Kopfzahl + archivierte Pakete = `ls aufgaben/*.md | wc -l`** (2026-09-04: 74 + 1 = 75).

## Erst die Sperren zählen, die nur Reihenfolge waren

**Der größte Hebel eines Laufs ist oft nicht ein neues Paket, sondern das Verengen einer
`dateien`-Liste.** Bei 0027 fielen damit **zwei** `haengt_an`-Einträge weg, beide nur wegen
der unsichtbaren Kollision (`gebaut` hält Dateien, `startbereit()` sieht sie nicht).

**Prüffrage bei jedem Rücklauf: zeigen `haengt_an`-Einträge hierher, und sind sie inhaltlich
oder nur Kollisionsschutz?** Steht der Grund im Annahmevermerk („hält Datei X"), fällt er
mit der Verengung — nachlesen, nicht raten. **Umgekehrt im Annahmevermerk hinschreiben,
welche Sorte ich setze.**

## Wann `blockiert` richtig ist — die Frage ist nicht der Zähler

**Die stärkere Prüffrage ist „Was rückt nach?", nicht „Kann ich die Ursache widerlegen?"**
Bei 0059 hing 0067 daran → nicht sperren, melden. Bei 0061 hing nichts daran → sperren,
obwohl ich alle vier Ursachen (Kriterium, Vorgabe, Zuschnitt, Rolle) widerlegt hatte.

**Dann schreibe ich in das Paket, was `blockiert` hier *nicht* heißt** — „die Ursache liegt
außerhalb dessen, was meine Rolle prüfen kann". Sonst liest der Nächste ein Urteil über den
Auftrag. **Einen angekündigten Auslöser ziehe ich**, sonst ist jede weitere Ankündigung
wertlos. **Leerlauf nur zählen, wenn ein Commit die Kennung im Betreff trägt.**
**Bauplätze gehen nach Paketnummer** (`baulauf.py:301`) — Preis in Plätzen melden.

## Aus einer Korrelation über zwei Pakete keine Ursache machen

**Zwei Gegenproben, bevor ich eine Rolle beschuldige:** Hat sie *irgendwo* im Zeitraum
geliefert? Gibt es ein `fertig`-Paket derselben Rolle mit derselben `dateien`-Liste?
**Widerrufen gehört in dieselben Dateien wie die Meldung.** **Stirbt eine Vermutung, gehe
ich zu jeder Sperre zurück, die auf ihr mitstand, und prüfe *gegen* sie** — 0061 hielt, weil
die Sperre auf einer Messung an der Zieldatei stand, nicht auf der Korrelation.

## Der Statusnachzug ist Kapazität, nicht Buchhaltung

**2026-09-04, zweiter Lauf.** Vier Prüfplätze hielten Pakete, deren Befund schon `geprueft`
sagte — darunter der Platz, auf den **Vorrang Nr. 2** wartete. Kein neues Paket, keine
Umplanung: drei `fertig` haben den Stau aufgelöst.

**Plätze gehen an das, was dasteht, nicht an das, was fertig ist.** Ein nicht eingetragener
Befund kostet exakt einen Platz je Durchgang. **Deshalb Schritt 3 vor Schritt 4** — „nur
Nachzug" ist nie ein leerer Lauf. Zweitwirkung mitzählen: 0048 `fertig` machte 0056 startbereit.

## Die Bedingung vorschreiben, nie den Wortlaut

**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor.** Ein
vorgeschriebener Halbsatz wandert ungeprüft in die Datei; findet der Prüfer ihn falsch, kann
der Bauagent nichts dafür (0028 → 0042 → 0053, dann 0065). **Prüffrage: Steht in meinem *Was
zu tun ist* ein Satz in Anführungszeichen zum Abschreiben? Dann durch die Bedingung ersetzen.**

## Die Falle mit der absoluten Zahl — sechster Fall (0074)

**Nennt ein Kriterium eine Zahl aus einer Summe — und schreibt ein anderes offenes Paket in
dieselbe Summe?** Dann ist die Abnahme durch fremde Arbeit unerfüllbar. Sechsmal.
**Heilung ist die Bedingung statt der Zahl**, und zwar **je Datei** („in *meiner* Datei kein
Treffer mehr", nie „0 Treffer"). **Zwilling: der Nachweis, der an der Datei hängt, die er
selbst ändert.** Heilung: **Bezugsstand nennen und nach dem letzten Schreiben nachmessen.**

**Der Konflikt steckt im `grep`-Pfad, nicht in der Zahl** — `dateien` aller offenen Pakete
gegen den Pfad halten (0074: `kern/src kern/include` gegen 0071).

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`; Abschnitt 13 nennt Kollisionsschnitt und Reihenfolge.
- **In C++ ist der Kollisionsschnitt der Kastenschnitt** (Kopf, Quelle, Probe; der GLOB
  sammelt sie ein). **Zwingt mein Paket jemanden, die `CMakeLists.txt` zu ändern?** Nein →
  es kollidiert nicht.
- **`geprueft`-Befunde sind die bessere Paketquelle als `zurueck`.** **Jeden Befund ganz
  lesen** — „an den Projektmanager" steht meist erst hinter der Abnahmetabelle.
- **Lässt ein Prüfer mir ausdrücklich zwei Wege, wählt er keinen — das ist meine Arbeit,
  nicht seine Unentschlossenheit.** Und ich schreibe die Wahl in **beide** Pakete.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`. Die Datei ist die Kollisionseinheit.**
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen** — beim
  **zweiten** Abbruch. Beim ersten den **gemessenen Zwischenstand** ins Paket.
- **`RUECKLAUF_MAX = 3`** (`baulauf.py:87`): Bei drei Rückläufen bekommt ein Paket weder
  Bau- noch Prüfplatz. **Bei zwei ist der Zuschnitt fällig, nicht bei drei** — sonst gehen
  die daran hängenden Pakete mit.

## Fall (c) und Fall (d): was der Commit-Betreff verspricht

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen`. Elfmal getragen — als Vorlage an den Betreiber gemeldet.

- **(c) liefert, meldet nicht** — committet, Status unverändert. **(d) meldet, liefert
  nicht** — Commit trägt seinen Namen, Zieldatei unberührt. **Ein belegter Bauplatz belegt
  keine Arbeit**, und (c) kann eine ganze Fehldiagnose tragen (0059, drei Fassungen lang).
- **Gegenprobe für beide ist immer die Zieldatei**, `git log -- <zieldatei>`. **Der Betreff
  lügt regelmäßig:** „test-pruefer: 0044" enthielt den Befund zu **0048**, „testentwickler:
  0061" zwei Dateien zu **0052**. Immer hinschreiben, was ich gemessen habe.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs. Verlässlich: `grep`, `head`, `tail -n`, `ls`, `wc`,
  `git add`/`log`/`mv`/`show`, `baulauf.py --trocken`. **Ich committe nicht selbst.**
- **Nie aus `~/fabrik` heraus `cd`en.** Die Arbeitsrichtung überlebt den Aufruf; nach einem
  `cd` scheitert jedes `Edit(ventures/**)` mit „don't ask mode" statt mit einem Pfadfehler.
  **2026-09-04 trotz dieses Eintrags wieder passiert:** Der `cd` stand in der *Erkundung*,
  der Schaden fiel Blöcke später beim ersten `Edit`. Die Regel greift zu spät, wenn ich sie
  erst beim Schreiben lese — **also `cd /home/adria/fabrik &&` in jeden Bash-Aufruf.**
- **`Grep` über `aufgaben/` mit `abnahme:` im Muster sprengt den Puffer** (48 kB). Nur
  `^status:` oder `^haengt_an:` greppen, nie beides mit den langen Feldern zusammen.
- **Mehrere `Edit` je Aufrufblock werden abgelehnt.** Einer je Block. `status:` steht in
  manchen Paketen zweimal — **mit der `rolle:`-Zeile davor ankern**, nie `replace_all`.
- **Die Bündelung des Baulaufs verschiebt fremde Arbeit um einen Commit.** Eine Datei
  **ausserhalb** der `dateien`-Liste im Commit ist deshalb kein Regelbruch, solange ihr
  Inhalt einen fremden Paketnamen trägt.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste in die Abnahme. **Die Datei aufnehmen, die der Bauagent anfassen *musste***,
  und ins Paket schreiben, welche er **nicht** mehr darf und wer sie jetzt hält.
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot.
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage — auch meine
  eigene aus der Vorfassung.** „Vier Pakete auf `technik.md`" waren **sechs**: Die Vorfassung
  hatte mit `grep -l` über den *Text* gezählt. **Wer Dateien zählt, greppt `^dateien:`.**
- **Der Kollisionsschutz sieht `gebaut` nicht** (`baulauf.py:270-281`). **Prüffrage bei
  jedem startbereiten Paket: Hält ein Paket auf `gebaut` eine seiner Dateien?**
- **`dateien` eines *abgenommenen* Pakets nicht nachziehen** — die Liste ist der Maßstab,
  gegen den der nächste Lauf Kollisionen prüft. Beim Rücklauf gilt das Gegenteil.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich sind sie
  fast immer richtig; der Fehler steckt im Kriterium oder in der Liste.
- **Zwei Vorschläge können dieselbe Arbeit sein, von zwei Gewerken gefunden** (0070/0044:
  dieselben drei Schlüssel, dieselbe Datei). **Vor dem Annehmen: Hält ein offenes Paket diese
  Datei schon — und tut es dort dasselbe?** Dann zusammenfassen.
- **Ein Vorschlag mit zwei Dateien kann zwei Rollen sein.** Der Schnitt entlang der Gewerke
  ist dann der richtige, kein Zugeständnis an die Mechanik.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein Deadlock**
  — besonders wenn ich eine Bedingung *dorthin* verlege. Dann `haengt_an` streichen und
  begründen.
- **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext.** Nebenbefunde bei
  `geprueft` sind kein Rücklauf; sie bekommen ein eigenes Paket — **oder ausdrücklich
  keines**, wenn sie eine Entwurfsfrage sind. Dann in den Rückstand, nicht ignorieren.
- **Doppelte Kennungen (parallele Läufe):** `git mv`, `id` mitändern, vorher `grep` auf
  `haengt_an`/`befunde/`/`ops/plan.md`. **Kennung bleibt, voller Name weicht.**
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge.** Zwei Greps: Rolle in
  `BAUROLLEN`/`PRUEFROLLEN` (`baulauf.py:59`)? Rollendatei mit `Edit()` auf das Ziel?
- **Verlangt ein Kriterium einen Lauf: staffeln** (`$TMPDIR`, sonst `befunde/`, sonst
  ausgewiesene Nichtmessung). **Eingriff in eine fremde Datei: Nachweis auf eine Kopie unter
  `befunde/<messung>/`** — `baulauf.py` übersetzt jedes Verzeichnis außer `befunde/`.

## Offene Fährten

- **Erledigt 2026-09-04:** Die Korrelation „zwei Pakete einer Rolle, höchstens eines
  liefert" ist tot (0027 und 0048 lieferten beide). **Lehre: ein vorab benannter Prüffall
  schlägt jede nachträgliche Deutung.**
- **2026-09-04, nächster Auslöser, angekündigt und damit fällig:** Bedingung 4 von 0026
  verlangt die Aussage, ob T47/T48/T50 unberührt bleiben. Ändern sie sich, ziehe ich Umfang
  und Abnahme von **0002** nach (nennt heute fest 4.200.000.000.000 Cent aus T47).
- **Ein Paket, das eine neue `CMakeLists.txt` anlegt, steht ab dem ersten Teilstand im
  Übersetzungsbericht.** **Zuschnittsfrage: Kommt es in einem Lauf bis zum laufenden Test?**
- **Ein Abnahmekriterium kann dem Auftragstext widersprechen** — in beide Richtungen prüfen.
- **Belegstellen mit Zeilennummern:** Heilung ist Abschnittsüberschrift plus Zitat, **nie
  die nachgezogene Nummer**. Der Riegel aus 0059 misst das seit 2026-09-04 automatisch.
- **Prüffrage bei jedem Kriterium: Kann die Rolle den Nachweis führen?** Fähigkeit ist
  rollen-, nicht umgebungsgebunden.
- **Ein Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis.**
