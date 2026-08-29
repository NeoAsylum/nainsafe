---
nr: 0004
titel: Der Suchraum bekommt eine Untergrenze und verliert seine Landesgrenze
datum: 2026-08-29
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [ideen, sensorik, bewertung]
---

# ADR 0004 — Suchraum: Größe rein, Landesgrenze raus

## Kontext

Nach fünf Wochen Betrieb standen achtzehn Ideen im Repo. Drei hatten alle fünf Angriffe
und die Verteidigung überstanden und lagen als beste Kandidaten vor:

| Idee | Punkte | Segment | erreichbar | marge |
|---|---:|---|---:|---:|
| Asbestanzeige | 18 | Abbruchbetriebe mit TRGS-519-Pflicht | 3 | 3 |
| Zettelfoto | 16 | Kleinbetriebe mit Papierbelegen | 3 | 3 |
| Haushaltsturnus | 16 | Anbieter nach § 45b SGB XI | 2 | 3 |

Alle drei sind kleine Werkzeuge für kleine Nischen. Alle drei starben an derselben
Linse — Vertrieb. Und alle drei hatten schon beim Fit-Filter eine 2 oder 3 bei
`erreichbar` und eine 3 bei `marge` stehen. Die Fabrik hat das Ergebnis fünf
Angriffsläufe lang erarbeitet, das es beim Filter schon gab.

Parallel dazu die Marktprofile: **sechzehn von zweiundzwanzig Segmenten kamen auf
`potenzial: gering`.** Der häufigste Grund war immer derselbe — ein paar tausend
Betriebe, ein Zahlungsbereitschaftsdeckel um dreißig Euro, ein bis drei zugeschnittene
Anbieter, die den Rest schon bedienen.

Zwei Befunde, eine Ursache. Es fehlten zwei Angaben, die nie irgendwo standen:

1. **Wie groß soll das Unternehmen werden?** Ohne Zielgröße war jede Idee gut genug,
   solange sie überhaupt Geld einbrachte. Ein Werkzeug mit dreihundert Euro Umsatz im
   Monat und eines mit fünftausend sahen im Frontmatter gleich aus.
2. **In welchem Markt?** Die Fabrik hat ausschließlich Software für deutsche
   KMU-Nischen gesucht. Diese Beschränkung stand in **keiner** Regel — nicht in
   `grenzen.md`, nicht in `CLAUDE.md`, nicht in `quellen.yml`. Sie war eine
   unbegründete Verengung, entstanden aus den ersten Signalquellen und danach nie
   hinterfragt. Ausgerechnet auf die am dichtesten besetzte Kategorie überhaupt.

## Entscheidung

**Erstens: 5.000 € Marge im Monat sind die Untergrenze.** Marge, nicht Umsatz, vor
Steuern. Was diese Schwelle erkennbar nie erreichen kann, wird nicht ausgearbeitet.
Die Schwelle wird gerechnet, nicht geschätzt:

    Preis je Kunde und Monat  ×  erreichbare Kundenzahl

Beide Zahlen sind belegpflichtig — der Preis am nächstgrößeren Vollprodukt im Segment,
die Kundenzahl an der Segmentgröße. Fehlt eine, ist die Idee nicht beurteilbar und
damit abgelehnt. Für die Kundenzahl gilt: ein Prozent Marktdurchdringung ist
optimistisch, ein Promille realistisch, solange kein Kanal belegt ist.

Daraus folgt die Faustregel, die den Suchraum tatsächlich verändert: **Entweder das
Segment ist groß genug, oder der Preis ist hoch genug. Beides klein trägt nie.**

**Zweitens: Der Markt ist nicht auf Deutschland beschränkt.** Englischsprachige
Zielgruppen sind ausdrücklich erlaubt. Das ist der eine Hebel, der aus dreitausend
Betrieben hunderttausend macht, ohne dass sich am Produkt etwas ändert.

**Drittens: B2C ist erlaubt.** Der Grund ist nicht der Preis — Endkunden zahlen weniger
—, sondern G3: Sie bedienen sich selbst und suchen aktiv. Genau der Kanal, an dem
bisher jede zweite Idee gestorben ist.

**Viertens: Drei Sperren greifen unabhängig von der Punktsumme.** `genehmigung` unter 3
(wie bisher), neu `marge` unter 4 und `erreichbar` unter 3. Die Summe hat die
Schwachstellen der drei besten Ideen fünf Läufe lang überdeckt.

## Was das kostet

Die größeren Märkte sind nicht gratis, und wer sie wählt, benennt den Preis:

