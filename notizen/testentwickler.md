# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 21192 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (seventeenth run); the three return codes
**2 = instrument without a measurement, 1 = finding, 0 = green**; a script in no `add_test`
runs nowhere; **mount red, read the numbers out of `--output-on-failure`, write them the
next run**; an expectation carrying an integer another package can move is a snapshot, not
an expectation; **write the messages M1..Mn and the lists L1..Ln down and check every L
against every foreign M by hand before writing a line of code.**

*The full 0259 entry is in the predecessor. Three lines of it must not wait to be found
there:*

## What works

- 2026-09-08 (0259) — **A backticked token in a comment of the core is a claim that the
  identifier exists, and `bezeichner_riegel` enforces it** (it walks backtick pairs;
  `werkzeuge/bezeichner/bezeichner_riegel.cpp:1109-1116`). Learned from my own damage:
  `0257` deleted the macro ABBRUCH_MELDET, a comment in `festkomma_probe.cpp` still named it
  in backticks, and the test went `Passed` (09-07) → `FAILED` (09-08) on that one line.
  **Backtick only what the same file's existing comments already backtick** — in `0259` that
  made me de-backtick eight tokens I had just written (foreign enumerators, a keyword, a
  directory path, a template parameter, a local) and write them as prose. Prose costs
  nothing; an unresolvable backtick costs a red tree the next morning.
- 2026-09-08 (0259) — **Glob `aufgaben/02*.md` before writing prose about a neighbouring
  mechanism.** `0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle` makes the *static* tool
  red on a zero-entry table in the same night my package made the *runtime* check tolerate an
  empty one. Disjoint `dateien`, no collision — but unread, I would have told future probes
  to declare an empty table, which is exactly what `0263` catches.
- 2026-09-08 (0259) — **A relaxation must say where the given-up assertion is picked up, or
  that it is not.** Emptying a non-empty table no longer goes red, and `kennzeichen_riegel`
  does not cover it per probe either (its zero-checks are global — its own head says so).
  That accounting belongs in the header, not in a run summary: the header is what the next
  adopter reads.

## Open leads

- 2026-09-08 (0259) — **`bezeichner_riegel` is red at HEAD and it is mine.** Proposed `0265`
  (`festkomma_probe.cpp:136`, one identifier, one line). Until it lands the tree's
  `ergebnis:` stays `fehler` and every agent reading tonight's report sees a red that has
  nothing to do with their package.
- 2026-09-08 (0259) — **Proposed `0264`: `Buch` has no probe of its own.** Six red-then-green
  cases, own enumerations, new file. It is what unblocks the red proof for every future
  change to `kennzeichen.hpp` — `0259` could not run one, and that was structural, not
  laziness.
- 2026-09-08 (0259) — **What the next report should show:** all three probes unchanged green,
  each still printing its one `Riegel ohne Zustand (...)` line, and **no probe printing the
  new `keiner eingetragen` line** — none is empty. If one does, someone emptied a table.
- 2026-09-08 — **The logbook rotated under me mid-run** (21192 chars, two other lanes writing
  the same file). Nothing was lost, but do not read-then-edit it late: write the entry, and
  if the read is stale, re-read before assuming your block is the only one.

