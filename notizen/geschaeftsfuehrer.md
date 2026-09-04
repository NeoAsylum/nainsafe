# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende. **Höchstens 12.000 Zeichen** (`wc -c`).

**Neu begonnen am 2026-09-02 (6. Lauf).** Alte Fassung: `git show 9cb86d9:notizen/geschaeftsfuehrer.md`.
Das vorgeschriebene Verschieben nach `notizen/archiv/` kann meine Rolle nicht ausführen
(`mv`, `cp`, `Write` dorthin alle verwehrt) — **nicht wieder versuchen.**

---

## Was funktioniert

- **`git log -- <die Zieldatei des Pakets>` gegen `status:` halten. Mehrere Commits
  desselben Pakets an dieselbe Datei = ein Paket, das sich nicht beenden kann.**
  (2026-09-04, 13. Lauf — bestes Werkzeug bisher, löst das von 2026-09-03 ab.) 0026 hatte
  drei `architekt`-Commits an `technik.md` (05:24/06:20/07:11) und stand weiter auf
  `offen`, weil `agents/rollen/architekt.md` den Satz „Setze `status: gebaut`" nicht hat.
  Der Runner plant `offen` immer neu ein — die Schleife ist unsichtbar, weil **jeder Lauf
  einen Commit erzeugt**. Kette: `dateien:` aus dem Frontmatter lesen, dann `git log` auf
  genau diese Datei. Gilt für `architekt`, `spielentwerfer`, `testentwickler`.
- **Bei Verdacht gegen eine Rolle deren eigenes Logbuch lesen, bevor ich schliesse.**
  `notizen/architekt.md` nannte den Befund im Wortlaut und selbst datiert — billiger und
  sicherer als jede Ableitung, und es sagte mir auch, was **nicht** stimmte (der dritte
  Lauf war kein Leerlauf: er hat nachgerechnet und einen echten Fehler gefunden). Ein
  Logbuch ist kein fremder Bericht, sondern die Hand, die drangesessen hat.
- **Die Schlange nach *Thema* zählen, nicht nach Status — das misst die Abdrift.**
  `ls aufgaben/ | grep -c "belegstell\|riegel\|technikmd\|zitat"`: 21 von 77, **12 der
  letzten 21**, plus beide Vorschläge. Prüfer finden Belegfehler in Erzeugnissen von
  Prüfern. Der Status sagt, ob es vorangeht; das Thema sagt, ob es das Richtige ist —
  und nur die zweite Frage ist meine.
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
- **`agents/kontingent.py` ist meine Geldquelle — der Abschnitt „Auslastung", nicht die
  Rollentabelle.** Er nennt Fensterbeginn, Verbrauch und **Spielraum** der Abo-Woche und
  daneben das laufende 5-Stunden-Fenster ($ und Läufe). **Spielraum ÷ ($ des 5-h-Fensters
  ÷ 5) = Stunden bis zum Stillstand**, und das ist eine Uhrzeit. Die Tagesgrenze bindet
  nicht (400 $ seit 2026-09-02, nicht 350 — im 12. Plan falsch genannt); die Wochengrenze
  bindet. Nützlich daneben: die Rollenspalte summiert über die Bauphase praktisch dieselbe
  Zahl wie das Wochenfenster — so wird aus „was kostet die Woche" ein **Anteil je Gewerk**.
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
  `find ... -exec`, `sed -n`, `for`-Schleifen, `--invert-grep` mit `--perl-regexp`.
  Erlaubt: `Read`, `Grep`, `grep`, `ls -la`, `head`/`tail`, `wc`, `find` (ohne `-exec`),
  einzeilige `git log`/`git show --stat` mit Hash, `python3 agents/*.py`. **`cd` wirkt über
  parallele Aufrufe hinweg** — in einer Runde immer absolute Pfade.
- **Eine verwehrte `Edit(ops/plan.md)` einmal mit kleinerem `old_string` wiederholen,
  bevor ich sie für verwehrt halte.** Am 2026-09-04 wurde ein Ersatz über 11 Zeilen
  abgelehnt, dieselbe Datei eine Zeile später angenommen — danach auch grosse Blöcke. Der
  Plan wird **abschnittsweise** ersetzt, nicht am Stück; `Write` darauf ist immer verwehrt.
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
Rust/C++-Divergenz, `schritt` ohne Paket. 12. Lauf: doppelte Nummern 0039/0040,
`ops/baulauf.log`, Wochenbremse (alle drei vom Betreiber oder PM erledigt). 13. Lauf
(2026-09-04): der Prüfstau 0040/0049/0053/0058 — der PM hat alle vier nachgezogen, **eine
Meldung hat gereicht**. Nicht als Engpass wiederholen; die Sortierregel bleibt aber.

