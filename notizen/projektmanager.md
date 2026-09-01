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

- 2026-09-01 — **`python3 agents/baulauf.py <venture> --trocken` nach dem Anlegen der
  Pakete.** Es zeigt in drei Sekunden, welche vier Pakete der Scheduler wirklich zieht,
  und prüft nebenbei mein Frontmatter — `haengt_an` und `dateien` werden von
  `lauf.py:frontmatter` geparst, ein Tippfehler dort macht ein Paket lautlos startbereit
  oder lautlos unsichtbar. Erster Lauf: vier gezogen, genau die geplanten.
- 2026-09-01 — **Die 242 kB Spezifikation nicht lesen, sondern indizieren.**
  `grep '^#{1,3} '` auf beide Dokumente, dann `grep '^\*\*T\d+'` auf `technik.md` — das
  ergibt eine Liste von 51 nummerierten Vorgaben mit Zeilennummer. Danach liest man
  gezielt fünf Abschnitte statt eines Dokuments. `technik.md` Abschnitt 13 heisst
  „Hinweis für den Projektmanager" und nennt Kollisionsschnitt, Reihenfolge und die zwei
  vorzuziehenden Pakete; **dort anfangen**, nicht vorn.
- 2026-09-01 — **Der Kollisionsschnitt ist der Kastenschnitt.** T13 sagt es selbst. Ein
  Paket = eine Datei = ein Modul trägt weit; die einzige Stelle, an der es reisst, ist
  `lib.rs`, weil jedes Modul dort eine Zeile braucht. Gelöst über Platzhalterdateien:
  Das Gerüstpaket legt alle Moduldateien mit einer Kommentarzeile an, jedes spätere
  Paket überschreibt genau seine eine. Kein Paket fasst `lib.rs` zweimal an, und weil
  `startbereit` nur `offen` zählt, blockiert das fertige Gerüstpaket später niemanden.

## Was nicht funktioniert

- 2026-09-01 — **`cat` über mehrere Dateien wird in diesem Harness abgelehnt.** `Read`
  und `Grep` gehen, `ls` auch. Gleich so anfangen. (Steht auch im Logbuch des
  Geschäftsführers — offenbar eine Eigenschaft des Harness, nicht der Rolle.)
- 2026-09-01 — **Abnahmekriterien mit „übersetzt fehlerfrei" oder „Tests laufen grün"
  sind in dieser Fabrik wertlos.** Ich habe alle 31 Rollendateien nach `Bash` durchsucht:
  **keine einzige hat es**, und `lauf.py:NIE` sperrt es zusätzlich. Niemand kann `cargo`
  aufrufen — weder der Bauagent noch der Prüfer. Ein Kriterium, das ein Prüfer nicht
  nachvollziehen kann, erzeugt entweder eine Behauptung oder einen ewigen Rücklauf.
  Jedes Kriterium muss mit `Read`, `Grep` und Kopfrechnen prüfbar sein. Glücklicher
  Zufall: Der Architekt hat vier mechanische Nachweise genau in dieser Form gebaut
  (T4, T13, T48, T50), ohne den Grund zu kennen.

## Offene Faehrten

- **Ein Übersetzungslauf im Nachtlauf.** Er kostet null Tokens, wäre ein Skript neben
  `auslastung.py`, und ohne ihn baut die Fabrik wochenlang auf ungeprüftem Rust. In
  `rueckstand.md` an den Geschäftsführer gemeldet. Beim nächsten Lauf nachsehen, ob es
  in `ops/plan.md` angekommen ist — zweimal unverändert melden wäre der Bericht, der
  jede Woche gleich aussieht.
- **„Schaden" in Gegenkraft 5 hat keine Rechenvorschrift** (`technik.md` Abschnitt 12,
  Beobachtung 3). Ich habe dafür bewusst **kein** Paket angelegt: Es gehört dem
  Spielentwerfer, und der läuft im Baulauf nicht mehr. Es blockiert erst in einigen
  Wochen — aber wenn der Weltschritt an die Reihe kommt, ist es zu spät, die Frage dann
  erst zu stellen. Vorher aufwerfen.
- **0003 steht auf `blockiert`, weil Paket und T5 sich widersprechen** (Wrappertypen
  gegen „der Typ ist überall `i64`"). Ich habe es nicht aufgelöst — Entwurf ist nicht
  meine Rolle. Nachhalten, ob der Betreiber einen ADR will oder es liegen lässt.
- **Zwei Pakete waren überholt, bevor ein Agent sie angefasst hat** (0002 und 0003,
  geschrieben zwischen zwei Entwurfsfassungen). Lehre daraus: **Vor jedem Nachziehen die
  `git log`-Reihenfolge lesen** — hier lief nach der Prüfung, die die Pakete erzeugte,
  noch Spielentwerfer und Architekt, und die haben beide Befunde behoben. Ein Paket, das
  eine offene Frage zitiert, ist nur so aktuell wie die Fassung, gegen die es geschrieben
  wurde.
- **Rücklaufzähler.** Ich führe ihn ab jetzt in jedem Paket unter *Rückläufe* mit,
  damit die Empfehlung B aus `ops/plan.md` (blockiert nach dem zweiten `zurueck`) eine
  Zahl vorfindet, falls sie entschieden wird. Beim nächsten Lauf: Zähler aus den
  Befunden nachziehen, bevor neue Pakete entstehen.
