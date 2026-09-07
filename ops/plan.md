# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-08. Abgedeckt: seit 2026-09-07.

## Wo das Vorhaben steht

**Der Rückstand des letzten Plans ist abgeräumt.** 0198 (die Rechenvorschrift) ist `fertig`
und geprüft, 0200 hat die zehn toten Zitate nachgezogen, 0197 und 0208-baulauf stehen auf
`blockiert` statt auf `zurueck`. **Das stehende Rot ist weg:**
`befunde/uebersetzung-2026-09-07.md` meldet `ergebnis: ok` — 25 von 25 Tests grün im
Werkstattbaum, 13 von 13 im Kern, alle Werkzeugbäume grün. 196 Pakete: 169 fertig (+22),
19 offen, **0 Vorschläge**, 1 gebaut, 5 blockiert; Spielraum 8.722 von 12.000 $ (Stand
2026-09-06 05:00, zwei Tage alt), Geld bindet nicht.

## Der Engpass

**Eine Zeile in `ops/reserviert.txt` hält 15 der 19 offenen Pakete an.**

Die Zeile lautet `specs/0016-.../technik.md` und wird vom Übersetzungslauf gesetzt.
`baulauf.py:startbereit` zählt sie wie ein eingeplantes Paket: kein Paket, dessen
`dateien:` diese Datei trifft, wird eingeplant. Betroffen sind **0208-schritt** (der Draht),
0165, 0172-weltpreis, 0148, 0177, 0196, 0158, 0149, 0064, 0068, 0074, 0084, 0092, 0181,
0221.

Übrig bleiben **drei startbare Pakete** — 0189, 0224, 0225 —, und zwei davon räumen hinter
dem Übersetzungslauf auf. (0157 steht auf `offen`, hängt aber an 0197, das `blockiert` ist.)

Der Engpass ist damit zum ersten Mal **kein fehlender Beschluss, sondern eine Sperre.** Der
Projektmanager hat seinen Teil getan: sein Vermerk auf 0208 nennt die Sperre im Wortlaut
und stellt das Paket so, dass es anläuft, sobald sie fällt — „und dann ohne einen weiteren
Lauf von mir".

## Was quer liegt

- **Der Übersetzungslauf meldet alles fertig und hält die Datei trotzdem.**
  `ops/uebersetzt.txt` führt alle 21 Abschnitte von `technik.md`, alle 15 von `spiel.md`,
  alle 5 von `daten.md`; der Vorspann von `technik.md` liest bereits Englisch (Zeilen
  1–31). Der Kopf von `reserviert.txt` sagt „**Leer, sobald er fertig ist.**" Er ist nicht
  leer. Ob noch etwas aussteht oder die Zeile stehengeblieben ist, kann ich ohne Shell
  nicht messen — beides endet in demselben Stillstand.
- **Sieben der elf neuesten Pakete sind Nachlauf der Übersetzung** (0214-leitzins, 0220,
  0221, 0222, 0223, 0224, 0225). Der Riegel ist heute grün, **weil sie gebaut wurden** —
  nicht weil die Ursache weg wäre.
- **Überschriften werden uneinheitlich umbenannt.** In `spiel.md` sind vier ersetzt („Die
  Schleife" → „The loop", „Die Aktionen" → „The actions", „Der Zustand" → „The state", „Die
  Spiellänge R" → „The game length R"), elf stehen weiter deutsch; in `technik.md` keine
  einzige. Jede Umbenennung kostet ein Nachziehpaket.
- **0182 steht auf `gebaut` mit `urteil: geprueft`** (2026-09-08). Ein Lauf des
  Projektmanagers setzt es auf `fertig`. Heute der einzige Fall — gestern drei; die Lücke
  schliesst sich.
- Unverändert fortgeschrieben, nicht neu gefragt: `daten/roh/` gibt es nicht, `reihen.toml`
  sagt weiter „**Sie enthaelt keine Datenzeile.**" Drei Pakete tragen die Nummer 0208, die
  `id` ist eindeutig.

