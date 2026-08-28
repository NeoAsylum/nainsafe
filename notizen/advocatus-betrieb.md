# Logbuch: Advocatus Diaboli, Linse Betrieb

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-28 — Wirksamstes Vorgehen (0005): die *abgelehnten* Ideen mit demselben
  Ablehnungsgrund lesen. Wenn ein Entwurf schreibt „hier ist die Idee gestorben, wir
  machen es anders", ist die Frage nicht ob, sondern **wo die Heterogenität jetzt sitzt**.
- 2026-08-28 — Der teuerste Punkt lag bei 0005 und 0009 beide Male *unter* den
  Aufzählungspunkten meines Auftrags. Prüffrage, die beide Male getroffen hat:
  **Woher weiß der Dienst, was er behauptet?** Bei 0005 legte er aus statt zu tippen,
  bei 0009 behauptet er, was stattgefunden hat, ohne Sensor dafür. Ein Dienst ohne
  eigene Wahrnehmung wird vom Kunden gefüttert — und dann skaliert Pflege je Kunde.
- 2026-08-28 — Tabelle mit Annahme-Spalte je Aufwandsposten, danach die linear
  wachsenden Zeilen getrennt aufaddieren und auf 100 Kunden hochrechnen. Macht die
  Zahl im Frontmatter überprüfbar statt behauptet. Zweimal getragen.
- 2026-08-28 (0009, 0012) — Ergiebigster Angriff: **Wann fällt der Fehler auf, und trifft
  er einzeln oder gebündelt?** 0009: Steuerbeträge fallen 14–20 Monate später und geballt
  auf, in einem Jahr mit geschlossenen Büchern. 0012: alle Kunden eines Bundeslandes
  hängen an einem gepflegten Datensatz, also ist jeder Fehler ein Regionalausfall an
  einem Tag. Ein korrelierter Fehler macht den Wochendurchschnitt bedeutungslos.
- 2026-08-28 (0012) — Stärkster neuer Angriff: **den kundenunabhängigen Sockel getrennt
  ausrechnen.** Pflegt ein Produkt einen Datenbestand über die Außenwelt (Behörden,
  Formulare, Tarife), fällt der Aufwand *vor* dem ersten Kunden voll an — bei 0012 1,8
  von 2,0 Stunden bei null Umsatz. Wachstum hilft nicht; „was bei 100 Kunden?" greift
  hier zu spät.
- 2026-08-28 (0012) — Grenzt ein Entwurf sich mit „fällt es aus, macht der Kunde es von
  Hand" gegen eine frühere Ablehnung ab: prüfen, ob die **typische Fehlerart überhaupt
  ein Ausfall** ist. Formularbefüller fallen nicht aus, sie liefern still Falsches —
  dagegen greift kein Fallback.
- 2026-08-28 (0012) — Erbt eine Idee einen bereits **abgelehnten** Zuschnitt als
  Bestandteil (0013 in 0012), erbt sie dessen Aufwand ungepreist. Die
  Ablehnungsbegründung des Fit-Filters liefert die Zahlen frei Haus.
- 2026-08-28 (0012) — Support-Bemessungsgrundlage ist nicht immer die Kundenzahl. Hält
  ein Produkt Personendaten Dritter (hier 6 Beschäftigte je Kundenbetrieb), sind es 600
  Betroffene bei 100 Kunden — mit fristgebundenen, nicht automatisierbaren Anfragen.

## Was nicht funktioniert

- 2026-08-28 — Angriff über Modellkosten je Vorgang lief bei 0005 und 0009 beide Male
  ins Leere (Cent-Beträge bzw. gar kein Modellaufruf, gegen Pauschalpreis je Betrieb).
  *Merke:* Nicht dort anfangen, sondern beim Aufwand je Kunde. G7-Tokens sind bei
  B2B-Pauschalpreisen fast nie der Killer; sie nur zur Fairness kurz abhaken.
- 2026-08-28 — Skill `claude-api` nicht aufrufbar, `Bash` teils verweigert. Zahlen, die
  ich nicht belegen kann, sofort als Schätzung markieren statt Zeit in Belege zu stecken.
  Kalenderfakten (ISO-Wochen, Wochentage) lassen sich von Hand herleiten — 2026 hat 53
  ISO-Wochen, weil der 1.1.2026 ein Donnerstag ist.
- 2026-08-28 (0012) — `WebSearch` und `WebFetch` wurden verweigert („don't ask mode").
  Für diese Rolle ist das kein Verlust: Die drei bisherigen Angriffe kamen ohne eine
  einzige eigene Außenquelle aus. Künftig gar nicht erst danach greifen — die Zahlen
  stehen im Entwurf, im Marktprofil und in den Ablehnungsbegründungen.

## Offene Fährten

- **Ballt sich die Nachfrage in einem Zeitfenster?** Dreimal der Kern des schlimmsten
  Tages (0005 Lohnlauf, 0009 Monatsabschluss, 0012 Sieben-Tage-Frist je Baustelle).
  Diese Frage zuerst stellen, sie kollidiert immer mit G3.
- **Bestätigt an 0012, allgemeiner als gedacht:** Die tolerierbare Reaktionszeit sinkt
  unter 24 h nicht nur, wenn Endverbraucher *hinter* dem Kunden stehen, sondern auch,
  wenn eine gesetzliche Frist *vor* ihm liegt. Nicht der Vertrag setzt die Reaktionszeit,
  sondern die Frist des Kunden. Formal keine G3-Verletzung, faktisch dieselbe Falle.
- Neu (0012): Wenn Vertriebskanal und Beschwerdekanal identisch sind (Innung, Verband,
  Fachgruppe), ist ein Rufschaden nicht lokal, sondern regional total — und unbeantwortbar,
  weil er mündlich läuft. Bei jeder verbandsvertriebenen Idee prüfen.
- Ungeprüft geblieben (aus 0005): Wie oft ändern Craftnote, openHandwerk, ToolTime ihre
  Importformate? Bei der nächsten Idee mit Importdateien als Kern zuerst klären.
