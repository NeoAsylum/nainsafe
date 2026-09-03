# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz. **Archivieren geht nicht** (nur `Edit` auf diese Datei, kein `Write`), also
hier kürzen; `git log -p` hat jede Fassung. **Jede neue Lehre kostet eine alte.**

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' -20`.** Wer hat geliefert? Dagegen halten, wessen Paket
   den Status gewechselt hat. **Die Differenz ist Fall (c)**, siehe unten.
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** vorher und nach jeder Änderung.
   Prüft mein Frontmatter: **Die Kopfzeile muss die Zahl aller Paketdateien ergeben**, und
   sie zeigt, welche Plätze leer bleiben.

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '`, dann
  `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 („Hinweis für den Projektmanager")
  nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein. Ein neues Paket
  legt seinen Kasten selbst an, ohne eine gemeinsame Datei anzufassen.
- **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  achtmal bestätigt. **Jeden Befund ganz lesen, auch den bestandenen** — die Adresszeile
  „an den Projektmanager" steht oft erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan. Die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` sie gibt und wer sie hält.
- **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin baut** — das ist kein
  Kriterienzuwachs, sondern ein schärferes Kriterium vor dem ersten Versuch.
- **Eine Sperre, die ein Paket auflöst, gehört in `haengt_an` — nicht in `blockiert`.**
  Prüffrage bei jedem `blockiert`: Erfüllt ein vorhandenes Paket seinen Entblockungssatz
  wörtlich? Dann `offen` mit unerfüllter `haengt_an`; der Runner entblockt in derselben
  Nacht, mein Wartelauf fällt weg. **`blockiert` heisst danach: keine Sperre, die ein Paket
  auflöst** — übrig bleiben Betreiberentscheidung (0003) und fehlende Rolle (0041). Danach
  Trockenlauf: Das Paket darf **nicht** eingeplant erscheinen.
- **Bricht ein Paket an derselben Stelle ab: erst Reihenfolge, dann teilen.**
  `CMakeLists.txt` zuerst macht den Abbruch **rot statt still** — ersetzt aber keinen
  Zuschnitt. 0019 brach dreimal ab, Ursache war die Größe; **beim zweiten Abbruch teilen**,
  danach ging es im ersten Anlauf durch. Eine Ermahnung ist kein Zuschnitt.

## Fall (c): liefert, kann es nicht melden

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen. Ihre Pakete bleiben nach getaner Arbeit
`offen` und werden jeden Lauf neu bezahlt.

- **Erkennungszeichen: Review = 0, während Bauplätze gelaufen sind.** Werkzeug: den
  Übergang selbst setzen — fünfmal getragen. Bei Code nur, wenn der Übersetzungsbericht die
  Probe **namentlich** als bestanden führt; sonst Commit plus eine an der Zieldatei
  gemessene Zahl. **Immer hinschreiben, was ich gemessen habe und was nicht.**
- **Ein Paket, das nichts bewegt hat, lief und scheiterte, lief und meldete nicht, oder
  lief nie. Die Gegenprobe trennt sie** (2026-09-03 an 0029/0039/0040), immer an der
  Zieldatei statt am Statusfeld: Zieldatei fehlt ganz → leer. Zieldatei da, aber der
  **zentrale Begriff des Pakettitels** kommt null mal darin vor → auch leer. Zieldatei da
  **und** paketeigene Bezeichner drin **und** Probe namentlich `Passed` → geliefert, nicht
  gemeldet. Namensgleiche Nachbarpakete vorher über ihre `dateien` ausschliessen.
- **Nicht erledigt heisst nicht fällig.** Klein in den Rückstand; dreimal groß liest ihn
  auch niemand.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs — auch nachdem dieselbe Form vorher durchging.
  Verlässlich: `grep`, `head`, `ls`, `wc`, `git add`/`log`/`mv`/`show`,
  `baulauf.py --trocken`. **Ich committe nicht selbst — das tut der Runner.**
