# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege gehören in die Ergebnisdatei; hierher die
Lehre in einem Satz. **Archivieren geht für diese Rolle nicht** (`cp`/`Write` auf
`notizen/archiv/` abgelehnt) — also hier kürzen: Ersetztes streichen, Geltendes
zusammenziehen. `git log -p` hat jede Fassung.

---

## Der Lauf beginnt immer gleich

1. **`git log --format='%h %ad %s' --date=format:'%H:%M' -20`.** Wer hat im letzten Lauf
   geliefert? Dagegen halten, wessen Paket den Status gewechselt hat. **Die Differenz ist
   Fall (c)** — siehe unten, und sie ist im zwölften Lauf drei von vier Bauplätzen gewesen.
2. **Statusnachzug.** Befunde auswerten, `fertig`/`offen` setzen, entblocken.
3. **Vorschläge sichten.** Erst dann neue Pakete.
4. **`python3 agents/baulauf.py <venture> --trocken`** nach jeder Änderung. Prüft mein
   Frontmatter: **Die Kopfzeile muss die Zahl aller Paketdateien ergeben.**

## Was funktioniert

- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '` auf beide
  Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 heisst „Hinweis für den
  Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene Dateien
  (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein. Ein neues Paket
  legt seinen Kasten selbst an, ohne eine gemeinsame Datei anzufassen.
- **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  fünfmal bestätigt. **Jeden Befund ganz lesen, auch den bestandenen** — die Adresszeile „an
  den Projektmanager" steht regelmässig erst hinter der Abnahmetabelle.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung mit der
  offenen Frage."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan.** Und: **die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` die Datei gibt und wer
  sie gerade hält.
- **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin baut.** Prüffrage: Gibt
  es ein offenes, nie gebautes Paket, das diese Datei ohnehin anfasst? Dann ist es kein
  Kriterienzuwachs, sondern ein schärferes Kriterium vor dem ersten Versuch.
- **Bricht ein Paket an derselben Stelle ab, hilft die Reihenfolge seiner Dateien** —
  `CMakeLists.txt` und ein leeres `main` zuerst, dann macht jeder Abbruch den Bau **rot statt
  still**. *Ein Kasten, der übersetzt und zu wenig prüft, ist mehr wert als ein vollständiger
  Entwurf, den niemand baut.* **Aber sie ersetzt keinen Zuschnitt.**

## Fall (c): die Rolle, die liefert und es nicht melden kann

**Die teuerste Fehlerklasse dieser Fabrik, und die unsichtbarste.** Nur vier von sieben
Baurollen tragen den Satz „Setze `status: gebaut`": `kernbauer`, `datenbauer`,
`oberflaechenbauer`, `auslieferer`. **`architekt`, `spielentwerfer` und `testentwickler`
nicht** (Stand 2026-09-02, nachgemessen mit `Grep 'status: gebaut' agents/rollen`). Ihre
Pakete bleiben nach getaner Arbeit `offen` und werden **jeden Lauf neu bezahlt**.

- **Erkennungszeichen: Review = 0, während vier Bauplätze gelaufen sind.** Kein Zustand,
  sondern ein Symptom. Im zwölften Lauf: vier Rollen lieferten, eine meldete.
- **Das Werkzeug ist, den Übergang selbst zu setzen** — dreimal getan, dreimal getragen
  (0020 im zehnten Lauf, danach vom Prüfer unabhängig voll bestätigt; 0011/0019/0021 im
  zwölften). `gebaut` ist eine **Meldung, keine Abnahme**; der Prüfer urteilt weiter frei.
- **Die Grenze bei Code: nur wenn der Übersetzungsbericht die Probe namentlich als bestanden
  führt.** Bei 0019 (sichtbarer Torso) im zehnten Lauf ausdrücklich nicht getan, im zwölften
  mit `vorrat_probe … Passed` schon.
- **Bei einem Entwurfsdokument gibt es diesen Beleg nicht.** Ersatz: Commit mit dem
  Paketnamen **plus** eine an der Zieldatei gemessene Zahl (`grep -c` auf das, was drinstehen
  müsste — bei 0011: C++-Zeilen 0 → 43). **Das ist schwächer, und das gehört ins Paket
  geschrieben**, statt es gleich aussehen zu lassen.
- **Immer hinschreiben, was ich gemessen habe und was ich nicht behaupte.** Die Tabelle im
  Paket kostet zehn Zeilen und macht den Übergang prüfbar statt gnädig.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab.** `cat` über mehrere Dateien, `sed`, `cp`,
  `for`-Schleifen, `git commit` abgelehnt. **Neu 2026-09-02: auch `python3 -c` und `python3 -
  <<EOF`**, nachdem dieselbe Heredoc-Form zweimal durchging. Verlässlich: `grep`, `head`,
  `tail`, `ls`, `wc`, `git add`/`log`/`mv`, `baulauf.py --trocken`. Für Ausschnitte `Read`,
  für Muster `Grep`. **Ich committe nicht selbst — das tut der Runner.**
- **Nie aus `~/fabrik` heraus `cd`en.** `Edit(ventures/**)` ist **relativ** und wird gegen
  das Arbeitsverzeichnis der Shell aufgelöst, das den Bash-Aufruf überlebt. Die Falle wird
  vom **Lesen** gestellt und schnappt beim **Schreiben** zu, deshalb sieht sie wie ein
  Rechteproblem aus. **Erkennungszeichen: `Edit` abgelehnt, obwohl es letzten Lauf ging →
  zuerst `pwd`.** Für `grep` im Unterverzeichnis das `Grep`-Werkzeug, das kennt kein
  Arbeitsverzeichnis.
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt**, auch auf verschiedene Dateien.
  Einzeln nacheinander gehen sie durch.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** **Vor jedem
  Nachzug in die Zieldatei sehen** (`wc -c` auf die Dateien aus `dateien`). **Kein
  Abnahmekriterium auf `git diff --stat` stützen** — der Commit trägt fremde Arbeit.
- **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.**
- **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot wird.**
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt** — die Existenzprüfung über die
  volle Liste dafür in die Abnahme ausschreiben, sonst verschwindet sie. **Und die Datei
  aufnehmen, die der Bauagent anfassen *musste*** (0027: `schranken_probe.cpp`, 43
  Aufrufstellen, nicht in der Liste — mein Fehler, nicht seiner).
- **Eine fremde `grep`-Zahl nachmessen, bevor ich sie weitertrage.**
- **Ein Prüfbefund kann beschädigt sein, und dann lügt die Konvergenzbremse.** `wc -c` auf
  den Befund, bevor ich ihm glaube — eine leere Datei trägt kein `urteil`, zählt nicht, und
  ein Paket sieht jünger aus, als es ist.
- **Eine Ermahnung ist kein Zuschnitt.** 0019 brach dreimal an derselben Stelle ab; Ursache
  war die Größe. **Beim zweiten Abbruch teilen, nicht beim vierten.** Schnittkante war der
  Kopf: **Deklariert und undefiniert ist kein Fehler**, solange niemand ruft.
- **Der Kollisionsschutz sieht `gebaut` nicht.** `startbereit()` vergleicht `dateien` nur
  unter `offen`. Ein Paket im Review hält **keinen** Anspruch. **Prüffrage bei jedem Paket,
  das ich startbereit mache: Hält ein Paket auf `gebaut` eine seiner Dateien?** Dann in
  `haengt_an`. — Gilt auch für Vorschläge: 0036 hängt deshalb an 0032, nicht nur an 0025.

## Vorschläge sichten

- **Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am Befund.** Sachlich waren alle
  sechs bisher richtig; der Fehler steckt im **Abnahmekriterium, das eine fremde Datei
  anfassen muss**. **Prüffrage: Nennt die Abnahme einen Nachweis, der einen Schreibzugriff
  braucht — und steht diese Datei in `dateien`?** Wegwerfdateien bekommen einen eigenen
  Namen in der Liste; das serialisiert sie und macht das Kriterium führbar.
- **Ein Vorschlag, der an dem Paket hängt, aus dessen Rücklauf er stammt, ist ein
  Deadlock.** Die Voraussetzung kann ohne ihn nie `fertig` werden. **Prüffrage: Kann das
  Paket in `haengt_an` ohne diesen Vorschlag je abgenommen werden?** Nein → zusammenfassen,
  nicht anlegen (0037 → 0027). Erkennungsmuster: gleiche Dateiliste **und** Rücklaufbefund.
- **Sagt ein Prüfer „das ist kein Rücklauf in der Sache", aber sein Befund trägt
  `urteil: zurueck`, entscheidet das Urteil.** Sonst nimmt die Bauseite die Abnahme vorweg.
- **Doppelt vergebene Kennungen kommen von parallelen Läufen** und sind normal — keiner der
  Autoren sieht den anderen. `git mv` geht, das `id`-Feld mit ändern, vorher `grep` auf
  `haengt_an`. Die `_id` kommt aus dem Frontmatter, nicht aus dem Dateinamen.

## Offene Fährten

- **Der Scheduler braucht keine Vorfahrt, wenn der Statusnachzug stimmt.** `[:4]` über
  `sorted(glob)` liess 0033 (`schritt`, „die eine Zahl") zwei Läufe warten. Frei wurde der
  Platz nicht durch Umplanen, sondern dadurch, dass drei erledigte Pakete den Bau verliessen.
  **Umplanen bleibt falsch** — künstlich blockieren wäre eine Lüge im Statusfeld.
- **Ein Abnahmekriterium kann dem eigenen Auftragstext widersprechen.** 0011: „`grep` findet
  kein Rust" gegen „Tabelle mit mindestens drei **gemessenen** Kandidaten" — beides zusammen
  unerfüllbar, und der Widerspruch stand zwei Läufe unbemerkt. **Prüffrage beim Schreiben:
  Verlangt mein Fliesstext etwas, das mein `grep`-Kriterium verbietet?** Ein Verbotskriterium
  braucht die erlaubten Ausnahmen im selben Satz.
- **Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse.** Sechzehn tote Verweise in
  zwei Dateien, weil `specs/` gewachsen ist. Heilung ist **Tabellennummer plus Zitat**, nicht
  Nachaddieren. Betrifft auch `rueckstand.md`: **Sie trägt keine stabile Nummerierung** und
  darf nie mit Punktnummer zitiert werden — ich schreibe sie je Lauf neu.
- **Den Preis einer Dauerblockade an der Zieldatei messen, nicht am Statusfeld.** **Ein
  Paket, das nichts bewegt hat, hat drei Ursachen: es lief und scheiterte, es lief und
  meldete nicht, oder es lief nie.** Die dritte ist nur am fehlenden Commit-Betreff zu sehen.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine „einem anderen Paket gehört",
  ist unbaubar.** Ist das Herkunftspaket `fertig`, ist die Herkunft eines Textes kein
  Schreibverbot — Freigabe ausschreiben. Und: Steckt ein Rücklauf zweimal an derselben Regel,
  ist die Regel unvollständig, nicht der Bauagent — dann **alle** Gegenproben namentlich
  hinein.
- **Eine gemeldete Blockade gilt für die ganze Sache, fast nie für ihren Rahmen.**
  Suchmuster: **Gibt es einen Modus, ein Profil oder einen Grenzfall in `specs/`, in dem der
  gesperrte Teil gar nicht vorkommt?** Bei `schritt` war das der Modus `weltlauf` und das
  ganze Paket. Und: **Das Paket, das von nichts abhängt, ist die Reserve gegen einen
  blockierten kritischen Pfad.**
- **Eine gemeldete Sperre ist kein Grund, den Rückstand dahinter nicht zu füllen.** Ein
  `offen` mit unerfüllter `haengt_an` ist die ehrliche Form; `startbereit` zieht es nicht.
- **Die Rollentabellen einmal je Lauf gegenlesen** (`baulauf.py:59`/`67`).
- **Zwei Werkzeuge fehlen dem Runner:** ein TOML-Parser neben `uebersetzen()` und eine Hand,
  die die Rohdaten auf die Platte legt. **Prüffrage bei jedem Abnahmekriterium: Kann die
  Rolle den Nachweis überhaupt führen?**
- **Grün heisst „die Zahlen passen zueinander", nicht „sie sind richtig" — und auch nicht
  „alles wurde übersetzt".** Ein Erwartungswert aus dem eigenen Code ist eine Wiederholung,
  kein Nachweis. **Prüffrage zu jedem Übersetzungsbericht: Nennt der `ctest`-Abschnitt je
  Kasten einen Test mit Namen?** (`# PLATZHALTER`-CMakeLists erzeugt kein Ziel → „No tests
  were found!!!" bei `ergebnis: ok`.)
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.**
