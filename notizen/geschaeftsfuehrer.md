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
  8./9. Lauf — bestes Werkzeug bisher). `git log --since=... --format="%ad | %s | %b"`
  zeigt je Commit „Lauf N". **Lückenlose Folge = jeder aufgerufene Agent hat committet;
  eine Lücke = ein Lauf ohne Ergebnis.** Damit ist beweisbar, wer *nicht* aufgerufen
  wurde. Lauf 9 war 262–270 mit genau einer Lücke (267).
- **Der Commit-*Betreff* ist runner-erzeugt** (`lauf.py:328`,
  `f"{rolle}: {gegenstand} ({n} Dateien)"`). Er beweist den **Aufruf** — anders als der
  Commit-*Inhalt*, der nur den Schreibpfad spiegelt. Beides sauber trennen: Betreff sagt
  „wurde beauftragt", `wc -c` auf `dateien` sagt „hat geliefert".
- **Trockenlaufliste minus Ist-Bauliste nennt die ausgefallene Rolle.** Dreimal in Folge
  gehen die Läufe exakt auf, wenn man 0011 (architekt) und 0021 (spielentwerfer)
  streicht und von unten auffüllt. Drei unabhängige Läufe genügen für den Bericht, auch
  ohne die Codestelle.
- **Den Trockenlauf selbst aufrufen, nicht den Bericht des Projektmanagers abschreiben.**
  `python3 agents/baulauf.py <venture> --trocken` ist erlaubt und kostet nichts. Er sagt,
  was der **nächste** Lauf vorhat — die schärfste Vorwarnung, die ich habe (Lauf 10: nur
  noch drei Baupakete, zwei davon tot).
- **Die Fragen des Rückstands auf ihre Ursache zurückrechnen, statt sie zu referieren.**
  Und: **den Projektmanager gegenlesen** — er korrigiert mich, ich ihn.
- **Ein Vertagungspreis trägt nur mit Paket und Zeitpunkt.** `haengt_an` rückwärts lesen:
  0027←0023, 0028←0015, 0026←0025+0011, 0002←0026, 0010←0002. So wird aus „der Review
  stockt" eine Kette mit Namen.
- **Der Übersetzungsbericht ist die billigste Grundwahrheit im ganzen Vorhaben**
  (2026-09-02, 10. Lauf). `befunde/uebersetzung-<datum>.md` ist runner-erzeugt und nennt
  Ziele und Tests **namentlich** mit `Passed`. `tail -35` darauf hat mir die wichtigste
  Änderung des Laufs gegeben (erster Prüfstandstest). **Zuerst lesen, nicht zuletzt** —
  vor `rueckstand.md`, der immer den Stand *vor* der Bauphase beschreibt.
- **Die `dateien:`-Felder gegen die Kästen des Zielbilds halten — das nennt, was nie
  beauftragt wurde.** `grep "^dateien:" aufgaben/*.md | grep -c <kasten>` → 0 heisst: kein
  Paket, keine Blockade, sondern eine Lücke im Auftrag. So fand ich, dass `schritt` in 32
  Paketen nicht vorkommt. **Das ist meine Sonde für die Fehlerklasse des Betreibers**, sie
  kostet einen Aufruf — und ich habe fünf Pläne lang „7 von 9" gemeldet, ohne zu fragen,
  wer die fehlenden zwei bauen soll. Bei jeder wiederkehrenden Zahl künftig zuerst.
- **Vor jedem „unverändert seit N Plänen" die Uhr des Betreibers prüfen:** `git log` nach
  Commits *ohne* Rollenpräfix filtern. Am 2026-09-02 lagen drei meiner Pläne (07:32,
  08:25, 09:25) hinter seinem letzten Commit (06:39). **Eine Empfehlung, die er noch
  nicht gesehen hat, darf ich nicht als abgelehnt behandeln** — das schreibe ich künftig
  ausdrücklich in den Plan hinein.

## Was nicht funktioniert

- **Verwehrte Werkzeuge, nicht erneut versuchen:** `git commit` in jeder Form (`git add`
  geht), `sed`, `cat` über mehrere Dateien, `python3 -c`, mehrzeilige Bash-Schleifen,
  `find ... -exec`, `mv`/`cp`/`Write` nach `notizen/archiv/`. Erlaubt: `Read`, `grep`,
  `ls -la`, `head`, `wc`, `find` (ohne `-exec`), einzeilige `git`-Aufrufe,
  `python3 agents/*.py`. Für Codestellen `Read` mit `offset`/`limit` statt `sed`.
- **`grep -c <wort>` zählt Zeilen, nicht Treffer, und nimmt Prosa mit.** Immer den ganzen
  Satz greppen (`"status: gebaut"`), nie das Stichwort. (Der Projektmanager meldete
  8 Rust-„Treffer" in `technik.md`, `grep -c` gibt 6 Zeilen — beides richtig, aber nicht
  dasselbe. Im Plan sage ich, was ich gemessen habe: Zeilen.)
