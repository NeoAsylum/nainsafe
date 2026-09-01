# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/geschaeftsfuehrer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-09-01 — Erster Lauf. Die Spezifikation von 0016 ist 270 kB; sie ganz zu lesen
  ist unmöglich und unnötig. Getragen hat dieser Weg: Arbeitspakete und Befund-
  Frontmatter ganz (klein und aktuell), `specs/` nur über Gliederung und Abschnitt
  „Offene Entwurfsfragen", dazu `agents/*.py` und die Commit-Botschaft der letzten
  Änderung. Die Wahrheit über den Zustand stand in den Skripten, nicht in den Dokumenten.
- 2026-09-01 — Wenn ein Gate übersprungen wurde, steht der Grund im Gate-Dokument, die
  *Nebenwirkung* aber nirgends. `gates/0016-g1.md` nennt die archivierte Bewertungskette;
  dass damit `wip()` das Vorhaben nicht mehr als `im_bau` zählt, stand in keiner Datei.
  Übersprungene Schritte lohnen den Blick auf das Skript, das den Status liest.
- 2026-09-01 — Die nützlichste Frage nach dem Engpass war nicht „was fehlt", sondern
  „welche Größe lesen die meisten Stellen". `fondsvermoegen(z)` hat fünf Leser, und damit
  war Paket 0002 ohne Abwägung der Engpass.

## Was nicht funktioniert

- 2026-09-01 — `cat`/`sed` über mehrere Dateien wird in diesem Harness abgelehnt; `Read`
  mit `offset`/`limit` und `grep` gehen. Kein Zeitverlust, wenn man gleich so anfängt.
- 2026-09-01 — `ops/portfolio.md` (2026-08-30) und `ops/kontingent.md` (2026-08-30) sind
  älter als die Umstellung auf 0016 und beschreiben eine Fabrik, die es nicht mehr gibt.
  Für den Stand eines Vorhabens sind sie unbrauchbar; nicht wieder dort anfangen.

## Offene Faehrten

- **Die zwei Entscheidungen aus `ops/plan.md` vom 2026-09-01 nachhalten**: Rücklaufgrenze
  im Baulauf (Empfehlung B, Grenze je Paket) und Auslöser für die 170-gegen-121-Lücke
  (Empfehlung: erster bestandener Rückvergleich). Beim nächsten Lauf prüfen, ob eine
  davon beantwortet ist — unbeantwortete Empfehlungen zweimal hintereinander unverändert
  hinzuschreiben wäre genau der Bericht, der jede Woche gleich aussieht.
- **Ob der Kernbauer in 0002 wirklich entschieden hat oder nur beschrieben.** Das Paket
  verlangt Code samt Einheit; fünf Runden Prosa gingen voraus. Erste Frage nächstes Mal:
  Gibt es `kern/bewertung.rs`, und rechnet ein Test einen Fall von Hand nach?
- **Leere Prüfausgaben.** Runde 5 hatte 0 Byte und fiel durch jede Zählung. Wenn das im
  Bau wieder vorkommt, ist es kein Einzelfall, sondern eine Lücke in `pruefung.py`.
