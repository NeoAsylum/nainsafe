---
id: 0197-schritt-5-reaktion-rechnet-die-zustimmung
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: The four conditions under Acceptance. Condition 2 is the load-bearing one -- a run after which exactly one of the 310 quantities still changes over a round in weltlauf does not meet it.
vermerk: CREATED 2026-09-07, project manager. Not invented -- `kern/src/schritt.cpp` commissions it verbatim with the line "Das ist der Anschlussort fuer die Folgepakete", and `kern/include/kern/schritt.hpp` calls the six steps "sechs eigene Pakete". Until today none of the six had a package; that is the bottleneck `ops/plan.md` reports as the bottleneck. Your file list intersects no other open one -- you run alongside all eight existing lanes.
---

# Step 5 is the first of the six to get a computing body

`schritt_5_reaktion` is a single `schreiber.vortrag(platz)` today. Of the six steps it is
the smallest block that has anything to compute in `weltlauf`, which is why the series
starts here and not at step 4.

**Why step 5 and not step 4.** The `static_assert` in `kern/src/schritt.cpp` splits the
175 addresses of the target mask as `3 + 0 + 16 + 152 + 4 + 0`. Step 4 holds 152 addresses
and the market clearing with its fixed iteration count -- that is not one run, it is
several. Step 5 holds **four**: one approval rating per playable country. One run, one
body, and afterwards the round computes something for the first time.

**What lies outside and is not yours.** Supervisory counter, influence, remaining
durations, imitator counter and investor holdings are not in the `weltlauf` mask. The
change of government is computed and reported but **writes nothing** -- both statements
stand at the body of `schritt_5_reaktion` and stay as they are. You compute the approval
rating.

**You do not need counterforce 5.** Package 0165 records that its first reader is not yet
built; it lies outside the mask and is not in scope here.

## If the specification is not enough

`spiel.md` is being translated right now. If you cannot find the approval-rating rule
there in a form a body can be built from, then **build nothing invented**: set the package
to `gebaut` with a finding naming exactly which quantity is missing, and report it. A
guessed behavioural equation costs more than an empty run -- `grenzen.md` and the house
rule against invented numbers apply literally here.

## Acceptance

1. For the four approval-rating addresses `schritt_5_reaktion` no longer calls
   `schreiber.vortrag` but writes a computed value. The body states which rule in
   `spiel.md` it comes from, with that rule's wording.
2. **Over one round in `weltlauf`, more than one of the 310 quantities changes.** The
   evidence is a probe in `schritt_probe.cpp` that runs a start state for one round and
   prints the number of changed quantities: before this package exactly one
   (`partie.runde`), after it more. The probe names both numbers.
3. If your body takes its block as a whole rather than address by address, the statement
   about the ascending chain falls due -- `kern/src/schritt.cpp` carries it expressly
   "auf Widerruf". Retract it in the same change or record that the chain still ascends.
   A version that leaves this open is not finished.
4. `schritt_probe.cpp` passes, and the number of passing probes is not lower than at the
   start of your run. If a different number stands at the end, it follows the count, not
   this package.
