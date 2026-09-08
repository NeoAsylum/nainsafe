---
typ: pruefung
paket: 0254-der-sperrebindungsriegel-sieht-keinen-kopf-unter-test
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "condition 1 by tracing collector -> loop -> FATAL_ERROR against the line order of `kern/CMakeLists.txt` and re-deriving the poison list from `sperre.hpp`; condition 2 against the configure line the nightly build actually printed"
befunde: 1
---

# 0254 — the third collector holds, and one sentence in its error message does not

## Condition 1 — a check, not a comment, and red before anything is built

`kern/CMakeLists.txt:67` `file(GLOB KERN_PROBENKOEPFE ... test/*.hpp)` — a third set, not
the probe set widened. `:295-318` reads each file and holds it against each name in
`KERN_VERGIFTET`; `:307` matches on word boundaries, `:308` raises `FATAL_ERROR`.

Line order, re-derived and not taken from the comment: **308 < 338 < 346**. The raise sits
before the STATUS line by which a green run is recognised, and before `add_library`. A hit
ends the configure with no build tree. The trace at `:238-246` holds.

Input reaching it: every `kern/test/*.hpp`. Today exactly one — `Glob` over `kern/test/**`
gives 12 `.cpp` and `kennzeichen.hpp`.

The name list is read, not copied (`:257-279`). By hand from `sperre.hpp:65-69`:
2 + 12 + 4 + 2 = **20**. The configure printed `20 dort vergifteten Bezeichner`, which also
rules out two failure modes: the words `pragma GCC poison` were not swept in (that gives
23+), and `sperre.hpp:10`, which names the same three words inside a `//!` comment, was not
counted — the anchor at `:261` demands line start. Zero is terminal, not green: `:248`
missing header, `:282` empty list, both `FATAL_ERROR`.

**"and the current tree passes":** `befunde/uebersetzung-2026-09-08.md` — `cmake -S` code 0
in all 9 manifests, message at `:19` (workspace) and `:175` (standalone kern).
`kennzeichen.hpp` names none of the 20 (`\b`-anchored search over all 20 names: 0 hits).
`Glob` mtime order `sperre.hpp` < `kennzeichen.hpp` < `CMakeLists.txt` <
`uebersetzung-2026-09-08.md`, and the printed wording („Dazu … Kopf/Koepfe unter test/")
exists only after this package — the report saw the committed file.

**Attribution of the red tree** (the freigabe made this mine to answer): 5 of 27 fail in the
workspace — `belegstellen_riegel|messung|wortabstand|kopfzahlen`, `bezeichner_riegel`. The
string `CMakeLists` does not occur once in the whole report; the failures name core headers
and comments. Standalone kern: 13/13. `festkomma_probe.cpp` is a `.cpp` and outside the new
set, so `0257` is untouched.

## Condition 2 — the size is printed

`:337` `list(LENGTH KERN_PROBENKOEPFE ...)`, printed `:342` as `1 Kopf/Koepfe unter test/`
plus `20 Paar(e)`. Separate, not summed. The three numbers are redundant (1 × 20 = 20), so a
collector that lost its files shows as 0 and 0 rather than as a plausible total.

## Decision 2 — written down, and it matches the code

`:202-224` buys the poison *effect on the text*, not the riegel's two conditions, and names
both directions: stricter (a name in a comment or behind `#if 0` counts), weaker (a name from
macro expansion passes). Both are true of `:295-318` as written.

## Finding 1 — the error message states as fact an include order the tree does not have

`:311-312`: „Ein Kopf unter test/ kann den Sperrkopf nicht binden: Er wird vor den Koepfen
des Kerns eingebunden und vergiftete sie mit."

Both includers do the opposite. `schritt_probe.cpp:145-152` and `werte_probe.cpp:46-52` put
`kennzeichen.hpp` **after** every `kern/*.hpp` and immediately before `kern/sperre.hpp`. If
`kennzeichen.hpp` bound the sperre header last, poison would begin two lines earlier and
reach no core header — the stated reason fails at HEAD, and with it the „kann nicht" it
carries.

Not `zurueck`: the prose at `:205-207` says the same thing in the conditional („ein Kopf,
den eine Probe vor den Koepfen des Kerns einbindet, vergiftete diese also mit"), and the
message mixes indicative `wird` with subjunctive `vergiftete`, so a hypothetical reading
survives. Neither acceptance condition covers this sentence.

What it costs if left: the second reason at `:207` — „ob der Sperrkopf zuletzt gebunden ist,
ist eine Eigenschaft des Einbindenden und nicht des Eingebundenen" — carries the same
conclusion without depending on any include order, and it stands only in the prose. Whoever
trips the check reads the half that has already gone stale. One clause, for the next package
that opens this file. No proposal: a package for one subjunctive in a message costs two runs
and changes no behaviour.

## Where else I looked and found nothing

- **Determinism:** `file(GLOB)` returns sorted, `REMOVE_DUPLICATES` keeps first occurrence,
  no time or address enters. The printed counts are order-free regardless.
- **Edges:** `math(EXPR)` is 64-bit, the pair counter cannot overflow, no division. The
  `list(GET ... anzahl-1)` at `:178` stays unreachable on an empty list because `:167`
  aborts first.
- **Semicolons.** `:156` avoids them deliberately; `:261` does not, it takes `[^\n]*`. A `;`
  in a trailing comment there would split one instruction into fragments and carry comment
  words into `KERN_VERGIFTET`. `sperre.hpp:65-69` carry no comment and no `;`, so it does not
  fire today. File contents are only ever used quoted (`:303`, `:307`), so a `;` in a probe
  header cannot split anything.
- **Staleness:** `CMAKE_CONFIGURE_DEPENDS` at `:137-139` now carries the sperre header
  itself, so a new poison entry retriggers the configure instead of being checked against
  yesterday's list.