- **Englischsprachig:** Umsatzsteuer im Zielland, bei Endkunden je nach Land auch
  Verbrauchersteuern. Für ein Nebengewerbe nur über einen **Merchant of Record**
  handhabbar — einen Zahlungsanbieter, der als Verkäufer auftritt und die
  Steuerpflichten übernimmt. Sein Anteil gehört in die Rechnung.
- **Endkunden:** vierzehn Tage Widerrufsrecht, bei digitalen Inhalten nur durch
  ausdrückliche Verzichtserklärung vor dem Download abwendbar. Dazu Verbraucher-AGB,
  Preisangabenverordnung, Streitschlichtungshinweis. Einmalig zu erledigen, aber vor
  dem Start.

Was **nicht** zählt, ist ein größerer Markt, der nur behauptet wird. „Weltweit
verfügbar" ist kein Markt, solange kein Kanal in diesem Markt benannt ist.

## Was unverändert bleibt

**G1 betrifft die Branche, nicht das Land.** Versicherung, Bausparen und
Finanzdienstleistung samt ihrer IT bleiben ausgeschlossen — in jedem Markt. Ein Werkzeug
für australische Tierärzte berührt die Grenze nicht; eines für britische
Versicherungsmakler sehr wohl.

Die übrigen acht Grenzen gelten unverändert. Insbesondere G4 (zwei Stunden pro Woche)
und G9 (kein Personal): Ein größerer Markt darf nicht über mehr Betreuungsaufwand
erkauft werden. Englischsprachiger Support ist zulässig, weil er asynchron und
maschinell laufen kann — englischsprachige *Beratung* wäre bereits G3.

## Folgen

Geändert wurden an diesem Tag:

- `grenzen.md` — Abschnitt *Wonach überhaupt gesucht wird*, G7 neu gefasst als
  Größenschwelle, G1 um den Satz zur Landesgrenze ergänzt, drei Einzelsperren bei der
  Bewertung.
- `CLAUDE.md` — Abschnitt *Wonach gesucht wird* vor den vier harten Regeln.
- `quellen.yml` — zwei neue Segmentblöcke, achtzehn Einträge: englischsprachiger B2B
  und Endkunden. Der deutsche Block bleibt, seine sechs offenen Einträge auch.
- `vorlagen/idee.md` — Felder `suchraum`, `preis`, `kunden_noetig`,
  `kunden_erreichbar` und ein Abschnitt **Rechnung**.
- `agents/rollen/markt-analyst.md` — siebte Frage (die Rechnung), Zahlenquellen für
  alle drei Suchräume, `potenzial: hoch` setzt `traegt_5000: ja` voraus.
- `agents/rollen/ideator.md` — Abschnitt *Die Größenordnung*, Preis und Kundenzahl als
  Pflichtteil der Hypothese.
- `agents/rollen/fit-filter.md` — G1 bis G9 statt G1 bis G7, G7 als Rechnung, die drei
  neuen Sperren.
- `agents/rollen/modell-scout.md` — fünfte Übertragungsrichtung `direkt`: ein Modell im
  englischsprachigen Raum betreiben, statt es nach Deutschland zu übertragen.
- `agents/rollen/rechercheur.md` — die Ampel prüft den Zielmarkt des Signals, nicht
  pauschal den deutschsprachigen; `rot` bei rechnerisch verfehlter Schwelle.
- `agents/repo.py` — `offene_segmente()` vergleicht nur noch in einer Richtung und
  bevorzugt das neue Pflichtfeld `auftrag`. Die alte Fuzzy-Regel hätte „Tierarztpraxen
  im englischsprachigen Raum" als erledigt gemeldet, weil ein Profil über deutsche
  Tierarztpraxen existiert — ein anderer Markt mit anderer Größe.

## Was das nicht heißt

Die achtzehn bisherigen Ideen werden nicht neu bewertet. Sie sind unter den damals
geltenden Regeln entstanden und korrekt behandelt worden; die drei besten sind an einem
echten Einwand gestorben, nicht an einem Formfehler. Wer eine davon wiedervorlegt,
tut das nach der bestehenden Regel — alte Ablehnung benennen und widerlegen —, und die
neue Größenschwelle ist dabei kein Freibrief, sondern eine zusätzliche Hürde.

Dass zweiundzwanzig Ideen verworfen wurden, ist kein Befund. Die meisten Ideen sind
schlecht, und neun von zehn Unternehmen scheitern früh. Der Befund ist, dass sie alle
an derselben Stelle starben — und dass niemand vorher ausgerechnet hat, wie groß der
Markt sein müsste.
