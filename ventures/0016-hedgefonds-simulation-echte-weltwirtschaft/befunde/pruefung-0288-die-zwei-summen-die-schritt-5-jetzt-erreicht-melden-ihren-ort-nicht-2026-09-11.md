---
typ: pruefung
paket: 0288-die-zwei-summen-die-schritt-5-jetzt-erreicht-melden-ihren-ort-nicht
pruefer: kern-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: all four conditions traced to code, plus the two green ctest lines that cannot be green without the change
befunde: 2
---

# Both sums are located; a third that carries the same name is not

## Condition 1 -- the two messages

`summe_der_last_pruefen` (`kern/src/schritt.cpp:649-673`) and `pruefe_handelssumme`
(`kern/src/werte.cpp:475-498`) test `static_cast<i128>(a) + static_cast<i128>(b)` against
`[I64_MIN, I64_MAX]` before the addition and abort naming function, Gebiet,
Instrument/Sektor, address, summand and running sum. Both additions still run through
`festkomma::plus` (`schritt.cpp:702`, `werte.cpp:900,905`) -- T6 intact. Same shape as
`kern::werte::bip` (`werte.cpp:846-861`), only with the comparison inverted (`return` on
the good case instead of abort on the bad one); the predicate is identical.

**The address is a substitution, and it is the right one.** The criterion wants "the
address of the overflowing summand"; `politiklast`'s summand is `mal(richtung, zeile)`, a
product with no address. The builder names the instrument's `Stand` and says why at
`schritt.cpp:645-648`. Not a miss -- recorded so the next reader does not re-open it.

## Condition 2 -- red without the change

Without the guard, `plus` raises `"plus: Summe ausserhalb von i64 (T7)"`. Both probes
assert the function name *present* and that string *absent* (`werte_probe.cpp:2461,2476`;
`schritt_probe.cpp:1672,1691`), so a bare `plus` turns both red. Neither can be silently
skipped: `probe_handelsdecke_vollzaehlig` demands the counter be exactly 2
(`werte_probe.cpp:2541`), and `LastDerPolitikzeilen` sits in `ALLE_RIEGEL`
(`schritt_probe.cpp:525-532`), whose completeness half requires an arrived message in every
run. Both probes are green in both trees of `uebersetzung-2026-09-11.md` (kern #8, #10;
daten #9, #11). That is the proof.

Hand-checked: `2^62 + (2^62 - 1) == I64_MAX` runs, `2^62 + 2^62` aborts; `-2^62 + -2^62 ==
I64_MIN` runs, one more `-1` aborts. The green `== I64_MAX` at `werte_probe.cpp:2448` also
pins `ZWEI_HOCH_62` to exactly `2^62` without reading the constant.

## Condition 3 -- the set of aborting states

`festkomma::plus` (`festkomma.hpp:199-206`) aborts iff `__builtin_add_overflow` on two
`i64` reports; the i128 test over the same two values is that predicate. Evaluation order
unchanged: `mal` was an argument of `plus` before and is a named local now
(`schritt.cpp:700`), still evaluated first; `z.lies` likewise (`werte.cpp:898,903`). In
`politiklast` the guard sits inside the `richtung != 0` branch -- exactly where `plus`
stood. No threshold moved by one.

## Condition 4 -- nothing else moved

`werte.hpp` blob `e6edd482` identical in the 09-10 and 09-11 reports (both post-0288, HEAD
`48ee300` and `475f971`): no signature changed. `schritt.hpp:264` `SUMMIERTE_FELDER = 7`,
`:277` `JAHRGANGSFELDER = 3`, unchanged since my 2026-09-09 citation. Commit `48ee300`
carries 6 files = 4 `dateien` + package + logbook, and `lauf.py:commitpfade` admits nothing
else. `multiplikationsriegel` is red at `festkomma.hpp:99` -- red on 2026-09-10 with the
same BEFUND, not this package.

## Befund 1 -- the one-place `handelsvolumen` still says nothing (not a return)

`kern/src/werte.cpp:920` sums the two sector sums through a bare `plus`:

    summe = plus(summe, handelsvolumen(z, land, sektor));

Two sector sums each inside `i64` whose total is not -- `2^62` per sector suffices -- abort
with the eleven words this package exists to remove, *out of a function named
`kern::werte::handelsvolumen`*. That is worse than before 0288: a reader who greps the
located wording now concludes the abort cannot be from `handelsvolumen`. Reachable through
`waehrungswert` (`werte.cpp:722`, called at `:580`).

Outside the criterion, which cites `werte.cpp:829-837` -- the two-place body, `878-908`
today. Hence a finding and not a return. Proposal `0303`.

## Befund 2 -- eight bare accumulators are left, and nobody counts them

Unguarded `plus` accumulators still in the core: `werte.cpp:745, 750, 764, 776, 920, 992,
995, 1145`. `bip` (0242), the Zustimmungssumme (0240) and these two (0288) were each found
by a reader who hit the bare message first. Listed here so the next one starts from a list.

## Where I looked and found nothing

Determinism: `float|double|unordered|std::map|std::set|time(|rand(|chrono|reinterpret_cast|uintptr`
over all of `kern/src` -- 0 hits. Both new messages are fixed-buffer `Meldung`, enum values
cast to `i64`, addresses rendered by name. Truncation: both probes assert `MARKE` (`"[...]"`)
absent, and `werte_probe` measures the length at runtime -- neither message loses its tail.