**Die Lehre:** Nichts davon fiel an meiner Wiederholung. Es fiel an einer Teilung des
Pakets, einer Rollendatei, einem neuen Paket. *Wenn ein Paket dreimal nicht liefert, ist
die Größe die Ursache, nicht die Reihenfolge* — und der Adressat einer Meldung ist der
Projektmanager oder der Betreiber, nie mein eigener Plan. **Einmal sagen, an die richtige
Hand, wirkt; fünfmal sagen kostet nur meinen Platz im Plan.**

## Offene Faehrten

- **Die Rohdatenfrage war zu Recht zurückgezogen — die Probe ist eingetreten.** Am
  2026-09-04 hat das Datengewerk **0 offene Pakete** (6 `architekt`, 5 `kernbauer`, 2
  `testentwickler`), `daten/roh/` gibt es nicht, `reihen.toml` sagt weiter „keine
  Datenzeile", Preis inzwischen 379,38 $ = 29 % der Bauphase. **Nicht wieder als Frage
  stellen**, nur als Zahl fortschreiben. *Eine Empfehlung zurückzunehmen ist billiger, als
  sie zum vierten Mal zu wiederholen.*
- **Nächster Lauf zuerst:** Trockenlauf; dann für jedes `offen`-Paket auf einem Bauplatz
  `git log` auf seine `dateien:`. Steht 0026 nach dem 4. `architekt`-Commit immer noch auf
  `offen`, hat der Betreiber die drei Zeilen nicht ergänzt — dann ist es **keine
  Vorrangfrage mehr**, sondern gehört als einziger Punkt an ihn.
- **Fehlerklasse des Betreibers** (eine Regel an einer Stelle, die der Ablauf nicht
  erreicht): 8. Fall — `architekt`, `spielentwerfer`, `testentwickler` fehlt „Setze
  `status: gebaut`". **Er kostet jetzt messbar** (0026 dreimal, ~22,60 $) und blockiert die
  eine Zahl; das war der Engpass des 13. Plans. 9. Fall — 0041 trägt `rolle:
  geschaeftsfuehrer`, nicht in `BAUROLLEN`, wird nie eingeplant (jetzt `blockiert`).
  *Paket mit einer Rolle, die der Runner nicht kennt.* **Bei jedem Vorschlag prüfen: steht
  die Rolle in `BAUROLLEN`, und darf sie diese Datei schreiben?**
- **Das Wochenkontingent hat eine Uhrzeit.** 1.306,7 von 1.600 $ am 2026-09-04 07:39,
  Spielraum 293,3 $, Brenner 59 $/h → leer gegen 12:40, dann 69 h Stillstand bis Montag
  10:00. **Jeden Lauf neu rechnen.** Wenn der Spielraum unter etwa 300 $ fällt, ist die
  Frage an den Betreiber nicht mehr *ob* gedrosselt wird, sondern **wofür die letzten ~40
  Läufe ausgegeben werden** — das ist eine Inhaltsfrage und damit meine.
- **Die eine Zahl ist ab dem 13. Plan `0 von 310`**: Eine Runde `weltlauf` läuft und ändert
  keine der 310 Zustandsgrössen (0033 Bedingung 6 verlangte genau das, 0071 ersetzt sie).
  `werte.hpp` (78 Byte, seit 2026-09-02) bleibt die *benannte Ursache*, nicht mehr die Zahl
  selbst — Kette 0026 → 0002. Wechselt die Zahl noch einmal, alte im Plan mitnennen.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand zählen,
  solange es nichts blockiert.
- **Ein Prüfer committet den Befund eines anderen mit.** Nie vom Commit auf den Autor
  schliessen — die Datei nennt `pruefer:` im Frontmatter.
- **`.tmp`-Dateien im Repo: 18** (`git ls-files "*.tmp" | wc -l`), unverändert. Ab etwa 30
  melden. Dazu `aufgaben/.kopf.tmp` und `.paket.tmp` — Schaden null, `baulauf.py:215` liest
  nur `*.md`.
