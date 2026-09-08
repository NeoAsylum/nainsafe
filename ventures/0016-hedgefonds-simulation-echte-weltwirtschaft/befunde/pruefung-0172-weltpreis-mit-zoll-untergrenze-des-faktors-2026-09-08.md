---
typ: pruefung
paket: 0172-weltpreis-mit-zoll-untergrenze-des-faktors
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All three acceptance conditions replayed against technik.md section 23, the T30 check-2 sub-table, T51, T28, parameter.toml, spiel.md and werte.cpp; every load-bearing number reproduced.
befunde: 0
---

# Pruefung 0172 — way 1 holds, all three conditions met

## Condition 1 — the decision is explicit

technik.md:4381–4402 decides way 1 (bound at the instrument), quotes the measured
case verbatim, recomputes it as arithmetic (`11.000 · (10.000 − 12.000) / 10.000 =
−2.200`), and says what happens to it: both states become a hard error of check 2 in
the round they arise, reported at `land.DE.instrument.zoll.stand`, not at no. 21.
The number is the existing `instrument_min[zoll] = 0`, named in the row and in
reason 1. The measurement source cited (pruefung-0152…-2026-09-06.md, section
„4. Raender") carries the transcript character for character at its lines 218–224 —
the section re-anchors the brief's `mutanten.md` path to the reviewer's file, and
the re-anchored citation is the one that resolves.

## Condition 2 — bound 8 stands in the sub-table

Row 8 at technik.md:2401, address count 16, same form as rows 1–7; the check-2 head
(:2380) and the sub-table intro (:2388) now say **eight** bounds from T5, T49 **and
T51**. The address arithmetic reproduces: per playable country 3 instrument levels
are class 3 and the regulation tier is class 10 (:371, :375), the rest of world has
none (:380), so 4 × 4 = 16 — the roster's „4 instrument stage" counts only class 10
and does not contradict. `parameter.toml` carries `instrument_min`/`instrument_max`
for **all four** instruments (:1107–:1173, regulation min/max FEST, max coupled to
`regulierung_stufen`), so the generic row is buildable exactly as written. The
widening from 4 to 16 addresses is flagged as the one departure from the brief and
is reversible (:4435–4437); `spiel.md` knows no subsidy or negative tariff (grep
dry, 2026-09-08), so the 0-floor contradicts nothing there.

## Condition 3 — the domain reservation is untouched

The reservation stands at the end of section 18 (:3409–3416, the brief's former
:3262–3269), unedited; the werte.cpp comment (kern/src/werte.cpp:918–927) still
names the domain and is declared not closed (Report 3). The l/g divergence still
stands — spiel.md:366 writes `weltpreis_mit_zoll(l, s)`, technik.md:2198 `(g, s)` —
and section 23 names it without deciding it (:4458–4470), as the brief required.

## Load-bearing claims replayed, all reproduced

- Reason 2's quote sits at its source, technik.md:2095–2099 (wrapped across lines;
  a single-line grep misses it), and says what section 23 claims it says.
- T51: value range for all four instruments, both modes, „a finding of the vintage
  build" (:1823–1841); step-3 capping formula at :1836; capping acts in
  `spielmodus` only (:1838–1841).
- T28: exactly 40 steps, no convergence test (:1949–1954); wedge **inside** each
  step (:1956); the admissibility proof names exactly two premises (:1967–1970) —
  the third premise is real. Derivative recomputed from spiel.md:314:
  `durchgriff · (10.000 + zollstand) / 10^8`, sign flips below −10.000. Reader
  count 400 = 40 × 2 tradable sectors (:2242) × 5 territories (:2218).
- parameter.toml quotes exact: `instrument_min = 0  # FEST (T51)` (:1132),
  `instrument_max = 10000  # PLATZHALTER` (:1133) with the too-narrow note (:1128).
- T48 note (:2228–2234): `weltpreis_mit_zoll ≥ welt.preis > 0` follows from bounds
  8 and 2; welt.preis is one of the 22 class-5 addresses, so bound 2 covers it.

## Where I looked and found nothing

Timing of check 2 (a violating step-3 write is read by step 4 before a round-end
check): section 23 leaves where check 2 runs to T30 unchanged (:4402), and in both
modes a live mechanism precedes the test (capping; vintage-build precheck per T23
point 5) — coherent, no gap. Bound 4's redundancy is already reported to the PM in
Report 1; no separate proposal needed.
