# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende. **Höchstens 12.000 Zeichen** (`wc -c`).

**Neu begonnen am 2026-09-02 (6. Lauf) bei 11.583 Zeichen.** Die vollständige alte
Fassung steht in `git show 9cb86d9:notizen/geschaeftsfuehrer.md` — sie ist nicht
gelöscht, sondern nur nicht mehr geladen. **Das vorgeschriebene Verschieben nach
`notizen/archiv/` konnte ich nicht ausführen: `mv`, `cp` und `Write` dorthin sind meiner
Rolle alle verwehrt.** Der daten-pruefer meldet dasselbe (sein Logbuch, Zeile 130) — es
ist also kein Einzelfall, sondern eine Regel, die kein Ablauf ausführen kann.
**Nächster Lauf: nicht wieder versuchen, drei Aufrufe gespart.**

---

## Was funktioniert

- **Die Spezifikation von 0016 ist 270 kB und wird nie ganz gelesen.** Getragen hat:
  Arbeitspakete und Befund-Frontmatter ganz, `specs/` nur über Gliederung und „Offene
  Entwurfsfragen", dazu `agents/*.py`. Die Wahrheit über den Zustand steht in den
  Skripten, nicht in den Dokumenten.
- **`baulauf.py --trocken` ist die schärfste Engpassmessung, die ich habe** — sie sagt
  nicht, was offen ist, sondern was der nächste Lauf *anfasst*. **Aber sie zeigt zu
  wenig** (2026-09-02, 6. Lauf): Der echte Lauf hebt zuerst den Projektmanager auf die
  Pakete (`baulauf.py:302`) und **lädt in Zeile 306 neu**, also lösen sich alle Pakete,
  die an einem gerade `geprueft`-gemeldeten hängen, noch im selben Lauf. Trockenlauf
  lesen, dann die `urteil:`-Zeilen der frischen Befunde dagegen halten — sonst
  unterschätzt man den nächsten Lauf.
- **Erst prüfen, ob die Rolle eines liegengebliebenen Pakets überhaupt eingeplant werden
  kann** (`BAUROLLEN` gegen `rolle`, zwei greps). Ein Paket ohne planende Rolle ist kein
  Rückstand, sondern ein Loch. **2026-09-02 vom Betreiber behoben** — und
  `einrichtung/rollen-pruefen.py` meldet den Fall jetzt selbst. Nicht mehr von Hand
  prüfen, das Skript laufen lassen.
- **Die Fragen des Rückstands auf ihre Ursache zurückrechnen, statt sie zu referieren.**
  Sechs vorgelegte Fragen hingen an denselben zwei nicht einplanbaren Rollen; damit war
  aus einer Liste eine Entscheidung geworden. Beste Form der Engpassfrage bisher.
- **Ein Vertagungspreis trägt nur mit Paket und Zeitpunkt.** „C kostet etwas" ist
  folgenlos, „0002 giesst die Preisbasis in `kern::werte`, sobald 0008 fertig ist" ist
  eine Frist. Dafür genügt, die `haengt_an`-Kette rückwärts zu lesen.
- **Einen Ausweg, den ich als Option anbiete, einmal wirklich aufmachen.** Zwei Pläne
  lang führte ich den Konzeptlauf als Alternative; er hält vor dem ersten Token an. Eine
  Option, die ich nicht nachgesehen habe, ist eine Vermutung im Entscheidungstext.
- **Vor jedem „unverändert seit N Plänen" die Uhr des Betreibers prüfen:** `git log` nach
  Commits *ohne* Rollenpräfix filtern. Fünf meiner Pläne entstanden in einer Nacht — das
  sind keine fünf Ablehnungen. Seine Commit-Botschaften sind zudem die einzige aktuelle
  Kostenquelle (162 von 400 $ am 2026-09-02); `ops/kontingent.md` ist vom 2026-08-30.
- **Ein Logbuch, das die Vorlage geblieben ist, ist der billigste Beweis für einen leeren
  Lauf.** Verschärft: `grep -c "<datum>" notizen/*.md` über alle beteiligten Rollen auf
  einmal, ein Aufruf. **Noch schärfer (2026-09-02, 7. Lauf): `wc -c` gegen
  `VORLAGE.md` = 1.242 Zeichen.** Eine Rolle bei ~1.250 hat *noch nie* geschrieben, nicht
  nur heute nicht — das trennt „einmal ausgefallen" von „nie gelaufen" in einem Aufruf.
  So gefunden: `test-pruefer` 1.252, `testentwickler` 1.256 — obwohl der Testentwickler
  am selben Tag zweimal committet hat.
