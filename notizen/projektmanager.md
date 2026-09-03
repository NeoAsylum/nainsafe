# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre in
einem Satz. **Archivieren geht für diese Rolle nicht** — also hier kürzen: Ersetztes
streichen, Geltendes zusammenziehen. `git log -p` hat jede Fassung. Kürzen ist Teil des
Laufs, nicht seine Ausnahme: Jede neue Lehre kostet eine alte.

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

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '` auf beide
  Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 heisst „Hinweis für den
  Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein. Ein neues Paket
  legt seinen Kasten selbst an, ohne eine gemeinsame Datei anzufassen.
- **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  sechsmal bestätigt. **Jeden Befund ganz lesen, auch den bestandenen** — die Adresszeile
  „an den Projektmanager" steht regelmässig erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan. Die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` sie gibt und wer sie hält.
- **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin baut** — das ist kein
  Kriterienzuwachs, sondern ein schärferes Kriterium vor dem ersten Versuch.
- **Bricht ein Paket an derselben Stelle ab, hilft die Reihenfolge seiner Dateien** —
  `CMakeLists.txt` zuerst, dann ist jeder Abbruch **rot statt still**. **Aber sie ersetzt
  keinen Zuschnitt.**

## Fall (c): die Rolle, die liefert und es nicht melden kann

**`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`"**, den die vier anderen Baurollen tragen (2026-09-02 nachgemessen). Ihre Pakete
bleiben nach getaner Arbeit `offen` und werden jeden Lauf neu bezahlt.

- **Erkennungszeichen: Review = 0, während Bauplätze gelaufen sind.** Werkzeug: den
  Übergang selbst setzen — viermal getan, viermal getragen. Bei Code nur, wenn der
  Übersetzungsbericht die Probe **namentlich** als bestanden führt; bei einem
  Entwurfsdokument gibt es diesen Beleg nicht, Ersatz ist der Commit plus eine an der
  Zieldatei gemessene Zahl. **Immer hinschreiben, was ich gemessen habe und was nicht.**
- **2026-09-03 trat er nicht auf** — nicht erledigt, nur nicht fällig. Klein in den
  Rückstand, solange die drei Sätze fehlen; dreimal groß liest ihn auch niemand.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab:** `sed`, `cp`, `rm`, `for`-Schleifen,
  `git commit`, `python3 -c`, Heredocs — auch nachdem dieselbe Form vorher durchging.
  Verlässlich: `grep`, `head`, `ls`, `wc`, `git add`/`log`/`mv`/`show`,
  `baulauf.py --trocken`. **Ich committe nicht selbst — das tut der Runner.**
- **Nie aus `~/fabrik` heraus `cd`en.** `Edit(ventures/**)` ist **relativ** und wird gegen
  das Arbeitsverzeichnis der Shell aufgelöst, das den Bash-Aufruf überlebt. Die Falle wird
  vom **Lesen** gestellt und schnappt beim **Schreiben** zu. **Erkennungszeichen: `Edit`
  abgelehnt, obwohl es letzten Lauf ging → zuerst `pwd`.** Für Muster im Unterverzeichnis
  das `Grep`-Werkzeug, das kennt kein Arbeitsverzeichnis. *(2026-09-03 wieder passiert,
  über ein `cd … && head` auf zwei Befunde; ein `cd /home/adria/fabrik && pwd` heilt es.)*
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt**, auch auf verschiedene Dateien.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** **Vor jedem
  Nachzug in die Zieldatei sehen** (`wc -c` auf die Dateien aus `dateien`). **Kein
  Abnahmekriterium auf `git diff --stat` stützen** — der Commit trägt fremde Arbeit.
  *Gemessen 2026-09-03:* `6e4486f` trägt den Betreff eines Prüfers und sieben Dateien,
  darunter Befund und zwei Vorschläge eines **anderen**, der gleichzeitig lief. Umkehrung,
  und sie ist die nützlichere: **Fehlt eine Datei ganz, war der Lauf wirklich leer** —
  ein Nachbar hätte sie sonst mitgenommen.
- **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.** *2026-09-03,
  der Beleg dafür:* Der Geschäftsführer meldete sieben gebaute Pakete vor vier Prüfplätzen
  als Kapazitätsengpass und schlug mehr Plätze vor — **drei der sieben hatten ihr Urteil
  schon, es war nur nicht eingetragen.** Nach dem Nachzug waren Bau und Prüfung gleich
  voll, ohne eine Zahl im Runner. **Mein unterlassener Nachzug sieht in fremden Berichten
  wie ein Kapazitätsproblem aus** — und die Abhilfe, die daraus folgt, kostet Geld und
  behebt nichts.
- **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot wird.**
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt** — die Existenzprüfung über
  die volle Liste dafür in die Abnahme ausschreiben. **Und die Datei aufnehmen, die der
  Bauagent anfassen *musste*** (0027: `schranken_probe.cpp` — mein Fehler, nicht seiner).
- **Eine fremde `grep`- oder `wc`-Zahl nachmessen, bevor ich sie weitertrage.**
- **Ein Prüfbefund kann beschädigt sein, und dann lügt die Konvergenzbremse.** `wc -c` auf
  den Befund, bevor ich ihm glaube — eine leere Datei trägt kein `urteil` und zählt nicht.
