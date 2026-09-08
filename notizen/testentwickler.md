# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 16264 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (fifteenth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; **mount red,
read the numbers out of `--output-on-failure`, write them the next run**; an expectation
carrying an integer that another package can move is a snapshot, not an expectation; and
the habit that keeps paying — **write the messages M1..Mn and the lists L1..Ln down and
check every L against every foreign M by hand before writing a line of code.**

---

## What works

- 2026-09-08 (0255, kennzeichen/werte_probe) — **When one helper builds many wordings, the
  Riegel is the wording and not the helper.** `pruefe_handelssektor` is a single `if` at
  three call sites, and it produces **four** distinct messages: caller name and reason go in
  as text, and `pruefe_landessektor` passes the same reason under two names. Making it one
  Riegel would have forced the Kennzeichen list down to the shared tail — and the shared
  tail is precisely what the source refuses; each of those sites carries a comment saying
  the check is made *under the name of the Groesse*. **The rule I would use again: let the
  source's own justification decide the granularity.** Where a comment explains why the
  message names a thing, that thing is part of the Riegel's identity.
- 2026-09-08 (0255) — **A second entry point is cheaper than a conversion when the call site
  asserts in both directions.** Twenty-one sites checked `PRUEFE(enthaelt(...))` *and*
  `PRUEFE(!enthaelt(...))`; the ledger can only do the positive one. `merke(riegel, was,
  zeile, kennzeichen, wortlaut)` beside `bricht_ab_mit`, both funnelling into one private
  `verzeichne`, bought the completeness half and the foreign-pair comparison for **one added
  line per site and no removed assertion**. The trap to avoid on the way: two entry points
  that each do their own storing/comparing are two shapes of the record, and then the
  sharpness of the check depends on which door a site happened to use.
- 2026-09-08 (0255) — **A `merke`-style entry point must refuse an empty wortlaut.** The
  probe resets `letzte_meldung` to `""` before each attempt, so "nothing was caught" and
  "caught something" are one `if` apart — and an empty entry would turn its Riegel's
  completeness check green without any barrier having fired. That is the exact hole the
  ledger exists against, opened by the mechanism meant to close it.
- 2026-09-08 (0255) — **Once a hand-written list passes about a dozen entries, generate it.**
  `ALLE_RIEGEL` was 7 names beside an enum of the same 7, guarded by a `static_assert` on
  its length. At 23 that is 23 lines of retyping; `constexpr` loop over
  `static_cast<Riegel>(n)` cannot be forgotten at all. The assert that guarded it goes with
  it — but the one that still matters (**every new Riegel gets a Sollzahl**) is untouched
  and now carries the whole burden alone, which is the honest place for it.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Fifteenth run in a row without a shell, and the second where it cost real
  certainty** (0244 was the first). Every one of the 16 new Riegel and all 21 expected
  counts are derivations from `src/werte.cpp` and from the call sites, not measurements.

## Open leads

- 2026-09-08 (0255) — **The next report is the whole proof, and here is its shape.** Expect
  `werte_probe` green with 35 `Abbruch wie erwartet` lines, 23 `Riegel "..." : n
  Meldung(en), erwartet n` lines, the summary `35 Meldungen aus 23 Riegeln ... vor Paket
  0255 waren es 14 aus 7`, one `Riegel ohne Zustand (werte)` line, and a `Kennzeichen
  (werte)` line whose pair counts jump from 182 to **1190** — that number is itself the
  proof the cross-product really ran. **A red on `kennzeichnet nicht` means two of my lists
  collide, and the report names both wordings: copy them, do not re-derive them.** A red on
  `falscher Riegel` means I read one abort path wrong.
- 2026-09-08 (0255) — **The four pairs I checked by hand and would check first if something
  is red:** `keilhub`/`preishub_zoll` share two wordings and differ only in the Groesse
  name; `handelsvolumen -- ` is a **prefix of two different Riegel** and is held apart only
  by the second piece (`unbekanntes Gebiet`); and the two Sektor reasons differ in four
  words — *"den Zollkeil gibt es nur"* against *"den gibt es nur"*. Any shortening of one of
  those lists collides in the same run.
- 2026-09-08 (0255) — **`probe_nennerdecke_vollzaehlig` (Paket 0242) is now an exact
  duplicate.** It asserts `nennerdecke_angekommen == 2`; `SOLLZAHLEN` asserts the same 2 for
  `BipsummeVerlaesstI64`, in the same run, over the same two sites. Left standing — nothing
  deletes, and it is not in my acceptance. Too small for its own package; worth one line
  here so the next run does not re-derive that it is redundant rather than wrong.
- 2026-09-08 (0244, discharged) — the fourteen `BRICHT_AB_MIT` sites went green: the
  compiler report of 2026-09-08 has `ergebnis: ok` and `werte_probe ... Passed`. The counts
  themselves are not in the report (a passing test prints nothing under
  `--output-on-failure`), so what is confirmed is that nothing went red.
- 2026-09-08 (0244, still open) — **`0251` reads the `RIEGEL_OHNE_ZUSTAND` tables by name
  under `kern/test/`.** This run did **not** touch that table — same one entry, same shape,
  same Kennzeichen. Said in the run summary, because the last package that needed that
  sentence waited four nights for it.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of
  the same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`);
  the day someone adds `-j`, they collide.

## Where I am unsure

**0255.** Four soft spots, all cheap for the reviewer.

1. **I ran nothing.** No compiler, no ctest. The 16 Riegel, the 21 counts and every
   Kennzeichen piece are copied out of `src/werte.cpp` and `festkomma.hpp` by hand.
2. **Two `kern::festkomma` Riegel in a `kern::werte` ledger** (`plus`, `minus`) is a
   judgement call. `kennzeichen.hpp` argues that a foreign Riegel firing in the wrong probe
   says nothing about that probe — my reading is that this differs, because both wordings
   are ones this probe *deliberately provokes as a Gegenprobe*, so they belong to the
   alphabet its own lists must survive, and the completeness half then asserts the call site
   in this file rather than ownership of the barrier. A reviewer may read it the other way.
3. **`bricht_ab_mit` lost its own empty-Kennzeichen pre-check** when that moved into the
   shared `verzeichne`. One case changes: empty list *and* no abort used to report twice,
   now once — the second report is still there in the "kein Abbruch" line, which prints
   `(keins genannt)`. I judged that not a weakening; it is the only behaviour change in the
   header besides the buffer size.
4. **`MELDUNGEN_MAX` 32 → 64 and `ALLE_RIEGEL` generated** are both in a file two packages
   keep. Neither changes the interface `schritt_probe` uses.

