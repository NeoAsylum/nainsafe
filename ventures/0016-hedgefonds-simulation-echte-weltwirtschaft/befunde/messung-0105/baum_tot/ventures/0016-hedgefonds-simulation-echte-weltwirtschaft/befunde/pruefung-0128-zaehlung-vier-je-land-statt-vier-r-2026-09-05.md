---
typ: pruefung
paket: 0128-zaehlung-vier-je-land-statt-vier-r
pruefer: entwurf-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen am heutigen Dateistand und am spiel.md-Diff afe774a→a6963e4 nachgemessen; die Sieben-Zaehlung von vorn am 0119-Diff (d2fb21b→2ed2e0c) gerechnet, nicht wiedererkannt.
befunde: 1
---

# Prüfung 0128: beide Stellen berichtigt, keine dritte angefasst — aber die Arbeit sitzt im Commit des falschen Pakets

**Sonderlage dieses Laufs:** 0128 ist mein eigener Vorschlag aus der Prüfung von 0119.
Nach der Regel meines Logbuchs habe ich die tragende Zählung (sieben Einträge) von vorn
am 0119-Diff gerechnet, statt meine alte Zahl wiederzuerkennen; sie hält (Bedingung 2).

## Bedingung 1 — `4 · R` ist weg, `4 · L` steht und stimmt: erfüllt

- Grep `4 · R` über `spiel.md`: **null Treffer.** Breiter nachgefasst (Muster
  `4[·*x]R`, `R · 4`, `vier · R`, mit und ohne Leerzeichen): ebenfalls null.
- Z. 1089-1090 lautet heute: „Rückvergleich hätte nach der Zählung `4 · L` — vier
  Prüfgegenstände je Rückvergleichsland — **780** statt sechzehn (dieselbe Formel, die
  für vier Länder 16 ergibt)". Formelprobe: L = 4 → 16, L = 195 → 780; beide Zahlen des
  Satzes reproduziert.
- Zweitbelegung von `L` gesucht — die Fehlerfamilie, die dieses Paket schließt: alle
  L-Vorkommen in `spiel.md` gegriffen (Z. 9, 849, 862, 913, 926-927, 973, 1029-1068,
  1162, 2462-2471, 2491-2499). Überall ist L die Zahl der Politikländer, und das Dokument
  setzt Rückvergleichsland = Politikland (vier Länder, vier Rückvergleichsländer, Z. 849).
  **Keine zweite Belegung.**
- Die einzige weitere 780 des Dokuments (Z. 2182, Eintrag „Alle 195 Länder der Welt")
  rechnet mit keinem Symbol und verweist auf *Was die Schicht kostet* — konsistent.

## Bedingung 2 — der Vermerk zählt sieben und nennt den Zustand-Absatz: erfüllt

Wortlaut heute Z. 70-81 (Passage Z. 73-77): „…ein Absatz unter *Der Zustand* (welchen
Stand die 310 meint), ein Absatz unter *Warum die Größe des Zustands keine Verteidigung
ist*, **sieben** Einträge unter „Was bewusst fehlt" — sechs neue und der erste, „Mehr als
vier Länder und drei Sektoren", ergänzt statt gestrichen —, fünf unter „Offene
Entwurfsfragen"…" (Die Abnahme nannte Z. 70-79; der Vermerk ist durch die Korrektur
selbst um zwei Zeilen gewachsen — am Text gesucht, wie vom Projektmanager vorgegeben.)

Von vorn gerechnet am 0119-Diff (`git diff d2fb21b 2ed2e0c -- spiel.md`):

- Hunk `@@ -1756,6 +2169,39` ist der **einzige**, der den Abschnitt „Was bewusst fehlt"
  berührt (Überschrift heute Z. 2170, nächste Überschrift „Offene Entwurfsfragen"
  Z. 2330; der nächste Hunk beginnt bei alt Z. 1997 und liegt dahinter). Inhalt: **ein**
  bestehender Eintrag ergänzt — „Mehr als vier Länder und drei Sektoren", +5 Zeilen
  „Am 2026-09-05 eingeordnet, nicht gestrichen" — und **sechs** neue Einträge (Alle 195
  Länder der Welt; Börsenplatz mit Handelszeile, Politikinstrumenten oder Beteiligung;
  Aufsichtszähler auf der zweiten Schicht; Regulierungskanal auf `zins[b]`; gemessene
  Marktkapitalisierung je Börsenplatz; eigener Trägheitsparameter). Zeilenprobe:
  39 − 6 Kontext = 33 hinzugefügt = 5 + (4+5+5+5+5+4). **Sieben Einträge, 1 + 6.**
