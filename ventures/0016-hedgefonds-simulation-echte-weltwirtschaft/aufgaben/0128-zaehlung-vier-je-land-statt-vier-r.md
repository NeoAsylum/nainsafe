---
id: 0128-zaehlung-vier-je-land-statt-vier-r
rolle: spielentwerfer
status: vorschlag
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
