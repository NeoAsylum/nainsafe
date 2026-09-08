---
id: 0242-die-nennerbedingung-schuetzt-ihren-boden-und-nicht-ihre-decke
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: The three conditions under Acceptance. Condition 2 is the hard limit and the reason this package is cheap — you improve the message, not the arithmetic.
---

# `bip` names country and address when it is too small, and nothing when it is too large

Created 2026-09-08 by the project manager, from
`befunde/beschraenktheit-nach-schritt/bruch-2026-09-08.md`, **Finding 4**. Not invented and
not a repetition: `0237` gave the *floor* of the denominator condition a located message
this morning and was accepted on it. The ceiling has none.

## What is wrong

`werte::bip` (`kern/src/werte.cpp:691-700`) sums three Wertschoepfung values through
`festkomma::plus`. On overflow that aborts with `"plus: Summe ausserhalb von i64 (T7)"` —
**no country, no address, no mention of the denominator.** The same quantity, one step
further down, now aborts with rule, spec wording, `Meldung::adresse` and the number
(`schritt.cpp:625-645`). One value, two abort qualities.

Why it did not bite before: until `0197` no step read those addresses, so such a state ran
through. It is reachable now.

## Why it is its own package and not part of 0237 or 0240

Files. `0237` is `fertig` and owned `schritt.cpp` + `schritt_probe.cpp`; `0240` owns the
same two. `werte.cpp` and `werte_probe.cpp` are claimed by nobody, so this runs beside
them instead of behind them. The subject is one, the files are two — and per the house rule
the files decide.

## Acceptance

1. **The abort inside `bip` names country and address**, in the form `0237` established and
   was measured on: the rule, the condition in the spec's words, `Meldung::adresse`, the
   number. Take that message as the precedent literally — the reviewer counted it at 399
   characters against `MELDUNG_ZEICHEN_MAX = 511` (`meldung.hpp:74-77`), and the country
   name sits at the tail, so a message that grows past the ceiling loses exactly the part
   this package exists for. **Count yours and write the number down.**

2. **Hard limit: the set of aborting states does not change.** A state that aborts today
   aborts afterwards, and none is added. You are giving an existing abort a located
   message, not moving a threshold and not adding a barrier. **This is the whole reason the
   package is safe to run beside others** — see the blast-radius case of `0237`, whose new
   hard error killed `verlauf_probe.cpp` in a file outside its own list and cost `0238` a
   run. If you find you cannot meet condition 1 without changing which states abort,
   **stop and report it**; that is a different package and a different night.

3. **Both sides in `werte_probe.cpp`**, as `0237`'s condition 3 did it: the positive side
   runs through, the negative side asserts the abort by its Kennzeichen. The reproduction
   path is named in the finding — the three `land.US.sektor.<1|2|3>.wertschoepfung` at
   `4'611'686'018'427'387'904` (2^62) each; round 1 aborts in `bip`, at the second `plus`.
   **Register the Riegel so the completeness half of the Kennzeichen probe covers it** —
   that is what proved `0237`'s barrier actually fired instead of merely being present, and
   a green tree without it proves nothing.

**Not in this package:** `festkomma::plus` itself, `kern/include/kern/festkomma.hpp`, the
saturating-addition question (that is `0240`'s report to me), `schritt.cpp`, and
`werte::schaden`'s dormant overflow through `schuld` for CN and BR — the latter is written
down in `0237`'s `vermerk_abnahme` and stays dormant on purpose.

## Ruecklaeufe

0.
