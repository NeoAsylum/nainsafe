---
typ: pruefung
paket: 0242-die-nennerbedingung-schuetzt-ihren-boden-und-nicht-ihre-decke
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all three conditions re-derived from the sources — message recounted by hand (319), guard condition compared against `__builtin_add_overflow` case by case, both probe directions and the completeness counter traced to `main`
befunde: 1
---

# All three conditions hold. The stated upper bound on the message length does not.

## Condition 1 — the message names country, address, rule, wording, number

`werte.cpp:735-745`. Country comes through `Meldung::adresse`, exactly as `0237`'s
precedent does it (`schritt.cpp:637` uses the same mechanism, not a separate name).
`land.US.sektor.2.wertschoepfung (Nr. 5)` carries `US`.

**Recounted, not trusted.** Prose 215 characters (65 + 65 + 58 + 27), address 39
(31 + `" (Nr. "` 6 + `"5"` 1 + `")"` 1), `" mit "` 5, `4611686018427387904` 19,
`"; die Summe davor war "` 22, `4611686018427387904` 19 → **319**, as the comment at
`werte.cpp:717` claims. `MELDUNG_ZEICHEN_MAX` is 511, so nothing truncates and the tail
survives. Address index confirmed: `stelle_sektorgroesse(US, Industrie, Wertschoepfung)`
= `0 + 0 + 1·4 + 0` = 4 → Nr. 5 (`zustand.hpp:800`, `SEKTORGROESSEN = 4`,
`Wertschoepfung = 0`).

## Condition 2 — the set of aborting states is unchanged

The guard is `gesamt > I64_MAX || gesamt < I64_MIN` on `i128` (`werte.cpp:731-734`);
`plus` aborts iff `__builtin_add_overflow(summe, teil, …)` (`festkomma.hpp:202`). These
are the same predicate on the same two operands, evaluated in the same order over the
same three addresses of `SEKTORLISTE`, and `plus` still does the addition. Hand-checked
at all four edges:

| summe | teil | gesamt | before | after |
|---|---|---|---|---|
| 2^62 | 2^62−1 | I64_MAX | runs | runs |
| 2^62 | 2^62 | 2^63 | aborts | aborts |
| −2^62 | −2^62 | I64_MIN | runs | runs |
| I64_MIN | −1 | I64_MIN−1 | aborts | aborts |

Blast radius outside the two files: nothing asserts on `bip` reaching `"plus: Summe"`.
The only other holders of that string are `festkomma_probe.cpp:274-300`, which reach it
through `festkomma::plus` directly.

## Condition 3 — both sides, and the barrier demonstrably fired

`werte_probe.cpp:1746-1846`. Positive control first in both directions (`== I64_MAX`,
`== I64_MIN`), then the abort one unit further. `nennerdecke_angekommen` is incremented
only inside the two abort blocks and `probe_nennerdecke_vollzaehlig` demands exactly 2
(`:1846`), called from `main` at `:1894` after `probe_bip_nennerdecke()` at `:1891`. Line
1836-1839 is the receipt that `letzte_meldung` is not stale: after `plus(I64_MAX, 1)` the
`bip` Kennzeichen must be absent. `werte_probe` passed and both `werte.cpp` and
`werte_probe.cpp` were recompiled in this run (`uebersetzung-2026-09-08.md:161-162,169`).

## Finding 1 — `bip` reads fifteen addresses, not twelve, and the bound is 324

`werte.cpp:718-720` states: „Die zwoelf Adressen dieser Summe tragen alle dieselbe
Textform von 31 Zeichen", and derives „hoechstens 323" from it.

`bip` takes a `Gebiet`, not a country, and `gebiet_basis` (`zustand.hpp:771-778`) accepts
all five. `zustandsausgabe.cpp:169` calls `werte::bip(z, gebiet)` for every `nummer` in
the overview sheet — the line itself distinguishes `spielbar = nummer < LAENDER` two lines
above and then reads the BIP unconditionally. So the Restwelt is a live caller every
round, and its addresses are `restwelt.sektor.<s>.wertschoepfung`: **32** characters, at
indices 176/180/184 → Nr. 177/181/185, three digits.

Reproduce: `bip(z, Gebiet::RW)` on a state with `restwelt.sektor.1.wertschoepfung` and
`restwelt.sektor.2.wertschoepfung` both at `I64_MIN`. Abort at the second address; the
message is 215 + (32 + 6 + 3 + 1) + 5 + 20 + 22 + 20 = **324** characters.

Not blocking: 324 < 511 with 187 characters of margin, so condition 1's purpose — nothing
truncated, the country survives — holds. What is wrong is a counted number presented as
counted, in the one comment the next agent will read instead of recounting. Worth folding
into whichever package next owns `werte.cpp`; too small for a run of its own.
