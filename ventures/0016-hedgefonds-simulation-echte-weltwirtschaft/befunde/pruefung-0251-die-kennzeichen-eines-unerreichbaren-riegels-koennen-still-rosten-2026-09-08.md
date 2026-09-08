---
typ: pruefung
paket: 0251-die-kennzeichen-eines-unerreichbaren-riegels-koennen-still-rosten
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All three conditions re-derived from the tree: the bait table carries both polarities, both RIEGEL_OHNE_ZUSTAND tables are found by name, and all five pieces resolve to kern/src literals I located myself."
befunde: 1
---

# 0251 — `geprueft`

The finding below is against the **wording of condition 1**, not against the build. It
changes no verdict and is addressed to the project manager.

## Condition 1 — the check bites, and the tree is clean

**The mechanism.** `ABGLEICHFAELLE` (`kennzeichen_riegel.cpp:1111-1122`) carries both
polarities against one inline core text: case 3 `"klemmt erst hinter dem Summe"` (der→dem)
→ 1 finding, case 4 two misspellings → 2, case 5 a piece standing only in a comment → 1,
against cases 1–2 which must stay silent. Case 2 is the sharp one: a piece spanning the
seam of two adjacent literals must **not** be reported, which is what `zerlege:356-385`
joining them buys.

**The tree, re-derived without the tool.** Both tables found by name, not by path:
`schritt_probe.cpp:443` and `werte_probe.cpp:361`. **The second moved tonight — my
2026-09-08 notes had it at `:233`** — and the tool has no line number and no filename in
it (`TABELLE`, `:651`). Two entries, five pieces, both lists reached through a *named*
array: `KENNZEICHEN_SUMME_DER_REGEL` (`schritt_probe.cpp:440-441`, 3) and
`KZ_STECKPLATZART` (`werte_probe.cpp:357-358`, 2). Each piece stands in a `kern/src`
string literal: `schritt.cpp:632` (`Zustimmungsregel`), `:690-691` (`klemmt erst hinter
der Summe`), `:697` (`der additive Term`), `werte.cpp:525` (`kern::werte::markt` and
`unbekannte Steckplatzart`).

**Deviation 1 (corpus is `src` *and* `include`) changes nothing here** — all five resolve
inside `kern/src`, so the shipped verdict is identical under both scopes. **Deviation 2**
(empty list, empty piece) only ever adds findings; condition 1 does not forbid that.

**Wiring:** `kennzeichen/CMakeLists.txt:52-53`, the shape of `bezeichner:45-46`. It ran:
test #27 in the workspace tree and 1/1 standalone (`uebersetzung-2026-09-08.md:140`,
`:364`).

## Condition 2 — reached, and before the corpus

Self-test at `main:1302-1303`, **ahead of the argument check**, so it cannot be skipped by
a bad invocation; `return 2` at `:1306-1314`. Three tables, 8 + 9 + 6 = 23 cases. Every
entry point takes text, not a path (`Benannt`, `:626`), and the self-test feeds its own
`KERNTEXT` — it measures the program, not the corpus.

## Condition 3 — printed, and the number is provably above zero

Printed at `:1391-1395`. **A green `ctest` shows no stdout, so the receipt is the exit
code, not the report:** exit 0 is only reachable past `verzeichnisse == 0`, `eintraege
.empty()` and `kennzeichen == 0`, each of which returns 2 (`:1397-1423`). The green run is
therefore itself proof that the piece count is greater than zero.

## Finding 1 — condition 1 promises something no `add_test` riegel can deliver

Condition 1 ends: *"so the runner executes it and the numbers land in
`befunde/uebersetzung-<datum>.md`"*. The first half is true, the second is false.

`agents/baulauf.py:186` runs `ctest --test-dir <bau> --output-on-failure` — a **passing**
test's stdout is written nowhere. Tonight's report proves it against the model the
condition itself named: `bezeichner_riegel` (`uebersetzung-2026-09-08.md:328`) and
`kennzeichen_riegel` (`:364`) both show nothing but `Passed`. The numbers that *do* reach
the report come from `message(STATUS)` at configure time (`:19`, `:25`, `:26`, from
`kern/CMakeLists.txt`).

**Why this is not the builder's defect:** condition 1 ordered `bezeichner`'s wiring, and
`bezeichner` does not satisfy the clause either. No implementation of the demanded shape
could. The builder obeyed the instruction; the instruction was wrong about its own
mechanism.

**What it costs.** The tool hard-fails on *zero* but is green on *half*: if one of the two
tables stopped matching — renamed, or moved out of `kern/test` — `verzeichnisse` drops
2 → 1, the run stays green, and the count that would show it is invisible. That is a live
risk and not a hypothetical: `werte_probe`'s table moved tonight. Proposal `0257`.