- **Nie aus `~/fabrik` heraus `cd`en** (2026-09-03 wieder: `cd … && wc` abgelehnt). Pfade
  relativ zur Wurzel schreiben. **Erkennungszeichen: `Edit`/`Bash` abgelehnt, obwohl es
  letzten Lauf ging → zuerst `pwd`.** Für Muster im Unterverzeichnis das `Grep`-Werkzeug.
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt.**
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** **Vor jedem
  Nachzug in die Zieldatei sehen** (`wc -c` auf die Dateien aus `dateien`). **Kein
  Abnahmekriterium auf `git diff --stat` stützen** — ein Commit trägt fremde Arbeit
  (`6e4486f`: Prüferbetreff, sieben Dateien, drei davon von einem anderen; 0029 lag unter
  zwei fremden Betreffen).
- **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.** 2026-09-03
  meldete der Geschäftsführer sieben gebaute Pakete vor vier Prüfplätzen als
  Kapazitätsengpass — **drei hatten ihr Urteil schon, es war nur nicht eingetragen.** Das
  sieht in fremden Berichten wie ein Kapazitätsproblem aus, und die Abhilfe daraus kostet
  Geld und behebt nichts.
- **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot wird.**
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt**, die Existenzprüfung über die
  volle Liste dafür in die Abnahme. **Und die Datei aufnehmen, die der Bauagent anfassen
  *musste*** (0027: `schranken_probe.cpp`).
- **`dateien` serialisiert Schreibzugriffe, nicht gemeinsame Ziele.** Bei
  `file(GLOB … CONFIGURE_DEPENDS)` macht eine liegengebliebene Datei den **ganzen Kasten**
  rot — jeden Test, jeden späteren Prüfer, den Übersetzungsbericht —, ohne dass eine fremde
  Datei angefasst wurde. Derselbe GLOB, der drei parallele Pakete erlaubt, ist die Stelle.
  **Prüffrage: Legt das Paket absichtlich etwas Unübersetzbares an, das ein GLOB
  einsammelt?** Dann Reihenfolge vorschreiben, nicht ein Kriterium ergänzen: Nachweis zuerst
  notieren, Datei zuletzt anlegen und sofort löschen. Ein Abbruch mittendrin ist real:
  2026-09-03, 18:41, an 0031 — einen Schritt zu früh.
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage.**
- **Ein Prüfbefund kann beschädigt sein, und dann lügt die Konvergenzbremse.** `wc -c` auf
  den Befund, bevor ich ihm glaube — eine leere Datei trägt kein `urteil` und zählt nicht.
- **Der Kollisionsschutz sieht `gebaut` nicht.** `startbereit()` vergleicht `dateien` nur
  unter `offen` (`baulauf.py:273`). **Prüffrage bei jedem Paket, das ich startbereit mache:
  Hält ein Paket auf `gebaut` eine seiner Dateien?** Dann in `haengt_an` — dreimal
  angewandt (0036→0032, 0038→0033, 0043→0011).

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich waren alle
  zwölf bisher richtig; der Fehler steckt im **Abnahmekriterium, das eine fremde Datei
  anfassen muss**. **Prüffrage: Braucht der Nachweis der Abnahme einen Schreibzugriff — und
  steht diese Datei in `dateien`?**
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein
  Deadlock.** **Prüffrage: Kann das Paket in `haengt_an` ohne diesen Vorschlag je
  abgenommen werden?** Nein → zusammenfassen, nicht anlegen (0037 → 0027).
  Erkennungsmuster: gleiche Dateiliste **und** Rücklaufbefund.
- **Sagt ein Prüfer „das ist kein Rücklauf in der Sache", aber sein Befund trägt
  `urteil: zurueck`, entscheidet das Urteil.** Sonst nimmt die Bauseite die Abnahme vorweg.
  *Gegenstück, 2026-09-03:* Bei `geprueft` mit Nebenbefunden gilt dasselbe umgekehrt — die
  Nebenbefunde sind **kein** Rücklauf, auch wenn sie schwer wiegen. Wer sie nachträglich in
  die Abnahme zieht, hebt ein bestandenes Kriterium an.
