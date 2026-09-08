---
typ: pruefung
paket: 0271-der-riegel-der-die-zahl-sagt-sagt-die-falsche
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All four conditions read at HEAD bff08ee: the counts 19/7/26/16 recounted against TABELLENFAELLE, the third blind spot read at :88-97, the new case 26 at :1762 traced through stuecke_aus/gleiche_ab and confirmed green by ctest #28."
befunde: 2
---

# 0271 — geprueft

## The build report is the one for this package

`befunde/uebersetzung-2026-09-08.md:106` and `:137` name **HEAD bff08ee** — the 0271 commit
— at start and end of the run. `:42` and `:60` recompile and relink `kennzeichen_riegel.cpp`;
`kennzeichen_probe.cpp` does **not** recompile, so `kern/test` is untouched. `:153` test #28
`kennzeichen_riegel` Passed. The two red tests (`:160-161`) are `belegstellen_wortabstand` and
`belegstellen_kopfzahlen`. **Condition 4 holds.**

## Condition 1 — recounted, not read

`TABELLENFAELLE` is declared 26 at `:1537`; I counted 26 initialisers (`:1538` … `:1762`).
19 carry three trailing values (cases 1–19), 7 carry four (cases 20–26) — 19 + 7 = 26.
`lesbar: false` appears exactly three times (`:1579`, `:1585`, `:1592`), all inside the 19;
`if (!lesbar) { continue; }` at `:1825-1827` stands before `knappe_listen` at `:1907`, so
19 − 3 = **16** reach the check. Every number in `:1503-1519` is right, and `:1515-1516`
names the set: *„Gezaehlt sind hier die Faelle, die das Feld auf der Vorgabe lassen."*
No `achtzehn` or `fuenfundzwanzig` survives anywhere in the file.

## Condition 3 — the case bites, and its numbers are pinned

Case 26 (`:1762-1767`) expects `"R::Eins=beta"` with `listen_knapp = 1`. `lz.stuecke =
e.kennzeichen.size() - vorher` (`:1152`) comes from the same marks as the entry, so the
expectation string pins `stuecke = 1` and the fourth value pins `1 < deklariert`. `deklariert`
for `<const char*, 2>` is pinned to exactly 2 by the existing pair: case 24 needs it > 1,
case 23 needs it ≤ 2. So the head's *„2 deklariert, 1 gelesen"* cannot drift while green, and
the message format at `:2361` produces those words verbatim. The case fails in both
directions: give a non-literal element a mark and both the expectation string and the count
break. Green empirically at `:153`.

## Finding 1 — `:1756` gives a number without its set

*„Anders als **die vier Faelle darueber** ist das keine Schranke, die anschlaegt, wo etwas
fehlt"*. Three readings, and the file supplies the wrong precedent: `:1594` uses *„Die vier
Faelle des Bodens"* for a **contiguous** group of four, which here is cases 22–25 — and case
23 is a complete list, so the sentence is false under that reading. Short lists above = 20,
22, 24, 25 → four, true. Cases where the bar fires = 20, 22, 24 → three. One paragraph after
condition 1 taught this file to say the set, the new sentence says only the number.

## Finding 2 — the new blind spot is written wider than it is true

`:88-90`: *„Ein Element, das kein Zeichenkettenliteral ist -- **eine Konstante, ein Aufruf** --,
hinterlaesst keine Marke."* True for a constant. False for a call or a macro carrying a
literal. `stuecke_aus` (`:960-975`) walks every `MARKE` between the braces and knows nothing
of element boundaries. So for

```cpp
constexpr std::array<const char*, 2> KZ = {ERSTES("x"), "b"};
```

`stuecke = 2`, `deklariert = 2` — **nothing is reported at all**, and `gleiche_ab` (`:1395-1412`)
binds `"x"` to the kern as if it were the Kennzeichen while the element's real wording stays
unbound. That is the opposite failure from the one written down: not a complete list
over-reported as knapp, but a short list going green under a wrong wording — the file's own
*„stiller Ausfall"* (`:84-86`). The verdict of `0269` is untouched by this; only the head's
sentence claims more than the code does.

Neither finding breaks a condition. Follow-up proposed as `aufgaben/0272-…`.
