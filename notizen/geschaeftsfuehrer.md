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

- **Der Trockenlauf sagt den Engpass, nicht der Rückstand** (2026-09-03, 11. Lauf).
  `python3 agents/baulauf.py <v> --trocken` nennt die Platzbelegung je Phase. „4 von 4
  Prüfplätzen, 1 von 4 Bauplätzen" war der ganze Befund des Laufs — sichtbar in einem
  Aufruf, unsichtbar in 43 Paketdateien. **Immer zuerst, direkt nach den Statuszahlen.**
- **`einrichtung/bauleistung.py` (neu, Betreiber 2026-09-02) ist meine Geldquelle.** Läuft
  in Sekunden, nennt $ je Rolle, die Aufteilung Bau/Prüfung/Steuerung und die
  Wiederholungsquote der Urteile. Damit wird aus „das Datengewerk läuft leer" ein Satz mit
  228,90 $ darin. **Jeden Lauf aufrufen** — eine Empfehlung mit Preis wird gelesen.
- **`GLEICHZEITIG = 4` (`agents/baulauf.py:80`) gilt für Bau *und* Prüfung.** Die Zahl
  erklärt jede Stauung: Sind mehr Pakete `gebaut` als 4, wartet der Rest, und alles, was an
  ihnen hängt, wartet mit. `haengt_an` gegen `gebaut`-Status prüfen, nicht nur gegen
  `fertig` — ein Paket ist auch dann blockiert, wenn seine Abhängigkeit nur ungeprüft ist.

## Was nicht funktioniert

- **Verwehrte Werkzeuge, nicht erneut versuchen:** `git commit` in jeder Form (`git add`
  geht), `sed`, `cat` über mehrere Dateien, `python3 -c`, mehrzeilige Bash-Schleifen,
  `find ... -exec`, `mv`/`cp`/`Write` nach `notizen/archiv/`. Erlaubt: `Read`, `grep`,
  `ls -la`, `head`, `wc`, `find` (ohne `-exec`), einzeilige `git`-Aufrufe,
  `python3 agents/*.py`. Für Codestellen `Read` mit `offset`/`limit` statt `sed`.
