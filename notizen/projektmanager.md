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
- 2026-09-01, **am 2026-09-02 halb widerlegt** — Ich schrieb: „Abnahmekriterien mit
  ‚übersetzt fehlerfrei' sind wertlos, weil keine Rolle `Bash` hat." Die Prämisse über
  die Rollen stimmt weiter, der Schluss nicht: **`baulauf.py` übersetzt selbst** und legt
  das Urteil nach `befunde/uebersetzung-<datum>.md`. Ein Kriterium darf sich darauf
  stützen — `static_assert`, Probe mit ausgeschriebenem Erwartungswert, `ctest`-Eintrag.
  Die Lehre, die bleibt und die wichtigere ist: **grün heisst „die Zahlen passen
  zueinander", nicht „die Zahlen sind richtig".** Ein Erwartungswert aus dem eigenen Code
  ist eine Wiederholung, kein Nachweis; deshalb verlangen meine Kriterien für Zufall und
  Prüfsumme Werte aus unabhängiger Quelle mit URL und Abrufdatum.
- 2026-09-02 — **Nicht vom Runner behaupten lassen, was er tut: nachsehen.** Ich hätte
  die obige Lehre einen Lauf früher korrigieren können — `befunde/uebersetzung-*.md` lag
  da. Wer eine eigene alte Lehre nicht gegen den Ablagestand hält, plant gegen eine Welt,
  die es nicht mehr gibt. `ls befunde/` kostet einen Aufruf.

- 2026-09-02 — **Der Statusnachzug ist meine teuerste Unterlassung, nicht mein
  Nebenjob.** Fünf Pakete standen falsch, weil drei Bauagenten den Status vergessen
  hatten und ich beim letzten Lauf gar nicht dazu kam. Folge: Der erste Code des
  Vorhabens wäre ungeprüft geblieben (Review verlangt `gebaut`), und der kritische Pfad
  hätte zwei Läufe verloren. **Erst nachziehen, dann alles andere** — die Reihenfolge in
  meinem Auftrag ist nicht dekorativ. Und: `--trocken` nach jeder Statusänderung, ich
  hatte zwei Frontmatter-Zeilen vergessen und nur der Trockenlauf hat es gezeigt.
- 2026-09-02 — **Ein Stackwechsel per ADR macht jedes Paket falsch, ohne dass eines rot
  wird.** ADR 0011 (Rust → C++) hat fünf Pakete im Feld `dateien` auf Dateien zeigen
  lassen, die es nie geben wird; der Bauagent baute richtig gegen den ADR und damit
  gegen sein eigenes Paket. Ein Prüfer, der „gegen diese Liste und gegen nichts sonst"
  urteilt, hätte an einem Dateinamen zurückgewiesen — ein Rücklauf, den niemand
  verursacht hat. **Nach jedem ADR, der den Stack ändert, alle Pakete durchgehen**, bevor
  der nächste Baulauf startet. Kostet 20 Minuten, spart drei Rückläufe.
- 2026-09-02 — **In C++ ist der Kollisionsschnitt schärfer als in Rust.** Ein Modul sind
  drei eigene Dateien (Kopf, Quelle, Probe), und `file(GLOB … CONFIGURE_DEPENDS)` in
  `kern/CMakeLists.txt` sammelt sie ein — es gibt keine gemeinsame Modulliste wie
  `lib.rs`, die jedes Paket anfassen müsste. Damit laufen drei Kernpakete gleichzeitig
  ohne jede Platzhalterakrobatik.
- 2026-09-02, abends — **Beim Rücklauf gehört `dateien` auf den Rücklauf verengt, nicht
  auf die Baugeschichte.** 0004 führte fünfzehn Dateien, darunter sechs
  Modulplatzhalter; wiedereröffnet hätte es 0008 und 0012 gesperrt — für vier Zeilen
  Prosa. Das Feld ist Kollisionsvermeidung und keine Dokumentation. Die Existenzprüfung
  über die volle Liste habe ich dafür in die Abnahmebedingung ausgeschrieben; sonst
  verschwindet sie mit dem Feld.
- 2026-09-02, abends — **Ein Paket zu blockieren ist billiger, als es zurückzuholen.**
  0002 (`kern::werte`) auf `blockiert`, weil T5 Klasse 2 laufende und konstante Preise
  mischt und die Auflösung T50 berühren kann — die Vorgabe, die das Paket „Zeichen für
  Zeichen" abschreiben soll. Gebaut hätte es `fondsvermoegen` mit fünf Lesern, und die
  Korrektur wäre Nacharbeit am teuersten Modul. **Der Status ist mein einziges
  Vorwärtswerkzeug gegen eine Vorgabe, die gerade repariert wird**; die Prosa in
  `rueckstand.md` liest kein Scheduler. Merkregel: Sagt ein Prüfbefund „das ändert
  `specs/`", dann nachsehen, welches offene Paket genau diese Stelle abschreibt.

## Offene Faehrten
- **Der Kern nach 0008: entschieden am 2026-09-02.** Meine offene Frage `werte` (0002)
  oder `schreiber` (T18/T38/T39) hat sich selbst beantwortet — 0002 ist blockiert, also
  kam 0016 `kern::schreiber`. Entschieden hat die Entwurfsfrage, nicht meine Abwägung.
  **Lehre für die nächste Weggabelung:** Zuerst prüfen, welcher Zweig an einer offenen
  `specs/`-Frage hängt; das entscheidet öfter als der Aufwand.
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
- **Rücklaufzähler** (`RUECKLAUF_MAX = 3`): Stand 2026-09-02 abends je 1 bei 0004, 0006,
  0009, sonst 0. Ich führe ihn im Paket weiter; er kostet nichts und macht die Zahl
  lesbar, ohne Befunddateien zu zählen.
- **`BAUROLLEN` kennt weiter keinen `architekt` und keinen `spielentwerfer`** — am
  2026-09-02 zum zweiten Mal in `baulauf.py:49` nachgesehen, unverändert. Solange das so
  ist, **lege ich keine Entwurfspakete mehr an**; statt dessen Meldung in
  `rueckstand.md`. Jeden Lauf einmal nachsehen: Wird die Zeile gezogen, sind fünf
  Entwurfsfragen auf einmal einplanbar.
- **Ein Prüfbefund kann ein Paket erzeugen, ohne ein Rücklauf zu sein.** Die Befunde zu
  0005 und der zweite zu 0007 trugen `urteil: geprueft` und trotzdem echte Arbeit; daraus
  wurden 0014 und 0015. **Nicht nur auf `zurueck` schauen** — Befunde eines bestandenen
  Pakets sind die beste Paketquelle, weil sie schon gemessen sind.
- **Die Rohdaten sind keine Paketfrage, sondern eine Runner-Frage** — korrigiert am
  2026-09-02. Ich hatte sie als „nächstes grosses Datenpaket" geführt; kein Bauagent kann
  eine Rohdatei auf die Platte legen (`Edit` schreibt Text, `WebFetch` liefert Text, eine
  Shell hat keine Baurolle). Steht in `rueckstand.md`. Kein Gate — kein Geld, keine
  Rechtsfolge, nur eine Hand am Runner.
