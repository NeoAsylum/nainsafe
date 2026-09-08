---
typ: pruefung
paket: 0261-bip-sieht-die-restwelt-in-keiner-probe
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All five conditions read against werte_probe.cpp:2250-2363 and held against the runner report of 2026-09-08 (werte_probe green in root and kern runs at HEAD 6f2ec03)."
befunde: 0
---

# Pruefung 0261 — the Restwelt case exists, and the length is now an equation

Checked against `kern/test/werte_probe.cpp` at HEAD 6f2ec03 and
`befunde/uebersetzung-2026-09-08.md`. I did not read the builder's logbook.

## Condition by condition

**1 — the case.** `werte_probe.cpp:2269-2338`, inside `probe_bip_nennerdecke`:
`lege_wertschoepfung(r, Gebiet::RW, I64_MIN, I64_MIN, 0)`, then
`hat_abgebrochen(... bip(z, Gebiet::RW))` (:2278). The sector-2 address is asserted via
`adressform(rw_zwei)` (:2282), not written out, with the mirror-negative
`!enthaelt(adressform(rw_eins))` (:2283) matching the US case's shape. Met.

**2 — a number, not a bound.** :2317-2318: `PRUEFE(erwartet == std::size_t{324})` and
`PRUEFE(laenge == erwartet)`. `erwartet` = 242 (prose constant, recounted in the comment
as 215+5+22) + measured address width + 2 × measured width of `I64_MIN`. The green run
closes the triangle at runtime: actual length = 242 + 42 + 2·20 = 324, matching the PM's
independent derivation in the vermerk. The measurement equals 324, so no finding against
the `werte.cpp` comment. Met — and it can fail in both directions: prose drift breaks
`laenge == erwartet`, width drift breaks `erwartet == 324`. The extra red-proof at :2330
(RW address is exactly one character wider than BR's) pins why it must be the Restwelt.

**3 — positive control.** :2259-2264: `bip(z, RW)` with one summand at `I64_MIN`
returns `I64_MIN`, same compute-at-the-exact-boundary shape as the US (:2173-2178) and
DE (:2221-2226) controls. A `bip` aborting one step early goes red here. Met.

**4 — MERKE and the counter.** MERKE for `Riegel::BipsummeVerlaesstI64` at :2332;
`SOLLZAHLEN` bumped 2→3 (:414, third case named in the comment);
`probe_nennerdecke_vollzaehlig` now asserts `== 3` (:2363) with the rationale in its doc
comment. Deleting the RW case fails twice: counter 2≠3 and the Buch's exact count. Met.

**5 — attributable red.** Root run: `werte_probe` compiles (build log :63-64) and
passes; the two red tests (19 `belegstellen_wortabstand`, 21 `belegstellen_kopfzahlen`)
fail on the belegstellen riegel's own head numbers and the Bezugsstand drift
(2f2f79f vs HEAD 6f2ec03) — no failure line names `werte_probe.cpp`, and the citation
count is 41 at HEAD, equal to the head's 41, so the new comments added no citation.
Kern run 13/13 green. Met.

## What else I looked for, found nothing

- Weakened assertions: the old 319-vs-511 check (:2206-2209) stands untouched; the new
  case adds equality instead of loosening anything.
- Stale names in new comments (my 0257 pattern): `bezeichner_riegel` green at HEAD
  (root test 22 and standalone 1/1).
- 0263 guardrails from the vermerk: `RIEGEL_OHNE_ZUSTAND` (:361) unchanged, no
  `using enum` in the file (grep), `kennzeichen_riegel` green at HEAD (test 27).
- Ledger consistency: 23 SOLLZAHLEN entries, sum 36 (35 before this package), both
  static_asserts (:431-432) in place; `PlusOhneDarstellbareSumme` count 1 with its one
  arrival at :2351.

The PRUEFE-goes-red chain (counter in the catch path, exact-count compare, `main`
returns 1) was verified in `pruefung-0244-*-2026-09-08.md` and is unchanged.
