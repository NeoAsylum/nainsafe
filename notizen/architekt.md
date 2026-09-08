# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 14236 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (sechster Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0158, Rücklauf 1: ein Befund, behoben, zwei Wörter

Der Prüfer hatte recht. `seven` → `eight` und `101` → `117`; sonst nichts. Beide Zahlen
waren aus dem Quellbefund `befunde/beschraenktheit/bruch-2026-09-06.md` wörtlich
übernommen („101 Adressen der **sieben** Wertebereichsschranken") — und der ist älter als
Schranke 8, die Paket `0172` zwanzig Zeilen über meinem Absatz in dieselbe Tabelle
eingetragen hat, während ich in der Warteschlange stand.

### Der übertragbare Fund: eine zitierte Zahl altert an der Stelle, an die du sie schreibst

**Ein Befund ist auf sein Datum geeicht, das Zieldokument nicht.** Meine Zahl war am
2026-09-06 richtig und am 2026-09-08 falsch, ohne dass sich an ihr etwas geändert hätte —
geändert hat sich die Tabelle, auf die sie zeigt. Der Absatz sagte deshalb „seven bounds"
und zwölf Zeilen später „eight bounds", und beides stand unter einer Tabelle mit acht
Zeilen.

**Regel für den nächsten Lauf: Wer eine Anzahl aus einem Befund übernimmt, zählt sie einmal
am Zieldokument nach — und grept die Datei nach derselben Anzahl an anderer Stelle.** Beides
war hier billig und hätte den Rücklauf gespart: die Adressspalte summiert 117, und die
Begründung unter T18b (`:4922`, aus `0177`) trug „the eight bounds of T30 check 2 — **117
addresses**" schon, bevor ich schrieb. Die Datei hat sich selbst widersprochen, an zwei
Stellen, die beide ich hätte lesen können. **Das ist die teure Variante von „sag die Zahl,
nicht die Geschichte": die Zahl war die Geschichte eines anderen Datums.**

Merkposten dazu: der Prüfer hat die 65 ausdrücklich als *nicht* veraltet nachgewiesen
(65 = 1 + 32 + 32, Schranke 8 liegt mit ihren 16 Adressen **innerhalb** der `weltlauf`-Maske).
Ich habe sie deshalb nicht nachgerechnet — auf Anweisung des Projektmanagers, und es war
richtig: eine Zahl, die ein Prüfer gegen die Maskentabelle belegt hat, noch einmal zu zählen,
kostet einen Lauf und findet dasselbe.

### Unsicher, damit der Projektmanager es sieht — zwei Stellen

1. **Zwei Dreiergruppen sechs Zeilen auseinander, und ich habe sie stehen lassen.** `:2471`
   (aus `0172`) sagt „Bounds 1, 5 and 8 are the three that without a test would go wrong
   silently"; mein `:2477` sagt „decides three of its eight bounds away" und meint 5, 6, 7.
   Kein Widerspruch — zwei verschiedene Dreiergruppen —, aber ein Leser, der quer liest,
   verwechselt sie. Ausserhalb des Umfangs („and nothing else"), deshalb nicht angefasst.
2. **Schranke 8 kommt in meinem Absatz nicht vor.** Nach der Berichtigung stehen 117 − 65 =
   52 Adressen innerhalb der Maske, darunter die 16 der Schranke 8; der Text zählt nur die
   drei blinden Schranken auf. Das ist vollständig, aber implizit. Wer es ausdrücklich will,
   braucht einen halben Satz — er war nicht beauftragt.

### Fährten

- **Unverändert offen und nicht von mir gelöst:** `exogen_ab_runde = bruchjahr − startjahr
  + 1` (T40) macht 1997 zu Runde **1**, `R = stuetzstellen − 1` mit den Spieldritteln macht
  es zu Runde **0**. Beides zusammen geht nicht, und es entscheidet, ob die **176** oder die
  vom Quellbefund genannte 175 stimmt. Dieser Lauf hat den Satz nicht berührt; der Prüfer hat
  die 176 als in sich stimmig abgenommen und die Abweichung als benannt (`:2519`) durchgehen
  lassen.
- **Meldung 1 aus Abschnitt 28 bleibt ein Paketvorschlag:** keine der acht Prüfungen misst
  Beschränktheit über einen langen Horizont an Fonds, Kanal 8 und Korbwert. Prüfung 6 hat die
  200 Runden und ist gegen die drei blind; alle `spielmodus`-Läufe laufen R = 24 Runden.
- **Die Zählklausel in Abschnitt 27 zählt `T6[0-2]` über die ganze Datei und steht selbst im
  gezählten Bereich. Dieser Lauf hat sie nicht berührt** — in keinem der zwei Edits steht
  `T60`, `T61` oder `T62`. Wer nachprüft, misst weiter 48 Zeilen / 49 Treffer.
- **Der Vorgänger-Faden steht:** T15, T16 und die 310 zählen nicht in `L_R` — `0116` und
  Bedingung 1 des Horizonts in Abschnitt 26.
- Ältere Fährten: `notizen/archiv/architekt-2026-09-08-3.md`.

