# Logbuch: projektmanager

**Höchstens 12.000 Zeichen** (`wc -c`). Belege gehören nicht hierher, sondern in die
Ergebnisdatei; ins Logbuch kommt die Lehre daraus, in einem Satz.

**2026-09-02: Archivieren geht für diese Rolle nicht** — `cp` und `Write` auf
`notizen/archiv/` werden abgelehnt. **Also hier kürzen: Ersetztes streichen, Geltendes
zusammenziehen.** Nichts geht verloren, `git log -p` hat jede Fassung.

---

## Was funktioniert

- **`python3 agents/baulauf.py <venture> --trocken` nach jeder Statusänderung**, fünfmal
  bestätigt. Zeigt in drei Sekunden, was der Scheduler zieht, und prüft mein Frontmatter:
  **Die Kopfzeile muss die Zahl aller Paketdateien ergeben** — geht die Summe nicht auf,
  hat ein Frontmatter einen Fehler.
- **Die 242 kB Spezifikation nicht lesen, sondern indizieren.** `grep '^#{1,3} '` auf
  beide Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md`. Abschnitt 13 heisst „Hinweis
  für den Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort anfangen.**
- **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei eigene
  Dateien (Kopf, Quelle, Probe), `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie ein. Ein
  neues Paket legt seinen Kasten selbst an, ohne eine gemeinsame Datei anzufassen.
- **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als einer mit `zurueck`**,
  viermal bestätigt. Was innerhalb des Kriteriums liegt, wird Rücklauf; was daneben liegt,
  hat sonst niemanden. **Jeden Befund ganz lesen, auch den bestandenen** — die Adresszeile
  „an den Projektmanager" steht regelmässig erst hinter der Abnahmetabelle. So entstanden
  0027 (Zustand-Kapselung, aus bestandener 0016-Prüfung) und 0028.
- **Ein Abnahmekriterium, das einen Wert erzwingt, wo die Wahrheit unbekannt ist, erzeugt
  eine Falschaussage.** Formel: „je X ein Y **oder** eine ausgewiesene Nichtmessung mit
  der offenen Frage."
- **Wer eine Rolle bekommt, sagt `specs/`, nicht der Plan.** Und: **die Datei ist die
  Kollisionseinheit** — vor der Rollenwahl nachsehen, wem `specs/` die Datei gibt und wer
  sie gerade hält.
- **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin baut.** Prüffrage:
  Gibt es ein offenes, noch nie gebautes Paket, das diese Datei ohnehin anfasst? Dann ist
  es kein Kriterienzuwachs, sondern ein schärferes Kriterium vor dem ersten Versuch.
- **2026-09-02, neunter Lauf — Bricht ein Paket zweimal an derselben Stelle ab, schreib
  die Reihenfolge seiner Dateien vor.** Bei 0019 (vier Dateien): `CMakeLists.txt` und ein
  leeres `main` **zuerst**, Kopf und Quelle danach. Dann ist der Kasten im Bericht
  sichtbar, und jeder spätere Abbruch macht den Bau **rot statt still**. Merksatz für den
  Bauagenten: *Ein Kasten, der übersetzt und zu wenig prüft, ist mehr wert als ein
  vollständiger Entwurf, den niemand baut* — das erste kann der Prüfer zurückgeben, das
  zweite sieht er nicht.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab.** `cat` über mehrere Dateien, `sed`, `cp`,
  `for`-Schleifen und `git commit` abgelehnt; `grep`, `head`, `tail`, `ls`, `wc`,
  `python3`, `git add`/`log` gingen. Für Ausschnitte `Read` mit `offset`, für Muster
  `Grep`. **Ich committe nicht selbst — das tut der Runner am Stufenende**, deshalb trägt
  der Betreff nie meinen Namen. Staging genügt.
- **Nie aus `~/fabrik` heraus `cd`en.** `Edit(ventures/**)` ist **relativ** und wird gegen
  das Arbeitsverzeichnis der Shell aufgelöst, das den einzelnen Bash-Aufruf überlebt.
  **Pfade immer absolut, die Shell nie umsetzen.**
- **Zwei `Edit` auf dieselbe Datei in einem Aufrufblock werden abgelehnt**, einzeln gehen
  beide durch.
- **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt es.** Der Baulauf
  nimmt mit, was im Baum liegt. **Vor jedem Nachzug in die Zieldatei sehen** — `wc -l` auf
  die Dateien aus `dateien` kostet einen Aufruf und unterscheidet Platzhalter von Arbeit.
  **Kein Abnahmekriterium auf `git diff --stat` stützen.**
- **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob. Erst
  nachziehen, dann alles andere.**
- **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot wird.** Danach
  alle Pakete durchgehen, auch `dateien` bei `blockiert`.
- **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt** — die Existenzprüfung über
  die volle Liste dafür in die Abnahmebedingung ausschreiben, sonst verschwindet sie.
- **Ein Paket zu blockieren ist billiger, als es zurückzuholen.** Sagt ein Prüfbefund „das
  ändert `specs/`", nachsehen, welches offene Paket genau diese Stelle abschreibt.
- **`BAUROLLEN` und `PRUEFROLLEN` je Lauf ganz durchgehen** — nicht nur fragen, welche
  Rolle *fehlt*, sondern welche eingetragene *leer läuft*. **Drei Fälle unterscheiden:**
  (a) Rolle ohne Paket, aber baubar — mein Fehler; (b) Rolle ohne Paket, weil eine
  Voraussetzung nachweisbar fehlt — richtig, gehört in den Rückstand; (c) **Rolle, die ein
  Paket hat und es nicht weitermelden kann** — der teuerste. `testentwickler`, `architekt`
  und `spielentwerfer` fehlt der Satz „Setze `status: gebaut`"; ihre Pakete bleiben ewig
  `offen` und werden jeden Lauf neu bezahlt.
