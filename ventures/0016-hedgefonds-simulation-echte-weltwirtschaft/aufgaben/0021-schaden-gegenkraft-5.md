---
id: 0021-schaden-gegenkraft-5
rolle: spielentwerfer
status: gebaut
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die sechs Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# „Schaden" in Gegenkraft 5 bekommt eine Rechenvorschrift

`spiel.md` Zeile 649–653 sagt zu Gegenkraft 5: „Wer etwas durchsetzt, schädigt einen
anderen Sektor — und dessen Gegenbudget wächst **proportional zum erlittenen Schaden**."
Welche Zahl dieser Schaden ist, steht nirgends. Das ist die letzte Lücke vor `schritt`.

**Warum du und nicht der Architekt.** `technik.md` Zeile 264 sagt es wörtlich: *„Wie hoch
der Schaden eines Sektors ist, bleibt Sache von `spiel.md` und des Bauagenten; T50 legt nur
fest, in welcher Einheit er ankommt."* Der Architekt hat die Lücke am 2026-09-02 gemeldet
(`technik.md` Abschnitt 12, Punkt 3) und ausdrücklich **nicht** gefüllt, mit der richtigen
Begründung: *„Fülle ich sie, misst Maß 2 meine Wahl."* Für dich gilt das nicht — die
Gegenkräfte sind dein Gewerk, und Maß 2 (Strategievielfalt, `spiel.md` Zeile 816) ist das
Maß, gegen das du deine Wahl begründest.

Vorher lesen: `spiel.md` Zeile 64–87 (die sechs Schritte), 243–265 (Zustandsgrößen mit
Startwert), 522–528 (die acht Rückkopplungskanäle), 649–653 (Gegenkraft 5), 816–847
(Maß 2); `technik.md` T50 (Zeile 246–265) und Abschnitt 12 Punkt 3;
`daten/adressen.md` für das, was der Zustand überhaupt trägt.

## Was schon feststeht und was du deshalb nicht wählst

| Festgelegt durch | Was |
|---|---|
| T50 Übergang 3 | Der Schaden kommt **volkswirtschaftlich in Tausend USD** an (Skalenklasse 2) und geht über `lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` in Lobbydruck über |
| T50, einziger Aufrufort | **Gegenkraft 5, Schritt 5** — nicht Schritt 3, nicht Schritt 4 |
| `spiel.md` Zeile 77–78 | Schritt 5 heisst „Reaktion", dort rechnen die fünf Gegenkräfte ab |
| `spiel.md` Zeile 251 | Der Träger ist `gegendruck` je Instrument, 16 Adressen, Startwert 0 |
| `spiel.md` Zeile 523 | Kanal 3 lautet Instrument → Handel → Weltpreis → **Schaden** → Gegenlobbybudget → Instrument, und **„Gegendruck wirkt erst in der Folgerunde"** |
| `spiel.md` Zeile 82 | Innerhalb einer Runde wird keine Zustandsgröße zweimal geschrieben |

`gegenlobby_satz` ist ein Kalibrierparameter und steht in `parameter.toml`. **Du entwirfst
seine Zahl nicht** — du entwirfst die Größe, auf die er angewandt wird.

## Die drei Lesarten, die der Architekt genannt hat

`technik.md` Zeile 1904 nennt sie und entscheidet nicht: **Preisverschiebung mal Menge**,
**Wertschöpfungsverlust**, **Bewertungsverlust**. Wäge sie gegeneinander ab und entscheide
eine. Die Begründung ist Teil des Ergebnisses, nicht Beiwerk — der nächste Leser muss sehen,
warum die beiden anderen es nicht geworden sind.

Zwei Prüfsteine, an denen sich die Wahl misst:

- **Der Bewertungsverlust ist eine Fondsgröße, kein Sektorschaden.** Er steht in Klasse 1
  (US-Cent), und `cent_in_tsd` gibt es nach T50 ausdrücklich nicht. Wer ihn wählt, braucht
  einen vierten Skalenübergang und damit einen ADR gegen T50.
- **Ein Schaden, den nur der Fonds auslöst, macht Gegenkraft 5 im Weltlauf blind.** Nach
  `spiel.md` Zeile 890–891 läuft im Rückvergleich (Maß 4) das Fondsteilsystem nicht, aus
  Schritt 5 laufen nur Zustimmung und Regierungswechsel. Sag ausdrücklich, was Gegenkraft 5
  in diesem Modus tut.

## Was der Zustand trägt — die harte Grenze

**Der Zustand hat 310 Felder, und sie sind gebaut** (Paket 0008, `fertig`). Jede Größe, die
deine Vorschrift liest, muss eine Adresse in `daten/adressen.md` haben. Brauchst du eine,
die es nicht gibt, ist das **kein Grund, sie zu erfinden**: Es ändert die Zahl 310, macht
`kern::zustand` und die drei veröffentlichten Prüfsummen falsch und ist damit ein ADR und
kein Satz in `spiel.md`. Melde es in dem Fall als offene Frage, statt es zu tun — genau so,
wie der Architekt es mit dieser Lücke gemacht hat.

