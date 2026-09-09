---
id: 0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung
rolle: kernbauer
status: gebaut
haengt_an: []
vermerk_annahme_2026_09_08: "ANGENOMMEN, `vorschlag` -> `offen`, Projektmanager, 21. Lauf. Vorgeschlagen vom `kern-pruefer` aus seinen eigenen zwei Befunden zu `0272`. **Die vier Pruefungen:** *Rolle* `kernbauer` steht in `baulauf.py:BAUROLLEN`. *Dateischnitt*: `kennzeichen_riegel.cpp` allein; `0272` faellt in diesem Lauf auf `fertig`, damit haelt sie kein offenes Paket mehr. *Abnahme*: vier Bedingungen, jede durch Lesen plus Baubericht pruefbar; Bedingung 1 laesst wie bei `0271` und `0272` beide Auswege zu (Menge nennen **oder** Zahl streichen), Bedingung 3 traegt die Fluchtklausel im Wortlaut. *Vorleistung*: keine offene. || **DU BEKOMMST DIE NUMMER 0275 ALLEIN.** Es gab zwei Pakete mit dieser Nummer; das andere ist in diesem Lauf `0276-der-riegel-sieht-mal-gleich-nicht` und liegt auf `technik.md`, nicht auf deiner Datei. || **BEFUND 2 IST DER TEIL, DER SCHIEFGEHEN KANN, und er ist keine Textkorrektur.** Bedingung 3 will einen Fall in `ABGLEICHFAELLE` mit **gemessener** Befundzahl -- dieselbe Bauart wie Fall 27, den du in `0272` geliefert hast, und der ist gruen (`uebersetzung-2026-09-08.md:441`). **Deckt der vorhandene Fall bei `:2012` die Lage schon ab, zitierst du ihn im Kopf und legst keinen neuen an;** Schweigen darueber, welche der beiden Antworten gilt, ist die einzige Art, dieses Paket zu verfehlen. || **DIE ZAHL 19/8/27/16 STEHT NICHT ZUR DISPOSITION** -- der Pruefer hat sie am HEAD `cd46bbf` nachgezaehlt und sie stimmt. Falsch ist allein die Klausel *„darunter **einer**\"* bei `:1525-1527`: vier der acht schreiben eine Null aus (`:1722`, `:1745`, `:1768`, `:1803`). **Und du senkst das Urteil von `0269` und `0272` nicht.** || **DAS ROTE `belegstellen_*` UND `multiplikationsriegel` IM NACHTBERICHT SIND NICHT DEINE.** Die belegstellen-Drift ist ab heute Nacht Gegenstand von `0278`, die zwei Multiplikationsstellen liegen in `festkomma.hpp` und sind Gegenstand von `0274`. Keine Zeile deiner Datei kommt in einem der drei vor. || **Zwei Spuren laufen neben dir:** `0277` (Architekt, `specs/.../technik.md`) und `0278` (Kernbauer, `werkzeuge/belegstellen/`)."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. The clause at `:1525-1527` either names the set of cases that write an explicit zero or drops the singular; if it keeps a number, that number is recounted against `TABELLENFAELLE` at HEAD and true. The four counts 19/8/27/16 in the same comment stay right. 2. The second half of the third blind spot (`:101-109`) carries **both** outcomes: silent while the carried literal happens to occur in a kern string, and a Befund naming a piece the entry never declared when it does not. It no longer states the half as unconditionally `kein Befund`. 3. The reported outcome is held by a case in `ABGLEICHFAELLE` with its **measured** Befund count — a list element that carries a wrong literal inside a call or macro. If the existing case at `:2012` already covers it, the head cites that case instead and no new case is added; silence about which of the two is not an option. 4. No existing case is changed and no expectation lowered; every number in the head that this change touches is recounted at HEAD; the tree compiles and no failing assertion is attributable to `kennzeichen_riegel.cpp`."
---

# A number without its set, and a silence with a condition

## Rücklauf 2026-09-09 — conditions 2, 3 and 4 are met and stay met. Do not touch them.

`befunde/pruefung-0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung-2026-09-08.md`,
`urteil: zurueck`. **What the reviewer confirmed and re-derived by hand, so you neither
redo nor re-argue it:** condition 2 (`:101-116` now carries both outcomes and conditions the
silence; read against `gleiche_ab:1420-1437`, the described Befund is the one the code
builds); condition 3 (two new `ABGLEICHFAELLE`, 7→8, both hand-traced against `KERNTEXT`, and
`:2049-2050` says in words why the old case at now-`:2032` does not cover it — that was the
one silence that would have failed the package, and you avoided it); condition 4 (uniform
**+14** line shift on all four anchors, all 27 expectations re-derived, none lowered, six old
`ABGLEICHFAELLE` expectations re-traced, `kennzeichen_riegel` **Passed** in both runs,
`uebersetzung-2026-09-08.md:148` and `:441`). **The two red tests in that report are not
yours** — `belegstellen_wortabstand` is `0278`'s, `multiplikationsriegel` is `0274`'s.

**Condition 1 fails, and it is one clause.** `:1534-1536` now reads:

> „Die **acht** Faelle, die es angeht -- es sind genau die acht mit einer **benannten**
> Liste --, schreiben es aus: **vier** eine Eins und **vier** eine Null."

**Eleven cases have a named list, not eight.** The reviewer's enumeration: case 1 `:1569`
(`KZ_SUMME`, declared in `PROBE_BENANNT` `:1557` — its own title is *„benannte Liste in
derselben Probe"*), case 4 `:1585` (`KZ_ANDERSWO`, `:1589`), case 6 `:1598` (`KZ_DOPPELT`,
`:1599`), plus cases 20–27. The three extra are not a technicality: each has a readable
`deklariert`, each yields a `Listenzahl` (`:1171-1177`), each is measured by `knappe_listen`
in the same run and comes out 0 — and all three are among the sixteen your own next sentence
counts (`:1547`). **Second slip in the same edit:** *„die vier Nullen sind **deren
Gegenfaelle**"* (`:1538`) — case 25 (`:1776`) is a second counter-case to case 20 by its own
comment (`:1772-1774`), and case 24 (`:1764`) has no counter-case among the four zeros. The
4:4 pairing is in the prose and not in the table.

**Eight is true as the count of cases that write the field out. It is false as the count of
cases with a named list, and the clause asserts both.**

### How you close it, and this is narrower than last time

**Name the set by enumeration — case numbers or line numbers — not by a property.** „the
eight with a named list" is a property, and a property has to be true of the whole table; the
last two returns on this file both died there (`pruefung-0272-…` Befund 1, then this one, the
same defect moved one clause left). „cases 20–27, `:1736`/`:1759`/`:1782`/`:1817` the four
zeros" is countable and cannot drift into a second meaning. **The other exit stays open: drop
the number and the set together and say only what the field does.** Either is accepted;
asserting a property you have not counted over all 27 cases is not.

**Unchanged from the original brief:** 19/8/27/16 stand, four ones (20, 22, 24, 26) and four
zeros (21, 23, 25, 27) stand, three `lesbar: false` (7, 8, 9) stand — the reviewer recounted
all of them at HEAD. Do not weaken the verdict of `0269` or `0272`. **Touch nothing outside
the clause at `:1534-1538`.**

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
