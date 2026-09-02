---
id: 0024-notenbanken-unter-reihe-2b
rolle: datenbauer
status: offen
haengt_an: [0018-lizenzbefund-klaerungsliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/lizenzbefund-reihen.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Ein Satz zählt drei offene Stellen, wo sieben offen sind

Vorgabe: `befunde/pruefung-0018-lizenzbefund-klaerungsliste-2026-09-02.md`, Befund 1.

**Das ist kein Rücklauf.** Paket 0018 ist am 2026-09-02 mit `urteil: geprueft` abgenommen;
alle vier Bedingungen halten. Der Befund liegt **neben** dem Kriterium: Bedingung 1
verlangt die beiden Lieferantengruppen ausdrücklich für „Reihe 1 und 2a", und dort stehen
sie. 2b und 2c sind vom Wortlaut nicht erfasst, ein Rücklauf wäre eine Kriterienerhöhung
gewesen. Deshalb ein eigenes Paket.

## Der Befund, in drei Sätzen

Das `Source`-Feld von `NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS` nennt die Notenbanken als
**eigene, zweite Angabe** — deutlicher als bei Reihe 1 und 2a, wo sie im selben Halbsatz
mit den Ämtern stehen (`daten/lizenzbefund-reihen.md`, Zeilen 177–179):

> Country official statistics, National Statistical Offices (NSOs);
> **National Accounts data files, Central Banks;**
> Staff estimates, World Bank (WB)

Paket 0018 hat daraus an drei Stellen den richtigen Schluss gezogen — Reihe 1 („und
**keine einzige Notenbank**", Zeile 118), Reihe 2a („keine Notenbank", Zeile 161) und
Klärung 4 („Die Notenbanken sind also ein eigener Lieferant und nicht von den Ämtern mit
abgedeckt", Zeile 542; „**Sieben Abrufe, nicht drei.**", Zeile 554). An der vierten Stelle
nicht: Die Begründung unter 2b/2c (Zeilen 189–192) trägt weiter die alte Zählung —

> `daten.md` hat von den vier Modellländern genau ein statistisches Amt geprüft:
> **Destatis, Nr. 5, positiv** … Für die Ämter der drei übrigen Länder liegt nichts vor.

— und ist damit die **einzige** Begründung der Datei, die den zweiten Lieferanten
verschweigt, ausgerechnet unter dem Code-Paar, dessen `Source` ihn am klarsten ausweist.

## Warum das nicht folgenlos ist

Die Klärungsliste sagt, Klärung 4 allein hebe 2b und 2c. Ob sie das tut, hängt daran, wie
viele Stellen für 2b/2c zu klären sind — und die Begründung, die das ausweisen soll, sagt
drei statt sieben. **Die beiden Zahlen derselben Datei widersprechen einander**, die
richtige steht vierzig Bildschirmseiten später. Wer Reihe 2b/2c von ihrer eigenen Stelle
aus bepreist, bepreist sie zu billig.

Zweite Folge: `daten/reihen.toml` wird aus dieser Datei fortgeschrieben. Wandert die Zahl
drei dorthin, steht sie in der maschinenlesbaren Fassung und wird zitierbar.

## Was du tust

Bring die Begründung unter 2b/2c auf denselben Stand wie Reihe 1, 2a und Klärung 4: beide
Lieferantengruppen benannt, die Zahl der offenen Stellen richtig. **Ein bis zwei Sätze.**

Die Belege stehen vollständig in derselben Datei (Zeilen 177–179 für das `Source`-Feld,
542 für den Schluss, 547–556 für die Tabelle der acht Stellen und die eine geprüfte).
**Kein Abruf, keine Recherche, keine neue Quelle** — und keine der sechs
`Source`-Zitatzeilen wird angefasst; sie sind am 2026-09-02 in Paket 0014 gemessen worden
und tragen unverändert.

Das **Urteil** `unklar` für 2b/2c änderst du nicht, und den Grund dafür änderst du auch
nicht: Ob eine nationale Statistikbehörde im Sinne der Weltbank-Ausnahme Drittanbieter
ist, ist eine Rechtsfrage und gehört dem Betreiber. Dieses Paket korrigiert eine
**Abzählung**, kein Urteil.

## Abnahme

1. **Die Begründung unter 2b/2c nennt beide Lieferantengruppen** — die statistischen
   Ämter und die Notenbanken — und die Zahl der dort offenen Stellen stimmt mit der
   Tabelle unter Klärung 4 überein: acht Stellen für vier Modellländer, davon eine
   geprüft (Destatis), also **sieben offen**.
2. **Keine Begründung der Datei zählt mehr offene Stellen einer Reihe, ohne die
   Notenbanken mitzuzählen, deren `Source` sie nennt.** Nachweis: Jede Fundstelle von
   „liegt nichts vor" wird einzeln gegen das `Source`-Zitat *ihrer* Reihe gelegt; nennt
   das Zitat Notenbanken, nennt sie die Begründung auch. Reihen ohne Notenbanken im
   `Source` bleiben unberührt — dies ist keine Aufforderung, überall „sieben"
   hinzuschreiben.
3. **Alle Zahlen ausser dieser einen sind unverändert.** Die zwölf
   `reihen_*`/`sollreihen_*`-Felder des Frontmatters, `codes_abgerufen_reihen: 6`,
   `codes_abgerufen_gegenprobe: 2`, die Sollreihenzahlen der Abschnitte, die vier „Allein:"-
   Zeilen der Klärungsliste, die Probe 16 + 8 = 24 und die Kaskade 16 → 8 → 1 sind
   zeichengleich. Der Prüfer rechnet die Kaskade nach und darf auf keine Abweichung
   stossen.
4. **Kein neuer Abruf und kein neues Urteil.** Die Datei enthält keine URL und kein
   Abrufdatum, das vorher nicht darin stand; die sechs `Source`-Zitatzeilen sind
   unangetastet; das Urteil `unklar` für 2b/2c und seine gemeinsame T26-Folgezeile
   (Zeile 196–198) stehen unverändert.

## Was ausdrücklich kein Befund ist

- **Dass die Reihenfolge der Klärungsliste bleibt, wie sie ist.** Der Prüfer der 0018 hat
  erwogen, Klärung 2 vorzuziehen, und es selbst als Geschmack und nicht als Befund
  eingeordnet.
- **Dass Reihe 5 und Reihe 12 von der Klärungsliste nicht erreicht werden.** Beide tragen
  null Sollreihen und null Prüfgegenstände; die Datei sagt das an ihrer eigenen Stelle.
- **Die Form** — ob die Korrektur als eigener Satz, als Klammerzusatz oder als
  Aufzählungszeile steht. `specs/` schweigt dazu.

## Rückläufe

0.
