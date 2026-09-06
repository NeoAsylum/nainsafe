# Logbuch: portfolio-manager

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Höchstens 12.000 Zeichen (`wc -c`).

---

## Was funktioniert

- 2026-08-29 — **Erst `anwalt.md` lesen, dann zählen — und nur die Frontmatter-Zeilen
  `entkraeftet/loesbar/teuer/unloesbar` zählen.** Der Anwalt hat das Urteil je Linse
  bereits gefällt; die fünf Angriffsdateien musste ich nicht öffnen. Nachlesen lohnt nur,
  wenn er eine Linse auf `loesbar` dreht — dort ist die Begründung die Entscheidung.
- 2026-08-30 — **`grep -rn "Portfolio-Manager" notizen/` ist der billigste Einstieg in die
  Betreibermeldungen.** Die Rollen adressieren mich wörtlich. Sie wissen, was falsch läuft;
  sie dürfen es nur nicht ändern. **Ergänzung 2026-09-06:** In der Bauphase trägt
  `grep -rn "Betreiber" notizen/` mehr — die Baurollen schreiben „Betreiber." als
  Einzelwort ans Ende einer Zeile, nicht meinen Rollennamen.
- 2026-08-30 — **Eine Lehre wird stärker, wenn zwei Logbücher sie unabhängig melden.** Der
  beste Filter gegen Einzelfälle, den ich habe — besser als die Zahl der betroffenen Ideen.
  **2026-09-06 bestätigt und verschärft:** Beide neuen Lehren dieses Laufs hatten drei
  unabhängige Quellen, und beide Male sagte jede Quelle etwas anderes über *dieselbe*
  Sache (grünes Testfeld / blockiertes Paket / „die eine Zahl"). **Drei Beschreibungen
  desselben Dings sind wertvoller als drei Meldungen desselben Satzes** — die erste Sorte
  belegt, die zweite hallt nur.
- 2026-09-06 — **In einem Lauf ohne Kandidaten liegt der ganze Ertrag in `lehren.md` und
  den Meldungen.** Gilt weiter, aber die Quellen sind andere: nicht mehr `ideas/` und die
  Marktprofile, sondern `ops/auslastung.md`, `ops/kontingent.md`, der jüngste
  `befunde/uebersetzung-<datum>.md` und die Logbücher der drei Rollen mit Überblick
  (Geschäftsführer, Projektmanager, Bruchtester). Das reichte für den ganzen Lauf.
- 2026-09-06 — **Der Übersetzungsbericht ist die einzige Aussage über den Bau, die kein
  Modell geschrieben hat.** Runner-erzeugt, nennt jedes Ziel und jeden Test. Ich lese ihn
  vor jedem Logbuch, nicht danach.
- 2026-09-06 — **`Write` auf meine eigenen Dateien geht, obwohl die Werkzeugliste nur
  `Edit(...)` nennt.** Die Edit-Pfadregel deckt alle dateiändernden Werkzeuge ab
  (`lauf.py:69-73` sagt es ausdrücklich). Das erspart bei einem Umbau von `lehren.md` ein
  Dutzend stückweiser `Edit` über je 30 Zeilen, die alle exakt treffen müssten.

## Was nicht funktioniert

- 2026-08-29 — **`agents/repo.py` hat keinen CLI-Einstieg**, nur importierbare Funktionen.
  Frontmatter direkt greppen.
- 2026-09-06 — **`sqlite3 state.db` ist mir verwehrt** (zweimal versucht, „don't ask
  mode"), ebenso `sed -n`. **Nicht erneut versuchen.** `ops/auslastung.md` und
  `ops/kontingent.md` beantworten jede Frage, die ich an das Journal hätte — und die
  Hausregel sagt ohnehin: fertige Datei lesen, nicht selbst zählen. Ein `Read` mit
  `offset`/`limit` ersetzt `sed -n` vollständig.
- 2026-08-30, **2026-09-06 gelöst** — `lehren.md` wuchs schneller, als die 60-Tage-Prüfung
  sie leert: 9.608 → 13.394 → **42.578** Zeichen in einer Woche. Die 60-Tage-Regel greift
  nicht, wenn die Fabrik erst zehn Tage alt ist — sie ist das falsche Maß. **Das richtige
  Maß ist der Adressat:** Eine Lehre, die an eine abgeschaltete Rolle gerichtet ist, wird
  von allen gelesen und hilft keinem. Zwei Drittel der Datei waren so. Auf 25.645 gekürzt.

## Wie ich kürze, ohne zu löschen

- 2026-09-06 — **Ich darf nicht nach `notizen/archiv/` schreiben, keine Rolle darf das** —
  nachgemessen mit `grep -L "notizen/archiv" agents/rollen/*.md`: 31 von 31 Treffern. Die
  Hausregel schreibt genau diese Rotation vor. Fünf fremde Logbücher melden dieselbe Wand.
- 2026-09-06 — **Der Ersatzweg ist der Zeiger auf den Commit**, und Architekt und
  Geschäftsführer benutzen ihn schon: `git log -1 --format=%H -- <datei>` vor der Änderung,
  Hash in die Kopfzeile der neuen Fassung („Volltext in `git show <hash>:<datei>`").
  Hausregel 3 ist damit gewahrt — die Datei ist versioniert, eine gestrichene Passage ist
  einen Aufruf entfernt. **Dazu den tragenden Satz jeder gestrichenen Lehre als Einzeiler
  behalten.** Elf Zeilen ersetzten 17.000 Zeichen Suchphase.

## Prüfgriffe, die diesen Lauf entschieden haben

- 2026-09-06 — **Eine Lehre, die eine Rolle als Sicherheitsnetz nennt, gegen
  `konzeptlauf.py:STUFEN` und `agents/rollen/archiv/` halten.** Teuerster Fund des Laufs:
  Meine eigene Lehre vom 2026-08-31 wies die 170-gegen-121-Lücke dem Ökonomen und dem
  Vertriebsplaner zu „und Gate 2 ist die Stelle, an der es sichtbar wird" — beide Rollen und
  das Gate wurden **am selben Tag** archiviert. Sechs Tage lang stand ein Sicherheitsnetz
  in der gemeinsamen Datei, das es nicht gab. *Bei jeder Lehre mit „Rolle X wird das tun"
  prüfen, ob Rolle X noch läuft.*
- 2026-09-06 — **Eine Regel gegen ihre Ausführbarkeit prüfen kostet einen Aufruf:**
  `grep -L "<pfad>" agents/rollen/*.md`. Steht eine Pflicht in `CLAUDE.md` und in keiner
  Werkzeugliste, ist sie keine Regel, sondern eine Reibungsquelle. Das ist derselbe
  Fehlertyp, den der Betreiber „eine Regel an einer Stelle, die der Ablauf nicht erreicht"
  nennt — ich kann ihn von meiner Seite billig finden.
- 2026-09-06 — **`git ls-files <ordner> | wc -l` gegen `ls <ordner> | wc -l`** sagt, ob
  geschriebene Dateien auch in der Historie sind. 103 gegen 124: **21 archivierte Logbücher
  liegen nur im Arbeitsbaum.** Ursache ist der Commit-Pfadfilter (`lauf.py:470`), der nur
  die Schreibpfade der Rolle committet. Ein Lauf kann erfolgreich schreiben und trotzdem
  nichts hinterlassen.
- 2026-09-06 — **Die Schlange nach Thema zählen, nicht nach Status.**
  `ls aufgaben/ | grep -c "belegstell\|riegel\|zitat"` — 41 von 176. Der Status sagt, ob es
  vorangeht; das Thema sagt, ob es das Richtige ist. **Und die Vorzahl mitnennen:** Der
  Geschäftsführer hatte 21 von 77 gemessen und daraus eine Beschleunigung gelesen; es ist
  ein konstantes Viertel. *Ein Anteil braucht zwei Messungen, sonst ist er eine Stimmung.*

## Offene Fährten

- 2026-09-06 — **Eingefroren, solange `FOKUS` gesetzt ist** (nicht erledigt, nur ohne
  Gegenstand): ob Score-Summen etwas taugen; was mit einer `widerlegt`-Idee geschieht, wenn
  ihr Widerlegungsgrund veraltet; das Promille aus G7. Alle drei betreffen die Suchphase.
  **Wieder aufnehmen, sobald `FOKUS = None` steht** — vorher kosten sie nur Platz.
- 2026-09-06 — **Zu prüfen im nächsten Lauf: Hat der Betreiber `ops/plan.md` gefüllt?** Der
  Projektmanager meldet die leere Vorrangliste zum zwölften Mal. Ist sie dann immer noch
  leer, ist es keine Meldung mehr, sondern die Frage, ob der Vorrang überhaupt vom
  Betreiber kommen soll — und die gehört als einziger Punkt in die nächste Fassung.
- 2026-09-06 — **Zu prüfen: steht die eine Zahl noch auf `0 von 310`?** Sie ist der einzige
  Fortschrittsmaßstab des Vorhabens, der nicht aus einem Modell stammt. Der Griff:
  `notizen/geschaeftsfuehrer.md` nach „die eine Zahl", dazu `wc -c` auf `kern/src/schritt.cpp`.
- 2026-09-06 — **Ich habe die Woche nie am Kalender gemessen, nur an Läufen.** Der
  Wochenlauf erzeugt `ops/auslastung.md` und `ops/kontingent.md` um 05:00; beide Dateien
  waren zu Beginn dieses Laufs vier Stunden alt und passten zusammen. Wenn sie das einmal
  nicht tun, ist die jüngere die richtige — nicht die freundlichere.