- Der Zustand-Absatz steht heute Z. 402-407 unter `## Der Zustand` (Z. 397) und kam mit
  Hunk `@@ -384,6 +397,13` aus 0119 — der Hunk, den der alte Vermerk unterschlug.
- Gegenprobe des übrigen Vermerks am selben Diff: „fünf unter ‚Offene Entwurfsfragen'"
  deckt sich mit Hunk `@@ -1997,6 +2443,35` (fünf neue Einträge, nachgezählt).

## Bedingung 3 — Änderungen nur in spiel.md, keine Zahl außerhalb der zwei Stellen: in der Sache erfüllt

Der gesamte Diff der Berichtigung (`spiel.md` afe774a → a6963e4) umfasst **7
Zeilenänderungen in genau zwei Hunks**: den Vermerk (alt Z. 71-79) und die Zählstelle
(alt Z. 1084-1090). Keine weitere Zeile, keine weitere Zahl. Seither hat nichts
`spiel.md` berührt: `e00e7f9` enthält die Datei nicht, `38ab29f` ändert nur
`notizen/kernbauer.md`, und der Arbeitsbaum führt `spiel.md` nicht als geändert.

**Befund 1 (außerhalb der Abnahme, darum kein Rücklauf):** Die Paketarbeit sitzt im
Commit des falschen Pakets, und der Commit des Pakets enthält keine Paketarbeit.

- `0134179` mit Betreff „architekt: 0116-laenderzahl-als-parameter (25 Dateien)" enthält
  die **komplette** 0128-Änderung an `spiel.md` — aber **kein** `technik.md`, die einzige
  Datei in 0116s `dateien`-Liste (`technik.md` wurde zuletzt in `9e46cfa`, „architekt:
  0051", geändert; 0116 steht weiter `offen`). Dazu Dateien von 0079 (testentwickler),
  0122 (kernbauer, inkl. `kern/include/kern/festkomma.hpp`), Statuszüge des
  Projektmanagers und 12 leere `.claude`/`.mcp`-Platzhalter.
- `e00e7f9` mit Betreff „spielentwerfer: 0128-zaehlung-vier-je-land-statt-vier-r
  (29 Dateien)" enthält **null Bytes 0128-Arbeit**: das Pflichtlogbuch des Bauagenten
  (nach dem Urteil des 16. Laufs kein Verstoß), 15 leere Platzhalter,
  `aufgaben/0103-…md` (+180 Zeilen; ein **kernbauer**-Paket auf `werkzeugkette.cmake`),
  `aufgaben/0123-…md` (±2) und `befunde/messung-0123/messung.md` (+94).

Jede Fremddatei ist einem anderen, parallel gelaufenen Paket zuzuordnen; dem
Spielentwerfer ist keine inhaltliche Änderung außerhalb von `spiel.md` zuzurechnen. Das
Urteil über 0128 trägt deshalb — aber der Commit-Schritt des Baulaufs sammelt
offenkundig den ganzen Arbeitsbaum ein („Ein Lauf, ein Commit" ist damit nur noch dem
Betreff nach wahr). Das bricht drei Nachweisinstrumente: `git log -- <datei>` nennt den
falschen Urheber, die Verbotszonen-Prüfung per `diff --stat` je Commit wird wertlos, und
der Chronist liest Geschichte aus Betreffen, die nicht stimmen. **Vorschlag dazu:
`aufgaben/0131-baulauf-commit-nur-paketdateien.md`** (status: vorschlag).

## Wonach ich sonst gesucht habe, ohne Fund

- Zweitbelegung von `L` irgendwo in `spiel.md`: keine (siehe Bedingung 1).
- Weitere Schreibweisen von `4·R` und weitere symbolgebundene 780: keine.
- Die vom Projektmanager im Annahmevermerk zugesagte Reihenfolgesperre: `0118` führt
  `0128` tatsächlich in `haengt_an` — eingetragen, wie behauptet. Kein Befund.
- Leere Befunddatei-Falle (`ls -la befunde/`): keine bestehende Prüfung zu 0128; die
  bekannte 0-Byte-Datei `pruefung-0001-…runde5` ist Altbestand.
- Ob ein offenes Paket den Commit-Schritt schon berichtigt: kein Paket führt
  `agents/baulauf.py` in seiner `dateien`-Liste — alle Treffer sind Zitate in
  Begründungen. Darum der eigene Vorschlag.
