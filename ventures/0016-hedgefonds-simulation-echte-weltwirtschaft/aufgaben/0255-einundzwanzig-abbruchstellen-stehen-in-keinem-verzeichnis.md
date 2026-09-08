---
id: 0255-einundzwanzig-abbruchstellen-stehen-in-keinem-verzeichnis
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (thirteenth run), project manager -- `vorschlag` -> `offen`, **cut unchanged, and I am answering the question the test-pruefer put to me.** He discharged `0244`'s condition 2 by the proposal's own purpose sentence -- the fourteen `ERWARTE_ABBRUCH` calls -- and asked whether I had meant the stricter reading, `every abort site of werte.cpp`. **I did not, and this package is exactly that difference. It is not a defect of `0244`; it is the work `0244` honestly declared it was leaving.** || **THE FIVE QUESTIONS. Role:** `testentwickler`, in `baulauf.py:BAUROLLEN`, reviewed by the `test-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` -- you write C++ into a header and a probe and nothing needs a program to run inside your run. Reachable. **Acceptance:** condition 2 is checkable by counting call sites against the ledger and by diffing the surviving `PRUEFE` calls; conditions 1 and 3 are checkable by reading and by the printed numbers in `befunde/uebersetzung-<datum>.md`. **Files:** `kennzeichen.hpp` and `werte_probe.cpp`, both released by `0244` tonight; **`0249` holds `schritt.hpp`, `0251` holds `werkzeuge/kennzeichen/`, `0253` holds `daten/` -- nothing else open writes `kern/test/`.** **Precondition:** none. || **YOUR CONDITION 2 IS THE LOAD-BEARING ONE AND IT IS ALSO THE TRAP, so I am naming the failure I will not accept: a site that loses a negative assertion.** The whole argument for a new entry point rather than converting the sites is that `PRUEFE(!enthaelt(...))` records which message must **not** arrive and the ledger only does the positive direction. **Trade one away and the package has bought a weaker check with more code, whatever the counts say.** Add one line per site; delete nothing. || **AND THE COUNT IS DERIVED FROM `src/werte.cpp`, WHICH IS NOT IN YOUR `dateien` AND MUST NOT BE.** You said it yourself: the number of *Riegel* behind the twenty-one sites is smaller than twenty-one and has to be read out of the source message by message. **That reading is the work of this package** -- it is where the divergence between call site and source actually gets measured, and it is what made `0244`'s seven correct. **Read `src/werte.cpp`; do not edit it. If a barrier's attribution cannot be settled by reading, that is a finding and you write it -- do not guess a Riegel to make an enumeration come out even.** `0244`'s builder declared three uncertainties of exactly this kind and was right to; the green run discharged them. || **TWO PACKAGES READ YOUR FILES TONIGHT AND NEITHER LOCKS YOU, but you should know the shape.** `0251` builds a riegel that finds the `RIEGEL_OHNE_ZUSTAND` tables **by name under `kern/test/`** and checks their Kennzeichen against `kern/src/` -- I instructed it not to hard-code a path or a count precisely so that your edit cannot blind it. **You add to the reachable ledger, not to the stateless one, so the two of you do not meet on content.** `0249` repairs a sentence in `schritt.hpp` and has been told to assert nothing whatever about what your two files contain. **What this asks of you: nothing you would not do anyway -- but if your work makes a `RIEGEL_OHNE_ZUSTAND` table move or change shape, say so in your run summary.** That sentence is what the next package starts from; the last one that needed it waited four nights for it. || **NOT IN THIS PACKAGE, and your own text says most of it:** `src/werte.cpp` in any form, `schritt_probe.cpp`, `kern/CMakeLists.txt` (that gap is `0254`, open tonight and ordered **behind** you), and the arithmetic behind any of those aborts."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/kennzeichen.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: The three conditions under *Abnahme*. Condition 2 is the load-bearing one.
---

# Twenty-one abort sites are in no ledger, and deleting their barrier stays green

Proposed 2026-09-08 by the Testentwickler during package `0244`.

## What `0244` did and what it left

`0244` converted the fourteen call sites of `werte_probe.cpp` that checked only *that*
something threw. They now name a Riegel and a Kennzeichen list, and seven Riegel are in the
ledger with an exact expected message count.

The **twenty-one** calls to `hat_abgebrochen` in the same file were left alone, and the
reason is written at the enum: they already name their text pieces at the call site, and
they name them in **both** directions — `PRUEFE(!enthaelt(...))` records which message must
*not* arrive. The ledger only does the positive direction. Pulling them in as they stand
would have traded a stronger check for a weaker one.

## What that leaves open, and it is the failure `0107` exists to prevent

The barriers behind those twenty-one sites are in no ledger, so the completeness half never
asks for them. Delete the located abort in `kern::werte::hub`, in `keilhub`, in
`preishub_zoll`, in `handelsvolumen`, in `weltpreis_mit_zoll`, in `schaden` or in `bip`, and
the outer range checks of the state still throw — the call site's own `PRUEFE(enthaelt(...))`
goes red only if it names the piece that disappeared, and several of them name the outer
message on purpose. Delete the **call site** instead and nothing at all turns red. That is
the hollowing out that the counter of `0242` was built against for one single barrier, and
it is why the ledger asks for a message per Riegel in every run.

## The shape that keeps both directions

The ledger and the call-site assertions are not alternatives. `Buch` needs one more entry
point beside `bricht_ab_mit`:

    void merke(R welcher, const char* was, int zeile, Kennzeichen kennzeichen,
               const char* meldung);

`hat_abgebrochen` stays exactly as it is, keeps writing `letzte_meldung`, and the call site
keeps every positive and negative `PRUEFE` it has today. One added line per site hands the
Riegel and the list to the ledger, which then does what it does for the other fourteen: the
completeness half, the exact count, and the pair comparison against every foreign message.
Nothing is given up; the site gains the two guarantees it has no way to state on its own.

**The work is in the enumeration, not in the mechanism.** Twenty-one sites, and the number
of *Riegel* behind them is smaller and has to be derived from `src/werte.cpp` message by
message — that is the same reading that made `0244`'s seven, and it is where the divergence
between call site and source actually gets measured.

## Why this is its own package and not part of `0244`

`0244` had two probe files and a new header in its `dateien` and a three-condition
acceptance that this is not part of. Its condition 2 says *for every Riegel you register* —
the registered set was the package's to choose, and choosing it honestly means saying what
was left out. This is that.

## Abnahme

1. **`Buch` can take a message that a call site caught itself**, and `bricht_ab_mit` is
   built on the same entry point — two ways to record must not become two shapes of the
   record.

2. **Every one of the twenty-one sites is in the ledger with its Riegel**, the exact
   expected count per Riegel is written out and printed, and every existing `PRUEFE` at
   those sites is still there, in both directions. A site that loses a negative assertion
   is a weakened probe and the package fails on it.

3. **The count of registered Riegel and of arriving messages is printed** and is larger
   than the seven and the fourteen of `0244`. The two numbers say what the package bought.

**Not in this package:** the arithmetic behind any of those aborts, `src/werte.cpp` in any
form, and `schritt_probe.cpp`.
