# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende. **Höchstens 12.000 Zeichen** (`wc -c`).

**Neu begonnen am 2026-09-02 (6. Lauf).** Alte Fassung: `git show 9cb86d9:notizen/geschaeftsfuehrer.md`.
Das vorgeschriebene Verschieben nach `notizen/archiv/` kann meine Rolle nicht ausführen
(`mv`, `cp`, `Write` dorthin alle verwehrt) — **nicht wieder versuchen.**

---

## Was funktioniert

- **Den Trockenlauf selbst aufrufen, immer zuerst.**
  `python3 agents/baulauf.py <v> --trocken` kostet nichts und nennt die Platzbelegung je
  Phase. Er sagt, was der *nächste* Lauf vorhat — die schärfste Vorwarnung, die ich habe.
- **Die Review-Liste des Trockenlaufs gegen die `gebaut`-Pakete halten. Die Differenz ist
  das ausgehungerte Paket** (2026-09-03, 12. Lauf — bestes Werkzeug bisher).
  `reviewbereit()` (`baulauf.py:264`) sortiert nach Zahl der Rückläufe, Unbeprüfte zuerst,
  und schneidet bei 4 ab. **Ein Paket mit einem Rücklauf ist unsichtbar, solange vier
  frische davorstehen** — 0011 fünf Durchgänge, 0027 über 24 Stunden. Rückläufe zählen:
  `grep -c "urteil: zurueck" befunde/pruefung-<id>-*.md`.
- **`urteil: geprueft` gegen `status:` prüfen — die Lücke ist der billigste Engpass.**
  Nur der Projektmanager zieht `geprueft` → `fertig` (`rollen/projektmanager.md:95`). Vier
  Pakete mit bestandenem Urteil standen weiter auf `gebaut`, belegten alle vier Prüfplätze
  und liessen sich ein zweites Mal prüfen. **Ein Lauf behebt es.** Jeden Lauf messen.
- **Der Projektmanager kann sich über seine eigenen Pakete irren.** Er schrieb „0011 steht
  im Review"; der Trockenlauf nannte vier andere. Er sieht *in* die Pakete, ich sehe die
  *Schlange*. Deshalb: seinen Rückstand lesen, aber nie statt des Trockenlaufs.
- **`einrichtung/bauleistung.py` und `agents/kontingent.py` sind meine Geldquellen.**
  Ersteres $ je Rolle und Wiederholungsquote; letzteres seit 2026-09-03 (Betreiber, 18:53)
  **Fensterbeginn, Verbrauch und Spielraum der Abo-Woche**. Aus Spielraum ÷ Tagesgrenze
  (`lauf.py:TAGESGRENZE_USD`) wird ein **Datum**, an dem die Fabrik stillsteht — eine Zahl
  mit Kalendertag wird gelesen.
- **Die Lauf-Nummer im Commit-Body ist das fehlende Baulauf-Protokoll.**
  `git log --format="%ad | %s | %b"`: lückenlose Folge = jeder Agent hat committet, Lücke =
  Lauf ohne Ergebnis. Der Betreff ist runner-erzeugt (`lauf.py:328`) und beweist den
  **Aufruf**; `wc -c` auf `dateien` beweist die **Lieferung**. Sauber trennen.
- **Der Übersetzungsbericht ist die billigste Grundwahrheit** —
  `befunde/uebersetzung-<datum>.md`, runner-erzeugt, nennt Ziele und Tests namentlich.
  **Aber `manifeste:` mitlesen:** Am 2026-09-03 war das vierte Manifest ein unversioniertes
  `pruefstand/bau/.../CMakeLists.txt`, und die elf grünen Tests stammten daraus.
- **Die `dateien:`-Felder gegen die Kästen des Zielbilds halten — das nennt, was nie
  beauftragt wurde.** `grep "^dateien:" aufgaben/*.md | grep -c <kasten>` → 0 heisst Lücke
  im Auftrag, nicht Blockade. Bei jeder wiederkehrenden Zahl zuerst.
- **`haengt_an` rückwärts lesen macht aus „es stockt" eine Kette mit Namen** — und die Zahl
  der Nachfolger je gebautem Paket ist meine Vorrangreihenfolge.
- **Vor jedem „unverändert seit N Plänen" die Uhr des Betreibers prüfen:** `git log` nach
  Commits ohne Rollenpräfix. Eine Empfehlung, die er noch nicht gesehen hat, ist nicht
  abgelehnt — das gehört ausdrücklich in den Plan.

## Was nicht funktioniert

- **Verwehrte Werkzeuge, nicht erneut versuchen:** `git commit` (`git add` geht), `sed`,
  `awk`, `cat` über mehrere Dateien, `python3 -c`, mehrzeilige Bash-Schleifen,
  `find ... -exec`, `mv`/`cp`/`Write` nach `notizen/archiv/`, `git show <hash>`. Erlaubt:
  `Read`, `Grep`, `grep`, `ls -la`, `head`/`tail`, `wc`, `find` (ohne `-exec`), einzeilige
  `git log`-Aufrufe mit `--since`/`--until`, `python3 agents/*.py`. **`cd` wirkt über
  parallele Aufrufe hinweg** — in einer Runde immer absolute Pfade.
