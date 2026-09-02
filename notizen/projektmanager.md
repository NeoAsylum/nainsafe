# Logbuch: projektmanager

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/projektmanager-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-09-01, dreimal bestätigt — **`python3 agents/baulauf.py <venture> --trocken` nach
  jeder Statusänderung.** Es zeigt in drei Sekunden, welche vier Pakete der Scheduler
  wirklich zieht, und prüft nebenbei mein Frontmatter: `haengt_an` und `dateien` werden von
  `lauf.py:frontmatter` geparst, ein Tippfehler macht ein Paket lautlos startbereit oder
  lautlos unsichtbar. Die Kopfzeile (`n offen, m fertig, k blockiert`) muss die Zahl aller
  Paketdateien ergeben — geht die Summe nicht auf, hat ein Frontmatter einen Fehler.
- 2026-09-01 — **Die 242 kB Spezifikation nicht lesen, sondern indizieren.**
  `grep '^#{1,3} '` auf beide Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md` — eine
  Liste von 51 nummerierten Vorgaben mit Zeilennummer. `technik.md` Abschnitt 13 heisst
  „Hinweis für den Projektmanager" und nennt Kollisionsschnitt und Reihenfolge; **dort
  anfangen**, nicht vorn.
- 2026-09-02 — **In C++ ist der Kollisionsschnitt der Kastenschnitt, und er ist schärfer
  als in Rust.** Ein Modul sind drei eigene Dateien (Kopf, Quelle, Probe), und
  `file(GLOB … CONFIGURE_DEPENDS)` in `kern/CMakeLists.txt` sammelt sie ein — es gibt keine
  gemeinsame Modulliste wie `lib.rs`, die jedes Paket anfassen müsste. Drei Kernpakete
  laufen gleichzeitig ohne jede Platzhalterakrobatik.
- 2026-09-02, abends — **Ein Prüfbefund mit `geprueft` ist die bessere Paketquelle als
  einer mit `zurueck`.** Diese Nacht: drei `geprueft`, und zwei davon trugen echte Arbeit
  (0006 → Umrechnungsfaktoren, 0014 → drei Befunde an mich), während der eine `zurueck` nur
  fünf Zeilen kostete. Der Grund ist strukturell: Was innerhalb des Kriteriums liegt, wird
  Rücklauf; was daneben liegt, hat sonst niemanden. **Also jeden Befund ganz lesen, auch
  den bestandenen** — die Adresszeile „an den Projektmanager" steht regelmässig erst hinter
  der Abnahmetabelle.
- 2026-09-02, abends — **Geschärfte Vorgaben gehören in das Paket, das die Spalte ohnehin
  baut, nicht in ein neues.** Der Nebenbefund zu 0006 (zwei Reihen ohne Umrechnungsfaktor)
  wurde kein Paket, sondern zwei Absätze in 0017, wo die Umrechnungsspalte entsteht — 0017
  war nie gebaut, also ist das keine Kriterienerhöhung, sondern ein schärferes Kriterium
  vor dem ersten Versuch. Ein eigenes Paket hätte dieselbe Datei ein zweites Mal
  aufgemacht. **Prüffrage: Gibt es ein offenes Paket, das diese Datei ohnehin anfasst?**

## Was nicht funktioniert

- 2026-09-01 — **`cat` über mehrere Dateien wird in diesem Harness abgelehnt.** `Read`,
  `Grep`, `ls`, `head` und `wc` gehen. Gleich so anfangen.
- 2026-09-02, abends — **Zwei `Edit` auf dieselbe Datei in einem Aufrufblock werden
  abgelehnt, einzeln gehen beide durch.** Und allgemeiner, teurer gelernt: **Die
  Schreibsperre dieses Harness ist unstet.** Acht Ablehnungen in Folge, danach ging
  dieselbe Änderung wortgleich durch. Eine Ablehnung ist kein Urteil über den Inhalt —
  **wiederholen, nicht umschreiben und nicht aufgeben.** Ich hätte den Lauf beinahe mit
  vier nachgezogenen Statuszeilen und ohne die Rücklauftexte beendet; das wäre der teuerste
  Halbzustand überhaupt gewesen (siehe die Merkregel zu 0009 unten).
- 2026-09-02, abends — **Der Commit-Betreff belegt nicht, wer gebaut hat. Die Datei belegt
  es.** `fc61eaf` heisst „kernbauer: 0008-kern-zustand-310-felder" und enthält
  `parameter.toml` — die Arbeit eines gleichzeitig laufenden Datenbauers. Der Baulauf
  committet nicht paketweise, sondern nimmt mit, was im Baum liegt (der Kernbauer notiert
  dasselbe Muster zweimal). Hätte ich 0008 danach auf `gebaut` gezogen, wäre ein
  2-Zeilen-Platzhalter in den Review gegangen. **Vor jedem Nachzug in die Zieldatei sehen**
  — `wc -l` auf die Dateien aus `dateien` kostet einen Aufruf und unterscheidet Platzhalter
  von Arbeit.
- 2026-09-02 — **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein Nebenjob.**
  Fünf Pakete standen einmal falsch, weil Bauagenten den Status vergessen hatten und ich
  nicht dazu kam. Folge wäre gewesen: erster Code ungeprüft (Review verlangt `gebaut`),
  kritischer Pfad zwei Läufe verloren. **Erst nachziehen, dann alles andere.**
- 2026-09-02 — **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot
  wird.** ADR 0011 (Rust → C++) liess fünf Pakete auf Dateien zeigen, die es nie geben
  wird. **Nach jedem ADR, der den Stack ändert, alle Pakete durchgehen.**
- 2026-09-02, abends — **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt, nicht auf
  die Baugeschichte.** 0004 führte fünfzehn Dateien; wiedereröffnet hätte es 0008 und 0012
  gesperrt — für vier Zeilen Prosa. Die Existenzprüfung über die volle Liste gehört dafür
  ausgeschrieben in die Abnahmebedingung, sonst verschwindet sie mit dem Feld.
- 2026-09-02, abends, **Korrektur einer eigenen Entscheidung** — Ich hatte bei 0003
  geschrieben, die Dateiendung `.rs` ziehe ich nicht nach: „eine Datei, die es nicht geben
  soll, braucht keinen richtigen Namen." Falsch begründet. `dateien` ist kein Name, sondern
  die Kollisionsvermeidung; ein Feld, das eine unmögliche Datei schützt und die mögliche
  nicht, **sieht wie Schutz aus und ist keiner**. Auch bei `blockiert` nachziehen — es
  kostet eine Zeile und der Fehler fällt erst beim Entblocken auf.
- 2026-09-02, abends — **Ein Paket zu blockieren ist billiger, als es zurückzuholen.** 0002
  (`kern::werte`) steht auf `blockiert`, weil T5 Klasse 2 laufende und konstante Preise
  mischt. Gebaut hätte es `fondsvermoegen` mit fünf Lesern. **Der Status ist mein einziges
  Vorwärtswerkzeug gegen eine Vorgabe, die gerade repariert wird**; die Prosa in
  `rueckstand.md` liest kein Scheduler. Merkregel: Sagt ein Prüfbefund „das ändert
  `specs/`", dann nachsehen, welches offene Paket genau diese Stelle abschreibt.

## Offene Faehrten

- **0009 steht bei Rücklauf 2 von `RUECKLAUF_MAX = 3`.** Der nächste `zurueck` macht es
  `FESTGEFAHREN`, und dann ist mein Abnahmekriterium zu prüfen, nicht die Arbeit. Ich habe
  den Satz ins Paket geschrieben. **Merkregel für den nächsten Lauf:** Wer ein Paket auf
  `offen` zurücksetzt, schreibt im selben Zug hinein, *was* zu ändern ist — der Bauagent
  liest das Paket, nicht den Befund. Ein `offen` ohne Rücklauftext ist eine Falle, die
  einen Lauf kostet und den Zähler weiterdreht.
- **Der Kern hängt an 0008, und 0008 ist zweimal eingeplant und nicht gebaut worden.**
  Fünf von sechs Kernpaketen warten mittelbar darauf. Passiert es ein drittes Mal, liegt
  die Ursache im Runner, nicht im Rückstand — dann melden statt umplanen.
- **`BAUROLLEN` kennt weiter keinen `architekt` und keinen `spielentwerfer`** —
  `baulauf.py:49`, am 2026-09-02 zum dritten Mal nachgesehen, unverändert. Solange das so
  ist, **lege ich keine Entwurfspakete an**; statt dessen Meldung in `rueckstand.md`.
  Inzwischen hängen sechs Sachen daran. Jeden Lauf einmal nachsehen.
- **Zwei Werkzeuge fehlen dem Runner, und es ist immer dasselbe Muster** (Lehre vom
  2026-09-01): ein TOML-Parser (Abnahme 4 von 0009 war in zwei Runden nicht maschinell
  belegbar) und eine Hand, die die Rohdaten auf die Platte legt. Beides steht in
  `rueckstand.md`. **Prüffrage bei jedem Abnahmekriterium, das ich schreibe: Kann die Rolle
  den Nachweis überhaupt führen?** Kann sie es nicht, gehört das Werkzeug in den Runner —
  oder das Kriterium muss anders lauten.
- **„Schaden" in Gegenkraft 5 hat keine Rechenvorschrift** (`technik.md` Abschnitt 12).
  Kein Paket dafür — es gehört dem Spielentwerfer, und der läuft im Baulauf nicht. Es
  blockiert erst über `schritt`, also nach 0016; dann ist es zu spät, die Frage zu stellen.
- **Grün heisst „die Zahlen passen zueinander", nicht „die Zahlen sind richtig".** Ein
  Erwartungswert aus dem eigenen Code ist eine Wiederholung, kein Nachweis. Meine Kriterien
  für Zufall und Prüfsumme verlangen deshalb Werte aus unabhängiger Quelle mit URL und
  Abrufdatum; die Prüfer haben genau das benutzt und es hat gehalten.
