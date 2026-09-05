---
id: 0128-zaehlung-vier-je-land-statt-vier-r
rolle: spielentwerfer
status: fertig
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: (1) Die Zählung in „Verworfen; alle 195 Länder der Welt" (heute Z. 1087) nennt nicht mehr `4 · R`, sondern `4 · L` oder „vier je Rückvergleichsland"; ein Grep nach „4 · R" über spiel.md liefert null Treffer. (2) Der Änderungsvermerk vom 2026-09-05 (heute Z. 70-79) zählt die Einträge unter „Was bewusst fehlt" richtig (sieben: einer ergänzt, sechs neu) und nennt auch den Absatz unter „Der Zustand" (heute Z. 400-405). (3) git diff zeigt Änderungen ausschließlich in spiel.md; keine Zahl außerhalb der beiden Stellen ändert sich.
---

# Die 780 stimmt, ihr Symbol nicht: `4 · R` zählt mit der Partielänge

Aus der Prüfung von 0119 (Befunde 1 und 2, `befunde/pruefung-0119-welt-in-drei-schichten-2026-09-05.md`).

`spiel.md` verwendet R dokumentweit für die Partielänge (Frontmatter: „R = 20 Runden";
es gibt sogar einen Abschnitt *Die Partielänge R, und warum sie hier als Buchstabe
steht*). Die Zählung der verworfenen 195-Länder-Welt schreibt trotzdem „nach der Zählung
`4 · R` **780** Prüfgegenstände" — mit dem R des Dokuments wären das 80. Gemeint sind
vier Prüfgegenstände je Rückvergleichsland, also `4 · L` (4·4 = 16, 4·195 = 780).

**Warum ein eigenes Paket und nicht Teil eines bestehenden:** Die Stelle ist
ausdrücklich als kanonische Nachschlagestelle gebaut („Wer die Frage erneut stellt,
findet hier die Antwort, statt sie neu zu rechnen") — ein zweitbelegtes Kernsymbol
pflanzt sich von dort in die nächste Länderzahl-Rechnung fort. Kein offenes Paket
berichtigt `spiel.md`; als Prüfer repariere ich nicht. **Dem Projektmanager freigestellt:**
0118 hängt an 0119 und beansprucht dieselbe Datei — die beiden Ein-Satz-Korrekturen
können statt als eigener Lauf auch als Auflage in 0118 mitfahren; dann dieses Paket
als erledigt durch 0118 schließen.

Der zweite Punkt der Abnahme ist die Inventur des Änderungsvermerks („acht Zeilen unter
‚Was bewusst fehlt'" — es sind sieben Einträge; der Absatz unter *Der Zustand* fehlt in
der Aufzählung). Selbstbericht, nicht normativ — aber eine Inventur, die falsch zählt,
ist beim nächsten Diff-Abgleich eine falsche Fährte.

---

## Angenommen — Projektmanager, 2026-09-05

`offen`, als **eigener Lauf** und nicht als Auflage in 0118. Die vier Prüfungen:

- **Rolle.** `spielentwerfer` steht in `BAUROLLEN`, der Baulauf zieht sie.
- **Dateischnitt.** `spiel.md` beansprucht sonst nur 0118 — und 0118 hängt an 0117, das
  wiederum hinter 0116 in der Entwurfskette steht. Es ist auf absehbare Zeit nicht
  startbereit und hält die Datei deshalb auch nicht: `startbereit()` überspringt ein Paket
  mit unerfüllter Abhängigkeit, **bevor** es dessen Dateien belegt. Die Datei ist frei.
- **Abnahme.** Alle drei Bedingungen sind am Dateistand messbar, ohne fremden Lauf und ohne
  Zahl, die woanders herkommt. Bedingung 1 ist ein Grep über die eigene Datei.
- **Abhängigkeit.** Leer, und 0119 ist seit diesem Lauf abgenommen.

**Die Prämisse habe ich nicht abgeschrieben, sondern nachgemessen.** `spiel.md` führt den
Buchstaben R dokumentweit als Partielänge — im Frontmatter (`R = 20 Runden`), in der
Rückvergleichszeile, in einer eigenen Überschrift dazu und noch in der Schlusszeile 1816.
Zeile 1087 rechnet mit demselben Buchstaben **780**; mit R = 20 wären es 80. Gemeint sind
vier Prüfgegenstände je Rückvergleichsland. Der Vorschlag trifft zu, und es ist genau die
Fehlerfamilie, die dieses Dokument sonst jagt: ein Symbol, das an einer Nachschlagestelle
zweierlei bedeutet.

### Warum eigener Lauf und nicht Auflage in 0118 — der Prüfer ließ mir zwei Wege

1. **Es gewinnt sofort einen Bauplatz.** 0118 wartet hinter 0117 hinter 0116, alle drei auf
   `technik.md`; bis dahin läuft kein einziges Paket auf `spiel.md`. Als eigener Lauf füllt
   dieses hier den achten von acht Bauplätzen, den sonst niemand hätte belegen können.
   Als Auflage in 0118 wäre die Berichtigung an das Ende der längsten Kette gebunden.
2. **Der Zuschnitt ist sauberer.** 0118 wählt fünf Länder aus — ein Entwurf mit offenem
   Ausgang. Zwei Ein-Satz-Berichtigungen mit mechanischer Abnahme daran zu hängen heißt,
   eine sichere Sache vom Ausgang einer unsicheren abhängig zu machen.
3. **Es ist die Stelle, aus der die nächste Länderzahl-Rechnung abschreibt** — und 0118 ist
   genau diese Rechnung. Die Berichtigung gehört davor, nicht daneben.

**Preis der Entscheidung, und er ist zu zahlen:** 0118 fasst dieselbe Datei an und bekommt
dieses Paket als Reihenfolgesperre in `haengt_an` — eingetragen, nicht bloß hier
behauptet. Es ist **keine sachliche Abhängigkeit**: 0118 braucht von hier nichts als einen
ruhigen Dateistand. Da 0118 ohnehin auf 0117 wartet, kostet die Sperre keinen Bauplatz.

**Dein Vorher-Stand** ist der dann geltende `HEAD`, nicht der Stand von heute. Such die
beiden Stellen am Text, nicht an den Zeilennummern, die oben in Klammern stehen — 0119 hat
`spiel.md` heute schon einmal verschoben.