- **Ein Stichwort zu zählen misst nie eine Vorgabe.** Sechs Pläne lang „`technik.md` sagt
  Rust" mit `grep -c -i rust` belegt; am Ende stieg die Zahl, während der Befund fiel.
  **Bei jeder Divergenzbehauptung die entscheidende Stelle lesen**, nie nur zählen.
- **Statische Analyse von `baulauf.py` erklärt einen Rollenausfall nicht.** Vier Läufe
  daran verbraucht. Der Ausfall von 0011/0021 war am Ende keiner: Beide Rollen liefen am
  2026-09-03. **Erst messen, ob es noch gilt, dann suchen.**
- **`einrichtung/rollen-pruefen.py` meldet „keine Befunde", während Rollen nicht starten.**
  Es prüft Rollendateien, nicht Einplanung.
- **Veraltet für den Stand eines Vorhabens:** `ops/portfolio.md`, `ops/auslastung.md` (beide
  2026-08-30). Nicht dort anfangen. Die Wahrheit steht in den Skripten, nicht in der
  270-kB-Spezifikation.

## Erledigt — nicht erneut aufgreifen

10./11. Lauf: Review-Engpass als Kapazitätsfrage, 0019, Architektendiagnose,
Rust/C++-Divergenz, `schritt` ohne Paket. 12. Lauf (2026-09-03): doppelte Nummern 0039/0040
(PM hat auf 0042/0043 umnummeriert), `ops/baulauf.log` (Betreiber hat crontab versioniert
und `python3 -u` gesetzt), Wochenbremse (Betreiber, 18:51).

**Die Lehre:** Nichts davon fiel an meiner Wiederholung. Es fiel an einer Teilung des
Pakets, einer Rollendatei, einem neuen Paket. *Wenn ein Paket dreimal nicht liefert, ist
die Größe die Ursache, nicht die Reihenfolge* — und der Adressat einer Meldung ist der
Projektmanager oder der Betreiber, nie mein eigener Plan. **Einmal sagen, an die richtige
Hand, wirkt; fünfmal sagen kostet nur meinen Platz im Plan.**

## Offene Faehrten

- **Die Rohdaten sind geschlossen** (2026-09-03, 12. Lauf). Zweimal vorgelegt, nie
  beantwortet; ich habe das Ausbleiben als Antwort genommen und die Frage aus dem Plan
  entfernt — als Befund mit Preis (334,25 $, 35 % der Bauphase). **Nicht wieder als Frage
  stellen.** Prüfen, ob der leerlaufende Datenbauplatz nach 0057 eintritt: das ist der
  Beleg, ob die Rücknahme richtig war. Allgemein: *Eine Empfehlung zurückzunehmen ist
  billiger, als sie zum vierten Mal zu wiederholen.*
- **Nächster Lauf zuerst:** Trockenlauf, dann `urteil: geprueft` gegen `status:`. Stehen
  0040/0049/0053/0058 immer noch auf `gebaut`, ist nicht die Prüfkapazität das Problem,
  sondern dass der Projektmanager den Übergang nicht zieht — dann gehört es an den
  Betreiber, nicht noch einmal in meinen Vorrang.
- **Fehlerklasse des Betreibers** (eine Regel an einer Stelle, die der Ablauf nicht
  erreicht): 8. Fall — `architekt`, `spielentwerfer`, `testentwickler` fehlt „Setze
  `status: gebaut`" (`grep -c` = 0, bei `kernbauer`/`datenbauer` = 1). 9. Fall — **0041
  trägt jetzt `rolle: geschaeftsfuehrer`**, eine Rolle, die nicht in `BAUROLLEN` steht: das
  Paket wird nie eingeplant. Neue Untergattung zu „Paket ohne Rolle": *Paket mit einer
  Rolle, die der Runner nicht kennt.* **Bei jedem Vorschlag prüfen: steht die Rolle in
  `BAUROLLEN`, und darf sie diese Datei schreiben?**
- **Das Wochenkontingent hat ein Datum.** 951,4 von 1.600 $ am 2026-09-03 23:43, Fenster ab
  Montag 10:00. Bei 350 $/Tag Samstagfrüh leer. **Jeden Lauf neu rechnen** — die Zahl
  bindet härter als jeder Rückstand, und sie ist die einzige, die ein Wochenende kostet.
- **`werte` (78 Byte) ist der letzte leere Kernkasten**, entblockt über 0011 → 0026 → 0002.
  Die eine Zahl steht den dritten Plan bei 8 von 9. Fällt sie nicht, ist die Kette selbst
  der Befund, nicht `werte`.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand zählen,
  solange es nichts blockiert.
- **Ein Prüfer committet den Befund eines anderen mit.** Nie vom Commit auf den Autor
  schliessen — die Datei nennt `pruefer:` im Frontmatter.
- **`.tmp`-Dateien im Repo: 18** (`git ls-files "*.tmp" | wc -l`), unverändert. Ab etwa 30
  melden. Dazu `aufgaben/.kopf.tmp` und `.paket.tmp` — Schaden null, `baulauf.py:215` liest
  nur `*.md`.
