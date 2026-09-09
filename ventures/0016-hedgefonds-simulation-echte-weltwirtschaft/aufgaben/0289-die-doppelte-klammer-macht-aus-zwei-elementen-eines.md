---
id: 0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines
rolle: kernbauer
status: vorschlag
haengt_an: [0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. The element count reads `constexpr std::array<const char*, 2> KZ = {{\"a\", \"b\"}};` as **two** elements — or the head says at the count's own line (`:1254` today) that the doubled brace is an accepted blind spot and why it cannot be resolved from the text this latch reads. 2. A case in `TABELLENFAELLE` holds it: a **complete** list in the doubled-brace form, declared as many as it carries, expecting `listen_knapp: 0`. The case is red on today's code — say in one sentence what makes it red today, and that sentence is the red proof. 3. No existing case changed, no expectation lowered, every count in the head that this change touches recounted at HEAD; the verdicts of `0269`, `0272`, `0275` and `0279` not weakened. 4. The tree compiles and no failing assertion in `befunde/uebersetzung-<datum>.md` is attributable to `kennzeichen_riegel.cpp`."
---

# The doubled brace turns two elements into one

From `befunde/pruefung-0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still-2026-09-09.md`,
Befund 1, hand-traced. Not a return: `0279`'s four conditions do not reach this, and the
element count it asked for exists.

## What is wrong

`finde_zuweisungen:665-670` sets `auf` to the **first** `{` after `=`. `felder_von:851-891`
then splits from `auf + 1` and counts `(){}[]` as depth. For

    constexpr std::array<const char*, 2> KZ = {{"a", "b"}};

the second `{` raises the depth before the comma is reached, so the comma never separates:
one field, `elemente = 1`, `stuecke = 2`, `hergegeben` = 1 < 2 — a **complete** list is
reported as short. Only the fully wrapped form breaks; `{{A}, {B}}` still counts 2.

## Why it is its own package

`0279` shipped the element count and its trap case; this is the counter-case it did not get,
and it needs code, not only a case. It is also the one direction this file treats as
disqualifying: `:1801` and `:1846` reject a bar that *„faerbt einen heilen Baum"*, and cases
21, 23, 25 and 27 exist for nothing else. The element count is the only bar in the table whose
false-positive spelling has no case.

It is not urgent and it is not theoretical. No list in the tree carries the doubled brace on
2026-09-09 — the three resolved ones are 3, 2, 2 elements and the run is green — but the
doubled brace is this tree's own spelling for every other `std::array`: `TABELLENFAELLE = {{`,
`ZERLEGEFAELLE = {{`, `ABGLEICHFAELLE = {{`, `RIEGEL_OHNE_ZUSTAND = {{` in all three probes.
The day someone writes a Kennzeichenliste the way the file beside it is written, a healthy
tree goes red and the reason will be nowhere in the message.

## The exit, if the count is to learn it

One brace pair that wraps the whole body and nothing else is a spelling `felder_von` can see:
if the trimmed single field of a list starts with `{` and ends at the closing brace of the
list, count inside it instead. Whether that is worth the second reading is the builder's call
— naming it as a blind spot at the count's own line is the other accepted exit, and then the
case of condition 2 pins today's behaviour instead.

## What you do not touch

`stuecke_aus`, `knappe_tabellen`, `deklarierte_groesse`, every existing case of all three
tables, the counts in the head beyond the ones this change moves, everything under `kern/`,
every `CMakeLists.txt`.
