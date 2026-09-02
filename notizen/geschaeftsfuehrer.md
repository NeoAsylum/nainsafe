# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende. **Höchstens 12.000 Zeichen** (`wc -c`).

**Neu begonnen am 2026-09-02 (6. Lauf).** Alte Fassung: `git show 9cb86d9:notizen/geschaeftsfuehrer.md`.
Das vorgeschriebene Verschieben nach `notizen/archiv/` kann meine Rolle nicht ausführen
(`mv`, `cp`, `Write` dorthin alle verwehrt) — **nicht wieder versuchen.**

---

## Was funktioniert

- **Die Lauf-Nummer im Commit-Body ist das fehlende Baulauf-Protokoll** (2026-09-02,
  8. Lauf — bestes Werkzeug bisher). `git log --since=... --format="%ad | %s | %b"` zeigt
  je Commit „Lauf N" aus dem Journal. **Lückenlose Folge = jeder aufgerufene Agent hat
  committet; eine Lücke = ein Lauf ohne Ergebnis.** Damit ist beweisbar, wer *nicht*
  aufgerufen wurde — sonst sehen „nie geplant" und „gelaufen, nichts geliefert" gleich aus.
  Lauf 8 war 252–260 ohne Lücke, Lauf 7 hatte zwei Lücken (248, 249).
- **Trockenlaufliste minus tatsächliche Bauliste, über zwei Läufe gerechnet, nennt die
  ausgefallene Rolle.** Streiche Kandidaten aus der Vorhersage, bis der Rest exakt der
  Ist-Menge entspricht. 0011 und 0021 raus → beide Läufe gehen exakt auf. Zwei
  unabhängige Läufe sind genug für einen Bericht, auch ohne die Codestelle zu kennen.
- **Wenn zwei Pfade dasselbe berechnen und verschieden antworten, ist die Differenz die
  ganze Suchmenge.** Trockenlauf `baulauf.py:267` gegen echten Lauf `:307–308` — genau ein
  Filter unterschiedlich. Das schließt die Frage ein, auch wenn sie hier offenblieb.
- **Die Fragen des Rückstands auf ihre Ursache zurückrechnen, statt sie zu referieren.**
  Beste Form der Engpassfrage. Und: **den Projektmanager gegenlesen** — er hat meine
  `gebaut`-Zählung selbständig korrigiert. Widerspricht er, hat oft er recht.
- **Ein Vertagungspreis trägt nur mit Paket und Zeitpunkt.** „C kostet etwas" ist folgenlos,
  „0011 → 0026 → 0002 → 0010 steht still" ist eine Frist. `haengt_an` rückwärts lesen.
- **`wc -c` gegen `VORLAGE.md` (1.242) trennt „einmal ausgefallen" von „nie gelaufen"** in
  einem Aufruf. `test-pruefer` 1.252 und `testentwickler` 1.256 haben nie geschrieben.
  Ergänzend `grep -c "<datum>" notizen/*.md` für den einzelnen Tag.
- **Vor jedem „unverändert seit N Plänen" die Uhr des Betreibers prüfen:** `git log` nach
  Commits *ohne* Rollenpräfix filtern. Fünf meiner Pläne entstanden in einer Nacht.
  Seine Commit-Botschaften sind zudem die einzige aktuelle Kostenquelle.
- **Einen Ausweg, den ich als Option anbiete, einmal wirklich aufmachen.** Eine Option,
  die ich nicht nachgesehen habe, ist eine Vermutung im Entscheidungstext.

## Was nicht funktioniert

- **Verwehrte Werkzeuge, nicht erneut versuchen:** `git commit` in jeder Form (`git add`
  geht), `sed`, `cat` über mehrere Dateien, `python3 -c`, mehrzeilige Bash-Schleifen,
  `mv`/`cp`/`Write` nach `notizen/archiv/`. Erlaubt: `Read`, `grep`, `ls`, `head`, `tail`,
  `wc`, `find`, einzeilige `git`-Aufrufe, `python3 agents/*.py`. `state.db` ist für mich
  nicht lesbar — aber die Journalnummern stehen in den Commit-Bodies (siehe oben).
  Für Codestellen `Read` mit `offset`/`limit` statt `sed`.
- **`grep -c <wort>` zählt Prosatreffer mit.** So habe ich im 7. Lauf „nur zwei Rollen
  setzen `gebaut`" berichtet — es waren vier; in `architekt.md`/`spielentwerfer.md` kommt
  das Wort nur beiläufig vor. **Immer den ganzen Satz greppen** (`"status: gebaut"`),
  nie das Stichwort. Eine falsche Zahl im Engpasssatz kostet den Bericht.
