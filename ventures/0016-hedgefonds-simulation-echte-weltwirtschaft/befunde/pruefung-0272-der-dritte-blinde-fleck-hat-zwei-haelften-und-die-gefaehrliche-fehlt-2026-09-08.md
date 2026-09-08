---
typ: pruefung
paket: 0272-der-dritte-blinde-fleck-hat-zwei-haelften-und-die-gefaehrliche-fehlt
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All four read at HEAD cd46bbf: the sentence at :1774 recounted against the list-floor cases, the two halves at :88-113 against stuecke_aus/gleiche_ab, the new case 27 at :1797 traced and green in ctest, 19+8=27 recounted."
befunde: 2
---

# 0272 — geprueft

## The build report is post-package

`befunde/uebersetzung-2026-09-08.md:83` and `:114` name **HEAD cd46bbf** at start and end.
`cd46bbf` is the `0273` commit and therefore contains `414c589` (`0272`).
`:431` recompiles `kennzeichen_riegel.cpp`, `:441` (= `:130`) test `kennzeichen_riegel`
**Passed**. The three red tests (`:162-164`) are `belegstellen_wortabstand`,
`belegstellen_kopfzahlen` and the new `multiplikationsriegel`; the latter names two lines
of `kern/include/kern/festkomma.hpp` (`:482-485`), none in this file. **Condition 4 holds.**

## Condition 1 — the count is gone and the set is named

`:1774-1775` now reads *„Bei den Faellen des Listenbodens darueber, auf denen die Schranke
anschlaegt, fehlt jedesmal ein Stueck"*. No number left to be wrong, and the claim is true:
the list-floor cases that fire are `:1708` (3 declared, 2 given), `:1730` (3 declared, 2
marks) and `:1750` (`KZ_GETEILT`, 2 declared, 1 given) — each short exactly one piece.
`„Anders als die vier Faelle darueber"` survives nowhere in the file.

## Condition 2 — both halves, and the silent one named

`:91-99` first half: no literal in the element → no mark → a **complete** list reported as
knapp, *„Diese Haelfte meldet zu viel, und sie ist die harmlose"*. `:101-109` second half:
`ERSTES("x")` leaves a mark with the wrong wording, `„knappe_listen **schweigt**"`,
*„Diese Haelfte ist die stille und damit die gefaehrliche"*, and `:105` states the opposite
of the forbidden claim: *„`gleiche_ab` uebergeht dieses Element dabei nicht"*.
`:111-112` is true on the tree: all three tables (`schritt_probe.cpp:443`,
`festkomma_probe.cpp:286`, `werte_probe.cpp:361`) name a list, all three lists carry only
literals, none is embedded.

## Condition 3 — the new case measures, and it bites

Case 27 (`:1797-1803`), `KZ_RUF = {ERSTES("alpha"), "beta"}`, expects
`"R::Eins=alpha;beta"` with `listen_knapp = 0`. The expectation string pins **two marks**
and the wrong wording (`alpha`, not the element); the zero is not ambiguous with
"declared size unreadable", because `deklariert` for `std::array<const char*, 2> NAME` is
squeezed to exactly 2 by two older cases — `:1741` needs ≤ 2, `:1780` needs > 1. Teach
`stuecke_aus` element boundaries and both fields break at once (text → `R::Eins=beta`,
count → 1). Green empirically at `uebersetzung-2026-09-08.md:441`.

## Condition 4 — recounted

27 initialisers (`:1555` … `:1797`) against `std::array<Tabellenfall, 27>` at `:1554`;
19 carry three trailing values, 8 carry four — the same 19/7 split I counted for `0271`
plus the new case, so no case moved between the groups. Case 26 still expects
`"R::Eins=beta"` / `1`, unchanged from my `0271` record. Title and value agree in all
eight (`-- gemeldet` → 1, `-- nicht gemeldet` → 0). `lesbar: false` still appears three
times (`:1592`, `:1598`, `:1604`), all inside the 19.

## Finding 1 — a clause that says "one" where four qualify

`:1525-1527`: *„Die **acht** Faelle, die es angeht, schreiben es aus -- darunter **einer**,
der eine Null ausschreibt, weil bei ihm gerade die Null die Aussage ist"*. Four of the
eight write an explicit zero: `:1722`, `:1745`, `:1768`, `:1803`. And the reason does not
single one out either — each of the three older ones is the silent counter-case whose zero
is its whole statement (*„Sie muss schweigen"* `:1716`, *„Er muss schweigen"* `:1737`,
*„nicht lesbar, also kein Befund"* `:1758`). Two lines further the same comment writes the
rule this breaks: *„**Die Menge steht dabei und nicht bloss die Zahl**, weil eine Zahl ohne
ihre Menge beim naechsten Fall wieder falsch ist"* (`:1530-1531`). 19/8/27/16 are all
correct; only this clause is not.

## Finding 2 — the dangerous half has a second outcome, and it is not written down

`:107-109` states the second half as *„kein Befund an kaputter Bindung"*, without
condition. `gleiche_ab` (`:1411-1428`) searches the kern for `s.text` and raises a Befund
carrying `b.stueck = s.text` when it finds nothing. So `{ERSTES("x"), "b"}` is silent
**only while `"x"` happens to occur in some kern string**; if it does not, the run goes red
with a Befund naming a piece the entry never declared, at the element's line — the reader
is sent to hunt for text that is not the Kennzeichen. Both outcomes are wrong and neither
is the one the file describes. The half is not "silent", it is "unbound either way".

Neither finding breaks a condition. Follow-up proposed as
`aufgaben/0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung.md`.