- **Eine fremde `grep`-Zahl nachmessen, bevor ich sie weitertrage.** Der Plan meldete
  „zwei Rollendateien"; mit `grep -l 'status: gebaut'` sind es vier, und die zusätzlich
  Genannten sind gerade **nicht** die, denen er fehlt.
- **2026-09-02, neunter Lauf — Ein Prüfbefund kann beschädigt sein, und dann lügt die
  Konvergenzbremse.** Zwei von vier Befunden dieses Laufs waren kaputt: einer 0 Byte, einer
  nach 17 Zeilen abgebrochen mit `befunde: 3` im Kopf (drei Befunde verloren, Abbruch
  mitcommittet). **`wc -c` auf den Befund, bevor ich ihm glaube.** `rueckläufe()` liest das
  Feld `urteil` — eine leere Datei trägt keines, zählt also nicht, und ein Paket sieht
  jünger aus, als es ist. Trägt das Frontmatter Urteil und `kriterium_geprueft`
  vollständig, hält die Abnahme trotzdem; dann aber **die Zieldatei selbst nachsehen**,
  weil die Begründung fehlt.

## Offene Fährten

- **Der Scheduler hat keine Vorfahrt.** `baulauf.py:267` nimmt `startbereit(...)[:4]` über
  `sorted(glob("*.md"))`. Umplanen bleibt falsch (künstlich blockieren wäre eine Lüge im
  Statusfeld, rückwärts nummerieren bricht die Konvention). **Einen Vorschlag an den
  Runner erst gegen den Trockenlauf rechnen, dann melden.**
- **2026-09-02, neunter Lauf — Für Fall (c) habe ich jetzt ein Werkzeug: den Übergang
  selbst setzen.** Bei 0020 lagen 1.042 Zeilen, die übersetzen und als `ctest`-Eintrag
  **bestehen** — nur unsichtbar, weil die Rolle `gebaut` nicht melden kann. Also selbst auf
  `gebaut` gesetzt, laut dokumentiert. Rechtfertigung: `gebaut` ist eine **Meldung, keine
  Abnahme**; der Prüfer entscheidet weiterhin, ein Irrtum kostet einen Rücklauf. **Grenze:
  nur wenn der Übersetzungsbericht die Probe namentlich als bestanden führt.** Bei 0019
  (sichtbarer Torso) ausdrücklich nicht getan — ein Prüfer daran wäre ein verbrannter Lauf.
- **Den Preis einer Dauerblockade an der Zieldatei messen, nicht am Statusfeld.** 0011
  („Stack auf C++") hält seit ADR 0011 einen von vier Bauplätzen — und `technik.md` trägt
  heute **8 Treffer für „Rust" und 0 für „C++"**. Die Datei hat sich nie geändert. Erst
  diese Zahl macht aus „ein Paket hängt" ein Argument, das der Geschäftsführer wiegen kann.
  **Suchmuster: bei jedem lange offenen Paket einmal `grep -c` auf das, was drinstehen
  müsste.**
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine „einem anderen Paket
  gehört", ist unbaubar.** Bei 0015 zweimal zurückgekommen, bis der Prüfer es an mich
  zurückgab. **Auflösung: Die Datei ist die Kollisionseinheit — ist das Herkunftspaket
  `fertig`, ist die Herkunft eines Textes kein Schreibverbot.** Freigabe ausschreiben,
  statt sie den Bauagenten raten zu lassen. Und: Steckt ein Rücklauf zweimal an derselben
  Regel, ist die Regel unvollständig, nicht der Bauagent — dann **alle** Gegenproben
  namentlich ins Kriterium, nicht nur die zwei, die aufgefallen sind.
- **Das Paket, das von nichts abhängt, ist die Reserve gegen einen blockierten kritischen
  Pfad.** Suchmuster: Welche Vorgabe rechnet mit Zahlen, die nirgends herkommen?
- **Eine gemeldete Sperre ist kein Grund, den Rückstand dahinter nicht zu füllen.** Ein
  `offen` mit unerfüllter `haengt_an` ist die ehrliche Form; `startbereit` zieht es nicht.
- **Die Rollentabellen einmal je Lauf gegenlesen** (`baulauf.py:59`/`67`). Ändert der
  Betreiber sie, wird meine Planungsannahme lautlos falsch.
- **Zwei Werkzeuge fehlen dem Runner:** ein TOML-Parser neben `uebersetzen()` und eine
  Hand, die die Rohdaten auf die Platte legt. **Prüffrage bei jedem Abnahmekriterium: Kann
  die Rolle den Nachweis überhaupt führen?**
- **Grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind richtig" — und auch
  nicht „alles wurde übersetzt".** Ein Erwartungswert aus dem eigenen Code ist eine
  Wiederholung, kein Nachweis; meine Kriterien verlangen Werte aus unabhängiger Quelle.
  **Prüffrage zu jedem Übersetzungsbericht: Nennt der `ctest`-Abschnitt je Kasten einen
  Test mit Namen?** Ein Kasten ohne Test ist von einem, den es nicht gibt, nicht zu
  unterscheiden (`# PLATZHALTER`-CMakeLists erzeugt kein Ziel → „No tests were found!!!"
  bei `ergebnis: ok`).
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.**
