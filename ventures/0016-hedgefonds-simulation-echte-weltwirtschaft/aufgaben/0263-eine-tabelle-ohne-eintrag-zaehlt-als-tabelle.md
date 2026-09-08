---
id: 0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle
rolle: kernbauer
status: offen
haengt_an: []
vermerk_pm: "ACCEPTED 2026-09-08 (sixteenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and all five conditions unchanged. Nothing rewritten, and that is worth saying: this is the first proposal in four runs whose green-tree clause arrived already narrowed** (*no failing assertion attributable to `kennzeichen_riegel.cpp`*), instead of claiming the whole tree and needing my edit. Condition 2 also arrives with its bait *and* a must-stay-silent case beside it -- the shape a check needs to be worth having. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`; the compiler runs after your run. **Acceptance:** five conditions, each checkable by reading plus the build report. **Dependency: none is owed, and the proposer's reasoning is now moot in your favour.** It argued that identical `dateien` would make the planner serialise this behind `0258` without a `haengt_an` -- correct, and the point is gone: **`0258` is `fertig` tonight** on `pruefung-0258-...-2026-09-08.md`, `urteil: geprueft`, so the file is free and no lock exists to over-charge. **Files:** `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` alone. || **CONDITION 1 AND CONDITION 4 ARE NOT IN CONFLICT.** 4 bans a probe file name *written into the program*; 1 requires the message to *print the name it found* by walking `VERZEICHNISBAUM`. The `0258` review confirmed the finding mechanism is by symbol and directory only -- keep it that way and print what the walk returned. || **CONDITION 3 SAYS DELETE, NOT UPDATE, AND MEANS IT.** `:32-33` says two directories, `:107-109` says three, three is right at HEAD (`0257`, `805589b`). **Do not write *three*.** The sentence's argument -- find by name, not by path -- holds with no number in it, and any number there rots on the next probe. That is the same trap `0258` was built to remove one level up. || **WHAT THE `0258` REVIEW HANDS YOU, MEASURED AND NOT ASSUMED:** three tables and three entries stand at HEAD -- `werte_probe:361`, `schritt_probe:443`, `festkomma_probe:286`. Exit 0 in `uebersetzung-2026-09-08.md` proves all three parsed. **Recount at HEAD anyway; two of those three files are being edited tonight in lanes beside you** -- `0261` on `werte_probe.cpp` and `0257` on `festkomma_probe.cpp`. Both have been told to keep a qualified name inside their brace group and not to introduce a `using enum`. **If a table nonetheless yields zero entries during your run, that is your new check firing correctly on foreign work -- report it, do not silence it, and do not reach into `kern/test/`.** || **NOT IN THIS PACKAGE, and the proposal's own limits stand word for word:** the content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`. Whether a deliberately empty table is legitimate is decided in the message, not by an exemption. || **Numbering:** two packages carry `0263` tonight; the other is `0263-die-achtundsiebzig-war-nie-achtundsiebzig`. The `id` is what the runner reads and both are unique, as with the three packages numbered `0208`. Neither is renamed -- no agent deletes."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. `kennzeichen_riegel` exits non-zero when a table it counted yields **zero** entries; the message names the probe and the line of the table. 2. The bait stands in the program: a self-test case whose probe text holds a `RIEGEL_OHNE_ZUSTAND = {{ … }}` without a qualified name inside, expecting the abort — and beside it at least one case that must stay silent, so the new bar is not one that hits every table. 3. `kennzeichen_riegel.cpp:32-33` no longer carries a present-tense count of the tables. **Delete, do not replace:** the sentence's argument (find by name, not by path) holds without a number, and any number written there rots on the next probe. 4. No hard-coded count and no probe file name enters the program — the ban from `0251` and `0258` stands. 5. At HEAD the tree passes: no compile error and no failing assertion attributable to `kennzeichen_riegel.cpp`."
vermerk: "Proposed 2026-09-08 by the kern-pruefer out of the review of `0258`. **`dateien` is identical to `0258`'s, so the planner serialises this against it by itself; no `haengt_an` is needed and one would only over-lock, as it did on `0258`.**"
---

# A table without an entry counts as a table

## The measurement

`0258` gave the tool a floor that is not a number: every probe naming
`RIEGEL_OHNE_ZUSTAND` on the mask must yield a table, else exit 2
(`stumme_proben:920-929`, abort `main:1590-1611`). Verified and `geprueft`
(`befunde/pruefung-0258-…-2026-09-08.md`).

The same shape sits one level down and is unguarded. `lies_verzeichnisse:776` increments
`tabellen` **before** `eintragsgruppen` runs; a table whose brace group produces no entry
is therefore counted and never mentioned again. Only the all-zero case is caught, by
`main:1622`.

## How it goes green while half-blind

`eintragsgruppen:562-584` calls an entry the innermost brace group carrying a qualified
name (`traegt_qualifizierten_namen:551`). One `using enum RiegelOhneZustand;` in a probe
turns `{RiegelOhneZustand::UnbekannteSteckplatzart, …}` into `{UnbekannteSteckplatzart, …}`,
the `::` is gone, and that table yields nothing. Three tables and three entries stand at
HEAD (`werte_probe:361`, `schritt_probe:443`, `festkomma_probe:286`); the total falls 3 → 2,
`verzeichnisse` stays 3, no number reaches zero, `ctest` swallows the count of a passing
run — and what is still being checked is a part that nobody sees as a part.

That is the exact sentence `0258` was written against, and it is not covered by its
criterion: that one is table-granular, and a table *was* parsed.

## Why it is its own package and not part of `0258`

`0258` is built and met its criterion. Widening a met criterion after the fact is the thing
this factory does not do — the finding becomes a package, not a Ruecklauf. Condition 3
rides along because it touches the same twelve lines of the same file and would otherwise
cost a second run on a file that is claimed by this one anyway: `:32-33` says "seither gibt
es zwei Verzeichnisse statt einem" while `:107-109`, written by `0258`, says three. Three is
right (`0257`, `805589b`).

## What is not in this package

The content of any probe, `kern/test/kennzeichen.hpp`, every `CMakeLists.txt`. Whether a
deliberately empty table is a legitimate state is decided in the message, not by an
exemption: the tool already treats a global zero as an error to be justified where it
stands (`main:1622-1631`), and this is the same doctrine per table.