- **Statische Analyse von `baulauf.py` erklärt den Ausfall von 0011/0021 nicht.** Vier
  Läufe daran verbraucht. Nachgewiesen ausgeschlossen: `pakete()` filtert keine Rollen;
  `startbereit()` erreicht 0011 mit leerem `belegt` (0010 fällt vorher an `_haengt`
  raus); `rueckläufe()` ist 0 (keine `pruefung-0011-*`/`pruefung-0021-*`); der
  Projektmanager fasst beide Paketdateien nicht an; `phase()` führt jeden Auftrag aus.
  **Nicht noch einmal von außen suchen — das beantwortet nur `ops/baulauf.log`.**
- **`einrichtung/rollen-pruefen.py` meldet „keine Befunde", während zwei Rollen nicht
  starten.** Es prüft Rollendateien, nicht Einplanung. Kein Ersatz für die Lückenprobe.
- **Veraltet und unbrauchbar für den Stand eines Vorhabens:** `ops/portfolio.md`,
  `ops/kontingent.md`, `ops/auslastung.md` — alle vom 2026-08-30. Nicht dort anfangen.
- **Die 270-kB-Spezifikation wird nie ganz gelesen.** Getragen hat: Arbeitspakete,
  Befund-Frontmatter, `rueckstand.md`, `agents/*.py`. Die Wahrheit über den Zustand steht
  in den Skripten, nicht in den Dokumenten.

## Erledigt — nicht erneut aufgreifen

Alle vier am 2026-09-02 im 10. Lauf gefallen, nachdem sie 3–5 Pläne lang gestanden hatten:
Review-Engpass (3 von 4 Urteilen statt 1 von 4), 0019 (29 Byte → 30.835), „No tests were
found!!!" (`vorrat_probe … Passed`), Architektendiagnose (Betreiber, 19:13).
**Die Lehre daraus:** Was ich fünfmal gemeldet habe, fiel nicht an meiner Wiederholung,
sondern an einer Teilung des Pakets (0019) und an einer Rollendatei (Architekt). *Wenn ein
Paket dreimal nicht liefert, ist die Größe die Ursache, nicht die Reihenfolge* — und der
Adressat einer Meldung ist der Projektmanager oder der Betreiber, nie mein eigener Plan.

## Offene Faehrten

- **2026-09-02 (10. Lauf), Engpass: der Architekt.** Eine Rolle, eine Datei, vier Fragen
  in `technik.md`, das genau einen Bauplatz trägt — 0011, 0026, Wohnort der
  Zustandsausgabe, Präfix `gebiet.`/`land.`. Solange sie steht, hat `kernbauer` kein
  startbereites Paket. **Nächster Lauf zuerst:** `git log -- specs/*/technik.md | head -3`.
  Bewegt sie sich, hat die Rollenänderung von 19:13 getragen; bewegt sie sich nicht, ist
  es der dritte leere Architektenlauf und ein eigener Befund.
- **`schritt` hat kein Arbeitspaket** — 32 Pakete, `grep -c schritt` auf die `dateien:`-
  Zeilen gibt 0. Im Vorrang an den Projektmanager gemeldet. **Prüfen, ob er es anlegt;
  wenn nicht, im nächsten Plan als offene Bitte wiederholen, aber nur einmal** (siehe
  oben).
- **Die Rohdaten sind meine erste eigene Entscheidungsfrage, nicht geerbt** (Plan vom
  10. Lauf, Empfehlung B: Betreiber lädt vier Quellen von Hand). `daten/` hat null
  Datenzeilen nach zehn Bauläufen. **Prüfen:** `ls .../daten/roh/`.
- **Die Fehlerklasse, vom Betreiber benannt (`953bbf5`):** eine Regel oder Rolle an einer
  Stelle, die der Ablauf nicht erreicht — es fällt erst auf, wenn etwas **nicht**
  geschieht. Sechster Fall: `schritt` im Zielbild ohne Paket. Meine Rolle ist die einzige,
  die ausbleibende Arbeit sehen kann. **Aktiv danach suchen.**
- **Eine Empfehlung zurückzunehmen ist billiger, als sie zum vierten Mal zu wiederholen.**
  `ops/baulauf.log` war richtig, aber der Betreiber hat die Frage von Hand aus dem
  Rückgabetext des Architekten beantwortet. Eine Empfehlung, deren Zweck anders erfüllt
  wurde, gehört herabgestuft — sonst verdrängt sie die neue Frage.
- **Ein Prüfer committet den Befund eines anderen mit** (Lauf 269 trug den 0015-Befund).
  Der Runner committet den ganzen Schreibpfad. Nie vom Commit auf den Autor schließen —
  die Datei nennt `pruefer:` im Frontmatter.
- **`specs/technik.md`: 10 Zeilen Rust/cargo/rustc, 0 Zeilen C++**, unverändert seit
  2026-09-01 09:17. Die Stelle, an der Gebautes und Vorgabe auseinanderlaufen — meine
  eigentliche Frage. Jeden Lauf neu messen, sie ist billig. (Der Wert stieg von 6 auf 10,
  weil ich das Suchmuster erweitert habe, nicht der Text — Messmuster im Plan nennen.)
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand
  zählen, solange es nichts blockiert. Die 170-gegen-121-Lücke ebenso: erst wieder
  aufgreifen, wenn der Kern rechnet.
- **`.tmp`-Dateien im Repo: 18** (`git ls-files "*.tmp" | wc -l`, vorher 14). Ab etwa 30
  melden.
