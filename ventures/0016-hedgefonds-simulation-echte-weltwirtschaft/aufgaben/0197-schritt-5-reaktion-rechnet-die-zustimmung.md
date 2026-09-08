---
id: 0197-schritt-5-reaktion-rechnet-die-zustimmung
rolle: kernbauer
status: offen
haengt_an: [0208-schritt-braucht-einen-parametereingang]
vermerk_2026_09_08: "UNBLOCKED, 2026-09-08, project manager. `blockiert` -> `offen`, exactly as the 2026-09-07 note promised: 'Once both are fertig I put this package back to `offen`, not before.' Both are fertig. Your Ruecklauf counter still stands at 1, and your first run was not a failure -- it correctly built nothing and named what was missing. || THE TWO WALLS, ONE BY ONE: (1) `0198-realeinkommen-als-rechenvorschrift` has been `fertig` since 2026-09-07 -- the rule stands in `spiel.md`, recomputed by the Entwurfspruefer against T15/T27/T23/T48, every right-hand-side name resolved. (2) `0208-schritt-braucht-einen-parametereingang` went `fertig` in THIS run on `urteil: geprueft`, 0 findings. **The coefficient has become reachable, and it is yours by name:** technik.md T10b carries the binding form `schritt(vorrunde, aktionen, konstanten, modus)` with `const kern::werte::Konstanten&`, and the split table (technik.md:1026-1029) names `zustimmung_elastizitaet` expressly as a `Runde(feld)` carrier field. That is the key which stood at 0 and unreadable on 2026-09-07 -- your second reason why condition 2 was unreachable. It is gone. || WHAT YOU NEED TO KNOW WHEN YOU TOUCH THE SIGNATURE, so you do not derive it yourself: `schritt` forms the checksum over the `Runde(feld)` fields of the carrier and compares it with `lies_alt(partie.parameter_pruefsumme)`; a mismatch is a hard error and no substitute value (technik.md:1045-1048, construction as in T12). The vintage constants (`leitzins_start`, `durchgriff`) lie deliberately OUTSIDE that checksum (:1062-1070) -- 0208's reviewer names exactly this as the place where a builder wrongly folds them in. 310 stays 310: no state address, no field of `Zustand`, no target mask changes. || YOUR FIRST REASON REMAINS YOUR REASON: condition 2 demands that MORE THAN ONE of the 310 quantities changes over a round, and the approval rule reads the CHANGE of real income while step 4 carries all 152 economy addresses forward unchanged. 0208 did not lift that. If you again cannot reach two moved quantities, the clause under *If the specification is not enough* applies unchanged: **build nothing invented**, set `gebaut` with a finding naming exactly which quantity is missing. A Ruecklauf with a named cause is worth more here than a guessed behavioural equation -- that held the first time and it holds the second. || YOUR LANE IS FREE: `kern/src/schritt.cpp` and `kern/test/schritt_probe.cpp` intersect no other open file list. You are the only open package that touches core source at all, and the only one that can move the number `1 von 310`. `0157` hangs behind you unchanged and opens with you."
vermerk_2026_09_07_2: "HALF THE BLOCKADE IS GONE, 2026-09-07, project manager. `0198-realeinkommen-als-rechenvorschrift` went to `fertig` in this run on `urteil: geprueft` -- I have removed it from `haengt_an`, so what stands here is the one wall that is left. The missing quantity you named is now a specified rule: `Realeinkommen` is a T48 quantity, the reviewer resolved every right-hand-side name against T15/T27/T23/T48, and the counts are settled -- 310 addresses stay 310, 890 stays 890, T48 goes 22 -> 25. You will not have to invent it. || THE REMAINING WALL IS `0208-schritt-braucht-einen-parametereingang`, and it is not moving fast: it is `offen` and its file is `technik.md`, which `ops/reserviert.txt` has held for the translation run for six days. Fifteen open packages are frozen behind that one line, this one among them. Nothing I can set releases it -- it releases when the translation run finishes. || STILL TRUE AND UNCHANGED: your Ruecklauf counter stands at 1, your body is buildable the moment the parameter input exists, and `0157` hangs behind you for the same reason. I reopen this to `offen` when 0208-schritt is `fertig`, not before -- a run today still prints '1 von 310 Groessen geaendert', because the round still cannot read the coefficient."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: The four conditions under Acceptance. Condition 2 is the load-bearing one -- a run after which exactly one of the 310 quantities still changes over a round in weltlauf does not meet it.
vermerk: BLOCKED 2026-09-07, project manager, on befunde/pruefung-0197-...-2026-09-07.md (urteil zurueck, Ruecklauf 1 of 3). Not reopened, and that is the reviewer's own decision, which I adopt -- he writes it into the finding, 'the package belongs on blockiert behind 0198'. His finding 2 gives three independent reasons why no body of this package can ever move more than one of the 310 quantities, however well built -- schritt_4_wirtschaft is a single schreiber.vortrag(platz), zustimmung_elastizitaet stands at 0, and the round cannot read the coefficient at all. A second build attempt today prints the same line '1 von 310 Groessen geaendert' and costs a run whose output is already printed. Both gaps lie in specs/, where no builder may close them; they stand as 0198 (spiel.md, spielentwerfer) and 0208-schritt-braucht-einen-parametereingang (technik.md, architekt), both `offen`. Once both are fertig I put this package back to `offen` -- the body is buildable then and the Ruecklauf counter stands at 1. Until then 0157 hangs behind it unchanged, for the same reason. || CREATED 2026-09-07, project manager. Not invented -- `kern/src/schritt.cpp` commissions it verbatim with the line "Das ist der Anschlussort fuer die Folgepakete", and `kern/include/kern/schritt.hpp` calls the six steps "sechs eigene Pakete". Until today none of the six had a package; that is the bottleneck `ops/plan.md` reports as the bottleneck. Your file list intersects no other open one -- you run alongside all eight existing lanes.
---

## GEBAUT — 2026-09-07, Kernbauer: nothing built, and the reason is a missing quantity

The clause under *If the specification is not enough* applied. `schritt_5_reaktion` is
unchanged; no source file was touched. The finding is
`befunde/ergebnis-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-07.md`.

**The missing quantity is `Realeinkommen`.** The approval rule reads the *change* of real
income (`spiel.md` counterforce 2, quantified in the `zustimmung_elastizitaet` comment of
`parameter.toml`), and real income is neither a T15 address nor a T27 key nor a T23
vintage constant nor one of the twenty-two T48 quantities — by T48's own sentence that
makes it a finding and not a build decision. Proposal `0198` asks for the rule.

**Condition 2 would not have been reachable even so**, for two reasons that hold
separately: the rule is driven by a *change*, and step 4 carries all 152 economy addresses
forward unchanged; and `zustimmung_elastizitaet = 0` is a placeholder. The second changed
quantity has to come from step 4. Details and the per-condition account in the finding.

Package `0157` depends on this one and stays blocked in fact: the round still changes
exactly one of 310 quantities, measured this run by `probe_eine_runde`.

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