- **Die Anweisung, die eine Rolle ausführen soll, im Rollenverzeichnis zählen, nicht in
  einer Rolle lesen.** `grep -n gebaut agents/rollen/*.md` hat den Engpass des 7. Laufs in
  einem Aufruf gezeigt: zwei Treffer, sieben Baurollen. Wo eine Regel je Rolle wiederholt
  wird, ist die Frage nicht „steht sie da", sondern „in wie vielen von wie vielen".

## Was nicht funktioniert

- **Verwehrte Werkzeuge, nicht erneut versuchen:** `git commit` in jeder Form (`git add`
  geht — der Lauf committet, nicht ich), `cat`/`sed` über mehrere Dateien, `python3 -c`,
  mehrzeilige Bash-Schleifen, `mv`/`cp`/`Write` nach `notizen/archiv/`. Erlaubt sind
  `Read`, `grep`, `ls`, `head`, `wc`, einzeilige `git`-Aufrufe und `python3 agents/*.py`.
  `state.db` ist damit für mich nicht lesbar.
- **Veraltet und unbrauchbar für den Stand eines Vorhabens:** `ops/portfolio.md`,
  `ops/kontingent.md`, `ops/auslastung.md` — alle vom 2026-08-30, keins kennt einen
  Baulauf. Nicht wieder dort anfangen.
- **Die Commit-Betreffs sagen nicht, wer was getan hat.** Jeder Agent committet seinen
  ganzen Schreibpfad, also nimmt der erste fertige Lauf die Dateien der parallelen mit.
  Nur `--stat` gegen das Feld `dateien` des Pakets trägt.
- **Das Paket, das nach der Vorgabe klingt, ist selten das, das sie ausführt.** 0008 baut
  die *Ablage* der 310 Felder, die Bedeutung der Zahlen entsteht in 0002. Ein `grep` auf
  die zitierten Vorgabenpunkte (`T5`, `T50`) trennt beides in Sekunden — ungeprüft wäre
  die schärfste Zahl des Berichts falsch gewesen.
- **Widerlegt, nicht wieder aufwärmen:** „Eine Empfehlung, die um Aufmerksamkeit
  konkurriert, wird vertagt." Falsch — es lag an der Uhr, nicht an der Darstellung. Der
  Betreiber hat die fünfmal wiederholte Empfehlung beim ersten Blick ausgeführt.
- **`baulauf.py --trocken` sagt nicht mehr, was der Lauf tut** (2026-09-02, 7. Lauf).
  Vorhergesagt {0011, 0016, 0019, 0020} — vom Trockenlauf *und* vom Projektmanager
  unabhängig. Gebaut wurde {0016, 0019, 0020, 0022}. Ich kann die Abweichung nicht
  auflösen, **weil der Baulauf kein Protokoll schreibt**: `ops/` hat `nachtlauf.log`,
  `sensorlauf.log`, `wochenlauf.log` und nichts für den Bau. Meine Vorhersage „zieht zum
  ersten Mal ein Architektenpaket" war deshalb falsch. Trockenlauf ab jetzt als *eine*
  Quelle behandeln, nie als die Messung — und den fehlenden Log jedes Mal miterwähnen,
  bis er da ist.
- **Ein Commit des Bauagenten beweist nicht, dass sein Paket etwas hinterlassen hat.**
  0020 hat committet und seine einzige Datei (`kern/test/schranken_probe.cpp`) existiert
  nicht; 0019 hat Kopf und Quelle, aber die Prüfdatei ist 15 Byte. Der billige Test ist
  `ls`/`wc -c` auf das Feld `dateien` des Pakets, nicht `git show --stat` — der
  Commit nimmt die Dateien paralleler Läufe mit.

## Offene Faehrten

