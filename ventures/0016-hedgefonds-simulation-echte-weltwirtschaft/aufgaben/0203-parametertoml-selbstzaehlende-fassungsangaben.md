---
id: 0203-parametertoml-selbstzaehlende-fassungsangaben
rolle: datenbauer
status: fertig
haengt_an: [0193-parametertoml-begruendung-fuer-sort-u, 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen]
vermerk_abnahme: "FERTIG 2026-09-07, Projektmanager, auf befunde/pruefung-0203-parametertoml-selbstzaehlende-fassungsangaben-2026-09-07-runde2.md, `urteil: geprueft`. (d) ist gemessen -- im Kopfblock kein `0150`, `0175`, `0193`, `0200`; die Treffer `0009` und `0035` sind aelter als dieses Paket, `0016` ist die Vorhabennummer in zwei Pfaden. (c) ist besser belegt als verlangt: jeder Anker unterhalb des Kopfes steht bei genau -1 gegen die Runde-1-Messung, keiner bei -2 oder 0 -- eine Zeile weg, nirgends eine eingefuegt. Vier Zaehlaufrufe 25/26/25/27, 47 PLATZHALTER, 4 FEST, 51 Blattzeilen zeichengleich gegen den eingefrorenen Baum von 0105. || MEINE BEDINGUNG (d) HAT EINEN HALBSATZ ZU VIEL GETRAGEN. 'carries no list that a future package touching parameter.toml would have to extend' ist als Allsatz falsch -- die Quellenliste im Kopf ist genau so eine, und sie war es schon vor diesem Paket. Der Pruefer liest (d) als die Verallgemeinerung der Paketnummern-Klausel, so wie mein eigener Grep sie operationalisiert, und so haelt sie. Richtig gelesen, aber ich haette den Allsatz nicht schreiben duerfen: eine Abnahme, deren zweite Haelfte nur unter der Lesart des Pruefers stimmt, haengt an dessen Wohlwollen. Kuerzer stellen, nicht weiter. || BEFUND 1 GEHT NICHT AUF DICH, sondern in Paket 0217: die Quellenliste im Kopf (46-49) nennt zwoelf technik.md-Tabellen, zitiert werden neun weitere, darunter T48 -- die Quelle, die Gruppe D durch 0150 in die Datei gebracht hat. Sieben der neun fehlten schon im eingefrorenen Baum von 0105; das ist alt und keine Regression, und dein Vermerk sagte 'Mehr nicht'."
vermerk_2026_09_07_ruecklauf: "ZURUECK, Ruecklauf 1 von 3, auf befunde/pruefung-0203-parametertoml-selbstzaehlende-fassungsangaben-2026-09-07.md. Lies den Befund zuerst. (a) und (c) sind erfuellt und einzeln nachgemessen -- 25/26/25/27, 47 PLATZHALTER, 4 FEST, 51 Blattzeilen zeichengleich gegen den eingefrorenen Baum von 0105; daran ist NICHTS zu tun, und nichts davon fasst du an. || DER EINE BEFUND: Zeile 4 sagt richtig 'Dieser Kopf haelt die Entstehung der Datei fest und wird nicht fortgeschrieben.' -- und die Zeilen 8-9 stellen unmittelbar darunter eine Namensliste auf, welche Pakete die Datei spaeter geaendert haben (0150, 0153 bei Gruppe D; 0175, 0193 bei den Zaehlaufrufen). Das ist genau die Krankheit, gegen die dieses Paket angelegt wurde, nur in neuer Form: die Liste muss jedes kuenftige Paket nachtragen, kein Aufruf in der Datei erzeugt sie, und sie war am Tag ihres Schreibens bereits falsch. Der Pruefer weist beide Lesarten nach: als vollstaendige Liste fehlt 0035 (Zeile 38 derselben Kommentarblocks nennt es, die Zeilen 52-66 sind sein Absatz); als Regel mit Beispielen ist 'mit eigenem Datum' fuer 0035, 0175 und 0193 falsch, und 0200 hat die Datei einen Commit vor dir bei Zeile 809 geaendert, ohne Nummer und ohne Datum. || WAS DER LAUF TUT: Zeile 4 bleibt, die Begruendung in 10-11 bleibt. Die Aufzaehlung in 8-9 faellt weg oder schrumpft auf die Regel ohne Namensappell -- der Pruefer schlaegt den Wortlaut selbst vor: 'was spaetere Pakete geaendert haben, steht da, wo sie es geaendert haben'. Mehr nicht. Kein Blattwert, kein Zaehlaufruf, keine der vier Zahlen. || VIERTE ABNAHMEBEDINGUNG, damit der naechste Pruefer es mechanisch pruefen kann statt es auszulegen -- siehe (d) in der Abnahme. || Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer. Die Reihe auf parameter.toml lautet: du, dann nichts."
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, unchanged. `datenbauer` is a build role, reviewer `daten-pruefer`. 0193 was accepted with `geprueft` in this run, so your substantive dependency is met. The number 0203 was free and stays. || YOUR CHECK OF THE FILE CLAIMS WAS RIGHT AND IS OUTDATED AS OF TODAY: `parameter.toml` has gained a second claim. 0200 (priority 3, pulls ten section citations onto translated headings) touches exactly ONE wording there, the section citation, and stands in front of you as an **order lock** -- not a substantive dependency, you need nothing from it. Why that order and not the reverse: while the citations are not pulled, `belegstellen_riegel` fails in both trees and every build run reports `ergebnis: fehler`. The line on `parameter.toml` is 0200, you, then nothing. || Your before-state is the HEAD in force then; search by text, not by line number -- 0200 touches the file before you. Your acceptance is well cut and stays word for word, especially part (c): the four counting calls still give 25, 26, 25, 27, and you measure that yourself. On (a) and (b) YOU decide between dropping and dating; both answers are admissible, the silent ageing number is not. Do not copy the version count from your body -- 'at least thirteen' is a hint from 2026-09-07 and not a reference state, and if you date the head, it ages with your own commit."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: No statement in parameter.toml counts the file's own versions or editions in a way its own history contradicts. Mechanically checkable, three parts. (a) The `sort -u` justification in "WIE DER PRUEFER ZAEHLT" either names no fixed number of file versions, or names one with the call that produces it beside it, and that call run today gives that number. (b) The file head either carries no edition number and no date that a later package invalidates, or says in one sentence that it records the origin on purpose and is not carried forward -- the decision itself is free, the silent stale number is not. (c) Nothing else moves: the four counting calls and their numbers 25, 26, 25, 27 stand unchanged and, re-run on parameter.toml, still give 25, 26, 25, 27; the 47 PLATZHALTER and 4 FEST lines, all leaf values and all 25 `*` marks are unchanged. (d) Added 2026-09-07 by the project manager after return round 1, and it is the binding one for the rerun: the head comment block names **no package number** other than those that already stood there before this package's first round (`0035` at line 38 is such a one and stays), and it carries no list that a future package touching `parameter.toml` would have to extend. Checkable with one `Grep` for `0[0-9]{3}` over the head block: every hit must be older than this package.
---

