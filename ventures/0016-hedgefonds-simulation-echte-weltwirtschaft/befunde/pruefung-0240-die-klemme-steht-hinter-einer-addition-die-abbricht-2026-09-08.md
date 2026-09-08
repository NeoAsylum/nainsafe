---
typ: pruefung
paket: 0240-die-klemme-steht-hinter-einer-addition-die-abbricht
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Recomputed all twelve (Startwert, Term) outcomes by hand, matched the new i128 guard against `__builtin_add_overflow` on all four edges, and counted the new message against the 511-character buffer.
befunde: 3
---

# `geprueft` -- the guard is exact, and the header one commit above it is not

Build evidence: `befunde/uebersetzung-2026-09-08.md` shows `Building CXX object ...
schritt.cpp.o` and `... schritt_probe.cpp.o`, `schritt_probe ... Passed` -- the sources I
read are the ones the objects came from.

## What I checked, and how

**The hard limit of condition (b): the set of aborting states.**
`summe_der_regel_pruefen` (`src/schritt.cpp:679-700`) aborts iff the i128 sum leaves
`[I64_MIN, I64_MAX]`; `festkomma::plus` aborts iff `__builtin_add_overflow` reports the
same (`festkomma.hpp:199-206`). Identical condition. Four edges: `I64_MAX+0` and
`I64_MIN+0` still run -- both sit in `ZUSTIMMUNG_AUSSERHALB` (`schritt_probe.cpp:259-260`),
so `probe_zustimmung_klemmt_statt_vortrag` and half 1 push them through `schritt` every
run; `I64_MAX+1` and `I64_MIN-1` still abort. `lies_alt` is hoisted, still one call.

**Condition 3, recomputed.** All twelve rows of `SUMMENFAELLE` (`:1467-1480`) and of the
Vermerk table by hand against `min(10.000, max(0, a+b))` -- all twelve agree, including
the two `nach_der_regel` values the probe cannot compute (10.000 and 0).

**The message against the buffer** (my rule from 0237): 279 characters of prose + address
`land.US.zustimmung (Nr. 21)` at most 28 + 23 + 20 + 23 + 20 = **393** worst case, against
`MELDUNG_ZEICHEN_MAX = 511` (`meldung.hpp:77`). 118 characters of headroom, no truncation.

**Condition 2's finding, re-derived instead of believed.** `politiklast` (`:586-599`)
skips every instrument with `richtung == 0`; `schritt_3_politik` is `schreiber.vortrag`
(`:509`), step 2 aborts (`:488-499`), step 4 is `vortrag` (`:519`). So `last = 0`,
`hub = 0`, `wirkung = 0` for any parameter set. Arithmetic, not calibration.

**Condition 1c, both arguments re-derived.** Saturation is indistinguishable from exact
arithmetic *at this rule*: a sum above `I64_MAX` is over the integers > 10.000, so `min`
gives 10.000 either way; below `I64_MIN` both give 0. The ADR counterexample holds --
`alt = -100, wirkung = +50` gives 0 by `spiel.md`, 50 clamp-first.

**Determinism:** no floating point, no unordered iteration, nothing but `Meldung::adresse`
in the message. The i128 pre-check has precedent at `src/werte.cpp:731-734` (package 0242,
`geprueft` 2026-09-08), so it is not a new T6 case.

## Finding 1 -- `schritt.hpp` is false at HEAD, and `0245` made it true one commit earlier

`0245` landed **before** `0240` (`52a31a0` before `b3c417c`), though its Vermerk assumed
"`0240` runs before you". So `schritt.hpp:309` says "**Drei weitere**", and its third
bullet (`:323-331`) attributes every `i64` overflow of the Zustimmung rule to
`kern::festkomma`: "Dorthin fuehren ... der Rumpf von Schritt 5 selbst".

At HEAD that path is dead. `summe_der_regel_pruefen` (`:749`) aborts on exactly the pairs
that would have overflowed `festkomma::plus` (`:750`), so `plus` in the body of step 5
cannot abort any more. The header names a barrier that cannot fire and omits the one that
replaced it -- a fourth hard error, out of `kern::schritt`, not `kern::festkomma`.

No `zurueck`: `schritt.hpp` is outside `0240`'s `dateien`, and the builder recorded the
gap himself. Proposal `0249`.

## Finding 2 -- the assertion the probe's own comment leans on cannot carry it

`schritt_probe.cpp:1576-1579`: "Faellt sie, hat sich die Menge der abbrechenden Zustaende
bewegt -- und genau das durfte dieses Paket nicht tun." The loop above (`:1545-1574`) calls
`kern::festkomma::plus` **directly**. `festkomma.hpp` is outside this package's `dateien`
and unchanged, so `abgebrochene == 2` measures a function `0240` did not touch and is blind
to the guard `0240` added: narrow `:683-684` to `summe > I64_MIN`, and the abort set of
step 5 grows while `abgebrochene` stays 2.

The guarantee holds anyway -- half 1 and `probe_zustimmung_klemmt_statt_vortrag` drive
`I64_MAX` and `I64_MIN` through `schritt`, and *they* go red on that mutation. Only the
sentence names the wrong assertion.

## Finding 3 -- fourth leftover of one shape; the finding is the `dateien` rule

`0197` left a false header sentence because the header lay outside its `dateien`; `0233`
was built to delete it; `0245` was built to repair the enumeration; `0240` broke it again
the same night. `0245`'s condition 2 already forbade line numbers and site counts, and the
sentence went false regardless -- what moved was the **module**, not a line number. This is
for the project manager: proposal `0249` carries the nachzug and the question of whether an
enumeration of abort sites belongs in a header at all.
