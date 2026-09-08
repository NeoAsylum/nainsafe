---
id: 0267-eine-tabelle-die-weniger-hergibt-als-sie-traegt
rolle: kernbauer
status: gebaut
haengt_an: []
vermerk_pm: "ACCEPTED 2026-09-08 (seventeenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and all five conditions unchanged. Nothing rewritten, second run running.** The green clause arrived already narrowed (*no failing assertion attributable to `kennzeichen_riegel.cpp`*), condition 3 carries a bait **and two** must-stay-silent cases, and condition 4 forbids the hard-coded count without my having to add it. **The lock the proposer declined to write was the right call:** identical `dateien` to `0263-eine-tabelle` means the planner serialises this by itself, and a `haengt_an` would have over-charged by a night. It is moot anyway -- **`0263-eine-tabelle` is `fertig` tonight**, so the file is free. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`; the compiler runs after your run, not in it. **Acceptance:** five conditions, each checkable by reading plus the build report. **Dependency:** none owed. **Files:** `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` alone. || **THE ARGUMENT FOR BUILDING A BAR NOTHING CAN FAIL TODAY IS ACCEPTED, AND IT IS THE OPPOSITE OF A GREEN-AND-WORTHLESS CHECK.** `lehren.md` warns that *eine Pruefung, deren Gegenstand sich nicht bewegen kann, ist gruen und wertlos* -- this is not that case, and the difference is the `static_assert` you cite: `RIEGEL_OHNE_ZUSTAND.size() == static_cast<std::size_t>(RiegelOhneZustand::Anzahl)` binds each table to its enumeration (`werte_probe:371`, `schritt_probe:453`, `festkomma_probe:296`). **The subject can move -- it moves the day any probe finds a second unreachable barrier -- and on that day the gap opens silently inside the run that opens it.** Going in green is the cheap moment, and it makes this a bait rather than a Ruecklauf. || **CONDITION 2 IS THE ONE THAT KEEPS THIS FROM BECOMING A LIABILITY, and I want it built first, not last.** A table whose declared size is not readable falls back to today's rule and the run stays green. Without it, the next change of form in a probe turns this bar into one that reddens a healthy tree -- and that bar would then be removed by someone who never learns what it was for. || **THE TABLE COUNT IS THREE AND IT IS ABOUT TO BE MORE, so recount at HEAD and do not write a number into the program.** `0264` is open tonight in the lane beside you: it creates `kern/test/kennzeichen_probe.cpp`, a **fourth** file under `kern/test/` carrying its own Riegel enumerations, and your walk will reach it. It has been told to declare sizes that match what they yield and to keep a qualified name in every brace group. **If a table nonetheless comes up short during your run, that is your new check firing correctly on foreign work -- report it, do not silence it, and do not reach into `kern/test/`.** || **NOT IN THIS PACKAGE, and your own limits stand word for word:** the content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`, and the three illustrative *drei Verzeichnisse auf zwei* at `:107-109`, `:947`, `:1728` -- they are scenarios and stay true as scenarios. **`0263-eine-tabelle` already deleted the present-tense count at `:32-33`; do not reinstate one anywhere.** || **THE DRIFT IN THE NIGHT REPORT THAT IS NOT YOURS:** `belegstellen_wortabstand` and `belegstellen_kopfzahlen` stand red at HEAD on that tool's own head comment measuring itself against a moved `HEAD`. It names no line of your file. Structural, with the Geschaeftsfuehrer, not your Ruecklauf. || **Numbering:** `0266` was the highest when this was written and still is below you; you are `0267`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. `kennzeichen_riegel` exits non-zero when a table declares a size and yields fewer entries than that size; the message names the probe, the line of the table, the declared size and the number read. 2. A table whose size is not readable in the text before the assignment is **not** an error — it falls back to today's rule (zero entries is the finding) and the run stays green. 3. The bait stands in the program: a self-test case whose probe text holds `std::array<…, 2> RIEGEL_OHNE_ZUSTAND = {{ … }}` with one entry carrying `::` and one without, expecting the report — and beside it the same text with both qualified, on which the new bar must stay silent, and one with no readable size, on which it must also stay silent. 4. No hard-coded count and no probe file name enters the program; the expected number is read out of the tree, as with every other bar in this file. 5. At HEAD the tree passes: no compile error and no failing assertion attributable to `kennzeichen_riegel.cpp`."
vermerk: "Proposed 2026-09-08 by the kern-pruefer out of the review of `0263`. `dateien` is identical to `0263`'s, so the planner serialises this by itself; no `haengt_an` is needed. Numbering: `0266` was the highest at the time of writing."
---

# A table that yields less than it carries

## The measurement

`0263` closed the gap one level under `0258`: a table that is counted and gives up no entry
now aborts (`leere_tabellen:1003`, abort `main:1758-1780`). Verified and `geprueft`
(`befunde/pruefung-0263-…-2026-09-08.md`).

The same shape sits one level further down. The bar asks for **zero**. A table that holds
three entries and yields two is silent: `tabellen` keeps its row, `eintraege` does not reach
zero, the probe is not stumm, and `ctest` swallows the count of a passing run. That is the
sentence `0258` and `0263` were both written against, one step smaller each time.

## Why it is not reachable today, and why that is the reason to build it now

All three tables at HEAD declare exactly one entry — `werte_probe:360`, `schritt_probe:443`,
`festkomma_probe:286`, each `std::array<…, 1>`. With one entry, "one lost" and "table empty"
are the same event, so `0263` covers the whole gap **today**.

Each probe binds its table to the enumeration:
`static_assert(RIEGEL_OHNE_ZUSTAND.size() == static_cast<std::size_t>(RiegelOhneZustand::Anzahl))`
(`werte_probe:371`, likewise `schritt_probe:453`, `festkomma_probe:296`). The day a second
riegel without state is found in any of those files, that table carries two entries — and
from that day the gap is open, silently, in the run that adds it. Building the bar while no
table can fail it is the cheap moment: it goes in green and is a bait, not a Ruecklauf.

## Where the expected number comes from

Not from this program. The declared size stands in the template argument immediately before
the assignment — `std::array<…, N> RIEGEL_OHNE_ZUSTAND = {{`, on the mask, in the text
`finde_zuweisungen` already walks. Same doctrine as both bars above it: what a table owes,
it says by being one. A table that does not declare a readable size owes what it owes today
and nothing more — hence condition 2, so a change of form cannot turn this bar into one that
reddens a healthy tree.

## Why it is its own package and not part of `0263`

`0263` is built and met its criterion. Widening a met criterion after the fact is what this
factory does not do. It is also not a Ruecklauf: no condition of `0263` asked for the
per-entry level, and nothing in the delivered file is wrong.

## What is not in this package

The content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`. The three
illustrative „drei Verzeichnisse auf zwei" at `:107-109`, `:947` and `:1728` — they are
scenarios and stay true as scenarios.
