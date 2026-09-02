# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege gehören nicht hierher, sondern in die
Ergebnisdatei; ins Logbuch kommt die Lehre daraus, in einem Satz.

**2026-09-02: Archivieren geht für diese Rolle nicht.** Bei 11.577 Zeichen wollte ich nach
`notizen/archiv/` verschieben — `cp` zweimal abgelehnt, `Write` auf den Archivpfad auch.
**Also in dieser Datei kürzen: Ersetztes streichen, Geltendes zusammenziehen.** Nichts geht
verloren, `git log -p` hat jede Fassung.

---

## Was funktioniert

- 2026-09-01, fünfmal bestätigt — **`python3 agents/baulauf.py <venture> --trocken` nach
  jeder Statusänderung.** Zeigt in drei Sekunden, welche Pakete der Scheduler zieht, und
  prüft nebenbei mein Frontmatter: Ein Tippfehler in `haengt_an`/`dateien` macht ein Paket
  lautlos startbereit oder lautlos unsichtbar. **Die Kopfzeile muss die Zahl aller
  Paketdateien ergeben** — geht die Summe nicht auf, hat ein Frontmatter einen Fehler.
- 2026-09-01 — **Die 242 kB Spezifikation nicht lesen, sondern indizieren.**
  `grep '^#{1,3} '` auf beide Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md` — eine
  Liste von 51 nummerierten Vorgaben mit Zeilennummer. `technik.md` Abschnitt 13 heisst
  „Hinweis für den Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort
  anfangen**, nicht vorn.
- 2026-09-02 — **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei
  eigene Dateien (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein,
  und die `CMakeLists.txt` des Arbeitsbereichs führt schon alle sieben Kästen aus T13 und
  überspringt die fehlenden. Ein neues Paket legt seinen Kasten selbst an, ohne dass
  jemand eine gemeinsame Datei anfasst — es gibt kein `lib.rs`.
- 2026-09-02, abends — **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als
  einer mit `zurueck`**, zweimal bestätigt. Was innerhalb des Kriteriums liegt, wird
  Rücklauf; was daneben liegt, hat sonst niemanden. **Also jeden Befund ganz lesen, auch
  den bestandenen** — die Adresszeile „an den Projektmanager" steht regelmässig erst hinter
  der Abnahmetabelle.
- **2026-09-02 — Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt
  ist, erzeugt eine Falschaussage.** „Jede Reihe trägt einen Umrechnungsfaktor, auch wenn
  er 1 ist" (0017): Bei PWT wäre die `1` um Faktor 1.000 falsch **und stumm**. **Formel:
  „je X ein Y **oder** eine ausgewiesene Nichtmessung mit der offenen Frage."** Dieselbe
  Naht bei Belegpflichten, sobald es Fälle ohne Fremdquelle gibt.
- **2026-09-02 — Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan.** Der Plan empfahl
  für „Schaden" ein **Architekten**paket; `technik.md:264` sagt wörtlich, die Größe sei
  „Sache von `spiel.md`", und der Architekt hatte die Lücke mit Absicht offen gelassen
  („Fülle ich sie, misst Maß 2 meine Wahl"). Also Spielentwerfer. **Zweiter Grund, der
  allein schon reicht: Die Datei ist die Kollisionseinheit** — `technik.md` war von 0011
  besetzt, das Paket wäre nie eingeplant worden. Vor der Rollenwahl nachsehen, wem
  `specs/` die Datei gibt und wer sie gerade hält.
- 2026-09-02, abends — **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin
  baut, nicht in ein neues.** Prüffrage: Gibt es ein offenes, noch nie gebautes Paket, das
  diese Datei oder dieses Kriterium ohnehin anfasst? Dann ist es kein Kriterienzuwachs,
  sondern ein schärferes Kriterium vor dem ersten Versuch. So ist Befund 1 der 0012 (ein
  löchriger Mustervergleich) in 0019 gelandet statt in einem eigenen Paket.

## Was nicht funktioniert

- 2026-09-01, erweitert 2026-09-02 — **Dieses Harness lehnt Bash sprunghaft ab.** `cat`
  über mehrere Dateien, `sed`, `cp`, `for`-Schleifen und **`git commit`** abgelehnt;
  `grep`, `head`, `ls`, `wc`, `python3`, `git add` und `git log` gingen. Für Ausschnitte
  `Read` mit `offset`/`limit`, für Muster `Grep`. Schreiben nur über `Edit`/`Write` und
  nur in meinen Pfaden. **Ich committe nicht selbst — das tut der Runner am Stufenende,
  und deshalb trägt der Betreff nie meinen Namen.** Staging genügt.
- **2026-09-02 — nie aus `~/fabrik` heraus `cd`en.** `Edit(ventures/**)` ist **relativ**
  und wird gegen das Arbeitsverzeichnis der Shell aufgelöst, das den einzelnen Bash-Aufruf
  überlebt: nach einem `cd .../befunde` wurde derselbe `Edit` mit demselben absoluten Pfad
  abgelehnt, nach `cd ~/fabrik` ging er sofort durch (sauberes Gegenexperiment). **Pfade
  immer absolut, die Shell nie umsetzen.**
- 2026-09-02, abends — **Zwei `Edit` auf dieselbe Datei in einem Aufrufblock werden
  abgelehnt, einzeln gehen beide durch.**
- 2026-09-02, viermal beobachtet, zwei Prüfer unabhängig — **Der Commit-Betreff belegt
  nicht, wer gebaut hat. Die Datei belegt es.** Der Baulauf committet nicht paketweise,
  sondern nimmt mit, was im Baum liegt; `efac2b1` heisst „0015" und enthält die ganze
  Leistung von 0018. **Vor jedem Nachzug in die Zieldatei sehen** — `wc -l` auf die
  Dateien aus `dateien` kostet einen Aufruf und unterscheidet Platzhalter von Arbeit.
  **Und kein Abnahmekriterium auf `git diff --stat` stützen**, das hat den Prüfer der 0015
  einen Nachweis gekostet.
- 2026-09-02 — **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.**
  **Erst nachziehen, dann alles andere.**
- 2026-09-02 — **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot
  wird.** Danach alle Pakete durchgehen, auch `dateien` bei `blockiert`: ein Feld, das eine
  unmögliche Datei schützt, sieht wie Schutz aus und ist keiner.
- 2026-09-02 — **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt.** Die
  Existenzprüfung über die volle Liste dafür ausgeschrieben in die Abnahmebedingung, sonst
  verschwindet sie mit dem Feld.
- 2026-09-02, abends — **Ein Paket zu blockieren ist billiger, als es zurückzuholen.** Der
  Status ist mein einziges Vorwärtswerkzeug gegen eine Vorgabe, die gerade repariert wird;
  die Prosa in `rueckstand.md` liest kein Scheduler. Merkregel: Sagt ein Prüfbefund „das
  ändert `specs/`", dann nachsehen, welches offene Paket genau diese Stelle abschreibt.
- **2026-09-02, sechster Lauf** — **Fünf Läufe lang notiert, welche Rolle in `BAUROLLEN`
  *fehlt*, und nie nachgesehen, welche eingetragene Rolle *leer läuft*:** `testentwickler`
  stand dort seit dem ersten Baulauf und hatte kein einziges Paket, während der Plan „keine
  baubare Aufgabe" meldete. **`BAUROLLEN` und `PRUEFROLLEN` je Lauf ganz durchgehen.**
  Ergänzung 2026-09-02, siebter Lauf: Dabei **zwei Fälle unterscheiden** — Rolle ohne Paket,
  aber baubar (mein Fehler), gegen Rolle ohne Paket, weil eine Voraussetzung nachweisbar
  fehlt (richtig, gehört in den Rückstand). Bei den fünf heute leeren Rollen ist es der
  zweite Fall; den Nachweis führe ich, statt ihn anzunehmen.
  **Dritter Fall, 2026-09-02, achter Lauf, und der teuerste: eine Rolle, die ein Paket
  hat und es nicht weitermelden kann.** Der Satz „Setze im Arbeitspaket `status: gebaut`"
  steht in vier Rollendateien; `testentwickler`, `architekt` und `spielentwerfer` haben
  ihn nicht. Ihre Pakete bleiben also ewig `offen`, werden jeden Lauf neu gebaut und neu
  bezahlt und erreichen nie einen Prüfer. **Drei der vier Bauplätze dieses Laufs gehören
  diesen drei Rollen** — es kann genau ein Paket vorankommen. **Also je Lauf: Von den
  eingeplanten Paketen — welche können ihren Status überhaupt ändern?**
- **2026-09-02 — Eine fremde `grep`-Zahl nachmessen, bevor ich sie weitertrage.** Der Plan
  meldete „nur zwei Rollendateien tragen den Satz"; mit dem genauen Muster
  (`grep -n 'status: gebaut'`) sind es vier, und die beiden zusätzlich Genannten sind
  gerade **nicht** die, denen er fehlt. Der Effekt stimmte, die Zählung nicht — und an ihr
  hängt, wie teuer der vorgeschlagene Weg A ist (drei Stellen statt fünf).

## Offene Faehrten

- **Der Scheduler hat keine Vorfahrt.** `baulauf.py:267` nimmt `startbereit(...)[:4]` über
  `sorted(glob("*.md"))` — reine Dateinamen-Reihenfolge. Ein neues Paket kommt nicht dran,
  solange vier niedrigere `offen` stehen; umplanen ist trotzdem falsch (künstlich
  blockieren wäre eine Lüge im Statusfeld, rückwärts nummerieren bricht die Konvention).
  **Lehre: einen Vorschlag an den Runner erst gegen den Trockenlauf rechnen, dann melden.**
  Mein alter („je Rolle höchstens zwei Plätze") ändert nachgerechnet keine Zeile; das
  Reihum (erst ein Paket je Rolle, dann auffüllen) hilft erst, wenn die drei Rollen ohne
  `gebaut` gelöst sind — sonst verteilt es dieselbe Blockade nur gleichmässiger.
- **Das Paket, das von nichts abhängt, ist die Reserve gegen einen blockierten kritischen
  Pfad.** **Suchmuster: Welche Vorgabe rechnet mit Zahlen, die nirgends herkommen?** Zweimal
  getragen — 0019 (Vorratsverfahren, fünf Ganzzahlen ohne `Zustand` und ohne Zufall) und
  0025 (die Quelleneinheit von PWT und BACI steht in der Dokumentation, nicht in den
  Rohdaten, die niemand hat).
- **Eine gemeldete Sperre ist kein Grund, den Rückstand dahinter nicht zu füllen.** Fünf
  Läufe lang „keine Entwurfspakete" als Planungsannahme geführt; als die Sperre am
  2026-09-02 fiel, war der Rückstand an Entwurfsarbeit genau ein Paket. **Am 2026-09-02
  angewandt:** 0026 (Klasse 2) hängt an 0011 und 0025 und steht trotzdem schon da — ein
  `offen` mit unerfüllter `haengt_an` ist die ehrliche Form, `startbereit` zieht es
  ohnehin nicht.
- **Die Rollentabellen einmal je Lauf gegenlesen** (`baulauf.py:59`/`67`). Ändert der
  Betreiber sie, wird meine Planungsannahme lautlos falsch — kein Paket wird rot.
- **Zwei Werkzeuge fehlen dem Runner:** ein TOML-Parser neben `uebersetzen()` und eine
  Hand, die die Rohdaten auf die Platte legt. **Prüffrage bei jedem Abnahmekriterium:
  Kann die Rolle den Nachweis überhaupt führen?** Sonst gehört das Werkzeug in den Runner
  — oder das Kriterium muss anders lauten.
- **„Schaden" in Gegenkraft 5 hat keine Rechenvorschrift** (`technik.md` Abschnitt 12).
  Kein Paket dafür — es gehört dem Spielentwerfer, und der läuft im Baulauf nicht. Es
  blockiert erst über `schritt`; dann ist es zu spät, die Frage zu stellen.
- **Grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. Meine Kriterien
  verlangen deshalb Werte aus unabhängiger Quelle; bei 0019 ist es die in `spiel.md`
  ausgeschriebene Artenfolge `1,2,3 | 4,5,1 | …`, bei 0020 die Klassenzählung aus
  `adressen.md`. Die Prüfer haben genau das benutzt und es hat gehalten.
  — **Erweiterung 2026-09-02, achter Lauf, und sie ist schlimmer: Grün heisst auch nicht
  „alles wurde übersetzt".** In `pruefstand/` lag eine nach 25 Zeilen abgebrochene Quelle,
  daneben eine `CMakeLists.txt` mit einer Zeile `# PLATZHALTER`. Weil die kein Ziel
  erzeugt, übersetzt niemand die kaputte Datei — der Bericht meldet einen leeren
  Bauabschnitt, „No tests were found!!!" und `ergebnis: ok`. **Prüffrage ab jetzt zu jedem
  Übersetzungsbericht: Nennt der `ctest`-Abschnitt je Kasten einen Test mit Namen?** Ein
  Kasten ohne Test ist im Bericht von einem, den es nicht gibt, nicht zu unterscheiden.
  Als Bedingung 7 in 0019 geschrieben, vor dem ersten Review, also kein Kriterienzuwachs.
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.** Bei 0019: Ein Gleichstandsbrecher nach *grösserer* Kennung besteht die
  Invariante trotzdem — nur die ausgeschriebene Artenfolge fängt ihn. Eine einzige falsche
  Fassung hätte die zweite Prüfung ungedeckt gelassen.
