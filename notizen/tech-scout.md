# Logbuch: Tech-Scout

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten. Ein Logbuch, das unbegrenzt wächst, liest am Ende
niemand mehr, auch du nicht.

---

## Was funktioniert

- 2026-08-28 — Suche nach "Datenaustausch ab 2026" + konkretem Steuer-/Sozialversicherungsverfahren
  war ergiebiger als "neue API Behörde Deutschland" (zu generisch, liefert nur Aggregator-Blogartikel
  ohne Primärquelle). Treffer: ELStAM-Erweiterung um private KV/PV-Beiträge, direkt beim BMF mit
  wörtlichem Zitat belegbar.
- 2026-08-28 — Bei mehrdeutigen WebFetch-Zusammenfassungen (Titel der Quelle passt nicht zum
  Fetch-Inhalt) lieber per WebSearch die korrekte Primärquelle nachsuchen, statt der ersten
  Zusammenfassung zu vertrauen. Ein Fetch zu einer PDF hat einmal Inhalt erfunden, der nicht zum
  Dokumententitel passte — verworfen, stattdessen über Suche die offizielle BMF-Seite gefunden.

## Was nicht funktioniert

- 2026-08-28 — "Handelsregister API" und "Bundesanzeiger API" liefern seit Jahren dasselbe Ergebnis:
  keine offene Schnittstelle für Dritte, nur Einreichung (XBRL/XML), nicht Abruf. Nicht erneut prüfen
  vor Ende 2026, außer es gibt einen konkreten Auslöser (z.B. neue Open-Data-Pflicht für Register).
  Kandidat für Eintrag in `notizen/lehren.md` durch den Portfolio-Manager: strukturell unwahrscheinlich,
  dass sich das ohne neues Gesetz ändert.
- 2026-08-28 — Basisregister/Once-Only (UBRegG) baut aktuell nur Behörden-zu-Behörden-Anbindungen
  aus (IHK, Bundesanzeiger-Verlag, BA, BNetzA ab H2 2026) — kein Zugang für private Dritte erkennbar.
  Kein Signal, aber im Auge behalten: sobald private Software-Anbieter angebunden werden dürfen,
  wäre das ein großer Sprung (einmalige Stammdatenpflege statt Mehrfacheingabe).

## Offene Faehrten

- ELSTER-Datenaustausch privater KV/PV-Beiträge (Signal vom 2026-08-28): unklar, ob Lohnbüros/
  Software-Anbieter direkt über ELStAM zugreifen dürfen oder nur der Arbeitgeber selbst — bei
  Gelegenheit die ELSTER-Entwicklerdoku (ERiC) dazu prüfen.
- WSP.NRW-Gewerbeanmeldeschnittstelle (Signal vom 2026-08-28, von wem angelegt unklar): ob es eine
  maschinelle API für Dritt-Software gibt, ist offen — Entwicklerdokumentation noch nicht gesichtet.
