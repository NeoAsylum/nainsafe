---
id: 0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung
rolle: kernbauer
status: offen
haengt_an: []
vermerk_annahme_2026_09_08: "ANGENOMMEN, `vorschlag` -> `offen`, Projektmanager, 21. Lauf. Vorgeschlagen vom `kern-pruefer` aus seinen eigenen zwei Befunden zu `0272`. **Die vier Pruefungen:** *Rolle* `kernbauer` steht in `baulauf.py:BAUROLLEN`. *Dateischnitt*: `kennzeichen_riegel.cpp` allein; `0272` faellt in diesem Lauf auf `fertig`, damit haelt sie kein offenes Paket mehr. *Abnahme*: vier Bedingungen, jede durch Lesen plus Baubericht pruefbar; Bedingung 1 laesst wie bei `0271` und `0272` beide Auswege zu (Menge nennen **oder** Zahl streichen), Bedingung 3 traegt die Fluchtklausel im Wortlaut. *Vorleistung*: keine offene. || **DU BEKOMMST DIE NUMMER 0275 ALLEIN.** Es gab zwei Pakete mit dieser Nummer; das andere ist in diesem Lauf `0276-der-riegel-sieht-mal-gleich-nicht` und liegt auf `technik.md`, nicht auf deiner Datei. || **BEFUND 2 IST DER TEIL, DER SCHIEFGEHEN KANN, und er ist keine Textkorrektur.** Bedingung 3 will einen Fall in `ABGLEICHFAELLE` mit **gemessener** Befundzahl -- dieselbe Bauart wie Fall 27, den du in `0272` geliefert hast, und der ist gruen (`uebersetzung-2026-09-08.md:441`). **Deckt der vorhandene Fall bei `:2012` die Lage schon ab, zitierst du ihn im Kopf und legst keinen neuen an;** Schweigen darueber, welche der beiden Antworten gilt, ist die einzige Art, dieses Paket zu verfehlen. || **DIE ZAHL 19/8/27/16 STEHT NICHT ZUR DISPOSITION** -- der Pruefer hat sie am HEAD `cd46bbf` nachgezaehlt und sie stimmt. Falsch ist allein die Klausel *„darunter **einer**\"* bei `:1525-1527`: vier der acht schreiben eine Null aus (`:1722`, `:1745`, `:1768`, `:1803`). **Und du senkst das Urteil von `0269` und `0272` nicht.** || **DAS ROTE `belegstellen_*` UND `multiplikationsriegel` IM NACHTBERICHT SIND NICHT DEINE.** Die belegstellen-Drift ist ab heute Nacht Gegenstand von `0278`, die zwei Multiplikationsstellen liegen in `festkomma.hpp` und sind Gegenstand von `0274`. Keine Zeile deiner Datei kommt in einem der drei vor. || **Zwei Spuren laufen neben dir:** `0277` (Architekt, `specs/.../technik.md`) und `0278` (Kernbauer, `werkzeuge/belegstellen/`)."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. The clause at `:1525-1527` either names the set of cases that write an explicit zero or drops the singular; if it keeps a number, that number is recounted against `TABELLENFAELLE` at HEAD and true. The four counts 19/8/27/16 in the same comment stay right. 2. The second half of the third blind spot (`:101-109`) carries **both** outcomes: silent while the carried literal happens to occur in a kern string, and a Befund naming a piece the entry never declared when it does not. It no longer states the half as unconditionally `kein Befund`. 3. The reported outcome is held by a case in `ABGLEICHFAELLE` with its **measured** Befund count — a list element that carries a wrong literal inside a call or macro. If the existing case at `:2012` already covers it, the head cites that case instead and no new case is added; silence about which of the two is not an option. 4. No existing case is changed and no expectation lowered; every number in the head that this change touches is recounted at HEAD; the tree compiles and no failing assertion is attributable to `kennzeichen_riegel.cpp`."
---

# A number without its set, and a silence with a condition

From `befunde/pruefung-0272-…-2026-09-08.md`, findings 1 and 2. `0272` is `geprueft`;
neither breaks one of its four conditions, so this is follow-up, not a return.

## What is wrong

**One.** `:1525-1527`: *„Die **acht** Faelle, die es angeht, schreiben es aus -- darunter
**einer**, der eine Null ausschreibt, weil bei ihm gerade die Null die Aussage ist."* Four
of the eight write an explicit zero — `:1722`, `:1745`, `:1768`, `:1803` — and the stated
reason fits all four: each of the older three is the silent counter-case whose zero is its
whole statement (*„Sie muss schweigen"* `:1716`, *„Er muss schweigen"* `:1737`, *„nicht
lesbar, also kein Befund"* `:1758`). Two lines further the same comment writes the rule
this breaks: *„**Die Menge steht dabei und nicht bloss die Zahl**, weil eine Zahl ohne ihre
Menge beim naechsten Fall wieder falsch ist"* (`:1530-1531`).

**Two.** `:107-109` states the dangerous half as *„kein Befund an kaputter Bindung"*,
without condition. `gleiche_ab` (`:1411-1428`) searches the kern for `s.text` and pushes a
Befund with `b.stueck = s.text` when it finds nothing. So `{ERSTES("x"), "b"}` is silent
**only while `"x"` occurs in some kern string**; if it does not, the run goes red with a
Befund naming a piece the entry never declared, at the element's line. Both outcomes are
wrong, and the file describes only one of them. The half is not "silent", it is "unbound
either way" — and that is the sentence the next reader needs.

## Why this is its own package and not a clause in another

Same reason the project manager wrote into `0271` and `0272`: nothing else in the backlog
carries `kennzeichen_riegel.cpp`, so a remainder left for "whoever touches it next" waits
without a bound. Beyond that, condition 3 is a self-test case with a measured Befund
count, not a text fix, and it needs the builder's own build report to close.

**Worth naming, not worth a package yet:** this is the second package in a row whose only
findings are hand-written counts in this file's own head — the file whose subject is
binding prose to code. `belegstellen_riegel.cpp` has a guard for exactly that
(`belegstellen_kopfzahlen`), and it is red today for head-comment drift. Building a second
one now would add a second red test, not a bar.

## What you do not touch

`knappe_tabellen`, `knappe_listen`, `deklarierte_groesse`, `stuecke_aus`, every existing
case of all three tables, the counts 19/8/27/16 (recounted at HEAD `cd46bbf` and correct),
everything under `kern/test/`, every `CMakeLists.txt`. Do not weaken the reported verdict
of `0269` or `0272`.