- **Ein Stichwort zu zählen misst nie eine Vorgabe.** Ich habe sechs Pläne lang
  „`technik.md` sagt Rust" mit `grep -c -i rust` belegt. Am 2026-09-03 stand die Zahl bei
  15 statt 10 — und die Divergenz war *behoben*: Der Architekt hatte C++ eingetragen und
  Rust als verworfene Alternative **häufiger** erwähnt als vorher. Die Zahl stieg, während
  der Befund fiel. **Bei jeder Divergenzbehauptung die entscheidende Stelle lesen**
  (hier: den Satz nach „## 1. Stack"), nie nur zählen. `grep -c` zählt ausserdem Zeilen,
  nicht Treffer, und nimmt Prosa mit.
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

10. Lauf (2026-09-02): Review-Engpass, 0019 (29 Byte → 30.835), „No tests were found!!!",
Architektendiagnose. 11. Lauf (2026-09-03), alle drei nach 5–6 Plänen:
- **`schritt` hat ein Paket und ist gebaut** — 0033, 26.697 Byte, `schritt_probe` grün.
- **Der Architekt ist kein Engpass mehr** — 0011 am 2026-09-02 20:05 geliefert.
- **Die Rust/C++-Divergenz ist weg** — `technik.md` T1 schreibt C++20 vor.

**Die Lehre daraus:** Nichts davon fiel an meiner Wiederholung. Es fiel an einer Teilung
des Pakets (0019), einer Rollendatei (Architekt) und einem neuen Paket, das der
Projektmanager nach *einer* Meldung anlegte (`schritt`). *Wenn ein Paket dreimal nicht
liefert, ist die Größe die Ursache, nicht die Reihenfolge* — und der Adressat einer
Meldung ist der Projektmanager oder der Betreiber, nie mein eigener Plan. **Einmal sagen,
an die richtige Hand, wirkt; fünfmal sagen kostet nur meinen Platz im Plan.**

## Offene Faehrten

- **2026-09-03 (11. Lauf), Engpass: die Prüfung.** 7 `gebaut` vor 4 Plätzen; 6 von 7
  offenen und 5 von 6 vorgeschlagenen Paketen hängen an einem ungeprüften. **Nächster Lauf
  zuerst:** Trockenlauf, Platzbelegung Bau gegen Prüfung. Steht sie wieder bei 1:4, ist
  meine Empfehlung (getrennte, höhere Prüfzahl) fällig — dann mit der Wiederholungsquote
  aus `bauleistung.py` als Beleg, sie war 25 %.
- **Die Rohdaten, zum zweiten Mal vorgelegt** (Empfehlung B: Betreiber lädt vier Quellen
  nach `…/daten/roh/`). Neu und der Grund, warum sie diesmal trägt: 228,90 $ = 38 % der
  Bauphase für Datenarbeit ohne eine einzige Datenzeile. **Prüfen:** `ls …/daten/roh/`.
  **Ein drittes Mal lege ich sie nicht vor** — dann ist sie beantwortet, indem sie
  liegenbleibt, und das gehört als Befund in den Plan, nicht als Frage.
- **Doppelte Paketnummern: 0039 und 0040 je zweimal** (2026-09-03). Vier Gewerke haben
  gleichzeitig vorgeschlagen. `haengt_an` trägt (voller Name), meine Vorrangliste nicht.
  An den Projektmanager gemeldet. **Prüfen, ob er umnummeriert.**
- **Die Fehlerklasse, vom Betreiber benannt (`953bbf5`):** eine Regel oder Rolle an einer
  Stelle, die der Ablauf nicht erreicht — es fällt erst auf, wenn etwas **nicht**
  geschieht. Siebter Fall (2026-09-03): Vorschlag 0041 ändert `agents/baulauf.py`, und
  **kein Gewerk darf `agents/` schreiben** — ein Paket ohne zuständige Hand, das jeden
  Trockenlauf verstopft. Neue Untergattung: nicht nur „Kasten ohne Paket", sondern „Paket
  ohne Rolle". **Bei jedem Vorschlag prüfen: gibt es eine Rolle, die diese Datei darf?**
- **Eine Empfehlung zurückzunehmen ist billiger, als sie zum vierten Mal zu wiederholen.**
  `ops/baulauf.log` war richtig, aber der Betreiber hat die Frage von Hand aus dem
  Rückgabetext des Architekten beantwortet. Eine Empfehlung, deren Zweck anders erfüllt
  wurde, gehört herabgestuft — sonst verdrängt sie die neue Frage.
- **Ein Prüfer committet den Befund eines anderen mit** (Lauf 269 trug den 0015-Befund).
  Der Runner committet den ganzen Schreibpfad. Nie vom Commit auf den Autor schließen —
  die Datei nennt `pruefer:` im Frontmatter.
- **Ein ganzer Baudurchgang stand in keinem Betriebslog** (2026-09-02 19:33–21:23, elf
  Läufe). `ops/nachtlauf.log` endet 08:17 — die Abendläufe kamen offenbar direkt aus
  `baulauf.py`, und nur `nachtlauf.py` schreibt das Log. **Für den Stand reicht `git log`,
  für einen Störungsfall nicht.** Meine herabgestufte `ops/baulauf.log`-Empfehlung hat
  damit einen zweiten Beleg — aber erst wieder vorlegen, wenn sie etwas *kostet*.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand
  zählen, solange es nichts blockiert. Die 170-gegen-121-Lücke ebenso: erst wieder
  aufgreifen, wenn der Kern rechnet.
- **`werte` (78 Byte) ist der letzte leere Kernkasten**, entblockt über 0011 → 0026 →
  0002. Die eine Zahl steht bei 8 von 9. Fällt sie nicht bis zum nächsten Lauf, ist die
  Kette selbst der Befund, nicht `werte`.
- **`.tmp`-Dateien im Repo: 18** (`git ls-files "*.tmp" | wc -l`, vorher 14). Ab etwa 30
  melden.
