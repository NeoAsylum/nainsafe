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

## Offene Faehrten

- **2026-09-02 (9. Lauf), Engpass: Der Review liefert ein Urteil je vier Plätze.** Vier
  Pakete stehen auf `gebaut` ganz ohne Befunddatei (0020, 0023, 0024, 0025).
  **Der Mechanismus:** `rueckläufe()` (`baulauf.py:236`) zählt nur `urteil: zurueck` —
  ein Prüfer, der nichts schreibt, zählt nicht. 0009 hat fünf Reviewplätze verbraucht,
  steht weiter bei 2 von 3 und hält als Erster der Liste `[:4]` Platz 1 auf Dauer.
  **Nächster Lauf zuerst:** `grep -H "^urteil:" ventures/*/befunde/*.md` gegen die Liste
  der `gebaut`-Pakete halten — die Differenz ist die Zahl.
- **Empfehlung B steht seit drei Plänen** (Runner setzt `gebaut` + schreibt
  `ops/baulauf.log`). Sie deckt jetzt beide Engpässe. **Prüfen:** `ls ops/*.log` und ob
  `baulauf.py` einen `open(... "baulauf.log")` enthält. Solange nein: unverändert
  wiederholen und dazusagen, zum wievielten Mal.
- **Die Fehlerklasse, vom Betreiber benannt (`953bbf5`):** eine Regel oder Rolle an einer
  Stelle, die der Ablauf nicht erreicht — es fällt erst auf, wenn etwas **nicht**
  geschieht. Sechster Fall: die Konvergenzbremse greift nicht beim stummen Prüfer.
  Meine Rolle ist die einzige, die ausbleibende Arbeit sehen kann. **Aktiv danach
  suchen.**
- **Ein Prüfer committet den Befund eines anderen mit** (Lauf 269 trug den 0015-Befund).
  Der Runner committet den ganzen Schreibpfad. Deshalb nie vom Commit auf den Autor des
  Befunds schließen — die Datei selbst nennt `pruefer:` im Frontmatter.
- **0019: vierter Bauversuch, null eigene Bytes.** 14 und 15 Byte, unverändert seit
  07:54, obwohl der Projektmanager die Dateireihenfolge eigens vorgeschrieben hat. Ab
  dem fünften vergeblichen Versuch ist das ein eigener Befund, kein Nebensatz mehr.
- **`pruefstand/bau` meldet „No tests were found!!!" und `ctest` gibt Code 0.** Der
  Übersetzungsbefund ist die Grundwahrheit der Fabrik und kann in diesem Bausatz nie
  durchfallen. Blockiert nichts, entwertet aber ein Urteil — melden, wenn 0019 liefert.
- **`specs/technik.md` unverändert seit 2026-09-01 09:17, 6 Zeilen Rust, 0 Zeilen C++.**
  Das ist die Stelle, an der Gebautes und Vorgabe auseinanderlaufen — meine eigentliche
  Frage. Jeden Lauf neu messen, sie ist billig.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand
  zählen, solange es nichts blockiert. Die 170-gegen-121-Lücke ebenso: erst wieder
  aufgreifen, wenn der Kern rechnet.
- **`.tmp`-Dateien im Repo: 14** (`git ls-files "*.tmp" | wc -l`). Ab etwa 30 melden.
