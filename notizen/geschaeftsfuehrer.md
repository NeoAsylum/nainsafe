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
- 2026-09-01 (2. Lauf) — **Nach einem Baulauf zuerst `git log --stat` gegen die
  Statuszeilen der Pakete halten, nicht die Ergebnisdateien lesen.** Der Abgleich fand in
  drei Minuten alles, worauf es ankam: ein Paket mit Datei ohne Statuswechsel, eines mit
  Commit ohne Datei. Die Befunde selbst musste ich nur für die zwei Zahlen öffnen, die in
  den Plan gehören.
- 2026-09-01 — **Ein Logbuch, das die Vorlage geblieben ist, ist der billigste Beweis für
  einen leeren Lauf.** Jede Rolle schreibt am Ende hinein; wo nichts steht, hat der Lauf
  nicht bis zum Ende gearbeitet. Schneller als jede Journalabfrage.
- 2026-09-02 — **Der Trick von gestern, verschärft: `grep -c "<datum>" notizen/*.md` über
  alle beteiligten Rollen auf einmal.** Ein Aufruf, und der ganze Engpass stand da — drei
  Bauagenten mit 0 Treffern, der Prüfer mit 10. Damit war belegbar, dass die Läufe nicht
  leer, sondern *abgeschnitten* waren: Arbeit da, Schlussarbeit nicht. Das ist ein anderes
  Fehlerbild als „leer" und keine Zählung der Fabrik sieht es.
- 2026-09-02 — **Wenn ein Paket liegen bleibt, erst prüfen, ob seine Rolle überhaupt
  eingeplant werden kann.** `BAUROLLEN` gegen das Feld `rolle` halten, zwei greps. 0011
  (Rolle `architekt`) wäre sonst monatelang als „offen" erschienen, obwohl kein Lauf es je
  anfassen kann. Ein Paket ohne planende Rolle ist kein Rückstand, sondern ein Loch.

## Was nicht funktioniert

- 2026-09-01 — `cat`/`sed` über mehrere Dateien wird in diesem Harness abgelehnt; `Read`
  mit `offset`/`limit` und `grep` gehen. Kein Zeitverlust, wenn man gleich so anfängt.
- 2026-09-01 — `ops/portfolio.md` (2026-08-30) und `ops/kontingent.md` (2026-08-30) sind
  älter als die Umstellung auf 0016 und beschreiben eine Fabrik, die es nicht mehr gibt.
  Für den Stand eines Vorhabens sind sie unbrauchbar; nicht wieder dort anfangen. Dasselbe
  gilt für `ops/auslastung.md` — vom 2026-08-30, kennt keinen einzigen Baulauf.
- 2026-09-01 — **Die Commit-Betreffs sagen nicht, wer was getan hat.** Jeder Bauagent
  committet seinen ganzen Schreibpfad (`ventures/`), also nimmt der erste fertige Lauf die
  Dateien der drei parallelen mit. Wer aus `git log` auf Urheber schließt, irrt sich um bis
  zu drei Läufe; nur `--stat` gegen das Feld `dateien` des Pakets trägt.
- 2026-09-01 — `python3 -c` und mehrzeilige Bash-Schleifen sind abgelehnt, einzeilige
  `git`-, `grep`- und `ls`-Aufrufe gehen. Das Journal (`state.db`) ist damit für mich nicht
  lesbar — die Frage „warum blieb der Lauf leer" gehört in den Plan, nicht in meine
  eigene Recherche.

## Offene Faehrten

- **Erledigt und nicht wieder aufzuwärmen:** Übersetzungslauf (läuft seit 2026-09-02,
  cmake/ctest grün — die Prämisse „es gibt keinen Übersetzer" ist widerlegt) und
  Rücklaufgrenze (`RUECKLAUF_MAX = 3`). Zwei von vier Fragen des 2026-09-01 beantwortet.
- **Reihe 9 / R und „Schaden" sind zum zweiten Mal unbeantwortet.** Ich habe sie deshalb
  nicht erneut als eigene Frage hingeschrieben, sondern in die Ursache umgehängt: Ihre
  Rolle (Spielentwerfer) wird vom Baulauf nicht geplant. Beim nächsten Mal prüfen, ob das
  getragen hat — wenn eine Frage dreimal steht, war meine Umdeutung auch falsch.
- **Nächster Lauf zuerst:** Ist `BAUROLLEN` um `architekt`/`spielentwerfer` erweitert, und
  steht 0004 auf `gebaut`? Beides sind Ja/Nein-Fragen mit einem grep. Wenn nein, ist der
  Engpass unverändert und gehört wortgleich wieder nach oben — dann ist nicht der Bericht
  langweilig, sondern das Vorhaben steht.
- **Die 170-gegen-121-Lücke** hat seit dem 2026-09-01 niemand angefasst und sie blockiert
  noch nichts. Erst wieder aufgreifen, wenn der Kern rechnet.
- **Offen und ungemessen: Warum brechen Läufe vor der Schlussarbeit ab?** Vermutung
  (unbelegt): Kontingent- oder Zeitgrenze am Ende langer Bauläufe. `agents/auslastung.py`
  kennt Tokens je Lauf und könnte es zeigen — ich schreibe nicht nach `ops/auslastung.md`,
  also gehört die Frage in den Plan, nicht in meine eigene Recherche.
