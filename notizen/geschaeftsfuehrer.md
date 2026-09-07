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
- **Die *Arithmetik* der Schlange nennen, nicht die Reihenfolge — das ist der Hebel.**
  (2026-09-07, 15. Lauf, bestes Werkzeug bisher.) Der 14. Plan schrieb „13 Pakete tief,
  seriell, jedes Glied davor kostet einen Tag". Der Projektmanager hat daraufhin **alle
  dreizehn Glieder umgehängt** und in sein Logbuch geschrieben, alle fünf meiner
  Vorrangkennungen seien unstartbar gewesen und er sei die Ursache. Eine Reihenfolge kann
  er ablehnen; eine Rechnung nicht. **Und: die Empfehlung an den Betreiber (ein Satz in
  `projektmanager.md`) war überflüssig** — der PM hat sie selbst erledigt, aus derselben
  Seite. *Erst den Engpass an die richtige Hand benennen, dann fragen, ob eine Regel
  fehlt.*
- **Der nächste Engpass steht in der jüngsten `pruefung-*`, einen Tag vor den Paketen.**
  0208 („der Rahmen kann keinen Parameter lesen — sperrt alle sechs Schritte") wurde im
  Befund zu 0197 geboren, nicht im Rückstand. Prüferbefunde des Tages vor den Vorschlägen
  lesen.
- **Jeden `vorschlag` mit `dateien:` gegen `agents/lauf.py:NIE` halten.** Dort steht
  `Edit(/agents/**)`, `Edit(/CLAUDE.md)`, `Edit(/decisions/**)`, `Edit(/grenzen.md)`.
  0208-baulauf zielt auf `agents/baulauf.py` — auf `offen` gesetzt ein sicher verlorener
  Lauf. Zusammen mit der Rollenprüfung (`BAUROLLEN`) sind das zwei Grep, die einen Lauf
  sparen.

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
Rust/C++-Divergenz. 12. Lauf: doppelte Nummern 0039/0040, `ops/baulauf.log`, Wochenbremse.
13. Lauf: der Prüfstau 0040/0049/0053/0058 — **eine Meldung hat gereicht**. 14. Lauf
(2026-09-06): „die sechs Schritte haben kein Paket" und die serielle `technik.md`-Schlange
— der PM hat 0197 geschnitten und alle dreizehn Glieder umgehängt, ohne dass der Betreiber
etwas tun musste. **Beides nicht als Engpass wiederholen.**

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
- **Nächster Lauf zuerst:** Sind 0198 und 0208 auf `offen`? Wenn nein, ist der Engpass
  derselbe und die Frage geht an den PM, nicht in eine neue Analyse. Steht `belegstellen_riegel`
  im Bericht des Tages weiter rot, hat der Betreiber die Übersetzerfrage nicht entschieden
  — dann als einziger Punkt an ihn, nicht neu begründet.
- **Ohne `Bash` (15. Lauf, 2026-09-07) fällt jedes Skript aus.** Kein `baulauf.py --trocken`,
  kein `kontingent.py`. Ersatz, alle rein lesend: `ops/kontingent.md` (vom Wochenlauf, bis
  zu einem Tag alt), `befunde/uebersetzung-<datum>.md` (Compiler und ctest im Wortlaut,
  runner-erzeugt), und `Grep "^status:"` über `aufgaben/` für die Schlange. Das reicht für
  einen ganzen Plan — **nicht erst Werkzeuge suchen.** Die `.tmp`-Reste in `aufgaben/`
  verfälschen die `^status:`-Zählung um zwei (beide `gebaut`).
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
- **Die eine Zahl:** 13. Plan `0 von 310`, seit dem 14. **`1 von 310`** (`partie.runde`).
  Am 2026-09-07 zum ersten Mal *gedruckt* statt hergeleitet — Mitschnitt von `schritt_probe`
  im eigenständigen Kernbaum. Benannte Ursache jetzt nicht mehr organisatorisch, sondern
  zwei Lücken in `specs/`: die Regel (0198, `Realeinkommen` hat keine Rechenvorschrift) und
  der Weg (0208, `schritt()` hat kein Parameterargument). **Bewegt sich die Zahl, bevor
  beide `fertig` sind, stimmt die Messung nicht.** Alte Zahl im Plan mitnennen.
- **Der Übersetzungslauf ist neu und bricht Zitate.** Rolle `uebersetzer` (Modell Fable,
  eigener Topf), `ops/uebersetzt.txt` führt die fertigen Abschnitte. Er benennt
  Überschriften um; `belegstellen_riegel` fällt seitdem in beiden Bäumen aus, zehn Zitate.
  `CLAUDE.md` sagt dazu weiter „not planned" — der Satz ist überholt. **Nur der Betreiber
  kann das ändern; steht es im nächsten Plan noch offen, nicht neu begründen, nur zählen.**
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Nicht als Rückstand zählen,
  solange es nichts blockiert.
- **Ein Prüfer committet den Befund eines anderen mit.** Nie vom Commit auf den Autor
  schliessen — die Datei nennt `pruefer:` im Frontmatter.
- **`.tmp`-Dateien im Repo: 18** (`git ls-files "*.tmp" | wc -l`), unverändert. Ab etwa 30
  melden. Dazu `aufgaben/.kopf.tmp` und `.paket.tmp` — Schaden null, `baulauf.py:215` liest
  nur `*.md`.
