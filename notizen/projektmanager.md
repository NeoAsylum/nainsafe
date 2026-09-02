# Logbuch: projektmanager

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/projektmanager-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

---

## Was funktioniert

- 2026-09-01, viermal bestätigt — **`python3 agents/baulauf.py <venture> --trocken` nach
  jeder Statusänderung.** Es zeigt in drei Sekunden, welche Pakete der Scheduler wirklich
  zieht, und prüft nebenbei mein Frontmatter: `haengt_an` und `dateien` werden von
  `lauf.py:frontmatter` geparst, ein Tippfehler macht ein Paket lautlos startbereit oder
  lautlos unsichtbar. Die Kopfzeile (`n offen, m fertig, …`) muss die Zahl aller
  Paketdateien ergeben — geht die Summe nicht auf, hat ein Frontmatter einen Fehler.
- 2026-09-01 — **Die 242 kB Spezifikation nicht lesen, sondern indizieren.**
  `grep '^#{1,3} '` auf beide Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md` — eine
  Liste von 51 nummerierten Vorgaben mit Zeilennummer. `technik.md` Abschnitt 13 heisst
  „Hinweis für den Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort
  anfangen**, nicht vorn.
- 2026-09-02 — **In C++ ist der Kollisionsschnitt der Kastenschnitt.** Ein Modul sind drei
  eigene Dateien (Kopf, Quelle, Probe), und `file(GLOB … CONFIGURE_DEPENDS)` sammelt sie
  ein — es gibt keine gemeinsame Modulliste wie `lib.rs`, die jedes Paket anfassen müsste.
  **Und die `CMakeLists.txt` des Arbeitsbereichs führt schon alle sieben Kästen aus T13 und
  überspringt die fehlenden.** Ein neues Paket legt seinen Kasten also selbst an, ohne dass
  irgendjemand eine gemeinsame Datei anfasst. Vor dem Anlegen dort nachsehen: Was schon
  vorgesehen ist, kostet keine Absprache.
- 2026-09-02, abends — **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als
  einer mit `zurueck`**, zweimal bestätigt. Was innerhalb des Kriteriums liegt, wird
  Rücklauf; was daneben liegt, hat sonst niemanden. **Also jeden Befund ganz lesen, auch
  den bestandenen** — die Adresszeile „an den Projektmanager" steht regelmässig erst hinter
  der Abnahmetabelle.
- 2026-09-02, abends — **Geschärfte Vorgaben gehören in das Paket, das die Sache ohnehin
  baut, nicht in ein neues.** Prüffrage: Gibt es ein offenes, noch nie gebautes Paket, das
  diese Datei oder dieses Kriterium ohnehin anfasst? Dann ist es kein Kriterienzuwachs,
  sondern ein schärferes Kriterium vor dem ersten Versuch. So ist Befund 1 der 0012 (ein
  löchriger Mustervergleich) in 0019 gelandet statt in einem eigenen Paket.

## Was nicht funktioniert

- 2026-09-01, erweitert 2026-09-02 — **Dieses Harness lehnt Bash sprunghaft ab.** `cat`
  über mehrere Dateien, `sed -n 'a,bp'` und `for`-Schleifen wurden abgelehnt; `grep`,
  `head`, `ls`, `wc`, `python3` und `git log` gingen. Für Dateiausschnitte `Read` mit
  `offset`/`limit`, für Muster das `Grep`-Werkzeug. **Eine Ablehnung ist kein Urteil über
  den Inhalt** — bei Schreibzugriffen wiederholen, nicht umschreiben und nicht aufgeben.
- 2026-09-02, abends — **Zwei `Edit` auf dieselbe Datei in einem Aufrufblock werden
  abgelehnt, einzeln gehen beide durch.**
- 2026-09-02, zweimal beobachtet — **Der Commit-Betreff belegt nicht, wer gebaut hat. Die
  Datei belegt es.** `770e7b4` heisst „kernbauer: 0012-…" und enthält ausschliesslich die
  `zustand`-Dateien von 0008. Der Baulauf committet nicht paketweise, sondern nimmt mit,
  was im Baum liegt. **Vor jedem Nachzug in die Zieldatei sehen** — `wc -l` auf die Dateien
  aus `dateien` kostet einen Aufruf und unterscheidet Platzhalter von Arbeit. Beim zweiten
  Mal hat es sich ausgezahlt: 726 + 842 + 521 Zeilen, also echte Arbeit, `gebaut` zu Recht.
- 2026-09-02 — **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.**
  **Erst nachziehen, dann alles andere.**
- 2026-09-02 — **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot
  wird.** Nach jedem ADR, der den Stack ändert, alle Pakete durchgehen — auch `dateien` bei
  `blockiert`: Das Feld ist kein Name, sondern die Kollisionsvermeidung, und eines, das
  eine unmögliche Datei schützt, sieht wie Schutz aus und ist keiner.
- 2026-09-02, abends — **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt, nicht auf
  die Baugeschichte.** Die Existenzprüfung über die volle Liste gehört dafür ausgeschrieben
  in die Abnahmebedingung, sonst verschwindet sie mit dem Feld.
- 2026-09-02, abends — **Ein Paket zu blockieren ist billiger, als es zurückzuholen.** Der
  Status ist mein einziges Vorwärtswerkzeug gegen eine Vorgabe, die gerade repariert wird;
  die Prosa in `rueckstand.md` liest kein Scheduler. Merkregel: Sagt ein Prüfbefund „das
  ändert `specs/`", dann nachsehen, welches offene Paket genau diese Stelle abschreibt.
- **2026-09-02, sechster Lauf, der teuerste Fund über mich selbst** — **Ich habe fünf Läufe
  lang notiert, welche Rolle in `BAUROLLEN` *fehlt*, und nie nachgesehen, welche eingetragene
  Rolle *leer läuft*.** `testentwickler` steht dort seit dem ersten Baulauf, hat einen
  Prüfer in `REVIEW` (`baulauf.py:62`), eine Rollendatei, ein Logbuch — und hatte bis heute
  kein einziges Paket. Gleichzeitig stand im Plan „der Kern hat keine baubare Aufgabe mehr".
  Beides zusammen war einen Lauf lang wahr, ohne dass es mir auffiel. **Merkregel: `BAUROLLEN`
  und `PRUEFROLLEN` einmal je Lauf ganz durchgehen und je Rolle fragen, ob sie ein offenes
  Paket hat.** Die Antwort steht in drei Sekunden im Trockenlauf.

## Offene Faehrten

- **Der Scheduler hat keine Vorfahrt.** `baulauf.py:257` nimmt `startbereit(...)[:4]`, und
  `pakete()` liest `sorted(ordner.glob("*.md"))` — also reine Dateinamen-Reihenfolge. Ein
  neu angelegtes Paket mit hoher Nummer kommt nicht dran, solange vier niedriger
  nummerierte `offen` stehen, und ein steckengebliebenes Paket (0015 lieferte zweimal
  nichts, 0009 vergass den Statuswechsel) belegt seinen Platz dauerhaft. **Vor dem Anlegen
  eines Pakets prüfen, ob es überhaupt einen Platz bekommen kann** — sonst schreibe ich für
  den übernächsten Lauf. Umplanen ist trotzdem falsch: ein Paket künstlich zu blockieren
  wäre eine Lüge im Statusfeld, rückwärts nummerieren verstösst gegen die Konvention.
  Melden, und wenn es nach dem nächsten Lauf steht, ist es eine Zeile im Runner.
- **Die Rolle, die von nichts abhängt, ist die Reserve gegen einen blockierten kritischen
  Pfad.** Als der Kern an 0008 hing und `werte`/`schritt` zu waren, war die brauchbare
  Arbeit das Vorratsverfahren (T43/T36): fünf Ganzzahlen, drei Steckplätze, kein `Zustand`,
  kein Zufall („wird nie gerundet und nie gezogen"), und Maß 2 und 3 stehen darauf.
  **Suchmuster für den nächsten Engpass: Welche Vorgabe rechnet mit Zahlen, die nirgends
  herkommen?** Die ist immer sofort baubar.
- **`BAUROLLEN` kennt weiter keinen `architekt` und keinen `spielentwerfer`** —
  `baulauf.py:49`, am 2026-09-02 zum vierten Mal nachgesehen. Solange das so ist, **lege
  ich keine Entwurfspakete an**; statt dessen Meldung in `rueckstand.md`. Jeden Lauf einmal
  nachsehen.
- **Zwei Werkzeuge fehlen dem Runner, immer dasselbe Muster:** ein TOML-Parser neben
  `uebersetzen()` und eine Hand, die die Rohdaten auf die Platte legt. **Prüffrage bei jedem
  Abnahmekriterium, das ich schreibe: Kann die Rolle den Nachweis überhaupt führen?** Kann
  sie es nicht, gehört das Werkzeug in den Runner — oder das Kriterium muss anders lauten.
- **„Schaden" in Gegenkraft 5 hat keine Rechenvorschrift** (`technik.md` Abschnitt 12).
  Kein Paket dafür — es gehört dem Spielentwerfer, und der läuft im Baulauf nicht. Es
  blockiert erst über `schritt`; dann ist es zu spät, die Frage zu stellen.
- **Grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. Meine Kriterien
  verlangen deshalb Werte aus unabhängiger Quelle; bei 0019 ist es die in `spiel.md`
  ausgeschriebene Artenfolge `1,2,3 | 4,5,1 | …`, bei 0020 die Klassenzählung aus
  `adressen.md`. Die Prüfer haben genau das benutzt und es hat gehalten.
- **Ein Kriterium „zeig, dass der Test rot wird" braucht so viele falsche Fassungen wie es
  Prüfungen hat.** Bei 0019 gesehen: Ein Gleichstandsbrecher nach *grösserer* Kennung
  besteht die Invariante trotzdem, weil jede Art wieder dreimal drankommt — nur die
  ausgeschriebene Artenfolge fängt ihn. Eine falsche Fassung hätte belegt, dass *eine* der
  beiden Prüfungen misst, und die andere ungedeckt gelassen.