## Was der Betreiber entscheiden muss

Die Frage vom 2026-09-07 ist **unbeantwortet, nicht abgelehnt** — kein Commit ohne
Rollenpräfix, und `CLAUDE.md` trägt weiter „**They stay German until someone translates
them whole, which is not planned.**" Ich begründe sie nicht neu. **Sie hat sich aber
verschoben, und deshalb ändere ich meine Empfehlung.**

Damals war der Preis ein rotes Testergebnis. Heute ist es die Sperre: Übersetzungslauf und
Baulauf wollen dieselben zwei Dokumente, und der Übersetzungslauf gewinnt, weil er eine
Datei hält. Nur du kannst das entscheiden — `CLAUDE.md` und `agents/rollen/uebersetzer.md`
sind für jeden Agenten unschreibbar. Keine Geldfrage.

- **B (meine Empfehlung vom 2026-09-07)** — Überschrift erst umbenennen, wenn im selben
  Lauf jedes Zitat darauf nachgezogen ist. Richtig, aber **rührt die Sperre nicht an.**
- **C — `technik.md` und `spiel.md` vom Übersetzungslauf aussetzen**, bis die Runde
  rechnet. Gibt beide Dateien frei; 15 Pakete werden startbar.

**Empfehlung jetzt C** (bisher B). Der Grund ist neu und kostet nichts: Der Lauf meldet für
beide Dateien bereits **jeden** Abschnitt fertig. C nimmt ihm damit voraussichtlich keine
Arbeit ab — es nimmt nur die Sperre weg. B bleibt richtig und kann danach folgen.

## Vorrang

Solange die Sperre steht, sind nur die ersten beiden Punkte überhaupt einplanbar.

1. **0224** und **0225** — startbar, billig, schliessen den Nachlauf der Übersetzung.
   Solange er offen ist, ist der grüne Riegel geliehen.
2. **0189** — startbar; seine drei Abhängigkeiten (0147, 0166, 0182) sind durch.
3. **0208-schritt-braucht-einen-parametereingang** — unverändert der Draht und Kopf der
   Kette. **Keine Handlung nötig:** es läuft von selbst an, sobald `reserviert.txt` fällt.
4. **0165** — Kopf der umgehängten Kette, direkt hinter dem Draht.
5. **0172-weltpreis** — der Zollfaktor, Schritt 4; das einzige `technik.md`-Paket, das die
   Wirtschaft bewegt.

**Nicht einplanen:** 0157 steht auf `offen`, hängt aber am blockierten 0197 — es gehört
ebenfalls auf `blockiert`, sonst zählt es als Rückstand, den niemand abarbeiten kann.
0208-baulauf braucht einen anderen Schnitt oder den Betreiber — kein Agent darf `agents/`
schreiben.

## Die eine Zahl

**1 von 310** — unverändert seit dem 14. Plan (`partie.runde`). Der Apparat ist erneut
gewachsen: 25 Tests im Werkstattbaum (vorher 20), 13 im Kern (vorher 12), acht Manifeste,
407 geprüfte Schaltereinträge, alles grün — und die Runde rechnet weiterhin nichts.

**Neu ist, dass die eine Hälfte der Ursache weg ist.** 0198 ist `fertig`: die
Rechenvorschrift für das Realeinkommen steht in `spiel.md` und wurde vom Entwurfsprüfer
gegen T15/T27/T23/T48 nachgerechnet, jeder Name aufgelöst, jede Zahl unabhängig neu
gerechnet. Die andere Hälfte ist der Weg — `schritt(zustand, aktionen, modus)` hat weiter
kein Parameterargument —, und der Weg liegt hinter der Sperre. **Bewegt sich die Zahl,
bevor 0208 `fertig` ist, stimmt die Messung nicht.**
