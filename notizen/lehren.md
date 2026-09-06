# Lessons — one line per rule

Every agent reads this file at the start of every run, so it holds **the rule, not the
story**. Full accounts — what happened, what was measured, what it cost — are in
`notizen/archiv/lehren-ausfuehrlich.md`. Read that only when a rule below surprises you.

Each line was paid for once. If your run is about to do what a line warns against, do it
the other way. If you think a rule is wrong, write that in your own logbook — never act
against it.

- 2026-08-31 — Unterhaltung ist der einzige Suchraum, in dem das Killerkriterium dieser Fabrik gar nicht existiert — und der einzige mit noch schlechteren Zahlen.
- 2026-08-31 — Entschieden vom Betreiber: Ein Spiel über Finanzmärkte, Lobbyismus und Korruption ist bei `genehmigung` unbedenklich.
- 2026-08-31 — Die Fabrik sucht nicht mehr.
- 2026-09-02, ergänzt 2026-09-06 — Die 170-gegen-121-Lücke, und warum sie niemand mehr ansieht.
- 2026-09-01 — Ein Agent, der Code schreiben soll und ihn nie übersetzen kann, schreibt über Code.
- 2026-09-01 — Eine Bremse an der Stelle, die gerade weh tut, ist keine Bremse.
- 2026-09-01, berichtigt am 2026-09-06 — Ein Argument ist kein Vergleich, und diese Fabrik kann den Vergleich *bauen*, statt ihn zu führen.
- 2026-09-02 — Jede Rolle darf Arbeit vorschlagen, einplanen tut der Projektmanager.
- 2026-09-06 — Eine Prüfung, deren Gegenstand sich nicht bewegen *kann*, ist grün und wertlos.
- 2026-09-06 — Ein `cd` in einem Bash-Aufruf nimmt das Sitzungs-Arbeitsverzeichnis mit, und danach stirbt jeder `Edit`.
- 2026-09-02 — Ein Agent kann präzise begründen, warum er scheiterte, und dabei falsch liegen.
- 2026-09-05 — Es gibt drei Grenzen, und die Fabrik kannte zwei.
- 2026-09-02, aufgelöst am 2026-09-05 — Ich habe zwei Wochen gegen eine Zahl gebremst, die ich mir ausgedacht hatte, und danach gegen den falschen Tarif geeicht.
- 2026-09-02 — Jede Zeitfensterabfrage der Fabrik war falsch, und niemand hat es gemerkt, weil sie plausible Zahlen lieferte.
- 2026-09-02 — Wer einen Runner aendert, waehrend er laeuft, aendert nichts: Der Prozess hat das Modul einmal importiert und benutzt bis zum Schluss die alte Fassung.
- 2026-09-02 — Eine Grenze, die nur an einer Stelle gilt, verlagert das Problem: RUECKLAUF_MAX galt im Bau, nicht im Review, und die aeltesten Pakete verhungerten.
- 2026-09-03 — Die Fabrik hängt an einem Rechner, der schlafen darf.
- 2026-09-05 — Der Wecker stand im Schlafzimmer.
- 2026-09-03 — Der Nachstart von Hand war schlimmer als der verpasste Lauf.
- 2026-09-03 — Logik in einer Cron-Zeile wird beim Schreiben eingebrannt.
- 2026-09-03 — Ein Skript hieß „Bereitschaft" und veröffentlichte den ganzen Arbeitsbereich.
- 2026-09-01 — `state.db` von Windows aus geöffnet, Datenbank zerstört, 54 Journaleinträge verloren.
- 2026-09-02 — Eine Prüfung, die importiert statt auszuführen, prüft nichts.
- 2026-09-06 — Die Shell-Grenze der Fabrik gab es nie.
- 2026-09-06 — Der Dollarwert taugt nicht zur Eichung des Kontingents, und jetzt ist es dreimal gemessen.
- 2026-09-06 — Es sind zwei Töpfe, nicht einer.

- 2026-09-06 — A check written with single quotes cannot fail:  expands in the child shell, where the variable does not exist. The path became /notizen and find never matched. Always bait-test a new check.
- 2026-09-06 — Token cost is paid per read, not per file. A file read in every run is worth cutting; one read once is not. Hot set: CLAUDE.md, lehren.md, the role file, the logbook.

---

Full accounts and anything older: `notizen/archiv/lehren-ausfuehrlich.md`.
