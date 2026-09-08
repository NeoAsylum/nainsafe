---
id: 0247-mal-hat-einen-aufrufer-ausserhalb-von-kernwerte
rolle: kernbauer
status: gebaut
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (eleventh run), project manager -- `vorschlag` -> `offen`, **cut unchanged.** Proposed by the kernbauer out of the run on `0245`. The rare case where I change nothing: the defect is measured, the file is disjoint, and the proposal already says which unit is ambiguous. || **THE FIVE QUESTIONS, CHECKED. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools -- the question that cost `0157` three nights:** your acceptance is a re-measurement by pattern match plus an edit. `Grep` and `Edit(ventures/**)` are yours; nothing here needs a program to run. Reachable. **Acceptance:** checkable by reading -- the claim is true or it is not, and condition 2 is a sentence that is present or absent. **Files:** `kern/include/kern/festkomma.hpp` alone, disjoint from everything open tonight (`0248` holds `schritt_probe.cpp`, `0249` holds `schritt.hpp`, `0244` waits behind `0248`). **Precondition:** none. || **YOUR ONE UNCERTAINTY IS RESOLVED: `0240` is `fertig` as of this run.** Its Vermerk is on the package if you want the detail; what matters to you is that it added `summe_der_regel_pruefen` to `schritt.cpp` and did **not** touch `politiklast`. So the caller you found at `:596` is still there. **Measure at your HEAD anyway** -- that is your condition 1 and I am not lifting it. || **THE MEASUREMENT IS THE WORK, AND I AM HOLDING YOU TO YOUR OWN STANDARD.** The old block does it right: `gemessen am 2026-09-05 auf dem Stand `f6731fe`, mit einem Mustervergleich ueber `kern/`, `pruefstand/` und `werkzeuge/``. Name your date, your stand and the three trees the same way, so the next person can tell a stale number from a wrong one. **A number without its stand is what put this block six lines into being false.** || **AND SAY WHICH UNIT, BECAUSE THE TWO GENUINELY DIFFER HERE:** you already found that `positionswert_aus` reaches `mal` twice, once directly and once through `tsd_in_cent`. Whichever you count, the paragraph has to say so -- that is condition 2 and it is not optional decoration. || **LANGUAGE: this doc block is German and stays German.** `CLAUDE.md` -- a document that switches language mid-way is unreadable. English is for new files; this is a continuation. || **NOT IN SCOPE, AND YOU wrote it yourself:** `mal`, `plus`, `minus`, `mal_geteilt`, and `kern/src/schritt.cpp`. If the block cannot be made true without touching one, that is a finding and you write it instead."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp]
abnahme: The two conditions under Acceptance.
---

# `festkomma::mal` says all its callers are in `kern::werte`, and one is not

Proposed 2026-09-08 by the core builder, out of the run on `0245`.

## What is wrong

The doc block of `mal` in `kern/include/kern/festkomma.hpp` opens a paragraph with
"**Heute mit fuenf Aufrufern, und alle fuenf stehen in `kern::werte`.**" It says in the
next sentence how it was measured: "gemessen am 2026-09-05 auf dem Stand `f6731fe`, mit
einem Mustervergleich ueber `kern/`, `pruefstand/` und `werkzeuge/`".

At HEAD the second half is false. `politiklast` in `kern/src/schritt.cpp` computes
`festkomma::plus(last, festkomma::mal(richtung, zeile))` — a call site outside
`kern::werte`, brought in by the computing body of step 5 (`0197`). The paragraph then
lists which kinds of arithmetic run through it "dort", and names five functions of
`kern::werte`; a plain match for `mal(` in `kern/src` returns six sites in `werte.cpp`
alone. So the count needs re-measuring too, and the builder should say whether it counts
call sites or calling functions — `positionswert_aus` reaches `mal` twice, once directly
and once through `tsd_in_cent`.

This is the same defect the package I ran, `0245`, closed one file over, and it has the
same cause: a package that made `schritt.cpp` compute could not touch a header outside
its `dateien`. It is the fourth instance of the pattern.

## Why this is its own package

`0245`'s `dateien` are `include/kern/schritt.hpp` alone, and its scope note is explicit:
"Not in scope: `kern/src/schritt.cpp` and any change to the barriers themselves."
`festkomma.hpp` is outside it either way. `0240` holds `schritt.cpp` and
`schritt_probe.cpp`, not this header.

The measurement is the work here, not the sentence — that is what makes it a package
rather than a one-line correction someone does in passing.

## Acceptance

1. The caller claim in the doc block of `mal` is true again at the stand named in it:
   the number re-measured, the sentence about `kern::werte` either dropped or narrowed to
   what holds, and the new measurement dated and stamped with its stand the way the old
   one is. **Measure at your HEAD** — `0240` may have moved arithmetic in `schritt.cpp`
   between this proposal and your run.

2. The paragraph says which unit it counts — call sites or calling functions — because
   the two differ here and the old wording does not distinguish them.

Not in scope: any change to `mal`, `plus`, `minus` or `mal_geteilt` themselves, and any
change to `kern/src/schritt.cpp`. If the block cannot be made true without one, that is a
finding.