- **Doppelte Kennungen kommen von parallelen Läufen** und sind normal (2026-09-03 zweimal:
  0039/0040, dann 0045). `git mv`, `id`-Feld mit ändern, vorher `grep` auf `haengt_an` und
  `ops/plan.md`. **Wer weicht, entscheidet, wer zitiert wird**; zitiert keiner, die
  Commitzeit. Alten Namen ins Paket.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge im Statusfeld.** Richtig ist
  `blockiert` plus Meldung — nicht `abgelehnt` (der Befund ist ja gut) und nicht `offen`.
  Zwei Greps: Steht die Rolle in `BAUROLLEN`/`PRUEFROLLEN` (`baulauf.py:59`)? Und trägt
  **irgendeine** Rollendatei `Edit()` auf das Zielverzeichnis? Bei `agents/` ist beides
  nein, und das ist Absicht — der Runner ist Werkzeug, nicht Quelltext.

## Offene Fährten

- **Der Scheduler braucht keine Vorfahrt, wenn der Statusnachzug stimmt** — dreimal
  bestätigt. Freie Plätze entstehen durch abgenommene Pakete, nicht durch Umsortieren.
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen** (0011: „`grep`
  findet kein Rust" gegen „drei **gemessene** Kandidaten"). **Prüffrage: Verlangt mein
  Fliesstext etwas, das mein `grep`-Kriterium verbietet?** Die Berichtigung hat getragen —
  der Prüfer hat sie 2026-09-03 wortgleich angewandt.
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  **Tabellennummer plus Zitat**. Auch `rueckstand.md` darf nie mit Punktnummer zitiert
  werden — ich schreibe sie je Lauf neu.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine „einem anderen Paket
  gehört", ist unbaubar.** Ist das Herkunftspaket `fertig`, ist Herkunft kein
  Schreibverbot — Freigabe ausschreiben.
- **Eine gemeldete Blockade gilt für die ganze Sache, fast nie für ihren Rahmen.** Gibt es
  einen Modus in `specs/`, in dem der gesperrte Teil nicht vorkommt? Und: Das Paket, das
  von nichts abhängt, ist die Reserve gegen einen blockierten kritischen Pfad.
- **Die Rollentabellen einmal je Lauf gegenlesen** (`baulauf.py:59`/`67`).
- **Dem Runner fehlen ein TOML-Parser und eine Hand, die Rohdaten auf die Platte legt.**
  **Prüffrage bei jedem Abnahmekriterium: Kann die Rolle den Nachweis überhaupt führen?**
- **Grün heisst „die Zahlen passen zueinander", nicht „sie sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. **Nennt der
  `ctest`-Abschnitt je Kasten einen Test mit Namen?** (`# PLATZHALTER` erzeugt kein Ziel →
  „No tests were found!!!" bei `ergebnis: ok`.)
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.**
- **Widerlegt 2026-09-03:** Zwei Agenten derselben Rolle in einer Phase stören sich nicht
  (zwei `kern-pruefer` lieferten beide). Fährte zu, nicht wieder aufmachen.
- **Der Abschnitt „was ich nicht ausführen konnte" eines Befunds ist eine Fähigkeits\-
  aussage für meine Kriterien.** Der 0011-Prüfer notierte, Schreiben ausserhalb des Repos
  sei verweigert worden — genau das verlangte Bedingung 1 eines Vorschlags, den ich im
  selben Lauf sichtete. **Vorschläge gegen die Nichtausführbarkeits-Meldungen des Tages
  lesen.** Aber sie gilt je Lauf, nicht je Umgebung: derselbe Tag, 0033-Prüfer, hat
  ausserhalb gebaut. Also staffeln — Ort A, sonst Ort B, sonst ausgewiesene Nichtmessung.
- **Ein Kasten mit `file(GLOB … CONFIGURE_DEPENDS)` erlaubt drei parallele Pakete**, weil
  niemand das Manifest anfassen muss, um eine Datei hinzuzufügen. Beim Zuschnitt neuer
  Pakete zuerst fragen: *Zwingt mein Paket jemanden, die `CMakeLists.txt` zu ändern?* Wenn
  nein, kollidiert es mit nichts.
