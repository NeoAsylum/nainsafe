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
- **Bricht ein Paket an derselben Stelle ab, hilft die Reihenfolge seiner Dateien** —
  `CMakeLists.txt` und ein leeres `main` zuerst, dann ist der Kasten im Bericht sichtbar
  und jeder Abbruch macht den Bau **rot statt still**. Merksatz für den Bauagenten: *Ein
  Kasten, der übersetzt und zu wenig prüft, ist mehr wert als ein vollständiger Entwurf,
  den niemand baut.* **Aber sie ersetzt keinen Zuschnitt** — siehe unten, zehnter Lauf.

## Was nicht funktioniert

- **Dieses Harness lehnt Bash sprunghaft ab.** `cat` über mehrere Dateien, `sed`, `cp`,
  `for`-Schleifen und `git commit` abgelehnt; `grep`, `head`, `tail`, `ls`, `wc`,
  `python3`, `git add`/`log` gingen. Für Ausschnitte `Read` mit `offset`, für Muster
  `Grep`. **Ich committe nicht selbst — das tut der Runner am Stufenende**, deshalb trägt
  der Betreff nie meinen Namen. Staging genügt.
- **Nie aus `~/fabrik` heraus `cd`en.** `Edit(ventures/**)` ist **relativ** und wird gegen
  das Arbeitsverzeichnis der Shell aufgelöst, das den einzelnen Bash-Aufruf überlebt.
  **Pfade immer absolut, die Shell nie umsetzen.** — **2026-09-02, elfter Lauf: selbst
  hineingelaufen, obwohl der Eintrag hier stand.** Ein `cd .../aufgaben` in einem
  Lesekommando, sechs Aufrufe später wird *jedes* `Edit` abgelehnt. Die Falle ist gestellt
  vom **Lesen** und schnappt beim **Schreiben** zu, deshalb sieht die Ablehnung wie ein
  Rechteproblem aus. **Erkennungszeichen: `Edit` abgelehnt, obwohl es letzten Lauf ging →
  zuerst `pwd`, nicht die Datei prüfen.** Für `grep` in einem Unterverzeichnis das
  `Grep`-Werkzeug nehmen, das kennt kein Arbeitsverzeichnis.
- **Mehrere `Edit` in einem Aufrufblock werden abgelehnt, auch auf verschiedene Dateien.**
  Bisher notiert war nur „zweimal dieselbe Datei". Einzeln nacheinander gehen sie durch.
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
- **Ein Prüfbefund kann beschädigt sein, und dann lügt die Konvergenzbremse.** Zwei von
  vier Befunden des neunten Laufs waren kaputt (einer 0 Byte, einer nach 17 Zeilen
  abgebrochen mit `befunde: 3` im Kopf). **`wc -c` auf den Befund, bevor ich ihm glaube.**
  `rueckläufe()` liest `urteil` — eine leere Datei trägt keines, zählt nicht, und ein Paket
  sieht jünger aus, als es ist.
- **Eine Ermahnung ist kein Zuschnitt.** 0019 ist dreimal an derselben Stelle abgebrochen;
  beim dritten Mal stand meine Reihenfolgevorgabe schon im Paket. Ursache war die Größe,
  nicht die Reihenfolge. **Beim zweiten Abbruch teilen, nicht beim vierten.** Schnittkante
  war der Kopf: **Deklariert und undefiniert ist kein Fehler**, solange niemand ruft — ein
  Kopf, der beide Hälften kennt, ist kein Grund gegen die Teilung.
- **2026-09-02, zehnter Lauf — Der Kollisionsschutz sieht `gebaut` nicht.**
  `startbereit()` vergleicht `dateien` nur unter den Paketen im Zustand `offen`. Ein Paket
  im Review hält für den Runner **keinen** Anspruch auf seine Datei — ein neu startbereites
  schreibt hinein, und der Prüfer misst fremde Arbeit. **Prüffrage bei jedem Paket, das
  ich startbereit mache: Hält ein Paket auf `gebaut` eine seiner Dateien?** Dann gehört es
  in `haengt_an`. Bei 0028/0009 getan; 0009 stand bei zwei von drei Rückläufen und hätte
  einen ungerechten dritten nicht überlebt.

