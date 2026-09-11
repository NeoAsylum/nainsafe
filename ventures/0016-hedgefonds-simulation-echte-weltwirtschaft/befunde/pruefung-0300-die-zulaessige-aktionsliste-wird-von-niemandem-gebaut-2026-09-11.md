---
typ: pruefung
paket: 0300-die-zulaessige-aktionsliste-wird-von-niemandem-gebaut
pruefer: kern-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: all seven conditions traced to a green run in the runner's ctest log, with the five set sizes, the empty slot and the share-scale arithmetic recomputed by hand
befunde: 2
---

# The list and the bundle check hold; two things around them do not

Run evidence: `kern/bau/Testing/Temporary/LastTest.log:3-114` — `aktion_probe`
passed, and its output prints conditions 1 to 9.

## Condition by condition

1. `zulaessige_aktionen` at `aktion.hpp:506`, built against the round-start state.
   `probe_liste` (`aktion_probe.cpp:673`): 49 offers on 50 places (log:87),
   `in_kanonischer_ordnung` true, the reversed copy false (`:699`).
2. `zielmenge` (`aktion.hpp:427`) computes from `zustand::LAENDER`, `SEKTOREN`,
   `INSTRUMENTE`; no size is written out. The probe asserts 20/12/16/1/1 **and**
   the three formulas (`:738-746`). A fifth country turns the left side red.
3. `probe_der_leere_platz` (`:806`) asks each of the twenty slots singly and
   demands exactly one offer from nineteen, zero from Steckplatz 12 (log:95).
   Enumerated, not counted — a doubled plus a missing slot would fail.
4. Four conditions, each with a positive control at the admissible edge: three
   vs. four actions (`:836`/`:842`), cash 1'000 vs. 1'001 (`:866`/`:870`), the
   same target (`:850`) against the same number under a different kind (`:858`),
   the share 10'000 vs. 10'001 (`:903`/`:908`).
   **Recomputed by hand** at `stufenweite = 2'500`: Position step 2 plus stake
   5'000 on Steckplatz 0 gives `2·2500 + 5000 = 10000`, admissible; 5'001 gives
   10'001, rejected (`:1016-1019` / `:1010-1013`). Term for term the formula of
   `werte::fondsanteil` (`werte.cpp:960`), pinned against that function once:
   `besetzt`, DE Industrie, steps −3 and stake 1'500 → 9'000 (`:1031`, log:106).
5. `probe_der_satz_aus_t32` (`:986-995`): three stakes of 4'000 on one slot, each
   admissible alone, the bundle not.
6. `stufen_max` exists in `parameter.toml:361` as a placeholder and nowhere under
   `kern/`. The package's citations `technik.md:1704` and `spiel.md:3391` both
   check out verbatim. The outstanding-condition comment sits at
   `buendel_einwand` (`aktion.hpp:593-600`), which `buendel_zulaessig` is.
7. Probes are globbed into the build (`CMakeLists.txt:60,381-386`), so no build
   file had to move; `fondsanteil` and `Konstanten` are read, not changed.

Determinism: no floating point (`sperre.hpp` at `aktion.cpp:37`), no unordered
iteration, two counted loops, and the result does not read the state at all —
the probe pins that (`:721`).

## Finding 1 — for kind 2 the specification is not silent, and the code says it is

`aktion.hpp:573-577` and package `0302` both record: *"For kinds 1, 2 and 4 no
specification names an amount … The descriptions of the three kinds name no
amount."* For kind 2 that is refuted three times:

- `spiel.md:411-412` — the stake's *"exit discount is already built into the
  valuation, so **it is paid in full at entry**"*.
- `spiel.md:544` — *"The discount is thus paid when the stake is **built up**"*.
- `werte.hpp:444`, inside this core — *"Der Abschlag ist beim **Aufbau**
  bezahlt"*.

The amount is computable today: `korbwert(l, s)` (T48 Nr. 2, `werte.hpp:303`) is
built. What it costs: `0302`'s condition 1 forbids building the cash claim until
*"a sentence in `spiel.md` or an ADR"* exists. For kind 2 it exists, so `0302`
sends a decision back that the operator already took. Kinds 1 and 4 stay open.

No new package — `0302` claims the same three files and is the place. What needs
correcting is its premise and the header sentence.

## Finding 2 — the share check aborts where it should object

Reproduction: `konst.stufenweite = 2'500`, empty state, bundle of one action
`{Art::Position, Zielkennung{0}, 3'689'348'814'741'911}`. Steckplatz 0 is a
sector slot, so the loop at `aktion.cpp:323` takes it; `mal(…, 2500)` exceeds
`I64_MAX` and `festkomma::abbruch` (`festkomma.hpp:290-294`) throws
`std::domain_error`. Expected `Einwand::AnteilUeberDerSkala`; got a thrown core.
The `plus` at `aktion.cpp:353` is the second such site.

Against myself: T7 makes every overflow an abort, so the abort breaks no rule,
and `stufen_max` — condition 6, deferred on purpose — would reject far earlier.
It still matters because this is the one function whose job per T21 is to turn
bad input into a **reason**: once `0301` wires `setze` to it, one line of input
ends the process instead of being rejected. Belongs with whoever builds
`stufen_max`.

## Where I looked and found nothing

Order not a side effect of the loop (`ordne` runs on the already-ordered list);
the T9 collision between kind 1 and kind 2 target ids — both are
`land·SEKTOREN + sektor` for sector slots, so the shared loop in condition 5 is
correct; the empty currency slot keeps its ordinal instead of compacting the
rest; the cash comparison is `>` on both sides of its edge case.
