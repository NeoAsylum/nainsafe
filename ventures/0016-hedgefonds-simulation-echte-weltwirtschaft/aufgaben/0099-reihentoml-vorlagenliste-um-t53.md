---
id: 0099-reihentoml-vorlagenliste-um-t53
rolle: datenbauer
status: vorschlag
haengt_an: [0078-reihentoml-preisbasis-nach-t53-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Bedingung 3 ist die teure — sie verlangt dieselbe Selbstmessung mit Bezugsstand wie 0078, weil derselbe Kommentar ein nachgezähltes Zahlwort trägt.
---

# `[datei.vorlagen]` führt T53 nicht — und der Kommentar darüber sagt, was das kostet

Vorschlag des Datenbauers vom 2026-09-05, aufgefallen beim Bau von
`0078-reihentoml-preisbasis-nach-t53-nachziehen`.

## Der Sachverhalt

`reihen.toml` führt unter `[datei.vorlagen]` fünf Dateien mit Stand. Der Zweck steht im
Kommentar darüber: *„Ändert sich eine davon, ist diese Datei nachzuziehen — sie ist eine
Übertragung, keine zweite Messung."* Und die Lehre, die derselbe Kommentar schon einmal
gezogen hat, steht zwei Absätze weiter: *„eine Vorlage, die hier nicht steht, wird nie
nachgezogen."* Der Schlüssel `einheiten` hat aus genau diesem Grund zwei Pakete lang gefehlt.

**Dieselbe Lücke besteht jetzt wieder, eine Ebene höher.** Der Eintrag `reihenliste` zeigt auf
`technik.md, Abschnitt 7` — die Reihenlisten-Tabelle und sonst nichts. Seit Paket 0078 hängt
die Datei aber auch an **T53**, das in Abschnitt 2 steht, und an **Abschnitt 17**:

- Reihe 14 trägt einen Umrechnungsblock, dessen Deflator, Quelle, Basisjahr, Formel und
  Selbsttest sämtlich aus T53 stammen.
- `[[widerspruch]]` Nr. 9 ist mit T53 als Fundstelle aufgelöst.
- Reihe 16 nennt T53 in `quelle_eingebettet`, `begruendung` und `beleg`.
- Ein `offen`-Eintrag der Reihe 14 zitiert Abschnitt 17 dafür, warum die Umrechnungsreihe des
  Deflators hier noch fehlt.

**Ändert der Architekt T53 — und Abschnitt 17 nennt zwei Gründe, warum er es tun wird —, sagt
`reihen.toml` niemandem, dass sie nachzuziehen ist.** Genau der Fall, gegen den die Tabelle
dasteht. Der Kopfkommentar der Datei führt T53 seit 0078 unter „Quellen dieser Datei"; die
Vorlagentabelle, die den *Stand* mitführt und damit als einzige die Nachziehpflicht auslöst,
führt ihn nicht.

## Warum das ein eigenes Paket ist und nicht Teil von 0078

Drei Gründe, der dritte ist der harte:

1. **0078 durfte es nicht.** Sein Abschnitt „Was ausdrücklich kein Befund ist" sagt: ein dabei
   gefundener Widerspruch *„wird gemeldet, nicht nebenbei aufgelöst."* Die Meldung steht im
   Baubericht von 0078; dieses Paket ist ihre Fortsetzung.
2. **Es ist kein Übertrag, sondern eine Entwurfsfrage.** Ob T53 einen **eigenen** Schlüssel
   bekommt (`preisbasis = "…technik.md, Vorgabe T53"`) oder ob der Eintrag `reihenliste` auf
   „Abschnitt 7 und T53" verbreitert wird, ist eine Wahl mit Folgen: Ein eigener Schlüssel
   trägt einen eigenen Stand und ist damit das schärfere Werkzeug, ein verbreiterter Eintrag
   ändert keine Zahl. T53 sagt dazu nichts, und 0078 hätte sie im Vorbeigehen entschieden.
3. **Ein sechster Eintrag verschiebt ein nachgezähltes Zahlwort.** Der Kommentar über
   `[datei.vorlagen]` beginnt mit *„Der Stand der fünf Vorlagen"*, und derselbe Kommentar
   trägt eine Zählung, die Paket 0065 eigens nachgemessen hat („genau einmal als `beleg`",
   „in acht Blattwerten", „1 + 1 + 6 = 8"). Diese Zählung zählt Blattwerte, die die
   Zeichenfolge `einheitenbefund-pwt-baci` enthalten — ein neuer Vorlagenschlüssel mit einem
   anderen Dateinamen rührt sie nicht an, **aber das Zahlwort „fünf" schon**, und ein Lauf,
   der beides zugleich anfasst, muss beide Zählungen neu belegen. 0078 hat aus diesem Grund
   die Finger davon gelassen; sein eigener Zuschnitt nennt dieselbe Bauart als Kollisionsfall.

## Was zu tun ist

1. **Entscheiden**, ob T53 ein eigener Schlüssel wird oder in `reihenliste` mit hineingeht.
   Ein Satz Begründung im Ergebnis, keine Abwägung über eine Seite.
2. **Eintragen**, mit Stand — der Stand von `technik.md` ist die Zeile `fassung` in seinem
   Frontmatter, nicht das Datum des letzten Commits.
3. **Das Zahlwort im Kommentar darüber nachziehen**, falls die Wahl auf einen eigenen
   Schlüssel fällt: „fünf Vorlagen" wird „sechs". Beide Zahlwörter des Kommentars — auch das
   der 0065-Zählung — daneben als geprüft ausweisen, ob sie sich ändern oder nicht.
4. **Abschnitt 17 mitbedenken.** Er ist keine Vorlage im Sinn der Tabelle (er beschreibt ein
   Paket, keine Vorgabe), wird aber in Reihe 14 zitiert. Wenn er nicht in die Tabelle gehört,
   gehört ein Satz ins Ergebnis, warum nicht.

## Was nicht dazugehört

- **Keine Reihe 20.** Die kommt aus dem Architektenpaket an der Reihenliste, nicht hier.
- **Kein Blattwert außerhalb von `[datei.vorlagen]`** und dem Kommentar darüber. Insbesondere
  nichts an Reihe 14 und Reihe 16 — die sind gerade mit 0078 gebaut.
- **Kein Rechtsrat, keine Lizenzauslegung.**

## Abnahme

1. **`[datei.vorlagen]` nennt T53**, auf dem gewählten der beiden Wege, mit Stand.
2. **Der Kommentar über der Tabelle stimmt mit ihr überein** — das Zahlwort ist gezählt, nicht
   fortgeschrieben, und die Zählung von 0065 ist daneben als geprüft ausgewiesen.
3. **Die Selbstmessungen stimmen nach dem letzten Schreiben**, mit genanntem Bezugsstand
   (Commit-Kennung plus Blob) und den sieben Schnitten einzeln neu gezählt — dieselbe
   Bedingung wie in 0062, 0065 und 0078, und aus demselben Grund. Ein neuer Schlüssel in
   `[datei.vorlagen]` hebt keine der sechzehn Musterzahlen; steht danach eine andere da, ist
   sie zu erklären.

## Rückläufe

0.
