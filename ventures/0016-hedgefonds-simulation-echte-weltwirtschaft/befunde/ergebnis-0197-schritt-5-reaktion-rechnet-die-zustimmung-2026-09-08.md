---
typ: ergebnis
paket: 0197-schritt-5-reaktion-rechnet-die-zustimmung
rolle: kernbauer
datum: 2026-09-08
---

# The rule is complete; its carrier is not, and its address order forbids the loop

`0198` closed the gap of 2026-09-07: the approval rule stands in `spiel.md` with every
right-hand-side name resolved. `schritt_5_reaktion` still carries no computing body, and
the reasons are now two, both mechanical, both outside this package's `dateien`. Probe
and comments changed; the step body did not.

## The rule, as it now stands

```
politiklast(l)       = Σ_i sgn( lies_neu(land.<l>.instrument.<i>.stand)
                              − lies_alt(dieselbe) ) · schaden(l, i)
realeinkommenshub(l) = mal_geteilt( −politiklast(l), 10.000, bip(l) )
zustimmung_neu(l)    = min(10.000, max(0, lies_alt(land.<l>.zustimmung)
                     + mal_geteilt(zustimmung_elastizitaet, realeinkommenshub(l), 10.000)))
```

## Blocker 1 — the coefficient has no route, and neither has `schaden`

`zustimmung_elastizitaet` is a `parameter.toml` key. `kern::werte::Konstanten` does not
hold it (7 fields today: 6 T27 keys, 2 T23 constants — `regulierung_last` is there,
this key is not), and `kern::schritt::schritt` takes no carrier argument. T10b prescribes
`schritt(vorrunde, aktionen, konstanten, modus)` since `0208`; the code has not followed.

The same wall stands one level down and is easy to miss: `werte::schaden` — the right-hand
side of `politiklast` — has the signature `(z, rundenschreiber, konst, land, instrument)`.
It needs `const Konstanten&` too. So the carrier is not a convenience for one coefficient;
without it **no term of the rule is callable.**

Closing this touches `kern/include/kern/werte.hpp`, `kern/src/werte.cpp`,
`kern/include/kern/schritt.hpp` and the caller `kern/test/verlauf_probe.cpp` — four files,
none of them in this package's `dateien`. It also drags in the parameter checksum T10b
makes a hard error, which every existing probe's start state would fail. Proposed as
`0229`.

## Blocker 2 — approval sorts before the instrument levels it reads (new)

`LAND_POLITISCH_AB = 21`, `LAND_INSTRUMENTE_AB = 24` (`kern/include/kern/zustand.hpp`).
Within every country block the approval address therefore comes **before** all four
instrument stands. The round iterates addresses ascending (T9); `lies_neu` on an address
not yet written this round is a hard error (T39). A computing body at
`schritt_5_reaktion` would abort on its first address, for all four countries.

The route out exists and this package's condition 3 already names it: step 5 takes its
block as a whole, after the address loop, and the ascending-chain statement in
`kern/src/schritt.cpp` is retracted. That is a restructuring of `schritt()`, not a body —
and it is worth knowing before the next attempt, not during it.

## Condition 2 is refuted by `spiel.md` itself

> „because the rule is exactly zero without an instrument step, a round in which step 3
> carries the instruments forward moves no approval address. A probe that counts changed
> quantities over such a round measures nothing about this rule; the probe it needs is the
> two-state comparison above."

`schritt_3_politik` is one `schreiber.vortrag(platz)`. Every `sgn` is therefore zero,
`politiklast` is zero, the hub is exactly zero — for any coefficient. **`1 von 310` is a
property of step 3, and no body of step 5 can change it.** The acceptance criterion needs
replacing by the two-state comparison; that is the project manager's call, not a builder's.

## What was built

`kern/test/schritt_probe.cpp`: `probe_zustimmung_ohne_instrumentenschritt`. It measures
the two numbers the body hangs on, without the coefficient — how many of the 16 instrument
stands moved, how many of the 4 approval addresses moved — and asserts the implication
`spiel.md` calls its acceptance: no instrument step ⇒ no approval movement. Written as an
implication, not an equality, so it stays true once step 3 computes. It also measures the
address order of blocker 2 rather than transcribing it from T15.

Per-condition: 1 unmet (blockers 1 and 2), 2 unreachable (refuted above), 3 not due (no
body, chain still ascends), 4 the runner's — one probe added, none removed.