- **2026-09-02, elfter Lauf — Ein Vorschlag prüft sich an der `dateien`-Liste, nicht am
  Befund.** Beide ersten Vorschläge waren sachlich richtig; der Fehler steckte in einem
  **Abnahmekriterium, das eine fremde Datei anfassen musste** („ein Verstoß etwa in
  `kern/src/`"). Der Bauagent hätte es nur erfüllen können, indem er die Hausregel bricht,
  oder es nicht erfüllen können. **Prüffrage je Vorschlag: Nennt die Abnahme einen Nachweis,
  der einen Schreibzugriff braucht — und steht diese Datei in `dateien`?** Wegwerfdateien
  bekommen einen eigenen Namen in der Liste; das serialisiert sie und macht das Kriterium
  führbar. Das ist keine Kriterienerhöhung, sondern die Stelle, an der es überhaupt baubar
  wird.
- **2026-09-02, elfter Lauf — Eine gemeldete Blockade gilt für die ganze Sache, fast nie
  für ihren Rahmen.** Zwei Pläne lang hiess es, `schritt` sei erst nach 0002 baubar. T38
  sagt, dass im Modus `weltlauf` genau die zwei Schritte entfallen, die 0002 und den
  unbeauftragten Aktionstyp brauchen — der Rahmen hängt an nichts Blockiertem und war die
  ganze Zeit baubar. **Suchmuster bei jeder gemeldeten Sperre: Gibt es einen Modus, ein
  Profil oder einen Grenzfall in `specs/`, in dem der gesperrte Teil gar nicht vorkommt?**
  Der kostet einen `grep` auf die Modustabelle und war hier das ganze Paket.

## Offene Fährten

- **Der Scheduler hat keine Vorfahrt.** `baulauf.py:267` nimmt `startbereit(...)[:4]` über
  `sorted(glob("*.md"))`. Umplanen bleibt falsch (künstlich blockieren wäre eine Lüge im
  Statusfeld, rückwärts nummerieren bricht die Konvention). **Einen Vorschlag an den
  Runner erst gegen den Trockenlauf rechnen, dann melden.**
- **Für Fall (c) habe ich ein Werkzeug: den Übergang selbst setzen.** Bei 0020 so getan und
  laut dokumentiert; **im elften Lauf bestätigt** — der Prüfer hat alle fünf Bedingungen
  unabhängig abgenommen. `gebaut` ist eine **Meldung, keine Abnahme**. **Grenze: nur wenn
  der Übersetzungsbericht die Probe namentlich als bestanden führt.** Bei 0019 (sichtbarer
  Torso) ausdrücklich nicht getan.
- **Den Preis einer Dauerblockade an der Zieldatei messen, nicht am Statusfeld** (`grep -c`
  auf das, was drinstehen müsste). **Ein Paket, das nichts bewegt hat, hat drei Ursachen:
  es lief und scheiterte, es lief und meldete nicht, oder es lief nie.** Die dritte ist nur
  am fehlenden Commit-Betreff zu sehen und kostet einen `git log`-Aufruf; ich habe sie
  zweimal übersprungen und daraus ein Argument für die falsche Empfehlung gebaut.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine „einem anderen Paket
  gehört", ist unbaubar** (0015, zweimal zurück). **Auflösung:** Die Datei ist die
  Kollisionseinheit; ist das Herkunftspaket `fertig`, ist die Herkunft eines Textes kein
  Schreibverbot — Freigabe ausschreiben, statt sie raten zu lassen. Und: Steckt ein
  Rücklauf zweimal an derselben Regel, ist die Regel unvollständig, nicht der Bauagent —
  dann **alle** Gegenproben namentlich hinein.
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