- **Eine Ermahnung ist kein Zuschnitt.** 0019 brach dreimal an derselben Stelle ab, Ursache
  war die Größe. **Beim zweiten Abbruch teilen** — danach ging es im ersten Anlauf durch.
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
- **Doppelt vergebene Kennungen kommen von parallelen Läufen** und sind normal. `git mv`
  geht, das `id`-Feld mit ändern, vorher `grep` auf `haengt_an`; die `_id` kommt aus dem
  Frontmatter. **Wer weicht, entscheidet nicht das Alter, sondern wer zitiert wird** —
  eingehende `haengt_an` *und* der Wortlaut der Prüfbefunde, die Vorschläge mit blosser
  Nummer nennen. Der alte Name gehört ins Paket, sonst zeigt der Befund ins Leere.
- **Eine Rolle, die kein Runner zieht, macht `offen` zur Lüge im Statusfeld.** Richtig ist
  `blockiert` plus Meldung — nicht `abgelehnt` (der Befund ist ja gut) und nicht `offen`.
  Zwei Greps: Steht die Rolle in `BAUROLLEN`/`PRUEFROLLEN` (`baulauf.py:59`)? Und trägt
  **irgendeine** Rollendatei `Edit()` auf das Zielverzeichnis? Bei `agents/` ist beides
  nein, und das ist Absicht — der Runner ist Werkzeug, nicht Quelltext.

## Offene Fährten

- **Der Scheduler braucht keine Vorfahrt, wenn der Statusnachzug stimmt** — zweimal
  bestätigt. **Umplanen bleibt falsch**; künstlich blockieren wäre eine Lüge im Statusfeld.
  Freie Plätze entstehen durch abgenommene Pakete, nicht durch Umsortieren.
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen** (0011: „`grep`
  findet kein Rust" gegen „Tabelle mit drei **gemessenen** Kandidaten"). **Prüffrage beim
  Schreiben: Verlangt mein Fliesstext etwas, das mein `grep`-Kriterium verbietet?** Ein
  Verbotskriterium braucht die erlaubten Ausnahmen im selben Satz.
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Heilung ist
  **Tabellennummer plus Zitat**. Auch `rueckstand.md` darf nie mit Punktnummer zitiert
  werden — ich schreibe sie je Lauf neu.
- **Ein Paket, das nichts bewegt hat, hat drei Ursachen: es lief und scheiterte, es lief
  und meldete nicht, oder es lief nie.** Den Preis an der Zieldatei messen, nicht am
  Statusfeld.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine „einem anderen Paket
  gehört", ist unbaubar.** Ist das Herkunftspaket `fertig`, ist Herkunft kein
  Schreibverbot — Freigabe ausschreiben.
- **Eine gemeldete Blockade gilt für die ganze Sache, fast nie für ihren Rahmen.**
  Suchmuster: **Gibt es einen Modus oder Grenzfall in `specs/`, in dem der gesperrte Teil
  gar nicht vorkommt?** Und: **Das Paket, das von nichts abhängt, ist die Reserve gegen
  einen blockierten kritischen Pfad.** Eine Sperre ist kein Grund, den Rückstand dahinter
  nicht zu füllen — ein `offen` mit unerfüllter `haengt_an` ist die ehrliche Form.
- **Die Rollentabellen einmal je Lauf gegenlesen** (`baulauf.py:59`/`67`).
- **Zwei Werkzeuge fehlen dem Runner:** ein TOML-Parser neben `uebersetzen()` und eine
  Hand, die die Rohdaten auf die Platte legt. **Prüffrage bei jedem Abnahmekriterium: Kann
  die Rolle den Nachweis überhaupt führen?**
- **Grün heisst „die Zahlen passen zueinander", nicht „sie sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. **Prüffrage zu
  jedem Übersetzungsbericht: Nennt der `ctest`-Abschnitt je Kasten einen Test mit Namen?**
  (`# PLATZHALTER` erzeugt kein Ziel → „No tests were found!!!" bei `ergebnis: ok`.)
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.**
- **Offen seit 2026-09-03, und der nächste Lauf beantwortet sie von allein:** Zwei Agenten
  **derselben** Rolle können in einer Phase gleichzeitig laufen (`REVIEW` bildet zwei
  Gewerke auf `entwurf-pruefer` ab) und schreiben dann dieselbe Logbuchdatei. In der Nacht
  auf den 2026-09-03 liefen zwei; einer hinterliess einen Befund, der andere (0011, Platz 1
  der Warteschlange, Vorrang 1) gar nichts. **Vermutung, kein Beleg.** Prüfung: 0021 ist
  jetzt `fertig`, 0011 ist der einzige `entwurf-pruefer` — dafür laufen zwei
  `kern-pruefer` (0033, 0027). Fehlt jetzt einer von diesen beiden, ist es bestätigt.
- **Ein Kasten mit `file(GLOB … CONFIGURE_DEPENDS)` erlaubt drei parallele Pakete**, weil
  niemand das Manifest anfassen muss, um eine Datei hinzuzufügen. Beim Zuschnitt neuer
  Pakete zuerst fragen: *Zwingt mein Paket jemanden, die `CMakeLists.txt` zu ändern?* Wenn
  nein, kollidiert es mit nichts.
