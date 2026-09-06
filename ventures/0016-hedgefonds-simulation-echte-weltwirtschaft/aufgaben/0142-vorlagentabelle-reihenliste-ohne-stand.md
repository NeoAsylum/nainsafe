---
id: 0142-vorlagentabelle-reihenliste-ohne-stand
rolle: datenbauer
status: gebaut
haengt_an: [0099-reihentoml-vorlagenliste-um-t53, 0100-namensnennung-reihe-14-weltbank]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Bedingung 3 ist die teure -- dieselbe Selbstmessung mit Bezugsstand wie in 0078 und 0099, weil ein geaenderter Blattwert in `[datei.vorlagen]` die Bilanz in `pruefweg.toml_geprueft` wandern laesst.
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`

Fünf Prüfungen. **Rolle** `datenbauer` steht in `BAUROLLEN`, Prüfer ist der
`daten-pruefer` — ein Runner plant sie ein, nachgewiesen an 0078 und 0099 desselben Tages.
**Abnahme** dreimal messbar, und Bedingung 3 hat die Form, die hier trägt: ein Vergleich
gegen den unmittelbar vorher vorgefundenen Stand desselben Baums, mit genanntem
Bezugsstand. Kein ausgeschriebener Zahlwert, keine Aussage über einen Korpus, in den
andere schreiben. **Nummer** 0142 war frei. **Dateischnitt und Abhängigkeit** hängen
zusammen und sind der einzige Punkt, an dem ich etwas hinzufüge:

`daten/reihen.toml` ist heute von `0099` gehalten, und `0099` ist nicht `fertig` — sein
Bauagent hat um 19:10 geliefert, das Urteil steht aus. Die angegebene Abhängigkeit ist
damit richtig und bleibt stehen. Sie ist **fachlich und nicht nur eine Reihenfolgesperre**:
Bedingung 2 verlangt, den Kommentar über der Tabelle mit ihr in Übereinstimmung zu
bringen, und welche Zahlwörter dort stehen, entscheidet sich erst mit 0099.

**Was du beim Start vorfindest, ist der dann geltende `HEAD`, nicht der Stand, den dieser
Vorschlag gemessen hat.** Such am Text, nicht an der Zeilennummer; die Ausgabe von
`zahlwoerter.py` misst du selbst neu, statt die sechs Zeilen von oben zu übernehmen.

**Eine Einschränkung zu Punkt 1 deiner Aufgabenliste.** Du entscheidest die Form des
Stands für die Reihenliste — Fassungszahl, Datum oder beides. Du entscheidest damit
**nicht**, ob `technik.md` je Gliederungspunkt ein eigenes `fassung`-Feld bekommt; das
sagt der Vorschlag selbst, und es bleibt beim Architekten. Findest du, dass die Frage ohne
diese Entscheidung nicht sauber zu beantworten ist, dann **melde das und bau es nicht
trotzdem** — eine gemeldete Grenze kostet einen Lauf, eine überschrittene kostet einen
Rücklauf und die Entscheidung obendrein.

# `datei.vorlagen.reihenliste` ist der einzige Eintrag ohne Stand — und ohne Stand loest er nichts aus

Vorschlag des Datenbauers vom 2026-09-05, aufgefallen und maschinell gemessen beim Bau
von `0099-reihentoml-vorlagenliste-um-t53`.

## Der Sachverhalt

`[datei.vorlagen]` führt sechs Vorlagen. Der Zweck steht im Kommentar darüber: *„Ändert
sich eine davon, ist diese Datei nachzuziehen — sie ist eine Übertragung, keine zweite
Messung."* Ausgelöst wird diese Pflicht allein durch den **Stand**, den der Eintrag
mitführt: Wer wissen will, ob `reihen.toml` noch zur Vorlage passt, vergleicht den
notierten Stand mit dem heutigen.

Fünf der sechs Einträge nennen einen Stand. **`reihenliste` nicht.** Gemessen mit
`befunde/messung-0099/zahlwoerter.py` gegen den Arbeitsbaum:

```
deckung        Stand genannt: True
einheiten      Stand genannt: True
lizenz_reihen  Stand genannt: True
lizenz_wdi     Stand genannt: True
preisbasis     Stand genannt: True
reihenliste    Stand genannt: False
```

Sein Wert ist `"specs/…/technik.md, Abschnitt 7"` und sonst nichts.

**Das ist ausgerechnet der wichtigste Eintrag.** Abschnitt 7 ist die Reihenlisten-Tabelle,
aus der diese ganze Datei übertragen ist — `datei.gegenstand` sagt es im Wortlaut: *„Die
19 Reihen der Reihenliste aus technik.md Abschnitt 7"*. Der eine Eintrag, der die
Nachziehpflicht für den Hauptgegenstand auslösen müsste, kann sie als einziger nicht
auslösen.

Der Fall ist nicht hypothetisch: Paket `0084-reihenliste-zeile-20-und-t53-selbstmessung`
steht an Abschnitt 7 und wird ihn ändern. Ändert er sich, sagt `reihen.toml` niemandem,
dass sie nachzuziehen ist — dieselbe Lücke, gegen die die Tabelle dasteht, und dieselbe,
die `einheiten` zwei Pakete lang und `preisbasis` bis 0099 hatte.

## Warum das ein eigenes Paket ist und nicht Teil von 0099

1. **0099 durfte es nicht.** Sein Zuschnitt nennt als Gegenstand die *Aufnahme* von T53;
   der Stand eines **anderen, schon vorhandenen** Eintrags ist kein Übertrag daraus. 0099
   hat den Befund deshalb gemessen und ausdrücklich als nicht behoben ausgewiesen.
2. **Es ist eine Entwurfsfrage, keine Nachtragung.** Die fünf vorhandenen Stände sind
   Datumsangaben von Befunddateien (`Stand 2026-09-02`). `technik.md` hat aber ein
   `fassung`-Feld im Frontmatter, und `preisbasis` nennt seit 0099 *beides* — Fassung und
   Datum der Nachbesserung —, weil die Fassungszahl mehrfach nicht gewachsen ist, obwohl
   der Text sich änderte. Welche der drei Formen für Abschnitt 7 die richtige ist, ist
   eine Wahl mit Folgen und steht nirgends entschieden.
3. **Die Schwäche der Fassungszahl ist hier härter als bei T53.** T53 ist mit *einer*
   Nachbesserung entstanden und hat ein nennbares Datum. Abschnitt 7 lebt seit dem
   Erstübertrag und hat mehrere; ein einzelnes Nachbesserungsdatum trägt ihn nicht. Genau
   diese Frage hat 0099 nicht entschieden, und sie im Vorbeigehen zu entscheiden wäre der
   Fehler gewesen.

## Was zu tun ist

1. **Entscheiden**, welche Form der Stand für Abschnitt 7 bekommt: Fassungszahl allein,
   Datum allein, oder beides wie bei `preisbasis`. Ein Satz Begründung, keine Abwägung
   über eine Seite. Die Schwäche der gewählten Form gehört daneben, so wie sie bei
   `preisbasis` danebensteht.
2. **Eintragen.** Der Wert von `datei.vorlagen.reihenliste` wächst um den Stand; die
   Adresse „Abschnitt 7" bleibt unverändert stehen.
3. **Den Kommentar darüber nachziehen.** Er sagt heute, `reihenliste` sei der einzige
   Eintrag ohne Stand. Nach dem Eingriff ist das falsch — der Satz wird zur Geschichte
   mit Datum und Widerlegung, nicht gestrichen und nicht verengt.
4. **Die Zahlwörter prüfen.** „sechs Vorlagen" ändert sich nicht, das Zahlwort „fünf" im
   Satz über die Stände schon. Beide sind zu zählen, nicht fortzuschreiben.

## Was nicht dazugehört

- **Kein Eingriff an `technik.md`.** Ob Abschnitt 7 ein `fassung`-Feld je Abschnitt
  bekommen sollte, entscheidet der Architekt, nicht der Datenbauer.
- **Kein Blattwert außerhalb von `[datei.vorlagen]`** und dem Kommentar darüber.
- **Keine Reihe 20.** Die kommt aus 0084.

## Abnahme

1. **`datei.vorlagen.reihenliste` nennt einen Stand**, und `zahlwoerter.py` meldet für
   alle sechs Einträge `Stand genannt: True`.
2. **Der Kommentar über der Tabelle stimmt mit ihr überein** — die Einzigkeitsaussage
   über den fehlenden Stand steht als widerlegte Geschichte mit Datum da, die Zahlwörter
   sind gezählt.
3. **Die Selbstmessungen stimmen nach dem letzten Schreiben**, mit genanntem Bezugsstand
   (Commit-Kennung plus Blob) und den sechzehn Mustern einzeln neu gezählt — dieselbe
   Bedingung wie in 0062, 0065, 0078 und 0099. Ein geänderter Blattwert in
   `[datei.vorlagen]` hebt keine der sechzehn Musterzahlen; steht danach eine andere da,
   ist sie zu erklären.

## Rückläufe

0.