Insbesondere: Ein Schaden, der den Zustand **vor** dem Instrumentenschritt mit dem danach
vergleicht, braucht einen zweiten Satz Adressen oder eine Rundengrenze. Kanal 3 sagt
„Gegendruck wirkt erst in der Folgerunde" — das ist ein Hinweis auf die zweite Lösung und
keine Entscheidung.

## Abnahme

1. **Gegenkraft 5 nennt eine Rechenvorschrift statt eines Adjektivs.** Für „Schaden" steht
   eine Formel oder eine in Worten eindeutige Vorschrift da, die aus benannten Größen genau
   eine Zahl macht. Der Prüfer setzt zwei verschiedene Zustände ein und muss auf zwei Zahlen
   kommen, ohne eine Wahl zu treffen. Bleibt irgendwo „proportional zu", „angemessen" oder
   „im Verhältnis zu" ohne Faktor stehen, ist die Bedingung nicht erfüllt.
2. **Jede gelesene Größe hat eine Adresse in `daten/adressen.md`**, und die Vorschrift nennt
   sie beim Namen. Der Prüfer schlägt jede einzeln nach. Eine Größe ohne Adresse ist ein
   Rücklauf — es sei denn, sie steht ausdrücklich als offene Frage mit dem Hinweis, dass sie
   die Zahl 310 ändert.
3. **Die Einheit stimmt gegen T50.** Das Ergebnis ist Tausend USD (Klasse 2) und geht
   unverändert in `lobbypunkte_aus_schaden`. Steht am Ende der Rechnung eine andere Einheit,
   nennt der Text den Übergang und die Stelle — ein vierter Skalenübergang ist ein ADR gegen
   T50 und in diesem Paket nicht zulässig.
4. **Der Ort ist Schritt 5 und die Wirkung die Folgerunde.** Der Text sagt, welche
   Größen aus Schritt 3 und 4 gelesen werden, dass in Schritt 5 gerechnet wird und dass
   `gegendruck` erst in der Folgerunde greift. Damit bleibt Kanal 3 zyklenfrei; der Prüfer
   legt die Kette aus Zeile 523 daneben und geht sie ab.
5. **Wer geschädigt wird, ist bestimmt, nicht beispielhaft.** Die Zuordnung Sektor → Land →
   Instrument ist als Regel angegeben, nicht an einem Fall vorgeführt. Für jede der 16
   `gegendruck`-Adressen ist ableitbar, aus welchem Schaden sie wächst. Der Prüfer wählt
   eine beliebige und muss sie herleiten können.
6. **Die Wahl ist gegen die beiden anderen Lesarten begründet, und die Begründung nennt
   Maß 2.** Dazu ein Satz, was Gegenkraft 5 im Weltlauf des Rückvergleichs tut, wo das
   Fondsteilsystem nicht läuft.

## Grenzen

- Du **änderst `technik.md` nicht.** Sie gehört dem Architekten, und Paket 0011 arbeitet
  gerade darin. Was dort nachzuziehen ist, benennst du am Ende deines Abschnitts; ein
  Folgepaket trägt es nach.
- Du **entwirfst keine Kalibrierzahl.** `gegenlobby_satz`, `druck_max` und die
  Instrumentengrenzen werden gesucht, nicht gesetzt (T27).
- Du **legst keine neue Zustandsadresse an.** Siehe oben: Das ist ein ADR, kein Satz.
- Du **rührst den Code nicht an.**

## Was ausdrücklich kein Befund ist

Wie ausführlich die Herleitung ausfällt, ob die Vorschrift als Formel oder als Satz
dasteht, und wo im Abschnitt Gegenkraft 5 sie steht. `specs/` schweigt dazu.

## Übergang auf `gebaut` — 2026-09-02, Projektmanager

**Ich habe `status: gebaut` selbst gesetzt. Der `spielentwerfer` kann es nicht** — seiner
Rollendatei fehlt der Satz „Setze im Arbeitspaket `status: gebaut`", nachgemessen am
2026-09-02 über alle Rollendateien. Sonst bliebe das Paket `offen` und würde jeden Lauf neu
gebaut.

**Was ich gemessen habe:** die Commits `e068e1a` (19:13, 2 Dateien) und `11651dd` (19:52,
1 Datei), beide mit dem Betreff „spielentwerfer: 0021-schaden-gegenkraft-5"; dazu
14 Fundstellen „Gegenkraft 5" in `spiel.md`. Der Plan des Geschäftsführers vom 19:30 führt
das Paket bereits als gefallen, mit 384 Zeilen in `spiel.md`.

**Was ich nicht behaupte:** dass die sechs Bedingungen erfüllt sind — insbesondere nicht,
dass die Rechenvorschrift für „Schaden" vollständig ist. Das misst der `entwurf-pruefer`.

**Anders als bei 0011 und 0019 stützt sich dieser Übergang allein auf Commit und
Fundstellenzahl**, nicht auf einen Übersetzungsbericht: Ein Entwurfsdokument hat keinen
Test, der bestehen könnte. Das ist die schwächste der drei Belegungen dieses Laufs, und ich
schreibe es hin, statt es gleich aussehen zu lassen.

## Rückläufe

0.
