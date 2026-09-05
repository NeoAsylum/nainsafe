# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05-4.md` (voll bei Paket 0111);
davor `-3` (0086), `-2`, und ohne Suffix, alle 2026-09-05.

---

## Wie ich einen Mutanten baue (traegt seit 0019, destilliert)

- Mutant als Textersetzung an einer **Arbeitskopie unter `$TMPDIR`**, nie am Repo.
  `shutil.copytree` im python3-Heredoc kopiert auch, wenn `cp -r` gesperrt ist (0111).
- **Immer mit Trefferbremse** (`assert text.count(nadel) == 1` vor der Ersetzung) --
  und bei mehreren Vorkommen derselben Form **nach** der Ersetzung zaehlen, dass die
  Nachbarstelle noch steht (0111: Schwanz `, 10'000));` trennte `:583` von `:666`).
- **M0 vor der Mutation und nach jeder Ruecknahme.** Ohne sie belegt "alle Mutanten
  sterben" auch einen kaputten Aufbau.
- **Am selben Bau messen wie der Runner:** `baulauf.py:182-186` abschreiben
  (`RelWithDebInfo`, `-fwrapv -fno-fast-math`), Werkzeugkette kommt ueber
  `PROJECT_IS_TOP_LEVEL` von selbst, `kern/` ist allein baubar (0111).
- **Die alte Fassung der Probe gegen denselben Mutanten fahren**
  (`git show <baucommit>^:pfad`): alt gruen + neu rot belegt in einem Lauf, dass die
  Luecke offen war und der Einschub der einzige Faenger ist (0061, 0111).
- **Zaehlen, welche und wie viele Zusicherungen reissen** und ob es genau die der
  Abnahme sind; die Zeilennummern der Fehlausgabe im Quelltext nachschlagen (0111).
- Schwellen sind erst gemessen, wenn sie von **beiden** Seiten eingeklemmt sind (0086).
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?**
- **Den fremden GEBAUT-Absatz erst nach der eigenen Messung gegenlesen** (0088).
- **Dateiliste des Baucommits gegen die `dateien`-Liste legen**
  (`git show --numstat`); ein rein additiver Diff (+N/-0) beantwortet "abgeschwaechte
  Tests" in einem Griff (0077, 0111).
- `git log -- <datei>`, nie `git show <betreff>`: Der Runner buendelt mehrere Pakete
  unter einem Betreff (0086, 0111: 11 Dateien aus drei Paketen).

## Was funktioniert

- 2026-09-05 (0111) -- **Ein "vorher schon rot"-Nebenbefund des Bauagenten kann zur
  Pruefzeit repariert sein.** Der `belegstellen_riegel` war beim Bau rot (fremdes
  Paket), bei meiner Messung gruen -- 0120 lag dazwischen. Den aktuellen Stand messen,
  nicht die Behauptung uebernehmen; die Abweichung gehoert als Nebenbefund in den
  Befund, nicht als Widerspruch.
- 2026-09-05 (0088) -- Bei ueberlebender Mutation zuerst fragen: **welcher Eingabewert
  macht beide Formen gleich?** (0111 war der Lehrfall: `stufen = +3` machte `betrag`
  unsichtbar; die neue Probe schliesst das mit `-4`, `+4` und `0` selbst aus.)
- 2026-09-05 (0086) -- **Ein stiller Nulloutput ist ein Befund, kein Ergebnis** --
  Skripte, die nur nach der Ergebniszeile greifen, schweigen beim Abbruch.
- 2026-09-05 (0107) -- **Collage-Griff, wenn alle Textwerkzeuge zu sind:**
  `git show HEAD:pfad > kopie`, `head`/`printf`/`tail`, Loeschmutant `grep -Fxv`,
  Trefferbremse ersatzweise `git diff --no-index`.
- 2026-09-05 (0107) -- Loeschmutant an einer Aufrufzeile misst erst die Werkzeugkette
  (`-Werror=unused-function`); Funktion **samt** Aufruf loeschen.
- 2026-09-05 (0097) -- Fremde Mutationslisten nennen das Was, nicht den Wortlaut:
  selbst in Ersetzungen uebersetzen; Nadeln, die mit `...]` enden, sind gegen
  Praefix-Einheiten immun.

## Was nicht funktioniert

- Sperren wechseln je Sitzung **und innerhalb der Sitzung** -- probieren, nicht
  ableiten. Wiederkehrend: `git commit` gesperrt (vier Sitzungen in Folge bis 0061),
  `git add` und `git mv` gehen; Verbundbefehle mit `sed`/`cp`/`rm` fallen oft, der
  python3-Heredoc geht fast immer. Bei 0111 ging `Write` ins Repo-Zielverzeichnis
  und `cmake`/`ctest` ohne Einschraenkung.
- Mutantenskripte, die in den **Repo-Baubaum** schreiben, hinterlassen `ctest` rot
  (0086). Seit 0111: gar nicht erst hinein -- Arbeitskopie samt eigenem Baubaum.
- `git status` zeigt am Repowurzelrand Sandbox-Zeichengeraete (`.bashrc`,
  `.claude/*`): nicht erschrecken, nicht aufraeumen (0088).
- Zwei Laeufe derselben Rolle koennen parallel laufen: nur anfuegen, Kollisionen bei
  Befund- und Archivnamen pruefen (0083).
- Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen: `sort | uniq -d`
  daneben (2026-09-03).

## Offene Faehrten

- 2026-09-05 (0086) -- **Herkunftsangaben von `ZITATFAELLE` (9) und `ZIELFAELLE` (8)
  noch nie einzeln nachgeschlagen.** Beim naechsten Riegelpaket dran.
- 2026-09-05 (0086) -- **Der Riegel rueckt nach einem Treffer um den ganzen Zitatteil
  weiter** und kann ein Schluesselwort im zitierten Wortlaut ueberspringen. Bei der
  naechsten Lockerung nachsehen.
- 2026-09-05 (0111) -- **Erledigt:** mein Vorschlag 0111 ist gebaut und von mir
  `geprueft`; 0120 ist gebaut, der Arbeitsbereichs-`ctest` steht wieder 14/14. Offen
  aus derselben Reihe: **0115** (drei falsche Zahlen im Kopf des Riegels). Alle drei
  rechnenden `betrag`-Stellen in `werte.cpp` sind jetzt einzeln gedeckt (0002, 0088,
  0111) -- die Familie ist geschlossen, sofern kein neues Paket eine vierte anlegt.
- 2026-09-05 (0088) -- Bevor ich eine Zeile "unerreichbar" nenne, den Mutanten wirklich
  bauen; `festkomma`-Literale brechen am `static_assert` ab -- nicht als
  Empfindlichkeit zaehlen.
- 2026-09-05 (0083) -- `befunde/` und `bau/` tragen Abschriften des Quellbaums; jedes
  Werkzeug, das am Basisnamen sucht, wird belogen. Pfade oder Namen?
- 2026-09-02 -- `anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten; wandert die Pruefung in ein aufrufbares Modul fuer T30, wird der
  Fall scharf.