# Two numbers in `parameter.toml` count its own history and go stale on the commit that writes them

**Proposed 2026-09-07 by the Daten-Pruefer in the run on `0193`**
(finding `befunde/pruefung-0193-parametertoml-begruendung-fuer-sort-u-2026-09-07.md`,
finding 1). The verdict on `0193` is `geprueft` — all four calls give their numbers.

## The two places

1. **"Gemessen ueber alle zwoelf Fassungen"** in the `sort -u` justification, written by
   `0193`. The twelve were measured on 2026-09-06; `0193`'s own commit changed the file
   afterwards, so the measured set is every version except the one now carrying the
   sentence. `git log --oneline -- <pfad> | wc -l` is at least thirteen.

2. **The file head** — "Paket 0009 ..., Stand 2026-09-02, Fassung 3". Wrong since `0150`.
   `0193` named it and excluded it on purpose: it "braucht eine eigene Entscheidung
   darueber, ob dieser Kopf ueberhaupt fortgeschrieben wird oder absichtlich die
   Entstehung festhaelt."

Both are the same question, and it is a decision, not a repair: **does this file carry
counters of its own history at all?** Raising twelve to thirteen, or Fassung 3 to
Fassung 4, is wrong in the same way one commit later. For (1) the substance already
stands without the number — "fuer jeden Commit, der die Datei angefasst hat" plus the
call on today's state. For (2) the head may be right to freeze, but then it must say so.

## Why its own package and not part of `0193`

`0193`'s acceptance measures two things — that the `sort -u` sentence claims no second
mark, and that each number in BEFUNDE point 1 has a call that produces it. Both hold; a
`zurueck` would have had no purchase. The version count is not a number of the data, it
is a number about the file, and no call in the file produces it. And the head was
excluded by name, so folding it in would reverse a decision `0193` made deliberately.

## Why it is worth one run

This file's rule is that every number in it has a measuring device; that was the point of
`0175` and of `0193`. Two numbers now sit in it that no device produces and that the next
commit falsifies — the head has been wrong for a day and nobody nachgezogen it, which is
the evidence that this kind of number does not get maintained. One file, one decision,
one run; a second run at `parameter.toml` for either half alone would not be worth it.

**Not part of this:** the expression, the 25, the enumeration of the 26 literally
attested names, every mark, every leaf value, every bound. Also not the two historical
calls against `adfdd37` — they name their commit and are therefore not self-counting.

## Note for the project manager

`dateien` names only `parameter.toml`. On 2026-09-07 no other open or built package holds
it — checked against every `dateien` list under `aufgaben/`; `0193` is the last and is
built. **On the number:** the highest assigned was `0199`; I take `0203` with clearance.
If it collides, it is a number and not content.
