# Logbuch: digest-redakteur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist es voll, verschiebst du die Datei nach
`notizen/archiv/` und beginnst neu mit dem, was noch gilt.

---

## Was funktioniert

- 2026-08-29 — Erster Lauf dieser Rolle, `ops/digest/` war leer. Vier Quellen reichen
  vollständig aus: `ops/portfolio.md` (Lage + Meldungen an den Betreiber),
  `ops/auslastung.md` (alle Zahlen fertig gerechnet), `ops/verbesserung.md` (Vorschlag),
  `ls gates/`. Das `git log --since` diente nur zur Gegenprobe, ob das Portfolio etwas
  verschweigt — tat es nicht.
- 2026-08-29 — Leerlaufquote steht nicht in `auslastung.md`, nur die Spalte „leer“ je
  Rolle. Summe der Spalte durch Gesamtläufe: 25/122 = 20 %. Das ist Addition vorhandener
  Zahlen, keine eigene Rechnung aus dem Journal.
- 2026-08-29 — Regel „jede Zeile endet in Zahl oder Frage“ trägt den Abschnitt
  „Was auffällt“ von selbst: Wer keine Zahl hat, hat keine Auffälligkeit.

- 2026-08-30 — Delta-Spalte gelöst, ohne die Seite zu sprengen: Vorwochenzahl in Klammern
  hinter die aktuelle (`156 in 7 Tagen (Vorwoche 122)`). Quelle ist der eigene Digest der
  Vorwoche, nicht `auslastung.md` — die kennt nur das laufende Fenster.
- 2026-08-30 — Gibt es keine Gates, aber Meldungen des Portfolio-Managers an den
  Betreiber, gehören sie **nicht** in „Was du entscheiden musst" (dort stehen nur Gates),
  sondern als Frage nach „Was passiert ist" und „Was auffällt". Sonst geht die einzige
  echte Entscheidung der Woche unter.

- 2026-09-06 — Delta-Fährte aus KW 35 eingelöst: Vorwochenzahl in Klammern trägt, kostet
  fünf Wörter je Zeile. Beim Sprung 156 → 1.531 Läufe ist das Verhältnis („das
  17-Fache") die eigentliche Meldung, nicht die Rohzahl.
- 2026-09-06 — In der Bauphase ist `ops/portfolio.md` die einzige Quelle, die Zahlen
  über das *Vorhaben* trägt (Arbeitspakete, Tests, „0 von 310"). `auslastung.md` misst
  nur noch den Apparat. Ohne das Portfolio wäre der Digest eine reine Tokentabelle.

## Was nicht funktioniert

- 2026-08-29 — `git log --since="7 days ago"` liefert bei dieser Taktung rund 180 Zeilen
  und ist für den Digest fast unbrauchbar: Die Betreffzeilen der Frühphase heißen
  „rolle: lauf (2 Dateien)“ und sagen nichts. Nächstes Mal direkt mit
  `--format="%ad %s" --date=short` und nur zur Gegenprobe lesen, nicht zur Recherche.
- 2026-08-29 — `gates/` existiert, ist aber leer. „Keine offene Vorlage“ ist deshalb ein
  echter Befund, kein fehlendes Verzeichnis. Nicht verwechseln.

## Offene Faehrten

- 2026-09-06 — **Abweichung von meinem Eintrag vom 2026-08-30, bewusst:** Ich habe zwei
  Meldungen des Portfolio-Managers doch unter „Was du entscheiden musst" gesetzt, unter
  den Satz, dass es keine offene Gate-Vorlage gibt. Grund: Beide sind echte
  Betreiberentscheidungen mit Frist (Vorrangliste, Wiedervorlage 2026-09-13), und in
  „Was passiert ist" wären sie zwischen fünf Bauzahlen untergegangen. Nächster Lauf:
  prüfen, ob der Betreiber sie beantwortet hat — bleibt es unbeantwortet, war die
  Platzierung nicht das Problem.
- 2026-09-06 — `git log --since="7 days ago"` liefert jetzt 545 Zeilen und ist als
  Gegenprobe endgültig unbrauchbar; nur noch `| wc -l` für die Commitzahl nutzen.
- 2026-08-29 — Dateiname als `2026-KW35.md` gewählt; die Rollenbeschreibung sagt
  `<jahr>-KW<nr>.md`, der Aufbau nennt `<kw>`. Falls jemand ein anderes Muster erwartet,
  fällt es beim zweiten Digest auf.
- 2026-08-30 — **Der Digest lief zweimal in derselben Kalenderwoche** (Sa 08-29 und
  So 08-30, beide KW 35), weil der Nachtlauf täglich taktet und der Dateiname nur die
  Woche kennt. Ich habe die Datei überschrieben; die alte Fassung steht in der
  Git-Historie, gelöscht ist nichts. Offen für den Betreiber: Soll der Digest-Redakteur
  nur sonntags laufen? Sonst schreibt er jeden Tag dieselbe Datei neu.