- **`einrichtung/rollen-pruefen.py` meldet „keine Befunde", während zwei Rollen nicht
  starten.** Es prüft Rollendateien, nicht Einplanung. Kein Ersatz für die Lückenprobe.
- **Ein Commit unter dem Paketnamen beweist nichts.** Der Runner committet den ganzen
  Schreibpfad, also nimmt der erste fertige Lauf die Dateien der parallelen mit — der
  0019-Commit (Lauf 254) enthielt *keine* der vier eigenen Dateien. **Und `ls` genügt
  nicht:** 0019s Dateien existieren, sind aber 14 und 15 Byte. Immer `wc -c` auf das Feld
  `dateien` des Pakets.
- **`baulauf.py --trocken` sagt nicht, was der Lauf tut** — zweimal in Folge falsch.
  Als *eine* Quelle behandeln, nie als die Messung. Den fehlenden `ops/baulauf.log` jedes
  Mal miterwähnen, bis er da ist.
- **Veraltet und unbrauchbar für den Stand eines Vorhabens:** `ops/portfolio.md`,
  `ops/kontingent.md`, `ops/auslastung.md` — alle vom 2026-08-30. Nicht dort anfangen.
- **Widerlegt, nicht wieder aufwärmen:** „Eine Empfehlung, die um Aufmerksamkeit
  konkurriert, wird vertagt." Es lag an der Uhr, nicht an der Darstellung.
- **Die 270-kB-Spezifikation wird nie ganz gelesen.** Getragen hat: Arbeitspakete,
  Befund-Frontmatter, `rueckstand.md`, `agents/*.py`. Die Wahrheit über den Zustand steht
  in den Skripten, nicht in den Dokumenten.

## Offene Faehrten

- **2026-09-02 (8. Lauf), Engpass: Architekt (0011) und Spielentwerfer (0021) werden nicht
  aufgerufen.** Über Lücken bewiesen, Mechanismus unbekannt; `rueckläufe()` scheidet aus
  (`befunde/` hat keine `pruefung-0011-*`/`pruefung-0021-*`). Empfehlung war **B**:
  `gebaut` im Runner setzen **plus** `ops/baulauf.log`. **Nächster Lauf zuerst:**
  `ls ops/*.log` und `git log --format="%s|%b"` über den letzten Baulauf — startet der
  Architekt jetzt? Ist `specs/technik.md` nach dem 2026-09-01 09:17 angefasst?
- **Die Fehlerklasse, vom Betreiber benannt (`953bbf5`):** eine Regel oder Rolle an einer
  Stelle, die der Ablauf nicht erreicht — und es fällt erst auf, wenn etwas **nicht**
  geschieht. Fünfter Fall heute. Meine Rolle ist die einzige, die ausbleibende Arbeit
  sehen kann. **Danach aktiv suchen, nicht darauf warten** — die Lückenprobe ist das
  Werkzeug dafür.
- **Die Fährte „leerer Platz" hat sich verschoben.** Läufe 4–7: je 1–2 von 4 Plätzen ohne
  Commit. **Lauf 8: null.** Die Frage ist jetzt nicht mehr die Zahl, sondern der Inhalt —
  0019 hat committet und liefert seit drei Läufen 29 Byte. Nächste Messung: Anteil der
  Bauplätze, deren `dateien` sich wirklich geändert haben.
- **0009 und 0015 stehen beide bei zwei von drei Rückläufen** (`baulauf.py:295`). Beim
  dritten fallen sie aus dem Betrieb. 0009 hat drei Reviewplätze ohne Urteilsdatei
  verbraucht. Wenn eins von beiden festfährt: „Abnahmekriterien sind der zweite Engpass"
  ist dann belegt, nicht vermutet.
- **`pruefstand/bau` meldet „No tests were found!!!" und `ctest` gibt Code 0.** Der
  Übersetzungsbefund ist die Grundwahrheit der Fabrik und kann in diesem Bausatz nie
  durchfallen. Blockiert nichts, entwertet aber ein Urteil — melden, wenn 0019 je liefert.
- **0024/0025 sind baubar und kommen nie dran**, weil `startbereit(...)[:4]` nach
  Dateinamen sortiert und 0019/0020 zwei Plätze dauerhaft halten. Der Projektmanager hat
  einen Reihum-Vorschlag; er hilft erst nach dem Engpass. Nicht doppelt melden.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache** — das Paket sagt es selbst.
  Nicht als Rückstand zählen, solange es nichts blockiert.
- **Die 170-gegen-121-Lücke** blockiert nichts. Erst wieder aufgreifen, wenn der Kern rechnet.
- **`.tmp`-Dateien liegen committet im Repo** (`git ls-files "*.tmp"`); die Bauagenten
  behelfen sich damit und der Runner committet den ganzen Schreibpfad. Ab etwa 30 melden.
