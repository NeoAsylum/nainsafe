---
typ: pruefung
paket: 0248-die-riegelliste-kann-keinen-unerreichbaren-riegel-fuehren
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "Both conditions read against the source at HEAD, the three Kennzeichen counted against the message in src/schritt.cpp, the build shown younger than the source by mtime order."
befunde: 2
---

# 0248 — the second ledger holds; the number is not where the Vermerk said

## Condition 1 — a barrier no state reaches, registered

**Completeness untouched:** the loop still runs over `ALLE_RIEGEL`
(`schritt_probe.cpp:2159`), seven entries, tied to `Riegel::Anzahl` (`:364`). The new ledger
has its own enum, and a message can only be recorded under a `Riegel` (`merke_meldung`,
`:525`) — nothing crosses over without its abort site being rewritten.

**The remaining half bites, readably.** `KENNZEICHEN_SUMME_DER_REGEL` (`:445`) is
`"Zustimmungsregel"`, `"klemmt erst hinter der Summe"`, `"der additive Term"`. The first
piece also stands in the message of `Riegel::Nennerbedingung` (`src/schritt.cpp:632`), whose
arrival in every run the completeness half forces: cut the list to it and the run goes red.
`PRUEFE(ohne_zustand_paare > 0)` (`:2268`) forbids a green pass over zero pairs.

**The dropped half — the "no" is right.** Both producers of that message are blocked. *By
state:* `wirkung = mal_geteilt(k, hub, 10.000)` (`src/schritt.cpp:740`),
`hub = mal_geteilt(-politiklast, 10.000, bip)` (`:644`), and `politiklast` skips every
instrument with `richtung == 0` (`:592`) — while `schritt_3_politik` carries forward,
`last == 0`, hence `wirkung == 0` and `summe == ausgangswert`, for any coefficient. *By
call:* `summe_der_regel_pruefen` (`:679`) sits in the anonymous namespace `:72`–`:843`;
internal linkage, not nameable from the probe.

**The Kennzeichen are true today** — the check the mechanism itself cannot do, so with a
date on it: all three pieces occur in the message at `src/schritt.cpp:690`, `:691`, `:697`.

## Condition 2

`RiegelOhneZustand::SummeDerZustimmungsregel` is the only entry (`:459`), index tied to
enumerator (`:486`). Printed per entry: name, number of Kennzeichen, messages hit, reason
(`:2257`); the closing line prints `ALLE_RIEGEL.size()` and `RIEGEL_OHNE_ZUSTAND.size()`
(`:2271-2275`).

## The folded-in comment fix from 0240's review

`:1693-1704` now says the count says **nothing** about the set of aborting states, names why
(the loop calls `festkomma::plus` directly, never `kern::schritt`) and points at half 1 of
`probe_klemme_hinter_der_summe` and at `probe_zustimmung_klemmt_statt_vortrag`. Those carry
it: `ZUSTIMMUNG_AUSSERHALB` (`:265`) holds `I64_MAX` and `I64_MIN` and both run through
`schritt` (`:1615-1624`), so a narrower guard turns them red at either end.

## That the report belongs to this source

`kern/test/schritt_probe.cpp` is **older** than
`bau/kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o`, than the linked
`bau/kern/schritt_probe` and than `uebersetzung-2026-09-08.md` (mtime order); that report
has `Building CXX object … schritt_probe.cpp.o` in both trees and `schritt_probe … Passed`.
So the three `static_assert`s compiled and the new loop ran green — including the builder's
open point, the `constexpr std::span` onto a `constexpr` array.

## Findings

**1 — the acceptance path named in the Vermerk does not exist. For the project manager.** It
sends the reviewer to `uebersetzung-<tag>.md` for condition 2's number. It is not there and
cannot be: `ctest --test-dir … --output-on-failure` (`agents/baulauf.py:186`) prints nothing
for a passing test. I verified condition 2 by reading instead — the `printf` is
unconditional in a function `main` calls (`:2296`), and both sizes are compile-time
constants tied to their enums. **The rule: "the run prints N" is not checkable from the
build report while the tree is green.** No package proposed; the fix would sit in
`agents/baulauf.py`, outside every build role of this venture.

**2 — one sentence over-states its reason.** `:413-417`: „Es fehlt nicht ein Zustand, der
sie erreichte — es fehlt jede Moeglichkeit, sie von hier aus zu nennen." Both blocks are
needed; drop either one and the message exists. No defect against the criterion, and
`:424-425` says the right thing. Written down so nobody re-derives it.

## What I searched for and did not find

Determinism of the new code (ordered arrays only; no float, no address, no time). A hole in
the completeness half opened by the exemption. An already rusted Kennzeichen list. A third
route to the barrier. A behaviour change in `liste_passt` from being routed through
`alle_stuecke_in` (`:584-587`; `KENNZEICHEN_MAX` bounded at `:536`).
