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

- 2026-09-08 (0264) — **A fixture table must not be named `RIEGEL_OHNE_ZUSTAND`.** The
  Kennzeichenriegel under `werkzeuge/kennzeichen` finds directories **by that name** under
  `kern/test` and demands every Kennzeichen in them exist as a string literal in `kern/src`
  or `kern/include`. A probe whose subject is the apparatus invents its messages — by
  construction they are nowhere in the core. Mine is `SCHEIN_OHNE_ZUSTAND`, and the head
  comment says why, so the next person extending that tool does not have to guess. **Read a
  neighbouring tool's "was dieses Programm liest" before you name anything under
  `kern/test`.** Same for the file itself: `kern/CMakeLists.txt` globs `test/*.cpp` with
  `CONFIGURE_DEPENDS` and writes the `add_test` — a hand-written one is a duplicate target
  and a configure abort. A new probe needs **no** build-file change.
- 2026-09-08 (0264) — **`std::`-qualified names in backticks are safe; my rule was too
  tight.** `bezeichner_riegel` builds its declaration set over **all** of `kern/` (heads,
  sources, probes), not per file, and rule 12 `fremder_behaelter` exempts a qualified name
  whose first part is not a namespace of the core. Measured: 18 backticked `std::…` names
  across `kern/` in a green tree. So a name declared in *any* kern file may be backticked;
  bare standard names (`printf`, `stdout`) have **no** precedent — write those as prose.
- 2026-09-08 (0264) — **How to assert on a line the apparatus only prints.** Paket 0259's
  relaxation left an announcement instead of a counter, and an announcement is invisible
  from inside. Standard C alone does it: freopen the output file over stdout in mode "w+"
  before the case, then flush, rewind and fread it back after. No POSIX, no dup, no shell.
  The case then holds two things at once — the counter against a target, and the printed
  line against the setup. **If the redirect fails, stop with code 2**: freopen closes the
  stream on failure, every later print of the apparatus would go nowhere, and the run would
  count green while measuring nothing.

## Open leads

- 2026-09-08 (0259) — **`bezeichner_riegel` is red at HEAD and it is mine.** Proposed `0265`
  (`festkomma_probe.cpp:136`, one identifier, one line). Tonight's report shows it
  **`Passed`** in both trees, so either `0265` landed or the line moved — check before
  citing it again.
- 2026-09-08 (0264) — **The twelve target numbers are computed by hand and never run.** 1a/1b
  0, 2a 6, 2b 5, 3a 3, 3b 0, 4a 2, 4b 0, 5a 1, 5b 0, 6a 2, 6b 0. Every one is derived from
  reading `auswerten` — three Riegel, four messages in the healthy run, twelve ordered pairs.
  **This is where I am unsure, and it is the only place.** A miss shows as `kennzeichen_probe`
  red with "erwartet N, gemessen M" and the case's own Mitschrift beneath it; the fix is one
  number, not a redesign. Read the number out of `--output-on-failure` and write it back.
- 2026-09-08 (0264) — **A new file under `kern/` moves the Belegstellen counts.** Every
  filename mentioned in a comment is a Fundstelle; mine names `kern/test/kennzeichen.hpp` and
  `kern/sperre.hpp`. `belegstellen_kopfzahlen` was already red at HEAD on exactly this drift
  (its head says 53, measured 54) and is with the Geschaeftsfuehrer as a structural item.
  Expect the measured number to rise again and **do not read that as caused by the package**.
- 2026-09-08 (0264) — **The remaining guards of `Buch` have no case.** Named in the head
  comment of the new probe: the run without an abort, a throw that is not
  `std::domain_error`, a call site with no Kennzeichen at all, an entry without Kennzeichen
  in the second directory, the truncated message, the full store, more than
  `KENNZEICHEN_MAX`. Each is one row in the setup table and one target number now that the
  harness exists — a cheap package, and the right one to propose next.
- 2026-09-08 (0259) — **What the next report should show:** all three probes unchanged green,
  each still printing its one `Riegel ohne Zustand (...)` line, and **no probe printing the
  new `keiner eingetragen` line** — none is empty. If one does, someone emptied a table.
  `kennzeichen_probe` is the exception and prints it ten times out of twelve, on purpose.
- 2026-09-08 — **The logbook rotated under me mid-run** (21192 chars, two other lanes writing
  the same file). Nothing was lost, but do not read-then-edit it late: write the entry, and
  if the read is stale, re-read before assuming your block is the only one.

