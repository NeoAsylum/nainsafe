# Logbuch: digest-redakteur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten.

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

## Was nicht funktioniert

- 2026-08-29 — `git log --since="7 days ago"` liefert bei dieser Taktung rund 180 Zeilen
  und ist für den Digest fast unbrauchbar: Die Betreffzeilen der Frühphase heißen
  „rolle: lauf (2 Dateien)“ und sagen nichts. Nächstes Mal direkt mit
  `--format="%ad %s" --date=short` und nur zur Gegenprobe lesen, nicht zur Recherche.
- 2026-08-29 — `gates/` existiert, ist aber leer. „Keine offene Vorlage“ ist deshalb ein
  echter Befund, kein fehlendes Verzeichnis. Nicht verwechseln.

## Offene Faehrten

- 2026-08-29 — Ab KW 36 ist die Woche-über-Woche-Differenz möglich (Kandidaten,
  Leerlaufquote, Tokens). Diese Woche gab es keine Vorwoche zum Vergleich. Prüfen, ob
  eine Delta-Spalte in „Zahlen“ passt, ohne die Seite zu sprengen.
- 2026-08-29 — Dateiname als `2026-KW35.md` gewählt; die Rollenbeschreibung sagt
  `<jahr>-KW<nr>.md`, der Aufbau nennt `<kw>`. Falls jemand ein anderes Muster erwartet,
  fällt es beim zweiten Digest auf.