- **2026-09-02 (7. Lauf), Engpass: fünf von sieben Baurollen setzen kein `gebaut`.**
  Der Satz steht nur in `kernbauer.md:83` und `datenbauer.md:85`. Folge: Ihre Pakete
  bleiben `offen` (werden jeden Lauf neu gebaut und neu bezahlt) und erreichen nie den
  Review (der zieht nur `gebaut`). Empfehlung an den Betreiber war **B**: `baulauf.py`
  setzt es selbst, wenn der Agent mit 0 zurückkommt *und* die Dateien aus `dateien` sich
  geändert haben. **Nächster Lauf zuerst:** `grep -c gebaut agents/rollen/*.md` und
  `grep -n "gebaut" agents/baulauf.py` — ist eins von beiden gewachsen, ist es erledigt;
  dann prüfen, ob 0019/0020 endlich `gebaut` tragen.
- **Der Engpass davor ist nicht gelöst, nur verschoben:** `schritt` hat weiterhin kein
  Paket. 0021 (spielentwerfer, „Schaden") ist die Vorstufe und existiert seit 07:45 —
  aber es ist nicht gelaufen, und selbst wenn, bliebe es an derselben `gebaut`-Lücke
  hängen. Prüfmuster bleibt `grep -l "schritt.hpp" aufgaben/*.md` (findet heute nur 0004).
- **Die Fehlerklasse dahinter, vom Betreiber benannt (`953bbf5`) und der eigentliche
  Fund:** dreimal in zwei Tagen lag eine Regel an einer Stelle, die der Ablauf nicht
  erreicht, und jedes Mal fiel es erst auf, als etwas **nicht** geschah. Meine Rolle ist
  die einzige, die ausbleibende Arbeit sehen kann — erledigte und nie geplante Arbeit
  sehen in jeder Zählung gleich aus. **Der vierte Fall ist mein eigenes Archiv oben.**
  Danach aktiv suchen, nicht darauf warten.
- **Der leere Platz, vierte Messung.** Läufe 4/5: je 1 von 4 Bauplätzen leer. Lauf 6:
  2 von 4 Prüfplätzen. **Lauf 7: wieder 2 von 4 Prüfplätzen (0016 ohne Befunddatei, 0009
  ohne vierte Runde) und dazu 1 von 4 Bauplätzen (0020).** Die Rate hält, die Sorte
  Platz wandert nicht mehr — es fällt jetzt auf beiden aus. Fünfte Messung: zählen, ob
  die `gebaut`-Reparatur (falls sie kommt) die Bauplätze mit erledigt; die Prüfplätze
  erklärt sie **nicht**, das bleibt eine offene Ursache.
- **Architekt und Spielentwerfer sind seit dem 2026-09-02 06:39 einplanbar und haben in
  zwei Läufen null Bytes geliefert.** `specs/` ohne Commit seit dem 2026-09-01, beide
  Logbücher ohne Eintrag, `einrichtung/rollen-pruefen.py` meldet trotzdem „keine
  Befunde". Die Verdrahtung stimmt also — die Ursache liegt woanders und ich kenne sie
  nicht. Ohne `ops/baulauf.log` ist sie auch nicht zu finden.
- **0009 steht bei zwei von drei Rückläufen** (`RUECKLAUF_MAX = 3`, `baulauf.py:295`) und
  hat jetzt **zwei Läufe hintereinander gar keine Prüfung bekommen**. Ein weiteres
  `zurueck` und das Paket fällt aus dem Betrieb. 0015 hat im 7. Lauf seinen ersten
  `zurueck` bekommen — zweites Paket auf demselben Weg, also die alte Fährte
  „Abnahmekriterien werden zum zweiten Engpass" wieder aufnehmen, wenn 0015 ein zweites
  Mal zurückkommt.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache** — das Paket sagt es selbst
  („per ADR gegen T5 oder gar nicht"). Nicht als Rückstand zählen und nicht als Engpass
  vorschlagen, solange es nichts blockiert.
- **Die 170-gegen-121-Lücke** hat seit dem 2026-09-01 niemand angefasst und blockiert
  nichts. Erst wieder aufgreifen, wenn der Kern rechnet.
- **14 `.tmp`-Dateien liegen committet im Repo** (`git ls-files "*.tmp"`), darunter
  `daten/.neu3.tmp` mit 1.608 Zeilen. Die Bauagenten behelfen sich mit Zwischendateien,
  und der Runner committet den ganzen Schreibpfad. Blockiert nichts, wächst aber je Lauf —
  ab etwa 30 Dateien in den Bericht nehmen.
