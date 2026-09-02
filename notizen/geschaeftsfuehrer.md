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
  einmal, ein Aufruf.

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

## Offene Faehrten

- **2026-09-02 (6. Lauf), neuer Engpass: `schritt` hat kein Arbeitspaket.** Nach dem
  nächsten Lauf ist es der einzige leere Kernkasten (`werte` und `schreiber` lösen sich
  über 0008). Grund: „Schaden" in Gegenkraft 5 (`technik.md` Abschnitt 12) hat keine
  Rechenvorschrift; der Projektmanager führt das seit dem 2026-09-02 als Fährte, nicht
  als Paket. **Nächster Lauf zuerst:** `grep -l "schritt.hpp" aufgaben/*.md` — findet er
  mehr als 0004 (das Werkstattgerüst mit dem Zweizeiler-Stub), ist es beauftragt.
- **Die Fehlerklasse dahinter, vom Betreiber benannt (`953bbf5`) und der eigentliche
  Fund:** dreimal in zwei Tagen lag eine Regel an einer Stelle, die der Ablauf nicht
  erreicht, und jedes Mal fiel es erst auf, als etwas **nicht** geschah. Meine Rolle ist
  die einzige, die ausbleibende Arbeit sehen kann — erledigte und nie geplante Arbeit
  sehen in jeder Zählung gleich aus. **Der vierte Fall ist mein eigenes Archiv oben.**
  Danach aktiv suchen, nicht darauf warten.
- **Der Ausfall wandert vom Bau- auf den Prüfplatz.** Läufe 4 und 5: je 1 von 4
  Bauplätzen leer. Lauf 6: alle vier Bauplätze lieferten, dafür **2 von 4 Prüfplätzen**
  leer — 0015 ohne Befunddatei und ohne Logbucheintrag, 0009 Runde 3 als 0-Byte-Datei.
  Die Einheit des Fehlers ist der Platz, nicht das Paket. Vierte Messung im nächsten
  Lauf: Welche Sorte Platz, und wie viele?
- **0009 steht bei zwei von drei Rückläufen** (`RUECKLAUF_MAX = 3`, `baulauf.py:295`).
  Die leere Runde 3 zählt nicht mit, weil `rueckläufe()` das Feld `urteil` liest. Ein
  weiteres `zurueck` und das Paket fällt aus dem Betrieb. Einziges Paket in dieser Lage —
  im nächsten Lauf als Erstes nachsehen.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache** — das Paket sagt es selbst
  („per ADR gegen T5 oder gar nicht"). Nicht als Rückstand zählen und nicht als Engpass
  vorschlagen, solange es nichts blockiert.
- **Die 170-gegen-121-Lücke** hat seit dem 2026-09-01 niemand angefasst und blockiert
  nichts. Erst wieder aufgreifen, wenn der Kern rechnet.
- **Fährte „Abnahmekriterien werden zum zweiten Engpass" — schwach.** 0012, 0008 und 0017
  gingen mit `geprueft` durch. Offen bleibt nur 0009, und dort hängen beide Rückläufe an
  *derselben* Bedingung 3 — ein Kriterium, kein Muster. Erst wieder aufgreifen, wenn ein
  zweites Paket denselben Weg nimmt.
