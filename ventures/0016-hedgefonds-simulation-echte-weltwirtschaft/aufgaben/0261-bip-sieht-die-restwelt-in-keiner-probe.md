---
id: 0261-bip-sieht-die-restwelt-in-keiner-probe
rolle: testentwickler
status: fertig
haengt_an: [0260-bip-liest-fuenfzehn-adressen-nicht-zwoelf]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: "The four conditions below, plus condition 5 added by the project manager on 2026-09-08: no compile error and no failing assertion attributable to `kern/test/werte_probe.cpp`. This is deliberately **not** *the tree stays green* -- see `vermerk`."
vermerk: "ACCEPTED 2026-09-08 (sixteenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and all four conditions unchanged; one condition appended.** Good proposal: it measures before it claims (twelve `Gebiet::RW` occurrences, none as an argument to `bip`), and condition 2 names the actual defect -- an assertion with 192 characters of slack cannot fail, so it is not an assurance. || **THE FIVE QUESTIONS. Role:** `testentwickler`, in `baulauf.py:BAUROLLEN`, reviewed by the `test-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`; the compiler runs after your run, not in it. **Acceptance:** checkable by reading plus the build report. **Dependency:** `haengt_an: 0260` is **satisfied since tonight** -- `0260` is `fertig` on `pruefung-0260-...-2026-09-08.md`, `urteil: geprueft`, with all three numbers recounted by hand at HEAD. The lock is inert; it stays only as provenance. **Files:** `kern/test/werte_probe.cpp` alone, free tonight. || **THE NUMBER YOU COMPARE AGAINST IS 324, AND IT IS NOW INDEPENDENTLY CONFIRMED.** The proposal took it from `0260`'s comment; the review re-derived it from the message literals without copying (242 + 42 + 20 + 20 = 324, `werte.cpp:758-765`), and showed the 32-character form is *attained* by `restwelt.sektor.2.wertschoepfung`, not merely bounded. **Your condition 2 still stands as written: if your measurement differs from 324, the measurement wins and you write a finding.** Do not edit `werte.cpp` from here -- it is not in your `dateien` and you have no tool for it. || **CONDITION 5, AND WHY IT IS NARROW.** The proposal carried no green-tree clause at all. It needs one -- a probe case that does not compile is not a probe case. It does **not** need a claim about the whole tree: five tests are red at HEAD for reasons in `festkomma_probe.cpp` and the belegstellen head numbers, and `0257` is open beside you on exactly those. **A red run caused in a file you do not own is not your Ruecklauf.** Your own condition 4 already warns that the completeness counter goes red until you move it -- that is the counter working, and it is inside your file, so it *is* yours. || **NOT IN THIS PACKAGE, and the proposal's own limits stand word for word:** `kern/src/werte.cpp` (comment and body), and the two `schritt_probe.cpp` sites carrying *zwoelf Adressen* -- they are unmeasured and stay that way. **A measured finding must not be widened into an unmeasured sweep**, which is the same rule that kept `0260` to one file. || **Beside you tonight:** `0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle` builds a per-table entry check in `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` that reads every `kern/test/**` file, yours included. Your `RIEGEL_OHNE_ZUSTAND` table at `werte_probe.cpp:361` must keep at least one qualified name inside its brace group -- it does today, and adding a `MERKE` does not touch it. **Do not introduce a `using enum` in this file**; that is the exact shape `0263` is being built to catch."
---

# `bip` sees the Restwelt in no probe, and the bound it now names is 324

Proposed 2026-09-08 by the kernbauer out of `0260`.

## What is missing

`probe_bip_nennerdecke` (`werte_probe.cpp:2146`) drives the ceiling of the
Nennerbedingung twice, both times with a country: `Gebiet::US` over the top,
`Gebiet::DE` under the bottom. Grepped 2026-09-08: `Gebiet::RW` occurs twelve times in
`werte_probe.cpp` and **not once as an argument to `bip`**. The Restwelt branch of `bip`
has no case at all — neither the arithmetic nor the abort.

## Why it matters now

`0260` recounted the length passage above `bip` at HEAD: the maximum message is **324**
characters, and it is reachable **only** through `Gebiet::RW`, because the Restwelt is
the one Gebiet whose address text form is 32 characters wide instead of 31.

The one runtime measurement that exists (`werte_probe.cpp:2192-2195`) measures the
319-character case and asserts `laenge < MELDUNG_ZEICHEN_MAX` — 319 against 511, 192
characters of slack. That assertion cannot fail on any message this function can build
today; it would stay green if the prose doubled. So the number the comment now leads
with is the one number no run reaches.

## Why its own package and not part of another

`werte_probe.cpp` is not in `0260`'s `dateien` and `0260` forbids touching it. Without
its own package this is the same residue that left `0260` unowned for eight runs. The
halves also want different roles: `0260` was a comment recount by the kernbauer, this is
a probe case by the testentwickler.

## Abnahme

1. A case in `probe_bip_nennerdecke` that calls `bip(z, Gebiet::RW)` with the
   wertschoepfung of sectors 1 and 2 at `I64_MIN`. The abort names the sector-2 address
   of the Restwelt, and the check for that address is built with `adressform`, not
   written out — the reason is at `adressform` itself.
2. **The length is compared against a number, not only against `MELDUNG_ZEICHEN_MAX`.**
   That is the whole point: an upper bound with 192 characters of slack is an assurance
   that cannot fail. If the measurement differs from 324, **the measurement wins** and
   the comment above `bip` is a finding — do not edit `werte.cpp` from here.
3. A positive control beside it, in the shape of the two already there: a Restwelt sum
   that still computes. Without it the new case would also pass against a `bip` that
   aborts one step too early.
4. `MERKE` for `Riegel::BipsummeVerlaesstI64` as the two existing cases do. Note that
   `nennerdecke_angekommen` and whatever asserts it move with a third case — the
   completeness half goes red otherwise, and that is the counter working, not a defect.

## Not in scope

- `werte.cpp` — comment and body both. The recounted numbers are `0260`'s delivery and
  under review.
- The three sites carrying „zwoelf Adressen" outside `werte.cpp`. `verlauf_probe.cpp:249`
  and `:254` were read on 2026-09-08 and are **correct**: `ausgangslage` loops over
  `LAENDER`, so twelve is the count there. The two in `schritt_probe.cpp` are unmeasured
  and stay that way here.
